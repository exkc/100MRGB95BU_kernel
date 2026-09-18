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

logm_define (aad_debug, log_level_noti);
#define trace(fmt,args...)  logm_trace(aad_debug,fmt,##args)
#define debug(fmt,args...)  logm_debug(aad_debug,fmt,##args)
#define info(fmt,args...)   logm_info(aad_debug,fmt,##args)
#define noti(fmt,args...)   logm_noti(aad_debug,fmt,##args)
#define warn(fmt,args...)   logm_warning(aad_debug,fmt,##args)
#define error(fmt,args...)  logm_error(aad_debug,fmt,##args)


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define AUD_AADREG_OFFS(offs)   AUD_IPCREG_OFFS(AUD_IPCOFFS_AAD_AGC1+(offs))

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


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * Check a audio set analog mode status.
 * @see AAD_SIF_GetCurAnalogMode
*/
int AUD_AAD_DebugSetAnalogMode (LX_ATV_AUDIO_MODE_SET_T eAudioModeSet, BOOLEAN bNeedToDebug)
{
    UINT8 *debugStrMoSt[] = { "PAL_MONO", "PAL_MONO_F", "PAL_ST", "PAL_ST_F", "PAL_DUAL_I",
        "PAL_DUAL_II", "PAL_DUAL_I_II", "NICAM_MONO", "NICAM_MONO_F", "NICAM_ST",
        "NICAM_ST_F", "NICAM_DUAL_I", "NICAM_DUAL_II", "NICAM_DUAL_I_II", "NICAM_DUAL_F",
        "PAL_UNKNOWN", "A2_MONO", "A2_STEREO", "A2_SAP", "A2_UNKNOWN",
        "BTSC_MONO", "BTSC_ST", "BTSC_SAP_MONO", "BTSC_SAP_ST", "BTSC_UNKNOWN"
    };

    UINT8 *debugStrInit[] = { "TYPE_NONE", "ATSC_A2", "ATSC_BTSC", "DVB", "DVB_ID",
        "DVB_IN(DIA)", "DVB_CN", "DVB_AJJA", "TYPE_MAX"
    };

    UINT8 *debugStrSys[] = { "SYSTEM_BG", "SYSTEM_I", "SYSTEM_DK", "SYSTEM_L", "SYSTEM_MN",
        "SYSTEM_UNKNOWN"
    };

    static UINT32 ui32AadSetPrintCount = 0;

    //Sanity check for debug print
    if (eAudioModeSet >= LX_ATV_SET_NTSC_BTSC_UNKNOWN)
        eAudioModeSet = LX_ATV_SET_NTSC_BTSC_UNKNOWN;

    //Sanity check for debug print
    if (g_eAudAadInitType > LX_AAD_INIT_TYPE_MAX)
        g_eAudAadInitType = LX_AAD_INIT_TYPE_MAX;

    //Sanity check for debug print
    if (g_i_eAudSystem > LX_AAD_SIF_SYSTEM_MN)
        g_i_eAudSystem = LX_AAD_SIF_SYSTEM_MN + 1;

    //For debugging print
    if (bNeedToDebug == TRUE)
    {
        //Read registers
        unsigned int aud_aad_status = AUD_IPCREG (AAD_STATUS);
        unsigned int aud_aad_out_cont = AUD_IPCREG (AAD_OUT_CONT);

        //Increase Debug Print Count.
        ui32AadSetPrintCount++;

        if (eAudioModeSet == LX_ATV_SET_PAL_MONO || eAudioModeSet == LX_ATV_SET_PAL_UNKNOWN
            || eAudioModeSet == LX_ATV_SET_NTSC_A2_MONO
            || eAudioModeSet == LX_ATV_SET_NTSC_A2_UNKNOWN
            || eAudioModeSet == LX_ATV_SET_NTSC_BTSC_MONO
            || eAudioModeSet == LX_ATV_SET_NTSC_BTSC_UNKNOWN
            || g_i_eAudSystem == LX_AAD_SIF_SYSTEM_L)
        {
            if ((ui32AadSetPrintCount % AAD_DEBUG_MSG_PRINT_TIME_10S) == 0)
            {
                warn ("SET : %10s[output = 0x%2X](status = 0x%2X)(Type = %10s, eSystem = %10s)\n",
                    debugStrMoSt[eAudioModeSet], aud_aad_out_cont, aud_aad_status,
                    debugStrInit[g_eAudAadInitType], debugStrSys[g_i_eAudSystem]);
            }
            else
            {
                debug
                    ("SET : %10s[output = 0x%2X](status = 0x%2X)(Type = %10s, eSystem = %10s)\n",
                    debugStrMoSt[eAudioModeSet], aud_aad_out_cont, aud_aad_status,
                    debugStrInit[g_eAudAadInitType], debugStrSys[g_i_eAudSystem]);
            }
        }
        else
        {
            warn ("SET : %10s[output = 0x%2X](status = 0x%2X)(Type = %10s, eSystem = %10s)\n",
                debugStrMoSt[eAudioModeSet], aud_aad_out_cont, aud_aad_status,
                debugStrInit[g_eAudAadInitType], debugStrSys[g_i_eAudSystem]);
        }
    }

    return RET_OK;
}

