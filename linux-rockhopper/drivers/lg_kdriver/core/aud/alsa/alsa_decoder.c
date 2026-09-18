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

#include <linux/module.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include "linux/alsa-ext/alsa-ext-broadcast.h"
#include "linux/alsa-ext/alsa-ext-extinput.h"

#include <sound/soc.h>
#include <sound/pcm_params.h>

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "log.h"
#include "audio_kapi.h"

#include "block.h"
#include "input.h"
#include "decoder.h"
#include "renderer.h"
#include "mixer.h"
#include "se.h"
#include "output.h"
#include "encoder.h"
#include "capture.h"
#include "block_manager.h"
#include "clock.h"
#include "hal/hal.h"
#include "kaimc.h"

#include "alsa_decoder.h"
#include "alsa_support_sndout.h"
#include "alsa_sif.h"
#include "alsa_capture.h"
#include "hdmi_kapi.h"
#include "blind.h"

logm_define (alsadec, log_level_info);
#define trace(fmt,args...)  logm_trace(alsadec,fmt,##args)
#define debug(fmt,args...)  logm_debug(alsadec,fmt,##args)
#define info(fmt,args...)   logm_info(alsadec,fmt,##args)
#define noti(fmt,args...)   logm_noti(alsadec,fmt,##args)
#define warn(fmt,args...)   logm_warning(alsadec,fmt,##args)
#define error(fmt,args...)  logm_error(alsadec,fmt,##args)

#define debug_call() debug("ALSA_CALL# %s(): %ld %ld %ld", __func__, ucontrol->value.integer.value[0], ucontrol->value.integer.value[1], ucontrol->value.integer.value[2])

#define ALSA_ADEC_INT_MIN (0x80000000)
#define ALSA_ADEC_INT_MAX (0x7FFFFFFF)

#define ALSA_HDMI_IN_MAX (4)
#define ALSA_ADC_IN_MAX (0xFF)
#define ALSA_DP_IN_MAX (2)

#define ALSA_GROUP_INDEX_MAX (0x20)

#define ALSA_DEFAULT_PRL_MIN (-31)
#define ALSA_DEFAULT_PRL_MAX (0)
#define ALSA_INVALID_DEFAULT_PRL (0x7FFFFFFF)

#define ALSA_ASSOCIATE_MIX_BALANCE_MIN (-32)
#define ALSA_ASSOCIATE_MIX_BALANCE_MAX (32)

#define ALSA_DEFAULT_MAIN_AUDIO_INDEX (-1)

#define PES_BUFFER_SIZE     0x10010     ///< PES Buffer Size.(fw/xt_dsp/module/tpin.c)
#define DISCARD_PACKET_SIZE 7   ///< PES Discard Packet Size.(fw/xt_dsp/module/tpin.c)

static DEFINE_MUTEX (alsa_decoder_lock);

#define ALSADEC_LOCK()   mutex_lock(&alsa_decoder_lock)
#define ALSADEC_UNLOCK() mutex_unlock(&alsa_decoder_lock)

ALSA_DECODER_INFO_T alsa_decoder_info[ALSA_ADEC_MAX];
ALSA_RENDERER_INFO_T alsa_renderer_info[ALSA_ADEC_MAX];
ALSA_INPUT_INFO_T alsa_input_info[ALSA_ADEC_MAX];

int alsa_decoder_count;
int alsa_mixer_count;
bool alsa_decoder_ad_on_off;

int ottmode_enable;
int atmos_locking_enable;

bool atmos_decoding_enable = TRUE;
bool input_drop_enable = TRUE;

static int main_audio_index = ALSA_DEFAULT_MAIN_AUDIO_INDEX;
static ALSA_ADC_INFO_T adc_info = { 0, ALSA_ADC_IN_MAX, 1 };

#ifndef SUPPORT_SOUNDBAR
static LX_HDMI_AUDIO_TYPE_T lx_hdmi_audio_type[ALSA_HDMI_IN_MAX] = { };
static ahdmi_type_ext_type_t ahdmi_audio_type[ALSA_HDMI_IN_MAX] = { };
#endif

#ifndef CHIP_TYPE_FPGA
#if defined (INCLUDE_KDRV_HDMI20)
#ifdef INCLUDE_KDRV_HDMI20
#ifdef HAVE_HDMI21
extern int KDRV_HDMI21_HAL_Rx_GetAudioInfo (UINT8 port, LX_HDMI_AUDIO_INFO_T * pHdmiAudioInfo,
    int size);
extern int KDRV_HDMI21_HAL_Rx_GetAudioCopyInfo (UINT8 port,
    LX_HDMI_AUDIO_COPY_T * pHdmiCopyInfo, int size);
extern int KDRV_HDMI21_HAL_Rx_GetAudioACRInfo (UINT8 port,
    LX_HDMI_AUDIO_INFO_ACR_T * pHdmiAudioInfoAcr, int size);
#else
extern int KDRV_HDMI20_HAL_Rx_GetAudioInfo (UINT8 port, LX_HDMI_AUDIO_INFO_T * pHdmiAudioInfo,
    int size);
extern int KDRV_HDMI20_HAL_Rx_GetAudioCopyInfo (UINT8 port,
    LX_HDMI_AUDIO_COPY_T * pHdmiCopyInfo, int size);
extern int KDRV_HDMI20_HAL_Rx_GetAudioAcrInfo (UINT8 port,
    LX_HDMI_AUDIO_INFO_ACR_T * pHdmiAudioInfoAcr, int size);
#endif
#endif
#endif
#endif

static int hdmi_get_audioinfo (UINT8 port, LX_HDMI_AUDIO_INFO_T * pHdmiAudioInfo, int size)
{
#ifndef CHIP_TYPE_FPGA
#if defined (INCLUDE_KDRV_HDMI20)
#ifdef HAVE_HDMI21
    return KDRV_HDMI21_HAL_Rx_GetAudioInfo (port, pHdmiAudioInfo, size);
#else
    return KDRV_HDMI20_HAL_Rx_GetAudioInfo (port, pHdmiAudioInfo, size);
#endif
#else
    return 0;
#endif
#else
    return 0;
#endif
}

static int hdmi_get_audiocopyinfo (UINT8 port, LX_HDMI_AUDIO_COPY_T * pHdmiCopyInfo, int size)
{
#ifndef CHIP_TYPE_FPGA
#ifdef INCLUDE_KDRV_HDMI20
#ifdef HAVE_HDMI21
    return KDRV_HDMI21_HAL_Rx_GetAudioCopyInfo (port, pHdmiCopyInfo, size);
#else
    return KDRV_HDMI20_HAL_Rx_GetAudioCopyInfo (port, pHdmiCopyInfo, size);
#endif
#else
    return 0;
#endif
#else
    return 0;
#endif
}

static int hdmi_get_audioacrinfo (UINT8 port, LX_HDMI_AUDIO_INFO_ACR_T * pHdmiAudioInfoAcr,
    int size)
{
#ifndef CHIP_TYPE_FPGA
#ifdef INCLUDE_KDRV_HDMI20
#ifdef HAVE_HDMI21
    return KDRV_HDMI21_HAL_Rx_GetAudioACRInfo (port, pHdmiAudioInfoAcr, size);
#else
    return KDRV_HDMI20_HAL_Rx_GetAudioAcrInfo (port, pHdmiAudioInfoAcr, size);
#endif
#else
    return 0;
#endif
#else
    return 0;
#endif
}

const char *adec_src_port_type[] = {
    "UNKNOWN", "ATP0", "ATP1", "ADC", "AAD", "HDMI_PORT0", "HDMI_PORT1", "HDMI_PORT2", "HDMI_PORT3",
    "DISPLAY_PORT0", "DISPLAY_PORT1", "SPDIF", "I2S", "HDMI_DEFAULT"
};

const char *dualmono_name[] = {
    "LR", "LL", "RR", "MIX"
};

const char *drc_name[] = {
    "LINE", "RF", "DRC_OFF"
};

const char *downmix_name[] = {
    "LORO", "LTRT"
};

const char *trick_name[] = {
    "NONE", "PAUSE", "NORMAL_PLAY", "SLOW_0.25X", "SLOW_00.50X", "SLOW_0.80X", "FAST_1.20X",
    "FAST_1.50X", "FAST_2.00X"
};

const char *ac4_lang_type_name[] = {
    "ISO639_1", "ISO639_2"
};

const char *ac4_ad_type_name[] = {
    "NONE", "VI (Visually Impaired)", "HI (Hearing Impaired)", "C (Commentary)", "E (Emergency)",
    "VO (Voice Over)"
};

#define ADEC_SRC_CODEC_NAME(id)  {ADEC_SRC_CODEC_##id, #id}

struct str_table
{
    int id;
    const char *name;
};

static const struct str_table _codec_name[] = {
    ADEC_SRC_CODEC_NAME (UNKNOWN),
    ADEC_SRC_CODEC_NAME (PCM),
    ADEC_SRC_CODEC_NAME (AUTO),
    ADEC_SRC_CODEC_NAME (AC3),
    ADEC_SRC_CODEC_NAME (EAC3),
    ADEC_SRC_CODEC_NAME (EAC3_ATMOS),
    ADEC_SRC_CODEC_NAME (AC4),
    ADEC_SRC_CODEC_NAME (AC4_ATMOS),
    ADEC_SRC_CODEC_NAME (MAT),
    ADEC_SRC_CODEC_NAME (MAT_ATMOS),
    ADEC_SRC_CODEC_NAME (TRUEHD),
    ADEC_SRC_CODEC_NAME (TRUEHD_ATMOS),
    ADEC_SRC_CODEC_NAME (AAC),
    ADEC_SRC_CODEC_NAME (HEAAC),
    ADEC_SRC_CODEC_NAME (MPEG),
    ADEC_SRC_CODEC_NAME (MPEG_H),
    ADEC_SRC_CODEC_NAME (DRA),
    ADEC_SRC_CODEC_NAME (DTS),
    ADEC_SRC_CODEC_NAME (DTS_HD_MA),
    ADEC_SRC_CODEC_NAME (DTS_EXPRESS),
    ADEC_SRC_CODEC_NAME (DTS_HD),
    ADEC_SRC_CODEC_NAME (DTS_X_P1),
    ADEC_SRC_CODEC_NAME (DTS_X_P2),
    ADEC_SRC_CODEC_NAME (SIF),
    ADEC_SRC_CODEC_NAME (SIF_BTSC),
    ADEC_SRC_CODEC_NAME (SIF_A2),
};

static const char *_get_codec_name (adec_src_codec_ext_type_t codec)
{
    int i;

    for (i = 0; i < sizeof (_codec_name) / sizeof (_codec_name[0]); i++)
    {
        if (_codec_name[i].id == codec)
            return _codec_name[i].name;
    }
    return _codec_name[0].name;
}

#define LX_HDMI_AUDIO_NAME(id) {LX_HDMI_AUDIO_##id, #id}

static const struct str_table _hdmi_lxcodec_name[] = {
    LX_HDMI_AUDIO_NAME (DVI),
    LX_HDMI_AUDIO_NAME (NO_AUDIO),
    LX_HDMI_AUDIO_NAME (PCM),
    LX_HDMI_AUDIO_NAME (AC3),
    LX_HDMI_AUDIO_NAME (DTS),
    LX_HDMI_AUDIO_NAME (AAC),
    LX_HDMI_AUDIO_NAME (DEFAULT),
    LX_HDMI_AUDIO_NAME (MPEG),
    LX_HDMI_AUDIO_NAME (DTS_HD_MA),
    LX_HDMI_AUDIO_NAME (DTS_EXPRESS),
    LX_HDMI_AUDIO_NAME (DTS_CD),
    LX_HDMI_AUDIO_NAME (EAC3),
    LX_HDMI_AUDIO_NAME (EAC3_ATMOS),
    LX_HDMI_AUDIO_NAME (MAT),
    LX_HDMI_AUDIO_NAME (MAT_ATMOS),
    LX_HDMI_AUDIO_NAME (TRUE_HD),
    LX_HDMI_AUDIO_NAME (TRUE_HD_ATMOS),
    LX_HDMI_AUDIO_NAME (AC3_IEC60958),
    LX_HDMI_AUDIO_NAME (EAC3_IEC60958),
    LX_HDMI_AUDIO_NAME (DTS_HD),
    LX_HDMI_AUDIO_NAME (DTS_HD_HRA),
    LX_HDMI_AUDIO_NAME (UNKNOWN_AC3),
    LX_HDMI_AUDIO_NAME (UNKNOWN_DTS),
    LX_HDMI_AUDIO_NAME (UNKNOWN_AAC),
    LX_HDMI_AUDIO_NAME (UNKNOWN_MPEG),
    LX_HDMI_AUDIO_NAME (UNKNOWN_EAC3),
    LX_HDMI_AUDIO_NAME (UNKNOWN_MAT),
    LX_HDMI_AUDIO_NAME (UNKNOWN_DTS_HD),
    LX_HDMI_AUDIO_NAME (UNKNOWN_DTS_HD_HRA),
};

#ifndef SUPPORT_SOUNDBAR
static const char *_get_hdmi_lxcodec_name (LX_HDMI_AUDIO_TYPE_T codec)
{
    int i;

    for (i = 0; i < sizeof (_hdmi_lxcodec_name) / sizeof (_hdmi_lxcodec_name[0]); i++)
    {
        if (_hdmi_lxcodec_name[i].id == codec)
            return _hdmi_lxcodec_name[i].name;
    }
    return _hdmi_lxcodec_name[0].name;
}
#endif

static unsigned char lang_name[4];
static unsigned char *_get_ac4_lang_name (unsigned int lang)
{
    lang_name[3] = '\0';
    lang_name[2] = (lang >> 8) & 0xFF;
    lang_name[1] = (lang >> 16) & 0xFF;
    lang_name[0] = (lang >> 24) & 0xFF;

    return lang_name;
}

static adec_src_codec_ext_type_t decoder_get_source_codec (adec_src_codec_ext_type_t codec,
    struct decoded_info *info)
{
    adec_src_codec_ext_type_t source_codec = ADEC_SRC_CODEC_UNKNOWN;

    if (info->codec == AUDIO_DECODER_CODEC_UNKNOWN)
        return source_codec;

#ifdef SUPPORT_SOUNDBAR
    if (codec == ADEC_SRC_CODEC_AUTO)
    {
        switch (info->codec)
        {
            case AUDIO_DECODER_CODEC_PCM:
                codec = ADEC_SRC_CODEC_PCM;
                break;
            case AUDIO_DECODER_CODEC_AC3:
                codec = ADEC_SRC_CODEC_AC3;
                break;
            case AUDIO_DECODER_CODEC_AAC:
                codec = ADEC_SRC_CODEC_AAC;
                break;
            case AUDIO_DECODER_CODEC_MAT:
                codec = ADEC_SRC_CODEC_MAT;
                break;
            default:
                codec = ADEC_SRC_CODEC_PCM;
                break;
        };
    }
#endif

    switch (codec)
    {
        case ADEC_SRC_CODEC_PCM:
        case ADEC_SRC_CODEC_SIF:
        case ADEC_SRC_CODEC_SIF_BTSC:
        case ADEC_SRC_CODEC_SIF_A2:
            source_codec = ADEC_SRC_CODEC_PCM;
            break;
        case ADEC_SRC_CODEC_AC3:
        case ADEC_SRC_CODEC_EAC3_ATMOS:
        case ADEC_SRC_CODEC_EAC3:
            if (info->atmos)
                source_codec = ADEC_SRC_CODEC_EAC3_ATMOS;
            else if (info->eac3)
                source_codec = ADEC_SRC_CODEC_EAC3;
            else
                source_codec = ADEC_SRC_CODEC_AC3;
            break;

        case ADEC_SRC_CODEC_AC4_ATMOS:
        case ADEC_SRC_CODEC_AC4:
            if (info->atmos)
                source_codec = ADEC_SRC_CODEC_AC4_ATMOS;
            else
                source_codec = ADEC_SRC_CODEC_AC4;
            break;

        case ADEC_SRC_CODEC_MAT_ATMOS:
        case ADEC_SRC_CODEC_MAT:
        case ADEC_SRC_CODEC_TRUEHD_ATMOS:
        case ADEC_SRC_CODEC_TRUEHD:
            if (info->truehd)
            {
                if (info->atmos)
                    source_codec = ADEC_SRC_CODEC_TRUEHD_ATMOS;
                else
                    source_codec = ADEC_SRC_CODEC_TRUEHD;
            }
            else
            {
                if (info->atmos)
                    source_codec = ADEC_SRC_CODEC_MAT_ATMOS;
                else
                    source_codec = ADEC_SRC_CODEC_MAT;
            }
            break;

        case ADEC_SRC_CODEC_AAC:
        case ADEC_SRC_CODEC_HEAAC:
            if (info->version == AAC_CODEC_VERSION_AAC)
                source_codec = ADEC_SRC_CODEC_AAC;
            else
                source_codec = ADEC_SRC_CODEC_HEAAC;
            break;

        case ADEC_SRC_CODEC_MPEG:
            source_codec = ADEC_SRC_CODEC_MPEG;
            break;

        case ADEC_SRC_CODEC_MPEG_H:
            source_codec = ADEC_SRC_CODEC_MPEG_H;
            break;

        case ADEC_SRC_CODEC_DRA:
            source_codec = ADEC_SRC_CODEC_DRA;
            break;

#ifdef SUPPORT_DTSX
        case ADEC_SRC_CODEC_DTS:
        case ADEC_SRC_CODEC_DTS_HD_MA:
        case ADEC_SRC_CODEC_DTS_EXPRESS:
        case ADEC_SRC_CODEC_DTS_HD:
        case ADEC_SRC_CODEC_DTS_X_P1:
        case ADEC_SRC_CODEC_DTS_X_P2:
            switch (info->dts_detail)
            {
                default:
                case AUDIO_DECODER_DTS_DETAIL_DTS:
                    source_codec = ADEC_SRC_CODEC_DTS;
                    break;
                case AUDIO_DECODER_DTS_DETAIL_DTS_HD:
                    source_codec = ADEC_SRC_CODEC_DTS_HD;
                    break;
                case AUDIO_DECODER_DTS_DETAIL_DTS_EXPRESS:
                    source_codec = ADEC_SRC_CODEC_DTS_EXPRESS;
                    break;
                case AUDIO_DECODER_DTS_DETAIL_DTS_HD_MA:
                    source_codec = ADEC_SRC_CODEC_DTS_HD_MA;
                    break;
                case AUDIO_DECODER_DTS_DETAIL_DTS_X_1:
                    source_codec = ADEC_SRC_CODEC_DTS_X_P1;
                    break;
                case AUDIO_DECODER_DTS_DETAIL_DTS_X_2:
                    source_codec = ADEC_SRC_CODEC_DTS_X_P2;
                    break;
                case AUDIO_DECODER_DTS_DETAIL_NONE:
                    source_codec = ADEC_SRC_CODEC_UNKNOWN;
                    break;
            }
            break;
#endif

        default:
            source_codec = ADEC_SRC_CODEC_UNKNOWN;
            break;
    }

