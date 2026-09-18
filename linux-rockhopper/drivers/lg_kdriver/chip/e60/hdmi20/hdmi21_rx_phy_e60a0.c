/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 


/** @file 
 *
 *  Brief description. 
 *  Detailed description starts here. 
 *
 *  @author		won.hur
 *  @version	1.0 
 *  @date		2019-12-17
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */

#include "hdmi21_rx_phy_e60a0.h"
#include "hdmi21_cfg_e60.h"
#include "../../../core/hdmi20/hdmi21_engine/hdmi21_hal_driver.h"
#include "../../../core/hdmi20/hdmi21_engine/hdmi21_rx_snps_scdc.h"
#include "hdmi20_drv.h"
#include "hdmi20_module.h"

#include "os_util.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMI21_PHY_TCS_HIST_HISTORY_DEPTH	10

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
/* E60A0 */
static void __PHY_Reg_E60A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData);
static void __PHY_Reg_E60A0_WrFL(UINT8 port, UINT32 reg, UINT32 data);

static void __PHY_Reg_B1_E60A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData);
static void __PHY_Reg_B1_E60A0_WrFL(UINT8 port, UINT32 reg, UINT32 data);

static void __PHY_Reg_B2_E60A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData);
static void __PHY_Reg_B2_E60A0_WrFL(UINT8 port, UINT32 reg, UINT32 data);

/* TCS State Hist */
static void __HDMI21_PHY_E60A0_IncreaseTcsStateHistIdx(UINT8 port);
static int __HDMI21_PHY_E60A0_CheckTcsStateHistMatchVal(UINT8 port, UINT32 val);

/* DFE Center */
static void __HDMI21_PHY_E60A0_SetDfeResultCenter(UINT8 port);
/* DR_RESETB */
static int __HDMI21_PHY_E60A0_ToggleDrResetB(int port, int isSet);
static int __HDMI21_PHY_E60A0_ToggleCrModeSelResetB(int port, int isSet);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevPhyControler[HDMI21__DEV_PHY_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];
extern HDMI21_THREAD_CONTROLLER_T gHDMI21Thread;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
/* E60A0 */
HDMI21_PHY_REG_CTRL_E60A0_T 	phyReg_e60a0[HDMI21_NUM_OF_PORTS_E60];
HDMI21_PHY_REG_CTRL_B1_E60A0_T 	phyReg_B1_e60a0[HDMI21_NUM_OF_PORTS_E60];
HDMI21_PHY_REG_CTRL_B2_E60A0_T 	phyReg_B2_e60a0[HDMI21_NUM_OF_PORTS_E60];

static UINT32 gPhyTcsStateHist[HDMI21_NUM_OF_PORTS_E60][HDMI21_PHY_TCS_HIST_HISTORY_DEPTH] = {0,};
static int    gPhyTcsStateHistIdx[HDMI21_NUM_OF_PORTS_E60] = {0, };
static int    gPhyFrlFrlStartManualIdx[HDMI21_NUM_OF_PORTS_E60] = {0, };
/*----------------------------------------------------------------------------------------
    Implementation
----------------------------------------------------------------------------------------*/
/* E60A0 */
static void __HDMI21_PHY_E60A0_CheckPhyExceptionCase(UINT8 port, int resetClear);
static void __attribute__((unused)) __HDMI21_PHY_E60A0_SetPhyExceptionCase(UINT8 port, HDMI21_HAL_PHY_EXCEPTION_CASE_T phyCase, int isReverse);
static int 	__HDMI21_PHY_E60A0_Check_CRDone(UINT8 port);
static void __HDMI21_PHY_E60A0_SetI2cManualDFEBxValue(UINT8 port);
static int  __HDMI21_PHY_E60A0_IsOnboardPort(UINT8 port);

/* Common */
static char *phymode_type_to_str(HDMI21_HAL_PHY_INITIATED_MODE_T type)
{
	switch (type)
	{
		case HDMI21_HAL_PHY_INITIATED_ERROR:
		case HDMI21_HAL_PHY_INITIATED_3G:
			return "3G";
		case HDMI21_HAL_PHY_INITIATED_6G:
			return "6G";
		case HDMI21_HAL_PHY_INITIATED_FRL_3G_3L:
			return "FRL 3G 3L(R1)";
		case HDMI21_HAL_PHY_INITIATED_FRL_6G_3L:
			return "FRL 6G 3L(R2)";
		case HDMI21_HAL_PHY_INITIATED_FRL_6G_4L:
			return "FRL 6G 4L(R3)";
		case HDMI21_HAL_PHY_INITIATED_FRL_8G_4L:
			return "FRL 8G 4L(R4)";
		case HDMI21_HAL_PHY_INITIATED_FRL_10G_4L:
			return "FRL 10G 4L(R5)";
		case HDMI21_HAL_PHY_INITIATED_FRL_12G_4L:
			return "FRL 12G 4L(R6)";
		default :
				return "Unknown";
	}
}

int HDMI21_PHY_E60A0_CheckDfeDone(UINT8 port)
{
	int ret = 0;

	int ch0DfeDone = 0;
	int ch1DfeDone = 0;
	int ch2DfeDone = 0;
	int ch3DfeDone = 0;

	if(gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_CENTER_SWWA].value > 0) {
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_5f);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_5f, dfe_done_ch0, ch0DfeDone);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_5f, dfe_done_ch1, ch1DfeDone);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_5f, dfe_done_ch2, ch2DfeDone);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_5f, dfe_done_ch3, ch3DfeDone);

		if(gHDMI21RxHandler[port].phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_FRL_6G_3L){
			ch3DfeDone = 1;
		}

		if((ch0DfeDone > 0) &&(ch1DfeDone > 0) &&(ch2DfeDone > 0) &&(ch3DfeDone > 0)) {
			PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_59);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x8);
			PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5a);

			HDMI20_PHY("PHY[%d] : Detected DFE done for DFE-Center SWWA. Set EQ Sucess Sel [8]->[7]\n", port);

			PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_59);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x7);
			PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5a);

			if(gHDMI21RxDevPhyControler[HDMI21__PHY_CH0_SSB_CHECK_ON].value > 0 ) {
				gHDMI21RxHandler[port].phyFrlSwWaState = 2;
			}
			else {
				gHDMI21RxHandler[port].phyFrlSwWaState = 3;
			}
		
			ret = 1;
		}
		else {
			HDMI21_LINE_DBG(502, "DBG[%d] : DFE Done[%d][%d][%d][%d]\n", port, ch0DfeDone, ch1DfeDone, ch2DfeDone, ch3DfeDone);
		}
	}
	else {
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_59);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x8);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5a);

		HDMI20_PHY("PHY[%d] : Set EQ Sucess Sel [8]->[7]\n", port);

		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_59);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x7);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5a);

		if(gHDMI21RxDevPhyControler[HDMI21__PHY_CH0_SSB_CHECK_ON].value > 0 ) {
			gHDMI21RxHandler[port].phyFrlSwWaState = 2;
		}
		else {
			gHDMI21RxHandler[port].phyFrlSwWaState = 3;
		}
	
		ret = 1;
	}

	return ret;
}

void HDMI21_PHY_E60A0_InitiateDfeCenter(UINT8 port)
{
	int __attribute__((unused)) ch0DfeDone = 0;
	int __attribute__((unused)) ch1DfeDone = 0;
	int __attribute__((unused)) ch2DfeDone = 0;
	int __attribute__((unused)) ch3DfeDone = 0;

	if(gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_CENTER_SWWA].value > 0) {
		HDMI20_PHY("PHY[%d] : Initiate Calculation of DFE Center Position!\n", port);
		HDMI21_PHY_E60A0_Update_TMDS_TCS_Value(port, 0);
		__HDMI21_PHY_E60A0_SetDfeResultCenter(port);
	}

	/* 2019/12/04 : CROW.KIM said to do this due to chip bug */
	if(gHDMI21RxHandler[port].phyInitiatedMode != HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_58);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, 1);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_58);
	}

	gHDMI21RxHandler[port].phyFrlSwWaState = 1;
}


/* IOCTL */
int HDMI21_PHY_E60A0_Rx_Get_PHYStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall)
{
	int ret = RET_ERROR;
	LX_HDMI_PHY_INFORM_T userdata;
	UINT32 tempData;
	UINT32 valuefor5V[HDMI21_NUM_OF_PORTS_E60] = {0,};
	int i;

	int deltaError = 0;
	int cedError = 0;
	int SyncRecovery = 0;
	int tcsError = 0;
	int isCrDone = 0;
	int updateTcsValue = 0;
	int deltaEye = 0;
	int dfeResult = 0;
	int __attribute__((unused)) phyErrorCounter = 0;

	do{
		if(pData == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI_PHY_INFORM_T)){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_PHY_INFORM_T), size);
			break;
		}

		/* Step 1. Initiate Data */
		memset((void *)&userdata, 0, sizeof(LX_HDMI_PHY_INFORM_T));

		/* Step 2. Insert data */
		/* Step 2-1. HDMI/DVI Mode */
		for(i=0; i<HDMI21_NUM_OF_PORTS_E60; i++){
			userdata.hdmi_mode[i] = gHDMI21RxHandler[i].hwVideo.dvi;		// < hdmi/dvi mode
		}

		/* Step 2-2. 5V Info */
		/* SW W/A for webos Popup sign for SONY EXPERIA Z2*/
		if(gHDMI21RxDevVideoControler[HDMI21__HOLD_TIME_5V_DETECTION].value == 0){
			for(i=0; i<HDMI21_NUM_OF_PORTS_E60; i++){
				HDMI21_HAL_Rx_Get_Check5VLevelInfo(i, &valuefor5V[i], 1);
				if(valuefor5V[i] != 0) userdata.hdmi5v[i] = 1;
				else userdata.hdmi5v[i] = 0;
			}
		}
		else{
			for(i=0; i<HDMI21_NUM_OF_PORTS_E60; i++){
				if(gHDMI21RxHandler[i].connected5Vtime >= gHDMI21RxDevPhyControler[HDMI21__HOLD_TIME_5V_DETECTION].value) userdata.hdmi5v[i] = 1;	
				else userdata.hdmi5v[i] = 0;
			}
		}

		if(updatePhyI2C > 0){
			for(i=0; i<HDMI21_NUM_OF_PORTS_E60; i++){
				if(userdata.hdmi5v[i] > 0){
					/* Read Errors */
					tcsError = HDMI21_PHY_E60A0_Check_TMDSError(i);
					SyncRecovery = HDMI21_PHY_E60A0_Check_SyncRecovery(i);
					isCrDone = __HDMI21_PHY_E60A0_Check_CRDone(i);
					cedError = HDMI21_PHY_E60A0_Check_CEDError(i);
					deltaError = HDMI21_PHY_E60A0_Check_DeltaError(i);
					deltaEye = HDMI21_PHY_E60A0_Check_DeltaEye(i);
					if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_UPDATE_PHY_DFE_RESULT].value > 0){
						dfeResult = HDMI21_PHY_E60A0_Check_DfeResult(i);
					}

					updateTcsValue = HDMI21_PHY_E60A0_Update_TMDS_TCS_Value(i, 0);
				}
			}
		}

		for(i=0; i<HDMI21_NUM_OF_PORTS_E60; i++){
			/* Step 2-3. HPD Info */
			userdata.hpd_out[i] = gHDMI21RxHandler[i].isHPD;		//	< HPD out status on each ports

			/* Step 2-4. TMDS Clk Info */	
			userdata.tmds_clock[i] = gHDMI21RxHandler[i].real_tmds_clk;				// Phy TMDS Clock

			/* Step 2-5. HPD Polarity Info */
			userdata.hpd_pol[i] = gHDMI21RxHandler[i].isHPDInverseMode;	

		}

		/* Step 2-6. PHY PDB */
		for(i=0; i<HDMI21_NUM_OF_PORTS_E60; i++){
			tempData = gHDMI21RxHandler[i].top_read(HDMI21_TOP_REG_AD_MAIN_PHY_CTRL);
			if((tempData & HDMI21_TOP_FIELD_O_REG_PHY_PDB) != 0) userdata.phy_pdb[i] = 1;
			else userdata.phy_pdb[i] = 0;
		}

		/* Step 2-7. PHY RSTN */
		/* None */

		for(i=0; i<HDMI21_NUM_OF_PORTS_E60; i++){
			/* Step 2-8. TCS Done */
			userdata.tcs_done[i] = gHDMI21RxHandler[i].phyTCSDone;

			/* Step 2-9. TCS Min */
			userdata.tcs_min[i][0] = gHDMI21RxHandler[i].phyTCSMin[0];	
			userdata.tcs_min[i][1] = gHDMI21RxHandler[i].phyTCSMin[1];	
			userdata.tcs_min[i][2] = gHDMI21RxHandler[i].phyTCSMin[2];	
			userdata.tcs_min[i][2] = gHDMI21RxHandler[i].phyTCSMin[3];	

			/* Step 2-10. TCS max */
			userdata.tcs_max[i][0] = gHDMI21RxHandler[i].phyTCSMax[0];	
			userdata.tcs_max[i][1] = gHDMI21RxHandler[i].phyTCSMax[1];	
			userdata.tcs_max[i][2] = gHDMI21RxHandler[i].phyTCSMax[2];	
			userdata.tcs_max[i][3] = gHDMI21RxHandler[i].phyTCSMax[3];	

			/* Step 2-11. TCS result */
			userdata.tcs_result[i][0] = gHDMI21RxHandler[i].phyTCSResult[0];	
			userdata.tcs_result[i][1] = gHDMI21RxHandler[i].phyTCSResult[1];	
			userdata.tcs_result[i][2] = gHDMI21RxHandler[i].phyTCSResult[2];	
			userdata.tcs_result[i][3] = gHDMI21RxHandler[i].phyTCSResult[3];	

			userdata.tcs_error[i][0] = gHDMI21RxHandler[i].phyTMDSError[0];
			userdata.tcs_error[i][1] = gHDMI21RxHandler[i].phyTMDSError[1];
			userdata.tcs_error[i][2] = gHDMI21RxHandler[i].phyTMDSError[2];
			userdata.tcs_error[i][3] = gHDMI21RxHandler[i].phyTMDSError[3];

			userdata.tcs_sync_recover[i][0] = gHDMI21RxHandler[i].phySyncRecovery[0];
			userdata.tcs_sync_recover[i][1] = gHDMI21RxHandler[i].phySyncRecovery[1];
			userdata.tcs_sync_recover[i][2] = gHDMI21RxHandler[i].phySyncRecovery[2];
			userdata.tcs_sync_recover[i][3] = gHDMI21RxHandler[i].phySyncRecovery[3];
		}

		if(isInternalCall > 0){
			memcpy((LX_HDMI_PHY_INFORM_T *)pData, &userdata, sizeof(LX_HDMI_PHY_INFORM_T));
		}
		else{
			/* Step 3. Copy data to user layer */
			ret = copy_to_user((LX_HDMI_PHY_INFORM_T *)pData, &userdata, sizeof(LX_HDMI_PHY_INFORM_T));
			if(ret) {
				HDMI20_ERROR("Copy Error to USER space for [PHY STATUS] data.\n");
				break;
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;

}

int HDMI21_PHY_E60A0_InitiatePhySystemCtrl(UINT8 port)
{
	int ret = RET_ERROR;

	do{
		HDMI20_PHY("[%s] Entered for port[%d]\n", __F__, port);

		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Mem allocate Phy Block #0 SHDW space */
		if((phyReg_e60a0[port].shdw.addr == NULL)){
			phyReg_e60a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_E60A0_T));

		}
		else {
			OS_Free((void *)phyReg_e60a0[port].shdw.addr);
			phyReg_e60a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_E60A0_T));
		}

		/* Mem allocate Phy Block #1 SHDW space */
		if((phyReg_B1_e60a0[port].shdw.addr == NULL)){
			phyReg_B1_e60a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B1_E60A0_T));

		}
		else {
			OS_Free((void *)phyReg_B1_e60a0[port].shdw.addr);
			phyReg_B1_e60a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B1_E60A0_T));
		}

		/* Mem allocate Phy Block #1 SHDW space */
		if((phyReg_B2_e60a0[port].shdw.addr == NULL)){
			phyReg_B2_e60a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B2_E60A0_T));

		}
		else {
			OS_Free((void *)phyReg_B2_e60a0[port].shdw.addr);
			phyReg_B2_e60a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B2_E60A0_T));
		}
	
		ret = RET_OK;
	} while(0);

	return ret;
}



