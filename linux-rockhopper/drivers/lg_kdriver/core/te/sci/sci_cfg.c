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
 *  author		Juhee Park
 *  author		Yeonju Lee
 *  author		Ilkyu Kim
 *  version		1.0
 *  date		2025.04.04
 *  note		Additional information.
 *
 */

#include "sci_impl.h"
#include "os_util.h"

#define SCI_REG_BASE	(0xfe000000 + 0x700000)
#define SCI_IRQ_NUM	(32+5)

static struct sci_cfg sci_chip_normal = {
	.reg_base_addr = SCI_REG_BASE,
	.hw_irq_num = SCI_IRQ_NUM,
};

static struct sci_cfg *cfg;

struct sci_cfg *sci_get_config(void)
{
	return cfg;
}

void sci_cfg_init(void)
{
	switch (lx_chip()) {
#ifdef INCLUDE_O26_CHIP_KDRV
	case LX_CHIP_O26:
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	case LX_CHIP_O24:
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	case LX_CHIP_M23:
#endif
	case LX_CHIP_E60:
	case LX_CHIP_O22:
		cfg = &sci_chip_normal;
		break;
	default:
		panic("Not supported chip 0x%x\n", lx_chip());
	}
}

