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


/** @file aud_kapi_decoder.h
 *
 *  @author     Jihoon Lee (gaius.lee@lge.com)
 *  @version    0.1
 *  @date       2020.09.28
 *  @note       The simple wrapper function for audio kernel module.
 *
 */

#ifndef _AUD_KAPI_DECODER_H_
#define _AUD_KAPI_DECODER_H_

#include "aud_kapi.h"

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define ADEC_IOC_MAGIC                       'D'

/*----------------------------------------------------------------------------------------
    IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define ADEC_IOW_SET_INDEX                          _IOW(ADEC_IOC_MAGIC, 1, int)
#define ADEC_IOW_SET_CODEC                          _IOW(ADEC_IOC_MAGIC, 2, unsigned int)
#define ADEC_IOW_SET_CODEC_PARAM                    _IOW(ADEC_IOC_MAGIC, 3, adec_codec_param_t)
#define ADEC_IOR_GET_UID                            _IOR(ADEC_IOC_MAGIC, 4, unsigned int)
#define ADEC_IO_START                               _IO (ADEC_IOC_MAGIC, 5)
#define ADEC_IO_STOP                                _IO (ADEC_IOC_MAGIC, 6)

#define ADEC_IOW_SET_OUTPUT_MODE                    _IOW(ADEC_IOC_MAGIC, 11, unsigned int)
#define ADEC_IOR_GET_DECODED_INFO                   _IOWR(ADEC_IOC_MAGIC, 12, struct decoded_info)
#define ADEC_IOW_SET_INPUT                          _IOW(ADEC_IOC_MAGIC, 13, unsigned int)
#define ADEC_IOR_GET_INPUT                          _IOWR(ADEC_IOC_MAGIC, 14, struct input_info)
#define ADEC_IOW_SET_UI_PARAM                       _IOW(ADEC_IOC_MAGIC, 15, struct adec_mpegh_ui_param)
#define ADEC_IOR_GET_UI_PARAM                       _IOR(ADEC_IOC_MAGIC, 16, struct adec_mpegh_ui_param)
#define ADEC_IOW_SET_BASETIME                       _IOW(ADEC_IOC_MAGIC, 17, unsigned long long)
#define ADEC_IOW_SET_PRESENTATION_GROUP_INDEX       _IOW(ADEC_IOC_MAGIC, 18, unsigned int)
#define ADEC_IOW_SET_DEFAULT_PRL                    _IOW(ADEC_IOC_MAGIC, 19, unsigned int)
#define ADEC_IOW_SET_GAP_INFO                       _IOW(ADEC_IOC_MAGIC, 20, struct gap_info)
#define ADEC_IOW_SET_DIALOG_ENHANCEMENT_GAIN        _IOW(ADEC_IOC_MAGIC, 21, unsigned int)
#define ADEC_IOR_GET_DIALOG_ENHANCEMENT_GAIN        _IOR(ADEC_IOC_MAGIC, 22, unsigned int)
#define ADEC_IOR_GET_DIALOG_ENHANCEMENT_LIMIT       _IOR(ADEC_IOC_MAGIC, 23, unsigned int)
#ifdef SUPPORT_DTSX
#define ADEC_IOR_GET_DTS_SUPPORTED                  _IOR(ADEC_IOC_MAGIC, 24, bool)
#define ADEC_IOR_GET_DTS_BITSTREAM_PASSTHROUGH      _IOR(ADEC_IOC_MAGIC, 25, bool)
#endif
#define ADEC_IOW_SET_DOLBY_DRC_MODE                 _IOW(ADEC_IOC_MAGIC, 26, unsigned int)
#define ADEC_IOW_SET_AAC_FORMAT_TYPE                _IOW(ADEC_IOC_MAGIC, 27, unsigned int)
#define ADEC_IOW_SET_PROC_ID                        _IOW(ADEC_IOC_MAGIC, 28, unsigned int)
#define ADEC_IOW_SET_NORM_CLOSED                    _IO(ADEC_IOC_MAGIC, 29)
#define ADEC_IOW_SET_DOWNMIX                        _IOW(ADEC_IOC_MAGIC, 30, bool)
#define ADEC_IOW_SET_SOUND_SYSTEM                   _IOW(ADEC_IOC_MAGIC, 31, unsigned int)
#define ADEC_IOW_SET_MUSIC_MODE                     _IOW(ADEC_IOC_MAGIC, 32, bool)

#define MPEGH_SIZE_OF_SET_UI       1024 * 128
#define MPEGH_SIZE_OF_GET_UI       1024 * 128

/**
 * audio deccoder input
 */
