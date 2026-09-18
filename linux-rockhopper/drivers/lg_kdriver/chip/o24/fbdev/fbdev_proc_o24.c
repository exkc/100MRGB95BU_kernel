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
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hw_o24.h"
#include "osd_reg_o24.h"
#include "osd_shp_reg_o24.h"
#include "osd_afbc_reg_o24.h"
#include "osd_afrc_reg_o24.h"
#include "osd_mif0_reg_o24.h"
#include "osd_mif1_reg_o24.h"
#include "osd_top_ctrl_reg_o24.h"
#include "osd_top_ctrl1_reg_o24.h"

#include "os_util.h"
#include "proc_util.h"
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
    PROC_ID_O24_OSD_SR  = 0,
    PROC_ID_O24_OSD_SR_GAIN,
    PROC_ID_O24_DIAG_HW,
    PROC_ID_O24_HEALTH_CHECK,
    PROC_ID_O24_ESTREAMER_WRITE,
    PROC_ID_O24_TEST_RECONFIG,
    PROC_ID_O24_TEST_MIRROR,
    PROC_ID_O24_MAX
};

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int FBDEV_O24_CMN_MirrorCtrl(BOOLEAN v_mirror_en);


/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static  void    FBDEV_O24_PROC_DiagHW(struct seq_file* m);
static  void    FBDEV_O24_PROC_HealthCheck(struct seq_file* m);

static int FBDEV_O24_ReadProcFunc(UINT32 procId, char* buffer);
static int FBDEV_O24_WriteProcFunc(UINT32 procId, char* buffer);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
#ifdef OS_API_VERSION
static int fbdev_o24_proc_read_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return FBDEV_O24_ReadProcFunc(procId, buffer);
}

static int fbdev_o24_proc_write_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return FBDEV_O24_WriteProcFunc(procId, buffer);
}

static int fbdev_o24_proc_diag(struct seq_file* m, void* data)
{
    FBDEV_O24_PROC_DiagHW(m);
    return 0;
}

static int fbdev_o24_proc_check_health(struct seq_file* m, void* data)
{
    FBDEV_O24_PROC_HealthCheck(m);
    return 0;
}

#else
OS_PROC_SEQRD_DEFINE(fbdev_o24_hw_diag_proc_fops, FBDEV_O24_PROC_DiagHW)
OS_PROC_SEQRD_DEFINE(fbdev_o24_hw_health_check_proc_fops, FBDEV_O24_PROC_HealthCheck)

