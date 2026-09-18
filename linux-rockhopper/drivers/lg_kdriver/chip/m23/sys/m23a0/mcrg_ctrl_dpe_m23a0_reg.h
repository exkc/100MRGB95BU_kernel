#ifndef _MCRG_CTRL_DPE_M23A0_REG_H_
#define _MCRG_CTRL_DPE_M23A0_REG_H_

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
    0xCC53_0000    crg_main_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_DPE_CRG_MAIN_DPE00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_0004    crg_main_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_DPE_CRG_MAIN_DPE01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_DPE_CRG_MAIN_DPE00_M23A0_T    crg_main_dpe00;     // 0xCC53_0000
    MCRG_CTRL_DPE_CRG_MAIN_DPE01_M23A0_T    crg_main_dpe01;     // 0xCC53_0004
}MCRG_CTRL_DPE_REG_M23A0_T;
/* 2 regs */

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

#define MCRG_CTRL_DPE_CRG_MAIN_DPE00_M23A0_T_OFF            (BASEADDRESS+0x0000)
#define MCRG_CTRL_DPE_CRG_MAIN_DPE01_M23A0_T_OFF            (BASEADDRESS+0x0004)

/*-----------------------------------------------------------------------------------------
    0xCC53_0000    crg_main_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_DPE_CRG_MAIN_DPE00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_0004    crg_main_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_DPE_CRG_MAIN_DPE01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_DPE_CRG_MAIN_DPE00_M23A0_T    crg_main_dpe00;     // 0xCC53_0000
    MCRG_CTRL_DPE_CRG_MAIN_DPE01_M23A0_T    crg_main_dpe01;     // 0xCC53_0004
}MCRG_CTRL_DPE_REG_M23A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

