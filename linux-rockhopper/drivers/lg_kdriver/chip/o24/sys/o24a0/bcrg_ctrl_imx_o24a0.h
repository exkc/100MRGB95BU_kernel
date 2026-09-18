#ifndef _BCRG_CTRL_IMX_REG_O24A0_H_
#define _BCRG_CTRL_IMX_REG_O24A0_H_

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
    0xCC84_1000    crg_bnd_imx0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_IMX_CRG_BND_IMX0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_1004    crg_bnd_imx1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_IMX_CRG_BND_IMX1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_1008    crg_bnd_imx2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_gpu_clk_gate_en: 1,    //      0
    reg_apb_ipw_imx_clk_gate_en: 1,    //      1
    reg_apb_ipw_sb_imvd_clk_gate_en: 1,    //  2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_IMX_CRG_BND_IMX2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_100C    crg_bnd_imx3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_aud_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_cpu_0_n: 1,    //    1
    reg_soft_rst_axi_brdg_cpu_3_n: 1,    //    2
    reg_soft_rst_axi_brdg_lb0sb_0_n: 1,    //  3
    reg_soft_rst_axi_brdg_nd0_0_n: 1,    //    4
    reg_soft_rst_hsp_brdg_nd0_4_n: 1,    //    5
    reg_soft_rst_hsp_brdg_nd0_5_n: 1,    //    6
                              : 25;    //   31:7 reserved
}BCRG_CTRL_IMX_CRG_BND_IMX3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_1010    crg_bnd_imx4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_gpu_n:  1,    //      0
    reg_soft_rst_apb_ipw_imx_n:  1,    //      1
    reg_soft_rst_apb_ipw_sb_imvd_n: 1,    //   2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_IMX_CRG_BND_IMX4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_IMX_CRG_BND_IMX0_O24A0_T    crg_bnd_imx0;         // 0xCC84_1000
    BCRG_CTRL_IMX_CRG_BND_IMX1_O24A0_T    crg_bnd_imx1;         // 0xCC84_1004
    BCRG_CTRL_IMX_CRG_BND_IMX2_O24A0_T    crg_bnd_imx2;         // 0xCC84_1008
    BCRG_CTRL_IMX_CRG_BND_IMX3_O24A0_T    crg_bnd_imx3;         // 0xCC84_100C
    BCRG_CTRL_IMX_CRG_BND_IMX4_O24A0_T    crg_bnd_imx4;         // 0xCC84_1010
}BCRG_CTRL_IMX_REG_O24A0_T;
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

#define BCRG_CTRL_IMX_CRG_BND_IMX0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_IMX_CRG_BND_IMX1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_IMX_CRG_BND_IMX2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_IMX_CRG_BND_IMX3_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_IMX_CRG_BND_IMX4_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC84_1000    crg_bnd_imx0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_IMX_CRG_BND_IMX0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_1004    crg_bnd_imx1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_IMX_CRG_BND_IMX1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_1008    crg_bnd_imx2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_gpu_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_imx_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_sb_imvd_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_IMX_CRG_BND_IMX2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_100C    crg_bnd_imx3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_aud_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_cpu_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_cpu_3_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_lb0sb_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_nd0_0_n: 1;    //  4
    UINT32 reg_soft_rst_hsp_brdg_nd0_4_n: 1;    //  5
    UINT32 reg_soft_rst_hsp_brdg_nd0_5_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}BCRG_CTRL_IMX_CRG_BND_IMX3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC84_1010    crg_bnd_imx4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_gpu_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_imx_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_sb_imvd_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_IMX_CRG_BND_IMX4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_IMX_CRG_BND_IMX0_O24A0_T    crg_bnd_imx0;         // 0xCC84_1000
    BCRG_CTRL_IMX_CRG_BND_IMX1_O24A0_T    crg_bnd_imx1;         // 0xCC84_1004
    BCRG_CTRL_IMX_CRG_BND_IMX2_O24A0_T    crg_bnd_imx2;         // 0xCC84_1008
    BCRG_CTRL_IMX_CRG_BND_IMX3_O24A0_T    crg_bnd_imx3;         // 0xCC84_100C
    BCRG_CTRL_IMX_CRG_BND_IMX4_O24A0_T    crg_bnd_imx4;         // 0xCC84_1010
}BCRG_CTRL_IMX_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_IMX_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

