# Load the ch343 driver using dkms.

## Installing ch343ser files on linux systems

```bash
git clone https://github.com/WCHSoftGroup/ch343ser_linux.git
pkgver=printf "%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short=7 HEAD)"
cd ch343ser_linux/driver/dkms
sudo install -Dm644 ch343.conf -t /etc/modules-load.d/
sudo install -Dm644 Makefile -t /usr/src/ch343ser-${pkgver}/
sudo install -Dm644 dkms.conf -t /usr/src/ch343ser-${pkgver}/
sudo install -Dm644 ../ch343.c -t /usr/src/ch343ser-${pkgver}/
sudo install -Dm644 ../ch343.h -t /usr/src/ch343ser-${pkgver}/
# Arch & Manjaro Linux
sudo install -Dm644 ../../udev/99-ch34x-arch.rules -t /usr/lib/udev/rules.d/
# Debian & Ubuntu Linux
sudo install -Dm644 ../../udev/99-ch34x.rules -t /usr/lib/udev/rules.d/
```

## dkms compilation of ch343ser depends on dkms and linux kernel headers.

- install ch343ser

```bash
sudo dkms add -m ch343ser -v ${pkgver}
sudo dkms build -m ch343ser -v ${pkgver}
sudo dkms install -m ch343ser -v ${pkgver}
cat /var/lib/dkms/ch343ser/${pkgver}/build/make.log
sudo dkms status
```

- remove ch343ser

```bash
sudo dkms remove -m ch343ser -v ${pkgver}
sudo dkms status
```

- autoinstall ch343ser

```bash
sudo dkms autoinstall
```

- force build ch343ser
```bash
sudo dkms build -m ch343ser -v ${pkgver} -k $(uname -r) --force
sudo dkms install -m ch343ser -v ${pkgver} -k $(uname -r) --force
```
