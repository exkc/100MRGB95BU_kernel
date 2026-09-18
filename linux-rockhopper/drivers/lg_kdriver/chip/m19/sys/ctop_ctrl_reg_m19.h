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
 * author     hwanwook lee (hwanwook.lee@lge.com)
 * version    1.0
 * date       2018.04.18
 * note       Additional information.
 *
 * @addtogroup lg13xx_sys
 * @{
 */

#ifndef  __CTOP_CTRL_REG_M19_H__
#define  __CTOP_CTRL_REG_M19_H__

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "sys_reg_base.h"

#include "ctop_ctrl_reg_m19_a0.h"


/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/* M19Ax */

#define CTOP_M19Ax_SHDW(_m)					(gCTOP_CTRL_M19.shdw.a0._m)
#define CTOP_M19Ax_PHYS(_m)					(gCTOP_CTRL_M19.phys.a0._m)

#define CTOP_CTRL_M19Ax_RdFL(_m,_r)			_REG_RdFL(CTOP_M19Ax_SHDW(_m),CTOP_M19Ax_PHYS(_m),_r)
#define CTOP_CTRL_M19Ax_WrFL(_m,_r)			_REG_WrFL(CTOP_M19Ax_SHDW(_m),CTOP_M19Ax_PHYS(_m),_r)

#define CTOP_CTRL_M19Ax_Rd(_m,_r)			_REG_Rd(CTOP_M19Ax_SHDW(_m),_r)
#define CTOP_CTRL_M19Ax_Wr(_m,_r,_v)		_REG_Wr(CTOP_M19Ax_SHDW(_m),_r,_v)


#define CTOP_CTRL_M19Ax_RdFd(_m,_r,_f01)					_REG_RdFd(CTOP_M19Ax_SHDW(_m),_r,_f01)
#define CTOP_CTRL_M19Ax_Rd01(_m,_r,_f01,_v01)				_REG_Rd01(CTOP_M19Ax_SHDW(_m),_r,_f01,_v01)
#define CTOP_CTRL_M19Ax_Rd02(_m,_r,_f01,_v01,_f02,_v02)		_REG_Rd02(CTOP_M19Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_M19Ax_Rd03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Rd03(CTOP_M19Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define CTOP_CTRL_M19Ax_Wr01(_m,_r,_f01,_v01)				_REG_Wr01(CTOP_M19Ax_SHDW(_m),_r,_f01,_v01)
#define CTOP_CTRL_M19Ax_Wr02(_m,_r,_f01,_v01,_f02,_v02)		_REG_Wr02(CTOP_M19Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_M19Ax_Wr03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
	_REG_Wr03(CTOP_M19Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02,_f03,_v03)



/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	union {
		CTOP_REG_M19A0_T	a0;
		UINT32				b0; // dummy, not used
	} shdw;

	union {
		CTOP_REG_M19A0_T	a0;
		UINT32				b0; // dummy, not used
	} phys;
} CTOP_CTRL_REG_M19_T;


/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
extern CTOP_CTRL_REG_M19_T		gCTOP_CTRL_M19;



#define CTOP_CTRL_M19Ax_READ(m,offset)	\
({ \
	UINT32 v = 0; \
	if(offset < sizeof(M19_A0_##m##_TYPE)) { \
		v = _REG_OfsRd(gCTOP_CTRL_M19.shdw.a0.m, gCTOP_CTRL_M19.phys.a0.m, offset); \
	} \
	v; \
})

#define CTOP_CTRL_M19Ax_WRITE(m,offset,value)	\
do { \
	if(offset < sizeof(M19_A0_##m##_TYPE)) { \
		_REG_OfsWr(gCTOP_CTRL_M19.shdw.a0.m, gCTOP_CTRL_M19.phys.a0.m, offset, value); \
	} \
} while(0)

#endif
/**  @} */
