#ifndef _MCRG_CTRL_IMX_REG_H_
#define _MCRG_CTRL_IMX_REG_H_

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
    0x2A_0000    crg_main_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_IMX_CRG_MAIN_IMX00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2A_0004    crg_main_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_IMX_CRG_MAIN_IMX01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2A_0008    crg_main_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_imx_phy1_tmdsqp_clk_inv_sel: 1,    //  0
    reg_imx_phy2_tmdsqp_clk_inv_sel: 1,    //  1
    reg_imx_phy3_tmdsqp_clk_inv_sel: 1,    //  2
    reg_imx_phy4_tmdsqp_clk_inv_sel: 1,    //  3
                              : 28;    //   31:4 reserved
}MCRG_CTRL_IMX_CRG_MAIN_IMX02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_main_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_IMX_CRG_MAIN_IMX00_O22A0_T    crg_main_imx00;      // 0x2A_0000
    MCRG_CTRL_IMX_CRG_MAIN_IMX01_O22A0_T    crg_main_imx01;      // 0x2A_0004
    MCRG_CTRL_IMX_CRG_MAIN_IMX02_O22A0_T    crg_main_imx02;      // 0x2A_0008
}MCRG_CTRL_IMX_REG_O22A0_T;
/* 3 regs */

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

#define MCRG_CTRL_IMX_CRG_MAIN_IMX00_O22A0_T_OFF             (BASEADDRESS+0x0000)
#define MCRG_CTRL_IMX_CRG_MAIN_IMX01_O22A0_T_OFF             (BASEADDRESS+0x0004)
#define MCRG_CTRL_IMX_CRG_MAIN_IMX02_O22A0_T_OFF             (BASEADDRESS+0x0008)

/*-----------------------------------------------------------------------------------------
    0x2A_0000    crg_main_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_IMX_CRG_MAIN_IMX00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2A_0004    crg_main_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_IMX_CRG_MAIN_IMX01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2A_0008    crg_main_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_imx_phy1_tmdsqp_clk_inv_sel: 1;    //  0
    UINT32 reg_imx_phy2_tmdsqp_clk_inv_sel: 1;    //  1
    UINT32 reg_imx_phy3_tmdsqp_clk_inv_sel: 1;    //  2
    UINT32 reg_imx_phy4_tmdsqp_clk_inv_sel: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_IMX_CRG_MAIN_IMX02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_main_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_IMX_CRG_MAIN_IMX00_O22A0_T    crg_main_imx00;      // 0x2A_0000
    MCRG_CTRL_IMX_CRG_MAIN_IMX01_O22A0_T    crg_main_imx01;      // 0x2A_0004
    MCRG_CTRL_IMX_CRG_MAIN_IMX02_O22A0_T    crg_main_imx02;      // 0x2A_0008
}MCRG_CTRL_IMX_REG_O22A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

