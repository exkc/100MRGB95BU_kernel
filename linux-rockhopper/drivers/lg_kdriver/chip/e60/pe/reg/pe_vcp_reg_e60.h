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

/** @file pe_vcp_reg_e60.h
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
#ifndef _PE_VCP_REG_E60_H_
#define _PE_VCP_REG_E60_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_vcp_reg_e60a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
/* PE_VCP_DISP_E60 */
#define PE_VCP_DISP_E60_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_VCP_DISP_E60,data,_r)
#define PE_VCP_DISP_E60_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_VCP_DISP_E60,data,_r)
#define PE_VCP_DISP_E60_Rd(_r)			PE_REG_SHDW_Rd32(gPE_VCP_DISP_E60,data,_r)
#define PE_VCP_DISP_E60_Wr(_r,_d1)		PE_REG_SHDW_Wr32(gPE_VCP_DISP_E60,data,_r,_d1)
#define PE_VCP_DISP_E60_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_VCP_DISP_E60,data,_r,_f1,_d1)
#define PE_VCP_DISP_E60_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_VCP_DISP_E60,data,_r,_f1,_d1)

#define PE_VCP_DISP_E60_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_E60,data,_r);\
		PE_REG_SHDW_Wr01(gPE_VCP_DISP_E60,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_VCP_DISP_E60,data,_r);}
#define PE_VCP_DISP_E60_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_E60,data,_r);\
		PE_REG_SHDW_Wr02(gPE_VCP_DISP_E60,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_VCP_DISP_E60,data,_r);}
#define PE_VCP_DISP_E60_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_E60,data,_r);\
		PE_REG_SHDW_Wr03(gPE_VCP_DISP_E60,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_VCP_DISP_E60,data,_r);}
#define PE_VCP_DISP_E60_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_E60,data,_r);\
		PE_REG_SHDW_Wr04(gPE_VCP_DISP_E60,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_VCP_DISP_E60,data,_r);}
#define PE_VCP_DISP_E60_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_E60,data,_r);\
		PE_REG_SHDW_Rd01(gPE_VCP_DISP_E60,data,_r,_f1,_d1);}
#define PE_VCP_DISP_E60_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_E60,data,_r);\
		PE_REG_SHDW_Rd02(gPE_VCP_DISP_E60,data,_r,_f1,_d1,_f2,_d2);}
#define PE_VCP_DISP_E60_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_E60,data,_r);\
		PE_REG_SHDW_Rd03(gPE_VCP_DISP_E60,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_VCP_DISP_E60_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DISP_E60,data,_r);\
		PE_REG_SHDW_Rd04(gPE_VCP_DISP_E60,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#if 0
/* PE_VCP_DE_E60 */
#define PE_VCP_DE_E60_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_VCP_DE_E60,data,_r)
#define PE_VCP_DE_E60_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_VCP_DE_E60,data,_r)
#define PE_VCP_DE_E60_Rd(_r)			PE_REG_SHDW_Rd32(gPE_VCP_DE_E60,data,_r)
#define PE_VCP_DE_E60_Wr(_r,_d1)		PE_REG_SHDW_Wr32(gPE_VCP_DE_E60,data,_r,_d1)
#define PE_VCP_DE_E60_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_VCP_DE_E60,data,_r,_f1,_d1)
#define PE_VCP_DE_E60_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_VCP_DE_E60,data,_r,_f1,_d1)

#define PE_VCP_DE_E60_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DE_E60,data,_r);\
		PE_REG_SHDW_Wr01(gPE_VCP_DE_E60,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_VCP_DE_E60,data,_r);}
#define PE_VCP_DE_E60_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DE_E60,data,_r);\
		PE_REG_SHDW_Wr02(gPE_VCP_DE_E60,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_VCP_DE_E60,data,_r);}
#define PE_VCP_DE_E60_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DE_E60,data,_r);\
		PE_REG_SHDW_Rd01(gPE_VCP_DE_E60,data,_r,_f1,_d1);}
#define PE_VCP_DE_E60_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VCP_DE_E60,data,_r);\
		PE_REG_SHDW_Rd02(gPE_VCP_DE_E60,data,_r,_f1,_d1,_f2,_d2);}
#endif

