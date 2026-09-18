#ifndef _BCRG_CTRL_AUD_REG_O24A0_H_
#define _BCRG_CTRL_AUD_REG_O24A0_H_

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
    0xCE49_1000    crg_bnd_aud0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_AUD_CRG_BND_AUD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_1004    crg_bnd_aud1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_AUD_CRG_BND_AUD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_1008    crg_bnd_aud2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_aud_clk_gate_en: 1,    //      0
    reg_apb_ipw_te_clk_gate_en:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_AUD_CRG_BND_AUD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_100C    crg_bnd_aud3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_cvi_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_dbb_0_n: 1,    //    1
    reg_soft_rst_axi_brdg_ephy_0_n: 1,    //   2
    reg_soft_rst_axi_brdg_hdmi_0_n: 1,    //   3
    reg_soft_rst_fly_brdg_cvi_0_n: 1,    //    4
    reg_soft_rst_fly_brdg_cvi_1_n: 1,    //    5
    reg_soft_rst_fly_brdg_cvi_2_n: 1,    //    6
    reg_soft_rst_fly_brdg_cvi_3_n: 1,    //    7
    reg_soft_rst_fly_brdg_cvi_4_n: 1,    //    8
    reg_soft_rst_hsp_brdg_nd0_2_n: 1,    //    9
    reg_soft_rst_hsp_brdg_nd0_3_n: 1,    //   10
                              : 21;    //  31:11 reserved
}BCRG_CTRL_AUD_CRG_BND_AUD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_1010    crg_bnd_aud4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_aud_n:  1,    //      0
    reg_soft_rst_apb_ipw_te_n :  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_AUD_CRG_BND_AUD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_AUD_CRG_BND_AUD0_O24A0_T    crg_bnd_aud0;         // 0xCE49_1000
    BCRG_CTRL_AUD_CRG_BND_AUD1_O24A0_T    crg_bnd_aud1;         // 0xCE49_1004
    BCRG_CTRL_AUD_CRG_BND_AUD2_O24A0_T    crg_bnd_aud2;         // 0xCE49_1008
    BCRG_CTRL_AUD_CRG_BND_AUD3_O24A0_T    crg_bnd_aud3;         // 0xCE49_100C
    BCRG_CTRL_AUD_CRG_BND_AUD4_O24A0_T    crg_bnd_aud4;         // 0xCE49_1010
}BCRG_CTRL_AUD_REG_O24A0_T;
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

#define BCRG_CTRL_AUD_CRG_BND_AUD0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_AUD_CRG_BND_AUD1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_AUD_CRG_BND_AUD2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_AUD_CRG_BND_AUD3_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_AUD_CRG_BND_AUD4_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCE49_1000    crg_bnd_aud0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_AUD_CRG_BND_AUD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_1004    crg_bnd_aud1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_AUD_CRG_BND_AUD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_1008    crg_bnd_aud2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_aud_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_te_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_AUD_CRG_BND_AUD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_100C    crg_bnd_aud3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_cvi_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_dbb_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_ephy_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_hdmi_0_n: 1;    //  3
    UINT32 reg_soft_rst_fly_brdg_cvi_0_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_cvi_1_n: 1;    //  5
    UINT32 reg_soft_rst_fly_brdg_cvi_2_n: 1;    //  6
    UINT32 reg_soft_rst_fly_brdg_cvi_3_n: 1;    //  7
    UINT32 reg_soft_rst_fly_brdg_cvi_4_n: 1;    //  8
    UINT32 reg_soft_rst_hsp_brdg_nd0_2_n: 1;    //  9
    UINT32 reg_soft_rst_hsp_brdg_nd0_3_n: 1;    //  10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}BCRG_CTRL_AUD_CRG_BND_AUD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_1010    crg_bnd_aud4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_aud_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_te_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_AUD_CRG_BND_AUD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_AUD_CRG_BND_AUD0_O24A0_T    crg_bnd_aud0;         // 0xCE49_1000
    BCRG_CTRL_AUD_CRG_BND_AUD1_O24A0_T    crg_bnd_aud1;         // 0xCE49_1004
    BCRG_CTRL_AUD_CRG_BND_AUD2_O24A0_T    crg_bnd_aud2;         // 0xCE49_1008
    BCRG_CTRL_AUD_CRG_BND_AUD3_O24A0_T    crg_bnd_aud3;         // 0xCE49_100C
    BCRG_CTRL_AUD_CRG_BND_AUD4_O24A0_T    crg_bnd_aud4;         // 0xCE49_1010
}BCRG_CTRL_AUD_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_AUD_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

