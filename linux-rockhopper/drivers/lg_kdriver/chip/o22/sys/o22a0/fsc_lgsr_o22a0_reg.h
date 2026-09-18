#ifndef _FSC_LGSR_REG_H_
#define _FSC_LGSR_REG_H_

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
    0xCC3F_5000    reg_pwm_det_en ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_det_en_ch0        :  1,    //      0
    reg_pwm_det_en_ch1        :  1,    //      1
    reg_pwm_det_en_ch2        :  1,    //      2
    reg_pwm_det_en_ch3        :  1,    //      3
    reg_pwm_det_en_ch4        :  1,    //      4
    reg_pwm_det_en_ch5        :  1,    //      5
    reg_pwm_det_en_ch6        :  1,    //      6
    reg_pwm_det_en_ch7        :  1,    //      7
    reg_pwm_det_en_ch8        :  1,    //      8
    reg_pwm_det_en_ch9        :  1,    //      9
                              : 22;    //  31:10 reserved
}FSC_LGSR_REG_PWM_DET_EN_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5004    det_sample_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_period   : 32;    //  31: 0
}FSC_LGSR_DET_SAMPLE_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5008    det_deg_ctr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_deglitch_time         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_deglitch_en           :  1,    //      4
                              : 27;    //   31:5 reserved
}FSC_LGSR_DET_DEG_CTR_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_500C    det_int_en ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    fsc_intr_en               :  1,    //      0
                              : 31;    //   31:1 reserved
}FSC_LGSR_DET_INT_EN_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5010    det_int_ctr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    fsc_intr_clear            :  1,    //      0
                              : 31;    //   31:1 reserved
}FSC_LGSR_DET_INT_CTR_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5014    pwm_op_mode_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_pol_control_ch0   :  2,    //   1: 0
    reg_pwm_en_ch0            :  1,    //      2
                              : 29;    //   31:3 reserved
}FSC_LGSR_PWM_OP_MODE_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5018    pwm_op_mode_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_pol_control_ch1   :  2,    //   1: 0
    reg_pwm_en_ch1            :  1,    //      2
                              : 29;    //   31:3 reserved
}FSC_LGSR_PWM_OP_MODE_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_501C    pwm_op_mode_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_pol_control_ch2   :  2,    //   1: 0
    reg_pwm_en_ch2            :  1,    //      2
                              : 29;    //   31:3 reserved
}FSC_LGSR_PWM_OP_MODE_2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5020    pwm_duty_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_duty_ch0          : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_LGSR_PWM_DUTY_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5024    pwm_duty_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_duty_ch1          : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_LGSR_PWM_DUTY_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5028    pwm_duty_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_duty_ch2          : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_LGSR_PWM_DUTY_2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_502C    pwm_gen_clk_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_gen_clk_ch0       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_LGSR_PWM_GEN_CLK_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5030    pwm_gen_clk_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_gen_clk_ch1       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_LGSR_PWM_GEN_CLK_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5034    pwm_gen_clk_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_gen_clk_ch2       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_LGSR_PWM_GEN_CLK_2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5038    det_int_status ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    fsc_intr                  :  1,    //      0
                              : 31;    //   31:1 reserved
}FSC_LGSR_DET_INT_STATUS_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_503C    det_count_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch0 : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_COUNT_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5040    det_count_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch1 : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_COUNT_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5044    det_count_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch2 : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_COUNT_2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5048    det_count_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch3 : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_COUNT_3_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_504C    det_count_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch4 : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_COUNT_4_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5050    det_count_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch5 : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_COUNT_5_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5054    det_count_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch6 : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_COUNT_6_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5058    det_count_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch7 : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_COUNT_7_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_505C    det_count_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch8 : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_COUNT_8_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5060    det_count_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch9 : 10,    //   9: 0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_COUNT_9_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5064    det_avg_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch0: 10,    //  9:0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_AVG_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5068    det_avg_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch1: 10,    //  9:0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_AVG_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_506C    det_avg_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch2: 10,    //  9:0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_AVG_2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5070    det_avg_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch3: 10,    //  9:0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_AVG_3_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5074    det_avg_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch4: 10,    //  9:0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_AVG_4_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5078    det_avg_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch5: 10,    //  9:0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_AVG_5_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_507C    det_avg_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch6: 10,    //  9:0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_AVG_6_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5080    det_avg_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch7: 10,    //  9:0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_AVG_7_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5084    det_avg_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch8: 10,    //  9:0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_AVG_8_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5088    det_avg_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch9: 10,    //  9:0
                              : 22;    //  31:10 reserved
}FSC_LGSR_DET_AVG_9_O22A0_T;

