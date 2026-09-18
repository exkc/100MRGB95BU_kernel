/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
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
 * Register access for CTOP
 *
 * author     ks.hyun(ks.hyun@lge.com)
 * version    1.0
 * date       2019.04.16
 * note       Additional information.
 *
 * @addtogroup lg13xx_sys
 * @{
 */

#ifndef  __CTOP_CTRL_REG_E60_H__
#define  __CTOP_CTRL_REG_E60_H__

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "sys_reg_base.h"
#include "ctop_ctrl_reg_e60_a0.h"


/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/* E60Ax */

#define CTOP_E60Ax_SHDW(_m)					(gCTOP_CTRL_E60.shdw.a0._m)
#define CTOP_E60Ax_PHYS(_m)					(gCTOP_CTRL_E60.phys.a0._m)

#define CTOP_CTRL_E60Ax_RdFL(_m,_r)			_REG_RdFL(CTOP_E60Ax_SHDW(_m),CTOP_E60Ax_PHYS(_m),_r)
#define CTOP_CTRL_E60Ax_WrFL(_m,_r)			_REG_WrFL(CTOP_E60Ax_SHDW(_m),CTOP_E60Ax_PHYS(_m),_r)

#define CTOP_CTRL_E60Ax_Rd(_m,_r)			_REG_Rd(CTOP_E60Ax_SHDW(_m),_r)
#define CTOP_CTRL_E60Ax_Wr(_m,_r,_v)		_REG_Wr(CTOP_E60Ax_SHDW(_m),_r,_v)


#define CTOP_CTRL_E60Ax_RdFd(_m,_r,_f01)					_REG_RdFd(CTOP_E60Ax_SHDW(_m),_r,_f01)
#define CTOP_CTRL_E60Ax_Rd01(_m,_r,_f01,_v01)				_REG_Rd01(CTOP_E60Ax_SHDW(_m),_r,_f01,_v01)
#define CTOP_CTRL_E60Ax_Rd02(_m,_r,_f01,_v01,_f02,_v02)		_REG_Rd02(CTOP_E60Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_E60Ax_Rd03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Rd03(CTOP_E60Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define CTOP_CTRL_E60Ax_Wr01(_m,_r,_f01,_v01)				_REG_Wr01(CTOP_E60Ax_SHDW(_m),_r,_f01,_v01)
#define CTOP_CTRL_E60Ax_Wr02(_m,_r,_f01,_v01,_f02,_v02)		_REG_Wr02(CTOP_E60Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_E60Ax_Wr03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Wr03(CTOP_E60Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02,_f03,_v03)


/* E60Bx */
#define CTOP_E60Bx_SHDW(_m)					(gCTOP_CTRL_E60.shdw.a0._m)
#define CTOP_E60Bx_PHYS(_m)					(gCTOP_CTRL_E60.phys.a0._m)

#define CTOP_CTRL_E60Bx_RdFL(_m,_r)			_REG_RdFL(CTOP_E60Bx_SHDW(_m),CTOP_E60Bx_PHYS(_m),_r##_B0)
#define CTOP_CTRL_E60Bx_WrFL(_m,_r)			_REG_WrFL(CTOP_E60Bx_SHDW(_m),CTOP_E60Bx_PHYS(_m),_r##_B0)

#define CTOP_CTRL_E60Bx_Rd(_m,_r)			_REG_Rd(CTOP_E60Bx_SHDW(_m),_r##_B0)
#define CTOP_CTRL_E60Bx_Wr(_m,_r,_v)		_REG_Wr(CTOP_E60Bx_SHDW(_m),_r##_B0,_v)

#define CTOP_CTRL_E60Bx_RdFd(_m,_r,_f01) \
	_REG_RdFd(CTOP_E60Bx_SHDW(_m),_r##_B0,_f01)
#define CTOP_CTRL_E60Bx_Rd01(_m,_r,_f01,_v01) \
	_REG_Rd01(CTOP_E60Bx_SHDW(_m),_r##_B0,_f01,_v01)
#define CTOP_CTRL_E60Bx_Rd02(_m,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(CTOP_E60Bx_SHDW(_m),_r##_B0,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_E60Bx_Rd03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Rd03(CTOP_E60Bx_SHDW(_m),_r##_B0,_f01,_v01,_f02,_v02,_f03,_v03)

#define CTOP_CTRL_E60Bx_Wr01(_m,_r,_f01,_v01) \
	_REG_Wr01(CTOP_E60Bx_SHDW(_m),_r##_B0,_f01,_v01)
#define CTOP_CTRL_E60Bx_Wr02(_m,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(CTOP_E60Bx_SHDW(_m),_r##_B0,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_E60Bx_Wr03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Wr03(CTOP_E60Bx_SHDW(_m),_r##_B0,_f01,_v01,_f02,_v02,_f03,_v03)


/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	union {
		CTOP_REG_E60A0_T	a0;
		UINT32				b0; // dummy, not used
	} shdw;

	union {
		CTOP_REG_E60A0_T	a0;
		UINT32				b0; // dummy, not used
	} phys;
} CTOP_CTRL_REG_E60_T;


/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
extern CTOP_CTRL_REG_E60_T		gCTOP_CTRL_E60;



#define CTOP_CTRL_E60Ax_READ(m,offset)	\
({ \
	UINT32 v = 0; \
	if(offset < sizeof(E60_A0_##m##_TYPE)) { \
		v = _REG_OfsRd(gCTOP_CTRL_E60.shdw.a0.m, gCTOP_CTRL_E60.phys.a0.m, offset); \
	} \
	v; \
})

#define CTOP_CTRL_E60Ax_WRITE(m,offset,value)	\
do { \
	if(offset < sizeof(E60_A0_##m##_TYPE)) { \
		_REG_OfsWr(gCTOP_CTRL_E60.shdw.a0.m, gCTOP_CTRL_E60.phys.a0.m, offset, value); \
	} \
} while(0)

#endif
/**  @} */
