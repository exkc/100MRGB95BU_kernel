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

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
// legacy proc will be removed someday

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>

#include <asm/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "debug_util.h"
#include "proc_util.h"
#include "base_impl.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define BASE_PROC_NAME          "lg"
#define LINUXTV_PROC_NAME       "lgtv-driver"

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define os_vmalloc              vmalloc
#define os_vfree                vfree

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
struct os_proc
{
    char* name;
    struct proc_dir_entry* proc_entry;
};

struct os_proc_dir
{
    struct os_proc base;

    os_proc_rw_handler user_reader;
    os_proc_rw_handler user_writer;
};

struct os_proc_file
{
    struct os_proc base;
    struct os_proc_dir* dir;

    u32 id;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
    struct proc_ops fops;
#else
    struct file_operations fops;
#endif

    os_proc_seq_file_rd_handler seq_reader;
    os_proc_seq_file_wr_handler seq_writer;

    void* arg;
};

static ssize_t os_proc_simple_reader(struct file* file, char __user* user_buffer, size_t size, loff_t* pos);
static ssize_t os_proc_simple_writer(struct file* file, const char __user* user_buffer, size_t size, loff_t* pos);

/*----------------------------------------------------------------------------------------
   Function Prototype Declarations
----------------------------------------------------------------------------------------*/
void lg1k_proc_frwk_cleanup(void);
void lg1k_proc_frwk_init(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static struct os_proc           os_proc_base_dir;
static struct proc_dir_entry*   os_proc_entry = NULL;
static struct proc_dir_entry*   os_proc_linuxtv_entry = NULL;
static OS_SEM_T                 proc_mtx;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops os_proc_simple_fops =
{
    .proc_read = os_proc_simple_reader,
    .proc_write = os_proc_simple_writer,
};
#else
static const struct file_operations os_proc_simple_fops =
{
    .read = os_proc_simple_reader,
    .write = os_proc_simple_writer,
};
#endif

static int os_proc_seq_file_open(struct inode* inode, struct file* file);
static ssize_t os_proc_seq_file_write(struct file* file, const char __user* buf, size_t size, loff_t* off);
static int os_proc_seq_file_release(struct inode* inode, struct file* file);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static struct proc_ops os_proc_seq_file_fops =
{
    .proc_open = os_proc_seq_file_open,
    .proc_write = os_proc_seq_file_write,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = os_proc_seq_file_release,
};
#else
static struct file_operations os_proc_seq_file_fops =
{
    .open = os_proc_seq_file_open,
    .write = os_proc_seq_file_write,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = os_proc_seq_file_release,
};
#endif

static int os_max_proc_buffer_size = 0x4000;
module_param_named(proc_buffer_size, os_max_proc_buffer_size, int, 0644);

/*----------------------------------------------------------------------------------------
    Function Implementation
----------------------------------------------------------------------------------------*/
struct proc_dir_entry* os_proc_get_entry(struct os_proc* p)
{
    return (likely(p)) ? p->proc_entry : NULL;
}
EXPORT_SYMBOL(os_proc_get_entry);

struct os_proc* os_proc_create_dir(struct os_proc* pdir, const char* name, os_proc_rw_handler user_reader,
                                   os_proc_rw_handler user_writer)
{
    struct os_proc* parent_dir;
    struct os_proc_dir* obj = os_vmalloc(sizeof(struct os_proc_dir));

    if (!obj)
    {
        lg1k_logm_error("alloc error\n");
        return NULL;
    }

    lg1k_logm_proc_debug("pdir=%px, cname=%px, user_reader=%px, user_writer=%px\n", pdir, name, user_reader, user_writer);

    parent_dir = (pdir) ? pdir : &os_proc_base_dir;

    if (!parent_dir->proc_entry)
    {
        lg1k_logm_error("null pdir proc_entry\n");
        return NULL;
    }

    obj->base.proc_entry = proc_mkdir(name, parent_dir->proc_entry);
    obj->base.name = os_strdup(name, LX_STR_MAX);

    obj->user_reader = user_reader;
    obj->user_writer = user_writer;

    return (void*)obj;
}
EXPORT_SYMBOL(os_proc_create_dir);


static ssize_t os_proc_simple_reader(struct file* file, char __user* user_buffer, size_t size, loff_t* pos)
{
    ssize_t ret = 0;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    struct os_proc_file* obj = (struct os_proc_file*)pde_data(file->f_inode);
#else
    struct os_proc_file* obj = (struct os_proc_file*)PDE_DATA(file->f_inode);
#endif
    char* proc_buffer = NULL;
    int len = 0;

    if (*pos > 0)
    {
        return 0;
    }

    proc_buffer = os_vmalloc(ALIGN(os_max_proc_buffer_size, PAGE_SIZE));

    if (!proc_buffer)
    {
        lg1k_logm_error("alloc error\n");
        return -EFAULT;
    }

    lg1k_logm_proc_debug("os_proc.name=%s, pdir=%px, buffer.size=%ld\n", obj->base.name, obj->dir, size);

    // call user reader
    // group 이 NULL ?
    if (obj->dir->user_reader)
    {
        len = obj->dir->user_reader(obj->id, proc_buffer, size, obj->arg);

        *pos += len;
        ret = len;

        if (copy_to_user(user_buffer, proc_buffer, len))
        {
            ret = -EFAULT;
        }
    }

    if (proc_buffer)
    {
        os_vfree(proc_buffer);
    }

    return ret;
}

static ssize_t os_proc_simple_writer(struct file* file, const char __user* user_buffer, size_t size, loff_t* pos)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    struct os_proc_file* obj = (struct os_proc_file*)pde_data(file->f_inode);
#else
    struct os_proc_file* obj = (struct os_proc_file*)PDE_DATA(file->f_inode);
#endif
    char* proc_buffer = os_vmalloc(ALIGN(size, PAGE_SIZE));

    if (!proc_buffer)
    {
        lg1k_logm_error("alloc error\n");
        return -EFAULT;
    }

    if (copy_from_user(proc_buffer, user_buffer, size))
    {
        return -EFAULT;
    }

    proc_buffer[size - 1] = '\0';

    lg1k_logm_proc_debug("os_proc.name=%s, pdir=%px, buffer.size=%ld\n", obj->base.name, obj->dir, size);

    // call user writer
    if (obj->dir->user_writer)
    {
        obj->dir->user_writer(obj->id, proc_buffer, size, obj->arg);
        goto func_exit;
    }

func_exit:

    if (proc_buffer)
    {
        os_vfree(proc_buffer);
    }

    return size;
}

