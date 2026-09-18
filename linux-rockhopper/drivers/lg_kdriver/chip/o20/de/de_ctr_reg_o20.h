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

#ifndef  DE_CTR_REG_O20_INC
#define  DE_CTR_REG_O20_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_reg_mac.h"
#ifdef USE_KDRV_CODES_FOR_O20A0
#include "de_ctr_reg_o20a0.h"
#endif

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DE_CVC_O20_RdFL(_r)                         FN_CHIP_RdFL(DE_CVC, O20, _r)
#define DE_CVC_O20_WrFL(_r)                         FN_CHIP_WrFL(DE_CVC, O20, _r)
#define DE_CVC_O20_Rd(_r)                           FN_CHIP_Rd32(DE_CVC, O20, _r)
#define DE_CVC_O20_Wr(_r, _v)                       FN_CHIP_Wr32(DE_CVC, O20, _r, _v)
#define DE_CVC_O20_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_CVC, O20, _r, _f01, _v01)
#define DE_CVC_O20_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_CVC, O20, _r, _f01, _v01)
#define DE_CVC_O20_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_CVC, O20, _r, _f, _c, _m)
#define DE_CVC_O20_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_CVC, O20, _r, _f, _c, _v1, _v2)
#define DE_CVC_O20_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_CVC, O20, _r, _v)
#define DE_CVC_O20_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_CVC, O20, _r, _v)
#define DE_CVC_O20_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_CVC, O20, _r, _f01, _v01)
#define DE_CVC_O20_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_CVC, O20, _r, _f01, _v01)
#define DE_CVC_O20_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_CVC, O20, _r, _f, _c, _m)
#define DE_CVC_O20_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_CVC, O20, _r, _f, _c, _v1, _v2)

#define DE_VSD_O20_RdFL(_r)                         FN_CHIP_RdFL(DE_VSD, O20, _r)
#define DE_VSD_O20_WrFL(_r)                         FN_CHIP_WrFL(DE_VSD, O20, _r)
#define DE_VSD_O20_Rd(_r)                           FN_CHIP_Rd32(DE_VSD, O20, _r)
#define DE_VSD_O20_Wr(_r, _v)                       FN_CHIP_Wr32(DE_VSD, O20, _r, _v)
#define DE_VSD_O20_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_VSD, O20, _r, _f01, _v01)
#define DE_VSD_O20_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_VSD, O20, _r, _f01, _v01)
#define DE_VSD_O20_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_VSD, O20, _r, _f, _c, _m)
#define DE_VSD_O20_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_VSD, O20, _r, _f, _c, _v1, _v2)
#define DE_VSD_O20_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_VSD, O20, _r, _v)
#define DE_VSD_O20_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_VSD, O20, _r, _v)
#define DE_VSD_O20_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_VSD, O20, _r, _f01, _v01)
#define DE_VSD_O20_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_VSD, O20, _r, _f01, _v01)
#define DE_VSD_O20_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_VSD, O20, _r, _f, _c, _m)
#define DE_VSD_O20_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_VSD, O20, _r, _f, _c, _v1, _v2)

#define DE_CCO_O20_RdFL(_r)                         FN_CHIP_RdFL(DE_CCO, O20, _r)
#define DE_CCO_O20_WrFL(_r)                         FN_CHIP_WrFL(DE_CCO, O20, _r)
#define DE_CCO_O20_Rd(_r)                           FN_CHIP_Rd32(DE_CCO, O20, _r)
#define DE_CCO_O20_Wr(_r, _v)                       FN_CHIP_Wr32(DE_CCO, O20, _r, _v)
#define DE_CCO_O20_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_CCO, O20, _r, _f01, _v01)
#define DE_CCO_O20_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_CCO, O20, _r, _f01, _v01)
#define DE_CCO_O20_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_CCO, O20, _r, _f, _c, _m)
#define DE_CCO_O20_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_CCO, O20, _r, _f, _c, _v1, _v2)
#define DE_CCO_O20_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_CCO, O20, _r, _v)
#define DE_CCO_O20_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_CCO, O20, _r, _v)
#define DE_CCO_O20_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_CCO, O20, _r, _f01, _v01)
#define DE_CCO_O20_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_CCO, O20, _r, _f01, _v01)
#define DE_CCO_O20_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_CCO, O20, _r, _f, _c, _m)
#define DE_CCO_O20_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_CCO, O20, _r, _f, _c, _v1, _v2)

