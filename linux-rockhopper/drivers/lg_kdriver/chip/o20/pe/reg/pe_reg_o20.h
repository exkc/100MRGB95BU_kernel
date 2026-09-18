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

/** @file pe_reg_o20.h
 *
 *  driver header for picture enhance register read, write functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.02
 *	@see		
 */

#ifndef	_PE_REG_O20_H_
#define	_PE_REG_O20_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "be_kapi.h"
#include "pe_reg_def_o20.h"
#include "pe_cco_reg_o20.h"
#include "pe_cvi_reg_o20.h"
#include "pe_dpe_reg_o20.h"
#include "pe_gsc_reg_o20.h"
#include "pe_nd_reg_o20.h"
#include "pe_shp_reg_o20.h"
#include "pe_sr_shp_reg_o20.h"
#include "pe_vcp_reg_o20.h"
#include "pe_ddr_reg_o20.h"
#include "pe_ddr_reg_f20.h"
#include "pe_lgsr_ddr_reg_o20.h"
#include "pe_lgsr_ddr_reg_f20.h"
#include "pe_hdr_reg_o20.h"
#include "pe_hdr_ddr_o20.h"
#include "pe_chpi_def_f20.h"
#include "pe_chpi_reg_f20.h"
#include "pe_chpi_tbl_f20.h"

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
}PE_MCU_O20_REG_MCU_AD_DNN_BASE_ADDR_T;
/*-----------------------------------------------------------------------------
							 0xc90260dcL reg_mcu_ad_lne_base_addr							  
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lnebaseaddr;	// 31:0
}PE_MCU_O20_REG_MCU_AD_LNE_BASE_ADDR_T;
/*-----------------------------------------------------------------------------
							 0xc90260e0L reg_mcu_ad_tra_ctrl							 
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	runtra							   :1 , // 0 
	updatepatch 					   :1 , // 1 
	readpatch						   :1 , // 2 
	reqpatch						   :1 , // 3 
	setwgtgenlr 					   :4 , // 7:4
	reqwgtupdating					   :1 , // 8 
	reqwgtlatest					   :1 , // 9 
	resvd1							   :1 , // 10
	inittra 						   :1 , // 11
	donetra 						   :1 , // 12
	errtra							   :1 , // 13
	runval							   :1 , // 14
	targetwgt						   :3 , // 17:15
	doneval 						   :1 , // 18
	errval							   :1 , // 19
	runqnt							   :1 , // 20:20
	doneqnt 						   :1 , // 21:21
	errqnt							   :1 , // 22:22
	resvd3							   :1 , // 23:23
	uselasted						   :1 , // 24:24
	resvd4							   :6 , // 30:25
	demomodetra 					   :1 ; // 31
}PE_MCU_O20_REG_MCU_AD_TRA_CTRL_T;
/*-----------------------------------------------------------------------------
							 0xc90260e4L reg_mcu_ad_lne_ctrl							 
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	runlne							   :1 , // 0 
	updatepos						   :1 , // 1 
	readpos 						   :1 , // 2 
	reqpos							   :1 , // 3 
	cropposx						   :9 , // 12:4
	cropposy						   :9 , // 21:13
	condataon						   :1 , // 22
	resvd1							   :1 , // 23
	initlne 						   :1 , // 24
	donelne 						   :1 , // 25
	errlne							   :1 , // 26
	reqcondat						   :1 , // 27
	infwgt							   :3 , // 30:28
	demomodelne 					   :1 ; // 31
}PE_MCU_O20_REG_MCU_AD_LNE_CTRL_T;
/*-----------------------------------------------------------------------------
							 0xc90260e8L ad_gen_14							   
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sr_sqm_position_y				   :12 ,	// 11:0
	sr_sqm_position_x				   :12 ,	// 23:12
	pos_count						   :2  ;	// 25:24
}PE_MCU_O20_AD_GEN_14_T;
/*-----------------------------------------------------------------------------
							 0xc90260ecL ad_gen_15							   
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cpu_debug_reg15;	// 31:0
}PE_MCU_O20_AD_GEN_15_T;	

typedef struct
{ 
	PE_MCU_O20_REG_MCU_AD_DNN_BASE_ADDR_T				 reg_mcu_ad_dnn_base_addr;	//0x00D8
	PE_MCU_O20_REG_MCU_AD_LNE_BASE_ADDR_T				 reg_mcu_ad_lne_base_addr;	//0x00DC
	PE_MCU_O20_REG_MCU_AD_TRA_CTRL_T					 reg_mcu_ad_tra_ctrl;	//0x00E0
	PE_MCU_O20_REG_MCU_AD_LNE_CTRL_T					 reg_mcu_ad_lne_ctrl;	//0x00E4
	PE_MCU_O20_AD_GEN_14_T								 ad_gen_14; //0x00E8
	PE_MCU_O20_AD_GEN_15_T								 ad_gen_15; //0x00EC
}PE_MCU_REG_O20_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_MCU_REG_O20_T *data;
	} shdw;

	union {
		volatile UINT32 		 *addr;
		volatile PE_MCU_REG_O20_T *data;
	} phys;
} PE_MCU_REG_TYPE_O20_T;

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
} PE_REG_O20_HW_OPT_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_REG_O20_WD(UINT32 addr, UINT32 value);
int PE_REG_O20_WrAllocatedAddr(UINT32 addr, UINT32 value);
UINT32 PE_REG_O20_RD(UINT32 addr);
int PE_REG_O20_WrReg(LX_PE_ETC_TBL_T *pstParams);
int PE_REG_O20_RdReg(LX_PE_ETC_TBL_T *pstParams);
int PE_REG_O20_InitPhyToVirt(void);
int PE_REG_O20_FreePhyToVirt(void);
int PE_REG_O20_SetTraceTable(UINT32 type,const char* fn,UINT32 line,char *tbl,UINT32 ofst);
PE_REG_O20_HW_OPT_T PE_REG_O20_GetDispOpt(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern PE_CE_PE1_REG_TYPE_O20_T   gPE_CE_PE1_O20;
extern PE_CO_PE1_REG_TYPE_O20_T   gPE_CO_PE1_O20;
extern PE_CE2_PE1_REG_TYPE_O20_T   gPE_CE2_PE1_O20;
extern PE_CO2_PE1_REG_TYPE_O20_T   gPE_CO2_PE1_O20;
extern PE_CVI_REG_TYPE_O20_T      gPE_CVI_A_O20;
extern PE_CVI_REG_TYPE_O20_T      gPE_CVI_B_O20;
extern PE_CVI_REG_TYPE_O20_T      gPE_CVI_C_O20;
extern PE_CVI_REG_TYPE_O20_T      gPE_CVI_D_O20;
extern PE_LED_RP_REG_TYPE_O20_T   gPE_LED_RP_O20;
extern PE_GSC_Y_REG_TYPE_O20_T    gPE_GSC_Y_O20;
extern PE_GSC_C_REG_TYPE_O20_T    gPE_GSC_C_O20;
extern PE_ND_ND0_REG_TYPE_O20_T   gPE_ND_ND0_O20;
extern PE_ND_DNR0_REG_TYPE_O20_T  gPE_ND_DNR0_O20;
extern PE_ND_ND0_REG_TYPE_O20_T   gPE_ND_ND1_O20;
extern PE_ND_DNR0_REG_TYPE_O20_T  gPE_ND_DNR1_O20;
extern PE_SHP_REG_TYPE_O20_T      gPE_SHP_O20;
extern PE_VSD_OBC_O_REG_TYPE_O20_T	gPE_VSD_OBC_O_O20;
extern PE_VSD_OBC_F_REG_TYPE_O20_T	gPE_VSD_OBC_F_O20;
extern PE_VSD_RCE_O_REG_TYPE_O20_T	gPE_VSD_RCE_O_O20;
extern PE_VSD_RCE_F_REG_TYPE_O20_T	gPE_VSD_RCE_F_O20;
extern PE_VSD_DTM_REG_TYPE_O20_T	gPE_VSD_DTM_O20;
extern PE_SR_CHR_SHP_REG_TYPE_O20_T  gPE_SR_CHR_SHP_O20;
extern PE_SR_2K_SHP_REG_TYPE_O20_T   gPE_SR_2K_SHP_O20;
extern PE_SR_MERG_REG_TYPE_O20_T   gPE_SR_MERG_O20;
extern PE_VCP_DISP_REG_TYPE_O20_T 	gPE_VCP_DISP_O20;
extern PE_VSD_VERI_REG_TYPE_O20_T 	  gPE_VSD_VERI_O20;
extern PE_DDR_DB_REG_TYPE_O20_T     gPE_DDR_DB_O20;
extern PE_DDR_DB_REG_TYPE_F20_T     gPE_DDR_DB_F20;
extern PE_LGSR_DDR_DB_REG_TYPE_O20_T     gPE_LGSR_DDR_DB_O20;
extern PE_LGSR_DDR_DB_REG_TYPE_F20_T     gPE_LGSR_DDR_DB_F20;
extern PE_TOP_IMX_REG_TYPE_O20_T  	gPE_TOP_IMX_O20;
//extern PE_IPP_REG_TYPE_O20_T      	gPE_IPP_O20;

extern volatile UINT32			 	*gpe_vsd_ctrl_block_o20;
extern PE_LED_DCNT_REG_TYPE_O20_T   gPE_LED_DCNT_O20;

extern PE_HDR_REG_O20_H10_T    gPE_H10_E_O20;
extern PE_HDR_REG_O20_H10_T    gPE_H10_O_O20;
extern PE_HDR_REG_O20_H10_P_T  gPE_H10_P_O20;
extern PE_HDR_REG_O20_S2H_T    gPE_S2H_E_O20;
extern PE_HDR_REG_O20_S2H_T    gPE_S2H_O_O20;
extern PE_HDR_REG_O20_GAV_T    gPE_GAV_O20;
extern volatile UINT32         *gPE_HDR_DDR_O20;
extern PE_MCU_REG_TYPE_O20_T   gPE_MCU_O20;
extern PE_CCO_VERI_REG_TYPE_O20_T   gPE_CCO_VERI_O20;
extern PE_ND_ND0_VERI_REG_TYPE_O20_T   gPE_ND_ND0_VERI_O20;

extern PE_CHPI_REG_TYPE_F20_T gPE_CHPI_APB0_F20;
extern PE_CHPI_REG_TYPE_F20_T gPE_CHPI_APB1_F20;//causion : shdw not used(null)
extern PE_CHPI_TBL0_TYPE_F20_T gPE_CHPI_TBL0_F20;
extern PE_CHPI_TBL0_TYPE_F20_T gPE_CHPI_TBL1_F20;//causion : shdw not used(null)
extern volatile UINT32        *gPE_CHPI_DDR;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_REG_O20_H_ */
