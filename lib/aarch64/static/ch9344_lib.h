#ifndef _CH9344_LIB_H
#define _CH9344_LIB_H

#define IOCTL_MAGIC 'W'
#define IOCTL_CMD_GPIOENABLE _IOW(IOCTL_MAGIC, 0x80, uint16_t)
#define IOCTL_CMD_GPIODIR _IOW(IOCTL_MAGIC, 0x81, uint16_t)
#define IOCTL_CMD_GPIOSET _IOW(IOCTL_MAGIC, 0x82, uint16_t)
#define IOCTL_CMD_GPIOGET _IOWR(IOCTL_MAGIC, 0x83, uint16_t)
#define IOCTL_CMD_GETCHIPTYPE _IOR(IOCTL_MAGIC, 0x84, uint16_t)
#define IOCTL_CMD_GETUARTINDEX _IOR(IOCTL_MAGIC, 0x85, uint16_t)
#define IOCTL_CMD_CTRLIN _IOWR(IOCTL_MAGIC, 0x90, uint16_t)
#define IOCTL_CMD_CTRLOUT _IOW(IOCTL_MAGIC, 0x91, uint16_t)
#define IOCTL_CMD_CMDIN _IOWR(IOCTL_MAGIC, 0x92, uint16_t)
#define IOCTL_CMD_CMDOUT _IOW(IOCTL_MAGIC, 0x93, uint16_t)

typedef enum {
	CHIP_CH9344L = 0,
	CHIP_CH9344Q,
	CHIP_CH348L,
	CHIP_CH348Q,
} CH9344_CHIPTYPE;

/**
 * libch9344_open - open ch9344 device
 * @devname: ch9344 tty device or gpio device name,
 * tty device: /dev/tty*, gpio device: /dev/ch9344_iodev*
 *
 * In this demo device is opened blocked, you could modify it at will.
 */
extern int libch9344_open(const char *devname);

/**
 * libch9344_close - close ch9344 device
 * @fd: file descriptor of ch9344 tty device or gpio device
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_close(int fd);

/**
 * libch9344_get_chiptype - get chip model
 * @fd: file descriptor of ch9344 tty device or gpio device
 * @type: pointer to chip model
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_get_chiptype(int fd, CH9344_CHIPTYPE *type);

/**
 * libch9344_get_uartindex - get uart index number
 *         0->UART0, 1->UART1, 2->UART2, 3->UART3,
 *         4->UART4, 5->UART5, 6->UART6, 7->UART7
 * @fd: file descriptor of ch9344 tty device
 * @index: pointer to uart index
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_get_uartindex(int fd, uint8_t *index);

/**
 * libch9344_control_msg_in - control transfer in
 * @fd: file descriptor of ch9344 tty device or gpio device
 * @request: USB message request value
 * @requesttype: USB message request type value
 * @value: USB message value
 * @index: USB message index value
 * @data: pointer to the data to receive
 * @size: length in bytes of the data to receive
 *
 * The function returns the number of bytes transferred if successful.
 * Otherwise, a negative error number.
 */
extern int libch9344_control_msg_in(int fd, uint8_t request,
				    uint8_t requesttype, uint16_t value,
				    uint16_t index, uint8_t *data,
				    uint16_t size);

/**
 * libch9344_control_msg_out - control transfer out
 * @fd: file descriptor of ch9344 tty device or gpio device
 * @request: USB message request value
 * @requesttype: USB message request type value
 * @value: USB message value
 * @index: USB message index value
 * @data: pointer to the data to send
 * @size: length in bytes of the data to send
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_control_msg_out(int fd, uint8_t request,
				     uint8_t requesttype, uint16_t value,
				     uint16_t index, uint8_t *data,
				     uint16_t size);

/**
 * libch9344_cmd_msg_in - command transfer in
 * @fd: file descriptor of ch9344 tty device or gpio device
 * @sdata: pointer to the data to send
 * @size: length in bytes of the data to send
 * @rdata: pointer to the data to receive
 *
 * The function returns the number of bytes received if successful.
 * Otherwise, a negative error number.
 */
