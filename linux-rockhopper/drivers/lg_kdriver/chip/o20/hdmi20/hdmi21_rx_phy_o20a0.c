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
 *  @date		2019-04-17
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

#include "hdmi21_rx_phy_o20a0.h"
#include "hdmi21_cfg_o20.h"
#include "../../../core/hdmi20/hdmi21_engine/hdmi21_hal_driver.h"
#include "hdmi20_drv.h"
#include "hdmi20_module.h"

#include "os_util.h"
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
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
/* O20A0 */
static void __PHY_Reg_O20A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData);
static void __PHY_Reg_O20A0_WrFL(UINT8 port, UINT32 reg, UINT32 data);

static void __PHY_Reg_B1_O20A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData);
static void __PHY_Reg_B1_O20A0_WrFL(UINT8 port, UINT32 reg, UINT32 data);

static void __PHY_Reg_B2_O20A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData);
static void __PHY_Reg_B2_O20A0_WrFL(UINT8 port, UINT32 reg, UINT32 data);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern volatile HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_RX_PORTS];
extern volatile HDMI20_DEV_CONTROL_T	gHDMI21RxDevPhyControler[HDMI21__DEV_PHY_CONTROL_LIST_MAXNUM];
extern volatile HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
extern volatile HDMI21_THREAD_CONTROLLER_T gHDMI21Thread;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
/* O20A0 */
HDMI21_PHY_REG_CTRL_O20A0_T 	phyReg_o20a0[HDMI21_NUM_OF_RX_PORTS];
HDMI21_PHY_REG_CTRL_B1_O20A0_T 	phyReg_B1_o20a0[HDMI21_NUM_OF_RX_PORTS];
HDMI21_PHY_REG_CTRL_B2_O20A0_T 	phyReg_B2_o20a0[HDMI21_NUM_OF_RX_PORTS];

/*----------------------------------------------------------------------------------------
    Implementation
----------------------------------------------------------------------------------------*/
/* O20A0 */
static void __HDMI21_PHY_O20A0_CheckPhyExceptionCase(UINT8 port, int resetClear);
static void __attribute__((unused)) __HDMI21_PHY_O20A0_SetPhyExceptionCase(UINT8 port, HDMI21_HAL_PHY_EXCEPTION_CASE_T phyCase, int isReverse);
static int 	__HDMI21_PHY_O20A0_Check_CRDone(UINT8 port);


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

/* IOCTL */
int HDMI21_PHY_O20A0_Rx_Get_PHYStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall)
{
	int ret = RET_ERROR;
	LX_HDMI_PHY_INFORM_T userdata;
	UINT32 tempData;
	UINT32 valuefor5V[HDMI21_NUM_OF_RX_PORTS] = {0,};
	int i;

	int deltaError = 0;
	int cedError = 0;
	int SyncRecovery = 0;
	int tcsError = 0;
	int isCrDone = 0;
	int updateTcsValue = 0;
	int deltaEye = 0;
	int dfeResult = 0;

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
		for(i=0; i<HDMI21_NUM_OF_RX_PORTS; i++){
			userdata.hdmi_mode[i] = gHDMI21RxHandler[i].hwVideo.dvi;		// < hdmi/dvi mode
		}

		/* Step 2-2. 5V Info */
		/* SW W/A for webos Popup sign for SONY EXPERIA Z2*/
		if(gHDMI21RxDevVideoControler[HDMI21__HOLD_TIME_5V_DETECTION].value == 0){
			for(i=0; i<HDMI21_NUM_OF_RX_PORTS; i++){
				HDMI21_HAL_Rx_Get_Check5VLevelInfo(i, &valuefor5V[i], 1);
				if(valuefor5V[i] != 0) userdata.hdmi5v[i] = 1;
				else userdata.hdmi5v[i] = 0;
			}
		}
		else{
			for(i=0; i<HDMI21_NUM_OF_RX_PORTS; i++){
				if(gHDMI21RxHandler[i].connected5Vtime >= gHDMI21RxDevPhyControler[HDMI21__HOLD_TIME_5V_DETECTION].value) userdata.hdmi5v[i] = 1;	
				else userdata.hdmi5v[i] = 0;
			}
		}

		if(updatePhyI2C > 0){
			for(i=0; i<HDMI21_NUM_OF_RX_PORTS; i++){
				if(userdata.hdmi5v[i] > 0){
					tcsError = HDMI21_PHY_O20A0_Check_TMDSError(i);
					SyncRecovery = HDMI21_PHY_O20A0_Check_SyncRecovery(i);
					isCrDone = __HDMI21_PHY_O20A0_Check_CRDone(i);
					cedError = HDMI21_PHY_O20A0_Check_CEDError(i);
					deltaError = HDMI21_PHY_O20A0_Check_DeltaError(i);
					deltaEye = HDMI21_PHY_O20A0_Check_DeltaEye(i);
					dfeResult = HDMI21_PHY_O20A0_Check_DfeResult(i);

					updateTcsValue = HDMI21_PHY_O20A0_Update_TMDS_TCS_Value(i, 0);
				}
			}
		}

		for(i=0; i<HDMI21_NUM_OF_RX_PORTS; i++){
			/* Step 2-3. HPD Info */
			userdata.hpd_out[i] = gHDMI21RxHandler[i].isHPD;		//	< HPD out status on each ports

			/* Step 2-4. TMDS Clk Info */	
			userdata.tmds_clock[i] = gHDMI21RxHandler[i].real_tmds_clk;				// Phy TMDS Clock

			/* Step 2-5. HPD Polarity Info */
			userdata.hpd_pol[i] = gHDMI21RxHandler[i].isHPDInverseMode;	

		}

		/* Step 2-6. PHY PDB */
		for(i=0; i<HDMI21_NUM_OF_RX_PORTS; i++){
			tempData = gHDMI21RxHandler[i].top_read(HDMI21_TOP_REG_AD_MAIN_PHY_CTRL);
			if((tempData & HDMI21_TOP_FIELD_O_REG_PHY_PDB) != 0) userdata.phy_pdb[i] = 1;
			else userdata.phy_pdb[i] = 0;
		}

		/* Step 2-7. PHY RSTN */
		/* None */

		for(i=0; i<HDMI21_NUM_OF_RX_PORTS; i++){
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

int HDMI21_PHY_O20A0_InitiatePhySystemCtrl(UINT8 port)
{
	int ret = RET_ERROR;

	do{
		HDMI20_PHY("[%s] Entered for port[%d]\n", __F__, port);

		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Mem allocate Phy Block #0 SHDW space */
		if((phyReg_o20a0[port].shdw.addr == NULL)){
			phyReg_o20a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_O20A0_T));

		}
		else {
			OS_Free((void *)phyReg_o20a0[port].shdw.addr);
			phyReg_o20a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_O20A0_T));
		}

		/* Mem allocate Phy Block #1 SHDW space */
		if((phyReg_B1_o20a0[port].shdw.addr == NULL)){
			phyReg_B1_o20a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B1_O20A0_T));

		}
		else {
			OS_Free((void *)phyReg_B1_o20a0[port].shdw.addr);
			phyReg_B1_o20a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B1_O20A0_T));
		}

		/* Mem allocate Phy Block #1 SHDW space */
		if((phyReg_B2_o20a0[port].shdw.addr == NULL)){
			phyReg_B2_o20a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B2_O20A0_T));

		}
		else {
			OS_Free((void *)phyReg_B2_o20a0[port].shdw.addr);
			phyReg_B2_o20a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B2_O20A0_T));
		}
	
		ret = RET_OK;
	} while(0);

	return ret;
}



