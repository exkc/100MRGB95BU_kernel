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
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0)
#include <linux/sched/signal.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "log.h"

#include "aud_kapi.h"
#include "aapi.h"
#include "block.h"
#include "block_manager.h"
#include "decoder.h"
#include "renderer.h"
#include "clock.h"
#include "mixer.h"
#include "output.h"
#include "encoder.h"
#include "hal/hal.h"

#include "notifier.h"
#include "module_list.h"
#include "kaimc.h"
#include "module/adec_module_list.h"

logm_define (amedia, log_level_noti);
#define trace(fmt,args...)  logm_trace(amedia,fmt,##args)
#define debug(fmt,args...)  logm_debug(amedia,fmt,##args)
#define info(fmt,args...)   logm_info(amedia,fmt,##args)
#define noti(fmt,args...)   logm_noti(amedia,fmt,##args)
#define warn(fmt,args...)   logm_warning(amedia,fmt,##args)
#define error(fmt,args...)  logm_error(amedia,fmt,##args)

#define ADEC_MAX 2
#define AREN_MAX 10

#define DEFAULT_PRL_MIN (-31)
#define DEFAULT_PRL_MAX (0)
#define INVALID_DEFAULT_PRL (0x7FFFFFFF)
#define MOD_REF_PORT(__X__)             (((__X__)&0xff) | 0x200)

#if defined(CHIP_NAME_m23) || defined(CHIP_NAME_o22) || defined(CHIP_NAME_o24) || defined(CHIP_NAME_o26)
#define VDEC_AV_LIPSYNC_BASE (0xCE0008DC)
#else
#error "Please Define Chip Definition"
#endif

typedef struct
{
    struct aud_block_info *dec_info;
    struct mutex lock;

    bool is_open;
    bool is_started;
    enum audio_decoder_codec codec;

    int proc_id;
} ADECODER_INFO_T;


typedef struct
{
    struct aud_block_info *ren_info;
    struct mutex lock;

    bool is_open;

    enum md_clock_type clock_type;

    aren_pcm_info_t pcm_info;

    bool vsp_mode;

    int proc_id;

    int msgq_id;
    int pid_to_signal;
} ARENDERER_INFO_T;

static ADECODER_INFO_T adecoder_info[ADEC_MAX] = {
    {.lock = __MUTEX_INITIALIZER (adecoder_info[0].lock)},
    {.lock = __MUTEX_INITIALIZER (adecoder_info[1].lock)},
};

static ARENDERER_INFO_T arenderer_info[AREN_MAX] = {
    {.lock = __MUTEX_INITIALIZER (arenderer_info[0].lock)},
    {.lock = __MUTEX_INITIALIZER (arenderer_info[1].lock)},
    {.lock = __MUTEX_INITIALIZER (arenderer_info[2].lock)},
    {.lock = __MUTEX_INITIALIZER (arenderer_info[3].lock)},
    {.lock = __MUTEX_INITIALIZER (arenderer_info[4].lock)},
    {.lock = __MUTEX_INITIALIZER (arenderer_info[5].lock)},
    {.lock = __MUTEX_INITIALIZER (arenderer_info[6].lock)},
    {.lock = __MUTEX_INITIALIZER (arenderer_info[7].lock)},
    {.lock = __MUTEX_INITIALIZER (arenderer_info[8].lock)},
    {.lock = __MUTEX_INITIALIZER (arenderer_info[9].lock)},
};

#define CODEC_NAME(id)  {AUDIO_DECODER_CODEC_##id, #id}

#define ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK(_index) \
    if (_index < 0 || _index >= ADEC_MAX) \
    { \
        error ("invalid audio decoder index, index %d .\n", _index); \
        return -1; \
    } \
    dec = &adecoder_info[_index]; \
    mutex_lock (&dec->lock); \
    if (!dec->is_open) \
    { \
        error ("can not find audio decoder .\n"); \
	    mutex_unlock (&dec->lock); \
        return -1; \
    }

#define ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK(_index) \
    if (_index < 0 || _index >= AREN_MAX) \
    { \
        error ("invalid audio renderer index, index %d .\n", _index); \
        return -1; \
    } \
    ren = &arenderer_info[_index]; \
    mutex_lock (&ren->lock); \
    if (!ren->is_open) \
    { \
        error ("can not find audio renderer .\n"); \
	    mutex_unlock (&ren->lock); \
        return -1; \
    }

struct str_table
{
    int id;
    const char *name;
};

static const struct str_table _codec_name[] = {
    CODEC_NAME (UNKNOWN),
    CODEC_NAME (PCM),
    CODEC_NAME (AC3),
    CODEC_NAME (EAC3),
    CODEC_NAME (AC4),
    CODEC_NAME (MAT),
    CODEC_NAME (TRUE_HD),
    CODEC_NAME (AAC),
    CODEC_NAME (MP3),
    CODEC_NAME (MPEG_H),
    CODEC_NAME (DRA),
#ifdef SUPPORT_WMA
    CODEC_NAME (WMA_PRO),
#endif
    CODEC_NAME (VORBIS),
    CODEC_NAME (AMR_WB),
    CODEC_NAME (AMR_NB),
    CODEC_NAME (ADPCM),
    CODEC_NAME (FLAC),
    CODEC_NAME (OPUS),
    CODEC_NAME (AAC_ELD),
    CODEC_NAME (RA8),
    {}
};

static const char *_get_codec_name (enum audio_decoder_codec codec)
{
    int i;

    for (i = 0; i < sizeof (_codec_name) / sizeof (_codec_name[0]); i++)
    {
        if (_codec_name[i].id == codec)
            return _codec_name[i].name;
    }

    return _codec_name[0].name;
}

