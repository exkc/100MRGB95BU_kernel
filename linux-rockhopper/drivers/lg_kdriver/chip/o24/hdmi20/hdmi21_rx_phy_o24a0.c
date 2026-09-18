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
 *  @author		taejun.lee	
 *  @version	1.0 
 *  @date		2023-01-11
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

#include "hdmi21_rx_phy_o24a0.h"
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
#define HDMI21_PHY_O24A0_REG_WR(address,data)   \
		__sMapped_address=(UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(__sMapped_address == NULL) break;\
		*__sMapped_address = data;\
		iounmap((void *)__sMapped_address);\
	}while(0);\
	
#define HDMI21_PHY_O24A0_REG_RD(address,data)   \
		__sMapped_address = (UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(__sMapped_address == NULL) {data = 0; break;}\
		data = (unsigned int)*__sMapped_address;\
		iounmap((void *)__sMapped_address);\
	}while(0);\

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
/* O24A0 */
static void __PHY_Reg_O24A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData);
static void __PHY_Reg_O24A0_WrFL(UINT8 port, UINT32 reg, UINT32 data);

static void __PHY_Reg_B1_O24A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData);
static void __PHY_Reg_B1_O24A0_WrFL(UINT8 port, UINT32 reg, UINT32 data);

static void __PHY_Reg_B2_O24A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData);
static void __PHY_Reg_B2_O24A0_WrFL(UINT8 port, UINT32 reg, UINT32 data);

/* TCS State Hist */
static void __HDMI21_PHY_O24A0_IncreaseTcsStateHistIdx(UINT8 port);
static int __HDMI21_PHY_O24A0_CheckTcsStateHistMatchVal(UINT8 port, UINT32 val);

/* DFE Center */
static void __HDMI21_PHY_O24A0_SetDfeResultCenter(UINT8 port);
/* DR_RESETB */
static int __HDMI21_PHY_O24A0_ToggleDrResetB(int port, int isSet);
static int __HDMI21_PHY_O24A0_ToggleCrModeSelResetB(int port, int isSet);

/* FLT_START */
static int __HDMI21_PHY_O24A0_ToggleFltStart(int port, int isHigh, int isSet, UINT32 __callerLine);

static int HDMI_PHY_Set_Reg_Table(UINT8 port, HDMI_PHY_REG_APB_O24A0_T reg, HDMI_PHY_INIT_MODE_T mode);
static HDMI_PHY_INIT_MODE_T _CvtPhyMode(HDMI21_HAL_PHY_INITIATED_MODE_T mode);
static HDMI_PHY_INIT_MODE_T _CvtExceptRange(int phyCurExcepRange);
static void _SET_PHY (UINT8 port, HDMI_PHY_REG_APB_O24A0_T index, HDMI_PHY_INIT_MODE_T mode);

//static int __HDMI21_PHY_O24A0_CheckEqCalDone(int port);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern volatile HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];
extern volatile HDMI20_DEV_CONTROL_T	gHDMI21RxDevPhyControler[HDMI21__DEV_PHY_CONTROL_LIST_MAXNUM];
extern volatile HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
extern volatile HDMI20_DEV_CONTROL_T	gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];
extern volatile HDMI21_THREAD_CONTROLLER_T gHDMI21Thread;
extern UINT32 o24a0_phy_table[PHY_REG_MAX_NUM_O24A0][HDMI_PHY_INITIATED_MAXNUM];
extern volatile PHY_REG_TABLE_O24A0 o24a0_phy_reg_table[PHY_REG_MAX_NUM_O24A0];


/*---------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
/* O24A0 */
HDMI21_PHY_REG_CTRL_O24A0_T 	phyReg_o24a0[HDMI21_NUM_OF_PORTS_O24];
HDMI21_PHY_REG_CTRL_B1_O24A0_T 	phyReg_B1_o24a0[HDMI21_NUM_OF_PORTS_O24];
HDMI21_PHY_REG_CTRL_B2_O24A0_T 	phyReg_B2_o24a0[HDMI21_NUM_OF_PORTS_O24];

static UINT32 gPhyTcsStateHist[HDMI21_NUM_OF_PORTS_O24][HDMI21_PHY_TCS_HIST_HISTORY_DEPTH] = {0,};
static int    gPhyTcsStateHistIdx[HDMI21_NUM_OF_PORTS_O24] = {0, };
static int    gPhyFrlFrlStartManualIdx[HDMI21_NUM_OF_PORTS_O24] = {0, };

//TODO: O24A0
//HDMI21_PHY_O24A0_SAFF_OFFSET_DATA_T gPhySaffOffsetResult_O24[HDMI21_NUM_OF_PORTS_O24][HDMI21_HAL_CNT_OF_CHANNEL_IN_ONE_PHY];

//TODO: O24A0
//int gHDMI21PhyFakeTcsDone_O24[HDMI21_NUM_OF_PORTS_O24] = {0, };
//int gHDMI21PhyJinWooNewO24Check[HDMI21_NUM_OF_PORTS_O24] = {0, };

/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/
static unsigned int *__sMapped_address; // For DBG: REG Read/Write macro


/*----------------------------------------------------------------------------------------
    Implementation
----------------------------------------------------------------------------------------*/
/* O24A0 */
static void __HDMI21_PHY_O24A0_CheckPhyExceptionCase(UINT8 port, int resetClear);
static void __HDMI21_PHY_O24A0_SetPhyExceptionCase(UINT8 port, HDMI21_HAL_PHY_EXCEPTION_CASE_T phyCase, int isReverse);
static int 	__HDMI21_PHY_O24A0_Check_CRDone(UINT8 port);
static int  __HDMI21_PHY_O24A0_Check_RSDone(UINT8 port);
static int  __HDMI21_PHY_O24A0_IsOnboardPort(UINT8 port);

static int __HDMI21_PHY_O24A0_Check_EqCalDone(UINT8 port);
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

int HDMI21_PHY_O24A0_CheckDfeDone(UINT8 port)
{
	int ret = 0;

	int ch0DfeDone = 0;
	int ch1DfeDone = 0;
	int ch2DfeDone = 0;
	int ch3DfeDone = 0;

	if(gHDMI21RxHandler[port].phyInitiatedMode < HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
		HDMI20_PHY("WARNING[%d] : CheckDFEDone API entered in non-FRL 12G!!\n", port);

		ret = 1;
		return ret;
	}

	PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_5f);
	PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_5f, dfe_done_ch0, ch0DfeDone);
	PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_5f, dfe_done_ch1, ch1DfeDone);
	PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_5f, dfe_done_ch2, ch2DfeDone);
	PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_5f, dfe_done_ch3, ch3DfeDone);

	if(gHDMI21RxHandler[port].phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_FRL_6G_3L){
		ch3DfeDone = 1;
	}

	if((ch0DfeDone > 0) &&(ch1DfeDone > 0) &&(ch2DfeDone > 0) &&(ch3DfeDone > 0)) {

		HDMI20_PHY("PHY[%d] : Detected DFE DONE!! \n", port);


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

	return ret;
}

void HDMI21_PHY_O24A0_InitiateDfeCenter(UINT8 port)
{
	int ch0DfeDone = 0;
	int ch1DfeDone = 0;
	int ch2DfeDone = 0;
	int ch3DfeDone = 0;

	if(gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_CENTER_SWWA].value > 0) {
		HDMI20_PHY("PHY[%d] : Initiate Calculation of DFE Center Position!\n", port);
		HDMI21_PHY_O24A0_Update_TMDS_TCS_Value(port, 0);
		__HDMI21_PHY_O24A0_SetDfeResultCenter(port);
	}

	gHDMI21RxHandler[port].phyFrlSwWaState = 1;
}


