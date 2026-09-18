#ifndef _DSC_IPW_TOP_REG_H_
#define _DSC_IPW_TOP_REG_H_

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
    0xC88B_0000+0x0    ipw_dsc_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}DSC_IPW_TOP_IPW_DSC_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC88B_0000+0x4    ipw_dsc_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_hdmi_5      :  1,    //      0
    reg_swrst_fly_hdmi_1      :  1,    //      1
    reg_swrst_fly_hdmi_2      :  1,    //      2
    reg_swrst_fly_hdmi_3      :  1,    //      3
    reg_swrst_fly_hdmi_4      :  1,    //      4
                              : 27;    //   31:5 reserved
}DSC_IPW_TOP_IPW_DSC_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC88B_0000+0x8    ipw_dsc_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_dsc_1       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_swrst_fly_dsc_2       :  1,    //      4
                              : 27;    //   31:5 reserved
}DSC_IPW_TOP_IPW_DSC_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC88B_0000+0xFF8    ipw_dsc_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}DSC_IPW_TOP_IPW_DSC_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC88B_0000+0xFFC    ipw_dsc_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}DSC_IPW_TOP_IPW_DSC_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_dsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    DSC_IPW_TOP_IPW_DSC_000_O22A0_T        ipw_dsc_000;             // 0xC88B_0000+0x0
    DSC_IPW_TOP_IPW_DSC_001_O22A0_T        ipw_dsc_001;             // 0xC88B_0000+0x4
    DSC_IPW_TOP_IPW_DSC_002_O22A0_T        ipw_dsc_002;             // 0xC88B_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xC88B_0000+0xC ~ 0xC88B_0000+0xFF4
    DSC_IPW_TOP_IPW_DSC_1022_O22A0_T       ipw_dsc_1022;            // 0xC88B_0000+0xFF8
    DSC_IPW_TOP_IPW_DSC_1023_O22A0_T       ipw_dsc_1023;            // 0xC88B_0000+0xFFC
}DSC_IPW_TOP_REG_O22A0_T;
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

#define DSC_IPW_TOP_IPW_DSC_000_O22A0_T_OFF                     (BASEADDRESS+0xC88B_0000+0x0000)
#define DSC_IPW_TOP_IPW_DSC_001_O22A0_T_OFF                     (BASEADDRESS+0xC88B_0000+0x0004)
#define DSC_IPW_TOP_IPW_DSC_002_O22A0_T_OFF                     (BASEADDRESS+0xC88B_0000+0x0008)
#define DSC_IPW_TOP_IPW_DSC_1022_O22A0_T_OFF                    (BASEADDRESS+0xC88B_0000+0x0FF8)
#define DSC_IPW_TOP_IPW_DSC_1023_O22A0_T_OFF                    (BASEADDRESS+0xC88B_0000+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xC88B_0000+0x0    ipw_dsc_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}DSC_IPW_TOP_IPW_DSC_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC88B_0000+0x4    ipw_dsc_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_hdmi_5: 1;    //      0
    UINT32 reg_swrst_fly_hdmi_1: 1;    //      1
    UINT32 reg_swrst_fly_hdmi_2: 1;    //      2
    UINT32 reg_swrst_fly_hdmi_3: 1;    //      3
    UINT32 reg_swrst_fly_hdmi_4: 1;    //      4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}DSC_IPW_TOP_IPW_DSC_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC88B_0000+0x8    ipw_dsc_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_dsc_1:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_swrst_fly_dsc_2:  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}DSC_IPW_TOP_IPW_DSC_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC88B_0000+0xFF8    ipw_dsc_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}DSC_IPW_TOP_IPW_DSC_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC88B_0000+0xFFC    ipw_dsc_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}DSC_IPW_TOP_IPW_DSC_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_dsc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    DSC_IPW_TOP_IPW_DSC_000_O22A0_T        ipw_dsc_000;             // 0xC88B_0000+0x0
    DSC_IPW_TOP_IPW_DSC_001_O22A0_T        ipw_dsc_001;             // 0xC88B_0000+0x4
    DSC_IPW_TOP_IPW_DSC_002_O22A0_T        ipw_dsc_002;             // 0xC88B_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xC88B_0000+0xC ~ 0xC88B_0000+0xFF4
    DSC_IPW_TOP_IPW_DSC_1022_O22A0_T       ipw_dsc_1022;            // 0xC88B_0000+0xFF8
    DSC_IPW_TOP_IPW_DSC_1023_O22A0_T       ipw_dsc_1023;            // 0xC88B_0000+0xFFC
}DSC_IPW_TOP_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_DSC_IPW_TOP_REG_H_

/* from 'O22_CTOP_IPW_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

