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

/** @file pe_hdr_reg_m23.h
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
#ifndef _PE_HDR_REG_M23_H_
#define _PE_HDR_REG_M23_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_hdr_ddr_m23.h"
#include "pe_hdr_reg_m23a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
/* PE_H10_M23 */
#define PE_H10_M23_RdFL(_r)			PE_REG_PHYS_RdFL(gPE_H10_M23,data,_r)
#define PE_H10_M23_WrFL(_r)			PE_REG_PHYS_WrFL(gPE_H10_M23,data,_r)
#define PE_H10_M23_Rd(_r)			PE_REG_SHDW_Rd32(gPE_H10_M23,data,_r)
#define PE_H10_M23_Wr(_r,_d1)		PE_REG_SHDW_Wr32(gPE_H10_M23,data,_r,_d1)
#define PE_H10_M23_Rd01(_r,_f1,_d1)	PE_REG_SHDW_Rd01(gPE_H10_M23,data,_r,_f1,_d1)
#define PE_H10_M23_Wr01(_r,_f1,_d1)	PE_REG_SHDW_Wr01(gPE_H10_M23,data,_r,_f1,_d1)

#define PE_H10_M23_QWr(_r,_d1)	\
	{	PE_REG_SHDW_Wr32(gPE_H10_M23,data,_r,_d1);\
		PE_REG_PHYS_WrFL(gPE_H10_M23,data,_r);}
#define PE_H10_M23_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_M23,data,_r);\
		PE_REG_SHDW_Wr01(gPE_H10_M23,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_H10_M23,data,_r);}
#define PE_H10_M23_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_M23,data,_r);\
		PE_REG_SHDW_Wr02(gPE_H10_M23,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_H10_M23,data,_r);}
#define PE_H10_M23_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_M23,data,_r);\
		PE_REG_SHDW_Wr03(gPE_H10_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_H10_M23,data,_r);}
#define PE_H10_M23_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_M23,data,_r);\
		PE_REG_SHDW_Rd01(gPE_H10_M23,data,_r,_f1,_d1);}
#define PE_H10_M23_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_M23,data,_r);\
		PE_REG_SHDW_Rd02(gPE_H10_M23,data,_r,_f1,_d1,_f2,_d2);}
#define PE_H10_M23_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_H10_M23,data,_r);\
		PE_REG_SHDW_Rd03(gPE_H10_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_M23_REG_H10_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_M23_REG_H10_T *data;
	} phys;
} PE_HDR_REG_M23_H10_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/
extern PE_HDR_REG_M23_H10_T gPE_H10_M23;
extern volatile PE_HDR_DDR_M23_T *gPE_HDR_DDR_M23;

#endif	 /* _PE_HDR_REG_M23_H_ */

