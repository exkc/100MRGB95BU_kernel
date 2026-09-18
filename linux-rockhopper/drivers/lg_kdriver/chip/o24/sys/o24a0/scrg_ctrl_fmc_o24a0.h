#ifndef _SCRG_CTRL_FMC_REG_O24A0_H_
#define _SCRG_CTRL_FMC_REG_O24A0_H_

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
    0xCC43_0000    crg_fmc0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_FMC_CRG_FMC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_0004    crg_fmc1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_FMC_CRG_FMC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_0008    crg_fmc2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi2_clk_gate_en      :  1,    //      1
    reg_axi_clk_gate_en       :  1,    //      2
    reg_de_clk_gate_en        :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_FMC_CRG_FMC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_000C    crg_fmc3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi2_n       :  1,    //      1
    reg_soft_rst_axi_n        :  1,    //      2
    reg_soft_rst_de_n         :  1,    //      3
    reg_soft_rst_f_gsc_8_de_bnd_n: 1,    //    4
    reg_soft_rst_h_fmc_0_de_bnd_n: 1,    //    5
    reg_soft_rst_h_fmc_1_de_bnd_n: 1,    //    6
    reg_soft_rst_h_fmc_2_de_bnd_n: 1,    //    7
    reg_soft_rst_h_fmc_3_de_bnd_n: 1,    //    8
    reg_soft_rst_h_fmc_4_de_bnd_n: 1,    //    9
    reg_soft_rst_h_fmc_5_de_bnd_n: 1,    //   10
    reg_soft_rst_h_fmc_6_de_bnd_n: 1,    //   11
    reg_soft_rst_h_fmc_7_de_bnd_n: 1,    //   12
    reg_soft_rst_h_fmc_8_de_bnd_n: 1,    //   13
    reg_soft_rst_h_gsc_10_de_bnd_n: 1,    //  14
    reg_soft_rst_h_gsc_11_de_bnd_n: 1,    //  15
    reg_soft_rst_h_gsc_12_de_bnd_n: 1,    //  16
    reg_soft_rst_h_gsc_9_de_bnd_n: 1,    //   17
    reg_soft_rst_h_sre_2_de_bnd_n: 1,    //   18
    reg_soft_rst_h_sre_3_de_bnd_n: 1,    //   19
    reg_soft_rst_p_fmc_0_axi_bnd_n: 1,    //  20
    reg_soft_rst_p_fmc_1_axi_bnd_n: 1,    //  21
    reg_soft_rst_p_fmc_2_axi_bnd_n: 1,    //  22
    reg_soft_rst_p_fmc_3_axi_bnd_n: 1,    //  23
    reg_soft_rst_p_fmc_4_axi_bnd_n: 1,    //  24
    reg_soft_rst_p_fmc_5_axi_bnd_n: 1,    //  25
    reg_soft_rst_x_fmc_0_axi_bnd_n: 1,    //  26
    reg_soft_rst_x_fmc_0_axi_n:  1,    //     27
    reg_soft_rst_x_fmc_1_axi_bnd_n: 1,    //  28
    reg_soft_rst_x_fmc_1_axi_n:  1,    //     29
    reg_soft_rst_x_fmc_2_axi_bnd_n: 1,    //  30
    reg_soft_rst_x_fmc_2_axi_n:  1;    //     31
}SCRG_CTRL_FMC_CRG_FMC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_0010    crg_fmc4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_x_fmc_3_axi_bnd_n: 1,    //   0
    reg_soft_rst_x_fmc_3_axi_n:  1,    //      1
    reg_soft_rst_x_fmc_4_axi_bnd_n: 1,    //   2
    reg_soft_rst_x_fmc_4_axi_n:  1,    //      3
    reg_soft_rst_x_fmc_5_axi_bnd_n: 1,    //   4
    reg_soft_rst_x_fmc_5_axi_n:  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_FMC_CRG_FMC4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMC_CRG_FMC0_O24A0_T     crg_fmc0   ;             // 0xCC43_0000
    SCRG_CTRL_FMC_CRG_FMC1_O24A0_T     crg_fmc1   ;             // 0xCC43_0004
    SCRG_CTRL_FMC_CRG_FMC2_O24A0_T     crg_fmc2   ;             // 0xCC43_0008
    SCRG_CTRL_FMC_CRG_FMC3_O24A0_T     crg_fmc3   ;             // 0xCC43_000C
    SCRG_CTRL_FMC_CRG_FMC4_O24A0_T     crg_fmc4   ;             // 0xCC43_0010
}SCRG_CTRL_FMC_REG_O24A0_T;
/* 5 regs */

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

#define SCRG_CTRL_FMC_CRG_FMC0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_FMC_CRG_FMC1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_FMC_CRG_FMC2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_FMC_CRG_FMC3_O24A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_FMC_CRG_FMC4_O24A0_T_OFF                  (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC43_0000    crg_fmc0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_FMC_CRG_FMC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_0004    crg_fmc1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_FMC_CRG_FMC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_0008    crg_fmc2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi2_clk_gate_en: 1;    //      1
    UINT32 reg_axi_clk_gate_en:  1;    //      2
    UINT32 reg_de_clk_gate_en :  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_FMC_CRG_FMC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_000C    crg_fmc3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi2_n:  1;    //      1
    UINT32 reg_soft_rst_axi_n :  1;    //      2
    UINT32 reg_soft_rst_de_n  :  1;    //      3
    UINT32 reg_soft_rst_f_gsc_8_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_fmc_0_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_fmc_1_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_fmc_2_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_fmc_3_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_fmc_4_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_fmc_5_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_fmc_6_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_fmc_7_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_fmc_8_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_gsc_10_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_gsc_11_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_gsc_12_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_gsc_9_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_h_sre_2_de_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_h_sre_3_de_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_p_fmc_0_axi_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_p_fmc_1_axi_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_p_fmc_2_axi_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_p_fmc_3_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_p_fmc_4_axi_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_p_fmc_5_axi_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_x_fmc_0_axi_bnd_n: 1;    //  26
    UINT32 reg_soft_rst_x_fmc_0_axi_n: 1;    //  27
    UINT32 reg_soft_rst_x_fmc_1_axi_bnd_n: 1;    //  28
    UINT32 reg_soft_rst_x_fmc_1_axi_n: 1;    //  29
    UINT32 reg_soft_rst_x_fmc_2_axi_bnd_n: 1;    //  30
    UINT32 reg_soft_rst_x_fmc_2_axi_n: 1;    //  31
    };
}SCRG_CTRL_FMC_CRG_FMC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC43_0010    crg_fmc4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_x_fmc_3_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_x_fmc_3_axi_n: 1;    //  1
    UINT32 reg_soft_rst_x_fmc_4_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_x_fmc_4_axi_n: 1;    //  3
    UINT32 reg_soft_rst_x_fmc_5_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_fmc_5_axi_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_FMC_CRG_FMC4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMC_CRG_FMC0_O24A0_T     crg_fmc0   ;             // 0xCC43_0000
    SCRG_CTRL_FMC_CRG_FMC1_O24A0_T     crg_fmc1   ;             // 0xCC43_0004
    SCRG_CTRL_FMC_CRG_FMC2_O24A0_T     crg_fmc2   ;             // 0xCC43_0008
    SCRG_CTRL_FMC_CRG_FMC3_O24A0_T     crg_fmc3   ;             // 0xCC43_000C
    SCRG_CTRL_FMC_CRG_FMC4_O24A0_T     crg_fmc4   ;             // 0xCC43_0010
}SCRG_CTRL_FMC_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_FMC_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

