#ifndef _SRDS12TO3_REG_H_
#define _SRDS12TO3_REG_H_

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
    0x1_6000    swrst ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_chk1            :  1,    //      0
    reg_swrst_chk0            :  1,    //      1
    reg_swrst_ptg1            :  1,    //      2
    reg_swrst_ptg0            :  1,    //      3
    reg_swrst_sipo1_sd        :  1,    //      4
    reg_swrst_sipo1_tp        :  1,    //      5
    reg_swrst_sipo0_sd        :  1,    //      6
    reg_swrst_sipo0_tp        :  1,    //      7
    reg_swrst_piso1_sd        :  1,    //      8
    reg_swrst_piso1_tp        :  1,    //      9
    reg_swrst_piso0_sd        :  1,    //     10
    reg_swrst_piso0_tp        :  1,    //     11
    reg_swrst_fifo1           :  1,    //     12
    reg_swrst_fifo0           :  1,    //     13
                              : 18;    //  31:14 reserved
}SRDS12TO3_SWRST_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6004    mux ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_sipo1_sd_in       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sel_sipo0_sd_in       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_sel_piso1_sd_out      :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_sel_piso0_sd_out      :  2,    //  13:12
                              :  2,    //  15:14 reserved
    reg_sel_sipo1_tp_out      :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_sel_sipo0_tp_out      :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_sel_piso1_tp_in       :  2,    //  25:24
                              :  2,    //  27:26 reserved
    reg_sel_piso0_tp_in       :  1,    //     28
                              :  3;    //  31:29 reserved
}SRDS12TO3_MUX_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6008    align_cfg0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_idle_init_time1       :  8,    //   7: 0
    reg_idle_init_time0       :  8,    //  15: 8
    reg_idle_init_en1         :  1,    //     16
    reg_idle_init_en0         :  1,    //     17
    reg_check_sop1            :  1,    //     18
    reg_check_sop0            :  1,    //     19
    reg_delete_sop1           :  1,    //     20
    reg_delete_sop0           :  1,    //     21
    reg_invert_valid1         :  1,    //     22
    reg_invert_valid0         :  1,    //     23
    reg_fifo1_bypass          :  1,    //     24
    reg_fifo0_bypass          :  1,    //     25
    reg_piso1_gate_en         :  1,    //     26
    reg_piso0_gate_en         :  1,    //     27
    reg_mode_sipo1            :  1,    //     28
    reg_mode_sipo0            :  1,    //     29
    reg_mode_piso1            :  1,    //     30
    reg_mode_piso0            :  1;    //     31
}SRDS12TO3_ALIGN_CFG0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_600C    start_code ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_start_code0_ext0                : 8,    //  7: 0
                                        : 8,    // 15: 8 reserved
    reg_start_code0_ext1                : 8,    // 23:16
                                        : 8;    // 31:24 reserved
}SRDS12TO3_START_CODE_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6010    st_code23_en ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_st_code2_en_ext0                : 1,    //  0
    reg_st_code3_en_ext0                : 1,    //  1
    reg_tlv_en_ext0                     : 1,    //  2
                                        : 1,    //  3
    reg_st_code2_en_ext1                : 1,    //  4
    reg_st_code3_en_ext1                : 1,    //  5
    reg_tlv_en_ext1                     : 1,    //  6
                                        :25;    // 31: 7
}SRDS12TO3_ST_CODE23_EN_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6014    ptg_cfg ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_chk1_mode             :  1,    //      0
    reg_chk1_en               :  1,    //      1
                              :  2,    //   3: 2 reserved
    reg_chk0_mode             :  1,    //      4
    reg_chk0_en               :  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_ptg1_en               :  1,    //      8
    reg_ptg0_en               :  1,    //      9
                              :  2,    //  11:10 reserved
    result_valid1             :  1,    //     12
    result_valid0             :  1,    //     13
                              : 18;    //  31:14 reserved
}SRDS12TO3_PTG_CFG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6018    ptg_pkt0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tp_pkt_size_ext0      :  8,    //    7: 0
                              :  8,    //   15: 8 reserved
    reg_tp_pkt_size_ext1      :  8,    //   23:16
                              :  8;    //   31:24 reserved
}SRDS12TO3_PTG_PKT0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_601C    ptg_pkt1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tp_pkt_spacing        : 16,    //  15: 0
    reg_tp_pkt_num            : 16;    //  31:16
}SRDS12TO3_PTG_PKT1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6020    chk_tm0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_chk0_timer            : 32;    //  31: 0
}SRDS12TO3_CHK_TM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6024    chk_tm1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_chk1_timer            : 32;    //  31: 0
}SRDS12TO3_CHK_TM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6028    chk_cnt0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    err_pkt_cnt0              : 16,    //  15: 0
    rx_pkt_cnt0               : 16;    //  31:16
}SRDS12TO3_CHK_CNT0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_602C    chk_cnt1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    err_pkt_cnt1              : 16,    //  15: 0
    rx_pkt_cnt1               : 16;    //  31:16
}SRDS12TO3_CHK_CNT1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6030    start_2code ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_start_code2_ext0      :  8,    //    7: 0
                              :  8,    //   15: 8 reserved
    reg_start_code2_ext1      :  8,    //   23:16
                              :  8;    //   31:24 reserved
}SRDS12TO3_START_2CODE_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6034    start_3code ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_start_code3_ext0      :  8,    //   7: 0
                              :  8,    //  15: 8 reserved
    reg_start_code3_ext1      :  8,    //  23:16
                              :  8;    //  31:24 reserved
}SRDS12TO3_START_3CODE_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6038    ptg_start_code ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ptg_start_code        :  8,    //   7: 0
                              : 24;    //   31:8 reserved
}SRDS12TO3_PTG_START_CODE_O26A0_T;