extern int libch9344_cmd_msg_in(int fd, uint8_t *sdata, uint16_t size,
				uint8_t *rdata);

/**
 * libch9344_cmd_msg_out - command transfer out
 * @fd: file descriptor of ch9344 tty device or gpio device
 * @data: pointer to the data to send
 * @size: length in bytes of the data to send
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_cmd_msg_out(int fd, uint8_t *data, uint16_t size);

/**
 * libch9344_gpioenable - gpio enable
 * @fd: file descriptor of ch9344 gpio device
 * @gpiogroup: gpio group
 *             CH9344: gpio0-11, 0 on gpio0-2, 1 on gpio3-5, 2 on gpio6-8,
 *                     3 on gpio9-11
 * 			   CH348L: gpio0-47, 0 on gpio0-7, 1 on gpio8-15, 2 on gpio16-23
 *                     3 on gpio24-31, 4 on gpio32-39, 5 on gpio40-47
 * @gpioenable: gpio enable value
 *             CH9344: 1 on gpios of group all enable, 0 on all disable
 *             CH348L&Q: bits0-7 on gpio[0*N-7*N],
 *                     1 on enable, 0 on disable
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_gpioenable(int fd, uint8_t gpiogroup,
				uint8_t gpioenable);

/**
 * libch9344_gpiodirset - gpio direction set
 * @fd: file descriptor of ch9344 gpio device
 * @gpionumber: gpio number
 * @gpiodir: gpio direction value, 1 on output, 0 on input
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_gpiodirset(int fd, uint8_t gpionumber,
				uint8_t gpiodir);

/**
 * libch9344_gpioset - gpio output level set
 * @fd: file descriptor of ch9344 gpio device
 * @gpionumber: gpio number
 * @gpioval: gpio output value, 1 on high, 0 on low
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_gpioset(int fd, uint8_t gpionumber, uint8_t gpioval);

/**
 * libch9344_gpioget - get gpio input
 * @fd: file descriptor of ch9344 gpio device
 * @gpionumber: gpio number
 * @gpioval: pointer to gpio input value, 1 on high, 0 on low
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_gpioget(int fd, uint8_t gpionumber, uint8_t *gpioval);

/**
 * libch9344_get_gpio_count - get gpio amounts of specific chip model
 * @chiptype: chip model
 *
 * The function returns value larger then 0 if successful, -1 if fails.
 */
extern int libch9344_get_gpio_count(CH9344_CHIPTYPE chiptype);

/**
 * libch9344_get_gpio_group - get gpio groups of specific chip model
 * @chiptype: chip model
 *
 * The function returns value larger then 0 if successful, -1 if fails.
 */
extern int libch9344_get_gpio_group(CH9344_CHIPTYPE chiptype);

/**
 * libch9344_eeprom_read_byte - read one byte from eeprom area
 * @fd: file descriptor of ch9344 tty device
 * @offset: offset address of eeprom
 * @val: pointer to read value
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_eeprom_read_byte(int fd, uint8_t offset,
				      uint8_t *val);

/**
 * libch9344_eeprom_write_byte - write one byte to eeprom area
 * @fd: file descriptor of ch9344 tty device
 * @offset: offset address of eeprom
 * @val: value to write
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_eeprom_write_byte(int fd, uint8_t offset,
				       uint8_t val);

/**
 * libch9344_eeprom_read_area - read bytes from eeprom area
 * @fd: file descriptor of ch9344 tty device
 * @offset: offset address of eeprom
 * @data: pointer to read values
 * @size: read length
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_eeprom_read_area(int fd, uint8_t offset,
				      uint8_t *data, uint8_t size);

/**
 * libch9344_eeprom_write_area - write bytes to eeprom area
 * @fd: file descriptor of ch9344 tty device
 * @offset: offset address of eeprom
 * @data: values to write
 * @size: write length
 *
 * The function returns 0 if successful, others if fails.
 */
extern int libch9344_eeprom_write_area(int fd, uint8_t offset,
				       uint8_t *data, uint8_t size);

#endif
