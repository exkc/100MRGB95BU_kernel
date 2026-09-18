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
#include <linux/mutex.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include "os_util.h"            //for alloc functions
#include <linux/kthread.h>

#include "aad.h"
#include "debug_util.h"

#include "log.h"

logm_define (aad, log_level_noti);
#define trace(fmt,args...)  logm_trace(aad,fmt,##args)
#define debug(fmt,args...)  logm_debug(aad,fmt,##args)
#define info(fmt,args...)   logm_info(aad,fmt,##args)
#define noti(fmt,args...)   logm_noti(aad,fmt,##args)
#define warn(fmt,args...)   logm_warning(aad,fmt,##args)
#define error(fmt,args...)  logm_error(aad,fmt,##args)


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
//This value is set by Suspend and Resume.
bool g_bAudAadSuspended = false;

//This value is set by Suspend and Resume for Band Setup.
bool g_bAudAadBandSetup = false;

//semaphore for AAD Module
DEFINE_MUTEX (g_AUD_AAD_Sema);

//This value is set by AAD_SIF_InitModule function.
LX_AAD_INIT_TYPE_T g_eAudAadInitType = LX_AAD_INIT_TYPE_NONE;

//This value is set by IOCTL function.
bool g_bAudHighDevOnOff = false;        ///< The Status of High Deviation to setted

//This value is used by AAD_RegInitAfterAADReset function.
LX_AAD_HIGH_DEV_SET_T g_eAudHighDevMode = { false, LX_AAD_HIGH_DEV_LEVEL_OFF };

LX_AAD_SIF_THRESHOLD_T g_stAudThresholdLevel = { AUD_ID_MAGNITUDE_THRESHOLD_HI,
    AUD_ID_MAGNITUDE_THRESHOLD_LO
};

//This value is set by AAD_SIF_SetBandSetup.
LX_AAD_SIF_SOUNDSYSTEM_T g_i_eAudSystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

//This value is set by AAD_SIF_SetModeSetup.
LX_AAD_SIF_STANDARD_T g_i_eAudStandard = LX_AAD_SIF_NUM_SOUND_STD;

//This value is set by AAD_SIF_SetBandSetup.
LX_AAD_SIF_STANDARD_INFO_T g_io_stAudStandardInfo = { LX_AAD_SIF_DETECTING_AVALIBILITY,
    LX_AAD_SIF_DETECTING_AVALIBILITY,
    LX_AAD_SIF_DETECTING_EXSISTANCE
};

//This value is set by AAD_SIF_GetCurAnalogMode.
LX_ATV_AUDIO_MODE_GET_T g_o_eAudAudioMode = LX_ATV_GET_NTSC_BTSC_UNKNOWN;

//This value is set by AAD_SIF_SetUserAnalogMode.
LX_ATV_AUDIO_MODE_SET_T g_i_eAudAudioModeSet = LX_ATV_SET_NTSC_BTSC_UNKNOWN;

//AAD M/N A2 Volume for Audio AAD Module
AadCmdSetSoundLevel g_ui32AudAadVolume = { 0x1BAD00, 0x1BAD00, 0x18623B, 0x1A6E1F, 0x10AA3F,
    0x198400, 0x0E76A5, 0x470000, 0x1C4C4B, 0x1B0068,
    0x1B3E39, 0x1B3E39
};

/* Related to AAD monitor task */
DECLARE_WAIT_QUEUE_HEAD (AUD_AAD_ASD_Task_wait);
int AUD_AAD_ASD_Task_waitq_flag;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * Sets High Deviaton Level Value.
 * These settings do not apply to the single carrier hierarchical modulation modes(EIAJ, BTSC and FM-Radio).
 * @see
