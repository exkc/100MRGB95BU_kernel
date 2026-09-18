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
 *  interface header for audio ipc
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.08.13
 *
 */

#ifndef _HAL_IPC_H_
#define _HAL_IPC_H_

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
 * Read ipc register value
 *
 * @details
 * IPC register 값을 읽음
 *
 * @param[in] offset offset of IPC register
 * @return register value
 * @see
 */
unsigned int aud_hal_ipc_read (unsigned int offset);

/**
 * @brief
 * Write value to ipc register
 *
 * @details
 * IPC register 에 값을 씀
 *
 * @param[in] offset offset of IPC register
 * @param[in] value write value
 * @see
 */
void aud_hal_ipc_write (unsigned int offset, unsigned int value);

#endif  /* _HAL_IPC_H_ */
