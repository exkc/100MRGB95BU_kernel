#ifndef _IP_CTRL_TCON_REG_O24A0_H_
#define _IP_CTRL_TCON_REG_O24A0_H_

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
    0xCC92_1000    ipw_tcon_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}IP_CTRL_TCON_IPW_TCON_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1004    ipw_tcon_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tcon_gmau_flush_en        :  1,    //      0
                              : 31;    //   31:1 reserved
}IP_CTRL_TCON_IPW_TCON_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1008    ipw_tcon_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tcon_gmau_flush_done      :  1,    //      0
                              : 31;    //   31:1 reserved
}IP_CTRL_TCON_IPW_TCON_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_100C    ipw_tcon_003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_tcon_0      :  1,    //      0
    reg_swrst_fly_tcon_1      :  1,    //      1
                              : 30;    //   31:2 reserved
}IP_CTRL_TCON_IPW_TCON_003_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1010    ipw_tcon_004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4tx_data_sel         :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}IP_CTRL_TCON_IPW_TCON_004_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1FF8    ipw_tcon_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}IP_CTRL_TCON_IPW_TCON_1022_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1FFC    ipw_tcon_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}IP_CTRL_TCON_IPW_TCON_1023_O24A0_T;

/*-----------------------------------------------------------------------------------------
    ip_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_TCON_IPW_TCON_000_O24A0_T    ipw_tcon_000;          // 0xCC92_1000
    IP_CTRL_TCON_IPW_TCON_001_O24A0_T    ipw_tcon_001;          // 0xCC92_1004
    IP_CTRL_TCON_IPW_TCON_002_O24A0_T    ipw_tcon_002;          // 0xCC92_1008
    IP_CTRL_TCON_IPW_TCON_003_O24A0_T    ipw_tcon_003;          // 0xCC92_100C
    IP_CTRL_TCON_IPW_TCON_004_O24A0_T    ipw_tcon_004;          // 0xCC92_1010
    UINT32                             _rsvd_00[1017];          // 0xCC92_1014 ~ 0xCC92_1FF4
    IP_CTRL_TCON_IPW_TCON_1022_O24A0_T    ipw_tcon_1022;        // 0xCC92_1FF8
    IP_CTRL_TCON_IPW_TCON_1023_O24A0_T    ipw_tcon_1023;        // 0xCC92_1FFC
}IP_CTRL_TCON_REG_O24A0_T;
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

#define IP_CTRL_TCON_IPW_TCON_000_O24A0_T_OFF               (BASEADDRESS+0x0000)
#define IP_CTRL_TCON_IPW_TCON_001_O24A0_T_OFF               (BASEADDRESS+0x0004)
#define IP_CTRL_TCON_IPW_TCON_002_O24A0_T_OFF               (BASEADDRESS+0x0008)
#define IP_CTRL_TCON_IPW_TCON_003_O24A0_T_OFF               (BASEADDRESS+0x000C)
#define IP_CTRL_TCON_IPW_TCON_004_O24A0_T_OFF               (BASEADDRESS+0x0010)
#define IP_CTRL_TCON_IPW_TCON_1022_O24A0_T_OFF              (BASEADDRESS+0x0FF8)
#define IP_CTRL_TCON_IPW_TCON_1023_O24A0_T_OFF              (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCC92_1000    ipw_tcon_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}IP_CTRL_TCON_IPW_TCON_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1004    ipw_tcon_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 tcon_gmau_flush_en :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}IP_CTRL_TCON_IPW_TCON_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1008    ipw_tcon_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 tcon_gmau_flush_done: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}IP_CTRL_TCON_IPW_TCON_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_100C    ipw_tcon_003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_tcon_0: 1;    //      0
    UINT32 reg_swrst_fly_tcon_1: 1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}IP_CTRL_TCON_IPW_TCON_003_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1010    ipw_tcon_004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_c4tx_data_sel  :  2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}IP_CTRL_TCON_IPW_TCON_004_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1FF8    ipw_tcon_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}IP_CTRL_TCON_IPW_TCON_1022_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC92_1FFC    ipw_tcon_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}IP_CTRL_TCON_IPW_TCON_1023_O24A0_T;

/*-----------------------------------------------------------------------------------------
    ip_ctrl_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_TCON_IPW_TCON_000_O24A0_T    ipw_tcon_000;          // 0xCC92_1000
    IP_CTRL_TCON_IPW_TCON_001_O24A0_T    ipw_tcon_001;          // 0xCC92_1004
    IP_CTRL_TCON_IPW_TCON_002_O24A0_T    ipw_tcon_002;          // 0xCC92_1008
    IP_CTRL_TCON_IPW_TCON_003_O24A0_T    ipw_tcon_003;          // 0xCC92_100C
    IP_CTRL_TCON_IPW_TCON_004_O24A0_T    ipw_tcon_004;          // 0xCC92_1010
    UINT32                             _rsvd_00[1017];          // 0xCC92_1014 ~ 0xCC92_1FF4
    IP_CTRL_TCON_IPW_TCON_1022_O24A0_T    ipw_tcon_1022;        // 0xCC92_1FF8
    IP_CTRL_TCON_IPW_TCON_1023_O24A0_T    ipw_tcon_1023;        // 0xCC92_1FFC
}IP_CTRL_TCON_REG_O24A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _IP_CTRL_TCON_REG_H_

/* from 'O24_IPW_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

