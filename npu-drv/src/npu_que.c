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
 *  npu job queue
 *
 *  author      Dongmin Kwon (dongmin.kwon@lge.com)
 *  version     0.1
 *  date        2022.04.13
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>

#include "npu_que.h"
#include "logm.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)      logm_trace(npu_drv, fmt, ##args)
#define debug(fmt,args...)      logm_debug(npu_drv, fmt, ##args)
#define info(fmt,args...)       logm_info(npu_drv, fmt, ##args)
#define noti(fmt,args...)       logm_noti(npu_drv, fmt, ##args)
#define warn(fmt,args...)       logm_warning(npu_drv, fmt, ##args)
#define error(fmt,args...)      logm_error(npu_drv, fmt, ##args)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/

/*==============================================================================
    Implementation Group
==============================================================================*/
void *npu_que_open(void)
{
	struct npu_que_ctx *ctx = NULL;
	ctx = (struct npu_que_ctx *)kzalloc(sizeof(struct npu_que_ctx ), GFP_KERNEL);
	if(!ctx) {
		error("kmalloc fail\n");
        return NULL;
	}

	INIT_LIST_HEAD(&ctx->head);
	mutex_init(&ctx->lock);
	ctx->node_cnt = 0;
	info("%s [ctx:%p]\n", __func__, ctx);

	return (void*)ctx;
}

int npu_que_close(void *id) {
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *tmp = NULL, *node = NULL;
	unsigned int free_cnt = 0;

	ctx = (struct npu_que_ctx *)id;
	if(!ctx) {
		error("invalid argument\n");
		return -1;
	}

	mutex_lock(&ctx->lock);
    if(ctx->node_cnt)
    {
        list_for_each_entry_safe(node, tmp, &ctx->head, list) {
            kfree(node);
            free_cnt++;
        }
    }
	mutex_unlock(&ctx->lock);
	mutex_destroy(&ctx->lock);
	info("%s ctx:%p free_num:%d\n", __func__, ctx, free_cnt);
	kfree(ctx);

	return free_cnt;
}

int npu_que_push(void *id, void *data) {
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *node = NULL;
	volatile struct npu_inst * inst_id;

	ctx = (struct npu_que_ctx *)id;
	if(!ctx) {
		error("invalid argument\n");
		return -1;
	}

	node = (struct npu_que_node *)kzalloc(sizeof(struct npu_que_node), GFP_KERNEL);
	if(!node) {
		error("kmalloc fail\n");
        return -ENOMEM;
	}

	if(!data) {
		error("data NULL\n");
        if(node)
            kfree(node);
        return -1;
	}

	node->data = (struct npu_buffer_info *)data;
	mutex_lock(&ctx->lock);
	inst_id = node->data->inst_id;
	ctx->node_cnt++;
	list_add_tail(&node->list, &ctx->head);
	mutex_unlock(&ctx->lock);

	info("que_push_to_(0x%p) node:%p data:0x%p id:0x%p\n",
                ctx, node, data, inst_id);

	return 0;
}

struct npu_buffer_info *npu_que_pop(void *id) {
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *node = NULL;
	struct npu_buffer_info *data = NULL;

	ctx = (struct npu_que_ctx *)id;
	if (!ctx) {
		error("invalid argument.\n");
		return NULL;
	}

	mutex_lock(&ctx->lock);
	if (list_empty(&ctx->head)) {
		warn("ctx:%p, list is empty\n", ctx);
    	if(mutex_is_locked(&ctx->lock)) {
    		mutex_unlock(&ctx->lock);
    	}
		return NULL;
	}

	ctx->node_cnt--;
	node = list_entry(ctx->head.next, struct npu_que_node, list);
	data = node->data;
	list_del(&node->list);
	info("que_pop_from_(0x%p) node:%p data:0x%p id:0x%p\n",
            ctx, node, data, data->inst_id);
	kfree(node);
	mutex_unlock(&ctx->lock);

	return data;
}


unsigned int npu_que_get_node_cnt(void *id) {
	struct npu_que_ctx *ctx = NULL;
	unsigned int count = 0;

	ctx = (struct npu_que_ctx *)id;
	if (!ctx) {
		error("invalid argument\n");
		return 0;
	}

	mutex_lock(&ctx->lock);
	count = ctx->node_cnt;
	mutex_unlock(&ctx->lock);

	info("get_node_cnt_from_(0x%p) count:%d\n", ctx, count);

	return count;
}

