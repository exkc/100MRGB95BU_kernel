#ifndef _MCRG_CTRL_CVI_REG_O24A0_H_
#define _MCRG_CTRL_CVI_REG_O24A0_H_

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
    0xCCD7_0000    crg_main_cvi0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_CVI_CRG_MAIN_CVI0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_0004    crg_main_cvi1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_CVI_CRG_MAIN_CVI1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_0008    crg_main_cvi2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi_core884_clk_inv_sel: 1,    //      0
    reg_cvi_cvd54_clk_inv_sel :  1,    //      1
    reg_cvi_hdmirx_prt1_tmdsqp_clk_inv_sel: 1,    //  2
    reg_cvi_hdmirx_prt2_tmdsqp_clk_inv_sel: 1,    //  3
    reg_cvi_hdmirx_prt3_tmdsqp_clk_inv_sel: 1,    //  4
    reg_cvi_hdmirx_prt4_tmdsqp_clk_inv_sel: 1,    //  5
                              : 26;    //   31:6 reserved
}MCRG_CTRL_CVI_CRG_MAIN_CVI2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_CVI_CRG_MAIN_CVI0_O24A0_T    crg_main_cvi0;       // 0xCCD7_0000
    MCRG_CTRL_CVI_CRG_MAIN_CVI1_O24A0_T    crg_main_cvi1;       // 0xCCD7_0004
    MCRG_CTRL_CVI_CRG_MAIN_CVI2_O24A0_T    crg_main_cvi2;       // 0xCCD7_0008
}MCRG_CTRL_CVI_REG_O24A0_T;
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

#define MCRG_CTRL_CVI_CRG_MAIN_CVI0_O24A0_T_OFF             (BASEADDRESS+0x0000)
#define MCRG_CTRL_CVI_CRG_MAIN_CVI1_O24A0_T_OFF             (BASEADDRESS+0x0004)
#define MCRG_CTRL_CVI_CRG_MAIN_CVI2_O24A0_T_OFF             (BASEADDRESS+0x0008)

/*-----------------------------------------------------------------------------------------
    0xCCD7_0000    crg_main_cvi0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_CVI_CRG_MAIN_CVI0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_0004    crg_main_cvi1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_CVI_CRG_MAIN_CVI1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_0008    crg_main_cvi2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvi_core884_clk_inv_sel: 1;    //  0
    UINT32 reg_cvi_cvd54_clk_inv_sel: 1;    //  1
    UINT32 reg_cvi_hdmirx_prt1_tmdsqp_clk_inv_sel: 1;    //  2
    UINT32 reg_cvi_hdmirx_prt2_tmdsqp_clk_inv_sel: 1;    //  3
    UINT32 reg_cvi_hdmirx_prt3_tmdsqp_clk_inv_sel: 1;    //  4
    UINT32 reg_cvi_hdmirx_prt4_tmdsqp_clk_inv_sel: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}MCRG_CTRL_CVI_CRG_MAIN_CVI2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_CVI_CRG_MAIN_CVI0_O24A0_T    crg_main_cvi0;       // 0xCCD7_0000
    MCRG_CTRL_CVI_CRG_MAIN_CVI1_O24A0_T    crg_main_cvi1;       // 0xCCD7_0004
    MCRG_CTRL_CVI_CRG_MAIN_CVI2_O24A0_T    crg_main_cvi2;       // 0xCCD7_0008
}MCRG_CTRL_CVI_REG_O24A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MCRG_CTRL_CVI_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

