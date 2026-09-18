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

/** @file pe_clc_hw_param_e60.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_CLC_HW_PARAM_E60_H_
#define	_PE_CLC_HW_PARAM_E60_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"
#include "pe_clc_l_init_e60.h"
#include "pe_clc_l_hd_default_e60.h"
#include "pe_clc_l_sd_50_default_e60.h"
#include "pe_clc_l_sd_60_default_e60.h"
#include "pe_clc_l_pc_default_e60.h"
#include "pe_clc_l_vr_360_default_e60.h"

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
 *	clc hw param reg type
 */
 typedef struct {
	PE_E60_ND0_CLC_CTRL_00_T								   clc_ctrl_00; //0xC900E260
	PE_E60_ND0_CLC_CTRL_01_T								   clc_ctrl_01; //0xC900E264
	PE_E60_ND0_CLC_CTRL_02_T								   clc_ctrl_02; //0xC900E268
	PE_E60_ND0_CLC_CTRL_03_T								   clc_ctrl_03; //0xC900E26C
	PE_E60_ND0_CLC_CTRL_04_T								   clc_ctrl_04; //0xC900E270
	PE_E60_ND0_CLC_CTRL_05_T								   clc_ctrl_05; //0xC900E274
	PE_E60_ND0_CLC_CTRL_06_T								   clc_ctrl_06; //0xC900E278
	PE_E60_ND0_CLC_CTRL_07_T                                   clc_ctrl_07;	//0xC900E36C
}PE_CLC_HW_PARAM_REG_E60_T;

/**
 *	clc hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_CLC_HW_PARAM_REG_E60_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_CLC_HW_PARAM_REG_E60_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_CLC_HW_PARAM_REG_E60_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_CLC_HW_PARAM_REG_E60_T *data;
	} reg_data;
} PE_CLC_HW_PARAM_DATA_E60_T;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CLC_HW_PARAM_E60_H_ */
