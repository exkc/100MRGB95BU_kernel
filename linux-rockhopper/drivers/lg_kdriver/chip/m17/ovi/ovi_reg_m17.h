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
 *  OVI m17 reg header file for OVI device
 *
 *  author		dj911.kim@lge.com
 *  version		1.0
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup OVI
 *	@{
 */

#ifndef  OVI_REG_M17_INC
#define  OVI_REG_M17_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "ovi_reg_mac.h"
#include "ovi_reg_m17a0.h"
#include "ovi_reg_m17c0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define OVI_TCON_M17_RdFL(_r)                  		OVI_FN_CHIP_RdFL(OVI_TCON, M17, _r)
#define OVI_TCON_M17_WrFL(_r)                  		OVI_FN_CHIP_WrFL(OVI_TCON, M17, _r)
#define OVI_TCON_M17_Rd(_r)                    		OVI_FN_CHIP_Rd32(OVI_TCON, M17, _r)
#define OVI_TCON_M17_Wr(_r, _v)                		OVI_FN_CHIP_Wr32(OVI_TCON, M17, _r, _v)
#define OVI_TCON_M17_Rd01(_r, _f01, _v01)    		OVI_FN_CHIP_Rd01(OVI_TCON, M17, _r, _f01, _v01)
#define OVI_TCON_M17_Wr01(_r, _f01, _v01)    		OVI_FN_CHIP_Wr01(OVI_TCON, M17, _r, _f01, _v01)
#define OVI_TCON_M17_FLRd(_r, _v)              		OVI_FN_CHIP_FLRd(OVI_TCON, M17, _r, _v)
#define OVI_TCON_M17_FLWr(_r, _v)              		OVI_FN_CHIP_FLWr(OVI_TCON, M17, _r, _v)
#define OVI_TCON_M17_FLRf(_r, _f01, _v01)      		OVI_FN_CHIP_FLRf(OVI_TCON, M17, _r, _f01, _v01)
#define OVI_TCON_M17_FLWf(_r, _f01, _v01)    		OVI_FN_CHIP_FLWf(OVI_TCON, M17, _r, _f01, _v01)

#define OVI_TCON_M17C0_RdFL(_r)                  	OVI_FN_CHIP_VER_RdFL(OVI_TCON, M17, c0, _r)
#define OVI_TCON_M17C0_WrFL(_r)                  	OVI_FN_CHIP_VER_WrFL(OVI_TCON, M17, c0, _r)
#define OVI_TCON_M17C0_Rd(_r)                    	OVI_FN_CHIP_VER_Rd32(OVI_TCON, M17, c0, _r)
#define OVI_TCON_M17C0_Wr(_r, _v)                	OVI_FN_CHIP_VER_Wr32(OVI_TCON, M17, c0, _r, _v)
#define OVI_TCON_M17C0_Rd01(_r, _f01, _v01)    		OVI_FN_CHIP_VER_Rd01(OVI_TCON, M17, c0, _r, _f01, _v01)
#define OVI_TCON_M17C0_Wr01(_r, _f01, _v01)    		OVI_FN_CHIP_VER_Wr01(OVI_TCON, M17, c0, _r, _f01, _v01)
#define OVI_TCON_M17C0_FLRd(_r, _v)             	OVI_FN_CHIP_VER_FLRd(OVI_TCON, M17, c0, _r, _v)
#define OVI_TCON_M17C0_FLWr(_r, _v)              	OVI_FN_CHIP_VER_FLWr(OVI_TCON, M17, c0, _r, _v)
#define OVI_TCON_M17C0_FLRf(_r, _f01, _v01)      	OVI_FN_CHIP_VER_FLRf(OVI_TCON, M17, c0, _r, _f01, _v01)
#define OVI_TCON_M17C0_FLWf(_r, _f01, _v01)    		OVI_FN_CHIP_VER_FLWf(OVI_TCON, M17, c0, _r, _f01, _v01)

#define OVI_TCON_CAD_M17C0_RdFL(_r)                 OVI_FN_CHIP_VER_RdFL(OVI_TCON_CAD, M17, c0, _r)
#define OVI_TCON_CAD_M17C0_WrFL(_r)                 OVI_FN_CHIP_VER_WrFL(OVI_TCON_CAD, M17, c0, _r)
#define OVI_TCON_CAD_M17C0_Rd(_r)                   OVI_FN_CHIP_VER_Rd32(OVI_TCON_CAD, M17, c0, _r)
#define OVI_TCON_CAD_M17C0_Wr(_r, _v)               OVI_FN_CHIP_VER_Wr32(OVI_TCON_CAD, M17, c0, _r, _v)
#define OVI_TCON_CAD_M17C0_Rd01(_r, _f01, _v01)    	OVI_FN_CHIP_VER_Rd01(OVI_TCON_CAD, M17, c0, _r, _f01, _v01)
#define OVI_TCON_CAD_M17C0_Wr01(_r, _f01, _v01)    	OVI_FN_CHIP_VER_Wr01(OVI_TCON_CAD, M17, c0, _r, _f01, _v01)
#define OVI_TCON_CAD_M17C0_FLRd(_r, _v)            	OVI_FN_CHIP_VER_FLRd(OVI_TCON_CAD, M17, c0, _r, _v)
#define OVI_TCON_CAD_M17C0_FLWr(_r, _v)             OVI_FN_CHIP_VER_FLWr(OVI_TCON_CAD, M17, c0, _r, _v)
#define OVI_TCON_CAD_M17C0_FLRf(_r, _f01, _v01)     OVI_FN_CHIP_VER_FLRf(OVI_TCON_CAD, M17, c0, _r, _f01, _v01)
#define OVI_TCON_CAD_M17C0_FLWf(_r, _f01, _v01)    	OVI_FN_CHIP_VER_FLWf(OVI_TCON_CAD, M17, c0, _r, _f01, _v01)

#define OVI_TCON_LODC_M17C0_RdFL(_r)                OVI_FN_CHIP_VER_RdFL(OVI_TCON_LODC, M17, c0, _r)
#define OVI_TCON_LODC_M17C0_WrFL(_r)                OVI_FN_CHIP_VER_WrFL(OVI_TCON_LODC, M17, c0, _r)
#define OVI_TCON_LODC_M17C0_Rd(_r)                  OVI_FN_CHIP_VER_Rd32(OVI_TCON_LODC, M17, c0, _r)
#define OVI_TCON_LODC_M17C0_Wr(_r, _v)              OVI_FN_CHIP_VER_Wr32(OVI_TCON_LODC, M17, c0, _r, _v)
#define OVI_TCON_LODC_M17C0_Rd01(_r, _f01, _v01)    OVI_FN_CHIP_VER_Rd01(OVI_TCON_LODC, M17, c0, _r, _f01, _v01)
#define OVI_TCON_LODC_M17C0_Wr01(_r, _f01, _v01)    OVI_FN_CHIP_VER_Wr01(OVI_TCON_LODC, M17, c0, _r, _f01, _v01)
#define OVI_TCON_LODC_M17C0_FLRd(_r, _v)            OVI_FN_CHIP_VER_FLRd(OVI_TCON_LODC, M17, c0, _r, _v)
#define OVI_TCON_LODC_M17C0_FLWr(_r, _v)            OVI_FN_CHIP_VER_FLWr(OVI_TCON_LODC, M17, c0, _r, _v)
#define OVI_TCON_LODC_M17C0_FLRf(_r, _f01, _v01)    OVI_FN_CHIP_VER_FLRf(OVI_TCON_LODC, M17, c0, _r, _f01, _v01)
#define OVI_TCON_LODC_M17C0_FLWf(_r, _f01, _v01)   	OVI_FN_CHIP_VER_FLWf(OVI_TCON_LODC, M17, c0, _r, _f01, _v01)

#define OVI_OIF_M17_RdFL(_r)                  		OVI_FN_CHIP_RdFL(OVI_OIF, M17, _r)
#define OVI_OIF_M17_WrFL(_r)                  		OVI_FN_CHIP_WrFL(OVI_OIF, M17, _r)
#define OVI_OIF_M17_Rd(_r)                    		OVI_FN_CHIP_Rd32(OVI_OIF, M17, _r)
#define OVI_OIF_M17_Wr(_r, _v)                		OVI_FN_CHIP_Wr32(OVI_OIF, M17, _r, _v)
#define OVI_OIF_M17_Rd01(_r, _f01, _v01)    		OVI_FN_CHIP_Rd01(OVI_OIF, M17, _r, _f01, _v01)
#define OVI_OIF_M17_Wr01(_r, _f01, _v01)    		OVI_FN_CHIP_Wr01(OVI_OIF, M17, _r, _f01, _v01)
#define OVI_OIF_M17_FLRd(_r, _v)              		OVI_FN_CHIP_FLRd(OVI_OIF, M17, _r, _v)
#define OVI_OIF_M17_FLWr(_r, _v)              		OVI_FN_CHIP_FLWr(OVI_OIF, M17, _r, _v)
#define OVI_OIF_M17_FLRf(_r, _f01, _v01)      		OVI_FN_CHIP_FLRf(OVI_OIF, M17, _r, _f01, _v01)
#define OVI_OIF_M17_FLWf(_r, _f01, _v01)    		OVI_FN_CHIP_FLWf(OVI_OIF, M17, _r, _f01, _v01)

#define OVI_WPR_M17C0_RdFL(_r)                  	OVI_FN_CHIP_VER_RdFL(OVI_WPR, M17, c0, _r)
#define OVI_WPR_M17C0_WrFL(_r)                  	OVI_FN_CHIP_VER_WrFL(OVI_WPR, M17, c0, _r)
#define OVI_WPR_M17C0_Rd(_r)                    	OVI_FN_CHIP_VER_Rd32(OVI_WPR, M17, c0, _r)
#define OVI_WPR_M17C0_Wr(_r, _v)                	OVI_FN_CHIP_VER_Wr32(OVI_WPR, M17, c0, _r, _v)
#define OVI_WPR_M17C0_Rd01(_r, _f01, _v01)    		OVI_FN_CHIP_VER_Rd01(OVI_WPR, M17, c0, _r, _f01, _v01)
#define OVI_WPR_M17C0_Wr01(_r, _f01, _v01)    		OVI_FN_CHIP_VER_Wr01(OVI_WPR, M17, c0, _r, _f01, _v01)
#define OVI_WPR_M17C0_FLRd(_r, _v)              	OVI_FN_CHIP_VER_FLRd(OVI_WPR, M17, c0, _r, _v)
#define OVI_WPR_M17C0_FLWr(_r, _v)              	OVI_FN_CHIP_VER_FLWr(OVI_WPR, M17, c0, _r, _v)
#define OVI_WPR_M17C0_FLRf(_r, _f01, _v01)      	OVI_FN_CHIP_VER_FLRf(OVI_WPR, M17, c0, _r, _f01, _v01)
#define OVI_WPR_M17C0_FLWf(_r, _f01, _v01)    		OVI_FN_CHIP_VER_FLWf(OVI_WPR, M17, c0, _r, _f01, _v01)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		OVI_TCON_REG_M17A0_T *a0;
		OVI_TCON_REG_M17A0_T *b0;
		OVI_TCON_REG_M17C0_T *c0;
	} shdw;

	union {
		volatile UINT32 		 *addr;
		volatile OVI_TCON_REG_M17A0_T *a0;
		volatile OVI_TCON_REG_M17A0_T *b0;
		volatile OVI_TCON_REG_M17C0_T *c0;
	} phys;
} OVI_TCON_REG_M17_T;

