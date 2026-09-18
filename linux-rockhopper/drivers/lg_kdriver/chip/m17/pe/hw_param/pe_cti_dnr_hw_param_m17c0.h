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

/** @file pe_cti_dnr_hw_param_m17c0.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_CTI_DNR_HW_PARAM_M17C0_H_
#define	_PE_CTI_DNR_HW_PARAM_M17C0_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"
#include "pe_cti_y_l_hd_default_m17c0.h"
#include "pe_cti_y_l_sd_default_m17c0.h"
#include "pe_cti_y_l_vr_360_default_m17c0.h"
#include "pe_cti_y_l_atv_default_m17c0.h"
#include "pe_cti_y_l_dtv_480i_default_m17c0.h"


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
	PE_M17C0_CTI_CTRL_0_T				cti_ctrl_0; 			//0xc900458cL
	PE_M17C0_CTI_CTRL_1_T				cti_ctrl_1; 			//0xc9004590L
	PE_M17C0_REG_CTI_CTRL_2_T			reg_cti_ctrl_2;			//0xc90047a0L
	PE_M17C0_REG_CTI_CTRL_3_T			reg_cti_ctrl_3;			//0xc90047a4L
	PE_M17C0_SHP_CTI_CTRL_00_T			shp_cti_ctrl_00;		//0xc900d540L
	PE_M17C0_SHP_CTI_CTRL_01_T			shp_cti_ctrl_01;		//0xc900d544L
	PE_M17C0_SHP_CTI_CTRL_02_T			shp_cti_ctrl_02;		//0xc900d548L
} PE_CTI_HW_PARAM_REG_M17C0_T;

/**
 *	cti_dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_CTI_HW_PARAM_REG_M17C0_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_CTI_HW_PARAM_REG_M17C0_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_CTI_HW_PARAM_REG_M17C0_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_CTI_HW_PARAM_REG_M17C0_T *data;
	} reg_data;
} PE_CTI_HW_PARAM_DATA_M17C0_T;


/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CTI_DNR_HW_PARAM_M17C0_H_ */
