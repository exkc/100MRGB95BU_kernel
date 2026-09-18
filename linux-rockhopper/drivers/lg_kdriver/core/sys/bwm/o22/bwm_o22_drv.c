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
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/version.h>

#include "bwm/bwm_impl.h"
#include "sys_log.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define CPU 0
#define GPU 1
#define GFX 2
#define LNE 3

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define perf_level_str(val) ((val==bwm_perf_level_high)? "high": \
                            (val==bwm_perf_level_mid)?   "mid": \
                            (val==bwm_perf_level_low1)?  "low1":"low2")

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
enum bwm_perf_level
{
    bwm_perf_level_high = 0,
    bwm_perf_level_mid,
    bwm_perf_level_low,
    bwm_perf_level_low1 = bwm_perf_level_low,
    bwm_perf_level_low2,

    bwm_perf_level_max_num,
};

struct master_config
{
    int master;
    void* vaddr;

    unsigned int reg;
    unsigned int value[bwm_perf_level_max_num];

    char* desc;
};

// 실제 레지스터 값에 대한 해석은 아래 JIRA 를 활용할것
// http://clm.lge.com/issue/browse/SICDTV-10274
// http://clm.lge.com/issue/browse/SICDTV-10281
//
static struct master_config o22_master_config[] =
{
    //                        HIGH        MID         LOW1        LOW2

    // CPU_M0 1.5us
    // RD: 3GB/800MB/800MB/800MB
    // WR: 3GB/800MB/800MB/800MB
    //
    // CPU_M1 1.5us
    // RD: 3GB/800MB/800MB/800MB
    // WR: 3GB/800MB/800MB/800MB
    { CPU, NULL, 0xCAA01804, {0x0000031F, 0x0000031F, 0x0000031F, 0x0000031F}, "cpu_m0.tm"},
    { CPU, NULL, 0xCAA0183C, {0x10001194, 0x100004B0, 0x100004B0, 0x100004B0}, "cpu_m0.rd"},
    { CPU, NULL, 0xCAA01840, {0x10001194, 0x100004B0, 0x100004B0, 0x100004B0}, "cpu_m0.wr"},
    { CPU, NULL, 0xCAA01A04, {0x0000031F, 0x0000031F, 0x0000031F, 0x0000031F}, "cpu_m1.tm"},
    { CPU, NULL, 0xCAA01A3C, {0x10001194, 0x100004B0, 0x100004B0, 0x100004B0}, "cpu_m1.rd"},
    { CPU, NULL, 0xCAA01A40, {0x10001194, 0x100004B0, 0x100004B0, 0x100004B0}, "cpu_m1.wr"},

    // GPU 5us
    // RD: 2BB/2GB/800MB/300MB
    // WR: 2GB/2GB/800MB/300MB
    { GPU, NULL, 0xC6001018, {0x000007D0, 0x000007D0, 0x000007D0, 0x000007D0}, "gpu.tm"},
    { GPU, NULL, 0xC6001078, {0x30002710, 0x30002710, 0x30000FA0, 0x300005DC}, "gpu.rd"},
    { GPU, NULL, 0xC600107C, {0x30002710, 0x30002710, 0x30000FA0, 0x300005DC}, "gpu.wr"},

    // GFX 8us
    // RD 1.5GB/1.5GB/1.5GB/1.5GB
    // WR 1.5GB/1.5GB/1.5GB/1.5GB
    { GFX, NULL, 0xC6001218, {0x00000C80, 0x00000C80, 0x00000C80, 0x00000C80}, "gfx.tm"},
    { GFX, NULL, 0xC6001278, {0x30002EE0, 0x30002EE0, 0x30002EE0, 0x30002EE0}, "gfx.rd"},
    { GFX, NULL, 0xC600127C, {0x30002EE0, 0x30002EE0, 0x30002EE0, 0x30002EE0}, "gfx.wr"},

    // LNE ? us
    // RD: NA/NA/450MB/450MB
    // WR: NA/NA/200MB/200MB
    { LNE, NULL, 0xC6001E18, {0x000007D0, 0x000007D0, 0x000007D0, 0x000007D0}, "lne.tm"},
    { LNE, NULL, 0xC6001E78, {0x30002710, 0x30002710, 0x300008CA, 0x300008CA}, "lne.rd"},
    { LNE, NULL, 0xC6001E7C, {0x30002710, 0x30002710, 0x300003E8, 0x300003E8}, "lne.wr"},
};

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
struct bwm_chip_drv bwm_o22_chip_config(void);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void bwm_o22_do_init(void);
static void bwm_o22_do_config(struct bwm_ctx* ctx);
static void bwm_o22_do_proc(struct bwm_ctx* ctx, char* command, struct seq_file* m);
static void bwm_o22_write_regs(int master, enum bwm_perf_level level);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static enum bwm_perf_level g_perf_level = bwm_perf_level_high;

