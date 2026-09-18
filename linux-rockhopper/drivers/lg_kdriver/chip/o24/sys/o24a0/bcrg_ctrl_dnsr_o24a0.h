#ifndef _BCRG_CTRL_DNSR_REG_O24A0_H_
#define _BCRG_CTRL_DNSR_REG_O24A0_H_

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
    0xCC6A_1000    crg_bnd_dnsr0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_DNSR_CRG_BND_DNSR0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_1004    crg_bnd_dnsr1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_DNSR_CRG_BND_DNSR1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_1008    crg_bnd_dnsr2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ts_clk_gate_en        :  1,    //      0
                              : 31;    //   31:1 reserved
}BCRG_CTRL_DNSR_CRG_BND_DNSR2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_100C    crg_bnd_dnsr3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_dnnr_clk_gate_en: 1,    //     0
    reg_apb_ipw_dnsr_clk_gate_en: 1,    //     1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_DNSR_CRG_BND_DNSR3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_1010    crg_bnd_dnsr4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_sre_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_sre_1_n: 1,    //    1
    reg_soft_rst_ts_n         :  1,    //      2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_DNSR_CRG_BND_DNSR4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_1014    crg_bnd_dnsr5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_dnnr_n: 1,    //      0
    reg_soft_rst_apb_ipw_dnsr_n: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_DNSR_CRG_BND_DNSR5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_dnsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DNSR_CRG_BND_DNSR0_O24A0_T    crg_bnd_dnsr0;      // 0xCC6A_1000
    BCRG_CTRL_DNSR_CRG_BND_DNSR1_O24A0_T    crg_bnd_dnsr1;      // 0xCC6A_1004
    BCRG_CTRL_DNSR_CRG_BND_DNSR2_O24A0_T    crg_bnd_dnsr2;      // 0xCC6A_1008
    BCRG_CTRL_DNSR_CRG_BND_DNSR3_O24A0_T    crg_bnd_dnsr3;      // 0xCC6A_100C
    BCRG_CTRL_DNSR_CRG_BND_DNSR4_O24A0_T    crg_bnd_dnsr4;      // 0xCC6A_1010
    BCRG_CTRL_DNSR_CRG_BND_DNSR5_O24A0_T    crg_bnd_dnsr5;      // 0xCC6A_1014
}BCRG_CTRL_DNSR_REG_O24A0_T;
/* 6 regs */

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

#define BCRG_CTRL_DNSR_CRG_BND_DNSR0_O24A0_T_OFF            (BASEADDRESS+0x0000)
#define BCRG_CTRL_DNSR_CRG_BND_DNSR1_O24A0_T_OFF            (BASEADDRESS+0x0004)
#define BCRG_CTRL_DNSR_CRG_BND_DNSR2_O24A0_T_OFF            (BASEADDRESS+0x0008)
#define BCRG_CTRL_DNSR_CRG_BND_DNSR3_O24A0_T_OFF            (BASEADDRESS+0x000C)
#define BCRG_CTRL_DNSR_CRG_BND_DNSR4_O24A0_T_OFF            (BASEADDRESS+0x0010)
#define BCRG_CTRL_DNSR_CRG_BND_DNSR5_O24A0_T_OFF            (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCC6A_1000    crg_bnd_dnsr0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_1004    crg_bnd_dnsr1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_1008    crg_bnd_dnsr2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ts_clk_gate_en :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_100C    crg_bnd_dnsr3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_dnnr_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_dnsr_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_1010    crg_bnd_dnsr4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_sre_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_sre_1_n: 1;    //  1
    UINT32 reg_soft_rst_ts_n  :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_1014    crg_bnd_dnsr5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_dnnr_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_dnsr_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_DNSR_CRG_BND_DNSR5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_dnsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_DNSR_CRG_BND_DNSR0_O24A0_T    crg_bnd_dnsr0;      // 0xCC6A_1000
    BCRG_CTRL_DNSR_CRG_BND_DNSR1_O24A0_T    crg_bnd_dnsr1;      // 0xCC6A_1004
    BCRG_CTRL_DNSR_CRG_BND_DNSR2_O24A0_T    crg_bnd_dnsr2;      // 0xCC6A_1008
    BCRG_CTRL_DNSR_CRG_BND_DNSR3_O24A0_T    crg_bnd_dnsr3;      // 0xCC6A_100C
    BCRG_CTRL_DNSR_CRG_BND_DNSR4_O24A0_T    crg_bnd_dnsr4;      // 0xCC6A_1010
    BCRG_CTRL_DNSR_CRG_BND_DNSR5_O24A0_T    crg_bnd_dnsr5;      // 0xCC6A_1014
}BCRG_CTRL_DNSR_REG_O24A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_DNSR_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

