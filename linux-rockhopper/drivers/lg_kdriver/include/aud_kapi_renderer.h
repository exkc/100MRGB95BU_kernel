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


/** @file aud_kapi.h
 *
 *  @author     Jihoon Lee (gaius.lee@lge.com)
 *  @version    0.1
 *  @date       2020.09.28
 *  @note       The simple wrapper function for audio kernel module.
 *
 */

#ifndef _AUD_KAPI_RENDERER_H_
#define _AUD_KAPI_RENDERER_H_

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define AREN_IOC_MAGIC                       'R'

/*----------------------------------------------------------------------------------------
    IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define AREN_IOW_SET_INDEX                   _IOW(AREN_IOC_MAGIC, 1, int)
#define AREN_IOR_GET_UID                     _IOR(AREN_IOC_MAGIC, 2, unsigned int)
#define AREN_IOR_GET_BYPASS_UID              _IOR(AREN_IOC_MAGIC, 3, unsigned int)
#define AREN_IOR_GET_GSTC                    _IOR(AREN_IOC_MAGIC, 4, unsigned int)
#define AREN_IOW_SET_CLOCKTYPE               _IOW(AREN_IOC_MAGIC, 5, aud_clock_type_t)
#define AREN_IOW_SET_ENALBE_LIPSYNC          _IOW(AREN_IOC_MAGIC, 6, unsigned int)
#define AREN_IOW_SET_BASETIME                _IOW(AREN_IOC_MAGIC, 7, aren_base_time_t)
#define AREN_IOW_SET_LIPSYNC_PARAM           _IOW(AREN_IOC_MAGIC, 8, aren_lipsync_param_t)
#define AREN_IOW_SET_SPEED                   _IOW(AREN_IOC_MAGIC, 9, unsigned int)
#define AREN_IOW_SET_MUTE                    _IOW(AREN_IOC_MAGIC, 10, unsigned int)

#define AREN_IOW_SET_EASE_VOLUME             _IOW(AREN_IOC_MAGIC, 11, aren_ease_volume_t)
#define AREN_IOR_GET_EASE_VOLUME             _IOR(AREN_IOC_MAGIC, 12, unsigned int)
#define AREN_IOR_GET_STATUS                  _IOR(AREN_IOC_MAGIC, 13, unsigned int)
#define AREN_IOW_SET_GAP_INFO                _IOW(AREN_IOC_MAGIC, 14, aren_gap_info_t)
#define AREN_IOW_SET_MIXER_ACMOD             _IOW(AREN_IOC_MAGIC, 15, unsigned int)
#define AREN_IOR_GET_RENDERED_STATUS         _IOR(AREN_IOC_MAGIC, 16, aren_rendered_status_t)
#define AREN_IOR_GET_RTS_QUEUE_INFO          _IOR(AREN_IOC_MAGIC, 17, aren_rts_queue_info_t)
#define AREN_IOW_SET_RTS_PARAM               _IOW(AREN_IOC_MAGIC, 18, aren_rts_param_t)
#define AREN_IOW_ADD_RTS                     _IO(AREN_IOC_MAGIC, 19)
#define AREN_IOW_SET_JP4K_STREAM             _IOW(AREN_IOC_MAGIC, 20, bool)
#define AREN_IOW_CONNECT_ES_OUTPUT           _IO(AREN_IOC_MAGIC, 21)
#define AREN_IOW_DISCONNECT_ES_OUTPUT        _IO(AREN_IOC_MAGIC, 22)
#define AREN_IO_START                        _IO(AREN_IOC_MAGIC, 30)
#define AREN_IO_STOP                         _IO(AREN_IOC_MAGIC, 31)
#define AREN_IOW_SET_PCM_INFO                _IOW(AREN_IOC_MAGIC, 32, aren_pcm_info_t)
#define AREN_IO_ADD_QUEUE                    _IO(AREN_IOC_MAGIC, 33)
#define AREN_IOR_GET_TAIL_UID                _IOR(AREN_IOC_MAGIC, 34, unsigned int)
#define AREN_IOR_GET_BYPASS_TAIL_UID         _IOR(AREN_IOC_MAGIC, 35, unsigned int)
#define AREN_IOW_SET_BYPASS_FADER            _IOW(AREN_IOC_MAGIC, 36, bool)
#define AREN_IOR_GET_QUEUE_INFO              _IOR(AREN_IOC_MAGIC, 37, aren_queue_info_t)
#define AREN_IOR_GET_VDEC_CURRENT_PTS        _IOWR(AREN_IOC_MAGIC, 38, aren_vdec_current_pts_t)
#define AREN_IOW_SET_QUEUE_MAX_LENGTH        _IOW(AREN_IOC_MAGIC, 39, unsigned int)
#define AREN_IOW_SET_PROC_ID                 _IOW(AREN_IOC_MAGIC, 40, unsigned int)
#define AREN_IOW_SET_NORM_CLOSED             _IO(AREN_IOC_MAGIC, 41)
#define AREN_IOW_SET_VSP_MODE                _IO(AREN_IOC_MAGIC, 42)
#define AREN_IOW_SET_MSGPID_TO_SIGNAL        _IOW(AREN_IOC_MAGIC, 43, aren_msgpid_to_signal_t)



typedef enum aud_gain_duration_mode {
    AUD_GAIN_DURATION_MODE_LINEAR = 0,
    AUD_GAIN_DURATION_MODE_INCUBIC,
    AUD_GAIN_DURATION_MODE_OUTCUBIC,
} aud_gain_duration_mode_t;

/**
 * AUDIO Renderer Clock Basetime Parameter.
 */
