#ifndef _VSD_IPW_TOP_REG_H_
#define _VSD_IPW_TOP_REG_H_

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
    0xCC47_1000+0x0    ipw_vsd_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}VSD_IPW_TOP_IPW_VSD_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0x4    ipw_vsd_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_vsd_ctrl          : 32;    //  31: 0
}VSD_IPW_TOP_IPW_VSD_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0x8    ipw_vsd_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sync_gen_disable          :  1,    //      0
                              : 31;    //   31:1 reserved
}VSD_IPW_TOP_IPW_VSD_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0xC    ipw_vsd_003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_hsp_cco_1       :  1,    //      0
    reg_swrst_hsp_cco_2       :  1,    //      1
    reg_swrst_hsp_cco_3       :  1,    //      2
    reg_swrst_hsp_gsc_0       :  1,    //      3
    reg_swrst_hsp_gsc_1       :  1,    //      4
    reg_swrst_hsp_gsc_2       :  1,    //      5
    reg_swrst_hsp_gsc_3       :  1,    //      6
    reg_swrst_hsp_gsc_4       :  1,    //      7
    reg_swrst_hsp_gsc_5       :  1,    //      8
    reg_swrst_fly_cco_6       :  1,    //      9
    reg_swrst_fly_imx_16      :  1,    //     10
    reg_swrst_fly_me0_1       :  1,    //     11
                              : 20;    //  31:12 reserved
}VSD_IPW_TOP_IPW_VSD_003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0xFF8    ipw_vsd_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}VSD_IPW_TOP_IPW_VSD_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0xFFC    ipw_vsd_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}VSD_IPW_TOP_IPW_VSD_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_vsd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    VSD_IPW_TOP_IPW_VSD_000_O22A0_T        ipw_vsd_000;             // 0xCC47_1000+0x0
    VSD_IPW_TOP_IPW_VSD_001_O22A0_T        ipw_vsd_001;             // 0xCC47_1000+0x4
    VSD_IPW_TOP_IPW_VSD_002_O22A0_T        ipw_vsd_002;             // 0xCC47_1000+0x8
    VSD_IPW_TOP_IPW_VSD_003_O22A0_T        ipw_vsd_003;             // 0xCC47_1000+0xC
    UINT32                             _rsvd_00[1018];          // 0xCC47_1000+0x10 ~ 0xCC47_1000+0xFF4
    VSD_IPW_TOP_IPW_VSD_1022_O22A0_T       ipw_vsd_1022;            // 0xCC47_1000+0xFF8
    VSD_IPW_TOP_IPW_VSD_1023_O22A0_T       ipw_vsd_1023;            // 0xCC47_1000+0xFFC
}VSD_IPW_TOP_REG_O22A0_T;
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

#define VSD_IPW_TOP_IPW_VSD_000_O22A0_T_OFF                     (BASEADDRESS+0xCC47_1000+0x0000)
#define VSD_IPW_TOP_IPW_VSD_001_O22A0_T_OFF                     (BASEADDRESS+0xCC47_1000+0x0004)
#define VSD_IPW_TOP_IPW_VSD_002_O22A0_T_OFF                     (BASEADDRESS+0xCC47_1000+0x0008)
#define VSD_IPW_TOP_IPW_VSD_003_O22A0_T_OFF                     (BASEADDRESS+0xCC47_1000+0x000C)
#define VSD_IPW_TOP_IPW_VSD_1022_O22A0_T_OFF                    (BASEADDRESS+0xCC47_1000+0x0FF8)
#define VSD_IPW_TOP_IPW_VSD_1023_O22A0_T_OFF                    (BASEADDRESS+0xCC47_1000+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0x0    ipw_vsd_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}VSD_IPW_TOP_IPW_VSD_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0x4    ipw_vsd_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_vsd_ctrl   : 32;    //  31: 0
    };
}VSD_IPW_TOP_IPW_VSD_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0x8    ipw_vsd_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 sync_gen_disable   :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}VSD_IPW_TOP_IPW_VSD_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0xC    ipw_vsd_003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_hsp_cco_1:  1;    //      0
    UINT32 reg_swrst_hsp_cco_2:  1;    //      1
    UINT32 reg_swrst_hsp_cco_3:  1;    //      2
    UINT32 reg_swrst_hsp_gsc_0:  1;    //      3
    UINT32 reg_swrst_hsp_gsc_1:  1;    //      4
    UINT32 reg_swrst_hsp_gsc_2:  1;    //      5
    UINT32 reg_swrst_hsp_gsc_3:  1;    //      6
    UINT32 reg_swrst_hsp_gsc_4:  1;    //      7
    UINT32 reg_swrst_hsp_gsc_5:  1;    //      8
    UINT32 reg_swrst_fly_cco_6:  1;    //      9
    UINT32 reg_swrst_fly_imx_16: 1;    //     10
    UINT32 reg_swrst_fly_me0_1:  1;    //     11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}VSD_IPW_TOP_IPW_VSD_003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0xFF8    ipw_vsd_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}VSD_IPW_TOP_IPW_VSD_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC47_1000+0xFFC    ipw_vsd_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}VSD_IPW_TOP_IPW_VSD_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_vsd Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    VSD_IPW_TOP_IPW_VSD_000_O22A0_T        ipw_vsd_000;             // 0xCC47_1000+0x0
    VSD_IPW_TOP_IPW_VSD_001_O22A0_T        ipw_vsd_001;             // 0xCC47_1000+0x4
    VSD_IPW_TOP_IPW_VSD_002_O22A0_T        ipw_vsd_002;             // 0xCC47_1000+0x8
    VSD_IPW_TOP_IPW_VSD_003_O22A0_T        ipw_vsd_003;             // 0xCC47_1000+0xC
    UINT32                             _rsvd_00[1018];          // 0xCC47_1000+0x10 ~ 0xCC47_1000+0xFF4
    VSD_IPW_TOP_IPW_VSD_1022_O22A0_T       ipw_vsd_1022;            // 0xCC47_1000+0xFF8
    VSD_IPW_TOP_IPW_VSD_1023_O22A0_T       ipw_vsd_1023;            // 0xCC47_1000+0xFFC
}VSD_IPW_TOP_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_VSD_IPW_TOP_REG_H_

/* from 'O22_CTOP_IPW_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

