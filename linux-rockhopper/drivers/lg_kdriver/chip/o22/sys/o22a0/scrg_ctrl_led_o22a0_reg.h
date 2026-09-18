#ifndef _SCRG_CTRL_LED_REG_H_
#define _SCRG_CTRL_LED_REG_H_

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
    0x13_0000    crg_led00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LED_CRG_LED00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_0004    crg_led01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LED_CRG_LED01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_0008    crg_led02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_de_clk_gate_en        :  1,    //      1
    reg_led_pxl_clk_gate_en   :  1,    //      2
    reg_led_smm_clk_gate_en   :  1,    //      3
    reg_vx1_clk_gate_en       :  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_LED_CRG_LED02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_000C    crg_led03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_de_n         :  1,    //      1
    reg_soft_rst_f_cco_7_led_pxl_bnd_n: 1,    //  2
    reg_soft_rst_f_led_1_led_pxl_bnd_n: 1,    //  3
    reg_soft_rst_f_led_2_led_pxl_bnd_n: 1,    //  4
    reg_soft_rst_h_cco_0_de_bnd_n: 1,    //    5
    reg_soft_rst_h_led_0_vx1_bnd_n: 1,    //   6
    reg_soft_rst_led_pxl_n    :  1,    //      7
    reg_soft_rst_led_smm_n    :  1,    //      8
    reg_soft_rst_vx1_n        :  1,    //      9
                              : 22;    //  31:10 reserved
}SCRG_CTRL_LED_CRG_LED03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_0010    crg_led04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_led_pxl_clk_sel       :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_led_smm_clk_sel       :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}SCRG_CTRL_LED_CRG_LED04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_0014    crg_led05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_LED_CRG_LED05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_0018    crg_led06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_LED_CRG_LED06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_led Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LED_CRG_LED00_O22A0_T          crg_led00  ;             // 0x13_0000
    SCRG_CTRL_LED_CRG_LED01_O22A0_T          crg_led01  ;             // 0x13_0004
    SCRG_CTRL_LED_CRG_LED02_O22A0_T          crg_led02  ;             // 0x13_0008
    SCRG_CTRL_LED_CRG_LED03_O22A0_T          crg_led03  ;             // 0x13_000C
    SCRG_CTRL_LED_CRG_LED04_O22A0_T          crg_led04  ;             // 0x13_0010
    SCRG_CTRL_LED_CRG_LED05_O22A0_T          crg_led05  ;             // 0x13_0014
    SCRG_CTRL_LED_CRG_LED06_O22A0_T          crg_led06  ;             // 0x13_0018
}SCRG_CTRL_LED_REG_O22A0_T;
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

#define SCRG_CTRL_LED_CRG_LED00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_LED_CRG_LED01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_LED_CRG_LED02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_LED_CRG_LED03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_LED_CRG_LED04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_LED_CRG_LED05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_LED_CRG_LED06_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x13_0000    crg_led00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LED_CRG_LED00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_0004    crg_led01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LED_CRG_LED01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_0008    crg_led02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_de_clk_gate_en :  1;    //      1
    UINT32 reg_led_pxl_clk_gate_en: 1;    //   2
    UINT32 reg_led_smm_clk_gate_en: 1;    //   3
    UINT32 reg_vx1_clk_gate_en:  1;    //      4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_LED_CRG_LED02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_000C    crg_led03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_de_n  :  1;    //      1
    UINT32 reg_soft_rst_f_cco_7_led_pxl_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_f_led_1_led_pxl_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_f_led_2_led_pxl_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_cco_0_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_led_0_vx1_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_led_pxl_n: 1;    //    7
    UINT32 reg_soft_rst_led_smm_n: 1;    //    8
    UINT32 reg_soft_rst_vx1_n :  1;    //      9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}SCRG_CTRL_LED_CRG_LED03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_0010    crg_led04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_led_pxl_clk_sel:  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_led_smm_clk_sel:  3;    //   6: 4
    UINT32 resvd01            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_LED_CRG_LED04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_0014    crg_led05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_LED_CRG_LED05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x13_0018    crg_led06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_LED_CRG_LED06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_led Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LED_CRG_LED00_O22A0_T          crg_led00  ;             // 0x13_0000
    SCRG_CTRL_LED_CRG_LED01_O22A0_T          crg_led01  ;             // 0x13_0004
    SCRG_CTRL_LED_CRG_LED02_O22A0_T          crg_led02  ;             // 0x13_0008
    SCRG_CTRL_LED_CRG_LED03_O22A0_T          crg_led03  ;             // 0x13_000C
    SCRG_CTRL_LED_CRG_LED04_O22A0_T          crg_led04  ;             // 0x13_0010
    SCRG_CTRL_LED_CRG_LED05_O22A0_T          crg_led05  ;             // 0x13_0014
    SCRG_CTRL_LED_CRG_LED06_O22A0_T          crg_led06  ;             // 0x13_0018
}SCRG_CTRL_LED_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

