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
 *  @file encoder.h
 *  @addtogroup encoder
 *
 *  \section interface Interface
 *
 *              (up)
 *      (left) ENCODER (right)
 *              (down)
 *
 *  (up): ALSA Kcontrol\n
 *  (down): aacenc, aacmchenc, ddpenc, matenc, opusenc\n
 *  (left): Input, Mixer\n
 *  (right): Output, Capture\n
 *
 *  \section dataflow  Data Flow
 *
 *  ATV Encoding: Input(ATV) - Encoder - Capture\n
 *  Encoding (except for ATV): Mixer - Encoder - Output\n
 *
 *  \section controlflow  Control Flow
 *
 *  Start/Stop Encoder: ALSA KControl - Encoder - encoder\n
 *
 */

#ifndef _ENCODER_H
#define _ENCODER_H

#include "output.h"

#ifdef SUPPORT_DTSX
#define AUD_ENCODER_DTSX_DEFAULT_ENC_MODE 2
#endif

void aud_encoder_initializer (void);
int aud_encoder_set_codec (struct aud_block_info *block, enum output_codec_t codec, int channel);
int aud_encoder_set_acmod (struct aud_block_info *block, int acmod);
int aud_encoder_set_pre_gain (struct aud_block_info *block, int gain);
int aud_encoder_set_atmos_on (struct aud_block_info *block, bool atmos_on);
int aud_encoder_set_atmos_locking_mode (struct aud_block_info *block, bool atmos_lock_mode);
int aud_encoder_set_ch_lock_mode (struct aud_block_info *block, bool ch_lock_on);
#ifdef SUPPORT_DTSX
int aud_encoder_set_dtsx_enc_mode (struct aud_block_info *block, int enc_mode);
int aud_encoder_get_dtsx_enc_mode (struct aud_block_info *block);
#endif
#endif //_ENCODER_H
