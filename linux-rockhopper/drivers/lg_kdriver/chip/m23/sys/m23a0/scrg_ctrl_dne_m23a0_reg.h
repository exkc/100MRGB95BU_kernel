#ifndef _SCRG_CTRL_DNE_M23A0_REG_H_
#define _SCRG_CTRL_DNE_M23A0_REG_H_

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
    0xCC78_0000    crg_dne00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DNE_CRG_DNE00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC78_0004    crg_dne01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DNE_CRG_DNE01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC78_0008    crg_dne02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_dne_clk_gate_en   :  1,    //      0
    reg_axi_dne_clk_gate_en   :  1,    //      1
    reg_dne_clk_gate_en       :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_DNE_CRG_DNE02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC78_000C    crg_dne03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_dne_n    :  1,    //      0
    reg_soft_rst_axi_dne_n    :  1,    //      1
    reg_soft_rst_dne_n        :  1,    //      2
    reg_soft_rst_p_dne_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_x_dne_0_axi_bnd_n: 1,    //   4
    reg_soft_rst_x_dne_0_axi_n:  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_DNE_CRG_DNE03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC78_0010    crg_dne04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_dne_clk_sel       :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_axi_dne_clk_sel       :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_dne_clk_sel           :  3,    //  10: 8
                              : 21;    //  31:11 reserved
}SCRG_CTRL_DNE_CRG_DNE04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dne Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DNE_CRG_DNE00_M23A0_T    crg_dne00  ;             // 0xCC78_0000
    SCRG_CTRL_DNE_CRG_DNE01_M23A0_T    crg_dne01  ;             // 0xCC78_0004
    SCRG_CTRL_DNE_CRG_DNE02_M23A0_T    crg_dne02  ;             // 0xCC78_0008
    SCRG_CTRL_DNE_CRG_DNE03_M23A0_T    crg_dne03  ;             // 0xCC78_000C
    SCRG_CTRL_DNE_CRG_DNE04_M23A0_T    crg_dne04  ;             // 0xCC78_0010
}SCRG_CTRL_DNE_REG_M23A0_T;
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

#define SCRG_CTRL_DNE_CRG_DNE00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_DNE_CRG_DNE01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_DNE_CRG_DNE02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_DNE_CRG_DNE03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define SCRG_CTRL_DNE_CRG_DNE04_M23A0_T_OFF                 (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC78_0000    crg_dne00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DNE_CRG_DNE00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC78_0004    crg_dne01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DNE_CRG_DNE01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC78_0008    crg_dne02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_dne_clk_gate_en: 1;    //   0
    UINT32 reg_axi_dne_clk_gate_en: 1;    //   1
    UINT32 reg_dne_clk_gate_en:  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_DNE_CRG_DNE02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC78_000C    crg_dne03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_dne_n: 1;    //    0
    UINT32 reg_soft_rst_axi_dne_n: 1;    //    1
    UINT32 reg_soft_rst_dne_n :  1;    //      2
    UINT32 reg_soft_rst_p_dne_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_dne_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_dne_0_axi_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_DNE_CRG_DNE03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC78_0010    crg_dne04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_dne_clk_sel:  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_axi_dne_clk_sel:  3;    //   6: 4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_dne_clk_sel    :  3;    //  10: 8
    UINT32 resvd02            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_DNE_CRG_DNE04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dne Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DNE_CRG_DNE00_M23A0_T    crg_dne00  ;             // 0xCC78_0000
    SCRG_CTRL_DNE_CRG_DNE01_M23A0_T    crg_dne01  ;             // 0xCC78_0004
    SCRG_CTRL_DNE_CRG_DNE02_M23A0_T    crg_dne02  ;             // 0xCC78_0008
    SCRG_CTRL_DNE_CRG_DNE03_M23A0_T    crg_dne03  ;             // 0xCC78_000C
    SCRG_CTRL_DNE_CRG_DNE04_M23A0_T    crg_dne04  ;             // 0xCC78_0010
}SCRG_CTRL_DNE_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

