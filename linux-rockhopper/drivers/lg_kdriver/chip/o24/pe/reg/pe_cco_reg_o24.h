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

/** @file pe_cco_reg_o24.h
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
#ifndef _PE_CCO_REG_O24_H_
#define _PE_CCO_REG_O24_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_cco_reg_o24a0.h"
#include "pe_osd_reg_o24a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/* PE_CC_PE1_O24 */
#define PE_CC_PE1_O24_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r)
#define PE_CC_PE1_O24_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_CC_PE1_O24,data,_r)
#define PE_CC_PE1_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_CC_PE1_O24,data,_r)
#define PE_CC_PE1_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_CC_PE1_O24,data,_r,_d1)
#define PE_CC_PE1_O24_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_CC_PE1_O24,data,_r,_f1,_d1)
#define PE_CC_PE1_O24_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_CC_PE1_O24,data,_r,_f1,_d1)

#define PE_CC_PE1_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_CC_PE1_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_CC_PE1_O24,data,_r);}
#define PE_CC_PE1_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_CC_PE1_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_CC_PE1_O24,data,_r);}
#define PE_CC_PE1_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_CC_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_CC_PE1_O24,data,_r);}
#define PE_CC_PE1_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_CC_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_CC_PE1_O24,data,_r);}
#define PE_CC_PE1_O24_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr05(gPE_CC_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_CC_PE1_O24,data,_r);}
#define PE_CC_PE1_O24_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr06(gPE_CC_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_CC_PE1_O24,data,_r);}
#define PE_CC_PE1_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_CC_PE1_O24,data,_r,_f1,_d1);}
#define PE_CC_PE1_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_CC_PE1_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_CC_PE1_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_CC_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_CC_PE1_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CC_PE1_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_CC_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}

/* PE_CC2_PE1_O24 */
#define PE_CC2_PE1_O24_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_CC2_PE1_O24,data,_r)
#define PE_CC2_PE1_O24_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_CC2_PE1_O24,data,_r)
#define PE_CC2_PE1_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_CC2_PE1_O24,data,_r)
#define PE_CC2_PE1_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_CC2_PE1_O24,data,_r,_d1)
#define PE_CC2_PE1_O24_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_CC2_PE1_O24,data,_r,_f1,_d1)
#define PE_CC2_PE1_O24_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_CC2_PE1_O24,data,_r,_f1,_d1)

#define PE_CC2_PE1_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CC2_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_CC2_PE1_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_CC2_PE1_O24,data,_r);}
#define PE_CC2_PE1_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CC2_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_CC2_PE1_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_CC2_PE1_O24,data,_r);}
#define PE_CC2_PE1_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CC2_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_CC2_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_CC2_PE1_O24,data,_r);}
#define PE_CC2_PE1_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CC2_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_CC2_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_CC2_PE1_O24,data,_r);}
#define PE_CC2_PE1_O24_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_CC2_PE1_O24,data,_r);\
		PE_REG_SHDW_Wr05(gPE_CC2_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_CC2_PE1_O24,data,_r);}
#define PE_CC2_PE1_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CC2_PE1_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_CC2_PE1_O24,data,_r,_f1,_d1);}
#define PE_CC2_PE1_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CC2_PE1_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_CC2_PE1_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_CC2_PE1_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CC2_PE1_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_CC2_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_CC2_PE1_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CC2_PE1_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_CC2_PE1_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}

/* PE_CCO1_VERI_O24 */
#define PE_CCO_VERI_O24_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_CCO_VERI_O24,data,_r)
#define PE_CCO_VERI_O24_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_CCO_VERI_O24,data,_r)
#define PE_CCO_VERI_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_CCO_VERI_O24,data,_r)
#define PE_CCO_VERI_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_CCO_VERI_O24,data,_r,_d1)
#define PE_CCO_VERI_O24_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_CCO_VERI_O24,data,_r,_f1,_d1)
#define PE_CCO_VERI_O24_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_CCO_VERI_O24,data,_r,_f1,_d1)

#define PE_CCO_VERI_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_VERI_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_CCO_VERI_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_CCO_VERI_O24,data,_r);}
#define PE_CCO_VERI_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_VERI_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_CCO_VERI_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_CCO_VERI_O24,data,_r);}
#define PE_CCO_VERI_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_VERI_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_CCO_VERI_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_CCO_VERI_O24,data,_r);}
#define PE_CCO_VERI_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_VERI_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_CCO_VERI_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_CCO_VERI_O24,data,_r);}
#define PE_CCO_VERI_O24_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_VERI_O24,data,_r);\
		PE_REG_SHDW_Wr05(gPE_CCO_VERI_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_CCO_VERI_O24,data,_r);}
#define PE_CCO_VERI_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_VERI_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_CCO_VERI_O24,data,_r,_f1,_d1);}
#define PE_CCO_VERI_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_VERI_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_CCO_VERI_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_CCO_VERI_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_VERI_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_CCO_VERI_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_CCO_VERI_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_VERI_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_CCO_VERI_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}

/* PE_CCO1_DECON_O24 */
#define PE_CCO_DECON_O24_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r)
#define PE_CCO_DECON_O24_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_CCO_DCNT_O24,data,_r)
#define PE_CCO_DECON_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_CCO_DCNT_O24,data,_r)
#define PE_CCO_DECON_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_CCO_DCNT_O24,data,_r,_d1)
#define PE_CCO_DECON_O24_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_CCO_DCNT_O24,data,_r,_f1,_d1)
#define PE_CCO_DECON_O24_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_CCO_DCNT_O24,data,_r,_f1,_d1)

#define PE_CCO_DECON_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_CCO_DCNT_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_CCO_DCNT_O24,data,_r);}
#define PE_CCO_DECON_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_CCO_DCNT_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_CCO_DCNT_O24,data,_r);}
#define PE_CCO_DECON_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_CCO_DCNT_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_CCO_DCNT_O24,data,_r);}
#define PE_CCO_DECON_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_CCO_DCNT_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_CCO_DCNT_O24,data,_r);}
#define PE_CCO_DECON_O24_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r);\
		PE_REG_SHDW_Wr05(gPE_CCO_DCNT_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_CCO_DCNT_O24,data,_r);}
#define PE_CCO_DECON_O24_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r);\
		PE_REG_SHDW_Wr06(gPE_CCO_DCNT_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_CCO_DCNT_O24,data,_r);}
#define PE_CCO_DECON_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_CCO_DCNT_O24,data,_r,_f1,_d1);}
#define PE_CCO_DECON_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_CCO_DCNT_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_CCO_DECON_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_CCO_DCNT_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_CCO_DECON_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CCO_DCNT_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_CCO_DCNT_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}


/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_CC_PE1_REG_O24_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_CC_PE1_REG_O24_T *data;
	} phys;
} PE_CC_PE1_REG_TYPE_O24_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_CC2_PE1_REG_O24_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_CC2_PE1_REG_O24_T *data;
	} phys;
} PE_CC2_PE1_REG_TYPE_O24_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_CCO_VERI_REG_O24_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_CCO_VERI_REG_O24_T *data;
	} phys;
} PE_CCO_VERI_REG_TYPE_O24_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_CCO_DECON_REG_O24_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_CCO_DECON_REG_O24_T *data;
	} phys;
} PE_CCO_DECON_REG_TYPE_O24_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_OSD_ORD_REG_O24_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_OSD_ORD_REG_O24_T *data;
	} phys;
} PE_OSD_ORD_REG_TYPE_O24_T;


/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_CCO_REG_O24_H_ */

