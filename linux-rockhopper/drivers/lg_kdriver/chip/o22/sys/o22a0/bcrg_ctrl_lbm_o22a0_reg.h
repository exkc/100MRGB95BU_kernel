#ifndef _BCRG_CTRL_LBM_REG_H_
#define _BCRG_CTRL_LBM_REG_H_

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
    0x2E_0000    crg_bnd_lbm00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_LBM_CRG_BND_LBM00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2E_0004    crg_bnd_lbm01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_LBM_CRG_BND_LBM01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2E_0008    crg_bnd_lbm02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ts_clk_gate_en        :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2E_000C    crg_bnd_lbm03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_lbus_clk_gate_en: 1,    //     0
    reg_apb_ipw_mcu_clk_gate_en: 1,    //      1
    reg_apb_ipw_vdec_mcu_clk_gate_en: 1,    //  2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2E_0010    crg_bnd_lbm04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_pes_fly_brdg_te_4_n: 1,    //     0
    reg_soft_pes_fly_brdg_te_5_n: 1,    //     1
    reg_soft_rst_apb_brdg_cpu_0_n: 1,    //    2
    reg_soft_rst_apb_brdg_wov_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_cpu_1_n: 1,    //    4
    reg_soft_rst_axi_brdg_cpu_3_n: 1,    //    5
    reg_soft_rst_axi_brdg_micom_1_n: 1,    //  6
    reg_soft_rst_e_te_6_te_bnd_n: 1,    //     7
    reg_soft_rst_e_te_7_te_bnd_n: 1,    //     8
    reg_soft_rst_f_te_0_bnd_n :  1,    //      9
    reg_soft_rst_f_te_1_bnd_n :  1,    //     10
    reg_soft_rst_f_te_2_bnd_n :  1,    //     11
    reg_soft_rst_f_te_3_bnd_n :  1,    //     12
    reg_soft_rst_fly_brdg_cco_5_n: 1,    //   13
    reg_soft_rst_fly_brdg_imx_16_n: 1,    //  14
    reg_soft_rst_fly_brdg_vd0_0_n: 1,    //   15
    reg_soft_rst_fly_brdg_vd1_0_n: 1,    //   16
    reg_soft_rst_hsp_brdg_sre_2_n: 1,    //   17
    reg_soft_rst_hsp_brdg_sre_3_n: 1,    //   18
    reg_soft_rst_ts_n         :  1,    //     19
    reg_soft_sbw_aresetn_400  :  1,    //     20
    reg_soft_sbw_aresetn_480  :  1,    //     21
                              : 10;    //  31:22 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2E_0014    crg_bnd_lbm05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_lbus_n: 1,    //      0
    reg_soft_rst_apb_ipw_mcu_n:  1,    //      1
    reg_soft_rst_apb_ipw_vdec_mcu_n: 1,    //  2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_LBM_CRG_BND_LBM05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_lbm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LBM_CRG_BND_LBM00_O22A0_T    crg_bnd_lbm00;         // 0x2E_0000
    BCRG_CTRL_LBM_CRG_BND_LBM01_O22A0_T    crg_bnd_lbm01;         // 0x2E_0004
    BCRG_CTRL_LBM_CRG_BND_LBM02_O22A0_T    crg_bnd_lbm02;         // 0x2E_0008
    BCRG_CTRL_LBM_CRG_BND_LBM03_O22A0_T    crg_bnd_lbm03;         // 0x2E_000C
    BCRG_CTRL_LBM_CRG_BND_LBM04_O22A0_T    crg_bnd_lbm04;         // 0x2E_0010
    BCRG_CTRL_LBM_CRG_BND_LBM05_O22A0_T    crg_bnd_lbm05;         // 0x2E_0014
}BCRG_CTRL_LBM_REG_O22A0_T;
/* 6 regs */

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

#define BCRG_CTRL_LBM_CRG_BND_LBM00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_LBM_CRG_BND_LBM01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_LBM_CRG_BND_LBM02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_LBM_CRG_BND_LBM03_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_LBM_CRG_BND_LBM04_O22A0_T_OFF               (BASEADDRESS+0x0010)
#define BCRG_CTRL_LBM_CRG_BND_LBM05_O22A0_T_OFF               (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0x2E_0000    crg_bnd_lbm00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_LBM_CRG_BND_LBM00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2E_0004    crg_bnd_lbm01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_LBM_CRG_BND_LBM01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2E_0008    crg_bnd_lbm02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ts_clk_gate_en :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2E_000C    crg_bnd_lbm03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_lbus_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_mcu_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_vdec_mcu_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2E_0010    crg_bnd_lbm04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_pes_fly_brdg_te_4_n: 1;    //  0
    UINT32 reg_soft_pes_fly_brdg_te_5_n: 1;    //  1
    UINT32 reg_soft_rst_apb_brdg_cpu_0_n: 1;    //  2
    UINT32 reg_soft_rst_apb_brdg_wov_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_cpu_1_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_cpu_3_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_micom_1_n: 1;    //  6
    UINT32 reg_soft_rst_e_te_6_te_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_e_te_7_te_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_te_0_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_te_1_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_te_2_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_te_3_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_fly_brdg_cco_5_n: 1;    //  13
    UINT32 reg_soft_rst_fly_brdg_imx_16_n: 1;    //  14
    UINT32 reg_soft_rst_fly_brdg_vd0_0_n: 1;    //  15
    UINT32 reg_soft_rst_fly_brdg_vd1_0_n: 1;    //  16
    UINT32 reg_soft_rst_hsp_brdg_sre_2_n: 1;    //  17
    UINT32 reg_soft_rst_hsp_brdg_sre_3_n: 1;    //  18
    UINT32 reg_soft_rst_ts_n  :  1;    //     19
    UINT32 reg_soft_sbw_aresetn_400: 1;    //  20
    UINT32 reg_soft_sbw_aresetn_480: 1;    //  21
    UINT32 resvd00            : 10;    //  31:22 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2E_0014    crg_bnd_lbm05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_lbus_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_mcu_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_vdec_mcu_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_LBM_CRG_BND_LBM05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_lbm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LBM_CRG_BND_LBM00_O22A0_T    crg_bnd_lbm00;         // 0x2E_0000
    BCRG_CTRL_LBM_CRG_BND_LBM01_O22A0_T    crg_bnd_lbm01;         // 0x2E_0004
    BCRG_CTRL_LBM_CRG_BND_LBM02_O22A0_T    crg_bnd_lbm02;         // 0x2E_0008
    BCRG_CTRL_LBM_CRG_BND_LBM03_O22A0_T    crg_bnd_lbm03;         // 0x2E_000C
    BCRG_CTRL_LBM_CRG_BND_LBM04_O22A0_T    crg_bnd_lbm04;         // 0x2E_0010
    BCRG_CTRL_LBM_CRG_BND_LBM05_O22A0_T    crg_bnd_lbm05;         // 0x2E_0014
}BCRG_CTRL_LBM_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

