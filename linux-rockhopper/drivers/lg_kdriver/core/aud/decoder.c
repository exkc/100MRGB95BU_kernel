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

/** @defgroup Decoder
  * @{
  *
  * @brief
  * Decoder module for audio kernel driver
  * @detail
  *
  *
  * @}
  */

/** @file
  * @ingroup Decoder
  *
  *  implementation for Decoder
  *
  *  @author Youngjun Jang (youngjun.jang@lge.com)
  *  version	0.1
  *  date	2020.06.30
  *  note	Additional information.
  *
  */

//#include <linux/spinlock.h>
#include <linux/slab.h>

#include "log.h"
#include "kaimc.h"
#include "hma_alloc.h"
#include "os_util.h"

#include "block.h"
#include "block_manager.h"
#include "decoder.h"
#include "ipc_regs.h"
#include "common/ipc_reg_offs.h"

#include "imc/evt/module_evt_tp.h"
#include "imc/evt/module_evt_hdmi.h"
#include "imc/evt/module_evt_dec.h"
#include "imc/cmd/module_cmd_mpegh.h"
#include "module/adec_module_list.h"    ///< ADEC_CORE_ARM

#include "notifier.h"

logm_define (adecoder, log_level_noti);
#define trace(fmt,args...)	logm_trace(adecoder,fmt,##args)
#define debug(fmt,args...)	logm_debug(adecoder,fmt,##args)
#define info(fmt,args...)	logm_info(adecoder,fmt,##args)
#define noti(fmt,args...)	logm_noti(adecoder,fmt,##args)
#define error(fmt,args...)	logm_error(adecoder,fmt,##args)

static DEFINE_MUTEX (_dec_lock);

#define AUD_DEC_LOCK()         mutex_lock(&_dec_lock)
#define AUD_DEC_UNLOCK()       mutex_unlock(&_dec_lock)

static DEFINE_MUTEX (_dec_prop_lock);

#define AUD_DEC_PROP_LOCK()    mutex_lock(&_dec_prop_lock)
#define AUD_DEC_PROP_UNLOCK()  mutex_unlock(&_dec_prop_lock)

static DEFINE_MUTEX (_dec_event_lock);

#define AUD_DEC_EVENT_LOCK()   mutex_lock(&_dec_event_lock)
#define AUD_DEC_EVENT_UNLOCK() mutex_unlock(&_dec_event_lock)

struct mpegh_ui_param
{
    phys_addr_t phys_addr;
    void *virtual_addr;
    unsigned int offset;
    unsigned int size;
};

struct aud_decoder_property_info
{
    char *name;
    char *data;

    struct list_head list;
};

struct aud_decoder_event_info
{
    char *name;
    int id;
    int (*cb_func) (void *, int, void *);
    int repeat;

    struct list_head list;
};

/**
 * AUDIO Decoder Information.
 */
struct aud_decoder_info
{
    struct aud_block_info parent;

    struct apipeline *pipeline_bypass;

    unsigned int uid_decbin;
    unsigned int uid_dec;
    unsigned int uid_queue;

    unsigned int uid_bypass;

    bool is_bypass_created;
    bool is_dummy_codec;

    enum audio_decoder_input input;
    enum audio_decoder_codec codec;
    enum audio_decoder_drc drc;

    struct decoded_info es_info;

    struct mpegh_ui_param ui_param;

    struct list_head list_prop;
    struct list_head list_event;
#ifdef SUPPORT_SOUNDBAR
    struct list_head list_pending_event;
    struct list_head list_pending_prop;
#endif
};

#define ADEC_DECODER_CODEC_NAME(id)  {AUDIO_DECODER_CODEC_##id, #id}

struct str_table
{
    int id;
    const char *name;
};

static const struct str_table codec_name[] = {
    ADEC_DECODER_CODEC_NAME (UNKNOWN),
    ADEC_DECODER_CODEC_NAME (PCM),
    ADEC_DECODER_CODEC_NAME (AC3),
    ADEC_DECODER_CODEC_NAME (EAC3),
    ADEC_DECODER_CODEC_NAME (AC4),
    ADEC_DECODER_CODEC_NAME (MAT),
    ADEC_DECODER_CODEC_NAME (TRUE_HD),
    ADEC_DECODER_CODEC_NAME (AAC),
    ADEC_DECODER_CODEC_NAME (MP3),
    ADEC_DECODER_CODEC_NAME (MPEG_H),
    ADEC_DECODER_CODEC_NAME (DRA),
#ifdef SUPPORT_WMA
    ADEC_DECODER_CODEC_NAME (WMA_PRO),
#endif
    ADEC_DECODER_CODEC_NAME (VORBIS),
    ADEC_DECODER_CODEC_NAME (AMR_WB),
    ADEC_DECODER_CODEC_NAME (AMR_NB),
    ADEC_DECODER_CODEC_NAME (ADPCM),
    ADEC_DECODER_CODEC_NAME (FLAC),
#ifdef SUPPORT_DTSX
    ADEC_DECODER_CODEC_NAME (DTS),
#endif
    ADEC_DECODER_CODEC_NAME (OPUS),
    ADEC_DECODER_CODEC_NAME (AAC_BYPASS),
    ADEC_DECODER_CODEC_NAME (AAC_ELD),
    ADEC_DECODER_CODEC_NAME (RA8),
    ADEC_DECODER_CODEC_NAME (IAMF),
    ADEC_DECODER_CODEC_NAME (AUTO),
};

static const char *get_codec_name (enum audio_decoder_codec codec)
{
    int i;

    for (i = 0; i < sizeof (codec_name) / sizeof (codec_name[0]); i++)
    {
        if (codec_name[i].id == codec)
            return codec_name[i].name;
    }
    return codec_name[0].name;
}

static enum audio_decoder_codec convert_codec_type (ADEC_MEDIA_TYPE media_type)
{
    enum audio_decoder_codec codec;

    switch (media_type)
    {
        case ADEC_MEDIA_PCM:
            codec = AUDIO_DECODER_CODEC_PCM;
            break;
        case ADEC_MEDIA_MS10_DDC:
            codec = AUDIO_DECODER_CODEC_AC3;
            break;
        case ADEC_MEDIA_MS10_DDT:
            codec = AUDIO_DECODER_CODEC_AAC;
            break;
        case ADEC_MEDIA_DRA:
            codec = AUDIO_DECODER_CODEC_DRA;
            break;
        case ADEC_MEDIA_MP3:
            codec = AUDIO_DECODER_CODEC_MP3;
            break;
        case ADEC_MEDIA_MPEG_H:
            codec = AUDIO_DECODER_CODEC_MPEG_H;
            break;
        case ADEC_MEDIA_AC4:
            codec = AUDIO_DECODER_CODEC_AC4;
            break;
#ifdef SUPPORT_WMA
        case ADEC_MEDIA_WMA_PRO:
            codec = AUDIO_DECODER_CODEC_WMA_PRO;
            break;
#endif
        case ADEC_MEDIA_OGG:
            codec = AUDIO_DECODER_CODEC_VORBIS;
            break;
        case ADEC_MEDIA_AMR_WB:
            codec = AUDIO_DECODER_CODEC_AMR_WB;
            break;
        case ADEC_MEDIA_AMR_NB:
            codec = AUDIO_DECODER_CODEC_AMR_NB;
            break;
        case ADEC_MEDIA_ADPCM:
            codec = AUDIO_DECODER_CODEC_ADPCM;
            break;
        case ADEC_MEDIA_RA8:
            codec = AUDIO_DECODER_CODEC_RA8;
            break;
        case ADEC_MEDIA_FLAC:
            codec = AUDIO_DECODER_CODEC_FLAC;
            break;
        case ADEC_MEDIA_OPUS:
            codec = AUDIO_DECODER_CODEC_OPUS;
            break;
        case ADEC_MEDIA_MAT:
            codec = AUDIO_DECODER_CODEC_MAT;
            break;
        case ADEC_MEDIA_AACELD:
            codec = AUDIO_DECODER_CODEC_AAC_ELD;
            break;
#ifdef SUPPORT_DTSX
        case ADEC_MEDIA_DTS_M6:
        case ADEC_MEDIA_DTS_X:
            codec = AUDIO_DECODER_CODEC_DTS;
            break;
#endif
        case ADEC_MEDIA_IAMF:
            codec = AUDIO_DECODER_CODEC_IAMF;
            break;
        default:
            codec = AUDIO_DECODER_CODEC_UNKNOWN;
            break;
    }

    return codec;
}

struct channel_mode_table
{
    unsigned int channel_mode;
    enum audio_decoder_channel_mode audio_mode;
    unsigned int channels;
};

