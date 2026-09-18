#ifndef _CTOP_CTRL_ATG_O20A0_REG_H_
#define _CTOP_CTRL_ATG_O20A0_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xC930_1400    pad_mux0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pull_up_all       :  1,    //      0
    reg_pad_pull_down_all     :  1,    //      1
    reg_pad_floating_all      :  1,    //      2
                              : 29;    //   31:3 reserved
}CTOP_CTRL_ATG_PAD_MUX0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1404    tmod_mux0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tmod_tsadc            :  1,    //      0
    reg_tmod_saradc           :  1,    //      1
    reg_tmod_pll              :  1,    //      2
    reg_tmod_mipadc           :  1,    //      3
    reg_tmod_iomux            :  1,    //      4
    reg_tmod_hpm              :  1,    //      5
    reg_tmod_hdmi_scan        :  1,    //      6
    reg_tmod_hdmi_isol        :  1,    //      7
    reg_tmod_hdmi_earc        :  1,    //      8
    reg_tmod_ethernet         :  1,    //      9
    reg_tmod_c4tx_scan        :  1,    //     10
    reg_tmod_c4tx_isol        :  1,    //     11
    reg_tmod_c4tx_bist        :  1,    //     12
    reg_tmod_acodec_debug     :  1,    //     13
    reg_tmod_acodec           :  1,    //     14
                              : 17;    //  31:15 reserved
}CTOP_CTRL_ATG_TMOD_MUX0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_1408    jtag_mux ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jtag0_sel             :  4,    //   3: 0
    reg_jtag1_sel             :  4,    //   7: 4
    reg_jtag2_sel             :  4,    //  11: 8
    reg_jtag3_sel             :  4,    //  15:12
    reg_jtag0_lock            :  1,    //     16
    reg_jtag1_lock            :  1,    //     17
    reg_jtag2_lock            :  1,    //     18
    reg_jtag3_lock            :  1,    //     19
                              :  4,    //  23:20 reserved
    reg_use_jtag_hdmi_dbg     :  1,    //     24
                              :  7;    //  31:25 reserved
}CTOP_CTRL_ATG_JTAG_MUX_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_140C    uart_mux ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_uart0_sel             :  4,    //   3: 0
    reg_uart1_sel             :  4,    //   7: 4
    reg_uart2_sel             :  4,    //  11: 8
                              : 20;    //  31:12 reserved
}CTOP_CTRL_ATG_UART_MUX_O20A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_atg Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_ATG_PAD_MUX0_O20A0_T               pad_mux0                 ;         // 0xC930_1400
CTOP_CTRL_ATG_TMOD_MUX0_O20A0_T              tmod_mux0                ;         // 0xC930_1404
CTOP_CTRL_ATG_JTAG_MUX_O20A0_T               jtag_mux                 ;         // 0xC930_1408
CTOP_CTRL_ATG_UART_MUX_O20A0_T               uart_mux                 ;         // 0xC930_140C
} CTOP_CTRL_ATG_REG_O20A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_ATG_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

