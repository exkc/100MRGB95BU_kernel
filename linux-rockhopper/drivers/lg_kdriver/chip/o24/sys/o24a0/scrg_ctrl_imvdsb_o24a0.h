#ifndef _SCRG_CTRL_IMVDSB_REG_O24A0_H_
#define _SCRG_CTRL_IMVDSB_REG_O24A0_H_

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
    0xCC98_0000    crg_sb_imvd0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_IMVDSB_CRG_SB_IMVD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC98_0004    crg_sb_imvd1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_IMVDSB_CRG_SB_IMVD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC98_0008    crg_sb_imvd2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_async_axi_400_clk_gate_en: 1,    //    0
    reg_async_axi_884_clk_gate_en: 1,    //    1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_IMVDSB_CRG_SB_IMVD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC98_000C    crg_sb_imvd3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_ch_mux_imvdsb_4_axi_n: 1,    //  0
    reg_soft_rst_p_ch_mux_imvdsb_5_axi_n: 1,    //  1
    reg_soft_rst_p_imvd_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_p_imvd_1_axi_bnd_n: 1,    //  3
    reg_soft_rst_p_imvd_2_axi_bnd_n: 1,    //  4
    reg_soft_rst_p_imvd_3_axi_bnd_n: 1,    //  5
    reg_soft_rst_p_imx_1_axi_bnd_n: 1,    //   6
    reg_soft_rst_p_imx_3_axi_bnd_n: 1,    //   7
    reg_soft_rst_p_imx_5_axi_bnd_n: 1,    //   8
    reg_soft_rst_p_imx_7_axi_bnd_n: 1,    //   9
    reg_soft_rst_p_rx_imvdsb_4_axi_n: 1,    //  10
    reg_soft_rst_p_rx_imvdsb_5_axi_n: 1,    //  11
    reg_soft_rst_p_tx_imvdsb_4_axi_n: 1,    //  12
    reg_soft_rst_p_tx_imvdsb_5_axi_n: 1,    //  13
    reg_soft_rst_p_vdo_0_axi_bnd_n: 1,    //  14
    reg_soft_rst_p_vdo_1_axi_bnd_n: 1,    //  15
    reg_soft_rst_p_vdo_2_axi_bnd_n: 1,    //  16
    reg_soft_rst_p_vdo_3_axi_bnd_n: 1,    //  17
    reg_soft_rst_x_ch_mux_imvdsb_4_axi_n: 1,    //  18
    reg_soft_rst_x_ch_mux_imvdsb_5_axi_n: 1,    //  19
    reg_soft_rst_x_imvd_0_axi_bnd_n: 1,    //  20
    reg_soft_rst_x_imvd_0_axi_n: 1,    //     21
    reg_soft_rst_x_imvd_1_axi_bnd_n: 1,    //  22
    reg_soft_rst_x_imvd_1_axi_n: 1,    //     23
    reg_soft_rst_x_imvd_2_axi_bnd_n: 1,    //  24
    reg_soft_rst_x_imvd_2_axi_n: 1,    //     25
    reg_soft_rst_x_imvd_3_axi_bnd_n: 1,    //  26
    reg_soft_rst_x_imvd_3_axi_n: 1,    //     27
    reg_soft_rst_x_imx_1_axi_n:  1,    //     28
    reg_soft_rst_x_imx_3_axi_n:  1,    //     29
    reg_soft_rst_x_imx_5_axi_n:  1,    //     30
    reg_soft_rst_x_imx_7_axi_n:  1;    //     31
}SCRG_CTRL_IMVDSB_CRG_SB_IMVD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC98_0010    crg_sb_imvd4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_x_rx_imvdsb_4_axi_n: 1,    //  0
    reg_soft_rst_x_rx_imvdsb_5_axi_n: 1,    //  1
    reg_soft_rst_x_tx_imvdsb_4_axi_n: 1,    //  2
    reg_soft_rst_x_tx_imvdsb_5_axi_n: 1,    //  3
    reg_soft_rst_x_vdo_0_axi_n:  1,    //      4
    reg_soft_rst_x_vdo_1_axi_n:  1,    //      5
    reg_soft_rst_x_vdo_2_axi_n:  1,    //      6
    reg_soft_rst_x_vdo_3_axi_n:  1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_IMVDSB_CRG_SB_IMVD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_imvdsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_IMVDSB_CRG_SB_IMVD0_O24A0_T    crg_sb_imvd0;      // 0xCC98_0000
    SCRG_CTRL_IMVDSB_CRG_SB_IMVD1_O24A0_T    crg_sb_imvd1;      // 0xCC98_0004
    SCRG_CTRL_IMVDSB_CRG_SB_IMVD2_O24A0_T    crg_sb_imvd2;      // 0xCC98_0008
    SCRG_CTRL_IMVDSB_CRG_SB_IMVD3_O24A0_T    crg_sb_imvd3;      // 0xCC98_000C
    SCRG_CTRL_IMVDSB_CRG_SB_IMVD4_O24A0_T    crg_sb_imvd4;      // 0xCC98_0010
}SCRG_CTRL_IMVDSB_REG_O24A0_T;
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

