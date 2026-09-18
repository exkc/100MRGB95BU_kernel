/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2021 by LG Electronics Inc.
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
 *  interface header for audio dsp
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2021.02.09
 *
 */

#ifndef _DSP_CONTROL_H_
#define _DSP_CONTROL_H_

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/
#if defined(CHIP_NAME_o22)
#define NUM_OF_DSP      (4) //current used : 3, max : 4
#elif defined(CHIP_NAME_m23)
#define NUM_OF_DSP      (3)
#elif defined(CHIP_NAME_o24)
#define NUM_OF_DSP      (4)
#elif defined(CHIP_NAME_o26)
#define NUM_OF_DSP      (4)
#else
#define NUM_OF_DSP      (2)
#endif

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
 * Initialize DSP control
 *
 * @details
 * DSP control 초기화
 *
 * @return result of function call
 * @see
 */
int __init aud_dsp_control_init (void);

/**
 * @brief
 * Deinitialize DSP control
 *
 * @details
 * DSP control 사용 종료
 *
 * @see
 */
void __exit aud_dsp_control_exit (void);

/**
 * @brief
 * Reset dsp
 *
 * @details
 * dsp reset
 *
 * @see
 */
int aud_dsp_reset (void);
int _aud_dsp_reset (void);

/**
 * @brief
 * Halt dsp
 *
 * @details
 * dsp halt
 *
 * @see
 */
void aud_dsp_halt (void);


void aud_dsp_turn_on (int dsp_num);
void aud_dsp_turn_off (int dsp_num);

#endif  /* _DSP_CONTROL_H_ */

