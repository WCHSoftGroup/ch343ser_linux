/*
 * application library of ch342/ch343/ch344/ch347/ch9101/ch9102/ch9103/ch9104, etc.
 *
 * Copyright (C) 2023 Nanjing Qinheng Microelectronics Co., Ltd.
 * Web: http://wch.cn
 * Author: WCH <tech@wch.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I /path/to/cross-kernel/include
 *
 * V1.0 - initial version
 * V1.1 - add support of ch344, ch9103, ch9101
 * V1.2 - add support of ch9104
 * V1.3 - add support of control transfer and eeprom operation API
 * V1.4 - add support of ch342f
 */

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "ch343_lib.h"

#define BIT(nr) (1UL << (nr))

#define CMD_C7	0xAA
#define CMD_C8	0xAC
#define CMD_C9	0xAB
#define CMD_C10 0xA9
#define CMD_C11 0xAD
#define CMD_C12 0x54
#define CMD_C13 0x5E

struct gpioinfo {
	int group;
	int pin;
};

struct ch343_gpio {
	int gpiocount;
	struct gpioinfo io[64];
};

struct ch343_gpio ch343_gpios[] = {
	/* CH342F */
	{ 12,
	  { { 1, 1 },
	    { 1, 3 },
	    { 1, 2 },
	    { 1, 5 },
	    { 1, 0 },
	    { 1, 6 },
	    { 2, 1 },
	    { 2, 3 },
	    { 2, 2 },
	    { 2, 5 },
	    { 2, 0 },
	    { 2, 6 } } },
	{ 0, {} },
	{ 0, {} },
	{ 0, {} },
	{ 0, {} },
	{ 0, {} },
	/* CH344L */
	{ 12, {} },
	/* CH344L-V2 */
	{ 12, {} },
	/* CH344Q */
	{ 16, {} },
	/* CH347TF */
	{ 8, {} },
	/* CH9101UH */
	{ 6, { { 3, 2 }, { 3, 3 }, { 1, 3 }, { 1, 2 }, { 1, 5 }, { 2, 4 } } },
	/* CH9101RY */
	{ 4, { { 1, 3 }, { 3, 3 }, { 3, 2 }, { 2, 4 } } },
	/* CH9102F */
	{ 5, { { 2, 1 }, { 2, 7 }, { 2, 4 }, { 2, 6 }, { 2, 3 } } },
	/* CH9102X */
	{ 6, { { 2, 3 }, { 2, 5 }, { 2, 1 }, { 2, 7 }, { 3, 0 }, { 2, 2 } } },
	/* CH9103M */
	{ 12,
	  { { 1, 3 },
	    { 1, 2 },
	    { 3, 2 },
	    { 2, 6 },
	    { 1, 0 },
	    { 1, 6 },
	    { 2, 3 },
	    { 2, 5 },
	    { 3, 0 },
	    { 2, 2 },
	    { 1, 5 },
	    { 2, 4 } } },
	/* CH9104L */
	{ 24, {} },
};

/**
 * libch343_open - open ch343 device
 * @devname: ch343 tty device or gpio device name, tty device: /dev/tty*, gpio device: /dev/ch343_iodev*
 *
 * In this demo device is opened blocked, you could modify it at will.
 */
