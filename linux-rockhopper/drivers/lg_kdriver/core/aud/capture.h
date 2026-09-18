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
 *  @file capture.h
 *  @addtogroup capture
 *
 *  \section interface Interface
 *
 *              (up)
 *      (left) CAPTURE (right)
 *              (down)
 *
 *  (up): ALSA Kcontrol, ALSA Capture, Media Audio, libaec-fe(WoV)\n
 *  (down): capture (FW), hma\n
 *  (left): Encoder, Decoder, Mixer, PDM(WoV), BC(WoV)\n
 *  (right): Renderer, memory(?)\n
 *
 *  \section dataflow  Data Flow
 *
 *  Media Fileplay: Decoder - Capture - Renderer\n
 *  ATV Encoding: Encoder - Capture - file\n
 *  Bluetooth Play: Mixer - Capture - memory\n
 *  PDM/BC Capture: PDM/BC - Capture - memory\n
 *
 *  \section controlflow  Control Flow
 *
 *  Start/Stop Capture: ALSA Capture/Media Audio/libaec-fe - Capture - capture\n
 *  Gain/Mute: ALSA KControl - Capture - capture\n
 *
 */

#ifndef _CAPTURE_H
#define _CAPTURE_H

#include "block.h"

/**
* Open Capture device
*
* @return SINT32 module id
* @see
*/
int OpenCapture (void);

/**
* Close Capture device
*
* @param id [in] module id
* @return SINT32 0 if successful
* @see
*/
int CloseCapture (int id);

/**
* Start Capture device
*
* @param id [in] module id
* @return SINT32 0 if successful
* @see
*/
int StartCapture (int id);

/**
* Stop Capture device
*
* @param id [in] module id
* @return SINT32 0 if successful
* @see
*/
int StopCapture (int id);

/**
* Set Capture parameters
*
* @param id [in] module id: int
* @param pStrCmd [in] parameters in string format ex) "gain=0x800000": char*
* @return SINT32 0 if successful
* @see
*/
int SetCaptureParam (int id, char *pStrCmd);

/**
* Get Capture parameters
*
* @param id [in] module id: int
* @param name [in] name of parameter: char*
* @param pRetValue [out] parameter got: int
* @return SINT32 0 if successful
* @see
*/
int GetCaptureParam (int id, char *name, int *pRetValue);

void aud_capture_initializer (void);
int aud_capture_set_gain (struct aud_block_info *block, unsigned int gain);
int aud_capture_set_sampling_freq (struct aud_block_info *block, unsigned int sampling_freq);
unsigned int aud_capture_get_sampling_freq (struct aud_block_info *block);
unsigned int aud_capture_get_out_channels (struct aud_block_info *block);
int aud_capture_set_out_bps (struct aud_block_info *block, unsigned int bps);
int aud_capture_set_in_channel (struct aud_block_info *block, unsigned int in_channel);
int aud_capture_set_out_channel (struct aud_block_info *block, unsigned int out_channel);
int aud_capture_set_generate_lfe (struct aud_block_info *block, bool generate_lfe);
int aud_capture_set_out_acmod (struct aud_block_info *block, unsigned int out_acmod);
int aud_capture_set_es (struct aud_block_info *block, bool es);
int aud_capture_set_dafc_mode (struct aud_block_info *block, bool onOff);
int aud_capture_set_aenc_header (struct aud_block_info *block, bool use_aenc_header);
int aud_capture_set_disable (struct aud_block_info *block, bool disable);
int aud_capture_set_mute (struct aud_block_info *block, bool mute);
int aud_capture_set_read_pointer (struct aud_block_info *block, unsigned int rd_ptr);

int aud_capture_get_out_samples (struct aud_block_info *block);
int aud_capture_set_out_samples (struct aud_block_info *block, unsigned int out_samples);
#endif //_CAPTURE_H
