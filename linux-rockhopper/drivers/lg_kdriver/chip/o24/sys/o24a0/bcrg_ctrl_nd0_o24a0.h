#ifndef _BCRG_CTRL_ND0_REG_O24A0_H_
#define _BCRG_CTRL_ND0_REG_O24A0_H_

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
    0xCCC8_1000    crg_bnd_nd00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_ND0_CRG_BND_ND00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_1004    crg_bnd_nd01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_ND0_CRG_BND_ND01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_1008    crg_bnd_nd02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_nd0_clk_gate_en: 1,    //      0
    reg_apb_ipw_sb_epu_clk_gate_en: 1,    //   1
    reg_apb_ipw_sb_lb0_clk_gate_en: 1,    //   2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_ND0_CRG_BND_ND02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_100C    crg_bnd_nd03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_aud_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_cpu_4_n: 1,    //    1
    reg_soft_rst_axi_brdg_cpu_5_n: 1,    //    2
    reg_soft_rst_axi_brdg_micom_0_n: 1,    //  3
    reg_soft_rst_fly_brdg_cvi_0_n: 1,    //    4
    reg_soft_rst_fly_brdg_cvi_1_n: 1,    //    5
    reg_soft_rst_fly_brdg_cvi_2_n: 1,    //    6
    reg_soft_rst_fly_brdg_cvi_3_n: 1,    //    7
    reg_soft_rst_fly_brdg_cvi_4_n: 1,    //    8
    reg_soft_rst_fly_brdg_teipw_0_n: 1,    //  9
    reg_soft_rst_fly_brdg_teipw_1_n: 1,    //  10
    reg_soft_rst_fly_brdg_teipw_2_n: 1,    //  11
    reg_soft_rst_fly_brdg_teipw_3_n: 1,    //  12
    reg_soft_rst_pes_brdg_te_6_n: 1,    //    13
    reg_soft_rst_pes_brdg_te_7_n: 1,    //    14
                              : 17;    //  31:15 reserved
}BCRG_CTRL_ND0_CRG_BND_ND03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_1010    crg_bnd_nd04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_nd0_n:  1,    //      0
    reg_soft_rst_apb_ipw_sb_epu_n: 1,    //    1
    reg_soft_rst_apb_ipw_sb_lb0_n: 1,    //    2
                              : 29;    //   31:3 reserved
}BCRG_CTRL_ND0_CRG_BND_ND04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ND0_CRG_BND_ND00_O24A0_T    crg_bnd_nd00;         // 0xCCC8_1000
    BCRG_CTRL_ND0_CRG_BND_ND01_O24A0_T    crg_bnd_nd01;         // 0xCCC8_1004
    BCRG_CTRL_ND0_CRG_BND_ND02_O24A0_T    crg_bnd_nd02;         // 0xCCC8_1008
    BCRG_CTRL_ND0_CRG_BND_ND03_O24A0_T    crg_bnd_nd03;         // 0xCCC8_100C
    BCRG_CTRL_ND0_CRG_BND_ND04_O24A0_T    crg_bnd_nd04;         // 0xCCC8_1010
}BCRG_CTRL_ND0_REG_O24A0_T;
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

#define BCRG_CTRL_ND0_CRG_BND_ND00_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_ND0_CRG_BND_ND01_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_ND0_CRG_BND_ND02_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_ND0_CRG_BND_ND03_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_ND0_CRG_BND_ND04_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCC8_1000    crg_bnd_nd00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_ND0_CRG_BND_ND00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_1004    crg_bnd_nd01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_ND0_CRG_BND_ND01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_1008    crg_bnd_nd02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_nd0_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_sb_epu_clk_gate_en: 1;    //  1
    UINT32 reg_apb_ipw_sb_lb0_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_ND0_CRG_BND_ND02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_100C    crg_bnd_nd03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_aud_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_cpu_4_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_cpu_5_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_micom_0_n: 1;    //  3
    UINT32 reg_soft_rst_fly_brdg_cvi_0_n: 1;    //  4
    UINT32 reg_soft_rst_fly_brdg_cvi_1_n: 1;    //  5
    UINT32 reg_soft_rst_fly_brdg_cvi_2_n: 1;    //  6
    UINT32 reg_soft_rst_fly_brdg_cvi_3_n: 1;    //  7
    UINT32 reg_soft_rst_fly_brdg_cvi_4_n: 1;    //  8
    UINT32 reg_soft_rst_fly_brdg_teipw_0_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_teipw_1_n: 1;    //  10
    UINT32 reg_soft_rst_fly_brdg_teipw_2_n: 1;    //  11
    UINT32 reg_soft_rst_fly_brdg_teipw_3_n: 1;    //  12
    UINT32 reg_soft_rst_pes_brdg_te_6_n: 1;    //  13
    UINT32 reg_soft_rst_pes_brdg_te_7_n: 1;    //  14
    UINT32 resvd00            : 17;    //  31:15 reserved
    };
}BCRG_CTRL_ND0_CRG_BND_ND03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC8_1010    crg_bnd_nd04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_nd0_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_sb_epu_n: 1;    //  1
    UINT32 reg_soft_rst_apb_ipw_sb_lb0_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BCRG_CTRL_ND0_CRG_BND_ND04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_ND0_CRG_BND_ND00_O24A0_T    crg_bnd_nd00;         // 0xCCC8_1000
    BCRG_CTRL_ND0_CRG_BND_ND01_O24A0_T    crg_bnd_nd01;         // 0xCCC8_1004
    BCRG_CTRL_ND0_CRG_BND_ND02_O24A0_T    crg_bnd_nd02;         // 0xCCC8_1008
    BCRG_CTRL_ND0_CRG_BND_ND03_O24A0_T    crg_bnd_nd03;         // 0xCCC8_100C
    BCRG_CTRL_ND0_CRG_BND_ND04_O24A0_T    crg_bnd_nd04;         // 0xCCC8_1010
}BCRG_CTRL_ND0_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_ND0_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

