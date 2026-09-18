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

#include "bwm_impl.h"
#include "proc_util.h"
#include "sys_log.h"

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
    PROC_ID_TEST_CMD = 0,
    PROC_ID_MAX
};

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
extern struct os_proc* lg1k_sys_proc_entry;

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void do_dummy_init(void);
static void do_dummy_config(struct bwm_ctx* ctx);
static void do_dummy_proc(struct bwm_ctx* ctx, char* command, struct seq_file* m);

static void sys_bwm_init_proc(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static struct bwm_ctx  g_bwm_ctx =
{
    .status = { .configured = false },
    .pqe = { .input_src = "none", .input_win = { 0, 0 }, .input_rate = 0, .hdr_type = "sdr" },
};

/*========================================================================================
    Implementation Group
========================================================================================*/
void sys_bwm_init(void)
{
    memset(&g_bwm_ctx, 0x0, sizeof(struct bwm_ctx));
    strncpy(g_bwm_ctx.pqe.hdr_type, "none", 4);
    strncpy(g_bwm_ctx.demod.tune, "none", 4);

    if (0)
    {

    }

#ifdef INCLUDE_O26_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O26)
    {
        struct bwm_chip_drv bwm_o26_chip_config(void);
        g_bwm_ctx.chip_drv = bwm_o26_chip_config();
    }

#endif
#ifdef INCLUDE_O24_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O24)
    {
        struct bwm_chip_drv bwm_o24_chip_config(void);
        g_bwm_ctx.chip_drv = bwm_o24_chip_config();
    }

#endif
#ifdef INCLUDE_O22_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O22)
    {
        extern struct bwm_chip_drv bwm_o22_chip_config(void);
        g_bwm_ctx.chip_drv = bwm_o22_chip_config();
    }

#endif
    else
    {
        SYS_NOTI("sys_bwm not supported\n");
        g_bwm_ctx.chip_drv.do_init = do_dummy_init;
        g_bwm_ctx.chip_drv.do_config = do_dummy_config;
        g_bwm_ctx.chip_drv.do_proc = do_dummy_proc;
    }

    g_bwm_ctx.chip_drv.do_init();

    sys_bwm_init_proc();

    SYS_NOTI("[bwm] manager initialized\n");

#if 0
    //TEST
    sys_bwm_noti(BWM_OPT_DEFAULT, "pqe.input=none");

    sys_bwm_noti(BWM_OPT_DEFAULT, "pqe.input=hdmi,%dx%d@%d", 3840, 2160, 60);

    sys_bwm_noti(BWM_OPT_DEFAULT, "pqe.input=hdmi:%dx%d@%d", 7680, 4320, 60);

    sys_bwm_noti(BWM_OPT_DEFAULT, "pqe.input=hdmi,%dx%d@%d", 3840, 2160, 60);
    sys_bwm_noti(BWM_OPT_DEFAULT, "pqe.hdr=%s", "dolby");

    sys_bwm_noti(BWM_OPT_DEFAULT, "pqe.input=hdmi:%dx%d@%d", 7680, 4320, 60);

    sys_bwm_noti(BWM_OPT_DEFAULT, "pqe.input=none");
#endif
}

// power state 변경에 따라 필요한 작업을 진행한다.
void sys_bwm_pm_function(struct device* dev, char* command)
{
    bool restore_hw = false;

    if (!strncmp(command, "resume", 6) || !strncmp(command, "restore", 7))
    {
        restore_hw = true;
    }

    // 초기값으로 강제 설정토록 함
    if (restore_hw)
    {
        printk("[bwm] init hw with default config\n");
        g_bwm_ctx.chip_drv.do_init();
    }

    // add something
}

static void sys_bwm_parse_pqe_input(char* cmd_buf)
{
    char* tok, *sav_tok;
    char delim[] = ":,\t\n";

    SYS_DEBUG("[bwm] pqe.input params=%s\n", cmd_buf);

    tok = simple_strtok(cmd_buf, delim, &sav_tok);

    if (!tok)
    {
        SYS_ERROR("valid param not found. cmd_buf:%s\n", cmd_buf);
        return;
    }

    //  SYS_NOTI("[bwm] pqe.input param0:%s\n", tok);

    strncpy(g_bwm_ctx.pqe.input_src, tok, BWM_TEXT_MAX);
    g_bwm_ctx.pqe.input_win.w = 0;
    g_bwm_ctx.pqe.input_win.h = 0;
    g_bwm_ctx.pqe.input_rate = 0;

    tok = simple_strtok(NULL, delim, &sav_tok);

    if (tok)
    {
        int width, height, rate;

        //      SYS_NOTI("[bwm] pqe.input param1:%s\n", tok);

        if (3 != sscanf(tok, "%dx%d@%d", &width, &height, &rate))
        {
            SYS_ERROR("invalid param: %s\n", tok);
        }

        g_bwm_ctx.pqe.input_win.w = width;
        g_bwm_ctx.pqe.input_win.h = height;
        g_bwm_ctx.pqe.input_rate = rate;
    }

    SYS_DEBUG("[bwm] pqe.input src=%s, size=%dx%d, rate=%dhz\n",
              g_bwm_ctx.pqe.input_src,
              g_bwm_ctx.pqe.input_win.w,
              g_bwm_ctx.pqe.input_win.h,
              g_bwm_ctx.pqe.input_rate);
}

static void sys_bwm_parse_pqe_hdr(char* cmd_buf)
{
    char* tok, *sav_tok;
    char delim[] = ":,\t\n";

    SYS_DEBUG("[bwm] pqe.hdr params=%s\n", cmd_buf);

    tok = simple_strtok(cmd_buf, delim, &sav_tok);

    if (!tok)
    {
        SYS_ERROR("valid param not found. cmd_buf:%s\n", cmd_buf);
        return;
    }

    strncpy(g_bwm_ctx.pqe.hdr_type, tok, BWM_TEXT_MAX);

    SYS_DEBUG("[bwm] pqe.hdr type=%s\n", g_bwm_ctx.pqe.hdr_type);
}

static void sys_bwm_parse_demod_tune(char* cmd_buf)
{
    strncpy(g_bwm_ctx.demod.tune, cmd_buf, BWM_TEXT_MAX);

    SYS_DEBUG("[bwm] demod.tune=%s\n", cmd_buf);
}

// 정해진 syntax 에 따라 전달되는 정보를 파싱하여 ctx 에 저장한다.
void sys_bwm_noti(enum sys_bwm_opt opt, const char* fmt, ...)
{
    va_list args;
    char cmd_buf[256];

    char* tok, *sav_tok;
    char delim[] = "= \t\n";

    // 파싱한다.
    va_start(args, fmt);
    vsnprintf(cmd_buf, sizeof(cmd_buf), fmt, args);
    va_end(args);

    SYS_DEBUG("[bwm] cmd_buf=%s\n", cmd_buf);

    tok = simple_strtok(cmd_buf, delim, &sav_tok);

    while (tok)
    {
        if (!strncasecmp(tok, "pqe.input", strlen("pqe.input")))
        {
            tok = simple_strtok(NULL, delim, &sav_tok);

            if (tok)
            {
                sys_bwm_parse_pqe_input(tok);
            }

            break;
        }

        if (!strncasecmp(tok, "pqe.hdr", strlen("pqe.hdr")))
        {
            tok = simple_strtok(NULL, delim, &sav_tok);

            if (tok)
            {
                sys_bwm_parse_pqe_hdr(tok);
            }

            break;
        }

        if (!strncasecmp(tok, "demod.tune", strlen("demod.tune")))
        {
            tok = simple_strtok(NULL, delim, &sav_tok);

            if (tok)
            {
                sys_bwm_parse_demod_tune(tok);
            }

            break;
        }

        // parse others..
        //if (!strncasecmp(tok, "vdec.xxx", strlen("vdec.xxx")))
        // {}

        tok = simple_strtok(NULL, delim, &sav_tok);
    }

    // HW 설정을 바꿀 수 있도록 한다.
    g_bwm_ctx.chip_drv.do_config(&g_bwm_ctx);
}

static void do_dummy_init(void)
{
    SYS_DEBUG("[bwm] dummy do_init\n");
}

static void do_dummy_config(struct bwm_ctx* ctx)
{
    PARAM_UNUSED(ctx);
    SYS_DEBUG("[bwm] dummy do_config\n");
}

static void do_dummy_proc(struct bwm_ctx* ctx, char* command, struct seq_file* m)
{
    PARAM_UNUSED(ctx);
    PARAM_UNUSED(command);
    PARAM_UNUSED(m);
}

/*========================================================================================
    Implementation Group
========================================================================================*/
static int sys_bwm_proc_reader_func(UINT32 procId, char* buffer);
static int sys_bwm_proc_writer_func(UINT32 procId, char* command);

static int sys_bwm_read_proc_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return sys_bwm_proc_reader_func(procId, buffer);
}

