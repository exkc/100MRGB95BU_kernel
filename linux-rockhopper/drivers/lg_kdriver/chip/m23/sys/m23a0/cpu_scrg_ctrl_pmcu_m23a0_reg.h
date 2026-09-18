#ifndef _CPU_SCRG_CTRL_PMCU_M23A0_REG_H_
#define _CPU_SCRG_CTRL_PMCU_M23A0_REG_H_

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
    0xCAD0_0000    crg_pmcu00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}CPU_SCRG_CTRL_PMCU_CRG_PMCU00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAD0_0004    crg_pmcu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}CPU_SCRG_CTRL_PMCU_CRG_PMCU01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAD0_0008    crg_pmcu02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pmcu_apb_clk_gate_en  :  1,    //      0
    reg_pmcu_mcu_clk_gate_en  :  1,    //      1
                              : 30;    //   31:2 reserved
}CPU_SCRG_CTRL_PMCU_CRG_PMCU02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAD0_000C    crg_pmcu03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_bus_n        :  1,    //      1
    reg_soft_rst_mcu_n        :  1,    //      2
    reg_soft_rst_p_pmcu_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_x_pmcu_0_axi_bnd_n: 1,    //  4
    reg_soft_rst_x_pmcu_0_axi_n: 1,    //      5
                              : 26;    //   31:6 reserved
}CPU_SCRG_CTRL_PMCU_CRG_PMCU03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAD0_0010    crg_pmcu04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pmcu_mcu_clk_sel      :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}CPU_SCRG_CTRL_PMCU_CRG_PMCU04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_scrg_ctrl_pmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_SCRG_CTRL_PMCU_CRG_PMCU00_M23A0_T    crg_pmcu00;        // 0xCAD0_0000
    CPU_SCRG_CTRL_PMCU_CRG_PMCU01_M23A0_T    crg_pmcu01;        // 0xCAD0_0004
    CPU_SCRG_CTRL_PMCU_CRG_PMCU02_M23A0_T    crg_pmcu02;        // 0xCAD0_0008
    CPU_SCRG_CTRL_PMCU_CRG_PMCU03_M23A0_T    crg_pmcu03;        // 0xCAD0_000C
    CPU_SCRG_CTRL_PMCU_CRG_PMCU04_M23A0_T    crg_pmcu04;        // 0xCAD0_0010
}CPU_SCRG_CTRL_PMCU_REG_M23A0_T;
/* 5 regs */

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

#define CPU_SCRG_CTRL_PMCU_CRG_PMCU00_M23A0_T_OFF           (BASEADDRESS+0x0000)
#define CPU_SCRG_CTRL_PMCU_CRG_PMCU01_M23A0_T_OFF           (BASEADDRESS+0x0004)
#define CPU_SCRG_CTRL_PMCU_CRG_PMCU02_M23A0_T_OFF           (BASEADDRESS+0x0008)
#define CPU_SCRG_CTRL_PMCU_CRG_PMCU03_M23A0_T_OFF           (BASEADDRESS+0x000C)
#define CPU_SCRG_CTRL_PMCU_CRG_PMCU04_M23A0_T_OFF           (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCAD0_0000    crg_pmcu00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}CPU_SCRG_CTRL_PMCU_CRG_PMCU00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAD0_0004    crg_pmcu01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}CPU_SCRG_CTRL_PMCU_CRG_PMCU01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAD0_0008    crg_pmcu02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pmcu_apb_clk_gate_en: 1;    //  0
    UINT32 reg_pmcu_mcu_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}CPU_SCRG_CTRL_PMCU_CRG_PMCU02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAD0_000C    crg_pmcu03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_bus_n :  1;    //      1
    UINT32 reg_soft_rst_mcu_n :  1;    //      2
    UINT32 reg_soft_rst_p_pmcu_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_pmcu_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_pmcu_0_axi_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}CPU_SCRG_CTRL_PMCU_CRG_PMCU03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAD0_0010    crg_pmcu04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pmcu_mcu_clk_sel: 2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}CPU_SCRG_CTRL_PMCU_CRG_PMCU04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_scrg_ctrl_pmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_SCRG_CTRL_PMCU_CRG_PMCU00_M23A0_T    crg_pmcu00;        // 0xCAD0_0000
    CPU_SCRG_CTRL_PMCU_CRG_PMCU01_M23A0_T    crg_pmcu01;        // 0xCAD0_0004
    CPU_SCRG_CTRL_PMCU_CRG_PMCU02_M23A0_T    crg_pmcu02;        // 0xCAD0_0008
    CPU_SCRG_CTRL_PMCU_CRG_PMCU03_M23A0_T    crg_pmcu03;        // 0xCAD0_000C
    CPU_SCRG_CTRL_PMCU_CRG_PMCU04_M23A0_T    crg_pmcu04;        // 0xCAD0_0010
}CPU_SCRG_CTRL_PMCU_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

