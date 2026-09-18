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
#undef REG_ADDR_AUTO_SCAN

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

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions (register manual)
----------------------------------------------------------------------------------------*/
struct port_selector_ctrl
{
    uint32_t wr_m2 : 2, // [0:1]
             : 2,
             wr_m1 : 2, // [4:5]
             : 2,
             wr_m0 : 2, // [8:9]
             : 2,
             wr_en : 1, // [12:12]
             : 3,
             rd_m2 : 2, // [16:17]
             : 2,
             rd_m1 : 2, // [20:21]
             : 2,
             rd_m0 : 2, // [24:25]
             : 2,
             rd_en : 1, // [28:28]
             : 3;
};

struct pending_limiter_ctrl
{
    uint32_t wr_pend : 7, // [0:6]
             : 9,
             rd_pend : 7, // [16:22]
             : 9;
};

struct priority0_ctrl
{
    UINT32 rf_uc_nbudget_cmd_w             : 7,    //  0: 6
           : 1,                                    //     7 reserved
           rf_uc_user_qos_sel_w            : 1,    //     8
           : 3,                                    //  9:11 reserved
           rf_uc_user_mode_w               : 3,    // 12:14
           : 1,                                    //    15 reserved
           rf_uc_nbudget_cmd_r             : 7,    // 16:22
           : 1,                                    //    23 reserved
           rf_uc_user_qos_sel_r            : 1,    //    24
           : 3,                                    // 25:27 reserved
           rf_uc_user_mode_r               : 3;    // 28:30
} USER_BIT_CONTROL_MODE;

struct priority1_ctrl
{
    uint32_t rf_uc_m1_sub_user_w             : 4,    //  0: 3
             rf_uc_m1_main_user_w            : 4,    //  4: 7
             rf_uc_m0_sub_user_w             : 4,    //  8:11
             rf_uc_m0_main_user_w            : 4,    // 12:15
             rf_uc_m1_sub_user_r             : 4,    // 16:19
             rf_uc_m1_main_user_r            : 4,    // 20:23
             rf_uc_m0_sub_user_r             : 4,    // 24:27
             rf_uc_m0_main_user_r            : 4;    // 28:31
};

struct priority2_ctrl
{
    uint32_t : 8,                                    //  0: 7 reserved
             rf_uc_m2_sub_user_w             : 4,    //  8:11
             rf_uc_m2_main_user_w            : 4,    // 12:15
             : 8,                                    // 16:23 reserved
             rf_uc_m2_sub_user_r             : 4,    // 24:27
             rf_uc_m2_main_user_r            : 4;    // 28:31
};

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
enum bwm_perf_level
{
    bwm_perf_level_default = 0, // default 설정
    bwm_perf_level_low1,        // 일반 PC 모드 대응
    bwm_perf_level_low2,        // 144Hz 대응
    bwm_perf_level_low3,        // 165Hz 대응
    bwm_perf_level_low4,        // Dolby HDMI 대응

    bwm_perf_level_demod,       // ATSC3.0 demod 특화
    bwm_perf_level_8k,          // ID O248K 모델 대응

    bwm_perf_level_max,
};

enum bwm_ddrc_perf_level
{
    bwm_ddrc_perf_level_default = 0, // default 설정
    bwm_ddrc_perf_level_low3,        // 165Hz 대응
    bwm_ddrc_perf_level_low4,
    bwm_ddrc_perf_level_demod,        // 165Hz 대응

    bwm_ddrc_perf_level_max,
};

enum axi_master
{
    AXI_CPU_M0,
    AXI_CPU_M1,
    AXI_GPU0,
    AXI_GPU1,
    AXI_GFX,
    AXI_LOWBW,
    AXI_ICVENC,
    AXI_MEFMS,
    AXI_FMGSSR0,
    AXI_FMGSSR1,
    AXI_FMGSSR2,
    AXI_FMGSSR3,
    AXI_FMGSSR4,
    AXI_CCO0,
    AXI_CCO1,
    AXI_ND0,
    AXI_ND1,
    AXI_VDOIMXW0,
    AXI_VDOIMXW1,
    AXI_VDOIMXW2,
    AXI_VDOIMXW3,
    AXI_IMXR01,
    AXI_IMXR23,
    AXI_TCON,
    AXI_AUD,
    AXI_LNX0,
    AXI_LNX1,
    AXI_LNX2,
    AXI_VD0A,
    AXI_VD0B,
    AXI_VD1A,
    AXI_VD1B,
    AXI_VD2VMCU,
    AXI_VD2B,
    AXI_CPU_CORE,
    AXI_PERI_AXI,
    AXI_PERI_AHB,
    AXI_LZMA,
    AXI_CPU_FAST,
    MAX_AXI_MASTER,
};

struct axi_master_desc
{
    char*    name;
    uint32_t clk;           // MHz 단위

    uint32_t reg_base;

#ifdef REG_ADDR_AUTO_SCAN

#define scan_limiter        0x1
#define scan_port           0x2
#define scan_pend           0x4
#define scan_prio           0x8
#define scan_all            (scan_limiter|scan_port|scan_pend|scan_prio)
#define scan_none           0x0

    uint32_t flag;

#define reg_offset_limiter_tm   0x18
#define reg_offset_limiter_rd   0x78
#define reg_offset_limiter_wr   0x7c
#define reg_offset_port         0xa0
#define reg_offset_pend         0x70
#define reg_offset_prio         0xd0

#endif

    uint32_t reg_tm;        // register address for time parameter
    uint32_t reg_rdbw;      // register address for rd parameter
    uint32_t reg_wrbw;      // register address for wr parameter

    uint32_t reg_port;      // register address for port
    uint32_t reg_pend;      // register address for axi pend parameter

#define PRIO_REG_OFF_CTRL0  0x000
#define PRIO_REG_OFF_CTRL1  0x004
#define PRIO_REG_OFF_CTRL2  0x104

    uint32_t reg_prio;      // register base address for priority
};

struct axi_master_bwlimiter_desc
{
    uint32_t tm;          // nsec 단위. 소숫점 셋째자리까지 묘사. 1500 이면 1.5 us 의미임.
    int32_t rd;           // MB/s 단위. -1 if no bw limit
    int32_t wr;           // MB/s 단위. -1 if no bw limit
};

struct axi_master_pending_desc
{
    int16_t rd;           // 0x1~0x3e, 0 if default pending(0x3f)
    int16_t wr;           // 0x1~0x3e, 0 if default pending(0x3f)
};

struct axi_master_port_desc
{
    struct
    {
        bool en;
        int8_t m0;          // 0~3, -1 if default config
        int8_t m1;          // 0~3, -1 if default config
        int8_t m2;          // 0~3, -1 if default config
    } rd;

    struct
    {
        bool en;
        int8_t m0;          // 0~3, -1 if default config
        int8_t m1;          // 0~3, -1 if default config
        int8_t m2;          // 0~3, -1 if default config
    } wr;
};

struct axi_master_prio_desc
{
    bool en;
    int rd;                 // ~0xf, -1 if default config
    int wr;                 // ~0xf, -1 if default config
};

struct axi_master_perf_desc
{
    enum axi_master master;

#if 0
    uint32_t tm;            // nsec 단위. 소숫점 셋째자리까지 묘사. 1500 이면 1.5 us 의미임.
    int32_t rdbw;           // MB/s 단위. -1 if no bw limit
    int32_t wrbw;           // MB/s 단위. -1 if no bw limit
#endif

    struct axi_master_bwlimiter_desc bwlimit;
    struct axi_master_pending_desc pend;
    struct axi_master_port_desc port;
    struct axi_master_prio_desc prio;
};


struct ddrc_reg_desc
{
#define MAX_DDRC_NUM        2
#define MAX_DDRC_DATA_REGS  4
#define DDRC_EN_REG_VAL     0x1

    uint32_t    en_reg[MAX_DDRC_NUM];           // wr_en registers
    uint32_t    data_reg[MAX_DDRC_DATA_REGS];   // data_reg registers
};

struct ddrc_perf_desc
{
    char*       name;
    char*       desc;
    uint32_t    data[MAX_DDRC_DATA_REGS];
};

struct ddrc_perf_level_mapper
{
    enum bwm_perf_level perf_level;
    enum bwm_ddrc_perf_level ddrc_perf_level;
};

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
struct bwm_chip_drv bwm_o24_chip_config(void);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void bwm_o24_do_init(void);
static void bwm_o24_do_config(struct bwm_ctx* ctx);
static void bwm_o24_do_proc(struct bwm_ctx* ctx, char* command, struct seq_file* m);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/

static struct axi_master_port_desc g_default_port_desc[MAX_AXI_MASTER];
static struct axi_master_prio_desc g_default_prio_desc[MAX_AXI_MASTER];

// from CON_LIMITER sheet of PMT o24.xlxm
// from CON_PORT sheet of PMT o24.xlxm
// from COND_PND_LIMITER sheet of PMT o24.xlxm
// from CON_PRIORITY sheet of PMT o24.xlsm
struct axi_master_desc g_master_desc[MAX_AXI_MASTER] =
{
#ifdef REG_ADDR_AUTO_SCAN

    [    AXI_CPU_M0] = {.name = "CPU_M0",   .clk = 662, .flag = scan_none, .reg_base = 0x0, .reg_tm = 0xCA201804, .reg_rdbw = 0xCA20183C, .reg_wrbw = 0xCA201840, .reg_port = 0x00000000, .reg_pend = 0xCA201838, .reg_prio = 0x00000000},
    [    AXI_CPU_M1] = {.name = "CPU_M1",   .clk = 662, .flag = scan_none, .reg_base = 0x0, .reg_tm = 0xCA201A04, .reg_rdbw = 0xCA201A3C, .reg_wrbw = 0xCA201A40, .reg_port = 0x00000000, .reg_pend = 0xCA201A38, .reg_prio = 0x00000000},