struct os_proc* os_proc_create_file(struct os_proc* dir, const char* name, u32 id, void* arg)
{
    struct os_proc_file* obj;
    struct os_proc_dir* parent_dir = (struct os_proc_dir*)dir;

    if (!parent_dir || !parent_dir->base.proc_entry || !name)
    {
        lg1k_logm_error("null dir, null entry or null name\n");
        return NULL;
    }

    lg1k_logm_proc_debug("pdir=%px, id=%d, name=%px, arg=%px\n", dir, id, name, arg);


    obj = os_vmalloc(sizeof(struct os_proc_file));

    if (!obj)
    {
        lg1k_logm_error("alloc error\n");
        return NULL;
    }

    obj->fops = os_proc_simple_fops;
    obj->dir = parent_dir;
    obj->id = id;
    obj->seq_reader = NULL;
    obj->seq_writer = NULL;
    obj->arg = arg;

    obj->base.name = os_strdup(name, LX_STR_MAX);
    obj->base.proc_entry = proc_create_data(name, 0660, parent_dir->base.proc_entry, &obj->fops, obj);

    return (void*)obj;
}
EXPORT_SYMBOL(os_proc_create_file);

static ssize_t os_proc_seq_file_write(struct file* file, const char __user* user_buffer, size_t size, loff_t* off)
{
    int len = 0;
    struct os_proc_file* obj = ((struct seq_file*)file->private_data)->private;

    char* proc_buffer = os_vmalloc(ALIGN(size, PAGE_SIZE));

    if (!proc_buffer)
    {
        lg1k_logm_error("alloc error\n");
        return -EFAULT;
    }

    if (copy_from_user(proc_buffer, user_buffer, size))
    {
        return -EFAULT;
    }

    proc_buffer[size - 1] = '\0';

    lg1k_logm_proc_debug("os_proc.name=%s, pdir=%px, buffer.size=%ld\n", obj->base.name, obj->dir, size);

    if (obj->seq_writer)
    {
        len = obj->seq_writer(proc_buffer, size, obj->arg);
    }

    os_vfree(proc_buffer);

    return size;
}


