#!/bin/bash

cd ~
wget http://www.kernel.org/pub/linux/bluetooth/bluez-5.37.tar.xz
tar xvf bluez-5.37.tar.xz
cd bluez-5.37
sudo apt-get update
sudo apt-get install -y libusb-dev libdbus-1-dev libglib2.0-dev libudev-dev libical-dev libreadline-dev

./configure
make
sudo make install

systemctl status bluetooth
