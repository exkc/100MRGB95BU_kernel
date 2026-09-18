#ifndef _CPU_MCRG_CTRL_WOC_M23A0_REG_H_
#define _CPU_MCRG_CTRL_WOC_M23A0_REG_H_

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
    0xC851_0000    crg_main_woc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC851_0004    crg_main_woc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC851_0008    crg_main_woc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_woc_gmac_rx_clk_inv_sel: 1,    //      0
    reg_woc_gmac_tx_clk_inv_sel: 1,    //      1
                              : 30;    //   31:2 reserved
}CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_mcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC00_M23A0_T    crg_main_woc00;    // 0xC851_0000
    CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC01_M23A0_T    crg_main_woc01;    // 0xC851_0004
    CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC02_M23A0_T    crg_main_woc02;    // 0xC851_0008
}CPU_MCRG_CTRL_WOC_REG_M23A0_T;
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

#define CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC00_M23A0_T_OFF        (BASEADDRESS+0x0000)
#define CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC01_M23A0_T_OFF        (BASEADDRESS+0x0004)
#define CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC02_M23A0_T_OFF        (BASEADDRESS+0x0008)

/*-----------------------------------------------------------------------------------------
    0xC851_0000    crg_main_woc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC851_0004    crg_main_woc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC851_0008    crg_main_woc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_woc_gmac_rx_clk_inv_sel: 1;    //  0
    UINT32 reg_woc_gmac_tx_clk_inv_sel: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_mcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC00_M23A0_T    crg_main_woc00;    // 0xC851_0000
    CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC01_M23A0_T    crg_main_woc01;    // 0xC851_0004
    CPU_MCRG_CTRL_WOC_CRG_MAIN_WOC02_M23A0_T    crg_main_woc02;    // 0xC851_0008
}CPU_MCRG_CTRL_WOC_REG_M23A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

