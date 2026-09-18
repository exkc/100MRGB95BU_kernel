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
#ifndef  BE_REG_DPE_O26_INC
#define  BE_REG_DPE_O26_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "be_reg_mac.h"
#include "be_reg_dpe_o26a0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define BE_LED_O26_RdFL(_r)                  BE_FN_CHIP_RdFL(BE_LED, O26, _r)
#define BE_LED_O26_WrFL(_r)                  BE_FN_CHIP_WrFL(BE_LED, O26, _r)
#define BE_LED_O26_Rd(_r)                    BE_FN_CHIP_Rd32(BE_LED, O26, _r)
#define BE_LED_O26_Wr(_r, _v)                BE_FN_CHIP_Wr32(BE_LED, O26, _r, _v)
#define BE_LED_O26_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(BE_LED, O26, _r, _f01, _v01)
#define BE_LED_O26_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(BE_LED, O26, _r, _f01, _v01)
#define BE_LED_O26_FLRd(_r, _v)              BE_FN_CHIP_FLRd(BE_LED, O26, _r, _v)
#define BE_LED_O26_FLWr(_r, _v)              BE_FN_CHIP_FLWr(BE_LED, O26, _r, _v)
#define BE_LED_O26_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(BE_LED, O26, _r, _f01, _v01)
#define BE_LED_O26_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(BE_LED, O26, _r, _f01, _v01)

#define BE_OLED_O26_RdFL(_r)                  BE_FN_CHIP_RdFL(BE_OLED, O26, _r)
#define BE_OLED_O26_WrFL(_r)                  BE_FN_CHIP_WrFL(BE_OLED, O26, _r)
#define BE_OLED_O26_Rd(_r)                    BE_FN_CHIP_Rd32(BE_OLED, O26, _r)
#define BE_OLED_O26_Wr(_r, _v)                BE_FN_CHIP_Wr32(BE_OLED, O26, _r, _v)
#define BE_OLED_O26_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(BE_OLED, O26, _r, _f01, _v01)
#define BE_OLED_O26_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(BE_OLED, O26, _r, _f01, _v01)
#define BE_OLED_O26_FLRd(_r, _v)              BE_FN_CHIP_FLRd(BE_OLED, O26, _r, _v)
#define BE_OLED_O26_FLWr(_r, _v)              BE_FN_CHIP_FLWr(BE_OLED, O26, _r, _v)
#define BE_OLED_O26_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(BE_OLED, O26, _r, _f01, _v01)
#define BE_OLED_O26_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(BE_OLED, O26, _r, _f01, _v01)

#define BE_PCC_O26_RdFL(_r)                   BE_FN_CHIP_RdFL(BE_PCC, O26, _r)
#define BE_PCC_O26_WrFL(_r)                   BE_FN_CHIP_WrFL(BE_PCC, O26, _r)
#define BE_PCC_O26_Rd(_r)                     BE_FN_CHIP_Rd32(BE_PCC, O26, _r)
#define BE_PCC_O26_Wr(_r, _v)                 BE_FN_CHIP_Wr32(BE_PCC, O26, _r, _v)
#define BE_PCC_O26_Rd01(_r, _f01, _v01)       BE_FN_CHIP_Rd01(BE_PCC, O26, _r, _f01, _v01)
#define BE_PCC_O26_Wr01(_r, _f01, _v01)       BE_FN_CHIP_Wr01(BE_PCC, O26, _r, _f01, _v01)
#define BE_PCC_O26_FLRd(_r, _v)               BE_FN_CHIP_FLRd(BE_PCC, O26, _r, _v)
#define BE_PCC_O26_FLWr(_r, _v)               BE_FN_CHIP_FLWr(BE_PCC, O26, _r, _v)
#define BE_PCC_O26_FLRf(_r, _f01, _v01)       BE_FN_CHIP_FLRf(BE_PCC, O26, _r, _f01, _v01)
#define BE_PCC_O26_FLWf(_r, _f01, _v01)       BE_FN_CHIP_FLWf(BE_PCC, O26, _r, _f01, _v01)