#define SCRG_CTRL_IMVDSB_CRG_SB_IMVD0_O24A0_T_OFF           (BASEADDRESS+0x0000)
#define SCRG_CTRL_IMVDSB_CRG_SB_IMVD1_O24A0_T_OFF           (BASEADDRESS+0x0004)
#define SCRG_CTRL_IMVDSB_CRG_SB_IMVD2_O24A0_T_OFF           (BASEADDRESS+0x0008)
#define SCRG_CTRL_IMVDSB_CRG_SB_IMVD3_O24A0_T_OFF           (BASEADDRESS+0x000C)
#define SCRG_CTRL_IMVDSB_CRG_SB_IMVD4_O24A0_T_OFF           (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC98_0000    crg_sb_imvd0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_IMVDSB_CRG_SB_IMVD0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC98_0004    crg_sb_imvd1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_IMVDSB_CRG_SB_IMVD1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC98_0008    crg_sb_imvd2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_async_axi_400_clk_gate_en: 1;    //  0
    UINT32 reg_async_axi_884_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_IMVDSB_CRG_SB_IMVD2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC98_000C    crg_sb_imvd3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_ch_mux_imvdsb_4_axi_n: 1;    //  0
    UINT32 reg_soft_rst_p_ch_mux_imvdsb_5_axi_n: 1;    //  1
    UINT32 reg_soft_rst_p_imvd_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_imvd_1_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_imvd_2_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_imvd_3_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_imx_1_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_imx_3_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_imx_5_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_imx_7_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_rx_imvdsb_4_axi_n: 1;    //  10
    UINT32 reg_soft_rst_p_rx_imvdsb_5_axi_n: 1;    //  11
    UINT32 reg_soft_rst_p_tx_imvdsb_4_axi_n: 1;    //  12
    UINT32 reg_soft_rst_p_tx_imvdsb_5_axi_n: 1;    //  13
    UINT32 reg_soft_rst_p_vdo_0_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_p_vdo_1_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_p_vdo_2_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_p_vdo_3_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_x_ch_mux_imvdsb_4_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_ch_mux_imvdsb_5_axi_n: 1;    //  19
    UINT32 reg_soft_rst_x_imvd_0_axi_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_x_imvd_0_axi_n: 1;    //  21
    UINT32 reg_soft_rst_x_imvd_1_axi_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_x_imvd_1_axi_n: 1;    //  23
    UINT32 reg_soft_rst_x_imvd_2_axi_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_x_imvd_2_axi_n: 1;    //  25
    UINT32 reg_soft_rst_x_imvd_3_axi_bnd_n: 1;    //  26
    UINT32 reg_soft_rst_x_imvd_3_axi_n: 1;    //  27
    UINT32 reg_soft_rst_x_imx_1_axi_n: 1;    //  28
    UINT32 reg_soft_rst_x_imx_3_axi_n: 1;    //  29
    UINT32 reg_soft_rst_x_imx_5_axi_n: 1;    //  30
    UINT32 reg_soft_rst_x_imx_7_axi_n: 1;    //  31
    };
}SCRG_CTRL_IMVDSB_CRG_SB_IMVD3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC98_0010    crg_sb_imvd4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_x_rx_imvdsb_4_axi_n: 1;    //  0
    UINT32 reg_soft_rst_x_rx_imvdsb_5_axi_n: 1;    //  1
    UINT32 reg_soft_rst_x_tx_imvdsb_4_axi_n: 1;    //  2
    UINT32 reg_soft_rst_x_tx_imvdsb_5_axi_n: 1;    //  3
    UINT32 reg_soft_rst_x_vdo_0_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_vdo_1_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_vdo_2_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_vdo_3_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_IMVDSB_CRG_SB_IMVD4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_imvdsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_IMVDSB_CRG_SB_IMVD0_O24A0_T    crg_sb_imvd0;      // 0xCC98_0000
    SCRG_CTRL_IMVDSB_CRG_SB_IMVD1_O24A0_T    crg_sb_imvd1;      // 0xCC98_0004
    SCRG_CTRL_IMVDSB_CRG_SB_IMVD2_O24A0_T    crg_sb_imvd2;      // 0xCC98_0008
    SCRG_CTRL_IMVDSB_CRG_SB_IMVD3_O24A0_T    crg_sb_imvd3;      // 0xCC98_000C
    SCRG_CTRL_IMVDSB_CRG_SB_IMVD4_O24A0_T    crg_sb_imvd4;      // 0xCC98_0010
}SCRG_CTRL_IMVDSB_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_IMVDSB_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

