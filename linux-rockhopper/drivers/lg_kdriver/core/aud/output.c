/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2017 by LG Electronics Inc.
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
 *  @file output.c
 *
 *  Audio driver implementation for  audio output block.
 *  Output block manages Speaker, Headphone(HP), Optic(SPDIF), and ARC output
 *  (include eARC).
 *
 *  speaker output : 48000/96000Hz rate, 2/4 channels pcm.
 *  out_speaker - pcm
 *
 *  headphone output : only 48000Hz, 2 channels pcm.
 *  out_hp - pcmsub.
 *
 *  spdif output : 32000/44100/48000Hz rate, multi channels, pcm/aac/ac3 codec.
 *  pcm output : out_spdif - spdif
 *  es output : outes_spdif - spdif
 *
 *  arc output : 32000/44100/48000/64000/88200/96000/128000/17400/192000Hz rate,
 *  multi channels, pcm/aac/ac3/eac3/mat codec.
 *  pcm output : out_arc - arc
 *  es output : outes_arc - arc
 *
 *  @author	wonchang.shin (wonchang.shin@lge.com)
 *  @version    0.1
 *  @date       2020/06/29
 *
 *  @addtogroup output
 *  @{
 */
#include <linux/slab.h>

#include "log.h"
#include "block.h"
#include "block_manager.h"
#include "output.h"
#include "clock.h"

#include "kaimc.h"
#include "imc/cmd/module_cmd_spdifout.h"
#include "imc/cmd/module_cmd_arcout.h"
#include "imc/cmd/module_cmd_outctrl.h"
#include "imc/cmd/module_cmd_esoutctrl.h"
#include "imc/cmd/module_cmd_clock.h"
#include "imc/evt/module_evt_spdifout.h"
#include "module/adec_module_list.h"

#include "hal/hal_output.h"
#include "hal/hal_clock.h"

#ifndef CHIP_TYPE_FPGA
#ifdef INCLUDE_KDRV_HDMI20
extern void HDMI21_ISRUNIT_Rx_Set_RegisterEarcDmacIsrCallBack (void (*function) (unsigned int
        intStatus));
#endif
#endif

bool gOutputConnectSpdif;

void output_earc_dmac_irq (unsigned int intStatus);

logm_define (aud_output, log_level_noti);
#define trace(fmt,args...)  logm_trace(aud_output,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_output,fmt,##args)
#define info(fmt,args...)   logm_info(aud_output,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_output,fmt,##args)
#define error(fmt,args...)  logm_error(aud_output,fmt,##args)

static DEFINE_MUTEX (_output_lock);

#define AUD_OUTPUT_LOCK()		mutex_lock(&_output_lock)
#define AUD_OUTPUT_UNLOCK()	mutex_unlock(&_output_lock)

#define OUTPUT_TO_STR(x) (output_type_str[(x)->output_type])

#ifdef SUPPORT_SOUNDBAR
#define CLOCK_TYPE(_out) ( \
            (_out == OUTPUT_SPEAKER) ? CLOCK_OUTPUT_SPEAKER : \
            (_out == OUTPUT_HP) ? CLOCK_OUTPUT_HP : \
            (_out == OUTPUT_OPTIC) ? CLOCK_OUTPUT_OPTIC : \
            (_out == OUTPUT_ARC) ? CLOCK_OUTPUT_ARC : \
            (_out == OUTPUT_PC) ? CLOCK_OUTPUT_PC : CLOCK_OUTPUT_MAX)
#else
#define CLOCK_TYPE(_out) ( \
            (_out == OUTPUT_SPEAKER) ? CLOCK_OUTPUT_SPEAKER : \
            (_out == OUTPUT_HP) ? CLOCK_OUTPUT_HP : \
            (_out == OUTPUT_OPTIC) ? CLOCK_OUTPUT_OPTIC : \
            (_out == OUTPUT_ARC) ? CLOCK_OUTPUT_ARC : CLOCK_OUTPUT_MAX)
#endif

static const char *output_type_str[] = {
    "SPK", "HP", "OPTIC", "ARC",
#ifdef SUPPORT_SOUNDBAR
    "PC",
#endif
    "MAX", "OTHERS", "????", "????", "????", "????", "????", "????"
};

static const char *output_codec_str[] = {
    "pcm", "ac3", "eac3", "aac", "mat",
#ifdef SUPPORT_DTSX
    "dts", "dts_hd", "dts_hd_ma", "dtsx_p1", "dtsx_p2",
#endif
    "???"
};

