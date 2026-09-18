/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/io.h>
#include <linux/proc_fs.h>
#include <sound/soc.h>

#include "logm.h"

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"
#include "capture.h"
#include "encoder.h"
#include "se.h"

#include "imc/cmd/module_cmd_capture.h"
#include "hma_alloc.h"
#include "block_manager.h"
#include "kaimc.h"
#include "alsa_se.h"
#include "alsa_support_sndout.h"
#include "alsa_sndout.h"
#include "alsa_capture.h"
#include "alsa_platform.h"

#include "linux/alsa-ext/alsa-ext-broadcast.h"
#include "linux/alsa-ext/alsa-ext-renderer.h"

logm_define (acapture, log_level_noti);

#define error(fmt,args...)      logm_error(acapture,fmt,##args)
#define warning(fmt,args...)    logm_warning(acapture,fmt,##args)
#define noti(fmt,args...)       logm_noti(acapture,fmt,##args)
#define info(fmt,args...)       logm_info(acapture,fmt,##args)
#define debug(fmt,args...)      logm_debug(acapture,fmt,##args)
#define trace(fmt,args...)      logm_trace(acapture,fmt,##args)

static bool is_encoder_connected;
static long long jiffies_start;

static char *acapture_poolname = "audio_buffer";
module_param (acapture_poolname, charp, 0644);


static struct alsa_enc_info aenc_info = {
    .dec_idx = 0,
    .codec = AENC_ENCODE_AAC,
    .bitrate = AENC_BIT_128K,
    .gain = 0x800000,
    .status = 0,
    .pts = 0,
};

struct acapture_priv
{
    struct snd_pcm_substream *substream;

    struct aud_block_info *capture_info;
    struct aud_block_info *encoder_info;

    bool is_connected;
    SINT32 event_id;

    phys_addr_t dma_addr;
    unsigned int dma_size;
    void *dma_vaddr;

    unsigned int wrOffset;
    unsigned int rdOffset;
    int out_bps;

    common_output_ext_type_t output;
};

#define PERIOD_BYTES             (256 /*sample */  * 2 /*channel */  * 4 /*byte */)
#define MAX_BUFFER_BYTES         PERIOD_BYTES * 64

#ifdef SUPPORT_SOUNDBAR
#define PERIOD_BYTES_21CH        (256 /*sample */  * 21 /*channel */  * 4 /*byte */)
#define MAX_BUFFER_BYTES_21CH    PERIOD_BYTES_21CH * 16
#else
#define PERIOD_BYTES_10CH        (256 /*sample */  * 10 /*channel */  * 4 /*byte */)
#define MAX_BUFFER_BYTES_10CH    PERIOD_BYTES_10CH * 16
#endif /* SUPPORT_SOUNDBAR */

#define BT_BUF_SIZE             (4096)
#define ALSA_CAP_HW_BT_WISA     10
#define ALSA_CAP_HW_ENC         11
#define ALSA_CAP_HW_DSNOOP      12
#define ALSA_CAP_HW_AUTOTEST    13
#define ALSA_CAP_HW_WOW         14
#ifdef SUPPORT_DAFC
#define ALSA_CAP_HW_DAFC        15
#endif
#ifdef SUPPORT_DAFC
#define ALSA_CAP_HW_MAX         ALSA_CAP_HW_DAFC
#else
#define ALSA_CAP_HW_MAX         ALSA_CAP_HW_WOW
#endif

#define ALSA_CAP_FORMAT         SNDRV_PCM_FMTBIT_S16_LE
#define ALSA_CAP_CHANNEL        2
#define ALSA_CAP_FRAME_NUM (snd_pcm_format_width(ALSA_CAP_FORMAT) * 8 * ALSA_CAP_CHANNEL)

#define ALSA_INTEGER_GAIN_MAX 0x0FFFFFFF        /* +30dB, 0xFCFB724 */

static struct snd_pcm_hardware acapture_pcm_hardware = {
    .info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
    .formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,
    .rates = SNDRV_PCM_RATE_8000_384000 | SNDRV_PCM_RATE_KNOT,
    .channels_min = 1,
    .channels_max = 10,
    .period_bytes_min = 0,
    .period_bytes_max = PERIOD_BYTES,
    .periods_min = 2,
    .periods_max = UINT_MAX,
    .buffer_bytes_max = MAX_BUFFER_BYTES,
    .fifo_size = 4,
};

static struct snd_pcm_hardware acapture_pcm_aenc_hardware = {
    .info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
    .formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,
    .rates = (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000),
    .channels_min = 2,
    .channels_max = 8,
    .period_bytes_min = 1024,
    .period_bytes_max = sizeof (aenc_data_t),
    .periods_min = 2,
    .periods_max = UINT_MAX,
    .buffer_bytes_max = MAX_BUFFER_BYTES,
    .fifo_size = 4,
};

static struct snd_pcm_hardware acapture_pcm_wow_hardware = {
    .info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
    .formats =
        (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_BE |
        SNDRV_PCM_FMTBIT_S32_BE),
    .rates = SNDRV_PCM_RATE_8000_384000,
    .channels_min = 2,
    .channels_max = 8,
    .period_bytes_min = 1024,
    .period_bytes_max = PERIOD_BYTES,
    .periods_min = 2,
    .periods_max = UINT_MAX,
    .buffer_bytes_max = MAX_BUFFER_BYTES,
    .fifo_size = 4,
};

#ifdef SUPPORT_DAFC
static struct snd_pcm_hardware acapture_pcm_dafc_hardware = {
    .info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
    .formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,
    .rates = SNDRV_PCM_RATE_8000_384000,
    .channels_min = 1,
#ifdef SUPPORT_SOUNDBAR
    .channels_max = 21,
#else
    .channels_max = 10,
#endif
    .period_bytes_min = 0,
#ifdef SUPPORT_SOUNDBAR
    .period_bytes_max = PERIOD_BYTES_21CH,
#else
    .period_bytes_max = PERIOD_BYTES_10CH,
#endif /* SUPPORT_SOUNDBAR */
    .periods_min = 2,
    .periods_max = UINT_MAX,
#ifdef SUPPORT_SOUNDBAR
    .buffer_bytes_max = MAX_BUFFER_BYTES_21CH,
#else
    .buffer_bytes_max = MAX_BUFFER_BYTES_10CH,
#endif /* SUPPORT_SOUNDBAR */
    .fifo_size = 4,
};
#endif

static bool _cap_disable = false;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int acapture_ack (struct snd_soc_component *component, struct snd_pcm_substream *substream);
#else
static int acapture_ack (struct snd_pcm_substream *substream);
#endif
static void _acapture_destroy_se (struct acapture_priv *capture);

static bool leaudio_is_connected (struct acapture_priv *capture)
{
    if (capture->substream->pcm->device == ALSA_CAP_HW_BT_WISA
        && sndout_output_connected_any (COMMON_WISA) == false
        && sndout_output_connected_any (COMMON_CAPTURE) == false
        && sndout_output_connected_any (COMMON_SE_BT) == false
        && sndout_output_connected_any (COMMON_SE_BT_SUR) == false
        && sndout_output_connected_any (COMMON_DAP_HP_BT) == false)
        return true;
    else
        return false;
}

