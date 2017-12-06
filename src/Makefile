rssi: rssi.o
	gcc -o rssi rssi.o -lbluetooth
	mv rssi ../bin
	rm rssi.o
rssi.o: rssi.c
	gcc -c rssi.c

clean:
	rm -f rssi.o
