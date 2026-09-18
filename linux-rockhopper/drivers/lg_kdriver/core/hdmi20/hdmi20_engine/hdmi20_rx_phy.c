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
 *  @date		2016-05-02
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

#include "hdmi20_hal_driver.h"
#include "./synopsys_api/hdmi_rx_ctrl.h"

#include "../hdmi20_drv.h" // For debug prints

#include "os_util.h"

#include "hdmi20_rx_phy.h"
#include "../../../chip/o18/hdmi20/hdmi20_rx_phy_o18.h"
#include "../../../chip/m17/hdmi20/hdmi20_rx_phy_m17a0.h"
#include "../../../chip/m17/hdmi20/hdmi20_rx_phy_m17c0.h"

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
HDMI20_PHY_FUNC_POINTER_T gHDMI20PhyFuncPointer;

/*----------------------------------------------------------------------------------------
    Implementation
----------------------------------------------------------------------------------------*/

int HDMI20_PHY_InitFunctionPointer(void)
{
	int ret = RET_ERROR;

	HDMI20_INFO("[%s] entered\n", __F__);

	do{
		if( lx_chip_rev( ) >= LX_CHIP_REV(M19, A0) )
		{
			HDMI20_INFO("[%s:%d] PHY Chip set to [M19 A0]\n", __F__, __L__);
			gHDMI20PhyFuncPointer.HDMI20_PHY_InitiatePhySystemCtrl	= HDMI20_PHY_M19A0_InitiatePhySystemCtrl;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Get_PHYStatus	= HDMI20_PHY_M19A0_Rx_Get_PHYStatus;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyLockFlag	= HDMI20_PHY_M19A0_UpdatePhyLockFlag;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_AccessPhy	= HDMI20_PHY_M19A0_Rx_AccessPhy;
			gHDMI20PhyFuncPointer.HDMI20_PHY_ControlPhyPDB	= HDMI20_PHY_M19A0_ControlPhyPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Set_3G6G_Mode	= HDMI20_PHY_M19A0_Set_3G6G_Mode;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_ModeSel	= HDMI20_PHY_M19A0_Reset_ModeSel;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSDone	= HDMI20_PHY_M19A0_Check_TCSDone;
			gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyTCSStable	= HDMI20_PHY_M19A0_IsPhyTCSStable;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Update_TMDS_TCS_Value	= HDMI20_PHY_M19A0_Update_TMDS_TCS_Value;
			gHDMI20PhyFuncPointer.HDMI20_PHY_CheckLinkPhyLock	= HDMI20_PHY_M19A0_CheckLinkPhyLock;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_EqOffsetCalibration	= HDMI20_PHY_M19A0_Reset_EqOffsetCalibration;

			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_SetTCSAddVal	= HDMI20_PHY_M19A0_Rx_SetTCSAddVal;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Initiate_Phy	= HDMI20_PHY_M19A0_Rx_Initiate_Phy;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Get_TMDS_FREQ	= HDMI20_PHY_M19A0_Get_TMDS_FREQ;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyTMDSclock	= HDMI20_PHY_M19A0_UpdatePhyTMDSclock;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_PLLPDB	= HDMI20_PHY_M19A0_Reset_PLLPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_PowerControl_PLLPDB	= HDMI20_PHY_M19A0_PowerControl_PLLPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Restart_TCS	= HDMI20_PHY_M19A0_Restart_TCS;
			gHDMI20PhyFuncPointer.HDMI20_PHY_CheckTcsHist	= HDMI20_PHY_M19A0_CheckTcsHist;
			gHDMI20PhyFuncPointer.HDMI20_PHY_InitiateTCSHist	= HDMI20_PHY_M19A0_InitiateTCSHist;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdateModeSelStatus	= HDMI20_PHY_M19A0_UpdateModeSelStatus;
			gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyPdbPowerOn	= HDMI20_PHY_M19A0_IsPhyPdbPowerOn;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSError		= HDMI20_PHY_M19A0_Check_TCSError;
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV(O18, A0) )
		{
			HDMI20_INFO("[%s:%d] PHY Chip set to [O18]\n", __F__, __L__);
			gHDMI20PhyFuncPointer.HDMI20_PHY_InitiatePhySystemCtrl	= HDMI20_PHY_O18_InitiatePhySystemCtrl;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Get_PHYStatus	= HDMI20_PHY_O18_Rx_Get_PHYStatus;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyLockFlag	= HDMI20_PHY_O18_UpdatePhyLockFlag;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_AccessPhy	= HDMI20_PHY_O18_Rx_AccessPhy;
			gHDMI20PhyFuncPointer.HDMI20_PHY_ControlPhyPDB	= HDMI20_PHY_O18_ControlPhyPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Set_3G6G_Mode	= HDMI20_PHY_O18_Set_3G6G_Mode;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_ModeSel	= HDMI20_PHY_O18_Reset_ModeSel;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSDone	= HDMI20_PHY_O18_Check_TCSDone;
			gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyTCSStable	= HDMI20_PHY_O18_IsPhyTCSStable;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Update_TMDS_TCS_Value	= HDMI20_PHY_O18_Update_TMDS_TCS_Value;
			gHDMI20PhyFuncPointer.HDMI20_PHY_CheckLinkPhyLock	= HDMI20_PHY_O18_CheckLinkPhyLock;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_EqOffsetCalibration	= HDMI20_PHY_O18_Reset_EqOffsetCalibration;

			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_SetTCSAddVal	= HDMI20_PHY_O18_Rx_SetTCSAddVal;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Initiate_Phy	= HDMI20_PHY_O18_Rx_Initiate_Phy;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Get_TMDS_FREQ	= HDMI20_PHY_O18_Get_TMDS_FREQ;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyTMDSclock	= HDMI20_PHY_O18_UpdatePhyTMDSclock;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_PLLPDB	= HDMI20_PHY_O18_Reset_PLLPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_PowerControl_PLLPDB	= HDMI20_PHY_O18_PowerControl_PLLPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Restart_TCS	= HDMI20_PHY_O18_Restart_TCS;
			gHDMI20PhyFuncPointer.HDMI20_PHY_CheckTcsHist	= HDMI20_PHY_O18_CheckTcsHist;
			gHDMI20PhyFuncPointer.HDMI20_PHY_InitiateTCSHist	= HDMI20_PHY_O18_InitiateTCSHist;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdateModeSelStatus	= HDMI20_PHY_O18_UpdateModeSelStatus;
			gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyPdbPowerOn	= HDMI20_PHY_O18_IsPhyPdbPowerOn;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSError		= HDMI20_PHY_O18_Check_TCSError;
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV(M17, C0) )
		{
			HDMI20_INFO("[%s:%d] PHY Chip set to [M17 C0]\n", __F__, __L__);
			gHDMI20PhyFuncPointer.HDMI20_PHY_InitiatePhySystemCtrl	= HDMI20_PHY_M17C0_InitiatePhySystemCtrl;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Get_PHYStatus	= HDMI20_PHY_M17C0_Rx_Get_PHYStatus;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyLockFlag	= HDMI20_PHY_M17C0_UpdatePhyLockFlag;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_AccessPhy	= HDMI20_PHY_M17C0_Rx_AccessPhy;
			gHDMI20PhyFuncPointer.HDMI20_PHY_ControlPhyPDB	= HDMI20_PHY_M17C0_ControlPhyPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Set_3G6G_Mode	= HDMI20_PHY_M17C0_Set_3G6G_Mode;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_ModeSel	= HDMI20_PHY_M17C0_Reset_ModeSel;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSDone	= HDMI20_PHY_M17C0_Check_TCSDone;
			gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyTCSStable	= HDMI20_PHY_M17C0_IsPhyTCSStable;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Update_TMDS_TCS_Value	= HDMI20_PHY_M17C0_Update_TMDS_TCS_Value;
			gHDMI20PhyFuncPointer.HDMI20_PHY_CheckLinkPhyLock	= HDMI20_PHY_M17C0_CheckLinkPhyLock;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_EqOffsetCalibration	= HDMI20_PHY_M17C0_Reset_EqOffsetCalibration;

			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_SetTCSAddVal	= HDMI20_PHY_M17C0_Rx_SetTCSAddVal;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Initiate_Phy	= HDMI20_PHY_M17C0_Rx_Initiate_Phy;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Get_TMDS_FREQ	= HDMI20_PHY_M17C0_Get_TMDS_FREQ;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyTMDSclock	= HDMI20_PHY_M17C0_UpdatePhyTMDSclock;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_PLLPDB	= HDMI20_PHY_M17C0_Reset_PLLPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_PowerControl_PLLPDB	= HDMI20_PHY_M17C0_PowerControl_PLLPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Restart_TCS	= HDMI20_PHY_M17C0_Restart_TCS;
			gHDMI20PhyFuncPointer.HDMI20_PHY_CheckTcsHist	= HDMI20_PHY_M17C0_CheckTcsHist;
			gHDMI20PhyFuncPointer.HDMI20_PHY_InitiateTCSHist	= HDMI20_PHY_M17C0_InitiateTCSHist;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdateModeSelStatus	= HDMI20_PHY_M17C0_UpdateModeSelStatus;
			gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyPdbPowerOn	= HDMI20_PHY_M17C0_IsPhyPdbPowerOn;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSError		= HDMI20_PHY_M17C0_Check_TCSError;
		}
		else if( lx_chip_rev( ) >= LX_CHIP_REV(M17, A0) )
		{
			HDMI20_INFO("[%s:%d] PHY Chip set to [M17 A0]\n", __F__, __L__);
			gHDMI20PhyFuncPointer.HDMI20_PHY_InitiatePhySystemCtrl	= HDMI20_PHY_M17A0_InitiatePhySystemCtrl;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Get_PHYStatus	= HDMI20_PHY_M17A0_Rx_Get_PHYStatus;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyLockFlag	= HDMI20_PHY_M17A0_UpdatePhyLockFlag;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_AccessPhy	= HDMI20_PHY_M17A0_Rx_AccessPhy;
			gHDMI20PhyFuncPointer.HDMI20_PHY_ControlPhyPDB	= HDMI20_PHY_M17A0_ControlPhyPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Set_3G6G_Mode	= HDMI20_PHY_M17A0_Set_3G6G_Mode;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_ModeSel	= HDMI20_PHY_M17A0_Reset_ModeSel;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSDone	= HDMI20_PHY_M17A0_Check_TCSDone;
			gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyTCSStable	= HDMI20_PHY_M17A0_IsPhyTCSStable;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Update_TMDS_TCS_Value	= HDMI20_PHY_M17A0_Update_TMDS_TCS_Value;
			gHDMI20PhyFuncPointer.HDMI20_PHY_CheckLinkPhyLock	= HDMI20_PHY_M17A0_CheckLinkPhyLock;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_EqOffsetCalibration	= HDMI20_PHY_M17A0_Reset_EqOffsetCalibration;

			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_SetTCSAddVal	= HDMI20_PHY_M17A0_Rx_SetTCSAddVal;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Initiate_Phy	= HDMI20_PHY_M17A0_Rx_Initiate_Phy;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Get_TMDS_FREQ	= HDMI20_PHY_M17A0_Get_TMDS_FREQ;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyTMDSclock	= HDMI20_PHY_M17A0_UpdatePhyTMDSclock;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_PLLPDB	= HDMI20_PHY_M17A0_Reset_PLLPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_PowerControl_PLLPDB	= HDMI20_PHY_M17A0_PowerControl_PLLPDB;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Restart_TCS	= HDMI20_PHY_M17A0_Restart_TCS;
			gHDMI20PhyFuncPointer.HDMI20_PHY_CheckTcsHist	= HDMI20_PHY_M17A0_CheckTcsHist;
			gHDMI20PhyFuncPointer.HDMI20_PHY_InitiateTCSHist	= HDMI20_PHY_M17A0_InitiateTCSHist;
			gHDMI20PhyFuncPointer.HDMI20_PHY_UpdateModeSelStatus	= HDMI20_PHY_M17A0_UpdateModeSelStatus;
			gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyPdbPowerOn	= HDMI20_PHY_M17A0_IsPhyPdbPowerOn;
			gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSError		= HDMI20_PHY_M17A0_Check_TCSError;
		}
		else{
			HDMI20_INFO("[%s:%d] Error! Unknown chip type\n", __F__,__L__);
			break;
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


int HDMI20_PHY_InitiatePhySystemCtrl(UINT8 port)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_InitiatePhySystemCtrl)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_InitiatePhySystemCtrl(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}


int HDMI20_PHY_Rx_Get_PHYStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Get_PHYStatus)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Get_PHYStatus(pData,size, updatePhyI2C, isInternalCall);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}


