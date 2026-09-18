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

#ifndef	_AAD_H_
#define	_AAD_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/mutex.h>

#include "os_util.h"

#include "../aad_if.h"
#include "aad_cmd.h"
#include "imc/cmd/module_cmd_aad.h"
#include "imc/evt/module_evt_aad.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* Audio AAD IMC Function */
#define MODULE_AAD_NEW                  "aad"

//define Car1 or Car2 SNR is good.
#define AUD_AAD_SNR_GOOD                0

//define delay function and time delay
#define AUD_AAD_SIF_TIME_DELAY_MS(a)    OS_MsecSleep(a)
#define AUD_AAD_SIF_TIME_DELAY_10MS     10
#define AUD_ASD_TIMEOUT_DELAY           (350)       //350ms : Timeout Delay for ASD Auto Mode.

#define AUD_SIGNAL_QUALITY_DELAY_100MS  100         //Signal Quality Delay for ASD Auto Mode with 100ms
#define AUD_SIGNAL_QUALITY_DELAY_300MS  300         //Signal Quality Delay for ASD Auto Mode with 300ms
#define SIGNAL_QUALITY_DELAY_MANUAL_I   300         //Signal Quality Delay for Manual Scan Mode for  I Sysytem
#define SIGNAL_QUALITY_DELAY_MANUAL_BG  500         //Signal Quality Delay for Manual Scan Mode for BG Sysytem
#define SIGNAL_QUALITY_DELAY_MANUAL_DK  700         //Signal Quality Delay for Manual Scan Mode for DK Sysytem
#define AUD_AAD_REG_READ_DELAY          500         //AAD_SIF_TIME_DELAY_MS

//define for default value
#define AUD_ID_MAGNITUDE_THRESHOLD_HI   0x32        // ID Magnitude High for A2
#define AUD_ID_MAGNITUDE_THRESHOLD_LO   0x18        // ID Magnitude Low  for A2
#define AUD_BI_ID_MAGNITUDE_THRESHOLD_HI    0x2A    // Bi ID Magnitude High for A2
#define AUD_BI_ID_MAGNITUDE_THRESHOLD_LO    0x0F    // Bi ID Magnitude Low  for A2

//define CARRIER1 QUALITY Adjust value for weak signal in Auto Scan Mode
#define AUD_CAR1_QUAL_THD_WEAK_SIGNAL_ID_AUTO       0x170   // 0x170

//define CARRIER1 QUALITY Adjust value for DVB ID(Indonesia) weak signal in Manual Tunning
#define AUD_CAR1_QUAL_THD_WEAK_SIGNAL_ID_MAN        0x050   // 0x050
#define AUD_CAR1_QUAL_THD_LOSS_SIGNAL_ID_MAN        0x025   // 0x025


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/* In DVB mode, calls 30ms and in ATSC mode, calls 20ms(maybe) */
#define AAD_DEBUG_MSG_PRINT_TIME_10S    350


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * AAD 4.5MHz and 6.5MHz carrier interpretation mode.
 * This enumeration interpretates the 4.5MHz and 6.5MHz carrier.
 *
 */
typedef enum
{
    AAD_ASD_4_5_MHZ     =   0x00,    ///< 4.5 MHz Carrier Interpretation
    AAD_ASD_6_5_MHZ     =   0x01,    ///< 6.5 MHz Carrier Interpretation
} AAD_ASD_CARRIER_T;

/**
 * Audio AAD SIF Carrier Magnitude and Quality Info.
*/
typedef struct AUD_AAD_SIF_SIGANL_INFO{
    UINT32  ui32Carrier1Magnitude;      ///< The magnitude of input signal for Carrier1
    UINT32  ui32Carrier1Quality;        ///< The quality of input signal for Carrier1
    UINT32  ui32Carrier2Magnitude;      ///< The magnitude of input signal for Carrier2
    UINT32  ui32Carrier2Quality;        ///< The quality of input signal for Carrier2
} AUD_AAD_SIF_CARRIER_INFO_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
/* Related to AAD monitor task */
extern wait_queue_head_t            AUD_AAD_ASD_Task_wait;
extern int                          AUD_AAD_ASD_Task_waitq_flag;

//This value is set by AAD_SIF_InitModule function.
extern LX_AAD_INIT_TYPE_T           g_eAudAadInitType;

//This value is set by Suspend and Resume.
extern bool                         g_bAudAadSuspended;

//This value is set by IOCTL function.
extern bool                         g_bAudHighDevOnOff;

//This value is used by AAD_RegInitAfterAADReset function.
extern LX_AAD_HIGH_DEV_SET_T        g_eAudHighDevMode;

//This value is used by AAD_RegInitAfterAADReset function.
extern LX_AAD_SIF_THRESHOLD_T       g_stAudThresholdLevel;

//This value is set by AAD_SIF_SetBandSetup.
extern LX_AAD_SIF_SOUNDSYSTEM_T     g_i_eAudSystem;