    return source_codec;
}

static enum audio_decoder_codec decoder_convert_codec (adec_src_codec_ext_type_t codec)
{
    enum audio_decoder_codec decoder_codec;

    switch (codec)
    {
        case ADEC_SRC_CODEC_PCM:
        case ADEC_SRC_CODEC_SIF:
        case ADEC_SRC_CODEC_SIF_BTSC:
        case ADEC_SRC_CODEC_SIF_A2:
            decoder_codec = AUDIO_DECODER_CODEC_PCM;
            break;

        case ADEC_SRC_CODEC_AC3:
            decoder_codec = AUDIO_DECODER_CODEC_AC3;
            break;
        case ADEC_SRC_CODEC_EAC3_ATMOS:
        case ADEC_SRC_CODEC_EAC3:
            decoder_codec = AUDIO_DECODER_CODEC_EAC3;
            break;

        case ADEC_SRC_CODEC_AC4_ATMOS:
        case ADEC_SRC_CODEC_AC4:
            decoder_codec = AUDIO_DECODER_CODEC_AC4;
            break;

        case ADEC_SRC_CODEC_MAT_ATMOS:
        case ADEC_SRC_CODEC_MAT:
        case ADEC_SRC_CODEC_TRUEHD_ATMOS:
        case ADEC_SRC_CODEC_TRUEHD:
            decoder_codec = AUDIO_DECODER_CODEC_MAT;
            break;

        case ADEC_SRC_CODEC_AAC:
        case ADEC_SRC_CODEC_HEAAC:
            decoder_codec = AUDIO_DECODER_CODEC_AAC;
            break;

        case ADEC_SRC_CODEC_MPEG:
            decoder_codec = AUDIO_DECODER_CODEC_MP3;
            break;

        case ADEC_SRC_CODEC_MPEG_H:
            decoder_codec = AUDIO_DECODER_CODEC_MPEG_H;
            break;

        case ADEC_SRC_CODEC_DRA:
            decoder_codec = AUDIO_DECODER_CODEC_DRA;
            break;

#ifdef SUPPORT_DTSX
        case ADEC_SRC_CODEC_DTS:
        case ADEC_SRC_CODEC_DTS_HD_MA:
        case ADEC_SRC_CODEC_DTS_EXPRESS:
        case ADEC_SRC_CODEC_DTS_HD:
        case ADEC_SRC_CODEC_DTS_X_P1:
        case ADEC_SRC_CODEC_DTS_X_P2:
            decoder_codec = AUDIO_DECODER_CODEC_DTS;
            break;
#endif

        case ADEC_SRC_CODEC_AUTO:
            decoder_codec = AUDIO_DECODER_CODEC_AUTO;
            break;

        default:
            decoder_codec = AUDIO_DECODER_CODEC_AC3;
            break;
    }

    return decoder_codec;
}

static void _alsa_decoder_convert_input (adec_src_port_index_ext_type_t input,
    enum input_type *pInput_type, int *pIndex, bool *pBypass)
{
    enum input_type input_type;
    int index = 0;
    bool bypass = false;

    switch (input)
    {
        case ADEC_SRC_ATP0:
        case ADEC_SRC_ATP1:
            input_type = INPUT_TP;
            index = input - ADEC_SRC_ATP0;
            break;
        case ADEC_SRC_ADC:
            input_type = INPUT_ADC;
            break;
        case ADEC_SRC_AAD:
            input_type = INPUT_SIF;
            break;
        case ADEC_SRC_HDMI_DEFAULT:
            input_type = INPUT_HDMI;
            index = 0;
            bypass = true;
            break;
        case ADEC_SRC_HDMI_PORT0:
        case ADEC_SRC_HDMI_PORT1:
        case ADEC_SRC_HDMI_PORT2:
        case ADEC_SRC_HDMI_PORT3:
            input_type = INPUT_HDMI;
            index = input - ADEC_SRC_HDMI_PORT0;
            bypass = true;
            break;
#ifdef SUPPORT_SOUNDBAR
        case ADEC_SRC_I2S:
            input_type = INPUT_I2S;
            break;
#endif
        case ADEC_SRC_DISPLAYPORT0:
        case ADEC_SRC_DISPLAYPORT1:
        case ADEC_SRC_SPDIF:
        default:
            input_type = INPUT_MAX;
            break;
    }

    *pInput_type = input_type;
    *pIndex = index;
    *pBypass = bypass;
}

static enum audio_decoder_input decoder_convert_input (adec_src_port_index_ext_type_t input)
{
    enum audio_decoder_input input_type = AUDIO_DECODER_INPUT_NONE;

    switch (input)
    {
        case ADEC_SRC_ATP0:
            input_type = AUDIO_DECODER_INPUT_TP0;
            break;
        case ADEC_SRC_ATP1:
            input_type = AUDIO_DECODER_INPUT_TP1;
            break;
        case ADEC_SRC_ADC:
            input_type = AUDIO_DECODER_INPUT_ADC;
            break;
        case ADEC_SRC_AAD:
            input_type = AUDIO_DECODER_INPUT_SIF;
            break;
        case ADEC_SRC_HDMI_PORT0:
            input_type = AUDIO_DECODER_INPUT_HDMI0;
            break;
        case ADEC_SRC_HDMI_PORT1:
            input_type = AUDIO_DECODER_INPUT_HDMI1;
            break;
        case ADEC_SRC_HDMI_PORT2:
            input_type = AUDIO_DECODER_INPUT_HDMI2;
            break;
        case ADEC_SRC_HDMI_PORT3:
            input_type = AUDIO_DECODER_INPUT_HDMI3;
            break;
        case ADEC_SRC_HDMI_DEFAULT:
            input_type = AUDIO_DECODER_INPUT_HDMI0;
            break;
        case ADEC_SRC_I2S:
            input_type = AUDIO_DECODER_INPUT_I2S;
            break;
        case ADEC_SRC_DISPLAYPORT0:
        case ADEC_SRC_DISPLAYPORT1:
        case ADEC_SRC_SPDIF:
        default:
            input_type = AUDIO_DECODER_INPUT_NONE;
            break;
    }

    return input_type;
}

static int decoder_convert_trickmode (adec_trick_mode_ext_type_t trick_mode)
{
    int value = 1000;

    switch (trick_mode)
    {
        case ADEC_TRICK_NORMAL_PLAY:
            value = 1000;
            break;

        case ADEC_TRICK_SLOW_MOTION_OP25X:
            value = 250;
            break;

        case ADEC_TRICK_SLOW_MOTION_OP50X:
            value = 500;
            break;

        case ADEC_TRICK_SLOW_MOTION_OP80X:
            value = 800;
            break;

        case ADEC_TRICK_FAST_FORWARD_1P20X:
            value = 1200;
            break;

        case ADEC_TRICK_FAST_FORWARD_1P50X:
            value = 1500;
            break;

        case ADEC_TRICK_FAST_FORWARD_2P00X:
            value = 2000;
            break;

        default:
            value = 1000;
    }

    return value;
}

int decoder_enable_atmos_decoding (bool enable)
{
    // ATMOS enable/disable 기능은 성능 확인하면서 추후 업데이트 할 예정
    int index = main_audio_index;
    ALSA_DECODER_INFO_T *dec = NULL;
    int ret = -1;

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder .\n");
        goto exit;
    }

    if (!dec->is_started)
    {
        error ("audio decoder is not started, index %d .\n", index);
        goto exit;

    }

    atmos_decoding_enable = enable;

    info ("decoder_enable_atmos_decoding %d, main_audio %d .\n", enable, index);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static enum pcmren_downmix_mode decoder_get_pcmren_downmix_mode (adec_downmix_mode_ext_type_t
    dec_dmx_mode)
{
    if (dec_dmx_mode == ADEC_LORO_MODE)
        return PCMREN_DOWNMIX_LORO_MODE;
    else if (dec_dmx_mode == ADEC_LTRT_MODE)
        return PCMREN_DOWNMIX_LTRT_MODE;

    return PCMREN_DOWNMIX_LTRT_MODE;
}

static void decoder_set_main_decoder_property (int index)
{
    ALSA_DECODER_INFO_T *dec = &alsa_decoder_info[index];
    bool sub_decoder = false;

    if (!dec->dec_info)
    {
        return;
    }

    // set sub decoder proprty (audio description: ON & downmix: OFF)
    if (alsa_decoder_ad_on_off && !dec->downmix_2ch)
    {
        if ((main_audio_index != ALSA_DEFAULT_MAIN_AUDIO_INDEX) && (main_audio_index != index))
        {
            sub_decoder = true;
            info ("set sub-decoder, decoder %d \n", index);
        }
    }

    switch (dec->codec)
    {
        case ADEC_SRC_CODEC_AAC:
        case ADEC_SRC_CODEC_HEAAC:
        case ADEC_SRC_CODEC_AC3:
        case ADEC_SRC_CODEC_EAC3:
        case ADEC_SRC_CODEC_MPEG:
#ifdef SUPPORT_DTSX
        case ADEC_SRC_CODEC_DTS:
        case ADEC_SRC_CODEC_DTS_HD_MA:
        case ADEC_SRC_CODEC_DTS_EXPRESS:
        case ADEC_SRC_CODEC_DTS_HD:
        case ADEC_SRC_CODEC_DTS_X_P1:
        case ADEC_SRC_CODEC_DTS_X_P2:
#endif
            decoder_set_param (dec->dec_info, "sub-decoder=%d", sub_decoder);
            break;
        case ADEC_SRC_CODEC_AC4:
            decoder_set_param (dec->dec_info, "main-decoder=%d", !sub_decoder);
            break;
        default:
            break;
    }
}

#ifndef SUPPORT_SOUNDBAR
static void decoder_set_metadata_type (int index)
{
    ALSA_DECODER_INFO_T *dec = &alsa_decoder_info[index];
    unsigned int metadata_type;
    bool is_dolby = false;

    // 0: DD/DD+, 1: AAC, 2: AC4, 3: MAT, 4: ETC (EXTERNAL_PCM)

    switch (dec->codec)
    {
        case ADEC_SRC_CODEC_AC3:
        case ADEC_SRC_CODEC_EAC3_ATMOS:
        case ADEC_SRC_CODEC_EAC3:
            metadata_type = 0;
            is_dolby = true;
            break;

        case ADEC_SRC_CODEC_AAC:
        case ADEC_SRC_CODEC_HEAAC:
            metadata_type = 1;
            is_dolby = true;
            break;

        case ADEC_SRC_CODEC_AC4_ATMOS:
        case ADEC_SRC_CODEC_AC4:
            metadata_type = 2;
            is_dolby = true;
            break;

        case ADEC_SRC_CODEC_MAT_ATMOS:
        case ADEC_SRC_CODEC_MAT:
        case ADEC_SRC_CODEC_TRUEHD_ATMOS:
        case ADEC_SRC_CODEC_TRUEHD:
            metadata_type = 3;
            is_dolby = true;
            break;

        default:
            metadata_type = 4;
            is_dolby = false;
            break;
    }

    if (is_dolby)
    {
        struct aud_block_info *mixer = bm_get_block_info_by_index ("mixer", 0);

        // 0: DD/DD+, 1: AAC, 2: AC4, 3: MAT, 4: ETC (EXTERNAL_PCM)
        if (mixer)
            mixer_set_pcmren_metadata_type (mixer, metadata_type);
    }
}
#endif

static void decoder_set_thread_prio (void)
{
    struct aud_block_info *dec_info;
    int i;

    for (i = 0; i < ALSA_ADEC_MAX; i++)
    {
        decoder_acquire_lock ();
        dec_info = bm_get_block_info_by_index ("decoder", i);
        if (dec_info)
            decoder_set_prio (dec_info);
        decoder_release_lock ();
    }
}


static void decoder_set_input_drop (int index, bool enable)
{
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_INPUT_INFO_T *inp = NULL;

    if (index >= ALSA_ADEC_MAX)
    {
        info ("invalid decoder index %d, so do not set input drop\n", index);
        return;
    }

    dec = &alsa_decoder_info[index];
    inp = &alsa_input_info[index];

    if (!dec->is_open)
    {
        info ("can not find audio decoder, index %d .\n", index);
        return;
    }

    if (!inp->input_info)
    {
        info ("decoder is not connected yet .\n");
        return;
    }

    // input drop disable
    if (!enable)
    {
        input_drop_data (inp->input_info, false);
    }
    // input drop enable
    else
    {
        if (dec->is_main_dec)
        {
            if ((main_audio_index != ALSA_DEFAULT_MAIN_AUDIO_INDEX) && inp->input_info)
            {
                if (input_get_type (inp->input_info) == INPUT_TP
                    || input_get_type (inp->input_info) == INPUT_HDMI)
                {
                    if (input_is_drop_data (inp->input_info))
                    {
                        ALSA_RENDERER_INFO_T *ren = &alsa_renderer_info[index];

                        if (ren->is_open)
                            renderer_lipsync_clear_idle (ren->ren_info);

                        input_stop (inp->input_info);
                        input_start (inp->input_info);

                        if (ren->is_open)
                            renderer_lipsync_set_idle (ren->ren_info);

                        noti ("restart input, drop on to off \n");
                    }
                }
                input_drop_data (inp->input_info, false);
                noti ("main adec:%d, drop : false\n", index);
            }
        }
        else
        {
            if (inp->input_info)
            {
                if (input_get_type (inp->input_info) == INPUT_SIF
                    && main_audio_index < ALSA_ADEC_MAX)
                {
                    ALSA_INPUT_INFO_T *inp_main = &alsa_input_info[main_audio_index];

                    if (atmos_decoding_enable == true
                        && acapture_is_encoder_connected () == false
                        && (inp_main->input_info != NULL
                            && input_get_type (inp_main->input_info) != INPUT_SIF)
                        && dec->downmix_2ch == false)
                    {
                        noti ("INPUT_SIF is dropped by atmos_decoding_enable.(sub adec:%d)\n",
                            index);
                        input_drop_data (inp->input_info, true);
                    }
                }
                else
                {
                    if (alsa_decoder_ad_on_off == false && dec->downmix_2ch == false)
                    {
                        input_drop_data (inp->input_info, true);
                        noti ("sub audio(%d) is dropped by alsa_decoder_ad_on_off(%d).\n",
                            index, alsa_decoder_ad_on_off);
                    }
                }
            }
        }
    }

    return;
}


int decoder_set_main_audio_index (int index)
{
    int i;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_INPUT_INFO_T *inp = NULL;
#ifndef SUPPORT_SOUNDBAR
    struct aud_block_info *mixer = bm_get_block_info_by_index ("mixer", 0);
#endif

    ALSADEC_LOCK ();

    if (main_audio_index != index)
    {
        for (i = 0; i < ALSA_ADEC_MAX; i++)
        {
            dec = &alsa_decoder_info[i];
            inp = &alsa_input_info[i];

            if (i == index)
            {
                dec->is_main_dec = true;

                if (dec->is_started)
                {
                    decoder_set_input_drop (i, input_drop_enable);
                }
                else
                    noti ("main adec:%d, is_started : %d\n", i, dec->is_started);

#ifndef SUPPORT_SOUNDBAR
                if (mixer)
                {
                    unsigned int dec_dmx_mode = decoder_get_downmix_mode (i);
                    mixer_set_pcmren_drc_mode (mixer, decoder_get_drc_mode (i));
                    mixer_set_pcmren_downmix_mode (mixer,
                        decoder_get_pcmren_downmix_mode (dec_dmx_mode));
                    decoder_set_metadata_type (i);
                }
#endif
            }
            else
            {
                dec->is_main_dec = false;

#if (defined INCLUDE_COMMERCIAL_PLATFORM || defined INCLUDE_SIGNAGE_PLATFORM)
                noti ("sub audio(%d) is not dropped in ID signage model.\n", i);
#else
                decoder_set_input_drop (i, input_drop_enable);
#endif
            }

            decoder_set_main_decoder_property (i);
        }

        noti ("main audio index is changed. %d -> %d .\n", main_audio_index, index);

        main_audio_index = index;
    }

    // notify to block manager
    bm_set_main_audio_decoder_index (main_audio_index);

    // set decoder priority
    decoder_set_thread_prio ();

    ALSADEC_UNLOCK ();

    return 0;
}

adec_dolbydrc_mode_ext_type_t decoder_get_drc_mode (int index)
{
    ALSA_DECODER_INFO_T *dec = &alsa_decoder_info[index];
    ALSA_INPUT_INFO_T *inp = &alsa_input_info[index];
    struct aud_block_info *dec_block = bm_get_block_info_by_index ("decoder", index);

    adec_src_codec_ext_type_t codec;
    adec_src_port_index_ext_type_t input;
    adec_dolbydrc_mode_ext_type_t drc;

    enum input_type input_type = INPUT_MAX;

    if (inp->input_info)
        input_type = input_get_type (inp->input_info);

    codec = dec->codec;
    input = dec->input;

    if (dec_block)
        drc = (adec_dolbydrc_mode_ext_type_t) decoder_get_dolby_drc_mode (dec_block);
    else
        drc = dec->drc;

    if (index < ALSA_ADEC_MAX)
    {
        if (input_type == INPUT_HDMI)
        {
            drc = ADEC_DOLBY_LINE_MODE;
        }
        else
        {
            if (dec->codec == ADEC_SRC_CODEC_MPEG)
                drc = ADEC_DOLBY_LINE_MODE;
        }
    }
    else
    {
        drc = ADEC_DOLBY_LINE_MODE;
    }

    return drc;
}

adec_downmix_mode_ext_type_t decoder_get_downmix_mode (int index)
{
    ALSA_DECODER_INFO_T *dec = &alsa_decoder_info[index];
    ALSA_INPUT_INFO_T *inp = &alsa_input_info[index];

    adec_src_codec_ext_type_t codec;
    adec_src_port_index_ext_type_t input;
    adec_downmix_mode_ext_type_t downmix = dec->downmix;

    enum input_type input_type = INPUT_MAX;

    if (inp->input_info)
        input_type = input_get_type (inp->input_info);

    codec = dec->codec;
    input = dec->input;
    downmix = dec->downmix;

    if (index < ALSA_ADEC_MAX)
    {
        if (input_type == INPUT_HDMI)
        {
            switch (codec)
            {
                case ADEC_SRC_CODEC_AC3:
                case ADEC_SRC_CODEC_EAC3:
                case ADEC_SRC_CODEC_EAC3_ATMOS:
                case ADEC_SRC_CODEC_AC4:
                case ADEC_SRC_CODEC_AC4_ATMOS:
                    downmix = ADEC_LTRT_MODE;
                    break;
                case ADEC_SRC_CODEC_AAC:
                case ADEC_SRC_CODEC_HEAAC:
                    downmix = ADEC_LORO_MODE;
                    break;
                default:
                    downmix = ADEC_LORO_MODE;
                    break;
            }
        }
    }
    else
    {
        downmix = ADEC_LORO_MODE;
    }

    return downmix;
}

