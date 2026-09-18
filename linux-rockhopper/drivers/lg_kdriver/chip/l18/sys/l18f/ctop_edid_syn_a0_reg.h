#ifndef _CTOP_EDID_SYN_A0_REG_H_
#define _CTOP_EDID_SYN_A0_REG_H_

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
    0xC930_3000    syn_edid00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_icon         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}EDID_SYN_SYN_EDID00_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_3004    syn_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_jtag0_enable          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_hdmi1_ddc_disable     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_hdmi0_ddc_disable     :  1,    //      8
                              : 23;    //   31:9 reserved
}EDID_SYN_SYN_EDID01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_3008    syn_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  6,    //   5: 0 reserved
    reg_use_cpu_gpio_4_6      :  1,    //      6
    reg_use_cpu_gpio_4_7      :  1,    //      7
    reg_use_cpu_gpio_5_0      :  1,    //      8
    reg_use_cpu_gpio_5_1      :  1,    //      9
    reg_use_cpu_gpio_5_2      :  1,    //     10
    reg_use_cpu_gpio_5_3      :  1,    //     11
    reg_use_cpu_gpio_5_4      :  1,    //     12
    reg_use_cpu_gpio_5_5      :  1,    //     13
                              : 18;    //  31:14 reserved
}EDID_SYN_SYN_EDID02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_300C    syn_edid03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_edid_nisol_in__ren:  1,    //      0
    reg_pad_hdmi2_0_sda__pd   :  1,    //      1
    reg_pad_hdmi2_0_sda__pu   :  1,    //      2
    reg_pad_hdmi2_0_sda__ds   :  1,    //      3
    reg_pad_hdmi2_0_scl__pd   :  1,    //      4
    reg_pad_hdmi2_0_scl__pu   :  1,    //      5
    reg_pad_hdmi2_0_scl__ds   :  1,    //      6
    reg_pad_hdmi2_0_hpd__pd   :  1,    //      7
    reg_pad_hdmi2_0_hpd__pu   :  1,    //      8
    reg_pad_hdmi2_0_hpd__ds   :  1,    //      9
    reg_pad_hdmi2_0_5v_in__pd :  1,    //     10
    reg_pad_hdmi2_0_5v_in__pu :  1,    //     11
    reg_pad_hdmi2_0_5v_in__ds :  1,    //     12
    reg_pad_hdmi2_1_sda__pd   :  1,    //     13
    reg_pad_hdmi2_1_sda__pu   :  1,    //     14
    reg_pad_hdmi2_1_sda__ds   :  1,    //     15
    reg_pad_hdmi2_1_scl__pd   :  1,    //     16
    reg_pad_hdmi2_1_scl__pu   :  1,    //     17
    reg_pad_hdmi2_1_scl__ds   :  1,    //     18
    reg_pad_hdmi2_1_hpd__pd   :  1,    //     19
    reg_pad_hdmi2_1_hpd__pu   :  1,    //     20
    reg_pad_hdmi2_1_hpd__ds   :  1,    //     21
    reg_pad_hdmi2_1_5v_in__pd :  1,    //     22
    reg_pad_hdmi2_1_5v_in__pu :  1,    //     23
    reg_pad_hdmi2_2_5v_in__ds :  1,    //     24
                              :  7;    //  31:25 reserved
}EDID_SYN_SYN_EDID03_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_3010    syn_edid04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_apb1            :  1,    //      0
    reg_swrst_apb0            :  1,    //      1
    reg_swrst_comm_apb        :  1,    //      2
    reg_swrst_edid1           :  1,    //      3
    reg_swrst_edid0           :  1,    //      4
    reg_edid_clk_sel          :  2,    //   6: 5
    reg_apb_clk_gate_en       :  1,    //      7
                              : 24;    //   31:8 reserved
}EDID_SYN_SYN_EDID04_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_3014    syn_edid05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_r0                  : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}EDID_SYN_SYN_EDID05_L18F_A0;

/*-----------------------------------------------------------------------------------------
    edid_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
EDID_SYN_SYN_EDID00_L18F_A0                  syn_edid00               ;         // 0xC930_3000
EDID_SYN_SYN_EDID01_L18F_A0                  syn_edid01               ;         // 0xC930_3004
EDID_SYN_SYN_EDID02_L18F_A0                  syn_edid02               ;         // 0xC930_3008
EDID_SYN_SYN_EDID03_L18F_A0                  syn_edid03               ;         // 0xC930_300C
EDID_SYN_SYN_EDID04_L18F_A0                  syn_edid04               ;         // 0xC930_3010
EDID_SYN_SYN_EDID05_L18F_A0                  syn_edid05               ;         // 0xC930_3014
} EDID_SYN_REG_L18F_A0;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_EDID_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_Register_Manual_159.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

