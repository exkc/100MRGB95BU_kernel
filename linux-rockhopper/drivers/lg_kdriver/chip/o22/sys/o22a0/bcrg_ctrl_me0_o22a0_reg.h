#ifndef _BCRG_CTRL_ME0_REG_H_
#define _BCRG_CTRL_ME0_REG_H_

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
    0x3E_0000    crg_bnd_me000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ME0_CRG_BND_ME000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3E_0004    crg_bnd_me001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ME0_CRG_BND_ME001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3E_0008    crg_bnd_me002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_me0_clk_gate_en: 1,    //      0
    reg_apb_ipw_usb_hs_me0_clk_gate_en: 1,    //  1
    reg_apb_ipw_usb_ss_u1_me0_clk_gate_en: 1,    //  2
    reg_apb_ipw_usb_ss_u2_me0_clk_gate_en: 1,    //  3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_ME0_CRG_BND_ME002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3E_000C    crg_bnd_me003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_hsp_brdg_imx_12_n: 1,    //   0
    reg_soft_rst_hsp_brdg_imx_13_n: 1,    //   1
    reg_soft_rst_hsp_brdg_imx_14_n: 1,    //   2
    reg_soft_rst_hsp_brdg_imx_15_n: 1,    //   3
    reg_soft_rst_hsp_brdg_nd1_0_n: 1,    //    4
    reg_soft_rst_hsp_brdg_nd1_1_n: 1,    //    5
    reg_soft_rst_hsp_brdg_sre_4_n: 1,    //    6
    reg_soft_rst_hsp_brdg_sre_5_n: 1,    //    7
    reg_soft_rst_hsp_brdg_sre_6_n: 1,    //    8
    reg_soft_sbw_aresetn_200  :  1,    //      9
                              : 22;    //  31:10 reserved
}BCRG_CTRL_ME0_CRG_BND_ME003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3E_0010    crg_bnd_me004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_me0_n:  1,    //      0
    reg_soft_rst_apb_ipw_usb_hs_me0_n: 1,    //  1
    reg_soft_rst_apb_ipw_usb_ss_u1_me0_n: 1,    //  2
    reg_soft_rst_apb_ipw_usb_ss_u2_me0_n: 1,    //  3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_ME0_CRG_BND_ME004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME0_CRG_BND_ME000_O22A0_T    crg_bnd_me000;         // 0x3E_0000
    BCRG_CTRL_ME0_CRG_BND_ME001_O22A0_T    crg_bnd_me001;         // 0x3E_0004
    BCRG_CTRL_ME0_CRG_BND_ME002_O22A0_T    crg_bnd_me002;         // 0x3E_0008
    BCRG_CTRL_ME0_CRG_BND_ME003_O22A0_T    crg_bnd_me003;         // 0x3E_000C
    BCRG_CTRL_ME0_CRG_BND_ME004_O22A0_T    crg_bnd_me004;         // 0x3E_0010
}BCRG_CTRL_ME0_REG_O22A0_T;
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

#define BCRG_CTRL_ME0_CRG_BND_ME000_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_ME0_CRG_BND_ME001_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_ME0_CRG_BND_ME002_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_ME0_CRG_BND_ME003_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_ME0_CRG_BND_ME004_O22A0_T_OFF               (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x3E_0000    crg_bnd_me000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ME0_CRG_BND_ME000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3E_0004    crg_bnd_me001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ME0_CRG_BND_ME001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3E_0008    crg_bnd_me002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_me0_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_usb_hs_me0_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_usb_ss_u1_me0_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_usb_ss_u2_me0_clk_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3E_000C    crg_bnd_me003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_hsp_brdg_imx_12_n: 1;    //  0
    UINT32 reg_soft_rst_hsp_brdg_imx_13_n: 1;    //  1
    UINT32 reg_soft_rst_hsp_brdg_imx_14_n: 1;    //  2
    UINT32 reg_soft_rst_hsp_brdg_imx_15_n: 1;    //  3
    UINT32 reg_soft_rst_hsp_brdg_nd1_0_n: 1;    //  4
    UINT32 reg_soft_rst_hsp_brdg_nd1_1_n: 1;    //  5
    UINT32 reg_soft_rst_hsp_brdg_sre_4_n: 1;    //  6
    UINT32 reg_soft_rst_hsp_brdg_sre_5_n: 1;    //  7
    UINT32 reg_soft_rst_hsp_brdg_sre_6_n: 1;    //  8
    UINT32 reg_soft_sbw_aresetn_200: 1;    //  9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3E_0010    crg_bnd_me004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_me0_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_usb_hs_me0_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_usb_ss_u1_me0_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_usb_ss_u2_me0_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME0_CRG_BND_ME000_O22A0_T    crg_bnd_me000;         // 0x3E_0000
    BCRG_CTRL_ME0_CRG_BND_ME001_O22A0_T    crg_bnd_me001;         // 0x3E_0004
    BCRG_CTRL_ME0_CRG_BND_ME002_O22A0_T    crg_bnd_me002;         // 0x3E_0008
    BCRG_CTRL_ME0_CRG_BND_ME003_O22A0_T    crg_bnd_me003;         // 0x3E_000C
    BCRG_CTRL_ME0_CRG_BND_ME004_O22A0_T    crg_bnd_me004;         // 0x3E_0010
}BCRG_CTRL_ME0_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

