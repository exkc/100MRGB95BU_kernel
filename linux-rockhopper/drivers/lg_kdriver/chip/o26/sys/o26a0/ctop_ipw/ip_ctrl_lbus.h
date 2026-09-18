#ifndef _IP_CTRL_LBUS_REG_O26A0_H_
#define _IP_CTRL_LBUS_REG_O26A0_H_

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
    0xC422_1000    ipw_lbus_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}IP_CTRL_LBUS_IPW_LBUS_000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_1004    ipw_lbus_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_s_swrst_fmc_0     :  1,    //      0
    reg_axi_m_swrst_fmc_0     :  1,    //      1
    reg_axi_s_swrst_fmc_1     :  1,    //      2
    reg_axi_m_swrst_fmc_1     :  1,    //      3
    reg_axi_s_swrst_fmc_2     :  1,    //      4
    reg_axi_m_swrst_fmc_2     :  1,    //      5
    reg_axi_s_swrst_fmc_3     :  1,    //      6
    reg_axi_m_swrst_fmc_3     :  1,    //      7
    reg_axi_s_swrst_gsc_0     :  1,    //      8
    reg_axi_m_swrst_gsc_0     :  1,    //      9
    reg_axi_s_swrst_gsc_1     :  1,    //     10
    reg_axi_m_swrst_gsc_1     :  1,    //     11
    reg_axi_s_swrst_gsc_2     :  1,    //     12
    reg_axi_m_swrst_gsc_2     :  1,    //     13
    reg_axi_s_swrst_gsc_3     :  1,    //     14
    reg_axi_m_swrst_gsc_3     :  1,    //     15
    reg_axi_s_swrst_sre_0     :  1,    //     16
    reg_axi_m_swrst_sre_0     :  1,    //     17
    reg_axi_s_swrst_imx_0     :  1,    //     18
    reg_axi_m_swrst_imx_0     :  1,    //     19
    reg_axi_s_swrst_imx_1     :  1,    //     20
    reg_axi_m_swrst_imx_1     :  1,    //     21
    reg_axi_s_swrst_imx_2     :  1,    //     22
    reg_axi_m_swrst_imx_2     :  1,    //     23
    reg_axi_s_swrst_imx_3     :  1,    //     24
    reg_axi_m_swrst_imx_3     :  1,    //     25
    reg_axi_s_swrst_fms_0     :  1,    //     26
    reg_axi_m_swrst_srcosb_0  :  1,    //     27
    reg_axi_s_swrst_srcosb_0  :  1,    //     28
    reg_axi_m_swrst_fms_0     :  1,    //     29
    reg_axi_s_swrst_fmesb_0   :  1,    //     30
    reg_axi_m_swrst_fmesb_0   :  1;    //     31
}IP_CTRL_LBUS_IPW_LBUS_001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_1008    ipw_lbus_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_s_swrst_vd0_0     :  1,    //      0
    reg_axi_m_swrst_vd0_0     :  1,    //      1
    reg_axi_s_swrst_vd0_1     :  1,    //      2
    reg_axi_m_swrst_vd0_1     :  1,    //      3
    reg_axi_s_swrst_vd1_0     :  1,    //      4
    reg_axi_m_swrst_vd1_0     :  1,    //      5
    reg_axi_s_swrst_vd1_1     :  1,    //      6
    reg_axi_m_swrst_vd1_1     :  1,    //      7
                              : 24;    //   31:8 reserved
}IP_CTRL_LBUS_IPW_LBUS_002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_100C    ipw_lbus_003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_s_swrst_gpu_0     :  1,    //      0
    reg_axi_m_swrst_gpu_0     :  1,    //      1
    reg_axi_s_swrst_gpu_1     :  1,    //      2
    reg_axi_m_swrst_gpu_1     :  1,    //      3
                              : 28;    //   31:4 reserved
}IP_CTRL_LBUS_IPW_LBUS_003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_1FF8    ipw_lbus_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}IP_CTRL_LBUS_IPW_LBUS_1022_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_1FFC    ipw_lbus_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}IP_CTRL_LBUS_IPW_LBUS_1023_O26A0_T;