/**
 * Check a audio current mode status.
 * @see AAD_SIF_GetCurAnalogMode
*/
int AUD_AAD_DebugCurAnalogMode (LX_ATV_AUDIO_MODE_GET_T eAudioMode)
{
    UINT32 sifSystem;

    UINT8 *debugString[] = { "PAL_MONO", "PAL_STEREO", "PAL_DUAL", "NICAM_MONO", "NICAM_STEREO",
        "NICAM_DUAL", "PAL_UNKNOWN", "ERROR1", "ERROR2", "ERROR3",
        "ERROR4", "ERROR5", "ERROR6", "ERROR7", "ERROR8",
        "ERROR9", "A2_MONO", "A2_STEREO", "A2_SAP", "A2_UNKNOWN",
        "BTSC_MONO", "BTSC_STEREO", "BTSC_SAP_MONO", "BTSC_SAP_STEREO", "BTSC_UNKNOWN"
    };

    static UINT32 ui32AadGetPrintCount = 0;

    //Sanity check for debug print
    if (eAudioMode >= LX_ATV_GET_NTSC_BTSC_UNKNOWN)
        eAudioMode = LX_ATV_GET_NTSC_BTSC_UNKNOWN;

    //For debugging print
    if (g_o_eAudAudioMode != eAudioMode)
    {
        struct AUD_AAD_SYS_INFO aud_aad_sys_info;
        unsigned int aud_aad_status;
        unsigned int aud_aad_out_cont;

        //Check a current sound sysytem is detected.
        *(unsigned int *) &aud_aad_sys_info = AUD_IPCREG (AAD_SYS_INFO);
        sifSystem = aud_aad_sys_info.sif_system;

        //Read carrier & output registers
        aud_aad_status = AUD_IPCREG (AAD_STATUS);
        aud_aad_out_cont = AUD_IPCREG (AAD_OUT_CONT);

        //Increase Debug Print Count.
        ui32AadGetPrintCount++;

        if (eAudioMode == LX_ATV_GET_PAL_MONO || eAudioMode == LX_ATV_GET_PAL_UNKNOWN
            || eAudioMode == LX_ATV_GET_NTSC_A2_MONO || eAudioMode == LX_ATV_GET_NTSC_A2_UNKNOWN
            || eAudioMode == LX_ATV_GET_NTSC_BTSC_MONO || eAudioMode == LX_ATV_GET_NTSC_BTSC_UNKNOWN
            || g_i_eAudSystem == LX_AAD_SIF_SYSTEM_L)
        {
            if ((ui32AadGetPrintCount % AAD_DEBUG_MSG_PRINT_TIME_10S) == 0)
            {
                warn ("GET : 0x%x(%s)(sifSystem = %d, status = 0x%2X, output = 0x%4X)\n",
                    eAudioMode, debugString[eAudioMode], sifSystem, aud_aad_status,
                    aud_aad_out_cont);
            }
            else
            {
                debug ("GET : 0x%x(%s)(sifSystem = %d, status = 0x%2X, output = 0x%4X)\n",
                    eAudioMode, debugString[eAudioMode], sifSystem, aud_aad_status,
                    aud_aad_out_cont);
            }
        }
        else
        {
            warn ("GET : 0x%x(%s)(sifSystem = %d, status = 0x%2X, output = 0x%4X)\n",
                eAudioMode, debugString[eAudioMode], sifSystem, aud_aad_status, aud_aad_out_cont);
        }
    }

    return RET_OK;
}

