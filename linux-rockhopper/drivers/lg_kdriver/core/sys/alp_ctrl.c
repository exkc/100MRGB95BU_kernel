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

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/seq_file.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "sys_io.h"
#include "sys_drv.h"
#include "sys_log.h"
#include "sys_regs.h"
#include "alp_ctrl.h"
#include "proc_util.h"

#if defined(INCLUDE_O26_CHIP_KDRV)
#include "../../chip/o26/pm/pm_o26common.h"
#endif

#if defined(INCLUDE_O24_CHIP_KDRV)
#include "../../chip/o24/pm/pm_o24common.h"
#endif

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
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
    PROC_ID_DDR_ALP = 0,
    PROC_ID_CPU_ALP,
};


/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
extern struct os_proc* lg1k_sys_proc_entry;

/*----------------------------------------------------------------------------------------
    global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int sys_alp_ctrl_read_proc_handler(UINT32 procId, char* buffer, int size, void* data);
static int sys_alp_ctrl_write_proc_handler(UINT32 procId, char* buffer, int size, void* data);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
// O24, O26 will use pqe_pm instead of runtime pm
#if defined (CHIP_NAME_o24) || defined (CHIP_NAME_o26)
#define RUNTIME_PM_BY_PQE_PM
#endif

#if defined (BUILD_FEATURE_audio_board)
#undef RUNTIME_PM_BY_PQE_PM
#endif

#if !defined (INCLUDE_KDRV_PQE_PM)
#undef RUNTIME_PM_BY_PQE_PM
#endif

#if defined (CHIP_NAME_o24)
static int cpu_alp_mode = 1;
#elif defined (CHIP_NAME_o26)
static int cpu_alp_mode = 1;
#else
static int cpu_alp_mode = 0;
#endif

module_param(cpu_alp_mode, int, 0644);

#if defined (CHIP_NAME_o22)
static int ddr_alp_mode = 1;
#elif defined (CHIP_NAME_o24)
static int ddr_alp_mode = 1;
#elif defined (CHIP_NAME_m23)
static int ddr_alp_mode = 1;
#elif defined (CHIP_NAME_o26)
static int ddr_alp_mode = 1;
#else
static int ddr_alp_mode = 0;
#endif

module_param(ddr_alp_mode, int, 0644);

static int ddr_alp_time_param = 0x3f3;
module_param(ddr_alp_time_param, int, 0644);

/*========================================================================================
    Implementation Group
========================================================================================*/

