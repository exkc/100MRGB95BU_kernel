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
 *  @author     raxis.lim
 *  @version    1.0
 *  @date       2021-04-01
 *  @note       Additional information.
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "proc_util.h"
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hw_o26.h"

#include <linux/seq_file.h>
#include <linux/delay.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <linux/sched/clock.h>
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
    PROC_ID_O26_DIAG_HW,
    PROC_ID_O26_HEALTH_CHECK,
    PROC_ID_O26_ESTREAMER_WRITE,
    PROC_ID_O26_TEST_RECONFIG,
    PROC_ID_O26_TEST_MIRROR,
    PROC_ID_O26_TEST_MIXER_MUTE,
    PROC_ID_O26_MAX
};

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static  void    FBDEV_O26_PROC_DiagHW(struct seq_file* m);
static  void    FBDEV_O26_PROC_HealthCheck(struct seq_file* m);

static int FBDEV_O26_ReadProcFunc(UINT32 procId, char* buffer);
static int FBDEV_O26_WriteProcFunc(UINT32 procId, char* buffer);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
#ifdef OS_API_VERSION
static int fbdev_o26_proc_read_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return FBDEV_O26_ReadProcFunc(procId, buffer);
}

static int fbdev_o26_proc_write_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return FBDEV_O26_WriteProcFunc(procId, buffer);
}

static int fbdev_o26_proc_diag(struct seq_file* m, void* data)
{
    FBDEV_O26_PROC_DiagHW(m);
    return 0;
}

static int fbdev_o26_proc_check_health(struct seq_file* m, void* data)
{
    FBDEV_O26_PROC_HealthCheck(m);
    return 0;
}

#else
OS_PROC_SEQRD_DEFINE(fbdev_o26_hw_diag_proc_fops, FBDEV_O26_PROC_DiagHW)
OS_PROC_SEQRD_DEFINE(fbdev_o26_hw_health_check_proc_fops, FBDEV_O26_PROC_HealthCheck)

static const OS_PROC_DESC_TABLE_T g_fbdev_o26_device_proc_table[] =
{
    { "diag",           PROC_ID_O26_DIAG_HW,        OS_PROC_FLAG_SEQRD, (void*)& fbdev_o26_hw_diag_proc_fops },
    { "hw_ctx",         PROC_ID_O26_DIAG_HW,        OS_PROC_FLAG_SEQRD, (void*)& fbdev_o26_hw_diag_proc_fops },
    { "check_stuck",    PROC_ID_O26_HEALTH_CHECK,   OS_PROC_FLAG_SEQRD, (void*)& fbdev_o26_hw_health_check_proc_fops },
    { "estreamer_write", PROC_ID_O26_ESTREAMER_WRITE, OS_PROC_FLAG_WRITE },
    { "test_reconfig",  PROC_ID_O26_TEST_RECONFIG,  OS_PROC_FLAG_WRITE },
    { "mirror_test",    PROC_ID_O26_TEST_MIRROR,    OS_PROC_FLAG_WRITE },
    {  NULL,            PROC_ID_O26_MAX, 0 }
};
#endif

/*========================================================================================
    Implementation Group
========================================================================================*/
static  void    FBDEV_O26_PROC_DiagHW(struct seq_file* m)
{
    FBDEV_O26_CMN_DiagHW(m);
}

static  void    FBDEV_O26_PROC_HealthCheck(struct seq_file* m)
{
    FIXME_NOTE("OSD 모니터 레지스터 확인 필요. 미구현")

#if 0
    UINT32 val;

    OSD_PRE_RdFL(osd_status_state_line);
    OSD_PRE_Rd01(osd_status_state_line, sc_req_line_i, val);

    seq_printf(m, "line_status=0x%08x\n", val);

    UINT64 time_start = local_clock();
    UINT32 diff_ns;

    for (i = 1000; i > 0; i--)
    {
        OSDX_CTRL_RdFL(osd_status_mon_data[0], reg_status_mon_data);
        mon_reg = OSDX_CTRL_Rd(osd_status_mon_data[0], reg_status_mon_data);

        diff_ns = (UINT32)local_clock() - time_start;

        /* print diff_us & mon_data */
        seq_printf(m, "%8d %8d %8d\n", diff_ns / 1000, mon_reg, (mon_reg & ~0x40000));

        udelay(100);
    }

#endif
}

