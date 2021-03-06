//
//  Intel Edison Playground
//  Copyright (c) 2015 Damian Kołakowski. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <curses.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"
#include <errno.h>

struct hci_request ble_hci_request(uint16_t ocf, int clen, void * status, void * cparam)
{
	struct hci_request rq;
	memset(&rq, 0, sizeof(rq));
	rq.ogf = OGF_LE_CTL;
	rq.ocf = ocf;
	rq.cparam = cparam;
	rq.clen = clen;
	rq.rparam = status;
	rq.rlen = 1;
	return rq;
}
// void validation(le_advertising_info * info, Packet * packet)
// {
// 	printf(" RAW | Packet \n");
// 	printf("%04X | %04X\n", *(unsigned short *)(info->data + 25), packet->major);
// 	printf("%02X | %02X\n", (char)info->data[29], packet->tx_power);
// 	printf("%02X | %02X\n", (char)info->data[30], packet->rssi);
// }

void inject_packet(char * addr, char rssi, Packet * packet)
{
	int i, j;
	for(i = 0; i < 18; i++) packet->addr[i] = addr[i];
	packet->rssi = rssi;
}

void print_ble_info(le_advertising_info * info){
	if((int)info->length != 30) return;
	char addr[18];
	ba2str(&(info->bdaddr), addr);

	printf("event type : %d\n", (int)info->evt_type);
	printf("ble device type : %d\n", (int)info->bdaddr_type);
	printf("ble device addr : %s\n", addr);
	printf("ble length : %d\n", (int)info->length + 1);
	printf("ble tx power : 0x%02X\n", (int)info->data[info->length -1]);
	printf("ble rssi %d\n", (int)(info->data[info->length] | 0xffffff00));

	 printf("info->data : ====================\n");
	int len=(int)info->length + 1;
	int index=0;
	while(len--){
	  printf("[%02d] : 0x%02X ", (index+1), (signed int)info->data[index++]);
		if(index %10 == 0) printf("\n");
	}

	printf("\n========================================\n");
}

void checkMACaddr(char * addr, int rssi, Packet * packetshm)
{
	if(!strcmp(addr, PI0W1))
	{
		printf("[PI0 W 1] %d\n", rssi);
		inject_packet(addr, rssi, &packetshm[0]);
	}
	else if(!strcmp(addr, PI0W2))
	{
		printf("[PI0 W 2] %d\n", rssi);
		inject_packet(addr, rssi, &packetshm[1]);
	}
	else if(!strcmp(addr, PI0W3))
	{
		printf("[PI0 W 3] %d\n", rssi);
		inject_packet(addr, rssi, &packetshm[2]);
	}else{
		//printf("[MAC-%s] %d\n", addr, (int)rssi | 0xffffffff00);
	}
}

