/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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
 *  main configuration file for gfx device
 *  gfx device will teach you how to make device driver with new platform.
 *
 *  author      raxis.lim (raxis.lim@lge.com).lim (raxis.lim@lge.com)
 *  version     1.0
 *  date        2009.12.30
 *  note        Additional information.
 *
 *  @addtogroup lg1150_gfx
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "gfx_impl.h"
#include "base_device.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#ifndef GFX_DEV_MEM_SIZE_UHD    /* GFX_DEV_MEM_SIZE_UHD is defined only in H13 platform_mem_map.h */
#define GFX_DEV_MEM_SIZE_UHD    0
#endif

#ifndef GFX_DEV_MEM_SIZE        /* gfx memory size is configured at the platform_init */
#define GFX_DEV_MEM_SIZE        (180<<20)
#endif

#ifndef GFX_DEV_MEM_BASE
#define GFX_DEV_MEM_BASE        0x0
#endif

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
/** GFX memory description table
 *
 *  if base value is zero, base address is dynamicalled assigned by devmem manager ( dynamic address )
 *  if base value is non zero, devmem manager doesn't modify its address ( static address )
 *
 *  @see  GFX_InitCfg
 *  @note memory desc. is very platform dependent.
 */
LX_MEMCFG_T gfx_mem_desc_table[] =
{
    [0] = { .name = "gfx_surf", .base = GFX_DEV_MEM_BASE,   .size = GFX_DEV_MEM_SIZE        },  /* default */
    [1] = { .name = "gfx_surf", .base = 0,                  .size = 0                       },  /* FHD or general  */
};

/** GFX H/W configuratin table
 *
 */
LX_GFX_REG_CFG_T    gfx_reg_cfg_desc_table[] =
{
    [0] = {
        .chip = LX_CHIP_UNKNOWN,
        .chip_name = "gfx-dummy",
        .reg_base_addr = 0xffffffff /*NA*/,
        .reg_size = 0x0,
        .irq_num = (UINT32) - 1
    },

    [1] = {
        .chip = LX_CHIP_L18,
        .chip_name = "gfx-l18f",
        .reg_base_addr = 0xc9810000,
        .reg_size = 0x200,
        .irq_num = (32 + 54),
    },

    [2] = {
        .chip = LX_CHIP_O22,
        .chip_name = "gfx-o22",
        .reg_base_addr = 0xCAA40000,/* refer O22_GFX_IP_TOP_BASE */
        .reg_size = 0x200,
        .irq_num = (32 + 88),       /* refer O22_IRQ_INTR_GFX */
    },

    [3] = {
        .chip = LX_CHIP_M23,
        .chip_name = "gfx-m23",
        .reg_base_addr = 0xC4700000,
        .reg_size = 0x200,
        .irq_num = (32 + 86),       /* refer M23_IRQ_INTR_GFX */
    },

    [4] = {
        .chip = LX_CHIP_O24,
        .chip_name = "gfx-o24",
        .reg_base_addr = 0xC4140000,
        .reg_size = 0x200,
        .irq_num = (32 + 73),       /* refer O24_IRQ_GFX_CPU */
    },

    [5] = {
        .chip = LX_CHIP_O26,
        .chip_name = "gfx-o26",
        .reg_base_addr = 0xC4080000,
        .reg_size = 0x200,
        .irq_num = (32 + 74),       /* refer O26_IRQ_GFX_CPU */
    },
};

LX_GFX_REG_CFG_T*   gpGfxRegCfg = NULL;
LX_GFX_MEM_CFG_T    gMemCfgGfx;

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
    Implementation Group
========================================================================================*/
void    GFX_InitCfg(void)
{
    int i;

    memset(&gMemCfgGfx, 0x0, sizeof(LX_GFX_MEM_CFG_T));              // clear memcfg
    memcpy(&g_gfx_cfg, g_gfx_hal.GetCfg(), sizeof(LX_GFX_CFG_T));    // get chip cfg

    for (i = 0; i < NELEMENTS(gfx_reg_cfg_desc_table); i++)
    {
        if (lx_chip() == gfx_reg_cfg_desc_table[i].chip)
        {
            gpGfxRegCfg = &gfx_reg_cfg_desc_table[i];
            break;
        }
    }

    WARN(!gpGfxRegCfg, "unknown chip(0x%x)\n", lx_chip());

    memcpy(&gMemCfgGfx.surface[0], &gfx_mem_desc_table[0], sizeof(LX_MEMCFG_T));
}

/** @} */