/* IOCTL */
int HDMI21_PHY_O24A0_Rx_Get_PHYStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall)
{
	int ret = RET_ERROR;
	LX_HDMI_PHY_INFORM_T userdata;
	UINT32 tempData;
	UINT32 valuefor5V[HDMI21_NUM_OF_PORTS_O24] = {0,};
	int i;

	int deltaError = 0;
	int cedError = 0;
	int SyncRecovery = 0;
	int tcsError = 0;
	int isCrDone = 0;
	UINT8 isRsDone = 0;
	int updateTcsValue = 0;
	int deltaEye = 0;
	int dfeResult = 0;
	int phyErrorCounter = 0;

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
		for(i=0; i<HDMI21_NUM_OF_PORTS_O24; i++){
			userdata.hdmi_mode[i] = gHDMI21RxHandler[i].hwVideo.dvi;                // < hdmi/dvi mode
		}

		/* Step 2-2. 5V Info */
		/* SW W/A for webos Popup sign for SONY EXPERIA Z2*/
		if(gHDMI21RxDevVideoControler[HDMI21__HOLD_TIME_5V_DETECTION].value == 0){
			for(i=0; i<HDMI21_NUM_OF_PORTS_O24; i++){
				HDMI21_HAL_Rx_Get_Check5VLevelInfo(i, &valuefor5V[i], 1);
				if(valuefor5V[i] != 0) userdata.hdmi5v[i] = 1;
				else userdata.hdmi5v[i] = 0;
			}
		}
		else{
			for(i=0; i<HDMI21_NUM_OF_PORTS_O24; i++){
				if(gHDMI21RxHandler[i].connected5Vtime >= gHDMI21RxDevPhyControler[HDMI21__HOLD_TIME_5V_DETECTION].value) userdata.hdmi5v[i] = 1;
				else userdata.hdmi5v[i] = 0;
			}
		}

		if(updatePhyI2C > 0){
			for(i=0; i<HDMI21_NUM_OF_PORTS_O24; i++){
				if(userdata.hdmi5v[i] > 0){
					/* Read Errors */
					tcsError = HDMI21_PHY_O24A0_Check_TMDSError(i);
					SyncRecovery = HDMI21_PHY_O24A0_Check_SyncRecovery(i);
					isCrDone = __HDMI21_PHY_O24A0_Check_CRDone(i);
					isRsDone = __HDMI21_PHY_O24A0_Check_RSDone(i);
					cedError = HDMI21_PHY_O24A0_Check_CEDError(i);
					deltaError = HDMI21_PHY_O24A0_Check_DeltaError(i);
					deltaEye = HDMI21_PHY_O24A0_Check_DeltaEye(i);
					if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_UPDATE_PHY_DFE_RESULT].value > 0){
						dfeResult = HDMI21_PHY_O24A0_Check_DfeResult(i);
					}

					updateTcsValue = HDMI21_PHY_O24A0_Update_TMDS_TCS_Value(i, 0);
				}
			}
		}

		for(i=0; i<HDMI21_NUM_OF_PORTS_O24; i++){
			/* Step 2-3. HPD Info */
			userdata.hpd_out[i] = gHDMI21RxHandler[i].isHPD;		//	< HPD out status on each ports

			/* Step 2-4. TMDS Clk Info */	
			userdata.tmds_clock[i] = gHDMI21RxHandler[i].real_tmds_clk;				// Phy TMDS Clock

			/* Step 2-5. HPD Polarity Info */
			userdata.hpd_pol[i] = gHDMI21RxHandler[i].isHPDInverseMode;	

		}

		/* Step 2-6. PHY PDB */
		for(i=0; i<HDMI21_NUM_OF_PORTS_O24; i++){
			tempData = gHDMI21RxHandler[i].top_read(HDMI21_TOP_REG_AD_MAIN_PHY_CTRL);
			if((tempData & HDMI21_TOP_FIELD_O_REG_PHY_PDB) != 0) userdata.phy_pdb[i] = 1;
			else userdata.phy_pdb[i] = 0;
		}

		/* Step 2-7. PHY RSTN */
		/* None */

		for(i=0; i<HDMI21_NUM_OF_PORTS_O24; i++){
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

int HDMI21_PHY_O24A0_InitiatePhySystemCtrl(UINT8 port) 
{ 
	int ret = RET_ERROR; 

	do{ 
		HDMI20_PHY("[%s] Entered for port[%d]\n", __F__, port);

		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Mem allocate Phy Block #0 SHDW space */
		if((phyReg_o24a0[port].shdw.addr == NULL)){
			phyReg_o24a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_O24A0_T));

		}
		else {
			OS_Free((void *)phyReg_o24a0[port].shdw.addr);
			phyReg_o24a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_O24A0_T));
		}

		/* Mem allocate Phy Block #1 SHDW space */
		if((phyReg_B1_o24a0[port].shdw.addr == NULL)){
			phyReg_B1_o24a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B1_O24A0_T));

		}
		else {
			OS_Free((void *)phyReg_B1_o24a0[port].shdw.addr);
			phyReg_B1_o24a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B1_O24A0_T));
		}

		/* Mem allocate Phy Block #1 SHDW space */
		if((phyReg_B2_o24a0[port].shdw.addr == NULL)){
			phyReg_B2_o24a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B2_O24A0_T));

		}
		else {
			OS_Free((void *)phyReg_B2_o24a0[port].shdw.addr);
			phyReg_B2_o24a0[port].shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_PHY_REG_B2_O24A0_T));
		}

		/* ONLY FOR M23 */
		/* 2022/12/23 : SICDTV-11984-> For M23 SLT, we need lower gains for TMDS 6G.. reduce EQ strength for chip test */
		if( lx_board_opt() & LX_BOARD_OPT_SLT) {
			o24a0_phy_table[EQ_ICTRL_O24A0][HDMI_PHY_INITIATED_6G] = 0x3;
		}
	
		ret = RET_OK;
	} while(0);

	return ret;
}



void HDMI21_PHY_O24A0_UpdatePhyLockFlag(UINT8 port)
{
	int tcsDone = 0;
	int updateTcsValue = 0;
	int isTcsStable = 0;
	int isCrDone = 0;
	UINT8 isRsDone = 0;
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
	UINT32 frl_start_st = 0;
	UINT32 frl_start = 0;
	UINT32 __uD;
	HDMI21_SNPS_LINK_REG_0X584_T _r0;


	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
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

		//O24 TODO
		//need to check
		/* 2020/06/01 */
		if(__HDMI21_PHY_O24A0_ToggleFltStart(port, 0, 0, __L__ ) > 0) {
			__HDMI21_PHY_O24A0_ToggleFltStart(port, 0, 1, __L__);
		}

		/* Update Data */
		tcsDone = HDMI21_PHY_O24A0_Check_TCSDone(port);
		
		updateTcsValue = HDMI21_PHY_O24A0_Update_TMDS_TCS_Value(port, 0);
		isCrDone = __HDMI21_PHY_O24A0_Check_CRDone(port);
		isRsDone = __HDMI21_PHY_O24A0_Check_RSDone(port);

		tcsError = HDMI21_PHY_O24A0_Check_TMDSError(port);
		SyncRecovery = HDMI21_PHY_O24A0_Check_SyncRecovery(port);
		cedError = HDMI21_PHY_O24A0_Check_CEDError(port);
		deltaError = HDMI21_PHY_O24A0_Check_DeltaError(port);
		deltaEye = HDMI21_PHY_O24A0_Check_DeltaEye(port);
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_UPDATE_PHY_DFE_RESULT].value > 0){
			dfeResult = HDMI21_PHY_O24A0_Check_DfeResult(port);
		}


		/* Check Phy Lock */
		if(tcsDone >= 0){
			/* Update Flag */
			isPhyLocked = true;

			/* Execute any Phy Exception Case */
			if(gHDMI21RxDevPhyControler[HDMI21__PHY_ENABLE_PHY_EXCEPTION_CASE].value > 0){
				__HDMI21_PHY_O24A0_CheckPhyExceptionCase(port, 0);
			}
		}
	}while(0);

	if(port < HDMI21_NUM_OF_PORTS_O24){
		/* Update TCS State History */
		gPhyTcsStateHist[port][gPhyTcsStateHistIdx[port]] = gHDMI21RxHandler[port].phyTCSState;
		/* Increamnet TCS State History Idx */
		__HDMI21_PHY_O24A0_IncreaseTcsStateHistIdx(port);


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
			HDMI21_PHY_O24A0_CheckDfeDone(port);
		}
		else if((gHDMI21RxHandler[port].fsm_phy_lock > 0) && (isPhyLocked == true)  \
				&& (gHDMI21RxHandler[port].phyFrlSwWaState == 2) \
				&& (gHDMI21RxDevPhyControler[HDMI21__PHY_CH0_SSB_CHECK_ON].value > 0 )\
				&& (gHDMI21RxHandler[port].phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L))
		{

			if((gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_3].value & 0x1) != 0) { 

				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_47);
				PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_47, ch0_sr_ssb, ch0SrSsb);
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_48);
				PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_48, ch1_sr_ssb, ch1SrSsb);
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_49);
				PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_49, ch2_sr_ssb, ch2SrSsb);
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_4a);
				PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_4a, ch3_sr_ssb, ch3SrSsb);
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
				HDMI21_LINE_DBG(502, "PHY[%d] : FRL Mode detected Ch0SrSsb[0x%x] Match of [0x10]. [0x%x][0x%x][0x%x][0x%x]. State[%d]StartSTS[%d]\n",\
						port, ch0SrSsb, ch0SrSsb, ch1SrSsb, ch2SrSsb, ch3SrSsb, _r0.SCDC_FRL_START, _r0.FRL_START_STS);

				gHDMI21RxHandler[port].phyFrlSwWaState = 3;
				HDMI21_HAL_Rx_Set_CoreResetWithMask(&gHDMI21RxHandler[port], gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value);
			}
			else {
				HDMI21_LINE_DBG(502, "DBG[%d] : FRL Mode Checking Ch0SrSsb, but Ch0SrSsb value[0x%x] is not [0x10]. [0x%x][0x%x][0x%x][0x%x]\n",\
						port, ch0SrSsb, ch0SrSsb, ch1SrSsb, ch2SrSsb, ch3SrSsb);
			}
		}
		else if(isPhyLocked == false)
		{
			/* Only in FRL Modes */
			if(gHDMI21RxHandler[port].phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
				/* Check TCS State History */
				tcsStateMatchVal = __HDMI21_PHY_O24A0_CheckTcsStateHistMatchVal(port, gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_STATE_HIST_MATCH].value);

				/* Get FLT_UPDATE from SNPS Link */
				__uD = gHDMI21RxHandler[port].link_read(0x588);	memcpy((void *)&_r0, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X584_T));

				HDMI21_LINE_DBG(595, "DBG[%d] : Match Count[%d] FLT_UPDATE[%d] FRL_Start_ST[%d] FRL_Start[%d]\n",\
						port, tcsStateMatchVal, _r0.SCDC_FLT_UPDATE, _r0.FRL_START_STS , _r0.SCDC_FRL_START);

				if((tcsStateMatchVal == gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_STATE_HIST_DEPTH].value)&&(_r0.SCDC_FLT_UPDATE == 0)){
					PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_59);
					PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_59, flt_state, flt_state);
	
					HDMI21_LINE_DBG(595, "PHY[%d] : TCS State[%d] is Stuck [%d] times. Current FLT_State val [%d]. FLT_UPDATE[%d]\n", port,\
							gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_STATE_HIST_MATCH].value, tcsStateMatchVal, flt_state, _r0.SCDC_FLT_UPDATE);

					if(flt_state == gHDMI21RxDevPhyControler[HDMI21__PHY_FLT_STATE_MATCH].value) {
						if((gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_1].value & 0x1) != 0x0) {
							PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_59);
							PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x8);
							PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_5a);
							HDMI21_LINE_DBG(595, "PHY[%d]  : FLT State[%d] in TCS State stuck case. Execute #1. EQ Sucess Sel [8]->[7]\n", port, flt_state);

							PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_59);
							PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x7);
							PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_5a);
						}

						if((gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_1].value & 0x2) != 0x0) {
							HDMI21_LINE_DBG(595, "PHY[%d]  : FLT State[%d] in TCS State stuck case. Execute #2. Toggle DR RESETB\n", port, flt_state);
							__HDMI21_PHY_O24A0_ToggleDrResetB(port, 1);
							__HDMI21_PHY_O24A0_ToggleDrResetB(port, 0);
						}

						if((gHDMI21RxDevPhyControler[HDMI21__PHY_FRL_EQ_SWWA_OPTION_1].value & 0x4) != 0x0) {
							HDMI21_LINE_DBG(595, "PHY[%d]  : FLT State[%d] in TCS State stuck case. Execute #3. Toggle CR MODE SEL RESETB\n", port, flt_state);
							__HDMI21_PHY_O24A0_ToggleCrModeSelResetB(port, 1);
							__HDMI21_PHY_O24A0_ToggleCrModeSelResetB(port, 0);
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

									PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_99);
									PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, 0);
									PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_99);

									PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_66);
									PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_66,  flt_restart, 0x1);
									PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_66);

									HDMI21_LINE_DBG(595, "PHY[%d] : Send FLT Restart!\n", port);

									PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_66);
									PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_66,  flt_restart, 0x0);
									PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_66);

									HDMI21_PHY_O24A0_ToggleTCSEn(port, 0);
									HDMI21_PHY_O24A0_ToggleTCSEn(port, 1);


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
		if(port < HDMI21_NUM_OF_PORTS_O24){
			if( gHDMI21RxHandler[port].isPhyLocked != true ){
				__HDMI21_PHY_O24A0_CheckPhyExceptionCase(port, 1);
			}
		}
	}

	/* DBG PRINT */
	HDMI21_LINE_DBG(4242, "DBG %d : tcsDone[%d] / updateTcsValue[%d] / isTcsStable[%d]\n", port, tcsDone,updateTcsValue,isTcsStable);

	return;
}


