#!/bin/bash
# ref: http://www.theregister.co.uk/Print/2013/11/29/feature_diy_apple_ibeacons/
set -x
# inquiry local bluetooth device
#hcitool dev
export BLUETOOTH_DEVICE=hci0
#sudo hcitool -i hcix cmd <OGF> <OCF> <No. Significant Data Octets> <iBeacon Prefix> <UUID> <Major> <Minor> <Tx Power> <Placeholder Octets>

#OGF = Operation Group Field = Bluetooth Command Group = 0x08
#OCF = Operation Command Field = HCI_LE_Set_Advertising_Data = 0x0008
#No. Significant Data Octets (Max of 31) = 1E (Decimal 30)
#iBeacon Prefix (Always Fixed) = 02 01 1A 1A FF 4C 00 02 15

export OGF="0x08"
export OCF="0x0008"
# =============== Advertising Data Structure ===============
# Total 31 Bytes = DATA_OCTETS(1B) + DATA(30B)
# iBeacon prefix(9B) | Proximity UUID(16B) | Major(2B) | Minor(2B) | TX Power(2B)

export DATA_OCTETS="1E"  # 0x1E == 30 Bytes
export NUMBER_OF_BYTES_FOLLOW_IN_FIRST_AD_STRUCTURE="02"
export FLAGS_AD_TYPE="01"
export FLAG_VALUES="1A"
'
  0x1A : 0001 1010
  bit 0 (OFF) LE Limited Discoverable Mode
  bit 1 (ON) LE General Discoverable Mode
  bit 2 (OFF) BR/EDR Not Supported
  bit 3 (ON) Simultaneous LE and BR/EDR to Same Device Capable (controller)
  bit 4 (ON) Simultaneous LE and BR/EDR to Same Device Capable (Host)
'
export ADVERTISING_FLAG="$NUMBER_OF_BYTES_FOLLOW_IN_FIRST_AD_STRUCTURE $FLAGS_AD_TYPE $FLAG_VALUES"

export NUMBER_OF_BYTES_FOLLOW_IN_SECOND_AD_STRUCTURE="1A"  # 0x1A = 26 Bytes
export MANUFACTURER_SPECIFIC_DATA="FF"
export ADVERTISING_HEADER="$NUMBER_OF_BYTES_FOLLOW_IN_SECOND_AD_STRUCTURE $MANUFACTURER_SPECIFIC_DATA"

export COMPANY_ID="4C 00" # Apple ID

export IBEACON_TYPE="02"
export IBEACON_LENGTH="15"
export BEACON_ADVERTISE_INDICATOR="$IBEACON_TYPE $IBEACON_LENGTH"

# iBeacon prefix is 9 Bytes
export IBEACON_PREFIX="$DATA_OCTETS $ADVERTISING_FLAG $ADVERTISING_HEADER $COMPANY_ID $BEACON_ADVERTISE_INDICATOR"

#uuidgen  could gerenate uuid
# export UUID="4a 4e ce 60 7e b0 11 e4 b4 a9 08 00 20 0c 9a 66"
export UUID="00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff" # 16B
export MAJOR="00 02"  # 2B
export MINOR="00 01"  # 2B
# ref : http://www.argenox.com/a-ble-advertising-primer/
# 2’s complement of the calibrated TX power
export TX_POWER="B5 00" # interpreted as 0x00C5

#interval constants
export MIN_INTERVAL="0A 00"  # 10ms
export MAX_INTERVAL="0B 00"  # 20ms

export ENABLE_ADVERTISE="0x08 0x000a"
export SET_ADVERTISE_PARAMS="0x08 0x0006"


# initialize device
sudo hciconfig $BLUETOOTH_DEVICE up
# disable advertising
# sudo hciconfig $BLUETOOTH_DEVICE noleadv
# stop the dongle looking for other Bluetooth devices
sudo hciconfig $BLUETOOTH_DEVICE noscan

sudo hciconfig $BLUETOOTH_DEVICE pscan


sudo hciconfig $BLUETOOTH_DEVICE leadv

# advertise
sudo hcitool -i $BLUETOOTH_DEVICE cmd $OGF $OCF $IBEACON_PREFIX $UUID $MAJOR $MINOR $TX_POWER
sudo hcitool -i $BLUETOOTH_DEVICE cmd $SET_ADVERTISE_PARAMS $MIN_INTERVAL $MAX_INTERVAL 00 00 00 00 00 00 00 00 00 $TX_POWER
sudo hcitool -i $BLUETOOTH_DEVICE cmd $ENABLE_ADVERTISE 01

echo "COMPLETE"
