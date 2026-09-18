#ifndef _SCRG_CTRL_VDO_REG_H_
#define _SCRG_CTRL_VDO_REG_H_

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
    0x28_0000    crg_vdo00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VDO_CRG_VDO00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0004    crg_vdo01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VDO_CRG_VDO01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0008    crg_vdo02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_clk_gate_en       :  1,    //      1
    reg_bodp0_clk_gate_en     :  1,    //      2
    reg_bodp1_clk_gate_en     :  1,    //      3
    reg_de_clk_gate_en        :  1,    //      4
    reg_vdo0_clk_gate_en      :  1,    //      5
    reg_vdo1_clk_gate_en      :  1,    //      6
    reg_vdo2_clk_gate_en      :  1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_VDO_CRG_VDO02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_000C    crg_vdo03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_axi_sbus_n   :  1,    //      2
    reg_soft_rst_bodp0_n      :  1,    //      3
    reg_soft_rst_bodp1_n      :  1,    //      4
    reg_soft_rst_de_n         :  1,    //      5
    reg_soft_rst_h_vdo_0_de_bnd_n: 1,    //    6
    reg_soft_rst_h_vdo_1_de_bnd_n: 1,    //    7
    reg_soft_rst_h_vdo_2_de_bnd_n: 1,    //    8
    reg_soft_rst_h_vdo_3_de_bnd_n: 1,    //    9
    reg_soft_rst_h_vdo_4_de_bnd_n: 1,    //   10
    reg_soft_rst_h_vdo_5_de_bnd_n: 1,    //   11
    reg_soft_rst_p_vdo_0_axi_bnd_n: 1,    //  12
    reg_soft_rst_p_vdo_1_axi_bnd_n: 1,    //  13
    reg_soft_rst_p_vdo_2_axi_bnd_n: 1,    //  14
    reg_soft_rst_p_vdo_3_axi_bnd_n: 1,    //  15
    reg_soft_rst_vdo0_n       :  1,    //     16
    reg_soft_rst_vdo1_n       :  1,    //     17
    reg_soft_rst_vdo2_n       :  1,    //     18
    reg_soft_rst_x_vdo_0_axi_bnd_n: 1,    //  19
    reg_soft_rst_x_vdo_0_axi_n:  1,    //     20
    reg_soft_rst_x_vdo_1_axi_bnd_n: 1,    //  21
    reg_soft_rst_x_vdo_1_axi_n:  1,    //     22
    reg_soft_rst_x_vdo_2_axi_bnd_n: 1,    //  23
    reg_soft_rst_x_vdo_2_axi_n:  1,    //     24
    reg_soft_rst_x_vdo_3_axi_bnd_n: 1,    //  25
    reg_soft_rst_x_vdo_3_axi_n:  1,    //     26
                              :  5;    //  31:27 reserved
}SCRG_CTRL_VDO_CRG_VDO03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0010    crg_vdo04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bodp0_clk_sel         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_bodp1_clk_sel         :  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_VDO_CRG_VDO04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0014    crg_vdo05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDO_CRG_VDO05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0018    crg_vdo06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDO_CRG_VDO06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_001C    crg_vdo07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bodp0_clk_skip_ctrl   :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDO_CRG_VDO07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0020    crg_vdo08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bodp1_clk_skip_ctrl   :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDO_CRG_VDO08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0024    crg_vdo09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_de_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDO_CRG_VDO09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0028    crg_vdo10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vdo0_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDO_CRG_VDO10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_002C    crg_vdo11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vdo1_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDO_CRG_VDO11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0030    crg_vdo12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vdo2_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VDO_CRG_VDO12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    CRG_VDO Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VDO_CRG_VDO00_O22A0_T          crg_vdo00  ;             // 0x28_0000
    SCRG_CTRL_VDO_CRG_VDO01_O22A0_T          crg_vdo01  ;             // 0x28_0004
    SCRG_CTRL_VDO_CRG_VDO02_O22A0_T          crg_vdo02  ;             // 0x28_0008
    SCRG_CTRL_VDO_CRG_VDO03_O22A0_T          crg_vdo03  ;             // 0x28_000C
    SCRG_CTRL_VDO_CRG_VDO04_O22A0_T          crg_vdo04  ;             // 0x28_0010
    SCRG_CTRL_VDO_CRG_VDO05_O22A0_T          crg_vdo05  ;             // 0x28_0014
    SCRG_CTRL_VDO_CRG_VDO06_O22A0_T          crg_vdo06  ;             // 0x28_0018
    SCRG_CTRL_VDO_CRG_VDO07_O22A0_T          crg_vdo07  ;             // 0x28_001C
    SCRG_CTRL_VDO_CRG_VDO08_O22A0_T          crg_vdo08  ;             // 0x28_0020
    SCRG_CTRL_VDO_CRG_VDO09_O22A0_T          crg_vdo09  ;             // 0x28_0024
    SCRG_CTRL_VDO_CRG_VDO10_O22A0_T          crg_vdo10  ;             // 0x28_0028
    SCRG_CTRL_VDO_CRG_VDO11_O22A0_T          crg_vdo11  ;             // 0x28_002C
    SCRG_CTRL_VDO_CRG_VDO12_O22A0_T          crg_vdo12  ;             // 0x28_0030
}SCRG_CTRL_VDO_REG_O22A0_T;
/* 13 regs */

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