void HDMI21_PHY_O20A0_UpdatePhyLockFlag(UINT8 port)
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


	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
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
		tcsDone = HDMI21_PHY_O20A0_Check_TCSDone(port);
		
		updateTcsValue = HDMI21_PHY_O20A0_Update_TMDS_TCS_Value(port, 0);
		isCrDone = __HDMI21_PHY_O20A0_Check_CRDone(port);

		tcsError = HDMI21_PHY_O20A0_Check_TMDSError(port);
		SyncRecovery = HDMI21_PHY_O20A0_Check_SyncRecovery(port);
		cedError = HDMI21_PHY_O20A0_Check_CEDError(port);
		deltaError = HDMI21_PHY_O20A0_Check_DeltaError(port);
		deltaEye = HDMI21_PHY_O20A0_Check_DeltaEye(port);
		dfeResult = HDMI21_PHY_O20A0_Check_DfeResult(port);

		/* Check Phy Lock */
		if(tcsDone >= 0){
			/* Update Flag */
			isPhyLocked = true;

			/* Execute any Phy Exception Case */
			if(gHDMI21RxDevPhyControler[HDMI21__PHY_ENABLE_PHY_EXCEPTION_CASE].value > 0){
				__HDMI21_PHY_O20A0_CheckPhyExceptionCase(port, 0);
			}
		}
	}while(0);

	if(port < HDMI21_NUM_OF_RX_PORTS){
		if((gHDMI21RxHandler[port].fsm_phy_lock > 0) && (isPhyLocked == false)) {
			HDMI20_PHY("PHY[%d] : === Detected Phy Lock Loss === \n", port);	
			gHDMI21RxHandler[port].fsm_phy_lock = 0;

			/* Reset HDCP2.2 Engine & Start HDCP2.2 Auth  */
			if(gHDMI21RxHandler[port].gWasHDCP22Written > 0) {
				/* HDCP2.2 */
				HDMI21_HDCP23_Module_Set_HlcReset(port, 0);
			}
		}

		gHDMI21RxHandler[port].isPhyLocked = isPhyLocked;
	}

	/* Reset Phy Exception case history when PHY LOCK is toggled to FALSE */
	if(gHDMI21RxDevPhyControler[HDMI21__PHY_ENABLE_PHY_EXCEPTION_CASE].value > 0){
		if(port < HDMI21_NUM_OF_RX_PORTS){
			if( gHDMI21RxHandler[port].isPhyLocked != true ){
				__HDMI21_PHY_O20A0_CheckPhyExceptionCase(port, 1);
			}
		}
	}

	/* DBG PRINT */
	HDMI21_LINE_DBG(4242, "DBG %d : tcsDone[%d] / updateTcsValue[%d] / isTcsStable[%d]\n", port, tcsDone,updateTcsValue,isTcsStable);

	return;
}


