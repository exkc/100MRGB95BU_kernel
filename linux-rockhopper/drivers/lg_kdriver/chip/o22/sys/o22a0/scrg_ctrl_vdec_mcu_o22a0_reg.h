#ifndef _SCRG_CTRL_VDEC_MCU_REG_H_
#define _SCRG_CTRL_VDEC_MCU_REG_H_

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
    0x31_0000    crg_vdec_mcu00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0004    crg_vdec_mcu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0008    crg_vdec_mcu02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi0_clk_gate_en      :  1,    //      1
    reg_axi1_clk_gate_en      :  1,    //      2
    reg_bus_clk_gate_en       :  1,    //      3
    reg_mcu_clk_gate_en       :  1,    //      4
    reg_sys_clk_0_gate_en     :  1,    //      5
    reg_sys_clk_1_gate_en     :  1,    //      6
    reg_sys_clk_2_gate_en     :  1,    //      7
    reg_sys_clk_3_gate_en     :  1,    //      8
    reg_sys_clk_4_gate_en     :  1,    //      9
    reg_sys_clk_5_gate_en     :  1,    //     10
    reg_te_clk_gate_en        :  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_000C    crg_vdec_mcu03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi0_n       :  1,    //      1
    reg_soft_rst_axi1_n       :  1,    //      2
    reg_soft_rst_bus_n        :  1,    //      3
    reg_soft_rst_e_te_6_te_bnd_n: 1,    //     4
    reg_soft_rst_e_te_7_te_bnd_n: 1,    //     5
    reg_soft_rst_f_te_0_apb_bnd_n: 1,    //    6
    reg_soft_rst_f_te_1_apb_bnd_n: 1,    //    7
    reg_soft_rst_f_te_2_apb_bnd_n: 1,    //    8
    reg_soft_rst_f_te_3_apb_bnd_n: 1,    //    9
    reg_soft_rst_mcu_n        :  1,    //     10
    reg_soft_rst_p_vd_mcu_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_sys0_n       :  1,    //     12
    reg_soft_rst_sys1_n       :  1,    //     13
    reg_soft_rst_sys2_n       :  1,    //     14
    reg_soft_rst_sys3_n       :  1,    //     15
    reg_soft_rst_sys4_n       :  1,    //     16
    reg_soft_rst_sys5_n       :  1,    //     17
    reg_soft_rst_te_n         :  1,    //     18
    reg_soft_rst_x_vd_mcu_0_axi_bnd_n: 1,    //  19
    reg_soft_rst_x_vd_mcu_0_axi_n: 1,    //   20
                              : 11;    //  31:21 reserved
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0010    crg_vdec_mcu04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0014    crg_vdec_mcu05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi0_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0018    crg_vdec_mcu06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi1_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_001C    crg_vdec_mcu07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0020    crg_vdec_mcu08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mcu_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0024    crg_vdec_mcu09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vdec_mcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU00_O22A0_T    crg_vdec_mcu00;      // 0x31_0000
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU01_O22A0_T    crg_vdec_mcu01;      // 0x31_0004
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU02_O22A0_T    crg_vdec_mcu02;      // 0x31_0008
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU03_O22A0_T    crg_vdec_mcu03;      // 0x31_000C
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU04_O22A0_T    crg_vdec_mcu04;      // 0x31_0010
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU05_O22A0_T    crg_vdec_mcu05;      // 0x31_0014
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU06_O22A0_T    crg_vdec_mcu06;      // 0x31_0018
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU07_O22A0_T    crg_vdec_mcu07;      // 0x31_001C
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU08_O22A0_T    crg_vdec_mcu08;      // 0x31_0020
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU09_O22A0_T    crg_vdec_mcu09;      // 0x31_0024
}SCRG_CTRL_VDEC_MCU_REG_O22A0_T;
/* 10 regs */

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

