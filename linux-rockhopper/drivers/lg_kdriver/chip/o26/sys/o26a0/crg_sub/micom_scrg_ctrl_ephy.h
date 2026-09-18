#ifndef _MICOM_SCRG_CTRL_EPHY_REG_O26A0_H_
#define _MICOM_SCRG_CTRL_EPHY_REG_O26A0_H_

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
    0xF338_0000    crg_ephy000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MICOM_SCRG_CTRL_EPHY_CRG_EPHY000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF338_0004    crg_ephy001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MICOM_SCRG_CTRL_EPHY_CRG_EPHY001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF338_0008    crg_ephy002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_ephy_0__gmac_axi_clk_gate_en: 1,    //  0
    reg_apb_clk_gate_en       :  1,    //      1
    reg_ephy_xtal_clk_gate_en :  1,    //      2
    reg_gmac_axi_clk_gate_en  :  1,    //      3
    reg_gmac_rx_clk_gate_en   :  1,    //      4
    reg_gmac_tx_clk_gate_en   :  1,    //      5
                              : 26;    //   31:6 reserved
}MICOM_SCRG_CTRL_EPHY_CRG_EPHY002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF338_000C    crg_ephy003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_ephy_ctrl_n  :  1,    //      1
    reg_soft_rst_ephy_n       :  1,    //      2
    reg_soft_rst_gmac_axi_n   :  1,    //      3
    reg_soft_rst_gmac_ctrl_n  :  1,    //      4
    reg_soft_rst_p_ephy_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_ephy_0_axi_n: 1,    //      6
                              : 25;    //   31:7 reserved
}MICOM_SCRG_CTRL_EPHY_CRG_EPHY003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_scrg_ctrl_ephy Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_SCRG_CTRL_EPHY_CRG_EPHY000_O26A0_T    crg_ephy000;    // 0xF338_0000
    MICOM_SCRG_CTRL_EPHY_CRG_EPHY001_O26A0_T    crg_ephy001;    // 0xF338_0004
    MICOM_SCRG_CTRL_EPHY_CRG_EPHY002_O26A0_T    crg_ephy002;    // 0xF338_0008
    MICOM_SCRG_CTRL_EPHY_CRG_EPHY003_O26A0_T    crg_ephy003;    // 0xF338_000C
}MICOM_SCRG_CTRL_EPHY_REG_O26A0_T;
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

#define MICOM_SCRG_CTRL_EPHY_CRG_EPHY000_O26A0_T_OFF        (BASEADDRESS+0x0000)
#define MICOM_SCRG_CTRL_EPHY_CRG_EPHY001_O26A0_T_OFF        (BASEADDRESS+0x0004)
#define MICOM_SCRG_CTRL_EPHY_CRG_EPHY002_O26A0_T_OFF        (BASEADDRESS+0x0008)
#define MICOM_SCRG_CTRL_EPHY_CRG_EPHY003_O26A0_T_OFF        (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xF338_0000    crg_ephy000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MICOM_SCRG_CTRL_EPHY_CRG_EPHY000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF338_0004    crg_ephy001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MICOM_SCRG_CTRL_EPHY_CRG_EPHY001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF338_0008    crg_ephy002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_ephy_0__gmac_axi_clk_gate_en: 1;    //  0
    UINT32 reg_apb_clk_gate_en:  1;    //      1
    UINT32 reg_ephy_xtal_clk_gate_en: 1;    //  2
    UINT32 reg_gmac_axi_clk_gate_en: 1;    //  3
    UINT32 reg_gmac_rx_clk_gate_en: 1;    //   4
    UINT32 reg_gmac_tx_clk_gate_en: 1;    //   5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}MICOM_SCRG_CTRL_EPHY_CRG_EPHY002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF338_000C    crg_ephy003 ''
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
    UINT32 reg_soft_rst_x_ephy_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}MICOM_SCRG_CTRL_EPHY_CRG_EPHY003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_scrg_ctrl_ephy Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_SCRG_CTRL_EPHY_CRG_EPHY000_O26A0_T    crg_ephy000;    // 0xF338_0000
    MICOM_SCRG_CTRL_EPHY_CRG_EPHY001_O26A0_T    crg_ephy001;    // 0xF338_0004
    MICOM_SCRG_CTRL_EPHY_CRG_EPHY002_O26A0_T    crg_ephy002;    // 0xF338_0008
    MICOM_SCRG_CTRL_EPHY_CRG_EPHY003_O26A0_T    crg_ephy003;    // 0xF338_000C
}MICOM_SCRG_CTRL_EPHY_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MICOM_SCRG_CTRL_EPHY_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

