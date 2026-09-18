#ifndef _BCRG_CTRL_HDR_REG_O26A0_H_
#define _BCRG_CTRL_HDR_REG_O26A0_H_

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
    0xCC27_1000    crg_bnd_hdr000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_HDR_CRG_BND_HDR000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_1004    crg_bnd_hdr001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_HDR_CRG_BND_HDR001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_1008    crg_bnd_hdr002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_hdr_clk_gate_en: 1,    //      0
    reg_apb_ipw_vdo_clk_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_HDR_CRG_BND_HDR002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_100C    crg_bnd_hdr003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_dbb_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_fms_0_n: 1,    //    1
    reg_soft_rst_axi_brdg_nd0_0_n: 1,    //    2
    reg_soft_rst_fly_brdg_fms_0_n: 1,    //    3
    reg_soft_rst_hsp_brdg_dnsr0_0_n: 1,    //  4
    reg_soft_rst_hsp_brdg_dnsr1_0_n: 1,    //  5
    reg_soft_rst_hsp_brdg_imx_6_n: 1,    //    6
    reg_soft_rst_hsp_brdg_imx_7_n: 1,    //    7
    reg_soft_rst_hsp_brdg_nd0_0_n: 1,    //    8
    reg_soft_rst_hsp_brdg_nd0_1_n: 1,    //    9
    reg_soft_rst_hsp_brdg_nd0_4_n: 1,    //   10
    reg_soft_rst_hsp_brdg_nd0_5_n: 1,    //   11
    reg_soft_rst_hsp_brdg_nd1_2_n: 1,    //   12
    reg_soft_rst_hsp_brdg_nd1_3_n: 1,    //   13
    reg_soft_rst_hsp_brdg_sre_0_n: 1,    //   14
    reg_soft_rst_hsp_brdg_sre_1_n: 1,    //   15
                              : 16;    //  31:16 reserved
}BCRG_CTRL_HDR_CRG_BND_HDR003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_1010    crg_bnd_hdr004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_hdr_n:  1,    //      0
    reg_soft_rst_apb_ipw_vdo_n:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_HDR_CRG_BND_HDR004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_HDR_CRG_BND_HDR000_O26A0_T    crg_bnd_hdr000;     // 0xCC27_1000
    BCRG_CTRL_HDR_CRG_BND_HDR001_O26A0_T    crg_bnd_hdr001;     // 0xCC27_1004
    BCRG_CTRL_HDR_CRG_BND_HDR002_O26A0_T    crg_bnd_hdr002;     // 0xCC27_1008
    BCRG_CTRL_HDR_CRG_BND_HDR003_O26A0_T    crg_bnd_hdr003;     // 0xCC27_100C
    BCRG_CTRL_HDR_CRG_BND_HDR004_O26A0_T    crg_bnd_hdr004;     // 0xCC27_1010
}BCRG_CTRL_HDR_REG_O26A0_T;
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

#define BCRG_CTRL_HDR_CRG_BND_HDR000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_HDR_CRG_BND_HDR001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_HDR_CRG_BND_HDR002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_HDR_CRG_BND_HDR003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_HDR_CRG_BND_HDR004_O26A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC27_1000    crg_bnd_hdr000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_HDR_CRG_BND_HDR000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_1004    crg_bnd_hdr001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_HDR_CRG_BND_HDR001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_1008    crg_bnd_hdr002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_hdr_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_vdo_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_HDR_CRG_BND_HDR002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_100C    crg_bnd_hdr003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_dbb_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_fms_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_nd0_0_n: 1;    //  2
    UINT32 reg_soft_rst_fly_brdg_fms_0_n: 1;    //  3
    UINT32 reg_soft_rst_hsp_brdg_dnsr0_0_n: 1;    //  4
    UINT32 reg_soft_rst_hsp_brdg_dnsr1_0_n: 1;    //  5
    UINT32 reg_soft_rst_hsp_brdg_imx_6_n: 1;    //  6
    UINT32 reg_soft_rst_hsp_brdg_imx_7_n: 1;    //  7
    UINT32 reg_soft_rst_hsp_brdg_nd0_0_n: 1;    //  8
    UINT32 reg_soft_rst_hsp_brdg_nd0_1_n: 1;    //  9
    UINT32 reg_soft_rst_hsp_brdg_nd0_4_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_nd0_5_n: 1;    //  11
    UINT32 reg_soft_rst_hsp_brdg_nd1_2_n: 1;    //  12
    UINT32 reg_soft_rst_hsp_brdg_nd1_3_n: 1;    //  13
    UINT32 reg_soft_rst_hsp_brdg_sre_0_n: 1;    //  14
    UINT32 reg_soft_rst_hsp_brdg_sre_1_n: 1;    //  15
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}BCRG_CTRL_HDR_CRG_BND_HDR003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_1010    crg_bnd_hdr004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_hdr_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_vdo_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_HDR_CRG_BND_HDR004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_HDR_CRG_BND_HDR000_O26A0_T    crg_bnd_hdr000;     // 0xCC27_1000
    BCRG_CTRL_HDR_CRG_BND_HDR001_O26A0_T    crg_bnd_hdr001;     // 0xCC27_1004
    BCRG_CTRL_HDR_CRG_BND_HDR002_O26A0_T    crg_bnd_hdr002;     // 0xCC27_1008
    BCRG_CTRL_HDR_CRG_BND_HDR003_O26A0_T    crg_bnd_hdr003;     // 0xCC27_100C
    BCRG_CTRL_HDR_CRG_BND_HDR004_O26A0_T    crg_bnd_hdr004;     // 0xCC27_1010
}BCRG_CTRL_HDR_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_HDR_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

