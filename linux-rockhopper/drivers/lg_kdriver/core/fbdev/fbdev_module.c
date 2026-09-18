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
 *  main driver implementation for fbdev device.
 *
 *  author      raxis.lim (raxis.lim@lge.com)
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
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hal.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
ENDIAN_INFORM_T FBDEV_GetOSDImageEndian(int bpp);
UINT8 FBDEV_GetOSDPxlFmt(int bpp);
UINT8 FBDEV_GetOSDPxlDepth(int bpp);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
/** get endian value for given bpp information
 *
 *
 */
ENDIAN_INFORM_T FBDEV_GetOSDImageEndian(int bpp)
{
    ENDIAN_INFORM_T endian;

    switch (bpp)
    {
        case 8:
#ifdef FBDEV_SUPPORT_8BPP_EMUL
            endian.header   = 4;
            endian.palette  = 4;
            endian.image    = 4;
#else
            endian.header   = 4;
            endian.palette  = 4;
            endian.image    = 7;
#endif
            break;

        case 16:
            endian.header   = 4;
            endian.palette  = 4;
            endian.image    = 6;
            break;

        case 32:
            endian.header   = 4;
            endian.palette  = 4;
            endian.image    = 4;
            break;

        default:
            endian.header   = 4;
            endian.palette  = 4;
            endian.image    = 4;
            break;
    }

    return endian;
}


UINT8   FBDEV_GetOSDPxlFmt(int bpp)
{
    switch (bpp)
    {
        case 8:     return ARGB8888;

        case 16:    return RGB565;

        case 32:
        default:    return ARGB8888;
    }
}

UINT8   FBDEV_GetOSDPxlDepth(int bpp)
{
    switch (bpp)
    {
#ifdef FBDEV_SUPPORT_8BPP_EMUL

        case 8:     return PIX_DEPTH_32_BPP;
#else

        case 8:     return PIX_DEPTH_8_BPP;
#endif

        case 16:    return PIX_DEPTH_16_BPP;

        case 32:
        default:    return PIX_DEPTH_32_BPP;
    }
}

/*========================================================================================
    Implementation Group (MONITOR)
========================================================================================*/

