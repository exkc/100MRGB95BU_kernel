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
#ifndef __ADC_DIG_REG_O20_H__
#define __ADC_DIG_REG_O20_H__


/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "reg_ctrl.h"
#include "sys_reg_base.h"

#include "adc_dig_reg_o20_ax.h"

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DIG_REG_O20Ax_SHDW				(gMIP_DIG_CTRL_O20.shdw.addr)
#define DIG_REG_O20Ax_PHYS				(gMIP_DIG_CTRL_O20.phys.addr)

#define DIG_REG_O20Ax_RdFL(_r)			((gMIP_DIG_CTRL_O20.shdw.a0->_r)=(gMIP_DIG_CTRL_O20.phys.a0->_r))
#define DIG_REG_O20Ax_WrFL(_r)			((gMIP_DIG_CTRL_O20.phys.a0->_r)=(gMIP_DIG_CTRL_O20.shdw.a0->_r))

#define DIG_REG_O20Ax_Rd(_r)			*((UINT32*)(&(gMIP_DIG_CTRL_O20.shdw.a0->_r)))
#define DIG_REG_O20Ax_Wr(_r,_v)		((DIG_REG_O20Ax_Rd(_r))=((UINT32)(_v)))

#define DIG_REG_O20Ax_Rd01(_r,_f01,_v01)													\
								do { 											\
									(_v01) = (gMIP_DIG_CTRL_O20.shdw.a0->_r._f01);				\
								} while(0)

#define DIG_REG_O20Ax_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (gMIP_DIG_CTRL_O20.shdw.a0->_r._f01);				\
									(_v02) = (gMIP_DIG_CTRL_O20.shdw.a0->_r._f02);				\
								} while(0)

#define DIG_REG_O20Ax_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(_v01) = (gMIP_DIG_CTRL_O20.shdw.a0->_r._f01);				\
									(_v02) = (gMIP_DIG_CTRL_O20.shdw.a0->_r._f02);				\
									(_v03) = (gMIP_DIG_CTRL_O20.shdw.a0->_r._f03);				\
								} while(0)

#define DIG_REG_O20Ax_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(_v01) = (gMIP_DIG_CTRL_O20.shdw.a0->_r._f01);				\
									(_v02) = (gMIP_DIG_CTRL_O20.shdw.a0->_r._f02);				\
									(_v03) = (gMIP_DIG_CTRL_O20.shdw.a0->_r._f03);				\
									(_v04) = (gMIP_DIG_CTRL_O20.shdw.a0->_r._f04);				\
								} while(0)

#define DIG_REG_O20Ax_Wr01(_r,_f01,_v01)													\
								do { 											\
									(gMIP_DIG_CTRL_O20.shdw.a0->_r._f01) = (_v01);				\
								} while(0)

#define DIG_REG_O20Ax_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(gMIP_DIG_CTRL_O20.shdw.a0->_r._f01) = (_v01);				\
									(gMIP_DIG_CTRL_O20.shdw.a0->_r._f02) = (_v02);				\
								} while(0)

#define DIG_REG_O20Ax_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(gMIP_DIG_CTRL_O20.shdw.a0->_r._f01) = (_v01);				\
									(gMIP_DIG_CTRL_O20.shdw.a0->_r._f02) = (_v02);				\
									(gMIP_DIG_CTRL_O20.shdw.a0->_r._f03) = (_v03);				\
								} while(0)

#define DIG_REG_O20Ax_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(gMIP_DIG_CTRL_O20.shdw.a0->_r._f01) = (_v01);				\
									(gMIP_DIG_CTRL_O20.shdw.a0->_r._f02) = (_v02);				\
									(gMIP_DIG_CTRL_O20.shdw.a0->_r._f03) = (_v03);				\
									(gMIP_DIG_CTRL_O20.shdw.a0->_r._f04) = (_v04);				\
								} while(0)


#define ACE_REG_O20Ax_RdFL(_r)									DIG_REG_O20Ax_RdFL(_r)
#define ACE_REG_O20Ax_WrFL(_r)									DIG_REG_O20Ax_WrFL(_r)

#define ACE_REG_O20Ax_Rd(_r)									DIG_REG_O20Ax_Rd(_r)
#define ACE_REG_O20Ax_Wr(_r,_v)									DIG_REG_O20Ax_Wr(_r,_v)

#define ACE_REG_O20Ax_Rd01(_r,_f01,_v01) 						DIG_REG_O20Ax_Rd01(_r,_f01,_v01)

#define ACE_REG_O20Ax_Rd02(_r,_f01,_v01,_f02,_v02)				DIG_REG_O20Ax_Rd02(_r,_f01,_v01,_f02,_v02)

#define ACE_REG_O20Ax_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)	DIG_REG_O20Ax_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define ACE_REG_O20Ax_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)	DIG_REG_O20Ax_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)

#define ACE_REG_O20Ax_Wr01(_r,_f01,_v01)						DIG_REG_O20Ax_Wr01(_r,_f01,_v01)

