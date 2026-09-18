#ifndef _BCRG_CTRL_DPE_REG_H_
#define _BCRG_CTRL_DPE_REG_H_

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
    0x12_0000    crg_bnd_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_DPE_CRG_BND_DPE00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x12_0004    crg_bnd_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_DPE_CRG_BND_DPE01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x12_0008    crg_bnd_dpe02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_led_clk_gate_en: 1,    //      0
    reg_apb_ipw_tcon_clk_gate_en: 1,    //     1
    reg_apb_ipw_vsd_clk_gate_en: 1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_DPE_CRG_BND_DPE02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x12_000C    crg_bnd_dpe03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_brdg_wov_0_n: 1,    //    0
    reg_soft_rst_fly_brdg_gsc_6_n: 1,    //    1
    reg_soft_rst_hsp_brdg_fmc_0_n: 1,    //    2
    reg_soft_rst_hsp_brdg_fmc_1_n: 1,    //    3
    reg_soft_rst_hsp_brdg_fmc_2_n: 1,    //    4
    reg_soft_rst_hsp_brdg_fmc_3_n: 1,    //    5
    reg_soft_rst_hsp_brdg_fmc_4_n: 1,    //    6
    reg_soft_rst_hsp_brdg_fmc_5_n: 1,    //    7
    reg_soft_rst_hsp_brdg_gsc_10_n: 1,    //   8
    reg_soft_rst_hsp_brdg_gsc_7_n: 1,    //    9
    reg_soft_rst_hsp_brdg_gsc_8_n: 1,    //   10
    reg_soft_rst_hsp_brdg_gsc_9_n: 1,    //   11
                              : 20;    //  31:12 reserved
}BCRG_CTRL_DPE_CRG_BND_DPE03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x12_0010    crg_bnd_dpe04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_led_n:  1,    //      0
    reg_soft_rst_apb_ipw_tcon_n: 1,    //      1
    reg_soft_rst_apb_ipw_vsd_n:  1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_DPE_CRG_BND_DPE04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DPE_CRG_BND_DPE00_O22A0_T    crg_bnd_dpe00;         // 0x12_0000
    BCRG_CTRL_DPE_CRG_BND_DPE01_O22A0_T    crg_bnd_dpe01;         // 0x12_0004
    BCRG_CTRL_DPE_CRG_BND_DPE02_O22A0_T    crg_bnd_dpe02;         // 0x12_0008
    BCRG_CTRL_DPE_CRG_BND_DPE03_O22A0_T    crg_bnd_dpe03;         // 0x12_000C
    BCRG_CTRL_DPE_CRG_BND_DPE04_O22A0_T    crg_bnd_dpe04;         // 0x12_0010
}BCRG_CTRL_DPE_REG_O22A0_T;
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

#define BCRG_CTRL_DPE_CRG_BND_DPE00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_DPE_CRG_BND_DPE01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_DPE_CRG_BND_DPE02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_DPE_CRG_BND_DPE03_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_DPE_CRG_BND_DPE04_O22A0_T_OFF               (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x12_0000    crg_bnd_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_DPE_CRG_BND_DPE00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x12_0004    crg_bnd_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_DPE_CRG_BND_DPE01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x12_0008    crg_bnd_dpe02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_led_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_tcon_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_vsd_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_DPE_CRG_BND_DPE02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x12_000C    crg_bnd_dpe03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_brdg_wov_0_n: 1;    //  0
    UINT32 reg_soft_rst_fly_brdg_gsc_6_n: 1;    //  1
    UINT32 reg_soft_rst_hsp_brdg_fmc_0_n: 1;    //  2
    UINT32 reg_soft_rst_hsp_brdg_fmc_1_n: 1;    //  3
    UINT32 reg_soft_rst_hsp_brdg_fmc_2_n: 1;    //  4
    UINT32 reg_soft_rst_hsp_brdg_fmc_3_n: 1;    //  5
    UINT32 reg_soft_rst_hsp_brdg_fmc_4_n: 1;    //  6
    UINT32 reg_soft_rst_hsp_brdg_fmc_5_n: 1;    //  7
    UINT32 reg_soft_rst_hsp_brdg_gsc_10_n: 1;    //  8
    UINT32 reg_soft_rst_hsp_brdg_gsc_7_n: 1;    //  9
    UINT32 reg_soft_rst_hsp_brdg_gsc_8_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_gsc_9_n: 1;    //  11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}BCRG_CTRL_DPE_CRG_BND_DPE03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x12_0010    crg_bnd_dpe04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_led_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_tcon_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_vsd_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_DPE_CRG_BND_DPE04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DPE_CRG_BND_DPE00_O22A0_T    crg_bnd_dpe00;         // 0x12_0000
    BCRG_CTRL_DPE_CRG_BND_DPE01_O22A0_T    crg_bnd_dpe01;         // 0x12_0004
    BCRG_CTRL_DPE_CRG_BND_DPE02_O22A0_T    crg_bnd_dpe02;         // 0x12_0008
    BCRG_CTRL_DPE_CRG_BND_DPE03_O22A0_T    crg_bnd_dpe03;         // 0x12_000C
    BCRG_CTRL_DPE_CRG_BND_DPE04_O22A0_T    crg_bnd_dpe04;         // 0x12_0010
}BCRG_CTRL_DPE_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

