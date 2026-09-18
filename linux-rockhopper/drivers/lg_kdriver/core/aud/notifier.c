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
 *  @file notifier.c
 *
 *  Audio driver implementation for  audio notifier.
 *  Audio notifier notifies alsa driver when input changed and kernel driver
 *  when output changed.
 *
 *  @author	wonchang.shin (wonchang.shin@lge.com)
 *  @version    0.1
 *  @date       2020/12/21
 *
 *  @addtogroup sndout
 *  @{
 */
#include <linux/module.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <sound/soc.h>
#include <sound/pcm_params.h>

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "log.h"
#include "audio_kapi.h"

#include "block.h"
#include "decoder.h"
#include "mixer.h"
#include "se.h"
#include "output.h"
#include "encoder.h"
#include "renderer.h"
#include "block_manager.h"
#include "clock.h"
#include "notifier.h"

#include "alsa/alsa_support_sndout.h"

logm_define (notifier, log_level_noti);
#define trace(fmt,args...)  logm_trace(notifier,fmt,##args)
#define debug(fmt,args...)  logm_debug(notifier,fmt,##args)
#define info(fmt,args...)   logm_info(notifier,fmt,##args)
#define noti(fmt,args...)   logm_noti(notifier,fmt,##args)
#define warn(fmt,args...)   logm_warning(notifier,fmt,##args)
#define error(fmt,args...)  logm_error(notifier,fmt,##args)

#ifdef SUPPORT_DTSX
bool dtsx_bitstream_passthrough = false;
#endif

#define PLAY_SPEED_INDEX_MAX    2
unsigned int play_speed[PLAY_SPEED_INDEX_MAX] = { 1000, 1000 };

void notifier_output_changed (void)
{
    renderer_change_output ();

    debug ("output changed\n");
}

void notifier_input_changed (void)
{
    sndout_connect_output ();

    debug ("input changed\n");
}

#ifdef SUPPORT_DTSX
void notifier_set_dtsx_bitstream_passthrough (bool bitstream_passthrough)
{
    dtsx_bitstream_passthrough = bitstream_passthrough;

    noti ("set dtsx bitstream-passthrough: %d\n", bitstream_passthrough);
}

bool notifier_get_dtsx_bitstream_passthrough (void)
{
    return dtsx_bitstream_passthrough;
}
#endif

void notifier_set_play_speed (int index, unsigned int speed)
{
    if (index < PLAY_SPEED_INDEX_MAX && index >= 0)
    {
        if (play_speed[index] != speed)
        {
            play_speed[index] = speed;
            sndout_connect_output ();
        }
    }

    noti ("set play speed: index %d, speed %d\n", index, speed);
}

unsigned int notifier_get_play_speed (int index)
{
    unsigned int speed = 1000;

    if (index < PLAY_SPEED_INDEX_MAX && index >= 0)
        speed = play_speed[index];

    return speed;
}
