#ifndef _SCRG_CTRL_ME0_REG_O24A0_H_
#define _SCRG_CTRL_ME0_REG_O24A0_H_

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
    0xCC4B_0000    crg_me00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ME0_CRG_ME00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4B_0004    crg_me01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ME0_CRG_ME01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4B_0008    crg_me02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_ME0_CRG_ME02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4B_000C    crg_me03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_me0_0_de_bnd_n: 1,    //    3
    reg_soft_rst_p_me0_0_axi_bnd_n: 1,    //   4
    reg_soft_rst_p_me0_1_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_me0_0_axi_bnd_n: 1,    //   6
    reg_soft_rst_x_me0_0_axi_n:  1,    //      7
    reg_soft_rst_x_me0_1_axi_bnd_n: 1,    //   8
    reg_soft_rst_x_me0_1_axi_n:  1,    //      9
                              : 22;    //  31:10 reserved
}SCRG_CTRL_ME0_CRG_ME03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME0_CRG_ME00_O24A0_T     crg_me00   ;             // 0xCC4B_0000
    SCRG_CTRL_ME0_CRG_ME01_O24A0_T     crg_me01   ;             // 0xCC4B_0004
    SCRG_CTRL_ME0_CRG_ME02_O24A0_T     crg_me02   ;             // 0xCC4B_0008
    SCRG_CTRL_ME0_CRG_ME03_O24A0_T     crg_me03   ;             // 0xCC4B_000C
}SCRG_CTRL_ME0_REG_O24A0_T;
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

#define SCRG_CTRL_ME0_CRG_ME00_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_ME0_CRG_ME01_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_ME0_CRG_ME02_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_ME0_CRG_ME03_O24A0_T_OFF                  (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC4B_0000    crg_me00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ME0_CRG_ME00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4B_0004    crg_me01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ME0_CRG_ME01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4B_0008    crg_me02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_ME0_CRG_ME02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4B_000C    crg_me03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_me0_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_me0_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_me0_1_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_me0_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_me0_0_axi_n: 1;    //  7
    UINT32 reg_soft_rst_x_me0_1_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_x_me0_1_axi_n: 1;    //  9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}SCRG_CTRL_ME0_CRG_ME03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME0_CRG_ME00_O24A0_T     crg_me00   ;             // 0xCC4B_0000
    SCRG_CTRL_ME0_CRG_ME01_O24A0_T     crg_me01   ;             // 0xCC4B_0004
    SCRG_CTRL_ME0_CRG_ME02_O24A0_T     crg_me02   ;             // 0xCC4B_0008
    SCRG_CTRL_ME0_CRG_ME03_O24A0_T     crg_me03   ;             // 0xCC4B_000C
}SCRG_CTRL_ME0_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_ME0_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

