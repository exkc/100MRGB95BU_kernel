#ifndef _MCRG_CTRL_HDR_REG_O26A0_H_
#define _MCRG_CTRL_HDR_REG_O26A0_H_

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
    0xCC27_0000    crg_main_hdr000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_HDR_CRG_MAIN_HDR000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_0004    crg_main_hdr001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_HDR_CRG_MAIN_HDR001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_HDR_CRG_MAIN_HDR000_O26A0_T    crg_main_hdr000;    // 0xCC27_0000
    MCRG_CTRL_HDR_CRG_MAIN_HDR001_O26A0_T    crg_main_hdr001;    // 0xCC27_0004
}MCRG_CTRL_HDR_REG_O26A0_T;
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

#define MCRG_CTRL_HDR_CRG_MAIN_HDR000_O26A0_T_OFF           (BASEADDRESS+0x0000)
#define MCRG_CTRL_HDR_CRG_MAIN_HDR001_O26A0_T_OFF           (BASEADDRESS+0x0004)

/*-----------------------------------------------------------------------------------------
    0xCC27_0000    crg_main_hdr000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_HDR_CRG_MAIN_HDR000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC27_0004    crg_main_hdr001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_HDR_CRG_MAIN_HDR001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_HDR_CRG_MAIN_HDR000_O26A0_T    crg_main_hdr000;    // 0xCC27_0000
    MCRG_CTRL_HDR_CRG_MAIN_HDR001_O26A0_T    crg_main_hdr001;    // 0xCC27_0004
}MCRG_CTRL_HDR_REG_O26A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MCRG_CTRL_HDR_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