void HDMI21_PHY_E60A0_UpdatePhyLockFlag(UINT8 port)
{
	int tcsDone = 0;
	int updateTcsValue = 0;
	int isTcsStable = 0;
	int isCrDone = 0;
	bool isPhyLocked = false;
	bool wasPhyLocked;
	int tcsError;
	int SyncRecovery;
	int cedError;
	int deltaError;
	int deltaEye;
	int dfeResult;
	int ch0SrSsb = 0;
	int ch1SrSsb = 0;
	int ch2SrSsb = 0;
	int ch3SrSsb = 0;
	UINT32 tcsStateMatchVal = 0;
	UINT32 flt_state = 0;
	UINT32 __attribute__((unused)) frl_start_st = 0;
	UINT32 __attribute__((unused)) frl_start = 0;
	UINT32 __uD;
	HDMI21_SNPS_LINK_REG_0X584_T _r0;


	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(HDMI21_HAL_Rx_Get_IsHpdUp(port) <= 0){
			break;
		}

		if(gHDMI21RxHandler[port].isHPD == false){
			break;
		}

		wasPhyLocked = gHDMI21RxHandler[port].isPhyLocked;

		/* Update Data */
		tcsDone = HDMI21_PHY_E60A0_Check_TCSDone(port);
		
		updateTcsValue = HDMI21_PHY_E60A0_Update_TMDS_TCS_Value(port, 0);
		isCrDone = __HDMI21_PHY_E60A0_Check_CRDone(port);

		tcsError = HDMI21_PHY_E60A0_Check_TMDSError(port);
		SyncRecovery = HDMI21_PHY_E60A0_Check_SyncRecovery(port);
		cedError = HDMI21_PHY_E60A0_Check_CEDError(port);
		deltaError = HDMI21_PHY_E60A0_Check_DeltaError(port);
		deltaEye = HDMI21_PHY_E60A0_Check_DeltaEye(port);
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_UPDATE_PHY_DFE_RESULT].value > 0){
			dfeResult = HDMI21_PHY_E60A0_Check_DfeResult(port);
		}

		/* Check Phy Lock */
		if(tcsDone >= 0){
			/* Update Flag */
			isPhyLocked = true;

			/* Execute any Phy Exception Case */
			if(gHDMI21RxDevPhyControler[HDMI21__PHY_ENABLE_PHY_EXCEPTION_CASE].value > 0){
				__HDMI21_PHY_E60A0_CheckPhyExceptionCase(port, 0);
			}
		}
	}while(0);

	if(port < HDMI21_NUM_OF_PORTS_E60){
		/* Update TCS State History */
		gPhyTcsStateHist[port][gPhyTcsStateHistIdx[port]] = gHDMI21RxHandler[port].phyTCSState;
		/* Increamnet TCS State History Idx */
		__HDMI21_PHY_E60A0_IncreaseTcsStateHistIdx(port);


		if((gHDMI21RxHandler[port].fsm_phy_lock > 0) && (isPhyLocked == false)) {
			HDMI20_PHY("PHY[%d] : === Detected Phy Lock Loss === \n", port);	
			gHDMI21RxHandler[port].fsm_phy_lock = 0;
			gHDMI21RxHandler[port].phyFrlSwWaState = 0;

			/* Reset HDCP2.2 Engine & Start HDCP2.2 Auth  */
			if(gHDMI21RxHandler[port].gWasHDCP22Written > 0) {
				/* HDCP2.2 */
				HDMI21_HDCP23_Module_Set_HlcReset(port, 0);
			}

			/* 2019/12/23 : PS4 Pro HDR */
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value != 521) {
				/* 2019/12/24 : For today.. lets do this only in HDMI2.0 6G mode. Need to spread this to all */
				if(gHDMI21RxHandler[port].phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_6G){
					HDMI21_HAL_Rx_Set_CoreResetWithMask(&gHDMI21RxHandler[port], gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value);
				}
			}
		}
		else if((gHDMI21RxHandler[port].fsm_phy_lock > 0) && (isPhyLocked == true)  \
				&& (gHDMI21RxHandler[port].phyFrlSwWaState == 1) \
				&& (gHDMI21RxHandler[port].phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L))
		{
			/* Incase DFE was not finished when Link Main Thread checked.. */
			HDMI21_PHY_E60A0_CheckDfeDone(port);
		}
		else if((gHDMI21RxHandler[port].fsm_phy_lock > 0) && (isPhyLocked == true)  \
				&& (gHDMI21RxHandler[port].phyFrlSwWaState == 2) &&(gHDMI21RxDevPhyControler[HDMI21__PHY_CH0_SSB_CHECK_ON].value > 0 )\
				&& (gHDMI21RxHandler[port].phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L))
		{

			if((gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_3].value & 0x1) != 0) { 

				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_47);
				PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_47, ch0_sr_ssb, ch0SrSsb);
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_48);
				PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_48, ch1_sr_ssb, ch1SrSsb);
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_49);
				PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_49, ch2_sr_ssb, ch2SrSsb);
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_4a);
				PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_4a, ch3_sr_ssb, ch3SrSsb);
			}
			else {
				ch0SrSsb = 0x10;
			}

			if((gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_3].value & 0x2) != 0) { 
				/* Get FLT_UPDATE from SNPS Link */
				__uD = gHDMI21RxHandler[port].link_read(0x588);	memcpy((void *)&_r0, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X584_T));
			}
			else {
				_r0.SCDC_FRL_START = 0;
				_r0.FRL_START_STS = 1;
			}


			if((ch0SrSsb == 0x10) && ((_r0.SCDC_FRL_START == 0) && (_r0.FRL_START_STS == 1))) {
				HDMI20_PHY("PHY[%d] : FRL Mode detected Ch0SrSsb[0x%x] Match of [0x10]. [0x%x][0x%x][0x%x][0x%x]. State[%d]StartSTS[%d]\n",\
						port, ch0SrSsb, ch0SrSsb, ch1SrSsb, ch2SrSsb, ch3SrSsb, _r0.SCDC_FRL_START, _r0.FRL_START_STS);

				gHDMI21RxHandler[port].phyFrlSwWaState = 3;
				HDMI21_HAL_Rx_Set_CoreResetWithMask(&gHDMI21RxHandler[port], gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value);
			}
			else {
				HDMI21_LINE_DBG(434, "DBG[%d] : FRL Mode Checking Ch0SrSsb, but Ch0SrSsb value[0x%x] is not [0x10]. [0x%x][0x%x][0x%x][0x%x]\n",\
						port, ch0SrSsb, ch0SrSsb, ch1SrSsb, ch2SrSsb, ch3SrSsb);
			}
		}
		else if(isPhyLocked == false)
		{
			/* Only in FRL Modes */
			if(gHDMI21RxHandler[port].phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
				/* Check TCS State History */
				tcsStateMatchVal = __HDMI21_PHY_E60A0_CheckTcsStateHistMatchVal(port, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_STATE_HIST_MATCH].value);

				/* Get FLT_UPDATE from SNPS Link */
				__uD = gHDMI21RxHandler[port].link_read(0x588);	memcpy((void *)&_r0, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X584_T));

				HDMI21_LINE_DBG(595, "DBG[%d] : Match Count[%d] FLT_UPDATE[%d] FRL_Start_ST[%d] FRL_Start[%d]\n",\
						port, tcsStateMatchVal, _r0.SCDC_FLT_UPDATE, _r0.FRL_START_STS , _r0.SCDC_FRL_START);

				if((tcsStateMatchVal == gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_STATE_HIST_DEPTH].value)&&(_r0.SCDC_FLT_UPDATE == 0)){
					PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_59);
					PHY_REG_B2_E60A0_Rd01(port, hdmi_phy_addr_59, flt_state, flt_state);
	
					HDMI21_LINE_DBG(595, "PHY[%d] : TCS State[%d] is Stuck [%d] times. Current FLT_State val [%d]. FLT_UPDATE[%d]\n", port,\
							gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_STATE_HIST_MATCH].value, tcsStateMatchVal, flt_state, _r0.SCDC_FLT_UPDATE);

					if(flt_state == gHDMI21RxDevPhyControler[HDMI21__PHY_FLT_STATE_MATCH].value) {
						if((gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_1].value & 0x1) != 0x0) {
							PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_59);
							PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x8);
							PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5a);
							
							HDMI21_LINE_DBG(595, "PHY[%d]  : FLT State[%d] in TCS State stuck case. Execute #1. EQ Sucess Sel [8]->[7]\n", port, flt_state);

							PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_59);
							PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x7);
							PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5a);
						}

						if((gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_1].value & 0x2) != 0x0) {
							HDMI21_LINE_DBG(595, "PHY[%d]  : FLT State[%d] in TCS State stuck case. Execute #2. Toggle DR RESETB\n", port, flt_state);
							__HDMI21_PHY_E60A0_ToggleDrResetB(port, 1);
							__HDMI21_PHY_E60A0_ToggleDrResetB(port, 0);
						}

						if((gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_1].value & 0x4) != 0x0) {
							HDMI21_LINE_DBG(595, "PHY[%d]  : FLT State[%d] in TCS State stuck case. Execute #3. Toggle CR MODE SEL RESETB\n", port, flt_state);
							__HDMI21_PHY_E60A0_ToggleCrModeSelResetB(port, 1);
							__HDMI21_PHY_E60A0_ToggleCrModeSelResetB(port, 0);
						}
					}
					else {
						if(_r0.FRL_START_STS == 0) {
							HDMI21_LINE_DBG(595, "PHY[%d]  : [1]-NO. FLT_STATE not [1]. FRL_START_STS is not [1]. Current STS[%d]\n", port, _r0.FRL_START_STS);
							
							/* Set FRL_START Manual ON */
							__uD = gHDMI21RxHandler[port].link_read(0x584); 
							__uD |= (0x1);
							gHDMI21RxHandler[port].link_write(0x584, __uD);

							/* Set Idx to 0 */
							gPhyFrlFrlStartManualIdx[port] = 0;
						}
						else {
							HDMI21_LINE_DBG(595, "PHY[%d]  : [1]-YES. FLT_STATE is [1]. Current FRL_START_STS [%d]\n", port, _r0.FRL_START_STS);

							if(_r0.SCDC_FRL_START == 0) {
								HDMI21_LINE_DBG(595, "PHY[%d]  : [2]-NO FRL_Start [%d]. Current Cnt[%d]\n", port, _r0.SCDC_FRL_START, 	gPhyFrlFrlStartManualIdx[port]);

								if(gPhyFrlFrlStartManualIdx[port] >= gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_2].value) {
									HDMI21_LINE_DBG(595, "PHY[%d]  : [3]-YES Cnt[%d] reached thres[%d]. Execute FLT Restart\n", port, gPhyFrlFrlStartManualIdx[port], gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_2].value);

									PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_99);
									PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, 0);
									PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_99);

									PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_66);
									PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_66,  flt_restart, 0x1);
									PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_66);

									HDMI21_LINE_DBG(595, "PHY[%d] : Send FLT Restart!\n", port);

									PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_66);
									PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_66,  flt_restart, 0x0);
									PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_66);

									HDMI21_PHY_E60A0_ToggleTCSEn(port, 0);
									HDMI21_PHY_E60A0_ToggleTCSEn(port, 1);


									/* Reset Hist Counter */
									memset((void *)&gPhyTcsStateHist[port], 0xF, sizeof(UINT32) * HDMI21_PHY_TCS_HIST_HISTORY_DEPTH);
								}

								/* Incr Counter */
								gPhyFrlFrlStartManualIdx[port]++;
							}
							else {
								HDMI21_LINE_DBG(595, "PHY[%d]  : [2]-YES FRL_Start [%d]\n", port, _r0.SCDC_FRL_START);
								/* Do Nothing */
							}
						}
					}
				}
			}
		}

		gHDMI21RxHandler[port].isPhyLocked = isPhyLocked;
	}

	/* Reset Phy Exception case history when PHY LOCK is toggled to FALSE */
	if(gHDMI21RxDevPhyControler[HDMI21__PHY_ENABLE_PHY_EXCEPTION_CASE].value > 0){
		if(port < HDMI21_NUM_OF_PORTS_E60){
			if( gHDMI21RxHandler[port].isPhyLocked != true ){
				__HDMI21_PHY_E60A0_CheckPhyExceptionCase(port, 1);
			}
		}
	}

	/* DBG PRINT */
	HDMI21_LINE_DBG(4242, "DBG %d : tcsDone[%d] / updateTcsValue[%d] / isTcsStable[%d]\n", port, tcsDone,updateTcsValue,isTcsStable);

	return;
}


