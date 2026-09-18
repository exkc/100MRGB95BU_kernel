#ifndef _FUNC_IOMUX_ME1_REG_H_
#define _FUNC_IOMUX_ME1_REG_H_

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
    0xCC33_2000    pad_me100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_rx_clk__ds0 :  1,    //      0
    reg_pad_rgmii_rx_clk__ds1 :  1,    //      1
    reg_pad_rgmii_rx_clk__ds2 :  1,    //      2
    reg_pad_rgmii_rx_clk__ds3 :  1,    //      3
    reg_pad_rgmii_rx_clk__pd  :  1,    //      4
    reg_pad_rgmii_rx_clk__pu  :  1,    //      5
    reg_pad_rgmii_rx_clk__st  :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_rgmii_ref_clk__ds0:  1,    //      8
    reg_pad_rgmii_ref_clk__ds1:  1,    //      9
    reg_pad_rgmii_ref_clk__ds2:  1,    //     10
    reg_pad_rgmii_ref_clk__ds3:  1,    //     11
    reg_pad_rgmii_ref_clk__pd :  1,    //     12
    reg_pad_rgmii_ref_clk__pu :  1,    //     13
    reg_pad_rgmii_ref_clk__st :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_rgmii_mdio__ds0   :  1,    //     16
    reg_pad_rgmii_mdio__ds1   :  1,    //     17
    reg_pad_rgmii_mdio__ds2   :  1,    //     18
    reg_pad_rgmii_mdio__ds3   :  1,    //     19
    reg_pad_rgmii_mdio__pd    :  1,    //     20
    reg_pad_rgmii_mdio__pu    :  1,    //     21
    reg_pad_rgmii_mdio__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_rgmii_mdc__ds0    :  1,    //     24
    reg_pad_rgmii_mdc__ds1    :  1,    //     25
    reg_pad_rgmii_mdc__ds2    :  1,    //     26
    reg_pad_rgmii_mdc__ds3    :  1,    //     27
    reg_pad_rgmii_mdc__pd     :  1,    //     28
    reg_pad_rgmii_mdc__pu     :  1,    //     29
    reg_pad_rgmii_mdc__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ME1_PAD_ME100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC33_2004    pad_me101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_rxd_2__ds0  :  1,    //      0
    reg_pad_rgmii_rxd_2__ds1  :  1,    //      1
    reg_pad_rgmii_rxd_2__ds2  :  1,    //      2
    reg_pad_rgmii_rxd_2__ds3  :  1,    //      3
    reg_pad_rgmii_rxd_2__pd   :  1,    //      4
    reg_pad_rgmii_rxd_2__pu   :  1,    //      5
    reg_pad_rgmii_rxd_2__st   :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_rgmii_rxd_1__ds0  :  1,    //      8
    reg_pad_rgmii_rxd_1__ds1  :  1,    //      9
    reg_pad_rgmii_rxd_1__ds2  :  1,    //     10
    reg_pad_rgmii_rxd_1__ds3  :  1,    //     11
    reg_pad_rgmii_rxd_1__pd   :  1,    //     12
    reg_pad_rgmii_rxd_1__pu   :  1,    //     13
    reg_pad_rgmii_rxd_1__st   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_rgmii_rxd_0__ds0  :  1,    //     16
    reg_pad_rgmii_rxd_0__ds1  :  1,    //     17
    reg_pad_rgmii_rxd_0__ds2  :  1,    //     18
    reg_pad_rgmii_rxd_0__ds3  :  1,    //     19
    reg_pad_rgmii_rxd_0__pd   :  1,    //     20
    reg_pad_rgmii_rxd_0__pu   :  1,    //     21
    reg_pad_rgmii_rxd_0__st   :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_rgmii_rx_ctl__ds0 :  1,    //     24
    reg_pad_rgmii_rx_ctl__ds1 :  1,    //     25
    reg_pad_rgmii_rx_ctl__ds2 :  1,    //     26
    reg_pad_rgmii_rx_ctl__ds3 :  1,    //     27
    reg_pad_rgmii_rx_ctl__pd  :  1,    //     28
    reg_pad_rgmii_rx_ctl__pu  :  1,    //     29
    reg_pad_rgmii_rx_ctl__st  :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ME1_PAD_ME101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC33_2008    pad_me102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_txd_0__ds0  :  1,    //      0
    reg_pad_rgmii_txd_0__ds1  :  1,    //      1
    reg_pad_rgmii_txd_0__ds2  :  1,    //      2
    reg_pad_rgmii_txd_0__ds3  :  1,    //      3
    reg_pad_rgmii_txd_0__pd   :  1,    //      4
    reg_pad_rgmii_txd_0__pu   :  1,    //      5
    reg_pad_rgmii_txd_0__st   :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_rgmii_tx_ctl__ds0 :  1,    //      8
    reg_pad_rgmii_tx_ctl__ds1 :  1,    //      9
    reg_pad_rgmii_tx_ctl__ds2 :  1,    //     10
    reg_pad_rgmii_tx_ctl__ds3 :  1,    //     11
    reg_pad_rgmii_tx_ctl__pd  :  1,    //     12
    reg_pad_rgmii_tx_ctl__pu  :  1,    //     13
    reg_pad_rgmii_tx_ctl__st  :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_rgmii_tx_clk__ds0 :  1,    //     16
    reg_pad_rgmii_tx_clk__ds1 :  1,    //     17
    reg_pad_rgmii_tx_clk__ds2 :  1,    //     18
    reg_pad_rgmii_tx_clk__ds3 :  1,    //     19
    reg_pad_rgmii_tx_clk__pd  :  1,    //     20
    reg_pad_rgmii_tx_clk__pu  :  1,    //     21
    reg_pad_rgmii_tx_clk__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_rgmii_rxd_3__ds0  :  1,    //     24
    reg_pad_rgmii_rxd_3__ds1  :  1,    //     25
    reg_pad_rgmii_rxd_3__ds2  :  1,    //     26
    reg_pad_rgmii_rxd_3__ds3  :  1,    //     27
    reg_pad_rgmii_rxd_3__pd   :  1,    //     28
    reg_pad_rgmii_rxd_3__pu   :  1,    //     29
    reg_pad_rgmii_rxd_3__st   :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_ME1_PAD_ME102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC33_200C    pad_me103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_txd_3__ds0  :  1,    //      0
    reg_pad_rgmii_txd_3__ds1  :  1,    //      1
    reg_pad_rgmii_txd_3__ds2  :  1,    //      2
    reg_pad_rgmii_txd_3__ds3  :  1,    //      3
    reg_pad_rgmii_txd_3__pd   :  1,    //      4
    reg_pad_rgmii_txd_3__pu   :  1,    //      5
    reg_pad_rgmii_txd_3__st   :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_rgmii_txd_2__ds0  :  1,    //      8
    reg_pad_rgmii_txd_2__ds1  :  1,    //      9
    reg_pad_rgmii_txd_2__ds2  :  1,    //     10
    reg_pad_rgmii_txd_2__ds3  :  1,    //     11
    reg_pad_rgmii_txd_2__pd   :  1,    //     12
    reg_pad_rgmii_txd_2__pu   :  1,    //     13
    reg_pad_rgmii_txd_2__st   :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_rgmii_txd_1__ds0  :  1,    //     16
    reg_pad_rgmii_txd_1__ds1  :  1,    //     17
    reg_pad_rgmii_txd_1__ds2  :  1,    //     18
    reg_pad_rgmii_txd_1__ds3  :  1,    //     19
    reg_pad_rgmii_txd_1__pd   :  1,    //     20
    reg_pad_rgmii_txd_1__pu   :  1,    //     21
    reg_pad_rgmii_txd_1__st   :  1,    //     22
                              :  9;    //  31:23 reserved
}FUNC_IOMUX_ME1_PAD_ME103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC33_2100    pad_me164 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_rxd_2_mux_sel: 4,    //   3: 0
    reg_pad_rgmii_rxd_1_mux_sel: 4,    //   7: 4
    reg_pad_rgmii_rxd_0_mux_sel: 4,    //  11: 8
    reg_pad_rgmii_rx_ctl_mux_sel: 4,    //  15:12
    reg_pad_rgmii_rx_clk_mux_sel: 4,    //  19:16
    reg_pad_rgmii_ref_clk_mux_sel: 4,    //  23:20
    reg_pad_rgmii_mdio_mux_sel:  4,    //  27:24
    reg_pad_rgmii_mdc_mux_sel :  4;    //  31:28
}FUNC_IOMUX_ME1_PAD_ME164_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC33_2104    pad_me165 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_rgmii_txd_3_mux_sel: 4,    //   3: 0
    reg_pad_rgmii_txd_2_mux_sel: 4,    //   7: 4
    reg_pad_rgmii_txd_1_mux_sel: 4,    //  11: 8
    reg_pad_rgmii_txd_0_mux_sel: 4,    //  15:12
    reg_pad_rgmii_tx_ctl_mux_sel: 4,    //  19:16
    reg_pad_rgmii_tx_clk_mux_sel: 4,    //  23:20
    reg_pad_rgmii_rxd_3_mux_sel: 4,    //  27:24
                              :  4;    //  31:28 reserved
}FUNC_IOMUX_ME1_PAD_ME165_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_ME1_PAD_ME100_O22A0_T          pad_me100  ;             // 0xCC33_2000
    FUNC_IOMUX_ME1_PAD_ME101_O22A0_T          pad_me101  ;             // 0xCC33_2004
    FUNC_IOMUX_ME1_PAD_ME102_O22A0_T          pad_me102  ;             // 0xCC33_2008
    FUNC_IOMUX_ME1_PAD_ME103_O22A0_T          pad_me103  ;             // 0xCC33_200C
    UINT32                             _rsvd_00[60];            // 0xCC33_2010 ~ 0xCC33_20FC
    FUNC_IOMUX_ME1_PAD_ME164_O22A0_T          pad_me164  ;             // 0xCC33_2100
    FUNC_IOMUX_ME1_PAD_ME165_O22A0_T          pad_me165  ;             // 0xCC33_2104
}FUNC_IOMUX_ME1_REG_O22A0_T;
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

