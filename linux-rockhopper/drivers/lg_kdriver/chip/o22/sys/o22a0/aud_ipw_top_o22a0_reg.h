#ifndef _AUD_IPW_TOP_REG_H_
#define _AUD_IPW_TOP_REG_H_

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
    0xF309_1000    ipw_aud_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_0           : 32;    //  31: 0
}AUD_IPW_TOP_IPW_AUD_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1004    ipw_aud_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dto0_add_value            : 32;    //  31: 0
}AUD_IPW_TOP_IPW_AUD_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1008    ipw_aud_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dto0_err_value            : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}AUD_IPW_TOP_IPW_AUD_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_100C    ipw_aud_003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dto0_sync_update          :  1,    //      0
                              : 31;    //   31:1 reserved
}AUD_IPW_TOP_IPW_AUD_003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1010    ipw_aud_004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dto1_add_value            : 32;    //  31: 0
}AUD_IPW_TOP_IPW_AUD_004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1014    ipw_aud_005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dto1_err_value            : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}AUD_IPW_TOP_IPW_AUD_005_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1018    ipw_aud_006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dto1_sync_update          :  1,    //      0
                              : 31;    //   31:1 reserved
}AUD_IPW_TOP_IPW_AUD_006_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_101C    ipw_aud_007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dto2_add_value            : 32;    //  31: 0
}AUD_IPW_TOP_IPW_AUD_007_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1020    ipw_aud_008 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dto2_err_value            : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}AUD_IPW_TOP_IPW_AUD_008_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1024    ipw_aud_009 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    dto2_sync_update          :  1,    //      0
                              : 31;    //   31:1 reserved
}AUD_IPW_TOP_IPW_AUD_009_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1028    ipw_aud_010 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    npwrupsram                :  8,    //   7: 0
                              : 24;    //   31:8 reserved
}AUD_IPW_TOP_IPW_AUD_010_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_102C    ipw_aud_011 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_te_0        :  1,    //      0
    reg_swrst_fly_te_1        :  1,    //      1
    reg_swrst_fly_te_2        :  1,    //      2
    reg_swrst_fly_te_3        :  1,    //      3
    reg_swrst_pes_te_4        :  1,    //      4
    reg_swrst_pes_te_5        :  1,    //      5
                              : 26;    //   31:6 reserved
}AUD_IPW_TOP_IPW_AUD_011_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1030    ipw_aud_012 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adpt_aud_1_cmd_vio_w  :  1,    //      0
    reg_adpt_aud_1_cmd_vio_r  :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_adpt_aud_1_wcmd_pnd_cnt: 7,    //  10: 4
                              :  1,    //     11 reserved
    reg_adpt_aud_1_rcmd_pnd_cnt: 7,    //  18:12
                              : 13;    //  31:19 reserved
}AUD_IPW_TOP_IPW_AUD_012_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1034    ipw_aud_013 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adpt_aud_1_cmd_gating_en_w: 1,    //   0
    reg_adpt_aud_1_cmd_gating_en_r: 1,    //   1
                              : 30;    //   31:2 reserved
}AUD_IPW_TOP_IPW_AUD_013_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1038    ipw_aud_014 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adpt_aud_2_cmd_vio_w  :  1,    //      0
    reg_adpt_aud_2_cmd_vio_r  :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_adpt_aud_2_wcmd_pnd_cnt: 7,    //  10: 4
                              :  1,    //     11 reserved
    reg_adpt_aud_2_rcmd_pnd_cnt: 7,    //  18:12
                              : 13;    //  31:19 reserved
}AUD_IPW_TOP_IPW_AUD_014_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_103C    ipw_aud_015 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adpt_aud_2_cmd_gating_en_w: 1,    //   0
    reg_adpt_aud_2_cmd_gating_en_r: 1,    //   1
                              : 30;    //   31:2 reserved
}AUD_IPW_TOP_IPW_AUD_015_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1FF8    ipw_aud_1022 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1022        : 32;    //  31: 0
}AUD_IPW_TOP_IPW_AUD_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1FFC    ipw_aud_1023 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_base_addr_1023        : 32;    //  31: 0
}AUD_IPW_TOP_IPW_AUD_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    AUD_IPW_TOP_IPW_AUD_000_O22A0_T        ipw_aud_000;             // 0xF309_1000
    AUD_IPW_TOP_IPW_AUD_001_O22A0_T        ipw_aud_001;             // 0xF309_1004
    AUD_IPW_TOP_IPW_AUD_002_O22A0_T        ipw_aud_002;             // 0xF309_1008
    AUD_IPW_TOP_IPW_AUD_003_O22A0_T        ipw_aud_003;             // 0xF309_100C
    AUD_IPW_TOP_IPW_AUD_004_O22A0_T        ipw_aud_004;             // 0xF309_1010
    AUD_IPW_TOP_IPW_AUD_005_O22A0_T        ipw_aud_005;             // 0xF309_1014
    AUD_IPW_TOP_IPW_AUD_006_O22A0_T        ipw_aud_006;             // 0xF309_1018
    AUD_IPW_TOP_IPW_AUD_007_O22A0_T        ipw_aud_007;             // 0xF309_101C
    AUD_IPW_TOP_IPW_AUD_008_O22A0_T        ipw_aud_008;             // 0xF309_1020
    AUD_IPW_TOP_IPW_AUD_009_O22A0_T        ipw_aud_009;             // 0xF309_1024
    AUD_IPW_TOP_IPW_AUD_010_O22A0_T        ipw_aud_010;             // 0xF309_1028
    AUD_IPW_TOP_IPW_AUD_011_O22A0_T        ipw_aud_011;             // 0xF309_102C
    AUD_IPW_TOP_IPW_AUD_012_O22A0_T        ipw_aud_012;             // 0xF309_1030
    AUD_IPW_TOP_IPW_AUD_013_O22A0_T        ipw_aud_013;             // 0xF309_1034
    AUD_IPW_TOP_IPW_AUD_014_O22A0_T        ipw_aud_014;             // 0xF309_1038
    AUD_IPW_TOP_IPW_AUD_015_O22A0_T        ipw_aud_015;             // 0xF309_103C
    UINT32                             _rsvd_00[1006];          // 0xF309_1040 ~ 0xF309_1FF4
    AUD_IPW_TOP_IPW_AUD_1022_O22A0_T       ipw_aud_1022;            // 0xF309_1FF8
    AUD_IPW_TOP_IPW_AUD_1023_O22A0_T       ipw_aud_1023;            // 0xF309_1FFC
}AUD_IPW_TOP_REG_O22A0_T;
/* 18 regs */

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

