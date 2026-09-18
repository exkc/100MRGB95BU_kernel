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

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <sound/soc.h>
#include <sound/pcm_params.h>

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "aad_if.h"
#include "alsa_sif.h"
#include "linux/alsa-ext/alsa-ext-broadcast.h"

logm_define (alsasif, log_level_info);
#define trace(fmt,args...)  logm_trace(alsasif,fmt,##args)
#define debug(fmt,args...)  logm_debug(alsasif,fmt,##args)
#define info(fmt,args...)   logm_info(alsasif,fmt,##args)
#define noti(fmt,args...)   logm_noti(alsasif,fmt,##args)
#define warn(fmt,args...)   logm_warning(alsasif,fmt,##args)
#define error(fmt,args...)  logm_error(alsasif,fmt,##args)

static DEFINE_MUTEX (_sif_lock);

#define AUD_SIF_LOCK()		mutex_lock(&_sif_lock)
#define AUD_SIF_UNLOCK()	mutex_unlock(&_sif_lock)

#define ALSA_SIF_MAX 1
#define	ALSA_SIF_DRV_VERSION    2022091300

#define SIF_SYSTEM_AUTO_DETECT 0x1F

SIF_DEVICE_T *sif_dev = NULL;
static BOOLEAN sif_is_closed = FALSE;
static BOOLEAN sif_is_disonnected = FALSE;
static sif_mode_user_ext_type_t sif_analogmode = SIF_USER_PAL_UNKNOWN;

static LX_AAD_COUNTRY_EXT_TYPE_T sif_convert_countryext (sif_country_ext_type_t sif_countryext)
{
    LX_AAD_COUNTRY_EXT_TYPE_T aadInitType = LX_AAD_TYPE_NONE;

    switch (sif_countryext)
    {
        case SIF_ATSC_SELECT:
            aadInitType = LX_AAD_ATSC_SELECT;
            break;

        case SIF_KOREA_A2_SELECT:
            aadInitType = LX_AAD_KOREA_A2_SELECT;
            break;

        case SIF_BTSC_SELECT:
            aadInitType = LX_AAD_BTSC_SELECT;
            break;

        case SIF_BTSC_BR_SELECT:
            aadInitType = LX_AAD_BTSC_BR_SELECT;
            break;

        case SIF_BTSC_US_SELECT:
            aadInitType = LX_AAD_BTSC_US_SELECT;
            break;

        case SIF_DVB_SELECT:
            aadInitType = LX_AAD_DVB_SELECT;
            break;

        case SIF_DVB_ID_SELECT:
            aadInitType = LX_AAD_DVB_ID_SELECT;
            break;

        case SIF_DVB_IN_SELECT:
            aadInitType = LX_AAD_DVB_IN_SELECT;
            break;

        case SIF_DVB_CN_SELECT:
            aadInitType = LX_AAD_DVB_CN_SELECT;
            break;

        case SIF_DVB_AJJA_SELECT:
            aadInitType = LX_AAD_DVB_AJJA_SELECT;
            break;

        case SIF_TYPE_NONE:
        case SIF_TYPE_MAX:
        default:
            aadInitType = LX_AAD_TYPE_NONE;
            break;
    }

    return aadInitType;
}

static LX_AAD_SIF_SOUNDSYSTEM_T sif_convert_soundsystem (sif_soundsystem_ext_type_t sif_soundsystem)
{
    LX_AAD_SIF_SOUNDSYSTEM_T soundsystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

    switch (sif_soundsystem)
    {
        case SIF_SYSTEM_BG:
            soundsystem = LX_AAD_SIF_SYSTEM_BG;
            break;

        case SIF_SYSTEM_I:
            soundsystem = LX_AAD_SIF_SYSTEM_I;
            break;

        case SIF_SYSTEM_DK:
            soundsystem = LX_AAD_SIF_SYSTEM_DK;
            break;

        case SIF_SYSTEM_L:
            soundsystem = LX_AAD_SIF_SYSTEM_L;
            break;

        case SIF_SYSTEM_MN:
            soundsystem = LX_AAD_SIF_SYSTEM_MN;
            break;

        case SIF_SYSTEM_UNKNOWN:
            soundsystem = LX_AAD_SIF_SYSTEM_UNKNOWN;
            break;

        default:
            soundsystem = LX_AAD_SIF_SYSTEM_ERROR;
            break;
    }

    if (sif_soundsystem == SIF_SYSTEM_AUTO_DETECT)
        soundsystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

    return soundsystem;
}

static sif_soundsystem_ext_type_t lx_aad_convert_soundsystem (LX_AAD_SIF_SOUNDSYSTEM_T soundsystem)
{
    sif_soundsystem_ext_type_t sif_soundsystem = SIF_SYSTEM_UNKNOWN;

    switch (soundsystem)
    {
        case LX_AAD_SIF_SYSTEM_BG:
            sif_soundsystem = SIF_SYSTEM_BG;
            break;

        case LX_AAD_SIF_SYSTEM_I:
            sif_soundsystem = SIF_SYSTEM_I;
            break;

        case LX_AAD_SIF_SYSTEM_DK:
            sif_soundsystem = SIF_SYSTEM_DK;
            break;

        case LX_AAD_SIF_SYSTEM_L:
            sif_soundsystem = SIF_SYSTEM_L;
            break;

        case LX_AAD_SIF_SYSTEM_MN:
            sif_soundsystem = SIF_SYSTEM_MN;
            break;

        case LX_AAD_SIF_SYSTEM_UNKNOWN:
        default:
            sif_soundsystem = SIF_SYSTEM_UNKNOWN;
            break;
    }

    return sif_soundsystem;
}

