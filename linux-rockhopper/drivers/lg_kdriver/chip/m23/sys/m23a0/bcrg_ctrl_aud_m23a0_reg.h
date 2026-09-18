#ifndef _BCRG_CTRL_AUD_M23A0_REG_H_
#define _BCRG_CTRL_AUD_M23A0_REG_H_

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
    0xCECB_1000    crg_bnd_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_AUD_CRG_BND_AUD00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_1004    crg_bnd_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_AUD_CRG_BND_AUD01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_1008    crg_bnd_aud02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_aud_clk_gate_en: 1,    //      0
    reg_apb_ipw_icod_clk_gate_en: 1,    //     1
    reg_apb_ipw_sb_tiv_clk_gate_en: 1,    //   2
    reg_apb_ipw_te_clk_gate_en:  1,    //      3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_AUD_CRG_BND_AUD02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_100C    crg_bnd_aud03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_cpu_1_n: 1,    //    0
    reg_soft_rst_axi_brdg_epusb_0_n: 1,    //  1
    reg_soft_rst_axi_brdg_fms_0_n: 1,    //    2
    reg_soft_rst_axi_brdg_lne_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_me_0_n: 1,    //     4
    reg_soft_rst_axi_brdg_micom_1_n: 1,    //  5
    reg_soft_rst_f_tp_int_n   :  1,    //      6
    reg_soft_rst_fly_brdg_cco_1_n: 1,    //    7
    reg_soft_rst_fly_brdg_imx_4_n: 1,    //    8
    reg_soft_rst_fly_brdg_me_0_n: 1,    //     9
    reg_soft_rst_fly_brdg_vsd_0_n: 1,    //   10
    reg_soft_rst_hsp_brdg_gsc_0_n: 1,    //   11
    reg_soft_rst_hsp_brdg_gsc_1_n: 1,    //   12
                              : 19;    //  31:13 reserved
}BCRG_CTRL_AUD_CRG_BND_AUD03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_1010    crg_bnd_aud04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_aud_n:  1,    //      0
    reg_soft_rst_apb_ipw_icod_n: 1,    //      1
    reg_soft_rst_apb_ipw_sb_tiv_n: 1,    //    2
    reg_soft_rst_apb_ipw_te_n :  1,    //      3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_AUD_CRG_BND_AUD04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_AUD_CRG_BND_AUD00_M23A0_T    crg_bnd_aud00;       // 0xCECB_1000
    BCRG_CTRL_AUD_CRG_BND_AUD01_M23A0_T    crg_bnd_aud01;       // 0xCECB_1004
    BCRG_CTRL_AUD_CRG_BND_AUD02_M23A0_T    crg_bnd_aud02;       // 0xCECB_1008
    BCRG_CTRL_AUD_CRG_BND_AUD03_M23A0_T    crg_bnd_aud03;       // 0xCECB_100C
    BCRG_CTRL_AUD_CRG_BND_AUD04_M23A0_T    crg_bnd_aud04;       // 0xCECB_1010
}BCRG_CTRL_AUD_REG_M23A0_T;
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

#define BCRG_CTRL_AUD_CRG_BND_AUD00_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_AUD_CRG_BND_AUD01_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_AUD_CRG_BND_AUD02_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_AUD_CRG_BND_AUD03_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_AUD_CRG_BND_AUD04_M23A0_T_OFF             (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCECB_1000    crg_bnd_aud00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_AUD_CRG_BND_AUD00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_1004    crg_bnd_aud01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_AUD_CRG_BND_AUD01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_1008    crg_bnd_aud02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_aud_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_icod_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_sb_tiv_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_te_clk_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_AUD_CRG_BND_AUD02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_100C    crg_bnd_aud03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_cpu_1_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_epusb_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_fms_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_lne_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_me_0_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_micom_1_n: 1;    //  5
    UINT32 reg_soft_rst_f_tp_int_n: 1;    //   6
    UINT32 reg_soft_rst_fly_brdg_cco_1_n: 1;    //  7
    UINT32 reg_soft_rst_fly_brdg_imx_4_n: 1;    //  8
    UINT32 reg_soft_rst_fly_brdg_me_0_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_vsd_0_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_gsc_0_n: 1;    //  11
    UINT32 reg_soft_rst_hsp_brdg_gsc_1_n: 1;    //  12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}BCRG_CTRL_AUD_CRG_BND_AUD03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCECB_1010    crg_bnd_aud04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_aud_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_icod_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_sb_tiv_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_te_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_AUD_CRG_BND_AUD04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_AUD_CRG_BND_AUD00_M23A0_T    crg_bnd_aud00;       // 0xCECB_1000
    BCRG_CTRL_AUD_CRG_BND_AUD01_M23A0_T    crg_bnd_aud01;       // 0xCECB_1004
    BCRG_CTRL_AUD_CRG_BND_AUD02_M23A0_T    crg_bnd_aud02;       // 0xCECB_1008
    BCRG_CTRL_AUD_CRG_BND_AUD03_M23A0_T    crg_bnd_aud03;       // 0xCECB_100C
    BCRG_CTRL_AUD_CRG_BND_AUD04_M23A0_T    crg_bnd_aud04;       // 0xCECB_1010
}BCRG_CTRL_AUD_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