static const OS_PROC_DESC_TABLE_T g_fbdev_o24_device_proc_table[] =
{
    { "osd_sr",         PROC_ID_O24_OSD_SR,         OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { "osd_sr_gain",    PROC_ID_O24_OSD_SR_GAIN,    OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
    { "diag",           PROC_ID_O24_DIAG_HW,        OS_PROC_FLAG_SEQRD, (void*)& fbdev_o24_hw_diag_proc_fops },
    { "hw_ctx",         PROC_ID_O24_DIAG_HW,        OS_PROC_FLAG_SEQRD, (void*)& fbdev_o24_hw_diag_proc_fops },
    { "check_stuck",    PROC_ID_O24_HEALTH_CHECK,   OS_PROC_FLAG_SEQRD, (void*)& fbdev_o24_hw_health_check_proc_fops },
    { "estreamer_write", PROC_ID_O24_ESTREAMER_WRITE, OS_PROC_FLAG_WRITE },
    { "test_reconfig",  PROC_ID_O24_TEST_RECONFIG,  OS_PROC_FLAG_WRITE },
    { "mirror_test",    PROC_ID_O24_TEST_MIRROR,    OS_PROC_FLAG_WRITE },
    {  NULL,            PROC_ID_O24_MAX, 0 }
};
#endif

/*========================================================================================
    Implementation Group
========================================================================================*/
static  void    FBDEV_O24_PROC_DiagHW(struct seq_file* m)
{
    FBDEV_O24_CMN_DiagHW(m);
}

static  void    FBDEV_O24_PROC_HealthCheck(struct seq_file* m)
{
    int i;
    UINT32  mon_reg;

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
}

static int FBDEV_O24_ReadProcFunc(UINT32 procId, char* buffer)
{
    int ret;

    /* TODO: add your proc_write implementation */
    switch (procId)
    {
        case PROC_ID_O24_OSD_SR:
        {
            int len = 0;
            len += sprintf(buffer + len, "[usage] echo value > /proc/lg/fbdev/chip/osd_sr\n");
            len += sprintf(buffer + len, "        value = 0:off, 1:on\n");
            ret = len;
        }
        break;

        case PROC_ID_O24_OSD_SR_GAIN:
        {
            UINT32 gain;
            int len = 0;

            FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

            OSD_SHP_CTRL_RdFL(shp_lti_ctrl_00);
            OSD_SHP_CTRL_Rd01(shp_lti_ctrl_00, reg_lti_2d_gain, gain);

            /* print user-requested gain value & real HW value which normalized to 8bit */
            len += sprintf(buffer + len, "sw=%3d hw=%3dn", hw_ctx->sr_ctrl[LX_FBDEV_ID_OSD0].ti_gain, gain);
            len += sprintf(buffer + len, "[usage] echo value > /proc/lg/fbdev/chip/osd_sr_gain\n");
            len += sprintf(buffer + len, "        value = 0~255\n");
            ret = len;
        }
        break;

        default:
        {
            ret = sprintf(buffer, "%s(%d)\n", "unimplemented read proc", procId);
        }
    }

    return ret;
}

static int FBDEV_O24_WriteProcFunc(UINT32 procId, char* command)
{
    switch (procId)
    {
        case PROC_ID_O24_OSD_SR:
        {
            int onoff;

            sscanf(command, " %d", &onoff);

            FBDEV_O24_CMN_SRCtrl((onoff == 1) ? TRUE : FALSE);
        }
        break;

        case PROC_ID_O24_OSD_SR_GAIN:
        {
            UINT32 gain;
            FBDEV_O24_HW_CTX_T* hw_ctx = FBDEV_O24_GET_HW_CTX();

            sscanf(command, " 0x%x", &gain);

            /* if gain is not valid 8bit value, DO NOT change HW gain configuration */
            if (gain & 0xffffff00) break;

            hw_ctx->sr_ctrl[LX_FBDEV_ID_OSD0].ti_gain = gain;

            OSD_SHP_CTRL_RdFL(shp_lti_ctrl_00);
            OSD_SHP_CTRL_Wr01(shp_lti_ctrl_00, reg_lti_2d_gain, gain);
            OSD_SHP_CTRL_WrFL(shp_lti_ctrl_00);
        }
        break;

        case PROC_ID_O24_ESTREAMER_WRITE:
        {
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
        }
        break;

        case PROC_ID_O24_TEST_RECONFIG:
        {
            /* 테스트 목적으로 OSD 재설정이 필요할 경우 호출. 배포시에는 삭제할것  */

            UINT32 w, h;

            sscanf(command, " %d %d", &w, &h);

            OSDX_CTRL_RdFL(osdx_ctrl[0], osd_ctrl_hdr2);
            OSDX_CTRL_Wr01(osdx_ctrl[0], osd_ctrl_hdr2, osd_hdr_w_out, w);
            OSDX_CTRL_Wr01(osdx_ctrl[0], osd_ctrl_hdr2, osd_hdr_h_out, h);
            FBDEV_NOTI("fb(%d) flush OSD_CTRL_HDR2. %dx%d\n", 0, w, h);
            OSDX_CTRL_WrFL(osdx_ctrl[0], osd_ctrl_hdr2);
        }
        break;

        case PROC_ID_O24_TEST_MIRROR:
        {
            UINT32 val;
            sscanf(command, " %d", &val);
            FBDEV_O24_CMN_MirrorCtrl(val);
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

void    FBDEV_O24_CreateProc(struct proc_dir_entry* parent_proc)
{
#ifdef OS_API_VERSION
    struct os_proc* pdir = (struct os_proc*)parent_proc;

    struct os_proc* chipdir = os_proc_create_dir(pdir, "chip", fbdev_o24_proc_read_handler, fbdev_o24_proc_write_handler);

    os_proc_create_file(chipdir, "osd_sr", PROC_ID_O24_OSD_SR, NULL);
    os_proc_create_file(chipdir, "osd_sr_gain", PROC_ID_O24_OSD_SR_GAIN, NULL);
    os_proc_create_file(chipdir, "estreamer_write", PROC_ID_O24_ESTREAMER_WRITE, NULL);
    os_proc_create_file(chipdir, "test_reconfig", PROC_ID_O24_TEST_RECONFIG, NULL);
    os_proc_create_file(chipdir, "mirror_test", PROC_ID_O24_TEST_MIRROR, NULL);

    os_proc_create_seq_file(chipdir, "diag", fbdev_o24_proc_diag, NULL, NULL);
    os_proc_create_seq_file(chipdir, "check_stuck", fbdev_o24_proc_check_health, NULL, NULL);

#else
    OS_PROC_CreateEntry("chip", parent_proc, (OS_PROC_DESC_TABLE_T*)g_fbdev_o24_device_proc_table,
                        FBDEV_O24_ReadProcFunc,
                        FBDEV_O24_WriteProcFunc);
#endif
}

