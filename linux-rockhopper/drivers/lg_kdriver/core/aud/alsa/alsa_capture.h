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



/** @file alsa_capture.h
 *
 *  alsa capture driver.
 *
 *  @author     wunseo.yeo@lge.com
 *  @version    0.1
 *  @date       2025.05.12
 *
 *  @{
 */

#ifndef _ALSA_CAPTURE_H_
#define _ALSA_CAPTURE_H_

int acapture_set_gain (common_output_ext_type_t output, int gain);
int acapture_set_mute (common_output_ext_type_t output, bool mute);
bool acapture_is_encoder_connected (void);
int register_aenc_audio_kcontrols (struct snd_soc_card *card);

#endif /* _ALSA_CAPTURE_H_ */



