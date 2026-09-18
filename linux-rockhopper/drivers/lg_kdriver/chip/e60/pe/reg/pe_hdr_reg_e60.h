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

/** @file pe_hdr_reg_e60.h
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
#ifndef _PE_HDR_REG_E60_H_
#define _PE_HDR_REG_E60_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_hdr_reg_e60a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
/* PE_H10_0_E60 */
#define PE_H10_0_E60_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_H10_0_E60,data,_r)
#define PE_H10_0_E60_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_H10_0_E60,data,_r)
#define PE_H10_0_E60_Rd(_r)				PE_REG_SHDW_Rd32(gPE_H10_0_E60,data,_r)
#define PE_H10_0_E60_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_H10_0_E60,data,_r,_d1)
#define PE_H10_0_E60_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_H10_0_E60,data,_r,_f1,_d1)
#define PE_H10_0_E60_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_H10_0_E60,data,_r,_f1,_d1)

#define PE_H10_0_E60_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_H10_0_E60,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_H10_0_E60,data,_r);}
#define PE_H10_0_E60_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_0_E60,data,_r);\
		PE_REG_SHDW_Wr01(gPE_H10_0_E60,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_H10_0_E60,data,_r);}
#define PE_H10_0_E60_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_0_E60,data,_r);\
		PE_REG_SHDW_Wr02(gPE_H10_0_E60,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_H10_0_E60,data,_r);}
#define PE_H10_0_E60_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_0_E60,data,_r);\
		PE_REG_SHDW_Rd01(gPE_H10_0_E60,data,_r,_f1,_d1);}
#define PE_H10_0_E60_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_0_E60,data,_r);\
		PE_REG_SHDW_Rd02(gPE_H10_0_E60,data,_r,_f1,_d1,_f2,_d2);}

/* PE_H10_1_E60 */
#define PE_H10_1_E60_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_H10_1_E60,data,_r)
#define PE_H10_1_E60_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_H10_1_E60,data,_r)
#define PE_H10_1_E60_Rd(_r)				PE_REG_SHDW_Rd32(gPE_H10_1_E60,data,_r)
#define PE_H10_1_E60_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_H10_1_E60,data,_r,_d1)
#define PE_H10_1_E60_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_H10_1_E60,data,_r,_f1,_d1)
#define PE_H10_1_E60_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_H10_1_E60,data,_r,_f1,_d1)

#define PE_H10_1_E60_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_H10_1_E60,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_H10_1_E60,data,_r);}
#define PE_H10_1_E60_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_1_E60,data,_r);\
		PE_REG_SHDW_Wr01(gPE_H10_1_E60,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_H10_1_E60,data,_r);}
#define PE_H10_1_E60_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_1_E60,data,_r);\
		PE_REG_SHDW_Wr02(gPE_H10_1_E60,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_H10_1_E60,data,_r);}
#define PE_H10_1_E60_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_1_E60,data,_r);\
		PE_REG_SHDW_Rd01(gPE_H10_1_E60,data,_r,_f1,_d1);}
#define PE_H10_1_E60_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_1_E60,data,_r);\
		PE_REG_SHDW_Rd02(gPE_H10_1_E60,data,_r,_f1,_d1,_f2,_d2);}

/* PE_S2H_0_E60 */
#define PE_S2H_0_E60_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_S2H_0_E60,data,_r)
#define PE_S2H_0_E60_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_S2H_0_E60,data,_r)
#define PE_S2H_0_E60_Rd(_r)				PE_REG_SHDW_Rd32(gPE_S2H_0_E60,data,_r)
#define PE_S2H_0_E60_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_S2H_0_E60,data,_r,_d1)
#define PE_S2H_0_E60_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_S2H_0_E60,data,_r,_f1,_d1)
#define PE_S2H_0_E60_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_S2H_0_E60,data,_r,_f1,_d1)

#define PE_S2H_0_E60_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_S2H_0_E60,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_S2H_0_E60,data,_r);}
#define PE_S2H_0_E60_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_S2H_0_E60,data,_r);\
		PE_REG_SHDW_Wr01(gPE_S2H_0_E60,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_S2H_0_E60,data,_r);}
