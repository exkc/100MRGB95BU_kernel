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
#undef  SUPPORT_DEBUG
#undef  SUPPORT_PENDING
#undef  SUPPORT_PRIORITY

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
#ifdef SUPPORT_DEBUG
#define REG_READ(addr,pval)        do { \
                                    SYS_DEBUG("bwm reg_read 0x%08x @%s:%d\n", addr, __FUNCTION__, __LINE__); \
                                    OS_RdReg(addr,pval); \
                                } while(0)

#define REG_WRITE(addr,val)        do { \
                                    SYS_DEBUG("bwm reg_write 0x%08x=0x%08x @%s:%d\n", addr, val, __FUNCTION__, __LINE__); \
                                    OS_WrReg(addr,val); \
                                } while(0)
#else
#define REG_READ(addr,pval)        OS_RdReg(addr,pval)
#define REG_WRITE(addr,val)        OS_WrReg(addr,val)
#endif

#define IS_MASTER_INVALID(m)    m >= AXI_NONE

/*----------------------------------------------------------------------------------------
    Type Definitions (register manual)
----------------------------------------------------------------------------------------*/
/* astyle: off */
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
    uint32_t rf_uc_nbudget_cmd_w : 7,    //  0: 6
             : 1,    //     7 reserved
             rf_uc_user_qos_sel_w  : 1,    //     8
             : 3,    //  9:11 reserved
             rf_uc_user_mode_w     : 3,    // 12:14
             : 1,    //    15 reserved
             rf_uc_nbudget_cmd_r   : 7,    // 16:22
             : 1,    //    23 reserved
             rf_uc_user_qos_sel_r  : 1,    //    24
             : 3,    // 25:27 reserved
             rf_uc_user_mode_r     : 3;    // 28:30
};

struct priority1_ctrl
{
    uint32_t rf_uc_m1_sub_user_w  : 4,    //  0: 3
             rf_uc_m1_main_user_w : 4,    //  4: 7
             rf_uc_m0_sub_user_w  : 4,    //  8:11
             rf_uc_m0_main_user_w : 4,    // 12:15
             rf_uc_m1_sub_user_r  : 4,    // 16:19
             rf_uc_m1_main_user_r : 4,    // 20:23
             rf_uc_m0_sub_user_r  : 4,    // 24:27
             rf_uc_m0_main_user_r : 4;    // 28:31
};
/* astyle: on */

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
// perf_level 의 기준은 없으나, 설정이 약한 것을 낮은 숫자로 배치해 줄것.
// 기존처럼 pef_level_low1, low2 이런식으로 숫자로 명기하지 말고 명확한 씬을 이름으로 사용할것
enum bwm_perf_level
{
    bwm_perf_level_default = 0, // default 설정
    bwm_perf_level_hdmi444_hfr,   // 144Hz, 165Hz hdmi444 특화 설정

    bwm_perf_level_max,
};

enum axi_master
{
    AXI_CPU_M0,
    AXI_CPU_M1,
    AXI_GPU0,
    AXI_GPU1,
    AXI_GFX,
    AXI_LOWBW,
    AXI_TIVVMCU,
    AXI_ME3X1,
    AXI_FMC0,
    AXI_FMC1,
    AXI_FMC2,
    AXI_FMC3,
    AXI_FMS,
    AXI_SRE0,
    AXI_SRE1CCO,
    AXI_ND0,
    AXI_ND1,
    AXI_IMX0,
    AXI_IMX1,
    AXI_IMX2,
    AXI_IMX3,
    AXI_VDO0,
    AXI_VDO1,
    AXI_GSC0,
    AXI_GSC1,
    AXI_GSC2,
    AXI_GSC3,
    AXI_AUD,
    AXI_NPPTCU,
    AXI_LNX0,
    AXI_LNX1,
    AXI_LNX2,
    AXI_VD0A,
    AXI_VD0B,
    AXI_VD1A,
    AXI_VD1B,

    AXI_CPU_CORE,
    AXI_PERI_AXI,
    AXI_PERI_AHB,
    AXI_LZMA,
    AXI_CPU_FAST,

    MAX_AXI_MASTER,

    AXI_NONE = MAX_AXI_MASTER,
};

struct axi_master_desc
{
    char*    name;
    uint32_t clk;           // MHz 단위

    uint32_t reg_base;

#define flag_limiter        0x1
#define flag_port            0x2
#define flag_pend           0x4
#define flag_prio           0x8
#define flag_all            (flag_limiter|flag_port|flag_pend|flag_prio)
#define flag_none           0x0

    uint32_t flag;

#define reg_offset_limiter_tm   0x18
#define reg_offset_limiter_rd   0x78
#define reg_offset_limiter_wr   0x7c
#define reg_offset_port         0xa0
#define reg_offset_pend         0x70
#define reg_offset_prio         0xd0

    uint32_t reg_bw_tm;      // base register address for time parameter
    uint32_t reg_bw_rd;      // base register address for rd parameter
    uint32_t reg_bw_wr;      // base register address for wr parameter

    uint32_t reg_port;      // base register address for port

    uint32_t reg_pend;      // base register address for axi pend parameter

#define PRIO_REG_OFF_CTRL0  0x000
#define PRIO_REG_OFF_CTRL1  0x004
    uint32_t reg_prio;      // register base address for priority
};

// see http://jira.lge.com/issue/browse/SICDTV-15723
// 0x0 : disable register write
// xxx : RR , Read & Write urgent etc
struct ddrc_reg_desc
{
#define DDRC_NUM            2    // en/disable 제어 목적
#define DDRC_CTRL_REGS_NUM  6    // 세부 설정용
#define DDRC_CTRL_EN_VAL    0x1  // 0x0 : disable, 0x1: enable

    uint32_t    en_reg[DDRC_NUM];               // wr_en registers
    uint32_t    data_reg[DDRC_CTRL_REGS_NUM];   // data_reg registers
};


struct axi_master_bwlimiter_desc
{
    uint32_t tm;          // nsec 단위. 소숫점 셋째자리까지 묘사. 1500 이면 1.5 us 의미임.
    int32_t  rd;          // MB/s 단위. -1 if no bw limit
    int32_t  wr;          // MB/s 단위. -1 if no bw limit
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
        bool   en;
        int8_t m0;          // 0~3, -1 if default config
        int8_t m1;          // 0~3, -1 if default config
    } rd;

    struct
    {
        bool   en;
        int8_t m0;          // 0~3, -1 if default config
        int8_t m1;          // 0~3, -1 if default config
    } wr;
};

struct axi_master_prio_desc
{
    bool en;
    int  rd;                // ~0xf, -1 if default config
    int  wr;                // ~0xf, -1 if default config
};

// AXI 와 DDRC performacne 그룹 정의
// 그룹별 성능 지시자는 struct bwm_perf_desc 로 표현함
struct axi_master_perf_desc
{
    enum axi_master master;

    struct axi_master_bwlimiter_desc bwlimit;
    struct axi_master_port_desc port;

    struct axi_master_pending_desc pend;
    struct axi_master_prio_desc prio;
};