/*-----------------------------------------------------------------------------------------
    fsc_lgsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FSC_LGSR_REG_PWM_DET_EN_O22A0_T    reg_pwm_det_en;          // 0xCC3F_5000
    FSC_LGSR_DET_SAMPLE_0_O22A0_T      det_sample_0;            // 0xCC3F_5004
    FSC_LGSR_DET_DEG_CTR_O22A0_T       det_deg_ctr;             // 0xCC3F_5008
    FSC_LGSR_DET_INT_EN_O22A0_T        det_int_en ;             // 0xCC3F_500C
    FSC_LGSR_DET_INT_CTR_O22A0_T       det_int_ctr;             // 0xCC3F_5010
    FSC_LGSR_PWM_OP_MODE_0_O22A0_T     pwm_op_mode_0;           // 0xCC3F_5014
    FSC_LGSR_PWM_OP_MODE_1_O22A0_T     pwm_op_mode_1;           // 0xCC3F_5018
    FSC_LGSR_PWM_OP_MODE_2_O22A0_T     pwm_op_mode_2;           // 0xCC3F_501C
    FSC_LGSR_PWM_DUTY_0_O22A0_T        pwm_duty_0 ;             // 0xCC3F_5020
    FSC_LGSR_PWM_DUTY_1_O22A0_T        pwm_duty_1 ;             // 0xCC3F_5024
    FSC_LGSR_PWM_DUTY_2_O22A0_T        pwm_duty_2 ;             // 0xCC3F_5028
    FSC_LGSR_PWM_GEN_CLK_0_O22A0_T     pwm_gen_clk_0;           // 0xCC3F_502C
    FSC_LGSR_PWM_GEN_CLK_1_O22A0_T     pwm_gen_clk_1;           // 0xCC3F_5030
    FSC_LGSR_PWM_GEN_CLK_2_O22A0_T     pwm_gen_clk_2;           // 0xCC3F_5034
    FSC_LGSR_DET_INT_STATUS_O22A0_T    det_int_status;          // 0xCC3F_5038
    FSC_LGSR_DET_COUNT_0_O22A0_T       det_count_0;             // 0xCC3F_503C
    FSC_LGSR_DET_COUNT_1_O22A0_T       det_count_1;             // 0xCC3F_5040
    FSC_LGSR_DET_COUNT_2_O22A0_T       det_count_2;             // 0xCC3F_5044
    FSC_LGSR_DET_COUNT_3_O22A0_T       det_count_3;             // 0xCC3F_5048
    FSC_LGSR_DET_COUNT_4_O22A0_T       det_count_4;             // 0xCC3F_504C
    FSC_LGSR_DET_COUNT_5_O22A0_T       det_count_5;             // 0xCC3F_5050
    FSC_LGSR_DET_COUNT_6_O22A0_T       det_count_6;             // 0xCC3F_5054
    FSC_LGSR_DET_COUNT_7_O22A0_T       det_count_7;             // 0xCC3F_5058
    FSC_LGSR_DET_COUNT_8_O22A0_T       det_count_8;             // 0xCC3F_505C
    FSC_LGSR_DET_COUNT_9_O22A0_T       det_count_9;             // 0xCC3F_5060
    FSC_LGSR_DET_AVG_0_O22A0_T         det_avg_0  ;             // 0xCC3F_5064
    FSC_LGSR_DET_AVG_1_O22A0_T         det_avg_1  ;             // 0xCC3F_5068
    FSC_LGSR_DET_AVG_2_O22A0_T         det_avg_2  ;             // 0xCC3F_506C
    FSC_LGSR_DET_AVG_3_O22A0_T         det_avg_3  ;             // 0xCC3F_5070
    FSC_LGSR_DET_AVG_4_O22A0_T         det_avg_4  ;             // 0xCC3F_5074
    FSC_LGSR_DET_AVG_5_O22A0_T         det_avg_5  ;             // 0xCC3F_5078
    FSC_LGSR_DET_AVG_6_O22A0_T         det_avg_6  ;             // 0xCC3F_507C
    FSC_LGSR_DET_AVG_7_O22A0_T         det_avg_7  ;             // 0xCC3F_5080
    FSC_LGSR_DET_AVG_8_O22A0_T         det_avg_8  ;             // 0xCC3F_5084
    FSC_LGSR_DET_AVG_9_O22A0_T         det_avg_9  ;             // 0xCC3F_5088
}FSC_LGSR_REG_O22A0_T;
/* 35 regs */

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