// DDR ALP 모드에 대한 정보는 아래 JIRA 참조할것
// http://clm.lge.com/issue/browse/SICDTV-10086
// http://clm.lge.com/issue/browse/SICDTV-12972
static int sys_alp_ctrl_enable_ddr_alp_mode(void)
{
    int ret = RET_ERROR;

    if (!ddr_alp_mode)
    {
        SYS_NOTI("DDR_ALP not supported\n");
        return RET_OK;
    }

    SYS_NOTI("DDR_ALP ON - begin\n");

    switch (lx_chip())
    {
#ifdef INCLUDE_O22_CHIP_KDRV

        // see http://clm.lge.com/issue/browse/SICDTV-10086?focusedCommentId=3171150&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3171150
        // TODO :
        // 1. DDR ALP 관련 설정을 kdriver 하는게 맞는지 논의 필요
        // 2. register 필드 파악하여 명확하게 필드만 업데이트 되도록 해야 함
        //
        // (2021/11/05)
        // 1. DDR ALP 모드 진입전 VT tracking off (신뢰성 문제 해결)
        // 2. DDR ALp 모드 해제후 VT tracking on
        //
        // 두개 설정사이의 time margin 은 존재하지 않다고 하나, 10~20 ms 정도의 안정화 시간을 부여함.
        //
        // http://clm.lge.com/issue/browse/SCDCR-4564?focusedCommentId=3578591&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3578591
        // http://clm.lge.com/issue/browse/SCDCR-4564?focusedCommentId=3579162&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3579162
        //
        case LX_CHIP_O22:
        {
            OS_WrReg(0xC67C820C, 0x80000301);
            OS_WrReg(0xF300820C, 0x80000301);

            usleep_range(10000, 20000); // 10~20ms

            OS_WrReg(0xC67C8050, 0x000023D0);
            OS_WrReg(0xF3008050, 0x000023D0);
            OS_WrReg(0xC67C300C, 0x0500F101);
            OS_WrReg(0xF300300C, 0x0500F101);
            OS_WrReg(0xC67C0100, 0x00000003);
            OS_WrReg(0xF3000100, 0x00000003);

            ret = RET_OK;
        }
        break;
#endif

#ifdef INCLUDE_O24_CHIP_KDRV

        // see http://clm.lge.com/issue/browse/SICDTV-12972
        // see http://clm.lge.com/issue/browse/SICDTV-13415
        case LX_CHIP_O24:
        {
            // ;; APB lockup cnt disable
            OS_WrReg(0xC4C0201C, 0x00000000);
            OS_WrReg(0xC400601C, 0x00000000);

            // [PHY][WA] Disable Periodic PHY IO Re-calibration
            OS_WrReg(0xC4D0820C, 0x80000301);
            OS_WrReg(0xC490820C, 0x80000301);

            // Wait 10~20ms
            usleep_range(10000, 20000);

            // [CTRL] Disable Periodic DRAM ZQ Re-calibration
            OS_WrReg(0xC4D0300C, 0x0502F100);
            OS_WrReg(0xC490300C, 0x0502F100);

            // [CTRL] ALP Enable
            OS_WrReg(0xC4D00100, ddr_alp_time_param);
            OS_WrReg(0xC4900100, ddr_alp_time_param);

            // M0 PLL-ON
            OS_WrReg(0xC4D0F010, 0x00C80110); // No Wait Setting in PHY when PLL-ON @ Self-refresh
            OS_WrReg(0xC4D030C0, 0x00004033); // PLL-ON @ Self-refresh

            // M1 PLL-ON
            OS_WrReg(0xC490F010, 0x00C80110); // No Wait Setting in PHY when PLL-ON @ Self-refresh
            OS_WrReg(0xC49030C0, 0x00004033); // PLL-ON @ Self-refresh

            // ;; APB lockup cnt enable
            OS_WrReg(0xC4C0201C, 0x00000001);
            OS_WrReg(0xC400601C, 0x00000001);

            ret = RET_OK;
        }
        break;
#endif

#ifdef INCLUDE_M23_CHIP_KDRV

        case LX_CHIP_M23:
        {
            //;;PLL-ON
            OS_WrReg(0xC4F4F010, 0x00C80110); // ;; No Wait Setting in PHY when PLL-ON @ Self-refresh
            OS_WrReg(0xC4F430C0, 0x00004033); // ;; PLL-ON @ Self-refresh

            //;; [PHY][WA] Disable Periodic PHY IO Re-calibration
            OS_WrReg(0xC4F4820C, 0x80000301);

            //;; Wait 10~20ms
            usleep_range(10000, 20000);

            //;; [CTRL] Disable Periodic DRAM ZQ Re-calibration
            OS_WrReg(0xC4F4300C, 0x0502F100);

            // ;; [CTRL] ALP Enable
            OS_WrReg(0xC4F40100, 0x000003F3);

            ret = RET_OK;
        }
        break;
#endif

#ifdef INCLUDE_O26_CHIP_KDRV

        //;; [PHY][WA] Disable Periodic PHY IO Re-calibration
        //D.S ASD:0xC490910C %LE %Long 0x00000000
        //D.S ASD:0xC4D0910C %LE %Long 0x00000000
        //
        //;; Wait 10~20ms
        //
        //;; [CTRL] Disable Periodic DRAM ZQ Re-calibration
        //D.S ASD:0xC490300C %LE %Long 0x0502F100
        //D.S ASD:0xC4D0300C %LE %Long 0x0502F100
        //
        //;; [PHY] No Wait Setting when PLL-ON @ Self-refresh
        //D.S ASD:0xC490F010 %LE %Long 0x17D00101
        //D.S ASD:0xC4D0F010 %LE %Long 0x17D00101
        //
        //;; [CTRL] PLL-ON @ Self-refresh
        //D.S ASD:0xC49030C0 %LE %Long 0x00004030
        //D.S ASD:0xC4D030C0 %LE %Long 0x00004030
        //
        //;; [CTRL] ALP Enable
        //D.S ASD:0xC4900020 %LE %Long 0x000003F3
        //D.S ASD:0xC4D00020 %LE %Long 0x000003F3
        case LX_CHIP_O26:
        {
            OS_WrReg(0xC490910C, 0x00000000);
            OS_WrReg(0xC4D0910C, 0x00000000);

            usleep_range(10000, 20000);

            OS_WrReg(0xC490300C, 0x0502F100);
            OS_WrReg(0xC4D0300C, 0x0502F100);

            OS_WrReg(0xC490F010, 0x17D00101);
            OS_WrReg(0xC4D0F010, 0x17D00101);

            OS_WrReg(0xC49030C0, 0x00004030);
            OS_WrReg(0xC4D030C0, 0x00004030);

            OS_WrReg(0xC4900020, 0x000003F3);
            OS_WrReg(0xC4D00020, 0x000003F3);

            usleep_range(10000, 20000);

            ret = RET_OK;
        }
        break;
#endif

        default:
        {
            // not supported feature.
            ret = RET_OK;
        }
    }

    SYS_NOTI("DDR_ALP ON - completed\n");

    return ret;
}

