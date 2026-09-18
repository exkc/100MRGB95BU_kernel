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
#ifndef  BE_REG_DPE_O20_INC
#define  BE_REG_DPE_O20_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "be_reg_mac.h"
#include "be_reg_dpe_o20a0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DPE_LED_O20_RdFL(_r)                  BE_FN_CHIP_RdFL(DPE_LED, O20, _r)
#define DPE_LED_O20_WrFL(_r)                  BE_FN_CHIP_WrFL(DPE_LED, O20, _r)
#define DPE_LED_O20_Rd(_r)                    BE_FN_CHIP_Rd32(DPE_LED, O20, _r)
#define DPE_LED_O20_Wr(_r, _v)                BE_FN_CHIP_Wr32(DPE_LED, O20, _r, _v)
#define DPE_LED_O20_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(DPE_LED, O20, _r, _f01, _v01)
#define DPE_LED_O20_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(DPE_LED, O20, _r, _f01, _v01)
#define DPE_LED_O20_FLRd(_r, _v)              BE_FN_CHIP_FLRd(DPE_LED, O20, _r, _v)
#define DPE_LED_O20_FLWr(_r, _v)              BE_FN_CHIP_FLWr(DPE_LED, O20, _r, _v)
#define DPE_LED_O20_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(DPE_LED, O20, _r, _f01, _v01)
#define DPE_LED_O20_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(DPE_LED, O20, _r, _f01, _v01)

#define DPE_OLED_O20_RdFL(_r)                  BE_FN_CHIP_RdFL(DPE_OLED, O20, _r)
#define DPE_OLED_O20_WrFL(_r)                  BE_FN_CHIP_WrFL(DPE_OLED, O20, _r)
#define DPE_OLED_O20_Rd(_r)                    BE_FN_CHIP_Rd32(DPE_OLED, O20, _r)
#define DPE_OLED_O20_Wr(_r, _v)                BE_FN_CHIP_Wr32(DPE_OLED, O20, _r, _v)
#define DPE_OLED_O20_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(DPE_OLED, O20, _r, _f01, _v01)
#define DPE_OLED_O20_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(DPE_OLED, O20, _r, _f01, _v01)
#define DPE_OLED_O20_FLRd(_r, _v)              BE_FN_CHIP_FLRd(DPE_OLED, O20, _r, _v)
#define DPE_OLED_O20_FLWr(_r, _v)              BE_FN_CHIP_FLWr(DPE_OLED, O20, _r, _v)
#define DPE_OLED_O20_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(DPE_OLED, O20, _r, _f01, _v01)
#define DPE_OLED_O20_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(DPE_OLED, O20, _r, _f01, _v01)

#define PE_PCC_O20_RdFL(_r)                   BE_FN_CHIP_RdFL(PE_PCC, O20, _r)
#define PE_PCC_O20_WrFL(_r)                   BE_FN_CHIP_WrFL(PE_PCC, O20, _r)
#define PE_PCC_O20_Rd(_r)                     BE_FN_CHIP_Rd32(PE_PCC, O20, _r)
#define PE_PCC_O20_Wr(_r, _v)                 BE_FN_CHIP_Wr32(PE_PCC, O20, _r, _v)
#define PE_PCC_O20_Rd01(_r, _f01, _v01)       BE_FN_CHIP_Rd01(PE_PCC, O20, _r, _f01, _v01)
#define PE_PCC_O20_Wr01(_r, _f01, _v01)       BE_FN_CHIP_Wr01(PE_PCC, O20, _r, _f01, _v01)
#define PE_PCC_O20_FLRd(_r, _v)               BE_FN_CHIP_FLRd(PE_PCC, O20, _r, _v)
#define PE_PCC_O20_FLWr(_r, _v)               BE_FN_CHIP_FLWr(PE_PCC, O20, _r, _v)
#define PE_PCC_O20_FLRf(_r, _f01, _v01)       BE_FN_CHIP_FLRf(PE_PCC, O20, _r, _f01, _v01)
#define PE_PCC_O20_FLWf(_r, _f01, _v01)       BE_FN_CHIP_FLWf(PE_PCC, O20, _r, _f01, _v01)

#define L3D_O20_RdFL(_r)                   	  BE_FN_CHIP_RdFL(L3D, O20, _r)
#define L3D_O20_Rd(_r)                     	  BE_FN_CHIP_Rd32(L3D, O20, _r)
#define L3D_O20_Rd01(_r, _f01, _v01)       	  BE_FN_CHIP_Rd01(L3D, O20, _r, _f01, _v01)

