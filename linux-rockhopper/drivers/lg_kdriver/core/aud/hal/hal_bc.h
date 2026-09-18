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
 *  interface header for audio bc device
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.08.13
 *
 */

#ifndef _HAL_BC_H_
#define _HAL_BC_H_

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
 * Buffer control hardware 들 초기화
 *
 * @return result of function call
 * @see
 */
int aud_hal_bc_init (void);

/**
 * @brief
 * Deinitialize hardware
 *
 * @details
 * Buffer control hardware 사용 종료 시 호출
 *
 * @see
 */
void aud_hal_bc_exit (void);

/**
 * @brief
 * Initialize bc buffer hardware
 *
 * @details
 * 특정 buffer control hardware 초기화
 *
 * @return result of function call
 * @see
 */
int aud_hal_bc_buffer_init (const char *name);

/**
 * @brief
 * Enable bc hardware
 *
 * @details
 * 특정 buffer control hardware 활성화
 *
 * @return result of function call
 * @see
 */
int aud_hal_bc_enable (const char *name);

/**
 * @brief
 * Disable bc hardware
 *
 * @details
 * 특정 buffer control hardware 비활성화
 *
 * @return result of function call
 * @see
 */
int aud_hal_bc_disable (const char *name);

#endif  /* _HAL_BC_H_ */
