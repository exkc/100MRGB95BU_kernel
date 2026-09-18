#ifndef _BCRG_CTRL_FMS_M23A0_REG_H_
#define _BCRG_CTRL_FMS_M23A0_REG_H_

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
    0xCC99_1000    crg_bnd_fms00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_FMS_CRG_BND_FMS00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_1004    crg_bnd_fms01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_FMS_CRG_BND_FMS01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_1008    crg_bnd_fms02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_fms_clk_gate_en: 1,    //      0
    reg_apb_ipw_gsc_clk_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_100C    crg_bnd_fms03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_phy3_rstn        :  1,    //      0
    reg_soft_phy4_rstn        :  1,    //      1
    reg_soft_rst_f_tp_int_n   :  1,    //      2
    reg_soft_rst_fly_brdg_cco_1_n: 1,    //    3
    reg_soft_rst_fly_brdg_imx_4_n: 1,    //    4
    reg_soft_rst_hdmirx_prt3_link_n: 1,    //  5
    reg_soft_rst_hdmirx_prt4_link_n: 1,    //  6
                              : 25;    //   31:7 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_1010    crg_bnd_fms04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_fms_n:  1,    //      0
    reg_soft_rst_apb_ipw_gsc_n:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMS_CRG_BND_FMS00_M23A0_T    crg_bnd_fms00;       // 0xCC99_1000
    BCRG_CTRL_FMS_CRG_BND_FMS01_M23A0_T    crg_bnd_fms01;       // 0xCC99_1004
    BCRG_CTRL_FMS_CRG_BND_FMS02_M23A0_T    crg_bnd_fms02;       // 0xCC99_1008
    BCRG_CTRL_FMS_CRG_BND_FMS03_M23A0_T    crg_bnd_fms03;       // 0xCC99_100C
    BCRG_CTRL_FMS_CRG_BND_FMS04_M23A0_T    crg_bnd_fms04;       // 0xCC99_1010
}BCRG_CTRL_FMS_REG_M23A0_T;
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

#define BCRG_CTRL_FMS_CRG_BND_FMS00_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_FMS_CRG_BND_FMS01_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_FMS_CRG_BND_FMS02_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_FMS_CRG_BND_FMS03_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_FMS_CRG_BND_FMS04_M23A0_T_OFF             (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC99_1000    crg_bnd_fms00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_FMS_CRG_BND_FMS00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_1004    crg_bnd_fms01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_FMS_CRG_BND_FMS01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_1008    crg_bnd_fms02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_fms_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_gsc_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_100C    crg_bnd_fms03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_phy3_rstn :  1;    //      0
    UINT32 reg_soft_phy4_rstn :  1;    //      1
    UINT32 reg_soft_rst_f_tp_int_n: 1;    //   2
    UINT32 reg_soft_rst_fly_brdg_cco_1_n: 1;    //  3
    UINT32 reg_soft_rst_fly_brdg_imx_4_n: 1;    //  4
    UINT32 reg_soft_rst_hdmirx_prt3_link_n: 1;    //  5
    UINT32 reg_soft_rst_hdmirx_prt4_link_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_1010    crg_bnd_fms04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_fms_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_gsc_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMS_CRG_BND_FMS00_M23A0_T    crg_bnd_fms00;       // 0xCC99_1000
    BCRG_CTRL_FMS_CRG_BND_FMS01_M23A0_T    crg_bnd_fms01;       // 0xCC99_1004
    BCRG_CTRL_FMS_CRG_BND_FMS02_M23A0_T    crg_bnd_fms02;       // 0xCC99_1008
    BCRG_CTRL_FMS_CRG_BND_FMS03_M23A0_T    crg_bnd_fms03;       // 0xCC99_100C
    BCRG_CTRL_FMS_CRG_BND_FMS04_M23A0_T    crg_bnd_fms04;       // 0xCC99_1010
}BCRG_CTRL_FMS_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

