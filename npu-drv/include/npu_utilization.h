/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2022 by LG Electronics Inc.
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
 *  npu utilization header
 *
 *  author      Dongmin Kwon (dongmin.kwon@lge.com)
 *  version     0.1
 *  date        2022.05.31
 *
 */

#ifndef _NPU_UTILIZATION_H
#define _NPU_UTILIZATION_H

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
struct npu_dbg_info
{
    int period;
    unsigned long long start_time;
    unsigned long long end_time;
    unsigned long long acc_ms;
};

struct npu_util_que_node {
	struct list_head list;
    struct npu_dbg_info *data;
};

struct npu_util_que_ctx {
	struct list_head head;
	unsigned int node_cnt;
	struct mutex lock;
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/
int npu_utilization_proc_init(void);
void npu_utilization_proc_exit(void);
int iommuinfo_utilization_proc_init(void);
void iommuinfo_utilization_proc_exit(void);

void *npu_util_que_open(void);
int npu_util_que_close(void *id);
int npu_util_que_push(void *id, void *data);
struct npu_dbg_info *npu_util_que_pop(void *id);
unsigned int npu_util_que_get_node_cnt(void *id);
unsigned int npu_util_que_all_clear(void *id);

#endif /* _NPU_UTILIZATION_H */
