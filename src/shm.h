#define KEY_SHM 0x2222
#define STATUS_INVALID 0
#define STATUS_VALID 0xbeafbeaf
#define TIMEOUT 30
#define MAX_BUF 64
#define ERROR -1
typedef struct 
{
  char prefix[9];
  unsigned long long uuid[2];
  unsigned short major;
  unsigned short minor;
  char tx_power;
  char rssi;
}Packet;


#define P_OFFSET sizeof(Packet)

