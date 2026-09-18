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

#ifndef __PROC_UTIL_H__
#define __PROC_UTIL_H__

#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/version.h>
#include "base_types.h"

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/////////////////////////////////////////////////////////////////////////////////////////
//  NEW PROC
//
// 기존 proc 이 너무 테이블에 기반하고 있어 동적 생성이 어려운 점이 있어 새로 만듦
// 각 proc 항목 하나마다 생성 함수를 호출해야 하는 불편함이 있을 수 있으나, 호출 형식이
// 마치 테이블을 사용하는 것 처럼 편할 것이다.
//
// 또한 기존의 simple read, write proc 은 물론 seq read, write 도 쉽게 등록할 수 있다.
//
// 특히 해당 proc 마다 private data 포인터를 넘길 수 있기 때문에, 하나의 proc handler 로
// 다양한 케이스를 대응할 수 있다.
//
/////////////////////////////////////////////////////////////////////////////////////////
struct os_proc;

typedef int (*os_proc_rw_handler)(u32 id, char* buffer, int size, void* data);
typedef int (*os_proc_seq_file_rd_handler)(struct seq_file* s, void* data);
typedef int (*os_proc_seq_file_wr_handler)(const char* buffer, int size, void* data);

struct os_proc* os_proc_create_dir(struct os_proc* pdir, const char* name,
                                   os_proc_rw_handler user_reader, os_proc_rw_handler user_writer);

struct os_proc* os_proc_create_file(struct os_proc* dir, const char* name, u32 id, void* data);

struct os_proc* os_proc_create_seq_file(struct os_proc* dir, const char* name,
                                        os_proc_seq_file_rd_handler rd_handler, os_proc_seq_file_wr_handler, void* data);

// get struct proc_dir_entry info from os_proc object
// get the inux proc_dir_envtry info and make your own proc
struct proc_dir_entry* os_proc_get_entry(struct os_proc* p);

// get linux proc_dir_entry object for /proc/lg and /proc/linuxtv-driver
struct proc_dir_entry* os_get_base_proc_entry(void);
struct proc_dir_entry* os_get_linuxtv_proc_entry(void);

/////////////////////////////////////////////////////////////////////////////////////////
//  LEGACY PROC
//  DO NOT use legacy proc
//
/////////////////////////////////////////////////////////////////////////////////////////
#define OS_PROC_RD_BUF_SZ   4096
#define OS_PROC_WR_BUF_SZ   100

/**
 * Proc attribute flag for OS_PROC_DESC_TABLE_T.
 * READ/WRITE flag can be ORed.
 *
 * @see OS_PROC_DESC_TABLE_T
 */
enum
{
    OS_PROC_FLAG_READ       = 0x0001,   ///< read attribute enabled
    OS_PROC_FLAG_WRITE      = 0x0002,   ///< write attribute eanbled
    OS_PROC_FLAG_SEQRD      = 0x0010,   ///< OS_PROC_DESC_TABLE_T.fop shall be used and proc_create shall be used.
    OS_PROC_FLAG_SEQRW      = 0x0020,   ///< OS_PROC_DESC_TABLE_T.fop shall be used and proc_create shall be used.
    OS_PROC_FLAG_FOP        = OS_PROC_FLAG_SEQRD,
};

/**
 * Proc description table.
 * device driver using proc_util should define its own proc description.
 * by convention, OS_PROC_DESC_TABLE_t is defined at [module_name]_proc.c
 *
 * @code
 * static OS_PROC_DESC_TABLE_t  _g_template_device_proc_table[] =
 * {
 *   { "author",    PROC_ID_AUTHOR  , OS_PROC_FLAG_READ },
 *   { "command",   PROC_ID_COMMAND , OS_PROC_FLAG_WRITE},
 *   { "debug",     PROC_ID_DEBUG   , OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
 *   { "big_debug", PROC_ID_BIG_DEBUG,OS_PROC_FLAG_READ | OS_PROC_FLAG_FOP },
 *   { "big_debug2",PROC_ID_BIG_2   , OS_PROC_FLAG_READ | OS_PROC_FLAG_FOP, &module_private_data },
 *   { NULL,        PROC_ID_MAX     , 0 }
 * };
 * @endcode
 *
 * @see template_proc.c
*/
typedef struct
{
    char*   name;       ///< proc name
    UINT32  id: 16,     ///< unique id used at device driver
            flag: 16;   ///< read/write/seq_file(fop) flag
    void*   fop;        ///< if fop should be overred per-proc_entry base.(i.e. OS_PROC_FLAG_FOP )
    void*   data;       ///< if OS_PROC_FLAG_FOP, proc_entry->data shall be set by this.
}
OS_PROC_DESC_TABLE_T;

#define OS_PROC_DESC_END    { NULL, PROC_ID_MAX, 0 }

/**
 * user-defined read proc function
 * proc_util checks basic error conditions, so you don't need to check any error.
 * basic usage is the same as linux read proc function.
 * you should write something to buf.
 *
 * @see OS_PROC_CreateEntryEx
*/
typedef int (*OS_PROC_READ_FUNC_T)(UINT32 procId, char* buffer);

/**
 * user-defined write proc function
 * proc_util checks basic error conditions, so you don't need to check any error.
 * basic usage is the same as linux read proc function.
 * proc_util passes command which is null terminated string and you need to parse command string.
 *
 * @see OS_PROC_CreateEntryEx
*/
typedef int (*OS_PROC_WRITE_FUNC_T)(UINT32 procId, char* command);