int libch343_open(const char *devname)
{
	int fd;
	int flags;

	if (strstr(devname, "tty")) {
		fd = open(devname, O_RDWR | O_NOCTTY | O_NDELAY);
		if (fd < 0) {
			printf("open tty device failed.\n");
			return fd;
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
	} else {
		fd = open(devname, O_RDWR);
	}

	return fd;
}

/**
 * libch343_close - close ch343 device
 * @fd: file descriptor of ch343 tty device or gpio device
 *
 * The function return 0 if success, others if fail.
 */
int libch343_close(int fd)
{
	return close(fd);
}

/**
 * libch343_get_chiptype - get chip model
 * @fd: file descriptor of ch343 tty device or gpio device
 * @type: pointer to chip model
 *
 * The function return 0 if success, others if fail.
 */
int libch343_get_chiptype(int fd, CHIPTYPE *type)
{
	return ioctl(fd, IOCTL_CMD_GETCHIPTYPE, type);
}

/**
 * libch343_get_uartindex - get uart index number, 0->UART0, 1->UART1, 2->UART2, 3->UART3
 * @fd: file descriptor of ch343 tty device
 * @index: pointer to uart index
 *
 * The function return 0 if success, others if fail.
 */
int libch343_get_uartindex(int fd, uint8_t *index)
{
	return ioctl(fd, IOCTL_CMD_GETUARTINDEX, index);
}

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
int libch343_control_msg_in(int fd, uint8_t request, uint8_t requesttype, uint16_t value, uint16_t index, uint8_t *data,
			    uint16_t size)
{
	struct _controlmsg {
		uint8_t request;
		uint8_t requesttype;
		uint16_t value;
		uint16_t index;
		uint16_t size;
		uint8_t data[0];
	} __attribute__((packed));

	int ret;
	struct _controlmsg *controlmsg;

	controlmsg = malloc(sizeof(struct _controlmsg) + size);

	controlmsg->request = request;
	controlmsg->requesttype = requesttype;
	controlmsg->value = value;
	controlmsg->index = index;
	controlmsg->size = size;

	ret = ioctl(fd, IOCTL_CMD_CTRLIN, (unsigned long)controlmsg);
	if (ret < 0) {
		goto exit;
	}

	memcpy(data, controlmsg->data, ret);

exit:
	free(controlmsg);
	return ret;
}

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
int libch343_control_msg_out(int fd, uint8_t request, uint8_t requesttype, uint16_t value, uint16_t index,
			     uint8_t *data, uint16_t size)
{
	struct _controlmsg {
		uint8_t request;
		uint8_t requesttype;
		uint16_t value;
		uint16_t index;
		uint16_t size;
		uint8_t data[0];
	} __attribute__((packed));

	int ret;
	struct _controlmsg *controlmsg;

	controlmsg = malloc(sizeof(struct _controlmsg) + size);

	controlmsg->request = request;
	controlmsg->requesttype = requesttype;
	controlmsg->value = value;
	controlmsg->index = index;
	controlmsg->size = size;
	memcpy(controlmsg->data, data, size);

	ret = ioctl(fd, IOCTL_CMD_CTRLOUT, (unsigned long)controlmsg);

	free(controlmsg);
	return ret;
}

/**
 * libch343_gpioinfo - get gpio status
 * @fd: file descriptor of ch343 gpio device
 * @enablebits: pointer to gpio function enable bits, 1 on enable
 * @gpiodirbits: pointer to gpio direction bits, 1 on ouput, 0 on input
 * @gpioval: pointer to gpio input value, bits0-31 on gpio0-31, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
int libch343_gpioinfo(int fd, uint32_t *enablebits, uint32_t *gpiodirbits, uint32_t *gpioval)
{
	int ret;
	int i;
	CHIPTYPE chiptype;
	char buffer[8];

	uint8_t gen[5], gd[5], gv[5];
	uint8_t group, pin;
	uint8_t biti;

	uint32_t gev, gdv, gvv;

	ret = libch343_get_chiptype(fd, &chiptype);
	if (ret) {
		goto out;
	}

	if (chiptype == CHIP_CH9104L) {
		for (i = 0; i < 4; i++) {
			ret = libch343_control_msg_in(fd, CMD_C11, 0xC0, i, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gen[i + 1] = buffer[1];
			gd[i + 1] = buffer[3];
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, i, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gv[i + 1] = buffer[3];
		}
	} else {
		ret = libch343_control_msg_in(fd, CMD_C11, 0xC0, 0x00, 0x00, buffer, 0x04);
		if (ret < 0x03)
			goto out;

		gen[1] = buffer[0];
		gen[2] = buffer[1];
		gen[3] = buffer[2];

		if ((chiptype == CHIP_CH344L) || (chiptype == CHIP_CH344Q) || (chiptype == CHIP_CH344L_V2) ||
		    (chiptype == CHIP_CH347TF)) {
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, 0x00, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gd[1] = buffer[0];
			gd[2] = buffer[1];
			gv[1] = buffer[2];
			gv[2] = buffer[3];
		} else {
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, 0x00, 0x00, buffer, 0x08);
			if (ret < 0x06)
				goto out;
			gd[1] = buffer[0];
			gd[2] = buffer[1];
			gd[3] = buffer[2];
			gv[1] = buffer[3];
			gv[2] = buffer[4];
			gv[3] = buffer[5];
		}
	}

	gev = gdv = gvv = 0x00;

	if (chiptype == CHIP_CH9104L) {
		gev = gen[1] & 0x3F;
		gev |= (gen[2] & 0x3F) << 6;
		gev |= (gen[3] & 0x3F) << 12;
		gev |= (gen[4] & 0x3F) << 18;
		gdv = gd[1] & 0x3F;
		gdv |= (gd[2] & 0x3F) << 6;
		gdv |= (gd[3] & 0x3F) << 12;
		gdv |= (gd[4] & 0x3F) << 18;
		gvv = gv[1] & 0x3F;
		gvv |= (gv[2] & 0x3F) << 6;
		gvv |= (gv[3] & 0x3F) << 12;
		gvv |= (gv[4] & 0x3F) << 18;
	} else if ((chiptype == CHIP_CH344L) || (chiptype == CHIP_CH344Q) || (chiptype == CHIP_CH344L_V2) ||
		   (chiptype == CHIP_CH347TF)) {
		gev |= gen[1] << 8;
		gev |= gen[2];
		gdv |= gd[1] << 8;
		gdv |= gd[2];
		gvv |= gv[1] << 8;
		gvv |= gv[2];
	} else {
		for (i = 0; i < ch343_gpios[chiptype].gpiocount; i++) {
			group = ch343_gpios[chiptype].io[i].group;
			pin = ch343_gpios[chiptype].io[i].pin;
			if ((chiptype == CHIP_CH9102X) && (i > 3))
				biti = i + 1;
			else if ((chiptype == CHIP_CH9101UH) && (i > 4))
				biti = i + 1;
			else
				biti = i;

			if (gen[group] & BIT(pin))
				gev |= BIT(biti);
			if (gd[group] & BIT(pin))
				gdv |= BIT(biti);
			if (gv[group] & BIT(pin))
				gvv |= BIT(biti);
		}
	}
	*enablebits = gev;
	*gpiodirbits = gdv;
	*gpioval = gvv;

	return 0;

out:
	return ret;
}

/**
 * libch343_gpioenable - gpio enable
 * @fd: file descriptor of ch343 gpio device
 * @enablebits: gpio function enable bits, 1 on enable
 * @gpiodirbits: gpio direction bits, 1 on ouput, 0 on input
 *
 * The function return 0 if success, others if fail.
 */
int libch343_gpioenable(int fd, uint32_t enablebits, uint32_t gpiodirbits)
{
	int ret;
	int i, j;
	CHIPTYPE chiptype;
	char buffer[8];

	uint8_t gen[5], gd[5], gv[5];
	uint8_t group, pin;
	uint8_t biti;

	uint32_t gev, gdv, gvv;
	uint16_t value, index;

	ret = libch343_get_chiptype(fd, &chiptype);
	if (ret) {
		goto out;
	}

	if (chiptype == CHIP_CH9104L) {
		for (i = 0; i < 4; i++) {
			ret = libch343_control_msg_in(fd, CMD_C11, 0xC0, i, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gen[i + 1] = buffer[1];
			gd[i + 1] = buffer[3];
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, i, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gv[i + 1] = buffer[3];
		}
	} else {
		ret = libch343_control_msg_in(fd, CMD_C11, 0xC0, 0x00, 0x00, buffer, 0x04);
		if (ret < 0x03)
			goto out;

		gen[1] = buffer[0];
		gen[2] = buffer[1];
		gen[3] = buffer[2];

		if ((chiptype == CHIP_CH344L) || (chiptype == CHIP_CH344Q) || (chiptype == CHIP_CH344L_V2) ||
		    (chiptype == CHIP_CH347TF)) {
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, 0x00, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gd[1] = buffer[0];
			gd[2] = buffer[1];
			gv[1] = buffer[2];
			gv[2] = buffer[3];
		} else {
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, 0x00, 0x00, buffer, 0x08);
			if (ret < 0x06)
				goto out;
			gd[1] = buffer[0];
			gd[2] = buffer[1];
			gd[3] = buffer[2];
			gv[1] = buffer[3];
			gv[2] = buffer[4];
			gv[3] = buffer[5];
		}
	}

	if (chiptype == CHIP_CH9104L) {
		for (i = 0; i < ch343_gpios[chiptype].gpiocount; i++) {
			j = i / 6 + 1;
			if (enablebits & BIT(i)) {
				gen[j] |= BIT(i % 6);
				if (gpiodirbits & BIT(i))
					gd[j] |= BIT(i % 6);
				else
					gd[j] &= ~BIT(i % 6);
			}
		}
		for (i = 0; i < 4; i++) {
			value = i << 4;
			index = gen[i + 1] + ((uint16_t)gd[i + 1] << 8);
			ret = libch343_control_msg_out(fd, CMD_C7, 0x40, value, index, NULL, 0);
			if (ret < 0)
				goto out;
		}
	} else if ((chiptype == CHIP_CH344L) || (chiptype == CHIP_CH344Q) || (chiptype == CHIP_CH344L_V2) ||
		   (chiptype == CHIP_CH347TF)) {
		for (i = 0; i < ch343_gpios[chiptype].gpiocount; i++) {
			if (enablebits & BIT(i)) {
				gen[2] |= BIT(i);
				if (gpiodirbits & BIT(i))
					gd[2] |= BIT(i);
				else
					gd[2] &= ~BIT(i);
			} else
				gen[2] &= ~BIT(i);
			if (enablebits & BIT(i + 8)) {
				gen[1] |= BIT(i);
				if (gpiodirbits & BIT(i + 8))
					gd[1] |= BIT(i);
				else
					gd[1] &= ~BIT(i);
			} else
				gen[1] &= ~BIT(i);
		}
		value = gen[1] + ((uint16_t)gd[1] << 8);
		index = gen[2] + ((uint16_t)gd[2] << 8);
		ret = libch343_control_msg_out(fd, CMD_C7, 0x40, value, index, NULL, 0);
		if (ret < 0)
			goto out;
	} else {
		for (i = 0; i < ch343_gpios[chiptype].gpiocount; i++) {
			group = ch343_gpios[chiptype].io[i].group;
			pin = ch343_gpios[chiptype].io[i].pin;
			if ((chiptype == CHIP_CH9102X) && (i > 3))
				biti = i + 1;
			else if ((chiptype == CHIP_CH9101UH) && (i > 4))
				biti = i + 1;
			else
				biti = i;

			if (enablebits & BIT(biti)) {
				gen[group] |= BIT(pin);
				if (gpiodirbits & BIT(biti))
					gd[group] |= BIT(pin);
				else
					gd[group] &= ~BIT(pin);
			} else {
				gen[group] &= ~BIT(pin);
			}
		}
		value = gen[1] + ((uint16_t)gd[1] << 8);
		index = gen[2] + ((uint16_t)gd[2] << 8);
		ret = libch343_control_msg_out(fd, CMD_C7, 0x40, value, index, NULL, 0);
		if (ret < 0)
			goto out;

		if (chiptype == CHIP_CH342F)
			goto out;

		value = gd[3] + ((uint16_t)gv[3] << 8);
		index = gen[3];
		ret = libch343_control_msg_out(fd, CMD_C8, 0x40, value, index, NULL, 0);
		if (ret < 0)
			goto out;
	}

	return 0;

out:
	return ret;
}

/**
 * libch343_gpioset - gpio output
 * @fd: file descriptor of ch343 gpio device
 * @gpiobits: gpio valid bits, bits0-31 on gpio0-31, 1 on care, 0 on not
 * @gpiolevelbits: gpio output bits, bits0-31 on gpio0-31, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
int libch343_gpioset(int fd, uint32_t gpiobits, uint32_t gpiolevelbits)
{
	int ret;
	int i, j;
	CHIPTYPE chiptype;
	char buffer[8];

	uint8_t gbit[5];
	uint8_t gopbit1, gopbit2;

	uint8_t gen[5], gd[5], gv[5];
	uint8_t group, pin;
	uint8_t biti;

	uint32_t gev, gdv, gvv;
	uint16_t value, index;

	ret = libch343_get_chiptype(fd, &chiptype);
	if (ret) {
		goto out;
	}

	if (chiptype == CHIP_CH9104L) {
		for (i = 0; i < 4; i++) {
			ret = libch343_control_msg_in(fd, CMD_C11, 0xC0, i, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gen[i + 1] = buffer[1];
			gd[i + 1] = buffer[3];
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, i, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gv[i + 1] = buffer[3];
		}
	} else {
		ret = libch343_control_msg_in(fd, CMD_C11, 0xC0, 0x00, 0x00, buffer, 0x04);
		if (ret < 0x03)
			goto out;

		gen[1] = buffer[0];
		gen[2] = buffer[1];
		gen[3] = buffer[2];

		if ((chiptype == CHIP_CH344L) || (chiptype == CHIP_CH344Q) || (chiptype == CHIP_CH344L_V2) ||
		    (chiptype == CHIP_CH347TF)) {
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, 0x00, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gd[1] = buffer[0];
			gd[2] = buffer[1];
			gv[1] = buffer[2];
			gv[2] = buffer[3];
		} else {
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, 0x00, 0x00, buffer, 0x08);
			if (ret < 0x06)
				goto out;
			gd[1] = buffer[0];
			gd[2] = buffer[1];
			gd[3] = buffer[2];
			gv[1] = buffer[3];
			gv[2] = buffer[4];
			gv[3] = buffer[5];
		}
	}

	gbit[1] = gbit[2] = gbit[3] = gbit[4] = 0x00;
	gopbit1 = gopbit2 = 0x00;

	if (chiptype == CHIP_CH9104L) {
		for (i = 0; i < ch343_gpios[chiptype].gpiocount; i++) {
			j = i / 6 + 1;
			if ((gpiobits & BIT(i)) && (gen[j] & BIT(i % 6)) && (gd[j] & BIT(i % 6))) {
				gbit[j] |= BIT(i % 6);
				if (gpiolevelbits & BIT(i))
					gv[j] |= BIT(i % 6);
				else
					gv[j] &= ~BIT(i % 6);
			}
		}
		for (i = 0; i < 4; i++) {
			value = i << 4;
			index = gbit[i + 1] + ((uint16_t)gv[i + 1] << 8);
			ret = libch343_control_msg_out(fd, CMD_C9, 0x40, value, index, NULL, 0);
			if (ret < 0)
				goto out;
		}
	} else if ((chiptype == CHIP_CH344L) || (chiptype == CHIP_CH344Q) || (chiptype == CHIP_CH344L_V2) ||
		   (chiptype == CHIP_CH347TF)) {
		for (i = 0; i < 8; i++) {
			if ((gpiobits & BIT(i)) && (gen[2] & BIT(i)) && (gd[2] & BIT(i))) {
				gbit[2] |= BIT(i);
				if (gpiolevelbits & BIT(i))
					gv[2] |= BIT(i);
				else
					gv[2] &= ~BIT(i);
			}
			if ((gpiobits & BIT(i + 8)) && (gen[1] & BIT(i)) && (gd[1] & BIT(i))) {
				gbit[1] |= BIT(i);
				if (gpiolevelbits & BIT(i + 8))
					gv[1] |= BIT(i);
				else
					gv[1] &= ~BIT(i);
			}
		}
		value = gbit[1] + ((uint16_t)gv[1] << 8);
		index = gbit[2] + ((uint16_t)gv[2] << 8);
		ret = libch343_control_msg_out(fd, CMD_C9, 0x40, value, index, NULL, 0);
		if (ret < 0)
			goto out;
	} else {
		for (i = 0; i < ch343_gpios[chiptype].gpiocount; i++) {
			group = ch343_gpios[chiptype].io[i].group;
			pin = ch343_gpios[chiptype].io[i].pin;
			if ((chiptype == CHIP_CH9102X) && (i > 3))
				biti = i + 1;
			else if ((chiptype == CHIP_CH9101UH) && (i > 4))
				biti = i + 1;
			else
				biti = i;

			if ((gpiobits & BIT(biti)) && (gen[group] & BIT(pin)) && (gd[group] & BIT(pin))) {
				gbit[group] |= BIT(pin);
				if (gpiolevelbits & BIT(biti))
					gv[group] |= BIT(pin);
				else
					gv[group] &= ~BIT(pin);
			}
		}
		value = gbit[1] + ((uint16_t)gv[1] << 8);
		index = gbit[2] + ((uint16_t)gv[2] << 8);
		ret = libch343_control_msg_out(fd, CMD_C9, 0x40, value, index, NULL, 0);
		if (ret < 0)
			goto out;

		if (chiptype == CHIP_CH342F)
			goto out;

		value = gd[3] + ((uint16_t)gv[3] << 8);
		index = gen[3];
		ret = libch343_control_msg_out(fd, CMD_C8, 0x40, value, index, NULL, 0);
		if (ret < 0)
			goto out;
	}

	return 0;

out:
	return ret;
}

/**
 * libch343_gpioget - get gpio input
 * @fd: file descriptor of ch343 gpio device
 * @gpioval: pointer to gpio input value, bits0-31 on gpio0-31, 1 on high, 0 on low
 *
 * The function return 0 if success, others if fail.
 */
int libch343_gpioget(int fd, uint32_t *gpioval)
{
	int ret;
	int i;
	CHIPTYPE chiptype;
	char buffer[8];

	uint8_t gen[5], gd[5], gv[5];
	uint8_t group, pin;
	uint8_t biti;

	uint32_t gev, gdv, gvv;
	uint16_t value, index;

	ret = libch343_get_chiptype(fd, &chiptype);
	if (ret) {
		goto out;
	}

	gvv = 0;
	if (chiptype == CHIP_CH9104L) {
		for (i = 0; i < 4; i++) {
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, i, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gv[i + 1] = buffer[3];
		}
		gvv = gv[1] & 0x3F;
		gvv |= (gv[2] & 0x3F) << 6;
		gvv |= (gv[3] & 0x3F) << 12;
		gvv |= (gv[4] & 0x3F) << 18;
	} else {
		if ((chiptype == CHIP_CH344L) || (chiptype == CHIP_CH344Q) || (chiptype == CHIP_CH344L_V2) ||
		    (chiptype == CHIP_CH347TF)) {
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, 0x00, 0x00, buffer, 0x04);
			if (ret != 0x04)
				goto out;
			gd[1] = buffer[0];
			gd[2] = buffer[1];
			gv[1] = buffer[2];
			gv[2] = buffer[3];
		} else {
			ret = libch343_control_msg_in(fd, CMD_C10, 0xC0, 0x00, 0x00, buffer, 0x08);
			if (ret < 0x06)
				goto out;
			gd[1] = buffer[0];
			gd[2] = buffer[1];
			gd[3] = buffer[2];
			gv[1] = buffer[3];
			gv[2] = buffer[4];
			gv[3] = buffer[5];
		}
	}

	if ((chiptype == CHIP_CH344L) || (chiptype == CHIP_CH344Q) || (chiptype == CHIP_CH344L_V2) ||
	    (chiptype == CHIP_CH347TF)) {
		gvv |= gv[1] << 8;
		gvv |= gv[2];
	} else {
		for (i = 0; i < ch343_gpios[chiptype].gpiocount; i++) {
			group = ch343_gpios[chiptype].io[i].group;
			pin = ch343_gpios[chiptype].io[i].pin;
			if ((chiptype == CHIP_CH9102X) && (i > 3))
				biti = i + 1;
			else if ((chiptype == CHIP_CH9101UH) && (i > 4))
				biti = i + 1;
			else
				biti = i;

			if (gv[group] & BIT(pin))
				gvv |= BIT(biti);
		}
	}
	*gpioval = gvv;

	return 0;

out:
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

	if (chiptype == CHIP_CH342F)
		ret = 12;
	else if (chiptype == CHIP_CH9102X)
		ret = 6;
	else if (chiptype == CHIP_CH9102F)
		ret = 5;
	else if (chiptype == CHIP_CH9103M)
		ret = 12;
	else if (chiptype == CHIP_CH9101UH)
		ret = 6;
	else if (chiptype == CHIP_CH9101RY)
		ret = 4;
	else if (chiptype == CHIP_CH9101RY)
		ret = 4;
	else if (chiptype == CHIP_CH344L)
		ret = 12;
	else if (chiptype == CHIP_CH344L_V2)
		ret = 12;
	else if (chiptype == CHIP_CH344Q)
		ret = 16;
	else if (chiptype == CHIP_CH347TF)
		ret = 8;
	else if (chiptype == CHIP_CH9104L)
		ret = 24;
	else {
		printf("current chip not support gpio function.\n");
		ret = -1;
	}
	return ret;
}