#ifdef ENABLE_DECODER_OUTPUT_MODE
int decoder_set_output_mode (int index, enum DECODER_OUTPUT_MODE output_mode, bool enable)
{
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_DECODER_INFO_T *dec = NULL;
    int ret = -1;

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return ret;
    }

    inp = &alsa_input_info[index];
    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if ((output_mode == DECODER_OUTPUT_MAIN && dec->hdmi_output_main == enable)
        || (output_mode == DECODER_OUTPUT_SUB && dec->hdmi_output_sub == enable))
    {
        info ("SAME output_mode %d, enable %d .\n", output_mode, enable);
        goto exit;
    }

    if (output_mode == DECODER_OUTPUT_MAIN)
        dec->hdmi_output_main = enable;
    else if (output_mode == DECODER_OUTPUT_SUB)
        dec->hdmi_output_sub = enable;

    if (!dec->is_open)
    {
#ifdef SUPPORT_DTSX
        // media scenario dts decoder property (bitstream-passthrough) setting
        struct aud_block_info *decoder = bm_get_block_info_by_index ("decoder", index);

        if (decoder)
        {
            if (dec->hdmi_output_sub)
                decoder_set_dtsx_bitstream_passthrough (decoder, true);
            else
                decoder_set_dtsx_bitstream_passthrough (decoder, false);

            info ("media scenario decoder property setting.(output_sub = %d)\n",
                dec->hdmi_output_sub);
            ret = 0;
            goto exit;
        }
        error ("can not find audio decoder, index %d .\n", index);
#endif
        goto exit;
    }

    if (inp->input_info == NULL)
    {
        error ("audio decoder is not connected to input, index %d .\n", index);
        goto exit;
    }

    if ((dec->input >= ADEC_SRC_HDMI_PORT0 && dec->input <= ADEC_SRC_HDMI_PORT3)
        || (dec->input == ADEC_SRC_HDMI_DEFAULT))
    {
        if (dec->hdmi_output_main && dec->hdmi_output_sub)
            input_set_hdmi_bypass (inp->input_info, false, 0);
        else if (!dec->hdmi_output_main && dec->hdmi_output_sub)
            input_set_hdmi_bypass (inp->input_info, true, 0);
        else                    //if (dec->hdmi_output_main)
            input_set_hdmi_bypass (inp->input_info, true, 1);
    }

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}
#else
int decoder_set_output_drop (int index, enum DECODER_OUTPUT_DROP output_drop)
{
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_DECODER_INFO_T *dec = NULL;
    int ret = -1;

    inp = &alsa_input_info[index];
    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    dec->output_drop = output_drop;

    if (!dec->is_open)
    {
#ifdef SUPPORT_DTSX
        // media scenario dts decoder property (bitstream-passthrough) setting
        struct aud_block_info *decoder = bm_get_block_info_by_index ("decoder", index);

        if (decoder)
        {
            if (output_drop == DECODER_OUTPUT_DROP_MAIN || output_drop == DECODER_OUTPUT_DROP_NONE)
                decoder_set_dtsx_bitstream_passthrough (decoder, true);
            else
                decoder_set_dtsx_bitstream_passthrough (decoder, false);

            info ("media scenario decoder property setting. \n");
            ret = 0;
            goto exit;
        }
        error ("can not find audio decoder, index %d .\n", index);
#endif
        goto exit;
    }

    if (inp->input_info == NULL)
    {
        error ("audio decoder is not connected to input, index %d .\n", index);
        goto exit;
    }

    if ((dec->input >= ADEC_SRC_HDMI_PORT0 && dec->input <= ADEC_SRC_HDMI_PORT3)
        || (dec->input == ADEC_SRC_HDMI_DEFAULT))
    {
        if (output_drop == DECODER_OUTPUT_DROP_NONE)
            input_set_hdmi_bypass (inp->input_info, false, 0);
        else if (output_drop == DECODER_OUTPUT_DROP_MAIN)
            input_set_hdmi_bypass (inp->input_info, true, 0);
        else                    //if (output_drop == DECODER_OUTPUT_DROP_SUB)
            input_set_hdmi_bypass (inp->input_info, true, 1);
    }

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}
#endif

int decoder_set_multi_pcm_out (int index, bool enable)
{
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_DECODER_INFO_T *dec = NULL;
    int ret = -1;

    if (index < 0)
    {
        error ("invalid, index %d .\n", index);
        return -1;
    }

    inp = &alsa_input_info[index];
    dec = &alsa_decoder_info[index];

    dec->hdmi_multi_pcm_out = enable;

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (inp->input_info == NULL)
    {
        error ("audio decoder is not connected to input, index %d .\n", index);
        goto exit;
    }

    if ((dec->input >= ADEC_SRC_HDMI_PORT0 && dec->input <= ADEC_SRC_HDMI_PORT3)
        || (dec->input == ADEC_SRC_HDMI_DEFAULT))
    {
        input_set_hdmi_multi_pcm_out (inp->input_info, enable);
    }

    ret = 0;
  exit:
    return ret;
}