#define FSC_LGSR_REG_PWM_DET_EN_O22A0_T_OFF                 (BASEADDRESS+0x0000)
#define FSC_LGSR_DET_SAMPLE_0_O22A0_T_OFF                   (BASEADDRESS+0x0004)
#define FSC_LGSR_DET_DEG_CTR_O22A0_T_OFF                    (BASEADDRESS+0x0008)
#define FSC_LGSR_DET_INT_EN_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define FSC_LGSR_DET_INT_CTR_O22A0_T_OFF                    (BASEADDRESS+0x0010)
#define FSC_LGSR_PWM_OP_MODE_0_O22A0_T_OFF                  (BASEADDRESS+0x0014)
#define FSC_LGSR_PWM_OP_MODE_1_O22A0_T_OFF                  (BASEADDRESS+0x0018)
#define FSC_LGSR_PWM_OP_MODE_2_O22A0_T_OFF                  (BASEADDRESS+0x001C)
#define FSC_LGSR_PWM_DUTY_0_O22A0_T_OFF                     (BASEADDRESS+0x0020)
#define FSC_LGSR_PWM_DUTY_1_O22A0_T_OFF                     (BASEADDRESS+0x0024)
#define FSC_LGSR_PWM_DUTY_2_O22A0_T_OFF                     (BASEADDRESS+0x0028)
#define FSC_LGSR_PWM_GEN_CLK_0_O22A0_T_OFF                  (BASEADDRESS+0x002C)
#define FSC_LGSR_PWM_GEN_CLK_1_O22A0_T_OFF                  (BASEADDRESS+0x0030)
#define FSC_LGSR_PWM_GEN_CLK_2_O22A0_T_OFF                  (BASEADDRESS+0x0034)
#define FSC_LGSR_DET_INT_STATUS_O22A0_T_OFF                 (BASEADDRESS+0x0038)
#define FSC_LGSR_DET_COUNT_0_O22A0_T_OFF                    (BASEADDRESS+0x003C)
#define FSC_LGSR_DET_COUNT_1_O22A0_T_OFF                    (BASEADDRESS+0x0040)
#define FSC_LGSR_DET_COUNT_2_O22A0_T_OFF                    (BASEADDRESS+0x0044)
#define FSC_LGSR_DET_COUNT_3_O22A0_T_OFF                    (BASEADDRESS+0x0048)
#define FSC_LGSR_DET_COUNT_4_O22A0_T_OFF                    (BASEADDRESS+0x004C)
#define FSC_LGSR_DET_COUNT_5_O22A0_T_OFF                    (BASEADDRESS+0x0050)
#define FSC_LGSR_DET_COUNT_6_O22A0_T_OFF                    (BASEADDRESS+0x0054)
#define FSC_LGSR_DET_COUNT_7_O22A0_T_OFF                    (BASEADDRESS+0x0058)
#define FSC_LGSR_DET_COUNT_8_O22A0_T_OFF                    (BASEADDRESS+0x005C)
#define FSC_LGSR_DET_COUNT_9_O22A0_T_OFF                    (BASEADDRESS+0x0060)
#define FSC_LGSR_DET_AVG_0_O22A0_T_OFF                      (BASEADDRESS+0x0064)
#define FSC_LGSR_DET_AVG_1_O22A0_T_OFF                      (BASEADDRESS+0x0068)
#define FSC_LGSR_DET_AVG_2_O22A0_T_OFF                      (BASEADDRESS+0x006C)
#define FSC_LGSR_DET_AVG_3_O22A0_T_OFF                      (BASEADDRESS+0x0070)
#define FSC_LGSR_DET_AVG_4_O22A0_T_OFF                      (BASEADDRESS+0x0074)
#define FSC_LGSR_DET_AVG_5_O22A0_T_OFF                      (BASEADDRESS+0x0078)
#define FSC_LGSR_DET_AVG_6_O22A0_T_OFF                      (BASEADDRESS+0x007C)
#define FSC_LGSR_DET_AVG_7_O22A0_T_OFF                      (BASEADDRESS+0x0080)
#define FSC_LGSR_DET_AVG_8_O22A0_T_OFF                      (BASEADDRESS+0x0084)
#define FSC_LGSR_DET_AVG_9_O22A0_T_OFF                      (BASEADDRESS+0x0088)

