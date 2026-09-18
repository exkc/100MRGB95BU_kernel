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
 *  interface header for audio clock device
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.08.13
 *
 */

#ifndef _HAL_CLOCK_H_
#define _HAL_CLOCK_H_

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define CLOCK_CENTER            71
#define CLOCK_MIN               1
#define CLOCK_MAX               141
#define TABLE_MIN               61
#define TABLE_MAX               81
#define TABLE_LOW_TO_HIGH       21
#define TABLE_HIGH_TO_LOW       121
#define CLOCK_LOW               4
#define CLOCK_HIGH              4

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/**
 * @brief
 * Initialize hardware
 *
 * @details
 * Clock hardware 초기화
 *
 * @return result of function call
 * @see
 */
int aud_hal_clock_init (void);

/**
 * @brief
 * Deinitialize hardware
 *
 * @details
 * Clock hardware 사용 종료 시 호출
 *
 * @see
 */
void aud_hal_clock_exit (void);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int aud_hal_set_speaker_sample_rate (unsigned int sample_rate);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int aud_hal_set_speaker_channel (unsigned int channel);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int aud_hal_set_speaker_dto_rate (unsigned int dto_rate);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
unsigned int aud_hal_get_speaker_fcw (void);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int aud_hal_set_spdif_sample_rate (unsigned int sample_rate);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int aud_hal_set_spdif_channel (unsigned int channel);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int aud_hal_set_spdif_dto_rate (unsigned int dto_rate);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
unsigned int aud_hal_get_spdif_fcw (void);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int aud_hal_set_arc_sample_rate (unsigned int sample_rate);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int aud_hal_set_arc_channel (unsigned int channel);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
int aud_hal_set_arc_dto_rate (unsigned int dto_rate);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
unsigned int aud_hal_get_arc_fcw (void);

/**
 * @brief
 *
 *
 * @details
 *
 *
 * @see
 */
void aud_hal_switch_spdif_clock (bool onoff);

#endif  /* _HAL_CLOCK_H_ */
