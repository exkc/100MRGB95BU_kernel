#ifndef _SCRG_CTRL_LNX1_REG_O24A0_H_
#define _SCRG_CTRL_LNX1_REG_O24A0_H_

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
    0xCC96_0000    crg_lnx10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LNX1_CRG_LNX10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0004    crg_lnx11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LNX1_CRG_LNX11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0008    crg_lnx12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lnx1_apb_clk_gate_en  :  1,    //      0
    reg_lnx1_axi_clk_gate_en  :  1,    //      1
    reg_lnx1_core_clk_gate_en :  1,    //      2
    reg_lnx1_jtag_tck_gate_en :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_LNX1_CRG_LNX12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_000C    crg_lnx13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_h_lnx0_0_lnx1_core_bnd_n: 1,    //  0
    reg_soft_rst_h_lnx1_0_lnx1_core_bnd_n: 1,    //  1
    reg_soft_rst_h_lnx1_1_lnx1_core_bnd_n: 1,    //  2
    reg_soft_rst_lnx1_apb_n   :  1,    //      3
    reg_soft_rst_lnx1_axi_flush_n: 1,    //    4
    reg_soft_rst_lnx1_axi_n   :  1,    //      5
    reg_soft_rst_lnx1_core_n  :  1,    //      6
    reg_soft_rst_p_lnx1_0_axi_bnd_n: 1,    //  7
    reg_soft_rst_x_lnx1_0_axi_bnd_n: 1,    //  8
    reg_soft_rst_x_lnx1_0_axi_n: 1,    //      9
                              : 22;    //  31:10 reserved
}SCRG_CTRL_LNX1_CRG_LNX13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0010    crg_lnx14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lnx1_core_clk_sel     :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}SCRG_CTRL_LNX1_CRG_LNX14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lnx1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LNX1_CRG_LNX10_O24A0_T    crg_lnx10 ;             // 0xCC96_0000
    SCRG_CTRL_LNX1_CRG_LNX11_O24A0_T    crg_lnx11 ;             // 0xCC96_0004
    SCRG_CTRL_LNX1_CRG_LNX12_O24A0_T    crg_lnx12 ;             // 0xCC96_0008
    SCRG_CTRL_LNX1_CRG_LNX13_O24A0_T    crg_lnx13 ;             // 0xCC96_000C
    SCRG_CTRL_LNX1_CRG_LNX14_O24A0_T    crg_lnx14 ;             // 0xCC96_0010
}SCRG_CTRL_LNX1_REG_O24A0_T;
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

#define SCRG_CTRL_LNX1_CRG_LNX10_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_LNX1_CRG_LNX11_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_LNX1_CRG_LNX12_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_LNX1_CRG_LNX13_O24A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_LNX1_CRG_LNX14_O24A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC96_0000    crg_lnx10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LNX1_CRG_LNX10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0004    crg_lnx11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LNX1_CRG_LNX11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0008    crg_lnx12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lnx1_apb_clk_gate_en: 1;    //  0
    UINT32 reg_lnx1_axi_clk_gate_en: 1;    //  1
    UINT32 reg_lnx1_core_clk_gate_en: 1;    //  2
    UINT32 reg_lnx1_jtag_tck_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_LNX1_CRG_LNX12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_000C    crg_lnx13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_h_lnx0_0_lnx1_core_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_h_lnx1_0_lnx1_core_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_h_lnx1_1_lnx1_core_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_lnx1_apb_n: 1;    //   3
    UINT32 reg_soft_rst_lnx1_axi_flush_n: 1;    //  4
    UINT32 reg_soft_rst_lnx1_axi_n: 1;    //   5
    UINT32 reg_soft_rst_lnx1_core_n: 1;    //  6
    UINT32 reg_soft_rst_p_lnx1_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_lnx1_0_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_x_lnx1_0_axi_n: 1;    //  9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}SCRG_CTRL_LNX1_CRG_LNX13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC96_0010    crg_lnx14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lnx1_core_clk_sel: 2;    //  1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_LNX1_CRG_LNX14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lnx1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LNX1_CRG_LNX10_O24A0_T    crg_lnx10 ;             // 0xCC96_0000
    SCRG_CTRL_LNX1_CRG_LNX11_O24A0_T    crg_lnx11 ;             // 0xCC96_0004
    SCRG_CTRL_LNX1_CRG_LNX12_O24A0_T    crg_lnx12 ;             // 0xCC96_0008
    SCRG_CTRL_LNX1_CRG_LNX13_O24A0_T    crg_lnx13 ;             // 0xCC96_000C
    SCRG_CTRL_LNX1_CRG_LNX14_O24A0_T    crg_lnx14 ;             // 0xCC96_0010
}SCRG_CTRL_LNX1_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_LNX1_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

