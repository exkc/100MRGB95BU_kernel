#ifndef _BCRG_CTRL_FMS_REG_O24A0_H_
#define _BCRG_CTRL_FMS_REG_O24A0_H_

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
    0xCC50_1000    crg_bnd_fms0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_FMS_CRG_BND_FMS0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_1004    crg_bnd_fms1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_FMS_CRG_BND_FMS1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_1008    crg_bnd_fms2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_fms_clk_gate_en: 1,    //      0
    reg_apb_ipw_sb_icve_clk_gate_en: 1,    //  1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_100C    crg_bnd_fms3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_ddr2sb_0_n: 1,    //  0
    reg_soft_rst_axi_brdg_lbus_10_n: 1,    //  1
    reg_soft_rst_axi_brdg_lbus_11_n: 1,    //  2
    reg_soft_rst_axi_brdg_lbus_9_n: 1,    //   3
    reg_soft_rst_fly_brdg_vsd_1_n: 1,    //    4
    reg_soft_rst_hsp_brdg_gsc_0_n: 1,    //    5
    reg_soft_rst_hsp_brdg_gsc_1_n: 1,    //    6
    reg_soft_rst_hsp_brdg_gsc_2_n: 1,    //    7
    reg_soft_rst_hsp_brdg_gsc_3_n: 1,    //    8
                              : 23;    //   31:9 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_1010    crg_bnd_fms4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_fms_n:  1,    //      0
    reg_soft_rst_apb_ipw_sb_icve_n: 1,    //   1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMS_CRG_BND_FMS0_O24A0_T    crg_bnd_fms0;         // 0xCC50_1000
    BCRG_CTRL_FMS_CRG_BND_FMS1_O24A0_T    crg_bnd_fms1;         // 0xCC50_1004
    BCRG_CTRL_FMS_CRG_BND_FMS2_O24A0_T    crg_bnd_fms2;         // 0xCC50_1008
    BCRG_CTRL_FMS_CRG_BND_FMS3_O24A0_T    crg_bnd_fms3;         // 0xCC50_100C
    BCRG_CTRL_FMS_CRG_BND_FMS4_O24A0_T    crg_bnd_fms4;         // 0xCC50_1010
}BCRG_CTRL_FMS_REG_O24A0_T;
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

#define BCRG_CTRL_FMS_CRG_BND_FMS0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_FMS_CRG_BND_FMS1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_FMS_CRG_BND_FMS2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_FMS_CRG_BND_FMS3_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_FMS_CRG_BND_FMS4_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC50_1000    crg_bnd_fms0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_FMS_CRG_BND_FMS0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_1004    crg_bnd_fms1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_FMS_CRG_BND_FMS1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_1008    crg_bnd_fms2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_fms_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_sb_icve_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_100C    crg_bnd_fms3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_ddr2sb_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_lbus_10_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_lbus_11_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_lbus_9_n: 1;    //  3
    UINT32 reg_soft_rst_fly_brdg_vsd_1_n: 1;    //  4
    UINT32 reg_soft_rst_hsp_brdg_gsc_0_n: 1;    //  5
    UINT32 reg_soft_rst_hsp_brdg_gsc_1_n: 1;    //  6
    UINT32 reg_soft_rst_hsp_brdg_gsc_2_n: 1;    //  7
    UINT32 reg_soft_rst_hsp_brdg_gsc_3_n: 1;    //  8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC50_1010    crg_bnd_fms4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_fms_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_sb_icve_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMS_CRG_BND_FMS0_O24A0_T    crg_bnd_fms0;         // 0xCC50_1000
    BCRG_CTRL_FMS_CRG_BND_FMS1_O24A0_T    crg_bnd_fms1;         // 0xCC50_1004
    BCRG_CTRL_FMS_CRG_BND_FMS2_O24A0_T    crg_bnd_fms2;         // 0xCC50_1008
    BCRG_CTRL_FMS_CRG_BND_FMS3_O24A0_T    crg_bnd_fms3;         // 0xCC50_100C
    BCRG_CTRL_FMS_CRG_BND_FMS4_O24A0_T    crg_bnd_fms4;         // 0xCC50_1010
}BCRG_CTRL_FMS_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_FMS_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