/*-----------------------------------------------------------------------------------------
    srds12to3 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SRDS12TO3_SWRST_O26A0_T            swrst      ;             // 0x1_6000
    SRDS12TO3_MUX_O26A0_T              mux        ;             // 0x1_6004
    SRDS12TO3_ALIGN_CFG0_O26A0_T       align_cfg0 ;             // 0x1_6008
    SRDS12TO3_START_CODE_O26A0_T       start_code ;             // 0x1_600C
    SRDS12TO3_ST_CODE23_EN_O26A0_T     st_code23_en;            // 0x1_6010
    SRDS12TO3_PTG_CFG_O26A0_T          ptg_cfg    ;             // 0x1_6014
    SRDS12TO3_PTG_PKT0_O26A0_T         ptg_pkt0   ;             // 0x1_6018
    SRDS12TO3_PTG_PKT1_O26A0_T         ptg_pkt1   ;             // 0x1_601C
    SRDS12TO3_CHK_TM0_O26A0_T          chk_tm0    ;             // 0x1_6020
    SRDS12TO3_CHK_TM1_O26A0_T          chk_tm1    ;             // 0x1_6024
    SRDS12TO3_CHK_CNT0_O26A0_T         chk_cnt0   ;             // 0x1_6028
    SRDS12TO3_CHK_CNT1_O26A0_T         chk_cnt1   ;             // 0x1_602C
    SRDS12TO3_START_2CODE_O26A0_T      start_2code;             // 0x1_6030
    SRDS12TO3_START_3CODE_O26A0_T      start_3code;             // 0x1_6034
    SRDS12TO3_PTG_START_CODE_O26A0_T    ptg_start_code;         // 0x1_6038
}SRDS12TO3_REG_O26A0_T;
/* 15 regs */

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

#define SRDS12TO3_SWRST_O26A0_T_OFF                         (BASEADDRESS+0x0000)
#define SRDS12TO3_MUX_O26A0_T_OFF                           (BASEADDRESS+0x0004)
#define SRDS12TO3_ALIGN_CFG0_O26A0_T_OFF                    (BASEADDRESS+0x0008)
#define SRDS12TO3_START_CODE_O26A0_T_OFF                    (BASEADDRESS+0x000C)
#define SRDS12TO3_ST_CODE23_EN_O26A0_T_OFF                  (BASEADDRESS+0x0010)
#define SRDS12TO3_PTG_CFG_O26A0_T_OFF                       (BASEADDRESS+0x0014)
#define SRDS12TO3_PTG_PKT0_O26A0_T_OFF                      (BASEADDRESS+0x0018)
#define SRDS12TO3_PTG_PKT1_O26A0_T_OFF                      (BASEADDRESS+0x001C)
#define SRDS12TO3_CHK_TM0_O26A0_T_OFF                       (BASEADDRESS+0x0020)
#define SRDS12TO3_CHK_TM1_O26A0_T_OFF                       (BASEADDRESS+0x0024)
#define SRDS12TO3_CHK_CNT0_O26A0_T_OFF                      (BASEADDRESS+0x0028)
#define SRDS12TO3_CHK_CNT1_O26A0_T_OFF                      (BASEADDRESS+0x002C)
#define SRDS12TO3_START_2CODE_O26A0_T_OFF                   (BASEADDRESS+0x0030)
#define SRDS12TO3_START_3CODE_O26A0_T_OFF                   (BASEADDRESS+0x0034)
#define SRDS12TO3_PTG_START_CODE_O26A0_T_OFF                (BASEADDRESS+0x0038)

