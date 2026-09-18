#ifndef _BCRG_CTRL_HDR_REG_O24A0_H_
#define _BCRG_CTRL_HDR_REG_O24A0_H_

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
    0xCCC5_1000    crg_bnd_hdr0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}BCRG_CTRL_HDR_CRG_BND_HDR0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_1004    crg_bnd_hdr1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}BCRG_CTRL_HDR_CRG_BND_HDR1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_1008    crg_bnd_hdr2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_hdr_clk_gate_en: 1,    //      0
    reg_apb_ipw_vdo_clk_gate_en: 1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_HDR_CRG_BND_HDR2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_100C    crg_bnd_hdr3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_axi_brdg_aud_0_n: 1,    //    0
    reg_soft_rst_axi_brdg_cpu_4_n: 1,    //    1
    reg_soft_rst_axi_brdg_cpu_5_n: 1,    //    2
    reg_soft_rst_axi_brdg_epusb_0_n: 1,    //  3
    reg_soft_rst_axi_brdg_lb0sb_0_n: 1,    //  4
    reg_soft_rst_axi_brdg_micom_0_n: 1,    //  5
    reg_soft_rst_axi_brdg_nd0_0_n: 1,    //    6
    reg_soft_rst_fly_brdg_cvi_0_n: 1,    //    7
    reg_soft_rst_fly_brdg_cvi_1_n: 1,    //    8
    reg_soft_rst_fly_brdg_cvi_2_n: 1,    //    9
    reg_soft_rst_fly_brdg_cvi_3_n: 1,    //   10
    reg_soft_rst_fly_brdg_cvi_4_n: 1,    //   11
    reg_soft_rst_fly_brdg_teipw_0_n: 1,    //  12
    reg_soft_rst_fly_brdg_teipw_1_n: 1,    //  13
    reg_soft_rst_fly_brdg_teipw_2_n: 1,    //  14
    reg_soft_rst_fly_brdg_teipw_3_n: 1,    //  15
    reg_soft_rst_hsp_brdg_imx_6_n: 1,    //   16
    reg_soft_rst_hsp_brdg_imx_7_n: 1,    //   17
    reg_soft_rst_hsp_brdg_nd0_0_n: 1,    //   18
    reg_soft_rst_hsp_brdg_nd0_1_n: 1,    //   19
    reg_soft_rst_hsp_brdg_nd0_4_n: 1,    //   20
    reg_soft_rst_hsp_brdg_nd0_5_n: 1,    //   21
    reg_soft_rst_pes_brdg_te_6_n: 1,    //    22
    reg_soft_rst_pes_brdg_te_7_n: 1,    //    23
                              :  8;    //  31:24 reserved
}BCRG_CTRL_HDR_CRG_BND_HDR3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_1010    crg_bnd_hdr4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_ipw_hdr_n:  1,    //      0
    reg_soft_rst_apb_ipw_vdo_n:  1,    //      1
                              : 30;    //   31:2 reserved
}BCRG_CTRL_HDR_CRG_BND_HDR4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_HDR_CRG_BND_HDR0_O24A0_T    crg_bnd_hdr0;         // 0xCCC5_1000
    BCRG_CTRL_HDR_CRG_BND_HDR1_O24A0_T    crg_bnd_hdr1;         // 0xCCC5_1004
    BCRG_CTRL_HDR_CRG_BND_HDR2_O24A0_T    crg_bnd_hdr2;         // 0xCCC5_1008
    BCRG_CTRL_HDR_CRG_BND_HDR3_O24A0_T    crg_bnd_hdr3;         // 0xCCC5_100C
    BCRG_CTRL_HDR_CRG_BND_HDR4_O24A0_T    crg_bnd_hdr4;         // 0xCCC5_1010
}BCRG_CTRL_HDR_REG_O24A0_T;
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

