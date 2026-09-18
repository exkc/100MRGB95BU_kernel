#ifndef _SCRG_CTRL_VD0_REG_H_
#define _SCRG_CTRL_VD0_REG_H_

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
    0x50_0000    crg_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VD0_CRG_VD000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0004    crg_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VD0_CRG_VD001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0008    crg_vd002 ''
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
}SCRG_CTRL_VD0_CRG_VD002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_000C    crg_vd003 ''
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
    reg_soft_rst_p_vd0_0_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_vd0_1_axi_bnd_n: 1,    //  11
    reg_soft_rst_vvc_ed_n     :  1,    //     12
    reg_soft_rst_vvc_lcu_n    :  1,    //     13
    reg_soft_rst_vvc_n        :  1,    //     14
    reg_soft_rst_x_vd0_0_axi_bnd_n: 1,    //  15
    reg_soft_rst_x_vd0_0_axi_n:  1,    //     16
    reg_soft_rst_x_vd0_1_axi_bnd_n: 1,    //  17
    reg_soft_rst_x_vd0_1_axi_n:  1,    //     18
                              : 13;    //  31:19 reserved
}SCRG_CTRL_VD0_CRG_VD003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0010    crg_vd004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0014    crg_vd005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi0_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD005_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0018    crg_vd006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi1_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD006_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_001C    crg_vd007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD007_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0020    crg_vd008 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hevc_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD008_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0024    crg_vd009 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hevc_ed_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD009_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0028    crg_vd010 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hevc_lcu_clk_skip_ctrl:  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD010_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_002C    crg_vd011 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mem_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD011_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0030    crg_vd012 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vdec_order_clk_skip_ctrl: 9,    //  8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD012_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0034    crg_vd013 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vvc_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD013_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0038    crg_vd014 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vvc_ed_clk_skip_ctrl  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD014_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_003C    crg_vd015 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vvc_lcu_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD0_CRG_VD015_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD0_CRG_VD000_O22A0_T          crg_vd000  ;             // 0x50_0000
    SCRG_CTRL_VD0_CRG_VD001_O22A0_T          crg_vd001  ;             // 0x50_0004
    SCRG_CTRL_VD0_CRG_VD002_O22A0_T          crg_vd002  ;             // 0x50_0008
    SCRG_CTRL_VD0_CRG_VD003_O22A0_T          crg_vd003  ;             // 0x50_000C
    SCRG_CTRL_VD0_CRG_VD004_O22A0_T          crg_vd004  ;             // 0x50_0010
    SCRG_CTRL_VD0_CRG_VD005_O22A0_T          crg_vd005  ;             // 0x50_0014
    SCRG_CTRL_VD0_CRG_VD006_O22A0_T          crg_vd006  ;             // 0x50_0018
    SCRG_CTRL_VD0_CRG_VD007_O22A0_T          crg_vd007  ;             // 0x50_001C
    SCRG_CTRL_VD0_CRG_VD008_O22A0_T          crg_vd008  ;             // 0x50_0020
    SCRG_CTRL_VD0_CRG_VD009_O22A0_T          crg_vd009  ;             // 0x50_0024
    SCRG_CTRL_VD0_CRG_VD010_O22A0_T          crg_vd010  ;             // 0x50_0028
    SCRG_CTRL_VD0_CRG_VD011_O22A0_T          crg_vd011  ;             // 0x50_002C
    SCRG_CTRL_VD0_CRG_VD012_O22A0_T          crg_vd012  ;             // 0x50_0030
    SCRG_CTRL_VD0_CRG_VD013_O22A0_T          crg_vd013  ;             // 0x50_0034
    SCRG_CTRL_VD0_CRG_VD014_O22A0_T          crg_vd014  ;             // 0x50_0038
    SCRG_CTRL_VD0_CRG_VD015_O22A0_T          crg_vd015  ;             // 0x50_003C
}SCRG_CTRL_VD0_REG_O22A0_T;
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