/* IOCTL */
int HDMI21_PHY_O20A0_Rx_AccessPhy(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size)
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

		if(port >= HDMI21_NUM_OF_RX_PORTS){
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



int HDMI21_PHY_O20A0_Set_3G6G_Mode(UINT8 port, UINT8 isAuto, HDMI21_HAL_PHY_INITIATED_MODE_T mode, UINT8 isScrambling, UINT8 lowfreqGain)
{
	int ret = RET_ERROR;
	int wasEQmodeChanged = 0;
	UINT32 flt_state = 0;

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Clear Phy Exception case history */
		if(gHDMI21RxDevPhyControler[HDMI21__PHY_ENABLE_PHY_EXCEPTION_CASE].value > 0){
			__HDMI21_PHY_O20A0_CheckPhyExceptionCase(port, 1);
		}


		HDMI20_PHY("PHY[%d] : Set PhyMode=>Sel[%s]/Mode[%s]/isScrambling[%d]/RSGain[0x%x]\n",\
				port, isAuto?"Auto":"Manual", phymode_type_to_str(mode), isScrambling, lowfreqGain);
		
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

		/* Flag for 3G/6G */
		gHDMI21RxHandler[port].phyInitiatedMode = mode;

		/* 0x28:0x23 = EQ_HDMI20_VAL
		 * 0x28:0x2A = Manual HDMI20_MODE
		 * 0x28:0x26 = Manual HDMI21_MODE
		 * 0x48:0x88 = SCR_MAN_OFF 
		 * 0x38:0xB8 = TCS_ERROR_SEL			*/
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_23);
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_2a);
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_26);
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_88);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_b8);
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_70);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_45);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_b7);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_8a);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_5a);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_93);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_92);
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_39);
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_24);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_59);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_f4);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_9a);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_98);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_76);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_b4);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_b5);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_b6);
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_41);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_5c);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_5d);
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_5e);
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_59);
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_66);

		if(isAuto)	{PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_2a, cr_i2c_hdmi20_mode, 0x0);}
		else 		{PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_2a, cr_i2c_hdmi20_mode, 0x1);}

		if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
			/* 2019/06/26 : Jinwoo told me to have this set(48:59) on the very top of all settings */
			PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_59,flt_man_mode, 0x0);
			PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_66,flt_update_man_mode, 0x0);
			HDMI21_PHY_O20A0_ToggleTCSEn(port, 0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5a,\
					ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_FRL_TYPE2].value,\
					cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_FRL_TYPE2].value );
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_8a, delta_scan_man_mode, 0x0, delta_scan_man, 0x0);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_23, eq_hdmi20_val, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE2].value,\
					eq_hdmi20_man, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE2].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_2a, cr_man_hdmi20, 0x0);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_26, cr_man_hdmi21, 0x1, cr_i2c_hdmi21_mode, 0x1 );
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE2].value);
			PHY_REG_B2_O20A0_Wr02(port, hdmi_phy_addr_88, scr_man_mode, 0x1, scr_man_val, 0x1);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_70, \
					ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE2].value,\
					ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE2].value);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_45, idr_adj, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL10G].value);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_b7, \
					tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL].value,\
					tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_39, eq_dohg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DOHG_FRL_TYPE2].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_24,eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_FRL_TYPE2].value);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE2].value\
					, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_FRL_TYPE2].value);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_f4, g2_sel, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_9a, delta_scope2_pll3, 0x0, delta_scope2_pll2, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x0, delta_max_adjust, 0x1);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b4, reg_tcs_man_pre , 0xFF);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b5, reg_tcs_man_mea_14_8, 0xA);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b6, reg_tcs_man_mea_7_0, 0xD2);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_41, pi_set_man_mode, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_a_on, 0x1, dfe_b1_on, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_b2_on, 0x1, dfe_b3_on, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_b4_on, 0x1, dfe_b5_on, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5d, dfe_n1, 0x0, dfe_n2_on, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_5d, dfe_n2, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_5e, dfe_updn_period, 0x0C);

		}
		else if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
			/* 2019/06/26 : Jinwoo told me to have this set(48:59) on the very top of all settings */
			PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_59,flt_man_mode, 0x0);
			PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_66,flt_update_man_mode, 0x0);
			HDMI21_PHY_O20A0_ToggleTCSEn(port, 0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5a,\
					ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_FRL_TYPE1].value,\
					cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_FRL_TYPE1].value );
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, 0x1);

			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_8a, delta_scan_man_mode, 0x0, delta_scan_man, 0x0);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_23, eq_hdmi20_val, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_FRL_TYPE1].value,\
					eq_hdmi20_man, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_FRL_TYPE1].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_2a, cr_man_hdmi20, 0x0);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_26, cr_man_hdmi21, 0x1, cr_i2c_hdmi21_mode, 0x1 );
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_FRL_TYPE1].value);
			PHY_REG_B2_O20A0_Wr02(port, hdmi_phy_addr_88, scr_man_mode, 0x1, scr_man_val, 0x1);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_70, \
					ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_FRL_TYPE1].value,\
					ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_FRL_TYPE1].value);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_45, idr_adj, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_FRL3G].value);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_b7, \
					tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_FRL].value,\
					tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_FRL].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_39, eq_dohg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DOHG_FRL_TYPE1].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_24, eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_FRL_TYPE1].value);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_FRL_TYPE1].value\
					, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_FRL_TYPE1].value);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_f4, g2_sel, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_9a, delta_scope2_pll3, 0x0, delta_scope2_pll2, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x0, delta_max_adjust, 0x1);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b4, reg_tcs_man_pre , 0xFF);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b5, reg_tcs_man_mea_14_8, 0xA);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b6, reg_tcs_man_mea_7_0, 0xD2);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_41, pi_set_man_mode, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_a_on, 0x1, dfe_b1_on, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_b2_on, 0x0, dfe_b3_on, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_b4_on, 0x0, dfe_b5_on, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5d, dfe_n1, 0x0, dfe_n2_on, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_5d, dfe_n2, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_5e, dfe_updn_period, 0x0C);
		}
		else if(mode ==  HDMI21_HAL_PHY_INITIATED_6G) {
			/* 2019/06/26 : Jinwoo told me to have this set(48:59) on the very top of all settings */
			PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_59,flt_man_mode, 0x1);
			PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_66,flt_update_man_mode, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5a,\
					ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_6G].value,\
					cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_6G].value );
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_8a, delta_scan_man_mode, 0x0, delta_scan_man, 0x0);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_23, eq_hdmi20_val, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_6G].value,\
					eq_hdmi20_man, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_6G].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_2a, cr_man_hdmi20, 0x1);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_26, cr_man_hdmi21, 0x0, cr_i2c_hdmi21_mode, 0x1 );
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_6G].value);
			PHY_REG_B2_O20A0_Wr02(port, hdmi_phy_addr_88, scr_man_mode, 0x1, scr_man_val, 0x1);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_70, \
					ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_6G].value,\
					ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_6G].value);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_45, idr_adj, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_TMDS6G].value);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_b7, \
					tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_TMDS].value,\
					tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_TMDS].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_39, eq_dohg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DOHG_6G].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_24, eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_6G].value);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_6G].value\
					, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_6G].value);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_f4, g2_sel, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_9a, delta_scope2_pll3, 0x1, delta_scope2_pll2, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x3, delta_max_adjust, 0x2);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b4, reg_tcs_man_pre , 0x60);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b5, reg_tcs_man_mea_14_8, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b6, reg_tcs_man_mea_7_0, 0xA);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_41, pi_set_man_mode, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_a_on, 0x1, dfe_b1_on, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_b2_on, 0x0, dfe_b3_on, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_b4_on, 0x0, dfe_b5_on, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5d, dfe_n1, 0x0, dfe_n2_on, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_5d, dfe_n2, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_5e, dfe_updn_period, 0x0C);
		}
		else {
			/* 2019/06/26 : Jinwoo told me to have this set(48:59) on the very top of all settings */
			PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_59,flt_man_mode, 0x1);
			PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_66,flt_update_man_mode, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5a,\
					ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_MODE_2_0].value,\
					cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_MODE_2_0].value );
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_8a, delta_scan_man_mode, 0x0, delta_scan_man, 0x0);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_23, eq_hdmi20_val, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_VAL_3G].value,\
					eq_hdmi20_man, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_HDMI20_MAN_3G].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_2a, cr_man_hdmi20, 0x0);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_26, cr_man_hdmi21, 0x0, cr_i2c_hdmi21_mode, 0x1 );
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_3G].value);
			PHY_REG_B2_O20A0_Wr02(port, hdmi_phy_addr_88, scr_man_mode, 0x1, scr_man_val, 0x0);
			PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_70, \
					ctrl_vref, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_VREF_3G].value,\
					ctrl_vreg14, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_REG_VOUT_3G].value);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_45, idr_adj, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_92, delta_add_val_20, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL_TMDS3G].value);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_b7, \
					tcs_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_PERIOD_S_TMDS].value,\
					tcs_scope, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_SCOPE_SEL_TMDS].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_39, eq_dohg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_DOHG_3G].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_24, eq_ictrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQICTRL_3G].value);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_59, dfe_sum_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_SUM_BIAS_3G].value\
					, dfe_dac_bias_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_DAC_BIAS_3G].value);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_f4, g2_sel, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_9a, delta_scope2_pll3, 0x1, delta_scope2_pll2, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_98, delta_cutline, 0x3, delta_max_adjust, 0x2);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b4, reg_tcs_man_pre , 0x60);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b5, reg_tcs_man_mea_14_8, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b6, reg_tcs_man_mea_7_0, 0xA);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_41, pi_set_man_mode, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_a_on, 0x1, dfe_b1_on, 0x1);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_b2_on, 0x0, dfe_b3_on, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5c, dfe_b4_on, 0x0, dfe_b5_on, 0x0);
			PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5d, dfe_n1, 0x0, dfe_n2_on, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_5d, dfe_n2, 0x0);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_5e, dfe_updn_period, 0x0C);
		}


		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_66);
		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_59);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_5e);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_5d);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_5c);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_8a);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_b7);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_92);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_45);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_70);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_23);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_2a);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_26);
		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_88);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_b8);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_5a);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_93);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_39);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_24);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_59);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_f4);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_9a);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_98);	
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_76);	
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_b4);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_b5);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_b6);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_41);

		/* 0x5D : EQ_RS_MAN */
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_16);
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_17);
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_18);
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_19);

		PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_16, eq_rs_man_ch0, lowfreqGain);
		PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_17, eq_rs_man_ch1, lowfreqGain);
		PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_18, eq_rs_man_ch2, lowfreqGain);
		PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_19, eq_rs_man_ch3, lowfreqGain);

		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_16);
		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_17);
		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_18);
		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_19);

		/* 0x39 : EQ_CAL_MODE_VAL 0->1 : Redo EQ offset calibration when lowfreqGain(RS) value changes */
		if(wasEQmodeChanged){
			HDMI21_PHY_O20A0_Reset_EqOffsetCalibration(port, 1, __L__);
			HDMI21_PHY_O20A0_Reset_EqOffsetCalibration(port, 0, __L__);
		}

		if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
			PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_59);
			PHY_REG_B2_O20A0_Rd01(port, hdmi_phy_addr_59, flt_state, flt_state);

			HDMI20_PHY("PHY[%d] : FLT State val is [0x%x]\n", port, flt_state);

			PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_59);
			PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x0);
			PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_5a);

			HDMI20_PHY("PHY[%d][%s] : Set EQ_SUCCESS_SEL to [0x0]\n", port, phymode_type_to_str(mode));

			HDMI21_PHY_O20A0_ToggleTCSEn(port, 1);
		}

		#if 0
		if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_ad);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_ad, chk_infinite_mode, 0x0);
			PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_ad);
		}
		#endif

		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_4b);
		if(mode ==  HDMI21_HAL_PHY_INITIATED_6G){
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_val, 0x3);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_mode, 0x1);	
		}
		else{
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_val, 0x0);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_mode, 0x0);	
		}
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_4b);
		#if 0
		/* 2016/07/21 : Audio Issue for 6G */
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_3c);
		if(is6G){
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_3c, pll_aud_man_val, 0x3);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_3c, pll_aud_man_mode, 0x1);	
		}
		else{
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_3c, pll_aud_man_val, 0x0);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_3c, pll_aud_man_mode, 0x0);	
		}
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_3c);
		#endif
		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI21_PHY_O20A0_IsPhyPdbPowerOn(UINT8 port)
{
	UINT32 data;
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Phy PDB Control */
		data = gHDMI21RxHandler[port].top_read(HDMI21_TOP_REG_AD_MAIN_PHY_CTRL);
		data &= HDMI21_TOP_FIELD_O_REG_PHY_PDB;
		
		if(data)
		{
			if(gHDMI21RxDevPhyControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1515){
				HDMI20_DBG("DBG %d : PDB is ON\n", port);
			}
			ret = RET_OK;
		}
		else{
			if(gHDMI21RxDevPhyControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 1515){
				HDMI20_DBG("DBG %d : PDB is OFF", port);
			}
			ret = RET_ERROR;
		}

	}while(0);

	return ret;
}

