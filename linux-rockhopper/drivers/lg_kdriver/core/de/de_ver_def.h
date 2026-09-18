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
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2011.02.21
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

#ifndef  DE_VER_INC
#define  DE_VER_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#ifdef INCLUDE_O18_CHIP_KDRV
#define USE_KDRV_CODES_FOR_O18
#define _O18_FPGA_TEMPORAL_
#define USE_KDRV_CODES_FOR_O18A0
#ifndef INCLUDE_KDRV_VER_FPGA
#define USE_CTOP_CODES_FOR_O18
#endif
#endif
#ifdef INCLUDE_L18_CHIP_KDRV
#define USE_KDRV_CODES_FOR_L18
#define _L18_FPGA_TEMPORAL_
#define USE_KDRV_CODES_FOR_L18A0
#define USE_CTOP_CODES_FOR_L18
#ifndef INCLUDE_KDRV_VER_FPGA
#define USE_CTOP_CODES_FOR_L18
#endif
#endif

#ifdef INCLUDE_M17_CHIP_KDRV
#define USE_KDRV_CODES_FOR_M17
#define _M17_FPGA_TEMPORAL_
#define USE_KDRV_CODES_FOR_M17A0
#ifndef INCLUDE_KDRV_VER_FPGA
#define USE_CTOP_CODES_FOR_M17
#endif
#endif

#ifdef INCLUDE_M19_CHIP_KDRV
#define USE_KDRV_CODES_FOR_M19
#define _M19_FPGA_TEMPORAL_
#define USE_KDRV_CODES_FOR_M19A0
#ifndef INCLUDE_KDRV_VER_FPGA
#define USE_CTOP_CODES_FOR_M19
#endif
#endif

#ifdef INCLUDE_O20_CHIP_KDRV
#define USE_KDRV_CODES_FOR_O20
#define _O20_FPGA_TEMPORAL_
#define USE_KDRV_CODES_FOR_O20A0
#ifndef INCLUDE_KDRV_VER_FPGA
#define USE_CTOP_CODES_FOR_O20
#endif
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
#define USE_KDRV_CODES_FOR_E60
#define _E60_FPGA_TEMPORAL_
#define USE_KDRV_CODES_FOR_E60A0
#ifndef INCLUDE_KDRV_VER_FPGA
#define USE_CTOP_CODES_FOR_E60
#endif
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
#define USE_KDRV_CODES_FOR_O22
#define _O22_FPGA_TEMPORAL_
#define USE_KDRV_CODES_FOR_O22A0
#define USE_ND1_INTR_FOR_IPC  // w/a for A0 IPC interrupt (use ND1 interrupt)
#ifndef INCLUDE_KDRV_VER_FPGA
#define USE_CTOP_CODES_FOR_O22
#endif
#endif

#ifdef INCLUDE_M23_CHIP_KDRV
#define USE_KDRV_CODES_FOR_M23
#define _M23_FPGA_TEMPORAL_
#define USE_KDRV_CODES_FOR_M23A0
#ifndef INCLUDE_KDRV_VER_FPGA
#define USE_CTOP_CODES_FOR_M23
#endif
#endif

#ifdef INCLUDE_O24_CHIP_KDRV
#define USE_KDRV_CODES_FOR_O24
#define USE_KDRV_CODES_FOR_O24A0
#ifndef INCLUDE_KDRV_VER_FPGA
#define USE_CTOP_CODES_FOR_O24
#endif
#endif

#ifdef INCLUDE_O26_CHIP_KDRV
#define USE_KDRV_CODES_FOR_O26
#define USE_KDRV_CODES_FOR_O26A0
#ifndef INCLUDE_KDRV_VER_FPGA
#define USE_CTOP_CODES_FOR_O26
#endif
#endif

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "base_types.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#ifndef LX_CHIP_REV
#define lx_chip_rev() 0x09A0
#define MAKE_CHIP_REV(chp, rev) (( chp << 8) | ( rev ))
#define LX_CHIP_REV(chp, rev) MAKE_CHIP_REV( LX_CHIP_##chp, 0x##rev )
#endif

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_VER_INC  ----- */
/**  @} */
