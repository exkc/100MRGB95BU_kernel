#ifndef _TCON_IPW_TOP_REG_H_
#define _TCON_IPW_TOP_REG_H_

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
    0xCC45_0000+0x0    ipw_tcon_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}TCON_IPW_TOP_IPW_TCON_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC45_0000+0x4    ipw_tcon_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_hsp_led_0       :  1,    //      0
    reg_swrst_fly_cco_4       :  1,    //      1
    reg_swrst_fly_led_2       :  1,    //      2
    reg_swrst_hsp_cco_8       :  1,    //      3
                              : 28;    //   31:4 reserved
}TCON_IPW_TOP_IPW_TCON_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC45_0000+0xFF8    ipw_tcon_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}TCON_IPW_TOP_IPW_TCON_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC45_0000+0xFFC    ipw_tcon_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}TCON_IPW_TOP_IPW_TCON_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TCON_IPW_TOP_IPW_TCON_000_O22A0_T      ipw_tcon_000;            // 0xCC45_0000+0x0
    TCON_IPW_TOP_IPW_TCON_001_O22A0_T      ipw_tcon_001;            // 0xCC45_0000+0x4
    UINT32                             _rsvd_00[1020];          // 0xCC45_0000+0x8 ~ 0xCC45_0000+0xFF4
    TCON_IPW_TOP_IPW_TCON_1022_O22A0_T     ipw_tcon_1022;           // 0xCC45_0000+0xFF8
    TCON_IPW_TOP_IPW_TCON_1023_O22A0_T     ipw_tcon_1023;           // 0xCC45_0000+0xFFC
}TCON_IPW_TOP_REG_O22A0_T;
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

#define TCON_IPW_TOP_IPW_TCON_000_O22A0_T_OFF                   (BASEADDRESS+0xCC45_0000+0x0000)
#define TCON_IPW_TOP_IPW_TCON_001_O22A0_T_OFF                   (BASEADDRESS+0xCC45_0000+0x0004)
#define TCON_IPW_TOP_IPW_TCON_1022_O22A0_T_OFF                  (BASEADDRESS+0xCC45_0000+0x0FF8)
#define TCON_IPW_TOP_IPW_TCON_1023_O22A0_T_OFF                  (BASEADDRESS+0xCC45_0000+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCC45_0000+0x0    ipw_tcon_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}TCON_IPW_TOP_IPW_TCON_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC45_0000+0x4    ipw_tcon_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_hsp_led_0:  1;    //      0
    UINT32 reg_swrst_fly_cco_4:  1;    //      1
    UINT32 reg_swrst_fly_led_2:  1;    //      2
    UINT32 reg_swrst_hsp_cco_8:  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}TCON_IPW_TOP_IPW_TCON_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC45_0000+0xFF8    ipw_tcon_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}TCON_IPW_TOP_IPW_TCON_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC45_0000+0xFFC    ipw_tcon_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}TCON_IPW_TOP_IPW_TCON_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_tcon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    TCON_IPW_TOP_IPW_TCON_000_O22A0_T      ipw_tcon_000;            // 0xCC45_0000+0x0
    TCON_IPW_TOP_IPW_TCON_001_O22A0_T      ipw_tcon_001;            // 0xCC45_0000+0x4
    UINT32                             _rsvd_00[1020];          // 0xCC45_0000+0x8 ~ 0xCC45_0000+0xFF4
    TCON_IPW_TOP_IPW_TCON_1022_O22A0_T     ipw_tcon_1022;           // 0xCC45_0000+0xFF8
    TCON_IPW_TOP_IPW_TCON_1023_O22A0_T     ipw_tcon_1023;           // 0xCC45_0000+0xFFC
}TCON_IPW_TOP_REG_O22A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_TCON_IPW_TOP_REG_H_

/* from 'O22_CTOP_IPW_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