struct sound_bar_status
{
    unsigned int subframe_id;   ///< subframe id.
    unsigned int subframe_data; ///< subframe data.
    unsigned int subframe_checksum;     ///< subframe checksum.
};

/**
 * AUDIO output Information.
 */
struct aud_output_info
{
    struct aud_block_info parent;

    struct list_head list_module;

    bool suspended;
    enum output_type_t output_type;
    int uid_outctrl;
    int uid_out;

    bool mute;
    unsigned int volume;
    unsigned int delay;

    enum output_codec_t codec;
    unsigned int channel;
    unsigned int sample_rate;
    unsigned int acmod;
    unsigned int bypass;

    unsigned int scms;
    unsigned int category_code;
    bool on;
    bool sound_bar_on;
    struct sound_bar_param sound_bar_param;
    struct sound_bar_command sound_bar_command;
    struct sound_bar_status sound_bar_status;
    bool sound_bar_power;

    bool earc_on;
    int event_id;

#ifdef SUPPORT_ULTRASENSE
    // for ultrasense
    struct apipeline *pipeline_playback_in;
    int uid_queue_playback_in;
    int uid_bypass_playback_in;
#endif
};

/**
 * Set Output Volume
 *
 * @param type [in] output type
 * @param volume [in] output volume
 * @return int
 * @see
*/
int output_set_volume (struct aud_block_info *block, unsigned int volume)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (output->codec == OUTPUT_CODEC_PCM)
        aimc_set_property (output->uid_outctrl, "gain=%d", volume);
    else
        aimc_set_property (output->uid_outctrl, "gain=%d", 0x800000);

    output->volume = volume;

    info ("%s volume : 0x%x.\n", OUTPUT_TO_STR (output), volume);

    return 0;
}

/**
 * Set Output Mute
 *
 * @param type [in] output type
 * @param on [in] output mute
 * @return int
 * @see
*/
int output_set_mute (struct aud_block_info *block, bool on)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    aimc_set_property (output->uid_outctrl, "mute-output=%d\\mute-input=%d", on, on);

    output->mute = on;

    info ("%s mute : %s.\n", OUTPUT_TO_STR (output), on ? "ON" : "OFF");

    return 0;
}

/**
 * Set Output Delay
 *
 * @param type [in] output type
 * @param delay [in] output delay
 * @return int
 * @see
*/
int output_set_delay (struct aud_block_info *block, unsigned int delay)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    aimc_set_property (output->uid_outctrl, "delay=%d", delay);

    output->delay = delay;

    info ("%s delay : %d.\n", OUTPUT_TO_STR (output), delay);

    return 0;
}

static void _set_format (struct aud_output_info *output, enum output_codec_t codec,
    unsigned int channel, unsigned int acmod, unsigned int sample_rate, bool bypass)
{
    aud_clock_update_output ((enum aud_clock_output) output->output_type, sample_rate, channel,
        bypass);

    if (output->output_type == OUTPUT_ARC)
    {
        audio_hal_earc_set_mute (true);

        audio_hal_earc_set_channel (channel, acmod);

        if (codec == OUTPUT_CODEC_PCM)
            audio_hal_earc_set_output_format (AUDIO_HAL_OUTPUT_PCM, sample_rate);
        else
            audio_hal_earc_set_output_format (AUDIO_HAL_OUTPUT_ES, sample_rate);

        audio_hal_earc_set_mute (false);

        audio_hal_earc_set_on (output->earc_on);
    }

    output->codec = codec;
    output->channel = channel;
    output->sample_rate = sample_rate;
    output->bypass = bypass;

    return;
}

/**
 * Set Output Format about codec, channel, sample_rate.
 *
 * @param block [in] output block information
 * @param channel [in] output codec
 * @param channel [in] output channel
 * @param sample_rate [in] output sample_rate
 * @return int
 * @see
*/
int output_set_format (struct aud_block_info *block, enum output_codec_t codec,
    unsigned int channel, unsigned int sample_rate, bool bypass)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    //_set_format (output, codec, channel, output->acmod, sample_rate, bypass);

    noti ("%s %d, %d, %d %d.\n", OUTPUT_TO_STR (output), codec, channel, sample_rate, bypass);

    return 0;
}

