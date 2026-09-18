/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 1998-2013 by LG Electronics Inc.

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
 *  main configuration file for mjpeg device
 *	mjpeg device will teach you how to make device driver with new platform.
 *
 *  author		youngwoo.jin (youngwoo.jin@lge.com)
 *  version		1.0
 *  date		2011.04.09
 *  note		Additional information.
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

/*-----------------------------------------------------------------------------
        Control Constants
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        File Inclusions
-----------------------------------------------------------------------------*/
#include "mjpeg_cfg.h"
#include "base_types.h"
#include "mjpeg_drv.h"
#include "mjpeg_kapi.h"
#include "os_util.h"

/*-----------------------------------------------------------------------------
        Constant Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Macro Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Type Definitions
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 chip;
	LX_MJPEG_CFG_T cfg;
	LX_MJPEG_DEF_T def;
} MJPEG_CFG_TBL_T;

/*-----------------------------------------------------------------------------
        External Function Prototype Declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        External Variables
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        global Variables
-----------------------------------------------------------------------------*/
#define O18_JPEG_BASE 0xC9850000

MJPEG_MEM_CFG_T gMemCfgMjpeg = {
	.pcMemory_name = "mjpeg_buffer",
	.ui32Memory_base = 0x00000000,
	.ui32Memory_size = 0x00200000 /* 2Mb */
	//.ui32Memory_size = 0x00100000 /* 1Mb */
};

/** JPG H/W decoder configuration
 *
 */
static MJPEG_CFG_TBL_T g_mjpeg_cfg_table[] = {
#ifdef INCLUDE_O18_CHIP_KDRV
	{ .chip = LX_CHIP_REV(O18, A0),
	  .cfg = { .max_decode_width = 32 << 10,
			   .max_decode_height = 32 << 10,
			   .decode_caps = LX_MJPEG_DECODE_CAPS_LG,
			   .encode_caps = LX_MJPEG_ENCODE_CAPS_SW },
	  .def = { .jpeg_reg_base = O18_JPEG_BASE,
			   .icod_reg_base = O18_JPEG_BASE,
			   .irq_num = O18_IRQ_INTR_ICOD0,
			   .num_device = 1 } },
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	{ .chip = LX_CHIP_REV(M19, A0),
	  .cfg = { .max_decode_width = 32 << 10,
			   .max_decode_height = 32 << 10,
			   .decode_caps = LX_MJPEG_DECODE_CAPS_LG,
			   .encode_caps = LX_MJPEG_ENCODE_CAPS_SW },
	  .def = { .jpeg_reg_base = M19_ICOD_IP_TOP_BASE,
			   .icod_reg_base = M19_ICOD_IP_TOP_BASE,
			   .irq_num = M19_IRQ_INTR_ICOD,
			   .num_device = 1 } },
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	{ .chip = LX_CHIP_REV(O20, A0),
	  .cfg = { .max_decode_width = 32 << 10,
			   .max_decode_height = 32 << 10,
			   .decode_caps = LX_MJPEG_DECODE_CAPS_LG,
			   .encode_caps = LX_MJPEG_ENCODE_CAPS_SW },
	  .def = { .jpeg_reg_base = O20_ICOD_IP_TOP_BASE,
			   .icod_reg_base = O20_ICOD_IP_TOP_BASE,
			   .irq_num = O20_IRQ_INTR_ICOD,
			   .num_device = 1 } },
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	{ .chip = LX_CHIP_REV(E60, A0),
	  .cfg = { .max_decode_width = 32 << 10,
			   .max_decode_height = 32 << 10,
			   .decode_caps = LX_MJPEG_DECODE_CAPS_LG,
			   .encode_caps = LX_MJPEG_ENCODE_CAPS_SW },
	  .def = { .jpeg_reg_base = E60_ICOD_IP_TOP_BASE,
			   .icod_reg_base = E60_ICOD_IP_TOP_BASE,
			   .irq_num = E60_IRQ_INTR_ICODJPEG,
			   .num_device = 1 } },
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
#ifndef O22_ICOD_IP_TOP_BASE
#define O22_ICOD_IP_TOP_BASE (0xF30B0000)
#endif
#ifndef O22_IRQ_INTR_ICODJPEG
#define O22_IRQ_INTR_ICODJPEG (32 + 79)
#endif
	{ .chip = LX_CHIP_REV(O22, A0),
	  .cfg = { .max_decode_width = 32 << 10,
			   .max_decode_height = 32 << 10,
			   .decode_caps = LX_MJPEG_DECODE_CAPS_LG,
			   .encode_caps = LX_MJPEG_ENCODE_CAPS_SW },
	  .def = { .jpeg_reg_base = O22_ICOD_IP_TOP_BASE,
			   .icod_reg_base = O22_ICOD_IP_TOP_BASE,
			   .irq_num = O22_IRQ_INTR_ICODJPEG,
			   .num_device = 1 } },
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	{ .chip = LX_CHIP_REV(M23, A0),
	  .cfg = { .max_decode_width = 32 << 10,
			   .max_decode_height = 32 << 10,
			   .decode_caps = LX_MJPEG_DECODE_CAPS_LG,
			   .encode_caps = LX_MJPEG_ENCODE_CAPS_SW },
	  .def = { .jpeg_reg_base = M23_ICOD_IP_TOP_BASE,
			   .icod_reg_base = M23_ICOD_IP_TOP_BASE,
			   .irq_num = M23_IRQ_INTR_ICOD_JPEG_CPU,
			   .num_device = 1 } },
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
#ifndef O24_ICOD_IP_BASE
#define O24_ICOD_IP_BASE (0xCE850000)
#endif
#ifndef O24_IRQ_ICOD_JPEG_CPU
#define O24_IRQ_ICOD_JPEG_CPU (32 + 133)
#endif
	{ .chip = LX_CHIP_REV(O24, A0),
	  .cfg = { .max_decode_width = 32 << 10,
			   .max_decode_height = 32 << 10,
			   .decode_caps = LX_MJPEG_DECODE_CAPS_LG,
			   .encode_caps = LX_MJPEG_ENCODE_CAPS_SW },
	  .def = { .jpeg_reg_base = O24_ICOD_IP_BASE,
			   .icod_reg_base = O24_ICOD_IP_BASE,
			   .irq_num = O24_IRQ_ICOD_JPEG_CPU,
			   .num_device = 1 } },
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
#ifndef O26_ICOD_IP_BASE
#define O26_ICOD_IP_BASE (0xCE450000)
#endif
	{ .chip = LX_CHIP_REV(O26, A0),
	  .cfg = { .max_decode_width = 32 << 10,
			   .max_decode_height = 32 << 10,
			   .decode_caps = LX_MJPEG_DECODE_CAPS_LG,
			   .encode_caps = LX_MJPEG_ENCODE_CAPS_SW },
	  .def = { .jpeg_reg_base = O26_ICOD_IP_BASE,
			   .icod_reg_base = O26_ICOD_IP_BASE,
			   .irq_num = O26_IRQ_ICOD_JPEG_CPU,
			   .num_device = 1 } },
#endif
};