unsigned int npu_que_all_clear(void *id) {
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *tmp = NULL, *node = NULL;
	unsigned int free_cnt = 0;

	ctx = (struct npu_que_ctx *)id;
	if(!ctx) {
		error("invalid argument\n");
		return 0;
	}

	mutex_lock(&ctx->lock);
    if(ctx->node_cnt)
    {
        list_for_each_entry_safe(node, tmp, &ctx->head, list) {
            kfree(node);
            free_cnt++;
        }
    }
	mutex_unlock(&ctx->lock);
	info("que_clear ctx:0x%p free_num:%d\n", ctx, free_cnt);

	return free_cnt;
}

//Get the first data in the queue
struct npu_buffer_info *npu_que_peek(void *id) {
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *node = NULL;
	struct npu_buffer_info *data = NULL;

	ctx = (struct npu_que_ctx *)id;
	if (!ctx) {
		error("invalid argument\n");
		return NULL;
	}

	mutex_lock(&ctx->lock);
	if (list_empty(&ctx->head)) {
		mutex_unlock(&ctx->lock);
		info("ctx:%p, list is empty\n", ctx);
		return NULL;
	}

	node = list_entry(ctx->head.next, struct npu_que_node, list);
	data = node->data;
	mutex_unlock(&ctx->lock);

	info("que_peek_from_(0x%p) node:0x%p data:0x%p\n", ctx, node, data);

	return data;
}

//Get last data in the queue
struct npu_buffer_info *npu_que_peek_last(void *id) {
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *node = NULL;
	struct npu_buffer_info *data = NULL;

	ctx = (struct npu_que_ctx *)id;
	if (!ctx) {
		error("invalid argument\n");
		return NULL;
	}

	mutex_lock(&ctx->lock);
	if (list_empty(&ctx->head)) {
		mutex_unlock(&ctx->lock);
		warn("ctx:%p, list is empty\n", ctx);
		return NULL;
	}

	node = list_last_entry(ctx->head.next, struct npu_que_node, list);
	data = node->data;
	mutex_unlock(&ctx->lock);

	info("que_peek_last_from_(0x%p) node:0x%p data:0x%p\n", ctx, node, data);

	return data;
}

bool npu_que_check_node_by_id(void *id, void* inst_id)
{
	struct npu_que_ctx *ctx = NULL;
    struct npu_que_node *tmp = NULL, *node = NULL;

	ctx = (struct npu_que_ctx *)id;
	if (!ctx) {
		error("invalid argument\n");
		return 0;
	}

    mutex_lock(&ctx->lock);
    if(ctx->node_cnt)
    {
        list_for_each_entry_safe(node, tmp, &ctx->head, list) {
            if(node->data->inst_id == inst_id){
                mutex_unlock(&ctx->lock);
                return true;
            }
        }
    }
    mutex_unlock(&ctx->lock);

    info("not_ready_check_node_from_(0x%p) [id:0x%p] \n", ctx, inst_id);

    return false;
}

int npu_que_check_npu_done_by_id(void *id, void* inst_id)
{
	struct npu_que_ctx *ctx = NULL;
    struct npu_que_node *tmp = NULL, *node = NULL;

	ctx = (struct npu_que_ctx *)id;
	if (!ctx) {
		error("invalid argument\n");
		return 0;
	}

    mutex_lock(&ctx->lock);
    if(ctx->node_cnt)
    {
        list_for_each_entry_safe(node, tmp, &ctx->head, list) {
            if(node->data->inst_id == inst_id){
                mutex_unlock(&ctx->lock);
                info("que_check_npu_done_from_(0x%p) node:%p npu_done:%d id:0x%p\n",
                            ctx, node, node->data->npu_done, inst_id);
                return node->data->npu_done;
            }
        }
    }
    mutex_unlock(&ctx->lock);

    info("not_ready_check_node_from_(0x%p) [id:0x%p] \n", ctx, inst_id);

    return -1;
}