static LX_AAD_SIF_SOUNDSYSTEM_T sif_convert_detectedsoundsystem (sif_soundsystem_ext_type_t
    sif_soundsystem, LX_AAD_SIF_SOUNDSYSTEM_T soundsystem)
{
    LX_AAD_SIF_SOUNDSYSTEM_T detected_soundsystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

    switch (soundsystem)
    {
        case LX_AAD_SIF_SYSTEM_BG:
            if (sif_soundsystem & SIF_SYSTEM_BG)
                detected_soundsystem = LX_AAD_SIF_SYSTEM_BG;
            break;

        case LX_AAD_SIF_SYSTEM_I:
            if (sif_soundsystem & SIF_SYSTEM_I)
                detected_soundsystem = LX_AAD_SIF_SYSTEM_I;
            break;

        case LX_AAD_SIF_SYSTEM_DK:
            if (sif_soundsystem & SIF_SYSTEM_DK)
                detected_soundsystem = LX_AAD_SIF_SYSTEM_DK;
            break;

        case LX_AAD_SIF_SYSTEM_L:
            if (sif_soundsystem & SIF_SYSTEM_L)
                detected_soundsystem = LX_AAD_SIF_SYSTEM_L;
            break;

        case LX_AAD_SIF_SYSTEM_MN:
            if (sif_soundsystem & SIF_SYSTEM_MN)
                detected_soundsystem = LX_AAD_SIF_SYSTEM_MN;
            break;

        case LX_AAD_SIF_SYSTEM_UNKNOWN:
        default:
            detected_soundsystem = LX_AAD_SIF_SYSTEM_UNKNOWN;
            break;
    }

    info ("(detected = %X, sif_sound = 0x%X, sound = 0x%X).\n", detected_soundsystem,
        sif_soundsystem, soundsystem);

    return detected_soundsystem;
}

static LX_AAD_SIF_STANDARD_T sif_convert_standardsetup (sif_standard_ext_type_t sif_standard)
{
    LX_AAD_SIF_STANDARD_T standardMode = LX_AAD_SIF_MODE_DETECT;

    switch (sif_standard)
    {
        case SIF_BG_NICAM:
            standardMode = LX_AAD_SIF_BG_NICAM;
            break;

        case SIF_BG_FM:
            standardMode = LX_AAD_SIF_BG_FM;
            break;

        case SIF_BG_A2:
            standardMode = LX_AAD_SIF_BG_A2;
            break;

        case SIF_I_NICAM:
            standardMode = LX_AAD_SIF_I_NICAM;
            break;

        case SIF_I_FM:
            standardMode = LX_AAD_SIF_I_FM;
            break;

        case SIF_DK_NICAM:
            standardMode = LX_AAD_SIF_DK_NICAM;
            break;

        case SIF_DK_FM:
            standardMode = LX_AAD_SIF_DK_FM;
            break;

        case SIF_DK1_A2:
            standardMode = LX_AAD_SIF_DK1_A2;
            break;

        case SIF_DK2_A2:
            standardMode = LX_AAD_SIF_DK2_A2;
            break;

        case SIF_DK3_A2:
            standardMode = LX_AAD_SIF_DK3_A2;
            break;

        case SIF_L_NICAM:
            standardMode = LX_AAD_SIF_L_NICAM;
            break;

        case SIF_L_AM:
            standardMode = LX_AAD_SIF_L_AM;
            break;

        case SIF_MN_A2:
            standardMode = LX_AAD_SIF_MN_A2;
            break;

        case SIF_MN_BTSC:
            standardMode = LX_AAD_SIF_MN_BTSC;
            break;

        case SIF_MN_EIAJ:
            standardMode = LX_AAD_SIF_MN_EIAJ;
            break;

        case SIF_NUM_SOUND_STD:
            standardMode = LX_AAD_SIF_NUM_SOUND_STD;
            break;

        case SIF_STANDARD_DETECT:
        default:
            standardMode = LX_AAD_SIF_MODE_DETECT;
            break;
    }

    trace ("(sif_standard = %d, standardMode = %d).\n", sif_standard, standardMode);

    return standardMode;
}

static sif_standard_ext_type_t lx_sif_convert_standardsetup (LX_AAD_SIF_STANDARD_T standardMode,
    LX_ATV_AUDIO_MODE_GET_T audiomode)
{
    sif_standard_ext_type_t sif_standard = SIF_STANDARD_DETECT;

    switch (standardMode)
    {
        case LX_AAD_SIF_BG_A2:
            sif_standard = SIF_BG_A2;
            break;

        case LX_AAD_SIF_BG_NICAM:
            if (audiomode == LX_ATV_GET_PAL_NICAM_MONO || audiomode == LX_ATV_GET_PAL_NICAM_STEREO
                || audiomode == LX_ATV_GET_PAL_NICAM_DUAL)
                sif_standard = SIF_BG_NICAM;
            else
                sif_standard = SIF_BG_FM;
            break;

        case LX_AAD_SIF_L_AM:
            if (audiomode == LX_ATV_GET_PAL_NICAM_MONO || audiomode == LX_ATV_GET_PAL_NICAM_STEREO
                || audiomode == LX_ATV_GET_PAL_NICAM_DUAL)
                sif_standard = SIF_L_NICAM;
            else
                sif_standard = SIF_L_AM;
            break;

        case LX_AAD_SIF_I_FM:
            if (audiomode == LX_ATV_GET_PAL_NICAM_MONO || audiomode == LX_ATV_GET_PAL_NICAM_STEREO
                || audiomode == LX_ATV_GET_PAL_NICAM_DUAL)
                sif_standard = SIF_I_NICAM;
            else
                sif_standard = SIF_I_FM;
            break;

        case LX_AAD_SIF_DK1_A2:
            sif_standard = SIF_DK1_A2;
            break;

        case LX_AAD_SIF_DK2_A2:
            sif_standard = SIF_DK2_A2;
            break;

        case LX_AAD_SIF_DK3_A2:
            sif_standard = SIF_DK3_A2;
            break;

        case LX_AAD_SIF_DK_NICAM:
            if (audiomode == LX_ATV_GET_PAL_NICAM_MONO || audiomode == LX_ATV_GET_PAL_NICAM_STEREO
                || audiomode == LX_ATV_GET_PAL_NICAM_DUAL)
                sif_standard = SIF_DK_NICAM;
            else
                sif_standard = SIF_DK_FM;
            break;

        case LX_AAD_SIF_MN_A2:
            sif_standard = SIF_MN_A2;
            break;

        case LX_AAD_SIF_MN_BTSC:
            sif_standard = SIF_MN_BTSC;
            break;

        case LX_AAD_SIF_MODE_DETECT:
        default:
            sif_standard = SIF_MN_A2;
            break;
    }

    trace ("(sif_standard = %d, standardMode = %d, audiomode = %d).\n", sif_standard,
        standardMode, audiomode);

    return sif_standard;
}

