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
 *  @file notifier.h
 *
 *  Audio driver implementation for  audio notifier.
 *  Audio notifier notifies alsa driver when input changed and kernel driver
 *  when output changed.
 *
 *  @author	    wonchang.shin (wonchang.shin@lge.com)
 *  @version    0.1
 *  @date       2020/12/24
 *
 *  @addtogroup output
 *  @{
 */

#ifndef _NOTIFIER_H_
#define _NOTIFIER_H_

void notifier_output_changed (void);
void notifier_input_changed (void);

#ifdef SUPPORT_DTSX
void notifier_set_dtsx_bitstream_passthrough (bool bitstream_passthrough);
bool notifier_get_dtsx_bitstream_passthrough (void);
#endif

void notifier_set_play_speed (int index, unsigned int speed);
unsigned int notifier_get_play_speed (int index);


#endif /* _NOTIFIER_H_ */
/** @} */