int adecoder_open (int index)
{
    ADECODER_INFO_T *dec = NULL;
#ifdef SUPPORT_SOUNDBAR
    int opened_index = -1;
#endif
    int ret = -1;

    if (index < 0 || index >= ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &adecoder_info[index];

    mutex_lock (&dec->lock);

    if (dec->is_open || (bm_get_block_info_by_index ("decoder", index) != NULL))
    {
        error ("can not open audio decoder. already opened index %d", index);
        goto exit;
    }

#ifdef SUPPORT_SOUNDBAR
    opened_index = decoder_get_already_opened_index ();
    if (opened_index >= 0)
    {
        error ("can not open audio decoder. already opened index %d\n", opened_index);
        goto exit;
    }
#endif

    dec->dec_info = bm_create_block ("decoder", index);
    dec->is_open = TRUE;
    dec->proc_id = -1;

    info ("adecoder_open index %d .\n", index);

    ret = 0;
  exit:
    mutex_unlock (&dec->lock);

    return ret;
}

int adecoder_close (int index)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    if (dec->is_started)
    {
        decoder_unregister_event (dec->dec_info, AUDIO_DECODER_EVENT_INFO);

        if (dec->codec == AUDIO_DECODER_CODEC_MPEG_H)
            decoder_unregister_event (dec->dec_info, AUDIO_DECODER_EVENT_MPEGH_UI);
    }

    bm_destroy_block (dec->dec_info);

    dec->is_open = FALSE;
    dec->is_started = FALSE;
    dec->codec = AUDIO_DECODER_CODEC_UNKNOWN;
    dec->dec_info = NULL;

    mutex_unlock (&dec->lock);

    info ("adecoder_close index %d .\n", index);

    return 0;
}

int adecoder_start (int index)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_register_event (dec->dec_info, AUDIO_DECODER_EVENT_INFO, decoder_decoded_info_cb, true);
#ifdef SUPPORT_SOUNDBAR
    decoder_register_event (dec->dec_info, AUDIO_DECODER_EVENT_DEC_ID_CHANGED,
        decoder_module_id_changed_cb, true);
#endif
    decoder_connect (dec->dec_info);

    if (dec->codec == AUDIO_DECODER_CODEC_MPEG_H)
    {
        decoder_register_event (dec->dec_info, AUDIO_DECODER_EVENT_MPEGH_UI,
            decoder_mpegh_ui_param_info_cb, true);
    }

    dec->is_started = TRUE;

    mutex_unlock (&dec->lock);

    info ("adecoder_start index %d .\n", index);

    return 0;
}

int adecoder_stop (int index)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_unregister_event (dec->dec_info, AUDIO_DECODER_EVENT_INFO);

    if (dec->codec == AUDIO_DECODER_CODEC_MPEG_H)
    {
        decoder_unregister_event (dec->dec_info, AUDIO_DECODER_EVENT_MPEGH_UI);
    }

#ifdef SUPPORT_SOUNDBAR
    decoder_stop (dec->dec_info);
#endif
    dec->is_started = FALSE;

    mutex_unlock (&dec->lock);

    info ("adecoder_stop index %d .\n", index);

    return 0;
}


int adecoder_codec (int index, enum audio_decoder_codec codec)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    dec->codec = codec;

    decoder_set_codec (dec->dec_info, codec);

    mutex_unlock (&dec->lock);

    info ("adecoder_codec index %d codec %d (%s) .\n", index, codec, _get_codec_name (codec));

    return 0;
}

#ifndef SUPPORT_SOUNDBAR
static enum pcmren_downmix_mode adecoder_get_pcmren_downmix_mode (unsigned int downmix_mode)
{
    if (downmix_mode == 0)
        return PCMREN_DOWNMIX_LORO_MODE;
    else
        return PCMREN_DOWNMIX_LTRT_MODE;

    return PCMREN_DOWNMIX_LTRT_MODE;
}
#endif

