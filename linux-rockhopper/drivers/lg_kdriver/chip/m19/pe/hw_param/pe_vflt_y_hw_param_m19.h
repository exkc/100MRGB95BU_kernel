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

/** @file pe_vfilt_y_hw_param_m19.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_VFILT_Y_HW_PARAM_M16p_H_
#define	_PE_VFILT_Y_HW_PARAM_M16p_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"
#include "pe_vflt_y_l_sd_default_m19.h"
#include "pe_vflt_y_l_hd_i_default_m19.h"
#include "pe_vflt_y_l_hd_p_default_m19.h"
#include "pe_vflt_y_l_ud_default_m19.h"
#include "pe_vflt_y_l_ud_else_default_m19.h"
#include "pe_vflt_y_l_ud_hdmi_420_default_m19.h"
#include "pe_vflt_y_l_hd_i_dtv_default_m19.h"
#include "pe_vflt_y_l_vr_360_default_m19.h"
#include "pe_vflt_y_l_sd_dtv_default_m19.h"
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
 *	vfy hw param reg type
 */
 typedef struct {
	PE_M19_VFILTER_CTRL_00_T			vfilter_ctrl_00; 	//0xc8007180L
	PE_M19_VFILTER_CTRL_01_T			vfilter_ctrl_01; 	//0xc8007184L
	PE_M19_VFILTER_CTRL_02_T			vfilter_ctrl_02; 	//0xc8007188L
	PE_M19_VFILTER_CTRL_03_T            vfilter_ctrl_03;	//0x0238
	PE_M19_VFILTER_CTRL_04_T            vfilter_ctrl_04;	//0x023C
	PE_M19_VFILTER_CTRL_05_T            vfilter_ctrl_05;	//0x0240
	PE_M19_VFILTER_CTRL_06_T            vfilter_ctrl_06;	//0x0244
	PE_M19_VFILTER_CTRL_07_T            vfilter_ctrl_07;	//0x0248
	PE_M19_VFILTER_CTRL_08_T            vfilter_ctrl_08;	//0x024C
	PE_M19_VFILTER_CTRL_09_T            vfilter_ctrl_09;	//0x0250
	PE_M19_VFILTER_CTRL_10_T            vfilter_ctrl_10;	//0x0254
	PE_M19_VFILTER_CTRL_11_T            vfilter_ctrl_11;	//0x0258
	PE_M19_VFILTER_CTRL_12_T            vfilter_ctrl_12;	//0x025C
	PE_M19_VFILTER_CTRL_13_T            vfilter_ctrl_13;	//0x0260
}PE_VFY_HW_PARAM_REG_M19_T;
/**
 *	vfy hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_VFY_HW_PARAM_REG_M19_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_VFY_HW_PARAM_REG_M19_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_VFY_HW_PARAM_REG_M19_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_VFY_HW_PARAM_REG_M19_T *data;
	} reg_data;
} PE_VFY_HW_PARAM_DATA_M19_T;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_VFILT_Y_HW_PARAM_M16p_H_ */