/* IOCTL */
int HDMI21_PHY_O24A0_Rx_AccessPhy(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size)
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

		if(port >= HDMI21_NUM_OF_PORTS_O24){
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

int HDMI21_PHY_O24A0_Set_3G6G_Mode(UINT8 port, UINT8 isAuto, HDMI21_HAL_PHY_INITIATED_MODE_T mode, UINT8 isScrambling, UINT8 lowfreqGain)
{
	int ret = RET_ERROR;
	int wasEQmodeChanged = 0;
	UINT32 flt_state = 0;
	int isOnboard = 0;
	UINT32 __tcsManVal[4];
	UINT32 __frlRsGain[4];
	UINT32 __d = 0;
	HDMI_PHY_INIT_MODE_T local_mode = HDMI_PHY_INITIATED_3G_M3;

	/* Get FRL_NO_RETRAIN */
	UINT32 __uD;
	HDMI21_SNPS_LINK_REG_0X58C_T _r2;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Read FRL No Retrain : 0x58C on O24A0, 0x590 on O24A0 */
		__uD = gHDMI21RxHandler[port].link_read(0x590);	memcpy((void *)&_r2, &__uD, sizeof(HDMI21_SNPS_LINK_REG_0X58C_T));
		if(_r2.SCDC_FLT_NO_RETRAIN != 0) { gHDMI21RxHandler[port].isPhyFrlCtsMode = 1; }

		/* Override CTS mode, when debugger is set */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_FORCE_FRL_CTS_MODE].value == 2) {
			gHDMI21RxHandler[port].isPhyFrlCtsMode = 1;
		}
		else if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_FORCE_FRL_CTS_MODE].value == 0) {
			gHDMI21RxHandler[port].isPhyFrlCtsMode = 0;
		}

		local_mode = _CvtPhyMode(mode);
		if( local_mode == HDMI_PHY_INITIATED_ERROR )
		{
			HDMI20_PHY("Invalid phy-initiated mode..!\n");
			break;
		}

		if( (local_mode == HDMI_PHY_INITIATED_FRL_10G_4L) &&  (gHDMI21RxHandler[port].isPhyFrlCtsMode == 1) ){
			local_mode = HDMI_PHY_INITIATED_FRL_10G_CTS;	
		} else if ( (local_mode == HDMI_PHY_INITIATED_FRL_12G_4L) &&  (gHDMI21RxHandler[port].isPhyFrlCtsMode == 1) ){
			local_mode = HDMI_PHY_INITIATED_FRL_12G_CTS;	
		}
				
		/* Clear Phy Exception case history */
		if(gHDMI21RxDevPhyControler[HDMI21__PHY_ENABLE_PHY_EXCEPTION_CASE].value > 0){
			__HDMI21_PHY_O24A0_CheckPhyExceptionCase(port, 1);
		}


		/* 2021/12/14 : Denon+PS5 */
		gHDMI21RxHandler[port].fsm_phy_lock = 0;
		/* Reset HDCP2.2 Engine & Start HDCP2.2 Auth  */
		if(gHDMI21RxHandler[port].gWasHDCP22Written > 0) {
			/* HDCP2.2 */
			HDMI21_HDCP23_Module_Set_HlcReset(port, 0);
		}
		/* End of Denon+PS5 */

		/* Check if this port is Onboard port */
		isOnboard = __HDMI21_PHY_O24A0_IsOnboardPort(port);
		//O24A0 BringUp
		isOnboard = 0;

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

			/* 2021/09/14 : FRL Rate can be sent for retraining for the same rate. Need to Reset OffSet Calibration for FRL retraining*/
			if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
				wasEQmodeChanged = 2;
			}
		}

		if( mode >= HDMI_PHY_INITIATED_FRL_3G_3L ){
			__HDMI21_PHY_O24A0_ToggleFltStart(port, 0, 1, __L__);
		}

		/* DFE Center SW WA */
		gHDMI21RxHandler[port].phyFrlSwWaState = 0;


		/* 2021/09/14 : I2C_DFE_LEVEL_X_XX_MODE values are set from LINK TCS done ISR code. 
		 * 				Since I2C_DFE_LEVEL_A_XX_MODE values are not defined in devctrl, it needs to be reseted to default values before PHY SET */
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_81);
		PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_81, i2c_dfe_level_a_11_mode, 0x0);
		PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_81, i2c_dfe_level_a_01_mode, 0x0);
		PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_81);


		/* Flag for 3G/6G */
		gHDMI21RxHandler[port].phyInitiatedMode = mode;
		local_mode = _CvtPhyMode(mode);
		if( local_mode == HDMI_PHY_INITIATED_ERROR )
		{
			HDMI20_PHY("Invalid phy-initiated mode..!\n");
			break;
		}		

		if( (local_mode == HDMI_PHY_INITIATED_FRL_10G_4L) &&  (gHDMI21RxHandler[port].isPhyFrlCtsMode == 1) ){
			local_mode = HDMI_PHY_INITIATED_FRL_10G_CTS;	
		} else if ( (local_mode == HDMI_PHY_INITIATED_FRL_12G_4L) &&  (gHDMI21RxHandler[port].isPhyFrlCtsMode == 1) ){
			local_mode = HDMI_PHY_INITIATED_FRL_12G_CTS;	
		}

		/* DH's For loop for PHY reg setting */
		HDMI_PHY_Set_Reg_Table(port, 1, local_mode);


		//Hard Coding (audio)
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_4b);
		if(mode ==  HDMI21_HAL_PHY_INITIATED_6G){
			PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_val, 0x3);
			PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_mode, 0x1);	
		}
		else{
			PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_val, 0x0);
			PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_mode, 0x0);	
		}
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_4b);

		/* 2020/08/19 */
		//Hard Coding
		if((((mode >= HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) && (port == 3)))\
				|| ((mode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) && (port == 2))){
			PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_34);
			PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_34, cr_man_aud_ref_div, 1);
			PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_34, cr_i2c_aud_ref_div_mode, 1);
			PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_34);

			PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_4b);
			PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_mode, 1);
			PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_4b, pll_aud_man_val, 3);
			PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_4b);
		}
		else{
			PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_34);
			PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_34, cr_man_aud_ref_div, 0);
			PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_34, cr_i2c_aud_ref_div_mode, 0);
			PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_34);
		}

		//Hard Coding
		if((gHDMI21RxHandler[port].top_read(0xB0) & 0x20000000) != 0) {
			PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_07);
			PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_07, mode_4ch_val, 0x1);
			PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_07, mode_4ch_man, 0x1);
			PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_07);
		}

		/* 0x39 : EQ_CAL_MODE_VAL 0->1 : Redo EQ offset calibration when lowfreqGain(RS) value changes */
		if(wasEQmodeChanged){
			HDMI21_PHY_O24A0_Reset_EqOffsetCalibration(port, 1, __L__);
			HDMI21_PHY_O24A0_Reset_EqOffsetCalibration(port, 0, __L__);
		}

		/* 2021/05/12 won.hur : DH1128 code changes did not consider FLT_START signal, as well as eq-success-sel settings
		 * 						which caused PS5 to not work */
		
		if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {

			PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_5a);
			PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_5a, eq_success_sel, 0x7);
			PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_5a);

			if(mode >= HDMI21_HAL_PHY_INITIATED_FRL_8G_4L) {
				// 20240108 : SW W/R for Apple PC
				if(gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DISABLE].value == 0){
					PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_5a);
					PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_5a, eq_fail_sel, 0x4);
					PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_5a);
				}
				if((gHDMI21RxHandler[port].isFLT != 1) && (gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DISABLE].value == 0)){
					HDMI20_PRINT("DBG[%d] : FRL mode. isFLT change %d -> 1\n", port, gHDMI21RxHandler[port].isFLT);
					gHDMI21RxHandler[port].isFLT = 1;
				}else if(gHDMI21RxDevPhyControler[HDMI21__PHY_RS_SCAN_RETRY_DISABLE].value != 0){
					HDMI20_PRINT("DBG[%d] : RS Scan retry Force disable!! \n", port);
				}
			}else{
				if(gHDMI21RxHandler[port].isFLT >= 1){
					gHDMI21RxHandler[port].isFLT = 0;
					HDMI20_PRINT("DBG[%d] : 6G mode. isFLT change 1 -> 0(%d)\n", port, gHDMI21RxHandler[port].isFLT);
				}
			}

			HDMI21_LINE_DBG(502, "PHY[%d][%s] : FLT State val[0x%x]. Set eq_success_sel to [0x7]\n", port, phymode_type_to_str(mode), flt_state);

			__HDMI21_PHY_O24A0_ToggleFltStart(port, 1, 1, __L__);
		}else{
			if(gHDMI21RxHandler[port].isFLT >= 1){
				gHDMI21RxHandler[port].isFLT = 0;
				HDMI20_PRINT("DBG[%d] : TMDS mode. isFLT change 1 -> 0(%d)\n", port, gHDMI21RxHandler[port].isFLT);
			}
		}

		//RESETB_ALL/////////////////////////////////////////////////////////////////////////////////////////////
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_00);
		PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_00, resetb_all, 0x1);
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_00);
		//ODT_PDB////////////////////////////////////////////////////////////////////////////////////////////////
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_48);
		PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_48, eq_i2c_odt_pdb_mode, 0x1);
		PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_48, eq_man_odt_pdb, 0x1);
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_48);


		/* 2021/09/14 : Need to get rid of unnessessary duplicate PHY mode set calls : Poll/ISR unsync issue */
		gHDMI21RxHandler[port].frlRateRcv = 0;

		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI21_PHY_O24A0_IsPhyPdbPowerOn(UINT8 port)
{
	UINT32 data;
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
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

int HDMI21_PHY_O24A0_ControlPhyPDB(UINT8 port, BOOLEAN bOnOff)
{
	UINT32 data, __devid;
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;;
		}

		HDMI21_LINE_DBG(502, "Notice %d : Phy PDB Control[%d]\n", port, (int)bOnOff);

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

		/* Only for M23/O24 : Need to consider this when porting to other SoC */
		/* PDB control when attaching and detaching cables (PHY reg initialization) */
		HDMI21_PHY_O24A0_REG_RD(0xC8D71010, data);
		if(port == 0) {
			if(bOnOff)	{	data &= (~0x2);}
			else		{	data |= ( 0x2);}
		}
		else if(port == 1) {
			if(bOnOff)	{	data &= (~0x4);}
			else		{	data |= ( 0x4);}
		}
		else if(port == 2) {
			if(bOnOff)	{	data &= (~0x8);}
			else		{	data |= ( 0x8);}
		}
		else if(port == 3) {
			if(bOnOff)	{	data &= (~0x10);}
			else		{	data |= ( 0x10);}
		}
		HDMI21_PHY_O24A0_REG_WR(0xC8D71010, data);

		ret = RET_OK;
	}while(0);

	return ret;
}


