/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef  __CTOP_CTRL_REG_O26_H__
#define  __CTOP_CTRL_REG_O26_H__

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "sys_reg_base.h"
#include "ctop_ctrl_reg_o26_a0.h"

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#ifndef USE_O26_FAKE_CTOP_REGS

#define CTOP_O26Ax_SHDW(_m)             (gCTOP_CTRL_O26.shdw.a0._m)
#define CTOP_O26Ax_PHYS(_m)             (gCTOP_CTRL_O26.phys.a0._m)

#define CTOP_CTRL_O26Ax_RdFL(_m,_r)     _REG_RdFL(CTOP_O26Ax_SHDW(_m),CTOP_O26Ax_PHYS(_m),_r)
#define CTOP_CTRL_O26Ax_WrFL(_m,_r)     _REG_WrFL(CTOP_O26Ax_SHDW(_m),CTOP_O26Ax_PHYS(_m),_r)

#define CTOP_CTRL_O26Ax_Rd(_m,_r)       _REG_Rd(CTOP_O26Ax_SHDW(_m),_r)
#define CTOP_CTRL_O26Ax_Wr(_m,_r,_v)    _REG_Wr(CTOP_O26Ax_SHDW(_m),_r,_v)

#define CTOP_CTRL_O26Ax_RdFd(_m,_r,_f01) \
    _REG_RdFd(CTOP_O26Ax_SHDW(_m),_r,_f01)
#define CTOP_CTRL_O26Ax_Rd01(_m,_r,_f01,_v01) \
    _REG_Rd01(CTOP_O26Ax_SHDW(_m),_r,_f01,_v01)
