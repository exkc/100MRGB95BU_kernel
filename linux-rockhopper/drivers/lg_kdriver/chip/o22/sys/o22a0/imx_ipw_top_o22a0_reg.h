#ifndef _IMX_IPW_TOP_REG_H_
#define _IMX_IPW_TOP_REG_H_

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
    0xCC8D_0000+0x0    ipw_imx_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}IMX_IPW_TOP_IPW_IMX_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8D_0000+0x4    ipw_imx_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_imx_ctrl          : 32;    //  31: 0
}IMX_IPW_TOP_IPW_IMX_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8D_0000+0x8    ipw_imx_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_hsp_hdr_0       :  1,    //      0
    reg_swrst_hsp_hdr_1       :  1,    //      1
    reg_swrst_hsp_hdr_2       :  1,    //      2
    reg_swrst_hsp_hdr_3       :  1,    //      3
    reg_swrst_hsp_hdr_5       :  1,    //      4
    reg_swrst_hsp_nd0_0       :  1,    //      5
    reg_swrst_hsp_hdr_4       :  1,    //      6
    reg_swrst_hsp_nd0_1       :  1,    //      7
    reg_swrst_hsp_nd1_0       :  1,    //      8
    reg_swrst_hsp_nd1_1       :  1,    //      9
    reg_swrst_hsp_sre_4       :  1,    //     10
    reg_swrst_hsp_sre_5       :  1,    //     11
    reg_swrst_hsp_sre_6       :  1,    //     12
    reg_swrst_hsp_vdo_0       :  1,    //     13
    reg_swrst_hsp_vdo_1       :  1,    //     14
    reg_swrst_hsp_vdo_2       :  1,    //     15
    reg_swrst_hsp_vdo_3       :  1,    //     16
    reg_swrst_hsp_vdo_4       :  1,    //     17
    reg_swrst_hsp_vdo_5       :  1,    //     18
    reg_swrst_fly_cco_5       :  1,    //     19
    reg_swrst_fly_cvi_0       :  1,    //     20
    reg_swrst_fly_cvi_1       :  1,    //     21
    reg_swrst_fly_cvi_2       :  1,    //     22
    reg_swrst_fly_cvi_3       :  1,    //     23
    reg_swrst_fly_cvi_4       :  1,    //     24
                              :  7;    //  31:25 reserved
}IMX_IPW_TOP_IPW_IMX_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8D_0000+0xFF8    ipw_imx_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}IMX_IPW_TOP_IPW_IMX_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8D_0000+0xFFC    ipw_imx_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}IMX_IPW_TOP_IPW_IMX_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IMX_IPW_TOP_IPW_IMX_000_O22A0_T        ipw_imx_000;             // 0xCC8D_0000+0x0
    IMX_IPW_TOP_IPW_IMX_001_O22A0_T        ipw_imx_001;             // 0xCC8D_0000+0x4
    IMX_IPW_TOP_IPW_IMX_002_O22A0_T        ipw_imx_002;             // 0xCC8D_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xCC8D_0000+0xC ~ 0xCC8D_0000+0xFF4
    IMX_IPW_TOP_IPW_IMX_1022_O22A0_T       ipw_imx_1022;            // 0xCC8D_0000+0xFF8
    IMX_IPW_TOP_IPW_IMX_1023_O22A0_T       ipw_imx_1023;            // 0xCC8D_0000+0xFFC
}IMX_IPW_TOP_REG_O22A0_T;
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

#define IMX_IPW_TOP_IPW_IMX_000_O22A0_T_OFF                     (BASEADDRESS+0xCC8D_0000+0x0000)
#define IMX_IPW_TOP_IPW_IMX_001_O22A0_T_OFF                     (BASEADDRESS+0xCC8D_0000+0x0004)
#define IMX_IPW_TOP_IPW_IMX_002_O22A0_T_OFF                     (BASEADDRESS+0xCC8D_0000+0x0008)
#define IMX_IPW_TOP_IPW_IMX_1022_O22A0_T_OFF                    (BASEADDRESS+0xCC8D_0000+0x0FF8)
#define IMX_IPW_TOP_IPW_IMX_1023_O22A0_T_OFF                    (BASEADDRESS+0xCC8D_0000+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCC8D_0000+0x0    ipw_imx_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}IMX_IPW_TOP_IPW_IMX_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8D_0000+0x4    ipw_imx_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_imx_ctrl   : 32;    //  31: 0
    };
}IMX_IPW_TOP_IPW_IMX_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8D_0000+0x8    ipw_imx_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_hsp_hdr_0:  1;    //      0
    UINT32 reg_swrst_hsp_hdr_1:  1;    //      1
    UINT32 reg_swrst_hsp_hdr_2:  1;    //      2
    UINT32 reg_swrst_hsp_hdr_3:  1;    //      3
    UINT32 reg_swrst_hsp_hdr_5:  1;    //      4
    UINT32 reg_swrst_hsp_nd0_0:  1;    //      5
    UINT32 reg_swrst_hsp_hdr_4:  1;    //      6
    UINT32 reg_swrst_hsp_nd0_1:  1;    //      7
    UINT32 reg_swrst_hsp_nd1_0:  1;    //      8
    UINT32 reg_swrst_hsp_nd1_1:  1;    //      9
    UINT32 reg_swrst_hsp_sre_4:  1;    //     10
    UINT32 reg_swrst_hsp_sre_5:  1;    //     11
    UINT32 reg_swrst_hsp_sre_6:  1;    //     12
    UINT32 reg_swrst_hsp_vdo_0:  1;    //     13
    UINT32 reg_swrst_hsp_vdo_1:  1;    //     14
    UINT32 reg_swrst_hsp_vdo_2:  1;    //     15
    UINT32 reg_swrst_hsp_vdo_3:  1;    //     16
    UINT32 reg_swrst_hsp_vdo_4:  1;    //     17
    UINT32 reg_swrst_hsp_vdo_5:  1;    //     18
    UINT32 reg_swrst_fly_cco_5:  1;    //     19
    UINT32 reg_swrst_fly_cvi_0:  1;    //     20
    UINT32 reg_swrst_fly_cvi_1:  1;    //     21
    UINT32 reg_swrst_fly_cvi_2:  1;    //     22
    UINT32 reg_swrst_fly_cvi_3:  1;    //     23
    UINT32 reg_swrst_fly_cvi_4:  1;    //     24
    UINT32 resvd00            :  7;    //  31:25 reserved
    };
}IMX_IPW_TOP_IPW_IMX_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8D_0000+0xFF8    ipw_imx_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}IMX_IPW_TOP_IPW_IMX_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC8D_0000+0xFFC    ipw_imx_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}IMX_IPW_TOP_IPW_IMX_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_imx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IMX_IPW_TOP_IPW_IMX_000_O22A0_T        ipw_imx_000;             // 0xCC8D_0000+0x0
    IMX_IPW_TOP_IPW_IMX_001_O22A0_T        ipw_imx_001;             // 0xCC8D_0000+0x4
    IMX_IPW_TOP_IPW_IMX_002_O22A0_T        ipw_imx_002;             // 0xCC8D_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xCC8D_0000+0xC ~ 0xCC8D_0000+0xFF4
    IMX_IPW_TOP_IPW_IMX_1022_O22A0_T       ipw_imx_1022;            // 0xCC8D_0000+0xFF8
    IMX_IPW_TOP_IPW_IMX_1023_O22A0_T       ipw_imx_1023;            // 0xCC8D_0000+0xFFC
}IMX_IPW_TOP_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IMX_IPW_TOP_REG_H_

/* from 'O22_CTOP_IPW_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

