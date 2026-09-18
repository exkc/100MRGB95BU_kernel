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

/** @file pe_ipc_hw_param_m23.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_IPC_HW_PARAM_M23_H_
#define	_PE_IPC_HW_PARAM_M23_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"


#include "pe_ipc_l_hd_default_m23.h"
#include "pe_ipc_l_sd_default_m23.h"
#include "pe_ipc_l_atv_default_m23.h"
#include "pe_ipc_l_dtv_sd_default_m23.h"
#include "pe_ipc_l_dtv_hd_default_m23.h"
#include "pe_ipc_l_vr_360_default_m23.h"
#include "pe_ipc_l_av_default_m23.h"

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
	PE_M23_IPC_CTRL_00_T                                   ipc_ctrl_00;	//0xCC800200
	PE_M23_IPC_CTRL_01_T                                   ipc_ctrl_01;	//0xCC800204
	PE_M23_IPC_CTRL_02_T                                   ipc_ctrl_02;	//0xCC800208
	PE_M23_IPC_CTRL_03_T                                   ipc_ctrl_03;	//0xCC80020C
	PE_M23_IPC_CTRL_04_T                                   ipc_ctrl_04;	//0xCC800210
	PE_M23_IPC_CTRL_05_T                                   ipc_ctrl_05;	//0xCC800214
	PE_M23_IPC_CTRL_06_T                                   ipc_ctrl_06;	//0xCC800218
	PE_M23_IPC_CTRL_07_T                                   ipc_ctrl_07;	//0xCC80021C
	PE_M23_IPC_CTRL_08_T                                   ipc_ctrl_08;	//0xCC800220
	PE_M23_IPC_CTRL_09_T                                   ipc_ctrl_09;	//0xCC800224
	PE_M23_IPC_CTRL_10_T                                   ipc_ctrl_10;	//0xCC800228
	PE_M23_IPC_CTRL_11_T                                   ipc_ctrl_11;	//0xCC80022C
	PE_M23_IPC_CTRL_12_T                                   ipc_ctrl_12;	//0xCC800230
	PE_M23_IPC_CTRL_13_T                                   ipc_ctrl_13;	//0xCC800234
	PE_M23_IPC_CTRL_14_T                                   ipc_ctrl_14;	//0xCC800238
	PE_M23_IPC_CTRL_15_T                                   ipc_ctrl_15;	//0xCC80023C
	PE_M23_IPC_CTRL_16_T                                   ipc_ctrl_16;	//0xCC800240
	PE_M23_IPC_CTRL_17_T                                   ipc_ctrl_17;	//0xCC800244
	PE_M23_IPC_CTRL_18_T                                   ipc_ctrl_18;	//0xCC800248
	PE_M23_IPC_CTRL_19_T                                   ipc_ctrl_19;	//0xCC80024C
	PE_M23_IPC_CTRL_34_T                                   ipc_ctrl_34;	//0xCC800280
	PE_M23_IPC_CTRL_35_T                                   ipc_ctrl_35;	//0xCC800284
	PE_M23_IPC_CTRL_36_T                                   ipc_ctrl_36;	//0xCC800288
	PE_M23_IPC_CTRL_37_T                                   ipc_ctrl_37;	//0xCC80028C
	PE_M23_IPC_CTRL_38_T                                   ipc_ctrl_38;	//0xCC800290
	PE_M23_IPC_CTRL_39_T                                   ipc_ctrl_39;	//0xCC800294
	PE_M23_IPC_CTRL_40_T                                   ipc_ctrl_40;	//0xCC800298
	PE_M23_IPC_CTRL_41_T                                   ipc_ctrl_41;	//0xCC80029C
	PE_M23_IPC_CTRL_42_T                                   ipc_ctrl_42;	//0xCC8002A0
	PE_M23_IPC_CTRL_43_T                                   ipc_ctrl_43;	//0xCC8002A4
	PE_M23_IPC_CTRL_44_T                                   ipc_ctrl_44;	//0xCC8002A8
	PE_M23_IPC_CTRL_45_T                                   ipc_ctrl_45;	//0xCC8002AC
	PE_M23_IPC_CTRL_46_T                                   ipc_ctrl_46;	//0xCC8002B0
	PE_M23_IPC_CTRL_47_T                                   ipc_ctrl_47;	//0xCC8002B4
	PE_M23_IPC_CTRL_48_T                                   ipc_ctrl_48;	//0xCC8002B8
	PE_M23_IPC_CTRL_49_T                                   ipc_ctrl_49;	//0xCC8002BC
	PE_M23_IPC_CTRL_50_T                                   ipc_ctrl_50;	//0xCC8002C0
	PE_M23_IPC_CTRL_51_T                                   ipc_ctrl_51;	//0xCC8002C4
	PE_M23_IPC_CTRL_52_T                                   ipc_ctrl_52;	//0xCC8002C8
	PE_M23_IPC_CTRL_20_T                                   ipc_ctrl_20;	//0xCC8002F0
	PE_M23_IPC_CTRL_21_T                                   ipc_ctrl_21;	//0xCC8002F4
	PE_M23_IPC_CTRL_22_T                                   ipc_ctrl_22;	//0xCC8002F8
	PE_M23_IPC_CTRL_23_T                                   ipc_ctrl_23;	//0xCC8002FC
	PE_M23_IPC_CTRL_24_T                                   ipc_ctrl_24;	//0xCC800300
	PE_M23_IPC_CTRL_25_T                                   ipc_ctrl_25;	//0xCC800304
	PE_M23_IPC_CTRL_26_T                                   ipc_ctrl_26;	//0xCC800308
	PE_M23_IPC_CTRL_27_T                                   ipc_ctrl_27;	//0xCC80030C
	PE_M23_IPC_CTRL_28_T                                   ipc_ctrl_28;	//0xCC800310
	PE_M23_IPC_CTRL_29_T                                   ipc_ctrl_29;	//0xCC800314
	PE_M23_IPC_CTRL_30_T                                   ipc_ctrl_30;	//0xCC800318
	PE_M23_IPC_CTRL_31_T                                   ipc_ctrl_31;	//0xCC80031C
	PE_M23_IPC_CTRL_32_T                                   ipc_ctrl_32;	//0xCC800320
	PE_M23_IPC_CTRL_33_T                                   ipc_ctrl_33;	//0xCC800324
} PE_IPC_HW_PARAM_REG_M23_T;

/**
 *	ipc hw param data type
 */
 typedef struct {
	union {
		UINT32			*addr;
		PE_IPC_HW_PARAM_REG_M23_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_IPC_HW_PARAM_REG_M23_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_IPC_HW_PARAM_REG_M23_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_IPC_HW_PARAM_REG_M23_T *data;
	} reg_data;
} PE_IPC_HW_PARAM_DATA_M23_T;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_IPC_HW_PARAM_M23_H_ */

