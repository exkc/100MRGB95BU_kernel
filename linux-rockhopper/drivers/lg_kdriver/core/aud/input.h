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

/**
 *  @file input.h
 *
 *  Audio driver implementation for audio input block.
 *  Input block manages TP, HDMI, ADC, SIF and MEMORY input.
 *
 *  @author	Jong-Sang Oh(jongsang.oh@lge.com)
 *  @version    0.1
 *  @date       2020/06/30
 *
 *  @addtogroup input
 *  @{
 */
#ifndef _INPUT_H_
#define _INPUT_H_

#include "block.h"
#include "aud_kapi_decoder.h"

#define INPUT_SIF_INDEX 100

/**
 *  @enum input_type
 */
enum input_type
{
    INPUT_SIF,                  ///< SIF input(ATV)
    INPUT_TP,                   ///< TP input(0 : TP0(Main), 1 : TP1(Sub)
    INPUT_HDMI,                 ///< HDMI input(0 ~ 3 : HDMI0 ~ HDMI3)
    INPUT_ADC,                  ///< ADC input(1 : ADC, other : Mute)
#ifdef SUPPORT_SOUNDBAR
    INPUT_I2S,                  ///< I2S input(0 : I2S0)(E-ARC for soundbar)
#endif
    INPUT_MAX
};

/**
 *  @enum input_evt
 */
enum input_evt
{
    INPUT_EVT_TP_ES_EXIST_INFO, ///< TP ES exist Event
    INPUT_EVT_HDMI_PCM_FORMAT,  ///< HDMI PCM(IEC 60958) Format Event
    INPUT_EVT_TP_PDEC_ERROR_INFO,       ///< TP PDEC Error Event
#ifdef SUPPORT_DTSX
    INPUT_EVT_HDMI_DTS_FORMAT_CHANGED,  ///< HDMI Input DTS Format Changed Event
#endif
    INPUT_EVT_MAX
};


/**
 *  @enum hdmi_audio_type
 */
enum hdmi_audio_codec
{
    HDMI_AUDIO_DVI = 0,         ///< DVI Type
    HDMI_AUDIO_NO_AUDIO = 1,    ///< No Audio Type
    HDMI_AUDIO_PCM = 2,         ///< PCM Type
    HDMI_AUDIO_AC3 = 3,         ///< AC3 Type
    HDMI_AUDIO_DTS = 4,         ///< DTS Type
    HDMI_AUDIO_AAC = 5,         ///< AAC Type
    HDMI_AUDIO_DEFAULT = 6,     ///< DEFAULT Type
    HDMI_AUDIO_MPEG = 10,       ///< MPEG Type
    HDMI_AUDIO_DTS_HD_MA = 11,  ///< DTS-HD MA Type
    HDMI_AUDIO_DTS_EXPRESS = 12,        ///< DTS-Express Type
    HDMI_AUDIO_DTS_CD = 13,     ///< DTS-CD Type
    HDMI_AUDIO_EAC3 = 14,       ///< Enhanced AC3 Type.(EAC3 is added by TV Lab Request.(SCDCR-861, 2016.03.23))
    HDMI_AUDIO_EAC3_ATMOS = 15, ///< Enhanced AC3 ATMOS Type
    HDMI_AUDIO_MAT = 16,        ///< MAT Type
    HDMI_AUDIO_MAT_ATMOS = 17,  ///< MAT ATMOS Type
    HDMI_AUDIO_TRUE_HD = 18,    ///< TRUE HD Type
    HDMI_AUDIO_TRUE_HD_ATMOS = 19,      ///< TRUE HD ATMOS Type

    HDMI_AUDIO_AC3_IEC60958 = 200,      ///< AC3 Type, IEC60958 Format(Internal Use)
    HDMI_AUDIO_EAC3_IEC60958 = 201,     ///< Enhanced AC3 Type, IEC60958 Format(Internal Use)
    HDMI_AUDIO_DTS_HD = 202,    ///< DTS-HD Type(Internal Use)
    HDMI_AUDIO_DTS_HD_HRA = 203,        ///< DTS-HD High Resolution Audio Type(Internal Use)

