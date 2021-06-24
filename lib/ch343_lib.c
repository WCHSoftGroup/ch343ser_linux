/* 
 * application library of ch342/ch343/ch344/ch9101/ch9102/ch9103, etc.
 *
 * Copyright (C) 2021 WCH.
 * Author: TECH39 <zhangj@wch.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I /path/to/cross-kernel/include
 *
 * Version: V1.1
 * 
 * Update Log:
 * V1.0 - initial version
 * V1.1 - added support of ch344, ch9103, ch9101
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/ioctl.h>
#include "ch343_lib.h"

/**
 * libch343_open - open tty device
 * @devname: the device name to open
 *
 * In this demo device is opened blocked, you could modify it at will.
 */
int libch343_open(const char *devname)
{
	int fd = open(devname, O_RDWR | O_NOCTTY | O_NDELAY); 
	int flags = 0;
	
	if (fd < 0) {                        
		perror("open device failed");
		return -1;            
	}
	
	flags = fcntl(fd, F_GETFL, 0);
	flags &= ~O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0) {
		printf("fcntl failed.\n");
		return -1;
	}
		
	if (isatty(fd) == 0) {
		printf("not tty device.\n");
		return -1;
	}
	else
		printf("tty device open successfully.\n");
	
	return fd;
}
 
/**
 * libtty_close - close tty device
 * @fd: the device handle
 *
 * The function return 0 if success, others if fail.
 */
int libch343_close(int fd)
{
	return close(fd);
}

/**
 * libch343_gpioinfo - get gpio status
 * @fd: file descriptor of tty device
 * @enablebits: pointer to gpio function enable bits, 1 on enable
 * @gpiodirbits: pointer to gpio direction bits, 1 on ouput, 0 on input
 * @gpioval: pointer to gpio input value, bits0-15 on gpio0-15, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
int libch343_gpioinfo(int fd, uint16_t *enablebits, uint16_t *gpiodirbits, uint16_t *gpioval)
{
	struct {
		uint16_t *enablebits;
		uint16_t *gpiodirbits;
		uint16_t *gpioval;
	} gpioinfo_t;

	gpioinfo_t.enablebits = enablebits;
	gpioinfo_t.gpiodirbits = gpiodirbits;
	gpioinfo_t.gpioval = gpioval;
	
	if (ioctl(fd, IOCTL_CMD_GPIOINFO, &gpioinfo_t) != 0)
		return -1;
	
	return 0;
}

/**
 * libch343_gpioenable - gpio enable
 * @fd: file descriptor of tty device
 * @enablebits: gpio function enable bits, 1 on enable
 * @gpiodirbits: gpio direction bits, 1 on ouput, 0 on input
 *
 * The function return 0 if success, others if fail.
 */
int libch343_gpioenable(int fd, uint16_t enablebits, uint16_t gpiodirbits)
{
	unsigned long val = (enablebits << 16) | gpiodirbits;
	
	return ioctl(fd, IOCTL_CMD_GPIOENABLE, &val);
}

/**
 * libch343_gpioset - gpio output
 * @fd: file descriptor of tty device
 * @gpiobits: gpio valid bits, bits0-15 on gpio0-15, 1 on care, 0 on not
 * @gpiolevelbits: gpio output bits, bits0-15 on gpio0-15, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
int libch343_gpioset(int fd, uint16_t gpiobits, uint16_t gpiolevelbits)
{
	unsigned long val = (gpiobits << 16) | gpiolevelbits;
	
	return ioctl(fd, IOCTL_CMD_GPIOSET, &val);
}

/**
 * libch343_gpioget - get gpio input
 * @fd: file descriptor of tty device
 * @gpioval: pointer to gpio input value, bits0-15 on gpio0-15, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
int libch343_gpioget(int fd, uint16_t *gpioval)
{
	unsigned long val;

	if (ioctl(fd, IOCTL_CMD_GPIOGET, &val) != 0)
		return -1;
	*gpioval = (uint16_t)val;
	
	return 0;
}

/**
 * libch343_get_chiptype - get chip model
 * @fd: file descriptor of tty device
 * @type: pointer to chip model
 *
 * The function return 0 if success, others if fail.
 */
int libch343_get_chiptype(int fd, CHIPTYPE *type)
{
	int ret;
	
	ret = ioctl(fd, IOCTL_CMD_GETCHIPTYPE, type);
	if (ret) {
		printf("get chip type error.\n");
		goto exit;
	}
	switch (*type) {
	case CHIP_CH342F:
		printf("current chip is CH342F.\n");
		break;
	case CHIP_CH342GJK:
		printf("current chip is CH342G/J/K.\n");
		break;
	case CHIP_CH343G:
		printf("current chip is CH343G.\n");
		break;
	case CHIP_CH343G_AUTOBAUD:
		printf("current chip is CH343G(Auto BaudRate Mode).\n");
		break;
	case CHIP_CH343J:
		printf("current chip is CH343J.\n");
		break;
	case CHIP_CH343K:
		printf("current chip is CH343K.\n");
		break;
	case CHIP_CH9102X:
		printf("current chip is CH9102X.\n");
		break;
	case CHIP_CH9102F:
		printf("current chip is CH9102F.\n");
		break;
	case CHIP_CH9103M:
		printf("current chip is CH9103M.\n");
		break;
	case CHIP_CH9101UH:
		printf("current chip is CH9101U/H.\n");
		break;
	default:
		printf("current chip cannot be recognized.\n");
		break;
	}

exit:
	return ret;
}

/**
 * libch343_get_gpio_count - get gpio amounts of specific chip model
 * @chiptype: chip model
 *
 * The function return value larger then 0 if success, -1 if fail.
 */
int libch343_get_gpio_count(CHIPTYPE chiptype)
{
	int ret;
	
	if (chiptype == CHIP_CH9102X)
		ret = 6;
	else if (chiptype == CHIP_CH9102F)
		ret = 5;
	else if (chiptype == CHIP_CH9103M)
		ret = 12;
	else if (chiptype == CHIP_CH9101UH)
		ret = 7;
	else {
		printf("current chip not support gpio function.\n");
		ret = -1;
	}
	return ret;
}