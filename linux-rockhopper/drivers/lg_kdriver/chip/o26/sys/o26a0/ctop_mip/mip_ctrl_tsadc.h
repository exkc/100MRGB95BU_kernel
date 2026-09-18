#ifndef _MIP_CTRL_TSADC_REG_O26A0_H_
#define _MIP_CTRL_TSADC_REG_O26A0_H_

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
    0xC404_3000    ts_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ts_pdb                    :  1,    //      0
    ts_trim                   :  8,    //   8: 1
    ts_sel_clk                :  3,    //  11: 9
    ts_sel_osr                :  2,    //  13:12
    ts_sel_cic                :  1,    //     14
    ts_sel_chop               :  1,    //     15
    ts_vdd_det                :  1,    //     16
    ts_12b_out                :  1,    //     17
    tsc_din_shift_en          :  1,    //     18
    tsc_dout_avg_en           :  1,    //     19
    tsc_dout_iir_en           :  1,    //     20
    tsc_intr_th_mode          :  1,    //     21
    tsc_intr_th_en            :  1,    //     22
    tsc_intr_th_urgent_en     :  1,    //     23
    tsc_intr_raw_en           :  1,    //     24
    tsc_iir_coef              :  4,    //  28:25
    mux_on                    :  2,    //  30:29
                              :  1;    //  31:31 reserved
}MIP_CTRL_TSADC_TS_CTRL_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_3004    ts_th_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tsc_th_0                  : 16,    //  15: 0
    tsc_th_1                  : 16;    //  31:16
}MIP_CTRL_TSADC_TS_TH_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_3008    ts_th_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tsc_th_2                  : 16,    //  15: 0
    tsc_th_3                  : 16;    //  31:16
}MIP_CTRL_TSADC_TS_TH_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_300C    ts_th_urgent ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tsc_th_urgent             : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}MIP_CTRL_TSADC_TS_TH_URGENT_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_3010    ts_stat ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tsc_stat_raw              :  1,    //      0
    tsc_stat_th_0             :  1,    //      1
    tsc_stat_th_1             :  1,    //      2
    tsc_stat_th_2             :  1,    //      3
    tsc_stat_th_3             :  1,    //      4
    tsc_stat_th_urgent        :  1,    //      5
                              : 26;    //   31:6 reserved
}MIP_CTRL_TSADC_TS_STAT_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_3014    ts_data ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tsc_dout                  : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}MIP_CTRL_TSADC_TS_DATA_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_3018    ts_dig_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ts_dig_ctrl               : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}MIP_CTRL_TSADC_TS_DIG_CTRL_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_tsadc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_TSADC_TS_CTRL_O26A0_T     ts_ctrl    ;             // 0xC404_3000
    MIP_CTRL_TSADC_TS_TH_0_O26A0_T     ts_th_0    ;             // 0xC404_3004
    MIP_CTRL_TSADC_TS_TH_1_O26A0_T     ts_th_1    ;             // 0xC404_3008
    MIP_CTRL_TSADC_TS_TH_URGENT_O26A0_T    ts_th_urgent;        // 0xC404_300C
    MIP_CTRL_TSADC_TS_STAT_O26A0_T     ts_stat    ;             // 0xC404_3010
    MIP_CTRL_TSADC_TS_DATA_O26A0_T     ts_data    ;             // 0xC404_3014
    MIP_CTRL_TSADC_TS_DIG_CTRL_O26A0_T    ts_dig_ctrl;          // 0xC404_3018
}MIP_CTRL_TSADC_REG_O26A0_T;
/* 7 regs */

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