#define PE_S2H_0_E60_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_S2H_0_E60,data,_r);\
		PE_REG_SHDW_Wr02(gPE_S2H_0_E60,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_S2H_0_E60,data,_r);}
#define PE_S2H_0_E60_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_S2H_0_E60,data,_r);\
		PE_REG_SHDW_Rd01(gPE_S2H_0_E60,data,_r,_f1,_d1);}
#define PE_S2H_0_E60_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_S2H_0_E60,data,_r);\
		PE_REG_SHDW_Rd02(gPE_S2H_0_E60,data,_r,_f1,_d1,_f2,_d2);}

/* PE_S2H_1_E60 */
#define PE_S2H_1_E60_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_S2H_1_E60,data,_r)
#define PE_S2H_1_E60_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_S2H_1_E60,data,_r)
#define PE_S2H_1_E60_Rd(_r)				PE_REG_SHDW_Rd32(gPE_S2H_1_E60,data,_r)
#define PE_S2H_1_E60_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_S2H_1_E60,data,_r,_d1)
#define PE_S2H_1_E60_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_S2H_1_E60,data,_r,_f1,_d1)
#define PE_S2H_1_E60_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_S2H_1_E60,data,_r,_f1,_d1)

#define PE_S2H_1_E60_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_S2H_1_E60,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_S2H_1_E60,data,_r);}
#define PE_S2H_1_E60_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_S2H_1_E60,data,_r);\
		PE_REG_SHDW_Wr01(gPE_S2H_1_E60,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_S2H_1_E60,data,_r);}
#define PE_S2H_1_E60_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_S2H_1_E60,data,_r);\
		PE_REG_SHDW_Wr02(gPE_S2H_1_E60,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_S2H_1_E60,data,_r);}
#define PE_S2H_1_E60_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_S2H_1_E60,data,_r);\
		PE_REG_SHDW_Rd01(gPE_S2H_1_E60,data,_r,_f1,_d1);}
#define PE_S2H_1_E60_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_S2H_1_E60,data,_r);\
		PE_REG_SHDW_Rd02(gPE_S2H_1_E60,data,_r,_f1,_d1,_f2,_d2);}

/* PE_HDR_VERI_E60 */
#define PE_HDR_VERI_E60_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_HDR_VERI_E60,data,_r)
#define PE_HDR_VERI_E60_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_HDR_VERI_E60,data,_r)
#define PE_HDR_VERI_E60_Rd(_r)				PE_REG_SHDW_Rd32(gPE_HDR_VERI_E60,data,_r)
#define PE_HDR_VERI_E60_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_HDR_VERI_E60,data,_r,_d1)
#define PE_HDR_VERI_E60_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_HDR_VERI_E60,data,_r,_f1,_d1)
#define PE_HDR_VERI_E60_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_HDR_VERI_E60,data,_r,_f1,_d1)

#define PE_HDR_VERI_E60_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_HDR_VERI_E60,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_HDR_VERI_E60,data,_r);}
#define PE_HDR_VERI_E60_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_HDR_VERI_E60,data,_r);\
		PE_REG_SHDW_Wr01(gPE_HDR_VERI_E60,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_HDR_VERI_E60,data,_r);}
#define PE_HDR_VERI_E60_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_HDR_VERI_E60,data,_r);\
		PE_REG_SHDW_Wr02(gPE_HDR_VERI_E60,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_HDR_VERI_E60,data,_r);}
#define PE_HDR_VERI_E60_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_HDR_VERI_E60,data,_r);\
		PE_REG_SHDW_Rd01(gPE_HDR_VERI_E60,data,_r,_f1,_d1);}
#define PE_HDR_VERI_E60_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_HDR_VERI_E60,data,_r);\
		PE_REG_SHDW_Rd02(gPE_HDR_VERI_E60,data,_r,_f1,_d1,_f2,_d2);}

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_E60_REG_H10_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_E60_REG_H10_T *data;
	} phys;
} PE_HDR_REG_E60_H10_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_E60_REG_S2H_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_E60_REG_S2H_T *data;
	} phys;
} PE_HDR_REG_E60_S2H_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_E60_REG_HDR_VERI_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_E60_REG_HDR_VERI_T *data;
	} phys;
} PE_HDR_REG_E60_VERI_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_HDR_REG_E60_H_ */

