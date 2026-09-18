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

#ifndef _AUD_KAPI_DEBUG_H_
#define _AUD_KAPI_DEBUG_H_

#include <linux/kernel.h>
#include <linux/ioctl.h>


#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define ADBG_IOC_MAGIC                       'G'

/*----------------------------------------------------------------------------------------
    IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/

#define ADBG_IOW_OPEN_BLOCK                  _IOW(ADBG_IOC_MAGIC, 1, adbg_open_block_t)
#define ADBG_IOW_REN_SET_PARAM               _IOW(ADBG_IOC_MAGIC, 2, adbg_ren_param_t)
#define ADBG_IOR_REN_GET_PARAM               _IOWR(ADBG_IOC_MAGIC, 3, adbg_ren_param_t)
#define ADBG_IOR_SUSPEND                     _IO(ADBG_IOC_MAGIC, 4)
#define ADBG_IOR_RESUME                      _IO(ADBG_IOC_MAGIC, 5)
#define ADBG_IO_RESET                        _IO(ADBG_IOC_MAGIC, 6)

/**
 * Open Block for Debug
 */
typedef struct adbg_open_block {
    char name[32];
    int len_name;
    int index;
} adbg_open_block_t;

/**
 * Open Block for Debug
 */
typedef struct adbg_ren_param {
    char args[256];     /* set/get param string */
    int ret_val;        /* for get param */
} adbg_ren_param_t;

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _AUD_KAPI_DEBUG_H_ */

