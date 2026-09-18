#ifndef _BCRG_CTRL_HDMI_REG_O26A0_H_
#define _BCRG_CTRL_HDMI_REG_O26A0_H_

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
    0xC877_1000    crg_bnd_hdmi000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_HDMI_CRG_BND_HDMI000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_1004    crg_bnd_hdmi001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_HDMI_CRG_BND_HDMI001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_1008    crg_bnd_hdmi002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_hdmi1_mclk_gate_en:  1,    //      0
    reg_aud_hdmi2_mclk_gate_en:  1,    //      1
    reg_aud_hdmi3_mclk_gate_en:  1,    //      2
    reg_aud_hdmi4_mclk_gate_en:  1,    //      3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_HDMI_CRG_BND_HDMI002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_100C    crg_bnd_hdmi003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_cvi_clk_gate_en: 1,    //      0
    reg_apb_ipw_dsc_clk_gate_en: 1,    //      1
    reg_apb_ipw_hdmi_clk_gate_en: 1,    //     2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_HDMI_CRG_BND_HDMI003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_1010    crg_bnd_hdmi004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_earc_rstn        :  1,    //      0
    reg_soft_phy1_rstn        :  1,    //      1
    reg_soft_phy2_rstn        :  1,    //      2
    reg_soft_phy3_rstn        :  1,    //      3
    reg_soft_phy4_rstn        :  1,    //      4
    reg_soft_rst_axi_brdg_cpu_0_n: 1,    //    5
    reg_soft_rst_axi_brdg_usbsb_0_n: 1,    //  6
    reg_soft_rst_fly_brdg_teipw_0_n: 1,    //  7
    reg_soft_rst_fly_brdg_teipw_1_n: 1,    //  8
    reg_soft_rst_fly_brdg_teipw_2_n: 1,    //  9
    reg_soft_rst_fly_brdg_teipw_3_n: 1,    //  10
    reg_soft_rst_fly_brdg_tp_int_n: 1,    //  11
    reg_soft_rst_pes_brdg_te_6_n: 1,    //    12
    reg_soft_rst_pes_brdg_te_7_n: 1,    //    13
                              : 18;    //  31:14 reserved
}BCRG_CTRL_HDMI_CRG_BND_HDMI004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_1014    crg_bnd_hdmi005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_cvi_n:  1,    //      0
    reg_soft_rst_apb_ipw_dsc_n:  1,    //      1
    reg_soft_rst_apb_ipw_hdmi_n: 1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_HDMI_CRG_BND_HDMI005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_1018    crg_bnd_hdmi006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy_i2c_clk_sel       :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_HDMI_CRG_BND_HDMI006_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_HDMI_CRG_BND_HDMI000_O26A0_T    crg_bnd_hdmi000;    // 0xC877_1000
    BCRG_CTRL_HDMI_CRG_BND_HDMI001_O26A0_T    crg_bnd_hdmi001;    // 0xC877_1004
    BCRG_CTRL_HDMI_CRG_BND_HDMI002_O26A0_T    crg_bnd_hdmi002;    // 0xC877_1008
    BCRG_CTRL_HDMI_CRG_BND_HDMI003_O26A0_T    crg_bnd_hdmi003;    // 0xC877_100C
    BCRG_CTRL_HDMI_CRG_BND_HDMI004_O26A0_T    crg_bnd_hdmi004;    // 0xC877_1010
    BCRG_CTRL_HDMI_CRG_BND_HDMI005_O26A0_T    crg_bnd_hdmi005;    // 0xC877_1014
    BCRG_CTRL_HDMI_CRG_BND_HDMI006_O26A0_T    crg_bnd_hdmi006;    // 0xC877_1018
}BCRG_CTRL_HDMI_REG_O26A0_T;
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

#define BCRG_CTRL_HDMI_CRG_BND_HDMI000_O26A0_T_OFF          (BASEADDRESS+0x0000)
#define BCRG_CTRL_HDMI_CRG_BND_HDMI001_O26A0_T_OFF          (BASEADDRESS+0x0004)
#define BCRG_CTRL_HDMI_CRG_BND_HDMI002_O26A0_T_OFF          (BASEADDRESS+0x0008)
#define BCRG_CTRL_HDMI_CRG_BND_HDMI003_O26A0_T_OFF          (BASEADDRESS+0x000C)
#define BCRG_CTRL_HDMI_CRG_BND_HDMI004_O26A0_T_OFF          (BASEADDRESS+0x0010)
#define BCRG_CTRL_HDMI_CRG_BND_HDMI005_O26A0_T_OFF          (BASEADDRESS+0x0014)
#define BCRG_CTRL_HDMI_CRG_BND_HDMI006_O26A0_T_OFF          (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xC877_1000    crg_bnd_hdmi000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_1004    crg_bnd_hdmi001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_1008    crg_bnd_hdmi002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_hdmi1_mclk_gate_en: 1;    //  0
    UINT32 reg_aud_hdmi2_mclk_gate_en: 1;    //  1
    UINT32 reg_aud_hdmi3_mclk_gate_en: 1;    //  2
    UINT32 reg_aud_hdmi4_mclk_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_100C    crg_bnd_hdmi003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_cvi_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_dsc_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_hdmi_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_1010    crg_bnd_hdmi004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_earc_rstn :  1;    //      0
    UINT32 reg_soft_phy1_rstn :  1;    //      1
    UINT32 reg_soft_phy2_rstn :  1;    //      2
    UINT32 reg_soft_phy3_rstn :  1;    //      3
    UINT32 reg_soft_phy4_rstn :  1;    //      4
    UINT32 reg_soft_rst_axi_brdg_cpu_0_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_usbsb_0_n: 1;    //  6
    UINT32 reg_soft_rst_fly_brdg_teipw_0_n: 1;    //  7
    UINT32 reg_soft_rst_fly_brdg_teipw_1_n: 1;    //  8
    UINT32 reg_soft_rst_fly_brdg_teipw_2_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_teipw_3_n: 1;    //  10
    UINT32 reg_soft_rst_fly_brdg_tp_int_n: 1;    //  11
    UINT32 reg_soft_rst_pes_brdg_te_6_n: 1;    //  12
    UINT32 reg_soft_rst_pes_brdg_te_7_n: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_1014    crg_bnd_hdmi005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_cvi_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_dsc_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_hdmi_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_1018    crg_bnd_hdmi006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy_i2c_clk_sel:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI006_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_HDMI_CRG_BND_HDMI000_O26A0_T    crg_bnd_hdmi000;    // 0xC877_1000
    BCRG_CTRL_HDMI_CRG_BND_HDMI001_O26A0_T    crg_bnd_hdmi001;    // 0xC877_1004
    BCRG_CTRL_HDMI_CRG_BND_HDMI002_O26A0_T    crg_bnd_hdmi002;    // 0xC877_1008
    BCRG_CTRL_HDMI_CRG_BND_HDMI003_O26A0_T    crg_bnd_hdmi003;    // 0xC877_100C
    BCRG_CTRL_HDMI_CRG_BND_HDMI004_O26A0_T    crg_bnd_hdmi004;    // 0xC877_1010
    BCRG_CTRL_HDMI_CRG_BND_HDMI005_O26A0_T    crg_bnd_hdmi005;    // 0xC877_1014
    BCRG_CTRL_HDMI_CRG_BND_HDMI006_O26A0_T    crg_bnd_hdmi006;    // 0xC877_1018
}BCRG_CTRL_HDMI_REG_O26A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_HDMI_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

