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

/** @file
 * @ingroup Decoder
 *
 *  driver interface header for audio renderer
 *
 *  @author Youngjun Jang (youngjun.jang@lge.com)
 *  @version    0.1
 *  @date       2020.06.30
 *
 *  @addtogroup Decoder
 *  @{
 *  @}
 */

#ifndef _DECODER_H_
#define _DECODER_H_

#include "block.h"
#include "aud_kapi_decoder.h"

void decoder_acquire_lock (void);
void decoder_release_lock (void);
int decoder_tp_es_exist_info_cb (void *param, int cb_param_len, void *cb_param);
int decoder_hdmi_pcm_format_info_cb (void *param, int cb_param_len, void *cb_param);
int decoder_decoded_info_cb (void *param, int cb_param_len, void *cb_param);
int decoder_mpegh_ui_param_info_cb (void *param, int cb_param_len, void *cb_param);
int decoder_module_id_changed_cb (void *param, int cb_param_len, void *cb_param);
int decoder_get_tp_buffer_status (struct aud_block_info *block, enum audio_decoder_input_tp input, unsigned int *max, unsigned int *free);
int decoder_get_tp_audio_pts (struct aud_block_info *block, int index, unsigned int *pts);
int decoder_get_decoded_info (struct aud_block_info *block, struct decoded_info *info);
int decoder_set_codec (struct aud_block_info* block, enum audio_decoder_codec codec);
enum audio_decoder_codec decoder_get_codec (struct aud_block_info *block);
int decoder_get_param (struct aud_block_info *block, char *name, int *val);
int decoder_set_param (struct aud_block_info* block, char *pStrParam, ...);
int decoder_set_input (struct aud_block_info* block, enum audio_decoder_input input);
enum audio_decoder_input decoder_get_input (struct aud_block_info *block);
int decoder_config_mpegh_ui_param (struct aud_block_info *block);
int decoder_set_mpegh_ui_param (struct aud_block_info* block, struct adec_mpegh_ui_param *ui_param);
int decoder_get_mpegh_ui_param (struct aud_block_info* block, struct adec_mpegh_ui_param *ui_param);
int decoder_register_event (struct aud_block_info *block, enum audio_decoder_event event, int (*cb_func) (void *, int, void *), int repeat);
int decoder_unregister_event (struct aud_block_info *block, enum audio_decoder_event event);
int decoder_connect (struct aud_block_info *block);
#ifdef SUPPORT_DTSX
int decoder_set_dtsx_bitstream_passthrough (struct aud_block_info *block, bool bitstream_passthrough);
#endif
int decoder_set_prio (struct aud_block_info *block);
int decoder_set_dolby_drc_mode (struct aud_block_info *block, enum audio_decoder_drc drc);
enum audio_decoder_drc decoder_get_dolby_drc_mode (struct aud_block_info *block);
bool decoder_is_created (struct aud_block_info *block);
#ifdef SUPPORT_SOUNDBAR
void decoder_stop (struct aud_block_info *block);
int decoder_get_already_opened_index (void);
#endif
void decoder_initializer (void);

#endif /* _DECODER_H_ */