/**
 * Set Output SCMS
 *
 * @param type [in] output type
 * @param scms [in] output scms
 * @return int
 * @see
*/
int output_set_scms (struct aud_block_info *block, unsigned int scms)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (output->output_type == OUTPUT_OPTIC)
    {
        SpdifCmdSetScms set_spdif_scms = { };

        set_spdif_scms.scms_type = scms;
        aimc_send_command (NULL, SPDIF_CMD_SET_SCMS, 0, output->uid_out, &set_spdif_scms,
            sizeof (set_spdif_scms));
    }
    else if (output->output_type == OUTPUT_ARC)
    {
        ArcCmdSetScms set_arc_scms = { };

        set_arc_scms.scms_type = scms;
        aimc_send_command (NULL, ARC_CMD_SET_SCMS, 0, output->uid_out, &set_arc_scms,
            sizeof (set_arc_scms));

        audio_hal_earc_set_scms (scms);
    }
    else
    {
        debug ("%s is not supported.\n", OUTPUT_TO_STR (output));
        return -1;
    }

    output->scms = scms;

    noti ("%s %x\n", OUTPUT_TO_STR (output), scms);

    return 0;
}

/**
 * Set Output Category Code
 *
 * @param type [in] output type
 * @param category_code [in] output category code
 * @return int
 * @see
*/
int output_set_category_code (struct aud_block_info *block, unsigned int category_code)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (output->output_type == OUTPUT_OPTIC)
    {
        SpdifCmdSetCategoryCode set_spdif_category_code = { };

        set_spdif_category_code.category_code = category_code;
        aimc_send_command (NULL, SPDIF_CMD_SET_CATEGORY_CODE, 0, output->uid_out,
            &set_spdif_category_code, sizeof (set_spdif_category_code));
    }
    else if (output->output_type == OUTPUT_ARC)
    {
        ArcCmdSetCategoryCode set_arc_category_code = { };

        set_arc_category_code.category_code = category_code;
        aimc_send_command (NULL, ARC_CMD_SET_CATEGORY_CODE, 0, output->uid_out,
            &set_arc_category_code, sizeof (set_arc_category_code));

        audio_hal_earc_set_category_code (category_code);
    }
    else
    {
        debug ("%s is not supported.\n", OUTPUT_TO_STR (output));
        return -1;
    }

    output->category_code = category_code;

    noti ("%s %x\n", OUTPUT_TO_STR (output), category_code);

    return 0;
}

/**
 * Set Output On/Off
 *
 * @param type [in] output type
 * @param on [in] output on
 * @return int
 * @see
*/
int output_set_on (struct aud_block_info *block, bool on)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    output->on = on;

    if (output->output_type == OUTPUT_OPTIC)
    {
        SpdifCmdSetLight set_light = { };

        set_light.onoff = on;
        aimc_send_command (NULL, SPDIF_CMD_SET_LIGHT, 0, output->uid_out, &set_light,
            sizeof (set_light));

        aud_hal_output_optic_light_on (on);
    }
    else if (output->output_type == OUTPUT_ARC)
        ;
    else
    {
        debug ("%s is not supported.\n", OUTPUT_TO_STR (output));
        return -1;
    }

    noti ("%s %s\n", OUTPUT_TO_STR (output), on ? "on" : "off");

    return 0;
}

/**
 * Set Sound Bar On/Off
 *
 * @param on [in] sound bar on
 * @return int
 * @see
*/
int output_set_sound_bar_on (struct aud_block_info *block, bool on)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (on == false)
    {
        aimc_send_command (NULL, SPDIF_CMD_CLEAR_FMT_FOR_SOUNDBAR, 0, output->uid_out, NULL, 0);
        memset (&(output->sound_bar_param), 0, sizeof (struct sound_bar_param));
    }

    output->sound_bar_on = on;

    noti ("soundbar %s.\n", on ? "ON" : "OFF");

    return 0;
}

