/*
 * ch342/ch344/ch347/ch9101/ch9102/ch9103/ch9104 parameter configuration application
 *
 * Copyright (C) 2024 Nanjing Qinheng Microelectronics Co., Ltd.
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
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ch343_lib.h"
#include "ch9344_lib.h"
#include "ch34x_parse_cfg.h"

static char device[64];
static char profile[64];

int main(int argc, char *argv[])
{
	int ret;
	char c;
	CH34X *ch34x;

	if (argc == 3) {
		memset(device, 0x00, sizeof(device));
		memcpy(device, argv[1], strlen(argv[1]));
		memset(profile, 0x00, sizeof(profile));
		memcpy(profile, argv[2], strlen(argv[2]));
	} else {
		printf("Usage: ./sercfg [device path] [config file path]\n");
		printf("Exp1: ./sercfg /dev/ch343_iodev0 CONFIG.INI\n");
		printf("Exp2: ./sercfg /dev/ttyCH343USB0 CONFIG.INI\n");
		printf("Exp3: ./sercfg /dev/ttyCH9344USB0 CONFIG.INI\n");
		exit(0);
	}

	ch34x = ch34x_cfg_alloc(device);
	if (!ch34x) {
		printf("ch34x_cfg_alloc error\n");
		exit(1);
	}

	ret = ch34x_cfg_init(ch34x);
	if (ret < 0) {
		printf("ch34x_cfg_init error. ret:%d\n", ret);
		goto exit;
	}

	ret = ch34x_cfg_get(ch34x);
	if (ret < 0) {
		printf("ch34x_cfg_get error. Error code:%d\n", ret);
		goto exit;
	}

	while (1) {
		if (c != '\n')
			printf("\npress g to get usb config, s to set usb config, r to set default config, q to quit this app.\n");

		scanf("%c", &c);
		if (c == 'q')
			break;
		switch (c) {
		case 'g':
			ret = ch34x_cfg_get(ch34x);
			if (ret < 0) {
				printf("ch34x_cfg_get error. Error code:%d\n", ret);
				if (ret == -ERROR_CODE7)
					printf("The chip configuration is not activated and needs to be written.\n");
				goto exit;
			}
			ret = ch34x_cfg_show(ch34x);
			if (ret < 0) {
				printf("ch34x_cfg_show error. Error code:%d\n", ret);
				goto exit;
			}
			break;
		case 's':
			ret = ch34x_update_cfg(ch34x, profile);
			if (ret < 0) {
				printf("ch34x_update_cfg error. Error code:%d\n", ret);
				goto exit;
			}
			break;
		case 'r':
			printf("Writing the default configuration...\n");
			ret = ch34x_defaultCfg_update(ch34x);
			if (ret < 0) {
				printf("ch34x_defaultCfg_update error. Error code:%d\n", ret);
				goto exit;
			}
			printf("The default configuration is successfully written!\n");
		default:
			break;
		}
	}

exit:
	ret = ch34x_cfg_free(ch34x);
	if (ret < 0)
		printf("ch34x_cfg_free error. ret:%d\n", ret);

	exit(0);
}