    [      AXI_GPU0] = {.name = "GPU0",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F1000 },
    [      AXI_GPU1] = {.name = "GPU1",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F1200 },
    [       AXI_GFX] = {.name = "GFX",      .clk = 442, .flag = scan_all, .reg_base = 0xC40F1400 },
    [     AXI_LOWBW] = {.name = "LOWBW",    .clk = 442, .flag = scan_all, .reg_base = 0xC40F1600 },
    [    AXI_ICVENC] = {.name = "ICVENC",   .clk = 442, .flag = scan_all, .reg_base = 0xC40F1800 },

    [     AXI_MEFMS] = {.name = "MEFMS",    .clk = 442, .flag = scan_all, .reg_base = 0xC40F1A00 },
    [   AXI_FMGSSR0] = {.name = "FMGSSR0",  .clk = 442, .flag = scan_all, .reg_base = 0xC40F1C00 },
    [   AXI_FMGSSR1] = {.name = "FMGSSR1",  .clk = 442, .flag = scan_all, .reg_base = 0xC40F1E00 },
    [   AXI_FMGSSR2] = {.name = "FMGSSR2",  .clk = 442, .flag = scan_all, .reg_base = 0xC40F2000 },
    [   AXI_FMGSSR3] = {.name = "FMGSSR3",  .clk = 442, .flag = scan_all, .reg_base = 0xC40F2200 },
    [   AXI_FMGSSR4] = {.name = "FMGSSR4",  .clk = 442, .flag = scan_all, .reg_base = 0xC40F2400 },

    [      AXI_CCO0] = {.name = "CCO0",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F2600 },
    [      AXI_CCO1] = {.name = "CCO1",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F2800 },
    [       AXI_ND0] = {.name = "ND0",      .clk = 442, .flag = scan_all, .reg_base = 0xC40F2A00 },
    [       AXI_ND1] = {.name = "ND1",      .clk = 442, .flag = scan_all, .reg_base = 0xC40F2C00 },

    [  AXI_VDOIMXW0] = {.name = "VDOIMXW0", .clk = 442, .flag = scan_all, .reg_base = 0xC40F2E00 },
    [  AXI_VDOIMXW1] = {.name = "VDOIMXW1", .clk = 442, .flag = scan_all, .reg_base = 0xC40F3000 },
    [  AXI_VDOIMXW2] = {.name = "VDOIMXW2", .clk = 442, .flag = scan_all, .reg_base = 0xC40F3200 },
    [  AXI_VDOIMXW3] = {.name = "VDOIMXW3", .clk = 442, .flag = scan_all, .reg_base = 0xC40F3400 },
    [    AXI_IMXR01] = {.name = "IMXR01",   .clk = 442, .flag = scan_all, .reg_base = 0xC40F3600 },
    [    AXI_IMXR23] = {.name = "IMXR23",   .clk = 442, .flag = scan_all, .reg_base = 0xC40F3800 },
    [      AXI_TCON] = {.name = "TCON",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F3A00 },
    [       AXI_AUD] = {.name = "AUD",      .clk = 442, .flag = scan_all, .reg_base = 0xC40F3C00 },
    [      AXI_LNX0] = {.name = "LNX0",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F3E00 },
    [      AXI_LNX1] = {.name = "LNX1",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F4000 },
    [      AXI_LNX2] = {.name = "LNX2",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F4200 },

    [      AXI_VD0A] = {.name = "VD0A",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F4400 },
    [      AXI_VD0B] = {.name = "VD0B",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F4600 },
    [      AXI_VD1A] = {.name = "VD1A",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F4800 },
    [      AXI_VD1B] = {.name = "VD1B",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F4A00 },
    [   AXI_VD2VMCU] = {.name = "VD2VMCU",  .clk = 442, .flag = scan_all, .reg_base = 0xC40F4C00 },
    [      AXI_VD2B] = {.name = "VD2B",     .clk = 442, .flag = scan_all, .reg_base = 0xC40F4E00 },

    [  AXI_CPU_CORE] = {.name = "CPU_CORE", .clk = 662, .flag = scan_limiter | scan_pend | scan_prio, .reg_base = 0xCA201000, .reg_port = 0x00000000 },
    [  AXI_PERI_AXI] = {.name = "PERI_AXI", .clk = 400, .flag = scan_limiter | scan_pend | scan_prio, .reg_base = 0xCA200000, .reg_port = 0x00000000 },
    [  AXI_PERI_AHB] = {.name = "PERI_AHB", .clk = 200, .flag = scan_limiter | scan_pend | scan_prio, .reg_base = 0xCA202000, .reg_port = 0x00000000 },
    [      AXI_LZMA] = {.name = "LZMA",     .clk = 662, .flag = scan_limiter | scan_pend | scan_prio, .reg_base = 0xCA201200, .reg_port = 0x00000000 },
    [  AXI_CPU_FAST] = {.name = "CPU_FAST", .clk = 662, .flag = scan_limiter | scan_pend | scan_prio, .reg_base = 0xCA201400, .reg_port = 0x00000000 },

#else

    [    AXI_CPU_M0] = {.name = "CPU_M0",   .clk = 662, .reg_tm = 0xCA201804, .reg_rdbw = 0xCA20183C, .reg_wrbw = 0xCA201840, .reg_port = 0x00000000, .reg_pend = 0xCA201838, .reg_prio = 0x00000000},
    [    AXI_CPU_M1] = {.name = "CPU_M1",   .clk = 662, .reg_tm = 0xCA201A04, .reg_rdbw = 0xCA201A3C, .reg_wrbw = 0xCA201A40, .reg_port = 0x00000000, .reg_pend = 0xCA201A38, .reg_prio = 0x00000000},

    [      AXI_GPU0] = {.name = "GPU0",     .clk = 442, .reg_tm = 0xC40F1018, .reg_rdbw = 0xC40F1078, .reg_wrbw = 0xC40F107C, .reg_port = 0xC40F10A0, .reg_pend = 0xC40F1070, .reg_prio = 0xC40F10D0},
    [      AXI_GPU1] = {.name = "GPU1",     .clk = 442, .reg_tm = 0xC40F1218, .reg_rdbw = 0xC40F1278, .reg_wrbw = 0xC40F127C, .reg_port = 0xC40F12A0, .reg_pend = 0xC40F1270, .reg_prio = 0xC40F12D0},
    [       AXI_GFX] = {.name = "GFX",      .clk = 442, .reg_tm = 0xC40F1418, .reg_rdbw = 0xC40F1478, .reg_wrbw = 0xC40F147C, .reg_port = 0xC40F14A0, .reg_pend = 0xC40F1470, .reg_prio = 0xC40F14D0},
    [     AXI_LOWBW] = {.name = "LOWBW",    .clk = 442, .reg_tm = 0xC40F1618, .reg_rdbw = 0xC40F1678, .reg_wrbw = 0xC40F167C, .reg_port = 0xC40F16A0, .reg_pend = 0xC40F1670, .reg_prio = 0xC40F16D0},
    [    AXI_ICVENC] = {.name = "ICVENC",   .clk = 442, .reg_tm = 0xC40F1818, .reg_rdbw = 0xC40F1878, .reg_wrbw = 0xC40F187C, .reg_port = 0xC40F18A0, .reg_pend = 0xC40F1870, .reg_prio = 0xC40F18D0},

    [     AXI_MEFMS] = {.name = "MEFMS",    .clk = 442, .reg_tm = 0xC40F1A18, .reg_rdbw = 0xC40F1A78, .reg_wrbw = 0xC40F1A7C, .reg_port = 0xC40F1AA0, .reg_pend = 0xC40F1A70, .reg_prio = 0xC40F1AD0},
    [   AXI_FMGSSR0] = {.name = "FMGSSR0",  .clk = 442, .reg_tm = 0xC40F1C18, .reg_rdbw = 0xC40F1C78, .reg_wrbw = 0xC40F1C7C, .reg_port = 0xC40F1CA0, .reg_pend = 0xC40F1C70, .reg_prio = 0xC40F1CD0},
    [   AXI_FMGSSR1] = {.name = "FMGSSR1",  .clk = 442, .reg_tm = 0xC40F1E18, .reg_rdbw = 0xC40F1E78, .reg_wrbw = 0xC40F1E7C, .reg_port = 0xC40F1EA0, .reg_pend = 0xC40F1E70, .reg_prio = 0xC40F1ED0},
    [   AXI_FMGSSR2] = {.name = "FMGSSR2",  .clk = 442, .reg_tm = 0xC40F2018, .reg_rdbw = 0xC40F2078, .reg_wrbw = 0xC40F207C, .reg_port = 0xC40F20A0, .reg_pend = 0xC40F2070, .reg_prio = 0xC40F20D0},
    [   AXI_FMGSSR3] = {.name = "FMGSSR3",  .clk = 442, .reg_tm = 0xC40F2218, .reg_rdbw = 0xC40F2278, .reg_wrbw = 0xC40F227C, .reg_port = 0xC40F22A0, .reg_pend = 0xC40F2270, .reg_prio = 0xC40F22D0},
    [   AXI_FMGSSR4] = {.name = "FMGSSR4",  .clk = 442, .reg_tm = 0xC40F2418, .reg_rdbw = 0xC40F2478, .reg_wrbw = 0xC40F247C, .reg_port = 0xC40F24A0, .reg_pend = 0xC40F2470, .reg_prio = 0xC40F24D0},

