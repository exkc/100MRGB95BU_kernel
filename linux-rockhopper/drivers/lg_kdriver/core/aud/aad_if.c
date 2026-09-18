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
#include <linux/mutex.h>

#include "module/adec_module_list.h"
#include "aad_if.h"
#include "aad/aad.h"

#include "log.h"

logm_define (aad_if, log_level_noti);
#define trace(fmt,args...)  logm_trace(aad_if,fmt,##args)
#define debug(fmt,args...)  logm_debug(aad_if,fmt,##args)
#define info(fmt,args...)   logm_info(aad_if,fmt,##args)
#define noti(fmt,args...)   logm_noti(aad_if,fmt,##args)
#define warn(fmt,args...)   logm_warning(aad_if,fmt,##args)
#define error(fmt,args...)  logm_error(aad_if,fmt,##args)


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
static DEFINE_MUTEX (_aud_aad_lock);


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define AUD_AAD_LOCK()      mutex_lock(&_aud_aad_lock)
#define AUD_AAD_UNLOCK()    mutex_unlock(&_aud_aad_lock)


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

//This value is set by IOCTL function.
extern bool g_bAudHighDevOnOff; ///< The Status of High Deviation to setted

//This value is set by Suspend and Resume for Band Setup.
extern bool g_bAudAadBandSetup;


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct aud_aad_info aad_info;

bool aud_disable_aad = true;
module_param (aud_disable_aad, bool, 0644);


/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * Register Event for Notification.
 * @param   aad_info        [in] audio aad information.
 * @return 	if succeeded - RET_OK, else - -EFAULT.
 * @see     .
 */
static int AUDIO_RegisterEventAad (struct aud_aad_info *aad_info)
{
    if (aad_info->event_id > 0)
    {
        aimc_unregister_named_event (aad_info->event_id);
        noti ("aad event is unregistered.(%d)\n", aad_info->event_id);
    }

    //Register a audio aad event
    aad_info->event_id = aimc_register_named_event (aad_info,
        AUD_AAD_DetectSoundSystemCb, aad_info->uid, "aad_band_search", false);
    if (aad_info->event_id <= 0)
    {
        error ("fail to register evnet %d\n", aad_info->event_id);
        return RET_ERROR;
    }

    noti ("aad event is registered.(%d)\n", aad_info->event_id);
    return RET_OK;
}

/**
 * Init Analog Audio Decoder.
 *
 * @param 	allocDev		[in] a allocated aad device.
 * @return 	if succeeded - RET_OK, else - -EFAULT.
 * @see		.
 */
static SINT32 AUDIO_InitAad (struct aud_aad_info *aad_info)
{
    UINT32 paramSize = 0;
    void *param = NULL;

    AUD_AAD_LOCK ();

    //Init analog audio decoder
    aimc_send_command (NULL, ADEC_CMD_INIT, 0, AUD_AAD_GetModuleUID (), param, paramSize);

    AUD_AAD_UNLOCK ();

    trace ("Init Audio AAD device\n");
    return RET_OK;
}

/**
 * Start Analog Audio Decoder.
 *
 * @param 	allocDev		[in] a allocated device.
 * @return 	if succeeded - RET_OK, else - -EFAULT.
 * @see		.
 */
static SINT32 AUDIO_StartAad (struct aud_aad_info *aad_info)
{
    UINT32 paramSize = 0;
    void *param = NULL;

    AUD_AAD_LOCK ();

    //Start analog audio decoder
    aimc_send_command (NULL, ADEC_CMD_START, 0, AUD_AAD_GetModuleUID (), param, paramSize);

    AUD_AAD_UNLOCK ();

    trace ("Start Audio AAD device\n");
    return RET_OK;
}

/**
 * Stop Analog Audio Decoder.
 *
 * @param 	allocDev		[in] a allocated device.
 * @return 	if succeeded - RET_OK, else - -EFAULT.
 * @see		.
 */