int adecoder_codec_param_user (int index, struct adec_codec_param *codec_param)
{
    ADECODER_INFO_T *dec = NULL;
    struct aud_block_info *mixer = NULL;
    int main_audio_index = -1;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    info ("codec: %d (%s)\n", dec->codec, _get_codec_name (dec->codec));

    mixer = bm_get_block_info_by_index ("mixer", 0);
    if (mixer)
        main_audio_index = mixer_get_main_audio_index (mixer);

    switch (dec->codec)
    {
        case AUDIO_DECODER_CODEC_PCM:
        case AUDIO_DECODER_CODEC_ADPCM:
        {
            struct adec_pcm_param param = { };

            if (sizeof (struct adec_pcm_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_pcm_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);
            info ("bits per sample: %d\n", param.bits_per_sample);
            info ("byte align: %d\n", param.byte_align);
            info ("sign: %d\n", param.sign);

            decoder_set_param (dec->dec_info,
                "rate=%d channels=%d bits-per-sample=%d endian=%d sign=%d",
                param.sampling_rate, param.channels, param.bits_per_sample, param.byte_align,
                param.sign);

            break;
        }

        case AUDIO_DECODER_CODEC_AC3:
        case AUDIO_DECODER_CODEC_EAC3:
        {
            struct adec_ac3_param param = { };

            if (sizeof (struct adec_ac3_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_ac3_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);
            info ("drc mode: %d\n", param.drc_mode);
            info ("downmix mode: %d\n", param.downmix_mode);
            info ("audio description: %d\n", param.audio_description);
            info ("atmos decoding: %d\n", param.atmos_decoding);
            info ("legacy ddp out: %d\n", param.legacy_ddp_out);
            info ("play speed: %d\n", param.play_speed);
            info ("Downmix 2ch (Multiview): %d\n", param.downmix);

            decoder_set_param (dec->dec_info, "dec-id=%d", index);
#ifndef SUPPORT_SOUNDBAR
            decoder_set_param (dec->dec_info,
                "drc-mode=%d downmix-mode=%d audio-description=%d atmos-decoding=%d",
                param.drc_mode, param.downmix_mode, param.audio_description, param.atmos_decoding);

            if (param.downmix)
                decoder_set_param (dec->dec_info, "downmix-out-ch=%d", param.downmix);
#else
            decoder_set_param (dec->dec_info,
                "drc-mode=%d audio-description=%d atmos-decoding=%d",
                param.drc_mode, param.audio_description, param.atmos_decoding);
#endif

#ifndef SUPPORT_SOUNDBAR
            if (mixer && (index == main_audio_index))
            {
                mixer_set_pcmren_drc_mode (mixer, param.drc_mode);
                mixer_set_pcmren_downmix_mode (mixer,
                    adecoder_get_pcmren_downmix_mode (param.downmix_mode));

                // 0: DD/DD+, 1: AAC, 2: AC4, 3: MAT, 4: ETC (EXTERNAL_PCM)
                mixer_set_pcmren_metadata_type (mixer, 0);
            }
#endif

            break;
        }

        case AUDIO_DECODER_CODEC_AC4:
        {
            struct adec_ac4_param param = { };

            if (sizeof (struct adec_ac4_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_ac4_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);
            info ("drc mode: %d\n", param.drc_mode);
            info ("downmix mode: %d\n", param.downmix_mode);
            info ("audio description: %d\n", param.audio_description);
            info ("atmos decoding: %d\n", param.atmos_decoding);
            info ("de gain: %d\n", param.de_gain);
            info ("legacy ddp out: %d\n", param.legacy_ddp_out);
            info ("play speed: %d\n", param.play_speed);
            info ("Downmix 2ch (Multiview): %d\n", param.downmix);

            decoder_set_param (dec->dec_info,
                "de-gain=%d legacy-ddp-out=%d atmos-decoding=%d",
                param.de_gain, param.legacy_ddp_out, param.atmos_decoding);
            decoder_set_param (dec->dec_info, "main-decoder=1");

            if (param.downmix)
                decoder_set_param (dec->dec_info, "downmix-out-ch=%d", param.downmix);

#ifndef SUPPORT_SOUNDBAR
            if (mixer && (index == main_audio_index))
            {
                mixer_set_pcmren_drc_mode (mixer, param.drc_mode);
                mixer_set_pcmren_downmix_mode (mixer,
                    adecoder_get_pcmren_downmix_mode (param.downmix_mode));

                // 0: DD/DD+, 1: AAC, 2: AC4, 3: MAT, 4: ETC (EXTERNAL_PCM)
                mixer_set_pcmren_metadata_type (mixer, 2);
            }
#endif

            break;
        }

        case AUDIO_DECODER_CODEC_AAC:
        {
            struct adec_aac_param param = { };

            if (sizeof (struct adec_aac_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_aac_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);
            info ("drc mode: %d\n", param.drc_mode);
            info ("downmix mode: %d\n", param.downmix_mode);
            info ("audio description: %d\n", param.audio_description);
            info ("iec format: %d\n", param.iec_format);
            info ("transcoding: %d\n", param.transcoding);
            info ("play speed: %d\n", param.play_speed);
            info ("Downmix 2ch (Multiview): %d\n", param.downmix);

#if (MS12_VER >= 28)
            decoder_set_param (dec->dec_info, "dec-id=%d", index);
#endif
#ifndef SUPPORT_SOUNDBAR
            decoder_set_param (dec->dec_info,
                "drc-mode=%d downmix-mode=%d audio-description=%d iec-format=%d transcoding=%d",
                param.drc_mode, param.downmix_mode,
                param.audio_description, param.iec_format, param.transcoding, param.play_speed);

            if (param.downmix)
                decoder_set_param (dec->dec_info, "downmix-out-ch=%d", param.downmix);
#else
            decoder_set_param (dec->dec_info,
                "drc-mode=%d audio-description=%d iec-format=%d transcoding=%d",
                param.drc_mode, param.audio_description, param.iec_format, param.transcoding,
                param.play_speed);
#endif

#ifndef SUPPORT_SOUNDBAR
            if (mixer && (index == main_audio_index))
            {
                mixer_set_pcmren_drc_mode (mixer, param.drc_mode);
                mixer_set_pcmren_downmix_mode (mixer,
                    adecoder_get_pcmren_downmix_mode (param.downmix_mode));

                // 0: DD/DD+, 1: AAC, 2: AC4, 3: MAT, 4: ETC (EXTERNAL_PCM)
                mixer_set_pcmren_metadata_type (mixer, 1);
            }
#endif

            break;
        }

        case AUDIO_DECODER_CODEC_MP3:
        {
            struct adec_mp3_param param = { };

            if (sizeof (struct adec_mp3_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_mp3_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);
            info ("drc mode: %d\n", param.drc_mode);
            info ("audio description: %d\n", param.audio_description);

            decoder_set_param (dec->dec_info,
                "drc-mode=%d audio-description=%d", param.drc_mode, param.audio_description);

            break;
        }

        case AUDIO_DECODER_CODEC_MPEG_H:
        {
            struct adec_mpegh_param param = { };

            if (sizeof (struct adec_mpegh_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_mpegh_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);
            info ("Downmix 2ch (Multiview): %d\n", param.downmix);

            if (param.downmix)
                decoder_set_param (dec->dec_info, "downmix-out-ch=%d", param.downmix);

            break;
        }

        case AUDIO_DECODER_CODEC_DRA:
        {
            struct adec_dra_param param = { };

            if (sizeof (struct adec_dra_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_dra_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);

            break;
        }

#ifdef SUPPORT_WMA
        case AUDIO_DECODER_CODEC_WMA_PRO:
        {
            struct adec_wma_param param = { };

            if (sizeof (struct adec_wma_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_wma_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);

            info ("bits per sample: %d\n", param.bits_per_sample);
            info ("wma format tag: %d\n", param.wma_format_tag);
            info ("block align: %d\n", param.block_align);
            info ("avg bps: %d\n", param.avg_bps);
            info ("channel mask: %d\n", param.channel_mask);
            info ("encode opt: %d\n", param.encode_opt);
            info ("adv encode opt: %d\n", param.adv_encode_opt);
            info ("adv encode opt2: %d\n", param.adv_encode_opt2);

            decoder_set_param (dec->dec_info,
                "sampling-rate=%d channels=%d bits-per-sample=%d wma-format-tag=%d block-align=%d avg-bps=%d channel-mask=%d encode-opt=%d adv-encode-opt=%d adv-encode-opt2=%d",
                param.sampling_rate, param.channels, param.bits_per_sample, param.wma_format_tag,
                param.block_align, param.avg_bps, param.channel_mask, param.encode_opt,
                param.adv_encode_opt, param.adv_encode_opt2);

            break;
        }
#endif

        case AUDIO_DECODER_CODEC_VORBIS:
        {
            struct adec_vorbis_param param = { };

            if (sizeof (struct adec_vorbis_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_vorbis_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);

            break;
        }

        case AUDIO_DECODER_CODEC_AMR_WB:
        case AUDIO_DECODER_CODEC_AMR_NB:
        {
            struct adec_amr_param param = { };

            if (sizeof (struct adec_amr_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_amr_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);

            break;
        }

        case AUDIO_DECODER_CODEC_FLAC:
        {
            struct adec_flac_param param = { };

            if (sizeof (struct adec_flac_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_flac_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);

            decoder_set_param (dec->dec_info, "channels=%d", param.channels);

            break;
        }

        case AUDIO_DECODER_CODEC_OPUS:
        {
            struct adec_opus_param param = { };

            if (sizeof (struct adec_opus_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_opus_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);
            info ("Downmix 2ch (Multiview): %d\n", param.downmix);

            decoder_set_param (dec->dec_info, "sampling-rate=%d channels=%d",
                param.sampling_rate, param.channels);

#ifndef SUPPORT_SOUNDBAR
            if (param.downmix)
                decoder_set_param (dec->dec_info, "downmix-out-ch=%d", param.downmix);
#endif

            break;
        }

#ifdef SUPPORT_DTSX
        case AUDIO_DECODER_CODEC_DTS:
        {
            struct adec_dtsx_param param = { };
            struct aud_block_info *encoder;
            int enc_mode = 2;

            if (sizeof (struct adec_dtsx_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_dtsx_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("bitstream passthrough: %d\n", param.bitstream_passthrough);

            decoder_set_param (dec->dec_info, "bitstream-passthrough=%d",
                param.bitstream_passthrough);

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

        case AUDIO_DECODER_CODEC_AAC_ELD:
        {
            struct adec_aac_eld_param param = { };

            if (sizeof (struct adec_aac_eld_param) != codec_param->size)
            {
                error ("invalid param length. struct size: %ld, param size: %d\n",
                    sizeof (struct adec_aac_eld_param), codec_param->size);
                goto failed;
            }

            if (copy_from_user (&param, codec_param->param, codec_param->size))
            {
                error ("copy_from_user() failed\n");
                goto failed;
            }

            info ("sampling rate: %d\n", param.sampling_rate);
            info ("channels: %d\n", param.channels);

            break;
        }

        default:
        {
            error ("unknown codec. codec: %d\n", dec->codec);
            goto failed;
        }
    }

#ifdef SUPPORT_SOUNDBAR
    switch (dec->codec)
    {
            extern int sndout_get_decoder_spk_conf (void);

        case AUDIO_DECODER_CODEC_AC3:
        case AUDIO_DECODER_CODEC_EAC3:
#ifdef SUPPORT_DTSX
        case AUDIO_DECODER_CODEC_DTS:
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
    mutex_unlock (&dec->lock);

    return 0;

  failed:
    mutex_unlock (&dec->lock);

    return -1;
}

int adecoder_get_uid (int index, unsigned int *uid)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    *uid = bm_get_block_head (dec->dec_info);
    if (!*uid)
    {
        error ("error to get uid from decoder\n");
        mutex_unlock (&dec->lock);
        return -1;
    }

    mutex_unlock (&dec->lock);

    return 0;
}

//pioneer debug function only
int adecoder_get_decoded_info (int index, struct decoded_info *info)
{
    ADECODER_INFO_T *dec = NULL;

    if (index < 0 || index >= ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &adecoder_info[index];

    if (!info)
    {
        error ("decoded_info parameter is null\n");
        return -1;
    }

    mutex_lock (&dec->lock);
    if (dec->dec_info)
    {
        decoder_get_decoded_info (dec->dec_info, info);
    }
    else
    {
        struct aud_block_info *dec = NULL;
        dec = bm_get_block_info_by_index ("decoder", index);
        if (dec)
        {
            decoder_get_decoded_info (dec, info);
        }
        else
        {
            debug ("can not find decoder block, index: %d\n", index);
        }
    }
    mutex_unlock (&dec->lock);

    debug ("codec_type = %d, sampling_rate = %d, channel = %d, bit_per_sample = %d acmod = %d \n",
        info->codec, info->sampling_rate, info->source_channels, info->bit_per_sample, info->acmod);

    return 0;
}

int adecoder_set_input (int index, enum audio_decoder_input input)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_input (dec->dec_info, input);

    mutex_unlock (&dec->lock);

    return 0;
}

//pioneer debug function only
int adecoder_get_input (int index, unsigned int *input)
{
    ADECODER_INFO_T *dec = NULL;

    if (index < 0 || index >= ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    if (!input)
    {
        error ("input is null .\n");
        return -1;
    }

    dec = &adecoder_info[index];

    mutex_lock (&dec->lock);
    if (dec->dec_info)
    {
        *input = decoder_get_input (dec->dec_info);
    }
    else
    {
        struct aud_block_info *dec = NULL;
        dec = bm_get_block_info_by_index ("decoder", index);
        if (dec)
        {
            *input = decoder_get_input (dec);
        }
        else
        {
            debug ("can not find decoder block, index: %d\n", index);
        }
    }
    mutex_unlock (&dec->lock);

    debug ("decoder#%d input: %d\n", index, *input);

    return 0;
}

int adecoder_set_mpegh_ui_param (int index, struct adec_mpegh_ui_param *ui_param)
{
    ADECODER_INFO_T *dec = NULL;

    if (!ui_param)
    {
        error ("param is null .\n");
        return -1;
    }

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_mpegh_ui_param (dec->dec_info, ui_param);

    mutex_unlock (&dec->lock);

    return 0;
}

int adecoder_get_mpegh_ui_param (int index, struct adec_mpegh_ui_param *ui_param)
{
    ADECODER_INFO_T *dec = NULL;

    if (!ui_param)
    {
        error ("param is null .\n");
        return -1;
    }

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_get_mpegh_ui_param (dec->dec_info, ui_param);

    mutex_unlock (&dec->lock);

    return 0;
}

int adecoder_set_output_mode (int index, unsigned int output_mode)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "output-mode=%d", output_mode);

    mutex_unlock (&dec->lock);

    return 0;
}

int adecoder_set_basetime (int index, unsigned long long basetime)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "basetime=%llu", basetime);

    mutex_unlock (&dec->lock);

    return 0;
}

int adecoder_set_presentation_group_index (int index, unsigned int pres_group_index)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "pres-group-index=%d", pres_group_index);

    mutex_unlock (&dec->lock);

    return 0;
}

int adecoder_set_dialog_enhancement_gain (int index, unsigned int gain)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "de-gain=%d", gain);

    mutex_unlock (&dec->lock);

    return 0;
}

int adecoder_get_dialog_enhancement_gain (int index, unsigned int *gain)
{
    ADECODER_INFO_T *dec = NULL;

    if (index < 0 || index >= ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &adecoder_info[index];

    if (!dec->dec_info)
    {
        error ("decoder is not opened\n");
        return -1;
    }

    decoder_get_param (dec->dec_info, "de-gain", gain);

    info ("dialog enhancement gain: %d\n", *gain);

    return 0;
}

int adecoder_get_dialog_enhancement_limit (int index, unsigned int *limit)
{
    ADECODER_INFO_T *dec = NULL;

    if (index < 0 || index >= ADEC_MAX)
    {
        error ("invalid audio decoder index, index %d .\n", index);
        return -1;
    }

    dec = &adecoder_info[index];

    if (!dec->dec_info)
    {
        error ("decoder is not opened\n");
        return -1;
    }

    decoder_get_param (dec->dec_info, "de-limit", limit);

#if (MS12_VER == 24)
    //http://source.lge.com/dsw/#/c/DTV/media/gst-plugins-bsp/+/155712/
    *limit = *limit * 3;
#endif

    info ("dialog enhancement limit: %d\n", *limit);

    return 0;
}

int adecoder_set_default_prl (int index, unsigned int default_prl)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "default-prl=%d", default_prl);

    mutex_unlock (&dec->lock);

    return 0;
}

int adecoder_set_gap_info (int index, struct gap_info *gap_info)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "start-pts=%d end-pts=%d", gap_info->start_pts,
        gap_info->end_pts);

    mutex_unlock (&dec->lock);

    return 0;
}

#ifdef SUPPORT_DTSX
int adecoder_get_dts_supported (int index, bool *is_supported)
{
    *is_supported = aud_hal_dts_supported ();

    return 0;
}

int adecoder_get_dts_bitstream_passthrough (int index, bool *bitstream_passthrough)
{
    *bitstream_passthrough = notifier_get_dtsx_bitstream_passthrough ();

    return 0;
}
#endif

int adecoder_set_dolby_drc_mode (int index, unsigned int drc_mode)
{
    ADECODER_INFO_T *dec = NULL;
#ifndef SUPPORT_SOUNDBAR
    struct aud_block_info *mixer = NULL;
    int main_audio_index = -1;
#endif

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "drc-mode=%d", drc_mode);

#ifndef SUPPORT_SOUNDBAR
    decoder_set_dolby_drc_mode (dec->dec_info, drc_mode);

    mixer = bm_get_block_info_by_index ("mixer", 0);

    if (mixer)
    {
        main_audio_index = mixer_get_main_audio_index (mixer);
        if (index == main_audio_index)
        {
            if (dec->codec == AUDIO_DECODER_CODEC_MP3)
                drc_mode = AUDIO_DECODER_DRC_LINE;

            mixer_set_pcmren_drc_mode (mixer, drc_mode);
        }
    }
#endif

    mutex_unlock (&dec->lock);

    return 0;
}

int adecoder_set_aac_format_type (int index, unsigned int format_type)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "format-type=%d", format_type);

    mutex_unlock (&dec->lock);

    info ("aac format type %d .\n", format_type);

    return 0;
}

int adecoder_set_proc_id (int index, unsigned int proc_id)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    dec->proc_id = proc_id;
    mutex_unlock (&dec->lock);

    info ("set processor id as %d(0x%0x)\n", proc_id, proc_id);

    return 0;
}

int adecoder_set_normal_closed (int index)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    mutex_unlock (&dec->lock);

    info ("normal closed.\n");

    return 0;
}

