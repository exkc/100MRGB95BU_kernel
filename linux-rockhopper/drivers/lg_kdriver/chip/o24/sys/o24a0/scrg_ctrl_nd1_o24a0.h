#ifndef _SCRG_CTRL_ND1_REG_O24A0_H_
#define _SCRG_CTRL_ND1_REG_O24A0_H_

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
    0xCCCA_0000    crg_nd10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ND1_CRG_ND10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCA_0004    crg_nd11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ND1_CRG_ND11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCA_0008    crg_nd12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_nd_clk_gate_en    :  1,    //      0
    reg_axi_nd_clk_gate_en    :  1,    //      1
    reg_nd_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_ND1_CRG_ND12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCA_000C    crg_nd13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_nd_n     :  1,    //      0
    reg_soft_rst_axi_nd_n     :  1,    //      1
    reg_soft_rst_h_imx_8_nd_bnd_n: 1,    //    2
    reg_soft_rst_h_imx_9_nd_bnd_n: 1,    //    3
    reg_soft_rst_h_nd0_2_nd_bnd_n: 1,    //    4
    reg_soft_rst_h_nd0_3_nd_bnd_n: 1,    //    5
    reg_soft_rst_h_nd1_0_nd_bnd_n: 1,    //    6
    reg_soft_rst_h_nd1_1_nd_bnd_n: 1,    //    7
    reg_soft_rst_h_nd1_2_nd_bnd_n: 1,    //    8
    reg_soft_rst_h_nd1_3_nd_bnd_n: 1,    //    9
    reg_soft_rst_nd_n         :  1,    //     10
    reg_soft_rst_p_nd1_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_nd1_0_axi_bnd_n: 1,    //  12
    reg_soft_rst_x_nd1_0_axi_n:  1,    //     13
                              : 18;    //  31:14 reserved
}SCRG_CTRL_ND1_CRG_ND13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCA_0010    crg_nd14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ND1_CRG_ND14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND1_CRG_ND10_O24A0_T     crg_nd10   ;             // 0xCCCA_0000
    SCRG_CTRL_ND1_CRG_ND11_O24A0_T     crg_nd11   ;             // 0xCCCA_0004
    SCRG_CTRL_ND1_CRG_ND12_O24A0_T     crg_nd12   ;             // 0xCCCA_0008
    SCRG_CTRL_ND1_CRG_ND13_O24A0_T     crg_nd13   ;             // 0xCCCA_000C
    SCRG_CTRL_ND1_CRG_ND14_O24A0_T     crg_nd14   ;             // 0xCCCA_0010
}SCRG_CTRL_ND1_REG_O24A0_T;
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

#define SCRG_CTRL_ND1_CRG_ND10_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_ND1_CRG_ND11_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_ND1_CRG_ND12_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_ND1_CRG_ND13_O24A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_ND1_CRG_ND14_O24A0_T_OFF                  (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCCA_0000    crg_nd10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ND1_CRG_ND10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCA_0004    crg_nd11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ND1_CRG_ND11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCA_0008    crg_nd12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_nd_clk_gate_en: 1;    //    0
    UINT32 reg_axi_nd_clk_gate_en: 1;    //    1
    UINT32 reg_nd_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_ND1_CRG_ND12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCA_000C    crg_nd13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_nd_n: 1;    //     0
    UINT32 reg_soft_rst_axi_nd_n: 1;    //     1
    UINT32 reg_soft_rst_h_imx_8_nd_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_h_imx_9_nd_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_nd0_2_nd_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_nd0_3_nd_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_nd1_0_nd_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_nd1_1_nd_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_nd1_2_nd_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_nd1_3_nd_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_nd_n  :  1;    //     10
    UINT32 reg_soft_rst_p_nd1_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_nd1_0_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_x_nd1_0_axi_n: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}SCRG_CTRL_ND1_CRG_ND13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCA_0010    crg_nd14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core400_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ND1_CRG_ND14_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_nd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND1_CRG_ND10_O24A0_T     crg_nd10   ;             // 0xCCCA_0000
    SCRG_CTRL_ND1_CRG_ND11_O24A0_T     crg_nd11   ;             // 0xCCCA_0004
    SCRG_CTRL_ND1_CRG_ND12_O24A0_T     crg_nd12   ;             // 0xCCCA_0008
    SCRG_CTRL_ND1_CRG_ND13_O24A0_T     crg_nd13   ;             // 0xCCCA_000C
    SCRG_CTRL_ND1_CRG_ND14_O24A0_T     crg_nd14   ;             // 0xCCCA_0010
}SCRG_CTRL_ND1_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_ND1_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

