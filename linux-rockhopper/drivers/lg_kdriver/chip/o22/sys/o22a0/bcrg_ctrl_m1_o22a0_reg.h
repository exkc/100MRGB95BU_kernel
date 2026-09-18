#ifndef _BCRG_CTRL_M1_REG_H_
#define _BCRG_CTRL_M1_REG_H_

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
    0x3B_0000    crg_bnd_m100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_M1_CRG_BND_M100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3B_0004    crg_bnd_m101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_M1_CRG_BND_M101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3B_0008    crg_bnd_m102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_m1_clk_gate_en:  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_M1_CRG_BND_M102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3B_000C    crg_bnd_m103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_sbw_aresetn_ddrc :  1,    //      0
    reg_soft_sbw_m0_ddr       :  1,    //      1
    reg_soft_sbw_s0_bus       :  1,    //      2
    reg_soft_sbw_s1_cpu       :  1,    //      3
    reg_soft_sbw_s2_wov       :  1,    //      4
                              : 27;    //   31:5 reserved
}BCRG_CTRL_M1_CRG_BND_M103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3B_0010    crg_bnd_m104 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_m1_n :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_M1_CRG_BND_M104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_m1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_M1_CRG_BND_M100_O22A0_T    crg_bnd_m100;            // 0x3B_0000
    BCRG_CTRL_M1_CRG_BND_M101_O22A0_T    crg_bnd_m101;            // 0x3B_0004
    BCRG_CTRL_M1_CRG_BND_M102_O22A0_T    crg_bnd_m102;            // 0x3B_0008
    BCRG_CTRL_M1_CRG_BND_M103_O22A0_T    crg_bnd_m103;            // 0x3B_000C
    BCRG_CTRL_M1_CRG_BND_M104_O22A0_T    crg_bnd_m104;            // 0x3B_0010
}BCRG_CTRL_M1_REG_O22A0_T;
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

#define BCRG_CTRL_M1_CRG_BND_M100_O22A0_T_OFF                 (BASEADDRESS+0x0000)
#define BCRG_CTRL_M1_CRG_BND_M101_O22A0_T_OFF                 (BASEADDRESS+0x0004)
#define BCRG_CTRL_M1_CRG_BND_M102_O22A0_T_OFF                 (BASEADDRESS+0x0008)
#define BCRG_CTRL_M1_CRG_BND_M103_O22A0_T_OFF                 (BASEADDRESS+0x000C)
#define BCRG_CTRL_M1_CRG_BND_M104_O22A0_T_OFF                 (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0x3B_0000    crg_bnd_m100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_M1_CRG_BND_M100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3B_0004    crg_bnd_m101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_M1_CRG_BND_M101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3B_0008    crg_bnd_m102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_m1_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_M1_CRG_BND_M102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3B_000C    crg_bnd_m103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_sbw_aresetn_ddrc: 1;    //  0
    UINT32 reg_soft_sbw_m0_ddr:  1;    //      1
    UINT32 reg_soft_sbw_s0_bus:  1;    //      2
    UINT32 reg_soft_sbw_s1_cpu:  1;    //      3
    UINT32 reg_soft_sbw_s2_wov:  1;    //      4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}BCRG_CTRL_M1_CRG_BND_M103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x3B_0010    crg_bnd_m104 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_m1_n: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_M1_CRG_BND_M104_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_bnd_m1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_M1_CRG_BND_M100_O22A0_T    crg_bnd_m100;            // 0x3B_0000
    BCRG_CTRL_M1_CRG_BND_M101_O22A0_T    crg_bnd_m101;            // 0x3B_0004
    BCRG_CTRL_M1_CRG_BND_M102_O22A0_T    crg_bnd_m102;            // 0x3B_0008
    BCRG_CTRL_M1_CRG_BND_M103_O22A0_T    crg_bnd_m103;            // 0x3B_000C
    BCRG_CTRL_M1_CRG_BND_M104_O22A0_T    crg_bnd_m104;            // 0x3B_0010
}BCRG_CTRL_M1_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

