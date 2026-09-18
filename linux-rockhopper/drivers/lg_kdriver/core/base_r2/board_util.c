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
 *  @date       2024-11-11
 *  @note       Additional information.
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
#undef TEST

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_impl.h"
#include "board_opts.h"
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define DEFINE_DESC(prefix, name)   { .id = prefix##_##name , .text = #name }

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
struct board_opt_desc
{
    u32 id;
    char* text;
};

/*----------------------------------------------------------------------------------------
    Function Prototype Declarations
----------------------------------------------------------------------------------------*/
u32 get_base_board_opt(void);
u32 get_base_chip_plt(void);
int  print_board_opts(struct seq_file* s, void* data);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static struct board_opt_desc country_type_desc[] =
{
    DEFINE_DESC(MODELOPT_COUNTRY, AJ_JA),
    DEFINE_DESC(MODELOPT_COUNTRY, TW_CO),
    DEFINE_DESC(MODELOPT_COUNTRY, KR),
    DEFINE_DESC(MODELOPT_COUNTRY, EU),
    DEFINE_DESC(MODELOPT_COUNTRY, US),
    DEFINE_DESC(MODELOPT_COUNTRY, BR),
    DEFINE_DESC(MODELOPT_COUNTRY, JP),
    DEFINE_DESC(MODELOPT_COUNTRY, CN_HK),
    DEFINE_DESC(MODELOPT_COUNTRY, NONE),
};

static struct board_opt_desc panel_interface_desc[] =
{
    DEFINE_DESC(MODELOPT_PANEL_INTERFACE, EPI),
    DEFINE_DESC(MODELOPT_PANEL_INTERFACE, LVDS),
    DEFINE_DESC(MODELOPT_PANEL_INTERFACE, VBYONE),
    DEFINE_DESC(MODELOPT_PANEL_INTERFACE, CEDS),
    DEFINE_DESC(MODELOPT_PANEL_INTERFACE, EPI_QSAC),
    DEFINE_DESC(MODELOPT_PANEL_INTERFACE, EDP),
};

static struct board_opt_desc panel_resolution_desc[] =
{
    DEFINE_DESC(MODELOPT_PANEL_RESOLUTION, HD),
    DEFINE_DESC(MODELOPT_PANEL_RESOLUTION, FHD),
    DEFINE_DESC(MODELOPT_PANEL_RESOLUTION, UD),
    DEFINE_DESC(MODELOPT_PANEL_RESOLUTION, 8K),
    DEFINE_DESC(MODELOPT_PANEL_RESOLUTION, QHD),
    DEFINE_DESC(MODELOPT_PANEL_RESOLUTION, WQHD),
};


static struct board_opt_desc panel_type_desc[] =
{
    DEFINE_DESC(MODELOPT_PANEL, TYPE_NONE),
    DEFINE_DESC(MODELOPT_PANEL, V12),
    DEFINE_DESC(MODELOPT_PANEL, V13),
    DEFINE_DESC(MODELOPT_PANEL, V14),
    DEFINE_DESC(MODELOPT_PANEL, V14_32inch),
    DEFINE_DESC(MODELOPT_PANEL, V15),
    DEFINE_DESC(MODELOPT_PANEL, V16),
    DEFINE_DESC(MODELOPT_PANEL, V17),
};

static struct board_opt_desc panel_output_frame_rate_desc[] =
{
    DEFINE_DESC(MODELOPT_PANEL_OUTPUT_FRAME_RATE, 60HZ),
    DEFINE_DESC(MODELOPT_PANEL_OUTPUT_FRAME_RATE, 120HZ),
    DEFINE_DESC(MODELOPT_PANEL_OUTPUT_FRAME_RATE, 144HZ),
    DEFINE_DESC(MODELOPT_PANEL_OUTPUT_FRAME_RATE, 165HZ),
    DEFINE_DESC(MODELOPT_PANEL_OUTPUT_FRAME_RATE, 240HZ),
    DEFINE_DESC(MODELOPT_PANEL_OUTPUT_FRAME_RATE, 100HZ),
    DEFINE_DESC(MODELOPT_PANEL_OUTPUT_FRAME_RATE, 180HZ),
};

static struct board_opt_desc ddr_size_desc[] =
{
    DEFINE_DESC(DDR_SIZE, 768M),
    DEFINE_DESC(DDR_SIZE, 1G),
    DEFINE_DESC(DDR_SIZE, 1_25G),
    DEFINE_DESC(DDR_SIZE, 1_5G),
    DEFINE_DESC(DDR_SIZE, 2G),
    DEFINE_DESC(DDR_SIZE, 2_5G),
    DEFINE_DESC(DDR_SIZE, 3G),
    DEFINE_DESC(DDR_SIZE, 2G_ADV),
    DEFINE_DESC(DDR_SIZE, 2G_STD),
    DEFINE_DESC(DDR_SIZE, 4G),
    DEFINE_DESC(DDR_SIZE, 5G),
    DEFINE_DESC(DDR_SIZE, 3_5G),
    DEFINE_DESC(DDR_SIZE, 8G),
};

static struct board_opt_desc graphic_resolution_desc[] =
{
    DEFINE_DESC(MODELOPT_GRAPHIC, 1024X768),
    DEFINE_DESC(MODELOPT_GRAPHIC, 1366X768),
    DEFINE_DESC(MODELOPT_GRAPHIC, 1920X1080),
    DEFINE_DESC(MODELOPT_GRAPHIC, 2560X1080),
    DEFINE_DESC(MODELOPT_GRAPHIC, 3840X2160),
    DEFINE_DESC(MODELOPT_GRAPHIC, 5120X2160),
    DEFINE_DESC(MODELOPT_GRAPHIC, 1280X720),
    DEFINE_DESC(MODELOPT_GRAPHIC, 1920X804),
    DEFINE_DESC(MODELOPT_GRAPHIC, 2560X1440),
};

static struct board_opt_desc frc_type_desc[] =
{
    DEFINE_DESC(MODELOPT_FRC, NONE),
    DEFINE_DESC(MODELOPT_FRC, INTERNAL),
    DEFINE_DESC(MODELOPT_FRC, URSA9),
    DEFINE_DESC(MODELOPT_FRC, URSA9_P),
    DEFINE_DESC(MODELOPT_FRC, URSA11),
    DEFINE_DESC(MODELOPT_FRC, URSA11_P),
    DEFINE_DESC(MODELOPT_FRC, F16),
    DEFINE_DESC(MODELOPT_FRC, URSA17),
    DEFINE_DESC(MODELOPT_FRC, F20),
    DEFINE_DESC(MODELOPT_FRC, F22),
};

static struct board_opt_desc hdmi_output_desc[] =
{
    DEFINE_DESC(MODELOPT_HDMI_OUTPUT, NONE),
    DEFINE_DESC(MODELOPT_HDMI_OUTPUT, 60HZ),
    DEFINE_DESC(MODELOPT_HDMI_OUTPUT, 60HZ_FIXED),
};

static struct board_opt_desc board_type_desc[] =
{
    DEFINE_DESC(MODELOPT, SYS_BOARD),
    DEFINE_DESC(MODELOPT, SLT_BOARD),
    DEFINE_DESC(MODELOPT, FPGA_BOARD),
};

static void make_legacy_board_opts(void);
static void check_board_opt(void);
static void parse_device_tree(void);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
// 아래 기본값의 동작성은 각 칩마다 틀릴 수 있다.
// 특히 DDR size 의 경우는 실제 값으로 항상 설정되어져야 한다.
static struct board_opts board_ctx =
{
    .country_type = MODELOPT_COUNTRY_KR,
    .support_5byte_vx1_mode = 1,
    .panel_interface = MODELOPT_PANEL_INTERFACE_VBYONE,
    .panel_resolution = MODELOPT_PANEL_RESOLUTION_UD,
    .support_optic = 1,
    .panel_type = MODELOPT_PANEL_TYPE_NONE,
    .support_tuner = 1,
    .panel_output_frame_rate = MODELOPT_PANEL_OUTPUT_FRAME_RATE_120HZ,
    .ddr_size = DDR_SIZE_2_5G,
    .graphic_resolution = MODELOPT_GRAPHIC_1920X1080,
    .frc_type = MODELOPT_FRC_INTERNAL,
    .hdmi_output = MODELOPT_HDMI_OUTPUT_NONE,
    .board_type = MODELOPT_SYS_BOARD,
    .official = 0,
};

#if 0
gModelOpt.country_type,             // 1.HW_OPT_COUNTRY
gModelOpt.bSupport_5byteVx1Mode,    // 2.bSupport_5byteVx1Mode
gModelOpt.panel_interface,          // 3.HW_OPT_PANEL_INTERFACE
gModelOpt.panel_resolution,         // 4.HW_OPT_PANEL_RESOLUTION
gModelOpt.bSupport_frc,             // 5.HW_OPT_FRC
cmd_panel_type,                     // 6.HW_OPT_PANEL_TYPE
gModelOpt.bSupport_cp_box,          // 7.HW_OPT_CP_BOX
gModelOpt.SoCOutputFrameRate,       // 8.HW_OPT_SOC_OUTPUT_FRAME_RATE
gModelOpt.bSupport_tuner,           // 9.HW_OPT_TUNER
gModelOpt.panelOutputFrameRate,     // 10.HW_OPT_PANEL_OUTPUT_FRAME_RATE
gModelOpt.isSupportEWBS,            // 11.HW_OPT_EWBS
gModelOpt.ddr_size,                 // 12.HW_OPT_DDR_SIZE
gModelOpt.bSupportOptic,            // 13.HW_OPT_OPTIC
gModelOpt.division_type,            // 14.HW_OPT_DIVISION_TYPE
gModelOpt.graphic_resolution,       // 15.HW_OPT_GRAPHIC_RESOLUTION
gModelOpt.reserved,                 // 16.HW_OPT_BANDWIDTH
gModelOpt.reserved,                 // 17.HW_OPT_MODULE_TYPE
gModelOpt.frc_type                  // 18.HW_OPT_FRC_TYPE
#endif

static u32 legacy_board_opt = 0x0;
static u32 legacy_chip_plt = 0x0;

/*========================================================================================
    Implementation Group
========================================================================================*/
static int char_to_hex(unsigned char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    else if (ch >= 'a' && ch <= 'f')
    {
        return ch - 'a' + 10;
    }
    else if (ch >= 'A' && ch <= 'F')
    {
        return ch - 'A' + 10;
    }
    else
    {
        return -1;
    }
}

static char* get_board_opt_desc(struct board_opt_desc desc[], int num_desc, int id)
{
    int i;
    static char* unknown = "UNKNOWN";

    for (i = 0; num_desc; i++)
    {
        if (desc[i].id == id) return desc[i].text;
    }

    return unknown;
}

static char* get_boolean_desc(int val)
{
    static char* true_str = "TRUE";
    static char* false_str = "FALSE";

    return (val) ? true_str : false_str;
};

void lg1k_board_frwk_init(void)
{
    int i;
    int val;
    char optstr[256] = {0};
    const char* pioneer_board_fmtstr[2] = {"pioneer.board=%s", "pioneer.boardopts=%s"};

    if (RET_OK != os_scan_kernel_cmdline("hwopt=%s", optstr))
    {
        lg1k_logm_error("cant' find hwopt= token\n");
        return;
    }

#ifdef TEST
    {
        char test_hwopt[] = "412210010105102001";
        memcpy(optstr, test_hwopt, strlen(test_hwopt));
    }
#endif

    // parse country
    val = char_to_hex(optstr[0]);

    if (val >= 0) board_ctx.country_type = (MODELOPT_COUNTRY_T)val;
    else          lg1k_logm_error("unknown country type. use default vale=0x%x\n", board_ctx.country_type);

    // parse support 5byte vx1 mode
    val = char_to_hex(optstr[1]);

    if (val >= 0) board_ctx.support_5byte_vx1_mode = val;
    else          lg1k_logm_error("unknown 5byte_vx1_mode. use default vale=0x%x\n", board_ctx.support_5byte_vx1_mode);

    // parse panel interface
    val = char_to_hex(optstr[2]);

    if (val >= 0) board_ctx.panel_interface = (MODELOPT_PANEL_INTERFACE_T)val;
    else          lg1k_logm_error("unknown panel_interface. use default vale=0x%x\n", board_ctx.panel_interface);

    // parse panel_resolution
    val = char_to_hex(optstr[3]);

    if (val >= 0) board_ctx.panel_resolution = (MODELOPT_PANEL_RESOLUTION_T)val;
    else          lg1k_logm_error("unknown panel_resolution. use default vale=0x%x\n", board_ctx.panel_resolution);

    // parse optic
    val = char_to_hex(optstr[4]);

    if (val >= 0) board_ctx.support_optic = val;
    else          lg1k_logm_error("unknown support_optic. use default vale=0x%x\n", board_ctx.support_optic);

    // parse panel type
    val = char_to_hex(optstr[5]);

    if (val >= 0) board_ctx.panel_type = (MODELOPT_PANEL_T)val;
    else          lg1k_logm_error("unknown panel_type. use default vale=0x%x\n", board_ctx.panel_type);

    // parse tuner
    val = char_to_hex(optstr[8]);

    if (val >= 0) board_ctx.support_tuner = val;
    else          lg1k_logm_error("unknown support_tuner. use default vale=0x%x\n", board_ctx.support_tuner);

    // parse panel output frame rate
    val = char_to_hex(optstr[9]);

    if (val >= 0) board_ctx.panel_output_frame_rate = (MODELOPT_PANEL_OUTPUT_FRAME_RATE_T)val;
    else          lg1k_logm_error("unknown panel_output_frame_rate. use default vale=0x%x\n",
                                      board_ctx.panel_output_frame_rate);

    // parse ddr_size
    val = char_to_hex(optstr[11]);

    if (val >= 0) board_ctx.ddr_size = (MODELOPT_DDR_SIZE_T)val;
    else          lg1k_logm_error("unknown ddr_size. use default vale=0x%x\n", board_ctx.ddr_size);

    // parse graphic resolution
    val = char_to_hex(optstr[14]);

    if (val >= 0) board_ctx.graphic_resolution = (MODELOPT_GRAPHIC_RESOLUTION_T)val;
    else          lg1k_logm_error("unknown graphic_resolution. use default vale=0x%x\n", board_ctx.graphic_resolution);

    // parse frc type
    val = char_to_hex(optstr[17]);

    if (val >= 0) board_ctx.frc_type = (MODELOPT_FRC_T)val;
    else          lg1k_logm_error("unknown frc_type. use default vale=0x%x\n", board_ctx.frc_type);

    check_board_opt();

    // something to override board options
    if (RET_OK != os_scan_kernel_cmdline("disp=%s", optstr))
    {
        if (!strncmp(optstr, "hdmi", 4))
        {
            if (!strncmp(optstr, "hdmi60", 6))
            {
                board_ctx.hdmi_output = MODELOPT_HDMI_OUTPUT_60HZ_FIXED;
            }
            else if (!strncmp(optstr, "hdmi5060", 8))
            {
                board_ctx.hdmi_output = MODELOPT_HDMI_OUTPUT_60HZ;
            }
            else if (!strncmp(optstr, "hdmi2k", 6))
            {
                board_ctx.hdmi_output = MODELOPT_HDMI_OUTPUT_60HZ;
                board_ctx.panel_resolution = MODELOPT_PANEL_RESOLUTION_FHD;
            }
        }

        if (!strncmp(optstr, "4byte", 5))
        {
            board_ctx.support_5byte_vx1_mode = 0;
        }
        else if (!strncmp(optstr, "5byte", 5))
        {
            board_ctx.support_5byte_vx1_mode = 1;
        }
    }

    // parse PIONEER board options
    for (i = 0; i < NELEMENTS(pioneer_board_fmtstr); i++)
    {
        if (RET_OK == os_scan_kernel_cmdline(pioneer_board_fmtstr[i], optstr))
        {
            char* tok, *sav_tok;
            char delim[] = ",\t\n";

            tok = simple_strtok(optstr, delim, &sav_tok);

            while (tok)
            {
                if (!strncasecmp(tok, "1.0GB", 5))  board_ctx.ddr_size = DDR_SIZE_1G;

                if (!strncasecmp(tok, "1.5GB", 5))  board_ctx.ddr_size = DDR_SIZE_1_5G;

                if (!strncasecmp(tok, "2.0GB", 5))  board_ctx.ddr_size = DDR_SIZE_2G;

                if (!strncasecmp(tok, "2.5GB", 5))  board_ctx.ddr_size = DDR_SIZE_2_5G;

                if (!strncasecmp(tok, "3.0GB", 5))  board_ctx.ddr_size = DDR_SIZE_3G;

                if (!strncasecmp(tok, "3.5GB", 5))  board_ctx.ddr_size = DDR_SIZE_3_5G;

                if (!strncasecmp(tok, "4G", 2))     board_ctx.ddr_size = DDR_SIZE_4G;

                if (!strncasecmp(tok, "4.0GB", 5))  board_ctx.ddr_size = DDR_SIZE_4G;

                if (!strncasecmp(tok, "5.0GB", 5))  board_ctx.ddr_size = DDR_SIZE_5G;

                if (!strncasecmp(tok, "8G", 2))     board_ctx.ddr_size = DDR_SIZE_8G;

                if (!strncasecmp(tok, "8.0G", 4))   board_ctx.ddr_size = DDR_SIZE_8G;

                if (!strncasecmp(tok, "FHD", 3))
                {
                    board_ctx.panel_resolution = MODELOPT_PANEL_RESOLUTION_FHD;
                }

                if (!strncasecmp(tok, "UHD", 3))
                {
                    board_ctx.panel_resolution = MODELOPT_PANEL_RESOLUTION_UD;
                }

                if (!strncasecmp(tok, "UHD", 3))
                {
                    board_ctx.panel_resolution = MODELOPT_PANEL_RESOLUTION_8K;
                }

                if (!strncasecmp(tok, "LCD", 3))
                {
                    board_ctx.support_optic = 0;
                }

                if (!strncasecmp(tok, "OLED", 4))
                {
                    board_ctx.support_optic = 1;
                }

                if (!strncasecmp(tok, "EPI", 3))
                {
                    board_ctx.panel_interface = MODELOPT_PANEL_INTERFACE_EPI;
                }

                if (!strncasecmp(tok, "LVDS", 4))
                {
                    board_ctx.panel_interface = MODELOPT_PANEL_INTERFACE_LVDS;
                }

                if (!strncasecmp(tok, "VBYONE", 6))
                {
                    board_ctx.panel_interface = MODELOPT_PANEL_INTERFACE_VBYONE;
                }

                if (!strncasecmp(tok, "2KOSD", 5))
                {
                    board_ctx.graphic_resolution = MODELOPT_GRAPHIC_1920X1080;
                }

                if (!strncasecmp(tok, "4KOSD", 5))
                {
                    board_ctx.graphic_resolution = MODELOPT_GRAPHIC_3840X2160;
                }

                if (!strncasecmp(tok, "SYS_BOARD", 9))
                {
                    board_ctx.board_type = MODELOPT_SYS_BOARD;
                }

                if (!strncasecmp(tok, "SLT_BOARD", 9))
                {
                    board_ctx.board_type = MODELOPT_SLT_BOARD;
                }

                if (!strncasecmp(tok, "FPGA_BOARD", 10))
                {
                    board_ctx.board_type = MODELOPT_FPGA_BOARD;
                }

                tok = simple_strtok(NULL, delim, &sav_tok);
            }
        }
    }

#ifdef BUILD_FEATURE_fpga
    board_ctx.board_type = MODELOPT_FPGA_BOARD;
#endif
#ifdef BUILD_FEATURE_slt
    board_ctx.board_type = MODELOPT_SLT_BOARD;
#endif

#ifdef CHIP_NAME_o24

    // O24: SLT 보드는 실제 DDR 용량과 상관없이 3.5GB (8K 지원) 메모리맵 설정을 하도록 한다.
    if (board_ctx.board_type == MODELOPT_SLT_BOARD)
    {
        lg1k_logm_noti("<warning> SLT board uses 3.5GB memory map. ddr_size is changed from %d to %d\n",
                       board_ctx.ddr_size, DDR_SIZE_3_5G);

        board_ctx.ddr_size = DDR_SIZE_3_5G;
    }

#endif

    lg1k_logm_noti("board.country_type=0x%x\n", board_ctx.country_type);
    lg1k_logm_noti("board.support_5byte_vx1_mode=0x%x\n", board_ctx.support_5byte_vx1_mode);
    lg1k_logm_noti("board.panel_interface=0x%x\n", board_ctx.panel_interface);
    lg1k_logm_noti("board.panel_resolution=0x%x\n", board_ctx.panel_resolution);
    lg1k_logm_noti("board.support_optic=0x%x\n", board_ctx.support_optic);
    lg1k_logm_noti("board.panel_type=0x%x\n", board_ctx.panel_type);
    lg1k_logm_noti("board.support_tuner=0x%x\n", board_ctx.support_tuner);
    lg1k_logm_noti("board.panel_output_frame_rate=0x%x\n", board_ctx.panel_output_frame_rate);
    lg1k_logm_noti("board.ddr_size=0x%x\n", board_ctx.ddr_size);
    lg1k_logm_noti("board.graphic_resolution=0x%x\n", board_ctx.graphic_resolution);
    lg1k_logm_noti("board.frc_type=0x%x\n", board_ctx.frc_type);
    lg1k_logm_noti("board.hdmi_output=0x%x\n", board_ctx.hdmi_output);
    lg1k_logm_noti("board.borad_type=0x%x\n", board_ctx.board_type);
    lg1k_logm_noti("board.official=0x%x\n", board_ctx.official);

    parse_device_tree();

    make_legacy_board_opts();
}

void lg1k_board_frwk_cleanup(void)
{
    /* do nothing */
}

struct board_opts get_board_opts(void)
{
    return board_ctx;
}
EXPORT_SYMBOL(get_board_opts);

u32 get_base_board_opt(void)
{
    return legacy_board_opt;
}

u32 get_base_chip_plt(void)
{
    return legacy_chip_plt;
}

// board opt 값들에 대한 정상 유무를 체크한다.
// 가령 TV 에서 hwopt= 문자열의 진위 유무를 기록한다면, 해당 정보를 읽도록 한다.
static void check_board_opt(void)
{
#ifdef BUILD_FEATURE_pioneer
    board_ctx.official = 1;
#endif

    // check if hwopt is official
    lg1k_logm_noti("boardopt check: %s\n", board_ctx.official ? "OFFICIAL" : "NON-OFFICIAL");
}

static void parse_device_tree(void)
{
    struct device_node* ddr_node = NULL;
    const char* clock_str = NULL;
    const char* size_str = NULL;
    const char* m0_str = NULL;
    const char* m1_str = NULL;
    const char* m2_str = NULL;
    struct property* prop;
    int ret;

    board_ctx.soc.ddr.clock = 0;
    board_ctx.soc.ddr.size = 0;
    board_ctx.soc.ddr.m0 = 0;
    board_ctx.soc.ddr.m1 = 0;
    board_ctx.soc.ddr.m2 = 0;

    ddr_node = of_find_node_by_path("/soc/hw-info/ddr");

    if (!ddr_node)
    {
        lg1k_logm_error("/soc/hw-info/ddr node not found\n");
        return;
    }

    // parse clock
    ret = of_property_read_string(ddr_node, "clock", &clock_str);

    if (ret == 0)
    {
        unsigned long freq;

        if (sscanf(clock_str, "%luMHz", &freq) == 1)
        {
            lg1k_logm_noti("hw_info/ddr/clock: %lu MHz\n", freq);
            board_ctx.soc.ddr.clock = freq;
        }
    }
    else
    {
        lg1k_logm_error("/soc/hw_info/ddr/clock prop not found\n");
    }

    // parse size
    ret = of_property_read_string(ddr_node, "size", &size_str);

    if (ret == 0)
    {
        unsigned long size_mb = 0;
        unsigned long size_int = 0, size_frac = 0;

        if (strchr(size_str, '.'))
        {
            sscanf(size_str, "%lu.%luG", &size_int, &size_frac);
            size_mb = (size_int << 10) + ((size_frac * (1UL << 10)) / 10);
        }
        else
        {
            sscanf(size_str, "%luG", &size_int);
            size_mb = size_int << 10;
        }

        lg1k_logm_noti("hw_info/ddr/size: %lu MB\n", size_mb);
        board_ctx.soc.ddr.size = size_mb;
    }
    else
    {
        pr_warn("/soc/hw_info/ddr/size prop not found\n");
    }

    // parse m0
    ret = of_property_read_string(ddr_node, "m0", &m0_str);

    if (ret == 0)
    {
        unsigned long size_mb;

        sscanf(m0_str, "%luMB", &size_mb);

        lg1k_logm_noti("hw_info/ddr/m0: %lu MB\n", size_mb);
        board_ctx.soc.ddr.m0 = size_mb;
    }
    else
    {
        lg1k_logm_error("/soc/hw_info/ddr/m0 prop not found\n");
    }

    // parse m1
    ret = of_property_read_string(ddr_node, "m1", &m1_str);

    if (ret == 0)
    {

        unsigned long size_mb;

        sscanf(m1_str, "%luMB", &size_mb);
        lg1k_logm_noti("hw_info/ddr/m1: %lu MB\n", size_mb);
        board_ctx.soc.ddr.m1 = size_mb;
    }
    else
    {
        lg1k_logm_error("/soc/hw_info/ddr/m1 prop not found\n");
    }

    // parse m2
    ret = of_property_read_string(ddr_node, "m2", &m2_str);

    if (ret == 0)
    {
        unsigned long size_mb;

        sscanf(m2_str, "%luMB", &size_mb);
        lg1k_logm_noti("hw_info/ddr/m2: %lu MB\n", size_mb);
        board_ctx.soc.ddr.m2 = size_mb;
    }
    else
    {
        lg1k_logm_error("/soc/hw_info/ddr/m2 prop not found\n");
    }

    if (ddr_node)
    {
        of_node_put(ddr_node);
    }
}

// 기존 사용하는 lx_board_opt(), lx_chip_plt() 에서 리턴하는 값들을 만든다
// 과도기적으로 기존 LX_CHIP_PLT_xxx 와 LX_BOARD_OPTS_xxx 를 지원하도록 한다.
// 장기적으로 드라이버에서의 해당 함수와 타입의 사용을 없애야 할것이다.
// 즉 get_board_opts() 함수를 호출하여 상세 보드 옵션를 얻어야 할것이다
static void make_legacy_board_opts(void)
{
    switch (board_ctx.panel_resolution)
    {
        case MODELOPT_PANEL_RESOLUTION_8K:  legacy_chip_plt |= LX_CHIP_PLT_QUHD; break;

        case MODELOPT_PANEL_RESOLUTION_FHD: legacy_chip_plt |= LX_CHIP_PLT_FHD; break;

        case MODELOPT_PANEL_RESOLUTION_UD:
        default:                            legacy_chip_plt |= LX_CHIP_PLT_UHD; break;
    }

    switch (board_ctx.ddr_size)
    {
        case DDR_SIZE_1G:                   legacy_board_opt |= LX_BOARD_OPT_DDR_1_0GB; break;

        case DDR_SIZE_1_5G:                 legacy_board_opt |= LX_BOARD_OPT_DDR_1_5GB; break;

        case DDR_SIZE_2G:                   legacy_board_opt |= (LX_BOARD_OPT_DDR_2_0GB | LX_BOARD_OPT_ADV); break;

        case DDR_SIZE_3G:                   legacy_board_opt |= (LX_BOARD_OPT_DDR_3_0GB | LX_BOARD_OPT_ADV); break;

        case DDR_SIZE_4G:                   legacy_board_opt |= (LX_BOARD_OPT_DDR_4_0GB | LX_BOARD_OPT_ADV); break;

        case DDR_SIZE_5G:                   legacy_board_opt |= (LX_BOARD_OPT_DDR_5_0GB | LX_BOARD_OPT_ADV); break;

        case DDR_SIZE_3_5G:                 legacy_board_opt |= (LX_BOARD_OPT_DDR_3_5GB | LX_BOARD_OPT_ADV); break;

        case DDR_SIZE_8G:                   legacy_board_opt |= (LX_BOARD_OPT_DDR_8_0GB | LX_BOARD_OPT_ADV); break;

        case DDR_SIZE_2_5G:
        default:                            legacy_board_opt |= (LX_BOARD_OPT_DDR_2_5GB | LX_BOARD_OPT_ADV); break;
    }

    switch (board_ctx.frc_type)
    {
        case MODELOPT_FRC_NONE:
        case MODELOPT_FRC_INTERNAL:         legacy_board_opt |= LX_BOARD_OPT_INT_FRC; break;

        default:                            legacy_board_opt |= LX_BOARD_OPT_EXT_FRC; break;
    }

#if 0

    switch (board_ctx.panel_interface)
    {
        case MODELOPT_PANEL_INTERFACE_EPI:  legacy_board_opt |= LX_BOARD_OPT_EPI; break;

        default:                            /* do nothing */; break;
    }

#endif

    switch (board_ctx.panel_output_frame_rate)
    {
        case MODELOPT_PANEL_OUTPUT_FRAME_RATE_60HZ: legacy_board_opt |= LX_BOARD_OPT_DISP_60HZ; break;

        default:                            legacy_board_opt |= LX_BOARD_OPT_DISP_120HZ; break;
    }

    switch (board_ctx.support_optic)
    {
        case 1:                             legacy_board_opt |= LX_BOARD_OPT_OLED; break;

        default:                            legacy_board_opt |= LX_BOARD_OPT_LCD; break;
    }

    switch (board_ctx.graphic_resolution)
    {
        case MODELOPT_GRAPHIC_3840X2160:    legacy_board_opt |= LX_BOARD_OPT_4K_GRAPHIC; break;

        default:                            legacy_board_opt |= LX_BOARD_OPT_2K_GRAPHIC; break;
    }

    switch (board_ctx.board_type)
    {
        case MODELOPT_FPGA_BOARD:           legacy_board_opt |= LX_BOARD_OPT_FPGA; break;

        case MODELOPT_SLT_BOARD:            legacy_board_opt |= (LX_BOARD_OPT_SLT | LX_BOARD_OPT_SLT_MAP);  break;

        default:                            legacy_board_opt |= LX_BOARD_OPT_SYSTEM; break;
    }
}

int  print_board_opts(struct seq_file* s, void* data)
{
    seq_printf(s, "country_type: 0x%x (%s)\n",
               board_ctx.country_type, get_board_opt_desc(country_type_desc, NELEMENTS(country_type_desc), board_ctx.country_type));

    seq_printf(s, "support_5byte_vx1_mode: 0x%x (%s)\n",
               board_ctx.support_5byte_vx1_mode, get_boolean_desc(board_ctx.support_5byte_vx1_mode));

    seq_printf(s, "panel_interface: 0x%x (%s)\n",
               board_ctx.panel_interface, get_board_opt_desc(panel_interface_desc, NELEMENTS(panel_interface_desc),
                       board_ctx.panel_interface));

    seq_printf(s, "panel_resolution: 0x%x (%s)\n",
               board_ctx.panel_resolution, get_board_opt_desc(panel_resolution_desc, NELEMENTS(panel_resolution_desc),
                       board_ctx.panel_resolution));

    seq_printf(s, "support_optic: 0x%x (%s)\n",
               board_ctx.support_optic, get_boolean_desc(board_ctx.support_optic));

    seq_printf(s, "panel_type: 0x%x (%s)\n",
               board_ctx.panel_type, get_board_opt_desc(panel_type_desc, NELEMENTS(panel_type_desc), board_ctx.panel_type));

    seq_printf(s, "support_tuner: 0x%x (%s)\n",
               board_ctx.support_tuner, get_boolean_desc(board_ctx.support_tuner));

    seq_printf(s, "panel_output_frame_rate: 0x%x (%s)\n",
               board_ctx.panel_output_frame_rate, get_board_opt_desc(panel_output_frame_rate_desc,
                       NELEMENTS(panel_output_frame_rate_desc), board_ctx.panel_output_frame_rate));

    seq_printf(s, "ddr_size: 0x%x (%s)\n",
               board_ctx.ddr_size, get_board_opt_desc(ddr_size_desc, NELEMENTS(ddr_size_desc), board_ctx.ddr_size));

    seq_printf(s, "graphic_resolution: 0x%x (%s)\n",
               board_ctx.graphic_resolution, get_board_opt_desc(graphic_resolution_desc, NELEMENTS(graphic_resolution_desc),
                       board_ctx.graphic_resolution));

    seq_printf(s, "frc_type: 0x%x (%s)\n",
               board_ctx.frc_type, get_board_opt_desc(frc_type_desc, NELEMENTS(frc_type_desc), board_ctx.frc_type));

    seq_printf(s, "hdmi_output: 0x%x (%s)\n",
               board_ctx.hdmi_output, get_board_opt_desc(hdmi_output_desc, NELEMENTS(hdmi_output_desc), board_ctx.hdmi_output));

    seq_printf(s, "board_type: 0x%x (%s)\n",
               board_ctx.board_type, get_board_opt_desc(board_type_desc, NELEMENTS(board_type_desc), board_ctx.board_type));

    seq_printf(s, "official: 0x%x (%s)\n",
               board_ctx.official, get_boolean_desc(board_ctx.official));

    seq_printf(s, "\n");
    seq_printf(s, "[Device Tree Info]\n");

    seq_printf(s, "/soc/hw_info/ddr/clock: %d MHz\n", board_ctx.soc.ddr.clock);
    seq_printf(s, "/soc/hw_info/ddr/size: %d MB\n", board_ctx.soc.ddr.size);
    seq_printf(s, "/soc/hw_info/ddr/m0: %d MB\n", board_ctx.soc.ddr.m0);
    seq_printf(s, "/soc/hw_info/ddr/m1: %d MB\n", board_ctx.soc.ddr.m1);
    seq_printf(s, "/soc/hw_info/ddr/m2: %d MB\n", board_ctx.soc.ddr.m2);

    seq_printf(s, "\n");
    seq_printf(s, "[Legacy Board Info]\n");

    if (legacy_chip_plt & LX_CHIP_PLT_HD)   seq_printf(s, "LX_CHIP_PLT_UD\n");

    if (legacy_chip_plt & LX_CHIP_PLT_FHD)  seq_printf(s, "LX_CHIP_PLT_FHD\n");

    if (legacy_chip_plt & LX_CHIP_PLT_UHD)  seq_printf(s, "LX_CHIP_PLT_UHD\n");

    if (legacy_chip_plt & LX_CHIP_PLT_QUHD) seq_printf(s, "LX_CHIP_PLT_QUHD\n");

    seq_printf(s, "LX_BOARD_OPT_EXT_FRC: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_EXT_FRC));
    seq_printf(s, "LX_BOARD_OPT_INT_FRC: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_INT_FRC));
    seq_printf(s, "LX_BOARD_OPT_LCD: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_LCD));
    seq_printf(s, "LX_BOARD_OPT_OLED: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_OLED));

    seq_printf(s, "LX_BOARD_OPT_HD_GRAPHIC: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_HD_GRAPHIC));
    seq_printf(s, "LX_BOARD_OPT_2K_GRAPHIC: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_2K_GRAPHIC));
    seq_printf(s, "LX_BOARD_OPT_4K_GRAPHIC: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_4K_GRAPHIC));

    seq_printf(s, "LX_BOARD_OPT_DDR_1_5GB: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_DDR_1_5GB));
    seq_printf(s, "LX_BOARD_OPT_DDR_2_0GB: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_DDR_2_0GB));
    seq_printf(s, "LX_BOARD_OPT_DDR_2_5GB: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_DDR_2_5GB));
    seq_printf(s, "LX_BOARD_OPT_DDR_3_0GB: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_DDR_3_0GB));
    seq_printf(s, "LX_BOARD_OPT_DDR_3_5GB: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_DDR_3_5GB));
    seq_printf(s, "LX_BOARD_OPT_DDR_8_0GB: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_DDR_8_0GB));

    seq_printf(s, "LX_BOARD_OPT_ADV: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_ADV));

    seq_printf(s, "LX_BOARD_OPT_DISP_60HZ: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_DISP_60HZ));
    seq_printf(s, "LX_BOARD_OPT_DISP_120HZ: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_DISP_120HZ));

    seq_printf(s, "LX_BOARD_OPT_FPGA: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_FPGA));
    seq_printf(s, "LX_BOARD_OPT_SYSTEM: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_SYSTEM));
    seq_printf(s, "LX_BOARD_OPT_SLT: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_SLT));
    seq_printf(s, "LX_BOARD_OPT_SLT_MAP: %d\n", !!(legacy_board_opt & LX_BOARD_OPT_SLT_MAP));

    return 0;
}

