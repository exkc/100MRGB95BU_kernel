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

/** @file pe_cvi_reg_o24.h
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
#ifndef _PE_CVI_REG_O24_H_
#define _PE_CVI_REG_O24_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_cvi_reg_o24a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#if 0
/* PE_HDMI_A_O24 */
#define PE_HDMI_A_O24_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_HDMI_A_O24,data,_r)
#define PE_HDMI_A_O24_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_HDMI_A_O24,data,_r)
#define PE_HDMI_A_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_HDMI_A_O24,data,_r)
#define PE_HDMI_A_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_HDMI_A_O24,data,_r,_d1)
#define PE_HDMI_A_O24_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_HDMI_A_O24,data,_r,_f1,_d1)
#define PE_HDMI_A_O24_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_HDMI_A_O24,data,_r,_f1,_d1)

#define PE_HDMI_A_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_A_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_HDMI_A_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_HDMI_A_O24,data,_r);}
#define PE_HDMI_A_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_A_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_HDMI_A_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_HDMI_A_O24,data,_r);}
#define PE_HDMI_A_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_A_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_HDMI_A_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_HDMI_A_O24,data,_r);}
#define PE_HDMI_A_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_A_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_HDMI_A_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_HDMI_A_O24,data,_r);}
#define PE_HDMI_A_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_A_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_HDMI_A_O24,data,_r,_f1,_d1);}
#define PE_HDMI_A_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_A_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_HDMI_A_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_HDMI_A_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_A_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_HDMI_A_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_HDMI_A_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_A_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_HDMI_A_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}

/* PE_HDMI_B_O24 */
#define PE_HDMI_B_O24_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_HDMI_B_O24,data,_r)
#define PE_HDMI_B_O24_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_HDMI_B_O24,data,_r)
#define PE_HDMI_B_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_HDMI_B_O24,data,_r)
#define PE_HDMI_B_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_HDMI_B_O24,data,_r,_d1)
#define PE_HDMI_B_O24_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_HDMI_B_O24,data,_r,_f1,_d1)
#define PE_HDMI_B_O24_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_HDMI_B_O24,data,_r,_f1,_d1)

#define PE_HDMI_B_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_B_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_HDMI_B_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_HDMI_B_O24,data,_r);}
#define PE_HDMI_B_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_B_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_HDMI_B_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_HDMI_B_O24,data,_r);}
#define PE_HDMI_B_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_B_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_HDMI_B_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_HDMI_B_O24,data,_r);}
#define PE_HDMI_B_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_B_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_HDMI_B_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_HDMI_B_O24,data,_r);}
#define PE_HDMI_B_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_B_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_HDMI_B_O24,data,_r,_f1,_d1);}
#define PE_HDMI_B_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_B_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_HDMI_B_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_HDMI_B_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_B_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_HDMI_B_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_HDMI_B_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_B_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_HDMI_B_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}

/* PE_HDMI_C_O24 */
#define PE_HDMI_C_O24_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_HDMI_C_O24,data,_r)
#define PE_HDMI_C_O24_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_HDMI_C_O24,data,_r)
#define PE_HDMI_C_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_HDMI_C_O24,data,_r)
#define PE_HDMI_C_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_HDMI_C_O24,data,_r,_d1)
#define PE_HDMI_C_O24_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_HDMI_C_O24,data,_r,_f1,_d1)
#define PE_HDMI_C_O24_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_HDMI_C_O24,data,_r,_f1,_d1)

#define PE_HDMI_C_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_C_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_HDMI_C_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_HDMI_C_O24,data,_r);}
#define PE_HDMI_C_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_C_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_HDMI_C_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_HDMI_C_O24,data,_r);}
#define PE_HDMI_C_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_C_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_HDMI_C_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_HDMI_C_O24,data,_r);}
#define PE_HDMI_C_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_C_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_HDMI_C_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_HDMI_C_O24,data,_r);}
#define PE_HDMI_C_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_C_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_HDMI_C_O24,data,_r,_f1,_d1);}
#define PE_HDMI_C_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_C_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_HDMI_C_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_HDMI_C_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_C_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_HDMI_C_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_HDMI_C_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_C_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_HDMI_C_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}