struct ddrc_perf_desc
{
    uint32_t  data[DDRC_CTRL_REGS_NUM];
};

#define perf_item_max 12    // just large buffer
struct bwm_perf_desc
{
    char* text;
    struct axi_master_perf_desc  axi_perf[perf_item_max];
    struct ddrc_perf_desc        ddrc_perf;
};

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
struct bwm_chip_drv bwm_o26_chip_config(void);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void bwm_o26_do_init(void);
static void bwm_o26_do_config(struct bwm_ctx* ctx);
static void bwm_o26_do_proc(struct bwm_ctx* ctx, char* command, struct seq_file* m);

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static struct axi_master_port_desc g_default_port_desc[MAX_AXI_MASTER];
static struct axi_master_prio_desc g_default_prio_desc[MAX_AXI_MASTER];
static struct axi_master_pending_desc g_default_pend_desc[MAX_AXI_MASTER];
static struct ddrc_perf_desc g_default_ddrc_desc;

// from CON_LIMITER sheet of PMT o26.xlxm
// from CON_PORT sheet of PMT o26.xlxm
// from COND_PND_LIMITER sheet of PMT o26.xlxm
// from CON_PRIORITY sheet of PMT o26.xlsm
static struct axi_master_desc g_master_desc[MAX_AXI_MASTER] =
{
    [  AXI_CPU_M0] = {.name = "CPU_M0",    .clk = 662, .reg_base = 0xCA202C00, .flag = flag_none, .reg_bw_tm = 0xCA202C04, .reg_bw_rd = 0xCA202C3C, .reg_bw_wr = 0xCA202C40, .reg_port = 0x0, .reg_pend = 0xCA202C38, .reg_prio = 0x0},
    [  AXI_CPU_M1] = {.name = "CPU_M1",    .clk = 662, .reg_base = 0xCA203000, .flag = flag_none, .reg_bw_tm = 0xCA203004, .reg_bw_rd = 0xCA20303C, .reg_bw_wr = 0xCA203040, .reg_port = 0x0, .reg_pend = 0xCA203038, .reg_prio = 0x0},

    [    AXI_GPU0] = {.name = "GPU0",      .clk = 480, .reg_base = 0xC4208400, .flag = flag_all },
    [    AXI_GPU1] = {.name = "GPU1",      .clk = 480, .reg_base = 0xC4208800, .flag = flag_all },
    [     AXI_GFX] = {.name = "GFX",       .clk = 480, .reg_base = 0xC4210400, .flag = flag_all },
    [   AXI_LOWBW] = {.name = "LOWBW",     .clk = 480, .reg_base = 0xC4208C00, .flag = flag_all },
    [ AXI_TIVVMCU] = {.name = "TIVVMCU",   .clk = 480, .reg_base = 0xC4210800, .flag = flag_all },
    [   AXI_ME3X1] = {.name = "ME3X1",     .clk = 480, .reg_base = 0xC4200400, .flag = flag_all },
    [    AXI_FMC0] = {.name = "FMC0",      .clk = 480, .reg_base = 0xC4200800, .flag = flag_all },
    [    AXI_FMC1] = {.name = "FMC1",      .clk = 480, .reg_base = 0xC4200C00, .flag = flag_all },
    [    AXI_FMC2] = {.name = "FMC2",      .clk = 480, .reg_base = 0xC4201000, .flag = flag_all },
    [    AXI_FMC3] = {.name = "FMC3",      .clk = 480, .reg_base = 0xC4201400, .flag = flag_all },
    [     AXI_FMS] = {.name = "FMS",       .clk = 480, .reg_base = 0xC4209000, .flag = flag_all },
    [    AXI_SRE0] = {.name = "SRE0",      .clk = 480, .reg_base = 0xC4201800, .flag = flag_all },
    [ AXI_SRE1CCO] = {.name = "SRE1CCO",   .clk = 480, .reg_base = 0xC4201C00, .flag = flag_all },
    [     AXI_ND0] = {.name = "ND0",       .clk = 480, .reg_base = 0xC4209400, .flag = flag_all },
    [     AXI_ND1] = {.name = "ND1",       .clk = 480, .reg_base = 0xC4209800, .flag = flag_all },
    [    AXI_IMX0] = {.name = "IMX0",      .clk = 480, .reg_base = 0xC4209C00, .flag = flag_all },
    [    AXI_IMX1] = {.name = "IMX1",      .clk = 480, .reg_base = 0xC420A000, .flag = flag_all },
    [    AXI_IMX2] = {.name = "IMX2",      .clk = 480, .reg_base = 0xC420A400, .flag = flag_all },
    [    AXI_IMX3] = {.name = "IMX3",      .clk = 480, .reg_base = 0xC420A800, .flag = flag_all },
    [    AXI_VDO0] = {.name = "VDO0",      .clk = 480, .reg_base = 0xC420AC00, .flag = flag_all },
    [    AXI_VDO1] = {.name = "VDO1",      .clk = 480, .reg_base = 0xC420B000, .flag = flag_all },
    [    AXI_GSC0] = {.name = "GSC0",      .clk = 480, .reg_base = 0xC4202000, .flag = flag_all },
    [    AXI_GSC1] = {.name = "GSC1",      .clk = 480, .reg_base = 0xC4202400, .flag = flag_all },
    [    AXI_GSC2] = {.name = "GSC2",      .clk = 480, .reg_base = 0xC4202800, .flag = flag_all },
    [    AXI_GSC3] = {.name = "GSC3",      .clk = 480, .reg_base = 0xC4202C00, .flag = flag_all },
    [     AXI_AUD] = {.name = "AUD",       .clk = 480, .reg_base = 0xC4210C00, .flag = flag_all },
    [  AXI_NPPTCU] = {.name = "NPPTCU",    .clk = 480, .reg_base = 0xC4211000, .flag = flag_all },
    [    AXI_LNX0] = {.name = "LNX0",      .clk = 480, .reg_base = 0xC4211400, .flag = flag_all },
    [    AXI_LNX1] = {.name = "LNX1",      .clk = 480, .reg_base = 0xC4211800, .flag = flag_all },
    [    AXI_LNX2] = {.name = "LNX2",      .clk = 480, .reg_base = 0xC4211C00, .flag = flag_all },
    [    AXI_VD0A] = {.name = "VD0A",      .clk = 480, .reg_base = 0xC4212000, .flag = flag_all },
    [    AXI_VD0B] = {.name = "VD0B",      .clk = 480, .reg_base = 0xC4212400, .flag = flag_all },
    [    AXI_VD1A] = {.name = "VD1A",      .clk = 480, .reg_base = 0xC4212800, .flag = flag_all },
    [    AXI_VD1B] = {.name = "VD1B",      .clk = 480, .reg_base = 0xC4212C00, .flag = flag_all },

