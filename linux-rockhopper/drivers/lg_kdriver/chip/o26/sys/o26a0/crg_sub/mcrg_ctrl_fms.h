#ifndef _MCRG_CTRL_FMS_REG_O26A0_H_
#define _MCRG_CTRL_FMS_REG_O26A0_H_

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
    0xCC32_0000    crg_main_fms000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_FMS_CRG_MAIN_FMS000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_0004    crg_main_fms001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_FMS_CRG_MAIN_FMS001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_0008    crg_main_fms002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fms_tpi_int_clk_inv_sel: 1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_FMS_CRG_MAIN_FMS002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_FMS_CRG_MAIN_FMS000_O26A0_T    crg_main_fms000;    // 0xCC32_0000
    MCRG_CTRL_FMS_CRG_MAIN_FMS001_O26A0_T    crg_main_fms001;    // 0xCC32_0004
    MCRG_CTRL_FMS_CRG_MAIN_FMS002_O26A0_T    crg_main_fms002;    // 0xCC32_0008
}MCRG_CTRL_FMS_REG_O26A0_T;
/* 3 regs */

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

#define MCRG_CTRL_FMS_CRG_MAIN_FMS000_O26A0_T_OFF           (BASEADDRESS+0x0000)
#define MCRG_CTRL_FMS_CRG_MAIN_FMS001_O26A0_T_OFF           (BASEADDRESS+0x0004)
#define MCRG_CTRL_FMS_CRG_MAIN_FMS002_O26A0_T_OFF           (BASEADDRESS+0x0008)

/*-----------------------------------------------------------------------------------------
    0xCC32_0000    crg_main_fms000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_FMS_CRG_MAIN_FMS000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_0004    crg_main_fms001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_FMS_CRG_MAIN_FMS001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC32_0008    crg_main_fms002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fms_tpi_int_clk_inv_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_FMS_CRG_MAIN_FMS002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_FMS_CRG_MAIN_FMS000_O26A0_T    crg_main_fms000;    // 0xCC32_0000
    MCRG_CTRL_FMS_CRG_MAIN_FMS001_O26A0_T    crg_main_fms001;    // 0xCC32_0004
    MCRG_CTRL_FMS_CRG_MAIN_FMS002_O26A0_T    crg_main_fms002;    // 0xCC32_0008
}MCRG_CTRL_FMS_REG_O26A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MCRG_CTRL_FMS_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

