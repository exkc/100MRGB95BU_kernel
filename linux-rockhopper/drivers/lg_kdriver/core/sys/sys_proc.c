/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */


/** @file
 *
 *  Linux proc interface for sys device.
 *  sys device will teach you how to make device driver with new platform.
 *
 *  author      ks.hyun (ks.hyun@lge.com)
 *  version     1.0
 *  date        2010.12.13
 *  note        Additional information.
 *
 *  @addtogroup lg1150_sys
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
#define SOC_SCRTEST_MAGIC_CODE      0x5343524E  /* S,C,R,N */

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include "sys_drv.h"
#include "sys_log.h"
#include "sys_io.h"
#include "proc_util.h"
#include "debug_util.h"
#include "base_drv.h"
#include "hma_alloc.h"
#ifdef INCLUDE_KDRV_GFX
#include "gfx_drv.h"
#endif

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
enum
{
    PROC_ID_AUTHOR  = 0,
    PROC_ID_COMMAND,
    PROC_ID_MEM_STAT,
    PROC_ID_SOC_SCRTEST,
    PROC_ID_STATUS,
    PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
void SYS_PROC_Init(void);
void SYS_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void _SYS_PrintStatus(struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
struct os_proc* lg1k_sys_proc_entry;
static int sys_proc_print_status(struct seq_file* m, void* data);

/*========================================================================================
    Implementation Group
========================================================================================*/
static DEFINE_SPINLOCK(soc_scrtest_spinlock);

static void SYS_SOCScreenTest(void)
{
#define M14_SOC_SCRTEST_MAGIC_PHYSADDR      0x7f4c0000  /* reseved area between ham & sys. 0x7eac8000 ~ 0x7f500000 */
#define M14_SOC_TE_PIDF_REG_BASE            0xc0008490  /* TE pidf sram reg */
#define M14_SOC_COREAPB_REG_BASE            0xfd000000  /* coreapb reg */
#define M14_SOC_WATCHDOG_REG_BASE           (M14_SOC_COREAPB_REG_BASE+0x200000) /* WD reg */

    if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M14))
    {
        int i;
        ULONG flags;

        volatile void* magic_vaddr   = (volatile void*)ioremap(M14_SOC_SCRTEST_MAGIC_PHYSADDR, sizeof(UINT32) * 4);
        volatile void* te_pidf_vaddr = (volatile void*)ioremap(M14_SOC_TE_PIDF_REG_BASE, sizeof(UINT32) * 2);
        volatile void* watchdog_vaddr = (volatile void*)ioremap(M14_SOC_WATCHDOG_REG_BASE, 0x1000);

        if (!magic_vaddr)    { printk("can't ioremap magic addr\n"); return; }

        if (!te_pidf_vaddr)  { printk("can't ioremap te_pidf addr\n"); return; }

        if (!watchdog_vaddr) { printk("can't ioremap watchdog reg\n"); return; }

        spin_lock_irqsave(&soc_scrtest_spinlock, flags);                            /* irq disable */

        for (i = 0x3c; i < 0x40; i++)
        {
            __raw_writel(i, (volatile void*)(te_pidf_vaddr + 0x00));                    /* write index=i*/
            __raw_writel(SOC_SCRTEST_MAGIC_CODE, (volatile void*)(te_pidf_vaddr + 0x04)); /* write magic  */
        }

        for (i = 0; i < 4; i++)
        {
            __raw_writel(SOC_SCRTEST_MAGIC_CODE, (volatile void*)(magic_vaddr + (i * 4))); /* write magic */
        }

        __raw_writel(0x2, (volatile void*)(watchdog_vaddr + 0x08));                 /* WD ctrl reg */
        __raw_writel(0x0, (volatile void*)(watchdog_vaddr + 0x00));                 /* WD load reg */

        while (1) OS_UsecDelay(100 * 1000);                                         /* wait for reset */
    }
    else
    {

    }
}


/*
 * read_proc implementation of sys device
 *
*/
static int  _SYS_ReadProcFunction(UINT32 procId, char* buffer)
{
    int     ret;

    /* TODO: add your proc_write implementation */
    switch (procId)
    {
        case PROC_ID_AUTHOR:
        {
            ret = snprintf(buffer, 80, "%s\n", "n/a");
        }
        break;

        case PROC_ID_MEM_STAT:
        {
#if 0   /* not ready */
            LX_MEMCFG_STAT_T cfg_stat;
            LX_GFX_MEM_STAT_T gfx_stat;
            UINT32 total, alloc;

            BASE_MEMCFG_GetStat(&cfg_stat);
            GFX_GetSurfaceMemoryStat(&gfx_stat);
            total = cfg_stat.size;
            alloc = cfg_stat.alloc;
            alloc -= gfx_stat.surface_mem_free_size;
#else
            UINT32 total, alloc;
            total = 0;
            alloc = 0;
#endif
            ret = snprintf(buffer, 80, "total    used\n");
            ret += snprintf(buffer + ret, 80, "%08x %08x\n", total, alloc);
        }
        break;

        default:
        {
            ret = snprintf(buffer, 80, "%s(%d)\n", "unimplemented read proc", procId);
        }
    }

    return ret;
}

