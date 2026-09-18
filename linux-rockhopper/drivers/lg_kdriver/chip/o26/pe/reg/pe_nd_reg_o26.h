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

/** @file pe_nd_reg_o26.h
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
#ifndef _PE_ND_REG_O26_H_
#define _PE_ND_REG_O26_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_nd_reg_o26a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/* PE_ND0_O26 */
#define PE_ND0_O26_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r)
#define PE_ND0_O26_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r)
#define PE_ND0_O26_Rd(_r)				PE_REG_SHDW_Rd32(gPE_ND0_O26,data,_r)
#define PE_ND0_O26_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_ND0_O26,data,_r,_d1)
#define PE_ND0_O26_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_ND0_O26,data,_r,_f1,_d1)
#define PE_ND0_O26_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_ND0_O26,data,_r,_f1,_d1)

#define PE_ND0_O26_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_ND0_O26,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r);}
#define PE_ND0_O26_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Wr01(gPE_ND0_O26,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r);}
#define PE_ND0_O26_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Wr02(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r);}
#define PE_ND0_O26_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Wr03(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r);}
#define PE_ND0_O26_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Wr04(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r);}
#define PE_ND0_O26_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Wr05(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r);}
#define PE_ND0_O26_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Wr06(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r);}
#define PE_ND0_O26_QWr07(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Wr07(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7);\
		PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r);}
#define PE_ND0_O26_QWr09(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Wr09(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9);\
		PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r);}
#define PE_ND0_O26_QWr10(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Wr10(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);\
		PE_REG_PHYS_WrFL(gPE_ND0_O26,data,_r);}


#define PE_ND0_O26_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Rd01(gPE_ND0_O26,data,_r,_f1,_d1);}
#define PE_ND0_O26_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Rd02(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2);}
#define PE_ND0_O26_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Rd03(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_ND0_O26_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Rd04(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_ND0_O26_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Rd05(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}
#define PE_ND0_O26_QRd06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Rd06(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);}
#define PE_ND0_O26_QRd07(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Rd07(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7);}
#define PE_ND0_O26_QRd09(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Rd09(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9);}
#define PE_ND0_O26_QRd10(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_REG_PHYS_RdFL(gPE_ND0_O26,data,_r);\
		PE_REG_SHDW_Rd10(gPE_ND0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);}

/* PE_ND1_O26 */
#define PE_ND1_O26_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r)
#define PE_ND1_O26_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r)
#define PE_ND1_O26_Rd(_r)				PE_REG_SHDW_Rd32(gPE_ND1_O26,data,_r)
#define PE_ND1_O26_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_ND1_O26,data,_r,_d1)
#define PE_ND1_O26_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_ND1_O26,data,_r,_f1,_d1)
#define PE_ND1_O26_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_ND1_O26,data,_r,_f1,_d1)

#define PE_ND1_O26_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_ND1_O26,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r);}
#define PE_ND1_O26_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Wr01(gPE_ND1_O26,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r);}
#define PE_ND1_O26_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Wr02(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r);}
#define PE_ND1_O26_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Wr03(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r);}
#define PE_ND1_O26_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Wr04(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r);}
#define PE_ND1_O26_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Wr05(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r);}
#define PE_ND1_O26_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Wr06(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r);}
#define PE_ND1_O26_QWr07(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Wr07(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7);\
		PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r);}
#define PE_ND1_O26_QWr09(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Wr09(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9);\
		PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r);}
#define PE_ND1_O26_QWr10(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Wr10(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);\
		PE_REG_PHYS_WrFL(gPE_ND1_O26,data,_r);}

#define PE_ND1_O26_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Rd01(gPE_ND1_O26,data,_r,_f1,_d1);}
#define PE_ND1_O26_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Rd02(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2);}
#define PE_ND1_O26_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Rd03(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_ND1_O26_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Rd04(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_ND1_O26_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Rd05(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}
#define PE_ND1_O26_QRd06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Rd06(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);}
#define PE_ND1_O26_QRd07(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Rd07(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7);}
#define PE_ND1_O26_QRd09(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Rd09(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9);}
#define PE_ND1_O26_QRd10(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_REG_PHYS_RdFL(gPE_ND1_O26,data,_r);\
		PE_REG_SHDW_Rd10(gPE_ND1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);}

