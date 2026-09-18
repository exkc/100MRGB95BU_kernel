#ifndef _SCRG_CTRL_LBUS_REG_H_
#define _SCRG_CTRL_LBUS_REG_H_

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
    0x2F_0000    crg_lbus00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LBUS_CRG_LBUS00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_0004    crg_lbus01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LBUS_CRG_LBUS01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_0008    crg_lbus02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fast_clk_gate_en      :  1,    //      0
    reg_main_clk_gate_en      :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_LBUS_CRG_LBUS02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_000C    crg_lbus03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_fast_n       :  1,    //      0
    reg_soft_rst_main_n       :  1,    //      1
    reg_soft_rst_p_lbus_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_p_lbus_1_axi_bnd_n: 1,    //  3
    reg_soft_rst_p_lbus_2_axi_bnd_n: 1,    //  4
    reg_soft_rst_p_lbus_3_axi_bnd_n: 1,    //  5
    reg_soft_rst_p_lbus_4_axi_bnd_n: 1,    //  6
    reg_soft_rst_p_lbus_5_axi_bnd_n: 1,    //  7
    reg_soft_rst_p_lbus_6_axi_bnd_n: 1,    //  8
    reg_soft_rst_p_lbus_7_axi_bnd_n: 1,    //  9
    reg_soft_rst_x_aud_1_axi_n:  1,    //     10
    reg_soft_rst_x_aud_2_axi_n:  1,    //     11
    reg_soft_rst_x_cco_0_axi_n:  1,    //     12
    reg_soft_rst_x_cco_1_axi_n:  1,    //     13
    reg_soft_rst_x_cvd_0_axi_n:  1,    //     14
    reg_soft_rst_x_dbb_0_axi_n:  1,    //     15
    reg_soft_rst_x_dne_0_axi_n:  1,    //     16
    reg_soft_rst_x_dne_1_axi_n:  1,    //     17
    reg_soft_rst_x_fmc_0_axi_n:  1,    //     18
    reg_soft_rst_x_fmc_1_axi_n:  1,    //     19
    reg_soft_rst_x_fmc_2_axi_n:  1,    //     20
    reg_soft_rst_x_fmc_3_axi_n:  1,    //     21
    reg_soft_rst_x_fms_0_axi_n:  1,    //     22
    reg_soft_rst_x_gfx_0_axi_n:  1,    //     23
    reg_soft_rst_x_gpu_0_axi_n:  1,    //     24
    reg_soft_rst_x_gsc_0_axi_n:  1,    //     25
    reg_soft_rst_x_gsc_1_axi_n:  1,    //     26
    reg_soft_rst_x_imx_0_axi_n:  1,    //     27
    reg_soft_rst_x_imx_1_axi_n:  1,    //     28
    reg_soft_rst_x_imx_2_axi_n:  1,    //     29
    reg_soft_rst_x_imx_3_axi_n:  1,    //     30
    reg_soft_rst_x_lbus_0_axi_bnd_n: 1;    //  31
}SCRG_CTRL_LBUS_CRG_LBUS03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_0010    crg_lbus04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_x_lbus_0_axi_n: 1,    //      0
    reg_soft_rst_x_lbus_1_axi_bnd_n: 1,    //  1
    reg_soft_rst_x_lbus_1_axi_n: 1,    //      2
    reg_soft_rst_x_lbus_2_axi_bnd_n: 1,    //  3
    reg_soft_rst_x_lbus_2_axi_n: 1,    //      4
    reg_soft_rst_x_lbus_3_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_lbus_3_axi_n: 1,    //      6
    reg_soft_rst_x_lbus_4_axi_bnd_n: 1,    //  7
    reg_soft_rst_x_lbus_4_axi_n: 1,    //      8
    reg_soft_rst_x_lbus_5_axi_bnd_n: 1,    //  9
    reg_soft_rst_x_lbus_5_axi_n: 1,    //     10
    reg_soft_rst_x_lbus_6_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_lbus_6_axi_n: 1,    //     12
    reg_soft_rst_x_lbus_7_axi_bnd_n: 1,    //  13
    reg_soft_rst_x_lbus_7_axi_n: 1,    //     14
    reg_soft_rst_x_lne_0_axi_n:  1,    //     15
    reg_soft_rst_x_mcu_0_axi_n:  1,    //     16
    reg_soft_rst_x_me0_0_axi_n:  1,    //     17
    reg_soft_rst_x_me0_1_axi_n:  1,    //     18
    reg_soft_rst_x_me1_0_axi_n:  1,    //     19
    reg_soft_rst_x_nd0_0_axi_n:  1,    //     20
    reg_soft_rst_x_nd1_0_axi_n:  1,    //     21
    reg_soft_rst_x_sre_0_axi_n:  1,    //     22
    reg_soft_rst_x_srnr_0_axi_n: 1,    //     23
    reg_soft_rst_x_tiv_0_axi_n:  1,    //     24
    reg_soft_rst_x_vd0_0_axi_n:  1,    //     25
    reg_soft_rst_x_vd0_1_axi_n:  1,    //     26
    reg_soft_rst_x_vd1_0_axi_n:  1,    //     27
    reg_soft_rst_x_vd1_1_axi_n:  1,    //     28
    reg_soft_rst_x_vd2_0_axi_n:  1,    //     29
    reg_soft_rst_x_vd2_1_axi_n:  1,    //     30
    reg_soft_rst_x_vd3_0_axi_n:  1;    //     31
}SCRG_CTRL_LBUS_CRG_LBUS04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_0014    crg_lbus05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_x_vd3_1_axi_n:  1,    //      0
    reg_soft_rst_x_vdec_mcu_0_axi_n: 1,    //  1
    reg_soft_rst_x_vdo_0_axi_n:  1,    //      2
    reg_soft_rst_x_vdo_1_axi_n:  1,    //      3
    reg_soft_rst_x_vdo_2_axi_n:  1,    //      4
    reg_soft_rst_x_vdo_3_axi_n:  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_LBUS_CRG_LBUS05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_0018    crg_lbus06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fast_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_LBUS_CRG_LBUS06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_001C    crg_lbus07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_LBUS_CRG_LBUS07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_lbus Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LBUS_CRG_LBUS00_O22A0_T        crg_lbus00 ;             // 0x2F_0000
    SCRG_CTRL_LBUS_CRG_LBUS01_O22A0_T        crg_lbus01 ;             // 0x2F_0004
    SCRG_CTRL_LBUS_CRG_LBUS02_O22A0_T        crg_lbus02 ;             // 0x2F_0008
    SCRG_CTRL_LBUS_CRG_LBUS03_O22A0_T        crg_lbus03 ;             // 0x2F_000C
    SCRG_CTRL_LBUS_CRG_LBUS04_O22A0_T        crg_lbus04 ;             // 0x2F_0010
    SCRG_CTRL_LBUS_CRG_LBUS05_O22A0_T        crg_lbus05 ;             // 0x2F_0014
    SCRG_CTRL_LBUS_CRG_LBUS06_O22A0_T        crg_lbus06 ;             // 0x2F_0018
    SCRG_CTRL_LBUS_CRG_LBUS07_O22A0_T        crg_lbus07 ;             // 0x2F_001C
}SCRG_CTRL_LBUS_REG_O22A0_T;
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