/*-----------------------------------------------------------------------------------------
    0x1_6000    swrst ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_chk1     :  1;    //      0
    UINT32 reg_swrst_chk0     :  1;    //      1
    UINT32 reg_swrst_ptg1     :  1;    //      2
    UINT32 reg_swrst_ptg0     :  1;    //      3
    UINT32 reg_swrst_sipo1_sd :  1;    //      4
    UINT32 reg_swrst_sipo1_tp :  1;    //      5
    UINT32 reg_swrst_sipo0_sd :  1;    //      6
    UINT32 reg_swrst_sipo0_tp :  1;    //      7
    UINT32 reg_swrst_piso1_sd :  1;    //      8
    UINT32 reg_swrst_piso1_tp :  1;    //      9
    UINT32 reg_swrst_piso0_sd :  1;    //     10
    UINT32 reg_swrst_piso0_tp :  1;    //     11
    UINT32 reg_swrst_fifo1    :  1;    //     12
    UINT32 reg_swrst_fifo0    :  1;    //     13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}SRDS12TO3_SWRST_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6004    mux ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel_sipo1_sd_in:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_sel_sipo0_sd_in:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_sel_piso1_sd_out: 2;    //   9: 8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_sel_piso0_sd_out: 2;    //  13:12
    UINT32 resvd03            :  2;    //  15:14 reserved
    UINT32 reg_sel_sipo1_tp_out: 2;    //  17:16
    UINT32 resvd04            :  2;    //  19:18 reserved
    UINT32 reg_sel_sipo0_tp_out: 3;    //  22:20
    UINT32 resvd05            :  1;    //     23 reserved
    UINT32 reg_sel_piso1_tp_in:  2;    //  25:24
    UINT32 resvd06            :  2;    //  27:26 reserved
    UINT32 reg_sel_piso0_tp_in:  1;    //     28
    UINT32 resvd07            :  3;    //  31:29 reserved
    };
}SRDS12TO3_MUX_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6008    align_cfg0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_idle_init_time1:  8;    //   7: 0
    UINT32 reg_idle_init_time0:  8;    //  15: 8
    UINT32 reg_idle_init_en1  :  1;    //     16
    UINT32 reg_idle_init_en0  :  1;    //     17
    UINT32 reg_check_sop1     :  1;    //     18
    UINT32 reg_check_sop0     :  1;    //     19
    UINT32 reg_delete_sop1    :  1;    //     20
    UINT32 reg_delete_sop0    :  1;    //     21
    UINT32 reg_invert_valid1  :  1;    //     22
    UINT32 reg_invert_valid0  :  1;    //     23
    UINT32 reg_fifo1_bypass   :  1;    //     24
    UINT32 reg_fifo0_bypass   :  1;    //     25
    UINT32 reg_piso1_gate_en  :  1;    //     26
    UINT32 reg_piso0_gate_en  :  1;    //     27
    UINT32 reg_mode_sipo1     :  1;    //     28
    UINT32 reg_mode_sipo0     :  1;    //     29
    UINT32 reg_mode_piso1     :  1;    //     30
    UINT32 reg_mode_piso0     :  1;    //     31
    };
}SRDS12TO3_ALIGN_CFG0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_600C    start_code ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_start_code0_ext0     :  8;    //   7: 0
    UINT32 resvd00                  :  8;    //   15:8 reserved
    UINT32 reg_start_code0_ext1     :  8;    //   23:16
    UINT32 resvd01                  :  8;    //   31:24 reserved
    };
}SRDS12TO3_START_CODE_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6010    st_code23_en ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_st_code2_en_ext0   :  1;    //      0
    UINT32 reg_st_code3_en_ext0   :  1;    //      1
    UINT32 reg_tlv_en_ext0        :  1;    //      2
    UINT32 resvd00                :  1;    //      3
    UINT32 reg_st_code2_en_ext1   :  1;    //      4
    UINT32 reg_st_code3_en_ext1   :  1;    //      5
    UINT32 reg_tlv_en_ext1        :  1;    //      6
    UINT32 resvd01                : 25;    //   31:7 reserved
    };
}SRDS12TO3_ST_CODE23_EN_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6014    ptg_cfg ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_chk1_mode      :  1;    //      0
    UINT32 reg_chk1_en        :  1;    //      1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_chk0_mode      :  1;    //      4
    UINT32 reg_chk0_en        :  1;    //      5
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_ptg1_en        :  1;    //      8
    UINT32 reg_ptg0_en        :  1;    //      9
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 result_valid1      :  1;    //     12
    UINT32 result_valid0      :  1;    //     13
    UINT32 resvd03            : 18;    //  31:14 reserved
    };
}SRDS12TO3_PTG_CFG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6018    ptg_pkt0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tp_pkt_size_ext0   :  8;    //   7: 0
    UINT32 resvd00                :  8;    //  15: 8 reserved
    UINT32 reg_tp_pkt_size_ext1   :  8;    //  23:16
    UINT32 resvd01                :  8;    //  31:24 reserved
    };
}SRDS12TO3_PTG_PKT0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_601C    ptg_pkt1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tp_pkt_spacing : 16;    //  15: 0
    UINT32 reg_tp_pkt_num     : 16;    //  31:16
    };
}SRDS12TO3_PTG_PKT1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6020    chk_tm0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_chk0_timer     : 32;    //  31: 0
    };
}SRDS12TO3_CHK_TM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6024    chk_tm1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_chk1_timer     : 32;    //  31: 0
    };
}SRDS12TO3_CHK_TM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6028    chk_cnt0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 err_pkt_cnt0       : 16;    //  15: 0
    UINT32 rx_pkt_cnt0        : 16;    //  31:16
    };
}SRDS12TO3_CHK_CNT0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_602C    chk_cnt1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 err_pkt_cnt1       : 16;    //  15: 0
    UINT32 rx_pkt_cnt1        : 16;    //  31:16
    };
}SRDS12TO3_CHK_CNT1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6030    start_2code ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_start_code2_ext0  :  8;    //   7: 0
    UINT32 resvd00               :  8;    //  15: 8 reserved
    UINT32 reg_start_code2_ext1  :  8;    //  23:16
    UINT32 resvd01               :  8;    //  31:24 reserved
    };
}SRDS12TO3_START_2CODE_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6034    start_3code ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_start_code2_ext0  :  8;    //   7: 0
    UINT32 resvd00               :  8;    //  15: 8 reserved
    UINT32 reg_start_code2_ext1  :  8;    //  23:16
    UINT32 resvd01               :  8;    //  31:24 reserved
    };
}SRDS12TO3_START_3CODE_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0x1_6038    ptg_start_code ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ptg_start_code :  8;    //   7: 0
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SRDS12TO3_PTG_START_CODE_O26A0_T;

/*-----------------------------------------------------------------------------------------
    srds12to3 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SRDS12TO3_SWRST_O26A0_T            swrst      ;             // 0x1_6000
    SRDS12TO3_MUX_O26A0_T              mux        ;             // 0x1_6004
    SRDS12TO3_ALIGN_CFG0_O26A0_T       align_cfg0 ;             // 0x1_6008
    SRDS12TO3_START_CODE_O26A0_T       start_code ;             // 0x1_600C
    SRDS12TO3_ST_CODE23_EN_O26A0_T     st_code23_en;            // 0x1_6010
    SRDS12TO3_PTG_CFG_O26A0_T          ptg_cfg    ;             // 0x1_6014
    SRDS12TO3_PTG_PKT0_O26A0_T         ptg_pkt0   ;             // 0x1_6018
    SRDS12TO3_PTG_PKT1_O26A0_T         ptg_pkt1   ;             // 0x1_601C
    SRDS12TO3_CHK_TM0_O26A0_T          chk_tm0    ;             // 0x1_6020
    SRDS12TO3_CHK_TM1_O26A0_T          chk_tm1    ;             // 0x1_6024
    SRDS12TO3_CHK_CNT0_O26A0_T         chk_cnt0   ;             // 0x1_6028
    SRDS12TO3_CHK_CNT1_O26A0_T         chk_cnt1   ;             // 0x1_602C
    SRDS12TO3_START_2CODE_O26A0_T      start_2code;             // 0x1_6030
    SRDS12TO3_START_3CODE_O26A0_T      start_3code;             // 0x1_6034
    SRDS12TO3_PTG_START_CODE_O26A0_T    ptg_start_code;         // 0x1_6038
}SRDS12TO3_REG_O26A0_T;
/* 15 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SRDS12TO3_REG_H_

/* from 'ION_CTOP_Register_Manual.xlsx'  2025.4.17  KJH by LGSiCRDV V3.1C*/
