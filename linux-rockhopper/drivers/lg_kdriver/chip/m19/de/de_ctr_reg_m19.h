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

#ifndef  DE_CTR_REG_M19_INC
#define  DE_CTR_REG_M19_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_reg_mac.h"
#ifdef USE_KDRV_CODES_FOR_M19A0
#include "de_ctr_reg_m19a0.h"
#endif

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DE_CVC_M19_RdFL(_r)                         FN_CHIP_RdFL(DE_CVC, M19, _r)
#define DE_CVC_M19_WrFL(_r)                         FN_CHIP_WrFL(DE_CVC, M19, _r)
#define DE_CVC_M19_Rd(_r)                           FN_CHIP_Rd32(DE_CVC, M19, _r)
#define DE_CVC_M19_Wr(_r, _v)                       FN_CHIP_Wr32(DE_CVC, M19, _r, _v)
#define DE_CVC_M19_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_CVC, M19, _r, _f01, _v01)
#define DE_CVC_M19_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_CVC, M19, _r, _f01, _v01)
#define DE_CVC_M19_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_CVC, M19, _r, _f, _c, _m)
#define DE_CVC_M19_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_CVC, M19, _r, _f, _c, _v1, _v2)
#define DE_CVC_M19_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_CVC, M19, _r, _v)
#define DE_CVC_M19_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_CVC, M19, _r, _v)
#define DE_CVC_M19_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_CVC, M19, _r, _f01, _v01)
#define DE_CVC_M19_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_CVC, M19, _r, _f01, _v01)
#define DE_CVC_M19_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_CVC, M19, _r, _f, _c, _m)
#define DE_CVC_M19_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_CVC, M19, _r, _f, _c, _v1, _v2)

#define DE_VSD_M19_RdFL(_r)                         FN_CHIP_RdFL(DE_VSD, M19, _r)
#define DE_VSD_M19_WrFL(_r)                         FN_CHIP_WrFL(DE_VSD, M19, _r)
#define DE_VSD_M19_Rd(_r)                           FN_CHIP_Rd32(DE_VSD, M19, _r)
#define DE_VSD_M19_Wr(_r, _v)                       FN_CHIP_Wr32(DE_VSD, M19, _r, _v)
#define DE_VSD_M19_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_VSD, M19, _r, _f01, _v01)
#define DE_VSD_M19_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_VSD, M19, _r, _f01, _v01)
#define DE_VSD_M19_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_VSD, M19, _r, _f, _c, _m)
#define DE_VSD_M19_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_VSD, M19, _r, _f, _c, _v1, _v2)
#define DE_VSD_M19_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_VSD, M19, _r, _v)
#define DE_VSD_M19_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_VSD, M19, _r, _v)
#define DE_VSD_M19_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_VSD, M19, _r, _f01, _v01)
#define DE_VSD_M19_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_VSD, M19, _r, _f01, _v01)
#define DE_VSD_M19_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_VSD, M19, _r, _f, _c, _m)
#define DE_VSD_M19_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_VSD, M19, _r, _f, _c, _v1, _v2)

#define DE_CCO_M19_RdFL(_r)                         FN_CHIP_RdFL(DE_CCO, M19, _r)
#define DE_CCO_M19_WrFL(_r)                         FN_CHIP_WrFL(DE_CCO, M19, _r)
#define DE_CCO_M19_Rd(_r)                           FN_CHIP_Rd32(DE_CCO, M19, _r)
#define DE_CCO_M19_Wr(_r, _v)                       FN_CHIP_Wr32(DE_CCO, M19, _r, _v)
#define DE_CCO_M19_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_CCO, M19, _r, _f01, _v01)
#define DE_CCO_M19_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_CCO, M19, _r, _f01, _v01)
#define DE_CCO_M19_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_CCO, M19, _r, _f, _c, _m)
#define DE_CCO_M19_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_CCO, M19, _r, _f, _c, _v1, _v2)
#define DE_CCO_M19_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_CCO, M19, _r, _v)
#define DE_CCO_M19_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_CCO, M19, _r, _v)
#define DE_CCO_M19_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_CCO, M19, _r, _f01, _v01)
#define DE_CCO_M19_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_CCO, M19, _r, _f01, _v01)
#define DE_CCO_M19_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_CCO, M19, _r, _f, _c, _m)
#define DE_CCO_M19_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_CCO, M19, _r, _f, _c, _v1, _v2)