static int _cb_sound_bar_status (void *_param, int _paramLen, void *_cbParam)
{
    struct aud_output_info *output = (struct aud_output_info *) _cbParam;
    SpdifEvtGetFmtForSoundbar *pSoundBarStatus = (SpdifEvtGetFmtForSoundbar *) _param;

    if (_paramLen != sizeof (SpdifEvtGetFmtForSoundbar))
    {
        error ("Param Length Error[Expected:%zd][Input:%d]\n", sizeof (SpdifEvtGetFmtForSoundbar),
            _paramLen);
        return -1;
    }

    output->sound_bar_status.subframe_id = pSoundBarStatus->id;
    output->sound_bar_status.subframe_data = pSoundBarStatus->data;
    output->sound_bar_status.subframe_checksum = pSoundBarStatus->checksum;
    output->sound_bar_status.subframe_data |= (pSoundBarStatus->reserved << 16);

    noti ("id(0x%x), data(0x%x), res(0x%x), checksum(0x%x)\n",
        pSoundBarStatus->id, pSoundBarStatus->data, pSoundBarStatus->reserved,
        pSoundBarStatus->checksum);
    debug ("subframe_data(0x%x)\n", output->sound_bar_status.subframe_data);

    return 0;
}

/**
 * Set Sound Bar Parameters
 *
 * @param param [in] sound bar parameters
 * @return int
 * @see
*/
int output_set_sound_bar_param (struct aud_block_info *block, struct sound_bar_param *param)
{
    struct aud_output_info *output = (struct aud_output_info *) block;
    SpdifCmdSetFmtForSoundbar setSoundbarFormat = { };

    setSoundbarFormat.id = param->id;
    setSoundbarFormat.mute = (param->data >> 7) & 0x1;
    setSoundbarFormat.volume = param->data & 0x7F;
    aimc_send_command (NULL, SPDIF_CMD_SET_FMT_FOR_SOUNDBAR, 0, output->uid_out, &setSoundbarFormat,
        sizeof (SpdifCmdSetFmtForSoundbar));

    memcpy (&(output->sound_bar_param), param, sizeof (struct sound_bar_param));

    noti ("mute:%d vol:%d.\n", setSoundbarFormat.mute, setSoundbarFormat.volume);

    return 0;
}

#if 0                           // Unused function
/**
 * Set Sound Bar Commands
 *
 * @param command [in] sound bar commands
 * @return int
 * @see
*/
int output_set_sound_bar_command (struct aud_block_info *block, struct sound_bar_command *command)
{
#if 0
    struct aud_output_info *output = (struct aud_output_info *) block;
    SpdifCmdSetEqbypassForSoundbar setSoundBarEqBypass;
    SpdifCmdSetWooferlevelForSoundbar setSoundBarWooferLevel;
    SpdifCmdSetWirelessresetForSoundbar setSoundBarWirelessReset;
    aimc_register_named_event (output, _cb_sound_bar_status, output->uid_out, "sound_bar_format",
        false);

    /* Set a Soundbar Command Mode */
    if (command->mode == LX_AUD_MASTER_SB_CMD_AUTO_VOLUME)
    {
        setSoundBarEqBypass.onoff = pSoundbarCmd->ui32CmdParam & 0x1;
        AUDIO_IMC_SendCmdParam (SPDIF_CMD_SET_EQBYPASS_FOR_SOUNDBAR,
            gAdecOutMod[LX_AUD_MASTER_OUTPUT_SPDIF], sizeof (SpdifCmdSetEqbypassForSoundbar),
            &setSoundBarEqBypass);
    }
    else if (command->mode == LX_AUD_MASTER_SB_CMD_WOOFER_LEVEL)
    {
        setSoundBarWooferLevel.level = pSoundbarCmd->ui32CmdParam & 0xF;
        AUDIO_IMC_SendCmdParam (SPDIF_CMD_SET_WOOFERLEVEL_FOR_SOUNDBAR,
            gAdecOutMod[LX_AUD_MASTER_OUTPUT_SPDIF], sizeof (SpdifCmdSetWooferlevelForSoundbar),
            &setSoundBarWooferLevel);
    }
    else if (command->mode == LX_AUD_MASTER_SB_CMD_WIRELESS_RESET)
    {
        setSoundBarWirelessReset.reset = pSoundbarCmd->ui32CmdParam & 0x1;
        AUDIO_IMC_SendCmdParam (SPDIF_CMD_SET_WIRELESSRESET_FOR_SOUNDBAR,
            gAdecOutMod[LX_AUD_MASTER_OUTPUT_SPDIF], sizeof (SpdifCmdSetWirelessresetForSoundbar),
            &setSoundBarWirelessReset);
    }
    else
    {
        error ("(cmd : %d, param : %d)\n", command->mode, command->param);
        return -1;
    }
#endif
    noti ("cmd : %x, param : %x\n", command->mode, command->param);
    return 0;
}
#endif

