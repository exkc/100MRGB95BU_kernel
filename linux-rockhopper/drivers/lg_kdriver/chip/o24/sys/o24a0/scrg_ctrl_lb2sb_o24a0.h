#ifndef _SCRG_CTRL_LB2SB_REG_O24A0_H_
#define _SCRG_CTRL_LB2SB_REG_O24A0_H_

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
    0xC41F_0000    crg_sb_lb20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LB2SB_CRG_SB_LB20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41F_0004    crg_sb_lb21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LB2SB_CRG_SB_LB21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41F_0008    crg_sb_lb22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_442_clk_gate_en   :  1,    //      0
    reg_bus_884_clk_gate_en   :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_LB2SB_CRG_SB_LB22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41F_000C    crg_sb_lb23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_bus_442_n    :  1,    //      0
    reg_soft_rst_bus_884_n    :  1,    //      1
    reg_soft_rst_p_dmcu_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_p_lb0sb_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_p_lb1sb_0_axi_bnd_n: 1,    //  4
    reg_soft_rst_p_lb2_0_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_dmcu_0_axi_n: 1,    //      6
    reg_soft_rst_x_lb0sb_0_axi_n: 1,    //     7
    reg_soft_rst_x_lb1sb_0_axi_n: 1,    //     8
    reg_soft_rst_x_lb2_0_axi_bnd_n: 1,    //   9
    reg_soft_rst_x_lb2_0_axi_n:  1,    //     10
                              : 21;    //  31:11 reserved
}SCRG_CTRL_LB2SB_CRG_SB_LB23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lb2sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LB2SB_CRG_SB_LB20_O24A0_T    crg_sb_lb20;         // 0xC41F_0000
    SCRG_CTRL_LB2SB_CRG_SB_LB21_O24A0_T    crg_sb_lb21;         // 0xC41F_0004
    SCRG_CTRL_LB2SB_CRG_SB_LB22_O24A0_T    crg_sb_lb22;         // 0xC41F_0008
    SCRG_CTRL_LB2SB_CRG_SB_LB23_O24A0_T    crg_sb_lb23;         // 0xC41F_000C
}SCRG_CTRL_LB2SB_REG_O24A0_T;
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

#define SCRG_CTRL_LB2SB_CRG_SB_LB20_O24A0_T_OFF             (BASEADDRESS+0x0000)
#define SCRG_CTRL_LB2SB_CRG_SB_LB21_O24A0_T_OFF             (BASEADDRESS+0x0004)
#define SCRG_CTRL_LB2SB_CRG_SB_LB22_O24A0_T_OFF             (BASEADDRESS+0x0008)
#define SCRG_CTRL_LB2SB_CRG_SB_LB23_O24A0_T_OFF             (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC41F_0000    crg_sb_lb20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LB2SB_CRG_SB_LB20_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41F_0004    crg_sb_lb21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LB2SB_CRG_SB_LB21_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41F_0008    crg_sb_lb22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_442_clk_gate_en: 1;    //   0
    UINT32 reg_bus_884_clk_gate_en: 1;    //   1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_LB2SB_CRG_SB_LB22_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC41F_000C    crg_sb_lb23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_bus_442_n: 1;    //    0
    UINT32 reg_soft_rst_bus_884_n: 1;    //    1
    UINT32 reg_soft_rst_p_dmcu_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_lb0sb_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_lb1sb_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_lb2_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_dmcu_0_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_lb0sb_0_axi_n: 1;    //  7
    UINT32 reg_soft_rst_x_lb1sb_0_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_lb2_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_lb2_0_axi_n: 1;    //  10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_LB2SB_CRG_SB_LB23_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lb2sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LB2SB_CRG_SB_LB20_O24A0_T    crg_sb_lb20;         // 0xC41F_0000
    SCRG_CTRL_LB2SB_CRG_SB_LB21_O24A0_T    crg_sb_lb21;         // 0xC41F_0004
    SCRG_CTRL_LB2SB_CRG_SB_LB22_O24A0_T    crg_sb_lb22;         // 0xC41F_0008
    SCRG_CTRL_LB2SB_CRG_SB_LB23_O24A0_T    crg_sb_lb23;         // 0xC41F_000C
}SCRG_CTRL_LB2SB_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_LB2SB_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