enum audio_decoder_input {
    AUDIO_DECODER_INPUT_NONE,
    AUDIO_DECODER_INPUT_TP0,
    AUDIO_DECODER_INPUT_TP1,
    AUDIO_DECODER_INPUT_SIF,
    AUDIO_DECODER_INPUT_ADC,
    AUDIO_DECODER_INPUT_HDMI0,
    AUDIO_DECODER_INPUT_HDMI1,
    AUDIO_DECODER_INPUT_HDMI2,
    AUDIO_DECODER_INPUT_HDMI3,
    AUDIO_DECODER_INPUT_I2S,
    AUDIO_DECODER_INPUT_SYSTEM,
    AUDIO_DECODER_INPUT_SYSTEM_CLIP,
    AUDIO_DECODER_INPUT_MAX,
};

/**
 * audio deccoder Codec Type.
 */
enum audio_decoder_codec {
    AUDIO_DECODER_CODEC_UNKNOWN,
    AUDIO_DECODER_CODEC_PCM,
    AUDIO_DECODER_CODEC_AC3,
    AUDIO_DECODER_CODEC_EAC3,
    AUDIO_DECODER_CODEC_AC4,
    AUDIO_DECODER_CODEC_MAT,
    AUDIO_DECODER_CODEC_TRUE_HD,
    AUDIO_DECODER_CODEC_AAC,
    AUDIO_DECODER_CODEC_MP3,
    AUDIO_DECODER_CODEC_MPEG_H,
    AUDIO_DECODER_CODEC_DRA,
#ifdef SUPPORT_WMA
    AUDIO_DECODER_CODEC_WMA_PRO,
#endif
    AUDIO_DECODER_CODEC_VORBIS,
    AUDIO_DECODER_CODEC_AMR_WB,
    AUDIO_DECODER_CODEC_AMR_NB,
    AUDIO_DECODER_CODEC_ADPCM,
    AUDIO_DECODER_CODEC_FLAC,
#ifdef SUPPORT_DTSX
    AUDIO_DECODER_CODEC_DTS,
    AUDIO_DECODER_CODEC_DTS_HD,
#endif
    AUDIO_DECODER_CODEC_OPUS,
    AUDIO_DECODER_CODEC_AAC_BYPASS,
    AUDIO_DECODER_CODEC_AAC_ELD,
    AUDIO_DECODER_CODEC_RA8,
    AUDIO_DECODER_CODEC_IAMF,
    AUDIO_DECODER_CODEC_AUTO,
    AUDIO_DECODER_CODEC_MAX,
};

/**
 * audio deccoder event
 */
enum audio_decoder_event {
    AUDIO_DECODER_EVENT_ERROR,
    AUDIO_DECODER_EVENT_INFO,
    AUDIO_DECODER_EVENT_MPEGH_UI,
    AUDIO_DECODER_EVENT_DEC_ID_CHANGED,
    AUDIO_DECODER_EVENT_MAX,
};

enum audio_decoder_dualmono_mode {
    AUDIO_DECODER_DUALMONO_MODE_LR,
    AUDIO_DECODER_DUALMONO_MODE_LL,
    AUDIO_DECODER_DUALMONO_MODE_RR,
    AUDIO_DECODER_DUALMONO_MODE_MIX,
    AUDIO_DECODER_DUALMONO_MODE_LR_FORCED,
    AUDIO_DECODER_DUALMONO_MODE_LL_FORCED,
    AUDIO_DECODER_DUALMONO_MODE_RR_FORCED,
    AUDIO_DECODER_DUALMONO_MODE_MIX_FORCED,
    AUDIO_DECODER_DUALMONO_MODE_MAX,
};

enum audio_decoder_downmix {
	AUDIO_DECODER_DOWNMIX_LORO,
	AUDIO_DECODER_DOWNMIX_LTRT,
	AUDIO_DECODER_DOWNMIX_ARIB,
};

enum audio_decoder_drc {
	AUDIO_DECODER_DRC_LINE,
	AUDIO_DECODER_DRC_RF,
	AUDIO_DECODER_DRC_OFF,
};

