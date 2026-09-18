/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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
 *  memory manager for TE
 *
 *  @author	Kyungseok Hyun(ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2015-04-29
 *  @note		Additional information.
 */

#include <linux/atomic.h>
#include <linux/kref.h>

#include "te_impl.h"
#include "hma_alloc.h"
#include "debug_util.h"

#define MAX_MEM_NAME		14

struct te_mem_pool {
	enum te_mem_type type;
	char name[MAX_MEM_NAME + 1];

	u32 start;
	u32 size;
	struct kref refcount;

	struct mutex mutex;
	struct list_head ctx_list;
	struct list_head list;	/* node of mem_pool_list */
};

struct te_mem_chunk {
	te_phys_addr_t addr;
	struct list_head list;
};

struct te_mem_ctx {
	struct te_mem_pool *pool;
	struct mutex mutex;
	struct list_head chunk_list;
	struct list_head list;	/* node of struct te_mem_pool.ctx_list */
};

static LIST_HEAD(mem_pool_list);
static DEFINE_MUTEX(mem_mutex);

static struct te_mem_pool *get_mem_pool(const char *name)
{
	struct te_mem_pool *pool;

	list_for_each_entry(pool, &mem_pool_list, list) {
		if (!strcmp(name, pool->name))
			return pool;
	}

	return NULL;
}

#if CONFIG_LX_BOARD_FPGA
static void free_cma_pool(const char *name)
{
}
#else
static int alloc_cma_pool(const char *name, phys_addr_t addr, u32 size)
{
	int ret;
	phys_addr_t ptr;
	char cma_name[MAX_MEM_NAME + 5];

	snprintf(cma_name, MAX_MEM_NAME + 5, "%s_cma", name);

	ret = hma_pool_register_type(cma_name, addr, size, CMA_POOL);
	if (ret) {
		log_error("can't register(%s) to cma pool\n", cma_name);
		return ret;
	}

	ptr = hma_alloc_user(cma_name, size, 1, "hma");	/* alloc all memory from cma */
	if (ptr == 0 || ptr != addr) {
		log_error("can't alloc memory from cma(%s)\n", cma_name);
		hma_pool_unregister(cma_name);
		return -EIO;
	}

	return 0;
}

static void free_cma_pool(const char *name)
{
	char cma_name[MAX_MEM_NAME + 5];

	snprintf(cma_name, MAX_MEM_NAME + 5, "%s_cma", name);

	hma_pool_unregister(cma_name);
}
#endif

static int add_exist_mem_pool(struct te_mem_pool *pool, enum te_mem_type type,
			      u32 addr, u32 size)
{
	if (pool->type != type || pool->start != addr || pool->size != size) {
		log_error("'%s' already registerd - type(%d) 0x%08x++0x%x\n",
			  pool->name, type, pool->start, pool->size);
		return EEXIST;
	}

	kref_get(&pool->refcount);

	return 0;
}

/**
 * Register memory pool
 *
 * @def
 * @param	name 	[in	] memory pool name
 * @param	addr 	[in	] address
 * @param	size 	[in	] size
 * @return	if succeeded - 0, else - errno.
 */
int te_mem_register(const char *name, u32 addr, u32 size, enum te_mem_type type)
{
	int ret;
	struct te_mem_pool *pool;
	bool alloc_cma = false;

	if (strlen(name) > MAX_MEM_NAME) {
		log_error("'%s' over max(%d) name length", name, MAX_MEM_NAME);
		return -EINVAL;
	}

#if 0
	/* Not use cma in O24 until it is stable
	 * http://clm.lge.com/issue/browse/SICDTV-12489 */
	if (lx_chip() == LX_CHIP_O24 && type == TE_MEM_TYPE_CMA) {
		log_warning("%s is forced to set as HMA(NORMAL/Bringup)", name);
		type = TE_MEM_TYPE_NORMAL;
	}
#endif

	/* forced hma setting check (for memory debugging) */
	if (check_force_hma_pool(name) && type == TE_MEM_TYPE_CMA) {
		log_warning("%s is forced to set as HMA(NORMAL)", name);
		type = TE_MEM_TYPE_NORMAL;
	}

	mutex_lock(&mem_mutex);
	pool = get_mem_pool(name);
	if (pool) {
		ret = add_exist_mem_pool(pool, type, addr, size);
		mutex_unlock(&mem_mutex);
		return ret;
	}

	pool = kmalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool) {
		ret = -ENOMEM;
		goto err_alloc;
	}
#if CONFIG_LX_BOARD_FPGA
	ret = hma_pool_register(name, addr, size);
#else
	if (type == TE_MEM_TYPE_CMA)
		ret = hma_pool_register_type(name, addr, size, CMA_POOL);
	else if (type == TE_MEM_TYPE_BIGCMA)
		ret = hma_pool_register_type(name, addr, size, BIGCMA_POOL);
	else if (type == TE_MEM_TYPE_HMA)
		ret = hma_pool_register_type(name, addr, size, HMA_POOL);
	else if (type == TE_MEM_TYPE_NORMAL) {
		ret = alloc_cma_pool(name, addr, size);
		if (!ret) {
			alloc_cma = true;
			ret =
			    hma_pool_register_type(name, addr, size, HMA_POOL);
		}
	} else {
		ret = -EINVAL;
	}
#endif

	if (ret) {
		log_error("can't register(%s) memory\n", name);
		goto err_register;
	}

	strncpy(pool->name, name, MAX_MEM_NAME);
	pool->name[MAX_MEM_NAME] = 0;
	pool->type = type;
	pool->start = addr;
	pool->size = size;

	kref_init(&pool->refcount);
	mutex_init(&pool->mutex);
	INIT_LIST_HEAD(&pool->ctx_list);

	list_add_tail(&pool->list, &mem_pool_list);

	mutex_unlock(&mem_mutex);

	return 0;

 err_register:
	if (alloc_cma)
		free_cma_pool(name);

	kfree(pool);
 err_alloc:
	mutex_unlock(&mem_mutex);

	return ret;
}