#define CTOP_CTRL_O26Ax_Rd02(_m,_r,_f01,_v01,_f02,_v02) \
    _REG_Rd02(CTOP_O26Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_O26Ax_Rd03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
    _REG_Rd03(CTOP_O26Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define CTOP_CTRL_O26Ax_Wr01(_m,_r,_f01,_v01) \
    _REG_Wr01(CTOP_O26Ax_SHDW(_m),_r,_f01,_v01)
#define CTOP_CTRL_O26Ax_Wr02(_m,_r,_f01,_v01,_f02,_v02) \
    _REG_Wr02(CTOP_O26Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_O26Ax_Wr03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
    _REG_Wr03(CTOP_O26Ax_SHDW(_m),_r,_f01,_v01,_f02,_v02,_f03,_v03)

/* O26Bx */
#define CTOP_O26Bx_SHDW(_m)             (gCTOP_CTRL_O26.shdw.a0._m)
#define CTOP_O26Bx_PHYS(_m)             (gCTOP_CTRL_O26.phys.a0._m)

#define CTOP_CTRL_O26Bx_RdFL(_m,_r)     _REG_RdFL(CTOP_O26Bx_SHDW(_m),CTOP_O26Bx_PHYS(_m),_r##_B0)
#define CTOP_CTRL_O26Bx_WrFL(_m,_r)     _REG_WrFL(CTOP_O26Bx_SHDW(_m),CTOP_O26Bx_PHYS(_m),_r##_B0)

#define CTOP_CTRL_O26Bx_Rd(_m,_r)       _REG_Rd(CTOP_O26Bx_SHDW(_m),_r##_B0)
#define CTOP_CTRL_O26Bx_Wr(_m,_r,_v)    _REG_Wr(CTOP_O26Bx_SHDW(_m),_r##_B0,_v)

#define CTOP_CTRL_O26Bx_RdFd(_m,_r,_f01) \
    _REG_RdFd(CTOP_O26Bx_SHDW(_m),_r##_B0,_f01)
#define CTOP_CTRL_O26Bx_Rd01(_m,_r,_f01,_v01) \
    _REG_Rd01(CTOP_O26Bx_SHDW(_m),_r##_B0,_f01,_v01)
#define CTOP_CTRL_O26Bx_Rd02(_m,_r,_f01,_v01,_f02,_v02) \
    _REG_Rd02(CTOP_O26Bx_SHDW(_m),_r##_B0,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_O26Bx_Rd03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
    _REG_Rd03(CTOP_O26Bx_SHDW(_m),_r##_B0,_f01,_v01,_f02,_v02,_f03,_v03)

#define CTOP_CTRL_O26Bx_Wr01(_m,_r,_f01,_v01) \
    _REG_Wr01(CTOP_O26Bx_SHDW(_m),_r##_B0,_f01,_v01)
#define CTOP_CTRL_O26Bx_Wr02(_m,_r,_f01,_v01,_f02,_v02) \
    _REG_Wr02(CTOP_O26Bx_SHDW(_m),_r##_B0,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_O26Bx_Wr03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
    _REG_Wr03(CTOP_O26Bx_SHDW(_m),_r##_B0,_f01,_v01,_f02,_v02,_f03,_v03)

#else                           /* USE_O26_FAKE_CTOP_REGS */

#warning +++ Fake O26 CTOP !! see USE_O26_FAKE_CTOP_REGS in your Makefile. see SICDTV-12300

#define CTOP_O26Ax_SHDW(_m)
#define CTOP_O26Ax_PHYS(_m)
#define CTOP_CTRL_O26Ax_RdFL(_m,_r)
#define CTOP_CTRL_O26Ax_WrFL(_m,_r)
#define CTOP_CTRL_O26Ax_Rd(_m,_r)   (0)
#define CTOP_CTRL_O26Ax_Wr(_m,_r,_v)
#define CTOP_CTRL_O26Ax_RdFd(_m,_r,_f01)
#define CTOP_CTRL_O26Ax_Rd01(_m,_r,_f01,_v01)
#define CTOP_CTRL_O26Ax_Rd02(_m,_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_O26Ax_Rd03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03)
#define CTOP_CTRL_O26Ax_Wr01(_m,_r,_f01,_v01)
#define CTOP_CTRL_O26Ax_Wr02(_m,_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_O26Ax_Wr03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define CTOP_O26Bx_SHDW(_m)
#define CTOP_O26Bx_PHYS(_m)

#define CTOP_CTRL_O26Bx_RdFL(_m,_r)
#define CTOP_CTRL_O26Bx_WrFL(_m,_r)

#define CTOP_CTRL_O26Bx_Rd(_m,_r)
#define CTOP_CTRL_O26Bx_Wr(_m,_r,_v)

#define CTOP_CTRL_O26Bx_RdFd(_m,_r,_f01)
#define CTOP_CTRL_O26Bx_Rd01(_m,_r,_f01,_v01)
#define CTOP_CTRL_O26Bx_Rd02(_m,_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_O26Bx_Rd03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03)

#define CTOP_CTRL_O26Bx_Wr01(_m,_r,_f01,_v01)
#define CTOP_CTRL_O26Bx_Wr02(_m,_r,_f01,_v01,_f02,_v02)
#define CTOP_CTRL_O26Bx_Wr03(_m,_r,_f01,_v01,_f02,_v02,_f03,_v03)

#endif

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
    union
    {
        CTOP_REG_O26A0_T a0;
        UINT32 b0;      // dummy, not used
    } shdw;

    union
    {
        CTOP_REG_O26A0_T a0;
        UINT32 b0;      // dummy, not used
    } phys;
} CTOP_CTRL_REG_O26_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
extern CTOP_CTRL_REG_O26_T gCTOP_CTRL_O26;

#define CTOP_CTRL_O26Ax_READ(m,offset)  \
({ \
    UINT32 v = 0; \
    if(offset < sizeof(O26_A0_##m##_TYPE)) { \
        v = _REG_OfsRd(gCTOP_CTRL_O26.shdw.a0.m, gCTOP_CTRL_O26.phys.a0.m, offset); \
    } \
    v; \
})

#define CTOP_CTRL_O26Ax_WRITE(m,offset,value)   \
do { \
    if(offset < sizeof(O26_A0_##m##_TYPE)) { \
        _REG_OfsWr(gCTOP_CTRL_O26.shdw.a0.m, gCTOP_CTRL_O26.phys.a0.m, offset, value); \
    } \
} while(0)

#endif                          /* __CTOP_CTRL_REG_O26_H__ */
/**  @} */
