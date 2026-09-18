/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
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
#include <sound/soc.h>

#include "logm.h"

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "decoder.h"
#include "renderer.h"
#include "block_manager.h"
#include "kaimc.h"
#include "alsa_sndout.h"
#include "alsa_platform.h"

#include "imc/cmd/module_cmd_capture.h"
#include "hma_alloc.h"
#include "module/adec_module_list.h"    ///< ADEC_CORE_ARM

#ifdef USE_DIRECT_CODEC
#include "linux/alsa-ext/alsa-ext-direct.h"
#endif

#define ALSA_DIRECT_DEVICE_NUM  2
#define ALSA_DEC_DEV_ID         8

#define ALSA_PLAYBACK_DEC_NUM 4
#ifdef SUPPORT_DAFC
#define ALSA_PLAYBACK_DAFC_HW   8
#endif
#ifdef SUPPORT_ULTRASENSE
#define ALSA_PLAYBACK_ULTRASENSE   9
#endif

typedef struct
{
    int codec;
    int samplingFreq;
    int numOfChannel;
    int bitPerSample;
} ALSA_DIRECT_INFO_T;


#ifdef USE_DIRECT_CODEC
ALSA_DIRECT_INFO_T gAlsaDirectInfo[ALSA_DIRECT_DEVICE_NUM] = {
    {DIRECT_CODEC_UNKNOWN, 0, 0, 0},
    {DIRECT_CODEC_UNKNOWN, 0, 0, 0},
};
#endif

logm_define (aplayback, log_level_noti);

#define error(fmt,args...)      logm_error(aplayback,fmt,##args)
#define warning(fmt,args...)    logm_warning(aplayback,fmt,##args)
#define noti(fmt,args...)       logm_noti(aplayback,fmt,##args)
#define info(fmt,args...)       logm_info(aplayback,fmt,##args)
#define debug(fmt,args...)      logm_debug(aplayback,fmt,##args)
#define trace(fmt,args...)      logm_trace(aplayback,fmt,##args)

static char *aplayback_poolname = "audio_buffer";
module_param (aplayback_poolname, charp, 0644);

struct aplayback_priv
{
    struct snd_pcm_substream *substream;

    struct aud_block_info *decoder_info;
    struct aud_block_info *renderer_info;
    int uid_playback;

    int is_connected;
    SINT32 event_id;
    bool is_started;
    bool use_decoder;

    phys_addr_t dma_addr;
    unsigned int dma_size;
    void *dma_vaddr;

