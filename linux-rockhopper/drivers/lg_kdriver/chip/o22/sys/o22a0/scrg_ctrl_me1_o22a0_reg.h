#ifndef _SCRG_CTRL_ME1_REG_H_
#define _SCRG_CTRL_ME1_REG_H_

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
    0x45_0000    crg_me100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ME1_CRG_ME100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_0004    crg_me101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ME1_CRG_ME101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_0008    crg_me102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_ME1_CRG_ME102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_000C    crg_me103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_me0_0_de_bnd_n: 1,    //    3
    reg_soft_rst_p_me1_0_axi_bnd_n: 1,    //   4
    reg_soft_rst_x_me1_0_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_me1_0_axi_n:  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_ME1_CRG_ME103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_0010    crg_me104 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ME1_CRG_ME104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_0014    crg_me105 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ME1_CRG_ME105_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_0018    crg_me106 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ME1_CRG_ME106_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME1_CRG_ME100_O22A0_T          crg_me100  ;             // 0x45_0000
    SCRG_CTRL_ME1_CRG_ME101_O22A0_T          crg_me101  ;             // 0x45_0004
    SCRG_CTRL_ME1_CRG_ME102_O22A0_T          crg_me102  ;             // 0x45_0008
    SCRG_CTRL_ME1_CRG_ME103_O22A0_T          crg_me103  ;             // 0x45_000C
    SCRG_CTRL_ME1_CRG_ME104_O22A0_T          crg_me104  ;             // 0x45_0010
    SCRG_CTRL_ME1_CRG_ME105_O22A0_T          crg_me105  ;             // 0x45_0014
    SCRG_CTRL_ME1_CRG_ME106_O22A0_T          crg_me106  ;             // 0x45_0018
}SCRG_CTRL_ME1_REG_O22A0_T;
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

#define SCRG_CTRL_ME1_CRG_ME100_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_ME1_CRG_ME101_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_ME1_CRG_ME102_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_ME1_CRG_ME103_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_ME1_CRG_ME104_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_ME1_CRG_ME105_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_ME1_CRG_ME106_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x45_0000    crg_me100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ME1_CRG_ME100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_0004    crg_me101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ME1_CRG_ME101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_0008    crg_me102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_ME1_CRG_ME102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_000C    crg_me103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_me0_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_me1_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_me1_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_me1_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_ME1_CRG_ME103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_0010    crg_me104 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ME1_CRG_ME104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_0014    crg_me105 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ME1_CRG_ME105_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x45_0018    crg_me106 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ME1_CRG_ME106_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME1_CRG_ME100_O22A0_T          crg_me100  ;             // 0x45_0000
    SCRG_CTRL_ME1_CRG_ME101_O22A0_T          crg_me101  ;             // 0x45_0004
    SCRG_CTRL_ME1_CRG_ME102_O22A0_T          crg_me102  ;             // 0x45_0008
    SCRG_CTRL_ME1_CRG_ME103_O22A0_T          crg_me103  ;             // 0x45_000C
    SCRG_CTRL_ME1_CRG_ME104_O22A0_T          crg_me104  ;             // 0x45_0010
    SCRG_CTRL_ME1_CRG_ME105_O22A0_T          crg_me105  ;             // 0x45_0014
    SCRG_CTRL_ME1_CRG_ME106_O22A0_T          crg_me106  ;             // 0x45_0018
}SCRG_CTRL_ME1_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