#define SCRG_CTRL_VD0_CRG_VD000_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_VD0_CRG_VD001_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_VD0_CRG_VD002_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_VD0_CRG_VD003_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_VD0_CRG_VD004_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_VD0_CRG_VD005_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_VD0_CRG_VD006_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_VD0_CRG_VD007_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define SCRG_CTRL_VD0_CRG_VD008_O22A0_T_OFF                       (BASEADDRESS+0x0020)
#define SCRG_CTRL_VD0_CRG_VD009_O22A0_T_OFF                       (BASEADDRESS+0x0024)
#define SCRG_CTRL_VD0_CRG_VD010_O22A0_T_OFF                       (BASEADDRESS+0x0028)
#define SCRG_CTRL_VD0_CRG_VD011_O22A0_T_OFF                       (BASEADDRESS+0x002C)
#define SCRG_CTRL_VD0_CRG_VD012_O22A0_T_OFF                       (BASEADDRESS+0x0030)
#define SCRG_CTRL_VD0_CRG_VD013_O22A0_T_OFF                       (BASEADDRESS+0x0034)
#define SCRG_CTRL_VD0_CRG_VD014_O22A0_T_OFF                       (BASEADDRESS+0x0038)
#define SCRG_CTRL_VD0_CRG_VD015_O22A0_T_OFF                       (BASEADDRESS+0x003C)

/*-----------------------------------------------------------------------------------------
    0x50_0000    crg_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VD0_CRG_VD000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0004    crg_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VD0_CRG_VD001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0008    crg_vd002 ''
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
}SCRG_CTRL_VD0_CRG_VD002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_000C    crg_vd003 ''
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
    UINT32 reg_soft_rst_p_vd0_0_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_vd0_1_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_vvc_ed_n: 1;    //    12
    UINT32 reg_soft_rst_vvc_lcu_n: 1;    //   13
    UINT32 reg_soft_rst_vvc_n :  1;    //     14
    UINT32 reg_soft_rst_x_vd0_0_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_x_vd0_0_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_vd0_1_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_x_vd0_1_axi_n: 1;    //  18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_VD0_CRG_VD003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0010    crg_vd004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0014    crg_vd005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi0_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD005_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0018    crg_vd006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi1_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD006_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_001C    crg_vd007 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD007_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0020    crg_vd008 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hevc_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD008_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0024    crg_vd009 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hevc_ed_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD009_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0028    crg_vd010 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hevc_lcu_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD010_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_002C    crg_vd011 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_mem_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD011_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0030    crg_vd012 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vdec_order_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD012_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0034    crg_vd013 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vvc_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD013_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_0038    crg_vd014 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vvc_ed_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD014_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x50_003C    crg_vd015 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vvc_lcu_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD0_CRG_VD015_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD0_CRG_VD000_O22A0_T          crg_vd000  ;             // 0x50_0000
    SCRG_CTRL_VD0_CRG_VD001_O22A0_T          crg_vd001  ;             // 0x50_0004
    SCRG_CTRL_VD0_CRG_VD002_O22A0_T          crg_vd002  ;             // 0x50_0008
    SCRG_CTRL_VD0_CRG_VD003_O22A0_T          crg_vd003  ;             // 0x50_000C
    SCRG_CTRL_VD0_CRG_VD004_O22A0_T          crg_vd004  ;             // 0x50_0010
    SCRG_CTRL_VD0_CRG_VD005_O22A0_T          crg_vd005  ;             // 0x50_0014
    SCRG_CTRL_VD0_CRG_VD006_O22A0_T          crg_vd006  ;             // 0x50_0018
    SCRG_CTRL_VD0_CRG_VD007_O22A0_T          crg_vd007  ;             // 0x50_001C
    SCRG_CTRL_VD0_CRG_VD008_O22A0_T          crg_vd008  ;             // 0x50_0020
    SCRG_CTRL_VD0_CRG_VD009_O22A0_T          crg_vd009  ;             // 0x50_0024
    SCRG_CTRL_VD0_CRG_VD010_O22A0_T          crg_vd010  ;             // 0x50_0028
    SCRG_CTRL_VD0_CRG_VD011_O22A0_T          crg_vd011  ;             // 0x50_002C
    SCRG_CTRL_VD0_CRG_VD012_O22A0_T          crg_vd012  ;             // 0x50_0030
    SCRG_CTRL_VD0_CRG_VD013_O22A0_T          crg_vd013  ;             // 0x50_0034
    SCRG_CTRL_VD0_CRG_VD014_O22A0_T          crg_vd014  ;             // 0x50_0038
    SCRG_CTRL_VD0_CRG_VD015_O22A0_T          crg_vd015  ;             // 0x50_003C
}SCRG_CTRL_VD0_REG_O22A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

