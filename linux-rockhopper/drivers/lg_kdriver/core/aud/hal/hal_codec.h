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
 *  interface header for audio codec device
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.08.13
 *
 */

#ifndef _HAL_CODEC_H_
#define _HAL_CODEC_H_

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

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/**
 * @brief
 * Initialize hardware
 *
 * @details
 * Codec hardware 초기화
 *
 * @return result of function call
 * @see
 */
int aud_hal_codec_init (void);

/**
 * @brief
 * Deinitialize hardware
 *
 * @details
 * Codec hardware 사용 종료 시 호출
 *
 * @see
 */
void aud_hal_codec_exit (void);

/**
 * @brief
 * Set codec port number
 *
 * @details
 * Codec port number is enabled
 *
 * @return result of function call
 * @see
 */
int aud_hal_codec_set_adc_port_number (unsigned int number);

#ifdef SUPPORT_SOUNDBAR
/**
 * @brief
 * Set codec i2s input
 *
 * @details
 * Sound bar i2s setting is not different from tv.
 *
 * @return result of function call
 * @see
 */

int aud_hal_codec_set_i2s_input (void);
#endif

#endif  /* _HAL_CODEC_H_ */