int HDMI21_PHY_O24A0_Reset_EqOffsetCalibration(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		HDMI21_LINE_DBG(502, "PHY[%d] : Offset Calibration [%s]. Caller[%d]\n", port, isReset?"Reset Activate":"Reset Clear", callerId); 

		/* 0x39 (hdmi_phy_addr_39) */
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_47);
		if(isReset)	{PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_47, eq_cal_mode_val, 0x0);}
		else 		{PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_47, eq_cal_mode_val, 0x1);}
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_47);

		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI21_PHY_O24A0_PowerControl_PLLPDB(UINT8 port, UINT8 isDown, UINT32 callerId)
{
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;;
		}

		HDMI21_LINE_DBG(502, "PHY[%d] :  CR PDB Power Ctrl[%s]. Caller[%d]\n", port, isDown?"Down":"Up", callerId); 

		/* hdmi_phy_addr_03 */
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_02);
		if(isDown)	{PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_02, cr_pll_pdb, 0x0);}
		else 		{PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_02, cr_pll_pdb, 0x1);}
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_02);

		ret = RET_OK;
	}while(0);

	return ret;
}


int HDMI21_PHY_O24A0_Reset_PLLPDB(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;;
		}

		HDMI21_LINE_DBG(502, "Notice %d : Phy PLL PDB Reset : [%s]. Caller[%d]\n", port, isReset?"Reset Activate":"Reset Clear", callerId); 

		/* CR_PLL_RESETB_PDB */
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_02);
		if(isReset)	{PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_02, cr_pll_resetb, 0x0);}
		else 		{PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_02, cr_pll_resetb, 0x1);}
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_02);

		ret = RET_OK;
	}while(0);

	return ret;
}

static int __HDMI21_PHY_O24A0_Check_CRDone(UINT8 port)
{
	int ret = RET_ERROR;
	int isCrDone = 0;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_3e);
		PHY_REG_O24A0_Rd01(port, hdmi_phy_addr_3e, cr_done, isCrDone);

		if(isCrDone)	{ gHDMI21RxHandler[port].phyCrDone = TRUE; ret = RET_OK; }
		else 			{ gHDMI21RxHandler[port].phyCrDone = FALSE; ret = RET_ERROR; }

	} while(0);

	return ret;
}

static int __HDMI21_PHY_O24A0_Check_RSDone(UINT8 port)
{
	int ret =  RET_ERROR;
	UINT8 isRsDone = 0;
	int i;
	UINT8 rs_scan_done_ch[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	UINT8 __rs_scan_ch[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY]= {0,};
	
	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step1. Check RS Done */
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_2b);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_2b, rs_scan_done_ch3, rs_scan_done_ch[3]);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_2b, rs_scan_done_ch2, rs_scan_done_ch[2]);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_2b, rs_scan_done_ch1, rs_scan_done_ch[1]);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_2b, rs_scan_done_ch0, rs_scan_done_ch[0]);

		isRsDone |= (rs_scan_done_ch[3] << 3);
		isRsDone |= (rs_scan_done_ch[2] << 2);
		isRsDone |= (rs_scan_done_ch[1] << 1);
		isRsDone |= (rs_scan_done_ch[0]);

		if( rs_scan_done_ch[3] == 1 && rs_scan_done_ch[2] == 1 && rs_scan_done_ch[1] == 1 && rs_scan_done_ch[0] )
		{
			gHDMI21RxHandler[port].phyRsDone = TRUE;
		} else {
			gHDMI21RxHandler[port].phyRsDone = FALSE;
		}

		/* Update RS Result */
		PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_1a);
		PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_1a, eq_rs_ch0, __rs_scan_ch[0]);
		PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_1b);
		PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_1b, eq_rs_ch1, __rs_scan_ch[1]);
		PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_1c);
		PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_1c, eq_rs_ch2, __rs_scan_ch[2]);
		PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_1d);
		PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_1d, eq_rs_ch3, __rs_scan_ch[3]);


		for(i=0; i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY; i++)
		{
			gHDMI21RxHandler[port].phyRsResult[i] = __rs_scan_ch[i];
		}

	}while(0);

	return isRsDone;
}