static int _get_capture_index (common_output_ext_type_t output)
{
    int capture_index = 0;
    switch (output)
    {
        case COMMON_CAPTURE:
        case COMMON_WISA:
        case COMMON_BLUETOOTH:
        case COMMON_SE_BT:
        case COMMON_SE_BT_SUR:
        case COMMON_DAP_HP_BT:
            capture_index = ALSA_CAP_HW_BT_WISA;
            break;
#ifdef SUPPORT_DAFC
        case COMMON_DAFC:
            capture_index = ALSA_CAP_HW_DAFC;
            break;
#endif
        default:
            error ("unknown output 0x%x\n", output);
            return -1;
    }

    return capture_index;
}

int acapture_set_gain (common_output_ext_type_t output, int gain)
{
    struct aud_block_info *block = NULL;
    int capture_index = _get_capture_index (output);

    if (capture_index > 0)
    {
        block = bm_get_block_info_by_index ("capture", capture_index);
        if (block)
            aud_capture_set_gain (block, gain);
    }

    return 0;
}

int acapture_set_mute (common_output_ext_type_t output, bool mute)
{
    struct aud_block_info *block = NULL;
    int capture_index = _get_capture_index (output);

    if (capture_index > 0)
    {
        block = bm_get_block_info_by_index ("capture", capture_index);
        if (block)
            aud_capture_set_mute (block, mute);
    }

    return 0;
}

bool acapture_is_encoder_connected (void)
{
    return is_encoder_connected;
}

/**
 * callback function to update wrPrt
 */
static int _acapture_updated (void *_param, int _paramLen, void *_cbParam)
{
    struct acapture_priv *capture = _cbParam;

    int wrOffset = 0;
    unsigned int elapsed = 0;

    debug ("got callback from\n");

    if (_param && _paramLen)
    {
        wrOffset = *(int *) _param;
        trace ("wrOffset is 0x%08x dma_buffer.addr %pad\n", wrOffset,
            &capture->substream->dma_buffer.addr);

        // atv case should update pts
        if (capture->substream->pcm->device == ALSA_CAP_HW_ENC)
        {
            void *pSharedBuffer = capture->dma_vaddr + capture->wrOffset;
            aenc_info.pts = ((aenc_data_t *) pSharedBuffer)->pts;
            trace ("found pts : %lld", aenc_info.pts);
        }
        capture->wrOffset = wrOffset;

        if (capture->substream->pcm->device == ALSA_CAP_HW_BT_WISA)
        {
            if (capture->substream->runtime->period_size < ALSA_CAP_FRAME_NUM)
            {
                trace ("period_size(%lu) is smaller than ALSA_CAP_FRAME_NUM(%d)\n",
                    capture->substream->runtime->period_size, ALSA_CAP_FRAME_NUM);
            }
        }

        snd_pcm_period_elapsed (capture->substream);

        elapsed = (unsigned int) jiffies_to_msecs (jiffies - jiffies_start);

        if (elapsed > 30)
            noti ("elapsed = %d ms  over 30ms \n", elapsed);
        else
            trace ("elapsed = %d ms \n", elapsed);

        jiffies_start = jiffies;

    }

    return 0;
}

extern int _gAlsaCaptureSource;
static int _acapture_disconnect (struct acapture_priv *capture)
{
    int ret = RET_OK;

    debug ("called\n");
    if (capture->is_connected == false)
    {
        debug ("not connected.\n");
        goto exit;
    }

    capture->is_connected = false;

    if (capture->substream->pcm->device == ALSA_CAP_HW_ENC)
    {
        is_encoder_connected = false;
        noti ("is_encoder_connected = %d\n", is_encoder_connected);
    }

#ifdef SUPPORT_SOUNDBAR
    if (capture->substream->pcm->device == ALSA_CAP_HW_BT_WISA)
    {
        if (capture->output == COMMON_DAP_HP_BT)
        {
            struct aud_block_info *se_info = NULL;
            alsa_se_handle_t handle = NULL;

            handle = alsa_se_get_handle ("COMMON_DAP_HP_BT");

            if (handle)
            {
                se_info = alsa_se_get_block (handle);
                if (se_info)
                {
                    se_set_dap_output_device (se_info, 0);
                }
            }
        }
    }
#else
    if (capture->substream->pcm->device == ALSA_CAP_HW_BT_WISA)
    {
        struct aud_block_info *se_info = NULL;
        alsa_se_handle_t handle = NULL;

        if ((capture->output == COMMON_SE_BT) || (capture->output == COMMON_SE_BT_SUR))
            handle = alsa_se_get_handle ("COMMON_SE_BT");
        else if (capture->output == COMMON_DAP_HP_BT)
            handle = alsa_se_get_handle ("COMMON_DAP_HP_BT");

        if (handle)
        {
            se_info = alsa_se_get_block (handle);
            if (se_info)
            {
                if (capture->output == COMMON_DAP_HP_BT)
                {
                    se_set_dap_output_device (se_info, 0);

                    info ("Disconnect se block port #1\n");
                    bm_disconnect_block (se_info, 1);
                }
                else
                {
                    info ("Disconnect se block port #0\n");
                    bm_disconnect_block (se_info, 0);
                }
            }
        }
    }
#ifdef SUPPORT_DAFC
    else if (capture->substream->pcm->device == ALSA_CAP_HW_DAFC)
    {
        struct aud_block_info *se_info = NULL;
        alsa_se_handle_t handle = NULL;

        handle = alsa_se_get_handle ("COMMON_DAFC");

        if (handle)
        {
            se_info = alsa_se_get_block (handle);
            if (se_info)
            {
                info ("Disconnect se block port #1\n");
                bm_disconnect_block (se_info, 1);
            }
        }
    }
#endif
#endif

    if (capture->capture_info)
    {
        bm_disconnect_block (capture->capture_info, 0);
        bm_destroy_block (capture->capture_info);
        aimc_unregister_named_event (capture->event_id);
        capture->capture_info = NULL;
    }

    if (capture->encoder_info)
    {
        bm_disconnect_block (capture->encoder_info, 0);
        bm_destroy_block (capture->encoder_info);
        capture->encoder_info = NULL;
    }

    _acapture_destroy_se (capture);

  exit:
    return ret;
}


