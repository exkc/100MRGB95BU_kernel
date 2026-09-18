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

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/mm.h>       // si_meminfo()
#include <linux/spinlock.h>

#include "base_drv.h"

#include "logm_drv.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
DEFINE_SPINLOCK(g_Base_AVLipsync_Lock);
EXPORT_SYMBOL(g_Base_AVLipsync_Lock);

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
    /**< digital chip revision information
     *
     * [note] please refer to LX_CHIP_REV macro in base_types.h
     */
    UINT32 chip_rev;

    /**< analog chip revision information
     *
     * [note] please refer to LX_CHIP_REV macro in base_types.h
     */
    UINT32 ace_rev;

    UINT32 chip_plt;

    UINT32 board_opt;
} LX_BASE_DEV_CFG_T;

/*----------------------------------------------------------------------------------------
    Board Basic Configuration
----------------------------------------------------------------------------------------*/
static LX_BASE_DEV_CFG_T g_base_dev_cfg;

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern char* simple_strtok(char* s, const char* delim, char** save_ptr);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/
extern void BASE_DEV_PreInit(void);
extern void BASE_DEV_Init(void);
extern void BASE_DEV_Cleanup(void);

extern void BASE_PLT_Probe(UINT32* plt, UINT32* board_opt);     /* platform prober */
extern void BASE_PLT_Init(void);    /* platform depdendent initializer */

