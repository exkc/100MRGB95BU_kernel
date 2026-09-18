#ifndef _SCRG_CTRL_DMCU_REG_O26A0_H_
#define _SCRG_CTRL_DMCU_REG_O26A0_H_

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
    0xCA3B_0000    crg_dmcu000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DMCU_CRG_DMCU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3B_0004    crg_dmcu001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DMCU_CRG_DMCU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3B_0008    crg_dmcu002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_cpu_3__ss_clk_gate_en: 1,    //  0
    reg_adaptx_x_dmcu_0__ss_clk_gate_en: 1,    //  1
    reg_apb_clk_gate_en       :  1,    //      2
    reg_mc_clk_gate_en        :  1,    //      3
    reg_ss_clk_gate_en        :  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_DMCU_CRG_DMCU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3B_000C    crg_dmcu003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_mc_n         :  1,    //      1
    reg_soft_rst_p_cpu_3_axi_bnd_n: 1,    //   2
    reg_soft_rst_p_dmcu_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_ss_n         :  1,    //      4
    reg_soft_rst_x_cpu_3_axi_n:  1,    //      5
    reg_soft_rst_x_dmcu_0_axi_n: 1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_DMCU_CRG_DMCU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DMCU_CRG_DMCU000_O26A0_T    crg_dmcu000;          // 0xCA3B_0000
    SCRG_CTRL_DMCU_CRG_DMCU001_O26A0_T    crg_dmcu001;          // 0xCA3B_0004
    SCRG_CTRL_DMCU_CRG_DMCU002_O26A0_T    crg_dmcu002;          // 0xCA3B_0008
    SCRG_CTRL_DMCU_CRG_DMCU003_O26A0_T    crg_dmcu003;          // 0xCA3B_000C
}SCRG_CTRL_DMCU_REG_O26A0_T;
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

#define SCRG_CTRL_DMCU_CRG_DMCU000_O26A0_T_OFF              (BASEADDRESS+0x0000)
#define SCRG_CTRL_DMCU_CRG_DMCU001_O26A0_T_OFF              (BASEADDRESS+0x0004)
#define SCRG_CTRL_DMCU_CRG_DMCU002_O26A0_T_OFF              (BASEADDRESS+0x0008)
#define SCRG_CTRL_DMCU_CRG_DMCU003_O26A0_T_OFF              (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCA3B_0000    crg_dmcu000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DMCU_CRG_DMCU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3B_0004    crg_dmcu001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DMCU_CRG_DMCU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3B_0008    crg_dmcu002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_cpu_3__ss_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_x_dmcu_0__ss_clk_gate_en: 1;    //  1
    UINT32 reg_apb_clk_gate_en:  1;    //      2
    UINT32 reg_mc_clk_gate_en :  1;    //      3
    UINT32 reg_ss_clk_gate_en :  1;    //      4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_DMCU_CRG_DMCU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3B_000C    crg_dmcu003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_mc_n  :  1;    //      1
    UINT32 reg_soft_rst_p_cpu_3_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_dmcu_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_ss_n  :  1;    //      4
    UINT32 reg_soft_rst_x_cpu_3_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_dmcu_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_DMCU_CRG_DMCU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DMCU_CRG_DMCU000_O26A0_T    crg_dmcu000;          // 0xCA3B_0000
    SCRG_CTRL_DMCU_CRG_DMCU001_O26A0_T    crg_dmcu001;          // 0xCA3B_0004
    SCRG_CTRL_DMCU_CRG_DMCU002_O26A0_T    crg_dmcu002;          // 0xCA3B_0008
    SCRG_CTRL_DMCU_CRG_DMCU003_O26A0_T    crg_dmcu003;          // 0xCA3B_000C
}SCRG_CTRL_DMCU_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_DMCU_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