static sif_mode_ext_type_t lx_aad_convert_soundmode (LX_ATV_AUDIO_MODE_GET_T getaudiomode)
{
    sif_mode_ext_type_t sif_soundmode = SIF_PAL_UNKNOWN;

    switch (getaudiomode)
    {
        case LX_ATV_GET_PAL_MONO:
            sif_soundmode = SIF_PAL_MONO;
            break;

        case LX_ATV_GET_PAL_STEREO:
            sif_soundmode = SIF_PAL_STEREO;
            break;

        case LX_ATV_GET_PAL_DUAL:
            sif_soundmode = SIF_PAL_DUAL;
            break;

        case LX_ATV_GET_PAL_NICAM_MONO:
            sif_soundmode = SIF_PAL_NICAM_MONO;
            break;

        case LX_ATV_GET_PAL_NICAM_STEREO:
            sif_soundmode = SIF_PAL_NICAM_STEREO;
            break;

        case LX_ATV_GET_PAL_NICAM_DUAL:
            sif_soundmode = SIF_PAL_NICAM_DUAL;
            break;

        case LX_ATV_GET_PAL_UNKNOWN:
            sif_soundmode = SIF_PAL_UNKNOWN;
            break;

        case LX_ATV_GET_NTSC_A2_MONO:
            sif_soundmode = SIF_NTSC_A2_MONO;
            break;

        case LX_ATV_GET_NTSC_A2_STEREO:
            sif_soundmode = SIF_NTSC_A2_STEREO;
            break;

        case LX_ATV_GET_NTSC_A2_SAP:
            sif_soundmode = SIF_NTSC_A2_SAP;
            break;

        case LX_ATV_GET_NTSC_A2_UNKNOWN:
            sif_soundmode = SIF_NTSC_A2_UNKNOWN;
            break;

        case LX_ATV_GET_NTSC_BTSC_MONO:
            sif_soundmode = SIF_NTSC_BTSC_MONO;
            break;

        case LX_ATV_GET_NTSC_BTSC_STEREO:
            sif_soundmode = SIF_NTSC_BTSC_STEREO;
            break;

        case LX_ATV_GET_NTSC_BTSC_SAP_MONO:
            sif_soundmode = SIF_NTSC_BTSC_SAP_MONO;
            break;

        case LX_ATV_GET_NTSC_BTSC_SAP_STEREO:
            sif_soundmode = SIF_NTSC_BTSC_SAP_STEREO;
            break;

        case LX_ATV_GET_NTSC_BTSC_UNKNOWN:
            sif_soundmode = SIF_NTSC_BTSC_UNKNOWN;
            break;

        default:
            sif_soundmode = SIF_PAL_UNKNOWN;
            break;
    }

    return sif_soundmode;
}

static LX_ATV_AUDIO_MODE_SET_T sif_convert_soundmode (sif_mode_user_ext_type_t sif_soundmode)
{
    LX_ATV_AUDIO_MODE_SET_T audiomode = LX_ATV_SET_PAL_UNKNOWN;

    switch (sif_soundmode)
    {
        case SIF_USER_PAL_UNKNOWN:
            audiomode = LX_ATV_SET_PAL_UNKNOWN;
            break;

        case SIF_USER_PAL_MONO:
            audiomode = LX_ATV_SET_PAL_MONO;
            break;

        case SIF_USER_PAL_MONO_FORCED:
            audiomode = LX_ATV_SET_PAL_MONO_FORCED;
            break;

        case SIF_USER_PAL_STEREO:
            audiomode = LX_ATV_SET_PAL_STEREO;
            break;

        case SIF_USER_PAL_STEREO_FORCED:
            audiomode = LX_ATV_SET_PAL_STEREO_FORCED;
            break;

        case SIF_USER_PAL_DUALI:
            audiomode = LX_ATV_SET_PAL_DUALI;
            break;

        case SIF_USER_PAL_DUALII:
            audiomode = LX_ATV_SET_PAL_DUALII;
            break;

        case SIF_USER_PAL_DUALI_II:
            audiomode = LX_ATV_SET_PAL_DUALI_II;
            break;

        case SIF_USER_PAL_NICAM_MONO:
            audiomode = LX_ATV_SET_PAL_NICAM_MONO;
            break;

        case SIF_USER_PAL_NICAM_MONO_FORCED:
            audiomode = LX_ATV_SET_PAL_NICAM_MONO_FORCED;
            break;

        case SIF_USER_PAL_NICAM_STEREO:
            audiomode = LX_ATV_SET_PAL_NICAM_STEREO;
            break;

        case SIF_USER_PAL_NICAM_STEREO_FORCED:
            audiomode = LX_ATV_SET_PAL_NICAM_STEREO_FORCED;
            break;

        case SIF_USER_PAL_NICAM_DUALI:
            audiomode = LX_ATV_SET_PAL_NICAM_DUALI;
            break;

        case SIF_USER_PAL_NICAM_DUALII:
            audiomode = LX_ATV_SET_PAL_NICAM_DUALII;
            break;

        case SIF_USER_PAL_NICAM_DUALI_II:
            audiomode = LX_ATV_SET_PAL_NICAM_DUALI_II;
            break;

        case SIF_USER_PAL_NICAM_DUAL_FORCED:
            audiomode = LX_ATV_SET_PAL_NICAM_DUAL_FORCED;
            break;

        case SIF_USER_NTSC_A2_UNKNOWN:
            audiomode = LX_ATV_SET_NTSC_A2_UNKNOWN;
            break;

        case SIF_USER_NTSC_A2_MONO:
            audiomode = LX_ATV_SET_NTSC_A2_MONO;
            break;

        case SIF_USER_NTSC_A2_STEREO:
            audiomode = LX_ATV_SET_NTSC_A2_STEREO;
            break;

        case SIF_USER_NTSC_A2_SAP:
            audiomode = LX_ATV_SET_NTSC_A2_SAP;
            break;

        case SIF_USER_NTSC_BTSC_UNKNOWN:
            audiomode = LX_ATV_SET_NTSC_BTSC_UNKNOWN;
            break;

        case SIF_USER_NTSC_BTSC_MONO:
            audiomode = LX_ATV_SET_NTSC_BTSC_MONO;
            break;

        case SIF_USER_NTSC_BTSC_STEREO:
            audiomode = LX_ATV_SET_NTSC_BTSC_STEREO;
            break;

        case SIF_USER_NTSC_BTSC_SAP_MONO:
            audiomode = LX_ATV_SET_NTSC_BTSC_SAP_MONO;
            break;

        case SIF_USER_NTSC_BTSC_SAP_STEREO:
            audiomode = LX_ATV_SET_NTSC_BTSC_SAP_STEREO;
            break;

        default:
            audiomode = LX_ATV_SET_ERROR;
            break;
    }

    return audiomode;
}

