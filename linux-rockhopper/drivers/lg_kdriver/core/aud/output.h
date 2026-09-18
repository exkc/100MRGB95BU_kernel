/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2017 by LG Electronics Inc.
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
 *  @file output.h
 *
 *  Audio driver implementation for  audio output block.
 *  Output block manages Speaker, Headphone(HP), Optic(SPDIF), and ARC output(include eARC).
 *
 *  @author	    wonchang.shin (wonchang.shin@lge.com)
 *  @version    0.1
 *  @date       2020/06/29
 *
 *  @addtogroup output
 *  @{
 */

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "block.h"
#include "linux/alsa-ext/alsa-ext-common.h"

/**
 *  @enum output_type
 *  device type to output audio.
 */
enum output_type_t
{
    OUTPUT_SPEAKER,             ///< speaekr output
    OUTPUT_HP,                  ///< headphone output
    OUTPUT_OPTIC,               ///< optic(SPDIF) output
    OUTPUT_ARC,                 ///< arc(audio return channel) include eARC
#ifdef SUPPORT_SOUNDBAR
    OUTPUT_PC,                  ///< pc(gaming) output
#endif
    OUTPUT_MAX,                 ///< max output
};

/**
 * @enum OUTPUT Codec Type.
 */
enum output_codec_t
{
    OUTPUT_CODEC_PCM,
    OUTPUT_CODEC_AC3,
    OUTPUT_CODEC_EAC3,
    OUTPUT_CODEC_AAC,
    OUTPUT_CODEC_MAT,
#ifdef SUPPORT_DTSX
    OUTPUT_CODEC_DTS,
    OUTPUT_CODEC_DTS_HD,
    OUTPUT_CODEC_DTS_HD_MA,
    OUTPUT_CODEC_DTSX_P1,
    OUTPUT_CODEC_DTSX_P2,
#endif
    OUTPUT_CODEC_MAX,
};

/**
 *  @struct sound_bar_param
 */
struct sound_bar_param
{
    unsigned int id;            ///< Sound Bar id
    unsigned int data;          ///< Sound Bar data. 8th bit is mute, 0~7th bits are volume.

};

/**
 *  @struct sound_bar_command
 */
struct sound_bar_command
{
    unsigned int mode;          ///< command mode
    unsigned int param;         ///< parameters of command
};

struct output_format
{
    enum output_codec_t codec;
    unsigned int channel;
    unsigned int sample_rate;
};

int output_set_on (struct aud_block_info *block, bool on);
int output_set_mute (struct aud_block_info *block, bool on);
int output_set_volume (struct aud_block_info *block, unsigned int volume);
int output_set_delay (struct aud_block_info *block, unsigned int delay);
int output_set_format (struct aud_block_info *block, enum output_codec_t codec, unsigned int channel, unsigned int sample_rate, bool bypass);
int output_set_type (struct aud_block_info *block, enum output_type_t output_type);
int output_set_scms (struct aud_block_info *block, unsigned int scms);
int output_set_category_code (struct aud_block_info *block, unsigned int category_code);
void output_initializer (void);
int output_set_earc_on (struct aud_block_info *block, bool on);

int output_set_sound_bar_on (struct aud_block_info *block, bool on);
int output_set_sound_bar_param (struct aud_block_info *block, struct sound_bar_param *param);
int output_set_sound_bar_power (struct aud_block_info *block, bool on);

int output_set_input_index (struct aud_block_info *block, int index);
int output_get_underflow (struct aud_block_info *block, unsigned int *underflow);
int output_get_latency (struct aud_block_info *block, int *latency);

int output_get_format (struct aud_block_info *block, struct output_format *format);
int output_get_bc_write_time (struct aud_block_info *block, unsigned long long *bc_write_time);

#endif /* _OUTPUT_H_ */
/** @} */
