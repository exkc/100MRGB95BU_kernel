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

/** @file pe_nd_reg_o18.h
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
#ifndef _PE_ND_REG_O18_H_
#define _PE_ND_REG_O18_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_nd_reg_o18a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/* PE_ND0_O18 */
#define PE_ND0_O18_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r)
#define PE_ND0_O18_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_ND_ND0_O18,data,_r)
#define PE_ND0_O18_Rd(_r)				PE_REG_SHDW_Rd32(gPE_ND_ND0_O18,data,_r)
#define PE_ND0_O18_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_ND_ND0_O18,data,_r,_d1)
#define PE_ND0_O18_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_ND_ND0_O18,data,_r,_f1,_d1)
#define PE_ND0_O18_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_ND_ND0_O18,data,_r,_f1,_d1)

#define PE_ND0_O18_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_ND_ND0_O18,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND_ND0_O18,data,_r);}
#define PE_ND0_O18_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Wr01(gPE_ND_ND0_O18,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND_ND0_O18,data,_r);}
#define PE_ND0_O18_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Wr02(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_ND_ND0_O18,data,_r);}
#define PE_ND0_O18_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Wr03(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_ND_ND0_O18,data,_r);}
#define PE_ND0_O18_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Wr04(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_ND_ND0_O18,data,_r);}
#define PE_ND0_O18_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Wr05(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_ND_ND0_O18,data,_r);}
#define PE_ND0_O18_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Wr06(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_ND_ND0_O18,data,_r);}
#define PE_ND0_O18_QWr07(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Wr07(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7);\
		PE_REG_PHYS_WrFL(gPE_ND_ND0_O18,data,_r);}
#define PE_ND0_O18_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Rd01(gPE_ND_ND0_O18,data,_r,_f1,_d1);}
#define PE_ND0_O18_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Rd02(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2);}
#define PE_ND0_O18_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Rd03(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_ND0_O18_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Rd04(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_ND0_O18_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Rd05(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}
#define PE_ND0_O18_QRd06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Rd06(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);}
#define PE_ND0_O18_QRd07(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND0_O18,data,_r);\
		PE_REG_SHDW_Rd07(gPE_ND_ND0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7);}

/* PE_ND1_O18 */
#define PE_ND1_O18_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r)
#define PE_ND1_O18_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_ND_ND1_O18,data,_r)
#define PE_ND1_O18_Rd(_r)				PE_REG_SHDW_Rd32(gPE_ND_ND1_O18,data,_r)
#define PE_ND1_O18_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_ND_ND1_O18,data,_r,_d1)
#define PE_ND1_O18_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_ND_ND1_O18,data,_r,_f1,_d1)
#define PE_ND1_O18_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_ND_ND1_O18,data,_r,_f1,_d1)

#define PE_ND1_O18_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_ND_ND1_O18,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND_ND1_O18,data,_r);}
#define PE_ND1_O18_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Wr01(gPE_ND_ND1_O18,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND_ND1_O18,data,_r);}
#define PE_ND1_O18_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Wr02(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_ND_ND1_O18,data,_r);}
#define PE_ND1_O18_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Wr03(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_ND_ND1_O18,data,_r);}
#define PE_ND1_O18_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Wr04(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_ND_ND1_O18,data,_r);}
#define PE_ND1_O18_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Wr05(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_ND_ND1_O18,data,_r);}
#define PE_ND1_O18_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Wr06(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_ND_ND1_O18,data,_r);}
#define PE_ND1_O18_QWr07(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Wr07(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7);\
		PE_REG_PHYS_WrFL(gPE_ND_ND1_O18,data,_r);}
#define PE_ND1_O18_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Rd01(gPE_ND_ND1_O18,data,_r,_f1,_d1);}
#define PE_ND1_O18_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Rd02(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2);}
#define PE_ND1_O18_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Rd03(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_ND1_O18_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Rd04(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_ND1_O18_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Rd05(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}
#define PE_ND1_O18_QRd06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Rd06(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);}
#define PE_ND1_O18_QRd07(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_ND1_O18,data,_r);\
		PE_REG_SHDW_Rd07(gPE_ND_ND1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7);}


/* PE_DNR0_O18 */
#define PE_DNR0_O18_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r)
#define PE_DNR0_O18_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_ND_DNR0_O18,data,_r)
#define PE_DNR0_O18_Rd(_r)				PE_REG_SHDW_Rd32(gPE_ND_DNR0_O18,data,_r)
#define PE_DNR0_O18_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_ND_DNR0_O18,data,_r,_d1)
#define PE_DNR0_O18_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_ND_DNR0_O18,data,_r,_f1,_d1)
#define PE_DNR0_O18_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_ND_DNR0_O18,data,_r,_f1,_d1)