/* IOCTL */
int HDMI21_PHY_E60A0_Rx_AccessPhy(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size)
{
	int ret = RET_ERROR;

	LX_HDMI20_PHY_ACCESS_T data;

	do{
		if(gHDMI21RxHandler[port].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		if(pPhyCtrl == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI20_PHY_ACCESS_T) ){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_PHY_ACCESS_T) , size);
			break;
		}

		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		memset((void *)&data, 0, sizeof(LX_HDMI20_PHY_ACCESS_T));

		if( copy_from_user(&data, (void __user *)pPhyCtrl, sizeof(LX_HDMI20_PHY_ACCESS_T))){
			HDMI20_ERROR("Cannot copy HDMI20 phy data structure from user\n");
			break;
		}

		if(data.regBank == 2){
			if(data.isWrite){
				gHDMI21RxHandler[port].phyDR_write( (data.regAddr << 2) + 0x400, data.data);
			}
			else{
				data.data = gHDMI21RxHandler[port].phyDR_read( (data.regAddr << 2) + 0x400);
			}

		}
		else if(data.regBank == 1){
			if(data.isWrite){
				gHDMI21RxHandler[port].phyDR_write( (data.regAddr << 2), data.data);
			}
			else{
				data.data = gHDMI21RxHandler[port].phyDR_read( (data.regAddr << 2));
			}

		}
		else{
			if(data.isWrite){
				gHDMI21RxHandler[port].phyPDC_write( (data.regAddr << 2), data.data);
			}
			else{
				data.data = gHDMI21RxHandler[port].phyPDC_read( (data.regAddr << 2));
			}
		}

		ret = copy_to_user((LX_HDMI20_PHY_ACCESS_T *)pPhyCtrl, (void *)&data, sizeof(LX_HDMI20_PHY_ACCESS_T));
		if(ret) {
			HDMI20_ERROR("Copy Error to USER space for [%s] data on Port[%d].\n", "PHY" ,port);
			break;
		}


		ret = RET_OK;
	} while(0);

	return ret;
}



