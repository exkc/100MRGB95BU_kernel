#ifndef _SB_CTRL_FMGSESB_REG_O24A0_H_
#define _SB_CTRL_FMGSESB_REG_O24A0_H_

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
    0xCC53_1000    sbw_fmgse_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc0_w_port_sel       :  3,    //   2: 0
                              : 13,    //  15: 3 reserved
    reg_fmc0_r_port_sel       :  3,    //  18:16
                              : 13;    //  31:19 reserved
}SB_CTRL_FMGSESB_SBW_FMGSE_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1004    sbw_fmgse_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc1_w_port_sel       :  3,    //   2: 0
                              : 13,    //  15: 3 reserved
    reg_fmc1_r_port_sel       :  3,    //  18:16
                              : 13;    //  31:19 reserved
}SB_CTRL_FMGSESB_SBW_FMGSE_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1008    sbw_fmgse_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc2_w_port_sel       :  3,    //   2: 0
                              : 13,    //  15: 3 reserved
    reg_fmc2_r_port_sel       :  3,    //  18:16
                              : 13;    //  31:19 reserved
}SB_CTRL_FMGSESB_SBW_FMGSE_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_100C    sbw_fmgse_003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc3_w_port_sel       :  3,    //   2: 0
                              : 13,    //  15: 3 reserved
    reg_fmc3_r_port_sel       :  3,    //  18:16
                              : 13;    //  31:19 reserved
}SB_CTRL_FMGSESB_SBW_FMGSE_003_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1010    sbw_fmgse_004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc0_w_port_sel       :  3,    //   2: 0
                              : 13,    //  15: 3 reserved
    reg_gsc0_r_port_sel       :  3,    //  18:16
                              : 13;    //  31:19 reserved
}SB_CTRL_FMGSESB_SBW_FMGSE_004_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1014    sbw_fmgse_005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc1_w_port_sel       :  3,    //   2: 0
                              : 13,    //  15: 3 reserved
    reg_gsc1_r_port_sel       :  3,    //  18:16
                              : 13;    //  31:19 reserved
}SB_CTRL_FMGSESB_SBW_FMGSE_005_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1018    sbw_fmgse_006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sre0_w_port_sel       :  3,    //   2: 0
                              : 13,    //  15: 3 reserved
    reg_sre0_r_port_sel       :  3,    //  18:16
                              : 13;    //  31:19 reserved
}SB_CTRL_FMGSESB_SBW_FMGSE_006_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_101C    sbw_fmgse_007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sre1_w_port_sel       :  3,    //   2: 0
                              : 13,    //  15: 3 reserved
    reg_sre1_r_port_sel       :  3,    //  18:16
                              : 13;    //  31:19 reserved
}SB_CTRL_FMGSESB_SBW_FMGSE_007_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10D0    user_bit_cntl_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc0_awuser           :  4,    //   3: 0
    reg_fmc0_aruser           :  4,    //   7: 4
    reg_fmc0_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_fmc0_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_FMGSESB_USER_BIT_CNTL_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10D4    user_bit_cntl_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc1_awuser           :  4,    //   3: 0
    reg_fmc1_aruser           :  4,    //   7: 4
    reg_fmc1_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_fmc1_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_FMGSESB_USER_BIT_CNTL_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10D8    user_bit_cntl_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc2_awuser           :  4,    //   3: 0
    reg_fmc2_aruser           :  4,    //   7: 4
    reg_fmc2_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_fmc2_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_FMGSESB_USER_BIT_CNTL_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10DC    user_bit_cntl_003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fmc3_awuser           :  4,    //   3: 0
    reg_fmc3_aruser           :  4,    //   7: 4
    reg_fmc3_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_fmc3_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_FMGSESB_USER_BIT_CNTL_003_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10E0    user_bit_cntl_004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc0_awuser           :  4,    //   3: 0
    reg_gsc0_aruser           :  4,    //   7: 4
    reg_gsc0_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_gsc0_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_FMGSESB_USER_BIT_CNTL_004_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10E4    user_bit_cntl_005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gsc1_awuser           :  4,    //   3: 0
    reg_gsc1_aruser           :  4,    //   7: 4
    reg_gsc1_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_gsc1_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_FMGSESB_USER_BIT_CNTL_005_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10E8    user_bit_cntl_006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sre0_awuser           :  4,    //   3: 0
    reg_sre0_aruser           :  4,    //   7: 4
    reg_sre0_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_sre0_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_FMGSESB_USER_BIT_CNTL_006_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10EC    user_bit_cntl_007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sre1_awuser           :  4,    //   3: 0
    reg_sre1_aruser           :  4,    //   7: 4
    reg_sre1_awuser_sel       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_sre1_aruser_sel       :  1,    //     12
                              : 19;    //  31:13 reserved
}SB_CTRL_FMGSESB_USER_BIT_CNTL_007_O24A0_T;

