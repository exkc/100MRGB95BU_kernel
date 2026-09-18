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

logm_define (aad_info, log_level_noti);
#define trace(fmt,args...)  logm_trace(aad_info,fmt,##args)
#define debug(fmt,args...)  logm_debug(aad_info,fmt,##args)
#define info(fmt,args...)   logm_info(aad_info,fmt,##args)
#define noti(fmt,args...)   logm_noti(aad_info,fmt,##args)
#define warn(fmt,args...)   logm_warning(aad_info,fmt,##args)
#define error(fmt,args...)  logm_error(aad_info,fmt,##args)


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
//static void _AUD_AAD_NTSC_MN_A2_SetAudioMode( UINT32 ui32Carrier2Quality );
static void _AUD_AAD_CheckA2SoundMode (LX_AAD_SIF_STANDARD_INFO_T * pstStandardInfo,
    UINT8 sifSystem, UINT32 ui32SoundStatus);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * Get dectected Sound System.
 * @see AAD_SIF_GetBandDetect
*/
LX_AAD_SIF_SOUNDSYSTEM_T AUD_AAD_GetSoundSystem (UINT32 * pSifSystem)
{
    UINT32 sifSystem;

    LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

    struct AUD_AAD_SYS_INFO aad_sys_info;

    //Check a current sound sysytem is detected.
    *(unsigned *) &aad_sys_info = AUD_IPCREG (AAD_SYS_INFO);
    sifSystem = aad_sys_info.sif_system;

    if (sifSystem == 0 || sifSystem == 1)
        eSoundSystem = LX_AAD_SIF_SYSTEM_BG;
    else if (sifSystem == 2)
        eSoundSystem = LX_AAD_SIF_SYSTEM_L;
    else if (sifSystem == 3)
        eSoundSystem = LX_AAD_SIF_SYSTEM_I;
    else if (sifSystem >= 4 && sifSystem <= 7)
        eSoundSystem = LX_AAD_SIF_SYSTEM_DK;
    else if (sifSystem == 8)
        eSoundSystem = LX_AAD_SIF_SYSTEM_MN;    //A2
    else if (sifSystem == 0xA)
        eSoundSystem = LX_AAD_SIF_SYSTEM_MN;    //BTSC
    else
        eSoundSystem = LX_AAD_SIF_SYSTEM_UNKNOWN;       //FM-Radio

    //Set a audio sound system
    *pSifSystem = sifSystem;

    info ("eSoundSystem = %d(sifSystem = %d)\n", eSoundSystem, sifSystem);

    return eSoundSystem;
}

/**
 * AAD SIF Signal Magnitude and Quality Info.
 * @see AAD_SIF_SIGANL_INFO_T
*/
int AUD_AAD_GetCarrierInformation (AUD_AAD_SIF_CARRIER_INFO_T * pstCarrierInfo)
{
    UINT32 ui32Carrier1Magnitude, ui32Carrier1Quality;
    UINT32 ui32Carrier2Magnitude, ui32Carrier2Quality;

    struct AUD_AAD_C1_MAG_CNR aad_c1_mag_cnr;
    struct AUD_AAD_C2_MAG_CNR aad_c2_mag_cnr;

    //Read Carrier1 Magnitude & CNR register
    *(unsigned int *) &aad_c1_mag_cnr = AUD_IPCREG (AAD_C1_MAG_CNR);
    ui32Carrier1Magnitude = aad_c1_mag_cnr.car1_mag;
    ui32Carrier1Quality = aad_c1_mag_cnr.car1_cnr;

    debug ("Carrier1 Magnitude Current 0x%4X\n", ui32Carrier1Magnitude);
    debug ("Carrier1 Quality Current   0x%4X\n", ui32Carrier1Quality);

    //Read Carrier2 Magnitude & CNR register
    *(unsigned int *) &aad_c2_mag_cnr = AUD_IPCREG (AAD_C2_MAG_CNR);
    ui32Carrier2Magnitude = aad_c2_mag_cnr.car2_mag;
    ui32Carrier2Quality = aad_c2_mag_cnr.car2_cnr;

    debug ("Carrier2 Magnitude Current 0x%4X\n", ui32Carrier2Magnitude);
    debug ("Carrier2 Quality Current   0x%4X\n", ui32Carrier2Quality);

    //Update Variables.
    pstCarrierInfo->ui32Carrier1Magnitude = ui32Carrier1Magnitude;
    pstCarrierInfo->ui32Carrier1Quality = ui32Carrier1Quality;
    pstCarrierInfo->ui32Carrier2Magnitude = ui32Carrier2Magnitude;
    pstCarrierInfo->ui32Carrier2Quality = ui32Carrier2Quality;

    return RET_OK;
}

