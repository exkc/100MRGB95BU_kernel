#ifndef _IP_CTRL_EDPTX_REG_O26A0_H_
#define _IP_CTRL_EDPTX_REG_O26A0_H_

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
    0xC6BB_1000    ipw_edptx_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}IP_CTRL_EDPTX_IPW_EDPTX_000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_1004    ipw_edptx_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_edptx_0     :  1,    //      0
                              : 31;    //   31:1 reserved
}IP_CTRL_EDPTX_IPW_EDPTX_001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_1FF8    ipw_edptx_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}IP_CTRL_EDPTX_IPW_EDPTX_1022_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_1FFC    ipw_edptx_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}IP_CTRL_EDPTX_IPW_EDPTX_1023_O26A0_T;

/*-----------------------------------------------------------------------------------------
    ip_ctrl_edptx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_EDPTX_IPW_EDPTX_000_O26A0_T    ipw_edptx_000;       // 0xC6BB_1000
    IP_CTRL_EDPTX_IPW_EDPTX_001_O26A0_T    ipw_edptx_001;       // 0xC6BB_1004
    UINT32                             _rsvd_00[1020];          // 0xC6BB_1008 ~ 0xC6BB_1FF4
    IP_CTRL_EDPTX_IPW_EDPTX_1022_O26A0_T    ipw_edptx_1022;     // 0xC6BB_1FF8
    IP_CTRL_EDPTX_IPW_EDPTX_1023_O26A0_T    ipw_edptx_1023;     // 0xC6BB_1FFC
}IP_CTRL_EDPTX_REG_O26A0_T;
/* 4 regs */

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

#define IP_CTRL_EDPTX_IPW_EDPTX_000_O26A0_T_OFF             (BASEADDRESS+0x0000)
#define IP_CTRL_EDPTX_IPW_EDPTX_001_O26A0_T_OFF             (BASEADDRESS+0x0004)
#define IP_CTRL_EDPTX_IPW_EDPTX_1022_O26A0_T_OFF            (BASEADDRESS+0x0FF8)
#define IP_CTRL_EDPTX_IPW_EDPTX_1023_O26A0_T_OFF            (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xC6BB_1000    ipw_edptx_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}IP_CTRL_EDPTX_IPW_EDPTX_000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_1004    ipw_edptx_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_edptx_0: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}IP_CTRL_EDPTX_IPW_EDPTX_001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_1FF8    ipw_edptx_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}IP_CTRL_EDPTX_IPW_EDPTX_1022_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_1FFC    ipw_edptx_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}IP_CTRL_EDPTX_IPW_EDPTX_1023_O26A0_T;

/*-----------------------------------------------------------------------------------------
    ip_ctrl_edptx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_EDPTX_IPW_EDPTX_000_O26A0_T    ipw_edptx_000;       // 0xC6BB_1000
    IP_CTRL_EDPTX_IPW_EDPTX_001_O26A0_T    ipw_edptx_001;       // 0xC6BB_1004
    UINT32                             _rsvd_00[1020];          // 0xC6BB_1008 ~ 0xC6BB_1FF4
    IP_CTRL_EDPTX_IPW_EDPTX_1022_O26A0_T    ipw_edptx_1022;     // 0xC6BB_1FF8
    IP_CTRL_EDPTX_IPW_EDPTX_1023_O26A0_T    ipw_edptx_1023;     // 0xC6BB_1FFC
}IP_CTRL_EDPTX_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IP_CTRL_EDPTX_REG_H_

/* from 'O26_IPW_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

