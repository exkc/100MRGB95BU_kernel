#ifndef _ION_TOP_CTRL_REG_H_
#define _ION_TOP_CTRL_REG_H_

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
    0x1_0000    reg33to18_trim ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_reg33to18_lv_d18      :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}ION_TOP_CTRL_REG33TO18_TRIM_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0004    reg33to18_rstb ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_por_rstb_out_reg      :  1,    //      0
                              : 31;    //   31:1 reserved
}ION_TOP_CTRL_REG33TO18_RSTB_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0010    ci_intr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ci_intr               :  1,    //      0
                              : 31;    //   31:1 reserved
}ION_TOP_CTRL_CI_INTR_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0014    ci_intr_sel ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ci_intr_sel           :  1,    //      0
                              : 31;    //   31:1 reserved
}ION_TOP_CTRL_CI_INTR_SEL_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0018    srds_intr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_intr_tstmp_err0       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_intr_tstmp_err1       :  1,    //      4
                              : 27;    //   31:5 reserved
}ION_TOP_CTRL_SRDS_INTR_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0020    crg_ctrl_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_i_sel_tu_io_sd07      :  1,    //      0
    reg_c_sel_tu_io_sd07      :  1,    //      1
    reg_i_sel_tu_io_sd06      :  1,    //      2
    reg_c_sel_tu_io_sd06      :  1,    //      3
    reg_i_sel_tu_io_sd05      :  1,    //      4
    reg_c_sel_tu_io_sd05      :  1,    //      5
    reg_i_sel_tu_io_sd04      :  1,    //      6
    reg_c_sel_tu_io_sd04      :  1,    //      7
    reg_i_sel_tu_io_sd03      :  1,    //      8
    reg_c_sel_tu_io_sd03      :  1,    //      9
    reg_i_sel_tu_io_sd02      :  1,    //     10
    reg_c_sel_tu_io_sd02      :  1,    //     11
    reg_i_sel_tu_io_sd01      :  1,    //     12
    reg_c_sel_tu_io_sd01      :  1,    //     13
    reg_i_sel_tu_io_sd00      :  1,    //     14
    reg_c_sel_tu_io_sd00      :  1,    //     15
                              : 16;    //  31:16 reserved
}ION_TOP_CTRL_CRG_CTRL_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0024    crg_ctrl_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_clk_sel          :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_cicam_clk_sel         :  1,    //      4
                              : 27;    //   31:5 reserved
}ION_TOP_CTRL_CRG_CTRL_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0030    rev_id_ion_a0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rev_id_out00          :  1,    //      0
    reg_rev_id_out01          :  1,    //      1
    reg_rev_id_out02          :  1,    //      2
    reg_rev_id_out03          :  1,    //      3
    reg_rev_id_out04          :  1,    //      4
    reg_rev_id_out05          :  1,    //      5
    reg_rev_id_out06          :  1,    //      6
    reg_rev_id_out07          :  1,    //      7
                              : 24;    //   31:8 reserved
}ION_TOP_CTRL_REV_ID_ION_A0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0040    ion_id ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ion_id                : 32;    //  31: 0
}ION_TOP_CTRL_ION_ID_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0044    ion_test_reg ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_reg_test              : 32;    //  31: 0
}ION_TOP_CTRL_ION_TEST_REG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0050    ion_ssp_cs_reg ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ssp_cs_control        :  1,    //      0
                              : 31;    //   31:1 reserved
}ION_TOP_CTRL_ION_SSP_CS_REG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    top_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
ION_TOP_CTRL_REG33TO18_TRIM_O26A0_T    reg33to18_trim;          // 0x1_0000
ION_TOP_CTRL_REG33TO18_RSTB_O26A0_T    reg33to18_rstb;          // 0x1_0004
    UINT32                             _rsvd_00[2];             // 0x1_0008 ~ 0x1_000C
