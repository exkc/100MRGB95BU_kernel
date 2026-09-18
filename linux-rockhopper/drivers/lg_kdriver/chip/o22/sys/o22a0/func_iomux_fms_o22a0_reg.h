#ifndef _FUNC_IOMUX_FMS_REG_H_
#define _FUNC_IOMUX_FMS_REG_H_

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
    0xCC37_2000    pad_fms00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_aec_lrch2__ds0    :  1,    //      0
    reg_pad_aec_lrch2__ds1    :  1,    //      1
    reg_pad_aec_lrch2__ds2    :  1,    //      2
    reg_pad_aec_lrch2__ds3    :  1,    //      3
    reg_pad_aec_lrch2__pd     :  1,    //      4
    reg_pad_aec_lrch2__pu     :  1,    //      5
    reg_pad_aec_lrch2__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_aec_lrch1__ds0    :  1,    //      8
    reg_pad_aec_lrch1__ds1    :  1,    //      9
    reg_pad_aec_lrch1__ds2    :  1,    //     10
    reg_pad_aec_lrch1__ds3    :  1,    //     11
    reg_pad_aec_lrch1__pd     :  1,    //     12
    reg_pad_aec_lrch1__pu     :  1,    //     13
    reg_pad_aec_lrch1__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_aec_lrch0__ds0    :  1,    //     16
    reg_pad_aec_lrch0__ds1    :  1,    //     17
    reg_pad_aec_lrch0__ds2    :  1,    //     18
    reg_pad_aec_lrch0__ds3    :  1,    //     19
    reg_pad_aec_lrch0__pd     :  1,    //     20
    reg_pad_aec_lrch0__pu     :  1,    //     21
    reg_pad_aec_lrch0__st     :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_iec958out__ds0    :  1,    //     24
    reg_pad_iec958out__ds1    :  1,    //     25
    reg_pad_iec958out__ds2    :  1,    //     26
    reg_pad_iec958out__ds3    :  1,    //     27
    reg_pad_iec958out__pd     :  1,    //     28
    reg_pad_iec958out__pu     :  1,    //     29
    reg_pad_iec958out__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_FMS_PAD_FMS00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2004    pad_fms01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pcmi3lrch__ds0    :  1,    //      0
    reg_pad_pcmi3lrch__ds1    :  1,    //      1
    reg_pad_pcmi3lrch__ds2    :  1,    //      2
    reg_pad_pcmi3lrch__ds3    :  1,    //      3
    reg_pad_pcmi3lrch__pd     :  1,    //      4
    reg_pad_pcmi3lrch__pu     :  1,    //      5
    reg_pad_pcmi3lrch__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_dacclfch__ds0     :  1,    //      8
    reg_pad_dacclfch__ds1     :  1,    //      9
    reg_pad_dacclfch__ds2     :  1,    //     10
    reg_pad_dacclfch__ds3     :  1,    //     11
    reg_pad_dacclfch__pd      :  1,    //     12
    reg_pad_dacclfch__pu      :  1,    //     13
    reg_pad_dacclfch__st      :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_dacslrch__ds0     :  1,    //     16
    reg_pad_dacslrch__ds1     :  1,    //     17
    reg_pad_dacslrch__ds2     :  1,    //     18
    reg_pad_dacslrch__ds3     :  1,    //     19
    reg_pad_dacslrch__pd      :  1,    //     20
    reg_pad_dacslrch__pu      :  1,    //     21
    reg_pad_dacslrch__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_aec_lrch3__ds0    :  1,    //     24
    reg_pad_aec_lrch3__ds1    :  1,    //     25
    reg_pad_aec_lrch3__ds2    :  1,    //     26
    reg_pad_aec_lrch3__ds3    :  1,    //     27
    reg_pad_aec_lrch3__pd     :  1,    //     28
    reg_pad_aec_lrch3__pu     :  1,    //     29
    reg_pad_aec_lrch3__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_FMS_PAD_FMS01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2008    pad_fms02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pwm0__ds0         :  1,    //      0
    reg_pad_pwm0__ds1         :  1,    //      1
    reg_pad_pwm0__ds2         :  1,    //      2
    reg_pad_pwm0__ds3         :  1,    //      3
    reg_pad_pwm0__pd          :  1,    //      4
    reg_pad_pwm0__pu          :  1,    //      5
    reg_pad_pwm0__st          :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_pwm_in__ds0       :  1,    //      8
    reg_pad_pwm_in__ds1       :  1,    //      9
    reg_pad_pwm_in__ds2       :  1,    //     10
    reg_pad_pwm_in__ds3       :  1,    //     11
    reg_pad_pwm_in__pd        :  1,    //     12
    reg_pad_pwm_in__pu        :  1,    //     13
    reg_pad_pwm_in__st        :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_pcmi3sck__ds0     :  1,    //     16
    reg_pad_pcmi3sck__ds1     :  1,    //     17
    reg_pad_pcmi3sck__ds2     :  1,    //     18
    reg_pad_pcmi3sck__ds3     :  1,    //     19
    reg_pad_pcmi3sck__pd      :  1,    //     20
    reg_pad_pcmi3sck__pu      :  1,    //     21
    reg_pad_pcmi3sck__st      :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_pcmi3lrck__ds0    :  1,    //     24
    reg_pad_pcmi3lrck__ds1    :  1,    //     25
    reg_pad_pcmi3lrck__ds2    :  1,    //     26
    reg_pad_pcmi3lrck__ds3    :  1,    //     27
    reg_pad_pcmi3lrck__pd     :  1,    //     28
    reg_pad_pcmi3lrck__pu     :  1,    //     29
    reg_pad_pcmi3lrck__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_FMS_PAD_FMS02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_200C    pad_fms03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim0_mosi__ds0    :  1,    //      0
    reg_pad_dim0_mosi__ds1    :  1,    //      1
    reg_pad_dim0_mosi__ds2    :  1,    //      2
    reg_pad_dim0_mosi__ds3    :  1,    //      3
    reg_pad_dim0_mosi__pd     :  1,    //      4
    reg_pad_dim0_mosi__pu     :  1,    //      5
    reg_pad_dim0_mosi__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ld_vs_out0__ds0   :  1,    //      8
    reg_pad_ld_vs_out0__ds1   :  1,    //      9
    reg_pad_ld_vs_out0__ds2   :  1,    //     10
    reg_pad_ld_vs_out0__ds3   :  1,    //     11
    reg_pad_ld_vs_out0__pd    :  1,    //     12
    reg_pad_ld_vs_out0__pu    :  1,    //     13
    reg_pad_ld_vs_out0__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_pwm2__ds0         :  1,    //     16
    reg_pad_pwm2__ds1         :  1,    //     17
    reg_pad_pwm2__ds2         :  1,    //     18
    reg_pad_pwm2__ds3         :  1,    //     19
    reg_pad_pwm2__pd          :  1,    //     20
    reg_pad_pwm2__pu          :  1,    //     21
    reg_pad_pwm2__st          :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_pwm1__ds0         :  1,    //     24
    reg_pad_pwm1__ds1         :  1,    //     25
    reg_pad_pwm1__ds2         :  1,    //     26
    reg_pad_pwm1__ds3         :  1,    //     27
    reg_pad_pwm1__pd          :  1,    //     28
    reg_pad_pwm1__pu          :  1,    //     29
    reg_pad_pwm1__st          :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_FMS_PAD_FMS03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2010    pad_fms04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim1_sclk__ds0    :  1,    //      0
    reg_pad_dim1_sclk__ds1    :  1,    //      1
    reg_pad_dim1_sclk__ds2    :  1,    //      2
    reg_pad_dim1_sclk__ds3    :  1,    //      3
    reg_pad_dim1_sclk__pd     :  1,    //      4
    reg_pad_dim1_sclk__pu     :  1,    //      5
    reg_pad_dim1_sclk__st     :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_dim1_mosi__ds0    :  1,    //      8
    reg_pad_dim1_mosi__ds1    :  1,    //      9
    reg_pad_dim1_mosi__ds2    :  1,    //     10
    reg_pad_dim1_mosi__ds3    :  1,    //     11
    reg_pad_dim1_mosi__pd     :  1,    //     12
    reg_pad_dim1_mosi__pu     :  1,    //     13
    reg_pad_dim1_mosi__st     :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_ld_vs_out1__ds0   :  1,    //     16
    reg_pad_ld_vs_out1__ds1   :  1,    //     17
    reg_pad_ld_vs_out1__ds2   :  1,    //     18
    reg_pad_ld_vs_out1__ds3   :  1,    //     19
    reg_pad_ld_vs_out1__pd    :  1,    //     20
    reg_pad_ld_vs_out1__pu    :  1,    //     21
    reg_pad_ld_vs_out1__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_dim0_sclk__ds0    :  1,    //     24
    reg_pad_dim0_sclk__ds1    :  1,    //     25
    reg_pad_dim0_sclk__ds2    :  1,    //     26
    reg_pad_dim0_sclk__ds3    :  1,    //     27
    reg_pad_dim0_sclk__pd     :  1,    //     28
    reg_pad_dim0_sclk__pu     :  1,    //     29
    reg_pad_dim0_sclk__st     :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_FMS_PAD_FMS04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2014    pad_fms05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_pad_pqe_ip_enb__ds0   :  1,    //      1
    reg_pad_pqe_ip_enb__ds1   :  1,    //      2
    reg_pad_pqe_ip_enb__ds2   :  1,    //      3
    reg_pad_pqe_ip_enb__ds3   :  1,    //      4
    reg_pad_pqe_ip_enb__pu    :  1,    //      5
    reg_pad_pqe_ip_enb__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_ld_vs_out2__ds0   :  1,    //      8
    reg_pad_ld_vs_out2__ds1   :  1,    //      9
    reg_pad_ld_vs_out2__ds2   :  1,    //     10
    reg_pad_ld_vs_out2__ds3   :  1,    //     11
    reg_pad_ld_vs_out2__pd    :  1,    //     12
    reg_pad_ld_vs_out2__pu    :  1,    //     13
    reg_pad_ld_vs_out2__st    :  1,    //     14
                              : 17;    //  31:15 reserved
}FUNC_IOMUX_FMS_PAD_FMS05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2100    pad_fms64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pcmi3lrch_mux_sel :  4,    //   3: 0
    reg_pad_dacclfch_mux_sel  :  4,    //   7: 4
    reg_pad_dacslrch_mux_sel  :  4,    //  11: 8
    reg_pad_aec_lrch3_mux_sel :  4,    //  15:12
    reg_pad_aec_lrch2_mux_sel :  4,    //  19:16
    reg_pad_aec_lrch1_mux_sel :  4,    //  23:20
    reg_pad_aec_lrch0_mux_sel :  4,    //  27:24
    reg_pad_iec958out_mux_sel :  4;    //  31:28
}FUNC_IOMUX_FMS_PAD_FMS64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2104    pad_fms65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_dim0_mosi_mux_sel :  4,    //   3: 0
    reg_pad_ld_vs_out0_mux_sel:  4,    //   7: 4
    reg_pad_pwm2_mux_sel      :  4,    //  11: 8
    reg_pad_pwm1_mux_sel      :  4,    //  15:12
    reg_pad_pwm0_mux_sel      :  4,    //  19:16
    reg_pad_pwm_in_mux_sel    :  4,    //  23:20
    reg_pad_pcmi3sck_mux_sel  :  4,    //  27:24
    reg_pad_pcmi3lrck_mux_sel :  4;    //  31:28
}FUNC_IOMUX_FMS_PAD_FMS65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2108    pad_fms66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_pqe_ip_enb_mux_sel:  4,    //   3: 0
    reg_pad_ld_vs_out2_mux_sel:  4,    //   7: 4
    reg_pad_dim1_sclk_mux_sel :  4,    //  11: 8
    reg_pad_dim1_mosi_mux_sel :  4,    //  15:12
    reg_pad_ld_vs_out1_mux_sel:  4,    //  19:16
    reg_pad_dim0_sclk_mux_sel :  4,    //  23:20
                              :  8;    //  31:24 reserved
}FUNC_IOMUX_FMS_PAD_FMS66_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_FMS_PAD_FMS00_O22A0_T          pad_fms00  ;             // 0xCC37_2000
    FUNC_IOMUX_FMS_PAD_FMS01_O22A0_T          pad_fms01  ;             // 0xCC37_2004
    FUNC_IOMUX_FMS_PAD_FMS02_O22A0_T          pad_fms02  ;             // 0xCC37_2008
    FUNC_IOMUX_FMS_PAD_FMS03_O22A0_T          pad_fms03  ;             // 0xCC37_200C
    FUNC_IOMUX_FMS_PAD_FMS04_O22A0_T          pad_fms04  ;             // 0xCC37_2010
    FUNC_IOMUX_FMS_PAD_FMS05_O22A0_T          pad_fms05  ;             // 0xCC37_2014
    UINT32                             _rsvd_00[58];            // 0xCC37_2018 ~ 0xCC37_20FC
    FUNC_IOMUX_FMS_PAD_FMS64_O22A0_T          pad_fms64  ;             // 0xCC37_2100
    FUNC_IOMUX_FMS_PAD_FMS65_O22A0_T          pad_fms65  ;             // 0xCC37_2104
    FUNC_IOMUX_FMS_PAD_FMS66_O22A0_T          pad_fms66  ;             // 0xCC37_2108
}FUNC_IOMUX_FMS_REG_O22A0_T;
/* 9 regs */

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

