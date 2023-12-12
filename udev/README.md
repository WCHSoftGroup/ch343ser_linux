1. Copy `99-ch34x.rules` file to the /etc/udev/rules.d/ directory.
2. Run `sudo udevadm control -R` to reload UDEV rules.
3. Plug out and plug in your device to the USB port. CDC-ACM device driver should not be used anymore for WCH USB-Serial converter devices.