int HDMI21_PHY_O20A0_ControlPhyPDB(UINT8 port, BOOLEAN bOnOff)
{
	UINT32 data, __devid;
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
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


int HDMI21_PHY_O20A0_Reset_EqOffsetCalibration(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		HDMI20_PHY("PHY[%d] : Offset Calibration [%s]. Caller[%d]\n", port, isReset?"Reset Activate":"Reset Clear", callerId); 

		/* 0x39 (hdmi_phy_addr_39) */
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_47);
		if(isReset)	{PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_47, eq_cal_mode_val, 0x0);}
		else 		{PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_47, eq_cal_mode_val, 0x1);}
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_47);

		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI21_PHY_O20A0_PowerControl_PLLPDB(UINT8 port, UINT8 isDown, UINT32 callerId)
{
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;;
		}

		HDMI20_PHY("PHY[%d] :  CR PDB Power Ctrl[%s]. Caller[%d]\n", port, isDown?"Down":"Up", callerId); 

		/* hdmi_phy_addr_03 */
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_02);
		if(isDown)	{PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_02, cr_pll_pdb, 0x0);}
		else 		{PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_02, cr_pll_pdb, 0x1);}
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_02);

		ret = RET_OK;
	}while(0);

	return ret;
}


int HDMI21_PHY_O20A0_Reset_PLLPDB(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;;
		}

		HDMI20_PHY("Notice %d : Phy PLL PDB Reset : [%s]. Caller[%d]\n", port, isReset?"Reset Activate":"Reset Clear", callerId); 

		/* CR_PLL_RESETB_PDB */
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_02);
		if(isReset)	{PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_02, cr_pll_resetb, 0x0);}
		else 		{PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_02, cr_pll_resetb, 0x1);}
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_02);

		ret = RET_OK;
	}while(0);

	return ret;
}

static int __HDMI21_PHY_O20A0_Check_CRDone(UINT8 port)
{
	int ret = RET_ERROR;
	int isCrDone = 0;

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_3e);
		PHY_REG_O20A0_Rd01(port, hdmi_phy_addr_3e, cr_done, isCrDone);

		if(isCrDone)	{ gHDMI21RxHandler[port].phyCrDone = TRUE; ret = RET_OK; }
		else 			{ gHDMI21RxHandler[port].phyCrDone = FALSE; ret = RET_ERROR; }

	} while(0);

	return ret;
}

int HDMI21_PHY_O20A0_Check_SyncRecovery(UINT8 port)
{

	int ret = RET_ERROR;
	int phySyncRecovery[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int i;

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
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
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_14);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_14, tot_sync_recover_ch0, phySyncRecovery[0]);

			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_15);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_15, tot_sync_recover_ch1, phySyncRecovery[1]);

			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_16);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_16, tot_sync_recover_ch2, phySyncRecovery[2]);

			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_17);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_17, tot_sync_recover_ch3, phySyncRecovery[3]);
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


int HDMI21_PHY_O20A0_Check_TMDSError(UINT8 port)
{

	int ret = RET_ERROR;
	int phyTMDSError[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_18);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_18, tot_tmds_error_ch0, phyTMDSError[0]);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_19);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_19, tot_tmds_error_ch1, phyTMDSError[1]);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_1a);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_1a, tot_tmds_error_ch2, phyTMDSError[2]);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_1b);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_1b, tot_tmds_error_ch3, phyTMDSError[3]);

		/* Step 2. Put in data */
		gHDMI21RxHandler[port].phyTMDSError[0] = phyTMDSError[0];
		gHDMI21RxHandler[port].phyTMDSError[1] = phyTMDSError[1];
		gHDMI21RxHandler[port].phyTMDSError[2] = phyTMDSError[2];
		gHDMI21RxHandler[port].phyTMDSError[3] = phyTMDSError[3];

		ret = phyTMDSError[0] + phyTMDSError[1] + phyTMDSError[2] + phyTMDSError[3];
	} while(0);

	return ret;
}

