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
 * @ingroup Renderer
 *
 *  driver interface header for audio renderer
 *
 *  @author Jihoon Lee (gaius.lee@lge.com)
 *  @version    0.1
 *  @date       2020.06.30
 *
 *  @addtogroup Renderer
 *  @{
 *  @}
 */

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "block.h"

/**
 * audio renderer event
 */
enum audio_renderer_event {
    AUDIO_RENDERER_EVENT_MASTER_INFO,
    AUDIO_RENDERER_EVENT_MAX,
};

/**
 * AUDIO Renderer Clock Type Index.
 */
enum RENDERER_CLK_TYPE {
    RENDERER_CLK_TYPE_PCR_M        =   0x1,        ///< main PCR.
    RENDERER_CLK_TYPE_PCR_A        =   0x2,        ///< associate PCR.
    RENDERER_CLK_TYPE_NO_PCR       =   0x11,       ///< no PCR.
    RENDERER_CLK_TYPE_GSTC         =   0x100,      ///< global STC 0.
    RENDERER_CLK_TYPE_GSTC_1       =   0x101,      ///< global STC 1.
    RENDERER_CLK_TYPE_MASTER       =   0x200,      ///< audio master.
};

/**
 * Endian of PCM.
 */
enum renderer_endian_t {
    renderer_endian_le = 0,            ///< little endian
    renderer_endian_be = 1,            ///< big endian
};

/**
 * Signed of PCM.
 */
enum renderer_sign_t {
    renderer_sign_signed = 0,             ///< signed PCM
    renderer_sign_unsigned = 1,           ///< unsigned PCM
};

/**
 * PCM Format Type.
 */
struct renderer_pcm_format {
    bool set_default;                   ///< set default value, ignore variables..
    unsigned int sample_rate;           ///< The Sampling Rate of PCM
    unsigned int channel;               ///< The number of channnel of PCM
    unsigned int bit_per_sample;        ///< The bit per sample of PCM
    enum renderer_endian_t endian;      ///< The endian of PCM(0 is little, 1 is big)
    enum renderer_sign_t sign;          ///< The signed of PCM(0 is signed, 1 is unsigned)
} ;

/*
* set gap info to lipsync
*
* @param renderer [in] pointer of renderer info
* @param [start_pts] unsigned long long
* @param [end_pts] unsigned long long

* @return 0 : OK, other : NOT_OK
* @see aud_renderer_info
*/
int renderer_set_gap_info (struct aud_block_info *block, unsigned int start_pts, unsigned int end_pts);

/*
* set endian/sign pcm format to pcmcvt
*
* @param renderer [in] pointer of renderer info
* @param [endian] endian pcm format, see @renderer_pcm_format
* @param [sign] sign pcm format, see @renderer_pcm_format

* @return 0 : OK, other : NOT_OK
* @see aud_renderer_info
*/
int renderer_set_endian_sign( struct aud_block_info *block,  enum renderer_endian_t endian, enum renderer_sign_t sign );

/*
* set input/output pcm format to pcmcvt
*
* @param renderer [in] pointer of renderer info
* @param [in] input pcm format, see @renderer_pcm_format
* @param [out] output pcm format, see @renderer_pcm_format

* @return 0 : OK, other : NOT_OK
* @see aud_renderer_info
*/
int renderer_set_pcm_format (struct aud_block_info *block, struct renderer_pcm_format in, struct renderer_pcm_format out);

/**
 * add rts module into renderer
 *
 * renderer make pipeline for bypass ( ES & PCM )
 *
 * @param renderer [in] pointer of renderer info
 * @return 0 : OK, other : NOT_OK
 * @see aud_renderer_info
*/
int renderer_add_rts (struct aud_block_info *block);

/**
 * add queue module into renderer
 *
 * @param block [in] pointer of renderer block
 * @param forced[in] add queue forcely
 * @return 0 : OK, other : NOT_OK
 * @see aud_renderer_info
*/
int renderer_add_queue (struct aud_block_info *block, bool forced);

/**
 * set parameter to renderer
 *
 * renderer_set_param(renderer, "gain=%d", 3);
 *
 * @param renderer [in] pointer of renderer info
 * @param pStrParam [in] formatted input
 * @return 0 : OK, other : NOT_OK
 * @see aud_renderer_info
*/
int renderer_set_param (struct aud_block_info* block, char *pStrParam, ...);

/**
 * get parameter from renderer
 *
 * renderer_get_param(renderer, "current_gain", &val);
 *
 * @param renderer [in] pointer of renderer info
 * @param pStrParam [in] formatted input
 * @param val [out] variable to get value
 * @return 0 : OK, other : NOT_OK
 * @see aud_renderer_info
*/
int renderer_get_param (struct aud_block_info *block, char *pStrParam, int *val);
void renderer_initializer (void);

int renderer_set_rts_out_freq (struct aud_block_info *block, unsigned int fast_freq,
    unsigned int normal_freq, unsigned int slow_freq);
int renderer_set_rts_skipping (struct aud_block_info *block, unsigned int skipping_recovery,
    unsigned int skipping_threshold);
int renderer_set_rts_threshold (struct aud_block_info *block, unsigned int upper_th,
    unsigned int lower_th, unsigned int recover_upper, unsigned int recover_lower);
int renderer_set_rts_opmode (struct aud_block_info *block, unsigned int opmode);
int renderer_set_rts_port_multiplier (struct aud_block_info *block, unsigned int ref_port, unsigned int numerator, unsigned int denominator);
int renderer_set_rts_start (struct aud_block_info *block);
void renderer_change_output (void);
int renderer_set_jp4k (struct aud_block_info *block, bool is_jp4k);
bool renderer_get_jp4k (struct aud_block_info *block);
bool renderer_get_pcm_bypass (struct aud_block_info * block);
int renderer_get_uid_pcm_bypass_head (struct aud_block_info * block);
int renderer_get_uid_bypass_tail (struct aud_block_info *block);
int renderer_get_uid_es_bypass_head (struct aud_block_info *block);
int renderer_set_pcm_bypass_rts_out_channels (struct aud_block_info * block, unsigned int channels);
int renderer_lipsync_set_idle (struct aud_block_info *block);
int renderer_lipsync_clear_idle (struct aud_block_info *block);
int renderer_lipsync_set_idle_time (struct aud_block_info *block, unsigned int msec);
void renderer_set_basetime_ipc (unsigned int index, unsigned int clock_base_time,
    unsigned int stream_base_time, bool is_set, bool is_all_set);

int renderer_master_info_cb (void *param, int cb_param_len, void *cb_param);
int renderer_register_event (struct aud_block_info *block, enum audio_renderer_event event, int (*cb_func) (void *, int, void *), int repeat);
int renderer_unregister_event (struct aud_block_info *block, enum audio_renderer_event event);
#endif /* _RENDERER_H_ */
