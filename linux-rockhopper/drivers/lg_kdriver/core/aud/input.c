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
 *  @file input.c
 *
 *  Audio driver implementation for audio input block.
 *  Input block manages TP, HDMI, ADC, SIF and MEMORY input.
 *
 *  @author	Jong-Sang Oh(jongsang.oh@lge.com)
 *  @version    0.1
 *  @date       2020/06/30
 *
 *  @addtogroup input
 *  @{
 */
#include <linux/slab.h>

#include "kaimc.h"
#include "log.h"
#include "block.h"
#include "block_manager.h"
#include "input.h"
#include "clock.h"
#include "hdmi_kapi.h"
#include "hal/hal_bc.h"
#include "aad_if.h"

#include "imc/adec_imc_cmd.h"
#include "imc/cmd/module_cmd_tp.h"
#include "imc/cmd/module_cmd_hdmi.h"
#include "imc/evt/module_evt_tp.h"
#include "imc/evt/module_evt_hdmi.h"
#include "common/adec_media_type.h"
#include "module/adec_module.h"

logm_define (aud_input, log_level_noti);
#define trace(fmt,args...)  logm_trace(aud_input,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_input,fmt,##args)
#define info(fmt,args...)   logm_info(aud_input,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_input,fmt,##args)
#define error(fmt,args...)  logm_error(aud_input,fmt,##args)

static DEFINE_MUTEX (_input_lock);

#define AUD_INPUT_LOCK()        mutex_lock(&_input_lock)
#define AUD_INPUT_UNLOCK()      mutex_unlock(&_input_lock)

#define TP_INPUT_QUEUE_SIZE             ( 64 * 1024)    // 64KB(ES buffer :  512KB, legacy : 256KB)
#define HDMI_HBR_INPUT_QUEUE_SIZE       (128 * 1024)    //128KB(ES buffer : 1024KB, legacy : 320KB)

#ifndef CHIP_TYPE_FPGA
#if defined (INCLUDE_KDRV_HDMI20)
#ifdef HAVE_HDMI21
extern int KDRV_HDMI21_HAL_Rx_GetAudioInfo (UINT8 port, LX_HDMI_AUDIO_INFO_T * pHdmiAudioInfo,
    int size);
extern int KDRV_HDMI21_HAL_Rx_Set_AudioMute (UINT8 port, LX_HDMI_MUTE_CTRL_T * pMuteCtrl, int size);
#else
extern int KDRV_HDMI20_HAL_Rx_GetAudioInfo (UINT8 port, LX_HDMI_AUDIO_INFO_T * pHdmiAudioInfo,
    int size);
extern int KDRV_HDMI20_HAL_Rx_Set_AudioMute (UINT8 port, LX_HDMI_MUTE_CTRL_T * pMuteCtrl, int size);
#endif
#endif
#endif

static int hdmi_get_audioinfo (UINT8 port, LX_HDMI_AUDIO_INFO_T * pHdmiAudioInfo, int size)
{
#ifndef CHIP_TYPE_FPGA
#if defined (INCLUDE_KDRV_HDMI20)
#ifdef HAVE_HDMI21
    return KDRV_HDMI21_HAL_Rx_GetAudioInfo (port, pHdmiAudioInfo, size);
#else
    return KDRV_HDMI20_HAL_Rx_GetAudioInfo (port, pHdmiAudioInfo, size);
#endif
#else
    return 0;
#endif
#else
    return 0;
#endif
}

static int hdmi_set_audiomute (UINT8 port, LX_HDMI_MUTE_CTRL_T * pMuteCtrl, int size)
{
#ifndef CHIP_TYPE_FPGA
#if defined (INCLUDE_KDRV_HDMI20)
#ifdef HAVE_HDMI21
    return KDRV_HDMI21_HAL_Rx_Set_AudioMute (port, pMuteCtrl, size);
#else
    return KDRV_HDMI20_HAL_Rx_Set_AudioMute (port, pMuteCtrl, size);
#endif
#else
    return 0;
#endif
#else
    return 0;
#endif
}

struct aud_input_event_info
{
    char *name;
    int id;
    input_callback_func cb_func;
    struct aud_block_info *cb_target_block;

    struct list_head list;
};

/**
 * Information of input.
 */
struct aud_input_info
{
    struct aud_block_info parent;

    struct apipeline *pipeline_queue;
#ifndef SUPPORT_SOUNDBAR
    struct apipeline *pipeline_bypass;
#endif

    int dec_index;

    enum input_type input;
    int index;
    unsigned int channel_num;
    unsigned int sampling_freq;
    unsigned int org_hdmi_freq;
    unsigned int org_hdmi_ch;
#ifdef SUPPORT_SOUNDBAR
    unsigned int org_hdmi_type;
    unsigned int i2s_port_count;
#endif

    int uid;
    int uid_queue;
#ifndef SUPPORT_SOUNDBAR
    int uid_queue_bypass;
#endif

    bool is_suspended;
    bool is_start;

    enum audio_decoder_codec tp_codec;
    bool clock_x4;
    enum audio_decoder_codec hdmi_codec;
    bool forced_pcm;
    bool data_drop;
    int output_port;

    bool drop;
    bool hdmi_multi_pcm_out;

    struct list_head list_event;
};

static const char *_input_name[INPUT_MAX] = {
    [INPUT_SIF] = "SIF",
    [INPUT_TP] = "TP",
    [INPUT_HDMI] = "HDMI",
    [INPUT_ADC] = "ADC",
#ifdef SUPPORT_SOUNDBAR
    [INPUT_I2S] = "I2S",
#endif
};

static void _input_set_stop_property (struct aud_input_info *input)
{
    aimc_set_property (input->uid, "drop-output-data=%d", true);
    aimc_set_property (input->uid, "drop=%d", true);
    aimc_set_property (input->uid, "start=%d", false);
    aimc_set_property (input->uid_queue, "set-flush=%d", true);

    if (input->input == INPUT_HDMI)
    {
#ifndef SUPPORT_SOUNDBAR
        aimc_set_property (input->uid_queue_bypass, "set-flush=%d", true);
#endif
        if (input->hdmi_codec == AUDIO_DECODER_CODEC_PCM)
            aimc_set_property (input->uid, "multi-pcm-out=%d", false);
    }
    return;
}

static void _input_set_start_property (struct aud_input_info *input)
{
    aimc_set_property (input->uid, "start=%d", true);
    aimc_set_property (input->uid, "drop-output-data=%d", input->drop);
    aimc_set_property (input->uid, "drop=%d", input->drop);
    return;
}

/**
 * get tp pdec error info. from tp module
 *
 * @param
 * @return
*/
int input_tp_pdec_error_info_cb (void *param, int cb_param_len, void *cb_param)
{
    struct aud_input_info *input = (struct aud_input_info *) cb_param;
    TpEvtPdecErrorParam *errorParam = (TpEvtPdecErrorParam *) param;

    if (cb_param_len != sizeof (TpEvtPdecErrorParam))
    {
        error ("Param Length Error[Expected:%zd][Input:%d]\n",
            sizeof (TpEvtPdecErrorParam), cb_param_len);
        return -1;
    }

    _input_set_stop_property (input);

    if (input->index == 0)
        aud_hal_bc_buffer_init ("bc-tp0");
    else
        aud_hal_bc_buffer_init ("bc-tp1");

    _input_set_start_property (input);

    noti ("PDEC Error Info(%d) : codec(%d) error(%d)\n", input->uid, errorParam->media_type,
        errorParam->error_type);
    return 0;
}

#ifdef SUPPORT_DTSX
/**
 * get hdmi dts format changed info. from hdmi module
 *
 * @param
 * @return
*/
int input_hdmi_dts_format_changed_cb (void *param, int cb_param_len, void *cb_param)
{
    struct aud_input_info *input = (struct aud_input_info *) cb_param;
    HdmiEvtDtsFormatChangedParam *errorParam = (HdmiEvtDtsFormatChangedParam *) param;

    if (cb_param_len != sizeof (HdmiEvtDtsFormatChangedParam))
    {
        error ("Param Length Error[Expected:%zd][Input:%d]\n",
            sizeof (HdmiEvtDtsFormatChangedParam), cb_param_len);
        return -1;
    }

    if (errorParam->format_changed)
    {
        _input_set_stop_property (input);

        _input_set_start_property (input);
    }

    noti ("HDMI Format Changed : changed(%d)\n", errorParam->format_changed);
    return 0;
}
#endif

static int input_set_clock (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;
    enum aud_clock_source clock_source = CLOCK_SOURCE_DTV0;

    switch (input->input)
    {
        case INPUT_TP:
            clock_source = (input->index == 0) ? CLOCK_SOURCE_DTV0 : CLOCK_SOURCE_DTV1;
            break;

        case INPUT_SIF:
            clock_source = CLOCK_SOURCE_ATV;
            break;

        case INPUT_HDMI:
            clock_source = CLOCK_SOURCE_HDMI;
            break;

        case INPUT_ADC:
            clock_source = CLOCK_SOURCE_ADC;
            break;

#ifdef SUPPORT_SOUNDBAR
        case INPUT_I2S:
            clock_source = CLOCK_SOURCE_I2S;
            break;
#endif

        default:
            clock_source = CLOCK_SOURCE_GSTC0;
            break;
    }

    if (aud_clock_enable_input (input->dec_index, clock_source, input->uid) != 0)
    {
        error ("no mem\n");
        return -1;
    }

    if (input->input == INPUT_TP && input->clock_x4 == true)
        aud_clock_update_input (input->dec_index, input->channel_num, input->sampling_freq * 4);
    else
        aud_clock_update_input (input->dec_index, input->channel_num, input->sampling_freq);

    return 0;
}

/**
 * Drop input data
 *
 * @param input [in] opend input block context
 * @return int
 * @see
*/
int input_drop_data (struct aud_block_info *block, bool drop)
{
    struct aud_input_info *input = (struct aud_input_info *) block;
    input->drop = drop;

    aimc_set_property (input->uid, "drop-output-data=%d", drop);
    aimc_set_property (input->uid, "drop=%d", drop);

    info ("adec : %d, drop : %d(%s%d)\n", input->dec_index, drop, _input_name[input->input],
        input->index);
    return 0;
}

bool input_is_drop_data (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    return input->drop;
}

int input_start (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    if (input->dec_index < 2)
    {
        if (input->input == INPUT_TP)
        {
            if (input->index == 0)
                aud_hal_bc_buffer_init ("bc-tp0");
            else
                aud_hal_bc_buffer_init ("bc-tp1");
        }
        else if (input->input == INPUT_HDMI)
        {
            if ((input->hdmi_codec == AUDIO_DECODER_CODEC_PCM) && (input->org_hdmi_freq < 32000
                    || input->org_hdmi_freq > 192000))
            {
                noti ("org_hdmi_freq is error : port = %d freq = %d ch = %d\n", input->index,
                    input->org_hdmi_freq, input->org_hdmi_ch);
                return -1;
            }

            if (input->dec_index == 0)
                aud_hal_bc_buffer_init ("bc-sai0");
            else
                aud_hal_bc_buffer_init ("bc-sai1");
        }
        else if (input->input == INPUT_ADC)
            aud_hal_bc_buffer_init ("bc-sai2");
#ifdef SUPPORT_SOUNDBAR
        else if (input->input == INPUT_I2S)
        {
            //ARC : i2s_port_count = 1, e-ARC : i2s_port_count = 4
            if (input->i2s_port_count == 1)
                aud_hal_bc_buffer_init ("bc-sai4");
            else
                aud_hal_bc_buffer_init ("bc-aec-sai");
        }
#endif
    }

    if (input->input == INPUT_SIF)
        AUDIO_RestartAad (false);
    else
        aimc_set_property (input->uid, "start=%d", true);

    input_set_clock (block);

    input->is_start = true;

    info ("adec : %d(%s%d)\n", input->dec_index, _input_name[input->input], input->index);
    return 0;
}

int input_stop (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    if (input->is_start == true && input->input != INPUT_SIF)
        aimc_set_property (input->uid, "start=%d", false);

    aud_clock_disable_input (input->dec_index);

    input->is_start = false;

    if (input->input == INPUT_TP)
        aimc_set_property (input->uid_queue, "set-flush=%d", true);
#ifdef SUPPORT_SOUNDBAR
    else if (input->input == INPUT_HDMI || input->input == INPUT_I2S)
#else
    else if (input->input == INPUT_HDMI)
#endif
    {
        aimc_set_property (input->uid_queue, "set-flush=%d", true);
#ifndef SUPPORT_SOUNDBAR
        aimc_set_property (input->uid_queue_bypass, "set-flush=%d", true);
#endif
    }

    info ("adec : %d(%s%d)\n", input->dec_index, _input_name[input->input], input->index);
    return 0;
}

enum input_type input_get_type (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    return input->input;
}

enum audio_decoder_codec input_get_hdmi_codec (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    return input->hdmi_codec;
}

int input_get_index (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    return input->index;
}

int input_get_uid (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    return input->uid;
}

int input_get_int_count (struct aud_block_info *block, int *int_count, int *clock_count)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    if (int_count == NULL || clock_count == NULL)
        return -1;

    if (input->input == INPUT_TP || input->input == INPUT_HDMI)
    {
        aimc_get_property (input->uid, "int-count", int_count);
        aimc_get_property (input->uid, "clock-count", clock_count);
    }
    else
    {
        *int_count = 0;
        *clock_count = 0;
    }

    trace ("int_count = %d clock_count = %d\n", *int_count, *clock_count);
    return 0;
}

