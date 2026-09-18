#ifndef _SCRG_CTRL_IMX_REG_H_
#define _SCRG_CTRL_IMX_REG_H_

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
    0x2C_0000    crg_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_IMX_CRG_IMX00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_0004    crg_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_IMX_CRG_IMX01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_0008    crg_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_IMX_CRG_IMX02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_000C    crg_imx03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_cco_5_de_bnd_n: 1,    //    3
    reg_soft_rst_f_cvi_0_de_bnd_n: 1,    //    4
    reg_soft_rst_f_cvi_1_de_bnd_n: 1,    //    5
    reg_soft_rst_f_cvi_2_de_bnd_n: 1,    //    6
    reg_soft_rst_f_cvi_3_de_bnd_n: 1,    //    7
    reg_soft_rst_f_cvi_4_de_bnd_n: 1,    //    8
    reg_soft_rst_f_imx_16_de_bnd_n: 1,    //   9
    reg_soft_rst_h_hdr_0_de_bnd_n: 1,    //   10
    reg_soft_rst_h_hdr_1_de_bnd_n: 1,    //   11
    reg_soft_rst_h_hdr_2_de_bnd_n: 1,    //   12
    reg_soft_rst_h_hdr_3_de_bnd_n: 1,    //   13
    reg_soft_rst_h_hdr_4_de_bnd_n: 1,    //   14
    reg_soft_rst_h_hdr_5_de_bnd_n: 1,    //   15
    reg_soft_rst_h_imx_0_de_bnd_n: 1,    //   16
    reg_soft_rst_h_imx_10_de_bnd_n: 1,    //  17
    reg_soft_rst_h_imx_11_de_bnd_n: 1,    //  18
    reg_soft_rst_h_imx_12_de_bnd_n: 1,    //  19
    reg_soft_rst_h_imx_13_de_bnd_n: 1,    //  20
    reg_soft_rst_h_imx_14_de_bnd_n: 1,    //  21
    reg_soft_rst_h_imx_15_de_bnd_n: 1,    //  22
    reg_soft_rst_h_imx_1_de_bnd_n: 1,    //   23
    reg_soft_rst_h_imx_2_de_bnd_n: 1,    //   24
    reg_soft_rst_h_imx_3_de_bnd_n: 1,    //   25
    reg_soft_rst_h_imx_4_de_bnd_n: 1,    //   26
    reg_soft_rst_h_imx_5_de_bnd_n: 1,    //   27
    reg_soft_rst_h_imx_6_de_bnd_n: 1,    //   28
    reg_soft_rst_h_imx_7_de_bnd_n: 1,    //   29
    reg_soft_rst_h_imx_8_de_bnd_n: 1,    //   30
    reg_soft_rst_h_imx_9_de_bnd_n: 1;    //   31
}SCRG_CTRL_IMX_CRG_IMX03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_0010    crg_imx04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_h_nd0_0_de_bnd_n: 1,    //    0
    reg_soft_rst_h_nd0_1_de_bnd_n: 1,    //    1
    reg_soft_rst_h_nd1_0_de_bnd_n: 1,    //    2
    reg_soft_rst_h_nd1_1_de_bnd_n: 1,    //    3
    reg_soft_rst_h_sre_4_de_bnd_n: 1,    //    4
    reg_soft_rst_h_sre_5_de_bnd_n: 1,    //    5
    reg_soft_rst_h_sre_6_de_bnd_n: 1,    //    6
    reg_soft_rst_h_vdo_0_de_bnd_n: 1,    //    7
    reg_soft_rst_h_vdo_1_de_bnd_n: 1,    //    8
    reg_soft_rst_h_vdo_2_de_bnd_n: 1,    //    9
    reg_soft_rst_h_vdo_3_de_bnd_n: 1,    //   10
    reg_soft_rst_h_vdo_4_de_bnd_n: 1,    //   11
    reg_soft_rst_h_vdo_5_de_bnd_n: 1,    //   12
    reg_soft_rst_p_imx_0_axi_bnd_n: 1,    //  13
    reg_soft_rst_p_imx_1_axi_bnd_n: 1,    //  14
    reg_soft_rst_p_imx_2_axi_bnd_n: 1,    //  15
    reg_soft_rst_p_imx_3_axi_bnd_n: 1,    //  16
    reg_soft_rst_x_imx_0_axi_bnd_n: 1,    //  17
    reg_soft_rst_x_imx_0_axi_n:  1,    //     18
    reg_soft_rst_x_imx_1_axi_bnd_n: 1,    //  19
    reg_soft_rst_x_imx_1_axi_n:  1,    //     20
    reg_soft_rst_x_imx_2_axi_bnd_n: 1,    //  21
    reg_soft_rst_x_imx_2_axi_n:  1,    //     22
    reg_soft_rst_x_imx_3_axi_bnd_n: 1,    //  23
    reg_soft_rst_x_imx_3_axi_n:  1,    //     24
                              :  7;    //  31:25 reserved
}SCRG_CTRL_IMX_CRG_IMX04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_0014    crg_imx05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_IMX_CRG_IMX05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_0018    crg_imx06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_IMX_CRG_IMX06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_001C    crg_imx07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_IMX_CRG_IMX07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_IMX_CRG_IMX00_O22A0_T          crg_imx00  ;             // 0x2C_0000
    SCRG_CTRL_IMX_CRG_IMX01_O22A0_T          crg_imx01  ;             // 0x2C_0004
    SCRG_CTRL_IMX_CRG_IMX02_O22A0_T          crg_imx02  ;             // 0x2C_0008
    SCRG_CTRL_IMX_CRG_IMX03_O22A0_T          crg_imx03  ;             // 0x2C_000C
    SCRG_CTRL_IMX_CRG_IMX04_O22A0_T          crg_imx04  ;             // 0x2C_0010
    SCRG_CTRL_IMX_CRG_IMX05_O22A0_T          crg_imx05  ;             // 0x2C_0014
    SCRG_CTRL_IMX_CRG_IMX06_O22A0_T          crg_imx06  ;             // 0x2C_0018
    SCRG_CTRL_IMX_CRG_IMX07_O22A0_T          crg_imx07  ;             // 0x2C_001C
}SCRG_CTRL_IMX_REG_O22A0_T;
/* 8 regs */

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

