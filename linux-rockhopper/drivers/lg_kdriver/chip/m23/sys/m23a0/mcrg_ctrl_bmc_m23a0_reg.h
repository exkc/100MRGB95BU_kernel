#ifndef _MCRG_CTRL_BMC_M23A0_REG_H_
#define _MCRG_CTRL_BMC_M23A0_REG_H_

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
    0xC615_0000    crg_main_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_BMC_CRG_MAIN_BMC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_0004    crg_main_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_BMC_CRG_MAIN_BMC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_0008    crg_main_bmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bmc_phy3_hdmi_link_clk_inv_sel: 1,    //  0
    reg_bmc_phy4_hdmi_link_clk_inv_sel: 1,    //  1
                              : 30;    //   31:2 reserved
}MCRG_CTRL_BMC_CRG_MAIN_BMC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_BMC_CRG_MAIN_BMC00_M23A0_T    crg_main_bmc00;     // 0xC615_0000
    MCRG_CTRL_BMC_CRG_MAIN_BMC01_M23A0_T    crg_main_bmc01;     // 0xC615_0004
    MCRG_CTRL_BMC_CRG_MAIN_BMC02_M23A0_T    crg_main_bmc02;     // 0xC615_0008
}MCRG_CTRL_BMC_REG_M23A0_T;
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

#define MCRG_CTRL_BMC_CRG_MAIN_BMC00_M23A0_T_OFF            (BASEADDRESS+0x0000)
#define MCRG_CTRL_BMC_CRG_MAIN_BMC01_M23A0_T_OFF            (BASEADDRESS+0x0004)
#define MCRG_CTRL_BMC_CRG_MAIN_BMC02_M23A0_T_OFF            (BASEADDRESS+0x0008)

/*-----------------------------------------------------------------------------------------
    0xC615_0000    crg_main_bmc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_BMC_CRG_MAIN_BMC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_0004    crg_main_bmc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_BMC_CRG_MAIN_BMC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_0008    crg_main_bmc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bmc_phy3_hdmi_link_clk_inv_sel: 1;    //  0
    UINT32 reg_bmc_phy4_hdmi_link_clk_inv_sel: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MCRG_CTRL_BMC_CRG_MAIN_BMC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mcrg_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_BMC_CRG_MAIN_BMC00_M23A0_T    crg_main_bmc00;     // 0xC615_0000
    MCRG_CTRL_BMC_CRG_MAIN_BMC01_M23A0_T    crg_main_bmc01;     // 0xC615_0004
    MCRG_CTRL_BMC_CRG_MAIN_BMC02_M23A0_T    crg_main_bmc02;     // 0xC615_0008
}MCRG_CTRL_BMC_REG_M23A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

