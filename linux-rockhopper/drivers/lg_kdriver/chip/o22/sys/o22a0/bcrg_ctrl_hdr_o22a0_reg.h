#ifndef _BCRG_CTRL_HDR_REG_H_
#define _BCRG_CTRL_HDR_REG_H_

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
    0x26_0000    crg_bnd_hdr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_HDR_CRG_BND_HDR00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x26_0004    crg_bnd_hdr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_HDR_CRG_BND_HDR01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x26_0008    crg_bnd_hdr02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_emmc_clk_gate_en: 1,    //     0
    reg_apb_ipw_hdr_clk_gate_en: 1,    //      1
    reg_apb_ipw_vdo_clk_gate_en: 1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_HDR_CRG_BND_HDR02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x26_000C    crg_bnd_hdr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_brdg_cvi_isol_n: 1,    //  0
    reg_soft_rst_apb_brdg_nd0_2_n: 1,    //    1
    reg_soft_rst_axi_brdg_cvd_0_n: 1,    //    2
    reg_soft_rst_axi_brdg_dne_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_dne_1_n: 1,    //    4
    reg_soft_rst_axi_brdg_imx_0_n: 1,    //    5
    reg_soft_rst_axi_brdg_imx_1_n: 1,    //    6
    reg_soft_rst_axi_brdg_imx_2_n: 1,    //    7
    reg_soft_rst_axi_brdg_imx_3_n: 1,    //    8
    reg_soft_rst_fly_brdg_cco_5_n: 1,    //    9
    reg_soft_rst_fly_brdg_imx_16_n: 1,    //  10
    reg_soft_rst_hsp_brdg_imx_10_n: 1,    //  11
    reg_soft_rst_hsp_brdg_imx_11_n: 1,    //  12
    reg_soft_rst_hsp_brdg_nd0_0_n: 1,    //   13
    reg_soft_rst_hsp_brdg_nd0_1_n: 1,    //   14
                              : 17;    //  31:15 reserved
}BCRG_CTRL_HDR_CRG_BND_HDR03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x26_0010    crg_bnd_hdr04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_emmc_n: 1,    //      0
    reg_soft_rst_apb_ipw_hdr_n:  1,    //      1
    reg_soft_rst_apb_ipw_vdo_n:  1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_HDR_CRG_BND_HDR04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_HDR_CRG_BND_HDR00_O22A0_T    crg_bnd_hdr00;         // 0x26_0000
    BCRG_CTRL_HDR_CRG_BND_HDR01_O22A0_T    crg_bnd_hdr01;         // 0x26_0004
    BCRG_CTRL_HDR_CRG_BND_HDR02_O22A0_T    crg_bnd_hdr02;         // 0x26_0008
    BCRG_CTRL_HDR_CRG_BND_HDR03_O22A0_T    crg_bnd_hdr03;         // 0x26_000C
    BCRG_CTRL_HDR_CRG_BND_HDR04_O22A0_T    crg_bnd_hdr04;         // 0x26_0010
}BCRG_CTRL_HDR_REG_O22A0_T;
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

#define BCRG_CTRL_HDR_CRG_BND_HDR00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_HDR_CRG_BND_HDR01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_HDR_CRG_BND_HDR02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_HDR_CRG_BND_HDR03_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_HDR_CRG_BND_HDR04_O22A0_T_OFF               (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x26_0000    crg_bnd_hdr00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_HDR_CRG_BND_HDR00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x26_0004    crg_bnd_hdr01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_HDR_CRG_BND_HDR01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x26_0008    crg_bnd_hdr02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_emmc_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_hdr_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_vdo_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_HDR_CRG_BND_HDR02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x26_000C    crg_bnd_hdr03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_brdg_cvi_isol_n: 1;    //  0
    UINT32 reg_soft_rst_apb_brdg_nd0_2_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_cvd_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_dne_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_dne_1_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_imx_0_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_imx_1_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_imx_2_n: 1;    //  7
    UINT32 reg_soft_rst_axi_brdg_imx_3_n: 1;    //  8
    UINT32 reg_soft_rst_fly_brdg_cco_5_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_imx_16_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_imx_10_n: 1;    //  11
    UINT32 reg_soft_rst_hsp_brdg_imx_11_n: 1;    //  12
    UINT32 reg_soft_rst_hsp_brdg_nd0_0_n: 1;    //  13
    UINT32 reg_soft_rst_hsp_brdg_nd0_1_n: 1;    //  14
    UINT32 resvd00            : 17;    //  31:15 reserved
    };
}BCRG_CTRL_HDR_CRG_BND_HDR03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x26_0010    crg_bnd_hdr04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_emmc_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_hdr_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_vdo_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_HDR_CRG_BND_HDR04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_HDR_CRG_BND_HDR00_O22A0_T    crg_bnd_hdr00;         // 0x26_0000
    BCRG_CTRL_HDR_CRG_BND_HDR01_O22A0_T    crg_bnd_hdr01;         // 0x26_0004
    BCRG_CTRL_HDR_CRG_BND_HDR02_O22A0_T    crg_bnd_hdr02;         // 0x26_0008
    BCRG_CTRL_HDR_CRG_BND_HDR03_O22A0_T    crg_bnd_hdr03;         // 0x26_000C
    BCRG_CTRL_HDR_CRG_BND_HDR04_O22A0_T    crg_bnd_hdr04;         // 0x26_0010
}BCRG_CTRL_HDR_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

