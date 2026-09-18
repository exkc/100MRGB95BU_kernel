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

/** @file pe_ifc_hw_param_o24.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_IFC_HW_PARAM_O24_H_
#define	_PE_IFC_HW_PARAM_O24_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"

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
	PE_O24_DNR_IFC_CTRL_0_T				ifc_ctrl_0; 			 //0xc8007214L
	PE_O24_DNR_IFC_CTRL_1_T				ifc_ctrl_1; 			 //0xc8007218L
	PE_O24_DNR_IFC_CTRL_2_T				ifc_ctrl_2; 			 //0xc800721cL
	PE_O24_DNR_IFC_CTRL_3_T				ifc_ctrl_3; 			 //0xc8007220L
	PE_O24_DNR_IFC_CTRL_4_T				ifc_ctrl_4; 			 //0xc8007224L
	PE_O24_DNR_IFC_CTRL_5_T				ifc_ctrl_5; 			 //0xc8007228L
	PE_O24_DNR_IFC_CTRL_8_T				ifc_ctrl_8; 			 //0xc8007234L
	PE_O24_DNR_IFC_CTRL_12_T 			ifc_ctrl_12;			 //0xc8007244L
	PE_O24_DNR_IFC_CTRL_15_T 			ifc_ctrl_15;			 //0xc8007250L
	PE_O24_DNR_IFC_CTRL_16_T 			ifc_ctrl_16;			 //0xc8007254L
	PE_O24_DNR_IFC_CTRL_17_T 			ifc_ctrl_17;			 //0xc8007258L
	PE_O24_DNR_IFC_CTRL_19_T 			ifc_ctrl_19;			 //0xc8007260L
	PE_O24_DNR_IFC_CTRL_21_T 			ifc_ctrl_21;			 //0xc8007268L
}PE_IFC_HW_PARAM_REG_O24_T;

/**
 *	ifc hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_IFC_HW_PARAM_REG_O24_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_IFC_HW_PARAM_REG_O24_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_IFC_HW_PARAM_REG_O24_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_IFC_HW_PARAM_REG_O24_T *data;
	} reg_data;
} PE_IFC_HW_PARAM_DATA_O24_T;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_IFC_HW_PARAM_O24_H_ */
