#ifndef _VDEC_MCU_IPW_TOP_REG_H_
#define _VDEC_MCU_IPW_TOP_REG_H_

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
    0xCE21_0000+0x0    ipw_vdec_mcu_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE21_0000+0x4    ipw_vdec_mcu_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_te_0        :  1,    //      0
    reg_swrst_fly_te_1        :  1,    //      1
    reg_swrst_fly_te_2        :  1,    //      2
    reg_swrst_fly_te_3        :  1,    //      3
    reg_swrst_pes_te_6        :  1,    //      4
    reg_swrst_pes_te_7        :  1,    //      5
                              : 26;    //   31:6 reserved
}VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE21_0000+0xFF8    ipw_vdec_mcu_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE21_0000+0xFFC    ipw_vdec_mcu_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_vdec_mcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_000_O22A0_T    ipw_vdec_mcu_000;    // 0xCE21_0000+0x0
    VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_001_O22A0_T    ipw_vdec_mcu_001;    // 0xCE21_0000+0x4
    UINT32                             _rsvd_00[1020];          // 0xCE21_0000+0x8 ~ 0xCE21_0000+0xFF4
    VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_1022_O22A0_T    ipw_vdec_mcu_1022;    // 0xCE21_0000+0xFF8
    VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_1023_O22A0_T    ipw_vdec_mcu_1023;    // 0xCE21_0000+0xFFC
}VDEC_MCU_IPW_TOP_REG_O22A0_T;
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

#define VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_000_O22A0_T_OFF           (BASEADDRESS+0xCE21_0000+0x0000)
#define VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_001_O22A0_T_OFF           (BASEADDRESS+0xCE21_0000+0x0004)
#define VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_1022_O22A0_T_OFF          (BASEADDRESS+0xCE21_0000+0x0FF8)
#define VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_1023_O22A0_T_OFF          (BASEADDRESS+0xCE21_0000+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCE21_0000+0x0    ipw_vdec_mcu_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE21_0000+0x4    ipw_vdec_mcu_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_te_0 :  1;    //      0
    UINT32 reg_swrst_fly_te_1 :  1;    //      1
    UINT32 reg_swrst_fly_te_2 :  1;    //      2
    UINT32 reg_swrst_fly_te_3 :  1;    //      3
    UINT32 reg_swrst_pes_te_6 :  1;    //      4
    UINT32 reg_swrst_pes_te_7 :  1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE21_0000+0xFF8    ipw_vdec_mcu_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE21_0000+0xFFC    ipw_vdec_mcu_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_vdec_mcu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_000_O22A0_T    ipw_vdec_mcu_000;    // 0xCE21_0000+0x0
    VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_001_O22A0_T    ipw_vdec_mcu_001;    // 0xCE21_0000+0x4
    UINT32                             _rsvd_00[1020];          // 0xCE21_0000+0x8 ~ 0xCE21_0000+0xFF4
    VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_1022_O22A0_T    ipw_vdec_mcu_1022;    // 0xCE21_0000+0xFF8
    VDEC_MCU_IPW_TOP_IPW_VDEC_MCU_1023_O22A0_T    ipw_vdec_mcu_1023;    // 0xCE21_0000+0xFFC
}VDEC_MCU_IPW_TOP_REG_O22A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_VDEC_MCU_IPW_TOP_REG_H_

/* from 'O22_CTOP_IPW_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

