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

/** @file pe_reg_o18.h
 *
 *  driver header for picture enhance register read, write functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.02
 *	@see		
 */

#ifndef	_PE_REG_O18_H_
#define	_PE_REG_O18_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "be_kapi.h"
#include "pe_reg_def_o18.h"
#include "pe_cco_reg_o18.h"
#include "pe_cvi_reg_o18.h"
#include "pe_dpe_reg_o18.h"
#include "pe_gsc_reg_o18.h"
#include "pe_nd_reg_o18.h"
#include "pe_shp_reg_o18.h"
#include "pe_sr_shp_reg_o18.h"
#include "pe_vcp_reg_o18.h"
#include "pe_ddr_reg_o18.h"
#include "pe_hdr_reg_o18.h"
#include "pe_hdr_ddr_o18.h"
#include "pe_sr_msc_reg_o18.h"

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

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_REG_O18_WD(UINT32 addr, UINT32 value);
int PE_REG_O18_WrAllocatedAddr(UINT32 addr, UINT32 value);
UINT32 PE_REG_O18_RD(UINT32 addr);
int PE_REG_O18_WrReg(LX_PE_ETC_TBL_T *pstParams);
int PE_REG_O18_RdReg(LX_PE_ETC_TBL_T *pstParams);
int PE_REG_O18_InitPhyToVirt(void);
int PE_REG_O18_FreePhyToVirt(void);
int PE_REG_O18_SetTraceTable(const char* fn, UINT32 line, char *tbl, UINT32 ofst);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern PE_CE_PE1_REG_TYPE_O18_T   gPE_CE_PE1_O18;
extern PE_CO_PE1_REG_TYPE_O18_T   gPE_CO_PE1_O18;
extern PE_HDMI_REG_TYPE_O18_T     gPE_HDMI_A_O18;
extern PE_HDMI_REG_TYPE_O18_T     gPE_HDMI_B_O18;
extern PE_HDMI_REG_TYPE_O18_T     gPE_HDMI_C_O18;
extern PE_HDMI_REG_TYPE_O18_T     gPE_HDMI_D_O18;
extern PE_CVI_REG_TYPE_O18_T      gPE_CVI_A_O18;
extern PE_CVI_REG_TYPE_O18_T      gPE_CVI_B_O18;
extern PE_CVI_REG_TYPE_O18_T      gPE_CVI_C_O18;
extern PE_CVI_REG_TYPE_O18_T      gPE_CVI_D_O18;
extern PE_LED_RP_REG_TYPE_O18_T   gPE_LED_RP_O18;
extern PE_GSC_Y_REG_TYPE_O18_T    gPE_GSC_Y_O18;
extern PE_GSC_C_REG_TYPE_O18_T    gPE_GSC_C_O18;
extern PE_ND_ND0_REG_TYPE_O18_T   gPE_ND_ND0_O18;
extern PE_ND_DNR0_REG_TYPE_O18_T  gPE_ND_DNR0_O18;
extern PE_ND_ND0_REG_TYPE_O18_T   gPE_ND_ND1_O18;
extern PE_ND_DNR0_REG_TYPE_O18_T  gPE_ND_DNR1_O18;
extern PE_SHP_REG_TYPE_O18_T      gPE_SHP_O18;
extern PE_SHP_PSP_REG_TYPE_O18_T	gPE_SHP_PSP_O18;
extern PE_SHP_PSP_GAIN_REG_TYPE_O18_T	gPE_SHP_PSP_GAIN_O18;
extern PE_SR_CHR_SHP_REG_TYPE_O18_T  gPE_SR_CHR_SHP_O18;
extern PE_SR_2K_SHP_REG_TYPE_O18_T   gPE_SR_2K_SHP_O18;
extern PE_SR_4K_SHP_REG_TYPE_O18_T   gPE_SR_4K_SHP_O18;
#if 1
extern PE_SR_2K_MSC_Y_REG_TYPE_O18_T gPE_2K_SR_MSC_Y_O18;
extern PE_SR_MSC_Y_REG_TYPE_O18_T    gPE_SR_MSC_Y_O18;
extern PE_SR_MSC_C_REG_TYPE_O18_T    gPE_SR_MSC_C_O18;
#endif
extern PE_VCP_DISP_REG_TYPE_O18_T 	gPE_VCP_DISP_O18;
extern PE_DDR_DB_REG_TYPE_O18_T     gPE_DDR_DB_O18;
extern PE_TOP_IMX_REG_TYPE_O18_T  	gPE_TOP_IMX_O18;
//extern PE_IPP_REG_TYPE_O18_T      	gPE_IPP_O18;
extern PE_HDR10_REG_TYPE_O18_T      gPE_HDR10_O18;
extern PE_HDR10_REG_TYPE_O18_T      gPE_HDR10_2_O18;
extern PE_S2H_REG_TYPE_O18_T        gPE_S2H_O18;
extern PE_S2H_REG_TYPE_O18_T        gPE_S2H_2_O18;
//extern PE_DDR_DB_REG_TYPE_O18_T     gPE_DDR_DB_O18;
extern volatile UINT32			 	*gpe_vsd_ctrl_block_o18;
extern volatile UINT32				*gPE_HDR_DDR_O18;
extern volatile UINT32				*gPE_DDR_BLK_APL_O18;
extern PE_LED_DCNT_REG_TYPE_O18_T   gPE_LED_DCNT_O18;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_REG_O18_H_ */
