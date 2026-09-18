#ifndef _CPU_IP_CTRL_EDID_REG_O26A0_H_
#define _CPU_IP_CTRL_EDID_REG_O26A0_H_

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
    0xF336_1000    ipw_edid_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}CPU_IP_CTRL_EDID_IPW_EDID_000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_1004    ipw_edid_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_wr_done          :  1,    //      0
                              : 31;    //   31:1 reserved
}CPU_IP_CTRL_EDID_IPW_EDID_001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_1FF8    ipw_edid_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}CPU_IP_CTRL_EDID_IPW_EDID_1022_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_1FFC    ipw_edid_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}CPU_IP_CTRL_EDID_IPW_EDID_1023_O26A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_ip_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_IP_CTRL_EDID_IPW_EDID_000_O26A0_T    ipw_edid_000;      // 0xF336_1000
    CPU_IP_CTRL_EDID_IPW_EDID_001_O26A0_T    ipw_edid_001;      // 0xF336_1004
    UINT32                             _rsvd_00[1020];          // 0xF336_1008 ~ 0xF336_1FF4
    CPU_IP_CTRL_EDID_IPW_EDID_1022_O26A0_T    ipw_edid_1022;    // 0xF336_1FF8
    CPU_IP_CTRL_EDID_IPW_EDID_1023_O26A0_T    ipw_edid_1023;    // 0xF336_1FFC
}CPU_IP_CTRL_EDID_REG_O26A0_T;
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

#define CPU_IP_CTRL_EDID_IPW_EDID_000_O26A0_T_OFF           (BASEADDRESS+0x0000)
#define CPU_IP_CTRL_EDID_IPW_EDID_001_O26A0_T_OFF           (BASEADDRESS+0x0004)
#define CPU_IP_CTRL_EDID_IPW_EDID_1022_O26A0_T_OFF          (BASEADDRESS+0x0FF8)
#define CPU_IP_CTRL_EDID_IPW_EDID_1023_O26A0_T_OFF          (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xF336_1000    ipw_edid_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}CPU_IP_CTRL_EDID_IPW_EDID_000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_1004    ipw_edid_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_wr_done   :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}CPU_IP_CTRL_EDID_IPW_EDID_001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_1FF8    ipw_edid_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}CPU_IP_CTRL_EDID_IPW_EDID_1022_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF336_1FFC    ipw_edid_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}CPU_IP_CTRL_EDID_IPW_EDID_1023_O26A0_T;

/*-----------------------------------------------------------------------------------------
    cpu_ip_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    CPU_IP_CTRL_EDID_IPW_EDID_000_O26A0_T    ipw_edid_000;      // 0xF336_1000
    CPU_IP_CTRL_EDID_IPW_EDID_001_O26A0_T    ipw_edid_001;      // 0xF336_1004
    UINT32                             _rsvd_00[1020];          // 0xF336_1008 ~ 0xF336_1FF4
    CPU_IP_CTRL_EDID_IPW_EDID_1022_O26A0_T    ipw_edid_1022;    // 0xF336_1FF8
    CPU_IP_CTRL_EDID_IPW_EDID_1023_O26A0_T    ipw_edid_1023;    // 0xF336_1FFC
}CPU_IP_CTRL_EDID_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_CPU_IP_CTRL_EDID_REG_H_

/* from 'O26_IPW_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

