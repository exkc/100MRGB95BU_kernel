/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2020 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include "os_util.h"            //for alloc functions
#include <linux/kthread.h>

#include "aad.h"
#include "ipc_regs.h"

#include "log.h"

logm_define (aad_cfg, log_level_noti);
#define trace(fmt,args...)  logm_trace(aad_cfg,fmt,##args)
#define debug(fmt,args...)  logm_debug(aad_cfg,fmt,##args)
#define info(fmt,args...)   logm_info(aad_cfg,fmt,##args)
#define noti(fmt,args...)   logm_noti(aad_cfg,fmt,##args)
#define warn(fmt,args...)   logm_warning(aad_cfg,fmt,##args)
#define error(fmt,args...)  logm_error(aad_cfg,fmt,##args)


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


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void _AUD_AAD_SetMNA2SoundOutputMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet);
static void _AUD_AAD_SetPALA2SoundOutputMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet);
static void _AUD_AAD_SetBTSCSoundOutputMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet);
static void _AUD_AAD_SetNICAMSoundOutputMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet);

static SINT32 _AUD_AAD_CheckSoundSystemDetection (void);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * callback function to notify audio aad system detect action.
 * @see     _AUD_AAD_RegisterEvent().
 */
int AUD_AAD_DetectSoundSystemCb (void *_param, int _paramLen, void *_cbParam)
{
    UINT32 sifSystem;

    LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem;

    AadEvtResultSystem *pAadEvtResultSystem = (AadEvtResultSystem *) _param;

    if (_paramLen != sizeof (AadEvtResultSystem))
    {
        error ("Param Length Error[Expected:%zd][Input:%d]\n",
            sizeof (AadEvtResultSystem), _paramLen);
        return RET_ERROR;
    }

    //Check a Band Detect Started.
    if (AUD_AAD_ASD_Task_waitq_flag == 0)
    {
        //Signal ASD is completed.
        AUD_AAD_ASD_Task_waitq_flag = 1;
        wake_up_interruptible (&AUD_AAD_ASD_Task_wait);
    }

    //Save a audio aad system detect.
    noti ("system(%d)\n", pAadEvtResultSystem->system);

    //Get a audio system to be detected.
    eSoundSystem = AUD_AAD_GetSoundSystem (&sifSystem);

    //Check a audio system to be detected.
    if (eSoundSystem != g_i_eAudSystem)
        noti ("eSoundSystem(%d), g_i_eAudSystem(%d), g_i_eAudStandard(%d)\n",
            eSoundSystem, g_i_eAudSystem, g_i_eAudStandard);

    return RET_OK;
}

/**
 * Set a High Deviaton Level Value function.
*/
int AUD_AAD_SetHighDeviationMode (LX_AAD_HIGH_DEV_SET_T eHighDevMode)
{
    // Level_Off = 0; //  50Khz
    // Level_1       = 1; // 100Khz
    // Level_2       = 2; // 200Khz
    // Level_3       = 3; // 300Khz
    // Level_4       = 4; // 400Khz
    // Level_5       = 5; // 500Khz
    // Level_Auto= 6; // Auto
    //unsigned int HighDevLevel;

    AadCmdSetHighDevLevel filterMode = { };

    //Set a High Deviation Mode(Demod Filter)
    if (eHighDevMode.highDevLevel == LX_AAD_HIGH_DEV_LEVEL_OFF)
        filterMode.high_dev_level = 0;  //50Khz
    else if (eHighDevMode.highDevLevel == LX_AAD_HIGH_DEV_LEVEL_1)
        filterMode.high_dev_level = 1;  //100Khz
    else if (eHighDevMode.highDevLevel == LX_AAD_HIGH_DEV_LEVEL_2)
        filterMode.high_dev_level = 2;  //200Khz
    else if (eHighDevMode.highDevLevel == LX_AAD_HIGH_DEV_LEVEL_3)
        filterMode.high_dev_level = 4;  //400Khz
    else if (eHighDevMode.highDevLevel == LX_AAD_HIGH_DEV_LEVEL_4)
        filterMode.high_dev_level = 5;  //500Khz
    else
    {
        error ("HighDevLevel %d\n", eHighDevMode.highDevLevel);
        return RET_ERROR;
    }

    //Set high deviation level
    aimc_send_command (NULL, AAD_CMD_SET_HIGH_DEV_LEVEL, 0,
        AUD_AAD_GetModuleUID (), &filterMode, sizeof (AadCmdSetHighDevLevel));
    debug ("HighDevLevel = %d\n", filterMode.high_dev_level);

    return RET_OK;
}

/**
 * Set a A2 Band Setup function.
*/
int AUD_AAD_A2_SetBandSetup (void)
{
    AadCmdSetMNIDLevel thLevel = { };
    AadCmdSetAutoSoundMode autoSoundMode = { };

#ifdef ENABLE_AAD_TEST_MODE     //test only
#else

    //unsigned int mn_id_threshold_high;    //default 0x32
    //unsigned int mn_id_threshold_low;             //default 0x18
    //unsigned int mn_biid_threshold_high;  // default 0x2a
    //unsigned int mn_biid_threshold_low;   // default 0x0f

    //Set A2 threshold level
    thLevel.mn_id_threshold_high = g_stAudThresholdLevel.stereoIDMagHigh;
    thLevel.mn_id_threshold_low = g_stAudThresholdLevel.stereoIDMagLow;
    thLevel.mn_biid_threshold_high = AUD_BI_ID_MAGNITUDE_THRESHOLD_HI;
    thLevel.mn_biid_threshold_low = AUD_BI_ID_MAGNITUDE_THRESHOLD_LO;

    //Set MN ID Threshold command
    aimc_send_command (NULL, AAD_CMD_SET_MN_ID_LEVEL, 0,
        AUD_AAD_GetModuleUID (), &thLevel, sizeof (AadCmdSetMNIDLevel));
    debug ("mn_id_threshold_level = %d\n", thLevel.mn_id_threshold_high);
#endif //#ifndef       ENABLE_AAD_TEST_MODE    //test only

    //  0 ; Auto Sound Mode Off
    //  1 ; Auto Sound Mode On
    //unsigned int auto_sound_mode;

    //Set Auto Sound Mode Off
    autoSoundMode.auto_sound_mode = 0;

    //Set Auto Sound Mode command
    aimc_send_command (NULL, AAD_CMD_SET_AUTO_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &autoSoundMode, sizeof (AadCmdSetAutoSoundMode));
    debug ("auto_sound_mode = %d\n", autoSoundMode.auto_sound_mode);
    return RET_OK;
}

