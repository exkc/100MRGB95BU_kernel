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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.18
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "de_model.h"
#include "de_ver_def.h"
#include "de_def.h"

#include "vsc_print.h"
/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
struct vsc_print_ctx {
    int (*oprint_set_color)(int, int, int);
    int (*oprint_set_size)(int);
    int (*oprint_enable)(int);
    int (*oprint)(const char *, ...);
};

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/
struct vsc_print_ctx _g_vsc_print_ctx;

/*========================================================================================
 *	 Implementation Group
 *=======================================================================================*/
int vsc_print_init(void)
{
    struct vsc_print_ctx *p = &_g_vsc_print_ctx;

    memset(&_g_vsc_print_ctx,0,sizeof(_g_vsc_print_ctx));

    if (0) { }
#ifdef INCLUDE_O26_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O26) {
        extern int de_dosd_o26_set_color(int r, int g, int b);
        extern int de_dosd_o26_set_size(int big);
        extern int de_dosd_o26_enable(int onoff);
        extern int de_dosd_o26_print(const char *fmt, ...);
        p->oprint_set_color = de_dosd_o26_set_color;
        p->oprint_set_size = de_dosd_o26_set_size;
        p->oprint_enable = de_dosd_o26_enable;
        p->oprint = de_dosd_o26_print;
    }
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O24) {
        extern int de_dosd_o24_set_color(int r, int g, int b);
        extern int de_dosd_o24_set_size(int big);
        extern int de_dosd_o24_enable(int onoff);
        extern int de_dosd_o24_print(const char *fmt, ...);
        p->oprint_set_color = de_dosd_o24_set_color;
        p->oprint_set_size = de_dosd_o24_set_size;
        p->oprint_enable = de_dosd_o24_enable;
        p->oprint = de_dosd_o24_print;
    }
#endif
    else {
        //not support
    }

    return 0;
}

int vsc_oprint(const char *fmt, ...)
{
    int len;
    va_list ap;
    char print_buf[128];
    struct vsc_print_ctx *p = &_g_vsc_print_ctx;
    if (!p->oprint) return -1;

    va_start(ap, fmt);
    len = vsnprintf(print_buf, 128, fmt, ap);
    va_end(ap);
    if (len <= 0 || len >= 128) return -1;
    //DE_NOTI("print_buf(%s)\n",print_buf);

    return p->oprint("%s",print_buf);
}

int vsc_oprint_enable(int onoff)
{
    struct vsc_print_ctx *p = &_g_vsc_print_ctx;
    if (!p->oprint_enable) return -1;
    return p->oprint_enable(onoff);
}

int vsc_oprint_set_size(int big)
{
    struct vsc_print_ctx *p = &_g_vsc_print_ctx;
    if (!p->oprint_set_size) return -1;
    return p->oprint_set_size(big);
}

int vsc_oprint_set_color(int r, int g, int b)
{
    struct vsc_print_ctx *p = &_g_vsc_print_ctx;
    if (!p->oprint_set_color) return -1;
    return p->oprint_set_color(r,g,b);
}