int adecoder_set_downmix (int index, bool enable)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "downmix-out-ch=%d", enable);

    mutex_unlock (&dec->lock);

    info ("downmix : %s.\n", (enable) ? "enable" : "disable");

    return 0;
}

int adecoder_set_sound_system (int index, unsigned int sound_system)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "sound_system=%d", sound_system);

    mutex_unlock (&dec->lock);

    info ("sound_system = %d\n", sound_system);

    return 0;
}

#ifdef SUPPORT_MUSIC_MODE
int adecoder_set_music_mode (int index, bool music_mode)
{
    ADECODER_INFO_T *dec = NULL;

    ADECODER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    decoder_set_param (dec->dec_info, "music-mode=%d", (int)music_mode);

    mutex_unlock (&dec->lock);

    info ("music-mode = %d\n", music_mode);

    return 0;
}
#endif

int aren_open (int index)
{
    ARENDERER_INFO_T *ren = NULL;

    if (index < 0 || index >= AREN_MAX)
    {
        error ("invalid audio renderer index, index %d .\n", index);
        return -1;
    }

    ren = &arenderer_info[index];

    mutex_lock (&ren->lock);

    if (ren->is_open)
    {
        error ("can not open audio renderer. already opened index %d", index);
        mutex_unlock (&ren->lock);
        return -1;
    }

    ren->ren_info = bm_create_block ("renderer", index);

    ren->is_open = TRUE;
    ren->proc_id = -1;
    ren->msgq_id = -1;
    ren->pid_to_signal = -1;

    mutex_unlock (&ren->lock);

    info ("aren_open index %d .\n", index);

    return 0;
}