int input_get_overflow_count (struct aud_block_info *block, int *overflow_count)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    if (overflow_count == NULL)
        return -1;

    aimc_get_property (input->uid, "overflow-count", overflow_count);

    trace ("overflow_count = %d\n", *overflow_count);
    return 0;
}

static void input_remove_pipelines (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    // disconnect & remove input queue & bypass queue
    if (input->pipeline_queue)
    {
        bm_unregister_port_forward (block, PORT_OUT, 0);
        apipeline_disconnect (input->pipeline_queue, 0);
        apipeline_del (input->pipeline_queue);
    }

#ifndef SUPPORT_SOUNDBAR
    if (input->pipeline_bypass)
    {
        bm_unregister_port_forward (block, PORT_OUT, BYPASS_PORT);
        apipeline_disconnect (input->pipeline_bypass, 0);
        apipeline_del (input->pipeline_bypass);
    }
#endif

    // remove main pipeline
    if (block->pipeline)
        apipeline_del (block->pipeline);

    block->pipeline = NULL;
    input->pipeline_queue = NULL;
#ifndef SUPPORT_SOUNDBAR
    input->pipeline_bypass = NULL;
#endif
}

static int input_set_input_queue (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;
    int preferred_proc = bm_get_preffered_processor (block);

    input->pipeline_queue = apipeline_new2 (preferred_proc, "input_queue");
    input->uid_queue = apipeline_appendf (input->pipeline_queue, "input_queue");

    apipeline_connect (block->pipeline, 0, input->pipeline_queue, 0);
    bm_register_port_forward (block, PORT_OUT, 0, input->pipeline_queue, 0);
    return 0;
}

