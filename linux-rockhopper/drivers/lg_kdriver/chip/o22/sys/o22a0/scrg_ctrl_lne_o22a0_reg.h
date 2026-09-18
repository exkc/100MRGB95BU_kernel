#ifndef _SCRG_CTRL_LNE_REG_H_
#define _SCRG_CTRL_LNE_REG_H_

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
    0x36_0000    crg_lne00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LNE_CRG_LNE00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_0004    crg_lne01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LNE_CRG_LNE01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_0008    crg_lne02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lne_apb_clk_gate_en   :  1,    //      0
    reg_lne_axi_clk_gate_en   :  1,    //      1
    reg_lne_tle0_clk_gate_en  :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_LNE_CRG_LNE02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_000C    crg_lne03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_lne_apb_n    :  1,    //      0
    reg_soft_rst_lne_axi0_async_n: 1,    //    1
    reg_soft_rst_lne_axi0_n   :  1,    //      2
    reg_soft_rst_lne_axi_bus_n:  1,    //      3
    reg_soft_rst_lne_tle0_async_n: 1,    //    4
    reg_soft_rst_lne_tle0_n   :  1,    //      5
    reg_soft_rst_lne_tle0_sys_n: 1,    //      6
    reg_soft_rst_p_lne_0_axi_bnd_n: 1,    //   7
    reg_soft_rst_x_lne_0_axi_bnd_n: 1,    //   8
    reg_soft_rst_x_lne_0_axi_n:  1,    //      9
                              : 22;    //  31:10 reserved
}SCRG_CTRL_LNE_CRG_LNE03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_0010    crg_lne04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lne_apb_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_LNE_CRG_LNE04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_0014    crg_lne05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lne_axi_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_LNE_CRG_LNE05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_0018    crg_lne06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lne_tle0_clk_skip_ctrl:  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_LNE_CRG_LNE06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_lne Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LNE_CRG_LNE00_O22A0_T          crg_lne00  ;             // 0x36_0000
    SCRG_CTRL_LNE_CRG_LNE01_O22A0_T          crg_lne01  ;             // 0x36_0004
    SCRG_CTRL_LNE_CRG_LNE02_O22A0_T          crg_lne02  ;             // 0x36_0008
    SCRG_CTRL_LNE_CRG_LNE03_O22A0_T          crg_lne03  ;             // 0x36_000C
    SCRG_CTRL_LNE_CRG_LNE04_O22A0_T          crg_lne04  ;             // 0x36_0010
    SCRG_CTRL_LNE_CRG_LNE05_O22A0_T          crg_lne05  ;             // 0x36_0014
    SCRG_CTRL_LNE_CRG_LNE06_O22A0_T          crg_lne06  ;             // 0x36_0018
}SCRG_CTRL_LNE_REG_O22A0_T;
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

#define SCRG_CTRL_LNE_CRG_LNE00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_LNE_CRG_LNE01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_LNE_CRG_LNE02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_LNE_CRG_LNE03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_LNE_CRG_LNE04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_LNE_CRG_LNE05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_LNE_CRG_LNE06_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x36_0000    crg_lne00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LNE_CRG_LNE00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_0004    crg_lne01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LNE_CRG_LNE01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_0008    crg_lne02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lne_apb_clk_gate_en: 1;    //   0
    UINT32 reg_lne_axi_clk_gate_en: 1;    //   1
    UINT32 reg_lne_tle0_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_LNE_CRG_LNE02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_000C    crg_lne03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_lne_apb_n: 1;    //    0
    UINT32 reg_soft_rst_lne_axi0_async_n: 1;    //  1
    UINT32 reg_soft_rst_lne_axi0_n: 1;    //   2
    UINT32 reg_soft_rst_lne_axi_bus_n: 1;    //  3
    UINT32 reg_soft_rst_lne_tle0_async_n: 1;    //  4
    UINT32 reg_soft_rst_lne_tle0_n: 1;    //   5
    UINT32 reg_soft_rst_lne_tle0_sys_n: 1;    //  6
    UINT32 reg_soft_rst_p_lne_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_lne_0_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_x_lne_0_axi_n: 1;    //  9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}SCRG_CTRL_LNE_CRG_LNE03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_0010    crg_lne04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lne_apb_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_LNE_CRG_LNE04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_0014    crg_lne05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lne_axi_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_LNE_CRG_LNE05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x36_0018    crg_lne06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lne_tle0_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_LNE_CRG_LNE06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_lne Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LNE_CRG_LNE00_O22A0_T          crg_lne00  ;             // 0x36_0000
    SCRG_CTRL_LNE_CRG_LNE01_O22A0_T          crg_lne01  ;             // 0x36_0004
    SCRG_CTRL_LNE_CRG_LNE02_O22A0_T          crg_lne02  ;             // 0x36_0008
    SCRG_CTRL_LNE_CRG_LNE03_O22A0_T          crg_lne03  ;             // 0x36_000C
    SCRG_CTRL_LNE_CRG_LNE04_O22A0_T          crg_lne04  ;             // 0x36_0010
    SCRG_CTRL_LNE_CRG_LNE05_O22A0_T          crg_lne05  ;             // 0x36_0014
    SCRG_CTRL_LNE_CRG_LNE06_O22A0_T          crg_lne06  ;             // 0x36_0018
}SCRG_CTRL_LNE_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