/**
 * Set a BTSC Band Setup function.
*/
int AUD_AAD_BTSC_SetBandSetup (void)
{
    AadCmdSetAutoSoundMode autoSoundMode = { };

    //  0 ; Auto Sound Mode Off
    //  1 ; Auto Sound Mode On
    //unsigned int auto_sound_mode;

    //Set Auto Sound Mode Off
    autoSoundMode.auto_sound_mode = 0;

    //Set Auto Sound Mode command
    aimc_send_command (NULL, AAD_CMD_SET_AUTO_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &autoSoundMode, sizeof (AadCmdSetAutoSoundMode));
    debug ("auto_sound_mode = %d\n", autoSoundMode.auto_sound_mode);

    return RET_OK;
}

/**
 * Set a PAL Band Setup function.
*/
int AUD_AAD_PAL_SetBandSetup (void)
{
    AadCmdSetMNIDLevel thLevel = { };
    AadCmdSetAutoSoundMode autoSoundMode = { };

    //unsigned int mn_id_threshold_high;    //default 0x32
    //unsigned int mn_id_threshold_low;             //default 0x18
    //unsigned int mn_biid_threshold_high;  // default 0x2a
    //unsigned int mn_biid_threshold_low;   // default 0x0f

    //Set A2 threshold level
    thLevel.mn_id_threshold_high = g_stAudThresholdLevel.stereoIDMagHigh;
    thLevel.mn_id_threshold_low = g_stAudThresholdLevel.stereoIDMagLow;
    thLevel.mn_biid_threshold_high = AUD_BI_ID_MAGNITUDE_THRESHOLD_HI;
    thLevel.mn_biid_threshold_low = AUD_BI_ID_MAGNITUDE_THRESHOLD_LO;

    //Set MN ID Threshold command
    aimc_send_command (NULL, AAD_CMD_SET_MN_ID_LEVEL, 0,
        AUD_AAD_GetModuleUID (), &thLevel, sizeof (AadCmdSetMNIDLevel));

    //  0 ; Auto Sound Mode Off
    //  1 ; Auto Sound Mode On
    //unsigned int auto_sound_mode;

    //Check a AJJA and India model for previous model.
    if ((g_eAudAadInitType == LX_AAD_INIT_DVB_AJJA_SELECT)
        || (g_eAudAadInitType == LX_AAD_INIT_DVB_CN_SELECT
            && g_i_eAudSystem == LX_AAD_SIF_SYSTEM_MN)
        || (g_eAudAadInitType == LX_AAD_INIT_DVB_IN_SELECT && g_bAudHighDevOnOff == true))
    {
        //Set Auto Sound Mode Off
        autoSoundMode.auto_sound_mode = 0;
    }
    else
    {
        //Set Auto Sound Mode Off
        autoSoundMode.auto_sound_mode = 1;
    }

    //Set Auto Sound Mode command
    aimc_send_command (NULL, AAD_CMD_SET_AUTO_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &autoSoundMode, sizeof (AadCmdSetAutoSoundMode));
    debug ("auto_sound_mode = %d\n", autoSoundMode.auto_sound_mode);

    return RET_OK;
}

/**
 * Resume a Audio Sound System function after suspend.
*/
int AUD_AAD_ResumeBandSetup (LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem)
{
    if (lx_chip () != LX_CHIP_O22)
    {
        //Reset a kmna2_mul21 value.
        g_ui32AudAadVolume.kmna2_mul21 = 0x1A6E1F;
    }

    //Reset a kbtsc_mono_mul21 value.
    g_ui32AudAadVolume.kbtsc_mono_mul21 = 0x10AA3F;     //BTSC Mono

    //Set A2/BTSC mode
    if (eSoundSystem == LX_AAD_SIF_SYSTEM_MN)
    {
        //Check a BTSC audio system
        if (g_eAudAadInitType == LX_AAD_INIT_ATSC_BTSC_SELECT)
        {
            //Set a BTSC Band Setup
            (void) AUD_AAD_BTSC_SetBandSetup ();
        }
        else
        {
            //Set a A2 Band Setup
            (void) AUD_AAD_A2_SetBandSetup ();
        }
    }
    else
    {
        //Set a PAL Band Setup
        (void) AUD_AAD_PAL_SetBandSetup ();
    }

    //Set a Audio Sound System
    (void) AUD_AAD_SetSoundSystem (eSoundSystem);

    //Reset audio mode in channel is changed.
    g_o_eAudAudioMode = LX_ATV_GET_NTSC_BTSC_UNKNOWN;
    g_io_stAudStandardInfo.detectedStandard = LX_AAD_SIF_NOT_AVAILE;
    g_io_stAudStandardInfo.availability = LX_AAD_SIF_DETECTING_EXSISTANCE;

    noti ("eSoundSystem = %d\n", eSoundSystem);
    return RET_OK;
}