static int FBDEV_O26_ReadProcFunc(UINT32 procId, char* buffer)
{
    int ret;

    /* TODO: add your proc_write implementation */
    switch (procId)
    {
        default:
        {
            ret = sprintf(buffer, "%s(%d)\n", "unimplemented read proc", procId);
        }
    }

    return ret;
}

static int FBDEV_O26_WriteProcFunc(UINT32 procId, char* command)
{
    switch (procId)
    {
        case PROC_ID_O26_ESTREAMER_WRITE:
        {
            FIXME_NOTE("미구현 혹은 미지원")
#if 0
            UINT32  fbmem;
            int     width = 1024;
            int     height = 4320;
            int     xoffset = 0;
            int     en      = 1;

            sscanf(command, " 0x%x", &fbmem);

            FBDEV_NOTI("++ write estreamer y:0x%08x c:0x%08x xoff:%d en:%d\n", fbmem, fbmem + (width * height), xoffset, en);

            OS_WrReg(0xC9011520, fbmem);
            OS_WrReg(0xC9011524, fbmem + (width * height));
            OS_WrReg(0xC9011528, (en << 16) | (xoffset & 0xffff));
#endif
        }
        break;

        case PROC_ID_O26_TEST_RECONFIG:
        {
            UINT32 w, h;
            OSDX_DESC_T desc;

            sscanf(command, " %d %d", &w, &h);

            FBDEV_O26_CMN_ReadOSDXDesc(0, &desc, OSDX_DESC_FLAG_HDR_2);

            desc.osd_ctrl_hdr2.osd_hdr_w_out = w;
            desc.osd_ctrl_hdr2.osd_hdr_h_out = h;

            FBDEV_O26_CMN_WriteOSDXDesc(0, &desc, OSDX_DESC_FLAG_HDR_2);
        }
        break;

        case PROC_ID_O26_TEST_MIRROR:
        {
            UINT32 val;
            sscanf(command, " %d", &val);
            FBDEV_O26_CMN_MirrorCtrl(val);
        }
        break;

        case PROC_ID_O26_TEST_MIXER_MUTE:
        {
            UINT32 en;
            UINT32 color;

            sscanf(command, " %d %x", &en, &color);

            FBDEV_O26_CMN_SetMixerMute(en, color);
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

void    FBDEV_O26_CreateProc(struct proc_dir_entry* parent_proc)
{
#ifdef OS_API_VERSION
    struct os_proc* pdir = (struct os_proc*)parent_proc;

    struct os_proc* chipdir = os_proc_create_dir(pdir, "chip", fbdev_o26_proc_read_handler, fbdev_o26_proc_write_handler);

    os_proc_create_file(chipdir, "test_reconfig", PROC_ID_O26_TEST_RECONFIG, NULL);
    os_proc_create_file(chipdir, "mirror_test", PROC_ID_O26_TEST_MIRROR, NULL);
    os_proc_create_file(chipdir, "estreamer_write", PROC_ID_O26_ESTREAMER_WRITE, NULL);
    os_proc_create_file(chipdir, "mixer_mute", PROC_ID_O26_TEST_MIXER_MUTE, NULL);

    os_proc_create_seq_file(chipdir, "diag", fbdev_o26_proc_diag, NULL, NULL);
    os_proc_create_seq_file(chipdir, "check_stuck", fbdev_o26_proc_check_health, NULL, NULL);

#else
    OS_PROC_CreateEntry("chip", parent_proc, (OS_PROC_DESC_TABLE_T*)g_fbdev_o26_device_proc_table,
                        FBDEV_O26_ReadProcFunc,
                        FBDEV_O26_WriteProcFunc);
#endif
}

