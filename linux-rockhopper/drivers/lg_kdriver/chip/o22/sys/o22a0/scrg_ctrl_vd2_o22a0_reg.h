
#ifndef _SCRG_CTRL_VD2_REG_H_
#define _SCRG_CTRL_VD2_REG_H_

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
    0x56_0000    crg_vd200 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VD2_CRG_VD200_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0004    crg_vd201 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VD2_CRG_VD201_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0008    crg_vd202 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_av1_clk_gate_en       :  1,    //      1
    reg_axi0_clk_gate_en      :  1,    //      2
    reg_axi1_clk_gate_en      :  1,    //      3
    reg_bus_clk_gate_en       :  1,    //      4
    reg_mem_clk_gate_en       :  1,    //      5
    reg_msvc_396_clk_gate_en  :  1,    //      6
    reg_msvc_clk_gate_en      :  1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_VD2_CRG_VD202_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_000C    crg_vd203 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_av1_n        :  1,    //      1
    reg_soft_rst_axi0_n       :  1,    //      2
    reg_soft_rst_axi1_n       :  1,    //      3
    reg_soft_rst_bus_n        :  1,    //      4
    reg_soft_rst_mem_n        :  1,    //      5
    reg_soft_rst_msvc_396_n   :  1,    //      6
    reg_soft_rst_msvc_n       :  1,    //      7
    reg_soft_rst_p_vd2_0_axi_bnd_n: 1,    //   8
    reg_soft_rst_p_vd2_1_axi_bnd_n: 1,    //   9
    reg_soft_rst_x_vd2_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_x_vd2_0_axi_n:  1,    //     11
    reg_soft_rst_x_vd2_1_axi_bnd_n: 1,    //  12
    reg_soft_rst_x_vd2_1_axi_n:  1,    //     13
                              : 18;    //  31:14 reserved
}SCRG_CTRL_VD2_CRG_VD203_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0010    crg_vd204 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi0_clk_sel          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_msvc_clk_sel          :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_mem_clk_sel           :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}SCRG_CTRL_VD2_CRG_VD204_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0014    crg_vd205 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD2_CRG_VD205_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0018    crg_vd206 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_av1_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD2_CRG_VD206_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_001C    crg_vd207 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi0_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD2_CRG_VD207_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0020    crg_vd208 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi1_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD2_CRG_VD208_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0024    crg_vd209 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD2_CRG_VD209_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0028    crg_vd210 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mem_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD2_CRG_VD210_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_002C    crg_vd211 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_msvc_396_clk_skip_ctrl:  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD2_CRG_VD211_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0030    crg_vd212 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_msvc_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD2_CRG_VD212_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vd2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD2_CRG_VD200_O22A0_T          crg_vd200  ;             // 0x56_0000
    SCRG_CTRL_VD2_CRG_VD201_O22A0_T          crg_vd201  ;             // 0x56_0004
    SCRG_CTRL_VD2_CRG_VD202_O22A0_T          crg_vd202  ;             // 0x56_0008
    SCRG_CTRL_VD2_CRG_VD203_O22A0_T          crg_vd203  ;             // 0x56_000C
    SCRG_CTRL_VD2_CRG_VD204_O22A0_T          crg_vd204  ;             // 0x56_0010
    SCRG_CTRL_VD2_CRG_VD205_O22A0_T          crg_vd205  ;             // 0x56_0014
    SCRG_CTRL_VD2_CRG_VD206_O22A0_T          crg_vd206  ;             // 0x56_0018
    SCRG_CTRL_VD2_CRG_VD207_O22A0_T          crg_vd207  ;             // 0x56_001C
    SCRG_CTRL_VD2_CRG_VD208_O22A0_T          crg_vd208  ;             // 0x56_0020
    SCRG_CTRL_VD2_CRG_VD209_O22A0_T          crg_vd209  ;             // 0x56_0024
    SCRG_CTRL_VD2_CRG_VD210_O22A0_T          crg_vd210  ;             // 0x56_0028
    SCRG_CTRL_VD2_CRG_VD211_O22A0_T          crg_vd211  ;             // 0x56_002C
    SCRG_CTRL_VD2_CRG_VD212_O22A0_T          crg_vd212  ;             // 0x56_0030
}SCRG_CTRL_VD2_REG_O22A0_T;
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