static void _acapture_connect_wisa (struct acapture_priv *capture)
{
    int output_port = 0;
    struct aud_block_info *mixer_info = bm_get_block_info_by_index ("mixer", 0);

    if (mixer_info == NULL)
    {
        error ("mixer_info is null\n");
        return;
    }

    capture->capture_info =
        bm_create_block_peer ("capture", capture->substream->pcm->device, mixer_info, true);

    if (capture->capture_info == NULL)
    {
        error ("error in create capture block\n");
        return;
    }

    aud_capture_set_es (capture->capture_info, false);
    aud_capture_set_disable (capture->capture_info, _cap_disable);

    if (capture->substream->runtime->channels > 3)
    {
        // switch connection from 2ch to 6ch output port of mixer
        output_port = 3;
        aud_capture_set_in_channel (capture->capture_info, 6);
        aud_capture_set_out_channel (capture->capture_info, 6);
        aud_capture_set_out_acmod (capture->capture_info, 7);
    }
    else if (capture->substream->runtime->channels == 3)
    {
        aud_capture_set_out_channel (capture->capture_info, 3);
        aud_capture_set_out_acmod (capture->capture_info, 2);
        aud_capture_set_generate_lfe (capture->capture_info, true);
    }
    else
    {
        aud_capture_set_out_channel (capture->capture_info, 2);
    }

    aud_capture_set_gain (capture->capture_info, sndout_get_capture_gain ());
    aud_capture_set_mute (capture->capture_info, sndout_get_capture_mute ());
    aud_capture_set_sampling_freq (capture->capture_info, capture->substream->runtime->rate);
    aud_capture_set_out_bps (capture->capture_info, capture->substream->runtime->sample_bits);

    bm_connect_block (mixer_info, output_port, capture->capture_info, 0);
}

static void _acapture_connect_atv (struct acapture_priv *capture)
{
    struct aud_block_info *decoder_info = bm_get_block_info_by_index ("decoder", aenc_info.dec_idx);

    capture->encoder_info =
        bm_create_block_peer ("encoder", capture->substream->pcm->device, decoder_info, true);

    if (capture->encoder_info == NULL)
    {
        error ("error in create encoder block\n");
        return;
    }

    if (aenc_info.codec == AENC_ENCODE_AAC)
    {
        aud_encoder_set_codec (capture->encoder_info, OUTPUT_CODEC_AAC, 2);
        aud_encoder_set_pre_gain (capture->encoder_info, aenc_info.gain);
    }

    if (decoder_info)
        bm_connect_block (decoder_info, 0, capture->encoder_info, 0);

    capture->capture_info =
        bm_create_block_peer ("capture", capture->substream->pcm->device, capture->encoder_info,
        true);

    if (capture->capture_info == NULL)
    {
        error ("error in create capture block\n");
        return;
    }

    aud_capture_set_es (capture->capture_info, true);
    aud_capture_set_aenc_header (capture->capture_info, true);

    bm_connect_block (capture->encoder_info, 0, capture->capture_info, 0);

    is_encoder_connected = true;
}

static struct aud_block_info *_acapture_get_se_info (common_output_ext_type_t output)
{
    struct aud_block_info *se_info = NULL;
    alsa_se_handle_t handle = NULL;

    if (output == COMMON_SE_BT || output == COMMON_SE_BT_SUR)
        handle = alsa_se_get_handle ("COMMON_SE_BT");
    else if (output == COMMON_DAP_HP_BT)
        handle = alsa_se_get_handle ("COMMON_DAP_HP_BT");
#ifdef SUPPORT_DAFC
    else if (output == COMMON_DAFC)
        handle = alsa_se_get_handle ("COMMON_DAFC");
#endif
    else
        error ("output is wrong\n");

    se_info = alsa_se_get_block (handle);

    return se_info;
}

static void _acapture_create_se (common_output_ext_type_t output)
{
    alsa_se_handle_t handle = NULL;

    info ("output = 0x%08X\n", output);

    if ((output == COMMON_SE_BT) || (output == COMMON_SE_BT_SUR))
    {
        handle = alsa_se_get_handle ("COMMON_SE_BT");

        if (handle)
            alsa_se_set_type (handle, (output == COMMON_SE_BT) ? "LGSE_BT" : "LGSE_BT_BTSUR");
    }
    else if (output == COMMON_DAP_HP_BT)
    {
        handle = alsa_se_get_handle ("COMMON_DAP_HP_BT");

        if (handle)
            alsa_se_set_type (handle, "LGSE_DAP_HP_BT");
    }
#ifdef SUPPORT_DAFC
    else if (output == COMMON_DAFC)
    {
        handle = alsa_se_get_handle ("COMMON_DAFC");

        if (handle)
            alsa_se_set_type (handle, "LGSE_DAFC");
    }
#endif

    return;
}

static void _acapture_destroy_se (struct acapture_priv *capture)
{
    alsa_se_handle_t handle = NULL;

    info ("output = 0x%X\n", capture->output);

    // Destroy DAP_HP_BT pipeline.
    if (capture->output == COMMON_DAP_HP_BT)
    {
        handle = alsa_se_get_handle ("COMMON_DAP_HP_BT");
        if (handle)
            alsa_se_set_type (handle, NULL);
    }
    else if ((capture->output == COMMON_SE_BT) || (capture->output == COMMON_SE_BT_SUR))
    {
        handle = alsa_se_get_handle ("COMMON_SE_BT");
        if (handle)
            alsa_se_set_type (handle, NULL);
    }
#ifdef SUPPORT_DAFC
    else if (capture->output == COMMON_DAFC)
    {
        handle = alsa_se_get_handle ("COMMON_DAFC");
        if (handle)
            alsa_se_set_type (handle, NULL);
    }
#endif
    return;
}

static void _acapture_connect_other (struct acapture_priv *capture)
{
    struct aud_block_info *mixer_info = bm_get_block_info_by_index ("mixer", 0);
    struct aud_block_info *se_info = NULL;
    common_output_ext_type_t output = COMMON_NO_OUTPUT;

    if (mixer_info == NULL)
    {
        error ("mixer_info is null\n");
        return;
    }

    if (sndout_output_connected_any (COMMON_SE_BT))
        output = COMMON_SE_BT;
    else if (sndout_output_connected_any (COMMON_SE_BT_SUR))
        output = COMMON_SE_BT_SUR;
    else if (sndout_output_connected_any (COMMON_DAP_HP_BT))
        output = COMMON_DAP_HP_BT;

    capture->output = output;

    if ((output == COMMON_SE_BT) || (output == COMMON_SE_BT_SUR) || (output == COMMON_DAP_HP_BT))
    {
        info ("Try to connect SE module  0x%08X\n", output);
        _acapture_create_se (output);

        se_info = _acapture_get_se_info (output);

        if (se_info == NULL)
        {
            error ("se_info is null\n");
            return;
        }

        capture->capture_info =
            bm_create_block_peer ("capture", capture->substream->pcm->device, se_info, true);

        if (capture->capture_info == NULL)
        {
            error ("error in create capture block\n");
            return;
        }

        aud_capture_set_es (capture->capture_info, false);

#ifndef SUPPORT_SOUNDBAR
        if (output == COMMON_DAP_HP_BT)
            bm_connect_block (mixer_info, 2, se_info, 1);
        else
            bm_connect_block (mixer_info, 0, se_info, 0);
#endif

        bm_connect_block (se_info, 0, capture->capture_info, 0);

        if (output == COMMON_DAP_HP_BT)
            se_set_dap_output_device (se_info, 1);
    }
    else
    {
        capture->capture_info =
            bm_create_block_peer ("capture", capture->substream->pcm->device, mixer_info, true);

        if (capture->capture_info == NULL)
        {
            error ("error in create capture block\n");
            return;
        }
        aud_capture_set_es (capture->capture_info, false);

        bm_connect_block (mixer_info, 0, capture->capture_info, 0);
    }
    aud_capture_set_disable (capture->capture_info, _cap_disable);

    aud_capture_set_gain (capture->capture_info, sndout_get_capture_gain ());
    aud_capture_set_mute (capture->capture_info, sndout_get_capture_mute ());
    aud_capture_set_sampling_freq (capture->capture_info, capture->substream->runtime->rate);
    aud_capture_set_out_channel (capture->capture_info, capture->substream->runtime->channels);
    aud_capture_set_out_bps (capture->capture_info, capture->substream->runtime->sample_bits);

    // only LE audio scenario
    if (leaudio_is_connected (capture))
    {
        aud_capture_set_out_samples (capture->capture_info,
            capture->substream->runtime->period_size);
    }

    return;
}