/**
 * Get dectected Signal Strength for PAL Audio System.
 * @see AAD_SIF_GetBandDetect
*/
int AUD_AAD_GetSignalStrengthAndQuality (LX_AAD_SIF_SYSTEM_INFO_T * pstSystemInfo)
{
    UINT32 ui32Carrier1Quality, ui32Carrier1Magnitude;

    AUD_AAD_SIF_CARRIER_INFO_T carrierInfo;

    //Wait to read signal strength
    AUD_AAD_SIF_TIME_DELAY_MS (AUD_SIGNAL_QUALITY_DELAY_100MS);

    //Get a AAD SIF Signal Magnitude and Quality Info.
    (void) AUD_AAD_GetCarrierInformation (&carrierInfo);

    //Update Variables.
    ui32Carrier1Quality = carrierInfo.ui32Carrier1Quality;
    ui32Carrier1Magnitude = carrierInfo.ui32Carrier1Magnitude;

    //Check a ui32Carrier1Quality value under 0x100 for weak signal.
    if (pstSystemInfo->bManualMode == TRUE
        && ui32Carrier1Quality < AUD_CAR1_QUAL_THD_WEAK_SIGNAL_ID_MAN)
    {
        //Wait to read signal strength
        AUD_AAD_SIF_TIME_DELAY_MS (AUD_SIGNAL_QUALITY_DELAY_300MS);

        //Check a ui32Carrier1Quality value under 0x050 for loss signal.
        if (ui32Carrier1Quality < AUD_CAR1_QUAL_THD_LOSS_SIGNAL_ID_MAN)
        {
            //Wait to read signal strength
            AUD_AAD_SIF_TIME_DELAY_MS (AUD_SIGNAL_QUALITY_DELAY_300MS);
        }

        //Get a AAD SIF Signal Magnitude and Quality Info.
        (void) AUD_AAD_GetCarrierInformation (&carrierInfo);

        //Update Variables.
        ui32Carrier1Quality = carrierInfo.ui32Carrier1Quality;
        ui32Carrier1Magnitude = carrierInfo.ui32Carrier1Magnitude;
    }

    //Update Variables for ui32Carrier1Quality plus ui32Carrier1Magnitude for Manual Scan Mode.
    if (pstSystemInfo->bManualMode == TRUE)
    {
        ui32Carrier1Quality += ui32Carrier1Magnitude;

        warn ("setSystem = %d Qual = 0x%04X(Qual 0x%04X, Mag 0x%04X)\n",
            pstSystemInfo->setSystem, ui32Carrier1Quality,
            carrierInfo.ui32Carrier1Quality, carrierInfo.ui32Carrier1Magnitude);
    }
    else
    {
        warn ("set = %d detect = %d Qual = 0x%04X(Qual 0x%04X, Mag 0x%04X)\n",
            pstSystemInfo->setSystem, pstSystemInfo->detectedSystem, ui32Carrier1Quality,
            carrierInfo.ui32Carrier1Quality, carrierInfo.ui32Carrier1Magnitude);
    }

    //Copy SNR value for Carrier 1 Quality and Magnitude
    pstSystemInfo->bandStrength = ui32Carrier1Quality;
    pstSystemInfo->bandMagnitude = ui32Carrier1Magnitude;

    return RET_OK;
}