/* PE_ND2_O26 */
#define PE_ND2_O26_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r)
#define PE_ND2_O26_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r)
#define PE_ND2_O26_Rd(_r)				PE_REG_SHDW_Rd32(gPE_ND2_O26,data,_r)
#define PE_ND2_O26_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_ND2_O26,data,_r,_d1)
#define PE_ND2_O26_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_ND2_O26,data,_r,_f1,_d1)
#define PE_ND2_O26_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_ND2_O26,data,_r,_f1,_d1)

#define PE_ND2_O26_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_ND2_O26,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r);}
#define PE_ND2_O26_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Wr01(gPE_ND2_O26,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r);}
#define PE_ND2_O26_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Wr02(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r);}
#define PE_ND2_O26_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Wr03(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r);}
#define PE_ND2_O26_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Wr04(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r);}
#define PE_ND2_O26_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Wr05(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r);}
#define PE_ND2_O26_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Wr06(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r);}
#define PE_ND2_O26_QWr07(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Wr07(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7);\
		PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r);}
#define PE_ND2_O26_QWr09(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Wr09(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9);\
		PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r);}
#define PE_ND2_O26_QWr10(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Wr10(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);\
		PE_REG_PHYS_WrFL(gPE_ND2_O26,data,_r);}

#define PE_ND2_O26_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Rd01(gPE_ND2_O26,data,_r,_f1,_d1);}
#define PE_ND2_O26_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Rd02(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2);}
#define PE_ND2_O26_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Rd03(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_ND2_O26_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Rd04(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_ND2_O26_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Rd05(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}
#define PE_ND2_O26_QRd06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Rd06(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);}
#define PE_ND2_O26_QRd07(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Rd07(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7);}
#define PE_ND2_O26_QRd09(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Rd09(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9);}
#define PE_ND2_O26_QRd10(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10)	\
	{	PE_REG_PHYS_RdFL(gPE_ND2_O26,data,_r);\
		PE_REG_SHDW_Rd10(gPE_ND2_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7,_f8,_d8,_f9,_d9,_f10,_d10);}

/* PE_DNR0_O26 */
#define PE_DNR0_O26_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r)
#define PE_DNR0_O26_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_DNR0_O26,data,_r)
#define PE_DNR0_O26_Rd(_r)				PE_REG_SHDW_Rd32(gPE_DNR0_O26,data,_r)
#define PE_DNR0_O26_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_DNR0_O26,data,_r,_d1)
#define PE_DNR0_O26_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_DNR0_O26,data,_r,_f1,_d1)
#define PE_DNR0_O26_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_DNR0_O26,data,_r,_f1,_d1)

#define PE_DNR0_O26_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Wr01(gPE_DNR0_O26,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_DNR0_O26,data,_r);}
#define PE_DNR0_O26_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Wr02(gPE_DNR0_O26,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_DNR0_O26,data,_r);}
#define PE_DNR0_O26_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Wr03(gPE_DNR0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_DNR0_O26,data,_r);}
#define PE_DNR0_O26_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Wr04(gPE_DNR0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_DNR0_O26,data,_r);}
#define PE_DNR0_O26_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Wr05(gPE_DNR0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_DNR0_O26,data,_r);}
#define PE_DNR0_O26_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Wr06(gPE_DNR0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_DNR0_O26,data,_r);}
#define PE_DNR0_O26_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Rd01(gPE_DNR0_O26,data,_r,_f1,_d1);}
#define PE_DNR0_O26_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Rd02(gPE_DNR0_O26,data,_r,_f1,_d1,_f2,_d2);}
#define PE_DNR0_O26_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Rd03(gPE_DNR0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_DNR0_O26_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Rd04(gPE_DNR0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_DNR0_O26_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Rd05(gPE_DNR0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}
#define PE_DNR0_O26_QRd06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR0_O26,data,_r);\
		PE_REG_SHDW_Rd06(gPE_DNR0_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);}

