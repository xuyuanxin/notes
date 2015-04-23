obj-m := dns.o
kdir := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	make -C $(kdir) M=$(PWD) modules

clean:
	rm -f *.o *.ko *.mod.c 