    unsigned int wrOffset;
    unsigned int rdOffset;

#ifdef SUPPORT_SOUNDBAR
    unsigned int acmod;
    unsigned int remap;
    struct snd_pcm_chmap_elem chmap;
#endif
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int aplayback_ack (struct snd_soc_component *component, struct snd_pcm_substream *substream);
#else
static int aplayback_ack (struct snd_pcm_substream *substream);
#endif

#define PERIOD_SIZE_MIN             (256 /*sample */  * 2 /*channel */  * 2 /*byte */)
#ifdef SUPPORT_SOUNDBAR
#define PERIOD_SIZE_MAX             (256 /*sample */  * 12 /*channel */  * 4 /*byte */)
#else
#define PERIOD_SIZE_MAX             (256 /*sample */  * 2 /*channel */  * 4 /*byte */)
#endif

static struct snd_pcm_hardware aplayback_pcm_hardware = {
    .info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP,
    .formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE
        | SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_U16_BE
        | SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE
        | SNDRV_PCM_FMTBIT_U24_LE | SNDRV_PCM_FMTBIT_U24_BE
        | SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S32_BE
        | SNDRV_PCM_FMTBIT_U32_LE | SNDRV_PCM_FMTBIT_U32_BE
#ifdef SUPPORT_SOUNDBAR
        | SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE
        | SNDRV_PCM_FMTBIT_U24_3LE | SNDRV_PCM_FMTBIT_U24_3BE
        | SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S20_3BE
        | SNDRV_PCM_FMTBIT_U20_3LE | SNDRV_PCM_FMTBIT_U20_3BE
        | SNDRV_PCM_FMTBIT_S18_3LE | SNDRV_PCM_FMTBIT_S18_3BE
        | SNDRV_PCM_FMTBIT_U18_3LE | SNDRV_PCM_FMTBIT_U18_3BE | SNDRV_PCM_FMTBIT_FLOAT_LE
#endif
        ,
    .rates = SNDRV_PCM_RATE_48000,
    .rate_min = 48000,
    .rate_max = 48000,
    .channels_min = 2,
#ifdef SUPPORT_SOUNDBAR
    .channels_max = 12,
#else
    .channels_max = 8,
#endif
    .period_bytes_min = PERIOD_SIZE_MIN,
    .period_bytes_max = PERIOD_SIZE_MAX,
    .periods_min = 4,
    .periods_max = UINT_MAX,
#ifdef SUPPORT_SOUNDBAR
    .buffer_bytes_max = PERIOD_SIZE_MAX * 16,
#else
    .buffer_bytes_max = PERIOD_SIZE_MAX * 64,
#endif
    .fifo_size = 4,
};

#ifdef SUPPORT_SOUNDBAR
const struct snd_pcm_chmap_elem aplayback_chmaps[] = {
    /* *INDENT-OFF* */
    { .channels = 1, // MONO
      .map = { SNDRV_CHMAP_MONO } },
    { .channels = 2, // STEREO
      .map = { SNDRV_CHMAP_FL, SNDRV_CHMAP_FR } },
    { .channels = 4,
        .map = { SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
            SNDRV_CHMAP_RL, SNDRV_CHMAP_RR } },
    { .channels = 6, // AAC 5.1     acmod 7
      .map = { SNDRV_CHMAP_FC, SNDRV_CHMAP_FL,
           SNDRV_CHMAP_FR, SNDRV_CHMAP_SL,
           SNDRV_CHMAP_SR, SNDRV_CHMAP_LFE } },
    { .channels = 8, // MPEG 7.1    acmod 21
      .map = { SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
           SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE,
           SNDRV_CHMAP_SL, SNDRV_CHMAP_SR,
           SNDRV_CHMAP_RL, SNDRV_CHMAP_RR } },
    { .channels = 8, // ATMOS 5.1.2    acmod 28
      .map = { SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
           SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE,
           SNDRV_CHMAP_SL, SNDRV_CHMAP_SR,
           SNDRV_CHMAP_FLH, SNDRV_CHMAP_FRH } },
    { .channels = 10, // ATMOS 5.1.4   acmod 31
      .map = { SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
           SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE,
           SNDRV_CHMAP_SL, SNDRV_CHMAP_SR,
           SNDRV_CHMAP_FLH, SNDRV_CHMAP_FRH,
           SNDRV_CHMAP_TRL, SNDRV_CHMAP_TRR } },
    { .channels = 10, // ATMOS 7.1.2   acmod 41
      .map = { SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
           SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE,
           SNDRV_CHMAP_SL, SNDRV_CHMAP_SR,
           SNDRV_CHMAP_FLW, SNDRV_CHMAP_FRW,
           SNDRV_CHMAP_FLH, SNDRV_CHMAP_FRH } },
    { .channels = 12, // ATMOS 7.1.4    acmod 42
      .map = { SNDRV_CHMAP_FL, SNDRV_CHMAP_FR,
           SNDRV_CHMAP_FC,  SNDRV_CHMAP_LFE,
           SNDRV_CHMAP_SL,  SNDRV_CHMAP_SR,
           SNDRV_CHMAP_FLW, SNDRV_CHMAP_FRW,
           SNDRV_CHMAP_FLH, SNDRV_CHMAP_FRH,
           SNDRV_CHMAP_TRL,  SNDRV_CHMAP_TRR } },
    { }
    /* *INDENT-ON* */
};

struct aplayback_chmap_table
{
    unsigned int idx;
    unsigned int ch;
    unsigned int acmod;
    unsigned long mask;
    unsigned int remap;
};

enum aplayback_ch_bit
{
    /* *INDENT-OFF* */
    UNKNOWN = BIT( SNDRV_CHMAP_UNKNOWN),
    NA      = BIT( SNDRV_CHMAP_NA     ),      /* N/A, silent */
    MONO    = BIT( SNDRV_CHMAP_MONO   ),      /* mono stream */
    FL      = BIT( SNDRV_CHMAP_FL     ),      /* front left */
    FR      = BIT( SNDRV_CHMAP_FR     ),      /* front right */
    RL      = BIT( SNDRV_CHMAP_RL     ),      /* rear left */
    RR      = BIT( SNDRV_CHMAP_RR     ),      /* rear right */
    FC      = BIT( SNDRV_CHMAP_FC     ),      /* front center */
    LFE     = BIT( SNDRV_CHMAP_LFE    ),      /* LFE */
    SL      = BIT( SNDRV_CHMAP_SL     ),      /* side left */
    SR      = BIT( SNDRV_CHMAP_SR     ),      /* side right */
    RC      = BIT( SNDRV_CHMAP_RC     ),      /* rear center */
    FLC     = BIT( SNDRV_CHMAP_FLC    ),      /* front left center */
    FRC     = BIT( SNDRV_CHMAP_FRC    ),      /* front right center */
    RLC     = BIT( SNDRV_CHMAP_RLC    ),      /* rear left center */
    RRC     = BIT( SNDRV_CHMAP_RRC    ),      /* rear right center */
    FLW     = BIT( SNDRV_CHMAP_FLW    ),      /* front left wide */
    FRW     = BIT( SNDRV_CHMAP_FRW    ),      /* front right wide */
    FLH     = BIT( SNDRV_CHMAP_FLH    ),      /* front left high */
    FCH     = BIT( SNDRV_CHMAP_FCH    ),      /* front center high */
    FRH     = BIT( SNDRV_CHMAP_FRH    ),      /* front right high */
    TC      = BIT( SNDRV_CHMAP_TC     ),      /* top center */
    TFL     = BIT( SNDRV_CHMAP_TFL    ),      /* top front left */
    TFR     = BIT( SNDRV_CHMAP_TFR    ),      /* top front right */
    TFC     = BIT( SNDRV_CHMAP_TFC    ),      /* top front center */
    TRL     = BIT( SNDRV_CHMAP_TRL    ),      /* top rear left */
    TRR     = BIT( SNDRV_CHMAP_TRR    ),      /* top rear right */
    TRC     = BIT( SNDRV_CHMAP_TRC    ),      /* top rear center */
    TFLC    = BIT( SNDRV_CHMAP_TFLC   ),      /* top front left center */
    TFRC    = BIT( SNDRV_CHMAP_TFRC   ),      /* top front right center */
    TSL     = BIT( SNDRV_CHMAP_TSL    ),      /* top side left */
    TSR     = BIT( SNDRV_CHMAP_TSR    ),      /* top side right */
    LLFE    = BIT( SNDRV_CHMAP_LLFE   ),      /* left LFE */
    RLFE    = BIT( SNDRV_CHMAP_RLFE   ),      /* right LFE */
    BC      = BIT( SNDRV_CHMAP_BC     ),      /* bottom center */
    BLC     = BIT( SNDRV_CHMAP_BLC    ),      /* bottom left center */
    BRC     = BIT( SNDRV_CHMAP_BRC    ),      /* bottom right center */
    /* *INDENT-ON* */
};

static const struct aplayback_chmap_table aplayback_chmap_tables[] = {
    {
            // AAC_5_1: // 5.1   < C L R Ls Rs Lfe >
            .idx = 0,
            .ch = 6,
            .acmod = 7,
            .remap = 1,
        .mask = FC | FL | FR | SL | SR | LFE},
    {
            //MPEG_7_1_C: // 7.1   < L R C LFE Ls Rs Rls Rrs >
            .idx = 1,
            .ch = 8,
            .acmod = 21,
            .remap = 0,
        .mask = FL | FR | FC | LFE | SL | SR | RL | RR},
    {
            //Atmos_5_1_2: // 5.1.2 < L R C LFE Ls Rs Ltm Rtm >
            .idx = 2,
            .ch = 8,
            .acmod = 28,
            .remap = 2,
        .mask = FL | FR | FC | LFE | SL | SR | FLH | FRH},
    {
            //Atmos_5_1_4: // 5.1.4 < L R C LFE Ls Rs Vhl Vhr Ltr Rtr >
            .idx = 3,
            .ch = 10,
            .acmod = 31,
            .remap = 3,
        .mask = FL | FR | FC | LFE | SL | SR | FLH | FRH | TRL | TRR},
    {
            //Atmos_7_1_2: // 7.1.2 < L R C LFE Ls Rs Rls Rrs Ltm Rtm >
            .idx = 4,
            .ch = 10,
            .acmod = 41,
            .remap = 0,
        .mask = FL | FR | FC | LFE | SL | SR | FLW | FRW | FLH | FRH},
    {
            //Atmos_7_1_4: // 7.1.4 < L R C LFE Ls Rs Rls Rrs Vhl Vhr Ltr Rtr >
            .idx = 5,
            .ch = 12,
            .acmod = 42,
            .remap = 0,
        .mask = FL | FR | FC | LFE | SL | SR | FLW | FRW | FLH | FRH | TRL | TRR},
};


static int aplayback_chmap_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    struct snd_pcm_chmap *info = snd_kcontrol_chip (kcontrol);

    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = info->max_channels;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = SNDRV_CHMAP_LAST;

