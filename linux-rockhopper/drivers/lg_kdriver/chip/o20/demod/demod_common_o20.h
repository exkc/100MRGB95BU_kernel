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
 *  driver interface header for demod device. ( used only within kdriver )
 *	demod device will teach you how to make device driver with new platform.
 *
 *  @author		jeongpil.yun (jeongpil.yun@lge.com)
 *  @version	1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_demod
 *	@{
 */


/*****************************************************************************
**
**  Name:demod_common_m16.h
**
**  Description:    ABB/GBB common block.
**
**  Functions
**  Implemented:   int	DEMOD_O20_ResetHW
**                  int DEMOD_O20_SetI2C
**                  int DEMOD_O20_SetInclk
**                  int DEMOD_O20_AdcInit
**                  int DEMOD_O20_RepeaterEnable
**                  int DEMOD_O20_SoftwareReset
**                  int DEMOD_O20_Serial_Control
**                  int DEMOD_O20_Power_Save
**                  int DEMOD_O20_StdOperModeContrl
**                  int DEMOD_O20_NeverlockScan
**                  int DEMOD_O20_TPOutEnable
**                  int DEMOD_O20_Set_IF_Frq
**                  int DEMOD_O20_Set_AGCPolarity
**                  int DEMOD_O20_Set_SpectrumCtrl
**                  int DEMOD_O20_Get_Id
**                  int DEMOD_O20_Get_SpectrumStatus
**                  int DEMOD_O20_Get_IFAGC
**                  int DEMOD_O20_Get_OperMode
**                  int DEMOD_O20_Get_NeverLockStatus
**                  int DEMOD_O20_Get_CarrierFreqOffset
**                  int DEMOD_O20_Get_TPIFStatus
**                  int DEMOD_O20_Get_VABER
**                  int DEMOD_O20_Get_Packet_Error
**                  int DEMOD_O20_Get_BandWidthMode
**                  int DEMOD_O20_Get_QAMMode
**                  int DEMOD_O20_Get_MseInfo
**                  int DEMOD_O20_Get_Lock
**                  int DEMOD_O20_VSB_Get_SysLockTime
**                  int DEMOD_O20_VSB_Get_FecLockTime
**
**                  int DEMOD_O20_ANALOG_ResetHW
**                  int DEMOD_O20_ANALOG_SetI2C
**                  int DEMOD_O20_ANALOG_Set_AbbMode
**                  int DEMOD_O20_ANALOG_Set_WorkAround
**
**  References:
**
**  Exports:
**
**  Dependencies:   demod_impl.h for system configuration data.
**				 demod_analog_m16.h, demod_reg_O20.h
**
**  Revision History:
**
**     Date        Author          Description
**  -------------------------------------------------------------------------
**   30-12-2009  Jeongpil Yun    Initial draft.
**   31-07-2013   Jeongpil Yun
**
*****************************************************************************/


#ifndef	_DEMOD_COMMON_O20_H_
#define	_DEMOD_COMMON_O20_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "demod_impl.h"
#include "lgdbb/DBB_DEMOD_L2_Common_API.h"
#include "lgdbb/DBB_DEMOD_L2_ATSC_API.h"
#include "lgdbb/DBB_DEMOD_L2_DVB_API.h"
#include "lgdbb/DBB_DEMOD_L2_SAT_API.h"

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
	Function Prototype Declaration
----------------------------------------------------------------------------------------*/
LX_DEMOD_L2_Context * DEMOD_O20_GetContext(void);

int DEMOD_O20_ResetHW(void);
int DEMOD_O20_OperModeReset(LX_DEMOD_OPER_MODE_T operMode);
int DEMOD_O20_SetI2C(void);
int DEMOD_O20_SetInclk(LX_DEMOD_INCLK_SEL_T *inclk);
int DEMOD_O20_AdcInit(void);

int DEMOD_O20_RepeaterEnable(BOOLEAN bEnable);
int DEMOD_O20_SoftwareReset(void);
int DEMOD_O20_Serial_Control(BOOLEAN bEnable);
int DEMOD_O20_Power_Save(BOOLEAN bEnable);
int DEMOD_O20_StdOperModeContrl( LX_DEMOD_OPER_MODE_T operMode, LX_DEMOD_BWMODE_T bandWd, LX_DEMOD_SYMRDET_MODE_T symbr);
int DEMOD_O20_NeverlockScan(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_FLAG_T ResetOn, LX_DEMOD_FLAG_T *pScanProcessing, LX_DEMOD_LOCK_STATE_T *pScanLock);
int DEMOD_O20_TPOutEnable(BOOLEAN bEnable);
int DEMOD_O20_Set_IF_Frq(UINT32 ifFrq);
int DEMOD_O20_Set_AGCPolarity(LX_DEMOD_AGC_POLAR_T agcPola);
int DEMOD_O20_Set_SpectrumCtrl(BOOLEAN bAutoEnable, BOOLEAN bSpecInvEnable);
int DEMOD_O20_Get_Id(UINT8 *pCellIDLength, UINT16 *cell_id);
int DEMOD_O20_Get_SpectrumStatus(LX_DEMOD_LOCK_STATE_T *pSpectrumAuto, LX_DEMOD_LOCK_STATE_T *pSpectrumInv);
int DEMOD_O20_Get_IFAGC(UINT16 *pIfAgc);
int DEMOD_O20_Get_OperMode(LX_DEMOD_OPER_MODE_T *pOperMode);
int DEMOD_O20_Get_NeverLockStatus(LX_DEMOD_OPER_MODE_T scanMode, LX_DEMOD_LOCK_STATE_T *pNeverLockStatus);
int DEMOD_O20_Get_CarrierFreqOffset(SINT32 *pFreqOff);
int DEMOD_O20_Get_TPIFStatus(BOOLEAN *pbEnable);
int DEMOD_O20_Get_VABER(UINT32 *pVber);
int DEMOD_O20_Get_Packet_Error(UINT32 *pError);
int DEMOD_O20_Get_BandWidthMode( LX_DEMOD_BWMODE_T *ChannelBW );
int DEMOD_O20_Get_QAMMode( LX_DEMOD_RF_MODE_T *pQamMode );
int DEMOD_O20_Get_MseInfo( LX_DEMOD_MSE_T *pSigMse);
int DEMOD_O20_Get_Lock(LX_DEMOD_LOCK_STATUS_T whatLock, LX_DEMOD_LOCK_STATE_T *lockState);
int DEMOD_O20_VSB_Get_SysLockTime(UINT16 *pSyslocktime);
int DEMOD_O20_VSB_Get_FecLockTime(UINT16 *pFeclocktime);
int DEMOD_O20_FecReset(BOOLEAN bReset);
int DEMOD_O20_CountryGrpSetting(BOOLEAN bEnable);
int DEMOD_O20_DVB_Set_MemSconfig(void);
int DEMOD_O20_GetTsClkRate (UINT32 *demodTsClkRate);

int DEMOD_O20_ANALOG_ResetHW(void);
int DEMOD_O20_ANALOG_SetI2C(void);
int DEMOD_O20_ANALOG_Set_AbbMode(BOOLEAN bIsAbbMode);

int DEMOD_O20_Get_I2C_Handle(UINT8 portI2C, UINT16 deviceID);

int DEMOD_O20_FW_Configuration_Initialize(LX_DEMOD_OPER_MODE_T operMode);
int DEMOD_O20_Opermode(DEMOD_CTX_T *pDemodInfo);
int DEMOD_O20_Debug_ReadREGvalue (UINT16 address, UINT32 *pData);
int DEMOD_O20_Debug_ATSC_ReadREGvalue(UINT16 address, UINT32 *pData);
int DEMOD_O20_Debug_ATSC_WriteREGvalue(UINT16 address, UINT32 *pData);
int DEMOD_O20_Get_BW(DEMOD_CTX_T *pDemodInfo, UINT16 *pter_bandwidth_KHz);
int DEMOD_O20_Get_FW_PartInfo(UINT32 *pFW_Info);
int DEMOD_O20_Get_Dump(void);
int DEMOD_O20_ADC_Enable (void);

int DEMOD_O20_Get_Signal_Information(LX_DEMOD_SIGNAL_TOTAL_T *pSignalStatus);
int DEMOD_O20_Get_CFG_Information(LX_DEMOD_SIGNAL_TUNE_CFG_T *pSignalStatus);
int DEMOD_O20_DVBC_reset(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	unsigned int 	g_NewTuneReqeustTime;
extern	unsigned int 	g_RetuneStartTime;
extern	UINT64 		pauseTimeDemod ;
extern	UINT32 		notifyinglockTimeOut;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DEMOD_DRV_H_ */

/** @} */