enum audio_decoder_channel_mode {
    AUDIO_DECODER_CH_MODE_MONO,
    AUDIO_DECODER_CH_MODE_JOINT_STEREO,
    AUDIO_DECODER_CH_MODE_STEREO,
    AUDIO_DECODER_CH_MODE_DUAL_MONO,
    AUDIO_DECODER_CH_MODE_MULTI,
    AUDIO_DECODER_CH_MODE_UNKNOWN,
    AUDIO_DECODER_CH_MODE_2_1_FL_FR_LFE,
    AUDIO_DECODER_CH_MODE_3_0_FL_FR_RC,
    AUDIO_DECODER_CH_MODE_3_1_FL_FR_RC_LFE,
    AUDIO_DECODER_CH_MODE_4_0_FL_FR_RL_RR,
    AUDIO_DECODER_CH_MODE_4_1_FL_FR_RL_RR_LFE,
    AUDIO_DECODER_CH_MODE_5_0_FL_FR_FC_RL_RR,
    AUDIO_DECODER_CH_MODE_5_1_FL_FR_FC_RL_RR_LFE,
};

enum audio_decoder_input_tp {
    AUDIO_DECODER_INPUT_TP_0,
    AUDIO_DECODER_INPUT_TP_1,
};

enum aac_codec_version {
    AAC_CODEC_VERSION_AAC,
    AAC_CODEC_VERSION_HEAAC_V1,
    AAC_CODEC_VERSION_HEAAC_V2,
};

#ifdef SUPPORT_DTSX
enum dts_codec_detail {
    AUDIO_DECODER_DTS_DETAIL_NONE,
    AUDIO_DECODER_DTS_DETAIL_DTS,
    AUDIO_DECODER_DTS_DETAIL_DTS_HD,
    AUDIO_DECODER_DTS_DETAIL_DTS_EXPRESS,
    AUDIO_DECODER_DTS_DETAIL_DTS_CD,
    AUDIO_DECODER_DTS_DETAIL_DTS_HD_MA,
    AUDIO_DECODER_DTS_DETAIL_DTS_X_1,
    AUDIO_DECODER_DTS_DETAIL_DTS_X_2,
    AUDIO_DECODER_DTS_DETAIL_MAX,
};
#endif

struct decoded_info
{
    unsigned int index;

    enum audio_decoder_codec codec;

    unsigned int sampling_rate;
    unsigned int avg_bit_rate;

    unsigned int source_channels;
    unsigned int channels;
    unsigned int bit_per_sample;

    unsigned int acmod;

    // HEAAC
    unsigned int version;   // 0: AAC, 1: HE-AACv1, 2: HE-AACv2
    unsigned int transmissionformat;    // 0: LOAS/LATM, 1: ADTS

    // MPEG
    unsigned int layer;

    // AC3
    unsigned int atmos;
    unsigned int eac3;

    // MAT
    unsigned int truehd;

    enum audio_decoder_channel_mode audio_mode;

    // HDMI PCM
    unsigned int pc_valid_pcm;   // 0: es, 1: pcm

    // TP ES
    unsigned int is_es_exist;   // 0: non exist, 1: exist

#ifdef SUPPORT_DTSX
    // DTS
    enum dts_codec_detail dts_detail;
    unsigned int pass_through;
#endif
};

struct input_info
{
    unsigned int index;

    enum audio_decoder_input input;
};

/**
 * AUDIO DECODER UI Parameters for MHPEG-H 3D Audio.
 */
typedef struct adec_mpegh_ui_param {
    unsigned int size;
    union
    {
        void *param;
        unsigned int compat_param;
        unsigned long long sizer;
    };
} adec_mpegh_ui_param_t;

/**
 * AUDIO DECODER Gap Handling Parameter.
 */
struct gap_info
{
    unsigned int start_pts;
    unsigned int end_pts;
};

/**
 * AUDIO Decoder Codec Parameter.
 */
typedef struct adec_codec_param {
    unsigned int size;
    union
    {
        void *param;
        unsigned int compat_param;
        unsigned long long sizer;
    };
} adec_codec_param_t;

/**
 * AUDIO Decoder Codec (PCM) Parameter.
 */
typedef struct adec_pcm_param {
    unsigned int sampling_rate;
    unsigned int channels;
    unsigned int bits_per_sample;
    unsigned int byte_align;
    unsigned int sign;
} adec_pcm_param_t;

