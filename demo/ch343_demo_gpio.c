/*
 * ch342/ch344/ch347/ch9101/ch9102/ch9103/ch9104 gpio application example
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
 * V1.3 - add support of ch347
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "ch343_lib.h"

CHIPTYPE chiptype;
int gpiocount;
uint32_t gpioenable, gpiodir, gpioval;

int ch343_gpioinfo(int fd)
{
    int ret;
    int i, bit;

    ret = libch343_get_chiptype(fd, &chiptype);
    if (ret) {
        return ret;
    }

    gpiocount = libch343_get_gpio_count(chiptype);
    if (gpiocount <= 0) {
        printf("get gpio count error.\n");
        goto exit;
    }
    printf("current chip has %d gpios.\n", gpiocount);

    ret = libch343_gpioinfo(fd, &gpioenable, &gpiodir, &gpioval);
    if (ret) {
        printf("get gpio information error.\n");
        goto exit;
    }

    printf("\n********** GPIO Status Dump **********\n");
    printf("\nGPIO Number\t");
    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        printf("---%d", bit);
    }
    printf("\nGPIO Enable\t");
    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        if (i > 9)
            printf("----%c", (gpioenable & (1 << bit)) ? 'Y' : 'N');
        else
            printf("---%c", (gpioenable & (1 << bit)) ? 'Y' : 'N');
    }
    printf("\nGPIO DirBit\t");
    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        if (i > 9)
            printf("----%c", (gpiodir & (1 << bit)) ? 'O' : 'I');
        else
            printf("---%c", (gpiodir & (1 << bit)) ? 'O' : 'I');
    }

    printf("\nGPIO ValBit\t");
    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        if (i > 9)
            printf("----%c", (gpioval & (1 << bit)) ? 'H' : 'L');
        else
            printf("---%c", (gpioval & (1 << bit)) ? 'H' : 'L');
    }
    printf("\n");
    printf("\n********** GPIO Status End **********\n\n");

exit:
    return ret;
}

void ch343_gpio_out_test(int fd)
{
    int ret;
    int i, j, bit;
    uint32_t lgpioenable = 0x00, lgpiodir = 0x00, lgpioval = 0x00;
    uint32_t lgpiobits = 0x00, lgpiolevelbits = 0x00;

    /* set all gpios to input first */
    ret = libch343_gpioenable(fd, lgpioenable, lgpiodir);
    if (ret) {
        printf("libch343_gpioenable error.\n");
        return;
    }

    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        lgpioenable |= 1 << bit;
        lgpiodir |= 1 << bit;
    }

    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        lgpiobits |= 1 << bit;
    }

    ret = libch343_gpioenable(fd, lgpioenable, lgpiodir);
    if (ret) {
        printf("libch343_gpioenable error.\n");
        return;
    }

    /* analog leds here */
    libch343_gpioset(fd, lgpiobits, 0x00);

    printf("\n********** GPIO Output Start **********\n");
    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        lgpiolevelbits = 1 << bit;
        ret = libch343_gpioset(fd, lgpiobits, lgpiolevelbits);
        if (ret) {
            printf("libch343_gpioset error.\n");
            return;
        }
        printf("\n");
        for (j = 0; j < gpiocount; j++) {
            if (j == i)
                printf("H");
            else
                printf("L");
        }
        printf("\n");
        usleep(200 * 1000);
    }
    libch343_gpioset(fd, lgpiobits, 0x00);
    printf("\n********** GPIO Output End **********\n\n");
}

void ch343_gpio_in_test(int fd)
{
    int ret;
    int i, bit;
    uint32_t lgpioenable = 0x00, lgpiodir = 0x00, lgpioval = 0x00;

    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        lgpioenable |= 1 << bit;
    }
    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        lgpiodir &= ~(1 << bit);
    }
    ret = libch343_gpioenable(fd, lgpioenable, lgpiodir);
    if (ret) {
        printf("libch343_gpioenable error.\n");
        return;
    }
    ret = libch343_gpioget(fd, &lgpioval);
    if (ret) {
        printf("libch343_gpioget error.\n");
        return;
    }

    printf("\n********** GPIO Input Status **********\n");
    printf("\nGPIO Number\t");
    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        printf("---%d", bit);
    }
    printf("\nGPIO ValBit\t");

    for (i = 0; i < gpiocount; i++) {
        if ((chiptype == CHIP_CH9102X) && (i >= 4))
            bit = i + 1;
        else if ((chiptype == CHIP_CH9101UH) && (i >= 5))
            bit = i + 1;
        else
            bit = i;
        if (i > 9)
            printf("----%c", (lgpioval & (1 << bit)) ? 'H' : 'L');
        else
            printf("---%c", (lgpioval & (1 << bit)) ? 'H' : 'L');
    }
    printf("\n");
    printf("\n********** GPIO Input End **********\n\n");
}

void ch343_gpiotest(int fd)
{
    char c;

    while (1) {
        if (c != '\n')
            printf(
                "g to get gpio information, press o to test gpio output, "
                "i to get gpio status, q for quit.\n");
        scanf("%c", &c);
        if (c == 'q') break;
        switch (c) {
        case 'g':
            ch343_gpioinfo(fd);
            break;
        case 'o':
            ch343_gpio_out_test(fd);
            break;
        case 'i':
            ch343_gpio_in_test(fd);
            break;
        default:
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    int fd;
    int ret;

	if (argc != 2) {
		printf("Usage: sudo %s [device]\n", argv[0]);
		return -1;
	}

	if (!strstr(argv[1], "iodev")) {
        printf("the gpio device is named ch343_iodev*\n");
        return -1;
    }

    fd = libch343_open(argv[1]);
    if (fd < 0) {
        printf("libch343_open error.\n");
        return fd;
    }

    ret = ch343_gpioinfo(fd);
    if (ret) {
        printf("ch343_gpioinfo error.\n");
        goto exit;
    }

    ch343_gpiotest(fd);

    ret = libch343_close(fd);
    if (ret != 0) {
        printf("libch343_close error.\n");
        goto exit;
    }

exit:
    return ret;
}