#define DE_IMX_M19_RdFL(_r)                         FN_CHIP_RdFL(DE_IMX, M19, _r)
#define DE_IMX_M19_WrFL(_r)                         FN_CHIP_WrFL(DE_IMX, M19, _r)
#define DE_IMX_M19_Rd(_r)                           FN_CHIP_Rd32(DE_IMX, M19, _r)
#define DE_IMX_M19_Wr(_r, _v)                       FN_CHIP_Wr32(DE_IMX, M19, _r, _v)
#define DE_IMX_M19_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_IMX, M19, _r, _f01, _v01)
#define DE_IMX_M19_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_IMX, M19, _r, _f01, _v01)
#define DE_IMX_M19_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_IMX, M19, _r, _f, _c, _m)
#define DE_IMX_M19_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_IMX, M19, _r, _f, _c, _v1, _v2)
#define DE_IMX_M19_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_IMX, M19, _r, _v)
#define DE_IMX_M19_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_IMX, M19, _r, _v)
#define DE_IMX_M19_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_IMX, M19, _r, _f01, _v01)
#define DE_IMX_M19_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_IMX, M19, _r, _f01, _v01)
#define DE_IMX_M19_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_IMX, M19, _r, _f, _c, _m)
#define DE_IMX_M19_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_IMX, M19, _r, _f, _c, _v1, _v2)

#define DE_ND0_M19_RdFL(_r)                         FN_CHIP_RdFL(DE_ND0, M19, _r)
#define DE_ND0_M19_WrFL(_r)                         FN_CHIP_WrFL(DE_ND0, M19, _r)
#define DE_ND0_M19_Rd(_r)                           FN_CHIP_Rd32(DE_ND0, M19, _r)
#define DE_ND0_M19_Wr(_r, _v)                       FN_CHIP_Wr32(DE_ND0, M19, _r, _v)
#define DE_ND0_M19_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_ND0, M19, _r, _f01, _v01)
#define DE_ND0_M19_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_ND0, M19, _r, _f01, _v01)
#define DE_ND0_M19_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_ND0, M19, _r, _f, _c, _m)
#define DE_ND0_M19_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_ND0, M19, _r, _f, _c, _v1, _v2)
#define DE_ND0_M19_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_ND0, M19, _r, _v)
#define DE_ND0_M19_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_ND0, M19, _r, _v)
#define DE_ND0_M19_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_ND0, M19, _r, _f01, _v01)
#define DE_ND0_M19_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_ND0, M19, _r, _f01, _v01)
#define DE_ND0_M19_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_ND0, M19, _r, _f, _c, _m)
#define DE_ND0_M19_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_ND0, M19, _r, _f, _c, _v1, _v2)

#define DE_ND1_M19_RdFL(_r)                         FN_CHIP_RdFL(DE_ND1, M19, _r)
#define DE_ND1_M19_WrFL(_r)                         FN_CHIP_WrFL(DE_ND1, M19, _r)
#define DE_ND1_M19_Rd(_r)                           FN_CHIP_Rd32(DE_ND1, M19, _r)
#define DE_ND1_M19_Wr(_r, _v)                       FN_CHIP_Wr32(DE_ND1, M19, _r, _v)
#define DE_ND1_M19_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_ND1, M19, _r, _f01, _v01)
#define DE_ND1_M19_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_ND1, M19, _r, _f01, _v01)
#define DE_ND1_M19_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_ND1, M19, _r, _f, _c, _m)
#define DE_ND1_M19_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_ND1, M19, _r, _f, _c, _v1, _v2)
#define DE_ND1_M19_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_ND1, M19, _r, _v)
#define DE_ND1_M19_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_ND1, M19, _r, _v)
#define DE_ND1_M19_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_ND1, M19, _r, _f01, _v01)
#define DE_ND1_M19_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_ND1, M19, _r, _f01, _v01)
#define DE_ND1_M19_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_ND1, M19, _r, _f, _c, _m)
#define DE_ND1_M19_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_ND1, M19, _r, _f, _c, _v1, _v2)

