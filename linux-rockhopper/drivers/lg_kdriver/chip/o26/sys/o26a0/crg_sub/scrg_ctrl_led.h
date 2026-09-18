#ifndef _SCRG_CTRL_LED_REG_O26A0_H_
#define _SCRG_CTRL_LED_REG_O26A0_H_

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
    0xCC92_0000    crg_led000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LED_CRG_LED000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0004    crg_led001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LED_CRG_LED001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0008    crg_led002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_f_cco_6__led_pxl_clk_gate_en: 1,    //  0
    reg_adaprx_f_cco_9__led_pxl_clk_gate_en: 1,    //  1
    reg_adaprx_f_tcon_0__vx1_clk_gate_en: 1,    //  2
    reg_adaprx_h_cco_0__de_clk_gate_en: 1,    //  3
    reg_adaptx_f_led_0__led_pxl_clk_gate_en: 1,    //  4
    reg_adaptx_f_led_1__led_pxl_clk_gate_en: 1,    //  5
    reg_adaptx_f_led_2__led_pxl_clk_gate_en: 1,    //  6
    reg_adaptx_f_led_3__vx1_clk_gate_en: 1,    //  7
    reg_apb_clk_gate_en       :  1,    //      8
    reg_de_clk_gate_en        :  1,    //      9
    reg_led_pxl_clk_gate_en   :  1,    //     10
    reg_vx1_clk_gate_en       :  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_LED_CRG_LED002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_000C    crg_led003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_de_n         :  1,    //      1
    reg_soft_rst_f_cco_6_led_pxl_bnd_n: 1,    //  2
    reg_soft_rst_f_cco_9_led_pxl_bnd_n: 1,    //  3
    reg_soft_rst_f_led_0_led_pxl_bnd_n: 1,    //  4
    reg_soft_rst_f_led_1_led_pxl_bnd_n: 1,    //  5
    reg_soft_rst_f_led_2_led_pxl_bnd_n: 1,    //  6
    reg_soft_rst_f_led_3_vx1_bnd_n: 1,    //   7
    reg_soft_rst_f_tcon_0_vx1_bnd_n: 1,    //  8
    reg_soft_rst_h_cco_0_de_bnd_n: 1,    //    9
    reg_soft_rst_led_pxl_n    :  1,    //     10
    reg_soft_rst_vx1_n        :  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_LED_CRG_LED003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0010    crg_led004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_led_pxl_clk_sel       :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}SCRG_CTRL_LED_CRG_LED004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_led Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LED_CRG_LED000_O26A0_T    crg_led000;             // 0xCC92_0000
    SCRG_CTRL_LED_CRG_LED001_O26A0_T    crg_led001;             // 0xCC92_0004
    SCRG_CTRL_LED_CRG_LED002_O26A0_T    crg_led002;             // 0xCC92_0008
    SCRG_CTRL_LED_CRG_LED003_O26A0_T    crg_led003;             // 0xCC92_000C
    SCRG_CTRL_LED_CRG_LED004_O26A0_T    crg_led004;             // 0xCC92_0010
}SCRG_CTRL_LED_REG_O26A0_T;
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

#define SCRG_CTRL_LED_CRG_LED000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_LED_CRG_LED001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_LED_CRG_LED002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_LED_CRG_LED003_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_LED_CRG_LED004_O26A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC92_0000    crg_led000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LED_CRG_LED000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0004    crg_led001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LED_CRG_LED001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0008    crg_led002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_f_cco_6__led_pxl_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_f_cco_9__led_pxl_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_f_tcon_0__vx1_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_h_cco_0__de_clk_gate_en: 1;    //  3
    UINT32 reg_adaptx_f_led_0__led_pxl_clk_gate_en: 1;    //  4
    UINT32 reg_adaptx_f_led_1__led_pxl_clk_gate_en: 1;    //  5
    UINT32 reg_adaptx_f_led_2__led_pxl_clk_gate_en: 1;    //  6
    UINT32 reg_adaptx_f_led_3__vx1_clk_gate_en: 1;    //  7
    UINT32 reg_apb_clk_gate_en:  1;    //      8
    UINT32 reg_de_clk_gate_en :  1;    //      9
    UINT32 reg_led_pxl_clk_gate_en: 1;    //  10
    UINT32 reg_vx1_clk_gate_en:  1;    //     11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_LED_CRG_LED002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_000C    crg_led003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_de_n  :  1;    //      1
    UINT32 reg_soft_rst_f_cco_6_led_pxl_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_f_cco_9_led_pxl_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_f_led_0_led_pxl_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_led_1_led_pxl_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_led_2_led_pxl_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_led_3_vx1_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_tcon_0_vx1_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_cco_0_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_led_pxl_n: 1;    //   10
    UINT32 reg_soft_rst_vx1_n :  1;    //     11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_LED_CRG_LED003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_0010    crg_led004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_led_pxl_clk_sel:  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_LED_CRG_LED004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_led Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LED_CRG_LED000_O26A0_T    crg_led000;             // 0xCC92_0000
    SCRG_CTRL_LED_CRG_LED001_O26A0_T    crg_led001;             // 0xCC92_0004
    SCRG_CTRL_LED_CRG_LED002_O26A0_T    crg_led002;             // 0xCC92_0008
    SCRG_CTRL_LED_CRG_LED003_O26A0_T    crg_led003;             // 0xCC92_000C
    SCRG_CTRL_LED_CRG_LED004_O26A0_T    crg_led004;             // 0xCC92_0010
}SCRG_CTRL_LED_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_LED_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

