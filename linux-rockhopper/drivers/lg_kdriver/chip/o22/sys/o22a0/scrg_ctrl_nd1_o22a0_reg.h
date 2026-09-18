#ifndef _SCRG_CTRL_ND1_REG_H_
#define _SCRG_CTRL_ND1_REG_H_

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
    0x4C_0000    crg_nd100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ND1_CRG_ND100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_0004    crg_nd101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ND1_CRG_ND101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_0008    crg_nd102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_ND1_CRG_ND102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_000C    crg_nd103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_h_imx_12_de_bnd_n: 1,    //   3
    reg_soft_rst_h_imx_13_de_bnd_n: 1,    //   4
    reg_soft_rst_h_nd0_2_de_bnd_n: 1,    //    5
    reg_soft_rst_h_nd0_3_de_bnd_n: 1,    //    6
    reg_soft_rst_h_nd1_0_de_bnd_n: 1,    //    7
    reg_soft_rst_h_nd1_1_de_bnd_n: 1,    //    8
    reg_soft_rst_h_nd1_2_de_bnd_n: 1,    //    9
    reg_soft_rst_h_nd1_3_de_bnd_n: 1,    //   10
    reg_soft_rst_h_nd1_4_de_bnd_n: 1,    //   11
    reg_soft_rst_h_nd1_5_de_bnd_n: 1,    //   12
    reg_soft_rst_h_nd1_6_de_bnd_n: 1,    //   13
    reg_soft_rst_h_nd1_7_de_bnd_n: 1,    //   14
    reg_soft_rst_p_nd1_0_axi_bnd_n: 1,    //  15
    reg_soft_rst_x_nd1_0_axi_bnd_n: 1,    //  16
    reg_soft_rst_x_nd1_0_axi_n:  1,    //     17
                              : 14;    //  31:18 reserved
}SCRG_CTRL_ND1_CRG_ND103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_0010    crg_nd104 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ND1_CRG_ND104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_0014    crg_nd105 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ND1_CRG_ND105_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_0018    crg_nd106 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ND1_CRG_ND106_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND1_CRG_ND100_O22A0_T          crg_nd100  ;             // 0x4C_0000
    SCRG_CTRL_ND1_CRG_ND101_O22A0_T          crg_nd101  ;             // 0x4C_0004
    SCRG_CTRL_ND1_CRG_ND102_O22A0_T          crg_nd102  ;             // 0x4C_0008
    SCRG_CTRL_ND1_CRG_ND103_O22A0_T          crg_nd103  ;             // 0x4C_000C
    SCRG_CTRL_ND1_CRG_ND104_O22A0_T          crg_nd104  ;             // 0x4C_0010
    SCRG_CTRL_ND1_CRG_ND105_O22A0_T          crg_nd105  ;             // 0x4C_0014
    SCRG_CTRL_ND1_CRG_ND106_O22A0_T          crg_nd106  ;             // 0x4C_0018
}SCRG_CTRL_ND1_REG_O22A0_T;
/* 7 regs */

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

#define SCRG_CTRL_ND1_CRG_ND100_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_ND1_CRG_ND101_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_ND1_CRG_ND102_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_ND1_CRG_ND103_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_ND1_CRG_ND104_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_ND1_CRG_ND105_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_ND1_CRG_ND106_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x4C_0000    crg_nd100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ND1_CRG_ND100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_0004    crg_nd101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ND1_CRG_ND101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_0008    crg_nd102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_ND1_CRG_ND102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_000C    crg_nd103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_h_imx_12_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_imx_13_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_nd0_2_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_nd0_3_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_nd1_0_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_nd1_1_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_nd1_2_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_nd1_3_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_nd1_4_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_nd1_5_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_nd1_6_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_nd1_7_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_p_nd1_0_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_x_nd1_0_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_x_nd1_0_axi_n: 1;    //  17
    UINT32 resvd00            : 14;    //  31:18 reserved
    };
}SCRG_CTRL_ND1_CRG_ND103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_0010    crg_nd104 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ND1_CRG_ND104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_0014    crg_nd105 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ND1_CRG_ND105_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4C_0018    crg_nd106 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ND1_CRG_ND106_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND1_CRG_ND100_O22A0_T          crg_nd100  ;             // 0x4C_0000
    SCRG_CTRL_ND1_CRG_ND101_O22A0_T          crg_nd101  ;             // 0x4C_0004
    SCRG_CTRL_ND1_CRG_ND102_O22A0_T          crg_nd102  ;             // 0x4C_0008
    SCRG_CTRL_ND1_CRG_ND103_O22A0_T          crg_nd103  ;             // 0x4C_000C
    SCRG_CTRL_ND1_CRG_ND104_O22A0_T          crg_nd104  ;             // 0x4C_0010
    SCRG_CTRL_ND1_CRG_ND105_O22A0_T          crg_nd105  ;             // 0x4C_0014
    SCRG_CTRL_ND1_CRG_ND106_O22A0_T          crg_nd106  ;             // 0x4C_0018
}SCRG_CTRL_ND1_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