ION_TOP_CTRL_CI_INTR_O26A0_T           ci_intr    ;             // 0x1_0010
ION_TOP_CTRL_CI_INTR_SEL_O26A0_T       ci_intr_sel;             // 0x1_0014
ION_TOP_CTRL_SRDS_INTR_O26A0_T         srds_intr  ;             // 0x1_0018
    UINT32                             _rsvd_01[1];             // 0x1_001C
ION_TOP_CTRL_CRG_CTRL_1_O26A0_T        crg_ctrl_1 ;             // 0x1_0020
ION_TOP_CTRL_CRG_CTRL_2_O26A0_T        crg_ctrl_2 ;             // 0x1_0024
    UINT32                             _rsvd_02[2];             // 0x1_0028 ~ 0x1_002C
ION_TOP_CTRL_REV_ID_ION_A0_O26A0_T     rev_id_ion_a0;           // 0x1_0030
    UINT32                             _rsvd_03[3];             // 0x1_0034 ~ 0x1_003C
ION_TOP_CTRL_ION_ID_O26A0_T            ion_id     ;             // 0x1_0040
ION_TOP_CTRL_ION_TEST_REG_O26A0_T      ion_test_reg;            // 0x1_0044
    UINT32                             _rsvd_04[2];             // 0x1_0048 ~ 0x1_004C
ION_TOP_CTRL_ION_SSP_CS_REG_O26A0_T    ion_ssp_cs_reg;          // 0x1_0050
}ION_TOP_CTRL_REG_O26A0_T;
/* 11 regs */

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

#define ION_TOP_CTRL_REG33TO18_TRIM_O26A0_T_OFF             (BASEADDRESS+0x0000)
#define ION_TOP_CTRL_REG33TO18_RSTB_O26A0_T_OFF             (BASEADDRESS+0x0004)
#define ION_TOP_CTRL_CI_INTR_O26A0_T_OFF                    (BASEADDRESS+0x0010)
#define ION_TOP_CTRL_CI_INTR_SEL_O26A0_T_OFF                (BASEADDRESS+0x0014)
#define ION_TOP_CTRL_SRDS_INTR_O26A0_T_OFF                  (BASEADDRESS+0x0018)
#define ION_TOP_CTRL_CRG_CTRL_1_O26A0_T_OFF                 (BASEADDRESS+0x0020)
#define ION_TOP_CTRL_CRG_CTRL_2_O26A0_T_OFF                 (BASEADDRESS+0x0024)
#define ION_TOP_CTRL_REV_ID_ION_A0_O26A0_T_OFF              (BASEADDRESS+0x0030)
#define ION_TOP_CTRL_ION_ID_O26A0_T_OFF                     (BASEADDRESS+0x0040)
#define ION_TOP_CTRL_ION_TEST_REG_O26A0_T_OFF               (BASEADDRESS+0x0044)
#define ION_TOP_CTRL_ION_SSP_CS_REG_O26A0_T_OFF             (BASEADDRESS+0x0050)