#define DE_IMX_O20_RdFL(_r)                         FN_CHIP_RdFL(DE_IMX, O20, _r)
#define DE_IMX_O20_WrFL(_r)                         FN_CHIP_WrFL(DE_IMX, O20, _r)
#define DE_IMX_O20_Rd(_r)                           FN_CHIP_Rd32(DE_IMX, O20, _r)
#define DE_IMX_O20_Wr(_r, _v)                       FN_CHIP_Wr32(DE_IMX, O20, _r, _v)
#define DE_IMX_O20_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_IMX, O20, _r, _f01, _v01)
#define DE_IMX_O20_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_IMX, O20, _r, _f01, _v01)
#define DE_IMX_O20_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_IMX, O20, _r, _f, _c, _m)
#define DE_IMX_O20_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_IMX, O20, _r, _f, _c, _v1, _v2)
#define DE_IMX_O20_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_IMX, O20, _r, _v)
#define DE_IMX_O20_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_IMX, O20, _r, _v)
#define DE_IMX_O20_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_IMX, O20, _r, _f01, _v01)
#define DE_IMX_O20_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_IMX, O20, _r, _f01, _v01)
#define DE_IMX_O20_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_IMX, O20, _r, _f, _c, _m)
#define DE_IMX_O20_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_IMX, O20, _r, _f, _c, _v1, _v2)

#define DE_ND0_O20_RdFL(_r)                         FN_CHIP_RdFL(DE_ND0, O20, _r)
#define DE_ND0_O20_WrFL(_r)                         FN_CHIP_WrFL(DE_ND0, O20, _r)
#define DE_ND0_O20_Rd(_r)                           FN_CHIP_Rd32(DE_ND0, O20, _r)
#define DE_ND0_O20_Wr(_r, _v)                       FN_CHIP_Wr32(DE_ND0, O20, _r, _v)
#define DE_ND0_O20_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_ND0, O20, _r, _f01, _v01)
#define DE_ND0_O20_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_ND0, O20, _r, _f01, _v01)
#define DE_ND0_O20_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_ND0, O20, _r, _f, _c, _m)
#define DE_ND0_O20_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_ND0, O20, _r, _f, _c, _v1, _v2)
#define DE_ND0_O20_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_ND0, O20, _r, _v)
#define DE_ND0_O20_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_ND0, O20, _r, _v)
#define DE_ND0_O20_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_ND0, O20, _r, _f01, _v01)
#define DE_ND0_O20_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_ND0, O20, _r, _f01, _v01)
#define DE_ND0_O20_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_ND0, O20, _r, _f, _c, _m)
#define DE_ND0_O20_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_ND0, O20, _r, _f, _c, _v1, _v2)

#define DE_ND1_O20_RdFL(_r)                         FN_CHIP_RdFL(DE_ND1, O20, _r)
#define DE_ND1_O20_WrFL(_r)                         FN_CHIP_WrFL(DE_ND1, O20, _r)
#define DE_ND1_O20_Rd(_r)                           FN_CHIP_Rd32(DE_ND1, O20, _r)
#define DE_ND1_O20_Wr(_r, _v)                       FN_CHIP_Wr32(DE_ND1, O20, _r, _v)
#define DE_ND1_O20_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_ND1, O20, _r, _f01, _v01)
#define DE_ND1_O20_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_ND1, O20, _r, _f01, _v01)
#define DE_ND1_O20_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_ND1, O20, _r, _f, _c, _m)
#define DE_ND1_O20_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_ND1, O20, _r, _f, _c, _v1, _v2)
#define DE_ND1_O20_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_ND1, O20, _r, _v)
#define DE_ND1_O20_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_ND1, O20, _r, _v)
#define DE_ND1_O20_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_ND1, O20, _r, _f01, _v01)
#define DE_ND1_O20_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_ND1, O20, _r, _f01, _v01)
#define DE_ND1_O20_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_ND1, O20, _r, _f, _c, _m)
#define DE_ND1_O20_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_ND1, O20, _r, _f, _c, _v1, _v2)

