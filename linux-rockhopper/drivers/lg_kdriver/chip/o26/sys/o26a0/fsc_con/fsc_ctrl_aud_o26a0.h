#ifndef _FSC_CTRL_AUD_REG_O26A0_H_
#define _FSC_CTRL_AUD_REG_O26A0_H_

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
    0xCE7B_4000    reg_pwm_det_en ''
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
}FSC_CTRL_AUD_REG_PWM_DET_EN_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4004    det_sample_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_period   : 32;    //  31: 0
}FSC_CTRL_AUD_DET_SAMPLE_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4008    det_deg_ctr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_deglitch_time         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_deglitch_en           :  1,    //      4
                              : 27;    //   31:5 reserved
}FSC_CTRL_AUD_DET_DEG_CTR_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_400C    det_int_en ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    fsc_intr_en               :  1,    //      0
                              : 31;    //   31:1 reserved
}FSC_CTRL_AUD_DET_INT_EN_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4010    det_int_ctr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    fsc_intr_clear            :  1,    //      0
                              : 31;    //   31:1 reserved
}FSC_CTRL_AUD_DET_INT_CTR_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4014    pwm_op_mode_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_pol_control_ch0   :  2,    //   1: 0
    reg_pwm_en_ch0            :  1,    //      2
                              : 29;    //   31:3 reserved
}FSC_CTRL_AUD_PWM_OP_MODE_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4018    pwm_op_mode_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_pol_control_ch1   :  2,    //   1: 0
    reg_pwm_en_ch1            :  1,    //      2
                              : 29;    //   31:3 reserved
}FSC_CTRL_AUD_PWM_OP_MODE_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_401C    pwm_op_mode_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_pol_control_ch2   :  2,    //   1: 0
    reg_pwm_en_ch2            :  1,    //      2
                              : 29;    //   31:3 reserved
}FSC_CTRL_AUD_PWM_OP_MODE_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4020    pwm_duty_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_duty_ch0          : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_AUD_PWM_DUTY_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4024    pwm_duty_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_duty_ch1          : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_AUD_PWM_DUTY_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4028    pwm_duty_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_duty_ch2          : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_AUD_PWM_DUTY_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_402C    pwm_gen_clk_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_gen_clk_ch0       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_AUD_PWM_GEN_CLK_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4030    pwm_gen_clk_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_gen_clk_ch1       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_AUD_PWM_GEN_CLK_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4034    pwm_gen_clk_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_gen_clk_ch2       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_AUD_PWM_GEN_CLK_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4038    det_int_status ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    fsc_intr                  :  1,    //      0
                              : 31;    //   31:1 reserved
}FSC_CTRL_AUD_DET_INT_STATUS_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_403C    det_count_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch0 : 32;    //  31: 0
}FSC_CTRL_AUD_DET_COUNT_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4040    det_count_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch1 : 32;    //  31: 0
}FSC_CTRL_AUD_DET_COUNT_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4044    det_count_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch2 : 32;    //  31: 0
}FSC_CTRL_AUD_DET_COUNT_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4048    det_count_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch3 : 32;    //  31: 0
}FSC_CTRL_AUD_DET_COUNT_3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_404C    det_count_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch4 : 32;    //  31: 0
}FSC_CTRL_AUD_DET_COUNT_4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4050    det_count_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch5 : 32;    //  31: 0
}FSC_CTRL_AUD_DET_COUNT_5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4054    det_count_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch6 : 32;    //  31: 0
}FSC_CTRL_AUD_DET_COUNT_6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4058    det_count_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch7 : 32;    //  31: 0
}FSC_CTRL_AUD_DET_COUNT_7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_405C    det_count_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch8 : 32;    //  31: 0
}FSC_CTRL_AUD_DET_COUNT_8_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4060    det_count_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch9 : 32;    //  31: 0
}FSC_CTRL_AUD_DET_COUNT_9_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4064    det_avg_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch0: 32;    //  31:0
}FSC_CTRL_AUD_DET_AVG_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4068    det_avg_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch1: 32;    //  31:0
}FSC_CTRL_AUD_DET_AVG_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_406C    det_avg_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch2: 32;    //  31:0
}FSC_CTRL_AUD_DET_AVG_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4070    det_avg_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch3: 32;    //  31:0
}FSC_CTRL_AUD_DET_AVG_3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4074    det_avg_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch4: 32;    //  31:0
}FSC_CTRL_AUD_DET_AVG_4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4078    det_avg_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch5: 32;    //  31:0
}FSC_CTRL_AUD_DET_AVG_5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_407C    det_avg_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch6: 32;    //  31:0
}FSC_CTRL_AUD_DET_AVG_6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4080    det_avg_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch7: 32;    //  31:0
}FSC_CTRL_AUD_DET_AVG_7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4084    det_avg_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch8: 32;    //  31:0
}FSC_CTRL_AUD_DET_AVG_8_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4088    det_avg_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch9: 32;    //  31:0
}FSC_CTRL_AUD_DET_AVG_9_O26A0_T;

