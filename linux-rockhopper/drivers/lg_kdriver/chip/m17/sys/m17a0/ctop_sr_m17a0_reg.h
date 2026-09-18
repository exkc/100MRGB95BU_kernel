#ifndef _CTOP_SR_M17A0_REG_H_
#define _CTOP_SR_M17A0_REG_H_

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
    0xC930_5400    ctop_sr_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    auda_chop_en              :  1,    //      0
    auda_chop_freq            :  2,    //   2: 1
    auda_chop_refp_en         :  1,    //      3
    auda_ic_d2s               :  2,    //   5: 4
    auda_ic_refp              :  2,    //   7: 6
    auda_ic_ref               :  2,    //   9: 8
    auda_ic_scf               :  2,    //  11:10
    auda_vcont_refp           :  3,    //  14:12
                              :  1,    //     15 reserved
    auda_ccont                :  2,    //  17:16
                              :  2,    //  19:18 reserved
    auda_chop_vbuf_en         :  1,    //     20
    auda_cnt_rdiv             :  1,    //     21
                              :  2,    //  23:22 reserved
    auda_ic_bgr               :  2,    //  25:24
    auda_ic_iref              :  2,    //  27:26
    auda_ic_vbuf              :  2,    //  29:28
    auda_ic_vcom              :  2;    //  31:30
}CTOP_SR_CTOP_SR_R00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_5404    ctop_sr_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_scl2_ds               :  1,    //      0
    reg_scl2_pu               :  1,    //      1
    reg_scl2_pd               :  1,    //      2
                              :  1,    //      3 reserved
    reg_sda2_ds               :  1,    //      4
    reg_sda2_pu               :  1,    //      5
    reg_sda2_pd               :  1,    //      6
                              :  1,    //      7 reserved
    reg_scl1_ds               :  1,    //      8
    reg_scl1_pu               :  1,    //      9
    reg_scl1_pd               :  1,    //     10
                              :  1,    //     11 reserved
    reg_sda1_ds               :  1,    //     12
    reg_sda1_pu               :  1,    //     13
    reg_sda1_pd               :  1,    //     14
                              :  1,    //     15 reserved
    reg_scl0_ds               :  1,    //     16
    reg_scl0_pu               :  1,    //     17
    reg_scl0_pd               :  1,    //     18
                              :  1,    //     19 reserved
    reg_sda0_ds               :  1,    //     20
    reg_sda0_pu               :  1,    //     21
    reg_sda0_pd               :  1,    //     22
                              :  1,    //     23 reserved
    reg_scl4_ds               :  1,    //     24
    reg_scl4_pu               :  1,    //     25
    reg_scl4_pd               :  1,    //     26
                              :  1,    //     27 reserved
    reg_sda4_ds               :  1,    //     28
    reg_sda4_pu               :  1,    //     29
    reg_sda4_pd               :  1,    //     30
                              :  1;    //  31:31 reserved
}CTOP_SR_CTOP_SR_R01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_5408    ctop_sr_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  8,    //   7: 0 reserved
    reg_scl5_ds               :  1,    //      8
    reg_scl5_pu               :  1,    //      9
    reg_scl5_pd               :  1,    //     10
                              :  1,    //     11 reserved
    reg_sda5_ds               :  1,    //     12
    reg_sda5_pu               :  1,    //     13
    reg_sda5_pd               :  1,    //     14
                              :  1,    //     15 reserved
    reg_scl3_ds               :  1,    //     16
    reg_scl3_pu               :  1,    //     17
    reg_scl3_pd               :  1,    //     18
                              :  1,    //     19 reserved
    reg_sda3_ds               :  1,    //     20
    reg_sda3_pu               :  1,    //     21
    reg_sda3_pd               :  1,    //     22
    reg_avcom_fs_pd           :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_avcom_do_pd           :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_avcom_sclk_pd         :  1;    //     31
}CTOP_SR_CTOP_SR_R02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_540C    ctop_sr_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_spi_cs1_pu            :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_spi_di1_pu            :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_spi_cs0_pu            :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_spi_do0_pu            :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_spi_sclk1_pu          :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_spi_do1_pu            :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_spi_di0_pu            :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_spi_sclk0_pu          :  1;    //     31
}CTOP_SR_CTOP_SR_R03_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_5410    ctop_sr_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  7,    //   6: 0 reserved
    gp9_2_mux_en              :  1,    //      7
    gp9_6_mux_en              :  1,    //      8
    gp17_0_mux_en             :  1,    //      9
    gp17_2_mux_en             :  1,    //     10
    gp9_3_mux_en              :  1,    //     11
    gp9_7_mux_en              :  1,    //     12
    gp17_1_mux_en             :  1,    //     13
    gp17_3_mux_en             :  1,    //     14
    gp9_0_mux_en              :  1,    //     15
    gp9_1_mux_en              :  1,    //     16
    gp9_4_mux_en              :  1,    //     17
    gp9_5_mux_en              :  1,    //     18
                              :  5,    //  23:19 reserved
    gp4_0_mux_en              :  1,    //     24
    gp4_1_mux_en              :  1,    //     25
    gp4_2_mux_en              :  1,    //     26
    gp4_3_mux_en              :  1,    //     27
    gp4_4_mux_en              :  1,    //     28
    gp4_5_mux_en              :  1,    //     29
    gp4_6_mux_en              :  1,    //     30
    gp4_7_mux_en              :  1;    //     31
}CTOP_SR_CTOP_SR_R04_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_5414    ctop_sr_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 28,    //  27: 0 reserved
    rxclkdrv0_smv_normal      :  1,    //     28
    rxclkdrv0_outsel_normal   :  2,    //  30:29
    rxclkdrv0_pdb_normal      :  1;    //     31
}CTOP_SR_CTOP_SR_R05_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_5418    ctop_sr_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    auda_res                  :  3,    //   2: 0
                              :  1,    //      3 reserved
    auda_vcom_cont            :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}CTOP_SR_CTOP_SR_R06_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_541C    ctop_sr_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    usb2_2_fsel               :  3,    //   4: 2
    usb2_2_txrestune0         :  2,    //   6: 5
    usb2_2_txhsxvtune0        :  2,    //   8: 7
    usb2_2_txvreftune0        :  4,    //  12: 9
    usb2_2_txrisetune0        :  2,    //  14:13
    usb2_2_txpreemppulsetune0 :  1,    //     15
    usb2_2_txpreempamptune0   :  2,    //  17:16
    usb2_2_txfslstune0        :  4,    //  21:18
    usb2_2_sqrxtune0          :  3,    //  24:22
    usb2_2_compdistune0       :  3,    //  27:25
    usb2_2_commononn          :  1,    //     28
    usb2_2_refclksel          :  2,    //  30:29
    usb2_2_portreset0         :  1;    //     31
}CTOP_SR_CTOP_SR_R07_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_5420    ctop_sr_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_2_bypasssel0         :  1,    //      0
    usb2_2_bypassdmen0        :  1,    //      1
    usb2_2_bypassdpen0        :  1,    //      2
    usb2_2_bypassdmdata0      :  1,    //      3
    usb2_2_bypassdpdata0      :  1,    //      4
    usb2_2_otgdisable0        :  1,    //      5
    usb2_2_vatestenb          :  2,    //   7: 6
    usb2_2_loopbackenb0       :  1,    //      8
    usb2_2_siddq              :  1,    //      9
    usb2_2_testclk0           :  1,    //     10
                              :  2,    //  12:11 reserved
    usb2_2_fsxcvrowner0       :  1,    //     13
    usb2_2_fsse0ext0          :  1,    //     14
    usb2_2_fsdataext0         :  1,    //     15
    usb2_2_testdatain0        :  8,    //  23:16
    usb2_2_testaddr0          :  4,    //  27:24
    usb2_2_testdataoutsel0    :  1,    //     28
                              :  2,    //  30:29 reserved
    usb2_2_atereset           :  1;    //     31
}CTOP_SR_CTOP_SR_R08_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_5424    ctop_sr_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    usb2_2_por                :  1,    //      0
                              : 26,    //  26: 1 reserved
    jtag1_disable             :  1,    //     27
                              :  4;    //  31:28 reserved
}CTOP_SR_CTOP_SR_R09_M17_A0;