int input_set_type (struct aud_block_info *block, int dec_index, enum input_type type_input,
    int index, bool update)
{
    struct aud_input_info *input = (struct aud_input_info *) block;
    int preferred_proc = bm_get_preffered_processor (block);

    info ("input : %s%d%d\n", _input_name[type_input], index, dec_index);

    input->dec_index = dec_index;
    input->input = type_input;
    input->index = index;

    //update a adec index when AAD input decoder is connected.
    if (update)
    {
        info ("input : %s%d%d\n", _input_name[type_input], index, dec_index);
        return 0;
    }

    input_remove_pipelines (block);

    block->pipeline = apipeline_new2 (preferred_proc, "input_%s", _input_name[type_input]);

    if (type_input == INPUT_SIF)
        input->uid = apipeline_addf (block->pipeline, "aad");
    else if (type_input == INPUT_TP)
    {
        if (input->dec_index < 2)
        {
            if (input->index == 0)
                aud_hal_bc_buffer_init ("bc-tp0");
            else
                aud_hal_bc_buffer_init ("bc-tp1");
        }

        input->uid = apipeline_addf (block->pipeline, "tp%d", index);
        input_set_input_queue (block);
    }
    else if (type_input == INPUT_HDMI)
    {
        if (input->dec_index < 2)
        {
            if (input->dec_index == 0)
                aud_hal_bc_buffer_init ("bc-sai0");
            else
                aud_hal_bc_buffer_init ("bc-sai1");
        }

        input->uid = apipeline_addf (block->pipeline, "hdmi%d", dec_index);
        input_set_input_queue (block);

#ifndef SUPPORT_SOUNDBAR
        input->pipeline_bypass = apipeline_new2 (preferred_proc, "input_bypass");
        input->uid_queue_bypass = apipeline_appendf (input->pipeline_bypass, "input_queue");
        apipeline_connect (block->pipeline, 1, input->pipeline_bypass, 0);
        bm_register_port_forward (block, PORT_OUT, BYPASS_PORT, input->pipeline_bypass, 0);
#endif
    }
    else if (type_input == INPUT_ADC)
    {
        aud_hal_bc_buffer_init ("bc-sai2");
        input->uid = apipeline_addf (block->pipeline, "adc");
    }
#ifdef SUPPORT_SOUNDBAR
    else if (type_input == INPUT_I2S)
    {
        //ARC : i2s_port_count = 1, e-ARC : i2s_port_count = 4
        if (input->i2s_port_count == 1)
        {
            aud_hal_bc_buffer_init ("bc-sai4");
            input->uid = apipeline_addf (block->pipeline, "i2s_sai4");
        }
        else
        {
            aud_hal_bc_buffer_init ("bc-aec-sai");
            input->uid = apipeline_addf (block->pipeline, "i2s_aec_sai");
        }

        input_set_input_queue (block);
    }
#endif
    else
        return -1;

    return 0;
}