void sif_set_data_drop (bool on_off)
{
    SINT32 ret = 0;

    ret = kcontrol_sif_set_data_drop (sif_dev, on_off);

    if (ret < 0)
    {
        error ("sif_set_data_drop failed\n");
    }
}

static int sif_open_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_SIF_MAX;
    return 0;
}

static int sif_open_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    SINT32 isOpend;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
        isOpend = 0;
    else
        isOpend = 1;

    ucontrol->value.integer.value[0] = isOpend;

    AUD_SIF_UNLOCK ();
    info ("(isOpend = %d).\n", isOpend);
    return 0;
}

static int sif_open (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    AUD_SIF_LOCK ();

    if (sif_dev != NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("kcontrol_sif_open is already opend\n");
        return -EINVAL;
    }

    sif_dev = kcontrol_sif_open ();
    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("kcontrol_sif_open error\n");
        return -EIO;
    }

    sif_is_closed = FALSE;
    sif_analogmode = SIF_USER_PAL_UNKNOWN;

    AUD_SIF_UNLOCK ();
    info ("(sif_dev = %p, sif_is_closed = %d(Ver. = %d)).\n", sif_dev, sif_is_closed,
        ALSA_SIF_DRV_VERSION);
    return 0;
}

static int sif_close_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_SIF_MAX;
    return 0;
}

static int sif_close_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    AUD_SIF_LOCK ();

    ucontrol->value.integer.value[0] = sif_is_closed;

    AUD_SIF_UNLOCK ();
    info ("(sif_is_closed = %d).\n", sif_is_closed);
    return 0;
}

static int sif_close (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    SINT32 ret;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("kcontrol_sif_open is not opended\n");
        return -EINVAL;
    }

    ret = kcontrol_sif_close (sif_dev);
    if (ret)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_close error\n");
        return -EIO;
    }

    sif_dev = NULL;
    sif_is_closed = TRUE;

    AUD_SIF_UNLOCK ();
    info ("(sif_dev = %p).\n", sif_dev);
    return 0;
}

static int sif_connect_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 1;
    return 0;
}

static int sif_connect_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    SINT32 connected;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
        connected = FALSE;
    else
        connected = sif_dev->connected;

    ucontrol->value.integer.value[0] = connected;

    AUD_SIF_UNLOCK ();
    info ("(connected = %d).\n", connected);
    return 0;
}

static int sif_connect (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    if (sif_dev->connected == TRUE)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is doublely connected.\n");
        return -EINVAL;
    }

    sif_dev->connected = TRUE;
    sif_is_disonnected = FALSE;

    AUD_SIF_UNLOCK ();
    info ("(connected = %d).\n", sif_dev->connected);
    return 0;
}

static int sif_disconnect_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 1;
    return 0;
}

static int sif_disconnect_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    AUD_SIF_LOCK ();

    ucontrol->value.integer.value[0] = sif_is_disonnected;

    AUD_SIF_UNLOCK ();
    info ("(sif_is_disonnected = %d).\n", sif_is_disonnected);
    return 0;
}

static int sif_disconnect (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    if (sif_dev->connected == TRUE && sif_is_disonnected == TRUE)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is doublely disconnected.\n");
        return -EINVAL;
    }

    sif_dev->connected = FALSE;
    sif_is_disonnected = TRUE;

    AUD_SIF_UNLOCK ();
    info ("(sif_is_disonnected = %d).\n", sif_is_disonnected);
    return 0;
}

static int sif_soundsystem_strength_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 0xffff;
    return 0;
}

static int sif_soundsystem_strength_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    sif_soundsystem_ext_type_t soundsystem;
    SINT32 strength;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        soundsystem = SIF_SYSTEM_UNKNOWN;
        strength = 0;
    }
    else
    {
        soundsystem = lx_aad_convert_soundsystem (sif_dev->detectsoundsystem);
        strength = sif_dev->band_strength;
    }

    ucontrol->value.integer.value[0] = soundsystem;
    ucontrol->value.integer.value[1] = strength;

    AUD_SIF_UNLOCK ();
    info ("(soundsystem = %d, strength = %d).\n", soundsystem, strength);
    return 0;
}

static int sif_soundsystem_strength (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    sif_soundsystem_ext_type_t sound_system;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    sound_system = ucontrol->value.integer.value[0];

    sif_dev->detectsoundsystem = sif_convert_soundsystem (sound_system);

    if (sif_dev->detectsoundsystem == LX_AAD_SIF_SYSTEM_ERROR)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_soundsystem_ext_type_t is error(0x%x)\n", sound_system);
        return -EINVAL;
    }

    kcontrol_sif_detectsoundsystem (sif_dev);

    if (sif_dev->detectsoundsystem != sif_dev->detectedsoundsystem)
    {
        sif_dev->band_strength = 0;
    }

    AUD_SIF_UNLOCK ();
    info ("sif_soundsystem_strngth. sound_system: %d, band_strength: %d\n", sound_system,
        sif_dev->band_strength);

    return 0;
}

