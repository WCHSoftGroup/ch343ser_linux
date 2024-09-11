CONFIG_MODULE_SIG=n

ifeq ($(KERNELRELEASE), )
DESTDIR ?= /
KERNELRELEASE ?= $(shell uname -r)
KERNELDIR ?= /lib/modules/$(KERNELRELEASE)/build
KERNELDESTDIR ?= $(DESTDIR)/lib/modules/$(KERNELRELEASE)/kernel/drivers/usb/serial
PWD ?= $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR)  M=$(PWD)  
clean:
	rm -rf *.mk .tmp_versions Module.symvers *.mod.c *.o *.ko .*.cmd Module.markers modules.order *.a *.mod
load:
	insmod ch343.ko
unload:
	rmmod ch343
install: default
	insmod ch343.ko || true
	mkdir -p $(KERNELDESTDIR) || true
	cp -f ./ch343.ko $(KERNELDESTDIR) || true
	@/bin/echo -e "ch343" >> /etc/modules || true
	depmod -a
uninstall:
	rmmod ch343 || true
	rm -rf $(KERNELDESTDIR)/ch343.ko || true
	depmod -a
else
	obj-m := ch343.o
endif
