#ifndef _SCRG_CTRL_TCON_REG_H_
#define _SCRG_CTRL_TCON_REG_H_

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
    0x14_0000    crg_tcon00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_TCON_CRG_TCON00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x14_0004    crg_tcon01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_TCON_CRG_TCON01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x14_0008    crg_tcon02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_op_clk_gate_en        :  1,    //      1
    reg_pix2_clk_gate_en      :  1,    //      2
    reg_pix_clk_gate_en       :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_TCON_CRG_TCON02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x14_000C    crg_tcon03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_apb_rst_n        :  1,    //      0
    reg_soft_op_rst_n         :  1,    //      1
    reg_soft_pix2_rst_n       :  1,    //      2
    reg_soft_pix_rst_n        :  1,    //      3
    reg_soft_rst_f_cco_4_rst_bnd_n: 1,    //   4
    reg_soft_rst_f_led_2_rst_bnd_n: 1,    //   5
    reg_soft_rst_h_cco_8_rst_bnd_n: 1,    //   6
    reg_soft_rst_h_led_0_rst_bnd_n: 1,    //   7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_TCON_CRG_TCON03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x14_0010    crg_tcon04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_op_clk_sel            :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_pix2_clk_sel          :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}SCRG_CTRL_TCON_CRG_TCON04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x14_0014    crg_tcon05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_TCON_CRG_TCON05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TCON_CRG_TCON00_O22A0_T        crg_tcon00 ;             // 0x14_0000
    SCRG_CTRL_TCON_CRG_TCON01_O22A0_T        crg_tcon01 ;             // 0x14_0004
    SCRG_CTRL_TCON_CRG_TCON02_O22A0_T        crg_tcon02 ;             // 0x14_0008
    SCRG_CTRL_TCON_CRG_TCON03_O22A0_T        crg_tcon03 ;             // 0x14_000C
    SCRG_CTRL_TCON_CRG_TCON04_O22A0_T        crg_tcon04 ;             // 0x14_0010
    SCRG_CTRL_TCON_CRG_TCON05_O22A0_T        crg_tcon05 ;             // 0x14_0014
}SCRG_CTRL_TCON_REG_O22A0_T;
/* 6 regs */

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

#define SCRG_CTRL_TCON_CRG_TCON00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define SCRG_CTRL_TCON_CRG_TCON01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define SCRG_CTRL_TCON_CRG_TCON02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define SCRG_CTRL_TCON_CRG_TCON03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define SCRG_CTRL_TCON_CRG_TCON04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define SCRG_CTRL_TCON_CRG_TCON05_O22A0_T_OFF                     (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0x14_0000    crg_tcon00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_TCON_CRG_TCON00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x14_0004    crg_tcon01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_TCON_CRG_TCON01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x14_0008    crg_tcon02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_op_clk_gate_en :  1;    //      1
    UINT32 reg_pix2_clk_gate_en: 1;    //      2
    UINT32 reg_pix_clk_gate_en:  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x14_000C    crg_tcon03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_apb_rst_n :  1;    //      0
    UINT32 reg_soft_op_rst_n  :  1;    //      1
    UINT32 reg_soft_pix2_rst_n:  1;    //      2
    UINT32 reg_soft_pix_rst_n :  1;    //      3
    UINT32 reg_soft_rst_f_cco_4_rst_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_led_2_rst_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_cco_8_rst_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_led_0_rst_bnd_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x14_0010    crg_tcon04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_op_clk_sel     :  2;    //   1: 0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_pix2_clk_sel   :  2;    //   5: 4
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x14_0014    crg_tcon05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_TCON_CRG_TCON05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TCON_CRG_TCON00_O22A0_T        crg_tcon00 ;             // 0x14_0000
    SCRG_CTRL_TCON_CRG_TCON01_O22A0_T        crg_tcon01 ;             // 0x14_0004
    SCRG_CTRL_TCON_CRG_TCON02_O22A0_T        crg_tcon02 ;             // 0x14_0008
    SCRG_CTRL_TCON_CRG_TCON03_O22A0_T        crg_tcon03 ;             // 0x14_000C
    SCRG_CTRL_TCON_CRG_TCON04_O22A0_T        crg_tcon04 ;             // 0x14_0010
    SCRG_CTRL_TCON_CRG_TCON05_O22A0_T        crg_tcon05 ;             // 0x14_0014
}SCRG_CTRL_TCON_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