int HDMI21_PHY_O24A0_Check_SyncRecovery(UINT8 port)
{

	int ret = RET_ERROR;
	int phySyncRecovery[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int i;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
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
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_14);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_14, tot_sync_recover_ch0, phySyncRecovery[0]);

			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_15);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_15, tot_sync_recover_ch1, phySyncRecovery[1]);

			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_16);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_16, tot_sync_recover_ch2, phySyncRecovery[2]);

			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_17);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_17, tot_sync_recover_ch3, phySyncRecovery[3]);
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


int HDMI21_PHY_O24A0_Check_TMDSError(UINT8 port)
{

	int ret = RET_ERROR;
	int phyTMDSError[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyErrorCounter = 0;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Update Error Counter */
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_13);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_13, err_update, phyErrorCounter);


		/* Step 1. Check TCS Done */
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_18);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_18, tot_tmds_error_ch0, phyTMDSError[0]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_19);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_19, tot_tmds_error_ch1, phyTMDSError[1]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_1a);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_1a, tot_tmds_error_ch2, phyTMDSError[2]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_1b);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_1b, tot_tmds_error_ch3, phyTMDSError[3]);

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

int HDMI21_PHY_O24A0_Check_DeltaEye(UINT8 port)
{

	int ret = RET_ERROR;
	int phyDeltaPlus[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int phyDeltaMinus[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_94);
		PHY_REG_B1_O24A0_Rd02(port, hdmi_phy_addr_94, delta_plus_ch0, phyDeltaPlus[0], delta_minus_ch0, phyDeltaMinus[0]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_95);
		PHY_REG_B1_O24A0_Rd02(port, hdmi_phy_addr_95, delta_plus_ch1, phyDeltaPlus[1], delta_minus_ch1, phyDeltaMinus[1]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_96);
		PHY_REG_B1_O24A0_Rd02(port, hdmi_phy_addr_96, delta_plus_ch2, phyDeltaPlus[2], delta_minus_ch2, phyDeltaMinus[2]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_97);
		PHY_REG_B1_O24A0_Rd02(port, hdmi_phy_addr_97, delta_plus_ch3, phyDeltaPlus[3], delta_minus_ch3, phyDeltaMinus[3]);

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

int HDMI21_PHY_O24A0_Check_DeltaError(UINT8 port)
{

	int ret = RET_ERROR;
	int phyDeltaError[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_14);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_14, tot_delta_error_ch0, phyDeltaError[0]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_15);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_15, tot_delta_error_ch1, phyDeltaError[1]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_16);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_16, tot_delta_error_ch2, phyDeltaError[2]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_17);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_17, tot_delta_error_ch3, phyDeltaError[3]);

		/* Step 2. Put in data */
		gHDMI21RxHandler[port].phyDeltaError[0] = phyDeltaError[0];
		gHDMI21RxHandler[port].phyDeltaError[1] = phyDeltaError[1];
		gHDMI21RxHandler[port].phyDeltaError[2] = phyDeltaError[2];
		gHDMI21RxHandler[port].phyDeltaError[3] = phyDeltaError[3];

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_PHY_O24A0_Check_CEDError(UINT8 port)
{

	int ret = RET_ERROR;
	int phyCEDError[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_18);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_18, tot_ced_error_ch0, phyCEDError[0]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_19);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_19, tot_ced_error_ch1, phyCEDError[1]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_1a);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_1a, tot_ced_error_ch2, phyCEDError[2]);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_1b);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_1b, tot_ced_error_ch3, phyCEDError[3]);

		/* Step 2. Put in data */
		gHDMI21RxHandler[port].phyCEDError[0] = phyCEDError[0];
		gHDMI21RxHandler[port].phyCEDError[1] = phyCEDError[1];
		gHDMI21RxHandler[port].phyCEDError[2] = phyCEDError[2];
		gHDMI21RxHandler[port].phyCEDError[3] = phyCEDError[3];

		ret = phyCEDError[0] + phyCEDError[1] + phyCEDError[2] + phyCEDError[3];
	} while(0);

	return ret;
}

int HDMI21_PHY_O24A0_Check_DfeResult(UINT8 port)
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
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		for(i=0;i<HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY;i++){
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_3b);
			PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_3b, dfe_result_ch_sel, i);
			PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_3b);

			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_35);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_35, dfe_level_a_01, phyDfeA01[i]);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_36);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_36, dfe_level_a_11, phyDfeA11[i]);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_37);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_37, dfe_level_b1, phyDfeB1[i]);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_38);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_38, dfe_level_b2, phyDfeB2[i]);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_39);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_39, dfe_level_b3, phyDfeB3[i]);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_3a);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_3a, dfe_level_b4, phyDfeB4[i]);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_3a);
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_3a, dfe_level_b5, phyDfeB5[i]);

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


int HDMI21_PHY_O24A0_Check_TCSDone(UINT8 port)
{

	int ret = RET_ERROR;
	int isTcsDone= 0;
	UINT32 fail_ch0, fail_ch1, fail_ch2, fail_ch3;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}


		/* Step 1. Check TCS Done */
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_2c);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_2c, tcs_done, isTcsDone);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch0, fail_ch0);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch1, fail_ch1);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch2, fail_ch2);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_2c, tcs_fail_ch3, fail_ch3);

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

		/*
		//TODO: O24A0
		if((gHDMI21PhyFakeTcsDone_O24[port] > 0) && (gHDMI21RxHandler[port].phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L)) {
			ret = RET_OK;
		}
		*/

	} while(0);

	return ret;
}




UINT8 HDMI21_PHY_O24A0_Get_TMDS_FREQ(UINT8 port, int isMSB)
{
	UINT8 tmds_value = 0;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		//O24A0 Name changed
		//tmds_freq_15_8: tmds_freq_2
		//tmds_freq_7_0:  tmds_freq_1
		if(isMSB){
			PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_3a); 
			PHY_REG_O24A0_Rd01(port, hdmi_phy_addr_3a, tmds_freq_2, tmds_value);
		}
		else{
			PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_3b); 
			PHY_REG_O24A0_Rd01(port, hdmi_phy_addr_3b, tmds_freq_1, tmds_value);
		}

	} while(0);

	return tmds_value;
}