#define AUD_IPW_TOP_IPW_AUD_000_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define AUD_IPW_TOP_IPW_AUD_001_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define AUD_IPW_TOP_IPW_AUD_002_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define AUD_IPW_TOP_IPW_AUD_003_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define AUD_IPW_TOP_IPW_AUD_004_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define AUD_IPW_TOP_IPW_AUD_005_O22A0_T_OFF                     (BASEADDRESS+0x0014)
#define AUD_IPW_TOP_IPW_AUD_006_O22A0_T_OFF                     (BASEADDRESS+0x0018)
#define AUD_IPW_TOP_IPW_AUD_007_O22A0_T_OFF                     (BASEADDRESS+0x001C)
#define AUD_IPW_TOP_IPW_AUD_008_O22A0_T_OFF                     (BASEADDRESS+0x0020)
#define AUD_IPW_TOP_IPW_AUD_009_O22A0_T_OFF                     (BASEADDRESS+0x0024)
#define AUD_IPW_TOP_IPW_AUD_010_O22A0_T_OFF                     (BASEADDRESS+0x0028)
#define AUD_IPW_TOP_IPW_AUD_011_O22A0_T_OFF                     (BASEADDRESS+0x002C)
#define AUD_IPW_TOP_IPW_AUD_012_O22A0_T_OFF                     (BASEADDRESS+0x0030)
#define AUD_IPW_TOP_IPW_AUD_013_O22A0_T_OFF                     (BASEADDRESS+0x0034)
#define AUD_IPW_TOP_IPW_AUD_014_O22A0_T_OFF                     (BASEADDRESS+0x0038)
#define AUD_IPW_TOP_IPW_AUD_015_O22A0_T_OFF                     (BASEADDRESS+0x003C)
#define AUD_IPW_TOP_IPW_AUD_1022_O22A0_T_OFF                    (BASEADDRESS+0x0FF8)
#define AUD_IPW_TOP_IPW_AUD_1023_O22A0_T_OFF                    (BASEADDRESS+0x0FFC)

