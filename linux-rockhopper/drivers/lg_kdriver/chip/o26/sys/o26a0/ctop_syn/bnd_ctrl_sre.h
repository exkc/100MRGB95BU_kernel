#ifndef _BND_CTRL_SRE_REG_O26A0_H_
#define _BND_CTRL_SRE_REG_O26A0_H_

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
    0xCCA2_2010    vds0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_droop_detector_en     :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_SRE_VDS0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2014    vds1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nma_cfg               : 24,    //  23: 0
                              :  8;    //  31:24 reserved
}BND_CTRL_SRE_VDS1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2018    vds2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pre_measure_exp       :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_SRE_VDS2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_201C    vds3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_prtn_refval_recalib_exp: 4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_SRE_VDS3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2020    vds4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_threshold_afs_activation: 6,    //  5: 0
                              : 26;    //   31:6 reserved
}BND_CTRL_SRE_VDS4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2024    vds5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_threshold_afs_deactivation: 6,    //  5:0
                              : 26;    //   31:6 reserved
}BND_CTRL_SRE_VDS5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2028    vds6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_min_pulse             :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}BND_CTRL_SRE_VDS6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_202C    vds7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_prtn_alert_mask       :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_SRE_VDS7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2030    vdsr0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_droop_detector_active :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_prtn_nma_drpdet       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_calib_failed          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_prtn_status_data_rdy  :  1,    //     12
                              : 19;    //  31:13 reserved
}BND_CTRL_SRE_VDSR0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2034    vdsr1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_calib_info            :  5,    //   4: 0
                              : 27;    //   31:5 reserved
}BND_CTRL_SRE_VDSR1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2038    vdsr2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ref_value             :  8,    //   7: 0
                              : 24;    //   31:8 reserved
}BND_CTRL_SRE_VDSR2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_203C    vdsr3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_failed_measure_count  : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}BND_CTRL_SRE_VDSR3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2040    vdsr4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_droop_detected_count  :  6,    //   5: 0
                              : 26;    //   31:6 reserved
}BND_CTRL_SRE_VDSR4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2044    vdsr5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_min_tdc_value         :  8,    //   7: 0
                              : 24;    //   31:8 reserved
}BND_CTRL_SRE_VDSR5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2048    vdsr6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_max_tdc_value         :  8,    //   7: 0
                              : 24;    //   31:8 reserved
}BND_CTRL_SRE_VDSR6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2050    vds_intr1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vds_intr_polar_high_en:  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_vds_intr_edge_en      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_vds_intr_clear        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_vds_intr_en           :  1,    //     12
                              : 19;    //  31:13 reserved
}BND_CTRL_SRE_VDS_INTR1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2054    vds_intr2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vds_intr_lockn_main_counter: 4,    //  3:0
    reg_vds_intr_init_cnt     :  4,    //   7: 4
    reg_vds_intr_rising_edge_en: 1,    //      8
                              :  3,    //  11: 9 reserved
    reg_vds_intr_counter_clear:  1,    //     12
                              : 19;    //  31:13 reserved
}BND_CTRL_SRE_VDS_INTR2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2100    sre_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sre_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sre_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_sre_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_SRE_SRE_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2104    sre_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sre_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_SRE_SRE_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2108    sre_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sre_sra_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_SRE_SRE_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_210C    sre_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sre_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_SRE_SRE_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[4];             // 0xCCA2_2000 ~ 0xCCA2_200C
    BND_CTRL_SRE_VDS0_O26A0_T          vds0       ;             // 0xCCA2_2010
    BND_CTRL_SRE_VDS1_O26A0_T          vds1       ;             // 0xCCA2_2014
    BND_CTRL_SRE_VDS2_O26A0_T          vds2       ;             // 0xCCA2_2018
    BND_CTRL_SRE_VDS3_O26A0_T          vds3       ;             // 0xCCA2_201C
    BND_CTRL_SRE_VDS4_O26A0_T          vds4       ;             // 0xCCA2_2020
    BND_CTRL_SRE_VDS5_O26A0_T          vds5       ;             // 0xCCA2_2024
    BND_CTRL_SRE_VDS6_O26A0_T          vds6       ;             // 0xCCA2_2028
    BND_CTRL_SRE_VDS7_O26A0_T          vds7       ;             // 0xCCA2_202C
    BND_CTRL_SRE_VDSR0_O26A0_T         vdsr0      ;             // 0xCCA2_2030
    BND_CTRL_SRE_VDSR1_O26A0_T         vdsr1      ;             // 0xCCA2_2034
    BND_CTRL_SRE_VDSR2_O26A0_T         vdsr2      ;             // 0xCCA2_2038
    BND_CTRL_SRE_VDSR3_O26A0_T         vdsr3      ;             // 0xCCA2_203C
    BND_CTRL_SRE_VDSR4_O26A0_T         vdsr4      ;             // 0xCCA2_2040
    BND_CTRL_SRE_VDSR5_O26A0_T         vdsr5      ;             // 0xCCA2_2044
    BND_CTRL_SRE_VDSR6_O26A0_T         vdsr6      ;             // 0xCCA2_2048
    UINT32                             _rsvd_01[1];             // 0xCCA2_204C
    BND_CTRL_SRE_VDS_INTR1_O26A0_T     vds_intr1  ;             // 0xCCA2_2050
    BND_CTRL_SRE_VDS_INTR2_O26A0_T     vds_intr2  ;             // 0xCCA2_2054
    UINT32                             _rsvd_02[42];            // 0xCCA2_2058 ~ 0xCCA2_20FC
    BND_CTRL_SRE_SRE_MEM0_O26A0_T      sre_mem0   ;             // 0xCCA2_2100
    BND_CTRL_SRE_SRE_MEM1_O26A0_T      sre_mem1   ;             // 0xCCA2_2104
    BND_CTRL_SRE_SRE_MEM2_O26A0_T      sre_mem2   ;             // 0xCCA2_2108
    BND_CTRL_SRE_SRE_MEM3_O26A0_T      sre_mem3   ;             // 0xCCA2_210C
}BND_CTRL_SRE_REG_O26A0_T;
/* 21 regs */

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

