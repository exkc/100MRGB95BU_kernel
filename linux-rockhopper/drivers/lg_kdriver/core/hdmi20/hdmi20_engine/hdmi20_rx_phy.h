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
 * Register access for hdmi20 phy 
 *
 * author     Won Hur (won.hur@lge.com)
 * version    1.0
 * date       2016.05.02
 * note       Additional information.
 *
 * @addtogroup lg11xxx_sys
 * @{
 */
#ifndef __HDMI20_RX_PHY_H__
#define __HDMI20_RX_PHY_H__


/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "reg_ctrl.h"
#include "sys_reg_base.h"

#include "hdmi20_kapi.h"
/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
	----------------------------------------------------------------------------------------*/
/* IOCTL */
typedef struct
{
	int (*HDMI20_PHY_InitiatePhySystemCtrl)(UINT8 port);
	int (*HDMI20_PHY_Rx_Get_PHYStatus)(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall);
	void (*HDMI20_PHY_UpdatePhyLockFlag)(UINT8 port);
	int (*HDMI20_PHY_Rx_AccessPhy)(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size);
	int (*HDMI20_PHY_ControlPhyPDB)(UINT8 port, BOOLEAN bOnOff);
	int (*HDMI20_PHY_Set_3G6G_Mode)(UINT8 port, UINT8 isAuto, UINT8 is6G, UINT8 isScrambling, UINT8 lowfreqGain);
	int (*HDMI20_PHY_Reset_ModeSel)(UINT8 port, UINT8 isReset, UINT32 callerId);
	int (*HDMI20_PHY_Check_TCSDone)(UINT8 port);
	int (*HDMI20_PHY_IsPhyTCSStable)(UINT8 port);
	int (*HDMI20_PHY_Update_TMDS_TCS_Value)(UINT8 port, int isClear);
	int (*HDMI20_PHY_CheckLinkPhyLock)(UINT8 port, int isClear);
	int (*HDMI20_PHY_Reset_EqOffsetCalibration)(UINT8 port, UINT8 isReset, UINT32 callerId);

	int (*HDMI20_PHY_Rx_SetTCSAddVal)(int port, UINT8 tcsAddVal);
	int (*HDMI20_PHY_Rx_Initiate_Phy)(int port, int isUD);
	UINT8 (*HDMI20_PHY_Get_TMDS_FREQ)(UINT8 port, int isMSB);
	void (*HDMI20_PHY_UpdatePhyTMDSclock)(UINT8 port);
	int (*HDMI20_PHY_Reset_PLLPDB)(UINT8 port, UINT8 isReset, UINT32 callerId);
	int (*HDMI20_PHY_PowerControl_PLLPDB)(UINT8 port, UINT8 isDown, UINT32 callerId);
	int (*HDMI20_PHY_Restart_TCS)(UINT8 port, UINT8 isRestart, UINT32 callerId);
	int (*HDMI20_PHY_CheckTcsHist)(UINT8 port);
	void (*HDMI20_PHY_InitiateTCSHist)(UINT8 port);
	void (*HDMI20_PHY_UpdateModeSelStatus)(UINT8 port);
	int (*HDMI20_PHY_IsPhyPdbPowerOn)(UINT8 port);
	int (*HDMI20_PHY_Check_TCSError)(UINT8 port);
} HDMI20_PHY_FUNC_POINTER_T;
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
int HDMI20_PHY_InitFunctionPointer(void);

int HDMI20_PHY_InitiatePhySystemCtrl(UINT8 port);
int HDMI20_PHY_Rx_Get_PHYStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall);
void HDMI20_PHY_UpdatePhyLockFlag(UINT8 port);
int HDMI20_PHY_Rx_AccessPhy(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size);
int HDMI20_PHY_ControlPhyPDB(UINT8 port, BOOLEAN bOnOff);
int HDMI20_PHY_Set_3G6G_Mode(UINT8 port, UINT8 isAuto, UINT8 is6G, UINT8 isScrambling, UINT8 lowfreqGain);
int HDMI20_PHY_Reset_ModeSel(UINT8 port, UINT8 isReset, UINT32 callerId);
int HDMI20_PHY_Check_TCSDone(UINT8 port);
int HDMI20_PHY_IsPhyTCSStable(UINT8 port);
int HDMI20_PHY_Update_TMDS_TCS_Value(UINT8 port, int isClear);
int HDMI20_PHY_CheckLinkPhyLock(UINT8 port, int isClear);
int HDMI20_PHY_Reset_EqOffsetCalibration(UINT8 port, UINT8 isReset, UINT32 callerId);
int HDMI20_PHY_Rx_SetTCSAddVal(int port, UINT8 tcsAddVal);
int HDMI20_PHY_Rx_Initiate_Phy(int port, int isUD);
UINT8 HDMI20_PHY_Get_TMDS_FREQ(UINT8 port, int isMSB);
void HDMI20_PHY_UpdatePhyTMDSclock(UINT8 port);
int HDMI20_PHY_Reset_PLLPDB(UINT8 port, UINT8 isReset, UINT32 callerId);
int HDMI20_PHY_PowerControl_PLLPDB(UINT8 port, UINT8 isDown, UINT32 callerId);
int HDMI20_PHY_Restart_TCS(UINT8 port, UINT8 isRestart, UINT32 callerId);
int HDMI20_PHY_CheckTcsHist(UINT8 port);
void HDMI20_PHY_InitiateTCSHist(UINT8 port);
void HDMI20_PHY_UpdateModeSelStatus(UINT8 port);
int HDMI20_PHY_IsPhyPdbPowerOn(UINT8 port);
int HDMI20_PHY_Check_TCSError(UINT8 port);

#endif
