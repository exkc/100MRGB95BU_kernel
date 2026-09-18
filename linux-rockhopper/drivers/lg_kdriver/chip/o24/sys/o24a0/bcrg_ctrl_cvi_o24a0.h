#ifndef _BCRG_CTRL_CVI_REG_O24A0_H_
#define _BCRG_CTRL_CVI_REG_O24A0_H_

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
    0xCCD7_1000    crg_bnd_cvi0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_CVI_CRG_BND_CVI0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_1004    crg_bnd_cvi1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_CVI_CRG_BND_CVI1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_1008    crg_bnd_cvi2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_cvi_clk_gate_en: 1,    //      0
    reg_apb_ipw_dsc_clk_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_100C    crg_bnd_cvi3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_ephy_0_n: 1,    //   0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_1010    crg_bnd_cvi4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_cvi_n:  1,    //      0
    reg_soft_rst_apb_ipw_dsc_n:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_CVI_CRG_BND_CVI4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CVI_CRG_BND_CVI0_O24A0_T    crg_bnd_cvi0;         // 0xCCD7_1000
    BCRG_CTRL_CVI_CRG_BND_CVI1_O24A0_T    crg_bnd_cvi1;         // 0xCCD7_1004
    BCRG_CTRL_CVI_CRG_BND_CVI2_O24A0_T    crg_bnd_cvi2;         // 0xCCD7_1008
    BCRG_CTRL_CVI_CRG_BND_CVI3_O24A0_T    crg_bnd_cvi3;         // 0xCCD7_100C
    BCRG_CTRL_CVI_CRG_BND_CVI4_O24A0_T    crg_bnd_cvi4;         // 0xCCD7_1010
}BCRG_CTRL_CVI_REG_O24A0_T;
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

#define BCRG_CTRL_CVI_CRG_BND_CVI0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_CVI_CRG_BND_CVI1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_CVI_CRG_BND_CVI2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_CVI_CRG_BND_CVI3_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_CVI_CRG_BND_CVI4_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCD7_1000    crg_bnd_cvi0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_CVI_CRG_BND_CVI0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_1004    crg_bnd_cvi1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_CVI_CRG_BND_CVI1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_1008    crg_bnd_cvi2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_cvi_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_dsc_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_100C    crg_bnd_cvi3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_ephy_0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD7_1010    crg_bnd_cvi4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_cvi_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_dsc_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_CVI_CRG_BND_CVI4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CVI_CRG_BND_CVI0_O24A0_T    crg_bnd_cvi0;         // 0xCCD7_1000
    BCRG_CTRL_CVI_CRG_BND_CVI1_O24A0_T    crg_bnd_cvi1;         // 0xCCD7_1004
    BCRG_CTRL_CVI_CRG_BND_CVI2_O24A0_T    crg_bnd_cvi2;         // 0xCCD7_1008
    BCRG_CTRL_CVI_CRG_BND_CVI3_O24A0_T    crg_bnd_cvi3;         // 0xCCD7_100C
    BCRG_CTRL_CVI_CRG_BND_CVI4_O24A0_T    crg_bnd_cvi4;         // 0xCCD7_1010
}BCRG_CTRL_CVI_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_CVI_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