    [AXI_CPU_CORE] = {.name = "CPU_CORE",  .clk = 662, .reg_base = 0xCA202000, .flag = (flag_all & ~flag_port) },
    [AXI_PERI_AXI] = {.name = "PERI_AXI",  .clk = 400, .reg_base = 0xCA200000, .flag = (flag_all & ~flag_port) },
    [AXI_PERI_AHB] = {.name = "PERI_AHB",  .clk = 200, .reg_base = 0xCA204000, .flag = (flag_all & ~flag_port) },
    [    AXI_LZMA] = {.name = "LZMA",      .clk = 662, .reg_base = 0xCA202400, .flag = (flag_all & ~flag_port) },
    [AXI_CPU_FAST] = {.name = "CPU_FAST",  .clk = 662, .reg_base = 0xCA202800, .flag = (flag_all & ~flag_port) },
};

// see http://jira.lge.com/issue/browse/SICDTV-15723, taejun.kang comment - 2025/05/22 14:49
static struct ddrc_reg_desc g_ddrc_reg_desc =
{
    .en_reg = {
        0xC4D00004, // M0 write enable
        0xC4900004, // M1 write enable
    },

    .data_reg = {
        0xC4D0200C, // M0 rw starvation
        0xC490200C, // M1 rw starvation
        0xC4D02008, // M0 hybrid starvation
        0xC4902008, // M1 hybrid starvation
        0xC4901420, // M0 real time port
        0xC4D01420, // M1 real time port
    },
};

// performance description
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
//
// (2) port 설정
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
//
//     axi_master_port_desc 참조
//
// (3) pending 설정 (O26 에서는 사용전까지  미지원)
//
//     - rd : read pending 설정함.  유효값 0x0~0x3e, -1 입력시 pending 해제 조치함
//     - wr : write pending 설정함. 유효값 0x0~0x3e, -1 입력시 pending 해제 조치함
//
//     struct axi_master_pending_desc 참조
//
// (4) priority 설정 (O26 에서는 사용전까지  미지원)
//
//     TBD
//
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
static struct bwm_perf_desc g_bwm_perf_desc[bwm_perf_level_max] =
{
    // CPU, GPU no blw limit, no port change
    //
    // default 의 ddrc_perf 데이터는 초기화시에 읽힌 값으로 초기화된다.
    // DDRC config = STV-R:W=2:1, RR=3.0us, UGT-R:W=2:1, Write-urgent < Read_urgent, Hybrid-Starvation-ON
    // (O24 CKR=1:2 대비 O26 CKR=1:4에서 설정값은 다를 수 있음)
    [bwm_perf_level_default] = {

        .text = "default config. no bwlimit, no port change",

        .axi_perf = {
            // master,      bwlimit rd/wr       port rd m0/m1     port wr m0/m1
            { AXI_CPU_M0,   {1500,   -1,   -1}, {{false, -1, -1}, {false, -1, -1}} },
            { AXI_CPU_M1,   {1500,   -1,   -1}, {{false, -1, -1}, {false, -1, -1}} },
            { AXI_GPU0,     {5000,   -1,   -1}, {{ true, -1, -1}, { true, -1, -1}} },
            { AXI_GPU1,     {5000,   -1,   -1}, {{ true, -1, -1}, { true, -1, -1}} },
            { AXI_LOWBW,    {5000,   -1,   -1}, {{ true, -1, -1}, { true, -1, -1}} },
            { AXI_NONE }
        },

        .ddrc_perf = {
            {-1, -1, -1, -1, -1, -1} /* 0xFF130041, 0xFF130041, 0x0F1F0F07, 0x0F1F0F07, 0x00100010, 0x00100010 */
        },
    },

    // HDMI444 HFR 대응(144Hz, 165Hz)
    // BW config = CPU 1GB/s, GPU 1GB/s, LNX 2GB/s
	// DDRC config = STV-R:W=2:1, RR=3.0us, UGT-R:W=2:1, Write-urgent < Read_urgent, Hybrid-Starvation-ON",
	//
	// (real time port) : FMC3 (port2)를 real port로 사용하기 위함
	// M0 및 M1 의 PORT2의 우선순위 부여
	//
	// (port switch)
	// TIVMCU : M0.R=P0(<-P2), M0.W=P0(<-P2), M1.R=P0(<-P2), M1.W=P0(<-P2),
	// FMC2 : M0.R = P1 (<-P2)
	// FMC3 : M0.R = P2 (<-P1)
	// IMX0 : M0.R = P1 (<-P2), M1.R = P1 (<-P2)
    // see http://jira.lge.com/issue/browse/SICDTV-15723
    [bwm_perf_level_hdmi444_hfr] = {

        .text = "HDMI444 HFR(144Hz, 165Hz) config. \
		BW config = CPU 1GB/s, GPU 1GB/s, LNX 2GB/s \
		DDRC config = (3rd) STV-R:W=4:1, UGT-R:W=3:1, Hybrid-Starvation-ON, real-time-port : PORT2(FMC3) \
		(2nd) : DDRC config = STV-R:W=2:1, RR=3.0us, UGT-R:W=2:1, Write-urgent < Read_urgent, Hybrid-Starvation-ON \
		+ reg_bq_hyb_stv_cbuf_thr (0x13 -> 0xFC) : cbuf thr 값 보다 작으면 hyb_stv 발생 시킴 (read에 유리하도록) \
		+ reg_bq_hyb_stv_thr (0x4 -> 0x0) : 실제 hyb_stv 발생 시 rd thr을 낮춰 rd stv이 보다 빨리 발생하도록 함 \
		+ Urgent에 대한 starvation값이 1/4로 줄어들어 Urgent시 보다 빨리 R/W starvation이 발생 (비율은 동일) \
		urgent write starvation threshold (0xF -> 0x3) / urgent read starvation threshold (0x7 -> 0x1) \
		(3rd) : DDRC config = (3rd) STV-R:W=4:1, UGT-R:W=3:1, Write-urgent < Read_urgent, Hybrid-Starvation-ON \
		+ reg_bq_hyb_stv_cbuf_thr (0xFC -> 0x3C) : 동일 (어차피 Max가 0x3C) \
		+ reg_bq_rd_stv_thr (0x0F -> 0x08) : rd stv 유발 조건 강화 (해당 thr 만큼 서비스를 못 받으면 stv 일으킴) \
		+ reg_bq_wr_stv_thr (0x1F -> 0x20) : wr stv 유발 조건 약화 (해당 thr 만큼 서비스를 못 받으면 stv 일으킴) \
		+ reg_bq_wr_urg_stv_thr (0x03 -> 0x05) : urg에 대한 stv thr 값이 늘어나 Urgent 시 보다 느리게 wr stv 발생 \
		* FMC3 (port2)를 real time port로 사용 : M0 및 M1 의 PORT2의 우선순위 부여 및 기타 port 조정 \
		- TIVMCU : M0.R=P0(<-P2), M0.W=P0(<-P2), M1.R=P0(<-P2), M1.W=P0(<-P2) \
		- FMC2 : M0.R = P1 (<-P2) \
		- FMC3 : M0.R = P2 (<-P1) \
		- IMX0 : M0.R = P1 (<-P2), M1.R = P1 (<-P2)",

        .axi_perf = {
            // master,      bwlimit rd/wr       port rd m0/m1     port wr m0/m1
            { AXI_CPU_M0,   {5000, 1000, 1000}, {{false, -1, -1}, {false, -1, -1}} },
            { AXI_CPU_M1,   {5000, 1000, 1000}, {{false, -1, -1}, {false, -1, -1}} },
            { AXI_GPU0,     {5000, 1000, 1000}, {{ true, -1, -1}, { true, -1, -1}} },
            { AXI_GPU1,     {5000, 1000, 1000}, {{ true, -1, -1}, { true, -1, -1}} },
            { AXI_LNX2,     {5000, 2000, 2000}, {{ true, -1, -1}, { true, -1, -1}} },
            { AXI_LOWBW,    {5000,   -1,   -1}, {{ true, -1, -1}, { true, -1, -1}} },
            { AXI_TIVVMCU,  {5000,   -1,   -1}, {{ true,  0,  0}, { true,  0,  0}} },
            { AXI_FMC2,     {5000,   -1,   -1}, {{ true,  1, -1}, { true, -1, -1}} },
            { AXI_FMC3,     {5000,   -1,   -1}, {{ true,  2, -1}, { true, -1, -1}} },
            { AXI_IMX0,     {5000,   -1,   -1}, {{ true,  1,  1}, { true, -1, -1}} },
            { AXI_NONE }
        },

        .ddrc_perf = {
            {0xFF3C0001, 0xFF3C0001, 0x08200501, 0x08200501, 0x40110010, 0x40110010}
        },
    },
};