/*-----------------------------------------------------------------------------------------
    0x1_0000    reg33to18_trim ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_reg33to18_lv_d18: 4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}ION_TOP_CTRL_REG33TO18_TRIM_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0004    reg33to18_rstb ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_por_rstb_out_reg: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}ION_TOP_CTRL_REG33TO18_RSTB_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0010    ci_intr ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ci_intr        :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}ION_TOP_CTRL_CI_INTR_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0014    ci_intr_sel ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ci_intr_sel    :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}ION_TOP_CTRL_CI_INTR_SEL_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0018    srds_intr ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_intr_tstmp_err0:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_intr_tstmp_err1:  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}ION_TOP_CTRL_SRDS_INTR_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0020    crg_ctrl_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_i_sel_tu_io_sd07: 1;    //      0
    UINT32 reg_c_sel_tu_io_sd07: 1;    //      1
    UINT32 reg_i_sel_tu_io_sd06: 1;    //      2
    UINT32 reg_c_sel_tu_io_sd06: 1;    //      3
    UINT32 reg_i_sel_tu_io_sd05: 1;    //      4
    UINT32 reg_c_sel_tu_io_sd05: 1;    //      5
    UINT32 reg_i_sel_tu_io_sd04: 1;    //      6
    UINT32 reg_c_sel_tu_io_sd04: 1;    //      7
    UINT32 reg_i_sel_tu_io_sd03: 1;    //      8
    UINT32 reg_c_sel_tu_io_sd03: 1;    //      9
    UINT32 reg_i_sel_tu_io_sd02: 1;    //     10
    UINT32 reg_c_sel_tu_io_sd02: 1;    //     11
    UINT32 reg_i_sel_tu_io_sd01: 1;    //     12
    UINT32 reg_c_sel_tu_io_sd01: 1;    //     13
    UINT32 reg_i_sel_tu_io_sd00: 1;    //     14
    UINT32 reg_c_sel_tu_io_sd00: 1;    //     15
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}ION_TOP_CTRL_CRG_CTRL_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0024    crg_ctrl_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_clk_sel   :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_cicam_clk_sel  :  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}ION_TOP_CTRL_CRG_CTRL_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0030    rev_id_ion_a0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_rev_id_out00   :  1;    //      0
    UINT32 reg_rev_id_out01   :  1;    //      1
    UINT32 reg_rev_id_out02   :  1;    //      2
    UINT32 reg_rev_id_out03   :  1;    //      3
    UINT32 reg_rev_id_out04   :  1;    //      4
    UINT32 reg_rev_id_out05   :  1;    //      5
    UINT32 reg_rev_id_out06   :  1;    //      6
    UINT32 reg_rev_id_out07   :  1;    //      7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}ION_TOP_CTRL_REV_ID_ION_A0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0040    ion_id ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ion_id         : 32;    //  31: 0
    };
}ION_TOP_CTRL_ION_ID_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0044    ion_test_reg ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_reg_test       : 32;    //  31: 0
    };
}ION_TOP_CTRL_ION_TEST_REG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_0050    ion_ssp_cs_reg ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ssp_cs_control :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}ION_TOP_CTRL_ION_SSP_CS_REG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    top_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
ION_TOP_CTRL_REG33TO18_TRIM_O26A0_T    reg33to18_trim;          // 0x1_0000
ION_TOP_CTRL_REG33TO18_RSTB_O26A0_T    reg33to18_rstb;          // 0x1_0004
    UINT32                             _rsvd_00[2];             // 0x1_0008 ~ 0x1_000C
ION_TOP_CTRL_CI_INTR_O26A0_T           ci_intr    ;             // 0x1_0010
ION_TOP_CTRL_CI_INTR_SEL_O26A0_T       ci_intr_sel;             // 0x1_0014
ION_TOP_CTRL_SRDS_INTR_O26A0_T         srds_intr  ;             // 0x1_0018
    UINT32                             _rsvd_01[1];             // 0x1_001C
ION_TOP_CTRL_CRG_CTRL_1_O26A0_T        crg_ctrl_1 ;             // 0x1_0020
ION_TOP_CTRL_CRG_CTRL_2_O26A0_T        crg_ctrl_2 ;             // 0x1_0024
    UINT32                             _rsvd_02[2];             // 0x1_0028 ~ 0x1_002C
ION_TOP_CTRL_REV_ID_ION_A0_O26A0_T     rev_id_ion_a0;           // 0x1_0030
    UINT32                             _rsvd_03[3];             // 0x1_0034 ~ 0x1_003C
ION_TOP_CTRL_ION_ID_O26A0_T            ion_id     ;             // 0x1_0040
ION_TOP_CTRL_ION_TEST_REG_O26A0_T      ion_test_reg;            // 0x1_0044
    UINT32                             _rsvd_04[2];             // 0x1_0048 ~ 0x1_004C
ION_TOP_CTRL_ION_SSP_CS_REG_O26A0_T    ion_ssp_cs_reg;          // 0x1_0050
}ION_TOP_CTRL_REG_O26A0_T;
/* 11 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // ION_TOP_CTRL_REG_H_

/* from 'ION_CTOP_Register_Manual.xlsx'  2025.4.17  KJH by LGSiCRDV V3.1C*/