int HDMI21_PHY_O20A0_Check_DeltaEye(UINT8 port)
{

	int ret = RET_ERROR;
	int phyDeltaPlus[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDeltaMinus[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_94);
		PHY_REG_B1_O20A0_Rd02(port, hdmi_phy_addr_94, delta_plus_ch0, phyDeltaPlus[0], delta_minus_ch0, phyDeltaMinus[0]);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_95);
		PHY_REG_B1_O20A0_Rd02(port, hdmi_phy_addr_95, delta_plus_ch1, phyDeltaPlus[1], delta_minus_ch1, phyDeltaMinus[1]);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_96);
		PHY_REG_B1_O20A0_Rd02(port, hdmi_phy_addr_96, delta_plus_ch2, phyDeltaPlus[2], delta_minus_ch2, phyDeltaMinus[2]);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_97);
		PHY_REG_B1_O20A0_Rd02(port, hdmi_phy_addr_97, delta_plus_ch3, phyDeltaPlus[3], delta_minus_ch3, phyDeltaMinus[3]);

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

int HDMI21_PHY_O20A0_Check_DeltaError(UINT8 port)
{

	int ret = RET_ERROR;
	int phyDeltaError[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_14);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_14, tot_delta_error_ch0, phyDeltaError[0]);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_15);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_15, tot_delta_error_ch1, phyDeltaError[1]);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_16);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_16, tot_delta_error_ch2, phyDeltaError[2]);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_17);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_17, tot_delta_error_ch3, phyDeltaError[3]);

		/* Step 2. Put in data */
		gHDMI21RxHandler[port].phyDeltaError[0] = phyDeltaError[0];
		gHDMI21RxHandler[port].phyDeltaError[1] = phyDeltaError[1];
		gHDMI21RxHandler[port].phyDeltaError[2] = phyDeltaError[2];
		gHDMI21RxHandler[port].phyDeltaError[3] = phyDeltaError[3];

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_PHY_O20A0_Check_CEDError(UINT8 port)
{

	int ret = RET_ERROR;
	int phyCEDError[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}
		if(gHDMI21RxHandler[port].phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L){
			/* In FRL mode, we cannot read CED Error from PHY registers */
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_14);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_14, tot_sync_recover_ch0, phyCEDError[0]);

			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_15);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_15, tot_sync_recover_ch1, phyCEDError[1]);

			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_16);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_16, tot_sync_recover_ch2, phyCEDError[2]);

			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_17);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_17, tot_sync_recover_ch3, phyCEDError[3]);

		}
		else{
			/* Step 1. Check TCS Done */
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_18);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_18, tot_ced_error_ch0, phyCEDError[0]);

			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_19);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_19, tot_ced_error_ch1, phyCEDError[1]);

			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_1a);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_1a, tot_ced_error_ch2, phyCEDError[2]);

			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_1b);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_1b, tot_ced_error_ch3, phyCEDError[3]);
		}
		/* Step 2. Put in data */
		gHDMI21RxHandler[port].phyCEDError[0] = phyCEDError[0];
		gHDMI21RxHandler[port].phyCEDError[1] = phyCEDError[1];
		gHDMI21RxHandler[port].phyCEDError[2] = phyCEDError[2];
		gHDMI21RxHandler[port].phyCEDError[3] = phyCEDError[3];

		ret = phyCEDError[0] + phyCEDError[1] + phyCEDError[2] + phyCEDError[3];
	} while(0);

	return ret;
}

int HDMI21_PHY_O20A0_Check_DfeResult(UINT8 port)
{
	int ret = RET_ERROR;
	int i;
	int phyDfeA01[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDfeA11[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDfeB1[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		for(i=0;i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_3b);
			PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_3b, dfe_result_ch_sel, i);
			PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_3b);

			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_35);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_35, dfe_level_a_01, phyDfeA01[i]);
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_36);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_36, dfe_level_a_11, phyDfeA11[i]);
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_37);
			PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_37, dfe_level_b1, phyDfeB1[i]);

			gHDMI21RxHandler[port].phyDfeA01Result[i] = phyDfeA01[i];
			gHDMI21RxHandler[port].phyDfeA11Result[i] = phyDfeA11[i];
			gHDMI21RxHandler[port].phyDfeB1Result[i]  = phyDfeB1[i];
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


int HDMI21_PHY_O20A0_Check_TCSDone(UINT8 port)
{

	int ret = RET_ERROR;
	int isTcsDone= 0;
	UINT32 fail_ch0, fail_ch1, fail_ch2, fail_ch3;

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_2c);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_2c, tcs_done, isTcsDone);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch0, fail_ch0);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch1, fail_ch1);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch2, fail_ch2);
		PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch3, fail_ch3);

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




UINT8 HDMI21_PHY_O20A0_Get_TMDS_FREQ(UINT8 port, int isMSB)
{
	UINT8 tmds_value = 0;

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(isMSB){
			PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_3a); 
			PHY_REG_O20A0_Rd01(port, hdmi_phy_addr_3a, tmds_freq_15_8, tmds_value);
		}
		else{
			PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_3b); 
			PHY_REG_O20A0_Rd01(port, hdmi_phy_addr_3b, tmds_freq_7_0, tmds_value);
		}

	} while(0);

	return tmds_value;
}

void HDMI21_PHY_O20A0_UpdatePhyTMDSclock(UINT8 port)
{
	UINT32 tmdsVal;
	int isManualEQ = 0;

	/* Port defence */
	if(port >= HDMI21_NUM_OF_RX_PORTS){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	/* Check for Manual EQ */
	if ( port == 3 )     { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_ENABLE_MANUAL_EQ].value; }
	else if ( port == 2) { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_ENABLE_MANUAL_EQ].value; }
	else if ( port == 1) { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_ENABLE_MANUAL_EQ].value; }
	else				 { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_ENABLE_MANUAL_EQ].value; }


	/* Calculate */
	tmdsVal = ((((UINT32)HDMI21_PHY_O20A0_Get_TMDS_FREQ(port, 1) & 0x000000FF)<<8) | ((UINT32)HDMI21_PHY_O20A0_Get_TMDS_FREQ(port, 0) & 0x000000FF));

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
					gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange = 1;
				}
				else{
					gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange = 0;
				}
			}
		}


		if(gHDMI21RxHandler[port].phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) {
			if(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange != (gHDMI21RxHandler[port].phyPrevTMDSExceptionRange)){

				HDMI21_LINE_DBG(4243, "PHY[%d] :TMDS Range Changed from [%d]->[%d]\n", port, gHDMI21RxHandler[port].phyPrevTMDSExceptionRange, gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange);

				if(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange > 0){

					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_5a);
					PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5a,\
							ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_MODE_2_0].value,\
							cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_MODE_2_0].value );
					PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5a, ana_cdr_sel, 0x0, cdr_fltr_ctrl, 0x0 );
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_5a);

					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_93);
					PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, 0x0);
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_93);

					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_92);
					PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_92);

					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_b8);
					PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_MODE_2].value);
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_b8);

					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_76);
					PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x0);
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_76);

					/* 2019/08/20 with DK : DK said it is werid for DFE to be ON on manual CS mode */
					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_58);
					PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, 0);
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_58);
				}
				else if(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange == 0){
					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_5a);
					PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_5a,\
							ana_cdr_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ANA_CDR_SEL_MODE_3].value,\
							cdr_fltr_ctrl, gHDMI21RxDevPhyControler[HDMI21__PHY_CDR_FLTR_CTRL_MODE_3].value );
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_5a);

					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_93);
					PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_93, delta_scan2_mode, 0x1);
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_93);

					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_92);
					PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_92, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_92);

					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_b8);
					PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ERROR_SEL_MODE_3].value);
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_b8);

					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_76);
					PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_76, dr_n2, 0x1);
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_76);

					/* 2019/08/20 with DK : DK said it is werid for DFE to be ON on manual CS mode */
					PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_58);
					PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_DIG_ON].value);
					PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_58);
				}


				/* Update TMDS Range Flag */
				gHDMI21RxHandler[port].phyPrevTMDSExceptionRange = gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange;

				/* Toggle TCS EN */
				HDMI21_PHY_O20A0_ToggleTCSEn(port, 0);
				HDMI21_PHY_O20A0_ToggleTCSEn(port, 1);
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