/**
 * Set Sound Bar Power On/Off
 *
 * @param on [in] sound bar power on
 * @return int
 * @see
*/
int output_set_sound_bar_power (struct aud_block_info *block, bool on)
{
    struct aud_output_info *output = (struct aud_output_info *) block;
    SpdifCmdOnoffSoundbar setSoundBarPower = { };

    aimc_register_named_event (output, _cb_sound_bar_status, output->uid_out, "sound_bar_format",
        false);

    setSoundBarPower.onoff = on;

    aimc_send_command (NULL, SPDIF_CMD_ONOFF_SOUNDBAR, 0, output->uid_out, &setSoundBarPower,
        sizeof (SpdifCmdOnoffSoundbar));

    output->sound_bar_power = on;

    noti ("power %s.\n", on ? "ON" : "OFF");

    return 0;
}

#if 0                           // Unused function
/**
 * Set Sound Frame On/Off
 *
 * @param on [in] sound bar on
 * @return int
 * @see
*/
int output_set_sound_frame_on (struct aud_block_info *block, bool on)
{
    return 0;
}

/**
 * Set Wisa Speaker On/Off
 *
 * @param on [in] sound bar on
 * @return int
 * @see
*/
int output_set_wisa_on (struct aud_block_info *block, bool on)
{
    return 0;
}

/**
 * Set Blue Tooth Speaker On/Off
 *
 * @param on [in] sound bar on
 * @return int
 * @see
*/
int output_set_bt_on (struct aud_block_info *block, bool on)
{
    return 0;
}

/**
 * Set Blue Tooth Surround Speaker On/Off
 *
 * @param on [in] sound bar on
 * @return int
 * @see
*/
int output_set_bt_surround_on (struct aud_block_info *block, bool on)
{
    return 0;
}
#endif

/**
 * Set eARC On/Off
 *
 * @param on [in] earc on
 * @return int
 * @see
*/
int output_set_earc_on (struct aud_block_info *block, bool on)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (output->output_type != OUTPUT_ARC)
    {
        debug ("%s is not supported.\n", OUTPUT_TO_STR (output));
        return -1;
    }

    output->earc_on = on;

    aud_clock_update_output ((enum aud_clock_output) output->output_type, output->sample_rate,
        output->channel, output->bypass);
    audio_hal_earc_set_on (on);

    noti ("earc %s\n", on ? "on" : "off");

    return 0;
}

void output_earc_dmac_irq (unsigned int intStatus)
{
    audio_hal_earc_clear_interrupt (intStatus);

    return;
}

int output_set_input_index (struct aud_block_info *block, int index)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    aud_clock_set_input_index (CLOCK_TYPE (output->output_type), index);

    return 0;
}

static enum output_codec_t _adec_codec_convert_output_codec (FW_AUD_OUTPUT_CODEC_T adec_codec)
{
    enum output_codec_t output_codec = OUTPUT_CODEC_PCM;

    if (adec_codec == FW_AUD_OUTPUT_CODEC_PCM)
        output_codec = OUTPUT_CODEC_PCM;
    else if (adec_codec == FW_AUD_OUTPUT_CODEC_AC3)
        output_codec = OUTPUT_CODEC_AC3;
    else if (adec_codec == FW_AUD_OUTPUT_CODEC_EAC3)
        output_codec = OUTPUT_CODEC_EAC3;
    else if (adec_codec == FW_AUD_OUTPUT_CODEC_AAC)
        output_codec = OUTPUT_CODEC_AAC;
    else if (adec_codec == FW_AUD_OUTPUT_CODEC_MAT)
        output_codec = OUTPUT_CODEC_MAT;
#ifdef SUPPORT_DTSX
    else if (adec_codec == FW_AUD_OUTPUT_CODEC_DTS)
        output_codec = OUTPUT_CODEC_DTS;
    else if (adec_codec == FW_AUD_OUTPUT_CODEC_DTS_HD)
        output_codec = OUTPUT_CODEC_DTS_HD;
    else if (adec_codec == FW_AUD_OUTPUT_CODEC_DTS_HD_MA)
        output_codec = OUTPUT_CODEC_DTS_HD_MA;
    else if (adec_codec == FW_AUD_OUTPUT_CODEC_DTSX_P1)
        output_codec = OUTPUT_CODEC_DTSX_P1;
    else if (adec_codec == FW_AUD_OUTPUT_CODEC_DTSX_P2)
        output_codec = OUTPUT_CODEC_DTSX_P2;
#endif
    else
        error ("Not supproted adec codec(%d). default pcm output.\n", adec_codec);

