#ifndef _SCRG_CTRL_DSC_REG_H_
#define _SCRG_CTRL_DSC_REG_H_

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
    0x10_0000    crg_dsc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DSC_CRG_DSC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_0004    crg_dsc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DSC_CRG_DSC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_0008    crg_dsc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_cvi_594_clk_gate_en   :  1,    //      1
    reg_dsc_clk_gate_en       :  1,    //      2
    reg_dsc_cvi_clk_gate_en   :  1,    //      3
    reg_hdmi_rx_clk_selected_gate_en: 1,    //  4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_DSC_CRG_DSC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_000C    crg_dsc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_apb_clk_resetn   :  1,    //      0
    reg_soft_cvi_594_clk_apb_resetn: 1,    //  1
    reg_soft_cvi_594_clk_resetn: 1,    //      2
    reg_soft_dsc_clk_apb_resetn: 1,    //      3
    reg_soft_dsc_clk_resetn   :  1,    //      4
    reg_soft_dsc_cvi_clk_resetn: 1,    //      5
    reg_soft_hdmi_rx_clk_selected_resetn: 1,    //  6
    reg_soft_rst_f_dsc_1_cvi_594_clk_bnd_n: 1,    //  7
    reg_soft_rst_f_dsc_2_cvi_594_clk_bnd_n: 1,    //  8
    reg_soft_rst_f_hdmi_1_hdmi_rx_clk_bnd_n: 1,    //  9
    reg_soft_rst_f_hdmi_2_hdmi_rx_clk_bnd_n: 1,    //  10
    reg_soft_rst_f_hdmi_3_hdmi_rx_clk_bnd_n: 1,    //  11
    reg_soft_rst_f_hdmi_4_hdmi_rx_clk_bnd_n: 1,    //  12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_DSC_CRG_DSC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_0010    crg_dsc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi_594_clk_sel       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_dsc_cvi_clk_sel       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_dsc_clk_sel           :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_hdmi_rx_clk_sel       :  2,    //  13:12
                              : 18;    //  31:14 reserved
}SCRG_CTRL_DSC_CRG_DSC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_0014    crg_dsc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DSC_CRG_DSC05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_0018    crg_dsc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DSC_CRG_DSC06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_dsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DSC_CRG_DSC00_O22A0_T          crg_dsc00  ;             // 0x10_0000
    SCRG_CTRL_DSC_CRG_DSC01_O22A0_T          crg_dsc01  ;             // 0x10_0004
    SCRG_CTRL_DSC_CRG_DSC02_O22A0_T          crg_dsc02  ;             // 0x10_0008
    SCRG_CTRL_DSC_CRG_DSC03_O22A0_T          crg_dsc03  ;             // 0x10_000C
    SCRG_CTRL_DSC_CRG_DSC04_O22A0_T          crg_dsc04  ;             // 0x10_0010
    SCRG_CTRL_DSC_CRG_DSC05_O22A0_T          crg_dsc05  ;             // 0x10_0014
    SCRG_CTRL_DSC_CRG_DSC06_O22A0_T          crg_dsc06  ;             // 0x10_0018
}SCRG_CTRL_DSC_REG_O22A0_T;
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

#define SCRG_CTRL_DSC_CRG_DSC00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_DSC_CRG_DSC01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_DSC_CRG_DSC02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_DSC_CRG_DSC03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_DSC_CRG_DSC04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_DSC_CRG_DSC05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_DSC_CRG_DSC06_O22A0_T_OFF                       (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x10_0000    crg_dsc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DSC_CRG_DSC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_0004    crg_dsc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DSC_CRG_DSC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_0008    crg_dsc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_cvi_594_clk_gate_en: 1;    //   1
    UINT32 reg_dsc_clk_gate_en:  1;    //      2
    UINT32 reg_dsc_cvi_clk_gate_en: 1;    //   3
    UINT32 reg_hdmi_rx_clk_selected_gate_en: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_DSC_CRG_DSC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_000C    crg_dsc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_apb_clk_resetn: 1;    //   0
    UINT32 reg_soft_cvi_594_clk_apb_resetn: 1;    //  1
    UINT32 reg_soft_cvi_594_clk_resetn: 1;    //  2
    UINT32 reg_soft_dsc_clk_apb_resetn: 1;    //  3
    UINT32 reg_soft_dsc_clk_resetn: 1;    //   4
    UINT32 reg_soft_dsc_cvi_clk_resetn: 1;    //  5
    UINT32 reg_soft_hdmi_rx_clk_selected_resetn: 1;    //  6
    UINT32 reg_soft_rst_f_dsc_1_cvi_594_clk_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_dsc_2_cvi_594_clk_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_hdmi_1_hdmi_rx_clk_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_hdmi_2_hdmi_rx_clk_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_hdmi_3_hdmi_rx_clk_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_hdmi_4_hdmi_rx_clk_bnd_n: 1;    //  12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_DSC_CRG_DSC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_0010    crg_dsc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvi_594_clk_sel:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_dsc_cvi_clk_sel:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_dsc_clk_sel    :  2;    //   9: 8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_hdmi_rx_clk_sel:  2;    //  13:12
    UINT32 resvd03            : 18;    //  31:14 reserved
    };
}SCRG_CTRL_DSC_CRG_DSC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_0014    crg_dsc05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DSC_CRG_DSC05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x10_0018    crg_dsc06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dsc_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DSC_CRG_DSC06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_dsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DSC_CRG_DSC00_O22A0_T          crg_dsc00  ;             // 0x10_0000
    SCRG_CTRL_DSC_CRG_DSC01_O22A0_T          crg_dsc01  ;             // 0x10_0004
    SCRG_CTRL_DSC_CRG_DSC02_O22A0_T          crg_dsc02  ;             // 0x10_0008
    SCRG_CTRL_DSC_CRG_DSC03_O22A0_T          crg_dsc03  ;             // 0x10_000C
    SCRG_CTRL_DSC_CRG_DSC04_O22A0_T          crg_dsc04  ;             // 0x10_0010
    SCRG_CTRL_DSC_CRG_DSC05_O22A0_T          crg_dsc05  ;             // 0x10_0014
    SCRG_CTRL_DSC_CRG_DSC06_O22A0_T          crg_dsc06  ;             // 0x10_0018
}SCRG_CTRL_DSC_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