static int os_proc_seq_file_read(struct seq_file* s, void* data)
{
    struct os_proc_file* obj = (struct os_proc_file*)s->private;

    lg1k_logm_proc_debug("os_proc.name=%s, pdir=%px\n", obj->base.name, obj->dir);

    if (obj->seq_reader)
    {
        obj->seq_reader(s, obj->arg);
    }

    return 0;
}

static int os_proc_seq_file_release(struct inode* inode, struct file* file)
{
    // release obj ?

    return single_release(inode, file);
}

static int os_proc_seq_file_open(struct inode* inode, struct file* file)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    return single_open(file, os_proc_seq_file_read, pde_data(inode));
#else
    return single_open(file, os_proc_seq_file_read, PDE_DATA(inode));
#endif
}

struct os_proc* os_proc_create_seq_file(struct os_proc* dir, const char* name,
                                        os_proc_seq_file_rd_handler seq_rd_handler, os_proc_seq_file_wr_handler seq_wr_handler, void* arg)
{
    struct os_proc_file* obj;
    struct os_proc_dir* parent_dir = (struct os_proc_dir*)dir;

    if (!parent_dir || !parent_dir->base.proc_entry || !name)
    {
        lg1k_logm_error("null dir, null entry or null name\n");
        return NULL;
    }

    lg1k_logm_proc_debug("pdir=%px, name=%px, arg=%px\n", dir, name, arg);

    obj = os_vmalloc(sizeof(struct os_proc_file));

    if (!obj)
    {
        lg1k_logm_error("alloc error\n");
        return NULL;
    }

    obj->fops = os_proc_seq_file_fops;
    obj->dir = parent_dir;
    obj->id = -1;
    obj->seq_reader = seq_rd_handler;
    obj->seq_writer = seq_wr_handler;
    obj->arg = arg;

    obj->base.name = os_strdup(name, LX_STR_MAX);
    obj->base.proc_entry = proc_create_data(name, 0660, parent_dir->base.proc_entry, &obj->fops, obj);

    return (void*)obj;
}
EXPORT_SYMBOL(os_proc_create_seq_file);


/*========================================================================================

    LEGACY IMPLEMNTATION (DO NOT USE)

========================================================================================*/
#if 1//def SUPPORT_LEGACY_PROC

#define MAX_PROC_LIST   (LX_MAX_DEVICE_NUM*3)

/* proc_util makes proc data using module_id and proc_id */
#define MK_PROC_DATA(idx,id)        ((unsigned long)(((idx)<<16)|(id)))
#define GET_MODULE_ID(data)         (((UINT32)(data))>>16)
#define GET_PROC_ID(data)           (((UINT32)(data))&0xffff)

typedef struct
{
    char                    module_name[LX_MAX_DEVICE_NAME];
    OS_PROC_DESC_TABLE_T*   module_proc_table;
    struct proc_dir_entry*  module_proc_dir;
    struct proc_dir_entry*  parent_proc_dir;

    int                     max_proc_num;
    OS_PROC_READ_FUNC_T     user_reader;
    OS_PROC_WRITE_FUNC_T    user_writer;
}
MOD_PROC_TBL_T;

static struct proc_dir_entry* _OS_PROC_CreateEntry(const char* module_name, struct proc_dir_entry* parent_entry,
        OS_PROC_DESC_TABLE_T* pTable, void* read_func, void* write_func);

static ssize_t  _OS_PROC_Reader(struct file* file, char __user* buf, size_t size, loff_t* ppos);
static ssize_t  _OS_PROC_Writer(struct file* file, const char __user* buf, size_t size, loff_t* ppos);

static MOD_PROC_TBL_T*              _g_proc_tbl_list = NULL;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static struct proc_ops              _g_proc_module_fops;
#else
static struct file_operations       _g_proc_module_fops;
#endif