extern void BASE_PROC_Init(void);

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void BASE_ProbeChipRev(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
    Implementation Group
========================================================================================*/

/**
 * initialize base device.
 * if global link mode, this device calls all init function of each module.
 *
*/
int BASE_Init(void)
{
    printk("<!> initialzing lg1k kdriver...\n");

    OS_CORE_Init();     /* initialize OS framework */

    OS_DEBUG_Init();    /* initialize debug framework   */

    BASE_ProbeChipRev();    /* read chip info */

    OS_PROC_Init();     /* initialize proc framework    */

    BASE_DEV_PreInit(); /* preconfigure devices */
    BASE_PLT_Init();    /* initialize target platform environment */
    BASE_DEV_Init();    /* initialize SOC devices */

    BASE_PROC_Init();   /* initialize base module proc */
    return 0;
}

/**
 * cleanup base device.
 * if global link mode, this function calls all cleanup function of each module.
*/
void BASE_Cleanup(void)
{
    printk("<!> cleanup lg1k kdriver...\n");

    /* cleanup custom board */
    BASE_DEV_Cleanup();

    DBG_MSG("<!> custom board  cleanup..\n");

    /* cleanup all the base system */
    OS_PROC_Cleanup();
    OS_DEBUG_Cleanup();
    OS_CORE_Cleanup();

    LOGM_Cleanup();
}

static UINT32 BASE_ScanChipName(char chp_class, int chp_num, char chp_series)
{
    int i;
    static const struct
    {
        char chp_class;
        int chp_num;
        char chp_series;
        UINT32 chp_name;
    } chip_list[] =
    {
        {'L', 9, ' ', LX_CHIP_L9},
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

    const int num_list = sizeof(chip_list) / sizeof(chip_list[0]);

    for (i = 0; i < num_list; i++)
    {
        if (chip_list[i].chp_class == chp_class
                && chip_list[i].chp_num == chp_num
                && chip_list[i].chp_series == chp_series)
            return chip_list[i].chp_name;
    }

    return LX_CHIP_UNKNOWN;
}

/**
 *
 *
 */
static void BASE_ProbeChipRev(void)
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

        if (RET_OK !=
                OS_OpenFile(&file, "/proc/cmdline", O_RDONLY | O_LARGEFILE,
                            0666))
        {
            printk("<error> can't open /proc/cmdline\n");
            goto func_exit;
        }

        memset(cmd_buf, 0, cmd_buf_sz);

        if (0 >= OS_ReadFile(&file, cmd_buf, cmd_buf_sz - 1))
        {
            OS_CloseFile(&file);
            printk("<error> can't read /proc/cmdline\n");
            goto func_exit;
        }

        OS_CloseFile(&file);
    }
#else
    {
        extern char* saved_command_line;
        snprintf(cmd_buf, cmd_buf_sz - 1, "%s", saved_command_line);
    }
#endif

    /* initialize data */
    g_base_dev_cfg.chip_rev = 0x0;
    g_base_dev_cfg.ace_rev = 0x0;
    g_base_dev_cfg.chip_plt = 0x0;

    {
#define TOKEN_DCHIP     0x1
#define TOKEN_ACHIP     0x2
#define TOKEN_PLATFORM  0x4
        UINT8 status = TOKEN_DCHIP | TOKEN_ACHIP;   //TOKEN_PLATFORM
        UINT8 chip_model;
        UINT32 chip_rev;

        char chp_class, rev_class, rev_series = ' ';
        int chp_num, rev_num;

        tok = simple_strtok(cmd_buf, delim, &sav_tok);

        while (tok)
        {
            chip_model = 0x0;
            chip_rev = 0x0;

            if (status & TOKEN_DCHIP)
            {
                if ((4 ==
                        sscanf(tok, "chip=%c%d%c%d", &chp_class,
                               &chp_num, &rev_class, &rev_num))
                        || (5 ==
                            sscanf(tok, "chip=%c%d%c%c%d",
                                   &chp_class, &chp_num,
                                   &rev_series, &rev_class,
                                   &rev_num)))
                {
                    chip_model =
                        BASE_ScanChipName(chp_class,
                                          chp_num,
                                          rev_series);
                    chip_rev =
                        (((rev_class - 'A') + 0xA) << 4) +
                        rev_num;

                    g_base_dev_cfg.chip_rev =
                        MAKE_CHIP_REV(chip_model, chip_rev);
                    status &= ~TOKEN_DCHIP;
                }
            }

            rev_series = ' ';

            /* find ace = L,9,A,0 or H,13,A,0 .. */
            if ((status & TOKEN_ACHIP)
                    && sscanf(tok, "ace=%c%d%c%d", &chp_class, &chp_num,
                              &rev_class, &rev_num) == 4)
            {
                chip_model =
                    BASE_ScanChipName(chp_class, chp_num,
                                      rev_series);
                chip_rev =
                    (((rev_class - 'A') + 0xA) << 4) + rev_num;

                g_base_dev_cfg.ace_rev =
                    MAKE_CHIP_REV(chip_model, chip_rev);
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
    if (g_base_dev_cfg.chip_rev == 0x0)
        g_base_dev_cfg.chip_rev = LX_CHIP_UNKNOWN;

    if (g_base_dev_cfg.ace_rev == 0x0)
        g_base_dev_cfg.ace_rev = g_base_dev_cfg.chip_rev;

#ifdef CONFIG_LX_CHIP_EMUL
#if CONFIG_LX_CHIP_EMUL
    g_base_dev_cfg.chip_rev = CONFIG_LX_CHIP_EMUL;
    g_base_dev_cfg.ace_rev = CONFIG_LX_CHIP_EMUL;
#endif
#endif

    BASE_PLT_Probe(&g_base_dev_cfg.chip_plt, &g_base_dev_cfg.board_opt);    /* probe chip platform & board option */

    printk("+ CHIP_REV=0x%04X CHIP_PLT=0x%04X BOARD_OPT=0x%08X\n",
           g_base_dev_cfg.chip_rev, g_base_dev_cfg.chip_plt,
           g_base_dev_cfg.board_opt);
}

UINT32 lx_chip(void)
{
    return (g_base_dev_cfg.chip_rev >> 8) & 0xff;
}

EXPORT_SYMBOL(lx_chip);

UINT32 lx_chip_rev(void)
{
    return g_base_dev_cfg.chip_rev;
}

EXPORT_SYMBOL(lx_chip_rev);

UINT32 lx_ace(void)
{
    return (g_base_dev_cfg.ace_rev >> 8) & 0xff;
}

EXPORT_SYMBOL(lx_ace);

UINT32 lx_ace_rev(void)
{
    return g_base_dev_cfg.ace_rev;
}

EXPORT_SYMBOL(lx_ace_rev);

UINT32 lx_chip_plt(void)
{
    return g_base_dev_cfg.chip_plt;
}

EXPORT_SYMBOL(lx_chip_plt);

UINT32 lx_board_opt(void)
{
    return g_base_dev_cfg.board_opt;
}

EXPORT_SYMBOL(lx_board_opt);

/////////////////////////////////////////////////////////////////////////////////////////
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv", BASE_Init);
#else
module_init(BASE_Init);
#endif
module_exit(BASE_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("BASE driver");
MODULE_LICENSE("GPL");

/** @} */
