#ifndef _SCRG_CTRL_TIVSB_REG_O26A0_H_
#define _SCRG_CTRL_TIVSB_REG_O26A0_H_

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
    0xCE42_0000    crg_tivsb000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_TIVSB_CRG_TIVSB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE42_0004    crg_tivsb001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_TIVSB_CRG_TIVSB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE42_0008    crg_tivsb002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_icod_0__bus_662_clk_gate_en: 1,    //  0
    reg_adaprx_x_te_0__bus_662_clk_gate_en: 1,    //  1
    reg_adaprx_x_venc_0__bus_662_clk_gate_en: 1,    //  2
    reg_adaptx_x_tiv_0__bus_662_clk_gate_en: 1,    //  3
    reg_bus_662_clk_gate_en   :  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_TIVSB_CRG_TIVSB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE42_000C    crg_tivsb003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_bus_662_n    :  1,    //      0
    reg_soft_rst_p_icod_0_axi_bnd_n: 1,    //  1
    reg_soft_rst_p_te_0_axi_bnd_n: 1,    //    2
    reg_soft_rst_p_tiv_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_p_venc_0_axi_bnd_n: 1,    //  4
    reg_soft_rst_x_icod_0_axi_n: 1,    //      5
    reg_soft_rst_x_te_0_axi_n :  1,    //      6
    reg_soft_rst_x_tiv_0_axi_n:  1,    //      7
    reg_soft_rst_x_venc_0_axi_n: 1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_TIVSB_CRG_TIVSB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_tivsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TIVSB_CRG_TIVSB000_O26A0_T    crg_tivsb000;       // 0xCE42_0000
    SCRG_CTRL_TIVSB_CRG_TIVSB001_O26A0_T    crg_tivsb001;       // 0xCE42_0004
    SCRG_CTRL_TIVSB_CRG_TIVSB002_O26A0_T    crg_tivsb002;       // 0xCE42_0008
    SCRG_CTRL_TIVSB_CRG_TIVSB003_O26A0_T    crg_tivsb003;       // 0xCE42_000C
}SCRG_CTRL_TIVSB_REG_O26A0_T;
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

#define SCRG_CTRL_TIVSB_CRG_TIVSB000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define SCRG_CTRL_TIVSB_CRG_TIVSB001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define SCRG_CTRL_TIVSB_CRG_TIVSB002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define SCRG_CTRL_TIVSB_CRG_TIVSB003_O26A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCE42_0000    crg_tivsb000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_TIVSB_CRG_TIVSB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE42_0004    crg_tivsb001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_TIVSB_CRG_TIVSB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE42_0008    crg_tivsb002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_icod_0__bus_662_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_x_te_0__bus_662_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_x_venc_0__bus_662_clk_gate_en: 1;    //  2
    UINT32 reg_adaptx_x_tiv_0__bus_662_clk_gate_en: 1;    //  3
    UINT32 reg_bus_662_clk_gate_en: 1;    //   4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_TIVSB_CRG_TIVSB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE42_000C    crg_tivsb003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_bus_662_n: 1;    //    0
    UINT32 reg_soft_rst_p_icod_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_te_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_tiv_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_venc_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_x_icod_0_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_te_0_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_tiv_0_axi_n: 1;    //  7
    UINT32 reg_soft_rst_x_venc_0_axi_n: 1;    //  8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_TIVSB_CRG_TIVSB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_tivsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_TIVSB_CRG_TIVSB000_O26A0_T    crg_tivsb000;       // 0xCE42_0000
    SCRG_CTRL_TIVSB_CRG_TIVSB001_O26A0_T    crg_tivsb001;       // 0xCE42_0004
    SCRG_CTRL_TIVSB_CRG_TIVSB002_O26A0_T    crg_tivsb002;       // 0xCE42_0008
    SCRG_CTRL_TIVSB_CRG_TIVSB003_O26A0_T    crg_tivsb003;       // 0xCE42_000C
}SCRG_CTRL_TIVSB_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_TIVSB_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

