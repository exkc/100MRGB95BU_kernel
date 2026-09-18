#ifndef _BCRG_CTRL_CVI_REG_H_
#define _BCRG_CTRL_CVI_REG_H_

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
    0xD_0000    crg_bnd_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_CVI_CRG_BND_CVI00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xD_0004    crg_bnd_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_CVI_CRG_BND_CVI01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xD_0008    crg_bnd_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_cvi_clk_gate_en: 1,    //      0
    reg_apb_ipw_dne_clk_gate_en: 1,    //      1
    reg_apb_ipw_dsc_clk_gate_en: 1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xD_000C    crg_bnd_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_adap_hdmirx_prt0_tmdsqp_n: 1,    //  0
    reg_soft_rst_adap_hdmirx_prt1_tmdsqp_n: 1,    //  1
    reg_soft_rst_adap_hdmirx_prt2_tmdsqp_n: 1,    //  2
    reg_soft_rst_adap_hdmirx_prt3_tmdsqp_n: 1,    //  3
    reg_soft_rst_axi_brdg_imx_0_n: 1,    //    4
    reg_soft_rst_axi_brdg_imx_1_n: 1,    //    5
    reg_soft_rst_axi_brdg_imx_2_n: 1,    //    6
    reg_soft_rst_axi_brdg_imx_3_n: 1,    //    7
    reg_soft_rst_fly_brdg_cco_5_n: 1,    //    8
    reg_soft_rst_fly_brdg_imx_16_n: 1,    //   9
    reg_soft_rst_hsp_brdg_hdr_0_n: 1,    //   10
    reg_soft_rst_hsp_brdg_hdr_1_n: 1,    //   11
    reg_soft_rst_hsp_brdg_hdr_2_n: 1,    //   12
    reg_soft_rst_hsp_brdg_hdr_3_n: 1,    //   13
    reg_soft_rst_hsp_brdg_hdr_4_n: 1,    //   14
    reg_soft_rst_hsp_brdg_hdr_5_n: 1,    //   15
    reg_soft_rst_hsp_brdg_imx_0_n: 1,    //   16
    reg_soft_rst_hsp_brdg_imx_10_n: 1,    //  17
    reg_soft_rst_hsp_brdg_imx_11_n: 1,    //  18
    reg_soft_rst_hsp_brdg_imx_1_n: 1,    //   19
    reg_soft_rst_hsp_brdg_imx_2_n: 1,    //   20
    reg_soft_rst_hsp_brdg_imx_3_n: 1,    //   21
    reg_soft_rst_hsp_brdg_imx_4_n: 1,    //   22
    reg_soft_rst_hsp_brdg_imx_5_n: 1,    //   23
    reg_soft_rst_hsp_brdg_imx_6_n: 1,    //   24
    reg_soft_rst_hsp_brdg_imx_7_n: 1,    //   25
    reg_soft_rst_hsp_brdg_imx_8_n: 1,    //   26
    reg_soft_rst_hsp_brdg_imx_9_n: 1,    //   27
    reg_soft_rst_hsp_brdg_nd0_0_n: 1,    //   28
    reg_soft_rst_hsp_brdg_nd0_1_n: 1,    //   29
    reg_soft_rst_hsp_brdg_vdo_0_n: 1,    //   30
    reg_soft_rst_hsp_brdg_vdo_1_n: 1;    //   31
}BCRG_CTRL_CVI_CRG_BND_CVI03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xD_0010    crg_bnd_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_hsp_brdg_vdo_2_n: 1,    //    0
    reg_soft_rst_hsp_brdg_vdo_3_n: 1,    //    1
    reg_soft_rst_hsp_brdg_vdo_4_n: 1,    //    2
    reg_soft_rst_hsp_brdg_vdo_5_n: 1,    //    3
    reg_soft_sbw_aresetn_400  :  1,    //      4
    reg_soft_sbw_aresetn_480  :  1,    //      5
                              : 26;    //   31:6 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xD_0014    crg_bnd_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_cvi_n:  1,    //      0
    reg_soft_rst_apb_ipw_dne_n:  1,    //      1
    reg_soft_rst_apb_ipw_dsc_n:  1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CVI_CRG_BND_CVI00_O22A0_T    crg_bnd_cvi00;         // 0xD_0000
    BCRG_CTRL_CVI_CRG_BND_CVI01_O22A0_T    crg_bnd_cvi01;         // 0xD_0004
    BCRG_CTRL_CVI_CRG_BND_CVI02_O22A0_T    crg_bnd_cvi02;         // 0xD_0008
    BCRG_CTRL_CVI_CRG_BND_CVI03_O22A0_T    crg_bnd_cvi03;         // 0xD_000C
    BCRG_CTRL_CVI_CRG_BND_CVI04_O22A0_T    crg_bnd_cvi04;         // 0xD_0010
    BCRG_CTRL_CVI_CRG_BND_CVI05_O22A0_T    crg_bnd_cvi05;         // 0xD_0014
}BCRG_CTRL_CVI_REG_O22A0_T;
/* 6 regs */

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