/**
 * Set a Audio Sound System function.
*/
int AUD_AAD_SetSoundSystem (LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem)
{
    int eRetVal = RET_OK;

    AadCmdSetBand bandMode = { };

    // BG = 0;
    // I  = 1;
    // DK = 2;
    // L  = 3;
    // MNA2 = 4;
    // BTSC = 5;
    // BG_MONO = 6;
    //unsigned int band;
    //unsigned int band_search_en;  //0; disable, 1 ; Once Search enable, 2; Continuous Search

    // Set a sound system as same as previous sound system if sound system is unknown.
    if (eSoundSystem == LX_AAD_SIF_SYSTEM_UNKNOWN)
        eSoundSystem = g_i_eAudSystem;

    switch (eSoundSystem)
    {
        case LX_AAD_SIF_SYSTEM_BG:
            //Set a PAL B India A2 Signal to surpress audio noise.
            if (g_eAudAadInitType == LX_AAD_INIT_DVB_IN_SELECT && g_bAudHighDevOnOff == true)
            {
                //Set BG Audio Mode
                bandMode.band = 6;      //BG_MONO
                bandMode.band_search_en = 0;    //disable
            }
            else
            {
                //Set BG Audio Mode
                bandMode.band = 0;      //BG
                bandMode.band_search_en = 2;    //Continuous Search
            }
            break;

        case LX_AAD_SIF_SYSTEM_I:
            //Set I Audio Mode
            bandMode.band = 1;  //I
            bandMode.band_search_en = 0;        //disable
            break;

        case LX_AAD_SIF_SYSTEM_DK:
            //Set D/K Audio Mode
            bandMode.band = 2;  //D/K
            bandMode.band_search_en = 2;        //Continuous Search
            break;

        case LX_AAD_SIF_SYSTEM_L:
            //Set L Audio Mode
            bandMode.band = 3;  //L
            bandMode.band_search_en = 0;        //disable
            break;

        case LX_AAD_SIF_SYSTEM_MN:
            if (g_eAudAadInitType == LX_AAD_INIT_ATSC_BTSC_SELECT)
            {
                //Set BTSC Audio Mode
                bandMode.band = 5;      //BTSC
                bandMode.band_search_en = 0;    //disable
            }
            else
            {
                //Set A2 Audio Mode
                bandMode.band = 4;      //MNA2
                bandMode.band_search_en = 0;    //disable
            }
            break;

        case LX_AAD_SIF_SYSTEM_UNKNOWN:
        default:
            eRetVal = RET_INVALID_PARAMS;

            debug ("eSoundSystem = %d\n", eSoundSystem);
            return eRetVal;
    }

    //Set Analog Audio A2 Sound Mode command
    aimc_send_command (NULL, AAD_CMD_SET_BAND, 0,
        AUD_AAD_GetModuleUID (), &bandMode, sizeof (AadCmdSetBand));
    debug ("band = %d, search = %d\n", bandMode.band, bandMode.band_search_en);

    return eRetVal;
}

/**
 * Set a Audio Sound Ouput Mode function.
*/
int AUD_AAD_SetSoundOutputMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet)
{
    //Set a Audio Ouput Mode
    if ((eAudioModeSet == LX_ATV_SET_NTSC_A2_MONO) || (eAudioModeSet == LX_ATV_SET_NTSC_A2_STEREO)
        || (eAudioModeSet == LX_ATV_SET_NTSC_A2_SAP)
        || (eAudioModeSet == LX_ATV_SET_NTSC_A2_UNKNOWN))
    {
        //Set a M/N A2 sound output mode
        _AUD_AAD_SetMNA2SoundOutputMode (eAudioModeSet);
    }
    else if ((eAudioModeSet == LX_ATV_SET_PAL_MONO) || (eAudioModeSet == LX_ATV_SET_PAL_STEREO)
        || (eAudioModeSet == LX_ATV_SET_PAL_DUALI) || (eAudioModeSet == LX_ATV_SET_PAL_DUALII)
        || (eAudioModeSet == LX_ATV_SET_PAL_DUALI_II)
        || (eAudioModeSet == LX_ATV_SET_PAL_MONO_FORCED)
        || (eAudioModeSet == LX_ATV_SET_PAL_STEREO_FORCED)
        || (eAudioModeSet == LX_ATV_SET_PAL_UNKNOWN))
    {
        //Set a PAL A2 sound output mode
        _AUD_AAD_SetPALA2SoundOutputMode (eAudioModeSet);
    }
    else if ((eAudioModeSet == LX_ATV_SET_NTSC_BTSC_MONO)
        || (eAudioModeSet == LX_ATV_SET_NTSC_BTSC_STEREO)
        || (eAudioModeSet == LX_ATV_SET_NTSC_BTSC_SAP_MONO)
        || (eAudioModeSet == LX_ATV_SET_NTSC_BTSC_SAP_STEREO)
        || (eAudioModeSet == LX_ATV_SET_NTSC_BTSC_UNKNOWN))
    {
        //Set a BTSC sound output mode
        _AUD_AAD_SetBTSCSoundOutputMode (eAudioModeSet);
    }
    else if ((eAudioModeSet == LX_ATV_SET_PAL_NICAM_MONO)
        || (eAudioModeSet == LX_ATV_SET_PAL_NICAM_STEREO)
        || (eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUALI)
        || (eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUALII)
        || (eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUALI_II)
        || (eAudioModeSet == LX_ATV_SET_PAL_NICAM_MONO_FORCED)
        || (eAudioModeSet == LX_ATV_SET_PAL_NICAM_STEREO_FORCED)
        || (eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUAL_FORCED))
    {
        //Set a PAL NICAM sound output mode
        _AUD_AAD_SetNICAMSoundOutputMode (eAudioModeSet);
    }
    else
    {
        return RET_INVALID_PARAMS;
    }

    return RET_OK;
}