#define FUNC_IOMUX_FMS_PAD_FMS00_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define FUNC_IOMUX_FMS_PAD_FMS01_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define FUNC_IOMUX_FMS_PAD_FMS02_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define FUNC_IOMUX_FMS_PAD_FMS03_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define FUNC_IOMUX_FMS_PAD_FMS04_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define FUNC_IOMUX_FMS_PAD_FMS05_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define FUNC_IOMUX_FMS_PAD_FMS64_O22A0_T_OFF                       (BASEADDRESS+0x0100)
#define FUNC_IOMUX_FMS_PAD_FMS65_O22A0_T_OFF                       (BASEADDRESS+0x0104)
#define FUNC_IOMUX_FMS_PAD_FMS66_O22A0_T_OFF                       (BASEADDRESS+0x0108)

/*-----------------------------------------------------------------------------------------
    0xCC37_2000    pad_fms00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_aec_lrch2__ds0: 1;    //    0
    UINT32 reg_pad_aec_lrch2__ds1: 1;    //    1
    UINT32 reg_pad_aec_lrch2__ds2: 1;    //    2
    UINT32 reg_pad_aec_lrch2__ds3: 1;    //    3
    UINT32 reg_pad_aec_lrch2__pd: 1;    //     4
    UINT32 reg_pad_aec_lrch2__pu: 1;    //     5
    UINT32 reg_pad_aec_lrch2__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_aec_lrch1__ds0: 1;    //    8
    UINT32 reg_pad_aec_lrch1__ds1: 1;    //    9
    UINT32 reg_pad_aec_lrch1__ds2: 1;    //   10
    UINT32 reg_pad_aec_lrch1__ds3: 1;    //   11
    UINT32 reg_pad_aec_lrch1__pd: 1;    //    12
    UINT32 reg_pad_aec_lrch1__pu: 1;    //    13
    UINT32 reg_pad_aec_lrch1__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_aec_lrch0__ds0: 1;    //   16
    UINT32 reg_pad_aec_lrch0__ds1: 1;    //   17
    UINT32 reg_pad_aec_lrch0__ds2: 1;    //   18
    UINT32 reg_pad_aec_lrch0__ds3: 1;    //   19
    UINT32 reg_pad_aec_lrch0__pd: 1;    //    20
    UINT32 reg_pad_aec_lrch0__pu: 1;    //    21
    UINT32 reg_pad_aec_lrch0__st: 1;    //    22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_iec958out__ds0: 1;    //   24
    UINT32 reg_pad_iec958out__ds1: 1;    //   25
    UINT32 reg_pad_iec958out__ds2: 1;    //   26
    UINT32 reg_pad_iec958out__ds3: 1;    //   27
    UINT32 reg_pad_iec958out__pd: 1;    //    28
    UINT32 reg_pad_iec958out__pu: 1;    //    29
    UINT32 reg_pad_iec958out__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_FMS_PAD_FMS00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2004    pad_fms01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pcmi3lrch__ds0: 1;    //    0
    UINT32 reg_pad_pcmi3lrch__ds1: 1;    //    1
    UINT32 reg_pad_pcmi3lrch__ds2: 1;    //    2
    UINT32 reg_pad_pcmi3lrch__ds3: 1;    //    3
    UINT32 reg_pad_pcmi3lrch__pd: 1;    //     4
    UINT32 reg_pad_pcmi3lrch__pu: 1;    //     5
    UINT32 reg_pad_pcmi3lrch__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_dacclfch__ds0: 1;    //     8
    UINT32 reg_pad_dacclfch__ds1: 1;    //     9
    UINT32 reg_pad_dacclfch__ds2: 1;    //    10
    UINT32 reg_pad_dacclfch__ds3: 1;    //    11
    UINT32 reg_pad_dacclfch__pd: 1;    //     12
    UINT32 reg_pad_dacclfch__pu: 1;    //     13
    UINT32 reg_pad_dacclfch__st: 1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_dacslrch__ds0: 1;    //    16
    UINT32 reg_pad_dacslrch__ds1: 1;    //    17
    UINT32 reg_pad_dacslrch__ds2: 1;    //    18
    UINT32 reg_pad_dacslrch__ds3: 1;    //    19
    UINT32 reg_pad_dacslrch__pd: 1;    //     20
    UINT32 reg_pad_dacslrch__pu: 1;    //     21
    UINT32 reg_pad_dacslrch__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_aec_lrch3__ds0: 1;    //   24
    UINT32 reg_pad_aec_lrch3__ds1: 1;    //   25
    UINT32 reg_pad_aec_lrch3__ds2: 1;    //   26
    UINT32 reg_pad_aec_lrch3__ds3: 1;    //   27
    UINT32 reg_pad_aec_lrch3__pd: 1;    //    28
    UINT32 reg_pad_aec_lrch3__pu: 1;    //    29
    UINT32 reg_pad_aec_lrch3__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_FMS_PAD_FMS01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2008    pad_fms02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pwm0__ds0  :  1;    //      0
    UINT32 reg_pad_pwm0__ds1  :  1;    //      1
    UINT32 reg_pad_pwm0__ds2  :  1;    //      2
    UINT32 reg_pad_pwm0__ds3  :  1;    //      3
    UINT32 reg_pad_pwm0__pd   :  1;    //      4
    UINT32 reg_pad_pwm0__pu   :  1;    //      5
    UINT32 reg_pad_pwm0__st   :  1;    //      6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_pwm_in__ds0:  1;    //      8
    UINT32 reg_pad_pwm_in__ds1:  1;    //      9
    UINT32 reg_pad_pwm_in__ds2:  1;    //     10
    UINT32 reg_pad_pwm_in__ds3:  1;    //     11
    UINT32 reg_pad_pwm_in__pd :  1;    //     12
    UINT32 reg_pad_pwm_in__pu :  1;    //     13
    UINT32 reg_pad_pwm_in__st :  1;    //     14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_pcmi3sck__ds0: 1;    //    16
    UINT32 reg_pad_pcmi3sck__ds1: 1;    //    17
    UINT32 reg_pad_pcmi3sck__ds2: 1;    //    18
    UINT32 reg_pad_pcmi3sck__ds3: 1;    //    19
    UINT32 reg_pad_pcmi3sck__pd: 1;    //     20
    UINT32 reg_pad_pcmi3sck__pu: 1;    //     21
    UINT32 reg_pad_pcmi3sck__st: 1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_pcmi3lrck__ds0: 1;    //   24
    UINT32 reg_pad_pcmi3lrck__ds1: 1;    //   25
    UINT32 reg_pad_pcmi3lrck__ds2: 1;    //   26
    UINT32 reg_pad_pcmi3lrck__ds3: 1;    //   27
    UINT32 reg_pad_pcmi3lrck__pd: 1;    //    28
    UINT32 reg_pad_pcmi3lrck__pu: 1;    //    29
    UINT32 reg_pad_pcmi3lrck__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_FMS_PAD_FMS02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_200C    pad_fms03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dim0_mosi__ds0: 1;    //    0
    UINT32 reg_pad_dim0_mosi__ds1: 1;    //    1
    UINT32 reg_pad_dim0_mosi__ds2: 1;    //    2
    UINT32 reg_pad_dim0_mosi__ds3: 1;    //    3
    UINT32 reg_pad_dim0_mosi__pd: 1;    //     4
    UINT32 reg_pad_dim0_mosi__pu: 1;    //     5
    UINT32 reg_pad_dim0_mosi__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_ld_vs_out0__ds0: 1;    //   8
    UINT32 reg_pad_ld_vs_out0__ds1: 1;    //   9
    UINT32 reg_pad_ld_vs_out0__ds2: 1;    //  10
    UINT32 reg_pad_ld_vs_out0__ds3: 1;    //  11
    UINT32 reg_pad_ld_vs_out0__pd: 1;    //   12
    UINT32 reg_pad_ld_vs_out0__pu: 1;    //   13
    UINT32 reg_pad_ld_vs_out0__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_pwm2__ds0  :  1;    //     16
    UINT32 reg_pad_pwm2__ds1  :  1;    //     17
    UINT32 reg_pad_pwm2__ds2  :  1;    //     18
    UINT32 reg_pad_pwm2__ds3  :  1;    //     19
    UINT32 reg_pad_pwm2__pd   :  1;    //     20
    UINT32 reg_pad_pwm2__pu   :  1;    //     21
    UINT32 reg_pad_pwm2__st   :  1;    //     22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_pwm1__ds0  :  1;    //     24
    UINT32 reg_pad_pwm1__ds1  :  1;    //     25
    UINT32 reg_pad_pwm1__ds2  :  1;    //     26
    UINT32 reg_pad_pwm1__ds3  :  1;    //     27
    UINT32 reg_pad_pwm1__pd   :  1;    //     28
    UINT32 reg_pad_pwm1__pu   :  1;    //     29
    UINT32 reg_pad_pwm1__st   :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_FMS_PAD_FMS03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2010    pad_fms04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dim1_sclk__ds0: 1;    //    0
    UINT32 reg_pad_dim1_sclk__ds1: 1;    //    1
    UINT32 reg_pad_dim1_sclk__ds2: 1;    //    2
    UINT32 reg_pad_dim1_sclk__ds3: 1;    //    3
    UINT32 reg_pad_dim1_sclk__pd: 1;    //     4
    UINT32 reg_pad_dim1_sclk__pu: 1;    //     5
    UINT32 reg_pad_dim1_sclk__st: 1;    //     6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_dim1_mosi__ds0: 1;    //    8
    UINT32 reg_pad_dim1_mosi__ds1: 1;    //    9
    UINT32 reg_pad_dim1_mosi__ds2: 1;    //   10
    UINT32 reg_pad_dim1_mosi__ds3: 1;    //   11
    UINT32 reg_pad_dim1_mosi__pd: 1;    //    12
    UINT32 reg_pad_dim1_mosi__pu: 1;    //    13
    UINT32 reg_pad_dim1_mosi__st: 1;    //    14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_ld_vs_out1__ds0: 1;    //  16
    UINT32 reg_pad_ld_vs_out1__ds1: 1;    //  17
    UINT32 reg_pad_ld_vs_out1__ds2: 1;    //  18
    UINT32 reg_pad_ld_vs_out1__ds3: 1;    //  19
    UINT32 reg_pad_ld_vs_out1__pd: 1;    //   20
    UINT32 reg_pad_ld_vs_out1__pu: 1;    //   21
    UINT32 reg_pad_ld_vs_out1__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_dim0_sclk__ds0: 1;    //   24
    UINT32 reg_pad_dim0_sclk__ds1: 1;    //   25
    UINT32 reg_pad_dim0_sclk__ds2: 1;    //   26
    UINT32 reg_pad_dim0_sclk__ds3: 1;    //   27
    UINT32 reg_pad_dim0_sclk__pd: 1;    //    28
    UINT32 reg_pad_dim0_sclk__pu: 1;    //    29
    UINT32 reg_pad_dim0_sclk__st: 1;    //    30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_FMS_PAD_FMS04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2014    pad_fms05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_pad_pqe_ip_enb__ds0: 1;    //   1
    UINT32 reg_pad_pqe_ip_enb__ds1: 1;    //   2
    UINT32 reg_pad_pqe_ip_enb__ds2: 1;    //   3
    UINT32 reg_pad_pqe_ip_enb__ds3: 1;    //   4
    UINT32 reg_pad_pqe_ip_enb__pu: 1;    //    5
    UINT32 reg_pad_pqe_ip_enb__st: 1;    //    6
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_pad_ld_vs_out2__ds0: 1;    //   8
    UINT32 reg_pad_ld_vs_out2__ds1: 1;    //   9
    UINT32 reg_pad_ld_vs_out2__ds2: 1;    //  10
    UINT32 reg_pad_ld_vs_out2__ds3: 1;    //  11
    UINT32 reg_pad_ld_vs_out2__pd: 1;    //   12
    UINT32 reg_pad_ld_vs_out2__pu: 1;    //   13
    UINT32 reg_pad_ld_vs_out2__st: 1;    //   14
    UINT32 resvd02            : 17;    //  31:15 reserved
    };
}FUNC_IOMUX_FMS_PAD_FMS05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2100    pad_fms64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pcmi3lrch_mux_sel: 4;    //  3:0
    UINT32 reg_pad_dacclfch_mux_sel: 4;    //  7:4
    UINT32 reg_pad_dacslrch_mux_sel: 4;    //  11:8
    UINT32 reg_pad_aec_lrch3_mux_sel: 4;    //  15:12
    UINT32 reg_pad_aec_lrch2_mux_sel: 4;    //  19:16
    UINT32 reg_pad_aec_lrch1_mux_sel: 4;    //  23:20
    UINT32 reg_pad_aec_lrch0_mux_sel: 4;    //  27:24
    UINT32 reg_pad_iec958out_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_FMS_PAD_FMS64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2104    pad_fms65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_dim0_mosi_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ld_vs_out0_mux_sel: 4;    //  7:4
    UINT32 reg_pad_pwm2_mux_sel: 4;    //  11: 8
    UINT32 reg_pad_pwm1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_pwm0_mux_sel: 4;    //  19:16
    UINT32 reg_pad_pwm_in_mux_sel: 4;    //  23:20
    UINT32 reg_pad_pcmi3sck_mux_sel: 4;    //  27:24
    UINT32 reg_pad_pcmi3lrck_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_FMS_PAD_FMS65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC37_2108    pad_fms66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_pqe_ip_enb_mux_sel: 4;    //  3:0
    UINT32 reg_pad_ld_vs_out2_mux_sel: 4;    //  7:4
    UINT32 reg_pad_dim1_sclk_mux_sel: 4;    //  11:8
    UINT32 reg_pad_dim1_mosi_mux_sel: 4;    //  15:12
    UINT32 reg_pad_ld_vs_out1_mux_sel: 4;    //  19:16
    UINT32 reg_pad_dim0_sclk_mux_sel: 4;    //  23:20
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}FUNC_IOMUX_FMS_PAD_FMS66_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_FMS_PAD_FMS00_O22A0_T          pad_fms00  ;             // 0xCC37_2000
    FUNC_IOMUX_FMS_PAD_FMS01_O22A0_T          pad_fms01  ;             // 0xCC37_2004
    FUNC_IOMUX_FMS_PAD_FMS02_O22A0_T          pad_fms02  ;             // 0xCC37_2008
    FUNC_IOMUX_FMS_PAD_FMS03_O22A0_T          pad_fms03  ;             // 0xCC37_200C
    FUNC_IOMUX_FMS_PAD_FMS04_O22A0_T          pad_fms04  ;             // 0xCC37_2010
    FUNC_IOMUX_FMS_PAD_FMS05_O22A0_T          pad_fms05  ;             // 0xCC37_2014
    UINT32                             _rsvd_00[58];            // 0xCC37_2018 ~ 0xCC37_20FC
    FUNC_IOMUX_FMS_PAD_FMS64_O22A0_T          pad_fms64  ;             // 0xCC37_2100
    FUNC_IOMUX_FMS_PAD_FMS65_O22A0_T          pad_fms65  ;             // 0xCC37_2104
    FUNC_IOMUX_FMS_PAD_FMS66_O22A0_T          pad_fms66  ;             // 0xCC37_2108
}FUNC_IOMUX_FMS_REG_O22A0_T;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FUNC_IOMUX_FMS_REG_H_

/* from 'O22_CTOP_PAD_Register_Manual.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

