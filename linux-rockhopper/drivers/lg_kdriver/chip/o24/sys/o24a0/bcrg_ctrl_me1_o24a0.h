#ifndef _BCRG_CTRL_ME1_REG_O24A0_H_
#define _BCRG_CTRL_ME1_REG_O24A0_H_

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
    0xCC8C_1000    crg_bnd_me10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ME1_CRG_BND_ME10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8C_1004    crg_bnd_me11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ME1_CRG_BND_ME11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8C_1008    crg_bnd_me12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_me1_clk_gate_en: 1,    //      0
    reg_apb_ipw_vsd_clk_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_ME1_CRG_BND_ME12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8C_100C    crg_bnd_me13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_lnx0_0_n: 1,    //   0
    reg_soft_rst_axi_brdg_lnx1_0_n: 1,    //   1
    reg_soft_rst_axi_brdg_lnx2_0_n: 1,    //   2
    reg_soft_rst_axi_brdg_tcon_0_n: 1,    //   3
    reg_soft_rst_fly_brdg_cco_0_n: 1,    //    4
    reg_soft_rst_fly_brdg_cco_10_n: 1,    //   5
    reg_soft_rst_fly_brdg_cco_5_n: 1,    //    6
    reg_soft_rst_fly_brdg_cco_6_n: 1,    //    7
    reg_soft_rst_fly_brdg_led_2_n: 1,    //    8
    reg_soft_rst_fly_brdg_led_3_n: 1,    //    9
    reg_soft_rst_fly_brdg_tcon_1_n: 1,    //  10
    reg_soft_rst_hsp_brdg_cco_1_n: 1,    //   11
                              : 20;    //  31:12 reserved
}BCRG_CTRL_ME1_CRG_BND_ME13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8C_1010    crg_bnd_me14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_me1_n:  1,    //      0
    reg_soft_rst_apb_ipw_vsd_n:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_ME1_CRG_BND_ME14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8C_1014    crg_bnd_me15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fly_brdg_cco_5_clk_sel:  3,    //   2: 0
                              : 29;    //   31:3 reserved
}BCRG_CTRL_ME1_CRG_BND_ME15_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME1_CRG_BND_ME10_O24A0_T    crg_bnd_me10;         // 0xCC8C_1000
    BCRG_CTRL_ME1_CRG_BND_ME11_O24A0_T    crg_bnd_me11;         // 0xCC8C_1004
    BCRG_CTRL_ME1_CRG_BND_ME12_O24A0_T    crg_bnd_me12;         // 0xCC8C_1008
    BCRG_CTRL_ME1_CRG_BND_ME13_O24A0_T    crg_bnd_me13;         // 0xCC8C_100C
    BCRG_CTRL_ME1_CRG_BND_ME14_O24A0_T    crg_bnd_me14;         // 0xCC8C_1010
    BCRG_CTRL_ME1_CRG_BND_ME15_O24A0_T    crg_bnd_me15;         // 0xCC8C_1014
}BCRG_CTRL_ME1_REG_O24A0_T;
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

#define BCRG_CTRL_ME1_CRG_BND_ME10_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_ME1_CRG_BND_ME11_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_ME1_CRG_BND_ME12_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_ME1_CRG_BND_ME13_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_ME1_CRG_BND_ME14_O24A0_T_OFF              (BASEADDRESS+0x0010)
#define BCRG_CTRL_ME1_CRG_BND_ME15_O24A0_T_OFF              (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCC8C_1000    crg_bnd_me10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ME1_CRG_BND_ME10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8C_1004    crg_bnd_me11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ME1_CRG_BND_ME11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8C_1008    crg_bnd_me12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_me1_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_vsd_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_ME1_CRG_BND_ME12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8C_100C    crg_bnd_me13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_lnx0_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_lnx1_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_lnx2_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_tcon_0_n: 1;    //  3
    UINT32 reg_soft_rst_fly_brdg_cco_0_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_cco_10_n: 1;    //  5
    UINT32 reg_soft_rst_fly_brdg_cco_5_n: 1;    //  6
    UINT32 reg_soft_rst_fly_brdg_cco_6_n: 1;    //  7
    UINT32 reg_soft_rst_fly_brdg_led_2_n: 1;    //  8
    UINT32 reg_soft_rst_fly_brdg_led_3_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_tcon_1_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_cco_1_n: 1;    //  11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}BCRG_CTRL_ME1_CRG_BND_ME13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8C_1010    crg_bnd_me14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_me1_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_vsd_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_ME1_CRG_BND_ME14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8C_1014    crg_bnd_me15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fly_brdg_cco_5_clk_sel: 3;    //  2:0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_ME1_CRG_BND_ME15_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME1_CRG_BND_ME10_O24A0_T    crg_bnd_me10;         // 0xCC8C_1000
    BCRG_CTRL_ME1_CRG_BND_ME11_O24A0_T    crg_bnd_me11;         // 0xCC8C_1004
    BCRG_CTRL_ME1_CRG_BND_ME12_O24A0_T    crg_bnd_me12;         // 0xCC8C_1008
    BCRG_CTRL_ME1_CRG_BND_ME13_O24A0_T    crg_bnd_me13;         // 0xCC8C_100C
    BCRG_CTRL_ME1_CRG_BND_ME14_O24A0_T    crg_bnd_me14;         // 0xCC8C_1010
    BCRG_CTRL_ME1_CRG_BND_ME15_O24A0_T    crg_bnd_me15;         // 0xCC8C_1014
}BCRG_CTRL_ME1_REG_O24A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_ME1_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

