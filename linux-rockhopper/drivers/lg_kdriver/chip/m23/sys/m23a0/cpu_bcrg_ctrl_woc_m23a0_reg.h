#ifndef _CPU_BCRG_CTRL_WOC_M23A0_REG_H_
#define _CPU_BCRG_CTRL_WOC_M23A0_REG_H_

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
    0xC851_1000    crg_bnd_woc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}CPU_BCRG_CTRL_WOC_CRG_BND_WOC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC851_1004    crg_bnd_woc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}CPU_BCRG_CTRL_WOC_CRG_BND_WOC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC851_1008    crg_bnd_woc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_edid1_clk_gate_en: 1,    //    0
    reg_apb_ipw_ephy_clk_gate_en: 1,    //     1
    reg_apb_ipw_micom_clk_gate_en: 1,    //    2
    reg_apb_ipw_pdm_clk_gate_en: 1,    //      3
    reg_micom_cm0p_clk_gate_en:  1,    //      4
                              : 27;    //   31:5 reserved
}CPU_BCRG_CTRL_WOC_CRG_BND_WOC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC851_100C    crg_bnd_woc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_edid1_n: 1,    //     0
    reg_soft_rst_apb_ipw_ephy_n: 1,    //      1
    reg_soft_rst_apb_ipw_micom_n: 1,    //     2
    reg_soft_rst_apb_ipw_pdm_n:  1,    //      3
                              : 28;    //   31:4 reserved
}CPU_BCRG_CTRL_WOC_CRG_BND_WOC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_bcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_BCRG_CTRL_WOC_CRG_BND_WOC00_M23A0_T    crg_bnd_woc00;    // 0xC851_1000
    CPU_BCRG_CTRL_WOC_CRG_BND_WOC01_M23A0_T    crg_bnd_woc01;    // 0xC851_1004
    CPU_BCRG_CTRL_WOC_CRG_BND_WOC02_M23A0_T    crg_bnd_woc02;    // 0xC851_1008
    CPU_BCRG_CTRL_WOC_CRG_BND_WOC03_M23A0_T    crg_bnd_woc03;    // 0xC851_100C
}CPU_BCRG_CTRL_WOC_REG_M23A0_T;
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

#define CPU_BCRG_CTRL_WOC_CRG_BND_WOC00_M23A0_T_OFF         (BASEADDRESS+0x0000)
#define CPU_BCRG_CTRL_WOC_CRG_BND_WOC01_M23A0_T_OFF         (BASEADDRESS+0x0004)
#define CPU_BCRG_CTRL_WOC_CRG_BND_WOC02_M23A0_T_OFF         (BASEADDRESS+0x0008)
#define CPU_BCRG_CTRL_WOC_CRG_BND_WOC03_M23A0_T_OFF         (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC851_1000    crg_bnd_woc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}CPU_BCRG_CTRL_WOC_CRG_BND_WOC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC851_1004    crg_bnd_woc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}CPU_BCRG_CTRL_WOC_CRG_BND_WOC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC851_1008    crg_bnd_woc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_edid1_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_ephy_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_micom_clk_gate_en: 1;    //  2
    UINT32 reg_apb_ipw_pdm_clk_gate_en: 1;    //  3
    UINT32 reg_micom_cm0p_clk_gate_en: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}CPU_BCRG_CTRL_WOC_CRG_BND_WOC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC851_100C    crg_bnd_woc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_edid1_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_ephy_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_micom_n: 1;    //  2
    UINT32 reg_soft_rst_apb_ipw_pdm_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}CPU_BCRG_CTRL_WOC_CRG_BND_WOC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_bcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_BCRG_CTRL_WOC_CRG_BND_WOC00_M23A0_T    crg_bnd_woc00;    // 0xC851_1000
    CPU_BCRG_CTRL_WOC_CRG_BND_WOC01_M23A0_T    crg_bnd_woc01;    // 0xC851_1004
    CPU_BCRG_CTRL_WOC_CRG_BND_WOC02_M23A0_T    crg_bnd_woc02;    // 0xC851_1008
    CPU_BCRG_CTRL_WOC_CRG_BND_WOC03_M23A0_T    crg_bnd_woc03;    // 0xC851_100C
}CPU_BCRG_CTRL_WOC_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

