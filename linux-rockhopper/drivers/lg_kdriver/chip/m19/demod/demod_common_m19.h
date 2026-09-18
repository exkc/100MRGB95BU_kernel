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
**  Implemented:   int	DEMOD_M19_ResetHW
**                  int DEMOD_M19_SetI2C
**                  int DEMOD_M19_SetInclk
**                  int DEMOD_M19_AdcInit
**                  int DEMOD_M19_RepeaterEnable
**                  int DEMOD_M19_SoftwareReset
**                  int DEMOD_M19_Serial_Control
**                  int DEMOD_M19_Power_Save
**                  int DEMOD_M19_StdOperModeContrl
**                  int DEMOD_M19_NeverlockScan
**                  int DEMOD_M19_TPOutEnable
**                  int DEMOD_M19_Set_IF_Frq
**                  int DEMOD_M19_Set_AGCPolarity
**                  int DEMOD_M19_Set_SpectrumCtrl
**                  int DEMOD_M19_Get_Id
**                  int DEMOD_M19_Get_SpectrumStatus
**                  int DEMOD_M19_Get_IFAGC
**                  int DEMOD_M19_Get_OperMode
**                  int DEMOD_M19_Get_NeverLockStatus
**                  int DEMOD_M19_Get_CarrierFreqOffset
**                  int DEMOD_M19_Get_TPIFStatus
**                  int DEMOD_M19_Get_VABER
**                  int DEMOD_M19_Get_Packet_Error
**                  int DEMOD_M19_Get_BandWidthMode
**                  int DEMOD_M19_Get_QAMMode
**                  int DEMOD_M19_Get_MseInfo
**                  int DEMOD_M19_Get_Lock
**                  int DEMOD_M19_VSB_Get_SysLockTime
**                  int DEMOD_M19_VSB_Get_FecLockTime
**
**                  int DEMOD_M19_ANALOG_ResetHW
**                  int DEMOD_M19_ANALOG_SetI2C
**                  int DEMOD_M19_ANALOG_Set_AbbMode
**                  int DEMOD_M19_ANALOG_Set_WorkAround
**
**  References:
**
**  Exports:
**
**  Dependencies:   demod_impl.h for system configuration data.
**				 demod_analog_m16.h, demod_reg_M19.h
**
**  Revision History:
**
**     Date        Author          Description
**  -------------------------------------------------------------------------
**   30-12-2009  Jeongpil Yun    Initial draft.
**   31-07-2013   Jeongpil Yun
**
*****************************************************************************/


#ifndef	_DEMOD_COMMON_M19_H_
#define	_DEMOD_COMMON_M19_H_

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

//#include "lgdbb/M16P_DEMOD_firmware_0_7_0.h"
#include "lgdbb/M19_SAT_DEMOD_firmware_A_0_1.h"
#include "lgdbb/M19_TER_DEMOD_firmware_A_0_1.h"

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
extern int DEMOD_M19_ResetHW(void);
extern int DEMOD_M19_OperModeReset(LX_DEMOD_OPER_MODE_T operMode);
extern int DEMOD_M19_SetI2C(void);
extern int DEMOD_M19_SetInclk(LX_DEMOD_INCLK_SEL_T *inclk);
extern int DEMOD_M19_AdcInit(void);