#define SCRG_CTRL_IMX_CRG_IMX00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_IMX_CRG_IMX01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_IMX_CRG_IMX02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_IMX_CRG_IMX03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_IMX_CRG_IMX04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_IMX_CRG_IMX05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_IMX_CRG_IMX06_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_IMX_CRG_IMX07_O22A0_T_OFF                       (BASEADDRESS+0x001C)

/*-----------------------------------------------------------------------------------------
    0x2C_0000    crg_imx00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_IMX_CRG_IMX00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_0004    crg_imx01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_IMX_CRG_IMX01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_0008    crg_imx02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_IMX_CRG_IMX02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_000C    crg_imx03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_cco_5_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_f_cvi_0_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_cvi_1_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_cvi_2_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_cvi_3_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_cvi_4_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_imx_16_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_hdr_0_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_hdr_1_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_hdr_2_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_h_hdr_3_de_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_h_hdr_4_de_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_h_hdr_5_de_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_h_imx_0_de_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_h_imx_10_de_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_h_imx_11_de_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_h_imx_12_de_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_h_imx_13_de_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_h_imx_14_de_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_h_imx_15_de_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_h_imx_1_de_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_h_imx_2_de_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_h_imx_3_de_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_h_imx_4_de_bnd_n: 1;    //  26
    UINT32 reg_soft_rst_h_imx_5_de_bnd_n: 1;    //  27
    UINT32 reg_soft_rst_h_imx_6_de_bnd_n: 1;    //  28
    UINT32 reg_soft_rst_h_imx_7_de_bnd_n: 1;    //  29
    UINT32 reg_soft_rst_h_imx_8_de_bnd_n: 1;    //  30
    UINT32 reg_soft_rst_h_imx_9_de_bnd_n: 1;    //  31
    };
}SCRG_CTRL_IMX_CRG_IMX03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_0010    crg_imx04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_h_nd0_0_de_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_h_nd0_1_de_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_h_nd1_0_de_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_h_nd1_1_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_sre_4_de_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_h_sre_5_de_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_h_sre_6_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_vdo_0_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_vdo_1_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_vdo_2_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_vdo_3_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_vdo_4_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_h_vdo_5_de_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_p_imx_0_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_p_imx_1_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_p_imx_2_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_p_imx_3_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_x_imx_0_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_x_imx_0_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_imx_1_axi_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_x_imx_1_axi_n: 1;    //  20
    UINT32 reg_soft_rst_x_imx_2_axi_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_x_imx_2_axi_n: 1;    //  22
    UINT32 reg_soft_rst_x_imx_3_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_x_imx_3_axi_n: 1;    //  24
    UINT32 resvd00            :  7;    //  31:25 reserved
    };
}SCRG_CTRL_IMX_CRG_IMX04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_0014    crg_imx05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_IMX_CRG_IMX05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_0018    crg_imx06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_IMX_CRG_IMX06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2C_001C    crg_imx07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_IMX_CRG_IMX07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_IMX_CRG_IMX00_O22A0_T          crg_imx00  ;             // 0x2C_0000
    SCRG_CTRL_IMX_CRG_IMX01_O22A0_T          crg_imx01  ;             // 0x2C_0004
    SCRG_CTRL_IMX_CRG_IMX02_O22A0_T          crg_imx02  ;             // 0x2C_0008
    SCRG_CTRL_IMX_CRG_IMX03_O22A0_T          crg_imx03  ;             // 0x2C_000C
    SCRG_CTRL_IMX_CRG_IMX04_O22A0_T          crg_imx04  ;             // 0x2C_0010
    SCRG_CTRL_IMX_CRG_IMX05_O22A0_T          crg_imx05  ;             // 0x2C_0014
    SCRG_CTRL_IMX_CRG_IMX06_O22A0_T          crg_imx06  ;             // 0x2C_0018
    SCRG_CTRL_IMX_CRG_IMX07_O22A0_T          crg_imx07  ;             // 0x2C_001C
}SCRG_CTRL_IMX_REG_O22A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