/**
 * Checks if a SIF standard such as NICAM, A2(DK), FM exists in the input SIF signal.
 * Gets also a detected sound standard and signal existence..
 * @see
*/
int AUD_AAD_CheckSoundMode (LX_AAD_SIF_STANDARD_INFO_T * pstStandardInfo)
{
    int eRetVal = RET_OK;
    UINT32 sifSystem;
    UINT32 ui32SoundStatus, ui32Stereo, ui32BiSap;

    //NICAM
    UINT32 ui32SoundCar, ui32FrameSync, ui32NicamMode;

    LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem;
    struct AUD_AAD_STATUS aud_aad_status;

    //Set dafault value
    pstStandardInfo->detectedStandard = LX_AAD_SIF_NOT_AVAILE;
    pstStandardInfo->availability = LX_AAD_SIF_ABSENT;

    //Check a Audio Mode Result Register
    //case 0x0://FM-Stereo (A2, B/G)
    //case 0x1://FM-Mono/NICAM(B/G)
    //case 0x2://AM-Mono/NICAM(L)
    //case 0x3://FM-Mono/NICAM(I)
    //case 0x4://FM-Stereo (A2, D/K1)
    //case 0x5://FM-Stereo (A2, D/K2)
    //case 0x6://FM-Stereo (A2, D/K3)
    //case 0x7://FM-Mono/NICAM(D/K)

    //Check a detected sound system
    eSoundSystem = AUD_AAD_GetSoundSystem (&sifSystem);

    //Read status register
    *(unsigned int *) &aud_aad_status = AUD_IPCREG (AAD_STATUS);
    ui32SoundStatus = aud_aad_status.sound_status;
    ui32SoundCar = aud_aad_status.sound_car;
    ui32Stereo = aud_aad_status.stereo;
    ui32BiSap = aud_aad_status.bisap;

    /* Check a Sound Standard to detect sound mode. */
    if (pstStandardInfo->setStandard == LX_AAD_SIF_NICAM)
    {
        /* Check a Sound Standard. */
        if ((sifSystem >= 1 && sifSystem <= 3) || (sifSystem == 7))
        {
            pstStandardInfo->detectedStandard = LX_AAD_SIF_NICAM;

            //Check the availability of SIF carrier(NICAM status needs long time to set value.)
            if (ui32SoundCar == 1)      //NICAM(digital sound) is available.
            {
                struct AUD_AAD_NICAM_INFO aad_nicam_info;

                //Read a NICAM Information
                *(unsigned int *) &aad_nicam_info = AUD_IPCREG (AAD_NICAM_INFO);
                ui32NicamMode = aad_nicam_info.nicam_mode;
                ui32FrameSync = aad_nicam_info.frame_sync_lock;

                if ((ui32FrameSync == 1) && (ui32NicamMode == 0x2))     //Dual Mode
                    pstStandardInfo->availability = LX_AAD_SIF_PRESENT;
                else if ((ui32FrameSync == 1) && (ui32NicamMode == 0x0))        //Stereo Mode
                    pstStandardInfo->availability = LX_AAD_SIF_PRESENT;
                else if ((ui32FrameSync == 1) && (ui32NicamMode == 0x1))        //Mono Mode
                    pstStandardInfo->availability = LX_AAD_SIF_PRESENT;
                else if ((ui32FrameSync == 1) && (ui32NicamMode == 0x3))        //Data Mode
                    pstStandardInfo->availability = LX_AAD_SIF_PRESENT;
            }
        }
    }
    else if ((pstStandardInfo->setStandard == LX_AAD_SIF_A2)
        || (pstStandardInfo->setStandard >= LX_AAD_SIF_A2_DK1
            && pstStandardInfo->setStandard <= LX_AAD_SIF_A2_DK3))
    {
        /* Check a A2 Sound Standard. */
        (void) _AUD_AAD_CheckA2SoundMode (pstStandardInfo, sifSystem, ui32SoundStatus);
    }
    else if (pstStandardInfo->setStandard == LX_AAD_SIF_FM)
    {
        /* Check a Sound Standard. */
        if ((sifSystem == 1) || (sifSystem == 3) || (sifSystem == 7))
        {
            pstStandardInfo->detectedStandard = LX_AAD_SIF_FM;

            //Check the availability of SIF carrier
            if (ui32SoundCar == 1)      //NICAM(digital sound) is available.
                pstStandardInfo->availability = LX_AAD_SIF_ABSENT;
            //Analog Sound Standard(AM/FM) active, No signal case, this value is set.
            else if ((ui32SoundStatus == AUD_AAD_SNR_GOOD) || (ui32Stereo == 1) || (ui32BiSap == 1))
                pstStandardInfo->availability = LX_AAD_SIF_PRESENT;
            else                //Bad reception condition of analogl sound -> PRESENT
                pstStandardInfo->availability = LX_AAD_SIF_PRESENT;
        }
    }
    else
    {
        eRetVal = RET_INVALID_PARAMS;
    }

    //For debugging print
    info ("std : %d, avail : %d\n", pstStandardInfo->detectedStandard,
        pstStandardInfo->availability);

    return eRetVal;
}

