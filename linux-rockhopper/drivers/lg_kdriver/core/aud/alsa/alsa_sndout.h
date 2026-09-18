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



/** @file alsa_sndout.h
 *
 *  alsa sndout driver.
 *
 *  @author     Won Chang Shin(wonchang.shin@lge.com)
 *  @version    0.1
 *  @date       2025.05.12
 *
 *  @{
 */

#ifndef _ALSA_SNDOUT_H_
#define _ALSA_SNDOUT_H_

#include "linux/alsa-ext/alsa-ext-renderer.h"
#include "linux/alsa-ext/tv_alsa-ext-soundengine.h"

bool sndout_output_connected_any (common_output_ext_type_t output);
int sndout_get_capture_gain (void);
bool sndout_get_capture_mute (void);
struct aud_block_info *sndout_get_se_info (common_output_ext_type_t output);
unsigned int sndout_get_resampling_freq (void);
void sndout_set_resampling_freq (unsigned int rate);
bool sndout_get_input_downmix_enable (int input, int port);

int register_sndout_kcontrols (struct snd_soc_card *card);

#endif /* _ALSA_SNDOUT_H_ */



