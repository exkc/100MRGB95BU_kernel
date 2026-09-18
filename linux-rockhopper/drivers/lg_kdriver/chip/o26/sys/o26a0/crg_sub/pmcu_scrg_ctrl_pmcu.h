#ifndef _PMCU_SCRG_CTRL_PMCU_REG_O26A0_H_
#define _PMCU_SCRG_CTRL_PMCU_REG_O26A0_H_

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
    0xCC3D_0000    crg_pmcu000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}PMCU_SCRG_CTRL_PMCU_CRG_PMCU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3D_0004    crg_pmcu001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}PMCU_SCRG_CTRL_PMCU_CRG_PMCU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3D_0008    crg_pmcu002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_pmcu_0__mcu_clk_gate_en: 1,    //  0
    reg_apb_clk_gate_en       :  1,    //      1
    reg_mcu_clk_gate_en       :  1,    //      2
                              : 29;    //   31:3 reserved
}PMCU_SCRG_CTRL_PMCU_CRG_PMCU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3D_000C    crg_pmcu003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_bus_n        :  1,    //      1
    reg_soft_rst_mcu_n        :  1,    //      2
    reg_soft_rst_p_pmcu_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_x_pmcu_0_axi_n: 1,    //      4
                              : 27;    //   31:5 reserved
}PMCU_SCRG_CTRL_PMCU_CRG_PMCU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3D_0010    crg_pmcu004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mcu_clk_sel           :  1,    //      0
                              : 31;    //   31:1 reserved
}PMCU_SCRG_CTRL_PMCU_CRG_PMCU004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    pmcu_scrg_ctrl_pmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    PMCU_SCRG_CTRL_PMCU_CRG_PMCU000_O26A0_T    crg_pmcu000;     // 0xCC3D_0000
    PMCU_SCRG_CTRL_PMCU_CRG_PMCU001_O26A0_T    crg_pmcu001;     // 0xCC3D_0004
    PMCU_SCRG_CTRL_PMCU_CRG_PMCU002_O26A0_T    crg_pmcu002;     // 0xCC3D_0008
    PMCU_SCRG_CTRL_PMCU_CRG_PMCU003_O26A0_T    crg_pmcu003;     // 0xCC3D_000C
    PMCU_SCRG_CTRL_PMCU_CRG_PMCU004_O26A0_T    crg_pmcu004;     // 0xCC3D_0010
}PMCU_SCRG_CTRL_PMCU_REG_O26A0_T;
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

#define PMCU_SCRG_CTRL_PMCU_CRG_PMCU000_O26A0_T_OFF         (BASEADDRESS+0x0000)
#define PMCU_SCRG_CTRL_PMCU_CRG_PMCU001_O26A0_T_OFF         (BASEADDRESS+0x0004)
#define PMCU_SCRG_CTRL_PMCU_CRG_PMCU002_O26A0_T_OFF         (BASEADDRESS+0x0008)
#define PMCU_SCRG_CTRL_PMCU_CRG_PMCU003_O26A0_T_OFF         (BASEADDRESS+0x000C)
#define PMCU_SCRG_CTRL_PMCU_CRG_PMCU004_O26A0_T_OFF         (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC3D_0000    crg_pmcu000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}PMCU_SCRG_CTRL_PMCU_CRG_PMCU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3D_0004    crg_pmcu001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}PMCU_SCRG_CTRL_PMCU_CRG_PMCU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3D_0008    crg_pmcu002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_pmcu_0__mcu_clk_gate_en: 1;    //  0
    UINT32 reg_apb_clk_gate_en:  1;    //      1
    UINT32 reg_mcu_clk_gate_en:  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}PMCU_SCRG_CTRL_PMCU_CRG_PMCU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3D_000C    crg_pmcu003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_bus_n :  1;    //      1
    UINT32 reg_soft_rst_mcu_n :  1;    //      2
    UINT32 reg_soft_rst_p_pmcu_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_pmcu_0_axi_n: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}PMCU_SCRG_CTRL_PMCU_CRG_PMCU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3D_0010    crg_pmcu004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_mcu_clk_sel    :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}PMCU_SCRG_CTRL_PMCU_CRG_PMCU004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    pmcu_scrg_ctrl_pmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    PMCU_SCRG_CTRL_PMCU_CRG_PMCU000_O26A0_T    crg_pmcu000;     // 0xCC3D_0000
    PMCU_SCRG_CTRL_PMCU_CRG_PMCU001_O26A0_T    crg_pmcu001;     // 0xCC3D_0004
    PMCU_SCRG_CTRL_PMCU_CRG_PMCU002_O26A0_T    crg_pmcu002;     // 0xCC3D_0008
    PMCU_SCRG_CTRL_PMCU_CRG_PMCU003_O26A0_T    crg_pmcu003;     // 0xCC3D_000C
    PMCU_SCRG_CTRL_PMCU_CRG_PMCU004_O26A0_T    crg_pmcu004;     // 0xCC3D_0010
}PMCU_SCRG_CTRL_PMCU_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_PMCU_SCRG_CTRL_PMCU_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