int HDMI21_PHY_O20A0_Update_TMDS_TCS_Value(UINT8 port, int isClear)
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
		if(port >= HDMI21_NUM_OF_RX_PORTS){
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
				PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_24); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_24, cs_min_ch0, tcs_min[0]);
				PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_26); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_26, cs_min_ch1, tcs_min[1]);
				PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_28); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_28, cs_min_ch2, tcs_min[2]);
				PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_2a); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_2a, cs_min_ch3, tcs_min[3]);

				/* Step 2. Check TCS Max for every TMDS channel */
				PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_25); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_25, cs_max_ch0, tcs_max[0]);
				PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_27); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_27, cs_max_ch1, tcs_max[1]);
				PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_29); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_29, cs_max_ch2, tcs_max[2]);
				PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_2b); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_2b, cs_max_ch3, tcs_max[3]);
			}
			else {
				/* Step 1. Check TCS min for every TMDS channel */
				PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_f4); PHY_REG_B2_O20A0_Rd01(port, hdmi_phy_addr_f4, delta_cs_min_ch0, tcs_min[0]);
				PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_f6); PHY_REG_B2_O20A0_Rd01(port, hdmi_phy_addr_f6, delta_cs_min_ch1, tcs_min[1]);
				PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_f8); PHY_REG_B2_O20A0_Rd01(port, hdmi_phy_addr_f8, delta_cs_min_ch2, tcs_min[2]);
				PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_fa); PHY_REG_B2_O20A0_Rd01(port, hdmi_phy_addr_fa, delta_cs_min_ch3, tcs_min[3]);

				/* Step 2. Check TCS Max for every TMDS channel */
				PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_f5); PHY_REG_B2_O20A0_Rd01(port, hdmi_phy_addr_f5, delta_cs_max_ch0, tcs_max[0]);
				PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_f7); PHY_REG_B2_O20A0_Rd01(port, hdmi_phy_addr_f7, delta_cs_max_ch1, tcs_max[1]);
				PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_f9); PHY_REG_B2_O20A0_Rd01(port, hdmi_phy_addr_f9, delta_cs_max_ch2, tcs_max[2]);
				PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_fb); PHY_REG_B2_O20A0_Rd01(port, hdmi_phy_addr_fb, delta_cs_max_ch3, tcs_max[3]);
			}

			/* Step 3. Check TCS Result */
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_20); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_20, cs_ch0, tcs_result[0]);
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_21); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_21, cs_ch1, tcs_result[1]);
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_22); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_22, cs_ch2, tcs_result[2]);
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_23); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_23, cs_ch3, tcs_result[3]);

			/* Step 4. Check TCS State */
			PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_31); PHY_REG_B1_O20A0_Rd01(port, hdmi_phy_addr_31, tcs_state, __tcs_state);

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

int HDMI21_PHY_O20A0_ToggleTCSEn(int port, int isSet)
{
	HDMI20_PHY("PHY[%d] : TCS [%s]\n", port, isSet?"Enable":"Disable");

	if(isSet) {
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_03, tcs_en_man_mode, 0x1, tcs_en_man_val, 0x1);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_03);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_03, tcs_en_man_mode, 0x0, tcs_en_man_val, 0x1);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_03);
	}
	else{
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_03, tcs_en_man_mode, 0x1, tcs_en_man_val, 0x0);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_03);
	}


	return 0;
}