int HDMI21_PHY_E60A0_Set_3G6G_Mode(UINT8 port, UINT8 isAuto, HDMI21_HAL_PHY_INITIATED_MODE_T mode, UINT8 isScrambling, UINT8 lowfreqGain)
{
	int ret = RET_ERROR;
	int wasEQmodeChanged = 0;
	UINT32 flt_state = 0;
	int isOnboard = 0;
	UINT32 __tcsManVal[4];
	UINT32 __frlRsGain[4];

	/* Get FRL_NO_RETRAIN */
	UINT32 __uD;
	HDMI21_SNPS_LINK_REG_0X58C_T _r2;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Read FRL No Retrain : 0x58C on O20A0, 0x590 on E60A0 */
		__uD = gHDMI21RxHandler[port].link_read(0x590);	memcpy((void *)&_r2, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X58C_T));
		if(_r2.SCDC_FLT_NO_RETRAIN == 0) { gHDMI21RxHandler[port].isPhyFrlCtsMode = 0; }
		else 							 { gHDMI21RxHandler[port].isPhyFrlCtsMode = 1; }

		/* Override CTS mode, when debugger is set */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_FORCE_FRL_CTS_MODE].value == 2) {
			gHDMI21RxHandler[port].isPhyFrlCtsMode = 1;
		}
		else if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_FORCE_FRL_CTS_MODE].value == 0) {
			gHDMI21RxHandler[port].isPhyFrlCtsMode = 0;
		}

		/* JANG SILVER LIGHT TOLD me to set current to max on CTS Mode : 2019/11/04 */
		if(gHDMI21RxHandler[port].isPhyFrlCtsMode > 0) {
			PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_6f);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6f, ctrl_rbias, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_RBIAS_CTS_MODE].value);
			PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_6f);
		}
		else {
			PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_6f);
			/* HW Default Val is 0x6F */
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6f, ctrl_rbias, 0xF); 
			PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_6f);
		}

		/* Re-Insert Manual EQ value because we need to set this back due to DFE Center SWWA */
		/* Check for Manual EQ */
		if ( port == 4 )     { 
			__tcsManVal[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH0].value;
			__tcsManVal[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH1].value;
			__tcsManVal[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH2].value;
			__tcsManVal[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH3].value;
		}
		else if ( port == 3 )     { 
			__tcsManVal[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH0].value;
			__tcsManVal[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH1].value;
			__tcsManVal[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH2].value;
			__tcsManVal[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH3].value;
		}
		else if ( port == 2) { 
			__tcsManVal[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH0].value;
			__tcsManVal[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH1].value;
			__tcsManVal[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH2].value;
			__tcsManVal[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH3].value;
		}
		else if ( port == 1) { 
			__tcsManVal[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH0].value;
			__tcsManVal[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH1].value;
			__tcsManVal[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH2].value;
			__tcsManVal[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH3].value;
		}
		else { 
			__tcsManVal[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH0].value;
			__tcsManVal[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH1].value;
			__tcsManVal[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH2].value;
			__tcsManVal[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH3].value;
		}

		/* Just Incase : Scramble EN or HDMI1.4 came after FRL mode, and main thread could not detected the changes..*/
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_60);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_60, flt_ready_man, 0x0);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_60, flt_ready_man_mode, 0x0);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_60);

		/* EQ_CS_MAN_CH */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a2);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a2, eq_cs_man_ch0, __tcsManVal[0]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a2);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a3);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a3, eq_cs_man_ch1, __tcsManVal[1]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a3);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a4);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a4, eq_cs_man_ch2, __tcsManVal[2]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a4);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a5);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a5, eq_cs_man_ch3, __tcsManVal[3]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a5);

		/* End of Manual EQ value setting */

		/* Clear Phy Exception case history */
		if(gHDMI21RxDevPhyControler[HDMI21__PHY_ENABLE_PHY_EXCEPTION_CASE].value > 0){
			__HDMI21_PHY_E60A0_CheckPhyExceptionCase(port, 1);
		}

		/* Check if this port is Onboard port */
		isOnboard = __HDMI21_PHY_E60A0_IsOnboardPort(port);


		HDMI20_PHY("PHY[%d][Onboard:%d] : Set PhyMode=>Sel[%s]/Mode[%s]/isScrambling[%d]/RSGain[0x%x]\n",\
				port, isOnboard,isAuto?"Auto":"Manual", phymode_type_to_str(mode), isScrambling, lowfreqGain);
		
		/* Check 3G/6G change */
		if(gHDMI21RxHandler[port].phyInitiatedMode != mode){
			HDMI20_PHY("PHY[%d] : Mode change. Prev[%s]->Current[%s]\n", port, phymode_type_to_str(gHDMI21RxHandler[port].phyInitiatedMode),\
					phymode_type_to_str(mode));	
			wasEQmodeChanged = 1;
		}
		else{
			if(mode == HDMI21_HAL_PHY_INITIATED_3G){
				wasEQmodeChanged = 1;
			}
			else {
				HDMI20_PHY("PHY[%d] : Discard Phy mode set on non-different case[%s]\n", port, phymode_type_to_str(mode));
				break;
			}
		}

		/* DFE Center SW WA */
		gHDMI21RxHandler[port].phyFrlSwWaState = 0;

		/* Flag for 3G/6G */
		gHDMI21RxHandler[port].phyInitiatedMode = mode;

		/* 0x28:0x23 = EQ_HDMI20_VAL
		 * 0x28:0x2A = Manual HDMI20_MODE
		 * 0x28:0x26 = Manual HDMI21_MODE
		 * 0x48:0x88 = SCR_MAN_OFF 
		 * 0x38:0xB8 = TCS_ERROR_SEL			*/
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_ad);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a8);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_23);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_2a);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_26);
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_88);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_b8);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_70);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_73);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_b7);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_8a);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_5a);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_93);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_92);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_39);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_24);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_59);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_f4);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_9a);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_98);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_76);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_b4);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_b5);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_b6);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_41);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_5c);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_5d);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_5e);
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_59);
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_66);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_f3);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_58);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_bc);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_5f);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_99);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_89);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_ac);
	

		if(isAuto)	{PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_2a, cr_i2c_hdmi20_mode, 0x0);}
		else 		{PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_2a, cr_i2c_hdmi20_mode, 0x1);}


		if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_12G_4L) {
			/* 2019/06/26 : Jinwoo told me to have this set(48:59) on the very top of all settings */
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_59,flt_man_mode, 0x0);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_66,flt_update_man_mode, 0x0);
			HDMI21_PHY_E60A0_ToggleTCSEn(port, 0);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, 0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ad, chk_infinite_mode, 0x1, chk_limit, 0xF);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5a,\
					ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_FRL_TYPE3].value,\
					cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_FRL_TYPE3].value );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_SCAN2_MODE].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_8a, delta_scan_man_mode, 0x0, delta_scan_man, 0x0);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_2a, cr_man_hdmi20, 0x0);
			PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_26, cr_man_hdmi21, 0x1, cr_i2c_hdmi21_mode, 0x1 );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE3].value);
			PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_88, scr_man_mode, 0x1, scr_man_val, 0x1);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_73, idr_adj, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_IDR_ADJ_FRL_TYPE3].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_39, eq_dohg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DOHG_FRL_TYPE3].value);
			if(isOnboard > 0) {
				PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24,eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_EQICTRL_FRL_TYPE3_ONBOARD].value);
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE3_ONBOARD].value \
						, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_FRL_TYPE3].value);
				PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL12G_ONB].value);
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_70, \
						ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE3_ONBOARD].value,\
						ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE3].value);
				PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a8, eq_dhfg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DHFG_FRL_TYPE3_ONB].value);
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_23, eq_hdmi20_val, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE3_OB].value,\
						eq_hdmi20_man, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE3].value);

				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
						tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL12G_CTS].value,\
						tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);
			}
			else {
				if(gHDMI21RxHandler[port].isPhyFrlCtsMode > 0) {
					PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24,eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_CTS_TYPE3].value);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL12G_CTS].value);

					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
							tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL12G_CTS].value,\
							tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);
				}
				else {
					PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24,eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_FRL_TYPE3].value);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL12G].value);

					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
							tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL12G].value,\
							tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);
				}
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE3].value \
						, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_FRL_TYPE3].value);

				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_70, \
						ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE3].value,\
						ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE3].value);
				PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a8, eq_dhfg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DHFG_FRL_TYPE3].value);
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_23, eq_hdmi20_val, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE3].value,\
						eq_hdmi20_man, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE3].value);

			}
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_f4, g2_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_G2_SEL_FRL_TYPE3].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_9a, delta_scope2_pll3, 0x0, delta_scope2_pll2, 0x1);
			if(gHDMI21RxHandler[port].isPhyFrlCtsMode > 0) {
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x0,\
						delta_max_adjust, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_CTS_TYPE3].value);
			}
			else {
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x0,\
						delta_max_adjust, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_FRL_TYPE3].value);
			}
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b4, reg_tcs_man_pre , 0xFF);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b5, reg_tcs_man_mea_14_8, 0xA);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b6, reg_tcs_man_mea_7_0, 0xD2);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_41, pi_set_man_mode, 0x1);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c,\
					dfe_a_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_A_ON_FRL_TYPE2].value,\
					dfe_b1_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B1_ON_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c,\
					dfe_b2_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B2_ON_FRL_TYPE2].value,\
					dfe_b3_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B3_ON_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c,\
					dfe_b4_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B4_ON_FRL_TYPE2].value,\
					dfe_b5_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B5_ON_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5d,\
					dfe_n1, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N1_FRL_TYPE3].value,\
					dfe_n2_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N2_FRL_TYPE3].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5d, dfe_n2, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N2_ON_FRL_TYPE3].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5e, dfe_updn_period, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PERIOD_FRL_TYPE3].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_f3, filter_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_FILTER_SEL_FRL_TYPE3].value,\
					g1_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_G1_SEL_FRL_TYPE3].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, 0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_bc,\
					adaptive_period, gHDMI21RxDevPhyControler[HDMI21__PHY_ADAPTIVE_PERIOD_6G_FRL].value,\
					adaptive_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ADAPTIVE_PERIOD_SEL_6G_FRL].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5f, dfe_updn_period_pre, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PRE_FRL_TYPE3].value);
		
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_val, 0x0 );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_mode, 0x0 );

			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ac, ced_open_length, gHDMI21RxDevPhyControler[HDMI21__PHY_CED_OPEN_LENGTH_FRL].value, \
					tmds_open_length, gHDMI21RxDevPhyControler[HDMI21__PHY_TMDS_OPEN_LENGTH].value);
		}
		else if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
			/* 2019/12/09 : Crow.Kim */
			__HDMI21_PHY_E60A0_SetI2cManualDFEBxValue(port);

			/* 2019/06/26 : Jinwoo told me to have this set(48:59) on the very top of all settings */
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_59,flt_man_mode, 0x0);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_66,flt_update_man_mode, 0x0);
			HDMI21_PHY_E60A0_ToggleTCSEn(port, 0);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, 0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ad, chk_infinite_mode, 0x1, chk_limit, 0xF);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5a,\
					ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_FRL_TYPE2].value,\
					cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_FRL_TYPE2].value );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_SCAN2_MODE].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_8a, delta_scan_man_mode, 0x0, delta_scan_man, 0x0);
			PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_23, eq_hdmi20_val, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE2].value,\
					eq_hdmi20_man, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE2].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_2a, cr_man_hdmi20, 0x0);
			PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_26, cr_man_hdmi21, 0x1, cr_i2c_hdmi21_mode, 0x1 );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE2].value);
			PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_88, scr_man_mode, 0x1, scr_man_val, 0x1);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_73, idr_adj, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_IDR_ADJ_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_39, eq_dohg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DOHG_FRL_TYPE2].value);
			if(isOnboard > 0) {
				PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24,eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_EQICTRL_FRL_TYPE2_ONBOARD].value);
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE2_ONBOARD].value \
						, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_FRL_TYPE2].value);
				PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL10G_ONB].value);
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_70, \
						ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE2_ONBOARD].value,\
						ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE2].value);

				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
						tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL_CTS].value,\
						tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);
			}
			else {
				if(gHDMI21RxHandler[port].isPhyFrlCtsMode > 0) {
					PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24,eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_CTS_TYPE2].value);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL10G_CTS].value);

					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
							tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL_CTS].value,\
							tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);
				}
				else {
					PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24,eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_FRL_TYPE2].value);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL10G].value);
				
					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
							tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL].value,\
							tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);
				}
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE2].value \
						, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_FRL_TYPE2].value);
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_70, \
						ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE2].value,\
						ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE2].value);
			}
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_f4, g2_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_G2_SEL_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_9a, delta_scope2_pll3, 0x0, delta_scope2_pll2, 0x1);
			if(gHDMI21RxHandler[port].isPhyFrlCtsMode > 0) {
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x0,\
						delta_max_adjust, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_CTS_TYPE2].value);
			}
			else{
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x0,\
						delta_max_adjust, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_FRL_TYPE2].value);
			}
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b4, reg_tcs_man_pre , 0xFF);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b5, reg_tcs_man_mea_14_8, 0xA);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b6, reg_tcs_man_mea_7_0, 0xD2);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_41, pi_set_man_mode, 0x1);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c,\
					dfe_a_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_A_ON_FRL_TYPE2].value,\
					dfe_b1_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B1_ON_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c,\
					dfe_b2_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B2_ON_FRL_TYPE2].value,\
					dfe_b3_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B3_ON_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c,\
					dfe_b4_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B4_ON_FRL_TYPE2].value,\
					dfe_b5_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B5_ON_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5d,\
					dfe_n1, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N1_FRL_TYPE2].value,\
					dfe_n2_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N2_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5d, dfe_n2, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N2_ON_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5e, dfe_updn_period, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PERIOD_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a8, eq_dhfg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DHFG_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_f3, filter_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_FILTER_SEL_FRL_TYPE2].value,\
					g1_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_G1_SEL_FRL_TYPE2].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, 0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_bc,\
					adaptive_period, gHDMI21RxDevPhyControler[HDMI21__PHY_ADAPTIVE_PERIOD_6G_FRL].value,\
					adaptive_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ADAPTIVE_PERIOD_SEL_6G_FRL].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5f, dfe_updn_period_pre, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PRE_FRL_TYPE2].value);
		
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_val, 0x0 );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_mode, 0x0 );

			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ac, ced_open_length, gHDMI21RxDevPhyControler[HDMI21__PHY_CED_OPEN_LENGTH_FRL].value, \
					tmds_open_length, gHDMI21RxDevPhyControler[HDMI21__PHY_TMDS_OPEN_LENGTH].value);

		}
		else if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
			/* 2019/06/26 : Jinwoo told me to have this set(48:59) on the very top of all settings */
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_59,flt_man_mode, 0x0);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_66,flt_update_man_mode, 0x0);
			HDMI21_PHY_E60A0_ToggleTCSEn(port, 0);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, 0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ad, chk_infinite_mode, 0x1, chk_limit, 0xF);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5a,\
					ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_FRL_TYPE1].value,\
					cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_FRL_TYPE1].value );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_SCAN2_MODE].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_8a, delta_scan_man_mode, 0x0, delta_scan_man, 0x0);
			PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_23, eq_hdmi20_val, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE1].value,\
					eq_hdmi20_man, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE1].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_2a, cr_man_hdmi20, 0x0);
			PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_26, cr_man_hdmi21, 0x1, cr_i2c_hdmi21_mode, 0x1 );
		
			PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_88, scr_man_mode, 0x1, scr_man_val, 0x1);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_73, idr_adj, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_IDR_ADJ_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL3G].value);

			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_39, eq_dohg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DOHG_FRL_TYPE1].value);
			if(isOnboard > 0) {
				PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24, eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_EQICTRL_FRL_TYPE1_ONBOARD].value);
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE1_ONBOARD].value \
						, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_FRL_TYPE1].value);
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_70, \
						ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE1_ONBOARD].value,\
						ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE1].value);

			}
			else {
				PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24, eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_FRL_TYPE1].value);
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE1].value \
						, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_FRL_TYPE1].value);
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_70, \
						ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE1].value,\
						ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE1].value);
			}
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_f4, g2_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_G2_SEL_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_9a, delta_scope2_pll3, 0x0, delta_scope2_pll2, 0x1);
			if(gHDMI21RxHandler[port].isPhyFrlCtsMode > 0) {
				if(mode == HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
							tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL3G_CTS].value,\
							tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);
				}
				else {
					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
							tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL_CTS].value,\
							tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);
				}

				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x0,\
						delta_max_adjust, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_CTS_TYPE1].value);
			}
			else{
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
						tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL].value,\
						tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);

				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x0,\
						delta_max_adjust, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_FRL_TYPE1].value);
			}
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b4, reg_tcs_man_pre , 0xFF);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b5, reg_tcs_man_mea_14_8, 0xA);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b6, reg_tcs_man_mea_7_0, 0xD2);
			
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c,\
					dfe_a_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_A_ON_FRL_TYPE1].value,\
					dfe_b1_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B1_ON_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c,\
					dfe_b2_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B2_ON_FRL_TYPE1].value,\
					dfe_b3_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B3_ON_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c,\
					dfe_b4_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B4_ON_FRL_TYPE1].value,\
					dfe_b5_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_B5_ON_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5d,\
					dfe_n1, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N1_FRL_TYPE1].value,\
					dfe_n2_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N2_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5d, dfe_n2, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N2_ON_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5e, dfe_updn_period, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PERIOD_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a8, eq_dhfg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DHFG_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_f3, filter_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_FILTER_SEL_FRL_TYPE1].value,\
					g1_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_G1_SEL_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, 0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_bc,\
					adaptive_period, gHDMI21RxDevPhyControler[HDMI21__PHY_ADAPTIVE_PERIOD_6G_FRL].value,\
					adaptive_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ADAPTIVE_PERIOD_SEL_6G_FRL].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5f, dfe_updn_period_pre, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PRE_FRL_TYPE1].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ac, ced_open_length, gHDMI21RxDevPhyControler[HDMI21__PHY_CED_OPEN_LENGTH_FRL].value, \
					tmds_open_length, gHDMI21RxDevPhyControler[HDMI21__PHY_TMDS_OPEN_LENGTH].value);

			if(mode == HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
				PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_41, pi_set_man_mode, 0x0);
				PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_val, 0x1 );
				PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_mode, 0x1 );
				PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_FRL_3G].value);
			}
			else {
				PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_41, pi_set_man_mode, 0x1);
				PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_val, 0x0 );
				PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_mode, 0x0 );
				PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE1].value);
			}
		}
		else if(mode ==  HDMI21_HAL_PHY_INITIATED_6G) {
			/* 2019/06/26 : Jinwoo told me to have this set(48:59) on the very top of all settings */
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_AUTO_PLL_3].value);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_59,flt_man_mode, 0x0);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_66,flt_update_man_mode, 0x1);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ad, chk_infinite_mode, 0x1, chk_limit, 0xF);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5a,\
					ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_6G].value,\
					cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_6G].value );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_SCAN2_MODE].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_8a, delta_scan_man_mode, 0x0, delta_scan_man, 0x0);
			PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_23, eq_hdmi20_val, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_6G].value,\
					eq_hdmi20_man, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_6G].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_2a, cr_man_hdmi20, 0x1);
			PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_26, cr_man_hdmi21, 0x0, cr_i2c_hdmi21_mode, 0x1 );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_6G].value);
			PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_88, scr_man_mode, 0x1, scr_man_val, 0x1);
			if(isOnboard > 0) {
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_70, \
						ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_6G_ONBOARD].value,\
						ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_6G].value);
			}
			else {
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_70, \
						ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_6G].value,\
						ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_6G].value);
			}
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_73, idr_adj, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_IDR_ADJ_6G].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_TMDS6G].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
					tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_TMDS].value,\
					tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_TMDS].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_39, eq_dohg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DOHG_6G].value);
			if(isOnboard > 0) {
				PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24, eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_EQICTRL_6G_ONBOARD].value);
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_6G_ONBOARD].value \
						, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_6G].value);
			}
			else {
				PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24, eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_6G].value);
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_6G].value \
						, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_6G].value);
			}
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_f4, g2_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_G2_SEL_6G].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_9a, delta_scope2_pll3, 0x1, delta_scope2_pll2, 0x1);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x3,\
					delta_max_adjust, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_6G].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b4, reg_tcs_man_pre , 0x60);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b5, reg_tcs_man_mea_14_8, 0x0);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b6, reg_tcs_man_mea_7_0, 0xA);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_41, pi_set_man_mode, 0x1);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c, dfe_a_on, 0x1, dfe_b1_on, 0x1);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c, dfe_b2_on, 0x0, dfe_b3_on, 0x0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c, dfe_b4_on, 0x0, dfe_b5_on, 0x0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5d,\
					dfe_n1, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N1_6G].value,\
					dfe_n2_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N2_6G].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5d, dfe_n2, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N2_ON_6G].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5e, dfe_updn_period, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PERIOD_3G].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a8, eq_dhfg, 0x0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_f3, filter_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_FILTER_SEL_6G].value,\
					g1_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_G1_SEL_6G].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_DIG_ON].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_bc,\
					adaptive_period, gHDMI21RxDevPhyControler[HDMI21__PHY_ADAPTIVE_PERIOD_6G_FRL].value,\
					adaptive_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ADAPTIVE_PERIOD_SEL_6G_FRL].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5f, dfe_updn_period_pre, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PRE_6G].value);
		
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_val, 0x0 );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_mode, 0x0 );

			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ac, ced_open_length, gHDMI21RxDevPhyControler[HDMI21__PHY_CED_OPEN_LENGTH_TMDS].value, \
					tmds_open_length, gHDMI21RxDevPhyControler[HDMI21__PHY_TMDS_OPEN_LENGTH].value);
		}
		else {
			/* 2019/06/26 : Jinwoo told me to have this set(48:59) on the very top of all settings */
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_AUTO_PLL_3].value);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_59,flt_man_mode, 0x0);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_66,flt_update_man_mode, 0x1);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ad, chk_infinite_mode, 0x1, chk_limit, 0xF);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5a,\
					ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_MODE_2_0].value,\
					cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_MODE_2_0].value );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_SCAN2_MODE].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_8a, delta_scan_man_mode, 0x0, delta_scan_man, 0x0);
			PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_23, eq_hdmi20_val, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_3G].value,\
					eq_hdmi20_man, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_3G].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_2a, cr_man_hdmi20, 0x0);
			PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_26, cr_man_hdmi21, 0x0, cr_i2c_hdmi21_mode, 0x1 );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_3G].value);
			PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_88, scr_man_mode, 0x1, scr_man_val, 0x0);
			if(isOnboard > 0) {
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_70, \
						ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_3G_ONBOARD].value,\
						ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_3G].value);
			}
			else {
				PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_70, \
						ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_3G].value,\
						ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_3G].value);
			}
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_73, idr_adj, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_IDR_ADJ_3G].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_TMDS3G].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b7, \
					tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_TMDS].value,\
					tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_TMDS].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_39, eq_dohg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DOHG_3G].value);
			if(isOnboard > 0) {
				PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24, eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_EQICTRL_3G_ONBOARD].value);
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_3G_ONBOARD].value \
						, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_3G].value);
			}
			else {
				PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_24, eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_3G].value);
				PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_3G].value \
						, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_3G].value);
			}
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_f4, g2_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_G2_SEL_3G].value);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_9a, delta_scope2_pll3, 0x1, delta_scope2_pll2, 0x1);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x3,\
					delta_max_adjust, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_M_AD_3G].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b4, reg_tcs_man_pre , 0x60);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b5, reg_tcs_man_mea_14_8, 0x0);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b6, reg_tcs_man_mea_7_0, 0xA);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_41, pi_set_man_mode, 0x0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c, dfe_a_on, 0x1, dfe_b1_on, 0x1);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c, dfe_b2_on, 0x0, dfe_b3_on, 0x0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5c, dfe_b4_on, 0x0, dfe_b5_on, 0x0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5d,\
					dfe_n1, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N1_3G].value,\
					dfe_n2_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N2_3G].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5d, dfe_n2, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_N2_ON_3G].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5e, dfe_updn_period, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PERIOD_3G].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a8, eq_dhfg, 0x0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_f3, filter_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_FILTER_SEL_3G].value,\
					g1_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_G1_SEL_3G].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, 0);
			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_bc,\
					adaptive_period, gHDMI21RxDevPhyControler[HDMI21__PHY_ADAPTIVE_PERIOD_3GTMDS].value,\
					adaptive_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ADAPTIVE_PERIOD_SEL_3GTMDS].value);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_5f, dfe_updn_period_pre, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_UPDN_PRE_3G].value);
		
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_val, 0x1 );
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_mode, 0x1 );

			PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ac, ced_open_length, gHDMI21RxDevPhyControler[HDMI21__PHY_CED_OPEN_LENGTH_TMDS].value, \
					tmds_open_length, gHDMI21RxDevPhyControler[HDMI21__PHY_TMDS_OPEN_LENGTH].value);
		}

		/* 2019/06/26 : Jinwoo told me to have this set(48:59) on the very top of all settings */
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_99);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_59);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_66);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_5e);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_ad);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_5d);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_5c);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_8a);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_b7);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_92);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_73);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_70);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_23);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_2a);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_26);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_88);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_b8);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_5a);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_93);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_39);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_24);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_59);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_f4);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_9a);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_98);	
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_76);	
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_b4);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_b5);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_b6);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a8);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_41);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_f3);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_58);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_bc);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_5f);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_89);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_ac);

		/* 0x5D : EQ_RS_MAN */
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_16);
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_17);
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_18);
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_19);

		if((gHDMI21RxHandler[port].isPhyFrlCtsMode > 0)&&(mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L)&&(isOnboard == 0)) {
			if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_12G_4L) {
				__frlRsGain[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH0].value;
				__frlRsGain[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH1].value;
				__frlRsGain[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH2].value;
				__frlRsGain[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE3_CH3].value;
			}
			else if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
				__frlRsGain[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH0].value;
				__frlRsGain[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH1].value;
				__frlRsGain[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH2].value;
				__frlRsGain[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE2_CH3].value;
			}
			else {
				__frlRsGain[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE1_CH0].value;
				__frlRsGain[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE1_CH1].value;
				__frlRsGain[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE1_CH2].value;
				__frlRsGain[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_CTS_TYPE1_CH3].value;
			}
		
			HDMI20_PHY("PHY[%d]: CTS Mode[%s] for RSGain[0x%x][0x%x][0x%x][0x%x]\n",\
					port, phymode_type_to_str(mode), __frlRsGain[0], __frlRsGain[1], __frlRsGain[2], __frlRsGain[3]);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_16, eq_rs_man_ch0, __frlRsGain[0]);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_17, eq_rs_man_ch1, __frlRsGain[1]);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_18, eq_rs_man_ch2, __frlRsGain[2]);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_19, eq_rs_man_ch3, __frlRsGain[3]);

		}
		else {
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_16, eq_rs_man_ch0, lowfreqGain);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_17, eq_rs_man_ch1, lowfreqGain);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_18, eq_rs_man_ch2, lowfreqGain);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_19, eq_rs_man_ch3, lowfreqGain);
		}

		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_16);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_17);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_18);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_19);

		/* 0x39 : EQ_CAL_MODE_VAL 0->1 : Redo EQ offset calibration when lowfreqGain(RS) value changes */
		if(wasEQmodeChanged){
			HDMI21_PHY_E60A0_Reset_EqOffsetCalibration(port, 1, __L__);
			HDMI21_PHY_E60A0_Reset_EqOffsetCalibration(port, 0, __L__);
		}

		if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
			PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_59);
			PHY_REG_B2_E60A0_Rd01(port, hdmi_phy_addr_59, flt_state, flt_state);

			PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_59);
			PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x7);
			PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5a);

			HDMI20_PHY("PHY[%d][%s] : FLT State val[0x%x]. Set eq_success_sel to [0x7]\n", port, phymode_type_to_str(mode), flt_state);

			HDMI21_PHY_E60A0_ToggleTCSEn(port, 1);
		}

		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_4b);
		if(mode ==  HDMI21_HAL_PHY_INITIATED_6G){
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_val, 0x3);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_mode, 0x1);	
		}
		else{
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_val, 0x0);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_mode, 0x0);	
		}
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_4b);
		#if 0
		/* 2016/07/21 : Audio Issue for 6G */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_3c);
		if(is6G){
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_3c, pll_aud_man_val, 0x3);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_3c, pll_aud_man_mode, 0x1);	
		}
		else{
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_3c, pll_aud_man_val, 0x0);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_3c, pll_aud_man_mode, 0x0);	
		}
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_3c);
		#endif
		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI21_PHY_E60A0_IsPhyPdbPowerOn(UINT8 port)
{
	UINT32 data;
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Phy PDB Control */
		data = gHDMI21RxHandler[port].top_read(HDMI21_TOP_REG_AD_MAIN_PHY_CTRL);
		data &= HDMI21_TOP_FIELD_O_REG_PHY_PDB;
		
		if(data)
		{
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1515){
				HDMI20_DBG("DBG %d : PDB is ON\n", port);
			}
			ret = RET_OK;
		}
		else{
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1515){
				HDMI20_DBG("DBG %d : PDB is OFF", port);
			}
			ret = RET_ERROR;
		}

	}while(0);

	return ret;
}