#define BND_CTRL_SRE_VDS0_O26A0_T_OFF                       (BASEADDRESS+0x0010)
#define BND_CTRL_SRE_VDS1_O26A0_T_OFF                       (BASEADDRESS+0x0014)
#define BND_CTRL_SRE_VDS2_O26A0_T_OFF                       (BASEADDRESS+0x0018)
#define BND_CTRL_SRE_VDS3_O26A0_T_OFF                       (BASEADDRESS+0x001C)
#define BND_CTRL_SRE_VDS4_O26A0_T_OFF                       (BASEADDRESS+0x0020)
#define BND_CTRL_SRE_VDS5_O26A0_T_OFF                       (BASEADDRESS+0x0024)
#define BND_CTRL_SRE_VDS6_O26A0_T_OFF                       (BASEADDRESS+0x0028)
#define BND_CTRL_SRE_VDS7_O26A0_T_OFF                       (BASEADDRESS+0x002C)
#define BND_CTRL_SRE_VDSR0_O26A0_T_OFF                      (BASEADDRESS+0x0030)
#define BND_CTRL_SRE_VDSR1_O26A0_T_OFF                      (BASEADDRESS+0x0034)
#define BND_CTRL_SRE_VDSR2_O26A0_T_OFF                      (BASEADDRESS+0x0038)
#define BND_CTRL_SRE_VDSR3_O26A0_T_OFF                      (BASEADDRESS+0x003C)
#define BND_CTRL_SRE_VDSR4_O26A0_T_OFF                      (BASEADDRESS+0x0040)
#define BND_CTRL_SRE_VDSR5_O26A0_T_OFF                      (BASEADDRESS+0x0044)
#define BND_CTRL_SRE_VDSR6_O26A0_T_OFF                      (BASEADDRESS+0x0048)
#define BND_CTRL_SRE_VDS_INTR1_O26A0_T_OFF                  (BASEADDRESS+0x0050)
#define BND_CTRL_SRE_VDS_INTR2_O26A0_T_OFF                  (BASEADDRESS+0x0054)
#define BND_CTRL_SRE_SRE_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0100)
#define BND_CTRL_SRE_SRE_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0104)
#define BND_CTRL_SRE_SRE_MEM2_O26A0_T_OFF                   (BASEADDRESS+0x0108)
#define BND_CTRL_SRE_SRE_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x010C)