/**
 * Set A2 threshold level function.
*/
int AUD_AAD_A2_SetThresholdLevel (SINT32 level)
{
    AadCmdSetMNIDLevel thLevel = { };

    //Copy A2 Threshold Level by chip revision(This value is decided by experimental result in PT measurement.
    //M17 A0 :      0x168: 0x12, 0x16C: 0x0E
    //Set a A2 threshold level, UI Default 11(0xB), 2016.12.16(0x14/0x0F)
    //Set a A2 threshold level, UI Default 11(0xB), 2017.05.11(0x11/0x0F)
    thLevel.mn_id_threshold_high = 0x06 + level;        //0x07 = 0x12 - 0x0B, 0x09 = 0x14 - 0x0B, 0x06 = 0x11 - 0x0B
    thLevel.mn_id_threshold_low = 0x04 + level; //0x03 = 0x0E - 0x0B, 0x04 = 0x0F - 0x0B, 0x04 = 0x0F - 0x0B
    thLevel.mn_biid_threshold_high = AUD_BI_ID_MAGNITUDE_THRESHOLD_HI;
    thLevel.mn_biid_threshold_low = AUD_BI_ID_MAGNITUDE_THRESHOLD_LO;

    //Set MN ID Threshold command
    aimc_send_command (NULL, AAD_CMD_SET_MN_ID_LEVEL, 0,
        AUD_AAD_GetModuleUID (), &thLevel, sizeof (AadCmdSetMNIDLevel));
    debug ("mn_id_threshold_high = 0x%02X\n", thLevel.mn_id_threshold_high);
    debug ("mn_id_threshold_low  = 0x%02X\n", thLevel.mn_id_threshold_low);

    //Copy A2 Threshold Level
    g_stAudThresholdLevel.stereoIDMagHigh = thLevel.mn_id_threshold_high;
    g_stAudThresholdLevel.stereoIDMagLow = thLevel.mn_id_threshold_low;
    return RET_OK;
}

/**
 * Detect Automatic Sound System function.
*/
int AUD_AAD_DetectAutomaticSoundSystem (LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem)
{
    int eRetVal = RET_OK;

    AadCmdSetBandDetect bandDetect = { };

    UINT8 *debugString[6] = { "BG", "I ", "DK", "L ", "MN", "UNKNOWN" };

    //unsigned int band_detect_en;        // 0 : disable, 1 : enable
    //unsigned int band_4P5;              // 0 : BTSC ,   1 : KOREA, 2 : Other
    //unsigned int band_6P5;              // 0 : SECAM_L, 1 : DK
    bandDetect.band_detect_en = 1;
    bandDetect.band_4P5 = 3;
    bandDetect.band_6P5 = 2;

    //Check a sound system
    switch (eSoundSystem)
    {
        case LX_AAD_SIF_SYSTEM_BG:
        case LX_AAD_SIF_SYSTEM_I:
            break;

        case LX_AAD_SIF_SYSTEM_DK:
            bandDetect.band_6P5 = 1;
            break;

        case LX_AAD_SIF_SYSTEM_L:
            bandDetect.band_6P5 = 0;
            break;

        case LX_AAD_SIF_SYSTEM_MN:

            //Check a M/N audio system
            if (g_eAudAadInitType == LX_AAD_INIT_ATSC_BTSC_SELECT)
                bandDetect.band_4P5 = 0;        //BTSC
            else if (g_eAudAadInitType == LX_AAD_INIT_ATSC_A2_SELECT)
                bandDetect.band_4P5 = 1;        //Korea
            else
                bandDetect.band_4P5 = 2;        //Other
            break;

        case LX_AAD_SIF_SYSTEM_UNKNOWN:
            bandDetect.band_4P5 = 2;    //Other
            bandDetect.band_6P5 = 1;    //DK
            break;

        default:
            eRetVal = RET_INVALID_PARAMS;

            error ("eSoundSystem %d\n", eSoundSystem);
            return eRetVal;

            //May be we can implement after complete all system test
            break;
    }

    //Set Audio Band Detect command
    aimc_send_command (NULL, AAD_CMD_SET_BAND_DETECT, 0,
        AUD_AAD_GetModuleUID (), &bandDetect, sizeof (AadCmdSetBandDetect));
    debug ("band_detect_en = %d\n", bandDetect.band_detect_en);

    //Check a audio aad event.
    eRetVal = _AUD_AAD_CheckSoundSystemDetection ();

    //Sanity check for debug print
    if (eSoundSystem > LX_AAD_SIF_SYSTEM_MN)
        eSoundSystem = LX_AAD_SIF_SYSTEM_MN + 1;

    trace ("eSoundSystem %d(%s)\n", eSoundSystem, debugString[eSoundSystem]);
    return eRetVal;
}

/**
 * Detects a PAL Audio Signal Strength After ASD fails to Scan Audio Signal.
 * @see
*/
int AUD_AAD_DetectSoundSystemCommandWait (LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem)
{
    UINT32 ui32SoundStatus, ui32Car1Good;
    struct AUD_AAD_STATUS aad_status;

    //Disable a Automatic Audio Ouput Mode
    if (eSoundSystem == LX_AAD_SIF_SYSTEM_MN)
    {
        //Check a BTSC audio system
        if (g_eAudAadInitType == LX_AAD_INIT_ATSC_BTSC_SELECT)
        {
            //Set a BTSC sound output mode
            _AUD_AAD_SetBTSCSoundOutputMode (LX_ATV_SET_NTSC_BTSC_UNKNOWN);
        }
        else
        {
            //Set a M/N A2 sound output mode
            _AUD_AAD_SetMNA2SoundOutputMode (LX_ATV_SET_NTSC_A2_UNKNOWN);
        }
    }
    else
    {
        //Set a PAL NICAM sound output mode
        _AUD_AAD_SetNICAMSoundOutputMode (LX_ATV_SET_PAL_UNKNOWN);
    }

    //Set a Audio Sound System
    (void) AUD_AAD_SetSoundSystem (eSoundSystem);

    //Check a each sound system.
    if (eSoundSystem == LX_AAD_SIF_SYSTEM_DK || eSoundSystem == LX_AAD_SIF_SYSTEM_L)
    {
        //Wait to read signal strength
        AUD_AAD_SIF_TIME_DELAY_MS (SIGNAL_QUALITY_DELAY_MANUAL_DK);     //700 ms
    }
    else if (eSoundSystem == LX_AAD_SIF_SYSTEM_BG)
    {
        //Wait to read signal strength
        AUD_AAD_SIF_TIME_DELAY_MS (SIGNAL_QUALITY_DELAY_MANUAL_BG);     //500 ms
    }
    else                        //I, M/N
    {
        //Wait to read signal strength
        AUD_AAD_SIF_TIME_DELAY_MS (SIGNAL_QUALITY_DELAY_MANUAL_I);      //300 ms
    }

    //Read status register
    *(unsigned int *) &aad_status = AUD_IPCREG (AAD_STATUS);
    ui32Car1Good = aad_status.car1_good;
    ui32SoundStatus = aad_status.sound_status;

    //Check a Primary Carrier Status to detect PAL B/G, I, D/K, M/N Signal
    if (ui32Car1Good == 1 || ui32SoundStatus == AUD_AAD_SNR_GOOD)
        info ("System = %d : Pri Car. or NICAM Detected(aud_aad_status = 0x%02X)\n",
            eSoundSystem, *(unsigned int *) &aad_status);
    else                        //Wait to read signal strength
        AUD_AAD_SIF_TIME_DELAY_MS (AUD_SIGNAL_QUALITY_DELAY_300MS);

    return RET_OK;
}

