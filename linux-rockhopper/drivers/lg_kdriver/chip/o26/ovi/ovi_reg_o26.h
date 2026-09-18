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
 *  OVI O26 reg header file for OVI device
 *
 *  author		dj911.kim@lge.com
 *  version		1.0
 *  date		2017.06.07
 *  note		Additional information.
 *
 *  @addtogroup OVI
 *	@{
 */

#ifndef  OVI_REG_O26_INC
#define  OVI_REG_O26_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "ovi_reg_mac.h"
#include "ovi_reg_o26a0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define OVI_TCON_O26_RdFL(_r)                  		OVI_FN_CHIP_RdFL(OVI_TCON, O26, _r)
#define OVI_TCON_O26_WrFL(_r)                  		OVI_FN_CHIP_WrFL(OVI_TCON, O26, _r)
#define OVI_TCON_O26_Rd(_r)                    		OVI_FN_CHIP_Rd32(OVI_TCON, O26, _r)
#define OVI_TCON_O26_Wr(_r, _v)                		OVI_FN_CHIP_Wr32(OVI_TCON, O26, _r, _v)
#define OVI_TCON_O26_Rd01(_r, _f01, _v01)    		OVI_FN_CHIP_Rd01(OVI_TCON, O26, _r, _f01, _v01)
#define OVI_TCON_O26_Wr01(_r, _f01, _v01)    		OVI_FN_CHIP_Wr01(OVI_TCON, O26, _r, _f01, _v01)
#define OVI_TCON_O26_FLRd(_r, _v)              		OVI_FN_CHIP_FLRd(OVI_TCON, O26, _r, _v)
#define OVI_TCON_O26_FLWr(_r, _v)              		OVI_FN_CHIP_FLWr(OVI_TCON, O26, _r, _v)
#define OVI_TCON_O26_FLRf(_r, _f01, _v01)      		OVI_FN_CHIP_FLRf(OVI_TCON, O26, _r, _f01, _v01)
#define OVI_TCON_O26_FLWf(_r, _f01, _v01)    		OVI_FN_CHIP_FLWf(OVI_TCON, O26, _r, _f01, _v01)

#define OVI_TCON_CAD_O26_RdFL(_r)                 	OVI_FN_CHIP_RdFL(OVI_TCON_CAD, O26, _r)
#define OVI_TCON_CAD_O26_WrFL(_r)                 	OVI_FN_CHIP_WrFL(OVI_TCON_CAD, O26, _r)
#define OVI_TCON_CAD_O26_Rd(_r)                   	OVI_FN_CHIP_Rd32(OVI_TCON_CAD, O26, _r)
#define OVI_TCON_CAD_O26_Wr(_r, _v)               	OVI_FN_CHIP_Wr32(OVI_TCON_CAD, O26, _r, _v)
#define OVI_TCON_CAD_O26_Rd01(_r, _f01, _v01)    	OVI_FN_CHIP_Rd01(OVI_TCON_CAD, O26, _r, _f01, _v01)
#define OVI_TCON_CAD_O26_Wr01(_r, _f01, _v01)    	OVI_FN_CHIP_Wr01(OVI_TCON_CAD, O26, _r, _f01, _v01)
#define OVI_TCON_CAD_O26_FLRd(_r, _v)            	OVI_FN_CHIP_FLRd(OVI_TCON_CAD, O26, _r, _v)
#define OVI_TCON_CAD_O26_FLWr(_r, _v)             	OVI_FN_CHIP_FLWr(OVI_TCON_CAD, O26, _r, _v)
#define OVI_TCON_CAD_O26_FLRf(_r, _f01, _v01)     	OVI_FN_CHIP_FLRf(OVI_TCON_CAD, O26, _r, _f01, _v01)
#define OVI_TCON_CAD_O26_FLWf(_r, _f01, _v01)    	OVI_FN_CHIP_FLWf(OVI_TCON_CAD, O26, _r, _f01, _v01)

#define OVI_TCON_LODC_O26_RdFL(_r)                  OVI_FN_CHIP_RdFL(OVI_TCON_LODC, O26, _r)
#define OVI_TCON_LODC_O26_WrFL(_r)             		OVI_FN_CHIP_WrFL(OVI_TCON_LODC, O26, _r)
#define OVI_TCON_LODC_O26_Rd(_r)               		OVI_FN_CHIP_Rd32(OVI_TCON_LODC, O26, _r)
#define OVI_TCON_LODC_O26_Wr(_r, _v)           		OVI_FN_CHIP_Wr32(OVI_TCON_LODC, O26, _r, _v)
#define OVI_TCON_LODC_O26_Rd01(_r, _f01, _v01) 		OVI_FN_CHIP_Rd01(OVI_TCON_LODC, O26, _r, _f01, _v01)
#define OVI_TCON_LODC_O26_Wr01(_r, _f01, _v01) 		OVI_FN_CHIP_Wr01(OVI_TCON_LODC, O26, _r, _f01, _v01)
#define OVI_TCON_LODC_O26_FLRd(_r, _v)         		OVI_FN_CHIP_FLRd(OVI_TCON_LODC, O26, _r, _v)
#define OVI_TCON_LODC_O26_FLWr(_r, _v)         		OVI_FN_CHIP_FLWr(OVI_TCON_LODC, O26, _r, _v)
#define OVI_TCON_LODC_O26_FLRf(_r, _f01, _v01) 		OVI_FN_CHIP_FLRf(OVI_TCON_LODC, O26, _r, _f01, _v01)
#define OVI_TCON_LODC_O26_FLWf(_r, _f01, _v01) 		OVI_FN_CHIP_FLWf(OVI_TCON_LODC, O26, _r, _f01, _v01)

#define OVI_OIF_O26_RdFL(_r)                  		OVI_FN_CHIP_RdFL(OVI_OIF, O26, _r)
#define OVI_OIF_O26_WrFL(_r)                  		OVI_FN_CHIP_WrFL(OVI_OIF, O26, _r)
#define OVI_OIF_O26_Rd(_r)                    		OVI_FN_CHIP_Rd32(OVI_OIF, O26, _r)
#define OVI_OIF_O26_Wr(_r, _v)                		OVI_FN_CHIP_Wr32(OVI_OIF, O26, _r, _v)
#define OVI_OIF_O26_Rd01(_r, _f01, _v01)    		OVI_FN_CHIP_Rd01(OVI_OIF, O26, _r, _f01, _v01)
#define OVI_OIF_O26_Wr01(_r, _f01, _v01)    		OVI_FN_CHIP_Wr01(OVI_OIF, O26, _r, _f01, _v01)
#define OVI_OIF_O26_FLRd(_r, _v)              		OVI_FN_CHIP_FLRd(OVI_OIF, O26, _r, _v)
#define OVI_OIF_O26_FLWr(_r, _v)              		OVI_FN_CHIP_FLWr(OVI_OIF, O26, _r, _v)
#define OVI_OIF_O26_FLRf(_r, _f01, _v01)      		OVI_FN_CHIP_FLRf(OVI_OIF, O26, _r, _f01, _v01)
#define OVI_OIF_O26_FLWf(_r, _f01, _v01)    		OVI_FN_CHIP_FLWf(OVI_OIF, O26, _r, _f01, _v01)

#define OVI_WPR_O26_RdFL(_r)                  		OVI_FN_CHIP_RdFL(OVI_WPR, O26, _r)
#define OVI_WPR_O26_WrFL(_r)                  		OVI_FN_CHIP_WrFL(OVI_WPR, O26, _r)
#define OVI_WPR_O26_Rd(_r)                    		OVI_FN_CHIP_Rd32(OVI_WPR, O26, _r)
#define OVI_WPR_O26_Wr(_r, _v)                		OVI_FN_CHIP_Wr32(OVI_WPR, O26, _r, _v)
#define OVI_WPR_O26_Rd01(_r, _f01, _v01)    		OVI_FN_CHIP_Rd01(OVI_WPR, O26, _r, _f01, _v01)
#define OVI_WPR_O26_Wr01(_r, _f01, _v01)    		OVI_FN_CHIP_Wr01(OVI_WPR, O26, _r, _f01, _v01)
#define OVI_WPR_O26_FLRd(_r, _v)              		OVI_FN_CHIP_FLRd(OVI_WPR, O26, _r, _v)
#define OVI_WPR_O26_FLWr(_r, _v)              		OVI_FN_CHIP_FLWr(OVI_WPR, O26, _r, _v)
#define OVI_WPR_O26_FLRf(_r, _f01, _v01)      		OVI_FN_CHIP_FLRf(OVI_WPR, O26, _r, _f01, _v01)
#define OVI_WPR_O26_FLWf(_r, _f01, _v01)    		OVI_FN_CHIP_FLWf(OVI_WPR, O26, _r, _f01, _v01)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		OVI_O26A0_TCON_REG_T *a0;
		OVI_O26A0_TCON_REG_T *b0;
	} shdw;

	union {
		volatile UINT32 		 *addr;
		volatile OVI_O26A0_TCON_REG_T *a0;
		volatile OVI_O26A0_TCON_REG_T *b0;
	} phys;
} OVI_TCON_REG_O26_T;

typedef struct {
	union {
		UINT32          *addr;
		OVI_O26A0_OIF_REG_T *a0;
		OVI_O26A0_OIF_REG_T *b0;
	} shdw;

	union {
		volatile UINT32          *addr;
		volatile OVI_O26A0_OIF_REG_T *a0;
		volatile OVI_O26A0_OIF_REG_T *b0;
	} phys;
} OVI_OIF_REG_O26_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef OVI_REG_O26_INC  ----- */
/**  @} */

