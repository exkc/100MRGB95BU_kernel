#ifndef _IOMUX_CTRL_EDID_M23A0_REG_H_
#define _IOMUX_CTRL_EDID_M23A0_REG_H_

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
    0x0    pad_edid00 ''
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
    reg_pad_hdmi_2_sda__ds0   :  1,    //     16
    reg_pad_hdmi_2_sda__ds1   :  1,    //     17
    reg_pad_hdmi_2_sda__ds2   :  1,    //     18
    reg_pad_hdmi_2_sda__ds3   :  1,    //     19
    reg_pad_hdmi_2_sda__pd    :  1,    //     20
    reg_pad_hdmi_2_sda__pu    :  1,    //     21
    reg_pad_hdmi_2_sda__st    :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_2_scl__ds0   :  1,    //     24
    reg_pad_hdmi_2_scl__ds1   :  1,    //     25
    reg_pad_hdmi_2_scl__ds2   :  1,    //     26
    reg_pad_hdmi_2_scl__ds3   :  1,    //     27
    reg_pad_hdmi_2_scl__pd    :  1,    //     28
    reg_pad_hdmi_2_scl__pu    :  1,    //     29
    reg_pad_hdmi_2_scl__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_EDID_PAD_EDID00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    pad_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_1_hpd__ds0   :  1,    //      0
    reg_pad_hdmi_1_hpd__ds1   :  1,    //      1
    reg_pad_hdmi_1_hpd__ds2   :  1,    //      2
    reg_pad_hdmi_1_hpd__ds3   :  1,    //      3
    reg_pad_hdmi_1_hpd__pd    :  1,    //      4
    reg_pad_hdmi_1_hpd__pu    :  1,    //      5
    reg_pad_hdmi_1_hpd__st    :  1,    //      6
                              :  1,    //      7 reserved
    reg_pad_hdmi_2_hpd__ds0   :  1,    //      8
    reg_pad_hdmi_2_hpd__ds1   :  1,    //      9
    reg_pad_hdmi_2_hpd__ds2   :  1,    //     10
    reg_pad_hdmi_2_hpd__ds3   :  1,    //     11
    reg_pad_hdmi_2_hpd__pd    :  1,    //     12
    reg_pad_hdmi_2_hpd__pu    :  1,    //     13
    reg_pad_hdmi_2_hpd__st    :  1,    //     14
                              :  1,    //     15 reserved
    reg_pad_hdmi_1_5v_in__ds0 :  1,    //     16
    reg_pad_hdmi_1_5v_in__ds1 :  1,    //     17
    reg_pad_hdmi_1_5v_in__ds2 :  1,    //     18
    reg_pad_hdmi_1_5v_in__ds3 :  1,    //     19
    reg_pad_hdmi_1_5v_in__pd  :  1,    //     20
    reg_pad_hdmi_1_5v_in__pu  :  1,    //     21
    reg_pad_hdmi_1_5v_in__st  :  1,    //     22
                              :  1,    //     23 reserved
    reg_pad_hdmi_2_5v_in__ds0 :  1,    //     24
    reg_pad_hdmi_2_5v_in__ds1 :  1,    //     25
    reg_pad_hdmi_2_5v_in__ds2 :  1,    //     26
    reg_pad_hdmi_2_5v_in__ds3 :  1,    //     27
    reg_pad_hdmi_2_5v_in__pd  :  1,    //     28
    reg_pad_hdmi_2_5v_in__pu  :  1,    //     29
    reg_pad_hdmi_2_5v_in__st  :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_EDID_PAD_EDID01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x8    pad_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 25,    //  24: 0 reserved
    reg_pad_edid_nisol__ds0   :  1,    //     25
    reg_pad_edid_nisol__ds1   :  1,    //     26
    reg_pad_edid_nisol__ds2   :  1,    //     27
    reg_pad_edid_nisol__ds3   :  1,    //     28
                              :  1,    //     29 reserved
    reg_pad_edid_nisol__st    :  1,    //     30
                              :  1;    //  31:31 reserved
}IOMUX_CTRL_EDID_PAD_EDID02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC    pad_edid03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_xin__ref1         :  1,    //      0
    reg_pad_xin__ref0         :  1,    //      1
    reg_pad_xin__rd1          :  1,    //      2
    reg_pad_xin__rd0          :  1,    //      3
    reg_pad_xin__ds3          :  1,    //      4
    reg_pad_xin__ds2          :  1,    //      5
    reg_pad_xin__ds1          :  1,    //      6
    reg_pad_xin__ds0          :  1,    //      7
                              : 24;    //   31:8 reserved
}IOMUX_CTRL_EDID_PAD_EDID03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x100    pad_edid64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_hdmi_1_hpd_mux_sel:  4,    //   3: 0
    reg_pad_hdmi_2_hpd_mux_sel:  4,    //   7: 4
    reg_pad_hdmi_1_5v_in_mux_sel: 4,    //  11:8
    reg_pad_hdmi_2_5v_in_mux_sel: 4,    //  15:12
    reg_pad_hdmi_1_sda_mux_sel:  4,    //  19:16
    reg_pad_hdmi_1_scl_mux_sel:  4,    //  23:20
    reg_pad_hdmi_2_sda_mux_sel:  4,    //  27:24
    reg_pad_hdmi_2_scl_mux_sel:  4;    //  31:28
}IOMUX_CTRL_EDID_PAD_EDID64_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x200    pad_edid128 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_prt1_hpd_oen     :  1,    //      0
    reg_edid_prt2_hpd_oen     :  1,    //      1
                              : 30;    //   31:2 reserved
}IOMUX_CTRL_EDID_PAD_EDID128_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_EDID_PAD_EDID00_M23A0_T    pad_edid00 ;             // 0x0
    IOMUX_CTRL_EDID_PAD_EDID01_M23A0_T    pad_edid01 ;             // 0x4
    IOMUX_CTRL_EDID_PAD_EDID02_M23A0_T    pad_edid02 ;             // 0x8
    IOMUX_CTRL_EDID_PAD_EDID03_M23A0_T    pad_edid03 ;             // 0xC
    UINT32                             _rsvd_00[60];            // 0x10 ~ 0xFC
    IOMUX_CTRL_EDID_PAD_EDID64_M23A0_T    pad_edid64 ;             // 0x100
    UINT32                             _rsvd_01[63];            // 0x104 ~ 0x1FC
    IOMUX_CTRL_EDID_PAD_EDID128_M23A0_T    pad_edid128;            // 0x200
}IOMUX_CTRL_EDID_REG_M23A0_T;
/* 6 regs */

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