/* *INDENT-OFF* */
struct channel_mode_table ch_mode_pcm[] = {
    { PCMDEC_CHANNELMODE_UNDEFINED, AUDIO_DECODER_CH_MODE_UNKNOWN, 0 },
    { PCMDEC_CHANNELMODE_1CH,       AUDIO_DECODER_CH_MODE_MONO,    1 },
    { PCMDEC_CHANNELMODE_2CH,       AUDIO_DECODER_CH_MODE_STEREO,  2 },
    { PCMDEC_CHANNELMODE_3CH,       AUDIO_DECODER_CH_MODE_MULTI,   3 },
    { PCMDEC_CHANNELMODE_4CH,       AUDIO_DECODER_CH_MODE_MULTI,   4 },
    { PCMDEC_CHANNELMODE_5CH,       AUDIO_DECODER_CH_MODE_MULTI,   5 },
    { PCMDEC_CHANNELMODE_6CH,       AUDIO_DECODER_CH_MODE_MULTI,   6 },
};
/* *INDENT-ON* */

/* *INDENT-OFF* */
#ifdef SUPPORT_SOUNDBAR
// HADEC(AC3, MAT) 공통으로 사용
struct channel_mode_table ch_mode_dolby[] = {
    { HADEC_CHANNELMODE_DUAL_MONO,       AUDIO_DECODER_CH_MODE_DUAL_MONO, 2 },
    { HADEC_CHANNELMODE_MONO_CENTER,     AUDIO_DECODER_CH_MODE_MONO,      1 },
    { HADEC_CHANNELMODE_STEREO,          AUDIO_DECODER_CH_MODE_STEREO,    2 },
    { HADEC_CHANNELMODE_3_0_1_0_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     4 },
    { HADEC_CHANNELMODE_2_1_1_0_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     4 },
    { HADEC_CHANNELMODE_3_1_1_0_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     5 },
    { HADEC_CHANNELMODE_2_2_1_0_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     5 },
    { HADEC_CHANNELMODE_3_2_1_0_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     6 },
    { HADEC_CHANNELMODE_3_4_1_0_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     8 },
    { HADEC_CHANNELMODE_3_2_1_2_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     8 },
    { HADEC_CHANNELMODE_3_2_1_4_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,    10 },
    { HADEC_CHANNELMODE_3_0_1_2_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     6 },
    { HADEC_CHANNELMODE_3_4_1_4_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,    12 },
    { HADEC_CHANNELMODE_3_6_1_4_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,    14 },
    { HADEC_CHANNELMODE_3_6_1_6_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,    16 },
};
#else
// AAC, AC3, AC4 공통으로 사용
struct channel_mode_table ch_mode_dolby[] = {
    { MS10DDC_CHANNELMODE_DUAL_MONO,   AUDIO_DECODER_CH_MODE_DUAL_MONO, 2 },
    { MS10DDC_CHANNELMODE_MONO_CENTER, AUDIO_DECODER_CH_MODE_MONO,      1 },
    { MS10DDC_CHANNELMODE_STEREO,      AUDIO_DECODER_CH_MODE_STEREO,    2 },
    { MS10DDC_CHANNELMODE_3_0_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     3 },
    { MS10DDC_CHANNELMODE_2_1_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     3 },
    { MS10DDC_CHANNELMODE_3_1_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     4 },
    { MS10DDC_CHANNELMODE_2_2_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     4 },
    { MS10DDC_CHANNELMODE_3_2_CHANNEL, AUDIO_DECODER_CH_MODE_MULTI,     6 },
    { MS10DDC_CHANNELMODE_5_1_CHANNEL_LRS_RRS, AUDIO_DECODER_CH_MODE_MULTI, 8 },
    { MS10DDC_CHANNELMODE_5_1_CHANNEL_LTF_RTF, AUDIO_DECODER_CH_MODE_MULTI, 8 },
    { MS10DDC_CHANNELMODE_5_1_CHANNEL_LRS_RRS_LTF_RTF, AUDIO_DECODER_CH_MODE_MULTI, 10 },
    { MS10DDC_CHANNELMODE_5_1_CHANNEL_LTF_RTF_LTR_RTR, AUDIO_DECODER_CH_MODE_MULTI, 10 },
};
#endif
/* *INDENT-ON* */

/* *INDENT-OFF* */
struct channel_mode_table ch_mode_mp3[] = {
    { MP3DEC_CHANNELMODE_STEREO,       AUDIO_DECODER_CH_MODE_STEREO,       2 },
    { MP3DEC_CHANNELMODE_JOINT_STEREO, AUDIO_DECODER_CH_MODE_JOINT_STEREO, 2 },
    { MP3DEC_CHANNELMODE_DUAL_MONO,    AUDIO_DECODER_CH_MODE_DUAL_MONO,    2 },
    { MP3DEC_CHANNELMODE_MONO,         AUDIO_DECODER_CH_MODE_MONO,         1 },
};
/* *INDENT-ON* */

#ifdef SUPPORT_WMA
/* *INDENT-OFF* */
struct channel_mode_table ch_mode_wma[] = {
    { WMADEC_CHANNELMODE_STEREO, AUDIO_DECODER_CH_MODE_STEREO, 2 },
    { WMADEC_CHANNELMODE_MONO,   AUDIO_DECODER_CH_MODE_MONO,   1 },
    { WMADEC_CHANNELMODE_THREE,  AUDIO_DECODER_CH_MODE_MULTI,  3 },
    { WMADEC_CHANNELMODE_BACK,   AUDIO_DECODER_CH_MODE_MULTI,  4 },
    { WMADEC_CHANNELMODE_QUAD,   AUDIO_DECODER_CH_MODE_MULTI,  4 },
    { WMADEC_CHANNELMODE_5,      AUDIO_DECODER_CH_MODE_MULTI,  5 },
    { WMADEC_CHANNELMODE_5DOT1,  AUDIO_DECODER_CH_MODE_MULTI,  6 },
    { WMADEC_CHANNELMODE_6DOT1,  AUDIO_DECODER_CH_MODE_MULTI,  7 },
    { WMADEC_CHANNELMODE_7DOT1,  AUDIO_DECODER_CH_MODE_MULTI,  8 },
};
/* *INDENT-ON* */
#endif

/* *INDENT-OFF* */
struct channel_mode_table ch_mode_vorbis[] = {
    { OGGDEC_CHANNELMODE_1CH, AUDIO_DECODER_CH_MODE_MONO,   1 },
    { OGGDEC_CHANNELMODE_2CH, AUDIO_DECODER_CH_MODE_STEREO, 2 },
};
/* *INDENT-ON* */

/* *INDENT-OFF* */
struct channel_mode_table ch_mode_amrwb[] = {
    { AMRWBDEC_CHANNELMODE_MONO, AUDIO_DECODER_CH_MODE_MONO, 1 },
};
/* *INDENT-ON* */

/* *INDENT-OFF* */
struct channel_mode_table ch_mode_amrnb[] = {
    { AMRNBDEC_CHANNELMODE_MONO, AUDIO_DECODER_CH_MODE_MONO, 1 },
};
/* *INDENT-ON* */

/* *INDENT-OFF* */
struct channel_mode_table ch_mode_flac[] = {
    { FLACDEC_CHANNELMODE_1CH, AUDIO_DECODER_CH_MODE_MONO,   1 },
    { FLACDEC_CHANNELMODE_2CH, AUDIO_DECODER_CH_MODE_STEREO, 2 },
    { FLACDEC_CHANNELMODE_3CH, AUDIO_DECODER_CH_MODE_MULTI,  3 },
    { FLACDEC_CHANNELMODE_4CH, AUDIO_DECODER_CH_MODE_MULTI,  4 },
    { FLACDEC_CHANNELMODE_5CH, AUDIO_DECODER_CH_MODE_MULTI,  5 },
    { FLACDEC_CHANNELMODE_6CH, AUDIO_DECODER_CH_MODE_MULTI,  6 },
    { FLACDEC_CHANNELMODE_7CH, AUDIO_DECODER_CH_MODE_MULTI,  7 },
    { FLACDEC_CHANNELMODE_8CH, AUDIO_DECODER_CH_MODE_MULTI,  8 },
};
/* *INDENT-ON* */