#define SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU00_O22A0_T_OFF             (BASEADDRESS+0x0000)
#define SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU01_O22A0_T_OFF             (BASEADDRESS+0x0004)
#define SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU02_O22A0_T_OFF             (BASEADDRESS+0x0008)
#define SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU03_O22A0_T_OFF             (BASEADDRESS+0x000C)
#define SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU04_O22A0_T_OFF             (BASEADDRESS+0x0010)
#define SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU05_O22A0_T_OFF             (BASEADDRESS+0x0014)
#define SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU06_O22A0_T_OFF             (BASEADDRESS+0x0018)
#define SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU07_O22A0_T_OFF             (BASEADDRESS+0x001C)
#define SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU08_O22A0_T_OFF             (BASEADDRESS+0x0020)
#define SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU09_O22A0_T_OFF             (BASEADDRESS+0x0024)

/*-----------------------------------------------------------------------------------------
    0x31_0000    crg_vdec_mcu00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0004    crg_vdec_mcu01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0008    crg_vdec_mcu02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi0_clk_gate_en: 1;    //      1
    UINT32 reg_axi1_clk_gate_en: 1;    //      2
    UINT32 reg_bus_clk_gate_en:  1;    //      3
    UINT32 reg_mcu_clk_gate_en:  1;    //      4
    UINT32 reg_sys_clk_0_gate_en: 1;    //     5
    UINT32 reg_sys_clk_1_gate_en: 1;    //     6
    UINT32 reg_sys_clk_2_gate_en: 1;    //     7
    UINT32 reg_sys_clk_3_gate_en: 1;    //     8
    UINT32 reg_sys_clk_4_gate_en: 1;    //     9
    UINT32 reg_sys_clk_5_gate_en: 1;    //    10
    UINT32 reg_te_clk_gate_en :  1;    //     11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_000C    crg_vdec_mcu03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi0_n:  1;    //      1
    UINT32 reg_soft_rst_axi1_n:  1;    //      2
    UINT32 reg_soft_rst_bus_n :  1;    //      3
    UINT32 reg_soft_rst_e_te_6_te_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_e_te_7_te_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_te_0_apb_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_te_1_apb_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_te_2_apb_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_te_3_apb_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_mcu_n :  1;    //     10
    UINT32 reg_soft_rst_p_vd_mcu_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_sys0_n:  1;    //     12
    UINT32 reg_soft_rst_sys1_n:  1;    //     13
    UINT32 reg_soft_rst_sys2_n:  1;    //     14
    UINT32 reg_soft_rst_sys3_n:  1;    //     15
    UINT32 reg_soft_rst_sys4_n:  1;    //     16
    UINT32 reg_soft_rst_sys5_n:  1;    //     17
    UINT32 reg_soft_rst_te_n  :  1;    //     18
    UINT32 reg_soft_rst_x_vd_mcu_0_axi_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_x_vd_mcu_0_axi_n: 1;    //  20
    UINT32 resvd00            : 11;    //  31:21 reserved
    };
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0010    crg_vdec_mcu04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0014    crg_vdec_mcu05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi0_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0018    crg_vdec_mcu06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi1_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_001C    crg_vdec_mcu07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0020    crg_vdec_mcu08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_mcu_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x31_0024    crg_vdec_mcu09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_te_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vdec_mcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU00_O22A0_T    crg_vdec_mcu00;      // 0x31_0000
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU01_O22A0_T    crg_vdec_mcu01;      // 0x31_0004
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU02_O22A0_T    crg_vdec_mcu02;      // 0x31_0008
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU03_O22A0_T    crg_vdec_mcu03;      // 0x31_000C
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU04_O22A0_T    crg_vdec_mcu04;      // 0x31_0010
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU05_O22A0_T    crg_vdec_mcu05;      // 0x31_0014
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU06_O22A0_T    crg_vdec_mcu06;      // 0x31_0018
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU07_O22A0_T    crg_vdec_mcu07;      // 0x31_001C
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU08_O22A0_T    crg_vdec_mcu08;      // 0x31_0020
    SCRG_CTRL_VDEC_MCU_CRG_VDEC_MCU09_O22A0_T    crg_vdec_mcu09;      // 0x31_0024
}SCRG_CTRL_VDEC_MCU_REG_O22A0_T;
/* 10 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

