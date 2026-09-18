#ifndef _SCRG_CTRL_FMS_REG_H_
#define _SCRG_CTRL_FMS_REG_H_

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
    0x1E_0000    crg_fms00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_FMS_CRG_FMS00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0004    crg_fms01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_FMS_CRG_FMS01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0008    crg_fms02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_fms_clk_gate_en   :  1,    //      0
    reg_axi_fms_clk_gate_en   :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
    reg_fms_clk_gate_en       :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_FMS_CRG_FMS02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_000C    crg_fms03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_fms_n    :  1,    //      0
    reg_soft_rst_axi_fms_n    :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_fms_0_de_bnd_n: 1,    //    3
    reg_soft_rst_fms_n        :  1,    //      4
    reg_soft_rst_p_fms_0_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_fms_0_axi_bnd_n: 1,    //   6
    reg_soft_rst_x_fms_0_axi_n:  1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_FMS_CRG_FMS03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0010    crg_fms04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_sel           :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_axi_clk_sel           :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_fms_clk_sel           :  1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_FMS_CRG_FMS04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0014    crg_fms05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_fms_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_FMS_CRG_FMS05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0018    crg_fms06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_fms_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_FMS_CRG_FMS06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_001C    crg_fms07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_FMS_CRG_FMS07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0020    crg_fms08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fms_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_FMS_CRG_FMS08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMS_CRG_FMS00_O22A0_T          crg_fms00  ;             // 0x1E_0000
    SCRG_CTRL_FMS_CRG_FMS01_O22A0_T          crg_fms01  ;             // 0x1E_0004
    SCRG_CTRL_FMS_CRG_FMS02_O22A0_T          crg_fms02  ;             // 0x1E_0008
    SCRG_CTRL_FMS_CRG_FMS03_O22A0_T          crg_fms03  ;             // 0x1E_000C
    SCRG_CTRL_FMS_CRG_FMS04_O22A0_T          crg_fms04  ;             // 0x1E_0010
    SCRG_CTRL_FMS_CRG_FMS05_O22A0_T          crg_fms05  ;             // 0x1E_0014
    SCRG_CTRL_FMS_CRG_FMS06_O22A0_T          crg_fms06  ;             // 0x1E_0018
    SCRG_CTRL_FMS_CRG_FMS07_O22A0_T          crg_fms07  ;             // 0x1E_001C
    SCRG_CTRL_FMS_CRG_FMS08_O22A0_T          crg_fms08  ;             // 0x1E_0020
}SCRG_CTRL_FMS_REG_O22A0_T;
/* 9 regs */

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

#define SCRG_CTRL_FMS_CRG_FMS00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_FMS_CRG_FMS01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_FMS_CRG_FMS02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_FMS_CRG_FMS03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_FMS_CRG_FMS04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_FMS_CRG_FMS05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_FMS_CRG_FMS06_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_FMS_CRG_FMS07_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define SCRG_CTRL_FMS_CRG_FMS08_O22A0_T_OFF                       (BASEADDRESS+0x0020)

/*-----------------------------------------------------------------------------------------
    0x1E_0000    crg_fms00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_FMS_CRG_FMS00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0004    crg_fms01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_FMS_CRG_FMS01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0008    crg_fms02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_fms_clk_gate_en: 1;    //   0
    UINT32 reg_axi_fms_clk_gate_en: 1;    //   1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 reg_fms_clk_gate_en:  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_000C    crg_fms03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_fms_n: 1;    //    0
    UINT32 reg_soft_rst_axi_fms_n: 1;    //    1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_fms_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_fms_n :  1;    //      4
    UINT32 reg_soft_rst_p_fms_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_fms_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_fms_0_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0010    crg_fms04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_sel    :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_axi_clk_sel    :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_fms_clk_sel    :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0014    crg_fms05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_fms_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0018    crg_fms06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_fms_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_001C    crg_fms07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x1E_0020    crg_fms08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fms_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMS_CRG_FMS00_O22A0_T          crg_fms00  ;             // 0x1E_0000
    SCRG_CTRL_FMS_CRG_FMS01_O22A0_T          crg_fms01  ;             // 0x1E_0004
    SCRG_CTRL_FMS_CRG_FMS02_O22A0_T          crg_fms02  ;             // 0x1E_0008
    SCRG_CTRL_FMS_CRG_FMS03_O22A0_T          crg_fms03  ;             // 0x1E_000C
    SCRG_CTRL_FMS_CRG_FMS04_O22A0_T          crg_fms04  ;             // 0x1E_0010
    SCRG_CTRL_FMS_CRG_FMS05_O22A0_T          crg_fms05  ;             // 0x1E_0014
    SCRG_CTRL_FMS_CRG_FMS06_O22A0_T          crg_fms06  ;             // 0x1E_0018
    SCRG_CTRL_FMS_CRG_FMS07_O22A0_T          crg_fms07  ;             // 0x1E_001C
    SCRG_CTRL_FMS_CRG_FMS08_O22A0_T          crg_fms08  ;             // 0x1E_0020
}SCRG_CTRL_FMS_REG_O22A0_T;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

