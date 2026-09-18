#ifndef _BCRG_CTRL_IMX_REG_O26A0_H_
#define _BCRG_CTRL_IMX_REG_O26A0_H_

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
    0xCCC3_1000    crg_bnd_imx000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_IMX_CRG_BND_IMX000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_1004    crg_bnd_imx001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_IMX_CRG_BND_IMX001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_1008    crg_bnd_imx002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_imx_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_IMX_CRG_BND_IMX002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_100C    crg_bnd_imx003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_cpu_1_n: 1,    //    0
    reg_soft_rst_axi_brdg_cpu_2_n: 1,    //    1
    reg_soft_rst_axi_brdg_emusb_0_n: 1,    //  2
    reg_soft_rst_axi_brdg_fms_0_n: 1,    //    3
    reg_soft_rst_axi_brdg_lb1sb_0_n: 1,    //  4
    reg_soft_rst_axi_brdg_nd0_0_n: 1,    //    5
    reg_soft_rst_axi_brdg_nd1_0_n: 1,    //    6
    reg_soft_rst_axi_brdg_vdo_0_n: 1,    //    7
    reg_soft_rst_axi_brdg_vdo_1_n: 1,    //    8
    reg_soft_rst_axi_brdg_vmcu_0_n: 1,    //   9
    reg_soft_rst_fly_brdg_fms_0_n: 1,    //   10
    reg_soft_rst_hsp_brdg_dnsr0_0_n: 1,    //  11
    reg_soft_rst_hsp_brdg_dnsr1_0_n: 1,    //  12
    reg_soft_rst_hsp_brdg_nd0_4_n: 1,    //   13
    reg_soft_rst_hsp_brdg_nd0_5_n: 1,    //   14
    reg_soft_rst_hsp_brdg_nd1_2_n: 1,    //   15
    reg_soft_rst_hsp_brdg_nd1_3_n: 1,    //   16
    reg_soft_rst_hsp_brdg_sre_0_n: 1,    //   17
    reg_soft_rst_hsp_brdg_sre_1_n: 1,    //   18
                              : 13;    //  31:19 reserved
}BCRG_CTRL_IMX_CRG_BND_IMX003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_1010    crg_bnd_imx004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_imx_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_IMX_CRG_BND_IMX004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_IMX_CRG_BND_IMX000_O26A0_T    crg_bnd_imx000;     // 0xCCC3_1000
    BCRG_CTRL_IMX_CRG_BND_IMX001_O26A0_T    crg_bnd_imx001;     // 0xCCC3_1004
    BCRG_CTRL_IMX_CRG_BND_IMX002_O26A0_T    crg_bnd_imx002;     // 0xCCC3_1008
    BCRG_CTRL_IMX_CRG_BND_IMX003_O26A0_T    crg_bnd_imx003;     // 0xCCC3_100C
    BCRG_CTRL_IMX_CRG_BND_IMX004_O26A0_T    crg_bnd_imx004;     // 0xCCC3_1010
}BCRG_CTRL_IMX_REG_O26A0_T;
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

#define BCRG_CTRL_IMX_CRG_BND_IMX000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_IMX_CRG_BND_IMX001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_IMX_CRG_BND_IMX002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_IMX_CRG_BND_IMX003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_IMX_CRG_BND_IMX004_O26A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCC3_1000    crg_bnd_imx000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_IMX_CRG_BND_IMX000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_1004    crg_bnd_imx001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_IMX_CRG_BND_IMX001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_1008    crg_bnd_imx002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_imx_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_IMX_CRG_BND_IMX002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_100C    crg_bnd_imx003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_cpu_1_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_cpu_2_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_emusb_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_fms_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_lb1sb_0_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_nd0_0_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_nd1_0_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_vdo_0_n: 1;    //  7
    UINT32 reg_soft_rst_axi_brdg_vdo_1_n: 1;    //  8
    UINT32 reg_soft_rst_axi_brdg_vmcu_0_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_fms_0_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_dnsr0_0_n: 1;    //  11
    UINT32 reg_soft_rst_hsp_brdg_dnsr1_0_n: 1;    //  12
    UINT32 reg_soft_rst_hsp_brdg_nd0_4_n: 1;    //  13
    UINT32 reg_soft_rst_hsp_brdg_nd0_5_n: 1;    //  14
    UINT32 reg_soft_rst_hsp_brdg_nd1_2_n: 1;    //  15
    UINT32 reg_soft_rst_hsp_brdg_nd1_3_n: 1;    //  16
    UINT32 reg_soft_rst_hsp_brdg_sre_0_n: 1;    //  17
    UINT32 reg_soft_rst_hsp_brdg_sre_1_n: 1;    //  18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}BCRG_CTRL_IMX_CRG_BND_IMX003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_1010    crg_bnd_imx004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_imx_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_IMX_CRG_BND_IMX004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_IMX_CRG_BND_IMX000_O26A0_T    crg_bnd_imx000;     // 0xCCC3_1000
    BCRG_CTRL_IMX_CRG_BND_IMX001_O26A0_T    crg_bnd_imx001;     // 0xCCC3_1004
    BCRG_CTRL_IMX_CRG_BND_IMX002_O26A0_T    crg_bnd_imx002;     // 0xCCC3_1008
    BCRG_CTRL_IMX_CRG_BND_IMX003_O26A0_T    crg_bnd_imx003;     // 0xCCC3_100C
    BCRG_CTRL_IMX_CRG_BND_IMX004_O26A0_T    crg_bnd_imx004;     // 0xCCC3_1010
}BCRG_CTRL_IMX_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_IMX_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