int decoder_set_downmix (int index, bool enable)
{
    int i;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_INPUT_INFO_T *inp = NULL;

    if (index < 0 || index >= ALSA_ADEC_MAX)
    {
        error ("invalid, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    for (i = 0; i < ALSA_ADEC_MAX; i++)
    {
        dec = &alsa_decoder_info[i];
        inp = &alsa_input_info[i];

        if (!dec->is_open)
        {
            struct aud_block_info *decoder = bm_get_block_info_by_index ("decoder", index);

            if (decoder)
            {
                decoder_set_param (decoder, "downmix-out-ch=%d", enable);
                if (enable)
                    decoder_set_param (decoder, "sub-decoder=%d", false);
            }
        }
        else
        {
            if (dec->dec_info)
            {
                decoder_set_param (dec->dec_info, "downmix-out-ch=%d", enable);
                if (enable)
                {
                    if (dec->codec == ADEC_SRC_CODEC_AC4)
                        decoder_set_param (dec->dec_info, "main-decoder=%d", true);
                    else
                        decoder_set_param (dec->dec_info, "sub-decoder=%d", false);
                }
            }
        }

        if (i != main_audio_index)
        {
            if (inp->input_info)
            {
                input_drop_data (inp->input_info, false);
            }
        }
    }

    dec->downmix_2ch = enable;

    info ("decoder_set_downmix index %d enable %d .\n", index, enable);

    return 0;
}

#ifdef SUPPORT_SOUNDBAR
bool decoder_sb_codec_supported (adec_src_codec_ext_type_t codec)
{
    bool ret = false;

    switch (codec)
    {
        case ADEC_SRC_CODEC_PCM:
        case ADEC_SRC_CODEC_AC3:
        case ADEC_SRC_CODEC_EAC3_ATMOS:
        case ADEC_SRC_CODEC_EAC3:
        case ADEC_SRC_CODEC_MAT_ATMOS:
        case ADEC_SRC_CODEC_MAT:
        case ADEC_SRC_CODEC_TRUEHD_ATMOS:
        case ADEC_SRC_CODEC_TRUEHD:
        case ADEC_SRC_CODEC_AAC:
        case ADEC_SRC_CODEC_HEAAC:
#ifdef SUPPORT_DTSX
        case ADEC_SRC_CODEC_DTS:
        case ADEC_SRC_CODEC_DTS_HD_MA:
        case ADEC_SRC_CODEC_DTS_EXPRESS:
        case ADEC_SRC_CODEC_DTS_HD:
        case ADEC_SRC_CODEC_DTS_X_P1:
        case ADEC_SRC_CODEC_DTS_X_P2:
#endif
        case ADEC_SRC_CODEC_AUTO:
            ret = true;
            break;

        default:
            ret = false;
            break;
    }

    return ret;
}
#endif

static void alsa_decoder_init (int index)
{
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;

    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    memset (dec, 0x0, sizeof (ALSA_DECODER_INFO_T));
    memset (ren, 0x0, sizeof (ALSA_RENDERER_INFO_T));

    dec->is_open = FALSE;
    dec->codec = ADEC_SRC_CODEC_UNKNOWN;
    dec->is_main_dec = FALSE;
    dec->input = ADEC_SRC_UNKNOWN;
    dec->prev_input = ADEC_SRC_UNKNOWN;
    dec->src_format = ADEC_SRC_CODEC_UNKNOWN;
    dec->first_lang.iso_type = ADEC_AC4_LANG_CODE_ISO639_1;
    dec->first_lang.lang = 0x0;
    dec->second_lang.iso_type = ADEC_AC4_LANG_CODE_ISO639_1;
    dec->second_lang.lang = 0x0;
    dec->ad_type = ADEC_AC4_AD_TYPE_VI;
    dec->prio_ad_type = FALSE;
    dec->ac4_group_index = ALSA_GROUP_INDEX_MAX;
    dec->dialog_gain = 0x0;
    dec->dualmono_mode = ADEC_DUALMONO_MODE_LR;
#ifdef SUPPORT_SOUNDBAR
    dec->drc = ADEC_DOLBY_DRC_OFF;
#else
    dec->drc = ADEC_DOLBY_LINE_MODE;
#endif
    dec->downmix = ADEC_LORO_MODE;
    dec->ac4_ad_on_off = 0;
    dec->default_prl = ALSA_INVALID_DEFAULT_PRL;
    dec->associate_audio_volume = 0;
#ifdef ENABLE_DECODER_OUTPUT_MODE
    dec->hdmi_output_main = true;
    dec->hdmi_output_sub = false;
#else
    dec->output_drop = DECODER_OUTPUT_DROP_SUB;
#endif
    dec->hdmi_multi_pcm_out = false;

#ifdef SUPPORT_SOUNDBAR
    dec->i2s_hdmi_type = 0;
    dec->i2s_hdmi_ch = 0;
    dec->i2s_hdmi_freq = 0;
    dec->i2s_port_count = 4;
#endif

    ren->is_open = FALSE;
    ren->sync = TRUE;
    ren->trick = ADEC_TRICK_NONE;
    ren->master_syncmode = FALSE;
    ren->offset = 150;
}

static int alsa_decoder_open_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_open_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = TRUE;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_open_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_open (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
#ifdef SUPPORT_SOUNDBAR
    int opened_index = -1;
#endif
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    ablind_post ("Auto " ADEC_OPEN, 1, index);

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (dec->is_open || (bm_get_block_info_by_index ("decoder", index) != NULL))
    {
        error ("alsa_decoder_open failed. already used index %d .\n", index);
        goto exit;
    }

#ifdef SUPPORT_SOUNDBAR
    opened_index = decoder_get_already_opened_index ();
    if (opened_index >= 0)
    {
        error ("alsa_decoder_open failed. already used index %d .\n", opened_index);
        goto exit;
    }
#endif

    alsa_decoder_init (index);

    dec->dec_info = bm_create_block ("decoder", index);
    ren->ren_info = bm_create_block ("renderer", index);
    renderer_add_queue (ren->ren_info, false);

    dec->is_open = TRUE;
    ren->is_open = TRUE;

    info ("alsa_decoder_open index %d .\n", index);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_close_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_close_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (!dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = TRUE;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_close_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_close (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    ablind_post ("Auto " ADEC_CLOSE, 1, index);

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    inp = &alsa_input_info[index];
    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (dec->input != ADEC_SRC_UNKNOWN)
    {
        // disconnect input-decoder
        if (dec->dec_info != NULL)
        {
            bm_disconnect_block (dec->dec_info, 0);
            bm_disconnect_block (dec->dec_info, BYPASS_PORT);
        }
        // disconnect decoder-renderer
        if (ren->ren_info != NULL)
        {
            bm_disconnect_block (ren->ren_info, 0);
            bm_disconnect_block (ren->ren_info, BYPASS_PORT);
        }
    }

    if (dec->dec_info != NULL)
        bm_destroy_block (dec->dec_info);

    if (ren->ren_info != NULL)
        bm_destroy_block (ren->ren_info);

    if (dec->input == ADEC_SRC_AAD)
    {
        debug ("INPUT_SIF is allocated in sif module.\n");
    }
    else
    {
        if (inp->input_info != NULL)
        {
            bm_destroy_block (inp->input_info);
        }
    }

    memset (inp, 0x0, sizeof (ALSA_INPUT_INFO_T));

    dec->dec_info = NULL;
    ren->ren_info = NULL;
    inp->input_info = NULL;

    alsa_decoder_init (index);

    info ("alsa_decoder_close index %d .\n", index);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_connect_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_connect_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open && dec->input != ADEC_SRC_UNKNOWN)
            ucontrol->value.integer.value[index * 2 + 1] = dec->input;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_connect_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_connect (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
    adec_src_port_index_ext_type_t input = ADEC_SRC_UNKNOWN;
    enum input_type input_type;
    int input_index;
    bool bypass = false;
    enum RENDERER_CLK_TYPE clock_type = RENDERER_CLK_TYPE_GSTC;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    input = ucontrol->value.integer.value[1];
    ablind_post ("Auto " ADEC_CONNECT, 2, index, input);

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    inp = &alsa_input_info[index];
    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!ren->is_open)
    {
        error ("can not find audio renderer, index %d .\n", index);
        goto exit;
    }

    if (dec->input != ADEC_SRC_UNKNOWN)
    {
        error ("audio decoder is already connected to input, index %d input %d .\n", index,
            dec->input);
        goto exit;
    }

    if (input <= ADEC_SRC_UNKNOWN || input > ADEC_SRC_HDMI_DEFAULT)
    {
        error ("audio decoder input is error, index %d input %d .\n", index, input);
        goto exit;
    }

    dec->input = input;

    decoder_set_input (dec->dec_info, decoder_convert_input (input));

    _alsa_decoder_convert_input (input, &input_type, &input_index, &bypass);

    if (input_type >= INPUT_MAX)
    {
        error ("invalid input type, input %d .\n", input);
        goto exit;
    }

    if (input_type != INPUT_SIF)
    {
        if (inp->input_info)
        {
            noti ("input%d (%p) already exist!!\n", index, inp->input_info);

            if (input_get_type (inp->input_info) == INPUT_SIF)
                debug ("INPUT_SIF is allocated in sif module.\n");
            else
                bm_destroy_block (inp->input_info);
        }

        inp->input_info = bm_create_block ("input", index);
        if (inp->input_info == NULL)
        {
            error ("error in create input block\n");
            goto exit;
        }

#ifdef SUPPORT_SOUNDBAR
        if (input_type == INPUT_I2S)
        {
#if defined (CHIP_NAME_o26)
            extern int aud_hal_codec_set_i2s_input (void);

            aud_hal_codec_set_i2s_input ();
#endif

            input_set_i2s_port_count (inp->input_info, dec->i2s_port_count);
        }
#endif

        input_set_type (inp->input_info, index, input_type, input_index, false);
    }
    else
    {
        inp->input_info = bm_get_block_info_by_index ("input", INPUT_SIF_INDEX);
        if (inp->input_info == NULL)
        {
            error ("error in get input block by index\n");
            goto exit;
        }
        input_set_type (inp->input_info, index, input_type, input_index, true);
    }
    inp->index = input_index;

    // set input as drop
    if (inp->input_info)
    {
        if (input_get_type (inp->input_info) == INPUT_SIF)
        {
            if (index == main_audio_index && acapture_is_encoder_connected () == true)
                noti ("MAIN INPUT_SIF is used by encoder module.\n");
            else if (index != main_audio_index && (main_audio_index >= 0
                    && main_audio_index < ALSA_ADEC_MAX))
            {
                ALSA_INPUT_INFO_T *inp_main = &alsa_input_info[main_audio_index];

                if (inp_main->input_info != NULL
                    && input_get_type (inp_main->input_info) == INPUT_SIF)
                    noti ("SUB INPUT_SIF is used by MAIN INPUT_SIF.\n");
                else
                    input_drop_data (inp->input_info, true);
            }
            else
                input_drop_data (inp->input_info, true);
        }
        else
            input_drop_data (inp->input_info, true);
    }

    if (inp->input_info != NULL && input_get_type (inp->input_info) == INPUT_TP)
        clock_type = RENDERER_CLK_TYPE_PCR_M + inp->index;
    else
        clock_type = RENDERER_CLK_TYPE_GSTC;
    renderer_set_param (ren->ren_info, "clock_type=%d", clock_type);

    if (dec->is_connected == FALSE)
    {
        bm_connect_block (inp->input_info, 0, dec->dec_info, 0);
        bm_connect_block (dec->dec_info, 0, ren->ren_info, 0);

        // HDMI pass-through
        if (bypass)
        {
            bm_connect_block (inp->input_info, BYPASS_PORT, dec->dec_info, BYPASS_PORT);

#ifdef ENABLE_DECODER_OUTPUT_MODE
            if (dec->hdmi_output_main && dec->hdmi_output_sub)
                input_set_hdmi_bypass (inp->input_info, false, 0);
            else if (!dec->hdmi_output_main && dec->hdmi_output_sub)
                input_set_hdmi_bypass (inp->input_info, true, 0);
#else
            if (dec->output_drop == DECODER_OUTPUT_DROP_NONE)
                input_set_hdmi_bypass (inp->input_info, false, 0);
            else if (dec->output_drop == DECODER_OUTPUT_DROP_MAIN)
                input_set_hdmi_bypass (inp->input_info, true, 0);
#endif

            input_set_hdmi_multi_pcm_out (inp->input_info, dec->hdmi_multi_pcm_out);
        }

        dec->is_connected = TRUE;
    }

    info ("alsa_decoder_connect index %d input %d (%s) .\n", index, input,
        adec_src_port_type[input]);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_disconnect_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_disconnect_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open && dec->input == ADEC_SRC_UNKNOWN)
            ucontrol->value.integer.value[index * 2 + 1] = TRUE;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_open_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_disconnect (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    ablind_post ("Auto " ADEC_DISCONNECT, 1, index);

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    inp = &alsa_input_info[index];
    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!ren->is_open)
    {
        error ("can not find audio renderer, index %d .\n", index);
        goto exit;
    }

    if (dec->input == ADEC_SRC_UNKNOWN)
    {
        error ("audio decoder is not connected to input, index %d .\n", index);
        goto exit;
    }

    // disconnect input-decoder-renderer
    if (dec->is_connected == TRUE)
    {
        bm_disconnect_block (dec->dec_info, 0);
        bm_disconnect_block (ren->ren_info, 0);
        bm_disconnect_block (ren->ren_info, BYPASS_PORT);

        if ((dec->input >= ADEC_SRC_HDMI_PORT0 && dec->input <= ADEC_SRC_HDMI_PORT3)
            || (dec->input == ADEC_SRC_HDMI_DEFAULT))
        {
            bm_disconnect_block (dec->dec_info, BYPASS_PORT);
        }

        dec->is_connected = FALSE;
    }

    dec->prev_input = dec->input;
    dec->input = ADEC_SRC_UNKNOWN;
    ren->is_play_paused = false;

    if (dec->prev_input > ADEC_SRC_UNKNOWN && dec->prev_input <= ADEC_SRC_HDMI_DEFAULT)
    {
        if (dec->prev_input != ADEC_SRC_AAD)
            bm_destroy_block (inp->input_info);
        inp->input_info = NULL;
    }

    info ("alsa_decoder_disconnect index %d .\n", index);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_codec_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_codec_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open && dec->codec != ADEC_SRC_CODEC_UNKNOWN)
            ucontrol->value.integer.value[index * 2 + 1] = dec->codec;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_codec_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_codec (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
    adec_src_codec_ext_type_t codec = ADEC_SRC_CODEC_UNKNOWN;
    enum audio_decoder_codec decoder_codec = AUDIO_DECODER_CODEC_UNKNOWN;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    codec = ucontrol->value.integer.value[1];
    ablind_post ("Auto " ADEC_CODEC, 2, index, codec);

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    inp = &alsa_input_info[index];
    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    dec->codec = codec;

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!ren->is_open)
    {
        error ("can not find audio renderer, index %d .\n", index);
        goto exit;
    }

    if (codec == ADEC_SRC_CODEC_UNKNOWN
        || (aud_hal_dts_supported () == false && ADEC_SRC_CODEC_DTS <= codec
            && codec <= ADEC_SRC_CODEC_DTS_X_P2))
    {
        error ("codec %d (%s) is not suppported\n", codec, _get_codec_name (codec));
        dec->codec = ADEC_SRC_CODEC_UNKNOWN;
        goto exit;
    }

#ifdef SUPPORT_SOUNDBAR
    if (decoder_sb_codec_supported (codec) == false)
    {
        error ("soundbar: codec %d (%s) is not suppported\n", codec, _get_codec_name (codec));
        dec->codec = ADEC_SRC_CODEC_UNKNOWN;
        goto exit;
    }
#endif

    if (decoder_is_created (dec->dec_info) && dec->is_started)
    {
        error ("decoder is running, index %d .\n", index);
        goto exit;
    }

    decoder_codec = decoder_convert_codec (codec);

    //In case of SIF input, do not set es codec if not pcm codec.
    if (inp->input_info != NULL && input_get_type (inp->input_info) == INPUT_SIF)
    {
        if (decoder_codec != AUDIO_DECODER_CODEC_PCM)
        {
            noti ("sif codec error index %d codec %d (%s) .\n", index, codec,
                _get_codec_name (codec));

            ret = 0;
            goto exit;
        }
    }

    decoder_set_codec (dec->dec_info, decoder_codec);

    if (inp->input_info != NULL && input_get_type (inp->input_info) == INPUT_HDMI)
        bm_connect_block (dec->dec_info, BYPASS_PORT, ren->ren_info, BYPASS_PORT);
    else
        bm_connect_block (dec->dec_info, 1, ren->ren_info, BYPASS_PORT);

    info ("alsa_decoder_codec index %d codec %d (%s) .\n", index, codec, _get_codec_name (codec));

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int decoder_set_codec_param (int index)
{
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
#ifndef SUPPORT_SOUNDBAR
    struct aud_block_info *mixer = bm_get_block_info_by_index ("mixer", 0);
#endif

    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    if (!dec->dec_info)
    {
        error ("decoder is not opened\n");
        return -1;
    }

    decoder_set_main_decoder_property (index);

    decoder_set_param (dec->dec_info,
        "drc-mode=%d audio-description=%d output-mode=%d",
        dec->drc, alsa_decoder_ad_on_off, dec->dualmono_mode);

#ifndef SUPPORT_SOUNDBAR
    decoder_set_param (dec->dec_info, "downmix-mode=%d", dec->downmix);
#endif

    switch (dec->codec)
    {
        case ADEC_SRC_CODEC_AAC:
        case ADEC_SRC_CODEC_HEAAC:
        {
#if (MS12_VER >= 28)
            decoder_set_param (dec->dec_info, "dec-id=%d", index);
#endif
            decoder_set_param (dec->dec_info, "iec-format=1");
            if (dec->default_prl != ALSA_INVALID_DEFAULT_PRL)
                decoder_set_param (dec->dec_info, "default-prl=%d", (dec->default_prl * -1 * 4));       //calc dBFS value
            decoder_set_param (dec->dec_info, "audio-description=%d", ottmode_enable ? 0 : 1);
            break;
        }
        case ADEC_SRC_CODEC_AC3:
        {
            decoder_set_param (dec->dec_info, "dec-id=%d", index);
            decoder_set_param (dec->dec_info, "atmos-decoding=%d", 0);
            decoder_set_param (dec->dec_info, "audio-description=%d", ottmode_enable ? 0 : 1);
            break;
        }
        case ADEC_SRC_CODEC_EAC3:
        {
            decoder_set_param (dec->dec_info, "dec-id=%d", index);
            decoder_set_param (dec->dec_info, "atmos-decoding=%d", atmos_decoding_enable);
            if (sndout_get_atmos_encode_on ())
                decoder_set_param (dec->dec_info, "legacy-ddp-out=0");
            else
                decoder_set_param (dec->dec_info, "legacy-ddp-out=1");
            decoder_set_param (dec->dec_info, "audio-description=%d", ottmode_enable ? 0 : 1);
            break;
        }
        case ADEC_SRC_CODEC_MAT:
        {
            decoder_set_param (dec->dec_info, "dec-id=%d", index);
            break;
        }
        case ADEC_SRC_CODEC_AC4:
        {
            decoder_set_param (dec->dec_info, "atmos-decoding=%d", atmos_decoding_enable);
            decoder_set_param (dec->dec_info,
                "iso-type=%d first-lang=%d second-lang=%d ad-type=%d prio-ad-type=%d ad-mixing=%d associate-volume=%d de-gain=%d",
                dec->first_lang.iso_type, dec->first_lang.lang, dec->second_lang.lang, dec->ad_type,
                dec->prio_ad_type, dec->ac4_ad_on_off, dec->associate_audio_volume,
                dec->dialog_gain);
            decoder_set_param (dec->dec_info, "pres-group-index=%d",
                (dec->ac4_group_index == ALSA_GROUP_INDEX_MAX) ? -1 : dec->ac4_group_index);
            if (sndout_get_atmos_encode_on ())
                decoder_set_param (dec->dec_info, "legacy-ddp-out=0");
            else
                decoder_set_param (dec->dec_info, "legacy-ddp-out=1");
            break;
        }
        case ADEC_SRC_CODEC_DRA:
        {
            if (ren->is_open)
                renderer_set_param (ren->ren_info, "lowerbound=%d upperbound=%d", 50, 64);
            break;
        }

#ifdef SUPPORT_DTSX
        case ADEC_SRC_CODEC_DTS:
        case ADEC_SRC_CODEC_DTS_HD_MA:
        case ADEC_SRC_CODEC_DTS_EXPRESS:
        case ADEC_SRC_CODEC_DTS_HD:
        case ADEC_SRC_CODEC_DTS_X_P1:
        case ADEC_SRC_CODEC_DTS_X_P2:
        {
            struct aud_block_info *encoder;
            int enc_mode = 2;

            decoder_set_param (dec->dec_info, "transcoding=%d", 1);
            decoder_set_param (dec->dec_info, "dts-seamless=%d", 0);

            encoder = bm_get_block_info_by_index ("encoder", OUTPUT_ARC);
            if (encoder)
            {
                enc_mode = aud_encoder_get_dtsx_enc_mode (encoder);
                noti ("GET enc_mode From ARC = %d\n", enc_mode);
            }
            else
            {
                encoder = bm_get_block_info_by_index ("encoder", OUTPUT_OPTIC);
                if (encoder)
                {
                    enc_mode = aud_encoder_get_dtsx_enc_mode (encoder);
                    noti ("GET enc_mode From OPTIC = %d\n", enc_mode);
                }
            }

            noti ("set enc_mode %d to decoder\n", enc_mode);

            decoder_set_param (dec->dec_info, "enc-mode=%d", enc_mode);
            break;
        }
#endif

        default:
            break;
    }

#ifdef SUPPORT_SOUNDBAR
    switch (dec->codec)
    {
        case ADEC_SRC_CODEC_AUTO:
        case ADEC_SRC_CODEC_AC3:
        case ADEC_SRC_CODEC_EAC3:
        case ADEC_SRC_CODEC_MAT:
#ifdef SUPPORT_DTSX
        case ADEC_SRC_CODEC_DTS:
        case ADEC_SRC_CODEC_DTS_HD_MA:
        case ADEC_SRC_CODEC_DTS_EXPRESS:
        case ADEC_SRC_CODEC_DTS_HD:
        case ADEC_SRC_CODEC_DTS_X_P1:
        case ADEC_SRC_CODEC_DTS_X_P2:
#endif
        {
            int decoder_spk_conf = sndout_get_decoder_spk_conf ();

            if (decoder_spk_conf != -1)
                decoder_set_param (dec->dec_info, "speakers=%d", decoder_spk_conf);
            break;
        }
        default:
            break;
    }
#endif

#ifndef SUPPORT_SOUNDBAR
    if (mixer && (index == main_audio_index))
    {
        unsigned int dec_dmx_mode = decoder_get_downmix_mode (index);
        mixer_set_pcmren_drc_mode (mixer, decoder_get_drc_mode (index));
        mixer_set_pcmren_downmix_mode (mixer, decoder_get_pcmren_downmix_mode (dec_dmx_mode));
        decoder_set_metadata_type (index);
    }
#endif

    return 0;
}

static int decoder_config (int index)
{
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_DECODER_INFO_T *dec = NULL;

    enum input_type input_type = INPUT_MAX;

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    inp = &alsa_input_info[index];
    dec = &alsa_decoder_info[index];

    if (inp->input_info != NULL)
        input_type = input_get_type (inp->input_info);

    decoder_set_codec_param (index);

#ifdef SUPPORT_SOUNDBAR
    if (input_type == INPUT_HDMI || input_type == INPUT_I2S)
#else
    if (input_type == INPUT_HDMI)
#endif
    {
        if (inp->input_info)
        {
            bool forced_pcm = false;

            if (dec->codec == ADEC_SRC_CODEC_PCM)
                forced_pcm = true;

#ifdef SUPPORT_SOUNDBAR
            if (input_type == INPUT_HDMI)
                input_set_hdmi (inp->input_info, forced_pcm);
            else
                input_set_i2s (inp->input_info, forced_pcm, dec->i2s_hdmi_type,
                    dec->i2s_hdmi_ch, dec->i2s_hdmi_freq);
#else
            input_set_hdmi (inp->input_info, forced_pcm);
#endif

            input_register_event (inp->input_info, INPUT_EVT_HDMI_PCM_FORMAT,
                decoder_hdmi_pcm_format_info_cb, dec->dec_info);

#ifdef SUPPORT_DTSX
            //Register only DTS/DTS-HD codec only
            if (dec->codec >= ADEC_SRC_CODEC_DTS && dec->codec <= ADEC_SRC_CODEC_DTS_X_P2)
            {
                input_register_event (inp->input_info, INPUT_EVT_HDMI_DTS_FORMAT_CHANGED,
                    input_hdmi_dts_format_changed_cb, inp->input_info);
            }
#endif
        }
    }
    else if (input_type == INPUT_TP)
    {
        if (inp->input_info)
        {
            enum audio_decoder_codec decoder_codec = AUDIO_DECODER_CODEC_UNKNOWN;
            adec_src_codec_ext_type_t codec;
            bool clock_x4 = false;

            codec = dec->codec;
            decoder_codec = decoder_convert_codec (codec);

            if (codec == ADEC_SRC_CODEC_EAC3 || codec == ADEC_SRC_CODEC_EAC3_ATMOS)
                clock_x4 = true;

            input_set_tp (inp->input_info, decoder_codec, clock_x4);
            input_register_event (inp->input_info, INPUT_EVT_TP_ES_EXIST_INFO,
                decoder_tp_es_exist_info_cb, dec->dec_info);
            input_register_event (inp->input_info, INPUT_EVT_TP_PDEC_ERROR_INFO,
                input_tp_pdec_error_info_cb, inp->input_info);

            if (alsa_decoder_ad_on_off == true && index != main_audio_index)
            {
                aimc_set_property (input_get_uid (inp->input_info), "discard-packet=%d",
                    DISCARD_PACKET_SIZE);
                noti ("index %d, discard-packet %d .\n", index, DISCARD_PACKET_SIZE);
            }
        }
    }
    else if (input_type == INPUT_ADC)
    {
        noti ("adc_port_index %d .\n", adc_info.adc_port_index);
        aud_hal_set_adc_port_number (adc_info.adc_port_index);
    }

    return 0;
}

static int alsa_decoder_start_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_start_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open && dec->is_started)
            ucontrol->value.integer.value[index * 2 + 1] = TRUE;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_start_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_start (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    inp = &alsa_input_info[index];
    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (dec->input == ADEC_SRC_UNKNOWN)
    {
        error ("audio decoder is not connected to input, index %d .\n", index);
        goto exit;
    }

    if (dec->codec == ADEC_SRC_CODEC_UNKNOWN)
    {
        error ("audio decoder codec is not setted, index %d .\n", index);
        goto exit;
    }

    if (dec->is_started)
    {
        error ("audio decoder is already started, index %d .\n", index);
        goto exit;
    }

    info ("dec%d is starting..\n", index);

    decoder_config (index);

    decoder_register_event (dec->dec_info, AUDIO_DECODER_EVENT_INFO, decoder_decoded_info_cb, true);
#ifdef SUPPORT_SOUNDBAR
    decoder_register_event (dec->dec_info, AUDIO_DECODER_EVENT_DEC_ID_CHANGED,
        decoder_module_id_changed_cb, true);
#endif
    decoder_connect (dec->dec_info);

    //sndout_connect_output (index);

    if (dec->is_connected == FALSE)
    {
        bm_connect_block (dec->dec_info, 0, ren->ren_info, 0);

        dec->is_connected = TRUE;
    }

    if (inp->input_info)
    {
        bool valid_codec = true;
        enum input_type input_type = INPUT_MAX;
        enum audio_decoder_codec input_codec = AUDIO_DECODER_CODEC_UNKNOWN;
        enum audio_decoder_codec decoder_codec = AUDIO_DECODER_CODEC_UNKNOWN;

        decoder_codec = decoder_convert_codec (dec->codec);
        input_type = input_get_type (inp->input_info);
        if (input_type != INPUT_TP)
        {
            input_codec = AUDIO_DECODER_CODEC_PCM;

#ifdef SUPPORT_SOUNDBAR
            if (input_type == INPUT_HDMI || input_type == INPUT_I2S)
#else
            if (input_type == INPUT_HDMI)
#endif
                input_codec = input_get_hdmi_codec (inp->input_info);
        }

#ifndef SUPPORT_SOUNDBAR
        if (decoder_codec != AUDIO_DECODER_CODEC_PCM && input_codec == AUDIO_DECODER_CODEC_PCM)
            valid_codec = false;
#endif

#ifdef SUPPORT_SOUNDBAR
        //ARC : i2s_port_count = 1, e-ARC : i2s_port_count = 4
        if (dec->i2s_port_count == 1)
        {
            if (dec->codec == ADEC_SRC_CODEC_MAT)
            {
                error ("invalid i2s port count, %d codec, %d .\n", dec->i2s_port_count, dec->codec);
                valid_codec = false;
            }
        }
#endif

        if (valid_codec)
        {
            input_start (inp->input_info);
            input_drop_data (inp->input_info, false);
        }
        else
        {
            noti ("decoder_start index %d valid_codec %d dec_codec %d input_codec %d.\n", index,
                valid_codec, decoder_codec, input_codec);
        }
    }

    if (ren->is_open)
    {
        if (dec->input >= ADEC_SRC_ATP0 && dec->input <= ADEC_SRC_ATP1)
        {
            renderer_set_param (ren->ren_info, "sync=%d", ren->sync);
            renderer_set_param (ren->ren_info, "presented-pts-index=%d", index);

            if (ren->is_play_paused == true)
            {
                renderer_lipsync_set_idle_time (ren->ren_info, 300);
                ren->is_play_paused = false;
            }
            else
                renderer_lipsync_set_idle_time (ren->ren_info, 60);

            if (ren->master_syncmode)
            {
                renderer_set_param (ren->ren_info, "offset=%d", ren->offset);
                renderer_set_param (ren->ren_info, "clock_type=%d", RENDERER_CLK_TYPE_MASTER);

                renderer_register_event (ren->ren_info, AUDIO_RENDERER_EVENT_MASTER_INFO,
                    renderer_master_info_cb, true);
            }
        }

        if ((dec->input >= ADEC_SRC_HDMI_PORT0 && dec->input <= ADEC_SRC_HDMI_PORT3)
            || (dec->input == ADEC_SRC_HDMI_DEFAULT) || (dec->input == ADEC_SRC_I2S))
        {
            renderer_set_param (ren->ren_info, "discard_param=%d", 11);
        }

        renderer_lipsync_set_idle (ren->ren_info);
    }

    dec->is_started = TRUE;

    info ("decoder_start index %d .\n", index);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_stop_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_stop_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open && !dec->is_started)
            ucontrol->value.integer.value[index * 2 + 1] = TRUE;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_stop_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

extern void renderer_set_basetime_ipc (unsigned int index, unsigned int clock_base_time,
    unsigned int stream_base_time, bool is_set, bool is_all_set);
static int alsa_decoder_stop (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
    ALSA_INPUT_INFO_T *inp = NULL;
    enum input_type input_type = INPUT_MAX;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];
    inp = &alsa_input_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!dec->is_started)
    {
        error ("audio decoder is not started, index %d .\n", index);
        goto exit;
    }

    if (inp->input_info)
    {
        input_type = input_get_type (inp->input_info);

#ifdef SUPPORT_SOUNDBAR
        if (input_type == INPUT_HDMI || input_type == INPUT_I2S)
#else
        if (input_type == INPUT_HDMI)
#endif
        {
            input_unregister_event (inp->input_info, INPUT_EVT_HDMI_PCM_FORMAT);

#ifdef SUPPORT_DTSX
            //Unregister only DTS/DTS-HD codec only
            if (dec->codec >= ADEC_SRC_CODEC_DTS && dec->codec <= ADEC_SRC_CODEC_DTS_X_P2)
            {
                input_unregister_event (inp->input_info, INPUT_EVT_HDMI_DTS_FORMAT_CHANGED);
            }
#endif
        }
        else if (input_type == INPUT_TP)
        {
            input_unregister_event (inp->input_info, INPUT_EVT_TP_ES_EXIST_INFO);
            input_unregister_event (inp->input_info, INPUT_EVT_TP_PDEC_ERROR_INFO);
        }

        if (input_type == INPUT_SIF)
        {
            if (index == main_audio_index && acapture_is_encoder_connected () == true)
                noti ("MAIN INPUT_SIF is used by encoder module.\n");
            else if (index != main_audio_index && (main_audio_index >= 0
                    && main_audio_index < ALSA_ADEC_MAX))
            {
                ALSA_INPUT_INFO_T *inp_main = &alsa_input_info[main_audio_index];

                if (inp_main->input_info != NULL
                    && input_get_type (inp_main->input_info) == INPUT_SIF)
                    noti ("SUB INPUT_SIF is used by MAIN INPUT_SIF.\n");
                else
                {
                    input_stop (inp->input_info);
                    input_drop_data (inp->input_info, true);
                }
            }
            else
            {
                input_stop (inp->input_info);
                input_drop_data (inp->input_info, true);
            }
        }
        else
        {
            input_stop (inp->input_info);
            input_drop_data (inp->input_info, true);
        }
    }

    if (dec->codec == ADEC_SRC_CODEC_AC4 || dec->codec == ADEC_SRC_CODEC_AC4_ATMOS)
        decoder_set_param (dec->dec_info, "pres-group-index=-1");

    renderer_lipsync_clear_idle (ren->ren_info);

    if (ren->master_syncmode)
    {
        renderer_unregister_event (ren->ren_info, AUDIO_RENDERER_EVENT_MASTER_INFO);

        /* clear basetime IPC registers */
        renderer_set_basetime_ipc (index, 0xFFFFFFFF, 0xFFFFFFFF, false, false);
    }

    decoder_unregister_event (dec->dec_info, AUDIO_DECODER_EVENT_INFO);
