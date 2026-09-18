#ifndef _FUNC_IOMUX_EDID_REG_H_
#define _FUNC_IOMUX_EDID_REG_H_

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
    0xCA43_3000    pad_edid00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_1_sda__ds0   :  1,    //      0
    reg_pad_hdmi_1_sda__ds1   :  1,    //      1
    reg_pad_hdmi_1_sda__ds2   :  1,    //      2
    reg_pad_hdmi_1_sda__ds3   :  1,    //      3
    reg_pad_hdmi_1_sda__pd    :  1,    //      4
    reg_pad_hdmi_1_sda__pu    :  1,    //      5
    reg_pad_hdmi_1_sda__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_1_scl__ds0   :  1,    //      8
    reg_pad_hdmi_1_scl__ds1   :  1,    //      9
    reg_pad_hdmi_1_scl__ds2   :  1,    //     10
    reg_pad_hdmi_1_scl__ds3   :  1,    //     11
    reg_pad_hdmi_1_scl__pd    :  1,    //     12
    reg_pad_hdmi_1_scl__pu    :  1,    //     13
    reg_pad_hdmi_1_scl__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_edid_nisol__ds0   :  1,    //     16
    reg_pad_edid_nisol__ds1   :  1,    //     17
    reg_pad_edid_nisol__ds2   :  1,    //     18
    reg_pad_edid_nisol__ds3   :  1,    //     19
    reg_pad_edid_nisol__pd    :  1,    //     20
    reg_pad_edid_nisol__pu    :  1,    //     21
    reg_pad_edid_nisol__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_gpio28__ds0       :  1,    //     24
    reg_pad_gpio28__ds1       :  1,    //     25
    reg_pad_gpio28__ds2       :  1,    //     26
    reg_pad_gpio28__ds3       :  1,    //     27
    reg_pad_gpio28__pd        :  1,    //     28
    reg_pad_gpio28__pu        :  1,    //     29
    reg_pad_gpio28__st        :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_EDID_PAD_EDID00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3004    pad_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_2_sda__ds0   :  1,    //      0
    reg_pad_hdmi_2_sda__ds1   :  1,    //      1
    reg_pad_hdmi_2_sda__ds2   :  1,    //      2
    reg_pad_hdmi_2_sda__ds3   :  1,    //      3
    reg_pad_hdmi_2_sda__pd    :  1,    //      4
    reg_pad_hdmi_2_sda__pu    :  1,    //      5
    reg_pad_hdmi_2_sda__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_2_scl__ds0   :  1,    //      8
    reg_pad_hdmi_2_scl__ds1   :  1,    //      9
    reg_pad_hdmi_2_scl__ds2   :  1,    //     10
    reg_pad_hdmi_2_scl__ds3   :  1,    //     11
    reg_pad_hdmi_2_scl__pd    :  1,    //     12
    reg_pad_hdmi_2_scl__pu    :  1,    //     13
    reg_pad_hdmi_2_scl__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_1_5v_in__ds0 :  1,    //     16
    reg_pad_hdmi_1_5v_in__ds1 :  1,    //     17
    reg_pad_hdmi_1_5v_in__ds2 :  1,    //     18
    reg_pad_hdmi_1_5v_in__ds3 :  1,    //     19
    reg_pad_hdmi_1_5v_in__pd  :  1,    //     20
    reg_pad_hdmi_1_5v_in__pu  :  1,    //     21
    reg_pad_hdmi_1_5v_in__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_1_hpd__ds0   :  1,    //     24
    reg_pad_hdmi_1_hpd__ds1   :  1,    //     25
    reg_pad_hdmi_1_hpd__ds2   :  1,    //     26
    reg_pad_hdmi_1_hpd__ds3   :  1,    //     27
    reg_pad_hdmi_1_hpd__pd    :  1,    //     28
    reg_pad_hdmi_1_hpd__pu    :  1,    //     29
    reg_pad_hdmi_1_hpd__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_EDID_PAD_EDID01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3008    pad_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_3_sda__ds0   :  1,    //      0
    reg_pad_hdmi_3_sda__ds1   :  1,    //      1
    reg_pad_hdmi_3_sda__ds2   :  1,    //      2
    reg_pad_hdmi_3_sda__ds3   :  1,    //      3
    reg_pad_hdmi_3_sda__pd    :  1,    //      4
    reg_pad_hdmi_3_sda__pu    :  1,    //      5
    reg_pad_hdmi_3_sda__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_3_scl__ds0   :  1,    //      8
    reg_pad_hdmi_3_scl__ds1   :  1,    //      9
    reg_pad_hdmi_3_scl__ds2   :  1,    //     10
    reg_pad_hdmi_3_scl__ds3   :  1,    //     11
    reg_pad_hdmi_3_scl__pd    :  1,    //     12
    reg_pad_hdmi_3_scl__pu    :  1,    //     13
    reg_pad_hdmi_3_scl__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_2_5v_in__ds0 :  1,    //     16
    reg_pad_hdmi_2_5v_in__ds1 :  1,    //     17
    reg_pad_hdmi_2_5v_in__ds2 :  1,    //     18
    reg_pad_hdmi_2_5v_in__ds3 :  1,    //     19
    reg_pad_hdmi_2_5v_in__pd  :  1,    //     20
    reg_pad_hdmi_2_5v_in__pu  :  1,    //     21
    reg_pad_hdmi_2_5v_in__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_2_hpd__ds0   :  1,    //     24
    reg_pad_hdmi_2_hpd__ds1   :  1,    //     25
    reg_pad_hdmi_2_hpd__ds2   :  1,    //     26
    reg_pad_hdmi_2_hpd__ds3   :  1,    //     27
    reg_pad_hdmi_2_hpd__pd    :  1,    //     28
    reg_pad_hdmi_2_hpd__pu    :  1,    //     29
    reg_pad_hdmi_2_hpd__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_EDID_PAD_EDID02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_300C    pad_edid03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_4_sda__ds0   :  1,    //      0
    reg_pad_hdmi_4_sda__ds1   :  1,    //      1
    reg_pad_hdmi_4_sda__ds2   :  1,    //      2
    reg_pad_hdmi_4_sda__ds3   :  1,    //      3
    reg_pad_hdmi_4_sda__pd    :  1,    //      4
    reg_pad_hdmi_4_sda__pu    :  1,    //      5
    reg_pad_hdmi_4_sda__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_4_scl__ds0   :  1,    //      8
    reg_pad_hdmi_4_scl__ds1   :  1,    //      9
    reg_pad_hdmi_4_scl__ds2   :  1,    //     10
    reg_pad_hdmi_4_scl__ds3   :  1,    //     11
    reg_pad_hdmi_4_scl__pd    :  1,    //     12
    reg_pad_hdmi_4_scl__pu    :  1,    //     13
    reg_pad_hdmi_4_scl__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_3_5v_in__ds0 :  1,    //     16
    reg_pad_hdmi_3_5v_in__ds1 :  1,    //     17
    reg_pad_hdmi_3_5v_in__ds2 :  1,    //     18
    reg_pad_hdmi_3_5v_in__ds3 :  1,    //     19
    reg_pad_hdmi_3_5v_in__pd  :  1,    //     20
    reg_pad_hdmi_3_5v_in__pu  :  1,    //     21
    reg_pad_hdmi_3_5v_in__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_3_hpd__ds0   :  1,    //     24
    reg_pad_hdmi_3_hpd__ds1   :  1,    //     25
    reg_pad_hdmi_3_hpd__ds2   :  1,    //     26
    reg_pad_hdmi_3_hpd__ds3   :  1,    //     27
    reg_pad_hdmi_3_hpd__pd    :  1,    //     28
    reg_pad_hdmi_3_hpd__pu    :  1,    //     29
    reg_pad_hdmi_3_hpd__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_EDID_PAD_EDID03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3010    pad_edid04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 16,    //  15: 0 reserved
    reg_pad_hdmi_4_5v_in__ds0 :  1,    //     16
    reg_pad_hdmi_4_5v_in__ds1 :  1,    //     17
    reg_pad_hdmi_4_5v_in__ds2 :  1,    //     18
    reg_pad_hdmi_4_5v_in__ds3 :  1,    //     19
    reg_pad_hdmi_4_5v_in__pd  :  1,    //     20
    reg_pad_hdmi_4_5v_in__pu  :  1,    //     21
    reg_pad_hdmi_4_5v_in__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_4_hpd__ds0   :  1,    //     24
    reg_pad_hdmi_4_hpd__ds1   :  1,    //     25
    reg_pad_hdmi_4_hpd__ds2   :  1,    //     26
    reg_pad_hdmi_4_hpd__ds3   :  1,    //     27
    reg_pad_hdmi_4_hpd__pd    :  1,    //     28
    reg_pad_hdmi_4_hpd__pu    :  1,    //     29
    reg_pad_hdmi_4_hpd__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}FUNC_IOMUX_EDID_PAD_EDID04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3100    pad_edid64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_2_sda_mux_sel:  4,    //   3: 0
    reg_pad_hdmi_2_scl_mux_sel:  4,    //   7: 4
    reg_pad_hdmi_1_5v_in_mux_sel: 4,    //  11:8
    reg_pad_hdmi_1_hpd_mux_sel:  4,    //  15:12
    reg_pad_hdmi_1_sda_mux_sel:  4,    //  19:16
    reg_pad_hdmi_1_scl_mux_sel:  4,    //  23:20
    reg_pad_edid_nisol_mux_sel:  4,    //  27:24
    reg_pad_gpio28_mux_sel    :  4;    //  31:28
}FUNC_IOMUX_EDID_PAD_EDID64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3104    pad_edid65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_4_sda_mux_sel:  4,    //   3: 0
    reg_pad_hdmi_4_scl_mux_sel:  4,    //   7: 4
    reg_pad_hdmi_3_5v_in_mux_sel: 4,    //  11:8
    reg_pad_hdmi_3_hpd_mux_sel:  4,    //  15:12
    reg_pad_hdmi_3_sda_mux_sel:  4,    //  19:16
    reg_pad_hdmi_3_scl_mux_sel:  4,    //  23:20
    reg_pad_hdmi_2_5v_in_mux_sel: 4,    //  27:24
    reg_pad_hdmi_2_hpd_mux_sel:  4;    //  31:28
}FUNC_IOMUX_EDID_PAD_EDID65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3108    pad_edid66 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 24,    //  23: 0 reserved
    reg_pad_hdmi_4_5v_in_mux_sel: 4,    //  27:24
    reg_pad_hdmi_4_hpd_mux_sel:  4;    //  31:28
}FUNC_IOMUX_EDID_PAD_EDID66_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3200    pad_edid128 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_prt4_hpd_oen     :  1,    //      0
    reg_edid_prt3_hpd_oen     :  1,    //      1
    reg_edid_prt2_hpd_oen     :  1,    //      2
    reg_edid_prt1_hpd_oen     :  1,    //      3
                              : 28;    //   31:4 reserved
}FUNC_IOMUX_EDID_PAD_EDID128_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_EDID_PAD_EDID00_O22A0_T        pad_edid00 ;             // 0xCA43_3000
    FUNC_IOMUX_EDID_PAD_EDID01_O22A0_T        pad_edid01 ;             // 0xCA43_3004
    FUNC_IOMUX_EDID_PAD_EDID02_O22A0_T        pad_edid02 ;             // 0xCA43_3008
    FUNC_IOMUX_EDID_PAD_EDID03_O22A0_T        pad_edid03 ;             // 0xCA43_300C
    FUNC_IOMUX_EDID_PAD_EDID04_O22A0_T        pad_edid04 ;             // 0xCA43_3010
    UINT32                             _rsvd_00[59];            // 0xCA43_3014 ~ 0xCA43_30FC
    FUNC_IOMUX_EDID_PAD_EDID64_O22A0_T        pad_edid64 ;             // 0xCA43_3100
    FUNC_IOMUX_EDID_PAD_EDID65_O22A0_T        pad_edid65 ;             // 0xCA43_3104
    FUNC_IOMUX_EDID_PAD_EDID66_O22A0_T        pad_edid66 ;             // 0xCA43_3108
    UINT32                             _rsvd_01[61];            // 0xCA43_310C ~ 0xCA43_31FC
    FUNC_IOMUX_EDID_PAD_EDID128_O22A0_T       pad_edid128;             // 0xCA43_3200
}FUNC_IOMUX_EDID_REG_O22A0_T;
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

