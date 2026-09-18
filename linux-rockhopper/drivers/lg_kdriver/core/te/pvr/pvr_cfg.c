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
 *  main configuration file for pvr device
 *	pvr device will teach you how to make device driver with new platform.
 *
 *  author		Ilkyu Kim
 *  version		1.0
 *  date		2025-04-04
 *  note		Additional information.
 *
 *  @addtogroup lg1150_pvr
 *	@{
 */

#include "os_util.h"
#include "pvr_impl.h"

static struct pvr_config config_old = {
	.num_dn = 2,
	.num_up = 2,
	.no_pie = 1,
};
static struct pvr_config config_new = {
	.num_dn = 2,
	.num_up = 2,
	.no_pie = 1,
	.use_shared_mem = true,
};

static struct pvr_config *config;

void pvr_cfg_init(void)
{

	switch (lx_chip()) {
#ifdef INCLUDE_M23_CHIP_KDRV
	case LX_CHIP_M23:
	{
		struct te_config *tcfg = te_get_config();

		config = &config_new;
		if (tcfg->no_pvr_download)
			config->no_download_support = true;
		break;
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	case LX_CHIP_O24:
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
	case LX_CHIP_O26:
#endif
	case LX_CHIP_O22:
		config = &config_new;
		break;
	case LX_CHIP_E60:
	case LX_CHIP_O20:
		config = &config_old;
		break;
	default:
		panic("Not supported chip !!! 0x%x\n", lx_chip());
	}
}

struct pvr_config *pvr_get_config(void)
{
	return config;
}

/** @} */