static enum bwm_perf_level g_perf_level = bwm_perf_level_default;

/*========================================================================================
    Implementation Group
========================================================================================*/
static void bwm_o26_detect_default_config(void)
{
    static bool inited = false;

    if (inited) return;

    {
        int i;
        uint32_t reg_val;

        // read AXI master registers & make default configuration
        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct port_selector_ctrl* port_reg;
            struct priority1_ctrl* prio_reg;
            struct pending_limiter_ctrl* pend_reg;

            struct axi_master_desc* master_desc = &g_master_desc[i];

            // read default port configuration
            if (master_desc->reg_port > 0x0)
            {
                REG_READ(master_desc->reg_port, &reg_val);

                port_reg = (struct port_selector_ctrl*)&reg_val;

                g_default_port_desc[i].rd.en = port_reg->rd_en;
                g_default_port_desc[i].rd.m0 = port_reg->rd_m0;
                g_default_port_desc[i].rd.m1 = port_reg->rd_m1;
                g_default_port_desc[i].wr.en = port_reg->wr_en;
                g_default_port_desc[i].wr.m0 = port_reg->wr_m0;
                g_default_port_desc[i].wr.m1 = port_reg->wr_m1;
            }
            else
            {
                g_default_port_desc[i].rd.en = false;
                g_default_port_desc[i].rd.m0 = 0;
                g_default_port_desc[i].rd.m1 = 0;
                g_default_port_desc[i].wr.en = false;
                g_default_port_desc[i].wr.m0 = 0;
                g_default_port_desc[i].wr.m1 = 0;
            }

            // read default priority configuration
            if (master_desc->reg_prio > 0x0)
            {
                REG_READ(master_desc->reg_prio + PRIO_REG_OFF_CTRL1, &reg_val);
                prio_reg = (struct priority1_ctrl*)&reg_val;

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

            if (master_desc->reg_pend > 0x0)
            {
                REG_READ(master_desc->reg_pend, &reg_val);
                pend_reg = (struct pending_limiter_ctrl*)&reg_val;

                g_default_pend_desc[i].rd = pend_reg->rd_pend;
                g_default_pend_desc[i].wr = pend_reg->wr_pend;
            }
            else
            {
                g_default_pend_desc[i].rd = 0x3f;
                g_default_pend_desc[i].wr = 0x3f;
            }
        }


#ifndef BUILD_FEATURE_audio_board /* TV */
        // make DDRC to be wr_en state
        for (i = 0; i < DDRC_NUM; i++)
        {
            OS_WrReg(g_ddrc_reg_desc.en_reg[i], DDRC_CTRL_EN_VAL);
        }

        // read default DDRC master registers
        for (i = 0; i < DDRC_CTRL_REGS_NUM; i++)
        {
            REG_READ(g_ddrc_reg_desc.data_reg[i], &reg_val);

            g_default_ddrc_desc.data[i] = reg_val;
            //g_bwm_perf_desc[bwm_perf_level_default].ddrc_perf.data[i] = reg_val;
        }
#endif
    }

    inited = true;
}