/*-----------------------------------------------------------------------------------------
    fsc_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FSC_CTRL_AUD_REG_PWM_DET_EN_O26A0_T    reg_pwm_det_en;      // 0xCE7B_4000
    FSC_CTRL_AUD_DET_SAMPLE_0_O26A0_T    det_sample_0;          // 0xCE7B_4004
    FSC_CTRL_AUD_DET_DEG_CTR_O26A0_T    det_deg_ctr;            // 0xCE7B_4008
    FSC_CTRL_AUD_DET_INT_EN_O26A0_T    det_int_en ;             // 0xCE7B_400C
    FSC_CTRL_AUD_DET_INT_CTR_O26A0_T    det_int_ctr;            // 0xCE7B_4010
    FSC_CTRL_AUD_PWM_OP_MODE_0_O26A0_T    pwm_op_mode_0;        // 0xCE7B_4014
    FSC_CTRL_AUD_PWM_OP_MODE_1_O26A0_T    pwm_op_mode_1;        // 0xCE7B_4018
    FSC_CTRL_AUD_PWM_OP_MODE_2_O26A0_T    pwm_op_mode_2;        // 0xCE7B_401C
    FSC_CTRL_AUD_PWM_DUTY_0_O26A0_T    pwm_duty_0 ;             // 0xCE7B_4020
    FSC_CTRL_AUD_PWM_DUTY_1_O26A0_T    pwm_duty_1 ;             // 0xCE7B_4024
    FSC_CTRL_AUD_PWM_DUTY_2_O26A0_T    pwm_duty_2 ;             // 0xCE7B_4028
    FSC_CTRL_AUD_PWM_GEN_CLK_0_O26A0_T    pwm_gen_clk_0;        // 0xCE7B_402C
    FSC_CTRL_AUD_PWM_GEN_CLK_1_O26A0_T    pwm_gen_clk_1;        // 0xCE7B_4030
    FSC_CTRL_AUD_PWM_GEN_CLK_2_O26A0_T    pwm_gen_clk_2;        // 0xCE7B_4034
    FSC_CTRL_AUD_DET_INT_STATUS_O26A0_T    det_int_status;      // 0xCE7B_4038
    FSC_CTRL_AUD_DET_COUNT_0_O26A0_T    det_count_0;            // 0xCE7B_403C
    FSC_CTRL_AUD_DET_COUNT_1_O26A0_T    det_count_1;            // 0xCE7B_4040
    FSC_CTRL_AUD_DET_COUNT_2_O26A0_T    det_count_2;            // 0xCE7B_4044
    FSC_CTRL_AUD_DET_COUNT_3_O26A0_T    det_count_3;            // 0xCE7B_4048
    FSC_CTRL_AUD_DET_COUNT_4_O26A0_T    det_count_4;            // 0xCE7B_404C
    FSC_CTRL_AUD_DET_COUNT_5_O26A0_T    det_count_5;            // 0xCE7B_4050
    FSC_CTRL_AUD_DET_COUNT_6_O26A0_T    det_count_6;            // 0xCE7B_4054
    FSC_CTRL_AUD_DET_COUNT_7_O26A0_T    det_count_7;            // 0xCE7B_4058
    FSC_CTRL_AUD_DET_COUNT_8_O26A0_T    det_count_8;            // 0xCE7B_405C
    FSC_CTRL_AUD_DET_COUNT_9_O26A0_T    det_count_9;            // 0xCE7B_4060
    FSC_CTRL_AUD_DET_AVG_0_O26A0_T     det_avg_0  ;             // 0xCE7B_4064
    FSC_CTRL_AUD_DET_AVG_1_O26A0_T     det_avg_1  ;             // 0xCE7B_4068
    FSC_CTRL_AUD_DET_AVG_2_O26A0_T     det_avg_2  ;             // 0xCE7B_406C
    FSC_CTRL_AUD_DET_AVG_3_O26A0_T     det_avg_3  ;             // 0xCE7B_4070
    FSC_CTRL_AUD_DET_AVG_4_O26A0_T     det_avg_4  ;             // 0xCE7B_4074
    FSC_CTRL_AUD_DET_AVG_5_O26A0_T     det_avg_5  ;             // 0xCE7B_4078
    FSC_CTRL_AUD_DET_AVG_6_O26A0_T     det_avg_6  ;             // 0xCE7B_407C
    FSC_CTRL_AUD_DET_AVG_7_O26A0_T     det_avg_7  ;             // 0xCE7B_4080
    FSC_CTRL_AUD_DET_AVG_8_O26A0_T     det_avg_8  ;             // 0xCE7B_4084
    FSC_CTRL_AUD_DET_AVG_9_O26A0_T     det_avg_9  ;             // 0xCE7B_4088
}FSC_CTRL_AUD_REG_O26A0_T;
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

#define FSC_CTRL_AUD_REG_PWM_DET_EN_O26A0_T_OFF             (BASEADDRESS+0x0000)
#define FSC_CTRL_AUD_DET_SAMPLE_0_O26A0_T_OFF               (BASEADDRESS+0x0004)
#define FSC_CTRL_AUD_DET_DEG_CTR_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define FSC_CTRL_AUD_DET_INT_EN_O26A0_T_OFF                 (BASEADDRESS+0x000C)
#define FSC_CTRL_AUD_DET_INT_CTR_O26A0_T_OFF                (BASEADDRESS+0x0010)
#define FSC_CTRL_AUD_PWM_OP_MODE_0_O26A0_T_OFF              (BASEADDRESS+0x0014)
#define FSC_CTRL_AUD_PWM_OP_MODE_1_O26A0_T_OFF              (BASEADDRESS+0x0018)
#define FSC_CTRL_AUD_PWM_OP_MODE_2_O26A0_T_OFF              (BASEADDRESS+0x001C)
#define FSC_CTRL_AUD_PWM_DUTY_0_O26A0_T_OFF                 (BASEADDRESS+0x0020)
#define FSC_CTRL_AUD_PWM_DUTY_1_O26A0_T_OFF                 (BASEADDRESS+0x0024)
#define FSC_CTRL_AUD_PWM_DUTY_2_O26A0_T_OFF                 (BASEADDRESS+0x0028)
#define FSC_CTRL_AUD_PWM_GEN_CLK_0_O26A0_T_OFF              (BASEADDRESS+0x002C)
#define FSC_CTRL_AUD_PWM_GEN_CLK_1_O26A0_T_OFF              (BASEADDRESS+0x0030)
#define FSC_CTRL_AUD_PWM_GEN_CLK_2_O26A0_T_OFF              (BASEADDRESS+0x0034)
#define FSC_CTRL_AUD_DET_INT_STATUS_O26A0_T_OFF             (BASEADDRESS+0x0038)
#define FSC_CTRL_AUD_DET_COUNT_0_O26A0_T_OFF                (BASEADDRESS+0x003C)
#define FSC_CTRL_AUD_DET_COUNT_1_O26A0_T_OFF                (BASEADDRESS+0x0040)
#define FSC_CTRL_AUD_DET_COUNT_2_O26A0_T_OFF                (BASEADDRESS+0x0044)
#define FSC_CTRL_AUD_DET_COUNT_3_O26A0_T_OFF                (BASEADDRESS+0x0048)
#define FSC_CTRL_AUD_DET_COUNT_4_O26A0_T_OFF                (BASEADDRESS+0x004C)
#define FSC_CTRL_AUD_DET_COUNT_5_O26A0_T_OFF                (BASEADDRESS+0x0050)
#define FSC_CTRL_AUD_DET_COUNT_6_O26A0_T_OFF                (BASEADDRESS+0x0054)
#define FSC_CTRL_AUD_DET_COUNT_7_O26A0_T_OFF                (BASEADDRESS+0x0058)
#define FSC_CTRL_AUD_DET_COUNT_8_O26A0_T_OFF                (BASEADDRESS+0x005C)
#define FSC_CTRL_AUD_DET_COUNT_9_O26A0_T_OFF                (BASEADDRESS+0x0060)
#define FSC_CTRL_AUD_DET_AVG_0_O26A0_T_OFF                  (BASEADDRESS+0x0064)
#define FSC_CTRL_AUD_DET_AVG_1_O26A0_T_OFF                  (BASEADDRESS+0x0068)
#define FSC_CTRL_AUD_DET_AVG_2_O26A0_T_OFF                  (BASEADDRESS+0x006C)
#define FSC_CTRL_AUD_DET_AVG_3_O26A0_T_OFF                  (BASEADDRESS+0x0070)
#define FSC_CTRL_AUD_DET_AVG_4_O26A0_T_OFF                  (BASEADDRESS+0x0074)
#define FSC_CTRL_AUD_DET_AVG_5_O26A0_T_OFF                  (BASEADDRESS+0x0078)
#define FSC_CTRL_AUD_DET_AVG_6_O26A0_T_OFF                  (BASEADDRESS+0x007C)
#define FSC_CTRL_AUD_DET_AVG_7_O26A0_T_OFF                  (BASEADDRESS+0x0080)
#define FSC_CTRL_AUD_DET_AVG_8_O26A0_T_OFF                  (BASEADDRESS+0x0084)
#define FSC_CTRL_AUD_DET_AVG_9_O26A0_T_OFF                  (BASEADDRESS+0x0088)

/*-----------------------------------------------------------------------------------------
    0xCE7B_4000    reg_pwm_det_en ''
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
}FSC_CTRL_AUD_REG_PWM_DET_EN_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4004    det_sample_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_period: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_SAMPLE_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4008    det_deg_ctr ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_deglitch_time  :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_deglitch_en    :  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}FSC_CTRL_AUD_DET_DEG_CTR_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_400C    det_int_en ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 fsc_intr_en        :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}FSC_CTRL_AUD_DET_INT_EN_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4010    det_int_ctr ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 fsc_intr_clear     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}FSC_CTRL_AUD_DET_INT_CTR_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4014    pwm_op_mode_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_pol_control_ch0: 2;    //  1:0
    UINT32 reg_pwm_en_ch0     :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}FSC_CTRL_AUD_PWM_OP_MODE_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4018    pwm_op_mode_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_pol_control_ch1: 2;    //  1:0
    UINT32 reg_pwm_en_ch1     :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}FSC_CTRL_AUD_PWM_OP_MODE_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_401C    pwm_op_mode_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_pol_control_ch2: 2;    //  1:0
    UINT32 reg_pwm_en_ch2     :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}FSC_CTRL_AUD_PWM_OP_MODE_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4020    pwm_duty_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_duty_ch0   : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_AUD_PWM_DUTY_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4024    pwm_duty_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_duty_ch1   : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_AUD_PWM_DUTY_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4028    pwm_duty_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_duty_ch2   : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_AUD_PWM_DUTY_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_402C    pwm_gen_clk_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_gen_clk_ch0: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_AUD_PWM_GEN_CLK_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4030    pwm_gen_clk_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_gen_clk_ch1: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_AUD_PWM_GEN_CLK_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4034    pwm_gen_clk_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_gen_clk_ch2: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_AUD_PWM_GEN_CLK_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4038    det_int_status ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 fsc_intr           :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}FSC_CTRL_AUD_DET_INT_STATUS_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_403C    det_count_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch0: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_COUNT_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4040    det_count_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch1: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_COUNT_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4044    det_count_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch2: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_COUNT_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4048    det_count_3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch3: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_COUNT_3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_404C    det_count_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch4: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_COUNT_4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4050    det_count_5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch5: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_COUNT_5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4054    det_count_6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch6: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_COUNT_6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4058    det_count_7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch7: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_COUNT_7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_405C    det_count_8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch8: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_COUNT_8_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4060    det_count_9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch9: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_COUNT_9_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4064    det_avg_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch0: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_AVG_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4068    det_avg_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch1: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_AVG_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_406C    det_avg_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch2: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_AVG_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4070    det_avg_3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch3: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_AVG_3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4074    det_avg_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch4: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_AVG_4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4078    det_avg_5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch5: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_AVG_5_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_407C    det_avg_6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch6: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_AVG_6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4080    det_avg_7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch7: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_AVG_7_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4084    det_avg_8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch8: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_AVG_8_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_4088    det_avg_9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch9: 32;    //  31:0
    };
}FSC_CTRL_AUD_DET_AVG_9_O26A0_T;

/*-----------------------------------------------------------------------------------------
    fsc_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FSC_CTRL_AUD_REG_PWM_DET_EN_O26A0_T    reg_pwm_det_en;      // 0xCE7B_4000
    FSC_CTRL_AUD_DET_SAMPLE_0_O26A0_T    det_sample_0;          // 0xCE7B_4004
    FSC_CTRL_AUD_DET_DEG_CTR_O26A0_T    det_deg_ctr;            // 0xCE7B_4008
    FSC_CTRL_AUD_DET_INT_EN_O26A0_T    det_int_en ;             // 0xCE7B_400C
    FSC_CTRL_AUD_DET_INT_CTR_O26A0_T    det_int_ctr;            // 0xCE7B_4010
    FSC_CTRL_AUD_PWM_OP_MODE_0_O26A0_T    pwm_op_mode_0;        // 0xCE7B_4014
    FSC_CTRL_AUD_PWM_OP_MODE_1_O26A0_T    pwm_op_mode_1;        // 0xCE7B_4018
    FSC_CTRL_AUD_PWM_OP_MODE_2_O26A0_T    pwm_op_mode_2;        // 0xCE7B_401C
    FSC_CTRL_AUD_PWM_DUTY_0_O26A0_T    pwm_duty_0 ;             // 0xCE7B_4020
    FSC_CTRL_AUD_PWM_DUTY_1_O26A0_T    pwm_duty_1 ;             // 0xCE7B_4024
    FSC_CTRL_AUD_PWM_DUTY_2_O26A0_T    pwm_duty_2 ;             // 0xCE7B_4028
    FSC_CTRL_AUD_PWM_GEN_CLK_0_O26A0_T    pwm_gen_clk_0;        // 0xCE7B_402C
    FSC_CTRL_AUD_PWM_GEN_CLK_1_O26A0_T    pwm_gen_clk_1;        // 0xCE7B_4030
    FSC_CTRL_AUD_PWM_GEN_CLK_2_O26A0_T    pwm_gen_clk_2;        // 0xCE7B_4034
    FSC_CTRL_AUD_DET_INT_STATUS_O26A0_T    det_int_status;      // 0xCE7B_4038
    FSC_CTRL_AUD_DET_COUNT_0_O26A0_T    det_count_0;            // 0xCE7B_403C
    FSC_CTRL_AUD_DET_COUNT_1_O26A0_T    det_count_1;            // 0xCE7B_4040
    FSC_CTRL_AUD_DET_COUNT_2_O26A0_T    det_count_2;            // 0xCE7B_4044
    FSC_CTRL_AUD_DET_COUNT_3_O26A0_T    det_count_3;            // 0xCE7B_4048
    FSC_CTRL_AUD_DET_COUNT_4_O26A0_T    det_count_4;            // 0xCE7B_404C
    FSC_CTRL_AUD_DET_COUNT_5_O26A0_T    det_count_5;            // 0xCE7B_4050
    FSC_CTRL_AUD_DET_COUNT_6_O26A0_T    det_count_6;            // 0xCE7B_4054
    FSC_CTRL_AUD_DET_COUNT_7_O26A0_T    det_count_7;            // 0xCE7B_4058
    FSC_CTRL_AUD_DET_COUNT_8_O26A0_T    det_count_8;            // 0xCE7B_405C
    FSC_CTRL_AUD_DET_COUNT_9_O26A0_T    det_count_9;            // 0xCE7B_4060
    FSC_CTRL_AUD_DET_AVG_0_O26A0_T     det_avg_0  ;             // 0xCE7B_4064
    FSC_CTRL_AUD_DET_AVG_1_O26A0_T     det_avg_1  ;             // 0xCE7B_4068
    FSC_CTRL_AUD_DET_AVG_2_O26A0_T     det_avg_2  ;             // 0xCE7B_406C
    FSC_CTRL_AUD_DET_AVG_3_O26A0_T     det_avg_3  ;             // 0xCE7B_4070
    FSC_CTRL_AUD_DET_AVG_4_O26A0_T     det_avg_4  ;             // 0xCE7B_4074
    FSC_CTRL_AUD_DET_AVG_5_O26A0_T     det_avg_5  ;             // 0xCE7B_4078
    FSC_CTRL_AUD_DET_AVG_6_O26A0_T     det_avg_6  ;             // 0xCE7B_407C
    FSC_CTRL_AUD_DET_AVG_7_O26A0_T     det_avg_7  ;             // 0xCE7B_4080
    FSC_CTRL_AUD_DET_AVG_8_O26A0_T     det_avg_8  ;             // 0xCE7B_4084
    FSC_CTRL_AUD_DET_AVG_9_O26A0_T     det_avg_9  ;             // 0xCE7B_4088
}FSC_CTRL_AUD_REG_O26A0_T;
/* 35 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FSC_CTRL_AUD_REG_O26A0_H_

/* from 'O26_CTOP_FSCON_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