static SINT32 AUDIO_StopAad (struct aud_aad_info *aad_info)
{
    UINT32 paramSize = 0;
    void *param = NULL;

    AUD_AAD_LOCK ();

    // Stop analog audio decoder
    aimc_send_command (NULL, ADEC_CMD_STOP, 0, AUD_AAD_GetModuleUID (), param, paramSize);

    AUD_AAD_UNLOCK ();

    trace ("Stop Audio AAD device\n");
    return RET_OK;
}

/**
 * Flush Analog Audio Decoder.
 *
 * @param 	allocDev		[in] a allocated device.
 * @return 	if succeeded - RET_OK, else - -EFAULT.
 * @see		.
 */
static SINT32 AUDIO_FlushAad (struct aud_aad_info *aad_info)
{
    UINT32 paramSize = 0;
    void *param = NULL;

    AUD_AAD_LOCK ();

    // Flush analog audio decoder
    aimc_send_command (NULL, ADEC_CMD_FLUSH, 0, AUD_AAD_GetModuleUID (), param, paramSize);

    AUD_AAD_UNLOCK ();

    trace ("Flush Audio AAD device\n");
    return RET_OK;
}

/**
 * Close Analog Audio Decoder.
 *
 * @param 	allocDev		[in] a allocated device information.
 * @return 	if succeeded - RET_OK, else - -EFAULT.
 * @see		.
 */
static SINT32 AUDIO_CloseAad (struct aud_aad_info *aad_info)
{
    AUD_AAD_LOCK ();

    if (aad_info->input_info != NULL)
    {
        bm_destroy_block (aad_info->input_info);
        aad_info->input_info = NULL;

        if (aad_info->event_id > 0)
        {
            aimc_unregister_named_event (aad_info->event_id);
            noti ("aad event is unregistered.(%d)\n", aad_info->event_id);
        }
    }

    AUD_AAD_UNLOCK ();

    trace ("Close Device.\n");
    return RET_OK;
}

/**
 * Open Analog Audio Decoder.
 *
 * @param   void   [in]    None.
 * @return  a allocated device information.
 * @see     KDRV_AUDIO_IoctlAad().
 */
static SINT32 AUDIO_OpenAad (struct aud_aad_info *aad_info)
{
    AUD_AAD_LOCK ();

    if (aad_info->input_info)
    {
        error ("input (%p) already exist!!\n", aad_info->input_info);
        bm_destroy_block (aad_info->input_info);
    }

    aad_info->input_info = bm_create_block ("input", INPUT_SIF_INDEX);
    if (aad_info->input_info == NULL)
    {
        error ("error in create input block\n");
        return -1;
    }

    input_set_type (aad_info->input_info, 0, INPUT_SIF, 0, false);
    aad_info->uid = input_get_uid (aad_info->input_info);

    AUD_AAD_UNLOCK ();

    noti ("Open Audio AAD device\n");
    return RET_OK;
}

SINT32 AUDIO_SuspendAad (void)
{
    //Stop & Flush Audio AAD Module.
    (void) AUDIO_StopAad (&aad_info);
    (void) AUDIO_FlushAad (&aad_info);

    noti ("Suspend Device.\n");
    return RET_OK;
}

SINT32 AUDIO_ResumeAad (bool set_is_drop)
{
    AUD_AAD_LOCK ();

    input_set_type (aad_info.input_info, 0, INPUT_SIF, 0, false);
    aad_info.uid = input_get_uid (aad_info.input_info);

    aimc_set_property (aad_info.uid, "drop-output-data=%d", set_is_drop);
    aimc_set_property (aad_info.uid, "drop=%d", set_is_drop);

    AUD_AAD_UNLOCK ();

    //Init Audio AAD Device
    AUDIO_InitAad (&aad_info);

    aad_info.is_resumed = true;

    noti ("Resume Device.\n");
    return RET_OK;
}

