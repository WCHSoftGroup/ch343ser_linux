CONFIG_MODULE_SIG=n

ifeq ($(KERNELRELEASE), )
DESTDIR ?= /
SCRIPLET ?= yes
PREFIX ?= /usr
KERNELRELEASE ?= $(shell uname -r)
KERNELDIR ?= /$(PREFIX)/lib/modules/$(KERNELRELEASE)/build
KERNELDESTDIR ?= $(DESTDIR)/$(PREFIX)/lib/modules/$(KERNELRELEASE)/kernel/drivers/usb/serial
WORKDIR ?= $(shell pwd)
build:
	mkdir -pv "$(WORKDIR)" || true
	cp *.c *.h Makefile "$(WORKDIR)/" || true
	$(MAKE) -C $(KERNELDIR)  M="$(WORKDIR)"
clean:
	rm -rf "$(WORKDIR)/"*.mk "$(WORKDIR)/".tmp_versions "$(WORKDIR)/"Module.symvers "$(WORKDIR)/"*.mod.c "$(WORKDIR)/"*.o "$(WORKDIR)/"*.ko "$(WORKDIR)/".*.cmd "$(WORKDIR)/"Module.markers "$(WORKDIR)/"modules.order "$(WORKDIR)/"*.a "$(WORKDIR)/"*.mod
load:
	insmod ch343.ko
unload:
	rmmod ch343
install: default
	insmod ch343.ko || true
	mkdir -p $(KERNELDESTDIR) || true
	cp -f "$(WORKDIR)/"ch343.ko $(KERNELDESTDIR) || true
ifeq ($(SCRIPLET),yes)
	@/bin/echo -e "ch343" >> /etc/modules || true
	depmod -a
endif
uninstall:
	rm -rf $(KERNELDESTDIR)/ch343.ko || true
ifeq ($(SCRIPLET),yes)
	rmmod ch343 || true
	depmod -a
endif
else
	obj-m := ch343.o
endif

