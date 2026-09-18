#ifndef _SCRG_CTRL_LED_M23A0_REG_H_
#define _SCRG_CTRL_LED_M23A0_REG_H_

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
    0xCC44_0000    crg_led00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LED_CRG_LED00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_0004    crg_led01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LED_CRG_LED01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_0008    crg_led02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_led_apb_clk_gate_en   :  1,    //      0
    reg_led_pxl_clk_gate_en   :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_LED_CRG_LED02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_000C    crg_led03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_f_cco_0_led_pxl_bnd_n: 1,    //  1
    reg_soft_rst_f_led_0_led_pxl_bnd_n: 1,    //  2
    reg_soft_rst_f_led_1_led_pxl_bnd_n: 1,    //  3
    reg_soft_rst_led_pxl_n    :  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_LED_CRG_LED03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_0010    crg_led04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_led_pxl_clk_sel       :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}SCRG_CTRL_LED_CRG_LED04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_led Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LED_CRG_LED00_M23A0_T    crg_led00  ;             // 0xCC44_0000
    SCRG_CTRL_LED_CRG_LED01_M23A0_T    crg_led01  ;             // 0xCC44_0004
    SCRG_CTRL_LED_CRG_LED02_M23A0_T    crg_led02  ;             // 0xCC44_0008
    SCRG_CTRL_LED_CRG_LED03_M23A0_T    crg_led03  ;             // 0xCC44_000C
    SCRG_CTRL_LED_CRG_LED04_M23A0_T    crg_led04  ;             // 0xCC44_0010
}SCRG_CTRL_LED_REG_M23A0_T;
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

#define SCRG_CTRL_LED_CRG_LED00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_LED_CRG_LED01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_LED_CRG_LED02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_LED_CRG_LED03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define SCRG_CTRL_LED_CRG_LED04_M23A0_T_OFF                 (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC44_0000    crg_led00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LED_CRG_LED00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_0004    crg_led01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LED_CRG_LED01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_0008    crg_led02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_led_apb_clk_gate_en: 1;    //   0
    UINT32 reg_led_pxl_clk_gate_en: 1;    //   1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_LED_CRG_LED02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_000C    crg_led03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_f_cco_0_led_pxl_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_f_led_0_led_pxl_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_f_led_1_led_pxl_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_led_pxl_n: 1;    //    4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_LED_CRG_LED03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC44_0010    crg_led04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_led_pxl_clk_sel:  2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_LED_CRG_LED04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_led Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LED_CRG_LED00_M23A0_T    crg_led00  ;             // 0xCC44_0000
    SCRG_CTRL_LED_CRG_LED01_M23A0_T    crg_led01  ;             // 0xCC44_0004
    SCRG_CTRL_LED_CRG_LED02_M23A0_T    crg_led02  ;             // 0xCC44_0008
    SCRG_CTRL_LED_CRG_LED03_M23A0_T    crg_led03  ;             // 0xCC44_000C
    SCRG_CTRL_LED_CRG_LED04_M23A0_T    crg_led04  ;             // 0xCC44_0010
}SCRG_CTRL_LED_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

