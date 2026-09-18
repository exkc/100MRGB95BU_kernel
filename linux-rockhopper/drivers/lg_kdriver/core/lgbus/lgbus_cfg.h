/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */


/** @file
 *
 *  main configuration file for lgbus device
 *	lgbus device will teach you how to make device driver with new platform.
 *
 *  author		hwanwook.lee (hwanwook.lee@lge.com)
 *  version		1.0
 *  date		2012.07.14
 *  note		Additional information.
 *
 *  @addtogroup lg115x_lgbus
 *	@{
 */

#ifndef	_LGBUS_CFG_H_
#define	_LGBUS_CFG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/types.h>


#define H15_MPRO_RANGE_SLOT_CNT			(2)
#define M16_MPRO_RANGE_SLOT_CNT			(3)
#define M16P_MPRO_RANGE_SLOT_CNT		(3)
#define L18_MPRO_RANGE_SLOT_CNT			(3)
#define O18_MPRO_RANGE_SLOT_CNT			(3)
#define M19_MPRO_RANGE_SLOT_CNT			(3)
#define O20_MPRO_RANGE_SLOT_CNT			(3)
#define E60_MPRO_RANGE_SLOT_CNT			(3)
#define O22_MPRO_RANGE_SLOT_CNT			(3)
#define M23_MPRO_RANGE_SLOT_CNT			(3)
#define O24_MPRO_RANGE_SLOT_CNT			(3)
#define O26_MPRO_RANGE_SLOT_CNT			(3)

#define MPRO_RANGE_SLOT_CNT_MAX			(3)

typedef struct
{
	u64		start;
	u64		end;
}lgbus_mpro_add_t;

typedef struct
{
	u32		port;
	lgbus_mpro_add_t 	range[MPRO_RANGE_SLOT_CNT_MAX];
}lgbus_mpro_range_t;

typedef	struct
{
	u64		start;
	u64		end;
	u64		offset;
}lgbus_addr_switch_t;

typedef struct
{
	u64		start;
	u64		end;
	u64		offset;
	u32		offset_mode;
	u32		mode;
	u32		unit;
}lgbus_bwb_t;

#ifdef INCLUDE_H15_CHIP_KDRV
#include "h15/lgbus/lgbus_h15_mpro.h"
#endif

#ifdef INCLUDE_M16_CHIP_KDRV
#include "m16/lgbus/lgbus_m16_mpro.h"
#endif

#ifdef INCLUDE_M17_CHIP_KDRV
#include "m16p/lgbus/lgbus_m16p_mpro.h"
#endif

#ifdef INCLUDE_L18_CHIP_KDRV
#include "l18/lgbus/lgbus_l18_mpro.h"
#endif

#ifdef INCLUDE_O18_CHIP_KDRV
#include "o18/lgbus/lgbus_o18_mpro.h"
#endif

#ifdef INCLUDE_M19_CHIP_KDRV
#include "m19/lgbus/lgbus_m19_mpro.h"
#endif

#ifdef INCLUDE_O20_CHIP_KDRV
#include "o20/lgbus/lgbus_o20_mpro.h"
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
#include "e60/lgbus/lgbus_e60_mpro.h"
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
#include "o22/lgbus/lgbus_o22_mpro.h"
#endif

#ifdef INCLUDE_M23_CHIP_KDRV
#include "m23/lgbus/lgbus_m23_mpro.h"
#endif

#ifdef INCLUDE_O24_CHIP_KDRV
#include "o24/lgbus/lgbus_o24_mpro.h"
#endif

#ifdef INCLUDE_O26_CHIP_KDRV
#include "o26/lgbus/lgbus_o26_mpro.h"
#endif

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	LGBUS_MODULE			"lgbus"
#define LGBUS_MAX_DEVICE		1

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern u64 LGBUS_GetDDRAddr(u64 phy_addr);
extern int LGBUS_SetMproRange(lgbus_mpro_range_t *mpro_range);
extern int LGBUS_GetMproRange(lgbus_mpro_range_t *mpro_range);
extern int lgbus_mpro_stall_ctrl_module(int port, int ctrl);


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _LGBUS_CFG_H_ */

/** @} */

