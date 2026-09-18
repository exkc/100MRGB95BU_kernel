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
 *  header for register utility
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.08.13
 *
 */

#ifndef _REG_UTIL_H_
#define _REG_UTIL_H_

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/types.h>
#include <linux/io.h>
#include <linux/slab.h>

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define AUD_REG_SHDW(_m)            (g_aud_regs.shdw._m)
#define AUD_REG_PHYS(_m)            (g_aud_regs.phys._m)

#define AUD_REG_INIT(_m, _base)     \
({                                                                              \
    size_t size = sizeof (typeof (*AUD_REG_PHYS(_m)));                          \
    AUD_REG_PHYS(_m) = (typeof (AUD_REG_PHYS(_m)))ioremap (_base, size);        \
    AUD_REG_SHDW(_m) = (typeof (AUD_REG_PHYS(_m)))kmalloc (size, GFP_KERNEL); \
    !(AUD_REG_PHYS(_m) && AUD_REG_SHDW(_m));                                    \
})

#define AUD_REG_DEINIT(_m)          \
do {                                                                            \
    if (AUD_REG_SHDW(_m)) kfree ((void *)AUD_REG_SHDW(_m));                     \
    if (AUD_REG_PHYS(_m)) iounmap ((void *)AUD_REG_PHYS(_m));                   \
} while (0)

#define AUD_REG_RdFL(_m,_r)         ((AUD_REG_SHDW(_m)->_r)=(AUD_REG_PHYS(_m)->_r))
#define AUD_REG_WrFL(_m,_r)         ((AUD_REG_PHYS(_m)->_r)=(AUD_REG_SHDW(_m)->_r))

#define AUD_REG_Rd(_m,_r)           (*(volatile uint32_t *)(&(AUD_REG_PHYS(_m)->_r)))
#define AUD_REG_Wr(_m,_r,_v)        (AUD_REG_Rd(_m,_r)=((uint32_t)(_v)))

#define AUD_REG_RdFd(_m,_r,_f)      (AUD_REG_SHDW(_m)->_r._f)
#define AUD_REG_WrFd(_m,_r,_f,_v)   ((AUD_REG_SHDW(_m)->_r._f)=(_v))

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/
extern struct aud_regs g_aud_regs;

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

#endif  /* _REG_UTIL_H_ */
