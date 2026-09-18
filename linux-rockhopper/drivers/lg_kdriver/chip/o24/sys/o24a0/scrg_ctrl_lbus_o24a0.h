#ifndef _SCRG_CTRL_LBUS_REG_O24A0_H_
#define _SCRG_CTRL_LBUS_REG_O24A0_H_

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
    0xC410_0000    crg_lbus0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_LBUS_CRG_LBUS0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_0004    crg_lbus1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_LBUS_CRG_LBUS1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_0008    crg_lbus2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_axi_884_clk_gate_en   :  1,    //      1
    reg_main_clk_gate_en      :  1,    //      2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_LBUS_CRG_LBUS2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_000C    crg_lbus3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_main_n       :  1,    //      1
    reg_soft_rst_p_aud_0_axi_bnd_n: 1,    //   2
    reg_soft_rst_p_cco_0_axi_bnd_n: 1,    //   3
    reg_soft_rst_p_cco_1_axi_bnd_n: 1,    //   4
    reg_soft_rst_p_conv_rx_tcon_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_p_conv_rx_vd0_0_axi_bnd_n: 1,    //  6
    reg_soft_rst_p_conv_rx_vd0_1_axi_bnd_n: 1,    //  7
    reg_soft_rst_p_conv_rx_vd1_0_axi_bnd_n: 1,    //  8
    reg_soft_rst_p_conv_rx_vd1_1_axi_bnd_n: 1,    //  9
    reg_soft_rst_p_conv_rx_vd2_1_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_conv_rx_vd2vmsb_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_p_conv_tx_tcon_0_axi_bnd_n: 1,    //  12
    reg_soft_rst_p_conv_tx_vd0_0_axi_bnd_n: 1,    //  13
    reg_soft_rst_p_conv_tx_vd0_1_axi_bnd_n: 1,    //  14
    reg_soft_rst_p_conv_tx_vd1_0_axi_bnd_n: 1,    //  15
    reg_soft_rst_p_conv_tx_vd1_1_axi_bnd_n: 1,    //  16
    reg_soft_rst_p_conv_tx_vd2_1_axi_bnd_n: 1,    //  17
    reg_soft_rst_p_conv_tx_vd2vmsb_0_axi_bnd_n: 1,    //  18
    reg_soft_rst_p_fmgsesb_0_axi_bnd_n: 1,    //  19
    reg_soft_rst_p_fmgsesb_1_axi_bnd_n: 1,    //  20
    reg_soft_rst_p_fmgsesb_2_axi_bnd_n: 1,    //  21
    reg_soft_rst_p_fmgsesb_3_axi_bnd_n: 1,    //  22
    reg_soft_rst_p_fmgsesb_4_axi_bnd_n: 1,    //  23
    reg_soft_rst_p_gfx_0_axi_bnd_n: 1,    //  24
    reg_soft_rst_p_gpu_0_axi_bnd_n: 1,    //  25
    reg_soft_rst_p_gpu_1_axi_bnd_n: 1,    //  26
    reg_soft_rst_p_icvesb_0_axi_bnd_n: 1,    //  27
    reg_soft_rst_p_imvdsb_0_axi_bnd_n: 1,    //  28
    reg_soft_rst_p_imvdsb_1_axi_bnd_n: 1,    //  29
    reg_soft_rst_p_imvdsb_2_axi_bnd_n: 1,    //  30
    reg_soft_rst_p_imvdsb_3_axi_bnd_n: 1;    //  31
}SCRG_CTRL_LBUS_CRG_LBUS3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_0010    crg_lbus4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_imvdsb_4_axi_bnd_n: 1,    //  0
    reg_soft_rst_p_imvdsb_5_axi_bnd_n: 1,    //  1
    reg_soft_rst_p_lb2sb_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_p_lbus_0_axi_bnd_n: 1,    //  3
    reg_soft_rst_p_lbus_10_axi_bnd_n: 1,    //  4
    reg_soft_rst_p_lbus_11_axi_bnd_n: 1,    //  5
    reg_soft_rst_p_lbus_1_axi_bnd_n: 1,    //  6
    reg_soft_rst_p_lbus_2_axi_bnd_n: 1,    //  7
    reg_soft_rst_p_lbus_3_axi_bnd_n: 1,    //  8
    reg_soft_rst_p_lbus_4_axi_bnd_n: 1,    //  9
    reg_soft_rst_p_lbus_5_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_lbus_6_axi_bnd_n: 1,    //  11
    reg_soft_rst_p_lbus_7_axi_bnd_n: 1,    //  12
    reg_soft_rst_p_lbus_8_axi_bnd_n: 1,    //  13
    reg_soft_rst_p_lbus_9_axi_bnd_n: 1,    //  14
    reg_soft_rst_p_lnx0_0_axi_bnd_n: 1,    //  15
    reg_soft_rst_p_lnx1_0_axi_bnd_n: 1,    //  16
    reg_soft_rst_p_lnx2_0_axi_bnd_n: 1,    //  17
    reg_soft_rst_p_mefmssb_0_axi_bnd_n: 1,    //  18
    reg_soft_rst_p_nd0_0_axi_bnd_n: 1,    //  19
    reg_soft_rst_p_nd1_0_axi_bnd_n: 1,    //  20
    reg_soft_rst_p_tcon_0_axi_bnd_n: 1,    //  21
    reg_soft_rst_p_vd0_0_axi_bnd_n: 1,    //  22
    reg_soft_rst_p_vd0_1_axi_bnd_n: 1,    //  23
    reg_soft_rst_p_vd1_0_axi_bnd_n: 1,    //  24
    reg_soft_rst_p_vd1_1_axi_bnd_n: 1,    //  25
    reg_soft_rst_p_vd2_1_axi_bnd_n: 1,    //  26
    reg_soft_rst_p_vd2vmsb_0_axi_bnd_n: 1,    //  27
    reg_soft_rst_x_aud_0_axi_n:  1,    //     28
    reg_soft_rst_x_cco_0_axi_n:  1,    //     29
    reg_soft_rst_x_cco_1_axi_n:  1,    //     30
    reg_soft_rst_x_conv_rx_tcon_0_axi_n: 1;    //  31
}SCRG_CTRL_LBUS_CRG_LBUS4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_0014    crg_lbus5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_x_conv_rx_vd0_0_axi_n: 1,    //  0
    reg_soft_rst_x_conv_rx_vd0_1_axi_n: 1,    //  1
    reg_soft_rst_x_conv_rx_vd1_0_axi_n: 1,    //  2
    reg_soft_rst_x_conv_rx_vd1_1_axi_n: 1,    //  3
    reg_soft_rst_x_conv_rx_vd2_1_axi_n: 1,    //  4
    reg_soft_rst_x_conv_rx_vd2vmsb_0_axi_n: 1,    //  5
    reg_soft_rst_x_conv_tx_tcon_0_axi_n: 1,    //  6
    reg_soft_rst_x_conv_tx_vd0_0_axi_n: 1,    //  7
    reg_soft_rst_x_conv_tx_vd0_1_axi_n: 1,    //  8
    reg_soft_rst_x_conv_tx_vd1_0_axi_n: 1,    //  9
    reg_soft_rst_x_conv_tx_vd1_1_axi_n: 1,    //  10
    reg_soft_rst_x_conv_tx_vd2_1_axi_n: 1,    //  11
    reg_soft_rst_x_conv_tx_vd2vmsb_0_axi_n: 1,    //  12
    reg_soft_rst_x_fmgsesb_0_axi_n: 1,    //  13
    reg_soft_rst_x_fmgsesb_1_axi_n: 1,    //  14
    reg_soft_rst_x_fmgsesb_2_axi_n: 1,    //  15
    reg_soft_rst_x_fmgsesb_3_axi_n: 1,    //  16
    reg_soft_rst_x_fmgsesb_4_axi_n: 1,    //  17
    reg_soft_rst_x_gfx_0_axi_n:  1,    //     18
    reg_soft_rst_x_gpu_0_axi_n:  1,    //     19
    reg_soft_rst_x_gpu_1_axi_n:  1,    //     20
    reg_soft_rst_x_icvesb_0_axi_n: 1,    //   21
    reg_soft_rst_x_imvdsb_0_axi_n: 1,    //   22
    reg_soft_rst_x_imvdsb_1_axi_n: 1,    //   23
    reg_soft_rst_x_imvdsb_2_axi_n: 1,    //   24
    reg_soft_rst_x_imvdsb_3_axi_n: 1,    //   25
    reg_soft_rst_x_imvdsb_4_axi_n: 1,    //   26
    reg_soft_rst_x_imvdsb_5_axi_n: 1,    //   27
    reg_soft_rst_x_lb2sb_0_axi_n: 1,    //    28
    reg_soft_rst_x_lbus_0_axi_bnd_n: 1,    //  29
    reg_soft_rst_x_lbus_0_axi_n: 1,    //     30
    reg_soft_rst_x_lbus_10_axi_bnd_n: 1;    //  31
}SCRG_CTRL_LBUS_CRG_LBUS5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_0018    crg_lbus6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_x_lbus_10_axi_n: 1,    //     0
    reg_soft_rst_x_lbus_11_axi_bnd_n: 1,    //  1
    reg_soft_rst_x_lbus_11_axi_n: 1,    //     2
    reg_soft_rst_x_lbus_1_axi_bnd_n: 1,    //  3
    reg_soft_rst_x_lbus_1_axi_n: 1,    //      4
    reg_soft_rst_x_lbus_2_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_lbus_2_axi_n: 1,    //      6
    reg_soft_rst_x_lbus_3_axi_bnd_n: 1,    //  7
    reg_soft_rst_x_lbus_3_axi_n: 1,    //      8
    reg_soft_rst_x_lbus_4_axi_bnd_n: 1,    //  9
    reg_soft_rst_x_lbus_4_axi_n: 1,    //     10
    reg_soft_rst_x_lbus_5_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_lbus_5_axi_n: 1,    //     12
    reg_soft_rst_x_lbus_6_axi_bnd_n: 1,    //  13
    reg_soft_rst_x_lbus_6_axi_n: 1,    //     14
    reg_soft_rst_x_lbus_7_axi_bnd_n: 1,    //  15
    reg_soft_rst_x_lbus_7_axi_n: 1,    //     16
    reg_soft_rst_x_lbus_8_axi_bnd_n: 1,    //  17
    reg_soft_rst_x_lbus_8_axi_n: 1,    //     18
    reg_soft_rst_x_lbus_9_axi_bnd_n: 1,    //  19
    reg_soft_rst_x_lbus_9_axi_n: 1,    //     20
    reg_soft_rst_x_lnx0_0_axi_n: 1,    //     21
    reg_soft_rst_x_lnx1_0_axi_n: 1,    //     22
    reg_soft_rst_x_lnx2_0_axi_n: 1,    //     23
    reg_soft_rst_x_mefmssb_0_axi_n: 1,    //  24
    reg_soft_rst_x_nd0_0_axi_n:  1,    //     25
    reg_soft_rst_x_nd1_0_axi_n:  1,    //     26
    reg_soft_rst_x_tcon_0_axi_n: 1,    //     27
    reg_soft_rst_x_vd0_0_axi_n:  1,    //     28
    reg_soft_rst_x_vd0_1_axi_n:  1,    //     29
    reg_soft_rst_x_vd1_0_axi_n:  1,    //     30
    reg_soft_rst_x_vd1_1_axi_n:  1;    //     31
}SCRG_CTRL_LBUS_CRG_LBUS6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_001C    crg_lbus7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_x_vd2_1_axi_n:  1,    //      0
    reg_soft_rst_x_vd2vmsb_0_axi_n: 1,    //   1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_LBUS_CRG_LBUS7_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lbus Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LBUS_CRG_LBUS0_O24A0_T    crg_lbus0 ;             // 0xC410_0000
    SCRG_CTRL_LBUS_CRG_LBUS1_O24A0_T    crg_lbus1 ;             // 0xC410_0004
    SCRG_CTRL_LBUS_CRG_LBUS2_O24A0_T    crg_lbus2 ;             // 0xC410_0008
    SCRG_CTRL_LBUS_CRG_LBUS3_O24A0_T    crg_lbus3 ;             // 0xC410_000C
    SCRG_CTRL_LBUS_CRG_LBUS4_O24A0_T    crg_lbus4 ;             // 0xC410_0010
    SCRG_CTRL_LBUS_CRG_LBUS5_O24A0_T    crg_lbus5 ;             // 0xC410_0014
    SCRG_CTRL_LBUS_CRG_LBUS6_O24A0_T    crg_lbus6 ;             // 0xC410_0018
    SCRG_CTRL_LBUS_CRG_LBUS7_O24A0_T    crg_lbus7 ;             // 0xC410_001C
}SCRG_CTRL_LBUS_REG_O24A0_T;
/* 8 regs */

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

