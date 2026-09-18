#ifndef _DNNR_IPW_TOP_REG_H_
#define _DNNR_IPW_TOP_REG_H_

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
    0xCC3B_0000+0x0    ipw_dnnr_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}DNNR_IPW_TOP_IPW_DNNR_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3B_0000+0x4    ipw_dnnr_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_hsp_sre_0       :  1,    //      0
                              : 31;    //   31:1 reserved
}DNNR_IPW_TOP_IPW_DNNR_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3B_0000+0x8    ipw_dnnr_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_hsp_dnnr_0      :  1,    //      0
                              : 31;    //   31:1 reserved
}DNNR_IPW_TOP_IPW_DNNR_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3B_0000+0xFF8    ipw_dnnr_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}DNNR_IPW_TOP_IPW_DNNR_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3B_0000+0xFFC    ipw_dnnr_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}DNNR_IPW_TOP_IPW_DNNR_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_dnnr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    DNNR_IPW_TOP_IPW_DNNR_000_O22A0_T      ipw_dnnr_000;            // 0xCC3B_0000+0x0
    DNNR_IPW_TOP_IPW_DNNR_001_O22A0_T      ipw_dnnr_001;            // 0xCC3B_0000+0x4
    DNNR_IPW_TOP_IPW_DNNR_002_O22A0_T      ipw_dnnr_002;            // 0xCC3B_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xCC3B_0000+0xC ~ 0xCC3B_0000+0xFF4
    DNNR_IPW_TOP_IPW_DNNR_1022_O22A0_T     ipw_dnnr_1022;           // 0xCC3B_0000+0xFF8
    DNNR_IPW_TOP_IPW_DNNR_1023_O22A0_T     ipw_dnnr_1023;           // 0xCC3B_0000+0xFFC
}DNNR_IPW_TOP_REG_O22A0_T;
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

#define DNNR_IPW_TOP_IPW_DNNR_000_O22A0_T_OFF                   (BASEADDRESS+0xCC3B_0000+0x0000)
#define DNNR_IPW_TOP_IPW_DNNR_001_O22A0_T_OFF                   (BASEADDRESS+0xCC3B_0000+0x0004)
#define DNNR_IPW_TOP_IPW_DNNR_002_O22A0_T_OFF                   (BASEADDRESS+0xCC3B_0000+0x0008)
#define DNNR_IPW_TOP_IPW_DNNR_1022_O22A0_T_OFF                  (BASEADDRESS+0xCC3B_0000+0x0FF8)
#define DNNR_IPW_TOP_IPW_DNNR_1023_O22A0_T_OFF                  (BASEADDRESS+0xCC3B_0000+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCC3B_0000+0x0    ipw_dnnr_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}DNNR_IPW_TOP_IPW_DNNR_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3B_0000+0x4    ipw_dnnr_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_hsp_sre_0:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}DNNR_IPW_TOP_IPW_DNNR_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3B_0000+0x8    ipw_dnnr_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_hsp_dnnr_0: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}DNNR_IPW_TOP_IPW_DNNR_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3B_0000+0xFF8    ipw_dnnr_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}DNNR_IPW_TOP_IPW_DNNR_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3B_0000+0xFFC    ipw_dnnr_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}DNNR_IPW_TOP_IPW_DNNR_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_dnnr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    DNNR_IPW_TOP_IPW_DNNR_000_O22A0_T      ipw_dnnr_000;            // 0xCC3B_0000+0x0
    DNNR_IPW_TOP_IPW_DNNR_001_O22A0_T      ipw_dnnr_001;            // 0xCC3B_0000+0x4
    DNNR_IPW_TOP_IPW_DNNR_002_O22A0_T      ipw_dnnr_002;            // 0xCC3B_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xCC3B_0000+0xC ~ 0xCC3B_0000+0xFF4
    DNNR_IPW_TOP_IPW_DNNR_1022_O22A0_T     ipw_dnnr_1022;           // 0xCC3B_0000+0xFF8
    DNNR_IPW_TOP_IPW_DNNR_1023_O22A0_T     ipw_dnnr_1023;           // 0xCC3B_0000+0xFFC
}DNNR_IPW_TOP_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_DNNR_IPW_TOP_REG_H_

/* from 'O22_CTOP_IPW_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

