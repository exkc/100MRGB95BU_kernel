#ifndef _SCRG_CTRL_TIVVMSB_REG_O26A0_H_
#define _SCRG_CTRL_TIVVMSB_REG_O26A0_H_

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
    0xCE49_0000    crg_tivvmsb000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_TIVVMSB_CRG_TIVVMSB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0004    crg_tivvmsb001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_TIVVMSB_CRG_TIVVMSB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0008    crg_tivvmsb002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_tivsb_0__bus_480_clk_gate_en: 1,    //  0
    reg_adaprx_x_vmcu_0__bus_480_clk_gate_en: 1,    //  1
    reg_adaptx_x_tivvm_0__bus_480_clk_gate_en: 1,    //  2
    reg_bus_480_clk_gate_en   :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_TIVVMSB_CRG_TIVVMSB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_000C    crg_tivvmsb003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_bus_480_n    :  1,    //      0
    reg_soft_rst_p_tivsb_0_axi_bnd_n: 1,    //  1
    reg_soft_rst_p_tivvm_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_p_vmcu_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_x_tivsb_0_axi_n: 1,    //     4
    reg_soft_rst_x_tivvm_0_axi_n: 1,    //     5
    reg_soft_rst_x_vmcu_0_axi_n: 1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_TIVVMSB_CRG_TIVVMSB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_tivvmsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TIVVMSB_CRG_TIVVMSB000_O26A0_T    crg_tivvmsb000;    // 0xCE49_0000
    SCRG_CTRL_TIVVMSB_CRG_TIVVMSB001_O26A0_T    crg_tivvmsb001;    // 0xCE49_0004
    SCRG_CTRL_TIVVMSB_CRG_TIVVMSB002_O26A0_T    crg_tivvmsb002;    // 0xCE49_0008
    SCRG_CTRL_TIVVMSB_CRG_TIVVMSB003_O26A0_T    crg_tivvmsb003;    // 0xCE49_000C
}SCRG_CTRL_TIVVMSB_REG_O26A0_T;
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

#define SCRG_CTRL_TIVVMSB_CRG_TIVVMSB000_O26A0_T_OFF        (BASEADDRESS+0x0000)
#define SCRG_CTRL_TIVVMSB_CRG_TIVVMSB001_O26A0_T_OFF        (BASEADDRESS+0x0004)
#define SCRG_CTRL_TIVVMSB_CRG_TIVVMSB002_O26A0_T_OFF        (BASEADDRESS+0x0008)
#define SCRG_CTRL_TIVVMSB_CRG_TIVVMSB003_O26A0_T_OFF        (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCE49_0000    crg_tivvmsb000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_TIVVMSB_CRG_TIVVMSB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0004    crg_tivvmsb001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_TIVVMSB_CRG_TIVVMSB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_0008    crg_tivvmsb002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_tivsb_0__bus_480_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_x_vmcu_0__bus_480_clk_gate_en: 1;    //  1
    UINT32 reg_adaptx_x_tivvm_0__bus_480_clk_gate_en: 1;    //  2
    UINT32 reg_bus_480_clk_gate_en: 1;    //   3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_TIVVMSB_CRG_TIVVMSB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE49_000C    crg_tivvmsb003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_bus_480_n: 1;    //    0
    UINT32 reg_soft_rst_p_tivsb_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_tivvm_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_vmcu_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_tivsb_0_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_tivvm_0_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_vmcu_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_TIVVMSB_CRG_TIVVMSB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_tivvmsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TIVVMSB_CRG_TIVVMSB000_O26A0_T    crg_tivvmsb000;    // 0xCE49_0000
    SCRG_CTRL_TIVVMSB_CRG_TIVVMSB001_O26A0_T    crg_tivvmsb001;    // 0xCE49_0004
    SCRG_CTRL_TIVVMSB_CRG_TIVVMSB002_O26A0_T    crg_tivvmsb002;    // 0xCE49_0008
    SCRG_CTRL_TIVVMSB_CRG_TIVVMSB003_O26A0_T    crg_tivvmsb003;    // 0xCE49_000C
}SCRG_CTRL_TIVVMSB_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_TIVVMSB_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

