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

#ifndef	_DEMOD_SAT_O22_H_
#define	_DEMOD_SAT_O22_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "demod_impl.h"
#include "DBB_DEMOD_L2_Common_API.h"
#include "DBB_DEMOD_L2_SAT_API.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define DISEQC_END_GAP_VALUE		30
#define DISEQC_TX_GAP_VALUE 		150
#define DISEQC_IDLE_GAP_VALUE		30
#define DISEQC_RX_GAP_VALUE		300
#define DVBS_FFT_SIZE				32768
#define DVBS_DC_RANGE_BW			110 //khz

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

extern int DEMOD_O24_DVBS_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_O24_DVBS_Set_FullConfig (LX_DEMOD_DVBS_CONFIG_T *pDvbsConfigParam);
extern int DEMOD_O24_DVBS_Get_CoderRate( LX_DEMOD_CODERATE_T *pCodeRate );
extern int DEMOD_O24_DVBS_Get_SymbolRate( UINT32 *pSymbolRate );
extern int DEMOD_O24_DVBS_Get_TotalInfo( void);
extern int DEMOD_O24_DVBS_Set_DiseqcToneMessageCtrl( LX_DEMOD_DVBS_DiSEqC_MSG_T *pDiseqcMsg);
extern int DEMOD_O24_DVBS_Get_BlindInfo(UINT32 centerFreq, LX_DEMOD_DVBS_BLIND_PARAM_T *pBlindParam);

extern int DEMOD_O24_DVBS_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_DVBS_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);

extern int DEMOD_O24_DVBS2_Set_Config_auto (BOOLEAN bAutoDetect);
extern int DEMOD_O24_DVBS2_Set_FullConfig (LX_DEMOD_DVBS2_CONFIG_T *pDvbs2ConfigParam);
extern int DEMOD_O24_DVBS2_Get_CoderRate( LX_DEMOD_CODERATE_T *pCodeRate );
extern int DEMOD_O24_DVBS2_Get_Pilot( BOOLEAN *pPilot );
extern int DEMOD_O24_DVBS2_Get_SymbolRate( UINT32 *pSymbolRate );
extern int DEMOD_O24_DVBS2_Get_TotalInfo( void);

extern int DEMOD_O24_DVBS2_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_DVBS2_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo);
extern int DEMOD_O24_DVBSX_BlindScan_Init(LX_DEMOD_BLIND_SCAN_INIT_FREQ_PARAM_T *initFreq);
extern int DEMOD_O24_DVBSX_BlindScan_End(void);
extern int DEMOD_O24_DVBSX_Get_TunerFreq(LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T *freqInfo);
extern int DEMOD_O24_DVBSX_Get_OffsetFreq(LX_DEMOD_BLIND_SCAN_OFFSET_PARAM_T *pOffsetInfo);
extern int DEMOD_O24_DVBSX_SymbolRate_Detec(void);
extern int DEMOD_O24_DVBSX_BlindLock_Loop(void);
extern int DEMOD_O24_DVBSX_Get_Nextfreq_Status(BOOLEAN* pBlindScanEnd);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DEMOD_SAT_O22_H_ */

/** @} */