#ifdef SUPPORT_SOUNDBAR
    decoder_unregister_event (dec->dec_info, AUDIO_DECODER_EVENT_DEC_ID_CHANGED);
#endif
    if (dec->is_connected == TRUE)
    {
        bm_disconnect_block (ren->ren_info, 0);
        bm_disconnect_block (ren->ren_info, BYPASS_PORT);

        dec->is_connected = FALSE;
    }

#ifdef SUPPORT_SOUNDBAR
    decoder_stop (dec->dec_info);
#endif
    dec->is_started = FALSE;

    info ("alsa_decoder_stop index %d .\n", index);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_capacity_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_capacity_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;

    ucontrol->value.integer.value[0] = ALSA_ADEC_MAX;   // ADEC
    ucontrol->value.integer.value[1] = ALSA_AMIXER_MAX; // AMIXER

    for (index = 0; index < 2; index++)
    {
        debug ("alsa_decoder_capacity_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_user_capacity_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_user_capacity_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;

    ucontrol->value.integer.value[0] = alsa_decoder_count;      // ADEC
    ucontrol->value.integer.value[1] = alsa_mixer_count;        // AMIXER

    for (index = 0; index < 2; index++)
    {
        debug ("alsa_decoder_user_capacity_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_user_capacity (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int decoder_count;
    int mixer_count;

    decoder_count = ucontrol->value.integer.value[0];
    mixer_count = ucontrol->value.integer.value[1];

    if (!(decoder_count >= 0 && decoder_count <= ALSA_ADEC_MAX))
    {
        error ("invalid user max capacity, decoder count %d .\n", decoder_count);
        return -1;
    }

    if (!(mixer_count >= 0 && mixer_count <= ALSA_AMIXER_MAX))
    {
        error ("invalid user max capacity, mixer count %d .\n", mixer_count);
        return -1;
    }

    alsa_decoder_count = decoder_count;
    alsa_mixer_count = mixer_count;

    info ("decoder_user_capacity adec %d amixer %d .\n", decoder_count, mixer_count);

    return 0;
}

static int alsa_decoder_syncmode_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_syncmode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index = 0;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];
        if (dec->is_open)
        {
            ren = &alsa_renderer_info[index];
            ucontrol->value.integer.value[index * 2 + 1] = ren->sync;
        }
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_syncmode_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_syncmode (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_RENDERER_INFO_T *ren = NULL;
    int on_off;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    on_off = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    if (!(on_off >= 0 && on_off <= 1))
    {
        error ("invalid sync mode, %d .\n", on_off);
        return -1;
    }

    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (!ren->is_open)
    {
        error ("can not find audio renderer, index %d .\n", index);
        goto exit;
    }

    renderer_set_param (ren->ren_info, "sync=%d", on_off);

    ren->sync = on_off;

    info ("alsa_decoder_syncmode index %d on_off %d .\n", index, on_off);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_trickmode_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_trickmode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index = 0;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
        {
            ren = &alsa_renderer_info[index];
            ucontrol->value.integer.value[index * 2 + 1] = ren->trick;
        }
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_trickmode_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_trickmode (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
    adec_trick_mode_ext_type_t trick_mode = ADEC_TRICK_NONE;
    int rate = 0;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    trick_mode = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    if (!(trick_mode >= ADEC_TRICK_NONE && trick_mode <= ADEC_TRICK_FAST_FORWARD_2P00X))
    {
        error ("invalid trick mode, %d .\n", trick_mode);
        return -1;
    }

    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (!ren->is_open)
    {
        error ("can not find audio renderer, index %d .\n", index);
        goto exit;
    }

    rate = decoder_convert_trickmode (trick_mode);

    renderer_set_param (ren->ren_info, "rate-in=%d", rate);

    ren->trick = trick_mode;

    if (trick_mode == ADEC_TRICK_PAUSE)
        ren->is_play_paused = true;

    info ("alsa_decoder_trickmode index %d trick_speed %d (%s) .\n", index, trick_mode,
        trick_name[trick_mode]);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_master_syncmode_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_master_syncmode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index = 0;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];
        if (dec->is_open)
        {
            ren = &alsa_renderer_info[index];
            ucontrol->value.integer.value[index * 2 + 1] = ren->master_syncmode;
        }
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_mster_syncmode_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_master_syncmode (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
    int on_off;
    enum RENDERER_CLK_TYPE clock_type = RENDERER_CLK_TYPE_GSTC;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    on_off = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    if (!(on_off >= 0 && on_off <= 1))
    {
        error ("invalid master sync mode, %d .\n", on_off);
        return -1;
    }

    inp = &alsa_input_info[index];
    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (!ren->is_open)
    {
        error ("can not find audio renderer, index %d .\n", index);
        goto exit;
    }

    if (on_off)
        clock_type = RENDERER_CLK_TYPE_MASTER;
    else
    {
        if (inp->input_info != NULL && input_get_type (inp->input_info) == INPUT_TP)
            clock_type = RENDERER_CLK_TYPE_PCR_M + inp->index;
        else
            clock_type = RENDERER_CLK_TYPE_GSTC;
    }

    renderer_set_param (ren->ren_info, "sync=%d", on_off);
    renderer_set_param (ren->ren_info, "clock_type=%d", clock_type);

    ren->sync = on_off;
    ren->master_syncmode = on_off;

    info ("alsa_decoder_mster_syncmode index %d on_off %d .\n", index, on_off);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_lipsyc_offset_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_lipsyc_offset_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index = 0;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];
        if (dec->is_open)
        {
            ren = &alsa_renderer_info[index];
            ucontrol->value.integer.value[index * 2 + 1] = ren->offset;
        }
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_lipsyc_offset_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_lipsyc_offset (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_RENDERER_INFO_T *ren = NULL;
    int offset;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    offset = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    if (!(offset >= 0 && offset <= 2500))
    {
        error ("invalid lipsync offset, %d .\n", offset);
        return -1;
    }

    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (!ren->is_open)
    {
        error ("can not find audio renderer, index %d .\n", index);
        goto exit;
    }

    renderer_set_param (ren->ren_info, "offset=%d", offset);

    ren->offset = offset;

    info ("alsa_decoder_lipsyc_offset index %d offset %d .\n", index, offset);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_hdmi_audiomode_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = AHDMI_UNKNOWN;
    uinfo->value.integer.max = AHDMI_NO_AUDIO;
    return 0;
}

#ifdef INCLUDE_KDRV_HDMI20
static ahdmi_type_ext_type_t decoder_convert_hdmi_audiomode (LX_HDMI_AUDIO_TYPE_T lx_hdmi)
{
    ahdmi_type_ext_type_t hdmi;

    switch (lx_hdmi)
    {
        case LX_HDMI_AUDIO_DVI:
            hdmi = AHDMI_DVI;
            break;

        case LX_HDMI_AUDIO_NO_AUDIO:
            hdmi = AHDMI_NO_AUDIO;
            break;

        case LX_HDMI_AUDIO_PCM:
            hdmi = AHDMI_PCM;
            break;

        case LX_HDMI_AUDIO_AC3:
        case LX_HDMI_AUDIO_UNKNOWN_AC3:
            hdmi = AHDMI_AC3;
            break;

        case LX_HDMI_AUDIO_EAC3:
        case LX_HDMI_AUDIO_UNKNOWN_EAC3:
            hdmi = AHDMI_EAC3;
            break;

        case LX_HDMI_AUDIO_MAT:
        case LX_HDMI_AUDIO_UNKNOWN_MAT:
            hdmi = AHDMI_MAT;
            break;

        case LX_HDMI_AUDIO_DTS:
        case LX_HDMI_AUDIO_DTS_EXPRESS:
        case LX_HDMI_AUDIO_DTS_CD:
        case LX_HDMI_AUDIO_UNKNOWN_DTS:
            hdmi = AHDMI_DTS;
            break;

        case LX_HDMI_AUDIO_DTS_HD:
        case LX_HDMI_AUDIO_DTS_HD_HRA:
        case LX_HDMI_AUDIO_DTS_HD_MA:
        case LX_HDMI_AUDIO_UNKNOWN_DTS_HD:
        case LX_HDMI_AUDIO_UNKNOWN_DTS_HD_HRA:
            hdmi = AHDMI_DTS_HD;
            break;

        case LX_HDMI_AUDIO_AAC:
        case LX_HDMI_AUDIO_UNKNOWN_AAC:
            hdmi = AHDMI_AAC;
            break;

        case LX_HDMI_AUDIO_MPEG:
        case LX_HDMI_AUDIO_UNKNOWN_MPEG:
        case LX_HDMI_AUDIO_DEFAULT:
        default:
            hdmi = AHDMI_UNKNOWN;
    }

    return hdmi;
}
#endif

static int alsa_decoder_hdmi_audiomode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
#ifdef INCLUDE_KDRV_HDMI20
    int index = 0;
    ahdmi_type_ext_type_t hdmi_mode;
    LX_HDMI_AUDIO_INFO_T lx_hdmi_mode;

    int i;
    ALSA_DECODER_INFO_T *dec = NULL;
    enum audio_decoder_input input_type;

    index = kcontrol->private_value;

    if (index >= ALSA_HDMI_IN_MAX)
    {
        error ("invalid audio HDMI index, index %d .\n", index);
        return -1;
    }

    hdmi_get_audioinfo (index, &lx_hdmi_mode, sizeof (LX_HDMI_AUDIO_INFO_T));
    hdmi_mode = decoder_convert_hdmi_audiomode (lx_hdmi_mode.audioType);

    if (lx_hdmi_mode.audioType >= LX_HDMI_AUDIO_AC3_IEC60958
        && lx_hdmi_mode.audioType <= LX_HDMI_AUDIO_UNKNOWN_DTS_HD_HRA)
    {
        for (i = 0; i < ALSA_ADEC_MAX; i++)
        {
            dec = &alsa_decoder_info[i];

            ALSADEC_LOCK ();

            input_type = decoder_convert_input (dec->input);
            if (dec->is_started &&
                (input_type >= AUDIO_DECODER_INPUT_HDMI0
                    && input_type <= AUDIO_DECODER_INPUT_HDMI3))
            {
                if (index == (input_type - AUDIO_DECODER_INPUT_HDMI0))
                {
                    struct decoded_info info = { };

                    decoder_get_decoded_info (dec->dec_info, &info);
                    if (info.codec == AUDIO_DECODER_CODEC_PCM || info.pc_valid_pcm)
                    {
                        hdmi_mode = AHDMI_PCM;
                        if (ahdmi_audio_type[index] != hdmi_mode)
                        {
                            noti ("PCM ahdmi audio type is changed, port %d type %d -> %d.\n",
                                index, ahdmi_audio_type[index], hdmi_mode);
                        }
                        ALSADEC_UNLOCK ();
                        break;
                    }
                }
            }

            ALSADEC_UNLOCK ();
        }
    }

    if (lx_hdmi_audio_type[index] != lx_hdmi_mode.audioType)
    {
        noti ("hdmi audio type is changed, port %d type %d(%s) -> %d(%s).\n", index,
            lx_hdmi_audio_type[index], _get_hdmi_lxcodec_name (lx_hdmi_audio_type[index]),
            lx_hdmi_mode.audioType, _get_hdmi_lxcodec_name (lx_hdmi_mode.audioType));

        lx_hdmi_audio_type[index] = lx_hdmi_mode.audioType;
    }

    ucontrol->value.integer.value[0] = hdmi_mode;
    ahdmi_audio_type[index] = hdmi_mode;

    debug ("index[%d]: %d, hdmi_audio_type %d.\n", index, hdmi_mode, lx_hdmi_mode.audioType);
#endif

    return 0;
}

static int alsa_decoder_hdmi_copyprotectioninfo_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = AHDMI_COPY_FREE;
    uinfo->value.integer.max = AHDMI_COPY_NEVER;
    return 0;
}

static int alsa_decoder_hdmi_copyprotectioninfo_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index = 0;
    LX_HDMI_AUDIO_COPY_T hdmi_copyinfo = LX_HDMI_AUDIO_COPY_FREE;

    index = kcontrol->private_value;

    if (index >= ALSA_HDMI_IN_MAX)
    {
        error ("invalid audio HDMI index, index %d .\n", index);
        return -1;
    }

    hdmi_get_audiocopyinfo (index, &hdmi_copyinfo, sizeof (LX_HDMI_AUDIO_COPY_T));

    ucontrol->value.integer.value[0] = hdmi_copyinfo;

    debug ("alsa_decoder_hdmi_copyprotectioninfo_get_param[%d]: %ld .\n", index,
        ucontrol->value.integer.value[index]);

    return 0;
}

static int alsa_decoder_adecinfo_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 22;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_adecinfo_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    int loop;
    ALSA_DECODER_INFO_T *dec = NULL;
    int ret = -1;

    index = kcontrol->private_value;

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (dec->is_open == FALSE)
    {
        error ("audio decoder is not opened.\n");
        goto exit;
    }

    for (loop = 0; loop < 22; loop++)
        ucontrol->value.integer.value[loop] = 0;

    // UINT32 adec_index (ADEC)
    ucontrol->value.integer.value[0] = index;

    // adec_src_codec_ext_type_t adec_decoding_type, what user set (ADEC)
    ucontrol->value.integer.value[2] = dec->codec;

    // adec_src_port_index_ext_type_t curAdecInputPort (ADEC)
    ucontrol->value.integer.value[5] = dec->input;

    // adec_src_port_index_ext_type_t prevAdecInputPort (ADEC)
    ucontrol->value.integer.value[6] = dec->prev_input;

    // adec_tp_mode_ext_type_t audioMode (TP) - set to default value
    ucontrol->value.integer.value[9] = AUDIO_DECODER_CH_MODE_UNKNOWN;

    if (dec->dec_info != NULL)
    {
        struct decoded_info info = { };
        decoder_get_decoded_info (dec->dec_info, &info);

        // BOOL bAdecStart (ADEC)
        ucontrol->value.integer.value[1] = dec->is_started;

        if (((dec->input >= ADEC_SRC_HDMI_PORT0 && dec->input <= ADEC_SRC_HDMI_PORT3)
                || (dec->input == ADEC_SRC_HDMI_DEFAULT) || (dec->input == ADEC_SRC_I2S))
            && (dec->codec == ADEC_SRC_CODEC_PCM))
        {
            ucontrol->value.integer.value[3] = ADEC_SRC_CODEC_PCM;
            ucontrol->value.integer.value[4] = ADEC_SRC_CODEC_PCM;
        }
        else
        {
            adec_src_codec_ext_type_t decoded_codec_info;

            decoded_codec_info = decoder_get_source_codec (dec->codec, &info);

            // adec_src_codec_ext_type_t curAdecFormat, actual current codec info by driver (ADEC)
            if (dec->is_started == TRUE && decoded_codec_info != ADEC_SRC_CODEC_UNKNOWN)
            {
                if (atmos_decoding_enable == TRUE)
                    ucontrol->value.integer.value[3] = decoded_codec_info;
                else
                    ucontrol->value.integer.value[3] = dec->codec;

                // adec_src_codec_ext_type_t srcAdecFormat, actual source codec info by driver (ADEC)
                ucontrol->value.integer.value[4] = decoded_codec_info;
            }
            else
            {
                ucontrol->value.integer.value[3] = ADEC_SRC_CODEC_UNKNOWN;
                ucontrol->value.integer.value[4] = ADEC_SRC_CODEC_UNKNOWN;
            }
        }
        // adec_dualmono_mode_ext_type_t curAdecDualMonoMode (ADEC)
        ucontrol->value.integer.value[7] = dec->dualmono_mode;

        // IsEsExist (TP)
        ucontrol->value.integer.value[8] = info.is_es_exist;
        // input (TP)에 callback 등록해서 처리해야 하나... ?
        // 기존에는 TP_EVT_ES_EXIST_INFO 이벤트를 등록해서 callback으로 해당 값을 업데이트 하도록 되어 있었음

        // adec_tp_mode_ext_type_t audioMode (TP)
        ucontrol->value.integer.value[9] = info.audio_mode;

        if (dec->codec == ADEC_SRC_CODEC_AAC || dec->codec == ADEC_SRC_CODEC_HEAAC)
        {
            // UINT32 heaac_version (TP heaac)
            ucontrol->value.integer.value[10] = info.version;

            // UINT32 heaac_tranmissionformat (TP heaac)
            ucontrol->value.integer.value[11] = info.transmissionformat;

            // UINT32 heaac_channelNum (TP heaac)
            ucontrol->value.integer.value[12] = info.source_channels;
        }
        else if (dec->codec == ADEC_SRC_CODEC_MPEG)
        {
            // UINT32 mpeg_bitrate (TP mpeg)
            ucontrol->value.integer.value[13] = info.avg_bit_rate / 1000;

            // UINT32 mpeg_sampleRate (TP mpeg)
            ucontrol->value.integer.value[14] = info.sampling_rate / 1000;

            // UINT32 mpeg_layer (TP mpeg)
            ucontrol->value.integer.value[15] = info.layer;

            // UINT32 mpeg_channelNum (TP mpeg)
            ucontrol->value.integer.value[16] = info.channels;
        }
        else if (dec->codec == ADEC_SRC_CODEC_AC3)
        {
            // UINT32 ac3_bitrate (TP ac3)
            ucontrol->value.integer.value[17] = info.avg_bit_rate / 1000;

            // UINT32 ac3_sampleRate (TP ac3)
            ucontrol->value.integer.value[18] = info.sampling_rate;

            // UINT32 ac3_channelnum (TP ac3)
            ucontrol->value.integer.value[19] = info.source_channels;

            // UINT32 ac3_EAC3 (TP ac3)
            ucontrol->value.integer.value[20] = info.eac3;
        }
        else if (dec->codec == ADEC_SRC_CODEC_PCM)
        {
            // UINT32 pcm_channelNum
            ucontrol->value.integer.value[21] = info.source_channels;
        }
    }

    for (index = 0; index < 22; index++)
    {
        trace ("alsa_decoder_info_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_adecinfo (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;

    debug_call ();

    index = kcontrol->private_value;

    info ("alsa_decoder_adecinfo index %d .\n", index);

    return 0;
}

static int alsa_decoder_drcmode_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_drcmode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = dec->drc;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_drcmode_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_drcmode (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
#ifndef SUPPORT_SOUNDBAR
    struct aud_block_info *mixer = bm_get_block_info_by_index ("mixer", 0);
#endif
    adec_dolbydrc_mode_ext_type_t drc;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    drc = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }
#ifdef SUPPORT_SOUNDBAR
    if (!(drc == ADEC_DOLBY_LINE_MODE || drc == ADEC_DOLBY_DRC_OFF))
    {
        error ("invalid dolby drc mode, %d .\n", drc);
        goto exit;
    }

    if (dec->dec_info)
        decoder_set_param (dec->dec_info, "drc-mode=%d", drc);

    dec->drc = drc;

    info ("alsa_decoder_drcmode (%s) .\n", (drc == ADEC_DOLBY_LINE_MODE) ? "ON" : "OFF");
#else
    if (!(drc >= ADEC_DOLBY_LINE_MODE && drc <= ADEC_DOLBY_DRC_OFF))
    {
        error ("invalid dolby drc mode, %d .\n", drc);
        goto exit;
    }

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "drc-mode=%d", drc);

        decoder_set_dolby_drc_mode (dec->dec_info, (enum audio_decoder_drc) drc);
    }

    dec->drc = drc;

    if (mixer && (index == main_audio_index))
        mixer_set_pcmren_drc_mode (mixer, decoder_get_drc_mode (index));

    info ("alsa_decoder_drcmode index %d dolby_drcmode %d (%s) .\n", index, drc, drc_name[drc]);
