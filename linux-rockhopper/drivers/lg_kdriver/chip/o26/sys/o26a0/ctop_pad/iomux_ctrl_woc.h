#ifndef _IOMUX_CTRL_WOC_REG_O26A0_H_
#define _IOMUX_CTRL_WOC_REG_O26A0_H_

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
    0xCA3A_3000    pad_woc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_aec_lrch3__ds0    :  1,    //      4
    reg_pad_aec_lrch3__ds1    :  1,    //      5
    reg_pad_aec_lrch3__ds2    :  1,    //      6
    reg_pad_aec_lrch3__ds3    :  1,    //      7
    reg_pad_aec_lrch3__pd     :  1,    //      8
    reg_pad_aec_lrch3__pu     :  1,    //      9
    reg_pad_aec_lrch3__st     :  1,    //     10
    reg_pad_aec_lrch2__ds0    :  1,    //     11
    reg_pad_aec_lrch2__ds1    :  1,    //     12
    reg_pad_aec_lrch2__ds2    :  1,    //     13
    reg_pad_aec_lrch2__ds3    :  1,    //     14
    reg_pad_aec_lrch2__pd     :  1,    //     15
    reg_pad_aec_lrch2__pu     :  1,    //     16
    reg_pad_aec_lrch2__st     :  1,    //     17
    reg_pad_aec_lrch1__ds0    :  1,    //     18
    reg_pad_aec_lrch1__ds1    :  1,    //     19
    reg_pad_aec_lrch1__ds2    :  1,    //     20
    reg_pad_aec_lrch1__ds3    :  1,    //     21
    reg_pad_aec_lrch1__pd     :  1,    //     22
    reg_pad_aec_lrch1__pu     :  1,    //     23
    reg_pad_aec_lrch1__st     :  1,    //     24
    reg_pad_aec_lrch0__ds0    :  1,    //     25
    reg_pad_aec_lrch0__ds1    :  1,    //     26
    reg_pad_aec_lrch0__ds2    :  1,    //     27
    reg_pad_aec_lrch0__ds3    :  1,    //     28
    reg_pad_aec_lrch0__pd     :  1,    //     29
    reg_pad_aec_lrch0__pu     :  1,    //     30
    reg_pad_aec_lrch0__st     :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3004    pad_woc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_daclrch__ds0      :  1,    //      4
    reg_pad_daclrch__ds1      :  1,    //      5
    reg_pad_daclrch__ds2      :  1,    //      6
    reg_pad_daclrch__ds3      :  1,    //      7
    reg_pad_daclrch__pd       :  1,    //      8
    reg_pad_daclrch__pu       :  1,    //      9
    reg_pad_daclrch__st       :  1,    //     10
    reg_pad_dacclfch__ds0     :  1,    //     11
    reg_pad_dacclfch__ds1     :  1,    //     12
    reg_pad_dacclfch__ds2     :  1,    //     13
    reg_pad_dacclfch__ds3     :  1,    //     14
    reg_pad_dacclfch__pd      :  1,    //     15
    reg_pad_dacclfch__pu      :  1,    //     16
    reg_pad_dacclfch__st      :  1,    //     17
    reg_pad_pcmi3sck__ds0     :  1,    //     18
    reg_pad_pcmi3sck__ds1     :  1,    //     19
    reg_pad_pcmi3sck__ds2     :  1,    //     20
    reg_pad_pcmi3sck__ds3     :  1,    //     21
    reg_pad_pcmi3sck__pd      :  1,    //     22
    reg_pad_pcmi3sck__pu      :  1,    //     23
    reg_pad_pcmi3sck__st      :  1,    //     24
    reg_pad_pcmi3lrck__ds0    :  1,    //     25
    reg_pad_pcmi3lrck__ds1    :  1,    //     26
    reg_pad_pcmi3lrck__ds2    :  1,    //     27
    reg_pad_pcmi3lrck__ds3    :  1,    //     28
    reg_pad_pcmi3lrck__pd     :  1,    //     29
    reg_pad_pcmi3lrck__pu     :  1,    //     30
    reg_pad_pcmi3lrck__st     :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3008    pad_woc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_pwm_in__ds0       :  1,    //      4
    reg_pad_pwm_in__ds1       :  1,    //      5
    reg_pad_pwm_in__ds2       :  1,    //      6
    reg_pad_pwm_in__ds3       :  1,    //      7
    reg_pad_pwm_in__pd        :  1,    //      8
    reg_pad_pwm_in__pu        :  1,    //      9
    reg_pad_pwm_in__st        :  1,    //     10
    reg_pad_dacslrch__ds0     :  1,    //     11
    reg_pad_dacslrch__ds1     :  1,    //     12
    reg_pad_dacslrch__ds2     :  1,    //     13
    reg_pad_dacslrch__ds3     :  1,    //     14
    reg_pad_dacslrch__pd      :  1,    //     15
    reg_pad_dacslrch__pu      :  1,    //     16
    reg_pad_dacslrch__st      :  1,    //     17
    reg_pad_dacsck__ds0       :  1,    //     18
    reg_pad_dacsck__ds1       :  1,    //     19
    reg_pad_dacsck__ds2       :  1,    //     20
    reg_pad_dacsck__ds3       :  1,    //     21
    reg_pad_dacsck__pd        :  1,    //     22
    reg_pad_dacsck__pu        :  1,    //     23
    reg_pad_dacsck__st        :  1,    //     24
    reg_pad_daclrck__ds0      :  1,    //     25
    reg_pad_daclrck__ds1      :  1,    //     26
    reg_pad_daclrck__ds2      :  1,    //     27
    reg_pad_daclrck__ds3      :  1,    //     28
    reg_pad_daclrck__pd       :  1,    //     29
    reg_pad_daclrck__pu       :  1,    //     30
    reg_pad_daclrck__st       :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_300C    pad_woc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_diseqc__ds0       :  1,    //      4
    reg_pad_diseqc__ds1       :  1,    //      5
    reg_pad_diseqc__ds2       :  1,    //      6
    reg_pad_diseqc__ds3       :  1,    //      7
    reg_pad_diseqc__pd        :  1,    //      8
    reg_pad_diseqc__pu        :  1,    //      9
    reg_pad_diseqc__st        :  1,    //     10
    reg_pad_pwm2__ds0         :  1,    //     11
    reg_pad_pwm2__ds1         :  1,    //     12
    reg_pad_pwm2__ds2         :  1,    //     13
    reg_pad_pwm2__ds3         :  1,    //     14
    reg_pad_pwm2__pd          :  1,    //     15
    reg_pad_pwm2__pu          :  1,    //     16
    reg_pad_pwm2__st          :  1,    //     17
    reg_pad_pwm1__ds0         :  1,    //     18
    reg_pad_pwm1__ds1         :  1,    //     19
    reg_pad_pwm1__ds2         :  1,    //     20
    reg_pad_pwm1__ds3         :  1,    //     21
    reg_pad_pwm1__pd          :  1,    //     22
    reg_pad_pwm1__pu          :  1,    //     23
    reg_pad_pwm1__st          :  1,    //     24
    reg_pad_pwm0__ds0         :  1,    //     25
    reg_pad_pwm0__ds1         :  1,    //     26
    reg_pad_pwm0__ds2         :  1,    //     27
    reg_pad_pwm0__ds3         :  1,    //     28
    reg_pad_pwm0__pd          :  1,    //     29
    reg_pad_pwm0__pu          :  1,    //     30
    reg_pad_pwm0__st          :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3010    pad_woc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_iec958out__ds0    :  1,    //      4
    reg_pad_iec958out__ds1    :  1,    //      5
    reg_pad_iec958out__ds2    :  1,    //      6
    reg_pad_iec958out__ds3    :  1,    //      7
    reg_pad_iec958out__pd     :  1,    //      8
    reg_pad_iec958out__pu     :  1,    //      9
    reg_pad_iec958out__st     :  1,    //     10
    reg_pad_fefctrl__ds0      :  1,    //     11
    reg_pad_fefctrl__ds1      :  1,    //     12
    reg_pad_fefctrl__ds2      :  1,    //     13
    reg_pad_fefctrl__ds3      :  1,    //     14
    reg_pad_fefctrl__pd       :  1,    //     15
    reg_pad_fefctrl__pu       :  1,    //     16
    reg_pad_fefctrl__st       :  1,    //     17
    reg_pad_diseqci__ds0      :  1,    //     18
    reg_pad_diseqci__ds1      :  1,    //     19
    reg_pad_diseqci__ds2      :  1,    //     20
    reg_pad_diseqci__ds3      :  1,    //     21
    reg_pad_diseqci__pd       :  1,    //     22
    reg_pad_diseqci__pu       :  1,    //     23
    reg_pad_diseqci__st       :  1,    //     24
    reg_pad_diseqc_cmd__ds0   :  1,    //     25
    reg_pad_diseqc_cmd__ds1   :  1,    //     26
    reg_pad_diseqc_cmd__ds2   :  1,    //     27
    reg_pad_diseqc_cmd__ds3   :  1,    //     28
    reg_pad_diseqc_cmd__pd    :  1,    //     29
    reg_pad_diseqc_cmd__pu    :  1,    //     30
    reg_pad_diseqc_cmd__st    :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3014    pad_woc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_micom_01__ds0     :  1,    //      4
    reg_pad_micom_01__ds1     :  1,    //      5
    reg_pad_micom_01__ds2     :  1,    //      6
    reg_pad_micom_01__ds3     :  1,    //      7
    reg_pad_micom_01__pd      :  1,    //      8
    reg_pad_micom_01__pu      :  1,    //      9
    reg_pad_micom_01__st      :  1,    //     10
    reg_pad_micom_00__ds0     :  1,    //     11
    reg_pad_micom_00__ds1     :  1,    //     12
    reg_pad_micom_00__ds2     :  1,    //     13
    reg_pad_micom_00__ds3     :  1,    //     14
    reg_pad_micom_00__pd      :  1,    //     15
    reg_pad_micom_00__pu      :  1,    //     16
    reg_pad_micom_00__st      :  1,    //     17
    reg_pad_ifagc_s__ds0      :  1,    //     18
    reg_pad_ifagc_s__ds1      :  1,    //     19
    reg_pad_ifagc_s__ds2      :  1,    //     20
    reg_pad_ifagc_s__ds3      :  1,    //     21
    reg_pad_ifagc_s__pd       :  1,    //     22
    reg_pad_ifagc_s__pu       :  1,    //     23
    reg_pad_ifagc_s__st       :  1,    //     24
    reg_pad_ifagc__ds0        :  1,    //     25
    reg_pad_ifagc__ds1        :  1,    //     26
    reg_pad_ifagc__ds2        :  1,    //     27
    reg_pad_ifagc__ds3        :  1,    //     28
    reg_pad_ifagc__pd         :  1,    //     29
    reg_pad_ifagc__pu         :  1,    //     30
    reg_pad_ifagc__st         :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3018    pad_woc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_micom_05__ds0     :  1,    //      4
    reg_pad_micom_05__ds1     :  1,    //      5
    reg_pad_micom_05__ds2     :  1,    //      6
    reg_pad_micom_05__ds3     :  1,    //      7
    reg_pad_micom_05__pd      :  1,    //      8
    reg_pad_micom_05__pu      :  1,    //      9
    reg_pad_micom_05__st      :  1,    //     10
    reg_pad_micom_04__ds0     :  1,    //     11
    reg_pad_micom_04__ds1     :  1,    //     12
    reg_pad_micom_04__ds2     :  1,    //     13
    reg_pad_micom_04__ds3     :  1,    //     14
    reg_pad_micom_04__pd      :  1,    //     15
    reg_pad_micom_04__pu      :  1,    //     16
    reg_pad_micom_04__st      :  1,    //     17
    reg_pad_micom_03__ds0     :  1,    //     18
    reg_pad_micom_03__ds1     :  1,    //     19
    reg_pad_micom_03__ds2     :  1,    //     20
    reg_pad_micom_03__ds3     :  1,    //     21
    reg_pad_micom_03__pd      :  1,    //     22
    reg_pad_micom_03__pu      :  1,    //     23
    reg_pad_micom_03__st      :  1,    //     24
    reg_pad_micom_02__ds0     :  1,    //     25
    reg_pad_micom_02__ds1     :  1,    //     26
    reg_pad_micom_02__ds2     :  1,    //     27
    reg_pad_micom_02__ds3     :  1,    //     28
    reg_pad_micom_02__pd      :  1,    //     29
    reg_pad_micom_02__pu      :  1,    //     30
    reg_pad_micom_02__st      :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_301C    pad_woc07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_micom_09__ds0     :  1,    //      4
    reg_pad_micom_09__ds1     :  1,    //      5
    reg_pad_micom_09__ds2     :  1,    //      6
    reg_pad_micom_09__ds3     :  1,    //      7
    reg_pad_micom_09__pd      :  1,    //      8
    reg_pad_micom_09__pu      :  1,    //      9
    reg_pad_micom_09__st      :  1,    //     10
    reg_pad_micom_08__ds0     :  1,    //     11
    reg_pad_micom_08__ds1     :  1,    //     12
    reg_pad_micom_08__ds2     :  1,    //     13
    reg_pad_micom_08__ds3     :  1,    //     14
    reg_pad_micom_08__pd      :  1,    //     15
    reg_pad_micom_08__pu      :  1,    //     16
    reg_pad_micom_08__st      :  1,    //     17
    reg_pad_micom_07__ds0     :  1,    //     18
    reg_pad_micom_07__ds1     :  1,    //     19
    reg_pad_micom_07__ds2     :  1,    //     20
    reg_pad_micom_07__ds3     :  1,    //     21
    reg_pad_micom_07__pd      :  1,    //     22
    reg_pad_micom_07__pu      :  1,    //     23
    reg_pad_micom_07__st      :  1,    //     24
    reg_pad_micom_06__ds0     :  1,    //     25
    reg_pad_micom_06__ds1     :  1,    //     26
    reg_pad_micom_06__ds2     :  1,    //     27
    reg_pad_micom_06__ds3     :  1,    //     28
    reg_pad_micom_06__pd      :  1,    //     29
    reg_pad_micom_06__pu      :  1,    //     30
    reg_pad_micom_06__st      :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3020    pad_woc08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_micom_13__ds0     :  1,    //      4
    reg_pad_micom_13__ds1     :  1,    //      5
    reg_pad_micom_13__ds2     :  1,    //      6
    reg_pad_micom_13__ds3     :  1,    //      7
    reg_pad_micom_13__pd      :  1,    //      8
    reg_pad_micom_13__pu      :  1,    //      9
    reg_pad_micom_13__st      :  1,    //     10
    reg_pad_micom_12__ds0     :  1,    //     11
    reg_pad_micom_12__ds1     :  1,    //     12
    reg_pad_micom_12__ds2     :  1,    //     13
    reg_pad_micom_12__ds3     :  1,    //     14
    reg_pad_micom_12__pd      :  1,    //     15
    reg_pad_micom_12__pu      :  1,    //     16
    reg_pad_micom_12__st      :  1,    //     17
    reg_pad_micom_11__ds0     :  1,    //     18
    reg_pad_micom_11__ds1     :  1,    //     19
    reg_pad_micom_11__ds2     :  1,    //     20
    reg_pad_micom_11__ds3     :  1,    //     21
    reg_pad_micom_11__pd      :  1,    //     22
    reg_pad_micom_11__pu      :  1,    //     23
    reg_pad_micom_11__st      :  1,    //     24
    reg_pad_micom_10__ds0     :  1,    //     25
    reg_pad_micom_10__ds1     :  1,    //     26
    reg_pad_micom_10__ds2     :  1,    //     27
    reg_pad_micom_10__ds3     :  1,    //     28
    reg_pad_micom_10__pd      :  1,    //     29
    reg_pad_micom_10__pu      :  1,    //     30
    reg_pad_micom_10__st      :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC08_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3024    pad_woc09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_micom_17__ds0     :  1,    //      4
    reg_pad_micom_17__ds1     :  1,    //      5
    reg_pad_micom_17__ds2     :  1,    //      6
    reg_pad_micom_17__ds3     :  1,    //      7
    reg_pad_micom_17__pd      :  1,    //      8
    reg_pad_micom_17__pu      :  1,    //      9
    reg_pad_micom_17__st      :  1,    //     10
    reg_pad_micom_16__ds0     :  1,    //     11
    reg_pad_micom_16__ds1     :  1,    //     12
    reg_pad_micom_16__ds2     :  1,    //     13
    reg_pad_micom_16__ds3     :  1,    //     14
    reg_pad_micom_16__pd      :  1,    //     15
    reg_pad_micom_16__pu      :  1,    //     16
    reg_pad_micom_16__st      :  1,    //     17
    reg_pad_micom_15__ds0     :  1,    //     18
    reg_pad_micom_15__ds1     :  1,    //     19
    reg_pad_micom_15__ds2     :  1,    //     20
    reg_pad_micom_15__ds3     :  1,    //     21
    reg_pad_micom_15__pd      :  1,    //     22
    reg_pad_micom_15__pu      :  1,    //     23
    reg_pad_micom_15__st      :  1,    //     24
    reg_pad_micom_14__ds0     :  1,    //     25
    reg_pad_micom_14__ds1     :  1,    //     26
    reg_pad_micom_14__ds2     :  1,    //     27
    reg_pad_micom_14__ds3     :  1,    //     28
    reg_pad_micom_14__pd      :  1,    //     29
    reg_pad_micom_14__pu      :  1,    //     30
    reg_pad_micom_14__st      :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC09_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3028    pad_woc10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_micom_21__ds0     :  1,    //      4
    reg_pad_micom_21__ds1     :  1,    //      5
    reg_pad_micom_21__ds2     :  1,    //      6
    reg_pad_micom_21__ds3     :  1,    //      7
    reg_pad_micom_21__pd      :  1,    //      8
    reg_pad_micom_21__pu      :  1,    //      9
    reg_pad_micom_21__st      :  1,    //     10
    reg_pad_micom_20__ds0     :  1,    //     11
    reg_pad_micom_20__ds1     :  1,    //     12
    reg_pad_micom_20__ds2     :  1,    //     13
    reg_pad_micom_20__ds3     :  1,    //     14
    reg_pad_micom_20__pd      :  1,    //     15
    reg_pad_micom_20__pu      :  1,    //     16
    reg_pad_micom_20__st      :  1,    //     17
    reg_pad_micom_19__ds0     :  1,    //     18
    reg_pad_micom_19__ds1     :  1,    //     19
    reg_pad_micom_19__ds2     :  1,    //     20
    reg_pad_micom_19__ds3     :  1,    //     21
    reg_pad_micom_19__pd      :  1,    //     22
    reg_pad_micom_19__pu      :  1,    //     23
    reg_pad_micom_19__st      :  1,    //     24
    reg_pad_micom_18__ds0     :  1,    //     25
    reg_pad_micom_18__ds1     :  1,    //     26
    reg_pad_micom_18__ds2     :  1,    //     27
    reg_pad_micom_18__ds3     :  1,    //     28
    reg_pad_micom_18__pd      :  1,    //     29
    reg_pad_micom_18__pu      :  1,    //     30
    reg_pad_micom_18__st      :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_302C    pad_woc11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_micom_25__ds0     :  1,    //      4
    reg_pad_micom_25__ds1     :  1,    //      5
    reg_pad_micom_25__ds2     :  1,    //      6
    reg_pad_micom_25__ds3     :  1,    //      7
    reg_pad_micom_25__pd      :  1,    //      8
    reg_pad_micom_25__pu      :  1,    //      9
    reg_pad_micom_25__st      :  1,    //     10
    reg_pad_micom_24__ds0     :  1,    //     11
    reg_pad_micom_24__ds1     :  1,    //     12
    reg_pad_micom_24__ds2     :  1,    //     13
    reg_pad_micom_24__ds3     :  1,    //     14
    reg_pad_micom_24__pd      :  1,    //     15
    reg_pad_micom_24__pu      :  1,    //     16
    reg_pad_micom_24__st      :  1,    //     17
    reg_pad_micom_23__ds0     :  1,    //     18
    reg_pad_micom_23__ds1     :  1,    //     19
    reg_pad_micom_23__ds2     :  1,    //     20
    reg_pad_micom_23__ds3     :  1,    //     21
    reg_pad_micom_23__pd      :  1,    //     22
    reg_pad_micom_23__pu      :  1,    //     23
    reg_pad_micom_23__st      :  1,    //     24
    reg_pad_micom_22__ds0     :  1,    //     25
    reg_pad_micom_22__ds1     :  1,    //     26
    reg_pad_micom_22__ds2     :  1,    //     27
    reg_pad_micom_22__ds3     :  1,    //     28
    reg_pad_micom_22__pd      :  1,    //     29
    reg_pad_micom_22__pu      :  1,    //     30
    reg_pad_micom_22__st      :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC11_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3030    pad_woc12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_micom_31__ds0     :  1,    //      4
    reg_pad_micom_31__ds1     :  1,    //      5
    reg_pad_micom_31__ds2     :  1,    //      6
    reg_pad_micom_31__ds3     :  1,    //      7
    reg_pad_micom_31__pd      :  1,    //      8
    reg_pad_micom_31__pu      :  1,    //      9
    reg_pad_micom_31__st      :  1,    //     10
    reg_pad_micom_30__ds0     :  1,    //     11
    reg_pad_micom_30__ds1     :  1,    //     12
    reg_pad_micom_30__ds2     :  1,    //     13
    reg_pad_micom_30__ds3     :  1,    //     14
    reg_pad_micom_30__pd      :  1,    //     15
    reg_pad_micom_30__pu      :  1,    //     16
    reg_pad_micom_30__st      :  1,    //     17
    reg_pad_micom_29__ds0     :  1,    //     18
    reg_pad_micom_29__ds1     :  1,    //     19
    reg_pad_micom_29__ds2     :  1,    //     20
    reg_pad_micom_29__ds3     :  1,    //     21
    reg_pad_micom_29__pd      :  1,    //     22
    reg_pad_micom_29__pu      :  1,    //     23
    reg_pad_micom_29__st      :  1,    //     24
    reg_pad_micom_28__ds0     :  1,    //     25
    reg_pad_micom_28__ds1     :  1,    //     26
    reg_pad_micom_28__ds2     :  1,    //     27
    reg_pad_micom_28__ds3     :  1,    //     28
    reg_pad_micom_28__pd      :  1,    //     29
    reg_pad_micom_28__pu      :  1,    //     30
    reg_pad_micom_28__st      :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC12_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3034    pad_woc13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_pdm1_datain__ds0  :  1,    //      4
    reg_pad_pdm1_datain__ds1  :  1,    //      5
    reg_pad_pdm1_datain__ds2  :  1,    //      6
    reg_pad_pdm1_datain__ds3  :  1,    //      7
    reg_pad_pdm1_datain__pd   :  1,    //      8
    reg_pad_pdm1_datain__pu   :  1,    //      9
    reg_pad_pdm1_datain__st   :  1,    //     10
    reg_pad_pdm0_datain__ds0  :  1,    //     11
    reg_pad_pdm0_datain__ds1  :  1,    //     12
    reg_pad_pdm0_datain__ds2  :  1,    //     13
    reg_pad_pdm0_datain__ds3  :  1,    //     14
    reg_pad_pdm0_datain__pd   :  1,    //     15
    reg_pad_pdm0_datain__pu   :  1,    //     16
    reg_pad_pdm0_datain__st   :  1,    //     17
    reg_pad_pdm_clkout__ds0   :  1,    //     18
    reg_pad_pdm_clkout__ds1   :  1,    //     19
    reg_pad_pdm_clkout__ds2   :  1,    //     20
    reg_pad_pdm_clkout__ds3   :  1,    //     21
    reg_pad_pdm_clkout__pd    :  1,    //     22
    reg_pad_pdm_clkout__pu    :  1,    //     23
    reg_pad_pdm_clkout__st    :  1,    //     24
    reg_pad_micom_32__ds0     :  1,    //     25
    reg_pad_micom_32__ds1     :  1,    //     26
    reg_pad_micom_32__ds2     :  1,    //     27
    reg_pad_micom_32__ds3     :  1,    //     28
    reg_pad_micom_32__pd      :  1,    //     29
    reg_pad_micom_32__pu      :  1,    //     30
    reg_pad_micom_32__st      :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC13_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3038    pad_woc14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  7,    //   6: 0 reserved
    reg_pad_m0_ret_ctrl__ds0  :  1,    //      7
    reg_pad_m0_ret_ctrl__ds1  :  1,    //      8
    reg_pad_m0_ret_ctrl__ds2  :  1,    //      9
    reg_pad_m0_ret_ctrl__ds3  :  1,    //     10
    reg_pad_m0_ret_ctrl__pd   :  1,    //     11
    reg_pad_m0_ret_ctrl__pu   :  1,    //     12
    reg_pad_m0_ret_ctrl__st   :  1,    //     13
    reg_pad_hdmi_cec__ds0     :  1,    //     14
    reg_pad_hdmi_cec__ds1     :  1,    //     15
    reg_pad_hdmi_cec__ds2     :  1,    //     16
    reg_pad_hdmi_cec__pd      :  1,    //     17
    reg_pad_hdmi_cec__pu      :  1,    //     18
    reg_pad_hdmi_cec__smt     :  1,    //     19
    reg_pad_uart0_tx__ds0     :  1,    //     20
    reg_pad_uart0_tx__ds1     :  1,    //     21
    reg_pad_uart0_tx__ds2     :  1,    //     22
    reg_pad_uart0_tx__pd      :  1,    //     23
    reg_pad_uart0_tx__pu      :  1,    //     24
    reg_pad_uart0_tx__smt     :  1,    //     25
    reg_pad_uart0_rx__ds0     :  1,    //     26
    reg_pad_uart0_rx__ds1     :  1,    //     27
    reg_pad_uart0_rx__ds2     :  1,    //     28
    reg_pad_uart0_rx__pd      :  1,    //     29
    reg_pad_uart0_rx__pu      :  1,    //     30
    reg_pad_uart0_rx__smt     :  1;    //     31
}IOMUX_CTRL_WOC_PAD_WOC14_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_303C    pad_woc15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  6,    //   5: 0 reserved
    reg_pad_xin__ds0          :  1,    //      6
    reg_pad_xin__ds1          :  1,    //      7
    reg_pad_xin__ds2          :  1,    //      8
    reg_pad_xin__ds3          :  1,    //      9
    reg_pad_xin__rd1          :  1,    //     10
    reg_pad_xin__rd0          :  1,    //     11
    reg_pad_xin__ref1         :  1,    //     12
    reg_pad_xin__ref0         :  1,    //     13
    reg_pad_opm__ds0          :  1,    //     14
    reg_pad_opm__ds1          :  1,    //     15
    reg_pad_opm__ds2          :  1,    //     16
    reg_pad_opm__ds3          :  1,    //     17
    reg_pad_opm__st           :  1,    //     18
    reg_pad_pores_n__ds0      :  1,    //     19
    reg_pad_pores_n__ds1      :  1,    //     20
    reg_pad_pores_n__ds2      :  1,    //     21
    reg_pad_pores_n__ds3      :  1,    //     22
    reg_pad_pores_n__st       :  1,    //     23
                              :  8;    //  31:24 reserved
}IOMUX_CTRL_WOC_PAD_WOC15_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3100    pad_woc64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_daclrch_mux_sel   :  4,    //   3: 0
    reg_pad_dacclfch_mux_sel  :  4,    //   7: 4
    reg_pad_pcmi3sck_mux_sel  :  4,    //  11: 8
    reg_pad_pcmi3lrck_mux_sel :  4,    //  15:12
    reg_pad_aec_lrch3_mux_sel :  4,    //  19:16
    reg_pad_aec_lrch2_mux_sel :  4,    //  23:20
    reg_pad_aec_lrch1_mux_sel :  4,    //  27:24
    reg_pad_aec_lrch0_mux_sel :  4;    //  31:28
}IOMUX_CTRL_WOC_PAD_WOC64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3104    pad_woc65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_diseqc_mux_sel    :  4,    //   3: 0
    reg_pad_pwm2_mux_sel      :  4,    //   7: 4
    reg_pad_pwm1_mux_sel      :  4,    //  11: 8
    reg_pad_pwm0_mux_sel      :  4,    //  15:12
    reg_pad_pwm_in_mux_sel    :  4,    //  19:16
    reg_pad_dacslrch_mux_sel  :  4,    //  23:20
    reg_pad_dacsck_mux_sel    :  4,    //  27:24
    reg_pad_daclrck_mux_sel   :  4;    //  31:28
}IOMUX_CTRL_WOC_PAD_WOC65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3108    pad_woc66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_01_mux_sel  :  4,    //   3: 0
    reg_pad_micom_00_mux_sel  :  4,    //   7: 4
    reg_pad_ifagc_s_mux_sel   :  4,    //  11: 8
    reg_pad_ifagc_mux_sel     :  4,    //  15:12
    reg_pad_iec958out_mux_sel :  4,    //  19:16
    reg_pad_fefctrl_mux_sel   :  4,    //  23:20
    reg_pad_diseqci_mux_sel   :  4,    //  27:24
    reg_pad_diseqc_cmd_mux_sel:  4;    //  31:28
}IOMUX_CTRL_WOC_PAD_WOC66_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_310C    pad_woc67 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_09_mux_sel  :  4,    //   3: 0
    reg_pad_micom_08_mux_sel  :  4,    //   7: 4
    reg_pad_micom_07_mux_sel  :  4,    //  11: 8
    reg_pad_micom_06_mux_sel  :  4,    //  15:12
    reg_pad_micom_05_mux_sel  :  4,    //  19:16
    reg_pad_micom_04_mux_sel  :  4,    //  23:20
    reg_pad_micom_03_mux_sel  :  4,    //  27:24
    reg_pad_micom_02_mux_sel  :  4;    //  31:28
}IOMUX_CTRL_WOC_PAD_WOC67_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3110    pad_woc68 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_17_mux_sel  :  4,    //   3: 0
    reg_pad_micom_16_mux_sel  :  4,    //   7: 4
    reg_pad_micom_15_mux_sel  :  4,    //  11: 8
    reg_pad_micom_14_mux_sel  :  4,    //  15:12
    reg_pad_micom_13_mux_sel  :  4,    //  19:16
    reg_pad_micom_12_mux_sel  :  4,    //  23:20
    reg_pad_micom_11_mux_sel  :  4,    //  27:24
    reg_pad_micom_10_mux_sel  :  4;    //  31:28
}IOMUX_CTRL_WOC_PAD_WOC68_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3114    pad_woc69 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_micom_25_mux_sel  :  4,    //   3: 0
    reg_pad_micom_24_mux_sel  :  4,    //   7: 4
    reg_pad_micom_23_mux_sel  :  4,    //  11: 8
    reg_pad_micom_22_mux_sel  :  4,    //  15:12
    reg_pad_micom_21_mux_sel  :  4,    //  19:16
    reg_pad_micom_20_mux_sel  :  4,    //  23:20
    reg_pad_micom_19_mux_sel  :  4,    //  27:24
    reg_pad_micom_18_mux_sel  :  4;    //  31:28
}IOMUX_CTRL_WOC_PAD_WOC69_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3118    pad_woc70 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pdm1_datain_mux_sel: 4,    //   3: 0
    reg_pad_pdm0_datain_mux_sel: 4,    //   7: 4
    reg_pad_pdm_clkout_mux_sel:  4,    //  11: 8
    reg_pad_micom_32_mux_sel  :  4,    //  15:12
    reg_pad_micom_31_mux_sel  :  4,    //  19:16
    reg_pad_micom_30_mux_sel  :  4,    //  23:20
    reg_pad_micom_29_mux_sel  :  4,    //  27:24
    reg_pad_micom_28_mux_sel  :  4;    //  31:28
}IOMUX_CTRL_WOC_PAD_WOC70_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_311C    pad_woc71 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_opm_mux_sel       :  4,    //   7: 4
    reg_pad_pores_n_mux_sel   :  4,    //  11: 8
    reg_pad_m0_ret_ctrl_mux_sel: 4,    //  15:12
    reg_pad_hdmi_cec_mux_sel  :  4,    //  19:16
    reg_pad_uart0_tx_mux_sel  :  4,    //  23:20
    reg_pad_uart0_rx_mux_sel  :  4,    //  27:24
                              :  4;    //  31:28 reserved
}IOMUX_CTRL_WOC_PAD_WOC71_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_WOC_PAD_WOC00_O26A0_T    pad_woc00 ;             // 0xCA3A_3000
    IOMUX_CTRL_WOC_PAD_WOC01_O26A0_T    pad_woc01 ;             // 0xCA3A_3004
    IOMUX_CTRL_WOC_PAD_WOC02_O26A0_T    pad_woc02 ;             // 0xCA3A_3008
    IOMUX_CTRL_WOC_PAD_WOC03_O26A0_T    pad_woc03 ;             // 0xCA3A_300C
    IOMUX_CTRL_WOC_PAD_WOC04_O26A0_T    pad_woc04 ;             // 0xCA3A_3010
    IOMUX_CTRL_WOC_PAD_WOC05_O26A0_T    pad_woc05 ;             // 0xCA3A_3014
    IOMUX_CTRL_WOC_PAD_WOC06_O26A0_T    pad_woc06 ;             // 0xCA3A_3018
    IOMUX_CTRL_WOC_PAD_WOC07_O26A0_T    pad_woc07 ;             // 0xCA3A_301C
    IOMUX_CTRL_WOC_PAD_WOC08_O26A0_T    pad_woc08 ;             // 0xCA3A_3020
    IOMUX_CTRL_WOC_PAD_WOC09_O26A0_T    pad_woc09 ;             // 0xCA3A_3024
    IOMUX_CTRL_WOC_PAD_WOC10_O26A0_T    pad_woc10 ;             // 0xCA3A_3028
    IOMUX_CTRL_WOC_PAD_WOC11_O26A0_T    pad_woc11 ;             // 0xCA3A_302C
    IOMUX_CTRL_WOC_PAD_WOC12_O26A0_T    pad_woc12 ;             // 0xCA3A_3030
    IOMUX_CTRL_WOC_PAD_WOC13_O26A0_T    pad_woc13 ;             // 0xCA3A_3034
    IOMUX_CTRL_WOC_PAD_WOC14_O26A0_T    pad_woc14 ;             // 0xCA3A_3038
    IOMUX_CTRL_WOC_PAD_WOC15_O26A0_T    pad_woc15 ;             // 0xCA3A_303C
    UINT32                             _rsvd_00[48];            // 0xCA3A_3040 ~ 0xCA3A_30FC
    IOMUX_CTRL_WOC_PAD_WOC64_O26A0_T    pad_woc64 ;             // 0xCA3A_3100
    IOMUX_CTRL_WOC_PAD_WOC65_O26A0_T    pad_woc65 ;             // 0xCA3A_3104
    IOMUX_CTRL_WOC_PAD_WOC66_O26A0_T    pad_woc66 ;             // 0xCA3A_3108
    IOMUX_CTRL_WOC_PAD_WOC67_O26A0_T    pad_woc67 ;             // 0xCA3A_310C
    IOMUX_CTRL_WOC_PAD_WOC68_O26A0_T    pad_woc68 ;             // 0xCA3A_3110
    IOMUX_CTRL_WOC_PAD_WOC69_O26A0_T    pad_woc69 ;             // 0xCA3A_3114
    IOMUX_CTRL_WOC_PAD_WOC70_O26A0_T    pad_woc70 ;             // 0xCA3A_3118
    IOMUX_CTRL_WOC_PAD_WOC71_O26A0_T    pad_woc71 ;             // 0xCA3A_311C
}IOMUX_CTRL_WOC_REG_O26A0_T;
/* 24 regs */

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

