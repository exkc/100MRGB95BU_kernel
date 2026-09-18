#ifndef _CTOP_FMS_M17A0_REG_H_
#define _CTOP_FMS_M17A0_REG_H_

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
                              :  2,    //   1: 0 reserved
    usb2_0_fsel               :  3,    //   4: 2
    usb2_0_txrestune0         :  2,    //   6: 5
    usb2_0_txhsxvtune0        :  2,    //   8: 7
    usb2_0_txvreftune0        :  4,    //  12: 9
    usb2_0_txrisetune0        :  2,    //  14:13
    usb2_0_txpreemppulsetune0 :  1,    //     15
    usb2_0_txpreempamptune0   :  2,    //  17:16
    usb2_0_txfslstune0        :  4,    //  21:18
    usb2_0_sqrxtune0          :  3,    //  24:22
    usb2_0_compdistune0       :  3,    //  27:25
    usb2_0_commononn          :  1,    //     28
    usb2_0_refclksel          :  2,    //  30:29
    usb2_0_portreset0         :  1;    //     31
}CTOP_FMS_CTOP_FMS_R00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C404    ctop_fms_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_0_bypasssel0         :  1,    //      0
    usb2_0_bypassdmen0        :  1,    //      1
    usb2_0_bypassdpen0        :  1,    //      2
    usb2_0_bypassdmdata0      :  1,    //      3
    usb2_0_bypassdpdata0      :  1,    //      4
    usb2_0_otgdisable0        :  1,    //      5
    usb2_0_vatestenb          :  2,    //   7: 6
    usb2_0_loopbackenb0       :  1,    //      8
    usb2_0_siddq              :  1,    //      9
    usb2_0_testclk0           :  1,    //     10
                              :  1,    //     11 reserved
    usb2_0_vbusvldext0        :  1,    //     12
    usb2_0_fsxcvrowner0       :  1,    //     13
    usb2_0_fsse0ext0          :  1,    //     14
    usb2_0_fsdataext0         :  1,    //     15
    usb2_0_testdatain0        :  8,    //  23:16
    usb2_0_testaddr0          :  4,    //  27:24
    usb2_0_testdataoutsel0    :  1,    //     28
    usb2_0_dmpulldown0        :  1,    //     29
    usb2_0_dppulldown0        :  1,    //     30
    usb2_0_atereset           :  1;    //     31
}CTOP_FMS_CTOP_FMS_R01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C408    ctop_fms_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    usb2_1_fsel               :  3,    //   4: 2
    usb2_1_txrestune0         :  2,    //   6: 5
    usb2_1_txhsxvtune0        :  2,    //   8: 7
    usb2_1_txvreftune0        :  4,    //  12: 9
    usb2_1_txrisetune0        :  2,    //  14:13
    usb2_1_txpreemppulsetune0 :  1,    //     15
    usb2_1_txpreempamptune0   :  2,    //  17:16
    usb2_1_txfslstune0        :  4,    //  21:18
    usb2_1_sqrxtune0          :  3,    //  24:22
    usb2_1_compdistune0       :  3,    //  27:25
    usb2_1_commononn          :  1,    //     28
    usb2_1_refclksel          :  2,    //  30:29
    usb2_1_portreset0         :  1;    //     31
}CTOP_FMS_CTOP_FMS_R02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C40C    ctop_fms_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_1_bypasssel0         :  1,    //      0
    usb2_1_bypassdmen0        :  1,    //      1
    usb2_1_bypassdpen0        :  1,    //      2
    usb2_1_bypassdmdata0      :  1,    //      3
    usb2_1_bypassdpdata0      :  1,    //      4
    usb2_1_otgdisable0        :  1,    //      5
    usb2_1_vatestenb          :  2,    //   7: 6
    usb2_1_loopbackenb0       :  1,    //      8
    usb2_1_siddq              :  1,    //      9
    usb2_1_testclk0           :  1,    //     10
                              :  2,    //  12:11 reserved
    usb2_1_fsxcvrowner0       :  1,    //     13
    usb2_1_fsse0ext0          :  1,    //     14
    usb2_1_fsdataext0         :  1,    //     15
    usb2_1_testdatain0        :  8,    //  23:16
    usb2_1_testaddr0          :  4,    //  27:24
    usb2_1_testdataoutsel0    :  1,    //     28
                              :  2,    //  30:29 reserved
    usb2_1_atereset           :  1;    //     31
}CTOP_FMS_CTOP_FMS_R03_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C410    ctop_fms_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    hdmi4_en                  :  1,    //      3
    hdmi3_en                  :  1,    //      4
    hdmi2_en                  :  1,    //      5
    hdmi1_en                  :  1,    //      6
    ddc_write_en              :  1,    //      7
    rx_sel_uart1              :  1,    //      8
    rx_sel_uart0              :  1,    //      9
    rx_sel_hdmi               :  2,    //  11:10
    rx_sel_mcu                :  2,    //  13:12
    rx_sel_te                 :  2,    //  15:14
    rx_sel_vdec0              :  2,    //  17:16
    rx_sel_tz                 :  2,    //  19:18
    uart2_sel                 :  4,    //  23:20
    uart1_sel                 :  4,    //  27:24
    uart0_sel                 :  4;    //  31:28
}CTOP_FMS_CTOP_FMS_R04_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C414    ctop_fms_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    rx_sel_dpe                :  2,    //   1: 0
    jtag0_disable             :  1,    //      2
    jtag_sel_tdo1             :  1,    //      3
    jtag_sel_tdo0             :  1,    //      4
    jtag_sel_bmc              :  1,    //      5
    jtag_sel_cpu              :  1,    //      6
    jtag_sel_te1              :  1,    //      7
    jtag1_sel                 :  3,    //  10: 8
    jtag_sel_vdec0            :  1,    //     11
    jtag_sel_aud              :  1,    //     12
    jtag_sel_pmcu             :  1,    //     13
    jtag_sel_te0              :  1,    //     14
                              :  1,    //     15 reserved
    jtag0_sel                 :  3,    //  18:16
                              : 12,    //  30:19 reserved
    jtag_hdmi_dbg             :  1;    //     31
}CTOP_FMS_CTOP_FMS_R05_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C418    ctop_fms_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_stpi0_data4_pu        :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_stpi0_data5_pu        :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_stpi0_data6_pu        :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_stpi0_data7_pu        :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_stpi0_err_pu          :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_stpi0_val_pu          :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_stpi0_sop_pu          :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_stpi0_clk_pu          :  1;    //     31
}CTOP_FMS_CTOP_FMS_R06_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C41C    ctop_fms_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_3tp_enb               :  1,    //      0     "NOTE: bit name is 'reg_3tp_en' in M16++ (C0 manual)"
                              :  2,    //   2: 1 reserved
    reg_tp_dvb_err_pu         :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_tp_dvb_val_pu         :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_tp_dvb_sop_pu         :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_tp_dvb_clk_pu         :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_stpi0_data0_pu        :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_stpi0_data1_pu        :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_stpi0_data2_pu        :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_stpi0_data3_pu        :  1;    //     31
}CTOP_FMS_CTOP_FMS_R07_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C420    ctop_fms_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_tp_dvb_data0_pu       :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_tp_dvb_data1_pu       :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_tp_dvb_data2_pu       :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_tp_dvb_data3_pu       :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_tp_dvb_data4_pu       :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_tp_dvb_data5_pu       :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_tp_dvb_data6_pu       :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_tp_dvb_data7_pu       :  1;    //     31
}CTOP_FMS_CTOP_FMS_R08_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C424    ctop_fms_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  8,    //   7: 0 reserved
    reg_hdmi2_2_5v_in_ds      :  1,    //      8
    reg_hdmi2_2_5v_in_pu      :  1,    //      9
    reg_hdmi2_2_5v_in_pd      :  1,    //     10
                              :  1,    //     11 reserved
    reg_hdmi2_1_5v_in_ds      :  1,    //     12
    reg_hdmi2_1_5v_in_pu      :  1,    //     13
    reg_hdmi2_1_5v_in_pd      :  1,    //     14
                              :  1,    //     15 reserved
    reg_hdmi2_0_5v_in_ds      :  1,    //     16
    reg_hdmi2_0_5v_in_pu      :  1,    //     17
    reg_hdmi2_0_5v_in_pd      :  1,    //     18
                              : 10,    //  28:19 reserved
    reg_hdmi2_012_hpd_ds      :  1,    //     29
    reg_hdmi2_012_hpd_pu      :  1,    //     30
    reg_hdmi2_012_hpd_pd      :  1;    //     31
}CTOP_FMS_CTOP_FMS_R09_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C428    ctop_fms_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi2_2_cd_sense_ds   :  1,    //      0
    reg_hdmi2_2_cd_sense_pu   :  1,    //      1
    reg_hdmi2_2_cd_sense_pd   :  1,    //      2
                              :  1,    //      3 reserved
    reg_hdmi2_2_sda_ds        :  1,    //      4
    reg_hdmi2_2_sda_pu        :  1,    //      5
    reg_hdmi2_2_sda_pd        :  1,    //      6
                              :  1,    //      7 reserved
    reg_hdmi2_2_scl_ds        :  1,    //      8
    reg_hdmi2_2_scl_pu        :  1,    //      9
    reg_hdmi2_2_scl_pd        :  1,    //     10
                              :  1,    //     11 reserved
    reg_hdmi2_1_sda_ds        :  1,    //     12
    reg_hdmi2_1_sda_pu        :  1,    //     13
    reg_hdmi2_1_sda_pd        :  1,    //     14
                              :  1,    //     15 reserved
    reg_hdmi2_1_scl_ds        :  1,    //     16
    reg_hdmi2_1_scl_pu        :  1,    //     17
    reg_hdmi2_1_scl_pd        :  1,    //     18
                              :  1,    //     19 reserved
    reg_hdmi2_0_sda_ds        :  1,    //     20
    reg_hdmi2_0_sda_pu        :  1,    //     21
    reg_hdmi2_0_sda_pd        :  1,    //     22
                              :  1,    //     23 reserved
    reg_hdmi2_0_scl_ds        :  1,    //     24
    reg_hdmi2_0_scl_pu        :  1,    //     25
    reg_hdmi2_0_scl_pd        :  1,    //     26
                              :  5;    //  31:27 reserved
}CTOP_FMS_CTOP_FMS_R10_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C42C    ctop_fms_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    txclkdrv0_icon_normal     :  3,    //   3: 1
    txclkdrv0_pdb_normal      :  1,    //      4
    txclkdrv2_icon_normal     :  3,    //   7: 5
    txclkdrv2_pdb_normal      :  1,    //      8
    tp_dvb_out_ctrl           :  2,    //  10: 9
    stpi0_out_ctrl            :  2,    //  12:11
    gp6_0_mux_en              :  1,    //     13
    gp6_1_mux_en              :  1,    //     14
    gp6_2_mux_en              :  1,    //     15
    gp6_3_mux_en              :  1,    //     16
    gp6_4_mux_en              :  1,    //     17
    gp6_5_mux_en              :  1,    //     18
                              :  1,    //     19 reserved
    gp12_0_mux_en             :  1,    //     20
    gp12_1_mux_en             :  1,    //     21
    gp12_2_mux_en             :  1,    //     22
    gp12_3_mux_en             :  1,    //     23
    gp12_4_mux_en             :  1,    //     24
    gp12_5_mux_en             :  1,    //     25
    gp12_6_mux_en             :  1,    //     26
    gp12_7_mux_en             :  1,    //     27
    gp5_4_mux_en              :  1,    //     28
    gp5_5_mux_en              :  1,    //     29
    gp5_6_mux_en              :  1,    //     30
    gp5_7_mux_en              :  1;    //     31
}CTOP_FMS_CTOP_FMS_R11_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C430    ctop_fms_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_1_por                :  1,    //      0
    usb2_0_por                :  1,    //      1
                              : 16,    //  17: 2 reserved
    reg_ifagc_pu              :  1,    //     18
                              :  1,    //     19 reserved
    hdmi4_en_edid             :  1,    //     20
    hdmi3_en_edid             :  1,    //     21
    hdmi2_en_edid             :  1,    //     22
    hdmi1_en_edid             :  1,    //     23
    ddc_write_en_edid         :  1,    //     24
    hdmi_i2c_en_cvi           :  1,    //     25
    phy_arc_mux               :  1,    //     26
    a_edid_jtag_hdmi_dbg      :  1,    //     27
                              :  3,    //  30:28 reserved
    tst_dbb_abb_sel           :  1;    //     31
}CTOP_FMS_CTOP_FMS_R12_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_C434    ctop_fms_r13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reseved                   : 20,    //  19: 0
    usb2_2_testdataout0       :  4,    //  23:20
    usb2_1_testdataout0       :  4,    //  27:24
    usb2_0_testdataout0       :  4;    //  31:28
}CTOP_FMS_CTOP_FMS_R13_M17_A0;

