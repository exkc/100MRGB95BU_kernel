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
 *  kdriver main
 *
 *  author      daeyoung lim ( raxis.lim@lge.com )
 *  version 1.0
 *  date    2009.11.04
 *
 *  @addtogroup lg1150_base
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
#define CHECK_BOARD_OPTS

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/mm.h>       // si_meminfo()
#include <linux/spinlock.h>

#include "base_drv.h"
#include "logm_drv.h"
#include "base_impl.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
static const struct
{
    char chp_class;
    int  chp_num;
    char chp_series;
    u32 chp_name;
}
lg1k_chip_list[] =
{
    {'L', 9,  ' ', LX_CHIP_L9},
    {'H', 13, ' ', LX_CHIP_H13},
    {'M', 14, ' ', LX_CHIP_M14},
    {'H', 14, ' ', LX_CHIP_H14},
    {'H', 15, ' ', LX_CHIP_H15},
    {'M', 16, ' ', LX_CHIP_M16},
    {'M', 17, ' ', LX_CHIP_M17},
    {'M', 16, 'P', LX_CHIP_M17},
    {'L', 18, 'F', LX_CHIP_L18},
    {'O', 18, ' ', LX_CHIP_O18},
    {'M', 19, ' ', LX_CHIP_M19},
    {'O', 20, ' ', LX_CHIP_O20},
    {'E', 60, ' ', LX_CHIP_E60},
    {'O', 22, ' ', LX_CHIP_O22},
    {'M', 23, ' ', LX_CHIP_M23},
    {'O', 24, ' ', LX_CHIP_O24},
    {'O', 26, ' ', LX_CHIP_O26},
};

struct lg1k_base_config
{
    u32 chip_rev;
    u32 ace_rev;
    //u32 chip_plt;
    //u32 board_opt;
};