    return output_codec;
}

static int _cb_output_status (void *_param, int _paramLen, void *_cbParam)
{
    struct aud_output_info *output = (struct aud_output_info *) _cbParam;
    OutputEvtFirstAu *evtFirstAu = (OutputEvtFirstAu *) _param;
    enum output_codec_t pre_codec = output->codec;
    unsigned int pre_channel = output->channel;
    unsigned int pre_sample_rate = output->sample_rate;
    unsigned int pre_acmod = output->acmod;

    if ((output->output_type == OUTPUT_OPTIC) || (output->output_type == OUTPUT_ARC)
#ifdef SUPPORT_SOUNDBAR
        || (output->output_type == OUTPUT_SPEAKER)
#endif
        )
    {
        output->codec = _adec_codec_convert_output_codec (evtFirstAu->codec);
        output->channel = evtFirstAu->channel;
        output->sample_rate = evtFirstAu->sample_rate;
        if (output->codec == OUTPUT_CODEC_PCM)
            output->acmod = evtFirstAu->acmod;
        else if (output->codec >= OUTPUT_CODEC_MAX)
        {
            output->channel = 2;
            output->sample_rate = 48000;
            output->acmod = 2;
            error ("invalid codec(%d). default pcm 2ch 48000 output.\n", output->codec);
            output->codec = OUTPUT_CODEC_PCM;
        }
    }
    else
    {
        error ("wrong callback %s.\n", OUTPUT_TO_STR (output));
        return -1;
    }

    if ((pre_codec != output->codec) || (pre_channel != output->channel)
        || (pre_sample_rate != output->sample_rate) || (pre_acmod != output->acmod))
        _set_format (output, output->codec, output->channel, output->acmod, output->sample_rate,
            output->bypass);
    else
    {
        if (output->output_type == OUTPUT_ARC)
            audio_hal_earc_set_on (output->earc_on);
    }

    noti ("%s %s %d ch %d acmod %d Hz.\n", OUTPUT_TO_STR (output),
        output_codec_str[evtFirstAu->codec], evtFirstAu->channel, evtFirstAu->acmod,
        evtFirstAu->sample_rate);

    return 0;
}

int output_set_type (struct aud_block_info *block, enum output_type_t output_type)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    block->isOpened = true;

    output->output_type = output_type;

    block->pipeline = apipeline_new ("output_%s", OUTPUT_TO_STR (output));
    output->uid_outctrl = apipeline_appendf (block->pipeline, "outctrlbin");
    if (output_type != OUTPUT_HP)
        apipeline_prependf (block->pipeline, "queue");
    if (output_type == OUTPUT_SPEAKER)
        output->uid_out = apipeline_appendf (block->pipeline, "output_speaker");
    else if (output_type == OUTPUT_HP)
        output->uid_out = apipeline_appendf (block->pipeline, "output_hp");
    else if (output_type == OUTPUT_OPTIC)
    {
        output->uid_out = apipeline_appendf (block->pipeline, "output_spdif");
        gOutputConnectSpdif = true;
        aud_hal_switch_spdif_clock (true);
    }
    else if (output_type == OUTPUT_ARC)
    {
        output->uid_out = apipeline_appendf (block->pipeline, "output_arc");

#ifndef CHIP_TYPE_FPGA
#ifdef INCLUDE_KDRV_HDMI20
        HDMI21_ISRUNIT_Rx_Set_RegisterEarcDmacIsrCallBack (output_earc_dmac_irq);
#endif
#endif
    }
#ifdef SUPPORT_SOUNDBAR
    else if (output_type == OUTPUT_PC)
        output->uid_out = apipeline_appendf (block->pipeline, "output_pc");
#endif

    if ((output_type == OUTPUT_OPTIC) || (output_type == OUTPUT_ARC)
#ifdef SUPPORT_SOUNDBAR
        || (output_type == OUTPUT_SPEAKER)
#endif
        )
    {
        if (output->event_id > 0)
            aimc_unregister_named_event (output->event_id);

        output->event_id =
            aimc_register_named_event (output, _cb_output_status, output->uid_out, "output_status",
            true);
        if (output->event_id <= 0)
            error ("fail to register evnet %d\n", output->event_id);
    }

    output_set_mute (block, output->mute);

    // clock info 초기화
    aud_clock_enable_output (CLOCK_TYPE (output->output_type), output->uid_out);

    info ("output : %s.\n", OUTPUT_TO_STR (output));
    return 0;
}