#define DE_SUB_O20_RdFL(_r)                         FN_CHIP_RdFL(DE_SUB, O20, _r)
#define DE_SUB_O20_WrFL(_r)                         FN_CHIP_WrFL(DE_SUB, O20, _r)
#define DE_SUB_O20_Rd(_r)                           FN_CHIP_Rd32(DE_SUB, O20, _r)
#define DE_SUB_O20_Wr(_r, _v)                       FN_CHIP_Wr32(DE_SUB, O20, _r, _v)
#define DE_SUB_O20_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_SUB, O20, _r, _f01, _v01)
#define DE_SUB_O20_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_SUB, O20, _r, _f01, _v01)
#define DE_SUB_O20_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_SUB, O20, _r, _f, _c, _m)
#define DE_SUB_O20_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_SUB, O20, _r, _f, _c, _v1, _v2)
#define DE_SUB_O20_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_SUB, O20, _r, _v)
#define DE_SUB_O20_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_SUB, O20, _r, _v)
#define DE_SUB_O20_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_SUB, O20, _r, _f01, _v01)
#define DE_SUB_O20_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_SUB, O20, _r, _f01, _v01)
#define DE_SUB_O20_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_SUB, O20, _r, _f, _c, _m)
#define DE_SUB_O20_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_SUB, O20, _r, _f, _c, _v1, _v2)

#define DE_HDR_O20_RdFL(_r)                         FN_CHIP_RdFL(DE_HDR, O20, _r)
#define DE_HDR_O20_WrFL(_r)                         FN_CHIP_WrFL(DE_HDR, O20, _r)
#define DE_HDR_O20_Rd(_r)                           FN_CHIP_Rd32(DE_HDR, O20, _r)
#define DE_HDR_O20_Wr(_r, _v)                       FN_CHIP_Wr32(DE_HDR, O20, _r, _v)
#define DE_HDR_O20_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_HDR, O20, _r, _f01, _v01)
#define DE_HDR_O20_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_HDR, O20, _r, _f01, _v01)
#define DE_HDR_O20_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_HDR, O20, _r, _f, _c, _m)
#define DE_HDR_O20_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_HDR, O20, _r, _f, _c, _v1, _v2)
#define DE_HDR_O20_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_HDR, O20, _r, _v)
#define DE_HDR_O20_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_HDR, O20, _r, _v)
#define DE_HDR_O20_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_HDR, O20, _r, _f01, _v01)
#define DE_HDR_O20_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_HDR, O20, _r, _f01, _v01)
#define DE_HDR_O20_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_HDR, O20, _r, _f, _c, _m)
#define DE_HDR_O20_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_HDR, O20, _r, _f, _c, _v1, _v2)


/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        DE_CVC_REG_O20A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_CVC_REG_O20A0_T *a0;
    } phys;
} DE_CVC_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_VSD_REG_O20A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_VSD_REG_O20A0_T *a0;
    } phys;
} DE_VSD_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_CCO_REG_O20A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_CCO_REG_O20A0_T *a0;
    } phys;
} DE_CCO_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_IMX_REG_O20A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_IMX_REG_O20A0_T *a0;
    } phys;
} DE_IMX_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_ND0_REG_O20A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_ND0_REG_O20A0_T *a0;
    } phys;
} DE_ND0_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_SUB_REG_O20A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_SUB_REG_O20A0_T *a0;
    } phys;
} DE_SUB_REG_O20_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_HDR_REG_O20A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_HDR_REG_O20A0_T *a0;
    } phys;
} DE_HDR_REG_O20_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_CTR_REG_O20_INC  ----- */
/**  @} */