static void pool_release(struct kref *kref)
{
	struct te_mem_ctx *ctx, *ctx2;
	struct te_mem_pool *pool =
	    container_of(kref, struct te_mem_pool, refcount);

	list_del(&pool->list);

	list_for_each_entry_safe(ctx, ctx2, &pool->ctx_list, list) {
		te_mem_close(ctx);
	}

	hma_pool_unregister(pool->name);

	if (pool->type == TE_MEM_TYPE_NORMAL)
		free_cma_pool(pool->name);

	kfree(pool);
}

/**
 * Unregister memory pool
 *
 * @def
 * @param	name 	[in	] memory pool name
 */
void te_mem_unregister(const char *name)
{
	struct te_mem_pool *pool;

	log_noti("%s(%s)\n", __func__, name);

	mutex_lock(&mem_mutex);
	pool = get_mem_pool(name);
	if (pool)
		kref_put(&pool->refcount, pool_release);
	mutex_unlock(&mem_mutex);
}

struct te_mem_ctx *te_mem_open(const char *name)
{
	struct te_mem_ctx *ctx;
	struct te_mem_pool *pool;

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		log_error("no mem\n");
		return NULL;
	}

	log_mem("%s(%s)\n", __func__, name);

	mutex_lock(&mem_mutex);
	pool = get_mem_pool(name);
	mutex_unlock(&mem_mutex);

	if (!pool) {
		log_error("not registered memory(%s)\n", name);
		kfree(ctx);
		return NULL;
	}

	ctx->pool = pool;
	mutex_init(&ctx->mutex);
	INIT_LIST_HEAD(&ctx->chunk_list);

	mutex_lock(&pool->mutex);
	list_add_tail(&ctx->list, &pool->ctx_list);
	mutex_unlock(&pool->mutex);

	return ctx;
}

/**
 * Allocate memory
 *
 * @def
 * @param	h	 	[in	] memory pool handle
 * @param	size 	[in	] size
 * @return	if succeeded - 0, else - errno.
 */
te_phys_addr_t te_mem_alloc_user(struct te_mem_ctx *ctx, size_t size,
				 const char *name, size_t align)
{
	te_phys_addr_t addr;
	struct te_mem_chunk *chunk;
	struct te_mem_pool *pool;

	if (!ctx || !size) {
		log_error("invalid param : ctx:%p, size:%zu", ctx, size);
		return 0;
	}

	chunk = kmalloc(sizeof(*chunk), GFP_KERNEL);
	if (!chunk) {
		log_error("no mem\n");
		return 0;
	}

	pool = ctx->pool;
	log_mem("alloc(%s) %zubytes\n", pool->name, size);

	if (name)
		addr = (te_phys_addr_t)hma_alloc_user(pool->name, size, align,
						      name);
	else
		addr = (te_phys_addr_t)hma_alloc(pool->name, size, align);

	if (!addr) {
		log_error("hma_alloc failed\n");
		kfree(chunk);
		return 0;
	}

	chunk->addr = addr;

	mutex_lock(&ctx->mutex);
	list_add_tail(&chunk->list, &ctx->chunk_list);
	mutex_unlock(&ctx->mutex);

	return addr;
}

