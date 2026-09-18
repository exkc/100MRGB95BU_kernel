#ifndef _BCRG_CTRL_CVI_M23A0_REG_H_
#define _BCRG_CTRL_CVI_M23A0_REG_H_

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
    0xCC75_1000    crg_bnd_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_CVI_CRG_BND_CVI00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_1004    crg_bnd_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_CVI_CRG_BND_CVI01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_1008    crg_bnd_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_hdmi1_mclk_gate_en:  1,    //      0
    reg_aud_hdmi2_mclk_gate_en:  1,    //      1
    reg_aud_hdmi3_mclk_gate_en:  1,    //      2
    reg_aud_hdmi4_mclk_gate_en:  1,    //      3
    reg_earc_extern_aud_clk_gate_en: 1,    //  4
                              : 27;    //   31:5 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_100C    crg_bnd_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_cvi_clk_gate_en: 1,    //      0
    reg_apb_ipw_emmc_clk_gate_en: 1,    //     1
    reg_apb_ipw_hdmi_clk_gate_en: 1,    //     2
    reg_apb_ipw_imx_clk_gate_en: 1,    //      3
    reg_apb_ipw_sb_cvd_clk_gate_en: 1,    //   4
    reg_apb_ipw_sb_emu_clk_gate_en: 1,    //   5
    reg_apb_ipw_usb_hs1_clk_gate_en: 1,    //  6
    reg_apb_ipw_vdo_clk_gate_en: 1,    //      7
                              : 24;    //   31:8 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_1010    crg_bnd_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_earc_rstn        :  1,    //      0
    reg_soft_phy1_rstn        :  1,    //      1
    reg_soft_phy2_rstn        :  1,    //      2
    reg_soft_rst_axi_brdg_dbb_0_n: 1,    //    3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_1014    crg_bnd_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_cvi_n:  1,    //      0
    reg_soft_rst_apb_ipw_emmc_n: 1,    //      1
    reg_soft_rst_apb_ipw_hdmi_n: 1,    //      2
    reg_soft_rst_apb_ipw_imx_n:  1,    //      3
    reg_soft_rst_apb_ipw_sb_cvd_n: 1,    //    4
    reg_soft_rst_apb_ipw_sb_emu_n: 1,    //    5
    reg_soft_rst_apb_ipw_usb_hs1_n: 1,    //   6
    reg_soft_rst_apb_ipw_vdo_n:  1,    //      7
                              : 24;    //   31:8 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_1018    crg_bnd_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy_i2c_clk_sel       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_earc_extern_aud_clk_sel: 3,    //   6: 4
                              : 25;    //   31:7 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CVI_CRG_BND_CVI00_M23A0_T    crg_bnd_cvi00;       // 0xCC75_1000
    BCRG_CTRL_CVI_CRG_BND_CVI01_M23A0_T    crg_bnd_cvi01;       // 0xCC75_1004
    BCRG_CTRL_CVI_CRG_BND_CVI02_M23A0_T    crg_bnd_cvi02;       // 0xCC75_1008
    BCRG_CTRL_CVI_CRG_BND_CVI03_M23A0_T    crg_bnd_cvi03;       // 0xCC75_100C
    BCRG_CTRL_CVI_CRG_BND_CVI04_M23A0_T    crg_bnd_cvi04;       // 0xCC75_1010
    BCRG_CTRL_CVI_CRG_BND_CVI05_M23A0_T    crg_bnd_cvi05;       // 0xCC75_1014
    BCRG_CTRL_CVI_CRG_BND_CVI06_M23A0_T    crg_bnd_cvi06;       // 0xCC75_1018
}BCRG_CTRL_CVI_REG_M23A0_T;
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

#define BCRG_CTRL_CVI_CRG_BND_CVI00_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_CVI_CRG_BND_CVI01_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_CVI_CRG_BND_CVI02_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_CVI_CRG_BND_CVI03_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_CVI_CRG_BND_CVI04_M23A0_T_OFF             (BASEADDRESS+0x0010)
#define BCRG_CTRL_CVI_CRG_BND_CVI05_M23A0_T_OFF             (BASEADDRESS+0x0014)
#define BCRG_CTRL_CVI_CRG_BND_CVI06_M23A0_T_OFF             (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xCC75_1000    crg_bnd_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_CVI_CRG_BND_CVI00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_1004    crg_bnd_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_CVI_CRG_BND_CVI01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_1008    crg_bnd_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_hdmi1_mclk_gate_en: 1;    //  0
    UINT32 reg_aud_hdmi2_mclk_gate_en: 1;    //  1
    UINT32 reg_aud_hdmi3_mclk_gate_en: 1;    //  2
    UINT32 reg_aud_hdmi4_mclk_gate_en: 1;    //  3
    UINT32 reg_earc_extern_aud_clk_gate_en: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_100C    crg_bnd_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_cvi_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_emmc_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_hdmi_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_imx_clk_gate_en: 1;    //  3
    UINT32 reg_apb_ipw_sb_cvd_clk_gate_en: 1;    //  4
    UINT32 reg_apb_ipw_sb_emu_clk_gate_en: 1;    //  5
    UINT32 reg_apb_ipw_usb_hs1_clk_gate_en: 1;    //  6
    UINT32 reg_apb_ipw_vdo_clk_gate_en: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_1010    crg_bnd_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_earc_rstn :  1;    //      0
    UINT32 reg_soft_phy1_rstn :  1;    //      1
    UINT32 reg_soft_phy2_rstn :  1;    //      2
    UINT32 reg_soft_rst_axi_brdg_dbb_0_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_1014    crg_bnd_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_cvi_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_emmc_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_hdmi_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_imx_n: 1;    //  3
    UINT32 reg_soft_rst_apb_ipw_sb_cvd_n: 1;    //  4
    UINT32 reg_soft_rst_apb_ipw_sb_emu_n: 1;    //  5
    UINT32 reg_soft_rst_apb_ipw_usb_hs1_n: 1;    //  6
    UINT32 reg_soft_rst_apb_ipw_vdo_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_1018    crg_bnd_cvi06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy_i2c_clk_sel:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_earc_extern_aud_clk_sel: 3;    //  6:4
    UINT32 resvd01            : 25;    //   31:7 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CVI_CRG_BND_CVI00_M23A0_T    crg_bnd_cvi00;       // 0xCC75_1000
    BCRG_CTRL_CVI_CRG_BND_CVI01_M23A0_T    crg_bnd_cvi01;       // 0xCC75_1004
    BCRG_CTRL_CVI_CRG_BND_CVI02_M23A0_T    crg_bnd_cvi02;       // 0xCC75_1008
    BCRG_CTRL_CVI_CRG_BND_CVI03_M23A0_T    crg_bnd_cvi03;       // 0xCC75_100C
    BCRG_CTRL_CVI_CRG_BND_CVI04_M23A0_T    crg_bnd_cvi04;       // 0xCC75_1010
    BCRG_CTRL_CVI_CRG_BND_CVI05_M23A0_T    crg_bnd_cvi05;       // 0xCC75_1014
    BCRG_CTRL_CVI_CRG_BND_CVI06_M23A0_T    crg_bnd_cvi06;       // 0xCC75_1018
}BCRG_CTRL_CVI_REG_M23A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