SINT32 AUDIO_RestartAad (bool set_audio_mode)
{
    //Check a resume status.
    if (aad_info.is_resumed == true)
    {
        //Re-Start Audio AAD Module.
        AUDIO_StopAad (&aad_info);
        AUDIO_FlushAad (&aad_info);

        AUDIO_InitAad (&aad_info);
        AUDIO_StartAad (&aad_info);

        //Set a Band Setup
        AUD_AAD_SIF_ResumeBandSetup (set_audio_mode);

        aad_info.is_resumed = false;

        noti ("Restart Aad Module.\n");
    }
    else
        (void) AUDIO_StartAad (&aad_info);

    return RET_OK;
}

int AUD_AAD_GetModuleUID (void)
{
    return aad_info.uid;
}

/**
 * set a hdev level for audio sif(aad) device
 *
 */
static SINT32 kcontrol_hdevlevel (SIF_DEVICE_T * sif_dev, SINT32 hdevlevel)
{
    SINT32 retVal = 0;

    LX_AAD_HIGH_DEV_SET_T eHighDevMode = { false, LX_AAD_HIGH_DEV_LEVEL_OFF };

    /* Change High Deviation Level Value */
    eHighDevMode.bHighDevOnOff = hdevlevel;

    if (hdevlevel)
    {
        /* To eliminate audio noise in sweep test, default value is changed from 50Khz and to 100 Khz. */
        if (sif_dev->countryext & LX_AAD_KOREA_A2_SELECT)
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_2;        //200Khz
        else if (sif_dev->countryext & LX_AAD_DVB_AJJA_SELECT)
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_4;        //540Khz, 2012.03.28
        else if (sif_dev->countryext & LX_AAD_DVB_IN_SELECT)
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_4;        //540Khz, 2014.03.26
        else if (sif_dev->countryext & LX_AAD_DVB_SELECT
            || sif_dev->countryext & LX_AAD_DVB_CN_SELECT)
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_3;        //384Khz
        else if (sif_dev->countryext & LX_AAD_DVB_ID_SELECT)
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_3;        //384Khz, 2014.04.03
        else
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_2;        //200Khz, 2018.12.14
    }
    else
    {
        if (sif_dev->countryext & LX_AAD_KOREA_A2_SELECT)
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_1;        //100Khz
        else if (sif_dev->countryext & LX_AAD_DVB_AJJA_SELECT)
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_1;        //100kHz
        else if (sif_dev->countryext & LX_AAD_DVB_IN_SELECT)
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_1;        //100Khz, 2018.12.14
        else if (sif_dev->countryext & LX_AAD_DVB_SELECT
            || sif_dev->countryext & LX_AAD_DVB_CN_SELECT)
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_1;        //100Khz
        else if (sif_dev->countryext & LX_AAD_DVB_ID_SELECT)
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_1;        //100Khz, 2018.12.14
        else
            eHighDevMode.highDevLevel = LX_AAD_HIGH_DEV_LEVEL_1;        //100Khz, 2018.12.14
    }

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
        retVal = AUD_AAD_SIF_SetHighDeviationMode (eHighDevMode);

    return retVal;
}

/**
 * set a a2 threshold level for audio sif(aad) device
 *
 */
static SINT32 kcontrol_a2thresholdlevel (SIF_DEVICE_T * sif_dev, SINT32 a2thdlevel)
{
    SINT32 retVal = 0;

    if (sif_dev->countryext & LX_AAD_KOREA_A2_SELECT
        || sif_dev->countryext & LX_AAD_DVB_AJJA_SELECT)
    {
        //Set a minimum value to 11 from UI memu.
        if (a2thdlevel <= 11)
            a2thdlevel = 11;
        if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
            retVal = AUD_AAD_A2_SetThresholdLevel (a2thdlevel);
    }

    return retVal;
}


/**
 * open handler for audio sif(aad) device
 *
 */