int main()
{
	int ret, status;

	// Get HCI device.

	const int device = hci_open_dev(hci_get_route(NULL));
	if ( device < 0 ) {
		perror("Failed to open HCI device.");
		return 0;
	}

	// Set BLE scan parameters.

	le_set_scan_parameters_cp scan_params_cp;
	memset(&scan_params_cp, 0, sizeof(scan_params_cp));
	scan_params_cp.type 			= 0x00;
	scan_params_cp.interval 		= htobs(0x0010);
	scan_params_cp.window 			= htobs(0x0010);
	scan_params_cp.own_bdaddr_type 	= 0x00; // Public Device Address (default).
	scan_params_cp.filter 			= 0x00; // Accept all.

	struct hci_request scan_params_rq = ble_hci_request(OCF_LE_SET_SCAN_PARAMETERS, LE_SET_SCAN_PARAMETERS_CP_SIZE, &status, &scan_params_cp);

	ret = hci_send_req(device, &scan_params_rq, 1000);
	if ( ret < 0 ) {
		hci_close_dev(device);
		perror("Failed to set scan parameters data.");
		return 0;
	}

	// Set BLE events report mask.

	le_set_event_mask_cp event_mask_cp;
	memset(&event_mask_cp, 0, sizeof(le_set_event_mask_cp));
	int i = 0;
	for ( i = 0 ; i < 8 ; i++ ) event_mask_cp.mask[i] = 0xFF;

	struct hci_request set_mask_rq = ble_hci_request(OCF_LE_SET_EVENT_MASK, LE_SET_EVENT_MASK_CP_SIZE, &status, &event_mask_cp);
	ret = hci_send_req(device, &set_mask_rq, 1000);
	if ( ret < 0 ) {
		hci_close_dev(device);
		perror("Failed to set event mask.");
		return 0;
	}


	// Enable scanning.

	le_set_scan_enable_cp scan_cp;
	memset(&scan_cp, 0, sizeof(scan_cp));
	scan_cp.enable 		= 0x01;	// Enable flag.
	scan_cp.filter_dup 	= 0x00; // Filtering disabled.

	struct hci_request enable_adv_rq = ble_hci_request(OCF_LE_SET_SCAN_ENABLE, LE_SET_SCAN_ENABLE_CP_SIZE, &status, &scan_cp);

	ret = hci_send_req(device, &enable_adv_rq, 1000);
	if ( ret < 0 ) {
		hci_close_dev(device);
		perror("Failed to enable scan.");
		return 0;
	}

	// Get Results.

	struct hci_filter nf;
	hci_filter_clear(&nf);
	hci_filter_set_ptype(HCI_EVENT_PKT, &nf);
	hci_filter_set_event(EVT_LE_META_EVENT, &nf);
	if ( setsockopt(device, SOL_HCI, HCI_FILTER, &nf, sizeof(nf)) < 0 ) {
		hci_close_dev(device);
		perror("Could not set socket options\n");
		return 0;
	}

	printf("Scanning....\n");

	uint8_t buf[HCI_MAX_EVENT_SIZE];
	evt_le_meta_event * meta_event;
	le_advertising_info * info;
//	Packet packet;
	Packet * packetshm;
	int len;
	int offset = sizeof(Packet);
	//============ attach shared memory ===============
	int id_shm;
	id_shm = shmget((key_t)KEY_SHM, sizeof(Packet[3]), 0777 | IPC_CREAT);
	if(id_shm == ERROR)
	{
		printf("error: %s (%d)\n", strerror(errno), __LINE__);
		return EXIT_FAILURE;
	}
	packetshm = shmat(id_shm, (void *)0, 0);
	if(packetshm == (Packet *)ERROR)
	{
		printf("error: %s (%d)\n", strerror(errno), __LINE__);
                return EXIT_FAILURE;
	}
        //============ attach shared memory ===============


	while ( 1 ) {
		len = read(device, buf, sizeof(buf));
		if ( len >= HCI_EVENT_HDR_SIZE ) {
			meta_event = (evt_le_meta_event*)(buf+HCI_EVENT_HDR_SIZE+1);
			if ( meta_event->subevent == EVT_LE_ADVERTISING_REPORT ) {
				uint8_t reports_count = meta_event->data[0];
				void * offset = meta_event->data + 1;
				while ( reports_count-- ) {
					info = (le_advertising_info *)offset;
					char addr[18];
					ba2str(&(info->bdaddr), addr);
					checkMACaddr(addr, (int)(info->data[info->length] | 0xffffff00), packetshm);
					offset = info->data + info->length + 2;
//					print_ble_info(info);
				}
			}
		}
	}
        //============ detach shared memory ===============
	ret = shmdt(packetshm);
        if(ret == ERROR)
        {
                printf("error: %s (%d)\n", strerror(errno), __LINE__);
                return EXIT_FAILURE;
        }
	//============ detach shared memory ===============


	// Disable scanning.
	memset(&scan_cp, 0, sizeof(scan_cp));
	scan_cp.enable = 0x00;	// Disable flag.

	struct hci_request disable_adv_rq = ble_hci_request(OCF_LE_SET_SCAN_ENABLE, LE_SET_SCAN_ENABLE_CP_SIZE, &status, &scan_cp);
	ret = hci_send_req(device, &disable_adv_rq, 1000);
	if ( ret < 0 ) {
		hci_close_dev(device);
		perror("Failed to disable scan.");
		return 0;
	}

	hci_close_dev(device);

	return 0;
}
