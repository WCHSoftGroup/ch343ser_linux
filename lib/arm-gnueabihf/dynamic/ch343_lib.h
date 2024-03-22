#ifndef _CH343_LIB_H
#define _CH343_LIB_H

#include <stdint.h>

#define IOCTL_MAGIC	       'W'
#define IOCTL_CMD_GETCHIPTYPE  _IOR(IOCTL_MAGIC, 0x84, uint16_t)
#define IOCTL_CMD_GETUARTINDEX _IOR(IOCTL_MAGIC, 0x85, uint16_t)
#define IOCTL_CMD_CTRLIN       _IOWR(IOCTL_MAGIC, 0x90, uint16_t)
#define IOCTL_CMD_CTRLOUT      _IOW(IOCTL_MAGIC, 0x91, uint16_t)

typedef enum {
	CHIP_CH342F = 0x00,
	CHIP_CH342K,
	CHIP_CH343GP,
	CHIP_CH343G_AUTOBAUD,
	CHIP_CH343K,
	CHIP_CH343J,
	CHIP_CH344L,
	CHIP_CH344L_V2,
	CHIP_CH344Q,
	CHIP_CH347TF,
	CHIP_CH9101UH,
	CHIP_CH9101RY,
	CHIP_CH9102F,
	CHIP_CH9102X,
	CHIP_CH9103M,
	CHIP_CH9104L,
	CHIP_CH340B,
	CHIP_CH339W,
} CHIPTYPE;

/**
 * libch343_open - open ch343 device
 * @devname: ch343 tty device or gpio device name, tty device: /dev/tty*, gpio device: /dev/ch343_iodev*
 *
 * In this demo device is opened blocked, you could modify it at will.
 */
extern int libch343_open(const char *devname);

/**
 * libch343_close - close ch343 device
 * @fd: file descriptor of ch343 tty device or gpio device
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_close(int fd);

/**
 * libch343_get_chiptype - get chip model
 * @fd: file descriptor of ch343 tty device or gpio device
 * @type: pointer to chip model
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_get_chiptype(int fd, CHIPTYPE *type);

/**
 * libch343_get_uartindex - get uart index number, 0->UART0, 1->UART1, 2->UART2, 3->UART3
 * @fd: file descriptor of ch343 tty device
 * @index: pointer to uart index
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_get_uartindex(int fd, uint8_t *index);

/**
 * libch343_control_msg_in - control trasfer in
 * @fd: file descriptor of ch343 tty device or gpio device
 * @request: USB message request value
 * @requesttype: USB message request type value
 * @value: USB message value
 * @index: USB message index value
 * @data: pointer to the data to send
 * @size: length in bytes of the data to send
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_control_msg_in(int fd, uint8_t request, uint8_t requesttype, uint16_t value, uint16_t index,
				   uint8_t *data, uint16_t size);
/**
 * libch343_control_msg_out - control trasfer out
 * @fd: file descriptor of ch343 tty device or gpio device
 * @request: USB message request value
 * @requesttype: USB message request type value
 * @value: USB message value
 * @index: USB message index value
 * @data: pointer to the data to send
 * @size: length in bytes of the data to send
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_control_msg_out(int fd, uint8_t request, uint8_t requesttype, uint16_t value, uint16_t index,
				    uint8_t *data, uint16_t size);

/**
 * libch343_gpioinfo - get gpio status
 * @fd: file descriptor of ch343 gpio device
 * @enablebits: pointer to gpio function enable bits, 1 on enable
 * @gpiodirbits: pointer to gpio direction bits, 1 on ouput, 0 on input
 * @gpioval: pointer to gpio input value, bits0-31 on gpio0-31, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_gpioinfo(int fd, uint32_t *enablebits, uint32_t *gpiodirbits, uint32_t *gpioval);

/**
 * libch343_gpioenable - gpio enable
 * @fd: file descriptor of ch343 gpio device
 * @enablebits: gpio function enable bits, 1 on enable
 * @gpiodirbits: gpio direction bits, 1 on ouput, 0 on input
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_gpioenable(int fd, uint32_t enablebits, uint32_t gpiodirbits);

/**
 * libch343_gpioset - gpio output
 * @fd: file descriptor of ch343 gpio device
 * @gpiobits: gpio valid bits, bits0-31 on gpio0-31, 1 on care, 0 on not
 * @gpiolevelbits: gpio output bits, bits0-31 on gpio0-31, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_gpioset(int fd, uint32_t gpiobits, uint32_t gpiolevelbits);

/**
 * libch343_gpioget - get gpio input
 * @fd: file descriptor of ch343 gpio device
 * @gpioval: pointer to gpio input value, bits0-31 on gpio0-31, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_gpioget(int fd, uint32_t *gpioval);

/**
 * libch343_get_gpio_count - get gpio amounts of specific chip model
 * @chiptype: chip model
 *
 * The function return value larger then 0 if success, -1 if fail.
 */
extern int libch343_get_gpio_count(CHIPTYPE chiptype);

/**
 * libch343_eeprom_read_byte - read one byte from eeprom area
 * @fd: file descriptor of ch343 tty device
 * @offset: offset address of eeprom
 * @val: pointer to read value
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_eeprom_read_byte(int fd, uint8_t offset, uint8_t *val);

/**
 * libch343_eeprom_write_byte - write one byte to eeprom area
 * @fd: file descriptor of ch343 tty device
 * @offset: offset address of eeprom
 * @val: value to write
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_eeprom_write_byte(int fd, uint8_t offset, uint8_t val);

/**
 * libch343_eeprom_read_area - read bytes from eeprom area
 * @fd: file descriptor of ch343 tty device
 * @offset: offset address of eeprom
 * @data: pointer to read values
 * @size: read length
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_eeprom_read_area(int fd, uint8_t offset, uint8_t *data, uint8_t size);

/**
 * libch343_eeprom_write_area - write bytes to eeprom area
 * @fd: file descriptor of ch343 tty device
 * @offset: offset address of eeprom
 * @data: values to write
 * @size: write length
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_eeprom_write_area(int fd, uint8_t offset, uint8_t *data, uint8_t size);

#endif
