#ifndef _SCRG_CTRL_VD1_REG_H_
#define _SCRG_CTRL_VD1_REG_H_

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
    0x53_0000    crg_vd100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VD1_CRG_VD100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0004    crg_vd101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VD1_CRG_VD101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0008    crg_vd102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi0_clk_gate_en      :  1,    //      1
    reg_axi1_clk_gate_en      :  1,    //      2
    reg_bus_clk_gate_en       :  1,    //      3
    reg_hevc_clk_gate_en      :  1,    //      4
    reg_hevc_ed_clk_gate_en   :  1,    //      5
    reg_hevc_lcu_clk_gate_en  :  1,    //      6
    reg_mem_clk_gate_en       :  1,    //      7
    reg_vdec_order_clk_gate_en:  1,    //      8
    reg_vvc_clk_gate_en       :  1,    //      9
    reg_vvc_ed_clk_gate_en    :  1,    //     10
    reg_vvc_lcu_clk_gate_en   :  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_VD1_CRG_VD102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_000C    crg_vd103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi0_n       :  1,    //      1
    reg_soft_rst_axi1_n       :  1,    //      2
    reg_soft_rst_bus_n        :  1,    //      3
    reg_soft_rst_f_vd0_0_hevc_bnd_n: 1,    //  4
    reg_soft_rst_f_vd1_0_hevc_bnd_n: 1,    //  5
    reg_soft_rst_hevc_ed_n    :  1,    //      6
    reg_soft_rst_hevc_lcu_n   :  1,    //      7
    reg_soft_rst_hevc_n       :  1,    //      8
    reg_soft_rst_mem_n        :  1,    //      9
    reg_soft_rst_p_vd1_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_vd1_1_axi_bnd_n: 1,    //  11
    reg_soft_rst_vvc_ed_n     :  1,    //     12
    reg_soft_rst_vvc_lcu_n    :  1,    //     13
    reg_soft_rst_vvc_n        :  1,    //     14
    reg_soft_rst_x_vd1_0_axi_bnd_n: 1,    //  15
    reg_soft_rst_x_vd1_0_axi_n:  1,    //     16
    reg_soft_rst_x_vd1_1_axi_bnd_n: 1,    //  17
    reg_soft_rst_x_vd1_1_axi_n:  1,    //     18
                              : 13;    //  31:19 reserved
}SCRG_CTRL_VD1_CRG_VD103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0010    crg_vd104 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0014    crg_vd105 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi0_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD105_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0018    crg_vd106 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi1_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD106_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_001C    crg_vd107 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD107_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0020    crg_vd108 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hevc_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD108_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0024    crg_vd109 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hevc_ed_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD109_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0028    crg_vd110 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hevc_lcu_clk_skip_ctrl:  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD110_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_002C    crg_vd111 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mem_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD111_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0030    crg_vd112 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vdec_order_clk_skip_ctrl: 9,    //  8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD112_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0034    crg_vd113 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vvc_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD113_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0038    crg_vd114 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vvc_ed_clk_skip_ctrl  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD114_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_003C    crg_vd115 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vvc_lcu_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD1_CRG_VD115_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD1_CRG_VD100_O22A0_T          crg_vd100  ;             // 0x53_0000
    SCRG_CTRL_VD1_CRG_VD101_O22A0_T          crg_vd101  ;             // 0x53_0004
    SCRG_CTRL_VD1_CRG_VD102_O22A0_T          crg_vd102  ;             // 0x53_0008
    SCRG_CTRL_VD1_CRG_VD103_O22A0_T          crg_vd103  ;             // 0x53_000C
    SCRG_CTRL_VD1_CRG_VD104_O22A0_T          crg_vd104  ;             // 0x53_0010
    SCRG_CTRL_VD1_CRG_VD105_O22A0_T          crg_vd105  ;             // 0x53_0014
    SCRG_CTRL_VD1_CRG_VD106_O22A0_T          crg_vd106  ;             // 0x53_0018
    SCRG_CTRL_VD1_CRG_VD107_O22A0_T          crg_vd107  ;             // 0x53_001C
    SCRG_CTRL_VD1_CRG_VD108_O22A0_T          crg_vd108  ;             // 0x53_0020
    SCRG_CTRL_VD1_CRG_VD109_O22A0_T          crg_vd109  ;             // 0x53_0024
    SCRG_CTRL_VD1_CRG_VD110_O22A0_T          crg_vd110  ;             // 0x53_0028
    SCRG_CTRL_VD1_CRG_VD111_O22A0_T          crg_vd111  ;             // 0x53_002C
    SCRG_CTRL_VD1_CRG_VD112_O22A0_T          crg_vd112  ;             // 0x53_0030
    SCRG_CTRL_VD1_CRG_VD113_O22A0_T          crg_vd113  ;             // 0x53_0034
    SCRG_CTRL_VD1_CRG_VD114_O22A0_T          crg_vd114  ;             // 0x53_0038
    SCRG_CTRL_VD1_CRG_VD115_O22A0_T          crg_vd115  ;             // 0x53_003C
}SCRG_CTRL_VD1_REG_O22A0_T;
/* 16 regs */

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

