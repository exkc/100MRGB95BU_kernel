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
#ifndef  BE_REG_DPE_M23_INC
#define  BE_REG_DPE_M23_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "be_reg_mac.h"
#include "be_reg_dpe_m23a0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DPE_LED_M23_RdFL(_r)                  BE_FN_CHIP_RdFL(DPE_LED, M23, _r)
#define DPE_LED_M23_WrFL(_r)                  BE_FN_CHIP_WrFL(DPE_LED, M23, _r)
#define DPE_LED_M23_Rd(_r)                    BE_FN_CHIP_Rd32(DPE_LED, M23, _r)
#define DPE_LED_M23_Wr(_r, _v)                BE_FN_CHIP_Wr32(DPE_LED, M23, _r, _v)
#define DPE_LED_M23_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(DPE_LED, M23, _r, _f01, _v01)
#define DPE_LED_M23_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(DPE_LED, M23, _r, _f01, _v01)
#define DPE_LED_M23_FLRd(_r, _v)              BE_FN_CHIP_FLRd(DPE_LED, M23, _r, _v)
#define DPE_LED_M23_FLWr(_r, _v)              BE_FN_CHIP_FLWr(DPE_LED, M23, _r, _v)
#define DPE_LED_M23_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(DPE_LED, M23, _r, _f01, _v01)
#define DPE_LED_M23_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(DPE_LED, M23, _r, _f01, _v01)

/*#define DPE_OLED_M23_RdFL(_r)                  BE_FN_CHIP_RdFL(DPE_OLED, M23, _r)
#define DPE_OLED_M23_WrFL(_r)                  BE_FN_CHIP_WrFL(DPE_OLED, M23, _r)
#define DPE_OLED_M23_Rd(_r)                    BE_FN_CHIP_Rd32(DPE_OLED, M23, _r)
#define DPE_OLED_M23_Wr(_r, _v)                BE_FN_CHIP_Wr32(DPE_OLED, M23, _r, _v)
#define DPE_OLED_M23_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(DPE_OLED, M23, _r, _f01, _v01)
#define DPE_OLED_M23_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(DPE_OLED, M23, _r, _f01, _v01)
#define DPE_OLED_M23_FLRd(_r, _v)              BE_FN_CHIP_FLRd(DPE_OLED, M23, _r, _v)
#define DPE_OLED_M23_FLWr(_r, _v)              BE_FN_CHIP_FLWr(DPE_OLED, M23, _r, _v)
#define DPE_OLED_M23_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(DPE_OLED, M23, _r, _f01, _v01)
#define DPE_OLED_M23_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(DPE_OLED, M23, _r, _f01, _v01)*/

#define PE_PCC_M23_RdFL(_r)                   BE_FN_CHIP_RdFL(PE_PCC, M23, _r)
#define PE_PCC_M23_WrFL(_r)                   BE_FN_CHIP_WrFL(PE_PCC, M23, _r)
#define PE_PCC_M23_Rd(_r)                     BE_FN_CHIP_Rd32(PE_PCC, M23, _r)
#define PE_PCC_M23_Wr(_r, _v)                 BE_FN_CHIP_Wr32(PE_PCC, M23, _r, _v)
#define PE_PCC_M23_Rd01(_r, _f01, _v01)       BE_FN_CHIP_Rd01(PE_PCC, M23, _r, _f01, _v01)
#define PE_PCC_M23_Wr01(_r, _f01, _v01)       BE_FN_CHIP_Wr01(PE_PCC, M23, _r, _f01, _v01)
#define PE_PCC_M23_FLRd(_r, _v)               BE_FN_CHIP_FLRd(PE_PCC, M23, _r, _v)
#define PE_PCC_M23_FLWr(_r, _v)               BE_FN_CHIP_FLWr(PE_PCC, M23, _r, _v)
#define PE_PCC_M23_FLRf(_r, _f01, _v01)       BE_FN_CHIP_FLRf(PE_PCC, M23, _r, _f01, _v01)
#define PE_PCC_M23_FLWf(_r, _f01, _v01)       BE_FN_CHIP_FLWf(PE_PCC, M23, _r, _f01, _v01)

#define L3D_M23_RdFL(_r)                   	  BE_FN_CHIP_RdFL(L3D, M23, _r)
#define L3D_M23_Rd(_r)                     	  BE_FN_CHIP_Rd32(L3D, M23, _r)
#define L3D_M23_Rd01(_r, _f01, _v01)       	  BE_FN_CHIP_Rd01(L3D, M23, _r, _f01, _v01)

