# Debian & Ubuntu Linux
1. Copy `99-ch34x.rules` file to the /etc/udev/rules.d/ directory.
2. Run `sudo udevadm control -R` to reload UDEV rules.
3. Plug out and plug in your device to the USB port. CDC-ACM device driver should not be used anymore for WCH USB-Serial converter devices.

# Arch & Manjaro Linux
1. Copy `99-ch34x-arch.rules` file to the `/etc/udev/rules.d/` directory.
2. Run `sudo gpasswd -a $USER uucp` `sudo udevadm control --reload` `sudo udevadm trigger` to reload UDEV rules.
3. Plug out and plug in your device to the USB port. CDC-ACM device driver should not be used anymore for WCH USB-Serial converter devices.
4. Installing [ch343ser via the AUR repository](https://aur.archlinux.org/pkgbase/ch343ser-git): `yay -Syu ch343ser-dkms-git`
