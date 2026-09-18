#ifndef _SCRG_CTRL_DNE_REG_H_
#define _SCRG_CTRL_DNE_REG_H_

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
    0xF_0000    crg_dne00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DNE_CRG_DNE00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_0004    crg_dne01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DNE_CRG_DNE01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_0008    crg_dne02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_dne_clk_gate_en   :  1,    //      0
    reg_axi_dne_clk_gate_en   :  1,    //      1
    reg_dne_clk_gate_en       :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_DNE_CRG_DNE02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_000C    crg_dne03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_dne_n    :  1,    //      0
    reg_soft_rst_axi_dne_n    :  1,    //      1
    reg_soft_rst_dne_n        :  1,    //      2
    reg_soft_rst_p_dne_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_p_dne_1_axi_bnd_n: 1,    //   4
    reg_soft_rst_x_dne_0_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_dne_0_axi_n:  1,    //      6
    reg_soft_rst_x_dne_1_axi_bnd_n: 1,    //   7
    reg_soft_rst_x_dne_1_axi_n:  1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNE_CRG_DNE03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_0010    crg_dne04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_dne_clk_sel       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_axi_dne_clk_sel       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_dne_clk_sel           :  1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNE_CRG_DNE04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_0014    crg_dne05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_dne_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNE_CRG_DNE05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_0018    crg_dne06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_dne_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNE_CRG_DNE06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_001C    crg_dne07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dne_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNE_CRG_DNE07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_dne Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DNE_CRG_DNE00_O22A0_T          crg_dne00  ;             // 0xF_0000
    SCRG_CTRL_DNE_CRG_DNE01_O22A0_T          crg_dne01  ;             // 0xF_0004
    SCRG_CTRL_DNE_CRG_DNE02_O22A0_T          crg_dne02  ;             // 0xF_0008
    SCRG_CTRL_DNE_CRG_DNE03_O22A0_T          crg_dne03  ;             // 0xF_000C
    SCRG_CTRL_DNE_CRG_DNE04_O22A0_T          crg_dne04  ;             // 0xF_0010
    SCRG_CTRL_DNE_CRG_DNE05_O22A0_T          crg_dne05  ;             // 0xF_0014
    SCRG_CTRL_DNE_CRG_DNE06_O22A0_T          crg_dne06  ;             // 0xF_0018
    SCRG_CTRL_DNE_CRG_DNE07_O22A0_T          crg_dne07  ;             // 0xF_001C
}SCRG_CTRL_DNE_REG_O22A0_T;
/* 8 regs */

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

#define SCRG_CTRL_DNE_CRG_DNE00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_DNE_CRG_DNE01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_DNE_CRG_DNE02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_DNE_CRG_DNE03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_DNE_CRG_DNE04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_DNE_CRG_DNE05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_DNE_CRG_DNE06_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_DNE_CRG_DNE07_O22A0_T_OFF                       (BASEADDRESS+0x001C)

/*-----------------------------------------------------------------------------------------
    0xF_0000    crg_dne00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DNE_CRG_DNE00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_0004    crg_dne01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DNE_CRG_DNE01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_0008    crg_dne02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_dne_clk_gate_en: 1;    //   0
    UINT32 reg_axi_dne_clk_gate_en: 1;    //   1
    UINT32 reg_dne_clk_gate_en:  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_DNE_CRG_DNE02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_000C    crg_dne03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_dne_n: 1;    //    0
    UINT32 reg_soft_rst_axi_dne_n: 1;    //    1
    UINT32 reg_soft_rst_dne_n :  1;    //      2
    UINT32 reg_soft_rst_p_dne_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_dne_1_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_dne_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_dne_0_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_dne_1_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_dne_1_axi_n: 1;    //  8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNE_CRG_DNE03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_0010    crg_dne04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_dne_clk_sel:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_axi_dne_clk_sel:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_dne_clk_sel    :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNE_CRG_DNE04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_0014    crg_dne05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_dne_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNE_CRG_DNE05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_0018    crg_dne06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_dne_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNE_CRG_DNE06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF_001C    crg_dne07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dne_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNE_CRG_DNE07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_dne Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DNE_CRG_DNE00_O22A0_T          crg_dne00  ;             // 0xF_0000
    SCRG_CTRL_DNE_CRG_DNE01_O22A0_T          crg_dne01  ;             // 0xF_0004
    SCRG_CTRL_DNE_CRG_DNE02_O22A0_T          crg_dne02  ;             // 0xF_0008
    SCRG_CTRL_DNE_CRG_DNE03_O22A0_T          crg_dne03  ;             // 0xF_000C
    SCRG_CTRL_DNE_CRG_DNE04_O22A0_T          crg_dne04  ;             // 0xF_0010
    SCRG_CTRL_DNE_CRG_DNE05_O22A0_T          crg_dne05  ;             // 0xF_0014
    SCRG_CTRL_DNE_CRG_DNE06_O22A0_T          crg_dne06  ;             // 0xF_0018
    SCRG_CTRL_DNE_CRG_DNE07_O22A0_T          crg_dne07  ;             // 0xF_001C
}SCRG_CTRL_DNE_REG_O22A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

