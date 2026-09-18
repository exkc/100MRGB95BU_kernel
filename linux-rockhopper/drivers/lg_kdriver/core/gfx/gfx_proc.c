/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as publisrc_hed by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  Linux proc interface for gfx device.
 *  gfx device will teach you how to make device driver with new platform.
 *
 *  author      raxis.lim (raxis.lim@lge.com).lim (raxis.lim@lge.com)
 *  version     1.0
 *  date        2009.12.30
 *  note        Additional information.
 *
 *  @addtogroup lg1150_gfx
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include "proc_util.h"
#include "gfx_impl.h"
#include "gfx_export.h"

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
    PROC_ID_CMD_DELAY,
    PROC_ID_MEM_STAT,
    PROC_ID_REG_DUMP,
    PROC_ID_SURFACE,
    PROC_ID_PID_LIST,
    PROC_ID_STATUS,
    PROC_ID_PM_STATUS,
    PROC_ID_RESET,
    PROC_ID_SYNC_TMOUT,
    PROC_ID_CLK_CTL,
    PROC_ID_USER_COMMAND,
    PROC_ID_PM_TEST,
    PROC_ID_DRAW_TEST,
    PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern char* simple_strtok(char* s, const char* delim, char** save_ptr);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
//extern GFX_SURFACE_OBJ_T      *g_gfx_surf_list;

#if 0
extern volatile GFX_REG_MAP_T*   g_gfx_reg_l8;
extern GFX_REG_MAP_T*            g_gfx_reg_l8_cache;
#endif

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int  _GFX_PROC_ReadFunc(UINT32 procId, char* buffer);
static int _GFX_PROC_WriteFunc(UINT32 procId, char* command);

extern void GFX_ReportSurfaceList(struct seq_file* m);
extern void GFX_ReportPIDRefList(struct seq_file* m);
extern void GFX_ReportStatus(struct seq_file* m);
extern void GFX_ReportPMStatus(struct seq_file* m);

