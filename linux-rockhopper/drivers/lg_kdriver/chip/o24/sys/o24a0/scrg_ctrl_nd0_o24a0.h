#ifndef _SCRG_CTRL_ND0_REG_O24A0_H_
#define _SCRG_CTRL_ND0_REG_O24A0_H_

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
    0xCCC7_0000    crg_nd00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ND0_CRG_ND00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC7_0004    crg_nd01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ND0_CRG_ND01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC7_0008    crg_nd02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_nd_clk_gate_en    :  1,    //      0
    reg_axi_nd_clk_gate_en    :  1,    //      1
    reg_nd_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_ND0_CRG_ND02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC7_000C    crg_nd03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_nd_n     :  1,    //      0
    reg_soft_rst_axi_nd_n     :  1,    //      1
    reg_soft_rst_h_imx_6_nd_bnd_n: 1,    //    2
    reg_soft_rst_h_imx_7_nd_bnd_n: 1,    //    3
    reg_soft_rst_h_nd0_0_nd_bnd_n: 1,    //    4
    reg_soft_rst_h_nd0_1_nd_bnd_n: 1,    //    5
    reg_soft_rst_h_nd0_2_nd_bnd_n: 1,    //    6
    reg_soft_rst_h_nd0_3_nd_bnd_n: 1,    //    7
    reg_soft_rst_h_nd0_4_nd_bnd_n: 1,    //    8
    reg_soft_rst_h_nd0_5_nd_bnd_n: 1,    //    9
    reg_soft_rst_nd_n         :  1,    //     10
    reg_soft_rst_p_nd0_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_nd0_0_axi_bnd_n: 1,    //  12
    reg_soft_rst_x_nd0_0_axi_n:  1,    //     13
                              : 18;    //  31:14 reserved
}SCRG_CTRL_ND0_CRG_ND03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC7_0010    crg_nd04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_core400_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ND0_CRG_ND04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND0_CRG_ND00_O24A0_T     crg_nd00   ;             // 0xCCC7_0000
    SCRG_CTRL_ND0_CRG_ND01_O24A0_T     crg_nd01   ;             // 0xCCC7_0004
    SCRG_CTRL_ND0_CRG_ND02_O24A0_T     crg_nd02   ;             // 0xCCC7_0008
    SCRG_CTRL_ND0_CRG_ND03_O24A0_T     crg_nd03   ;             // 0xCCC7_000C
    SCRG_CTRL_ND0_CRG_ND04_O24A0_T     crg_nd04   ;             // 0xCCC7_0010
}SCRG_CTRL_ND0_REG_O24A0_T;
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

#define SCRG_CTRL_ND0_CRG_ND00_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_ND0_CRG_ND01_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_ND0_CRG_ND02_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_ND0_CRG_ND03_O24A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_ND0_CRG_ND04_O24A0_T_OFF                  (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCC7_0000    crg_nd00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ND0_CRG_ND00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC7_0004    crg_nd01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ND0_CRG_ND01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC7_0008    crg_nd02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_nd_clk_gate_en: 1;    //    0
    UINT32 reg_axi_nd_clk_gate_en: 1;    //    1
    UINT32 reg_nd_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_ND0_CRG_ND02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC7_000C    crg_nd03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_nd_n: 1;    //     0
    UINT32 reg_soft_rst_axi_nd_n: 1;    //     1
    UINT32 reg_soft_rst_h_imx_6_nd_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_h_imx_7_nd_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_nd0_0_nd_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_nd0_1_nd_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_nd0_2_nd_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_nd0_3_nd_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_nd0_4_nd_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_nd0_5_nd_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_nd_n  :  1;    //     10
    UINT32 reg_soft_rst_p_nd0_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_nd0_0_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_x_nd0_0_axi_n: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}SCRG_CTRL_ND0_CRG_ND03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC7_0010    crg_nd04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_core400_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ND0_CRG_ND04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND0_CRG_ND00_O24A0_T     crg_nd00   ;             // 0xCCC7_0000
    SCRG_CTRL_ND0_CRG_ND01_O24A0_T     crg_nd01   ;             // 0xCCC7_0004
    SCRG_CTRL_ND0_CRG_ND02_O24A0_T     crg_nd02   ;             // 0xCCC7_0008
    SCRG_CTRL_ND0_CRG_ND03_O24A0_T     crg_nd03   ;             // 0xCCC7_000C
    SCRG_CTRL_ND0_CRG_ND04_O24A0_T     crg_nd04   ;             // 0xCCC7_0010
}SCRG_CTRL_ND0_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_ND0_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