#define IOMUX_CTRL_EDID_PAD_EDID00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define IOMUX_CTRL_EDID_PAD_EDID01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define IOMUX_CTRL_EDID_PAD_EDID02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define IOMUX_CTRL_EDID_PAD_EDID03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define IOMUX_CTRL_EDID_PAD_EDID64_M23A0_T_OFF                 (BASEADDRESS+0x0100)
#define IOMUX_CTRL_EDID_PAD_EDID128_M23A0_T_OFF                (BASEADDRESS+0x0200)

/*-----------------------------------------------------------------------------------------
    0x0    pad_edid00 ''
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
    UINT32 reg_pad_hdmi_2_sda__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_2_sda__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_2_sda__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_2_sda__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_2_sda__pd: 1;    //   20
    UINT32 reg_pad_hdmi_2_sda__pu: 1;    //   21
    UINT32 reg_pad_hdmi_2_sda__st: 1;    //   22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_2_scl__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_2_scl__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_2_scl__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_2_scl__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_2_scl__pd: 1;    //   28
    UINT32 reg_pad_hdmi_2_scl__pu: 1;    //   29
    UINT32 reg_pad_hdmi_2_scl__st: 1;    //   30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_EDID_PAD_EDID00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x4    pad_edid01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_1_hpd__ds0: 1;    //   0
    UINT32 reg_pad_hdmi_1_hpd__ds1: 1;    //   1
    UINT32 reg_pad_hdmi_1_hpd__ds2: 1;    //   2
    UINT32 reg_pad_hdmi_1_hpd__ds3: 1;    //   3
    UINT32 reg_pad_hdmi_1_hpd__pd: 1;    //    4
    UINT32 reg_pad_hdmi_1_hpd__pu: 1;    //    5
    UINT32 reg_pad_hdmi_1_hpd__st: 1;    //    6
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_pad_hdmi_2_hpd__ds0: 1;    //   8
    UINT32 reg_pad_hdmi_2_hpd__ds1: 1;    //   9
    UINT32 reg_pad_hdmi_2_hpd__ds2: 1;    //  10
    UINT32 reg_pad_hdmi_2_hpd__ds3: 1;    //  11
    UINT32 reg_pad_hdmi_2_hpd__pd: 1;    //   12
    UINT32 reg_pad_hdmi_2_hpd__pu: 1;    //   13
    UINT32 reg_pad_hdmi_2_hpd__st: 1;    //   14
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_pad_hdmi_1_5v_in__ds0: 1;    //  16
    UINT32 reg_pad_hdmi_1_5v_in__ds1: 1;    //  17
    UINT32 reg_pad_hdmi_1_5v_in__ds2: 1;    //  18
    UINT32 reg_pad_hdmi_1_5v_in__ds3: 1;    //  19
    UINT32 reg_pad_hdmi_1_5v_in__pd: 1;    //  20
    UINT32 reg_pad_hdmi_1_5v_in__pu: 1;    //  21
    UINT32 reg_pad_hdmi_1_5v_in__st: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_pad_hdmi_2_5v_in__ds0: 1;    //  24
    UINT32 reg_pad_hdmi_2_5v_in__ds1: 1;    //  25
    UINT32 reg_pad_hdmi_2_5v_in__ds2: 1;    //  26
    UINT32 reg_pad_hdmi_2_5v_in__ds3: 1;    //  27
    UINT32 reg_pad_hdmi_2_5v_in__pd: 1;    //  28
    UINT32 reg_pad_hdmi_2_5v_in__pu: 1;    //  29
    UINT32 reg_pad_hdmi_2_5v_in__st: 1;    //  30
    UINT32 resvd03            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_EDID_PAD_EDID01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x8    pad_edid02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 25;    //  24: 0 reserved
    UINT32 reg_pad_edid_nisol__ds0: 1;    //  25
    UINT32 reg_pad_edid_nisol__ds1: 1;    //  26
    UINT32 reg_pad_edid_nisol__ds2: 1;    //  27
    UINT32 reg_pad_edid_nisol__ds3: 1;    //  28
    UINT32 resvd01            :  1;    //     29 reserved
    UINT32 reg_pad_edid_nisol__st: 1;    //   30
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}IOMUX_CTRL_EDID_PAD_EDID02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC    pad_edid03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_xin__ref1  :  1;    //      0
    UINT32 reg_pad_xin__ref0  :  1;    //      1
    UINT32 reg_pad_xin__rd1   :  1;    //      2
    UINT32 reg_pad_xin__rd0   :  1;    //      3
    UINT32 reg_pad_xin__ds3   :  1;    //      4
    UINT32 reg_pad_xin__ds2   :  1;    //      5
    UINT32 reg_pad_xin__ds1   :  1;    //      6
    UINT32 reg_pad_xin__ds0   :  1;    //      7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}IOMUX_CTRL_EDID_PAD_EDID03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x100    pad_edid64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_hdmi_1_hpd_mux_sel: 4;    //  3:0
    UINT32 reg_pad_hdmi_2_hpd_mux_sel: 4;    //  7:4
    UINT32 reg_pad_hdmi_1_5v_in_mux_sel: 4;    //  11:8
    UINT32 reg_pad_hdmi_2_5v_in_mux_sel: 4;    //  15:12
    UINT32 reg_pad_hdmi_1_sda_mux_sel: 4;    //  19:16
    UINT32 reg_pad_hdmi_1_scl_mux_sel: 4;    //  23:20
    UINT32 reg_pad_hdmi_2_sda_mux_sel: 4;    //  27:24
    UINT32 reg_pad_hdmi_2_scl_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_EDID_PAD_EDID64_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0x200    pad_edid128 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_prt1_hpd_oen: 1;    //     0
    UINT32 reg_edid_prt2_hpd_oen: 1;    //     1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}IOMUX_CTRL_EDID_PAD_EDID128_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_EDID_PAD_EDID00_M23A0_T    pad_edid00 ;             // 0x0
    IOMUX_CTRL_EDID_PAD_EDID01_M23A0_T    pad_edid01 ;             // 0x4
    IOMUX_CTRL_EDID_PAD_EDID02_M23A0_T    pad_edid02 ;             // 0x8
    IOMUX_CTRL_EDID_PAD_EDID03_M23A0_T    pad_edid03 ;             // 0xC
    UINT32                             _rsvd_00[60];            // 0x10 ~ 0xFC
    IOMUX_CTRL_EDID_PAD_EDID64_M23A0_T    pad_edid64 ;             // 0x100
    UINT32                             _rsvd_01[63];            // 0x104 ~ 0x1FC
    IOMUX_CTRL_EDID_PAD_EDID128_M23A0_T    pad_edid128;            // 0x200
}IOMUX_CTRL_EDID_REG_M23A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_PAD_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

