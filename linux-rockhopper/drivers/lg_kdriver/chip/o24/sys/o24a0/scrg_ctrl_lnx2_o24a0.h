#ifndef _SCRG_CTRL_LNX2_REG_O24A0_H_
#define _SCRG_CTRL_LNX2_REG_O24A0_H_

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
    0xCCD9_0000    crg_lnx20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LNX2_CRG_LNX20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD9_0004    crg_lnx21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LNX2_CRG_LNX21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD9_0008    crg_lnx22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lnx2_apb_clk_gate_en  :  1,    //      0
    reg_lnx2_axi_clk_gate_en  :  1,    //      1
    reg_lnx2_core_clk_gate_en :  1,    //      2
    reg_lnx2_jtag_tck_gate_en :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_LNX2_CRG_LNX22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD9_000C    crg_lnx23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_lnx2_apb_n   :  1,    //      0
    reg_soft_rst_lnx2_axi_flush_n: 1,    //    1
    reg_soft_rst_lnx2_axi_n   :  1,    //      2
    reg_soft_rst_lnx2_core_n  :  1,    //      3
    reg_soft_rst_p_lnx2_0_axi_bnd_n: 1,    //  4
    reg_soft_rst_x_lnx2_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_lnx2_0_axi_n: 1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_LNX2_CRG_LNX23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD9_0010    crg_lnx24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lnx2_core_clk_sel     :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}SCRG_CTRL_LNX2_CRG_LNX24_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lnx2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LNX2_CRG_LNX20_O24A0_T    crg_lnx20 ;             // 0xCCD9_0000
    SCRG_CTRL_LNX2_CRG_LNX21_O24A0_T    crg_lnx21 ;             // 0xCCD9_0004
    SCRG_CTRL_LNX2_CRG_LNX22_O24A0_T    crg_lnx22 ;             // 0xCCD9_0008
    SCRG_CTRL_LNX2_CRG_LNX23_O24A0_T    crg_lnx23 ;             // 0xCCD9_000C
    SCRG_CTRL_LNX2_CRG_LNX24_O24A0_T    crg_lnx24 ;             // 0xCCD9_0010
}SCRG_CTRL_LNX2_REG_O24A0_T;
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

#define SCRG_CTRL_LNX2_CRG_LNX20_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_LNX2_CRG_LNX21_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_LNX2_CRG_LNX22_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_LNX2_CRG_LNX23_O24A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_LNX2_CRG_LNX24_O24A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCD9_0000    crg_lnx20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LNX2_CRG_LNX20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD9_0004    crg_lnx21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LNX2_CRG_LNX21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD9_0008    crg_lnx22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lnx2_apb_clk_gate_en: 1;    //  0
    UINT32 reg_lnx2_axi_clk_gate_en: 1;    //  1
    UINT32 reg_lnx2_core_clk_gate_en: 1;    //  2
    UINT32 reg_lnx2_jtag_tck_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_LNX2_CRG_LNX22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD9_000C    crg_lnx23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_lnx2_apb_n: 1;    //   0
    UINT32 reg_soft_rst_lnx2_axi_flush_n: 1;    //  1
    UINT32 reg_soft_rst_lnx2_axi_n: 1;    //   2
    UINT32 reg_soft_rst_lnx2_core_n: 1;    //  3
    UINT32 reg_soft_rst_p_lnx2_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_lnx2_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_lnx2_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_LNX2_CRG_LNX23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD9_0010    crg_lnx24 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lnx2_core_clk_sel: 2;    //  1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_LNX2_CRG_LNX24_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lnx2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LNX2_CRG_LNX20_O24A0_T    crg_lnx20 ;             // 0xCCD9_0000
    SCRG_CTRL_LNX2_CRG_LNX21_O24A0_T    crg_lnx21 ;             // 0xCCD9_0004
    SCRG_CTRL_LNX2_CRG_LNX22_O24A0_T    crg_lnx22 ;             // 0xCCD9_0008
    SCRG_CTRL_LNX2_CRG_LNX23_O24A0_T    crg_lnx23 ;             // 0xCCD9_000C
    SCRG_CTRL_LNX2_CRG_LNX24_O24A0_T    crg_lnx24 ;             // 0xCCD9_0010
}SCRG_CTRL_LNX2_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_LNX2_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