static void _acapture_connect_dsnoop (struct acapture_priv *capture)
{
    struct aud_block_info *mixer_info = bm_get_block_info_by_index ("mixer", 0);
    info ("Connnect for DSNOOP \n");

    if (mixer_info == NULL)
    {
        error ("mixer_info is NULL\n");
        return;
    }

    capture->capture_info =
        bm_create_block_peer ("capture", capture->substream->pcm->device, mixer_info, true);

    if (capture->capture_info == NULL)
    {
        error ("error in create capture block\n");
        return;
    }

    aud_capture_set_es (capture->capture_info, false);
    aud_capture_set_disable (capture->capture_info, _cap_disable);

    aud_capture_set_gain (capture->capture_info, 0x800000);     // force set default gain
    aud_capture_set_mute (capture->capture_info, false);        // force set mute off
    aud_capture_set_sampling_freq (capture->capture_info, capture->substream->runtime->rate);
    aud_capture_set_out_channel (capture->capture_info, capture->substream->runtime->channels);
    aud_capture_set_out_bps (capture->capture_info, capture->substream->runtime->sample_bits);

    bm_connect_block (mixer_info, 0, capture->capture_info, 0);
}

static void _acapture_connect_path (struct acapture_priv *capture)
{
    struct aud_block_info *source_block = NULL;

    struct aud_block_info *output_info = NULL;
    struct output_format output_format = { 0, };

    output_info = bm_get_block_info_by_index ("output", OUTPUT_ARC);
    if (output_info == NULL)
    {
        error ("can't get OUTPUT_ARC block");
    }
    else
    {
        output_get_format (output_info, &output_format);
        info ("output_format.codec        = %d\n", output_format.codec);
        info ("output_format.channel      = %d\n", output_format.channel);
        info ("output_format.sample_rate  =  %d\n", output_format.sample_rate);
    }

    info ("Connnect for Capture Path \n");

    source_block = _get_capture_source_block (_gAlsaCaptureSource);
    if (source_block == NULL)
    {
        error ("can't get source block (%d)", _gAlsaCaptureSource);
        return;
    }

    capture->capture_info =
        bm_create_block_peer ("capture", capture->substream->pcm->device, source_block, true);

    if (capture->capture_info == NULL)
    {
        error ("error in create capture block\n");
        return;
    }

    if ((output_format.codec == OUTPUT_CODEC_PCM)
        && (capture->substream->pcm->device != ALSA_CAP_HW_WOW))
        aud_capture_set_es (capture->capture_info, false);
    else
        aud_capture_set_es (capture->capture_info, true);

    aud_capture_set_disable (capture->capture_info, _cap_disable);

    if (capture->substream->runtime->channels == 8)
    {
        // switch connection 8ch
        aud_capture_set_in_channel (capture->capture_info, 8);
    }
    else if (capture->substream->runtime->channels > 3 && capture->substream->runtime->channels < 8)
    {
        // switch connection from 2ch to 6ch output port of mixer
        aud_capture_set_in_channel (capture->capture_info, 6);
    }

    aud_capture_set_gain (capture->capture_info, 0x800000);     // force set default gain
    aud_capture_set_mute (capture->capture_info, false);        // force set mute off
    aud_capture_set_sampling_freq (capture->capture_info, capture->substream->runtime->rate);
    aud_capture_set_out_channel (capture->capture_info, capture->substream->runtime->channels);
    aud_capture_set_out_bps (capture->capture_info, capture->substream->runtime->sample_bits);

    bm_connect_block (source_block, 0, capture->capture_info, 0);
}

#ifdef SUPPORT_DAFC
static void _acapture_connect_dafc (struct acapture_priv *capture)
{
    struct aud_block_info *se_info = NULL;
#ifndef SUPPORT_SOUNDBAR
    struct aud_block_info *mixer_info = bm_get_block_info_by_index ("mixer", 0);
#endif
    common_output_ext_type_t output = COMMON_NO_OUTPUT;

#ifndef SUPPORT_SOUNDBAR
    if (mixer_info == NULL)
    {
        error ("mixer_info is null\n");
        return;
    }
#endif

    if (sndout_output_connected_any (COMMON_DAFC))
        output = COMMON_DAFC;

    capture->output = output;

    info ("Try to connect SE module  0x%08X\n", output);
    _acapture_create_se (output);

    se_info = _acapture_get_se_info (COMMON_DAFC);
    if (se_info)
    {
        capture->capture_info =
            bm_create_block_peer ("capture", capture->substream->pcm->device, se_info, true);

        if (capture->capture_info == NULL)
        {
            error ("error in create capture block\n");
            return;
        }

        aud_capture_set_es (capture->capture_info, false);
        aud_capture_set_dafc_mode (capture->capture_info, true);
        aud_capture_set_disable (capture->capture_info, _cap_disable);


        noti ("DAFC ch is %d \n", capture->substream->runtime->channels);
        aud_capture_set_in_channel (capture->capture_info, capture->substream->runtime->channels);
        aud_capture_set_gain (capture->capture_info, 0x800000); // force set default gain
        aud_capture_set_mute (capture->capture_info, false);    // force set mute off
        aud_capture_set_sampling_freq (capture->capture_info, capture->substream->runtime->rate);
        aud_capture_set_out_channel (capture->capture_info, capture->substream->runtime->channels);
        aud_capture_set_out_bps (capture->capture_info, capture->substream->runtime->sample_bits);

#ifndef SUPPORT_SOUNDBAR
        bm_connect_block (mixer_info, 2, se_info, 1);
#endif
        bm_connect_block (se_info, 0, capture->capture_info, 0);
    }
    else
    {
        error ("se_info is NULL\n");
        return;
    }
}
#endif