static int bwm_o26_write_perf_regs(struct axi_master_perf_desc* perf_desc)
{
    uint32_t tm_val;
    uint32_t rdbw_val;
    uint32_t wrbw_val;
    uint32_t port_val;
#ifdef SUPPORT_PENDING
    uint32_t pend_val;
#endif
#ifdef SUPPORT_PRIORITY
    uint32_t prio_val0, prio_val1;
#endif

    struct port_selector_ctrl* port_reg;
#ifdef SUPPORT_PENDING
    struct pending_limiter_ctrl* pend_reg;
#endif

    struct axi_master_desc* master_desc;
    struct axi_master_port_desc* default_port_desc;
#ifdef SUPPORT_PRIORITY
    struct axi_master_prio_desc* default_prio_desc;
#endif

    if (!perf_desc)
    {
        SYS_ERROR("invalid param\n");
        return RET_ERROR;
    }

    master_desc = &g_master_desc[perf_desc->master];
    default_port_desc = &g_default_port_desc[perf_desc->master];
#ifdef SUPPORT_PRIORITY
    default_prio_desc = &g_default_prio_desc[perf_desc->master];
#endif

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

    SYS_NOTI("[bwm] axi_master(%8s) bwlimit-configure. time=%d.%03dus, rd=%04dMB/s, wr=%04dMB/s, reg_val=0x%08x,0x%08x,0x%08x\n",
             master_desc->name,
             perf_desc->bwlimit.tm / 1000, perf_desc->bwlimit.tm % 1000,
             perf_desc->bwlimit.rd,
             perf_desc->bwlimit.wr,
             tm_val,
             rdbw_val,
             wrbw_val);

    OS_WrReg(master_desc->reg_bw_tm, tm_val);
    OS_WrReg(master_desc->reg_bw_rd, rdbw_val);
    OS_WrReg(master_desc->reg_bw_wr, wrbw_val);

    // port 변경.
    // default 값을 가지고 있지 않으므로, perf desc 내에서 잘 기술해 줘야 함
    // port 설정이 -1 이면 이미 확보한 default port 값으로 채우도록 함.
    // register 값이 0x0 인 경우 있으므로, 반드시 register 값이 유효한지 확인 필요함
    if (master_desc->reg_port > 0x0)
    {
        if (perf_desc->port.rd.en || perf_desc->port.wr.en)
        {
            REG_READ(master_desc->reg_port, &port_val);

            port_reg = (struct port_selector_ctrl*)&port_val;

            if (perf_desc->port.rd.en)
            {
                port_reg->rd_en = 1;
                port_reg->rd_m0 = (perf_desc->port.rd.m0 < 0) ? default_port_desc->rd.m0 : perf_desc->port.rd.m0;
                port_reg->rd_m1 = (perf_desc->port.rd.m1 < 0) ? default_port_desc->rd.m1 : perf_desc->port.rd.m1;
            }

            if (perf_desc->port.wr.en)
            {
                port_reg->wr_en = 1;
                port_reg->wr_m0 = (perf_desc->port.wr.m0 < 0) ? default_port_desc->wr.m0 : perf_desc->port.wr.m0;
                port_reg->wr_m1 = (perf_desc->port.wr.m1 < 0) ? default_port_desc->wr.m1 : perf_desc->port.wr.m1;
            }

            SYS_NOTI("[bwm] axi_master(%8s) port-configure. rd(en=%d, m0/m1=%d/%d) wr(en=%d, m0/m1=%d/%d), reg_val=0x%08x\n",
                     master_desc->name,
                     port_reg->rd_en, port_reg->rd_m0, port_reg->rd_m1,
                     port_reg->wr_en, port_reg->wr_m0, port_reg->wr_m1,
                     port_val);

            OS_WrReg(master_desc->reg_port, port_val);
        }
    }
    else
    {
        SYS_NOTI("[bwm] axi_master(%8s) port-configure. n/a\n", master_desc->name);
    }

#ifdef SUPPORT_PENDING
    // pending 변경
    // default 값으로 설정해야 하는 경우 0x3f 를 설정하면 됨.
    REG_READ(master_desc->reg_pend, &pend_val);

    pend_reg = (struct pending_limiter_ctrl*)&pend_val;

    pend_reg->rd_pend = (perf_desc->pend.rd < 0) ? 0x3f : perf_desc->pend.rd;
    pend_reg->wr_pend = (perf_desc->pend.wr < 0) ? 0x3f : perf_desc->pend.wr;

    SYS_NOTI("[bwm] axi_master(%d:%8s) pending-configure. rd=%02d, wr=%02d, reg_val=0x%08x\n",
             perf_desc->master, master_desc->name,
             perf_desc->pend.rd,
             perf_desc->pend.wr,
             pend_val);

    OS_WrReg(master_desc->reg_pend, pend_val);
#endif

#ifdef SUPPORT_PRIORITY

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
            REG_READ(master_desc->reg_prio + PRIO_REG_OFF_CTRL0, &prio_val0);
            prio_ctrl0_reg->rf_uc_user_mode_r = 0x1;
            prio_ctrl0_reg->rf_uc_user_mode_w = 0x1;
            OS_WrReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL0, prio_val0);

            // write read & write priority
            REG_READ(master_desc->reg_prio + PRIO_REG_OFF_CTRL1, &prio_val1);
            prio_ctrl1_reg->rf_uc_m0_main_user_r = rd_val;
            prio_ctrl1_reg->rf_uc_m0_main_user_w = wr_val;
            prio_ctrl1_reg->rf_uc_m1_main_user_r = rd_val;
            prio_ctrl1_reg->rf_uc_m1_main_user_w = wr_val;
            OS_WrReg(master_desc->reg_prio + PRIO_REG_OFF_CTRL1, prio_val1);

            SYS_NOTI("[bwm] axi_master(%d:%8s) prio-configure. rd=0x%2x, wr=0x%02x. reg_val=0x%08x,0x%08x\n",
                     perf_desc->master, master_desc->name,
                     rd_val, wr_val,
                     prio_val0, prio_val1);
        }
    }
    else
    {
        SYS_NOTI("[bwm] axi_master(%d:%8s) prio-configure. n/a\n", perf_desc->master, master_desc->name);
    }

#endif

    return RET_OK;
}

static int bwm_o26_write_ddrc_perf_regs(struct ddrc_perf_desc* val_desc)
{
#ifndef BUILD_FEATURE_audio_board /* TV */
    int i;

    if (!val_desc)
    {
        SYS_ERROR("invalid param\n");
        return RET_ERROR;
    }

    // make DDRC to be wr_en state
    for (i = 0; i < DDRC_NUM; i++)
    {
        OS_WrReg(g_ddrc_reg_desc.en_reg[i], DDRC_CTRL_EN_VAL);
    }

    for (i = 0; i < DDRC_CTRL_REGS_NUM; i++)
    {
        uint32_t reg_addr;
        uint32_t reg_val;
        bool b_default = false;

        reg_addr = g_ddrc_reg_desc.data_reg[i];

        if (val_desc->data[i] == (UINT32) - 1)
        {
            reg_val = g_default_ddrc_desc.data[i];
            b_default = true;
        }
        else
        {
            reg_val = val_desc->data[i];
        }

        SYS_NOTI("[bwm] ddrc data_reg[%d]=0x%08x, val=0x%08x (default? %s)\n",
                 i, reg_addr, reg_val, (b_default) ? "yes" : "no");
        OS_WrReg(reg_addr, reg_val);
    }
#endif

    return RET_OK;
}

static int bwm_o26_write_perf_level(enum bwm_perf_level perf_level)
{
    int i;
    int item_num;
    int ret = RET_ERROR;

    if (perf_level >= bwm_perf_level_max)
    {
        SYS_ERROR("invalid param. bwm_perfl_level=%d\n", perf_level);
        return RET_ERROR;
    }

    // write AXI perf data
    item_num = NELEMENTS(g_bwm_perf_desc[perf_level].axi_perf);

    for (i = 0; i < item_num; i++)
    {
        if (IS_MASTER_INVALID(g_bwm_perf_desc[perf_level].axi_perf[i].master)) break;

        if (RET_OK != bwm_o26_write_perf_regs(&g_bwm_perf_desc[perf_level].axi_perf[i]))
        {
            SYS_ERROR("write error during writing axi master. perf_level=%d, idx=%d\n", perf_level, i);
            goto func_exit;
        }
    }

    // write DDRC perf data
    if (RET_OK != bwm_o26_write_ddrc_perf_regs(&g_bwm_perf_desc[perf_level].ddrc_perf))
    {
        SYS_ERROR("write error during writing ddrc. perf_level=%d\n", perf_level);
        goto func_exit;
    }

    ret = RET_OK;
func_exit:
    return ret;
}