static int sys_alp_ctrl_disable_ddr_alp_mode(void)
{
    int ret = RET_ERROR;

    if (!ddr_alp_mode)
    {
        SYS_NOTI("DDR_ALP not supported\n");
        return RET_OK;
    }

    SYS_NOTI("DDR_ALP OFF - begin\n");

    switch (lx_chip())
    {
#ifdef INCLUDE_O22_CHIP_KDRV

        case LX_CHIP_O22:
        {
            OS_WrReg(0xC67C8050, 0x00002c78);
            OS_WrReg(0xF3008050, 0x00002c78);
            OS_WrReg(0xC67C300C, 0x0502f100);
            OS_WrReg(0xF300300C, 0x0502f100);
            OS_WrReg(0xC67C0100, 0x00000000);
            OS_WrReg(0xF3000100, 0x00000000);

            usleep_range(10000, 20000); // 10~20ms

            OS_WrReg(0xC67C820C, 0x80010301);
            OS_WrReg(0xF300820C, 0x80010301);

            ret = RET_OK;
        }
        break;
#endif

#ifdef INCLUDE_O24_CHIP_KDRV

        // see http://clm.lge.com/issue/browse/SICDTV-12972
        case LX_CHIP_O24:
        {
            // ;; APB lockup cnt disable
            OS_WrReg(0xC4C0201C, 0x00000000);
            OS_WrReg(0xC400601C, 0x00000000);

            // [CTRL] Enable Periodic DRAM ZQ Re-calibration
            OS_WrReg(0xC4D0300C, 0x0506F100);
            OS_WrReg(0xC490300C, 0x0506F100);

            // [CTRL] ALP Disable
            OS_WrReg(0xC4D00100, 0x00000000);
            OS_WrReg(0xC4900100, 0x00000000);

            // M0 PLL-OFF
            OS_WrReg(0xC4D0F010, 0x17D00110); // Wait Setting in PHY when PLL-OFF @ Self-refresh
            OS_WrReg(0xC4D030C0, 0x00008033); // PLL-OFF @ Self-refresh

            // M1 PLL-OFF
            OS_WrReg(0xC490F010, 0x17D00110); // Wait Setting in PHY when PLL-OFF @ Self-refresh
            OS_WrReg(0xC49030C0, 0x00008033); // PLL-OFF @ Self-refresh

            // Wait 10~20ms
            usleep_range(10000, 20000);

            // [PHY][WA] Enable Periodic PHY IO Re-calibration
            OS_WrReg(0xC4D0820C, 0x80010301);
            OS_WrReg(0xC490820C, 0x80010301);

            // ;; APB lockup cnt enable
            OS_WrReg(0xC4C0201C, 0x00000001);
            OS_WrReg(0xC400601C, 0x00000001);

            ret = RET_OK;
        }
        break;
#endif

#ifdef INCLUDE_M23_CHIP_KDRV

        case LX_CHIP_M23:
        {
            //;; [CTRL] Enable Periodic DRAM ZQ Re-calibration
            OS_WrReg(0xC4F4300C, 0x0506F100);

            //;; [CTRL] ALP Disable
            OS_WrReg(0xC4F40100, 0x00000000);

            //;; Wait 10~20ms
            usleep_range(10000, 20000);

            //;; [PHY][WA] Enable Periodic PHY IO Re-calibration
            OS_WrReg(0xC4F4820C, 0x80010301);

            //;;PLL-OFF
            OS_WrReg(0xC4F4F010, 0x17D00110); // ;; Wait Setting in PHY when PLL-OFF @ Self-refresh
            OS_WrReg(0xC4F430C0, 0x00008033); // ;; PLL-OFF @ Self-refresh

            ret = RET_OK;
        }
        break;
#endif

#ifdef INCLUDE_O26_CHIP_KDRV

        //;; [CTRL] Enable Periodic DRAM ZQ Re-calibration
        //D.S ASD:0xC490300C %LE %Long 0x0506F100
        //D.S ASD:0xC4D0300C %LE %Long 0x0506F100
        //
        //;; [CTRL] ALP Disable
        //D.S ASD:0xC4900020 %LE %Long 0x00000000
        //D.S ASD:0xC4D00020 %LE %Long 0x00000000
        //
        //;; [PHY] Wait Setting when PLL-OFF @ Self-refresh
        //D.S ASD:0xC490F010 %LE %Long 0x00C80101
        //D.S ASD:0xC4D0F010 %LE %Long 0x00C80101
        //
        //;; [CTRL] PLL-OFF @ Self-refresh
        //D.S ASD:0xC49030C0 %LE %Long 0x00008033
        //D.S ASD:0xC4D030C0 %LE %Long 0x00008033
        //
        //;; Wait 10~20ms
        //
        //;; [PHY][WA] Enable Periodic PHY IO Re-calibration
        //D.S ASD:0xC490910C %LE %Long 0x00001000
        //D.S ASD:0xC4D0910C %LE %Long 0x00001000
        case LX_CHIP_O26:
        {
            OS_WrReg(0xC490300C, 0x0506F100);
            OS_WrReg(0xC4D0300C, 0x0506F100);

            OS_WrReg(0xC4900020, 0x00000000);
            OS_WrReg(0xC4D00020, 0x00000000);

            OS_WrReg(0xC490F010, 0x00C80101);
            OS_WrReg(0xC4D0F010, 0x00C80101);

            OS_WrReg(0xC49030C0, 0x00008033);
            OS_WrReg(0xC4D030C0, 0x00008033);

            usleep_range(10000, 20000);

            OS_WrReg(0xC490910C, 0x00001000);
            OS_WrReg(0xC4D0910C, 0x00001000);

            usleep_range(10000, 20000);

            ret = RET_OK;
        }
        break;
#endif

        default:
        {
            // not supported feature.
            ret = RET_OK;
        }
    }

    SYS_NOTI("DDR_ALP OFF - completed\n");

    return ret;


}