*/
int AUD_AAD_SIF_SetHighDeviationMode (LX_AAD_HIGH_DEV_SET_T eHighDevMode)
{
    int eRetVal = RET_OK;

    /* Set a Deviaton Level. */
    eRetVal = AUD_AAD_SetHighDeviationMode (eHighDevMode);

    /* Copy High Deviation On or Off Status and Level */
    g_eAudHighDevMode.bHighDevOnOff = eHighDevMode.bHighDevOnOff;
    g_eAudHighDevMode.highDevLevel = eHighDevMode.highDevLevel;

    debug ("OnOff  = %d, Level = %d\n", eHighDevMode.bHighDevOnOff, eHighDevMode.highDevLevel);
    return RET_OK;
}

/**
 * Sets a SIF Band(B/G, I, DK, L, M).
 * This function sets a SIF sound system.
 * @see
*/
int AUD_AAD_SIF_SetBandSetup (LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem)
{
    int eRetVal = RET_OK;

    mutex_lock (&g_AUD_AAD_Sema);

    //Set A2/BTSC mode
    if (eSoundSystem == LX_AAD_SIF_SYSTEM_MN)
    {
        //Check a BTSC audio system
        if (g_eAudAadInitType == LX_AAD_INIT_ATSC_BTSC_SELECT)
        {
            //Set a BTSC Band Setup
            AUD_AAD_BTSC_SetBandSetup ();
        }
        else
        {
            //Set a A2 Band Setup
            AUD_AAD_A2_SetBandSetup ();
        }
    }
    else
    {
        //Set a PAL Band Setup
        AUD_AAD_PAL_SetBandSetup ();
    }

    //Set a Audio Sound System
    AUD_AAD_SetSoundSystem (eSoundSystem);

    //Copy for global value
    g_i_eAudSystem = eSoundSystem;

    //Reset audio mode in channel is changed.
    g_o_eAudAudioMode = LX_ATV_GET_NTSC_BTSC_UNKNOWN;
    g_io_stAudStandardInfo.detectedStandard = LX_AAD_SIF_NOT_AVAILE;
    g_io_stAudStandardInfo.availability = LX_AAD_SIF_DETECTING_EXSISTANCE;

    //Set a Band Setup is called.
    g_bAudAadBandSetup = true;

    mutex_unlock (&g_AUD_AAD_Sema);

    return eRetVal;
}

/**
 * Sets a SIF sound standard input mode.
 * This function sets a SIF sound standard.
 * @see
*/
int AUD_AAD_SIF_SetModeSetup (LX_AAD_SIF_STANDARD_T eStandard)
{
    int eRetVal = RET_OK;

    LX_AAD_SIF_SOUNDSYSTEM_T eSetSoundSystem;

    //Check a suspend and resume status.(Do not call in HAL code.)
    if (g_bAudAadBandSetup == false)
    {
        //Check a audio aad band set-up.
        if (g_i_eAudSystem != LX_AAD_SIF_SYSTEM_UNKNOWN)
        {
            mutex_lock (&g_AUD_AAD_Sema);

            //Resume sound system after suspend
            AUD_AAD_ResumeBandSetup (g_i_eAudSystem);
            noti ("eStandard = %d, g_i_eAudSystem = %d\n", eStandard, g_i_eAudSystem);

            mutex_unlock (&g_AUD_AAD_Sema);
        }
        else
        {
            //Set Mode using system select register based on the input parameter
            if ((eStandard >= LX_AAD_SIF_BG_NICAM && eStandard <= LX_AAD_SIF_BG_A2))
                eSetSoundSystem = LX_AAD_SIF_SYSTEM_BG;
            else if ((eStandard >= LX_AAD_SIF_I_NICAM && eStandard <= LX_AAD_SIF_I_FM))
                eSetSoundSystem = LX_AAD_SIF_SYSTEM_I;
            else if ((eStandard >= LX_AAD_SIF_DK_NICAM && eStandard <= LX_AAD_SIF_DK3_A2))
                eSetSoundSystem = LX_AAD_SIF_SYSTEM_DK;
            else if ((eStandard >= LX_AAD_SIF_L_NICAM && eStandard <= LX_AAD_SIF_L_AM))
                eSetSoundSystem = LX_AAD_SIF_SYSTEM_L;
            else if (eStandard == LX_AAD_SIF_MN_A2 || eStandard == LX_AAD_SIF_MN_BTSC
                || eStandard == LX_AAD_SIF_MN_EIAJ)
                eSetSoundSystem = LX_AAD_SIF_SYSTEM_MN;
            else
                eSetSoundSystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

            //Check bNeedToSet flag
            if (eSetSoundSystem != LX_AAD_SIF_SYSTEM_UNKNOWN)
            {
                mutex_lock (&g_AUD_AAD_Sema);

                //Set a current sound system and standard.
                AUD_AAD_ResumeBandSetup (eSetSoundSystem);
                noti ("g_i_eAudStandard = %d, eSetSoundSystem = %d\n",
                    g_i_eAudStandard, eSetSoundSystem);

                mutex_unlock (&g_AUD_AAD_Sema);
            }
        }

        //Set a Band Setup is called.
        g_bAudAadBandSetup = true;
    }

    //Copy for global value
    g_i_eAudStandard = eStandard;

    return eRetVal;
}

