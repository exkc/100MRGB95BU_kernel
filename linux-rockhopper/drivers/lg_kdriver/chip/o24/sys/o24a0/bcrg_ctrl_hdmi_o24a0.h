#ifndef _BCRG_CTRL_HDMI_REG_O24A0_H_
#define _BCRG_CTRL_HDMI_REG_O24A0_H_

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
    0xC8D7_1000    crg_bnd_hdmi0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_HDMI_CRG_BND_HDMI0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_1004    crg_bnd_hdmi1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_HDMI_CRG_BND_HDMI1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_1008    crg_bnd_hdmi2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_hdmi1_mclk_gate_en:  1,    //      0
    reg_aud_hdmi2_mclk_gate_en:  1,    //      1
    reg_aud_hdmi3_mclk_gate_en:  1,    //      2
    reg_aud_hdmi4_mclk_gate_en:  1,    //      3
    reg_earc_extern_aud_clk_gate_en: 1,    //  4
                              : 27;    //   31:5 reserved
}BCRG_CTRL_HDMI_CRG_BND_HDMI2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_100C    crg_bnd_hdmi3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_hdmi_clk_gate_en: 1,    //     0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_HDMI_CRG_BND_HDMI3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_1010    crg_bnd_hdmi4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_earc_rstn        :  1,    //      0
    reg_soft_phy1_rstn        :  1,    //      1
    reg_soft_phy2_rstn        :  1,    //      2
    reg_soft_phy3_rstn        :  1,    //      3
    reg_soft_phy4_rstn        :  1,    //      4
    reg_soft_rst_hsp_brdg_nd0_2_n: 1,    //    5
    reg_soft_rst_hsp_brdg_nd0_3_n: 1,    //    6
                              : 25;    //   31:7 reserved
}BCRG_CTRL_HDMI_CRG_BND_HDMI4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_1014    crg_bnd_hdmi5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_hdmi_n: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_HDMI_CRG_BND_HDMI5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_1018    crg_bnd_hdmi6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earc_extern_aud_clk_sel: 3,    //   2: 0
                              :  1,    //      3 reserved
    reg_phy_i2c_clk_sel       :  1,    //      4
                              : 27;    //   31:5 reserved
}BCRG_CTRL_HDMI_CRG_BND_HDMI6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_HDMI_CRG_BND_HDMI0_O24A0_T    crg_bnd_hdmi0;      // 0xC8D7_1000
    BCRG_CTRL_HDMI_CRG_BND_HDMI1_O24A0_T    crg_bnd_hdmi1;      // 0xC8D7_1004
    BCRG_CTRL_HDMI_CRG_BND_HDMI2_O24A0_T    crg_bnd_hdmi2;      // 0xC8D7_1008
    BCRG_CTRL_HDMI_CRG_BND_HDMI3_O24A0_T    crg_bnd_hdmi3;      // 0xC8D7_100C
    BCRG_CTRL_HDMI_CRG_BND_HDMI4_O24A0_T    crg_bnd_hdmi4;      // 0xC8D7_1010
    BCRG_CTRL_HDMI_CRG_BND_HDMI5_O24A0_T    crg_bnd_hdmi5;      // 0xC8D7_1014
    BCRG_CTRL_HDMI_CRG_BND_HDMI6_O24A0_T    crg_bnd_hdmi6;      // 0xC8D7_1018
}BCRG_CTRL_HDMI_REG_O24A0_T;
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

#define BCRG_CTRL_HDMI_CRG_BND_O24A0_HDMI0_O24A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_HDMI_CRG_BND_O24A0_HDMI1_O24A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_HDMI_CRG_BND_O24A0_HDMI2_O24A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_HDMI_CRG_BND_O24A0_HDMI3_O24A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_HDMI_CRG_BND_O24A0_HDMI4_O24A0_T_OFF            (BASEADDRESS+0x0010)
#define BCRG_CTRL_HDMI_CRG_BND_O24A0_HDMI5_O24A0_T_OFF            (BASEADDRESS+0x0014)
#define BCRG_CTRL_HDMI_CRG_BND_O24A0_HDMI6_O24A0_T_OFF            (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xC8D7_1000    crg_bnd_hdmi0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_1004    crg_bnd_hdmi1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_1008    crg_bnd_hdmi2 ''
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
}BCRG_CTRL_HDMI_CRG_BND_HDMI2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_100C    crg_bnd_hdmi3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_hdmi_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_1010    crg_bnd_hdmi4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_earc_rstn :  1;    //      0
    UINT32 reg_soft_phy1_rstn :  1;    //      1
    UINT32 reg_soft_phy2_rstn :  1;    //      2
    UINT32 reg_soft_phy3_rstn :  1;    //      3
    UINT32 reg_soft_phy4_rstn :  1;    //      4
    UINT32 reg_soft_rst_hsp_brdg_nd0_2_n: 1;    //  5
    UINT32 reg_soft_rst_hsp_brdg_nd0_3_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_1014    crg_bnd_hdmi5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_hdmi_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_1018    crg_bnd_hdmi6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earc_extern_aud_clk_sel: 3;    //  2:0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_phy_i2c_clk_sel:  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BCRG_CTRL_HDMI_CRG_BND_HDMI6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_HDMI_CRG_BND_HDMI0_O24A0_T    crg_bnd_hdmi0;      // 0xC8D7_1000
    BCRG_CTRL_HDMI_CRG_BND_HDMI1_O24A0_T    crg_bnd_hdmi1;      // 0xC8D7_1004
    BCRG_CTRL_HDMI_CRG_BND_HDMI2_O24A0_T    crg_bnd_hdmi2;      // 0xC8D7_1008
    BCRG_CTRL_HDMI_CRG_BND_HDMI3_O24A0_T    crg_bnd_hdmi3;      // 0xC8D7_100C
    BCRG_CTRL_HDMI_CRG_BND_HDMI4_O24A0_T    crg_bnd_hdmi4;      // 0xC8D7_1010
    BCRG_CTRL_HDMI_CRG_BND_HDMI5_O24A0_T    crg_bnd_hdmi5;      // 0xC8D7_1014
    BCRG_CTRL_HDMI_CRG_BND_HDMI6_O24A0_T    crg_bnd_hdmi6;      // 0xC8D7_1018
}BCRG_CTRL_HDMI_REG_O24A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_HDMI_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

