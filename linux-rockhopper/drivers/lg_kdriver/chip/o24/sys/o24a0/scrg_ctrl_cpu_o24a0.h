#ifndef _SCRG_CTRL_CPU_REG_O24A0_H_
#define _SCRG_CTRL_CPU_REG_O24A0_H_

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
    0xCA21_0000    crg_cpu0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_CPU_CRG_CPU0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0004    crg_cpu1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_CPU_CRG_CPU1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0008    crg_cpu2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_peri_200m_clk_gate_en :  1,    //      0
    reg_peri_200m_clk_n_gate_en: 1,    //      1
    reg_peri_25m_ci_clk_gate_en: 1,    //      2
    reg_peri_400m_clk_gate_en :  1,    //      3
    reg_peri_50m_ci_clk_gate_en: 1,    //      4
    reg_peri_660m_clk_gate_en :  1,    //      5
    reg_tzapb_clk_gate_en     :  1,    //      6
    reg_xtal_clk_w_gate_en    :  1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_CPU_CRG_CPU2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_000C    crg_cpu3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_o_cpu_clk_sel         :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_CPU_CRG_CPU3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CPU_CRG_CPU0_O24A0_T     crg_cpu0   ;             // 0xCA21_0000
    SCRG_CTRL_CPU_CRG_CPU1_O24A0_T     crg_cpu1   ;             // 0xCA21_0004
    SCRG_CTRL_CPU_CRG_CPU2_O24A0_T     crg_cpu2   ;             // 0xCA21_0008
    SCRG_CTRL_CPU_CRG_CPU3_O24A0_T     crg_cpu3   ;             // 0xCA21_000C
}SCRG_CTRL_CPU_REG_O24A0_T;
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

#define SCRG_CTRL_CPU_CRG_CPU0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_CPU_CRG_CPU1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_CPU_CRG_CPU2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_CPU_CRG_CPU3_O24A0_T_OFF                  (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCA21_0000    crg_cpu0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_CPU_CRG_CPU0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0004    crg_cpu1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_CPU_CRG_CPU1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0008    crg_cpu2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_peri_200m_clk_gate_en: 1;    //  0
    UINT32 reg_peri_200m_clk_n_gate_en: 1;    //  1
    UINT32 reg_peri_25m_ci_clk_gate_en: 1;    //  2
    UINT32 reg_peri_400m_clk_gate_en: 1;    //  3
    UINT32 reg_peri_50m_ci_clk_gate_en: 1;    //  4
    UINT32 reg_peri_660m_clk_gate_en: 1;    //  5
    UINT32 reg_tzapb_clk_gate_en: 1;    //     6
    UINT32 reg_xtal_clk_w_gate_en: 1;    //    7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_CPU_CRG_CPU2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_000C    crg_cpu3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_o_cpu_clk_sel  :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_CPU_CRG_CPU3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CPU_CRG_CPU0_O24A0_T     crg_cpu0   ;             // 0xCA21_0000
    SCRG_CTRL_CPU_CRG_CPU1_O24A0_T     crg_cpu1   ;             // 0xCA21_0004
    SCRG_CTRL_CPU_CRG_CPU2_O24A0_T     crg_cpu2   ;             // 0xCA21_0008
    SCRG_CTRL_CPU_CRG_CPU3_O24A0_T     crg_cpu3   ;             // 0xCA21_000C
}SCRG_CTRL_CPU_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_CPU_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