#define IOMUX_CTRL_WOC_PAD_WOC00_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define IOMUX_CTRL_WOC_PAD_WOC01_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define IOMUX_CTRL_WOC_PAD_WOC02_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define IOMUX_CTRL_WOC_PAD_WOC03_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define IOMUX_CTRL_WOC_PAD_WOC04_O26A0_T_OFF                (BASEADDRESS+0x0010)
#define IOMUX_CTRL_WOC_PAD_WOC05_O26A0_T_OFF                (BASEADDRESS+0x0014)
#define IOMUX_CTRL_WOC_PAD_WOC06_O26A0_T_OFF                (BASEADDRESS+0x0018)
#define IOMUX_CTRL_WOC_PAD_WOC07_O26A0_T_OFF                (BASEADDRESS+0x001C)
#define IOMUX_CTRL_WOC_PAD_WOC08_O26A0_T_OFF                (BASEADDRESS+0x0020)
#define IOMUX_CTRL_WOC_PAD_WOC09_O26A0_T_OFF                (BASEADDRESS+0x0024)
#define IOMUX_CTRL_WOC_PAD_WOC10_O26A0_T_OFF                (BASEADDRESS+0x0028)
#define IOMUX_CTRL_WOC_PAD_WOC11_O26A0_T_OFF                (BASEADDRESS+0x002C)
#define IOMUX_CTRL_WOC_PAD_WOC12_O26A0_T_OFF                (BASEADDRESS+0x0030)
#define IOMUX_CTRL_WOC_PAD_WOC13_O26A0_T_OFF                (BASEADDRESS+0x0034)
#define IOMUX_CTRL_WOC_PAD_WOC14_O26A0_T_OFF                (BASEADDRESS+0x0038)
#define IOMUX_CTRL_WOC_PAD_WOC15_O26A0_T_OFF                (BASEADDRESS+0x003C)
#define IOMUX_CTRL_WOC_PAD_WOC64_O26A0_T_OFF                (BASEADDRESS+0x0100)
#define IOMUX_CTRL_WOC_PAD_WOC65_O26A0_T_OFF                (BASEADDRESS+0x0104)
#define IOMUX_CTRL_WOC_PAD_WOC66_O26A0_T_OFF                (BASEADDRESS+0x0108)
#define IOMUX_CTRL_WOC_PAD_WOC67_O26A0_T_OFF                (BASEADDRESS+0x010C)
#define IOMUX_CTRL_WOC_PAD_WOC68_O26A0_T_OFF                (BASEADDRESS+0x0110)
#define IOMUX_CTRL_WOC_PAD_WOC69_O26A0_T_OFF                (BASEADDRESS+0x0114)
#define IOMUX_CTRL_WOC_PAD_WOC70_O26A0_T_OFF                (BASEADDRESS+0x0118)
#define IOMUX_CTRL_WOC_PAD_WOC71_O26A0_T_OFF                (BASEADDRESS+0x011C)