/*-----------------------------------------------------------------------------------------
    sb_ctrl_fmgsesb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SB_CTRL_FMGSESB_SBW_FMGSE_000_O24A0_T    sbw_fmgse_000;     // 0xCC53_1000
    SB_CTRL_FMGSESB_SBW_FMGSE_001_O24A0_T    sbw_fmgse_001;     // 0xCC53_1004
    SB_CTRL_FMGSESB_SBW_FMGSE_002_O24A0_T    sbw_fmgse_002;     // 0xCC53_1008
    SB_CTRL_FMGSESB_SBW_FMGSE_003_O24A0_T    sbw_fmgse_003;     // 0xCC53_100C
    SB_CTRL_FMGSESB_SBW_FMGSE_004_O24A0_T    sbw_fmgse_004;     // 0xCC53_1010
    SB_CTRL_FMGSESB_SBW_FMGSE_005_O24A0_T    sbw_fmgse_005;     // 0xCC53_1014
    SB_CTRL_FMGSESB_SBW_FMGSE_006_O24A0_T    sbw_fmgse_006;     // 0xCC53_1018
    SB_CTRL_FMGSESB_SBW_FMGSE_007_O24A0_T    sbw_fmgse_007;     // 0xCC53_101C
    UINT32                             _rsvd_00[44];            // 0xCC53_1020 ~ 0xCC53_10CC
    SB_CTRL_FMGSESB_USER_BIT_CNTL_000_O24A0_T    user_bit_cntl_000;    // 0xCC53_10D0
    SB_CTRL_FMGSESB_USER_BIT_CNTL_001_O24A0_T    user_bit_cntl_001;    // 0xCC53_10D4
    SB_CTRL_FMGSESB_USER_BIT_CNTL_002_O24A0_T    user_bit_cntl_002;    // 0xCC53_10D8
    SB_CTRL_FMGSESB_USER_BIT_CNTL_003_O24A0_T    user_bit_cntl_003;    // 0xCC53_10DC
    SB_CTRL_FMGSESB_USER_BIT_CNTL_004_O24A0_T    user_bit_cntl_004;    // 0xCC53_10E0
    SB_CTRL_FMGSESB_USER_BIT_CNTL_005_O24A0_T    user_bit_cntl_005;    // 0xCC53_10E4
    SB_CTRL_FMGSESB_USER_BIT_CNTL_006_O24A0_T    user_bit_cntl_006;    // 0xCC53_10E8
    SB_CTRL_FMGSESB_USER_BIT_CNTL_007_O24A0_T    user_bit_cntl_007;    // 0xCC53_10EC
}SB_CTRL_FMGSESB_REG_O24A0_T;
/* 16 regs */

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

#define SB_CTRL_FMGSESB_SBW_FMGSE_000_O24A0_T_OFF           (BASEADDRESS+0x0000)
#define SB_CTRL_FMGSESB_SBW_FMGSE_001_O24A0_T_OFF           (BASEADDRESS+0x0004)
#define SB_CTRL_FMGSESB_SBW_FMGSE_002_O24A0_T_OFF           (BASEADDRESS+0x0008)
#define SB_CTRL_FMGSESB_SBW_FMGSE_003_O24A0_T_OFF           (BASEADDRESS+0x000C)
#define SB_CTRL_FMGSESB_SBW_FMGSE_004_O24A0_T_OFF           (BASEADDRESS+0x0010)
#define SB_CTRL_FMGSESB_SBW_FMGSE_005_O24A0_T_OFF           (BASEADDRESS+0x0014)
#define SB_CTRL_FMGSESB_SBW_FMGSE_006_O24A0_T_OFF           (BASEADDRESS+0x0018)
#define SB_CTRL_FMGSESB_SBW_FMGSE_007_O24A0_T_OFF           (BASEADDRESS+0x001C)
#define SB_CTRL_FMGSESB_USER_BIT_CNTL_000_O24A0_T_OFF       (BASEADDRESS+0x00D0)
#define SB_CTRL_FMGSESB_USER_BIT_CNTL_001_O24A0_T_OFF       (BASEADDRESS+0x00D4)
#define SB_CTRL_FMGSESB_USER_BIT_CNTL_002_O24A0_T_OFF       (BASEADDRESS+0x00D8)
#define SB_CTRL_FMGSESB_USER_BIT_CNTL_003_O24A0_T_OFF       (BASEADDRESS+0x00DC)
#define SB_CTRL_FMGSESB_USER_BIT_CNTL_004_O24A0_T_OFF       (BASEADDRESS+0x00E0)
#define SB_CTRL_FMGSESB_USER_BIT_CNTL_005_O24A0_T_OFF       (BASEADDRESS+0x00E4)
#define SB_CTRL_FMGSESB_USER_BIT_CNTL_006_O24A0_T_OFF       (BASEADDRESS+0x00E8)
#define SB_CTRL_FMGSESB_USER_BIT_CNTL_007_O24A0_T_OFF       (BASEADDRESS+0x00EC)

