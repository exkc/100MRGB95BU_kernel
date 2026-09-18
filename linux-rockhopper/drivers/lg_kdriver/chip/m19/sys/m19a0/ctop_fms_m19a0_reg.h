#ifndef _CTOP_FMS_M19A0_REG_H_
#define _CTOP_FMS_M19A0_REG_H_

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
    0xC930_C400    ctop_fms_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 11,    //  10: 0 reserved
    reg_use_cpu_gpio_8_0      :  1,    //     11
    reg_use_cpu_gpio_5_3      :  1,    //     12
    reg_use_cpu_gpio_5_2      :  1,    //     13
    reg_use_cpu_gpio_5_1      :  1,    //     14
    reg_use_cpu_gpio_7_7      :  1,    //     15
    reg_use_cpu_gpio_7_6      :  1,    //     16
    reg_use_cpu_gpio_7_5      :  1,    //     17
    reg_use_cpu_gpio_7_4      :  1,    //     18
                              :  1,    //     19 reserved
    reg_use_cpu_gpio_7_3      :  1,    //     20
    reg_use_cpu_gpio_7_2      :  1,    //     21
    reg_use_cpu_gpio_7_1      :  1,    //     22
    reg_use_cpu_gpio_7_0      :  1,    //     23
    reg_use_cpu_gpio_10_7     :  1,    //     24
    reg_use_cpu_gpio_10_6     :  1,    //     25
    reg_use_cpu_gpio_10_5     :  1,    //     26
    reg_use_cpu_gpio_10_4     :  1,    //     27
    reg_use_cpu_gpio_10_3     :  1,    //     28
    reg_use_cpu_gpio_10_2     :  1,    //     29
    reg_use_cpu_gpio_10_1     :  1,    //     30
    reg_use_cpu_gpio_10_0     :  1;    //     31
}CTOP_CTRL_FMS_CTOP_FMS_R00_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C404    ctop_fms_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 24,    //  23: 0 reserved
    reg_l_vsout_ld_pd         :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_pcmi3lrch_pd          :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_ext_intr0_pu          :  1;    //     31
}CTOP_CTRL_FMS_CTOP_FMS_R01_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C408    ctop_fms_r02 ''
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
}CTOP_CTRL_FMS_CTOP_FMS_R02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C40C    ctop_fms_r03 ''
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
}CTOP_CTRL_FMS_CTOP_FMS_R03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C410    ctop_fms_r04 ''
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
}CTOP_CTRL_FMS_CTOP_FMS_R04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C414    ctop_fms_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_boot_mode_pd          :  1,    //      1
    reg_pllset0_pd            :  1,    //      2
    reg_epi_eo_pd             :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_epi_gclk_pd           :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_daclrch_pd            :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_dacclfch_pd           :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_dacslrch_pd           :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_dacsck_pd             :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_daclrck_pd            :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_audclk_out_pd         :  1;    //     31
}CTOP_CTRL_FMS_CTOP_FMS_R05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_C418    ctop_fms_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 16,    //  15: 0 reserved
    reg_mon_nd1_en            :  1,    //     16
    reg_uart2_en              :  1,    //     17
    reg_pwm_trig_en           :  1,    //     18
                              :  1,    //     19 reserved
    reg_led_vs_en             :  1,    //     20
    reg_led_i2c_en            :  1,    //     21
    reg_jtag0_disable         :  1,    //     22
    reg_hdmi_i2c_en           :  1,    //     23
    reg_en_aud_daclrch        :  1,    //     24
    reg_aud_multi_ch_en       :  1,    //     25
    reg_mon_vsd_en            :  1,    //     26
    reg_mon_venc_en           :  1,    //     27
    reg_mon_vdec1_en          :  1,    //     28
    reg_mon_nd0_en            :  1,    //     29
    reg_mon_lbm_en            :  1,    //     30
    reg_mon_fms_en            :  1;    //     31
}CTOP_CTRL_FMS_CTOP_FMS_R06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_CTRL_FMS_CTOP_FMS_R00_M19A0_T           ctop_fms_r00             ;         // 0xC930_C400
CTOP_CTRL_FMS_CTOP_FMS_R01_M19A0_T           ctop_fms_r01             ;         // 0xC930_C404
CTOP_CTRL_FMS_CTOP_FMS_R02_M19A0_T           ctop_fms_r02             ;         // 0xC930_C408
CTOP_CTRL_FMS_CTOP_FMS_R03_M19A0_T           ctop_fms_r03             ;         // 0xC930_C40C
CTOP_CTRL_FMS_CTOP_FMS_R04_M19A0_T           ctop_fms_r04             ;         // 0xC930_C410
CTOP_CTRL_FMS_CTOP_FMS_R05_M19A0_T           ctop_fms_r05             ;         // 0xC930_C414
CTOP_CTRL_FMS_CTOP_FMS_R06_M19A0_T           ctop_fms_r06             ;         // 0xC930_C418
} CTOP_CTRL_FMS_REG_M19A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_FMS_M19A0_REG_H_ */

/* from 'M16P3_CTOP_Register_Manual_136.xlsm'  2018.4.18  KST by LGSiCRDV V2.2A*/

