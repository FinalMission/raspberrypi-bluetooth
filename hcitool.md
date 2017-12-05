# hcitool
## hci란
  - Host Controller Interface의 약자이다.
  - hci protocol은 transport protocol(h4, h5, bcsp, usb,...) 위에 정의된다.
  - hci는 블루투스 표준 스펙의 일부이다.

- [참고1 - Stackoverflow](https://stackoverflow.com/questions/16151360/use-bluez-stack-as-a-peripheral-advertiser)
- [참고2 - 한글 블로그](https://arsviator.blogspot.kr/2016/05/using-raspberry-pi-as-beacon.html)
- [참고3 - advertise interval setting](https://stackoverflow.com/questions/21124993/is-there-a-way-to-increase-ble-advertisement-frequency-in-bluez)

### Configuration
- **pi zero w** 를 주변장치로 설정한 후, advertise packet을 날리도록 설정하는 코드.
- 아래의 코드는 **pi zero** 를 비콘 모드로 설정하는 코드이다.
- 비콘은 bluetooth의 subset이다. 즉, 블루투스의 일부 기능만 사용하는 셈.


```
# check if bluetooth module is exist
hciconfig

# enable hci0 interface
sudo hciconfig hci0 up

# configure advertising mode and data
sudo hcitool -i hci0 cmd 0x08 0x0008

# set advertise interval as 1280ms(=1.28s)
# parameter '0' means
#       Connectable undirected advertising (default)
# parameter '3' means
#       Non connectable undirected advertising

sudo hciconfig hci0 leadv 3

# disable scan from centrals.
sudo hciconfig hci0 noscan

# disable advertising mode
# sudo hciconfig hci0 noleadv
```

### Advertise interval 바꾸기
- [참조](https://stackoverflow.com/questions/21124993/is-there-a-way-to-increase-ble-advertisement-frequency-in-bluez)
```
  sudo hciconfig hci0 up
  sudo hcitool -i hci0 cmd 0x08 0x0008 1e 02 01 1a 1a ff 4c 00 02 15 e2 c5 6d b5 df fb 48 d2 b0 60 d0 f5 a7 10 96 e0 00 00 00 00 c5 00 00 00 00 00 00 00 00 00 00 00 00 00
  sudo hcitool -i hci0 cmd 0x08 0x0006 A0 00 A0 00 03 00 00 00 00 00 00 00 00 07 00
  sudo hcitool -i hci0 cmd 0x08 0x000a 01
```