/**
 * Set a manual volume by aad output mode for User Analog and High Devication mode.
 * @see
*/
int AUD_AAD_SetManualVolumeForAdjust (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet)
{
    AadCmdSetSoundLevel soundLevel = { };

    //unsigned int ka2_mono_mul21;           /// default : 0x1BAD00 (= 0.8648681640625 * MUL21(=2^21 = 2,097,152))
    //unsigned int ka2_mul21;                /// default : 0x1BAD00 (= 0.8648681640625 * MUL21(=2^21 = 2,097,152))
    //unsigned int kmna2_mono_mul21;         /// default : 0x18623B (= 0.761991024017333984375 * MUL21(=2^21 = 2,097,152))
    //unsigned int kmna2_mul21;              /// default : 0x1A6E1F (= 0.825942516326904296875 * MUL21(=2^21 = 2,097,152))
    //unsigned int kbtsc_mono_mul21;         /// default : 0x10AA3F (= 0.520781993865966796875 * MUL21(=2^21 = 2,097,152))
    //unsigned int kbtsc_mul21;              /// default : 0x198400 (= 0.79736328125 * MUL21(=2^21 = 2,097,152))
    //unsigned int kbtsc_sap_mul21;          /// default : 0x0E76A5 (= 0.451982975006103515625 * MUL21(=2^21 = 2,097,152))
    //unsigned int knicam_mul21;             /// default : 0x470000 (= 2.21875 * MUL21(=2^21 = 2,097,152))
    //unsigned int kbgfmam_mono_mul21;       /// default : 0x1C4C4B (= 0.884313106536865234375 * MUL21(=2^21 = 2,097,152))
    //unsigned int kifmam_mono_mul21;        /// default : 0x1B0068 (= 0.843799591064453125 * MUL21(=2^21 = 2,097,152))
    //unsigned int kdkfmam_mono_mul21;       /// default : 0x1B3E39 (= 0.851345539093017578125 * MUL21(=2^21 = 2,097,152))
    //unsigned int klfmam_mono_mul21;        /// default : 0x1B3E39 (= 0.851345539093017578125 * MUL21(=2^21 = 2,097,152))

    //Set a default value.
    soundLevel.ka2_mono_mul21 = 0x1BAD00;       //DVB A2 FM Mono
    soundLevel.ka2_mul21 = 0x1BAD00;    //DVB A2 FM Stereo
    soundLevel.kmna2_mono_mul21 = 0x18623B;     //Korea A2, AJJA M/N A2 FM Mono
    soundLevel.kmna2_mul21 = 0x1A6E1F;  //Korea A2, AJJA M/N A2 FM Stereo
    soundLevel.kbtsc_mono_mul21 = 0x10AA3F;     //BTSC Mono
    soundLevel.kbtsc_mul21 = 0x198400;  //BTSC Stereo
    soundLevel.kbtsc_sap_mul21 = 0x0E76A5;      //BTSC SAP
    soundLevel.knicam_mul21 = 0x470000; //NICAM
    soundLevel.kbgfmam_mono_mul21 = 0x1C4C4B;   //B/G FM Mono
    soundLevel.kifmam_mono_mul21 = 0x1B0068;    //I   FM Mono
    soundLevel.kdkfmam_mono_mul21 = 0x1B3E39;   //D/K FM Mono
    soundLevel.klfmam_mono_mul21 = 0x1B3E39;    //L AM Mono

    //Set a a2 level in PAL B/G, D/K, I signal in O22n SoC.
    if (((lx_chip () == LX_CHIP_O22) || (lx_chip () == LX_CHIP_O26))    \
     && (g_eAudAadInitType != LX_AAD_INIT_DVB_IN_SELECT))
    {
        //Sound Ouput Level(suji.baek, 2022.08.30)
        if (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_BG)
        {
            soundLevel.ka2_mono_mul21 = 0x1C1B00;
            soundLevel.kbgfmam_mono_mul21 = 0x1C1B00;
        }
        else if (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_DK)
        {
            soundLevel.ka2_mono_mul21 = 0x1B9800;
            soundLevel.kdkfmam_mono_mul21 = 0x1B9800;
        }
        else if (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_I)
        {
            soundLevel.kifmam_mono_mul21 = 0x1BDC00;
        }

        //Check a NICAM Mode
        if (eAudioModeSet == LX_ATV_SET_PAL_NICAM_MONO
            || eAudioModeSet == LX_ATV_SET_PAL_NICAM_STEREO
            || eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUALI
            || eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUALII
            || eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUALI_II)
        {
            //Sound Ouput Level(suji.baek, 2022.09.01)
            soundLevel.knicam_mul21 = 0x411000; //NICAM, 20220908:0x470000 ->0x411000
        }
    }

    //Set a a2 level in KR M/N A2 signal after M23 SoC(Not O22 SoC).
    if ((lx_chip () != LX_CHIP_O22)
        && (g_eAudAadInitType == LX_AAD_INIT_ATSC_A2_SELECT)
        && (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_MN))
    {
        //Sound Ouput Level(jy0212.lee, 2022.07.13), KMNA2_MUL21:0x199580
        soundLevel.kmna2_mul21 = 0x199580;
    }
    //Set a BTSC level in BTSC signal.
    else if ((g_eAudAadInitType == LX_AAD_INIT_ATSC_BTSC_SELECT)
        && (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_MN))
    {
        //Sound Ouput Level(seoktae.jeon, 2017.09.30), kbtsc_mono_mul21: 0x120000, kbtsc_mul21:0x144000, kbtsc_sap_mul21:0x0B0000
        //Sound Ouput Level(seoktae.jeon, 2017.10.01), kbtsc_mono_mul21: 0x120000, kbtsc_mul21:0x144000, kbtsc_sap_mul21:0x0D0000
        //Sound Ouput Level(seoktae.jeon, 2017.11.08), kbtsc_mono_mul21: 0x110000, kbtsc_mul21:0x178000, kbtsc_sap_mul21:0x0E0000
        soundLevel.kbtsc_mono_mul21 = 0x110000; //BTSC Mono
        soundLevel.kbtsc_mul21 = 0x178000;      //BTSC Stereo
        soundLevel.kbtsc_sap_mul21 = 0x0E0000;  //BTSC SAP
    }

    //Set a a2 level in PAL B/G, D/K, I signal in O22n SoC.
    if ((lx_chip () == LX_CHIP_O22) && (g_eAudAadInitType != LX_AAD_INIT_DVB_IN_SELECT))
    {
        aimc_send_command (NULL, AAD_CMD_SET_SOUND_LEVEL, 0,
            AUD_AAD_GetModuleUID (), &soundLevel, sizeof (AadCmdSetSoundLevel));

        //Sound Ouput Level(suji.baek, 2022.08.30)
        if (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_BG)
        {
            debug ("ka2_mono_mul21 = 0x%08X, kbgfmam_mono_mul21 = 0x%08X\n",
                soundLevel.ka2_mono_mul21, soundLevel.kbgfmam_mono_mul21);
        }
        else if (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_DK)
        {
            debug ("ka2_mono_mul21 = 0x%08X, kdkfmam_mono_mul21 = 0x%08X\n",
                soundLevel.ka2_mono_mul21, soundLevel.kdkfmam_mono_mul21);
        }
        else if (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_I)
        {
            debug ("kifmam_mono_mul21 = 0x%08X\n", soundLevel.kifmam_mono_mul21);
        }
    }

    //Check a audio aad volume change.
    if (soundLevel.kmna2_mul21 != g_ui32AudAadVolume.kmna2_mul21)
    {
        aimc_send_command (NULL, AAD_CMD_SET_SOUND_LEVEL, 0,
            AUD_AAD_GetModuleUID (), &soundLevel, sizeof (AadCmdSetSoundLevel));
        debug ("kmna2_mono_mul21 = 0x%08X, kmna2_mul21 = 0x%08X\n",
            soundLevel.kmna2_mono_mul21, soundLevel.kmna2_mul21);
    }
    else if (soundLevel.kbtsc_mono_mul21 != g_ui32AudAadVolume.kbtsc_mono_mul21)
    {
        aimc_send_command (NULL, AAD_CMD_SET_SOUND_LEVEL, 0,
            AUD_AAD_GetModuleUID (), &soundLevel, sizeof (AadCmdSetSoundLevel));
        debug
            ("kbtsc_mono_mul21 = 0x%08X, kbtsc_mul21 = 0x%08X, kbtsc_sap_mul21 = 0x%08X\n",
            soundLevel.kbtsc_mono_mul21, soundLevel.kbtsc_mul21, soundLevel.kbtsc_sap_mul21);
    }

    return RET_OK;
}