void HDMI21_PHY_O24A0_UpdatePhyTMDSclock(UINT8 port)
{
	UINT32 tmdsVal;
	int isManualEQ = 0;
	HDMI_PHY_INIT_MODE_T local_mode = HDMI_PHY_INITIATED_3G_M3;

	/* Port defence */
	if(port >= HDMI21_NUM_OF_PORTS_O24){
		HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
		return;
	}

	/* Check for Manual EQ */
	if ( port == 3 )     { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P3_ENABLE_MANUAL_EQ].value; }
	else if ( port == 2) { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P2_ENABLE_MANUAL_EQ].value; }
	else if ( port == 1) { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P1_ENABLE_MANUAL_EQ].value; }
	else				 { isManualEQ = gHDMI21RxDevPhyControler[HDMI21__PHY_P0_ENABLE_MANUAL_EQ].value; }


	/* Calculate */
	tmdsVal = ((((UINT32)HDMI21_PHY_O24A0_Get_TMDS_FREQ(port, 1) & 0x000000FF)<<8) | ((UINT32)HDMI21_PHY_O24A0_Get_TMDS_FREQ(port, 0) & 0x000000FF));

	/* Range Detector for exception case :
	 * [HDMI 3G Mode]                     [HDMI 6G Mode
	 *  25MHz ~ 40MHz  : Mode 0			  None
	 *  40MHz ~ 80MHz  : Mode 1
	 *  80MHz ~ 160MHz : Mode 2
	 * 160MHz ~ 340MHz : Mode 3 */
	if(gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_ENABLE_RANGE_EQ].value > 0){

		if(gHDMI21RxHandler[port].phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_6G) {
			gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange = -1;
			gHDMI21RxHandler[port].phyPrevTMDSExceptionRange = -1;
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


		if(gHDMI21RxHandler[port].phyInitiatedMode < HDMI21_HAL_PHY_INITIATED_6G) {
			if(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange != (gHDMI21RxHandler[port].phyPrevTMDSExceptionRange)){

				do { 
					HDMI21_LINE_DBG(4243, "PHY[%d] :TMDS Range Changed from [%d]->[%d]\n", port, gHDMI21RxHandler[port].phyPrevTMDSExceptionRange, gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange);

					local_mode = _CvtExceptRange(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange);
					if( local_mode == HDMI_PHY_INITIATED_ERROR)
					{
						break;
					}

					/* 2020/06/04 : DG Kim */
					PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_81);
					PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_81, i2c_dfe_level_a_11_mode, 0x0);
					PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_81, i2c_dfe_level_a_01_mode, 0x0);
					PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_81);

					PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_5a);
					PHY_REG_B1_O24A0_Wr02(port, hdmi_phy_addr_5a,\
							ana_cdr_sel,	o24a0_phy_table[ANA_CDR_SEL_O24A0][local_mode],\
							cdr_fltr_ctrl,	o24a0_phy_table[CDR_FLTR_CTRL_O24A0][local_mode] );
					PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_5a);

					PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_9c);
					PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_9c, delta_scan2_mode, o24a0_phy_table[DELTA_SCAN2_MODE_O24A0][local_mode]);
					PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_9c);

					PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_9b);
					PHY_REG_B1_O24A0_Wr02(port, hdmi_phy_addr_9b, i2c_delta_sample_mode, 0x0, i2c_delta_sample, 0x0);
					PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_9b);

					PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_b8);
					PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_b8, tcs_err_sel, o24a0_phy_table[TCS_ERR_SEL_O24A0][local_mode]);
					PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_b8);

					PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_2f);
					PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_2f, dr_n2, o24a0_phy_table[DR_N2_O24A0][local_mode]);
					PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_2f);

					PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_8c);
					PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_8c, i2c_delta_cdr_val, o24a0_phy_table[I2C_DELTA_CDR_VAL_O24A0][local_mode]);
					PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_8c, i2c_delta_cdr_mode, o24a0_phy_table[I2C_DELTA_CDR_MODE_O24A0][local_mode]);
					PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_8c);

					PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_04);
					PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch3, o24a0_phy_table[DR_CLK_INV_CH3_O24A0][local_mode]);
					PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch2, o24a0_phy_table[DR_CLK_INV_CH2_O24A0][local_mode]);
					PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch1, o24a0_phy_table[DR_CLK_INV_CH1_O24A0][local_mode]);
					PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_04, dr_clk_inv_ch0, o24a0_phy_table[DR_CLK_INV_CH0_O24A0][local_mode]);
					PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_04);

					//O24A0 Add
					PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_b9);
					PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_b9, tcs_divide_method, o24a0_phy_table[TCS_DIVIDE_METHOD_O24A0][local_mode]);
					PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_b9);

				} while(0);

				/* Update TMDS Range Flag */
				gHDMI21RxHandler[port].phyPrevTMDSExceptionRange = gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange;

				/* Toggle TCS EN */
				HDMI21_PHY_O24A0_ToggleTCSEn(port, 0);
				HDMI21_PHY_O24A0_ToggleTCSEn(port, 1);
			}
		}
	}

	if((tmdsVal == 0) && (tmdsVal != gHDMI21RxHandler[port].phy_tmds_clk)){
		HDMI21_LINE_DBG(939, "DBG[%d] : TMDS went to ZERO![%d]->[%d]\n", port, gHDMI21RxHandler[port].phy_tmds_clk, tmdsVal);

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

int HDMI21_PHY_O24A0_Update_TMDS_TCS_Value(UINT8 port, int isClear)
{

	int ret = RET_ERROR;
	int i;
	int tcs_min[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int tcs_max[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0xff, 0xff, 0xff, 0xff};
	int tcs_diff[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	int tcs_result[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	UINT32 __tcs_state = 0;

	//O24A0 Added
	UINT32 __tcs_state_ch0 = 0;
	UINT32 __tcs_state_ch1 = 0;
	UINT32 __tcs_state_ch2 = 0;
	UINT32 __tcs_state_ch3 = 0;


	do{
		/* Port defence */
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(isClear){
			/* Step 1. Memset TCS value */
			memset((void *)&gHDMI21RxHandler[port].phyTCSDiff, 0, (sizeof(int) * HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY));
			memset((void *)&gHDMI21RxHandler[port].phyTCSMin,  0, (sizeof(int) * HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY));
			memset((void *)&gHDMI21RxHandler[port].phyTCSMax,  0, (sizeof(int) * HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY));
			memset((void *)&gHDMI21RxHandler[port].phyTCSResult,  0, (sizeof(int) * HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY));
			memset((void *)&gHDMI21RxHandler[port].phyRsResult, 0, (sizeof(UINT8) * HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY));
		}
		else{
			if(gHDMI21RxHandler[port].phyCurrentTMDSExceptionRange >= 0){
				/* Step 1. Check TCS min for every TMDS channel */
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_20); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_20, cs_min_ch0, tcs_min[0]);
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_22); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_22, cs_min_ch1, tcs_min[1]);
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_24); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_24, cs_min_ch2, tcs_min[2]);
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_26); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_26, cs_min_ch3, tcs_min[3]);

				/* Step 2. Check TCS Max for every TMDS channel */
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_21); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_21, cs_max_ch0, tcs_max[0]);
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_23); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_23, cs_max_ch1, tcs_max[1]);
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_25); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_25, cs_max_ch2, tcs_max[2]);
				PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_27); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_27, cs_max_ch3, tcs_max[3]);
			}
			else {
				/* Step 1. Check TCS min for every TMDS channel */
				PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_f4); PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_f4, delta_cs_min_ch0, tcs_min[0]);
				PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_f6); PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_f6, delta_cs_min_ch1, tcs_min[1]);
				PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_f8); PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_f8, delta_cs_min_ch2, tcs_min[2]);
				PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_fa); PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_fa, delta_cs_min_ch3, tcs_min[3]);

				/* Step 2. Check TCS Max for every TMDS channel */
				PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_f5); PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_f5, delta_cs_max_ch0, tcs_max[0]);
				PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_f7); PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_f7, delta_cs_max_ch1, tcs_max[1]);
				PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_f9); PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_f9, delta_cs_max_ch2, tcs_max[2]);
				PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_fb); PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_fb, delta_cs_max_ch3, tcs_max[3]);
			}

			/* Step 3. Check TCS Result */
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_1c); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_1c, cs_out_ch0, tcs_result[0]);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_1d); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_1d, cs_out_ch1, tcs_result[1]);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_1e); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_1e, cs_out_ch2, tcs_result[2]);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_1f); PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_1f, cs_out_ch3, tcs_result[3]);

			/* Step 4. Check TCS State */
			//O24A0 TODO
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_31); 
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_31, tcs_state_ch0, __tcs_state_ch0);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_32); 
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_32, tcs_state_ch1, __tcs_state_ch1);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_33); 
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_33, tcs_state_ch2, __tcs_state_ch2);
			PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_34); 
			PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_34, tcs_state_ch3, __tcs_state_ch3);

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

			//O24A0
			__tcs_state |= (__tcs_state_ch0 & 0xFF);
			__tcs_state |= ((__tcs_state_ch1 & 0xFF) << 8);
			__tcs_state |= ((__tcs_state_ch2 & 0xFF) << 16);
			__tcs_state |= ((__tcs_state_ch3 & 0xFF) << 24);
			gHDMI21RxHandler[port].phyTCSState = __tcs_state;
		}
		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_PHY_O24A0_ToggleTCSEn(int port, int isSet)
{
	HDMI20_PHY("PHY[%d] : TCS [%s]\n", port, isSet?"Enable":"Disable");

	if(isSet) {
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_O24A0_Wr02(port, hdmi_phy_addr_03, tcs_en_man_mode, 0x1, tcs_en_man_val, 0x1);
		PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_03);

		/* 2019/12/18 : HDCP1.4 */
		HDMI21_HAL_Rx_Set_CoreResetWithMask(&gHDMI21RxHandler[port], gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_TOGGLE].value);
	}
	else{
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_O24A0_Wr02(port, hdmi_phy_addr_03, tcs_en_man_mode, 0x1, tcs_en_man_val, 0x0);
		PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_03);
	}


	return 0;
}


