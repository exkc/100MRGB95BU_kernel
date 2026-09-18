#ifndef _MICOM_MCRG_CTRL_WOC_REG_O24A0_H_
#define _MICOM_MCRG_CTRL_WOC_REG_O24A0_H_

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
    0xC63F_0000    crg_main_woc0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_0004    crg_main_woc1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    micom_mcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC0_O24A0_T    crg_main_woc0;    // 0xC63F_0000
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC1_O24A0_T    crg_main_woc1;    // 0xC63F_0004
}MICOM_MCRG_CTRL_WOC_REG_O24A0_T;
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

#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC0_O24A0_T_OFF       (BASEADDRESS+0x0000)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC1_O24A0_T_OFF       (BASEADDRESS+0x0004)

/*-----------------------------------------------------------------------------------------
    0xC63F_0000    crg_main_woc0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_0004    crg_main_woc1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    micom_mcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC0_O24A0_T    crg_main_woc0;    // 0xC63F_0000
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC1_O24A0_T    crg_main_woc1;    // 0xC63F_0004
}MICOM_MCRG_CTRL_WOC_REG_O24A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MICOM_MCRG_CTRL_WOC_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

