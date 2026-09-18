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

/** @file pe_clc_hw_param_o24.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_CLC_HW_PARAM_O24_H_
#define	_PE_CLC_HW_PARAM_O24_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"
#include "pe_clc_l_init_o24.h"
#include "pe_clc_l_hd_default_o24.h"
#include "pe_clc_l_sd_50_default_o24.h"
#include "pe_clc_l_sd_60_default_o24.h"
#include "pe_clc_l_pc_default_o24.h"
#include "pe_clc_l_vr_360_default_o24.h"
#include "pe_clc1_l_init_o24.h"
#include "pe_clc1_l_hd_default_o24.h"
#include "pe_clc1_l_sd_50_default_o24.h"
#include "pe_clc1_l_sd_60_default_o24.h"
#include "pe_clc1_l_pc_default_o24.h"
#include "pe_clc1_l_vr_360_default_o24.h"

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
	PE_O24_ND_CLC_CTRL_00_T								   clc_ctrl_00; //0xCC800260
	PE_O24_ND_CLC_CTRL_01_T								   clc_ctrl_01; //0xCC800264
	PE_O24_ND_CLC_CTRL_02_T								   clc_ctrl_02; //0xCC800268
	PE_O24_ND_CLC_CTRL_03_T								   clc_ctrl_03; //0xCC80026C
	PE_O24_ND_CLC_CTRL_04_T								   clc_ctrl_04; //0xCC800270
	PE_O24_ND_CLC_CTRL_05_T								   clc_ctrl_05; //0xCC800274
	PE_O24_ND_CLC_CTRL_06_T								   clc_ctrl_06; //0xCC800278
	PE_O24_ND_CLC_CTRL_07_T                                clc_ctrl_07;	//0xCC80036C
}PE_CLC_HW_PARAM_REG_O24_T;

/**
 *	clc hw ND_param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_CLC_HW_PARAM_REG_O24_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_CLC_HW_PARAM_REG_O24_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_CLC_HW_PARAM_REG_O24_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_CLC_HW_PARAM_REG_O24_T *data;
	} reg_data;
} PE_CLC_HW_PARAM_DATA_O24_T;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CLC_HW_PARAM_O24_H_ */
