#ifndef _SCRG_CTRL_DSC_REG_O26A0_H_
#define _SCRG_CTRL_DSC_REG_O26A0_H_

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
    0xCC51_0000    crg_dsc000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DSC_CRG_DSC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC51_0004    crg_dsc001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DSC_CRG_DSC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC51_0008    crg_dsc002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_f_hdmi_0__hdmi_rx_clk_gate_en: 1,    //  0
    reg_adaprx_f_hdmi_1__hdmi_rx_clk_gate_en: 1,    //  1
    reg_adaprx_f_hdmi_2__hdmi_rx_clk_gate_en: 1,    //  2
    reg_adaprx_f_hdmi_3__hdmi_rx_clk_gate_en: 1,    //  3
    reg_adaptx_f_dsc_0__dsc_cvi_clk_gate_en: 1,    //  4
    reg_apb_clk_gate_en       :  1,    //      5
    reg_dsc_clk_gate_en       :  1,    //      6
    reg_dsc_cvi_clk_gate_en   :  1,    //      7
    reg_hdmi_rx_clk_gate_en   :  1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DSC_CRG_DSC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC51_000C    crg_dsc003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_clk_n    :  1,    //      0
    reg_soft_rst_dsc_clk_apb_n:  1,    //      1
    reg_soft_rst_dsc_clk_n    :  1,    //      2
    reg_soft_rst_dsc_cvi_clk_n:  1,    //      3
    reg_soft_rst_f_dsc_0_dsc_cvi_clk_bnd_n: 1,    //  4
    reg_soft_rst_f_hdmi_0_hdmi_rx_clk_bnd_n: 1,    //  5
    reg_soft_rst_f_hdmi_1_hdmi_rx_clk_bnd_n: 1,    //  6
    reg_soft_rst_f_hdmi_2_hdmi_rx_clk_bnd_n: 1,    //  7
    reg_soft_rst_f_hdmi_3_hdmi_rx_clk_bnd_n: 1,    //  8
    reg_soft_rst_hdmi_rx_clk_n:  1,    //      9
                              : 22;    //  31:10 reserved
}SCRG_CTRL_DSC_CRG_DSC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC51_0010    crg_dsc004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc_clk_sel           :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_dsc_cvi_clk_sel       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_hdmi_rx_clk_sel       :  2,    //   9: 8
                              : 22;    //  31:10 reserved
}SCRG_CTRL_DSC_CRG_DSC004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DSC_CRG_DSC000_O26A0_T    crg_dsc000;             // 0xCC51_0000
    SCRG_CTRL_DSC_CRG_DSC001_O26A0_T    crg_dsc001;             // 0xCC51_0004
    SCRG_CTRL_DSC_CRG_DSC002_O26A0_T    crg_dsc002;             // 0xCC51_0008
    SCRG_CTRL_DSC_CRG_DSC003_O26A0_T    crg_dsc003;             // 0xCC51_000C
    SCRG_CTRL_DSC_CRG_DSC004_O26A0_T    crg_dsc004;             // 0xCC51_0010
}SCRG_CTRL_DSC_REG_O26A0_T;
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

#define SCRG_CTRL_DSC_CRG_DSC000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_DSC_CRG_DSC001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_DSC_CRG_DSC002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_DSC_CRG_DSC003_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_DSC_CRG_DSC004_O26A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC51_0000    crg_dsc000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DSC_CRG_DSC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC51_0004    crg_dsc001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DSC_CRG_DSC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC51_0008    crg_dsc002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_f_hdmi_0__hdmi_rx_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_f_hdmi_1__hdmi_rx_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_f_hdmi_2__hdmi_rx_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_f_hdmi_3__hdmi_rx_clk_gate_en: 1;    //  3
    UINT32 reg_adaptx_f_dsc_0__dsc_cvi_clk_gate_en: 1;    //  4
    UINT32 reg_apb_clk_gate_en:  1;    //      5
    UINT32 reg_dsc_clk_gate_en:  1;    //      6
    UINT32 reg_dsc_cvi_clk_gate_en: 1;    //   7
    UINT32 reg_hdmi_rx_clk_gate_en: 1;    //   8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DSC_CRG_DSC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC51_000C    crg_dsc003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_clk_n: 1;    //    0
    UINT32 reg_soft_rst_dsc_clk_apb_n: 1;    //  1
    UINT32 reg_soft_rst_dsc_clk_n: 1;    //    2
    UINT32 reg_soft_rst_dsc_cvi_clk_n: 1;    //  3
    UINT32 reg_soft_rst_f_dsc_0_dsc_cvi_clk_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_f_hdmi_0_hdmi_rx_clk_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_f_hdmi_1_hdmi_rx_clk_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_f_hdmi_2_hdmi_rx_clk_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_f_hdmi_3_hdmi_rx_clk_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_hdmi_rx_clk_n: 1;    //  9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}SCRG_CTRL_DSC_CRG_DSC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC51_0010    crg_dsc004 ''
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
}SCRG_CTRL_DSC_CRG_DSC004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DSC_CRG_DSC000_O26A0_T    crg_dsc000;             // 0xCC51_0000
    SCRG_CTRL_DSC_CRG_DSC001_O26A0_T    crg_dsc001;             // 0xCC51_0004
    SCRG_CTRL_DSC_CRG_DSC002_O26A0_T    crg_dsc002;             // 0xCC51_0008
    SCRG_CTRL_DSC_CRG_DSC003_O26A0_T    crg_dsc003;             // 0xCC51_000C
    SCRG_CTRL_DSC_CRG_DSC004_O26A0_T    crg_dsc004;             // 0xCC51_0010
}SCRG_CTRL_DSC_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_DSC_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

