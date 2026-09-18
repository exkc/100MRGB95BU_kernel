#ifndef _SCRG_CTRL_GSC_REG_H_
#define _SCRG_CTRL_GSC_REG_H_

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
    0x46_0000    crg_gsc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_GSC_CRG_GSC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_0004    crg_gsc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_GSC_CRG_GSC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_0008    crg_gsc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_GSC_CRG_GSC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_000C    crg_gsc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_gsc_6_de_bnd_n: 1,    //    3
    reg_soft_rst_f_vsd_0_de_bnd_n: 1,    //    4
    reg_soft_rst_h_fmc_0_de_bnd_n: 1,    //    5
    reg_soft_rst_h_fmc_1_de_bnd_n: 1,    //    6
    reg_soft_rst_h_fmc_2_de_bnd_n: 1,    //    7
    reg_soft_rst_h_fmc_3_de_bnd_n: 1,    //    8
    reg_soft_rst_h_fmc_4_de_bnd_n: 1,    //    9
    reg_soft_rst_h_fmc_5_de_bnd_n: 1,    //   10
    reg_soft_rst_h_gsc_0_de_bnd_n: 1,    //   11
    reg_soft_rst_h_gsc_10_de_bnd_n: 1,    //  12
    reg_soft_rst_h_gsc_1_de_bnd_n: 1,    //   13
    reg_soft_rst_h_gsc_2_de_bnd_n: 1,    //   14
    reg_soft_rst_h_gsc_3_de_bnd_n: 1,    //   15
    reg_soft_rst_h_gsc_4_de_bnd_n: 1,    //   16
    reg_soft_rst_h_gsc_5_de_bnd_n: 1,    //   17
    reg_soft_rst_h_gsc_7_de_bnd_n: 1,    //   18
    reg_soft_rst_h_gsc_8_de_bnd_n: 1,    //   19
    reg_soft_rst_h_gsc_9_de_bnd_n: 1,    //   20
    reg_soft_rst_p_gsc_0_axi_bnd_n: 1,    //  21
    reg_soft_rst_p_gsc_1_axi_bnd_n: 1,    //  22
    reg_soft_rst_x_gsc_0_axi_bnd_n: 1,    //  23
    reg_soft_rst_x_gsc_0_axi_n:  1,    //     24
    reg_soft_rst_x_gsc_1_axi_bnd_n: 1,    //  25
    reg_soft_rst_x_gsc_1_axi_n:  1,    //     26
                              :  5;    //  31:27 reserved
}SCRG_CTRL_GSC_CRG_GSC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_0010    crg_gsc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_GSC_CRG_GSC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_0014    crg_gsc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_GSC_CRG_GSC05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_0018    crg_gsc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_GSC_CRG_GSC06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_gsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GSC_CRG_GSC00_O22A0_T          crg_gsc00  ;             // 0x46_0000
    SCRG_CTRL_GSC_CRG_GSC01_O22A0_T          crg_gsc01  ;             // 0x46_0004
    SCRG_CTRL_GSC_CRG_GSC02_O22A0_T          crg_gsc02  ;             // 0x46_0008
    SCRG_CTRL_GSC_CRG_GSC03_O22A0_T          crg_gsc03  ;             // 0x46_000C
    SCRG_CTRL_GSC_CRG_GSC04_O22A0_T          crg_gsc04  ;             // 0x46_0010
    SCRG_CTRL_GSC_CRG_GSC05_O22A0_T          crg_gsc05  ;             // 0x46_0014
    SCRG_CTRL_GSC_CRG_GSC06_O22A0_T          crg_gsc06  ;             // 0x46_0018
}SCRG_CTRL_GSC_REG_O22A0_T;
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

#define SCRG_CTRL_GSC_CRG_GSC00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_GSC_CRG_GSC01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_GSC_CRG_GSC02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_GSC_CRG_GSC03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_GSC_CRG_GSC04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_GSC_CRG_GSC05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_GSC_CRG_GSC06_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x46_0000    crg_gsc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_GSC_CRG_GSC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_0004    crg_gsc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_GSC_CRG_GSC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_0008    crg_gsc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_GSC_CRG_GSC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_000C    crg_gsc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_gsc_6_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_f_vsd_0_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_fmc_0_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_fmc_1_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_fmc_2_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_fmc_3_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_fmc_4_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_fmc_5_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_gsc_0_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_gsc_10_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_gsc_1_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_gsc_2_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_gsc_3_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_gsc_4_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_gsc_5_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_h_gsc_7_de_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_h_gsc_8_de_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_h_gsc_9_de_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_p_gsc_0_axi_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_p_gsc_1_axi_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_x_gsc_0_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_x_gsc_0_axi_n: 1;    //  24
    UINT32 reg_soft_rst_x_gsc_1_axi_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_x_gsc_1_axi_n: 1;    //  26
    UINT32 resvd00            :  5;    //  31:27 reserved
    };
}SCRG_CTRL_GSC_CRG_GSC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_0010    crg_gsc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_GSC_CRG_GSC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_0014    crg_gsc05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_GSC_CRG_GSC05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x46_0018    crg_gsc06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_GSC_CRG_GSC06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_gsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GSC_CRG_GSC00_O22A0_T          crg_gsc00  ;             // 0x46_0000
    SCRG_CTRL_GSC_CRG_GSC01_O22A0_T          crg_gsc01  ;             // 0x46_0004
    SCRG_CTRL_GSC_CRG_GSC02_O22A0_T          crg_gsc02  ;             // 0x46_0008
    SCRG_CTRL_GSC_CRG_GSC03_O22A0_T          crg_gsc03  ;             // 0x46_000C
    SCRG_CTRL_GSC_CRG_GSC04_O22A0_T          crg_gsc04  ;             // 0x46_0010
    SCRG_CTRL_GSC_CRG_GSC05_O22A0_T          crg_gsc05  ;             // 0x46_0014
    SCRG_CTRL_GSC_CRG_GSC06_O22A0_T          crg_gsc06  ;             // 0x46_0018
}SCRG_CTRL_GSC_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

