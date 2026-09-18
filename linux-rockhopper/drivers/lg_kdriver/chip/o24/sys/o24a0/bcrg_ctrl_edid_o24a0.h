#ifndef _BCRG_CTRL_EDID_REG_O24A0_H_
#define _BCRG_CTRL_EDID_REG_O24A0_H_

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
    0xC886_1000    crg_bnd_edid0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_EDID_CRG_BND_EDID0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_1004    crg_bnd_edid1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_EDID_CRG_BND_EDID1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_1008    crg_bnd_edid2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_edid_clk_gate_en: 1,    //     0
    reg_apb_ipw_ephy_clk_gate_en: 1,    //     1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_EDID_CRG_BND_EDID2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_100C    crg_bnd_edid3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_edid_n: 1,    //      0
    reg_soft_rst_apb_ipw_ephy_n: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_EDID_CRG_BND_EDID3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_EDID_CRG_BND_EDID0_O24A0_T    crg_bnd_edid0;      // 0xC886_1000
    BCRG_CTRL_EDID_CRG_BND_EDID1_O24A0_T    crg_bnd_edid1;      // 0xC886_1004
    BCRG_CTRL_EDID_CRG_BND_EDID2_O24A0_T    crg_bnd_edid2;      // 0xC886_1008
    BCRG_CTRL_EDID_CRG_BND_EDID3_O24A0_T    crg_bnd_edid3;      // 0xC886_100C
}BCRG_CTRL_EDID_REG_O24A0_T;
/* 4 regs */

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

#define BCRG_CTRL_EDID_CRG_BND_EDID0_O24A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_EDID_CRG_BND_EDID1_O24A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_EDID_CRG_BND_EDID2_O24A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_EDID_CRG_BND_EDID3_O24A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC886_1000    crg_bnd_edid0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_EDID_CRG_BND_EDID0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_1004    crg_bnd_edid1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_EDID_CRG_BND_EDID1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_1008    crg_bnd_edid2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_edid_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_ephy_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_EDID_CRG_BND_EDID2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_100C    crg_bnd_edid3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_edid_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_ephy_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_EDID_CRG_BND_EDID3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_EDID_CRG_BND_EDID0_O24A0_T    crg_bnd_edid0;      // 0xC886_1000
    BCRG_CTRL_EDID_CRG_BND_EDID1_O24A0_T    crg_bnd_edid1;      // 0xC886_1004
    BCRG_CTRL_EDID_CRG_BND_EDID2_O24A0_T    crg_bnd_edid2;      // 0xC886_1008
    BCRG_CTRL_EDID_CRG_BND_EDID3_O24A0_T    crg_bnd_edid3;      // 0xC886_100C
}BCRG_CTRL_EDID_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_EDID_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

