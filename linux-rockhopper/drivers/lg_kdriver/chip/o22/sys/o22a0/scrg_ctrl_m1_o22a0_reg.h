#ifndef _SCRG_CTRL_M1_REG_H_
#define _SCRG_CTRL_M1_REG_H_

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
    0x3C_0000    crg_m100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_M1_CRG_M100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3C_0004    crg_m101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_M1_CRG_M101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3C_0008    crg_m102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_i_ddrc_clk_gate_en    :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_M1_CRG_M102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3C_000C    crg_m103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_apb_phy_n    :  1,    //      1
    reg_soft_rst_ddrc_n       :  1,    //      2
    reg_soft_rst_x_lbus_4_axi_n: 1,    //      3
    reg_soft_rst_x_lbus_5_axi_n: 1,    //      4
    reg_soft_rst_x_lbus_6_axi_n: 1,    //      5
    reg_soft_rst_x_lbus_7_axi_n: 1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_M1_CRG_M103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3C_0010    crg_m104 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_M1_CRG_M104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_m1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_M1_CRG_M100_O22A0_T            crg_m100   ;             // 0x3C_0000
    SCRG_CTRL_M1_CRG_M101_O22A0_T            crg_m101   ;             // 0x3C_0004
    SCRG_CTRL_M1_CRG_M102_O22A0_T            crg_m102   ;             // 0x3C_0008
    SCRG_CTRL_M1_CRG_M103_O22A0_T            crg_m103   ;             // 0x3C_000C
    SCRG_CTRL_M1_CRG_M104_O22A0_T            crg_m104   ;             // 0x3C_0010
}SCRG_CTRL_M1_REG_O22A0_T;
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

#define SCRG_CTRL_M1_CRG_M100_O22A0_T_OFF                         (BASEADDRESS+0x0000)
#define SCRG_CTRL_M1_CRG_M101_O22A0_T_OFF                         (BASEADDRESS+0x0004)
#define SCRG_CTRL_M1_CRG_M102_O22A0_T_OFF                         (BASEADDRESS+0x0008)
#define SCRG_CTRL_M1_CRG_M103_O22A0_T_OFF                         (BASEADDRESS+0x000C)
#define SCRG_CTRL_M1_CRG_M104_O22A0_T_OFF                         (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x3C_0000    crg_m100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_M1_CRG_M100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3C_0004    crg_m101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_M1_CRG_M101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3C_0008    crg_m102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_i_ddrc_clk_gate_en: 1;    //    1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_M1_CRG_M102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3C_000C    crg_m103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_apb_phy_n: 1;    //    1
    UINT32 reg_soft_rst_ddrc_n:  1;    //      2
    UINT32 reg_soft_rst_x_lbus_4_axi_n: 1;    //  3
    UINT32 reg_soft_rst_x_lbus_5_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_lbus_6_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_lbus_7_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_M1_CRG_M103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3C_0010    crg_m104 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_M1_CRG_M104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_m1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_M1_CRG_M100_O22A0_T            crg_m100   ;             // 0x3C_0000
    SCRG_CTRL_M1_CRG_M101_O22A0_T            crg_m101   ;             // 0x3C_0004
    SCRG_CTRL_M1_CRG_M102_O22A0_T            crg_m102   ;             // 0x3C_0008
    SCRG_CTRL_M1_CRG_M103_O22A0_T            crg_m103   ;             // 0x3C_000C
    SCRG_CTRL_M1_CRG_M104_O22A0_T            crg_m104   ;             // 0x3C_0010
}SCRG_CTRL_M1_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