te_phys_addr_t te_mem_alloc(struct te_mem_ctx *ctx, size_t size,
			    const char *name)
{
	return te_mem_alloc_user(ctx, size, name, PAGE_SIZE);
}


/**
 * Free allocated memory
 *
 * @def
 * @param	h	[in] memory pool handle
 * @param	ptr 	[in] allocate memory address
 * @return	if succeeded - 0, else - errno.
 */
int te_mem_free(struct te_mem_ctx *ctx, te_phys_addr_t addr)
{
	bool found;
	struct te_mem_chunk *chunk;
	struct te_mem_pool *pool;

	if (!ctx || !addr) {
		log_error("invalid param : ctx:%p, ptr:0x%x", ctx, addr);
		return -EINVAL;
	}

	pool = ctx->pool;

	found = false;

	mutex_lock(&ctx->mutex);
	list_for_each_entry(chunk, &ctx->chunk_list, list) {
		if (chunk->addr == addr) {
			found = true;
			list_del(&chunk->list);
			break;
		}
	}
	mutex_unlock(&ctx->mutex);

	if (!found) {
		log_error("pool:%s - invalid ptr:0x%08x\n", pool->name, addr);
		return -EINVAL;
	}

	log_mem("free(%s) addr=0x%08x", pool->name, addr);

	kfree(chunk);
	hma_free(pool->name, (phys_addr_t)addr);

	return 0;
}

void te_mem_close(struct te_mem_ctx *ctx)
{
	struct te_mem_chunk *chunk, *chunk2;
	struct te_mem_pool *pool;

	pool = ctx->pool;

	log_mem("%s(%s)\n", __func__, pool->name);

	mutex_lock(&pool->mutex);
	list_del(&ctx->list);
	mutex_unlock(&pool->mutex);

	list_for_each_entry_safe(chunk, chunk2, &ctx->chunk_list, list) {
		log_mem("free(%s) addr:0x%08x", pool->name, chunk->addr);
		hma_free(pool->name, chunk->addr);
		list_del(&chunk->list);
		kfree(chunk);
	}

	kfree(ctx);
}

/**
 * Get memory statistics for te memory
 * application can use this information to monitor memroy usage.
 *
 * @def
 * @param	h	[in ] memory pool handle
 * @param	info 	[out] information
 * @return	if succeeded - 0, else - errno.
 */
int te_mem_get_info(struct te_mem_ctx *h, struct te_mem_info *info)
{
	struct te_mem_pool *pool;
#if !CONFIG_LX_BOARD_FPGA
	int size;
#endif
	pool = h->pool;

	info->addr = pool->start;
	info->size = pool->size;

#if !CONFIG_LX_BOARD_FPGA
	hma_pool_status(pool->name, hma_pool_status_free_size, &size);
	info->free = size;

	hma_pool_status(pool->name, hma_pool_status_max_available_size, &size);
	info->avail = size;
#endif

	return 0;
}

/**
 * Check physical address range validation
 * The range should be in the range of preset memory area
 *
 * @def
 * @param	h	[in ] memory pool context
 * @param	paddr 	[in] physical address
 * @param	size 	[in] memory size start with paddr
 * @return	if succeeded - 0, else - errno.
 */
int te_mem_check_paddr_range(struct te_mem_ctx *h, u32 paddr, u32 size)
{
	struct te_mem_info i;
	u32 sptr, eptr;

	sptr = paddr;
	eptr = paddr + size;

	if (!size)
		return -EFAULT;

	te_mem_get_info(h, &i);
	if (sptr < i.addr || sptr >= (i.addr + i.size))
		return -EFAULT;

	if (eptr <= i.addr || eptr > (i.addr + i.size))
		return -EFAULT;

	return 0;
}


/**
 * Initialize memory pool manager.
 *
 * @def
 * @return	if succeeded - 0, else - errno.
 */
static int mem_dev_init(struct te_device *dev)
{
	int ret;
	struct te_mem_region_info *info;

	info = te_get_mem_region_info(TE_MEM_SHARED);
	ret = te_mem_register(TE_MEM_SHARED_NAME, info->addr, info->size,
			      TE_MEM_TYPE_CMA);

	CHECK_ERROR(ret, return ret, "can't register memory");

	return 0;
}

/**
 * Finalize memory pool manager.
 */
static void mem_dev_release(struct te_device *tdev)
{
	// TODO: free or not ?
}

const struct te_sub_driver te_mem_driver = {
	.name = "te_mem",
	.early_init = mem_dev_init,
	.release = mem_dev_release,
};
