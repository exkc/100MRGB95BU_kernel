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

/** @file pe_reg_o22.h
 *
 *  driver header for picture enhance register read, write functions. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.04.02
 *	@see
 */

#ifndef	_PE_REG_O22_H_
#define	_PE_REG_O22_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "be_kapi.h"
#include "pe_reg_def_o22.h"
#include "pe_cco_reg_o22.h"
#include "pe_cvi_reg_o22.h"
#include "pe_dpe_reg_o22.h"
#include "pe_gsc_reg_o22.h"
#include "pe_nd_reg_o22.h"
#include "pe_shp_reg_o22.h"
#include "pe_sr_shp_reg_o22.h"
#include "pe_vcp_reg_o22.h"
#include "pe_ddr_reg_o22.h"
#include "pe_ddr_reg_o22f22.h"
#include "pe_lgsr_ddr_reg_o22.h"
#include "pe_lgsr_ddr_reg_o22f22.h"
#include "pe_hdr_reg_o22.h"
#include "pe_hdr_ddr_o22.h"
#include "pe_chpi_def_o22f22.h"
#include "pe_chpi_reg_o22f22.h"
#include "pe_chpi_tbl_o22f22.h"
#include "pe_dcm_ddr_reg_o22f22.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
							 0xc90260d8L reg_mcu_ad_dnn_base_addr
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dnnsrbaseaddr;	// 31:0
}PE_MCU_O22_REG_MCU_AD_DNN_BASE_ADDR_T;
/*-----------------------------------------------------------------------------
							 0xc90260dcL reg_mcu_ad_lne_base_addr
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lnebaseaddr;	// 31:0
}PE_MCU_O22_REG_MCU_AD_LNE_BASE_ADDR_T;
/*-----------------------------------------------------------------------------
							 0xc90260e0L reg_mcu_ad_lne_ctrl_0
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	uiOnOff 		   :1,	// 0: 0 //(MCU0->MCU1) AI PQ pro UI On/Off inform
	runLNE			  :1,  // 1: 1 //(MCU0->MCU1) SR-SQM 동작 Turn On/Off
	conDataOn	:1,  // 2: 2 //(MCU0->MCU1) Checked Trained 8 hour after first boot
	resvd0		:1,  // 3: 3 // reserved
	cropPosX	:9,  // 4:12 //(MCU0->MCU1) Crop position X (based on L3 size)
	cropPosY	:9,  //13:21 //(MCU0->MCU1) Crop position Y (based on L3 size)
	resvd1			:2, //22:23 // reserved
	updatePos		:1,  //24:24 //(MCU0->MCU1) After done of Crop position generation from PLA
	resvd2			:3,  //25:27 // reserved
	accMode 	:1,  //28:28 //(MCU0->MCU1) LGSR Command 3: Acceleration 30 min
	forceTestQA :1,  //29:29 //(MCU0->MCU1) LGSR Command 3: Acceleration 2 min
	useDef				:1,  //30:30 //(MCU0->MCU1) LGSR Command 4: Reset (Using Default Weight)
	histRst 	:1;  //31:31 //(MCU0->MCU1) LGSR Command 6: histogram reset
}PE_MCU_O22_REG_MCU_AD_LNE_CTRL_0_T;
/*-----------------------------------------------------------------------------
							 0xc90260e4L reg_mcu_ad_lne_ctrl_1
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	runStatus		:1,  // 0: 0 //(MCU1->MCU0)
	readPos 	:1,  // 1: 1 //(MCU1->MCU0) Set 1 after read Patch, Set 0 after 
	reqPos		:1,  // 2: 2 //(MCU1->MCU0) Request crop position 
	resvd0		:1,  // 3: 3 // reserved
	initLNE 			:1,  // 4: 4 //(MCU1->MCU0) LNE의 initialization 완료 후 1 설정(유지)
	doneLNE 		:1,  // 5: 5 //(MCU1->MCU0) LOOP 1회 완료 후 1 설정, 재 진행 시 0으로 설정
	resvd1		:2,  // 6: 7 // reserved
	errLNE				:4,  // 8:11 //(MCU1->MCU0) Error status 확인 용
	reqConDat		:2,  //12:13 //(MCU1->MCU0) Status of accumulated data from eMMC
	resvd2		:2,  //14:15 // reserved
	infWgt				:4,  //16:19 //(MCU1->MCU0) SR-SQM에서 선택된 SR Inference용 weight index (실제 화질 반영)
	resvd3		:4,  //20:23 // reserved
	traUpdateCnt	:2,  //24:25 //(MCU1->MCU0) Count up after SQM Training done(linked with Pop-Up)
	traIgnoreCnt	:2,  //26:27 //(MCU1->MCU0) Count up SQM after criteria of traning (ex.8H)(linked with MCU0 Log)
	resvd4		:4;  //28:31 // reserved
}PE_MCU_O22_REG_MCU_AD_LNE_CTRL_1_T;
/*-----------------------------------------------------------------------------
							 0xc90260e8L ad_gen_14
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sr_sqm_position_y				   :12 ,	// 11:0
	sr_sqm_position_x				   :12 ,	// 23:12
	pos_count						   :2  ;	// 25:24
}PE_MCU_O22_AD_GEN_14_T;
/*-----------------------------------------------------------------------------
							 0xc90260ecL ad_gen_15
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cpu_debug_reg15;	// 31:0
}PE_MCU_O22_AD_GEN_15_T;

typedef struct
{
	PE_MCU_O22_REG_MCU_AD_DNN_BASE_ADDR_T				 reg_mcu_ad_dnn_base_addr;	//0x00c0
	PE_MCU_O22_REG_MCU_AD_LNE_BASE_ADDR_T				 reg_mcu_ad_lne_base_addr;	//0x00c4
	PE_MCU_O22_REG_MCU_AD_LNE_CTRL_0_T					 reg_mcu_ad_lne_ctrl_0;	//0x00c8
	PE_MCU_O22_REG_MCU_AD_LNE_CTRL_1_T					 reg_mcu_ad_lne_ctrl_1;	//0x00cc
	PE_MCU_O22_AD_GEN_14_T								 ad_gen_14; //0x00D0
	PE_MCU_O22_AD_GEN_15_T								 ad_gen_15; //0x00D4
}PE_MCU_REG_O22_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_MCU_REG_O22_T *data;
	} shdw;

	union {
		volatile UINT32 		 *addr;
		volatile PE_MCU_REG_O22_T *data;
	} phys;
} PE_MCU_REG_TYPE_O22_T;

typedef union {
	UINT32 u32Data;
	struct {
		UINT32 panel_type       :3;	 // [2:0] panel type / 0:LCD, 1:OLED, 2:BOX
		UINT32 set_type         :3;	 // [5:3] set type
		UINT32 panel_maker      :3;  // [8:6] panel_maker
		UINT32 panel_resolution :4;  // [12:9] panel_resolution
		UINT32 panel_frame_rate :2;	 // [14:13] panel_frame_rate
		UINT32 external_chip    :2;  // [16:15] external_chip
		UINT32 tcon_Scramble    :1;  // [17] tcon_Scramble
		UINT32 reserved         :11; // [28:18] RSVD
		UINT32 panel_carry_over :2;	 // [30:29] panel_carry_over
		UINT32 vx1_byte         :1;  // [31] VX1_BYTE
	};
} PE_REG_O22_HW_OPT_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_REG_O22_WD(UINT32 addr, UINT32 value);
int PE_REG_O22_WrAllocatedAddr(UINT32 addr, UINT32 value);
UINT32 PE_REG_O22_RD(UINT32 addr);
int PE_REG_O22_WrReg(LX_PE_ETC_TBL_T *pstParams);
int PE_REG_O22_RdReg(LX_PE_ETC_TBL_T *pstParams);
int PE_REG_O22_InitPhyToVirt(void);
int PE_REG_O22_FreePhyToVirt(void);
int PE_REG_O22_SetTraceTable(UINT32 type,const char* fn,UINT32 line,char *tbl,UINT32 ofst);
PE_REG_O22_HW_OPT_T PE_REG_O22_GetDispOpt(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern PE_CC_PE1_REG_TYPE_O22_T   gPE_CC_PE1_O22;
extern PE_CC2_PE1_REG_TYPE_O22_T  gPE_CC2_PE1_O22;
extern PE_CVI_REG_TYPE_O22_T      gPE_CVI_A_O22;
extern PE_CVI_REG_TYPE_O22_T      gPE_CVI_B_O22;
extern PE_CVI_REG_TYPE_O22_T      gPE_CVI_C_O22;
extern PE_CVI_REG_TYPE_O22_T      gPE_CVI_D_O22;
extern PE_GSC_Y_REG_TYPE_O22_T    gPE_GSC_Y_O22;
extern PE_GSC_C_REG_TYPE_O22_T    gPE_GSC_C_O22;
extern PE_ND_ND0_REG_TYPE_O22_T   gPE_ND_ND0_O22;
extern PE_ND_DNR0_REG_TYPE_O22_T  gPE_ND_DNR0_O22;
extern PE_ND_ND0_REG_TYPE_O22_T   gPE_ND_ND1_O22;
extern PE_ND0_VERI_REG_TYPE_O22_T   gPE_ND0_VERI_O22;
extern PE_ND1_VERI_REG_TYPE_O22_T   gPE_ND1_VERI_O22;
extern PE_SHP_REG_TYPE_O22_T      gPE_SHP_O22;
extern PE_VSD_OBC_BODY_REG_TYPE_O22_T	gPE_VSD_OBC_BODY_O22;
extern PE_VSD_OBC_HEAD_REG_TYPE_O22_T	gPE_VSD_OBC_HEAD_O22;
extern PE_VSD_OBC_M_SC_REG_TYPE_O22_T	gPE_VSD_OBC_M_SC_O22;
extern PE_AMG_BODY_REG_TYPE_O22_T	gPE_AMG_BODY_O22;
extern PE_AMG_HEAD_REG_TYPE_O22_T	gPE_AMG_HEAD_O22;
extern PE_VSD_OBE_REG_TYPE_O22_T	gPE_VSD_OBE_O22;
extern PE_OSD_ORD_REG_TYPE_O22_T	gPE_OSD_ORD_O22;
extern PE_VSD_DTM_REG_TYPE_O22_T	gPE_VSD_DTM_O22;
extern PE_SR_2K_SHP_REG_TYPE_O22_T  gPE_SR_2K_SHP_O22;
extern PE_SR_2K_SHC_REG_TYPE_O22_T  gPE_SR_2K_SHC_O22;
extern PE_SR_MERG_REG_TYPE_O22_T    gPE_SR_MERG_O22;
extern PE_SR_VERI_REG_TYPE_O22_T    gPE_SR_VERI_O22;
extern PE_VCP_DISP_REG_TYPE_O22_T 	gPE_VCP_DISP_O22;
extern PE_VSD0_VERI_REG_TYPE_O22_T gPE_VSD0_VERI_O22;
extern PE_DDR_DB_REG_TYPE_O22_T     gPE_DDR_DB_O22;
extern PE_DDR_DB_REG_TYPE_O22F22_T  gPE_DDR_DB_O22F22;
extern PE_DCM_DDR_DB_REG_TYPE_O22F22_T  gPE_DCM_DDR_DB_O22F22;
extern PE_DBC_DDR_DB_REG_TYPE_O22F22_T  gPE_DBC_DDR_DB_O22F22;

#if 0	//TODO:
extern PE_LGSR_DDR_DB_REG_TYPE_O22_T     gPE_LGSR_DDR_DB_O22;
extern PE_LGSR_DDR_DB_REG_TYPE_O22F22_T  gPE_LGSR_DDR_DB_O22F22;
#endif

extern PE_TOP_IMX_REG_TYPE_O22_T gPE_TOP_IMX_O22;
extern PE_LED_DCNT_REG_TYPE_O22_T gPE_LED_DCNT_O22;
extern PE_MCU_REG_TYPE_O22_T   gPE_MCU_O22;
extern PE_CCO_VERI_REG_TYPE_O22_T   gPE_CCO_VERI_O22;

extern PE_HDR_REG_O22_H10_T gPE_H10_0_O22;
extern PE_HDR_REG_O22_H10_T gPE_H10_1_O22;
extern PE_HDR_REG_O22_VERI_T gPE_HDR_VERI_O22;
extern volatile PE_HDR_DDR_O22_T *gPE_HDR_DDR_O22;

extern PE_CHPI_REG_TYPE_O22F22_T gPE_CHPI_APB0_O22F22;
extern PE_CHPI_REG_TYPE_O22F22_T gPE_CHPI_APB1_O22F22;//causion : shdw not used(null)
extern PE_CHPI_TBL0_TYPE_O22F22_T gPE_CHPI_TBL0_O22F22;
extern PE_CHPI_TBL0_TYPE_O22F22_T gPE_CHPI_TBL1_O22F22;//causion : shdw not used(null)
extern volatile UINT32        *gPE_CHPI_DDR_O22;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_REG_O22_H_ */