enum
{
    PROC_ID_DCHIP,
    PROC_ID_DCHIP_NAME,
    PROC_ID_ACHIP,
    PROC_ID_PLATFORM,
    PROC_ID_BOARD_OPT,
    PROC_ID_GRAPHIC_RES,
    PROC_ID_REG_RD,
    PROC_ID_REG_WR,
    PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void BASE_PLT_Probe(u32* plt, u32* board_opt);   /* platform prober */
extern void BASE_PLT_Init(void);                        /* platform depdendent initializer */

#define lg1k_platform_probe(plt, board_opt) BASE_PLT_Probe(plt, board_opt)
#define lg1k_platform_init()                BASE_PLT_Init()

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void probe_chip(void);
static void open_proc(void);
static int  print_memcfg(struct seq_file* s, void* data);
static int  read_proc_handler(u32 proc_id, char* buffer, int size, void* data);
static int  write_proc_handler(u32 proc_id, char* buffer, int size, void* data);

extern int  print_board_opts(struct seq_file* s, void* data);


int lg1k_kdrv_init(void);
void lg1k_kdrv_cleanup(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static struct lg1k_base_config lg1k_base_cfg;

static int do_drv_cfg = 1;
static int do_drv_init = 1;

module_param(do_drv_cfg, int, 0644); // for debug
module_param(do_drv_init, int, 0644); // for debug

/*----------------------------------------------------------------------------------------
    Implementation Group
----------------------------------------------------------------------------------------*/
int lg1k_kdrv_init(void)
{

    printk("<!> initialzing lg1k kdriver...\n");

    lg1k_os_frwk_init();
    lg1k_memcfg_frwk_init();
    lg1k_proc_frwk_init();

    probe_chip();
    open_proc();

    lg1k_board_frwk_init();

    // 신규 방식에서는 lg1k_board_frwk_init() 에서 이미 필요한 board opt 정보가 모두 수집된다.
    // 기존 코드와의 호환성을 위하여 lg1k_platform_probe() 을 호출하도록 하며, 이 함수에서 만약
    // 공통 코드에서 파악된 값과 틀린 값이 리턴된다면 추가 디버깅이 필요하다.
#ifdef CHECK_BOARD_OPTS
    {
        u32 base_chip_plt;
        u32 base_board_opt;
        u32 plt_chip_plt;
        u32 plt_board_opt;

        base_chip_plt = get_base_chip_plt();
        base_board_opt = get_base_board_opt();

        lg1k_platform_probe(&plt_chip_plt, &plt_board_opt);

        if (base_chip_plt != plt_chip_plt)
        {
            lg1k_logm_warn("check !! chip_plt: base(0x%04x) != plt(0x%04x)\n", base_chip_plt, plt_chip_plt);
        }

        if (base_board_opt != plt_board_opt)
        {
            lg1k_logm_warn("check !! board_opt: base(0x%08x) != plt(0x%08x)\n", base_board_opt, plt_board_opt);
        }

        lg1k_logm_noti("+ CHIP_REV=0x%04X CHIP_PLT=0x%04x BOARD_OPT=0x%08x\n",
                       lg1k_base_cfg.chip_rev, base_chip_plt, base_board_opt);
    }
#endif

    // identify dirver platform & initialize sub dirver
    if (do_drv_cfg) lg1k_kdrv_preinit_driver();

    lg1k_platform_init();

    if (do_drv_init) lg1k_kdrv_init_driver();

    return 0;
}

void lg1k_kdrv_cleanup(void)
{
    printk("<!> cleanup lg1k kdriver...\n");

    // cleanup sub driver
    lg1k_kdrv_cleanup_driver();

    lg1k_board_frwk_cleanup();

    lg1k_proc_frwk_cleanup();
    lg1k_memcfg_frwk_cleanup();
    lg1k_os_frwk_cleanup();
}


static u32 find_chip(char chp_class, int chp_num, char chp_series)
{
    int i;

    const int num_list = sizeof(lg1k_chip_list) / sizeof(lg1k_chip_list[0]);

    for (i = 0; i < num_list; i++)
    {
        if (lg1k_chip_list[i].chp_class == chp_class
                && lg1k_chip_list[i].chp_num == chp_num
                && lg1k_chip_list[i].chp_series == chp_series)
            return lg1k_chip_list[i].chp_name;
    }

    return LX_CHIP_UNKNOWN;
}

/**
 *
 *
 */
static void probe_chip(void)
{
    char* cmd_buf;
    int cmd_buf_sz = 1024;

    char* tok, *sav_tok;
    char delim[] = " \t\n";

    cmd_buf = kmalloc(cmd_buf_sz, GFP_KERNEL);

    if (!cmd_buf)
        goto func_exit;

#ifdef MODULE           // saved_command_line will be exported by kernel..but not yet
    {
        OS_FILE_T file;

        if (RET_OK != os_file_open(&file, "/proc/cmdline", O_RDONLY | O_LARGEFILE, 0666))
        {
            lg1k_logm_error("can't open /proc/cmdline\n");
            goto func_exit;
        }

        memset(cmd_buf, 0, cmd_buf_sz);

        if (0 >= os_file_read(&file, cmd_buf, cmd_buf_sz - 1))
        {
            os_file_close(&file);
            printk("<error> can't read /proc/cmdline\n");
            goto func_exit;
        }

        os_file_close(&file);
    }
#else
    {
        extern char* saved_command_line;
        snprintf(cmd_buf, cmd_buf_sz - 1, "%s", saved_command_line);
    }
#endif

    /* initialize data */
    lg1k_base_cfg.chip_rev = 0x0;
    lg1k_base_cfg.ace_rev = 0x0;

    {
#define TOKEN_DCHIP     0x1
#define TOKEN_ACHIP     0x2
#define TOKEN_PLATFORM  0x4
        UINT8 status = TOKEN_DCHIP | TOKEN_ACHIP;   //TOKEN_PLATFORM
        UINT8 chip_model;
        u32 chip_rev;

        char chp_class, rev_class, rev_series = ' ';
        int chp_num, rev_num;

        tok = simple_strtok(cmd_buf, delim, &sav_tok);

        while (tok)
        {
            chip_model = 0x0;
            chip_rev = 0x0;

            if (status & TOKEN_DCHIP)
            {
                if ((4 == sscanf(tok, "chip=%c%d%c%d", &chp_class, &chp_num, &rev_class, &rev_num)) ||
                        (5 == sscanf(tok, "chip=%c%d%c%c%d", &chp_class, &chp_num, &rev_series, &rev_class, &rev_num)))
                {
                    chip_model = find_chip(chp_class, chp_num, rev_series);
                    chip_rev = (((rev_class - 'A') + 0xA) << 4) + rev_num;

                    lg1k_base_cfg.chip_rev = MAKE_CHIP_REV(chip_model, chip_rev);
                    status &= ~TOKEN_DCHIP;
                }
            }

            rev_series = ' ';

            /* find ace = L,9,A,0 or H,13,A,0 .. */
            if ((status & TOKEN_ACHIP) &&
                    sscanf(tok, "ace=%c%d%c%d", &chp_class, &chp_num, &rev_class, &rev_num) == 4)
            {
                chip_model = find_chip(chp_class, chp_num, rev_series);
                chip_rev = (((rev_class - 'A') + 0xA) << 4) + rev_num;

                lg1k_base_cfg.ace_rev = MAKE_CHIP_REV(chip_model, chip_rev);
            }

            /* all tokens done, break loop !! */
            if (!status)
                break;

            tok = simple_strtok(NULL, delim, &sav_tok);
        }
    }
func_exit:

    if (cmd_buf)
        kfree(cmd_buf);

    /* check if all parameters are parsed successfully.
     * when valid token is not found, use the some default value.
     * espacially, the default value of ace_rev is the same value as chip_rev
     */
    if (lg1k_base_cfg.chip_rev == 0x0)
        lg1k_base_cfg.chip_rev = LX_CHIP_UNKNOWN;

    if (lg1k_base_cfg.ace_rev == 0x0)
        lg1k_base_cfg.ace_rev = lg1k_base_cfg.chip_rev;

#ifdef CONFIG_LX_CHIP_EMUL
#if CONFIG_LX_CHIP_EMUL
    lg1k_base_cfg.chip_rev = CONFIG_LX_CHIP_EMUL;
    lg1k_base_cfg.ace_rev = CONFIG_LX_CHIP_EMUL;
#endif
#endif

}

u32 lx_chip(void)
{
    return (lg1k_base_cfg.chip_rev >> 8) & 0xff;
}
EXPORT_SYMBOL(lx_chip);

u32 lx_chip_rev(void)
{
    return lg1k_base_cfg.chip_rev;
}
EXPORT_SYMBOL(lx_chip_rev);

u32 lx_ace(void)
{
    return (lg1k_base_cfg.ace_rev >> 8) & 0xff;
}
EXPORT_SYMBOL(lx_ace);

u32 lx_ace_rev(void)
{
    return lg1k_base_cfg.ace_rev;
}
EXPORT_SYMBOL(lx_ace_rev);

u32 lx_chip_plt(void)
{
    return get_base_chip_plt();
}
EXPORT_SYMBOL(lx_chip_plt);

u32 lx_board_opt(void)
{
    return get_base_board_opt();
}
EXPORT_SYMBOL(lx_board_opt);

u32 lx_chip_graphic_res(void)
{
#if defined(CONFIG_LX_GRAPHIC_RES) && (CONFIG_LX_GRAPHIC_RES>0)
    return CONFIG_LX_GRAPHIC_RES;
#else
    return 0x0;
#endif
}

/*========================================================================================
    BASE PROC SYSTEM
========================================================================================*/
static void open_proc(void)
{
    struct os_proc* pdir = os_proc_create_dir(NULL, "base", read_proc_handler, write_proc_handler);

    os_proc_create_file(pdir, "chip_rev",   PROC_ID_DCHIP, NULL);
    os_proc_create_file(pdir, "chip_name",  PROC_ID_DCHIP_NAME, NULL);
    os_proc_create_file(pdir, "ace_rev",    PROC_ID_DCHIP_NAME, NULL);
    os_proc_create_file(pdir, "platform",   PROC_ID_PLATFORM, NULL);
    os_proc_create_file(pdir, "board_opt",  PROC_ID_BOARD_OPT, NULL);
    os_proc_create_file(pdir, "graphic_res", PROC_ID_GRAPHIC_RES, NULL);
    os_proc_create_file(pdir, "reg_rd",     PROC_ID_REG_RD, NULL);
    os_proc_create_file(pdir, "reg_wr",     PROC_ID_REG_WR, NULL);

    os_proc_create_seq_file(pdir, "memcfg", print_memcfg, NULL, (void*)true);
    os_proc_create_seq_file(pdir, "status", print_memcfg, NULL, (void*)false);
    os_proc_create_seq_file(pdir, "board_info", print_board_opts, NULL, (void*)false);
}

static int print_memcfg(struct seq_file* s, void* data)
{
    bool detail = (bool)data;

    os_memcfg_dump(s, detail);
    BASE_DEVMEM_DumpMemCfg(s, detail);

    return 0;
}

static int read_proc_handler(u32 proc_id, char* buffer, int size, void* data)
{
    int len = 0;

    switch (proc_id)
    {
        case PROC_ID_DCHIP:
        {
            len += snprintf(buffer, size, "0x%x\n", lx_chip_rev());
        }
        break;

        case PROC_ID_DCHIP_NAME:
        {
            len += snprintf(buffer, size, "%s\n", CHIP_NAME);
        }
        break;

        case PROC_ID_ACHIP:
        {
            len += snprintf(buffer, size, "0x%x\n", lx_ace_rev());
        }
        break;

        case PROC_ID_PLATFORM:
        {
            len += snprintf(buffer, size, "0x%x\n", lx_chip_plt());
        }
        break;

        case PROC_ID_BOARD_OPT:
        {
            len += snprintf(buffer, size, "0x%x\n", lx_board_opt());
        }
        break;

        case PROC_ID_GRAPHIC_RES:
        {
            len += snprintf(buffer, size, "0x%x\n", lx_chip_graphic_res());
        }
        break;

        case PROC_ID_REG_RD:
        {
            len += snprintf(buffer, size, "<usage> echo #addr > /proc/lg/base/reg_rd\n");
        }
        break;

        case PROC_ID_REG_WR:
        {
            len += snprintf(buffer, size, "<usage> echo #addr #val > /proc/lg/base/reg_wr\n");
        }
        break;

        default:
        {
            len = snprintf(buffer, size, "%s(%d)\n", "proc(%d) not supported\n", proc_id);
        }
    }

    return len;
}

static int write_proc_handler(u32 proc_id, char* buffer, int size, void* data)
{
    switch (proc_id)
    {
        case PROC_ID_REG_RD:
        {
            u32 addr, val;
            sscanf(buffer, " %x", &addr);
            os_rd_reg(addr, &val);
            printk("\nAddr 0x%x = 0x%08x\n", addr, val);
        }
        break;

        case PROC_ID_REG_WR:
        {
            u32 addr, val;

            sscanf(buffer, " %x %x", &addr, &val);
            os_wr_reg(addr, val);
            os_rd_reg(addr, &val);
            printk("\nAddr 0x%x = 0x%08x\n", addr, val);
        }
        break;

        default:
        {
            /* do nothing */
        }
        break;
    }

    return strlen(buffer);
}

/*========================================================================================
    ETC
========================================================================================*/
DEFINE_SPINLOCK(g_Base_AVLipsync_Lock);
EXPORT_SYMBOL(g_Base_AVLipsync_Lock);

/////////////////////////////////////////////////////////////////////////////////////////
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", lg1k_kdrv_init);
#else
module_init(lg1k_kdrv_init);
#endif
module_exit(lg1k_kdrv_cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("BASE driver");
MODULE_LICENSE("GPL");

/** @} */
