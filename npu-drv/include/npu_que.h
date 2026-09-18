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
 *  npu job queue header
 *
 *  author      Dongmin Kwon (dongmin.kwon@lge.com)
 *  version     0.1
 *  date        2022.04.13
 *
 */

#ifndef _NPU_QUE_H
#define _NPU_QUE_H

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/types.h>

#include "npu_drv.h"
/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct npu_que_node {
	struct list_head list;
    struct npu_buffer_info *data;
};

struct npu_que_ctx {
	struct list_head head;
	unsigned int node_cnt;
	struct mutex lock;
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/
void *npu_que_open(void);
int npu_que_close(void *id);

int npu_que_push(void *id, void *data);
struct npu_buffer_info *npu_que_pop(void *id);
unsigned int npu_que_get_node_cnt(void *id);
unsigned int npu_que_all_clear(void *id);

struct npu_buffer_info *npu_que_peek(void *id);
struct npu_buffer_info *npu_que_peek_last(void *id);

int npu_que_asc_sort_push(void *id, void *data);

bool npu_que_check_node_by_id(void *id, void* inst_id);
int npu_que_check_npu_done_by_id(void *id, void* inst_id);
struct npu_buffer_info *npu_que_find_pop_by_id(void *id, void* inst_id);
unsigned int npu_que_find_clear_by_id(void *id, void* inst_id);

struct npu_buffer_info *npu_que_find_pop_by_job_id(void *id, int job_id);
struct npu_buffer_info *npu_que_find_by_job_id(void *id, int job_id);

void npu_que_dispay(void *id);

#endif /* _NPU_QUE_H */
