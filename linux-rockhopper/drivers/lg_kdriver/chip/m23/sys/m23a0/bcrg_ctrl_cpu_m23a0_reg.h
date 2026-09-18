#ifndef _BCRG_CTRL_CPU_M23A0_REG_H_
#define _BCRG_CTRL_CPU_M23A0_REG_H_

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
    0xCA22_1000    crg_bnd_cpu00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_CPU_CRG_BND_CPU00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_1004    crg_bnd_cpu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_CPU_CRG_BND_CPU01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_1008    crg_bnd_cpu02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_cpu_clk_gate_en: 1,    //      0
    reg_apb_ipw_pmcu_clk_gate_en: 1,    //     1
    reg_apb_ipw_vmcu_clk_gate_en: 1,    //     2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_CPU_CRG_BND_CPU02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_100C    crg_bnd_cpu03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_aud_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_aud_1_n: 1,    //    1
    reg_soft_rst_axi_brdg_fms_0_n: 1,    //    2
    reg_soft_rst_axi_brdg_tivsb_0_n: 1,    //  3
                              : 28;    //   31:4 reserved
}BCRG_CTRL_CPU_CRG_BND_CPU03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_1010    crg_bnd_cpu04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_cpu_n:  1,    //      0
    reg_soft_rst_apb_ipw_pmcu_n: 1,    //      1
    reg_soft_rst_apb_ipw_vmcu_n: 1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_CPU_CRG_BND_CPU04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CPU_CRG_BND_CPU00_M23A0_T    crg_bnd_cpu00;       // 0xCA22_1000
    BCRG_CTRL_CPU_CRG_BND_CPU01_M23A0_T    crg_bnd_cpu01;       // 0xCA22_1004
    BCRG_CTRL_CPU_CRG_BND_CPU02_M23A0_T    crg_bnd_cpu02;       // 0xCA22_1008
    BCRG_CTRL_CPU_CRG_BND_CPU03_M23A0_T    crg_bnd_cpu03;       // 0xCA22_100C
    BCRG_CTRL_CPU_CRG_BND_CPU04_M23A0_T    crg_bnd_cpu04;       // 0xCA22_1010
}BCRG_CTRL_CPU_REG_M23A0_T;
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

#define BCRG_CTRL_CPU_CRG_BND_CPU00_M23A0_T_OFF             (BASEADDRESS+0x0000)
#define BCRG_CTRL_CPU_CRG_BND_CPU01_M23A0_T_OFF             (BASEADDRESS+0x0004)
#define BCRG_CTRL_CPU_CRG_BND_CPU02_M23A0_T_OFF             (BASEADDRESS+0x0008)
#define BCRG_CTRL_CPU_CRG_BND_CPU03_M23A0_T_OFF             (BASEADDRESS+0x000C)
#define BCRG_CTRL_CPU_CRG_BND_CPU04_M23A0_T_OFF             (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCA22_1000    crg_bnd_cpu00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_CPU_CRG_BND_CPU00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_1004    crg_bnd_cpu01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_CPU_CRG_BND_CPU01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_1008    crg_bnd_cpu02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_cpu_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_pmcu_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_vmcu_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_CPU_CRG_BND_CPU02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_100C    crg_bnd_cpu03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_aud_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_aud_1_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_fms_0_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_tivsb_0_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BCRG_CTRL_CPU_CRG_BND_CPU03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_1010    crg_bnd_cpu04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_cpu_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_pmcu_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_vmcu_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_CPU_CRG_BND_CPU04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_CPU_CRG_BND_CPU00_M23A0_T    crg_bnd_cpu00;       // 0xCA22_1000
    BCRG_CTRL_CPU_CRG_BND_CPU01_M23A0_T    crg_bnd_cpu01;       // 0xCA22_1004
    BCRG_CTRL_CPU_CRG_BND_CPU02_M23A0_T    crg_bnd_cpu02;       // 0xCA22_1008
    BCRG_CTRL_CPU_CRG_BND_CPU03_M23A0_T    crg_bnd_cpu03;       // 0xCA22_100C
    BCRG_CTRL_CPU_CRG_BND_CPU04_M23A0_T    crg_bnd_cpu04;       // 0xCA22_1010
}BCRG_CTRL_CPU_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