/**
 simple macro to help define seq print with ease.
 OS_PROC_SEQRD_DEFINE is used without any extra data.
 OS_PROC_SEQRD_DEFINE_EX is used to pass extra data to seq_printf handler.
 OS_PROC_SEQRW_DEFINE is EXPERIMENTAL. print something with seq_printf and get something with proc write function.

 @code

 static void osd_reg_dump(struct seq_file* m, void* data)
 {
    seq_printf(m, "data          : %d\n", (int)data);
    seq_printf(m, "dump osd regs : 0x%08x\n", 0xc0035200);
 }

 OS_PROC_SEQRD_DEFINE_EX(g_reg_dump_proc_fops, osd_reg_dump, 0x1234 );

 @endcode
 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))

#define OS_PROC_SEQRD_DEFINE(name,readfn)  \
 static int print_##name(struct seq_file* m, void* v) \
 { \
     readfn(m); return RET_OK;\
 }\
 static int open_##name(struct inode *n, struct file *fl)\
 {\
     return single_open(fl, print_##name, NULL);\
 }\
 \
 static const struct proc_ops name = { \
     .proc_open       = open_##name, \
     .proc_read       = seq_read, \
     .proc_lseek      = seq_lseek, \
     .proc_release    = single_release, \
 };

/** sequential reader with args
 *
 */
#define OS_PROC_SEQRD_DEFINE_EX(name,readfn,data)  \
 static int print_##name(struct seq_file* m, void* v) \
 { \
     readfn(m,(void*)data); return RET_OK;\
 }\
 static int open_##name(struct inode *n, struct file *fl)\
 {\
     return single_open(fl, print_##name, NULL); \
 }\
 \
 static const struct proc_ops name = { \
     .proc_open       = open_##name, \
     .proc_read       = seq_read, \
     .proc_lseek      = seq_lseek, \
     .proc_release    = single_release, \
 };

#define OS_PROC_SEQRW_DEFINE(name,readfn,writefn)  \
 static int print_##name(struct seq_file* m, void* v) \
 { \
     readfn(m); return RET_OK;\
 }\
 static int open_##name(struct inode *n, struct file *fl)\
 {\
     return single_open(fl, print_##name, NULL);\
 }\
 \
 static const struct proc_ops name = { \
     .proc_open       = open_##name, \
     .proc_read       = seq_read, \
     .proc_write      = writefn,  \
     .proc_lseek      = seq_lseek, \
     .proc_release    = single_release, \
 };

#define OS_PROC_SEQRW_DEFINE_EX(name,readfn,writefn)  \
 OS_PROC_SEQRW_DEFINE(name,readfn,writefn)

#else

#define OS_PROC_SEQRD_DEFINE(name,readfn)  \
 static int print_##name(struct seq_file* m, void* v) \
 { \
     readfn(m); return RET_OK;\
 }\
 static int open_##name(struct inode *n, struct file *fl)\
 {\
     return single_open(fl, print_##name, NULL);\
 }\
 \
 static const struct file_operations name = { \
     .open       = open_##name, \
     .read       = seq_read, \
     .llseek     = seq_lseek, \
     .release    = single_release, \
 };

/** sequential reader with args
 *
 */
#define OS_PROC_SEQRD_DEFINE_EX(name,readfn,data)  \
 static int print_##name(struct seq_file* m, void* v) \
 { \
     readfn(m,(void*)data); return RET_OK;\
 }\
 static int open_##name(struct inode *n, struct file *fl)\
 {\
     return single_open(fl, print_##name, NULL); \
 }\
 \
 static const struct file_operations name = { \
     .open       = open_##name, \
     .read       = seq_read, \
     .llseek     = seq_lseek, \
     .release    = single_release, \
 };

#define OS_PROC_SEQRW_DEFINE(name,readfn,writefn)  \
 static int print_##name(struct seq_file* m, void* v) \
 { \
     readfn(m); return RET_OK;\
 }\
 static int open_##name(struct inode *n, struct file *fl)\
 {\
     return single_open(fl, print_##name, NULL);\
 }\
 \
 static const struct file_operations name = { \
     .open       = open_##name, \
     .read       = seq_read, \
     .write      = writefn,  \
     .llseek     = seq_lseek, \
     .release    = single_release, \
 };

#define OS_PROC_SEQRW_DEFINE_EX(name,readfn,writefn)  \
 OS_PROC_SEQRW_DEFINE(name,readfn,writefn)

#endif

/** @} */

extern  struct proc_dir_entry* OS_PROC_CreateEntryEx(const char*    base_name,
        OS_PROC_DESC_TABLE_T* pTable,
        OS_PROC_READ_FUNC_T   read_func,
        OS_PROC_WRITE_FUNC_T  write_func);

extern  struct proc_dir_entry* OS_PROC_CreateEntry(const char* base_name,
        struct proc_dir_entry* parent_entry,
        OS_PROC_DESC_TABLE_T*  pTable,
        OS_PROC_READ_FUNC_T    read_func,
        OS_PROC_WRITE_FUNC_T   write_func);

extern  int  OS_PROC_RemoveEntry(const char*    base_name);
extern  void OS_PROC_FlushEntry(void);

struct proc_dir_entry* OS_PROC_GetBaseEntry(void);
struct proc_dir_entry* OS_PROC_GetLinuxTvEntry(void);

extern void OS_PROC_Init(void);
extern void OS_PROC_Cleanup(void);

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* __PROC_UTIL_H__ */

/** @} */