#define BCRG_CTRL_HDR_CRG_BND_O24A0_HDR0_O24A0_T_OFF              (BASEADDRESS+0x0000)
#define BCRG_CTRL_HDR_CRG_BND_O24A0_HDR1_O24A0_T_OFF              (BASEADDRESS+0x0004)
#define BCRG_CTRL_HDR_CRG_BND_O24A0_HDR2_O24A0_T_OFF              (BASEADDRESS+0x0008)
#define BCRG_CTRL_HDR_CRG_BND_O24A0_HDR3_O24A0_T_OFF              (BASEADDRESS+0x000C)
#define BCRG_CTRL_HDR_CRG_BND_O24A0_HDR4_O24A0_T_OFF              (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCCC5_1000    crg_bnd_hdr0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}BCRG_CTRL_HDR_CRG_BND_HDR0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_1004    crg_bnd_hdr1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}BCRG_CTRL_HDR_CRG_BND_HDR1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_1008    crg_bnd_hdr2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_hdr_clk_gate_en: 1;    //  0
    UINT32 reg_apb_ipw_vdo_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_HDR_CRG_BND_HDR2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_100C    crg_bnd_hdr3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_axi_brdg_aud_0_n: 1;    //  0
    UINT32 reg_soft_rst_axi_brdg_cpu_4_n: 1;    //  1
    UINT32 reg_soft_rst_axi_brdg_cpu_5_n: 1;    //  2
    UINT32 reg_soft_rst_axi_brdg_epusb_0_n: 1;    //  3
    UINT32 reg_soft_rst_axi_brdg_lb0sb_0_n: 1;    //  4
    UINT32 reg_soft_rst_axi_brdg_micom_0_n: 1;    //  5
    UINT32 reg_soft_rst_axi_brdg_nd0_0_n: 1;    //  6
    UINT32 reg_soft_rst_fly_brdg_cvi_0_n: 1;    //  7
    UINT32 reg_soft_rst_fly_brdg_cvi_1_n: 1;    //  8
    UINT32 reg_soft_rst_fly_brdg_cvi_2_n: 1;    //  9
    UINT32 reg_soft_rst_fly_brdg_cvi_3_n: 1;    //  10
    UINT32 reg_soft_rst_fly_brdg_cvi_4_n: 1;    //  11
    UINT32 reg_soft_rst_fly_brdg_teipw_0_n: 1;    //  12
    UINT32 reg_soft_rst_fly_brdg_teipw_1_n: 1;    //  13
    UINT32 reg_soft_rst_fly_brdg_teipw_2_n: 1;    //  14
    UINT32 reg_soft_rst_fly_brdg_teipw_3_n: 1;    //  15
    UINT32 reg_soft_rst_hsp_brdg_imx_6_n: 1;    //  16
    UINT32 reg_soft_rst_hsp_brdg_imx_7_n: 1;    //  17
    UINT32 reg_soft_rst_hsp_brdg_nd0_0_n: 1;    //  18
    UINT32 reg_soft_rst_hsp_brdg_nd0_1_n: 1;    //  19
    UINT32 reg_soft_rst_hsp_brdg_nd0_4_n: 1;    //  20
    UINT32 reg_soft_rst_hsp_brdg_nd0_5_n: 1;    //  21
    UINT32 reg_soft_rst_pes_brdg_te_6_n: 1;    //  22
    UINT32 reg_soft_rst_pes_brdg_te_7_n: 1;    //  23
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}BCRG_CTRL_HDR_CRG_BND_HDR3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_1010    crg_bnd_hdr4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_ipw_hdr_n: 1;    //  0
    UINT32 reg_soft_rst_apb_ipw_vdo_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BCRG_CTRL_HDR_CRG_BND_HDR4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bcrg_ctrl_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BCRG_CTRL_HDR_CRG_BND_HDR0_O24A0_T    crg_bnd_hdr0;         // 0xCCC5_1000
    BCRG_CTRL_HDR_CRG_BND_HDR1_O24A0_T    crg_bnd_hdr1;         // 0xCCC5_1004
    BCRG_CTRL_HDR_CRG_BND_HDR2_O24A0_T    crg_bnd_hdr2;         // 0xCCC5_1008
    BCRG_CTRL_HDR_CRG_BND_HDR3_O24A0_T    crg_bnd_hdr3;         // 0xCCC5_100C
    BCRG_CTRL_HDR_CRG_BND_HDR4_O24A0_T    crg_bnd_hdr4;         // 0xCCC5_1010
}BCRG_CTRL_HDR_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BCRG_CTRL_HDR_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

