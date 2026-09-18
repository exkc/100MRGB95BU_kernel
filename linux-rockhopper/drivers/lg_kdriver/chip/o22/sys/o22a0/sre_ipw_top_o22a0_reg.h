#ifndef _SRE_IPW_TOP_REG_H_
#define _SRE_IPW_TOP_REG_H_

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
    0xCCC5_0000+0x0    ipw_sre_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}SRE_IPW_TOP_IPW_SRE_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0000+0x4    ipw_sre_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_sre_ctrl          : 32;    //  31: 0
}SRE_IPW_TOP_IPW_SRE_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0000+0x8    ipw_sre_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_hsp_dnnr_0      :  1,    //      0
    reg_swrst_hsp_dnsr_0      :  1,    //      1
    reg_swrst_hsp_imx_14      :  1,    //      2
    reg_swrst_hsp_imx_15      :  1,    //      3
    reg_swrst_hsp_nd0_4       :  1,    //      4
    reg_swrst_hsp_nd0_5       :  1,    //      5
    reg_swrst_hsp_nd1_2       :  1,    //      6
    reg_swrst_hsp_nd1_6       :  1,    //      7
    reg_swrst_hsp_nd1_3       :  1,    //      8
    reg_swrst_hsp_nd1_7       :  1,    //      9
    reg_swrst_hsp_nd1_4       :  1,    //     10
    reg_swrst_hsp_nd1_5       :  1,    //     11
                              : 20;    //  31:12 reserved
}SRE_IPW_TOP_IPW_SRE_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0000+0xFF8    ipw_sre_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}SRE_IPW_TOP_IPW_SRE_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0000+0xFFC    ipw_sre_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}SRE_IPW_TOP_IPW_SRE_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SRE_IPW_TOP_IPW_SRE_000_O22A0_T        ipw_sre_000;             // 0xCCC5_0000+0x0
    SRE_IPW_TOP_IPW_SRE_001_O22A0_T        ipw_sre_001;             // 0xCCC5_0000+0x4
    SRE_IPW_TOP_IPW_SRE_002_O22A0_T        ipw_sre_002;             // 0xCCC5_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xCCC5_0000+0xC ~ 0xCCC5_0000+0xFF4
    SRE_IPW_TOP_IPW_SRE_1022_O22A0_T       ipw_sre_1022;            // 0xCCC5_0000+0xFF8
    SRE_IPW_TOP_IPW_SRE_1023_O22A0_T       ipw_sre_1023;            // 0xCCC5_0000+0xFFC
}SRE_IPW_TOP_REG_O22A0_T;
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

#define SRE_IPW_TOP_IPW_SRE_000_O22A0_T_OFF                     (BASEADDRESS+0xCCC5_0000+0x0000)
#define SRE_IPW_TOP_IPW_SRE_001_O22A0_T_OFF                     (BASEADDRESS+0xCCC5_0000+0x0004)
#define SRE_IPW_TOP_IPW_SRE_002_O22A0_T_OFF                     (BASEADDRESS+0xCCC5_0000+0x0008)
#define SRE_IPW_TOP_IPW_SRE_1022_O22A0_T_OFF                    (BASEADDRESS+0xCCC5_0000+0x0FF8)
#define SRE_IPW_TOP_IPW_SRE_1023_O22A0_T_OFF                    (BASEADDRESS+0xCCC5_0000+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xCCC5_0000+0x0    ipw_sre_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}SRE_IPW_TOP_IPW_SRE_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0000+0x4    ipw_sre_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_sre_ctrl   : 32;    //  31: 0
    };
}SRE_IPW_TOP_IPW_SRE_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0000+0x8    ipw_sre_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_hsp_dnnr_0: 1;    //      0
    UINT32 reg_swrst_hsp_dnsr_0: 1;    //      1
    UINT32 reg_swrst_hsp_imx_14: 1;    //      2
    UINT32 reg_swrst_hsp_imx_15: 1;    //      3
    UINT32 reg_swrst_hsp_nd0_4:  1;    //      4
    UINT32 reg_swrst_hsp_nd0_5:  1;    //      5
    UINT32 reg_swrst_hsp_nd1_2:  1;    //      6
    UINT32 reg_swrst_hsp_nd1_6:  1;    //      7
    UINT32 reg_swrst_hsp_nd1_3:  1;    //      8
    UINT32 reg_swrst_hsp_nd1_7:  1;    //      9
    UINT32 reg_swrst_hsp_nd1_4:  1;    //     10
    UINT32 reg_swrst_hsp_nd1_5:  1;    //     11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}SRE_IPW_TOP_IPW_SRE_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0000+0xFF8    ipw_sre_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}SRE_IPW_TOP_IPW_SRE_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCC5_0000+0xFFC    ipw_sre_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}SRE_IPW_TOP_IPW_SRE_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SRE_IPW_TOP_IPW_SRE_000_O22A0_T        ipw_sre_000;             // 0xCCC5_0000+0x0
    SRE_IPW_TOP_IPW_SRE_001_O22A0_T        ipw_sre_001;             // 0xCCC5_0000+0x4
    SRE_IPW_TOP_IPW_SRE_002_O22A0_T        ipw_sre_002;             // 0xCCC5_0000+0x8
    UINT32                             _rsvd_00[1019];          // 0xCCC5_0000+0xC ~ 0xCCC5_0000+0xFF4
    SRE_IPW_TOP_IPW_SRE_1022_O22A0_T       ipw_sre_1022;            // 0xCCC5_0000+0xFF8
    SRE_IPW_TOP_IPW_SRE_1023_O22A0_T       ipw_sre_1023;            // 0xCCC5_0000+0xFFC
}SRE_IPW_TOP_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SRE_IPW_TOP_REG_H_

/* from 'O22_CTOP_IPW_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