OS_PROC_SEQRD_DEFINE(gfx_proc_slist_fops,   GFX_ReportSurfaceList)
OS_PROC_SEQRD_DEFINE(gfx_proc_pidlist_fops, GFX_ReportPIDRefList)
OS_PROC_SEQRD_DEFINE(gfx_proc_status_fops,  GFX_ReportStatus)
OS_PROC_SEQRD_DEFINE(gfx_proc_pm_status_fops, GFX_ReportPMStatus)

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static OS_PROC_DESC_TABLE_T _g_gfx_device_proc_table[] =
{
    { "author",     PROC_ID_AUTHOR,   OS_PROC_FLAG_READ },
    { "cmd_delay",  PROC_ID_CMD_DELAY,  OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { "mem_stat",   PROC_ID_MEM_STAT,  OS_PROC_FLAG_READ },
    { "surface",    PROC_ID_SURFACE,    OS_PROC_FLAG_SEQRD, (void*)& gfx_proc_slist_fops },
    { "pidref",     PROC_ID_PID_LIST,   OS_PROC_FLAG_SEQRD, (void*)& gfx_proc_pidlist_fops },
    { "reg_dump",   PROC_ID_REG_DUMP,  OS_PROC_FLAG_READ },
    { "status",     PROC_ID_STATUS,     OS_PROC_FLAG_SEQRD, (void*)& gfx_proc_status_fops },
    { "pm_status",  PROC_ID_STATUS,     OS_PROC_FLAG_SEQRD, (void*)& gfx_proc_pm_status_fops },
    { "reset",      PROC_ID_RESET,      OS_PROC_FLAG_WRITE },
    { "synctm",     PROC_ID_SYNC_TMOUT, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { "clkctl",     PROC_ID_CLK_CTL,    OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { "user_command", PROC_ID_USER_COMMAND, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { "pm_test",    PROC_ID_PM_TEST,    OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { "draw_test",  PROC_ID_DRAW_TEST,  OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { NULL,         PROC_ID_MAX, 0 }
};

/*========================================================================================
    Implementation Group
========================================================================================*/
/* initialize proc utility for gfx device
 *
 * @see GFX_Init
*/
void    GFX_PROC_Init(void)
{
    OS_PROC_CreateEntryEx(GFX_MODULE, _g_gfx_device_proc_table,
                          _GFX_PROC_ReadFunc,
                          _GFX_PROC_WriteFunc);
}

/* cleanup proc utility for gfx device
 *
 * @see GFX_Cleanup
*/
void    GFX_PROC_Cleanup(void)
{
    OS_PROC_RemoveEntry(GFX_MODULE);
}

/*
 * read_proc implementation of gfx device
 *
*/
static int  _GFX_PROC_ReadFunc(UINT32 procId, char* buffer)
{
    int     ret = 0;

    /* TODO: add your proc_write implementation */
    switch (procId)
    {
        case PROC_ID_AUTHOR:
        {
            ret = snprintf(buffer, 256, "raxis.lim (raxis.lim@lge.com)\n");
        }
        break;

        case PROC_ID_CMD_DELAY:
        {
            UINT32  cmd_delay;

            (void)GFX_GetCommandDelay(&cmd_delay);
            ret = sprintf(buffer, "-- cmd delay : 0x%x (%d)\n", cmd_delay, cmd_delay);
        }
        break;

        /* dump GFX memory status */
        case PROC_ID_MEM_STAT:
        {
            int i;
            int len;
            LX_GFX_MEM_STAT_T   stat;
            (void)GFX_GetSurfaceMemoryStat(&stat);

            len = 0;
            len += sprintf(buffer + len, "-- mem base   : %6d MB (0x%x - physical)\n", ((UINT32)stat.surface_mem_base) >> 20,
                           stat.surface_mem_base);
            len += sprintf(buffer + len, "-- mem length : %6d MB (%9d)\n", stat.surface_mem_length >> 20, stat.surface_mem_length);
            len += sprintf(buffer + len, "-- mem rgn    : %6d\n", CONFIG_LX_GFX_MEM_RGN_NUM);
            {
                stat.surface_mem_length = 0;

                for (i = 0; i < CONFIG_LX_GFX_MEM_RGN_NUM; i++)
                {
                    len += sprintf(buffer + len, "-- mem len[%d] : %6d MB (%9d)\n", i, gMemCfgGfx.surface[i].size >> 20,
                                   gMemCfgGfx.surface[i].size);
                    stat.surface_mem_length += gMemCfgGfx.surface[i].size;
                }
            }
            len += sprintf(buffer + len, "-- alloc size : %6d MB (%9d)\n", stat.surface_mem_alloc_size >> 20,
                           stat.surface_mem_alloc_size);
            len += sprintf(buffer + len, "-- free  size : %6d MB (%9d)\n", stat.surface_mem_free_size >> 20,
                           stat.surface_mem_free_size);
            len += sprintf(buffer + len, "-- alloc cnt  : %6d\n", stat.surface_alloc_num);

            ret = len;
        }
        break;

        /* dump GFX register */
        case PROC_ID_REG_DUMP:
        {
            GFX_DumpRegister();
            ret = sprintf(buffer, "ok\n");
        }
        break;

        case PROC_ID_SYNC_TMOUT:
        {
            int len = 0;
            len += sprintf(buffer + len, "sync wait timeout = %d ms\n",   g_gfx_cfg.sync_wait_timeout);
            len += sprintf(buffer + len, "fail retry count  = %d \n",     g_gfx_cfg.sync_fail_retry_count);
            ret = len;
        }
        break;

        case PROC_ID_CLK_CTL:
        {
            ret = snprintf(buffer, 256, "%s\n", GFX_ClkCheck() ? "on" : "off");
        }
        break;

        case PROC_ID_PM_TEST:
        {
            ret = snprintf(buffer, 256, "<usage> echo runtime_suspend | runtime_resume > pm_test\n");
        }
        break;

        case PROC_ID_DRAW_TEST:
        {
            ret = snprintf(buffer, 256, "<usage> echo fill paddr stride width height color > draw_test\n");
            ret = snprintf(buffer, 256,
                           "<usage> echo blit src_addr src_stride src_width src_height dst_addr dst_stride dst_width dst_height > draw_test\n");
            ret = snprintf(buffer, 256, "<usage> echo free > draw_test\n");
        }
        break;

        default:
        {
            ret = snprintf(buffer, 256, "unimplemented read proc(%d)\n", procId);
        }
    }

    return ret;
}

/*
 * write_proc implementation of gfx device
 *
*/
static int _GFX_PROC_WriteFunc(UINT32 procId, char* command)
{
    int command_len = (command) ? strlen(command) : 0;

    if (command_len == 0)
    {
        GFX_ERROR("null or empty command\n");
        return 0;
    }

    /* TODO: add your proc_write implementation */
    switch (procId)
    {
        case PROC_ID_CMD_DELAY:
        {
            char*   endp;
            UINT32  cmd_delay;

            cmd_delay = simple_strtoul(command, &endp, 16);

            (void)GFX_SetCommandDelay((cmd_delay > 0x7ff) ? 0x7ff : 0x0);
            (void)GFX_GetCommandDelay(&cmd_delay);
            printk("-- cmd delay : 0x%x (%d)\n", cmd_delay, cmd_delay);
        }
        break;

        case PROC_ID_RESET:
        {

        }
        break;

        case PROC_ID_SYNC_TMOUT:
        {
            int timeout, retry;
            sscanf(command, " %d %d", &timeout, &retry);

            g_gfx_cfg.sync_wait_timeout = timeout;
            g_gfx_cfg.sync_fail_retry_count = retry;
        }
        break;

        case PROC_ID_CLK_CTL:
        {
            int clk_on;
            sscanf(command, " %d", &clk_on);

            if (clk_on) GFX_RunClkOnCommand();
            else        GFX_RunClkOffCommand();
        }
        break;

        case PROC_ID_USER_COMMAND:
        {
            GFX_ExecuteUserCommand(command);
        }
        break;

        case PROC_ID_PM_TEST:
        {
            GFX_ExecutePMTest(command);
        }
        break;

        case PROC_ID_DRAW_TEST:
        {
            phys_addr_t src_addr = 0x0;
            int src_w = 0;
            int src_h = 0;
            int sstride = 0;

            phys_addr_t dst_addr = 0x0;
            int dst_w = 0;
            int dst_h = 0;
            int dstride = 0;

            unsigned int color = 0x0;

            int gfx_cmd;

            static int src_fd = -1;
            static int dst_fd = -1;

            LX_RECT_T src_rect = { 0, 0, 0, 0 };
            LX_RECT_T dst_rect = { 0, 0, 0, 0 };

            if (strstr(command, "fill"))
            {
                command += strlen("fill");

                sscanf(command, " %llx %d %d %d %x",
                       &dst_addr, &dstride, &dst_w, &dst_h, &color);

                gfx_cmd = 0;
            }
            else if (strstr(command, "blit"))
            {
                command += strlen("blit");

                sscanf(command, " %llx %d %d %d %llx %d %d %d",
                       &src_addr, &sstride, &src_w, &src_h,
                       &dst_addr, &dstride, &dst_w, &dst_h);

                gfx_cmd = 1;
            }
            else if (strstr(command, "free"))
            {
                command += strlen("free");

                gfx_export_lock_device();

                if (src_fd >= 0)
                {
                    gfx_export_free_surface(src_fd);
                    src_fd = -1;
                }

                if (dst_fd >= 0)
                {
                    gfx_export_free_surface(dst_fd);
                    dst_fd = -1;
                }

                gfx_export_unlock_device();
            }
            else
            {
                printk("invalid command\n");
                break;
            }

            src_rect.w = src_w;
            src_rect.h = src_h;
            dst_rect.w = dst_w;
            dst_rect.h = dst_h;

            // free the previous test surface
            if (src_fd >= 0)
            {
                gfx_export_free_surface(src_fd);
                src_fd = -1;
            }

            if (dst_fd >= 0)
            {
                gfx_export_free_surface(dst_fd);
                dst_fd = -1;
            }

            if (src_w && src_h)
            {
                src_fd = gfx_export_alloc_surface(src_addr, sstride, src_w, src_h);
            }

            if (dst_w && dst_h)
            {
                dst_fd = gfx_export_alloc_surface(dst_addr, dstride, dst_w, dst_h);
            }

            GFX_NOTI("src_fd = 0x%x, dst_fd = 0x%x\n", src_fd, dst_fd);

            if (gfx_cmd == 0)
            {
                gfx_export_fill_simple(dst_fd, dst_rect, color);
            }
            else if (gfx_cmd == 1)
            {
                gfx_export_blit_simple(src_fd, src_rect, dst_fd, dst_rect);
            }

            gfx_export_unlock_device();
        }
        break;

        default:
        {
            /* do nothing */
        }
        break;
    }

    return command_len;
}


/** @} */

