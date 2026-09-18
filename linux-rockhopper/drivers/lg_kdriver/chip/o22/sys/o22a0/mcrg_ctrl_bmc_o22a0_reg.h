#ifndef _MCRG_CTRL_BMC_REG_H_
#define _MCRG_CTRL_BMC_REG_H_

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
    0x0    crg_main_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_BMC_CRG_MAIN_BMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    crg_main_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_BMC_CRG_MAIN_BMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_main_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_BMC_CRG_MAIN_BMC00_O22A0_T    crg_main_bmc00;      // 0x0
    MCRG_CTRL_BMC_CRG_MAIN_BMC01_O22A0_T    crg_main_bmc01;      // 0x4
}MCRG_CTRL_BMC_REG_O22A0_T;
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

#define MCRG_CTRL_BMC_CRG_MAIN_BMC00_O22A0_T_OFF             (BASEADDRESS+0x0000)
#define MCRG_CTRL_BMC_CRG_MAIN_BMC01_O22A0_T_OFF             (BASEADDRESS+0x0004)

/*-----------------------------------------------------------------------------------------
    0x0    crg_main_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_BMC_CRG_MAIN_BMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    crg_main_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_BMC_CRG_MAIN_BMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_main_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_BMC_CRG_MAIN_BMC00_O22A0_T    crg_main_bmc00;      // 0x0
    MCRG_CTRL_BMC_CRG_MAIN_BMC01_O22A0_T    crg_main_bmc01;      // 0x4
}MCRG_CTRL_BMC_REG_O22A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