/*-----------------------------------------------------------------------------------------
    0xF309_1000    ipw_aud_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_0    : 32;    //  31: 0
    };
}AUD_IPW_TOP_IPW_AUD_000_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1004    ipw_aud_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 dto0_add_value     : 32;    //  31: 0
    };
}AUD_IPW_TOP_IPW_AUD_001_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1008    ipw_aud_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 dto0_err_value     : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}AUD_IPW_TOP_IPW_AUD_002_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_100C    ipw_aud_003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 dto0_sync_update   :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}AUD_IPW_TOP_IPW_AUD_003_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1010    ipw_aud_004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 dto1_add_value     : 32;    //  31: 0
    };
}AUD_IPW_TOP_IPW_AUD_004_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1014    ipw_aud_005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 dto1_err_value     : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}AUD_IPW_TOP_IPW_AUD_005_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1018    ipw_aud_006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 dto1_sync_update   :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}AUD_IPW_TOP_IPW_AUD_006_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_101C    ipw_aud_007 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 dto2_add_value     : 32;    //  31: 0
    };
}AUD_IPW_TOP_IPW_AUD_007_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1020    ipw_aud_008 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 dto2_err_value     : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}AUD_IPW_TOP_IPW_AUD_008_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1024    ipw_aud_009 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 dto2_sync_update   :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}AUD_IPW_TOP_IPW_AUD_009_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1028    ipw_aud_010 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 npwrupsram         :  8;    //   7: 0
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}AUD_IPW_TOP_IPW_AUD_010_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_102C    ipw_aud_011 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_te_0 :  1;    //      0
    UINT32 reg_swrst_fly_te_1 :  1;    //      1
    UINT32 reg_swrst_fly_te_2 :  1;    //      2
    UINT32 reg_swrst_fly_te_3 :  1;    //      3
    UINT32 reg_swrst_pes_te_4 :  1;    //      4
    UINT32 reg_swrst_pes_te_5 :  1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}AUD_IPW_TOP_IPW_AUD_011_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1030    ipw_aud_012 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adpt_aud_1_cmd_vio_w: 1;    //  0
    UINT32 reg_adpt_aud_1_cmd_vio_r: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_adpt_aud_1_wcmd_pnd_cnt: 7;    //  10:4
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_adpt_aud_1_rcmd_pnd_cnt: 7;    //  18:12
    UINT32 resvd02            : 13;    //  31:19 reserved
    };
}AUD_IPW_TOP_IPW_AUD_012_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1034    ipw_aud_013 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adpt_aud_1_cmd_gating_en_w: 1;    //  0
    UINT32 reg_adpt_aud_1_cmd_gating_en_r: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}AUD_IPW_TOP_IPW_AUD_013_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1038    ipw_aud_014 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adpt_aud_2_cmd_vio_w: 1;    //  0
    UINT32 reg_adpt_aud_2_cmd_vio_r: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_adpt_aud_2_wcmd_pnd_cnt: 7;    //  10:4
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_adpt_aud_2_rcmd_pnd_cnt: 7;    //  18:12
    UINT32 resvd02            : 13;    //  31:19 reserved
    };
}AUD_IPW_TOP_IPW_AUD_014_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_103C    ipw_aud_015 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adpt_aud_2_cmd_gating_en_w: 1;    //  0
    UINT32 reg_adpt_aud_2_cmd_gating_en_r: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}AUD_IPW_TOP_IPW_AUD_015_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1FF8    ipw_aud_1022 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1022 : 32;    //  31: 0
    };
}AUD_IPW_TOP_IPW_AUD_1022_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF309_1FFC    ipw_aud_1023 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_base_addr_1023 : 32;    //  31: 0
    };
}AUD_IPW_TOP_IPW_AUD_1023_O22A0_T;

/*-----------------------------------------------------------------------------------------
    ipw_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    AUD_IPW_TOP_IPW_AUD_000_O22A0_T        ipw_aud_000;             // 0xF309_1000
    AUD_IPW_TOP_IPW_AUD_001_O22A0_T        ipw_aud_001;             // 0xF309_1004
    AUD_IPW_TOP_IPW_AUD_002_O22A0_T        ipw_aud_002;             // 0xF309_1008
    AUD_IPW_TOP_IPW_AUD_003_O22A0_T        ipw_aud_003;             // 0xF309_100C
    AUD_IPW_TOP_IPW_AUD_004_O22A0_T        ipw_aud_004;             // 0xF309_1010
    AUD_IPW_TOP_IPW_AUD_005_O22A0_T        ipw_aud_005;             // 0xF309_1014
    AUD_IPW_TOP_IPW_AUD_006_O22A0_T        ipw_aud_006;             // 0xF309_1018
    AUD_IPW_TOP_IPW_AUD_007_O22A0_T        ipw_aud_007;             // 0xF309_101C
    AUD_IPW_TOP_IPW_AUD_008_O22A0_T        ipw_aud_008;             // 0xF309_1020
    AUD_IPW_TOP_IPW_AUD_009_O22A0_T        ipw_aud_009;             // 0xF309_1024
    AUD_IPW_TOP_IPW_AUD_010_O22A0_T        ipw_aud_010;             // 0xF309_1028
    AUD_IPW_TOP_IPW_AUD_011_O22A0_T        ipw_aud_011;             // 0xF309_102C
    AUD_IPW_TOP_IPW_AUD_012_O22A0_T        ipw_aud_012;             // 0xF309_1030
    AUD_IPW_TOP_IPW_AUD_013_O22A0_T        ipw_aud_013;             // 0xF309_1034
    AUD_IPW_TOP_IPW_AUD_014_O22A0_T        ipw_aud_014;             // 0xF309_1038
    AUD_IPW_TOP_IPW_AUD_015_O22A0_T        ipw_aud_015;             // 0xF309_103C
    UINT32                             _rsvd_00[1006];          // 0xF309_1040 ~ 0xF309_1FF4
    AUD_IPW_TOP_IPW_AUD_1022_O22A0_T       ipw_aud_1022;            // 0xF309_1FF8
    AUD_IPW_TOP_IPW_AUD_1023_O22A0_T       ipw_aud_1023;            // 0xF309_1FFC
}AUD_IPW_TOP_REG_O22A0_T;
/* 18 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_AUD_IPW_TOP_REG_H_

/* from 'O22_CTOP_IPW_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