    /* Unknown */
    HDMI_AUDIO_UNKNOWN_AC3 = 1003,      ///< AC3 Type
    HDMI_AUDIO_UNKNOWN_DTS = 1004,      ///< DTS Type
    HDMI_AUDIO_UNKNOWN_AAC = 1005,      ///< AAC Type
    HDMI_AUDIO_UNKNOWN_MPEG = 1010,     ///< MPEG Type
    HDMI_AUDIO_UNKNOWN_EAC3 = 1014,     ///< Enhanced AC3 Type.(EAC3 is added by TV Lab Request.(SCDCR-861, 2016.03.23))
    HDMI_AUDIO_UNKNOWN_MAT = 1016,      ///< MAT Type
    HDMI_AUDIO_UNKNOWN_DTS_HD = 1202,   ///< DTS-HD Type(Internal Use)
    HDMI_AUDIO_UNKNOWN_DTS_HD_HRA = 1203,       ///< DTS-HD High Resolution Audio Type(Internal Use)
};

#ifdef SUPPORT_SOUNDBAR
/**
 *  @enum i2s_audio_type
 */
enum i2s_audio_type
{
    I2S_AUDIO_TYPE_UNKNOWN,        ///< Unknown
    I2S_AUDIO_TYPE_PCM,            ///< PCM
    I2S_AUDIO_TYPE_AUTO,           ///< Auto(DD/DDP/AAC)
    I2S_AUDIO_TYPE_HBR,            ///< HBR(MAT/DTS:X)
};
#endif

/**
 * @brief
 * type of callback function
 *
 * @details
 * input callback function
 */
typedef int (*input_callback_func) (void *param, int cb_param_len, void *cb_param);

int input_tp_pdec_error_info_cb (void *param, int cb_param_len, void *cb_param);
#ifdef SUPPORT_DTSX
int input_hdmi_dts_format_changed_cb (void *param, int cb_param_len, void *cb_param);
#endif
int input_start (struct aud_block_info *block);
int input_stop (struct aud_block_info *block);
enum input_type input_get_type (struct aud_block_info *block);
enum audio_decoder_codec input_get_hdmi_codec (struct aud_block_info *block);
int input_get_index (struct aud_block_info *block);
int input_get_uid (struct aud_block_info *block);
int input_get_int_count (struct aud_block_info *block, int *int_count, int *clock_count);
int input_get_overflow_count (struct aud_block_info *block, int *overflow_count);
int input_set_type (struct aud_block_info *block, int dec_index, enum input_type type_input,
    int index, bool update);
int input_set_hdmi (struct aud_block_info *block, bool forced_pcm);
int input_set_hdmi_bypass (struct aud_block_info *block, bool data_drop, int output_port);
int input_set_hdmi_multi_pcm_out (struct aud_block_info *block, bool enable);
#ifdef SUPPORT_SOUNDBAR
int input_set_i2s_port_count (struct aud_block_info *block, int i2s_port_count);
int input_set_i2s (struct aud_block_info *block, bool forced_pcm, int i2s_hdmi_type,
    int i2s_hdmi_ch, int i2s_hdmi_freq);
#endif
int input_set_tp (struct aud_block_info *block, enum audio_decoder_codec tp_codec, bool clock_x4);
int input_register_event (struct aud_block_info *block, enum input_evt event,
    int (*cb_func) (void *, int, void *), struct aud_block_info *cb_target_block);
int input_unregister_event (struct aud_block_info *block, enum input_evt event);
int input_drop_data (struct aud_block_info *block, bool drop);
bool input_is_drop_data (struct aud_block_info *block);
void input_initializer (void);

#endif /* _INPUT_H_ */