    [      AXI_CCO0] = {.name = "CCO0",     .clk = 442, .reg_tm = 0xC40F2618, .reg_rdbw = 0xC40F2678, .reg_wrbw = 0xC40F267C, .reg_port = 0xC40F26A0, .reg_pend = 0xC40F2670, .reg_prio = 0xC40F26D0},
    [      AXI_CCO1] = {.name = "CCO1",     .clk = 442, .reg_tm = 0xC40F2818, .reg_rdbw = 0xC40F2878, .reg_wrbw = 0xC40F287C, .reg_port = 0xC40F28A0, .reg_pend = 0xC40F2870, .reg_prio = 0xC40F28D0},
    [       AXI_ND0] = {.name = "ND0",      .clk = 442, .reg_tm = 0xC40F2A18, .reg_rdbw = 0xC40F2A78, .reg_wrbw = 0xC40F2A7C, .reg_port = 0xC40F2AA0, .reg_pend = 0xC40F2A70, .reg_prio = 0xC40F2AD0},
    [       AXI_ND1] = {.name = "ND1",      .clk = 442, .reg_tm = 0xC40F2C18, .reg_rdbw = 0xC40F2C78, .reg_wrbw = 0xC40F2C7C, .reg_port = 0xC40F2CA0, .reg_pend = 0xC40F2C70, .reg_prio = 0xC40F2AD0},

    [  AXI_VDOIMXW0] = {.name = "VDOIMXW0", .clk = 442, .reg_tm = 0xC40F2E18, .reg_rdbw = 0xC40F2E78, .reg_wrbw = 0xC40F2E7C, .reg_port = 0xC40F2EA0, .reg_pend = 0xC40F2E70, .reg_prio = 0xC40F2ED0},
    [  AXI_VDOIMXW1] = {.name = "VDOIMXW1", .clk = 442, .reg_tm = 0xC40F3018, .reg_rdbw = 0xC40F3078, .reg_wrbw = 0xC40F307C, .reg_port = 0xC40F30A0, .reg_pend = 0xC40F3070, .reg_prio = 0xC40F30D0},
    [  AXI_VDOIMXW2] = {.name = "VDOIMXW2", .clk = 442, .reg_tm = 0xC40F3218, .reg_rdbw = 0xC40F3278, .reg_wrbw = 0xC40F327C, .reg_port = 0xC40F32A0, .reg_pend = 0xC40F3270, .reg_prio = 0xC40F32D0},
    [  AXI_VDOIMXW3] = {.name = "VDOIMXW3", .clk = 442, .reg_tm = 0xC40F3418, .reg_rdbw = 0xC40F3478, .reg_wrbw = 0xC40F347C, .reg_port = 0xC40F34A0, .reg_pend = 0xC40F3470, .reg_prio = 0xC40F34D0},
    [    AXI_IMXR01] = {.name = "IMXR01",   .clk = 442, .reg_tm = 0xC40F3618, .reg_rdbw = 0xC40F3678, .reg_wrbw = 0xC40F367C, .reg_port = 0xC40F36A0, .reg_pend = 0xC40F3670, .reg_prio = 0xC40F36D0},
    [    AXI_IMXR23] = {.name = "IMXR23",   .clk = 442, .reg_tm = 0xC40F3818, .reg_rdbw = 0xC40F3878, .reg_wrbw = 0xC40F387C, .reg_port = 0xC40F38A0, .reg_pend = 0xC40F3870, .reg_prio = 0xC40F36D0},
    [      AXI_TCON] = {.name = "TCON",     .clk = 442, .reg_tm = 0xC40F3A18, .reg_rdbw = 0xC40F3A78, .reg_wrbw = 0xC40F3A7C, .reg_port = 0xC40F3AA0, .reg_pend = 0xC40F3A70, .reg_prio = 0xC40F3AD0},
    [       AXI_AUD] = {.name = "AUD",      .clk = 442, .reg_tm = 0xC40F3C18, .reg_rdbw = 0xC40F3C78, .reg_wrbw = 0xC40F3C7C, .reg_port = 0xC40F3CA0, .reg_pend = 0xC40F3C70, .reg_prio = 0xC40F3CD0},
    [      AXI_LNX0] = {.name = "LNX0",     .clk = 442, .reg_tm = 0xC40F3E18, .reg_rdbw = 0xC40F3E78, .reg_wrbw = 0xC40F3E7C, .reg_port = 0xC40F3EA0, .reg_pend = 0xC40F3E70, .reg_prio = 0xC40F3ED0},
    [      AXI_LNX1] = {.name = "LNX1",     .clk = 442, .reg_tm = 0xC40F4018, .reg_rdbw = 0xC40F4078, .reg_wrbw = 0xC40F407C, .reg_port = 0xC40F40A0, .reg_pend = 0xC40F4070, .reg_prio = 0xC40F40D0},
    [      AXI_LNX2] = {.name = "LNX2",     .clk = 442, .reg_tm = 0xC40F4218, .reg_rdbw = 0xC40F4278, .reg_wrbw = 0xC40F427C, .reg_port = 0xC40F42A0, .reg_pend = 0xC40F4270, .reg_prio = 0xC40F42D0},

    [      AXI_VD0A] = {.name = "VD0A",     .clk = 442, .reg_tm = 0xC40F4418, .reg_rdbw = 0xC40F4478, .reg_wrbw = 0xC40F447C, .reg_port = 0xC40F44A0, .reg_pend = 0xC40F4470, .reg_prio = 0xC40F44D0},
    [      AXI_VD0B] = {.name = "VD0B",     .clk = 442, .reg_tm = 0xC40F4618, .reg_rdbw = 0xC40F4678, .reg_wrbw = 0xC40F467C, .reg_port = 0xC40F46A0, .reg_pend = 0xC40F4670, .reg_prio = 0xC40F46D0},
    [      AXI_VD1A] = {.name = "VD1A",     .clk = 442, .reg_tm = 0xC40F4818, .reg_rdbw = 0xC40F4878, .reg_wrbw = 0xC40F487C, .reg_port = 0xC40F48A0, .reg_pend = 0xC40F4870, .reg_prio = 0xC40F48D0},
    [      AXI_VD1B] = {.name = "VD1B",     .clk = 442, .reg_tm = 0xC40F4A18, .reg_rdbw = 0xC40F4A78, .reg_wrbw = 0xC40F4A7C, .reg_port = 0xC40F4AA0, .reg_pend = 0xC40F4A70, .reg_prio = 0xC40F4AD0},
    [   AXI_VD2VMCU] = {.name = "VD2VMCU",  .clk = 442, .reg_tm = 0xC40F4C18, .reg_rdbw = 0xC40F4C78, .reg_wrbw = 0xC40F4C7C, .reg_port = 0xC40F4CA0, .reg_pend = 0xC40F4C70, .reg_prio = 0xC40F4CD0},
    [      AXI_VD2B] = {.name = "VD2B",     .clk = 442, .reg_tm = 0xC40F4E18, .reg_rdbw = 0xC40F4E78, .reg_wrbw = 0xC40F4E7C, .reg_port = 0xC40F4EA0, .reg_pend = 0xC40F4E70, .reg_prio = 0xC40F4ED0},

    [  AXI_CPU_CORE] = {.name = "CPU_CORE", .clk = 662, .reg_tm = 0xCA201018, .reg_rdbw = 0xCA201078, .reg_wrbw = 0xCA20107C, .reg_port = 0x00000000, .reg_pend = 0xCA201070, .reg_prio = 0x00000000},
    [  AXI_PERI_AXI] = {.name = "PERI_AXI", .clk = 400, .reg_tm = 0xCA200018, .reg_rdbw = 0xCA200078, .reg_wrbw = 0xCA20007C, .reg_port = 0x00000000, .reg_pend = 0xCA200070, .reg_prio = 0xCA2000D0},
    [  AXI_PERI_AHB] = {.name = "PERI_AHB", .clk = 200, .reg_tm = 0xCA202018, .reg_rdbw = 0xCA202078, .reg_wrbw = 0xCA20207C, .reg_port = 0x00000000, .reg_pend = 0xCA202070, .reg_prio = 0xCA2020D0},
    [      AXI_LZMA] = {.name = "LZMA",     .clk = 662, .reg_tm = 0xCA201218, .reg_rdbw = 0xCA201278, .reg_wrbw = 0xCA20127C, .reg_port = 0x00000000, .reg_pend = 0xCA201270, .reg_prio = 0xCA2012D0},
    [  AXI_CPU_FAST] = {.name = "CPU_FAST", .clk = 662, .reg_tm = 0xCA201418, .reg_rdbw = 0xCA201478, .reg_wrbw = 0xCA20147C, .reg_port = 0x00000000, .reg_pend = 0xCA201470, .reg_prio = 0xCA2014D0},

#endif
};

// see http://clm.lge.com/issue/browse/SICDTV-14317
static struct ddrc_reg_desc g_ddrc_reg_desc =
{
    .en_reg = {
        0xC4D00004, // M0 write enable
        0xC4900004, // M1 write enable
    },

    .data_reg = {
        0xC4D0200C,
        0xC490200C,
        0xC4D02008,
        0xC4902008
    }
};

