#ifndef _BCRG_CTRL_WOV_REG_H_
#define _BCRG_CTRL_WOV_REG_H_

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
    0x5B_0000    crg_bnd_wov00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_WOV_CRG_BND_WOV00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5B_0004    crg_bnd_wov01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_WOV_CRG_BND_WOV01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5B_0008    crg_bnd_wov02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_aud_clk_gate_en: 1,    //      0
    reg_apb_ipw_icod_clk_gate_en: 1,    //     1
    reg_apb_ipw_micom_clk_gate_en: 1,    //    2
    reg_apb_ipw_venc_clk_gate_en: 1,    //     3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_WOV_CRG_BND_WOV02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5B_000C    crg_bnd_wov03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_3x3_sb_apb_bnd_n: 1,    //    0
    reg_soft_rst_apb_audipc_cpu_bnd_n: 1,    //  1
    reg_soft_rst_apb_pa_lgsr_bnd_n: 1,    //   2
    reg_soft_rst_apb_pm_m1_bnd_n: 1,    //     3
    reg_soft_rst_apb_vd2_pv0_bnd_n: 1,    //   4
    reg_soft_rst_fly_brdg_te_0_n: 1,    //     5
    reg_soft_rst_fly_brdg_te_1_n: 1,    //     6
    reg_soft_rst_x_aud_s1_axi_sbw_n: 1,    //  7
    reg_soft_rst_x_aud_s2_axi_sbw_n: 1,    //  8
    reg_soft_rst_x_ddr_m0_axi_sbw_n: 1,    //  9
    reg_soft_rst_x_lbus_m1_axi_sbw_n: 1,    //  10
    reg_soft_rst_x_lbus_m2_axi_sbw_n: 1,    //  11
    reg_soft_rst_x_micom_s0_axi_sbw_n: 1,    //  12
    reg_soft_sbw_aresetn_240  :  1,    //     13
    reg_soft_sbw_aresetn_400  :  1,    //     14
    reg_soft_sbw_aresetn_480  :  1,    //     15
                              : 16;    //  31:16 reserved
}BCRG_CTRL_WOV_CRG_BND_WOV03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5B_0010    crg_bnd_wov04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_aud_n:  1,    //      0
    reg_soft_rst_apb_ipw_icod_n: 1,    //      1
    reg_soft_rst_apb_ipw_micom_n: 1,    //     2
    reg_soft_rst_apb_ipw_venc_n: 1,    //      3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_WOV_CRG_BND_WOV04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5B_0014    crg_bnd_wov05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fly_brdg_te_0_clk_sel :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_fly_brdg_te_1_clk_sel :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_apb_bnd_clk_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_sbw_aclk_240_sel      :  1,    //     12
                              : 19;    //  31:13 reserved
}BCRG_CTRL_WOV_CRG_BND_WOV05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_WOV_CRG_BND_WOV00_O22A0_T    crg_bnd_wov00;         // 0x5B_0000
    BCRG_CTRL_WOV_CRG_BND_WOV01_O22A0_T    crg_bnd_wov01;         // 0x5B_0004
    BCRG_CTRL_WOV_CRG_BND_WOV02_O22A0_T    crg_bnd_wov02;         // 0x5B_0008
    BCRG_CTRL_WOV_CRG_BND_WOV03_O22A0_T    crg_bnd_wov03;         // 0x5B_000C
    BCRG_CTRL_WOV_CRG_BND_WOV04_O22A0_T    crg_bnd_wov04;         // 0x5B_0010
    BCRG_CTRL_WOV_CRG_BND_WOV05_O22A0_T    crg_bnd_wov05;         // 0x5B_0014
}BCRG_CTRL_WOV_REG_O22A0_T;
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

#define BCRG_CTRL_WOV_CRG_BND_WOV00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_WOV_CRG_BND_WOV01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_WOV_CRG_BND_WOV02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_WOV_CRG_BND_WOV03_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_WOV_CRG_BND_WOV04_O22A0_T_OFF               (BASEADDRESS+0x0010)
#define BCRG_CTRL_WOV_CRG_BND_WOV05_O22A0_T_OFF               (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0x5B_0000    crg_bnd_wov00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_WOV_CRG_BND_WOV00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5B_0004    crg_bnd_wov01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_WOV_CRG_BND_WOV01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5B_0008    crg_bnd_wov02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_aud_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_icod_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_micom_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_venc_clk_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_WOV_CRG_BND_WOV02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5B_000C    crg_bnd_wov03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_3x3_sb_apb_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_apb_audipc_cpu_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_apb_pa_lgsr_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_apb_pm_m1_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_apb_vd2_pv0_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_te_0_n: 1;    //  5
    UINT32 reg_soft_rst_fly_brdg_te_1_n: 1;    //  6
    UINT32 reg_soft_rst_x_aud_s1_axi_sbw_n: 1;    //  7
    UINT32 reg_soft_rst_x_aud_s2_axi_sbw_n: 1;    //  8
    UINT32 reg_soft_rst_x_ddr_m0_axi_sbw_n: 1;    //  9
    UINT32 reg_soft_rst_x_lbus_m1_axi_sbw_n: 1;    //  10
    UINT32 reg_soft_rst_x_lbus_m2_axi_sbw_n: 1;    //  11
    UINT32 reg_soft_rst_x_micom_s0_axi_sbw_n: 1;    //  12
    UINT32 reg_soft_sbw_aresetn_240: 1;    //  13
    UINT32 reg_soft_sbw_aresetn_400: 1;    //  14
    UINT32 reg_soft_sbw_aresetn_480: 1;    //  15
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}BCRG_CTRL_WOV_CRG_BND_WOV03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5B_0010    crg_bnd_wov04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_aud_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_icod_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_micom_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_venc_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_WOV_CRG_BND_WOV04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5B_0014    crg_bnd_wov05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fly_brdg_te_0_clk_sel: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_fly_brdg_te_1_clk_sel: 1;    //  4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_apb_bnd_clk_sel:  1;    //      8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_sbw_aclk_240_sel: 1;    //     12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}BCRG_CTRL_WOV_CRG_BND_WOV05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_WOV_CRG_BND_WOV00_O22A0_T    crg_bnd_wov00;         // 0x5B_0000
    BCRG_CTRL_WOV_CRG_BND_WOV01_O22A0_T    crg_bnd_wov01;         // 0x5B_0004
    BCRG_CTRL_WOV_CRG_BND_WOV02_O22A0_T    crg_bnd_wov02;         // 0x5B_0008
    BCRG_CTRL_WOV_CRG_BND_WOV03_O22A0_T    crg_bnd_wov03;         // 0x5B_000C
    BCRG_CTRL_WOV_CRG_BND_WOV04_O22A0_T    crg_bnd_wov04;         // 0x5B_0010
    BCRG_CTRL_WOV_CRG_BND_WOV05_O22A0_T    crg_bnd_wov05;         // 0x5B_0014
}BCRG_CTRL_WOV_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

