/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2019 by LG Electronics Inc.

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
 * main driver implementation for BE device.
 * BE device will teach you how to make device driver with new platform.
 *
 * author     dj911.kim
 * version    1.0
 * date       2017.06.07
 * note       Additional information.
 *
 * @addtogroup BE
 * @{
 */
#ifndef  BE_REG_PWM_O26_INC
#define  BE_REG_PWM_O26_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "be_reg_mac.h"
#include "be_reg_pwm_o26a0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define BE_PWM_O26_RdFL(_r)                  BE_FN_CHIP_RdFL(BE_PWM, O26, _r)
#define BE_PWM_O26_WrFL(_r)                  BE_FN_CHIP_WrFL(BE_PWM, O26, _r)
#define BE_PWM_O26_Rd(_r)                    BE_FN_CHIP_Rd32(BE_PWM, O26, _r)
#define BE_PWM_O26_Wr(_r, _v)                BE_FN_CHIP_Wr32(BE_PWM, O26, _r, _v)
#define BE_PWM_O26_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(BE_PWM, O26, _r, _f01, _v01)
#define BE_PWM_O26_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(BE_PWM, O26, _r, _f01, _v01)
#define BE_PWM_O26_FLRd(_r, _v)              BE_FN_CHIP_FLRd(BE_PWM, O26, _r, _v)
#define BE_PWM_O26_FLWr(_r, _v)              BE_FN_CHIP_FLWr(BE_PWM, O26, _r, _v)
#define BE_PWM_O26_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(BE_PWM, O26, _r, _f01, _v01)
#define BE_PWM_O26_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(BE_PWM, O26, _r, _f01, _v01)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        BE_O26A0_REG_PWM_T *a0;
        BE_O26A0_REG_PWM_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile BE_O26A0_REG_PWM_T *a0;
        volatile BE_O26A0_REG_PWM_T *b0;
    } phys;
} BE_PWM_REG_O26_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef BE_REG_PWM_O26_INC  ----- */
/**  @} */

