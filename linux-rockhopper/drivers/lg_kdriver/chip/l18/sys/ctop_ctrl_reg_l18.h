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
 * Register access for CTOP
 *
 * author     hwanwook lee (hwanwook.lee@lge.com)
 * version    1.0
 * date       2017.04.07
 * note       Additional information.
 *
 * @addtogroup lg14xx_sys
 * @{
 */

#ifndef  __CTOP_CTRL_REG_L18_H__
#define  __CTOP_CTRL_REG_L18_H__

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "sys_reg_base.h"


#include "ctop_ctrl_reg_l18_a0.h"


/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/* L18A0 */

#define CTOP_L18A0_SHDW(_m)					(gCTOP_CTRL_L18.shdw.a0._m)
#define CTOP_L18A0_PHYS(_m)					(gCTOP_CTRL_L18.phys.a0._m)

#define CTOP_CTRL_L18A0_RdFL(_m,_r)			_REG_RdFL(CTOP_L18A0_SHDW(_m),CTOP_L18A0_PHYS(_m),_r)
#define CTOP_CTRL_L18A0_WrFL(_m,_r)			_REG_WrFL(CTOP_L18A0_SHDW(_m),CTOP_L18A0_PHYS(_m),_r)

#define CTOP_CTRL_L18A0_Rd(_m,_r)			_REG_Rd(CTOP_L18A0_SHDW(_m),_r)
#define CTOP_CTRL_L18A0_Wr(_m,_r,_v)		_REG_Wr(CTOP_L18A0_SHDW(_m),_r,_v)


#define CTOP_CTRL_L18A0_RdFd(_m,_r,_f01)					_REG_RdFd(CTOP_L18A0_SHDW(_m),_r,_f01)
#define CTOP_CTRL_L18A0_Rd01(_m,_r,_f01,_v01)				_REG_Rd01(CTOP_L18A0_SHDW(_m),_r,_f01,_v01)
#define CTOP_CTRL_L18A0_Rd02(_m,_r,_f01,_v01,_f02,_v02)		_REG_Rd02(CTOP_L18A0_SHDW(_m),_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_L18A0_Rd03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Rd03(CTOP_L18A0_SHDW(_m),_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define CTOP_CTRL_L18A0_Wr01(_m,_r,_f01,_v01)				_REG_Wr01(CTOP_L18A0_SHDW(_m),_r,_f01,_v01)
#define CTOP_CTRL_L18A0_Wr02(_m,_r,_f01,_v01,_f02,_v02)		_REG_Wr02(CTOP_L18A0_SHDW(_m),_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_L18A0_Wr03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Wr03(CTOP_L18A0_SHDW(_m),_r,_f01,_v01,_f02,_v02,_f03,_v03)



/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	union {
		CTOP_REG_L18A0_T	a0;
		UINT32				b0; // dummy, not used
	} shdw;

	union {
		CTOP_REG_L18A0_T	a0;
		UINT32				b0; // dummy, not used
	} phys;
} CTOP_CTRL_REG_L18_T;


/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
extern CTOP_CTRL_REG_L18_T		gCTOP_CTRL_L18;



#define CTOP_CTRL_L18A0_READ(m,offset)	\
({ \
	UINT32 v = 0; \
	if(offset < sizeof(L18_A0_CTOP_##m##_TYPE)) { \
		v = _REG_OfsRd(gCTOP_CTRL_L18.shdw.a0.m, gCTOP_CTRL_L18.phys.a0.m, offset); \
	} \
	v; \
})

#define CTOP_CTRL_L18A0_WRITE(m,offset,value)	\
do { \
	if(offset < sizeof(L18_A0_CTOP_##m##_TYPE)) { \
		_REG_OfsWr(gCTOP_CTRL_L18.shdw.a0.m, gCTOP_CTRL_L18.phys.a0.m, offset, value); \
	} \
} while(0)

#endif
/**  @} */
