#ifndef _BCRG_CTRL_IMX_REG_H_
#define _BCRG_CTRL_IMX_REG_H_

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
    0x2B_0000    crg_bnd_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_IMX_CRG_BND_IMX00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2B_0004    crg_bnd_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_IMX_CRG_BND_IMX01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2B_0008    crg_bnd_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_imx_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_IMX_CRG_BND_IMX02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2B_000C    crg_bnd_imx03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_brdg_cvi_2_n: 1,    //    0
    reg_soft_rst_axi_brdg_hdmi_0_n: 1,    //   1
    reg_soft_rst_fly_brdg_hdmi_0_n: 1,    //   2
    reg_soft_rst_fly_brdg_hdmi_1_n: 1,    //   3
    reg_soft_rst_fly_brdg_hdmi_2_n: 1,    //   4
    reg_soft_rst_fly_brdg_hdmi_3_n: 1,    //   5
                              : 26;    //   31:6 reserved
}BCRG_CTRL_IMX_CRG_BND_IMX03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2B_0010    crg_bnd_imx04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_imx_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_IMX_CRG_BND_IMX04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_IMX_CRG_BND_IMX00_O22A0_T    crg_bnd_imx00;         // 0x2B_0000
    BCRG_CTRL_IMX_CRG_BND_IMX01_O22A0_T    crg_bnd_imx01;         // 0x2B_0004
    BCRG_CTRL_IMX_CRG_BND_IMX02_O22A0_T    crg_bnd_imx02;         // 0x2B_0008
    BCRG_CTRL_IMX_CRG_BND_IMX03_O22A0_T    crg_bnd_imx03;         // 0x2B_000C
    BCRG_CTRL_IMX_CRG_BND_IMX04_O22A0_T    crg_bnd_imx04;         // 0x2B_0010
}BCRG_CTRL_IMX_REG_O22A0_T;
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

#define BCRG_CTRL_IMX_CRG_BND_IMX00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_IMX_CRG_BND_IMX01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_IMX_CRG_BND_IMX02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_IMX_CRG_BND_IMX03_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_IMX_CRG_BND_IMX04_O22A0_T_OFF               (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x2B_0000    crg_bnd_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_IMX_CRG_BND_IMX00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2B_0004    crg_bnd_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_IMX_CRG_BND_IMX01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2B_0008    crg_bnd_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_imx_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_IMX_CRG_BND_IMX02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2B_000C    crg_bnd_imx03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_brdg_cvi_2_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_hdmi_0_n: 1;    //  1
    UINT32 reg_soft_rst_fly_brdg_hdmi_0_n: 1;    //  2
    UINT32 reg_soft_rst_fly_brdg_hdmi_1_n: 1;    //  3
    UINT32 reg_soft_rst_fly_brdg_hdmi_2_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_hdmi_3_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BCRG_CTRL_IMX_CRG_BND_IMX03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2B_0010    crg_bnd_imx04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_imx_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_IMX_CRG_BND_IMX04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_IMX_CRG_BND_IMX00_O22A0_T    crg_bnd_imx00;         // 0x2B_0000
    BCRG_CTRL_IMX_CRG_BND_IMX01_O22A0_T    crg_bnd_imx01;         // 0x2B_0004
    BCRG_CTRL_IMX_CRG_BND_IMX02_O22A0_T    crg_bnd_imx02;         // 0x2B_0008
    BCRG_CTRL_IMX_CRG_BND_IMX03_O22A0_T    crg_bnd_imx03;         // 0x2B_000C
    BCRG_CTRL_IMX_CRG_BND_IMX04_O22A0_T    crg_bnd_imx04;         // 0x2B_0010
}BCRG_CTRL_IMX_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

