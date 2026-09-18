#ifndef _SCRG_CTRL_GFX_REG_O26A0_H_
#define _SCRG_CTRL_GFX_REG_O26A0_H_

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
    0xC409_0000    crg_gfx000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_GFX_CRG_GFX000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC409_0004    crg_gfx001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_GFX_CRG_GFX001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC409_0008    crg_gfx002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_x_gfx_0__gfx_core_clk_gate_en: 1,    //  0
    reg_gfx_apb_clk_gate_en   :  1,    //      1
    reg_gfx_core_clk_gate_en  :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_GFX_CRG_GFX002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC409_000C    crg_gfx003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_gfxc_n       :  1,    //      0
    reg_soft_rst_gfxp_n       :  1,    //      1
    reg_soft_rst_p_gfx_0_axi_bnd_n: 1,    //   2
    reg_soft_rst_x_gfx_0_axi_n:  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_GFX_CRG_GFX003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_gfx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GFX_CRG_GFX000_O26A0_T    crg_gfx000;             // 0xC409_0000
    SCRG_CTRL_GFX_CRG_GFX001_O26A0_T    crg_gfx001;             // 0xC409_0004
    SCRG_CTRL_GFX_CRG_GFX002_O26A0_T    crg_gfx002;             // 0xC409_0008
    SCRG_CTRL_GFX_CRG_GFX003_O26A0_T    crg_gfx003;             // 0xC409_000C
}SCRG_CTRL_GFX_REG_O26A0_T;
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

#define SCRG_CTRL_GFX_CRG_GFX000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_GFX_CRG_GFX001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_GFX_CRG_GFX002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_GFX_CRG_GFX003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC409_0000    crg_gfx000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_GFX_CRG_GFX000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC409_0004    crg_gfx001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_GFX_CRG_GFX001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC409_0008    crg_gfx002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_x_gfx_0__gfx_core_clk_gate_en: 1;    //  0
    UINT32 reg_gfx_apb_clk_gate_en: 1;    //   1
    UINT32 reg_gfx_core_clk_gate_en: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_GFX_CRG_GFX002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC409_000C    crg_gfx003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_gfxc_n:  1;    //      0
    UINT32 reg_soft_rst_gfxp_n:  1;    //      1
    UINT32 reg_soft_rst_p_gfx_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_x_gfx_0_axi_n: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_GFX_CRG_GFX003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_gfx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_GFX_CRG_GFX000_O26A0_T    crg_gfx000;             // 0xC409_0000
    SCRG_CTRL_GFX_CRG_GFX001_O26A0_T    crg_gfx001;             // 0xC409_0004
    SCRG_CTRL_GFX_CRG_GFX002_O26A0_T    crg_gfx002;             // 0xC409_0008
    SCRG_CTRL_GFX_CRG_GFX003_O26A0_T    crg_gfx003;             // 0xC409_000C
}SCRG_CTRL_GFX_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_GFX_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