/* *INDENT-OFF* */
struct channel_mode_table ch_mode_dra[] = {
    { DRADEC_CHANNELMODE_1_0_CHANNEL, AUDIO_DECODER_CH_MODE_MONO,                   1 },
    { DRADEC_CHANNELMODE_1_1_CHANNEL, AUDIO_DECODER_CH_MODE_MONO,                   2 },
    { DRADEC_CHANNELMODE_2_0_CHANNEL, AUDIO_DECODER_CH_MODE_STEREO,                 2 },
    { DRADEC_CHANNELMODE_2_1_CHANNEL, AUDIO_DECODER_CH_MODE_2_1_FL_FR_LFE,          3 },
    { DRADEC_CHANNELMODE_3_0_CHANNEL, AUDIO_DECODER_CH_MODE_3_0_FL_FR_RC,           3 },
    { DRADEC_CHANNELMODE_3_1_CHANNEL, AUDIO_DECODER_CH_MODE_3_1_FL_FR_RC_LFE,       4 },
    { DRADEC_CHANNELMODE_4_0_CHANNEL, AUDIO_DECODER_CH_MODE_4_0_FL_FR_RL_RR,        4 },
    { DRADEC_CHANNELMODE_4_1_CHANNEL, AUDIO_DECODER_CH_MODE_4_1_FL_FR_RL_RR_LFE,    5 },
    { DRADEC_CHANNELMODE_5_0_CHANNEL, AUDIO_DECODER_CH_MODE_5_0_FL_FR_FC_RL_RR,     5 },
    { DRADEC_CHANNELMODE_5_1_CHANNEL, AUDIO_DECODER_CH_MODE_5_1_FL_FR_FC_RL_RR_LFE, 6 },
};
/* *INDENT-ON* */

static int set_decoded_info (struct aud_decoder_info *decoder, DecEvtESDecInfoParam * es_info)
{
    struct channel_mode_table *table = NULL;
    int i = 0;
    int max_index = 0;

    decoder->es_info.codec = convert_codec_type (es_info->media_type);

    decoder->es_info.sampling_rate = es_info->sample_rate;
    decoder->es_info.avg_bit_rate = es_info->avg_bit_rate;
    decoder->es_info.bit_per_sample = es_info->bit_per_sample;
    decoder->es_info.acmod = es_info->channel_mode;
    decoder->es_info.source_channels = es_info->num_of_channel;

    // atmos 여부 초기화 필요한지 확인
    decoder->es_info.atmos = false;

    info ("media_type: %d, codec: %d\n", es_info->media_type,
        convert_codec_type (es_info->media_type));
    info ("avg_bit_rate: %d\n", es_info->avg_bit_rate);
    info ("sampling_rate: %d\n", es_info->sample_rate);
    info ("channels: %d\n", es_info->num_of_channel);
    info ("bit_per_sample: %d\n", es_info->bit_per_sample);
    info ("channel_mode: %d\n", es_info->channel_mode);
    info ("endian: %d\n", es_info->input_endian);
    info ("sign: %d\n", es_info->input_signed);

    switch (decoder->es_info.codec)
    {
        case AUDIO_DECODER_CODEC_PCM:
        {
            table = ch_mode_pcm;
            max_index = sizeof (ch_mode_pcm) / sizeof (struct channel_mode_table);
            break;
        }

        case AUDIO_DECODER_CODEC_AC3:
        case AUDIO_DECODER_CODEC_EAC3:
        {
            DecAC3EsInfo info = { };
            memcpy (&info, es_info->es_info, sizeof (DecAC3EsInfo));

            decoder->es_info.eac3 = info.EAC3;
            // 6채널, 8채널이 아닌 경우 atmos = false 처리 필요한지 확인
            decoder->es_info.atmos = info.ATMOS;
            decoder->es_info.source_channels = info.num_of_channel;

            info ("eac3: %d\n", es_info->es_info[0]);
            info ("atmos: %d\n", es_info->es_info[1]);
            info ("channel_num: %d\n", es_info->es_info[2]);

            table = ch_mode_dolby;
            max_index = sizeof (ch_mode_dolby) / sizeof (struct channel_mode_table);
            break;
        }

        case AUDIO_DECODER_CODEC_AAC:
        {
            DecHEAACEsInfo info;
            memcpy (&info, es_info->es_info, sizeof (DecHEAACEsInfo));

            decoder->es_info.version = info.version;
            decoder->es_info.transmissionformat = info.transmissionformat;
            decoder->es_info.source_channels = info.num_of_channel;

            info ("version: %d (0: AAC, 1: HE-AACv1, 2: HE-AACv2)\n", es_info->es_info[0]);
            info ("transmissionformat: %d (0: LOAS/LATM, 1: ADTS)\n", es_info->es_info[1]);
            info ("channel_num: %d\n", es_info->es_info[2]);

            table = ch_mode_dolby;
            max_index = sizeof (ch_mode_dolby) / sizeof (struct channel_mode_table);
            break;
        }

        case AUDIO_DECODER_CODEC_AC4:
        {
            DecAC4EsInfo info = { };
            memcpy (&info, es_info->es_info, sizeof (DecAC4EsInfo));

            decoder->es_info.atmos = info.ATMOS;
            decoder->es_info.source_channels = info.num_of_channel;

            info ("atmos: %d\n", es_info->es_info[1]);
            info ("channel_num: %d\n", es_info->es_info[2]);

            // AC4 dual decoding event noti 필요한지 확인

            table = ch_mode_dolby;
            max_index = sizeof (ch_mode_dolby) / sizeof (struct channel_mode_table);
            break;
        }

        case AUDIO_DECODER_CODEC_DRA:
        {
            table = ch_mode_dra;
            max_index = sizeof (ch_mode_dra) / sizeof (struct channel_mode_table);
            break;
        }

        case AUDIO_DECODER_CODEC_MP3:
        {
            DecMPEGEsInfo info = { };
            memcpy (&info, es_info->es_info, sizeof (DecMPEGEsInfo));

            decoder->es_info.layer = info.layer;

            info ("version: %d\n", es_info->es_info[0]);

            table = ch_mode_mp3;
            max_index = sizeof (ch_mode_mp3) / sizeof (struct channel_mode_table);
            break;
        }

#ifdef SUPPORT_WMA
        case AUDIO_DECODER_CODEC_WMA_PRO:
        {
            table = ch_mode_wma;
            max_index = sizeof (ch_mode_wma) / sizeof (struct channel_mode_table);
            break;
        }
#endif

        case AUDIO_DECODER_CODEC_VORBIS:
        {
            table = ch_mode_vorbis;
            max_index = sizeof (ch_mode_vorbis) / sizeof (struct channel_mode_table);
            break;
        }

        case AUDIO_DECODER_CODEC_AMR_WB:
        {
            table = ch_mode_amrwb;
            max_index = sizeof (ch_mode_amrwb) / sizeof (struct channel_mode_table);
            break;
        }

        case AUDIO_DECODER_CODEC_AMR_NB:
        {
            table = ch_mode_amrnb;
            max_index = sizeof (ch_mode_amrnb) / sizeof (struct channel_mode_table);
            break;
        }

        case AUDIO_DECODER_CODEC_FLAC:
        {
            table = ch_mode_flac;
            max_index = sizeof (ch_mode_flac) / sizeof (struct channel_mode_table);
            break;
        }

        case AUDIO_DECODER_CODEC_MAT:
        {
            DecMATEsInfo info;
            memcpy (&info, es_info->es_info, sizeof (DecMATEsInfo));

            decoder->es_info.truehd = info.DTHD;
            decoder->es_info.atmos = info.ATMOS;
            decoder->es_info.source_channels = info.num_of_channel;

            info ("truehd: %d\n", es_info->es_info[0]);
            info ("atmos: %d\n", es_info->es_info[1]);
            info ("channel_num: %d\n", es_info->es_info[2]);
            break;
        }

#ifdef SUPPORT_DTSX
        case AUDIO_DECODER_CODEC_DTS:
        {
            DecDTSM6EsInfo info;
            memcpy (&info, es_info->es_info, sizeof (DecDTSM6EsInfo));

            decoder->es_info.pass_through = es_info->es_info[1];

            //Set a detail audio codec type.
            switch (info.dts_type)
            {
                case 0:        // DTS-CA
                    decoder->es_info.dts_detail = AUDIO_DECODER_DTS_DETAIL_DTS;
                    break;
                case 1:        // DTS-HD MA
                    decoder->es_info.dts_detail = AUDIO_DECODER_DTS_DETAIL_DTS_HD_MA;
                    break;
                case 2:        // LBR
                    decoder->es_info.dts_detail = AUDIO_DECODER_DTS_DETAIL_DTS_EXPRESS;
                    break;
                case 3:        // DTS Hi Res
                    decoder->es_info.dts_detail = AUDIO_DECODER_DTS_DETAIL_DTS_HD;
                    break;
                case 4:        // Coreless
                    decoder->es_info.dts_detail = AUDIO_DECODER_DTS_DETAIL_DTS_HD_MA;
                    break;
                case 5:        // DTS-X Phase 1
                    decoder->es_info.dts_detail = AUDIO_DECODER_DTS_DETAIL_DTS_X_1;
                    break;
                case 6:        // DTS-X Phase 2
                    decoder->es_info.dts_detail = AUDIO_DECODER_DTS_DETAIL_DTS_X_2;
                    break;
                default:
                    decoder->es_info.dts_detail = AUDIO_DECODER_DTS_DETAIL_DTS;
                    break;
            }

            info ("dts_type:  %d\n", es_info->es_info[0]);
            info ("es_format: %d\n", es_info->es_info[1]);
            info ("es_fsize:  %d\n", es_info->es_info[2]);
            break;
        }
#endif

        case AUDIO_DECODER_CODEC_IAMF:
        {
            break;
        }

        default:
        {
            max_index = 0;
            break;
        }
    }

    for (i = 0; i < max_index; i++)
    {
        if (es_info->channel_mode == table[i].channel_mode)
        {
            decoder->es_info.audio_mode = table[i].audio_mode;
            decoder->es_info.channels = table[i].channels;
            break;
        }
    }

    if ((max_index != 0) && (i == max_index))
    {
        error ("invalid channel mode. codec: %d, channel_mode: %d\n", decoder->es_info.codec,
            es_info->channel_mode);
        return -1;
    }

    return 0;
}

