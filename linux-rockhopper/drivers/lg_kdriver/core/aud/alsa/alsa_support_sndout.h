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


#ifndef _lg115x_ALSA_SNDOUT_KCONTROL_H_
#define _lg115x_ALSA_SNDOUT_KCONTROL_H_

#include "linux/alsa-ext/alsa-ext-renderer.h"

void sndout_connect_output (void);
//void sndout_disconnect_pass_through (int master_index, LX_AUD_MASTER_OUTPUT_T master_output);
int sndout_get_input_info (int index, int *gain, int *mute, int *delay);
int sndout_get_gain_duration_info (int index, int *gain, int *duration);
//void sndout_update_capture_info (ADEC_MODULE_ID modGain, ADEC_MODULE_ID modPcmcvt);
void sndout_set_audio_desc (int ad_index, bool prev_ad_on, bool ad_on);
bool sndout_get_atmos_encode_on (void);
void sndout_set_dolby_ottmode (int ott, int atmos_locking);
void sndout_speaker_onoff (bool on);
bool output_is_added (common_output_ext_type_t output);
struct aud_block_info *_get_capture_source_block (int capture_source);
#ifdef SUPPORT_SOUNDBAR
int sndout_get_decoder_spk_conf (void);
#endif
#endif /* _lg115x_ALSA_SNDOUT_KCONTROL_H_ */

