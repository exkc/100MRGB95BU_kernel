#ifndef _SCRG_CTRL_M2_REG_O24A0_H_
#define _SCRG_CTRL_M2_REG_O24A0_H_

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
    0xC452_0000    crg_m20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_M2_CRG_M20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_0004    crg_m21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_M2_CRG_M21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_0008    crg_m22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_i_ddrc_clk_gate_en    :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_M2_CRG_M22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_000C    crg_m23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_apb_phy_n    :  1,    //      1
    reg_soft_rst_ddrc_n       :  1,    //      2
    reg_soft_rst_p_ddr2sb_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_p_lbus_10_axi_bnd_n: 1,    //  4
    reg_soft_rst_p_lbus_11_axi_bnd_n: 1,    //  5
    reg_soft_rst_p_lbus_9_axi_bnd_n: 1,    //  6
    reg_soft_rst_x_ddr2sb_0_axi_n: 1,    //    7
    reg_soft_rst_x_lbus_10_axi_n: 1,    //     8
    reg_soft_rst_x_lbus_11_axi_n: 1,    //     9
    reg_soft_rst_x_lbus_9_axi_n: 1,    //     10
                              : 21;    //  31:11 reserved
}SCRG_CTRL_M2_CRG_M23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_m2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_M2_CRG_M20_O24A0_T       crg_m20    ;             // 0xC452_0000
    SCRG_CTRL_M2_CRG_M21_O24A0_T       crg_m21    ;             // 0xC452_0004
    SCRG_CTRL_M2_CRG_M22_O24A0_T       crg_m22    ;             // 0xC452_0008
    SCRG_CTRL_M2_CRG_M23_O24A0_T       crg_m23    ;             // 0xC452_000C
}SCRG_CTRL_M2_REG_O24A0_T;
/* 4 regs */

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

#define SCRG_CTRL_M2_CRG_M20_O24A0_T_OFF                    (BASEADDRESS+0x0000)
#define SCRG_CTRL_M2_CRG_M21_O24A0_T_OFF                    (BASEADDRESS+0x0004)
#define SCRG_CTRL_M2_CRG_M22_O24A0_T_OFF                    (BASEADDRESS+0x0008)
#define SCRG_CTRL_M2_CRG_M23_O24A0_T_OFF                    (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC452_0000    crg_m20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_M2_CRG_M20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_0004    crg_m21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_M2_CRG_M21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_0008    crg_m22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_i_ddrc_clk_gate_en: 1;    //    1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_M2_CRG_M22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC452_000C    crg_m23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_apb_phy_n: 1;    //    1
    UINT32 reg_soft_rst_ddrc_n:  1;    //      2
    UINT32 reg_soft_rst_p_ddr2sb_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_lbus_10_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_lbus_11_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_lbus_9_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_ddr2sb_0_axi_n: 1;    //  7
    UINT32 reg_soft_rst_x_lbus_10_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_lbus_11_axi_n: 1;    //  9
    UINT32 reg_soft_rst_x_lbus_9_axi_n: 1;    //  10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_M2_CRG_M23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_m2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_M2_CRG_M20_O24A0_T       crg_m20    ;             // 0xC452_0000
    SCRG_CTRL_M2_CRG_M21_O24A0_T       crg_m21    ;             // 0xC452_0004
    SCRG_CTRL_M2_CRG_M22_O24A0_T       crg_m22    ;             // 0xC452_0008
    SCRG_CTRL_M2_CRG_M23_O24A0_T       crg_m23    ;             // 0xC452_000C
}SCRG_CTRL_M2_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_M2_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