static const char *_event_name[INPUT_EVT_MAX] = {
    [INPUT_EVT_TP_ES_EXIST_INFO] = "tp_es_exist",
    [INPUT_EVT_HDMI_PCM_FORMAT] = "hdmi_pcm_format",
    [INPUT_EVT_TP_PDEC_ERROR_INFO] = "tp_pdec_error",
#ifdef SUPPORT_DTSX
    [INPUT_EVT_HDMI_DTS_FORMAT_CHANGED] = "hdmi_dts_format_changed",
#endif
};

int input_register_event (struct aud_block_info *block, enum input_evt event,
    int (*cb_func) (void *, int, void *), struct aud_block_info *cb_target_block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;
    struct aud_input_event_info *event_info = NULL;
    int event_id = 0;

    if (event >= INPUT_EVT_MAX)
        return -1;

    list_for_each_entry (event_info, &input->list_event, list)
    {
        if (!strcmp (_event_name[event], event_info->name))
        {
            info ("already registered event, %s\n", _event_name[event]);

            return 0;
        }
    }

    event_info =
        (struct aud_input_event_info *) kzalloc (sizeof (struct aud_input_event_info), GFP_KERNEL);
    if (!event_info)
    {
        error ("no mem\n");
        return -1;
    }

    event_id =
        aimc_register_named_event (cb_target_block, cb_func, input->uid, _event_name[event], true);

    event_info->name = kstrdup (_event_name[event], GFP_KERNEL);
    event_info->id = event_id;
    event_info->cb_func = cb_func;
    event_info->cb_target_block = cb_target_block;

    list_add (&event_info->list, &input->list_event);

    info ("input register event, %s (event_id: %d)\n", _event_name[event], event_id);

    return 0;
}

