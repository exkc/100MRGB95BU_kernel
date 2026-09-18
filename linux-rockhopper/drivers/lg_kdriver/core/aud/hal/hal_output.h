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
 *
 *  interface header for audio output device
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.08.13
 *
 */

#ifndef _HAL_OUTPUT_H_
#define _HAL_OUTPUT_H_

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
enum audio_hal_output_format {
    AUDIO_HAL_OUTPUT_PCM,
    AUDIO_HAL_OUTPUT_ES,
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/**
 * @brief
 * Initialize hardware
 *
 * @details
 * earc hardware 초기화
 * resume 에서 호출
 *
 * @return result of function call
 * @see
 */
int aud_hal_output_init_earc (void);

/**
 * @brief
 * Initialize hardware
 *
 * @details
 * Output hardware 초기화
 * booting 시에만 호출
 *
 * @return result of function call
 * @see
 */
int aud_hal_output_init (void);

/**
 * @brief
 * Deinitialize hardware
 *
 * @details
 * Output hardware 사용 종료 시 호출
 *
 * @see
 */
void aud_hal_output_exit (void);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void aud_hal_output_set_number_of_i2s (int number);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int aud_hal_output_optic_light_on (bool on);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int audio_hal_ioremap_earc (void);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void audio_hal_earc_set_on (bool on);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void audio_hal_earc_set_scms (unsigned int scms);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void audio_hal_earc_set_category_code (unsigned int category_code);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void audio_hal_earc_set_output_format (enum audio_hal_output_format output_format,
    unsigned int sampling_freq);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void audio_hal_earc_set_mute (bool on);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void audio_hal_earc_set_audio_mode (unsigned int audio_mode);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void audio_hal_earc_set_channel (unsigned int channel, unsigned int acmod);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void audio_hal_earc_clear_interrupt (unsigned int int_status);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void audio_hal_earc_set (void);

void audio_hal_speaker_start (bool on);
void audio_hal_hp_start (bool on);
void audio_hal_spdif_start (bool on);
#ifdef SUPPORT_SOUNDBAR
void audio_hal_pc_start (bool on);
#endif
void audio_hal_arc_start (bool on);

#endif  /* _HAL_OUTPUT_H_ */
