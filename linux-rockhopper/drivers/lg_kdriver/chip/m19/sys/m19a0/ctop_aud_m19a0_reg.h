#ifndef _CTOP_AUD_M19A0_REG_H_
#define _CTOP_AUD_M19A0_REG_H_

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
    0xC9C6_0604    ctop_aud_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    reg_eb_addr13_pd          :  1,    //      2
                              :  3,    //   5: 3 reserved
    reg_eb_addr9_pd           :  1,    //      6
                              :  3,    //   9: 7 reserved
    reg_eb_addr10_pd          :  1,    //     10
                              :  3,    //  13:11 reserved
    reg_eb_addr11_pd          :  1,    //     14
                              :  3,    //  17:15 reserved
    reg_eb_addr12_pd          :  1,    //     18
                              : 13;    //  31:19 reserved
}CTOP_CTRL_AUD_CTOP_AUD_R01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0608    ctop_aud_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    reg_eb_addr4_pd           :  1,    //      2
                              :  3,    //   5: 3 reserved
    reg_eb_addr3_pd           :  1,    //      6
                              :  3,    //   9: 7 reserved
    reg_eb_addr5_pd           :  1,    //     10
                              :  3,    //  13:11 reserved
    reg_eb_addr6_pd           :  1,    //     14
                              :  3,    //  17:15 reserved
    reg_eb_addr8_pd           :  1,    //     18
                              :  3,    //  21:19 reserved
    reg_eb_addr7_pd           :  1,    //     22
                              :  3,    //  25:23 reserved
    reg_eb_addr15_pd          :  1,    //     26
                              :  3,    //  29:27 reserved
    reg_eb_addr14_pd          :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_CTRL_AUD_CTOP_AUD_R02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_060C    ctop_aud_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_cam_ireq_n_pu         :  1,    //      1
    reg_cam_ireq_n_pd         :  1,    //      2
                              :  2,    //   4: 3 reserved
    reg_cam_ce1_n_pu          :  1,    //      5
    reg_cam_ce1_n_pd          :  1,    //      6
                              :  2,    //   8: 7 reserved
    reg_cam_ce2_n_pu          :  1,    //      9
    reg_cam_ce2_n_pd          :  1,    //     10
                              :  2,    //  12:11 reserved
    reg_cam_reset_pu          :  1,    //     13
    reg_cam_reset_pd          :  1,    //     14
                              :  2,    //  16:15 reserved
    reg_cam_vccen_n_pu        :  1,    //     17
    reg_cam_vccen_n_pd        :  1,    //     18
                              : 13;    //  31:19 reserved
}CTOP_CTRL_AUD_CTOP_AUD_R03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0610    ctop_aud_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 20,    //  19: 0 reserved
    reg_cam_reg_n_pu          :  1,    //     20
    reg_cam_reg_n_pd          :  1,    //     21
                              :  1,    //     22 reserved
    reg_cam_cd1_n_pu          :  1,    //     23
    reg_cam_cd1_n_pd          :  1,    //     24
                              :  1,    //     25 reserved
    reg_cam_cd2_n_pu          :  1,    //     26
    reg_cam_cd2_n_pd          :  1,    //     27
                              :  1,    //     28 reserved
    reg_cam_wait_n_pu         :  1,    //     29
    reg_cam_wait_n_pd         :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_CTRL_AUD_CTOP_AUD_R04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0634    ctop_aud_r13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    cpupll_fine_div           :  1,    //      1
    cpupll_dss                :  1,    //      2
    cpupll_accuracy           :  2,    //   4: 3
    cpupll_updn_max           :  7,    //  11: 5
    cpupll_mod_freq           :  9,    //  20:12
    cpupll_m                  :  6,    //  26:21
                              :  1,    //     27 reserved
    cpupll_cih                :  4;    //  31:28
}CTOP_CTRL_AUD_CTOP_AUD_R13_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0638    ctop_aud_r14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    cpupll_ofs_mode           :  1,    //      4
    cpupll_fout3_od           :  3,    //   7: 5
    cpupll_fout2_od           :  3,    //  10: 8
    cpupll_fout_od            :  2,    //  12:11
    cpupll_pre_fout3_div      :  3,    //  15:13
    cpupll_pre_fout2_div      :  3,    //  18:16
    cpupll_nsc                :  4,    //  22:19
    cpupll_npc                :  6,    //  28:23
    cpupll_fine_control       :  3;    //  31:29
}CTOP_CTRL_AUD_CTOP_AUD_R14_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_063C    ctop_aud_r15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    cpupll_wakeup_bypass      :  1,    //     22
    cpupll_ddr_mode           :  1,    //     23
    cpupll_offset             :  8;    //  31:24
}CTOP_CTRL_AUD_CTOP_AUD_R15_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0640    ctop_aud_r16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_use_cpu_gpio_11_1     :  1,    //      1
                              :  9,    //  10: 2 reserved
    reg_use_cpu_gpio_14_3     :  1,    //     11
    reg_use_cpu_gpio_14_4     :  1,    //     12
    reg_use_cpu_gpio_14_5     :  1,    //     13
    reg_use_cpu_gpio_14_6     :  1,    //     14
    reg_use_cpu_gpio_14_7     :  1,    //     15
                              : 12,    //  27:16 reserved
    reg_use_cpu_gpio_16_4     :  1,    //     28
    reg_use_cpu_gpio_16_5     :  1,    //     29
    reg_use_cpu_gpio_16_6     :  1,    //     30
    reg_use_cpu_gpio_16_7     :  1;    //     31
}CTOP_CTRL_AUD_CTOP_AUD_R16_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0644    ctop_aud_r17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_tst_enable        :  1,    //      0
    reg_ext_eth_enable        :  1,    //      1
    reg_sc_clk_sel            :  1,    //      2
                              : 29;    //   31:3 reserved
}CTOP_CTRL_AUD_CTOP_AUD_R17_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0648    ctop_aud_r18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_efuse_pd              :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CTRL_AUD_CTOP_AUD_R18_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_064C    ctop_aud_r19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 20,    //  19: 0 reserved
    reg_sc_detect_pd          :  1,    //     20
    reg_sc_detect_pu          :  1,    //     21
    reg_sc_data_pd            :  1,    //     22
    reg_sc_data_pu            :  1,    //     23
    reg_sc_rst_pd             :  1,    //     24
    reg_sc_rst_pu             :  1,    //     25
    reg_sc_vcc_sel_pd         :  1,    //     26
    reg_sc_vcc_sel_pu         :  1,    //     27
    reg_sc_clk_out_pd         :  1,    //     28
    reg_sc_clk_out_pu         :  1,    //     29
    reg_sc_vccen_pd           :  1,    //     30
    reg_sc_vccen_pu           :  1;    //     31
}CTOP_CTRL_AUD_CTOP_AUD_R19_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0650    ctop_aud_r20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gpio131_ren           :  1,    //      0
    reg_gpio130_ren           :  1,    //      1
    reg_dbb_i2c_enable        :  1,    //      2
    reg_jtag2_disable         :  1,    //      3
    reg_use_jtag_hdmi_dbg     :  1,    //      4
                              : 27;    //   31:5 reserved
}CTOP_CTRL_AUD_CTOP_AUD_R20_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC9C6_0654    rxclkdrv_cpu ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_rxclkdrv_cpu_smv      :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_CTRL_AUD_RXCLKDRV_CPU_M19A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
UINT32                                                 _rsvd_00[   1] ;         // 0xC9C6_0600
CTOP_CTRL_AUD_CTOP_AUD_R01_M19A0_T           ctop_aud_r01             ;         // 0xC9C6_0604
CTOP_CTRL_AUD_CTOP_AUD_R02_M19A0_T           ctop_aud_r02             ;         // 0xC9C6_0608
CTOP_CTRL_AUD_CTOP_AUD_R03_M19A0_T           ctop_aud_r03             ;         // 0xC9C6_060C
CTOP_CTRL_AUD_CTOP_AUD_R04_M19A0_T           ctop_aud_r04             ;         // 0xC9C6_0610
UINT32                                                 _rsvd_01[   8] ;         // 0xC9C6_0614 ~ 0xC9C6_0630
CTOP_CTRL_AUD_CTOP_AUD_R13_M19A0_T           ctop_aud_r13             ;         // 0xC9C6_0634
CTOP_CTRL_AUD_CTOP_AUD_R14_M19A0_T           ctop_aud_r14             ;         // 0xC9C6_0638
CTOP_CTRL_AUD_CTOP_AUD_R15_M19A0_T           ctop_aud_r15             ;         // 0xC9C6_063C
CTOP_CTRL_AUD_CTOP_AUD_R16_M19A0_T           ctop_aud_r16             ;         // 0xC9C6_0640
CTOP_CTRL_AUD_CTOP_AUD_R17_M19A0_T           ctop_aud_r17             ;         // 0xC9C6_0644
CTOP_CTRL_AUD_CTOP_AUD_R18_M19A0_T           ctop_aud_r18             ;         // 0xC9C6_0648
CTOP_CTRL_AUD_CTOP_AUD_R19_M19A0_T           ctop_aud_r19             ;         // 0xC9C6_064C
CTOP_CTRL_AUD_CTOP_AUD_R20_M19A0_T           ctop_aud_r20             ;         // 0xC9C6_0650
CTOP_CTRL_AUD_RXCLKDRV_CPU_M19A0_T           rxclkdrv_cpu             ;         // 0xC9C6_0654
} CTOP_CTRL_AUD_REG_M19A0_T;
/* 13 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_AUD_M19A0_REG_H_ */

/* from 'M16P3_CTOP_Register_Manual_136.xlsm'  2018.4.18  KST by LGSiCRDV V2.2A*/