/*-----------------------------------------------------------------------------------------
    ctop_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_FMS_CTOP_FMS_R00_M17_A0                 ctop_fms_r00             ;         // 0xC930_C400
CTOP_FMS_CTOP_FMS_R01_M17_A0                 ctop_fms_r01             ;         // 0xC930_C404
CTOP_FMS_CTOP_FMS_R02_M17_A0                 ctop_fms_r02             ;         // 0xC930_C408
CTOP_FMS_CTOP_FMS_R03_M17_A0                 ctop_fms_r03             ;         // 0xC930_C40C
CTOP_FMS_CTOP_FMS_R04_M17_A0                 ctop_fms_r04             ;         // 0xC930_C410
CTOP_FMS_CTOP_FMS_R05_M17_A0                 ctop_fms_r05             ;         // 0xC930_C414
CTOP_FMS_CTOP_FMS_R06_M17_A0                 ctop_fms_r06             ;         // 0xC930_C418
CTOP_FMS_CTOP_FMS_R07_M17_A0                 ctop_fms_r07             ;         // 0xC930_C41C
CTOP_FMS_CTOP_FMS_R08_M17_A0                 ctop_fms_r08             ;         // 0xC930_C420
CTOP_FMS_CTOP_FMS_R09_M17_A0                 ctop_fms_r09             ;         // 0xC930_C424
CTOP_FMS_CTOP_FMS_R10_M17_A0                 ctop_fms_r10             ;         // 0xC930_C428
CTOP_FMS_CTOP_FMS_R11_M17_A0                 ctop_fms_r11             ;         // 0xC930_C42C
CTOP_FMS_CTOP_FMS_R12_M17_A0                 ctop_fms_r12             ;         // 0xC930_C430
CTOP_FMS_CTOP_FMS_R13_M17_A0                 ctop_fms_r13             ;         // 0xC930_C434
} CTOP_FMS_REG_M17_A0;
/* 14 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_FMS_M17A0_REG_H_ */

/* from 'M16PP_CTOP_Register_Manual_13.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