    return 0;
}

static unsigned long aplayback_masking_bit (struct aplayback_priv *aplayback)
{
    int i;
    unsigned long mask = 0;
    struct snd_pcm_chmap_elem *aplayback_chmap = &aplayback->chmap;
    for (i = 0; i < aplayback_chmap->channels; i++)
    {
        mask |= 1 << aplayback_chmap->map[i];
    }

    return mask;
}

static unsigned int aplayback_choose_acmod (struct snd_pcm_substream *substream)
{
    struct aplayback_priv *aplayback = substream->runtime->private_data;
    struct snd_pcm_runtime *runtime = substream->runtime;
    int i = 0;

    unsigned long mask = aplayback_masking_bit (aplayback);
    const struct aplayback_chmap_table *table = aplayback_chmap_tables;

    for (i = 0; i < ARRAY_SIZE (aplayback_chmap_tables); i++, table++)
    {
        if (table->ch == runtime->channels && (table->mask == mask))
            return table->acmod;
    }
    return 0;
}

static unsigned int aplayback_choose_remap (struct snd_pcm_substream *substream)
{
    struct aplayback_priv *aplayback = substream->runtime->private_data;
    struct snd_pcm_runtime *runtime = substream->runtime;
    int i = 0;

    unsigned long mask = aplayback_masking_bit (aplayback);
    const struct aplayback_chmap_table *table = aplayback_chmap_tables;

    for (i = 0; i < ARRAY_SIZE (aplayback_chmap_tables); i++, table++)
    {
        if (table->ch == runtime->channels && (table->mask == mask))
            return table->remap;
    }
    return 0;
}

static int aplayback_chmap_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    info ("%s:%d\n", __func__, __LINE__);
    return 0;
}

static int aplayback_chmap_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int i = 0;
    struct snd_pcm_chmap *info = snd_kcontrol_chip (kcontrol);
    struct snd_pcm_substream *substream = info->private_data;
    struct aplayback_priv *aplayback = substream->runtime->private_data;
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct snd_pcm_chmap_elem *aplayback_chmap = &aplayback->chmap;

    info ("%s:%d info->max_channels = %d\n", __func__, __LINE__, info->max_channels);
    info ("called hw num:%d, ch:%d samplebits:%d, rate:%d, format:%d\n", substream->pcm->device,
        runtime->channels, runtime->sample_bits, runtime->rate, runtime->format);

    memset (aplayback_chmap, 0, sizeof (struct snd_pcm_chmap_elem));

    aplayback_chmap->channels = runtime->channels;
    for (i = 0; i < runtime->channels; i++)
    {
        aplayback_chmap->map[i] = ucontrol->value.integer.value[i];
        info ("%s:%d map[%d] = %d\n", __func__, __LINE__, i, aplayback_chmap->map[i]);
    }

    aplayback->acmod = aplayback_choose_acmod (substream);
    aplayback->remap = aplayback_choose_remap (substream);
    info ("acmod = %d, remap = %d\n", aplayback->acmod, aplayback->remap);
    return 0;
}

static int aplayback_set_acmod (struct snd_pcm_substream *substream)
{
    struct aplayback_priv *aplayback = substream->runtime->private_data;
    struct snd_pcm_runtime *runtime = substream->runtime;

    if (runtime->channels == 1)
        aplayback->acmod = 1;
    else if (runtime->channels == 0 || runtime->channels == 2)
        aplayback->acmod = 2;
    else if (runtime->channels == 6)
        aplayback->acmod = 7;
    else if (runtime->channels == 8)
        aplayback->acmod = 21;
    else if (runtime->channels == 10)
        aplayback->acmod = 31;
    else if (runtime->channels == 12)   //7.1.4, mixer.c
        aplayback->acmod = 42;
    else if (runtime->channels == 16)   //9.1.6, mixer.c
        aplayback->acmod = 55;

    info ("aplayback->acmod = %d\n", aplayback->acmod);
    return 0;
}
#endif //SUPPORT_SOUNDBAR

/* For DAFC or Ultrasense */
static bool _aplayback_is_with_output (struct aplayback_priv *aplayback)
{
#ifdef SUPPORT_DAFC
    if (aplayback->substream->pcm->device == ALSA_PLAYBACK_DAFC_HW)
    {
        info ("ALSA_PLAYBACK_DAFC_HW (%d)\n", aplayback->substream->pcm->device);
        return true;
    }
#endif
#ifdef SUPPORT_ULTRASENSE
    if (aplayback->substream->pcm->device == ALSA_PLAYBACK_ULTRASENSE)
    {
        info ("ALSA_PLAYBACK_ULTRASENSE (%d)\n", aplayback->substream->pcm->device);
        return true;
    }
#endif
    return false;
}

/**
 * callback function to update wrPrt
 * @see		_aplayback_connect().
 */
static int _aplayback_updated (void *_param, int _paramLen, void *_cbParam)
{
    struct aplayback_priv *aplayback = _cbParam;
    int rdOffset = 0;

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    struct snd_soc_pcm_runtime *soc_pcm_rtd = aplayback->substream->pcm->private_data;
    debug ("(device:%d) got callback from\n", soc_pcm_rtd->cpu_dai->id);
#endif
    if (aplayback == NULL)
    {
        error ("aplayback is NULL!!\n");
        return -1;
    }

    if (aplayback->substream == NULL)
    {
        error ("aplayback->substream is NULL!!\n");
        return -1;
    }

    if (_param && _paramLen)
    {
        rdOffset = *(int *) _param;
        trace ("rdOffset is 0x%08x\n", rdOffset);
        aplayback->rdOffset = rdOffset;
        snd_pcm_period_elapsed (aplayback->substream);
    }

    return 0;
}