int HDMI21_PHY_E60A0_ControlPhyPDB(UINT8 port, BOOLEAN bOnOff)
{
	UINT32 data, __devid;
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;;
		}

		HDMI20_PHY("Notice %d : Phy PDB Control[%d]\n", port, (int)bOnOff);

		/* Phy PDB Control */
		data = gHDMI21RxHandler[port].top_read(HDMI21_TOP_REG_AD_MAIN_PHY_CTRL);
		if(bOnOff)	{
			data |= HDMI21_TOP_FIELD_O_REG_PHY_PDB;
			data |= HDMI21_TOP_FIELD_O_REG_PHY_ODT_PDB;
			data |= HDMI21_TOP_FIELD_O_REG_PHY_ODT_PDB_MODE_SEL;
		}
		else {
			data &= (~HDMI21_TOP_FIELD_O_REG_PHY_PDB);
			data &= (~HDMI21_TOP_FIELD_O_REG_PHY_ODT_PDB);
			data &= (~HDMI21_TOP_FIELD_O_REG_PHY_ODT_PDB_MODE_SEL);

		}
		gHDMI21RxHandler[port].top_write(HDMI21_TOP_REG_AD_MAIN_PHY_CTRL, data);

		/* Phy I2C Ctrl */
		if(port == 0) __devid = 0x00000000;
		else if(port == 1) __devid = 0x00000100;
		else if(port == 2) __devid = 0x00001000;
		else if(port == 3) __devid = 0x00001100;
		else if(port == 4) __devid = 0x00010000;
		else __devid = 0x0;

		data = gHDMI21RxHandler[port].top_read(HDMI21_TOP_REG_AD_MAIN_PHY_I2C);
		if(bOnOff)	data |= HDMI21_TOP_FIELD_O_REG_PHY_I2C_RST_N;
		else		data &= (~HDMI21_TOP_FIELD_O_REG_PHY_I2C_RST_N);
		data |= __devid;	/* Always Write the Dev ID */
		gHDMI21RxHandler[port].top_write(HDMI21_TOP_REG_AD_MAIN_PHY_I2C, data);

		ret = RET_OK;
	}while(0);

	return ret;
}


int HDMI21_PHY_E60A0_Reset_EqOffsetCalibration(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		HDMI20_PHY("PHY[%d] : Offset Calibration [%s]. Caller[%d]\n", port, isReset?"Reset Activate":"Reset Clear", callerId); 

		/* 0x39 (hdmi_phy_addr_39) */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_47);
		if(isReset)	{PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_47, eq_cal_mode_val, 0x0);}
		else 		{PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_47, eq_cal_mode_val, 0x1);}
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_47);

		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI21_PHY_E60A0_PowerControl_PLLPDB(UINT8 port, UINT8 isDown, UINT32 callerId)
{
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;;
		}

		HDMI20_PHY("PHY[%d] :  CR PDB Power Ctrl[%s]. Caller[%d]\n", port, isDown?"Down":"Up", callerId); 

		/* hdmi_phy_addr_03 */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_02);
		if(isDown)	{PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_02, cr_pll_pdb, 0x0);}
		else 		{PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_02, cr_pll_pdb, 0x1);}
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_02);

		ret = RET_OK;
	}while(0);

	return ret;
}


int HDMI21_PHY_E60A0_Reset_PLLPDB(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;;
		}

		HDMI20_PHY("Notice %d : Phy PLL PDB Reset : [%s]. Caller[%d]\n", port, isReset?"Reset Activate":"Reset Clear", callerId); 

		/* CR_PLL_RESETB_PDB */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_02);
		if(isReset)	{PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_02, cr_pll_resetb, 0x0);}
		else 		{PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_02, cr_pll_resetb, 0x1);}
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_02);

		ret = RET_OK;
	}while(0);

	return ret;
}

static int __HDMI21_PHY_E60A0_Check_CRDone(UINT8 port)
{
	int ret = RET_ERROR;
	int isCrDone = 0;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_3e);
		PHY_REG_E60A0_Rd01(port, hdmi_phy_addr_3e, cr_done, isCrDone);

		if(isCrDone)	{ gHDMI21RxHandler[port].phyCrDone = TRUE; ret = RET_OK; }
		else 			{ gHDMI21RxHandler[port].phyCrDone = FALSE; ret = RET_ERROR; }

	} while(0);

	return ret;
}

int HDMI21_PHY_E60A0_Check_SyncRecovery(UINT8 port)
{

	int ret = RET_ERROR;
	int phySyncRecovery[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int i;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(gHDMI21RxHandler[port].phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L){
			for(i=0;i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
				phySyncRecovery[i] = 0;
			}
		}
		else{
			/* Step 1. Check TCS Done */
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_14);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_14, tot_sync_recover_ch0, phySyncRecovery[0]);

			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_15);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_15, tot_sync_recover_ch1, phySyncRecovery[1]);

			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_16);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_16, tot_sync_recover_ch2, phySyncRecovery[2]);

			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_17);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_17, tot_sync_recover_ch3, phySyncRecovery[3]);
		}
		/* Step 2. Put in data */
		gHDMI21RxHandler[port].phySyncRecovery[0] = phySyncRecovery[0];
		gHDMI21RxHandler[port].phySyncRecovery[1] = phySyncRecovery[1];
		gHDMI21RxHandler[port].phySyncRecovery[2] = phySyncRecovery[2];
		gHDMI21RxHandler[port].phySyncRecovery[3] = phySyncRecovery[3];

		ret = RET_OK;
	} while(0);

	return ret;
}


int HDMI21_PHY_E60A0_Check_TMDSError(UINT8 port)
{

	int ret = RET_ERROR;
	int phyTMDSError[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyErrorCounter = 0;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Update Error Counter */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_13);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_13, err_update, phyErrorCounter);


		/* Step 1. Check TCS Done */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_18);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_18, tot_tmds_error_ch0, phyTMDSError[0]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_19);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_19, tot_tmds_error_ch1, phyTMDSError[1]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_1a);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_1a, tot_tmds_error_ch2, phyTMDSError[2]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_1b);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_1b, tot_tmds_error_ch3, phyTMDSError[3]);

		/* Step 2. Put in data */
		gHDMI21RxHandler[port].phyErrCounter = phyErrorCounter;

		gHDMI21RxHandler[port].phyTMDSError[0] = phyTMDSError[0];
		gHDMI21RxHandler[port].phyTMDSError[1] = phyTMDSError[1];
		gHDMI21RxHandler[port].phyTMDSError[2] = phyTMDSError[2];
		gHDMI21RxHandler[port].phyTMDSError[3] = phyTMDSError[3];

		ret = phyTMDSError[0] + phyTMDSError[1] + phyTMDSError[2] + phyTMDSError[3];
	} while(0);

	return ret;
}

int HDMI21_PHY_E60A0_Check_DeltaEye(UINT8 port)
{

	int ret = RET_ERROR;
	int phyDeltaPlus[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDeltaMinus[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_94);
		PHY_REG_B1_E60A0_Rd02(port, hdmi_phy_addr_94, delta_plus_ch0, phyDeltaPlus[0], delta_minus_ch0, phyDeltaMinus[0]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_95);
		PHY_REG_B1_E60A0_Rd02(port, hdmi_phy_addr_95, delta_plus_ch1, phyDeltaPlus[1], delta_minus_ch1, phyDeltaMinus[1]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_96);
		PHY_REG_B1_E60A0_Rd02(port, hdmi_phy_addr_96, delta_plus_ch2, phyDeltaPlus[2], delta_minus_ch2, phyDeltaMinus[2]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_97);
		PHY_REG_B1_E60A0_Rd02(port, hdmi_phy_addr_97, delta_plus_ch3, phyDeltaPlus[3], delta_minus_ch3, phyDeltaMinus[3]);

		/* Step 2. Put in data */
		gHDMI21RxHandler[port].phyDeltaPlus[0] = phyDeltaPlus[0];
		gHDMI21RxHandler[port].phyDeltaPlus[1] = phyDeltaPlus[1];
		gHDMI21RxHandler[port].phyDeltaPlus[2] = phyDeltaPlus[2];
		gHDMI21RxHandler[port].phyDeltaPlus[3] = phyDeltaPlus[3];

		gHDMI21RxHandler[port].phyDeltaMinus[0] = phyDeltaMinus[0];
		gHDMI21RxHandler[port].phyDeltaMinus[1] = phyDeltaMinus[1];
		gHDMI21RxHandler[port].phyDeltaMinus[2] = phyDeltaMinus[2];
		gHDMI21RxHandler[port].phyDeltaMinus[3] = phyDeltaMinus[3];


		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_PHY_E60A0_Check_DeltaError(UINT8 port)
{

	int ret = RET_ERROR;
	int phyDeltaError[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_14);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_14, tot_delta_error_ch0, phyDeltaError[0]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_15);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_15, tot_delta_error_ch1, phyDeltaError[1]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_16);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_16, tot_delta_error_ch2, phyDeltaError[2]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_17);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_17, tot_delta_error_ch3, phyDeltaError[3]);

		/* Step 2. Put in data */
		gHDMI21RxHandler[port].phyDeltaError[0] = phyDeltaError[0];
		gHDMI21RxHandler[port].phyDeltaError[1] = phyDeltaError[1];
		gHDMI21RxHandler[port].phyDeltaError[2] = phyDeltaError[2];
		gHDMI21RxHandler[port].phyDeltaError[3] = phyDeltaError[3];

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_PHY_E60A0_Check_CEDError(UINT8 port)
{

	int ret = RET_ERROR;
	int phyCEDError[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_18);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_18, tot_ced_error_ch0, phyCEDError[0]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_19);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_19, tot_ced_error_ch1, phyCEDError[1]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_1a);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_1a, tot_ced_error_ch2, phyCEDError[2]);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_1b);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_1b, tot_ced_error_ch3, phyCEDError[3]);

		/* Step 2. Put in data */
		gHDMI21RxHandler[port].phyCEDError[0] = phyCEDError[0];
		gHDMI21RxHandler[port].phyCEDError[1] = phyCEDError[1];
		gHDMI21RxHandler[port].phyCEDError[2] = phyCEDError[2];
		gHDMI21RxHandler[port].phyCEDError[3] = phyCEDError[3];

		ret = phyCEDError[0] + phyCEDError[1] + phyCEDError[2] + phyCEDError[3];
	} while(0);

	return ret;
}

int HDMI21_PHY_E60A0_Check_DfeResult(UINT8 port)
{
	int ret = RET_ERROR;
	int i;
	int phyDfeA01[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDfeA11[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDfeB1[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDfeB2[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDfeB3[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDfeB4[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDfeB5[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		for(i=0;i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_3b);
			PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_3b, dfe_result_ch_sel, i);
			PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_3b);

			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_35);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_35, dfe_level_a_01, phyDfeA01[i]);
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_36);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_36, dfe_level_a_11, phyDfeA11[i]);
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_37);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_37, dfe_level_b1, phyDfeB1[i]);
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_38);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_38, dfe_level_b2, phyDfeB2[i]);
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_39);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_39, dfe_level_b3, phyDfeB3[i]);
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_3a);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_3a, dfe_level_b4, phyDfeB4[i]);
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_3a);
			PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_3a, dfe_level_b5, phyDfeB5[i]);

			gHDMI21RxHandler[port].phyDfeA01Result[i] = phyDfeA01[i];
			gHDMI21RxHandler[port].phyDfeA11Result[i] = phyDfeA11[i];
			gHDMI21RxHandler[port].phyDfeB1Result[i]  = phyDfeB1[i];
			gHDMI21RxHandler[port].phyDfeB2Result[i]  = phyDfeB2[i];
			gHDMI21RxHandler[port].phyDfeB3Result[i]  = phyDfeB3[i];
			gHDMI21RxHandler[port].phyDfeB4Result[i]  = phyDfeB4[i];
			gHDMI21RxHandler[port].phyDfeB5Result[i]  = phyDfeB5[i];
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


int HDMI21_PHY_E60A0_Check_TCSDone(UINT8 port)
{

	int ret = RET_ERROR;
	int isTcsDone= 0;
	UINT32 fail_ch0, fail_ch1, fail_ch2, fail_ch3;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_2c);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_2c, tcs_done, isTcsDone);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch0, fail_ch0);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch1, fail_ch1);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch2, fail_ch2);
		PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch3, fail_ch3);

		if(isTcsDone) {
			gHDMI21RxHandler[port].phyTCSFailed = (fail_ch0) | (fail_ch1 << 4) | (fail_ch2 << 8) | (fail_ch3 << 12);
			gHDMI21RxHandler[port].phyTCSDone = TRUE; 
			ret = RET_OK; 
		}
		else { 
			gHDMI21RxHandler[port].phyTCSFailed = 0;
			gHDMI21RxHandler[port].phyTCSDone = FALSE; 
			ret = RET_ERROR; 
		}

	} while(0);

	return ret;
}




UINT8 HDMI21_PHY_E60A0_Get_TMDS_FREQ(UINT8 port, int isMSB)
{
	UINT8 tmds_value = 0;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(isMSB){
			PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_3a); 
			PHY_REG_E60A0_Rd01(port, hdmi_phy_addr_3a, tmds_freq_15_8, tmds_value);
		}
		else{
			PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_3b); 
			PHY_REG_E60A0_Rd01(port, hdmi_phy_addr_3b, tmds_freq_7_0, tmds_value);
		}

	} while(0);

	return tmds_value;
}