int AUD_AAD_SetDataDrop (bool on_off)
{
    AadCmdDataDrop param = { };

    param.drop = on_off;

    aimc_send_command (NULL, AAD_CMD_DATA_DROP, 0, AUD_AAD_GetModuleUID (), &param, sizeof (param));

    return RET_OK;
}

/******************************************************************************
    Static Function Definitions
******************************************************************************/
/**
 * Set a Audio M/N A2 Sound Ouput Mode function.
*/
static void _AUD_AAD_SetMNA2SoundOutputMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet)
{
    AadCmdSetAutoSoundMode autoSoundMode;
    AadCmdSetA2SoundMode a2SoundMode;

    //  0 ; Auto Sound Mode Off
    //  1 ; Auto Sound Mode On
    //unsigned int auto_sound_mode;

    //Set Auto Sound Mode Off
    autoSoundMode.auto_sound_mode = 0;

    //Set Auto Sound Mode command
    aimc_send_command (NULL, AAD_CMD_SET_AUTO_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &autoSoundMode, sizeof (AadCmdSetAutoSoundMode));
    debug ("auto_sound_mode = %d\n", autoSoundMode.auto_sound_mode);

    //      0 ; Mono
    //      1 ; Stereo
    //      2 ; A(for Bilingual Main)
    //      3 ; B(for Bilingual Sub)
    //      4 ; A+B(for Bilingual Main+Sub/2)
    //unsigned int a2_sound_mode;

    //Check a Mono/Stereo/Bilingual Mode
    if (eAudioModeSet == LX_ATV_SET_NTSC_A2_MONO)
    {
        //Check a Bilingual Mode for A2 mode
        if (g_o_eAudAudioMode == LX_ATV_GET_NTSC_A2_SAP)
            a2SoundMode.a2_sound_mode = 2;      //      2 ; A(for Bilingual Main)
        else
            a2SoundMode.a2_sound_mode = 0;      //      0 ; Mono
    }
    else if (eAudioModeSet == LX_ATV_SET_NTSC_A2_STEREO)
    {
        a2SoundMode.a2_sound_mode = 1;  //      1 ; Stereo
    }
    else
    {
        //Check a Bilingual Mode for A2 mode
        if (eAudioModeSet == LX_ATV_SET_NTSC_A2_SAP)
            a2SoundMode.a2_sound_mode = 3;      //      3 ; B(for Bilingual Sub)
        else                    //Mono
            a2SoundMode.a2_sound_mode = 0;      //      0 ; Mono
    }

    //Set A2 Sound Mode
    aimc_send_command (NULL, AAD_CMD_SET_A2_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &a2SoundMode, sizeof (AadCmdSetA2SoundMode));
    debug ("a2_sound_mode = %d\n", a2SoundMode.a2_sound_mode);

    return;
}

