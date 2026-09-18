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

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "sys_regs.h"

#include "lgbus_cfg.h"

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
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

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


/*========================================================================================
	Implementation Group
========================================================================================*/

u64 LGBUS_GetDDRAddr(u64 phy_addr)
{
	switch(lx_chip())
	{
#ifdef INCLUDE_H15_CHIP_KDRV
		case LX_CHIP_H15:	return lgbus_h15_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_M16_CHIP_KDRV
		case LX_CHIP_M16:	return lgbus_m16_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_M16P_CHIP_KDRV
		case LX_CHIP_M16P:	return lgbus_m16p_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_L18_CHIP_KDRV
		case LX_CHIP_L18F:	return lgbus_l18_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
		case LX_CHIP_O18:	return lgbus_o18_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
		case LX_CHIP_M19:	return lgbus_m19_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
		case LX_CHIP_O20:	return lgbus_o20_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
		case LX_CHIP_E60:	return lgbus_e60_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
		case LX_CHIP_O22:	return lgbus_o22_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
		case LX_CHIP_M23:	return lgbus_m23_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
		case LX_CHIP_O24:	return lgbus_o24_get_ddr_addr(phy_addr);
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
		case LX_CHIP_O26:	return lgbus_o26_get_ddr_addr(phy_addr);
#endif

		default:			return 0;
	}
}
EXPORT_SYMBOL(LGBUS_GetDDRAddr);

/* TODO : implement HAL function */

int LGBUS_SetMproRange(lgbus_mpro_range_t *mpro_range)
{
	switch(lx_chip())
	{
#ifdef INCLUDE_H15_CHIP_KDRV
		case LX_CHIP_H15:	LGBUS_H15_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_M16_CHIP_KDRV
		case LX_CHIP_M16:	LGBUS_M16_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_M16P_CHIP_KDRV
		case LX_CHIP_M16P:	LGBUS_M16P_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_L18_CHIP_KDRV
		case LX_CHIP_L18F:	LGBUS_L18_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
		case LX_CHIP_O18:	LGBUS_O18_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
		case LX_CHIP_M19:	LGBUS_M19_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
		case LX_CHIP_O20:	LGBUS_O20_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
		case LX_CHIP_E60:	LGBUS_E60_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
		case LX_CHIP_O22:	LGBUS_O22_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
		case LX_CHIP_M23:	LGBUS_M23_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
		case LX_CHIP_O24:	LGBUS_O24_SetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
		case LX_CHIP_O26:	LGBUS_O26_SetMproRange(mpro_range); break;
#endif

		default:			/* do nothing */ break;
	}

	return 0;
}
EXPORT_SYMBOL(LGBUS_SetMproRange);

int LGBUS_GetMproRange(lgbus_mpro_range_t *mpro_range)
{
	switch(lx_chip())
	{
#ifdef INCLUDE_H15_CHIP_KDRV
		case LX_CHIP_H15:	LGBUS_H15_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_M16_CHIP_KDRV
		case LX_CHIP_M16:	LGBUS_M16_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_M16P_CHIP_KDRV
		case LX_CHIP_M16P:	LGBUS_M16P_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_L18_CHIP_KDRV
		case LX_CHIP_L18F:	LGBUS_L18_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
		case LX_CHIP_O18:	LGBUS_O18_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
		case LX_CHIP_M19:	LGBUS_M19_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
		case LX_CHIP_O20:	LGBUS_O20_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
		case LX_CHIP_E60:	LGBUS_E60_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
		case LX_CHIP_O22:	LGBUS_O22_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
		case LX_CHIP_M23:	LGBUS_M23_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
		case LX_CHIP_O24:	LGBUS_O24_GetMproRange(mpro_range); break;
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
		case LX_CHIP_O26:	LGBUS_O26_GetMproRange(mpro_range); break;
#endif

		default:			/* do nothing */ break;
	}

	return 0;
}
EXPORT_SYMBOL(LGBUS_GetMproRange);

/*
 * port	: port number, ref>lgbus_o24_port_t
 * ctrl	: 1:enable stall, 0:disable stall
 */
int lgbus_mpro_stall_ctrl_module(int port, int ctrl)
{
	switch(lx_chip())
	{
#ifdef INCLUDE_O26_CHIP_KDRV
		case LX_CHIP_O26:	lgbus_o26_mpro_stall_ctrl_module(port, ctrl); break;
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
		case LX_CHIP_O24:	lgbus_o24_mpro_stall_ctrl_module(port, ctrl); break;
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
		case LX_CHIP_O22:	lgbus_o22_mpro_stall_ctrl_module(port, ctrl); break;
#endif

		default:			/* do nothing */ break;
	}

	return 0;

}
EXPORT_SYMBOL(lgbus_mpro_stall_ctrl_module);

/** @} */