typedef struct {
	union {
		UINT32			*addr;
		OVI_TCON_LODC_REG_M17A0_T *a0;
		OVI_TCON_LODC_REG_M17A0_T *b0;
		OVI_TCON_LODC_REG_M17C0_T *c0;
	} shdw;

	union {
		volatile UINT32 		 *addr;
		volatile OVI_TCON_LODC_REG_M17A0_T *a0;
		volatile OVI_TCON_LODC_REG_M17A0_T *b0;
		volatile OVI_TCON_LODC_REG_M17C0_T *c0;
	} phys;
} OVI_TCON_LODC_REG_M17_T;

typedef struct {
	union {
		UINT32			*addr;
		OVI_TCON_CAD_REG_M17C0_T *c0;
	} shdw;

	union {
		volatile UINT32 		 *addr;
		volatile OVI_TCON_CAD_REG_M17C0_T *c0;
	} phys;
} OVI_TCON_CAD_REG_M17_T;

typedef struct {
	union {
		UINT32          *addr;
		OVI_OIF_REG_M17A0_T *a0;
		OVI_OIF_REG_M17A0_T *b0;
		OVI_OIF_REG_M17C0_T *c0;
	} shdw;

	union {
		volatile UINT32          *addr;
		volatile OVI_OIF_REG_M17A0_T *a0;
		volatile OVI_OIF_REG_M17A0_T *b0;
		volatile OVI_OIF_REG_M17C0_T *c0;
	} phys;
} OVI_OIF_REG_M17_T;

typedef struct {
	union {
		UINT32          *addr;
		OVI_WPR_REG_M17A0_T *a0;
		OVI_WPR_REG_M17A0_T *b0;
		OVI_WPR_REG_M17C0_T *c0;
	} shdw;

	union {
		volatile UINT32          *addr;
		volatile OVI_WPR_REG_M17A0_T *a0;
		volatile OVI_WPR_REG_M17A0_T *b0;
		volatile OVI_WPR_REG_M17C0_T *c0;
	} phys;
} OVI_WPR_REG_M17_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef OVI_REG_M17_INC  ----- */
/**  @} */