/**
 * libch343_eeprom_read_byte - read one byte from eeprom area
 * @fd: file descriptor of ch343 tty device
 * @offset: offset address of eeprom
 * @val: pointer to read value
 *
 * The function return 0 if success, others if fail.
 */
int libch343_eeprom_read_byte(int fd, uint8_t offset, uint8_t *val)
{
	int ret;
	uint16_t value, index;
	uint8_t data;

	value = offset << 8;
	index = 0xA001;
	ret = libch343_control_msg_in(fd, CMD_C12, 0xC0, value, index, &data, 0x01);
	if (ret != 0x01) {
		return -1;
	} else
		*val = data;

	return 0;
}

/**
 * libch343_eeprom_write_byte - write one byte to eeprom area
 * @fd: file descriptor of ch343 tty device
 * @offset: offset address of eeprom
 * @val: value to write
 *
 * The function return 0 if success, others if fail.
 */
int libch343_eeprom_write_byte(int fd, uint8_t offset, uint8_t val)
{
	int ret;
	uint16_t value, index;

	value = val | (offset << 8);
	index = 0xA001;
	ret = libch343_control_msg_out(fd, CMD_C12, 0x40, value, index, NULL, 0x00);
	if (ret != 0) {
		goto out;
	}

	value = 0x0A;
	index = 0x00;
	ret = libch343_control_msg_out(fd, CMD_C13, 0x40, value, index, NULL, 0x00);
	if (ret != 0) {
		goto out;
	}

	return 0;

out:
	return ret;
}