#define BE_PCC_WIN_O26_RdFL(_r)                   BE_FN_CHIP_RdFL(BE_PCC_WIN, O26, _r)
#define BE_PCC_WIN_O26_WrFL(_r)                   BE_FN_CHIP_WrFL(BE_PCC_WIN, O26, _r)
#define BE_PCC_WIN_O26_Rd(_r)                     BE_FN_CHIP_Rd32(BE_PCC_WIN, O26, _r)
#define BE_PCC_WIN_O26_Wr(_r, _v)                 BE_FN_CHIP_Wr32(BE_PCC_WIN, O26, _r, _v)
#define BE_PCC_WIN_O26_Rd01(_r, _f01, _v01)       BE_FN_CHIP_Rd01(BE_PCC_WIN, O26, _r, _f01, _v01)
#define BE_PCC_WIN_O26_Wr01(_r, _f01, _v01)       BE_FN_CHIP_Wr01(BE_PCC_WIN, O26, _r, _f01, _v01)
#define BE_PCC_WIN_O26_FLRd(_r, _v)               BE_FN_CHIP_FLRd(BE_PCC_WIN, O26, _r, _v)
#define BE_PCC_WIN_O26_FLWr(_r, _v)               BE_FN_CHIP_FLWr(BE_PCC_WIN, O26, _r, _v)
#define BE_PCC_WIN_O26_FLRf(_r, _f01, _v01)       BE_FN_CHIP_FLRf(BE_PCC_WIN, O26, _r, _f01, _v01)
#define BE_PCC_WIN_O26_FLWf(_r, _f01, _v01)       BE_FN_CHIP_FLWf(BE_PCC_WIN, O26, _r, _f01, _v01)

#define BE_L3D_O26_RdFL(_r)                   BE_FN_CHIP_RdFL(BE_L3D, O26, _r)
#define BE_L3D_O26_WrFL(_r)                   BE_FN_CHIP_WrFL(BE_L3D, O26, _r)
#define BE_L3D_O26_Rd(_r)                     BE_FN_CHIP_Rd32(BE_L3D, O26, _r)
#define BE_L3D_O26_Wr(_r, _v)                 BE_FN_CHIP_Wr32(BE_L3D, O26, _r, _v)
#define BE_L3D_O26_Rd01(_r, _f01, _v01)       BE_FN_CHIP_Rd01(BE_L3D, O26, _r, _f01, _v01)
#define BE_L3D_O26_Wr01(_r, _f01, _v01)       BE_FN_CHIP_Wr01(BE_L3D, O26, _r, _f01, _v01)
#define BE_L3D_O26_FLRd(_r, _v)               BE_FN_CHIP_FLRd(BE_L3D, O26, _r, _v)
#define BE_L3D_O26_FLWr(_r, _v)               BE_FN_CHIP_FLWr(BE_L3D, O26, _r, _v)
#define BE_L3D_O26_FLRf(_r, _f01, _v01)       BE_FN_CHIP_FLRf(BE_L3D, O26, _r, _f01, _v01)
#define BE_L3D_O26_FLWf(_r, _f01, _v01)       BE_FN_CHIP_FLWf(BE_L3D, O26, _r, _f01, _v01)

#define BE_OSD_O26_RdFL(_r)                   BE_FN_CHIP_RdFL(BE_OSD, O26, _r)
#define BE_OSD_O26_WrFL(_r)                   BE_FN_CHIP_WrFL(BE_OSD, O26, _r)
#define BE_OSD_O26_Rd(_r)                     BE_FN_CHIP_Rd32(BE_OSD, O26, _r)
#define BE_OSD_O26_Wr(_r, _v)                 BE_FN_CHIP_Wr32(BE_OSD, O26, _r, _v)
#define BE_OSD_O26_Rd01(_r, _f01, _v01)       BE_FN_CHIP_Rd01(BE_OSD, O26, _r, _f01, _v01)
#define BE_OSD_O26_Wr01(_r, _f01, _v01)       BE_FN_CHIP_Wr01(BE_OSD, O26, _r, _f01, _v01)
#define BE_OSD_O26_FLRd(_r, _v)               BE_FN_CHIP_FLRd(BE_OSD, O26, _r, _v)
#define BE_OSD_O26_FLWr(_r, _v)               BE_FN_CHIP_FLWr(BE_OSD, O26, _r, _v)
#define BE_OSD_O26_FLRf(_r, _f01, _v01)       BE_FN_CHIP_FLRf(BE_OSD, O26, _r, _f01, _v01)
#define BE_OSD_O26_FLWf(_r, _f01, _v01)       BE_FN_CHIP_FLWf(BE_OSD, O26, _r, _f01, _v01)

#define BE_UCR_O26_RdFL(_r)                  BE_FN_CHIP_RdFL(BE_UCR, O26, _r)
#define BE_UCR_O26_WrFL(_r)                  BE_FN_CHIP_WrFL(BE_UCR, O26, _r)
#define BE_UCR_O26_Rd(_r)                    BE_FN_CHIP_Rd32(BE_UCR, O26, _r)
#define BE_UCR_O26_Wr(_r, _v)                BE_FN_CHIP_Wr32(BE_UCR, O26, _r, _v)
#define BE_UCR_O26_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(BE_UCR, O26, _r, _f01, _v01)
#define BE_UCR_O26_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(BE_UCR, O26, _r, _f01, _v01)
#define BE_UCR_O26_FLRd(_r, _v)              BE_FN_CHIP_FLRd(BE_UCR, O26, _r, _v)
#define BE_UCR_O26_FLWr(_r, _v)              BE_FN_CHIP_FLWr(BE_UCR, O26, _r, _v)
#define BE_UCR_O26_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(BE_UCR, O26, _r, _f01, _v01)
#define BE_UCR_O26_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(BE_UCR, O26, _r, _f01, _v01)

