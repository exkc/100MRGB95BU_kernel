#ifndef _BCRG_CTRL_VD0_REG_O24A0_H_
#define _BCRG_CTRL_VD0_REG_O24A0_H_

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
    0xCEC8_1000    crg_bnd_vd00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_VD0_CRG_BND_VD00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_1004    crg_bnd_vd01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_VD0_CRG_BND_VD01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_1008    crg_bnd_vd02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fsc_clk_gate_en       :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD0_CRG_BND_VD02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_100C    crg_bnd_vd03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_vd0_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD0_CRG_BND_VD03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_1010    crg_bnd_vd04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_nd1_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_usbsb_0_n: 1,    //  1
    reg_soft_rst_hsp_brdg_imx_8_n: 1,    //    2
    reg_soft_rst_hsp_brdg_imx_9_n: 1,    //    3
    reg_soft_rst_hsp_brdg_nd1_0_n: 1,    //    4
    reg_soft_rst_hsp_brdg_nd1_1_n: 1,    //    5
    reg_soft_rst_hsp_brdg_nd1_2_n: 1,    //    6
    reg_soft_rst_hsp_brdg_nd1_3_n: 1,    //    7
    reg_soft_rst_sync_fsc_clk_n: 1,    //      8
                              : 23;    //   31:9 reserved
}BCRG_CTRL_VD0_CRG_BND_VD04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_1014    crg_bnd_vd05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_vd0_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD0_CRG_BND_VD05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD0_CRG_BND_VD00_O24A0_T    crg_bnd_vd00;         // 0xCEC8_1000
    BCRG_CTRL_VD0_CRG_BND_VD01_O24A0_T    crg_bnd_vd01;         // 0xCEC8_1004
    BCRG_CTRL_VD0_CRG_BND_VD02_O24A0_T    crg_bnd_vd02;         // 0xCEC8_1008
    BCRG_CTRL_VD0_CRG_BND_VD03_O24A0_T    crg_bnd_vd03;         // 0xCEC8_100C
    BCRG_CTRL_VD0_CRG_BND_VD04_O24A0_T    crg_bnd_vd04;         // 0xCEC8_1010
    BCRG_CTRL_VD0_CRG_BND_VD05_O24A0_T    crg_bnd_vd05;         // 0xCEC8_1014
}BCRG_CTRL_VD0_REG_O24A0_T;
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

#define BCRG_CTRL_VD0_CRG_BND_VD00_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_VD0_CRG_BND_VD01_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_VD0_CRG_BND_VD02_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_VD0_CRG_BND_VD03_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_VD0_CRG_BND_VD04_O24A0_T_OFF              (BASEADDRESS+0x0010)
#define BCRG_CTRL_VD0_CRG_BND_VD05_O24A0_T_OFF              (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCEC8_1000    crg_bnd_vd00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_VD0_CRG_BND_VD00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_1004    crg_bnd_vd01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_VD0_CRG_BND_VD01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_1008    crg_bnd_vd02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fsc_clk_gate_en:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_100C    crg_bnd_vd03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_vd0_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_1010    crg_bnd_vd04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_nd1_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_usbsb_0_n: 1;    //  1
    UINT32 reg_soft_rst_hsp_brdg_imx_8_n: 1;    //  2
    UINT32 reg_soft_rst_hsp_brdg_imx_9_n: 1;    //  3
    UINT32 reg_soft_rst_hsp_brdg_nd1_0_n: 1;    //  4
    UINT32 reg_soft_rst_hsp_brdg_nd1_1_n: 1;    //  5
    UINT32 reg_soft_rst_hsp_brdg_nd1_2_n: 1;    //  6
    UINT32 reg_soft_rst_hsp_brdg_nd1_3_n: 1;    //  7
    UINT32 reg_soft_rst_sync_fsc_clk_n: 1;    //  8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_1014    crg_bnd_vd05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_vd0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD0_CRG_BND_VD00_O24A0_T    crg_bnd_vd00;         // 0xCEC8_1000
    BCRG_CTRL_VD0_CRG_BND_VD01_O24A0_T    crg_bnd_vd01;         // 0xCEC8_1004
    BCRG_CTRL_VD0_CRG_BND_VD02_O24A0_T    crg_bnd_vd02;         // 0xCEC8_1008
    BCRG_CTRL_VD0_CRG_BND_VD03_O24A0_T    crg_bnd_vd03;         // 0xCEC8_100C
    BCRG_CTRL_VD0_CRG_BND_VD04_O24A0_T    crg_bnd_vd04;         // 0xCEC8_1010
    BCRG_CTRL_VD0_CRG_BND_VD05_O24A0_T    crg_bnd_vd05;         // 0xCEC8_1014
}BCRG_CTRL_VD0_REG_O24A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_VD0_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

