#define KEY_SHM 0x2222
#define STATUS_INVALID 0
#define STATUS_VALID 0xbeafbeaf
#define TIMEOUT 30
#define MAX_BUF 64
#define ERROR -1
#define SEG1 0xffeeddcc
#define SEG2 0xbbaa9988
#define SEG3 0x77665544
#define PI0_SEG4 0x33221199
#define PI1_O_SEG4 0x332211ff
#define PI1_X_SEG4 0x33221100

typedef struct 
{
  char prefix[9];
  unsigned int uuid[4];
  unsigned short major;
  unsigned short minor;
  char tx_power;
  char rssi;
}Packet;


#define P_OFFSET sizeof(Packet)

