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
 *  npu utilization
 *
 *  author      Dongmin Kwon (dongmin.kwon@lge.com)
 *  version     0.1
 *  date        2023.05.31
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "base_types.h"
#include "os_util.h"
#include "logm.h"
#include "npu_drv.h"
#include "npu_utilization.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define NPU_UTILS_PROC_DIR "npu"
#define NPU_UTILS_PROC_FILE "npu_utilization"
#define NPU_UTILS_DEV_CAP_PROC_FILE "npu_device_capability"
#define NPU_UTILS_PROCESS_LIST_PROC_FILE "npu_process_list"
#define IOMMUINFO_PROC_FILE "iommuinfo"

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
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int npu_util_proc_open(struct inode *in, struct file *file);
static int iommuinfo_util_proc_open(struct inode *in, struct file *file);

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static struct proc_dir_entry *npu_dir;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops npu_util_fops = {
    .proc_open = npu_util_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static const struct proc_ops iommuinfo_fops = {
    .proc_open = iommuinfo_util_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};
#else
static const struct file_operations npu_util_fops = {
    .owner = THIS_MODULE,
	.open = npu_util_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static const struct file_operations iommuinfo_fops = {
    .owner = THIS_MODULE,
	.open = iommuinfo_util_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};
#endif

/*==============================================================================
    Implementation Group
==============================================================================*/
void *npu_util_que_open(void)
{
	struct npu_util_que_ctx *ctx = NULL;
	ctx = (struct npu_util_que_ctx *)kzalloc(sizeof(struct npu_util_que_ctx ), GFP_KERNEL);
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

int npu_util_que_close(void *id) {
	struct npu_util_que_ctx *ctx = NULL;
	struct npu_util_que_node *tmp = NULL, *node = NULL;
	unsigned int free_cnt = 0;

	ctx = (struct npu_util_que_ctx *)id;
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

int npu_util_que_push(void *id, void *data) {
	struct npu_util_que_ctx *ctx = NULL;
	struct npu_util_que_node *node = NULL;

	ctx = (struct npu_util_que_ctx *)id;
	if(!ctx) {
		error("invalid argument\n");
		return -1;
	}

	node = (struct npu_util_que_node *)kzalloc(sizeof(struct npu_util_que_node), GFP_KERNEL);
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

	node->data = (struct npu_dbg_info *)data;
	mutex_lock(&ctx->lock);
	ctx->node_cnt++;
	list_add_tail(&node->list, &ctx->head);
	mutex_unlock(&ctx->lock);

	info("util_que_push_to_(0x%p) node:%p data:0x%p\n",
                ctx, node, data);

	return 0;
}

struct npu_dbg_info *npu_util_que_pop(void *id) {
	struct npu_util_que_ctx *ctx = NULL;
	struct npu_util_que_node *node = NULL;
	struct npu_dbg_info *data = NULL;

	ctx = (struct npu_util_que_ctx *)id;
	if(!ctx) {
		error("invalid argument.\n");
		return NULL;
	}

	mutex_lock(&ctx->lock);
	if(list_empty(&ctx->head)) {
		warn("ctx:%p, list is empty\n", ctx);
    	if(mutex_is_locked(&ctx->lock)) {
    		mutex_unlock(&ctx->lock);
    	}
		return NULL;
	}

	ctx->node_cnt--;
	node = list_entry(ctx->head.next, struct npu_util_que_node, list);
	data = node->data;
	list_del(&node->list);
	info("util_que_pop_from_(0x%p) node:%p data:0x%p\n",
            ctx, node, data);
	kfree(node);
	mutex_unlock(&ctx->lock);

	return data;
}

unsigned int npu_util_que_get_node_cnt(void *id) {
	struct npu_util_que_ctx *ctx = NULL;
	unsigned int count = 0;

	ctx = (struct npu_util_que_ctx *)id;
	if(!ctx) {
		error("invalid argument\n");
		return 0;
	}

	mutex_lock(&ctx->lock);
	count = ctx->node_cnt;
	mutex_unlock(&ctx->lock);

	info("util_que_get_node_cnt_from_(0x%p) count:%d\n", ctx, count);

	return count;
}

unsigned int npu_util_que_all_clear(void *id) {
	struct npu_util_que_ctx *ctx = NULL;
	struct npu_util_que_node *tmp = NULL, *node = NULL;
	unsigned int free_cnt = 0;

	ctx = (struct npu_util_que_ctx *)id;
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
	info("util_que_clear ctx:0x%p free_num:%d\n", ctx, free_cnt);

	return free_cnt;
}

extern struct mutex npu_inst_list_lock;
extern struct list_head npu_inst_list;

static int _npu_util_seq_show(struct seq_file *sfile, void *data)
{
    struct npu_inst *cur;
    unsigned long long total_avs_ms = 0;

    mutex_lock(&npu_inst_list_lock);
    list_for_each_entry (cur, &npu_inst_list, list) {
        total_avs_ms += cur->dbg_mtd.avg_ms;
        debug("%p, avg_ms %llu, tot %llu\n", cur, cur->dbg_mtd.avg_ms, total_avs_ms);
    }
    mutex_unlock(&npu_inst_list_lock);

    seq_printf(sfile, "%d\n", clamp((int)total_avs_ms, 0, 100));

    return 0;
}

#define NPU_DRIVER_VERS_MAJOR (1)
#define NPU_DRIVER_VERS_MINOR (0)

static int _npu_dev_cap_seq_show(struct seq_file *sfile, void *data)
{
    unsigned int chip = 0;
    unsigned int tops = 0;
    unsigned int cache_size = 0;
    char *aipq_enabled = "";
    char *npu_name = "";

    chip = lx_chip();
    if (chip == LX_CHIP_O26) {
        // 2 core
        tops = 36;  //lnx0: 1.8, lnx1: 1.8, lnx2: 0.9
        cache_size = 2048; //lnx0: 1024, lnx1: 1024, lnx2:512
        aipq_enabled = "true";
        npu_name = "LNX";
    } else if (chip == LX_CHIP_O24) {
        // 2 core
        tops = 32;  // 3.2
        cache_size = 1024;
        aipq_enabled = "true";
        npu_name = "LNX";
    } else if (chip == LX_CHIP_O22) {
        // 1 core
        tops = 4;   // 0.4
        cache_size = 256;
        aipq_enabled = "false";
        npu_name = "DNE";
    } else {
        tops = 0;
        cache_size = 0;
        aipq_enabled = "false";
        npu_name = "";
    }

    seq_printf(sfile, "NPU vendor : LGE\n");
    seq_printf(sfile, "NPU name : %s\n", npu_name);
    seq_printf(sfile, "NPU driver version : %d.%d\n", NPU_DRIVER_VERS_MAJOR, NPU_DRIVER_VERS_MINOR);
    seq_printf(sfile, "NPU cache size : %d\n", cache_size);
    seq_printf(sfile, "NPU tops : %d.%d\n", tops / 10, tops % 10);
    seq_printf(sfile, "aipq compatibility : %s\n", aipq_enabled);

    return 0;
}

static const char* user_process_type_to_str(unsigned int type)
{
    switch (type) {
        case NPU_USER_PROCESS_AIPQ:
            return "aipq";
        case NPU_USER_PROCESS_NNHAL:
            return "nnhal";
        case NPU_USER_PROCESS_DELEGATE:
            return "npu_delegate";
        default:
        case NPU_USER_PROCESS_NONE:
            return "unkown";
    }
}

static int _npu_process_list_seq_show(struct seq_file *sfile, void *data)
{
    struct npu_inst *cur;
    unsigned int list_size = 0, i = 0, j = 0;
    unsigned int *array_pid;

    mutex_lock(&npu_inst_list_lock);
    list_for_each_entry (cur, &npu_inst_list, list) {
        list_size++;
    }

    array_pid = kzalloc(list_size * sizeof(unsigned int), GFP_KERNEL);
    if(!array_pid) {
        error("kmalloc fail\n");
        mutex_unlock(&npu_inst_list_lock);
        return -ENOMEM;
    }

    list_for_each_entry (cur, &npu_inst_list, list) {
        bool is_same_pid = false;

        debug("pid %d\n", cur->procces_id);
        for (j=0; j<list_size; j++) {
            if (*(array_pid + j) == cur->procces_id) {
                is_same_pid = true;
                break;
            }
        }

        if (is_same_pid) {
            continue;
        }

        *(array_pid + i) = cur->procces_id;
        i++;

        seq_printf(sfile, "%s %d\n", user_process_type_to_str(cur->user_procces_type), 
            cur->procces_id);
    }

    kfree(array_pid);
    mutex_unlock(&npu_inst_list_lock);

    return 0;
}

static int npu_util_proc_open(struct inode *in, struct file *file)
{
    return  single_open(file, _npu_util_seq_show, NULL);
}

static int npu_dev_cap_proc_open(struct inode *in, struct file *file)
{
    return  single_open(file, _npu_dev_cap_seq_show, NULL);
}

static int npu_process_list_proc_open(struct inode *in, struct file *file)
{
    return  single_open(file, _npu_process_list_seq_show, NULL);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops npu_dev_cap_fops = {
    .proc_open = npu_dev_cap_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static const struct proc_ops npu_process_list_fops = {
    .proc_open = npu_process_list_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};
#else
static const struct file_operations npu_dev_cap_fops = {
    .owner = THIS_MODULE,
    .open = npu_dev_cap_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static const struct file_operations npu_process_list_fops = {
    .owner = THIS_MODULE,
    .open = npu_process_list_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};
#endif

int npu_utilization_proc_init(void)
{
    npu_dir = proc_mkdir(NPU_UTILS_PROC_DIR, NULL);
    if (!npu_dir)
    {
        error("Unable to create /proc/%s directory\n", NPU_UTILS_PROC_DIR);
        return -ENOMEM;
    }

    if (!proc_create(NPU_UTILS_PROC_FILE, 0, npu_dir, &npu_util_fops))
    {
        error("Unable to create /proc/%s/%s file\n", NPU_UTILS_PROC_DIR, NPU_UTILS_PROC_FILE);
        remove_proc_entry(NPU_UTILS_PROC_DIR, NULL);
        return -ENOMEM;
    }

    if (!proc_create(NPU_UTILS_DEV_CAP_PROC_FILE, 0, npu_dir, &npu_dev_cap_fops))
    {
        error("Unable to create /proc/%s/%s file\n", NPU_UTILS_PROC_DIR, NPU_UTILS_DEV_CAP_PROC_FILE);
        return -ENOMEM;
    }

    if (!proc_create(NPU_UTILS_PROCESS_LIST_PROC_FILE, 0, npu_dir, &npu_process_list_fops))
    {
        error("Unable to create /proc/%s/%s file\n", NPU_UTILS_PROC_DIR, NPU_UTILS_PROCESS_LIST_PROC_FILE);
        return -ENOMEM;
    }

    info("/proc/%s/%s created\n", NPU_UTILS_PROC_DIR, NPU_UTILS_PROC_FILE);
    return 0;
}

void npu_utilization_proc_exit(void)
{
    remove_proc_entry(NPU_UTILS_PROC_FILE, npu_dir);
    remove_proc_entry(NPU_UTILS_DEV_CAP_PROC_FILE, npu_dir);
    remove_proc_entry(NPU_UTILS_PROCESS_LIST_PROC_FILE, npu_dir);
    remove_proc_entry(NPU_UTILS_PROC_DIR, NULL);
    info("/proc/%s removed\n", NPU_UTILS_PROC_FILE);
}

static int _iommuinfo_util_seq_show(struct seq_file *sfile, void *data)
{
    seq_printf(sfile, "total size : %d kb\n", \
                iommuinfo_get_utilization());

    return 0;
}

static int iommuinfo_util_proc_open(struct inode *in, struct file *file)
{
    return  single_open(file, _iommuinfo_util_seq_show, NULL);
}

int iommuinfo_utilization_proc_init(void)
{
    proc_create(IOMMUINFO_PROC_FILE, 0, NULL, &iommuinfo_fops);
    info("/proc/%s created\n", IOMMUINFO_PROC_FILE);
    return 0;
}

void iommuinfo_utilization_proc_exit(void)
{
    remove_proc_entry(IOMMUINFO_PROC_FILE, NULL);
    info("/proc/%s removed\n", IOMMUINFO_PROC_FILE);
}