int npu_que_asc_sort_push(void *id, void *data) {
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *tmp = NULL, *node = NULL;
	struct npu_que_node *new_node = NULL, *tag_node = NULL;
	int	period;

	ctx = (struct npu_que_ctx *)id;
	if(!ctx) {
		error("invalid argument\n");
		return -1;
	}

	new_node = (struct npu_que_node *)kzalloc(sizeof(struct npu_que_node), GFP_KERNEL);
	if(!new_node) {
		error("kmalloc fail\n");
        return -ENOMEM;
	}

	if(!data) {
		error("data NULL\n");
        if(new_node)
            kfree(new_node);
        return -1;
	}

	new_node->data = (struct npu_buffer_info *)data;
	mutex_lock(&ctx->lock);
	period = new_node->data->inst_id->period;
	if (list_empty(&ctx->head)) {
		info("ctx:%p, list is empty\n", ctx);
		list_add_tail(&new_node->list, &ctx->head);
	}
	else
	{
		list_for_each_entry_safe(node, tmp, &ctx->head, list) {
			if(node->data->inst_id->period > period){
				info("que_sort_from_(0x%p) node:%p period_comp[ %d : %d ])\n",
	                        ctx, node, node->data->inst_id->period, period);
				tag_node = node;
				break;
			}
		}
        if(tag_node != NULL)
            list_add_tail(&new_node->list, &tag_node->list);
        else
            list_add_tail(&new_node->list, &ctx->head);

	}

	ctx->node_cnt++;
	mutex_unlock(&ctx->lock);

	info("que_asc_sort_push_to_(0x%p) node:%p period:%d\n",
                ctx, new_node, period);

	return 0;
}

struct npu_buffer_info *npu_que_find_pop_by_id(void *id, void* inst_id)
{
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *tmp = NULL, *node = NULL;
	struct npu_buffer_info *data = NULL;
	unsigned int cnt = 0;

	ctx = (struct npu_que_ctx *)id;
	if (!ctx) {
		error("invalid argument\n");
	    return NULL;
	}

	mutex_lock(&ctx->lock);
	if (list_empty(&ctx->head)) {
		warn("ctx:%p, list is empty\n", ctx);
        if (mutex_is_locked(&ctx->lock)) {
        	mutex_unlock(&ctx->lock);
        }
	    return NULL;
	}

	list_for_each_entry_safe(node, tmp, &ctx->head, list) {
		if(node->data->inst_id == inst_id){
			data = node->data;
			list_del(&node->list);
			info("que_find_pop_from_(0x%p) node:%p data:0x%p id:0x%p\n",
                        ctx, node, node->data, inst_id);
			kfree(node);
			cnt++;
			break;
		}
	}

	if(!cnt){
		warn("NOT_find_pop_node_from_(0x%p) [id:0x%p] \n", ctx, inst_id);
        if (mutex_is_locked(&ctx->lock)) {
        	mutex_unlock(&ctx->lock);
        }
        return NULL;
	}

	ctx->node_cnt--;
	mutex_unlock(&ctx->lock);

	return data;
}

unsigned int npu_que_find_clear_by_id(void *id, void* inst_id)
{
    struct npu_que_ctx *ctx = NULL;
    struct npu_que_node *tmp = NULL, *node = NULL;
    unsigned int free_cnt = 0;

    ctx = (struct npu_que_ctx *)id;
    if(!ctx) {
        error("invalid argument\n");
        return 0;
    }

    mutex_lock(&ctx->lock);
    if(ctx->node_cnt)
    {
        list_for_each_entry_safe(node, tmp, &ctx->head, list) {
            if(node->data->inst_id == inst_id){
                list_del(&node->list);
                kfree(node);
                ctx->node_cnt--;
                free_cnt++;
            }
        }
    }
    mutex_unlock(&ctx->lock);

	if(free_cnt)
        info("que_clear_from_(0x%p) free_num:%d id:0x%p\n",
                ctx, free_cnt, inst_id);

    return free_cnt;
}

struct npu_buffer_info *npu_que_find_pop_by_job_id(void *id, int job_id)
{
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *tmp = NULL, *node = NULL;
	struct npu_buffer_info *data = NULL;
	unsigned int cnt = 0;

	ctx = (struct npu_que_ctx *)id;
	if (!ctx) {
		error("invalid argument\n");
	    return NULL;
	}