int input_unregister_event (struct aud_block_info *block, enum input_evt event)
{
    struct aud_input_info *input = (struct aud_input_info *) block;
    struct aud_input_event_info *event_info = NULL;
    int event_id = -1;

    if (event >= INPUT_EVT_MAX)
        return -1;

    list_for_each_entry (event_info, &input->list_event, list)
    {
        if (!strcmp (_event_name[event], event_info->name))
        {
            info ("found register, %s (event_id: %d)\n", event_info->name, event_info->id);
            event_id = event_info->id;
            break;
        }
    }

    if (event_id > 0)
    {
        aimc_unregister_named_event (event_id);

        list_del (&event_info->list);
        kfree (event_info->name);
        kfree (event_info);

        info ("input unregister event, %s\n", _event_name[event]);
    }
    else
    {
        info ("event is not registered, %s\n", _event_name[event]);
    }

    return 0;
}

static int input_update_event_id (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;
    struct aud_input_event_info *event_info = NULL;
    int event_id = -1;

    list_for_each_entry (event_info, &input->list_event, list)
    {
        if (event_info)
        {
            aimc_unregister_named_event (event_info->id);

            event_id =
                aimc_register_named_event (event_info->cb_target_block, event_info->cb_func,
                input->uid, event_info->name, true);

            info ("event is update event id, %s (%d -> %d)\n", event_info->name, event_info->id,
                event_id);

            event_info->id = event_id;
        }
    }

    return 0;
}

static int _input_unregister_event_all (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;
    struct aud_input_event_info *event_info, *next;

    list_for_each_entry_safe (event_info, next, &input->list_event, list)
    {
        info ("input unregister event %s(0x%x)\n", event_info->name, event_info->id);

        aimc_unregister_named_event (event_info->id);

        list_del (&event_info->list);
        kfree (event_info->name);
        kfree (event_info);
    }

    return 0;
}


int input_set_tp (struct aud_block_info *block, enum audio_decoder_codec tp_codec, bool clock_x4)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    int codec;

    switch (tp_codec)
    {
        case AUDIO_DECODER_CODEC_MP3:
            codec = ADEC_MEDIA_MP3;
            break;

        case AUDIO_DECODER_CODEC_AC3:
        case AUDIO_DECODER_CODEC_EAC3:
            codec = ADEC_MEDIA_AC3;
            break;

        case AUDIO_DECODER_CODEC_AC4:
            codec = ADEC_MEDIA_AC4;
            break;

        case AUDIO_DECODER_CODEC_AAC:
            codec = ADEC_MEDIA_AAC;
            break;

        case AUDIO_DECODER_CODEC_DRA:
            codec = ADEC_MEDIA_DRA;
            break;

        default:
            error ("codec(%d) is not support in TP.\n", tp_codec);
            return -1;
            break;
    }
    aimc_set_property (input->uid, "codec=%d", codec);
    input->tp_codec = tp_codec;
    input->clock_x4 = clock_x4;

    aimc_set_property (input->uid_queue, "max-length=%d", TP_INPUT_QUEUE_SIZE);

    info ("tp_codec = %d codec = %d\n", tp_codec, codec);
    return 0;
}