/**
 * create output block
 *
 * @param block [in] context of this block
 * @return pointer of output info
*/
static int output_create (struct aud_block_info *block)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    info ("create output\n");

    block->isOpened = true;
    output->mute = false;
    output->volume = 0;
    output->channel = 2;
#ifdef SUPPORT_SOUNDBAR
    output->sample_rate = 96000;
#else
    output->sample_rate = 48000;
#endif
    output->suspended = false;

    info ("done\n");
    return 0;
}

int output_get_underflow (struct aud_block_info *block, unsigned int *underflow)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    aimc_get_property (output->uid_out, "underflow-count", underflow);

    info ("%s underflow : 0x%x.\n", OUTPUT_TO_STR (output), *underflow);

    return 0;
}

int output_get_latency (struct aud_block_info *block, int *latency)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (output)
    {
        aimc_get_property (output->uid_out, "latency", latency);
        info ("%s latency : %d usec\n", OUTPUT_TO_STR (output), *latency);
    }
    else
    {
        info ("output is null\n");
        return -1;
    }

    return 0;
}

/**
 * destroy output block
 *
 * @param block [in] context of this block
 * @return void
 * @see aud_output_info
*/
static void output_destroy (struct aud_block_info *block)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    AUD_OUTPUT_LOCK ();

    if (block == NULL)
    {
        error ("output_info is NULL!!\n");
        goto exit;
    }

    if (block->isOpened == false)
    {
        error ("output is already closed.\n");
        goto exit;
    }

    if (output->event_id > 0)
        aimc_unregister_named_event (output->event_id);

    aud_clock_disable_output (CLOCK_TYPE (output->output_type));

    // destroy pipeline (inside modules are destroyed automatically)
    if (block->pipeline)
        apipeline_del (block->pipeline);

    if (output->output_type == OUTPUT_OPTIC)
    {
        gOutputConnectSpdif = false;
        aud_hal_switch_spdif_clock (false);
    }

#ifndef CHIP_TYPE_FPGA
#ifdef INCLUDE_KDRV_HDMI20
    if (output->output_type == OUTPUT_ARC)
        HDMI21_ISRUNIT_Rx_Set_RegisterEarcDmacIsrCallBack (NULL);
#endif
#endif

    // Clear a output resource.
    block->isOpened = false;

  exit:
    AUD_OUTPUT_UNLOCK ();
}

static int output_suspend (struct aud_block_info *block)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    output->suspended = true;

    if (output->output_type == OUTPUT_SPEAKER)
        audio_hal_speaker_start (false);
    else if (output->output_type == OUTPUT_HP)
        audio_hal_hp_start (false);
    else if (output->output_type == OUTPUT_OPTIC)
        audio_hal_spdif_start (false);
    else if (output->output_type == OUTPUT_ARC)
        audio_hal_arc_start (false);
#ifdef SUPPORT_SOUNDBAR
    else if (output->output_type == OUTPUT_PC)
        audio_hal_pc_start (false);
#endif

    aud_clock_disable_output (CLOCK_TYPE (output->output_type));

    if (block->pipeline)
        apipeline_del (block->pipeline);

    block->pipeline = NULL;

    noti ("suspend output\n");

    return 0;
}

static int output_resume (struct aud_block_info *block)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (output->suspended)
    {
        output_set_type (block, output->output_type);   // 함수내 aud_clock_enable_output() 호출
        output_set_earc_on (block, output->earc_on);
        output_set_on (block, output->on);
        output_set_category_code (block, output->category_code);
        output_set_scms (block, output->scms);
        _set_format (output, output->codec, output->channel, output->acmod, output->sample_rate,
            output->bypass);
        output_set_delay (block, output->delay);
        output_set_mute (block, output->mute);
        output_set_volume (block, output->volume);
    }

    if (output->output_type == OUTPUT_SPEAKER)
        audio_hal_speaker_start (true);

    output->suspended = false;

    noti ("resume output\n");

    return 0;
}

