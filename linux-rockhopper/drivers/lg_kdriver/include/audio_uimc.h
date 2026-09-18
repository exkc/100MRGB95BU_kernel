#ifndef _KERNEL_DRIVER_AUDIO_UIMC_H_
#define _KERNEL_DRIVER_AUDIO_UIMC_H_

#include <linux/ioctl.h>
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif

#include "ipc/adec_ipc.h"


struct auimc_ipc_header
{
    int timeout;   /* ms */
    uint32_t param_length;
    union
    {
        IpcHeader *header;
        uint32_t compat_data;
        uint64_t compat_sizer;
    };
};

struct auimc_info
{
    int proc_id;
};

struct auimc_module
{
    char name[32];
    int preferred_processor;
    unsigned int uid;   /* output */
};

struct auimc_connect
{
    unsigned int out_uid;
    int out_port;
    unsigned int in_uid;
    int in_port;
};

struct auimc_disconnect
{
    unsigned int uid;
    int port;
};

struct auimc_implement2
{
    char name[32];
    unsigned int rank;
    unsigned int exp_usage;
};

struct auimc_implement
{
    char name[32];
    unsigned int rank;
};

struct auimc_implement_port_buf_def
{
    char name[32];
    int def_num;
    int max_num_au;
    int max_access_size;
};

struct auimc_role
{
    char name[32];
    unsigned int uid;
};

struct auimc_cache
{
    enum
    {
        AUIMC_CACHE_FROMDEV,
        AUIMC_CACHE_TODEV,
    } direction;
    unsigned int shbuf_offset;
    unsigned int offset;
    unsigned int size;
};

#define UIMC_HMA_MMAP_OFFSET        0x10000000
#define UIMC_VMALLOC_MMAP_OFFSET    0x20000000

#define AUIMC_IOC_MAGIC             'M'

#define AUIMC_IO_GET_INFO                       _IOR (AUIMC_IOC_MAGIC, 1, struct auimc_info)
#define AUIMC_IO_IPC_WRITE                      _IOW (AUIMC_IOC_MAGIC, 2, struct auimc_ipc_header)
#define AUIMC_IO_IPC_READ                       _IOW (AUIMC_IOC_MAGIC, 3, struct auimc_ipc_header)
#define AUIMC_IO_ADD_IMPL                       _IOW (AUIMC_IOC_MAGIC, 4, struct auimc_implement)
#define AUIMC_IO_ADD_IMPL2                      _IOW (AUIMC_IOC_MAGIC, 4, struct auimc_implement2)
#define AUIMC_IO_ADD_IMPL_PORT_BUF_DEF          _IOW (AUIMC_IOC_MAGIC, 5, struct auimc_implement_port_buf_def)

#define AUIMC_IO_CREATE_MODULE                  _IOWR(AUIMC_IOC_MAGIC, 6, struct auimc_module)
#define AUIMC_IO_DESTROY_MODULE                 _IOW (AUIMC_IOC_MAGIC, 7, unsigned int)
#define AUIMC_IO_CONNECT_MODULE                 _IOW (AUIMC_IOC_MAGIC, 8, struct auimc_connect)

#define AUIMC_IO_CREATE_LEGACY_MODULE           _IOWR(AUIMC_IOC_MAGIC, 9, unsigned int)
#define AUIMC_IO_DESTROY_LEGACY_MODULE          _IOWR(AUIMC_IOC_MAGIC, 10, unsigned int)

#define AUIMC_IO_SET_ROLE                       _IOW (AUIMC_IOC_MAGIC, 11, struct auimc_role)
#define AUIMC_IO_SEARCH_ROLE                    _IOWR(AUIMC_IOC_MAGIC, 11, struct auimc_role)

#define AUIMC_IO_CACHE_SYNC                     _IOW (AUIMC_IOC_MAGIC, 12, struct auimc_cache)
#define AUIMC_IO_MUNMAP                         _IOW (AUIMC_IOC_MAGIC, 13, unsigned int)

#define AUIMC_IO_DISCONNECT_MODULE_OUTPUT       _IOW (AUIMC_IOC_MAGIC, 14, struct auimc_disconnect)
#define AUIMC_IO_DISCONNECT_MODULE_INPUT        _IOW (AUIMC_IOC_MAGIC, 15, struct auimc_disconnect)
#define AUIMC_IO_SET_PROC_IDLE                  _IOW (AUIMC_IOC_MAGIC, 16, unsigned int)
#define AUIMC_IO_SET_PID                        _IOW (AUIMC_IOC_MAGIC, 20, unsigned int)


#endif