int input_set_hdmi (struct aud_block_info *block, bool forced_pcm)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    LX_HDMI_MUTE_CTRL_T hdmiMute = { input->index, FALSE, FALSE, LX_HDMI_AUDIO_MUTE };
    LX_HDMI_AUDIO_INFO_T hdmiAudioInfo = { };

    enum hdmi_audio_codec hdmi_codec;
    int hdmi_ch, hdmi_freq;
    int mode = HDMI_MODE_PCM;
    int codec;
    bool is_hbr = false;

    hdmi_set_audiomute (hdmiMute.linkNumber, &hdmiMute, sizeof (LX_HDMI_MUTE_CTRL_T));

    hdmiAudioInfo.linkNumber = input->index;
    hdmi_get_audioinfo (hdmiAudioInfo.linkNumber, &hdmiAudioInfo, sizeof (LX_HDMI_AUDIO_INFO_T));

    hdmi_codec = (enum hdmi_audio_codec) hdmiAudioInfo.audioType;
    hdmi_ch = hdmiAudioInfo.countOfChannel;
    hdmi_freq = hdmiAudioInfo.samplingFreq;
    input->org_hdmi_ch = hdmi_ch;
    input->org_hdmi_freq = hdmi_freq;

    aimc_set_property (input->uid, "hdmi-port=%d", input->index);

    if (hdmi_freq < 32000 || hdmi_freq > 192000)
        input->sampling_freq = 48000;
    else
        input->sampling_freq = hdmi_freq;
    aimc_set_property (input->uid, "sampling-freq=%d", input->sampling_freq);

    if (hdmi_codec == HDMI_AUDIO_PCM || forced_pcm == true)
    {
        if (hdmi_ch == 2 || hdmi_ch == 4 || hdmi_ch == 6 || hdmi_ch == 8)
            input->channel_num = hdmi_ch;
        else if (hdmi_ch == 3 || hdmi_ch == 5 || hdmi_ch == 7)
            input->channel_num = hdmi_ch + 1;
        else
            input->channel_num = 2;
        aimc_set_property (input->uid, "channel-num=%d", input->channel_num);
        info ("ch = %d\n", input->channel_num);

        if (hdmi_freq > 48000 || input->channel_num > 2)
            is_hbr = true;
    }
    else
    {
        switch (hdmi_codec)
        {
            case HDMI_AUDIO_MAT:
#ifdef SUPPORT_DTSX
            case HDMI_AUDIO_DTS_HD:
#endif
                mode = HDMI_MODE_BITSTREAM_HBR;
                break;

#ifdef SUPPORT_DTSX
            case HDMI_AUDIO_DTS_HD_HRA:
                mode = HDMI_MODE_BITSTREAM_HBR_HRA;
                break;
#endif

            case HDMI_AUDIO_AC3_IEC60958:
            case HDMI_AUDIO_EAC3_IEC60958:
            case HDMI_AUDIO_UNKNOWN_AC3:
            case HDMI_AUDIO_UNKNOWN_EAC3:
            case HDMI_AUDIO_UNKNOWN_AAC:
#ifdef SUPPORT_DTSX
            case HDMI_AUDIO_UNKNOWN_DTS:
#endif
                mode = HDMI_MODE_BYTE0_PC_VALID;
                break;

            case HDMI_AUDIO_UNKNOWN_MAT:
#ifdef SUPPORT_DTSX
            case HDMI_AUDIO_UNKNOWN_DTS_HD:
#endif
                mode = HDMI_MODE_BYTE0_PC_VALID_HBR;
                break;

#ifdef SUPPORT_DTSX
            case HDMI_AUDIO_UNKNOWN_DTS_HD_HRA:
                mode = HDMI_MODE_BYTE0_PC_VALID_HBR_HRA;
                break;
#endif

            default:
                mode = HDMI_MODE_BITSTREAM;     //non-pcm
                break;
        }
    }
    aimc_set_property (input->uid, "mode=%d", mode);

    //const unsigned char *evt_codec[] = { "pcm", "ac3", "eac3", "aac", "mat", "dts", "dts_hd", };
    if (hdmi_codec == HDMI_AUDIO_PCM || forced_pcm == true)
    {
        codec = HDMI_CODEC_PCM;
        input->hdmi_codec = AUDIO_DECODER_CODEC_PCM;
    }
    else
    {
        switch (hdmi_codec)
        {
            case HDMI_AUDIO_AC3:
            case HDMI_AUDIO_UNKNOWN_AC3:
                codec = HDMI_CODEC_AC3;
                input->hdmi_codec = AUDIO_DECODER_CODEC_AC3;
                break;

            case HDMI_AUDIO_EAC3:
            case HDMI_AUDIO_UNKNOWN_EAC3:
                codec = HDMI_CODEC_EAC3;
                input->hdmi_codec = AUDIO_DECODER_CODEC_EAC3;
                is_hbr = true;
                break;

            case HDMI_AUDIO_AAC:
            case HDMI_AUDIO_UNKNOWN_AAC:
                codec = HDMI_CODEC_AAC;
                input->hdmi_codec = AUDIO_DECODER_CODEC_AAC;
                break;

            case HDMI_AUDIO_MAT:
            case HDMI_AUDIO_UNKNOWN_MAT:
                codec = HDMI_CODEC_MAT;
                input->hdmi_codec = AUDIO_DECODER_CODEC_MAT;
                is_hbr = true;
                break;

#ifdef SUPPORT_DTSX
            case HDMI_AUDIO_DTS:
            case HDMI_AUDIO_UNKNOWN_DTS:
                codec = HDMI_CODEC_DTS;
                input->hdmi_codec = AUDIO_DECODER_CODEC_DTS;
                break;

            case HDMI_AUDIO_DTS_HD:
            case HDMI_AUDIO_UNKNOWN_DTS_HD:
                codec = HDMI_CODEC_DTS_HD;
                input->hdmi_codec = AUDIO_DECODER_CODEC_DTS_HD;
                is_hbr = true;
                break;

            case HDMI_AUDIO_DTS_HD_HRA:
            case HDMI_AUDIO_UNKNOWN_DTS_HD_HRA:
                if (hdmi_freq < 192000)
                {
                    codec = HDMI_CODEC_DTS;
                    input->hdmi_codec = AUDIO_DECODER_CODEC_DTS;
                }
                else
                {
                    codec = HDMI_CODEC_DTS_HD;
                    input->hdmi_codec = AUDIO_DECODER_CODEC_DTS_HD;
                    is_hbr = true;
                }
                break;
#endif

            default:
                codec = HDMI_CODEC_PCM;
                input->hdmi_codec = AUDIO_DECODER_CODEC_PCM;
                break;
        }
    }
    aimc_set_property (input->uid, "codec=%d", codec);

    if (is_hbr)
    {
        aimc_set_property (input->uid_queue, "max-length=%d", HDMI_HBR_INPUT_QUEUE_SIZE);
#ifndef SUPPORT_SOUNDBAR
        aimc_set_property (input->uid_queue_bypass, "max-length=%d", HDMI_HBR_INPUT_QUEUE_SIZE);
#endif
    }

    input->forced_pcm = forced_pcm;

    noti ("port = %d mode = %d codec = %d freq = %d\n", input->index, mode, codec,
        input->sampling_freq);
    return 0;
}