static bool is_changed_decoded_info (struct aud_decoder_info *decoder,
    DecEvtESDecInfoParam * es_info)
{
    struct decoded_info *prev_es_info = &decoder->es_info;

    if (prev_es_info->codec != convert_codec_type (es_info->media_type)
        || prev_es_info->sampling_rate != es_info->sample_rate
        || prev_es_info->channels != es_info->num_of_channel
        || prev_es_info->bit_per_sample != es_info->bit_per_sample
        || prev_es_info->acmod != es_info->channel_mode)
    {
        return true;
    }

    return false;
}

/**
 * get mutex lock of decoder
 *
 * @param
 * @return
*/
void decoder_acquire_lock (void)
{
    AUD_DEC_LOCK ();
}

/**
 * release mutex lock of decoder
 *
 * @param
 * @return
*/
void decoder_release_lock (void)
{
    AUD_DEC_UNLOCK ();
}

#ifdef SUPPORT_SOUNDBAR
static bool decoder_is_ha_decoder (enum audio_decoder_codec codec)
{
    bool ret = false;

    switch (codec)
    {
        case AUDIO_DECODER_CODEC_AUTO:
        case AUDIO_DECODER_CODEC_AC3:
        case AUDIO_DECODER_CODEC_EAC3:
        case AUDIO_DECODER_CODEC_MAT:
            ret = true;
            break;
        default:
            ret = false;
            break;
    };

    return ret;
}

static int decoder_register_pending_event (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    int ret = 0;

    AUD_DEC_EVENT_LOCK ();

    if (decoder_is_created (block))
    {
        struct aud_decoder_event_info *pending_event_info = NULL;
        struct aud_decoder_event_info *event_info = NULL;
        struct aud_decoder_event_info *event_next = NULL;

        list_for_each_entry (pending_event_info, &decoder->list_pending_event, list)
        {
            if (pending_event_info)
            {
                int event_id = 0;
                bool exist = false;

                info ("register pending event, %s\n", pending_event_info->name);

                event_id =
                    aimc_register_named_event (decoder, pending_event_info->cb_func,
                    decoder->uid_dec, pending_event_info->name, pending_event_info->repeat);

                list_for_each_entry (event_info, &decoder->list_event, list)
                {
                    if (!strcmp (event_info->name, pending_event_info->name))
                    {
                        exist = true;

                        debug ("already registered event, %s\n", pending_event_info->name);
                        break;
                    }
                }

                if (!exist)
                {
                    struct aud_decoder_event_info *event = NULL;

                    event =
                        (struct aud_decoder_event_info *) kzalloc (sizeof (struct
                            aud_decoder_event_info), GFP_KERNEL);
                    if (!event)
                    {
                        ret = -1;
                        error ("no mem");
                        goto exit;
                    }

                    event->name = kstrdup (pending_event_info->name, GFP_KERNEL);
                    event->id = event_id;
                    event->cb_func = pending_event_info->cb_func;
                    event->repeat = pending_event_info->repeat;

                    list_add (&event->list, &decoder->list_event);
                }
            }
        }

        list_for_each_entry_safe (event_info, event_next, &decoder->list_pending_event, list)
        {
            debug ("remove pending event list, event=%s\n", event_info->name);

            list_del (&event_info->list);
            kfree (event_info->name);
            kfree (event_info);
        }
    }
    else
    {
        ret = -1;
        error ("decoder is not yet created.");
    }

  exit:
    AUD_DEC_EVENT_UNLOCK ();
    return ret;
}

static int decoder_set_pending_param (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    int ret = 0;

    AUD_DEC_PROP_LOCK ();

    if (decoder_is_created (block))
    {
        struct aud_decoder_property_info *pending_prop_info = NULL;
        struct aud_decoder_property_info *prop_info = NULL;
        struct aud_decoder_property_info *prop_next = NULL;

        list_for_each_entry (pending_prop_info, &decoder->list_pending_prop, list)
        {
            if (pending_prop_info)
            {
                bool exist = false;

                list_for_each_entry (prop_info, &decoder->list_prop, list)
                {
                    if (!strcmp (pending_prop_info->name, prop_info->name))
                    {
                        kfree (prop_info->data);
                        prop_info->data = kstrdup (pending_prop_info->data, GFP_KERNEL);
                        exist = true;

                        info ("update property, %s = %s\n", pending_prop_info->name,
                            pending_prop_info->data);
                        break;
                    }
                }

                if (!exist)
                {
                    struct aud_decoder_property_info *prop = NULL;

                    prop =
                        (struct aud_decoder_property_info *) kzalloc (sizeof (struct
                            aud_decoder_property_info), GFP_KERNEL);
                    if (!prop)
                    {
                        ret = -1;
                        error ("no mem\n");
                        goto exit;
                    }

                    prop->name = kstrdup (pending_prop_info->name, GFP_KERNEL);
                    prop->data = kstrdup (pending_prop_info->data, GFP_KERNEL);

                    list_add (&prop->list, &decoder->list_prop);
                }
            }
        }

        list_for_each_entry_safe (prop_info, prop_next, &decoder->list_pending_prop, list)
        {
            debug ("remove pending property list, %s=%s\n", prop_info->name, prop_info->data);

            list_del (&prop_info->list);
            kfree (prop_info->name);
            kfree (prop_info->data);
            kfree (prop_info);
        }

        list_for_each_entry (prop_info, &decoder->list_prop, list)
        {
            if (prop_info)
            {
                info ("set property, %s = %s\n", prop_info->name, prop_info->data);
                aimc_set_property (decoder->uid_dec, "%s=%s", prop_info->name, prop_info->data);
            }
        }
    }
    else
    {
        ret = -1;
        error ("decoder is not yet created.");
    }

  exit:
    AUD_DEC_PROP_UNLOCK ();
    return ret;
}
#endif


/**
 * get decoding info from decoder module
 *
 * @param
 * @return
*/
int decoder_decoded_info_cb (void *param, int cb_param_len, void *cb_param)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) cb_param;
    DecEvtESDecInfoParam *es_info = (DecEvtESDecInfoParam *) param;
    enum audio_decoder_channel_mode prev_channel_mode = AUDIO_DECODER_CH_MODE_UNKNOWN;
    bool notify_event = false;

    if (cb_param_len != sizeof (DecEvtESDecInfoParam))
    {
        error ("Dec Es Info : Param Length Error[Expected:%zd][Input:%d]\n",
            sizeof (DecEvtESDecInfoParam), cb_param_len);
        return -1;
    }

    prev_channel_mode = decoder->es_info.acmod;

    if (is_changed_decoded_info (decoder, es_info))
    {
        notify_event = true;
    }

    set_decoded_info (decoder, es_info);

    noti ("Dec Info(%d) : codec(%d), freq(%d), ch(%d), channel mode(%d -> %d)\n",
        decoder->uid_decbin, decoder->es_info.codec, es_info->sample_rate, es_info->num_of_channel,
        prev_channel_mode, es_info->channel_mode);

    if (notify_event)
        notifier_input_changed ();

    return 0;
}