/* PE_DNR1_O26 */
#define PE_DNR1_O26_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r)
#define PE_DNR1_O26_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_DNR1_O26,data,_r)
#define PE_DNR1_O26_Rd(_r)				PE_REG_SHDW_Rd32(gPE_DNR1_O26,data,_r)
#define PE_DNR1_O26_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_DNR1_O26,data,_r,_d1)
#define PE_DNR1_O26_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_DNR1_O26,data,_r,_f1,_d1)
#define PE_DNR1_O26_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_DNR1_O26,data,_r,_f1,_d1)

#define PE_DNR1_O26_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Wr01(gPE_DNR1_O26,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_DNR1_O26,data,_r);}
#define PE_DNR1_O26_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Wr02(gPE_DNR1_O26,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_DNR1_O26,data,_r);}
#define PE_DNR1_O26_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Wr03(gPE_DNR1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_DNR1_O26,data,_r);}
#define PE_DNR1_O26_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Wr04(gPE_DNR1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_DNR1_O26,data,_r);}
#define PE_DNR1_O26_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Wr05(gPE_DNR1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_DNR1_O26,data,_r);}
#define PE_DNR1_O26_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Wr06(gPE_DNR1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_DNR1_O26,data,_r);}
#define PE_DNR1_O26_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Rd01(gPE_DNR1_O26,data,_r,_f1,_d1);}
#define PE_DNR1_O26_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Rd02(gPE_DNR1_O26,data,_r,_f1,_d1,_f2,_d2);}
#define PE_DNR1_O26_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Rd03(gPE_DNR1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_DNR1_O26_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Rd04(gPE_DNR1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_DNR1_O26_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Rd05(gPE_DNR1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}
#define PE_DNR1_O26_QRd06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_DNR1_O26,data,_r);\
		PE_REG_SHDW_Rd06(gPE_DNR1_O26,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);}

/* PE_IMX_O26 */
#define PE_IMX_O26_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_TOP_IMX_O26,data,_r)
#define PE_IMX_O26_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_TOP_IMX_O26,data,_r)
#define PE_IMX_O26_Rd(_r)				PE_REG_SHDW_Rd32(gPE_TOP_IMX_O26,data,_r)
#define PE_IMX_O26_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_TOP_IMX_O26,data,_r,_d1)
#define PE_IMX_O26_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_TOP_IMX_O26,data,_r,_f1,_d1)
#define PE_IMX_O26_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_TOP_IMX_O26,data,_r,_f1,_d1)

#define PE_ND0_VERI_O26_QWr02(_r,_f1,_d1,_f2,_d2)	\
{	PE_REG_PHYS_RdFL(gPE_ND0_VERI_O26,data,_r);\
	PE_REG_SHDW_Wr02(gPE_ND0_VERI_O26,data,_r,_f1,_d1,_f2,_d2);\
	PE_REG_PHYS_WrFL(gPE_ND0_VERI_O26,data,_r);}

#define PE_ND1_VERI_O26_QWr02(_r,_f1,_d1,_f2,_d2)	\
{	PE_REG_PHYS_RdFL(gPE_ND1_VERI_O26,data,_r);\
	PE_REG_SHDW_Wr02(gPE_ND1_VERI_O26,data,_r,_f1,_d1,_f2,_d2);\
	PE_REG_PHYS_WrFL(gPE_ND1_VERI_O26,data,_r);}


/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_ND_REG_O26_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_ND_REG_O26_T *data;
	} phys;
} PE_ND_REG_TYPE_O26_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_DNR0_REG_O26_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_DNR0_REG_O26_T *data;
	} phys;
} PE_DNR0_REG_TYPE_O26_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_DNR1_REG_O26_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_DNR1_REG_O26_T *data;
	} phys;
} PE_DNR1_REG_TYPE_O26_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_ND0_VERI_REG_O26_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_ND0_VERI_REG_O26_T *data;
	} phys;
} PE_ND0_VERI_REG_TYPE_O26_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_ND1_VERI_REG_O26_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_ND1_VERI_REG_O26_T *data;
	} phys;
} PE_ND1_VERI_REG_TYPE_O26_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_TOP_IMX_REG_O26_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_TOP_IMX_REG_O26_T *data;
	} phys;
} PE_TOP_IMX_REG_TYPE_O26_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_ND_REG_O26_H_ */

