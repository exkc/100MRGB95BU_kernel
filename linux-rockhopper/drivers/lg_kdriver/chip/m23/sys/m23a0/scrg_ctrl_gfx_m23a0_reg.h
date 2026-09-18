#ifndef _SCRG_CTRL_GFX_M23A0_REG_H_
#define _SCRG_CTRL_GFX_M23A0_REG_H_

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
    0xC471_0000    crg_gfx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_GFX_CRG_GFX00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC471_0004    crg_gfx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_GFX_CRG_GFX01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC471_0008    crg_gfx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx_apb_clk_gate_en   :  1,    //      0
    reg_gfx_core_clk_gate_en  :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_GFX_CRG_GFX02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC471_000C    crg_gfx03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_gfxc_n       :  1,    //      0
    reg_soft_rst_gfxp_n       :  1,    //      1
    reg_soft_rst_p_gfx_0_axi_bnd_n: 1,    //   2
    reg_soft_rst_x_gfx_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_x_gfx_0_axi_n:  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_GFX_CRG_GFX03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_gfx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GFX_CRG_GFX00_M23A0_T    crg_gfx00  ;             // 0xC471_0000
    SCRG_CTRL_GFX_CRG_GFX01_M23A0_T    crg_gfx01  ;             // 0xC471_0004
    SCRG_CTRL_GFX_CRG_GFX02_M23A0_T    crg_gfx02  ;             // 0xC471_0008
    SCRG_CTRL_GFX_CRG_GFX03_M23A0_T    crg_gfx03  ;             // 0xC471_000C
}SCRG_CTRL_GFX_REG_M23A0_T;
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

#define SCRG_CTRL_GFX_CRG_GFX00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_GFX_CRG_GFX01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_GFX_CRG_GFX02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_GFX_CRG_GFX03_M23A0_T_OFF                 (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC471_0000    crg_gfx00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_GFX_CRG_GFX00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC471_0004    crg_gfx01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_GFX_CRG_GFX01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC471_0008    crg_gfx02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gfx_apb_clk_gate_en: 1;    //   0
    UINT32 reg_gfx_core_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_GFX_CRG_GFX02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC471_000C    crg_gfx03 ''
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
}SCRG_CTRL_GFX_CRG_GFX03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_gfx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GFX_CRG_GFX00_M23A0_T    crg_gfx00  ;             // 0xC471_0000
    SCRG_CTRL_GFX_CRG_GFX01_M23A0_T    crg_gfx01  ;             // 0xC471_0004
    SCRG_CTRL_GFX_CRG_GFX02_M23A0_T    crg_gfx02  ;             // 0xC471_0008
    SCRG_CTRL_GFX_CRG_GFX03_M23A0_T    crg_gfx03  ;             // 0xC471_000C
}SCRG_CTRL_GFX_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

