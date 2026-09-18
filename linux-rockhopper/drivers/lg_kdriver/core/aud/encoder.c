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

/** @file
 * @ingroup encoder
 *
 * @brief
 * Encoder block API Implementation for audio kernel driver
 *
 * @author      Youngwoo Jin ( youngwoo.jin@lge.com )
 * @version     1.0
 * @date        2021.02.17
 *
 * @details
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/slab.h>

#include "log.h"
#include "kaimc.h"

#include "block.h"
#include "block_manager.h"
#include "imc/cmd/module_cmd_ddpenc.h"
#include "module/adec_module_list.h"
#include "encoder.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
/// @brief Print log message for trace level
#define trace(fmt,args...)      logm_trace (aencoder, fmt, ##args)
/// @brief Print log message for debug level
#define debug(fmt,args...)      logm_debug (aencoder, fmt, ##args)
/// @brief Print log message for info level
#define info(fmt,args...)       logm_info (aencoder, fmt, ##args)
/// @brief Print log message for noti level
#define noti(fmt,args...)       logm_noti (aencoder, fmt, ##args)
/// @brief Print log message for warning level
#define warn(fmt,args...)       logm_warning (aencoder, fmt, ##args)
/// @brief Print log message for error level
#define error(fmt,args...)      logm_error (aencoder, fmt, ##args)

#define AUD_DEC_LOCK()		    mutex_lock(&_enc_lock)
#define AUD_DEC_UNLOCK()	    mutex_unlock(&_enc_lock)

#define set_property(_prop, _value) ({                      \
    if (_prop == NULL) {                                    \
        _prop = kmalloc (sizeof (*(_prop)), GFP_KERNEL);    \
        if (_prop == NULL) return -1;                       \
    }                                                       \
    *(_prop) = _value;                                      \
})

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
/**
 * AUDIO Encoder Information.
 */
struct aud_encoder_info
{
    struct aud_block_info parent;

    unsigned int proc_id;

    unsigned int uid_gain;
    unsigned int uid_enc;

#ifdef SUPPORT_DTSX
    int dts_enc_mode;           /* encoder mode => DTS Legacy CA (1), DTS-HD MA (2), DTS:X-P1 (3), DTS:X-P2 (4) */
#endif

    // 상태 변수들
    enum output_codec_t *codec;
    int *acmod;
    int *gain;
    int *channel;
    bool *atmos_on;
    bool *atmos_lock_mode;
    bool *ch_lock_mode;
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
logm_define (aencoder, log_level_noti);

//TODO: wrapper 적용 안했으니 ddp/mat encoder instance 는 1개만 만들어져야 함
static DEFINE_MUTEX (_enc_lock);

/*==============================================================================
    Implementation Group
==============================================================================*/

/**
 * create decoder block
 *
 * @param block [in] context of this block
 * @return 0
*/
static int encoder_create (struct aud_block_info *block)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;
    int preferred_proc = bm_get_preffered_processor (block);

    noti ("create encoder [DSP%d]\n", preferred_proc - ADEC_CORE_DSP0);

    block->pipeline = apipeline_new2 (preferred_proc, "encoder");
    block->isOpened = true;

    encoder->codec = NULL;
    encoder->acmod = NULL;
    encoder->gain = NULL;
    encoder->channel = NULL;
    encoder->atmos_on = NULL;
    encoder->atmos_lock_mode = NULL;
    encoder->ch_lock_mode = NULL;
#ifdef SUPPORT_DTSX
    encoder->dts_enc_mode = AUD_ENCODER_DTSX_DEFAULT_ENC_MODE;
#endif

    return 0;
}

