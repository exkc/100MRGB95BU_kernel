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


#ifndef _AAPIL_H_
#define _AAPIL_H_

#include "aud_kapi.h"
#include "aud_kapi_decoder.h"
#include "aud_kapi_renderer.h"
#include "aud_kapi_debug.h"

enum md_clock_type {
    MD_CLK_TYPE_UNKNOWN      =   0x0,        /**< initial value. */
    MD_CLK_TYPE_PCR_M        =   0x1,        /**< main PCR. */
    MD_CLK_TYPE_PCR_A        =   0x2,        /**< associate PCR. */
    MD_CLK_TYPE_NO_PCR       =   0x11,       /**< no PCR. */
    MD_CLK_TYPE_GSTC         =   0x100,      /**< global STC 0. */
    MD_CLK_TYPE_GSTC_1       =   0x101,      /**< global STC 1. */
    MD_CLK_TYPE_MASTER       =   0x200,      /**< audio master. */
};

union audio_dbg_ioctl_args
{
    unsigned int index;

    struct adbg_open_block open_block;
    struct adbg_ren_param ren_param;
};

struct adebug_info_t {
    struct aud_block_info *block_info;

    unsigned int index;
    bool is_created;
} ;

int adecoder_open (int index);
int adecoder_close (int index);
int adecoder_start (int index);
int adecoder_stop (int index);
int adecoder_codec (int index, enum audio_decoder_codec codec);
int adecoder_codec_param_user (int index, struct adec_codec_param *param);
int adecoder_get_uid (int index, unsigned int *uid);
int adecoder_get_decoded_info (int index, struct decoded_info *info);
int adecoder_set_input (int index, enum audio_decoder_input input);
int adecoder_get_input (int index, unsigned int *input);
int adecoder_set_mpegh_ui_param (int index, struct adec_mpegh_ui_param *ui_param);
int adecoder_get_mpegh_ui_param (int index, struct adec_mpegh_ui_param *ui_param);
int adecoder_set_output_mode (int index, unsigned int output_mode);
int adecoder_set_basetime (int index, unsigned long long basetime);
int adecoder_set_presentation_group_index (int index, unsigned int pres_group_index);
int adecoder_set_dialog_enhancement_gain (int index, unsigned int gain);
int adecoder_get_dialog_enhancement_gain (int index, unsigned int *gain);
int adecoder_get_dialog_enhancement_limit (int index, unsigned int *limit);
int adecoder_set_default_prl (int index, unsigned int default_prl);
int adecoder_set_gap_info (int index, struct gap_info *gap_info);
#ifdef SUPPORT_DTSX
int adecoder_get_dts_supported (int index, bool *is_supported);
int adecoder_get_dts_bitstream_passthrough (int index, bool *bitstream_passthrough);
#endif
int adecoder_set_dolby_drc_mode (int index, unsigned int drc_mode);
int adecoder_set_aac_format_type (int index, unsigned int format_type);
int adecoder_set_proc_id (int index, unsigned int proc_id);
int adecoder_set_normal_closed (int index);
int adecoder_set_downmix (int index, bool enable);
int adecoder_set_sound_system (int index, unsigned int sound_system);
#ifdef SUPPORT_MUSIC_MODE
int adecoder_set_music_mode (int index, bool music_mode);
#endif

int aren_open (int index);
int aren_close (int index);
int aren_get_uid (int index, unsigned int *uid, bool is_bypass);
int aren_get_tail_uid (int index, unsigned int *uid, bool is_bypass);
int aren_set_clock_type (int index, enum md_clock_type clock_type);
int aren_enable_lipsync (int index, bool on);
int aren_set_basetime (int index, unsigned int clock_base, unsigned int stream_base);
int aren_set_lipsync_param (int index, unsigned int lower_bound, unsigned int upper_bound, unsigned int offset, unsigned int freerun_lbound, unsigned int freerun_ubound);
int aren_set_speed (int index, unsigned int speed);
int aren_set_mute(int index, unsigned int mute);
int aren_set_ease_volume (int index, aren_ease_volume_t easevolume);
int aren_get_ease_volume (int index, unsigned int *volume);
int aren_set_gap_info (int index, aren_gap_info_t gap_info );
#if 0
int aren_set_mixer_acmod (int index, unsigned int acmod);
#endif
int aren_add_queue (int index);
int aren_get_rendered_status (int index, aren_rendered_status_t *status);
int aren_get_rts_queue_info (int index, aren_rts_queue_info_t *info);
int aren_add_rts(int index);
int aren_set_rts_param (int index, aren_rts_param_t rts_param);
int aren_set_jp4k (int index, bool is_jp4k);
int aren_start (int index);
int aren_stop (int index);
int aren_set_pcm_info (int index, aren_pcm_info_t pcm_info);
int aren_set_bypass_fader( int index, bool game_mode);
int aren_get_queue_info (int index, aren_queue_info_t * info);
int aren_get_vdec_current_pts (int index, aren_vdec_current_pts_t * pts);
int aren_set_queue_max_length( int index, unsigned int queue_max_length);
int aren_set_proc_id (int index, unsigned int proc_id);
int aren_set_normal_closed (int index);
int aren_set_vsp_mode (int index);
int aren_set_msgpid_to_signal (int index, aren_msgpid_to_signal_t msgpid);
int aren_send_msg_signal(int index);

struct adebug_info_t *adebug_open (void);
int adebug_close (struct adebug_info_t *adebug_info);
long adebug_ioctl (struct adebug_info_t *info, unsigned int cmd, union audio_dbg_ioctl_args *args);

#endif /* _AAPIL_H_ */