/*-----------------------------------------------------------------------------------------
    ctop_sr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_SR_CTOP_SR_R00_M17_A0                   ctop_sr_r00              ;         // 0xC930_5400
CTOP_SR_CTOP_SR_R01_M17_A0                   ctop_sr_r01              ;         // 0xC930_5404
CTOP_SR_CTOP_SR_R02_M17_A0                   ctop_sr_r02              ;         // 0xC930_5408
CTOP_SR_CTOP_SR_R03_M17_A0                   ctop_sr_r03              ;         // 0xC930_540C
CTOP_SR_CTOP_SR_R04_M17_A0                   ctop_sr_r04              ;         // 0xC930_5410
CTOP_SR_CTOP_SR_R05_M17_A0                   ctop_sr_r05              ;         // 0xC930_5414
CTOP_SR_CTOP_SR_R06_M17_A0                   ctop_sr_r06              ;         // 0xC930_5418
CTOP_SR_CTOP_SR_R07_M17_A0                   ctop_sr_r07              ;         // 0xC930_541C
CTOP_SR_CTOP_SR_R08_M17_A0                   ctop_sr_r08              ;         // 0xC930_5420
CTOP_SR_CTOP_SR_R09_M17_A0                   ctop_sr_r09              ;         // 0xC930_5424
} CTOP_SR_REG_M17_A0;
/* 10 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SR_M17A0_REG_H_ */

/* from 'M16PP_CTOP_Register_Manual_13.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

