#ifndef _SCRG_CTRL_ME1_REG_O24A0_H_
#define _SCRG_CTRL_ME1_REG_O24A0_H_

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
    0xCC8B_0000    crg_me10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ME1_CRG_ME10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8B_0004    crg_me11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ME1_CRG_ME11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8B_0008    crg_me12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_ME1_CRG_ME12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8B_000C    crg_me13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_me0_0_de_bnd_n: 1,    //    3
    reg_soft_rst_p_me1_0_axi_bnd_n: 1,    //   4
    reg_soft_rst_x_me1_0_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_me1_0_axi_n:  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_ME1_CRG_ME13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME1_CRG_ME10_O24A0_T     crg_me10   ;             // 0xCC8B_0000
    SCRG_CTRL_ME1_CRG_ME11_O24A0_T     crg_me11   ;             // 0xCC8B_0004
    SCRG_CTRL_ME1_CRG_ME12_O24A0_T     crg_me12   ;             // 0xCC8B_0008
    SCRG_CTRL_ME1_CRG_ME13_O24A0_T     crg_me13   ;             // 0xCC8B_000C
}SCRG_CTRL_ME1_REG_O24A0_T;
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

#define SCRG_CTRL_ME1_CRG_ME10_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_ME1_CRG_ME11_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_ME1_CRG_ME12_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_ME1_CRG_ME13_O24A0_T_OFF                  (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC8B_0000    crg_me10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ME1_CRG_ME10_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8B_0004    crg_me11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ME1_CRG_ME11_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8B_0008    crg_me12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_ME1_CRG_ME12_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8B_000C    crg_me13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_me0_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_me1_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_me1_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_me1_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_ME1_CRG_ME13_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME1_CRG_ME10_O24A0_T     crg_me10   ;             // 0xCC8B_0000
    SCRG_CTRL_ME1_CRG_ME11_O24A0_T     crg_me11   ;             // 0xCC8B_0004
    SCRG_CTRL_ME1_CRG_ME12_O24A0_T     crg_me12   ;             // 0xCC8B_0008
    SCRG_CTRL_ME1_CRG_ME13_O24A0_T     crg_me13   ;             // 0xCC8B_000C
}SCRG_CTRL_ME1_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_ME1_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

