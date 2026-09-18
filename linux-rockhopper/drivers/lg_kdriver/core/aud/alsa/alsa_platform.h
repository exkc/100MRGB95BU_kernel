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



/** @file alsa_platform.h
 *
 *  alsa platform driver.
 *
 *  @author     Won Chang Shin(wonchang.shin@lge.com)
 *  @version    0.1
 *  @date       2013.03.20
 *
 *  @{
 */

#ifndef _LG115x_ALSA_PLATFORM_H_
#define _lg115x_ALSA_PLATFORM_H_

#include <linux/workqueue.h>
#include <linux/mutex.h>

#define PLATFORM_NAME   "lg115x-platform"
#define DAI_NAME        "lg115x-dai"

#define ALSA_DEVICE_NUM         10
#define ALSA_CAP_DEVICE_NUM     6
#define ALSA_DEV_TO_INDEX       DEV_DEC_NUM
#define ALSA_GET_INDEX(ALSA_DEV_ID) ((ALSA_DEV_ID) + ALSA_DEV_TO_INDEX)
#define ALSA_CAP_PCM_HW_NUM     ALSA_DEVICE_NUM
#define ALAS_CAP_ENC_HW_NUM     (ALSA_CAP_PCM_HW_NUM + 1)

//Define for ALSA Device Running Status
#define ALSA_DEVICE_STOP        0
#define ALSA_DEVICE_RUNNING     1

#define ADEC_DSP_MIX_VOLUME_GAIN_0DB    1024    //0x08000000
#define ADEC_DSP_MIX_VOLUME_GAIN_MUTE   0

#define ADEC_MIX_VOLUME_MAIN_30DB       0x9D    //157
#define ADEC_MIX_VOLUME_MAIN_0DB        0x00    //0
#define ADEC_MIX_VOLUME_FINE_15_16DB    0x0F    //15
#define ADEC_MIX_VOLUME_FINE_0DB        0x00    //0

#define LG115x_SUPPORT_CAPTURE_RATE    SNDRV_PCM_RATE_8000_384000

#define LG115x_SUPPORT_CAPTURE_FORMAT  (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_S32_BE)

#define LG115x_SUPPORT_PLAYBACK_RATE    (SNDRV_PCM_RATE_8000  | SNDRV_PCM_RATE_11025    \
                                        |SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050    \
                                        |SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100    \
                                        |SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_64000    \
                                        |SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000    \
                                        |SNDRV_PCM_RATE_176400| SNDRV_PCM_RATE_192000)

#ifdef SUPPORT_SOUNDBAR
#define LG115x_SUPPORT_PLAYBACK_FORMAT  (SNDRV_PCM_FMTBIT_S8      | SNDRV_PCM_FMTBIT_U8     \
                                        |SNDRV_PCM_FMTBIT_S16_LE  | SNDRV_PCM_FMTBIT_S16_BE \
                                        |SNDRV_PCM_FMTBIT_U16_LE  | SNDRV_PCM_FMTBIT_U16_BE \
                                        |SNDRV_PCM_FMTBIT_S24_LE  | SNDRV_PCM_FMTBIT_S24_BE \
                                        |SNDRV_PCM_FMTBIT_U24_LE  | SNDRV_PCM_FMTBIT_U24_BE \
                                        |SNDRV_PCM_FMTBIT_S32_LE  | SNDRV_PCM_FMTBIT_S32_BE \
                                        |SNDRV_PCM_FMTBIT_U32_LE  | SNDRV_PCM_FMTBIT_U32_BE \
                                        |SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE \
                                        |SNDRV_PCM_FMTBIT_U24_3LE | SNDRV_PCM_FMTBIT_U24_3BE \
                                        |SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S20_3BE \
                                        |SNDRV_PCM_FMTBIT_U20_3LE | SNDRV_PCM_FMTBIT_U20_3BE \
                                        |SNDRV_PCM_FMTBIT_S18_3LE | SNDRV_PCM_FMTBIT_S18_3BE \
                                        |SNDRV_PCM_FMTBIT_U18_3LE | SNDRV_PCM_FMTBIT_U18_3BE \
                                        |SNDRV_PCM_FMTBIT_FLOAT_LE)