/*-----------------------------------------------------------------------------
        Static Function Prototypes Declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Static Variables
-----------------------------------------------------------------------------*/

/*========================================================================================
        Implementation Group
========================================================================================*/
LX_MJPEG_CFG_T *MJPEG_GetCfg(void)
{
	int i;
	int num_cfg = NELEMENTS(g_mjpeg_cfg_table);

	UINT32 chip_rev = lx_chip_rev();

	for (i = num_cfg; i > 0; i--) {
		if (chip_rev >= g_mjpeg_cfg_table[i - 1].chip) {
			return &(g_mjpeg_cfg_table[i - 1].cfg);
		}
	}

	return NULL;
}

LX_MJPEG_DEF_T *MJPEG_GetDef(void)
{
	// int ret = RET_ERROR;
	int i;
	unsigned int chip_rev = lx_chip_rev();
	MJPEG_CFG_TBL_T *pConfig = NULL;

	int shift = 0;

	while (1) {
		chip_rev = lx_chip_rev() >> shift;
		// printk("chip_rev : 0x%X\n", chip_rev);

		for (i = 0; i < NELEMENTS(g_mjpeg_cfg_table); i++) {
			// printk("g_mjpeg_cfg_table chip_rev : 0x%X\n", g_mjpeg_cfg_table[i].chip
			// >> shift);

			if (shift == 0) {
				if (chip_rev == g_mjpeg_cfg_table[i].chip) {
					pConfig = &g_mjpeg_cfg_table[i];
					break;
				}
			} else {
				if (chip_rev == g_mjpeg_cfg_table[i].chip >> shift) {
					pConfig = &g_mjpeg_cfg_table[i];
					break;
				} else if (chip_rev < g_mjpeg_cfg_table[i].chip >> shift) {
					pConfig = &g_mjpeg_cfg_table[i - 1];
					break;
				}
			}
		}

		if (pConfig != NULL)
			break;

		shift += 4;
		if (shift > 8) {
			break;
		}
	}

	if (pConfig != NULL) {
		MJPEG_NOTI("matched chip rev 0x%0X to 0x%X\n", lx_chip_rev(),
				   pConfig->chip);
		// pMJPEGDef->platform = lx_chip_plt();
		// pMJPEGDef->devno = MKDEV(MJPEG_MAJOR, MJPEG_MINOR);

		return &pConfig->def;
	} else {
		// Default(H13)
		MJPEG_NOTI("Default(M16)\n");
		return &g_mjpeg_cfg_table[7].def;
	}
}

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory
 * size adjustment
 *  @note it's natural to keep this function blank :)
 */
void MJPEG_PreInit(void)
{
	gMemCfgMjpeg.ui32Memory_size = 2 << 20;
}

/** @} */
