#ifndef _SCRG_CTRL_SRCOSB_REG_O26A0_H_
#define _SCRG_CTRL_SRCOSB_REG_O26A0_H_

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
    0xCCD1_0000    crg_srcosb000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_SRCOSB_CRG_SRCOSB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD1_0004    crg_srcosb001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_SRCOSB_CRG_SRCOSB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD1_0008    crg_srcosb002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_cco_0__bus_884_clk_gate_en: 1,    //  0
    reg_adaprx_x_sre_1__bus_884_clk_gate_en: 1,    //  1
    reg_adaptx_x_srco_0__bus_884_clk_gate_en: 1,    //  2
    reg_bus_884_clk_gate_en   :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_SRCOSB_CRG_SRCOSB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD1_000C    crg_srcosb003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_bus_884_n    :  1,    //      0
    reg_soft_rst_p_cco_0_axi_bnd_n: 1,    //   1
    reg_soft_rst_p_srco_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_p_sre_1_axi_bnd_n: 1,    //   3
    reg_soft_rst_x_cco_0_axi_n:  1,    //      4
    reg_soft_rst_x_srco_0_axi_n: 1,    //      5
    reg_soft_rst_x_sre_1_axi_n:  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_SRCOSB_CRG_SRCOSB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_srcosb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SRCOSB_CRG_SRCOSB000_O26A0_T    crg_srcosb000;    // 0xCCD1_0000
    SCRG_CTRL_SRCOSB_CRG_SRCOSB001_O26A0_T    crg_srcosb001;    // 0xCCD1_0004
    SCRG_CTRL_SRCOSB_CRG_SRCOSB002_O26A0_T    crg_srcosb002;    // 0xCCD1_0008
    SCRG_CTRL_SRCOSB_CRG_SRCOSB003_O26A0_T    crg_srcosb003;    // 0xCCD1_000C
}SCRG_CTRL_SRCOSB_REG_O26A0_T;
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

#define SCRG_CTRL_SRCOSB_CRG_SRCOSB000_O26A0_T_OFF          (BASEADDRESS+0x0000)
#define SCRG_CTRL_SRCOSB_CRG_SRCOSB001_O26A0_T_OFF          (BASEADDRESS+0x0004)
#define SCRG_CTRL_SRCOSB_CRG_SRCOSB002_O26A0_T_OFF          (BASEADDRESS+0x0008)
#define SCRG_CTRL_SRCOSB_CRG_SRCOSB003_O26A0_T_OFF          (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCD1_0000    crg_srcosb000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_SRCOSB_CRG_SRCOSB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD1_0004    crg_srcosb001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_SRCOSB_CRG_SRCOSB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD1_0008    crg_srcosb002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_cco_0__bus_884_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_x_sre_1__bus_884_clk_gate_en: 1;    //  1
    UINT32 reg_adaptx_x_srco_0__bus_884_clk_gate_en: 1;    //  2
    UINT32 reg_bus_884_clk_gate_en: 1;    //   3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_SRCOSB_CRG_SRCOSB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD1_000C    crg_srcosb003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_bus_884_n: 1;    //    0
    UINT32 reg_soft_rst_p_cco_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_srco_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_sre_1_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_cco_0_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_srco_0_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_sre_1_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_SRCOSB_CRG_SRCOSB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_srcosb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_SRCOSB_CRG_SRCOSB000_O26A0_T    crg_srcosb000;    // 0xCCD1_0000
    SCRG_CTRL_SRCOSB_CRG_SRCOSB001_O26A0_T    crg_srcosb001;    // 0xCCD1_0004
    SCRG_CTRL_SRCOSB_CRG_SRCOSB002_O26A0_T    crg_srcosb002;    // 0xCCD1_0008
    SCRG_CTRL_SRCOSB_CRG_SRCOSB003_O26A0_T    crg_srcosb003;    // 0xCCD1_000C
}SCRG_CTRL_SRCOSB_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_SRCOSB_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

