#ifndef _IP_CTRL_CPU_M23A0_REG_H_
#define _IP_CTRL_CPU_M23A0_REG_H_

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
    0xCA21_1000    ipw_cpu_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}IP_CTRL_CPU_IPW_CPU_000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1004    ipw_cpu_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ayasofya_ctr00            : 32;    //  31: 0
}IP_CTRL_CPU_IPW_CPU_001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1008    ipw_cpu_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ayasofya_ctr01            : 32;    //  31: 0
}IP_CTRL_CPU_IPW_CPU_002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_100C    ipw_cpu_003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_efuse_value_valid     :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_efuse_read_done       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_otp_ar_bypass         :  1,    //      8
                              : 23;    //   31:9 reserved
}IP_CTRL_CPU_IPW_CPU_003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1010    ipw_cpu_004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_otp_read_addr         : 32;    //  31: 0
}IP_CTRL_CPU_IPW_CPU_004_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1014    ipw_cpu_005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_efuse_rdata           : 32;    //  31: 0
}IP_CTRL_CPU_IPW_CPU_005_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1018    ipw_cpu_006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_2_axi_lockup_chk_en: 1,    //      0
                              :  3,    //   3: 1 reserved
    reg_cpu_1_axi_lockup_chk_en: 1,    //      4
                              : 27;    //   31:5 reserved
}IP_CTRL_CPU_IPW_CPU_006_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1FF8    ipw_cpu_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}IP_CTRL_CPU_IPW_CPU_1022_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1FFC    ipw_cpu_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}IP_CTRL_CPU_IPW_CPU_1023_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_CPU_IPW_CPU_000_M23A0_T    ipw_cpu_000;            // 0xCA21_1000
    IP_CTRL_CPU_IPW_CPU_001_M23A0_T    ipw_cpu_001;            // 0xCA21_1004
    IP_CTRL_CPU_IPW_CPU_002_M23A0_T    ipw_cpu_002;            // 0xCA21_1008
    IP_CTRL_CPU_IPW_CPU_003_M23A0_T    ipw_cpu_003;            // 0xCA21_100C
    IP_CTRL_CPU_IPW_CPU_004_M23A0_T    ipw_cpu_004;            // 0xCA21_1010
    IP_CTRL_CPU_IPW_CPU_005_M23A0_T    ipw_cpu_005;            // 0xCA21_1014
    IP_CTRL_CPU_IPW_CPU_006_M23A0_T    ipw_cpu_006;            // 0xCA21_1018
    UINT32                             _rsvd_00[1015];          // 0xCA21_101C ~ 0xCA21_1FF4
    IP_CTRL_CPU_IPW_CPU_1022_M23A0_T    ipw_cpu_1022;          // 0xCA21_1FF8
    IP_CTRL_CPU_IPW_CPU_1023_M23A0_T    ipw_cpu_1023;          // 0xCA21_1FFC
}IP_CTRL_CPU_REG_M23A0_T;
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

#define IP_CTRL_CPU_IPW_CPU_000_M23A0_T_OFF                (BASEADDRESS+0x0000)
#define IP_CTRL_CPU_IPW_CPU_001_M23A0_T_OFF                (BASEADDRESS+0x0004)
#define IP_CTRL_CPU_IPW_CPU_002_M23A0_T_OFF                (BASEADDRESS+0x0008)
#define IP_CTRL_CPU_IPW_CPU_003_M23A0_T_OFF                (BASEADDRESS+0x000C)
#define IP_CTRL_CPU_IPW_CPU_004_M23A0_T_OFF                (BASEADDRESS+0x0010)
#define IP_CTRL_CPU_IPW_CPU_005_M23A0_T_OFF                (BASEADDRESS+0x0014)
#define IP_CTRL_CPU_IPW_CPU_006_M23A0_T_OFF                (BASEADDRESS+0x0018)
#define IP_CTRL_CPU_IPW_CPU_1022_M23A0_T_OFF               (BASEADDRESS+0x0FF8)
#define IP_CTRL_CPU_IPW_CPU_1023_M23A0_T_OFF               (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCA21_1000    ipw_cpu_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}IP_CTRL_CPU_IPW_CPU_000_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1004    ipw_cpu_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 ayasofya_ctr00     : 32;    //  31: 0
    };
}IP_CTRL_CPU_IPW_CPU_001_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1008    ipw_cpu_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 ayasofya_ctr01     : 32;    //  31: 0
    };
}IP_CTRL_CPU_IPW_CPU_002_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_100C    ipw_cpu_003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_efuse_value_valid: 1;    //     0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_efuse_read_done:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_otp_ar_bypass  :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}IP_CTRL_CPU_IPW_CPU_003_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1010    ipw_cpu_004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_otp_read_addr  : 32;    //  31: 0
    };
}IP_CTRL_CPU_IPW_CPU_004_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1014    ipw_cpu_005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_efuse_rdata    : 32;    //  31: 0
    };
}IP_CTRL_CPU_IPW_CPU_005_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1018    ipw_cpu_006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_2_axi_lockup_chk_en: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_cpu_1_axi_lockup_chk_en: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}IP_CTRL_CPU_IPW_CPU_006_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1FF8    ipw_cpu_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}IP_CTRL_CPU_IPW_CPU_1022_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_1FFC    ipw_cpu_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}IP_CTRL_CPU_IPW_CPU_1023_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_CPU_IPW_CPU_000_M23A0_T    ipw_cpu_000;            // 0xCA21_1000
    IP_CTRL_CPU_IPW_CPU_001_M23A0_T    ipw_cpu_001;            // 0xCA21_1004
    IP_CTRL_CPU_IPW_CPU_002_M23A0_T    ipw_cpu_002;            // 0xCA21_1008
    IP_CTRL_CPU_IPW_CPU_003_M23A0_T    ipw_cpu_003;            // 0xCA21_100C
    IP_CTRL_CPU_IPW_CPU_004_M23A0_T    ipw_cpu_004;            // 0xCA21_1010
    IP_CTRL_CPU_IPW_CPU_005_M23A0_T    ipw_cpu_005;            // 0xCA21_1014
    IP_CTRL_CPU_IPW_CPU_006_M23A0_T    ipw_cpu_006;            // 0xCA21_1018
    UINT32                             _rsvd_00[1015];          // 0xCA21_101C ~ 0xCA21_1FF4
    IP_CTRL_CPU_IPW_CPU_1022_M23A0_T    ipw_cpu_1022;          // 0xCA21_1FF8
    IP_CTRL_CPU_IPW_CPU_1023_M23A0_T    ipw_cpu_1023;          // 0xCA21_1FFC
}IP_CTRL_CPU_REG_M23A0_T;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_IPW_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