/*#define PE_OSD_M23_RdFL(_r)                   BE_FN_CHIP_RdFL(PE_OSD, M23, _r)
#define PE_OSD_M23_WrFL(_r)                   BE_FN_CHIP_WrFL(PE_OSD, M23, _r)
#define PE_OSD_M23_Rd(_r)                     BE_FN_CHIP_Rd32(PE_OSD, M23, _r)
#define PE_OSD_M23_Wr(_r, _v)                 BE_FN_CHIP_Wr32(PE_OSD, M23, _r, _v)
#define PE_OSD_M23_Rd01(_r, _f01, _v01)       BE_FN_CHIP_Rd01(PE_OSD, M23, _r, _f01, _v01)
#define PE_OSD_M23_Wr01(_r, _f01, _v01)       BE_FN_CHIP_Wr01(PE_OSD, M23, _r, _f01, _v01)
#define PE_OSD_M23_FLRd(_r, _v)               BE_FN_CHIP_FLRd(PE_OSD, M23, _r, _v)
#define PE_OSD_M23_FLWr(_r, _v)               BE_FN_CHIP_FLWr(PE_OSD, M23, _r, _v)
#define PE_OSD_M23_FLRf(_r, _f01, _v01)       BE_FN_CHIP_FLRf(PE_OSD, M23, _r, _f01, _v01)
#define PE_OSD_M23_FLWf(_r, _f01, _v01)       BE_FN_CHIP_FLWf(PE_OSD, M23, _r, _f01, _v01)

#define DPE_UCR_M23_RdFL(_r)                  BE_FN_CHIP_RdFL(DPE_UCR, M23, _r)
#define DPE_UCR_M23_WrFL(_r)                  BE_FN_CHIP_WrFL(DPE_UCR, M23, _r)
#define DPE_UCR_M23_Rd(_r)                    BE_FN_CHIP_Rd32(DPE_UCR, M23, _r)
#define DPE_UCR_M23_Wr(_r, _v)                BE_FN_CHIP_Wr32(DPE_UCR, M23, _r, _v)
#define DPE_UCR_M23_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(DPE_UCR, M23, _r, _f01, _v01)
#define DPE_UCR_M23_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(DPE_UCR, M23, _r, _f01, _v01)
#define DPE_UCR_M23_FLRd(_r, _v)              BE_FN_CHIP_FLRd(DPE_UCR, M23, _r, _v)
#define DPE_UCR_M23_FLWr(_r, _v)              BE_FN_CHIP_FLWr(DPE_UCR, M23, _r, _v)
#define DPE_UCR_M23_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(DPE_UCR, M23, _r, _f01, _v01)
#define DPE_UCR_M23_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(DPE_UCR, M23, _r, _f01, _v01)*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        DPE_LED_REG_M23A0_T *a0;
        DPE_LED_REG_M23A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DPE_LED_REG_M23A0_T *a0;
        volatile DPE_LED_REG_M23A0_T *b0;
    } phys;
} DPE_LED_REG_M23_T;

/*typedef struct {
    union {
        UINT32          *addr;
        DPE_OLED_REG_M23A0_T *a0;
        DPE_OLED_REG_M23A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DPE_OLED_REG_M23A0_T *a0;
        volatile DPE_OLED_REG_M23A0_T *b0;
    } phys;
} DPE_OLED_REG_M23_T;*/

typedef struct {
    union {
        UINT32          *addr;
        PE_PCC_REG_M23A0_T *a0;
        PE_PCC_REG_M23A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_PCC_REG_M23A0_T *a0;
        volatile PE_PCC_REG_M23A0_T *b0;
    } phys;
} PE_PCC_REG_M23_T;

typedef struct {
    union {
        UINT32          *addr;
        L3D_REG_M23A0_T *a0;
        L3D_REG_M23A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile L3D_REG_M23A0_T *a0;
        volatile L3D_REG_M23A0_T *b0;
    } phys;
} L3D_REG_M23_T;

/*typedef struct {
    union {
        UINT32          *addr;
		PE_OSD0_IMAGE_REG_M23A0_T *a0;
		PE_OSD0_IMAGE_REG_M23A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
		volatile PE_OSD0_IMAGE_REG_M23A0_T *a0;
		volatile PE_OSD0_IMAGE_REG_M23A0_T *b0;
    } phys;
} PE_OSD_REG_M23_T;

typedef struct {
    union {
        UINT32          *addr;
        DPE_UCR_REG_M23A0_T *a0;
        DPE_UCR_REG_M23A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DPE_UCR_REG_M23A0_T *a0;
        volatile DPE_UCR_REG_M23A0_T *b0;
    } phys;
} DPE_UCR_REG_M23_T;*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef BE_REG_DPE_M23_INC  ----- */
/**  @} */