/*========================================================================================
    Implementation Group
========================================================================================*/
static void bwm_o22_write_regs(int master, enum bwm_perf_level level)
{
    int i;
    unsigned int reg;
    unsigned int val;
    int cnt = NELEMENTS(o22_master_config);

    SYS_NOTI("[bwm] master(%d) perf_level=%s(%d)\n",
             master, perf_level_str(level), level);

    for (i = 0; i < cnt; i++)
    {
        if (o22_master_config[i].master == master)
        {
            reg = o22_master_config[i].reg;
            val = o22_master_config[i].value[level];

            SYS_DEBUG("master(%d), level=%d, reg=0x%08X, val=0x%08X\n",
                      master, level, reg, val);

            OS_WrReg(reg, val);
        }
    }
}

struct bwm_chip_drv bwm_o22_chip_config(void)
{
    struct bwm_chip_drv chip_drv;

    chip_drv.do_init = bwm_o22_do_init;
    chip_drv.do_config = bwm_o22_do_config;
    chip_drv.do_proc = bwm_o22_do_proc;

    return chip_drv;
}

// O22 기본 설정을 진행한다.
static void bwm_o22_do_init(void)
{
    SYS_NOTI("[bwm] set o22 hw default\n");

    bwm_o22_write_regs(CPU, bwm_perf_level_high);
    bwm_o22_write_regs(GPU, bwm_perf_level_high);
    bwm_o22_write_regs(GFX, bwm_perf_level_high);
    bwm_o22_write_regs(LNE, bwm_perf_level_high);

    g_perf_level = bwm_perf_level_high;
}

// 업데이트된 설정에 따라 설정을 업데이트한다.
static void bwm_o22_do_config(struct bwm_ctx* ctx)
{
    enum bwm_perf_level level = bwm_perf_level_high;

    SYS_DEBUG("[bwm] o22 do_config\n");

    // see http://clm.lge.com/issue/browse/SICDTV-10281
    // see http://hlm.lge.com/qi/browse/RITTEST-1121, http://hlm.lge.com/issue/browse/TVPM-29250
    if (strncmp(ctx->pqe.input_src, "hdmi444", strlen("hdmi444")) &&
	    !strncmp(ctx->pqe.input_src, "hdmi", strlen("hdmi")) &&
            !strncmp(ctx->pqe.hdr_type, "dolby", strlen("dolby")))
    {
        level = bwm_perf_level_mid;
    }

    // see http://clm.lge.com/issue/browse/SDOSTC-1376
    // http://clm.lge.com/issue/browse/SDOSTC-1376?focusedCommentId=3820508&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-3820508
    if (!strncmp(ctx->pqe.input_src, "hdmi", strlen("hdmi")) &&
            ctx->pqe.input_win.w > 3840 &&
            ctx->pqe.input_win.h > 2160)
    {
        level = bwm_perf_level_low1;
    }

    // see http://hlm.lge.com/qi/browse/DITTEST-2057
    if (!strncmp(ctx->pqe.input_src, "hdmi444", strlen("hdmi444")) &&
            ctx->pqe.input_win.w >= 3840 &&
            ctx->pqe.input_win.h >= 2160 &&
            ctx->pqe.input_rate >= 90)
    {
        level = bwm_perf_level_low2;
    }

    if (g_perf_level != level)
    {
        SYS_NOTI("[bwm] bw level change. old=%s(%d), new=%s(%d)\n",
                 perf_level_str(g_perf_level), g_perf_level,
                 perf_level_str(level), level);

        bwm_o22_write_regs(CPU, level);
        bwm_o22_write_regs(GPU, level);
        bwm_o22_write_regs(GFX, level);
        bwm_o22_write_regs(LNE, level);

        g_perf_level = level;

        SYS_NOTI("[bwm] bw level change done\n");
    }
}

// O22 칩 상태를 출력한다. 등등
static void bwm_o22_do_proc(struct bwm_ctx* ctx, char* command, struct seq_file* m)
{
    int i;
    int master;
    unsigned int reg;
    unsigned int val;
    char* desc;
    int cnt = NELEMENTS(o22_master_config);

    if (!strncmp(command, "status", strlen("status")))
    {
        seq_printf(m, "+ hw_bw_level: %s(%d)\n",
                   perf_level_str(g_perf_level), g_perf_level);

        seq_printf(m, "+ reg dump\n");

        for (i = 0; i < cnt; i++)
        {
            master = o22_master_config[i].master;
            reg = o22_master_config[i].reg;
            desc = o22_master_config[i].desc;

            OS_RdReg(reg, &val);

            seq_printf(m, "%16s 0x%08X: 0x%08X\n", desc, reg, val);
        }
    }

    // add something
}

