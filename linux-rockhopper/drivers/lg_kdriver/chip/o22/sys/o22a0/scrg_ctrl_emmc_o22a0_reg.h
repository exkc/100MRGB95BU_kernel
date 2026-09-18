#ifndef _SCRG_CTRL_EMMC_REG_H_
#define _SCRG_CTRL_EMMC_REG_H_

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
    0x29_0000    crg_emmc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_EMMC_CRG_EMMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x29_0004    crg_emmc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_EMMC_CRG_EMMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x29_0008    crg_emmc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_core_clk_gate_en :  1,    //      0
    reg_emmc_tm_clk_gate_en   :  1,    //      1
    reg_emmc_tx_clk_gate_en   :  1,    //      2
    reg_emmc_tx_inv_clk_gate_en: 1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_EMMC_CRG_EMMC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x29_000C    crg_emmc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_emmc_core_n  :  1,    //      0
    reg_soft_rst_emmc_tm_n    :  1,    //      1
    reg_soft_rst_emmc_tx_inv_n:  1,    //      2
    reg_soft_rst_emmc_tx_n    :  1,    //      3
    reg_soft_rst_p_emmc_0_axi_bnd_n: 1,    //  4
    reg_soft_rst_x_emmc_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_emmc_0_axi_n: 1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_EMMC_CRG_EMMC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_emmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EMMC_CRG_EMMC00_O22A0_T        crg_emmc00 ;             // 0x29_0000
    SCRG_CTRL_EMMC_CRG_EMMC01_O22A0_T        crg_emmc01 ;             // 0x29_0004
    SCRG_CTRL_EMMC_CRG_EMMC02_O22A0_T        crg_emmc02 ;             // 0x29_0008
    SCRG_CTRL_EMMC_CRG_EMMC03_O22A0_T        crg_emmc03 ;             // 0x29_000C
}SCRG_CTRL_EMMC_REG_O22A0_T;
/* 4 regs */

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

#define SCRG_CTRL_EMMC_CRG_EMMC00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define SCRG_CTRL_EMMC_CRG_EMMC01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define SCRG_CTRL_EMMC_CRG_EMMC02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define SCRG_CTRL_EMMC_CRG_EMMC03_O22A0_T_OFF                     (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0x29_0000    crg_emmc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_EMMC_CRG_EMMC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x29_0004    crg_emmc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_EMMC_CRG_EMMC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x29_0008    crg_emmc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_core_clk_gate_en: 1;    //  0
    UINT32 reg_emmc_tm_clk_gate_en: 1;    //   1
    UINT32 reg_emmc_tx_clk_gate_en: 1;    //   2
    UINT32 reg_emmc_tx_inv_clk_gate_en: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_EMMC_CRG_EMMC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x29_000C    crg_emmc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_emmc_core_n: 1;    //  0
    UINT32 reg_soft_rst_emmc_tm_n: 1;    //    1
    UINT32 reg_soft_rst_emmc_tx_inv_n: 1;    //  2
    UINT32 reg_soft_rst_emmc_tx_n: 1;    //    3
    UINT32 reg_soft_rst_p_emmc_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_emmc_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_emmc_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_EMMC_CRG_EMMC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_emmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EMMC_CRG_EMMC00_O22A0_T        crg_emmc00 ;             // 0x29_0000
    SCRG_CTRL_EMMC_CRG_EMMC01_O22A0_T        crg_emmc01 ;             // 0x29_0004
    SCRG_CTRL_EMMC_CRG_EMMC02_O22A0_T        crg_emmc02 ;             // 0x29_0008
    SCRG_CTRL_EMMC_CRG_EMMC03_O22A0_T        crg_emmc03 ;             // 0x29_000C
}SCRG_CTRL_EMMC_REG_O22A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

