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

/** @file
 * @ingroup Mixer
 *
 * driver interface header for audio renderer
 *
 */

#ifndef _MIXER_H_
#define _MIXER_H_

#include "block.h"
#include "pipeline.h"

/**
 * EASE TYPE of EASE VOLUME
 */
enum MIXER_EASE_TYPE_T
{
    MIXER_EASE_LINEAR,                         ///< LINEAR
    MIXER_EASE_INCUBIC,                        ///< INCUBIC
    MIXER_EASE_OUTCUBIC,                       ///< OUTCUBIC
    MIXER_EASE_MAX,                            ///< MAX
};

/**
 * pcmrenderer downmix mode
 */
enum pcmren_downmix_mode
{
    PCMREN_DOWNMIX_LTRT_MODE,
    PCMREN_DOWNMIX_LORO_MODE,
};

/**
 * msmixer mixing mode
 */
enum msmixer_mixing_mode {
    MSMIXER_MIXING_MODE_STRINGENT, // AD MIXER (Main + Sub (Associate) : Audio Description On
    MSMIXER_MIXING_MODE_LENIENT,   // SYSTEM MIXER
    MSMIXER_MIXING_MODE_AGGREGATE, // AD MIXER (Main + Main)
    MSMIXER_MIXING_MODE_MAX,
};

enum mixer_module_type
{
    MIXER_MODULE_TYPE_DELAY,
    MIXER_MODULE_TYPE_FADER,
    MIXER_MODULE_TYPE_GAIN,
    MIXER_MODULE_TYPE_MIXER,
    MIXER_MODULE_TYPE_PCMREN,
#ifdef SUPPORT_DTSX
    MIXER_MODULE_TYPE_DTSREN,
#endif
    MIXER_MODULE_TYPE_MAX,
};

int mixer_get_main_audio_index (struct aud_block_info* block);
int mixer_set_main_audio_index (struct aud_block_info* block, int main_audio_index);
int mixer_set_volume (struct aud_block_info* block, int port, unsigned int volume);
int mixer_get_volume (struct aud_block_info *block, int port, unsigned int *volume);
int mixer_set_ease_volume (struct aud_block_info *block, int port, unsigned int volume, unsigned int duration, enum MIXER_EASE_TYPE_T type);
int mixer_set_mute (struct aud_block_info *block, int port, bool mute);
int mixer_set_delay (struct aud_block_info* block, int port, int delay);
int mixer_set_mixing_mode (struct aud_block_info* block, enum msmixer_mixing_mode mode);
int mixer_set_limiter (struct aud_block_info* block, bool limiter_enable);
int mixer_set_pcmren_metadata_type (struct aud_block_info *block, unsigned int metadata_type);
int mixer_set_pcmren_drc_mode (struct aud_block_info* block, unsigned int drc_mode);
int mixer_set_pcmren_downmix_mode (struct aud_block_info* block, unsigned int downmix_mode);
int mixer_set_bypass_fader (struct aud_block_info *block, int port, bool onOff);
#if (MS12_VER >= 26)
int mixer_set_encoder_connection (struct aud_block_info *block, bool connected, bool is_mat_enc);
int mixer_set_atmos_locking_mode (struct aud_block_info *block, bool atmos_lock_mode);
int mixer_set_sp50 (struct aud_block_info *block, bool set_sp50);
#endif
void mixer_initializer (void);


#endif /* _MIXER_H_ */
