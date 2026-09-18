#ifndef _BCRG_CTRL_LBM_REG_O24A0_H_
#define _BCRG_CTRL_LBM_REG_O24A0_H_

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
    0xC419_1000    crg_bnd_lbm0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_LBM_CRG_BND_LBM0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC419_1004    crg_bnd_lbm1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_LBM_CRG_BND_LBM1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC419_1008    crg_bnd_lbm2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_dmcu_clk_gate_en: 1,    //     0
    reg_apb_ipw_gfx_clk_gate_en: 1,    //      1
    reg_apb_ipw_lbus_clk_gate_en: 1,    //     2
    reg_apb_ipw_sb_ddr0_clk_gate_en: 1,    //  3
    reg_apb_ipw_sb_ddr1_clk_gate_en: 1,    //  4
    reg_apb_ipw_sb_ddr2_clk_gate_en: 1,    //  5
    reg_apb_ipw_sb_lb2_clk_gate_en: 1,    //   6
                              : 25;    //   31:7 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC419_100C    crg_bnd_lbm3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_fly_brdg_cco_7_n: 1,    //    0
    reg_soft_rst_fly_brdg_imx_12_n: 1,    //   1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC419_1010    crg_bnd_lbm4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_dmcu_n: 1,    //      0
    reg_soft_rst_apb_ipw_gfx_n:  1,    //      1
    reg_soft_rst_apb_ipw_lbus_n: 1,    //      2
    reg_soft_rst_apb_ipw_sb_ddr0_n: 1,    //   3
    reg_soft_rst_apb_ipw_sb_ddr1_n: 1,    //   4
    reg_soft_rst_apb_ipw_sb_ddr2_n: 1,    //   5
    reg_soft_rst_apb_ipw_sb_lb2_n: 1,    //    6
                              : 25;    //   31:7 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lbm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LBM_CRG_BND_LBM0_O24A0_T    crg_bnd_lbm0;         // 0xC419_1000
    BCRG_CTRL_LBM_CRG_BND_LBM1_O24A0_T    crg_bnd_lbm1;         // 0xC419_1004
    BCRG_CTRL_LBM_CRG_BND_LBM2_O24A0_T    crg_bnd_lbm2;         // 0xC419_1008
    BCRG_CTRL_LBM_CRG_BND_LBM3_O24A0_T    crg_bnd_lbm3;         // 0xC419_100C
    BCRG_CTRL_LBM_CRG_BND_LBM4_O24A0_T    crg_bnd_lbm4;         // 0xC419_1010
}BCRG_CTRL_LBM_REG_O24A0_T;
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

#define BCRG_CTRL_LBM_CRG_BND_LBM0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_LBM_CRG_BND_LBM1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_LBM_CRG_BND_LBM2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_LBM_CRG_BND_LBM3_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_LBM_CRG_BND_LBM4_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xC419_1000    crg_bnd_lbm0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_LBM_CRG_BND_LBM0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC419_1004    crg_bnd_lbm1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_LBM_CRG_BND_LBM1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC419_1008    crg_bnd_lbm2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_dmcu_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_gfx_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_lbus_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_sb_ddr0_clk_gate_en: 1;    //  3
    UINT32 reg_apb_ipw_sb_ddr1_clk_gate_en: 1;    //  4
    UINT32 reg_apb_ipw_sb_ddr2_clk_gate_en: 1;    //  5
    UINT32 reg_apb_ipw_sb_lb2_clk_gate_en: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC419_100C    crg_bnd_lbm3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_fly_brdg_cco_7_n: 1;    //  0
    UINT32 reg_soft_rst_fly_brdg_imx_12_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC419_1010    crg_bnd_lbm4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_dmcu_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_gfx_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_lbus_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_sb_ddr0_n: 1;    //  3
    UINT32 reg_soft_rst_apb_ipw_sb_ddr1_n: 1;    //  4
    UINT32 reg_soft_rst_apb_ipw_sb_ddr2_n: 1;    //  5
    UINT32 reg_soft_rst_apb_ipw_sb_lb2_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lbm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LBM_CRG_BND_LBM0_O24A0_T    crg_bnd_lbm0;         // 0xC419_1000
    BCRG_CTRL_LBM_CRG_BND_LBM1_O24A0_T    crg_bnd_lbm1;         // 0xC419_1004
    BCRG_CTRL_LBM_CRG_BND_LBM2_O24A0_T    crg_bnd_lbm2;         // 0xC419_1008
    BCRG_CTRL_LBM_CRG_BND_LBM3_O24A0_T    crg_bnd_lbm3;         // 0xC419_100C
    BCRG_CTRL_LBM_CRG_BND_LBM4_O24A0_T    crg_bnd_lbm4;         // 0xC419_1010
}BCRG_CTRL_LBM_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_LBM_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