extern int DEMOD_M19_RepeaterEnable(BOOLEAN bEnable);
extern int DEMOD_M19_SoftwareReset(void);
extern int DEMOD_M19_Serial_Control(BOOLEAN bEnable);
extern int DEMOD_M19_Power_Save(BOOLEAN bEnable);
extern int DEMOD_M19_StdOperModeContrl( LX_DEMOD_OPER_MODE_T operMode, LX_DEMOD_BWMODE_T bandWd, LX_DEMOD_SYMRDET_MODE_T symbr);
extern int DEMOD_M19_NeverlockScan(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_FLAG_T ResetOn, LX_DEMOD_FLAG_T *pScanProcessing, LX_DEMOD_LOCK_STATE_T *pScanLock);
extern int DEMOD_M19_TPOutEnable(BOOLEAN bEnable);
extern int DEMOD_M19_Set_IF_Frq(UINT32 ifFrq);
extern int DEMOD_M19_Set_AGCPolarity(LX_DEMOD_AGC_POLAR_T agcPola);
extern int DEMOD_M19_Set_SpectrumCtrl(BOOLEAN bAutoEnable, BOOLEAN bSpecInvEnable);
extern int DEMOD_M19_Get_Id(UINT8 *pCellIDLength, UINT16 *cell_id);
extern int DEMOD_M19_Get_SpectrumStatus(LX_DEMOD_LOCK_STATE_T *pSpectrumAuto, LX_DEMOD_LOCK_STATE_T *pSpectrumInv);
extern int DEMOD_M19_Get_IFAGC(UINT16 *pIfAgc);
extern int DEMOD_M19_Get_OperMode(LX_DEMOD_OPER_MODE_T *pOperMode);
extern int DEMOD_M19_Get_NeverLockStatus(LX_DEMOD_OPER_MODE_T scanMode, LX_DEMOD_LOCK_STATE_T *pNeverLockStatus);
extern int DEMOD_M19_Get_CarrierFreqOffset(SINT32 *pFreqOff);
extern int DEMOD_M19_Get_TPIFStatus(BOOLEAN *pbEnable);
extern int DEMOD_M19_Get_VABER(UINT32 *pVber);
extern int DEMOD_M19_Get_Packet_Error(UINT32 *pError);
extern int DEMOD_M19_Get_BandWidthMode( LX_DEMOD_BWMODE_T *ChannelBW );
extern int DEMOD_M19_Get_QAMMode( LX_DEMOD_RF_MODE_T *pQamMode );
extern int DEMOD_M19_Get_MseInfo( LX_DEMOD_MSE_T *pSigMse);
extern int DEMOD_M19_Get_Lock(LX_DEMOD_LOCK_STATUS_T whatLock, LX_DEMOD_LOCK_STATE_T *lockState);
extern int DEMOD_M19_VSB_Get_SysLockTime(UINT16 *pSyslocktime);
extern int DEMOD_M19_VSB_Get_FecLockTime(UINT16 *pFeclocktime);
extern int DEMOD_M19_FecReset(BOOLEAN bReset);
extern int DEMOD_M19_CountryGrpSetting(BOOLEAN bEnable);
extern int DEMOD_M19_DVB_Set_MemSconfig(void);

extern int DEMOD_M19_ANALOG_ResetHW(void);
extern int DEMOD_M19_ANALOG_SetI2C(void);
extern int DEMOD_M19_ANALOG_Set_AbbMode(BOOLEAN bIsAbbMode);

extern int	DEMOD_M19_Get_I2C_Handle(UINT8 portI2C, UINT16 deviceID);
extern int  DEMOD_M19_FW_Initialize(void);
extern int	DEMOD_M19_SAT_FW_Initialize(void);
extern int	DEMOD_M19_ALL_FW_Initialize(void);
extern int	DEMOD_M19_FW_Configuration_Initialize(LX_DEMOD_OPER_MODE_T operMode);
extern int 	DEMOD_M19_Opermode(DEMOD_CTX_T *pDemodInfo);
extern int 	DEMOD_M19_Debug_ATSC_ReadREGvalue(UINT16 address, UINT32 *pData);
extern int 	DEMOD_M19_Debug_ATSC_WriteREGvalue(UINT16 address, UINT32 *pData);
extern int  DEMOD_M19_Get_BW(DEMOD_CTX_T *pDemodInfo, UINT16 *pter_bandwidth_KHz);
extern int 	DEMOD_M19_Get_FW_PartInfo(UINT32 *pFW_Info);
extern int	DEMOD_M19_Get_Dump(void);
extern int 	DEMOD_M19_Get_Signal_Information(LX_DEMOD_SIGNAL_TOTAL_T *pSignalStatus);
extern int 	DEMOD_M19_Get_CFG_Information(LX_DEMOD_SIGNAL_TUNE_CFG_T *pSignalStatus);
extern int	DEMOD_M19_DVBC_reset(void);
extern int	DEMOD_M19_ADC_Enable (void);



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
