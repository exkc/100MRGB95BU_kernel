/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/


/** @file aud_kapi.h
 *
 *  @author     Jihoon Lee (gaius.lee@lge.com)
 *  @version    0.1
 *  @date       2020.09.28
 *  @note       The simple wrapper function for audio kernel module.
 *
 */

#ifndef _AUD_KAPI_CLOCK_H_
#define _AUD_KAPI_CLOCK_H_

#include "aud_kapi.h"

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define ACLK_IOC_MAGIC                       'C'

/*----------------------------------------------------------------------------------------
    IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define ACLK_IOR_GET_GSTC                    _IOR(ACLK_IOC_MAGIC, 1, unsigned int)

typedef enum aud_clock_type {
    AUD_CLK_TYPE_PCR_M        =   0x1,        /**< main PCR. */
    AUD_CLK_TYPE_PCR_A        =   0x2,        /**< associate PCR. */
    AUD_CLK_TYPE_NO_PCR       =   0x11,       /**< no PCR. */
    AUD_CLK_TYPE_GSTC         =   0x100,      /**< global STC 0. */
    AUD_CLK_TYPE_GSTC_1       =   0x101,      /**< global STC 1. */
    AUD_CLK_TYPE_MASTER       =   0x200,      /**< audio master. */
} aud_clock_type_t;

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _AUD_KAPI_CLOCK_H_ */