/* PE_VSD0_VERI_E60 */
#define PE_VSD0_VERI_E60_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_VSD0_VERI_E60,data,_r)
#define PE_VSD0_VERI_E60_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_VSD0_VERI_E60,data,_r)
#define PE_VSD0_VERI_E60_Rd(_r)				PE_REG_SHDW_Rd32(gPE_VSD0_VERI_E60,data,_r)
#define PE_VSD0_VERI_E60_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_VSD0_VERI_E60,data,_r,_d1)
#define PE_VSD0_VERI_E60_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_VSD0_VERI_E60,data,_r,_f1,_d1)
#define PE_VSD0_VERI_E60_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_VSD0_VERI_E60,data,_r,_f1,_d1)

#define PE_VSD0_VERI_E60_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD0_VERI_E60,data,_r);\
		PE_REG_SHDW_Wr01(gPE_VSD0_VERI_E60,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_VSD0_VERI_E60,data,_r);}
#define PE_VSD0_VERI_E60_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD0_VERI_E60,data,_r);\
		PE_REG_SHDW_Wr02(gPE_VSD0_VERI_E60,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_VSD0_VERI_E60,data,_r);}
#define PE_VSD0_VERI_E60_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD0_VERI_E60,data,_r);\
		PE_REG_SHDW_Wr03(gPE_VSD0_VERI_E60,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_VSD0_VERI_E60,data,_r);}
#define PE_VSD0_VERI_E60_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD0_VERI_E60,data,_r);\
		PE_REG_SHDW_Rd01(gPE_VSD0_VERI_E60,data,_r,_f1,_d1);}
#define PE_VSD0_VERI_E60_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD0_VERI_E60,data,_r);\
		PE_REG_SHDW_Rd02(gPE_VSD0_VERI_E60,data,_r,_f1,_d1,_f2,_d2);}

/* PE_VSD1_VERI_E60 */
#define PE_VSD1_VERI_E60_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_VSD1_VERI_E60,data,_r)
#define PE_VSD1_VERI_E60_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_VSD1_VERI_E60,data,_r)
#define PE_VSD1_VERI_E60_Rd(_r)				PE_REG_SHDW_Rd32(gPE_VSD1_VERI_E60,data,_r)
#define PE_VSD1_VERI_E60_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_VSD1_VERI_E60,data,_r,_d1)
#define PE_VSD1_VERI_E60_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_VSD1_VERI_E60,data,_r,_f1,_d1)
#define PE_VSD1_VERI_E60_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_VSD1_VERI_E60,data,_r,_f1,_d1)

#define PE_VSD1_VERI_E60_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD1_VERI_E60,data,_r);\
		PE_REG_SHDW_Wr01(gPE_VSD1_VERI_E60,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_VSD1_VERI_E60,data,_r);}
#define PE_VSD1_VERI_E60_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD1_VERI_E60,data,_r);\
		PE_REG_SHDW_Wr02(gPE_VSD1_VERI_E60,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_VSD1_VERI_E60,data,_r);}
#define PE_VSD1_VERI_E60_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD1_VERI_E60,data,_r);\
		PE_REG_SHDW_Wr03(gPE_VSD1_VERI_E60,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_VSD1_VERI_E60,data,_r);}
#define PE_VSD1_VERI_E60_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD1_VERI_E60,data,_r);\
		PE_REG_SHDW_Rd01(gPE_VSD1_VERI_E60,data,_r,_f1,_d1);}
#define PE_VSD1_VERI_E60_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD1_VERI_E60,data,_r);\
		PE_REG_SHDW_Rd02(gPE_VSD1_VERI_E60,data,_r,_f1,_d1,_f2,_d2);}

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_VCP_DISP_REG_E60_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_VCP_DISP_REG_E60_T *data;
	} phys;
} PE_VCP_DISP_REG_TYPE_E60_T;
#if 0
/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_VCP_DE_REG_E60_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_VCP_DE_REG_E60_T *data;
	} phys;
} PE_VCP_DE_REG_TYPE_E60_T;
#endif

typedef struct {
	union {
		UINT32			*addr;
		PE_VSD0_VERI_REG_E60_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_VSD0_VERI_REG_E60_T *data;
	} phys;
} PE_VSD0_VERI_REG_TYPE_E60_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_VSD1_VERI_REG_E60_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_VSD1_VERI_REG_E60_T *data;
	} phys;
} PE_VSD1_VERI_REG_TYPE_E60_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_VCP_REG_M16_H_ */