#define BCRG_CTRL_CVI_CRG_BND_CVI00_O22A0_T_OFF               (BASEADDRESS+0x0000)
#define BCRG_CTRL_CVI_CRG_BND_CVI01_O22A0_T_OFF               (BASEADDRESS+0x0004)
#define BCRG_CTRL_CVI_CRG_BND_CVI02_O22A0_T_OFF               (BASEADDRESS+0x0008)
#define BCRG_CTRL_CVI_CRG_BND_CVI03_O22A0_T_OFF               (BASEADDRESS+0x000C)
#define BCRG_CTRL_CVI_CRG_BND_CVI04_O22A0_T_OFF               (BASEADDRESS+0x0010)
#define BCRG_CTRL_CVI_CRG_BND_CVI05_O22A0_T_OFF               (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xD_0000    crg_bnd_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_CVI_CRG_BND_CVI00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xD_0004    crg_bnd_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_CVI_CRG_BND_CVI01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xD_0008    crg_bnd_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_cvi_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_dne_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_dsc_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xD_000C    crg_bnd_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_adap_hdmirx_prt0_tmdsqp_n: 1;    //  0
    UINT32 reg_soft_rst_adap_hdmirx_prt1_tmdsqp_n: 1;    //  1
    UINT32 reg_soft_rst_adap_hdmirx_prt2_tmdsqp_n: 1;    //  2
    UINT32 reg_soft_rst_adap_hdmirx_prt3_tmdsqp_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_imx_0_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_imx_1_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_imx_2_n: 1;    //  6
    UINT32 reg_soft_rst_axi_brdg_imx_3_n: 1;    //  7
    UINT32 reg_soft_rst_fly_brdg_cco_5_n: 1;    //  8
    UINT32 reg_soft_rst_fly_brdg_imx_16_n: 1;    //  9
    UINT32 reg_soft_rst_hsp_brdg_hdr_0_n: 1;    //  10
    UINT32 reg_soft_rst_hsp_brdg_hdr_1_n: 1;    //  11
    UINT32 reg_soft_rst_hsp_brdg_hdr_2_n: 1;    //  12
    UINT32 reg_soft_rst_hsp_brdg_hdr_3_n: 1;    //  13
    UINT32 reg_soft_rst_hsp_brdg_hdr_4_n: 1;    //  14
    UINT32 reg_soft_rst_hsp_brdg_hdr_5_n: 1;    //  15
    UINT32 reg_soft_rst_hsp_brdg_imx_0_n: 1;    //  16
    UINT32 reg_soft_rst_hsp_brdg_imx_10_n: 1;    //  17
    UINT32 reg_soft_rst_hsp_brdg_imx_11_n: 1;    //  18
    UINT32 reg_soft_rst_hsp_brdg_imx_1_n: 1;    //  19
    UINT32 reg_soft_rst_hsp_brdg_imx_2_n: 1;    //  20
    UINT32 reg_soft_rst_hsp_brdg_imx_3_n: 1;    //  21
    UINT32 reg_soft_rst_hsp_brdg_imx_4_n: 1;    //  22
    UINT32 reg_soft_rst_hsp_brdg_imx_5_n: 1;    //  23
    UINT32 reg_soft_rst_hsp_brdg_imx_6_n: 1;    //  24
    UINT32 reg_soft_rst_hsp_brdg_imx_7_n: 1;    //  25
    UINT32 reg_soft_rst_hsp_brdg_imx_8_n: 1;    //  26
    UINT32 reg_soft_rst_hsp_brdg_imx_9_n: 1;    //  27
    UINT32 reg_soft_rst_hsp_brdg_nd0_0_n: 1;    //  28
    UINT32 reg_soft_rst_hsp_brdg_nd0_1_n: 1;    //  29
    UINT32 reg_soft_rst_hsp_brdg_vdo_0_n: 1;    //  30
    UINT32 reg_soft_rst_hsp_brdg_vdo_1_n: 1;    //  31
    };
}BCRG_CTRL_CVI_CRG_BND_CVI03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xD_0010    crg_bnd_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_hsp_brdg_vdo_2_n: 1;    //  0
    UINT32 reg_soft_rst_hsp_brdg_vdo_3_n: 1;    //  1
    UINT32 reg_soft_rst_hsp_brdg_vdo_4_n: 1;    //  2
    UINT32 reg_soft_rst_hsp_brdg_vdo_5_n: 1;    //  3
    UINT32 reg_soft_sbw_aresetn_400: 1;    //  4
    UINT32 reg_soft_sbw_aresetn_480: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xD_0014    crg_bnd_cvi05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_cvi_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_dne_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_dsc_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CVI_CRG_BND_CVI00_O22A0_T    crg_bnd_cvi00;         // 0xD_0000
    BCRG_CTRL_CVI_CRG_BND_CVI01_O22A0_T    crg_bnd_cvi01;         // 0xD_0004
    BCRG_CTRL_CVI_CRG_BND_CVI02_O22A0_T    crg_bnd_cvi02;         // 0xD_0008
    BCRG_CTRL_CVI_CRG_BND_CVI03_O22A0_T    crg_bnd_cvi03;         // 0xD_000C
    BCRG_CTRL_CVI_CRG_BND_CVI04_O22A0_T    crg_bnd_cvi04;         // 0xD_0010
    BCRG_CTRL_CVI_CRG_BND_CVI05_O22A0_T    crg_bnd_cvi05;         // 0xD_0014
}BCRG_CTRL_CVI_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