// 레지스터 offset 기반으로 register address 를 채운다.
static void bwm_o26_reg_auto_scan(void)
{
    int i;

#ifdef SUPPORT_DEBUG
    SYS_NOTI("|No|       MASTER | CLK | BASE_ADDR  | BWLIMIT_ADDR (time/rd/wr)          | PORT_ADDR  | PEND_ADDR  | PIO_ADDR (0/1)         |\n");
#endif

    for (i = 0; i < MAX_AXI_MASTER; i++)
    {
        struct axi_master_desc* master_desc = &g_master_desc[i];

        if (master_desc->flag & flag_limiter)
        {
            master_desc->reg_bw_tm = master_desc->reg_base + reg_offset_limiter_tm;
            master_desc->reg_bw_rd = master_desc->reg_base + reg_offset_limiter_rd;
            master_desc->reg_bw_wr = master_desc->reg_base + reg_offset_limiter_wr;
        }

        if (master_desc->flag & flag_port)
        {
            master_desc->reg_port = master_desc->reg_base + reg_offset_port;
        }

        if (master_desc->flag & flag_pend)
        {
            master_desc->reg_pend = master_desc->reg_base + reg_offset_pend;
        }

        if (master_desc->flag & flag_prio)
        {
            master_desc->reg_prio = master_desc->reg_base + reg_offset_prio;
        }

#ifdef SUPPORT_DEBUG
        SYS_NOTI("|%2d| %12s | %3d | 0x%08x | 0x%08x, 0x%08x, 0x%08x | 0x%08x | 0x%08x | 0x%08x, 0x%08x |\n",
                 i, master_desc->name, master_desc->clk, master_desc->reg_base,
                 master_desc->reg_bw_tm, master_desc->reg_bw_rd, master_desc->reg_bw_wr,
                 master_desc->reg_port,
                 master_desc->reg_pend,
                 master_desc->reg_prio + PRIO_REG_OFF_CTRL0, master_desc->reg_prio + PRIO_REG_OFF_CTRL1);
#endif
    }

    SYS_NOTI("[bwm] register table autoscan completed\n");
}

struct bwm_chip_drv bwm_o26_chip_config(void)
{
    struct bwm_chip_drv chip_drv;

    chip_drv.do_init = bwm_o26_do_init;
    chip_drv.do_config = bwm_o26_do_config;
    chip_drv.do_proc = bwm_o26_do_proc;

    bwm_o26_reg_auto_scan();

    return chip_drv;
}

// 기본 설정을 진행한다.
static void bwm_o26_do_init(void)
{
    SYS_NOTI("[bwm] set o26 hw default\n");

    bwm_o26_detect_default_config();

    bwm_o26_write_perf_level(bwm_perf_level_default);

    g_perf_level = bwm_perf_level_default;
}

// 업데이트된 설정에 따라 설정을 업데이트한다.
static void bwm_o26_do_config(struct bwm_ctx* ctx)
{
    enum bwm_perf_level level = bwm_perf_level_default;

    SYS_DEBUG("[bwm] o26 do_config. old perf level=%d\n", g_perf_level);

    if (0)
    {

    }
    // see http://jira.lge.com/issue/browse/SICDTV-15723
    // pqe.input_src: hdmi444
    // pqe.input_win: 3840x2160
    // pqe.input_rate: 144Hz, 165Hz
    else if (!strncmp(ctx->pqe.input_src, "hdmi444", strlen("hdmi444")) &&
             ctx->pqe.input_win.w >= 3840 &&
             ctx->pqe.input_win.h >= 1080 &&
             ctx->pqe.input_rate > 132)
    {
        SYS_DEBUG("[bwm] HDMI444 HFR (144Hz, 165Hz) %dx%d@%dHz notified. set perf_level=bwm_perf_level_hdmi444_hfr\n",
                  ctx->pqe.input_win.w, ctx->pqe.input_win.h, ctx->pqe.input_rate);

        level = bwm_perf_level_hdmi444_hfr;
    }

#if 0 // O24 자료. 필요시 참고하여 사용할것. 설정값은 bwm_drv_o24.c 를 참고할것

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
             ctx->pqe.input_win.h >= 2160 &&
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

#endif

    if (g_perf_level != level)
    {
        bwm_o26_write_perf_level(level);

        SYS_NOTI("[bwm] perf level changed: %d -> %d\n", g_perf_level, level);

        g_perf_level = level;
    }

    SYS_DEBUG("[bwm] o26 do_config completed. new perf level=%d\n", g_perf_level);
}