void HDMI20_PHY_UpdatePhyLockFlag(UINT8 port)
{
	if(gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyLockFlag)
	{
		gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyLockFlag(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
}

int HDMI20_PHY_Rx_AccessPhy(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_AccessPhy)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_AccessPhy(port, pPhyCtrl, size);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_ControlPhyPDB(UINT8 port, BOOLEAN bOnOff)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_ControlPhyPDB)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_ControlPhyPDB(port, bOnOff);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_Set_3G6G_Mode(UINT8 port, UINT8 isAuto, UINT8 is6G, UINT8 isScrambling, UINT8 lowfreqGain)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Set_3G6G_Mode)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Set_3G6G_Mode(port, isAuto, is6G, isScrambling, lowfreqGain);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_Reset_ModeSel(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_ModeSel)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_ModeSel(port, isReset, callerId);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_Check_TCSDone(UINT8 port)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSDone)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSDone(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_IsPhyTCSStable(UINT8 port)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyTCSStable)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyTCSStable(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_Update_TMDS_TCS_Value(UINT8 port, int isClear)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Update_TMDS_TCS_Value)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Update_TMDS_TCS_Value(port, isClear);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_CheckLinkPhyLock(UINT8 port, int isClear)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_CheckLinkPhyLock)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_CheckLinkPhyLock(port, isClear);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_Reset_EqOffsetCalibration(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_EqOffsetCalibration)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_EqOffsetCalibration(port, isReset, callerId);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}


