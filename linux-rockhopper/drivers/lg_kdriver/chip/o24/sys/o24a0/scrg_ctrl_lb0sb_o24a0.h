#ifndef _SCRG_CTRL_LB0SB_REG_O24A0_H_
#define _SCRG_CTRL_LB0SB_REG_O24A0_H_

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
    0xCCDE_0000    crg_sb_lb00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LB0SB_CRG_SB_LB00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDE_0004    crg_sb_lb01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LB0SB_CRG_SB_LB01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDE_0008    crg_sb_lb02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_884_clk_gate_en   :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_LB0SB_CRG_SB_LB02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDE_000C    crg_sb_lb03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_bus_884_n    :  1,    //      0
    reg_soft_rst_p_cvi_0_axi_bnd_n: 1,    //   1
    reg_soft_rst_p_dbb_0_axi_bnd_n: 1,    //   2
    reg_soft_rst_p_hdmi_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_p_lb0_0_axi_bnd_n: 1,    //   4
    reg_soft_rst_p_te_0_axi_bnd_n: 1,    //    5
    reg_soft_rst_x_cvi_0_axi_n:  1,    //      6
    reg_soft_rst_x_dbb_0_axi_n:  1,    //      7
    reg_soft_rst_x_hdmi_0_axi_n: 1,    //      8
    reg_soft_rst_x_lb0_0_axi_bnd_n: 1,    //   9
    reg_soft_rst_x_lb0_0_axi_n:  1,    //     10
    reg_soft_rst_x_te_0_axi_n :  1,    //     11
                              : 20;    //  31:12 reserved
}SCRG_CTRL_LB0SB_CRG_SB_LB03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lb0sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LB0SB_CRG_SB_LB00_O24A0_T    crg_sb_lb00;         // 0xCCDE_0000
    SCRG_CTRL_LB0SB_CRG_SB_LB01_O24A0_T    crg_sb_lb01;         // 0xCCDE_0004
    SCRG_CTRL_LB0SB_CRG_SB_LB02_O24A0_T    crg_sb_lb02;         // 0xCCDE_0008
    SCRG_CTRL_LB0SB_CRG_SB_LB03_O24A0_T    crg_sb_lb03;         // 0xCCDE_000C
}SCRG_CTRL_LB0SB_REG_O24A0_T;
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

#define SCRG_CTRL_LB0SB_CRG_SB_LB00_O24A0_T_OFF             (BASEADDRESS+0x0000)
#define SCRG_CTRL_LB0SB_CRG_SB_LB01_O24A0_T_OFF             (BASEADDRESS+0x0004)
#define SCRG_CTRL_LB0SB_CRG_SB_LB02_O24A0_T_OFF             (BASEADDRESS+0x0008)
#define SCRG_CTRL_LB0SB_CRG_SB_LB03_O24A0_T_OFF             (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCDE_0000    crg_sb_lb00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LB0SB_CRG_SB_LB00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDE_0004    crg_sb_lb01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LB0SB_CRG_SB_LB01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDE_0008    crg_sb_lb02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_884_clk_gate_en: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_LB0SB_CRG_SB_LB02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCDE_000C    crg_sb_lb03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_bus_884_n: 1;    //    0
    UINT32 reg_soft_rst_p_cvi_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_dbb_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_hdmi_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_lb0_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_te_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_cvi_0_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_dbb_0_axi_n: 1;    //  7
    UINT32 reg_soft_rst_x_hdmi_0_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_lb0_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_lb0_0_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_te_0_axi_n: 1;    //  11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SCRG_CTRL_LB0SB_CRG_SB_LB03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lb0sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LB0SB_CRG_SB_LB00_O24A0_T    crg_sb_lb00;         // 0xCCDE_0000
    SCRG_CTRL_LB0SB_CRG_SB_LB01_O24A0_T    crg_sb_lb01;         // 0xCCDE_0004
    SCRG_CTRL_LB0SB_CRG_SB_LB02_O24A0_T    crg_sb_lb02;         // 0xCCDE_0008
    SCRG_CTRL_LB0SB_CRG_SB_LB03_O24A0_T    crg_sb_lb03;         // 0xCCDE_000C
}SCRG_CTRL_LB0SB_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_LB0SB_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