/*-----------------------------------------------------------------------------------------
    0xCA3A_3000    pad_woc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_aec_lrch3__ds0: 1;    //    4
    UINT32 reg_pad_aec_lrch3__ds1: 1;    //    5
    UINT32 reg_pad_aec_lrch3__ds2: 1;    //    6
    UINT32 reg_pad_aec_lrch3__ds3: 1;    //    7
    UINT32 reg_pad_aec_lrch3__pd: 1;    //     8
    UINT32 reg_pad_aec_lrch3__pu: 1;    //     9
    UINT32 reg_pad_aec_lrch3__st: 1;    //    10
    UINT32 reg_pad_aec_lrch2__ds0: 1;    //   11
    UINT32 reg_pad_aec_lrch2__ds1: 1;    //   12
    UINT32 reg_pad_aec_lrch2__ds2: 1;    //   13
    UINT32 reg_pad_aec_lrch2__ds3: 1;    //   14
    UINT32 reg_pad_aec_lrch2__pd: 1;    //    15
    UINT32 reg_pad_aec_lrch2__pu: 1;    //    16
    UINT32 reg_pad_aec_lrch2__st: 1;    //    17
    UINT32 reg_pad_aec_lrch1__ds0: 1;    //   18
    UINT32 reg_pad_aec_lrch1__ds1: 1;    //   19
    UINT32 reg_pad_aec_lrch1__ds2: 1;    //   20
    UINT32 reg_pad_aec_lrch1__ds3: 1;    //   21
    UINT32 reg_pad_aec_lrch1__pd: 1;    //    22
    UINT32 reg_pad_aec_lrch1__pu: 1;    //    23
    UINT32 reg_pad_aec_lrch1__st: 1;    //    24
    UINT32 reg_pad_aec_lrch0__ds0: 1;    //   25
    UINT32 reg_pad_aec_lrch0__ds1: 1;    //   26
    UINT32 reg_pad_aec_lrch0__ds2: 1;    //   27
    UINT32 reg_pad_aec_lrch0__ds3: 1;    //   28
    UINT32 reg_pad_aec_lrch0__pd: 1;    //    29
    UINT32 reg_pad_aec_lrch0__pu: 1;    //    30
    UINT32 reg_pad_aec_lrch0__st: 1;    //    31
    };
}IOMUX_CTRL_WOC_PAD_WOC00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3004    pad_woc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_daclrch__ds0: 1;    //      4
    UINT32 reg_pad_daclrch__ds1: 1;    //      5
    UINT32 reg_pad_daclrch__ds2: 1;    //      6
    UINT32 reg_pad_daclrch__ds3: 1;    //      7
    UINT32 reg_pad_daclrch__pd:  1;    //      8
    UINT32 reg_pad_daclrch__pu:  1;    //      9
    UINT32 reg_pad_daclrch__st:  1;    //     10
    UINT32 reg_pad_dacclfch__ds0: 1;    //    11
    UINT32 reg_pad_dacclfch__ds1: 1;    //    12
    UINT32 reg_pad_dacclfch__ds2: 1;    //    13
    UINT32 reg_pad_dacclfch__ds3: 1;    //    14
    UINT32 reg_pad_dacclfch__pd: 1;    //     15
    UINT32 reg_pad_dacclfch__pu: 1;    //     16
    UINT32 reg_pad_dacclfch__st: 1;    //     17
    UINT32 reg_pad_pcmi3sck__ds0: 1;    //    18
    UINT32 reg_pad_pcmi3sck__ds1: 1;    //    19
    UINT32 reg_pad_pcmi3sck__ds2: 1;    //    20
    UINT32 reg_pad_pcmi3sck__ds3: 1;    //    21
    UINT32 reg_pad_pcmi3sck__pd: 1;    //     22
    UINT32 reg_pad_pcmi3sck__pu: 1;    //     23
    UINT32 reg_pad_pcmi3sck__st: 1;    //     24
    UINT32 reg_pad_pcmi3lrck__ds0: 1;    //   25
    UINT32 reg_pad_pcmi3lrck__ds1: 1;    //   26
    UINT32 reg_pad_pcmi3lrck__ds2: 1;    //   27
    UINT32 reg_pad_pcmi3lrck__ds3: 1;    //   28
    UINT32 reg_pad_pcmi3lrck__pd: 1;    //    29
    UINT32 reg_pad_pcmi3lrck__pu: 1;    //    30
    UINT32 reg_pad_pcmi3lrck__st: 1;    //    31
    };
}IOMUX_CTRL_WOC_PAD_WOC01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3008    pad_woc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_pwm_in__ds0:  1;    //      4
    UINT32 reg_pad_pwm_in__ds1:  1;    //      5
    UINT32 reg_pad_pwm_in__ds2:  1;    //      6
    UINT32 reg_pad_pwm_in__ds3:  1;    //      7
    UINT32 reg_pad_pwm_in__pd :  1;    //      8
    UINT32 reg_pad_pwm_in__pu :  1;    //      9
    UINT32 reg_pad_pwm_in__st :  1;    //     10
    UINT32 reg_pad_dacslrch__ds0: 1;    //    11
    UINT32 reg_pad_dacslrch__ds1: 1;    //    12
    UINT32 reg_pad_dacslrch__ds2: 1;    //    13
    UINT32 reg_pad_dacslrch__ds3: 1;    //    14
    UINT32 reg_pad_dacslrch__pd: 1;    //     15
    UINT32 reg_pad_dacslrch__pu: 1;    //     16
    UINT32 reg_pad_dacslrch__st: 1;    //     17
    UINT32 reg_pad_dacsck__ds0:  1;    //     18
    UINT32 reg_pad_dacsck__ds1:  1;    //     19
    UINT32 reg_pad_dacsck__ds2:  1;    //     20
    UINT32 reg_pad_dacsck__ds3:  1;    //     21
    UINT32 reg_pad_dacsck__pd :  1;    //     22
    UINT32 reg_pad_dacsck__pu :  1;    //     23
    UINT32 reg_pad_dacsck__st :  1;    //     24
    UINT32 reg_pad_daclrck__ds0: 1;    //     25
    UINT32 reg_pad_daclrck__ds1: 1;    //     26
    UINT32 reg_pad_daclrck__ds2: 1;    //     27
    UINT32 reg_pad_daclrck__ds3: 1;    //     28
    UINT32 reg_pad_daclrck__pd:  1;    //     29
    UINT32 reg_pad_daclrck__pu:  1;    //     30
    UINT32 reg_pad_daclrck__st:  1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_300C    pad_woc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_diseqc__ds0:  1;    //      4
    UINT32 reg_pad_diseqc__ds1:  1;    //      5
    UINT32 reg_pad_diseqc__ds2:  1;    //      6
    UINT32 reg_pad_diseqc__ds3:  1;    //      7
    UINT32 reg_pad_diseqc__pd :  1;    //      8
    UINT32 reg_pad_diseqc__pu :  1;    //      9
    UINT32 reg_pad_diseqc__st :  1;    //     10
    UINT32 reg_pad_pwm2__ds0  :  1;    //     11
    UINT32 reg_pad_pwm2__ds1  :  1;    //     12
    UINT32 reg_pad_pwm2__ds2  :  1;    //     13
    UINT32 reg_pad_pwm2__ds3  :  1;    //     14
    UINT32 reg_pad_pwm2__pd   :  1;    //     15
    UINT32 reg_pad_pwm2__pu   :  1;    //     16
    UINT32 reg_pad_pwm2__st   :  1;    //     17
    UINT32 reg_pad_pwm1__ds0  :  1;    //     18
    UINT32 reg_pad_pwm1__ds1  :  1;    //     19
    UINT32 reg_pad_pwm1__ds2  :  1;    //     20
    UINT32 reg_pad_pwm1__ds3  :  1;    //     21
    UINT32 reg_pad_pwm1__pd   :  1;    //     22
    UINT32 reg_pad_pwm1__pu   :  1;    //     23
    UINT32 reg_pad_pwm1__st   :  1;    //     24
    UINT32 reg_pad_pwm0__ds0  :  1;    //     25
    UINT32 reg_pad_pwm0__ds1  :  1;    //     26
    UINT32 reg_pad_pwm0__ds2  :  1;    //     27
    UINT32 reg_pad_pwm0__ds3  :  1;    //     28
    UINT32 reg_pad_pwm0__pd   :  1;    //     29
    UINT32 reg_pad_pwm0__pu   :  1;    //     30
    UINT32 reg_pad_pwm0__st   :  1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3010    pad_woc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_iec958out__ds0: 1;    //    4
    UINT32 reg_pad_iec958out__ds1: 1;    //    5
    UINT32 reg_pad_iec958out__ds2: 1;    //    6
    UINT32 reg_pad_iec958out__ds3: 1;    //    7
    UINT32 reg_pad_iec958out__pd: 1;    //     8
    UINT32 reg_pad_iec958out__pu: 1;    //     9
    UINT32 reg_pad_iec958out__st: 1;    //    10
    UINT32 reg_pad_fefctrl__ds0: 1;    //     11
    UINT32 reg_pad_fefctrl__ds1: 1;    //     12
    UINT32 reg_pad_fefctrl__ds2: 1;    //     13
    UINT32 reg_pad_fefctrl__ds3: 1;    //     14
    UINT32 reg_pad_fefctrl__pd:  1;    //     15
    UINT32 reg_pad_fefctrl__pu:  1;    //     16
    UINT32 reg_pad_fefctrl__st:  1;    //     17
    UINT32 reg_pad_diseqci__ds0: 1;    //     18
    UINT32 reg_pad_diseqci__ds1: 1;    //     19
    UINT32 reg_pad_diseqci__ds2: 1;    //     20
    UINT32 reg_pad_diseqci__ds3: 1;    //     21
    UINT32 reg_pad_diseqci__pd:  1;    //     22
    UINT32 reg_pad_diseqci__pu:  1;    //     23
    UINT32 reg_pad_diseqci__st:  1;    //     24
    UINT32 reg_pad_diseqc_cmd__ds0: 1;    //  25
    UINT32 reg_pad_diseqc_cmd__ds1: 1;    //  26
    UINT32 reg_pad_diseqc_cmd__ds2: 1;    //  27
    UINT32 reg_pad_diseqc_cmd__ds3: 1;    //  28
    UINT32 reg_pad_diseqc_cmd__pd: 1;    //   29
    UINT32 reg_pad_diseqc_cmd__pu: 1;    //   30
    UINT32 reg_pad_diseqc_cmd__st: 1;    //   31
    };
}IOMUX_CTRL_WOC_PAD_WOC04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3014    pad_woc05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_micom_01__ds0: 1;    //     4
    UINT32 reg_pad_micom_01__ds1: 1;    //     5
    UINT32 reg_pad_micom_01__ds2: 1;    //     6
    UINT32 reg_pad_micom_01__ds3: 1;    //     7
    UINT32 reg_pad_micom_01__pd: 1;    //      8
    UINT32 reg_pad_micom_01__pu: 1;    //      9
    UINT32 reg_pad_micom_01__st: 1;    //     10
    UINT32 reg_pad_micom_00__ds0: 1;    //    11
    UINT32 reg_pad_micom_00__ds1: 1;    //    12
    UINT32 reg_pad_micom_00__ds2: 1;    //    13
    UINT32 reg_pad_micom_00__ds3: 1;    //    14
    UINT32 reg_pad_micom_00__pd: 1;    //     15
    UINT32 reg_pad_micom_00__pu: 1;    //     16
    UINT32 reg_pad_micom_00__st: 1;    //     17
    UINT32 reg_pad_ifagc_s__ds0: 1;    //     18
    UINT32 reg_pad_ifagc_s__ds1: 1;    //     19
    UINT32 reg_pad_ifagc_s__ds2: 1;    //     20
    UINT32 reg_pad_ifagc_s__ds3: 1;    //     21
    UINT32 reg_pad_ifagc_s__pd:  1;    //     22
    UINT32 reg_pad_ifagc_s__pu:  1;    //     23
    UINT32 reg_pad_ifagc_s__st:  1;    //     24
    UINT32 reg_pad_ifagc__ds0 :  1;    //     25
    UINT32 reg_pad_ifagc__ds1 :  1;    //     26
    UINT32 reg_pad_ifagc__ds2 :  1;    //     27
    UINT32 reg_pad_ifagc__ds3 :  1;    //     28
    UINT32 reg_pad_ifagc__pd  :  1;    //     29
    UINT32 reg_pad_ifagc__pu  :  1;    //     30
    UINT32 reg_pad_ifagc__st  :  1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3018    pad_woc06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_micom_05__ds0: 1;    //     4
    UINT32 reg_pad_micom_05__ds1: 1;    //     5
    UINT32 reg_pad_micom_05__ds2: 1;    //     6
    UINT32 reg_pad_micom_05__ds3: 1;    //     7
    UINT32 reg_pad_micom_05__pd: 1;    //      8
    UINT32 reg_pad_micom_05__pu: 1;    //      9
    UINT32 reg_pad_micom_05__st: 1;    //     10
    UINT32 reg_pad_micom_04__ds0: 1;    //    11
    UINT32 reg_pad_micom_04__ds1: 1;    //    12
    UINT32 reg_pad_micom_04__ds2: 1;    //    13
    UINT32 reg_pad_micom_04__ds3: 1;    //    14
    UINT32 reg_pad_micom_04__pd: 1;    //     15
    UINT32 reg_pad_micom_04__pu: 1;    //     16
    UINT32 reg_pad_micom_04__st: 1;    //     17
    UINT32 reg_pad_micom_03__ds0: 1;    //    18
    UINT32 reg_pad_micom_03__ds1: 1;    //    19
    UINT32 reg_pad_micom_03__ds2: 1;    //    20
    UINT32 reg_pad_micom_03__ds3: 1;    //    21
    UINT32 reg_pad_micom_03__pd: 1;    //     22
    UINT32 reg_pad_micom_03__pu: 1;    //     23
    UINT32 reg_pad_micom_03__st: 1;    //     24
    UINT32 reg_pad_micom_02__ds0: 1;    //    25
    UINT32 reg_pad_micom_02__ds1: 1;    //    26
    UINT32 reg_pad_micom_02__ds2: 1;    //    27
    UINT32 reg_pad_micom_02__ds3: 1;    //    28
    UINT32 reg_pad_micom_02__pd: 1;    //     29
    UINT32 reg_pad_micom_02__pu: 1;    //     30
    UINT32 reg_pad_micom_02__st: 1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_301C    pad_woc07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_micom_09__ds0: 1;    //     4
    UINT32 reg_pad_micom_09__ds1: 1;    //     5
    UINT32 reg_pad_micom_09__ds2: 1;    //     6
    UINT32 reg_pad_micom_09__ds3: 1;    //     7
    UINT32 reg_pad_micom_09__pd: 1;    //      8
    UINT32 reg_pad_micom_09__pu: 1;    //      9
    UINT32 reg_pad_micom_09__st: 1;    //     10
    UINT32 reg_pad_micom_08__ds0: 1;    //    11
    UINT32 reg_pad_micom_08__ds1: 1;    //    12
    UINT32 reg_pad_micom_08__ds2: 1;    //    13
    UINT32 reg_pad_micom_08__ds3: 1;    //    14
    UINT32 reg_pad_micom_08__pd: 1;    //     15
    UINT32 reg_pad_micom_08__pu: 1;    //     16
    UINT32 reg_pad_micom_08__st: 1;    //     17
    UINT32 reg_pad_micom_07__ds0: 1;    //    18
    UINT32 reg_pad_micom_07__ds1: 1;    //    19
    UINT32 reg_pad_micom_07__ds2: 1;    //    20
    UINT32 reg_pad_micom_07__ds3: 1;    //    21
    UINT32 reg_pad_micom_07__pd: 1;    //     22
    UINT32 reg_pad_micom_07__pu: 1;    //     23
    UINT32 reg_pad_micom_07__st: 1;    //     24
    UINT32 reg_pad_micom_06__ds0: 1;    //    25
    UINT32 reg_pad_micom_06__ds1: 1;    //    26
    UINT32 reg_pad_micom_06__ds2: 1;    //    27
    UINT32 reg_pad_micom_06__ds3: 1;    //    28
    UINT32 reg_pad_micom_06__pd: 1;    //     29
    UINT32 reg_pad_micom_06__pu: 1;    //     30
    UINT32 reg_pad_micom_06__st: 1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3020    pad_woc08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_micom_13__ds0: 1;    //     4
    UINT32 reg_pad_micom_13__ds1: 1;    //     5
    UINT32 reg_pad_micom_13__ds2: 1;    //     6
    UINT32 reg_pad_micom_13__ds3: 1;    //     7
    UINT32 reg_pad_micom_13__pd: 1;    //      8
    UINT32 reg_pad_micom_13__pu: 1;    //      9
    UINT32 reg_pad_micom_13__st: 1;    //     10
    UINT32 reg_pad_micom_12__ds0: 1;    //    11
    UINT32 reg_pad_micom_12__ds1: 1;    //    12
    UINT32 reg_pad_micom_12__ds2: 1;    //    13
    UINT32 reg_pad_micom_12__ds3: 1;    //    14
    UINT32 reg_pad_micom_12__pd: 1;    //     15
    UINT32 reg_pad_micom_12__pu: 1;    //     16
    UINT32 reg_pad_micom_12__st: 1;    //     17
    UINT32 reg_pad_micom_11__ds0: 1;    //    18
    UINT32 reg_pad_micom_11__ds1: 1;    //    19
    UINT32 reg_pad_micom_11__ds2: 1;    //    20
    UINT32 reg_pad_micom_11__ds3: 1;    //    21
    UINT32 reg_pad_micom_11__pd: 1;    //     22
    UINT32 reg_pad_micom_11__pu: 1;    //     23
    UINT32 reg_pad_micom_11__st: 1;    //     24
    UINT32 reg_pad_micom_10__ds0: 1;    //    25
    UINT32 reg_pad_micom_10__ds1: 1;    //    26
    UINT32 reg_pad_micom_10__ds2: 1;    //    27
    UINT32 reg_pad_micom_10__ds3: 1;    //    28
    UINT32 reg_pad_micom_10__pd: 1;    //     29
    UINT32 reg_pad_micom_10__pu: 1;    //     30
    UINT32 reg_pad_micom_10__st: 1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC08_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3024    pad_woc09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_micom_17__ds0: 1;    //     4
    UINT32 reg_pad_micom_17__ds1: 1;    //     5
    UINT32 reg_pad_micom_17__ds2: 1;    //     6
    UINT32 reg_pad_micom_17__ds3: 1;    //     7
    UINT32 reg_pad_micom_17__pd: 1;    //      8
    UINT32 reg_pad_micom_17__pu: 1;    //      9
    UINT32 reg_pad_micom_17__st: 1;    //     10
    UINT32 reg_pad_micom_16__ds0: 1;    //    11
    UINT32 reg_pad_micom_16__ds1: 1;    //    12
    UINT32 reg_pad_micom_16__ds2: 1;    //    13
    UINT32 reg_pad_micom_16__ds3: 1;    //    14
    UINT32 reg_pad_micom_16__pd: 1;    //     15
    UINT32 reg_pad_micom_16__pu: 1;    //     16
    UINT32 reg_pad_micom_16__st: 1;    //     17
    UINT32 reg_pad_micom_15__ds0: 1;    //    18
    UINT32 reg_pad_micom_15__ds1: 1;    //    19
    UINT32 reg_pad_micom_15__ds2: 1;    //    20
    UINT32 reg_pad_micom_15__ds3: 1;    //    21
    UINT32 reg_pad_micom_15__pd: 1;    //     22
    UINT32 reg_pad_micom_15__pu: 1;    //     23
    UINT32 reg_pad_micom_15__st: 1;    //     24
    UINT32 reg_pad_micom_14__ds0: 1;    //    25
    UINT32 reg_pad_micom_14__ds1: 1;    //    26
    UINT32 reg_pad_micom_14__ds2: 1;    //    27
    UINT32 reg_pad_micom_14__ds3: 1;    //    28
    UINT32 reg_pad_micom_14__pd: 1;    //     29
    UINT32 reg_pad_micom_14__pu: 1;    //     30
    UINT32 reg_pad_micom_14__st: 1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC09_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3028    pad_woc10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_micom_21__ds0: 1;    //     4
    UINT32 reg_pad_micom_21__ds1: 1;    //     5
    UINT32 reg_pad_micom_21__ds2: 1;    //     6
    UINT32 reg_pad_micom_21__ds3: 1;    //     7
    UINT32 reg_pad_micom_21__pd: 1;    //      8
    UINT32 reg_pad_micom_21__pu: 1;    //      9
    UINT32 reg_pad_micom_21__st: 1;    //     10
    UINT32 reg_pad_micom_20__ds0: 1;    //    11
    UINT32 reg_pad_micom_20__ds1: 1;    //    12
    UINT32 reg_pad_micom_20__ds2: 1;    //    13
    UINT32 reg_pad_micom_20__ds3: 1;    //    14
    UINT32 reg_pad_micom_20__pd: 1;    //     15
    UINT32 reg_pad_micom_20__pu: 1;    //     16
    UINT32 reg_pad_micom_20__st: 1;    //     17
    UINT32 reg_pad_micom_19__ds0: 1;    //    18
    UINT32 reg_pad_micom_19__ds1: 1;    //    19
    UINT32 reg_pad_micom_19__ds2: 1;    //    20
    UINT32 reg_pad_micom_19__ds3: 1;    //    21
    UINT32 reg_pad_micom_19__pd: 1;    //     22
    UINT32 reg_pad_micom_19__pu: 1;    //     23
    UINT32 reg_pad_micom_19__st: 1;    //     24
    UINT32 reg_pad_micom_18__ds0: 1;    //    25
    UINT32 reg_pad_micom_18__ds1: 1;    //    26
    UINT32 reg_pad_micom_18__ds2: 1;    //    27
    UINT32 reg_pad_micom_18__ds3: 1;    //    28
    UINT32 reg_pad_micom_18__pd: 1;    //     29
    UINT32 reg_pad_micom_18__pu: 1;    //     30
    UINT32 reg_pad_micom_18__st: 1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_302C    pad_woc11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_micom_25__ds0: 1;    //     4
    UINT32 reg_pad_micom_25__ds1: 1;    //     5
    UINT32 reg_pad_micom_25__ds2: 1;    //     6
    UINT32 reg_pad_micom_25__ds3: 1;    //     7
    UINT32 reg_pad_micom_25__pd: 1;    //      8
    UINT32 reg_pad_micom_25__pu: 1;    //      9
    UINT32 reg_pad_micom_25__st: 1;    //     10
    UINT32 reg_pad_micom_24__ds0: 1;    //    11
    UINT32 reg_pad_micom_24__ds1: 1;    //    12
    UINT32 reg_pad_micom_24__ds2: 1;    //    13
    UINT32 reg_pad_micom_24__ds3: 1;    //    14
    UINT32 reg_pad_micom_24__pd: 1;    //     15
    UINT32 reg_pad_micom_24__pu: 1;    //     16
    UINT32 reg_pad_micom_24__st: 1;    //     17
    UINT32 reg_pad_micom_23__ds0: 1;    //    18
    UINT32 reg_pad_micom_23__ds1: 1;    //    19
    UINT32 reg_pad_micom_23__ds2: 1;    //    20
    UINT32 reg_pad_micom_23__ds3: 1;    //    21
    UINT32 reg_pad_micom_23__pd: 1;    //     22
    UINT32 reg_pad_micom_23__pu: 1;    //     23
    UINT32 reg_pad_micom_23__st: 1;    //     24
    UINT32 reg_pad_micom_22__ds0: 1;    //    25
    UINT32 reg_pad_micom_22__ds1: 1;    //    26
    UINT32 reg_pad_micom_22__ds2: 1;    //    27
    UINT32 reg_pad_micom_22__ds3: 1;    //    28
    UINT32 reg_pad_micom_22__pd: 1;    //     29
    UINT32 reg_pad_micom_22__pu: 1;    //     30
    UINT32 reg_pad_micom_22__st: 1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC11_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3030    pad_woc12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_micom_31__ds0: 1;    //     4
    UINT32 reg_pad_micom_31__ds1: 1;    //     5
    UINT32 reg_pad_micom_31__ds2: 1;    //     6
    UINT32 reg_pad_micom_31__ds3: 1;    //     7
    UINT32 reg_pad_micom_31__pd: 1;    //      8
    UINT32 reg_pad_micom_31__pu: 1;    //      9
    UINT32 reg_pad_micom_31__st: 1;    //     10
    UINT32 reg_pad_micom_30__ds0: 1;    //    11
    UINT32 reg_pad_micom_30__ds1: 1;    //    12
    UINT32 reg_pad_micom_30__ds2: 1;    //    13
    UINT32 reg_pad_micom_30__ds3: 1;    //    14
    UINT32 reg_pad_micom_30__pd: 1;    //     15
    UINT32 reg_pad_micom_30__pu: 1;    //     16
    UINT32 reg_pad_micom_30__st: 1;    //     17
    UINT32 reg_pad_micom_29__ds0: 1;    //    18
    UINT32 reg_pad_micom_29__ds1: 1;    //    19
    UINT32 reg_pad_micom_29__ds2: 1;    //    20
    UINT32 reg_pad_micom_29__ds3: 1;    //    21
    UINT32 reg_pad_micom_29__pd: 1;    //     22
    UINT32 reg_pad_micom_29__pu: 1;    //     23
    UINT32 reg_pad_micom_29__st: 1;    //     24
    UINT32 reg_pad_micom_28__ds0: 1;    //    25
    UINT32 reg_pad_micom_28__ds1: 1;    //    26
    UINT32 reg_pad_micom_28__ds2: 1;    //    27
    UINT32 reg_pad_micom_28__ds3: 1;    //    28
    UINT32 reg_pad_micom_28__pd: 1;    //     29
    UINT32 reg_pad_micom_28__pu: 1;    //     30
    UINT32 reg_pad_micom_28__st: 1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC12_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3034    pad_woc13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_pdm1_datain__ds0: 1;    //  4
    UINT32 reg_pad_pdm1_datain__ds1: 1;    //  5
    UINT32 reg_pad_pdm1_datain__ds2: 1;    //  6
    UINT32 reg_pad_pdm1_datain__ds3: 1;    //  7
    UINT32 reg_pad_pdm1_datain__pd: 1;    //   8
    UINT32 reg_pad_pdm1_datain__pu: 1;    //   9
    UINT32 reg_pad_pdm1_datain__st: 1;    //  10
    UINT32 reg_pad_pdm0_datain__ds0: 1;    //  11
    UINT32 reg_pad_pdm0_datain__ds1: 1;    //  12
    UINT32 reg_pad_pdm0_datain__ds2: 1;    //  13
    UINT32 reg_pad_pdm0_datain__ds3: 1;    //  14
    UINT32 reg_pad_pdm0_datain__pd: 1;    //  15
    UINT32 reg_pad_pdm0_datain__pu: 1;    //  16
    UINT32 reg_pad_pdm0_datain__st: 1;    //  17
    UINT32 reg_pad_pdm_clkout__ds0: 1;    //  18
    UINT32 reg_pad_pdm_clkout__ds1: 1;    //  19
    UINT32 reg_pad_pdm_clkout__ds2: 1;    //  20
    UINT32 reg_pad_pdm_clkout__ds3: 1;    //  21
    UINT32 reg_pad_pdm_clkout__pd: 1;    //   22
    UINT32 reg_pad_pdm_clkout__pu: 1;    //   23
    UINT32 reg_pad_pdm_clkout__st: 1;    //   24
    UINT32 reg_pad_micom_32__ds0: 1;    //    25
    UINT32 reg_pad_micom_32__ds1: 1;    //    26
    UINT32 reg_pad_micom_32__ds2: 1;    //    27
    UINT32 reg_pad_micom_32__ds3: 1;    //    28
    UINT32 reg_pad_micom_32__pd: 1;    //     29
    UINT32 reg_pad_micom_32__pu: 1;    //     30
    UINT32 reg_pad_micom_32__st: 1;    //     31
    };
}IOMUX_CTRL_WOC_PAD_WOC13_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3038    pad_woc14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  7;    //   6: 0 reserved
    UINT32 reg_pad_m0_ret_ctrl__ds0: 1;    //  7
    UINT32 reg_pad_m0_ret_ctrl__ds1: 1;    //  8
    UINT32 reg_pad_m0_ret_ctrl__ds2: 1;    //  9
    UINT32 reg_pad_m0_ret_ctrl__ds3: 1;    //  10
    UINT32 reg_pad_m0_ret_ctrl__pd: 1;    //  11
    UINT32 reg_pad_m0_ret_ctrl__pu: 1;    //  12
    UINT32 reg_pad_m0_ret_ctrl__st: 1;    //  13
    UINT32 reg_pad_hdmi_cec__ds0: 1;    //    14
    UINT32 reg_pad_hdmi_cec__ds1: 1;    //    15
    UINT32 reg_pad_hdmi_cec__ds2: 1;    //    16
    UINT32 reg_pad_hdmi_cec__pd: 1;    //     17
    UINT32 reg_pad_hdmi_cec__pu: 1;    //     18
    UINT32 reg_pad_hdmi_cec__smt: 1;    //    19
    UINT32 reg_pad_uart0_tx__ds0: 1;    //    20
    UINT32 reg_pad_uart0_tx__ds1: 1;    //    21
    UINT32 reg_pad_uart0_tx__ds2: 1;    //    22
    UINT32 reg_pad_uart0_tx__pd: 1;    //     23
    UINT32 reg_pad_uart0_tx__pu: 1;    //     24
    UINT32 reg_pad_uart0_tx__smt: 1;    //    25
    UINT32 reg_pad_uart0_rx__ds0: 1;    //    26
    UINT32 reg_pad_uart0_rx__ds1: 1;    //    27
    UINT32 reg_pad_uart0_rx__ds2: 1;    //    28
    UINT32 reg_pad_uart0_rx__pd: 1;    //     29
    UINT32 reg_pad_uart0_rx__pu: 1;    //     30
    UINT32 reg_pad_uart0_rx__smt: 1;    //    31
    };
}IOMUX_CTRL_WOC_PAD_WOC14_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_303C    pad_woc15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  6;    //   5: 0 reserved
    UINT32 reg_pad_xin__ds0   :  1;    //      6
    UINT32 reg_pad_xin__ds1   :  1;    //      7
    UINT32 reg_pad_xin__ds2   :  1;    //      8
    UINT32 reg_pad_xin__ds3   :  1;    //      9
    UINT32 reg_pad_xin__rd1   :  1;    //     10
    UINT32 reg_pad_xin__rd0   :  1;    //     11
    UINT32 reg_pad_xin__ref1  :  1;    //     12
    UINT32 reg_pad_xin__ref0  :  1;    //     13
    UINT32 reg_pad_opm__ds0   :  1;    //     14
    UINT32 reg_pad_opm__ds1   :  1;    //     15
    UINT32 reg_pad_opm__ds2   :  1;    //     16
    UINT32 reg_pad_opm__ds3   :  1;    //     17
    UINT32 reg_pad_opm__st    :  1;    //     18
    UINT32 reg_pad_pores_n__ds0: 1;    //     19
    UINT32 reg_pad_pores_n__ds1: 1;    //     20
    UINT32 reg_pad_pores_n__ds2: 1;    //     21
    UINT32 reg_pad_pores_n__ds3: 1;    //     22
    UINT32 reg_pad_pores_n__st:  1;    //     23
    UINT32 resvd01            :  8;    //  31:24 reserved
    };
}IOMUX_CTRL_WOC_PAD_WOC15_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3100    pad_woc64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_daclrch_mux_sel: 4;    //  3:0
    UINT32 reg_pad_dacclfch_mux_sel: 4;    //  7:4
    UINT32 reg_pad_pcmi3sck_mux_sel: 4;    //  11:8
    UINT32 reg_pad_pcmi3lrck_mux_sel: 4;    //  15:12
    UINT32 reg_pad_aec_lrch3_mux_sel: 4;    //  19:16
    UINT32 reg_pad_aec_lrch2_mux_sel: 4;    //  23:20
    UINT32 reg_pad_aec_lrch1_mux_sel: 4;    //  27:24
    UINT32 reg_pad_aec_lrch0_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_WOC_PAD_WOC64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3104    pad_woc65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_diseqc_mux_sel: 4;    //  3:0
    UINT32 reg_pad_pwm2_mux_sel: 4;    //   7: 4
    UINT32 reg_pad_pwm1_mux_sel: 4;    //  11: 8
    UINT32 reg_pad_pwm0_mux_sel: 4;    //  15:12
    UINT32 reg_pad_pwm_in_mux_sel: 4;    //  19:16
    UINT32 reg_pad_dacslrch_mux_sel: 4;    //  23:20
    UINT32 reg_pad_dacsck_mux_sel: 4;    //  27:24
    UINT32 reg_pad_daclrck_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_WOC_PAD_WOC65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3108    pad_woc66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_01_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_00_mux_sel: 4;    //  7:4
    UINT32 reg_pad_ifagc_s_mux_sel: 4;    //  11:8
    UINT32 reg_pad_ifagc_mux_sel: 4;    //  15:12
    UINT32 reg_pad_iec958out_mux_sel: 4;    //  19:16
    UINT32 reg_pad_fefctrl_mux_sel: 4;    //  23:20
    UINT32 reg_pad_diseqci_mux_sel: 4;    //  27:24
    UINT32 reg_pad_diseqc_cmd_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_WOC_PAD_WOC66_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_310C    pad_woc67 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_09_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_08_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_07_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_06_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_05_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_04_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_03_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_02_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_WOC_PAD_WOC67_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3110    pad_woc68 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_17_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_16_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_15_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_14_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_13_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_12_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_11_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_10_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_WOC_PAD_WOC68_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3114    pad_woc69 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_micom_25_mux_sel: 4;    //  3:0
    UINT32 reg_pad_micom_24_mux_sel: 4;    //  7:4
    UINT32 reg_pad_micom_23_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_22_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_21_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_20_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_19_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_18_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_WOC_PAD_WOC69_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_3118    pad_woc70 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pdm1_datain_mux_sel: 4;    //  3:0
    UINT32 reg_pad_pdm0_datain_mux_sel: 4;    //  7:4
    UINT32 reg_pad_pdm_clkout_mux_sel: 4;    //  11:8
    UINT32 reg_pad_micom_32_mux_sel: 4;    //  15:12
    UINT32 reg_pad_micom_31_mux_sel: 4;    //  19:16
    UINT32 reg_pad_micom_30_mux_sel: 4;    //  23:20
    UINT32 reg_pad_micom_29_mux_sel: 4;    //  27:24
    UINT32 reg_pad_micom_28_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_WOC_PAD_WOC70_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_311C    pad_woc71 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_opm_mux_sel:  4;    //   7: 4
    UINT32 reg_pad_pores_n_mux_sel: 4;    //  11:8
    UINT32 reg_pad_m0_ret_ctrl_mux_sel: 4;    //  15:12
    UINT32 reg_pad_hdmi_cec_mux_sel: 4;    //  19:16
    UINT32 reg_pad_uart0_tx_mux_sel: 4;    //  23:20
    UINT32 reg_pad_uart0_rx_mux_sel: 4;    //  27:24
    UINT32 resvd01            :  4;    //  31:28 reserved
    };
}IOMUX_CTRL_WOC_PAD_WOC71_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_WOC_PAD_WOC00_O26A0_T    pad_woc00 ;             // 0xCA3A_3000
    IOMUX_CTRL_WOC_PAD_WOC01_O26A0_T    pad_woc01 ;             // 0xCA3A_3004
    IOMUX_CTRL_WOC_PAD_WOC02_O26A0_T    pad_woc02 ;             // 0xCA3A_3008
    IOMUX_CTRL_WOC_PAD_WOC03_O26A0_T    pad_woc03 ;             // 0xCA3A_300C
    IOMUX_CTRL_WOC_PAD_WOC04_O26A0_T    pad_woc04 ;             // 0xCA3A_3010
    IOMUX_CTRL_WOC_PAD_WOC05_O26A0_T    pad_woc05 ;             // 0xCA3A_3014
    IOMUX_CTRL_WOC_PAD_WOC06_O26A0_T    pad_woc06 ;             // 0xCA3A_3018
    IOMUX_CTRL_WOC_PAD_WOC07_O26A0_T    pad_woc07 ;             // 0xCA3A_301C
    IOMUX_CTRL_WOC_PAD_WOC08_O26A0_T    pad_woc08 ;             // 0xCA3A_3020
    IOMUX_CTRL_WOC_PAD_WOC09_O26A0_T    pad_woc09 ;             // 0xCA3A_3024
    IOMUX_CTRL_WOC_PAD_WOC10_O26A0_T    pad_woc10 ;             // 0xCA3A_3028
    IOMUX_CTRL_WOC_PAD_WOC11_O26A0_T    pad_woc11 ;             // 0xCA3A_302C
    IOMUX_CTRL_WOC_PAD_WOC12_O26A0_T    pad_woc12 ;             // 0xCA3A_3030
    IOMUX_CTRL_WOC_PAD_WOC13_O26A0_T    pad_woc13 ;             // 0xCA3A_3034
    IOMUX_CTRL_WOC_PAD_WOC14_O26A0_T    pad_woc14 ;             // 0xCA3A_3038
    IOMUX_CTRL_WOC_PAD_WOC15_O26A0_T    pad_woc15 ;             // 0xCA3A_303C
    UINT32                             _rsvd_00[48];            // 0xCA3A_3040 ~ 0xCA3A_30FC
    IOMUX_CTRL_WOC_PAD_WOC64_O26A0_T    pad_woc64 ;             // 0xCA3A_3100
    IOMUX_CTRL_WOC_PAD_WOC65_O26A0_T    pad_woc65 ;             // 0xCA3A_3104
    IOMUX_CTRL_WOC_PAD_WOC66_O26A0_T    pad_woc66 ;             // 0xCA3A_3108
    IOMUX_CTRL_WOC_PAD_WOC67_O26A0_T    pad_woc67 ;             // 0xCA3A_310C
    IOMUX_CTRL_WOC_PAD_WOC68_O26A0_T    pad_woc68 ;             // 0xCA3A_3110
    IOMUX_CTRL_WOC_PAD_WOC69_O26A0_T    pad_woc69 ;             // 0xCA3A_3114
    IOMUX_CTRL_WOC_PAD_WOC70_O26A0_T    pad_woc70 ;             // 0xCA3A_3118
    IOMUX_CTRL_WOC_PAD_WOC71_O26A0_T    pad_woc71 ;             // 0xCA3A_311C
}IOMUX_CTRL_WOC_REG_O26A0_T;
/* 24 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IOMUX_CTRL_WOC_REG_H_

/* from 'O26_CTOP_PAD_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