/**
 * Get dectected Audio Mode for PAL Audio System.
 * @see AAD_SIF_GetCurAnalogMode
*/
LX_ATV_AUDIO_MODE_GET_T AUD_AAD_PAL_GetAudioMode (void)
{
    //A2
    UINT32 ui32Car1Good, ui32Car2Good;
    UINT32 ui32SoundStatus, ui32Stereo, ui32BiSap;

    //NICAM
    UINT32 ui32SoundCar, ui32FrameSync, ui32NicamMode;

    LX_ATV_AUDIO_MODE_GET_T eAudioMode;
    struct AUD_AAD_STATUS aud_aad_status;

    //Read status register
    *(unsigned int *) &aud_aad_status = AUD_IPCREG (AAD_STATUS);
    ui32Car1Good = aud_aad_status.car1_good;
    ui32Car2Good = aud_aad_status.car2_good;
    ui32SoundStatus = aud_aad_status.sound_status;
    ui32SoundCar = aud_aad_status.sound_car;
    ui32Stereo = aud_aad_status.stereo;
    ui32BiSap = aud_aad_status.bisap;

    //Check a PAL A2 Audio Mode.
    if (ui32SoundCar == 0)
    {
        if (ui32Car1Good == 1 && ui32Car2Good == 1 && ui32Stereo == 1)  //Stereo
            eAudioMode = LX_ATV_GET_PAL_STEREO;
        else if (ui32Car1Good == 1 && ui32Car2Good == 1 && ui32BiSap == 1)      //Bilingual
            eAudioMode = LX_ATV_GET_PAL_DUAL;
        else if (ui32Car1Good == 1 && ui32SoundStatus == AUD_AAD_SNR_GOOD)      //Mono
            eAudioMode = LX_ATV_GET_PAL_MONO;
        else
            eAudioMode = LX_ATV_GET_PAL_UNKNOWN;
    }
    //Check a PAL NICAM Audio Mode.
    else if (ui32SoundCar == 1)
    {
        struct AUD_AAD_NICAM_INFO aad_nicam_info;

        //Read a NICAM Information
        *(unsigned int *) &aad_nicam_info = AUD_IPCREG (AAD_NICAM_INFO);
        ui32NicamMode = aad_nicam_info.nicam_mode;
        ui32FrameSync = aad_nicam_info.frame_sync_lock;

        if ((ui32FrameSync == 1) && (ui32NicamMode == 0x2))     //Dual Mode
            eAudioMode = LX_ATV_GET_PAL_NICAM_DUAL;
        else if ((ui32FrameSync == 1) && (ui32NicamMode == 0x0))        //Stereo Mode
            eAudioMode = LX_ATV_GET_PAL_NICAM_STEREO;
        else if ((ui32FrameSync == 1) && (ui32NicamMode == 0x1))        //Mono Mode
            eAudioMode = LX_ATV_GET_PAL_NICAM_MONO;
        else if ((ui32FrameSync == 1) && (ui32NicamMode == 0x3))        //Data Mode
            eAudioMode = LX_ATV_GET_PAL_NICAM_MONO;
        else                    //default
            eAudioMode = LX_ATV_GET_PAL_MONO;
    }
    else
    {
        eAudioMode = LX_ATV_GET_PAL_UNKNOWN;
    }

    return eAudioMode;
}

