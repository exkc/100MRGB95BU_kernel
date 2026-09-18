#ifndef _BCRG_CTRL_VD1_REG_O26A0_H_
#define _BCRG_CTRL_VD1_REG_O26A0_H_

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
    0xCE5A_1000    crg_bnd_vd1000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_VD1_CRG_BND_VD1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_1004    crg_bnd_vd1001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_VD1_CRG_BND_VD1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_1008    crg_bnd_vd1002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_tivsb_clk_gate_en: 1,    //    0
    reg_apb_ipw_vd1_clk_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_VD1_CRG_BND_VD1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_100C    crg_bnd_vd1003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_aud_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_ddr1sb_0_n: 1,    //  1
    reg_soft_rst_axi_brdg_lbus_5_n: 1,    //   2
    reg_soft_rst_axi_brdg_lbus_6_n: 1,    //   3
    reg_soft_rst_axi_brdg_lbus_7_n: 1,    //   4
    reg_soft_rst_axi_brdg_lnx0_0_n: 1,    //   5
    reg_soft_rst_axi_brdg_lnx1_0_n: 1,    //   6
    reg_soft_rst_axi_brdg_lnx2_0_n: 1,    //   7
    reg_soft_rst_axi_brdg_vd0_0_n: 1,    //    8
    reg_soft_rst_axi_brdg_vd0_1_n: 1,    //    9
                              : 22;    //  31:10 reserved
}BCRG_CTRL_VD1_CRG_BND_VD1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_1010    crg_bnd_vd1004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_tivsb_n: 1,    //     0
    reg_soft_rst_apb_ipw_vd1_n:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_VD1_CRG_BND_VD1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD1_CRG_BND_VD1000_O26A0_T    crg_bnd_vd1000;     // 0xCE5A_1000
    BCRG_CTRL_VD1_CRG_BND_VD1001_O26A0_T    crg_bnd_vd1001;     // 0xCE5A_1004
    BCRG_CTRL_VD1_CRG_BND_VD1002_O26A0_T    crg_bnd_vd1002;     // 0xCE5A_1008
    BCRG_CTRL_VD1_CRG_BND_VD1003_O26A0_T    crg_bnd_vd1003;     // 0xCE5A_100C
    BCRG_CTRL_VD1_CRG_BND_VD1004_O26A0_T    crg_bnd_vd1004;     // 0xCE5A_1010
}BCRG_CTRL_VD1_REG_O26A0_T;
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

#define BCRG_CTRL_VD1_CRG_BND_VD1000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_VD1_CRG_BND_VD1001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_VD1_CRG_BND_VD1002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_VD1_CRG_BND_VD1003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_VD1_CRG_BND_VD1004_O26A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCE5A_1000    crg_bnd_vd1000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_VD1_CRG_BND_VD1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_1004    crg_bnd_vd1001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_VD1_CRG_BND_VD1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_1008    crg_bnd_vd1002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_tivsb_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_vd1_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_VD1_CRG_BND_VD1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_100C    crg_bnd_vd1003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_aud_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_ddr1sb_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_lbus_5_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_lbus_6_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_lbus_7_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_lnx0_0_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_lnx1_0_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_lnx2_0_n: 1;    //  7
    UINT32 reg_soft_rst_axi_brdg_vd0_0_n: 1;    //  8
    UINT32 reg_soft_rst_axi_brdg_vd0_1_n: 1;    //  9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}BCRG_CTRL_VD1_CRG_BND_VD1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE5A_1010    crg_bnd_vd1004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_tivsb_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_vd1_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_VD1_CRG_BND_VD1004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD1_CRG_BND_VD1000_O26A0_T    crg_bnd_vd1000;     // 0xCE5A_1000
    BCRG_CTRL_VD1_CRG_BND_VD1001_O26A0_T    crg_bnd_vd1001;     // 0xCE5A_1004
    BCRG_CTRL_VD1_CRG_BND_VD1002_O26A0_T    crg_bnd_vd1002;     // 0xCE5A_1008
    BCRG_CTRL_VD1_CRG_BND_VD1003_O26A0_T    crg_bnd_vd1003;     // 0xCE5A_100C
    BCRG_CTRL_VD1_CRG_BND_VD1004_O26A0_T    crg_bnd_vd1004;     // 0xCE5A_1010
}BCRG_CTRL_VD1_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_VD1_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

