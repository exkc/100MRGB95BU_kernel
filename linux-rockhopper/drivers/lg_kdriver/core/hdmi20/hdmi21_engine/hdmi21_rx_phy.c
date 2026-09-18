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
 *  @date		2019-04-23
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

#include "hdmi21_hal_driver.h"
#include "../hdmi20_drv.h" // For debug prints

#include "os_util.h"

#include "hdmi21_rx_phy.h"
#include "../../../chip/o20/hdmi20/hdmi21_rx_phy_o20a0.h"
#include "../../../chip/o20/hdmi20/hdmi21_rx_phy_o20b0.h"
#include "../../../chip/e60/hdmi20/hdmi21_rx_phy_e60a0.h"
#include "../../../chip/e60/hdmi20/hdmi21_rx_phy_e60b0.h"
#include "../../../chip/o22/hdmi20/hdmi21_rx_phy_o22a0.h"
#include "../../../chip/m23/hdmi20/hdmi21_rx_phy_m23a0.h"
#include "../../../chip/o24/hdmi20/hdmi21_rx_phy_o24a0.h"
#include "../../../chip/o26/hdmi20/hdmi21_rx_phy_o26a0.h"


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

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
HDMI21_PHY_FUNC_POINTER_T gHDMI21PhyFuncPointer;

/*----------------------------------------------------------------------------------------
    Implementation
----------------------------------------------------------------------------------------*/