/**
 * Get dectected Audio Mode for NTSC A2 Audio System.
 * @see AAD_SIF_GetCurAnalogMode
*/
LX_ATV_AUDIO_MODE_GET_T AUD_AAD_NTSC_A2_GetAudioMode (void)
{
    UINT32 ui32Car1Good, ui32Car2Good, ui32Stereo, ui32BiSap;
    UINT32 ui32SoundStatus;

    LX_ATV_AUDIO_MODE_GET_T eAudioMode;
    struct AUD_AAD_STATUS aud_aad_status;

    //Read status register
    *(unsigned int *) &aud_aad_status = AUD_IPCREG (AAD_STATUS);
    ui32Car1Good = aud_aad_status.car1_good;
    ui32Car2Good = aud_aad_status.car2_good;
    ui32SoundStatus = aud_aad_status.sound_status;
    ui32Stereo = aud_aad_status.stereo;
    ui32BiSap = aud_aad_status.bisap;

    if (ui32Car1Good == 1 && ui32Car2Good == 1 && ui32Stereo == 1)      //Stereo
        eAudioMode = LX_ATV_GET_NTSC_A2_STEREO;
    else if (ui32Car1Good == 1 && ui32Car2Good == 1 && ui32BiSap == 1)  //SAP
        eAudioMode = LX_ATV_GET_NTSC_A2_SAP;
    else if (ui32Car1Good == 1 && ui32SoundStatus == AUD_AAD_SNR_GOOD)  //Mono
        eAudioMode = LX_ATV_GET_NTSC_A2_MONO;
    else
        eAudioMode = LX_ATV_GET_NTSC_A2_UNKNOWN;

    info ("eAudioMode = %d, ui32Stereo = %d, ui32BiSap = %d(status = 0x%2X)\n",
        eAudioMode, ui32Stereo, ui32BiSap, *(unsigned int *) &aud_aad_status);
    return eAudioMode;
}

/**
 * Get dectected Audio Mode for NTSC BTSC Audio System.
 * @see AAD_SIF_GetCurAnalogMode
*/
LX_ATV_AUDIO_MODE_GET_T AUD_AAD_NTSC_BTSC_GetAudioMode (void)
{
    UINT32 ui32Car1Good, ui32Car2Good, ui32Stereo, ui32BiSap;
    UINT32 ui32SoundStatus;

    LX_ATV_AUDIO_MODE_GET_T eAudioMode;
    struct AUD_AAD_STATUS aud_aad_status;

    //Read status register
    *(unsigned int *) &aud_aad_status = AUD_IPCREG (AAD_STATUS);
    ui32Car1Good = aud_aad_status.car1_good;
    ui32Car2Good = aud_aad_status.car2_good;
    ui32SoundStatus = aud_aad_status.sound_status;
    ui32Stereo = aud_aad_status.stereo;
    ui32BiSap = aud_aad_status.bisap;

    /* BTSC */
    if (g_eAudAadInitType == LX_AAD_INIT_ATSC_BTSC_SELECT)      //FM-Stereo + SAP (BTSC)
    {
        if (ui32Car1Good == 1 && ui32BiSap == 1 && ui32Stereo == 1)     //SAP and Stereo
            eAudioMode = LX_ATV_GET_NTSC_BTSC_SAP_STEREO;
        else if (ui32Car1Good == 1 && ui32BiSap == 1)   //SAP and Mono
            eAudioMode = LX_ATV_GET_NTSC_BTSC_SAP_MONO;
        else if (ui32Car1Good == 1 && ui32Stereo == 1)  //Stereo
            eAudioMode = LX_ATV_GET_NTSC_BTSC_STEREO;
        else if (ui32Car1Good == 1 && ui32SoundStatus == AUD_AAD_SNR_GOOD)      //Mono
            eAudioMode = LX_ATV_GET_NTSC_BTSC_MONO;
        else
            eAudioMode = LX_ATV_GET_NTSC_BTSC_UNKNOWN;
    }
    else                        //FM-Stereo (Radio - Europe)
    {
        if (ui32Car1Good == 1 && ui32Car2Good == 1 && ui32Stereo == 1)  //Stereo
            eAudioMode = LX_ATV_GET_PAL_STEREO;
        else if (ui32Car1Good == 1 && ui32Car2Good == 1 && ui32BiSap == 1)      //Dual
            eAudioMode = LX_ATV_GET_PAL_DUAL;
        else if (ui32Car1Good == 1 && ui32SoundStatus == AUD_AAD_SNR_GOOD)      //Mono
            eAudioMode = LX_ATV_GET_PAL_MONO;
        else
            eAudioMode = LX_ATV_GET_PAL_UNKNOWN;
    }

    return eAudioMode;
}