static int _aplayback_disconnect (struct aplayback_priv *aplayback)
{
    int ret = RET_OK;

    debug ("called\n");
    if (aplayback->is_connected == false)
    {
        debug ("not connected.\n");
        goto exit;
    }

    if (aplayback->use_decoder)
        bm_disconnect_block (aplayback->renderer_info, 0);
    aimc_module_disconnect_output (aplayback->uid_playback, 0);

    aplayback->is_connected = false;

  exit:
    return ret;
}

static int _aplayback_connect (struct aplayback_priv *aplayback)
{
    int uid_head = 0;
    int ret = RET_OK;
    int bm_renderer_index = 0;
    int bm_decoder_index = 0;

    debug ("called\n");

    if (aplayback->is_connected == 1)
    {
        debug ("already connected.\n");
        //_aplayback_disconnect (aplayback);
    }

    // bm_create_block()호출시 아래와 같이 index를 수정
    // Dolby 계열  0, 1
    // 이외는 12,13
#ifdef USE_DIRECT_CODEC
    if (aplayback->use_decoder)
    {
        int decoder_index = aplayback->substream->pcm->device - ALSA_DEC_DEV_ID;

        switch (gAlsaDirectInfo[decoder_index].codec)
        {
            case DIRECT_CODEC_AC3:
            case DIRECT_CODEC_AAC:
                bm_renderer_index = aplayback->substream->pcm->device - ALSA_DEC_DEV_ID;
                bm_decoder_index = aplayback->substream->pcm->device - ALSA_DEC_DEV_ID;
                break;
            case DIRECT_CODEC_PCM:
            case DIRECT_CODEC_DRA:
            case DIRECT_CODEC_MP3:
            case DIRECT_CODEC_WMA_PRO:
#ifdef SUPPORT_DTSX
            case DIRECT_CODEC_DTS:
#endif
            case DIRECT_CODEC_VORBIS:
            case DIRECT_CODEC_AMR_WB:
            case DIRECT_CODEC_AMR_NB:
            case DIRECT_CODEC_ADPCM:
            case DIRECT_CODEC_RA8:
                bm_renderer_index = aplayback->substream->pcm->device + ALSA_PLAYBACK_DEC_NUM;
                bm_decoder_index = aplayback->substream->pcm->device + ALSA_PLAYBACK_DEC_NUM;
                break;
            default:
                error ("codec info is not set\n");
                ret = RET_ERROR;
                goto exit;
        }
    }
    else
#endif
    {
        bm_renderer_index = aplayback->substream->pcm->device + ALSA_PLAYBACK_DEC_NUM;
        bm_decoder_index = -1;
    }



    if (!aplayback->renderer_info)
    {
        if (_aplayback_is_with_output (aplayback))
        {
            struct aud_block_info *output_info = bm_get_block_info_by_index ("output", 0);
            if (output_info)
            {
                aplayback->renderer_info =
                    bm_create_block_peer ("renderer", bm_renderer_index, output_info, true);
            }
            else
            {
                error ("output_info is NULL\n");
                goto exit;
            }
        }
        else
            aplayback->renderer_info = bm_create_block ("renderer", bm_renderer_index);
    }
    uid_head = bm_get_block_head (aplayback->renderer_info);


#ifdef USE_DIRECT_CODEC
    if (aplayback->use_decoder)
    {
        int decoder_index = aplayback->substream->pcm->device - ALSA_DEC_DEV_ID;
        enum audio_decoder_codec codec = AUDIO_DECODER_CODEC_UNKNOWN;

        switch (gAlsaDirectInfo[decoder_index].codec)
        {
            case DIRECT_CODEC_PCM:
                codec = AUDIO_DECODER_CODEC_PCM;
                break;

            case DIRECT_CODEC_AC3:
                codec = AUDIO_DECODER_CODEC_AC3;
                break;

            case DIRECT_CODEC_AAC:
                codec = AUDIO_DECODER_CODEC_AAC;
                break;

            case DIRECT_CODEC_DRA:
                codec = AUDIO_DECODER_CODEC_DRA;
                break;

            case DIRECT_CODEC_MP3:
                codec = AUDIO_DECODER_CODEC_MP3;
                break;

            case DIRECT_CODEC_WMA_PRO:
                codec = AUDIO_DECODER_CODEC_WMA_PRO;
                break;

            case DIRECT_CODEC_VORBIS:
                codec = AUDIO_DECODER_CODEC_VORBIS;
                break;

            case DIRECT_CODEC_AMR_WB:
                codec = AUDIO_DECODER_CODEC_AMR_WB;
                break;

            case DIRECT_CODEC_AMR_NB:
                codec = AUDIO_DECODER_CODEC_AMR_NB;
                break;

            case DIRECT_CODEC_ADPCM:
                codec = AUDIO_DECODER_CODEC_ADPCM;
                break;

            case DIRECT_CODEC_FLAC:
                codec = AUDIO_DECODER_CODEC_FLAC;
                break;

            default:
                error ("codec info is not set\n");
                ret = RET_ERROR;
                goto exit;
        }

        if (!aplayback->decoder_info)
            aplayback->decoder_info = bm_create_block ("decoder", bm_decoder_index);
        decoder_set_codec (aplayback->decoder_info, codec);
        decoder_set_param (aplayback->decoder_info,
            "channels=%d bits-per-sample=%d sampling-rate=%d",
            gAlsaDirectInfo[decoder_index].numOfChannel,
            gAlsaDirectInfo[decoder_index].bitPerSample,
            gAlsaDirectInfo[decoder_index].samplingFreq);
        uid_head = bm_get_block_head (aplayback->decoder_info);
        bm_connect_block (aplayback->decoder_info, 0, aplayback->renderer_info, 0);
    }
#endif

    if (aplayback->uid_playback <= 0)
    {
        int preferred_processor = ADEC_CORE_DSP2;

        if (_aplayback_is_with_output (aplayback))
        {
            preferred_processor = ADEC_CORE_DSP1;
        }
        else
        {
#ifdef SUPPORT_SOUNDBAR
            preferred_processor = ADEC_CORE_DSP0;
#else
            preferred_processor = ADEC_CORE_DSP2;
#endif
        }

        aplayback->uid_playback = aimc_module_create ("playback", preferred_processor);
        info ("Create 0x%08X\n", aplayback->uid_playback);

        ret = aimc_register_named_event (aplayback, _aplayback_updated,
            aplayback->uid_playback, "update", true);
        if (ret < 0)
        {
            error ("fail to register evnet %d\n", ret);
            goto exit;
        }

        aplayback->event_id = ret;
    }

    ret = aimc_module_connect (aplayback->uid_playback, 0, uid_head, 0);
    if (ret < 0)
    {
        error ("aimc_module_connect err\n");
        goto exit;
    }

    aplayback->is_connected = true;

    return 0;

  exit:

    return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
// Register ack callback for Kernel 5.4
static void aplayback_set_ack (struct snd_pcm *pcm,
    int (*ack) (struct snd_pcm_substream * substream))
{
    struct snd_pcm_str *stream = &pcm->streams[SNDRV_PCM_STREAM_PLAYBACK];
    struct snd_pcm_substream *substream;

    for (substream = stream->substream; substream != NULL; substream = substream->next)
        memcpy ((void *) &substream->ops->ack, &ack, sizeof (int *));

    return;
}
#endif
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int aplayback_open (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int aplayback_open (struct snd_pcm_substream *substream)
#endif
{
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
    struct aplayback_priv *aplayback;
    int ret = RET_OK;

    noti ("open pcm device, %d\n", substream->pcm->device);

    debug ("called\n");
    info ("name %s\n", substream->name);
    info ("pcm name %s, %d\n", substream->pcm->name, substream->pcm->device);
    info ("pcm card name %s\n", substream->pcm->card->shortname);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    info ("cpu dai name %s -> %s\n", soc_pcm_rtd->cpu_dai->name, soc_pcm_rtd->codec_dai->name);
    info ("cpu dai id %d\n", soc_pcm_rtd->cpu_dai->id);
#endif
    snd_soc_set_runtime_hwparams (substream, &aplayback_pcm_hardware);

    aplayback = kzalloc (sizeof (struct aplayback_priv), GFP_KERNEL);
    if (!aplayback)
    {
        error ("Error in playback malloc.\n");
        return -ENOMEM;
    }

    aplayback->is_connected = false;
    aplayback->is_started = false;

    aplayback->substream = substream;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    dev_set_drvdata (soc_pcm_rtd->dev, (void *) aplayback);
#else
    dev_set_drvdata (soc_pcm_rtd->platform->dev, (void *) aplayback);
#endif

    if (substream->pcm->device >= ALSA_DEC_DEV_ID)
    {
        aplayback->use_decoder = true;
    }


    ret = _aplayback_connect (aplayback);
    if (ret != RET_OK)
    {
        error ("Error in playback module create or connection.\n");
        kfree (aplayback);
        return -EIO;
    }

    substream->runtime->private_data = aplayback;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    aplayback_set_ack (substream->pcm, &aplayback_ack);
#endif
#endif

    noti ("open aplayback done.\n");

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int aplayback_close (struct snd_soc_component *component,
    struct snd_pcm_substream *substream)
#else
static int aplayback_close (struct snd_pcm_substream *substream)
#endif
{
    struct aplayback_priv *aplayback = substream->runtime->private_data;

    debug ("called\n");


    _aplayback_disconnect (aplayback);

    if (aplayback->decoder_info)
    {
        bm_destroy_block (aplayback->decoder_info);
    }

#ifdef SUPPORT_ULTRASENSE
    if (aplayback->substream->pcm->device == ALSA_PLAYBACK_ULTRASENSE)
    {
        struct aud_block_info *output_info = bm_get_block_info_by_index ("output", 0);
        if (output_info)
        {
            bm_disconnect_block (output_info, 1);
        }
    }
#endif
    if (aplayback->renderer_info)
    {
        bm_destroy_block (aplayback->renderer_info);
    }

    aimc_unregister_named_event (aplayback->event_id);
    aimc_module_destroy (aplayback->uid_playback);

    kfree (aplayback);

    noti ("free aplayback done.\n");

    return 0;
}

static int _aplayback_set_format (struct snd_pcm_substream *substream)
{
    enum renderer_endian_t endian;
    enum renderer_sign_t sign;

    struct aplayback_priv *aplayback = substream->runtime->private_data;
    snd_pcm_format_t pcm_format = substream->runtime->format;   /* SNDRV_PCM_FORMAT_* */
    info ("substream->runtime->format = %d\n", pcm_format);

    switch (pcm_format)
    {
        case SNDRV_PCM_FORMAT_S8:
        case SNDRV_PCM_FORMAT_S16_LE:
        case SNDRV_PCM_FORMAT_S24_LE:
        case SNDRV_PCM_FORMAT_S32_LE:
        case SNDRV_PCM_FORMAT_S24_3LE:
            endian = renderer_endian_le;
            sign = renderer_sign_signed;
            break;

        case SNDRV_PCM_FORMAT_U8:
        case SNDRV_PCM_FORMAT_U16_LE:
        case SNDRV_PCM_FORMAT_U24_LE:
        case SNDRV_PCM_FORMAT_U32_LE:
        case SNDRV_PCM_FORMAT_U24_3LE:
            endian = renderer_endian_le;
            sign = renderer_sign_unsigned;
            break;

        case SNDRV_PCM_FORMAT_S16_BE:
        case SNDRV_PCM_FORMAT_S24_BE:
        case SNDRV_PCM_FORMAT_S32_BE:
        case SNDRV_PCM_FORMAT_S24_3BE:
            endian = renderer_endian_be;
            sign = renderer_sign_signed;
            break;

        case SNDRV_PCM_FORMAT_U16_BE:
        case SNDRV_PCM_FORMAT_U24_BE:
        case SNDRV_PCM_FORMAT_U32_BE:
        case SNDRV_PCM_FORMAT_U24_3BE:
            endian = renderer_endian_be;
            sign = renderer_sign_unsigned;
            break;

        default:
            endian = renderer_endian_le;
            sign = renderer_sign_signed;
            break;
    }

    noti ("endian = %d, sign = %d\n", endian, sign);
    renderer_set_endian_sign (aplayback->renderer_info, endian, sign);

    {
        struct snd_pcm_runtime *runtime = substream->runtime;
        bool downmix;

        downmix = sndout_get_input_downmix_enable (0x10, substream->pcm->device);

        if (!downmix)
            noti ("downmix = %d\n", downmix);

        if (downmix == false
#ifdef SUPPORT_DAFC
            || aplayback->substream->pcm->device == ALSA_PLAYBACK_DAFC_HW
#endif
            )
            renderer_set_param (aplayback->renderer_info, "out-channels=%d", runtime->channels);
    }

    return 0;
}


#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int aplayback_prepare (struct snd_soc_component *component,
    struct snd_pcm_substream *substream)
#else
static int aplayback_prepare (struct snd_pcm_substream *substream)
#endif
{
    struct aplayback_priv *aplayback = substream->runtime->private_data;
    struct snd_pcm_runtime *runtime = substream->runtime;
    CaptureCmdSetBuffer cmd = { };

    info ("called hw num:%d, ch:%d samplebits:%d, rate:%d, format:%d, period_size:%lu\n",
        substream->pcm->device, runtime->channels, runtime->sample_bits, runtime->rate,
        runtime->format, runtime->period_size);

#ifdef SUPPORT_SOUNDBAR
    if (aplayback->acmod == 0)
        aplayback_set_acmod (substream);

    info ("acmod:%d, remap:%d\n", aplayback->acmod, aplayback->remap);
#endif

    //TODO: AUDIO_GetLgbusAddr??
    cmd.buf_addr_p = aplayback->dma_addr;
    cmd.buf_size = snd_pcm_lib_buffer_bytes (substream);

#ifdef SUPPORT_SOUNDBAR
    aimc_set_property (aplayback->uid_playback,
        "channels=%d\\bits-per-sample=%d\\rate=%d\\format=%d\\acmod=%d\\remap=%d",
        runtime->channels, runtime->sample_bits, runtime->rate, runtime->format, aplayback->acmod,
        aplayback->remap);
#else
    aimc_set_property (aplayback->uid_playback,
        "channels=%d\\bits-per-sample=%d\\rate=%d\\format=%d", runtime->channels,
        runtime->sample_bits, runtime->rate, runtime->format);
#endif

    aimc_send_command_sync (NULL, CAPTURE_CMD_SET_BUFFER, 0, aplayback->uid_playback,
        &cmd, sizeof (CaptureCmdSetBuffer));

    // audio dsp 와 kernel rdOffset 일치.
    aplayback->rdOffset = 0;
    snd_pcm_period_elapsed (aplayback->substream);
    aimc_send_command_sync (NULL, CAPTURE_CMD_RESET_BUFFER, 0, aplayback->uid_playback, NULL, 0);

    info ("reset buffer done.\n");

    _aplayback_set_format (substream);

    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int aplayback_trigger (struct snd_soc_component *component,
    struct snd_pcm_substream *substream, int cmd)
#else
static int aplayback_trigger (struct snd_pcm_substream *substream, int cmd)
#endif
{
    struct aplayback_priv *aplayback = substream->runtime->private_data;

    switch (cmd)
    {
        case SNDRV_PCM_TRIGGER_STOP:
            info ("stop\n");
            aplayback->is_started = false;
            break;

        case SNDRV_PCM_TRIGGER_START:
            info ("start\n");
            // if pcm data exists
            if (substream->runtime->control->appl_ptr == substream->runtime->buffer_size)
            {
                snd_pcm_sframes_t sw_ptr =
                    substream->runtime->control->appl_ptr % substream->runtime->buffer_size;
                aplayback->wrOffset = frames_to_bytes (substream->runtime, sw_ptr);
                aimc_set_property (aplayback->uid_playback, "wrOffset=%d", aplayback->wrOffset);
            }
            aplayback->is_started = true;
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

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int aplayback_hw_params (struct snd_soc_component *component,
    struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params)
#else
static int aplayback_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params)
#endif
{
    struct aplayback_priv *aplayback = substream->runtime->private_data;
    const struct snd_interval *intv;

    debug ("called\n");

    /* dma buffer */
    aplayback->dma_size = aplayback_pcm_hardware.buffer_bytes_max;
    aplayback->dma_addr =
        hma_alloc_user (aplayback_poolname, aplayback->dma_size, 1024, "alsa_playback");
    if (!aplayback->dma_addr)
    {
        error ("no mem for dma\n");
        kfree (aplayback);
        return -ENOMEM;
    }
    aplayback->dma_vaddr = hma_map (aplayback->dma_addr, aplayback->dma_size);
    if (!aplayback->dma_vaddr)
    {
        error ("cannot map dma buffer\n");
        hma_free (aplayback_poolname, aplayback->dma_addr);
        kfree (aplayback);
        return -EIO;
    }
    info ("dma buffer %pap(0x%x), %p\n", &aplayback->dma_addr, aplayback->dma_size,
        aplayback->dma_vaddr);

    substream->dma_buffer.addr = aplayback->dma_addr;
    substream->dma_buffer.area = aplayback->dma_vaddr;
    substream->dma_buffer.bytes = aplayback->dma_size;

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


#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int aplayback_hw_free (struct snd_soc_component *component,
    struct snd_pcm_substream *substream)
#else
static int aplayback_hw_free (struct snd_pcm_substream *substream)
#endif
{
    struct aplayback_priv *aplayback = substream->runtime->private_data;

    debug ("called. vaddr %p\n", aplayback->dma_vaddr);

    snd_pcm_set_runtime_buffer (substream, NULL);

    hma_unmap (aplayback->dma_vaddr);
    hma_free ((const char *) aplayback_poolname, aplayback->dma_addr);
    info ("hma free done\n");

    aplayback->dma_vaddr = NULL;
    aplayback->dma_addr = 0;
#ifdef SUPPORT_SOUNDBAR
    aplayback->acmod = 0;
    aplayback->remap = 0;
#endif

    info ("done\n");
    return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static snd_pcm_uframes_t aplayback_pointer (struct snd_soc_component *component,
    struct snd_pcm_substream *substream)
#else
static snd_pcm_uframes_t aplayback_pointer (struct snd_pcm_substream *substream)
#endif
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#endif
    struct aplayback_priv *aplayback = substream->runtime->private_data;
    snd_pcm_uframes_t ret;
    unsigned int rdOffset = aplayback->rdOffset;

    if (rdOffset >= snd_pcm_lib_buffer_bytes (substream))
    {
        error ("wrong hardware pointer. hw_ptr 0x%x, dma_size 0x%x\n", rdOffset,
            aplayback->dma_size);
        rdOffset = 0;
    }

    ret = bytes_to_frames (substream->runtime, rdOffset);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    debug ("(device:%d) rdOffset 0x%05x, frames %4ld/%ld\n", soc_pcm_rtd->cpu_dai->id, rdOffset,
        ret, substream->runtime->buffer_size);
#endif
    return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int aplayback_mmap (struct snd_soc_component *component, struct snd_pcm_substream *substream,
    struct vm_area_struct *vma)
#else
static int aplayback_mmap (struct snd_pcm_substream *substream, struct vm_area_struct *vma)
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

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,5,0)
static int aplayback_ack (struct snd_soc_component *component, struct snd_pcm_substream *substream)
#else
static int aplayback_ack (struct snd_pcm_substream *substream)
#endif
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
    struct snd_soc_pcm_runtime *soc_pcm_rtd = substream->pcm->private_data;
#endif
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct aplayback_priv *aplayback = substream->runtime->private_data;
    snd_pcm_sframes_t sw_ptr;

    debug ("called runtime->control->appl_ptr:%lu buffer_size:%lu\n", runtime->control->appl_ptr,
        runtime->buffer_size);

    if (aplayback->is_started)
    {
        sw_ptr = runtime->control->appl_ptr % runtime->buffer_size;
        aplayback->wrOffset = frames_to_bytes (substream->runtime, sw_ptr);
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,5,0)
        debug ("(device:%d) wrOffset 0x%05x sw_ptr %4ld buffer_size %ld rdOffset 0x%05x\n",
            soc_pcm_rtd->cpu_dai->id, aplayback->wrOffset, sw_ptr, runtime->buffer_size,
            aplayback->rdOffset);
#endif
        aimc_set_property (aplayback->uid_playback, "wrOffset=%d", aplayback->wrOffset);
    }

    return 0;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
static const struct snd_pcm_ops aplayback_pcm_ops = {
    .open = aplayback_open,
    .close = aplayback_close,
    .ioctl = snd_pcm_lib_ioctl,
    .prepare = aplayback_prepare,
    .trigger = aplayback_trigger,
    .hw_params = aplayback_hw_params,
    .hw_free = aplayback_hw_free,
    .pointer = aplayback_pointer,
    .mmap = aplayback_mmap,
    .ack = aplayback_ack,
};
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static int aplayback_pcm_new (struct snd_soc_component *component,
    struct snd_soc_pcm_runtime *soc_pcm_rtd)
#else
static int aplayback_pcm_new (struct snd_soc_pcm_runtime *soc_pcm_rtd)
#endif
{
#ifdef SUPPORT_SOUNDBAR
    struct snd_pcm_chmap *chmap;
    struct snd_kcontrol *kctl;
    struct snd_pcm *pcm = soc_pcm_rtd->pcm;
    struct snd_pcm_str *pcm_str = &pcm->streams[SNDRV_PCM_STREAM_PLAYBACK];
    struct snd_pcm_substream *substream = pcm_str->substream;
    int ret, i;
#endif

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

#ifdef SUPPORT_SOUNDBAR
    info ("snd_pcm_add_chmap_ctls()\n");
    ret =
        snd_pcm_add_chmap_ctls (soc_pcm_rtd->pcm, SNDRV_PCM_STREAM_PLAYBACK, aplayback_chmaps, 12,
        0, &chmap);
    if (ret < 0)
    {
        error ("snd_pcm_add_chmap_ctls() failed. ret = %d\n", ret);
        return ret;
    }

    chmap->private_data = substream;

    kctl = chmap->kctl;

    // Add WRITE ACCESS
    for (i = 0; i < kctl->count; i++)
        kctl->vd[i].access |= SNDRV_CTL_ELEM_ACCESS_WRITE;
    kctl->get = aplayback_chmap_get;
    kctl->put = aplayback_chmap_put;
    kctl->info = aplayback_chmap_info;
#endif

    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
static void aplayback_pcm_free (struct snd_soc_component *component, struct snd_pcm *pcm)
#else
static void aplayback_pcm_free (struct snd_pcm *pcm)
#endif
{
    debug ("called\n");
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static int aplayback_probe (struct snd_soc_component *component)
#else
static int aplayback_probe (struct snd_soc_platform *platform)
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
static void aplayback_remove (struct snd_soc_component *component)
{
    debug ("called\n");
    return;
}
#else
static int aplayback_remove (struct snd_soc_platform *platform)
{
    debug ("called\n");
    return 0;
}
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static const struct snd_soc_component_driver aplayback_component = {
#else
static const struct snd_soc_platform_driver aplayback_platform = {
#endif
    .probe = aplayback_probe,
    .remove = aplayback_remove,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 5, 0))
    .pcm_new = aplayback_pcm_new,
    .pcm_free = aplayback_pcm_free,
    .ops = &aplayback_pcm_ops,
    .compr_ops = NULL,          //aplayback_compr_ops,
#else
    .pcm_construct = aplayback_pcm_new,
    .pcm_destruct = aplayback_pcm_free,
    .open = aplayback_open,
    .close = aplayback_close,
    .prepare = aplayback_prepare,
    .trigger = aplayback_trigger,
    .hw_params = aplayback_hw_params,
    .hw_free = aplayback_hw_free,
    .pointer = aplayback_pointer,
    .mmap = aplayback_mmap,
    .ack = aplayback_ack,
    .compress_ops = NULL,
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    .name = "lgsic-aplayback",
#endif
};

static int aplayback_dai_set_fmt (struct snd_soc_dai *dai, unsigned int fmt)
{
    debug ("called\n");
    return 0;
}

static int aplayback_dai_startup (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("dai name %s\n", dai->name);
    return 0;
}

static void aplayback_dai_shutdown (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    info ("dai name %s\n", dai->name);
}

static int aplayback_dai_hw_params (struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *hw_params, struct snd_soc_dai *dai)
{
    debug ("called\n");
    return 0;
}

static int aplayback_dai_hw_free (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    debug ("called\n");
    return 0;
}

static int aplayback_dai_prepare (struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
    debug ("called\n");
    return 0;
}

static const struct snd_soc_dai_ops aplayback_dai_ops = {
    .set_fmt = aplayback_dai_set_fmt,
    .startup = aplayback_dai_startup,
    .shutdown = aplayback_dai_shutdown,
    .hw_params = aplayback_dai_hw_params,
    .hw_free = aplayback_dai_hw_free,
    .prepare = aplayback_dai_prepare,
};

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
static const struct snd_soc_component_driver aplayback_component[] = {
    {.name = "lgsic-aplayback",},
};
#endif

static struct snd_soc_dai_driver aplayback_dai[] = {
    {
            .name = "lgsic-aplayback",
            .id = 0,
            .playback = {
                    .channels_min = 2,
#ifdef SUPPORT_SOUNDBAR
                    .channels_max = 12,
#else
                    .channels_max = 8,
#endif
                    .rates = SNDRV_PCM_RATE_48000,
                    .formats = SNDRV_PCM_FMTBIT_S16_LE,
                },
            .ops = &aplayback_dai_ops,
        },
};

static int pdev_probe (struct platform_device *pdev)
{
    int ret;

    info ("probe.. %s\n", pdev->name);

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,4,0)
    ret = snd_soc_register_platform (&pdev->dev, &aplayback_platform);
    if (ret < 0)
    {
        error ("cannot register_platform(). %d\n", ret);
        return ret;
    }
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
    ret =
        snd_soc_register_component (&pdev->dev, &aplayback_component, aplayback_dai,
        ARRAY_SIZE (aplayback_dai));
#else
    ret =
        snd_soc_register_component (&pdev->dev, aplayback_component, aplayback_dai,
        ARRAY_SIZE (aplayback_dai));
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
            .name = "lgsic-aplayback",
        },
    .probe = pdev_probe,
    .remove = pdev_remove,
};

#ifdef USE_DIRECT_CODEC
static int direct_codec_info (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    uinfo->count = 10;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 192000;
    return 0;
}

static int direct_codec_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int index;

    for (index = 0; index < ALSA_DIRECT_DEVICE_NUM; index++)
    {
        ucontrol->value.integer.value[index * 5] = index;
        ucontrol->value.integer.value[index * 5 + 1] = gAlsaDirectInfo[index].codec;
        ucontrol->value.integer.value[index * 5 + 2] = gAlsaDirectInfo[index].samplingFreq;
        ucontrol->value.integer.value[index * 5 + 3] = gAlsaDirectInfo[index].numOfChannel;
        ucontrol->value.integer.value[index * 5 + 4] = gAlsaDirectInfo[index].bitPerSample;
        info ("direct index(%ld), codec(%ld), freq(%ld), ch(%ld), bps(%ld)\n",
            ucontrol->value.integer.value[index * 5],
            ucontrol->value.integer.value[index * 5 + 1],
            ucontrol->value.integer.value[index * 5 + 2],
            ucontrol->value.integer.value[index * 5 + 3],
            ucontrol->value.integer.value[index * 5 + 4]);
    }

    return 0;
}

static int direct_codec_put (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
    int index;

    index = ucontrol->value.integer.value[0];

    if (index >= ALSA_DIRECT_DEVICE_NUM)
    {
        error ("index(%ld) is invalid\n", ucontrol->value.integer.value[0]);
        return -1;
    }

    if (ucontrol->value.integer.value[1] >= DIRECT_CODEC_MAX)
    {
        error ("codec(%ld) is invalid\n", ucontrol->value.integer.value[1]);
        return -1;
    }

    if (ucontrol->value.integer.value[1] == DIRECT_CODEC_RA8
#ifdef SUPPORT_DTSX
        || ucontrol->value.integer.value[1] == DIRECT_CODEC_DTS
#endif
        )
    {
        error ("codec(%ld) is not supported\n", ucontrol->value.integer.value[1]);
        return -1;
    }

    gAlsaDirectInfo[index].codec = ucontrol->value.integer.value[1];
    gAlsaDirectInfo[index].samplingFreq = ucontrol->value.integer.value[2];
    gAlsaDirectInfo[index].numOfChannel = ucontrol->value.integer.value[3];
    gAlsaDirectInfo[index].bitPerSample = ucontrol->value.integer.value[4];

    info ("idx=%d, codec=%d, freq=%d, ch=%d, bps=%d\n", index, gAlsaDirectInfo[index].codec,
        gAlsaDirectInfo[index].samplingFreq, gAlsaDirectInfo[index].numOfChannel,
        gAlsaDirectInfo[index].bitPerSample);
    return 0;
}

static const struct snd_kcontrol_new direct_audio_controls[] = {
    {
            .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
            .name = DIRECT_CODEC,
            .info = direct_codec_info,
            .get = direct_codec_get,
            .put = direct_codec_put,
        },
};

int register_direct_audio_kcontrols (struct snd_soc_card *card)
{
    int ret = 0;

    ret =
        snd_soc_add_card_controls (card, direct_audio_controls, ARRAY_SIZE (direct_audio_controls));
    if (ret != 0)
    {
        error ("add control is failed (ret %d)\n", ret);
        return ret;
    }

    info ("completed \n");
    return ret;
}
#endif

static struct platform_device *platform_device;

int aplayback_init (void)
{
    int ret = 0;

    ret = platform_driver_register (&pdev_driver);
    if (ret != 0)
    {
        error ("platform_driver_register failed\n");
        return ret;
    }
    platform_device = platform_device_alloc ("lgsic-aplayback", -1);
    if (!platform_device)
    {
        error ("platform_device_alloc failed\n");
        return -ENOMEM;
    }
    ret = platform_device_add (platform_device);
    if (ret != 0)
    {
        error ("platform_device_add failed\n");
        return ret;
    }

    info ("completed\n");
    return ret;
}

void aplayback_cleanup (void)
{
    platform_device_del (platform_device);
    platform_driver_unregister (&pdev_driver);
    info ("completed\n");
}