/**
 * Sets a user analog TV stereo mode.
 * Analog Audio Output Mode is setted to Analog Audio Decoder by User Mode or Analog Audio Task.
 * @see
*/
int AUD_AAD_SIF_SetUserAnalogMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet)
{
    int eRetVal = RET_OK;

    bool bNeedToDebug = false;

    //Set a volume for leveling.
    eRetVal = AUD_AAD_SetManualVolumeForAdjust (eAudioModeSet);
    if (eRetVal != RET_OK)
    {
        error ("AUD_AAD_SetManualVolumeForAdjust is error!!!\n");
        return eRetVal;
    }

    //Set a Audio Sound Ouput Mode.
    eRetVal = AUD_AAD_SetSoundOutputMode (eAudioModeSet);
    if (eRetVal != RET_OK)
    {
        error ("AUD_AAD_SetSoundOutputMode is error!!!\n");
        return eRetVal;
    }

    //Set a debugging print flag.
    if (g_i_eAudAudioModeSet != eAudioModeSet)
        bNeedToDebug = true;

    //Copy for global value to use high deviation setting.
    g_i_eAudAudioModeSet = eAudioModeSet;

    //Print Debug Print
    AUD_AAD_DebugSetAnalogMode (eAudioModeSet, bNeedToDebug);

    trace ("eAudioModeSet = 0x%2X\n", eAudioModeSet);
    return eRetVal;
}