#define SCRG_CTRL_LBUS_CRG_LBUS0_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_LBUS_CRG_LBUS1_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_LBUS_CRG_LBUS2_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_LBUS_CRG_LBUS3_O24A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_LBUS_CRG_LBUS4_O24A0_T_OFF                (BASEADDRESS+0x0010)
#define SCRG_CTRL_LBUS_CRG_LBUS5_O24A0_T_OFF                (BASEADDRESS+0x0014)
#define SCRG_CTRL_LBUS_CRG_LBUS6_O24A0_T_OFF                (BASEADDRESS+0x0018)
#define SCRG_CTRL_LBUS_CRG_LBUS7_O24A0_T_OFF                (BASEADDRESS+0x001C)

/*-----------------------------------------------------------------------------------------
    0xC410_0000    crg_lbus0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_LBUS_CRG_LBUS0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_0004    crg_lbus1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_LBUS_CRG_LBUS1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_0008    crg_lbus2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_axi_884_clk_gate_en: 1;    //   1
    UINT32 reg_main_clk_gate_en: 1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_LBUS_CRG_LBUS2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_000C    crg_lbus3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_main_n:  1;    //      1
    UINT32 reg_soft_rst_p_aud_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_cco_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_cco_1_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_conv_rx_tcon_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_conv_rx_vd0_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_conv_rx_vd0_1_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_conv_rx_vd1_0_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_conv_rx_vd1_1_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_conv_rx_vd2_1_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_conv_rx_vd2vmsb_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_p_conv_tx_tcon_0_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_p_conv_tx_vd0_0_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_p_conv_tx_vd0_1_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_p_conv_tx_vd1_0_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_p_conv_tx_vd1_1_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_p_conv_tx_vd2_1_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_p_conv_tx_vd2vmsb_0_axi_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_p_fmgsesb_0_axi_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_p_fmgsesb_1_axi_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_p_fmgsesb_2_axi_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_p_fmgsesb_3_axi_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_p_fmgsesb_4_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_p_gfx_0_axi_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_p_gpu_0_axi_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_p_gpu_1_axi_bnd_n: 1;    //  26
    UINT32 reg_soft_rst_p_icvesb_0_axi_bnd_n: 1;    //  27
    UINT32 reg_soft_rst_p_imvdsb_0_axi_bnd_n: 1;    //  28
    UINT32 reg_soft_rst_p_imvdsb_1_axi_bnd_n: 1;    //  29
    UINT32 reg_soft_rst_p_imvdsb_2_axi_bnd_n: 1;    //  30
    UINT32 reg_soft_rst_p_imvdsb_3_axi_bnd_n: 1;    //  31
    };
}SCRG_CTRL_LBUS_CRG_LBUS3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_0010    crg_lbus4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_imvdsb_4_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_p_imvdsb_5_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_lb2sb_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_lbus_0_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_lbus_10_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_lbus_11_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_lbus_1_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_lbus_2_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_lbus_3_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_lbus_4_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_lbus_5_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_lbus_6_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_p_lbus_7_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_p_lbus_8_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_p_lbus_9_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_p_lnx0_0_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_p_lnx1_0_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_p_lnx2_0_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_p_mefmssb_0_axi_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_p_nd0_0_axi_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_p_nd1_0_axi_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_p_tcon_0_axi_bnd_n: 1;    //  21
    UINT32 reg_soft_rst_p_vd0_0_axi_bnd_n: 1;    //  22
    UINT32 reg_soft_rst_p_vd0_1_axi_bnd_n: 1;    //  23
    UINT32 reg_soft_rst_p_vd1_0_axi_bnd_n: 1;    //  24
    UINT32 reg_soft_rst_p_vd1_1_axi_bnd_n: 1;    //  25
    UINT32 reg_soft_rst_p_vd2_1_axi_bnd_n: 1;    //  26
    UINT32 reg_soft_rst_p_vd2vmsb_0_axi_bnd_n: 1;    //  27
    UINT32 reg_soft_rst_x_aud_0_axi_n: 1;    //  28
    UINT32 reg_soft_rst_x_cco_0_axi_n: 1;    //  29
    UINT32 reg_soft_rst_x_cco_1_axi_n: 1;    //  30
    UINT32 reg_soft_rst_x_conv_rx_tcon_0_axi_n: 1;    //  31
    };
}SCRG_CTRL_LBUS_CRG_LBUS4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_0014    crg_lbus5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_x_conv_rx_vd0_0_axi_n: 1;    //  0
    UINT32 reg_soft_rst_x_conv_rx_vd0_1_axi_n: 1;    //  1
    UINT32 reg_soft_rst_x_conv_rx_vd1_0_axi_n: 1;    //  2
    UINT32 reg_soft_rst_x_conv_rx_vd1_1_axi_n: 1;    //  3
    UINT32 reg_soft_rst_x_conv_rx_vd2_1_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_conv_rx_vd2vmsb_0_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_conv_tx_tcon_0_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_conv_tx_vd0_0_axi_n: 1;    //  7
    UINT32 reg_soft_rst_x_conv_tx_vd0_1_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_conv_tx_vd1_0_axi_n: 1;    //  9
    UINT32 reg_soft_rst_x_conv_tx_vd1_1_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_conv_tx_vd2_1_axi_n: 1;    //  11
    UINT32 reg_soft_rst_x_conv_tx_vd2vmsb_0_axi_n: 1;    //  12
    UINT32 reg_soft_rst_x_fmgsesb_0_axi_n: 1;    //  13
    UINT32 reg_soft_rst_x_fmgsesb_1_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_fmgsesb_2_axi_n: 1;    //  15
    UINT32 reg_soft_rst_x_fmgsesb_3_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_fmgsesb_4_axi_n: 1;    //  17
    UINT32 reg_soft_rst_x_gfx_0_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_gpu_0_axi_n: 1;    //  19
    UINT32 reg_soft_rst_x_gpu_1_axi_n: 1;    //  20
    UINT32 reg_soft_rst_x_icvesb_0_axi_n: 1;    //  21
    UINT32 reg_soft_rst_x_imvdsb_0_axi_n: 1;    //  22
    UINT32 reg_soft_rst_x_imvdsb_1_axi_n: 1;    //  23
    UINT32 reg_soft_rst_x_imvdsb_2_axi_n: 1;    //  24
    UINT32 reg_soft_rst_x_imvdsb_3_axi_n: 1;    //  25
    UINT32 reg_soft_rst_x_imvdsb_4_axi_n: 1;    //  26
    UINT32 reg_soft_rst_x_imvdsb_5_axi_n: 1;    //  27
    UINT32 reg_soft_rst_x_lb2sb_0_axi_n: 1;    //  28
    UINT32 reg_soft_rst_x_lbus_0_axi_bnd_n: 1;    //  29
    UINT32 reg_soft_rst_x_lbus_0_axi_n: 1;    //  30
    UINT32 reg_soft_rst_x_lbus_10_axi_bnd_n: 1;    //  31
    };
}SCRG_CTRL_LBUS_CRG_LBUS5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_0018    crg_lbus6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_x_lbus_10_axi_n: 1;    //  0
    UINT32 reg_soft_rst_x_lbus_11_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_x_lbus_11_axi_n: 1;    //  2
    UINT32 reg_soft_rst_x_lbus_1_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_x_lbus_1_axi_n: 1;    //  4
    UINT32 reg_soft_rst_x_lbus_2_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_lbus_2_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_lbus_3_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_lbus_3_axi_n: 1;    //  8
    UINT32 reg_soft_rst_x_lbus_4_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_lbus_4_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_lbus_5_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_lbus_5_axi_n: 1;    //  12
    UINT32 reg_soft_rst_x_lbus_6_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_x_lbus_6_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_lbus_7_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_x_lbus_7_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_lbus_8_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_x_lbus_8_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_lbus_9_axi_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_x_lbus_9_axi_n: 1;    //  20
    UINT32 reg_soft_rst_x_lnx0_0_axi_n: 1;    //  21
    UINT32 reg_soft_rst_x_lnx1_0_axi_n: 1;    //  22
    UINT32 reg_soft_rst_x_lnx2_0_axi_n: 1;    //  23
    UINT32 reg_soft_rst_x_mefmssb_0_axi_n: 1;    //  24
    UINT32 reg_soft_rst_x_nd0_0_axi_n: 1;    //  25
    UINT32 reg_soft_rst_x_nd1_0_axi_n: 1;    //  26
    UINT32 reg_soft_rst_x_tcon_0_axi_n: 1;    //  27
    UINT32 reg_soft_rst_x_vd0_0_axi_n: 1;    //  28
    UINT32 reg_soft_rst_x_vd0_1_axi_n: 1;    //  29
    UINT32 reg_soft_rst_x_vd1_0_axi_n: 1;    //  30
    UINT32 reg_soft_rst_x_vd1_1_axi_n: 1;    //  31
    };
}SCRG_CTRL_LBUS_CRG_LBUS6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC410_001C    crg_lbus7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_x_vd2_1_axi_n: 1;    //  0
    UINT32 reg_soft_rst_x_vd2vmsb_0_axi_n: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_LBUS_CRG_LBUS7_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_lbus Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_LBUS_CRG_LBUS0_O24A0_T    crg_lbus0 ;             // 0xC410_0000
    SCRG_CTRL_LBUS_CRG_LBUS1_O24A0_T    crg_lbus1 ;             // 0xC410_0004
    SCRG_CTRL_LBUS_CRG_LBUS2_O24A0_T    crg_lbus2 ;             // 0xC410_0008
    SCRG_CTRL_LBUS_CRG_LBUS3_O24A0_T    crg_lbus3 ;             // 0xC410_000C
    SCRG_CTRL_LBUS_CRG_LBUS4_O24A0_T    crg_lbus4 ;             // 0xC410_0010
    SCRG_CTRL_LBUS_CRG_LBUS5_O24A0_T    crg_lbus5 ;             // 0xC410_0014
    SCRG_CTRL_LBUS_CRG_LBUS6_O24A0_T    crg_lbus6 ;             // 0xC410_0018
    SCRG_CTRL_LBUS_CRG_LBUS7_O24A0_T    crg_lbus7 ;             // 0xC410_001C
}SCRG_CTRL_LBUS_REG_O24A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_LBUS_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

