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
 *  interface header for audio device
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.08.13
 *
 */

#ifndef _HAL_H_
#define _HAL_H_

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/types.h>

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
typedef uint32_t aud_bus_addr_t;

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/**
 * @brief
 * Initialize hardware
 *
 * @details
 * Hardware 초기화
 * booting 시 호출
 *
 * @return result of function call
 * @see
 */
int aud_hal_init (void);

/**
 * @brief
 * Initialize hardware
 *
 * @details
 * Hardware 초기화
 * booting & resume 시 호출
 *
 * @return result of function call
 * @see
 */
int aud_hal_initHW (void);

/**
 * @brief
 * Deinitialize hardware
 *
 * @details
 * Hardware 사용 종료 시 호출
 *
 * @see
 */
void aud_hal_exit (void);

/**
 * @brief
 * Get number of audio DSP
 *
 * @details
 * audio DSP 개수 return
 *
 * @see
 */
int aud_hal_get_number_of_dsp (void);

/**
 * @brief
 * Get Soundbar mode or not
 *
 * @details
 * true  : soundbar
 * false : TV
 * @see
 */
bool aud_hal_is_soundbar (void);

/**
 * @brief
 * Do chip support DTS?
 *
 * @details
 * true/false
 *
 * @see
 */
bool aud_hal_dts_supported (void);

/**
 * @brief
 * Set axi gate keeper
 *
 * @details
 * Set axi gate keeper.
 * Only for O24
 *
 * @see
 */
int aud_hal_set_axi_gk (void);

/**
 * @brief
 * Get audio bus address
 *
 * @details
 * 주어진 address 를 audio bus address 로 변환
 *
 * @param address physical address
 * @see
 */
aud_bus_addr_t aud_hal_phys_to_aud_bus (phys_addr_t address);

/**
 * @brief
 * Set ADC port number
 *
 * @details
 * Audio ADC port is enabled
 *
 * @param number ADC port number
 * @see
 */
int aud_hal_set_adc_port_number (unsigned int number);

/**
 * @brief
 * get DSP program count
 *
 * @details
 * DSP 의 program count 값을 return
 *
 * @param dsp_num DSP number
 * @return program count of DSP
 * @see
 */
unsigned int aud_hal_get_dsp_pc (unsigned int dsp_num);

/**
 * @brief
 * get gstcc
 *
 * @details
 * gstc register 를 return
 *
 * @return gstc value
 * @see
 */
unsigned int aud_hal_get_gstc (void);

/**
 * @brief
 * Do chip support audio f/w secure loading?
 *
 * @details
 * true/false
 *
 * @see
 */
bool aud_hal_secure_loading_supported (void);

/**
 * @brief
 * get 33bits gstcc
 *
 * @details
 * gstc register 를 return
 *
 * @return gstc value
 * @see
 */
unsigned long long aud_hal_get_gstc_33bits (void);
#endif  /* _HAL_H_ */
