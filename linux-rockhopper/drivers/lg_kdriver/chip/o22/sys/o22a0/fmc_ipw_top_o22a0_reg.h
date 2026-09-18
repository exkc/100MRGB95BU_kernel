#ifndef _FMC_IPW_TOP_REG_H_
#define _FMC_IPW_TOP_REG_H_

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
    0xCC4D_0000+0x0    ipw_fmc_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}FMC_IPW_TOP_IPW_FMC_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4D_0000+0x4    ipw_fmc_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_fmc_ctrl          : 32;    //  31: 0
}FMC_IPW_TOP_IPW_FMC_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4D_0000+0x8    ipw_fmc_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_hsp_sre_2       :  1,    //      0
    reg_swrst_hsp_sre_3       :  1,    //      1
    reg_swrst_fly_gsc_6       :  1,    //      2
    reg_swrst_hsp_gsc_7       :  1,    //      3
    reg_swrst_hsp_gsc_8       :  1,    //      4
    reg_swrst_hsp_gsc_9       :  1,    //      5
    reg_swrst_hsp_gsc_10      :  1,    //      6
                              : 25;    //   31:7 reserved
}FMC_IPW_TOP_IPW_FMC_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4D_0000+0xFF8    ipw_fmc_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}FMC_IPW_TOP_IPW_FMC_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4D_0000+0xFFC    ipw_fmc_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}FMC_IPW_TOP_IPW_FMC_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FMC_IPW_TOP_IPW_FMC_000_O22A0_T        ipw_fmc_000;             // 0xCC4D_0000+0x0
    FMC_IPW_TOP_IPW_FMC_001_O22A0_T        ipw_fmc_001;             // 0xCC4D_0000+0x4
    FMC_IPW_TOP_IPW_FMC_002_O22A0_T        ipw_fmc_002;             // 0xCC4D_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xCC4D_0000+0xC ~ 0xCC4D_0000+0xFF4
    FMC_IPW_TOP_IPW_FMC_1022_O22A0_T       ipw_fmc_1022;            // 0xCC4D_0000+0xFF8
    FMC_IPW_TOP_IPW_FMC_1023_O22A0_T       ipw_fmc_1023;            // 0xCC4D_0000+0xFFC
}FMC_IPW_TOP_REG_O22A0_T;
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

#define FMC_IPW_TOP_IPW_FMC_000_O22A0_T_OFF                     (BASEADDRESS+0xCC4D_0000+0x0000)
#define FMC_IPW_TOP_IPW_FMC_001_O22A0_T_OFF                     (BASEADDRESS+0xCC4D_0000+0x0004)
#define FMC_IPW_TOP_IPW_FMC_002_O22A0_T_OFF                     (BASEADDRESS+0xCC4D_0000+0x0008)
#define FMC_IPW_TOP_IPW_FMC_1022_O22A0_T_OFF                    (BASEADDRESS+0xCC4D_0000+0x0FF8)
#define FMC_IPW_TOP_IPW_FMC_1023_O22A0_T_OFF                    (BASEADDRESS+0xCC4D_0000+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCC4D_0000+0x0    ipw_fmc_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}FMC_IPW_TOP_IPW_FMC_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4D_0000+0x4    ipw_fmc_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_fmc_ctrl   : 32;    //  31: 0
    };
}FMC_IPW_TOP_IPW_FMC_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4D_0000+0x8    ipw_fmc_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_hsp_sre_2:  1;    //      0
    UINT32 reg_swrst_hsp_sre_3:  1;    //      1
    UINT32 reg_swrst_fly_gsc_6:  1;    //      2
    UINT32 reg_swrst_hsp_gsc_7:  1;    //      3
    UINT32 reg_swrst_hsp_gsc_8:  1;    //      4
    UINT32 reg_swrst_hsp_gsc_9:  1;    //      5
    UINT32 reg_swrst_hsp_gsc_10: 1;    //      6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}FMC_IPW_TOP_IPW_FMC_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4D_0000+0xFF8    ipw_fmc_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}FMC_IPW_TOP_IPW_FMC_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC4D_0000+0xFFC    ipw_fmc_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}FMC_IPW_TOP_IPW_FMC_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_fmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FMC_IPW_TOP_IPW_FMC_000_O22A0_T        ipw_fmc_000;             // 0xCC4D_0000+0x0
    FMC_IPW_TOP_IPW_FMC_001_O22A0_T        ipw_fmc_001;             // 0xCC4D_0000+0x4
    FMC_IPW_TOP_IPW_FMC_002_O22A0_T        ipw_fmc_002;             // 0xCC4D_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xCC4D_0000+0xC ~ 0xCC4D_0000+0xFF4
    FMC_IPW_TOP_IPW_FMC_1022_O22A0_T       ipw_fmc_1022;            // 0xCC4D_0000+0xFF8
    FMC_IPW_TOP_IPW_FMC_1023_O22A0_T       ipw_fmc_1023;            // 0xCC4D_0000+0xFFC
}FMC_IPW_TOP_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FMC_IPW_TOP_REG_H_

/* from 'O22_CTOP_IPW_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