int HDMI21_PHY_Rx_Set_InitFunctionPointer(void)
{
	int ret = RET_ERROR;

	HDMI20_INFO("[%s] entered\n", __F__);

	do{
		if( lx_chip_rev() >= LX_CHIP_REV(O26, A0) ){
			HDMI20_INFO("[%s:%d] PHY Chip set to [O26 A0]\n", __F__, __L__);
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl	= HDMI21_PHY_O26A0_InitiatePhySystemCtrl;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_PhyStatus	= HDMI21_PHY_O26A0_Rx_Get_PHYStatus;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_UpdatePhyLockFlag	= HDMI21_PHY_O26A0_UpdatePhyLockFlag;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_AccessPhy	= HDMI21_PHY_O26A0_Rx_AccessPhy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ControlPhyPdb	= HDMI21_PHY_O26A0_ControlPhyPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_3g6gMode	= HDMI21_PHY_O26A0_Set_3G6G_Mode;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_CheckTcsDone	= HDMI21_PHY_O26A0_Check_TCSDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration	= HDMI21_PHY_O26A0_Reset_EqOffsetCalibration;

			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_Initiate_Phy	= HDMI21_PHY_O26A0_Rx_Initiate_Phy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_TmdsFreq	= HDMI21_PHY_O26A0_Get_TMDS_FREQ;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock	= HDMI21_PHY_O26A0_UpdatePhyTMDSclock;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetPllPdb	= HDMI21_PHY_O26A0_Reset_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_PowerControlPllPdb	= HDMI21_PHY_O26A0_PowerControl_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn	= HDMI21_PHY_O26A0_IsPhyPdbPowerOn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiateDfeCenter = HDMI21_PHY_O26A0_InitiateDfeCenter;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeDone = HDMI21_PHY_O26A0_CheckDfeDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ToggleTCSEn = HDMI21_PHY_O26A0_ToggleTCSEn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeResult = HDMI21_PHY_O26A0_Check_DfeResult;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckEqCalDone = HDMI21_PHY_O26A0_CheckEqCalDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_SaffManualValue = HDMI21_PHY_O26A0_SetSaffManualValue;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_SaffValue = HDMI21_PHY_O26A0_GetSaffValue;
		}
		else if( lx_chip_rev() >= LX_CHIP_REV(O24, A0) ){
			HDMI20_INFO("[%s:%d] PHY Chip set to [O24 A0]\n", __F__, __L__);
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl	= HDMI21_PHY_O24A0_InitiatePhySystemCtrl;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_PhyStatus	= HDMI21_PHY_O24A0_Rx_Get_PHYStatus;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_UpdatePhyLockFlag	= HDMI21_PHY_O24A0_UpdatePhyLockFlag;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_AccessPhy	= HDMI21_PHY_O24A0_Rx_AccessPhy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ControlPhyPdb	= HDMI21_PHY_O24A0_ControlPhyPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_3g6gMode	= HDMI21_PHY_O24A0_Set_3G6G_Mode;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_CheckTcsDone	= HDMI21_PHY_O24A0_Check_TCSDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration	= HDMI21_PHY_O24A0_Reset_EqOffsetCalibration;

			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_Initiate_Phy	= HDMI21_PHY_O24A0_Rx_Initiate_Phy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_TmdsFreq	= HDMI21_PHY_O24A0_Get_TMDS_FREQ;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock	= HDMI21_PHY_O24A0_UpdatePhyTMDSclock;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetPllPdb	= HDMI21_PHY_O24A0_Reset_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_PowerControlPllPdb	= HDMI21_PHY_O24A0_PowerControl_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn	= HDMI21_PHY_O24A0_IsPhyPdbPowerOn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiateDfeCenter = HDMI21_PHY_O24A0_InitiateDfeCenter;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeDone = HDMI21_PHY_O24A0_CheckDfeDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ToggleTCSEn = HDMI21_PHY_O24A0_ToggleTCSEn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeResult = HDMI21_PHY_O24A0_Check_DfeResult;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckEqCalDone = HDMI21_PHY_O24A0_CheckEqCalDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_SaffManualValue = HDMI21_PHY_O24A0_SetSaffManualValue;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_SaffValue = HDMI21_PHY_O24A0_GetSaffValue;
		}
		else if( lx_chip_rev() >= LX_CHIP_REV(M23, A0) ){
			HDMI20_INFO("[%s:%d] PHY Chip set to [M23 A0]\n", __F__, __L__);
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl	= HDMI21_PHY_M23A0_InitiatePhySystemCtrl;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_PhyStatus	= HDMI21_PHY_M23A0_Rx_Get_PHYStatus;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_UpdatePhyLockFlag	= HDMI21_PHY_M23A0_UpdatePhyLockFlag;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_AccessPhy	= HDMI21_PHY_M23A0_Rx_AccessPhy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ControlPhyPdb	= HDMI21_PHY_M23A0_ControlPhyPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_3g6gMode	= HDMI21_PHY_M23A0_Set_3G6G_Mode;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_CheckTcsDone	= HDMI21_PHY_M23A0_Check_TCSDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration	= HDMI21_PHY_M23A0_Reset_EqOffsetCalibration;

			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_Initiate_Phy	= HDMI21_PHY_M23A0_Rx_Initiate_Phy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_TmdsFreq	= HDMI21_PHY_M23A0_Get_TMDS_FREQ;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock	= HDMI21_PHY_M23A0_UpdatePhyTMDSclock;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetPllPdb	= HDMI21_PHY_M23A0_Reset_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_PowerControlPllPdb	= HDMI21_PHY_M23A0_PowerControl_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn	= HDMI21_PHY_M23A0_IsPhyPdbPowerOn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiateDfeCenter = HDMI21_PHY_M23A0_InitiateDfeCenter;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeDone = HDMI21_PHY_M23A0_CheckDfeDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ToggleTCSEn = HDMI21_PHY_M23A0_ToggleTCSEn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeResult = HDMI21_PHY_M23A0_Check_DfeResult;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckEqCalDone = HDMI21_PHY_M23A0_CheckEqCalDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_SaffManualValue = HDMI21_PHY_M23A0_SetSaffManualValue;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_SaffValue = HDMI21_PHY_M23A0_GetSaffValue;
		}
		else if( lx_chip_rev() >= LX_CHIP_REV(O22, A0) ){
			HDMI20_INFO("[%s:%d] PHY Chip set to [O22 A0]\n", __F__, __L__);
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl	= HDMI21_PHY_O22A0_InitiatePhySystemCtrl;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_PhyStatus	= HDMI21_PHY_O22A0_Rx_Get_PHYStatus;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_UpdatePhyLockFlag	= HDMI21_PHY_O22A0_UpdatePhyLockFlag;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_AccessPhy	= HDMI21_PHY_O22A0_Rx_AccessPhy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ControlPhyPdb	= HDMI21_PHY_O22A0_ControlPhyPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_3g6gMode	= HDMI21_PHY_O22A0_Set_3G6G_Mode;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_CheckTcsDone	= HDMI21_PHY_O22A0_Check_TCSDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration	= HDMI21_PHY_O22A0_Reset_EqOffsetCalibration;

			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_Initiate_Phy	= HDMI21_PHY_O22A0_Rx_Initiate_Phy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_TmdsFreq	= HDMI21_PHY_O22A0_Get_TMDS_FREQ;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock	= HDMI21_PHY_O22A0_UpdatePhyTMDSclock;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetPllPdb	= HDMI21_PHY_O22A0_Reset_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_PowerControlPllPdb	= HDMI21_PHY_O22A0_PowerControl_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn	= HDMI21_PHY_O22A0_IsPhyPdbPowerOn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiateDfeCenter = HDMI21_PHY_O22A0_InitiateDfeCenter;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeDone = HDMI21_PHY_O22A0_CheckDfeDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ToggleTCSEn = HDMI21_PHY_O22A0_ToggleTCSEn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeResult = HDMI21_PHY_O22A0_Check_DfeResult;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckEqCalDone = HDMI21_PHY_O22A0_CheckEqCalDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_SaffManualValue = HDMI21_PHY_O22A0_SetSaffManualValue;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_SaffValue = HDMI21_PHY_O22A0_GetSaffValue;
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV(E60, B0) )
		{
			HDMI20_INFO("[%s:%d] PHY Chip set to [E60 B0]\n", __F__, __L__);
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl	= HDMI21_PHY_E60B0_InitiatePhySystemCtrl;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_PhyStatus	= HDMI21_PHY_E60B0_Rx_Get_PHYStatus;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_UpdatePhyLockFlag	= HDMI21_PHY_E60B0_UpdatePhyLockFlag;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_AccessPhy	= HDMI21_PHY_E60B0_Rx_AccessPhy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ControlPhyPdb	= HDMI21_PHY_E60B0_ControlPhyPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_3g6gMode	= HDMI21_PHY_E60B0_Set_3G6G_Mode;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_CheckTcsDone	= HDMI21_PHY_E60B0_Check_TCSDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration	= HDMI21_PHY_E60B0_Reset_EqOffsetCalibration;

			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_Initiate_Phy	= HDMI21_PHY_E60B0_Rx_Initiate_Phy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_TmdsFreq	= HDMI21_PHY_E60B0_Get_TMDS_FREQ;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock	= HDMI21_PHY_E60B0_UpdatePhyTMDSclock;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetPllPdb	= HDMI21_PHY_E60B0_Reset_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_PowerControlPllPdb	= HDMI21_PHY_E60B0_PowerControl_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn	= HDMI21_PHY_E60B0_IsPhyPdbPowerOn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiateDfeCenter = HDMI21_PHY_E60B0_InitiateDfeCenter;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeDone = HDMI21_PHY_E60B0_CheckDfeDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ToggleTCSEn = HDMI21_PHY_E60B0_ToggleTCSEn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeResult = HDMI21_PHY_E60B0_Check_DfeResult;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckEqCalDone = HDMI21_PHY_E60B0_CheckEqCalDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_SaffManualValue = HDMI21_PHY_E60B0_SetSaffManualValue;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_SaffValue = HDMI21_PHY_E60B0_GetSaffValue;
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV(E60, A0) )
		{
			HDMI20_INFO("[%s:%d] PHY Chip set to [E60 A0]\n", __F__, __L__);
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl	= HDMI21_PHY_E60A0_InitiatePhySystemCtrl;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_PhyStatus	= HDMI21_PHY_E60A0_Rx_Get_PHYStatus;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_UpdatePhyLockFlag	= HDMI21_PHY_E60A0_UpdatePhyLockFlag;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_AccessPhy	= HDMI21_PHY_E60A0_Rx_AccessPhy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ControlPhyPdb	= HDMI21_PHY_E60A0_ControlPhyPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_3g6gMode	= HDMI21_PHY_E60A0_Set_3G6G_Mode;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_CheckTcsDone	= HDMI21_PHY_E60A0_Check_TCSDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration	= HDMI21_PHY_E60A0_Reset_EqOffsetCalibration;

			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_Initiate_Phy	= HDMI21_PHY_E60A0_Rx_Initiate_Phy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_TmdsFreq	= HDMI21_PHY_E60A0_Get_TMDS_FREQ;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock	= HDMI21_PHY_E60A0_UpdatePhyTMDSclock;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetPllPdb	= HDMI21_PHY_E60A0_Reset_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_PowerControlPllPdb	= HDMI21_PHY_E60A0_PowerControl_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn	= HDMI21_PHY_E60A0_IsPhyPdbPowerOn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiateDfeCenter = HDMI21_PHY_E60A0_InitiateDfeCenter;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeDone = HDMI21_PHY_E60A0_CheckDfeDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ToggleTCSEn = HDMI21_PHY_E60A0_ToggleTCSEn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeResult = NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckEqCalDone = NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_SaffManualValue = NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_SaffValue = NULL;
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV(O20, B0) )
		{
			HDMI20_INFO("[%s:%d] PHY Chip set to [O20 B0]\n", __F__, __L__);
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl	= HDMI21_PHY_O20B0_InitiatePhySystemCtrl;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_PhyStatus	= HDMI21_PHY_O20B0_Rx_Get_PHYStatus;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_UpdatePhyLockFlag	= HDMI21_PHY_O20B0_UpdatePhyLockFlag;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_AccessPhy	= HDMI21_PHY_O20B0_Rx_AccessPhy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ControlPhyPdb	= HDMI21_PHY_O20B0_ControlPhyPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_3g6gMode	= HDMI21_PHY_O20B0_Set_3G6G_Mode;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_CheckTcsDone	= HDMI21_PHY_O20B0_Check_TCSDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration	= HDMI21_PHY_O20B0_Reset_EqOffsetCalibration;

			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_Initiate_Phy	= HDMI21_PHY_O20B0_Rx_Initiate_Phy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_TmdsFreq	= HDMI21_PHY_O20B0_Get_TMDS_FREQ;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock	= HDMI21_PHY_O20B0_UpdatePhyTMDSclock;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetPllPdb	= HDMI21_PHY_O20B0_Reset_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_PowerControlPllPdb	= HDMI21_PHY_O20B0_PowerControl_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn	= HDMI21_PHY_O20B0_IsPhyPdbPowerOn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiateDfeCenter = HDMI21_PHY_O20B0_InitiateDfeCenter;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeDone = HDMI21_PHY_O20B0_CheckDfeDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ToggleTCSEn = HDMI21_PHY_O20B0_ToggleTCSEn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeResult = NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckEqCalDone = NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_SaffManualValue = NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_SaffValue = NULL;
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV(O20, A0) )
		{
			HDMI20_INFO("[%s:%d] PHY Chip set to [O20 A0]\n", __F__, __L__);
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl	= HDMI21_PHY_O20A0_InitiatePhySystemCtrl;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_PhyStatus	= HDMI21_PHY_O20A0_Rx_Get_PHYStatus;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_UpdatePhyLockFlag	= HDMI21_PHY_O20A0_UpdatePhyLockFlag;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_AccessPhy	= HDMI21_PHY_O20A0_Rx_AccessPhy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ControlPhyPdb	= HDMI21_PHY_O20A0_ControlPhyPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_3g6gMode	= HDMI21_PHY_O20A0_Set_3G6G_Mode;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_CheckTcsDone	= HDMI21_PHY_O20A0_Check_TCSDone;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration	= HDMI21_PHY_O20A0_Reset_EqOffsetCalibration;

			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_Initiate_Phy	= HDMI21_PHY_O20A0_Rx_Initiate_Phy;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_TmdsFreq	= HDMI21_PHY_O20A0_Get_TMDS_FREQ;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock	= HDMI21_PHY_O20A0_UpdatePhyTMDSclock;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetPllPdb	= HDMI21_PHY_O20A0_Reset_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_PowerControlPllPdb	= HDMI21_PHY_O20A0_PowerControl_PLLPDB;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn	= HDMI21_PHY_O20A0_IsPhyPdbPowerOn;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiateDfeCenter =  NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ToggleTCSEn = NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeResult = NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckEqCalDone = NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_SaffManualValue = NULL;
			gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_SaffValue = NULL;
		}
		else{
			HDMI20_INFO("[%s:%d] Error! Unknown chip type\n", __F__,__L__);
			break;
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl(UINT8 port)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}


int HDMI21_PHY_Rx_Get_PhyStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_PhyStatus)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_PhyStatus(pData,size, updatePhyI2C, isInternalCall);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}


