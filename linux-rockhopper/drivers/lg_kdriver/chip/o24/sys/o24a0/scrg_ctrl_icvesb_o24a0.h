#ifndef _SCRG_CTRL_ICVESB_REG_O24A0_H_
#define _SCRG_CTRL_ICVESB_REG_O24A0_H_

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
    0xCE89_0000    crg_sb_icve0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ICVESB_CRG_SB_ICVE0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE89_0004    crg_sb_icve1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ICVESB_CRG_SB_ICVE1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE89_0008    crg_sb_icve2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_async_axi_884_clk_gate_en: 1,    //    0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_ICVESB_CRG_SB_ICVE2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE89_000C    crg_sb_icve3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_async_axi_884_n: 1,    //     0
    reg_soft_rst_p_icod_0_axi_bnd_n: 1,    //  1
    reg_soft_rst_p_icod_ch_mux_axi_bnd_n: 1,    //  2
    reg_soft_rst_p_icve_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_x_icod_0_axi_n: 1,    //      4
    reg_soft_rst_x_icod_ch_mux_axi_n: 1,    //  5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_ICVESB_CRG_SB_ICVE3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_icvesb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ICVESB_CRG_SB_ICVE0_O24A0_T    crg_sb_icve0;      // 0xCE89_0000
    SCRG_CTRL_ICVESB_CRG_SB_ICVE1_O24A0_T    crg_sb_icve1;      // 0xCE89_0004
    SCRG_CTRL_ICVESB_CRG_SB_ICVE2_O24A0_T    crg_sb_icve2;      // 0xCE89_0008
    SCRG_CTRL_ICVESB_CRG_SB_ICVE3_O24A0_T    crg_sb_icve3;      // 0xCE89_000C
}SCRG_CTRL_ICVESB_REG_O24A0_T;
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

#define SCRG_CTRL_ICVESB_CRG_SB_ICVE0_O24A0_T_OFF           (BASEADDRESS+0x0000)
#define SCRG_CTRL_ICVESB_CRG_SB_ICVE1_O24A0_T_OFF           (BASEADDRESS+0x0004)
#define SCRG_CTRL_ICVESB_CRG_SB_ICVE2_O24A0_T_OFF           (BASEADDRESS+0x0008)
#define SCRG_CTRL_ICVESB_CRG_SB_ICVE3_O24A0_T_OFF           (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCE89_0000    crg_sb_icve0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ICVESB_CRG_SB_ICVE0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE89_0004    crg_sb_icve1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ICVESB_CRG_SB_ICVE1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE89_0008    crg_sb_icve2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_async_axi_884_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_ICVESB_CRG_SB_ICVE2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE89_000C    crg_sb_icve3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_async_axi_884_n: 1;    //  0
    UINT32 reg_soft_rst_p_icod_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_icod_ch_mux_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_icve_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_icod_0_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_icod_ch_mux_axi_n: 1;    //  5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_ICVESB_CRG_SB_ICVE3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_icvesb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ICVESB_CRG_SB_ICVE0_O24A0_T    crg_sb_icve0;      // 0xCE89_0000
    SCRG_CTRL_ICVESB_CRG_SB_ICVE1_O24A0_T    crg_sb_icve1;      // 0xCE89_0004
    SCRG_CTRL_ICVESB_CRG_SB_ICVE2_O24A0_T    crg_sb_icve2;      // 0xCE89_0008
    SCRG_CTRL_ICVESB_CRG_SB_ICVE3_O24A0_T    crg_sb_icve3;      // 0xCE89_000C
}SCRG_CTRL_ICVESB_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_ICVESB_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

