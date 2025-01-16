# **WCH USB 配置工具 CH34xSerCfg 使用说明**



## **一、概述**

CH34xSerCfg配置软件用于WCH USB转串口系列芯片进行USB参数配置，通过该工具可对芯片的厂商识别码VID、产品识别码PID、最大电流值、BCD版本号、厂商信息和产品信息字符串描述符等参数进行修改配置。

程序支持配置型号：CH342F、CH343P、CH344Q/L、CH346C、CH347T/F、CH348Q/L、CH9101U/H/R/Y、CH9102F、CH9103M、CH9104L、CH9344Q、CH9111L、CH9114F/L/W。

（注：CH342F/CH9102F批号倒数第4位是字母的芯片,则内置EEPROM可支持此配置功能。）

## **二、CH34xSerCfg 功能说明**

本节对 CH34xSerCfg 软件功能进行说明，使用前需安装对应产品VCP驱动和应用库，下载链接：

[GitHub - WCHSoftGroup/ch343ser_linux: USB driver for USB to serial chip ch342, ch343, ch344, ch9101, ch9102, ch9103, etc](https://github.com/WCHSoftGroup/ch343ser_linux)

[GitHub - WCHSoftGroup/ch9344ser_linux](https://github.com/WCHSoftGroup/ch9344ser_linux)

###  1、填写配置项

在CONFIG.INI文件中填写需要修改的配置项，**不需要修改的配置项可不用填写**。

| **配置项**                      | **说明**                           | 可选值/注意事项                                              |
| ------------------------------- | :--------------------------------- | :----------------------------------------------------------- |
| **VendorID**                    | 厂商识别码                         | 使用合法ID                                                   |
| **ProductID**                   | 产品识别码                         | 使用合法ID                                                   |
| **MaxPower(HEX)**               | 最大电源电流值                     | 填十六进制                                                   |
| **PowerMode**                   | USB供电方式                        | Self-Powered或Bus-Powered                                    |
| **Wakeup_Enable**               | 睡眠唤醒功能                       | 1：开启 0：关闭                                              |
| **CDC_CTSRTS_FlowControl**      | CDC模式下是否启用硬件流控          | 1：开启 0：关闭                                              |
| **Pin_EEPROM_Def_Enable**       | 芯片引脚是否启用EEPROM的默认配     | 支持 CH9102F 和 CH9101U/H/R/Y<br>1：开启 0：关闭             |
| **TNOW_DTR_SoftSet**            | TNOW/DTR引脚功能配置               | 支持 CH344、CH348 和 CH9104<br>1：开启 0：关闭               |
| **UARTx_TNOW_DTR_SETBIT**       | UARTx TNOW/DTR引脚功能配置         | 支持 CH344、CH348 和 CH9104；<br>需开启TNOW_DTR_SoftSet，填入8位16进制数值；<br>bit0~bit7对应UART0~UART7<br>1：TNOW 0：DTR |
| **CH9101RY_MODEM_Enable**       | CH9101R/Y芯片MODEM引脚功能配       | 支持CH9101RY<br>1：开启 0：关闭                              |
| **CH9101RY_DSR_MUX_TXS**        | CH9101RY  DSR#脚功能               | 支持CH9101RY<br>0:TXS功能(默认)  1: DSR#功能                 |
| **CH9101RY_RI_MUX_RXS**         | CH9101RY RI#脚功能                 | 支持CH9101RY<br>0:RXS功能(默认)  1: RI#功能                  |
| **CH9101RY_DCD_MUX_TNOW**       | CH9101RY  DCD#脚功能               | 支持CH9101RY<br>0:TNOW功能(默认)  1: DCD#功能                |
| **CH9101RY_DTR_MUX_SUSPEND**    | CH9101RY DTR#脚功能                | 支持CH9101RY<br>0:SLEEP功能(默认)  1: DTR#功能               |
| **Serial_String_enable**        | 开启USB设备序列号字符串使能        | 1：开启 0：关闭                                              |
| **Product_String_enable**       | 开启USB产品信息字符串使能          | 1：开启 0：关闭                                              |
| **Manufacturer_String_enable**  | 开启USB厂商信息字符串使能          | 1：开启 0：关闭                                              |
| **Serial_String**               | USB设备序列号字符串                | 长度范围0~24字节                                             |
| **Product_String**              | USB产品信息字符串                  | 长度范围0~40字节                                             |
| **Manufacturer_String**         | USB厂商信息字符串                  | 长度范围0~40字节                                             |
| **Sleep_Mode_enable**           | 芯片USB睡眠功能                    | 支持CH348Q/L、CH344Q、CH9114L/W/F、CH9111<br>1：开启 0：关闭 |
| **TXD_state**                   | TXD引脚切换成高阻态功能            | 支持CH342F、CH9102F<br>1：开启 0：关闭                       |
| **CH346_Extend_Config_Enabled** | CH346扩展配置使能                  | 1：开启 0：关闭                                              |
| **CH346_Extend_Config_Freq**    | CH346芯片工作主频                  | 填主频数值(十进制)<br>如120000000                            |
| **CH346_Extend_Config_Mode**    | CH346芯片工作模式                  | 有效值为0/1/2，分别表示工作模式0/1/2                         |
| **CH346_Extend_Config_PLen**    | CH346通信包大小                    | 被动并口或被动SPI接口通信包大小，必须是512的倍数，默认为512字节 |
| **CH346_Extend_Config_M0_IO0**  | CH346工作模式0的IO0(PIN12)功能配置 | 0x00：RXD0功能；<br/>0x01：TX_S功能；<br/>0x02：ACT功能；<br/>0x03：GPIO6功能 |
| **CH346_Extend_Config_M0_IO1**  | CH346工作模式0的IO1(PIN13)功能配置 | 0x00：TXD0功能；<br/>0x01：RX_S功能；<br/>0x02：SUSP功能；<br/>0x03：GPIO7功能 |
| **CH346_Extend_Config_M1_IO0**  | CH346工作模式1的IO0(PIN15)功能配置 | 0x00：DCD0功能；<br/>0x01：TX_S功能；<br/>0x02：无效；<br/>0x03：GPIO4功能 |
| **CH346_Extend_Config_M1_IO1**  | CH346工作模式1的IO0(PIN16)功能配置 | 0x00：DTR0功能；<br/>0x01：RX_S功能；<br/>0x02：无效；<br/>0x03：GPIO2功能 |
| **CH346_Extend_Config_M2_IO0**  | CH346工作模式2的IO0(PIN13)功能配置 | 0x00：DCD1功能；<br/>0x01：SUSP功能；<br/>0x02：无效；<br/>0x03：GPIO7功能 |
| **CH346_Extend_Config_M2_IO1**  | CH346工作模式2的IO1(PIN15)功能配置 | 0x00：DCD0功能；<br/>0x01：TX_S功能；<br/>0x02：无效；<br/>0x03：GPIO4功能 |
| **CH346_Extend_Config_M2_IO2**  | CH346工作模式2的IO2(PIN16)功能配置 | 0x00：DTR0功能；<br/>0x01：RX_S功能；<br/>0x02：无效；<br/>0x03：GPIO2功能 |
| **CH346_Extend_Config_M2_IO3**  | CH346工作模式2的IO3(PIN17)功能配置 | 0x00：DSR0功能；<br/>0x01：ACT功能；<br/>0x02：无效；<br/>0x03：GPIO3功能 |

**注意事项**：

- 修改设备的 VID 或 PID 后，原 VCP 驱动将不再适用于该硬件，设备此时只能使用系统自带 CDC 驱动（CH340/CH348 系列不支持系统 CDC 驱动），若需要使用 VCP 驱动，需在驱动static const struct usb_device_id xxx_ids[] 结构体数组中，增加对应的ID匹配项，重新编译、加载驱动。

- 不要修改CONFIG.INI文件中除配置项外的其他内容或格式。

### 2、编译和执行示例

- 从ch343ser_linux和ch9344ser_linux资料的lib文件夹中获取libch34xcfg.so(.a)、libch343.so(.a)和libch9344.so(.a)库文件，将库文件放置到系统标准库路径下或者param_config目录，将lib文件夹下所有头文件也拷贝至param_config目录；
- 进入param_config目录下，执行命令：gcc ch343_demo_param_config.c -lch34xcfg -lch343 -lch9344 -o CH34xSerCfg 
- 命令格式1：./CH34xSerCfg  [串口设备路径]  CONFIG.INI

​           输入g：获取当前配置

​           输入s：配置芯片

​	       输入r：向EEPROM写入厂商默认配置

​           输入q：退出程序

### 3、使用示例

执行程序

sudo ./CH34xSerCfg /dev/ttyCH343USB0 CONFIG.INI

配置文件

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

配置示例：

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

配置完成后输入’g’查看

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

向EEPROM写入厂商默认配置

```shell
press g to get usb config, s to set usb config, r to set default config, q to quit this app.
r
Writing the default configuration...
************************EEPROM************************
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  
00:  53 23 60 00 86 1A D9 55 00 00 32 80 00 00 00 00 
10:  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
20:  00 00 00 00 00 00 00 00 20 20 03 55 00 53 00 42 
30:  00 32 00 2E 00 30 00 20 00 54 00 6F 00 20 00 4D 
40:  00 75 00 6C 00 74 00 69 00 00 00 00 00 00 00 00 
50:  0E 0E 03 77 00 63 00 68 00 2E 00 63 00 6E 00 00 
60:  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
70:  00 00 00 00 00 00 00 00 FF 00 00 00 00 00 00 00 
80:  00 00 00 00 00 00 00 00 00 00 
******************************************************
The default configuration is successfully written!
```