/**
 * Sets a SIF Band(B/G, I, DK, L, M/N) and returns the strength of input signal.
 * Gets also a detected sound system and signal strength level.
 * @see
*/
int AUD_AAD_SIF_GetBandDetect (LX_AAD_SIF_SYSTEM_INFO_T * pstSystemInfo)
{
    int iRetVal = RET_OK;

    UINT8 *debugString[] = { "BG", "I", "DK", "L", "MN", "UNKNOWN" };
    UINT8 ui8SetStrNum = 0, ui8DebugStrNum = 0;
    UINT32 sifSystem;

    LX_AAD_SIF_SOUNDSYSTEM_T eTVSoundSystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

    debug ("GetBandDetect Start!!!\n");

    //Check a detected sound system
    pstSystemInfo->detectedSystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

    //Copy SNR value for Carrier 1 Quality and Magnitude to set default value.
    pstSystemInfo->bandStrength = 0;
    pstSystemInfo->bandMagnitude = 0;

    //Check a ASD or Manual Mode to detect audio sound system.
    if (pstSystemInfo->bManualMode == false)
    {
        //Do Automatic Sound System using both carrier(6.5 and 4.5MHz carrier) and return detected TV system
        iRetVal = AUD_AAD_DetectAutomaticSoundSystem (pstSystemInfo->setSystem);
        if (RET_OK != iRetVal)
            debug ("AUD_AAD_DetectAutomaticSoundSystem Failed!!! \n");
    }
    else if (pstSystemInfo->bManualMode == true
        && pstSystemInfo->setSystem != LX_AAD_SIF_SYSTEM_UNKNOWN)
    {
        //Do Automatic Sound System using both carrier(6.5 and 4.5MHz carrier) and return detected TV system
        iRetVal = AUD_AAD_DetectAutomaticSoundSystem (pstSystemInfo->setSystem);
        if (RET_OK != iRetVal)
            debug ("AUD_AAD_DetectAutomaticSoundSystem Failed!!! \n");
    }
    else
    {
        //Check a SIF Signal to detect sound system using manual mode.
        iRetVal = AUD_AAD_DetectSoundSystemCommandWait (pstSystemInfo->setSystem);
    }

    //Check a detected sound system
    eTVSoundSystem = AUD_AAD_GetSoundSystem (&sifSystem);
    debug ("eTVSystem = %d(sifSystem = 0x%X)\n", eTVSoundSystem, sifSystem);

    //In case of China signal, M/N ASD function is sometimes faild, so do not check error case.
    if (iRetVal == RET_OK)
    {
        //Copy a detected system
        pstSystemInfo->detectedSystem = eTVSoundSystem;

        //Get dectected Signal Strength for PAL Audio System.
        AUD_AAD_GetSignalStrengthAndQuality (pstSystemInfo);
    }

    //Check detected band if same band is detected.
    if (pstSystemInfo->bManualMode == true)
    {
        //Update Variables for ui16Carrier1Quality plus ui16Carrier1Magnitude for Auto Scan Mode.
        //Check a unknown audio band search mode.
        if ((pstSystemInfo->setSystem != pstSystemInfo->detectedSystem)
            || (pstSystemInfo->detectedSystem == LX_AAD_SIF_SYSTEM_UNKNOWN))
        {
            //Set a default value if ASD is failed.
            pstSystemInfo->bandStrength = 0;
        }
    }
#if 0                           //SEETV use a Auto Scan Mode.
    else                        //Auto Scan Mode
    {
        //Update Variables for ui16Carrier1Quality plus ui16Carrier1Magnitude for Auto Scan Mode.
        //Check a unknown audio band search mode.
        if ((pstSystemInfo->setSystem != pstSystemInfo->detectedSystem)
            && (pstSystemInfo->setSystem != LX_AAD_SIF_SYSTEM_UNKNOWN))
        {
            //Set a default value if ASD is failed.
            pstSystemInfo->bandStrength = 0;
        }

        //Check a Carrier Quality Threshold Value for Weak Signal.
        if (pstSystemInfo->bandStrength < AUD_CAR1_QUAL_THD_WEAK_SIGNAL_ID_AUTO)
        {
            //Set a Unknown Audio System to re-tunning manual mode from app.
            pstSystemInfo->detectedSystem = LX_AAD_SIF_SYSTEM_UNKNOWN;
        }
    }
#endif

    //Set set string number
    if (pstSystemInfo->setSystem <= LX_AAD_SIF_SYSTEM_MN)
        ui8SetStrNum = pstSystemInfo->setSystem;
    else
        ui8SetStrNum = LX_AAD_SIF_SYSTEM_MN + 1;

    //Set debug string number
    if (eTVSoundSystem <= LX_AAD_SIF_SYSTEM_MN)
        ui8DebugStrNum = eTVSoundSystem;
    else
        ui8DebugStrNum = LX_AAD_SIF_SYSTEM_MN + 1;

    noti ("set : %d(%s) => det : %d(%s), Qual 0x%04X, Mag 0x%04X\n",
        pstSystemInfo->setSystem, debugString[ui8SetStrNum], eTVSoundSystem,
        debugString[ui8DebugStrNum], pstSystemInfo->bandStrength, pstSystemInfo->bandMagnitude);

    return RET_OK;
}