#define MIP_CTRL_TSADC_TS_CTRL_O26A0_T_OFF                  (BASEADDRESS+0x0000)
#define MIP_CTRL_TSADC_TS_TH_0_O26A0_T_OFF                  (BASEADDRESS+0x0004)
#define MIP_CTRL_TSADC_TS_TH_1_O26A0_T_OFF                  (BASEADDRESS+0x0008)
#define MIP_CTRL_TSADC_TS_TH_URGENT_O26A0_T_OFF             (BASEADDRESS+0x000C)
#define MIP_CTRL_TSADC_TS_STAT_O26A0_T_OFF                  (BASEADDRESS+0x0010)
#define MIP_CTRL_TSADC_TS_DATA_O26A0_T_OFF                  (BASEADDRESS+0x0014)
#define MIP_CTRL_TSADC_TS_DIG_CTRL_O26A0_T_OFF              (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xC404_3000    ts_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 ts_pdb             :  1;    //      0
    UINT32 ts_trim            :  8;    //   8: 1
    UINT32 ts_sel_clk         :  3;    //  11: 9
    UINT32 ts_sel_osr         :  2;    //  13:12
    UINT32 ts_sel_cic         :  1;    //     14
    UINT32 ts_sel_chop        :  1;    //     15
    UINT32 ts_vdd_det         :  1;    //     16
    UINT32 ts_12b_out         :  1;    //     17
    UINT32 tsc_din_shift_en   :  1;    //     18
    UINT32 tsc_dout_avg_en    :  1;    //     19
    UINT32 tsc_dout_iir_en    :  1;    //     20
    UINT32 tsc_intr_th_mode   :  1;    //     21
    UINT32 tsc_intr_th_en     :  1;    //     22
    UINT32 tsc_intr_th_urgent_en: 1;    //    23
    UINT32 tsc_intr_raw_en    :  1;    //     24
    UINT32 tsc_iir_coef       :  4;    //  28:25
    UINT32 mux_on             :  2;    //  30:29
    UINT32 resvd00            :  1;    //  31:31 reserved
    };
}MIP_CTRL_TSADC_TS_CTRL_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_3004    ts_th_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 tsc_th_0           : 16;    //  15: 0
    UINT32 tsc_th_1           : 16;    //  31:16
    };
}MIP_CTRL_TSADC_TS_TH_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_3008    ts_th_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 tsc_th_2           : 16;    //  15: 0
    UINT32 tsc_th_3           : 16;    //  31:16
    };
}MIP_CTRL_TSADC_TS_TH_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_300C    ts_th_urgent ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 tsc_th_urgent      : 16;    //  15: 0
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}MIP_CTRL_TSADC_TS_TH_URGENT_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_3010    ts_stat ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 tsc_stat_raw       :  1;    //      0
    UINT32 tsc_stat_th_0      :  1;    //      1
    UINT32 tsc_stat_th_1      :  1;    //      2
    UINT32 tsc_stat_th_2      :  1;    //      3
    UINT32 tsc_stat_th_3      :  1;    //      4
    UINT32 tsc_stat_th_urgent :  1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}MIP_CTRL_TSADC_TS_STAT_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_3014    ts_data ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 tsc_dout           : 16;    //  15: 0
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}MIP_CTRL_TSADC_TS_DATA_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_3018    ts_dig_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 ts_dig_ctrl        : 16;    //  15: 0
    UINT32 resvd00            : 16;    //  31:16 reserved
    };
}MIP_CTRL_TSADC_TS_DIG_CTRL_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_tsadc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_TSADC_TS_CTRL_O26A0_T     ts_ctrl    ;             // 0xC404_3000
    MIP_CTRL_TSADC_TS_TH_0_O26A0_T     ts_th_0    ;             // 0xC404_3004
    MIP_CTRL_TSADC_TS_TH_1_O26A0_T     ts_th_1    ;             // 0xC404_3008
    MIP_CTRL_TSADC_TS_TH_URGENT_O26A0_T    ts_th_urgent;        // 0xC404_300C
    MIP_CTRL_TSADC_TS_STAT_O26A0_T     ts_stat    ;             // 0xC404_3010
    MIP_CTRL_TSADC_TS_DATA_O26A0_T     ts_data    ;             // 0xC404_3014
    MIP_CTRL_TSADC_TS_DIG_CTRL_O26A0_T    ts_dig_ctrl;          // 0xC404_3018
}MIP_CTRL_TSADC_REG_O26A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MIP_CTRL_TSADC_REG_H_

/* from 'O26_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

