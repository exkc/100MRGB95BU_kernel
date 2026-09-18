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
 *  npu driver header
 *
 *  author      Dongmin Kwon (dongmin.kwon@lge.com)
 *  version     0.1
 *  date        2022.04.13
 *
 */

#ifndef _NPU_DRV_H
#define _NPU_DRV_H

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/
#define IDL_MAGIC       0x49444C    //'IDLE'
#define USE_MAGIC       0x555345    //'USE'

#define DMA_BIT_MASK(n)	(((n) == 64) ? ~0ULL : ((1ULL<<(n))-1))

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/types.h>
#include <linux/scatterlist.h>
#include <linux/platform_device.h>

#include "npu_api.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct npu_cache_data {
    void *ptr;
    unsigned int size;
};

struct npu_buffer {
    unsigned int magic_num;
    MEMORY_TYPE_T memory_type;
    phys_addr_t phys_addr;
    void *va_addr;
    struct npu_cache_data cache_data;
    unsigned int size;
    unsigned int core_idx;
    struct sg_table sgt;
    struct mutex mutex_lock;
};

struct npu_buffer_info {
    struct npu_buffer *input_buf;
	int 	number_of_input_buf;
    struct npu_buffer *output_buf;
	int 	number_of_output_buf;
    struct npu_buffer inter_output_buf;
    struct npu_inst *inst_id;
    int  job_id;
    bool npu_done;
};

struct npu_reg_map {
    unsigned int address;
    unsigned int value;
};

struct npu_prepare_param {
    struct npu_buffer  program;
    struct npu_buffer  weight;
    struct npu_buffer  feature;
    int                reg_num;
    struct npu_reg_map *reg_info;
    int               stride_num;
    unsigned int    *stride_info;
    bool                data_img;
    int                 affinity;
    int                 core_idx;
    bool             enable_prot;
};

struct npu_run_param {
    struct npu_buffer *input;
	int 	number_of_input;
    struct npu_buffer output;
    int  npu_latency;
    /* point to npu_prepare_param */
    struct npu_buffer *program;
    struct npu_buffer *weight;
    struct npu_buffer *feature;
};

struct npu_tensor_info {
    TENSOR_TYPE_T type;
    unsigned int  data_size;
    unsigned int  dim_size;
};

struct debug_method
{
    unsigned int num_cnt;
    unsigned int overflow_cnt;
    unsigned long long start_time;
    unsigned long long end_time;
    unsigned long long acc_ms;
    unsigned long long sum_ms;
    unsigned long long avg_ms;
    uint32_t fps;
    int npu_latency;
    spinlock_t dbg_mtd_lock;
};

struct npu_inst
{
    int	period;
    int	last_req_id;
    bool set_exec_mem;
    struct mutex mutex_lock;
    struct mutex sync_lock;

    struct npu_cache_data cache_prog;
    struct npu_cache_data cache_param;
    unsigned int feature_size;

    struct npu_prepare_param prepare_param;
    struct npu_run_param run_param;

    wait_queue_head_t work_wait_rsp;

    unsigned int input_num;
    unsigned int output_num;
    unsigned int input_size;
    unsigned int output_size;
    unsigned int*   input_offset;
    unsigned int*   output_offset;
    struct npu_tensor_info *input_info;
    struct npu_tensor_info *output_info;
    struct debug_method dbg_mtd;
    struct debug_method cpy_dbg_mtd;
    struct debug_method prog_dbg_mtd;
    struct debug_method weigh_dbg_mtd;
    struct debug_method sche_dbg_mtd;
    unsigned int procces_id;
    unsigned int user_procces_type;
    struct list_head list;
    struct timer_list timer_utilization;
};

struct npu_hw {
	const char *name;

	int (*init)(struct npu_hw *);
	int (*reset)(struct npu_hw *, unsigned int);
	int (*prepare)(struct npu_hw *, unsigned int, struct npu_prepare_param *);
	int (*run)(struct npu_hw *, unsigned int, struct npu_run_param *);
	int (*release)(struct npu_hw *);
	int (*pmctrl)(struct npu_hw *, bool);

	void *private;
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/
#ifdef USE_IOMMU
#include <linux/platform_device.h>
int npu_hw_register(struct platform_device *pdev, struct npu_hw *hw);
#else
extern int npu_hw_register(struct npu_hw *hw);
#endif
extern int npu_get_utilization(void);
extern int iommuinfo_get_utilization(void);

#endif /* _NPU_DRV_H */