#endif
    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_default_prl_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = ALSA_ADEC_INT_MIN;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_default_prl_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = dec->default_prl;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_defaultprl_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_default_prl (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    int default_prl = 0;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    default_prl = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    if (default_prl > ALSA_DEFAULT_PRL_MAX || default_prl < ALSA_DEFAULT_PRL_MIN)
    {
        error ("invalid default PRL, default_prl %d .\n", default_prl);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "default-prl=%d", (default_prl * -1 * 4));    //calc dBFS value
    }

    dec->default_prl = default_prl;

    info ("alsa_decoder_default_prl index %d prl %d .\n", index, default_prl);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_dmxmode_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_dmxmode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = dec->downmix;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_dmxmode_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_dmxmode (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
    struct aud_block_info *mixer = bm_get_block_info_by_index ("mixer", 0);

    adec_downmix_mode_ext_type_t downmix_mode;
    unsigned int dec_dmx_mode;
    unsigned int pcmren_dmx_mode;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    downmix_mode = ucontrol->value.integer.value[1];

#ifdef SUPPORT_SOUNDBAR
    error ("soundbar does not supported downmix mode setting .");
    return -1;
#endif

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!(downmix_mode >= ADEC_LORO_MODE && downmix_mode <= ADEC_LTRT_MODE))
    {
        error ("invalid downmix mode, %d .\n", downmix_mode);
        goto exit;
    }

    dec->downmix = downmix_mode;

    dec_dmx_mode = decoder_get_downmix_mode (index);
    pcmren_dmx_mode = decoder_get_pcmren_downmix_mode (dec_dmx_mode);

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "downmix-mode=%d", dec_dmx_mode);
    }

    if (mixer && (index == main_audio_index))
    {
        mixer_set_pcmren_downmix_mode (mixer, pcmren_dmx_mode);
    }

    info ("alsa_decoder_dmxmode index %d downmix_mode %d (%s) .\n", index, downmix_mode,
        downmix_name[downmix_mode]);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_ac4_first_language_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 3;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_ac4_first_language_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 3);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 3] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
        {
            ucontrol->value.integer.value[index * 3 + 1] = dec->first_lang.iso_type;
            ucontrol->value.integer.value[index * 3 + 2] = dec->first_lang.lang;
        }
    }

    for (index = 0; index < ALSA_ADEC_MAX * 3; index++)
    {
        debug ("alsa_decoder_ac4_first_language_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_ac4_first_language (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    adec_ac4_lang_code_ext_type_t iso_type;
    int first_lang;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    iso_type = ucontrol->value.integer.value[1];
    first_lang = ucontrol->value.integer.value[2];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!(dec->codec == ADEC_SRC_CODEC_AC4 || dec->codec == ADEC_SRC_CODEC_AC4_ATMOS))
    {
        error ("audio decoder codec is not AC4 .\n");
        goto exit;
    }

    if (!(iso_type >= ADEC_AC4_LANG_CODE_ISO639_1 && iso_type <= ADEC_AC4_LANG_CODE_ISO639_2))
    {
        error ("invalid iso type, %d .\n", iso_type);
        goto exit;
    }

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "iso-type=%d first-lang=%d", iso_type, first_lang);
    }

    dec->first_lang.iso_type = iso_type;
    dec->first_lang.lang = first_lang;

    info ("alsa_decoder_ac4_first_language index %d, type %d (%s), first_lang %d (%s) .\n", index,
        iso_type, ac4_lang_type_name[iso_type], first_lang, _get_ac4_lang_name (first_lang));

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_ac4_second_language_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 3;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_ac4_second_language_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 3);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 3] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
        {
            ucontrol->value.integer.value[index * 3 + 1] = dec->second_lang.iso_type;
            ucontrol->value.integer.value[index * 3 + 2] = dec->second_lang.lang;
        }
    }

    for (index = 0; index < ALSA_ADEC_MAX * 3; index++)
    {
        debug ("alsa_decoder_ac4_second_language_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_ac4_second_language (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    adec_ac4_lang_code_ext_type_t iso_type;
    int second_lang;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    iso_type = ucontrol->value.integer.value[1];
    second_lang = ucontrol->value.integer.value[2];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!(dec->codec == ADEC_SRC_CODEC_AC4 || dec->codec == ADEC_SRC_CODEC_AC4_ATMOS))
    {
        error ("audio decoder codec is not AC4 .\n");
        goto exit;
    }

    if (!(iso_type >= ADEC_AC4_LANG_CODE_ISO639_1 && iso_type <= ADEC_AC4_LANG_CODE_ISO639_2))
    {
        error ("invalid iso type, %d .\n", iso_type);
        goto exit;
    }

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "iso-type=%d second-lang=%d", iso_type, second_lang);
    }

    dec->second_lang.iso_type = iso_type;
    dec->second_lang.lang = second_lang;

    info ("alsa_decoder_ac4_second_language index %d, type %d (%s), second_lang %d (%s) .\n", index,
        iso_type, ac4_lang_type_name[iso_type], second_lang, _get_ac4_lang_name (second_lang));

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_ac4_adtype_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_ac4_adtype_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = dec->ad_type;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_ac4_adtype_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_ac4_adtype (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    adec_ac4_ad_ext_type_t ad_type;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    ad_type = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!(dec->codec == ADEC_SRC_CODEC_AC4 || dec->codec == ADEC_SRC_CODEC_AC4_ATMOS))
    {
        error ("audio decoder codec is not AC4 .\n");
        goto exit;
    }

    if (!(ad_type >= ADEC_AC4_AD_TYPE_NONE && ad_type <= ADEC_AC4_AD_TYPE_VO))
    {
        error ("invalid ad type, %d .\n", ad_type);
        goto exit;
    }

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "ad-type=%d", ad_type);
    }

    dec->ad_type = ad_type;

    info ("alsa_decoder_ac4_adtype index %d adtype %d (%s) .\n", index, ad_type,
        ac4_ad_type_name[ad_type]);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_ac4_prioritize_adtype_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_ac4_prioritize_adtype_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = dec->prio_ad_type;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_ac4_prioritize_adtype_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_ac4_prioritize_adtype (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    int prio_ad_type;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    prio_ad_type = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!(dec->codec == ADEC_SRC_CODEC_AC4 || dec->codec == ADEC_SRC_CODEC_AC4_ATMOS))
    {
        error ("audio decoder codec is not AC4 .\n");
        goto exit;
    }

    if (!(prio_ad_type == TRUE || prio_ad_type == FALSE))
    {
        error ("invalid parameter %d .\n", prio_ad_type);
        goto exit;
    }

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "prio-ad-type=%d", prio_ad_type);
    }

    dec->prio_ad_type = prio_ad_type;

    info ("alsa_decoder_ac4_prioritize_adtype index %d prio_ad_type %d.\n", index, prio_ad_type);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_ac4_dialog_enhance_gain_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_ac4_dialog_enhance_gain_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
        {
            ucontrol->value.integer.value[index * 2 + 1] = dec->dialog_gain;
        }
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_ac4_dialog_enhance_gain_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_ac4_dialog_enhance_gain (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    int gain;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    gain = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "de-gain=%d", gain);
    }

    dec->dialog_gain = gain;

    info ("alsa_decoder_ac4_dialog_enhance_gain index %d, gain %d .\n", index, gain);

    ALSADEC_UNLOCK ();

    return 0;
}

static int alsa_decoder_ac4_presentation_group_index_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_ac4_presentation_group_index_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = dec->ac4_group_index;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_ac4_presentation_group_index_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_ac4_presentation_group_index (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    int group_index;
    ALSA_DECODER_INFO_T *dec = NULL;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    group_index = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!(dec->codec == ADEC_SRC_CODEC_AC4 || dec->codec == ADEC_SRC_CODEC_AC4_ATMOS))
    {
        error ("audio decoder codec is not AC4 .\n");
        goto exit;
    }

    if (group_index < 0 || group_index > ALSA_GROUP_INDEX_MAX)
    {
        error ("invalid group index, %d .\n", group_index);
        goto exit;
    }

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "pres-group-index=%d",
            (group_index == ALSA_GROUP_INDEX_MAX) ? -1 : group_index);
    }

    dec->ac4_group_index = group_index;

    info ("alsa_decoder_ac4_presentation_group_index index %d, group_index %d .\n", index,
        group_index);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_ac4_auto_admixing_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_ac4_auto_admixing_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = dec->ac4_ad_on_off;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_ac4_auto_admixing_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_ac4_auto_admixing (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    int on_off;
    ALSA_DECODER_INFO_T *dec = NULL;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    on_off = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!(dec->codec == ADEC_SRC_CODEC_AC4 || dec->codec == ADEC_SRC_CODEC_AC4_ATMOS))
    {
        error ("audio decoder codec is not AC4 .\n");
        goto exit;
    }

    if ((on_off == TRUE) && (dec->ad_type == ADEC_AC4_AD_TYPE_NONE))
    {
        error ("ac4 ad type is not setted .\n");
        goto exit;
    }

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "ad-mixing=%d", on_off);
    }

    dec->ac4_ad_on_off = on_off;

    info ("alsa_decoder_ac4_auto_admixing index %d, on_off %d .\n", index, on_off);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_ac4_associate_audio_volume_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = ALSA_ADEC_INT_MIN;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_ac4_associate_audio_volume_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = dec->associate_audio_volume;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_ac4_associate_audio_volume_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_ac4_associate_audio_volume (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    int mix_balance;
    ALSA_DECODER_INFO_T *dec = NULL;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    mix_balance = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!(dec->codec == ADEC_SRC_CODEC_AC4 || dec->codec == ADEC_SRC_CODEC_AC4_ATMOS))
    {
        error ("audio decoder codec is not AC4 .\n");
        goto exit;
    }

    if (dec->ad_type == ADEC_AC4_AD_TYPE_NONE)
    {
        error ("ac4 ad type is not setted .\n");
        goto exit;
    }

    if (mix_balance < ALSA_ASSOCIATE_MIX_BALANCE_MIN
        || mix_balance > ALSA_ASSOCIATE_MIX_BALANCE_MAX)
    {
        error ("invalid associate audio mix balance %d .\n", mix_balance);
        goto exit;
    }

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "associate-volume=%d", mix_balance);
    }

    dec->associate_audio_volume = mix_balance;

    info ("alsa_decoder_ac4_associate_audio_volume index %d, mix_balance %d .\n", index,
        mix_balance);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}


static int alsa_decoder_tp_audio_description_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_tp_audio_description_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;

    ucontrol->value.integer.value[0] = !main_audio_index;
    ucontrol->value.integer.value[1] = alsa_decoder_ad_on_off;

    for (index = 0; index < 2; index++)
    {
        debug ("alsa_decoder_tp_audio_description_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_tp_audio_description (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int main_dec_index, sub_dec_index;
    ALSA_DECODER_INFO_T *dec = NULL;
    bool on_off;

    debug_call ();

    sub_dec_index = ucontrol->value.integer.value[0];
    on_off = ucontrol->value.integer.value[1];

    if (sub_dec_index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", sub_dec_index);
        return -1;
    }

    if (!alsa_decoder_info[0].is_open)
    {
        error ("decoder is not opened, index 0. \n");
        return -1;
    }

    if (!alsa_decoder_info[1].is_open)
    {
        error ("decoder is not opened, index 1. \n");
        return -1;
    }

    main_dec_index = !sub_dec_index;

    // main decoder
    dec = &alsa_decoder_info[main_dec_index];

    ALSADEC_LOCK ();

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "audio-description=%d sub-decoder=%d", on_off, 0);
        dec->is_main_dec = TRUE;
    }

    // sub decoder
    dec = &alsa_decoder_info[sub_dec_index];

    if (dec->dec_info)
    {
        if (on_off)
            decoder_set_param (dec->dec_info, "audio-description=%d sub-decoder=%d", on_off, 1);
        else                    // AD OFF: (Main + Sub) -> (Main + Main)
            decoder_set_param (dec->dec_info, "audio-description=%d sub-decoder=%d", on_off, 0);
        dec->is_main_dec = FALSE;
    }

    ALSADEC_UNLOCK ();

    decoder_set_main_audio_index (main_dec_index);

    sndout_set_audio_desc (sub_dec_index, alsa_decoder_ad_on_off, on_off);

    alsa_decoder_ad_on_off = on_off;

    info ("decoder_tp_audio_description on_off %d audio_description_index: %d (main_audio_index: %d) .\n", on_off, sub_dec_index, main_dec_index);

    return 0;
}

static int alsa_decoder_tp_outputmode_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_tp_outputmode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * 2);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * 2] = index;

        dec = &alsa_decoder_info[index];

        if (dec->is_open)
            ucontrol->value.integer.value[index * 2 + 1] = dec->dualmono_mode;
    }

    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_tp_outputmode_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_tp_outputmode (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    adec_dualmono_mode_ext_type_t dualmono_mode;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    dualmono_mode = ucontrol->value.integer.value[1];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (!(dualmono_mode >= ADEC_DUALMONO_MODE_LR && dualmono_mode <= ADEC_DUALMONO_MODE_MIX))
    {
        error ("invalid dualmono mode, %d .\n", dualmono_mode);
        goto exit;
    }

    if (dec->dec_info)
    {
        decoder_set_param (dec->dec_info, "output-mode=%d", dualmono_mode);
    }

    dec->dualmono_mode = dualmono_mode;

    info ("alsa_decoder_tp_outputmode index %d dualmono_mode %d (%s) .\n", index,
        dualmono_mode, dualmono_name[dualmono_mode]);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_tp_audio_pts_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_tp_audio_pts_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    unsigned int pts = 0;

    index = kcontrol->private_value;
    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    decoder_get_tp_audio_pts (dec->dec_info, index, &pts);

    ucontrol->value.integer.value[0] = pts;

    debug ("decoder_tp_audio_pts_get param: %ld .\n", ucontrol->value.integer.value[0]);

    return 0;
}

