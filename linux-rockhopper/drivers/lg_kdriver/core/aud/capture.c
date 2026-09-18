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
 *  @file capture.c
 *  @addtogroup capture
 */

#include "log.h"
#include "kaimc.h"

#include "block.h"
#include "block_manager.h"
#include "capture.h"

logm_define (capture, log_level_noti);
#define trace(fmt,args...)	logm_trace(capture,fmt,##args)
#define debug(fmt,args...)	logm_debug(capture,fmt,##args)
#define info(fmt,args...)	logm_info(capture,fmt,##args)
#define noti(fmt,args...)	logm_noti(capture,fmt,##args)
#define error(fmt,args...)	logm_error(capture,fmt,##args)

/**
 * AUDIO Encoder Information.
 */
struct aud_capture_info
{
    struct aud_block_info parent;

    unsigned int uid_pcmcvt;
    unsigned int uid_capture;

    // 상태 변수들
    unsigned int gain;
    unsigned int sampling_freq;

    int peer_proc;

    bool mute;
    bool suspended;
};

/**
 * create decoder block
 *
 * @param block [in] context of this block
 * @return 0
*/
static int capture_create (struct aud_block_info *block)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;
    int preferred_proc = bm_get_preffered_processor (block);

    noti ("create capture\n");

    block->pipeline = apipeline_new2 (preferred_proc, "capture");
    capture->uid_capture = apipeline_appendf (block->pipeline, "capture");
    capture->peer_proc = preferred_proc;
    block->isOpened = true;
    return 0;
}

/**
 * destroy capture block
 *
 * @param block [in] context of this block
 * @return void
 * @see aud_capture_info
*/
static void capture_destroy (struct aud_block_info *block)
{
    noti ("called\n");

    if (block == NULL)
    {
        error ("capture_info is NULL!!\n");
        goto exit;
    }

    if (block->isOpened == false)
    {
        error ("capture is already closed. \n");
        goto exit;
    }


    if (block->pipeline)
        apipeline_del (block->pipeline);
    block->isOpened = false;

  exit:
    return;
}

static int capture_suspend (struct aud_block_info *block)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (block->pipeline)
        apipeline_del (block->pipeline);

    block->pipeline = NULL;

    capture->suspended = true;

    noti ("suspend capture\n");

    return 0;
}

static int capture_resume (struct aud_block_info *block)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    block->pipeline = apipeline_new2 (capture->peer_proc, "capture");

    capture->uid_capture = apipeline_appendf (block->pipeline, "capture");
    block->isOpened = true;

    capture->uid_pcmcvt = apipeline_prependf (block->pipeline, "pcmcvt");
    aimc_set_property (capture->uid_pcmcvt,
        "out-bit-per-sample=32\\in-sampling-rate=48000\\in-channels=2\\in-bit-per-sample=32\\out-sampling-rate=48000");

    aud_capture_set_sampling_freq (block, capture->sampling_freq);
    aud_capture_set_gain (block, capture->gain);
    capture->suspended = false;

    noti ("resume capture\n");

    return 0;
}

static struct audio_block_impl block_impl = {
    .block_info_size = sizeof (struct aud_capture_info),
    .block_type = "capture",
    .constructor = capture_create,
    .destructor = capture_destroy,
    .suspend = capture_suspend,
    .resume = capture_resume,
};

void aud_capture_initializer (void)
{
    bm_block_registry (&block_impl);
}

int aud_capture_set_gain (struct aud_block_info *block, unsigned int gain)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    capture->gain = gain;
    if (capture->mute == false)
    {
        if (capture->uid_pcmcvt)
            aimc_set_property (capture->uid_pcmcvt, "gain=%d", gain);
    }

    return 0;
}

int aud_capture_set_sampling_freq (struct aud_block_info *block, unsigned int sampling_freq)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    capture->sampling_freq = sampling_freq;
    if (capture->uid_pcmcvt)
        aimc_set_property (capture->uid_pcmcvt, "out-sampling-rate=%d", sampling_freq);

    return 0;
}