#define DE_SUB_M19_RdFL(_r)                         FN_CHIP_RdFL(DE_SUB, M19, _r)
#define DE_SUB_M19_WrFL(_r)                         FN_CHIP_WrFL(DE_SUB, M19, _r)
#define DE_SUB_M19_Rd(_r)                           FN_CHIP_Rd32(DE_SUB, M19, _r)
#define DE_SUB_M19_Wr(_r, _v)                       FN_CHIP_Wr32(DE_SUB, M19, _r, _v)
#define DE_SUB_M19_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_SUB, M19, _r, _f01, _v01)
#define DE_SUB_M19_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_SUB, M19, _r, _f01, _v01)
#define DE_SUB_M19_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_SUB, M19, _r, _f, _c, _m)
#define DE_SUB_M19_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_SUB, M19, _r, _f, _c, _v1, _v2)
#define DE_SUB_M19_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_SUB, M19, _r, _v)
#define DE_SUB_M19_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_SUB, M19, _r, _v)
#define DE_SUB_M19_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_SUB, M19, _r, _f01, _v01)
#define DE_SUB_M19_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_SUB, M19, _r, _f01, _v01)
#define DE_SUB_M19_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_SUB, M19, _r, _f, _c, _m)
#define DE_SUB_M19_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_SUB, M19, _r, _f, _c, _v1, _v2)

#define DE_HDR_M19_RdFL(_r)                         FN_CHIP_RdFL(DE_HDR, M19, _r)
#define DE_HDR_M19_WrFL(_r)                         FN_CHIP_WrFL(DE_HDR, M19, _r)
#define DE_HDR_M19_Rd(_r)                           FN_CHIP_Rd32(DE_HDR, M19, _r)
#define DE_HDR_M19_Wr(_r, _v)                       FN_CHIP_Wr32(DE_HDR, M19, _r, _v)
#define DE_HDR_M19_Rd01(_r, _f01, _v01)             FN_CHIP_Rd01(DE_HDR, M19, _r, _f01, _v01)
#define DE_HDR_M19_Wr01(_r, _f01, _v01)             FN_CHIP_Wr01(DE_HDR, M19, _r, _f01, _v01)
#define DE_HDR_M19_WfCM(_r, _f, _c, _m)             FN_CHIP_WfCM(DE_HDR, M19, _r, _f, _c, _m)
#define DE_HDR_M19_WfCV(_r, _f, _c, _v1, _v2)       FN_CHIP_WfCV(DE_HDR, M19, _r, _f, _c, _v1, _v2)
#define DE_HDR_M19_FLRd(_r, _v)                     FN_CHIP_FLRd(DE_HDR, M19, _r, _v)
#define DE_HDR_M19_FLWr(_r, _v)                     FN_CHIP_FLWr(DE_HDR, M19, _r, _v)
#define DE_HDR_M19_FLRf(_r, _f01, _v01)             FN_CHIP_FLRf(DE_HDR, M19, _r, _f01, _v01)
#define DE_HDR_M19_FLWf(_r, _f01, _v01)             FN_CHIP_FLWf(DE_HDR, M19, _r, _f01, _v01)
#define DE_HDR_M19_FLCM(_r, _f, _c, _m)             FN_CHIP_FLCM(DE_HDR, M19, _r, _f, _c, _m)
#define DE_HDR_M19_FLCV(_r, _f, _c, _v1, _v2)       FN_CHIP_FLCV(DE_HDR, M19, _r, _f, _c, _v1, _v2)


/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        DE_CVC_REG_M19A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_CVC_REG_M19A0_T *a0;
    } phys;
} DE_CVC_REG_M19_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_VSD_REG_M19A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_VSD_REG_M19A0_T *a0;
    } phys;
} DE_VSD_REG_M19_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_CCO_REG_M19A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_CCO_REG_M19A0_T *a0;
    } phys;
} DE_CCO_REG_M19_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_IMX_REG_M19A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_IMX_REG_M19A0_T *a0;
    } phys;
} DE_IMX_REG_M19_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_ND0_REG_M19A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_ND0_REG_M19A0_T *a0;
    } phys;
} DE_ND0_REG_M19_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_SUB_REG_M19A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_SUB_REG_M19A0_T *a0;
    } phys;
} DE_SUB_REG_M19_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_HDR_REG_M19A0_T *a0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_HDR_REG_M19A0_T *a0;
    } phys;
} DE_HDR_REG_M19_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_CTR_REG_M19_INC  ----- */
/**  @} */
