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
#ifndef __ATOP_REG_O20_H__
#define __ATOP_REG_O20_H__


/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "reg_ctrl.h"
#include "sys_reg_base.h"

#include "atop_reg_o20a0.h"

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define ACE_REG_O20A0_SHDW				(gATOP_CTRL_O20.shdw.addr)
#define ACE_REG_O20A0_PHYS				(gATOP_CTRL_O20.phys.addr)

#define ACE_REG_O20A0_RdFL(_r)			((gATOP_CTRL_O20.shdw.a0->_r)=(gATOP_CTRL_O20.phys.a0->_r))
#define ACE_REG_O20A0_WrFL(_r)			((gATOP_CTRL_O20.phys.a0->_r)=(gATOP_CTRL_O20.shdw.a0->_r))

#define ACE_REG_O20A0_Rd(_r)			*((UINT32*)(&(gATOP_CTRL_O20.shdw.a0->_r)))
#define ACE_REG_O20A0_Wr(_r,_v)		((ACE_REG_O20A0_Rd(_r))=((UINT32)(_v)))

#define ACE_REG_O20A0_Rd01(_r,_f01,_v01)													\
								do { 											\
									(_v01) = (gATOP_CTRL_O20.shdw.a0->_r._f01);				\
								} while(0)

#define ACE_REG_O20A0_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (gATOP_CTRL_O20.shdw.a0->_r._f01);				\
									(_v02) = (gATOP_CTRL_O20.shdw.a0->_r._f02);				\
								} while(0)

#define ACE_REG_O20A0_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(_v01) = (gATOP_CTRL_O20.shdw.a0->_r._f01);				\
									(_v02) = (gATOP_CTRL_O20.shdw.a0->_r._f02);				\
									(_v03) = (gATOP_CTRL_O20.shdw.a0->_r._f03);				\
								} while(0)

#define ACE_REG_O20A0_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(_v01) = (gATOP_CTRL_O20.shdw.a0->_r._f01);				\
									(_v02) = (gATOP_CTRL_O20.shdw.a0->_r._f02);				\
									(_v03) = (gATOP_CTRL_O20.shdw.a0->_r._f03);				\
									(_v04) = (gATOP_CTRL_O20.shdw.a0->_r._f04);				\
								} while(0)

#define ACE_REG_O20A0_Wr01(_r,_f01,_v01)													\
								do { 											\
									(gATOP_CTRL_O20.shdw.a0->_r._f01) = (_v01);				\
								} while(0)

#define ACE_REG_O20A0_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(gATOP_CTRL_O20.shdw.a0->_r._f01) = (_v01);				\
									(gATOP_CTRL_O20.shdw.a0->_r._f02) = (_v02);				\
								} while(0)

#define ACE_REG_O20A0_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(gATOP_CTRL_O20.shdw.a0->_r._f01) = (_v01);				\
									(gATOP_CTRL_O20.shdw.a0->_r._f02) = (_v02);				\
									(gATOP_CTRL_O20.shdw.a0->_r._f03) = (_v03);				\
								} while(0)

#define ACE_REG_O20A0_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(gATOP_CTRL_O20.shdw.a0->_r._f01) = (_v01);				\
									(gATOP_CTRL_O20.shdw.a0->_r._f02) = (_v02);				\
									(gATOP_CTRL_O20.shdw.a0->_r._f03) = (_v03);				\
									(gATOP_CTRL_O20.shdw.a0->_r._f04) = (_v04);				\
								} while(0)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

typedef struct
{
	union {
		UINT32			 *addr;
		REG_BRIDGE_REG_O20_T	*a0;
		UINT32				*b0; // dummy, not used
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile REG_BRIDGE_REG_O20_T	*a0;
		UINT32				*b0; // dummy, not used
	} phys;
} ATOP_CTRL_REG_O20_T;

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern ATOP_CTRL_REG_O20_T	gATOP_CTRL_O20;

#endif