unsigned int aud_capture_get_sampling_freq (struct aud_block_info *block)
{
    int sampling_freq = 0;
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_pcmcvt)
        aimc_get_property (capture->uid_pcmcvt, "out-sampling-rate", &sampling_freq);

    return sampling_freq;
}

unsigned int aud_capture_get_out_channels (struct aud_block_info *block)
{
    int out_channels = 0;
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_pcmcvt)
        aimc_get_property (capture->uid_pcmcvt, "out-channels", &out_channels);

    return out_channels;
}

int aud_capture_set_out_bps (struct aud_block_info *block, unsigned int bps)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_pcmcvt)
        aimc_set_property (capture->uid_pcmcvt, "out-bit-per-sample=%d", bps);

    return 0;
}

int aud_capture_set_out_channel (struct aud_block_info *block, unsigned int out_channel)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_pcmcvt)
        aimc_set_property (capture->uid_pcmcvt, "out-channels=%d", out_channel);

    return 0;
}

int aud_capture_set_in_channel (struct aud_block_info *block, unsigned int in_channel)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_pcmcvt)
        aimc_set_property (capture->uid_pcmcvt, "in-channels=%d", in_channel);

    return 0;
}

int aud_capture_set_generate_lfe (struct aud_block_info *block, bool generate_lfe)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_pcmcvt)
        aimc_set_property (capture->uid_pcmcvt, "generate-lfe=%d", generate_lfe);

    return 0;
}

int aud_capture_set_out_acmod (struct aud_block_info *block, unsigned int out_acmod)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_pcmcvt)
        aimc_set_property (capture->uid_pcmcvt, "acmod=%d", out_acmod);

    return 0;
}

int aud_capture_set_es (struct aud_block_info *block, bool es)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (!es)
    {
        noti ("pcm capture mode. pcmcvt, gain enabled\n");

        capture->uid_pcmcvt = apipeline_prependf (block->pipeline, "pcmcvt");
        aimc_set_property (capture->uid_pcmcvt,
            "out-bit-per-sample=32\\in-sampling-rate=48000\\in-channels=2\\in-bit-per-sample=32\\out-sampling-rate=48000\\gain=%d",
            capture->gain);
    }

    return 0;
}

int aud_capture_set_dafc_mode (struct aud_block_info *block, bool onOff)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    noti ("dafc capture mode : %d\n", onOff);

    if (capture->uid_pcmcvt)
        aimc_set_property (capture->uid_pcmcvt, "available=%d", onOff);

    return 0;
}

int aud_capture_set_aenc_header (struct aud_block_info *block, bool use_aenc_header)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_capture)
        aimc_set_property (capture->uid_capture, "use-aenc-header=%d", use_aenc_header);

    return 0;
}

int aud_capture_set_disable (struct aud_block_info *block, bool disable)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_capture)
        aimc_set_property (capture->uid_capture, "mute-output=%d", disable);

    return 0;
}

int aud_capture_set_mute (struct aud_block_info *block, bool mute)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    capture->mute = mute;
    if (capture->uid_pcmcvt)
        aimc_set_property (capture->uid_pcmcvt, "gain=%d", mute ? 0 : capture->gain);

    return 0;

}

int aud_capture_set_read_pointer (struct aud_block_info *block, unsigned int rd_ptr)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_capture)
        aimc_set_property (capture->uid_capture, "rdOffset=%d", rd_ptr);

    return 0;
}

int aud_capture_get_out_samples (struct aud_block_info *block)
{
    int out_samples = 0;
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_pcmcvt)
        aimc_get_property (capture->uid_pcmcvt, "out-samples", &out_samples);

    return out_samples;
}


int aud_capture_set_out_samples (struct aud_block_info *block, unsigned int out_samples)
{
    struct aud_capture_info *capture = (struct aud_capture_info *) block;

    if (capture->uid_pcmcvt)
        aimc_set_property (capture->uid_pcmcvt, "out-samples=%d", out_samples);

    return 0;
}