int aren_close (int index)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    bm_disconnect_block (ren->ren_info, 0);

    bm_destroy_block (ren->ren_info);

    ren->is_open = FALSE;
    ren->clock_type = MD_CLK_TYPE_UNKNOWN;

    memset (&ren->pcm_info, 0x0, sizeof (aren_pcm_info_t));

    ren->ren_info = NULL;

    mutex_unlock (&ren->lock);

    info ("aren_close index %d .\n", index);

    return 0;
}

int aren_add_queue (int index)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_add_queue (ren->ren_info, true);

    mutex_unlock (&ren->lock);

    return 0;
}

int aren_get_uid (int index, unsigned int *uid, bool is_bypass)
{
    ARENDERER_INFO_T *ren = NULL;
    aren_pcm_info_t *info;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    info = &ren->pcm_info;

    if (is_bypass)
    {
        if (info->pcm_bypass || info->pcm_multi_ch)
        {
            *uid = renderer_get_uid_pcm_bypass_head (ren->ren_info);
            info ("pcm bypass uid = 0x%08X\n", *uid);
        }
        else
        {
            *uid = renderer_get_uid_es_bypass_head (ren->ren_info);
            info ("es bypass uid = 0x%08X\n", *uid);
        }
    }
    else
    {
        *uid = bm_get_block_head (ren->ren_info);
        info ("uid = 0x%08X\n", *uid);
    }

    if (!*uid)
    {
        error ("error to get uid from %s\n", (is_bypass) ? "bypass_renderer" : "renderer");
        mutex_unlock (&ren->lock);
        return -1;
    }

    mutex_unlock (&ren->lock);

    return 0;
}

