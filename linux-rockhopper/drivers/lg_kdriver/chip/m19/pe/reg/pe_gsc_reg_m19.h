/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_gsc_reg_m19.h
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.17
 * note		  Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef _PE_GSC_REG_M19_H_
#define _PE_GSC_REG_M19_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_gsc_reg_m19a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/* PE_GSC_Y_M19 */
#define PE_GSC_Y_M19_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_GSC_Y_M19,data,_r)
#define PE_GSC_Y_M19_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_GSC_Y_M19,data,_r)
#define PE_GSC_Y_M19_Rd(_r)				PE_REG_SHDW_Rd32(gPE_GSC_Y_M19,data,_r)
#define PE_GSC_Y_M19_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_GSC_Y_M19,data,_r,_d1)
#define PE_GSC_Y_M19_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_GSC_Y_M19,data,_r,_f1,_d1)
#define PE_GSC_Y_M19_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_GSC_Y_M19,data,_r,_f1,_d1)

#define PE_GSC_Y_M19_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_Y_M19,data,_r);\
		PE_REG_SHDW_Wr01(gPE_GSC_Y_M19,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_GSC_Y_M19,data,_r);}
#define PE_GSC_Y_M19_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_Y_M19,data,_r);\
		PE_REG_SHDW_Wr02(gPE_GSC_Y_M19,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_GSC_Y_M19,data,_r);}
#define PE_GSC_Y_M19_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_Y_M19,data,_r);\
		PE_REG_SHDW_Wr03(gPE_GSC_Y_M19,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_GSC_Y_M19,data,_r);}
#define PE_GSC_Y_M19_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_Y_M19,data,_r);\
		PE_REG_SHDW_Wr04(gPE_GSC_Y_M19,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_GSC_Y_M19,data,_r);}
#define PE_GSC_Y_M19_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_Y_M19,data,_r);\
		PE_REG_SHDW_Rd01(gPE_GSC_Y_M19,data,_r,_f1,_d1);}
#define PE_GSC_Y_M19_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_Y_M19,data,_r);\
		PE_REG_SHDW_Rd02(gPE_GSC_Y_M19,data,_r,_f1,_d1,_f2,_d2);}
#define PE_GSC_Y_M19_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_Y_M19,data,_r);\
		PE_REG_SHDW_Rd03(gPE_GSC_Y_M19,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_GSC_Y_M19_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_Y_M19,data,_r);\
		PE_REG_SHDW_Rd04(gPE_GSC_Y_M19,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}

/* PE_GSC_C_M19 */
#define PE_GSC_C_M19_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_GSC_C_M19,data,_r)
#define PE_GSC_C_M19_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_GSC_C_M19,data,_r)
#define PE_GSC_C_M19_Rd(_r)				PE_REG_SHDW_Rd32(gPE_GSC_C_M19,data,_r)
#define PE_GSC_C_M19_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_GSC_C_M19,data,_r,_d1)
#define PE_GSC_C_M19_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_GSC_C_M19,data,_r,_f1,_d1)
#define PE_GSC_C_M19_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_GSC_C_M19,data,_r,_f1,_d1)

#define PE_GSC_C_M19_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_C_M19,data,_r);\
		PE_REG_SHDW_Wr01(gPE_GSC_C_M19,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_GSC_C_M19,data,_r);}
#define PE_GSC_C_M19_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_C_M19,data,_r);\
		PE_REG_SHDW_Wr02(gPE_GSC_C_M19,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_GSC_C_M19,data,_r);}
#define PE_GSC_C_M19_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_C_M19,data,_r);\
		PE_REG_SHDW_Wr03(gPE_GSC_C_M19,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_GSC_C_M19,data,_r);}
#define PE_GSC_C_M19_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_C_M19,data,_r);\
		PE_REG_SHDW_Wr04(gPE_GSC_C_M19,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_GSC_C_M19,data,_r);}
#define PE_GSC_C_M19_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_C_M19,data,_r);\
		PE_REG_SHDW_Rd01(gPE_GSC_C_M19,data,_r,_f1,_d1);}
#define PE_GSC_C_M19_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_C_M19,data,_r);\
		PE_REG_SHDW_Rd02(gPE_GSC_C_M19,data,_r,_f1,_d1,_f2,_d2);}
#define PE_GSC_C_M19_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_C_M19,data,_r);\
		PE_REG_SHDW_Rd03(gPE_GSC_C_M19,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_GSC_C_M19_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_GSC_C_M19,data,_r);\
		PE_REG_SHDW_Rd04(gPE_GSC_C_M19,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}



/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_GSC_Y_REG_M19_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_GSC_Y_REG_M19_T *data;
	} phys;
} PE_GSC_Y_REG_TYPE_M19_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_GSC_C_REG_M19_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_GSC_C_REG_M19_T *data;
	} phys;
} PE_GSC_C_REG_TYPE_M19_T;


/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_GSC_REG_M16_H_ */

