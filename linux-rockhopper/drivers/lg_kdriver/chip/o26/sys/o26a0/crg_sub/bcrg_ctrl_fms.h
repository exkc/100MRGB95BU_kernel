#ifndef _BCRG_CTRL_FMS_REG_O26A0_H_
#define _BCRG_CTRL_FMS_REG_O26A0_H_

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
    0xCC32_1000    crg_bnd_fms000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_FMS_CRG_BND_FMS000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_1004    crg_bnd_fms001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_FMS_CRG_BND_FMS001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_1008    crg_bnd_fms002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_fms_clk_gate_en: 1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_100C    crg_bnd_fms003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_dbb_0_n: 1,    //    0
    reg_soft_rst_f_tp_int_n   :  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_1010    crg_bnd_fms004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_fms_n:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_FMS_CRG_BND_FMS004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMS_CRG_BND_FMS000_O26A0_T    crg_bnd_fms000;     // 0xCC32_1000
    BCRG_CTRL_FMS_CRG_BND_FMS001_O26A0_T    crg_bnd_fms001;     // 0xCC32_1004
    BCRG_CTRL_FMS_CRG_BND_FMS002_O26A0_T    crg_bnd_fms002;     // 0xCC32_1008
    BCRG_CTRL_FMS_CRG_BND_FMS003_O26A0_T    crg_bnd_fms003;     // 0xCC32_100C
    BCRG_CTRL_FMS_CRG_BND_FMS004_O26A0_T    crg_bnd_fms004;     // 0xCC32_1010
}BCRG_CTRL_FMS_REG_O26A0_T;
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

#define BCRG_CTRL_FMS_CRG_BND_FMS000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_FMS_CRG_BND_FMS001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_FMS_CRG_BND_FMS002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_FMS_CRG_BND_FMS003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_FMS_CRG_BND_FMS004_O26A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC32_1000    crg_bnd_fms000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_FMS_CRG_BND_FMS000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_1004    crg_bnd_fms001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_FMS_CRG_BND_FMS001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_1008    crg_bnd_fms002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_fms_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_100C    crg_bnd_fms003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_dbb_0_n: 1;    //  0
    UINT32 reg_soft_rst_f_tp_int_n: 1;    //   1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_1010    crg_bnd_fms004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_fms_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_FMS_CRG_BND_FMS004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_FMS_CRG_BND_FMS000_O26A0_T    crg_bnd_fms000;     // 0xCC32_1000
    BCRG_CTRL_FMS_CRG_BND_FMS001_O26A0_T    crg_bnd_fms001;     // 0xCC32_1004
    BCRG_CTRL_FMS_CRG_BND_FMS002_O26A0_T    crg_bnd_fms002;     // 0xCC32_1008
    BCRG_CTRL_FMS_CRG_BND_FMS003_O26A0_T    crg_bnd_fms003;     // 0xCC32_100C
    BCRG_CTRL_FMS_CRG_BND_FMS004_O26A0_T    crg_bnd_fms004;     // 0xCC32_1010
}BCRG_CTRL_FMS_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_FMS_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