/*-----------------------------------------------------------------------------------------
    0xCC53_1000    sbw_fmgse_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmc0_w_port_sel:  3;    //   2: 0
    UINT32 resvd00            : 13;    //  15: 3 reserved
    UINT32 reg_fmc0_r_port_sel:  3;    //  18:16
    UINT32 resvd01            : 13;    //  31:19 reserved
    };
}SB_CTRL_FMGSESB_SBW_FMGSE_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1004    sbw_fmgse_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmc1_w_port_sel:  3;    //   2: 0
    UINT32 resvd00            : 13;    //  15: 3 reserved
    UINT32 reg_fmc1_r_port_sel:  3;    //  18:16
    UINT32 resvd01            : 13;    //  31:19 reserved
    };
}SB_CTRL_FMGSESB_SBW_FMGSE_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1008    sbw_fmgse_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmc2_w_port_sel:  3;    //   2: 0
    UINT32 resvd00            : 13;    //  15: 3 reserved
    UINT32 reg_fmc2_r_port_sel:  3;    //  18:16
    UINT32 resvd01            : 13;    //  31:19 reserved
    };
}SB_CTRL_FMGSESB_SBW_FMGSE_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_100C    sbw_fmgse_003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmc3_w_port_sel:  3;    //   2: 0
    UINT32 resvd00            : 13;    //  15: 3 reserved
    UINT32 reg_fmc3_r_port_sel:  3;    //  18:16
    UINT32 resvd01            : 13;    //  31:19 reserved
    };
}SB_CTRL_FMGSESB_SBW_FMGSE_003_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1010    sbw_fmgse_004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gsc0_w_port_sel:  3;    //   2: 0
    UINT32 resvd00            : 13;    //  15: 3 reserved
    UINT32 reg_gsc0_r_port_sel:  3;    //  18:16
    UINT32 resvd01            : 13;    //  31:19 reserved
    };
}SB_CTRL_FMGSESB_SBW_FMGSE_004_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1014    sbw_fmgse_005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gsc1_w_port_sel:  3;    //   2: 0
    UINT32 resvd00            : 13;    //  15: 3 reserved
    UINT32 reg_gsc1_r_port_sel:  3;    //  18:16
    UINT32 resvd01            : 13;    //  31:19 reserved
    };
}SB_CTRL_FMGSESB_SBW_FMGSE_005_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_1018    sbw_fmgse_006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sre0_w_port_sel:  3;    //   2: 0
    UINT32 resvd00            : 13;    //  15: 3 reserved
    UINT32 reg_sre0_r_port_sel:  3;    //  18:16
    UINT32 resvd01            : 13;    //  31:19 reserved
    };
}SB_CTRL_FMGSESB_SBW_FMGSE_006_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_101C    sbw_fmgse_007 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sre1_w_port_sel:  3;    //   2: 0
    UINT32 resvd00            : 13;    //  15: 3 reserved
    UINT32 reg_sre1_r_port_sel:  3;    //  18:16
    UINT32 resvd01            : 13;    //  31:19 reserved
    };
}SB_CTRL_FMGSESB_SBW_FMGSE_007_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10D0    user_bit_cntl_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmc0_awuser    :  4;    //   3: 0
    UINT32 reg_fmc0_aruser    :  4;    //   7: 4
    UINT32 reg_fmc0_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_fmc0_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_FMGSESB_USER_BIT_CNTL_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10D4    user_bit_cntl_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmc1_awuser    :  4;    //   3: 0
    UINT32 reg_fmc1_aruser    :  4;    //   7: 4
    UINT32 reg_fmc1_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_fmc1_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_FMGSESB_USER_BIT_CNTL_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10D8    user_bit_cntl_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmc2_awuser    :  4;    //   3: 0
    UINT32 reg_fmc2_aruser    :  4;    //   7: 4
    UINT32 reg_fmc2_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_fmc2_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_FMGSESB_USER_BIT_CNTL_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10DC    user_bit_cntl_003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fmc3_awuser    :  4;    //   3: 0
    UINT32 reg_fmc3_aruser    :  4;    //   7: 4
    UINT32 reg_fmc3_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_fmc3_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_FMGSESB_USER_BIT_CNTL_003_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10E0    user_bit_cntl_004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gsc0_awuser    :  4;    //   3: 0
    UINT32 reg_gsc0_aruser    :  4;    //   7: 4
    UINT32 reg_gsc0_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_gsc0_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_FMGSESB_USER_BIT_CNTL_004_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10E4    user_bit_cntl_005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gsc1_awuser    :  4;    //   3: 0
    UINT32 reg_gsc1_aruser    :  4;    //   7: 4
    UINT32 reg_gsc1_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_gsc1_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_FMGSESB_USER_BIT_CNTL_005_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10E8    user_bit_cntl_006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sre0_awuser    :  4;    //   3: 0
    UINT32 reg_sre0_aruser    :  4;    //   7: 4
    UINT32 reg_sre0_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_sre0_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_FMGSESB_USER_BIT_CNTL_006_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC53_10EC    user_bit_cntl_007 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sre1_awuser    :  4;    //   3: 0
    UINT32 reg_sre1_aruser    :  4;    //   7: 4
    UINT32 reg_sre1_awuser_sel:  1;    //      8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_sre1_aruser_sel:  1;    //     12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}SB_CTRL_FMGSESB_USER_BIT_CNTL_007_O24A0_T;

/*-----------------------------------------------------------------------------------------
    sb_ctrl_fmgsesb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SB_CTRL_FMGSESB_SBW_FMGSE_000_O24A0_T    sbw_fmgse_000;     // 0xCC53_1000
    SB_CTRL_FMGSESB_SBW_FMGSE_001_O24A0_T    sbw_fmgse_001;     // 0xCC53_1004
    SB_CTRL_FMGSESB_SBW_FMGSE_002_O24A0_T    sbw_fmgse_002;     // 0xCC53_1008
    SB_CTRL_FMGSESB_SBW_FMGSE_003_O24A0_T    sbw_fmgse_003;     // 0xCC53_100C
    SB_CTRL_FMGSESB_SBW_FMGSE_004_O24A0_T    sbw_fmgse_004;     // 0xCC53_1010
    SB_CTRL_FMGSESB_SBW_FMGSE_005_O24A0_T    sbw_fmgse_005;     // 0xCC53_1014
    SB_CTRL_FMGSESB_SBW_FMGSE_006_O24A0_T    sbw_fmgse_006;     // 0xCC53_1018
    SB_CTRL_FMGSESB_SBW_FMGSE_007_O24A0_T    sbw_fmgse_007;     // 0xCC53_101C
    UINT32                             _rsvd_00[44];            // 0xCC53_1020 ~ 0xCC53_10CC
    SB_CTRL_FMGSESB_USER_BIT_CNTL_000_O24A0_T    user_bit_cntl_000;    // 0xCC53_10D0
    SB_CTRL_FMGSESB_USER_BIT_CNTL_001_O24A0_T    user_bit_cntl_001;    // 0xCC53_10D4
    SB_CTRL_FMGSESB_USER_BIT_CNTL_002_O24A0_T    user_bit_cntl_002;    // 0xCC53_10D8
    SB_CTRL_FMGSESB_USER_BIT_CNTL_003_O24A0_T    user_bit_cntl_003;    // 0xCC53_10DC
    SB_CTRL_FMGSESB_USER_BIT_CNTL_004_O24A0_T    user_bit_cntl_004;    // 0xCC53_10E0
    SB_CTRL_FMGSESB_USER_BIT_CNTL_005_O24A0_T    user_bit_cntl_005;    // 0xCC53_10E4
    SB_CTRL_FMGSESB_USER_BIT_CNTL_006_O24A0_T    user_bit_cntl_006;    // 0xCC53_10E8
    SB_CTRL_FMGSESB_USER_BIT_CNTL_007_O24A0_T    user_bit_cntl_007;    // 0xCC53_10EC
}SB_CTRL_FMGSESB_REG_O24A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SB_CTRL_FMGSESB_REG_H_

/* from 'O24_IPW_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

