#ifndef _BCRG_CTRL_SRE_REG_O24A0_H_
#define _BCRG_CTRL_SRE_REG_O24A0_H_

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
    0xCC64_1000    crg_bnd_sre0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_SRE_CRG_BND_SRE0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC64_1004    crg_bnd_sre1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_SRE_CRG_BND_SRE1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC64_1008    crg_bnd_sre2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_sre_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_SRE_CRG_BND_SRE2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC64_100C    crg_bnd_sre3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_emmc_0_n: 1,    //   0
    reg_soft_rst_axi_brdg_nd1_0_n: 1,    //    1
    reg_soft_rst_axi_brdg_usbsb_0_n: 1,    //  2
    reg_soft_rst_axi_brdg_vd0_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_vd0_1_n: 1,    //    4
    reg_soft_rst_axi_brdg_vd1_0_n: 1,    //    5
    reg_soft_rst_axi_brdg_vd1_1_n: 1,    //    6
    reg_soft_rst_axi_brdg_vd2_0_n: 1,    //    7
    reg_soft_rst_axi_brdg_vd2_1_n: 1,    //    8
    reg_soft_rst_hsp_brdg_imx_8_n: 1,    //    9
    reg_soft_rst_hsp_brdg_imx_9_n: 1,    //   10
    reg_soft_rst_hsp_brdg_nd1_0_n: 1,    //   11
    reg_soft_rst_hsp_brdg_nd1_1_n: 1,    //   12
                              : 19;    //  31:13 reserved
}BCRG_CTRL_SRE_CRG_BND_SRE3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC64_1010    crg_bnd_sre4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_sre_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_SRE_CRG_BND_SRE4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_SRE_CRG_BND_SRE0_O24A0_T    crg_bnd_sre0;         // 0xCC64_1000
    BCRG_CTRL_SRE_CRG_BND_SRE1_O24A0_T    crg_bnd_sre1;         // 0xCC64_1004
    BCRG_CTRL_SRE_CRG_BND_SRE2_O24A0_T    crg_bnd_sre2;         // 0xCC64_1008
    BCRG_CTRL_SRE_CRG_BND_SRE3_O24A0_T    crg_bnd_sre3;         // 0xCC64_100C
    BCRG_CTRL_SRE_CRG_BND_SRE4_O24A0_T    crg_bnd_sre4;         // 0xCC64_1010
}BCRG_CTRL_SRE_REG_O24A0_T;
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

#define BCRG_CTRL_SRE_CRG_BND_SRE0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_SRE_CRG_BND_SRE1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_SRE_CRG_BND_SRE2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_SRE_CRG_BND_SRE3_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_SRE_CRG_BND_SRE4_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC64_1000    crg_bnd_sre0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_SRE_CRG_BND_SRE0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC64_1004    crg_bnd_sre1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_SRE_CRG_BND_SRE1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC64_1008    crg_bnd_sre2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_sre_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_SRE_CRG_BND_SRE2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC64_100C    crg_bnd_sre3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_emmc_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_nd1_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_usbsb_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_vd0_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_vd0_1_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_vd1_0_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_vd1_1_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_vd2_0_n: 1;    //  7
    UINT32 reg_soft_rst_axi_brdg_vd2_1_n: 1;    //  8
    UINT32 reg_soft_rst_hsp_brdg_imx_8_n: 1;    //  9
    UINT32 reg_soft_rst_hsp_brdg_imx_9_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_nd1_0_n: 1;    //  11
    UINT32 reg_soft_rst_hsp_brdg_nd1_1_n: 1;    //  12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}BCRG_CTRL_SRE_CRG_BND_SRE3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC64_1010    crg_bnd_sre4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_sre_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_SRE_CRG_BND_SRE4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_SRE_CRG_BND_SRE0_O24A0_T    crg_bnd_sre0;         // 0xCC64_1000
    BCRG_CTRL_SRE_CRG_BND_SRE1_O24A0_T    crg_bnd_sre1;         // 0xCC64_1004
    BCRG_CTRL_SRE_CRG_BND_SRE2_O24A0_T    crg_bnd_sre2;         // 0xCC64_1008
    BCRG_CTRL_SRE_CRG_BND_SRE3_O24A0_T    crg_bnd_sre3;         // 0xCC64_100C
    BCRG_CTRL_SRE_CRG_BND_SRE4_O24A0_T    crg_bnd_sre4;         // 0xCC64_1010
}BCRG_CTRL_SRE_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_SRE_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