SIF_DEVICE_T *kcontrol_sif_open (void)
{
    SINT32 retVal = RET_OK;

    SIF_DEVICE_T *sif_dev = NULL;
    struct aud_aad_info *aad = NULL;

    sif_dev = kcalloc (1, sizeof (SIF_DEVICE_T), GFP_KERNEL);
    if (!sif_dev)
    {
        error ("no mem\n");
        return NULL;
    }

    aad = &aad_info;

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
    {
        //Open Audio AAD Device
        retVal = AUDIO_OpenAad (aad);
        if (retVal < 0)
        {
            error ("AAD is not available!!!\n");
            kfree (sif_dev);
            return NULL;
        }

        //Init Audio AAD Device
        AUDIO_InitAad (&aad_info);
    }

    //Set a system default value.
    sif_dev->hdevlevel = 0;
    sif_dev->a2thdlevel = 0;
    sif_dev->countryext = LX_AAD_TYPE_NONE;
    sif_dev->soundsystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

    trace ("Open Audio SIF device\n");
    return sif_dev;
}

/**
 * close handler for audio sif device
 *
 */
SINT32 kcontrol_sif_close (SIF_DEVICE_T * sif_dev)
{
    SINT32 retVal = 0;

    if (sif_dev == NULL)
    {
        error ("sif_dev is NULL\n");
        return -EFAULT;
    }

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
    {
        retVal = AUDIO_StopAad (&aad_info);
        if (retVal != RET_OK)
            trace ("AUDIO_StopAad() failed.\n");

        retVal = AUDIO_FlushAad (&aad_info);
        if (retVal != RET_OK)
            trace ("AUDIO_FlushAad() failed.\n");

        retVal = AUDIO_CloseAad (&aad_info);
        if (retVal != RET_OK)
            trace ("AUDIO_CloseAad() failed or already closed.\n");
    }

    kfree (sif_dev);

    trace ("Close Audio AAD device\n");
    return retVal;
}

/**
 * detect sound system for audio sif device
 *
 */
SINT32 kcontrol_sif_detectsoundsystem (SIF_DEVICE_T * sif_dev)
{
    SINT32 retVal = 0;

    LX_AAD_SIF_SYSTEM_INFO_T io_stSystemInfo = { };

    if (sif_dev == NULL)
    {
        error ("sif_dev is NULL\n");
        return -EFAULT;
    }

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
    {
        //Re-Start Audio AAD Module.
        (void) AUDIO_StopAad (&aad_info);
        (void) AUDIO_FlushAad (&aad_info);

        (void) AUDIO_InitAad (&aad_info);
        (void) AUDIO_StartAad (&aad_info);

        /* Set sound system value */
        io_stSystemInfo.setSystem = sif_dev->detectsoundsystem;
        io_stSystemInfo.bManualMode = false;

        //Register a audio aad event.
        AUDIO_RegisterEventAad (&aad_info);

        retVal = AUD_AAD_SIF_GetBandDetect (&io_stSystemInfo);
    }

    if (retVal == RET_OK)
        sif_dev->detectedsoundsystem = io_stSystemInfo.detectedSystem;
    else
        sif_dev->detectedsoundsystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

    sif_dev->band_strength = io_stSystemInfo.bandStrength;

    trace ("kcontrol_sif_detectsoundsystem\n");
    return retVal;
}

/**
 * set sound system for audio sif device
 *
 */