#else
#define LG115x_SUPPORT_PLAYBACK_FORMAT  (SNDRV_PCM_FMTBIT_S8      | SNDRV_PCM_FMTBIT_U8     \
                                        |SNDRV_PCM_FMTBIT_S16_LE  | SNDRV_PCM_FMTBIT_S16_BE \
                                        |SNDRV_PCM_FMTBIT_U16_LE  | SNDRV_PCM_FMTBIT_U16_BE \
                                        |SNDRV_PCM_FMTBIT_S24_LE  | SNDRV_PCM_FMTBIT_S24_BE \
                                        |SNDRV_PCM_FMTBIT_U24_LE  | SNDRV_PCM_FMTBIT_U24_BE \
                                        |SNDRV_PCM_FMTBIT_S32_LE  | SNDRV_PCM_FMTBIT_S32_BE \
                                        |SNDRV_PCM_FMTBIT_U32_LE  | SNDRV_PCM_FMTBIT_U32_BE \
                                        |SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_U24_3LE\
                                        |SNDRV_PCM_FMTBIT_S24_3BE | SNDRV_PCM_FMTBIT_U24_3BE)
#endif

struct runtime_data{
    struct snd_pcm_substream *substream;
    spinlock_t lock;
    unsigned int running;
    struct aud_dev_info * alloc_dev_master;
    struct aud_decoder_info * decoder;
    struct aud_renderer_info * renderer;
    struct aud_capturer_info *capturer;
    struct aud_encoder_info *encoder;
    unsigned int write_ptr;
    unsigned int read_ptr;
    unsigned int render_is_connected;       // 0 : not connected, 1 : connected
    unsigned int capture_is_connected;       // 0 : not connected, 1 : connected
    unsigned int master_is_connected;
    unsigned int wake_up_is_called;
    unsigned int volume;                // 1024 : 0dB.
    unsigned int buffer_size_diff;
    unsigned int old_free_size;
    //LX_AUD_CODEC_T codec_type;
    unsigned int sampling_freq;
    unsigned int channels;
    unsigned int bits_per_sample;
    unsigned int sigend;
    unsigned int endian;
    unsigned int prev_read_ptr_byte;
    int fake_pointer;

    struct work_struct updated_work;
    struct mutex write_lock;
    // for debugging
    unsigned int bytes_per_sec;
    unsigned int write_bytes_total;
    unsigned int first_copy;
};

struct alsa_enc_info
{
    int dec_idx;
    int codec;
    int bitrate;
    unsigned int gain;
    int status;                 // 0:idle, 1:running
    unsigned long long pts;
};

enum alsa_cap_output
{
    CAP_OUTPUT_BT,
    CAP_OUTPUT_WISA,
    CAP_OUTPUT_SE_BT,
    CAP_OUTPUT_SE_BT_SUR,
    CAP_OUTPUT_MUSIC,
    CAP_OUTPUT_COMMON,
    CAP_OUTPUT_MAX,
};

struct alsa_capture_info
{
    struct aud_capturer_info *capturer;
    struct aud_encoder_info *encoder;
    struct aud_capturer_info *enc_capturer;
    struct alsa_enc_info enc_info;
    enum alsa_cap_output cap_output;
    unsigned int cap_gain[CAP_OUTPUT_MAX];
    unsigned int cap_mute[CAP_OUTPUT_MAX];
    unsigned int cap_out_channel[CAP_OUTPUT_MAX];
    unsigned int cap_out_freq[CAP_OUTPUT_MAX];
    bool cap_disable;
};

int ALSA_PLATFORM_DAI_Init(void);
void ALSA_PLATFORM_DAI_Cleanup(void);

int ALSA_PLATFORM_Init (void);
void ALSA_PLATFORM_Cleanup (void);

int ALSA_PLATFORM_PCM_Init(void);
void ALSA_PLATFORM_PCM_Cleanup(void);

int aplayback_init(void);
void aplayback_cleanup(void);

int acapture_init(void);
void acapture_cleanup(void);

#endif /* _lg115x_ALSA_PLATFORM_H_ */