/*
 * write_proc implementation of sys device
 *
*/
static int _SYS_WriteProcFunction(UINT32 procId, char* command)
{
    /* TODO: add your proc_write implementation */
    switch (procId)
    {
        case PROC_ID_COMMAND:
        {
            printk("command string : %s\n", command);
        }
        break;

        case PROC_ID_SOC_SCRTEST:
        {
            SYS_SOCScreenTest();
        }
        break;

        default:
        {
            /* do nothing */
        }
        break;
    }

    return strlen(command);
}


static void _SYS_PrintStatus(struct seq_file* m, void* data)
{

    int i;
    char boot_version[80];
    SYS_SOC_CLK_T clk;

    memset(boot_version, 0x0, 80);
    memset(&clk, 0x0, sizeof(clk));

    if (RET_OK != OS_ScanKernelCmdline("bver=%s", boot_version))
    {
        sprintf(boot_version, "n/a");
    }

    /* get detail clock info */
    SYS_IO_ScanClock(&clk, m);

    /* report status */
    if (strlen(boot_version) > 0)
    {
        seq_printf(m, "boot_version: %s\n", boot_version);
    }

    if (clk.cpu_clk > 0)
    {
        seq_printf(m, "cpu_clk: %d MHz\n", clk.cpu_clk);
    }

    if (clk.peri_clk > 0)
    {
        seq_printf(m, "peri_clk: %d MHz\n", clk.peri_clk);
    }

    if (clk.gpu_clk > 0)
    {
        seq_printf(m, "gpu_clk: %d MHz\n", clk.gpu_clk);
    }

    for (i = 0; i < 3; i++)
    {
        if (clk.ddr_clk[i] > 0)
        {
            seq_printf(m, "ddr%d_clk: %d MHz\n", i, clk.ddr_clk[i]);
        }
    }

    seq_printf(m, "ss: %s\n", clk.ss ? "ON" : "OFF");
}

/* http://clm.lge.com/issue/browse/SICDTV-4357
 * create /proc/kdump_mem to notify available memory region for crashcmd
 *
 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0))
static ssize_t sys_proc_read_kdump_meminfo(struct file* file, char __user* buf, size_t size, loff_t* ppos)
{
    phys_addr_t lkmem_addr = 0;
    int lkmem_size = 0;
    int len = 0;
    int ret = RET_ERROR;
    char* kbuf = NULL;

    if (*ppos > 0) return 0;

    kbuf = OS_KMalloc(64);
    __CHECK_IF_ERROR(!kbuf, SYS_ERROR, goto func_exit, "can't alloc %d\n", 64);

    __CHECK_IF_ERROR(RET_OK != hma_pool_info("surface", &lkmem_addr, &lkmem_size),
                     SYS_ERROR, goto func_exit, "can't find surface hma\n");

    len = snprintf(kbuf, 64, "%dM@0x%08x\n", lkmem_size >> 20, (UINT32)lkmem_addr);

    if (len > 0)
    {
        __CHECK_IF_ERROR(copy_to_user(buf, kbuf, len) > 0, SYS_ERROR, goto func_exit, "can't copy %d bytes\n", len);
    }

    *ppos += len;
    ret = RET_OK; /* all work done */
func_exit:

    if (kbuf) OS_Free(kbuf);

    return (ret == RET_OK) ? len : 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static struct proc_ops sys_proc_kdump_meminfo_fops = { .proc_read = sys_proc_read_kdump_meminfo };
#else
static struct file_operations sys_proc_kdump_meminfo_fops = { .read = sys_proc_read_kdump_meminfo };
#endif

static void SYS_PROC_CreateKDumpMemInfo(void)
{
    proc_create_data("kdump_mem", 0444, NULL, &sys_proc_kdump_meminfo_fops, NULL);
}
#else
static void SYS_PROC_CreateKDumpMemInfo(void)
{
    /* do nothing */
}
#endif

/**
 * initialize proc utility for sys device
 *
 * @see SYS_Init
*/
static int sys_read_proc_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return _SYS_ReadProcFunction(procId, buffer);
}

static int sys_write_proc_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return _SYS_WriteProcFunction(procId, buffer);
}

static int sys_proc_print_status(struct seq_file* m, void* data)
{
    _SYS_PrintStatus(m, data);
    return 0;
}

void    SYS_PROC_Init(void)
{
    lg1k_sys_proc_entry = os_proc_create_dir(NULL, "sys", sys_read_proc_handler, sys_write_proc_handler);

    os_proc_create_file(lg1k_sys_proc_entry, "command",  PROC_ID_COMMAND, NULL);
    os_proc_create_file(lg1k_sys_proc_entry, "mem_stat",  PROC_ID_MEM_STAT, NULL);
    os_proc_create_file(lg1k_sys_proc_entry, "soc_screen_test", PROC_ID_SOC_SCRTEST, NULL);

    os_proc_create_seq_file(lg1k_sys_proc_entry, "status", sys_proc_print_status, NULL, NULL);

    SYS_PROC_CreateKDumpMemInfo();
}

/**
 * cleanup proc utility for sys device
 *
 * @see SYS_Cleanup
*/
void    SYS_PROC_Cleanup(void)
{
    OS_PROC_RemoveEntry(SYS_MODULE);
}

/** @} */


