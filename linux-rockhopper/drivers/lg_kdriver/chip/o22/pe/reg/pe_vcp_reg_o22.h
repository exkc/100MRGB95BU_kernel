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

/** @file pe_vcp_reg_o22.h
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
#ifndef _PE_VCP_REG_O22_H_
#define _PE_VCP_REG_O22_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_vcp_reg_o22a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
/* PE_VCP_DISP_O22 */
#define PE_VCP_DISP_O22_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_VCP_DISP_O22,data,_r)
#define PE_VCP_DISP_O22_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_VCP_DISP_O22,data,_r)
#define PE_VCP_DISP_O22_Rd(_r)			PE_REG_SHDW_Rd32(gPE_VCP_DISP_O22,data,_r)
#define PE_VCP_DISP_O22_Wr(_r,_d1)		PE_REG_SHDW_Wr32(gPE_VCP_DISP_O22,data,_r,_d1)
#define PE_VCP_DISP_O22_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_VCP_DISP_O22,data,_r,_f1,_d1)
#define PE_VCP_DISP_O22_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_VCP_DISP_O22,data,_r,_f1,_d1)

#define PE_VCP_DISP_O22_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_O22,data,_r);\
		PE_REG_SHDW_Wr01(gPE_VCP_DISP_O22,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_VCP_DISP_O22,data,_r);}
#define PE_VCP_DISP_O22_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_O22,data,_r);\
		PE_REG_SHDW_Wr02(gPE_VCP_DISP_O22,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_VCP_DISP_O22,data,_r);}
#define PE_VCP_DISP_O22_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_O22,data,_r);\
		PE_REG_SHDW_Wr03(gPE_VCP_DISP_O22,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_VCP_DISP_O22,data,_r);}
#define PE_VCP_DISP_O22_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_O22,data,_r);\
		PE_REG_SHDW_Wr04(gPE_VCP_DISP_O22,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_VCP_DISP_O22,data,_r);}
#define PE_VCP_DISP_O22_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_O22,data,_r);\
		PE_REG_SHDW_Rd01(gPE_VCP_DISP_O22,data,_r,_f1,_d1);}
#define PE_VCP_DISP_O22_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_O22,data,_r);\
		PE_REG_SHDW_Rd02(gPE_VCP_DISP_O22,data,_r,_f1,_d1,_f2,_d2);}
#define PE_VCP_DISP_O22_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_O22,data,_r);\
		PE_REG_SHDW_Rd03(gPE_VCP_DISP_O22,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_VCP_DISP_O22_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_O22,data,_r);\
		PE_REG_SHDW_Rd04(gPE_VCP_DISP_O22,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#if 0
/* PE_VCP_DE_O22 */
#define PE_VCP_DE_O22_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_VCP_DE_O22,data,_r)
#define PE_VCP_DE_O22_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_VCP_DE_O22,data,_r)
#define PE_VCP_DE_O22_Rd(_r)			PE_REG_SHDW_Rd32(gPE_VCP_DE_O22,data,_r)
#define PE_VCP_DE_O22_Wr(_r,_d1)		PE_REG_SHDW_Wr32(gPE_VCP_DE_O22,data,_r,_d1)
#define PE_VCP_DE_O22_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_VCP_DE_O22,data,_r,_f1,_d1)
#define PE_VCP_DE_O22_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_VCP_DE_O22,data,_r,_f1,_d1)

#define PE_VCP_DE_O22_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DE_O22,data,_r);\
		PE_REG_SHDW_Wr01(gPE_VCP_DE_O22,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_VCP_DE_O22,data,_r);}
#define PE_VCP_DE_O22_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DE_O22,data,_r);\
		PE_REG_SHDW_Wr02(gPE_VCP_DE_O22,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_VCP_DE_O22,data,_r);}
#define PE_VCP_DE_O22_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DE_O22,data,_r);\
		PE_REG_SHDW_Rd01(gPE_VCP_DE_O22,data,_r,_f1,_d1);}
#define PE_VCP_DE_O22_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DE_O22,data,_r);\
		PE_REG_SHDW_Rd02(gPE_VCP_DE_O22,data,_r,_f1,_d1,_f2,_d2);}
#endif

