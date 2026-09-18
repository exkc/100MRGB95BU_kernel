#ifndef _IP_CTRL_TCON_M23A0_REG_H_
#define _IP_CTRL_TCON_M23A0_REG_H_

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
    0xCC48_1000    ipw_tcon_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}IP_CTRL_TCON_IPW_TCON_000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1004    ipw_tcon_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tcon_gmau_flush_en        :  1,    //      0
                              : 31;    //   31:1 reserved
}IP_CTRL_TCON_IPW_TCON_001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1008    ipw_tcon_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tcon_gmau_flush_done      :  1,    //      0
                              : 31;    //   31:1 reserved
}IP_CTRL_TCON_IPW_TCON_002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_100C    ipw_tcon_003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4tx_data_sel         :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}IP_CTRL_TCON_IPW_TCON_003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1FF8    ipw_tcon_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}IP_CTRL_TCON_IPW_TCON_1022_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1FFC    ipw_tcon_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}IP_CTRL_TCON_IPW_TCON_1023_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_TCON_IPW_TCON_000_M23A0_T    ipw_tcon_000;          // 0xCC48_1000
    IP_CTRL_TCON_IPW_TCON_001_M23A0_T    ipw_tcon_001;          // 0xCC48_1004
    IP_CTRL_TCON_IPW_TCON_002_M23A0_T    ipw_tcon_002;          // 0xCC48_1008
    IP_CTRL_TCON_IPW_TCON_003_M23A0_T    ipw_tcon_003;          // 0xCC48_100C
    UINT32                             _rsvd_00[1018];          // 0xCC48_1010 ~ 0xCC48_1FF4
    IP_CTRL_TCON_IPW_TCON_1022_M23A0_T    ipw_tcon_1022;        // 0xCC48_1FF8
    IP_CTRL_TCON_IPW_TCON_1023_M23A0_T    ipw_tcon_1023;        // 0xCC48_1FFC
}IP_CTRL_TCON_REG_M23A0_T;
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

#define IP_CTRL_TCON_IPW_TCON_000_M23A0_T_OFF               (BASEADDRESS+0x0000)
#define IP_CTRL_TCON_IPW_TCON_001_M23A0_T_OFF               (BASEADDRESS+0x0004)
#define IP_CTRL_TCON_IPW_TCON_002_M23A0_T_OFF               (BASEADDRESS+0x0008)
#define IP_CTRL_TCON_IPW_TCON_003_M23A0_T_OFF               (BASEADDRESS+0x000C)
#define IP_CTRL_TCON_IPW_TCON_1022_M23A0_T_OFF              (BASEADDRESS+0x0FF8)
#define IP_CTRL_TCON_IPW_TCON_1023_M23A0_T_OFF              (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCC48_1000    ipw_tcon_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}IP_CTRL_TCON_IPW_TCON_000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1004    ipw_tcon_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 tcon_gmau_flush_en :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}IP_CTRL_TCON_IPW_TCON_001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1008    ipw_tcon_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 tcon_gmau_flush_done: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}IP_CTRL_TCON_IPW_TCON_002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_100C    ipw_tcon_003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4tx_data_sel  :  2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}IP_CTRL_TCON_IPW_TCON_003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1FF8    ipw_tcon_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}IP_CTRL_TCON_IPW_TCON_1022_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC48_1FFC    ipw_tcon_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}IP_CTRL_TCON_IPW_TCON_1023_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_TCON_IPW_TCON_000_M23A0_T    ipw_tcon_000;          // 0xCC48_1000
    IP_CTRL_TCON_IPW_TCON_001_M23A0_T    ipw_tcon_001;          // 0xCC48_1004
    IP_CTRL_TCON_IPW_TCON_002_M23A0_T    ipw_tcon_002;          // 0xCC48_1008
    IP_CTRL_TCON_IPW_TCON_003_M23A0_T    ipw_tcon_003;          // 0xCC48_100C
    UINT32                             _rsvd_00[1018];          // 0xCC48_1010 ~ 0xCC48_1FF4
    IP_CTRL_TCON_IPW_TCON_1022_M23A0_T    ipw_tcon_1022;        // 0xCC48_1FF8
    IP_CTRL_TCON_IPW_TCON_1023_M23A0_T    ipw_tcon_1023;        // 0xCC48_1FFC
}IP_CTRL_TCON_REG_M23A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_IPW_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