/*-----------------------------------------------------------------------------------------
    0xCC3F_5000    reg_pwm_det_en ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_det_en_ch0 :  1;    //      0
    UINT32 reg_pwm_det_en_ch1 :  1;    //      1
    UINT32 reg_pwm_det_en_ch2 :  1;    //      2
    UINT32 reg_pwm_det_en_ch3 :  1;    //      3
    UINT32 reg_pwm_det_en_ch4 :  1;    //      4
    UINT32 reg_pwm_det_en_ch5 :  1;    //      5
    UINT32 reg_pwm_det_en_ch6 :  1;    //      6
    UINT32 reg_pwm_det_en_ch7 :  1;    //      7
    UINT32 reg_pwm_det_en_ch8 :  1;    //      8
    UINT32 reg_pwm_det_en_ch9 :  1;    //      9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_REG_PWM_DET_EN_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5004    det_sample_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_period: 32;    //  31:0
    };
}FSC_LGSR_DET_SAMPLE_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5008    det_deg_ctr ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_deglitch_time  :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_deglitch_en    :  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}FSC_LGSR_DET_DEG_CTR_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_500C    det_int_en ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 fsc_intr_en        :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}FSC_LGSR_DET_INT_EN_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5010    det_int_ctr ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 fsc_intr_clear     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}FSC_LGSR_DET_INT_CTR_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5014    pwm_op_mode_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_pol_control_ch0: 2;    //  1:0
    UINT32 reg_pwm_en_ch0     :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}FSC_LGSR_PWM_OP_MODE_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5018    pwm_op_mode_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_pol_control_ch1: 2;    //  1:0
    UINT32 reg_pwm_en_ch1     :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}FSC_LGSR_PWM_OP_MODE_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_501C    pwm_op_mode_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_pol_control_ch2: 2;    //  1:0
    UINT32 reg_pwm_en_ch2     :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}FSC_LGSR_PWM_OP_MODE_2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5020    pwm_duty_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_duty_ch0   : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_LGSR_PWM_DUTY_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5024    pwm_duty_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_duty_ch1   : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_LGSR_PWM_DUTY_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5028    pwm_duty_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_duty_ch2   : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_LGSR_PWM_DUTY_2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_502C    pwm_gen_clk_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_gen_clk_ch0: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_LGSR_PWM_GEN_CLK_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5030    pwm_gen_clk_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_gen_clk_ch1: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_LGSR_PWM_GEN_CLK_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5034    pwm_gen_clk_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_gen_clk_ch2: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_LGSR_PWM_GEN_CLK_2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5038    det_int_status ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 fsc_intr           :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}FSC_LGSR_DET_INT_STATUS_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_503C    det_count_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch0: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_COUNT_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5040    det_count_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch1: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_COUNT_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5044    det_count_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch2: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_COUNT_2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5048    det_count_3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch3: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_COUNT_3_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_504C    det_count_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch4: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_COUNT_4_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5050    det_count_5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch5: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_COUNT_5_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5054    det_count_6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch6: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_COUNT_6_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5058    det_count_7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch7: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_COUNT_7_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_505C    det_count_8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch8: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_COUNT_8_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5060    det_count_9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch9: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_COUNT_9_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5064    det_avg_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch0: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_AVG_0_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5068    det_avg_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch1: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_AVG_1_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_506C    det_avg_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch2: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_AVG_2_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5070    det_avg_3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch3: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_AVG_3_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5074    det_avg_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch4: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_AVG_4_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5078    det_avg_5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch5: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_AVG_5_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_507C    det_avg_6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch6: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_AVG_6_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5080    det_avg_7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch7: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_AVG_7_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5084    det_avg_8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch8: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_AVG_8_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_5088    det_avg_9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch9: 10;    //  9:0
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}FSC_LGSR_DET_AVG_9_O22A0_T;

/*-----------------------------------------------------------------------------------------
    fsc_lgsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FSC_LGSR_REG_PWM_DET_EN_O22A0_T    reg_pwm_det_en;          // 0xCC3F_5000
    FSC_LGSR_DET_SAMPLE_0_O22A0_T      det_sample_0;            // 0xCC3F_5004
    FSC_LGSR_DET_DEG_CTR_O22A0_T       det_deg_ctr;             // 0xCC3F_5008
    FSC_LGSR_DET_INT_EN_O22A0_T        det_int_en ;             // 0xCC3F_500C
    FSC_LGSR_DET_INT_CTR_O22A0_T       det_int_ctr;             // 0xCC3F_5010
    FSC_LGSR_PWM_OP_MODE_0_O22A0_T     pwm_op_mode_0;           // 0xCC3F_5014
    FSC_LGSR_PWM_OP_MODE_1_O22A0_T     pwm_op_mode_1;           // 0xCC3F_5018
    FSC_LGSR_PWM_OP_MODE_2_O22A0_T     pwm_op_mode_2;           // 0xCC3F_501C
    FSC_LGSR_PWM_DUTY_0_O22A0_T        pwm_duty_0 ;             // 0xCC3F_5020
    FSC_LGSR_PWM_DUTY_1_O22A0_T        pwm_duty_1 ;             // 0xCC3F_5024
    FSC_LGSR_PWM_DUTY_2_O22A0_T        pwm_duty_2 ;             // 0xCC3F_5028
    FSC_LGSR_PWM_GEN_CLK_0_O22A0_T     pwm_gen_clk_0;           // 0xCC3F_502C
    FSC_LGSR_PWM_GEN_CLK_1_O22A0_T     pwm_gen_clk_1;           // 0xCC3F_5030
    FSC_LGSR_PWM_GEN_CLK_2_O22A0_T     pwm_gen_clk_2;           // 0xCC3F_5034
    FSC_LGSR_DET_INT_STATUS_O22A0_T    det_int_status;          // 0xCC3F_5038
    FSC_LGSR_DET_COUNT_0_O22A0_T       det_count_0;             // 0xCC3F_503C
    FSC_LGSR_DET_COUNT_1_O22A0_T       det_count_1;             // 0xCC3F_5040
    FSC_LGSR_DET_COUNT_2_O22A0_T       det_count_2;             // 0xCC3F_5044
    FSC_LGSR_DET_COUNT_3_O22A0_T       det_count_3;             // 0xCC3F_5048
    FSC_LGSR_DET_COUNT_4_O22A0_T       det_count_4;             // 0xCC3F_504C
    FSC_LGSR_DET_COUNT_5_O22A0_T       det_count_5;             // 0xCC3F_5050
    FSC_LGSR_DET_COUNT_6_O22A0_T       det_count_6;             // 0xCC3F_5054
    FSC_LGSR_DET_COUNT_7_O22A0_T       det_count_7;             // 0xCC3F_5058
    FSC_LGSR_DET_COUNT_8_O22A0_T       det_count_8;             // 0xCC3F_505C
    FSC_LGSR_DET_COUNT_9_O22A0_T       det_count_9;             // 0xCC3F_5060
    FSC_LGSR_DET_AVG_0_O22A0_T         det_avg_0  ;             // 0xCC3F_5064
    FSC_LGSR_DET_AVG_1_O22A0_T         det_avg_1  ;             // 0xCC3F_5068
    FSC_LGSR_DET_AVG_2_O22A0_T         det_avg_2  ;             // 0xCC3F_506C
    FSC_LGSR_DET_AVG_3_O22A0_T         det_avg_3  ;             // 0xCC3F_5070
    FSC_LGSR_DET_AVG_4_O22A0_T         det_avg_4  ;             // 0xCC3F_5074
    FSC_LGSR_DET_AVG_5_O22A0_T         det_avg_5  ;             // 0xCC3F_5078
    FSC_LGSR_DET_AVG_6_O22A0_T         det_avg_6  ;             // 0xCC3F_507C
    FSC_LGSR_DET_AVG_7_O22A0_T         det_avg_7  ;             // 0xCC3F_5080
    FSC_LGSR_DET_AVG_8_O22A0_T         det_avg_8  ;             // 0xCC3F_5084
    FSC_LGSR_DET_AVG_9_O22A0_T         det_avg_9  ;             // 0xCC3F_5088
}FSC_LGSR_REG_O22A0_T;
/* 35 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FSC_LGSR_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

