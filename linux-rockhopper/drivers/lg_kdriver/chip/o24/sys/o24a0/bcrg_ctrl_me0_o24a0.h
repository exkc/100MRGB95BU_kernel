#ifndef _BCRG_CTRL_ME0_REG_O24A0_H_
#define _BCRG_CTRL_ME0_REG_O24A0_H_

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
    0xCC4C_1000    crg_bnd_me00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ME0_CRG_BND_ME00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1004    crg_bnd_me01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ME0_CRG_BND_ME01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1008    crg_bnd_me02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_me0_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_ME0_CRG_BND_ME02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_100C    crg_bnd_me03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_ddr1sb_0_n: 1,    //  0
    reg_soft_rst_axi_brdg_fms_0_n: 1,    //    1
    reg_soft_rst_axi_brdg_lbus_5_n: 1,    //   2
    reg_soft_rst_axi_brdg_lbus_6_n: 1,    //   3
    reg_soft_rst_axi_brdg_lbus_7_n: 1,    //   4
    reg_soft_rst_fly_brdg_fms_0_n: 1,    //    5
    reg_soft_rst_fly_brdg_vsd_1_n: 1,    //    6
    reg_soft_rst_hsp_brdg_gsc_0_n: 1,    //    7
    reg_soft_rst_hsp_brdg_gsc_1_n: 1,    //    8
    reg_soft_rst_hsp_brdg_gsc_2_n: 1,    //    9
    reg_soft_rst_hsp_brdg_gsc_3_n: 1,    //   10
                              : 21;    //  31:11 reserved
}BCRG_CTRL_ME0_CRG_BND_ME03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1010    crg_bnd_me04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_me0_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_ME0_CRG_BND_ME04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME0_CRG_BND_ME00_O24A0_T    crg_bnd_me00;         // 0xCC4C_1000
    BCRG_CTRL_ME0_CRG_BND_ME01_O24A0_T    crg_bnd_me01;         // 0xCC4C_1004
    BCRG_CTRL_ME0_CRG_BND_ME02_O24A0_T    crg_bnd_me02;         // 0xCC4C_1008
    BCRG_CTRL_ME0_CRG_BND_ME03_O24A0_T    crg_bnd_me03;         // 0xCC4C_100C
    BCRG_CTRL_ME0_CRG_BND_ME04_O24A0_T    crg_bnd_me04;         // 0xCC4C_1010
}BCRG_CTRL_ME0_REG_O24A0_T;
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

#define BCRG_CTRL_ME0_CRG_BND_ME00_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_ME0_CRG_BND_ME01_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_ME0_CRG_BND_ME02_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_ME0_CRG_BND_ME03_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_ME0_CRG_BND_ME04_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC4C_1000    crg_bnd_me00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ME0_CRG_BND_ME00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1004    crg_bnd_me01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ME0_CRG_BND_ME01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1008    crg_bnd_me02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_me0_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_100C    crg_bnd_me03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_ddr1sb_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_fms_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_lbus_5_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_lbus_6_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_lbus_7_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_fms_0_n: 1;    //  5
    UINT32 reg_soft_rst_fly_brdg_vsd_1_n: 1;    //  6
    UINT32 reg_soft_rst_hsp_brdg_gsc_0_n: 1;    //  7
    UINT32 reg_soft_rst_hsp_brdg_gsc_1_n: 1;    //  8
    UINT32 reg_soft_rst_hsp_brdg_gsc_2_n: 1;    //  9
    UINT32 reg_soft_rst_hsp_brdg_gsc_3_n: 1;    //  10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1010    crg_bnd_me04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_me0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_ME0_CRG_BND_ME04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ME0_CRG_BND_ME00_O24A0_T    crg_bnd_me00;         // 0xCC4C_1000
    BCRG_CTRL_ME0_CRG_BND_ME01_O24A0_T    crg_bnd_me01;         // 0xCC4C_1004
    BCRG_CTRL_ME0_CRG_BND_ME02_O24A0_T    crg_bnd_me02;         // 0xCC4C_1008
    BCRG_CTRL_ME0_CRG_BND_ME03_O24A0_T    crg_bnd_me03;         // 0xCC4C_100C
    BCRG_CTRL_ME0_CRG_BND_ME04_O24A0_T    crg_bnd_me04;         // 0xCC4C_1010
}BCRG_CTRL_ME0_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_ME0_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