	mutex_lock(&ctx->lock);
	if (list_empty(&ctx->head)) {
		warn("ctx:%p, list is empty\n", ctx);
        if (mutex_is_locked(&ctx->lock)) {
			mutex_unlock(&ctx->lock);
        }
	    return NULL;
	}

	list_for_each_entry_safe(node, tmp, &ctx->head, list) {
		if(node->data->job_id == job_id){
			data = node->data;
			list_del(&node->list);
			info("que_find_pop_from_(0x%p) node:%p data:0x%p job_id:%d\n",
                        ctx, node, node->data, job_id);
			kfree(node);
			cnt++;
			break;
		}
	}

	if(!cnt){
		warn("NOT_find_pop_node_from_(0x%p) [job_id:%d] \n", ctx, job_id);
        if (mutex_is_locked(&ctx->lock)) {
			mutex_unlock(&ctx->lock);
        }
        return NULL;
	}

	ctx->node_cnt--;
	mutex_unlock(&ctx->lock);

	return data;
}

struct npu_buffer_info *npu_que_find_by_job_id(void *id, int job_id)
{
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *tmp = NULL, *node = NULL;
	struct npu_buffer_info *data = NULL;
	unsigned int cnt = 0;

	ctx = (struct npu_que_ctx *)id;
	if (!ctx) {
		error("invalid argument\n");
	    return NULL;
	}

	mutex_lock(&ctx->lock);
	if (list_empty(&ctx->head)) {
		info("ctx:%p, list is empty\n", ctx);
        if (mutex_is_locked(&ctx->lock)) {
        	mutex_unlock(&ctx->lock);
        }
	    return NULL;
	}

	list_for_each_entry_safe(node, tmp, &ctx->head, list) {
		if(node->data->job_id == job_id){
			data = node->data;
			info("que_find_from_(0x%p) node:%p data:0x%p job_id:%d\n",
                        ctx, node, node->data, job_id);
			cnt++;
			break;
		}
	}

	if(!cnt){
		info("not_ready_pop_node_from_(0x%p) [job_id:%d] \n", ctx, job_id);
        if (mutex_is_locked(&ctx->lock)) {
        	mutex_unlock(&ctx->lock);
        }
        return NULL;
	}

	mutex_unlock(&ctx->lock);

	return data;
}

void npu_que_dispay(void *id)
{
	struct npu_que_ctx *ctx = NULL;
	struct npu_que_node *tmp = NULL, *node = NULL;
	unsigned int cnt = 0;

	ctx = (struct npu_que_ctx *)id;
	if (!ctx) {
		error("invalid argument\n");
	    return;
	}

	mutex_lock(&ctx->lock);
	if (list_empty(&ctx->head)) {
		warn("ctx:%p, list is empty\n", ctx);
        if (mutex_is_locked(&ctx->lock)) {
			mutex_unlock(&ctx->lock);
        }
	    return;
	}

	list_for_each_entry_safe(node, tmp, &ctx->head, list) {
		info("info_from_(0x%p)[%d] input_buf : 0x%p/n", ctx, cnt,
			(void *)(node->data->input_buf));
		info("info_from_(0x%p)[%d] number_of_input_buf : %d/n", ctx, cnt,
			node->data->number_of_input_buf);
		info("info_from_(0x%p)[%d] output_buf : 0x%p/n", ctx, cnt,
			(void *)(node->data->output_buf));
		info("info_from_(0x%p)[%d] number_of_output_buf : %d/n", ctx, cnt,
			node->data->number_of_output_buf);
		info("info_from_(0x%p)[%d] inter_output_buf : 0x%p/n", ctx, cnt,
			(void *) &(node->data->inter_output_buf));
		info("info_from_(0x%p)[%d] inst_id : 0x%p/n", ctx, cnt,
			node->data->inst_id);
		info("info_from_(0x%p)[%d] period : %d/n", ctx, cnt,
			node->data->inst_id->period);
		info("info_from_(0x%p)[%d] job_id : %d/n", ctx, cnt,
			node->data->job_id);
		info("info_from_(0x%p)[%d] npu_done : %d/n", ctx, cnt,
			node->data->npu_done);
		cnt++;
	}

	mutex_unlock(&ctx->lock);
}

