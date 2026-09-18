/*
 * SoC Center, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  atsc3 device driver
 *
 *  author		Ilkyu Kim
 *  version		1.0
 *  date		2025.04.04
 *  note		Additional information.
 *
 */

#include "os_util.h"
#include "atsc3_impl.h"

static struct atsc3_config config_o20a0 = {
	.num_ch = 4,
	.num_plpf = 8,
	.num_linksignalf = 16,
	.num_ipf = 32,
	.num_udpf = 128,
	.fixup_dumper = true,
};

static struct atsc3_config config_normal = {
	.num_ch = 4,
	.num_plpf = 8,
	.num_linksignalf = 16,
	.num_ipf = 32,
	.num_udpf = 128,
};

static struct atsc3_config *config;

void atsc3_cfg_init(void)
{
	switch (lx_chip()) {
	case LX_CHIP_O20:
		if (lx_chip_rev() >= LX_CHIP_REV(O20, B0))
			config = &config_normal;
		else
			config = &config_o20a0;

		config->use_engine_sel = true;
		break;

	case LX_CHIP_E60:
	case LX_CHIP_O22:
		config = &config_normal;
		config->use_engine_sel = true;
		break;
	default:
		// M23,O24 ~
		config = &config_normal;
		break;
	}
}

struct atsc3_config *atsc3_get_config(void)
{
	return config;
}

/** @} */
