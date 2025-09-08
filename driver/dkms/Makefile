obj-m := ch343.o

KVER ?= $(shell uname -r)
KDIR ?= /lib/modules/$(KVER)/build
VERSION ?= $(shell cat VERSION)
SRC_DIR=$(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(SRC_DIR) modules

clean:
	$(MAKE) -C $(KDIR) M=$(SRC_DIR) clean

install:
	$(MAKE) -C $(KDIR) M=$(SRC_DIR) modules_install

unload:
	/sbin/rmmod ch343

load: unload
	/sbin/insmod ch343.ko

dkms.conf: dkms.conf.in
	sed "s/@@VERSION@@/$(VERSION)/" $^ > $@

dkms-add: dkms.conf
	/usr/sbin/dkms add $(SRC_DIR)

dkms-build: dkms.conf
	/usr/sbin/dkms build ch343/$(VERSION)

dkms-install: dkms.conf
	/usr/sbin/dkms install ch343/$(VERSION)

dkms-remove: dkms.conf
	/usr/sbin/dkms remove ch343/$(VERSION) --all

modprobe-install:
	modprobe ch343

modprobe-remove:
	modprobe -r ch343

dev: modprobe-remove dkms-remove dkms-add dkms-builddkms-install modprobe-install