#define SCRG_CTRL_VD1_CRG_VD100_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_VD1_CRG_VD101_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_VD1_CRG_VD102_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_VD1_CRG_VD103_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_VD1_CRG_VD104_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_VD1_CRG_VD105_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_VD1_CRG_VD106_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_VD1_CRG_VD107_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define SCRG_CTRL_VD1_CRG_VD108_O22A0_T_OFF                       (BASEADDRESS+0x0020)
#define SCRG_CTRL_VD1_CRG_VD109_O22A0_T_OFF                       (BASEADDRESS+0x0024)
#define SCRG_CTRL_VD1_CRG_VD110_O22A0_T_OFF                       (BASEADDRESS+0x0028)
#define SCRG_CTRL_VD1_CRG_VD111_O22A0_T_OFF                       (BASEADDRESS+0x002C)
#define SCRG_CTRL_VD1_CRG_VD112_O22A0_T_OFF                       (BASEADDRESS+0x0030)
#define SCRG_CTRL_VD1_CRG_VD113_O22A0_T_OFF                       (BASEADDRESS+0x0034)
#define SCRG_CTRL_VD1_CRG_VD114_O22A0_T_OFF                       (BASEADDRESS+0x0038)
#define SCRG_CTRL_VD1_CRG_VD115_O22A0_T_OFF                       (BASEADDRESS+0x003C)

/*-----------------------------------------------------------------------------------------
    0x53_0000    crg_vd100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VD1_CRG_VD100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0004    crg_vd101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VD1_CRG_VD101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0008    crg_vd102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi0_clk_gate_en: 1;    //      1
    UINT32 reg_axi1_clk_gate_en: 1;    //      2
    UINT32 reg_bus_clk_gate_en:  1;    //      3
    UINT32 reg_hevc_clk_gate_en: 1;    //      4
    UINT32 reg_hevc_ed_clk_gate_en: 1;    //   5
    UINT32 reg_hevc_lcu_clk_gate_en: 1;    //  6
    UINT32 reg_mem_clk_gate_en:  1;    //      7
    UINT32 reg_vdec_order_clk_gate_en: 1;    //  8
    UINT32 reg_vvc_clk_gate_en:  1;    //      9
    UINT32 reg_vvc_ed_clk_gate_en: 1;    //   10
    UINT32 reg_vvc_lcu_clk_gate_en: 1;    //  11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_VD1_CRG_VD102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_000C    crg_vd103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi0_n:  1;    //      1
    UINT32 reg_soft_rst_axi1_n:  1;    //      2
    UINT32 reg_soft_rst_bus_n :  1;    //      3
    UINT32 reg_soft_rst_f_vd0_0_hevc_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_vd1_0_hevc_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_hevc_ed_n: 1;    //    6
    UINT32 reg_soft_rst_hevc_lcu_n: 1;    //   7
    UINT32 reg_soft_rst_hevc_n:  1;    //      8
    UINT32 reg_soft_rst_mem_n :  1;    //      9
    UINT32 reg_soft_rst_p_vd1_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_vd1_1_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_vvc_ed_n: 1;    //    12
    UINT32 reg_soft_rst_vvc_lcu_n: 1;    //   13
    UINT32 reg_soft_rst_vvc_n :  1;    //     14
    UINT32 reg_soft_rst_x_vd1_0_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_x_vd1_0_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_vd1_1_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_x_vd1_1_axi_n: 1;    //  18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_VD1_CRG_VD103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0010    crg_vd104 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0014    crg_vd105 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi0_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD105_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0018    crg_vd106 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi1_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD106_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_001C    crg_vd107 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD107_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0020    crg_vd108 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hevc_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD108_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0024    crg_vd109 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hevc_ed_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD109_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0028    crg_vd110 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hevc_lcu_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD110_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_002C    crg_vd111 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_mem_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD111_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0030    crg_vd112 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vdec_order_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD112_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0034    crg_vd113 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vvc_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD113_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_0038    crg_vd114 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vvc_ed_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD114_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x53_003C    crg_vd115 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vvc_lcu_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD1_CRG_VD115_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vd1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD1_CRG_VD100_O22A0_T          crg_vd100  ;             // 0x53_0000
    SCRG_CTRL_VD1_CRG_VD101_O22A0_T          crg_vd101  ;             // 0x53_0004
    SCRG_CTRL_VD1_CRG_VD102_O22A0_T          crg_vd102  ;             // 0x53_0008
    SCRG_CTRL_VD1_CRG_VD103_O22A0_T          crg_vd103  ;             // 0x53_000C
    SCRG_CTRL_VD1_CRG_VD104_O22A0_T          crg_vd104  ;             // 0x53_0010
    SCRG_CTRL_VD1_CRG_VD105_O22A0_T          crg_vd105  ;             // 0x53_0014
    SCRG_CTRL_VD1_CRG_VD106_O22A0_T          crg_vd106  ;             // 0x53_0018
    SCRG_CTRL_VD1_CRG_VD107_O22A0_T          crg_vd107  ;             // 0x53_001C
    SCRG_CTRL_VD1_CRG_VD108_O22A0_T          crg_vd108  ;             // 0x53_0020
    SCRG_CTRL_VD1_CRG_VD109_O22A0_T          crg_vd109  ;             // 0x53_0024
    SCRG_CTRL_VD1_CRG_VD110_O22A0_T          crg_vd110  ;             // 0x53_0028
    SCRG_CTRL_VD1_CRG_VD111_O22A0_T          crg_vd111  ;             // 0x53_002C
    SCRG_CTRL_VD1_CRG_VD112_O22A0_T          crg_vd112  ;             // 0x53_0030
    SCRG_CTRL_VD1_CRG_VD113_O22A0_T          crg_vd113  ;             // 0x53_0034
    SCRG_CTRL_VD1_CRG_VD114_O22A0_T          crg_vd114  ;             // 0x53_0038
    SCRG_CTRL_VD1_CRG_VD115_O22A0_T          crg_vd115  ;             // 0x53_003C
}SCRG_CTRL_VD1_REG_O22A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

