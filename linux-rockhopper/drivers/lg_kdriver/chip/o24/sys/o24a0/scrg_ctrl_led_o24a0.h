#ifndef _SCRG_CTRL_LED_REG_O24A0_H_
#define _SCRG_CTRL_LED_REG_O24A0_H_

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
    0xCC90_0000    crg_led0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LED_CRG_LED0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC90_0004    crg_led1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LED_CRG_LED1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC90_0008    crg_led2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_de_clk_gate_en        :  1,    //      1
    reg_led_pxl_clk_gate_en   :  1,    //      2
    reg_vx1_clk_gate_en       :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_LED_CRG_LED2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC90_000C    crg_led3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_de_n         :  1,    //      1
    reg_soft_rst_f_cco_10_led_pxl_bnd_n: 1,    //  2
    reg_soft_rst_f_cco_6_led_pxl_bnd_n: 1,    //  3
    reg_soft_rst_f_led_0_vx1_bnd_n: 1,    //   4
    reg_soft_rst_f_led_1_led_pxl_bnd_n: 1,    //  5
    reg_soft_rst_f_led_2_led_pxl_bnd_n: 1,    //  6
    reg_soft_rst_f_led_3_led_pxl_bnd_n: 1,    //  7
    reg_soft_rst_f_tcon_0_vx1_bnd_n: 1,    //  8
    reg_soft_rst_h_cco_1_de_bnd_n: 1,    //    9
    reg_soft_rst_led_pxl_n    :  1,    //     10
    reg_soft_rst_vx1_n        :  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_LED_CRG_LED3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC90_0010    crg_led4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_led_pxl_clk_sel       :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}SCRG_CTRL_LED_CRG_LED4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_led Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LED_CRG_LED0_O24A0_T     crg_led0   ;             // 0xCC90_0000
    SCRG_CTRL_LED_CRG_LED1_O24A0_T     crg_led1   ;             // 0xCC90_0004
    SCRG_CTRL_LED_CRG_LED2_O24A0_T     crg_led2   ;             // 0xCC90_0008
    SCRG_CTRL_LED_CRG_LED3_O24A0_T     crg_led3   ;             // 0xCC90_000C
    SCRG_CTRL_LED_CRG_LED4_O24A0_T     crg_led4   ;             // 0xCC90_0010
}SCRG_CTRL_LED_REG_O24A0_T;
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

#define SCRG_CTRL_LED_CRG_LED0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_LED_CRG_LED1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_LED_CRG_LED2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_LED_CRG_LED3_O24A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_LED_CRG_LED4_O24A0_T_OFF                  (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC90_0000    crg_led0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LED_CRG_LED0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC90_0004    crg_led1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LED_CRG_LED1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC90_0008    crg_led2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_de_clk_gate_en :  1;    //      1
    UINT32 reg_led_pxl_clk_gate_en: 1;    //   2
    UINT32 reg_vx1_clk_gate_en:  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_LED_CRG_LED2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC90_000C    crg_led3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_de_n  :  1;    //      1
    UINT32 reg_soft_rst_f_cco_10_led_pxl_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_f_cco_6_led_pxl_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_f_led_0_vx1_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_led_1_led_pxl_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_led_2_led_pxl_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_led_3_led_pxl_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_tcon_0_vx1_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_cco_1_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_led_pxl_n: 1;    //   10
    UINT32 reg_soft_rst_vx1_n :  1;    //     11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_LED_CRG_LED3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC90_0010    crg_led4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_led_pxl_clk_sel:  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_LED_CRG_LED4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_led Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LED_CRG_LED0_O24A0_T     crg_led0   ;             // 0xCC90_0000
    SCRG_CTRL_LED_CRG_LED1_O24A0_T     crg_led1   ;             // 0xCC90_0004
    SCRG_CTRL_LED_CRG_LED2_O24A0_T     crg_led2   ;             // 0xCC90_0008
    SCRG_CTRL_LED_CRG_LED3_O24A0_T     crg_led3   ;             // 0xCC90_000C
    SCRG_CTRL_LED_CRG_LED4_O24A0_T     crg_led4   ;             // 0xCC90_0010
}SCRG_CTRL_LED_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_LED_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