/* connect capture module to MIX_0 */
static int _acapture_connect (struct acapture_priv *capture)
{
    int uid_capture = 0;
    int ret = RET_OK;
    unsigned int capture_rate = 0;
    struct snd_pcm_runtime *runtime = capture->substream->runtime;

    debug ("called\n");

    // only LE audio scenario
    if (leaudio_is_connected (capture))
    {
        capture_rate = sndout_get_resampling_freq ();
        if (capture_rate > 0)
        {
            noti ("change rate from %u to %u\n", runtime->rate, capture_rate);
            runtime->rate = capture_rate;
        }
    }

    trace ("rate          = %d\n", runtime->rate);
    trace ("channel       = %d\n", runtime->channels);
    trace ("sample_bits   = %d\n", runtime->sample_bits);
    trace ("frame_bits    = %d\n", runtime->frame_bits);
    trace ("period_size   = %ld\n", runtime->period_size);
    trace ("periods       = %d\n", runtime->periods);
    trace ("buffer_size   = %ld\n", runtime->buffer_size);
    trace ("start_threshold   = %ld\n", runtime->start_threshold);
    trace ("stop_threshold    = %ld\n", runtime->stop_threshold);
    trace ("silence_threshold = %ld\n", runtime->silence_threshold);

    if (capture->is_connected == true)
    {
        debug ("already connected.\n");
        _acapture_disconnect (capture);
        capture->output = COMMON_NO_OUTPUT;
    }

    if (capture->substream->pcm->device == ALSA_CAP_HW_AUTOTEST
        || capture->substream->pcm->device == ALSA_CAP_HW_WOW)
        _acapture_connect_path (capture);
    else if (capture->substream->pcm->device == ALSA_CAP_HW_ENC)
        _acapture_connect_atv (capture);
    else if (capture->substream->pcm->device == ALSA_CAP_HW_DSNOOP)
        _acapture_connect_dsnoop (capture);
#ifdef SUPPORT_DAFC
    else if (capture->substream->pcm->device == ALSA_CAP_HW_DAFC)
        _acapture_connect_dafc (capture);
#endif
    else                        // ALSA_CAP_HW_BT_WISA
    {
        if (sndout_output_connected_any (COMMON_WISA))
            _acapture_connect_wisa (capture);
        else
            _acapture_connect_other (capture);
    }

    uid_capture = bm_get_block_tail (capture->capture_info);
    ret = aimc_register_named_event (capture, _acapture_updated, uid_capture, "update", true);
    if (ret < 0)
    {
        if (capture->capture_info)
        {
            bm_destroy_block (capture->capture_info);
            capture->capture_info = NULL;
        }

        if (capture->encoder_info)
        {
            bm_destroy_block (capture->encoder_info);
            capture->encoder_info = NULL;
        }

        error ("fail to register evnet %d\n", ret);
        return ret;
    }

    capture->event_id = ret;

    // handle module id to alsa_sndout
    //sndout_update_capture_info (ModuleID_Gain, ModuleID_Pcmcvt);

    jiffies_start = jiffies;
    return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
// Register ack callback for Kernel 5.4
static void acapture_set_ack (struct snd_pcm *pcm, int (*ack) (struct snd_pcm_substream * substream))
{
    struct snd_pcm_str *stream = &pcm->streams[SNDRV_PCM_STREAM_CAPTURE];
    struct snd_pcm_substream *substream;

    for (substream = stream->substream; substream != NULL; substream = substream->next)
        memcpy ((void *) &substream->ops->ack, &ack, sizeof (int *));

    return;
}
#endif
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int acapture_open (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int acapture_open (struct snd_pcm_substream *substream)
#endif
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#endif
    struct acapture_priv *capture;

    debug ("called\n");
    info ("name %s\n", substream->name);
    info ("pcm name %s\n", substream->pcm->name);
    info ("pcm card name %s\n", substream->pcm->card->shortname);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    info ("cpu dai name %s -> %s\n", soc_pcm_rtd->cpu_dai->name, soc_pcm_rtd->codec_dai->name);
#endif
#if 0
    if (!strcmp (soc_pcm_rtd->cpu_dai->name, "lgsic-mc2.1") && gAlsaCaptureSource == 0)
    {
        error ("capture source not set.\n");
        return -EIO;
    }
#endif

    if (substream->pcm->device == ALSA_CAP_HW_ENC)
        snd_soc_set_runtime_hwparams (substream, &acapture_pcm_aenc_hardware);
    else if (substream->pcm->device == ALSA_CAP_HW_WOW)
        snd_soc_set_runtime_hwparams (substream, &acapture_pcm_wow_hardware);
#ifdef SUPPORT_DAFC
    else if (substream->pcm->device == ALSA_CAP_HW_DAFC)
        snd_soc_set_runtime_hwparams (substream, &acapture_pcm_dafc_hardware);
#endif
    else
        snd_soc_set_runtime_hwparams (substream, &acapture_pcm_hardware);

    if (substream->pcm->device == ALSA_CAP_HW_DSNOOP)
        substream->runtime->hw.formats = SNDRV_PCM_FMTBIT_S16_LE;

    capture = kzalloc (sizeof (struct acapture_priv), GFP_KERNEL);
    if (!capture)
        return -ENOMEM;

    capture->is_connected = false;

    if (substream->pcm->device == ALSA_CAP_HW_ENC)
        is_encoder_connected = false;

    capture->substream = substream;

    substream->runtime->private_data = capture;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    acapture_set_ack (substream->pcm, &acapture_ack);
#endif
#endif

    return 0;
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int acapture_close (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int acapture_close (struct snd_pcm_substream *substream)
#endif
{
    struct acapture_priv *capture = substream->runtime->private_data;

    debug ("called\n");

    if (!capture)
    {
        error ("already closed!!\n");
        return -EIO;
    }

    //TODO: block disconnection prior to destroy
    _acapture_disconnect (capture);

    // Set capture rate 0
    if (capture->substream->pcm->device == ALSA_CAP_HW_BT_WISA)
        sndout_set_resampling_freq (0);

    kfree (capture);

    noti ("free capture done.\n");

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int acapture_prepare (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int acapture_prepare (struct snd_pcm_substream *substream)
#endif
{
    struct acapture_priv *capture = substream->runtime->private_data;
    CaptureCmdSetBuffer cmd = { };
    int uid_capture = 0;
    int ret = 0;

    ret = _acapture_connect (capture);
    if (ret < 0)
    {
        error ("Error in capture module create or connection.");
        return -EIO;
    }
    capture->is_connected = true;

    uid_capture = bm_get_block_tail (capture->capture_info);
    // send dma address to capture module
    //TODO: AUDIO_GetLgbusAddr??
    cmd.buf_addr_p = capture->dma_addr;
    cmd.buf_size = snd_pcm_lib_buffer_bytes (substream);

    aimc_send_command_sync (NULL, CAPTURE_CMD_SET_BUFFER, 0, uid_capture,
        &cmd, sizeof (CaptureCmdSetBuffer));

    aimc_send_command_sync (NULL, CAPTURE_CMD_RESET_BUFFER, 0, uid_capture, NULL, 0);

    capture->wrOffset = 0;

    info ("reset buffer done.\n");

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int acapture_trigger (struct snd_soc_component *component, struct snd_pcm_substream *substream, int cmd)
#else
static int acapture_trigger (struct snd_pcm_substream *substream, int cmd)
#endif
{
    struct acapture_priv *capture = substream->runtime->private_data;
    int uid_capture = 0;

    uid_capture = bm_get_block_tail (capture->capture_info);

    switch (cmd)
    {
        case SNDRV_PCM_TRIGGER_STOP:
            aimc_send_command (NULL, ADEC_CMD_STOP, 0, uid_capture, NULL, 0);
            info ("stop\n");
            break;

        case SNDRV_PCM_TRIGGER_START:
            aimc_send_command (NULL, ADEC_CMD_START, 0, uid_capture, NULL, 0);
            info ("start\n");
            break;

        case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
            info ("pause_push\n");
            break;

        case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
            info ("pause_release\n");
            break;

        case SNDRV_PCM_TRIGGER_SUSPEND:
            info ("suspend\n");
            break;

        case SNDRV_PCM_TRIGGER_RESUME:
            info ("resume\n");
            break;

        case SNDRV_PCM_TRIGGER_DRAIN:
            info ("drain\n");
            break;

        default:
            error ("unknown command. %d\n", cmd);
            return -EINVAL;
    }

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int acapture_hw_params (struct snd_soc_component *component, struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params)
#else
static int acapture_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params)
#endif
{
    struct acapture_priv *capture = substream->runtime->private_data;
    const struct snd_interval *intv;

    debug ("called\n");

    /* dma buffer */
#ifdef SUPPORT_DAFC
    if (substream->pcm->device == ALSA_CAP_HW_DAFC)
        capture->dma_size = acapture_pcm_dafc_hardware.buffer_bytes_max;
    else
        capture->dma_size = acapture_pcm_hardware.buffer_bytes_max;
#else
    capture->dma_size = acapture_pcm_hardware.buffer_bytes_max;
#endif /* SUPPORT_SOUNDBAR */
    capture->dma_addr = hma_alloc_user (acapture_poolname, capture->dma_size, 4096, "alsa_capture");
    if (!capture->dma_addr)
    {
        error ("no mem for dma\n");
        kfree (capture);
        return -ENOMEM;
    }
    capture->dma_vaddr = hma_map (capture->dma_addr, capture->dma_size);
    if (!capture->dma_vaddr)
    {
        error ("cannot map dma buffer\n");
        hma_free (acapture_poolname, capture->dma_addr);
        kfree (capture);
        return -EIO;
    }
    info ("dma buffer %pap(0x%x), %p\n", &capture->dma_addr, capture->dma_size, capture->dma_vaddr);

    substream->dma_buffer.addr = capture->dma_addr;
    substream->dma_buffer.area = capture->dma_vaddr;
    substream->dma_buffer.bytes = capture->dma_size;

    info ("substream->dma_buffer.dev.type %d\n", substream->dma_buffer.dev.type);
    info ("substream->dma_buffer.dev.dev %p(%s)\n",
        substream->dma_buffer.dev.dev,
        substream->dma_buffer.dev.dev ? dev_name (substream->dma_buffer.dev.dev) : "NULL");
    info ("substream->dma_buffer.area %p\n", substream->dma_buffer.area);
    info ("substream->dma_buffer.addr %pad\n", &substream->dma_buffer.addr);
    info ("substream->dma_buffer.bytes %zu\n", substream->dma_buffer.bytes);
    info ("substream->dma_buffer.private_data %p\n", &substream->dma_buffer.private_data);

    intv = hw_param_interval_c (params, SNDRV_PCM_HW_PARAM_BUFFER_SIZE);
    info ("buffer_size min %d - max %d\n", intv->min, intv->max);

    snd_pcm_set_runtime_buffer (substream, &substream->dma_buffer);

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int acapture_hw_free (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int acapture_hw_free (struct snd_pcm_substream *substream)
#endif
{
    struct acapture_priv *capture = substream->runtime->private_data;

    debug ("called\n");

    snd_pcm_set_runtime_buffer (substream, NULL);

    hma_unmap (capture->dma_vaddr);
    hma_free ((const char *) acapture_poolname, capture->dma_addr);
    info ("hma free done\n");

    capture->dma_vaddr = NULL;
    capture->dma_addr = 0;

    info ("done\n");
    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static snd_pcm_uframes_t acapture_pointer (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static snd_pcm_uframes_t acapture_pointer (struct snd_pcm_substream *substream)
#endif
{
    struct acapture_priv *capture = substream->runtime->private_data;
    snd_pcm_uframes_t ret;
    unsigned int wrOffset = capture->wrOffset;

    if (wrOffset >= snd_pcm_lib_buffer_bytes (substream))
    {
        error
            ("wrong hardware pointer. hw_ptr 0x%x snd_pcm_lib_buffer_bytes (substream) %zd dma_buffer.addr %pad\n",
            wrOffset, snd_pcm_lib_buffer_bytes (substream), &capture->substream->dma_buffer.addr);
        wrOffset = 0;
    }

    ret = bytes_to_frames (substream->runtime, wrOffset);
    debug ("wrOffset 0x%05x, frames %4ld/%ld dma_buffer.addr %pad\n", wrOffset, ret,
        substream->runtime->buffer_size, &capture->substream->dma_buffer.addr);

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int acapture_mmap (struct snd_soc_component *component, struct snd_pcm_substream *substream, struct vm_area_struct *vma)
#else
static int acapture_mmap (struct snd_pcm_substream *substream, struct vm_area_struct *vma)
#endif
{
    int ret;

    debug ("called\n");
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 3, 0))
    vm_flags_set (vma, VM_DONTEXPAND | VM_DONTDUMP);
#else
    vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
#endif
    vma->vm_page_prot = pgprot_noncached (vma->vm_page_prot);

    ret = remap_pfn_range (vma, vma->vm_start,
        substream->dma_buffer.addr >> PAGE_SHIFT, vma->vm_end - vma->vm_start, vma->vm_page_prot);

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int acapture_ack (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int acapture_ack (struct snd_pcm_substream *substream)
#endif
{
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct acapture_priv *capture = substream->runtime->private_data;
    snd_pcm_sframes_t sw_ptr;

    debug ("called\n");

    sw_ptr = runtime->control->appl_ptr % runtime->buffer_size;
    capture->rdOffset = frames_to_bytes (substream->runtime, sw_ptr);
    debug ("rdOffset 0x%05x(%4ld)/%ld (buffered size %d)\n", capture->rdOffset, sw_ptr,
        runtime->buffer_size, (capture->wrOffset - capture->rdOffset));

    aud_capture_set_read_pointer (capture->capture_info, capture->rdOffset);
    return 0;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
static const struct snd_pcm_ops acapture_pcm_ops = {
    .open = acapture_open,
    .close = acapture_close,
    .ioctl = snd_pcm_lib_ioctl,
    .prepare = acapture_prepare,
    .trigger = acapture_trigger,
    .hw_params = acapture_hw_params,
    .hw_free = acapture_hw_free,
    .pointer = acapture_pointer,
    .mmap = acapture_mmap,
    .ack = acapture_ack,
};
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int acapture_pcm_new (struct snd_soc_component *component, struct snd_soc_pcm_runtime *soc_pcm_rtd)
#else
static int acapture_pcm_new (struct snd_soc_pcm_runtime *soc_pcm_rtd)
#endif
{
    debug ("called\n");
    info ("dai_link %p\n", soc_pcm_rtd->dai_link);
    if (soc_pcm_rtd->dai_link)
        info ("dai_link name %s(%s)\n", soc_pcm_rtd->dai_link->name,
            soc_pcm_rtd->dai_link->stream_name);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    info ("cpu_dai name %s(%p)\n", soc_pcm_rtd->cpu_dai->name,
        snd_soc_dai_get_drvdata (soc_pcm_rtd->cpu_dai));
    info ("codec_dai name %s\n", soc_pcm_rtd->codec_dai->name);
#endif
    info ("device name %s\n", dev_name (soc_pcm_rtd->dev));
    info ("card name %s\n", soc_pcm_rtd->card->name);

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void acapture_pcm_free (struct snd_soc_component *component, struct snd_pcm *pcm)
#else
static void acapture_pcm_free (struct snd_pcm *pcm)
#endif
{
    debug ("called\n");
}

static int _cap_enc_parm_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 3;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 1000;
    return 0;
}

static int _cap_enc_parm_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    ucontrol->value.integer.value[0] = aenc_info.dec_idx;
    ucontrol->value.integer.value[1] = aenc_info.codec;
    ucontrol->value.integer.value[2] = aenc_info.bitrate;

    info ("Get encoding info: dec_index=%d, codec=%d, bitrate=%d\n",
        aenc_info.dec_idx, aenc_info.codec, aenc_info.bitrate);

    return 0;
}

static int _cap_enc_parm_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int decoder_index;
    int codec;
    int bitrate;

    decoder_index = ucontrol->value.integer.value[0];
    codec = ucontrol->value.integer.value[1];
    bitrate = ucontrol->value.integer.value[2];

    if (decoder_index >= 2 || decoder_index < 0)
    {
        error ("index(%d) is invalid\n", decoder_index);
        return -1;
    }
    if (codec < AENC_ENCODE_MP3 || codec > AENC_ENCODE_PCM)
    {
        error ("encoding codec(%d) is invalid\n", codec);
        return -1;
    }
    if (bitrate < AENC_BIT_48K || bitrate > AENC_BIT_320K)
    {
        error ("encoding bitrate(%d) is invalid\n", bitrate);
        return -1;
    }

    aenc_info.dec_idx = decoder_index;
    aenc_info.codec = codec;
    aenc_info.bitrate = bitrate;

    info ("Set encoding info: dec_index=%d, codec=%d, bitrate=%d\n", decoder_index, codec, bitrate);

    return 0;
}

static int _cap_enc_volume_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = ALSA_INTEGER_GAIN_MAX;

    return 0;
}

static int _cap_enc_volume_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    ucontrol->value.integer.value[0] = aenc_info.gain;
    info ("enc volume = %u\n", aenc_info.gain);

    return 0;
}

static int _cap_enc_volume_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int volume;

    volume = ucontrol->value.integer.value[0];
    info ("set encoder gain: %d\n", volume);

    if (volume < 0 || volume > ALSA_INTEGER_GAIN_MAX)
    {
        error ("volume(%d) is invalid\n", volume);
        return -1;
    }

    if (aenc_info.gain != volume)
    {
        aenc_info.gain = volume;
    }

    return 0;
}

static int _cap_enc_pts_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER64;
    uinfo->count = 1;
    uinfo->value.integer64.min = 0;
    uinfo->value.integer64.max = 0x7FFFFFFFFFFFFFFF;

    return 0;
}

static int _cap_enc_pts_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    if (!aenc_info.pts)
    {
        noti ("get pts error\n");
        return -1;
    }

    ucontrol->value.integer64.value[0] = aenc_info.pts;

    debug ("PTS = %llu\n", ucontrol->value.integer64.value[0]);

    return 0;
}

static int _cap_disable_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 1;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 1;

    return 0;
}

static int _cap_disable_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    ucontrol->value.integer.value[0] = _cap_disable;
    info ("cap disable = %d\n", _cap_disable);

    return 0;
}

static int _cap_disable_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int cap_disable;
    int i = 0;
    struct aud_block_info *block = NULL;

    cap_disable = ucontrol->value.integer.value[0];
    info ("set capture disable: %d\n", cap_disable);

    if (cap_disable < 0 || cap_disable > 1)
    {
        error ("cap_disable (%d) is invalid\n", cap_disable);
        return -1;
    }

    _cap_disable = cap_disable;

    // Disable capture BT/WISA, WOWCAST
    for (i = ALSA_CAP_HW_BT_WISA; i <= ALSA_CAP_HW_MAX; i++)
    {
        if (i == ALSA_CAP_HW_ENC || i == ALSA_CAP_HW_DSNOOP || i == ALSA_CAP_HW_AUTOTEST)
            continue;
        block = bm_get_block_info_by_index ("capture", i);
        if (block)
            aud_capture_set_disable (block, cap_disable);
    }

    return 0;
}

static int _proc_aenc_status_show (struct seq_file *m, void *data)
{
    char *aencFormat = "UNKNOWN";
    char *aencBitrate = "0k";
    int i;

    struct aenc_format
    {
        aenc_encoding_format_t format;
        char *name;
    } aenc_format_info[] =
    {
        /* *INDENT-OFF* */
        { AENC_ENCODE_UNKNOWN, "UNKNOWN" },
        { AENC_ENCODE_MP3, "MP3" },
        { AENC_ENCODE_AAC, "AAC" },
        { AENC_ENCODE_PCM, "PCM" },
        /* *INDENT-ON* */
    };
    struct aenc_bitrate
    {
        aenc_bitrate_t bitrate;
        char *name;
    } aenc_bitrate_info[] =
    {
        /* *INDENT-OFF* */
        { AENC_BIT_UNKNOWN, "0k" },
        { AENC_BIT_48K, "48k" },
        { AENC_BIT_56K, "56k" },
        { AENC_BIT_64K, "64k" },
        { AENC_BIT_80K, "80k" },
        { AENC_BIT_112K, "112k" },
        { AENC_BIT_128K, "128k" },
        { AENC_BIT_160K, "160k" },
        { AENC_BIT_192K, "192k" },
        { AENC_BIT_224K, "224k" },
        { AENC_BIT_256K, "256k" },
        { AENC_BIT_320K, "320k" },
        /* *INDENT-ON* */
    };

    for (i = 0; i < sizeof (aenc_format_info) / sizeof (aenc_format_info[0]); i++)
    {
        if (aenc_format_info[i].format == aenc_info.codec)
            aencFormat = aenc_format_info[i].name;
    }
    for (i = 0; i < sizeof (aenc_bitrate_info) / sizeof (aenc_bitrate_info[0]); i++)
    {
        if (aenc_bitrate_info[i].bitrate == aenc_info.bitrate)
            aencBitrate = aenc_bitrate_info[i].name;
    }

    seq_printf (m, "status : %s\n", aenc_info.status ? "playing" : "idle");
    seq_printf (m, "pts : 0x%llX\n", aenc_info.pts);
    seq_printf (m, "decoder index : %d\n", aenc_info.dec_idx);
    seq_printf (m, "volume gain : %d dB\n", aenc_info.gain);
    seq_printf (m, "format : %s\n", aencFormat);
    seq_printf (m, "bitrate : %s\n", aencBitrate);

    return 0;
}

static int _proc_aenc_status_open (struct inode *inode, struct file *file)
{
    int ret;

    ret = single_open (file, _proc_aenc_status_show, NULL);
    if (ret < 0)
        return ret;

    return ret;
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops _proc_aenc_status_fops = {
    .proc_open = _proc_aenc_status_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};
#else
static struct file_operations _proc_aenc_status_fops = {
    .open = _proc_aenc_status_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};
#endif

static const struct snd_kcontrol_new capture_audio_controls[] = {
    /* *INDENT-OFF* */
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = AENC_INFO,
        .info = _cap_enc_parm_info,
        .get = _cap_enc_parm_get,
        .put = _cap_enc_parm_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = AENC_VOLUME,
        .info = _cap_enc_volume_info,
        .get = _cap_enc_volume_get,
        .put = _cap_enc_volume_put,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = AENC_PTS,
        .access = SNDRV_CTL_ELEM_ACCESS_READ,
        .info = _cap_enc_pts_info,
        .get = _cap_enc_pts_get,
    },
    {
        .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
        .name = SNDOUT_CAPTURE_DISABLE,
        .info = _cap_disable_info,
        .get = _cap_disable_get,
        .put = _cap_disable_put,
    },
    /* *INDENT-ON* */
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int acapture_probe (struct snd_soc_component *component)
#else
static int acapture_probe (struct snd_soc_platform *platform)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    struct platform_device *pdev = to_platform_device (component->dev);
#else
    struct platform_device *pdev = to_platform_device (platform->dev);
#endif

    info ("pdev name %s.%d\n", pdev->name, pdev->id);
    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void acapture_remove (struct snd_soc_component *component)
{
    debug ("called\n");
    return;
}

#else
static int acapture_remove (struct snd_soc_platform *platform)
{
    debug ("called\n");
    return 0;
}
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
static const struct snd_soc_platform_driver acapture_platform = {
#else
static const struct snd_soc_component_driver acapture_component[] = {
    {
#endif
            .probe = acapture_probe,
            .remove = acapture_remove,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
            .pcm_new = acapture_pcm_new,
            .pcm_free = acapture_pcm_free,
            .ops = &acapture_pcm_ops,
            .compr_ops = NULL,  //acapture_compr_ops,
#else
	    .pcm_construct = acapture_pcm_new,
            .pcm_destruct = acapture_pcm_free,
            .open = acapture_open,
            .close = acapture_close,
            .prepare = acapture_prepare,
            .trigger = acapture_trigger,
            .hw_params = acapture_hw_params,
            .hw_free = acapture_hw_free,
            .pointer = acapture_pointer,
            .mmap = acapture_mmap,
            .ack = acapture_ack,
	    .compress_ops = NULL,
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
            .name = "lgsic-acapture",
        },
#endif
};

static int acapture_dai_set_fmt (struct snd_soc_dai *dai, unsigned int fmt)
{
    debug ("called\n");
    return 0;
}

static int acapture_dai_startup (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("dai name %s\n", dai->name);
    return 0;
}

static void acapture_dai_shutdown (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("dai name %s\n", dai->name);
}

static int acapture_dai_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *hw_params, struct snd_soc_dai *dai)
{
    debug ("called\n");
    return 0;
}

static int acapture_dai_hw_free (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    debug ("called\n");
    return 0;
}

static int acapture_dai_prepare (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    debug ("called\n");
    return 0;
}

static const struct snd_soc_dai_ops acapture_dai_ops = {
    .set_fmt = acapture_dai_set_fmt,
    .startup = acapture_dai_startup,
    .shutdown = acapture_dai_shutdown,
    .hw_params = acapture_dai_hw_params,
    .hw_free = acapture_dai_hw_free,
    .prepare = acapture_dai_prepare,
};

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
static const struct snd_soc_component_driver acapture_component[] = {
    {.name = "lgsic-acapture",},
};
#endif

static struct snd_soc_dai_driver acapture_dai[] = {
    {
            .name = "lgsic-acapture",
            .id = 0,
            .capture = {
                    .channels_min = 2,
                    .channels_max = 8,
                    .rates = (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_192000),
                    .formats =
                    (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_BE |
                        SNDRV_PCM_FMTBIT_S32_BE),
                },
            .ops = &acapture_dai_ops,
        },

};

static int pdev_probe (struct platform_device *pdev)
{
    int ret;

    info ("probe.. %s id %d\n", pdev->name, pdev->id);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
    ret = snd_soc_register_platform (&pdev->dev, &acapture_platform);
    if (ret < 0)
    {
        error ("cannot register_platform(). %d\n", ret);
        return ret;
    }

    ret =
        snd_soc_register_component (&pdev->dev, &acapture_component[pdev->id],
        &acapture_dai[pdev->id], 1);
#else
    ret = snd_soc_register_component (&pdev->dev, acapture_component, acapture_dai, 1);
#endif

    if (ret < 0)
    {
        error ("cannot register component. %d\n", ret);
        return ret;
    }

    return 0;
}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,5,0)
static void pdev_remove (struct platform_device *pdev)
#else
static int pdev_remove (struct platform_device *pdev)
#endif
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    snd_soc_unregister_component (&pdev->dev);
#else
    snd_soc_unregister_platform (&pdev->dev);
#endif

    info ("done.\n");
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,5,0)
    return 0;
#endif
}