int HDMI21_PHY_O24A0_Rx_Initiate_Phy(int port, HDMI21_HAL_PHY_INITIATED_MODE_T mode)
{
	int ret = RET_ERROR;
	UINT8 lowfreqGain = 0;
	int isManualEQ = 0;
	UINT32 __tcsManVal[4];
	int isOnboard = 0;
	HDMI_PHY_INIT_MODE_T local_mode = HDMI_PHY_INITIATED_3G_M3;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		if(gHDMI21RxHandler[port].initiated == 0){
			HDMI20_ERROR("Device handler was not initiated.\n");
			break;
		}

		/* Check for Onbaord HDMI source */
		//isOnboard = __HDMI21_PHY_O24A0_IsOnboardPort(port);
		//O24A0 - Disable Onboard
		isOnboard = 0;

		/* Always Initiate this on cable connect */
		gHDMI21RxHandler[port].isPhyFrlCtsMode = 0;

		/* Step 1 : PHY PDB=1, PHY_I2C_RSNT = 1 */
		if(HDMI21_PHY_O24A0_IsPhyPdbPowerOn(port) < 0){
			HDMI20_PHY("PHY[%d] : Phy PDB was Low but 5V High. Set PHY PDB to HIGH\n", port);
			HDMI21_PHY_O24A0_ControlPhyPDB(port, 1);
		}
	
		/* 2019/10/17 : Reset TCS State History & Idx */
		memset((void *)&gPhyTcsStateHist[port], 0xFF, sizeof(UINT32) * HDMI21_PHY_TCS_HIST_HISTORY_DEPTH);
		gPhyTcsStateHistIdx[port] = 0;

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
		local_mode = _CvtPhyMode(mode);
		if( local_mode == HDMI_PHY_INITIATED_ERROR ) {
			HDMI20_PHY("Invalid phy-initiated mode..!\n");	
			break;
		}

		HDMI20_PHY("PHY[%d][Onboard:%d] : Initate Phy[%s](RS Gain[0x%x])\n",port, isOnboard,phymode_type_to_str(mode), lowfreqGain);

		/* 2020/03/31 : to prevent side-effects from Low Power Mode */
		if((gHDMI21RxHandler[port].top_read(0xb0) & 0x20000000) != 0) {
			PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_11);
			PHY_REG_O24A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch0_man, 0x1, eq_pdb_ch0_val, 0x1);
			PHY_REG_O24A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch1_man, 0x1, eq_pdb_ch1_val, 0x1);
			PHY_REG_O24A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch2_man, 0x1, eq_pdb_ch2_val, 0x1);
			PHY_REG_O24A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch3_man, 0x1, eq_pdb_ch3_val, 0x1);
			PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_11);
		}
		else {
			PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_11);
			PHY_REG_O24A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch0_man, 0x0, eq_pdb_ch0_val, 0x0);
			PHY_REG_O24A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch1_man, 0x0, eq_pdb_ch1_val, 0x0);
			PHY_REG_O24A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch2_man, 0x0, eq_pdb_ch2_val, 0x0);
			PHY_REG_O24A0_Wr02(port, hdmi_phy_addr_11, eq_pdb_ch3_man, 0x0, eq_pdb_ch3_val, 0x0);
			PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_11);
		}

		PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_02);
		PHY_REG_B2_O24A0_Wr02(port, hdmi_phy_addr_02, pdb_ch0_man, 0x0, pdb_ch0_val, 0x0);
		PHY_REG_B2_O24A0_Wr02(port, hdmi_phy_addr_02, pdb_ch1_man, 0x0, pdb_ch1_val, 0x0);
		PHY_REG_B2_O24A0_Wr02(port, hdmi_phy_addr_02, pdb_ch2_man, 0x0, pdb_ch2_val, 0x0);
		PHY_REG_B2_O24A0_Wr02(port, hdmi_phy_addr_02, pdb_ch3_man, 0x0, pdb_ch3_val, 0x0);
		PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_02);

		/* 2021/11/16 */
		PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_8b);
		PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_8b, idx_max_lock, 0x0);
		PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_8b);



		/* 2019/11/06 */
		HDMI21_PHY_O24A0_PowerControl_PLLPDB(port, 1, __L__);

		/* 2019/10/22 */
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_03);
		PHY_REG_B1_O24A0_Wr02(port, hdmi_phy_addr_03, tcs_en_man_mode, 0x0, tcs_en_man_val, 0x0);
		PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_03);

		/* 0x20 : 0x02 (MANUAL HDMI20_MODE = 0) / 0xAD : 0xA0 (DISABLE_DECORDER/SCR_MAN_OFF) / 0x5D : 0x06(EQ_RS_MAN=6)... */
		HDMI21_PHY_O24A0_Set_3G6G_Mode(port, 0, mode, mode, lowfreqGain);

		
		/* 2019/11/04 : DK Kim said to have this set here on top of PDB RESET_ALL */
		HDMI21_PHY_O24A0_PowerControl_PLLPDB(port, 0, __L__);

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_PHY_O24A0_CheckEqCalDone(int port)
{
	int ret = 0;
	UINT32 __d = 0;

	PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_46);
	PHY_REG_O24A0_Rd01(port, hdmi_phy_addr_46, eq_cal_done, __d);

	/* Check Result */
	if(__d > 0) ret = 1;
	
	return ret;
}


static void __HDMI21_PHY_O24A0_SetPhyExceptionCase(UINT8 port, HDMI21_HAL_PHY_EXCEPTION_CASE_T phyCase, int isReverse)
{
	do{
		/* Port Defence */
		if(port >= HDMI21_NUM_OF_PORTS_O24){
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


static void __HDMI21_PHY_O24A0_CheckPhyExceptionCase(UINT8 port, int resetClear)
{
	/* This function should only be called once there is a TCS Done, and phy is in a good state */

	do{
		/* Port Defence */
		if(port >= HDMI21_NUM_OF_PORTS_O24){
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

static void __PHY_Reg_O24A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData)
{
	UINT32 apb_addr;
	if(port >= HDMI21_NUM_OF_PORTS_O24) return;
	if(pData == NULL) return;

	apb_addr = reg << 2;

	*pData = gHDMI21RxHandler[port].phyPDC_read(apb_addr);	
	return;
}

static void __PHY_Reg_O24A0_WrFL(UINT8 port, UINT32 reg, UINT32 data)
{
	UINT32 apb_addr;
	if(port >= HDMI21_NUM_OF_PORTS_O24) return;
	
	apb_addr = reg << 2;

	gHDMI21RxHandler[port].phyPDC_write(apb_addr, data);	
	return;
}

static void __PHY_Reg_B1_O24A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_PORTS_O24) return;
	if(pData == NULL) return;

	apb_addr = reg << 2;

	*pData = gHDMI21RxHandler[port].phyDR_read(apb_addr);	
	return;
}

static void __PHY_Reg_B1_O24A0_WrFL(UINT8 port, UINT32 reg, UINT32 data)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_PORTS_O24) return;
	
	apb_addr = reg << 2;

	gHDMI21RxHandler[port].phyDR_write(apb_addr, data);	
	return;
}


static void __PHY_Reg_B2_O24A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_PORTS_O24) return;
	if(pData == NULL) return;

	apb_addr = (reg << 2) + 0x400;

	*pData = gHDMI21RxHandler[port].phyDR_read(apb_addr);	
	return;
}

static void __PHY_Reg_B2_O24A0_WrFL(UINT8 port, UINT32 reg, UINT32 data)
{
	UINT32 apb_addr;

	if(port >= HDMI21_NUM_OF_PORTS_O24) return;
	
	apb_addr = (reg << 2) + 0x400;

	gHDMI21RxHandler[port].phyDR_write(apb_addr, data);	
	return;
}

static void __HDMI21_PHY_O24A0_IncreaseTcsStateHistIdx(UINT8 port)
{
	int _d = 0;
	int _t = 0;

	if(port >= HDMI21_NUM_OF_PORTS_O24) return;

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

static int __HDMI21_PHY_O24A0_CheckTcsStateHistMatchVal(UINT8 port, UINT32 val)
{
	int i = 0;
	int ret = 0;
	int _t = 0;

	/* Get Option */
	_t = gHDMI21RxDevPhyControler[HDMI21__PHY_TCS_STATE_HIST_DEPTH].value;

	do {
		/* Port Defence */
		if(port >= HDMI21_NUM_OF_PORTS_O24) break;

		/* Option Defence from seg fault */
		if(_t == 0) break;

		/* Memory access defence */
		if(_t > HDMI21_PHY_TCS_HIST_HISTORY_DEPTH) _t = HDMI21_PHY_TCS_HIST_HISTORY_DEPTH;

		for(i=0; i<_t; i++) {
			//O24A0 TODO
			//have to expand tcs_state_ch1~ch3 
			//only tcs_state_ch0 value is used
			if((gPhyTcsStateHist[port][i] & 0xFF) <= val) {
				ret += 1;
			}
		}
	} while(0);

	return ret;
}


static void __HDMI21_PHY_O24A0_SetDfeResultCenter(UINT8 port)
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
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_a2);
		PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_a2, eq_cs_man_ch0, deltaResult[0]);
		PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_a2);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_a3);
		PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_a3, eq_cs_man_ch1, deltaResult[1]);
		PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_a3);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_a4);
		PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_a4, eq_cs_man_ch2, deltaResult[2]);
		PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_a4);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_a5);
		PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_a5, eq_cs_man_ch3, deltaResult[3]);
		PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_a5);

		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_99);
		PHY_REG_B1_O24A0_Wr01(port, hdmi_phy_addr_99, eq_auto_pll3, 1);
		PHY_REG_B1_O24A0_WrFL(port, hdmi_phy_addr_99);
	}


	if((gHDMI21RxHandler[port].isPhyFrlCtsMode > 0) &&(gHDMI21RxDevPhyControler[HDMI21__PHY_DFE_ADD_VAL_ON_CTS].value > 0)){
		HDMI21_LINE_DBG(502, "PHY[%d] : FRL DFE Center SWWA not running(CTS Mode).\n",port);
	}
	else {
		HDMI21_LINE_DBG(502, "PHY[%d] : FRL DFE Center Calculate Done. Result[%d][%d][%d][%d]\n",\
				port, deltaResult[0], deltaResult[1], deltaResult[2], deltaResult[3]);
	}

	return;
}

