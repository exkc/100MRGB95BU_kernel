#ifndef _CPU_SCRG_CTRL_PMCU_REG_O24A0_H_
#define _CPU_SCRG_CTRL_PMCU_REG_O24A0_H_

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
    0xCA3D_0000    crg_pmcu0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}CPU_SCRG_CTRL_PMCU_CRG_PMCU0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3D_0004    crg_pmcu1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}CPU_SCRG_CTRL_PMCU_CRG_PMCU1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3D_0008    crg_pmcu2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_mcu_clk_gate_en       :  1,    //      1
                              : 30;    //   31:2 reserved
}CPU_SCRG_CTRL_PMCU_CRG_PMCU2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3D_000C    crg_pmcu3 ''
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
}CPU_SCRG_CTRL_PMCU_CRG_PMCU3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3D_0010    crg_pmcu4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pmcu_mcu_clk_sel      :  1,    //      0
                              : 31;    //   31:1 reserved
}CPU_SCRG_CTRL_PMCU_CRG_PMCU4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_scrg_ctrl_pmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_SCRG_CTRL_PMCU_CRG_PMCU0_O24A0_T    crg_pmcu0;          // 0xCA3D_0000
    CPU_SCRG_CTRL_PMCU_CRG_PMCU1_O24A0_T    crg_pmcu1;          // 0xCA3D_0004
    CPU_SCRG_CTRL_PMCU_CRG_PMCU2_O24A0_T    crg_pmcu2;          // 0xCA3D_0008
    CPU_SCRG_CTRL_PMCU_CRG_PMCU3_O24A0_T    crg_pmcu3;          // 0xCA3D_000C
    CPU_SCRG_CTRL_PMCU_CRG_PMCU4_O24A0_T    crg_pmcu4;          // 0xCA3D_0010
}CPU_SCRG_CTRL_PMCU_REG_O24A0_T;
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

#define CPU_SCRG_CTRL_PMCU_CRG_PMCU0_O24A0_T_OFF            (BASEADDRESS+0x0000)
#define CPU_SCRG_CTRL_PMCU_CRG_PMCU1_O24A0_T_OFF            (BASEADDRESS+0x0004)
#define CPU_SCRG_CTRL_PMCU_CRG_PMCU2_O24A0_T_OFF            (BASEADDRESS+0x0008)
#define CPU_SCRG_CTRL_PMCU_CRG_PMCU3_O24A0_T_OFF            (BASEADDRESS+0x000C)
#define CPU_SCRG_CTRL_PMCU_CRG_PMCU4_O24A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCA3D_0000    crg_pmcu0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}CPU_SCRG_CTRL_PMCU_CRG_PMCU0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3D_0004    crg_pmcu1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}CPU_SCRG_CTRL_PMCU_CRG_PMCU1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3D_0008    crg_pmcu2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_mcu_clk_gate_en:  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}CPU_SCRG_CTRL_PMCU_CRG_PMCU2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3D_000C    crg_pmcu3 ''
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
}CPU_SCRG_CTRL_PMCU_CRG_PMCU3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3D_0010    crg_pmcu4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pmcu_mcu_clk_sel: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}CPU_SCRG_CTRL_PMCU_CRG_PMCU4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_scrg_ctrl_pmcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_SCRG_CTRL_PMCU_CRG_PMCU0_O24A0_T    crg_pmcu0;          // 0xCA3D_0000
    CPU_SCRG_CTRL_PMCU_CRG_PMCU1_O24A0_T    crg_pmcu1;          // 0xCA3D_0004
    CPU_SCRG_CTRL_PMCU_CRG_PMCU2_O24A0_T    crg_pmcu2;          // 0xCA3D_0008
    CPU_SCRG_CTRL_PMCU_CRG_PMCU3_O24A0_T    crg_pmcu3;          // 0xCA3D_000C
    CPU_SCRG_CTRL_PMCU_CRG_PMCU4_O24A0_T    crg_pmcu4;          // 0xCA3D_0010
}CPU_SCRG_CTRL_PMCU_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _CPU_SCRG_CTRL_PMCU_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