/*-----------------------------------------------------------------------------------------
    ip_ctrl_lbus Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_LBUS_IPW_LBUS_000_O26A0_T    ipw_lbus_000;          // 0xC422_1000
    IP_CTRL_LBUS_IPW_LBUS_001_O26A0_T    ipw_lbus_001;          // 0xC422_1004
    IP_CTRL_LBUS_IPW_LBUS_002_O26A0_T    ipw_lbus_002;          // 0xC422_1008
    IP_CTRL_LBUS_IPW_LBUS_003_O26A0_T    ipw_lbus_003;          // 0xC422_100C
    UINT32                             _rsvd_00[1018];          // 0xC422_1010 ~ 0xC422_1FF4
    IP_CTRL_LBUS_IPW_LBUS_1022_O26A0_T    ipw_lbus_1022;        // 0xC422_1FF8
    IP_CTRL_LBUS_IPW_LBUS_1023_O26A0_T    ipw_lbus_1023;        // 0xC422_1FFC
}IP_CTRL_LBUS_REG_O26A0_T;
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

#define IP_CTRL_LBUS_IPW_LBUS_000_O26A0_T_OFF               (BASEADDRESS+0x0000)
#define IP_CTRL_LBUS_IPW_LBUS_001_O26A0_T_OFF               (BASEADDRESS+0x0004)
#define IP_CTRL_LBUS_IPW_LBUS_002_O26A0_T_OFF               (BASEADDRESS+0x0008)
#define IP_CTRL_LBUS_IPW_LBUS_003_O26A0_T_OFF               (BASEADDRESS+0x000C)
#define IP_CTRL_LBUS_IPW_LBUS_1022_O26A0_T_OFF              (BASEADDRESS+0x0FF8)
#define IP_CTRL_LBUS_IPW_LBUS_1023_O26A0_T_OFF              (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xC422_1000    ipw_lbus_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}IP_CTRL_LBUS_IPW_LBUS_000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_1004    ipw_lbus_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_s_swrst_fmc_0: 1;    //     0
    UINT32 reg_axi_m_swrst_fmc_0: 1;    //     1
    UINT32 reg_axi_s_swrst_fmc_1: 1;    //     2
    UINT32 reg_axi_m_swrst_fmc_1: 1;    //     3
    UINT32 reg_axi_s_swrst_fmc_2: 1;    //     4
    UINT32 reg_axi_m_swrst_fmc_2: 1;    //     5
    UINT32 reg_axi_s_swrst_fmc_3: 1;    //     6
    UINT32 reg_axi_m_swrst_fmc_3: 1;    //     7
    UINT32 reg_axi_s_swrst_gsc_0: 1;    //     8
    UINT32 reg_axi_m_swrst_gsc_0: 1;    //     9
    UINT32 reg_axi_s_swrst_gsc_1: 1;    //    10
    UINT32 reg_axi_m_swrst_gsc_1: 1;    //    11
    UINT32 reg_axi_s_swrst_gsc_2: 1;    //    12
    UINT32 reg_axi_m_swrst_gsc_2: 1;    //    13
    UINT32 reg_axi_s_swrst_gsc_3: 1;    //    14
    UINT32 reg_axi_m_swrst_gsc_3: 1;    //    15
    UINT32 reg_axi_s_swrst_sre_0: 1;    //    16
    UINT32 reg_axi_m_swrst_sre_0: 1;    //    17
    UINT32 reg_axi_s_swrst_imx_0: 1;    //    18
    UINT32 reg_axi_m_swrst_imx_0: 1;    //    19
    UINT32 reg_axi_s_swrst_imx_1: 1;    //    20
    UINT32 reg_axi_m_swrst_imx_1: 1;    //    21
    UINT32 reg_axi_s_swrst_imx_2: 1;    //    22
    UINT32 reg_axi_m_swrst_imx_2: 1;    //    23
    UINT32 reg_axi_s_swrst_imx_3: 1;    //    24
    UINT32 reg_axi_m_swrst_imx_3: 1;    //    25
    UINT32 reg_axi_s_swrst_fms_0: 1;    //    26
    UINT32 reg_axi_m_swrst_srcosb_0: 1;    //  27
    UINT32 reg_axi_s_swrst_srcosb_0: 1;    //  28
    UINT32 reg_axi_m_swrst_fms_0: 1;    //    29
    UINT32 reg_axi_s_swrst_fmesb_0: 1;    //  30
    UINT32 reg_axi_m_swrst_fmesb_0: 1;    //  31
    };
}IP_CTRL_LBUS_IPW_LBUS_001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_1008    ipw_lbus_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_s_swrst_vd0_0: 1;    //     0
    UINT32 reg_axi_m_swrst_vd0_0: 1;    //     1
    UINT32 reg_axi_s_swrst_vd0_1: 1;    //     2
    UINT32 reg_axi_m_swrst_vd0_1: 1;    //     3
    UINT32 reg_axi_s_swrst_vd1_0: 1;    //     4
    UINT32 reg_axi_m_swrst_vd1_0: 1;    //     5
    UINT32 reg_axi_s_swrst_vd1_1: 1;    //     6
    UINT32 reg_axi_m_swrst_vd1_1: 1;    //     7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}IP_CTRL_LBUS_IPW_LBUS_002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_100C    ipw_lbus_003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_s_swrst_gpu_0: 1;    //     0
    UINT32 reg_axi_m_swrst_gpu_0: 1;    //     1
    UINT32 reg_axi_s_swrst_gpu_1: 1;    //     2
    UINT32 reg_axi_m_swrst_gpu_1: 1;    //     3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}IP_CTRL_LBUS_IPW_LBUS_003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_1FF8    ipw_lbus_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}IP_CTRL_LBUS_IPW_LBUS_1022_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC422_1FFC    ipw_lbus_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}IP_CTRL_LBUS_IPW_LBUS_1023_O26A0_T;

/*-----------------------------------------------------------------------------------------
    ip_ctrl_lbus Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IP_CTRL_LBUS_IPW_LBUS_000_O26A0_T    ipw_lbus_000;          // 0xC422_1000
    IP_CTRL_LBUS_IPW_LBUS_001_O26A0_T    ipw_lbus_001;          // 0xC422_1004
    IP_CTRL_LBUS_IPW_LBUS_002_O26A0_T    ipw_lbus_002;          // 0xC422_1008
    IP_CTRL_LBUS_IPW_LBUS_003_O26A0_T    ipw_lbus_003;          // 0xC422_100C
    UINT32                             _rsvd_00[1018];          // 0xC422_1010 ~ 0xC422_1FF4
    IP_CTRL_LBUS_IPW_LBUS_1022_O26A0_T    ipw_lbus_1022;        // 0xC422_1FF8
    IP_CTRL_LBUS_IPW_LBUS_1023_O26A0_T    ipw_lbus_1023;        // 0xC422_1FFC
}IP_CTRL_LBUS_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IP_CTRL_LBUS_REG_H_

/* from 'O26_IPW_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

