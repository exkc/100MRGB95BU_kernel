#ifndef _SCRG_CTRL_GFX_REG_H_
#define _SCRG_CTRL_GFX_REG_H_

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
    0xB_0000    crg_gfx00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_GFX_CRG_GFX00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xB_0004    crg_gfx01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_GFX_CRG_GFX01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xB_0008    crg_gfx02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx_apb_clk_gate_en   :  1,    //      0
    reg_gfx_core_clk_gate_en  :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_GFX_CRG_GFX02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xB_000C    crg_gfx03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_gfxc_n       :  1,    //      0
    reg_soft_rst_gfxp_n       :  1,    //      1
    reg_soft_rst_p_gfx_0_axi_bnd_n: 1,    //   2
    reg_soft_rst_x_gfx_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_x_gfx_0_axi_n:  1,    //      4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_GFX_CRG_GFX03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xB_0010    crg_gfx04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx_apb_clk_skip_ctrl :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_GFX_CRG_GFX04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xB_0014    crg_gfx05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx_core_clk_skip_ctrl:  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_GFX_CRG_GFX05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_gfx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GFX_CRG_GFX00_O22A0_T          crg_gfx00  ;             // 0xB_0000
    SCRG_CTRL_GFX_CRG_GFX01_O22A0_T          crg_gfx01  ;             // 0xB_0004
    SCRG_CTRL_GFX_CRG_GFX02_O22A0_T          crg_gfx02  ;             // 0xB_0008
    SCRG_CTRL_GFX_CRG_GFX03_O22A0_T          crg_gfx03  ;             // 0xB_000C
    SCRG_CTRL_GFX_CRG_GFX04_O22A0_T          crg_gfx04  ;             // 0xB_0010
    SCRG_CTRL_GFX_CRG_GFX05_O22A0_T          crg_gfx05  ;             // 0xB_0014
}SCRG_CTRL_GFX_REG_O22A0_T;
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

#define SCRG_CTRL_GFX_CRG_GFX00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_GFX_CRG_GFX01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_GFX_CRG_GFX02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_GFX_CRG_GFX03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_GFX_CRG_GFX04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_GFX_CRG_GFX05_O22A0_T_OFF                       (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xB_0000    crg_gfx00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_GFX_CRG_GFX00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xB_0004    crg_gfx01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_GFX_CRG_GFX01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xB_0008    crg_gfx02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gfx_apb_clk_gate_en: 1;    //   0
    UINT32 reg_gfx_core_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_GFX_CRG_GFX02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xB_000C    crg_gfx03 ''
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
}SCRG_CTRL_GFX_CRG_GFX03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xB_0010    crg_gfx04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gfx_apb_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_GFX_CRG_GFX04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xB_0014    crg_gfx05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gfx_core_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_GFX_CRG_GFX05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_gfx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GFX_CRG_GFX00_O22A0_T          crg_gfx00  ;             // 0xB_0000
    SCRG_CTRL_GFX_CRG_GFX01_O22A0_T          crg_gfx01  ;             // 0xB_0004
    SCRG_CTRL_GFX_CRG_GFX02_O22A0_T          crg_gfx02  ;             // 0xB_0008
    SCRG_CTRL_GFX_CRG_GFX03_O22A0_T          crg_gfx03  ;             // 0xB_000C
    SCRG_CTRL_GFX_CRG_GFX04_O22A0_T          crg_gfx04  ;             // 0xB_0010
    SCRG_CTRL_GFX_CRG_GFX05_O22A0_T          crg_gfx05  ;             // 0xB_0014
}SCRG_CTRL_GFX_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

