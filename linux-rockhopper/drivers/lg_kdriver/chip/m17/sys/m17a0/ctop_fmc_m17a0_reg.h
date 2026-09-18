#ifndef _CTOP_FMC_M17A0_REG_H_
#define _CTOP_FMC_M17A0_REG_H_

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
    0xC930_9400    ctop_fmc_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 24,    //  23: 0 reserved
    reg_l_vsout_ld_pd         :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_pcmi3lrch_pd          :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_ext_intr0_pu          :  1;    //     31
}CTOP_FMC_CTOP_FMC_R00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_9404    ctop_fmc_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  7,    //   6: 0 reserved
    reg_pcmi3lrck_pd          :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_pcmi3sck_pd           :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_pwm_in_pu             :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_pwm2_pu               :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_pwm1_pu               :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_pwm0_pu               :  1,    //     27
                              :  4;    //  31:28 reserved
}CTOP_FMC_CTOP_FMC_R01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_9408    ctop_fmc_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  7,    //   6: 0 reserved
    reg_epi_mclk_pd           :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_epi_vst_pd            :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_dim1_sclk_pd          :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_dim1_mosi_pd          :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_dim0_sclk_pd          :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_dim0_mosi_pd          :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_frc_lrsync_pu         :  1;    //     31
}CTOP_FMC_CTOP_FMC_R02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_940C    ctop_fmc_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_gpio16_pd             :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_gpio17_pd             :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_gpio18_pd             :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_gpio19_pd             :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_gpio20_pd             :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_gpio21_pd             :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_gpio22_pd             :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_gpio23_pd             :  1;    //     31
}CTOP_FMC_CTOP_FMC_R03_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_9410    ctop_fmc_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_epi_eo_pd             :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_epi_gclk_pd           :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_daclrch_pu            :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_dacclfch_pu           :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_dacslrch_pu           :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_dacsck_pu             :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_daclrck_pu            :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_audclk_out_pd         :  1;    //     31
}CTOP_FMC_CTOP_FMC_R04_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_9414    ctop_fmc_r05 ''
-----------------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------------------
    0xC930_9418    ctop_fmc_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 16,    //  15: 0 reserved
    gp8_5_mux_en              :  1,    //     16
    gp8_6_mux_en              :  1,    //     17
    gp8_7_mux_en              :  1,    //     18
    gp10_0_mux_en             :  1,    //     19
    gp10_5_mux_en             :  1,    //     20
    gp10_6_mux_en             :  1,    //     21
    gp10_7_mux_en             :  1,    //     22
    gp8_0_mux_en              :  1,    //     23
    gp7_0_mux_en              :  1,    //     24
    gp7_1_mux_en              :  1,    //     25
    gp7_2_mux_en              :  1,    //     26
    gp7_3_mux_en              :  1,    //     27
    gp7_4_mux_en              :  1,    //     28
    gp7_5_mux_en              :  1,    //     29
    gp7_6_mux_en              :  1,    //     30
    gp7_7_mux_en              :  1;    //     31
}CTOP_FMC_CTOP_FMC_R06_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_941C    ctop_fmc_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  6,    //   5: 0 reserved
    jtag0_disable_cco         :  1,    //      6
    d1_enable_vsd             :  1,    //      7
    hdmi_i2c_en               :  1,    //      8
                              :  2,    //  10: 9 reserved
    led_i2c_en                :  1,    //     11
                              :  1,    //     12 reserved
    led_vs_en                 :  1,    //     13
                              :  1,    //     14 reserved
    uart2_en                  :  1,    //     15
                              :  4,    //  19:16 reserved
    mon_vsd_en                :  1,    //     20
    mon_vdec1_en              :  1,    //     21
    mon_nd0_en                :  1,    //     22
    mon_lbm_en                :  1,    //     23
    mon_fms_en                :  1,    //     24
    en_aud_daclrch            :  1,    //     25    "NOTE: bit name is 'en_aud_dacrlrch' in M16++ (C0 manual)"
    aud_multi_ch_en           :  1,    //     26
    gp10_4_mux_en             :  1,    //     27
    gp10_3_mux_en             :  1,    //     28
    gp10_2_mux_en             :  1,    //     29
    gp10_1_mux_en             :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_FMC_CTOP_FMC_R07_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_9420    ctop_fmc_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    gpupll_fine_div           :  1,    //      1
    gpupll_dss                :  1,    //      2
    gpupll_accuracy           :  2,    //   4: 3
    gpupll_updn_max           :  7,    //  11: 5
    gpupll_mod_freq           :  9,    //  20:12
    gpupll_m                  :  6,    //  26:21
                              :  1,    //     27 reserved
    gpupll_cih                :  4;    //  31:28
}CTOP_FMC_CTOP_FMC_R08_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_9424    ctop_fmc_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gpupll_freq_update        :  1,    //      0
    gpupll_sync_on            :  1,    //      1
                              :  2,    //   3: 2 reserved
    gpupll_ofs_mode           :  1,    //      4
    gpupll_fout3_od           :  3,    //   7: 5
    gpupll_fout2_od           :  3,    //  10: 8
    gpupll_fout_od            :  2,    //  12:11
    gpupll_pre_fout3_div      :  3,    //  15:13
    gpupll_pre_fout2_div      :  3,    //  18:16
    gpupll_nsc                :  4,    //  22:19
    gpupll_npc                :  6,    //  28:23
    gpupll_fine_control       :  3;    //  31:29
}CTOP_FMC_CTOP_FMC_R09_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_9428    ctop_fmc_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    gpupll_wakeup_bypass      :  1,    //     22
    gpupll_ddr_mode           :  1,    //     23
    gpupll_offset             :  8;    //  31:24
}CTOP_FMC_CTOP_FMC_R10_M17_A0;

/*-----------------------------------------------------------------------------------------
    ctop_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_FMC_CTOP_FMC_R00_M17_A0                 ctop_fmc_r00             ;         // 0xC930_9400
CTOP_FMC_CTOP_FMC_R01_M17_A0                 ctop_fmc_r01             ;         // 0xC930_9404
CTOP_FMC_CTOP_FMC_R02_M17_A0                 ctop_fmc_r02             ;         // 0xC930_9408
CTOP_FMC_CTOP_FMC_R03_M17_A0                 ctop_fmc_r03             ;         // 0xC930_940C
CTOP_FMC_CTOP_FMC_R04_M17_A0                 ctop_fmc_r04             ;         // 0xC930_9410
    UINT32                                   ctop_fmc_r05             ;         // 0xC930_9414
CTOP_FMC_CTOP_FMC_R06_M17_A0                 ctop_fmc_r06             ;         // 0xC930_9418
CTOP_FMC_CTOP_FMC_R07_M17_A0                 ctop_fmc_r07             ;         // 0xC930_941C
CTOP_FMC_CTOP_FMC_R08_M17_A0                 ctop_fmc_r08             ;         // 0xC930_9420
CTOP_FMC_CTOP_FMC_R09_M17_A0                 ctop_fmc_r09             ;         // 0xC930_9424
CTOP_FMC_CTOP_FMC_R10_M17_A0                 ctop_fmc_r10             ;         // 0xC930_9428
} CTOP_FMC_REG_M17_A0;
/* 11 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_FMC_M17A0_REG_H_ */

/* from 'M16PP_CTOP_Register_Manual_13.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

