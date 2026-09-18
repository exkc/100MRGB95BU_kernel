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

/** @file pe_cti_dnr_hw_param_o20.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_CTI_DNR_HW_PARAM_O20_H_
#define	_PE_CTI_DNR_HW_PARAM_O20_H_

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
 *	cti_dnr hw param reg type
 */
 
typedef struct {
#ifdef PE_HW_O20_BRINGUP
	PE_O20_REG_CTI_CTRL_0_T				reg_cti_ctrl_0; //0x358C
	PE_O20_REG_CTI_CTRL_1_T				reg_cti_ctrl_1; //0x3590
	PE_O20_REG_CTI_CTRL_2_T             reg_cti_ctrl_2;	//0x03BC
	PE_O20_REG_CTI_CTRL_3_T             reg_cti_ctrl_3;	//0x03C0
	PE_O20_REG_CTI_CTRL_0_T				reg_dnr1_cti_ctrl_0; //0x458C
	PE_O20_REG_CTI_CTRL_1_T				reg_dnr1_cti_ctrl_1; //0x4590
	PE_O20_REG_CTI_CTRL_2_T             reg_dnr1_cti_ctrl_2;	//0x43BC
	PE_O20_REG_CTI_CTRL_3_T             reg_dnr1_cti_ctrl_3;	//0x43C0
	PE_O20_SHP_CTI_CTRL_00_T            shp_cti_ctrl_00;	//0x0550
	PE_O20_SHP_CTI_CTRL_01_T            shp_cti_ctrl_01;	//0x0554
	PE_O20_SHP_CTI_CTRL_02_T            shp_cti_ctrl_02;	//0x0558
#endif
}PE_CTI_HW_PARAM_REG_O20_T;

/**
 *	cti_dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_CTI_HW_PARAM_REG_O20_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_CTI_HW_PARAM_REG_O20_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_CTI_HW_PARAM_REG_O20_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_CTI_HW_PARAM_REG_O20_T *data;
	} reg_data;
} PE_CTI_HW_PARAM_DATA_O20_T;


/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CTI_DNR_HW_PARAM_O20_H_ */