void HDMI21_PHY_Rx_Get_UpdatePhyLockFlag(UINT8 port)
{
	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_UpdatePhyLockFlag)
	{
		gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_UpdatePhyLockFlag(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
}

int HDMI21_PHY_Rx_Set_AccessPhy(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_AccessPhy)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_AccessPhy(port, pPhyCtrl, size);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI21_PHY_Rx_Set_ControlPhyPdb(UINT8 port, BOOLEAN bOnOff)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ControlPhyPdb)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ControlPhyPdb(port, bOnOff);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI21_PHY_Rx_Set_3g6gMode(UINT8 port, UINT8 isAuto, HDMI21_HAL_PHY_INITIATED_MODE_T mode, UINT8 isScrambling, UINT8 lowfreqGain)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_3g6gMode)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_3g6gMode(port, isAuto, mode, isScrambling, lowfreqGain);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI21_PHY_Rx_Set_CheckTcsDone(UINT8 port)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_CheckTcsDone)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_CheckTcsDone(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}



int HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration(port, isReset, callerId);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI21_PHY_Rx_Set_Initiate_Phy(int port, HDMI21_HAL_PHY_INITIATED_MODE_T mode)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_Initiate_Phy)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_Initiate_Phy(port, mode);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

UINT8 HDMI21_PHY_Rx_Get_TmdsFreq(UINT8 port, int isMSB)
{
	UINT8 ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_TmdsFreq)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_TmdsFreq(port, isMSB);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

void HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock(UINT8 port)
{
	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock)
	{
		gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
}

int HDMI21_PHY_Rx_Set_ResetPllPdb(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetPllPdb)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ResetPllPdb(port, isReset, callerId);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI21_PHY_Rx_Set_PowerControlPllPdb(UINT8 port, UINT8 isDown, UINT32 callerId)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_PowerControlPllPdb)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_PowerControlPllPdb(port, isDown, callerId);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}


int HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn(UINT8 port)
{
	int ret = RET_ERROR;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}


void HDMI21_PHY_Rx_Set_InitiateDfeCenter(UINT8 port)
{
	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiateDfeCenter)
	{
		gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_InitiateDfeCenter(port);
	}
}

int HDMI21_PHY_Rx_Get_CheckDfeDone(UINT8 port)
{
	int ret = 0;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeDone)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeDone(port);
	}

	return ret;
}

int 	HDMI21_PHY_Rx_Set_ToggleTCSEn(int port, int isSet)
{
	int ret = 0;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ToggleTCSEn)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_ToggleTCSEn(port, isSet);
	}

	return ret;

}

int 	HDMI21_PHY_Rx_Get_CheckDfeResult(UINT8 port)
{
	int ret = 0;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeResult)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckDfeResult(port);
	}

	return ret;
}

int  	HDMI21_PHY_Rx_Get_CheckEqCalDone(int port)
{
	int ret = 0;

	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckEqCalDone)
	{
		ret = gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_CheckEqCalDone(port);
	}

	return ret;
}

void 	HDMI21_PHY_Rx_Set_SaffManualValue(int port)
{
	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_SaffManualValue)
	{
		gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Set_SaffManualValue(port);
	}

	return;
}

void 	HDMI21_PHY_Rx_Get_SaffValue(int port)
{
	if(gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_SaffValue)
	{
		gHDMI21PhyFuncPointer.HDMI21_PHY_Rx_Get_SaffValue(port);
	}

	return;
}