int HDMI21_PHY_O20A0_Rx_Initiate_Phy(int port, HDMI21_HAL_PHY_INITIATED_MODE_T mode)
{
	int ret = RET_ERROR;
	UINT8 lowfreqGain = 0;
	int isManualEQ = 0;
	UINT32 __tcsManVal[4];

	do{
		if(port >= HDMI21_NUM_OF_RX_PORTS){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(gHDMI21RxHandler[port].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		/* Step 1 : PHY PDB=1, PHY_I2C_RSNT = 1 */
		if(HDMI21_PHY_O20A0_IsPhyPdbPowerOn(port) < 0){
			HDMI20_PHY("PHY[%d] : Phy PDB was Low but 5V High. Set PHY PDB to HIGH\n", port);
			HDMI21_PHY_O20A0_ControlPhyPDB(port, 1);
		}
		
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

		if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L){
			lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE2].value;
		}
		else if (mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L){
			lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE1].value;
		}
		else{
			lowfreqGain = gHDMI21RxDevPhyControler[HDMI21__PHY_RS_GAIN_TYPE0].value;
		}

		HDMI20_PHY("PHY[%d] : Initate Phy[%s](RS Gain[0x%x])\n",port, phymode_type_to_str(mode), lowfreqGain);


		/* Set local mute on PHy initiate */
		HDMI21_HAL_Rx_Set_LocalVideoMute(port, 1, 0);

		/* 0x20 : 0x02 (MANUAL HDMI20_MODE = 0) / 0xAD : 0xA0 (DISABLE_DECORDER/SCR_MAN_OFF) / 0x5D : 0x06(EQ_RS_MAN=6)... */
		HDMI21_PHY_O20A0_Set_3G6G_Mode(port, 0, mode, mode, lowfreqGain);

		/* 2019/07/03 : DQA BHO-UH400 */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_ae);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_ae, min_bound0, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_BOUND_0].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_ae, min_bound1, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_BOUND_1].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_ae);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_af);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_af, min_bound2, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_BOUND_2].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_af, min_bound3, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_BOUND_3].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_af);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_be);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_be, tcs_add_val0, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND0].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_be, tcs_new_add_val0, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND0].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_be);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_bf);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_bf, tcs_add_val1, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND1].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_bf, tcs_new_add_val1, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND1].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_bf);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_c0);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_c0, tcs_add_val2, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND2].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_c0, tcs_new_add_val2, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND2].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_c0);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_c1);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_c1, tcs_add_val3, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND3].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_c1, tcs_new_add_val3, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND3].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_c1);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_c2);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_c2, tcs_add_val4, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND4].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_c2, tcs_new_add_val4, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ADD_VAL_BOUND4].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_c2);

		/* #1 connection	MAN_CON_SEL	0x28	0x38	0x30 */
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_38);
		PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_38, i2c_con_sel_mode, 0x1, man_con_sel, 0x1);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_38);

		/* 2019/07/26 : Jang Silver Light Request */
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_6e);
		PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6e, cr_man_pll_reg, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_PLL_MANUAL_MODE].value);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_6e);

		if(gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_PLL_MANUAL_MODE].value > 0){
			PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_6b);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6b, man_ctrl_fb_10l_20h, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_FB_10L_20H].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6b, man_ctrl_div2h_bpl, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_DIV2H_BPL].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6b, man_ctrl_rdiv, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_DIV2H_BPL].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6b, man_ctrl_refclk, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_REFCLK].value);
			PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_6b);

			PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_6c);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6c, man_ctrl_icp, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_ICP].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6c, man_ctrl_fdiv, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_FDIV].value);
			PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_6c);

			PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_6d);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6d, man_ctrl_pdr_5l_9h, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_PDR_5L_9H].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6d, man_ctrl_lfr2, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_LFR2].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6d, man_ctrl_lfc2, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_LFC2].value);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_6d, man_ctrl_lfc1, gHDMI21RxDevPhyControler[HDMI21__PHY_MAN_CTRL_LFC1].value);
			PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_6d);
		}

		/* #2. PHY_DC	VBGR=4	0x28	0x70	0x23 */
		/* Move to 3G6G API */

		/* #3. EQ_DOGH=1	0x28	0x39	0x10 */
		/* Move to 3G6G API */


		/* #4. ODT_FREQ_DIV=4	0x28	0x5D	0x04 */
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_5d);
		PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_5d, odt_freq_div, 0x4);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_5d);

		/* #5. EQ_ICTRL=4	0x28	0x24	0x41 */
		/* Move to 3G6G API */


		/* #6. IDR	0x38	0x45	0x00 */
		/* move to 3g6g api */

		/* #7. isum=3, idac=3	0x38	0x59	0x1b */
		/* Move to 3G6G API */


		/* #8. CH0_RW_AUTO_MODE=0	0x38	0x05	0x00 */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_05);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_05, ch0_rw_auto_mode, 0x0);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_05);

		/* #9. EQ	RS_MAN_SEL=1	0x48	0x15	0x01 */
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_15);
		PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_15, eq_rs_mode_sel, 0x1);
		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_15);

		/* 2019/05/20 */
		/* EQ_CS_MAN_CH */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_a2);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_a2, eq_cs_man_ch0, __tcsManVal[0]);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_a2);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_a3);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_a3, eq_cs_man_ch1, __tcsManVal[1]);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_a3);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_a4);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_a4, eq_cs_man_ch2, __tcsManVal[2]);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_a4);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_a5);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_a5, eq_cs_man_ch3, __tcsManVal[3]);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_a5);

		/* 2019/05/20 : DELTA_PLL_MODE */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_8b);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_8b, delta_mode_pll0, 0x0);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_8b);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_8b);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_8b, delta_mode_pll1, 0x0);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_8b);
		
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_8b);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_8b, delta_mode_pll2, 0x2);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_8b);

		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_8b);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_8b, delta_mode_pll3, 0x0);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_8b);

		/* 2019/07/08 */
		/* EQ_CS_MAN_CH */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_99);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll0, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_AUTO_PLL_0].value );
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll1, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_AUTO_PLL_1].value );
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll2, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_AUTO_PLL_2].value );
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_AUTO_PLL_3].value );
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_99);

		/* Add setting 2019/05/21 */
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_8a);
		PHY_REG_B2_O20A0_Wr02(port, hdmi_phy_addr_8a, frl_match_man_val, 0x3, match_man_val, 0xf);
		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_8a);

		/* Add setting 2019/05/21 */
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_60);
		PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_60, hdmi21_sym_lock_sel, 0x0);
		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_60);

		/* #10. FILTER_SEL, G1_SEL	0x38	0xF3	0x14 */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_f3);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_f3, filter_sel, 0x1, g1_sel, 0x4);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_f3);

		/* #11. PHANTOM_MAN_VAL	0x38	0x75	0x01		*/
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_75);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_75, phantom_man_val, 0x1);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_75);

		/* #12. PHANTOM_FIX_MODE	0x38	0x74	0x03 */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_74);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_74, phase_repeat_num, 0x3);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_74);

		/* #13. DR_FILTER	0x38	0x70	0x01	*/
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_70);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_70,dr_filter, 0x1);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_70);

		/* #14. CS SCAN	DELTA_SCAN2, DELTA_ADD_VAL	0x38	0x93	0x46	0x56 */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_93);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_93, delta_scan2_mode, 0x1, eq_mode_auto_sel, 0x1);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_93, delta_add_val, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_ADD_VAL].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_93);
		
		/* #15. DELTA_ADD_VAL_20, I2C_DELTA_SAMPLE	0x38	0x92	0x63	0x60	*/
		/* Move to 3G6G API */

		/* #16. DELTA_SCOPE2	0x38	0x8D	0x10 */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_8d);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_8d, delta_scope2, 0x1, delta_full_chk, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_FULL_CHECK].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_8d, delta_nside_bypass, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_CHK_NSIDE].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_8d, delta_pside_bypass, gHDMI21RxDevPhyControler[HDMI21__PHY_DELTA_CHK_PSIDE].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_8d);
	
		/* New Add 5/8 : DELTA_SCOPE_PLL_MODE3	0x38	0x9A	0x03	*/
		/* Move to 3G6G API */

		/* #17. DELTA_MAX_ADJUST	0x38	0x98	0x32	*/
		/* Move to 3G6G API */

		/* #18. TCS_REPAT_OFF, TCS_DIVIDE_METHOD	0x38	0xB9	0x43 */				
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_b9);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_b9, tcs_skew_compare, 0x0, tcs_divide_method, 0x3);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_b9);


		/* #19. DFE	DFE_FILTER_ON, DFE_FILTER_G2_SEL	0x38	0x50	0x48 */				
		/* 2019/06/05 : Deleted */	

		/* #20. DFE_A, B1~B5	0x38	0x5C	0x3F	*/			
		/* Move to 3G6G API */

		/* #21. COMMON	EQ_EVAL_TIME2	0x38	0x72	0x01	*/
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_72);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_72, eq_eval_time_7_0, 0x1);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_72);


		/* #22. TCS_SCDT, MAN_PRE_OPTION	0x38	0xB3	0x06 */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_b3);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_b3, tcs_scdt, 0x1, man_pre_option, 0x2);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_b3);


		/* #23. TCS_BOUNDARY	0x38	0xBA	0x10	*/
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_ba);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_ba, tcs_boundary, 0x10);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_ba);


		/* #24. TCS_PREIOD_SEL, TCS_SCOPE	0x38	0xB7	0x81	*/
		/* Move to 3G6G API */

		/* #25. tcs_err_limit_basic	0x38	0xBD	0x0	*/
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_bd);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_bd, tcs_err_limit_loose, 0x0);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_bd);


		/* #26. FIFO_MODE	0x38	0x6E	0x53 */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_6e);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_6e, fifo_mode, 0x5, fifo_init_value, 0x3);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_6e);


		/* #27. ERROR_UNIT_SEL	0x48	0xA4	0xA9 */
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_a4);
		PHY_REG_B2_O20A0_Wr02(port, hdmi_phy_addr_a4, tot_error_unit_sel, 0x1, err_period_sel, gHDMI21RxDevPhyControler[HDMI21__PHY_ERROR_PERIOD_SEL].value);
		PHY_REG_B2_O20A0_Wr02(port, hdmi_phy_addr_a4, loosecheck, 0x1, tmds_errec_detect, 0x1);
		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_a4);

		/* #28. REG_TCS_MAN_PRE	0x38	0xB4	0x60	*/
		/* Move to 3G6G API */

		/* #29. REG_TCS_MAN_MEA_1	0x38	0xB5	0x00 */
		/* Move to 3G6G API */

		/* #30. REG_TCS_MAN_MEA_2	0x38	0xB6	0x0A */
		/* Move to 3G6G API */

			
		/* #31. CED_OPEN_LENGTH	0x38	0xAC	0x23	*/
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_ac);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_ac, ced_open_length, 0x2, tmds_open_length, 0x3);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_ac);

		/* #32.	CHK_INFINITE_MODE	0x38	0xAD	0x10 */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_ad);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_ad, chk_infinite_mode, 0x1);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_ad);

		/* #33. CED_CHECK_MODE	0x38	0xAB	0x00 */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_ab);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_ab, ced_violation, 0x0, ced_check_mode, 0x0);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_ab, scdt_chk_bypass, 0x0, scdt_det_done, 0x0);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_ab, ced_chk_done, 0x0);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_ab);


		/* #34. CED_ADAPTIVE_PERIOD	0x38	0xBC	0x15 */				
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_bc);
		PHY_REG_B1_O20A0_Wr02(port, hdmi_phy_addr_bc, adaptive_period, 0x1, adaptive_period_sel, 0x5);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_bc);

		/* New Add 5/8 : EQ_FREQ_DIV	0x38	0xED	0x06			*/
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_ed);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_ed, eq_freq_div, gHDMI21RxDevPhyControler[HDMI21__PHY_CTRL_EQ_FREQ_DIV].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_ed);

		/* New Add 5/8 : CAL_INTEVAL	0x38	0xEF	0x50 */				
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_ef);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_ef, cal_interval, 0x5);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_ef);


		/* #35. ODT	MAN_ODT50	0x28	0x58	0x01 */
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_58);
		PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_58, man_odt50, 0x1);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_58);


		/* #36. I2C_ODT_HDMI50	0x28	0x59	0x1C */	
		/* ODT value = 0x18 then, 50 Ohm
		 * ODB value = 0x1C then, 42.8 Ohm */
		if(port == 4){
			PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_59);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_59, i2c_odt_hdmi50, 0x18);
			PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_59);
		}
		else{
			PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_59);
			PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_59, i2c_odt_hdmi50, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_ODT_VAL].value);
			PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_59);
		}

		/* 2019/05/12 with DK */
		PHY_REG_B1_O20A0_RdFL(port, hdmi_phy_addr_58);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_58, i2c_dfe_on_mode, gHDMI21RxDevPhyControler[HDMI21__PHY_I2C_DFE_ON_MODE].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_58, dfe_dig_on, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_DIG_ON].value);
		PHY_REG_B1_O20A0_Wr01(port, hdmi_phy_addr_58, dfe_not_off, gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_NOT_OFF].value);
		PHY_REG_B1_O20A0_WrFL(port, hdmi_phy_addr_58);

		/* JINWOO */
		PHY_REG_B2_O20A0_RdFL(port, hdmi_phy_addr_5a);
		PHY_REG_B2_O20A0_Wr01(port, hdmi_phy_addr_5a, eq_fail_sel, 0x4);
		PHY_REG_B2_O20A0_WrFL(port, hdmi_phy_addr_5a);

		/* #37. RESET, PDB	RESETB_ALL	0x28	0x00	0x10 */
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_00);
		PHY_REG_O20A0_Wr01(port, hdmi_phy_addr_00, resetb_all, 0x1);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_00);

		/* #38.	ODT_PDB	0x28	0x48	0x11		*/		
		PHY_REG_O20A0_RdFL(port, hdmi_phy_addr_48);
		PHY_REG_O20A0_Wr02(port, hdmi_phy_addr_48, eq_i2c_odt_pdb_mode , 0x1, eq_man_odt_pdb, 0x1);
		PHY_REG_O20A0_WrFL(port, hdmi_phy_addr_48);


		ret = RET_OK;
	} while(0);

	return ret;
}

