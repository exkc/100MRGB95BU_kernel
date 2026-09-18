#ifndef _IOMUX_CTRL_HDMI_REG_O26A0_H_
#define _IOMUX_CTRL_HDMI_REG_O26A0_H_

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
    0xC877_3000    pad_hdmi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  6,    //   5: 0 reserved
    reg_pad_sc_clk_out__ds0   :  1,    //      6
    reg_pad_sc_clk_out__ds1   :  1,    //      7
    reg_pad_sc_clk_out__ds2   :  1,    //      8
    reg_pad_sc_clk_out__ds3   :  1,    //      9
    reg_pad_sc_clk_out__pd    :  1,    //     10
    reg_pad_sc_clk_out__pu    :  1,    //     11
    reg_pad_sc_clk_out__st    :  1,    //     12
    reg_pad_sc_vccen__ds0     :  1,    //     13
    reg_pad_sc_vccen__ds1     :  1,    //     14
    reg_pad_sc_vccen__ds2     :  1,    //     15
    reg_pad_sc_vccen__ds3     :  1,    //     16
    reg_pad_sc_vccen__pd      :  1,    //     17
    reg_pad_sc_vccen__pu      :  1,    //     18
    reg_pad_sc_vccen__st      :  1,    //     19
    reg_pad_uart1_tx__ds0     :  1,    //     20
    reg_pad_uart1_tx__ds1     :  1,    //     21
    reg_pad_uart1_tx__ds2     :  1,    //     22
    reg_pad_uart1_tx__pd      :  1,    //     23
    reg_pad_uart1_tx__pu      :  1,    //     24
    reg_pad_uart1_tx__smt     :  1,    //     25
    reg_pad_uart1_rx__ds0     :  1,    //     26
    reg_pad_uart1_rx__ds1     :  1,    //     27
    reg_pad_uart1_rx__ds2     :  1,    //     28
    reg_pad_uart1_rx__pd      :  1,    //     29
    reg_pad_uart1_rx__pu      :  1,    //     30
    reg_pad_uart1_rx__smt     :  1;    //     31
}IOMUX_CTRL_HDMI_PAD_HDMI00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_3004    pad_hdmi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_sc_vcc_sel__ds0   :  1,    //      4
    reg_pad_sc_vcc_sel__ds1   :  1,    //      5
    reg_pad_sc_vcc_sel__ds2   :  1,    //      6
    reg_pad_sc_vcc_sel__pd    :  1,    //      7
    reg_pad_sc_vcc_sel__pu    :  1,    //      8
    reg_pad_sc_vcc_sel__smt   :  1,    //      9
    reg_pad_sc_rst__ds0       :  1,    //     10
    reg_pad_sc_rst__ds1       :  1,    //     11
    reg_pad_sc_rst__ds2       :  1,    //     12
    reg_pad_sc_rst__ds3       :  1,    //     13
    reg_pad_sc_rst__pd        :  1,    //     14
    reg_pad_sc_rst__pu        :  1,    //     15
    reg_pad_sc_rst__st        :  1,    //     16
    reg_pad_sc_data__ds0      :  1,    //     17
    reg_pad_sc_data__ds1      :  1,    //     18
    reg_pad_sc_data__ds2      :  1,    //     19
    reg_pad_sc_data__ds3      :  1,    //     20
    reg_pad_sc_data__pd       :  1,    //     21
    reg_pad_sc_data__pu       :  1,    //     22
    reg_pad_sc_data__st       :  1,    //     23
                              :  8;    //  31:24 reserved
}IOMUX_CTRL_HDMI_PAD_HDMI01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_3100    pad_hdmi64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_sc_vcc_sel_mux_sel:  4,    //   3: 0
    reg_pad_sc_rst_mux_sel    :  4,    //   7: 4
    reg_pad_sc_data_mux_sel   :  4,    //  11: 8
    reg_pad_sc_clk_out_mux_sel:  4,    //  15:12
    reg_pad_sc_vccen_mux_sel  :  4,    //  19:16
    reg_pad_uart1_tx_mux_sel  :  4,    //  23:20
    reg_pad_uart1_rx_mux_sel  :  4,    //  27:24
                              :  4;    //  31:28 reserved
}IOMUX_CTRL_HDMI_PAD_HDMI64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_HDMI_PAD_HDMI00_O26A0_T    pad_hdmi00;           // 0xC877_3000
    IOMUX_CTRL_HDMI_PAD_HDMI01_O26A0_T    pad_hdmi01;           // 0xC877_3004
    UINT32                             _rsvd_00[62];            // 0xC877_3008 ~ 0xC877_30FC
    IOMUX_CTRL_HDMI_PAD_HDMI64_O26A0_T    pad_hdmi64;           // 0xC877_3100
}IOMUX_CTRL_HDMI_REG_O26A0_T;
/* 3 regs */

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

#define IOMUX_CTRL_HDMI_PAD_HDMI00_O26A0_T_OFF              (BASEADDRESS+0x0000)
#define IOMUX_CTRL_HDMI_PAD_HDMI01_O26A0_T_OFF              (BASEADDRESS+0x0004)
#define IOMUX_CTRL_HDMI_PAD_HDMI64_O26A0_T_OFF              (BASEADDRESS+0x0100)

