#ifndef _BCRG_CTRL_LNX2_REG_O24A0_H_
#define _BCRG_CTRL_LNX2_REG_O24A0_H_

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
    0xCCDA_1000    crg_bnd_lnx20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_LNX2_CRG_BND_LNX20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDA_1004    crg_bnd_lnx21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_LNX2_CRG_BND_LNX21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDA_1008    crg_bnd_lnx22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_lnx2_clk_gate_en: 1,    //     0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_LNX2_CRG_BND_LNX22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDA_100C    crg_bnd_lnx23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_cpu_5_n: 1,    //    0
    reg_soft_rst_axi_brdg_micom_0_n: 1,    //  1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_LNX2_CRG_BND_LNX23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDA_1010    crg_bnd_lnx24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_lnx2_n: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_LNX2_CRG_BND_LNX24_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lnx2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LNX2_CRG_BND_LNX20_O24A0_T    crg_bnd_lnx20;      // 0xCCDA_1000
    BCRG_CTRL_LNX2_CRG_BND_LNX21_O24A0_T    crg_bnd_lnx21;      // 0xCCDA_1004
    BCRG_CTRL_LNX2_CRG_BND_LNX22_O24A0_T    crg_bnd_lnx22;      // 0xCCDA_1008
    BCRG_CTRL_LNX2_CRG_BND_LNX23_O24A0_T    crg_bnd_lnx23;      // 0xCCDA_100C
    BCRG_CTRL_LNX2_CRG_BND_LNX24_O24A0_T    crg_bnd_lnx24;      // 0xCCDA_1010
}BCRG_CTRL_LNX2_REG_O24A0_T;
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

#define BCRG_CTRL_LNX2_CRG_BND_LNX20_O24A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_LNX2_CRG_BND_LNX21_O24A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_LNX2_CRG_BND_LNX22_O24A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_LNX2_CRG_BND_LNX23_O24A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_LNX2_CRG_BND_LNX24_O24A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCDA_1000    crg_bnd_lnx20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_LNX2_CRG_BND_LNX20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDA_1004    crg_bnd_lnx21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_LNX2_CRG_BND_LNX21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDA_1008    crg_bnd_lnx22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_lnx2_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_LNX2_CRG_BND_LNX22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDA_100C    crg_bnd_lnx23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_cpu_5_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_micom_0_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_LNX2_CRG_BND_LNX23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDA_1010    crg_bnd_lnx24 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_lnx2_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_LNX2_CRG_BND_LNX24_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_lnx2 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_LNX2_CRG_BND_LNX20_O24A0_T    crg_bnd_lnx20;      // 0xCCDA_1000
    BCRG_CTRL_LNX2_CRG_BND_LNX21_O24A0_T    crg_bnd_lnx21;      // 0xCCDA_1004
    BCRG_CTRL_LNX2_CRG_BND_LNX22_O24A0_T    crg_bnd_lnx22;      // 0xCCDA_1008
    BCRG_CTRL_LNX2_CRG_BND_LNX23_O24A0_T    crg_bnd_lnx23;      // 0xCCDA_100C
    BCRG_CTRL_LNX2_CRG_BND_LNX24_O24A0_T    crg_bnd_lnx24;      // 0xCCDA_1010
}BCRG_CTRL_LNX2_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_LNX2_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