// O22 칩 상태를 출력한다. 등등
static void bwm_o26_do_proc(struct bwm_ctx* ctx, char* command, struct seq_file* m)
{
    int i, j;
    uint32_t reg_val_tm, reg_val_rdbw, reg_val_wrbw;
    uint32_t reg_val_port, reg_val_pend, reg_val_ddrc;
    uint32_t reg_val_prio0, reg_val_prio1;

    int curr_axi_perf_cnt = NELEMENTS(g_bwm_perf_desc[g_perf_level].axi_perf);

    if (!strncmp(command, "status", strlen("status")))
    {
        seq_printf(m, "\n");
        seq_printf(m, "bwm_perf_level: %d (%s)\n", g_perf_level, g_bwm_perf_desc[g_perf_level].text);
        seq_printf(m, "\n");

        seq_printf(m, "current perf_level(%d) desc\n", g_perf_level);
        seq_printf(m,
                   "| %12s | BW LIMIT CFG (time/rd/wr)   |PORT RD(m0/m1)|PORT WR(m0/m1)| BW LIMIT REG VALUE               | PORT VALUE |\n",
                   "AXI_MASTER");

        // 현재 설정된 AXI perf 상태를 출력한다.
        for (i = 0; i < curr_axi_perf_cnt; i++)
        {
            struct axi_master_perf_desc* perf_desc = &g_bwm_perf_desc[g_perf_level].axi_perf[i];
            struct axi_master_desc* master_desc = &g_master_desc[perf_desc->master];

            if (IS_MASTER_INVALID(perf_desc->master)) break;

            REG_READ(master_desc->reg_bw_tm, &reg_val_tm);
            REG_READ(master_desc->reg_bw_rd, &reg_val_rdbw);
            REG_READ(master_desc->reg_bw_wr, &reg_val_wrbw);
            REG_READ(master_desc->reg_pend, &reg_val_pend);

            if (master_desc->reg_port > 0)
            {
                REG_READ(master_desc->reg_port, &reg_val_port);
            }
            else
            {
                reg_val_port = 0x0;
            }

            if (master_desc->reg_prio > 0)
            {
                REG_READ(master_desc->reg_prio + PRIO_REG_OFF_CTRL0, &reg_val_prio0);
                REG_READ(master_desc->reg_prio + PRIO_REG_OFF_CTRL1, &reg_val_prio1);
            }
            else
            {
                reg_val_prio0 = 0x0;
                reg_val_prio1 = 0x0;
            }

            seq_printf(m, "| %12s | %d.%03dus, %04dMB/s, %04dMB/s |"
#ifdef SUPPORT_PENDING
                       " %02d %02d |,"
#endif
#ifdef SUPPORT_PRIORITY
                       " %s %d %d |\n",
#endif
                       " %-6s %2d/%2d | %-6s %2d/%2d |",
                       master_desc->name,
                       perf_desc->bwlimit.tm / 1000, perf_desc->bwlimit.tm % 1000,
                       perf_desc->bwlimit.rd,
                       perf_desc->bwlimit.wr,
#ifdef SUPPORT_PENDING
                       perf_desc->pend.rd,
                       perf_desc->pend.wr,
#endif
#ifdef SUPPORT_PRIORITY
                       perf_desc->prio.en ? "enable" : "--",
                       perf_desc->prio.rd,
                       perf_desc->prio.wr,
#endif
                       perf_desc->port.rd.en ? "enable" : "--",
                       perf_desc->port.rd.m0,
                       perf_desc->port.rd.m1,
                       perf_desc->port.wr.en ? "enable" : "--",
                       perf_desc->port.wr.m0,
                       perf_desc->port.wr.m1);

            seq_printf(m, " 0x%08x 0x%08x 0x%08x |"
#ifdef SUPPORT_PENDING
                       " 0x%08x |"
#endif
#ifdef SUPPORT_PRIORITY
                       " 0x%08x 0x%08x |"
#endif
                       " 0x%08x |\n",
                       reg_val_tm,
                       reg_val_rdbw,
                       reg_val_wrbw,
#ifdef SUPPORT_PENDING
                       reg_val_pend,
#endif
#ifdef SUPPORT_PRIORITY
                       reg_val_prio0,
                       reg_val_prio1,
#endif
                       reg_val_port);
        }

        seq_printf(m, "| %12s |", "DDRC");

        for (i = 0; i < DDRC_CTRL_REGS_NUM; i++)
        {
            seq_printf(m, " 0x%08x", g_bwm_perf_desc[g_perf_level].ddrc_perf.data[i]);
        }

        seq_printf(m, " |\n\n");

        // 현재 BW limiter 설정을 덤프한다.
        seq_printf(m, "current BW Limit HW status\n");
        seq_printf(m, "| %12s | REG VALUE (time/rd/wr)           | BW LIMIT CFG (time/rd/wr)   |\n", "AXI_MASTER");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct axi_master_desc* master_desc = &g_master_desc[i];
            uint32_t tm;
            int rdbw;
            int wrbw;

            REG_READ(master_desc->reg_bw_tm, &reg_val_tm);
            REG_READ(master_desc->reg_bw_rd, &reg_val_rdbw);
            REG_READ(master_desc->reg_bw_wr, &reg_val_wrbw);

            tm = reg_val_tm * 1000 / master_desc->clk;

            reg_val_rdbw &= 0x0fffffff;
            reg_val_wrbw &= 0x0fffffff;

            if (reg_val_rdbw == 0x0fffffff)
            {
                rdbw = -1;
            }
            else
            {
                rdbw = reg_val_rdbw * 1000 / tm;
            }

            if (reg_val_wrbw == 0x0fffffff)
            {
                wrbw = -1;
            }
            else
            {
                wrbw = reg_val_wrbw * 1000 / tm;
            }

            seq_printf(m, "| %12s | 0x%08x 0x%08x 0x%08x | %d.%03dus, %04dMB/s, %04dMB/s |\n",
                       master_desc->name,
                       reg_val_tm, reg_val_rdbw, reg_val_wrbw,
                       tm / 1000, tm % 1000, rdbw, wrbw);
        }

        seq_printf(m, "\n");

        // 현재 port 설정을 덤프한다.
        seq_printf(m, "current port HW status\n");
        seq_printf(m, "| %12s |   reg_val  | %6s m0 m1 | %6s m0 m1 |\n", "AXI_MASTER", "RD", "WR");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct port_selector_ctrl* port_reg;
            struct axi_master_desc* master_desc = &g_master_desc[i];

            if (master_desc->reg_port > 0x0)
            {
                REG_READ(master_desc->reg_port, &reg_val_port);

                port_reg = (struct port_selector_ctrl*)&reg_val_port;

                seq_printf(m, "| %12s | 0x%08x | %-6s %2d %2d | %-6s %2d %2d |\n",
                           master_desc->name,
                           reg_val_port,
                           (port_reg->rd_en) ? "enable" : "--",
                           port_reg->rd_m0,
                           port_reg->rd_m1,
                           (port_reg->wr_en) ? "enable" : "--",
                           port_reg->wr_m0,
                           port_reg->wr_m1);
            }
        }

        seq_printf(m, "\n");

        // 현재 pending 설정을 덤프한다.
        seq_printf(m, "current pending HW status\n");

        seq_printf(m, "| %12s | REG VALUE  |  RD  |  WR  |\n", "AXI_MASTER");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct pending_limiter_ctrl* pend_regs;
            struct axi_master_desc* master_desc = &g_master_desc[i];

            if (master_desc->reg_pend > 0x0)
            {
                REG_READ(master_desc->reg_pend, &reg_val_pend);

                pend_regs = (struct pending_limiter_ctrl*)&reg_val_pend;

                seq_printf(m, "| %12s | 0x%08x | 0x%02x | 0x%02x |\n",
                           master_desc->name,
                           reg_val_pend,
                           pend_regs->rd_pend,
                           pend_regs->wr_pend);
            }
            else
            {
                seq_printf(m, "| %12s |     N/A    |  N/A |  N/A |\n", master_desc->name);
            }
        }

        seq_printf(m, "\n");

        // 현재 priority 설정을 덤프한다.
        seq_printf(m, "current priority HW status\n");
        seq_printf(m, "| %12s | REG VALUE (0/1)       | MODE (r/w)| RD (m0/m1)| WR (m0/m1)|\n", "AXI_MASTER");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct priority0_ctrl* prio0_reg = (struct priority0_ctrl*)&reg_val_prio0;
            struct priority1_ctrl* prio1_reg = (struct priority1_ctrl*)&reg_val_prio1;

            struct axi_master_desc* master_desc = &g_master_desc[i];

            if (master_desc->reg_prio > 0x0)
            {
                REG_READ(master_desc->reg_prio + PRIO_REG_OFF_CTRL0, &reg_val_prio0);
                REG_READ(master_desc->reg_prio + PRIO_REG_OFF_CTRL1, &reg_val_prio1);

                seq_printf(m, "| %12s | 0x%08x 0x%08x | 0x%02x 0x%02x | 0x%02x 0x%02x | 0x%02x 0x%02x |\n",
                           master_desc->name,
                           reg_val_prio0,
                           reg_val_prio1,
                           prio0_reg->rf_uc_user_mode_r,
                           prio0_reg->rf_uc_user_mode_w,
                           prio1_reg->rf_uc_m0_main_user_r,
                           prio1_reg->rf_uc_m1_main_user_r,
                           prio1_reg->rf_uc_m0_main_user_w,
                           prio1_reg->rf_uc_m1_main_user_w);
            }
            else
            {
                seq_printf(m, "| %12s |    N/A         N/A    |  N/A  N/A |  N/A  N/A |  N/A  N/A |\n", master_desc->name);
            }
        }

        seq_printf(m, "\n");


        // 현재 DDRC 설정을 덤프한다.
        seq_printf(m, "current DDRC HW status\n");
        seq_printf(m, "| DDRC_REGS  | VALUE      |\n");

        for (i = 0;  i < DDRC_NUM; i++)
        {
            REG_READ(g_ddrc_reg_desc.en_reg[i], &reg_val_ddrc);

            seq_printf(m, "| 0x%08x | 0x%08x |\n", g_ddrc_reg_desc.en_reg[i], reg_val_ddrc);
        }

        for (i = 0;  i < DDRC_CTRL_REGS_NUM; i++)
        {
            REG_READ(g_ddrc_reg_desc.data_reg[i], &reg_val_ddrc);

            seq_printf(m, "| 0x%08x | 0x%08x |\n", g_ddrc_reg_desc.data_reg[i], reg_val_ddrc);
        }

        // axi master 값을 덤프한다.
        seq_printf(m, "\n");
        seq_printf(m, "\n");
        seq_printf(m, "AXI MASTER DESC. TABLE\n");

        seq_printf(m,
                   "|No|       MASTER | CLK | BASE_ADDR  | BWLIMIT_ADDR (time/rd/wr)          | PORT_ADDR  | PEND_ADDR  | PRIO_ADDR (0/1)        |\n");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct axi_master_desc* master_desc = &g_master_desc[i];

            seq_printf(m, "|%2d| %12s | %3d | 0x%08x | 0x%08x, 0x%08x, 0x%08x | 0x%08x | 0x%08x | 0x%08x, 0x%08x |\n",
                       i,
                       master_desc->name,
                       master_desc->clk,
                       master_desc->reg_base,
                       master_desc->reg_bw_tm,
                       master_desc->reg_bw_rd,
                       master_desc->reg_bw_wr,
                       master_desc->reg_port,
                       master_desc->reg_pend,
                       master_desc->reg_prio + PRIO_REG_OFF_CTRL0,
                       master_desc->reg_prio + PRIO_REG_OFF_CTRL1);
        }

        seq_printf(m, "\n");
        seq_printf(m, "DDRC regs table\n");
        seq_printf(m, "| REGS ADDR  |\n");
