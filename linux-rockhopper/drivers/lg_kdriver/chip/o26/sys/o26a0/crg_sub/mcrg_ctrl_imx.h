#ifndef _MCRG_CTRL_IMX_REG_O26A0_H_
#define _MCRG_CTRL_IMX_REG_O26A0_H_

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
    0xCCC3_0000    crg_main_imx000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_IMX_CRG_MAIN_IMX000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_0004    crg_main_imx001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_IMX_CRG_MAIN_IMX001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_IMX_CRG_MAIN_IMX000_O26A0_T    crg_main_imx000;    // 0xCCC3_0000
    MCRG_CTRL_IMX_CRG_MAIN_IMX001_O26A0_T    crg_main_imx001;    // 0xCCC3_0004
}MCRG_CTRL_IMX_REG_O26A0_T;
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

#define MCRG_CTRL_IMX_CRG_MAIN_IMX000_O26A0_T_OFF           (BASEADDRESS+0x0000)
#define MCRG_CTRL_IMX_CRG_MAIN_IMX001_O26A0_T_OFF           (BASEADDRESS+0x0004)

/*-----------------------------------------------------------------------------------------
    0xCCC3_0000    crg_main_imx000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_IMX_CRG_MAIN_IMX000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC3_0004    crg_main_imx001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_IMX_CRG_MAIN_IMX001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_IMX_CRG_MAIN_IMX000_O26A0_T    crg_main_imx000;    // 0xCCC3_0000
    MCRG_CTRL_IMX_CRG_MAIN_IMX001_O26A0_T    crg_main_imx001;    // 0xCCC3_0004
}MCRG_CTRL_IMX_REG_O26A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MCRG_CTRL_IMX_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

