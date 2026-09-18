#ifndef _SCRG_CTRL_ME0_REG_O26A0_H_
#define _SCRG_CTRL_ME0_REG_O26A0_H_

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
    0xCCCB_0000    crg_me0000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ME0_CRG_ME0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_0004    crg_me0001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ME0_CRG_ME0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_0008    crg_me0002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_f_me0_0__de_clk_gate_en: 1,    //  0
    reg_adaptx_x_me0_0__axi_clk_gate_en: 1,    //  1
    reg_adaptx_x_me0_1__axi_clk_gate_en: 1,    //  2
    reg_apb_clk_gate_en       :  1,    //      3
    reg_axi_clk_gate_en       :  1,    //      4
    reg_de_clk_gate_en        :  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_ME0_CRG_ME0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_000C    crg_me0003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_me0_0_de_bnd_n: 1,    //    3
    reg_soft_rst_p_me0_0_axi_bnd_n: 1,    //   4
    reg_soft_rst_p_me0_1_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_me0_0_axi_n:  1,    //      6
    reg_soft_rst_x_me0_1_axi_n:  1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_ME0_CRG_ME0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME0_CRG_ME0000_O26A0_T    crg_me0000;             // 0xCCCB_0000
    SCRG_CTRL_ME0_CRG_ME0001_O26A0_T    crg_me0001;             // 0xCCCB_0004
    SCRG_CTRL_ME0_CRG_ME0002_O26A0_T    crg_me0002;             // 0xCCCB_0008
    SCRG_CTRL_ME0_CRG_ME0003_O26A0_T    crg_me0003;             // 0xCCCB_000C
}SCRG_CTRL_ME0_REG_O26A0_T;
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

#define SCRG_CTRL_ME0_CRG_ME0000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_ME0_CRG_ME0001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_ME0_CRG_ME0002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_ME0_CRG_ME0003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCCB_0000    crg_me0000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ME0_CRG_ME0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_0004    crg_me0001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ME0_CRG_ME0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_0008    crg_me0002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_f_me0_0__de_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_x_me0_0__axi_clk_gate_en: 1;    //  1
    UINT32 reg_adaptx_x_me0_1__axi_clk_gate_en: 1;    //  2
    UINT32 reg_apb_clk_gate_en:  1;    //      3
    UINT32 reg_axi_clk_gate_en:  1;    //      4
    UINT32 reg_de_clk_gate_en :  1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_ME0_CRG_ME0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCB_000C    crg_me0003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_me0_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_me0_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_me0_1_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_me0_0_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_me0_1_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_ME0_CRG_ME0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME0_CRG_ME0000_O26A0_T    crg_me0000;             // 0xCCCB_0000
    SCRG_CTRL_ME0_CRG_ME0001_O26A0_T    crg_me0001;             // 0xCCCB_0004
    SCRG_CTRL_ME0_CRG_ME0002_O26A0_T    crg_me0002;             // 0xCCCB_0008
    SCRG_CTRL_ME0_CRG_ME0003_O26A0_T    crg_me0003;             // 0xCCCB_000C
}SCRG_CTRL_ME0_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_ME0_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