/* PE_HDMI_D_O24 */
#define PE_HDMI_D_O24_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_HDMI_D_O24,data,_r)
#define PE_HDMI_D_O24_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_HDMI_D_O24,data,_r)
#define PE_HDMI_D_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_HDMI_D_O24,data,_r)
#define PE_HDMI_D_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_HDMI_D_O24,data,_r,_d1)
#define PE_HDMI_D_O24_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_HDMI_D_O24,data,_r,_f1,_d1)
#define PE_HDMI_D_O24_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_HDMI_D_O24,data,_r,_f1,_d1)

#define PE_HDMI_D_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_D_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_HDMI_D_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_HDMI_D_O24,data,_r);}
#define PE_HDMI_D_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_D_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_HDMI_D_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_HDMI_D_O24,data,_r);}
#define PE_HDMI_D_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_D_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_HDMI_D_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_HDMI_D_O24,data,_r);}
#define PE_HDMI_D_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_D_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_HDMI_D_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_HDMI_D_O24,data,_r);}
#define PE_HDMI_D_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_D_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_HDMI_D_O24,data,_r,_f1,_d1);}
#define PE_HDMI_D_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_D_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_HDMI_D_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_HDMI_D_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_D_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_HDMI_D_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_HDMI_D_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_HDMI_D_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_HDMI_D_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#endif

/* PE_CVI_A_O24 */
#define PE_CVI_A_O24_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_CVI_A_O24,data,_r)
#define PE_CVI_A_O24_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_CVI_A_O24,data,_r)
#define PE_CVI_A_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_CVI_A_O24,data,_r)
#define PE_CVI_A_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_CVI_A_O24,data,_r,_d1)
#define PE_CVI_A_O24_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_CVI_A_O24,data,_r,_f1,_d1)
#define PE_CVI_A_O24_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_CVI_A_O24,data,_r,_f1,_d1)

#define PE_CVI_A_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_A_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_CVI_A_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_CVI_A_O24,data,_r);}
#define PE_CVI_A_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_A_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_CVI_A_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_CVI_A_O24,data,_r);}
#define PE_CVI_A_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_A_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_CVI_A_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_CVI_A_O24,data,_r);}
#define PE_CVI_A_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_A_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_CVI_A_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_CVI_A_O24,data,_r);}
#define PE_CVI_A_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_A_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_CVI_A_O24,data,_r,_f1,_d1);}
#define PE_CVI_A_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_A_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_CVI_A_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_CVI_A_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_A_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_CVI_A_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_CVI_A_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_A_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_CVI_A_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}

/* PE_CVI_B_O24 */
#define PE_CVI_B_O24_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_CVI_B_O24,data,_r)
#define PE_CVI_B_O24_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_CVI_B_O24,data,_r)
#define PE_CVI_B_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_CVI_B_O24,data,_r)
#define PE_CVI_B_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_CVI_B_O24,data,_r,_d1)
#define PE_CVI_B_O24_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_CVI_B_O24,data,_r,_f1,_d1)
#define PE_CVI_B_O24_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_CVI_B_O24,data,_r,_f1,_d1)

#define PE_CVI_B_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_B_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_CVI_B_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_CVI_B_O24,data,_r);}
#define PE_CVI_B_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_B_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_CVI_B_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_CVI_B_O24,data,_r);}
#define PE_CVI_B_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_B_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_CVI_B_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_CVI_B_O24,data,_r);}
#define PE_CVI_B_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_B_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_CVI_B_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_CVI_B_O24,data,_r);}
#define PE_CVI_B_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_B_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_CVI_B_O24,data,_r,_f1,_d1);}
#define PE_CVI_B_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_B_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_CVI_B_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_CVI_B_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_B_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_CVI_B_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_CVI_B_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_B_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_CVI_B_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}