static int alsa_decoder_dolby_ottmode_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_dolby_ottmode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ucontrol->value.integer.value[0] = ottmode_enable;
    ucontrol->value.integer.value[1] = atmos_locking_enable;
    for (index = 0; index < ALSA_ADEC_MAX * 2; index++)
    {
        debug ("alsa_decoder_dolby_ottmode_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_dolby_ottmode (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int i;
    int ott_enable;
    int locking_enable;
    ALSA_DECODER_INFO_T *dec = NULL;
    struct aud_block_info *mixer = NULL;

    debug_call ();
    ott_enable = ucontrol->value.integer.value[0];
    locking_enable = ucontrol->value.integer.value[1];

    if (ottmode_enable == ott_enable && locking_enable == atmos_locking_enable)
    {
        info ("same dolby ottmode bOTTEnable %d, ATMOSLockingEnable %d .\n",
            ott_enable, atmos_locking_enable);
        return 0;
    }

    if (ott_enable == FALSE && locking_enable == TRUE)
    {
        error ("invalid parameters, ottmode: %d locking_enable %d .\n", ott_enable, locking_enable);
        return -1;
    }

    ALSADEC_LOCK ();

    // mixer setting
    mixer = bm_get_block_info_by_index ("mixer", 0);
    if (mixer)
    {
        enum msmixer_mixing_mode mixing_mode = MSMIXER_MIXING_MODE_STRINGENT;

        if (ott_enable)
            mixing_mode = MSMIXER_MIXING_MODE_AGGREGATE;

        mixer_set_mixing_mode (mixer, mixing_mode);
        mixer_set_limiter (mixer, ott_enable);
    }

    for (i = 0; i < ALSA_ADEC_MAX; i++)
    {
        dec = &alsa_decoder_info[i];

        if (dec->is_open)
        {
            decoder_set_param (dec->dec_info, "audio-description=%d", ottmode_enable ? 0 : 1);
        }
    }

    // encoder setting
    sndout_set_dolby_ottmode (ott_enable, locking_enable);

    ottmode_enable = ott_enable;
    atmos_locking_enable = locking_enable;

    ALSADEC_UNLOCK ();

    info ("alsa_decoder_dolby_ottmode bOTTEnable %d, ATMOSLockingEnable %d .\n", ott_enable,
        atmos_locking_enable);
    return 0;
}

static int alsa_decoder_tp_buffer_status_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_tp_buffer_status_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    unsigned int max_size = 0;
    unsigned int free_size = 0;
    int ret = -1;

    index = kcontrol->private_value;
    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    if (dec->dec_info)
    {
        if (dec->input == ADEC_SRC_ATP0)
            decoder_get_tp_buffer_status (dec->dec_info, AUDIO_DECODER_INPUT_TP_0, &max_size,
                &free_size);
        else if (dec->input == ADEC_SRC_ATP1)
            decoder_get_tp_buffer_status (dec->dec_info, AUDIO_DECODER_INPUT_TP_1, &max_size,
                &free_size);
    }

    if (max_size == 0 && free_size == 0)
    {
        ucontrol->value.integer.value[0] = PES_BUFFER_SIZE;
        ucontrol->value.integer.value[1] = PES_BUFFER_SIZE;
    }
    else
    {
        ucontrol->value.integer.value[0] = max_size;
        ucontrol->value.integer.value[1] = free_size;
    }

    for (index = 0; index < 2; index++)
    {
        debug ("alsa_decoder_tp_buffer_status_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}

static int alsa_decoder_tp_buffer_status (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    debug_call ();
    index = kcontrol->private_value;
    info ("alsa_decoder_tp_buffer_status index %d .\n", index);
    return 0;
}

static int alsa_decoder_audio_drop_enable_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_audio_drop_enable_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    ucontrol->value.integer.value[0] = input_drop_enable;

    debug ("alsa_decoder_hbbtv_mode_get param: %ld .\n", ucontrol->value.integer.value[0]);

    return 0;
}

static int alsa_decoder_audio_drop_enable (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int i;
    bool enable = TRUE;

    debug_call ();

    enable = ucontrol->value.integer.value[0];

    if (enable == input_drop_enable)
    {
        info ("same, audio drop enable : %s\n", enable ? "true" : "false");

        return 0;
    }

    ALSADEC_LOCK ();

    for (i = 0; i < ALSA_ADEC_MAX; i++)
    {
        decoder_set_input_drop (i, enable);
    }

    input_drop_enable = enable;

    ALSADEC_UNLOCK ();

    info ("alsa_decoder_audio_drop_enable %d.\n", enable);

    return 0;
}

#ifdef SUPPORT_SOUNDBAR
#define I2S_CONTROL_COUNT   5
static int alsa_decoder_i2s_control_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = ALSA_ADEC_MAX * I2S_CONTROL_COUNT;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADEC_INT_MAX;
    return 0;
}

static int alsa_decoder_i2s_control_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index = 0;
    ALSA_DECODER_INFO_T *dec = NULL;

    memset (ucontrol->value.integer.value, 0x0, sizeof (int) * ALSA_ADEC_MAX * I2S_CONTROL_COUNT);

    for (index = 0; index < ALSA_ADEC_MAX; index++)
    {
        ucontrol->value.integer.value[index * I2S_CONTROL_COUNT] = index;

        dec = &alsa_decoder_info[index];
        if (dec->is_open)
        {
            ucontrol->value.integer.value[index * 4 + 1] = dec->i2s_hdmi_type;
            ucontrol->value.integer.value[index * 4 + 2] = dec->i2s_hdmi_ch;
            ucontrol->value.integer.value[index * 4 + 3] = dec->i2s_hdmi_freq;
            ucontrol->value.integer.value[index * 4 + 4] = dec->i2s_port_count;
        }
    }

    for (index = 0; index < ALSA_ADEC_MAX * I2S_CONTROL_COUNT; index++)
    {
        debug ("alsa_decoder_i2s_control_get param[%d]: %ld .\n", index,
            ucontrol->value.integer.value[index]);
    }

    return 0;
}

static int alsa_decoder_i2s_control (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index;
    ALSA_DECODER_INFO_T *dec = NULL;
    int i2s_hdmi_type, i2s_hdmi_ch, i2s_hdmi_freq, i2s_port_count;
    int ret = -1;

    debug_call ();

    index = ucontrol->value.integer.value[0];
    i2s_hdmi_type = ucontrol->value.integer.value[1];
    i2s_hdmi_ch = ucontrol->value.integer.value[2];
    i2s_hdmi_freq = ucontrol->value.integer.value[3];
    i2s_port_count = ucontrol->value.integer.value[4];

    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    if (i2s_hdmi_type < 0 || i2s_hdmi_type > ADEC_I2S_AUDIO_TYPE_HBR)
    {
        error ("invalid i2s type, %d .\n", i2s_hdmi_type);
        return -1;
    }

    if (i2s_hdmi_ch <= 0 || i2s_hdmi_ch > 8)
    {
        error ("invalid i2s channel, %d .\n", i2s_hdmi_ch);
        return -1;
    }

    if ((i2s_hdmi_ch % 2) == 1)
    {
        info ("invalid i2s odd channel, %d .\n", i2s_hdmi_ch);
        i2s_hdmi_ch += 1;
    }

    if (i2s_hdmi_freq < 32000 || i2s_hdmi_freq > 768000)
    {
        error ("invalid i2s frequency, %d .\n", i2s_hdmi_freq);
        return -1;
    }

    if (i2s_port_count < 1 || i2s_port_count > 4)
    {
        error ("invalid i2s port count, %d .\n", i2s_port_count);
        return -1;
    }

    //ARC : i2s_port_count = 1, e-ARC : i2s_port_count = 4
    if (i2s_port_count == 1)
    {
        if (i2s_hdmi_type == ADEC_I2S_AUDIO_TYPE_HBR)
        {
            error ("invalid i2s port count, %d type, %d .\n", i2s_port_count, i2s_hdmi_type);
            return -1;
        }

        if (i2s_hdmi_ch > 2)
        {
            error ("invalid i2s port count, %d channel, %d .\n", i2s_port_count, i2s_hdmi_ch);
            return -1;
        }
    }

    dec = &alsa_decoder_info[index];

    ALSADEC_LOCK ();

    if (!dec->is_open)
    {
        error ("can not find audio decoder, index %d .\n", index);
        goto exit;
    }

    dec->i2s_hdmi_type = i2s_hdmi_type;
    dec->i2s_hdmi_ch = i2s_hdmi_ch;
    dec->i2s_hdmi_freq = i2s_hdmi_freq;
    dec->i2s_port_count = i2s_port_count;

    info ("alsa_decoder_i2s_control index %d type %d ch %d freq %d count %d.\n",
        index, i2s_hdmi_type, i2s_hdmi_ch, i2s_hdmi_freq, i2s_port_count);

    ret = 0;
  exit:
    ALSADEC_UNLOCK ();
    return ret;
}
#endif

static int adc_open_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADC_IN_MAX;
    return 0;
}

static int adc_open_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    ucontrol->value.integer.value[0] = adc_info.is_opened;
    info ("adc_open_get %d .\n", adc_info.is_opened);
    return 0;
}

static int adc_open (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    debug_call ();
    if (adc_info.is_closed == 0)
    {
        error ("adc state is error(%d) .\n", adc_info.is_closed);
        return -1;
    }

    adc_info.is_opened = 1;
    adc_info.is_closed = 0;
    info ("adc_open %d .\n", adc_info.is_opened);
    return 0;
}

static int adc_close_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADC_IN_MAX;
    return 0;
}

static int adc_close_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    ucontrol->value.integer.value[0] = adc_info.is_closed;
    info ("adc_close_get %d .\n", adc_info.is_closed);
    return 0;
}

static int adc_close (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    debug_call ();
    if (adc_info.is_opened == 0)
    {
        error ("adc state is error(%d %d) .\n", adc_info.is_opened, adc_info.adc_port_index);
        return -1;
    }

    adc_info.is_closed = 1;
    adc_info.is_opened = 0;
    adc_info.adc_port_index = ALSA_ADC_IN_MAX;
    info ("adc_close %d .\n", adc_info.is_closed);
    return 0;
}

static int adc_connect_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADC_IN_MAX;
    return 0;
}

static int adc_connect_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    ucontrol->value.integer.value[0] = adc_info.adc_port_index;
    info ("adc_connect_get %d .\n", adc_info.adc_port_index);
    return 0;
}

static int adc_connect (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    debug_call ();
    if (adc_info.is_opened == 0 || adc_info.adc_port_index != ALSA_ADC_IN_MAX)
    {
        error ("adc state is error(%d %d) .\n", adc_info.is_opened, adc_info.adc_port_index);
        return -1;
    }

    adc_info.adc_port_index = ucontrol->value.integer.value[0];
    aud_hal_set_adc_port_number (adc_info.adc_port_index);
    info ("adc_connect %d .\n", adc_info.adc_port_index);
    return 0;
}

static int adc_disconnect_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_ADC_IN_MAX;
    return 0;
}

static int adc_disconnect_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    if (adc_info.is_opened == 0)
    {
        error ("adc state is error(%d) .\n", adc_info.is_opened);
        return -1;
    }

    if (adc_info.adc_port_index == ALSA_ADC_IN_MAX)
        ucontrol->value.integer.value[0] = 1;
    else
        ucontrol->value.integer.value[0] = 0;
    info ("adc_disconnect_get %d .\n", adc_info.adc_port_index);
    return 0;
}

static int adc_disconnect (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    debug_call ();
    if (adc_info.is_opened == 0 || adc_info.adc_port_index == ALSA_ADC_IN_MAX)
    {
        error ("adc state is error(%d %d) .\n", adc_info.is_opened, adc_info.adc_port_index);
        return -1;
    }

    adc_info.adc_port_index = ALSA_ADC_IN_MAX;
    info ("adc_disconnect %d .\n", adc_info.adc_port_index);
    return 0;
}

static int displayport_audiomode_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = DISPLAYPORT_AUDIO_UNKNOWN;
    uinfo->value.integer.max = DISPLAYPORT_AUDIO_NO_AUDIO;
    return 0;
}

static int displayport_audiomode_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index = 0;

    index = kcontrol->private_value;

    if (index >= ALSA_DP_IN_MAX)
    {
        error ("invalid DP index, index %d .\n", index);
        return -1;
    }

    ucontrol->value.integer.value[0] = DISPLAYPORT_AUDIO_NO_AUDIO;

    debug ("displayport_audiomode_get[%d]: %ld .\n", index, ucontrol->value.integer.value[index]);

    return 0;
}

static int displayport_copyprotectioninfo_info (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = DISPLAYPORT_AUDIO_COPY_FREE;
    uinfo->value.integer.max = DISPLAYPORT_AUDIO_COPY_NEVER;
    return 0;
}

static int displayport_copyprotectioninfo_get (struct snd_kcontrol *kcontrol,
    struct snd_ctl_elem_value *ucontrol)
{
    int index = 0;

    index = kcontrol->private_value;

    if (index >= ALSA_DP_IN_MAX)
    {
        error ("invalid DP index, index %d .\n", index);
        return -1;
    }

    ucontrol->value.integer.value[0] = DISPLAYPORT_AUDIO_COPY_FREE;

    debug ("displayport_copyprotectioninfo_get[%d]: %ld .\n", index,
        ucontrol->value.integer.value[index]);

    return 0;
}

static const struct snd_kcontrol_new decoder_controls[] = {
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_OPEN,
            .info = alsa_decoder_open_info,
            .get = alsa_decoder_open_get,
            .put = alsa_decoder_open,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_CLOSE,
            .info = alsa_decoder_close_info,
            .get = alsa_decoder_close_get,
            .put = alsa_decoder_close,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_CONNECT,
            .info = alsa_decoder_connect_info,
            .get = alsa_decoder_connect_get,
            .put = alsa_decoder_connect,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_DISCONNECT,
            .info = alsa_decoder_disconnect_info,
            .get = alsa_decoder_disconnect_get,
            .put = alsa_decoder_disconnect,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_CODEC,
            .info = alsa_decoder_codec_info,
            .get = alsa_decoder_codec_get,
            .put = alsa_decoder_codec,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_START,
            .info = alsa_decoder_start_info,
            .get = alsa_decoder_start_get,
            .put = alsa_decoder_start,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_STOP,
            .info = alsa_decoder_stop_info,
            .get = alsa_decoder_stop_get,
            .put = alsa_decoder_stop,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_MAXCAPACITY,
            .info = alsa_decoder_capacity_info,
            .get = alsa_decoder_capacity_get,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_USERMAXCAPACITY,
            .info = alsa_decoder_user_capacity_info,
            .get = alsa_decoder_user_capacity_get,
            .put = alsa_decoder_user_capacity,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = AHDMI_PORT0_AUDIOMODE,
            .info = alsa_decoder_hdmi_audiomode_info,
            .get = alsa_decoder_hdmi_audiomode_get,
            .private_value = 0,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = AHDMI_PORT1_AUDIOMODE,
            .info = alsa_decoder_hdmi_audiomode_info,
            .get = alsa_decoder_hdmi_audiomode_get,
            .private_value = 1,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = AHDMI_PORT2_AUDIOMODE,
            .info = alsa_decoder_hdmi_audiomode_info,
            .get = alsa_decoder_hdmi_audiomode_get,
            .private_value = 2,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = AHDMI_PORT3_AUDIOMODE,
            .info = alsa_decoder_hdmi_audiomode_info,
            .get = alsa_decoder_hdmi_audiomode_get,
            .private_value = 3,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = AHDMI_PORT0_COPYPROTECTIONINFO,
            .info = alsa_decoder_hdmi_copyprotectioninfo_info,
            .get = alsa_decoder_hdmi_copyprotectioninfo_get,
            .private_value = 0,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = AHDMI_PORT1_COPYPROTECTIONINFO,
            .info = alsa_decoder_hdmi_copyprotectioninfo_info,
            .get = alsa_decoder_hdmi_copyprotectioninfo_get,
            .private_value = 1,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = AHDMI_PORT2_COPYPROTECTIONINFO,
            .info = alsa_decoder_hdmi_copyprotectioninfo_info,
            .get = alsa_decoder_hdmi_copyprotectioninfo_get,
            .private_value = 2,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = AHDMI_PORT3_COPYPROTECTIONINFO,
            .info = alsa_decoder_hdmi_copyprotectioninfo_info,
            .get = alsa_decoder_hdmi_copyprotectioninfo_get,
            .private_value = 3,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC0_INFO,
            .info = alsa_decoder_adecinfo_info,
            .get = alsa_decoder_adecinfo_get,
            .put = alsa_decoder_adecinfo,
            .private_value = 0,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC1_INFO,
            .info = alsa_decoder_adecinfo_info,
            .get = alsa_decoder_adecinfo_get,
            .put = alsa_decoder_adecinfo,
            .private_value = 1,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC2_INFO,
            .info = alsa_decoder_adecinfo_info,
            .get = alsa_decoder_adecinfo_get,
            .put = alsa_decoder_adecinfo,
            .private_value = 2,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC3_INFO,
            .info = alsa_decoder_adecinfo_info,
            .get = alsa_decoder_adecinfo_get,
            .put = alsa_decoder_adecinfo,
            .private_value = 3,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_DOLBYDRCMODE,
            .info = alsa_decoder_drcmode_info,
            .get = alsa_decoder_drcmode_get,
            .put = alsa_decoder_drcmode,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_DEFAULTPRL,
            .info = alsa_decoder_default_prl_info,
            .get = alsa_decoder_default_prl_get,
            .put = alsa_decoder_default_prl,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_DOWNMIXMODE,
            .info = alsa_decoder_dmxmode_info,
            .get = alsa_decoder_dmxmode_get,
            .put = alsa_decoder_dmxmode,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_AC4_AUTO1STLANG,
            .info = alsa_decoder_ac4_first_language_info,
            .get = alsa_decoder_ac4_first_language_get,
            .put = alsa_decoder_ac4_first_language,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_AC4_AUTO2NDLANG,
            .info = alsa_decoder_ac4_second_language_info,
            .get = alsa_decoder_ac4_second_language_get,
            .put = alsa_decoder_ac4_second_language,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_AC4_AUTO_ADTYPE,
            .info = alsa_decoder_ac4_adtype_info,
            .get = alsa_decoder_ac4_adtype_get,
            .put = alsa_decoder_ac4_adtype,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_AC4_AUTO_PRIORITIZE_ADTYPE,
            .info = alsa_decoder_ac4_prioritize_adtype_info,
            .get = alsa_decoder_ac4_prioritize_adtype_get,
            .put = alsa_decoder_ac4_prioritize_adtype,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_TP_AUDIODESCRIPTION,
            .info = alsa_decoder_tp_audio_description_info,
            .get = alsa_decoder_tp_audio_description_get,
            .put = alsa_decoder_tp_audio_description,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_TP_DECODER_OUTPUTMODE,
            .info = alsa_decoder_tp_outputmode_info,
            .get = alsa_decoder_tp_outputmode_get,
            .put = alsa_decoder_tp_outputmode,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC0_TP_PTS,
            .info = alsa_decoder_tp_audio_pts_info,
            .get = alsa_decoder_tp_audio_pts_get,
            .private_value = 0,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC1_TP_PTS,
            .info = alsa_decoder_tp_audio_pts_info,
            .get = alsa_decoder_tp_audio_pts_get,
            .private_value = 1,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC2_TP_PTS,
            .info = alsa_decoder_tp_audio_pts_info,
            .get = alsa_decoder_tp_audio_pts_get,
            .private_value = 2,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC3_TP_PTS,
            .info = alsa_decoder_tp_audio_pts_info,
            .get = alsa_decoder_tp_audio_pts_get,
            .private_value = 3,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_AC4_DIALOGENHANCEGAIN,
            .info = alsa_decoder_ac4_dialog_enhance_gain_info,
            .get = alsa_decoder_ac4_dialog_enhance_gain_get,
            .put = alsa_decoder_ac4_dialog_enhance_gain,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_DOLBY_OTTMODE,
            .info = alsa_decoder_dolby_ottmode_info,
            .get = alsa_decoder_dolby_ottmode_get,
            .put = alsa_decoder_dolby_ottmode,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC0_TP_BUFFERSTATUS,
            .info = alsa_decoder_tp_buffer_status_info,
            .get = alsa_decoder_tp_buffer_status_get,
            .put = alsa_decoder_tp_buffer_status,
            .private_value = 0,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC1_TP_BUFFERSTATUS,
            .info = alsa_decoder_tp_buffer_status_info,
            .get = alsa_decoder_tp_buffer_status_get,
            .put = alsa_decoder_tp_buffer_status,
            .private_value = 1,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC2_TP_BUFFERSTATUS,
            .info = alsa_decoder_tp_buffer_status_info,
            .get = alsa_decoder_tp_buffer_status_get,
            .put = alsa_decoder_tp_buffer_status,
            .private_value = 2,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC3_TP_BUFFERSTATUS,
            .info = alsa_decoder_tp_buffer_status_info,
            .get = alsa_decoder_tp_buffer_status_get,
            .put = alsa_decoder_tp_buffer_status,
            .private_value = 3,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_AC4_PRES_GROUP_IDX,
            .info = alsa_decoder_ac4_presentation_group_index_info,
            .get = alsa_decoder_ac4_presentation_group_index_get,
            .put = alsa_decoder_ac4_presentation_group_index,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_AC4_AUTO_ADMIXING,
            .info = alsa_decoder_ac4_auto_admixing_info,
            .get = alsa_decoder_ac4_auto_admixing_get,
            .put = alsa_decoder_ac4_auto_admixing,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_AC4_ASSOCIATE_AUDIO_VOLUME,
            .info = alsa_decoder_ac4_associate_audio_volume_info,
            .get = alsa_decoder_ac4_associate_audio_volume_get,
            .put = alsa_decoder_ac4_associate_audio_volume,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_AUDIO_DROP_ENABLE,
            .info = alsa_decoder_audio_drop_enable_info,
            .get = alsa_decoder_audio_drop_enable_get,
            .put = alsa_decoder_audio_drop_enable,
        },