static void __attribute__((unused)) __HDMI21_PHY_O20A0_SetPhyExceptionCase(UINT8 port, HDMI21_HAL_PHY_EXCEPTION_CASE_T phyCase, int isReverse)
{
	do{
		/* Port Defence */
		if(port >= HDMI21_NUM_OF_RX_PORTS){
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


static void __HDMI21_PHY_O20A0_CheckPhyExceptionCase(UINT8 port, int resetClear)
{
	/* This function should only be called once there is a TCS Done, and phy is in a good state */

	do{
		/* Port Defence */
		if(port >= HDMI21_NUM_OF_RX_PORTS){
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

static void __PHY_Reg_O20A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData)
{
	UINT32 apb_addr;
	if(port >= HDMI21_NUM_OF_RX_PORTS) return;
	if(pData == NULL) return;

	apb_addr = reg << 2;

	*pData = gHDMI21RxHandler[port].phyPDC_read(apb_addr);	
	return;
}

static void __PHY_Reg_O20A0_WrFL(UINT8 port, UINT32 reg, UINT32 data)
{
	UINT32 apb_addr;
	if(port >= HDMI21_NUM_OF_RX_PORTS) return;
	
	apb_addr = reg << 2;

	gHDMI21RxHandler[port].phyPDC_write(apb_addr, data);	
	return;
}

static void __PHY_Reg_B1_O20A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_RX_PORTS) return;
	if(pData == NULL) return;

	apb_addr = reg << 2;

	*pData = gHDMI21RxHandler[port].phyDR_read(apb_addr);	
	return;
}

static void __PHY_Reg_B1_O20A0_WrFL(UINT8 port, UINT32 reg, UINT32 data)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_RX_PORTS) return;
	
	apb_addr = reg << 2;

	gHDMI21RxHandler[port].phyDR_write(apb_addr, data);	
	return;
}


static void __PHY_Reg_B2_O20A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_RX_PORTS) return;
	if(pData == NULL) return;

	apb_addr = (reg << 2) + 0x400;

	*pData = gHDMI21RxHandler[port].phyDR_read(apb_addr);	
	return;
}

static void __PHY_Reg_B2_O20A0_WrFL(UINT8 port, UINT32 reg, UINT32 data)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_RX_PORTS) return;
	
	apb_addr = (reg << 2) + 0x400;

	gHDMI21RxHandler[port].phyDR_write(apb_addr, data);	
	return;
}