/**
 * get tp es exist info. from tp module
 *
 * @param
 * @return
*/
int decoder_tp_es_exist_info_cb (void *param, int cb_param_len, void *cb_param)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) cb_param;
    TpEvtESExistInfoParam *existParam = (TpEvtESExistInfoParam *) param;

    if (cb_param_len != sizeof (TpEvtESExistInfoParam))
    {
        error ("Param Length Error[Expected:%zd][Input:%d]\n",
            sizeof (TpEvtESExistInfoParam), cb_param_len);
        return -1;
    }

    decoder->es_info.is_es_exist = existParam->es_exist;

    noti ("Dec Info(%d) : es exist(%d)\n", decoder->uid_decbin, existParam->es_exist);
    return 0;
}

/**
 * get hdmi pcm format info. from hdmi module
 *
 * @param
 * @return
*/
int decoder_hdmi_pcm_format_info_cb (void *param, int cb_param_len, void *cb_param)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) cb_param;
    HdmiEvtPCMFormatParam *pPcmFormatParam = (HdmiEvtPCMFormatParam *) param;

    if (cb_param_len != sizeof (HdmiEvtPCMFormatParam))
    {
        error ("Param Length Error[Expected:%zd][Input:%d]\n",
            sizeof (HdmiEvtPCMFormatParam), cb_param_len);
        return -1;
    }

    if (pPcmFormatParam->format == 0)   // 0 : PCM
        decoder->es_info.pc_valid_pcm = 1;

    noti ("Dec Info(%d) : pcm format(%d)\n", decoder->uid_decbin, pPcmFormatParam->format);
    return 0;
}

/**
 * get hdmi pcm format info. from hdmi module
 *
 * @param
 * @return
*/
int decoder_mpegh_ui_param_info_cb (void *param, int cb_param_len, void *cb_param)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) cb_param;
    DecMPEGHUIInfo *mpegh_ui_info = (DecMPEGHUIInfo *) param;

    if (cb_param_len != sizeof (DecMPEGHUIInfo))
    {
        error ("Param Length Error[Expected:%zd][Input:%d]\n",
            sizeof (DecMPEGHUIInfo), cb_param_len);
        return -1;
    }

    if (mpegh_ui_info->xmlsize < MPEGH_SIZE_OF_GET_UI)
        decoder->ui_param.size = mpegh_ui_info->xmlsize;
    else
        decoder->ui_param.size = MPEGH_SIZE_OF_GET_UI;

    noti ("Dec Info(%d) : xmlsize(%d)\n", decoder->uid_decbin, mpegh_ui_info->xmlsize);

    return 0;
}

int decoder_module_id_changed_cb (void *param, int cb_param_len, void *cb_param)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) cb_param;
    DecEvtModuleId *uid_param = (DecEvtModuleId *) param;
    unsigned int uid;

    if (cb_param_len != sizeof (DecEvtModuleId))
    {
        error ("Param Length Error[Expected:%zd][Input:%d]\n",
            sizeof (DecEvtModuleId), cb_param_len);
        return -1;
    }

    uid = decoder->uid_dec;

    if (uid != uid_param->uid)
        decoder->uid_dec = uid_param->uid;

    info ("Decoder module id changed : 0x0%x -> 0x0%x\n", uid, decoder->uid_dec);
#ifdef SUPPORT_SOUNDBAR
    decoder_register_pending_event (cb_param);
    decoder_set_pending_param (cb_param);
#endif
    return 0;
}


/**
 * get tp buffer (TPM/TPA) status
 *
 * @param block [in] context of this block
 * @return pointer of decoder info
*/
int decoder_get_tp_buffer_status (struct aud_block_info *block, enum audio_decoder_input_tp input,
    unsigned int *max, unsigned int *free)
{
    //struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    unsigned int buffer_status = 0;

    // todo: read register (TPM_BUFSIZE, TPA_BUFSIZE)
    if (input == AUDIO_DECODER_INPUT_TP_0)
    {
        buffer_status = AUD_IPCREG (TPM_BUFSIZE);
    }
    else if (input == AUDIO_DECODER_INPUT_TP_1)
    {
        buffer_status = AUD_IPCREG (TPA_BUFSIZE);
    }
    else
    {
        error ("invalid input, input : %d .\n", input);
        return -1;
    }

    *max = (buffer_status >> 16) << 8;
    *free = (buffer_status & 0xFFFF) << 8;

    return 0;
}

/**
 * get tp audio presented pts
 *
 * @param block [in] context of this block
 * @return pointer of decoder info
*/
int decoder_get_tp_audio_pts (struct aud_block_info *block, int index, unsigned int *pts)
{
    //struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    if (index == 0)
        *pts = AUD_IPCREG (PRESENTED_PTS_LIP0);
    else if (index == 1)
        *pts = AUD_IPCREG (PRESENTED_PTS_LIP1);
    else if (index == 2)
        *pts = AUD_IPCREG (PRESENTED_PTS_LIP2);
    else if (index == 3)
        *pts = AUD_IPCREG (PRESENTED_PTS_LIP3);
    else
        error ("invalid index, index : %d .\n", index);

    return 0;
}

/**
 * get decoding info from decoder
 *
 * @param block [in] context of this block
 * @return pointer of decoder info
*/
int decoder_get_decoded_info (struct aud_block_info *block, struct decoded_info *info)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    if (info == NULL)
    {
        error ("info is NULL\n");
        return -1;
    }

    memcpy (info, &decoder->es_info, sizeof (struct decoded_info));

    return 0;
}

int decoder_set_prio (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    int prio = -4;

    if (bm_is_main_audio (block))
    {
        // MAIN audio decoder
        info ("MAIN thread priority is %d\n", prio);
    }
    else
    {
        struct aud_decoder_property_info *prop_info = NULL;
        bool is_audio_decription_on = false;

        // make lower SUB decoder thread priority
        list_for_each_entry (prop_info, &decoder->list_prop, list)
        {
            // thread priority of audio decoder should be same in AD (Audio Description) mode.
            if (prop_info && prop_info->name && prop_info->data &&
                !strcmp (prop_info->name, "audio-description") && !strcmp (prop_info->data, "1"))
            {
                is_audio_decription_on = true;
                break;
            }
        }
        prio = (is_audio_decription_on) ? -4 : -5;
        info ("SUB  thread priority is %d %s\n", prio, (is_audio_decription_on) ? "(AD)" : "");
    }

    aimc_set_property (decoder->uid_decbin, "thread-priority=%d", prio);

    return 0;
}

static const char *_event_name[AUDIO_DECODER_EVENT_MAX] = {
    [AUDIO_DECODER_EVENT_ERROR] = "dec_error",
    [AUDIO_DECODER_EVENT_INFO] = "dec_info",
    [AUDIO_DECODER_EVENT_MPEGH_UI] = "xml_info",
    [AUDIO_DECODER_EVENT_DEC_ID_CHANGED] = "dec_id_changed",
};

/**
 * register decoder event
 *
 * @param block [in] context of this block
 * @return pointer of decoder info
*/
int decoder_register_event (struct aud_block_info *block, enum audio_decoder_event event,
    int (*cb_func) (void *, int, void *), int repeat)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    int dec_id = 0;
    int ret = 0;

    struct aud_decoder_event_info *event_info = NULL;

    AUD_DEC_EVENT_LOCK ();

    if ((event < AUDIO_DECODER_EVENT_ERROR) || (event >= AUDIO_DECODER_EVENT_MAX))
    {
        ret = -1;
        error ("event is invalid. %d\n", event);
        goto exit;
    }

    list_for_each_entry (event_info, &decoder->list_event, list)
    {
        if (!strcmp (_event_name[event], event_info->name))
        {
            info ("already registered event, %s\n", _event_name[event]);
            goto exit;
        }
    }

    event_info =
        (struct aud_decoder_event_info *) kzalloc (sizeof (struct aud_decoder_event_info),
        GFP_KERNEL);
    if (!event_info)
    {
        ret = -1;
        error ("no mem\n");
        goto exit;
    }

    aimc_get_property (decoder->uid_decbin, "decoder-uid", &dec_id);

#ifdef SUPPORT_SOUNDBAR
    if (decoder_is_ha_decoder (decoder->codec) && event != AUDIO_DECODER_EVENT_DEC_ID_CHANGED)
    {
        event_info->name = kstrdup (_event_name[event], GFP_KERNEL);
        event_info->cb_func = cb_func;
        event_info->repeat = repeat;

        list_add (&event_info->list, &decoder->list_pending_event);

        info ("decoder is not yet created. add pending event list, %s\n", _event_name[event]);
    }
    else
