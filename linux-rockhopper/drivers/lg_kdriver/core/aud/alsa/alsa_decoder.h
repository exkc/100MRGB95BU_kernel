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


#ifndef _lg115x_ALSA_DECODER_KCONTROL_H_
#define _lg115x_ALSA_DECODER_KCONTROL_H_

#include "linux/alsa-ext/alsa-ext-broadcast.h"

#define ALSA_ADEC_MAX 2
#define ALSA_AMIXER_MAX 8
#define AUDIO_GUIDANCE_MIXER_INDEX 7      //mixer7
#define AUDIO_GUIDANCE_MASTER_INDEX (ALSA_ADEC_MAX + AUDIO_GUIDANCE_MIXER_INDEX)

#define ENABLE_DECODER_OUTPUT_MODE

#ifdef ENABLE_DECODER_OUTPUT_MODE
enum DECODER_OUTPUT_MODE {
    DECODER_OUTPUT_MAIN,
    DECODER_OUTPUT_SUB,
};
#else
enum DECODER_OUTPUT_DROP {
    DECODER_OUTPUT_DROP_NONE,
    DECODER_OUTPUT_DROP_MAIN,
    DECODER_OUTPUT_DROP_SUB,
};
#endif

typedef struct
{
    adec_ac4_lang_code_ext_type_t iso_type;
    int lang;
} AC4_LANG_INFO_T;

typedef struct
{
    struct aud_block_info *dec_info;

    bool is_open;
    bool is_main_dec;
    bool is_started;
    adec_src_port_index_ext_type_t input;
    adec_src_port_index_ext_type_t prev_input;
    adec_src_codec_ext_type_t codec;
    adec_src_codec_ext_type_t src_format;
    AC4_LANG_INFO_T first_lang;
    AC4_LANG_INFO_T second_lang;
    adec_ac4_ad_ext_type_t ad_type;
    adec_ac4_ad_ext_type_t prio_ad_type;
    int ac4_group_index;
    int dialog_gain;
    adec_dualmono_mode_ext_type_t dualmono_mode;
    adec_dolbydrc_mode_ext_type_t drc;
    adec_downmix_mode_ext_type_t downmix;
    int ac4_ad_on_off;
    int default_prl;
    int associate_audio_volume;
    bool downmix_2ch;

#ifdef ENABLE_DECODER_OUTPUT_MODE
    bool hdmi_output_main;
    bool hdmi_output_sub;
#else
    enum DECODER_OUTPUT_DROP output_drop;
#endif
    bool hdmi_multi_pcm_out;
    bool is_connected;

#ifdef SUPPORT_SOUNDBAR
    int i2s_hdmi_type;
    int i2s_hdmi_ch;
    int i2s_hdmi_freq;
    int i2s_port_count;
#endif
} ALSA_DECODER_INFO_T;

typedef struct
{
    struct aud_block_info *ren_info;

    bool is_open;
    bool sync;
    adec_trick_mode_ext_type_t trick;
    bool is_play_paused;
    bool master_syncmode;
    int offset;
} ALSA_RENDERER_INFO_T;

typedef struct
{
    struct aud_block_info *input_info;

    int index;
} ALSA_INPUT_INFO_T;

typedef struct
{
    int is_opened;
    int adc_port_index;
    int is_closed;
} ALSA_ADC_INFO_T;

int decoder_enable_atmos_decoding (bool enable);
int decoder_set_main_audio_index (int index);
adec_dolbydrc_mode_ext_type_t decoder_get_drc_mode (int index);
adec_downmix_mode_ext_type_t decoder_get_downmix_mode (int index);
#ifdef ENABLE_DECODER_OUTPUT_MODE
int decoder_set_output_mode (int index, enum DECODER_OUTPUT_MODE output_mode, bool enable);
#else
int decoder_set_output_drop (int index, enum DECODER_OUTPUT_DROP output_drop);
#endif
int decoder_set_multi_pcm_out (int index, bool enable);
int decoder_set_downmix (int index, bool enable);
#ifdef SUPPORT_SOUNDBAR
bool decoder_sb_codec_supported (adec_src_codec_ext_type_t codec);
#endif
int register_decoder_kcontrols (struct snd_soc_card *card);
#endif /* _lg115x_ALSA_DECODER_KCONTROL_H_ */