void HDMI21_PHY_E60A0_UpdatePhyTMDSclock(UINT8 port)
{
	UINT32 tmdsVal;
	int isManualEQ = 0;

	/* Port defence */
	if(port >= HDMI21_NUM_OF_PORTS_E60){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	/* Check for Manual EQ */
	if ( port == 3 )     { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_ENABLE_MANUAL_EQ].value; }
	else if ( port == 2) { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_ENABLE_MANUAL_EQ].value; }
	else if ( port == 1) { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_ENABLE_MANUAL_EQ].value; }
	else				 { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_ENABLE_MANUAL_EQ].value; }


	/* Calculate */
	tmdsVal = ((((UINT32)HDMI21_PHY_E60A0_Get_TMDS_FREQ(port, 1) & 0x000000FF)<<8) | ((UINT32)HDMI21_PHY_E60A0_Get_TMDS_FREQ(port, 0) & 0x000000FF));

	/* Range Detector for exception case :
	 * [HDMI 3G Mode]                     [HDMI 6G Mode
	 *  25MHz ~ 40MHz  : Mode 0			  None
	 *  40MHz ~ 80MHz  : Mode 1
	 *  80MHz ~ 160MHz : Mode 2
	 * 160MHz ~ 340MHz : Mode 3 */
	if(gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ENABLE_RANGE_EQ].value > 0){
		if(gHDMI21RxHandler[port].phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_6G) {
			gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange = -1;
		}
		else{
			if(gHDMI21RxHandler[port].phyCrDone > 0){
				if((tmdsVal >= gHDMI21RxDevPhyControler[HDMI21__PHY_TMDS_EXCEPTIONRANGE_LOW].value) &&(tmdsVal <= gHDMI21RxDevPhyControler[HDMI21__PHY_TMDS_EXCEPTIONRANGE_HIGH].value)){
					if(tmdsVal >= 8300) { gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange = 2; }
					else  				{ gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange = 1; }
				}
				else{
					gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange = 0;
				}
			}
			else {
				gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange = -1;
			}
		}


		if(gHDMI21RxHandler[port].phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) {
			if(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange != (gHDMI21RxHandler[port].phyPrevTMDSExceptionRange)){

				HDMI21_LINE_DBG(4243, "PHY[%d] :TMDS Range Changed from [%d]->[%d]\n", port, gHDMI21RxHandler[port].phyPrevTMDSExceptionRange, gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange);

				if(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange >= 2){

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_5a);
					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5a,\
							ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_MODE_2_0].value,\
							cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_MODE_2_0].value );
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_5a);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_93);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, 0x0);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_93);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_92);
					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_92);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_b8);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_MODE_2].value);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_b8);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_76);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x0);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_76);

					/* 2019/08/20 with DK : DK said it is werid for DFE to be ON on manual CS mode */
					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_58);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, 0);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_58);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_89);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_val, 0x0 );
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_mode, 0x0 );
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_89);
				
					/* 2020/02/19 */
					PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_04);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch3, 0x1);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch2, 0x1);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch1, 0x1);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch0, 0x1);
					PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_04);
				}
				else if(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange >= 1){
					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_5a);
					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5a,\
							ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_MODE_2_0].value,\
							cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_MODE_2_0].value );
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_5a);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_93);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, 0x0);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_93);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_92);
					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_92);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_b8);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_MODE_1_0].value);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_b8);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_76);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x0);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_76);

					/* 2019/08/20 with DK : DK said it is werid for DFE to be ON on manual CS mode */
					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_58);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, 0);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_58);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_89);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_val, 0x0 );
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_mode, 0x0 );
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_89);
				
					/* 2020/02/19 */
					PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_04);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch3, 0x1);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch2, 0x1);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch1, 0x1);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch0, 0x1);
					PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_04);

				}
				else if(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange == 0){
					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_5a);
					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_5a,\
							ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_MODE_3].value,\
							cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_MODE_3].value );
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_5a);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_93);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_SCAN2_MODE].value);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_93);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_92);
					PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_92);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_b8);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_MODE_3].value);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_b8);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_76);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_76);

					/* 2019/08/20 with DK : DK said it is werid for DFE to be ON on manual CS mode */
					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_58);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, 0);
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_58);

					PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_89);
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_val, 0x1 );
					PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_cdr_mode, 0x1 );
					PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_89);
				
					/* 2020/02/19 */
					PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_04);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch3, 0x0);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch2, 0x0);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch1, 0x0);
					PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch0, 0x0);
					PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_04);
				}


				/* Update TMDS Range Flag */
				gHDMI21RxHandler[port].phyPrevTMDSExceptionRange = gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange;

				/* Toggle TCS EN */
				HDMI21_PHY_E60A0_ToggleTCSEn(port, 0);
				HDMI21_PHY_E60A0_ToggleTCSEn(port, 1);
			}
		}
	}

	if((tmdsVal == 0) && (tmdsVal != gHDMI21RxHandler[port].phy_tmds_clk)){
		HDMI21_LINE_DBG(939, "DBG[%d] : TMDS went to ZERO![%llu]->[%d]\n", port, gHDMI21RxHandler[port].phy_tmds_clk, tmdsVal);

		/* Reset HDCP1.4/2.2 flag status */
		gHDMI21RxHandler[port].isHDCP14 = 0;
		gHDMI21RxHandler[port].isHDCP22 = 0;
		if(gHDMI21RxHandler[port].stable_cnt >= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value) {
			gHDMI21RxHandler[port].tmds_change = 1;
		}
	}

	gHDMI21RxHandler[port].phy_tmds_clk = tmdsVal;

	return;
}

int HDMI21_PHY_E60A0_Update_TMDS_TCS_Value(UINT8 port, int isClear)
{

	int ret = RET_ERROR;
	int i;
	int tcs_min[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int tcs_max[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0xff, 0xff, 0xff, 0xff};
	int tcs_diff[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int tcs_result[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int __tcs_state = 0;

	do{
		/* Port defence */
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(isClear){
			/* Step 1. Memset TCS value */
			memset((void *)&gHDMI21RxHandler[port].phyTCSDiff, 0, (sizeof(int) * HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY));
			memset((void *)&gHDMI21RxHandler[port].phyTCSMin,  0, (sizeof(int) * HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY));
			memset((void *)&gHDMI21RxHandler[port].phyTCSMax,  0, (sizeof(int) * HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY));
			memset((void *)&gHDMI21RxHandler[port].phyTCSResult,  0, (sizeof(int) * HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY));
		}
		else{
			if(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange > 0){
				/* Step 1. Check TCS min for every TMDS channel */
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_20); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_20, cs_min_ch0, tcs_min[0]);
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_22); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_22, cs_min_ch1, tcs_min[1]);
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_24); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_24, cs_min_ch2, tcs_min[2]);
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_26); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_26, cs_min_ch3, tcs_min[3]);

				/* Step 2. Check TCS Max for every TMDS channel */
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_21); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_21, cs_max_ch0, tcs_max[0]);
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_23); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_23, cs_max_ch1, tcs_max[1]);
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_25); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_25, cs_max_ch2, tcs_max[2]);
				PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_27); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_27, cs_max_ch3, tcs_max[3]);
			}
			else {
				/* Step 1. Check TCS min for every TMDS channel */
				PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_f4); PHY_REG_B2_E60A0_Rd01(port, hdmi_phy_addr_f4, delta_cs_min_ch0, tcs_min[0]);
				PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_f6); PHY_REG_B2_E60A0_Rd01(port, hdmi_phy_addr_f6, delta_cs_min_ch1, tcs_min[1]);
				PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_f8); PHY_REG_B2_E60A0_Rd01(port, hdmi_phy_addr_f8, delta_cs_min_ch2, tcs_min[2]);
				PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_fa); PHY_REG_B2_E60A0_Rd01(port, hdmi_phy_addr_fa, delta_cs_min_ch3, tcs_min[3]);

				/* Step 2. Check TCS Max for every TMDS channel */
				PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_f5); PHY_REG_B2_E60A0_Rd01(port, hdmi_phy_addr_f5, delta_cs_max_ch0, tcs_max[0]);
				PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_f7); PHY_REG_B2_E60A0_Rd01(port, hdmi_phy_addr_f7, delta_cs_max_ch1, tcs_max[1]);
				PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_f9); PHY_REG_B2_E60A0_Rd01(port, hdmi_phy_addr_f9, delta_cs_max_ch2, tcs_max[2]);
				PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_fb); PHY_REG_B2_E60A0_Rd01(port, hdmi_phy_addr_fb, delta_cs_max_ch3, tcs_max[3]);
			}

			/* Step 3. Check TCS Result */
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_1c); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_1c, cs_out_ch0, tcs_result[0]);
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_1d); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_1d, cs_out_ch1, tcs_result[1]);
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_1e); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_1e, cs_out_ch2, tcs_result[2]);
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_1f); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_1f, cs_out_ch3, tcs_result[3]);

			/* Step 4. Check TCS State */
			PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_31); PHY_REG_B1_E60A0_Rd01(port, hdmi_phy_addr_31, tcs_state, __tcs_state);

			/* Calculate TCS MIN/MAX differnce for all TDMS channel */
			for(i=0; i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY; i++){ 
				tcs_diff[i] = abs(tcs_max[i] - tcs_min[i]);
			}

			/* DBG Print */
			HDMI21_LINE_DBG(4242, "DBG %d : PHY Delta Min[%d/%d/%d]/Max[%d/%d/%d]/diff[%d/%d/%d]\n", port,\
					tcs_min[0], tcs_min[1], tcs_min[2], tcs_max[0], tcs_max[1], tcs_max[2],\
					tcs_diff[0], tcs_diff[1], tcs_diff[2]);

			/* Update TCS value */
			for(i=0;i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY; i++){ 
				gHDMI21RxHandler[port].phyTCSDiff[i] 	= tcs_diff[i];
				gHDMI21RxHandler[port].phyTCSMin[i] 	= tcs_min[i];
				gHDMI21RxHandler[port].phyTCSMax[i] 	= tcs_max[i];
				gHDMI21RxHandler[port].phyTCSResult[i] 	= tcs_result[i];
			}

			gHDMI21RxHandler[port].phyTCSState = __tcs_state;

		}
		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_PHY_E60A0_ToggleTCSEn(int port, int isSet)
{
	HDMI20_PHY("PHY[%d] : TCS [%s]\n", port, isSet?"Enable":"Disable");

	if(isSet) {
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_03, tcs_en_man_mode, 0x1, tcs_en_man_val, 0x1);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_03);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_03, tcs_en_man_mode, 0x0, tcs_en_man_val, 0x0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_03);

		/* 2019/12/18 : HDCP1.4 */
		HDMI21_HAL_Rx_Set_CoreResetWithMask(&gHDMI21RxHandler[port], gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value);
	}
	else{
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_03, tcs_en_man_mode, 0x1, tcs_en_man_val, 0x0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_03);
	}


	return 0;
}


