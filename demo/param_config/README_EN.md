# **WCH USB configuration tool CH34xSerCfg instruction**



## **1.**Introduction

The CH34xSerCfg configuration software is used to configure USB parameters for the WCH USB-to-serial port series chips. The CH34XSerCFG configuration tool allows you to modify the vendor identifier VID, product identifier PID, maximum current value, BCD version number, vendor information, and product information string descriptor of the chips.

Chips models supported: CH342F, CH343P, CH344Q/L, CH346C, CH347T/F, CH348Q/L, CH9101U/H/R/Y, CH9102F, CH9103M, CH9104L, CH9344Q, CH9111L, CH9114F/L/W.

(Note: CH342F/CH9102F chips whose last 4th digit of the batch number is letter supports this configuration function.)

## 2.CH34xSerCfg function declaration

This section describes the functions of the CH34xSerCfg software. Before using the CH34XSerCFG software, install the corresponding VCP driver and application library. Download the following link:

[GitHub - WCHSoftGroup/ch343ser_linux: USB driver for USB to serial chip ch342, ch343, ch344, ch9101, ch9102, ch9103, etc](https://github.com/WCHSoftGroup/ch343ser_linux)

[GitHub - WCHSoftGroup/ch9344ser_linux](https://github.com/WCHSoftGroup/ch9344ser_linux)

###  2.1 Configuration Items

In the CONFIG.INI file, enter the configuration items that need to be modified, and skip the configuration items that do not need to be modified.

| Item                            | **Description**                                     | Value                                                        |
| :------------------------------ | :-------------------------------------------------- | :----------------------------------------------------------- |
| **VendorID**                    | Vendor ID                                           | Use a valid ID                                               |
| **ProductID**                   | Product ID                                          | Use a valid ID                                               |
| **MaxPower(HEX)**               | Max Power                                           | A hexadecimal value                                          |
| **PowerMode**                   | USB Power Mode                                      | Self-Powered or Bus-Powered                                  |
| **Wakeup_Enable**               | Wakeup Enable                                       | 1: enable 0: disable                                         |
| **CDC_CTSRTS_FlowControl**      | Whether to enable hardware flow control in CDC mode | 1: enable 0: disable                                         |
| **Pin_EEPROM_Def_Enable**       | Chip pins use default configuration of EEPROM       | 1: enable 0: disable                                         |
| **TNOW_DTR_SoftSet**            | TNOW/DTR pin function                               | 1: enable 0: disable                                         |
| **UARTx_TNOW_DTR_SETBIT**       | UARTx TNOW/DTR pin function                         | Fill in the 8bit hex number<br>bit0~bit7 correspond to UART0~UART7<br>1: TNOW 0: DTR |
| **CH9101RY_MODEM_Enable**       | CH9101R/Y MODEM pin function                        | 1: enable 0: disable                                         |
| **CH9101RY_DSR_MUX_TXS**        | CH9101RY  DSR# pin function                         | 0:TXS(default)  1: DSR#                                      |
| **CH9101RY_RI_MUX_RXS**         | CH9101RY RI# pin function                           | 0:RXS(default)  1: RI#                                       |
| **CH9101RY_DCD_MUX_TNOW**       | CH9101RY  DCD# pin function                         | 0:TNOW(default)  1: DCD#                                     |
| **CH9101RY_DTR_MUX_SUSPEND**    | CH9101RY DTR# pin function                          | 0:SLEEP((default))  1: DTR#                                  |
| **Serial_String_enable**        | USB Serial String enable                            | 1：enable 0：disable                                         |
| **Product_String_enable**       | USB Product String enable                           | 1：enable 0：disable                                         |
| **Manufacturer_String_enable**  | USB Manufacturer String enable                      | 1：enable 0：disable                                         |
| **Serial_String**               | USB Serial String                                   | Length range 0~24bytes                                       |
| **Product_String**              | USB Product String                                  | Length range 0~40bytes                                       |
| **Manufacturer_String**         | USB Manufacturer String                             | Length range 0~40bytes                                       |
| **Sleep_Mode_enable**           | USB sleep mode                                      | Support CH348Q/L, CH344Q, CH9114L/W/F, CH9111<br>1：enable 0：disable |
| **TXD_state**                   | TXD pin switches to a high impedance state function | 1：enable 0：disable                                         |
| **CH346_Extend_Config_Enabled** | CH346 Extended configuration enable                 | 1：enable 0：disable                                         |
| **CH346_Extend_Config_Freq**    | CH346 Chip frequency                                | Frequency value (decimal)<br>For example, 120000000          |
| **CH346_Extend_Config_Mode**    | CH346 Chip mode                                     | Mode 0/1/2                                                   |
| **CH346_Extend_Config_PLen**    | CH346 Packet length                                 | Passive parallel port or passive SPI interface communication packet size, must be a multiple of 512, the default is 512 bytes |
| **CH346_Extend_Config_M0_IO0**  | CH346 mode 0 IO0(PIN12) function configuration      | 0x00：RXD0<br/>0x01：TX_S<br/>0x02：ACT<br/>0x03：GPIO6      |
| **CH346_Extend_Config_M0_IO1**  | CH346 mode 0 IO1(PIN13) function configuration      | 0x00：TXD0<br/>0x01：RX_S<br/>0x02：SUSP<br/>0x03：GPIO7     |
| **CH346_Extend_Config_M1_IO0**  | CH346 mode 1 IO0(PIN15) function configuration      | 0x00：DCD0<br/>0x01：TX_S<br/>0x02：Invalid<br/>0x03：GPIO4  |
| **CH346_Extend_Config_M1_IO1**  | CH346 mode 1 IO1(PIN16) function configuration      | 0x00：DTR0<br/>0x01：RX_S<br/>0x02：Invalid<br/>0x03：GPIO2  |
| **CH346_Extend_Config_M2_IO0**  | CH346 mode 2 IO0(PIN13) function configuration      | 0x00：DCD1<br/>0x01：SUSP<br/>0x02：Invalid<br/>0x03：GPIO7  |
| **CH346_Extend_Config_M2_IO1**  | CH346 mode 3 IO1(PIN15) function configuration      | 0x00：DCD0<br/>0x01：TX_S<br/>0x02：Invalid<br/>0x03：GPIO4  |
| **CH346_Extend_Config_M2_IO2**  | CH346 mode 2 IO2(PIN16) function configuration      | 0x00：DTR0<br/>0x01：RX_S<br/>0x02：Invalid<br/>0x03：GPIO2  |
| **CH346_Extend_Config_M2_IO3**  | CH346 mode 2 IO3(PIN17) function configuration      | 0x00：DSR0<br/>0x01：ACT<br/>0x02：Invalid<br/>0x03：GPIO3   |

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

sudo ./CH34xSerCfg /dev/ttyCH343USB0 CONFIG.INI

Configuration file format

```shell
[Public]
VendorID=1a86
ProductID=
MaxPower(HEX)=80
PowerMode=Bus-Powered
Wakeup_Enable=0
CDC_CTSRTS_FlowControl=0
Pin_EEPROM_Def_Enable=0
TNOW_DTR_SoftSet=0
UARTx_TNOW_DTR_SETBIT=00
CH9101RY_MODEM_Enable=0
CH9101RY_DSR_MUX_TXS=0
CH9101RY_RI_MUX_RXS=0
CH9101RY_DCD_MUX_TNOW=0
CH9101RY_DTR_MUX_SUSPEND=0
Serial_String_enable=1
Product_String_enable=1
Manufacturer_String_enable=1
Serial_String=abcde
Product_String=WCH
Manufacturer_String=usb to uart
Sleep_Mode_enable=1
TXD_state=0
CH346_Extend_Config_Enable=0
CH346_Extend_Config_Freq=120000000
CH346_Extend_Config_Mode=1
CH346_Extend_Config_PLen=1024
CH346_Extend_Config_M0_IO0=0
CH346_Extend_Config_M0_IO1=0
CH346_Extend_Config_M1_IO0=0
CH346_Extend_Config_M1_IO1=0
CH346_Extend_Config_M2_IO0=0
CH346_Extend_Config_M2_IO1=0
CH346_Extend_Config_M2_IO2=0
CH346_Extend_Config_M2_IO3=0
```

Configuration example

```shell
press g to get usb config, s to set usb config, r to set default config, q to quit this app.
s
Update [ Serial_String_enable       ]----------> [ON ]
Update [ Product_String_enable      ]----------> [ON ]
Update [ Manufacturer_String_enable ]----------> [ON ]
Update [ VendorID                   ]----------> [NULL]
Update [ ProductID                  ]----------> [NULL]
Update [ MaxPower(HEX)              ]----------> [c8]
Update [ PowerMode                  ]----------> [Bus-Powered]
Update [ Wakeup_Enable              ]----------> [OFF]
Update [ TNOW_DTR_SoftSet           ]----------> [OFF]
Update [ CDC_CTSRTS_FlowControl     ]----------> [OFF]
Update [ CH9101RY_DSR_MUX_TXS       ]----------> [OFF]
Update [ Manufacturer_String        ]----------> [wch.cn]
Update [ Product_String             ]----------> [usb2.0 to multi]
Update [ Serial_String              ]----------> [12345abc]
Update [ Sleep_Mode_enable          ]----------> [ON ]
```

After the configuration is complete, enter 'g' to view the configuration

```shell
press g to get usb config, s to set usb config, r to set default config, q to quit this app.
g
************************EEPROM************************
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  
00:  53 23 E0 00 86 1A D9 55 00 00 64 80 00 00 00 00 
10:  12 12 03 31 00 32 00 33 00 34 00 35 00 61 00 62 
20:  00 63 00 00 00 00 00 00 20 20 03 75 00 73 00 62 
30:  00 32 00 2E 00 30 00 20 00 74 00 6F 00 20 00 6D 
40:  00 75 00 6C 00 74 00 69 00 00 00 00 00 00 00 00 
50:  0E 0E 03 77 00 63 00 68 00 2E 00 63 00 6E 00 00 
60:  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
70:  00 00 00 00 00 00 00 00 FF 00 00 00 00 00 00 00 
80:  00 00 00 00 00 00 00 00 00 00 
******************************************************

************************CHIP-CH348L************************
idVendor: 1a86
idProduct: 55d9
Max Power: 200mA
bcdUSB: 0000
Powermode: [Bus-Powered]
Remote Wakeup: [Disable]
Hardware Flow Control in CDC mode: [Disable]
TNOW/DTR pin function software configuration: [Disable]
bSerialNumber: 12345abc
bProductString: usb2.0 to multi
bManufacturerDescriptor: wch.cn
Sleep mode: [Enable]
************************************************************
```

Writes the vendor default configuration to the EEPROM

```shell
press g to get usb config, s to set usb config, r to set default config, q to quit this app.
r
Writing the default configuration...
************************EEPROM************************
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  
00:  53 23 E0 00 86 1A D4 55 44 84 43 A0 00 00 00 00 
10:  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
20:  00 00 00 00 00 00 00 00 24 24 03 55 00 53 00 42 
30:  00 20 00 53 00 69 00 6E 00 67 00 6C 00 65 00 20 
40:  00 53 00 65 00 72 00 69 00 61 00 6C 00 00 00 00 
50:  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
60:  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
70:  00 00 00 00 00 00 00 00 FF 00 00 00 00 00 00 00 
80:  00 00 00 00 00 00 00 00 00 00 
******************************************************
The default configuration is successfully written!
```

