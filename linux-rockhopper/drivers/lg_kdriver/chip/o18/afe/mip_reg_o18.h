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
 * Register access for analog chip top
 *
 * author     ks.hyun (ks.hyun@lge.com)
 *            hwanwook lee (hwanwook.lee@lge.com)
 * version    1.0
 * date       2012.04.27
 * note       Additional information.
 *
 * @addtogroup lg115x_sys
 * @{
 */
#ifndef __ADC_MIP_REG_O18_H__
#define __ADC_MIP_REG_O18_H__


/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "reg_ctrl.h"
#include "sys_reg_base.h"

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/* CTOP_SYN : reg_bridge */
#define MIP_REG_O18A0_RdFL(_r)				_REG_RdFL(CTOP_O18A0_SHDW(REG_BRIDGE),CTOP_O18A0_PHYS(REG_BRIDGE),_r)
#define MIP_REG_O18A0_WrFL(_r)			_REG_WrFL(CTOP_O18A0_SHDW(REG_BRIDGE),CTOP_O18A0_PHYS(REG_BRIDGE),_r)

#define MIP_REG_O18A0_Rd(_r)				_REG_Rd(CTOP_O18A0_SHDW(REG_BRIDGE),_r)
#define MIP_REG_O18A0_Wr(_r,_v)				_REG_Wr(CTOP_O18A0_SHDW(REG_BRIDGE),_r,_v)

#define MIP_REG_O18A0_RdFd(_r,_f01)					_REG_RdFd(CTOP_O18A0_SHDW(REG_BRIDGE),_r,_f01)
#define MIP_REG_O18A0_Rd01(_r,_f01,_v01)				_REG_Rd01(CTOP_O18A0_SHDW(REG_BRIDGE),_r,_f01,_v01)
#define MIP_REG_O18A0_Rd02(_r,_f01,_v01,_f02,_v02)		_REG_Rd02(CTOP_O18A0_SHDW(REG_BRIDGE),_r,_f01,_v01,_f02,_v02)
#define MIP_REG_O18A0_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Rd03(CTOP_O18A0_SHDW(REG_BRIDGE),_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define MIP_REG_O18A0_Wr01(_r,_f01,_v01)				_REG_Wr01(CTOP_O18A0_SHDW(REG_BRIDGE),_r,_f01,_v01)
#define MIP_REG_O18A0_Wr02(_r,_f01,_v01,_f02,_v02)		_REG_Wr02(CTOP_O18A0_SHDW(REG_BRIDGE),_r,_f01,_v01,_f02,_v02)
#define MIP_REG_O18A0_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Wr03(CTOP_O18A0_SHDW(REG_BRIDGE),_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define ACE_REG_O18A0_RdFL(_r)									MIP_REG_O18A0_RdFL(_r)
#define ACE_REG_O18A0_WrFL(_r)									MIP_REG_O18A0_WrFL(_r)

#define ACE_REG_O18A0_Rd(_r)									MIP_REG_O18A0_Rd(_r)
#define ACE_REG_O18A0_Wr(_r,_v)									MIP_REG_O18A0_Wr(_r,_v)

#define ACE_REG_O18A0_Rd01(_r,_f01,_v01) 						MIP_REG_O18A0_Rd01(_r,_f01,_v01)

#define ACE_REG_O18A0_Rd02(_r,_f01,_v01,_f02,_v02)				MIP_REG_O18A0_Rd02(_r,_f01,_v01,_f02,_v02)

#define ACE_REG_O18A0_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)	MIP_REG_O18A0_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define ACE_REG_O18A0_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)	MIP_REG_O18A0_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)

#define ACE_REG_O18A0_Wr01(_r,_f01,_v01)						MIP_REG_O18A0_Wr01(_r,_f01,_v01)

#define ACE_REG_O18A0_Wr02(_r,_f01,_v01,_f02,_v02)				MIP_REG_O18A0_Wr02(_r,_f01,_v01,_f02,_v02)

#define ACE_REG_O18A0_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)	MIP_REG_O18A0_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define ACE_REG_O18A0_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)	MIP_REG_O18A0_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)


/* CTOP : CTOP_BMC */
#define BMC_REG_O18A0_RdFL(_r)				_REG_RdFL(CTOP_O18A0_SHDW(BMC_SYN),CTOP_O18A0_PHYS(BMC_SYN),_r)
#define BMC_REG_O18A0_WrFL(_r)			_REG_WrFL(CTOP_O18A0_SHDW(BMC_SYN),CTOP_O18A0_PHYS(BMC_SYN),_r)

#define BMC_REG_O18A0_Rd(_r)				_REG_Rd(CTOP_O18A0_SHDW(BMC_SYN),_r)
#define BMC_REG_O18A0_Wr(_r,_v)				_REG_Wr(CTOP_O18A0_SHDW(BMC_SYN),_r,_v)

#define BMC_REG_O18A0_RdFd(_r,_f01)					_REG_RdFd(CTOP_O18A0_SHDW(BMC_SYN),_r,_f01)
#define BMC_REG_O18A0_Rd01(_r,_f01,_v01)				_REG_Rd01(CTOP_O18A0_SHDW(BMC_SYN),_r,_f01,_v01)
#define BMC_REG_O18A0_Rd02(_r,_f01,_v01,_f02,_v02)		_REG_Rd02(CTOP_O18A0_SHDW(BMC_SYN),_r,_f01,_v01,_f02,_v02)
#define BMC_REG_O18A0_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Rd03(CTOP_O18A0_SHDW(BMC_SYN),_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define BMC_REG_O18A0_Wr01(_r,_f01,_v01)				_REG_Wr01(CTOP_O18A0_SHDW(BMC_SYN),_r,_f01,_v01)
#define BMC_REG_O18A0_Wr02(_r,_f01,_v01,_f02,_v02)		_REG_Wr02(CTOP_O18A0_SHDW(BMC_SYN),_r,_f01,_v01,_f02,_v02)
#define BMC_REG_O18A0_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Wr03(CTOP_O18A0_SHDW(BMC_SYN),_r,_f01,_v01,_f02,_v02,_f03,_v03)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#endif