/** @name Function Definition for Proc Utility
 * function list for proc utility
 *
 * @{
*/


/**
 * create proc entry for each module
 *
 * @param base_name [IN] module name
 * @param pTable [IN] pointer to proc description table
 * @param read_func [IN] read proc callback for read operation ( application reads something from driver )
 * @param write_func [IN] write proc callback for write operation ( application writes something to driver )
 * @returns RET_OK(0) if success, none zero for otherwise
 *
 * @see OS_PROC_RemoveEntry
 * @see OS_PROC_fush_entry
 *
*/
struct proc_dir_entry* OS_PROC_CreateEntryEx(const char* module_name,
        OS_PROC_DESC_TABLE_T* pTable, OS_PROC_READ_FUNC_T read_func, OS_PROC_WRITE_FUNC_T write_func)
{
    return _OS_PROC_CreateEntry(module_name, NULL, pTable, read_func, write_func);
}
EXPORT_SYMBOL(OS_PROC_CreateEntryEx);

struct proc_dir_entry* OS_PROC_CreateEntry(const char* module_name, struct proc_dir_entry* parent_entry,
        OS_PROC_DESC_TABLE_T* pTable, OS_PROC_READ_FUNC_T read_func, OS_PROC_WRITE_FUNC_T write_func)
{
    return _OS_PROC_CreateEntry(module_name, parent_entry, pTable, read_func, write_func);
}
EXPORT_SYMBOL(OS_PROC_CreateEntry);

static struct proc_dir_entry* _OS_PROC_CreateEntry(const char* module_name, struct proc_dir_entry* parent_entry,
        OS_PROC_DESC_TABLE_T* pTable, void* read_func, void* write_func)
{
    int i, j;
    int ret;
    mode_t  entry_mode;
    struct  proc_dir_entry* module_proc_dir = NULL;

    if (NULL == module_name || NULL == pTable)
    {
        DBG_PRINT_WARNING("null argument (%c,%c)\n", (module_name) ? 'O' : '-', (pTable) ? 'O' : '-');
        return NULL;
    }

    ret = OS_LockMutex(&proc_mtx);

    for (i = 0; i < MAX_PROC_LIST; i++)
    {
        if (NULL == _g_proc_tbl_list[i].module_proc_table) { /* found empty */ break; }
    }

    if (i >= MAX_PROC_LIST)
    {
        DBG_PRINT_WARNING("proc register failed. no empty slot.\n");
        ret = RET_INVALID_PARAMS; goto function_exit;
    }

    /* if ext mode, internal proc function will be used */
    _g_proc_tbl_list[i].user_reader = read_func;
    _g_proc_tbl_list[i].user_writer = write_func;

    /* make proc structure */
    _g_proc_tbl_list[i].module_proc_table = pTable;
    snprintf(_g_proc_tbl_list[i].module_name, LX_MAX_DEVICE_NAME - 1, "%s", module_name);

    _g_proc_tbl_list[i].parent_proc_dir = (parent_entry) ? parent_entry : os_proc_entry;
    _g_proc_tbl_list[i].module_proc_dir = proc_mkdir(module_name, _g_proc_tbl_list[i].parent_proc_dir);

    module_proc_dir = _g_proc_tbl_list[i].module_proc_dir;

    for (j = 0; pTable[j].name ; j++)
    {
        entry_mode = (pTable[j].flag & OS_PROC_FLAG_WRITE) ? 0644 : 0444;

        if (pTable[j].flag & (OS_PROC_FLAG_SEQRD | OS_PROC_FLAG_SEQRW))
        {
            proc_create_data(pTable[j].name, entry_mode,
                             _g_proc_tbl_list[i].module_proc_dir,
                             pTable[j].fop, (void*)pTable[j].data);
        }
        else
        {
            proc_create_data(pTable[j].name, entry_mode,
                             _g_proc_tbl_list[i].module_proc_dir,
                             &_g_proc_module_fops,
                             (void*)MK_PROC_DATA(i, pTable[j].id));
        }
    }

    _g_proc_tbl_list[i].max_proc_num = j;

function_exit:
    OS_UnlockMutex(&proc_mtx);

    return module_proc_dir;
}