static int sys_bwm_write_proc_handler(UINT32 procId, char* buffer, int size, void* data)
{
    return sys_bwm_proc_writer_func(procId, buffer);
}

static int sys_bwm_proc_print_status(struct seq_file* m, void* data)
{
    //  struct sys_bwm_dev* my_dev = (struct sys_bwm_dev*)m->private;
    //  struct sys_bwm_dev* my_dev = (struct sys_bwm_dev*)data;

    seq_printf(m, "pqe.input_src: %s\n", g_bwm_ctx.pqe.input_src);
    seq_printf(m, "pqe.input_win: %dx%d\n", g_bwm_ctx.pqe.input_win.w, g_bwm_ctx.pqe.input_win.h);
    seq_printf(m, "pqe.input_rate: %d\n", g_bwm_ctx.pqe.input_rate);
    seq_printf(m, "pqe.hdr_type: %s\n", g_bwm_ctx.pqe.hdr_type);

    seq_printf(m, "demod.tune: %s\n", g_bwm_ctx.demod.tune);

    if (g_bwm_ctx.chip_drv.do_proc)
    {
        g_bwm_ctx.chip_drv.do_proc(&g_bwm_ctx, "status", m);
    }

    return 0;
}

static int sys_bwm_proc_reader_func(UINT32 procId, char* buffer)
{
    return 0;
}

static int sys_bwm_proc_writer_func(UINT32 procId, char* command)
{
    switch (procId)
    {
        case PROC_ID_TEST_CMD:
        {
            sys_bwm_noti(BWM_OPT_DEFAULT, command);
        }
        break;
    }

    return strlen(command);
}

static void sys_bwm_init_proc(void)
{
    struct os_proc* pdir = os_proc_create_dir(lg1k_sys_proc_entry, "bwm", sys_bwm_read_proc_handler,
                           sys_bwm_write_proc_handler);

    os_proc_create_file(pdir, "testcmd",  PROC_ID_TEST_CMD, NULL);
    os_proc_create_seq_file(pdir, "status", sys_bwm_proc_print_status, NULL, NULL);
}

/** @} */