int HDMI21_PHY_E60A0_Rx_Initiate_Phy(int port, HDMI21_HAL_PHY_INITIATED_MODE_T mode)
{
	int ret = RET_ERROR;
	UINT8 lowfreqGain = 0;
	int isManualEQ = 0;
	UINT32 __tcsManVal[4];
	int isOnboard = 0;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(gHDMI21RxHandler[port].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		/* Check for Onbaord HDMI source */
		isOnboard = __HDMI21_PHY_E60A0_IsOnboardPort(port);

		/* Always Initiate this on cable connect */
		gHDMI21RxHandler[port].isPhyFrlCtsMode = 0;

		/* Step 1 : PHY PDB=1, PHY_I2C_RSNT = 1 */
		if(HDMI21_PHY_E60A0_IsPhyPdbPowerOn(port) < 0){
			HDMI20_PHY("PHY[%d] : Phy PDB was Low but 5V High. Set PHY PDB to HIGH\n", port);
			HDMI21_PHY_E60A0_ControlPhyPDB(port, 1);
		}
	
		/* 2019/10/17 : Reset TCS State History & Idx */
		memset((void *)&gPhyTcsStateHist[port], 0xFF, sizeof(UINT32) * HDMI21_PHY_TCS_HIST_HISTORY_DEPTH);
		gPhyTcsStateHistIdx[port] = 0;

		/* Check for Manual EQ */
		if ( port == 4 )     { 
			isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P4_ENABLE_MANUAL_EQ].value; 
			__tcsManVal[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH0].value;
			__tcsManVal[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH1].value;
			__tcsManVal[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH2].value;
			__tcsManVal[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_P4_MANUAL_CS_VAL_CH3].value;
		}
		else if ( port == 3 )     { 
			isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_ENABLE_MANUAL_EQ].value; 
			__tcsManVal[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH0].value;
			__tcsManVal[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH1].value;
			__tcsManVal[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH2].value;
			__tcsManVal[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_MANUAL_CS_VAL_CH3].value;
		}
		else if ( port == 2) { 
			isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_ENABLE_MANUAL_EQ].value; 
			__tcsManVal[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH0].value;
			__tcsManVal[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH1].value;
			__tcsManVal[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH2].value;
			__tcsManVal[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_MANUAL_CS_VAL_CH3].value;
		}
		else if ( port == 1) { 
			isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_ENABLE_MANUAL_EQ].value; 
			__tcsManVal[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH0].value;
			__tcsManVal[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH1].value;
			__tcsManVal[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH2].value;
			__tcsManVal[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_MANUAL_CS_VAL_CH3].value;
		}
		else { 
			isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_ENABLE_MANUAL_EQ].value; 
			__tcsManVal[0] = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH0].value;
			__tcsManVal[1] = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH1].value;
			__tcsManVal[2] = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH2].value;
			__tcsManVal[3] = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_MANUAL_CS_VAL_CH3].value;
		}

		/* DBG : Exit when specific DBG case */
		if(gHDMI21RxDevPhyControler[HDMI21__PHY_DISABLE_PHYINITIATE_API].value > 0) {
			ret = RET_OK;
			break;
		}

		/* DBG : Always SCDC scrambling enable */
		if(gHDMI21RxDevVideoControler[HDMI21__FORCE_SCDC_MODE].value > 0){ 
			mode = gHDMI21RxDevVideoControler[HDMI21__FORCE_SCDC_MODE].value;
		}

		/* Flag for 3G/6G/FRL... */
		gHDMI21RxHandler[port].phyInitiatedMode = mode;

		if(isOnboard > 0) {
			if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_12G_4L){
				lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE3_ONBOARD].value;
			}
			else if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L){
				lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE2_ONBOARD].value;
			}
			else if (mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L){
				lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE1_ONBOARD].value;
			}
			else{
				lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE0_ONBOARD].value;
			}
		}
		else {
			if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_12G_4L){
				lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE3].value;
			}
			else if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L){
				lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE2].value;
			}
			else if (mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L){
				lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE1].value;
			}
			else{
				lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE0].value;
			}
		}

		HDMI20_PHY("PHY[%d][Onboard:%d] : Initate Phy[%s](RS Gain[0x%x])\n",port, isOnboard,phymode_type_to_str(mode), lowfreqGain);


		/* Set local mute on PHy initiate */
		HDMI21_HAL_Rx_Set_LocalVideoMute(port, 1, 0);

		/* 2020/03/31 : to prevent side-effects from Low Power Mode */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_11);
		PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch0_man, 0x0, eq_pdb_ch0_val, 0x0);
		PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch1_man, 0x0, eq_pdb_ch1_val, 0x0);
		PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch2_man, 0x0, eq_pdb_ch2_val, 0x0);
		PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch3_man, 0x0, eq_pdb_ch3_val, 0x0);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_11);

		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_02);
		PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_02, pdb_ch0_man, 0x0, pdb_ch0_val, 0x0);
		PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_02, pdb_ch1_man, 0x0, pdb_ch1_val, 0x0);
		PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_02, pdb_ch2_man, 0x0, pdb_ch2_val, 0x0);
		PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_02, pdb_ch3_man, 0x0, pdb_ch3_val, 0x0);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_02);

		/* 2019/11/06 */
		HDMI21_PHY_E60A0_PowerControl_PLLPDB(port, 1, __L__);

		/* 2019/10/22 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_03, tcs_en_man_mode, 0x0, tcs_en_man_val, 0x0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_03);

		/* 0x20 : 0x02 (MANUAL HDMI20_MODE = 0) / 0xAD : 0xA0 (DISABLE_DECORDER/SCR_MAN_OFF) / 0x5D : 0x06(EQ_RS_MAN=6)... */
		HDMI21_PHY_E60A0_Set_3G6G_Mode(port, 0, mode, mode, lowfreqGain);

		/* 2019/07/03 : DQA BHO-UH400 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_ae);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_ae, min_bound0, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_BOUND_0].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_ae, min_bound1, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_BOUND_1].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_ae);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_af);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_af, min_bound2, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_BOUND_2].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_af, min_bound3, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_BOUND_3].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_af);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_be);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_be, tcs_add_val0, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND0].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_be, tcs_new_add_val0, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND0].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_be);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_bf);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_bf, tcs_add_val1, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND1].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_bf, tcs_new_add_val1, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND1].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_bf);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_c0);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_c0, tcs_add_val2, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND2].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_c0, tcs_new_add_val2, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND2].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_c0);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_c1);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_c1, tcs_add_val3, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND3].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_c1, tcs_new_add_val3, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND3].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_c1);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_c2);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_c2, tcs_add_val4, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND4].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_c2, tcs_new_add_val4, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND4].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_c2);

		/* #1 connection	MAN_CON_SEL	0x28	0x38	0x30 */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_38);
		PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_38, i2c_con_sel_mode, 0x1, man_con_sel, 0x1);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_38);

		/* 2019/07/26 : Jang Silver Light Request */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_6e);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6e, cr_man_pll_reg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_PLL_MANUAL_MODE].value);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_6e);

		if(gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_PLL_MANUAL_MODE].value > 0){
			PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_6b);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6b, man_ctrl_fb_10l_20h, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_FB_10L_20H].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6b, man_ctrl_div2h_bpl, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_DIV2H_BPL].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6b, man_ctrl_rdiv, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_DIV2H_BPL].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6b, man_ctrl_refclk, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_REFCLK].value);
			PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_6b);

			PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_6c);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6c, man_ctrl_icp, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_ICP].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6c, man_ctrl_fdiv, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_FDIV].value);
			PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_6c);

			PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_6d);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6d, man_ctrl_pdr_5l_9h, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_PDR_5L_9H].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6d, man_ctrl_lfr2, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_LFR2].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6d, man_ctrl_lfc2, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_LFC2].value);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_6d, man_ctrl_lfc1, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_LFC1].value);
			PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_6d);
		}

		/* #2. PHY_DC	VBGR=4	0x28	0x70	0x23 */
		/* Move to 3G6G API */

		/* #3. EQ_DOGH=1	0x28	0x39	0x10 */
		/* Move to 3G6G API */


		/* #4. ODT_FREQ_DIV=4	0x28	0x5D	0x04 */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_5d);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_5d, odt_freq_div, 0x4);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_5d);

		/* #5. EQ_ICTRL=4	0x28	0x24	0x41 */
		/* Move to 3G6G API */


		/* #6. IDR	0x38	0x45	0x00 */
		/* move to 3g6g api */

		/* #7. isum=3, idac=3	0x38	0x59	0x1b */
		/* Move to 3G6G API */


		/* #8. CH0_RW_AUTO_MODE=0	0x38	0x05	0x00 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_05);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_05, ch0_rw_auto_mode, 0x0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_05);

		/* #9. EQ	RS_MAN_SEL=1	0x48	0x15	0x01 */
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_15);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_15, eq_rs_mode_sel, 0x1);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_15);

		/* 2019/05/20 */
		/* EQ_CS_MAN_CH */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a2);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a2, eq_cs_man_ch0, __tcsManVal[0]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a2);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a3);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a3, eq_cs_man_ch1, __tcsManVal[1]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a3);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a4);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a4, eq_cs_man_ch2, __tcsManVal[2]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a4);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a5);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a5, eq_cs_man_ch3, __tcsManVal[3]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a5);

		/* 2019/05/20 : DELTA_PLL_MODE */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_8b);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_8b, delta_mode_pll0, 0x0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_8b);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_8b);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_8b, delta_mode_pll1, 0x0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_8b);
		
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_8b);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_8b, delta_mode_pll2, 0x0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_8b);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_8b);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_8b, delta_mode_pll3, 0x0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_8b);

		/* 2019/07/08 */
		/* EQ_CS_MAN_CH */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_99);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll0, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_AUTO_PLL_0].value );
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll1, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_AUTO_PLL_1].value );
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll2, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_AUTO_PLL_2].value );
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_AUTO_PLL_3].value );
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_99);

		/* Add setting 2019/05/21 */
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_8a);
		PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_8a, frl_match_man_val, 0x3, match_man_val, 0xf);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_8a);

		/* #10. FILTER_SEL, G1_SEL	0x38	0xF3	0x14 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_f3);
		PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_f3, filter_sel, 0x1, g1_sel, 0x3);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_f3);

		/* #11. PHANTOM_MAN_VAL	0x38	0x75	0x01		*/
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_75);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_75, phantom_man_val, gHDMI21RxDevPhyControler[HDMI21__PHY_PHANTOM_MAN_VAL].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_75);

		/* #12. PHANTOM_FIX_MODE	0x38	0x74	0x03 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_74);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_74, phase_repeat_num, 0x3);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_74, phantom_fix_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_PHANTOM_FIXED_MODE].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_74);

		/* #13. DR_FILTER	0x38	0x70	0x01	*/
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_70);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_70,dr_filter, 0x1);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_70);

		/* #14. CS SCAN	DELTA_SCAN2, DELTA_ADD_VAL	0x38	0x93	0x46	0x56 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_93);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_SCAN2_MODE].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_93, delta_add_val, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_93);
		
		/* #15. DELTA_ADD_VAL_20, I2C_DELTA_SAMPLE	0x38	0x92	0x63	0x60	*/
		/* Move to 3G6G API */

		/* #16. DELTA_SCOPE2	0x38	0x8D	0x10 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_8d);
		PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_8d, delta_scope2, 0x1, delta_full_chk, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_FULL_CHECK].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_8d, delta_nside_bypass, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_CHK_NSIDE].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_8d, delta_pside_bypass, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_CHK_PSIDE].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_8d);
	
		/* New Add 5/8 : DELTA_SCOPE_PLL_MODE3	0x38	0x9A	0x03	*/
		/* Move to 3G6G API */

		/* #17. DELTA_MAX_ADJUST	0x38	0x98	0x32	*/
		/* Move to 3G6G API */

		/* #18. TCS_REPAT_OFF, TCS_DIVIDE_METHOD	0x38	0xB9	0x43 */				
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_b9);
		PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b9, tcs_skew_compare, 0x0, tcs_divide_method, 0x3);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_b9);


		/* #19. DFE	DFE_FILTER_ON, DFE_FILTER_G2_SEL	0x38	0x50	0x48 */				
		/* 2019/06/05 : Deleted */	

		/* #20. DFE_A, B1~B5	0x38	0x5C	0x3F	*/			
		/* Move to 3G6G API */

		/* #21. COMMON	EQ_EVAL_TIME2	0x38	0x72	0x01	*/
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_72);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_72, eq_eval_time_7_0, 0x1);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_72);


		/* #22. TCS_SCDT, MAN_PRE_OPTION	0x38	0xB3	0x06 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_b3);
		PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_b3, tcs_scdt, 0x1, man_pre_option, 0x2);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_b3);


		/* #23. TCS_BOUNDARY	0x38	0xBA	0x10	*/
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_ba);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_ba, tcs_boundary, 0x10);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_ba);


		/* #24. TCS_PREIOD_SEL, TCS_SCOPE	0x38	0xB7	0x81	*/
		/* Move to 3G6G API */

		/* #25. tcs_err_limit_basic	0x38	0xBD	0x0	*/
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_bd);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_bd, tcs_err_limit_loose, 0x0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_bd);


		/* #26. FIFO_MODE	0x38	0x6E	0x53 -> Moved to 0x48:0x6 in E60A0*/
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_06);
		PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_06, fifo_mode, 0x5, fifo_init_value, 0x3);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_06);


		/* #27. ERROR_UNIT_SEL	0x48	0xA4	0xA9 */
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_a4);
		PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_a4, tot_error_unit_sel, 0x1, err_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ERROR_PERIOD_SEL].value);
		PHY_REG_B2_E60A0_Wr02(port, hdmi_phy_addr_a4, loosecheck, 0x1, tmds_errec_detect, 0x1);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_a4);

		/* #28. REG_TCS_MAN_PRE	0x38	0xB4	0x60	*/
		/* Move to 3G6G API */

		/* #29. REG_TCS_MAN_MEA_1	0x38	0xB5	0x00 */
		/* Move to 3G6G API */

		/* #30. REG_TCS_MAN_MEA_2	0x38	0xB6	0x0A */
		/* Move to 3G6G API */

			
		/* #31. CED_OPEN_LENGTH	0x38	0xAC	0x23	*/
		/* Moved to 3G6G API : 2019/12/06 crow.kim */


		/* #32.	CHK_INFINITE_MODE	0x38	0xAD	0x10 */
		/* Moved to 3G6G API */
		
		/* #33. CED_CHECK_MODE	0x38	0xAB	0x00 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_ab);
		PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ab, ced_violation, 0x0, ced_check_mode, 0x0);
		PHY_REG_B1_E60A0_Wr02(port, hdmi_phy_addr_ab, scdt_chk_bypass, 0x0, scdt_det_done, 0x0);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_ab, ced_chk_done, 0x0);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_ab, ced_chk_bypass, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_CED_CHK_BYPASS].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_ab);


		/* #34. CED_ADAPTIVE_PERIOD	0x38	0xBC	0x15 */			
		/* Move to 3G6G API */


		/* New Add 5/8 : EQ_FREQ_DIV	0x38	0xED	0x06			*/
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_ed);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_ed, eq_freq_div, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQ_FREQ_DIV].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_ed);

		/* New Add 5/8 : CAL_INTEVAL	0x38	0xEF	0x50 */				
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_ef);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_ef, cal_interval, 0x5);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_ef);


		/* #35. ODT	MAN_ODT50	0x28	0x58	0x01 */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_58);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_58, man_odt50, 0x1);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_58);


		/* #36. I2C_ODT_HDMI50	0x28	0x59	0x1C */	
		/* ODT value = 0x18 then, 50 Ohm
		 * ODB value = 0x1C then, 42.8 Ohm */
		if(isOnboard > 0) {
			PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_59);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_59, i2c_odt_hdmi50, 0x18);
			PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_59);
		}
		else{
			PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_59);
			PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_59, i2c_odt_hdmi50, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_ODT_VAL].value);
			PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_59);
		}

		/* 2019/05/12 with DK */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_58);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, i2c_dfe_on_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_ON_MODE].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_58, dfe_not_off, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_NOT_OFF].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_58);

		/* JINWOO */
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_5a);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5a, eq_fail_sel, 0x4);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5a);

		/* 2019/09/20 : JINWOO */
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_5b);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5b, scdt_chk_mode, 0x0);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5b);

		/* 2019/09/23 : DK */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_74);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_74, ctrl_sel_crref, 0x1);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_74);

		/* 2019/09/30 DBG only : I2c DFE Beta API */
		/* This would also be called at 3G6G API */
		__HDMI21_PHY_E60A0_SetI2cManualDFEBxValue(port);

		/* 2019/10/02 JINWOO Choi, HyunKyo Kim */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_89);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_en_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DELTA_EN_MODE].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_89, i2c_delta_en_val, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DELTA_EN_VAL].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_89);

		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_5e);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5e, flt_timer_2000_11_8, gHDMI21RxDevPhyControler[HDMI21__PHY_FLT_TIMER_2000_11_8].value);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5e);

		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_5f);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_5f, flt_timer_2000_7_0, gHDMI21RxDevPhyControler[HDMI21__PHY_FLT_TIMER_2000_7_0].value);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_5f);

		/* 2019/11/20 : JINWOO CHoi SocioNext Factory */
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_60);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_60, flt_ready_man, 0x0);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_60, flt_ready_man_mode, 0x0);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_60);

		/* 2019/10/07 : DK Kim said to have this set */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_03, tcs_result_mode_sel, 0x3);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_03);

		/* 2019/11/28 : DK KIM said to put this here */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_4e);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_4e, freq_bound1, 0xA);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_4e);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_4f);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_4f, freq_bound2, 0x12);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_4f);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_50);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_50, freq_bound3, 0x1C);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_50);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_51);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_51, freq_bound4, 0x26);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_51);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_52);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_52, freq_bound5, 0x2B);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_52);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_53);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_53, freq_bound6, 0x30);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_53);
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_54);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_54, freq_bound7, 0x3A);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_54);
	
		#if 1 
		/* 2019/12/13 : JINWOO */
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_a1);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_a1, hdmi21_match_sel, 0x0);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_a1);
		#endif
	
		/* 2020/01/09 : Kim Sung Eun */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_82);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_82, i2c_data_delta_mode_ch0, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_I2C_DDELTA_MODE_CH0].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_82, i2c_data_delta_mode_ch1, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_I2C_DDELTA_MODE_CH1].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_82, i2c_data_delta_mode_ch2, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_I2C_DDELTA_MODE_CH2].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_82, i2c_data_delta_mode_ch3, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_I2C_DDELTA_MODE_CH3].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_82);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_83);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_83, i2c_data_delta_ch0, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_I2C_DDELTA_CH0].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_83, i2c_data_delta_ch1, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_I2C_DDELTA_CH1].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_83);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_84);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_84, i2c_data_delta_ch2, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_I2C_DDELTA_CH2].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_84, i2c_data_delta_ch3, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_I2C_DDELTA_CH3].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_84);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_7b);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_7b, i2c_data_sign, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_I2C_DATA_SIGN].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_7b);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_f3);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_f3, pat_filter_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_PAT_FILTER_SEL].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_f3);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_63);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_63, dfe_delta_on, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_DFE_DELTA_ON].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_63);

		/* 2020/02/19 */
		PHY_REG_B2_E60A0_RdFL(port, hdmi_phy_addr_04);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch3, 0x0);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch2, 0x0);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch1, 0x0);
		PHY_REG_B2_E60A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch0, 0x0);
		PHY_REG_B2_E60A0_WrFL(port, hdmi_phy_addr_04);

		/* 2020/02/19 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_50);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_50, dfe_new_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_DFE_NEW_M].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_50);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_51);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_51, dfe_new_char_num, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_DFE_NEW_CHAR].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_51);

		/* 2020/03/11 : G6 device issue */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_21);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_21, mode_sel_thres, 0x64);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_21);


		/* #37. RESET, PDB	RESETB_ALL	0x28	0x00	0x10 */
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_00);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_00, resetb_all, 0x1);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_00);

		/* #38.	ODT_PDB	0x28	0x48	0x11		*/		
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_48);
		PHY_REG_E60A0_Wr02(port, hdmi_phy_addr_48, eq_i2c_odt_pdb_mode , 0x1, eq_man_odt_pdb, 0x1);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_48);

		/* 2019/11/04 : DK Kim said to have this set here on top of PDB RESET_ALL */
		HDMI21_PHY_E60A0_PowerControl_PLLPDB(port, 0, __L__);

		ret = RET_OK;
	} while(0);

	return ret;
}