SINT32 kcontrol_sif_bandsetup (SIF_DEVICE_T * sif_dev)
{
    SINT32 retVal = 0;

    if (sif_dev == NULL)
    {
        error ("sif_dev is NULL\n");
        return -EFAULT;
    }

    if (sif_dev->countryext & SIF_AAD_ATSC_A2_ALL_MASK)
        g_eAudAadInitType = LX_AAD_INIT_ATSC_A2_SELECT;
    else if (sif_dev->countryext & SIF_AAD_BTSC_ALL_MASK)
        g_eAudAadInitType = LX_AAD_INIT_ATSC_BTSC_SELECT;
    else if (sif_dev->countryext == LX_AAD_DVB_ID_SELECT)
        g_eAudAadInitType = LX_AAD_INIT_DVB_ID_SELECT;
    else if (sif_dev->countryext == LX_AAD_DVB_IN_SELECT)
        g_eAudAadInitType = LX_AAD_INIT_DVB_IN_SELECT;
    else if (sif_dev->countryext == LX_AAD_DVB_CN_SELECT)
        g_eAudAadInitType = LX_AAD_INIT_DVB_CN_SELECT;
    else if (sif_dev->countryext == LX_AAD_DVB_AJJA_SELECT)
        g_eAudAadInitType = LX_AAD_INIT_DVB_AJJA_SELECT;
    else
        g_eAudAadInitType = LX_AAD_INIT_DVB_SELECT;

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
    {
        //Re-Start Audio AAD Module.
        (void) AUDIO_StopAad (&aad_info);
        (void) AUDIO_FlushAad (&aad_info);

        (void) AUDIO_InitAad (&aad_info);
        (void) AUDIO_StartAad (&aad_info);

        //Set a High Deviation Level.
        (void) kcontrol_hdevlevel (sif_dev, sif_dev->hdevlevel);

        //Set a A2 Threshold Level
        if (sif_dev->a2thdlevel == 0)
            sif_dev->a2thdlevel = 11;
        (void) kcontrol_a2thresholdlevel (sif_dev, sif_dev->a2thdlevel);

        //Set a Band Setup
        retVal = AUD_AAD_SIF_SetBandSetup (sif_dev->soundsystem);
    }

    noti ("soundsystem = %d\n", sif_dev->soundsystem);
    return retVal;
}

/**
 * set sound standard for audio sif device
 *
 */
SINT32 kcontrol_sif_standardsetup (SIF_DEVICE_T * sif_dev)
{
    SINT32 retVal = 0;

    LX_AAD_SIF_SOUNDSYSTEM_T eSetSoundSystem;

    if (sif_dev == NULL)
    {
        error ("sif_dev is NULL\n");
        return -EFAULT;
    }

    //Set Mode using system select register based on the input parameter
    if ((sif_dev->setsoundstandard >= LX_AAD_SIF_BG_NICAM
            && sif_dev->setsoundstandard <= LX_AAD_SIF_BG_A2))
        eSetSoundSystem = LX_AAD_SIF_SYSTEM_BG;
    else if ((sif_dev->setsoundstandard >= LX_AAD_SIF_I_NICAM
            && sif_dev->setsoundstandard <= LX_AAD_SIF_I_FM))
        eSetSoundSystem = LX_AAD_SIF_SYSTEM_I;
    else if ((sif_dev->setsoundstandard >= LX_AAD_SIF_DK_NICAM
            && sif_dev->setsoundstandard <= LX_AAD_SIF_DK3_A2))
        eSetSoundSystem = LX_AAD_SIF_SYSTEM_DK;
    else if ((sif_dev->setsoundstandard >= LX_AAD_SIF_L_NICAM
            && sif_dev->setsoundstandard <= LX_AAD_SIF_L_AM))
        eSetSoundSystem = LX_AAD_SIF_SYSTEM_L;
    else if (sif_dev->setsoundstandard == LX_AAD_SIF_MN_A2
        || sif_dev->setsoundstandard == LX_AAD_SIF_MN_BTSC
        || sif_dev->setsoundstandard == LX_AAD_SIF_MN_EIAJ)
        eSetSoundSystem = LX_AAD_SIF_SYSTEM_MN;
    else
        eSetSoundSystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
    {
        //Check a audio sound system and standard.
        if (eSetSoundSystem != g_i_eAudSystem)
        {
            //Re-Start Audio AAD Module.
            (void) AUDIO_StopAad (&aad_info);
            (void) AUDIO_FlushAad (&aad_info);

            (void) AUDIO_InitAad (&aad_info);
            (void) AUDIO_StartAad (&aad_info);

            //Sets a SIF Band(B/G, I, DK, L, M).
            (void) AUD_AAD_SIF_SetBandSetup (eSetSoundSystem);
        }

        retVal = AUD_AAD_SIF_SetModeSetup (sif_dev->setsoundstandard);
    }

    trace ("kcontrol_sif_standardsetup\n");
    return retVal;
}

