#ifndef _BCRG_CTRL_VD0_REG_O26A0_H_
#define _BCRG_CTRL_VD0_REG_O26A0_H_

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
    0xCE52_1000    crg_bnd_vd0000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_VD0_CRG_BND_VD0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_1004    crg_bnd_vd0001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_VD0_CRG_BND_VD0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_1008    crg_bnd_vd0002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_vd0_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD0_CRG_BND_VD0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_100C    crg_bnd_vd0003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_icod_0_n: 1,    //   0
    reg_soft_rst_axi_brdg_lnx2_0_n: 1,    //   1
    reg_soft_rst_axi_brdg_venc_0_n: 1,    //   2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_VD0_CRG_BND_VD0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_1010    crg_bnd_vd0004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_vd0_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_VD0_CRG_BND_VD0004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD0_CRG_BND_VD0000_O26A0_T    crg_bnd_vd0000;     // 0xCE52_1000
    BCRG_CTRL_VD0_CRG_BND_VD0001_O26A0_T    crg_bnd_vd0001;     // 0xCE52_1004
    BCRG_CTRL_VD0_CRG_BND_VD0002_O26A0_T    crg_bnd_vd0002;     // 0xCE52_1008
    BCRG_CTRL_VD0_CRG_BND_VD0003_O26A0_T    crg_bnd_vd0003;     // 0xCE52_100C
    BCRG_CTRL_VD0_CRG_BND_VD0004_O26A0_T    crg_bnd_vd0004;     // 0xCE52_1010
}BCRG_CTRL_VD0_REG_O26A0_T;
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

#define BCRG_CTRL_VD0_CRG_BND_VD0000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_VD0_CRG_BND_VD0001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_VD0_CRG_BND_VD0002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_VD0_CRG_BND_VD0003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_VD0_CRG_BND_VD0004_O26A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCE52_1000    crg_bnd_vd0000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_VD0_CRG_BND_VD0000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_1004    crg_bnd_vd0001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_VD0_CRG_BND_VD0001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_1008    crg_bnd_vd0002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_vd0_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD0002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_100C    crg_bnd_vd0003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_icod_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_lnx2_0_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_venc_0_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD0003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE52_1010    crg_bnd_vd0004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_vd0_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_VD0_CRG_BND_VD0004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_VD0_CRG_BND_VD0000_O26A0_T    crg_bnd_vd0000;     // 0xCE52_1000
    BCRG_CTRL_VD0_CRG_BND_VD0001_O26A0_T    crg_bnd_vd0001;     // 0xCE52_1004
    BCRG_CTRL_VD0_CRG_BND_VD0002_O26A0_T    crg_bnd_vd0002;     // 0xCE52_1008
    BCRG_CTRL_VD0_CRG_BND_VD0003_O26A0_T    crg_bnd_vd0003;     // 0xCE52_100C
    BCRG_CTRL_VD0_CRG_BND_VD0004_O26A0_T    crg_bnd_vd0004;     // 0xCE52_1010
}BCRG_CTRL_VD0_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_VD0_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