#define PE_DNR0_O18_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Wr01(gPE_ND_DNR0_O18,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR0_O18,data,_r);}
#define PE_DNR0_O18_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Wr02(gPE_ND_DNR0_O18,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR0_O18,data,_r);}
#define PE_DNR0_O18_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Wr03(gPE_ND_DNR0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR0_O18,data,_r);}
#define PE_DNR0_O18_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Wr04(gPE_ND_DNR0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR0_O18,data,_r);}
#define PE_DNR0_O18_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Wr05(gPE_ND_DNR0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR0_O18,data,_r);}
#define PE_DNR0_O18_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Wr06(gPE_ND_DNR0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR0_O18,data,_r);}
#define PE_DNR0_O18_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Rd01(gPE_ND_DNR0_O18,data,_r,_f1,_d1);}
#define PE_DNR0_O18_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Rd02(gPE_ND_DNR0_O18,data,_r,_f1,_d1,_f2,_d2);}
#define PE_DNR0_O18_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Rd03(gPE_ND_DNR0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_DNR0_O18_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Rd04(gPE_ND_DNR0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_DNR0_O18_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Rd05(gPE_ND_DNR0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}
#define PE_DNR0_O18_QRd06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR0_O18,data,_r);\
		PE_REG_SHDW_Rd06(gPE_ND_DNR0_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);}

/* PE_DNR0_O18 */
#define PE_DNR1_O18_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r)
#define PE_DNR1_O18_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_ND_DNR1_O18,data,_r)
#define PE_DNR1_O18_Rd(_r)				PE_REG_SHDW_Rd32(gPE_ND_DNR1_O18,data,_r)
#define PE_DNR1_O18_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_ND_DNR1_O18,data,_r,_d1)
#define PE_DNR1_O18_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_ND_DNR1_O18,data,_r,_f1,_d1)
#define PE_DNR1_O18_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_ND_DNR1_O18,data,_r,_f1,_d1)

#define PE_DNR1_O18_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r);\
		PE_REG_SHDW_Wr01(gPE_ND_DNR1_O18,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR1_O18,data,_r);}
#define PE_DNR1_O18_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r);\
		PE_REG_SHDW_Wr02(gPE_ND_DNR1_O18,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR1_O18,data,_r);}
#define PE_DNR1_O18_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r);\
		PE_REG_SHDW_Wr03(gPE_ND_DNR1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR1_O18,data,_r);}
#define PE_DNR1_O18_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r);\
		PE_REG_SHDW_Wr04(gPE_ND_DNR1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR1_O18,data,_r);}
#define PE_DNR1_O18_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r);\
		PE_REG_SHDW_Wr05(gPE_ND_DNR1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_ND_DNR1_O18,data,_r);}
#define PE_DNR1_O18_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r);\
		PE_REG_SHDW_Rd01(gPE_ND_DNR1_O18,data,_r,_f1,_d1);}
#define PE_DNR1_O18_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r);\
		PE_REG_SHDW_Rd02(gPE_ND_DNR1_O18,data,_r,_f1,_d1,_f2,_d2);}
#define PE_DNR1_O18_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r);\
		PE_REG_SHDW_Rd03(gPE_ND_DNR1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_DNR1_O18_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r);\
		PE_REG_SHDW_Rd04(gPE_ND_DNR1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_DNR1_O18_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_ND_DNR1_O18,data,_r);\
		PE_REG_SHDW_Rd05(gPE_ND_DNR1_O18,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}


/* PE_IMX_O18 */
#define PE_IMX_O18_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_TOP_IMX_O18,data,_r)
#define PE_IMX_O18_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_TOP_IMX_O18,data,_r)
#define PE_IMX_O18_Rd(_r)					PE_REG_SHDW_Rd32(gPE_TOP_IMX_O18,data,_r)
#define PE_IMX_O18_Wr(_r,_d1)				PE_REG_SHDW_Wr32(gPE_TOP_IMX_O18,data,_r,_d1)
#define PE_IMX_O18_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_TOP_IMX_O18,data,_r,_f1,_d1)
#define PE_IMX_O18_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_TOP_IMX_O18,data,_r,_f1,_d1)
#if 0
/* PE_IMX_O18 */
#define PE_IPP_O18_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_IPP_O18,data,_r)
#define PE_IPP_O18_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_IPP_O18,data,_r)
#define PE_IPP_O18_Rd(_r)					PE_REG_SHDW_Rd32(gPE_IPP_O18,data,_r)
#define PE_IPP_O18_Wr(_r,_d1)				PE_REG_SHDW_Wr32(gPE_IPP_O18,data,_r,_d1)
#define PE_IPP_O18_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_IPP_O18,data,_r,_f1,_d1)
#define PE_IPP_O18_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_IPP_O18,data,_r,_f1,_d1)
#endif




/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_ND_ND0_REG_O18_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_ND_ND0_REG_O18_T *data;
	} phys;
} PE_ND_ND0_REG_TYPE_O18_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_ND_DNR0_REG_O18_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_ND_DNR0_REG_O18_T *data;
	} phys;
} PE_ND_DNR0_REG_TYPE_O18_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_TOP_IMX_REG_O18_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_TOP_IMX_REG_O18_T *data;
	} phys;
} PE_TOP_IMX_REG_TYPE_O18_T;

#if 0
typedef struct {
	union {
		UINT32			*addr;
		PE_IPP_REG_O18_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_IPP_REG_O18_T *data;
	} phys;
} PE_IPP_REG_TYPE_O18_T;
#endif

typedef struct {
	union {
		UINT32			*addr;
		PE_ND_PSP_REG_O18_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_ND_PSP_REG_O18_T *data;
	} phys;
} PE_ND_PSP_REG_TYPE_O18_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_ND_REG_O18_H_ */

