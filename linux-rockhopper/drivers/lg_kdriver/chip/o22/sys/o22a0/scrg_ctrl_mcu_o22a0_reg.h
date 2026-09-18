#ifndef _SCRG_CTRL_MCU_REG_H_
#define _SCRG_CTRL_MCU_REG_H_

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
    0x30_0000    crg_mcu00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_MCU_CRG_MCU00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_0004    crg_mcu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_MCU_CRG_MCU01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_0008    crg_mcu02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_mcu_clk_gate_en       :  1,    //      1
    reg_teclk_gate_en         :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_MCU_CRG_MCU02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_000C    crg_mcu03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_e_te_6_te_bnd_n: 1,    //     1
    reg_soft_rst_e_te_7_te_bnd_n: 1,    //     2
    reg_soft_rst_f_te_0_mcu_bnd_n: 1,    //    3
    reg_soft_rst_f_te_1_mcu_bnd_n: 1,    //    4
    reg_soft_rst_f_te_2_mcu_bnd_n: 1,    //    5
    reg_soft_rst_f_te_3_mcu_bnd_n: 1,    //    6
    reg_soft_rst_mcu_n        :  1,    //      7
    reg_soft_rst_p_mcu_0_axi_bnd_n: 1,    //   8
    reg_soft_rst_te_n         :  1,    //      9
    reg_soft_rst_x_mcu_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_x_mcu_0_axi_n:  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_MCU_CRG_MCU03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_0010    crg_mcu04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_MCU_CRG_MCU04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_0014    crg_mcu05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mcu_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_MCU_CRG_MCU05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_0018    crg_mcu06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_teclk_skip_ctrl       :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_MCU_CRG_MCU06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_mcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_MCU_CRG_MCU00_O22A0_T          crg_mcu00  ;             // 0x30_0000
    SCRG_CTRL_MCU_CRG_MCU01_O22A0_T          crg_mcu01  ;             // 0x30_0004
    SCRG_CTRL_MCU_CRG_MCU02_O22A0_T          crg_mcu02  ;             // 0x30_0008
    SCRG_CTRL_MCU_CRG_MCU03_O22A0_T          crg_mcu03  ;             // 0x30_000C
    SCRG_CTRL_MCU_CRG_MCU04_O22A0_T          crg_mcu04  ;             // 0x30_0010
    SCRG_CTRL_MCU_CRG_MCU05_O22A0_T          crg_mcu05  ;             // 0x30_0014
    SCRG_CTRL_MCU_CRG_MCU06_O22A0_T          crg_mcu06  ;             // 0x30_0018
}SCRG_CTRL_MCU_REG_O22A0_T;
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

#define SCRG_CTRL_MCU_CRG_MCU00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_MCU_CRG_MCU01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_MCU_CRG_MCU02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_MCU_CRG_MCU03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_MCU_CRG_MCU04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_MCU_CRG_MCU05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_MCU_CRG_MCU06_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x30_0000    crg_mcu00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_MCU_CRG_MCU00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_0004    crg_mcu01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_MCU_CRG_MCU01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_0008    crg_mcu02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_mcu_clk_gate_en:  1;    //      1
    UINT32 reg_teclk_gate_en  :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_MCU_CRG_MCU02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_000C    crg_mcu03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_e_te_6_te_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_e_te_7_te_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_f_te_0_mcu_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_f_te_1_mcu_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_te_2_mcu_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_te_3_mcu_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_mcu_n :  1;    //      7
    UINT32 reg_soft_rst_p_mcu_0_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_te_n  :  1;    //      9
    UINT32 reg_soft_rst_x_mcu_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_x_mcu_0_axi_n: 1;    //  11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_MCU_CRG_MCU03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_0010    crg_mcu04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_MCU_CRG_MCU04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_0014    crg_mcu05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_mcu_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_MCU_CRG_MCU05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x30_0018    crg_mcu06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_teclk_skip_ctrl:  9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_MCU_CRG_MCU06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_mcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_MCU_CRG_MCU00_O22A0_T          crg_mcu00  ;             // 0x30_0000
    SCRG_CTRL_MCU_CRG_MCU01_O22A0_T          crg_mcu01  ;             // 0x30_0004
    SCRG_CTRL_MCU_CRG_MCU02_O22A0_T          crg_mcu02  ;             // 0x30_0008
    SCRG_CTRL_MCU_CRG_MCU03_O22A0_T          crg_mcu03  ;             // 0x30_000C
    SCRG_CTRL_MCU_CRG_MCU04_O22A0_T          crg_mcu04  ;             // 0x30_0010
    SCRG_CTRL_MCU_CRG_MCU05_O22A0_T          crg_mcu05  ;             // 0x30_0014
    SCRG_CTRL_MCU_CRG_MCU06_O22A0_T          crg_mcu06  ;             // 0x30_0018
}SCRG_CTRL_MCU_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