typedef struct aren_base_time {
    unsigned int clock_base_time;      ///< clock base time.
    unsigned int stream_base_time;     ///< stream base time.
} aren_base_time_t;

/**
 * AUDIO Renderer Lipsync Parameter.
 */
typedef struct aren_lipsync_param {
    unsigned int lower_bound;            ///< lower bound. unit is miliseconds.
    unsigned int upper_bound;            ///< upper bound unit is miliseconds.
    unsigned int offset;                 ///< offset unit is miliseconds.
    unsigned int freerun_lbound;         ///< freerun lower bound. unit is miliseconds.
    unsigned int freerun_ubound;         ///< freerun upper bound. unit is miliseconds.
} aren_lipsync_param_t;

/**
 * AUDIO Renderer Volume Configuration.
 */
typedef struct {
    unsigned int volume;         ///< volume.
    unsigned int duration;       ///< duration. ms.
    aud_gain_duration_mode_t type;   ///< easeType.
} aren_ease_volume_t;

/**
 * Set Gap Infomation.
 */
typedef struct {
    unsigned int start_pts;
    unsigned int end_pts;
} aren_gap_info_t;

/**
 * AUDIO RENDERED Status from DSP.
*/
typedef struct {
    unsigned int                  max_mem_size;             ///< The Max size
    unsigned int                  free_mem_size;            ///< The Free size
    unsigned int                  max_aui_size;             ///< The Max AUI(Access Unit Index) size
    unsigned int                  free_aui_size;            ///< The free AUI(Access Unit Index) size
    unsigned int                  feeded_index;             ///< The Feeded Index
    unsigned int                  feeded_count;             ///< The Feeded Count
    unsigned int                  rendered_index;           ///< The Rendered Index
    unsigned long long            timestamp;                ///< The Rendered timestamp
    bool                          present_end;              ///< The status of Present End.
} aren_rendered_status_t;

/**
 * Setting of RTS module
 */
typedef struct {
    bool                              onoff;              ///< Enable/Disable RTS module

    unsigned int                      opmode;                 ///< operation mode. 0: Continuous, 1: Skipping, 2: Hybrid

    unsigned int                      upper_threshold;         ///< upper threashold of buffering (from NORMAL to FAST)
    unsigned int                      lower_threshold;         ///< lower threshold of buffering (from NORMAL to SLOW)
    unsigned int                      recover_upper;           ///< recover threshold of buffering (from FAST to NORMAL)
    unsigned int                      recover_lower;           ///< recover threshold of buffering (from SLOW to NORMAL)

    unsigned int                      skipping_threshold;      ///< skipping threshold of buffering (from NORMAL to SKIP)
    unsigned int                      recover_skipping;        ///< recover threshold of buffering (from SKIP to NORMAL)

    unsigned int                      fast_freq;               ///< frequency of FAST
    unsigned int                      normal_freq;             ///< frequency of NORMAL
    unsigned int                      slow_freq;               ///< frequency of SLOW

    unsigned int                      mix_fade_len;             ///< fade length of mixer
    unsigned int                      mix_wait_len;             ///< wait length of mixer (sample)

    unsigned int                      buffering_level;          ///< level of buffering threshold (ms)
} aren_rts_param_t;

/**
 * RTS Queue Info from DSP.
*/
typedef struct {
    unsigned int                queue_max;
    unsigned int                queued_byte;
} aren_rts_queue_info_t;

/**
 * PCM Infomation
 */
typedef struct {
    unsigned int sampling_rate;
    unsigned int channels;
    unsigned int bits_per_sample;
    unsigned int byte_align;
    unsigned int sign;
    unsigned int clock_x4;
    unsigned int pcm_bypass;    // google game (pcm multi channels)
    unsigned int pcm_multi_ch;  // netflix game (pcm multi channels)
} aren_pcm_info_t;


/**
 * Queue Info from DSP.
*/
typedef struct {
    unsigned int                queued_length;
    unsigned int                max_length;
} aren_queue_info_t;

/**
 * vdec_current_pts
*/
typedef struct {
    unsigned int                port;
    unsigned int                pts;
} aren_vdec_current_pts_t;

typedef struct {
    int                msgq_id;
    int                pid;
} aren_msgpid_to_signal_t;

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _AUD_KAPI_RENDERER_H_ */