static void __attribute__((unused)) __HDMI21_PHY_E60A0_SetPhyExceptionCase(UINT8 port, HDMI21_HAL_PHY_EXCEPTION_CASE_T phyCase, int isReverse)
{
	do{
		/* Port Defence */
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if((phyCase == HDMI21_HAL_PHY_EXCEPTION_CASE_NONE)||(phyCase >= HDMI21_HAL_PHY_EXCEPTION_CASE_MAXNUM)){
			break;
		}

		if(isReverse){
			//HDMI20_PHY("Notice %d : Reset Phy Exception Case[0x%08x]\n", port, phyCase);	
		}
		else{
			HDMI20_PHY("Notice %d : Execute Phy Exception Case[0x%08x]\n", port, phyCase);	
		}

		switch(phyCase)
		{
			default :
				{
					/* Do none */	
				}break;
		}

	} while(0);

	return;
}


static void __HDMI21_PHY_E60A0_CheckPhyExceptionCase(UINT8 port, int resetClear)
{
	/* This function should only be called once there is a TCS Done, and phy is in a good state */

	do{
		/* Port Defence */
		if(port >= HDMI21_NUM_OF_PORTS_E60){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(resetClear){
			gHDMI21RxHandler[port].phyExceptionState = HDMI21_HAL_PHY_EXCEPTION_CASE_NONE;
		}
		else{
			/* None */	
		}
	} while(0);

	return;
}

static void __PHY_Reg_E60A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData)
{
	UINT32 apb_addr;
	if(port >= HDMI21_NUM_OF_PORTS_E60) return;
	if(pData == NULL) return;

	apb_addr = reg << 2;

	*pData = gHDMI21RxHandler[port].phyPDC_read(apb_addr);	
	return;
}

static void __PHY_Reg_E60A0_WrFL(UINT8 port, UINT32 reg, UINT32 data)
{
	UINT32 apb_addr;
	if(port >= HDMI21_NUM_OF_PORTS_E60) return;
	
	apb_addr = reg << 2;

	gHDMI21RxHandler[port].phyPDC_write(apb_addr, data);	
	return;
}

static void __PHY_Reg_B1_E60A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_PORTS_E60) return;
	if(pData == NULL) return;

	apb_addr = reg << 2;

	*pData = gHDMI21RxHandler[port].phyDR_read(apb_addr);	
	return;
}

static void __PHY_Reg_B1_E60A0_WrFL(UINT8 port, UINT32 reg, UINT32 data)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_PORTS_E60) return;
	
	apb_addr = reg << 2;

	gHDMI21RxHandler[port].phyDR_write(apb_addr, data);	
	return;
}


static void __PHY_Reg_B2_E60A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_PORTS_E60) return;
	if(pData == NULL) return;

	apb_addr = (reg << 2) + 0x400;

	*pData = gHDMI21RxHandler[port].phyDR_read(apb_addr);	
	return;
}

static void __PHY_Reg_B2_E60A0_WrFL(UINT8 port, UINT32 reg, UINT32 data)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_PORTS_E60) return;
	
	apb_addr = (reg << 2) + 0x400;

	gHDMI21RxHandler[port].phyDR_write(apb_addr, data);	
	return;
}


static void __HDMI21_PHY_E60A0_SetI2cManualDFEBxValue(UINT8 port)
{
	UINT32 __d;

	__d = gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEVEL_B1_MODE].value;

	/* Override Menu for FRL 10G*/
	if(gHDMI21RxHandler[port].phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
		if(gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEV_B1_MODE_FRL10].value > 0) {
			__d = gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEV_B1_MODE_FRL10].value;
		}
	}

	if((__d != 0) || \
			(gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEVEL_B2_MODE].value != 0) || \
			(gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEVEL_B3_MODE].value != 0) || \
			(gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEVEL_B4_MODE].value != 0) || \
			(gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEVEL_B5_MODE].value != 0)) {

		/* Set Mode Value */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_52);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, i2c_dfe_level_b1_mode, __d);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, i2c_dfe_level_b2_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEVEL_B2_MODE].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, i2c_dfe_level_b3_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEVEL_B3_MODE].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, i2c_dfe_level_b4_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEVEL_B4_MODE].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, i2c_dfe_level_b5_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_LEVEL_B5_MODE].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_52);

		/* Set LN to 0 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_3b);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_3b, dfe_result_ch_sel, 0x0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_3b);

		/* Set Value */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_54);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_55);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_56);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_57);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_54, i2c_dfe_level_b1, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B1_LEVEL_LN0].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_55, i2c_dfe_level_b2, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B2_LEVEL_LN0].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_56, i2c_dfe_level_b3, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B3_LEVEL_LN0].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_56, i2c_dfe_level_b4, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B4_LEVEL_LN0].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_57, i2c_dfe_level_b5, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B5_LEVEL_LN0].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_54);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_55);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_56);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_57);

		/* Trigger */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_52);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, dfe_man_val_en, 0x1);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_52);

		/* Set LN to 1 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_3b);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_3b, dfe_result_ch_sel, 0x1);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_3b);

		/* Set Value */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_54);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_55);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_56);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_57);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_54, i2c_dfe_level_b1, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B1_LEVEL_LN1].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_55, i2c_dfe_level_b2, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B2_LEVEL_LN1].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_56, i2c_dfe_level_b3, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B3_LEVEL_LN1].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_56, i2c_dfe_level_b4, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B4_LEVEL_LN1].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_57, i2c_dfe_level_b5, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B5_LEVEL_LN1].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_54);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_55);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_56);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_57);

		/* Trigger */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_52);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, dfe_man_val_en, 0x1);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_52);

		/* Set LN to 2 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_3b);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_3b, dfe_result_ch_sel, 0x2);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_3b);

		/* Set Value */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_54);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_55);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_56);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_57);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_54, i2c_dfe_level_b1, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B1_LEVEL_LN2].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_55, i2c_dfe_level_b2, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B2_LEVEL_LN2].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_56, i2c_dfe_level_b3, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B3_LEVEL_LN2].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_56, i2c_dfe_level_b4, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B4_LEVEL_LN2].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_57, i2c_dfe_level_b5, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B5_LEVEL_LN2].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_54);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_55);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_56);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_57);

		/* Trigger */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_52);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, dfe_man_val_en, 0x1);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_52);

		/* Set LN to 3 */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_3b);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_3b, dfe_result_ch_sel, 0x3);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_3b);

		/* Set Value */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_54);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_55);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_56);
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_57);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_54, i2c_dfe_level_b1, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B1_LEVEL_LN3].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_55, i2c_dfe_level_b2, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B2_LEVEL_LN3].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_56, i2c_dfe_level_b3, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B3_LEVEL_LN3].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_56, i2c_dfe_level_b4, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B4_LEVEL_LN3].value);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_57, i2c_dfe_level_b5, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_B5_LEVEL_LN3].value);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_54);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_55);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_56);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_57);

		/* Trigger */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_52);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, dfe_man_val_en, 0x1);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_52);

	}
	else {
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_52);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, i2c_dfe_level_b1_mode, 0);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, i2c_dfe_level_b2_mode, 0);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, i2c_dfe_level_b3_mode, 0);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, i2c_dfe_level_b4_mode, 0);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_52, i2c_dfe_level_b5_mode, 0);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_52);

	}

}

static void __HDMI21_PHY_E60A0_IncreaseTcsStateHistIdx(UINT8 port)
{
	int _d = 0;
	int _t = 0;

	if(port >= HDMI21_NUM_OF_PORTS_E60) return;

	/* Get Option */
	_t = gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_STATE_HIST_DEPTH].value;
	
	/* Increase Value */
	_d = gPhyTcsStateHistIdx[port];
	_d += 1;

	/* Check value & and Option*/
	if((_t == 0) || (_t == 1)) _d = 0;
	else if(_t > HDMI21_PHY_TCS_HIST_HISTORY_DEPTH) {
		_d = 0;
	}
	else if(_d >= _t) {
		_d = 0;
	}

	gPhyTcsStateHistIdx[port] = _d;

	return;
}

static int __HDMI21_PHY_E60A0_CheckTcsStateHistMatchVal(UINT8 port, UINT32 val)
{
	int i = 0;
	int ret = 0;
	int _t = 0;

	/* Get Option */
	_t = gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_STATE_HIST_DEPTH].value;

	do {
		/* Port Defence */
		if(port >= HDMI21_NUM_OF_PORTS_E60) break;

		/* Option Defence from seg fault */
		if(_t == 0) break;

		/* Memory access defence */
		if(_t > HDMI21_PHY_TCS_HIST_HISTORY_DEPTH) _t = HDMI21_PHY_TCS_HIST_HISTORY_DEPTH;

		for(i=0; i<_t; i++) {
			if(gPhyTcsStateHist[port][i] <= val) {
				ret += 1;
			}
		}
	} while(0);

	return ret;
}


static void __HDMI21_PHY_E60A0_SetDfeResultCenter(UINT8 port)
{
	int i;
	int deltaResult[HDMI21_HAL_CNT_OF_CHANNEL_IN_ONE_PHY];

	if((gHDMI21RxHandler[port].isPhyFrlCtsMode > 0)&&(gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_ADD_VAL_ON_CTS].value > 0)){
		/* Do Nothing */
	}
	else {
		for(i=0;i<HDMI21_HAL_CNT_OF_CHANNEL_IN_ONE_PHY;i++)
		{
			deltaResult[i] = gHDMI21RxHandler[port].phyTCSMin[i] + gHDMI21RxHandler[port].phyTCSMax[i];

			if(gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_CENTER_SWWA_ROUND_UP].value > 0) {
				if((deltaResult[i] & 0x1) != 0) {
					deltaResult[i] += 1;
				}
			}
			/* Divid by 2 */
			deltaResult[i] = deltaResult[i] >> 1;
		}

		/* Write Manual Value */
		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a2);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a2, eq_cs_man_ch0, deltaResult[0]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a2);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a3);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a3, eq_cs_man_ch1, deltaResult[1]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a3);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a4);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a4, eq_cs_man_ch2, deltaResult[2]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a4);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_a5);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_a5, eq_cs_man_ch3, deltaResult[3]);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_a5);

		PHY_REG_B1_E60A0_RdFL(port, hdmi_phy_addr_99);
		PHY_REG_B1_E60A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, 1);
		PHY_REG_B1_E60A0_WrFL(port, hdmi_phy_addr_99);
	}


	if((gHDMI21RxHandler[port].isPhyFrlCtsMode > 0) &&(gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_ADD_VAL_ON_CTS].value > 0)){
		HDMI20_PHY("PHY[%d] : FRL DFE Center SWWA not running(CTS Mode).\n",port);
	}
	else {
		HDMI20_PHY("PHY[%d] : FRL DFE Center Calculate Done. Result[%d][%d][%d][%d]\n",\
				port, deltaResult[0], deltaResult[1], deltaResult[2], deltaResult[3]);
	}

	return;
}

static int __HDMI21_PHY_E60A0_ToggleCrModeSelResetB(int port, int isSet)
{
	HDMI20_PHY("PHY[%d] : Cr Mode Sel ResetB[%s]\n", port, isSet?"Reset":"Clear");

	if(isSet) {
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_04);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_04, cr_mode_sel_resetb, 0x0);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_04);
	}
	else{
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_04);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_04, cr_mode_sel_resetb, 0x1);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_04);
	}

	return 0;

}

static int __HDMI21_PHY_E60A0_ToggleDrResetB(int port, int isSet)
{
	HDMI20_PHY("PHY[%d] : DR ResetB[%s]\n", port, isSet?"Reset":"Clear");

	if(isSet) {
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_01);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_01, resetb_sel, 0x1);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_01);

		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_06);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_06, dr_resetb, 0x0);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_06);
	}
	else{
		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_06);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_06, dr_resetb, 0x1);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_06);

		PHY_REG_E60A0_RdFL(port, hdmi_phy_addr_01);
		PHY_REG_E60A0_Wr01(port, hdmi_phy_addr_01, resetb_sel, 0x0);
		PHY_REG_E60A0_WrFL(port, hdmi_phy_addr_01);
	}

	return 0;
}

static int  __HDMI21_PHY_E60A0_IsOnboardPort(UINT8 port)
{
	int ret = 0;

	do {
		/* Port Defence */
		if(port >= HDMI21_NUM_OF_PORTS_E60) break;


		/* Option incase for forceing 8K model without Tool Opts */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_FORCE_8K_MODEL].value == 0) {
			if(gHDMI21RxHandler[port].is8KModel <= 0) break;
		}

		/* Option for each ports only when in 8K tool opts Or Force mode */

		if(port == 0) {
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_IS_ONBOARD_PORT0].value > 0) {
				ret = 1;
			}
		}
		else if(port == 1) {
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_IS_ONBOARD_PORT1].value > 0) {
				ret = 1;
			}
		}
		else if(port == 2) {
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_IS_ONBOARD_PORT2].value > 0) {
				ret = 1;
			}
		}
		else if(port == 3) {
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_IS_ONBOARD_PORT3].value > 0) {
				ret = 1;
			}
		}
		else if(port == 4) {
			if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_PCB_IS_ONBOARD_PORT4].value > 0) {
				ret = 1;
			}
		}

	} while(0);


	return ret;
}
