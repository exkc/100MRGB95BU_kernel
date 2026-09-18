#ifndef _IP_CTRL_HDMI_REG_O24A0_H_
#define _IP_CTRL_HDMI_REG_O24A0_H_

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
    0xC8D4_1000    ipw_hdmi_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}IP_CTRL_HDMI_IPW_HDMI_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_1004    ipw_hdmi_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_hdmi_1      :  1,    //      0
    reg_swrst_fly_hdmi_3      :  1,    //      1
    reg_swrst_fly_hdmi_0      :  1,    //      2
    reg_swrst_fly_hdmi_2      :  1,    //      3
                              : 28;    //   31:4 reserved
}IP_CTRL_HDMI_IPW_HDMI_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_1008    ipw_hdmi_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_prt1_cec_enable:  1,    //      0
    reg_hdmirx_prt2_cec_enable:  1,    //      1
    reg_hdmirx_prt3_cec_enable:  1,    //      2
    reg_hdmirx_prt4_cec_enable:  1,    //      3
                              : 28;    //   31:4 reserved
}IP_CTRL_HDMI_IPW_HDMI_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_100C    ipw_hdmi_003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_prt_pix_data_sel: 1,    //      0
                              : 31;    //   31:1 reserved
}IP_CTRL_HDMI_IPW_HDMI_003_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_1010    ipw_hdmi_004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_hdmiipw_0   :  1,    //      0
    reg_swrst_fly_hdmiipw_1   :  1,    //      1
    reg_swrst_fly_hdmiipw_2   :  1,    //      2
    reg_swrst_fly_hdmiipw_3   :  1,    //      3
                              : 28;    //   31:4 reserved
}IP_CTRL_HDMI_IPW_HDMI_004_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_1FF8    ipw_hdmi_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}IP_CTRL_HDMI_IPW_HDMI_1022_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_1FFC    ipw_hdmi_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}IP_CTRL_HDMI_IPW_HDMI_1023_O24A0_T;

/*-----------------------------------------------------------------------------------------
    ip_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_HDMI_IPW_HDMI_000_O24A0_T    ipw_hdmi_000;          // 0xC8D4_1000
    IP_CTRL_HDMI_IPW_HDMI_001_O24A0_T    ipw_hdmi_001;          // 0xC8D4_1004
    IP_CTRL_HDMI_IPW_HDMI_002_O24A0_T    ipw_hdmi_002;          // 0xC8D4_1008
    IP_CTRL_HDMI_IPW_HDMI_003_O24A0_T    ipw_hdmi_003;          // 0xC8D4_100C
    IP_CTRL_HDMI_IPW_HDMI_004_O24A0_T    ipw_hdmi_004;          // 0xC8D4_1010
    UINT32                             _rsvd_00[1017];          // 0xC8D4_1014 ~ 0xC8D4_1FF4
    IP_CTRL_HDMI_IPW_HDMI_1022_O24A0_T    ipw_hdmi_1022;        // 0xC8D4_1FF8
    IP_CTRL_HDMI_IPW_HDMI_1023_O24A0_T    ipw_hdmi_1023;        // 0xC8D4_1FFC
}IP_CTRL_HDMI_REG_O24A0_T;
/* 7 regs */

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

#define IP_CTRL_HDMI_IPW_O24A0_HDMI_000_O24A0_T_OFF               (BASEADDRESS+0x0000)
#define IP_CTRL_HDMI_IPW_O24A0_HDMI_001_O24A0_T_OFF               (BASEADDRESS+0x0004)
#define IP_CTRL_HDMI_IPW_O24A0_HDMI_002_O24A0_T_OFF               (BASEADDRESS+0x0008)
#define IP_CTRL_HDMI_IPW_O24A0_HDMI_003_O24A0_T_OFF               (BASEADDRESS+0x000C)
#define IP_CTRL_HDMI_IPW_O24A0_HDMI_004_O24A0_T_OFF               (BASEADDRESS+0x0010)
#define IP_CTRL_HDMI_IPW_O24A0_HDMI_1022_O24A0_T_OFF              (BASEADDRESS+0x0FF8)
#define IP_CTRL_HDMI_IPW_O24A0_HDMI_1023_O24A0_T_OFF              (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xC8D4_1000    ipw_hdmi_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}IP_CTRL_HDMI_IPW_HDMI_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_1004    ipw_hdmi_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_hdmi_1: 1;    //      0
    UINT32 reg_swrst_fly_hdmi_3: 1;    //      1
    UINT32 reg_swrst_fly_hdmi_0: 1;    //      2
    UINT32 reg_swrst_fly_hdmi_2: 1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}IP_CTRL_HDMI_IPW_HDMI_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_1008    ipw_hdmi_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_prt1_cec_enable: 1;    //  0
    UINT32 reg_hdmirx_prt2_cec_enable: 1;    //  1
    UINT32 reg_hdmirx_prt3_cec_enable: 1;    //  2
    UINT32 reg_hdmirx_prt4_cec_enable: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}IP_CTRL_HDMI_IPW_HDMI_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_100C    ipw_hdmi_003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_prt_pix_data_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}IP_CTRL_HDMI_IPW_HDMI_003_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_1010    ipw_hdmi_004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_hdmiipw_0: 1;    //   0
    UINT32 reg_swrst_fly_hdmiipw_1: 1;    //   1
    UINT32 reg_swrst_fly_hdmiipw_2: 1;    //   2
    UINT32 reg_swrst_fly_hdmiipw_3: 1;    //   3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}IP_CTRL_HDMI_IPW_HDMI_004_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_1FF8    ipw_hdmi_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}IP_CTRL_HDMI_IPW_HDMI_1022_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D4_1FFC    ipw_hdmi_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}IP_CTRL_HDMI_IPW_HDMI_1023_O24A0_T;

/*-----------------------------------------------------------------------------------------
    ip_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_HDMI_IPW_HDMI_000_O24A0_T    ipw_hdmi_000;          // 0xC8D4_1000
    IP_CTRL_HDMI_IPW_HDMI_001_O24A0_T    ipw_hdmi_001;          // 0xC8D4_1004
    IP_CTRL_HDMI_IPW_HDMI_002_O24A0_T    ipw_hdmi_002;          // 0xC8D4_1008
    IP_CTRL_HDMI_IPW_HDMI_003_O24A0_T    ipw_hdmi_003;          // 0xC8D4_100C
    IP_CTRL_HDMI_IPW_HDMI_004_O24A0_T    ipw_hdmi_004;          // 0xC8D4_1010
    UINT32                             _rsvd_00[1017];          // 0xC8D4_1014 ~ 0xC8D4_1FF4
    IP_CTRL_HDMI_IPW_HDMI_1022_O24A0_T    ipw_hdmi_1022;        // 0xC8D4_1FF8
    IP_CTRL_HDMI_IPW_HDMI_1023_O24A0_T    ipw_hdmi_1023;        // 0xC8D4_1FFC
}IP_CTRL_HDMI_REG_O24A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _IP_CTRL_HDMI_REG_H_

/* from 'O24_IPW_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

