#ifndef _HDR_IPW_TOP_REG_H_
#define _HDR_IPW_TOP_REG_H_

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
    0xCCCD_0000+0x0    ipw_hdr_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}HDR_IPW_TOP_IPW_HDR_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCD_0000+0x4    ipw_hdr_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_hdr_ctrl          : 32;    //  31: 0
}HDR_IPW_TOP_IPW_HDR_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCD_0000+0x8    ipw_hdr_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_hsp_imx_2       :  1,    //      0
    reg_swrst_hsp_imx_0       :  1,    //      1
    reg_swrst_hsp_imx_1       :  1,    //      2
    reg_swrst_hsp_imx_3       :  1,    //      3
    reg_swrst_hsp_imx_4       :  1,    //      4
    reg_swrst_hsp_imx_5       :  1,    //      5
    reg_swrst_hsp_imx_6       :  1,    //      6
    reg_swrst_hsp_imx_7       :  1,    //      7
    reg_swrst_hsp_imx_8       :  1,    //      8
    reg_swrst_hsp_imx_9       :  1,    //      9
                              : 22;    //  31:10 reserved
}HDR_IPW_TOP_IPW_HDR_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCD_0000+0xFF8    ipw_hdr_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}HDR_IPW_TOP_IPW_HDR_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCD_0000+0xFFC    ipw_hdr_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}HDR_IPW_TOP_IPW_HDR_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    HDR_IPW_TOP_IPW_HDR_000_O22A0_T        ipw_hdr_000;             // 0xCCCD_0000+0x0
    HDR_IPW_TOP_IPW_HDR_001_O22A0_T        ipw_hdr_001;             // 0xCCCD_0000+0x4
    HDR_IPW_TOP_IPW_HDR_002_O22A0_T        ipw_hdr_002;             // 0xCCCD_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xCCCD_0000+0xC ~ 0xCCCD_0000+0xFF4
    HDR_IPW_TOP_IPW_HDR_1022_O22A0_T       ipw_hdr_1022;            // 0xCCCD_0000+0xFF8
    HDR_IPW_TOP_IPW_HDR_1023_O22A0_T       ipw_hdr_1023;            // 0xCCCD_0000+0xFFC
}HDR_IPW_TOP_REG_O22A0_T;
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

#define HDR_IPW_TOP_IPW_HDR_000_O22A0_T_OFF                     (BASEADDRESS+0xCCCD_0000+0x0000)
#define HDR_IPW_TOP_IPW_HDR_001_O22A0_T_OFF                     (BASEADDRESS+0xCCCD_0000+0x0004)
#define HDR_IPW_TOP_IPW_HDR_002_O22A0_T_OFF                     (BASEADDRESS+0xCCCD_0000+0x0008)
#define HDR_IPW_TOP_IPW_HDR_1022_O22A0_T_OFF                    (BASEADDRESS+0xCCCD_0000+0x0FF8)
#define HDR_IPW_TOP_IPW_HDR_1023_O22A0_T_OFF                    (BASEADDRESS+0xCCCD_0000+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCCCD_0000+0x0    ipw_hdr_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}HDR_IPW_TOP_IPW_HDR_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCD_0000+0x4    ipw_hdr_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_hdr_ctrl   : 32;    //  31: 0
    };
}HDR_IPW_TOP_IPW_HDR_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCD_0000+0x8    ipw_hdr_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_hsp_imx_2:  1;    //      0
    UINT32 reg_swrst_hsp_imx_0:  1;    //      1
    UINT32 reg_swrst_hsp_imx_1:  1;    //      2
    UINT32 reg_swrst_hsp_imx_3:  1;    //      3
    UINT32 reg_swrst_hsp_imx_4:  1;    //      4
    UINT32 reg_swrst_hsp_imx_5:  1;    //      5
    UINT32 reg_swrst_hsp_imx_6:  1;    //      6
    UINT32 reg_swrst_hsp_imx_7:  1;    //      7
    UINT32 reg_swrst_hsp_imx_8:  1;    //      8
    UINT32 reg_swrst_hsp_imx_9:  1;    //      9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}HDR_IPW_TOP_IPW_HDR_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCD_0000+0xFF8    ipw_hdr_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}HDR_IPW_TOP_IPW_HDR_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCD_0000+0xFFC    ipw_hdr_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}HDR_IPW_TOP_IPW_HDR_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    HDR_IPW_TOP_IPW_HDR_000_O22A0_T        ipw_hdr_000;             // 0xCCCD_0000+0x0
    HDR_IPW_TOP_IPW_HDR_001_O22A0_T        ipw_hdr_001;             // 0xCCCD_0000+0x4
    HDR_IPW_TOP_IPW_HDR_002_O22A0_T        ipw_hdr_002;             // 0xCCCD_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xCCCD_0000+0xC ~ 0xCCCD_0000+0xFF4
    HDR_IPW_TOP_IPW_HDR_1022_O22A0_T       ipw_hdr_1022;            // 0xCCCD_0000+0xFF8
    HDR_IPW_TOP_IPW_HDR_1023_O22A0_T       ipw_hdr_1023;            // 0xCCCD_0000+0xFFC
}HDR_IPW_TOP_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_HDR_IPW_TOP_REG_H_

/* from 'O22_CTOP_IPW_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