#define SCRG_CTRL_LBUS_CRG_LBUS00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define SCRG_CTRL_LBUS_CRG_LBUS01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define SCRG_CTRL_LBUS_CRG_LBUS02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define SCRG_CTRL_LBUS_CRG_LBUS03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define SCRG_CTRL_LBUS_CRG_LBUS04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define SCRG_CTRL_LBUS_CRG_LBUS05_O22A0_T_OFF                     (BASEADDRESS+0x0014)
#define SCRG_CTRL_LBUS_CRG_LBUS06_O22A0_T_OFF                     (BASEADDRESS+0x0018)
#define SCRG_CTRL_LBUS_CRG_LBUS07_O22A0_T_OFF                     (BASEADDRESS+0x001C)

/*-----------------------------------------------------------------------------------------
    0x2F_0000    crg_lbus00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LBUS_CRG_LBUS00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_0004    crg_lbus01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LBUS_CRG_LBUS01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_0008    crg_lbus02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fast_clk_gate_en: 1;    //      0
    UINT32 reg_main_clk_gate_en: 1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_LBUS_CRG_LBUS02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_000C    crg_lbus03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_fast_n:  1;    //      0
    UINT32 reg_soft_rst_main_n:  1;    //      1
    UINT32 reg_soft_rst_p_lbus_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_lbus_1_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_lbus_2_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_lbus_3_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_lbus_4_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_lbus_5_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_lbus_6_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_lbus_7_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_aud_1_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_aud_2_axi_n: 1;    //  11
    UINT32 reg_soft_rst_x_cco_0_axi_n: 1;    //  12
    UINT32 reg_soft_rst_x_cco_1_axi_n: 1;    //  13
    UINT32 reg_soft_rst_x_cvd_0_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_dbb_0_axi_n: 1;    //  15
    UINT32 reg_soft_rst_x_dne_0_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_dne_1_axi_n: 1;    //  17
    UINT32 reg_soft_rst_x_fmc_0_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_fmc_1_axi_n: 1;    //  19
    UINT32 reg_soft_rst_x_fmc_2_axi_n: 1;    //  20
    UINT32 reg_soft_rst_x_fmc_3_axi_n: 1;    //  21
    UINT32 reg_soft_rst_x_fms_0_axi_n: 1;    //  22
    UINT32 reg_soft_rst_x_gfx_0_axi_n: 1;    //  23
    UINT32 reg_soft_rst_x_gpu_0_axi_n: 1;    //  24
    UINT32 reg_soft_rst_x_gsc_0_axi_n: 1;    //  25
    UINT32 reg_soft_rst_x_gsc_1_axi_n: 1;    //  26
    UINT32 reg_soft_rst_x_imx_0_axi_n: 1;    //  27
    UINT32 reg_soft_rst_x_imx_1_axi_n: 1;    //  28
    UINT32 reg_soft_rst_x_imx_2_axi_n: 1;    //  29
    UINT32 reg_soft_rst_x_imx_3_axi_n: 1;    //  30
    UINT32 reg_soft_rst_x_lbus_0_axi_bnd_n: 1;    //  31
    };
}SCRG_CTRL_LBUS_CRG_LBUS03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_0010    crg_lbus04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_x_lbus_0_axi_n: 1;    //  0
    UINT32 reg_soft_rst_x_lbus_1_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_x_lbus_1_axi_n: 1;    //  2
    UINT32 reg_soft_rst_x_lbus_2_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_lbus_2_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_lbus_3_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_lbus_3_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_lbus_4_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_lbus_4_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_lbus_5_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_lbus_5_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_lbus_6_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_lbus_6_axi_n: 1;    //  12
    UINT32 reg_soft_rst_x_lbus_7_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_x_lbus_7_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_lne_0_axi_n: 1;    //  15
    UINT32 reg_soft_rst_x_mcu_0_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_me0_0_axi_n: 1;    //  17
    UINT32 reg_soft_rst_x_me0_1_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_me1_0_axi_n: 1;    //  19
    UINT32 reg_soft_rst_x_nd0_0_axi_n: 1;    //  20
    UINT32 reg_soft_rst_x_nd1_0_axi_n: 1;    //  21
    UINT32 reg_soft_rst_x_sre_0_axi_n: 1;    //  22
    UINT32 reg_soft_rst_x_srnr_0_axi_n: 1;    //  23
    UINT32 reg_soft_rst_x_tiv_0_axi_n: 1;    //  24
    UINT32 reg_soft_rst_x_vd0_0_axi_n: 1;    //  25
    UINT32 reg_soft_rst_x_vd0_1_axi_n: 1;    //  26
    UINT32 reg_soft_rst_x_vd1_0_axi_n: 1;    //  27
    UINT32 reg_soft_rst_x_vd1_1_axi_n: 1;    //  28
    UINT32 reg_soft_rst_x_vd2_0_axi_n: 1;    //  29
    UINT32 reg_soft_rst_x_vd2_1_axi_n: 1;    //  30
    UINT32 reg_soft_rst_x_vd3_0_axi_n: 1;    //  31
    };
}SCRG_CTRL_LBUS_CRG_LBUS04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_0014    crg_lbus05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_x_vd3_1_axi_n: 1;    //  0
    UINT32 reg_soft_rst_x_vdec_mcu_0_axi_n: 1;    //  1
    UINT32 reg_soft_rst_x_vdo_0_axi_n: 1;    //  2
    UINT32 reg_soft_rst_x_vdo_1_axi_n: 1;    //  3
    UINT32 reg_soft_rst_x_vdo_2_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_vdo_3_axi_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_LBUS_CRG_LBUS05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_0018    crg_lbus06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fast_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_LBUS_CRG_LBUS06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x2F_001C    crg_lbus07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_LBUS_CRG_LBUS07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_lbus Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LBUS_CRG_LBUS00_O22A0_T        crg_lbus00 ;             // 0x2F_0000
    SCRG_CTRL_LBUS_CRG_LBUS01_O22A0_T        crg_lbus01 ;             // 0x2F_0004
    SCRG_CTRL_LBUS_CRG_LBUS02_O22A0_T        crg_lbus02 ;             // 0x2F_0008
    SCRG_CTRL_LBUS_CRG_LBUS03_O22A0_T        crg_lbus03 ;             // 0x2F_000C
    SCRG_CTRL_LBUS_CRG_LBUS04_O22A0_T        crg_lbus04 ;             // 0x2F_0010
    SCRG_CTRL_LBUS_CRG_LBUS05_O22A0_T        crg_lbus05 ;             // 0x2F_0014
    SCRG_CTRL_LBUS_CRG_LBUS06_O22A0_T        crg_lbus06 ;             // 0x2F_0018
    SCRG_CTRL_LBUS_CRG_LBUS07_O22A0_T        crg_lbus07 ;             // 0x2F_001C
}SCRG_CTRL_LBUS_REG_O22A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

