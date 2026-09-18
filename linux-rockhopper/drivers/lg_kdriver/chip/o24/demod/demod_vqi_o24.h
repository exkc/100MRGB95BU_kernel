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

#ifndef	_DEMOD_VQI_H_
#define	_DEMOD_VQI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "demod_impl.h"
#include "DBB_DEMOD_L2_Common_API.h"
#include "DBB_DEMOD_L2_ATSC_API.h"
#include "DBB_DEMOD_L2_ISDB_API.h"

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


extern int DEMOD_O24_VSB_Set_DefaultRegisterValue(void);  //jeongpil.yun
extern int DEMOD_O24_VSB_Set_NeverLockWaitTime(UINT32 waitMs);
extern int DEMOD_O24_VSB_CochannelExist(BOOLEAN *pCochannel);  //jeongpil.yun
extern int DEMOD_O24_VSB_PreMonitor(void);
extern int DEMOD_O24_VSB_Monitor(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_VSB_Get_MSEdynStatus(BOOLEAN *pbEnable);
extern int DEMOD_O24_VSB_Get_TotalInfo( void);

extern int DEMOD_O24_VSB_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_VSB_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);

extern int DEMOD_O24_QAM_SoftwareResetFEC(void); //jeongpil.yun
extern int DEMOD_O24_QAM_Monitor(void);
extern int DEMOD_O24_QAM_ModeAutoDetection(BOOLEAN bEnable);
extern int DEMOD_O24_QAM_64Mode(void);  //jeongpil.yun
extern int DEMOD_O24_QAM_256Mode(void);  //jeongpil.yun
extern int DEMOD_O24_QAM_Set_DefaultRegisterValue(void);  //jeongpil.yun
extern int DEMOD_O24_QAM_Set_NeverLockWaitTime(UINT32 waitMs);
extern int DEMOD_O24_QAM_Get_TotalInfo( void);

extern int DEMOD_O24_QAM_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_QAM_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_QAM_EQ_Signal_Detector(BOOLEAN OnOff);

#if 1
extern int DEMOD_O24_ISDBT_Set_DefaultRegisterValue(void);
extern int DEMOD_O24_ISDBT_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_O24_ISDBT_Set_PartialConfig (LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam);
extern int DEMOD_O24_ISDBT_Set_FullConfig (LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam);
extern int DEMOD_O24_ISDBT_Set_NeverLockWaitTime(UINT32 waitMs);
extern int DEMOD_O24_ISDBT_Set_CrGearshEn(BOOLEAN bEnable);
extern int DEMOD_O24_ISDBT_Set_PhaseNoiseEnhancement(BOOLEAN bEnhanced);
extern int DEMOD_O24_ISDBT_Get_DelaySpreadStatus(UINT16 *pDelaySpread);
extern int DEMOD_O24_ISDBT_Get_FFTMode( LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode );
extern int DEMOD_O24_ISDBT_Get_GuradIntervalMode( LX_DEMOD_GIMODE_T *pGIMode );
extern int DEMOD_O24_ISDBT_Get_TMCCInfo( LX_DEMOD_ISDBT_TMCC_CONFIG_T *pTmccParams);
extern int DEMOD_O24_ISDBT_Get_TotalInfo( void);
extern int DEMOD_O24_ISDBT_Get_IFO_LOCK( BOOLEAN *pIfoLock);
extern int DEMOD_O24_ISDBT_Get_CochanDetIndicator( BOOLEAN *pDetStatus);
extern int DEMOD_O24_ISDBT_MemoryBusCheck(void);
extern int DEMOD_O24_ISDBT_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_ISDBT_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_ISDBT_Set_MemSconfig(void);
extern int DEMOD_O24_ISDBT_GetEmergencyAlertFlagStatus(BOOLEAN *pEalarm);

#endif

extern int DEMOD_O24_ATSC_SW_Init(void);
extern int DEMOD_O24_VSB_SetDemod_Simple(void);


////////////////////ATSC3
extern int DEMOD_O24_ATSC3_SetDemodExpand (DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_ATSC3_Get_FFTMode (LX_DEMOD_FFTMODE_T *pFftMode);
extern int DEMOD_O24_ATSC3_Get_GuradIntervalMode (LX_DEMOD_ATSC3_GIMODE_T *pGIMode);
extern int DEMOD_O24_ATSC3_Get_CodeRate (LX_DEMOD_ATSC3_CODERATE_T *pCodeRate);
extern int DEMOD_O24_ATSC3_Get_Constellation (LX_DEMOD_ATSC3_CONSTELLATION_T *pConstellation);
extern int DEMOD_O24_ATSC3_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_ATSC3_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_ATSC3_Set_PLP (LX_DEMOD_ATSC3_CONFIG_T *pAtsc3ConfigParam);
//extern int DEMOD_O24_ATSC3_Change_PLP (UINT8 unPLP);	// deprecated
extern int DEMOD_O24_ATSC3_Get_MPLP_Info (LX_DEMOD_ATSC3_MULTI_PLP_ID_T *pAtsc3mPLPInfo, LX_DEMOD_ATSC3_MULTI_PLP_ID_SEL_T plpSel);
extern int DEMOD_O24_ATSC3_Set_MemSconfig(void);
extern int DEMOD_O24_ATSC3_Set_OIFType (LX_DEMOD_ATSC3_OIF_TYPE_T *pAtsc3OifType); // htlim



/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DEMOD_DRV_H_ */

/** @} */