#endif
    {
        int event_id = 0;

        if (event == AUDIO_DECODER_EVENT_DEC_ID_CHANGED)
            dec_id = decoder->uid_decbin;

        event_id = aimc_register_named_event (decoder, cb_func, dec_id, _event_name[event], repeat);

        event_info->name = kstrdup (_event_name[event], GFP_KERNEL);
        event_info->id = event_id;
        event_info->cb_func = cb_func;
        event_info->repeat = repeat;

        list_add (&event_info->list, &decoder->list_event);

        info ("decoder register event, %s\n", _event_name[event]);
    }


  exit:
    AUD_DEC_EVENT_UNLOCK ();
    return ret;
}

/**
 * unregister decoder event
 *
 * @param block [in] context of this block
 * @return pointer of decoder info
*/
int decoder_unregister_event (struct aud_block_info *block, enum audio_decoder_event event)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    int event_id = -1;
    int ret = 0;

    struct aud_decoder_event_info *event_info = NULL;

    AUD_DEC_EVENT_LOCK ();

    if ((event < AUDIO_DECODER_EVENT_ERROR) || (event >= AUDIO_DECODER_EVENT_MAX))
    {
        ret = -1;
        error ("event is invalid. %d\n", event);
        goto exit;
    }

#ifdef SUPPORT_SOUNDBAR
    list_for_each_entry (event_info, &decoder->list_pending_event, list)
    {
        if (!strcmp (_event_name[event], event_info->name))
        {
            list_del (&event_info->list);
            kfree (event_info->name);
            kfree (event_info);
            break;
        }
    }
#endif

    list_for_each_entry (event_info, &decoder->list_event, list)
    {
        if (!strcmp (_event_name[event], event_info->name))
        {
            event_id = event_info->id;
            break;
        }
    }

    if (event_id > 0)
    {
        aimc_unregister_named_event (event_id);

        list_del (&event_info->list);
        kfree (event_info->name);
        kfree (event_info);

        info ("decoder unregister event, %s\n", _event_name[event]);
    }
    else
    {
        info ("event is not registered, %s\n", _event_name[event]);
    }

  exit:
    AUD_DEC_EVENT_UNLOCK ();

    return ret;
}

/**
 * update decoder event id
 *
 * @param block [in] context of this block
 * @return pointer of decoder info
*/
static int decoder_update_event_id (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    struct aud_decoder_event_info *event_info = NULL;

    list_for_each_entry (event_info, &decoder->list_event, list)
    {
        if (event_info)
        {
            unsigned int uid_dec = 0;
            int event_id = -1;

            aimc_get_property (decoder->uid_decbin, "decoder-uid", &uid_dec);

            decoder->uid_dec = uid_dec;

            aimc_unregister_named_event (event_info->id);
            event_id =
                aimc_register_named_event (decoder, event_info->cb_func, decoder->uid_dec,
                event_info->name, event_info->repeat);

            info ("decoder update event id, %s (%d -> %d)\n", event_info->name, event_info->id,
                event_id);

            event_info->id = event_id;
        }
    }

    return 0;
}

static int decoder_unregister_event_all (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    struct aud_decoder_event_info *event_info, *next;

    AUD_DEC_EVENT_LOCK ();

#ifdef SUPPORT_SOUNDBAR
    list_for_each_entry_safe (event_info, next, &decoder->list_pending_event, list)
    {
        info ("decoder unregister event %s(0x%x)\n", event_info->name, event_info->id);

        aimc_unregister_named_event (event_info->id);

        list_del (&event_info->list);
        kfree (event_info->name);
        kfree (event_info);
    }
#endif

    list_for_each_entry_safe (event_info, next, &decoder->list_event, list)
    {
        info ("decoder unregister event %s(0x%x)\n", event_info->name, event_info->id);

        aimc_unregister_named_event (event_info->id);

        list_del (&event_info->list);
        kfree (event_info->name);
        kfree (event_info);
    }

    AUD_DEC_EVENT_UNLOCK ();

    return 0;
}


static bool decoder_is_heavy (enum audio_decoder_codec codec)
{
    switch (codec)
    {
        case AUDIO_DECODER_CODEC_MAT:
        case AUDIO_DECODER_CODEC_TRUE_HD:
#ifdef SUPPORT_DTSX
        case AUDIO_DECODER_CODEC_DTS:
        case AUDIO_DECODER_CODEC_DTS_HD:
#endif
            return true;
        default:
            break;
    }
    return false;
}

static bool decoder_is_second_heavy (enum audio_decoder_codec codec)
{
#if (MS12_VER >= 28)
    return false;
#else
    switch (codec)
    {
            //case AUDIO_DECODER_CODEC_EAC3:
        case AUDIO_DECODER_CODEC_AC4:
            return true;
        default:
            break;
    }
    return false;
#endif
}

static bool decoder_check_codec (struct aud_block_info *me, struct aud_block_info *other)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) me;
    struct aud_decoder_info *decoder2 = (struct aud_decoder_info *) other;

    bool heavy_codec1 = false, heavy_codec2 = false;
    bool sec_heavy_codec1 = false, sec_heavy_codec2 = false;

    noti ("%s - %s", get_codec_name (decoder->codec), get_codec_name (decoder2->codec));

    heavy_codec1 = decoder_is_heavy (decoder->codec);
    heavy_codec2 = decoder_is_heavy (decoder2->codec);
    sec_heavy_codec1 = decoder_is_second_heavy (decoder->codec);
    sec_heavy_codec2 = decoder_is_second_heavy (decoder2->codec);

    if (heavy_codec1 && heavy_codec2)
        return true;
    else if ((heavy_codec1 && sec_heavy_codec2) || (heavy_codec2 && sec_heavy_codec1))
        return true;

    return false;
}

/**
 * set codec into decoder
 *
 * @param block [in] context of this block
 * @return pointer of decoder info
*/
int decoder_set_codec (struct aud_block_info *block, enum audio_decoder_codec codec)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    decoder->codec = codec;
    info ("codec = %d, name = %s\n", codec, get_codec_name (codec));

    if (codec > AUDIO_DECODER_CODEC_UNKNOWN && codec < AUDIO_DECODER_CODEC_MAX)
    {
        unsigned int uid_dec = 0;

        decoder->is_dummy_codec = false;

        if (bm_check_query_farm (block, decoder_check_codec))
            decoder->is_dummy_codec = true;

        info ("send dummy-codec=%s to decoderbin\n", (decoder->is_dummy_codec) ? "true" : "false");
        aimc_set_property (decoder->uid_decbin, "dummy-codec=%s",
            (decoder->is_dummy_codec) ? "true" : "false");

#ifdef SUPPORT_SOUNDBAR
        if (decoder->input == AUDIO_DECODER_INPUT_I2S && decoder_is_ha_decoder (codec))
            codec = AUDIO_DECODER_CODEC_AUTO;
#endif
        aimc_set_property (decoder->uid_decbin, "codec=%s", get_codec_name (codec));

        aimc_get_property (decoder->uid_decbin, "decoder-uid", &uid_dec);

#ifdef SUPPORT_SOUNDBAR
        if (decoder->input == AUDIO_DECODER_INPUT_I2S && decoder_is_ha_decoder (codec))
        {
            info ("decoder is created through the first event .");
        }
        else
#endif
        {
            if (uid_dec)
            {
                decoder->uid_dec = uid_dec;
                if (codec == AUDIO_DECODER_CODEC_MPEG_H)
                {
                    decoder_config_mpegh_ui_param (block);
                }
            }
            else
            {
                error ("can not find decoder\n");
                return -1;
            }
        }

        decoder_set_prio (block);
    }
    else
    {
        error ("decoder_set_codec failed, codec: %s (%d)\n", get_codec_name (codec), codec);
        return -1;
    }

    return 0;
}

enum audio_decoder_codec decoder_get_codec (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    return decoder->codec;
}

