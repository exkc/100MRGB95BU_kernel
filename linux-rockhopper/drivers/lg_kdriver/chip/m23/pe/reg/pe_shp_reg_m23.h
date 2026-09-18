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

/** @file pe_shp_reg_m23.h
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
#ifndef _PE_SHP_REG_M23_H_
#define _PE_SHP_REG_M23_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_shp_reg_m23a0.h"
//#include "pe_osd_reg_m23a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/* PE_SHP_M23 */
#define PE_SHP_M23_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r)
#define PE_SHP_M23_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_SHP_M23,data,_r)
#define PE_SHP_M23_Rd(_r)				PE_REG_SHDW_Rd32(gPE_SHP_M23,data,_r)
#define PE_SHP_M23_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_SHP_M23,data,_r,_d1)
#define PE_SHP_M23_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_SHP_M23,data,_r,_f1,_d1)
#define PE_SHP_M23_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_SHP_M23,data,_r,_f1,_d1)

#define PE_SHP_M23_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Wr01(gPE_SHP_M23,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_SHP_M23,data,_r);}
#define PE_SHP_M23_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Wr02(gPE_SHP_M23,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_SHP_M23,data,_r);}
#define PE_SHP_M23_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Wr03(gPE_SHP_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_SHP_M23,data,_r);}
#define PE_SHP_M23_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Wr04(gPE_SHP_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_SHP_M23,data,_r);}
#define PE_SHP_M23_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Wr05(gPE_SHP_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_SHP_M23,data,_r);}
#define PE_SHP_M23_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Wr06(gPE_SHP_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_SHP_M23,data,_r);}
#define PE_SHP_M23_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Rd01(gPE_SHP_M23,data,_r,_f1,_d1);}
#define PE_SHP_M23_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Rd02(gPE_SHP_M23,data,_r,_f1,_d1,_f2,_d2);}
#define PE_SHP_M23_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Rd03(gPE_SHP_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_SHP_M23_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Rd04(gPE_SHP_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_SHP_M23_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Rd05(gPE_SHP_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}
#define PE_SHP_M23_QRd06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_SHP_M23,data,_r);\
		PE_REG_SHDW_Rd06(gPE_SHP_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);}

/* gPE_VSD_DTM_M23 */
#define PE_VSD_DTM_M23_RdFL(_r)				PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r)
#define PE_VSD_DTM_M23_WrFL(_r)				PE_REG_PHYS_WrFL(gPE_VSD_DTM_M23,data,_r)
#define PE_VSD_DTM_M23_Rd(_r)				PE_REG_SHDW_Rd32(gPE_VSD_DTM_M23,data,_r)
#define PE_VSD_DTM_M23_Wr(_r,_d1)			PE_REG_SHDW_Wr32(gPE_VSD_DTM_M23,data,_r,_d1)
#define PE_VSD_DTM_M23_Rd01(_r,_f1,_d1)		PE_REG_SHDW_Rd01(gPE_VSD_DTM_M23,data,_r,_f1,_d1)
#define PE_VSD_DTM_M23_Wr01(_r,_f1,_d1)		PE_REG_SHDW_Wr01(gPE_VSD_DTM_M23,data,_r,_f1,_d1)

#define PE_VSD_DTM_M23_QWr01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Wr01(gPE_VSD_DTM_M23,data,_r,_f1,_d1);\
		PE_REG_PHYS_WrFL(gPE_VSD_DTM_M23,data,_r);}
#define PE_VSD_DTM_M23_QWr02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Wr02(gPE_VSD_DTM_M23,data,_r,_f1,_d1,_f2,_d2);\
		PE_REG_PHYS_WrFL(gPE_VSD_DTM_M23,data,_r);}
#define PE_VSD_DTM_M23_QWr03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Wr03(gPE_VSD_DTM_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);\
		PE_REG_PHYS_WrFL(gPE_VSD_DTM_M23,data,_r);}
#define PE_VSD_DTM_M23_QWr04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Wr04(gPE_VSD_DTM_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);\
		PE_REG_PHYS_WrFL(gPE_VSD_DTM_M23,data,_r);}
#define PE_VSD_DTM_M23_QWr05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Wr05(gPE_VSD_DTM_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);\
		PE_REG_PHYS_WrFL(gPE_VSD_DTM_M23,data,_r);}
#define PE_VSD_DTM_M23_QWr06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Wr06(gPE_VSD_DTM_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);\
		PE_REG_PHYS_WrFL(gPE_VSD_DTM_M23,data,_r);}
#define PE_VSD_DTM_M23_QRd01(_r,_f1,_d1)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Rd01(gPE_VSD_DTM_M23,data,_r,_f1,_d1);}
#define PE_VSD_DTM_M23_QRd02(_r,_f1,_d1,_f2,_d2)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Rd02(gPE_VSD_DTM_M23,data,_r,_f1,_d1,_f2,_d2);}
#define PE_VSD_DTM_M23_QRd03(_r,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Rd03(gPE_VSD_DTM_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3);}
#define PE_VSD_DTM_M23_QRd04(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Rd04(gPE_VSD_DTM_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4);}
#define PE_VSD_DTM_M23_QRd05(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Rd05(gPE_VSD_DTM_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5);}
#define PE_VSD_DTM_M23_QRd06(_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_REG_PHYS_RdFL(gPE_VSD_DTM_M23,data,_r);\
		PE_REG_SHDW_Rd06(gPE_VSD_DTM_M23,data,_r,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6);}


/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/

typedef struct {
	union {
		UINT32			*addr;
		PE_SHP_REG_M23_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_SHP_REG_M23_T *data;
	} phys;
} PE_SHP_REG_TYPE_M23_T;


typedef struct {
	union {
		UINT32			*addr;
		PE_VSD_DTM_REG_M23_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_VSD_DTM_REG_M23_T *data;
	} phys;
} PE_VSD_DTM_REG_TYPE_M23_T;


/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_SHP_REG_M16_H_ */

