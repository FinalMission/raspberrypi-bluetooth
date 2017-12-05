# BlueZ Configuration
### 1. BlueZ 라이브러리 설치 및 설정
http://www.bluez.org/download

### 2. bluez-4.42.tar.gz 압축해제
```bash
sudo tar xvfJ bluez-4.42.tar.gz
sudo cd bluez-4.4.2
```
### 3.라이브러리 설치

#### 1) apt-get fetching 주소 변경
```bash
sudo vim /etc/apt/sources.list
%s/kr.archive.ubuntu.com/ftp.daumkakao.com/
```
#### 2) apt-get 으로 각종 라이브러리 설치
```bash
sudo apt-get install libgtk2.0-dev
sudo apt-get install dbus-*dev
sudo apt-get install libusb-dev
sudo apt-get install libudev-dev
sudo apt-get install libical-dev
sudo apt-get install libreadline-dev
```
#### 3) install
```bash
sudo  ./configure --prefix=/usr/local/BlueZ
sudo make
sudo make install
```
#### 셋업 및 blueZ 사용법 레퍼런스 주소
- [hcitool](http://www.dreamy.pe.kr/zbxe/CodeClip/3768994)
- [bluez 라이브러리  설치 및 설정](http://blog.naver.com/lswcharming/30093416977)
- [bluez 라이브러리 명령어](http://chiccoder.tistory.com/14)
- [bluetoothctl 이용한 페어링 방법](http://webnautes.tistory.com/1137)

------------------------------------------------

### Login
- In terminal

```
  ssh pi@raspberrypi.local
```

- ID as **pi**, password as **raspberry**

- bluetoothctl의 명령어 목록을 보려면 ```help``` 를 친다.

#### Device info

```
  bluetooth my-iPhone
  74:1B:B2:59:FB:02

  bluetooth raspberry pi zero w mac address
  B8:27:EB:0C:CF:BD

  bluetooth cs-macbook-pro
  F4:0F:24:29:73:C0

  bluetooth raspberry pi UUID
  E2C56DB5DFFB48D2B060D0F5A71096E0
```

### Command
#### hcitool

```
  - 주변 블루투스 장치 스캔
  pi@raspberrypi:~ $ hcitool scan
```

#### bluetoothctl
- bluetoothctl 프로그램 실행

```bash
  pi@raspberrypi:~ $ bluetoothctl

  - 라즈베리 파이 모듈 정보 확인
  pi@raspberrypi:~ $ show

  - 모듈 전원 on/off
  pi@raspberrypi:~ $ power on/off

  - 라즈베리 파이 장치를 다른 장치에서 검색가능 하게 할지/말지
  pi@raspberrypi:~ $ discoverable on/off

  - pairing 가능여부 on/off
  pi@raspberrypi:~ $ pairable on/off

  - 블루투스 agent on/off
  pi@raspberrypi:~ $ agent on/off

  - 연결하고자 하는 블루투스 장비의 정보 확인
  pi@raspberrypi:~ $ info [MAC-ADDRESS]
```

```
  list                         List available controllers
  show [ctrl]                  Controller information
  select <ctrl>                Select default controller
  devices                      List available devices
  paired-devices               List paired devices
  power <on/off>               Set controller power
  pairable <on/off>            Set controller pairable mode
  discoverable <on/off>        Set controller discoverable mode
  agent <on/off/capability>    Enable/disable agent with given capability
  default-agent                Set agent as the default one
  advertise <on/off/type>      Enable/disable advertising with given type
  set-advertise-uuids [uuid1 uuid2 ...]                Set advertise uuids
  set-advertise-service [uuid][data=[xx xx ...]        Set advertise service data
  set-advertise-manufacturer [id][data=[xx xx ...]     Set advertise manufacturer data
  set-advertise-tx-power <on/off>                      Enable/disable TX power to be advertised
  set-scan-filter-uuids [uuid1 uuid2 ...]              Set scan filter uuids
  set-scan-filter-rssi [rssi]                          Set scan filter rssi, and clears pathloss
  set-scan-filter-pathloss [pathloss]                  Set scan filter pathloss, and clears rssi
  set-scan-filter-transport [transport]                Set scan filter transport
  set-scan-filter-clear          Clears discovery filter.
  scan <on/off>                  Scan for devices
  info [dev]                     Device information
  pair [dev]                     Pair with device
  trust [dev]                    Trust device
  untrust [dev]                  Untrust device
  block [dev]                    Block device
  unblock [dev]                  Unblock device
  remove <dev>                   Remove device
  connect <dev>                  Connect device
  disconnect [dev]               Disconnect device
  list-attributes [dev]          List attributes
  set-alias <alias>              Set device alias
  select-attribute <attribute>   Select attribute
  attribute-info [attribute]     Select attribute
  read                           Read attribute value
  write <data=[xx xx ...]>       Write attribute value
  notify <on/off>                Notify attribute value
  register-profile <UUID ...>    Register profile to connect
  unregister-profile             Unregister profile
  version                        Display version
  quit                           Quit program

```