static int output_pre_disconnect (struct aud_block_info *block, int port, bool in)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (in)
    {
        // not ultrasense
        if (port == 0)
            aimc_set_property (output->uid_outctrl, "mute-output=%d\\mute-input=%d", true, true);
        if (output->output_type == OUTPUT_ARC)
            audio_hal_earc_set_mute (true);

        aimc_set_property (output->uid_outctrl, "delay=%d", 0);
    }

    return 0;
}


static int output_post_disconnect (struct aud_block_info *block, int port, bool in)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (in)
    {
        if (output->output_type == OUTPUT_ARC)
            aimc_send_command (NULL, ADEC_CMD_STOP, 0, output->uid_out, NULL, 0);

#ifdef SUPPORT_ULTRASENSE
        // for ultrasense
        if (port != 0)
        {
            if (output->pipeline_playback_in)
            {
                noti ("remove pipeline %s\n", apipeline_get_name (output->pipeline_playback_in));
                bm_unregister_port_forward (block, PORT_IN, port);
                apipeline_del (output->pipeline_playback_in);
                output->pipeline_playback_in = NULL;
            }
        }
#endif
    }

    return 0;
}

static int output_pre_connect (struct aud_block_info *block, int port, bool in)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (in)
    {
        if (output->output_type == OUTPUT_ARC)
            aimc_send_command (NULL, ADEC_CMD_START, 0, output->uid_out, NULL, 0);

#ifdef SUPPORT_ULTRASENSE
        // for ultrasense
        if (port != 0)
        {
            int uid_tail;

            noti ("connect to port %d of output block...\n", port);
            if (!output->pipeline_playback_in)
            {
                int preferred_proc = bm_get_preffered_processor (block);

                output->pipeline_playback_in =
                    apipeline_new2 (preferred_proc, "output_from_playback");
            }
            output->uid_queue_playback_in =
                apipeline_appendf (output->pipeline_playback_in, "queue");
            output->uid_bypass_playback_in =
                apipeline_prependf (output->pipeline_playback_in, "bypass");
            uid_tail = apipeline_tail (output->pipeline_playback_in);
            aimc_module_connect (uid_tail, 0, output->uid_outctrl, port);

            noti ("register port forwading.. %d -> %d\n", port, 0);
            bm_register_port_forward (block, PORT_IN, port, output->pipeline_playback_in, 0);
        }
#endif
    }

    return 0;
}

static int output_post_connect (struct aud_block_info *block, int port, bool in)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (in)
    {
        output_set_delay (block, output->delay);

        if (output->output_type == OUTPUT_ARC)
            audio_hal_earc_set_mute (false);
        output_set_mute (block, output->mute);
    }

    return 0;
}

static struct audio_block_impl block_impl = {
    .block_info_size = sizeof (struct aud_output_info),
    .block_type = "output",
    .preffered_processor = ADEC_CORE_DSP1,
    .constructor = output_create,
    .destructor = output_destroy,
    .suspend = output_suspend,
    .resume = output_resume,
    .pre_disconnect = output_pre_disconnect,
    .post_disconnect = output_post_disconnect,
    .pre_connect = output_pre_connect,
    .post_connect = output_post_connect,
};

void output_initializer (void)
{
    bm_block_registry (&block_impl);
}

int output_get_format (struct aud_block_info *block, struct output_format *output_format)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (!output_format)
    {
        error ("output_format is NULL.\n");
        return -1;
    }

    output_format->codec = output->codec;
    if (output->acmod == 7)
        output_format->channel = 6;
    else
        output_format->channel = output->channel;

    output_format->sample_rate = output->sample_rate;

    info ("%s codec : %s, ch : %d, sample_rate : %d.\n", OUTPUT_TO_STR (output),
        output_codec_str[output_format->codec], output_format->channel, output_format->sample_rate);

    return 0;
}

int output_get_bc_write_time (struct aud_block_info *block, unsigned long long *bc_write_time)
{
    struct aud_output_info *output = (struct aud_output_info *) block;

    if (output)
    {
        ClockCmdGetBCWriteTime output_time = { 0, };

        aimc_send_command_return (NULL, CLOCK_CMD_GET_BC_WRITE_TIME, 0,
            output->uid_out, (void *) &output_time, sizeof (ClockCmdGetBCWriteTime));

        *bc_write_time = output_time.bc_write_time;

        info ("%s bc_write_time : %llu\n", OUTPUT_TO_STR (output), *bc_write_time);
    }
    else
    {
        info ("output is null\n");
        return -1;
    }

    return 0;
}
