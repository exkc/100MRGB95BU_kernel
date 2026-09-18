#ifndef _BCRG_CTRL_AUD_REG_O26A0_H_
#define _BCRG_CTRL_AUD_REG_O26A0_H_

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
    0xCE7B_1000    crg_bnd_aud000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_AUD_CRG_BND_AUD000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_1004    crg_bnd_aud001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_AUD_CRG_BND_AUD001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_1008    crg_bnd_aud002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fsc_clk_gate_en       :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_AUD_CRG_BND_AUD002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_100C    crg_bnd_aud003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_aud_clk_gate_en: 1,    //      0
    reg_apb_ipw_te_clk_gate_en:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_AUD_CRG_BND_AUD003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_1010    crg_bnd_aud004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_f_tp_int_n   :  1,    //      0
    reg_soft_rst_sync_fsc_clk_n: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_AUD_CRG_BND_AUD004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_1014    crg_bnd_aud005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_aud_n:  1,    //      0
    reg_soft_rst_apb_ipw_te_n :  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_AUD_CRG_BND_AUD005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_AUD_CRG_BND_AUD000_O26A0_T    crg_bnd_aud000;     // 0xCE7B_1000
    BCRG_CTRL_AUD_CRG_BND_AUD001_O26A0_T    crg_bnd_aud001;     // 0xCE7B_1004
    BCRG_CTRL_AUD_CRG_BND_AUD002_O26A0_T    crg_bnd_aud002;     // 0xCE7B_1008
    BCRG_CTRL_AUD_CRG_BND_AUD003_O26A0_T    crg_bnd_aud003;     // 0xCE7B_100C
    BCRG_CTRL_AUD_CRG_BND_AUD004_O26A0_T    crg_bnd_aud004;     // 0xCE7B_1010
    BCRG_CTRL_AUD_CRG_BND_AUD005_O26A0_T    crg_bnd_aud005;     // 0xCE7B_1014
}BCRG_CTRL_AUD_REG_O26A0_T;
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

#define BCRG_CTRL_AUD_CRG_BND_AUD000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_AUD_CRG_BND_AUD001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_AUD_CRG_BND_AUD002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_AUD_CRG_BND_AUD003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_AUD_CRG_BND_AUD004_O26A0_T_OFF            (BASEADDRESS+0x0010)
#define BCRG_CTRL_AUD_CRG_BND_AUD005_O26A0_T_OFF            (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCE7B_1000    crg_bnd_aud000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_AUD_CRG_BND_AUD000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_1004    crg_bnd_aud001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_AUD_CRG_BND_AUD001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_1008    crg_bnd_aud002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fsc_clk_gate_en:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_AUD_CRG_BND_AUD002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_100C    crg_bnd_aud003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_aud_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_te_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_AUD_CRG_BND_AUD003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_1010    crg_bnd_aud004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_f_tp_int_n: 1;    //   0
    UINT32 reg_soft_rst_sync_fsc_clk_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_AUD_CRG_BND_AUD004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_1014    crg_bnd_aud005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_aud_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_te_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_AUD_CRG_BND_AUD005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_AUD_CRG_BND_AUD000_O26A0_T    crg_bnd_aud000;     // 0xCE7B_1000
    BCRG_CTRL_AUD_CRG_BND_AUD001_O26A0_T    crg_bnd_aud001;     // 0xCE7B_1004
    BCRG_CTRL_AUD_CRG_BND_AUD002_O26A0_T    crg_bnd_aud002;     // 0xCE7B_1008
    BCRG_CTRL_AUD_CRG_BND_AUD003_O26A0_T    crg_bnd_aud003;     // 0xCE7B_100C
    BCRG_CTRL_AUD_CRG_BND_AUD004_O26A0_T    crg_bnd_aud004;     // 0xCE7B_1010
    BCRG_CTRL_AUD_CRG_BND_AUD005_O26A0_T    crg_bnd_aud005;     // 0xCE7B_1014
}BCRG_CTRL_AUD_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_AUD_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

