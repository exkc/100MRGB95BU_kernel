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
 * date       2019.04.23
 * note       Additional information.
 *
 * @addtogroup lg11xxx_sys
 * @{
 */
#ifndef __HDMI21_RX_PHY_H__
#define __HDMI21_RX_PHY_H__


/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "reg_ctrl.h"
#include "sys_reg_base.h"
#include "hdmi21_hal_driver.h"
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
	int 	(*HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl)(UINT8 port);
	int 	(*HDMI21_PHY_Rx_Get_PhyStatus)(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall);
	void	(*HDMI21_PHY_Rx_Get_UpdatePhyLockFlag)(UINT8 port);
	int		(*HDMI21_PHY_Rx_Set_AccessPhy)(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size);
	int 	(*HDMI21_PHY_Rx_Set_ControlPhyPdb)(UINT8 port, BOOLEAN bOnOff);
	int 	(*HDMI21_PHY_Rx_Set_3g6gMode)(UINT8 port, UINT8 isAuto, HDMI21_HAL_PHY_INITIATED_MODE_T mode, UINT8 isScrambling, UINT8 lowfreqGain);
	int 	(*HDMI21_PHY_Rx_Set_CheckTcsDone)(UINT8 port);
	int 	(*HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration)(UINT8 port, UINT8 isReset, UINT32 callerId);

	int 	(*HDMI21_PHY_Rx_Set_Initiate_Phy)(int port, HDMI21_HAL_PHY_INITIATED_MODE_T mode);
	UINT8 	(*HDMI21_PHY_Rx_Get_TmdsFreq)(UINT8 port, int isMSB);
	void 	(*HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock)(UINT8 port);
	int 	(*HDMI21_PHY_Rx_Set_ResetPllPdb)(UINT8 port, UINT8 isReset, UINT32 callerId);
	int 	(*HDMI21_PHY_Rx_Set_PowerControlPllPdb)(UINT8 port, UINT8 isDown, UINT32 callerId);
	int 	(*HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn)(UINT8 port);
	void	(*HDMI21_PHY_Rx_Set_InitiateDfeCenter)(UINT8 port);
	int		(*HDMI21_PHY_Rx_Get_CheckDfeDone)(UINT8 port);
	int 	(*HDMI21_PHY_Rx_Set_ToggleTCSEn)(int port, int isSet);
	int 	(*HDMI21_PHY_Rx_Get_CheckDfeResult)(UINT8 port);

	int  	(*HDMI21_PHY_Rx_Get_CheckEqCalDone)(int port);
	void 	(*HDMI21_PHY_Rx_Set_SaffManualValue)(int port);
	void 	(*HDMI21_PHY_Rx_Get_SaffValue)(int port);
} HDMI21_PHY_FUNC_POINTER_T;
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
int		HDMI21_PHY_Rx_Set_InitFunctionPointer(void);

int 	HDMI21_PHY_Rx_Set_InitiatePhySystemCtrl(UINT8 port);
int 	HDMI21_PHY_Rx_Get_PhyStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall);
void 	HDMI21_PHY_Rx_Get_UpdatePhyLockFlag(UINT8 port);
int 	HDMI21_PHY_Rx_Set_AccessPhy(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size);
int 	HDMI21_PHY_Rx_Set_ControlPhyPdb(UINT8 port, BOOLEAN bOnOff);
int 	HDMI21_PHY_Rx_Set_3g6gMode(UINT8 port, UINT8 isAuto, HDMI21_HAL_PHY_INITIATED_MODE_T mode, UINT8 isScrambling, UINT8 lowfreqGain);
int 	HDMI21_PHY_Rx_Set_CheckTcsDone(UINT8 port);
int 	HDMI21_PHY_Rx_Set_ResetEqOffsetCalibration(UINT8 port, UINT8 isReset, UINT32 callerId);

int 	HDMI21_PHY_Rx_Set_Initiate_Phy(int port, HDMI21_HAL_PHY_INITIATED_MODE_T mode);
UINT8 	HDMI21_PHY_Rx_Get_TmdsFreq(UINT8 port, int isMSB);
void 	HDMI21_PHY_Rx_Set_UpdatePhyTmdsClock(UINT8 port);
int 	HDMI21_PHY_Rx_Set_ResetPllPdb(UINT8 port, UINT8 isReset, UINT32 callerId);
int 	HDMI21_PHY_Rx_Set_PowerControlPllPdb(UINT8 port, UINT8 isDown, UINT32 callerId);
int 	HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn(UINT8 port);
void	HDMI21_PHY_Rx_Set_InitiateDfeCenter(UINT8 port);
int 	HDMI21_PHY_Rx_Get_CheckDfeDone(UINT8 port);
int 	HDMI21_PHY_Rx_Set_ToggleTCSEn(int port, int isSet);
int 	HDMI21_PHY_Rx_Get_CheckDfeResult(UINT8 port);

int  	HDMI21_PHY_Rx_Get_CheckEqCalDone(int port);
void 	HDMI21_PHY_Rx_Set_SaffManualValue(int port);
void 	HDMI21_PHY_Rx_Get_SaffValue(int port);
#endif