static int sys_alp_ctrl_enable_cpu_alp_mode(void)
{
    int ret = RET_ERROR;


    switch (lx_chip())
    {
#if defined(INCLUDE_O26_CHIP_KDRV)
        case LX_CHIP_O26:
        {
            if (!cpu_alp_mode)
            {
                SYS_NOTI("CPU ALP not supported\n");
                return RET_OK;
            }

            o26_set_kdrv_pm_runtime_suspend();
            ret = RET_OK;
        }
        break;

#endif
#if defined(INCLUDE_O24_CHIP_KDRV)

        // see http://clm.lge.com/issue/browse/SICDTV-12980
        case LX_CHIP_O24:
        {
            if (!cpu_alp_mode)
            {
                SYS_NOTI("CPU ALP not supported\n");
                return RET_OK;
            }

            o24_set_kdrv_pm_runtime_suspend();
            ret = RET_OK;
        }
        break;
#endif

        default:
        {
            // not supported feature.
            ret = RET_OK;
        }
    }

    return ret;
}


static int sys_alp_ctrl_disable_cpu_alp_mode(void)
{
    int ret = RET_ERROR;

    switch (lx_chip())
    {
#if defined(INCLUDE_O26_CHIP_KDRV)

        case LX_CHIP_O26:
        {
            if (!cpu_alp_mode)
            {
                SYS_NOTI("CPU ALP not supported\n");
                return RET_OK;
            }

            o26_set_kdrv_pm_runtime_resume();
            ret = RET_OK;
        }
        break;
#endif
#if defined(INCLUDE_O24_CHIP_KDRV)

        case LX_CHIP_O24:
        {
            if (!cpu_alp_mode)
            {
                SYS_NOTI("CPU ALP not supported\n");
                return RET_OK;
            }

            o24_set_kdrv_pm_runtime_resume();
            ret = RET_OK;
        }
        break;
#endif

        default:
        {
            // not supported feature.
            ret = RET_OK;
        }
    }

    return ret;


}

#ifdef RUNTIME_PM_BY_PQE_PM
static int SYS_IO_PQE_PM_RuntimeCallback(int action);

static struct pqe_pm_config g_pqe_pm_cfg =
{
    .name = "sys_alp_ctrl",
    .opt = PQE_PM_OPT_MONITOR,
    .order = 0,
    .callback = SYS_IO_PQE_PM_RuntimeCallback,
};

static int g_pqe_pm_id = -1;