#define SCRG_CTRL_VD2_CRG_VD200_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_VD2_CRG_VD201_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_VD2_CRG_VD202_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_VD2_CRG_VD203_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_VD2_CRG_VD204_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_VD2_CRG_VD205_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_VD2_CRG_VD206_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_VD2_CRG_VD207_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define SCRG_CTRL_VD2_CRG_VD208_O22A0_T_OFF                       (BASEADDRESS+0x0020)
#define SCRG_CTRL_VD2_CRG_VD209_O22A0_T_OFF                       (BASEADDRESS+0x0024)
#define SCRG_CTRL_VD2_CRG_VD210_O22A0_T_OFF                       (BASEADDRESS+0x0028)
#define SCRG_CTRL_VD2_CRG_VD211_O22A0_T_OFF                       (BASEADDRESS+0x002C)
#define SCRG_CTRL_VD2_CRG_VD212_O22A0_T_OFF                       (BASEADDRESS+0x0030)

/*-----------------------------------------------------------------------------------------
    0x56_0000    crg_vd200 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VD2_CRG_VD200_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0004    crg_vd201 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VD2_CRG_VD201_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0008    crg_vd202 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_av1_clk_gate_en:  1;    //      1
    UINT32 reg_axi0_clk_gate_en: 1;    //      2
    UINT32 reg_axi1_clk_gate_en: 1;    //      3
    UINT32 reg_bus_clk_gate_en:  1;    //      4
    UINT32 reg_mem_clk_gate_en:  1;    //      5
    UINT32 reg_msvc_396_clk_gate_en: 1;    //  6
    UINT32 reg_msvc_clk_gate_en: 1;    //      7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_VD2_CRG_VD202_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_000C    crg_vd203 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_av1_n :  1;    //      1
    UINT32 reg_soft_rst_axi0_n:  1;    //      2
    UINT32 reg_soft_rst_axi1_n:  1;    //      3
    UINT32 reg_soft_rst_bus_n :  1;    //      4
    UINT32 reg_soft_rst_mem_n :  1;    //      5
    UINT32 reg_soft_rst_msvc_396_n: 1;    //   6
    UINT32 reg_soft_rst_msvc_n:  1;    //      7
    UINT32 reg_soft_rst_p_vd2_0_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_vd2_1_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_vd2_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_x_vd2_0_axi_n: 1;    //  11
    UINT32 reg_soft_rst_x_vd2_1_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_x_vd2_1_axi_n: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}SCRG_CTRL_VD2_CRG_VD203_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0010    crg_vd204 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi0_clk_sel   :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_msvc_clk_sel   :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_mem_clk_sel    :  2;    //   9: 8
    UINT32 resvd02            : 22;    //  31:10 reserved
    };
}SCRG_CTRL_VD2_CRG_VD204_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0014    crg_vd205 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD2_CRG_VD205_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0018    crg_vd206 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_av1_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD2_CRG_VD206_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_001C    crg_vd207 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi0_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD2_CRG_VD207_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0020    crg_vd208 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi1_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD2_CRG_VD208_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0024    crg_vd209 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD2_CRG_VD209_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0028    crg_vd210 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_mem_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD2_CRG_VD210_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_002C    crg_vd211 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_msvc_396_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD2_CRG_VD211_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x56_0030    crg_vd212 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_msvc_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD2_CRG_VD212_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vd2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD2_CRG_VD200_O22A0_T          crg_vd200  ;             // 0x56_0000
    SCRG_CTRL_VD2_CRG_VD201_O22A0_T          crg_vd201  ;             // 0x56_0004
    SCRG_CTRL_VD2_CRG_VD202_O22A0_T          crg_vd202  ;             // 0x56_0008
    SCRG_CTRL_VD2_CRG_VD203_O22A0_T          crg_vd203  ;             // 0x56_000C
    SCRG_CTRL_VD2_CRG_VD204_O22A0_T          crg_vd204  ;             // 0x56_0010
    SCRG_CTRL_VD2_CRG_VD205_O22A0_T          crg_vd205  ;             // 0x56_0014
    SCRG_CTRL_VD2_CRG_VD206_O22A0_T          crg_vd206  ;             // 0x56_0018
    SCRG_CTRL_VD2_CRG_VD207_O22A0_T          crg_vd207  ;             // 0x56_001C
    SCRG_CTRL_VD2_CRG_VD208_O22A0_T          crg_vd208  ;             // 0x56_0020
    SCRG_CTRL_VD2_CRG_VD209_O22A0_T          crg_vd209  ;             // 0x56_0024
    SCRG_CTRL_VD2_CRG_VD210_O22A0_T          crg_vd210  ;             // 0x56_0028
    SCRG_CTRL_VD2_CRG_VD211_O22A0_T          crg_vd211  ;             // 0x56_002C
    SCRG_CTRL_VD2_CRG_VD212_O22A0_T          crg_vd212  ;             // 0x56_0030
}SCRG_CTRL_VD2_REG_O22A0_T;
/* 13 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

