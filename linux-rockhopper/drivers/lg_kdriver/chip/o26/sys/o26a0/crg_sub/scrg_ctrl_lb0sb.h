#ifndef _SCRG_CTRL_LB0SB_REG_O26A0_H_
#define _SCRG_CTRL_LB0SB_REG_O26A0_H_

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
    0xCC62_0000    crg_lb0sb000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LB0SB_CRG_LB0SB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC62_0004    crg_lb0sb001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LB0SB_CRG_LB0SB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC62_0008    crg_lb0sb002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_cvi_0__bus_884_clk_gate_en: 1,    //  0
    reg_adaprx_x_dnsr0_0__bus_884_clk_gate_en: 1,    //  1
    reg_adaprx_x_dnsr1_0__bus_884_clk_gate_en: 1,    //  2
    reg_adaprx_x_hdmi_0__bus_884_clk_gate_en: 1,    //  3
    reg_adaptx_x_lb0_0__bus_884_clk_gate_en: 1,    //  4
    reg_bus_884_clk_gate_en   :  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_LB0SB_CRG_LB0SB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC62_000C    crg_lb0sb003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_bus_884_n    :  1,    //      0
    reg_soft_rst_p_cvi_0_axi_bnd_n: 1,    //   1
    reg_soft_rst_p_dnsr0_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_p_dnsr1_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_p_hdmi_0_axi_bnd_n: 1,    //  4
    reg_soft_rst_p_lb0_0_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_cvi_0_axi_n:  1,    //      6
    reg_soft_rst_x_dnsr0_0_axi_n: 1,    //     7
    reg_soft_rst_x_dnsr1_0_axi_n: 1,    //     8
    reg_soft_rst_x_hdmi_0_axi_n: 1,    //      9
    reg_soft_rst_x_lb0_0_axi_n:  1,    //     10
                              : 21;    //  31:11 reserved
}SCRG_CTRL_LB0SB_CRG_LB0SB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lb0sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LB0SB_CRG_LB0SB000_O26A0_T    crg_lb0sb000;       // 0xCC62_0000
    SCRG_CTRL_LB0SB_CRG_LB0SB001_O26A0_T    crg_lb0sb001;       // 0xCC62_0004
    SCRG_CTRL_LB0SB_CRG_LB0SB002_O26A0_T    crg_lb0sb002;       // 0xCC62_0008
    SCRG_CTRL_LB0SB_CRG_LB0SB003_O26A0_T    crg_lb0sb003;       // 0xCC62_000C
}SCRG_CTRL_LB0SB_REG_O26A0_T;
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

#define SCRG_CTRL_LB0SB_CRG_LB0SB000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define SCRG_CTRL_LB0SB_CRG_LB0SB001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define SCRG_CTRL_LB0SB_CRG_LB0SB002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define SCRG_CTRL_LB0SB_CRG_LB0SB003_O26A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC62_0000    crg_lb0sb000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LB0SB_CRG_LB0SB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC62_0004    crg_lb0sb001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LB0SB_CRG_LB0SB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC62_0008    crg_lb0sb002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_cvi_0__bus_884_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_x_dnsr0_0__bus_884_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_x_dnsr1_0__bus_884_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_x_hdmi_0__bus_884_clk_gate_en: 1;    //  3
    UINT32 reg_adaptx_x_lb0_0__bus_884_clk_gate_en: 1;    //  4
    UINT32 reg_bus_884_clk_gate_en: 1;    //   5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_LB0SB_CRG_LB0SB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC62_000C    crg_lb0sb003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_bus_884_n: 1;    //    0
    UINT32 reg_soft_rst_p_cvi_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_dnsr0_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_dnsr1_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_hdmi_0_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_lb0_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_cvi_0_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_dnsr0_0_axi_n: 1;    //  7
    UINT32 reg_soft_rst_x_dnsr1_0_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_hdmi_0_axi_n: 1;    //  9
    UINT32 reg_soft_rst_x_lb0_0_axi_n: 1;    //  10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_LB0SB_CRG_LB0SB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lb0sb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LB0SB_CRG_LB0SB000_O26A0_T    crg_lb0sb000;       // 0xCC62_0000
    SCRG_CTRL_LB0SB_CRG_LB0SB001_O26A0_T    crg_lb0sb001;       // 0xCC62_0004
    SCRG_CTRL_LB0SB_CRG_LB0SB002_O26A0_T    crg_lb0sb002;       // 0xCC62_0008
    SCRG_CTRL_LB0SB_CRG_LB0SB003_O26A0_T    crg_lb0sb003;       // 0xCC62_000C
}SCRG_CTRL_LB0SB_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_LB0SB_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