int input_set_hdmi_bypass (struct aud_block_info *block, bool data_drop, int output_port)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    int data_drop_mode;

    if (data_drop == true)
    {
        switch (output_port)
        {
            case 0:
                data_drop_mode = HDMI_DATA_DROP_MODE_MAIN_PATH_DROP;
                break;

            case 1:
                data_drop_mode = HDMI_DATA_DROP_MODE_SUB_PATH_DROP;
                break;

            default:
                data_drop_mode = HDMI_DATA_DROP_MODE_NONE;
                error ("Set data drop port & flag but this is not drop mode. \n");
                break;
        }
    }
    else
        data_drop_mode = HDMI_DATA_DROP_MODE_NONE;

    aimc_set_property (input->uid, "data-drop-mode=%d", data_drop_mode);

    input->data_drop = data_drop;
    input->output_port = output_port;

    noti ("data_drop = %d output_port = %d mode = %d\n", data_drop, output_port, data_drop_mode);
    return 0;
}

int input_set_hdmi_multi_pcm_out (struct aud_block_info *block, bool enable)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    aimc_set_property (input->uid, "multi-pcm-out=%d", enable);
    input->hdmi_multi_pcm_out = enable;

    noti ("enable = %d\n", enable);
    return 0;
}

#ifdef SUPPORT_SOUNDBAR
int input_set_i2s_port_count (struct aud_block_info *block, int i2s_port_count)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    input->i2s_port_count = i2s_port_count;

    noti ("i2s_port_count = %d\n", input->i2s_port_count);
    return 0;
}

int input_set_i2s (struct aud_block_info *block, bool forced_pcm, int i2s_hdmi_type,
    int i2s_hdmi_ch, int i2s_hdmi_freq)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    int mode = HDMI_MODE_PCM;
    int codec;
    bool is_hbr = false;

    input->org_hdmi_type = i2s_hdmi_type;
    input->org_hdmi_ch = i2s_hdmi_ch;
    input->org_hdmi_freq = i2s_hdmi_freq;
    input->sampling_freq = i2s_hdmi_freq;

    //ARC : i2s_port_count = 1, e-ARC : i2s_port_count = 4
    if (input->i2s_port_count == 1)
        aimc_set_property (input->uid, "hdmi-port=%d", 4);
    else
        aimc_set_property (input->uid, "hdmi-port=%d", 5);

    aimc_set_property (input->uid, "sampling-freq=%d", input->sampling_freq);

    //const unsigned char *evt_codec[] = { "pcm", "ac3", "eac3", "aac", "mat", "dts", "dts_hd", "auto", };
    if (i2s_hdmi_type == I2S_AUDIO_TYPE_PCM || forced_pcm == true)
    {
        input->channel_num = i2s_hdmi_ch;
        aimc_set_property (input->uid, "channel-num=%d", input->channel_num);

        codec = HDMI_CODEC_PCM;
        input->hdmi_codec = AUDIO_DECODER_CODEC_PCM;

        if (i2s_hdmi_freq > 48000 || input->channel_num > 2)
            is_hbr = true;
    }
    else
    {
        switch (i2s_hdmi_type)
        {
            case I2S_AUDIO_TYPE_HBR:
                mode = HDMI_MODE_BITSTREAM_HBR;
                codec = HDMI_CODEC_AUTO;
                input->hdmi_codec = AUDIO_DECODER_CODEC_AUTO;
                is_hbr = true;
                break;

#ifdef SUPPORT_DTSX
            case I2S_AUDIO_TYPE_HBR:
                mode = HDMI_MODE_BITSTREAM_HBR_HRA;
                break;
#endif

            default:
                mode = I2S_AUDIO_TYPE_AUTO;     //non-pcm
                codec = HDMI_CODEC_AUTO;
                input->hdmi_codec = AUDIO_DECODER_CODEC_AUTO;
                break;
        }
    }
    aimc_set_property (input->uid, "mode=%d", mode);
    aimc_set_property (input->uid, "codec=%d", codec);

    if (is_hbr)
        aimc_set_property (input->uid_queue, "max-length=%d", HDMI_HBR_INPUT_QUEUE_SIZE);

    input->forced_pcm = forced_pcm;

    noti ("port = %d mode = %d codec = %d freq = %d\n", input->index, mode, codec,
        input->sampling_freq);
    return 0;
}
#endif