static int sif_detectsoundsystem_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 0xffff;
    return 0;
}

static int sif_detectsoundsystem_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    sif_soundsystem_ext_type_t soundsystem;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
        soundsystem = SIF_SYSTEM_UNKNOWN;
    else
        soundsystem = lx_aad_convert_soundsystem (sif_dev->detectedsoundsystem);

    ucontrol->value.integer.value[0] = soundsystem;

    AUD_SIF_UNLOCK ();
    info ("(soundsystem = %d).\n", soundsystem);
    return 0;
}

static int sif_detectsoundsystem (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    SINT32 ret, loop, retryCnt = 1;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    sif_dev->detectsoundsystem = sif_convert_soundsystem (ucontrol->value.integer.value[0]);
    if (sif_dev->detectsoundsystem == LX_AAD_SIF_SYSTEM_ERROR)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_soundsystem_ext_type_t is error(0x%lx)\n", ucontrol->value.integer.value[0]);
        return -EINVAL;
    }

    if (ucontrol->value.integer.value[0] == SIF_SYSTEM_AUTO_DETECT)
        retryCnt = 5;

    /* Retry for SoCTS auto detect case. */
    for (loop = 0; loop < retryCnt; loop++)
    {
        ret = kcontrol_sif_detectsoundsystem (sif_dev);
        if (ret)
        {
            sif_dev->detectedsoundsystem = LX_AAD_SIF_SYSTEM_UNKNOWN;

            AUD_SIF_UNLOCK ();
            error ("kcontrol_sif_detectsoundsystem error\n");
            return -EIO;
        }

        sif_dev->detectedsoundsystem =
            sif_convert_detectedsoundsystem (ucontrol->value.integer.value[0],
            sif_dev->detectedsoundsystem);

        AUD_SIF_UNLOCK ();
        info ("(detect = 0x%X, detected = 0x%X).\n",
            (UINT32) ucontrol->value.integer.value[0],
            lx_aad_convert_soundsystem (sif_dev->detectedsoundsystem));

        if (sif_dev->detectedsoundsystem != LX_AAD_SIF_SYSTEM_UNKNOWN)
            break;
    }

    return 0;
}

static int sif_bandsetup_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 0xffff;
    return 0;
}

static int sif_bandsetup_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    sif_country_ext_type_t countryext;
    sif_soundsystem_ext_type_t soundsystem;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        countryext = SIF_TYPE_NONE;
        soundsystem = SIF_SYSTEM_UNKNOWN;
    }
    else
    {
        countryext = (sif_country_ext_type_t)sif_dev->countryext;
        soundsystem = lx_aad_convert_soundsystem (sif_dev->soundsystem);
    }

    ucontrol->value.integer.value[0] = countryext;
    ucontrol->value.integer.value[1] = soundsystem;

    AUD_SIF_UNLOCK ();
    info ("(countryext = 0x%x, soundsystem = %d).\n", countryext, soundsystem);
    return 0;
}

static int sif_bandsetup (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    SINT32 ret;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    sif_dev->countryext = sif_convert_countryext (ucontrol->value.integer.value[0]);
    if (sif_dev->countryext == LX_AAD_TYPE_NONE)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_country_ext_type_t is error(0x%lx)\n", ucontrol->value.integer.value[0]);
        return -EINVAL;
    }

    sif_dev->soundsystem = sif_convert_soundsystem (ucontrol->value.integer.value[1]);
    if (sif_dev->soundsystem == LX_AAD_SIF_SYSTEM_ERROR)
    {
        sif_dev->countryext = LX_AAD_TYPE_NONE;

        AUD_SIF_UNLOCK ();
        error ("sif_soundsystem_ext_type_t is error(0x%lx)\n", ucontrol->value.integer.value[1]);
        return -EINVAL;
    }

    ret = kcontrol_sif_bandsetup (sif_dev);
    if (ret)
    {
        AUD_SIF_UNLOCK ();
        error ("kcontrol_sif_bandsetup error\n");
        return -EIO;
    }

    AUD_SIF_UNLOCK ();
    info ("(countryext = 0x%x, soundsystem = 0x%lx).\n", sif_dev->countryext,
        ucontrol->value.integer.value[1]);
    return 0;
}

static int sif_standardsetup_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 0xffff;
    return 0;
}

static int sif_standardsetup_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    sif_standard_ext_type_t getsoundstandard;

    if (sif_dev == NULL)
    {
        ucontrol->value.integer.value[0] = SIF_NUM_SOUND_STD;
        return 0;
    }

    AUD_SIF_LOCK ();

    kcontrol_sif_getsoundstandard (sif_dev);
    kcontrol_sif_curanalogmode (sif_dev);
    getsoundstandard = lx_sif_convert_standardsetup (sif_dev->getsoundstandard,
        sif_dev->getaudiomode);

    ucontrol->value.integer.value[0] = getsoundstandard;

    AUD_SIF_UNLOCK ();
    trace ("(getsoundstandard = %d).\n", getsoundstandard);
    return 0;
}

static int sif_standardsetup (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    SINT32 ret;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    sif_dev->setsoundstandard = sif_convert_standardsetup (ucontrol->value.integer.value[0]);

    ret = kcontrol_sif_standardsetup (sif_dev);
    if (ret)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_standardsetup error\n");
        return -EIO;
    }

    AUD_SIF_UNLOCK ();
    trace ("(setsoundstandard = %d).\n", sif_dev->setsoundstandard);
    return 0;
}

static int sif_curanalogmode_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 0x20;
    return 0;
}

static int sif_curanalogmode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    SINT32 ret;

    sif_mode_ext_type_t audiomode;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    ret = kcontrol_sif_curanalogmode (sif_dev);
    if (ret)
        audiomode = SIF_NTSC_BTSC_UNKNOWN;
    else
        audiomode = lx_aad_convert_soundmode (sif_dev->getaudiomode);

    ucontrol->value.integer.value[0] = audiomode;

    AUD_SIF_UNLOCK ();
    trace ("(audiomode = %d).\n", audiomode);
    return 0;
}