/**
 * Checks if a SIF standard such as NICAM, A2(DK), FM exists in the input SIF signal.
 * Gets also a detected sound standard and signal existence..
 * @see
*/
int AUD_AAD_SIF_CheckSoundMode (LX_AAD_SIF_STANDARD_INFO_T * pstStandardInfo)
{
    int eRetVal = RET_OK;

    //Checks if a SIF standard such as NICAM, A2(DK), FM exists.
    eRetVal = AUD_AAD_CheckSoundMode (pstStandardInfo);
    if (eRetVal != RET_OK)
    {
        error ("AUD_AAD_CheckSoundMode is error!!!\n");
        return eRetVal;
    }

    //For debugging print
    trace ("%d -> %d\n", pstStandardInfo->setStandard, pstStandardInfo->detectedStandard);

    //For debugging print
    if ((g_io_stAudStandardInfo.detectedStandard != pstStandardInfo->detectedStandard)
        || (g_io_stAudStandardInfo.availability != pstStandardInfo->availability))
    {
        trace ("std : %d -> %d, avail : %d -> %d\n",
            g_io_stAudStandardInfo.detectedStandard, pstStandardInfo->detectedStandard,
            g_io_stAudStandardInfo.availability, pstStandardInfo->availability);
    }

    //Copy for global value
    g_io_stAudStandardInfo.detectedStandard = pstStandardInfo->detectedStandard;
    g_io_stAudStandardInfo.availability = pstStandardInfo->availability;

    return eRetVal;
}

/**
 * Gets the sound standard mode.
 * @see
*/
int AUD_AAD_SIF_GetSoundStandardMode (LX_AAD_SIF_STANDARD_T * pStandardMode)
{
    UINT32 sifSystem;

    //Check a detected sound system
    AUD_AAD_GetSoundSystem (&sifSystem);

    //Check a Audio Mode Result Register
    //case 0x0://FM-Stereo (A2, B/G)
    //case 0x1://FM-Mono/NICAM(B/G)
    //case 0x2://AM-Mono/NICAM(L)
    //case 0x3://FM-Mono/NICAM(I)
    //case 0x4://FM-Stereo (A2, D/K1)
    //case 0x5://FM-Stereo (A2, D/K2)
    //case 0x6://FM-Stereo (A2, D/K3)
    //case 0x7://FM-Mono/NICAM(D/K)
    //case 0x8://A2(M/N)
    //case 0xA://BTSC(M/N)
    switch (sifSystem)
    {
        case 0:
            *pStandardMode = LX_AAD_SIF_BG_A2;
            break;

        case 1:
            *pStandardMode = LX_AAD_SIF_BG_NICAM;
            break;

        case 2:
            *pStandardMode = LX_AAD_SIF_L_AM;
            break;

        case 3:
            *pStandardMode = LX_AAD_SIF_I_FM;
            break;

        case 4:
            *pStandardMode = LX_AAD_SIF_DK1_A2;
            break;

        case 5:
            *pStandardMode = LX_AAD_SIF_DK2_A2;
            break;

        case 6:
            *pStandardMode = LX_AAD_SIF_DK3_A2;
            break;

        case 7:
            *pStandardMode = LX_AAD_SIF_DK_NICAM;
            break;

        case 8:
            *pStandardMode = LX_AAD_SIF_MN_A2;
            break;

        case 10:
            *pStandardMode = LX_AAD_SIF_MN_BTSC;
            break;

        default:
            //Set a default audio standard mode
            if (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_BG)
                *pStandardMode = LX_AAD_SIF_BG_A2;
            else if (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_I)
                *pStandardMode = LX_AAD_SIF_I_FM;
            else if (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_DK)
                *pStandardMode = LX_AAD_SIF_DK1_A2;
            else if (g_i_eAudSystem == LX_AAD_SIF_SYSTEM_L)
                *pStandardMode = LX_AAD_SIF_L_AM;
            else                //LX_AAD_SIF_SYSTEM_MN
            {
                if (g_i_eAudStandard == LX_AAD_SIF_MN_BTSC)
                    *pStandardMode = LX_AAD_SIF_MN_BTSC;
                else
                    *pStandardMode = LX_AAD_SIF_MN_A2;
            }
            break;
    }

    trace ("pStandardMode = %d\n", *pStandardMode);
    return RET_OK;
}

