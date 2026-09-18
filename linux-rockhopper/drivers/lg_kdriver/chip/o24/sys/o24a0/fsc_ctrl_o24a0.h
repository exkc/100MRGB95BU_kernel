#ifndef _FSC_CTRL_REG_H_
#define _FSC_CTRL_REG_H_

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
    0xCEC8_3000    reg_pwm_det_en ''
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
}FSC_CTRL_REG_PWM_DET_EN;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3004    det_sample_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_period   : 32;    //  31: 0
}FSC_CTRL_DET_SAMPLE_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3008    det_deg_ctr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_deglitch_time         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_deglitch_en           :  1,    //      4
                              : 27;    //   31:5 reserved
}FSC_CTRL_DET_DEG_CTR;

/*-----------------------------------------------------------------------------------------
    0xCEC8_300C    det_int_en ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    fsc_intr_en               :  1,    //      0
                              : 31;    //   31:1 reserved
}FSC_CTRL_DET_INT_EN;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3010    det_int_ctr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    fsc_intr_clear            :  1,    //      0
                              : 31;    //   31:1 reserved
}FSC_CTRL_DET_INT_CTR;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3014    pwm_op_mode_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_pol_control_ch0   :  2,    //   1: 0
    reg_pwm_en_ch0            :  1,    //      2
                              : 29;    //   31:3 reserved
}FSC_CTRL_PWM_OP_MODE_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3018    pwm_op_mode_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_pol_control_ch1   :  2,    //   1: 0
    reg_pwm_en_ch1            :  1,    //      2
                              : 29;    //   31:3 reserved
}FSC_CTRL_PWM_OP_MODE_1;

/*-----------------------------------------------------------------------------------------
    0xCEC8_301C    pwm_op_mode_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_pol_control_ch2   :  2,    //   1: 0
    reg_pwm_en_ch2            :  1,    //      2
                              : 29;    //   31:3 reserved
}FSC_CTRL_PWM_OP_MODE_2;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3020    pwm_duty_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_duty_ch0          : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_PWM_DUTY_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3024    pwm_duty_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_duty_ch1          : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_PWM_DUTY_1;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3028    pwm_duty_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_duty_ch2          : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_PWM_DUTY_2;

/*-----------------------------------------------------------------------------------------
    0xCEC8_302C    pwm_gen_clk_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_gen_clk_ch0       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_PWM_GEN_CLK_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3030    pwm_gen_clk_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_gen_clk_ch1       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_PWM_GEN_CLK_1;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3034    pwm_gen_clk_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_gen_clk_ch2       : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}FSC_CTRL_PWM_GEN_CLK_2;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3038    det_int_status ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    fsc_intr                  :  1,    //      0
                              : 31;    //   31:1 reserved
}FSC_CTRL_DET_INT_STATUS;

/*-----------------------------------------------------------------------------------------
    0xCEC8_303C    det_count_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch0 : 32;    //  31: 0
}FSC_CTRL_DET_COUNT_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3040    det_count_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch1 : 32;    //  31: 0
}FSC_CTRL_DET_COUNT_1;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3044    det_count_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch2 : 32;    //  31: 0
}FSC_CTRL_DET_COUNT_2;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3048    det_count_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch3 : 32;    //  31: 0
}FSC_CTRL_DET_COUNT_3;

/*-----------------------------------------------------------------------------------------
    0xCEC8_304C    det_count_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch4 : 32;    //  31: 0
}FSC_CTRL_DET_COUNT_4;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3050    det_count_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch5 : 32;    //  31: 0
}FSC_CTRL_DET_COUNT_5;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3054    det_count_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch6 : 32;    //  31: 0
}FSC_CTRL_DET_COUNT_6;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3058    det_count_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch7 : 32;    //  31: 0
}FSC_CTRL_DET_COUNT_7;

/*-----------------------------------------------------------------------------------------
    0xCEC8_305C    det_count_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch8 : 32;    //  31: 0
}FSC_CTRL_DET_COUNT_8;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3060    det_count_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_ch9 : 32;    //  31: 0
}FSC_CTRL_DET_COUNT_9;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3064    det_avg_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch0: 32;    //  31:0
}FSC_CTRL_DET_AVG_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3068    det_avg_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch1: 32;    //  31:0
}FSC_CTRL_DET_AVG_1;

/*-----------------------------------------------------------------------------------------
    0xCEC8_306C    det_avg_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch2: 32;    //  31:0
}FSC_CTRL_DET_AVG_2;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3070    det_avg_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch3: 32;    //  31:0
}FSC_CTRL_DET_AVG_3;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3074    det_avg_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch4: 32;    //  31:0
}FSC_CTRL_DET_AVG_4;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3078    det_avg_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch5: 32;    //  31:0
}FSC_CTRL_DET_AVG_5;

/*-----------------------------------------------------------------------------------------
    0xCEC8_307C    det_avg_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch6: 32;    //  31:0
}FSC_CTRL_DET_AVG_6;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3080    det_avg_7 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch7: 32;    //  31:0
}FSC_CTRL_DET_AVG_7;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3084    det_avg_8 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch8: 32;    //  31:0
}FSC_CTRL_DET_AVG_8;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3088    det_avg_9 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pwm_sampling_data_avg_ch9: 32;    //  31:0
}FSC_CTRL_DET_AVG_9;

/*-----------------------------------------------------------------------------------------
    batg_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FSC_CTRL_REG_PWM_DET_EN            reg_pwm_det_en;          // 0xCEC8_3000
    FSC_CTRL_DET_SAMPLE_0              det_sample_0;            // 0xCEC8_3004
    FSC_CTRL_DET_DEG_CTR               det_deg_ctr;             // 0xCEC8_3008
    FSC_CTRL_DET_INT_EN                det_int_en ;             // 0xCEC8_300C
    FSC_CTRL_DET_INT_CTR               det_int_ctr;             // 0xCEC8_3010
    FSC_CTRL_PWM_OP_MODE_0             pwm_op_mode_0;           // 0xCEC8_3014
    FSC_CTRL_PWM_OP_MODE_1             pwm_op_mode_1;           // 0xCEC8_3018
    FSC_CTRL_PWM_OP_MODE_2             pwm_op_mode_2;           // 0xCEC8_301C
    FSC_CTRL_PWM_DUTY_0                pwm_duty_0 ;             // 0xCEC8_3020
    FSC_CTRL_PWM_DUTY_1                pwm_duty_1 ;             // 0xCEC8_3024
    FSC_CTRL_PWM_DUTY_2                pwm_duty_2 ;             // 0xCEC8_3028
    FSC_CTRL_PWM_GEN_CLK_0             pwm_gen_clk_0;           // 0xCEC8_302C
    FSC_CTRL_PWM_GEN_CLK_1             pwm_gen_clk_1;           // 0xCEC8_3030
    FSC_CTRL_PWM_GEN_CLK_2             pwm_gen_clk_2;           // 0xCEC8_3034
    FSC_CTRL_DET_INT_STATUS            det_int_status;          // 0xCEC8_3038
    FSC_CTRL_DET_COUNT_0               det_count_0;             // 0xCEC8_303C
    FSC_CTRL_DET_COUNT_1               det_count_1;             // 0xCEC8_3040
    FSC_CTRL_DET_COUNT_2               det_count_2;             // 0xCEC8_3044
    FSC_CTRL_DET_COUNT_3               det_count_3;             // 0xCEC8_3048
    FSC_CTRL_DET_COUNT_4               det_count_4;             // 0xCEC8_304C
    FSC_CTRL_DET_COUNT_5               det_count_5;             // 0xCEC8_3050
    FSC_CTRL_DET_COUNT_6               det_count_6;             // 0xCEC8_3054
    FSC_CTRL_DET_COUNT_7               det_count_7;             // 0xCEC8_3058
    FSC_CTRL_DET_COUNT_8               det_count_8;             // 0xCEC8_305C
    FSC_CTRL_DET_COUNT_9               det_count_9;             // 0xCEC8_3060
    FSC_CTRL_DET_AVG_0                 det_avg_0  ;             // 0xCEC8_3064
    FSC_CTRL_DET_AVG_1                 det_avg_1  ;             // 0xCEC8_3068
    FSC_CTRL_DET_AVG_2                 det_avg_2  ;             // 0xCEC8_306C
    FSC_CTRL_DET_AVG_3                 det_avg_3  ;             // 0xCEC8_3070
    FSC_CTRL_DET_AVG_4                 det_avg_4  ;             // 0xCEC8_3074
    FSC_CTRL_DET_AVG_5                 det_avg_5  ;             // 0xCEC8_3078
    FSC_CTRL_DET_AVG_6                 det_avg_6  ;             // 0xCEC8_307C
    FSC_CTRL_DET_AVG_7                 det_avg_7  ;             // 0xCEC8_3080
    FSC_CTRL_DET_AVG_8                 det_avg_8  ;             // 0xCEC8_3084
    FSC_CTRL_DET_AVG_9                 det_avg_9  ;             // 0xCEC8_3088
}FSC_CTRL_REG_O24A0_T;
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

#define FSC_CTRL_REG_PWM_DET_EN_OFF                         (BASEADDRESS+0x0000)
#define FSC_CTRL_DET_SAMPLE_0_OFF                           (BASEADDRESS+0x0004)
#define FSC_CTRL_DET_DEG_CTR_OFF                            (BASEADDRESS+0x0008)
#define FSC_CTRL_DET_INT_EN_OFF                             (BASEADDRESS+0x000C)
#define FSC_CTRL_DET_INT_CTR_OFF                            (BASEADDRESS+0x0010)
#define FSC_CTRL_PWM_OP_MODE_0_OFF                          (BASEADDRESS+0x0014)
#define FSC_CTRL_PWM_OP_MODE_1_OFF                          (BASEADDRESS+0x0018)
#define FSC_CTRL_PWM_OP_MODE_2_OFF                          (BASEADDRESS+0x001C)
#define FSC_CTRL_PWM_DUTY_0_OFF                             (BASEADDRESS+0x0020)
#define FSC_CTRL_PWM_DUTY_1_OFF                             (BASEADDRESS+0x0024)
#define FSC_CTRL_PWM_DUTY_2_OFF                             (BASEADDRESS+0x0028)
#define FSC_CTRL_PWM_GEN_CLK_0_OFF                          (BASEADDRESS+0x002C)
#define FSC_CTRL_PWM_GEN_CLK_1_OFF                          (BASEADDRESS+0x0030)
#define FSC_CTRL_PWM_GEN_CLK_2_OFF                          (BASEADDRESS+0x0034)
#define FSC_CTRL_DET_INT_STATUS_OFF                         (BASEADDRESS+0x0038)
#define FSC_CTRL_DET_COUNT_0_OFF                            (BASEADDRESS+0x003C)
#define FSC_CTRL_DET_COUNT_1_OFF                            (BASEADDRESS+0x0040)
#define FSC_CTRL_DET_COUNT_2_OFF                            (BASEADDRESS+0x0044)
#define FSC_CTRL_DET_COUNT_3_OFF                            (BASEADDRESS+0x0048)
#define FSC_CTRL_DET_COUNT_4_OFF                            (BASEADDRESS+0x004C)
#define FSC_CTRL_DET_COUNT_5_OFF                            (BASEADDRESS+0x0050)
#define FSC_CTRL_DET_COUNT_6_OFF                            (BASEADDRESS+0x0054)
#define FSC_CTRL_DET_COUNT_7_OFF                            (BASEADDRESS+0x0058)
#define FSC_CTRL_DET_COUNT_8_OFF                            (BASEADDRESS+0x005C)
#define FSC_CTRL_DET_COUNT_9_OFF                            (BASEADDRESS+0x0060)
#define FSC_CTRL_DET_AVG_0_OFF                              (BASEADDRESS+0x0064)
#define FSC_CTRL_DET_AVG_1_OFF                              (BASEADDRESS+0x0068)
#define FSC_CTRL_DET_AVG_2_OFF                              (BASEADDRESS+0x006C)
#define FSC_CTRL_DET_AVG_3_OFF                              (BASEADDRESS+0x0070)
#define FSC_CTRL_DET_AVG_4_OFF                              (BASEADDRESS+0x0074)
#define FSC_CTRL_DET_AVG_5_OFF                              (BASEADDRESS+0x0078)
#define FSC_CTRL_DET_AVG_6_OFF                              (BASEADDRESS+0x007C)
#define FSC_CTRL_DET_AVG_7_OFF                              (BASEADDRESS+0x0080)
#define FSC_CTRL_DET_AVG_8_OFF                              (BASEADDRESS+0x0084)
#define FSC_CTRL_DET_AVG_9_OFF                              (BASEADDRESS+0x0088)

/*-----------------------------------------------------------------------------------------
    0xCEC8_3000    reg_pwm_det_en ''
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
}FSC_CTRL_REG_PWM_DET_EN;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3004    det_sample_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_period: 32;    //  31:0
    };
}FSC_CTRL_DET_SAMPLE_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3008    det_deg_ctr ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_deglitch_time  :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_deglitch_en    :  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}FSC_CTRL_DET_DEG_CTR;

/*-----------------------------------------------------------------------------------------
    0xCEC8_300C    det_int_en ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 fsc_intr_en        :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}FSC_CTRL_DET_INT_EN;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3010    det_int_ctr ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 fsc_intr_clear     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}FSC_CTRL_DET_INT_CTR;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3014    pwm_op_mode_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_pol_control_ch0: 2;    //  1:0
    UINT32 reg_pwm_en_ch0     :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}FSC_CTRL_PWM_OP_MODE_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3018    pwm_op_mode_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_pol_control_ch1: 2;    //  1:0
    UINT32 reg_pwm_en_ch1     :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}FSC_CTRL_PWM_OP_MODE_1;

/*-----------------------------------------------------------------------------------------
    0xCEC8_301C    pwm_op_mode_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_pol_control_ch2: 2;    //  1:0
    UINT32 reg_pwm_en_ch2     :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}FSC_CTRL_PWM_OP_MODE_2;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3020    pwm_duty_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_duty_ch0   : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_PWM_DUTY_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3024    pwm_duty_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_duty_ch1   : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_PWM_DUTY_1;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3028    pwm_duty_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_duty_ch2   : 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_PWM_DUTY_2;

/*-----------------------------------------------------------------------------------------
    0xCEC8_302C    pwm_gen_clk_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_gen_clk_ch0: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_PWM_GEN_CLK_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3030    pwm_gen_clk_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_gen_clk_ch1: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_PWM_GEN_CLK_1;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3034    pwm_gen_clk_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_gen_clk_ch2: 12;    //  11: 0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}FSC_CTRL_PWM_GEN_CLK_2;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3038    det_int_status ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 fsc_intr           :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}FSC_CTRL_DET_INT_STATUS;

/*-----------------------------------------------------------------------------------------
    0xCEC8_303C    det_count_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch0: 32;    //  31:0
    };
}FSC_CTRL_DET_COUNT_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3040    det_count_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch1: 32;    //  31:0
    };
}FSC_CTRL_DET_COUNT_1;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3044    det_count_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch2: 32;    //  31:0
    };
}FSC_CTRL_DET_COUNT_2;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3048    det_count_3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch3: 32;    //  31:0
    };
}FSC_CTRL_DET_COUNT_3;

/*-----------------------------------------------------------------------------------------
    0xCEC8_304C    det_count_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch4: 32;    //  31:0
    };
}FSC_CTRL_DET_COUNT_4;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3050    det_count_5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch5: 32;    //  31:0
    };
}FSC_CTRL_DET_COUNT_5;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3054    det_count_6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch6: 32;    //  31:0
    };
}FSC_CTRL_DET_COUNT_6;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3058    det_count_7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch7: 32;    //  31:0
    };
}FSC_CTRL_DET_COUNT_7;

/*-----------------------------------------------------------------------------------------
    0xCEC8_305C    det_count_8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch8: 32;    //  31:0
    };
}FSC_CTRL_DET_COUNT_8;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3060    det_count_9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_ch9: 32;    //  31:0
    };
}FSC_CTRL_DET_COUNT_9;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3064    det_avg_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch0: 32;    //  31:0
    };
}FSC_CTRL_DET_AVG_0;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3068    det_avg_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch1: 32;    //  31:0
    };
}FSC_CTRL_DET_AVG_1;

/*-----------------------------------------------------------------------------------------
    0xCEC8_306C    det_avg_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch2: 32;    //  31:0
    };
}FSC_CTRL_DET_AVG_2;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3070    det_avg_3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch3: 32;    //  31:0
    };
}FSC_CTRL_DET_AVG_3;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3074    det_avg_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch4: 32;    //  31:0
    };
}FSC_CTRL_DET_AVG_4;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3078    det_avg_5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch5: 32;    //  31:0
    };
}FSC_CTRL_DET_AVG_5;

/*-----------------------------------------------------------------------------------------
    0xCEC8_307C    det_avg_6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch6: 32;    //  31:0
    };
}FSC_CTRL_DET_AVG_6;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3080    det_avg_7 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch7: 32;    //  31:0
    };
}FSC_CTRL_DET_AVG_7;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3084    det_avg_8 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch8: 32;    //  31:0
    };
}FSC_CTRL_DET_AVG_8;

/*-----------------------------------------------------------------------------------------
    0xCEC8_3088    det_avg_9 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pwm_sampling_data_avg_ch9: 32;    //  31:0
    };
}FSC_CTRL_DET_AVG_9;

/*-----------------------------------------------------------------------------------------
    batg_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    FSC_CTRL_REG_PWM_DET_EN            reg_pwm_det_en;          // 0xCEC8_3000
    FSC_CTRL_DET_SAMPLE_0              det_sample_0;            // 0xCEC8_3004
    FSC_CTRL_DET_DEG_CTR               det_deg_ctr;             // 0xCEC8_3008
    FSC_CTRL_DET_INT_EN                det_int_en ;             // 0xCEC8_300C
    FSC_CTRL_DET_INT_CTR               det_int_ctr;             // 0xCEC8_3010
    FSC_CTRL_PWM_OP_MODE_0             pwm_op_mode_0;           // 0xCEC8_3014
    FSC_CTRL_PWM_OP_MODE_1             pwm_op_mode_1;           // 0xCEC8_3018
    FSC_CTRL_PWM_OP_MODE_2             pwm_op_mode_2;           // 0xCEC8_301C
    FSC_CTRL_PWM_DUTY_0                pwm_duty_0 ;             // 0xCEC8_3020
    FSC_CTRL_PWM_DUTY_1                pwm_duty_1 ;             // 0xCEC8_3024
    FSC_CTRL_PWM_DUTY_2                pwm_duty_2 ;             // 0xCEC8_3028
    FSC_CTRL_PWM_GEN_CLK_0             pwm_gen_clk_0;           // 0xCEC8_302C
    FSC_CTRL_PWM_GEN_CLK_1             pwm_gen_clk_1;           // 0xCEC8_3030
    FSC_CTRL_PWM_GEN_CLK_2             pwm_gen_clk_2;           // 0xCEC8_3034
    FSC_CTRL_DET_INT_STATUS            det_int_status;          // 0xCEC8_3038
    FSC_CTRL_DET_COUNT_0               det_count_0;             // 0xCEC8_303C
    FSC_CTRL_DET_COUNT_1               det_count_1;             // 0xCEC8_3040
    FSC_CTRL_DET_COUNT_2               det_count_2;             // 0xCEC8_3044
    FSC_CTRL_DET_COUNT_3               det_count_3;             // 0xCEC8_3048
    FSC_CTRL_DET_COUNT_4               det_count_4;             // 0xCEC8_304C
    FSC_CTRL_DET_COUNT_5               det_count_5;             // 0xCEC8_3050
    FSC_CTRL_DET_COUNT_6               det_count_6;             // 0xCEC8_3054
    FSC_CTRL_DET_COUNT_7               det_count_7;             // 0xCEC8_3058
    FSC_CTRL_DET_COUNT_8               det_count_8;             // 0xCEC8_305C
    FSC_CTRL_DET_COUNT_9               det_count_9;             // 0xCEC8_3060
    FSC_CTRL_DET_AVG_0                 det_avg_0  ;             // 0xCEC8_3064
    FSC_CTRL_DET_AVG_1                 det_avg_1  ;             // 0xCEC8_3068
    FSC_CTRL_DET_AVG_2                 det_avg_2  ;             // 0xCEC8_306C
    FSC_CTRL_DET_AVG_3                 det_avg_3  ;             // 0xCEC8_3070
    FSC_CTRL_DET_AVG_4                 det_avg_4  ;             // 0xCEC8_3074
    FSC_CTRL_DET_AVG_5                 det_avg_5  ;             // 0xCEC8_3078
    FSC_CTRL_DET_AVG_6                 det_avg_6  ;             // 0xCEC8_307C
    FSC_CTRL_DET_AVG_7                 det_avg_7  ;             // 0xCEC8_3080
    FSC_CTRL_DET_AVG_8                 det_avg_8  ;             // 0xCEC8_3084
    FSC_CTRL_DET_AVG_9                 det_avg_9  ;             // 0xCEC8_3088
}FSC_CTRL_REG_O24A0_T;
/* 35 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_FSC_CTRL_REG_H_

/* from 'O24_CTOP_FSCON_Register_Manual.xlsx'  2023.8.24  KJH by LGSiCRDV V3.1C*/