/**
 * libch343_eeprom_read_area - read bytes from eeprom area
 * @fd: file descriptor of ch343 tty device
 * @offset: offset address of eeprom
 * @data: pointer to read values
 * @size: read length
 *
 * The function return 0 if success, others if fail.
 */
int libch343_eeprom_read_area(int fd, uint8_t offset, uint8_t *data, uint8_t size)
{
	int ret;
	uint16_t value, index;
	uint8_t *buffer;
	int i;

	buffer = malloc(size);

	index = 0x01A0;
	for (i = 0; i < size; i++) {
		value = ((uint16_t)(offset + i)) << 8;
		ret = libch343_control_msg_in(fd, CMD_C12, 0xC0, value, index, buffer + i, 0x01);
		if (ret != 0x01) {
			goto out;
		}
	}
	memcpy(data, buffer, size);

	return 0;

out:
	free(buffer);
	return ret;
}

/**
 * libch343_eeprom_write_area - write bytes to eeprom area
 * @fd: file descriptor of ch343 tty device
 * @offset: offset address of eeprom
 * @data: values to write
 * @size: write length
 *
 * The function return 0 if success, others if fail.
 */
int libch343_eeprom_write_area(int fd, uint8_t offset, uint8_t *data, uint8_t size)
{
	int ret;
	int i;
	uint16_t value, index;

	for (i = 0; i < size; i++) {
		value = *(data + i) | ((offset + i) << 8);
		index = 0xA001;
		ret = libch343_control_msg_out(fd, CMD_C12, 0x40, value, index, NULL, 0x00);
		if (ret != 0) {
			goto out;
		}

		value = 0x0A;
		index = 0x00;
		ret = libch343_control_msg_out(fd, CMD_C13, 0x40, value, index, NULL, 0x00);
		if (ret != 0) {
			goto out;
		}
	}

	return 0;

out:
	return ret;
}
