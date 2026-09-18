#ifndef _BCRG_CTRL_DPE_M23A0_REG_H_
#define _BCRG_CTRL_DPE_M23A0_REG_H_

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
    0xCC53_1000    crg_bnd_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_DPE_CRG_BND_DPE00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1004    crg_bnd_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_DPE_CRG_BND_DPE01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1008    crg_bnd_dpe02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_cco_clk_gate_en: 1,    //      0
    reg_apb_ipw_led_clk_gate_en: 1,    //      1
    reg_apb_ipw_tcon_clk_gate_en: 1,    //     2
    reg_apb_ipw_vsd_clk_gate_en: 1,    //      3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_DPE_CRG_BND_DPE02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_100C    crg_bnd_dpe03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_fmc_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_fmc_1_n: 1,    //    1
    reg_soft_rst_axi_brdg_lne_0_n: 1,    //    2
    reg_soft_rst_axi_brdg_me_0_n: 1,    //     3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_DPE_CRG_BND_DPE03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1010    crg_bnd_dpe04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_cco_n:  1,    //      0
    reg_soft_rst_apb_ipw_led_n:  1,    //      1
    reg_soft_rst_apb_ipw_tcon_n: 1,    //      2
    reg_soft_rst_apb_ipw_vsd_n:  1,    //      3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_DPE_CRG_BND_DPE04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DPE_CRG_BND_DPE00_M23A0_T    crg_bnd_dpe00;       // 0xCC53_1000
    BCRG_CTRL_DPE_CRG_BND_DPE01_M23A0_T    crg_bnd_dpe01;       // 0xCC53_1004
    BCRG_CTRL_DPE_CRG_BND_DPE02_M23A0_T    crg_bnd_dpe02;       // 0xCC53_1008
    BCRG_CTRL_DPE_CRG_BND_DPE03_M23A0_T    crg_bnd_dpe03;       // 0xCC53_100C
    BCRG_CTRL_DPE_CRG_BND_DPE04_M23A0_T    crg_bnd_dpe04;       // 0xCC53_1010
}BCRG_CTRL_DPE_REG_M23A0_T;
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

#define BCRG_CTRL_DPE_CRG_BND_DPE00_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_DPE_CRG_BND_DPE01_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_DPE_CRG_BND_DPE02_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_DPE_CRG_BND_DPE03_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_DPE_CRG_BND_DPE04_M23A0_T_OFF             (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC53_1000    crg_bnd_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_DPE_CRG_BND_DPE00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1004    crg_bnd_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_DPE_CRG_BND_DPE01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1008    crg_bnd_dpe02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_cco_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_led_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_tcon_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_vsd_clk_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_DPE_CRG_BND_DPE02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_100C    crg_bnd_dpe03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_fmc_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_fmc_1_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_lne_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_me_0_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_DPE_CRG_BND_DPE03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1010    crg_bnd_dpe04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_cco_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_led_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_tcon_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_vsd_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_DPE_CRG_BND_DPE04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DPE_CRG_BND_DPE00_M23A0_T    crg_bnd_dpe00;       // 0xCC53_1000
    BCRG_CTRL_DPE_CRG_BND_DPE01_M23A0_T    crg_bnd_dpe01;       // 0xCC53_1004
    BCRG_CTRL_DPE_CRG_BND_DPE02_M23A0_T    crg_bnd_dpe02;       // 0xCC53_1008
    BCRG_CTRL_DPE_CRG_BND_DPE03_M23A0_T    crg_bnd_dpe03;       // 0xCC53_100C
    BCRG_CTRL_DPE_CRG_BND_DPE04_M23A0_T    crg_bnd_dpe04;       // 0xCC53_1010
}BCRG_CTRL_DPE_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

