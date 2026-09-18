#ifndef _SCRG_CTRL_DSC_REG_O24A0_H_
#define _SCRG_CTRL_DSC_REG_O24A0_H_

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
    0xC8CF_0000    crg_dsc0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DSC_CRG_DSC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8CF_0004    crg_dsc1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DSC_CRG_DSC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8CF_0008    crg_dsc2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_cvi_594_clk_gate_en   :  1,    //      1
    reg_dsc_clk_gate_en       :  1,    //      2
    reg_dsc_cvi_clk_gate_en   :  1,    //      3
    reg_hdmi_rx_clk_gate_en   :  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_DSC_CRG_DSC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8CF_000C    crg_dsc3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_clk_n    :  1,    //      0
    reg_soft_rst_cvi_594_clk_apb_n: 1,    //   1
    reg_soft_rst_cvi_594_clk_n:  1,    //      2
    reg_soft_rst_dsc_clk_apb_n:  1,    //      3
    reg_soft_rst_dsc_clk_n    :  1,    //      4
    reg_soft_rst_dsc_cvi_clk_n:  1,    //      5
    reg_soft_rst_f_dsc_0_dsc_cvi_clk_bnd_n: 1,    //  6
    reg_soft_rst_f_dsc_1_cvi_594_clk_bnd_n: 1,    //  7
    reg_soft_rst_f_hdmi_0_hdmi_rx_clk_bnd_n: 1,    //  8
    reg_soft_rst_f_hdmi_1_hdmi_rx_clk_bnd_n: 1,    //  9
    reg_soft_rst_f_hdmi_2_hdmi_rx_clk_bnd_n: 1,    //  10
    reg_soft_rst_f_hdmi_3_hdmi_rx_clk_bnd_n: 1,    //  11
    reg_soft_rst_hdmi_rx_clk_n:  1,    //     12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_DSC_CRG_DSC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8CF_0010    crg_dsc4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc_clk_sel           :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_dsc_cvi_clk_sel       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_hdmi_rx_clk_sel       :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}SCRG_CTRL_DSC_CRG_DSC4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DSC_CRG_DSC0_O24A0_T     crg_dsc0   ;             // 0xC8CF_0000
    SCRG_CTRL_DSC_CRG_DSC1_O24A0_T     crg_dsc1   ;             // 0xC8CF_0004
    SCRG_CTRL_DSC_CRG_DSC2_O24A0_T     crg_dsc2   ;             // 0xC8CF_0008
    SCRG_CTRL_DSC_CRG_DSC3_O24A0_T     crg_dsc3   ;             // 0xC8CF_000C
    SCRG_CTRL_DSC_CRG_DSC4_O24A0_T     crg_dsc4   ;             // 0xC8CF_0010
}SCRG_CTRL_DSC_REG_O24A0_T;
/* 5 regs */

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

#define SCRG_CTRL_DSC_CRG_DSC0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_DSC_CRG_DSC1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_DSC_CRG_DSC2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_DSC_CRG_DSC3_O24A0_T_OFF                  (BASEADDRESS+0x000C)
#define SCRG_CTRL_DSC_CRG_DSC4_O24A0_T_OFF                  (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xC8CF_0000    crg_dsc0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DSC_CRG_DSC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8CF_0004    crg_dsc1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DSC_CRG_DSC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8CF_0008    crg_dsc2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_cvi_594_clk_gate_en: 1;    //   1
    UINT32 reg_dsc_clk_gate_en:  1;    //      2
    UINT32 reg_dsc_cvi_clk_gate_en: 1;    //   3
    UINT32 reg_hdmi_rx_clk_gate_en: 1;    //   4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_DSC_CRG_DSC2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8CF_000C    crg_dsc3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_clk_n: 1;    //    0
    UINT32 reg_soft_rst_cvi_594_clk_apb_n: 1;    //  1
    UINT32 reg_soft_rst_cvi_594_clk_n: 1;    //  2
    UINT32 reg_soft_rst_dsc_clk_apb_n: 1;    //  3
    UINT32 reg_soft_rst_dsc_clk_n: 1;    //    4
    UINT32 reg_soft_rst_dsc_cvi_clk_n: 1;    //  5
    UINT32 reg_soft_rst_f_dsc_0_dsc_cvi_clk_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_dsc_1_cvi_594_clk_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_hdmi_0_hdmi_rx_clk_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_hdmi_1_hdmi_rx_clk_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_hdmi_2_hdmi_rx_clk_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_hdmi_3_hdmi_rx_clk_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_hdmi_rx_clk_n: 1;    //  12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_DSC_CRG_DSC3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8CF_0010    crg_dsc4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dsc_clk_sel    :  2;    //   1: 0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_dsc_cvi_clk_sel:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_hdmi_rx_clk_sel:  2;    //   9: 8
    UINT32 resvd02            : 22;    //  31:10 reserved
    };
}SCRG_CTRL_DSC_CRG_DSC4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DSC_CRG_DSC0_O24A0_T     crg_dsc0   ;             // 0xC8CF_0000
    SCRG_CTRL_DSC_CRG_DSC1_O24A0_T     crg_dsc1   ;             // 0xC8CF_0004
    SCRG_CTRL_DSC_CRG_DSC2_O24A0_T     crg_dsc2   ;             // 0xC8CF_0008
    SCRG_CTRL_DSC_CRG_DSC3_O24A0_T     crg_dsc3   ;             // 0xC8CF_000C
    SCRG_CTRL_DSC_CRG_DSC4_O24A0_T     crg_dsc4   ;             // 0xC8CF_0010
}SCRG_CTRL_DSC_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_DSC_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

