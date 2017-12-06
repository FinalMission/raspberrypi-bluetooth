scan: scan.o
	gcc -o scan scan.o -lbluetooth
	mv scan ../bin
	rm scan.o
scan.o: scan.c
	gcc -c scan.c

advertise: advertise.o
	gcc -o advertise advertise.o -lbluetooth
	mv advertise ../bin
	rm advertise.o
advertise.o: advertise.c
	gcc -c advertise.c
	
clean:
	rm -f scan.o
	rm -f advertise.o