/**
 * create input block
 *
 *
 * @return 0 - OK
*/
static int input_create (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    info ("create\n");

    block->isOpened = true;
    input->dec_index = -1;
    input->drop = true;
    input->hdmi_multi_pcm_out = false;
    input->is_start = false;
    input->is_suspended = false;
    input->data_drop = false;
    input->channel_num = 2;
    input->org_hdmi_ch = 2;
    input->sampling_freq = 48000;
    input->org_hdmi_freq = 48000;
    input->hdmi_codec = AUDIO_DECODER_CODEC_UNKNOWN;
#ifdef SUPPORT_SOUNDBAR
    input->org_hdmi_type = I2S_AUDIO_TYPE_UNKNOWN;
    input->i2s_port_count = 4;
#endif
    input->forced_pcm = false;

    INIT_LIST_HEAD (&input->list_event);

    info ("done\n");
    return 0;
}

/**
 * close input
 *
 * @param input [in] pointer of input info
 * @return void
 * @see aud_input_info
*/
static void input_destroy (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;
    struct aud_input_event_info *event_info = NULL;
    struct aud_input_event_info *next = NULL;

    info ("called\n");

    AUD_INPUT_LOCK ();

    if (block == NULL)
    {
        error ("input is NULL!!\n");
        goto exit;
    }

    if (block->isOpened == false)
    {
        error ("input is already closed.\n");
        goto exit;
    }

    aud_clock_disable_input (input->dec_index);

    // destroy pipeline (inside modules are destroyed automatically)
    input_remove_pipelines (block);

    block->isOpened = false;

    list_for_each_entry_safe (event_info, next, &input->list_event, list)
    {
        debug ("remove event list, event=%s\n", event_info->name);
        list_del (&event_info->list);
        kfree (event_info->name);
        kfree (event_info);
    }

  exit:
    AUD_INPUT_UNLOCK ();
    info ("done\n");
}

static int input_suspend (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    info ("is_start = %d drop = %d\n", input->is_start, input->drop);

    aud_clock_disable_input (input->dec_index);

    _input_set_stop_property (input);

    if (input->input == INPUT_SIF)
        AUDIO_SuspendAad ();

    _input_unregister_event_all (block);
    input_remove_pipelines (block);

    input->is_suspended = true;
    return 0;
}

static int input_resume (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    info ("is_start = %d drop = %d\n", input->is_start, input->drop);

    if (input->input == INPUT_SIF)
        AUDIO_ResumeAad (true);
    else
        input_set_type (block, input->dec_index, input->input, input->index, false);

    aimc_set_property (input->uid, "drop-output-data=%d", true);
    aimc_set_property (input->uid, "drop=%d", true);

    input->is_suspended = false;
    return 0;
}

static int input_post_reconnect (struct aud_block_info *block)
{
    struct aud_input_info *input = (struct aud_input_info *) block;

    info ("is_start = %d drop = %d\n", input->is_start, input->drop);

    if (input->is_start == true)
    {
        if (input->input == INPUT_SIF)
            AUDIO_RestartAad (true);
        else
        {
            if (input->input == INPUT_TP)
                input_set_tp (block, input->tp_codec, input->clock_x4);
            else if (input->input == INPUT_HDMI)
            {
                input_set_hdmi (block, input->forced_pcm);

                if (input->data_drop == true)
                    input_set_hdmi_bypass (block, input->data_drop, input->output_port);

                aimc_set_property (input->uid, "multi-pcm-out=%d", input->hdmi_multi_pcm_out);
            }
#ifdef SUPPORT_SOUNDBAR
            else if (input->input == INPUT_I2S)
            {
                input_set_i2s (block, input->forced_pcm, input->org_hdmi_type,
                    input->org_hdmi_ch, input->org_hdmi_freq);
            }
#endif

            input_update_event_id (block);
            input_start (block);
        }

        input_drop_data (block, input->drop);
        input_set_clock (block);
    }

    return 0;
}

static struct audio_block_impl block_impl = {
    .block_info_size = sizeof (struct aud_input_info),
    .block_type = "input",
    .preffered_processor = ADEC_CORE_DSP0,
    .constructor = input_create,
    .destructor = input_destroy,
    .suspend = input_suspend,
    .resume = input_resume,
    .post_reconnect = input_post_reconnect,
};

void input_initializer (void)
{
    bm_block_registry (&block_impl);
}
