#ifndef _BCRG_CTRL_DNSR_REG_O26A0_H_
#define _BCRG_CTRL_DNSR_REG_O26A0_H_

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
    0xCC4C_1000    crg_bnd_dnsr000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_DNSR_CRG_BND_DNSR000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1004    crg_bnd_dnsr001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_DNSR_CRG_BND_DNSR001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1008    crg_bnd_dnsr002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_dnsr0_clk_gate_en: 1,    //    0
    reg_apb_ipw_dnsr1_clk_gate_en: 1,    //    1
    reg_apb_ipw_lb0sb_clk_gate_en: 1,    //    2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_DNSR_CRG_BND_DNSR002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_100C    crg_bnd_dnsr003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_cpu_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_usbsb_0_n: 1,    //  1
    reg_soft_rst_fly_brdg_cvi_0_n: 1,    //    2
    reg_soft_rst_fly_brdg_cvi_1_n: 1,    //    3
    reg_soft_rst_fly_brdg_cvi_2_n: 1,    //    4
    reg_soft_rst_fly_brdg_cvi_3_n: 1,    //    5
    reg_soft_rst_fly_brdg_teipw_0_n: 1,    //  6
    reg_soft_rst_fly_brdg_teipw_1_n: 1,    //  7
    reg_soft_rst_fly_brdg_teipw_2_n: 1,    //  8
    reg_soft_rst_fly_brdg_teipw_3_n: 1,    //  9
    reg_soft_rst_fly_brdg_tp_int_n: 1,    //  10
    reg_soft_rst_pes_brdg_te_6_n: 1,    //    11
    reg_soft_rst_pes_brdg_te_7_n: 1,    //    12
                              : 19;    //  31:13 reserved
}BCRG_CTRL_DNSR_CRG_BND_DNSR003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1010    crg_bnd_dnsr004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_dnsr0_n: 1,    //     0
    reg_soft_rst_apb_ipw_dnsr1_n: 1,    //     1
    reg_soft_rst_apb_ipw_lb0sb_n: 1,    //     2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_DNSR_CRG_BND_DNSR004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_dnsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DNSR_CRG_BND_DNSR000_O26A0_T    crg_bnd_dnsr000;    // 0xCC4C_1000
    BCRG_CTRL_DNSR_CRG_BND_DNSR001_O26A0_T    crg_bnd_dnsr001;    // 0xCC4C_1004
    BCRG_CTRL_DNSR_CRG_BND_DNSR002_O26A0_T    crg_bnd_dnsr002;    // 0xCC4C_1008
    BCRG_CTRL_DNSR_CRG_BND_DNSR003_O26A0_T    crg_bnd_dnsr003;    // 0xCC4C_100C
    BCRG_CTRL_DNSR_CRG_BND_DNSR004_O26A0_T    crg_bnd_dnsr004;    // 0xCC4C_1010
}BCRG_CTRL_DNSR_REG_O26A0_T;
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

#define BCRG_CTRL_DNSR_CRG_BND_DNSR000_O26A0_T_OFF          (BASEADDRESS+0x0000)
#define BCRG_CTRL_DNSR_CRG_BND_DNSR001_O26A0_T_OFF          (BASEADDRESS+0x0004)
#define BCRG_CTRL_DNSR_CRG_BND_DNSR002_O26A0_T_OFF          (BASEADDRESS+0x0008)
#define BCRG_CTRL_DNSR_CRG_BND_DNSR003_O26A0_T_OFF          (BASEADDRESS+0x000C)
#define BCRG_CTRL_DNSR_CRG_BND_DNSR004_O26A0_T_OFF          (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC4C_1000    crg_bnd_dnsr000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1004    crg_bnd_dnsr001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1008    crg_bnd_dnsr002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_dnsr0_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_dnsr1_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_lb0sb_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_100C    crg_bnd_dnsr003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_cpu_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_usbsb_0_n: 1;    //  1
    UINT32 reg_soft_rst_fly_brdg_cvi_0_n: 1;    //  2
    UINT32 reg_soft_rst_fly_brdg_cvi_1_n: 1;    //  3
    UINT32 reg_soft_rst_fly_brdg_cvi_2_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_cvi_3_n: 1;    //  5
    UINT32 reg_soft_rst_fly_brdg_teipw_0_n: 1;    //  6
    UINT32 reg_soft_rst_fly_brdg_teipw_1_n: 1;    //  7
    UINT32 reg_soft_rst_fly_brdg_teipw_2_n: 1;    //  8
    UINT32 reg_soft_rst_fly_brdg_teipw_3_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_tp_int_n: 1;    //  10
    UINT32 reg_soft_rst_pes_brdg_te_6_n: 1;    //  11
    UINT32 reg_soft_rst_pes_brdg_te_7_n: 1;    //  12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4C_1010    crg_bnd_dnsr004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_dnsr0_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_dnsr1_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_lb0sb_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_dnsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DNSR_CRG_BND_DNSR000_O26A0_T    crg_bnd_dnsr000;    // 0xCC4C_1000
    BCRG_CTRL_DNSR_CRG_BND_DNSR001_O26A0_T    crg_bnd_dnsr001;    // 0xCC4C_1004
    BCRG_CTRL_DNSR_CRG_BND_DNSR002_O26A0_T    crg_bnd_dnsr002;    // 0xCC4C_1008
    BCRG_CTRL_DNSR_CRG_BND_DNSR003_O26A0_T    crg_bnd_dnsr003;    // 0xCC4C_100C
    BCRG_CTRL_DNSR_CRG_BND_DNSR004_O26A0_T    crg_bnd_dnsr004;    // 0xCC4C_1010
}BCRG_CTRL_DNSR_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BCRG_CTRL_DNSR_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