/**
 * Check a audio carrier and status detection.
 * @see
*/
int AUD_AAD_DebugCarrierDetection (void)
{
    UINT32 ui32Car1Good, ui32Car2Good, ui32SoundStatus, ui32SoundCar;
    UINT32 ui32Stereo, ui32Nicam, ui32BiSap, ui32BandDetect;

    //NICAM
    UINT32 ui32FrameFlag, ui32NicamMode, ui32ADSame, ui32FrameSync, ui32SyncSearch;
    struct AUD_AAD_STATUS aud_aad_status;

    //Read status register
    *(unsigned int *) &aud_aad_status = AUD_IPCREG (AAD_STATUS);
    ui32Car1Good = aud_aad_status.car1_good;
    ui32Car2Good = aud_aad_status.car2_good;
    ui32SoundStatus = aud_aad_status.sound_status;
    ui32SoundCar = aud_aad_status.sound_car;
    ui32Stereo = aud_aad_status.stereo;
    ui32Nicam = aud_aad_status.nicam;
    ui32BiSap = aud_aad_status.bisap;
    ui32BandDetect = aud_aad_status.band_detect_enable;

    if ((ui32Car1Good == 1) && (ui32Car2Good == 1))
        debug ("Primary & Secondary Carrier Detected\n");
    else if (ui32Car1Good == 1)
        debug ("Primary Carrier Detected\n");
    else if (ui32Car2Good == 1)
        debug ("Secondary Carrier Detected\n");

    if (ui32SoundStatus == AUD_AAD_SNR_GOOD)
        debug ("Sound Good\n");
    else
        debug ("Sound Bad\n");

    if (ui32SoundCar == 1)
        debug ("Sound Digital(NICAM)\n");
    else
        debug ("Sound Analog\n");

    if (ui32Stereo == 1)
        debug ("Stereo Detected\n");

    if (ui32Nicam == 1)
        debug ("NICAM Detected\n");

    if (ui32BiSap == 1)
        debug ("BI-SAP Detected\n");

    if (ui32BandDetect == 1)
        debug ("Band Detected\n");
    else
        debug ("Band Not Detected\n");

    //Checka Sound Carrier : NICAM
    if (ui32SoundCar == 1)
    {
        struct AUD_AAD_NICAM_INFO aad_nicam_info;

        //Read a NICAM Information
        *(unsigned int *) &aad_nicam_info = AUD_IPCREG (AAD_NICAM_INFO);
        ui32FrameFlag = aad_nicam_info.frame_flag;
        ui32NicamMode = aad_nicam_info.nicam_mode;
        ui32ADSame = aad_nicam_info.ad_same;
        ui32FrameSync = aad_nicam_info.frame_sync_lock;
        ui32SyncSearch = aad_nicam_info.sync_searchng;

        debug ("NICAM Frame Flag = %d\n", ui32FrameFlag);

        if (ui32NicamMode == 0)
            debug ("NICAM : Stereo Channel\n");
        else if (ui32NicamMode == 1)
            debug ("NICAM : One Mono and One Data Channel\n");
        else if (ui32NicamMode == 2)
            debug ("NICAM : Bilingual Channel\n");
        else
            debug ("NICAM : Single Data Channel\n");

        if (ui32ADSame == 1)
            debug ("Analog and Digital : Same Contents\n");

        debug ("NICAM Frame Sync Lock = %d\n", ui32FrameSync);
        debug ("NICAM Sync Searching  = %d\n", ui32SyncSearch);
    }

    return RET_OK;
}

/**
 * Check a audio carrier thsreshold level.
 * @see
*/
int AUD_AAD_DebugThresholdLevel (void)
{
    UINT32 ui32PilotMag, ui32IDBiMag, ui32IDStMag;
    struct AUD_AAD_PLL_INFO aad_pll_info;

    //Read carrier threshold register
    *(unsigned *) &aad_pll_info = AUD_IPCREG (AAD_PLL_INFO);
    ui32PilotMag = aad_pll_info.pilot_mag;
    ui32IDBiMag = aad_pll_info.id_bi_mag;
    ui32IDStMag = aad_pll_info.id_st_mag;

    debug ("Pilot  ID Mag. Current	  0x%4X\n", ui32PilotMag);
    debug ("Biling ID Mag. Current	  0x%4X\n", ui32IDBiMag);
    debug ("Stereo ID Mag. Current	  0x%4X\n", ui32IDStMag);

    //Print global variables
    debug ("stereoIDMagHigh	   = 0x%4X, Low = 0x%4X\n",
        g_stAudThresholdLevel.stereoIDMagHigh, g_stAudThresholdLevel.stereoIDMagLow);

    return RET_OK;
}