int decoder_config_mpegh_ui_param (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    struct mpegh_ui_param *param = &decoder->ui_param;
    unsigned int uid_dec = 0;
    unsigned int addr = 0;
    unsigned int size = 0;

    if (param->phys_addr == 0)
    {
        param->phys_addr =
            hma_alloc ("audio_buffer", (MPEGH_SIZE_OF_SET_UI + MPEGH_SIZE_OF_GET_UI), 0x1000);
        if (param->phys_addr == 0)
        {
            error ("phys_addr is null.\n");
            return -1;
        }
    }

    param->virtual_addr =
        vmap_phys (param->phys_addr, (MPEGH_SIZE_OF_SET_UI + MPEGH_SIZE_OF_GET_UI));
    if (param->virtual_addr == NULL)
    {
        hma_free ("audio_buffer", param->phys_addr);
        error ("virtAddrMpeghUI is null.\n");
        return -1;
    }

    addr = ((unsigned int) (param->phys_addr) + MPEGH_SIZE_OF_SET_UI);
    size = MPEGH_SIZE_OF_GET_UI;

    aimc_get_property (decoder->uid_decbin, "decoder-uid", &uid_dec);

    if (uid_dec)
    {
        aimc_set_property (uid_dec, "ui-param=%d", addr);
        aimc_set_property (uid_dec, "ui-param-size=%d", size);
    }
    else
    {
        hma_free ("audio_buffer", param->phys_addr);
        vunmap_phys (decoder->ui_param.virtual_addr);
        error ("can not find decoder\n");
        return -1;
    }

    noti ("ui-param: %d, ui-param-size: %d\n", addr, size);

    return 0;
}

int decoder_set_mpegh_ui_param (struct aud_block_info *block, struct adec_mpegh_ui_param *ui_param)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    struct mpegh_ui_param *param = &decoder->ui_param;
    unsigned char *buf = NULL;
    MpeghCmdSetUIParam cmd_param = { };
    unsigned int uid_dec = 0;

    if (ui_param->param == NULL)
    {
        error ("param = %p, size = %d\n", ui_param->param, ui_param->size);
    }

    if (param->virtual_addr == NULL)
    {
        error ("virtual address is null\n");
        return -1;
    }

    if (ui_param->size > MPEGH_SIZE_OF_SET_UI)
    {
        error ("user parameter size error (size: %d, max_size: %d) \n", ui_param->size,
            MPEGH_SIZE_OF_SET_UI);
        return -1;
    }

    if (ui_param->size + param->offset >= MPEGH_SIZE_OF_SET_UI)
        param->offset = 0;

    buf = (unsigned char *) param->virtual_addr + param->offset;

    if (copy_from_user (buf, ui_param->param, ui_param->size))
    {
        error ("copy_from_user error \n");
        return -1;
    }

    cmd_param.xmlsize = ui_param->size;
    cmd_param.pxml = ((unsigned int) (param->phys_addr) + param->offset);
    aimc_get_property (decoder->uid_decbin, "decoder-uid", &uid_dec);

    if (uid_dec)
    {
        aimc_send_command_sync (NULL, MPEGH_CMD_SET_UI, 0, uid_dec, &cmd_param,
            sizeof (MpeghCmdSetUIParam));
    }
    else
    {
        error ("can not find decoder\n");
    }

    param->offset += ui_param->size;

    info ("set user parameter (addr: %p, size: %d, offset: %d\n", &param->phys_addr,
        ui_param->size, param->offset);

    return 0;
}

int decoder_get_mpegh_ui_param (struct aud_block_info *block, struct adec_mpegh_ui_param *ui_param)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    struct mpegh_ui_param *param = &decoder->ui_param;
    unsigned char *buf = NULL;

    if (ui_param->param == NULL)
    {
        error ("param = %p, size = %d\n", ui_param->param, ui_param->size);
    }

    if (param->virtual_addr == NULL)
    {
        error ("virtual address is null\n");
        return -1;
    }

    if (ui_param->size > MPEGH_SIZE_OF_GET_UI)
    {
        error ("user parameter size error (size: %d, max_size: %d) \n", ui_param->size,
            MPEGH_SIZE_OF_GET_UI);
        return -1;
    }

    buf = (unsigned char *) param->virtual_addr + MPEGH_SIZE_OF_SET_UI;
    ui_param->size = param->size;

    if (copy_to_user (ui_param->param, buf, param->size))
    {
        error ("copy_to_user error \n");
        return -1;
    }

    info ("get user parameter (size: %d) \n", ui_param->size);

    return 0;
}

int decoder_connect (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    aimc_set_property (decoder->uid_decbin, "connect=1");

    return 0;
}

#ifdef SUPPORT_DTSX
int decoder_set_dtsx_bitstream_passthrough (struct aud_block_info *block,
    bool bitstream_passthrough)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    if (decoder->codec == AUDIO_DECODER_CODEC_DTS)
    {
        decoder_set_param (block, "bitstream-passthrough=%d", bitstream_passthrough);

        info ("decoder codec is DTS. passthrough: %d. \n", bitstream_passthrough);

        notifier_set_dtsx_bitstream_passthrough (bitstream_passthrough);
    }
    else
    {
        info ("decoder codec is not DTS. \n");
    }

    return 0;
}
#endif

int decoder_set_dolby_drc_mode (struct aud_block_info *block, enum audio_decoder_drc drc)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    if (drc >= AUDIO_DECODER_DRC_LINE && drc <= AUDIO_DECODER_DRC_RF)
    {
        decoder->drc = drc;
        info ("set dolby drc mode: %d\n", drc);
    }
    else
    {
        error ("invalid dolby drc mode\n");
    }


    return 0;
}

enum audio_decoder_drc decoder_get_dolby_drc_mode (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    return decoder->drc;
}

bool decoder_is_created (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    if (decoder->uid_dec > 0)
        return true;

    return false;
}

#ifdef SUPPORT_SOUNDBAR
void decoder_stop (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    decoder->uid_dec = 0;

    memset (&decoder->es_info, 0x0, sizeof (struct decoded_info));
}

#define MAX_DECODER_INDEX 2

int decoder_get_already_opened_index (void)
{
    int i;
    int index = -1;

    for (i = 0; i < MAX_DECODER_INDEX; i++)
    {
        if (bm_get_block_info_by_index ("decoder", i) != NULL)
            index = i;
    }

    return index;
}
#endif

static int decoder_set_property_list (struct aud_block_info *block, char *name, char *data)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    struct aud_decoder_property_info *prop_info = NULL;
    int ret = 0;

    AUD_DEC_PROP_LOCK ();

    list_for_each_entry (prop_info, &decoder->list_prop, list)
    {
        if (!strcmp (name, prop_info->name))
        {
            kfree (prop_info->data);
            prop_info->data = kstrdup (data, GFP_KERNEL);

            info ("update property, %s = %s\n", name, data);
            goto exit;
        }
    }

    prop_info =
        (struct aud_decoder_property_info *) kzalloc (sizeof (struct aud_decoder_property_info),
        GFP_KERNEL);
    if (!prop_info)
    {
        ret = -1;
        error ("no mem\n");
        goto exit;
    }

    prop_info->name = kstrdup (name, GFP_KERNEL);
    prop_info->data = kstrdup (data, GFP_KERNEL);

#ifdef SUPPORT_SOUNDBAR
    if (decoder_is_created (block))
        list_add (&prop_info->list, &decoder->list_prop);
    else
        list_add (&prop_info->list, &decoder->list_pending_prop);
#else
    list_add (&prop_info->list, &decoder->list_prop);
#endif

    debug ("decoder property list add, %s = %s\n", name, data);

  exit:
    AUD_DEC_PROP_UNLOCK ();
    return ret;
}

struct decoder_param_cmd
{
    char *name;

    // function pointer
    int (*set) (struct aud_block_info *, char *);
    int (*get) (struct aud_block_info *, char *);
};


static int decoder_run_param (struct aud_block_info *block, char *name, char *data, int *ret_value,
    bool is_set)
{
    int ret = -1;
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    if (decoder_is_created (block))
    {
        if (is_set)
        {
            decoder_set_property_list (block, name, data);

            ret = aimc_set_property (decoder->uid_dec, "%s=%s", name, data);
        }
        else
            ret = aimc_get_property (decoder->uid_dec, name, ret_value);
    }
    else
    {
#ifdef SUPPORT_SOUNDBAR
        if (is_set)
        {
            ret = 0;
            decoder_set_property_list (block, name, data);
            debug ("decoder is not yet created. add pending list");
        }
#else
        info ("decoder_run_param failed. can not find decoder\n");
#endif
    }

    return ret;
}


#define DECODER_PARAM_DELIMITER " =\\"

/**
 * get parameter to decoder
 *
 * decoder_get_param(decoder, &freq, sizeof(int), "freq");
 *
 * @param decoder [in] pointer of decoder info
 * @param val [out] pointer of returned value
 * @param val_len [in] length of variable for value
 * @param pStrParam [in] formatted input
 * @return 0 : OK, other : NOT_OK
 * @see aud_renderer_info
*/
int decoder_get_param (struct aud_block_info *block, char *name, int *val)
{
    int ret = -1;
    int uid_dec = 0;
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    // update uid of decoder module in case of that decoder module is not yet created in worerbin
    aimc_get_property (decoder->uid_decbin, "decoder-uid", &uid_dec);
    if (uid_dec)
        decoder->uid_dec = uid_dec;

    ret = decoder_run_param (block, name, NULL, val, false);

    if (ret < 0)
    {
        info ("decoder_run_param () failed\n");
        return ret;
    }

    info ("%s = %d\n", name, *val);

    return ret;
}


