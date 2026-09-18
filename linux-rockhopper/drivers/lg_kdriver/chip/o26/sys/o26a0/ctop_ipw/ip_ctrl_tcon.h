#ifndef _IP_CTRL_TCON_REG_O26A0_H_
#define _IP_CTRL_TCON_REG_O26A0_H_

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
    0xCC94_1000    ipw_tcon_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}IP_CTRL_TCON_IPW_TCON_000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_1004    ipw_tcon_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_tcon_0      :  1,    //      0
    reg_swrst_fly_tcon_1      :  1,    //      1
    reg_swrst_fly_tcon_2      :  1,    //      2
    reg_swrst_fly_tcon_3      :  1,    //      3
    reg_swrst_fly_tcon_4      :  1,    //      4
    reg_swrst_fly_tcon_5      :  1,    //      5
    reg_swrst_fly_tcon_6      :  1,    //      6
    reg_swrst_fly_tcon_7      :  1,    //      7
    reg_swrst_fly_tcon_8      :  1,    //      8
    reg_swrst_fly_tcon_9      :  1,    //      9
    reg_swrst_fly_tcon_10     :  1,    //     10
    reg_swrst_fly_tcon_11     :  1,    //     11
    reg_swrst_fly_tcon_12     :  1,    //     12
                              : 19;    //  31:13 reserved
}IP_CTRL_TCON_IPW_TCON_001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_1008    ipw_tcon_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4tx_data_sel         :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}IP_CTRL_TCON_IPW_TCON_002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_1FF8    ipw_tcon_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}IP_CTRL_TCON_IPW_TCON_1022_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_1FFC    ipw_tcon_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}IP_CTRL_TCON_IPW_TCON_1023_O26A0_T;

/*-----------------------------------------------------------------------------------------
    ip_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_TCON_IPW_TCON_000_O26A0_T    ipw_tcon_000;          // 0xCC94_1000
    IP_CTRL_TCON_IPW_TCON_001_O26A0_T    ipw_tcon_001;          // 0xCC94_1004
    IP_CTRL_TCON_IPW_TCON_002_O26A0_T    ipw_tcon_002;          // 0xCC94_1008
    UINT32                             _rsvd_00[1019];          // 0xCC94_100C ~ 0xCC94_1FF4
    IP_CTRL_TCON_IPW_TCON_1022_O26A0_T    ipw_tcon_1022;        // 0xCC94_1FF8
    IP_CTRL_TCON_IPW_TCON_1023_O26A0_T    ipw_tcon_1023;        // 0xCC94_1FFC
}IP_CTRL_TCON_REG_O26A0_T;
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

#define IP_CTRL_TCON_IPW_TCON_000_O26A0_T_OFF               (BASEADDRESS+0x0000)
#define IP_CTRL_TCON_IPW_TCON_001_O26A0_T_OFF               (BASEADDRESS+0x0004)
#define IP_CTRL_TCON_IPW_TCON_002_O26A0_T_OFF               (BASEADDRESS+0x0008)
#define IP_CTRL_TCON_IPW_TCON_1022_O26A0_T_OFF              (BASEADDRESS+0x0FF8)
#define IP_CTRL_TCON_IPW_TCON_1023_O26A0_T_OFF              (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCC94_1000    ipw_tcon_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}IP_CTRL_TCON_IPW_TCON_000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_1004    ipw_tcon_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_tcon_0: 1;    //      0
    UINT32 reg_swrst_fly_tcon_1: 1;    //      1
    UINT32 reg_swrst_fly_tcon_2: 1;    //      2
    UINT32 reg_swrst_fly_tcon_3: 1;    //      3
    UINT32 reg_swrst_fly_tcon_4: 1;    //      4
    UINT32 reg_swrst_fly_tcon_5: 1;    //      5
    UINT32 reg_swrst_fly_tcon_6: 1;    //      6
    UINT32 reg_swrst_fly_tcon_7: 1;    //      7
    UINT32 reg_swrst_fly_tcon_8: 1;    //      8
    UINT32 reg_swrst_fly_tcon_9: 1;    //      9
    UINT32 reg_swrst_fly_tcon_10: 1;    //    10
    UINT32 reg_swrst_fly_tcon_11: 1;    //    11
    UINT32 reg_swrst_fly_tcon_12: 1;    //    12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}IP_CTRL_TCON_IPW_TCON_001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_1008    ipw_tcon_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4tx_data_sel  :  2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}IP_CTRL_TCON_IPW_TCON_002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_1FF8    ipw_tcon_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}IP_CTRL_TCON_IPW_TCON_1022_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC94_1FFC    ipw_tcon_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}IP_CTRL_TCON_IPW_TCON_1023_O26A0_T;

/*-----------------------------------------------------------------------------------------
    ip_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_TCON_IPW_TCON_000_O26A0_T    ipw_tcon_000;          // 0xCC94_1000
    IP_CTRL_TCON_IPW_TCON_001_O26A0_T    ipw_tcon_001;          // 0xCC94_1004
    IP_CTRL_TCON_IPW_TCON_002_O26A0_T    ipw_tcon_002;          // 0xCC94_1008
    UINT32                             _rsvd_00[1019];          // 0xCC94_100C ~ 0xCC94_1FF4
    IP_CTRL_TCON_IPW_TCON_1022_O26A0_T    ipw_tcon_1022;        // 0xCC94_1FF8
    IP_CTRL_TCON_IPW_TCON_1023_O26A0_T    ipw_tcon_1023;        // 0xCC94_1FFC
}IP_CTRL_TCON_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IP_CTRL_TCON_REG_H_

/* from 'O26_IPW_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