static int sif_useranalogmode_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 0x20;
    return 0;
}

static int sif_useranalogmode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    ucontrol->value.integer.value[0] = sif_analogmode;

    AUD_SIF_UNLOCK ();
    debug ("(audiomode = %d).\n", sif_analogmode);
    return 0;
}

static int sif_useranalogmode (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    SINT32 ret;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    sif_dev->setaudiomode = sif_convert_soundmode (ucontrol->value.integer.value[0]);
    if (sif_dev->setaudiomode == LX_ATV_SET_ERROR)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_mode_user_ext_type_t is error(0x%lx)\n", ucontrol->value.integer.value[0]);
        return -EINVAL;
    }

    sif_analogmode = ucontrol->value.integer.value[0];

    ret = kcontrol_sif_useranalogmode (sif_dev);
    if (ret)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_useranalogmode error\n");
        return -EIO;
    }

    AUD_SIF_UNLOCK ();
    debug ("(setaudiomode = %d).\n", sif_dev->setaudiomode);
    return 0;
}

static int sif_sifexist_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 0x20;
    return 0;
}

static int sif_sifexist_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    SINT32 ret;

    SINT32 sifstatus;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
        sifstatus = 0;
    else
    {
        ret = kcontrol_sif_sifexist (sif_dev);
        if (ret)
            sifstatus = 0;
        else
            sifstatus = sif_dev->sifstatus;
    }

    ucontrol->value.integer.value[0] = sifstatus;

    AUD_SIF_UNLOCK ();
    debug ("(sifstatus = %d).\n", sifstatus);
    return 0;
}

static int sif_hdevlevel_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0 - 1;
    uinfo->value.integer.max = 1 + 1;
    return 0;
}

static int sif_hdevlevel_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    SINT32 hdevlevel;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
        hdevlevel = 0;
    else
        hdevlevel = sif_dev->hdevlevel;

    ucontrol->value.integer.value[0] = hdevlevel;

    AUD_SIF_UNLOCK ();
    info ("(hdevlevel = %d).\n", hdevlevel);
    return 0;
}

static int sif_hdevlevel (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    SINT32 ret;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    if (ucontrol->value.integer.value[0] < 0 || ucontrol->value.integer.value[0] > 1)
    {
        AUD_SIF_UNLOCK ();
        error ("hdev_onoff is error(%lu)\n", ucontrol->value.integer.value[0]);
        return -EINVAL;
    }

    sif_dev->hdevlevel = ucontrol->value.integer.value[0];

    ret = kcontrol_sif_hdevlevel (sif_dev);
    if (ret)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_hdevlevel error\n");
        return -EIO;
    }

    AUD_SIF_UNLOCK ();
    info ("(hdevlevel = %d).\n", sif_dev->hdevlevel);
    return 0;
}

static int sif_a2thresholdlevel_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0 - 1;
    uinfo->value.integer.max = 100 + 1;
    return 0;
}

static int sif_a2thresholdlevel_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    SINT32 a2thdlevel;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
        a2thdlevel = 0;
    else
        a2thdlevel = sif_dev->a2thdlevel;

    ucontrol->value.integer.value[0] = a2thdlevel;

    AUD_SIF_UNLOCK ();
    info ("(a2thdlevel = %d).\n", a2thdlevel);
    return 0;
}

static int sif_a2thresholdlevel (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    SINT32 ret;

    AUD_SIF_LOCK ();

    if (sif_dev == NULL)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_dev is not opended\n");
        return -EINVAL;
    }

    if (ucontrol->value.integer.value[0] < 0 || ucontrol->value.integer.value[0] > 100)
    {
        AUD_SIF_UNLOCK ();
        error ("a2thresholdlevel is error(%lu)\n", ucontrol->value.integer.value[0]);
        return -EINVAL;
    }

    sif_dev->a2thdlevel = ucontrol->value.integer.value[0];

    ret = kcontrol_sif_a2thresholdlevel (sif_dev);
    if (ret)
    {
        AUD_SIF_UNLOCK ();
        error ("sif_a2thresholdlevel error\n");
        return -EIO;
    }

    AUD_SIF_UNLOCK ();
    info ("(a2thdlevel = %d).\n", sif_dev->a2thdlevel);
    return 0;
}


static const struct snd_kcontrol_new sif_controls[] = {
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_OPEN,
            .info = sif_open_info,
            .get = sif_open_get,
            .put = sif_open,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_CLOSE,
            .info = sif_close_info,
            .get = sif_close_get,
            .put = sif_close,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_CONNECT,
            .info = sif_connect_info,
            .get = sif_connect_get,
            .put = sif_connect,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_DISCONNECT,
            .info = sif_disconnect_info,
            .get = sif_disconnect_get,
            .put = sif_disconnect,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_SOUNDSYSTEMSTRENGTH,
            .info = sif_soundsystem_strength_info,
            .get = sif_soundsystem_strength_get,
            .put = sif_soundsystem_strength,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_DETECTSOUNDSYSTEM,
            .info = sif_detectsoundsystem_info,
            .get = sif_detectsoundsystem_get,
            .put = sif_detectsoundsystem,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_BANDSETUP,
            .info = sif_bandsetup_info,
            .get = sif_bandsetup_get,
            .put = sif_bandsetup,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_STANDARDSETUP,
            .info = sif_standardsetup_info,
            .get = sif_standardsetup_get,
            .put = sif_standardsetup,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_CUR_ANALOGMODE,
            .info = sif_curanalogmode_info,
            .get = sif_curanalogmode_get,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_USER_ANALOGMODE,
            .info = sif_useranalogmode_info,
            .get = sif_useranalogmode_get,
            .put = sif_useranalogmode,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_SIFEXIST,
            .info = sif_sifexist_info,
            .get = sif_sifexist_get,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_HDEV,
            .info = sif_hdevlevel_info,
            .get = sif_hdevlevel_get,
            .put = sif_hdevlevel,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = SIF_A2THERESHOLDLEVEL,
            .info = sif_a2thresholdlevel_info,
            .get = sif_a2thresholdlevel_get,
            .put = sif_a2thresholdlevel,
        },
};