/*-----------------------------------------------------------------------------------------
    0xCCA2_2010    vds0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_droop_detector_en: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_SRE_VDS0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2014    vds1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nma_cfg        : 24;    //  23: 0
    UINT32 resvd00            :  8;    //  31:24 reserved
    };
}BND_CTRL_SRE_VDS1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2018    vds2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pre_measure_exp:  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_SRE_VDS2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_201C    vds3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_prtn_refval_recalib_exp: 4;    //  3:0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_SRE_VDS3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2020    vds4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_threshold_afs_activation: 6;    //  5:0
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BND_CTRL_SRE_VDS4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2024    vds5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_threshold_afs_deactivation: 6;    //  5:0
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BND_CTRL_SRE_VDS5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2028    vds6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_min_pulse      :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_SRE_VDS6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_202C    vds7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_prtn_alert_mask:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_SRE_VDS7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2030    vdsr0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_droop_detector_active: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_prtn_nma_drpdet:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_calib_failed   :  1;    //      8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_prtn_status_data_rdy: 1;    //  12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}BND_CTRL_SRE_VDSR0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2034    vdsr1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_calib_info     :  5;    //   4: 0
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}BND_CTRL_SRE_VDSR1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2038    vdsr2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ref_value      :  8;    //   7: 0
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BND_CTRL_SRE_VDSR2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_203C    vdsr3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_failed_measure_count: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}BND_CTRL_SRE_VDSR3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2040    vdsr4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_droop_detected_count: 6;    //  5:0
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BND_CTRL_SRE_VDSR4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2044    vdsr5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_min_tdc_value  :  8;    //   7: 0
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BND_CTRL_SRE_VDSR5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2048    vdsr6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_max_tdc_value  :  8;    //   7: 0
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BND_CTRL_SRE_VDSR6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2050    vds_intr1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vds_intr_polar_high_en: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_vds_intr_edge_en: 1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_vds_intr_clear :  1;    //      8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_vds_intr_en    :  1;    //     12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}BND_CTRL_SRE_VDS_INTR1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2054    vds_intr2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vds_intr_lockn_main_counter: 4;    //  3:0
    UINT32 reg_vds_intr_init_cnt: 4;    //  7: 4
    UINT32 reg_vds_intr_rising_edge_en: 1;    //  8
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_vds_intr_counter_clear: 1;    //  12
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}BND_CTRL_SRE_VDS_INTR2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2100    sre_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sre_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_sre_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_sre_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_SRE_SRE_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2104    sre_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sre_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_SRE_SRE_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_2108    sre_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sre_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_SRE_SRE_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCA2_210C    sre_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sre_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_SRE_SRE_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_sre Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[4];             // 0xCCA2_2000 ~ 0xCCA2_200C
    BND_CTRL_SRE_VDS0_O26A0_T          vds0       ;             // 0xCCA2_2010
    BND_CTRL_SRE_VDS1_O26A0_T          vds1       ;             // 0xCCA2_2014
    BND_CTRL_SRE_VDS2_O26A0_T          vds2       ;             // 0xCCA2_2018
    BND_CTRL_SRE_VDS3_O26A0_T          vds3       ;             // 0xCCA2_201C
    BND_CTRL_SRE_VDS4_O26A0_T          vds4       ;             // 0xCCA2_2020
    BND_CTRL_SRE_VDS5_O26A0_T          vds5       ;             // 0xCCA2_2024
    BND_CTRL_SRE_VDS6_O26A0_T          vds6       ;             // 0xCCA2_2028
    BND_CTRL_SRE_VDS7_O26A0_T          vds7       ;             // 0xCCA2_202C
    BND_CTRL_SRE_VDSR0_O26A0_T         vdsr0      ;             // 0xCCA2_2030
    BND_CTRL_SRE_VDSR1_O26A0_T         vdsr1      ;             // 0xCCA2_2034
    BND_CTRL_SRE_VDSR2_O26A0_T         vdsr2      ;             // 0xCCA2_2038
    BND_CTRL_SRE_VDSR3_O26A0_T         vdsr3      ;             // 0xCCA2_203C
    BND_CTRL_SRE_VDSR4_O26A0_T         vdsr4      ;             // 0xCCA2_2040
    BND_CTRL_SRE_VDSR5_O26A0_T         vdsr5      ;             // 0xCCA2_2044
    BND_CTRL_SRE_VDSR6_O26A0_T         vdsr6      ;             // 0xCCA2_2048
    UINT32                             _rsvd_01[1];             // 0xCCA2_204C
    BND_CTRL_SRE_VDS_INTR1_O26A0_T     vds_intr1  ;             // 0xCCA2_2050
    BND_CTRL_SRE_VDS_INTR2_O26A0_T     vds_intr2  ;             // 0xCCA2_2054
    UINT32                             _rsvd_02[42];            // 0xCCA2_2058 ~ 0xCCA2_20FC
    BND_CTRL_SRE_SRE_MEM0_O26A0_T      sre_mem0   ;             // 0xCCA2_2100
    BND_CTRL_SRE_SRE_MEM1_O26A0_T      sre_mem1   ;             // 0xCCA2_2104
    BND_CTRL_SRE_SRE_MEM2_O26A0_T      sre_mem2   ;             // 0xCCA2_2108
    BND_CTRL_SRE_SRE_MEM3_O26A0_T      sre_mem3   ;             // 0xCCA2_210C
}BND_CTRL_SRE_REG_O26A0_T;
/* 21 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_SRE_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