#ifdef SUPPORT_SOUNDBAR
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_I2S_CONTROL,
            .info = alsa_decoder_i2s_control_info,
            .get = alsa_decoder_i2s_control_get,
            .put = alsa_decoder_i2s_control,
        },
#endif
};

static const struct snd_kcontrol_new renderer_controls[] = {
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_SYNCMODE,
            .info = alsa_decoder_syncmode_info,
            .get = alsa_decoder_syncmode_get,
            .put = alsa_decoder_syncmode,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_TRICKMODE,
            .info = alsa_decoder_trickmode_info,
            .get = alsa_decoder_trickmode_get,
            .put = alsa_decoder_trickmode,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_MASTER_SYNCMODE,
            .info = alsa_decoder_master_syncmode_info,
            .get = alsa_decoder_master_syncmode_get,
            .put = alsa_decoder_master_syncmode,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADEC_LIPSYNC_OFFSET,
            .info = alsa_decoder_lipsyc_offset_info,
            .get = alsa_decoder_lipsyc_offset_get,
            .put = alsa_decoder_lipsyc_offset,
        },
};

static const struct snd_kcontrol_new adc_controls[] = {
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADC_OPEN,
            .info = adc_open_info,
            .get = adc_open_get,
            .put = adc_open,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADC_CLOSE,
            .info = adc_close_info,
            .get = adc_close_get,
            .put = adc_close,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADC_CONNECT,
            .info = adc_connect_info,
            .get = adc_connect_get,
            .put = adc_connect,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = ADC_DISCONNECT,
            .info = adc_disconnect_info,
            .get = adc_disconnect_get,
            .put = adc_disconnect,
        },
};

static const struct snd_kcontrol_new displayport_controls[] = {
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = DP_PORT0_AUDIOMODE,
            .info = displayport_audiomode_info,
            .get = displayport_audiomode_get,
            .private_value = 0,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = DP_PORT1_AUDIOMODE,
            .info = displayport_audiomode_info,
            .get = displayport_audiomode_get,
            .private_value = 1,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = DP_PORT0_COPYPROTECTIONINFO,
            .info = displayport_copyprotectioninfo_info,
            .get = displayport_copyprotectioninfo_get,
            .private_value = 0,
        },
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = DP_PORT1_COPYPROTECTIONINFO,
            .info = displayport_copyprotectioninfo_info,
            .get = displayport_copyprotectioninfo_get,
            .private_value = 1,
        },
};

static int _proc_hdmi_status_show (struct seq_file *m, void *data)
{
    int index = main_audio_index;
    int hdmi_link_index = 0;
    int connected = 0;
    int existAudioData = 0;
    char *codecName = "UNKNOWN";
    int samplingRate = 0;
    struct hdmi_codec
    {
        LX_HDMI_AUDIO_TYPE_T codec;
        char *name;
    } hdmi_codec_info[] = {
        /* *INDENT-OFF* */
        { LX_HDMI_AUDIO_DVI, "DVI" },
        { LX_HDMI_AUDIO_NO_AUDIO, "NO_AUDIO" },
        { LX_HDMI_AUDIO_PCM, "PCM" },
        { LX_HDMI_AUDIO_AC3, "AC3" },
        { LX_HDMI_AUDIO_DTS, "DTS" },
        { LX_HDMI_AUDIO_AAC, "AAC" },
        { LX_HDMI_AUDIO_DEFAULT, "DEFAULT" },
        { LX_HDMI_AUDIO_MPEG, "MPEG" },
        { LX_HDMI_AUDIO_DTS_HD_MA, "DTS_HD_MA" },
        { LX_HDMI_AUDIO_DTS_EXPRESS, "DTS_EXPRESS" },
        { LX_HDMI_AUDIO_DTS_CD, "DTS_CD" },
        { LX_HDMI_AUDIO_EAC3, "EAC3" },
        { LX_HDMI_AUDIO_EAC3_ATMOS, "EAC3_ATMOS" },
        { LX_HDMI_AUDIO_MAT, "MAT"},
        { LX_HDMI_AUDIO_MAT_ATMOS, "MAT_ATMOS" },
        { LX_HDMI_AUDIO_TRUE_HD, "TRUE_HD" },
        { LX_HDMI_AUDIO_TRUE_HD_ATMOS, "TRUE_HD_ATMOS" },
        { LX_HDMI_AUDIO_AC3_IEC60958, "AC3_IEC60958" },
        { LX_HDMI_AUDIO_EAC3_IEC60958, "EAC3_IEC60958" },
        { LX_HDMI_AUDIO_DTS_HD, "DTS_HD" },
        { LX_HDMI_AUDIO_DTS_HD_HRA, "DTS_HD_HRA" },
        { LX_HDMI_AUDIO_UNKNOWN_AC3, "UNKNOWN_AC3" },
        { LX_HDMI_AUDIO_UNKNOWN_DTS, "UNKNOWN_DTS" },
        { LX_HDMI_AUDIO_UNKNOWN_AAC, "UNKNOWN_AAC" },
        { LX_HDMI_AUDIO_UNKNOWN_MPEG, "UNKNOWN_MPEG" },
        { LX_HDMI_AUDIO_UNKNOWN_EAC3, "UNKNOWN_EAC3" },
        { LX_HDMI_AUDIO_UNKNOWN_MAT, "UNKNOWN_MAT" },
        { LX_HDMI_AUDIO_UNKNOWN_DTS_HD, "UNKNOWN_DTS_HD" },
        { LX_HDMI_AUDIO_UNKNOWN_DTS_HD_HRA, "UNKNOWN_DTS_HD_HRA" },
        /* *INDENT-ON* */
    };
    int n_param = 0;
    int cts_param = 0;

    if (index >= 0 && index < ALSA_ADEC_MAX)
    {
        ALSA_DECODER_INFO_T *dec = NULL;
        LX_HDMI_AUDIO_INFO_T hdmiAudioInfo;
        LX_HDMI_AUDIO_INFO_ACR_T hdmiAudioInfoAcr;
        int ret;
        dec = &alsa_decoder_info[index];
        if (dec->is_open
            && ((dec->input >= ADEC_SRC_HDMI_PORT0 && dec->input <= ADEC_SRC_HDMI_PORT3)
                || (dec->input == ADEC_SRC_HDMI_DEFAULT)))
        {
            connected = 1;
            hdmi_link_index = dec->input - ADEC_SRC_HDMI_PORT0;
            ret =
                hdmi_get_audioinfo (hdmi_link_index, &hdmiAudioInfo, sizeof (LX_HDMI_AUDIO_INFO_T));

            noti ("ret=%d port=%d type=%d freq=%d\n", ret, hdmi_link_index,
                hdmiAudioInfo.audioType, hdmiAudioInfo.samplingFreq);

            if (ret == RET_OK)
            {
                LX_HDMI_AUDIO_TYPE_T codec = hdmiAudioInfo.audioType;
                int i;

                if (codec != LX_HDMI_AUDIO_DVI && codec != LX_HDMI_AUDIO_NO_AUDIO
                    && codec != LX_HDMI_AUDIO_DEFAULT)
                    existAudioData = 1;

                for (i = 0; i < sizeof (hdmi_codec_info) / sizeof (hdmi_codec_info[0]); i++)
                {
                    if (hdmi_codec_info[i].codec == codec)
                        codecName = hdmi_codec_info[i].name;
                }

                samplingRate = hdmiAudioInfo.samplingFreq;
            }

            ret =
                hdmi_get_audioacrinfo (hdmi_link_index, &hdmiAudioInfoAcr,
                sizeof (LX_HDMI_AUDIO_INFO_ACR_T));

            noti ("ret=%d N=%d CTS=%d\n", ret, hdmiAudioInfoAcr.n_param,
                hdmiAudioInfoAcr.cts_param);

            if (ret == RET_OK)
            {
                n_param = hdmiAudioInfoAcr.n_param;
                cts_param = hdmiAudioInfoAcr.cts_param;
            }
        }
    }
    else
    {
        noti ("deocder(%d) is not opend or not connected with HDMI\n", index);
    }
    noti ("HDMIConnected=%d AudioData=%d\n", connected, existAudioData);

    seq_printf (m, "HDMIConnected=%d\n", connected);
    seq_printf (m, "AudioData=%d\n", existAudioData);
    seq_printf (m, "Codec=%s\n", codecName);
    seq_printf (m, "SamplingRate=%d\n", samplingRate);
    seq_printf (m, "N=%d\n", n_param);
    seq_printf (m, "CTS=%d\n", cts_param);
    return 0;
}

static int _proc_hdmi_status_open (struct inode *inode, struct file *file)
{
    int ret;
    ret = single_open (file, _proc_hdmi_status_show, NULL);

    return ret;
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops _proc_hdmi_status_fops = {
    .proc_open = _proc_hdmi_status_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};
#else
static struct file_operations _proc_hdmi_status_fops = {
    .open = _proc_hdmi_status_open,.read = seq_read,.llseek = seq_lseek,.release = single_release,
};
#endif

static int _proc_adec_status_show (struct seq_file *m, void *data)
{
    int index = 0;
    ALSA_INPUT_INFO_T *inp = NULL;
    ALSA_DECODER_INFO_T *dec = NULL;
    ALSA_RENDERER_INFO_T *ren = NULL;
    adec_src_port_index_ext_type_t inputPort = ADEC_SRC_UNKNOWN;
    int isStarted = 0;
    adec_src_codec_ext_type_t usercodec = ADEC_SRC_CODEC_UNKNOWN;
    adec_src_codec_ext_type_t curCodec = ADEC_SRC_CODEC_UNKNOWN;
    adec_src_codec_ext_type_t srcCodec = ADEC_SRC_CODEC_UNKNOWN;
    unsigned int srcBitRate = 0;
    unsigned int srcSamplingRate = 0;
    unsigned int srcChannel = 0;
    unsigned int outputChannel = 0;
    unsigned int pts = 0;
    unsigned int overflow_count = 0;
    int firstLang = 0;
    int drc = ADEC_DOLBY_LINE_MODE;
    int downmix = ADEC_LORO_MODE;
    bool sync = FALSE;
    adec_trick_mode_ext_type_t trick = ADEC_TRICK_NONE;
    adec_dualmono_mode_ext_type_t dualmono = ADEC_DUALMONO_MODE_LR;
    int gain = 0, mute = 0, delay = 0;
    int ease_gain = 0, ease_duration = 0;
    bool ad = false;
    int default_prl = 0;
#ifdef SUPPORT_SOUNDBAR
    int i2s_hdmi_type = 0;
    int i2s_hdmi_ch = 0;
    int i2s_hdmi_freq = 0;
    int i2s_port_count = 0;
#endif

    index = *(int *) m->private;
    if (index >= ALSA_ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    inp = &alsa_input_info[index];
    dec = &alsa_decoder_info[index];
    ren = &alsa_renderer_info[index];

    if (dec->is_open)
    {
        inputPort = dec->input;
        if (inputPort < ADEC_SRC_UNKNOWN || inputPort > ADEC_SRC_HDMI_DEFAULT)
            inputPort = ADEC_SRC_UNKNOWN;
        isStarted = dec->is_started;
        usercodec = dec->codec;
        if (dec->dec_info != NULL)
        {
            struct decoded_info info = { };

            decoder_get_decoded_info (dec->dec_info, &info);

            if (dec->src_format == ADEC_SRC_CODEC_UNKNOWN)
                srcCodec = decoder_get_source_codec (dec->codec, &info);
            else
                srcCodec = dec->src_format;

            if (atmos_decoding_enable == TRUE)
                curCodec = srcCodec;
            else
                curCodec = dec->codec;

            srcBitRate = info.avg_bit_rate;
            srcSamplingRate = info.sampling_rate;
            // source channel 정보 필요한지 확인
            srcChannel = info.channels;
            outputChannel = info.channels;
        }
        firstLang = dec->first_lang.lang;
        drc = dec->drc;
        downmix = dec->downmix;
        sync = ren->sync;
        trick = ren->trick;
        dualmono = dec->dualmono_mode;

        if (dec->is_started)
            decoder_get_tp_audio_pts (dec->dec_info, index, &pts);
    }

    if (sndout_get_input_info (index, &gain, &mute, &delay) < 0)
    {
        error ("sndout_get_input_info(index=%d) err\n", index);
    }
    if (sndout_get_gain_duration_info (index, &ease_gain, &ease_duration) < 0)
    {
        error ("sndout_get_gain_duration_info(index=%d) err\n", index);
    }

    if (inp->input_info)
        input_get_overflow_count (inp->input_info, &overflow_count);

    ad = alsa_decoder_ad_on_off;
    default_prl = dec->default_prl;
#ifdef SUPPORT_SOUNDBAR
    i2s_hdmi_type = dec->i2s_hdmi_type;
    i2s_hdmi_ch = dec->i2s_hdmi_ch;
    i2s_hdmi_freq = dec->i2s_hdmi_freq;
    i2s_port_count = dec->i2s_port_count;
#endif

    seq_printf (m, "AdecPortNum=%d\n", index);
    seq_printf (m, "Open=%d\n", dec->is_open);
    seq_printf (m, "Connect=%s\n", adec_src_port_type[inputPort]);
    seq_printf (m, "Start=%d\n", isStarted);
    seq_printf (m, "UserCodec=%s\n", _get_codec_name (usercodec));
    seq_printf (m, "CurCodec=%s\n", _get_codec_name (curCodec));
    seq_printf (m, "SrcCodec=%s\n", _get_codec_name (srcCodec));
    seq_printf (m, "SrcBitrate=%d\n", srcBitRate);
    seq_printf (m, "SrcSamplingRate=%d\n", srcSamplingRate);
    seq_printf (m, "SrcChannel=%d\n", srcChannel);
    seq_printf (m, "OutputCodec=%s\n", "PCM");
    seq_printf (m, "OutputChannel=%d\n", outputChannel);
    seq_printf (m, "PTS=%u\n", pts);
    seq_printf (m, "Language=%d\n", firstLang); // TODO: convert int to ascii
    seq_printf (m, "DolbyDRCMode=%s\n", drc_name[drc]);
    seq_printf (m, "DownmixMode=%s\n", downmix_name[downmix]);
    seq_printf (m, "SyncMode=%d\n", sync);
    seq_printf (m, "TrickMode=%s\n", trick_name[trick]);
    seq_printf (m, "DualmonoMode=%s\n", dualmono_name[dualmono]);
    seq_printf (m, "Gain=0x%X\n", gain);
    seq_printf (m, "Mute=%d\n", mute);
    seq_printf (m, "Delay=%d\n", delay);
    seq_printf (m, "Audio Description=%d\n", ad);
    seq_printf (m, "EaseGain=%d\n", ease_gain);
    seq_printf (m, "EaseDuration=%d\n", ease_duration);
    seq_printf (m, "DefaultPRL=%d\n", default_prl);
    seq_printf (m, "Overflow=%d\n", overflow_count);
#ifdef SUPPORT_SOUNDBAR
    seq_printf (m, "I2SAudioType=%d\n", i2s_hdmi_type);
    seq_printf (m, "I2SChannelNumber=%d\n", i2s_hdmi_ch);
    seq_printf (m, "I2SSamplingFrequency=%d\n", i2s_hdmi_freq);
    seq_printf (m, "I2SPortCount=%d\n", i2s_port_count);
#endif
    seq_printf (m, "\n");

    return 0;
}

static int _proc_adec_status_open (struct inode *inode, struct file *file)
{
    int ret;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    ret = single_open (file, _proc_adec_status_show, pde_data (inode));
#else
    ret = single_open (file, _proc_adec_status_show, PDE_DATA (inode));
#endif
    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops _proc_adec_status_fops = {
    .proc_open = _proc_adec_status_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};
#else
static struct file_operations _proc_adec_status_fops = {
    .open = _proc_adec_status_open,.read = seq_read,.llseek = seq_lseek,.release = single_release,
};
#endif

extern struct proc_dir_entry *aproc_seetv;
static int decoder_index[2] = {
    0, 1
};

int register_decoder_kcontrols (struct snd_soc_card *card)
{
    int ret = 0;
    ret = snd_soc_add_card_controls (card, decoder_controls, ARRAY_SIZE (decoder_controls));
    if (ret != RET_OK)
    {
        error ("add control is failed (ret %d)\n", ret);
        return ret;
    }

    ret = snd_soc_add_card_controls (card, renderer_controls, ARRAY_SIZE (renderer_controls));
    if (ret != RET_OK)
    {
        error ("add control is failed (ret %d)\n", ret);
        return ret;
    }

    ret = snd_soc_add_card_controls (card, adc_controls, ARRAY_SIZE (adc_controls));
    if (ret != RET_OK)
    {
        error ("add control is failed (ret %d)\n", ret);
        return ret;
    }

    ret = snd_soc_add_card_controls (card, displayport_controls, ARRAY_SIZE (displayport_controls));
    if (ret != RET_OK)
    {
        error ("add control is failed (ret %d)\n", ret);
        return ret;
    }

    // create proc node for debug status
    proc_create_data ("adec.p0", 0440, aproc_seetv, &_proc_adec_status_fops, &decoder_index[0]);
    proc_create_data ("adec.p1", 0440, aproc_seetv, &_proc_adec_status_fops, &decoder_index[1]);
    proc_create_data ("hdmi", 0440, aproc_seetv, &_proc_hdmi_status_fops, NULL);
    info ("completed \n");
    return ret;
}