static int _proc_atv_status_show (struct seq_file *m, void *data)
{
    int isOpened = 0;
    int isConnected = 0;
    char *country = "NONE";
    char *soundsystem = "UNKNOWN";
    char *standard = "UNKNOWN";
    char *analogmode_set = "UNKNOWN";
    char *analogmode_get = "UNKNOWN";
    char *sifexist = "ABSENT";
    int hdev = 0;

    struct atv_country
    {
        int country;
        char *name;
    } country_info[] =
    {
        /* *INDENT-OFF* */
        {LX_AAD_TYPE_NONE, "NONE"},
        {LX_AAD_ATSC_SELECT, "ATSC"},
        {LX_AAD_KOREA_A2_SELECT, "KOREA_A2"},
        {LX_AAD_BTSC_SELECT, "BTSC"},
        {LX_AAD_BTSC_BR_SELECT, "BTSC_BR"},
        {LX_AAD_BTSC_US_SELECT, "BTSC_US"},
        {LX_AAD_DVB_SELECT, "DVB"},
        {LX_AAD_DVB_ID_SELECT, "DVB_ID"},
        {LX_AAD_DVB_IN_SELECT, "DVB_IN"},
        {LX_AAD_DVB_CN_SELECT, "DVB_CN"},
        {LX_AAD_DVB_AJJA_SELECT, "DVB_AJJA"},
        /* *INDENT-ON* */
    };
    struct atv_sound_system
    {
        int drv_soundsystem;
        int app_soundsystem;
        char *name;
    } soundsystem_info[] =
    {
        /* *INDENT-OFF* */
        {LX_AAD_SIF_SYSTEM_UNKNOWN, SIF_SYSTEM_UNKNOWN, "UNKNOWN"},
        {LX_AAD_SIF_SYSTEM_BG, SIF_SYSTEM_BG, "BG"},
        {LX_AAD_SIF_SYSTEM_I, SIF_SYSTEM_I, "I"},
        {LX_AAD_SIF_SYSTEM_DK, SIF_SYSTEM_DK, "DK"},
        {LX_AAD_SIF_SYSTEM_L, SIF_SYSTEM_L, "L"},
        {LX_AAD_SIF_SYSTEM_MN, SIF_SYSTEM_MN, "MN"},
        /* *INDENT-ON* */
    };
    struct atv_standard
    {
        int standard;
        char *name;
    } standard_info[] =
    {
        /* *INDENT-OFF* */
        {LX_AAD_SIF_MODE_DETECT, "DETECT"},
        {LX_AAD_SIF_BG_NICAM, "BG_NICAM"},
        {LX_AAD_SIF_BG_FM, "BG_FM"},
        {LX_AAD_SIF_BG_A2, "BG_A2"},
        {LX_AAD_SIF_I_NICAM, "I_NICAM"},
        {LX_AAD_SIF_I_FM, "I_FM"},
        {LX_AAD_SIF_DK_NICAM, "DK_NICAM"},
        {LX_AAD_SIF_DK_FM, "DK_FM"},
        {LX_AAD_SIF_DK1_A2, "DK1_A2"},
        {LX_AAD_SIF_DK2_A2, "DK2_A2"},
        {LX_AAD_SIF_DK3_A2, "DK3_A2"},
        {LX_AAD_SIF_L_NICAM, "L_NICAM"},
        {LX_AAD_SIF_L_AM, "L_AM"},
        {LX_AAD_SIF_MN_A2, "MN_A2"},
        {LX_AAD_SIF_MN_BTSC, "MN_BTSC"},
        {LX_AAD_SIF_MN_EIAJ, "MN_EIAJ"},
        {LX_AAD_SIF_NUM_SOUND_STD, "UNKNOWN"},
        /* *INDENT-ON* */
    };
    struct atv_get_analogmode
    {
        int analogmode;
        char *name;
    } get_analogmode_info[] =
    {
        /* *INDENT-OFF* */
        {LX_ATV_GET_PAL_MONO, "PAL_MONO"},
        {LX_ATV_GET_PAL_STEREO, "PAL_STEREO"},
        {LX_ATV_GET_PAL_DUAL, "PAL_DUAL"},
        {LX_ATV_GET_PAL_NICAM_MONO, "PAL_NICAM_MONO"},
        {LX_ATV_GET_PAL_NICAM_STEREO, "PAL_NICAM_STEREO"},
        {LX_ATV_GET_PAL_NICAM_DUAL, "PAL_NICAM_DUAL"},
        {LX_ATV_GET_PAL_UNKNOWN, "PAL_UNKNOWN"},
        {LX_ATV_GET_NTSC_A2_MONO, "NTSC_A2_MONO"},
        {LX_ATV_GET_NTSC_A2_STEREO, "NTSC_A2_STEREO"},
        {LX_ATV_GET_NTSC_A2_SAP, "NTSC_A2_SAP"},
        {LX_ATV_GET_NTSC_A2_UNKNOWN, "NTSC_A2_UNKNOWN"},
        {LX_ATV_GET_NTSC_BTSC_MONO, "NTSC_BTSC_MONO"},
        {LX_ATV_GET_NTSC_BTSC_STEREO, "NTSC_BTSC_STEREO"},
        {LX_ATV_GET_NTSC_BTSC_SAP_MONO, "NTSC_BTSC_SAP_MONO"},
        {LX_ATV_GET_NTSC_BTSC_SAP_STEREO, "NTSC_BTSC_SAP_STEREO"},
        {LX_ATV_GET_NTSC_BTSC_UNKNOWN, "NTSC_BTSC_UNKNOWN"},
        /* *INDENT-ON* */
    };
    struct atv_set_analogmode
    {
        int analogmode;
        char *name;
    } set_analogmode_info[] =
    {
        /* *INDENT-OFF* */
        {LX_ATV_SET_PAL_MONO, "PAL_MONO"},
        {LX_ATV_SET_PAL_MONO_FORCED, "PAL_MONO_FORCED"},
        {LX_ATV_SET_PAL_STEREO, "PAL_STEREO"},
        {LX_ATV_SET_PAL_STEREO_FORCED, "PAL_STEREO_FORCED"},
        {LX_ATV_SET_PAL_DUALI, "PAL_DUAL_I"},
        {LX_ATV_SET_PAL_DUALII, "PAL_DUAL_II"},
        {LX_ATV_SET_PAL_DUALI_II, "PAL_DUAL_I_II"},
        {LX_ATV_SET_PAL_NICAM_MONO, "PAL_NICAM_MONO"},
        {LX_ATV_SET_PAL_NICAM_MONO_FORCED, "PAL_NICAM_MONO_FORCED"},
        {LX_ATV_SET_PAL_NICAM_STEREO, "PAL_NICAM_STEREO"},
        {LX_ATV_SET_PAL_NICAM_STEREO_FORCED, "PAL_NICAM_STEREO_FORCED"},
        {LX_ATV_SET_PAL_NICAM_DUALI, "PAL_NICAM_DUAL_I"},
        {LX_ATV_SET_PAL_NICAM_DUALII, "PAL_NICAM_DUAL_II"},
        {LX_ATV_SET_PAL_NICAM_DUALI_II, "PAL_NICAM_DUAL_I_II"},
        {LX_ATV_SET_PAL_NICAM_DUAL_FORCED, "PAL_NICAM_DUAL_FORCED"},
        {LX_ATV_SET_PAL_UNKNOWN, "PAL_UNKNOWN"},
        {LX_ATV_SET_NTSC_A2_MONO, "NTSC_A2_MONO"},
        {LX_ATV_SET_NTSC_A2_STEREO, "NTSC_A2_STEREO"},
        {LX_ATV_SET_NTSC_A2_SAP, "NTSC_A2_SAP"},
        {LX_ATV_SET_NTSC_A2_UNKNOWN, "NTSC_A2_UNKNOWN"},
        {LX_ATV_SET_NTSC_BTSC_MONO, "NTSC_BTSC_MONO"},
        {LX_ATV_SET_NTSC_BTSC_STEREO, "NTSC_BTSC_STEREO"},
        {LX_ATV_SET_NTSC_BTSC_SAP_MONO, "NTSC_BTSC_SAP_MONO"},
        {LX_ATV_SET_NTSC_BTSC_SAP_STEREO, "NTSC_BTSC_SAP_STEREO"},
        {LX_ATV_SET_NTSC_BTSC_UNKNOWN, "NTSC_BTSC_UNKNOWN"},
        {LX_ATV_SET_ERROR, "ERROR"},
        /* *INDENT-ON* */
    };

    if (sif_dev != NULL)
    {
        int i;

        isOpened = 1;
        isConnected = sif_dev->connected;
        for (i = 0; i < sizeof (country_info) / sizeof (country_info[0]); i++)
        {
            if (country_info[i].country == sif_dev->countryext)
                country = country_info[i].name;
        }
        for (i = 0; i < sizeof (soundsystem_info) / sizeof (soundsystem_info[0]); i++)
        {
            if (soundsystem_info[i].drv_soundsystem == sif_dev->soundsystem)
                soundsystem = soundsystem_info[i].name;
        }
        for (i = 0; i < sizeof (standard_info) / sizeof (standard_info[0]); i++)
        {
            if (standard_info[i].standard == sif_dev->setsoundstandard)
                standard = standard_info[i].name;
        }
        if (kcontrol_sif_curanalogmode (sif_dev) == RET_OK)
        {
            for (i = 0; i < sizeof (get_analogmode_info) / sizeof (get_analogmode_info[0]); i++)
            {
                if (get_analogmode_info[i].analogmode == sif_dev->getaudiomode)
                    analogmode_get = get_analogmode_info[i].name;
            }
        }
        for (i = 0; i < sizeof (set_analogmode_info) / sizeof (set_analogmode_info[0]); i++)
        {
            if (set_analogmode_info[i].analogmode == sif_dev->setaudiomode)
                analogmode_set = set_analogmode_info[i].name;
        }
        if (kcontrol_sif_sifexist (sif_dev) == RET_OK)
        {
            if (sif_dev->sifstatus)
                sifexist = "PRESENT";
        }
        hdev = sif_dev->hdevlevel;
    }

    seq_printf (m, "Open=%d\n", isOpened);
    seq_printf (m, "Connect=%d\n", isConnected);
    seq_printf (m, "BandCountry=%s\n", country);
    seq_printf (m, "BandSoundSystem=%s\n", soundsystem);
    seq_printf (m, "Standard=%s\n", standard);
    seq_printf (m, "CurAnalogMode=%s\n", analogmode_get);
    seq_printf (m, "UserAnalogMode=%s\n", analogmode_set);
    seq_printf (m, "SifExist=%s\n", sifexist);
    seq_printf (m, "HDev=%d\n", hdev);

    return 0;
}

static int _proc_atv_status_open (struct inode *inode, struct file *file)
{
    int ret;

    ret = single_open (file, _proc_atv_status_show, NULL);
    if (ret < 0)
        return ret;

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops _proc_atv_status_fops = {
    .proc_open = _proc_atv_status_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};
#else
static struct file_operations _proc_atv_status_fops = {
    .open = _proc_atv_status_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};
#endif

extern struct proc_dir_entry *aproc_seetv;

int register_sif_kcontrols (struct snd_soc_card *card)
{
    int ret = 0;

    ret = snd_soc_add_card_controls (card, sif_controls, ARRAY_SIZE (sif_controls));
    if (ret != RET_OK)
    {
        error ("add control is failed (ret %d)\n", ret);
        return ret;
    }

    // create proc node for debug status
    proc_create_data ("atv", 0440, aproc_seetv, &_proc_atv_status_fops, NULL);

    info ("completed \n");
    return ret;
}
