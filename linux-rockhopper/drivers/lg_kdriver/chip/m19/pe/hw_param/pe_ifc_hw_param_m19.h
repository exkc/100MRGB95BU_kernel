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

/** @file pe_ifc_hw_param_m19.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_IFC_HW_PARAM_M19_H_
#define	_PE_IFC_HW_PARAM_M19_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"
#include "pe_ifc_l_init_m19.h"
#include "pe_ifc_l_pc_default_m19.h"
#include "pe_ifc_l_atv_ntsc_default_m19.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/
/**
 *	ifc hw param reg type
 */
typedef struct {
	PE_M19_IFC_CTRL_0_T                             ifc_ctrl_0;	//0x0114
	PE_M19_IFC_CTRL_1_T                             ifc_ctrl_1;	//0x0118
	PE_M19_IFC_CTRL_2_T                             ifc_ctrl_2;	//0x011C
	PE_M19_IFC_CTRL_3_T                             ifc_ctrl_3;	//0x0120
	PE_M19_IFC_CTRL_4_T                             ifc_ctrl_4;	//0x0124
	PE_M19_IFC_CTRL_5_T                             ifc_ctrl_5;	//0x0128
	PE_M19_IFC_CTRL_8_T                             ifc_ctrl_8;	//0x0134
	PE_M19_IFC_CTRL_12_T                            ifc_ctrl_12;	//0x0144
	PE_M19_IFC_CTRL_15_T                            ifc_ctrl_15;	//0x0150
	PE_M19_IFC_CTRL_16_T                            ifc_ctrl_16;	//0x0154
	PE_M19_IFC_CTRL_17_T                            ifc_ctrl_17;	//0x0158
	PE_M19_IFC_CTRL_19_T                            ifc_ctrl_19;	//0x0160
	PE_M19_IFC_CTRL_21_T                            ifc_ctrl_21;	//0x0168
}PE_IFC_HW_PARAM_REG_M19_T;

/**
 *	ifc hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_IFC_HW_PARAM_REG_M19_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_IFC_HW_PARAM_REG_M19_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_IFC_HW_PARAM_REG_M19_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_IFC_HW_PARAM_REG_M19_T *data;
	} reg_data;
} PE_IFC_HW_PARAM_DATA_M19_T;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_IFC_HW_PARAM_M19_H_ */