#define BE_DEC_O26_RdFL(_r)                  BE_FN_CHIP_RdFL(BE_DEC, O26, _r)
#define BE_DEC_O26_WrFL(_r)                  BE_FN_CHIP_WrFL(BE_DEC, O26, _r)
#define BE_DEC_O26_Rd(_r)                    BE_FN_CHIP_Rd32(BE_DEC, O26, _r)
#define BE_DEC_O26_Wr(_r, _v)                BE_FN_CHIP_Wr32(BE_DEC, O26, _r, _v)
#define BE_DEC_O26_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(BE_DEC, O26, _r, _f01, _v01)
#define BE_DEC_O26_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(BE_DEC, O26, _r, _f01, _v01)
#define BE_DEC_O26_FLRd(_r, _v)              BE_FN_CHIP_FLRd(BE_DEC, O26, _r, _v)
#define BE_DEC_O26_FLWr(_r, _v)              BE_FN_CHIP_FLWr(BE_DEC, O26, _r, _v)
#define BE_DEC_O26_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(BE_DEC, O26, _r, _f01, _v01)
#define BE_DEC_O26_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(BE_DEC, O26, _r, _f01, _v01)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        BE_O26A0_REG_LED_T *a0;
        BE_O26A0_REG_LED_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile BE_O26A0_REG_LED_T *a0;
        volatile BE_O26A0_REG_LED_T *b0;
    } phys;
} BE_LED_REG_O26_T;

typedef struct {
    union {
        UINT32          *addr;
        BE_O26A0_REG_OLED_T *a0;
        BE_O26A0_REG_OLED_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile BE_O26A0_REG_OLED_T *a0;
        volatile BE_O26A0_REG_OLED_T *b0;
    } phys;
} BE_OLED_REG_O26_T;

typedef struct {
    union {
        UINT32          *addr;
        BE_O26A0_REG_CC_PE_PCC_T *a0;
        BE_O26A0_REG_CC_PE_PCC_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile BE_O26A0_REG_CC_PE_PCC_T *a0;
        volatile BE_O26A0_REG_CC_PE_PCC_T *b0;
    } phys;
} BE_PCC_REG_O26_T;

typedef struct {
    union {
        UINT32          *addr;
        BE_O26A0_REG_CC_PCC_WINCTRL_T *a0;
        BE_O26A0_REG_CC_PCC_WINCTRL_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile BE_O26A0_REG_CC_PCC_WINCTRL_T *a0;
        volatile BE_O26A0_REG_CC_PCC_WINCTRL_T *b0;
    } phys;
} BE_PCC_WIN_REG_O26_T;

typedef struct {
    union {
        UINT32          *addr;
        BE_O26A0_REG_L3D_L3D_CORE_CTRL_T *a0;
        BE_O26A0_REG_L3D_L3D_CORE_CTRL_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile BE_O26A0_REG_L3D_L3D_CORE_CTRL_T *a0;
        volatile BE_O26A0_REG_L3D_L3D_CORE_CTRL_T *b0;
    } phys;
} BE_L3D_REG_O26_T;

typedef struct {
    union {
        UINT32          *addr;
		BE_O26A0_REG_OSD_IMAGE0_1_REG_OSD0_GSR_CTRL_T *a0;
		BE_O26A0_REG_OSD_IMAGE0_1_REG_OSD0_GSR_CTRL_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
		volatile BE_O26A0_REG_OSD_IMAGE0_1_REG_OSD0_GSR_CTRL_T *a0;
		volatile BE_O26A0_REG_OSD_IMAGE0_1_REG_OSD0_GSR_CTRL_T *b0;
    } phys;
} BE_OSD_REG_O26_T;

typedef struct {
    union {
        UINT32          *addr;
        BE_O26A0_REG_UCR_T *a0;
        BE_O26A0_REG_UCR_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile BE_O26A0_REG_UCR_T *a0;
        volatile BE_O26A0_REG_UCR_T *b0;
    } phys;
} BE_UCR_REG_O26_T;

typedef struct {
    union {
        UINT32          *addr;
        BE_O26A0_REG_CCO_DEC_T *a0;
        BE_O26A0_REG_CCO_DEC_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile BE_O26A0_REG_CCO_DEC_T *a0;
        volatile BE_O26A0_REG_CCO_DEC_T *b0;
    } phys;
} BE_DEC_REG_O26_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef BE_REG_DPE_O26_INC  ----- */
/**  @} */
