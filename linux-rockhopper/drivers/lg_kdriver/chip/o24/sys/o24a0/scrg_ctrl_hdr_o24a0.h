#ifndef _SCRG_CTRL_HDR_REG_O24A0_H_
#define _SCRG_CTRL_HDR_REG_O24A0_H_

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
    0xCCC2_0000    crg_hdr0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_HDR_CRG_HDR0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC2_0004    crg_hdr1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_HDR_CRG_HDR1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC2_0008    crg_hdr2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_de_clk_gate_en        :  1,    //      1
    reg_hdr_clk_gate_en       :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_HDR_CRG_HDR2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC2_000C    crg_hdr3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_de_n         :  1,    //      1
    reg_soft_rst_h_hdr_0_de_bnd_n: 1,    //    2
    reg_soft_rst_h_hdr_1_de_bnd_n: 1,    //    3
    reg_soft_rst_h_hdr_2_de_bnd_n: 1,    //    4
    reg_soft_rst_h_hdr_3_de_bnd_n: 1,    //    5
    reg_soft_rst_h_hdr_4_de_bnd_n: 1,    //    6
    reg_soft_rst_h_hdr_5_de_bnd_n: 1,    //    7
    reg_soft_rst_h_imx_0_de_bnd_n: 1,    //    8
    reg_soft_rst_h_imx_13_de_bnd_n: 1,    //   9
    reg_soft_rst_h_imx_14_de_bnd_n: 1,    //  10
    reg_soft_rst_h_imx_15_de_bnd_n: 1,    //  11
    reg_soft_rst_h_imx_16_de_bnd_n: 1,    //  12
    reg_soft_rst_h_imx_1_de_bnd_n: 1,    //   13
    reg_soft_rst_h_imx_2_de_bnd_n: 1,    //   14
    reg_soft_rst_h_imx_3_de_bnd_n: 1,    //   15
    reg_soft_rst_h_imx_4_de_bnd_n: 1,    //   16
    reg_soft_rst_h_imx_5_de_bnd_n: 1,    //   17
    reg_soft_rst_hdr_n        :  1,    //     18
                              : 13;    //  31:19 reserved
}SCRG_CTRL_HDR_CRG_HDR3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC2_0010    crg_hdr4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdr_clk_sel           :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_HDR_CRG_HDR4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDR_CRG_HDR0_O24A0_T     crg_hdr0   ;             // 0xCCC2_0000
    SCRG_CTRL_HDR_CRG_HDR1_O24A0_T     crg_hdr1   ;             // 0xCCC2_0004
    SCRG_CTRL_HDR_CRG_HDR2_O24A0_T     crg_hdr2   ;             // 0xCCC2_0008
    SCRG_CTRL_HDR_CRG_HDR3_O24A0_T     crg_hdr3   ;             // 0xCCC2_000C
    SCRG_CTRL_HDR_CRG_HDR4_O24A0_T     crg_hdr4   ;             // 0xCCC2_0010
}SCRG_CTRL_HDR_REG_O24A0_T;
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

#define SCRG_CTRL_HDR_CRG_O24A0_HDR0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_HDR_CRG_O24A0_HDR1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_HDR_CRG_O24A0_HDR2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_HDR_CRG_O24A0_HDR3_O24A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_HDR_CRG_O24A0_HDR4_O24A0_T_OFF                  (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCC2_0000    crg_hdr0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_HDR_CRG_HDR0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC2_0004    crg_hdr1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_HDR_CRG_HDR1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC2_0008    crg_hdr2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_de_clk_gate_en :  1;    //      1
    UINT32 reg_hdr_clk_gate_en:  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC2_000C    crg_hdr3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_de_n  :  1;    //      1
    UINT32 reg_soft_rst_h_hdr_0_de_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_h_hdr_1_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_hdr_2_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_hdr_3_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_hdr_4_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_hdr_5_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_imx_0_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_imx_13_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_imx_14_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_imx_15_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_imx_16_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_imx_1_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_imx_2_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_imx_3_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_imx_4_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_imx_5_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_hdr_n :  1;    //     18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC2_0010    crg_hdr4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdr_clk_sel    :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_HDR_CRG_HDR4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_HDR_CRG_HDR0_O24A0_T     crg_hdr0   ;             // 0xCCC2_0000
    SCRG_CTRL_HDR_CRG_HDR1_O24A0_T     crg_hdr1   ;             // 0xCCC2_0004
    SCRG_CTRL_HDR_CRG_HDR2_O24A0_T     crg_hdr2   ;             // 0xCCC2_0008
    SCRG_CTRL_HDR_CRG_HDR3_O24A0_T     crg_hdr3   ;             // 0xCCC2_000C
    SCRG_CTRL_HDR_CRG_HDR4_O24A0_T     crg_hdr4   ;             // 0xCCC2_0010
}SCRG_CTRL_HDR_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_HDR_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