/**
 * destroy encoder block
 *
 * @param block [in] context of this block
 * @return void
 * @see aud_encoder_info
*/
static void encoder_destroy (struct aud_block_info *block)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;

    noti ("called\n");

    if (block == NULL)
    {
        error ("encoder_info is NULL!!\n");
        goto exit;
    }

    if (block->isOpened == false)
    {
        error ("encoder is already closed. \n");
        goto exit;
    }

    if (block->pipeline)
    {
        apipeline_del (block->pipeline);
    }

    block->isOpened = false;

    if (encoder->codec)
    {
        kfree (encoder->codec);
    }

    if (encoder->acmod)
    {
        kfree (encoder->acmod);
    }

    if (encoder->gain)
    {
        kfree (encoder->gain);
    }

    if (encoder->channel)
    {
        kfree (encoder->channel);
    }

    if (encoder->atmos_on)
    {
        kfree (encoder->atmos_on);
    }

    if (encoder->atmos_lock_mode)
    {
        kfree (encoder->atmos_lock_mode);
    }

    if (encoder->ch_lock_mode)
    {
        kfree (encoder->ch_lock_mode);
    }

  exit:
    return;
}

static int encoder_suspend (struct aud_block_info *block)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;

    if (block->pipeline)
    {
        apipeline_del (block->pipeline);
    }

    block->pipeline = NULL;

    encoder->uid_enc = 0;
    encoder->uid_gain = 0;

    return 0;
}

static int encoder_resume (struct aud_block_info *block)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;
    int preferred_proc = bm_get_preffered_processor (block);

    block->pipeline = apipeline_new2 (preferred_proc, "encoder");

    if (encoder->codec && encoder->channel)
    {
        if (aud_encoder_set_codec (block, *encoder->codec, *encoder->channel) != 0)
        {
            return -1;
        }
    }

    if (encoder->acmod)
    {
        if (aud_encoder_set_acmod (block, *encoder->acmod) != 0)
        {
            return -1;
        }
    }

    if (encoder->gain)
    {
        if (aud_encoder_set_pre_gain (block, *encoder->gain) != 0)
        {
            return -1;
        }
    }

    if (encoder->atmos_on)
    {
        if (aud_encoder_set_atmos_on (block, *encoder->atmos_on) != 0)
        {
            return -1;
        }
    }

    if (encoder->atmos_lock_mode)
    {
        if (aud_encoder_set_atmos_locking_mode (block, *encoder->atmos_lock_mode) != 0)
        {
            return -1;
        }
    }

    if (encoder->ch_lock_mode)
    {
        if (aud_encoder_set_ch_lock_mode (block, *encoder->ch_lock_mode) != 0)
        {
            return -1;
        }
    }

    return 0;
}


/**
 * create encoder module based on codec info
 *
 * @param block [in] context of this block
 * @param codec [in] codec info
 * @return void
 * @see aud_encoder_info
*/
int aud_encoder_set_codec (struct aud_block_info *block, enum output_codec_t codec, int channel)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;

    info ("set codec %d", codec);

    set_property (encoder->codec, codec);
    set_property (encoder->channel, channel);

    if (!encoder->uid_enc)
    {
        encoder->uid_enc = apipeline_appendf (block->pipeline, "encoderbin");
    }

    switch (codec)
    {
        case OUTPUT_CODEC_AC3:
            aimc_set_property (encoder->uid_enc, "codec=ac3");
            break;
        case OUTPUT_CODEC_EAC3:
            aimc_set_property (encoder->uid_enc, "codec=eac3");
            break;
        case OUTPUT_CODEC_AAC:
            if (channel == 2)
            {
                if (!encoder->uid_gain)
                {
                    encoder->uid_gain = apipeline_prependf (block->pipeline, "gain");
                    apipeline_prependf (block->pipeline, "queue");
                }
                aimc_set_property (encoder->uid_enc, "codec=aac");
            }
            else
                aimc_set_property (encoder->uid_enc, "codec=aacmch");
            break;
        case OUTPUT_CODEC_MAT:
            aimc_set_property (encoder->uid_enc, "codec=mat");
            break;
#ifdef SUPPORT_DTSX
        case OUTPUT_CODEC_DTS:
            aimc_set_property (encoder->uid_enc, "codec=dts_ca");
            break;
        case OUTPUT_CODEC_DTS_HD_MA:
            aimc_set_property (encoder->uid_enc, "codec=dts_ma");
            break;
        case OUTPUT_CODEC_DTSX_P1:
            aimc_set_property (encoder->uid_enc, "codec=dtsx_p1");
            break;
#endif
        default:
            error ("invalid codec %d\n", codec);
            break;
    }

    return 0;
}