#define PE_OSD_O20_RdFL(_r)                   BE_FN_CHIP_RdFL(PE_OSD, O20, _r)
#define PE_OSD_O20_WrFL(_r)                   BE_FN_CHIP_WrFL(PE_OSD, O20, _r)
#define PE_OSD_O20_Rd(_r)                     BE_FN_CHIP_Rd32(PE_OSD, O20, _r)
#define PE_OSD_O20_Wr(_r, _v)                 BE_FN_CHIP_Wr32(PE_OSD, O20, _r, _v)
#define PE_OSD_O20_Rd01(_r, _f01, _v01)       BE_FN_CHIP_Rd01(PE_OSD, O20, _r, _f01, _v01)
#define PE_OSD_O20_Wr01(_r, _f01, _v01)       BE_FN_CHIP_Wr01(PE_OSD, O20, _r, _f01, _v01)
#define PE_OSD_O20_FLRd(_r, _v)               BE_FN_CHIP_FLRd(PE_OSD, O20, _r, _v)
#define PE_OSD_O20_FLWr(_r, _v)               BE_FN_CHIP_FLWr(PE_OSD, O20, _r, _v)
#define PE_OSD_O20_FLRf(_r, _f01, _v01)       BE_FN_CHIP_FLRf(PE_OSD, O20, _r, _f01, _v01)
#define PE_OSD_O20_FLWf(_r, _f01, _v01)       BE_FN_CHIP_FLWf(PE_OSD, O20, _r, _f01, _v01)

#define DPE_UCR_O20_RdFL(_r)                  BE_FN_CHIP_RdFL(DPE_UCR, O20, _r)
#define DPE_UCR_O20_WrFL(_r)                  BE_FN_CHIP_WrFL(DPE_UCR, O20, _r)
#define DPE_UCR_O20_Rd(_r)                    BE_FN_CHIP_Rd32(DPE_UCR, O20, _r)
#define DPE_UCR_O20_Wr(_r, _v)                BE_FN_CHIP_Wr32(DPE_UCR, O20, _r, _v)
#define DPE_UCR_O20_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(DPE_UCR, O20, _r, _f01, _v01)
#define DPE_UCR_O20_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(DPE_UCR, O20, _r, _f01, _v01)
#define DPE_UCR_O20_FLRd(_r, _v)              BE_FN_CHIP_FLRd(DPE_UCR, O20, _r, _v)
#define DPE_UCR_O20_FLWr(_r, _v)              BE_FN_CHIP_FLWr(DPE_UCR, O20, _r, _v)
#define DPE_UCR_O20_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(DPE_UCR, O20, _r, _f01, _v01)
#define DPE_UCR_O20_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(DPE_UCR, O20, _r, _f01, _v01)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        DPE_LED_REG_O20A0_T *a0;
        DPE_LED_REG_O20A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DPE_LED_REG_O20A0_T *a0;
        volatile DPE_LED_REG_O20A0_T *b0;
    } phys;
} DPE_LED_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
        DPE_OLED_REG_O20A0_T *a0;
        DPE_OLED_REG_O20A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DPE_OLED_REG_O20A0_T *a0;
        volatile DPE_OLED_REG_O20A0_T *b0;
    } phys;
} DPE_OLED_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_PCC_REG_O20A0_T *a0;
        PE_PCC_REG_O20A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_PCC_REG_O20A0_T *a0;
        volatile PE_PCC_REG_O20A0_T *b0;
    } phys;
} PE_PCC_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
        L3D_REG_O20A0_T *a0;
        L3D_REG_O20A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile L3D_REG_O20A0_T *a0;
        volatile L3D_REG_O20A0_T *b0;
    } phys;
} L3D_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
		PE_OSD0_IMAGE_REG_O20A0_T *a0;
		PE_OSD0_IMAGE_REG_O20A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
		volatile PE_OSD0_IMAGE_REG_O20A0_T *a0;
		volatile PE_OSD0_IMAGE_REG_O20A0_T *b0;
    } phys;
} PE_OSD_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
        DPE_UCR_REG_O20A0_T *a0;
        DPE_UCR_REG_O20A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DPE_UCR_REG_O20A0_T *a0;
        volatile DPE_UCR_REG_O20A0_T *b0;
    } phys;
} DPE_UCR_REG_O20_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef BE_REG_DPE_O20_INC  ----- */
/**  @} */
