#ifndef _SCRG_CTRL_FMC_REG_H_
#define _SCRG_CTRL_FMC_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  HEADER_2 : Use Another Header Structure 
---------------------------------------------------------------------------------------*/

#ifndef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0x1B_0000    crg_fmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_FMC_CRG_FMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_0004    crg_fmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_FMC_CRG_FMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_0008    crg_fmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_FMC_CRG_FMC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_000C    crg_fmc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_gsc_6_de_bnd_n: 1,    //    3
    reg_soft_rst_h_fmc_0_de_bnd_n: 1,    //    4
    reg_soft_rst_h_fmc_1_de_bnd_n: 1,    //    5
    reg_soft_rst_h_fmc_2_de_bnd_n: 1,    //    6
    reg_soft_rst_h_fmc_3_de_bnd_n: 1,    //    7
    reg_soft_rst_h_fmc_4_de_bnd_n: 1,    //    8
    reg_soft_rst_h_fmc_5_de_bnd_n: 1,    //    9
    reg_soft_rst_h_gsc_10_de_bnd_n: 1,    //  10
    reg_soft_rst_h_gsc_7_de_bnd_n: 1,    //   11
    reg_soft_rst_h_gsc_8_de_bnd_n: 1,    //   12
    reg_soft_rst_h_gsc_9_de_bnd_n: 1,    //   13
    reg_soft_rst_h_sre_2_de_bnd_n: 1,    //   14
    reg_soft_rst_h_sre_3_de_bnd_n: 1,    //   15
    reg_soft_rst_p_fmc_0_axi_bnd_n: 1,    //  16
    reg_soft_rst_p_fmc_1_axi_bnd_n: 1,    //  17
    reg_soft_rst_p_fmc_2_axi_bnd_n: 1,    //  18
    reg_soft_rst_p_fmc_3_axi_bnd_n: 1,    //  19
    reg_soft_rst_x_fmc_0_axi_bnd_n: 1,    //  20
    reg_soft_rst_x_fmc_0_axi_n:  1,    //     21
    reg_soft_rst_x_fmc_1_axi_bnd_n: 1,    //  22
    reg_soft_rst_x_fmc_1_axi_n:  1,    //     23
    reg_soft_rst_x_fmc_2_axi_bnd_n: 1,    //  24
    reg_soft_rst_x_fmc_2_axi_n:  1,    //     25
    reg_soft_rst_x_fmc_3_axi_bnd_n: 1,    //  26
    reg_soft_rst_x_fmc_3_axi_n:  1,    //     27
                              :  4;    //  31:28 reserved
}SCRG_CTRL_FMC_CRG_FMC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_0010    crg_fmc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_FMC_CRG_FMC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_0014    crg_fmc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_FMC_CRG_FMC05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_0018    crg_fmc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_FMC_CRG_FMC06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMC_CRG_FMC00_O22A0_T          crg_fmc00  ;             // 0x1B_0000
    SCRG_CTRL_FMC_CRG_FMC01_O22A0_T          crg_fmc01  ;             // 0x1B_0004
    SCRG_CTRL_FMC_CRG_FMC02_O22A0_T          crg_fmc02  ;             // 0x1B_0008
    SCRG_CTRL_FMC_CRG_FMC03_O22A0_T          crg_fmc03  ;             // 0x1B_000C
    SCRG_CTRL_FMC_CRG_FMC04_O22A0_T          crg_fmc04  ;             // 0x1B_0010
    SCRG_CTRL_FMC_CRG_FMC05_O22A0_T          crg_fmc05  ;             // 0x1B_0014
    SCRG_CTRL_FMC_CRG_FMC06_O22A0_T          crg_fmc06  ;             // 0x1B_0018
}SCRG_CTRL_FMC_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif

/*----------------------------------------------------------------------------------------
  Reference Header (Another Header Structure)
---------------------------------------------------------------------------------------*/

#ifdef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

#define BASEADDRESS 0

#define SCRG_CTRL_FMC_CRG_FMC00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_FMC_CRG_FMC01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_FMC_CRG_FMC02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_FMC_CRG_FMC03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_FMC_CRG_FMC04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_FMC_CRG_FMC05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_FMC_CRG_FMC06_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x1B_0000    crg_fmc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_FMC_CRG_FMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_0004    crg_fmc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_FMC_CRG_FMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_0008    crg_fmc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_FMC_CRG_FMC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_000C    crg_fmc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_gsc_6_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_fmc_0_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_fmc_1_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_fmc_2_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_fmc_3_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_fmc_4_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_fmc_5_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_gsc_10_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_gsc_7_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_gsc_8_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_gsc_9_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_sre_2_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_sre_3_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_p_fmc_0_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_p_fmc_1_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_p_fmc_2_axi_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_p_fmc_3_axi_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_x_fmc_0_axi_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_x_fmc_0_axi_n: 1;    //  21
    UINT32 reg_soft_rst_x_fmc_1_axi_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_x_fmc_1_axi_n: 1;    //  23
    UINT32 reg_soft_rst_x_fmc_2_axi_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_x_fmc_2_axi_n: 1;    //  25
    UINT32 reg_soft_rst_x_fmc_3_axi_bnd_n: 1;    //  26
    UINT32 reg_soft_rst_x_fmc_3_axi_n: 1;    //  27
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}SCRG_CTRL_FMC_CRG_FMC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_0010    crg_fmc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_FMC_CRG_FMC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_0014    crg_fmc05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_FMC_CRG_FMC05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1B_0018    crg_fmc06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_FMC_CRG_FMC06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMC_CRG_FMC00_O22A0_T          crg_fmc00  ;             // 0x1B_0000
    SCRG_CTRL_FMC_CRG_FMC01_O22A0_T          crg_fmc01  ;             // 0x1B_0004
    SCRG_CTRL_FMC_CRG_FMC02_O22A0_T          crg_fmc02  ;             // 0x1B_0008
    SCRG_CTRL_FMC_CRG_FMC03_O22A0_T          crg_fmc03  ;             // 0x1B_000C
    SCRG_CTRL_FMC_CRG_FMC04_O22A0_T          crg_fmc04  ;             // 0x1B_0010
    SCRG_CTRL_FMC_CRG_FMC05_O22A0_T          crg_fmc05  ;             // 0x1B_0014
    SCRG_CTRL_FMC_CRG_FMC06_O22A0_T          crg_fmc06  ;             // 0x1B_0018
}SCRG_CTRL_FMC_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