int aud_encoder_set_acmod (struct aud_block_info *block, int acmod)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;

    set_property (encoder->acmod, acmod);
    aimc_set_property (encoder->uid_enc, "i-ch-mode=%d", acmod);

    return 0;
}

int aud_encoder_set_pre_gain (struct aud_block_info *block, int gain)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;

    set_property (encoder->gain, gain);
    aimc_set_property (encoder->uid_gain, "gain=%d\\mute-input=false\\mute-output=false", gain);

    return 0;
}

int aud_encoder_set_atmos_on (struct aud_block_info *block, bool atmos_on)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;
    enum output_codec_t codec;

    set_property (encoder->atmos_on, atmos_on);

    if (encoder->codec == NULL)
    {
        return -1;
    }

    codec = *encoder->codec;

    if (codec == OUTPUT_CODEC_EAC3)
        aimc_set_property (encoder->uid_enc, "atmos-on=%d", atmos_on);

    info ("codec : %d atmos_on : %d\n", codec, atmos_on);
    return 0;
}

int aud_encoder_set_atmos_locking_mode (struct aud_block_info *block, bool atmos_lock_mode)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;
    enum output_codec_t codec;

    set_property (encoder->atmos_lock_mode, atmos_lock_mode);

    if (encoder->codec == NULL)
    {
        return -1;
    }

    codec = *encoder->codec;

    if (codec == OUTPUT_CODEC_EAC3 || codec == OUTPUT_CODEC_MAT)
        aimc_set_property (encoder->uid_enc, "atmos-lock=%d", atmos_lock_mode);

    info ("codec : %d atmos_lock_mode : %d\n", codec, atmos_lock_mode);
    return 0;
}

int aud_encoder_set_ch_lock_mode (struct aud_block_info *block, bool ch_lock_mode)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;
    enum output_codec_t codec;

    set_property (encoder->ch_lock_mode, ch_lock_mode);

    if (encoder->codec == NULL)
    {
        return -1;
    }

    codec = *encoder->codec;

    if (codec == OUTPUT_CODEC_EAC3 || codec == OUTPUT_CODEC_AC3 || codec == OUTPUT_CODEC_MAT)
        aimc_set_property (encoder->uid_enc, "channel-lock=%d", ch_lock_mode);

    info ("codec : %d ch_lock_mode : %d\n", codec, ch_lock_mode);
    return 0;
}

#ifdef SUPPORT_DTSX
int aud_encoder_set_dtsx_enc_mode (struct aud_block_info *block, int enc_mode)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;

    if (encoder == NULL)
        return -1;

    encoder->dts_enc_mode = enc_mode;

    info ("enc_mode : %d\n", enc_mode);
    return 0;
}

int aud_encoder_get_dtsx_enc_mode (struct aud_block_info *block)
{
    struct aud_encoder_info *encoder = (struct aud_encoder_info *) block;

    if (encoder == NULL)
        return AUD_ENCODER_DTSX_DEFAULT_ENC_MODE;

    info ("GET enc_mode : %d\n", encoder->dts_enc_mode);

    return encoder->dts_enc_mode;
}
#endif

static struct audio_block_impl block_impl = {
    .block_info_size = sizeof (struct aud_encoder_info),
    .block_type = "encoder",
    .preffered_processor = ADEC_CORE_DSP1,
    .constructor = encoder_create,
    .destructor = encoder_destroy,
    .suspend = encoder_suspend,
    .resume = encoder_resume,
};

void aud_encoder_initializer (void)
{
    bm_block_registry (&block_impl);
}
