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
 *  lne device driver header
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.06.18
 *
 */

#ifndef _LNE_DRV_H
#define _LNE_DRV_H

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
struct lne_buffer
{
    phys_addr_t phys_addr;
    void *mapped;
    unsigned int size;
};

struct lne_run_param {
    void *instance;
    struct lne_buffer firmware;
    struct lne_buffer weight;
    struct lne_buffer input;
    struct lne_buffer output;
    struct lne_buffer firmware2;
    struct lne_buffer weight2;
    struct lne_buffer input2;
    struct lne_buffer output2;
};

struct lne_hw {
    const char *name;

    int (*init) (struct lne_hw *);
    int (*reset) (struct lne_hw *);
    int (*run) (struct lne_hw *, struct lne_run_param *);
    int (*set) (struct lne_run_param *);
    int (*net_en) (unsigned int);

    void *private;
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/
int lne_hw_register (struct lne_hw *hw);

#endif /* _LNE_DRV_H */