/**
 * Get SIFStatus.
 * @see
*/
int AUD_AAD_GetSIFSatus (bool * pSIFStatus)
{
    UINT32 ui32Car1Good, ui32Car2Good, ui32SoundStatus;

    struct AUD_AAD_STATUS aud_aad_status;

    //Check if any primary or secondary carrier is detected using status register and return as boolean value.
    *(unsigned int *) &aud_aad_status = AUD_IPCREG (AAD_STATUS);
    ui32Car1Good = aud_aad_status.car1_good;
    ui32Car2Good = aud_aad_status.car2_good;
    ui32SoundStatus = aud_aad_status.sound_status;

    //Check primary or secondary carrier status
    if ((ui32Car1Good == 1) || (ui32Car2Good == 1) || (ui32SoundStatus == AUD_AAD_SNR_GOOD))
        *pSIFStatus = true;
    else
        *pSIFStatus = false;

    info ("pSIFStatus = %d(status = 0x%X)\n", *pSIFStatus, *(unsigned int *) &aud_aad_status);

    return RET_OK;
}


/******************************************************************************
	Static 함수 정의 (Static Function Definitions)
******************************************************************************/
/**
 * Check a A2 Audio Sound Mode.
 * @see
*/
static void _AUD_AAD_CheckA2SoundMode (LX_AAD_SIF_STANDARD_INFO_T * pstStandardInfo,
    UINT8 sifSystem, UINT32 ui32SoundStatus)
{
    if (pstStandardInfo->setStandard == LX_AAD_SIF_A2)
    {
        /* Check a Sound Standard. */
        if ((sifSystem == 0) || (sifSystem >= 4 && sifSystem <= 6) || (sifSystem == 8))
        {
            pstStandardInfo->detectedStandard = LX_AAD_SIF_A2;

            //Check the availability of SIF carrier
            if (ui32SoundStatus == AUD_AAD_SNR_GOOD)    //Analog Sound Standard(AM/FM) active
                pstStandardInfo->availability = LX_AAD_SIF_PRESENT;
        }
    }
    else                        //if (pstStandardInfo->setStandard >= LX_AAD_SIF_A2_DK1 && pstStandardInfo->setStandard <= LX_AAD_SIF_A2_DK3)
    {
        /* Check a Sound Standard. */
        if (sifSystem == 4 && ui32SoundStatus == AUD_AAD_SNR_GOOD)
        {
            pstStandardInfo->detectedStandard = LX_AAD_SIF_A2_DK1;
            pstStandardInfo->availability = LX_AAD_SIF_PRESENT;
        }
        else if (sifSystem == 5 && ui32SoundStatus == AUD_AAD_SNR_GOOD)
        {
            pstStandardInfo->detectedStandard = LX_AAD_SIF_A2_DK2;
            pstStandardInfo->availability = LX_AAD_SIF_PRESENT;
        }
        else if (sifSystem == 6 && ui32SoundStatus == AUD_AAD_SNR_GOOD)
        {
            pstStandardInfo->detectedStandard = LX_AAD_SIF_A2_DK3;
            pstStandardInfo->availability = LX_AAD_SIF_PRESENT;
        }
    }

    return;
}