int aren_get_tail_uid (int index, unsigned int *uid, bool is_bypass)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    if (is_bypass)
        *uid = renderer_get_uid_bypass_tail (ren->ren_info);
    else
        *uid = bm_get_block_tail (ren->ren_info);

    if (!*uid)
    {
        error ("error to get uid from renderer\n");
        mutex_unlock (&ren->lock);
        return -1;
    }

    mutex_unlock (&ren->lock);

    return 0;
}

int aren_set_clock_type (int index, enum md_clock_type clock_type)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_set_param (ren->ren_info, "clockType=%d", clock_type);

    if (clock_type == MD_CLK_TYPE_GSTC)
    {
        renderer_set_param (ren->ren_info, "idle_time=0");
    }

    ren->clock_type = clock_type;

    mutex_unlock (&ren->lock);

    return 0;
}


int aren_enable_lipsync (int index, bool on)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_set_param (ren->ren_info, "LipsyncOnOff=%d", on);

    mutex_unlock (&ren->lock);

    info ("aren_enable_lipsync index %d on_off %d .\n", index, on);

    return 0;
}

int aren_set_basetime (int index, unsigned int clock_base, unsigned int stream_base)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_set_param (ren->ren_info, "BaseCT=%d BaseST=%d", clock_base, stream_base);

    mutex_unlock (&ren->lock);

    info ("aren_set_basetime index %d 0x%x 0x%x\n", index, clock_base, stream_base);

    return 0;
}


int aren_set_lipsync_param (int index, unsigned int lower_bound, unsigned int upper_bound,
    unsigned int offset, unsigned int freerun_lbound, unsigned int freerun_ubound)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_set_param (ren->ren_info, "lowerbound=%d upperbound=%d", lower_bound, upper_bound);
    renderer_set_param (ren->ren_info, "offset=%d", offset);

    mutex_unlock (&ren->lock);

    info ("aren_set_lipsync_param index %d done\n", index);

    return 0;
}

int aren_set_speed (int index, unsigned int speed)
{
    ARENDERER_INFO_T *ren = NULL;
    unsigned int rate_in = 1000;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    // trick speed adjust ex) 2x: InSample = 2000
    if (speed > 2000 || speed <= 0)
    {
        rate_in = 1000;
    }
    else
    {
        rate_in = speed;
    }

    if (!ren->vsp_mode)
    {
        notifier_set_play_speed (index, rate_in);
    }

    renderer_set_param (ren->ren_info, "rate-in=%d", rate_in);
    renderer_set_param (ren->ren_info, "speed-in=%d", rate_in);

    mutex_unlock (&ren->lock);

    info ("aren_set_speed index %d done\n", index);

    return 0;
}