/**
 * remove proc entry for each module
 *
 * @param   base_name [IN] base module name
 * @returns RET_OK(0) if success, none zero for otherwise
 *
*/
int         OS_PROC_RemoveEntry(const char*        module_name)
{
    int     i, j;
    int     ret;
    MOD_PROC_TBL_T  n;

    if (NULL == module_name)
    {
        DBG_PRINT_WARNING("null argument\n");
        return RET_INVALID_PARAMS;
    }

    ret = OS_LockMutex(&proc_mtx);

    for (i = 0 ; i < MAX_PROC_LIST ; i++)
    {
        if (!*(_g_proc_tbl_list[i].module_name)) continue;

        if (!strcmp(_g_proc_tbl_list[i].module_name, module_name))
        {
            n = _g_proc_tbl_list[i];
            memset(&_g_proc_tbl_list[i], 0x0, sizeof(MOD_PROC_TBL_T));
            break;
        }
    }

    if (i >= MAX_PROC_LIST)
    {
        ret = RET_INVALID_PARAMS; goto function_exit;
    }

    for (j = 0; n.module_proc_table[j].name ; j++)
    {
        remove_proc_entry(n.module_proc_table[j].name, n.module_proc_dir);
    }

    remove_proc_entry(n.module_name, n.parent_proc_dir);

    ret = 0;

function_exit:
    OS_UnlockMutex(&proc_mtx);

    return ret;
}
EXPORT_SYMBOL(OS_PROC_RemoveEntry);

/**
 * flush all proc entries
 *
*/
void        OS_PROC_FlushEntry(void)
{
    int i, j;
    int ret;
    MOD_PROC_TBL_T  n;

    ret = OS_LockMutex(&proc_mtx);

    for (i = 0; i < MAX_PROC_LIST ; i++)
    {
        n = _g_proc_tbl_list[i];

        if (!n.module_proc_table) continue;

        n = _g_proc_tbl_list[i];

        for (j = 0; n.module_proc_table[j].name ; j++)
        {
            remove_proc_entry(n.module_proc_table[j].name, n.module_proc_dir);
        }

        memset(&_g_proc_tbl_list[i], 0x0, sizeof(MOD_PROC_TBL_T));
        remove_proc_entry(n.module_name, os_proc_entry);
    }

    OS_UnlockMutex(&proc_mtx);
}

static ssize_t _OS_PROC_Reader(struct file* file, char __user* buf, size_t size, loff_t* ppos)
{
    int op_rc  = RET_ERROR;
    char* kbuf = NULL;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    void* data = pde_data(file->f_inode);
#else
    void* data = PDE_DATA(file->f_inode);
#endif
    UINT32 moduleId = GET_MODULE_ID((long)data);
    UINT32 procId = GET_PROC_ID((long)data);

    OS_PROC_READ_FUNC_T user_reader = NULL;
    int len = 0;

    if (moduleId >= MAX_PROC_LIST)
    {
        DBG_PRINT_WARNING("unknown module (%d)\n", moduleId);
        /* we've finished to read, return 0 */
        return -EIO;
    }

    if (*ppos > 0) goto read_proc_exit;

    kbuf = OS_Malloc(OS_PROC_RD_BUF_SZ);
    __CHECK_IF_ERROR(!kbuf, printk, goto read_proc_exit, "can't alloc %d\n", OS_PROC_RD_BUF_SZ);

    user_reader = _g_proc_tbl_list[moduleId].user_reader;

    if (user_reader)
    {
        len = user_reader(procId, kbuf);

        if (len > 0)
        {
            __CHECK_IF_ERROR(copy_to_user(buf, kbuf, len) > 0, printk, goto read_proc_exit, "can't copy %d bytes\n", len);
        }
    }

    *ppos += len;
    op_rc = RET_OK; /* all work done */
read_proc_exit:

    if (kbuf) OS_Free(kbuf);

    return (op_rc == RET_OK) ? len : 0;
}