/* PE_CVI_C_O24 */
#define PE_CVI_C_O24_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_CVI_C_O24,data,_r)
#define PE_CVI_C_O24_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_CVI_C_O24,data,_r)
#define PE_CVI_C_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_CVI_C_O24,data,_r)
#define PE_CVI_C_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_CVI_C_O24,data,_r,_d1)
#define PE_CVI_C_O24_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_CVI_C_O24,data,_r,_f1,_d1)
#define PE_CVI_C_O24_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_CVI_C_O24,data,_r,_f1,_d1)

#define PE_CVI_C_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_C_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_CVI_C_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_CVI_C_O24,data,_r);}
#define PE_CVI_C_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_C_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_CVI_C_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_CVI_C_O24,data,_r);}
#define PE_CVI_C_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_C_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_CVI_C_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_CVI_C_O24,data,_r);}
#define PE_CVI_C_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_C_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_CVI_C_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_CVI_C_O24,data,_r);}
#define PE_CVI_C_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_C_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_CVI_C_O24,data,_r,_f1,_d1);}
#define PE_CVI_C_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_C_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_CVI_C_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_CVI_C_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_C_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_CVI_C_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_CVI_C_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_C_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_CVI_C_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}

/* PE_CVI_D_O24 */
#define PE_CVI_D_O24_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_CVI_D_O24,data,_r)
#define PE_CVI_D_O24_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_CVI_D_O24,data,_r)
#define PE_CVI_D_O24_Rd(_r)				PE_REG_SHDW_Rd32(gPE_CVI_D_O24,data,_r)
#define PE_CVI_D_O24_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_CVI_D_O24,data,_r,_d1)
#define PE_CVI_D_O24_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_CVI_D_O24,data,_r,_f1,_d1)
#define PE_CVI_D_O24_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_CVI_D_O24,data,_r,_f1,_d1)

#define PE_CVI_D_O24_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_D_O24,data,_r);\
		PE_REG_SHDW_Wr01(gPE_CVI_D_O24,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_CVI_D_O24,data,_r);}
#define PE_CVI_D_O24_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_D_O24,data,_r);\
		PE_REG_SHDW_Wr02(gPE_CVI_D_O24,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_CVI_D_O24,data,_r);}
#define PE_CVI_D_O24_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_D_O24,data,_r);\
		PE_REG_SHDW_Wr03(gPE_CVI_D_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_CVI_D_O24,data,_r);}
#define PE_CVI_D_O24_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_D_O24,data,_r);\
		PE_REG_SHDW_Wr04(gPE_CVI_D_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_CVI_D_O24,data,_r);}
#define PE_CVI_D_O24_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_D_O24,data,_r);\
		PE_REG_SHDW_Rd01(gPE_CVI_D_O24,data,_r,_f1,_d1);}
#define PE_CVI_D_O24_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_D_O24,data,_r);\
		PE_REG_SHDW_Rd02(gPE_CVI_D_O24,data,_r,_f1,_d1,_f2,_d2);}
#define PE_CVI_D_O24_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_D_O24,data,_r);\
		PE_REG_SHDW_Rd03(gPE_CVI_D_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_CVI_D_O24_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_CVI_D_O24,data,_r);\
		PE_REG_SHDW_Rd04(gPE_CVI_D_O24,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
#if 0
typedef struct {
	union {
		UINT32			*addr;
		PE_HDMI_REG_O24_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_HDMI_REG_O24_T *data;
	} phys;
} PE_HDMI_REG_TYPE_O24_T;
#endif
typedef struct {
	union {
		UINT32			*addr;
		PE_CVI_REG_O24_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_CVI_REG_O24_T *data;
	} phys;
} PE_CVI_REG_TYPE_O24_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_CVI_REG_O24_H_ */