/**
 * Set a Audio A2 Sound Ouput Mode function.
*/
static void _AUD_AAD_SetPALA2SoundOutputMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet)
{
    AadCmdSetAutoSoundMode autoSoundMode;
    AadCmdSetA2SoundMode a2SoundMode;

    //  0 ; Auto Sound Mode Off
    //  1 ; Auto Sound Mode On
    //unsigned int auto_sound_mode;

    //Check a AJJA model for previous model.
    if ((g_eAudAadInitType == LX_AAD_INIT_DVB_AJJA_SELECT)
        || (g_eAudAadInitType == LX_AAD_INIT_DVB_CN_SELECT
            && g_i_eAudSystem == LX_AAD_SIF_SYSTEM_MN))
    {
        //Set Auto Sound Mode Off
        autoSoundMode.auto_sound_mode = 0;
    }
    else if ((eAudioModeSet == LX_ATV_SET_PAL_MONO_FORCED)
        || (eAudioModeSet == LX_ATV_SET_PAL_STEREO_FORCED)
        || (eAudioModeSet == LX_ATV_SET_PAL_UNKNOWN))
    {
        //Set Auto Sound Mode Off
        autoSoundMode.auto_sound_mode = 0;
    }
    else
    {
        //Set Auto Sound Mode Off
        autoSoundMode.auto_sound_mode = 1;
    }

    //Set Auto Sound Mode command
    aimc_send_command (NULL, AAD_CMD_SET_AUTO_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &autoSoundMode, sizeof (AadCmdSetAutoSoundMode));
    debug ("auto_sound_mode = %d\n", autoSoundMode.auto_sound_mode);

    //      0 ; Mono
    //      1 ; Stereo
    //      2 ; A(for Bilingual Main)
    //      3 ; B(for Bilingual Sub)
    //      4 ; A+B(for Bilingual Main+Sub/2)
    //unsigned int a2_sound_mode;

    //Check a Mono/Stereo/Bilingual Mode
    if (eAudioModeSet == LX_ATV_SET_PAL_MONO)
    {
        a2SoundMode.a2_sound_mode = 0;  //      0 ; Mono
    }
    else if (eAudioModeSet == LX_ATV_SET_PAL_STEREO)
    {
        a2SoundMode.a2_sound_mode = 1;  //      1 ; Stereo
    }
    else
    {
        //Check a Bilingual Mode for PAL Dual  mode
        if ((eAudioModeSet == LX_ATV_SET_PAL_DUALI) || (eAudioModeSet == LX_ATV_SET_PAL_DUALII)
            || (eAudioModeSet == LX_ATV_SET_PAL_DUALI_II))
        {
            if (eAudioModeSet == LX_ATV_SET_PAL_DUALI)
                a2SoundMode.a2_sound_mode = 2;  //      2 ; A(for Bilingual Main)
            else if (eAudioModeSet == LX_ATV_SET_PAL_DUALII)
                a2SoundMode.a2_sound_mode = 3;  //      3 ; B(for Bilingual Sub)
            else
                a2SoundMode.a2_sound_mode = 4;  //      4 ; A+B(for Bilingual Main+Sub/2)
        }
        else                    //Mono
        {
            a2SoundMode.a2_sound_mode = 0;      //      0 ; Mono
        }
    }

    //Set A2 Sound Mode
    aimc_send_command (NULL, AAD_CMD_SET_A2_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &a2SoundMode, sizeof (AadCmdSetA2SoundMode));
    debug ("a2_sound_mode = %d\n", a2SoundMode.a2_sound_mode);

    return;
}

/**
 * Set a Audio Sound Ouput Mode function.
*/
static void _AUD_AAD_SetBTSCSoundOutputMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet)
{
    AadCmdSetAutoSoundMode autoSoundMode;
    AadCmdSetBTSCSoundMode btscSoundMode;

    //  0 ; Auto Sound Mode Off
    //  1 ; Auto Sound Mode On
    //unsigned int auto_sound_mode;

    //Set Auto Sound Mode Off
    autoSoundMode.auto_sound_mode = 0;

    //Set Auto Sound Mode command
    aimc_send_command (NULL, AAD_CMD_SET_AUTO_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &autoSoundMode, sizeof (AadCmdSetAutoSoundMode));
    debug ("auto_sound_mode = %d\n", autoSoundMode.auto_sound_mode);

    //  0 ; Mono
    //  1 ; Stereo
    //  2 ; SAP
    //unsigned int btsc_sound_mode;

    if (eAudioModeSet == LX_ATV_SET_NTSC_BTSC_MONO || eAudioModeSet == LX_ATV_SET_NTSC_BTSC_UNKNOWN)
        btscSoundMode.btsc_sound_mode = 0;      //      0 ; Mono
    else if (eAudioModeSet == LX_ATV_SET_NTSC_BTSC_STEREO)
        btscSoundMode.btsc_sound_mode = 1;      //      1 ; Stereo
    else
        btscSoundMode.btsc_sound_mode = 2;      //      2 ; SAP

    //Set BTSC Sound Mode
    aimc_send_command (NULL, AAD_CMD_SET_BTSC_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &btscSoundMode, sizeof (AadCmdSetBTSCSoundMode));
    debug ("btsc_sound_mode = %d\n", btscSoundMode.btsc_sound_mode);

    return;
}