static ssize_t _OS_PROC_Writer(struct file* file, const char __user* buf, size_t size, loff_t* ppos)
{
    int i;
    char msg[OS_PROC_WR_BUF_SZ];

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    void* data = pde_data(file->f_inode);
#else
    void* data = PDE_DATA(file->f_inode);
#endif
    UINT32 moduleId = GET_MODULE_ID((long)data);
    UINT32 procId = GET_PROC_ID((long)data);

    OS_PROC_WRITE_FUNC_T user_writer = NULL;

    if (moduleId >= MAX_PROC_LIST)
    {
        DBG_PRINT_WARNING("unknown module (%d)\n", moduleId);
        /* we've finished to write, return 0 */
        return -EIO;
    }

    /* copy buffer to internal msg */
    if (size > (OS_PROC_WR_BUF_SZ - 1))
        size = OS_PROC_WR_BUF_SZ - 1;

    for (i = 0; i < size; i++)
    {
        get_user(msg[i], buf + i);
    }

    msg[i] = '\0';

    user_writer = _g_proc_tbl_list[moduleId].user_writer;

    if (user_writer)
        return user_writer(procId, msg);

    return size;
}

#endif


/*========================================================================================

    COMMON

========================================================================================*/
struct proc_dir_entry* os_get_base_proc_entry(void)
{
    return os_proc_entry;
}
EXPORT_SYMBOL(os_get_base_proc_entry);

struct proc_dir_entry* os_get_linuxtv_proc_entry(void)
{
    return os_proc_linuxtv_entry;
}
EXPORT_SYMBOL(os_get_linuxtv_proc_entry);

struct proc_dir_entry* OS_PROC_GetBaseEntry(void)
{
    return os_proc_entry;
}
EXPORT_SYMBOL(OS_PROC_GetBaseEntry);

struct proc_dir_entry* OS_PROC_GetLinuxTvEntry(void)
{
    return os_proc_linuxtv_entry;
}
EXPORT_SYMBOL(OS_PROC_GetLinuxTvEntry);

void OS_PROC_Init(void)
{
    lg1k_proc_frwk_init();
}
EXPORT_SYMBOL(OS_PROC_Init);

void OS_PROC_Cleanup(void)
{
    lg1k_proc_frwk_cleanup();
}
EXPORT_SYMBOL(OS_PROC_Cleanup);

/**
 * Initialize proc utility system.
 * This function should be called at main device initialization
 *
 * @see base_device_init
*/
void lg1k_proc_frwk_init(void)
{
    //os_mutex_init(&proc_mtx, "proc_mtx");

#if 1//def SUPPORT_LEGACY_PROC
    OS_InitMutex(&proc_mtx, OS_SEM_ATTR_DEFAULT);

    _g_proc_tbl_list = (MOD_PROC_TBL_T*)vmalloc(sizeof(MOD_PROC_TBL_T) * MAX_PROC_LIST);
    __CHECK_IF_ERROR(!_g_proc_tbl_list, printk, /* nop */, "-E- out of memory\n");

    memset(_g_proc_tbl_list, 0x0, sizeof(MOD_PROC_TBL_T)*MAX_PROC_LIST);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
    _g_proc_module_fops.proc_read = _OS_PROC_Reader;
    _g_proc_module_fops.proc_write = _OS_PROC_Writer;
#else
    _g_proc_module_fops.read = _OS_PROC_Reader;
    _g_proc_module_fops.write = _OS_PROC_Writer;
#endif
#endif

    // create /proc/lg & /proc/linuxtv-driver proc directory
    os_proc_entry = proc_mkdir(BASE_PROC_NAME, NULL);
    os_proc_linuxtv_entry = proc_mkdir(LINUXTV_PROC_NAME, NULL);

    os_proc_base_dir.proc_entry = os_proc_entry;
    os_proc_base_dir.name = os_strdup(BASE_PROC_NAME, LX_STR_MAX);

    lg1k_logm_noti("os_proc_frwk initialized\n");
}

/**
 * Cleanup proc utility system
 * This function should be called at main deivce cleanup
 *
 * @see base_device_shutdown
*/
void lg1k_proc_frwk_cleanup(void)
{
#if 1//def SUPPORT_LEGACY_PROC
    OS_PROC_FlushEntry();
#endif

    remove_proc_entry(BASE_PROC_NAME, NULL);
    remove_proc_entry(LINUXTV_PROC_NAME, NULL);
}

/** @} */
/** @} */
