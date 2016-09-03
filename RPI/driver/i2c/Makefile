obj-m:=main.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=`pwd` modules
install:
	rmmod bcm2835-gpiomem i2c_dev
	insmod main.ko
uninstall:
	rmmod main
clean:
	make -C /lib/modules/$(shell uname -r)/build M=`pwd` clean