static int SYS_IO_PQE_PM_RuntimeCallback(int pqe_pm_action)
{
    if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_PREPARE)
    {
        // make fbdev to be pseudo suspend state
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND)
    {
        // TODO: 필요시 추가할것
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_COMPLETED)
    {
        sys_alp_ctrl_enable_cpu_alp_mode();
        sys_alp_ctrl_enable_ddr_alp_mode();
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_PREPARE)
    {
        sys_alp_ctrl_disable_ddr_alp_mode();
        sys_alp_ctrl_disable_cpu_alp_mode();
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_RESUME)
    {
        // re-initialize fbdev
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_COMPLETED)
    {
        // TODO: 필요시 추가할것
    }
    else
    {
        // not supported action
    }

    return RET_OK;
}

#endif

void sys_alp_ctrl_init(void)
{
    // (2023/11/21)
    // O24 의 경우 PQE clock gating 과 연계하여 동작을 해야 하므로, lg1k-sys 장치 기반의
    // runtime_pm 동작은 하지 않고, pqe_pm 과 연계하여 동작하도록 한다.
    //
    // (note) pqe_pm 에 MONITOR 옵션으로 등록한다. 즉 suspend, resume 동작은 하지 못하나,
    // pqe_pm 의 callback 을 받을 수 있다.
#ifdef RUNTIME_PM_BY_PQE_PM
    g_pqe_pm_id = pqe_pm_register(&g_pqe_pm_cfg);

    if (g_pqe_pm_id < 0)
    {
        SYS_ERROR("pqe_pm register error\n");
        return;
    }

#endif

    // init proc
    {
        struct os_proc* pdir = os_proc_create_dir(lg1k_sys_proc_entry, "alp_ctrl",
                               sys_alp_ctrl_read_proc_handler, sys_alp_ctrl_write_proc_handler);

        os_proc_create_file(pdir, "ddr_alp",  PROC_ID_DDR_ALP, NULL);
        os_proc_create_file(pdir, "cpu_alp", PROC_ID_CPU_ALP, NULL);
    }
}

int sys_alp_ctrl_runtime_suspend(struct device* dev)
{
    int ret;

#ifdef RUNTIME_PM_BY_PQE_PM
    SYS_NOTI("lg1k-sys, pm runtime suspend handler is moved to pqe_pm\n");
    ret = RET_OK;
#else
    int ret0, ret1;
    ret0 = sys_alp_ctrl_enable_cpu_alp_mode();
    ret1 = sys_alp_ctrl_enable_ddr_alp_mode();
    SYS_NOTI("lg1k-sys, pm runtime suspend, cpu_alp=%d, ddr_alp=%d\n", ret0, ret1);

    ret = (ret0 == RET_OK && ret1 == RET_OK) ? RET_OK : RET_ERROR;
#endif
    return ret;
}

int sys_alp_ctrl_runtime_resume(struct device* dev)
{
    int ret;

#ifdef RUNTIME_PM_BY_PQE_PM
    SYS_NOTI("lg1k-sys, pm runtime resume handler is moved to pqe_pm\n");
    ret = RET_OK;
#else
    int ret0, ret1;
    ret0 = sys_alp_ctrl_disable_ddr_alp_mode();
    ret1 = sys_alp_ctrl_disable_cpu_alp_mode();
    SYS_NOTI("lg1k-sys, pm runtime resume, ddr_alp=%d, cpu_alp=%d\n", ret0, ret1);

    ret = (ret0 == RET_OK && ret1 == RET_OK) ? RET_OK : RET_ERROR;
#endif

    return ret;
}

static int sys_alp_ctrl_read_proc_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return sprintf(buffer, "not implemented\n");
}

static int sys_alp_ctrl_write_proc_handler(UINT32 procId, char* buffer, int size, void* data)
{
    switch (procId)
    {
        case PROC_ID_DDR_ALP:
        {
            UINT32 en;
            sscanf(buffer, " %d", &en);

            if (!en)
            {
                sys_alp_ctrl_disable_ddr_alp_mode();
            }
            else
            {
                sys_alp_ctrl_enable_ddr_alp_mode();
            }
        }
        break;

        case PROC_ID_CPU_ALP:
        {
            UINT32 en;
            sscanf(buffer, " %d", &en);

            if (!en)
            {
                sys_alp_ctrl_disable_cpu_alp_mode();
            }
            else
            {
                sys_alp_ctrl_enable_cpu_alp_mode();
            }
        }
        break;
    }

    return strlen(buffer);
}

/** @} */

