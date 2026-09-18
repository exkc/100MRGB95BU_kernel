#ifndef _SCRG_CTRL_ME1_REG_O26A0_H_
#define _SCRG_CTRL_ME1_REG_O26A0_H_

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
    0xCCCE_0000    crg_me1000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ME1_CRG_ME1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCE_0004    crg_me1001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ME1_CRG_ME1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCE_0008    crg_me1002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_f_me0_0__de_clk_gate_en: 1,    //  0
    reg_adaptx_x_me1_0__axi_clk_gate_en: 1,    //  1
    reg_apb_clk_gate_en       :  1,    //      2
    reg_axi_clk_gate_en       :  1,    //      3
    reg_de_clk_gate_en        :  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_ME1_CRG_ME1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCE_000C    crg_me1003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_me0_0_de_bnd_n: 1,    //    3
    reg_soft_rst_p_me1_0_axi_bnd_n: 1,    //   4
    reg_soft_rst_x_me1_0_axi_n:  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_ME1_CRG_ME1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME1_CRG_ME1000_O26A0_T    crg_me1000;             // 0xCCCE_0000
    SCRG_CTRL_ME1_CRG_ME1001_O26A0_T    crg_me1001;             // 0xCCCE_0004
    SCRG_CTRL_ME1_CRG_ME1002_O26A0_T    crg_me1002;             // 0xCCCE_0008
    SCRG_CTRL_ME1_CRG_ME1003_O26A0_T    crg_me1003;             // 0xCCCE_000C
}SCRG_CTRL_ME1_REG_O26A0_T;
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

#define SCRG_CTRL_ME1_CRG_ME1000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_ME1_CRG_ME1001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_ME1_CRG_ME1002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_ME1_CRG_ME1003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCCE_0000    crg_me1000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ME1_CRG_ME1000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCE_0004    crg_me1001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ME1_CRG_ME1001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCE_0008    crg_me1002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_f_me0_0__de_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_x_me1_0__axi_clk_gate_en: 1;    //  1
    UINT32 reg_apb_clk_gate_en:  1;    //      2
    UINT32 reg_axi_clk_gate_en:  1;    //      3
    UINT32 reg_de_clk_gate_en :  1;    //      4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_ME1_CRG_ME1002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCE_000C    crg_me1003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_me0_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_me1_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_me1_0_axi_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_ME1_CRG_ME1003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME1_CRG_ME1000_O26A0_T    crg_me1000;             // 0xCCCE_0000
    SCRG_CTRL_ME1_CRG_ME1001_O26A0_T    crg_me1001;             // 0xCCCE_0004
    SCRG_CTRL_ME1_CRG_ME1002_O26A0_T    crg_me1002;             // 0xCCCE_0008
    SCRG_CTRL_ME1_CRG_ME1003_O26A0_T    crg_me1003;             // 0xCCCE_000C
}SCRG_CTRL_ME1_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_ME1_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