static int __HDMI21_PHY_O24A0_ToggleCrModeSelResetB(int port, int isSet)
{
	HDMI21_LINE_DBG(502, "PHY[%d] : Cr Mode Sel ResetB[%s]\n", port, isSet?"Reset":"Clear");

	if(isSet) {
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_04);
		PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_04, cr_mode_sel_resetb, 0x0);
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_04);
	}
	else{
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_04);
		PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_04, cr_mode_sel_resetb, 0x1);
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_04);
	}

	return 0;

}

static int __HDMI21_PHY_O24A0_ToggleDrResetB(int port, int isSet)
{
	HDMI21_LINE_DBG("PHY[%d] : DR ResetB[%s]\n", port, isSet?"Reset":"Clear");

	if(isSet) {
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_01);
		PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_01, resetb_sel, 0x1);
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_01);

		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_06);
		PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_06, dr_resetb, 0x0);
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_06);
	}
	else{
		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_06);
		PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_06, dr_resetb, 0x1);
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_06);

		PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_01);
		PHY_REG_O24A0_Wr01(port, hdmi_phy_addr_01, resetb_sel, 0x0);
		PHY_REG_O24A0_WrFL(port, hdmi_phy_addr_01);
	}

	return 0;
}

static int  __HDMI21_PHY_O24A0_IsOnboardPort(UINT8 port)
{
	int ret = 0;

	do {
		/* Port Defence */
		if(port >= HDMI21_NUM_OF_PORTS_O24) break;


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


/* 2020/06/01 : There is no such thing as FLT_START in HDMI2.1 FRL Training protocol
 *              This is somewhat of a internal signal to postpone FLT_UPDATE after writing LTP_x to source device
 *              to buy some time for the software to set the PHY system */
static int __HDMI21_PHY_O24A0_ToggleFltStart(int port, int isHigh, int isSet, UINT32 __callerLine)
{
	int ret = 0;

	/* Flush Shadow */
	PHY_REG_B2_O24A0_RdFL(port, hdmi_phy_addr_6a);
	
	if(isSet) {
		HDMI21_LINE_DBG(502, "PHY[%d] : Internal FLT_START signal[%s]. Caller[%d]\n", port, isHigh?"High":"Low", __callerLine);

		if(isHigh) {
			PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_6a, flt_start, 1);
		}
		else{
			PHY_REG_B2_O24A0_Wr01(port, hdmi_phy_addr_6a, flt_start, 0);
		}

		PHY_REG_B2_O24A0_WrFL(port, hdmi_phy_addr_6a);
	}

	PHY_REG_B2_O24A0_Rd01(port, hdmi_phy_addr_6a, flt_start, ret);

	return ret;
}


#if 0
static int __HDMI21_PHY_O24A0_CheckEqCalDone(int port)
{
	int ret = 0;
	UINT32 __d = 0;

	PHY_REG_O24A0_RdFL(port, hdmi_phy_addr_46);
	PHY_REG_O24A0_Rd01(port, hdmi_phy_addr_46, eq_cal_done, __d);

	/* Check Result */
	if(__d > 0) ret = 1;
	
	return ret;
}
#endif

void HDMI21_PHY_O24A0_GetSaffValue(int port)
{
	//O24A0: TODO
	//unused function
	
	return;
}

void HDMI21_PHY_O24A0_SetSaffManualValue(int port)
{
	//O24A0 : TODO
	//unused function

	return;
}

static int __HDMI21_PHY_O24A0_Check_EqCalDone(UINT8 port)
{

	int ret = 0;
	UINT32 eqCalDone = 0;

	do{
		if(port >= HDMI21_NUM_OF_PORTS_O24){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)]n", port);
			break;
		}

		/* Step 1. Check TCS Done */
		PHY_REG_B1_O24A0_RdFL(port, hdmi_phy_addr_f0);
		PHY_REG_B1_O24A0_Rd01(port, hdmi_phy_addr_f0, eq_cal_done_cr, eqCalDone);

		if(eqCalDone > 0) {
			ret = 1;
		}
	} while(0);

	return ret;
}


static void _SET_PHY (UINT8 port,HDMI_PHY_REG_APB_O24A0_T index, HDMI_PHY_INIT_MODE_T mode)
{
	UINT32 addr = o24a0_phy_reg_table[index].addr;
	HDMI_PHY_BLOCK_O24A0 block = o24a0_phy_reg_table[index].phy_block;
	volatile UINT32 data = 0x0;
	volatile UINT32 clear = MSK(o24a0_phy_reg_table[index].length, \
			o24a0_phy_reg_table[index].offset);
	volatile UINT32 mask = ((1 << (o24a0_phy_reg_table[index].length))-1);

	switch(block)
	{
		case PHY_PDC_O24A0:
			__PHY_Reg_O24A0_RdFL(port, addr, &data);
			data &= (~clear);
			mask &= (o24a0_phy_reg_table[index].reg_val[mode]);
			mask <<= o24a0_phy_reg_table[index].offset;
			data |= mask;
			__PHY_Reg_O24A0_WrFL(port, addr, data);
			break;

		case PHY_DR1_O24A0:
			__PHY_Reg_B1_O24A0_RdFL(port, addr, &data);
			data &= (~clear);
			mask &= (o24a0_phy_reg_table[index].reg_val[mode]);
			mask <<= o24a0_phy_reg_table[index].offset;
			data |= mask;
			__PHY_Reg_B1_O24A0_WrFL(port, addr, data);
			break;

		case PHY_DR2_O24A0:
			__PHY_Reg_B2_O24A0_RdFL(port, addr, &data);
			data &= (~clear);
			mask &= (o24a0_phy_reg_table[index].reg_val[mode]);
			mask <<= o24a0_phy_reg_table[index].offset;
			data |= mask;
			__PHY_Reg_B2_O24A0_WrFL(port, addr, data);
			break;

		default:
			break;
	}
}

static int HDMI_PHY_Set_Reg_Table(UINT8 port, HDMI_PHY_REG_APB_O24A0_T reg, HDMI_PHY_INIT_MODE_T mode)
{
	int ret = 0;
	HDMI_PHY_REG_APB_O24A0_T index = -1;

	for(index=I2C_CON_SEL_MODE_O24A0; index<PHY_REG_MAX_NUM_O24A0; ++index)
	{
		_SET_PHY(port, index, mode);
	}

	return ret;
}

static HDMI_PHY_INIT_MODE_T _CvtPhyMode(HDMI21_HAL_PHY_INITIATED_MODE_T mode)
{
	HDMI_PHY_INIT_MODE_T ret;
	switch(mode)
	{
		case HDMI21_HAL_PHY_INITIATED_ERROR:
			ret = HDMI_PHY_INITIATED_ERROR;
			break;
		//0 -> 2
		case HDMI21_HAL_PHY_INITIATED_3G:
			ret = HDMI_PHY_INITIATED_3G_M3;
			break;
		//1 -> 4
		case HDMI21_HAL_PHY_INITIATED_6G:
			ret = HDMI_PHY_INITIATED_6G;
			break;
		//2 -> 5
		case HDMI21_HAL_PHY_INITIATED_FRL_3G_3L:
			ret = HDMI_PHY_INITIATED_FRL_3G_3L;
			break;
		case HDMI21_HAL_PHY_INITIATED_FRL_6G_3L:
			ret = HDMI_PHY_INITIATED_FRL_6G_3L;
			break;
		case HDMI21_HAL_PHY_INITIATED_FRL_6G_4L:
			ret = HDMI_PHY_INITIATED_FRL_6G_4L;
			break;
		case HDMI21_HAL_PHY_INITIATED_FRL_8G_4L:
			ret = HDMI_PHY_INITIATED_FRL_8G_4L;
			break;
		case HDMI21_HAL_PHY_INITIATED_FRL_10G_4L:
			ret = HDMI_PHY_INITIATED_FRL_10G_4L;
			break;
		case HDMI21_HAL_PHY_INITIATED_FRL_12G_4L:
			ret = HDMI_PHY_INITIATED_FRL_12G_4L;
			break;
		default:
			ret = HDMI_PHY_INITIATED_3G_M3;
			break;
	}
	return ret;
}

static HDMI_PHY_INIT_MODE_T _CvtExceptRange(int phyCurExcepRange)
{
	HDMI_PHY_INIT_MODE_T ret;

	switch(phyCurExcepRange)
	{
		case -1:
			ret = HDMI_PHY_INITIATED_ERROR;
			break;
		case 0:
			ret = HDMI_PHY_INITIATED_3G_M3;
			break;
		case 1:
			ret = HDMI_PHY_INITIATED_3G_M1;
			//ret = HDMI_PHY_INITIATED_3G_M0;
			break;
		case 2:
			ret = HDMI_PHY_INITIATED_3G_M2;
			break;
		default:
			ret = HDMI_PHY_INITIATED_3G_M2;
			break;
	}
	return ret;
}
