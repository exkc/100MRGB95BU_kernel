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

/** @file machine.c
 *
 *  ALSA module init driver
 *
 *  @author Youngwoo Jin (youngwoo.jin@lge.com)
 *  @version    0.1
 *  @date       2019.12.26
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <sound/soc.h>
#include "os_util.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define _print(fmt,args...) do { printk ("%s.%d: "fmt,__func__,__LINE__,##args); } while(0)
#define trace(fmt,args...)	do { if (log_level >= 6) _print (fmt,##args); } while(0)
#define debug(fmt,args...)	do { if (log_level >= 5) _print (fmt,##args); } while(0)
#define info(fmt,args...)	do { if (log_level >= 4) _print (fmt,##args); } while(0)
#define noti(fmt,args...)	do { if (log_level >= 3) _print (fmt,##args); } while(0)
#define warn(fmt,args...)	do { if (log_level >= 2) _print (fmt,##args); } while(0)
#define error(fmt,args...)	do { if (log_level >= 1) _print (fmt,##args); } while(0)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct dev_info
{
    const char *name;
    const char *driver_name;
    int id;
    struct resource *res;
    int res_num;
    struct platform_device *pdev;
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int __init init_lgsic (void);
static void __exit exit_lgsic (void);

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static struct resource bc_res_sai0[] = {
    /* *INDENT-OFF* */
#if defined (CHIP_NAME_o26)
    DEFINE_RES_MEM_NAMED (0xf2810500, 0x0700, "reg"),
    DEFINE_RES_NAMED (O26_IRQ_AUD_WOVSAI_CPU, 1, "irq", IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE),
#elif defined (CHIP_NAME_o24)
    DEFINE_RES_MEM_NAMED (0xf2810500, 0x0700, "reg"),
    DEFINE_RES_NAMED (O24_IRQ_AUD_WOVSAI_CPU, 1, "irq", IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE),
#elif defined (CHIP_NAME_m23)
    DEFINE_RES_MEM_NAMED (0xf2810500, 0x0700, "reg"),
    DEFINE_RES_NAMED (M23_IRQ_INTR_AUD_WOVSAI_CPU, 1, "irq", IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE),
#elif defined (CHIP_NAME_o22)
    DEFINE_RES_MEM_NAMED (0xf2100500, 0x0700, "reg"),
    DEFINE_RES_NAMED (O22_IRQ_INTR_AUD_WOVSAI_CPU, 1, "irq", IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE),
#else
#error "Please Define Chip Definition"
#endif
    /* *INDENT-ON* */
};

static struct resource pdm0_res[] = {
    /* *INDENT-OFF* */
#if defined (CHIP_NAME_o26)
    DEFINE_RES_MEM_NAMED (0xF2817000, 0x0200, "reg"),
    DEFINE_RES_NAMED (O26_IRQ_AUD_PDM0_CPU, 1, "irq", IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE),
#elif defined (CHIP_NAME_o24)
    DEFINE_RES_MEM_NAMED (0xf2900000, 0x0200, "reg"),
    DEFINE_RES_NAMED (O24_IRQ_AUD_PDM0_CPU, 1, "irq", IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE),
#elif defined (CHIP_NAME_m23)
    DEFINE_RES_MEM_NAMED (0xf2200000, 0x0200, "reg"),
    DEFINE_RES_NAMED (M23_IRQ_INTR_PDM_PDM0_CPU, 1, "irq", IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE),
#elif defined (CHIP_NAME_o22)
    DEFINE_RES_MEM_NAMED (0xf2220000, 0x0200, "reg"),
    DEFINE_RES_NAMED (O22_IRQ_INTR_AUD_PDM0_CPU, 1, "irq", IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE),
#else
#error "Please Define Chip Definition"
#endif
    /* *INDENT-ON* */
};

#ifdef SUPPORT_SOUNDBAR
static struct resource pdm1_res[] = {
    /* *INDENT-OFF* */
#if defined (CHIP_NAME_o26)
    DEFINE_RES_MEM_NAMED (0xF2817200, 0x0200, "reg"),
    DEFINE_RES_NAMED (O26_IRQ_AUD_PDM1_CPU, 1, "irq", IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE),
#else
#error "Please Define Chip Definition"
#endif
    /* *INDENT-ON* */
};
#endif

static struct dev_info devs[] = {
    /* *INDENT-OFF* */
    { .name = "lgsic-bc-sai0", .driver_name = "lgsic-bc",   .id = -1, .res = bc_res_sai0, .res_num = ARRAY_SIZE (bc_res_sai0), },
    { .name = "lgsic-pdm0",    .driver_name = "lgsic-pdm",  .id = -1, .res = pdm0_res,    .res_num = ARRAY_SIZE (pdm0_res), },
#ifdef SUPPORT_SOUNDBAR
    { .name = "lgsic-pdm1",    .driver_name = "lgsic-pdm",  .id = -1, .res = pdm1_res,    .res_num = ARRAY_SIZE (pdm1_res), },
#endif
    { .name = "lgsic-mc",      .driver_name = "lgsic-mc",   .id = -1, },
    { .name = "lgsic-audio",   .id = -1,},
    /* *INDENT-ON* */
};

static int log_level = 4;
module_param (log_level, int, 0644);

/*==============================================================================
    Implementation Group
==============================================================================*/

static int __init init_lgsic (void)
{
    int ret = 0;
    int i;

    extern bool audio_disable;

    if (audio_disable)
    {
        // do not initialize audio
        noti ("do not initialize audio\n");
        return 0;
    }

    for (i = 0; i < ARRAY_SIZE (devs); i++)
    {
        struct dev_info *d = devs + i;

        d->pdev = platform_device_alloc (d->name, d->id);
        if (!d->pdev)
        {
            error ("no mem\n");
            ret = -ENOMEM;
            break;
        }

        d->pdev->driver_override = kstrdup (d->driver_name, GFP_KERNEL);

        if (d->res)
        {
            ret = platform_device_add_resources (d->pdev, d->res, d->res_num);
            if (ret < 0)
            {
                error ("cannot add resource.\n");
                break;
            }
        }

        ret = platform_device_add (d->pdev);
        if (ret)
        {
            error ("cannot add device. %s\n", d->name);
            break;
        }
    }

    return ret;
}

static void __exit exit_lgsic (void)
{
    int i;

    for (i = 0; i < ARRAY_SIZE (devs); i++)
    {
        struct dev_info *d = devs + i;

        info ("unregister %s..\n", d->name);
        platform_device_unregister (d->pdev);
    }
}

module_init (init_lgsic);
module_exit (exit_lgsic);

MODULE_AUTHOR ("LGE");
MODULE_DESCRIPTION ("LG SIC codec driver");
MODULE_LICENSE ("GPL");
