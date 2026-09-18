#ifndef _IP_CTRL_TE_M23A0_REG_H_
#define _IP_CTRL_TE_M23A0_REG_H_

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
    0xCED4_1000    ipw_te_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}IP_CTRL_TE_IPW_TE_000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED4_1004    ipw_te_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_te_0        :  1,    //      0
    reg_swrst_fly_te_1        :  1,    //      1
    reg_swrst_fly_te_2        :  1,    //      2
    reg_swrst_fly_te_3        :  1,    //      3
                              : 28;    //   31:4 reserved
}IP_CTRL_TE_IPW_TE_001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED4_1008    ipw_te_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_teipw_0     :  1,    //      0
    reg_swrst_fly_teipw_1     :  1,    //      1
    reg_swrst_fly_teipw_2     :  1,    //      2
    reg_swrst_fly_teipw_3     :  1,    //      3
    reg_swrst_fly_teipw_4     :  1,    //      4
    reg_swrst_fly_teipw_5     :  1,    //      5
                              : 26;    //   31:6 reserved
}IP_CTRL_TE_IPW_TE_002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED4_1FF8    ipw_te_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}IP_CTRL_TE_IPW_TE_1022_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED4_1FFC    ipw_te_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}IP_CTRL_TE_IPW_TE_1023_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_TE_IPW_TE_000_M23A0_T    ipw_te_000 ;             // 0xCED4_1000
    IP_CTRL_TE_IPW_TE_001_M23A0_T    ipw_te_001 ;             // 0xCED4_1004
    IP_CTRL_TE_IPW_TE_002_M23A0_T    ipw_te_002 ;             // 0xCED4_1008
    UINT32                             _rsvd_00[1019];          // 0xCED4_100C ~ 0xCED4_1FF4
    IP_CTRL_TE_IPW_TE_1022_M23A0_T    ipw_te_1022;            // 0xCED4_1FF8
    IP_CTRL_TE_IPW_TE_1023_M23A0_T    ipw_te_1023;            // 0xCED4_1FFC
}IP_CTRL_TE_REG_M23A0_T;
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

#define IP_CTRL_TE_IPW_TE_000_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define IP_CTRL_TE_IPW_TE_001_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define IP_CTRL_TE_IPW_TE_002_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define IP_CTRL_TE_IPW_TE_1022_M23A0_T_OFF                (BASEADDRESS+0x0FF8)
#define IP_CTRL_TE_IPW_TE_1023_M23A0_T_OFF                (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCED4_1000    ipw_te_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}IP_CTRL_TE_IPW_TE_000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED4_1004    ipw_te_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_te_0 :  1;    //      0
    UINT32 reg_swrst_fly_te_1 :  1;    //      1
    UINT32 reg_swrst_fly_te_2 :  1;    //      2
    UINT32 reg_swrst_fly_te_3 :  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}IP_CTRL_TE_IPW_TE_001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED4_1008    ipw_te_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_teipw_0: 1;    //     0
    UINT32 reg_swrst_fly_teipw_1: 1;    //     1
    UINT32 reg_swrst_fly_teipw_2: 1;    //     2
    UINT32 reg_swrst_fly_teipw_3: 1;    //     3
    UINT32 reg_swrst_fly_teipw_4: 1;    //     4
    UINT32 reg_swrst_fly_teipw_5: 1;    //     5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}IP_CTRL_TE_IPW_TE_002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED4_1FF8    ipw_te_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}IP_CTRL_TE_IPW_TE_1022_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCED4_1FFC    ipw_te_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}IP_CTRL_TE_IPW_TE_1023_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_TE_IPW_TE_000_M23A0_T    ipw_te_000 ;             // 0xCED4_1000
    IP_CTRL_TE_IPW_TE_001_M23A0_T    ipw_te_001 ;             // 0xCED4_1004
    IP_CTRL_TE_IPW_TE_002_M23A0_T    ipw_te_002 ;             // 0xCED4_1008
    UINT32                             _rsvd_00[1019];          // 0xCED4_100C ~ 0xCED4_1FF4
    IP_CTRL_TE_IPW_TE_1022_M23A0_T    ipw_te_1022;            // 0xCED4_1FF8
    IP_CTRL_TE_IPW_TE_1023_M23A0_T    ipw_te_1023;            // 0xCED4_1FFC
}IP_CTRL_TE_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_IPW_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

