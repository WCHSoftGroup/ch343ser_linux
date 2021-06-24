#ifndef _CH343_LIB_H
#define _CH343_LIB_H

#define IOCTL_MAGIC 'W'
#define IOCTL_CMD_GPIOENABLE 	_IOW(IOCTL_MAGIC, 0x80, uint16_t)
#define IOCTL_CMD_GPIOSET		_IOW(IOCTL_MAGIC, 0x81, uint16_t)
#define IOCTL_CMD_GPIOGET		_IOWR(IOCTL_MAGIC, 0x82, uint16_t)
#define IOCTL_CMD_GPIOINFO		_IOWR(IOCTL_MAGIC, 0x83, uint16_t)
#define IOCTL_CMD_GETCHIPTYPE   _IOR(IOCTL_MAGIC, 0x84, uint16_t)

typedef enum {
	CHIP_CH342F = 0x00,
	CHIP_CH342GJK,
	CHIP_CH343G,
	CHIP_CH343G_AUTOBAUD,
	CHIP_CH343K,
	CHIP_CH343J,
	CHIP_CH344L,
	CHIP_CH9101UH,
	CHIP_CH9102F,
	CHIP_CH9102X,
	CHIP_CH9103M,
} CHIPTYPE;

/**
 * libch343_open - open tty device
 * @devname: the device name to open
 *
 * In this demo device is opened blocked, you could modify it at will.
 */
extern int libch343_open(const char *devname);

/**
 * libch343_close - close tty device
 * @fd: the device handle
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_close(int fd);

/**
 * libch343_gpioinfo - get gpio status
 * @fd: file descriptor of tty device
 * @enablebits: pointer to gpio function enable bits, 1 on enable
 * @gpiodirbits: pointer to gpio direction bits, 1 on ouput, 0 on input
 * @gpioval: pointer to gpio input value, bits0-15 on gpio0-15, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_gpioinfo(int fd, uint16_t *enablebits, uint16_t *gpiodirbits, uint16_t *gpioval);

/**
 * libch343_gpioenable - gpio enable
 * @fd: file descriptor of tty device
 * @enablebits: gpio function enable bits, 1 on enable
 * @gpiodirbits: gpio direction bits, 1 on ouput, 0 on input
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_gpioenable(int fd, uint16_t enablebits, uint16_t gpiodirbits);

/**
 * libch343_gpioset - gpio output
 * @fd: file descriptor of tty device
 * @gpiobits: gpio valid bits, bits0-15 on gpio0-15, 1 on care, 0 on not
 * @gpiolevelbits: gpio output bits, bits0-15 on gpio0-15, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_gpioset(int fd, uint16_t gpiobits, uint16_t gpiolevelbits);

/**
 * libch343_gpioget - get gpio input
 * @fd: file descriptor of tty device
 * @gpioval: pointer to gpio input value, bits0-15 on gpio0-15, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_gpioget(int fd, uint16_t *gpioval);

/**
 * libch343_get_chiptype - get chip model
 * @fd: file descriptor of tty device
 * @type: pointer to chip model
 *
 * The function return 0 if success, others if fail.
 */
extern int libch343_get_chiptype(int fd, CHIPTYPE *type);

/**
 * libch343_get_gpio_count - get gpio amounts of specific chip model
 * @chiptype: chip model
 *
 * The function return value larger then 0 if success, -1 if fail.
 */
extern int libch343_get_gpio_count(CHIPTYPE chiptype);

#endif