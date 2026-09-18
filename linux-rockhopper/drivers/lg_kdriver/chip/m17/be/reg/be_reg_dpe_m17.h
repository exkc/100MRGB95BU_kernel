/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

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
 * date       2016.05.03
 * note       Additional information.
 *
 * @addtogroup BE
 * @{
 */
#ifndef  BE_REG_DPE_M17_INC
#define  BE_REG_DPE_M17_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "be_reg_mac.h"
#include "be_reg_dpe_m17a0.h"
#include "be_reg_dpe_m17c0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DPE_LED_M17_RdFL(_r)                  BE_FN_CHIP_RdFL(DPE_LED, M17, _r)
#define DPE_LED_M17_WrFL(_r)                  BE_FN_CHIP_WrFL(DPE_LED, M17, _r)
#define DPE_LED_M17_Rd(_r)                    BE_FN_CHIP_Rd32(DPE_LED, M17, _r)
#define DPE_LED_M17_Wr(_r, _v)                BE_FN_CHIP_Wr32(DPE_LED, M17, _r, _v)
#define DPE_LED_M17_Rd01(_r, _f01, _v01)      BE_FN_CHIP_Rd01(DPE_LED, M17, _r, _f01, _v01)
#define DPE_LED_M17_Wr01(_r, _f01, _v01)      BE_FN_CHIP_Wr01(DPE_LED, M17, _r, _f01, _v01)
#define DPE_LED_M17_FLRd(_r, _v)              BE_FN_CHIP_FLRd(DPE_LED, M17, _r, _v)
#define DPE_LED_M17_FLWr(_r, _v)              BE_FN_CHIP_FLWr(DPE_LED, M17, _r, _v)
#define DPE_LED_M17_FLRf(_r, _f01, _v01)      BE_FN_CHIP_FLRf(DPE_LED, M17, _r, _f01, _v01)
#define DPE_LED_M17_FLWf(_r, _f01, _v01)      BE_FN_CHIP_FLWf(DPE_LED, M17, _r, _f01, _v01)

#define PE_PCC_M17_RdFL(_r)                   BE_FN_CHIP_RdFL(PE_PCC, M17, _r)
#define PE_PCC_M17_WrFL(_r)                   BE_FN_CHIP_WrFL(PE_PCC, M17, _r)
#define PE_PCC_M17_Rd(_r)                     BE_FN_CHIP_Rd32(PE_PCC, M17, _r)
#define PE_PCC_M17_Wr(_r, _v)                 BE_FN_CHIP_Wr32(PE_PCC, M17, _r, _v)
#define PE_PCC_M17_Rd01(_r, _f01, _v01)       BE_FN_CHIP_Rd01(PE_PCC, M17, _r, _f01, _v01)
#define PE_PCC_M17_Wr01(_r, _f01, _v01)       BE_FN_CHIP_Wr01(PE_PCC, M17, _r, _f01, _v01)
#define PE_PCC_M17_FLRd(_r, _v)               BE_FN_CHIP_FLRd(PE_PCC, M17, _r, _v)
#define PE_PCC_M17_FLWr(_r, _v)               BE_FN_CHIP_FLWr(PE_PCC, M17, _r, _v)
#define PE_PCC_M17_FLRf(_r, _f01, _v01)       BE_FN_CHIP_FLRf(PE_PCC, M17, _r, _f01, _v01)
#define PE_PCC_M17_FLWf(_r, _f01, _v01)       BE_FN_CHIP_FLWf(PE_PCC, M17, _r, _f01, _v01)

#define PE_PCC_M17C0_RdFL(_r)                   BE_FN_CHIP_VER_RdFL(PE_PCC, M17, c0, _r)
#define PE_PCC_M17C0_WrFL(_r)                   BE_FN_CHIP_VER_WrFL(PE_PCC, M17, c0, _r)
#define PE_PCC_M17C0_Rd(_r)                     BE_FN_CHIP_VER_Rd32(PE_PCC, M17, c0, _r)
#define PE_PCC_M17C0_Wr(_r, _v)                 BE_FN_CHIP_VER_Wr32(PE_PCC, M17, c0, _r, _v)
#define PE_PCC_M17C0_Rd01(_r, _f01, _v01)       BE_FN_CHIP_VER_Rd01(PE_PCC, M17, c0, _r, _f01, _v01)
#define PE_PCC_M17C0_Wr01(_r, _f01, _v01)       BE_FN_CHIP_VER_Wr01(PE_PCC, M17, c0, _r, _f01, _v01)
#define PE_PCC_M17C0_FLRd(_r, _v)               BE_FN_CHIP_VER_FLRd(PE_PCC, M17, c0, _r, _v)
#define PE_PCC_M17C0_FLWr(_r, _v)               BE_FN_CHIP_VER_FLWr(PE_PCC, M17, c0, _r, _v)
#define PE_PCC_M17C0_FLRf(_r, _f01, _v01)       BE_FN_CHIP_VER_FLRf(PE_PCC, M17, c0, _r, _f01, _v01)
#define PE_PCC_M17C0_FLWf(_r, _f01, _v01)       BE_FN_CHIP_VER_FLWf(PE_PCC, M17, c0, _r, _f01, _v01)

#define L3D_M17C0_RdFL(_r)                   	  BE_FN_CHIP_VER_RdFL(L3D, M17, c0, _r)
#define L3D_M17C0_Rd(_r)                     	  BE_FN_CHIP_VER_Rd32(L3D, M17, c0, _r)
#define L3D_M17C0_Rd01(_r, _f01, _v01)       	  BE_FN_CHIP_VER_Rd01(L3D, M17, c0, _r, _f01, _v01)

#define PE_OSD_M17C0_RdFL(_r)                   BE_FN_CHIP_VER_RdFL(PE_OSD, M17, c0, _r)
#define PE_OSD_M17C0_WrFL(_r)                   BE_FN_CHIP_VER_WrFL(PE_OSD, M17, c0, _r)
#define PE_OSD_M17C0_Rd(_r)                     BE_FN_CHIP_VER_Rd32(PE_OSD, M17, c0, _r)
#define PE_OSD_M17C0_Wr(_r, _v)                 BE_FN_CHIP_VER_Wr32(PE_OSD, M17, c0, _r, _v)
#define PE_OSD_M17C0_Rd01(_r, _f01, _v01)       BE_FN_CHIP_VER_Rd01(PE_OSD, M17, c0, _r, _f01, _v01)
#define PE_OSD_M17C0_Wr01(_r, _f01, _v01)       BE_FN_CHIP_VER_Wr01(PE_OSD, M17, c0, _r, _f01, _v01)
#define PE_OSD_M17C0_FLRd(_r, _v)               BE_FN_CHIP_VER_FLRd(PE_OSD, M17, c0, _r, _v)
#define PE_OSD_M17C0_FLWr(_r, _v)               BE_FN_CHIP_VER_FLWr(PE_OSD, M17, c0, _r, _v)
#define PE_OSD_M17C0_FLRf(_r, _f01, _v01)       BE_FN_CHIP_VER_FLRf(PE_OSD, M17, c0, _r, _f01, _v01)
#define PE_OSD_M17C0_FLWf(_r, _f01, _v01)       BE_FN_CHIP_VER_FLWf(PE_OSD, M17, c0, _r, _f01, _v01)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        DPE_LED_REG_M17A0_T *a0;
        DPE_LED_REG_M17A0_T *b0;
		DPE_LED_REG_M17C0_T *c0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DPE_LED_REG_M17A0_T *a0;
        volatile DPE_LED_REG_M17A0_T *b0;
		volatile DPE_LED_REG_M17C0_T *c0;
    } phys;
} DPE_LED_REG_M17_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_PCC_REG_M17A0_T *a0;
        PE_PCC_REG_M17A0_T *b0;
		PE_PCC_REG_M17C0_T *c0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_PCC_REG_M17A0_T *a0;
        volatile PE_PCC_REG_M17A0_T *b0;
		volatile PE_PCC_REG_M17C0_T *c0;
    } phys;
} PE_PCC_REG_M17_T;

typedef struct {
    union {
        UINT32          *addr;
        L3D_REG_M17C0_T *c0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile L3D_REG_M17C0_T *c0;
    } phys;
} L3D_REG_M17_T;

typedef struct {
    union {
        UINT32          *addr;
		PE_OSD0_IMAGE_REG_M17C0_T *c0;
    } shdw;

    union {
        volatile UINT32          *addr;
		volatile PE_OSD0_IMAGE_REG_M17C0_T *c0;
    } phys;
} PE_OSD_REG_M17_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef BE_REG_DPE_M17_INC  ----- */
/**  @} */