/**
 * set parameter to decoder
 *
 * decoder_set_param(decoder, "freq=%d", 48000);
 *
 * @param decoder [in] pointer of decoder info
 * @param pStrParam [in] formatted input
 * @return 0 : OK, other : NOT_OK
 * @see aud_decoder_info
*/
int decoder_set_param (struct aud_block_info *block, char *pStrParam, ...)
{
    va_list ap;
    char *param, *name, *str;

    va_start (ap, pStrParam);
    param = kvasprintf (GFP_KERNEL, pStrParam, ap);
    va_end (ap);

    str = param;

    while ((name = strsep (&str, DECODER_PARAM_DELIMITER)))
    {
        char *data;
        int ret = -1;

        data = strsep (&str, DECODER_PARAM_DELIMITER);
        if (!data)
        {
            error ("no data for data. str %s\n", str);
            break;
        }

        info ("%s = %s\n", name, data);
        ret = decoder_run_param (block, name, data, NULL, true);

        if (ret < 0)
            info ("decoder_run_param () failed\n");
    }

    kfree (param);

    return 0;
}

int decoder_set_input (struct aud_block_info *block, enum audio_decoder_input input)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    decoder->input = input;

    return 0;
}

enum audio_decoder_input decoder_get_input (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    return decoder->input;
}

static void decoder_create_bypass (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    int preferred_proc = bm_get_preffered_processor (block);

    if (decoder->pipeline_bypass)
        apipeline_del (decoder->pipeline_bypass);

    decoder->pipeline_bypass = apipeline_new2 (preferred_proc, "decoder_es");
    decoder->uid_bypass = apipeline_appendf (decoder->pipeline_bypass, "bypass");

    bm_register_port_forward (block, PORT_IN, BYPASS_PORT, decoder->pipeline_bypass, 0);
    bm_register_port_forward (block, PORT_OUT, BYPASS_PORT, decoder->pipeline_bypass, 0);

    decoder->is_bypass_created = true;
}

static int decoder_preconnect (struct aud_block_info *block, int port, bool in)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    /* if got connection to bypass port, make! */
    if (port == BYPASS_PORT && decoder->pipeline_bypass == NULL)
    {
        info ("bypass path.. so make bypass path!\n");

        decoder_create_bypass (block);
    }

    return 0;
}

static void decoder_create_pipeline (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    int preferred_proc = bm_get_preffered_processor (block);

    block->pipeline = apipeline_new2 (preferred_proc, "decoder");
    decoder->uid_decbin = apipeline_addf (block->pipeline, "decoderbin");

    info ("pipeline created (preferred proc is %d)\n", preferred_proc);
}

/**
 * create decoder block
 *
 * @param block [in] context of this block
 * @param index [in] index of decoder
 * @return pointer of decoder info
*/
static int decoder_create (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    info ("create decoder\n");

    /* add to list */
    AUD_DEC_LOCK ();

    decoder_create_pipeline (block);

    decoder->is_bypass_created = false;
    block->isOpened = true;

    INIT_LIST_HEAD (&decoder->list_prop);
    INIT_LIST_HEAD (&decoder->list_event);
#ifdef SUPPORT_SOUNDBAR
    INIT_LIST_HEAD (&decoder->list_pending_prop);
    INIT_LIST_HEAD (&decoder->list_pending_event);
#endif
    AUD_DEC_UNLOCK ();

    info ("done\n");
    return 0;
}


/**
 * destroy decoder block
 *
 * @param block [in] context of this block
 * @return void
 * @see aud_decoder_info
*/
static void decoder_destroy (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;
    struct aud_decoder_property_info *prop_info = NULL;
    struct aud_decoder_property_info *next = NULL;
    struct aud_decoder_event_info *event_info = NULL;
    struct aud_decoder_event_info *next_event = NULL;

    info ("called\n");

    AUD_DEC_LOCK ();

    if (block == NULL)
    {
        error ("decoder_info is NULL!!");
        goto exit;
    }

    if (block->isOpened == false)
    {
        error ("decoder is already closed\n");
        goto exit;
    }

    // destroy pipeline (inside modules are destroyed automatically)
    if (block->pipeline)
        apipeline_del (block->pipeline);

    if (decoder->pipeline_bypass)
        apipeline_del (decoder->pipeline_bypass);

    decoder->is_bypass_created = false;

    // Clear a decoder resource.
    block->isOpened = false;

    list_for_each_entry_safe (prop_info, next, &decoder->list_prop, list)
    {
        debug ("remove property list, %s=%s\n", prop_info->name, prop_info->data);
        list_del (&prop_info->list);
        kfree (prop_info->name);
        kfree (prop_info->data);
        kfree (prop_info);
    }

    list_for_each_entry_safe (event_info, next_event, &decoder->list_event, list)
    {
        debug ("remove event list, event=%s\n", event_info->name);
        list_del (&event_info->list);
        kfree (event_info->name);
        kfree (event_info);
    }
#ifdef SUPPORT_SOUNDBAR
    list_for_each_entry_safe (prop_info, next, &decoder->list_pending_prop, list)
    {
        debug ("remove property list, %s=%s\n", prop_info->name, prop_info->data);
        list_del (&prop_info->list);
        kfree (prop_info->name);
        kfree (prop_info->data);
        kfree (prop_info);
    }

    list_for_each_entry_safe (event_info, next_event, &decoder->list_pending_event, list)
    {
        debug ("remove event list, event=%s\n", event_info->name);
        list_del (&event_info->list);
        kfree (event_info->name);
        kfree (event_info);
    }
#endif

    if (decoder->ui_param.phys_addr)
        hma_free ("audio_buffer", decoder->ui_param.phys_addr);

    if (decoder->ui_param.virtual_addr)
        vunmap_phys (decoder->ui_param.virtual_addr);

  exit:
    AUD_DEC_UNLOCK ();
    info ("done\n");
}

static int decoder_suspend (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    info ("called\n");

    decoder_unregister_event_all (block);

    if (block->pipeline)
        apipeline_del (block->pipeline);

    if (decoder->pipeline_bypass)
        apipeline_del (decoder->pipeline_bypass);

    block->pipeline = NULL;
    decoder->pipeline_bypass = NULL;

    info ("done\n");

    return 0;
}

static int decoder_resume (struct aud_block_info *block)
{
    struct aud_decoder_info *decoder = (struct aud_decoder_info *) block;

    info ("called\n");

    decoder_create_pipeline (block);
    if (decoder->is_bypass_created)
        decoder_create_bypass (block);

    if (decoder->codec)
    {
        unsigned int uid_dec = 0;
        struct aud_decoder_property_info *prop_info = NULL;

        if (decoder->is_dummy_codec)
        {
            info ("send dumm-codec to decoderbin\n");
            aimc_set_property (decoder->uid_decbin, "dummy-codec=true");
        }

        aimc_set_property (decoder->uid_decbin, "codec=%s", get_codec_name (decoder->codec));

        aimc_get_property (decoder->uid_decbin, "decoder-uid", &uid_dec);

        decoder->uid_dec = uid_dec;
        decoder_set_prio (block);
        decoder_update_event_id (block);

        if (decoder->codec == AUDIO_DECODER_CODEC_MPEG_H)
        {
            decoder_config_mpegh_ui_param (block);
        }

        list_for_each_entry (prop_info, &decoder->list_prop, list)
        {
            if (prop_info)
            {
                info ("set property, %s = %s\n", prop_info->name, prop_info->data);
                aimc_set_property (decoder->uid_dec, "%s=%s", prop_info->name, prop_info->data);
            }
        }

        aimc_set_property (decoder->uid_decbin, "connect=1");
    }

    info ("done\n");

    return 0;
}

static struct audio_block_impl block_impl = {
    .block_info_size = sizeof (struct aud_decoder_info),
    .block_type = "decoder",
    .preffered_processor = ADEC_CORE_DSP0,
    .constructor = decoder_create,
    .destructor = decoder_destroy,
    .pre_connect = decoder_preconnect,
    .suspend = decoder_suspend,
    .resume = decoder_resume,
};

void decoder_initializer (void)
{
    bm_block_registry (&block_impl);
}