// O24 performance description
//
// 기본 구조는 아래 bwm_perf_level_default 와 struct axi_master_perf_desc 을 참조할것
//
// master 별로 bw limit, pending, port 3종을 모두 기술해야 한다.
//
// (0) master 명기
//     enum axi_master 참조
//
// (1) bw limit 설정
//     PMT 툴 입려값 time, read bw, write bw 3개의 값을 명기함
//
//     - tm : 원래 단위는 us 이나 정확한 계산을 위하여 ns 값으로 입력함
//            만약 1.5 us 이면, 1500 을 입력할것
//     - rdbw : MB/s 단위로 입력함. -1 입력시 bw limit 해제함
//     - wrbw : MB/s 단위로 입력함. -1 입력시 bw limit 해제함
//
// (2) pending 설정
//
//     - rd : read pending 설정함.  유효값 0x0~0x3e, -1 입력시 pending 해제 조치함
//     - wr : write pending 설정함. 유효값 0x0~0x3e, -1 입력시 pending 해제 조치함
//
//     struct axi_master_pending_desc 참조
//
// (3) port 설정
//
//     port 는 rd, wr 별로 en, m0, m1, m2 설정값을 모두 기입해 줘야 함
//     보통은 m0, m1, m2 은 같은 값 즉 같은 port 로 설정함이 일반적이나, 상황에 따라 예외 있을 수 있음
//
//     - rd.en : read port 설정 변경시 true 설정. port 변경 불가한 master 외에는 항상 true 로 설정할것
//     - rd.m0 : m0 read port 설정값으로 0~3 유효값 설정.
//               만약 -1 입력시 초기 부팅시에 사용된 기본 port 값을 사용한다는 의미로 해석함
//     - rd:m1
//     - rd:m2
//
//     - wr:en : write port 설정 변경시 true 설정. port 변경 불가한 master 외에는 항상 true 로 설정할것
//     - wr.m0 : m0 read port 설정값으로 0~3 유효값 설정.
//               만약 -1 입력시 초기 부팅시에 사용된 기본 port 값을 사용한다는 의미로 해석함
//     - wr:m1
//     - wr:m2
//
//     axi_master_port_desc 참조
//
// 현재 구성된 perf level 의 변경시 DDRC 성능 튜닝값을 변경할 수 있도록 조치함.
//
// (1) perf level 에 종속될 DDRC perf level 의 매핑
//     g_ddrc_perf_level_mapper 참조할것
//
// (2) 각 DDRC perf level 별로 설정값 기술
//     default 값은 boot 에서 초기화하느 설정값을 그대로 읽어서 자동으로 처리함
//     kdriver 에서 변경된 DDRC 의 기본값 재설정시 사용함
//
//     perf level 별로 필요시 DDRC 파라미터를 입수하여 리스트할것
//
//    (노트) ddrc_reg_desc 에는 레지스터 주소값만 명기되어 있으며, 실제 설정값은 ddrc_perf_desc 으로 설정함
//
#define perf_item_max 8
struct axi_master_perf_desc g_perf_desc[bwm_perf_level_max][perf_item_max] =
{
    [bwm_perf_level_default] = {

        // CPU: no bw limiter, no pending, no port change
        { AXI_CPU_M0,   {1500,   -1,   -1}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},
        { AXI_CPU_M1,   {1500,   -1,   -1}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},

        // GPU: no bw limiter, no pending, use default port
        { AXI_GPU0,     {5000, 2000, 2000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_GPU1,     {5000, 2000, 2000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // FMGSSR1: no bw limiter, no pending, use default port
        // FMGSSR3: no bw limiter, no pending, use default port
        { AXI_FMGSSR1,  {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true,  -1, -1, -1}}, {false, -1, -1}},
        { AXI_FMGSSR3,  {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // LOWBW
        { AXI_LOWBW,    {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {true, -1, -1}},
    },

    // see http://clm.lge.com/issue/browse/AVTASK-1434
    // note) bwm_perf_level_low2 settings with CPU0 unlimited BW
    [bwm_perf_level_low1] = {

        // CPU: M0: no bw limiter, M1: 5.0us, rd 1GB/s, wr 1GB/s, no pending, no port change
        { AXI_CPU_M0,   {1500,   -1,   -1}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},
        { AXI_CPU_M1,   {5000, 1000, 1000}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},

        // GPU: 5.0us rd 1GB/s wr 1GB/s, no pending, use default port
        { AXI_GPU0,     {5000, 1000, 1000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_GPU1,     {5000, 1000, 1000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // FMGSSR1: no bw limiter, no pending, port rd.m0=3
        // FMGSSR3: no bw limiter, no pending, use default port
        { AXI_FMGSSR1,  {5000,   -1,   -1}, {-1, -1}, {{ true,  3, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_FMGSSR3,  {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // LOWBW
        { AXI_LOWBW,    {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
    },

    // see http://clm.lge.com/issue/browse/SICDTV-13178
    [bwm_perf_level_low2] = {

        // CPU: 5.0us rd 1GB/s wr 1GB/s, no pending, no port change
        { AXI_CPU_M0,   {5000, 1000, 1000}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},
        { AXI_CPU_M1,   {5000, 1000, 1000}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},

        // GPU: 5.0us rd 1GB/s wr 1GB/s, no pending, use default port
        { AXI_GPU0,     {5000, 1000, 1000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_GPU1,     {5000, 1000, 1000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // FMGSSR1: no bw limiter, no pending, port rd.m0=3
        // FMGSSR3: no bw limiter, no pending, use default port
        { AXI_FMGSSR1,  {5000,   -1,   -1}, {-1, -1}, {{ true,  3, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_FMGSSR3,  {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // LOWBW
        { AXI_LOWBW,    {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
    },

    // see http://clm.lge.com/issue/browse/SICDTV-14175
    [bwm_perf_level_low3] = {

        // CPU: 5.0us rd 1GB/s wr 1GB/s, no pending, no port change
        { AXI_CPU_M0,   {5000, 1000, 1000}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},
        { AXI_CPU_M1,   {5000, 1000, 1000}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},

        // GPU: 5.0us rd 500M/s wr 1000GB/s, no pending, use default port
        { AXI_GPU0,     {5000,  500, 1000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_GPU1,     {5000,  500, 1000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // FMGSSR1: no bw limiter, no pending, port rd.m0=3
        // FMGSSR3: no bw limiter, no pending, port rd.m0=3
        { AXI_FMGSSR1,  {5000,   -1,   -1}, {-1, -1}, {{ true,  3, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_FMGSSR3,  {5000,   -1,   -1}, {-1, -1}, {{ true,  3,  3, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // LOWBW
        { AXI_LOWBW,    {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
    },

    // see http://jira.lge.com/issue/browse/SDOSTD-968
    [bwm_perf_level_low4] = {

        // CPU: no bw limiter, no pending, no port change
        { AXI_CPU_M0,   {1500,   -1,   -1}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},
        { AXI_CPU_M1,   {1500,   -1,   -1}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},

        // GPU: no bw limiter, no pending, use default port
        { AXI_GPU0,     {5000, 2000, 2000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_GPU1,     {5000, 2000, 2000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // FMGSSR1: no bw limiter, no pending, use default port
        // FMGSSR3: no bw limiter, no pending, use default port
        { AXI_FMGSSR1,  {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true,  -1, -1, -1}}, {false, -1, -1}},
        { AXI_FMGSSR3,  {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // LOWBW
        { AXI_LOWBW,    {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {true, -1, -1}},
    },



    // see http://jira.lge.com/issue/browse/SICDTV-14720
    [bwm_perf_level_demod] = {
        // CPU: no bw limiter, no pending, no port change
        { AXI_CPU_M0,   {1500,   -1,   -1}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},
        { AXI_CPU_M1,   {1500,   -1,   -1}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},

        // GPU: no bw limiter, no pending, use default port
        { AXI_GPU0,     {5000, 2000, 2000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_GPU1,     {5000, 2000, 2000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // FMGSSR1: no bw limiter, no pending, use default port
        // FMGSSR3: no bw limiter, no pending, use default port
        { AXI_FMGSSR1,  {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_FMGSSR3,  {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // LOWBW
        { AXI_LOWBW,    {5000,   -1,   -1}, {-1, -1}, {{ true,  3,  3, -1}, { true,  3,  3, -1}}, {false, -1, -1}},
    },

    // see http://jira.lge.com/issue/browse/SICDTV-15664
    // bwm_perf_level_low1 base + GPU0 M0 Write port 2 -> 0
    [bwm_perf_level_8k] = {

        // CPU: M0: no bw limiter, M1: 5.0us, rd 1GB/s, wr 1GB/s, no pending, no port change
        { AXI_CPU_M0,   {1500,   -1,   -1}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},
        { AXI_CPU_M1,   {5000, 1000, 1000}, {-1, -1}, {{false, -1, -1, -1}, {false, -1, -1, -1}}, {false, -1, -1}},

        // GPU: 5.0us rd 1GB/s wr 1GB/s, no pending, use default port
        { AXI_GPU0,     {5000, 1000, 1000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_GPU1,     {5000, 1000, 1000}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // FMGSSR1: no bw limiter, no pending, port rd.m0=3
        // FMGSSR3: no bw limiter, no pending, use default port
        { AXI_FMGSSR1,  {5000,   -1,   -1}, {-1, -1}, {{ true,  3, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
        { AXI_FMGSSR3,  {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},

        // LOWBW
        { AXI_LOWBW,    {5000,   -1,   -1}, {-1, -1}, {{ true, -1, -1, -1}, { true, -1, -1, -1}}, {false, -1, -1}},
    },
};

static struct ddrc_perf_level_mapper g_ddrc_perf_level_mapper[bwm_perf_level_max] =
{
    { bwm_perf_level_default, bwm_ddrc_perf_level_default },
    { bwm_perf_level_low1, bwm_ddrc_perf_level_default },
    { bwm_perf_level_low2, bwm_ddrc_perf_level_default },
    { bwm_perf_level_low3, bwm_ddrc_perf_level_low3 },
    { bwm_perf_level_low4, bwm_ddrc_perf_level_low4 },
    { bwm_perf_level_demod, bwm_ddrc_perf_level_demod },
    { bwm_perf_level_low2, bwm_ddrc_perf_level_default },
};

static struct ddrc_perf_desc g_ddrc_perf_desc[bwm_ddrc_perf_level_max] =
{
    // value arrys is initialized during boot automatically
    [bwm_ddrc_perf_level_default] = {
        .name = "ddrc_level_default",
        .desc = "default DDRC configuration",
        .data = {0x0, 0x0, 0x0, 0x0},
    },

    // * HDMI 165Hz *
    // see http://clm.lge.com/issue/browse/SICDTV-14317 (1st)
    //
    // R:W=2:1, RR=0.75us, Write-urgent < Read_urgent, Hybrid-Starvation-ON
    // D.S ASD:0xC4D00004 %LONG 0x00000001
    // D.S ASD:0xC4900004 %LONG 0x00000001
    // D.S ASD:0xC4D0200C %LONG 0xFF130031
    // D.S ASD:0xC490200C %LONG 0xFF130031
    // D.S ASD:0xC4D02008 %LONG 0x070F0703
    // D.S ASD:0xC4902008 %LONG 0x070F0703
    //
    // see http://clm.lge.com/issue/browse/SICDTV-14175 (2nd)
    //
    // R:W=2:1, RR=3.0us, Write-urgent < Read_urgent(6:3=2:1), Hybrid-Starvation-ON *
    // D.S ASD:0xC4D00004 %LONG 0x00000001
    // D.S ASD:0xC4900004 %LONG 0x00000001
    // D.S ASD:0xC4D0200C %LONG 0xFF130031
    // D.S ASD:0xC490200C %LONG 0xFF130031
    // D.S ASD:0xC4D02008 %LONG 0x1F3F0603 *Normal R:W 3F:1F=2:1(RR=3.0us)
    // D.S ASD:0xC4902008 %LONG 0x1F3F0603 *Normal R:W 3F:1F=2:1(RR=3.0us)
    //
    [bwm_ddrc_perf_level_low3] = {
        .name = "ddrc_level_low3",
        .desc = "R:W=2:1, RR=3.0us, Write-urgent < Read_urgent(6:3=2:1), Hybrid-Starvation-ON ",
        .data  = {
            0xFF130031,
            0xFF130031,
            0x1F3F0603,
            0x1F3F0603
        },
    },

    // * Dolby Vision HDMI *
    // see http://clm.lge.com/issue/browse/SDOSTD-968
    //
    // R:W=2:1, RR=3.0us, Write-urgent < Read_urgent(8:4=2:1), Hybrid-Starvation-ON *
    // D.S ASD:0xC4D00004 %LONG 0x00000001
    // D.S ASD:0xC4900004 %LONG 0x00000001
    // D.S ASD:0xC4D0200C %LONG 0xFF130041
    // D.S ASD:0xC490200C %LONG 0xFF130041
    // D.S ASD:0xC4D02008 %LONG 0x1F3F0804 (Hybrid Starvation : 1F08 -> 0804)
    // D.S ASD:0xC4902008 %LONG 0x1F3F0804 (Hybrid Starvation : 1F08 -> 0804)
    //
    [bwm_ddrc_perf_level_low4] = {
        .name = "ddrc_level_low4",
        .desc = "R:W=2:1, RR=3.0us, Write-urgent < Read_urgent(8:4=2:1), Hybrid-Starvation-ON ",
        .data  = {
            0xFF130041,
            0xFF130041,
            0x1F3F0804,
            0x1F3F0804
        },
    },

    [bwm_ddrc_perf_level_demod] = {
        .name = "ddrc_level_demod",
        .desc = "R:W=2:1, RR=1.5us",
        .data  = {
            -1, // use default value
                -1, // use default value
                0xC4900004,
                0xC4900004,
            },
    },
};


static enum bwm_perf_level g_perf_level = bwm_perf_level_default;
static enum bwm_ddrc_perf_level g_ddrc_perf_level = bwm_ddrc_perf_level_default;

/*========================================================================================
    Implementation Group
========================================================================================*/
static enum bwm_ddrc_perf_level bwm_o24_calc_ddrc_perf_level(enum bwm_perf_level perf_level)
{
    int i;

    if (perf_level < bwm_perf_level_max)
    {
        for (i = 0; i < bwm_perf_level_max; i++)
        {
            if (g_ddrc_perf_level_mapper[i].perf_level == perf_level)
            {
                return g_ddrc_perf_level_mapper[i].ddrc_perf_level;
            }
        }
    }

    SYS_ERROR("can't find ddrc_perf_level for perf_level(%d)\n", perf_level);
    return bwm_ddrc_perf_level_default;
}

static void bwm_o24_detect_default_config(void)
{
    static bool inited = false;

    if (inited) return;

    {
        int i;
        uint32_t regval;

        // read AXI master registers & make default configuration
        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct port_selector_ctrl* port_reg;
            struct priority1_ctrl* prio_reg;
            struct axi_master_desc* master_desc = &g_master_desc[i];

            // make default port configuration
            if (master_desc->reg_port > 0x0)
            {
                OS_RdReg(master_desc->reg_port, &regval);

                port_reg = (struct port_selector_ctrl*)&regval;

                g_default_port_desc[i].rd.en = port_reg->rd_en;
                g_default_port_desc[i].rd.m0 = port_reg->rd_m0;
                g_default_port_desc[i].rd.m1 = port_reg->rd_m1;
                g_default_port_desc[i].rd.m2 = port_reg->rd_m2;
                g_default_port_desc[i].wr.en = port_reg->wr_en;
                g_default_port_desc[i].wr.m0 = port_reg->wr_m0;
                g_default_port_desc[i].wr.m1 = port_reg->wr_m1;
                g_default_port_desc[i].wr.m2 = port_reg->wr_m2;
            }
            else
            {
                g_default_port_desc[i].rd.en = false;
                g_default_port_desc[i].rd.m0 = 0;
                g_default_port_desc[i].rd.m1 = 0;
                g_default_port_desc[i].rd.m2 = 0;
                g_default_port_desc[i].wr.en = false;
                g_default_port_desc[i].wr.m0 = 0;
                g_default_port_desc[i].wr.m1 = 0;
                g_default_port_desc[i].wr.m2 = 0;
            }

            // make default priority configuration
            if (master_desc->reg_prio > 0x0)
            {
                OS_RdReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL1, &regval);
                prio_reg = (struct priority1_ctrl*)&regval;

                g_default_prio_desc[i].en = true; // not used
                g_default_prio_desc[i].wr = prio_reg->rf_uc_m0_main_user_w;
                g_default_prio_desc[i].rd = prio_reg->rf_uc_m0_main_user_r;
            }
            else
            {
                g_default_prio_desc[i].en = false;
                g_default_prio_desc[i].wr = -1;
                g_default_prio_desc[i].rd = -1;
            }
        }

        // make DDRC to be wr_en state
        for (i = 0; i < MAX_DDRC_NUM; i++)
        {
            OS_WrReg(g_ddrc_reg_desc.en_reg[i], DDRC_EN_REG_VAL);
        }

        // read DDRC master registers
        for (i = 0; i < MAX_DDRC_DATA_REGS; i++)
        {
            OS_RdReg(g_ddrc_reg_desc.data_reg[i], &regval);

            g_ddrc_perf_desc[bwm_ddrc_perf_level_default].data[i] = regval;
        }
    }

    inited = true;
}

static int bwm_o24_write_perf_regs(struct axi_master_perf_desc* perf_desc)
{
    uint32_t tm_val;
    uint32_t rdbw_val;
    uint32_t wrbw_val;
    uint32_t port_val;
    uint32_t pend_val;
    uint32_t prio_val0, prio_val1, prio_val2;

    struct port_selector_ctrl* port_reg;
    struct pending_limiter_ctrl* pend_reg;

    struct axi_master_desc* master_desc;
    struct axi_master_port_desc* default_port_desc;
    struct axi_master_prio_desc* default_prio_desc;

    if (!perf_desc)
    {
        SYS_ERROR("invalid param\n");
        return RET_ERROR;
    }

    master_desc = &g_master_desc[perf_desc->master];
    default_port_desc = &g_default_port_desc[perf_desc->master];
    default_prio_desc = &g_default_prio_desc[perf_desc->master];

    // clock freq 480MHz 일 경우
    // Timer 값  10us 로 만들고 싶으면 0x018 번지에    480*10us =  4800 = 0x12C0 입력
    // Read BW 값 3500MB로 하고 싶으면 0x078 번지에   3500*10us =35,000 = 0x88B8 입력
    // Write BW 값 2000MB로 하고 싶으면 0x07C 번지에  2000*10us =20,000 = 0x4E20 입력
    //
    if (perf_desc->bwlimit.tm > 0)
    {
        tm_val = master_desc->clk * perf_desc->bwlimit.tm / 1000;
    }
    else
    {
        SYS_ERROR("zero time value\n");
        return RET_ERROR;
    }

    if (perf_desc->bwlimit.rd < 0)
    {
        rdbw_val = 0x0fffffff;
    }
    else
    {
        rdbw_val = (perf_desc->bwlimit.rd * perf_desc->bwlimit.tm / 1000) & 0x0fffffff;
        rdbw_val |= 0x30000000; // M0 & M1
    }

    if (perf_desc->bwlimit.wr < 0)
    {
        wrbw_val = 0x0fffffff;
    }
    else
    {
        wrbw_val = (perf_desc->bwlimit.wr * perf_desc->bwlimit.tm / 1000) & 0x0fffffff;
        wrbw_val |= 0x30000000; // M0 & M1
    }

    SYS_NOTI("[bwm] axi_master(%d:%8s) bwlimit-config. time=%d.%03dus, rdbw=%04dMB/s, wrbw=%04dMB/s, regval=0x%08x,0x%08x,0x%08x\n",
             perf_desc->master, master_desc->name,
             perf_desc->bwlimit.tm / 1000, perf_desc->bwlimit.tm % 1000,
             perf_desc->bwlimit.rd,
             perf_desc->bwlimit.wr,
             tm_val,
             rdbw_val,
             wrbw_val);

    OS_WrReg(master_desc->reg_tm, tm_val);
    OS_WrReg(master_desc->reg_rdbw, rdbw_val);
    OS_WrReg(master_desc->reg_wrbw, wrbw_val);

    // pending 변경
    // default 값으로 설정해야 하는 경우 0x3f 를 설정하면 됨.
    OS_RdReg(master_desc->reg_pend, &pend_val);

    pend_reg = (struct pending_limiter_ctrl*)&pend_val;

    pend_reg->rd_pend = (perf_desc->pend.rd < 0) ? 0x3f : perf_desc->pend.rd;
    pend_reg->wr_pend = (perf_desc->pend.wr < 0) ? 0x3f : perf_desc->pend.wr;

    SYS_NOTI("[bwm] axi_master(%d:%8s) pending-config. rd=%02d, wr=%02d, regval=0x%08x\n",
             perf_desc->master, master_desc->name,
             perf_desc->pend.rd,
             perf_desc->pend.wr,
             pend_val);

    OS_WrReg(master_desc->reg_pend, pend_val);

    // port 변경.
    // default 값을 가지고 있지 않으므로, perf desc 내에서 잘 기술해 줘야 함
    // port 설정이 -1 이면 이미 확보한 default port 값으로 채우도록 함.
    // register 값이 0x0 인 경우 있으므로, 반드시 register 값이 유효한지 확인 필요함
    if (master_desc->reg_port > 0)
    {
        if (perf_desc->port.rd.en || perf_desc->port.wr.en)
        {
            OS_RdReg(master_desc->reg_port, &port_val);

            port_reg = (struct port_selector_ctrl*)&port_val;

            if (perf_desc->port.rd.en)
            {
                port_reg->rd_en = 1;
                port_reg->rd_m0 = (perf_desc->port.rd.m0 < 0) ? default_port_desc->rd.m0 : perf_desc->port.rd.m0;
                port_reg->rd_m1 = (perf_desc->port.rd.m1 < 0) ? default_port_desc->rd.m1 : perf_desc->port.rd.m1;
                port_reg->rd_m2 = (perf_desc->port.rd.m2 < 0) ? default_port_desc->rd.m2 : perf_desc->port.rd.m2;
            }

            if (perf_desc->port.wr.en)
            {
                port_reg->wr_en = 1;
                port_reg->wr_m0 = (perf_desc->port.wr.m0 < 0) ? default_port_desc->wr.m0 : perf_desc->port.wr.m0;
                port_reg->wr_m1 = (perf_desc->port.wr.m1 < 0) ? default_port_desc->wr.m1 : perf_desc->port.wr.m1;
                port_reg->wr_m2 = (perf_desc->port.wr.m2 < 0) ? default_port_desc->wr.m2 : perf_desc->port.wr.m2;
            }

            SYS_NOTI("[bwm] axi_master(%d:%8s) port-config.    rd.en=%d, port=%d/%d/%d, wr.en=%d, port=%d/%d/%d, regval=0x%08x\n",
                     perf_desc->master, master_desc->name,
                     port_reg->rd_en, port_reg->rd_m0, port_reg->rd_m1, port_reg->rd_m2,
                     port_reg->wr_en, port_reg->wr_m0, port_reg->wr_m1, port_reg->wr_m2,
                     port_val);

            OS_WrReg(master_desc->reg_port, port_val);
        }
    }
    else
    {
        SYS_NOTI("[bwm] axi_master(%d:%8s) port-config. n/a\n", perf_desc->master, master_desc->name);
    }

    // priority 변경
    // prio 설정이 -1 이면 이미 확보한 default prio 값으로 채우도록 함
    // register 값이 0x0 인 경우 있으므로, 반드시 register 값이 유효한지 확인 필요함
    if (master_desc->reg_prio > 0)
    {
        if (perf_desc->prio.en)
        {
            uint32_t wr_val;
            uint32_t rd_val;

            struct priority0_ctrl* prio_ctrl0_reg = (struct priority0_ctrl*)&prio_val0;
            struct priority1_ctrl* prio_ctrl1_reg = (struct priority1_ctrl*)&prio_val1;
            struct priority2_ctrl* prio_ctrl2_reg = (struct priority2_ctrl*)&prio_val2;

            // determine priority
            rd_val = (perf_desc->prio.rd < 0) ? default_prio_desc->rd : perf_desc->prio.rd;
            wr_val = (perf_desc->prio.wr < 0) ? default_prio_desc->wr : perf_desc->prio.wr;

            // enable user mode write
            OS_RdReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL0, &prio_val0);
            prio_ctrl0_reg->rf_uc_user_mode_r = 0x1;
            prio_ctrl0_reg->rf_uc_user_mode_w = 0x1;
            OS_WrReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL0, prio_val0);

            // write read & write priority
            OS_RdReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL1, &prio_val1);
            prio_ctrl1_reg->rf_uc_m0_main_user_r = rd_val;
            prio_ctrl1_reg->rf_uc_m0_main_user_w = wr_val;
            prio_ctrl1_reg->rf_uc_m1_main_user_r = rd_val;
            prio_ctrl1_reg->rf_uc_m1_main_user_w = wr_val;
            OS_WrReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL1, prio_val1);

            OS_RdReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL2, &prio_val2);
            prio_ctrl2_reg->rf_uc_m2_main_user_r = rd_val;
            prio_ctrl2_reg->rf_uc_m2_main_user_w = wr_val;
            OS_WrReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL2, prio_val2);

            SYS_NOTI("[bwm] axi_master(%d:%8s) prio-config.    rd=0x%2x, wr=0x%02x. regval=0x%08x,0x%08x,0x%08x\n",
                     perf_desc->master, master_desc->name,
                     rd_val, wr_val,
                     prio_val0, prio_val1, prio_val2);
        }
    }
    else
    {
        SYS_NOTI("[bwm] axi_master(%d:%8s) prio-config. n/a\n", perf_desc->master, master_desc->name);
    }

    return RET_OK;
}

static int bwm_o24_write_ddrc_perf_regs(struct ddrc_perf_desc* val_desc)
{
    int i;

    if (!val_desc)
    {
        SYS_ERROR("invalid param\n");
        return RET_ERROR;
    }

    // make DDRC to be wr_en state
    for (i = 0; i < MAX_DDRC_NUM; i++)
    {
        SYS_NOTI("[bwm] ddrc en_reg[%d]=0x%08x, val=0x%08x\n",
                 i, g_ddrc_reg_desc.en_reg[i], DDRC_EN_REG_VAL);

        OS_WrReg(g_ddrc_reg_desc.en_reg[i], DDRC_EN_REG_VAL);
    }

    for (i = 0; i < MAX_DDRC_DATA_REGS; i++)
    {

        if (val_desc->data[i] == (UINT32) - 1)
        {
            SYS_NOTI("[bwm] ddrc data_reg[%d]=0x%08x, val=0x%08x (default)\n",
                     i, g_ddrc_reg_desc.data_reg[i], g_ddrc_perf_desc[bwm_ddrc_perf_level_default].data[i]);
            OS_WrReg(g_ddrc_reg_desc.data_reg[i], g_ddrc_perf_desc[bwm_ddrc_perf_level_default].data[i]);
        }
        else
        {
            SYS_NOTI("[bwm] ddrc data_reg[%d]=0x%08x, val=0x%08x\n",
                     i, g_ddrc_reg_desc.data_reg[i], val_desc->data[i]);
            OS_WrReg(g_ddrc_reg_desc.data_reg[i], val_desc->data[i]);
        }
    }

    return RET_OK;
}

static int bwm_o24_write_perf_level(enum bwm_perf_level perf_level)
{
    int i;
    int item_num;
    int ret = RET_ERROR;

    if (perf_level >= bwm_perf_level_max)
    {
        SYS_ERROR("invalid param. bwm_perfl_level=%d\n", perf_level);
        return RET_ERROR;
    }

    // write basic perf values
    item_num = NELEMENTS(g_perf_desc[perf_level]);

    for (i = 0; i < item_num; i++)
    {
        if (RET_OK != bwm_o24_write_perf_regs(&g_perf_desc[perf_level][i]))
        {
            SYS_ERROR("write error during writing axi master. perf_level=%d, idx=%d\n", perf_level, i);
            goto func_exit;
        }
    }

    // write ddrc perf values
    {
        enum bwm_ddrc_perf_level old_ddrc_level = g_ddrc_perf_level;
        enum bwm_ddrc_perf_level new_ddrc_level = bwm_o24_calc_ddrc_perf_level(perf_level);

        if (new_ddrc_level != old_ddrc_level)
        {
            if (RET_OK != bwm_o24_write_ddrc_perf_regs(&g_ddrc_perf_desc[new_ddrc_level]))
            {
                SYS_ERROR("write error during writing ddrc. ddrc_perf_level=%d\n", new_ddrc_level);
                goto func_exit;
            }

            SYS_NOTI("[bwm] ddrc perf level changed %s(%d) -> %s(%d)\n",
                     g_ddrc_perf_desc[old_ddrc_level].name, old_ddrc_level,
                     g_ddrc_perf_desc[new_ddrc_level].name, new_ddrc_level);

            g_ddrc_perf_level = new_ddrc_level;
        }
    }

    ret = RET_OK;
func_exit:
    SYS_NOTI("modify m0.rd =3 , m1.rd =3 (SICDTV-14175, 20240807)");
    return ret;
}

#ifdef REG_ADDR_AUTO_SCAN

// 레지스터 offset 기반으로 register address 를 채운다.
static void bwm_o24_reg_auto_scan(void)
{
    int i;

    for (i = 0; i < MAX_AXI_MASTER; i++)
    {
        struct axi_master_desc* master_desc = &g_master_desc[i];

        if (master_desc->flag & scan_limiter)
        {
            master_desc->reg_tm   = master_desc->reg_base + reg_offset_limiter_tm;
            master_desc->reg_rdbw = master_desc->reg_base + reg_offset_limiter_rd;
            master_desc->reg_wrbw = master_desc->reg_base + reg_offset_limiter_wr;
        }

        if (master_desc->flag & scan_port)
        {
            master_desc->reg_port = master_desc->reg_base + reg_offset_port;
        }

        if (master_desc->flag & scan_pend)
        {
            master_desc->reg_pend = master_desc->reg_base + reg_offset_pend;
        }

        if (master_desc->flag & scan_prio)
        {
            master_desc->reg_prio = master_desc->reg_base + reg_offset_prio;
        }
    }

    SYS_NOTI("[bwm] register table autoscan completed\n");
}
#endif

struct bwm_chip_drv bwm_o24_chip_config(void)
{
    struct bwm_chip_drv chip_drv;

    chip_drv.do_init = bwm_o24_do_init;
    chip_drv.do_config = bwm_o24_do_config;
    chip_drv.do_proc = bwm_o24_do_proc;

#ifdef REG_ADDR_AUTO_SCAN
    bwm_o24_reg_auto_scan();
#endif

    return chip_drv;
}

// O22 기본 설정을 진행한다.
static void bwm_o24_do_init(void)
{
    SYS_NOTI("[bwm] set o24 hw default\n");

    bwm_o24_detect_default_config();

    bwm_o24_write_perf_level(bwm_perf_level_default);

    g_perf_level = bwm_perf_level_default;
    g_ddrc_perf_level = bwm_ddrc_perf_level_default;
}

// 업데이트된 설정에 따라 설정을 업데이트한다.
static void bwm_o24_do_config(struct bwm_ctx* ctx)
{
    enum bwm_perf_level level = bwm_perf_level_default;

    SYS_DEBUG("[bwm] o24 do_config. old perf level=%d\n", g_perf_level);

    // see http://clm.lge.com/issue/browse/SICDTV-15664
    //
    // pqe.input_src: hdmi
    // pqe.input_win: 8k
    if (!strncmp(ctx->pqe.input_src, "hdmi", strlen("hdmi")) &&
            ctx->pqe.input_win.w > 3840 &&
            ctx->pqe.input_win.h > 2160)
    {
        SYS_DEBUG("[bwm] 8K HDMI %dx%d@%dHz nofified. set 8k level\n",
                  ctx->pqe.input_win.w, ctx->pqe.input_win.h, ctx->pqe.input_rate);

        level = bwm_perf_level_8k;
    }

    // see http://clm.lge.com/issue/browse/SICDTV-14175
    //
    // pqe.input_src: hdmi
    // pqe.input_win: 3840x2160
    // pqe.input_rate: 165
    else if (!strncmp(ctx->pqe.input_src, "hdmi444", strlen("hdmi444")) &&
            ctx->pqe.input_win.w >= 3840 &&
            ctx->pqe.input_win.h >= 540 && // 2160 -> 540 (SICDTV-14508)
            ctx->pqe.input_rate > 154)
    {
        SYS_DEBUG("[bwm] 160Hz HDMI444 %dx%d@%dHz nofified. set low3 level\n",
                  ctx->pqe.input_win.w, ctx->pqe.input_win.h, ctx->pqe.input_rate);

        level = bwm_perf_level_low3;
    }
    // see http://clm.lge.com/issue/browse/SDOSTD-381
    //
    // pqe.input_src: hdmi
    // pqe.input_win: 3840x2160
    // pqe.input_rate: 144
    else if (!strncmp(ctx->pqe.input_src, "hdmi444", strlen("hdmi444")) &&
             ctx->pqe.input_win.w >= 3840 &&
             ctx->pqe.input_win.h >= 2160 &&
             ctx->pqe.input_rate > 90)
    {
        SYS_DEBUG("[bwm] HDMI444 %dx%d@%dHz nofified. set low2 level\n",
                  ctx->pqe.input_win.w, ctx->pqe.input_win.h, ctx->pqe.input_rate);

        level = bwm_perf_level_low2;
    }
    // see http://clm.lge.com/issue/browse/AVTASK-1434
    //
    // pqe.input_src: hdmi
    // pqe.input_win: 3840x2160
    // pqe.input_rate: 30, 60 etc
    else if (!strncmp(ctx->pqe.input_src, "hdmi444", strlen("hdmi444")) &&
             ctx->pqe.input_win.w >= 3840 &&
             ctx->pqe.input_win.h >= 2160)
    {
        SYS_DEBUG("[bwm] HDMI444 %dx%d@%dHz nofified. set low1 level\n",
                  ctx->pqe.input_win.w, ctx->pqe.input_win.h, ctx->pqe.input_rate);

        level = bwm_perf_level_low1;
    }
    else if (!strncmp(ctx->pqe.input_src, "hdmi", strlen("hdmi")) &&
             !strncmp(ctx->pqe.hdr_type, "dolby", strlen("dolby")))
    {
        SYS_DEBUG("[bwm] Dolby HDMI (input_src:%s, hdr_type:%s) nofified. set low4 level\n",
                  ctx->pqe.input_src, ctx->pqe.hdr_type);

        level = bwm_perf_level_low4;
    }
    // see http://jira.lge.com/issue/browse/SICDTV-14720
    else if (!strncmp(ctx->pqe.input_src, "vdec", strlen("vdec")) &&
             !strncmp(ctx->demod.tune, "atsc3", strlen("atsc3")))
    {
        SYS_DEBUG("[bwm] ATSC3 nofified. set demod level\n");

        level = bwm_perf_level_demod;
    }

    if (g_perf_level != level)
    {
        bwm_o24_write_perf_level(level);

        SYS_NOTI("[bwm] perf level changed: %d -> %d\n", g_perf_level, level);

        g_perf_level = level;
    }

    SYS_DEBUG("[bwm] o24 do_config completed. new perf level=%d\n", g_perf_level);
}

// O22 칩 상태를 출력한다. 등등
static void bwm_o24_do_proc(struct bwm_ctx* ctx, char* command, struct seq_file* m)
{
    int i, j;
    uint32_t regval_tm, regval_rdbw, regval_wrbw;
    uint32_t regval_port, regval_pend, regval_ddrc;
    uint32_t regval_prio0, regval_prio1, regval_prio2;

    int curr_perf_cnt = NELEMENTS(g_perf_desc[g_perf_level]);

    if (!strncmp(command, "status", strlen("status")))
    {
        seq_printf(m, "+ hwm_perf_level: %d.\n", g_perf_level);
        seq_printf(m, "+ hwm_ddrc_perf_level: %d (%s)\n",
                   g_ddrc_perf_level, g_ddrc_perf_desc[g_ddrc_perf_level].name);

        seq_printf(m, "+ current perf status\n");

        // 현재 설정된 perf 상태를 출력한다.
        for (i = 0; i < curr_perf_cnt; i++)
        {
            struct axi_master_perf_desc* perf_desc = &g_perf_desc[g_perf_level][i];
            struct axi_master_desc* master_desc = &g_master_desc[perf_desc->master];

            OS_RdReg(master_desc->reg_tm, &regval_tm);
            OS_RdReg(master_desc->reg_rdbw, &regval_rdbw);
            OS_RdReg(master_desc->reg_wrbw, &regval_wrbw);
            OS_RdReg(master_desc->reg_pend, &regval_pend);

            if (master_desc->reg_port > 0)
            {
                OS_RdReg(master_desc->reg_port, &regval_port);
            }
            else
            {
                regval_port = 0x0;
            }

            if (master_desc->reg_prio > 0)
            {
                OS_RdReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL0, &regval_prio0);
                OS_RdReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL1, &regval_prio1);
                OS_RdReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL2, &regval_prio2);
            }
            else
            {
                regval_prio0 = 0x0;
                regval_prio1 = 0x0;
                regval_prio2 = 0x0;
            }

            seq_printf(m, "%12s limiter(time=%d.%03dus, rdbw=%04dMB/s, wrbw=%04dMB/s), "
                       "pend(rd=%02d, wr=%02d), "
                       "port(rd=%s,%d/%d/%d, wr=%s,%d/%d/%d) "
                       "prio(%s,%d,%d) \n",
                       master_desc->name,
                       perf_desc->bwlimit.tm / 1000, perf_desc->bwlimit.tm % 1000,
                       perf_desc->bwlimit.rd,
                       perf_desc->bwlimit.wr,
                       perf_desc->pend.rd,
                       perf_desc->pend.wr,
                       perf_desc->port.rd.en ? "enable" : "disable",
                       perf_desc->port.rd.m0,
                       perf_desc->port.rd.m1,
                       perf_desc->port.rd.m2,
                       perf_desc->port.wr.en ? "enable" : "disable",
                       perf_desc->port.wr.m0,
                       perf_desc->port.wr.m1,
                       perf_desc->port.wr.m2,
                       perf_desc->prio.en ? "enable" : "disable",
                       perf_desc->prio.rd,
                       perf_desc->prio.wr);

            seq_printf(m, "%12s regval:limiter(0x%08x,0x%08x,0x%08x), pend(0x%08x), port(0x%08x), prio(0x%08x,0x%08x,0x%08x)\n",
                       "",
                       regval_tm,
                       regval_rdbw,
                       regval_wrbw,
                       regval_pend,
                       regval_port,
                       regval_prio0,
                       regval_prio1,
                       regval_prio2);
        }

        // 현재 port 설정을 덤프한다.
        seq_printf(m, "\n");
        seq_printf(m, "+ current port HW status\n");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct port_selector_ctrl* port_reg;
            struct axi_master_desc* master_desc = &g_master_desc[i];

            if (master_desc->reg_port > 0x0)
            {
                OS_RdReg(master_desc->reg_port, &regval_port);

                port_reg = (struct port_selector_ctrl*)&regval_port;

                seq_printf(m, "%12s regval=0x%08x. rd.en=%d, port=%d/%d/%d, wr.en=%d, port=%d/%d/%d\n",
                           master_desc->name,
                           regval_port,
                           port_reg->rd_en,
                           port_reg->rd_m0,
                           port_reg->rd_m1,
                           port_reg->rd_m2,
                           port_reg->wr_en,
                           port_reg->wr_m0,
                           port_reg->wr_m1,
                           port_reg->wr_m2);
            }
        }

        // 현재 priority 설정을 덤프한다.
        seq_printf(m, "\n");
        seq_printf(m, "+ current priority HW status\n");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct priority0_ctrl* prio0_reg = (struct priority0_ctrl*)&regval_prio0;
            struct priority1_ctrl* prio1_reg = (struct priority1_ctrl*)&regval_prio1;
            struct priority2_ctrl* prio2_reg = (struct priority2_ctrl*)&regval_prio2;

            struct axi_master_desc* master_desc = &g_master_desc[i];

            if (master_desc->reg_prio > 0x0)
            {
                OS_RdReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL0, &regval_prio0);
                OS_RdReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL1, &regval_prio1);
                OS_RdReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL2, &regval_prio2);

                seq_printf(m, "%12s regval=0x%08x,0x%08x,0x%08x. user_mode=%d,%d rd_prio=%02x,%02x,%02x, wr_prio=%02x,%02x,%02x\n",
                           master_desc->name,
                           regval_prio0,
                           regval_prio1,
                           regval_prio2,
                           prio0_reg->rf_uc_user_mode_r,
                           prio0_reg->rf_uc_user_mode_w,
                           prio1_reg->rf_uc_m0_main_user_r,
                           prio1_reg->rf_uc_m1_main_user_r,
                           prio2_reg->rf_uc_m2_main_user_r,
                           prio1_reg->rf_uc_m0_main_user_w,
                           prio1_reg->rf_uc_m1_main_user_w,
                           prio2_reg->rf_uc_m2_main_user_w);
            }
            else
            {
                seq_printf(m, "%12s N/A\n", master_desc->name);
            }
        }

        // 현재 pending 설정을 덤프한다.
        seq_printf(m, "\n");
        seq_printf(m, "+ current pending HW status\n");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct pending_limiter_ctrl* pend_regs;
            struct axi_master_desc* master_desc = &g_master_desc[i];

            if (master_desc->reg_pend > 0x0)
            {
                OS_RdReg(master_desc->reg_pend, &regval_pend);

                pend_regs = (struct pending_limiter_ctrl*)&regval_pend;

                seq_printf(m, "%12s regval=0x%08x. rd.pend=0x%02x, wr.pend=0x%02x\n",
                           master_desc->name,
                           regval_pend,
                           pend_regs->rd_pend,
                           pend_regs->wr_pend);
            }
        }

        // 현재 DDRC 설정을 덤프한다.
        seq_printf(m, "\n");
        seq_printf(m, "+ current DDRC perf HW status\n");

        for (i = 0;  i < MAX_DDRC_NUM; i++)
        {
            OS_RdReg(g_ddrc_reg_desc.en_reg[i], &regval_ddrc);

            seq_printf(m, "%12s ddrc.en_reg[%d]=0x%08x\n", " ", i, regval_ddrc);
        }

        for (i = 0;  i < MAX_DDRC_DATA_REGS; i++)
        {
            OS_RdReg(g_ddrc_reg_desc.data_reg[i], &regval_ddrc);

            seq_printf(m, "%12s ddrc.data_reg[%d]=0x%08x\n", " ", i, regval_ddrc);
        }

        // axi master 값을 덤프한다.
        seq_printf(m, "\n");
        seq_printf(m, "\n");
        seq_printf(m, "+ AXI master table regs description\n");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct axi_master_desc* master_desc = &g_master_desc[i];

            seq_printf(m,
                       "%12s, reg_base=0x%08x, clk=%3dMHz, bwtm=0x%08x, bwrd=0x%08x, bwrd=0x%08x, port=0x%08x, pend=0x%08x, prio=0x%08x\n",
                       master_desc->name,
                       master_desc->reg_base,
                       master_desc->clk,
                       master_desc->reg_tm,
                       master_desc->reg_rdbw,
                       master_desc->reg_wrbw,
                       master_desc->reg_port,
                       master_desc->reg_pend,
                       master_desc->reg_prio);
        }

        seq_printf(m, "\n");
        seq_printf(m, "+ DDRC regs table description\n");

        for (i = 0; i < MAX_DDRC_DATA_REGS; i++)
        {
            seq_printf(m, "%12s 0x%08x\n", " ", g_ddrc_reg_desc.data_reg[i]);
        }

        // perf 값을 덤프한다.
        seq_printf(m, "\n");
        seq_printf(m, "+ AXI perf level table description\n");

        for (j = 0; j < bwm_perf_level_max; j++)
        {
            int cnt = NELEMENTS(g_perf_desc[j]);

            seq_printf(m, "+ perf level[%d]\n", j);

            for (i = 0; i < cnt; i++)
            {
                struct axi_master_perf_desc* perf_desc = &g_perf_desc[j][i];
                struct axi_master_desc* master_desc = &g_master_desc[perf_desc->master];

                seq_printf(m,
                           "%12s, limit(tm=%d.%03dus, rd=%04dMB/s, wr=%04dMB/s) pend(rd=%02d, wr=%02d), port(rd=%7s,%2d,%2d,%2d), wr=%7s,%2d,%2d,%2d) prio=(%7s,%2d,%2d)\n",
                           master_desc->name,
                           perf_desc->bwlimit.tm / 1000, perf_desc->bwlimit.tm % 1000,
                           perf_desc->bwlimit.rd,
                           perf_desc->bwlimit.wr,
                           perf_desc->pend.rd,
                           perf_desc->pend.wr,
                           perf_desc->port.rd.en ? "enable" : "disable",
                           perf_desc->port.rd.m0,
                           perf_desc->port.rd.m1,
                           perf_desc->port.rd.m2,
                           perf_desc->port.wr.en ? "enable" : "disable",
                           perf_desc->port.wr.m0,
                           perf_desc->port.wr.m1,
                           perf_desc->port.wr.m2,
                           perf_desc->prio.en ? "enable" : "disable",
                           perf_desc->prio.rd,
                           perf_desc->prio.wr);
            }
        }

        seq_printf(m, "\n");
        seq_printf(m, "+ DDRC perf level table description\n");

        for (j = 0; j < bwm_ddrc_perf_level_max; j++)
        {
            struct ddrc_perf_desc* val_desc = &g_ddrc_perf_desc[j];

            seq_printf(m, "+ perf level[%s]\n", val_desc->name);
            seq_printf(m, "%12s %s\n", "desc:", val_desc->desc);

            for (i = 0; i < MAX_DDRC_DATA_REGS; i++)
            {
                seq_printf(m, "%12s 0x%08x\n", " ", val_desc->data[i]);
            }
        }

        // 기본 port 구성을 덤프한다.
        seq_printf(m, "\n");
        seq_printf(m, "+ default port HW status\n");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct axi_master_desc* master_desc = &g_master_desc[i];
            struct axi_master_port_desc* port_desc = &g_default_port_desc[i];

            seq_printf(m, "%12s rd.en=%d, port=%d/%d/%d, wr.en=%d, port=%d/%d/%d\n",
                       master_desc->name,
                       port_desc->rd.en,
                       port_desc->rd.m0,
                       port_desc->rd.m1,
                       port_desc->rd.m2,
                       port_desc->wr.en,
                       port_desc->wr.m0,
                       port_desc->wr.m1,
                       port_desc->wr.m2);
        }

        // 기본 prio 구성을 덤프한다.
        seq_printf(m, "\n");
        seq_printf(m, "+ default priority HW status\n");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct axi_master_desc* master_desc = &g_master_desc[i];
            struct axi_master_prio_desc* prio_desc = &g_default_prio_desc[i];

            if (master_desc->reg_prio > 0)
            {
                seq_printf(m, "%12s user_mode=%d, rd=0x%02x, wr=0x%02x\n",
                           master_desc->name,
                           prio_desc->en,
                           prio_desc->rd,
                           prio_desc->wr);
            }
            else
            {
                seq_printf(m, "%12s N/A\n", master_desc->name);
            }
        }

    }
}

