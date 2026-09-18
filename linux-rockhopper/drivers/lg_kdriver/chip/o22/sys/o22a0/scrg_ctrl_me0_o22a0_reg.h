#ifndef _SCRG_CTRL_ME0_REG_H_
#define _SCRG_CTRL_ME0_REG_H_

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
    0x3F_0000    crg_me000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ME0_CRG_ME000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_0004    crg_me001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ME0_CRG_ME001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_0008    crg_me002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_ME0_CRG_ME002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_000C    crg_me003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_me0_0_de_bnd_n: 1,    //    3
    reg_soft_rst_f_me0_1_de_bnd_n: 1,    //    4
    reg_soft_rst_p_me0_0_axi_bnd_n: 1,    //   5
    reg_soft_rst_p_me0_1_axi_bnd_n: 1,    //   6
    reg_soft_rst_x_me0_0_axi_bnd_n: 1,    //   7
    reg_soft_rst_x_me0_0_axi_n:  1,    //      8
    reg_soft_rst_x_me0_1_axi_bnd_n: 1,    //   9
    reg_soft_rst_x_me0_1_axi_n:  1,    //     10
                              : 21;    //  31:11 reserved
}SCRG_CTRL_ME0_CRG_ME003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_0010    crg_me004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ME0_CRG_ME004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_0014    crg_me005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ME0_CRG_ME005_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_0018    crg_me006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ME0_CRG_ME006_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME0_CRG_ME000_O22A0_T          crg_me000  ;             // 0x3F_0000
    SCRG_CTRL_ME0_CRG_ME001_O22A0_T          crg_me001  ;             // 0x3F_0004
    SCRG_CTRL_ME0_CRG_ME002_O22A0_T          crg_me002  ;             // 0x3F_0008
    SCRG_CTRL_ME0_CRG_ME003_O22A0_T          crg_me003  ;             // 0x3F_000C
    SCRG_CTRL_ME0_CRG_ME004_O22A0_T          crg_me004  ;             // 0x3F_0010
    SCRG_CTRL_ME0_CRG_ME005_O22A0_T          crg_me005  ;             // 0x3F_0014
    SCRG_CTRL_ME0_CRG_ME006_O22A0_T          crg_me006  ;             // 0x3F_0018
}SCRG_CTRL_ME0_REG_O22A0_T;
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

#define SCRG_CTRL_ME0_CRG_ME000_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_ME0_CRG_ME001_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_ME0_CRG_ME002_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_ME0_CRG_ME003_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_ME0_CRG_ME004_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_ME0_CRG_ME005_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_ME0_CRG_ME006_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x3F_0000    crg_me000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ME0_CRG_ME000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_0004    crg_me001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ME0_CRG_ME001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_0008    crg_me002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_ME0_CRG_ME002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_000C    crg_me003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_me0_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_f_me0_1_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_me0_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_me0_1_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_me0_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_me0_0_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_me0_1_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_me0_1_axi_n: 1;    //  10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_ME0_CRG_ME003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_0010    crg_me004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ME0_CRG_ME004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_0014    crg_me005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ME0_CRG_ME005_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3F_0018    crg_me006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ME0_CRG_ME006_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME0_CRG_ME000_O22A0_T          crg_me000  ;             // 0x3F_0000
    SCRG_CTRL_ME0_CRG_ME001_O22A0_T          crg_me001  ;             // 0x3F_0004
    SCRG_CTRL_ME0_CRG_ME002_O22A0_T          crg_me002  ;             // 0x3F_0008
    SCRG_CTRL_ME0_CRG_ME003_O22A0_T          crg_me003  ;             // 0x3F_000C
    SCRG_CTRL_ME0_CRG_ME004_O22A0_T          crg_me004  ;             // 0x3F_0010
    SCRG_CTRL_ME0_CRG_ME005_O22A0_T          crg_me005  ;             // 0x3F_0014
    SCRG_CTRL_ME0_CRG_ME006_O22A0_T          crg_me006  ;             // 0x3F_0018
}SCRG_CTRL_ME0_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