/* PE_VSD0_VERI_O22 */
#define PE_VSD0_VERI_O22_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_VSD0_VERI_O22,data,_r)
#define PE_VSD0_VERI_O22_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_VSD0_VERI_O22,data,_r)
#define PE_VSD0_VERI_O22_Rd(_r)				PE_REG_SHDW_Rd32(gPE_VSD0_VERI_O22,data,_r)
#define PE_VSD0_VERI_O22_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_VSD0_VERI_O22,data,_r,_d1)
#define PE_VSD0_VERI_O22_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_VSD0_VERI_O22,data,_r,_f1,_d1)
#define PE_VSD0_VERI_O22_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_VSD0_VERI_O22,data,_r,_f1,_d1)

#define PE_VSD0_VERI_O22_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD0_VERI_O22,data,_r);\
		PE_REG_SHDW_Wr01(gPE_VSD0_VERI_O22,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_VSD0_VERI_O22,data,_r);}
#define PE_VSD0_VERI_O22_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD0_VERI_O22,data,_r);\
		PE_REG_SHDW_Wr02(gPE_VSD0_VERI_O22,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_VSD0_VERI_O22,data,_r);}
#define PE_VSD0_VERI_O22_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD0_VERI_O22,data,_r);\
		PE_REG_SHDW_Wr03(gPE_VSD0_VERI_O22,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_VSD0_VERI_O22,data,_r);}
#define PE_VSD0_VERI_O22_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD0_VERI_O22,data,_r);\
		PE_REG_SHDW_Rd01(gPE_VSD0_VERI_O22,data,_r,_f1,_d1);}
#define PE_VSD0_VERI_O22_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD0_VERI_O22,data,_r);\
		PE_REG_SHDW_Rd02(gPE_VSD0_VERI_O22,data,_r,_f1,_d1,_f2,_d2);}

/* PE_VSD1_VERI_O22 */
#define PE_VSD1_VERI_O22_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_VSD1_VERI_O22,data,_r)
#define PE_VSD1_VERI_O22_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_VSD1_VERI_O22,data,_r)
#define PE_VSD1_VERI_O22_Rd(_r)				PE_REG_SHDW_Rd32(gPE_VSD1_VERI_O22,data,_r)
#define PE_VSD1_VERI_O22_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_VSD1_VERI_O22,data,_r,_d1)
#define PE_VSD1_VERI_O22_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_VSD1_VERI_O22,data,_r,_f1,_d1)
#define PE_VSD1_VERI_O22_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_VSD1_VERI_O22,data,_r,_f1,_d1)

#define PE_VSD1_VERI_O22_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD1_VERI_O22,data,_r);\
		PE_REG_SHDW_Wr01(gPE_VSD1_VERI_O22,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_VSD1_VERI_O22,data,_r);}
#define PE_VSD1_VERI_O22_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD1_VERI_O22,data,_r);\
		PE_REG_SHDW_Wr02(gPE_VSD1_VERI_O22,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_VSD1_VERI_O22,data,_r);}
#define PE_VSD1_VERI_O22_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD1_VERI_O22,data,_r);\
		PE_REG_SHDW_Wr03(gPE_VSD1_VERI_O22,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_VSD1_VERI_O22,data,_r);}
#define PE_VSD1_VERI_O22_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD1_VERI_O22,data,_r);\
		PE_REG_SHDW_Rd01(gPE_VSD1_VERI_O22,data,_r,_f1,_d1);}
#define PE_VSD1_VERI_O22_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD1_VERI_O22,data,_r);\
		PE_REG_SHDW_Rd02(gPE_VSD1_VERI_O22,data,_r,_f1,_d1,_f2,_d2);}

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_VCP_DISP_REG_O22_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_VCP_DISP_REG_O22_T *data;
	} phys;
} PE_VCP_DISP_REG_TYPE_O22_T;
#if 0
/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_VCP_DE_REG_O22_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_VCP_DE_REG_O22_T *data;
	} phys;
} PE_VCP_DE_REG_TYPE_O22_T;
#endif

typedef struct {
	union {
		UINT32			*addr;
		PE_VSD0_VERI_REG_O22_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_VSD0_VERI_REG_O22_T *data;
	} phys;
} PE_VSD0_VERI_REG_TYPE_O22_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_VCP_REG_M16_H_ */