/**
 * get sound standard for audio sif device
 *
 */
SINT32 kcontrol_sif_getsoundstandard (SIF_DEVICE_T * sif_dev)
{
    SINT32 retVal = 0;

    LX_AAD_SIF_STANDARD_T standardMode = LX_AAD_SIF_BG_A2;

    if (sif_dev == NULL)
    {
        error ("sif_dev is NULL\n");
        return -EFAULT;
    }

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
        retVal = AUD_AAD_SIF_GetSoundStandardMode (&standardMode);
    sif_dev->getsoundstandard = standardMode;

    trace ("kcontrol_sif_getsoundstandard\n");
    return retVal;
}

/**
 * get current analog mode for audio sif device
 *
 */
SINT32 kcontrol_sif_curanalogmode (SIF_DEVICE_T * sif_dev)
{
    SINT32 retVal = 0;

    LX_ATV_AUDIO_MODE_GET_T eAudioMode = LX_ATV_GET_PAL_MONO;

    if (sif_dev == NULL)
    {
        error ("sif_dev is NULL\n");
        return -EFAULT;
    }

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
        retVal = AUD_AAD_SIF_GetCurAnalogMode (&eAudioMode);
    sif_dev->getaudiomode = eAudioMode;

    trace ("kcontrol_sif_curanalogmode\n");
    return retVal;
}

/**
 * set user analog mode for audio sif device
 *
 */
SINT32 kcontrol_sif_useranalogmode (SIF_DEVICE_T * sif_dev)
{
    SINT32 retVal = 0;

    LX_ATV_AUDIO_MODE_SET_T i_eAudioModeSet;

    if (sif_dev == NULL)
    {
        error ("sif_dev is NULL\n");
        return -EFAULT;
    }

    i_eAudioModeSet = sif_dev->setaudiomode;

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
        retVal = AUD_AAD_SIF_SetUserAnalogMode (i_eAudioModeSet);

    trace ("kcontrol_sif_useranalogmode\n");
    return retVal;
}

/**
 * get sif status for audio sif device
 *
 */
SINT32 kcontrol_sif_sifexist (SIF_DEVICE_T * sif_dev)
{
    SINT32 retVal = 0;

    bool bSIFStatus = true;

    if (sif_dev == NULL)
    {
        error ("sif_dev is NULL\n");
        return -EFAULT;
    }

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
        retVal = AUD_AAD_SIF_GetSIFSatus (&bSIFStatus);
    sif_dev->sifstatus = bSIFStatus;

    trace ("kcontrol_sif_sifexist\n");
    return retVal;
}

/**
 * set high deviation level for audio sif device
 *
 */
SINT32 kcontrol_sif_hdevlevel (SIF_DEVICE_T * sif_dev)
{
    SINT32 retVal = 0;

    if (sif_dev == NULL)
    {
        error ("sif_dev is NULL\n");
        return -EFAULT;
    }

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
        retVal = kcontrol_hdevlevel (sif_dev, sif_dev->hdevlevel);
    g_bAudHighDevOnOff = sif_dev->hdevlevel;

    trace ("kcontrol_sif_hdevlevel\n");
    return retVal;
}

/**
 * set a2 threshold level for audio sif device
 *
 */
SINT32 kcontrol_sif_a2thresholdlevel (SIF_DEVICE_T * sif_dev)
{
    SINT32 retVal = 0;

    if (sif_dev == NULL)
    {
        error ("sif_dev is NULL\n");
        return -EFAULT;
    }

    if (!aud_disable_aad || lx_chip_rev () >= LX_CHIP_REV (O22, A1))
        retVal = kcontrol_a2thresholdlevel (sif_dev, sif_dev->a2thdlevel);

    trace ("kcontrol_sif_a2thresholdlevel\n");
    return retVal;
}

SINT32 kcontrol_sif_set_data_drop (SIF_DEVICE_T * sif_dev, bool on_off)
{
    return AUD_AAD_SIF_SetDataDrop (on_off);
}