#define FUNC_IOMUX_ME1_PAD_ME100_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define FUNC_IOMUX_ME1_PAD_ME101_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define FUNC_IOMUX_ME1_PAD_ME102_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define FUNC_IOMUX_ME1_PAD_ME103_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define FUNC_IOMUX_ME1_PAD_ME164_O22A0_T_OFF                       (BASEADDRESS+0x0100)
#define FUNC_IOMUX_ME1_PAD_ME165_O22A0_T_OFF                       (BASEADDRESS+0x0104)

/*-----------------------------------------------------------------------------------------
    0xCC33_2000    pad_me100 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_rgmii_rx_clk__ds0: 1;    //  0
    UINT32 reg_pad_rgmii_rx_clk__ds1: 1;    //  1
    UINT32 reg_pad_rgmii_rx_clk__ds2: 1;    //  2
    UINT32 reg_pad_rgmii_rx_clk__ds3: 1;    //  3
    UINT32 reg_pad_rgmii_rx_clk__pd: 1;    //  4
    UINT32 reg_pad_rgmii_rx_clk__pu: 1;    //  5
    UINT32 reg_pad_rgmii_rx_clk__st: 1;    //  6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_rgmii_ref_clk__ds0: 1;    //  8
    UINT32 reg_pad_rgmii_ref_clk__ds1: 1;    //  9
    UINT32 reg_pad_rgmii_ref_clk__ds2: 1;    //  10
    UINT32 reg_pad_rgmii_ref_clk__ds3: 1;    //  11
    UINT32 reg_pad_rgmii_ref_clk__pd: 1;    //  12
    UINT32 reg_pad_rgmii_ref_clk__pu: 1;    //  13
    UINT32 reg_pad_rgmii_ref_clk__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_rgmii_mdio__ds0: 1;    //  16
    UINT32 reg_pad_rgmii_mdio__ds1: 1;    //  17
    UINT32 reg_pad_rgmii_mdio__ds2: 1;    //  18
    UINT32 reg_pad_rgmii_mdio__ds3: 1;    //  19
    UINT32 reg_pad_rgmii_mdio__pd: 1;    //   20
    UINT32 reg_pad_rgmii_mdio__pu: 1;    //   21
    UINT32 reg_pad_rgmii_mdio__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_rgmii_mdc__ds0: 1;    //   24
    UINT32 reg_pad_rgmii_mdc__ds1: 1;    //   25
    UINT32 reg_pad_rgmii_mdc__ds2: 1;    //   26
    UINT32 reg_pad_rgmii_mdc__ds3: 1;    //   27
    UINT32 reg_pad_rgmii_mdc__pd: 1;    //    28
    UINT32 reg_pad_rgmii_mdc__pu: 1;    //    29
    UINT32 reg_pad_rgmii_mdc__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ME1_PAD_ME100_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC33_2004    pad_me101 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_rgmii_rxd_2__ds0: 1;    //  0
    UINT32 reg_pad_rgmii_rxd_2__ds1: 1;    //  1
    UINT32 reg_pad_rgmii_rxd_2__ds2: 1;    //  2
    UINT32 reg_pad_rgmii_rxd_2__ds3: 1;    //  3
    UINT32 reg_pad_rgmii_rxd_2__pd: 1;    //   4
    UINT32 reg_pad_rgmii_rxd_2__pu: 1;    //   5
    UINT32 reg_pad_rgmii_rxd_2__st: 1;    //   6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_rgmii_rxd_1__ds0: 1;    //  8
    UINT32 reg_pad_rgmii_rxd_1__ds1: 1;    //  9
    UINT32 reg_pad_rgmii_rxd_1__ds2: 1;    //  10
    UINT32 reg_pad_rgmii_rxd_1__ds3: 1;    //  11
    UINT32 reg_pad_rgmii_rxd_1__pd: 1;    //  12
    UINT32 reg_pad_rgmii_rxd_1__pu: 1;    //  13
    UINT32 reg_pad_rgmii_rxd_1__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_rgmii_rxd_0__ds0: 1;    //  16
    UINT32 reg_pad_rgmii_rxd_0__ds1: 1;    //  17
    UINT32 reg_pad_rgmii_rxd_0__ds2: 1;    //  18
    UINT32 reg_pad_rgmii_rxd_0__ds3: 1;    //  19
    UINT32 reg_pad_rgmii_rxd_0__pd: 1;    //  20
    UINT32 reg_pad_rgmii_rxd_0__pu: 1;    //  21
    UINT32 reg_pad_rgmii_rxd_0__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_rgmii_rx_ctl__ds0: 1;    //  24
    UINT32 reg_pad_rgmii_rx_ctl__ds1: 1;    //  25
    UINT32 reg_pad_rgmii_rx_ctl__ds2: 1;    //  26
    UINT32 reg_pad_rgmii_rx_ctl__ds3: 1;    //  27
    UINT32 reg_pad_rgmii_rx_ctl__pd: 1;    //  28
    UINT32 reg_pad_rgmii_rx_ctl__pu: 1;    //  29
    UINT32 reg_pad_rgmii_rx_ctl__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ME1_PAD_ME101_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC33_2008    pad_me102 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_rgmii_txd_0__ds0: 1;    //  0
    UINT32 reg_pad_rgmii_txd_0__ds1: 1;    //  1
    UINT32 reg_pad_rgmii_txd_0__ds2: 1;    //  2
    UINT32 reg_pad_rgmii_txd_0__ds3: 1;    //  3
    UINT32 reg_pad_rgmii_txd_0__pd: 1;    //   4
    UINT32 reg_pad_rgmii_txd_0__pu: 1;    //   5
    UINT32 reg_pad_rgmii_txd_0__st: 1;    //   6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_rgmii_tx_ctl__ds0: 1;    //  8
    UINT32 reg_pad_rgmii_tx_ctl__ds1: 1;    //  9
    UINT32 reg_pad_rgmii_tx_ctl__ds2: 1;    //  10
    UINT32 reg_pad_rgmii_tx_ctl__ds3: 1;    //  11
    UINT32 reg_pad_rgmii_tx_ctl__pd: 1;    //  12
    UINT32 reg_pad_rgmii_tx_ctl__pu: 1;    //  13
    UINT32 reg_pad_rgmii_tx_ctl__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_rgmii_tx_clk__ds0: 1;    //  16
    UINT32 reg_pad_rgmii_tx_clk__ds1: 1;    //  17
    UINT32 reg_pad_rgmii_tx_clk__ds2: 1;    //  18
    UINT32 reg_pad_rgmii_tx_clk__ds3: 1;    //  19
    UINT32 reg_pad_rgmii_tx_clk__pd: 1;    //  20
    UINT32 reg_pad_rgmii_tx_clk__pu: 1;    //  21
    UINT32 reg_pad_rgmii_tx_clk__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_rgmii_rxd_3__ds0: 1;    //  24
    UINT32 reg_pad_rgmii_rxd_3__ds1: 1;    //  25
    UINT32 reg_pad_rgmii_rxd_3__ds2: 1;    //  26
    UINT32 reg_pad_rgmii_rxd_3__ds3: 1;    //  27
    UINT32 reg_pad_rgmii_rxd_3__pd: 1;    //  28
    UINT32 reg_pad_rgmii_rxd_3__pu: 1;    //  29
    UINT32 reg_pad_rgmii_rxd_3__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_ME1_PAD_ME102_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC33_200C    pad_me103 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_rgmii_txd_3__ds0: 1;    //  0
    UINT32 reg_pad_rgmii_txd_3__ds1: 1;    //  1
    UINT32 reg_pad_rgmii_txd_3__ds2: 1;    //  2
    UINT32 reg_pad_rgmii_txd_3__ds3: 1;    //  3
    UINT32 reg_pad_rgmii_txd_3__pd: 1;    //   4
    UINT32 reg_pad_rgmii_txd_3__pu: 1;    //   5
    UINT32 reg_pad_rgmii_txd_3__st: 1;    //   6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_rgmii_txd_2__ds0: 1;    //  8
    UINT32 reg_pad_rgmii_txd_2__ds1: 1;    //  9
    UINT32 reg_pad_rgmii_txd_2__ds2: 1;    //  10
    UINT32 reg_pad_rgmii_txd_2__ds3: 1;    //  11
    UINT32 reg_pad_rgmii_txd_2__pd: 1;    //  12
    UINT32 reg_pad_rgmii_txd_2__pu: 1;    //  13
    UINT32 reg_pad_rgmii_txd_2__st: 1;    //  14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_rgmii_txd_1__ds0: 1;    //  16
    UINT32 reg_pad_rgmii_txd_1__ds1: 1;    //  17
    UINT32 reg_pad_rgmii_txd_1__ds2: 1;    //  18
    UINT32 reg_pad_rgmii_txd_1__ds3: 1;    //  19
    UINT32 reg_pad_rgmii_txd_1__pd: 1;    //  20
    UINT32 reg_pad_rgmii_txd_1__pu: 1;    //  21
    UINT32 reg_pad_rgmii_txd_1__st: 1;    //  22
    UINT32 resvd02            :  9;    //  31:23 reserved
    };
}FUNC_IOMUX_ME1_PAD_ME103_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC33_2100    pad_me164 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_rgmii_rxd_2_mux_sel: 4;    //  3:0
    UINT32 reg_pad_rgmii_rxd_1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_rgmii_rxd_0_mux_sel: 4;    //  11:8
    UINT32 reg_pad_rgmii_rx_ctl_mux_sel: 4;    //  15:12
    UINT32 reg_pad_rgmii_rx_clk_mux_sel: 4;    //  19:16
    UINT32 reg_pad_rgmii_ref_clk_mux_sel: 4;    //  23:20
    UINT32 reg_pad_rgmii_mdio_mux_sel: 4;    //  27:24
    UINT32 reg_pad_rgmii_mdc_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_ME1_PAD_ME164_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC33_2104    pad_me165 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_rgmii_txd_3_mux_sel: 4;    //  3:0
    UINT32 reg_pad_rgmii_txd_2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_rgmii_txd_1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_rgmii_txd_0_mux_sel: 4;    //  15:12
    UINT32 reg_pad_rgmii_tx_ctl_mux_sel: 4;    //  19:16
    UINT32 reg_pad_rgmii_tx_clk_mux_sel: 4;    //  23:20
    UINT32 reg_pad_rgmii_rxd_3_mux_sel: 4;    //  27:24
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}FUNC_IOMUX_ME1_PAD_ME165_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_me1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_ME1_PAD_ME100_O22A0_T          pad_me100  ;             // 0xCC33_2000
    FUNC_IOMUX_ME1_PAD_ME101_O22A0_T          pad_me101  ;             // 0xCC33_2004
    FUNC_IOMUX_ME1_PAD_ME102_O22A0_T          pad_me102  ;             // 0xCC33_2008
    FUNC_IOMUX_ME1_PAD_ME103_O22A0_T          pad_me103  ;             // 0xCC33_200C
    UINT32                             _rsvd_00[60];            // 0xCC33_2010 ~ 0xCC33_20FC
    FUNC_IOMUX_ME1_PAD_ME164_O22A0_T          pad_me164  ;             // 0xCC33_2100
    FUNC_IOMUX_ME1_PAD_ME165_O22A0_T          pad_me165  ;             // 0xCC33_2104
}FUNC_IOMUX_ME1_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FUNC_IOMUX_ME1_REG_H_

/* from 'O22_CTOP_PAD_Register_Manual.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