int aren_set_mute (int index, unsigned int mute)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_set_param (ren->ren_info, "mute-input=%d", mute);

    mutex_unlock (&ren->lock);

    info ("%s done. mute = %d \n", __func__, mute);

    return 0;
}

int aren_set_ease_volume (int index, aren_ease_volume_t easevolume)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

//    renderer_set_param (ren->ren_info, "target-gain=%d", easevolume.volume);
//    renderer_set_param (ren->ren_info, "fade-type=%d", easevolume.type);
//    renderer_set_param (ren->ren_info, "fadetime-ms=%d", easevolume.duration);
    renderer_set_param (ren->ren_info, "{ease-volume}={target-gain:%d,fade-type:%d,fadetime-ms:%d}",
        easevolume.volume, easevolume.type, easevolume.duration);

    mutex_unlock (&ren->lock);

    info ("volume:%d, duration:%d, type:%d \n", easevolume.volume, easevolume.duration,
        easevolume.type);

    return 0;
}

int aren_get_ease_volume (int index, unsigned int *volume)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_get_param (ren->ren_info, "final-gain", volume);

    mutex_unlock (&ren->lock);

    info ("done. volume = %d \n", *volume);

    return 0;
}


int aren_set_gap_info (int index, aren_gap_info_t gap_info)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_set_gap_info (ren->ren_info, gap_info.start_pts, gap_info.end_pts);

    mutex_unlock (&ren->lock);

    info ("done. start_pts:%d, end_pts:%d \n", gap_info.start_pts, gap_info.end_pts);

    return 0;
}

int aren_get_rendered_status (int index, aren_rendered_status_t * status)
{
    ARENDERER_INFO_T *ren = NULL;

    if (index < 0 || index >= AREN_MAX)
    {
        error ("invalid audio renderer index, index %d .\n", index);
        return -1;
    }

    ren = &arenderer_info[index];

    return 0;
}

int aren_get_rts_queue_info (int index, aren_rts_queue_info_t * info)
{
    ARENDERER_INFO_T *ren = NULL;
    unsigned int queued_byte = 0;
    unsigned int max_length = 0;
    unsigned int stride_shift = 0;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_get_param (ren->ren_info, "queued-byte", &queued_byte);
    renderer_get_param (ren->ren_info, "max-length", &max_length);
    renderer_get_param (ren->ren_info, "stride-shift", &stride_shift);

    info->queue_max = max_length << stride_shift;
    info->queued_byte = queued_byte;

    mutex_unlock (&ren->lock);

    trace ("queued-byte :%d\n", queued_byte);
    trace ("max-length :%d\n", max_length);
    trace ("stride-shift :%d\n", stride_shift);
    trace ("queue_max = %d\n", info->queue_max);

    return 0;
}

int aren_add_rts (int index)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_add_rts (ren->ren_info);

    mutex_unlock (&ren->lock);

    info ("renderer_add_rts done\n");
    return 0;
}

int aren_set_rts_param (int index, aren_rts_param_t rts_param)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_set_rts_port_multiplier (ren->ren_info, MOD_REF_PORT (0), 384000,
        (unsigned int) (ren->pcm_info.sampling_rate * ren->pcm_info.channels *
            (ren->pcm_info.bits_per_sample >> 3)));
    renderer_set_rts_threshold (ren->ren_info, rts_param.upper_threshold, rts_param.lower_threshold,
        rts_param.recover_upper, rts_param.recover_lower);
    renderer_set_rts_out_freq (ren->ren_info, rts_param.fast_freq, rts_param.normal_freq,
        rts_param.slow_freq);
    renderer_set_rts_skipping (ren->ren_info, rts_param.recover_skipping,
        rts_param.skipping_threshold);
    renderer_set_rts_opmode (ren->ren_info, rts_param.opmode);
    renderer_set_param (ren->ren_info, "buffering-ms=%d", rts_param.buffering_level);
    renderer_set_rts_start (ren->ren_info);

    mutex_unlock (&ren->lock);

    return 0;
}

int aren_set_jp4k (int index, bool is_jp4k)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_set_jp4k (ren->ren_info, is_jp4k);

    mutex_unlock (&ren->lock);

    return 0;
}

int aren_start (int index)
{
    ARENDERER_INFO_T *ren = NULL;
    bool update = TRUE;
    aren_pcm_info_t *info;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    info = &ren->pcm_info;

    if (ren->clock_type == MD_CLK_TYPE_GSTC)
        aud_clock_enable_input (index, CLOCK_SOURCE_GSTC0, 0);
    else if (ren->clock_type == MD_CLK_TYPE_GSTC_1)
        aud_clock_enable_input (index, CLOCK_SOURCE_GSTC1, 0);
    else
        update = FALSE;

    if (update == TRUE)
    {
        if (ren->pcm_info.clock_x4)
            aud_clock_update_input (index, ren->pcm_info.channels, ren->pcm_info.sampling_rate * 4);
        else
            aud_clock_update_input (index, ren->pcm_info.channels, ren->pcm_info.sampling_rate);
    }

    renderer_set_param (ren->ren_info, "endian=%d sign=%d", info->byte_align, info->sign);
    renderer_set_param (ren->ren_info, "block-queue=%d", 0);

    if (info->pcm_bypass)
    {
        unsigned int channels = (info->channels <= 2) ? 2 : 8;
        renderer_set_pcm_bypass_rts_out_channels (ren->ren_info, channels);
    }

    if (info->pcm_multi_ch)
    {
        unsigned int channels = (info->channels <= 2) ? 2 : 8;
        renderer_set_pcm_bypass_rts_out_channels (ren->ren_info, channels);
        renderer_set_param (ren->ren_info, "out-channels=%d", channels);
    }

    mutex_unlock (&ren->lock);

    return 0;
}