#define SCRG_CTRL_VDO_CRG_VDO00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_VDO_CRG_VDO01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_VDO_CRG_VDO02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_VDO_CRG_VDO03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_VDO_CRG_VDO04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_VDO_CRG_VDO05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_VDO_CRG_VDO06_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_VDO_CRG_VDO07_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define SCRG_CTRL_VDO_CRG_VDO08_O22A0_T_OFF                       (BASEADDRESS+0x0020)
#define SCRG_CTRL_VDO_CRG_VDO09_O22A0_T_OFF                       (BASEADDRESS+0x0024)
#define SCRG_CTRL_VDO_CRG_VDO10_O22A0_T_OFF                       (BASEADDRESS+0x0028)
#define SCRG_CTRL_VDO_CRG_VDO11_O22A0_T_OFF                       (BASEADDRESS+0x002C)
#define SCRG_CTRL_VDO_CRG_VDO12_O22A0_T_OFF                       (BASEADDRESS+0x0030)

/*-----------------------------------------------------------------------------------------
    0x28_0000    crg_vdo00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VDO_CRG_VDO00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0004    crg_vdo01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VDO_CRG_VDO01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0008    crg_vdo02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_clk_gate_en:  1;    //      1
    UINT32 reg_bodp0_clk_gate_en: 1;    //     2
    UINT32 reg_bodp1_clk_gate_en: 1;    //     3
    UINT32 reg_de_clk_gate_en :  1;    //      4
    UINT32 reg_vdo0_clk_gate_en: 1;    //      5
    UINT32 reg_vdo1_clk_gate_en: 1;    //      6
    UINT32 reg_vdo2_clk_gate_en: 1;    //      7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_000C    crg_vdo03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_axi_sbus_n: 1;    //   2
    UINT32 reg_soft_rst_bodp0_n: 1;    //      3
    UINT32 reg_soft_rst_bodp1_n: 1;    //      4
    UINT32 reg_soft_rst_de_n  :  1;    //      5
    UINT32 reg_soft_rst_h_vdo_0_de_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_h_vdo_1_de_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_h_vdo_2_de_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_h_vdo_3_de_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_h_vdo_4_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_h_vdo_5_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_p_vdo_0_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_p_vdo_1_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_p_vdo_2_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_p_vdo_3_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_vdo0_n:  1;    //     16
    UINT32 reg_soft_rst_vdo1_n:  1;    //     17
    UINT32 reg_soft_rst_vdo2_n:  1;    //     18
    UINT32 reg_soft_rst_x_vdo_0_axi_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_x_vdo_0_axi_n: 1;    //  20
    UINT32 reg_soft_rst_x_vdo_1_axi_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_x_vdo_1_axi_n: 1;    //  22
    UINT32 reg_soft_rst_x_vdo_2_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_x_vdo_2_axi_n: 1;    //  24
    UINT32 reg_soft_rst_x_vdo_3_axi_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_x_vdo_3_axi_n: 1;    //  26
    UINT32 resvd00            :  5;    //  31:27 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0010    crg_vdo04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bodp0_clk_sel  :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_bodp1_clk_sel  :  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0014    crg_vdo05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0018    crg_vdo06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_001C    crg_vdo07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bodp0_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0020    crg_vdo08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bodp1_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0024    crg_vdo09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_de_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0028    crg_vdo10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vdo0_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_002C    crg_vdo11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vdo1_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x28_0030    crg_vdo12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vdo2_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VDO_CRG_VDO12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    CRG_VDO Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VDO_CRG_VDO00_O22A0_T          crg_vdo00  ;             // 0x28_0000
    SCRG_CTRL_VDO_CRG_VDO01_O22A0_T          crg_vdo01  ;             // 0x28_0004
    SCRG_CTRL_VDO_CRG_VDO02_O22A0_T          crg_vdo02  ;             // 0x28_0008
    SCRG_CTRL_VDO_CRG_VDO03_O22A0_T          crg_vdo03  ;             // 0x28_000C
    SCRG_CTRL_VDO_CRG_VDO04_O22A0_T          crg_vdo04  ;             // 0x28_0010
    SCRG_CTRL_VDO_CRG_VDO05_O22A0_T          crg_vdo05  ;             // 0x28_0014
    SCRG_CTRL_VDO_CRG_VDO06_O22A0_T          crg_vdo06  ;             // 0x28_0018
    SCRG_CTRL_VDO_CRG_VDO07_O22A0_T          crg_vdo07  ;             // 0x28_001C
    SCRG_CTRL_VDO_CRG_VDO08_O22A0_T          crg_vdo08  ;             // 0x28_0020
    SCRG_CTRL_VDO_CRG_VDO09_O22A0_T          crg_vdo09  ;             // 0x28_0024
    SCRG_CTRL_VDO_CRG_VDO10_O22A0_T          crg_vdo10  ;             // 0x28_0028
    SCRG_CTRL_VDO_CRG_VDO11_O22A0_T          crg_vdo11  ;             // 0x28_002C
    SCRG_CTRL_VDO_CRG_VDO12_O22A0_T          crg_vdo12  ;             // 0x28_0030
}SCRG_CTRL_VDO_REG_O22A0_T;
/* 13 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

