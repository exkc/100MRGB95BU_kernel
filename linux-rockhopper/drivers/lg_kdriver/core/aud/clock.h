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
 *  @file clock.h
 *
 *  Audio driver implementation for  audio output block.
 *  Clock functions manage clock of Speaker, Headphone(HP), Optic(SPDIF), and ARC output(include eARC).
 *
 *  @author	    wonchang.shin (wonchang.shin@lge.com)
 *  @version    0.1
 *  @date       2020/10/26
 *
 *  @addtogroup output
 *  @{
 */

#ifndef _CLOCK_H_
#define _CLOCK_H_

/**
 * @brief
 * enumeration for output type
 *
 * @details
 * type of output device
 */
enum aud_clock_output
{
    CLOCK_OUTPUT_SPEAKER,
    CLOCK_OUTPUT_HP,
    CLOCK_OUTPUT_OPTIC,
    CLOCK_OUTPUT_ARC,
#ifdef SUPPORT_SOUNDBAR
    CLOCK_OUTPUT_PC,
#endif
    CLOCK_OUTPUT_MAX,
};

/**
 * @brief
 * enumeration for source type
 *
 * @details
 * type of source clock
 */
enum aud_clock_source
{
    CLOCK_SOURCE_UNKNOWN,   //Unknown
    CLOCK_SOURCE_DTV0,      //DTV 0 to SPK(System)
    CLOCK_SOURCE_DTV1,      //DTV 1 to SPK(System)
    CLOCK_SOURCE_ATV,       //ATV to SPK
    CLOCK_SOURCE_HDMI,      //HDMI to SPK
    CLOCK_SOURCE_ADC,       //ADC to SPK
    CLOCK_SOURCE_GSTC0,     //Fileplay to SPK
    CLOCK_SOURCE_GSTC1,     //ATSC 3.0 to SPK
#ifdef SUPPORT_SOUNDBAR
    CLOCK_SOURCE_I2S,       //I2S to SPK
#endif
    CLOCK_SOURCE_MAX,       //max
};

/**
 *  @struct pll_control_info
 */
struct pll_control_info
{
    unsigned long long interrupt_count;             ///< interrupt_count
    unsigned long long reference_clock_count;       ///< reference_clock_count
    unsigned long long reserved00;                  ///< reserved00
    unsigned long long reserved01;                  ///< reserved01
};

/**
 * @brief
 * Enable clock info for input
 *
 * @details
 * input 에 대한 clock 정보 활성화
 *
 * @param index input index
 * @param source clock source
 * @param uid input module uid
 * @return result of function call
 * @see
 */
int aud_clock_enable_input (unsigned int index, enum aud_clock_source source, int uid);

/**
 * @brief
 * Disable clock info for input
 *
 * @details
 * input 에 대한 clock 정보 비활성화
 *
 * @param index input index
 * @return result of function call
 * @see
 */
int aud_clock_disable_input (unsigned int index);

/**
 * @brief
 * Update clock info for input
 *
 * @details
 * input 에 대한 clock 정보 갱신
 *
 * @param index input index
 * @param channel number of channels
 * @param sample_rate sampel rate
 * @return result of function call
 * @see
 */
int aud_clock_update_input (unsigned int index, unsigned int channel, unsigned int sample_rate);

/**
 * @brief
 * Enable clock for output
 *
 * @details
 * Output device 에 대한 clock 활성화
 *
 * @param output output type
 * @param uid input module uid
 * @return result of function call
 * @see
 */
int aud_clock_enable_output (enum aud_clock_output output, int uid);

/**
 * @brief
 * Disable clock for output
 *
 * @details
 * Output device 에 대한 clock 비활성화
 *
 * @param output output type
 * @return result of function call
 * @see
 */
int aud_clock_disable_output (enum aud_clock_output output);

/**
 * @brief
 * Set index of input for output
 *
 * @details
 * Output device 의 input index 를 설정
 *
 * @param index input index
 * @return result of function call
 * @see
 */
int aud_clock_set_input_index (enum aud_clock_output output, unsigned int index);

/**
 * @brief
 * Update clock info for output
 *
 * @details
 * Output 에 대한 clock 정보 갱신
 *
 * @param sample_rate sample rate
 * @param bypass bypass enable / disable
 * @return result of function call
 * @see
 */
int aud_clock_update_output (enum aud_clock_output output, unsigned int sample_rate, unsigned int channel, bool bypass);

/**
 * @brief
 * get pll control info for speaker
 *
 * @details
 * speaker output의 irq_count, clock count를 전달
 *
 * @param struct pll_control_info
 * @return result of function call
 * @see
 */
int aud_clock_get_pll_control_info (enum aud_clock_output output, struct pll_control_info *pll_control_info);

#endif /* _CLOCK_H_ */