#define FUNC_IOMUX_EDID_PAD_EDID00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define FUNC_IOMUX_EDID_PAD_EDID01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define FUNC_IOMUX_EDID_PAD_EDID02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define FUNC_IOMUX_EDID_PAD_EDID03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define FUNC_IOMUX_EDID_PAD_EDID04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define FUNC_IOMUX_EDID_PAD_EDID64_O22A0_T_OFF                     (BASEADDRESS+0x0100)
#define FUNC_IOMUX_EDID_PAD_EDID65_O22A0_T_OFF                     (BASEADDRESS+0x0104)
#define FUNC_IOMUX_EDID_PAD_EDID66_O22A0_T_OFF                     (BASEADDRESS+0x0108)
#define FUNC_IOMUX_EDID_PAD_EDID128_O22A0_T_OFF                    (BASEADDRESS+0x0200)

/*-----------------------------------------------------------------------------------------
    0xCA43_3000    pad_edid00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_1_sda__ds0: 1;    //   0
    UINT32 reg_pad_hdmi_1_sda__ds1: 1;    //   1
    UINT32 reg_pad_hdmi_1_sda__ds2: 1;    //   2
    UINT32 reg_pad_hdmi_1_sda__ds3: 1;    //   3
    UINT32 reg_pad_hdmi_1_sda__pd: 1;    //    4
    UINT32 reg_pad_hdmi_1_sda__pu: 1;    //    5
    UINT32 reg_pad_hdmi_1_sda__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_1_scl__ds0: 1;    //   8
    UINT32 reg_pad_hdmi_1_scl__ds1: 1;    //   9
    UINT32 reg_pad_hdmi_1_scl__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_1_scl__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_1_scl__pd: 1;    //   12
    UINT32 reg_pad_hdmi_1_scl__pu: 1;    //   13
    UINT32 reg_pad_hdmi_1_scl__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_edid_nisol__ds0: 1;    //  16
    UINT32 reg_pad_edid_nisol__ds1: 1;    //  17
    UINT32 reg_pad_edid_nisol__ds2: 1;    //  18
    UINT32 reg_pad_edid_nisol__ds3: 1;    //  19
    UINT32 reg_pad_edid_nisol__pd: 1;    //   20
    UINT32 reg_pad_edid_nisol__pu: 1;    //   21
    UINT32 reg_pad_edid_nisol__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_gpio28__ds0:  1;    //     24
    UINT32 reg_pad_gpio28__ds1:  1;    //     25
    UINT32 reg_pad_gpio28__ds2:  1;    //     26
    UINT32 reg_pad_gpio28__ds3:  1;    //     27
    UINT32 reg_pad_gpio28__pd :  1;    //     28
    UINT32 reg_pad_gpio28__pu :  1;    //     29
    UINT32 reg_pad_gpio28__st :  1;    //     30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_EDID_PAD_EDID00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3004    pad_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_2_sda__ds0: 1;    //   0
    UINT32 reg_pad_hdmi_2_sda__ds1: 1;    //   1
    UINT32 reg_pad_hdmi_2_sda__ds2: 1;    //   2
    UINT32 reg_pad_hdmi_2_sda__ds3: 1;    //   3
    UINT32 reg_pad_hdmi_2_sda__pd: 1;    //    4
    UINT32 reg_pad_hdmi_2_sda__pu: 1;    //    5
    UINT32 reg_pad_hdmi_2_sda__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_2_scl__ds0: 1;    //   8
    UINT32 reg_pad_hdmi_2_scl__ds1: 1;    //   9
    UINT32 reg_pad_hdmi_2_scl__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_2_scl__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_2_scl__pd: 1;    //   12
    UINT32 reg_pad_hdmi_2_scl__pu: 1;    //   13
    UINT32 reg_pad_hdmi_2_scl__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_1_5v_in__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_1_5v_in__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_1_5v_in__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_1_5v_in__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_1_5v_in__pd: 1;    //  20
    UINT32 reg_pad_hdmi_1_5v_in__pu: 1;    //  21
    UINT32 reg_pad_hdmi_1_5v_in__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_1_hpd__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_1_hpd__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_1_hpd__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_1_hpd__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_1_hpd__pd: 1;    //   28
    UINT32 reg_pad_hdmi_1_hpd__pu: 1;    //   29
    UINT32 reg_pad_hdmi_1_hpd__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_EDID_PAD_EDID01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3008    pad_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_3_sda__ds0: 1;    //   0
    UINT32 reg_pad_hdmi_3_sda__ds1: 1;    //   1
    UINT32 reg_pad_hdmi_3_sda__ds2: 1;    //   2
    UINT32 reg_pad_hdmi_3_sda__ds3: 1;    //   3
    UINT32 reg_pad_hdmi_3_sda__pd: 1;    //    4
    UINT32 reg_pad_hdmi_3_sda__pu: 1;    //    5
    UINT32 reg_pad_hdmi_3_sda__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_3_scl__ds0: 1;    //   8
    UINT32 reg_pad_hdmi_3_scl__ds1: 1;    //   9
    UINT32 reg_pad_hdmi_3_scl__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_3_scl__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_3_scl__pd: 1;    //   12
    UINT32 reg_pad_hdmi_3_scl__pu: 1;    //   13
    UINT32 reg_pad_hdmi_3_scl__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_2_5v_in__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_2_5v_in__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_2_5v_in__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_2_5v_in__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_2_5v_in__pd: 1;    //  20
    UINT32 reg_pad_hdmi_2_5v_in__pu: 1;    //  21
    UINT32 reg_pad_hdmi_2_5v_in__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_2_hpd__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_2_hpd__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_2_hpd__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_2_hpd__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_2_hpd__pd: 1;    //   28
    UINT32 reg_pad_hdmi_2_hpd__pu: 1;    //   29
    UINT32 reg_pad_hdmi_2_hpd__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_EDID_PAD_EDID02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_300C    pad_edid03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_4_sda__ds0: 1;    //   0
    UINT32 reg_pad_hdmi_4_sda__ds1: 1;    //   1
    UINT32 reg_pad_hdmi_4_sda__ds2: 1;    //   2
    UINT32 reg_pad_hdmi_4_sda__ds3: 1;    //   3
    UINT32 reg_pad_hdmi_4_sda__pd: 1;    //    4
    UINT32 reg_pad_hdmi_4_sda__pu: 1;    //    5
    UINT32 reg_pad_hdmi_4_sda__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_4_scl__ds0: 1;    //   8
    UINT32 reg_pad_hdmi_4_scl__ds1: 1;    //   9
    UINT32 reg_pad_hdmi_4_scl__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_4_scl__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_4_scl__pd: 1;    //   12
    UINT32 reg_pad_hdmi_4_scl__pu: 1;    //   13
    UINT32 reg_pad_hdmi_4_scl__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_3_5v_in__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_3_5v_in__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_3_5v_in__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_3_5v_in__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_3_5v_in__pd: 1;    //  20
    UINT32 reg_pad_hdmi_3_5v_in__pu: 1;    //  21
    UINT32 reg_pad_hdmi_3_5v_in__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_3_hpd__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_3_hpd__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_3_hpd__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_3_hpd__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_3_hpd__pd: 1;    //   28
    UINT32 reg_pad_hdmi_3_hpd__pu: 1;    //   29
    UINT32 reg_pad_hdmi_3_hpd__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_EDID_PAD_EDID03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3010    pad_edid04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 16;    //  15: 0 reserved
    UINT32 reg_pad_hdmi_4_5v_in__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_4_5v_in__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_4_5v_in__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_4_5v_in__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_4_5v_in__pd: 1;    //  20
    UINT32 reg_pad_hdmi_4_5v_in__pu: 1;    //  21
    UINT32 reg_pad_hdmi_4_5v_in__st: 1;    //  22
    UINT32 resvd01            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_4_hpd__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_4_hpd__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_4_hpd__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_4_hpd__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_4_hpd__pd: 1;    //   28
    UINT32 reg_pad_hdmi_4_hpd__pu: 1;    //   29
    UINT32 reg_pad_hdmi_4_hpd__st: 1;    //   30
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}FUNC_IOMUX_EDID_PAD_EDID04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3100    pad_edid64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_2_sda_mux_sel: 4;    //  3:0
    UINT32 reg_pad_hdmi_2_scl_mux_sel: 4;    //  7:4
    UINT32 reg_pad_hdmi_1_5v_in_mux_sel: 4;    //  11:8
    UINT32 reg_pad_hdmi_1_hpd_mux_sel: 4;    //  15:12
    UINT32 reg_pad_hdmi_1_sda_mux_sel: 4;    //  19:16
    UINT32 reg_pad_hdmi_1_scl_mux_sel: 4;    //  23:20
    UINT32 reg_pad_edid_nisol_mux_sel: 4;    //  27:24
    UINT32 reg_pad_gpio28_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_EDID_PAD_EDID64_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3104    pad_edid65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_4_sda_mux_sel: 4;    //  3:0
    UINT32 reg_pad_hdmi_4_scl_mux_sel: 4;    //  7:4
    UINT32 reg_pad_hdmi_3_5v_in_mux_sel: 4;    //  11:8
    UINT32 reg_pad_hdmi_3_hpd_mux_sel: 4;    //  15:12
    UINT32 reg_pad_hdmi_3_sda_mux_sel: 4;    //  19:16
    UINT32 reg_pad_hdmi_3_scl_mux_sel: 4;    //  23:20
    UINT32 reg_pad_hdmi_2_5v_in_mux_sel: 4;    //  27:24
    UINT32 reg_pad_hdmi_2_hpd_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_EDID_PAD_EDID65_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3108    pad_edid66 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 24;    //  23: 0 reserved
    UINT32 reg_pad_hdmi_4_5v_in_mux_sel: 4;    //  27:24
    UINT32 reg_pad_hdmi_4_hpd_mux_sel: 4;    //  31:28
    };
}FUNC_IOMUX_EDID_PAD_EDID66_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA43_3200    pad_edid128 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_prt4_hpd_oen: 1;    //     0
    UINT32 reg_edid_prt3_hpd_oen: 1;    //     1
    UINT32 reg_edid_prt2_hpd_oen: 1;    //     2
    UINT32 reg_edid_prt1_hpd_oen: 1;    //     3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}FUNC_IOMUX_EDID_PAD_EDID128_O22A0_T;

/*-----------------------------------------------------------------------------------------
    pad_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FUNC_IOMUX_EDID_PAD_EDID00_O22A0_T        pad_edid00 ;             // 0xCA43_3000
    FUNC_IOMUX_EDID_PAD_EDID01_O22A0_T        pad_edid01 ;             // 0xCA43_3004
    FUNC_IOMUX_EDID_PAD_EDID02_O22A0_T        pad_edid02 ;             // 0xCA43_3008
    FUNC_IOMUX_EDID_PAD_EDID03_O22A0_T        pad_edid03 ;             // 0xCA43_300C
    FUNC_IOMUX_EDID_PAD_EDID04_O22A0_T        pad_edid04 ;             // 0xCA43_3010
    UINT32                             _rsvd_00[59];            // 0xCA43_3014 ~ 0xCA43_30FC
    FUNC_IOMUX_EDID_PAD_EDID64_O22A0_T        pad_edid64 ;             // 0xCA43_3100
    FUNC_IOMUX_EDID_PAD_EDID65_O22A0_T        pad_edid65 ;             // 0xCA43_3104
    FUNC_IOMUX_EDID_PAD_EDID66_O22A0_T        pad_edid66 ;             // 0xCA43_3108
    UINT32                             _rsvd_01[61];            // 0xCA43_310C ~ 0xCA43_31FC
    FUNC_IOMUX_EDID_PAD_EDID128_O22A0_T       pad_edid128;             // 0xCA43_3200
}FUNC_IOMUX_EDID_REG_O22A0_T;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FUNC_IOMUX_EDID_REG_H_

/* from 'O22_CTOP_PAD_Register_Manual.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