/*-----------------------------------------------------------------------------------------
    0xC877_3000    pad_hdmi00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  6;    //   5: 0 reserved
    UINT32 reg_pad_sc_clk_out__ds0: 1;    //   6
    UINT32 reg_pad_sc_clk_out__ds1: 1;    //   7
    UINT32 reg_pad_sc_clk_out__ds2: 1;    //   8
    UINT32 reg_pad_sc_clk_out__ds3: 1;    //   9
    UINT32 reg_pad_sc_clk_out__pd: 1;    //   10
    UINT32 reg_pad_sc_clk_out__pu: 1;    //   11
    UINT32 reg_pad_sc_clk_out__st: 1;    //   12
    UINT32 reg_pad_sc_vccen__ds0: 1;    //    13
    UINT32 reg_pad_sc_vccen__ds1: 1;    //    14
    UINT32 reg_pad_sc_vccen__ds2: 1;    //    15
    UINT32 reg_pad_sc_vccen__ds3: 1;    //    16
    UINT32 reg_pad_sc_vccen__pd: 1;    //     17
    UINT32 reg_pad_sc_vccen__pu: 1;    //     18
    UINT32 reg_pad_sc_vccen__st: 1;    //     19
    UINT32 reg_pad_uart1_tx__ds0: 1;    //    20
    UINT32 reg_pad_uart1_tx__ds1: 1;    //    21
    UINT32 reg_pad_uart1_tx__ds2: 1;    //    22
    UINT32 reg_pad_uart1_tx__pd: 1;    //     23
    UINT32 reg_pad_uart1_tx__pu: 1;    //     24
    UINT32 reg_pad_uart1_tx__smt: 1;    //    25
    UINT32 reg_pad_uart1_rx__ds0: 1;    //    26
    UINT32 reg_pad_uart1_rx__ds1: 1;    //    27
    UINT32 reg_pad_uart1_rx__ds2: 1;    //    28
    UINT32 reg_pad_uart1_rx__pd: 1;    //     29
    UINT32 reg_pad_uart1_rx__pu: 1;    //     30
    UINT32 reg_pad_uart1_rx__smt: 1;    //    31
    };
}IOMUX_CTRL_HDMI_PAD_HDMI00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_3004    pad_hdmi01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_sc_vcc_sel__ds0: 1;    //   4
    UINT32 reg_pad_sc_vcc_sel__ds1: 1;    //   5
    UINT32 reg_pad_sc_vcc_sel__ds2: 1;    //   6
    UINT32 reg_pad_sc_vcc_sel__pd: 1;    //    7
    UINT32 reg_pad_sc_vcc_sel__pu: 1;    //    8
    UINT32 reg_pad_sc_vcc_sel__smt: 1;    //   9
    UINT32 reg_pad_sc_rst__ds0:  1;    //     10
    UINT32 reg_pad_sc_rst__ds1:  1;    //     11
    UINT32 reg_pad_sc_rst__ds2:  1;    //     12
    UINT32 reg_pad_sc_rst__ds3:  1;    //     13
    UINT32 reg_pad_sc_rst__pd :  1;    //     14
    UINT32 reg_pad_sc_rst__pu :  1;    //     15
    UINT32 reg_pad_sc_rst__st :  1;    //     16
    UINT32 reg_pad_sc_data__ds0: 1;    //     17
    UINT32 reg_pad_sc_data__ds1: 1;    //     18
    UINT32 reg_pad_sc_data__ds2: 1;    //     19
    UINT32 reg_pad_sc_data__ds3: 1;    //     20
    UINT32 reg_pad_sc_data__pd:  1;    //     21
    UINT32 reg_pad_sc_data__pu:  1;    //     22
    UINT32 reg_pad_sc_data__st:  1;    //     23
    UINT32 resvd01            :  8;    //  31:24 reserved
    };
}IOMUX_CTRL_HDMI_PAD_HDMI01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_3100    pad_hdmi64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_sc_vcc_sel_mux_sel: 4;    //  3:0
    UINT32 reg_pad_sc_rst_mux_sel: 4;    //  7:4
    UINT32 reg_pad_sc_data_mux_sel: 4;    //  11:8
    UINT32 reg_pad_sc_clk_out_mux_sel: 4;    //  15:12
    UINT32 reg_pad_sc_vccen_mux_sel: 4;    //  19:16
    UINT32 reg_pad_uart1_tx_mux_sel: 4;    //  23:20
    UINT32 reg_pad_uart1_rx_mux_sel: 4;    //  27:24
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}IOMUX_CTRL_HDMI_PAD_HDMI64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_HDMI_PAD_HDMI00_O26A0_T    pad_hdmi00;           // 0xC877_3000
    IOMUX_CTRL_HDMI_PAD_HDMI01_O26A0_T    pad_hdmi01;           // 0xC877_3004
    UINT32                             _rsvd_00[62];            // 0xC877_3008 ~ 0xC877_30FC
    IOMUX_CTRL_HDMI_PAD_HDMI64_O26A0_T    pad_hdmi64;           // 0xC877_3100
}IOMUX_CTRL_HDMI_REG_O26A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IOMUX_CTRL_HDMI_REG_H_

/* from 'O26_CTOP_PAD_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

