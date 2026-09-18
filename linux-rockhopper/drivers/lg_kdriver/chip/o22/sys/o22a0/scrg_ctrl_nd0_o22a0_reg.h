#ifndef _SCRG_CTRL_ND0_REG_H_
#define _SCRG_CTRL_ND0_REG_H_

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
    0x49_0000    crg_nd000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ND0_CRG_ND000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_0004    crg_nd001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ND0_CRG_ND001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_0008    crg_nd002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_ND0_CRG_ND002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_000C    crg_nd003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_h_imx_10_de_bnd_n: 1,    //   3
    reg_soft_rst_h_imx_11_de_bnd_n: 1,    //   4
    reg_soft_rst_h_nd0_0_de_bnd_n: 1,    //    5
    reg_soft_rst_h_nd0_1_de_bnd_n: 1,    //    6
    reg_soft_rst_h_nd0_2_de_bnd_n: 1,    //    7
    reg_soft_rst_h_nd0_3_de_bnd_n: 1,    //    8
    reg_soft_rst_h_nd0_4_de_bnd_n: 1,    //    9
    reg_soft_rst_h_nd0_5_de_bnd_n: 1,    //   10
    reg_soft_rst_p_nd0_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_nd0_0_axi_bnd_n: 1,    //  12
    reg_soft_rst_x_nd0_0_axi_n:  1,    //     13
                              : 18;    //  31:14 reserved
}SCRG_CTRL_ND0_CRG_ND003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_0010    crg_nd004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ND0_CRG_ND004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_0014    crg_nd005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ND0_CRG_ND005_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_0018    crg_nd006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ND0_CRG_ND006_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND0_CRG_ND000_O22A0_T          crg_nd000  ;             // 0x49_0000
    SCRG_CTRL_ND0_CRG_ND001_O22A0_T          crg_nd001  ;             // 0x49_0004
    SCRG_CTRL_ND0_CRG_ND002_O22A0_T          crg_nd002  ;             // 0x49_0008
    SCRG_CTRL_ND0_CRG_ND003_O22A0_T          crg_nd003  ;             // 0x49_000C
    SCRG_CTRL_ND0_CRG_ND004_O22A0_T          crg_nd004  ;             // 0x49_0010
    SCRG_CTRL_ND0_CRG_ND005_O22A0_T          crg_nd005  ;             // 0x49_0014
    SCRG_CTRL_ND0_CRG_ND006_O22A0_T          crg_nd006  ;             // 0x49_0018
}SCRG_CTRL_ND0_REG_O22A0_T;
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

#define SCRG_CTRL_ND0_CRG_ND000_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_ND0_CRG_ND001_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_ND0_CRG_ND002_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_ND0_CRG_ND003_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_ND0_CRG_ND004_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_ND0_CRG_ND005_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_ND0_CRG_ND006_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x49_0000    crg_nd000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ND0_CRG_ND000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_0004    crg_nd001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ND0_CRG_ND001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_0008    crg_nd002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_ND0_CRG_ND002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_000C    crg_nd003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_h_imx_10_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_imx_11_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_nd0_0_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_nd0_1_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_nd0_2_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_nd0_3_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_nd0_4_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_nd0_5_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_nd0_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_nd0_0_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_x_nd0_0_axi_n: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}SCRG_CTRL_ND0_CRG_ND003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_0010    crg_nd004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ND0_CRG_ND004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_0014    crg_nd005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ND0_CRG_ND005_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x49_0018    crg_nd006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ND0_CRG_ND006_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ND0_CRG_ND000_O22A0_T          crg_nd000  ;             // 0x49_0000
    SCRG_CTRL_ND0_CRG_ND001_O22A0_T          crg_nd001  ;             // 0x49_0004
    SCRG_CTRL_ND0_CRG_ND002_O22A0_T          crg_nd002  ;             // 0x49_0008
    SCRG_CTRL_ND0_CRG_ND003_O22A0_T          crg_nd003  ;             // 0x49_000C
    SCRG_CTRL_ND0_CRG_ND004_O22A0_T          crg_nd004  ;             // 0x49_0010
    SCRG_CTRL_ND0_CRG_ND005_O22A0_T          crg_nd005  ;             // 0x49_0014
    SCRG_CTRL_ND0_CRG_ND006_O22A0_T          crg_nd006  ;             // 0x49_0018
}SCRG_CTRL_ND0_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