/**
 * AUDIO Decoder Codec (AC3) Parameter.
 */
typedef struct adec_ac3_param {
    unsigned int sampling_rate;
    unsigned int channels;
    unsigned int drc_mode;
    unsigned int downmix_mode;
    bool audio_description;
    bool atmos_decoding;
    bool legacy_ddp_out;
    unsigned int play_speed;
    bool downmix;
} adec_ac3_param_t;

/**
 * AUDIO Decoder Codec (AAC) Parameter.
 */
typedef struct adec_aac_param {
    unsigned int sampling_rate;
    unsigned int channels;
    unsigned int drc_mode;
    unsigned int downmix_mode;
    bool audio_description;
    unsigned int iec_format; // aac bypass
    bool transcoding;
    unsigned int play_speed;
    bool downmix;
} adec_aac_param_t;

/**
 * AUDIO Decoder Codec (AAC-ELD) Parameter.
 */
typedef struct adec_aac_eld_param {
    unsigned int sampling_rate;
    unsigned int channels;
} adec_aac_eld_param_t;

/**
 * AUDIO Decoder Codec (DRA) Parameter.
 */
typedef struct adec_dra_param {
    unsigned int sampling_rate;
    unsigned int channels;
} adec_dra_param_t;

/**
 * AUDIO Decoder Codec (MP3) Parameter.
 */
typedef struct adec_mp3_param {
    unsigned int sampling_rate;
    unsigned int channels;
    unsigned int drc_mode;
    unsigned int audio_description;
} adec_mp3_param_t;

/**
 * AUDIO Decoder Codec (MPEG-H) Parameter.
 */
typedef struct adec_mpegh_param {
    unsigned int sampling_rate;
    unsigned int channels;
    bool downmix;
} adec_mpegh_param_t;

/**
 * AUDIO Decoder Codec (AC4) Parameter.
 */
typedef struct adec_ac4_param {
    unsigned int sampling_rate;
    unsigned int channels;
    unsigned int drc_mode;
    unsigned int downmix_mode;
    unsigned int audio_description;
    bool atmos_decoding;
    unsigned int de_gain;
    bool legacy_ddp_out;
    unsigned int play_speed;
    bool downmix;
} adec_ac4_param_t;

#ifdef SUPPORT_WMA
/**
 * AUDIO Decoder Codec (WMA) Parameter.
 */
typedef struct adec_wma_param {
    unsigned int sampling_rate;
    unsigned int channels;
    unsigned int bits_per_sample;
    unsigned int wma_format_tag;
    unsigned int block_align;
    unsigned int avg_bps;
    unsigned int channel_mask;
    unsigned int encode_opt;
    unsigned int adv_encode_opt;
    unsigned int adv_encode_opt2;
} adec_wma_param_t;
#endif

/**
 * AUDIO Decoder Codec (VORBIS) Parameter.
 */
typedef struct adec_vorbis_param {
    unsigned int sampling_rate;
    unsigned int channels;
} adec_vorbis_param_t;

/**
 * AUDIO Decoder Codec (AMRWB/AMRNB) Parameter.
 */
typedef struct adec_amr_param {
    unsigned int sampling_rate;
    unsigned int channels;
} adec_amr_param_t;

/**
 * AUDIO Decoder Codec (ADPCM) Parameter.
 */
typedef struct adec_adpcm_param {
    unsigned int sampling_rate;
    unsigned int channels;
} adec_adpcm_param_t;

/**
 * AUDIO Decoder Codec (RA8) Parameter.
 */
typedef struct adec_ra8_param {
    unsigned int sampling_rate;
    unsigned int channels;
} adec_ra8_param_t;

/**
 * AUDIO Decoder Codec (FLAC) Parameter.
 */
typedef struct adec_flac_param {
    unsigned int sampling_rate;
    unsigned int channels;
} adec_flac_param_t;

/**
 * AUDIO Decoder Codec (OPUS) Parameter.
 */
typedef struct adec_opus_param {
    unsigned int sampling_rate;
    unsigned int channels;
    bool downmix;
} adec_opus_param_t;

#ifdef SUPPORT_DTSX
/**
 * AUDIO Decoder Codec (DTSX) Parameter.
 */
typedef struct adec_dtsx_param {
    bool bitstream_passthrough;
} adec_dtsx_param_t;
#endif

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _AUD_KAPI_DECODER_H_ */
