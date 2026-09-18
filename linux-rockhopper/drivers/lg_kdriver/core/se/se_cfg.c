/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 2013 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

/** @file
 *
 *  se memcfg data. this code is included by base_mem_cfg.c.
 *
 *	NOTE :	TZFW uses fixed address, and SE also uses fixed address.
 *			size of TZFW is 1MBytes, and other 7MBytes are marked by TZ-ASC for Secure Memory for SE.
 *	NOTE :	size of TZFW is 2MBytes after M16P
 */
#include <linux/kernel.h>
#include <linux/module.h>

#include "se_drv_impl.h"

LX_MEMCFG_T gMemCfgSE[] =
{
	//E60, O20, O18K
	{
		.name = "se_mem",
		.base = 0x7d300000,
		.size = 0x01100000,
	},
	//M16P3
	{
		.name = "se_mem",
		.base = 0x7e900000,
		.size = 0x00500000,
	},
	//L18
	{
		.name = "se_mem",
		.base = 0x7fe00000,
		.size = 0x000c0000,
	},
};
EXPORT_SYMBOL(gMemCfgSE);

LX_MEMCFG_T gMemCfgSE_TZFW[] =
{
	//E60, O20, O18K
	{
		.name = "se_tzfw",
		.base = 0x7e400000,
		.size = 0x01c00000,
	},
	//M16P3
	{
		.name = "se_tzfw",
		.base = 0x7ee00000,
		.size = 0x01200000,
	},
	//L18
	{
		.name = "se_tzfw",
		.base = 0x7fec0000,
		.size = 0x00140000,
	},
};
EXPORT_SYMBOL(gMemCfgSE_TZFW);

LX_MEMCFG_T *gpMemCfgSE;
LX_MEMCFG_T *gpMemCfgSE_TZFW;

#ifndef _SE_STANDALONE_

void SE_InitCfg(void)
{
	switch (lx_chip()) {

		case LX_CHIP_M19:
			gpMemCfgSE = &gMemCfgSE[1];
			gpMemCfgSE_TZFW = &gMemCfgSE_TZFW[1];
			break;

		case LX_CHIP_L18:
			gpMemCfgSE = &gMemCfgSE[2];
			gpMemCfgSE_TZFW = &gMemCfgSE_TZFW[2];
			break;

		default:
			gpMemCfgSE = &gMemCfgSE[0];
			gpMemCfgSE_TZFW = &gMemCfgSE_TZFW[0];
			break;
	}
}

#else	// _SE_STANDALONE_

void SE_InitCfg(void)
{
	// Fix STAND ALONE CHIP
	gpMemCfgSE = &gMemCfgSE[0];
	gpMemCfgSE_TZFW = &gMemCfgSE_TZFW[0];
}

#endif	// _SE_STANDALONE_

