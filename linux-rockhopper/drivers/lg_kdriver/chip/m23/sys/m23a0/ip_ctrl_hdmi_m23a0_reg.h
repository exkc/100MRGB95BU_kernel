#ifndef _IP_CTRL_HDMI_M23A0_REG_H_
#define _IP_CTRL_HDMI_M23A0_REG_H_

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
    0xC47B_1000    ipw_hdmi_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}IP_CTRL_HDMI_IPW_HDMI_000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC47B_1004    ipw_hdmi_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_hdmi_0      :  1,    //      0
    reg_swrst_fly_hdmi_1      :  1,    //      1
    reg_swrst_fly_hdmi_2      :  1,    //      2
    reg_swrst_fly_hdmi_3      :  1,    //      3
                              : 28;    //   31:4 reserved
}IP_CTRL_HDMI_IPW_HDMI_001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC47B_1008    ipw_hdmi_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_prt1_cec_enable:  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_hdmirx_prt2_cec_enable:  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_hdmirx_prt3_cec_enable:  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_hdmirx_prt4_cec_enable:  1,    //     12
                              : 19;    //  31:13 reserved
}IP_CTRL_HDMI_IPW_HDMI_002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC47B_1FF8    ipw_hdmi_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}IP_CTRL_HDMI_IPW_HDMI_1022_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC47B_1FFC    ipw_hdmi_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}IP_CTRL_HDMI_IPW_HDMI_1023_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_HDMI_IPW_HDMI_000_M23A0_T    ipw_hdmi_000;          // 0xC47B_1000
    IP_CTRL_HDMI_IPW_HDMI_001_M23A0_T    ipw_hdmi_001;          // 0xC47B_1004
    IP_CTRL_HDMI_IPW_HDMI_002_M23A0_T    ipw_hdmi_002;          // 0xC47B_1008
    UINT32                             _rsvd_00[1019];          // 0xC47B_100C ~ 0xC47B_1FF4
    IP_CTRL_HDMI_IPW_HDMI_1022_M23A0_T    ipw_hdmi_1022;        // 0xC47B_1FF8
    IP_CTRL_HDMI_IPW_HDMI_1023_M23A0_T    ipw_hdmi_1023;        // 0xC47B_1FFC
}IP_CTRL_HDMI_REG_M23A0_T;
/* 5 regs */

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

#define IP_CTRL_HDMI_IPW_HDMI_000_M23A0_T_OFF               (BASEADDRESS+0x0000)
#define IP_CTRL_HDMI_IPW_HDMI_001_M23A0_T_OFF               (BASEADDRESS+0x0004)
#define IP_CTRL_HDMI_IPW_HDMI_002_M23A0_T_OFF               (BASEADDRESS+0x0008)
#define IP_CTRL_HDMI_IPW_HDMI_1022_M23A0_T_OFF              (BASEADDRESS+0x0FF8)
#define IP_CTRL_HDMI_IPW_HDMI_1023_M23A0_T_OFF              (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xC47B_1000    ipw_hdmi_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}IP_CTRL_HDMI_IPW_HDMI_000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC47B_1004    ipw_hdmi_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_hdmi_0: 1;    //      0
    UINT32 reg_swrst_fly_hdmi_1: 1;    //      1
    UINT32 reg_swrst_fly_hdmi_2: 1;    //      2
    UINT32 reg_swrst_fly_hdmi_3: 1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}IP_CTRL_HDMI_IPW_HDMI_001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC47B_1008    ipw_hdmi_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_prt1_cec_enable: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_hdmirx_prt2_cec_enable: 1;    //  4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_hdmirx_prt3_cec_enable: 1;    //  8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_hdmirx_prt4_cec_enable: 1;    //  12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}IP_CTRL_HDMI_IPW_HDMI_002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC47B_1FF8    ipw_hdmi_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}IP_CTRL_HDMI_IPW_HDMI_1022_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC47B_1FFC    ipw_hdmi_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}IP_CTRL_HDMI_IPW_HDMI_1023_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_HDMI_IPW_HDMI_000_M23A0_T    ipw_hdmi_000;          // 0xC47B_1000
    IP_CTRL_HDMI_IPW_HDMI_001_M23A0_T    ipw_hdmi_001;          // 0xC47B_1004
    IP_CTRL_HDMI_IPW_HDMI_002_M23A0_T    ipw_hdmi_002;          // 0xC47B_1008
    UINT32                             _rsvd_00[1019];          // 0xC47B_100C ~ 0xC47B_1FF4
    IP_CTRL_HDMI_IPW_HDMI_1022_M23A0_T    ipw_hdmi_1022;        // 0xC47B_1FF8
    IP_CTRL_HDMI_IPW_HDMI_1023_M23A0_T    ipw_hdmi_1023;        // 0xC47B_1FFC
}IP_CTRL_HDMI_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_IPW_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

