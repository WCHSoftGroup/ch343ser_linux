# **WCH USB configuration tool CH34xSerCfg instruction**



## **1.**Introduction

The CH34xSerCfg configuration software is used to configure USB parameters for the WCH USB-to-serial port series chips. The CH34XSerCFG configuration tool allows you to modify the vendor identifier VID, product identifier PID, maximum current value, BCD version number, vendor information, and product information string descriptor of the chips.

Chips models supported: CH343P, CH342F, CH347T/F, CH344Q/L, CH348Q/L, CH9101U/H/R/Y, CH9102F, CH9103M, CH9104L.

(Note: CH342F/CH9102F chips whose last 4th digit of the batch number is letter supports this configuration function.)

## 2.CH34xSerCfg function declaration

This section describes the functions of the CH34xSerCfg software. Before using the CH34XSerCFG software, install the corresponding VCP driver and application library. Download the following link:

[GitHub - WCHSoftGroup/ch343ser_linux: USB driver for USB to serial chip ch342, ch343, ch344, ch9101, ch9102, ch9103, etc](https://github.com/WCHSoftGroup/ch343ser_linux)

[GitHub - WCHSoftGroup/ch9344ser_linux](https://github.com/WCHSoftGroup/ch9344ser_linux)

###  2.1 Configuration Items

In the CONFIG.INI file, enter the configuration items that need to be modified, and skip the configuration items that do not need to be modified.

|             Item             |                   **Description**                   |              Value               |
| :--------------------------: | :-------------------------------------------------: | :------------------------------: |
|         **VendorID**         |                      Vendor ID                      |          Use a valid ID          |
|        **ProductID**         |                     Product ID                      |          Use a valid ID          |
|      **MaxPower(HEX)**       |                      Max Power                      | A hexadecimal value in 2mA units |
|        **PowerMode**         |                   USB Power Mode                    |   Self-Powered or Bus-Powered    |
|      **Wakeup_Enable**       |                    Wakeup Enable                    |       1: enable 0: disable       |
|  **CDC_CTSRTS_FlowControl**  | Whether to enable hardware flow control in CDC mode |       1: enable 0: disable       |
|      **EEPROM_Disable**      |      Disable the default eeprom configuration       |       1: disable 0: enable       |
|     **TNOW_DTR_SoftSet**     |                TNOW/DTR pin function                |       1: enable 0: disable       |
|  **CH9101RY_MODEM_Enable**   |            CH9101R/Y MODEM pin function             |       1: enable 0: disable       |
|   **CH9101RY_DSR_MUX_TXS**   |             CH9101RY  DSR# pin function             |     0:TXS(default)  1: DSR#      |
|   **CH9101RY_RI_MUX_RXS**    |              CH9101RY RI# pin function              |      0:RXS(default)  1: RI#      |
|  **CH9101RY_DCD_MUX_TNOW**   |             CH9101RY  DCD# pin function             |     0:TNOW(default)  1: DCD#     |
| **CH9101RY_DTR_MUX_SUSPEND** |             CH9101RY DTR# pin function              |   0:SLEEP((default))  1: DTR#    |
|      **Serial_String**       |                  USB Serial String                  |      Length range 0~24bytes      |
|      **Product_String**      |                 USB Product String                  |      Length range 0~40bytes      |
|   **Manufacturer_String**    |               USB Manufacturer String               |      Length range 0~40bytes      |

**Note:** 

- After the VID or PID of the device is changed, the original VCP driver is no longer applicable to the hardware. In this case, the device can only use the CDC driver delivered with the system (the CH340/CH348 series do not support the CDC driver). If the VCP driver is required, You need to add ID matching entries to the static const struct usb_device_id xxx_ids[] structure array of the driver, and then compile and load the driver again.
- Do not modify the content or format of the CONFIG.INI file other than the configuration items.

### 2.2 Method of compile and excute

- Obtain the libch34xcfg.so(.a), libch343.so(.a) and libch9344.so(.a) library files from the lib folder of ch343ser_linux and ch9344ser_linux repos, and place the library files in the system standard library path or param_config directory, copy all header files in the lib folder to the param_config directory;
- Enter the param_config directory and execute the command: gcc ch34x_demo_param_config.c -lch34xcfg -lch343 -lch9344 -o CH34xSerCfg

- command format 1: ./CH34xSerCfg [Serial device path]

​           enter 'g': Get current configuration

​           enter ‘s’: Configure the chip using CONFIG.INI

​	       enter ’r‘: Writes the vendor default configuration to the EEPROM

​           enter ‘q’: exit

### 2.3 Example

Excute program

sudo ./CH34xSerCfg /dev/ttyCH343USB0

Configuration file format

```shell
[Public]
VendorID=
ProductID=
MaxPower(HEX)=40
PowerMode=Bus-Powered
Wakeup_Enable=1
CDC_CTSRTS_FlowControl=1
EEPROM_Disable=1
TNOW_DTR_SoftSet=1
CH9101RY_MODEM_Enable=1
CH9101RY_DSR_MUX_TXS=0
CH9101RY_RI_MUX_RXS=0
CH9101RY_DCD_MUX_TNOW=0
CH9101RY_DTR_MUX_SUSPEND=0
Serial_String=abcdeabcde
Product_String=USB Single Serial
Manufacturer_String=www.wch.cn
```

Configuration example

```shell
press g to get usb config, s to set usb config, r to set default config, q to quit this app.
s
CINFIG.INI [VendorID] null
CINFIG.INI [ProductID] null
Update [MaxPower(HEX)] >>>>>>>>> [0x40].
Update [PowerMode] >>>>>>>>> [Bus-Powered].
Update [Wakeup_Enable] >>>>>>>>> [0x1].
Update [CDC_CTSRTS_FlowControl] >>>>>>>>> [0x0].
Update [EEPROM_Disable] >>>>>>>>> [0x0].
Update [TNOW_DTR_SoftSet] >>>>>>>>> [0x0].
Update [CH9101RY_MODEM_Enable] >>>>>>>>> [0x1].
Update [CH9101RY_DSR_MUX_TXS] >>>>>>>>> [0x0].
Update [CH9101RY_RI_MUX_RXS] >>>>>>>>> [0x0].
Update [CH9101RY_DCD_MUX_TNOW] >>>>>>>>> [0x0].
Update [CH9101RY_DTR_MUX_SUSPEND] >>>>>>>>> [0x0].
Update [Manufacturer_String] >>>>>>>>> [www.wch.cn].
Update [Product_String] >>>>>>>>> [USB Single Serial].
Update [Serial_String] >>>>>>>>> [abcdeabcde].

```

After the configuration is complete, enter 'g' to view the configuration

```shell
press g to get usb config, s to set usb config, r to set default config, q to quit this app.
g
************************EEPROM************************
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  
00:  53 23 E2 00 86 1A D8 55 41 0A 40 A0 00 00 00 00 
10:  16 16 03 61 00 62 00 63 00 64 00 65 00 61 00 62 
20:  00 63 00 64 00 65 00 00 24 24 03 55 00 53 00 42 
30:  00 20 00 53 00 69 00 6E 00 67 00 6C 00 65 00 20 
40:  00 53 00 65 00 72 00 69 00 61 00 6C 00 00 00 00 
50:  16 16 03 77 00 77 00 77 00 2E 00 77 00 63 00 68 
60:  00 2E 00 63 00 6E 00 00 00 00 00 00 00 00 00 00 
70:  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
80:  00 00 00 00 00 00 00 00 00 00 
******************************************************

************************CHIP-CH9101RY************************
idVendor: 1a86
idProduct: 55d8
bcdUSB: 0a41
Disable Hardware Flow Control in CDC mode.
Disable the default configuration of the EEPROM.
Disable TNOW/DTR pin function software configuration.
Enable Modem Pin Multiplex.
	DSR Multiplex pin function: TXS.
	RI  Multiplex pin function: RXS.
	DSR Multiplex pin function: TNOW.
	DTR Multiplex pin function: SLEEP.
bSerialNumber: abcdeabcde
bProductString: USB Single Serial
bManufacturerDescriptor: www.wch.cn
************************************************************

```

Writes the vendor default configuration to the EEPROM

```shell
press g to get usb config, s to set usb config, r to set default config, q to quit this app.
r
Writing the default configuration...
************************EEPROM************************
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  
00:  53 23 E0 00 86 1A D8 55 00 00 40 80 00 00 00 00 
10:  16 16 03 35 00 33 00 35 00 41 00 30 00 30 00 30 
20:  00 30 00 30 00 31 00 00 24 24 03 55 00 53 00 42 
30:  00 20 00 53 00 69 00 6E 00 67 00 6C 00 65 00 20 
40:  00 53 00 65 00 72 00 69 00 61 00 6C 00 00 00 00 
50:  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
60:  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
70:  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
80:  00 00 00 00 00 00 00 00 00 00 
******************************************************
The default configuration is successfully written!

```