#if 0

        for (i = 0; i < DDRC_NUM; i++)
        {
            seq_printf(m, "| 0x%08x |\n", g_ddrc_reg_desc.en_reg[i]);
        }

#endif

        for (i = 0; i < DDRC_CTRL_REGS_NUM; i++)
        {
            seq_printf(m, "| 0x%08x |\n", g_ddrc_reg_desc.data_reg[i]);
        }

        seq_printf(m, "\n");

        // perf 값을 덤프한다.
        seq_printf(m, "BWM PERF DESC. TABLE\n");

        for (j = 0; j < bwm_perf_level_max; j++)
        {
            int axi_perf_cnt = NELEMENTS(g_bwm_perf_desc[j].axi_perf);

            seq_printf(m, "perf_level[%d]\n", j);
            seq_printf(m, "text: %s\n", g_bwm_perf_desc[j].text);

            seq_printf(m, "|       MASTER | BWLIMIT(time/rd/wr)       |PORT RD(m1/m1)|PORT WR(m0/m1)|\n");

            for (i = 0; i < axi_perf_cnt; i++)
            {
                struct axi_master_perf_desc* perf_desc = &g_bwm_perf_desc[j].axi_perf[i];
                struct axi_master_desc* master_desc = &g_master_desc[perf_desc->master];

                if (IS_MASTER_INVALID(perf_desc->master)) break;

                seq_printf(m,
                           "| %12s | %d.%03dus %04dMB/s %04dMB/s | %-6s %2d %2d | %-6s %2d %2d |\n",
                           master_desc->name,
                           perf_desc->bwlimit.tm / 1000, perf_desc->bwlimit.tm % 1000,
                           perf_desc->bwlimit.rd,
                           perf_desc->bwlimit.wr,
                           perf_desc->port.rd.en ? "enable" : "--",
                           perf_desc->port.rd.m0,
                           perf_desc->port.rd.m1,
                           perf_desc->port.wr.en ? "enable" : "--",
                           perf_desc->port.wr.m0,
                           perf_desc->port.wr.m1);
            }

            seq_printf(m, "|         DDRC |");

            for (i = 0; i < DDRC_CTRL_REGS_NUM; i++)
            {
                seq_printf(m, " 0x%08x", g_bwm_perf_desc[j].ddrc_perf.data[i]);
            }

            seq_printf(m, " |\n\n");
        }

        // HW 기본 port 구성을 덤프한다.
        seq_printf(m, "+ default port HW status\n");

        seq_printf(m, "| %12s | RD m0 m1 | WR m0 m1 |\n", "AXI_MASTER");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct axi_master_desc* master_desc = &g_master_desc[i];
            struct axi_master_port_desc* port_desc = &g_default_port_desc[i];

            seq_printf(m, "| %12s | %-2s %2d %2d | %-2s %2d %2d |\n",
                       master_desc->name,
                       (port_desc->rd.en) ? "en" : "--",
                       port_desc->rd.m0,
                       port_desc->rd.m1,
                       (port_desc->wr.en) ? "en" : "--",
                       port_desc->wr.m0,
                       port_desc->wr.m1);
        }

        seq_printf(m, "\n");

        // 기본 pend 구성을 덤프한다.
        seq_printf(m, "+ default pending HW status\n");
        seq_printf(m, "| %12s |  RD  |  WR  |\n", "AXI_MASTER");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct axi_master_desc* master_desc = &g_master_desc[i];
            struct axi_master_pending_desc* pend_desc = &g_default_pend_desc[i];

            if (master_desc->reg_pend > 0)
            {
                seq_printf(m, "| %12s | 0x%02x | 0x%02x |\n",
                           master_desc->name,
                           pend_desc->rd,
                           pend_desc->wr);
            }
            else
            {
                seq_printf(m, "| %12s |   N/A  |  N/A |  N/A |\n", master_desc->name);
            }
        }

        seq_printf(m, "\n");

        // 기본 prio 구성을 덤프한다.
        seq_printf(m, "+ default priority HW status\n");
        seq_printf(m, "| %12s |  MODE  |  RD   WR  |\n", "AXI_MASTER");

        for (i = 0; i < MAX_AXI_MASTER; i++)
        {
            struct axi_master_desc* master_desc = &g_master_desc[i];
            struct axi_master_prio_desc* prio_desc = &g_default_prio_desc[i];

            if (master_desc->reg_prio > 0)
            {
                seq_printf(m, "| %12s | %s | 0x%02x 0x%02x |\n",
                           master_desc->name,
                           (prio_desc->en) ? "enable" : "disable",
                           prio_desc->rd,
                           prio_desc->wr);
            }
            else
            {
                seq_printf(m, "| %12s |   N/A  |  N/A  N/A |\n", master_desc->name);
            }
        }

#ifndef BUILD_FEATURE_audio_board /* TV */
        seq_printf(m, "\n");

        seq_printf(m, "+ default DDRC HW status\n");
        seq_printf(m, "| DDRC_REGS  | VALUE      |\n");

        for (i = 0; i < DDRC_NUM; i++)
        {
            seq_printf(m, "| 0x%08x | 0x%08x |\n", g_ddrc_reg_desc.en_reg[i], DDRC_CTRL_EN_VAL);
        }

        for (i = 0; i < DDRC_CTRL_REGS_NUM; i++)
        {
            seq_printf(m, "| 0x%08x | 0x%08x |\n", g_ddrc_reg_desc.data_reg[i], g_default_ddrc_desc.data[i]);
        }
#endif
    }
}

