# 라즈베리 파이 3에 QT앱 실행하기.

- `apt`가 파일을 받아오는 `ftp` 서버가 막혀있을 경우, 다음 파일에 들어가서 서버를 업데이트 한다.

```
$ sudo nano /etc/apt/sources.list

+++ in file +++
# comment below line in sources.list
# type wheezy or stretch
deb http://mirrordirector.raspbian.org/raspbian/ stretch main contrib non-free rpi

# type below
deb http://mirror.premi.st/raspbian/raspbian/ wheezy main contrib non-free rpi

deb http://ftp.jaist.ac.jp/raspbian/ wheezy main contrib non-free rpi


```

- 저장 후 나와서
- `$ sudo apt-get update`

- 터치 스크린 라이브러리 설치
- `$ sudo apt-get install tslib`

- qt gui 라이브러리를 설치한다.
- `sudo apt-get install libqtgui4`

- qt network 라이브러리 설치.
- `sudo apt-get install libqt4-network`

- DISPLAY 환경 변수가 필요한듯.
- `export DISPLAY=:0.0`

------------------------------

- QT를 pi3에 설치한다.
-

- QT-Creator을 설치함
sudo apt-get install qtcreator