/**
 * Set a Audio Sound Ouput Mode function.
*/
static void _AUD_AAD_SetNICAMSoundOutputMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet)
{
    AadCmdSetAutoSoundMode autoSoundMode;
    AadCmdSetNICAMSoundMode nicamSoundMode;

    //  0 ; Auto Sound Mode Off
    //  1 ; Auto Sound Mode On
    //unsigned int auto_sound_mode;

    //Check a AJJA model for previous model.
    if (g_eAudAadInitType == LX_AAD_INIT_DVB_AJJA_SELECT)
        autoSoundMode.auto_sound_mode = 0;      //Disable
    else if (g_eAudAadInitType == LX_AAD_INIT_DVB_CN_SELECT
        && g_i_eAudSystem == LX_AAD_SIF_SYSTEM_MN)
        autoSoundMode.auto_sound_mode = 0;      //Disable
    else if ((eAudioModeSet == LX_ATV_SET_PAL_NICAM_MONO_FORCED)
        || (eAudioModeSet == LX_ATV_SET_PAL_NICAM_STEREO_FORCED)
        || (eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUAL_FORCED))
        autoSoundMode.auto_sound_mode = 0;      //Disable
    else
        autoSoundMode.auto_sound_mode = 1;      //Enable

    //Set Auto Sound Mode command
    aimc_send_command (NULL, AAD_CMD_SET_AUTO_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &autoSoundMode, sizeof (AadCmdSetAutoSoundMode));
    debug ("auto_sound_mode = %d\n", autoSoundMode.auto_sound_mode);

    //      0 ; AM/FM - Mono
    //      1 ; Nicam - Mono
    //      2 ; Nicam - Stereo
    //      3 ; Nicam - A(for Bilingual Main)
    //      4 ; Nicam - B(for Bilingual Sub)
    //      5 ; Nicam - A+B(for Bilingual Main+Sub/2)
    //unsigned int nicam_sound_mode;

    //Check a Bilingual Mode
    if (eAudioModeSet == LX_ATV_SET_PAL_NICAM_MONO)
        nicamSoundMode.nicam_sound_mode = 1;    //      1 ; Nicam - Mono
    else if (eAudioModeSet == LX_ATV_SET_PAL_NICAM_STEREO)
        nicamSoundMode.nicam_sound_mode = 2;    //      2 ; Nicam - Stereo
    else if (eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUALI)
        nicamSoundMode.nicam_sound_mode = 3;    //      3 ; Nicam - A(for Bilingual Main)
    else if (eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUALII)
        nicamSoundMode.nicam_sound_mode = 4;    //      4 ; Nicam - B(for Bilingual Sub)
    else if (eAudioModeSet == LX_ATV_SET_PAL_NICAM_DUALI_II)
        nicamSoundMode.nicam_sound_mode = 5;    //      5 ; Nicam - A+B(for Bilingual Main+Sub/2)
    else
        nicamSoundMode.nicam_sound_mode = 0;    //      0 ; AM/FM - Mono

    //Set A2 Sound Mode
    aimc_send_command (NULL, AAD_CMD_SET_NICAM_SOUND_MODE, 0,
        AUD_AAD_GetModuleUID (), &nicamSoundMode, sizeof (AadCmdSetNICAMSoundMode));
    debug ("nicam_sound_mode = %d\n", nicamSoundMode.nicam_sound_mode);
    return;
}

/**
 * Checks and Waits a Audio AAD ASD function.
 * @see
*/
static SINT32 _AUD_AAD_CheckSoundSystemDetection (void)
{
    int eRetVal = RET_OK;

    UINT64 start, elapsed;

    AadCmdSetBandDetect bandDetect;

    debug ("Wait %d ms for ASD to complete!!!\n", AUD_ASD_TIMEOUT_DELAY);

    //Get a current mili-second time
    start = jiffies;

    /* Reset AUD_AAD_ASD_Task_waitq_flag value */
    AUD_AAD_ASD_Task_waitq_flag = 0;

    //Wait timeout to do ASD function.
    wait_event_interruptible_timeout (AUD_AAD_ASD_Task_wait, AUD_AAD_ASD_Task_waitq_flag != 0,
        msecs_to_jiffies (AUD_ASD_TIMEOUT_DELAY));

    //Get a elapsed mili-second time
    elapsed = (UINT32) jiffies_to_msecs (jiffies - start);

    //Check Audio AAD ASD status.
    if (AUD_AAD_ASD_Task_waitq_flag == 1)
    {
        eRetVal = RET_OK;
        debug ("ASD is completed in %3d ms.\n", (UINT32) elapsed);
    }
    else
    {
        //unsigned int band_detect_en;            // 0 : disable, 1 : enable
        //unsigned int band_4P5;                          // 0 : BTSC ,   1 : KOREA, 2 : Other
        //unsigned int band_6P5;                          // 0 : SECAM_L, 1 : DK
        bandDetect.band_detect_en = 0;
        bandDetect.band_4P5 = 3;
        bandDetect.band_6P5 = 2;

        //Set Audio Band Detect command
        aimc_send_command (NULL, AAD_CMD_SET_BAND_DETECT, 0,
            AUD_AAD_GetModuleUID (), &bandDetect, sizeof (AadCmdSetBandDetect));
        debug ("band_detect_en = %d\n", bandDetect.band_detect_en);
        debug ("ASD is timeout in %3d ms.\n", (UINT32) elapsed);
    }
    return eRetVal;
}
