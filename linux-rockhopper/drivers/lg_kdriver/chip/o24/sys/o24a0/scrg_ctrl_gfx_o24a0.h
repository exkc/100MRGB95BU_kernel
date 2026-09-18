#ifndef _SCRG_CTRL_GFX_REG_O24A0_H_
#define _SCRG_CTRL_GFX_REG_O24A0_H_

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
    0xC415_0000    crg_gfx0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_GFX_CRG_GFX0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC415_0004    crg_gfx1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_GFX_CRG_GFX1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC415_0008    crg_gfx2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx_apb_clk_gate_en   :  1,    //      0
    reg_gfx_core_clk_gate_en  :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_GFX_CRG_GFX2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC415_000C    crg_gfx3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_gfxc_n       :  1,    //      0
    reg_soft_rst_gfxp_n       :  1,    //      1
    reg_soft_rst_p_gfx_0_axi_bnd_n: 1,    //   2
    reg_soft_rst_x_gfx_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_x_gfx_0_axi_n:  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_GFX_CRG_GFX3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_gfx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GFX_CRG_GFX0_O24A0_T     crg_gfx0   ;             // 0xC415_0000
    SCRG_CTRL_GFX_CRG_GFX1_O24A0_T     crg_gfx1   ;             // 0xC415_0004
    SCRG_CTRL_GFX_CRG_GFX2_O24A0_T     crg_gfx2   ;             // 0xC415_0008
    SCRG_CTRL_GFX_CRG_GFX3_O24A0_T     crg_gfx3   ;             // 0xC415_000C
}SCRG_CTRL_GFX_REG_O24A0_T;
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

#define SCRG_CTRL_GFX_CRG_GFX0_O24A0_T_OFF                  (BASEADDRESS+0x0000)
#define SCRG_CTRL_GFX_CRG_GFX1_O24A0_T_OFF                  (BASEADDRESS+0x0004)
#define SCRG_CTRL_GFX_CRG_GFX2_O24A0_T_OFF                  (BASEADDRESS+0x0008)
#define SCRG_CTRL_GFX_CRG_GFX3_O24A0_T_OFF                  (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC415_0000    crg_gfx0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_GFX_CRG_GFX0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC415_0004    crg_gfx1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_GFX_CRG_GFX1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC415_0008    crg_gfx2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gfx_apb_clk_gate_en: 1;    //   0
    UINT32 reg_gfx_core_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_GFX_CRG_GFX2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC415_000C    crg_gfx3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_gfxc_n:  1;    //      0
    UINT32 reg_soft_rst_gfxp_n:  1;    //      1
    UINT32 reg_soft_rst_p_gfx_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_x_gfx_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_gfx_0_axi_n: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_GFX_CRG_GFX3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_gfx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GFX_CRG_GFX0_O24A0_T     crg_gfx0   ;             // 0xC415_0000
    SCRG_CTRL_GFX_CRG_GFX1_O24A0_T     crg_gfx1   ;             // 0xC415_0004
    SCRG_CTRL_GFX_CRG_GFX2_O24A0_T     crg_gfx2   ;             // 0xC415_0008
    SCRG_CTRL_GFX_CRG_GFX3_O24A0_T     crg_gfx3   ;             // 0xC415_000C
}SCRG_CTRL_GFX_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_GFX_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