int aren_stop (int index)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    aud_clock_disable_input (index);
    renderer_set_param (ren->ren_info, "block-queue=%d", 1);

    mutex_unlock (&ren->lock);

    info ("aren_stop index %d .\n", index);

    return 0;
}

int aren_set_pcm_info (int index, aren_pcm_info_t pcm_info)
{
    ARENDERER_INFO_T *ren = NULL;
    aren_pcm_info_t *info;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    info = &ren->pcm_info;

    info->bits_per_sample = pcm_info.bits_per_sample;
    info->channels = pcm_info.channels;
    info->sampling_rate = pcm_info.sampling_rate;
    info->byte_align = pcm_info.byte_align;
    info->sign = pcm_info.sign;
    info->clock_x4 = pcm_info.clock_x4;
    info->pcm_bypass = pcm_info.pcm_bypass;
    info->pcm_multi_ch = pcm_info.pcm_multi_ch;

    mutex_unlock (&ren->lock);

    info ("renderer set pcm info. bits per sample: %d, channels: %d, sampling rate: %d, byte align: %d, signed: %d, clock_x4 (eac3): %d, pcm-bypass(google): %d, pcm-multi-ch(netflix): %d\n", info->bits_per_sample, info->channels, info->sampling_rate, info->byte_align, info->sign, info->clock_x4, info->pcm_bypass, info->pcm_multi_ch);

    return 0;
}

int aren_set_bypass_fader (int index, bool game_mode)
{
    struct aud_block_info *mixer = NULL;

    mixer = bm_get_block_info_by_index ("mixer", 0);
    if (mixer)
    {
        info ("Set bypass fader : %d\n", game_mode);
        mixer_set_bypass_fader (mixer, index, game_mode);
    }
    else
    {
        info ("mixer is not connected.\n");
        return -1;
    }

    return 0;
}

int aren_get_queue_info (int index, aren_queue_info_t * info)
{
    ARENDERER_INFO_T *ren = NULL;
    unsigned int queued_length = 0;
    unsigned int max_length = 0;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_get_param (ren->ren_info, "queued-length", &queued_length);
    renderer_get_param (ren->ren_info, "queue-max-length", &max_length);

    info->queued_length = queued_length;
    info->max_length = max_length;

    mutex_unlock (&ren->lock);

    trace ("queued-length :%d\n", queued_length);
    trace ("max-length :%d\n", max_length);

    return 0;
}

int aren_get_vdec_current_pts (int index, aren_vdec_current_pts_t * vdec_current_pts)
{
    ARENDERER_INFO_T *ren = NULL;
    volatile unsigned int *reg = NULL;
    unsigned int vdec_pts_reg = 0;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    vdec_pts_reg = (VDEC_AV_LIPSYNC_BASE + (vdec_current_pts->port * 8) + 4);
    reg = (volatile unsigned int *) ioremap (vdec_pts_reg, sizeof (unsigned int));
    if (reg == NULL)
    {
        error ("Failed ioremap\n");
        return -EFAULT;
    }

    vdec_current_pts->pts = readl (reg);
    iounmap (reg);

    mutex_unlock (&ren->lock);

    info ("vdec_port = 0x%08X\n", vdec_current_pts->port);
    info ("pts_reg   = 0x%08X\n", vdec_pts_reg);
    info ("vdec_current_pts->pts = 0x%08X\n", vdec_current_pts->pts);

    return 0;
}

int aren_set_queue_max_length (int index, unsigned int queue_max_length)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    renderer_set_param (ren->ren_info, "queue-max-length=%d", queue_max_length);

    mutex_unlock (&ren->lock);

    info ("queue_max_length = 0x%08X(%d)\n", queue_max_length, queue_max_length);
    return 0;
}

int aren_set_proc_id (int index, unsigned int proc_id)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    ren->proc_id = proc_id;
    mutex_unlock (&ren->lock);

    info ("set processor id as %d(0x%0x)\n", proc_id, proc_id);

    return 0;
}

int aren_set_normal_closed (int index)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    mutex_unlock (&ren->lock);

    info ("normal closed.\n");

    return 0;
}

int aren_set_vsp_mode (int index)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    ren->vsp_mode = true;

    mutex_unlock (&ren->lock);

    info ("set vsp(variable speed playback) mode.\n");

    return 0;
}

int aren_set_msgpid_to_signal (int index, aren_msgpid_to_signal_t value)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    ren->msgq_id = value.msgq_id;
    ren->pid_to_signal = value.pid;

    mutex_unlock (&ren->lock);

    info ("set msgq id %d, pid_to_signal %d\n", ren->msgq_id, ren->pid_to_signal);

    return 0;
}

int aren_send_msg_signal (int index)
{
    ARENDERER_INFO_T *ren = NULL;

    ARENDERER_CHECK_INDEX_AND_OPENED_AND_LOCK (index);

    if (ren->pid_to_signal > 0 && ren->msgq_id > 0)
    {
        struct task_struct *task;
        struct kernel_siginfo info;

        task = pid_task (find_vpid (ren->pid_to_signal), PIDTYPE_PID);
        if (!task)
        {
            error ("No such process\n");
            return -1;
        }

        memset (&info, 0, sizeof (struct kernel_siginfo));
        info.si_signo = SIGUSR1;
        info.si_code = SI_QUEUE;
        info.si_int = ren->msgq_id;

        if (send_sig_info (SIGUSR1, &info, task) < 0)
        {
            error ("Fail sending signal\n");
        }
    }

    mutex_unlock (&ren->lock);

    info ("Send signal to process %d, msgq_id %d\n", ren->pid_to_signal, ren->msgq_id);

    return 0;
}