//This value is set by AAD_SIF_SetModeSetup.
extern LX_AAD_SIF_STANDARD_T        g_i_eAudStandard;

//This value is set by AAD_SIF_SetBandSetup.
extern LX_AAD_SIF_STANDARD_INFO_T   g_io_stAudStandardInfo;

//This value is set by AAD_SIF_GetCurAnalogMode.
extern LX_ATV_AUDIO_MODE_GET_T      g_o_eAudAudioMode;

//This value is set by AAD_SIF_SetUserAnalogMode.
extern LX_ATV_AUDIO_MODE_SET_T      g_i_eAudAudioModeSet;

//Current AAD Volume for Audio AAD Module
extern AadCmdSetSoundLevel          g_ui32AudAadVolume;


/*----------------------------------------------------------------------------------------
	Function Prototype Declaration
----------------------------------------------------------------------------------------*/
//AAD function
int AUD_AAD_SIF_SetHighDeviationMode( LX_AAD_HIGH_DEV_SET_T eHighDevMode );
int AUD_AAD_SIF_SetBandSetup( LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem );
int AUD_AAD_SIF_SetModeSetup( LX_AAD_SIF_STANDARD_T eStandard );
int AUD_AAD_SIF_SetUserAnalogMode( LX_ATV_AUDIO_MODE_SET_T eAudioModeSet );
int AUD_AAD_SIF_SetThresholdLevel( SINT32 level );
int AUD_AAD_SIF_GetBandDetect( LX_AAD_SIF_SYSTEM_INFO_T *pstSystemInfo );
int AUD_AAD_SIF_CheckSoundMode( LX_AAD_SIF_STANDARD_INFO_T *pstStandardInfo );
int AUD_AAD_SIF_GetSoundStandardMode( LX_AAD_SIF_STANDARD_T *pStandardMode );
int AUD_AAD_SIF_GetCurAnalogMode( LX_ATV_AUDIO_MODE_GET_T *pAudioMode );
int AUD_AAD_SIF_GetSIFSatus( bool *pSIFStatus );
int AUD_AAD_SIF_SetDataDrop (bool on_off);
int AUD_AAD_SIF_ResumeBandSetup (bool set_audio_mode);

//AAD coredrv get function
LX_AAD_SIF_SOUNDSYSTEM_T AUD_AAD_GetSoundSystem( UINT32 *pSifSystem );
int AUD_AAD_GetCarrierInformation( AUD_AAD_SIF_CARRIER_INFO_T *pstCarrierInfo );
int AUD_AAD_GetSignalStrengthAndQuality( LX_AAD_SIF_SYSTEM_INFO_T *pstSystemInfo );
int AUD_AAD_CheckSoundMode( LX_AAD_SIF_STANDARD_INFO_T *pstStandardInfo );
LX_ATV_AUDIO_MODE_GET_T AUD_AAD_PAL_GetAudioMode( void );
LX_ATV_AUDIO_MODE_GET_T AUD_AAD_NTSC_A2_GetAudioMode( void );
LX_ATV_AUDIO_MODE_GET_T AUD_AAD_NTSC_BTSC_GetAudioMode( void );
int AUD_AAD_GetSIFSatus( bool *pSIFStatus );

//AAD coredrv set function
int AUD_AAD_DetectSoundSystemCb (void *_param, int _paramLen, void *_cbParam);
int AUD_AAD_SetHighDeviationMode( LX_AAD_HIGH_DEV_SET_T eHighDevMode );
int AUD_AAD_A2_SetBandSetup( void );
int AUD_AAD_BTSC_SetBandSetup( void );
int AUD_AAD_PAL_SetBandSetup( void );
int AUD_AAD_ResumeBandSetup( LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem );
int AUD_AAD_SetSoundSystem( LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem );
int AUD_AAD_SetSoundOutputMode( LX_ATV_AUDIO_MODE_SET_T eAudioModeSet );
int AUD_AAD_A2_SetThresholdLevel( SINT32 level );
int AUD_AAD_DetectAutomaticSoundSystem( LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem );
int AUD_AAD_DetectSoundSystemCommandWait( LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem );
int AUD_AAD_SetManualVolumeForAdjust( LX_ATV_AUDIO_MODE_SET_T eAudioModeSet );
int AUD_AAD_SetOutputVolume ( UINT32 gain );
int AUD_AAD_SetDataDrop (bool on_off);

//AAD coredrv debug function
int AUD_AAD_DebugSetAnalogMode( LX_ATV_AUDIO_MODE_SET_T eAudioModeSet, BOOLEAN bNeedToDebug );
int AUD_AAD_DebugCarrierDetection( void );
int AUD_AAD_DebugThresholdLevel( void );
int AUD_AAD_DebugCurAnalogMode( LX_ATV_AUDIO_MODE_GET_T eAudioMode );
int AUD_AAD_DebugCarrierDetection( void );
#ifdef	__cplusplus
}
#endif /* __cplusplus */

int AUD_AAD_GetModuleUID (void);
#endif /* _AAD_H_ */

/** @} */