int HDMI20_PHY_Rx_SetTCSAddVal(int port, UINT8 tcsAddVal)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_SetTCSAddVal)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_SetTCSAddVal(port, tcsAddVal);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_Rx_Initiate_Phy(int port, int isUD)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Initiate_Phy)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Rx_Initiate_Phy(port, isUD);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

UINT8 HDMI20_PHY_Get_TMDS_FREQ(UINT8 port, int isMSB)
{
	UINT8 ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Get_TMDS_FREQ)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Get_TMDS_FREQ(port, isMSB);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

void HDMI20_PHY_UpdatePhyTMDSclock(UINT8 port)
{
	if(gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyTMDSclock)
	{
		gHDMI20PhyFuncPointer.HDMI20_PHY_UpdatePhyTMDSclock(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
}

int HDMI20_PHY_Reset_PLLPDB(UINT8 port, UINT8 isReset, UINT32 callerId)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_PLLPDB)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Reset_PLLPDB(port, isReset, callerId);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_PowerControl_PLLPDB(UINT8 port, UINT8 isDown, UINT32 callerId)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_PowerControl_PLLPDB)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_PowerControl_PLLPDB(port, isDown, callerId);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_Restart_TCS(UINT8 port, UINT8 isRestart, UINT32 callerId)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Restart_TCS)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Restart_TCS(port, isRestart, callerId);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_CheckTcsHist(UINT8 port)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_CheckTcsHist)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_CheckTcsHist(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

void HDMI20_PHY_InitiateTCSHist(UINT8 port)
{
	if(gHDMI20PhyFuncPointer.HDMI20_PHY_InitiateTCSHist)
	{
		gHDMI20PhyFuncPointer.HDMI20_PHY_InitiateTCSHist(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
}

void HDMI20_PHY_UpdateModeSelStatus(UINT8 port)
{
	if(gHDMI20PhyFuncPointer.HDMI20_PHY_UpdateModeSelStatus)
	{
		gHDMI20PhyFuncPointer.HDMI20_PHY_UpdateModeSelStatus(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
}

int HDMI20_PHY_IsPhyPdbPowerOn(UINT8 port)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyPdbPowerOn)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_IsPhyPdbPowerOn(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}

int HDMI20_PHY_Check_TCSError(UINT8 port)
{
	int ret = RET_ERROR;

	if(gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSError)
	{
		ret = gHDMI20PhyFuncPointer.HDMI20_PHY_Check_TCSError(port);
	}
	else
	{
		HDMI20_ERROR("%s : Function Pointer is NULL!\n",__F__);
	}
	return ret;
}