static struct platform_driver pdev_driver = {
    .driver = {
            .name = "lgsic-acapture",
        },
    .probe = pdev_probe,
    .remove = pdev_remove,
};

static struct platform_device *platform_device;

int acapture_init (void)
{
    int ret = RET_OK;

    ret = platform_driver_register (&pdev_driver);
    if (ret != RET_OK)
    {
        error ("platform_driver_register failed\n");
        return ret;
    }
    platform_device = platform_device_alloc ("lgsic-acapture", -1);
    if (!platform_device)
    {
        error ("platform_device_alloc failed\n");
        return -ENOMEM;
    }
    ret = platform_device_add (platform_device);
    if (ret != RET_OK)
    {
        error ("platform_device_add failed\n");
        return ret;
    }

    info ("completed\n");
    return ret;
}

void acapture_cleanup (void)
{
    platform_device_del (platform_device);
    platform_driver_unregister (&pdev_driver);
    info ("completed\n");
}

extern struct proc_dir_entry *aproc_seetv;
int register_aenc_audio_kcontrols (struct snd_soc_card *card)
{
    int ret = 0;

    ret =
        snd_soc_add_card_controls (card, capture_audio_controls,
        ARRAY_SIZE (capture_audio_controls));
    if (ret != RET_OK)
    {
        error ("add aenc control is failed (ret %d)\n", ret);
        return ret;
    }

    // create proc node for debug status
    proc_create_data ("aenc", 0440, aproc_seetv, &_proc_aenc_status_fops, NULL);

    info ("completed \n");
    return ret;
}