/**
 * Gets the setting value of analog TV stereo mode by user or analog task.
 * Analog Audio Output Mode is returned from User Mode or Analog Audio Task in Analog Audio Decoder.
 * @see
*/
int AUD_AAD_SIF_GetCurAnalogMode (LX_ATV_AUDIO_MODE_GET_T * pAudioMode)
{
    UINT32 sifSystem;

    LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem;
    LX_ATV_AUDIO_MODE_GET_T eAudioMode;

    //Set a default audio mode
    eAudioMode = LX_ATV_GET_NTSC_BTSC_UNKNOWN;

    //Check a detected sound system
    eSoundSystem = AUD_AAD_GetSoundSystem (&sifSystem);

    //Check a Audio Mode Result Register
    //case 0x0://FM-Stereo (A2, B/G)
    //case 0x1://FM-Mono/NICAM(B/G)
    //case 0x2://AM-Mono/NICAM(L)
    //case 0x3://FM-Mono/NICAM(I)
    //case 0x4://FM-Stereo (A2, D/K1)
    //case 0x5://FM-Stereo (A2, D/K2)
    //case 0x6://FM-Stereo (A2, D/K3)
    //case 0x7://FM-Mono/NICAM(D/K)
    //if (sifSystem >= 0x0 && sifSystem <= 0x7)
    if (sifSystem <= 0x7)
    {
        //Get a PAL audio mode.
        eAudioMode = AUD_AAD_PAL_GetAudioMode ();
    }
    //case 0x8://FM-Stereo (A2, M/N)
    else if (sifSystem == 0x8)
    {
        //Get a NTSC A2 audio mode.
        eAudioMode = AUD_AAD_NTSC_A2_GetAudioMode ();
    }
    //case 0xA://FM-Stereo + SAP (BTSC)
    else if (sifSystem == 0xA)
    {
        //Get a NTSC BTSC audio mode.
        eAudioMode = AUD_AAD_NTSC_BTSC_GetAudioMode ();
    }
    else
    {
        debug ("default : LX_ATV_GET_NTSC_BTSC_UNKNOWN\n");
    }

    //Check a audio mode status.
    AUD_AAD_DebugCurAnalogMode (eAudioMode);

    //Copy for return value
    *pAudioMode = eAudioMode;

    //Copy for global value
    g_o_eAudAudioMode = eAudioMode;

    trace ("0x%x(eSoundSystem = %d)\n", eAudioMode, eSoundSystem);
    return RET_OK;
}

/**
 * Checks whether SIF(Sound Intermediate Frequency) carrier exists or not.
 * This function is used for checking the SIF of the current analog signal.
 * @see
*/
int AUD_AAD_SIF_GetSIFSatus (bool * pSIFStatus)
{
    //Get a SIF status.
    AUD_AAD_GetSIFSatus (pSIFStatus);

    trace ("pSIFStatus : %d\n", *pSIFStatus);
    return RET_OK;
}

int AUD_AAD_SIF_SetDataDrop (bool on_off)
{
    return AUD_AAD_SetDataDrop (on_off);
}

int AUD_AAD_SIF_ResumeBandSetup (bool set_audio_mode)
{
    int ret;

    mutex_lock (&g_AUD_AAD_Sema);

    /* Set a Deviaton Level. */
    AUD_AAD_SetHighDeviationMode (g_eAudHighDevMode);

    //Resume a Band Setup
    ret = AUD_AAD_ResumeBandSetup (g_i_eAudSystem);

    if (set_audio_mode == true)
    {
        /* Set a AAD audio output mode by saved value. */
        AUD_AAD_SIF_SetUserAnalogMode (g_i_eAudAudioModeSet);
    }

    mutex_unlock (&g_AUD_AAD_Sema);

    return ret;
}
