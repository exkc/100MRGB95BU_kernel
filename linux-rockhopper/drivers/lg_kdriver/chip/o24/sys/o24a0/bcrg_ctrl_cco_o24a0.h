#ifndef _BCRG_CTRL_CCO_REG_O24A0_H_
#define _BCRG_CTRL_CCO_REG_O24A0_H_

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
    0xCC88_1000    crg_bnd_cco0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_CCO_CRG_BND_CCO0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC88_1004    crg_bnd_cco1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_CCO_CRG_BND_CCO1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC88_1008    crg_bnd_cco2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_cco_clk_gate_en: 1,    //      0
    reg_apb_ipw_sb_mefms_clk_gate_en: 1,    //  1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_CCO_CRG_BND_CCO2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC88_100C    crg_bnd_cco3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_ddr0sb_0_n: 1,    //  0
    reg_soft_rst_axi_brdg_lbus_1_n: 1,    //   1
    reg_soft_rst_axi_brdg_lbus_2_n: 1,    //   2
    reg_soft_rst_axi_brdg_lbus_3_n: 1,    //   3
    reg_soft_rst_axi_brdg_lnx0_0_n: 1,    //   4
    reg_soft_rst_axi_brdg_lnx1_0_n: 1,    //   5
    reg_soft_rst_axi_brdg_lnx2_0_n: 1,    //   6
    reg_soft_rst_axi_brdg_tcon_0_n: 1,    //   7
    reg_soft_rst_fly_brdg_imx_12_n: 1,    //   8
    reg_soft_rst_fly_brdg_me0_0_n: 1,    //    9
    reg_soft_rst_fly_brdg_vsd_1_n: 1,    //   10
    reg_soft_rst_hsp_brdg_gsc_0_n: 1,    //   11
    reg_soft_rst_hsp_brdg_gsc_1_n: 1,    //   12
    reg_soft_rst_hsp_brdg_gsc_2_n: 1,    //   13
    reg_soft_rst_hsp_brdg_gsc_3_n: 1,    //   14
                              : 17;    //  31:15 reserved
}BCRG_CTRL_CCO_CRG_BND_CCO3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC88_1010    crg_bnd_cco4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_cco_n:  1,    //      0
    reg_soft_rst_apb_ipw_sb_mefms_n: 1,    //  1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_CCO_CRG_BND_CCO4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CCO_CRG_BND_CCO0_O24A0_T    crg_bnd_cco0;         // 0xCC88_1000
    BCRG_CTRL_CCO_CRG_BND_CCO1_O24A0_T    crg_bnd_cco1;         // 0xCC88_1004
    BCRG_CTRL_CCO_CRG_BND_CCO2_O24A0_T    crg_bnd_cco2;         // 0xCC88_1008
    BCRG_CTRL_CCO_CRG_BND_CCO3_O24A0_T    crg_bnd_cco3;         // 0xCC88_100C
    BCRG_CTRL_CCO_CRG_BND_CCO4_O24A0_T    crg_bnd_cco4;         // 0xCC88_1010
}BCRG_CTRL_CCO_REG_O24A0_T;
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

#define BCRG_CTRL_CCO_CRG_BND_CCO0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_CCO_CRG_BND_CCO1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_CCO_CRG_BND_CCO2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_CCO_CRG_BND_CCO3_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_CCO_CRG_BND_CCO4_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC88_1000    crg_bnd_cco0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_CCO_CRG_BND_CCO0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC88_1004    crg_bnd_cco1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_CCO_CRG_BND_CCO1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC88_1008    crg_bnd_cco2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_cco_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_sb_mefms_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_CCO_CRG_BND_CCO2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC88_100C    crg_bnd_cco3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_ddr0sb_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_lbus_1_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_lbus_2_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_lbus_3_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_lnx0_0_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_lnx1_0_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_lnx2_0_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_tcon_0_n: 1;    //  7
    UINT32 reg_soft_rst_fly_brdg_imx_12_n: 1;    //  8
    UINT32 reg_soft_rst_fly_brdg_me0_0_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_vsd_1_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_gsc_0_n: 1;    //  11
    UINT32 reg_soft_rst_hsp_brdg_gsc_1_n: 1;    //  12
    UINT32 reg_soft_rst_hsp_brdg_gsc_2_n: 1;    //  13
    UINT32 reg_soft_rst_hsp_brdg_gsc_3_n: 1;    //  14
    UINT32 resvd00            : 17;    //  31:15 reserved
    };
}BCRG_CTRL_CCO_CRG_BND_CCO3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC88_1010    crg_bnd_cco4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_cco_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_sb_mefms_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_CCO_CRG_BND_CCO4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CCO_CRG_BND_CCO0_O24A0_T    crg_bnd_cco0;         // 0xCC88_1000
    BCRG_CTRL_CCO_CRG_BND_CCO1_O24A0_T    crg_bnd_cco1;         // 0xCC88_1004
    BCRG_CTRL_CCO_CRG_BND_CCO2_O24A0_T    crg_bnd_cco2;         // 0xCC88_1008
    BCRG_CTRL_CCO_CRG_BND_CCO3_O24A0_T    crg_bnd_cco3;         // 0xCC88_100C
    BCRG_CTRL_CCO_CRG_BND_CCO4_O24A0_T    crg_bnd_cco4;         // 0xCC88_1010
}BCRG_CTRL_CCO_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_CCO_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

