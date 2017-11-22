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
