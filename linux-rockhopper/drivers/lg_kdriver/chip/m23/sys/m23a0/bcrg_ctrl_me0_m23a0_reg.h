#ifndef _BCRG_CTRL_ME0_M23A0_REG_H_
#define _BCRG_CTRL_ME0_M23A0_REG_H_

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
    0xCCA0_1000    crg_bnd_me000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ME0_CRG_BND_ME000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA0_1004    crg_bnd_me001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ME0_CRG_BND_ME001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA0_1008    crg_bnd_me002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_lne_clk_gate_en: 1,    //      0
    reg_apb_ipw_me_clk_gate_en:  1,    //      1
    reg_apb_ipw_sb_epu_clk_gate_en: 1,    //   2
    reg_apb_ipw_usb_hs2_clk_gate_en: 1,    //  3
    reg_apb_ipw_usb_hs3_clk_gate_en: 1,    //  4
    reg_apb_ipw_venc_clk_gate_en: 1,    //     5
                              : 26;    //   31:6 reserved
}BCRG_CTRL_ME0_CRG_BND_ME002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA0_100C    crg_bnd_me003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_fms_0_n: 1,    //    0
    reg_soft_rst_fly_brdg_cco_1_n: 1,    //    1
    reg_soft_rst_fly_brdg_gsc_4_n: 1,    //    2
    reg_soft_rst_fly_brdg_imx_4_n: 1,    //    3
    reg_soft_rst_fly_brdg_tp_int_n: 1,    //   4
    reg_soft_rst_fly_brdg_vsd_0_n: 1,    //    5
    reg_soft_rst_hsp_brdg_fmc_0_n: 1,    //    6
    reg_soft_rst_hsp_brdg_fmc_1_n: 1,    //    7
    reg_soft_rst_hsp_brdg_fmc_2_n: 1,    //    8
    reg_soft_rst_hsp_brdg_fmc_3_n: 1,    //    9
    reg_soft_rst_hsp_brdg_gsc_0_n: 1,    //   10
    reg_soft_rst_hsp_brdg_gsc_1_n: 1,    //   11
    reg_soft_rst_hsp_brdg_gsc_5_n: 1,    //   12
    reg_soft_rst_hsp_brdg_gsc_6_n: 1,    //   13
                              : 18;    //  31:14 reserved
}BCRG_CTRL_ME0_CRG_BND_ME003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA0_1010    crg_bnd_me004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_lne_n:  1,    //      0
    reg_soft_rst_apb_ipw_me_n :  1,    //      1
    reg_soft_rst_apb_ipw_sb_epu_n: 1,    //    2
    reg_soft_rst_apb_ipw_usb_hs2_n: 1,    //   3
    reg_soft_rst_apb_ipw_usb_hs3_n: 1,    //   4
    reg_soft_rst_apb_ipw_venc_n: 1,    //      5
                              : 26;    //   31:6 reserved
}BCRG_CTRL_ME0_CRG_BND_ME004_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME0_CRG_BND_ME000_M23A0_T    crg_bnd_me000;       // 0xCCA0_1000
    BCRG_CTRL_ME0_CRG_BND_ME001_M23A0_T    crg_bnd_me001;       // 0xCCA0_1004
    BCRG_CTRL_ME0_CRG_BND_ME002_M23A0_T    crg_bnd_me002;       // 0xCCA0_1008
    BCRG_CTRL_ME0_CRG_BND_ME003_M23A0_T    crg_bnd_me003;       // 0xCCA0_100C
    BCRG_CTRL_ME0_CRG_BND_ME004_M23A0_T    crg_bnd_me004;       // 0xCCA0_1010
}BCRG_CTRL_ME0_REG_M23A0_T;
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

#define BCRG_CTRL_ME0_CRG_BND_ME000_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_ME0_CRG_BND_ME001_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_ME0_CRG_BND_ME002_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_ME0_CRG_BND_ME003_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_ME0_CRG_BND_ME004_M23A0_T_OFF             (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCA0_1000    crg_bnd_me000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ME0_CRG_BND_ME000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA0_1004    crg_bnd_me001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ME0_CRG_BND_ME001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA0_1008    crg_bnd_me002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_lne_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_me_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_sb_epu_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_usb_hs2_clk_gate_en: 1;    //  3
    UINT32 reg_apb_ipw_usb_hs3_clk_gate_en: 1;    //  4
    UINT32 reg_apb_ipw_venc_clk_gate_en: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA0_100C    crg_bnd_me003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_fms_0_n: 1;    //  0
    UINT32 reg_soft_rst_fly_brdg_cco_1_n: 1;    //  1
    UINT32 reg_soft_rst_fly_brdg_gsc_4_n: 1;    //  2
    UINT32 reg_soft_rst_fly_brdg_imx_4_n: 1;    //  3
    UINT32 reg_soft_rst_fly_brdg_tp_int_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_vsd_0_n: 1;    //  5
    UINT32 reg_soft_rst_hsp_brdg_fmc_0_n: 1;    //  6
    UINT32 reg_soft_rst_hsp_brdg_fmc_1_n: 1;    //  7
    UINT32 reg_soft_rst_hsp_brdg_fmc_2_n: 1;    //  8
    UINT32 reg_soft_rst_hsp_brdg_fmc_3_n: 1;    //  9
    UINT32 reg_soft_rst_hsp_brdg_gsc_0_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_gsc_1_n: 1;    //  11
    UINT32 reg_soft_rst_hsp_brdg_gsc_5_n: 1;    //  12
    UINT32 reg_soft_rst_hsp_brdg_gsc_6_n: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA0_1010    crg_bnd_me004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_lne_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_me_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_sb_epu_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_usb_hs2_n: 1;    //  3
    UINT32 reg_soft_rst_apb_ipw_usb_hs3_n: 1;    //  4
    UINT32 reg_soft_rst_apb_ipw_venc_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME004_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME0_CRG_BND_ME000_M23A0_T    crg_bnd_me000;       // 0xCCA0_1000
    BCRG_CTRL_ME0_CRG_BND_ME001_M23A0_T    crg_bnd_me001;       // 0xCCA0_1004
    BCRG_CTRL_ME0_CRG_BND_ME002_M23A0_T    crg_bnd_me002;       // 0xCCA0_1008
    BCRG_CTRL_ME0_CRG_BND_ME003_M23A0_T    crg_bnd_me003;       // 0xCCA0_100C
    BCRG_CTRL_ME0_CRG_BND_ME004_M23A0_T    crg_bnd_me004;       // 0xCCA0_1010
}BCRG_CTRL_ME0_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

