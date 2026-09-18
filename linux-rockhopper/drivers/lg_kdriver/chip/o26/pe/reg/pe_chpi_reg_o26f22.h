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

/** @file pe_chpi_reg_o26f22.h
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
#ifndef _PE_CHPI_REG_O26F22_H_
#define _PE_CHPI_REG_O26F22_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_chpi_reg_o26f22a0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
/* PE_CHPI_APB0_O26F22 */
#define PE_CHPI_APB0_O26F22_RdFL(_r)			\
{rmb();gPE_CHPI_APB0_O26F22.shdw.data->_r=PE_SWAP32(gPE_CHPI_APB0_O26F22.phys.data->_r);rmb();}

#define PE_CHPI_APB0_O26F22_WrFL(_r)			\
{wmb();gPE_CHPI_APB0_O26F22.phys.data->_r=PE_SWAP32(gPE_CHPI_APB0_O26F22.shdw.data->_r);\
gPE_CHPI_APB1_O26F22.phys.data->_r=PE_SWAP32(gPE_CHPI_APB0_O26F22.shdw.data->_r);wmb();}

#define PE_CHPI_APB0_O26F22_Rd(_r)			(gPE_CHPI_APB0_O26F22.shdw.data->_r)
#define PE_CHPI_APB0_O26F22_Wr(_r,_d1)		{gPE_CHPI_APB0_O26F22.shdw.data->_r = (_d1);}

#define PE_CHPI_APB0_O26F22_QRd(_r,_d1)	\
{PE_CHPI_APB0_O26F22_RdFL(_r);(_d1)=PE_CHPI_APB0_O26F22_Rd(_r);}
#define PE_CHPI_APB0_O26F22_QWr(_r,_d1)	\
{PE_CHPI_APB0_O26F22_Wr(_r,_d1);PE_CHPI_APB0_O26F22_WrFL(_r);}

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_CHPI_REG_O26F22_T *data;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_CHPI_REG_O26F22_T *data;
	} phys;
} PE_CHPI_REG_TYPE_O26F22_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/
//extern PE_CHPI_REG_TYPE_O26F22_T gPE_CHPI_APB0_O26F22;
//extern PE_CHPI_REG_TYPE_O26F22_T gPE_CHPI_APB1_O26F22;

#endif	 /* _PE_CHPI_REG_O26F22_H_ */
