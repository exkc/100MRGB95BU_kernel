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

/** @file pe_ipc_hw_param_e60.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_IPC_HW_PARAM_E60_H_
#define	_PE_IPC_HW_PARAM_E60_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"


#include "pe_ipc_l_hd_default_e60.h"
#include "pe_ipc_l_sd_default_e60.h"
#include "pe_ipc_l_atv_default_e60.h"
#include "pe_ipc_l_dtv_sd_default_e60.h"
#include "pe_ipc_l_dtv_hd_default_e60.h"
#include "pe_ipc_l_vr_360_default_e60.h"
#include "pe_ipc_l_av_default_e60.h"

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
 *	ipc hw param reg type
 */
typedef struct {
	PE_E60_ND0_IPC_CTRL_00_T                                   ipc_ctrl_00;	//0xC900E200
	PE_E60_ND0_IPC_CTRL_01_T                                   ipc_ctrl_01;	//0xC900E204
	PE_E60_ND0_IPC_CTRL_02_T                                   ipc_ctrl_02;	//0xC900E208
	PE_E60_ND0_IPC_CTRL_03_T                                   ipc_ctrl_03;	//0xC900E20C
	PE_E60_ND0_IPC_CTRL_04_T                                   ipc_ctrl_04;	//0xC900E210
	PE_E60_ND0_IPC_CTRL_05_T                                   ipc_ctrl_05;	//0xC900E214
	PE_E60_ND0_IPC_CTRL_06_T                                   ipc_ctrl_06;	//0xC900E218
	PE_E60_ND0_IPC_CTRL_07_T                                   ipc_ctrl_07;	//0xC900E21C
	PE_E60_ND0_IPC_CTRL_08_T                                   ipc_ctrl_08;	//0xC900E220
	PE_E60_ND0_IPC_CTRL_09_T                                   ipc_ctrl_09;	//0xC900E224
	PE_E60_ND0_IPC_CTRL_10_T                                   ipc_ctrl_10;	//0xC900E228
	PE_E60_ND0_IPC_CTRL_11_T                                   ipc_ctrl_11;	//0xC900E22C
	PE_E60_ND0_IPC_CTRL_12_T                                   ipc_ctrl_12;	//0xC900E230
	PE_E60_ND0_IPC_CTRL_13_T                                   ipc_ctrl_13;	//0xC900E234
	PE_E60_ND0_IPC_CTRL_14_T                                   ipc_ctrl_14;	//0xC900E238
	PE_E60_ND0_IPC_CTRL_15_T                                   ipc_ctrl_15;	//0xC900E23C
	PE_E60_ND0_IPC_CTRL_16_T                                   ipc_ctrl_16;	//0xC900E240
	PE_E60_ND0_IPC_CTRL_17_T                                   ipc_ctrl_17;	//0xC900E244
	PE_E60_ND0_IPC_CTRL_18_T                                   ipc_ctrl_18;	//0xC900E248
	PE_E60_ND0_IPC_CTRL_19_T                                   ipc_ctrl_19;	//0xC900E24C
	PE_E60_ND0_IPC_CTRL_34_T                                   ipc_ctrl_34;	//0xC900E280
	PE_E60_ND0_IPC_CTRL_35_T                                   ipc_ctrl_35;	//0xC900E284
	PE_E60_ND0_IPC_CTRL_36_T                                   ipc_ctrl_36;	//0xC900E288
	PE_E60_ND0_IPC_CTRL_37_T                                   ipc_ctrl_37;	//0xC900E28C
	PE_E60_ND0_IPC_CTRL_38_T                                   ipc_ctrl_38;	//0xC900E290
	PE_E60_ND0_IPC_CTRL_39_T                                   ipc_ctrl_39;	//0xC900E294
	PE_E60_ND0_IPC_CTRL_40_T                                   ipc_ctrl_40;	//0xC900E298
	PE_E60_ND0_IPC_CTRL_41_T                                   ipc_ctrl_41;	//0xC900E29C
	PE_E60_ND0_IPC_CTRL_42_T                                   ipc_ctrl_42;	//0xC900E2A0
	PE_E60_ND0_IPC_CTRL_43_T                                   ipc_ctrl_43;	//0xC900E2A4
	PE_E60_ND0_IPC_CTRL_44_T                                   ipc_ctrl_44;	//0xC900E2A8
	PE_E60_ND0_IPC_CTRL_45_T                                   ipc_ctrl_45;	//0xC900E2AC
	PE_E60_ND0_IPC_CTRL_46_T                                   ipc_ctrl_46;	//0xC900E2B0
	PE_E60_ND0_IPC_CTRL_47_T                                   ipc_ctrl_47;	//0xC900E2B4
	PE_E60_ND0_IPC_CTRL_48_T                                   ipc_ctrl_48;	//0xC900E2B8
	PE_E60_ND0_IPC_CTRL_49_T                                   ipc_ctrl_49;	//0xC900E2BC
	PE_E60_ND0_IPC_CTRL_50_T                                   ipc_ctrl_50;	//0xC900E2C0
	PE_E60_ND0_IPC_CTRL_51_T                                   ipc_ctrl_51;	//0xC900E2C4
	PE_E60_ND0_IPC_CTRL_52_T                                   ipc_ctrl_52;	//0xC900E2C8
	PE_E60_ND0_IPC_CTRL_20_T                                   ipc_ctrl_20;	//0xC900E2F0
	PE_E60_ND0_IPC_CTRL_21_T                                   ipc_ctrl_21;	//0xC900E2F4
	PE_E60_ND0_IPC_CTRL_22_T                                   ipc_ctrl_22;	//0xC900E2F8
	PE_E60_ND0_IPC_CTRL_23_T                                   ipc_ctrl_23;	//0xC900E2FC
	PE_E60_ND0_IPC_CTRL_24_T                                   ipc_ctrl_24;	//0xC900E300
	PE_E60_ND0_IPC_CTRL_25_T                                   ipc_ctrl_25;	//0xC900E304
	PE_E60_ND0_IPC_CTRL_26_T                                   ipc_ctrl_26;	//0xC900E308
	PE_E60_ND0_IPC_CTRL_27_T                                   ipc_ctrl_27;	//0xC900E30C
	PE_E60_ND0_IPC_CTRL_28_T                                   ipc_ctrl_28;	//0xC900E310
	PE_E60_ND0_IPC_CTRL_29_T                                   ipc_ctrl_29;	//0xC900E314
	PE_E60_ND0_IPC_CTRL_30_T                                   ipc_ctrl_30;	//0xC900E318
	PE_E60_ND0_IPC_CTRL_31_T                                   ipc_ctrl_31;	//0xC900E31C
	PE_E60_ND0_IPC_CTRL_32_T                                   ipc_ctrl_32;	//0xC900E320
	PE_E60_ND0_IPC_CTRL_33_T                                   ipc_ctrl_33;	//0xC900E324
} PE_IPC_HW_PARAM_REG_E60_T;

/**
 *	ipc hw param data type
 */
 typedef struct {
	union {
		UINT32			*addr;
		PE_IPC_HW_PARAM_REG_E60_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_IPC_HW_PARAM_REG_E60_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_IPC_HW_PARAM_REG_E60_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_IPC_HW_PARAM_REG_E60_T *data;
	} reg_data;
} PE_IPC_HW_PARAM_DATA_E60_T;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_IPC_HW_PARAM_E60_H_ */