#define ACE_REG_O20Ax_Wr02(_r,_f01,_v01,_f02,_v02)				DIG_REG_O20Ax_Wr02(_r,_f01,_v01,_f02,_v02)

#define ACE_REG_O20Ax_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)	DIG_REG_O20Ax_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define ACE_REG_O20Ax_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)	DIG_REG_O20Ax_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)

#define BMC_REG_O20Ax_RdFL(_r)				_REG_RdFL(CTOP_O20Ax_SHDW(CTOP_BMC),CTOP_O20Ax_PHYS(CTOP_BMC),_r)
#define BMC_REG_O20Ax_WrFL(_r)			_REG_WrFL(CTOP_O20Ax_SHDW(CTOP_BMC),CTOP_O20Ax_PHYS(CTOP_BMC),_r)

#define BMC_REG_O20Ax_Rd(_r)				_REG_Rd(CTOP_O20Ax_SHDW(CTOP_BMC),_r)
#define BMC_REG_O20Ax_Wr(_r,_v)				_REG_Wr(CTOP_O20Ax_SHDW(CTOP_BMC),_r,_v)

#define BMC_REG_O20Ax_RdFd(_r,_f01)					_REG_RdFd(CTOP_O20Ax_SHDW(CTOP_BMC),_r,_f01)
#define BMC_REG_O20Ax_Rd01(_r,_f01,_v01)				_REG_Rd01(CTOP_O20Ax_SHDW(CTOP_BMC),_r,_f01,_v01)
#define BMC_REG_O20Ax_Rd02(_r,_f01,_v01,_f02,_v02)		_REG_Rd02(CTOP_O20Ax_SHDW(CTOP_BMC),_r,_f01,_v01,_f02,_v02)
#define BMC_REG_O20Ax_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Rd03(CTOP_O20Ax_SHDW(CTOP_BMC),_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define BMC_REG_O20Ax_Wr01(_r,_f01,_v01)				_REG_Wr01(CTOP_O20Ax_SHDW(CTOP_BMC),_r,_f01,_v01)
#define BMC_REG_O20Ax_Wr02(_r,_f01,_v01,_f02,_v02)		_REG_Wr02(CTOP_O20Ax_SHDW(CTOP_BMC),_r,_f01,_v01,_f02,_v02)
#define BMC_REG_O20Ax_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Wr03(CTOP_O20Ax_SHDW(CTOP_BMC),_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define MIP_REG_O20Ax_RdFL(_r)				_REG_RdFL(CTOP_O20Ax_SHDW(BMC_SYN),CTOP_O20Ax_PHYS(BMC_SYN),_r)
#define MIP_REG_O20Ax_WrFL(_r)			_REG_WrFL(CTOP_O20Ax_SHDW(BMC_SYN),CTOP_O20Ax_PHYS(BMC_SYN),_r)

#define MIP_REG_O20Ax_Rd(_r)				_REG_Rd(CTOP_O20Ax_SHDW(BMC_SYN),_r)
#define MIP_REG_O20Ax_Wr(_r,_v)				_REG_Wr(CTOP_O20Ax_SHDW(BMC_SYN),_r,_v)

#define MIP_REG_O20Ax_RdFd(_r,_f01)					_REG_RdFd(CTOP_O20Ax_SHDW(BMC_SYN),_r,_f01)
#define MIP_REG_O20Ax_Rd01(_r,_f01,_v01)				_REG_Rd01(CTOP_O20Ax_SHDW(BMC_SYN),_r,_f01,_v01)
#define MIP_REG_O20Ax_Rd02(_r,_f01,_v01,_f02,_v02)		_REG_Rd02(CTOP_O20Ax_SHDW(BMC_SYN),_r,_f01,_v01,_f02,_v02)
#define MIP_REG_O20Ax_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Rd03(CTOP_O20Ax_SHDW(BMC_SYN),_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define MIP_REG_O20Ax_Wr01(_r,_f01,_v01)				_REG_Wr01(CTOP_O20Ax_SHDW(BMC_SYN),_r,_f01,_v01)
#define MIP_REG_O20Ax_Wr02(_r,_f01,_v01,_f02,_v02)		_REG_Wr02(CTOP_O20Ax_SHDW(BMC_SYN),_r,_f01,_v01,_f02,_v02)
#define MIP_REG_O20Ax_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Wr03(CTOP_O20Ax_SHDW(BMC_SYN),_r,_f01,_v01,_f02,_v02,_f03,_v03)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

typedef struct
{
	union {
		UINT32			 *addr;
		MIP_DIG_REG_O20_T	*a0;
		UINT32				*b0; // dummy, not used
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile MIP_DIG_REG_O20_T	*a0;
		UINT32				*b0; // dummy, not used
	} phys;
} MIP_DIG_CTRL_REG_O20_T;


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern MIP_DIG_CTRL_REG_O20_T	gMIP_DIG_CTRL_O20;

#endif
