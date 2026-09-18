#ifndef _SCRG_CTRL_EPHY_M23A0_REG_H_
#define _SCRG_CTRL_EPHY_M23A0_REG_H_

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
    0xF315_0000    crg_ephy00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_EPHY_CRG_EPHY00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF315_0004    crg_ephy01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_EPHY_CRG_EPHY01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF315_0008    crg_ephy02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_ephy_xtal_clk_gate_en :  1,    //      1
    reg_gmac_axi_clk_gate_en  :  1,    //      2
    reg_gmac_rx_clk_gate_en   :  1,    //      3
    reg_gmac_tx_clk_gate_en   :  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_EPHY_CRG_EPHY02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF315_000C    crg_ephy03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_ephy_ctrl_n  :  1,    //      1
    reg_soft_rst_ephy_n       :  1,    //      2
    reg_soft_rst_gmac_axi_n   :  1,    //      3
    reg_soft_rst_gmac_ctrl_n  :  1,    //      4
    reg_soft_rst_p_ephy_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_ephy_0_axi_bnd_n: 1,    //  6
    reg_soft_rst_x_ephy_0_axi_n: 1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_EPHY_CRG_EPHY03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ephy Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EPHY_CRG_EPHY00_M23A0_T    crg_ephy00;            // 0xF315_0000
    SCRG_CTRL_EPHY_CRG_EPHY01_M23A0_T    crg_ephy01;            // 0xF315_0004
    SCRG_CTRL_EPHY_CRG_EPHY02_M23A0_T    crg_ephy02;            // 0xF315_0008
    SCRG_CTRL_EPHY_CRG_EPHY03_M23A0_T    crg_ephy03;            // 0xF315_000C
}SCRG_CTRL_EPHY_REG_M23A0_T;
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

#define SCRG_CTRL_EPHY_CRG_EPHY00_M23A0_T_OFF               (BASEADDRESS+0x0000)
#define SCRG_CTRL_EPHY_CRG_EPHY01_M23A0_T_OFF               (BASEADDRESS+0x0004)
#define SCRG_CTRL_EPHY_CRG_EPHY02_M23A0_T_OFF               (BASEADDRESS+0x0008)
#define SCRG_CTRL_EPHY_CRG_EPHY03_M23A0_T_OFF               (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xF315_0000    crg_ephy00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_EPHY_CRG_EPHY00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF315_0004    crg_ephy01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_EPHY_CRG_EPHY01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF315_0008    crg_ephy02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_ephy_xtal_clk_gate_en: 1;    //  1
    UINT32 reg_gmac_axi_clk_gate_en: 1;    //  2
    UINT32 reg_gmac_rx_clk_gate_en: 1;    //   3
    UINT32 reg_gmac_tx_clk_gate_en: 1;    //   4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_EPHY_CRG_EPHY02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF315_000C    crg_ephy03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_ephy_ctrl_n: 1;    //  1
    UINT32 reg_soft_rst_ephy_n:  1;    //      2
    UINT32 reg_soft_rst_gmac_axi_n: 1;    //   3
    UINT32 reg_soft_rst_gmac_ctrl_n: 1;    //  4
    UINT32 reg_soft_rst_p_ephy_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_ephy_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_ephy_0_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_EPHY_CRG_EPHY03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_ephy Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EPHY_CRG_EPHY00_M23A0_T    crg_ephy00;            // 0xF315_0000
    SCRG_CTRL_EPHY_CRG_EPHY01_M23A0_T    crg_ephy01;            // 0xF315_0004
    SCRG_CTRL_EPHY_CRG_EPHY02_M23A0_T    crg_ephy02;            // 0xF315_0008
    SCRG_CTRL_EPHY_CRG_EPHY03_M23A0_T    crg_ephy03;            // 0xF315_000C
}SCRG_CTRL_EPHY_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

