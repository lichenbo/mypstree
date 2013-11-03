TARGET=helloworld
KDIR=/usr/src/linux-headers-3.11.0-12
PWD=$(shell pwd)
obj-m += $(TARGET).o
default:
	make -C $(KDIR) M=$(PWD) modules