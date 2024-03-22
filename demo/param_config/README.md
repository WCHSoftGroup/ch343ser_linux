# **WCH USB 配置工具 CH34xSerCfg 使用说明**



## **一、概述**

CH34xSerCfg配置软件用于WCH USB转串口系列芯片进行USB参数配置，通过该工具可对芯片的厂商识别码VID、产品识别码PID、最大电流值、BCD版本号、厂商信息和产品信息字符串描述符等参数进行修改配置。

程序支持配置型号：CH343P、CH342F、CH347T/F、CH344Q/L、CH348Q/L、CH9101U/H/R/Y、CH9102F、CH9103M、CH9104L。

（注：CH342F/CH9102F批号倒数第4位是字母的芯片,则内置EEPROM可支持此配置功能。）

## **二、CH34xSerCfg 功能说明**

本节对 CH34xSerCfg 软件功能进行说明，使用前需安装对应产品VCP驱动和应用库，下载链接：

[GitHub - WCHSoftGroup/ch343ser_linux: USB driver for USB to serial chip ch342, ch343, ch344, ch9101, ch9102, ch9103, etc](https://github.com/WCHSoftGroup/ch343ser_linux)

[GitHub - WCHSoftGroup/ch9344ser_linux](https://github.com/WCHSoftGroup/ch9344ser_linux)

###  1、填写配置项

在CONFIG.INI文件中填写需要修改的配置项，**不需要修改的配置项可不用填写**。

|          **配置项**          |            **说明**            |        可选值/注意事项         |
| :--------------------------: | :----------------------------: | :----------------------------: |
|         **VendorID**         |           厂商识别码           |           使用合法ID           |
|        **ProductID**         |           产品识别码           |           使用合法ID           |
|      **MaxPower(HEX)**       |         最大电源电流值         |    以2mA为单位，填十六进制     |
|        **PowerMode**         |          USB供电方式           |   Self-Powered或Bus-Powered    |
|      **Wakeup_Enable**       |          睡眠唤醒功能          |        1：开启 0：关闭         |
|  **CDC_CTSRTS_FlowControl**  |   CDC模式下是否启用硬件流控    |        1：开启 0：关闭         |
|      **EEPROM_Disable**      |       禁用eeprom默认配置       |        1：禁用 0：开启         |
|     **TNOW_DTR_SoftSet**     |      TNOW/DTR引脚功能配置      |        1：开启 0：关闭         |
|  **CH9101RY_MODEM_Enable**   | CH9101R/Y芯片MODEM引脚功能配置 |        1：开启 0：关闭         |
|   **CH9101RY_DSR_MUX_TXS**   |      CH9101RY  DSR#脚功能      |  0:TXS功能(默认)  1: DSR#功能  |
|   **CH9101RY_RI_MUX_RXS**    |       CH9101RY RI#脚功能       |  0:RXS功能(默认)  1: RI#功能   |
|  **CH9101RY_DCD_MUX_TNOW**   |      CH9101RY  DCD#脚功能      | 0:TNOW功能(默认)  1: DCD#功能  |
| **CH9101RY_DTR_MUX_SUSPEND** |      CH9101RY DTR#脚功能       | 0:SLEEP功能(默认)  1: DTR#功能 |
|      **Serial_String**       |      USB设备序列号字符串       |        长度范围0~24字节        |
|      **Product_String**      |       USB产品信息字符串        |        长度范围0~40字节        |
|   **Manufacturer_String**    |       USB厂商信息字符串        |        长度范围0~40字节        |

**注意事项**：

- 修改设备的 VID 或 PID 后，原 VCP 驱动将不再适用于该硬件，设备此时只能使用系统自带 CDC 驱动（CH340/CH348 系列不支持系统 CDC 驱动），若需要使用 VCP 驱动，需在驱动static const struct usb_device_id xxx_ids[] 结构体数组中，增加对应的ID匹配项，重新编译、加载驱动。

- 不要修改CONFIG.INI文件中除配置项外的其他内容或格式。

### 2、编译和执行示例

- 从ch343ser_linux和ch9344ser_linux资料的lib文件夹中获取libch34xcfg.so(.a)、libch343.so(.a)和libch9344.so(.a)库文件，将库文件放置到系统标准库路径下或者param_config目录，将lib文件夹下所有头文件也拷贝至param_config目录；
- 进入param_config目录下，执行命令：gcc ch34x_demo_param_config.c -lch34xcfg -lch343 -lch9344 -o CH34xSerCfg
- 命令格式1：./CH34xSerCfg [串口设备路径]

​           输入g：获取当前配置

​           输入s：配置芯片

​	       输入r：向EEPROM写入厂商默认配置

​           输入q：退出程序

### 3、使用示例

执行程序

sudo ./CH34xSerCfg /dev/ttyCH343USB0

配置文件

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

配置示例：

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

配置完成后输入’g’查看

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

向EEPROM写入厂商默认配置

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

