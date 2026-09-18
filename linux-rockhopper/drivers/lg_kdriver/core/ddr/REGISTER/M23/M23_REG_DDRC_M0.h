#ifndef _REG_DDRC_M0_h
#define _REG_DDRC_M0_h
//Header File for DDRC_M0 in \M23\M23_DRAM_M0_Register_Manual.xls

#define REG_DDRC_M0_DRAM_CONF                                               (APB_DDRC_M0_BASE+0x0000)
#define REG_DDRC_M0_MODE_SEL                                                (APB_DDRC_M0_BASE+0x0004)
#define REG_DDRC_M0_BASE_PERIOD                                             (APB_DDRC_M0_BASE+0x0008)
#define REG_DDRC_M0_ALP                                                     (APB_DDRC_M0_BASE+0x0100)
#define REG_DDRC_M0_CGL                                                     (APB_DDRC_M0_BASE+0x0104)
#define REG_DDRC_M0_CGL_MON                                                 (APB_DDRC_M0_BASE+0x0108)
#define REG_DDRC_M0_PERFMON                                                 (APB_DDRC_M0_BASE+0x0200)
#define REG_DDRC_M0_PERFMON_EMG_MAX                                         (APB_DDRC_M0_BASE+0x0204)
#define REG_DDRC_M0_PERFMON_W0                                              (APB_DDRC_M0_BASE+0x0210)
#define REG_DDRC_M0_PERFMON_W1                                              (APB_DDRC_M0_BASE+0x0214)
#define REG_DDRC_M0_PERFMON_W2                                              (APB_DDRC_M0_BASE+0x0218)
#define REG_DDRC_M0_PERFMON_W3                                              (APB_DDRC_M0_BASE+0x021C)
#define REG_DDRC_M0_PERFMON_R0                                              (APB_DDRC_M0_BASE+0x0220)
#define REG_DDRC_M0_PERFMON_R1                                              (APB_DDRC_M0_BASE+0x0224)
#define REG_DDRC_M0_PERFMON_R2                                              (APB_DDRC_M0_BASE+0x0228)
#define REG_DDRC_M0_PERFMON_R3                                              (APB_DDRC_M0_BASE+0x022C)
#define REG_DDRC_M0_LATMON                                                  (APB_DDRC_M0_BASE+0x0230)
#define REG_DDRC_M0_DFS                                                     (APB_DDRC_M0_BASE+0x0300)
#define REG_DDRC_M0_DFS_RESULT                                              (APB_DDRC_M0_BASE+0x0304)
#define REG_DDRC_M0_ADDR_MAP                                                (APB_DDRC_M0_BASE+0x0400)
#define REG_DDRC_M0_COMMON                                                  (APB_DDRC_M0_BASE+0x0404)
#define REG_DDRC_M0_DATA_ENC0                                               (APB_DDRC_M0_BASE+0x0408)
#define REG_DDRC_M0_DATA_ENC1                                               (APB_DDRC_M0_BASE+0x040C)
#define REG_DDRC_M0_RD_URG                                                  (APB_DDRC_M0_BASE+0x0500)
#define REG_DDRC_M0_WR_URG                                                  (APB_DDRC_M0_BASE+0x0504)
#define REG_DDRC_M0_FIFO_RDY                                                (APB_DDRC_M0_BASE+0x1000)
#define REG_DDRC_M0_FIFO_STATUS                                             (APB_DDRC_M0_BASE+0x1004)
#define REG_DDRC_M0_FIFO_CONF                                               (APB_DDRC_M0_BASE+0x1008)
#define REG_DDRC_M0_LIMITER_EN                                              (APB_DDRC_M0_BASE+0x1010)
#define REG_DDRC_M0_LIMITER_AW_THR                                          (APB_DDRC_M0_BASE+0x1014)
#define REG_DDRC_M0_LIMITER_W_THR                                           (APB_DDRC_M0_BASE+0x1018)
#define REG_DDRC_M0_LIMITER_AR_THR                                          (APB_DDRC_M0_BASE+0x1024)
#define REG_DDRC_M0_LIMITER_R_THR                                           (APB_DDRC_M0_BASE+0x1028)
#define REG_DDRC_M0_FIFO_MUX                                                (APB_DDRC_M0_BASE+0x1100)
#define REG_DDRC_M0_FIFO_MUX_MAX                                            (APB_DDRC_M0_BASE+0x1104)
#define REG_DDRC_M0_FIFO_MUX_WR_PRT                                         (APB_DDRC_M0_BASE+0x1108)
#define REG_DDRC_M0_FIFO_MUX_RD_PRT                                         (APB_DDRC_M0_BASE+0x110C)
#define REG_DDRC_M0_FIFO_MUX_PRT_MAX                                        (APB_DDRC_M0_BASE+0x1110)
#define REG_DDRC_M0_PQ                                                      (APB_DDRC_M0_BASE+0x2000)
#define REG_DDRC_M0_BQ                                                      (APB_DDRC_M0_BASE+0x2004)
#define REG_DDRC_M0_BQ_RW_THR                                               (APB_DDRC_M0_BASE+0x2008)
#define REG_DDRC_M0_BQ_HYB_STV                                              (APB_DDRC_M0_BASE+0x200C)
#define REG_DDRC_M0_LPD4_MAIN_FSM_INIT_0                                    (APB_DDRC_M0_BASE+0x3000)
#define REG_DDRC_M0_LPD4_MAIN_FSM_INIT_1                                    (APB_DDRC_M0_BASE+0x3004)
#define REG_DDRC_M0_LPD4_MAIN_FSM_INIT_2                                    (APB_DDRC_M0_BASE+0x3008)
#define REG_DDRC_M0_LPD4_MAIN_FSM_CTRL                                      (APB_DDRC_M0_BASE+0x300C)
#define REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_0                                (APB_DDRC_M0_BASE+0x3010)
#define REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_1                                (APB_DDRC_M0_BASE+0x3014)
#define REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_2                                (APB_DDRC_M0_BASE+0x3018)
#define REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_3                                (APB_DDRC_M0_BASE+0x301C)
#define REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_4                                (APB_DDRC_M0_BASE+0x3020)
#define REG_DDRC_M0_LPD4_MAIN_FSM_DFS_MRW                                   (APB_DDRC_M0_BASE+0x3024)
#define REG_DDRC_M0_LPD4_MAIN_FSM_CTRLUPD                                   (APB_DDRC_M0_BASE+0x3028)
#define REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_0                                (APB_DDRC_M0_BASE+0x302C)
#define REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_1                                (APB_DDRC_M0_BASE+0x3030)
#define REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_2                                (APB_DDRC_M0_BASE+0x3034)
#define REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_3                                (APB_DDRC_M0_BASE+0x3038)
#define REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_4                                (APB_DDRC_M0_BASE+0x303C)
#define REG_DDRC_M0_LPD4_MR_CTRL_0                                          (APB_DDRC_M0_BASE+0x3050)
#define REG_DDRC_M0_LPD4_MR_CTRL_1                                          (APB_DDRC_M0_BASE+0x3054)
#define REG_DDRC_M0_LPD4_MR_CTRL_2                                          (APB_DDRC_M0_BASE+0x3058)
#define REG_DDRC_M0_LPD4_REF_REQ_CTRL                                       (APB_DDRC_M0_BASE+0x3060)
#define REG_DDRC_M0_LPD4_REF_CTRL                                           (APB_DDRC_M0_BASE+0x3070)
#define REG_DDRC_M0_LPD4_BANK_FSM                                           (APB_DDRC_M0_BASE+0x3080)
#define REG_DDRC_M0_LPD4_BANK_STATUS                                        (APB_DDRC_M0_BASE+0x30A0)
#define REG_DDRC_M0_LPD4_PHY_IF                                             (APB_DDRC_M0_BASE+0x30C0)
#define REG_DDRC_M0_LPD4_DFS0_MR_0_CH0                                      (APB_DDRC_M0_BASE+0x3100)
#define REG_DDRC_M0_LPD4_DFS0_MR_1_CH0                                      (APB_DDRC_M0_BASE+0x3104)
#define REG_DDRC_M0_LPD4_DFS0_MR_2_CH0                                      (APB_DDRC_M0_BASE+0x3108)
#define REG_DDRC_M0_LPD4_DFS0_MR_3_CH0                                      (APB_DDRC_M0_BASE+0x310C)
#define REG_DDRC_M0_LPD4_DFS0_MR_4_CH0                                      (APB_DDRC_M0_BASE+0x3110)
#define REG_DDRC_M0_LPD4_DFS0_MR_5_CH0                                      (APB_DDRC_M0_BASE+0x3114)
#define REG_DDRC_M0_LPD4_DFS0_MR_6_CH0                                      (APB_DDRC_M0_BASE+0x3118)
#define REG_DDRC_M0_LPD4_DFS0_MR_0_CH1                                      (APB_DDRC_M0_BASE+0x3120)
#define REG_DDRC_M0_LPD4_DFS0_MR_1_CH1                                      (APB_DDRC_M0_BASE+0x3124)
#define REG_DDRC_M0_LPD4_DFS0_MR_2_CH1                                      (APB_DDRC_M0_BASE+0x3128)
#define REG_DDRC_M0_LPD4_DFS0_MR_3_CH1                                      (APB_DDRC_M0_BASE+0x312C)
#define REG_DDRC_M0_LPD4_DFS0_MR_4_CH1                                      (APB_DDRC_M0_BASE+0x3130)
#define REG_DDRC_M0_LPD4_DFS0_MR_5_CH1                                      (APB_DDRC_M0_BASE+0x3134)
#define REG_DDRC_M0_LPD4_DFS0_MR_6_CH1                                      (APB_DDRC_M0_BASE+0x3138)
#define REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_0                                    (APB_DDRC_M0_BASE+0x3140)
#define REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_1                                    (APB_DDRC_M0_BASE+0x3144)
#define REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_2                                    (APB_DDRC_M0_BASE+0x3148)
#define REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_3                                    (APB_DDRC_M0_BASE+0x314C)
#define REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_4                                    (APB_DDRC_M0_BASE+0x3150)
#define REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_5                                    (APB_DDRC_M0_BASE+0x3154)
#define REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_0                                (APB_DDRC_M0_BASE+0x3160)
#define REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_1                                (APB_DDRC_M0_BASE+0x3164)
#define REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_2                                (APB_DDRC_M0_BASE+0x3168)
#define REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_3                                (APB_DDRC_M0_BASE+0x316C)
#define REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_4                                (APB_DDRC_M0_BASE+0x3170)
#define REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_5                                (APB_DDRC_M0_BASE+0x3174)
#define REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_6                                (APB_DDRC_M0_BASE+0x3178)
#define REG_DDRC_M0_LPD4_DFS0_REF_CTRL                                      (APB_DDRC_M0_BASE+0x3190)
#define REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_0                                 (APB_DDRC_M0_BASE+0x31A0)
#define REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_1                                 (APB_DDRC_M0_BASE+0x31A4)
#define REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_2                                 (APB_DDRC_M0_BASE+0x31A8)
#define REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_3                                 (APB_DDRC_M0_BASE+0x31AC)
#define REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_4                                 (APB_DDRC_M0_BASE+0x31B0)
#define REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_5                                 (APB_DDRC_M0_BASE+0x31B4)
#define REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_6                                 (APB_DDRC_M0_BASE+0x31B8)
#define REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_7                                 (APB_DDRC_M0_BASE+0x31BC)
#define REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_8                                 (APB_DDRC_M0_BASE+0x31C0)
#define REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_9                                 (APB_DDRC_M0_BASE+0x31C4)
#define REG_DDRC_M0_LPD4_DFS0_PHY_IF                                        (APB_DDRC_M0_BASE+0x31E0)
#define REG_DDRC_M0_LPD4_DFS1_MR_0_CH0                                      (APB_DDRC_M0_BASE+0x3200)
#define REG_DDRC_M0_LPD4_DFS1_MR_1_CH0                                      (APB_DDRC_M0_BASE+0x3204)
#define REG_DDRC_M0_LPD4_DFS1_MR_2_CH0                                      (APB_DDRC_M0_BASE+0x3208)
#define REG_DDRC_M0_LPD4_DFS1_MR_3_CH0                                      (APB_DDRC_M0_BASE+0x320C)
#define REG_DDRC_M0_LPD4_DFS1_MR_4_CH0                                      (APB_DDRC_M0_BASE+0x3210)
#define REG_DDRC_M0_LPD4_DFS1_MR_5_CH0                                      (APB_DDRC_M0_BASE+0x3214)
#define REG_DDRC_M0_LPD4_DFS1_MR_6_CH0                                      (APB_DDRC_M0_BASE+0x3218)
#define REG_DDRC_M0_LPD4_DFS1_MR_0_CH1                                      (APB_DDRC_M0_BASE+0x3220)
#define REG_DDRC_M0_LPD4_DFS1_MR_1_CH1                                      (APB_DDRC_M0_BASE+0x3224)
#define REG_DDRC_M0_LPD4_DFS1_MR_2_CH1                                      (APB_DDRC_M0_BASE+0x3228)
#define REG_DDRC_M0_LPD4_DFS1_MR_3_CH1                                      (APB_DDRC_M0_BASE+0x322C)
#define REG_DDRC_M0_LPD4_DFS1_MR_4_CH1                                      (APB_DDRC_M0_BASE+0x3230)
#define REG_DDRC_M0_LPD4_DFS1_MR_5_CH1                                      (APB_DDRC_M0_BASE+0x3234)
#define REG_DDRC_M0_LPD4_DFS1_MR_6_CH1                                      (APB_DDRC_M0_BASE+0x3238)
#define REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_0                                    (APB_DDRC_M0_BASE+0x3240)
#define REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_1                                    (APB_DDRC_M0_BASE+0x3244)
#define REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_2                                    (APB_DDRC_M0_BASE+0x3248)
#define REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_3                                    (APB_DDRC_M0_BASE+0x324C)
#define REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_4                                    (APB_DDRC_M0_BASE+0x3250)
#define REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_5                                    (APB_DDRC_M0_BASE+0x3254)
#define REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_0                                (APB_DDRC_M0_BASE+0x3260)
#define REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_1                                (APB_DDRC_M0_BASE+0x3264)
#define REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_2                                (APB_DDRC_M0_BASE+0x3268)
#define REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_3                                (APB_DDRC_M0_BASE+0x326C)
#define REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_4                                (APB_DDRC_M0_BASE+0x3270)
#define REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_5                                (APB_DDRC_M0_BASE+0x3274)
#define REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_6                                (APB_DDRC_M0_BASE+0x3278)
#define REG_DDRC_M0_LPD4_DFS1_REF_CTRL                                      (APB_DDRC_M0_BASE+0x3290)
#define REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_0                                 (APB_DDRC_M0_BASE+0x32A0)
#define REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_1                                 (APB_DDRC_M0_BASE+0x32A4)
#define REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_2                                 (APB_DDRC_M0_BASE+0x32A8)
#define REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_3                                 (APB_DDRC_M0_BASE+0x32AC)
#define REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_4                                 (APB_DDRC_M0_BASE+0x32B0)
#define REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_5                                 (APB_DDRC_M0_BASE+0x32B4)
#define REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_6                                 (APB_DDRC_M0_BASE+0x32B8)
#define REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_7                                 (APB_DDRC_M0_BASE+0x32BC)
#define REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_8                                 (APB_DDRC_M0_BASE+0x32C0)
#define REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_9                                 (APB_DDRC_M0_BASE+0x32C4)
#define REG_DDRC_M0_LPD4_DFS1_PHY_IF                                        (APB_DDRC_M0_BASE+0x32E0)
#define REG_DDRC_M0_LPD4_DFS2_MR_0_CH0                                      (APB_DDRC_M0_BASE+0x3300)
#define REG_DDRC_M0_LPD4_DFS2_MR_1_CH0                                      (APB_DDRC_M0_BASE+0x3304)
#define REG_DDRC_M0_LPD4_DFS2_MR_2_CH0                                      (APB_DDRC_M0_BASE+0x3308)
#define REG_DDRC_M0_LPD4_DFS2_MR_3_CH0                                      (APB_DDRC_M0_BASE+0x330C)
#define REG_DDRC_M0_LPD4_DFS2_MR_4_CH0                                      (APB_DDRC_M0_BASE+0x3310)
#define REG_DDRC_M0_LPD4_DFS2_MR_5_CH0                                      (APB_DDRC_M0_BASE+0x3314)
#define REG_DDRC_M0_LPD4_DFS2_MR_6_CH0                                      (APB_DDRC_M0_BASE+0x3318)
#define REG_DDRC_M0_LPD4_DFS2_MR_0_CH1                                      (APB_DDRC_M0_BASE+0x3320)
#define REG_DDRC_M0_LPD4_DFS2_MR_1_CH1                                      (APB_DDRC_M0_BASE+0x3324)
#define REG_DDRC_M0_LPD4_DFS2_MR_2_CH1                                      (APB_DDRC_M0_BASE+0x3328)
#define REG_DDRC_M0_LPD4_DFS2_MR_3_CH1                                      (APB_DDRC_M0_BASE+0x332C)
#define REG_DDRC_M0_LPD4_DFS2_MR_4_CH1                                      (APB_DDRC_M0_BASE+0x3330)
#define REG_DDRC_M0_LPD4_DFS2_MR_5_CH1                                      (APB_DDRC_M0_BASE+0x3334)
#define REG_DDRC_M0_LPD4_DFS2_MR_6_CH1                                      (APB_DDRC_M0_BASE+0x3338)
#define REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_0                                    (APB_DDRC_M0_BASE+0x3340)
#define REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_1                                    (APB_DDRC_M0_BASE+0x3344)
#define REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_2                                    (APB_DDRC_M0_BASE+0x3348)
#define REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_3                                    (APB_DDRC_M0_BASE+0x334C)
#define REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_4                                    (APB_DDRC_M0_BASE+0x3350)
#define REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_5                                    (APB_DDRC_M0_BASE+0x3354)
#define REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_0                                (APB_DDRC_M0_BASE+0x3360)
#define REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_1                                (APB_DDRC_M0_BASE+0x3364)
#define REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_2                                (APB_DDRC_M0_BASE+0x3368)
#define REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_3                                (APB_DDRC_M0_BASE+0x336C)
#define REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_4                                (APB_DDRC_M0_BASE+0x3370)
#define REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_5                                (APB_DDRC_M0_BASE+0x3374)
#define REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_6                                (APB_DDRC_M0_BASE+0x3378)
#define REG_DDRC_M0_LPD4_DFS2_REF_CTRL                                      (APB_DDRC_M0_BASE+0x3390)
#define REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_0                                 (APB_DDRC_M0_BASE+0x33A0)
#define REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_1                                 (APB_DDRC_M0_BASE+0x33A4)
#define REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_2                                 (APB_DDRC_M0_BASE+0x33A8)
#define REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_3                                 (APB_DDRC_M0_BASE+0x33AC)
#define REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_4                                 (APB_DDRC_M0_BASE+0x33B0)
#define REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_5                                 (APB_DDRC_M0_BASE+0x33B4)
#define REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_6                                 (APB_DDRC_M0_BASE+0x33B8)
#define REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_7                                 (APB_DDRC_M0_BASE+0x33BC)
#define REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_8                                 (APB_DDRC_M0_BASE+0x33C0)
#define REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_9                                 (APB_DDRC_M0_BASE+0x33C4)
#define REG_DDRC_M0_LPD4_DFS2_PHY_IF                                        (APB_DDRC_M0_BASE+0x33E0)
#define REG_DDRC_M0_DEBUG_COMMON                                            (APB_DDRC_M0_BASE+0x5000)
#define REG_DDRC_M0_DEBUG_PERIOD                                            (APB_DDRC_M0_BASE+0x5004)
#define REG_DDRC_M0_IRQ_MASK                                                (APB_DDRC_M0_BASE+0x5010)
#define REG_DDRC_M0_IRQ_STATUS                                              (APB_DDRC_M0_BASE+0x5014)
#define REG_DDRC_M0_DEBUG_BUS_IF                                            (APB_DDRC_M0_BASE+0x5100)
#define REG_DDRC_M0_DEBUG_PORT_IF_0                                         (APB_DDRC_M0_BASE+0x5200)
#define REG_DDRC_M0_DEBUG_PORT_IF_1                                         (APB_DDRC_M0_BASE+0x5204)
#define REG_DDRC_M0_DEBUG_PORT_IF_2                                         (APB_DDRC_M0_BASE+0x5208)
#define REG_DDRC_M0_DEBUG_PORT_IF_3                                         (APB_DDRC_M0_BASE+0x520C)
#define REG_DDRC_M0_DEBUG_PORT_IF_4                                         (APB_DDRC_M0_BASE+0x5210)
#define REG_DDRC_M0_DEBUG_PORT_IF_5                                         (APB_DDRC_M0_BASE+0x5214)
#define REG_DDRC_M0_DEBUG_PORT_IF_6                                         (APB_DDRC_M0_BASE+0x5218)
#define REG_DDRC_M0_DEBUG_PORT_IF_7                                         (APB_DDRC_M0_BASE+0x521C)
#define REG_DDRC_M0_DEBUG_UQ_1                                              (APB_DDRC_M0_BASE+0x5300)
#define REG_DDRC_M0_DEBUG_UQ_2                                              (APB_DDRC_M0_BASE+0x5304)
#define REG_DDRC_M0_DEBUG_SCH0                                              (APB_DDRC_M0_BASE+0x5400)
#define REG_DDRC_M0_DEBUG_SCH1                                              (APB_DDRC_M0_BASE+0x5404)
#define REG_DDRC_M0_DEBUG_ALP                                               (APB_DDRC_M0_BASE+0x5500)
#define REG_DDRC_M0_DEBUG_ALP_ENTRY_NUM                                     (APB_DDRC_M0_BASE+0x5504)
#define REG_DDRC_M0_DEBUG_ALP_TIME                                          (APB_DDRC_M0_BASE+0x5508)
#define REG_DDRC_M0_DEBUG_ALP_WAIT_CNT                                      (APB_DDRC_M0_BASE+0x550C)
#define REG_DDRC_M0_DEBUG_DFS                                               (APB_DDRC_M0_BASE+0x5600)
#define REG_DDRC_M0_DEBUG_IDLE_CNT                                          (APB_DDRC_M0_BASE+0x5700)
#define REG_DDRC_M0_DEBUG_RD_CNT                                            (APB_DDRC_M0_BASE+0x5704)
#define REG_DDRC_M0_DEBUG_RDL_CNT                                           (APB_DDRC_M0_BASE+0x5708)
#define REG_DDRC_M0_DEBUG_RWR_CNT                                           (APB_DDRC_M0_BASE+0x5710)
#define REG_DDRC_M0_DEBUG_MWR_CNT                                           (APB_DDRC_M0_BASE+0x5714)
#define REG_DDRC_M0_DEBUG_WRL_CNT                                           (APB_DDRC_M0_BASE+0x5718)
#define REG_DDRC_M0_DEBUG_PRG_CNT                                           (APB_DDRC_M0_BASE+0x5720)
#define REG_DDRC_M0_DEBUG_REF_CNT                                           (APB_DDRC_M0_BASE+0x5724)
#define REG_DDRC_M0_DEBUG_ACT_CNT                                           (APB_DDRC_M0_BASE+0x5728)
#define REG_DDRC_M0_DEBUG_RW_SWC_CNT                                        (APB_DDRC_M0_BASE+0x572C)
#define REG_DDRC_M0_DEBUG_R_URG_SWC_CNT                                     (APB_DDRC_M0_BASE+0x5730)
#define REG_DDRC_M0_DEBUG_R_REQ_ROW_HIT_CNT                                 (APB_DDRC_M0_BASE+0x5734)
#define REG_DDRC_M0_DEBUG_R_REQ_HIT_CNT                                     (APB_DDRC_M0_BASE+0x5738)
#define REG_DDRC_M0_DEBUG_R_URG_ROW_HIT_CNT                                 (APB_DDRC_M0_BASE+0x573C)
#define REG_DDRC_M0_DEBUG_R_URG_HIT_CNT                                     (APB_DDRC_M0_BASE+0x5740)
#define REG_DDRC_M0_DEBUG_R_ROW_HIT_CNT                                     (APB_DDRC_M0_BASE+0x5744)
#define REG_DDRC_M0_DEBUG_R_LUCKY_HIT_CNT                                   (APB_DDRC_M0_BASE+0x5748)
#define REG_DDRC_M0_DEBUG_W_URG_SWC_CNT                                     (APB_DDRC_M0_BASE+0x5750)
#define REG_DDRC_M0_DEBUG_W_REQ_ROW_HIT_CNT                                 (APB_DDRC_M0_BASE+0x5754)
#define REG_DDRC_M0_DEBUG_W_REQ_HIT_CNT                                     (APB_DDRC_M0_BASE+0x5758)
#define REG_DDRC_M0_DEBUG_W_URG_ROW_HIT_CNT                                 (APB_DDRC_M0_BASE+0x575C)
#define REG_DDRC_M0_DEBUG_W_URG_HIT_CNT                                     (APB_DDRC_M0_BASE+0x5760)
#define REG_DDRC_M0_DEBUG_W_ROW_HIT_CNT                                     (APB_DDRC_M0_BASE+0x5764)
#define REG_DDRC_M0_DEBUG_W_LUCKY_HIT_CNT                                   (APB_DDRC_M0_BASE+0x5768)
#define REG_DDRC_M0_DEBUG_MAX_LAT_QOS                                       (APB_DDRC_M0_BASE+0x5770)
#define REG_DDRC_M0_DEBUG_R_HYB_SWC_CNT                                     (APB_DDRC_M0_BASE+0x5800)
#define REG_DDRC_M0_DEBUG_W_HYB_SWC_CNT                                     (APB_DDRC_M0_BASE+0x5804)
#define REG_DDRC_M0_DEBUG_R_FIFO_0_PRT_CNT                                  (APB_DDRC_M0_BASE+0x5900)
#define REG_DDRC_M0_DEBUG_R_FIFO_1_PRT_CNT                                  (APB_DDRC_M0_BASE+0x5904)
#define REG_DDRC_M0_DEBUG_R_FIFO_2_PRT_CNT                                  (APB_DDRC_M0_BASE+0x5908)
#define REG_DDRC_M0_DEBUG_R_FIFO_3_PRT_CNT                                  (APB_DDRC_M0_BASE+0x590C)
#define REG_DDRC_M0_DEBUG_W_FIFO_0_PRT_CNT                                  (APB_DDRC_M0_BASE+0x5910)
#define REG_DDRC_M0_DEBUG_W_FIFO_1_PRT_CNT                                  (APB_DDRC_M0_BASE+0x5914)
#define REG_DDRC_M0_DEBUG_W_FIFO_2_PRT_CNT                                  (APB_DDRC_M0_BASE+0x5918)
#define REG_DDRC_M0_DEBUG_W_FIFO_3_PRT_CNT                                  (APB_DDRC_M0_BASE+0x591C)
#define REG_DDRC_M0_DEBUG_LPD4_0                                            (APB_DDRC_M0_BASE+0x6000)
#define REG_DDRC_M0_DEBUG_LPD4_1                                            (APB_DDRC_M0_BASE+0x6004)
#define REG_DDRC_M0_DEBUG_LPD4_2                                            (APB_DDRC_M0_BASE+0x6008)
#define REG_DDRC_M0_DEBUG_LPD4_3                                            (APB_DDRC_M0_BASE+0x600C)
#define REG_DDRC_M0_DEBUG_LPD4_4                                            (APB_DDRC_M0_BASE+0x6010)
#define REG_DDRC_M0_DEBUG_LPD4_5                                            (APB_DDRC_M0_BASE+0x6014)
#define REG_DDRC_M0_DEBUG_LPD4_6                                            (APB_DDRC_M0_BASE+0x6018)
#define REG_DDRC_M0_DEBUG_LPD4_7                                            (APB_DDRC_M0_BASE+0x601C)
#define REG_DDRC_M0_DEBUG_LPD4_8                                            (APB_DDRC_M0_BASE+0x6020)
#define REG_DDRC_M0_DEBUG_LPD4_9                                            (APB_DDRC_M0_BASE+0x6024)
#define REG_DDRC_M0_DEBUG_LPD4_10                                           (APB_DDRC_M0_BASE+0x6028)
#define REG_DDRC_M0_DEBUG_LPD4_11                                           (APB_DDRC_M0_BASE+0x602C)
#define REG_DDRC_M0_DEBUG_LPD4_12                                           (APB_DDRC_M0_BASE+0x6030)
#define REG_DDRC_M0_DEBUG_LPD4_13                                           (APB_DDRC_M0_BASE+0x6034)
#define REG_DDRC_M0_DEBUG_LPD4_14                                           (APB_DDRC_M0_BASE+0x6038)
#define REG_DDRC_M0_DEBUG_LPD4_15                                           (APB_DDRC_M0_BASE+0x603C)
#define REG_DDRC_M0_DEBUG_LPD4_16                                           (APB_DDRC_M0_BASE+0x6040)
#define REG_DDRC_M0_DEBUG_LPD4_MR_0                                         (APB_DDRC_M0_BASE+0x6100)
#define REG_DDRC_M0_DEBUG_LPD4_MR_1                                         (APB_DDRC_M0_BASE+0x6104)
#define REG_DDRC_M0_DEBUG_LPD4_MR_2                                         (APB_DDRC_M0_BASE+0x6108)
#define REG_DDRC_M0_DEBUG_LPD4_MR_3                                         (APB_DDRC_M0_BASE+0x610C)
#define REG_DDRC_M0_DEBUG_LPD4_MR_4                                         (APB_DDRC_M0_BASE+0x6110)
#define REG_DDRC_M0_DEBUG_LPD4_MR_5                                         (APB_DDRC_M0_BASE+0x6114)
#define REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_0                                   (APB_DDRC_M0_BASE+0x6118)
#define REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_1                                   (APB_DDRC_M0_BASE+0x611C)
#define REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_2                                   (APB_DDRC_M0_BASE+0x6120)
#define REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_3                                   (APB_DDRC_M0_BASE+0x6124)
#define REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_4                                   (APB_DDRC_M0_BASE+0x6128)
#define REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_5                                   (APB_DDRC_M0_BASE+0x612C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MRW1                                     (APB_DDRC_M0_BASE+0x6200)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MRW0                                     (APB_DDRC_M0_BASE+0x6204)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_LP_EXIT                                  (APB_DDRC_M0_BASE+0x6208)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_LP_ENTRY                                 (APB_DDRC_M0_BASE+0x620C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_SR_PD_EXIT                               (APB_DDRC_M0_BASE+0x6210)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_SR_PD_ENTRY                              (APB_DDRC_M0_BASE+0x6214)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_SR_EXIT                                  (APB_DDRC_M0_BASE+0x6218)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_SR_ENTRY                                 (APB_DDRC_M0_BASE+0x621C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_PD_EXIT                                  (APB_DDRC_M0_BASE+0x6220)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_PD_ENTRY                                 (APB_DDRC_M0_BASE+0x6224)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_ZQLAT                                    (APB_DDRC_M0_BASE+0x6228)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_ZQCAL                                    (APB_DDRC_M0_BASE+0x622C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_CKE1                                     (APB_DDRC_M0_BASE+0x6230)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_CKE0                                     (APB_DDRC_M0_BASE+0x6234)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_RSTN1                                    (APB_DDRC_M0_BASE+0x6238)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_RSTN0                                    (APB_DDRC_M0_BASE+0x623C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_RD0                                      (APB_DDRC_M0_BASE+0x6240)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_RD1                                      (APB_DDRC_M0_BASE+0x6244)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_RD2                                      (APB_DDRC_M0_BASE+0x6248)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_RD3                                      (APB_DDRC_M0_BASE+0x624C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_RD4                                      (APB_DDRC_M0_BASE+0x6250)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_RD5                                      (APB_DDRC_M0_BASE+0x6254)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_RD6                                      (APB_DDRC_M0_BASE+0x6258)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_RD7                                      (APB_DDRC_M0_BASE+0x625C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MWR0                                     (APB_DDRC_M0_BASE+0x6260)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MWR1                                     (APB_DDRC_M0_BASE+0x6264)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MWR2                                     (APB_DDRC_M0_BASE+0x6268)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MWR3                                     (APB_DDRC_M0_BASE+0x626C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MWR4                                     (APB_DDRC_M0_BASE+0x6270)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MWR5                                     (APB_DDRC_M0_BASE+0x6274)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MWR6                                     (APB_DDRC_M0_BASE+0x6278)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MWR7                                     (APB_DDRC_M0_BASE+0x627C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_WR0                                      (APB_DDRC_M0_BASE+0x6280)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_WR1                                      (APB_DDRC_M0_BASE+0x6284)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_WR2                                      (APB_DDRC_M0_BASE+0x6288)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_WR3                                      (APB_DDRC_M0_BASE+0x628C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_WR4                                      (APB_DDRC_M0_BASE+0x6290)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_WR5                                      (APB_DDRC_M0_BASE+0x6294)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_WR6                                      (APB_DDRC_M0_BASE+0x6298)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_WR7                                      (APB_DDRC_M0_BASE+0x629C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_ACT0                                     (APB_DDRC_M0_BASE+0x62A0)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_ACT1                                     (APB_DDRC_M0_BASE+0x62A4)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_ACT2                                     (APB_DDRC_M0_BASE+0x62A8)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_ACT3                                     (APB_DDRC_M0_BASE+0x62AC)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_ACT4                                     (APB_DDRC_M0_BASE+0x62B0)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_ACT5                                     (APB_DDRC_M0_BASE+0x62B4)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_ACT6                                     (APB_DDRC_M0_BASE+0x62B8)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_ACT7                                     (APB_DDRC_M0_BASE+0x62BC)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB0                                  (APB_DDRC_M0_BASE+0x6300)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB1                                  (APB_DDRC_M0_BASE+0x6304)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB2                                  (APB_DDRC_M0_BASE+0x6308)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB3                                  (APB_DDRC_M0_BASE+0x630C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB4                                  (APB_DDRC_M0_BASE+0x6310)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB5                                  (APB_DDRC_M0_BASE+0x6314)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB6                                  (APB_DDRC_M0_BASE+0x6318)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB7                                  (APB_DDRC_M0_BASE+0x631C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB0                                  (APB_DDRC_M0_BASE+0x6320)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB1                                  (APB_DDRC_M0_BASE+0x6324)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB2                                  (APB_DDRC_M0_BASE+0x6328)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB3                                  (APB_DDRC_M0_BASE+0x632C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB4                                  (APB_DDRC_M0_BASE+0x6330)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB5                                  (APB_DDRC_M0_BASE+0x6334)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB6                                  (APB_DDRC_M0_BASE+0x6338)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB7                                  (APB_DDRC_M0_BASE+0x633C)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_CG_REF_AB                                (APB_DDRC_M0_BASE+0x6340)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MF_REF_AB                                (APB_DDRC_M0_BASE+0x6344)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_CG_PRG_AB                                (APB_DDRC_M0_BASE+0x6350)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_MF_PRG_AB                                (APB_DDRC_M0_BASE+0x6354)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_CG_BL                                    (APB_DDRC_M0_BASE+0x6360)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_CG_AP                                    (APB_DDRC_M0_BASE+0x6364)
#define REG_DDRC_M0_DEBUG_CTRL_CMD_REF_CYCLE                                (APB_DDRC_M0_BASE+0x6368)
#define REG_DDRC_M0_DEBUG_DFI                                               (APB_DDRC_M0_BASE+0x6700)
#define REG_DDRC_M0_DRAM_BIST_CTRL_0                                        (APB_DDRC_M0_BASE+0x6800)
#define REG_DDRC_M0_DRAM_BIST_CTRL_1                                        (APB_DDRC_M0_BASE+0x6804)
#define REG_DDRC_M0_DRAM_BIST_CTRL_2                                        (APB_DDRC_M0_BASE+0x6808)
#define REG_DDRC_M0_DRAM_BIST_DATA_0                                        (APB_DDRC_M0_BASE+0x680C)
#define REG_DDRC_M0_DRAM_BIST_DATA_1                                        (APB_DDRC_M0_BASE+0x6810)
#define REG_DDRC_M0_DRAM_BIST_DATA_2                                        (APB_DDRC_M0_BASE+0x6814)
#define REG_DDRC_M0_DRAM_BIST_ADDR_0                                        (APB_DDRC_M0_BASE+0x6818)
#define REG_DDRC_M0_DRAM_BIST_ADDR_1                                        (APB_DDRC_M0_BASE+0x681C)
#define REG_DDRC_M0_DRAM_BIST_ADDR_2                                        (APB_DDRC_M0_BASE+0x6820)
#define REG_DDRC_M0_DRAM_BIST_OPCMD_0                                       (APB_DDRC_M0_BASE+0x6824)
#define REG_DDRC_M0_DRAM_BIST_OPCMD_1                                       (APB_DDRC_M0_BASE+0x6828)
#define REG_DDRC_M0_DRAM_BIST_OPCMD_2                                       (APB_DDRC_M0_BASE+0x682C)
#define REG_DDRC_M0_DRAM_BIST_OPCMD_3                                       (APB_DDRC_M0_BASE+0x6830)
#define REG_DDRC_M0_DRAM_BIST_ERR_ADDR_INFO                                 (APB_DDRC_M0_BASE+0x6834)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_00                              (APB_DDRC_M0_BASE+0x6838)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_01                              (APB_DDRC_M0_BASE+0x683C)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_02                              (APB_DDRC_M0_BASE+0x6840)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_03                              (APB_DDRC_M0_BASE+0x6844)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_04                              (APB_DDRC_M0_BASE+0x6848)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_05                              (APB_DDRC_M0_BASE+0x684C)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_06                              (APB_DDRC_M0_BASE+0x6850)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_07                              (APB_DDRC_M0_BASE+0x6854)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_08                              (APB_DDRC_M0_BASE+0x6858)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_09                              (APB_DDRC_M0_BASE+0x685C)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_10                              (APB_DDRC_M0_BASE+0x6860)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_11                              (APB_DDRC_M0_BASE+0x6864)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_12                              (APB_DDRC_M0_BASE+0x6868)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_13                              (APB_DDRC_M0_BASE+0x686C)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_14                              (APB_DDRC_M0_BASE+0x6870)
#define REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_15                              (APB_DDRC_M0_BASE+0x6874)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_00                              (APB_DDRC_M0_BASE+0x6878)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_01                              (APB_DDRC_M0_BASE+0x687C)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_02                              (APB_DDRC_M0_BASE+0x6880)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_03                              (APB_DDRC_M0_BASE+0x6884)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_04                              (APB_DDRC_M0_BASE+0x6888)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_05                              (APB_DDRC_M0_BASE+0x688C)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_06                              (APB_DDRC_M0_BASE+0x6890)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_07                              (APB_DDRC_M0_BASE+0x6894)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_08                              (APB_DDRC_M0_BASE+0x6898)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_09                              (APB_DDRC_M0_BASE+0x689C)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_10                              (APB_DDRC_M0_BASE+0x68A0)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_11                              (APB_DDRC_M0_BASE+0x68A4)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_12                              (APB_DDRC_M0_BASE+0x68A8)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_13                              (APB_DDRC_M0_BASE+0x68AC)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_14                              (APB_DDRC_M0_BASE+0x68B0)
#define REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_15                              (APB_DDRC_M0_BASE+0x68B4)
#define REG_DDRC_M0_REY_SPARE                                               (APB_DDRC_M0_BASE+0x6FE0)

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40000 RW
	UINT32 reg_dram_ch                      :1;	//0 //Dram channel width (0: x16, 1: x32)
	UINT32 resvd0                           :3;  
	UINT32 reg_byte_mode                    :1;	//4 //Byte mode enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M0_DRAM_CONF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40004 RW
	UINT32 reg_op_mode                      :1;	//0 //operation mode selection (0: normal, 1: debug)
	UINT32 reg_bist_en                      :1;	//1 //bist mode enable
	UINT32 resvd                            :30; 
	};
}REG_DDRC_M0_MODE_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40008 RW
	UINT32 reg_base_period                  :10;	//9:0	//base period for counter (counter resolution) - ex: 1us
	UINT32 resvd                            :22; 
	};
}REG_DDRC_M0_BASE_PERIOD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40100 RW
	UINT32 reg_alp_en                       :2;	//1:0	//low power mode enable 	 ([0]: power down, [1]: self refresh)
	UINT32 resvd0                           :2;  
	UINT32 reg_pd_thr                       :4;	//7:4	//power down threshold - waiting for 4*(x+1) cycles
	UINT32 reg_sr_thr                       :4;	//11:8	//self refresh threshold - waiting for tREFI*(x+1) cycles
	UINT32 resvd1                           :20; 
	};
}REG_DDRC_M0_ALP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40104 RW
	UINT32 reg_cgl_en                       :1;	//0 //clock gating enable
	UINT32 reg_rey_cgl_en                   :1;	//1 //rey clock gating enable
	UINT32 resvd0                           :2;  
	UINT32 reg_uq_cgl_en                    :1;	//4 //unified q clock gating enable
	UINT32 reg_sch_cgl_en                   :1;	//5 //scheduler clock gating enable
	UINT32 reg_ctrl_cgl_en                  :1;	//6 //ctrl clcok gating enable
	UINT32 reg_apb_reg_cgl_en               :1;	//7 //apb regsiter clock gating enable
	UINT32 reg_dbist_cgl_en                 :1;	//8 //dbist clock gating enable
	UINT32 reg_perfmon_cgl_en               :1;	//9 //perfmon clock gating enable
	UINT32 reg_latmon_cgl_en                :1;	//10 //latency monitor clock gating enable
	UINT32 reg_debug_cgl_en                 :1;	//11 //debug clock gating enable
	UINT32 resvd1                           :20; 
	};
}REG_DDRC_M0_CGL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40108 RO
	UINT32 reg_wuq_cgl_mon                  :1;	//0 //write unified q clock gating status
	UINT32 reg_ruq_cgl_mon                  :1;	//1 //read unified q clock gating status
	UINT32 reg_wsch_cgl_mon                 :1;	//2 //write port scheduler clock gating status
	UINT32 reg_rsch_cgl_mon                 :1;	//3 //read port scheduler clock gating status
	UINT32 reg_lpd4_cgl_mon                 :1;	//4 //lpd4 ctrl clcok gating status
	UINT32 resvd0                           :3;  
	UINT32 reg_apb_reg_cgl_mon              :1;	//8 //apb regsiter clock gating status
	UINT32 reg_dbist_cgl_mon                :1;	//9 //dbist clock gating status
	UINT32 reg_debug_cgl_mon                :1;	//10 //debug clock gating status
	UINT32 resvd1                           :1;  
	UINT32 reg_perfmon_cgl_mon              :1;	//12 //perfmon clock gating status
	UINT32 reg_latmon_cgl_mon               :1;	//13 //latency monitor clock gating status
	UINT32 reg_rey_cgl_mon                  :1;	//14 //rey clock gating status
	UINT32 resvd2                           :17; 
	};
}REG_DDRC_M0_CGL_MON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40200 RW
	UINT32 reg_pm_en                        :1;	//0 //performance monitor enable
	UINT32 resvd0                           :3;  
	UINT32 reg_emg_period                   :10;	//13:4	//emergency dfs monitoring period (ex: 100us) - (reg_base_period+1 (ex:1us)) * (reg_emg_period+1) : (final default value 0x63 --> 100ms)
	UINT32 resvd1                           :18; 
	};
}REG_DDRC_M0_PERFMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40204 RO
	UINT32 reg_emg_max                      :12;	//11:0	//max value among dfs_emg_totals during debug monitoring period : emg_total >> cut_width	(max of served bytes during emg period in debug monitoring period can be calculated by reg_emg_max * 16 << cut_width)	- cut_width : reg_emg_period[9]? 10 : 	                  reg_emg_period[8]?  9 :	                   reg_emg_period[7]?  8 :   	                   reg_emg_period[6]?  7 :	                   reg_emg_period[5]?  6 :	                   reg_emg_period[4]?  5 :   	                   reg_emg_period[3]?  4 :	                   reg_emg_period[2]?  3 :	                   reg_emg_period[1]?  2 :   	                      reg_emg_period[0]?  1 : 0
	UINT32 resvd                            :20; 
	};
}REG_DDRC_M0_PERFMON_EMG_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40210 RO
	UINT32 reg_pm_w0                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_W0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40214 RO
	UINT32 reg_pm_w1                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_W1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40218 RO
	UINT32 reg_pm_w2                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_W2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4021C RO
	UINT32 reg_pm_w3                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_W3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40220 RO
	UINT32 reg_pm_r0                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_R0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40224 RO
	UINT32 reg_pm_r1                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_R1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40228 RO
	UINT32 reg_pm_r2                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_R2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4022C RO
	UINT32 reg_pm_r3                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_R3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40230 
	UINT32 reg_max_lat_en                   :1;	//0 //max latency monitor enable
	UINT32 resvd0                           :7;  
	UINT32 reg_max_lat                      :8;	//15:8	//max latency for read request in unified Q (it is reset at every period)
	UINT32 resvd1                           :16; 
	};
}REG_DDRC_M0_LATMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40300 RW
	UINT32 reg_dfs_en                       :1;	//0 //normal dfs enable
	UINT32 reg_dfs_emg_en                   :1;	//1 //emergency dfs enable
	UINT32 reg_dfs_mask_en                  :1;	//2 //dfs mask enable by external blocking	- dfs is masked when asserting external blocking signal
	UINT32 reg_dfs_do                       :1;	//3 //user driven dfs start
	UINT32 resvd0                           :4;  
	UINT32 reg_dfs_block_period             :8;	//15:8	//dfs blocking period after completing dfs done : (reg_dfs_block_period+1)*0x100
	UINT32 reg_dfs_emg_thr                  :12;	//27:16	//emergency dfs threshold : it can be determined like as ((reg_base_period+1)*(reg_emg_period+1))*12.8G/(1s*16*2^cut_width))*80%)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_DFS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40304 RO
	UINT32 reg_dfs_done                     :1;	//0 //dfs done
	UINT32 resvd0                           :3;  
	UINT32 reg_dfs_type                     :2;	//5:4	//dfs type: DFS0, DFS1, DFS2 (emergency DFS exit)
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M0_DFS_RESULT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40400 RW
	UINT32 reg_dram_density                 :3;	//2:0	//dram density configuration per channel 	(enum {2Gb, 3Gb, 4Gb, 6Gb, 8Gb, 12Gb, 16Gb})
	UINT32 reg_addr_scrb_en                 :1;	//3 //address map: bank scramble enable
	UINT32 reg_addr_sel_bq                  :4;	//7:4	//address map: bank position	(enum {BG4, BG5, BG6, BG7, BP4, BP5, BP6, BP7, BP8, BP9, BP11, BP12})
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_ADDR_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40404 RW
	UINT32 reg_fast_en                      :1;	//0 //fast b valid enable
	UINT32 reg_ooo_en                       :1;	//1 //out of order enable
	UINT32 reg_lpd4_32bl_en                 :1;	//2 //lpddr4 long burst support
	UINT32 reg_exmon_en                     :1;	//3 //exclusive monitor enable
	UINT32 reg_errchk_en                    :1;	//4 //errore checker enable	 - 0: error checker disable	   - for out of range address, row address bits are truncated according to dram_density	     - 6Gb, 8Gb : row[16] = 1'b0	     - 3Gb, 4Gb : row[16:15] = 2'h0	     - 2Gb : row[16:14] = 3'h0	 - 1: error checker enable
	UINT32 reg_illegal_strb_mask_dis        :1;	//5 //illegal strb mask disable	      - '0 : mask illegal strb bits	      - '1 : disable illegal strb checker
	UINT32 resvd                            :26; 
	};
}REG_DDRC_M0_COMMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40408 
	UINT32 reg_rc4_enb                      :1;	//0 //data encryption enable
	UINT32 resvd0                           :7;  
	UINT32 reg_rc4_key_in_4                 :8;	//15:8	//key seed for data encryption (39:32 bits)
	UINT32 reg_rc4_state                    :2;	//17:16	//rc4 key generation status
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M0_DATA_ENC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4040C RW
	UINT32 reg_rc4_key_in_3_0               :32;	//31:0	//key seed for data encryption (31:0 bits)
	};
}REG_DDRC_M0_DATA_ENC1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40500 RW
	UINT32 reg_sameid_urg_en                :1;	//0 //urgent arbitration enable for predecssor wth same id	 - if it is enabled, whenever sameid request served at cbuf, prt_tag of previous request with same id is incremented
	UINT32 reg_sameid_urg_wt                :3;	//3:1	//weight value to increase prt_tag when same id urgent occurs
	UINT32 reg_prt_en                       :3;	//6:4	//per-request timeout enable ([0]: cbuf, [1]: pq, [2]: bq)
	UINT32 resvd0                           :1;  
	UINT32 reg_prt_bq_thr                   :4;	//11:8	//threshold value of per-request timeout for bank Q
	UINT32 reg_prt_pq_thr                   :4;	//15:12	//threshold value of per-request timeout for port Q
	UINT32 reg_ep_period                    :10;	//25:16	//a period of epoch counter for per-request timeout
	UINT32 resvd1                           :6;  
	};
}REG_DDRC_M0_RD_URG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F40504 RW
	UINT32 reg_urg_en                       :1;	//0 //urgent enable for port Q and bank Q in write port	 - if a request is blocking others due to RAW or WAW, it becomes urgent one.
	UINT32 resvd0                           :3;  
	UINT32 reg_wr_prt_en                    :1;	//4 //per-request timeout enable for port Q and bank Q in write port	 - if a request is timed-out, it becomes urgent one
	UINT32 resvd1                           :3;  
	UINT32 reg_wr_prt_thr                   :4;	//11:8	//threshold value of per-request timeout for write port
	UINT32 resvd2                           :4;  
	UINT32 reg_wr_ep_period                 :10;	//25:16	//a period of epoch counter for per-request timeout
	UINT32 resvd3                           :6;  
	};
}REG_DDRC_M0_WR_URG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41000 RW
	UINT32 reg_awready_en                   :4;	//3:0	//enable awready for each port
	UINT32 reg_pre_wready_en                :1;	//4 //enable pre-wready
	UINT32 resvd0                           :3;  
	UINT32 reg_arready_en                   :4;	//11:8	//enable arready for each port
	UINT32 resvd1                           :20; 
	};
}REG_DDRC_M0_FIFO_RDY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41004 RO
	UINT32 reg_aw_all_empty                 :4;	//3:0	//monitor whether all aw valid entries is empty for each port
	UINT32 reg_ar_all_empty                 :4;	//7:4	//monitor whether all aw valid entries is empty for each port
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_FIFO_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41008 RW
	UINT32 reg_aw_depth                     :3;	//2:0	//the number of valid entries is restricted for write request (x+1)
	UINT32 resvd0                           :1;  
	UINT32 reg_w_depth                      :2;	//5:4	//the number of valid entries is restricted for write data (x+1)
	UINT32 resvd1                           :10; 
	UINT32 reg_ar_depth                     :3;	//18:16	//the number of valid entries is restricted for read request (x+1)
	UINT32 resvd2                           :1;  
	UINT32 reg_resp_c_depth                 :2;	//21:20	//the number of valid entries is restricted for read request reesponse (x+1)
	UINT32 resvd3                           :2;  
	UINT32 reg_resp_d_depth                 :2;	//25:24	//the number of valid entries is restricted for read data response (x+1)
	UINT32 resvd4                           :6;  
	};
}REG_DDRC_M0_FIFO_CONF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41010 RW
	UINT32 reg_w_c_lim_en                   :4;	//3:0	//enable cmd cnt limiter
	UINT32 reg_w_d_lim_en                   :4;	//7:4	//enable data len limiter
	UINT32 reg_r_c_lim_en                   :4;	//11:8	//enable cmd cnt limiter
	UINT32 reg_r_d_lim_en                   :4;	//15:12	//enable data len limiter
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LIMITER_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41014 RW
	UINT32 reg_w_c_lim_thr0                 :5;	//4:0	//threshold value for cmd cnt limiter for write port 0
	UINT32 resvd0                           :3;  
	UINT32 reg_w_c_lim_thr1                 :5;	//12:8	//threshold value for cmd cnt limiter for write port 1
	UINT32 resvd1                           :3;  
	UINT32 reg_w_c_lim_thr2                 :5;	//20:16	//threshold value for cmd cnt limiter for write port 2
	UINT32 resvd2                           :3;  
	UINT32 reg_w_c_lim_thr3                 :5;	//28:24	//threshold value for cmd cnt limiter for write port 3
	UINT32 resvd3                           :3;  
	};
}REG_DDRC_M0_LIMITER_AW_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41018 RW
	UINT32 reg_w_d_lim_thr0                 :8;	//7:0	//threshold value for data len limiter for port 0
	UINT32 reg_w_d_lim_thr1                 :8;	//15:8	//threshold value for data len limiter for port 1
	UINT32 reg_w_d_lim_thr2                 :8;	//23:16	//threshold value for data len limiter for port 2
	UINT32 reg_w_d_lim_thr3                 :8;	//31:24	//threshold value for data len limiter for port 3
	};
}REG_DDRC_M0_LIMITER_W_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41024 RW
	UINT32 reg_r_c_lim_thr0                 :5;	//4:0	//threshold value for cmd cnt limiter for write port 0
	UINT32 resvd0                           :3;  
	UINT32 reg_r_c_lim_thr1                 :5;	//12:8	//threshold value for cmd cnt limiter for write port 1
	UINT32 resvd1                           :3;  
	UINT32 reg_r_c_lim_thr2                 :5;	//20:16	//threshold value for cmd cnt limiter for write port 2
	UINT32 resvd2                           :3;  
	UINT32 reg_r_c_lim_thr3                 :5;	//28:24	//threshold value for cmd cnt limiter for write port 3
	UINT32 resvd3                           :3;  
	};
}REG_DDRC_M0_LIMITER_AR_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41028 RW
	UINT32 reg_r_d_lim_thr0                 :8;	//7:0	//threshold value for data len limiter for port 0
	UINT32 reg_r_d_lim_thr1                 :8;	//15:8	//threshold value for data len limiter for port 1
	UINT32 reg_r_d_lim_thr2                 :8;	//23:16	//threshold value for data len limiter for port 2
	UINT32 reg_r_d_lim_thr3                 :8;	//31:24	//threshold value for data len limiter for port 3
	};
}REG_DDRC_M0_LIMITER_R_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41100 RW
	UINT32 reg_wfo_qos_en                   :1;	//0 //qos hit enable
	UINT32 reg_wfo_srt_en                   :1;	//1 //shortest burst length hit enable
	UINT32 resvd0                           :2;  
	UINT32 reg_wfo_qos_thr                  :4;	//7:4	//qos threshold
	UINT32 reg_rfo_qos_en                   :1;	//8 //qos hit enable for read
	UINT32 reg_rfo_srt_en                   :1;	//9 //shortest burst length hit enable for read
	UINT32 resvd1                           :2;  
	UINT32 reg_rfo_qos_thr                  :4;	//15:12	//qos threshold for read
	UINT32 reg_wfo_pend_en                  :1;	//16 //pend hit enable for write port: give a higher priority for port with lowest number of pending request
	UINT32 reg_rfo_pend_en                  :1;	//17 //pend hit enable for read port: give a higher priority for port with lowest number of pending request
	UINT32 resvd2                           :14; 
	};
}REG_DDRC_M0_FIFO_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41104 RW
	UINT32 reg_wfo_sol_max0                 :4;	//3:0	//The number of additionally continuous max serving requests for a write fifo 0
	UINT32 reg_wfo_sol_max1                 :4;	//7:4	//The number of additionally continuous max serving requests for a write fifo 1
	UINT32 reg_wfo_sol_max2                 :4;	//11:8	//The number of additionally continuous max serving requests for a write fifo 2
	UINT32 reg_wfo_sol_max3                 :4;	//15:12	//The number of additionally continuous max serving requests for a write fifo 3
	UINT32 reg_rfo_sol_max0                 :4;	//19:16	//The number of additionally continuous max serving requests for a read fifo 1
	UINT32 reg_rfo_sol_max1                 :4;	//23:20	//The number of additionally continuous max serving requests for a read fifo 1
	UINT32 reg_rfo_sol_max2                 :4;	//27:24	//The number of additionally continuous max serving requests for a read fifo 2
	UINT32 reg_rfo_sol_max3                 :4;	//31:28	//The number of additionally continuous max serving requests for a read fifo 3
	};
}REG_DDRC_M0_FIFO_MUX_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41108 RW
	UINT32 reg_wfo_prt_sol_max_en           :1;	//0 //write fifo prt sol max enable
	UINT32 resvd0                           :3;  
	UINT32 reg_wfo_prt_sol_max_thr          :4;	//7:4	//write fifo prt sol max threshold
	UINT32 reg_wfo_prt_ep_period            :10;	//17:8	//a period of epoch counter for wfifo prt
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M0_FIFO_MUX_WR_PRT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4110C RW
	UINT32 reg_rfo_prt_sol_max_en           :1;	//0 //read fifo prt sol max enable
	UINT32 resvd0                           :3;  
	UINT32 reg_rfo_prt_sol_max_thr          :4;	//7:4	//read fifo prt sol max threshold
	UINT32 reg_rfo_prt_ep_period            :10;	//17:8	//a period of epoch counter for rfifo prt
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M0_FIFO_MUX_RD_PRT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F41110 RW
	UINT32 reg_wfo_prt_sol_max0             :4;	//3:0	//The number of additionally continuous max serving requests for a write fifo 0 in the case prt occurred
	UINT32 reg_wfo_prt_sol_max1             :4;	//7:4	//The number of additionally continuous max serving requests for a write fifo 1 in the case prt occurred
	UINT32 reg_wfo_prt_sol_max2             :4;	//11:8	//The number of additionally continuous max serving requests for a write fifo 2 in the case prt occurred
	UINT32 reg_wfo_prt_sol_max3             :4;	//15:12	//The number of additionally continuous max serving requests for a write fifo 3 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max0             :4;	//19:16	//The number of additionally continuous max serving requests for a read fifo 1 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max1             :4;	//23:20	//The number of additionally continuous max serving requests for a read fifo 1 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max2             :4;	//27:24	//The number of additionally continuous max serving requests for a read fifo 2 in the case prt occurred
	UINT32 reg_rfo_prt_sol_max3             :4;	//31:28	//The number of additionally continuous max serving requests for a read fifo 3 in the case prt occurred
	};
}REG_DDRC_M0_FIFO_MUX_PRT_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F42000 RW
	UINT32 reg_pq_rd_urgonly_en             :1;	//0 //Enable per-request timeout hit without row hit
	UINT32 reg_pq_rd_urghit_en              :1;	//1 //Enable per-request timeout hit
	UINT32 reg_pq_wr_urgonly_en             :1;	//2 //Enable urgent hit without row hit
	UINT32 reg_pq_wr_urghit_en              :1;	//3 //Enable urgent hit
	UINT32 reg_pq_reqonly_en                :1;	//4 //Enable request hit without row hit
	UINT32 reg_pq_reqhit_en                 :1;	//5 //Enable request hit
	UINT32 resvd0                           :2;  
	UINT32 reg_pq_lucky_thr                 :5;	//12:8	//valid entry threshold for lucky hit (only valid up to #threshold)
	UINT32 resvd1                           :19; 
	};
}REG_DDRC_M0_PQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F42004 RW
	UINT32 reg_bq_rw_stv_en                 :1;	//0 //read/write starvation enable
	UINT32 reg_bq_rd_urghit_en              :1;	//1 //per-request timeout hit enable
	UINT32 reg_bq_wr_urghit_en              :1;	//2 //uregent hit enable
	UINT32 reg_bq_reqhit_en                 :1;	//3 //request hit enable
	UINT32 reg_bq_close_en                  :1;	//4 //close policy enable (close: 1, open: 0)
	UINT32 reg_bq_cond_close_en             :1;	//5 //conditional close policy enable
	UINT32 resvd0                           :2;  
	UINT32 reg_bq_cond_close_thr            :4;	//11:8	//conditional close threshold
	UINT32 resvd1                           :20; 
	};
}REG_DDRC_M0_BQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F42008 RW
	UINT32 reg_bq_rd_urg_stv_thr            :6;	//5:0	//ead starvation threshold when per request timeout hit is asserted  : 32*(x+1)
	UINT32 resvd0                           :2;  
	UINT32 reg_bq_wr_urg_stv_thr            :6;	//13:8	//write starvation threshold when urg hit is asserted : 32*(x+1)
	UINT32 resvd1                           :2;  
	UINT32 reg_bq_wr_stv_thr                :8;	//23:16	//write starvation threshold : 32*(x+1)
	UINT32 reg_bq_rd_stv_thr                :8;	//31:24	//read starvation threshold : 32*(x+1)
	};
}REG_DDRC_M0_BQ_RW_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4200C RW
	UINT32 reg_bq_hyb_stv_en                :1;	//0 //hybrid starvation enable
	UINT32 resvd0                           :3;  
	UINT32 reg_bq_hyb_stv_thr               :8;	//11:4	//hybrid starvation threshold : 32*(x+1)
	UINT32 resvd1                           :4;  
	UINT32 reg_bq_hyb_stv_cbuf_thr          :5;	//20:16	//cbuf threshold for hybrid starvation operation
	UINT32 resvd2                           :3;  
	UINT32 reg_bq_hyb_stv_dbuf_thr          :8;	//31:24	//dbuf threshold for hybrid starvation operation
	};
}REG_DDRC_M0_BQ_HYB_STV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43000 RW
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_dram_init_entry         :1;	//4 //DRAM initialization entry control	- 1'b0 : Stop DRAM initialization	- 1'b1 : Start DRAM initialization
	UINT32 lpd4_reg_dram_init_exit          :1;	//5 //DRAM initialization exit control	- 1'b0 : Hold DRAM initialization	- 1'b1 : Finish DRAM initialization
	UINT32 lpd4_reg_dram_auto_init          :1;	//6 //DRAM initialization mode selection	- 1'b0 : Manual initialization mode	- 1'b1 : Automatic initialization mode
	UINT32 lpd4_reg_dram_auto_resume        :1;	//7 //DRAM auto-resume initialization mode enable	- 1'b0 : Disable	- 1'b1 : Enable (only when the automatic initialization mode is enabled)
	UINT32 lpd4_reg_init_freq               :5;	//12:8	//DFS group selection of FSP0 for initialization	- 5'd0 : DFS0	- 5'd1 : DFS1	- 5'd2 : DFS2	- Else : N/A
	UINT32 resvd1                           :3;  
	UINT32 lpd4_reg_init_clk_change_en      :1;	//16 //Clock frequency change enable during initialization	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_init_pi_en              :1;	//17 //PHY independent training mode enable during initialization	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd2                           :2;  
	UINT32 lpd4_reg_init_dfs_freq           :5;	//24:20	//DFS group selection of FSP1 for initialization	- 5'd0 : DFS0	- 5'd1 : DFS1	- 5'd2 : DFS2	- Else : N/A
	UINT32 resvd3                           :3;  
	UINT32 lpd4_reg_init_mrr4_en            :1;	//28 //MRR (MR4) enable during initialization	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_init_ref_en             :1;	//29 //All-bank refresh enable during initialization	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd4                           :2;  
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_INIT_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43004 RW
	UINT32 lpd4_reg_init_mrw_ma_fsp0        :32;	//31:0	//Each of bit indicates the MR address for MRW operation for FSP0 during initialization.	[0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_INIT_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43008 RW
	UINT32 lpd4_reg_init_mrw_ma_fsp1        :32;	//31:0	//Each of bit indicates the MR address for MRW operation for FSP1 during initialization.	[0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_INIT_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4300C RW
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_ref_pi_en               :1;	//4 //All-bank refresh enable during PHY Independent training mode	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :3;  
	UINT32 lpd4_reg_active_pd_en            :1;	//8 //Active power-down enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd2                           :3;  
	UINT32 lpd4_reg_dir_pd_lp_en            :1;	//12 //PHY low-power enable during DRAM power-down mode via direct control interface	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_alp_pd_lp_en            :1;	//13 //PHY low-power enable during DRAM power-down mode via ALP	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_dir_sr_pd_lp_en         :1;	//14 //PHY low-power enable during DRAM self-refresh power-down mode via direct control interface	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_alp_sr_pd_lp_en         :1;	//15 //PHY low-power enable during DRAM self-refresh power-down mode via ALP	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_dfs_zqcal_en            :1;	//16 //DRAM ZQ calibration enable during self-refresh exit via DFS	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_alp_sr_pd_zqcal_en      :1;	//17 //DRAM ZQ calibration enable during self-refresh exit via ALP	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_period_zq_req_en        :1;	//18 //Periodic DRAM ZQ calibration enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd3                           :1;  
	UINT32 lpd4_reg_sr_abort_en             :1;	//20 //Self-refresh abort enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd4                           :3;  
	UINT32 lpd4_reg_main_lock_wait          :8;	//31:24	//Configurable locking time for MAIN FSM operation
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43010 
	UINT32 lpd4_reg_dir_ctrl_valid          :1;	//0 //Direct control request (This will be cleared when both lpd4_reg_dir_ctrl_valid and lpd4_mf_reg_dir_ctrl_done are asserted high)
	UINT32 lpd4_mf_reg_dir_ctrl_done        :1;	//1 //Completion of direct control request
	UINT32 reg_edge_dir_ctrl_done           :1;	//2 //Direct control done pulse
	UINT32 resvd                            :1;  
	UINT32 lpd4_reg_dir_ctrl_cmd            :20;	//23:4	//Direct control command	[19:18] : Location	[17:0] : One-hot command based on location
	UINT32 lpd4_reg_dir_mrw_ch              :2;	//25:24	//Channel selection for MRW via direct control interface	- [0] : CH0	- [1] : CH1
	UINT32 lpd4_reg_dir_mrr_ch              :2;	//27:26	//Channel selection for MRR via direct control interface	- [0] : CH0	- [1] : CH1
	UINT32 lpd4_reg_dir_sr_mrw_ch           :2;	//29:28	//Channel selection for MRW during self-refresh mode via direct control interface	- [0] : CH0	- [1] : CH1
	UINT32 lpd4_reg_dir_sr_mrr_ch           :2;	//31:30	//Channel selection for MRR during self-refresh mode via direct control interface	- [0] : CH0	- [1] : CH1
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43014 RW
	UINT32 lpd4_reg_dir_mrw_ma              :32;	//31:0	//Each of bit indicates the MR address for MRW operation for direct control interface	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43018 RW
	UINT32 lpd4_reg_dir_mrr_ma              :32;	//31:0	//Each of bit indicates the MR address for MRR operation for direct control interface	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4301C RW
	UINT32 lpd4_reg_dir_sr_mrw_ma           :32;	//31:0	//Each of bit indicates the MR address for MRW operation for direct control interface during self-refresh	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43020 RW
	UINT32 lpd4_reg_dir_sr_mrr_ma           :32;	//31:0	//Each of bit indicates the MR address for MRR operation for direct control interface during self-refresh	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43024 RW
	UINT32 lpd4_reg_dfs_mrw_ma              :32;	//31:0	//Each of bit indicates the MR address for MRW operation for DFS	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DFS_MRW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43028 
	UINT32 lpd4_reg_dfi_ctrlupd_req         :1;	//0 //DFI control update request (This will be cleared when lpd4_mf_reg_dfi_ctrlupd_ack is asserted high)
	UINT32 lpd4_mf_reg_dfi_ctrlupd_ack      :1;	//1 //Completion of DFI control update request
	UINT32 resvd                            :30; 
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_CTRLUPD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4302C RW
	UINT32 lpd4_reg_mpc_fifo_en             :1;	//0 //Periodic MPC WR/RD FIFO command enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_mpc_fifo_cmd_cnt        :3;	//6:4	//Number of MPC FIFO commands issued at one time
	UINT32 resvd1                           :25; 
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43030 RW
	UINT32 lpd4_reg_mpc_fifo_period         :32;	//31:0	//Period of MPC WR/RD FIFO command
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43034 RW
	UINT32 lpd4_reg_mpc_fifo_data0          :32;	//31:0	//Data pattern of MPC WR FIFO Command
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43038 RW
	UINT32 lpd4_reg_mpc_fifo_data1          :32;	//31:0	//Data pattern of MPC WR FIFO Command
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4303C RW
	UINT32 lpd4_reg_mpc_fifo_dmi0           :4;	//3:0	//DMI data pattern of MPC WR FIFO Command
	UINT32 lpd4_reg_mpc_fifo_dmi1           :4;	//7:4	//DMI data pattern of MPC WR FIFO Command
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43050 RW
	UINT32 lpd4_reg_mrr_mr4_tuf_sel         :2;	//1:0	//Temperature Update Flag (TUF) in MR4 selection between two-channel (x32)	- 2'b00 : CH0 or CH1	- 2'b01 : CH0 and CH1	- 2'b10 : CH0	- 2'b11 : CH1
	UINT32 resvd0                           :2;  
	UINT32 lpd4_reg_mrr_mr4_rate_sel        :2;	//5:4	//Refresh rate in MR4 selection between two-channel (x32)	- 2'b00 : Bigger value between CH0 and CH1	- 2'b01 : Smaller value between CH0 and CH1	- 2'b10 : CH0	- 2'b11 : CH1
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M0_LPD4_MR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43054 RW
	UINT32 lpd4_reg_mrr_mr4_tuf_byte_sel    :2;	//1:0	//Temperature Update Flag (TUF) in MR4 selection between two-byte (x16) in byte-mode	- 2'b00 : Byte0 or Byte1	- 2'b01 : Byte0 and Byte1	- 2'b10 : Byte0	- 2'b11 : Byte1
	UINT32 resvd0                           :2;  
	UINT32 lpd4_reg_mrr_mr4_rate_byte_sel   :2;	//5:4	//Refresh rate in MR4 selection between two-byte (x16) in byte-mode	- 2'b00 : Bigger value between Byte0 and Byte1	- 2'b01 : Smaller value between Byte0 and Byte1	- 2'b10 : Byte0	- 2'b11 : Byte1
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M0_LPD4_MR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43058 RW
	UINT32 lpd4_reg_mrr_byte_sel            :1;	//0 //MR selection between two-byte (x16) in byte-mode	- 1'b0 : Byte0	- 1'b1 : Byte1
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_LPD4_MR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43060 RW
	UINT32 lpd4_reg_ref_en                  :1;	//0 //Periodic refresh operation enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_ref_auto_en             :1;	//1 //Automatic mode enable for periodic refresh operation	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :2;  
	UINT32 lpd4_reg_ref_start               :1;	//4 //Manual mode enable for periodic refresh operation	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :3;  
	UINT32 lpd4_reg_ref_urg_thr             :4;	//11:8	//Threshold value of urgent refresh mode
	UINT32 lpd4_reg_ref_dist_en             :1;	//12 //Distributed all-bank refresh mode enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_ref_force_ab_en         :1;	//13 //Forced all-bank refresh mode enable when refresh rate is faster than lpd4_reg_ref_force_ab_thr value	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd2                           :2;  
	UINT32 lpd4_reg_mrr4_en                 :1;	//16 //Periodic MRR enable toward MR4	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_mrr4_auto_en            :1;	//17 //Automatic mode enable for periodic MRR operation toward MR4	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd3                           :2;  
	UINT32 lpd4_reg_mrr4_start              :1;	//20 //Manual mode enable for periodic MRR operation toward MR4	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd4                           :3;  
	UINT32 lpd4_reg_refi_derate_en          :1;	//24 //Derating enable for tREFI timing parameter according to refresh rate	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_urg_thr_derate_en       :1;	//25 //Derating enable for threshold value of urgent refresh mode according to refresh rate	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_ac_derate_en            :1;	//26 //Derating enable for AC timing parameters according to refresh rate	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd5                           :1;  
	UINT32 lpd4_reg_ref_force_ab_thr        :3;	//30:28	//Threshold value of forced all-bank refresh mode	- Refer to definition of refresh rate specified in JEDEC spec.
	UINT32 resvd6                           :1;  
	};
}REG_DDRC_M0_LPD4_REF_REQ_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43070 RW
	UINT32 lpd4_reg_ref_pullin_ab_en        :1;	//0 //Pull-in refresh mode enable during urgent refresh mode when using postponing all-bank refresh scheme	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pullin_thr          :4;	//7:4	//Threshold value of pull-in refresh mode	- Pull-in refresh mode is enabled until the number of postponing refresh is decreased to (lpd4_reg_ref_pullin_thr-2)
	UINT32 lpd4_reg_ref_urg_pb_en           :1;	//8 //Urgent per-bank refresh mode enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 lpd4_reg_ref_urg_ab_en           :1;	//9 //Urgent all-bank refresh mode enable when the number of postponed refresh is greater than or equal to lpd4_reg_ref_urg_ab_thr_register	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :2;  
	UINT32 lpd4_reg_ref_urg_ab_thr          :4;	//15:12	//Threshold value of urgent all-bank refresh scheme
	UINT32 lpd4_reg_ref_pb_cond             :1;	//16 //Per-bank refresh condition	- 1'b0 : bank close or bank queue idle	- 1'b1 : bank queue idle
	UINT32 lpd4_reg_urg_ref_pb_cond         :1;	//17 //Urgent Per-bank refresh condition	- 1'b0 : round robin	- 1'b1 : close bank first
	UINT32 resvd2                           :2;  
	UINT32 lpd4_reg_ref_rate_offset         :2;	//21:20	//Offset value of refresh rate
	UINT32 resvd3                           :10; 
	};
}REG_DDRC_M0_LPD4_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43080 RW
	UINT32 lpd4_reg_bank_lock_wait          :8;	//7:0	//Configurable locking time for BANK FSM operation
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_BANK_FSM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F430A0 RW
	UINT32 lpd4_reg_tBL                     :8;	//7:0	//Additional offset of AC timing parameters when applying BL32
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_BANK_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F430C0 RW
	UINT32 lpd4_reg_dfi_odtca               :2;	//1:0	//DFI ODTCA output value	- [0] : CH0	- [1] : CH1
	UINT32 resvd0                           :2;  
	UINT32 lpd4_reg_pd_clk_disable          :1;	//4 //DRAM clock disable when entering power-down mode	- 1'b0 : DRAM clock is enabled	- 1'b1 : DRAM clock is disabled
	UINT32 lpd4_reg_sr_pd_clk_disable       :1;	//5 //DRAM clock disable when entering self-refresh power-down mode	- 1'b0 : DRAM clock is enabled	- 1'b1 : DRAM clock is disabled
	UINT32 resvd1                           :2;  
	UINT32 lpd4_reg_lp_pd_wakeup            :4;	//11:8	//Wake-up time of PHY low-power mode when entering DRAM power-down mode
	UINT32 lpd4_reg_lp_sr_pd_wakeup         :4;	//15:12	//Wake-up time of PHY low-power mode when entering DRAM self-refresh power-down mode
	UINT32 lpd4_reg_mrr_data_sel            :2;	//17:16	//MRR data selection among burst 4 data	- 2'b00 : 1st read data	- 2'b01 : 2nd read data	- 2'b10 : 3rd read data	- 2'b11 : 4th read data
	UINT32 resvd2                           :14; 
	};
}REG_DDRC_M0_LPD4_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43100 RW
	UINT32 lpd4_reg_mr1_ch0_dfs0            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs0            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs0            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs0            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS0_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43104 RW
	UINT32 lpd4_reg_mr9_ch0_dfs0            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs0           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs0           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43108 RW
	UINT32 lpd4_reg_mr12_ch0_dfs0           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs0           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS0_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4310C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs0       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs0       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs0       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43110 RW
	UINT32 lpd4_reg_mr15_ch0_dfs0           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs0           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs0           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs0           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS0_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43114 RW
	UINT32 lpd4_reg_mr21_ch0_dfs0           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs0           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs0           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs0           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS0_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43118 RW
	UINT32 lpd4_reg_mr31_ch0_dfs0           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs0           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs0           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs0           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS0_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43120 RW
	UINT32 lpd4_reg_mr1_ch1_dfs0            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs0            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs0            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs0            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS0_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43124 RW
	UINT32 lpd4_reg_mr9_ch1_dfs0            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs0           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs0           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43128 RW
	UINT32 lpd4_reg_mr12_ch1_dfs0           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs0           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS0_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4312C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs0       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs0       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs0       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43130 RW
	UINT32 lpd4_reg_mr15_ch1_dfs0           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs0           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs0           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs0           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS0_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43134 RW
	UINT32 lpd4_reg_mr21_ch1_dfs0           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs0           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs0           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs0           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS0_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43138 RW
	UINT32 lpd4_reg_mr31_ch1_dfs0           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs0           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs0           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs0           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS0_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43140 RW
	UINT32 lpd4_reg_period_zq_req_dfs0      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43144 RW
	UINT32 lpd4_reg_tINIT1_dfs0             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs0             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43148 RW
	UINT32 lpd4_reg_tINIT5_dfs0             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs0             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs0             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4314C RW
	UINT32 lpd4_reg_tXP_dfs0                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs0             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs0            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs0            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43150 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs0           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43154 RW
	UINT32 lpd4_reg_tXSR_dfs0               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs0         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43160 RW
	UINT32 lpd4_reg_tREFI_dfs0              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs0           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43164 RW
	UINT32 lpd4_reg_tMRR4I_dfs0             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43168 RW
	UINT32 lpd4_reg_tRRD_dfs0               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs0           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs0           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs0               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4316C RW
	UINT32 lpd4_reg_tRAS_dfs0               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs0              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs0              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs0               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43170 RW
	UINT32 lpd4_reg_tRAP_dfs0               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs0        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs0    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs0    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43174 RW
	UINT32 lpd4_reg_tRCD_derate_dfs0        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs0        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs0       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs0       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43178 RW
	UINT32 lpd4_reg_tWAP_derate_dfs0        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs0        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43190 RW
	UINT32 lpd4_reg_ref_ab_en_dfs0          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs0          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M0_LPD4_DFS0_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431A0 RW
	UINT32 lpd4_reg_odt_on_dfs0             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431A4 RW
	UINT32 lpd4_reg_tCCD_dfs0               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs0             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs0               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs0               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431A8 RW
	UINT32 lpd4_reg_tW2PD_dfs0              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs0             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs0           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs0         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs0        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs0               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs0              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs0             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs0           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs0               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431B4 RW
	UINT32 lpd4_reg_tRFCab_dfs0             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs0             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431B8 RW
	UINT32 lpd4_reg_tMRW_dfs0               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs0           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs0       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs0      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431BC RW
	UINT32 lpd4_reg_tFC_dfs0                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs0           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs0               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs0              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs0            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs0             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs0             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs0           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F431E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs0             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs0            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs0             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43200 RW
	UINT32 lpd4_reg_mr1_ch0_dfs1            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs1            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs1            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs1            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS1_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43204 RW
	UINT32 lpd4_reg_mr9_ch0_dfs1            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs1           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs1           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43208 RW
	UINT32 lpd4_reg_mr12_ch0_dfs1           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs1           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS1_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4320C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs1       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs1       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs1       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43210 RW
	UINT32 lpd4_reg_mr15_ch0_dfs1           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs1           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs1           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs1           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS1_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43214 RW
	UINT32 lpd4_reg_mr21_ch0_dfs1           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs1           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs1           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs1           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS1_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43218 RW
	UINT32 lpd4_reg_mr31_ch0_dfs1           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs1           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs1           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs1           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS1_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43220 RW
	UINT32 lpd4_reg_mr1_ch1_dfs1            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs1            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs1            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs1            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS1_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43224 RW
	UINT32 lpd4_reg_mr9_ch1_dfs1            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs1           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs1           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43228 RW
	UINT32 lpd4_reg_mr12_ch1_dfs1           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs1           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS1_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4322C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs1       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs1       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs1       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43230 RW
	UINT32 lpd4_reg_mr15_ch1_dfs1           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs1           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs1           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs1           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS1_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43234 RW
	UINT32 lpd4_reg_mr21_ch1_dfs1           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs1           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs1           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs1           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS1_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43238 RW
	UINT32 lpd4_reg_mr31_ch1_dfs1           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs1           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs1           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs1           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS1_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43240 RW
	UINT32 lpd4_reg_period_zq_req_dfs1      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43244 RW
	UINT32 lpd4_reg_tINIT1_dfs1             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs1             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43248 RW
	UINT32 lpd4_reg_tINIT5_dfs1             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs1             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs1             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4324C RW
	UINT32 lpd4_reg_tXP_dfs1                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs1             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs1            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs1            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43250 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs1           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43254 RW
	UINT32 lpd4_reg_tXSR_dfs1               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs1         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43260 RW
	UINT32 lpd4_reg_tREFI_dfs1              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs1           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43264 RW
	UINT32 lpd4_reg_tMRR4I_dfs1             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43268 RW
	UINT32 lpd4_reg_tRRD_dfs1               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs1           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs1           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs1               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4326C RW
	UINT32 lpd4_reg_tRAS_dfs1               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs1              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs1              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs1               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43270 RW
	UINT32 lpd4_reg_tRAP_dfs1               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs1        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs1    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs1    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43274 RW
	UINT32 lpd4_reg_tRCD_derate_dfs1        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs1        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs1       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs1       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43278 RW
	UINT32 lpd4_reg_tWAP_derate_dfs1        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs1        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43290 RW
	UINT32 lpd4_reg_ref_ab_en_dfs1          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs1          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M0_LPD4_DFS1_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432A0 RW
	UINT32 lpd4_reg_odt_on_dfs1             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432A4 RW
	UINT32 lpd4_reg_tCCD_dfs1               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs1             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs1               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs1               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432A8 RW
	UINT32 lpd4_reg_tW2PD_dfs1              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs1             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs1           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs1         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs1        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs1               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs1              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs1             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs1           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs1               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432B4 RW
	UINT32 lpd4_reg_tRFCab_dfs1             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs1             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432B8 RW
	UINT32 lpd4_reg_tMRW_dfs1               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs1           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs1       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs1      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432BC RW
	UINT32 lpd4_reg_tFC_dfs1                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs1           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs1               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs1              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs1            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs1             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs1             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs1           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F432E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs1             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs1            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs1             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43300 RW
	UINT32 lpd4_reg_mr1_ch0_dfs2            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs2            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs2            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs2            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS2_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43304 RW
	UINT32 lpd4_reg_mr9_ch0_dfs2            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs2           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs2           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43308 RW
	UINT32 lpd4_reg_mr12_ch0_dfs2           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs2           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS2_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4330C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs2       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs2       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs2       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43310 RW
	UINT32 lpd4_reg_mr15_ch0_dfs2           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs2           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs2           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs2           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS2_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43314 RW
	UINT32 lpd4_reg_mr21_ch0_dfs2           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs2           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs2           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs2           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS2_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43318 RW
	UINT32 lpd4_reg_mr31_ch0_dfs2           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs2           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs2           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs2           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS2_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43320 RW
	UINT32 lpd4_reg_mr1_ch1_dfs2            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs2            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs2            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs2            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS2_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43324 RW
	UINT32 lpd4_reg_mr9_ch1_dfs2            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs2           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs2           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43328 RW
	UINT32 lpd4_reg_mr12_ch1_dfs2           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs2           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS2_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4332C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs2       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs2       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs2       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43330 RW
	UINT32 lpd4_reg_mr15_ch1_dfs2           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs2           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs2           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs2           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS2_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43334 RW
	UINT32 lpd4_reg_mr21_ch1_dfs2           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs2           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs2           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs2           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS2_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43338 RW
	UINT32 lpd4_reg_mr31_ch1_dfs2           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs2           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs2           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs2           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS2_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43340 RW
	UINT32 lpd4_reg_period_zq_req_dfs2      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43344 RW
	UINT32 lpd4_reg_tINIT1_dfs2             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs2             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43348 RW
	UINT32 lpd4_reg_tINIT5_dfs2             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs2             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs2             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4334C RW
	UINT32 lpd4_reg_tXP_dfs2                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs2             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs2            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs2            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43350 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs2           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43354 RW
	UINT32 lpd4_reg_tXSR_dfs2               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs2         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43360 RW
	UINT32 lpd4_reg_tREFI_dfs2              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs2           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43364 RW
	UINT32 lpd4_reg_tMRR4I_dfs2             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43368 RW
	UINT32 lpd4_reg_tRRD_dfs2               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs2           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs2           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs2               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4336C RW
	UINT32 lpd4_reg_tRAS_dfs2               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs2              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs2              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs2               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43370 RW
	UINT32 lpd4_reg_tRAP_dfs2               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs2        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs2    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs2    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43374 RW
	UINT32 lpd4_reg_tRCD_derate_dfs2        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs2        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs2       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs2       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43378 RW
	UINT32 lpd4_reg_tWAP_derate_dfs2        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs2        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F43390 RW
	UINT32 lpd4_reg_ref_ab_en_dfs2          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs2          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M0_LPD4_DFS2_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433A0 RW
	UINT32 lpd4_reg_odt_on_dfs2             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433A4 RW
	UINT32 lpd4_reg_tCCD_dfs2               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs2             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs2               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs2               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433A8 RW
	UINT32 lpd4_reg_tW2PD_dfs2              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs2             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs2           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs2         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs2        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs2               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs2              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs2             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs2           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs2               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433B4 RW
	UINT32 lpd4_reg_tRFCab_dfs2             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs2             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433B8 RW
	UINT32 lpd4_reg_tMRW_dfs2               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs2           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs2       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs2      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433BC RW
	UINT32 lpd4_reg_tFC_dfs2                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs2           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs2               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs2              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs2            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs2             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs2             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs2           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F433E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs2             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs2            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs2             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45000 RO
	UINT32 reg_dram_init_done               :1;	//0 //DRAM initialization done
	UINT32 reg_rey_idle                     :1;	//1 //Rey idle
	UINT32 resvd0                           :2;  
	UINT32 reg_init_set                     :1;	//4 //debug mode or before dram initialization
	UINT32 reg_set                          :1;	//5 //debug mode or rey idle
	UINT32 reg_alp_ready                    :1;	//6 //ALP READY state
	UINT32 resvd1                           :25; 
	};
}REG_DDRC_M0_DEBUG_COMMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45004 RW
	UINT32 reg_debug_mon_period             :20;	//19:0	//debug monitoring period (ex: 100ms) - (reg_base_period+1) * (reg_debug_mon_period+1)
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_PERIOD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45010 RW
	UINT32 reg_irq_en                       :1;	//0 //interrupt inable
	UINT32 resvd0                           :3;  
	UINT32 reg_irq_clr                      :1;	//4 //interrupt status registers clear
	UINT32 resvd1                           :3;  
	UINT32 reg_irq_dfs_mask                 :1;	//8 //dfs_done interrupt mask
	UINT32 resvd2                           :1;  
	UINT32 reg_irq_dir_ctrl_mask            :1;	//10 //direct controll done mask
	UINT32 reg_irq_ref_rate_mask            :1;	//11 //refresh rate change mask
	UINT32 reg_irq_apb_mask                 :1;	//12 //apb error interrupt mask
	UINT32 reg_irq_axi_mask                 :1;	//13 //axi error interrupt mask
	UINT32 resvd3                           :18; 
	};
}REG_DDRC_M0_IRQ_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45014 RO
	UINT32 resvd0                           :8;  
	UINT32 reg_irq_dfs_done                 :1;	//8 //dfs_done (user driven dfs or emegency dfs)
	UINT32 reg_irq_dfs_type                 :1;	//9 //user driven dfs (0) or emegency dfs (1)
	UINT32 reg_irq_dir_ctrl_done            :1;	//10 //direct control done
	UINT32 reg_irq_ref_rate                 :1;	//11 //refresh rate change due to dram temperature change
	UINT32 reg_irq_apb_err                  :1;	//12 //illegal register access
	UINT32 reg_irq_axi_err                  :1;	//13 //illegal axi request
	UINT32 resvd1                           :2;  
	UINT32 reg_irq_apb_addr                 :16;	//31:16	//apb address for illeagl access
	};
}REG_DDRC_M0_IRQ_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45100 RO
	UINT32 reg_debug_aw_valid               :4;	//3:0	//aw valid signal probe per each port
	UINT32 reg_debug_w_valid                :4;	//7:4	//w valid signal probe per each port
	UINT32 reg_debug_ar_valid               :4;	//11:8	//ar valid signal probe per each port
	UINT32 resvd                            :4;  
	UINT32 reg_debug_aw_ready               :4;	//19:16	//aw ready signal probe per each port
	UINT32 reg_debug_w_ready                :4;	//23:20	//w ready signal probe per each port
	UINT32 reg_debug_ar_ready               :4;	//27:24	//ar ready signal probe per each port
	UINT32 reg_debug_wf_valid               :1;	//28 //wfifo to wuq valid signal probe
	UINT32 reg_debug_wf_ready               :1;	//29 //wfifo to wuq ready signal probe
	UINT32 reg_debug_rf_valid               :1;	//30 //rfifo to ruq valid signal probe
	UINT32 reg_debug_rf_ready               :1;	//31 //rfifo to ruq ready signal probe
	};
}REG_DDRC_M0_DEBUG_BUS_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45200 RO
	UINT32 reg_aw_err_0                     :4;	//3:0	//AXI AW Request ERR flag in port0
	UINT32 reg_aw_err_1                     :4;	//7:4	//AXI AW Request ERR flag in port1
	UINT32 reg_aw_err_2                     :4;	//11:8	//AXI AW Request ERR flag in port2
	UINT32 reg_aw_err_3                     :4;	//15:12	//AXI AW Request ERR flag in port3
	UINT32 reg_ar_err_0                     :4;	//19:16	//AXI AR Request ERR flag in port0
	UINT32 reg_ar_err_1                     :4;	//23:20	//AXI AR Request ERR flag in port1
	UINT32 reg_ar_err_2                     :4;	//27:24	//AXI AR Request ERR flag in port2
	UINT32 reg_ar_err_3                     :4;	//31:28	//AXI AR Request ERR flag in port3
	};
}REG_DDRC_M0_DEBUG_PORT_IF_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45204 RW
	UINT32 reg_port_cmd_mon_en              :1;	//0 //AXI  Request capture en in wfo/rfo
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_DEBUG_PORT_IF_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45208 RO
	UINT32 reg_ar_err_id                    :18;	//17:0	//AXI AR Request ERR or Last Request's id
	UINT32 resvd                            :14; 
	};
}REG_DDRC_M0_DEBUG_PORT_IF_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4520C RO
	UINT32 reg_ar_err_addr                  :32;	//31:0	//AXI AR Request ERR or Last Request's addr
	};
}REG_DDRC_M0_DEBUG_PORT_IF_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45210 RO
	UINT32 reg_ar_err_len                   :8;	//7:0	//AXI AR Request ERR or Last Request's len
	UINT32 reg_ar_err_size                  :3;	//10:8	//AXI AR Request ERR or Last Request's size
	UINT32 resvd0                           :1;  
	UINT32 reg_ar_err_qos                   :4;	//15:12	//AXI AR Request ERR or Last Request's qos
	UINT32 reg_ar_err_burst                 :2;	//17:16	//AXI AR Request ERR or Last Request's burst
	UINT32 resvd1                           :2;  
	UINT32 reg_ar_err_lock                  :1;	//20 //AXI AR Request ERR or Last Request's lock
	UINT32 resvd2                           :7;  
	UINT32 reg_ar_err_port                  :2;	//29:28	//AXI AR Request ERR or Last Request's port
	UINT32 resvd3                           :2;  
	};
}REG_DDRC_M0_DEBUG_PORT_IF_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45214 RO
	UINT32 reg_aw_err_id                    :18;	//17:0	//AXI AW Request ERR or Last Request's id
	UINT32 resvd                            :14; 
	};
}REG_DDRC_M0_DEBUG_PORT_IF_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45218 RO
	UINT32 reg_aw_err_addr                  :32;	//31:0	//AXI AW Request ERR or Last Request's addr
	};
}REG_DDRC_M0_DEBUG_PORT_IF_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4521C RO
	UINT32 reg_aw_err_len                   :8;	//7:0	//AXI AW Request ERR or Last Request's len
	UINT32 reg_aw_err_size                  :3;	//10:8	//AXI AW Request ERR or Last Request's size
	UINT32 resvd0                           :1;  
	UINT32 reg_aw_err_qos                   :4;	//15:12	//AXI AW Request ERR or Last Request's qos
	UINT32 reg_aw_err_burst                 :2;	//17:16	//AXI AW Request ERR or Last Request's burst
	UINT32 resvd1                           :2;  
	UINT32 reg_aw_err_lock                  :1;	//20 //AXI AW Request ERR or Last Request's lock
	UINT32 resvd2                           :7;  
	UINT32 reg_aw_err_port                  :2;	//29:28	//AXI AW Request ERR or Last Request's port
	UINT32 resvd3                           :2;  
	};
}REG_DDRC_M0_DEBUG_PORT_IF_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45300 RO
	UINT32 reg_debug_wuq_valid              :1;	//0 //wuq to sch valid signal probe
	UINT32 reg_debug_wuq_ready              :1;	//1 //wuq to sch ready signal probe
	UINT32 reg_debug_ruq_valid              :1;	//2 //ruq to sch valid signal probe
	UINT32 reg_debug_ruq_ready              :1;	//3 //ruq to sch ready signal probe
	UINT32 resvd                            :28; 
	};
}REG_DDRC_M0_DEBUG_UQ_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45304 RO
	UINT32 reg_debug_wuq_c_cnt              :6;	//5:0	//wuq data queue pending cnt
	UINT32 resvd0                           :10; 
	UINT32 reg_debug_wuq_d_cnt              :9;	//24:16	//wuq command queue pending cnt
	UINT32 resvd1                           :7;  
	};
}REG_DDRC_M0_DEBUG_UQ_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45400 RO
	UINT32 reg_debug_prg_rdy                :8;	//7:0	//precharge ready signal probe per each bank
	UINT32 reg_debug_act_rdy                :8;	//15:8	//activate ready signal probe per each bank
	UINT32 reg_debug_wr_rdy                 :8;	//23:16	//write ready signal probe per each bank
	UINT32 reg_debug_mwr_rdy                :8;	//31:24	//masked write ready signal probe per each bank
	};
}REG_DDRC_M0_DEBUG_SCH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45404 RO
	UINT32 reg_debug_rd_rdy                 :8;	//7:0	//read ready signal probe per each bank
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_DEBUG_SCH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45500 RO
	UINT32 reg_debug_alp_state              :4;	//3:0	//alp status
	UINT32 reg_debug_entry_pd_req           :1;	//4 //power down entry request signal probe
	UINT32 reg_debug_entry_pd_ack           :1;	//5 //power down entry request ack signal probe
	UINT32 reg_debug_entry_sr_req           :1;	//6 //self refresh entry request signal probe
	UINT32 reg_debug_entry_sr_ack           :1;	//7 //self refresh entry request ack signal probe
	UINT32 reg_debug_exit_pd_req            :1;	//8 //power down exit request signal probe
	UINT32 reg_debug_exit_pd_ack            :1;	//9 //power down exit request ack signal probe
	UINT32 reg_debug_exit_sr_req            :1;	//10 //self refresh exit request signal probe
	UINT32 reg_debug_exit_sr_ack            :1;	//11 //self refresh exit request ack signal probe
	UINT32 reg_debug_wakeup                 :1;	//12 //alp wake up signal probe
	UINT32 resvd                            :19; 
	};
}REG_DDRC_M0_DEBUG_ALP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45504 RO
	UINT32 reg_debug_pd_cnt                 :16;	//15:0	//the number of power down entry during monitor period
	UINT32 reg_debug_sr_cnt                 :16;	//31:16	//the number of self refresh entry during monitor period
	};
}REG_DDRC_M0_DEBUG_ALP_ENTRY_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45508 RO
	UINT32 reg_debug_pd_time                :16;	//15:0	//total time of power down stay during monitor period
	UINT32 reg_debug_sr_time                :16;	//31:16	//total time of self refresh stay during monitor period: it is increased every reg_base_period (ex: 1us)
	};
}REG_DDRC_M0_DEBUG_ALP_TIME_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4550C RO
	UINT32 reg_debug_pd_std_cnt             :8;	//7:0	//max value of power down entry waiting counter during monitor period
	UINT32 reg_debug_sr_std_cnt             :8;	//15:8	//max value of self refresh entry waiting counter during monitor period: it is increased every reg_base_period (ex: 1us)
	UINT32 reg_debug_pd_ex_std_cnt          :8;	//23:16	//max value of power down exit waiting counter during monitor period
	UINT32 reg_debug_sr_ex_std_cnt          :8;	//31:24	//max value of self refresh exit waiting counter during monitor period: it is increased every reg_base_period (ex: 1us)
	};
}REG_DDRC_M0_DEBUG_ALP_WAIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45600 RO
	UINT32 reg_debug_dfs_state              :3;	//2:0	//dfs status
	UINT32 resvd                            :29; 
	};
}REG_DDRC_M0_DEBUG_DFS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45700 RO
	UINT32 reg_debug_nidle                  :32;	//31:0	//number of idle cycle
	};
}REG_DDRC_M0_DEBUG_IDLE_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45704 RO
	UINT32 reg_debug_nrd                    :32;	//31:0	//number of short read commands
	};
}REG_DDRC_M0_DEBUG_RD_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45708 RO
	UINT32 reg_debug_nrdl                   :32;	//31:0	//number of long read commands
	};
}REG_DDRC_M0_DEBUG_RDL_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45710 RO
	UINT32 reg_debug_nwr                    :32;	//31:0	//number of short write commands
	};
}REG_DDRC_M0_DEBUG_RWR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45714 RO
	UINT32 reg_debug_nmwr                   :32;	//31:0	//number of short masked write commands
	};
}REG_DDRC_M0_DEBUG_MWR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45718 RO
	UINT32 reg_debug_nwrl                   :32;	//31:0	//number of long write commands
	};
}REG_DDRC_M0_DEBUG_WRL_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45720 RO
	UINT32 reg_debug_nap                    :20;	//19:0	//number of AP commands
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_PRG_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45724 RO
	UINT32 reg_debug_nref                   :20;	//19:0	//number of all bank refresh commands
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_REF_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45728 RO
	UINT32 reg_debug_nact                   :32;	//31:0	//number of act commands
	};
}REG_DDRC_M0_DEBUG_ACT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4572C RO
	UINT32 reg_debug_nrw_swc                :32;	//31:0	//number of read/write command swich
	};
}REG_DDRC_M0_DEBUG_RW_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45730 RO
	UINT32 reg_debug_nr_urg_swc             :32;	//31:0	//number of urgent read command swich
	};
}REG_DDRC_M0_DEBUG_R_URG_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45734 RO
	UINT32 reg_debug_nr_req_row_hit         :32;	//31:0	//number of req_row hit in read port
	};
}REG_DDRC_M0_DEBUG_R_REQ_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45738 RO
	UINT32 reg_debug_nr_req_hit             :32;	//31:0	//number of req hit in read port
	};
}REG_DDRC_M0_DEBUG_R_REQ_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4573C RO
	UINT32 reg_debug_nr_urg_row_hit         :32;	//31:0	//number of urgent row hit in read port
	};
}REG_DDRC_M0_DEBUG_R_URG_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45740 RO
	UINT32 reg_debug_nr_urg_hit             :32;	//31:0	//number of urgent hit in read port
	};
}REG_DDRC_M0_DEBUG_R_URG_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45744 RO
	UINT32 reg_debug_nr_row_hit             :32;	//31:0	//number of row hit in read port
	};
}REG_DDRC_M0_DEBUG_R_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45748 RO
	UINT32 reg_debug_nr_lucky_hit           :32;	//31:0	//number of lucky in read port
	};
}REG_DDRC_M0_DEBUG_R_LUCKY_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45750 RO
	UINT32 reg_debug_nw_urg_swc             :32;	//31:0	//number of urgent write command swich
	};
}REG_DDRC_M0_DEBUG_W_URG_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45754 RO
	UINT32 reg_debug_nw_req_row_hit         :32;	//31:0	//number of req_row hit in write port
	};
}REG_DDRC_M0_DEBUG_W_REQ_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45758 RO
	UINT32 reg_debug_nw_req_hit             :32;	//31:0	//number of req hit in write port
	};
}REG_DDRC_M0_DEBUG_W_REQ_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4575C RO
	UINT32 reg_debug_nw_urg_row_hit         :32;	//31:0	//number of urgent row hit in write port
	};
}REG_DDRC_M0_DEBUG_W_URG_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45760 RO
	UINT32 reg_debug_nw_urg_hit             :32;	//31:0	//number of urgent hit in write port
	};
}REG_DDRC_M0_DEBUG_W_URG_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45764 RO
	UINT32 reg_debug_nw_row_hit             :32;	//31:0	//number of row hit in write port
	};
}REG_DDRC_M0_DEBUG_W_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45768 RO
	UINT32 reg_debug_nw_lucky_hit           :32;	//31:0	//number of lucky in write port
	};
}REG_DDRC_M0_DEBUG_W_LUCKY_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45770 RO
	UINT32 reg_debug_max_lat_3              :8;	//7:0	//max latency for qos 1~3
	UINT32 reg_debug_max_lat_5              :8;	//15:8	//max latency for qos 4~5
	UINT32 reg_debug_max_lat_7              :8;	//23:16	//max latency for qos 6~7
	UINT32 reg_debug_max_lat_8              :8;	//31:24	//max latency for qos 8~
	};
}REG_DDRC_M0_DEBUG_MAX_LAT_QOS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45800 RO
	UINT32 reg_debug_nr_hyb_swc             :32;	//31:0	//number of hybrid read command swich
	};
}REG_DDRC_M0_DEBUG_R_HYB_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45804 RO
	UINT32 reg_debug_nw_hyb_swc             :32;	//31:0	//number of hybrid write command swich
	};
}REG_DDRC_M0_DEBUG_W_HYB_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45900 RO
	UINT32 reg_debug_nr_fifo_0_prt          :32;	//31:0	//number of read fifo 0 prt
	};
}REG_DDRC_M0_DEBUG_R_FIFO_0_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45904 RO
	UINT32 reg_debug_nr_fifo_1_prt          :32;	//31:0	//number of read fifo 1 prt
	};
}REG_DDRC_M0_DEBUG_R_FIFO_1_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45908 RO
	UINT32 reg_debug_nr_fifo_2_prt          :32;	//31:0	//number of read fifo 2 prt
	};
}REG_DDRC_M0_DEBUG_R_FIFO_2_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4590C RO
	UINT32 reg_debug_nr_fifo_3_prt          :32;	//31:0	//number of read fifo 3 prt
	};
}REG_DDRC_M0_DEBUG_R_FIFO_3_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45910 RO
	UINT32 reg_debug_nw_fifo_0_prt          :32;	//31:0	//number of write fifo 0 prt
	};
}REG_DDRC_M0_DEBUG_W_FIFO_0_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45914 RO
	UINT32 reg_debug_nw_fifo_1_prt          :32;	//31:0	//number of write fifo 1 prt
	};
}REG_DDRC_M0_DEBUG_W_FIFO_1_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F45918 RO
	UINT32 reg_debug_nw_fifo_2_prt          :32;	//31:0	//number of write fifo 2 prt
	};
}REG_DDRC_M0_DEBUG_W_FIFO_2_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4591C RO
	UINT32 reg_debug_nw_fifo_3_prt          :32;	//31:0	//number of write fifo 3 prt
	};
}REG_DDRC_M0_DEBUG_W_FIFO_3_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46000 RO
	UINT32 lpd4_mf_reg_dram_init_done       :1;	//0 //DRAM initialization done
	UINT32 resvd0                           :3;  
	UINT32 lpd4_mr_reg_refresh_rate_ch0     :3;	//6:4	//Refresh rate read from DRAM (CH0)
	UINT32 lpd4_mr_reg_temp_upd_flag_ch0    :1;	//7 //Temperature update flag read from DRAM (CH0)
	UINT32 lpd4_mr_reg_refresh_rate_ch1     :3;	//10:8	//Refresh rate read from DRAM (CH1)
	UINT32 lpd4_mr_reg_temp_upd_flag_ch1    :1;	//11 //Temperature update flag read from DRAM (CH1)
	UINT32 lpd4_mr_reg_mrw0_fsp_wr          :1;	//12 //FSP-WR information (CH0)
	UINT32 lpd4_mr_reg_mrw1_fsp_wr          :1;	//13 //FSP-WR information (CH1)
	UINT32 lpd4_mr_reg_mrw0_fsp_op          :1;	//14 //FSP-OP information (CH0)
	UINT32 lpd4_mr_reg_mrw1_fsp_op          :1;	//15 //FSP-OP information (CH1)
	UINT32 lpd4_mr_reg_mrw0_vrcg            :1;	//16 //VRCG mode information (CH0)
	UINT32 lpd4_mr_reg_mrw1_vrcg            :1;	//17 //VRCG mode information (CH1)
	UINT32 lpd4_mr_reg_mrw0_dmd             :1;	//18 //DMD information (CH0)
	UINT32 lpd4_mr_reg_mrw1_dmd             :1;	//19 //DMD information (CH1)
	UINT32 lpd4_mr_reg_mrw0_dbi_wr          :1;	//20 //DBI-WR information (CH0)
	UINT32 lpd4_mr_reg_mrw1_dbi_wr          :1;	//21 //DBI-WR information (CH1)
	UINT32 lpd4_mr_reg_mrw0_dbi_rd          :1;	//22 //DBI-RD information (CH0)
	UINT32 lpd4_mr_reg_mrw1_dbi_rd          :1;	//23 //DBI-RD information (CH1)
	UINT32 lpd4_rr_reg_refi_req_cnt         :4;	//27:24	//# of postponed refresh number based on tREFI
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_DEBUG_LPD4_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46004 RO
	UINT32 lpd4_mf_reg_fsm_status_0         :32;	//31:0	//Main FSM information (1ST)
	};
}REG_DDRC_M0_DEBUG_LPD4_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46008 RO
	UINT32 lpd4_mf_reg_fsm_status_1         :32;	//31:0	//Main FSM information (2ND)
	};
}REG_DDRC_M0_DEBUG_LPD4_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4600C RO
	UINT32 lpd4_mf_reg_fsm_status_2         :1;	//0 //Main FSM information (3RD)
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_DEBUG_LPD4_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46010 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_0    :32;	//31:0	//Direct control done information (1ST)
	};
}REG_DDRC_M0_DEBUG_LPD4_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46014 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_1    :32;	//31:0	//Direct control done information (2ND)
	};
}REG_DDRC_M0_DEBUG_LPD4_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46018 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_2    :1;	//0 //Direct control done information (3RD)
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_DEBUG_LPD4_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4601C RO
	UINT32 lpd4_rr_reg_ref_req_ctrl_status  :32;	//31:0	//[31:16] : Derated tREFI	[15:12] : Derated threshold value of urgent refresh	[11:4] : Derated tRRD	[1] : Forced all-bank refresh mode	[0] : Distributed all-bank refresh mode
	};
}REG_DDRC_M0_DEBUG_LPD4_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46020 RO
	UINT32 lpd4_rc_reg_fsm_status           :11;	//10:0	//Refresh controller FSM information
	UINT32 resvd                            :5;  
	UINT32 lpd4_rc_reg_ref_pb_sel_flag      :8;	//23:16	//Bank selection information for per-bank refresh
	UINT32 lpd4_rc_reg_ref_pb_done_flag     :8;	//31:24	//Bank completion information for per-bank refresh
	};
}REG_DDRC_M0_DEBUG_LPD4_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46024 RO
	UINT32 lpd4_bf_reg_fsm_status_b0        :14;	//13:0	//Bank FSM information (bank0)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b1        :14;	//29:16	//Bank FSM information (bank1)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M0_DEBUG_LPD4_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46028 RO
	UINT32 lpd4_bf_reg_fsm_status_b2        :14;	//13:0	//Bank FSM information (bank2)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b3        :14;	//29:16	//Bank FSM information (bank3)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M0_DEBUG_LPD4_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4602C RO
	UINT32 lpd4_bf_reg_fsm_status_b4        :14;	//13:0	//Bank FSM information (bank4)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b5        :14;	//29:16	//Bank FSM information (bank5)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M0_DEBUG_LPD4_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46030 RO
	UINT32 lpd4_bf_reg_fsm_status_b6        :14;	//13:0	//Bank FSM information (bank6)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b7        :14;	//29:16	//Bank FSM information (bank7)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M0_DEBUG_LPD4_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46034 RO
	UINT32 lpd4_bs_reg_bank_open            :8;	//7:0	//Bank open information
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_DEBUG_LPD4_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46038 RO
	UINT32 lpd4_bs_reg_rdy_status_0         :32;	//31:0	//Bank ready information	[31:24] : Read	[23:16] : Masked write	[15:8] : Write	[7:0] : Activate
	};
}REG_DDRC_M0_DEBUG_LPD4_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4603C RO
	UINT32 lpd4_bs_reg_rdy_status_1         :32;	//31:0	//Bank ready information	[28] : MRR	[27] : MRW	[26] : Power-down	[25] : All-bank refresh	[23:16] : Per-bank refresh	[15:8] : Auto-precharge	[7:0] : Per-bank precharge
	};
}REG_DDRC_M0_DEBUG_LPD4_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46040 RO
	UINT32 lpd4_pi_reg_fifo_status          :32;	//31:0	//Pointer information	[22:20] : Read pipeline pointer	[18:16] : Write pipeline pointer	[15:12] : RFIFO output pointer	[11:8] : RFIFO input pointer	[7:4] : WFIFO output pointer	[3:0] : WFIFO input pointer
	};
}REG_DDRC_M0_DEBUG_LPD4_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46100 RO
	UINT32 lpd4_mr_reg_mr0_ch0              :8;	//7:0	//MR0 read information for CH0
	UINT32 lpd4_mr_reg_mr4_ch0              :8;	//15:8	//MR4 read information for CH0
	UINT32 lpd4_mr_reg_mr5_ch0              :8;	//23:16	//MR5 read information for CH0
	UINT32 lpd4_mr_reg_mr6_ch0              :8;	//31:24	//MR6 read information for CH0
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46104 RO
	UINT32 lpd4_mr_reg_mr7_ch0              :8;	//7:0	//MR7 read information for CH0
	UINT32 lpd4_mr_reg_mr8_ch0              :8;	//15:8	//MR8 read information for CH0
	UINT32 lpd4_mr_reg_mr12_ch0             :8;	//23:16	//MR12 read information for CH0
	UINT32 lpd4_mr_reg_mr14_ch0             :8;	//31:24	//MR14 read information for CH0
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46108 RO
	UINT32 lpd4_mr_reg_mr18_ch0             :8;	//7:0	//MR18 read information for CH0
	UINT32 lpd4_mr_reg_mr19_ch0             :8;	//15:8	//MR19 read information for CH0
	UINT32 lpd4_mr_reg_mr24_ch0             :8;	//23:16	//MR24 read information for CH0
	UINT32 lpd4_mr_reg_mr25_ch0             :8;	//31:24	//MR25 read information for CH0
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4610C RO
	UINT32 lpd4_mr_reg_mr0_ch1              :8;	//7:0	//MR0 read information for CH1
	UINT32 lpd4_mr_reg_mr4_ch1              :8;	//15:8	//MR4 read information for CH1
	UINT32 lpd4_mr_reg_mr5_ch1              :8;	//23:16	//MR5 read information for CH1
	UINT32 lpd4_mr_reg_mr6_ch1              :8;	//31:24	//MR6 read information for CH1
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46110 RO
	UINT32 lpd4_mr_reg_mr7_ch1              :8;	//7:0	//MR7 read information for CH1
	UINT32 lpd4_mr_reg_mr8_ch1              :8;	//15:8	//MR8 read information for CH1
	UINT32 lpd4_mr_reg_mr12_ch1             :8;	//23:16	//MR12 read information for CH1
	UINT32 lpd4_mr_reg_mr14_ch1             :8;	//31:24	//MR14 read information for CH1
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46114 RO
	UINT32 lpd4_mr_reg_mr18_ch1             :8;	//7:0	//MR18 read information for CH1
	UINT32 lpd4_mr_reg_mr19_ch1             :8;	//15:8	//MR19 read information for CH1
	UINT32 lpd4_mr_reg_mr24_ch1             :8;	//23:16	//MR24 read information for CH1
	UINT32 lpd4_mr_reg_mr25_ch1             :8;	//31:24	//MR25 read information for CH1
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46118 RO
	UINT32 lpd4_reg_mpc_fifo_fail_cnt       :32;	//31:0	//Periodic MPC FIFO fail count
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4611C RO
	UINT32 lpd4_reg_mpc_fifo_fail_data0     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46120 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data1     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46124 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data2     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46128 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data3     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4612C RO
	UINT32 lpd4_reg_mpc_fifo_fail_dmi0      :4;	//3:0	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi1      :4;	//7:4	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi2      :4;	//11:8	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi3      :4;	//15:12	//Periodic MPC FIFO fail dmi data
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46200 RO
	UINT32 reg_mf_mrw1_cnt                  :20;	//19:0	//number of channel 1 mrw command issued by main function
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MRW1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46204 RO
	UINT32 reg_mf_mrw0_cnt                  :20;	//19:0	//number of channel 0 mrw command issued by main function
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MRW0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46208 RO
	UINT32 reg_mf_lp_exit_cnt               :20;	//19:0	//number of lp exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_LP_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4620C RO
	UINT32 reg_mf_lp_entry_cnt              :20;	//19:0	//number of lp entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_LP_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46210 RO
	UINT32 reg_mf_sr_pd_exit_cnt            :20;	//19:0	//number of self-rerfresh power down exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_SR_PD_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46214 RO
	UINT32 reg_mf_sr_pd_entry_cnt           :20;	//19:0	//number of self-refresh power down entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_SR_PD_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46218 RO
	UINT32 reg_mf_sr_exit_cnt               :20;	//19:0	//number of self-refresh exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_SR_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4621C RO
	UINT32 reg_mf_sr_entry_cnt              :20;	//19:0	//number of self_refresh entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_SR_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46220 RO
	UINT32 reg_mf_pd_exit_cnt               :20;	//19:0	//number of power down exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PD_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46224 RO
	UINT32 reg_mf_pd_entry_cnt              :20;	//19:0	//number of power down entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PD_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46228 RO
	UINT32 reg_mf_zqlat_cnt                 :20;	//19:0	//number of zqcal latch command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ZQLAT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4622C RO
	UINT32 reg_mf_zqcal_cnt                 :20;	//19:0	//number of zqcal command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ZQCAL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46230 RO
	UINT32 reg_mf_cke_1_cnt                 :20;	//19:0	//number of cke rising command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CKE1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46234 RO
	UINT32 reg_mf_cke_0_cnt                 :20;	//19:0	//number of cke falling command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CKE0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46238 RO
	UINT32 reg_mf_rstn_1_cnt                :20;	//19:0	//number of reset rising command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RSTN1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4623C RO
	UINT32 reg_mf_rstn_0_cnt                :20;	//19:0	//number of reset falling command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RSTN0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46240 RO
	UINT32 reg_cg_rd0_cnt                   :32;	//31:0	//number of bank 0 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46244 RO
	UINT32 reg_cg_rd1_cnt                   :32;	//31:0	//number of bank 1 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46248 RO
	UINT32 reg_cg_rd2_cnt                   :32;	//31:0	//number of bank 2 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4624C RO
	UINT32 reg_cg_rd3_cnt                   :32;	//31:0	//number of bank 3 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46250 RO
	UINT32 reg_cg_rd4_cnt                   :32;	//31:0	//number of bank 4 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46254 RO
	UINT32 reg_cg_rd5_cnt                   :32;	//31:0	//number of bank 5 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46258 RO
	UINT32 reg_cg_rd6_cnt                   :32;	//31:0	//number of bank 6 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4625C RO
	UINT32 reg_cg_rd7_cnt                   :32;	//31:0	//number of bank 7 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46260 RO
	UINT32 reg_cg_mwr0_cnt                  :32;	//31:0	//number of bank 0 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46264 RO
	UINT32 reg_cg_mwr1_cnt                  :32;	//31:0	//number of bank 1 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46268 RO
	UINT32 reg_cg_mwr2_cnt                  :32;	//31:0	//number of bank 2 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4626C RO
	UINT32 reg_cg_mwr3_cnt                  :32;	//31:0	//number of bank 3 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46270 RO
	UINT32 reg_cg_mwr4_cnt                  :32;	//31:0	//number of bank 4 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46274 RO
	UINT32 reg_cg_mwr5_cnt                  :32;	//31:0	//number of bank 5 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46278 RO
	UINT32 reg_cg_mwr6_cnt                  :32;	//31:0	//number of bank 6 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4627C RO
	UINT32 reg_cg_mwr7_cnt                  :32;	//31:0	//number of bank 7 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46280 RO
	UINT32 reg_cg_wr0_cnt                   :32;	//31:0	//number of bank 0 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46284 RO
	UINT32 reg_cg_wr1_cnt                   :32;	//31:0	//number of bank 1 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46288 RO
	UINT32 reg_cg_wr2_cnt                   :32;	//31:0	//number of bank 2 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4628C RO
	UINT32 reg_cg_wr3_cnt                   :32;	//31:0	//number of bank 3 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46290 RO
	UINT32 reg_cg_wr4_cnt                   :32;	//31:0	//number of bank 4 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46294 RO
	UINT32 reg_cg_wr5_cnt                   :32;	//31:0	//number of bank 5 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46298 RO
	UINT32 reg_cg_wr6_cnt                   :32;	//31:0	//number of bank 6 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4629C RO
	UINT32 reg_cg_wr7_cnt                   :32;	//31:0	//number of bank 7 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F462A0 RO
	UINT32 reg_cg_act0_cnt                  :32;	//31:0	//number of bank 0 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F462A4 RO
	UINT32 reg_cg_act1_cnt                  :32;	//31:0	//number of bank 1 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F462A8 RO
	UINT32 reg_cg_act2_cnt                  :32;	//31:0	//number of bank 2 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F462AC RO
	UINT32 reg_cg_act3_cnt                  :32;	//31:0	//number of bank 3 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F462B0 RO
	UINT32 reg_cg_act4_cnt                  :32;	//31:0	//number of bank 4 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F462B4 RO
	UINT32 reg_cg_act5_cnt                  :32;	//31:0	//number of bank 5 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F462B8 RO
	UINT32 reg_cg_act6_cnt                  :32;	//31:0	//number of bank 6 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F462BC RO
	UINT32 reg_cg_act7_cnt                  :32;	//31:0	//number of bank 7 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46300 RO
	UINT32 reg_ref_pb0_cnt                  :22;	//21:0	//number of bank 0 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46304 RO
	UINT32 reg_ref_pb1_cnt                  :22;	//21:0	//number of bank 1 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46308 RO
	UINT32 reg_ref_pb2_cnt                  :22;	//21:0	//number of bank 2 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4630C RO
	UINT32 reg_ref_pb3_cnt                  :22;	//21:0	//number of bank 3 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46310 RO
	UINT32 reg_ref_pb4_cnt                  :22;	//21:0	//number of bank 4 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46314 RO
	UINT32 reg_ref_pb5_cnt                  :22;	//21:0	//number of bank 5 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46318 RO
	UINT32 reg_ref_pb6_cnt                  :22;	//21:0	//number of bank 6 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4631C RO
	UINT32 reg_ref_pb7_cnt                  :22;	//21:0	//number of bank 7 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46320 RO
	UINT32 reg_prg_pb0_cnt                  :22;	//21:0	//number of bank 0 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46324 RO
	UINT32 reg_prg_pb1_cnt                  :22;	//21:0	//number of bank 1 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46328 RO
	UINT32 reg_prg_pb2_cnt                  :22;	//21:0	//number of bank 2 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4632C RO
	UINT32 reg_prg_pb3_cnt                  :22;	//21:0	//number of bank 3 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46330 RO
	UINT32 reg_prg_pb4_cnt                  :22;	//21:0	//number of bank 4 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46334 RO
	UINT32 reg_prg_pb5_cnt                  :22;	//21:0	//number of bank 5 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46338 RO
	UINT32 reg_prg_pb6_cnt                  :22;	//21:0	//number of bank 6 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4633C RO
	UINT32 reg_prg_pb7_cnt                  :22;	//21:0	//number of bank 7 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46340 RO
	UINT32 reg_cg_ref_ab_cnt                :22;	//21:0	//number of all bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CG_REF_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46344 RO
	UINT32 reg_mf_ref_ab_cnt                :22;	//21:0	//number of all bank refresh command issued by main function
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MF_REF_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46350 RO
	UINT32 reg_cg_prg_ab_cnt                :22;	//21:0	//number of all bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CG_PRG_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46354 RO
	UINT32 reg_mf_prg_ab_cnt                :22;	//21:0	//number of all bank pre-charge command issued by main function
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MF_PRG_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46360 RO
	UINT32 reg_cg_bl_cnt                    :22;	//21:0	//number of long burst command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CG_BL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46364 RO
	UINT32 reg_cg_ap_cnt                    :22;	//21:0	//number of auto precharge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CG_AP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46368 RO
	UINT32 reg_ref_cycling_done_cnt         :20;	//19:0	//number of refresh cycling done command
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_CYCLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46700 RO
	UINT32 pi_reg_dfi_status                :32;	//31:0	//DFI information	[30] : dfi_lp_ack	[29:26] : dfi_lp_wakeup	[25] : dfi_lp_req	[24] : dfi_dram_clk_disable	[23:21] : pll_freq_type[2:0]	[20] : pll_lock_done	[19:18] : pll_freq_type[4:3]	[17] : dfi_ctrlupd_ack	[16] : dfi_ctrlupd_req	[14] : dfi_phyupd_ack	[13] : dfi_phyupd_type	[12] : dfi_phyupd_req	[10] : dfi_phymstr_ack	[9] : dfi_phymstr_type	[8] : dfi_phymstr_req	[6] : dfi_init_complete	[5:1] : dfi_frequency	[0] : dfi_init_start
	};
}REG_DDRC_M0_DEBUG_DFI_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46800 
	UINT32 reg_bist_start                   :1;	//0 //dram bist start, 0: stop, 1: start
	UINT32 resvd0                           :3;  
	UINT32 reg_bist_done                    :1;	//4 //dram bist done check, 0: running or idle, 1: done
	UINT32 resvd1                           :3;  
	UINT32 reg_bist_result                  :1;	//8 //dram bist result check , 0: PASS, 1: FAIL
	UINT32 resvd2                           :3;  
	UINT32 reg_bist_opcmd_ptr               :4;	//15:12	//dram bist opcmd pointer monitor
	UINT32 reg_bist_err_cnt                 :16;	//31:16	//dram bist err count monitor
	};
}REG_DDRC_M0_DRAM_BIST_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46804 
	UINT32 reg_bist_addr_map                :3;	//2:0	//set bist address map, (0~7: SPL, TGA, IIF, ITF, IIT, SFT, RND,ETC)
	UINT32 resvd0                           :1;  
	UINT32 reg_bist_err_skip                :1;	//4 //ignore bist fail, 0: BIST stop when err occurred. 1: BIST don't stop when err occurred.
	UINT32 resvd1                           :3;  
	UINT32 reg_rey_idle_skip                :1;	//8 //ignore rey idle state, 0: rey idle check, 1: ignore rey idle
	UINT32 resvd2                           :3;  
	UINT32 reg_bist_ap_en                   :1;	//12 //ap enable in LPD4, 0: ap disable, 1: enable(all rd/wr/mwr cmd are issued with ap )
	UINT32 reg_bist_cmd_delay_en            :1;	//13 //set 1cycle delay insert each DRAM CMD
	UINT32 resvd3                           :2;  
	UINT32 reg_bist_err_cnt_max             :16;	//31:16	//set bist err count max, Even if " FAIL " occurs, if the current number of errors is less than the maximum number of errors, it continues.
	};
}REG_DDRC_M0_DRAM_BIST_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46808 
	UINT32 reg_bist_cmdq_vld                :16;	//15:0	//bist cmdq valid state monitor
	UINT32 reg_bist_cmdq_req                :16;	//31:16	//bist cmdq request state monitor
	};
}REG_DDRC_M0_DRAM_BIST_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4680C 
	UINT32 reg_user_pat                     :32;	//31:0	//set bist user data pattern
	};
}REG_DDRC_M0_DRAM_BIST_DATA_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46810 
	UINT32 reg_mask_pat_0                   :16;	//15:0	//data mask for 1st 16byte data
	UINT32 reg_mask_pat_1                   :16;	//31:16	//data mask for 2nd 16byte data
	};
}REG_DDRC_M0_DRAM_BIST_DATA_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46814 
	UINT32 reg_mask_pat_2                   :16;	//15:0	//data mask for 3rd 16byte data
	UINT32 reg_mask_pat_3                   :16;	//31:16	//data mask for 4th 16byte data
	};
}REG_DDRC_M0_DRAM_BIST_DATA_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46818 
	UINT32 reg_bist_addr_cnt_max            :32;	//31:0	//Set how many times to repeat when reg_bist_addr_map is not "SPL".
	};
}REG_DDRC_M0_DRAM_BIST_ADDR_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4681C 
	UINT32 reg_s_addr                       :32;	//31:0	//set bist start address, SPL mode (use full bit), not SPL mode ([31:15] row, [14:12] ba, [11:5] col)
	};
}REG_DDRC_M0_DRAM_BIST_ADDR_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46820 
	UINT32 reg_e_addr                       :32;	//31:0	//set bist start address, SPL mode (use full bit), not SPL mode ([31:15] row, [14:12] ba, [11:5] col), default 2Gbyte setting
	};
}REG_DDRC_M0_DRAM_BIST_ADDR_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46824 
	UINT32 reg_bist_opcmd_00                :8;	//7:0	//
	UINT32 reg_bist_opcmd_01                :8;	//15:8	//
	UINT32 reg_bist_opcmd_02                :8;	//23:16	//
	UINT32 reg_bist_opcmd_03                :8;	//31:24	//set bist operation cmd  , default MARCH C-,
	};
}REG_DDRC_M0_DRAM_BIST_OPCMD_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46828 
	UINT32 reg_bist_opcmd_04                :8;	//7:0	//
	UINT32 reg_bist_opcmd_05                :8;	//15:8	//
	UINT32 reg_bist_opcmd_06                :8;	//23:16	//
	UINT32 reg_bist_opcmd_07                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M0_DRAM_BIST_OPCMD_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4682C 
	UINT32 reg_bist_opcmd_08                :8;	//7:0	//
	UINT32 reg_bist_opcmd_09                :8;	//15:8	//
	UINT32 reg_bist_opcmd_10                :8;	//23:16	//
	UINT32 reg_bist_opcmd_11                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M0_DRAM_BIST_OPCMD_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46830 
	UINT32 reg_bist_opcmd_12                :8;	//7:0	//
	UINT32 reg_bist_opcmd_13                :8;	//15:8	//
	UINT32 reg_bist_opcmd_14                :8;	//23:16	//
	UINT32 reg_bist_opcmd_15                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M0_DRAM_BIST_OPCMD_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46834 RO
	UINT32 reg_err_addr                     :32;	//31:0	//address where error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_ADDR_INFO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46838 RO
	UINT32 reg_err_data_00                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4683C RO
	UINT32 reg_err_data_01                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46840 RO
	UINT32 reg_err_data_02                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46844 RO
	UINT32 reg_err_data_03                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46848 RO
	UINT32 reg_err_data_04                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4684C RO
	UINT32 reg_err_data_05                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46850 RO
	UINT32 reg_err_data_06                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46854 RO
	UINT32 reg_err_data_07                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46858 RO
	UINT32 reg_err_data_08                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4685C RO
	UINT32 reg_err_data_09                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46860 RO
	UINT32 reg_err_data_10                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46864 RO
	UINT32 reg_err_data_11                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46868 RO
	UINT32 reg_err_data_12                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4686C RO
	UINT32 reg_err_data_13                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46870 RO
	UINT32 reg_err_data_14                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46874 RO
	UINT32 reg_err_data_15                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46878 RO
	UINT32 reg_exp_data_00                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4687C RO
	UINT32 reg_exp_data_01                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46880 RO
	UINT32 reg_exp_data_02                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46884 RO
	UINT32 reg_exp_data_03                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46888 RO
	UINT32 reg_exp_data_04                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4688C RO
	UINT32 reg_exp_data_05                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46890 RO
	UINT32 reg_exp_data_06                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46894 RO
	UINT32 reg_exp_data_07                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46898 RO
	UINT32 reg_exp_data_08                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F4689C RO
	UINT32 reg_exp_data_09                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F468A0 RO
	UINT32 reg_exp_data_10                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F468A4 RO
	UINT32 reg_exp_data_11                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F468A8 RO
	UINT32 reg_exp_data_12                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F468AC RO
	UINT32 reg_exp_data_13                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F468B0 RO
	UINT32 reg_exp_data_14                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F468B4 RO
	UINT32 reg_exp_data_15                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4F46FE0 RW
	UINT32 reg_rey_spare                    :32;	//31:0	//spare register for ECO (should not be removed)
	};
}REG_DDRC_M0_REY_SPARE_T;

typedef struct {
	REG_DDRC_M0_DRAM_CONF_T                                   dram_conf;	//0xC4F40000
	REG_DDRC_M0_MODE_SEL_T                                     mode_sel;	//0xC4F40004
	REG_DDRC_M0_BASE_PERIOD_T                               base_period;	//0xC4F40008
	UINT32                                                    reserved0;	//0xC4F4000C
	UINT32                                                    reserved1;	//0xC4F40010
	UINT32                                                    reserved2;	//0xC4F40014
	UINT32                                                    reserved3;	//0xC4F40018
	UINT32                                                    reserved4;	//0xC4F4001C
	UINT32                                                    reserved5;	//0xC4F40020
	UINT32                                                    reserved6;	//0xC4F40024
	UINT32                                                    reserved7;	//0xC4F40028
	UINT32                                                    reserved8;	//0xC4F4002C
	UINT32                                                    reserved9;	//0xC4F40030
	UINT32                                                   reserved10;	//0xC4F40034
	UINT32                                                   reserved11;	//0xC4F40038
	UINT32                                                   reserved12;	//0xC4F4003C
	UINT32                                                   reserved13;	//0xC4F40040
	UINT32                                                   reserved14;	//0xC4F40044
	UINT32                                                   reserved15;	//0xC4F40048
	UINT32                                                   reserved16;	//0xC4F4004C
	UINT32                                                   reserved17;	//0xC4F40050
	UINT32                                                   reserved18;	//0xC4F40054
	UINT32                                                   reserved19;	//0xC4F40058
	UINT32                                                   reserved20;	//0xC4F4005C
	UINT32                                                   reserved21;	//0xC4F40060
	UINT32                                                   reserved22;	//0xC4F40064
	UINT32                                                   reserved23;	//0xC4F40068
	UINT32                                                   reserved24;	//0xC4F4006C
	UINT32                                                   reserved25;	//0xC4F40070
	UINT32                                                   reserved26;	//0xC4F40074
	UINT32                                                   reserved27;	//0xC4F40078
	UINT32                                                   reserved28;	//0xC4F4007C
	UINT32                                                   reserved29;	//0xC4F40080
	UINT32                                                   reserved30;	//0xC4F40084
	UINT32                                                   reserved31;	//0xC4F40088
	UINT32                                                   reserved32;	//0xC4F4008C
	UINT32                                                   reserved33;	//0xC4F40090
	UINT32                                                   reserved34;	//0xC4F40094
	UINT32                                                   reserved35;	//0xC4F40098
	UINT32                                                   reserved36;	//0xC4F4009C
	UINT32                                                   reserved37;	//0xC4F400A0
	UINT32                                                   reserved38;	//0xC4F400A4
	UINT32                                                   reserved39;	//0xC4F400A8
	UINT32                                                   reserved40;	//0xC4F400AC
	UINT32                                                   reserved41;	//0xC4F400B0
	UINT32                                                   reserved42;	//0xC4F400B4
	UINT32                                                   reserved43;	//0xC4F400B8
	UINT32                                                   reserved44;	//0xC4F400BC
	UINT32                                                   reserved45;	//0xC4F400C0
	UINT32                                                   reserved46;	//0xC4F400C4
	UINT32                                                   reserved47;	//0xC4F400C8
	UINT32                                                   reserved48;	//0xC4F400CC
	UINT32                                                   reserved49;	//0xC4F400D0
	UINT32                                                   reserved50;	//0xC4F400D4
	UINT32                                                   reserved51;	//0xC4F400D8
	UINT32                                                   reserved52;	//0xC4F400DC
	UINT32                                                   reserved53;	//0xC4F400E0
	UINT32                                                   reserved54;	//0xC4F400E4
	UINT32                                                   reserved55;	//0xC4F400E8
	UINT32                                                   reserved56;	//0xC4F400EC
	UINT32                                                   reserved57;	//0xC4F400F0
	UINT32                                                   reserved58;	//0xC4F400F4
	UINT32                                                   reserved59;	//0xC4F400F8
	UINT32                                                   reserved60;	//0xC4F400FC
	REG_DDRC_M0_ALP_T                                               alp;	//0xC4F40100
	REG_DDRC_M0_CGL_T                                               cgl;	//0xC4F40104
	REG_DDRC_M0_CGL_MON_T                                       cgl_mon;	//0xC4F40108
	UINT32                                                   reserved61;	//0xC4F4010C
	UINT32                                                   reserved62;	//0xC4F40110
	UINT32                                                   reserved63;	//0xC4F40114
	UINT32                                                   reserved64;	//0xC4F40118
	UINT32                                                   reserved65;	//0xC4F4011C
	UINT32                                                   reserved66;	//0xC4F40120
	UINT32                                                   reserved67;	//0xC4F40124
	UINT32                                                   reserved68;	//0xC4F40128
	UINT32                                                   reserved69;	//0xC4F4012C
	UINT32                                                   reserved70;	//0xC4F40130
	UINT32                                                   reserved71;	//0xC4F40134
	UINT32                                                   reserved72;	//0xC4F40138
	UINT32                                                   reserved73;	//0xC4F4013C
	UINT32                                                   reserved74;	//0xC4F40140
	UINT32                                                   reserved75;	//0xC4F40144
	UINT32                                                   reserved76;	//0xC4F40148
	UINT32                                                   reserved77;	//0xC4F4014C
	UINT32                                                   reserved78;	//0xC4F40150
	UINT32                                                   reserved79;	//0xC4F40154
	UINT32                                                   reserved80;	//0xC4F40158
	UINT32                                                   reserved81;	//0xC4F4015C
	UINT32                                                   reserved82;	//0xC4F40160
	UINT32                                                   reserved83;	//0xC4F40164
	UINT32                                                   reserved84;	//0xC4F40168
	UINT32                                                   reserved85;	//0xC4F4016C
	UINT32                                                   reserved86;	//0xC4F40170
	UINT32                                                   reserved87;	//0xC4F40174
	UINT32                                                   reserved88;	//0xC4F40178
	UINT32                                                   reserved89;	//0xC4F4017C
	UINT32                                                   reserved90;	//0xC4F40180
	UINT32                                                   reserved91;	//0xC4F40184
	UINT32                                                   reserved92;	//0xC4F40188
	UINT32                                                   reserved93;	//0xC4F4018C
	UINT32                                                   reserved94;	//0xC4F40190
	UINT32                                                   reserved95;	//0xC4F40194
	UINT32                                                   reserved96;	//0xC4F40198
	UINT32                                                   reserved97;	//0xC4F4019C
	UINT32                                                   reserved98;	//0xC4F401A0
	UINT32                                                   reserved99;	//0xC4F401A4
	UINT32                                                  reserved100;	//0xC4F401A8
	UINT32                                                  reserved101;	//0xC4F401AC
	UINT32                                                  reserved102;	//0xC4F401B0
	UINT32                                                  reserved103;	//0xC4F401B4
	UINT32                                                  reserved104;	//0xC4F401B8
	UINT32                                                  reserved105;	//0xC4F401BC
	UINT32                                                  reserved106;	//0xC4F401C0
	UINT32                                                  reserved107;	//0xC4F401C4
	UINT32                                                  reserved108;	//0xC4F401C8
	UINT32                                                  reserved109;	//0xC4F401CC
	UINT32                                                  reserved110;	//0xC4F401D0
	UINT32                                                  reserved111;	//0xC4F401D4
	UINT32                                                  reserved112;	//0xC4F401D8
	UINT32                                                  reserved113;	//0xC4F401DC
	UINT32                                                  reserved114;	//0xC4F401E0
	UINT32                                                  reserved115;	//0xC4F401E4
	UINT32                                                  reserved116;	//0xC4F401E8
	UINT32                                                  reserved117;	//0xC4F401EC
	UINT32                                                  reserved118;	//0xC4F401F0
	UINT32                                                  reserved119;	//0xC4F401F4
	UINT32                                                  reserved120;	//0xC4F401F8
	UINT32                                                  reserved121;	//0xC4F401FC
	REG_DDRC_M0_PERFMON_T                                       perfmon;	//0xC4F40200
	REG_DDRC_M0_PERFMON_EMG_MAX_T                       perfmon_emg_max;	//0xC4F40204
	UINT32                                                  reserved122;	//0xC4F40208
	UINT32                                                  reserved123;	//0xC4F4020C
	REG_DDRC_M0_PERFMON_W0_T                                 perfmon_w0;	//0xC4F40210
	REG_DDRC_M0_PERFMON_W1_T                                 perfmon_w1;	//0xC4F40214
	REG_DDRC_M0_PERFMON_W2_T                                 perfmon_w2;	//0xC4F40218
	REG_DDRC_M0_PERFMON_W3_T                                 perfmon_w3;	//0xC4F4021C
	REG_DDRC_M0_PERFMON_R0_T                                 perfmon_r0;	//0xC4F40220
	REG_DDRC_M0_PERFMON_R1_T                                 perfmon_r1;	//0xC4F40224
	REG_DDRC_M0_PERFMON_R2_T                                 perfmon_r2;	//0xC4F40228
	REG_DDRC_M0_PERFMON_R3_T                                 perfmon_r3;	//0xC4F4022C
	REG_DDRC_M0_LATMON_T                                         latmon;	//0xC4F40230
	UINT32                                                  reserved124;	//0xC4F40234
	UINT32                                                  reserved125;	//0xC4F40238
	UINT32                                                  reserved126;	//0xC4F4023C
	UINT32                                                  reserved127;	//0xC4F40240
	UINT32                                                  reserved128;	//0xC4F40244
	UINT32                                                  reserved129;	//0xC4F40248
	UINT32                                                  reserved130;	//0xC4F4024C
	UINT32                                                  reserved131;	//0xC4F40250
	UINT32                                                  reserved132;	//0xC4F40254
	UINT32                                                  reserved133;	//0xC4F40258
	UINT32                                                  reserved134;	//0xC4F4025C
	UINT32                                                  reserved135;	//0xC4F40260
	UINT32                                                  reserved136;	//0xC4F40264
	UINT32                                                  reserved137;	//0xC4F40268
	UINT32                                                  reserved138;	//0xC4F4026C
	UINT32                                                  reserved139;	//0xC4F40270
	UINT32                                                  reserved140;	//0xC4F40274
	UINT32                                                  reserved141;	//0xC4F40278
	UINT32                                                  reserved142;	//0xC4F4027C
	UINT32                                                  reserved143;	//0xC4F40280
	UINT32                                                  reserved144;	//0xC4F40284
	UINT32                                                  reserved145;	//0xC4F40288
	UINT32                                                  reserved146;	//0xC4F4028C
	UINT32                                                  reserved147;	//0xC4F40290
	UINT32                                                  reserved148;	//0xC4F40294
	UINT32                                                  reserved149;	//0xC4F40298
	UINT32                                                  reserved150;	//0xC4F4029C
	UINT32                                                  reserved151;	//0xC4F402A0
	UINT32                                                  reserved152;	//0xC4F402A4
	UINT32                                                  reserved153;	//0xC4F402A8
	UINT32                                                  reserved154;	//0xC4F402AC
	UINT32                                                  reserved155;	//0xC4F402B0
	UINT32                                                  reserved156;	//0xC4F402B4
	UINT32                                                  reserved157;	//0xC4F402B8
	UINT32                                                  reserved158;	//0xC4F402BC
	UINT32                                                  reserved159;	//0xC4F402C0
	UINT32                                                  reserved160;	//0xC4F402C4
	UINT32                                                  reserved161;	//0xC4F402C8
	UINT32                                                  reserved162;	//0xC4F402CC
	UINT32                                                  reserved163;	//0xC4F402D0
	UINT32                                                  reserved164;	//0xC4F402D4
	UINT32                                                  reserved165;	//0xC4F402D8
	UINT32                                                  reserved166;	//0xC4F402DC
	UINT32                                                  reserved167;	//0xC4F402E0
	UINT32                                                  reserved168;	//0xC4F402E4
	UINT32                                                  reserved169;	//0xC4F402E8
	UINT32                                                  reserved170;	//0xC4F402EC
	UINT32                                                  reserved171;	//0xC4F402F0
	UINT32                                                  reserved172;	//0xC4F402F4
	UINT32                                                  reserved173;	//0xC4F402F8
	UINT32                                                  reserved174;	//0xC4F402FC
	REG_DDRC_M0_DFS_T                                               dfs;	//0xC4F40300
	REG_DDRC_M0_DFS_RESULT_T                                 dfs_result;	//0xC4F40304
	UINT32                                                  reserved175;	//0xC4F40308
	UINT32                                                  reserved176;	//0xC4F4030C
	UINT32                                                  reserved177;	//0xC4F40310
	UINT32                                                  reserved178;	//0xC4F40314
	UINT32                                                  reserved179;	//0xC4F40318
	UINT32                                                  reserved180;	//0xC4F4031C
	UINT32                                                  reserved181;	//0xC4F40320
	UINT32                                                  reserved182;	//0xC4F40324
	UINT32                                                  reserved183;	//0xC4F40328
	UINT32                                                  reserved184;	//0xC4F4032C
	UINT32                                                  reserved185;	//0xC4F40330
	UINT32                                                  reserved186;	//0xC4F40334
	UINT32                                                  reserved187;	//0xC4F40338
	UINT32                                                  reserved188;	//0xC4F4033C
	UINT32                                                  reserved189;	//0xC4F40340
	UINT32                                                  reserved190;	//0xC4F40344
	UINT32                                                  reserved191;	//0xC4F40348
	UINT32                                                  reserved192;	//0xC4F4034C
	UINT32                                                  reserved193;	//0xC4F40350
	UINT32                                                  reserved194;	//0xC4F40354
	UINT32                                                  reserved195;	//0xC4F40358
	UINT32                                                  reserved196;	//0xC4F4035C
	UINT32                                                  reserved197;	//0xC4F40360
	UINT32                                                  reserved198;	//0xC4F40364
	UINT32                                                  reserved199;	//0xC4F40368
	UINT32                                                  reserved200;	//0xC4F4036C
	UINT32                                                  reserved201;	//0xC4F40370
	UINT32                                                  reserved202;	//0xC4F40374
	UINT32                                                  reserved203;	//0xC4F40378
	UINT32                                                  reserved204;	//0xC4F4037C
	UINT32                                                  reserved205;	//0xC4F40380
	UINT32                                                  reserved206;	//0xC4F40384
	UINT32                                                  reserved207;	//0xC4F40388
	UINT32                                                  reserved208;	//0xC4F4038C
	UINT32                                                  reserved209;	//0xC4F40390
	UINT32                                                  reserved210;	//0xC4F40394
	UINT32                                                  reserved211;	//0xC4F40398
	UINT32                                                  reserved212;	//0xC4F4039C
	UINT32                                                  reserved213;	//0xC4F403A0
	UINT32                                                  reserved214;	//0xC4F403A4
	UINT32                                                  reserved215;	//0xC4F403A8
	UINT32                                                  reserved216;	//0xC4F403AC
	UINT32                                                  reserved217;	//0xC4F403B0
	UINT32                                                  reserved218;	//0xC4F403B4
	UINT32                                                  reserved219;	//0xC4F403B8
	UINT32                                                  reserved220;	//0xC4F403BC
	UINT32                                                  reserved221;	//0xC4F403C0
	UINT32                                                  reserved222;	//0xC4F403C4
	UINT32                                                  reserved223;	//0xC4F403C8
	UINT32                                                  reserved224;	//0xC4F403CC
	UINT32                                                  reserved225;	//0xC4F403D0
	UINT32                                                  reserved226;	//0xC4F403D4
	UINT32                                                  reserved227;	//0xC4F403D8
	UINT32                                                  reserved228;	//0xC4F403DC
	UINT32                                                  reserved229;	//0xC4F403E0
	UINT32                                                  reserved230;	//0xC4F403E4
	UINT32                                                  reserved231;	//0xC4F403E8
	UINT32                                                  reserved232;	//0xC4F403EC
	UINT32                                                  reserved233;	//0xC4F403F0
	UINT32                                                  reserved234;	//0xC4F403F4
	UINT32                                                  reserved235;	//0xC4F403F8
	UINT32                                                  reserved236;	//0xC4F403FC
	REG_DDRC_M0_ADDR_MAP_T                                     addr_map;	//0xC4F40400
	REG_DDRC_M0_COMMON_T                                         common;	//0xC4F40404
	REG_DDRC_M0_DATA_ENC0_T                                   data_enc0;	//0xC4F40408
	REG_DDRC_M0_DATA_ENC1_T                                   data_enc1;	//0xC4F4040C
	UINT32                                                  reserved237;	//0xC4F40410
	UINT32                                                  reserved238;	//0xC4F40414
	UINT32                                                  reserved239;	//0xC4F40418
	UINT32                                                  reserved240;	//0xC4F4041C
	UINT32                                                  reserved241;	//0xC4F40420
	UINT32                                                  reserved242;	//0xC4F40424
	UINT32                                                  reserved243;	//0xC4F40428
	UINT32                                                  reserved244;	//0xC4F4042C
	UINT32                                                  reserved245;	//0xC4F40430
	UINT32                                                  reserved246;	//0xC4F40434
	UINT32                                                  reserved247;	//0xC4F40438
	UINT32                                                  reserved248;	//0xC4F4043C
	UINT32                                                  reserved249;	//0xC4F40440
	UINT32                                                  reserved250;	//0xC4F40444
	UINT32                                                  reserved251;	//0xC4F40448
	UINT32                                                  reserved252;	//0xC4F4044C
	UINT32                                                  reserved253;	//0xC4F40450
	UINT32                                                  reserved254;	//0xC4F40454
	UINT32                                                  reserved255;	//0xC4F40458
	UINT32                                                  reserved256;	//0xC4F4045C
	UINT32                                                  reserved257;	//0xC4F40460
	UINT32                                                  reserved258;	//0xC4F40464
	UINT32                                                  reserved259;	//0xC4F40468
	UINT32                                                  reserved260;	//0xC4F4046C
	UINT32                                                  reserved261;	//0xC4F40470
	UINT32                                                  reserved262;	//0xC4F40474
	UINT32                                                  reserved263;	//0xC4F40478
	UINT32                                                  reserved264;	//0xC4F4047C
	UINT32                                                  reserved265;	//0xC4F40480
	UINT32                                                  reserved266;	//0xC4F40484
	UINT32                                                  reserved267;	//0xC4F40488
	UINT32                                                  reserved268;	//0xC4F4048C
	UINT32                                                  reserved269;	//0xC4F40490
	UINT32                                                  reserved270;	//0xC4F40494
	UINT32                                                  reserved271;	//0xC4F40498
	UINT32                                                  reserved272;	//0xC4F4049C
	UINT32                                                  reserved273;	//0xC4F404A0
	UINT32                                                  reserved274;	//0xC4F404A4
	UINT32                                                  reserved275;	//0xC4F404A8
	UINT32                                                  reserved276;	//0xC4F404AC
	UINT32                                                  reserved277;	//0xC4F404B0
	UINT32                                                  reserved278;	//0xC4F404B4
	UINT32                                                  reserved279;	//0xC4F404B8
	UINT32                                                  reserved280;	//0xC4F404BC
	UINT32                                                  reserved281;	//0xC4F404C0
	UINT32                                                  reserved282;	//0xC4F404C4
	UINT32                                                  reserved283;	//0xC4F404C8
	UINT32                                                  reserved284;	//0xC4F404CC
	UINT32                                                  reserved285;	//0xC4F404D0
	UINT32                                                  reserved286;	//0xC4F404D4
	UINT32                                                  reserved287;	//0xC4F404D8
	UINT32                                                  reserved288;	//0xC4F404DC
	UINT32                                                  reserved289;	//0xC4F404E0
	UINT32                                                  reserved290;	//0xC4F404E4
	UINT32                                                  reserved291;	//0xC4F404E8
	UINT32                                                  reserved292;	//0xC4F404EC
	UINT32                                                  reserved293;	//0xC4F404F0
	UINT32                                                  reserved294;	//0xC4F404F4
	UINT32                                                  reserved295;	//0xC4F404F8
	UINT32                                                  reserved296;	//0xC4F404FC
	REG_DDRC_M0_RD_URG_T                                         rd_urg;	//0xC4F40500
	REG_DDRC_M0_WR_URG_T                                         wr_urg;	//0xC4F40504
	UINT32                                                  reserved297;	//0xC4F40508
	UINT32                                                  reserved298;	//0xC4F4050C
	UINT32                                                  reserved299;	//0xC4F40510
	UINT32                                                  reserved300;	//0xC4F40514
	UINT32                                                  reserved301;	//0xC4F40518
	UINT32                                                  reserved302;	//0xC4F4051C
	UINT32                                                  reserved303;	//0xC4F40520
	UINT32                                                  reserved304;	//0xC4F40524
	UINT32                                                  reserved305;	//0xC4F40528
	UINT32                                                  reserved306;	//0xC4F4052C
	UINT32                                                  reserved307;	//0xC4F40530
	UINT32                                                  reserved308;	//0xC4F40534
	UINT32                                                  reserved309;	//0xC4F40538
	UINT32                                                  reserved310;	//0xC4F4053C
	UINT32                                                  reserved311;	//0xC4F40540
	UINT32                                                  reserved312;	//0xC4F40544
	UINT32                                                  reserved313;	//0xC4F40548
	UINT32                                                  reserved314;	//0xC4F4054C
	UINT32                                                  reserved315;	//0xC4F40550
	UINT32                                                  reserved316;	//0xC4F40554
	UINT32                                                  reserved317;	//0xC4F40558
	UINT32                                                  reserved318;	//0xC4F4055C
	UINT32                                                  reserved319;	//0xC4F40560
	UINT32                                                  reserved320;	//0xC4F40564
	UINT32                                                  reserved321;	//0xC4F40568
	UINT32                                                  reserved322;	//0xC4F4056C
	UINT32                                                  reserved323;	//0xC4F40570
	UINT32                                                  reserved324;	//0xC4F40574
	UINT32                                                  reserved325;	//0xC4F40578
	UINT32                                                  reserved326;	//0xC4F4057C
	UINT32                                                  reserved327;	//0xC4F40580
	UINT32                                                  reserved328;	//0xC4F40584
	UINT32                                                  reserved329;	//0xC4F40588
	UINT32                                                  reserved330;	//0xC4F4058C
	UINT32                                                  reserved331;	//0xC4F40590
	UINT32                                                  reserved332;	//0xC4F40594
	UINT32                                                  reserved333;	//0xC4F40598
	UINT32                                                  reserved334;	//0xC4F4059C
	UINT32                                                  reserved335;	//0xC4F405A0
	UINT32                                                  reserved336;	//0xC4F405A4
	UINT32                                                  reserved337;	//0xC4F405A8
	UINT32                                                  reserved338;	//0xC4F405AC
	UINT32                                                  reserved339;	//0xC4F405B0
	UINT32                                                  reserved340;	//0xC4F405B4
	UINT32                                                  reserved341;	//0xC4F405B8
	UINT32                                                  reserved342;	//0xC4F405BC
	UINT32                                                  reserved343;	//0xC4F405C0
	UINT32                                                  reserved344;	//0xC4F405C4
	UINT32                                                  reserved345;	//0xC4F405C8
	UINT32                                                  reserved346;	//0xC4F405CC
	UINT32                                                  reserved347;	//0xC4F405D0
	UINT32                                                  reserved348;	//0xC4F405D4
	UINT32                                                  reserved349;	//0xC4F405D8
	UINT32                                                  reserved350;	//0xC4F405DC
	UINT32                                                  reserved351;	//0xC4F405E0
	UINT32                                                  reserved352;	//0xC4F405E4
	UINT32                                                  reserved353;	//0xC4F405E8
	UINT32                                                  reserved354;	//0xC4F405EC
	UINT32                                                  reserved355;	//0xC4F405F0
	UINT32                                                  reserved356;	//0xC4F405F4
	UINT32                                                  reserved357;	//0xC4F405F8
	UINT32                                                  reserved358;	//0xC4F405FC
	UINT32                                                  reserved359;	//0xC4F40600
	UINT32                                                  reserved360;	//0xC4F40604
	UINT32                                                  reserved361;	//0xC4F40608
	UINT32                                                  reserved362;	//0xC4F4060C
	UINT32                                                  reserved363;	//0xC4F40610
	UINT32                                                  reserved364;	//0xC4F40614
	UINT32                                                  reserved365;	//0xC4F40618
	UINT32                                                  reserved366;	//0xC4F4061C
	UINT32                                                  reserved367;	//0xC4F40620
	UINT32                                                  reserved368;	//0xC4F40624
	UINT32                                                  reserved369;	//0xC4F40628
	UINT32                                                  reserved370;	//0xC4F4062C
	UINT32                                                  reserved371;	//0xC4F40630
	UINT32                                                  reserved372;	//0xC4F40634
	UINT32                                                  reserved373;	//0xC4F40638
	UINT32                                                  reserved374;	//0xC4F4063C
	UINT32                                                  reserved375;	//0xC4F40640
	UINT32                                                  reserved376;	//0xC4F40644
	UINT32                                                  reserved377;	//0xC4F40648
	UINT32                                                  reserved378;	//0xC4F4064C
	UINT32                                                  reserved379;	//0xC4F40650
	UINT32                                                  reserved380;	//0xC4F40654
	UINT32                                                  reserved381;	//0xC4F40658
	UINT32                                                  reserved382;	//0xC4F4065C
	UINT32                                                  reserved383;	//0xC4F40660
	UINT32                                                  reserved384;	//0xC4F40664
	UINT32                                                  reserved385;	//0xC4F40668
	UINT32                                                  reserved386;	//0xC4F4066C
	UINT32                                                  reserved387;	//0xC4F40670
	UINT32                                                  reserved388;	//0xC4F40674
	UINT32                                                  reserved389;	//0xC4F40678
	UINT32                                                  reserved390;	//0xC4F4067C
	UINT32                                                  reserved391;	//0xC4F40680
	UINT32                                                  reserved392;	//0xC4F40684
	UINT32                                                  reserved393;	//0xC4F40688
	UINT32                                                  reserved394;	//0xC4F4068C
	UINT32                                                  reserved395;	//0xC4F40690
	UINT32                                                  reserved396;	//0xC4F40694
	UINT32                                                  reserved397;	//0xC4F40698
	UINT32                                                  reserved398;	//0xC4F4069C
	UINT32                                                  reserved399;	//0xC4F406A0
	UINT32                                                  reserved400;	//0xC4F406A4
	UINT32                                                  reserved401;	//0xC4F406A8
	UINT32                                                  reserved402;	//0xC4F406AC
	UINT32                                                  reserved403;	//0xC4F406B0
	UINT32                                                  reserved404;	//0xC4F406B4
	UINT32                                                  reserved405;	//0xC4F406B8
	UINT32                                                  reserved406;	//0xC4F406BC
	UINT32                                                  reserved407;	//0xC4F406C0
	UINT32                                                  reserved408;	//0xC4F406C4
	UINT32                                                  reserved409;	//0xC4F406C8
	UINT32                                                  reserved410;	//0xC4F406CC
	UINT32                                                  reserved411;	//0xC4F406D0
	UINT32                                                  reserved412;	//0xC4F406D4
	UINT32                                                  reserved413;	//0xC4F406D8
	UINT32                                                  reserved414;	//0xC4F406DC
	UINT32                                                  reserved415;	//0xC4F406E0
	UINT32                                                  reserved416;	//0xC4F406E4
	UINT32                                                  reserved417;	//0xC4F406E8
	UINT32                                                  reserved418;	//0xC4F406EC
	UINT32                                                  reserved419;	//0xC4F406F0
	UINT32                                                  reserved420;	//0xC4F406F4
	UINT32                                                  reserved421;	//0xC4F406F8
	UINT32                                                  reserved422;	//0xC4F406FC
	UINT32                                                  reserved423;	//0xC4F40700
	UINT32                                                  reserved424;	//0xC4F40704
	UINT32                                                  reserved425;	//0xC4F40708
	UINT32                                                  reserved426;	//0xC4F4070C
	UINT32                                                  reserved427;	//0xC4F40710
	UINT32                                                  reserved428;	//0xC4F40714
	UINT32                                                  reserved429;	//0xC4F40718
	UINT32                                                  reserved430;	//0xC4F4071C
	UINT32                                                  reserved431;	//0xC4F40720
	UINT32                                                  reserved432;	//0xC4F40724
	UINT32                                                  reserved433;	//0xC4F40728
	UINT32                                                  reserved434;	//0xC4F4072C
	UINT32                                                  reserved435;	//0xC4F40730
	UINT32                                                  reserved436;	//0xC4F40734
	UINT32                                                  reserved437;	//0xC4F40738
	UINT32                                                  reserved438;	//0xC4F4073C
	UINT32                                                  reserved439;	//0xC4F40740
	UINT32                                                  reserved440;	//0xC4F40744
	UINT32                                                  reserved441;	//0xC4F40748
	UINT32                                                  reserved442;	//0xC4F4074C
	UINT32                                                  reserved443;	//0xC4F40750
	UINT32                                                  reserved444;	//0xC4F40754
	UINT32                                                  reserved445;	//0xC4F40758
	UINT32                                                  reserved446;	//0xC4F4075C
	UINT32                                                  reserved447;	//0xC4F40760
	UINT32                                                  reserved448;	//0xC4F40764
	UINT32                                                  reserved449;	//0xC4F40768
	UINT32                                                  reserved450;	//0xC4F4076C
	UINT32                                                  reserved451;	//0xC4F40770
	UINT32                                                  reserved452;	//0xC4F40774
	UINT32                                                  reserved453;	//0xC4F40778
	UINT32                                                  reserved454;	//0xC4F4077C
	UINT32                                                  reserved455;	//0xC4F40780
	UINT32                                                  reserved456;	//0xC4F40784
	UINT32                                                  reserved457;	//0xC4F40788
	UINT32                                                  reserved458;	//0xC4F4078C
	UINT32                                                  reserved459;	//0xC4F40790
	UINT32                                                  reserved460;	//0xC4F40794
	UINT32                                                  reserved461;	//0xC4F40798
	UINT32                                                  reserved462;	//0xC4F4079C
	UINT32                                                  reserved463;	//0xC4F407A0
	UINT32                                                  reserved464;	//0xC4F407A4
	UINT32                                                  reserved465;	//0xC4F407A8
	UINT32                                                  reserved466;	//0xC4F407AC
	UINT32                                                  reserved467;	//0xC4F407B0
	UINT32                                                  reserved468;	//0xC4F407B4
	UINT32                                                  reserved469;	//0xC4F407B8
	UINT32                                                  reserved470;	//0xC4F407BC
	UINT32                                                  reserved471;	//0xC4F407C0
	UINT32                                                  reserved472;	//0xC4F407C4
	UINT32                                                  reserved473;	//0xC4F407C8
	UINT32                                                  reserved474;	//0xC4F407CC
	UINT32                                                  reserved475;	//0xC4F407D0
	UINT32                                                  reserved476;	//0xC4F407D4
	UINT32                                                  reserved477;	//0xC4F407D8
	UINT32                                                  reserved478;	//0xC4F407DC
	UINT32                                                  reserved479;	//0xC4F407E0
	UINT32                                                  reserved480;	//0xC4F407E4
	UINT32                                                  reserved481;	//0xC4F407E8
	UINT32                                                  reserved482;	//0xC4F407EC
	UINT32                                                  reserved483;	//0xC4F407F0
	UINT32                                                  reserved484;	//0xC4F407F4
	UINT32                                                  reserved485;	//0xC4F407F8
	UINT32                                                  reserved486;	//0xC4F407FC
	UINT32                                                  reserved487;	//0xC4F40800
	UINT32                                                  reserved488;	//0xC4F40804
	UINT32                                                  reserved489;	//0xC4F40808
	UINT32                                                  reserved490;	//0xC4F4080C
	UINT32                                                  reserved491;	//0xC4F40810
	UINT32                                                  reserved492;	//0xC4F40814
	UINT32                                                  reserved493;	//0xC4F40818
	UINT32                                                  reserved494;	//0xC4F4081C
	UINT32                                                  reserved495;	//0xC4F40820
	UINT32                                                  reserved496;	//0xC4F40824
	UINT32                                                  reserved497;	//0xC4F40828
	UINT32                                                  reserved498;	//0xC4F4082C
	UINT32                                                  reserved499;	//0xC4F40830
	UINT32                                                  reserved500;	//0xC4F40834
	UINT32                                                  reserved501;	//0xC4F40838
	UINT32                                                  reserved502;	//0xC4F4083C
	UINT32                                                  reserved503;	//0xC4F40840
	UINT32                                                  reserved504;	//0xC4F40844
	UINT32                                                  reserved505;	//0xC4F40848
	UINT32                                                  reserved506;	//0xC4F4084C
	UINT32                                                  reserved507;	//0xC4F40850
	UINT32                                                  reserved508;	//0xC4F40854
	UINT32                                                  reserved509;	//0xC4F40858
	UINT32                                                  reserved510;	//0xC4F4085C
	UINT32                                                  reserved511;	//0xC4F40860
	UINT32                                                  reserved512;	//0xC4F40864
	UINT32                                                  reserved513;	//0xC4F40868
	UINT32                                                  reserved514;	//0xC4F4086C
	UINT32                                                  reserved515;	//0xC4F40870
	UINT32                                                  reserved516;	//0xC4F40874
	UINT32                                                  reserved517;	//0xC4F40878
	UINT32                                                  reserved518;	//0xC4F4087C
	UINT32                                                  reserved519;	//0xC4F40880
	UINT32                                                  reserved520;	//0xC4F40884
	UINT32                                                  reserved521;	//0xC4F40888
	UINT32                                                  reserved522;	//0xC4F4088C
	UINT32                                                  reserved523;	//0xC4F40890
	UINT32                                                  reserved524;	//0xC4F40894
	UINT32                                                  reserved525;	//0xC4F40898
	UINT32                                                  reserved526;	//0xC4F4089C
	UINT32                                                  reserved527;	//0xC4F408A0
	UINT32                                                  reserved528;	//0xC4F408A4
	UINT32                                                  reserved529;	//0xC4F408A8
	UINT32                                                  reserved530;	//0xC4F408AC
	UINT32                                                  reserved531;	//0xC4F408B0
	UINT32                                                  reserved532;	//0xC4F408B4
	UINT32                                                  reserved533;	//0xC4F408B8
	UINT32                                                  reserved534;	//0xC4F408BC
	UINT32                                                  reserved535;	//0xC4F408C0
	UINT32                                                  reserved536;	//0xC4F408C4
	UINT32                                                  reserved537;	//0xC4F408C8
	UINT32                                                  reserved538;	//0xC4F408CC
	UINT32                                                  reserved539;	//0xC4F408D0
	UINT32                                                  reserved540;	//0xC4F408D4
	UINT32                                                  reserved541;	//0xC4F408D8
	UINT32                                                  reserved542;	//0xC4F408DC
	UINT32                                                  reserved543;	//0xC4F408E0
	UINT32                                                  reserved544;	//0xC4F408E4
	UINT32                                                  reserved545;	//0xC4F408E8
	UINT32                                                  reserved546;	//0xC4F408EC
	UINT32                                                  reserved547;	//0xC4F408F0
	UINT32                                                  reserved548;	//0xC4F408F4
	UINT32                                                  reserved549;	//0xC4F408F8
	UINT32                                                  reserved550;	//0xC4F408FC
	UINT32                                                  reserved551;	//0xC4F40900
	UINT32                                                  reserved552;	//0xC4F40904
	UINT32                                                  reserved553;	//0xC4F40908
	UINT32                                                  reserved554;	//0xC4F4090C
	UINT32                                                  reserved555;	//0xC4F40910
	UINT32                                                  reserved556;	//0xC4F40914
	UINT32                                                  reserved557;	//0xC4F40918
	UINT32                                                  reserved558;	//0xC4F4091C
	UINT32                                                  reserved559;	//0xC4F40920
	UINT32                                                  reserved560;	//0xC4F40924
	UINT32                                                  reserved561;	//0xC4F40928
	UINT32                                                  reserved562;	//0xC4F4092C
	UINT32                                                  reserved563;	//0xC4F40930
	UINT32                                                  reserved564;	//0xC4F40934
	UINT32                                                  reserved565;	//0xC4F40938
	UINT32                                                  reserved566;	//0xC4F4093C
	UINT32                                                  reserved567;	//0xC4F40940
	UINT32                                                  reserved568;	//0xC4F40944
	UINT32                                                  reserved569;	//0xC4F40948
	UINT32                                                  reserved570;	//0xC4F4094C
	UINT32                                                  reserved571;	//0xC4F40950
	UINT32                                                  reserved572;	//0xC4F40954
	UINT32                                                  reserved573;	//0xC4F40958
	UINT32                                                  reserved574;	//0xC4F4095C
	UINT32                                                  reserved575;	//0xC4F40960
	UINT32                                                  reserved576;	//0xC4F40964
	UINT32                                                  reserved577;	//0xC4F40968
	UINT32                                                  reserved578;	//0xC4F4096C
	UINT32                                                  reserved579;	//0xC4F40970
	UINT32                                                  reserved580;	//0xC4F40974
	UINT32                                                  reserved581;	//0xC4F40978
	UINT32                                                  reserved582;	//0xC4F4097C
	UINT32                                                  reserved583;	//0xC4F40980
	UINT32                                                  reserved584;	//0xC4F40984
	UINT32                                                  reserved585;	//0xC4F40988
	UINT32                                                  reserved586;	//0xC4F4098C
	UINT32                                                  reserved587;	//0xC4F40990
	UINT32                                                  reserved588;	//0xC4F40994
	UINT32                                                  reserved589;	//0xC4F40998
	UINT32                                                  reserved590;	//0xC4F4099C
	UINT32                                                  reserved591;	//0xC4F409A0
	UINT32                                                  reserved592;	//0xC4F409A4
	UINT32                                                  reserved593;	//0xC4F409A8
	UINT32                                                  reserved594;	//0xC4F409AC
	UINT32                                                  reserved595;	//0xC4F409B0
	UINT32                                                  reserved596;	//0xC4F409B4
	UINT32                                                  reserved597;	//0xC4F409B8
	UINT32                                                  reserved598;	//0xC4F409BC
	UINT32                                                  reserved599;	//0xC4F409C0
	UINT32                                                  reserved600;	//0xC4F409C4
	UINT32                                                  reserved601;	//0xC4F409C8
	UINT32                                                  reserved602;	//0xC4F409CC
	UINT32                                                  reserved603;	//0xC4F409D0
	UINT32                                                  reserved604;	//0xC4F409D4
	UINT32                                                  reserved605;	//0xC4F409D8
	UINT32                                                  reserved606;	//0xC4F409DC
	UINT32                                                  reserved607;	//0xC4F409E0
	UINT32                                                  reserved608;	//0xC4F409E4
	UINT32                                                  reserved609;	//0xC4F409E8
	UINT32                                                  reserved610;	//0xC4F409EC
	UINT32                                                  reserved611;	//0xC4F409F0
	UINT32                                                  reserved612;	//0xC4F409F4
	UINT32                                                  reserved613;	//0xC4F409F8
	UINT32                                                  reserved614;	//0xC4F409FC
	UINT32                                                  reserved615;	//0xC4F40A00
	UINT32                                                  reserved616;	//0xC4F40A04
	UINT32                                                  reserved617;	//0xC4F40A08
	UINT32                                                  reserved618;	//0xC4F40A0C
	UINT32                                                  reserved619;	//0xC4F40A10
	UINT32                                                  reserved620;	//0xC4F40A14
	UINT32                                                  reserved621;	//0xC4F40A18
	UINT32                                                  reserved622;	//0xC4F40A1C
	UINT32                                                  reserved623;	//0xC4F40A20
	UINT32                                                  reserved624;	//0xC4F40A24
	UINT32                                                  reserved625;	//0xC4F40A28
	UINT32                                                  reserved626;	//0xC4F40A2C
	UINT32                                                  reserved627;	//0xC4F40A30
	UINT32                                                  reserved628;	//0xC4F40A34
	UINT32                                                  reserved629;	//0xC4F40A38
	UINT32                                                  reserved630;	//0xC4F40A3C
	UINT32                                                  reserved631;	//0xC4F40A40
	UINT32                                                  reserved632;	//0xC4F40A44
	UINT32                                                  reserved633;	//0xC4F40A48
	UINT32                                                  reserved634;	//0xC4F40A4C
	UINT32                                                  reserved635;	//0xC4F40A50
	UINT32                                                  reserved636;	//0xC4F40A54
	UINT32                                                  reserved637;	//0xC4F40A58
	UINT32                                                  reserved638;	//0xC4F40A5C
	UINT32                                                  reserved639;	//0xC4F40A60
	UINT32                                                  reserved640;	//0xC4F40A64
	UINT32                                                  reserved641;	//0xC4F40A68
	UINT32                                                  reserved642;	//0xC4F40A6C
	UINT32                                                  reserved643;	//0xC4F40A70
	UINT32                                                  reserved644;	//0xC4F40A74
	UINT32                                                  reserved645;	//0xC4F40A78
	UINT32                                                  reserved646;	//0xC4F40A7C
	UINT32                                                  reserved647;	//0xC4F40A80
	UINT32                                                  reserved648;	//0xC4F40A84
	UINT32                                                  reserved649;	//0xC4F40A88
	UINT32                                                  reserved650;	//0xC4F40A8C
	UINT32                                                  reserved651;	//0xC4F40A90
	UINT32                                                  reserved652;	//0xC4F40A94
	UINT32                                                  reserved653;	//0xC4F40A98
	UINT32                                                  reserved654;	//0xC4F40A9C
	UINT32                                                  reserved655;	//0xC4F40AA0
	UINT32                                                  reserved656;	//0xC4F40AA4
	UINT32                                                  reserved657;	//0xC4F40AA8
	UINT32                                                  reserved658;	//0xC4F40AAC
	UINT32                                                  reserved659;	//0xC4F40AB0
	UINT32                                                  reserved660;	//0xC4F40AB4
	UINT32                                                  reserved661;	//0xC4F40AB8
	UINT32                                                  reserved662;	//0xC4F40ABC
	UINT32                                                  reserved663;	//0xC4F40AC0
	UINT32                                                  reserved664;	//0xC4F40AC4
	UINT32                                                  reserved665;	//0xC4F40AC8
	UINT32                                                  reserved666;	//0xC4F40ACC
	UINT32                                                  reserved667;	//0xC4F40AD0
	UINT32                                                  reserved668;	//0xC4F40AD4
	UINT32                                                  reserved669;	//0xC4F40AD8
	UINT32                                                  reserved670;	//0xC4F40ADC
	UINT32                                                  reserved671;	//0xC4F40AE0
	UINT32                                                  reserved672;	//0xC4F40AE4
	UINT32                                                  reserved673;	//0xC4F40AE8
	UINT32                                                  reserved674;	//0xC4F40AEC
	UINT32                                                  reserved675;	//0xC4F40AF0
	UINT32                                                  reserved676;	//0xC4F40AF4
	UINT32                                                  reserved677;	//0xC4F40AF8
	UINT32                                                  reserved678;	//0xC4F40AFC
	UINT32                                                  reserved679;	//0xC4F40B00
	UINT32                                                  reserved680;	//0xC4F40B04
	UINT32                                                  reserved681;	//0xC4F40B08
	UINT32                                                  reserved682;	//0xC4F40B0C
	UINT32                                                  reserved683;	//0xC4F40B10
	UINT32                                                  reserved684;	//0xC4F40B14
	UINT32                                                  reserved685;	//0xC4F40B18
	UINT32                                                  reserved686;	//0xC4F40B1C
	UINT32                                                  reserved687;	//0xC4F40B20
	UINT32                                                  reserved688;	//0xC4F40B24
	UINT32                                                  reserved689;	//0xC4F40B28
	UINT32                                                  reserved690;	//0xC4F40B2C
	UINT32                                                  reserved691;	//0xC4F40B30
	UINT32                                                  reserved692;	//0xC4F40B34
	UINT32                                                  reserved693;	//0xC4F40B38
	UINT32                                                  reserved694;	//0xC4F40B3C
	UINT32                                                  reserved695;	//0xC4F40B40
	UINT32                                                  reserved696;	//0xC4F40B44
	UINT32                                                  reserved697;	//0xC4F40B48
	UINT32                                                  reserved698;	//0xC4F40B4C
	UINT32                                                  reserved699;	//0xC4F40B50
	UINT32                                                  reserved700;	//0xC4F40B54
	UINT32                                                  reserved701;	//0xC4F40B58
	UINT32                                                  reserved702;	//0xC4F40B5C
	UINT32                                                  reserved703;	//0xC4F40B60
	UINT32                                                  reserved704;	//0xC4F40B64
	UINT32                                                  reserved705;	//0xC4F40B68
	UINT32                                                  reserved706;	//0xC4F40B6C
	UINT32                                                  reserved707;	//0xC4F40B70
	UINT32                                                  reserved708;	//0xC4F40B74
	UINT32                                                  reserved709;	//0xC4F40B78
	UINT32                                                  reserved710;	//0xC4F40B7C
	UINT32                                                  reserved711;	//0xC4F40B80
	UINT32                                                  reserved712;	//0xC4F40B84
	UINT32                                                  reserved713;	//0xC4F40B88
	UINT32                                                  reserved714;	//0xC4F40B8C
	UINT32                                                  reserved715;	//0xC4F40B90
	UINT32                                                  reserved716;	//0xC4F40B94
	UINT32                                                  reserved717;	//0xC4F40B98
	UINT32                                                  reserved718;	//0xC4F40B9C
	UINT32                                                  reserved719;	//0xC4F40BA0
	UINT32                                                  reserved720;	//0xC4F40BA4
	UINT32                                                  reserved721;	//0xC4F40BA8
	UINT32                                                  reserved722;	//0xC4F40BAC
	UINT32                                                  reserved723;	//0xC4F40BB0
	UINT32                                                  reserved724;	//0xC4F40BB4
	UINT32                                                  reserved725;	//0xC4F40BB8
	UINT32                                                  reserved726;	//0xC4F40BBC
	UINT32                                                  reserved727;	//0xC4F40BC0
	UINT32                                                  reserved728;	//0xC4F40BC4
	UINT32                                                  reserved729;	//0xC4F40BC8
	UINT32                                                  reserved730;	//0xC4F40BCC
	UINT32                                                  reserved731;	//0xC4F40BD0
	UINT32                                                  reserved732;	//0xC4F40BD4
	UINT32                                                  reserved733;	//0xC4F40BD8
	UINT32                                                  reserved734;	//0xC4F40BDC
	UINT32                                                  reserved735;	//0xC4F40BE0
	UINT32                                                  reserved736;	//0xC4F40BE4
	UINT32                                                  reserved737;	//0xC4F40BE8
	UINT32                                                  reserved738;	//0xC4F40BEC
	UINT32                                                  reserved739;	//0xC4F40BF0
	UINT32                                                  reserved740;	//0xC4F40BF4
	UINT32                                                  reserved741;	//0xC4F40BF8
	UINT32                                                  reserved742;	//0xC4F40BFC
	UINT32                                                  reserved743;	//0xC4F40C00
	UINT32                                                  reserved744;	//0xC4F40C04
	UINT32                                                  reserved745;	//0xC4F40C08
	UINT32                                                  reserved746;	//0xC4F40C0C
	UINT32                                                  reserved747;	//0xC4F40C10
	UINT32                                                  reserved748;	//0xC4F40C14
	UINT32                                                  reserved749;	//0xC4F40C18
	UINT32                                                  reserved750;	//0xC4F40C1C
	UINT32                                                  reserved751;	//0xC4F40C20
	UINT32                                                  reserved752;	//0xC4F40C24
	UINT32                                                  reserved753;	//0xC4F40C28
	UINT32                                                  reserved754;	//0xC4F40C2C
	UINT32                                                  reserved755;	//0xC4F40C30
	UINT32                                                  reserved756;	//0xC4F40C34
	UINT32                                                  reserved757;	//0xC4F40C38
	UINT32                                                  reserved758;	//0xC4F40C3C
	UINT32                                                  reserved759;	//0xC4F40C40
	UINT32                                                  reserved760;	//0xC4F40C44
	UINT32                                                  reserved761;	//0xC4F40C48
	UINT32                                                  reserved762;	//0xC4F40C4C
	UINT32                                                  reserved763;	//0xC4F40C50
	UINT32                                                  reserved764;	//0xC4F40C54
	UINT32                                                  reserved765;	//0xC4F40C58
	UINT32                                                  reserved766;	//0xC4F40C5C
	UINT32                                                  reserved767;	//0xC4F40C60
	UINT32                                                  reserved768;	//0xC4F40C64
	UINT32                                                  reserved769;	//0xC4F40C68
	UINT32                                                  reserved770;	//0xC4F40C6C
	UINT32                                                  reserved771;	//0xC4F40C70
	UINT32                                                  reserved772;	//0xC4F40C74
	UINT32                                                  reserved773;	//0xC4F40C78
	UINT32                                                  reserved774;	//0xC4F40C7C
	UINT32                                                  reserved775;	//0xC4F40C80
	UINT32                                                  reserved776;	//0xC4F40C84
	UINT32                                                  reserved777;	//0xC4F40C88
	UINT32                                                  reserved778;	//0xC4F40C8C
	UINT32                                                  reserved779;	//0xC4F40C90
	UINT32                                                  reserved780;	//0xC4F40C94
	UINT32                                                  reserved781;	//0xC4F40C98
	UINT32                                                  reserved782;	//0xC4F40C9C
	UINT32                                                  reserved783;	//0xC4F40CA0
	UINT32                                                  reserved784;	//0xC4F40CA4
	UINT32                                                  reserved785;	//0xC4F40CA8
	UINT32                                                  reserved786;	//0xC4F40CAC
	UINT32                                                  reserved787;	//0xC4F40CB0
	UINT32                                                  reserved788;	//0xC4F40CB4
	UINT32                                                  reserved789;	//0xC4F40CB8
	UINT32                                                  reserved790;	//0xC4F40CBC
	UINT32                                                  reserved791;	//0xC4F40CC0
	UINT32                                                  reserved792;	//0xC4F40CC4
	UINT32                                                  reserved793;	//0xC4F40CC8
	UINT32                                                  reserved794;	//0xC4F40CCC
	UINT32                                                  reserved795;	//0xC4F40CD0
	UINT32                                                  reserved796;	//0xC4F40CD4
	UINT32                                                  reserved797;	//0xC4F40CD8
	UINT32                                                  reserved798;	//0xC4F40CDC
	UINT32                                                  reserved799;	//0xC4F40CE0
	UINT32                                                  reserved800;	//0xC4F40CE4
	UINT32                                                  reserved801;	//0xC4F40CE8
	UINT32                                                  reserved802;	//0xC4F40CEC
	UINT32                                                  reserved803;	//0xC4F40CF0
	UINT32                                                  reserved804;	//0xC4F40CF4
	UINT32                                                  reserved805;	//0xC4F40CF8
	UINT32                                                  reserved806;	//0xC4F40CFC
	UINT32                                                  reserved807;	//0xC4F40D00
	UINT32                                                  reserved808;	//0xC4F40D04
	UINT32                                                  reserved809;	//0xC4F40D08
	UINT32                                                  reserved810;	//0xC4F40D0C
	UINT32                                                  reserved811;	//0xC4F40D10
	UINT32                                                  reserved812;	//0xC4F40D14
	UINT32                                                  reserved813;	//0xC4F40D18
	UINT32                                                  reserved814;	//0xC4F40D1C
	UINT32                                                  reserved815;	//0xC4F40D20
	UINT32                                                  reserved816;	//0xC4F40D24
	UINT32                                                  reserved817;	//0xC4F40D28
	UINT32                                                  reserved818;	//0xC4F40D2C
	UINT32                                                  reserved819;	//0xC4F40D30
	UINT32                                                  reserved820;	//0xC4F40D34
	UINT32                                                  reserved821;	//0xC4F40D38
	UINT32                                                  reserved822;	//0xC4F40D3C
	UINT32                                                  reserved823;	//0xC4F40D40
	UINT32                                                  reserved824;	//0xC4F40D44
	UINT32                                                  reserved825;	//0xC4F40D48
	UINT32                                                  reserved826;	//0xC4F40D4C
	UINT32                                                  reserved827;	//0xC4F40D50
	UINT32                                                  reserved828;	//0xC4F40D54
	UINT32                                                  reserved829;	//0xC4F40D58
	UINT32                                                  reserved830;	//0xC4F40D5C
	UINT32                                                  reserved831;	//0xC4F40D60
	UINT32                                                  reserved832;	//0xC4F40D64
	UINT32                                                  reserved833;	//0xC4F40D68
	UINT32                                                  reserved834;	//0xC4F40D6C
	UINT32                                                  reserved835;	//0xC4F40D70
	UINT32                                                  reserved836;	//0xC4F40D74
	UINT32                                                  reserved837;	//0xC4F40D78
	UINT32                                                  reserved838;	//0xC4F40D7C
	UINT32                                                  reserved839;	//0xC4F40D80
	UINT32                                                  reserved840;	//0xC4F40D84
	UINT32                                                  reserved841;	//0xC4F40D88
	UINT32                                                  reserved842;	//0xC4F40D8C
	UINT32                                                  reserved843;	//0xC4F40D90
	UINT32                                                  reserved844;	//0xC4F40D94
	UINT32                                                  reserved845;	//0xC4F40D98
	UINT32                                                  reserved846;	//0xC4F40D9C
	UINT32                                                  reserved847;	//0xC4F40DA0
	UINT32                                                  reserved848;	//0xC4F40DA4
	UINT32                                                  reserved849;	//0xC4F40DA8
	UINT32                                                  reserved850;	//0xC4F40DAC
	UINT32                                                  reserved851;	//0xC4F40DB0
	UINT32                                                  reserved852;	//0xC4F40DB4
	UINT32                                                  reserved853;	//0xC4F40DB8
	UINT32                                                  reserved854;	//0xC4F40DBC
	UINT32                                                  reserved855;	//0xC4F40DC0
	UINT32                                                  reserved856;	//0xC4F40DC4
	UINT32                                                  reserved857;	//0xC4F40DC8
	UINT32                                                  reserved858;	//0xC4F40DCC
	UINT32                                                  reserved859;	//0xC4F40DD0
	UINT32                                                  reserved860;	//0xC4F40DD4
	UINT32                                                  reserved861;	//0xC4F40DD8
	UINT32                                                  reserved862;	//0xC4F40DDC
	UINT32                                                  reserved863;	//0xC4F40DE0
	UINT32                                                  reserved864;	//0xC4F40DE4
	UINT32                                                  reserved865;	//0xC4F40DE8
	UINT32                                                  reserved866;	//0xC4F40DEC
	UINT32                                                  reserved867;	//0xC4F40DF0
	UINT32                                                  reserved868;	//0xC4F40DF4
	UINT32                                                  reserved869;	//0xC4F40DF8
	UINT32                                                  reserved870;	//0xC4F40DFC
	UINT32                                                  reserved871;	//0xC4F40E00
	UINT32                                                  reserved872;	//0xC4F40E04
	UINT32                                                  reserved873;	//0xC4F40E08
	UINT32                                                  reserved874;	//0xC4F40E0C
	UINT32                                                  reserved875;	//0xC4F40E10
	UINT32                                                  reserved876;	//0xC4F40E14
	UINT32                                                  reserved877;	//0xC4F40E18
	UINT32                                                  reserved878;	//0xC4F40E1C
	UINT32                                                  reserved879;	//0xC4F40E20
	UINT32                                                  reserved880;	//0xC4F40E24
	UINT32                                                  reserved881;	//0xC4F40E28
	UINT32                                                  reserved882;	//0xC4F40E2C
	UINT32                                                  reserved883;	//0xC4F40E30
	UINT32                                                  reserved884;	//0xC4F40E34
	UINT32                                                  reserved885;	//0xC4F40E38
	UINT32                                                  reserved886;	//0xC4F40E3C
	UINT32                                                  reserved887;	//0xC4F40E40
	UINT32                                                  reserved888;	//0xC4F40E44
	UINT32                                                  reserved889;	//0xC4F40E48
	UINT32                                                  reserved890;	//0xC4F40E4C
	UINT32                                                  reserved891;	//0xC4F40E50
	UINT32                                                  reserved892;	//0xC4F40E54
	UINT32                                                  reserved893;	//0xC4F40E58
	UINT32                                                  reserved894;	//0xC4F40E5C
	UINT32                                                  reserved895;	//0xC4F40E60
	UINT32                                                  reserved896;	//0xC4F40E64
	UINT32                                                  reserved897;	//0xC4F40E68
	UINT32                                                  reserved898;	//0xC4F40E6C
	UINT32                                                  reserved899;	//0xC4F40E70
	UINT32                                                  reserved900;	//0xC4F40E74
	UINT32                                                  reserved901;	//0xC4F40E78
	UINT32                                                  reserved902;	//0xC4F40E7C
	UINT32                                                  reserved903;	//0xC4F40E80
	UINT32                                                  reserved904;	//0xC4F40E84
	UINT32                                                  reserved905;	//0xC4F40E88
	UINT32                                                  reserved906;	//0xC4F40E8C
	UINT32                                                  reserved907;	//0xC4F40E90
	UINT32                                                  reserved908;	//0xC4F40E94
	UINT32                                                  reserved909;	//0xC4F40E98
	UINT32                                                  reserved910;	//0xC4F40E9C
	UINT32                                                  reserved911;	//0xC4F40EA0
	UINT32                                                  reserved912;	//0xC4F40EA4
	UINT32                                                  reserved913;	//0xC4F40EA8
	UINT32                                                  reserved914;	//0xC4F40EAC
	UINT32                                                  reserved915;	//0xC4F40EB0
	UINT32                                                  reserved916;	//0xC4F40EB4
	UINT32                                                  reserved917;	//0xC4F40EB8
	UINT32                                                  reserved918;	//0xC4F40EBC
	UINT32                                                  reserved919;	//0xC4F40EC0
	UINT32                                                  reserved920;	//0xC4F40EC4
	UINT32                                                  reserved921;	//0xC4F40EC8
	UINT32                                                  reserved922;	//0xC4F40ECC
	UINT32                                                  reserved923;	//0xC4F40ED0
	UINT32                                                  reserved924;	//0xC4F40ED4
	UINT32                                                  reserved925;	//0xC4F40ED8
	UINT32                                                  reserved926;	//0xC4F40EDC
	UINT32                                                  reserved927;	//0xC4F40EE0
	UINT32                                                  reserved928;	//0xC4F40EE4
	UINT32                                                  reserved929;	//0xC4F40EE8
	UINT32                                                  reserved930;	//0xC4F40EEC
	UINT32                                                  reserved931;	//0xC4F40EF0
	UINT32                                                  reserved932;	//0xC4F40EF4
	UINT32                                                  reserved933;	//0xC4F40EF8
	UINT32                                                  reserved934;	//0xC4F40EFC
	UINT32                                                  reserved935;	//0xC4F40F00
	UINT32                                                  reserved936;	//0xC4F40F04
	UINT32                                                  reserved937;	//0xC4F40F08
	UINT32                                                  reserved938;	//0xC4F40F0C
	UINT32                                                  reserved939;	//0xC4F40F10
	UINT32                                                  reserved940;	//0xC4F40F14
	UINT32                                                  reserved941;	//0xC4F40F18
	UINT32                                                  reserved942;	//0xC4F40F1C
	UINT32                                                  reserved943;	//0xC4F40F20
	UINT32                                                  reserved944;	//0xC4F40F24
	UINT32                                                  reserved945;	//0xC4F40F28
	UINT32                                                  reserved946;	//0xC4F40F2C
	UINT32                                                  reserved947;	//0xC4F40F30
	UINT32                                                  reserved948;	//0xC4F40F34
	UINT32                                                  reserved949;	//0xC4F40F38
	UINT32                                                  reserved950;	//0xC4F40F3C
	UINT32                                                  reserved951;	//0xC4F40F40
	UINT32                                                  reserved952;	//0xC4F40F44
	UINT32                                                  reserved953;	//0xC4F40F48
	UINT32                                                  reserved954;	//0xC4F40F4C
	UINT32                                                  reserved955;	//0xC4F40F50
	UINT32                                                  reserved956;	//0xC4F40F54
	UINT32                                                  reserved957;	//0xC4F40F58
	UINT32                                                  reserved958;	//0xC4F40F5C
	UINT32                                                  reserved959;	//0xC4F40F60
	UINT32                                                  reserved960;	//0xC4F40F64
	UINT32                                                  reserved961;	//0xC4F40F68
	UINT32                                                  reserved962;	//0xC4F40F6C
	UINT32                                                  reserved963;	//0xC4F40F70
	UINT32                                                  reserved964;	//0xC4F40F74
	UINT32                                                  reserved965;	//0xC4F40F78
	UINT32                                                  reserved966;	//0xC4F40F7C
	UINT32                                                  reserved967;	//0xC4F40F80
	UINT32                                                  reserved968;	//0xC4F40F84
	UINT32                                                  reserved969;	//0xC4F40F88
	UINT32                                                  reserved970;	//0xC4F40F8C
	UINT32                                                  reserved971;	//0xC4F40F90
	UINT32                                                  reserved972;	//0xC4F40F94
	UINT32                                                  reserved973;	//0xC4F40F98
	UINT32                                                  reserved974;	//0xC4F40F9C
	UINT32                                                  reserved975;	//0xC4F40FA0
	UINT32                                                  reserved976;	//0xC4F40FA4
	UINT32                                                  reserved977;	//0xC4F40FA8
	UINT32                                                  reserved978;	//0xC4F40FAC
	UINT32                                                  reserved979;	//0xC4F40FB0
	UINT32                                                  reserved980;	//0xC4F40FB4
	UINT32                                                  reserved981;	//0xC4F40FB8
	UINT32                                                  reserved982;	//0xC4F40FBC
	UINT32                                                  reserved983;	//0xC4F40FC0
	UINT32                                                  reserved984;	//0xC4F40FC4
	UINT32                                                  reserved985;	//0xC4F40FC8
	UINT32                                                  reserved986;	//0xC4F40FCC
	UINT32                                                  reserved987;	//0xC4F40FD0
	UINT32                                                  reserved988;	//0xC4F40FD4
	UINT32                                                  reserved989;	//0xC4F40FD8
	UINT32                                                  reserved990;	//0xC4F40FDC
	UINT32                                                  reserved991;	//0xC4F40FE0
	UINT32                                                  reserved992;	//0xC4F40FE4
	UINT32                                                  reserved993;	//0xC4F40FE8
	UINT32                                                  reserved994;	//0xC4F40FEC
	UINT32                                                  reserved995;	//0xC4F40FF0
	UINT32                                                  reserved996;	//0xC4F40FF4
	UINT32                                                  reserved997;	//0xC4F40FF8
	UINT32                                                  reserved998;	//0xC4F40FFC
	REG_DDRC_M0_FIFO_RDY_T                                     fifo_rdy;	//0xC4F41000
	REG_DDRC_M0_FIFO_STATUS_T                               fifo_status;	//0xC4F41004
	REG_DDRC_M0_FIFO_CONF_T                                   fifo_conf;	//0xC4F41008
	UINT32                                                  reserved999;	//0xC4F4100C
	REG_DDRC_M0_LIMITER_EN_T                                 limiter_en;	//0xC4F41010
	REG_DDRC_M0_LIMITER_AW_THR_T                         limiter_aw_thr;	//0xC4F41014
	REG_DDRC_M0_LIMITER_W_THR_T                           limiter_w_thr;	//0xC4F41018
	UINT32                                                 reserved1000;	//0xC4F4101C
	UINT32                                                 reserved1001;	//0xC4F41020
	REG_DDRC_M0_LIMITER_AR_THR_T                         limiter_ar_thr;	//0xC4F41024
	REG_DDRC_M0_LIMITER_R_THR_T                           limiter_r_thr;	//0xC4F41028
	UINT32                                                 reserved1002;	//0xC4F4102C
	UINT32                                                 reserved1003;	//0xC4F41030
	UINT32                                                 reserved1004;	//0xC4F41034
	UINT32                                                 reserved1005;	//0xC4F41038
	UINT32                                                 reserved1006;	//0xC4F4103C
	UINT32                                                 reserved1007;	//0xC4F41040
	UINT32                                                 reserved1008;	//0xC4F41044
	UINT32                                                 reserved1009;	//0xC4F41048
	UINT32                                                 reserved1010;	//0xC4F4104C
	UINT32                                                 reserved1011;	//0xC4F41050
	UINT32                                                 reserved1012;	//0xC4F41054
	UINT32                                                 reserved1013;	//0xC4F41058
	UINT32                                                 reserved1014;	//0xC4F4105C
	UINT32                                                 reserved1015;	//0xC4F41060
	UINT32                                                 reserved1016;	//0xC4F41064
	UINT32                                                 reserved1017;	//0xC4F41068
	UINT32                                                 reserved1018;	//0xC4F4106C
	UINT32                                                 reserved1019;	//0xC4F41070
	UINT32                                                 reserved1020;	//0xC4F41074
	UINT32                                                 reserved1021;	//0xC4F41078
	UINT32                                                 reserved1022;	//0xC4F4107C
	UINT32                                                 reserved1023;	//0xC4F41080
	UINT32                                                 reserved1024;	//0xC4F41084
	UINT32                                                 reserved1025;	//0xC4F41088
	UINT32                                                 reserved1026;	//0xC4F4108C
	UINT32                                                 reserved1027;	//0xC4F41090
	UINT32                                                 reserved1028;	//0xC4F41094
	UINT32                                                 reserved1029;	//0xC4F41098
	UINT32                                                 reserved1030;	//0xC4F4109C
	UINT32                                                 reserved1031;	//0xC4F410A0
	UINT32                                                 reserved1032;	//0xC4F410A4
	UINT32                                                 reserved1033;	//0xC4F410A8
	UINT32                                                 reserved1034;	//0xC4F410AC
	UINT32                                                 reserved1035;	//0xC4F410B0
	UINT32                                                 reserved1036;	//0xC4F410B4
	UINT32                                                 reserved1037;	//0xC4F410B8
	UINT32                                                 reserved1038;	//0xC4F410BC
	UINT32                                                 reserved1039;	//0xC4F410C0
	UINT32                                                 reserved1040;	//0xC4F410C4
	UINT32                                                 reserved1041;	//0xC4F410C8
	UINT32                                                 reserved1042;	//0xC4F410CC
	UINT32                                                 reserved1043;	//0xC4F410D0
	UINT32                                                 reserved1044;	//0xC4F410D4
	UINT32                                                 reserved1045;	//0xC4F410D8
	UINT32                                                 reserved1046;	//0xC4F410DC
	UINT32                                                 reserved1047;	//0xC4F410E0
	UINT32                                                 reserved1048;	//0xC4F410E4
	UINT32                                                 reserved1049;	//0xC4F410E8
	UINT32                                                 reserved1050;	//0xC4F410EC
	UINT32                                                 reserved1051;	//0xC4F410F0
	UINT32                                                 reserved1052;	//0xC4F410F4
	UINT32                                                 reserved1053;	//0xC4F410F8
	UINT32                                                 reserved1054;	//0xC4F410FC
	REG_DDRC_M0_FIFO_MUX_T                                     fifo_mux;	//0xC4F41100
	REG_DDRC_M0_FIFO_MUX_MAX_T                             fifo_mux_max;	//0xC4F41104
	REG_DDRC_M0_FIFO_MUX_WR_PRT_T                       fifo_mux_wr_prt;	//0xC4F41108
	REG_DDRC_M0_FIFO_MUX_RD_PRT_T                       fifo_mux_rd_prt;	//0xC4F4110C
	REG_DDRC_M0_FIFO_MUX_PRT_MAX_T                     fifo_mux_prt_max;	//0xC4F41110
	UINT32                                                 reserved1055;	//0xC4F41114
	UINT32                                                 reserved1056;	//0xC4F41118
	UINT32                                                 reserved1057;	//0xC4F4111C
	UINT32                                                 reserved1058;	//0xC4F41120
	UINT32                                                 reserved1059;	//0xC4F41124
	UINT32                                                 reserved1060;	//0xC4F41128
	UINT32                                                 reserved1061;	//0xC4F4112C
	UINT32                                                 reserved1062;	//0xC4F41130
	UINT32                                                 reserved1063;	//0xC4F41134
	UINT32                                                 reserved1064;	//0xC4F41138
	UINT32                                                 reserved1065;	//0xC4F4113C
	UINT32                                                 reserved1066;	//0xC4F41140
	UINT32                                                 reserved1067;	//0xC4F41144
	UINT32                                                 reserved1068;	//0xC4F41148
	UINT32                                                 reserved1069;	//0xC4F4114C
	UINT32                                                 reserved1070;	//0xC4F41150
	UINT32                                                 reserved1071;	//0xC4F41154
	UINT32                                                 reserved1072;	//0xC4F41158
	UINT32                                                 reserved1073;	//0xC4F4115C
	UINT32                                                 reserved1074;	//0xC4F41160
	UINT32                                                 reserved1075;	//0xC4F41164
	UINT32                                                 reserved1076;	//0xC4F41168
	UINT32                                                 reserved1077;	//0xC4F4116C
	UINT32                                                 reserved1078;	//0xC4F41170
	UINT32                                                 reserved1079;	//0xC4F41174
	UINT32                                                 reserved1080;	//0xC4F41178
	UINT32                                                 reserved1081;	//0xC4F4117C
	UINT32                                                 reserved1082;	//0xC4F41180
	UINT32                                                 reserved1083;	//0xC4F41184
	UINT32                                                 reserved1084;	//0xC4F41188
	UINT32                                                 reserved1085;	//0xC4F4118C
	UINT32                                                 reserved1086;	//0xC4F41190
	UINT32                                                 reserved1087;	//0xC4F41194
	UINT32                                                 reserved1088;	//0xC4F41198
	UINT32                                                 reserved1089;	//0xC4F4119C
	UINT32                                                 reserved1090;	//0xC4F411A0
	UINT32                                                 reserved1091;	//0xC4F411A4
	UINT32                                                 reserved1092;	//0xC4F411A8
	UINT32                                                 reserved1093;	//0xC4F411AC
	UINT32                                                 reserved1094;	//0xC4F411B0
	UINT32                                                 reserved1095;	//0xC4F411B4
	UINT32                                                 reserved1096;	//0xC4F411B8
	UINT32                                                 reserved1097;	//0xC4F411BC
	UINT32                                                 reserved1098;	//0xC4F411C0
	UINT32                                                 reserved1099;	//0xC4F411C4
	UINT32                                                 reserved1100;	//0xC4F411C8
	UINT32                                                 reserved1101;	//0xC4F411CC
	UINT32                                                 reserved1102;	//0xC4F411D0
	UINT32                                                 reserved1103;	//0xC4F411D4
	UINT32                                                 reserved1104;	//0xC4F411D8
	UINT32                                                 reserved1105;	//0xC4F411DC
	UINT32                                                 reserved1106;	//0xC4F411E0
	UINT32                                                 reserved1107;	//0xC4F411E4
	UINT32                                                 reserved1108;	//0xC4F411E8
	UINT32                                                 reserved1109;	//0xC4F411EC
	UINT32                                                 reserved1110;	//0xC4F411F0
	UINT32                                                 reserved1111;	//0xC4F411F4
	UINT32                                                 reserved1112;	//0xC4F411F8
	UINT32                                                 reserved1113;	//0xC4F411FC
	UINT32                                                 reserved1114;	//0xC4F41200
	UINT32                                                 reserved1115;	//0xC4F41204
	UINT32                                                 reserved1116;	//0xC4F41208
	UINT32                                                 reserved1117;	//0xC4F4120C
	UINT32                                                 reserved1118;	//0xC4F41210
	UINT32                                                 reserved1119;	//0xC4F41214
	UINT32                                                 reserved1120;	//0xC4F41218
	UINT32                                                 reserved1121;	//0xC4F4121C
	UINT32                                                 reserved1122;	//0xC4F41220
	UINT32                                                 reserved1123;	//0xC4F41224
	UINT32                                                 reserved1124;	//0xC4F41228
	UINT32                                                 reserved1125;	//0xC4F4122C
	UINT32                                                 reserved1126;	//0xC4F41230
	UINT32                                                 reserved1127;	//0xC4F41234
	UINT32                                                 reserved1128;	//0xC4F41238
	UINT32                                                 reserved1129;	//0xC4F4123C
	UINT32                                                 reserved1130;	//0xC4F41240
	UINT32                                                 reserved1131;	//0xC4F41244
	UINT32                                                 reserved1132;	//0xC4F41248
	UINT32                                                 reserved1133;	//0xC4F4124C
	UINT32                                                 reserved1134;	//0xC4F41250
	UINT32                                                 reserved1135;	//0xC4F41254
	UINT32                                                 reserved1136;	//0xC4F41258
	UINT32                                                 reserved1137;	//0xC4F4125C
	UINT32                                                 reserved1138;	//0xC4F41260
	UINT32                                                 reserved1139;	//0xC4F41264
	UINT32                                                 reserved1140;	//0xC4F41268
	UINT32                                                 reserved1141;	//0xC4F4126C
	UINT32                                                 reserved1142;	//0xC4F41270
	UINT32                                                 reserved1143;	//0xC4F41274
	UINT32                                                 reserved1144;	//0xC4F41278
	UINT32                                                 reserved1145;	//0xC4F4127C
	UINT32                                                 reserved1146;	//0xC4F41280
	UINT32                                                 reserved1147;	//0xC4F41284
	UINT32                                                 reserved1148;	//0xC4F41288
	UINT32                                                 reserved1149;	//0xC4F4128C
	UINT32                                                 reserved1150;	//0xC4F41290
	UINT32                                                 reserved1151;	//0xC4F41294
	UINT32                                                 reserved1152;	//0xC4F41298
	UINT32                                                 reserved1153;	//0xC4F4129C
	UINT32                                                 reserved1154;	//0xC4F412A0
	UINT32                                                 reserved1155;	//0xC4F412A4
	UINT32                                                 reserved1156;	//0xC4F412A8
	UINT32                                                 reserved1157;	//0xC4F412AC
	UINT32                                                 reserved1158;	//0xC4F412B0
	UINT32                                                 reserved1159;	//0xC4F412B4
	UINT32                                                 reserved1160;	//0xC4F412B8
	UINT32                                                 reserved1161;	//0xC4F412BC
	UINT32                                                 reserved1162;	//0xC4F412C0
	UINT32                                                 reserved1163;	//0xC4F412C4
	UINT32                                                 reserved1164;	//0xC4F412C8
	UINT32                                                 reserved1165;	//0xC4F412CC
	UINT32                                                 reserved1166;	//0xC4F412D0
	UINT32                                                 reserved1167;	//0xC4F412D4
	UINT32                                                 reserved1168;	//0xC4F412D8
	UINT32                                                 reserved1169;	//0xC4F412DC
	UINT32                                                 reserved1170;	//0xC4F412E0
	UINT32                                                 reserved1171;	//0xC4F412E4
	UINT32                                                 reserved1172;	//0xC4F412E8
	UINT32                                                 reserved1173;	//0xC4F412EC
	UINT32                                                 reserved1174;	//0xC4F412F0
	UINT32                                                 reserved1175;	//0xC4F412F4
	UINT32                                                 reserved1176;	//0xC4F412F8
	UINT32                                                 reserved1177;	//0xC4F412FC
	UINT32                                                 reserved1178;	//0xC4F41300
	UINT32                                                 reserved1179;	//0xC4F41304
	UINT32                                                 reserved1180;	//0xC4F41308
	UINT32                                                 reserved1181;	//0xC4F4130C
	UINT32                                                 reserved1182;	//0xC4F41310
	UINT32                                                 reserved1183;	//0xC4F41314
	UINT32                                                 reserved1184;	//0xC4F41318
	UINT32                                                 reserved1185;	//0xC4F4131C
	UINT32                                                 reserved1186;	//0xC4F41320
	UINT32                                                 reserved1187;	//0xC4F41324
	UINT32                                                 reserved1188;	//0xC4F41328
	UINT32                                                 reserved1189;	//0xC4F4132C
	UINT32                                                 reserved1190;	//0xC4F41330
	UINT32                                                 reserved1191;	//0xC4F41334
	UINT32                                                 reserved1192;	//0xC4F41338
	UINT32                                                 reserved1193;	//0xC4F4133C
	UINT32                                                 reserved1194;	//0xC4F41340
	UINT32                                                 reserved1195;	//0xC4F41344
	UINT32                                                 reserved1196;	//0xC4F41348
	UINT32                                                 reserved1197;	//0xC4F4134C
	UINT32                                                 reserved1198;	//0xC4F41350
	UINT32                                                 reserved1199;	//0xC4F41354
	UINT32                                                 reserved1200;	//0xC4F41358
	UINT32                                                 reserved1201;	//0xC4F4135C
	UINT32                                                 reserved1202;	//0xC4F41360
	UINT32                                                 reserved1203;	//0xC4F41364
	UINT32                                                 reserved1204;	//0xC4F41368
	UINT32                                                 reserved1205;	//0xC4F4136C
	UINT32                                                 reserved1206;	//0xC4F41370
	UINT32                                                 reserved1207;	//0xC4F41374
	UINT32                                                 reserved1208;	//0xC4F41378
	UINT32                                                 reserved1209;	//0xC4F4137C
	UINT32                                                 reserved1210;	//0xC4F41380
	UINT32                                                 reserved1211;	//0xC4F41384
	UINT32                                                 reserved1212;	//0xC4F41388
	UINT32                                                 reserved1213;	//0xC4F4138C
	UINT32                                                 reserved1214;	//0xC4F41390
	UINT32                                                 reserved1215;	//0xC4F41394
	UINT32                                                 reserved1216;	//0xC4F41398
	UINT32                                                 reserved1217;	//0xC4F4139C
	UINT32                                                 reserved1218;	//0xC4F413A0
	UINT32                                                 reserved1219;	//0xC4F413A4
	UINT32                                                 reserved1220;	//0xC4F413A8
	UINT32                                                 reserved1221;	//0xC4F413AC
	UINT32                                                 reserved1222;	//0xC4F413B0
	UINT32                                                 reserved1223;	//0xC4F413B4
	UINT32                                                 reserved1224;	//0xC4F413B8
	UINT32                                                 reserved1225;	//0xC4F413BC
	UINT32                                                 reserved1226;	//0xC4F413C0
	UINT32                                                 reserved1227;	//0xC4F413C4
	UINT32                                                 reserved1228;	//0xC4F413C8
	UINT32                                                 reserved1229;	//0xC4F413CC
	UINT32                                                 reserved1230;	//0xC4F413D0
	UINT32                                                 reserved1231;	//0xC4F413D4
	UINT32                                                 reserved1232;	//0xC4F413D8
	UINT32                                                 reserved1233;	//0xC4F413DC
	UINT32                                                 reserved1234;	//0xC4F413E0
	UINT32                                                 reserved1235;	//0xC4F413E4
	UINT32                                                 reserved1236;	//0xC4F413E8
	UINT32                                                 reserved1237;	//0xC4F413EC
	UINT32                                                 reserved1238;	//0xC4F413F0
	UINT32                                                 reserved1239;	//0xC4F413F4
	UINT32                                                 reserved1240;	//0xC4F413F8
	UINT32                                                 reserved1241;	//0xC4F413FC
	UINT32                                                 reserved1242;	//0xC4F41400
	UINT32                                                 reserved1243;	//0xC4F41404
	UINT32                                                 reserved1244;	//0xC4F41408
	UINT32                                                 reserved1245;	//0xC4F4140C
	UINT32                                                 reserved1246;	//0xC4F41410
	UINT32                                                 reserved1247;	//0xC4F41414
	UINT32                                                 reserved1248;	//0xC4F41418
	UINT32                                                 reserved1249;	//0xC4F4141C
	UINT32                                                 reserved1250;	//0xC4F41420
	UINT32                                                 reserved1251;	//0xC4F41424
	UINT32                                                 reserved1252;	//0xC4F41428
	UINT32                                                 reserved1253;	//0xC4F4142C
	UINT32                                                 reserved1254;	//0xC4F41430
	UINT32                                                 reserved1255;	//0xC4F41434
	UINT32                                                 reserved1256;	//0xC4F41438
	UINT32                                                 reserved1257;	//0xC4F4143C
	UINT32                                                 reserved1258;	//0xC4F41440
	UINT32                                                 reserved1259;	//0xC4F41444
	UINT32                                                 reserved1260;	//0xC4F41448
	UINT32                                                 reserved1261;	//0xC4F4144C
	UINT32                                                 reserved1262;	//0xC4F41450
	UINT32                                                 reserved1263;	//0xC4F41454
	UINT32                                                 reserved1264;	//0xC4F41458
	UINT32                                                 reserved1265;	//0xC4F4145C
	UINT32                                                 reserved1266;	//0xC4F41460
	UINT32                                                 reserved1267;	//0xC4F41464
	UINT32                                                 reserved1268;	//0xC4F41468
	UINT32                                                 reserved1269;	//0xC4F4146C
	UINT32                                                 reserved1270;	//0xC4F41470
	UINT32                                                 reserved1271;	//0xC4F41474
	UINT32                                                 reserved1272;	//0xC4F41478
	UINT32                                                 reserved1273;	//0xC4F4147C
	UINT32                                                 reserved1274;	//0xC4F41480
	UINT32                                                 reserved1275;	//0xC4F41484
	UINT32                                                 reserved1276;	//0xC4F41488
	UINT32                                                 reserved1277;	//0xC4F4148C
	UINT32                                                 reserved1278;	//0xC4F41490
	UINT32                                                 reserved1279;	//0xC4F41494
	UINT32                                                 reserved1280;	//0xC4F41498
	UINT32                                                 reserved1281;	//0xC4F4149C
	UINT32                                                 reserved1282;	//0xC4F414A0
	UINT32                                                 reserved1283;	//0xC4F414A4
	UINT32                                                 reserved1284;	//0xC4F414A8
	UINT32                                                 reserved1285;	//0xC4F414AC
	UINT32                                                 reserved1286;	//0xC4F414B0
	UINT32                                                 reserved1287;	//0xC4F414B4
	UINT32                                                 reserved1288;	//0xC4F414B8
	UINT32                                                 reserved1289;	//0xC4F414BC
	UINT32                                                 reserved1290;	//0xC4F414C0
	UINT32                                                 reserved1291;	//0xC4F414C4
	UINT32                                                 reserved1292;	//0xC4F414C8
	UINT32                                                 reserved1293;	//0xC4F414CC
	UINT32                                                 reserved1294;	//0xC4F414D0
	UINT32                                                 reserved1295;	//0xC4F414D4
	UINT32                                                 reserved1296;	//0xC4F414D8
	UINT32                                                 reserved1297;	//0xC4F414DC
	UINT32                                                 reserved1298;	//0xC4F414E0
	UINT32                                                 reserved1299;	//0xC4F414E4
	UINT32                                                 reserved1300;	//0xC4F414E8
	UINT32                                                 reserved1301;	//0xC4F414EC
	UINT32                                                 reserved1302;	//0xC4F414F0
	UINT32                                                 reserved1303;	//0xC4F414F4
	UINT32                                                 reserved1304;	//0xC4F414F8
	UINT32                                                 reserved1305;	//0xC4F414FC
	UINT32                                                 reserved1306;	//0xC4F41500
	UINT32                                                 reserved1307;	//0xC4F41504
	UINT32                                                 reserved1308;	//0xC4F41508
	UINT32                                                 reserved1309;	//0xC4F4150C
	UINT32                                                 reserved1310;	//0xC4F41510
	UINT32                                                 reserved1311;	//0xC4F41514
	UINT32                                                 reserved1312;	//0xC4F41518
	UINT32                                                 reserved1313;	//0xC4F4151C
	UINT32                                                 reserved1314;	//0xC4F41520
	UINT32                                                 reserved1315;	//0xC4F41524
	UINT32                                                 reserved1316;	//0xC4F41528
	UINT32                                                 reserved1317;	//0xC4F4152C
	UINT32                                                 reserved1318;	//0xC4F41530
	UINT32                                                 reserved1319;	//0xC4F41534
	UINT32                                                 reserved1320;	//0xC4F41538
	UINT32                                                 reserved1321;	//0xC4F4153C
	UINT32                                                 reserved1322;	//0xC4F41540
	UINT32                                                 reserved1323;	//0xC4F41544
	UINT32                                                 reserved1324;	//0xC4F41548
	UINT32                                                 reserved1325;	//0xC4F4154C
	UINT32                                                 reserved1326;	//0xC4F41550
	UINT32                                                 reserved1327;	//0xC4F41554
	UINT32                                                 reserved1328;	//0xC4F41558
	UINT32                                                 reserved1329;	//0xC4F4155C
	UINT32                                                 reserved1330;	//0xC4F41560
	UINT32                                                 reserved1331;	//0xC4F41564
	UINT32                                                 reserved1332;	//0xC4F41568
	UINT32                                                 reserved1333;	//0xC4F4156C
	UINT32                                                 reserved1334;	//0xC4F41570
	UINT32                                                 reserved1335;	//0xC4F41574
	UINT32                                                 reserved1336;	//0xC4F41578
	UINT32                                                 reserved1337;	//0xC4F4157C
	UINT32                                                 reserved1338;	//0xC4F41580
	UINT32                                                 reserved1339;	//0xC4F41584
	UINT32                                                 reserved1340;	//0xC4F41588
	UINT32                                                 reserved1341;	//0xC4F4158C
	UINT32                                                 reserved1342;	//0xC4F41590
	UINT32                                                 reserved1343;	//0xC4F41594
	UINT32                                                 reserved1344;	//0xC4F41598
	UINT32                                                 reserved1345;	//0xC4F4159C
	UINT32                                                 reserved1346;	//0xC4F415A0
	UINT32                                                 reserved1347;	//0xC4F415A4
	UINT32                                                 reserved1348;	//0xC4F415A8
	UINT32                                                 reserved1349;	//0xC4F415AC
	UINT32                                                 reserved1350;	//0xC4F415B0
	UINT32                                                 reserved1351;	//0xC4F415B4
	UINT32                                                 reserved1352;	//0xC4F415B8
	UINT32                                                 reserved1353;	//0xC4F415BC
	UINT32                                                 reserved1354;	//0xC4F415C0
	UINT32                                                 reserved1355;	//0xC4F415C4
	UINT32                                                 reserved1356;	//0xC4F415C8
	UINT32                                                 reserved1357;	//0xC4F415CC
	UINT32                                                 reserved1358;	//0xC4F415D0
	UINT32                                                 reserved1359;	//0xC4F415D4
	UINT32                                                 reserved1360;	//0xC4F415D8
	UINT32                                                 reserved1361;	//0xC4F415DC
	UINT32                                                 reserved1362;	//0xC4F415E0
	UINT32                                                 reserved1363;	//0xC4F415E4
	UINT32                                                 reserved1364;	//0xC4F415E8
	UINT32                                                 reserved1365;	//0xC4F415EC
	UINT32                                                 reserved1366;	//0xC4F415F0
	UINT32                                                 reserved1367;	//0xC4F415F4
	UINT32                                                 reserved1368;	//0xC4F415F8
	UINT32                                                 reserved1369;	//0xC4F415FC
	UINT32                                                 reserved1370;	//0xC4F41600
	UINT32                                                 reserved1371;	//0xC4F41604
	UINT32                                                 reserved1372;	//0xC4F41608
	UINT32                                                 reserved1373;	//0xC4F4160C
	UINT32                                                 reserved1374;	//0xC4F41610
	UINT32                                                 reserved1375;	//0xC4F41614
	UINT32                                                 reserved1376;	//0xC4F41618
	UINT32                                                 reserved1377;	//0xC4F4161C
	UINT32                                                 reserved1378;	//0xC4F41620
	UINT32                                                 reserved1379;	//0xC4F41624
	UINT32                                                 reserved1380;	//0xC4F41628
	UINT32                                                 reserved1381;	//0xC4F4162C
	UINT32                                                 reserved1382;	//0xC4F41630
	UINT32                                                 reserved1383;	//0xC4F41634
	UINT32                                                 reserved1384;	//0xC4F41638
	UINT32                                                 reserved1385;	//0xC4F4163C
	UINT32                                                 reserved1386;	//0xC4F41640
	UINT32                                                 reserved1387;	//0xC4F41644
	UINT32                                                 reserved1388;	//0xC4F41648
	UINT32                                                 reserved1389;	//0xC4F4164C
	UINT32                                                 reserved1390;	//0xC4F41650
	UINT32                                                 reserved1391;	//0xC4F41654
	UINT32                                                 reserved1392;	//0xC4F41658
	UINT32                                                 reserved1393;	//0xC4F4165C
	UINT32                                                 reserved1394;	//0xC4F41660
	UINT32                                                 reserved1395;	//0xC4F41664
	UINT32                                                 reserved1396;	//0xC4F41668
	UINT32                                                 reserved1397;	//0xC4F4166C
	UINT32                                                 reserved1398;	//0xC4F41670
	UINT32                                                 reserved1399;	//0xC4F41674
	UINT32                                                 reserved1400;	//0xC4F41678
	UINT32                                                 reserved1401;	//0xC4F4167C
	UINT32                                                 reserved1402;	//0xC4F41680
	UINT32                                                 reserved1403;	//0xC4F41684
	UINT32                                                 reserved1404;	//0xC4F41688
	UINT32                                                 reserved1405;	//0xC4F4168C
	UINT32                                                 reserved1406;	//0xC4F41690
	UINT32                                                 reserved1407;	//0xC4F41694
	UINT32                                                 reserved1408;	//0xC4F41698
	UINT32                                                 reserved1409;	//0xC4F4169C
	UINT32                                                 reserved1410;	//0xC4F416A0
	UINT32                                                 reserved1411;	//0xC4F416A4
	UINT32                                                 reserved1412;	//0xC4F416A8
	UINT32                                                 reserved1413;	//0xC4F416AC
	UINT32                                                 reserved1414;	//0xC4F416B0
	UINT32                                                 reserved1415;	//0xC4F416B4
	UINT32                                                 reserved1416;	//0xC4F416B8
	UINT32                                                 reserved1417;	//0xC4F416BC
	UINT32                                                 reserved1418;	//0xC4F416C0
	UINT32                                                 reserved1419;	//0xC4F416C4
	UINT32                                                 reserved1420;	//0xC4F416C8
	UINT32                                                 reserved1421;	//0xC4F416CC
	UINT32                                                 reserved1422;	//0xC4F416D0
	UINT32                                                 reserved1423;	//0xC4F416D4
	UINT32                                                 reserved1424;	//0xC4F416D8
	UINT32                                                 reserved1425;	//0xC4F416DC
	UINT32                                                 reserved1426;	//0xC4F416E0
	UINT32                                                 reserved1427;	//0xC4F416E4
	UINT32                                                 reserved1428;	//0xC4F416E8
	UINT32                                                 reserved1429;	//0xC4F416EC
	UINT32                                                 reserved1430;	//0xC4F416F0
	UINT32                                                 reserved1431;	//0xC4F416F4
	UINT32                                                 reserved1432;	//0xC4F416F8
	UINT32                                                 reserved1433;	//0xC4F416FC
	UINT32                                                 reserved1434;	//0xC4F41700
	UINT32                                                 reserved1435;	//0xC4F41704
	UINT32                                                 reserved1436;	//0xC4F41708
	UINT32                                                 reserved1437;	//0xC4F4170C
	UINT32                                                 reserved1438;	//0xC4F41710
	UINT32                                                 reserved1439;	//0xC4F41714
	UINT32                                                 reserved1440;	//0xC4F41718
	UINT32                                                 reserved1441;	//0xC4F4171C
	UINT32                                                 reserved1442;	//0xC4F41720
	UINT32                                                 reserved1443;	//0xC4F41724
	UINT32                                                 reserved1444;	//0xC4F41728
	UINT32                                                 reserved1445;	//0xC4F4172C
	UINT32                                                 reserved1446;	//0xC4F41730
	UINT32                                                 reserved1447;	//0xC4F41734
	UINT32                                                 reserved1448;	//0xC4F41738
	UINT32                                                 reserved1449;	//0xC4F4173C
	UINT32                                                 reserved1450;	//0xC4F41740
	UINT32                                                 reserved1451;	//0xC4F41744
	UINT32                                                 reserved1452;	//0xC4F41748
	UINT32                                                 reserved1453;	//0xC4F4174C
	UINT32                                                 reserved1454;	//0xC4F41750
	UINT32                                                 reserved1455;	//0xC4F41754
	UINT32                                                 reserved1456;	//0xC4F41758
	UINT32                                                 reserved1457;	//0xC4F4175C
	UINT32                                                 reserved1458;	//0xC4F41760
	UINT32                                                 reserved1459;	//0xC4F41764
	UINT32                                                 reserved1460;	//0xC4F41768
	UINT32                                                 reserved1461;	//0xC4F4176C
	UINT32                                                 reserved1462;	//0xC4F41770
	UINT32                                                 reserved1463;	//0xC4F41774
	UINT32                                                 reserved1464;	//0xC4F41778
	UINT32                                                 reserved1465;	//0xC4F4177C
	UINT32                                                 reserved1466;	//0xC4F41780
	UINT32                                                 reserved1467;	//0xC4F41784
	UINT32                                                 reserved1468;	//0xC4F41788
	UINT32                                                 reserved1469;	//0xC4F4178C
	UINT32                                                 reserved1470;	//0xC4F41790
	UINT32                                                 reserved1471;	//0xC4F41794
	UINT32                                                 reserved1472;	//0xC4F41798
	UINT32                                                 reserved1473;	//0xC4F4179C
	UINT32                                                 reserved1474;	//0xC4F417A0
	UINT32                                                 reserved1475;	//0xC4F417A4
	UINT32                                                 reserved1476;	//0xC4F417A8
	UINT32                                                 reserved1477;	//0xC4F417AC
	UINT32                                                 reserved1478;	//0xC4F417B0
	UINT32                                                 reserved1479;	//0xC4F417B4
	UINT32                                                 reserved1480;	//0xC4F417B8
	UINT32                                                 reserved1481;	//0xC4F417BC
	UINT32                                                 reserved1482;	//0xC4F417C0
	UINT32                                                 reserved1483;	//0xC4F417C4
	UINT32                                                 reserved1484;	//0xC4F417C8
	UINT32                                                 reserved1485;	//0xC4F417CC
	UINT32                                                 reserved1486;	//0xC4F417D0
	UINT32                                                 reserved1487;	//0xC4F417D4
	UINT32                                                 reserved1488;	//0xC4F417D8
	UINT32                                                 reserved1489;	//0xC4F417DC
	UINT32                                                 reserved1490;	//0xC4F417E0
	UINT32                                                 reserved1491;	//0xC4F417E4
	UINT32                                                 reserved1492;	//0xC4F417E8
	UINT32                                                 reserved1493;	//0xC4F417EC
	UINT32                                                 reserved1494;	//0xC4F417F0
	UINT32                                                 reserved1495;	//0xC4F417F4
	UINT32                                                 reserved1496;	//0xC4F417F8
	UINT32                                                 reserved1497;	//0xC4F417FC
	UINT32                                                 reserved1498;	//0xC4F41800
	UINT32                                                 reserved1499;	//0xC4F41804
	UINT32                                                 reserved1500;	//0xC4F41808
	UINT32                                                 reserved1501;	//0xC4F4180C
	UINT32                                                 reserved1502;	//0xC4F41810
	UINT32                                                 reserved1503;	//0xC4F41814
	UINT32                                                 reserved1504;	//0xC4F41818
	UINT32                                                 reserved1505;	//0xC4F4181C
	UINT32                                                 reserved1506;	//0xC4F41820
	UINT32                                                 reserved1507;	//0xC4F41824
	UINT32                                                 reserved1508;	//0xC4F41828
	UINT32                                                 reserved1509;	//0xC4F4182C
	UINT32                                                 reserved1510;	//0xC4F41830
	UINT32                                                 reserved1511;	//0xC4F41834
	UINT32                                                 reserved1512;	//0xC4F41838
	UINT32                                                 reserved1513;	//0xC4F4183C
	UINT32                                                 reserved1514;	//0xC4F41840
	UINT32                                                 reserved1515;	//0xC4F41844
	UINT32                                                 reserved1516;	//0xC4F41848
	UINT32                                                 reserved1517;	//0xC4F4184C
	UINT32                                                 reserved1518;	//0xC4F41850
	UINT32                                                 reserved1519;	//0xC4F41854
	UINT32                                                 reserved1520;	//0xC4F41858
	UINT32                                                 reserved1521;	//0xC4F4185C
	UINT32                                                 reserved1522;	//0xC4F41860
	UINT32                                                 reserved1523;	//0xC4F41864
	UINT32                                                 reserved1524;	//0xC4F41868
	UINT32                                                 reserved1525;	//0xC4F4186C
	UINT32                                                 reserved1526;	//0xC4F41870
	UINT32                                                 reserved1527;	//0xC4F41874
	UINT32                                                 reserved1528;	//0xC4F41878
	UINT32                                                 reserved1529;	//0xC4F4187C
	UINT32                                                 reserved1530;	//0xC4F41880
	UINT32                                                 reserved1531;	//0xC4F41884
	UINT32                                                 reserved1532;	//0xC4F41888
	UINT32                                                 reserved1533;	//0xC4F4188C
	UINT32                                                 reserved1534;	//0xC4F41890
	UINT32                                                 reserved1535;	//0xC4F41894
	UINT32                                                 reserved1536;	//0xC4F41898
	UINT32                                                 reserved1537;	//0xC4F4189C
	UINT32                                                 reserved1538;	//0xC4F418A0
	UINT32                                                 reserved1539;	//0xC4F418A4
	UINT32                                                 reserved1540;	//0xC4F418A8
	UINT32                                                 reserved1541;	//0xC4F418AC
	UINT32                                                 reserved1542;	//0xC4F418B0
	UINT32                                                 reserved1543;	//0xC4F418B4
	UINT32                                                 reserved1544;	//0xC4F418B8
	UINT32                                                 reserved1545;	//0xC4F418BC
	UINT32                                                 reserved1546;	//0xC4F418C0
	UINT32                                                 reserved1547;	//0xC4F418C4
	UINT32                                                 reserved1548;	//0xC4F418C8
	UINT32                                                 reserved1549;	//0xC4F418CC
	UINT32                                                 reserved1550;	//0xC4F418D0
	UINT32                                                 reserved1551;	//0xC4F418D4
	UINT32                                                 reserved1552;	//0xC4F418D8
	UINT32                                                 reserved1553;	//0xC4F418DC
	UINT32                                                 reserved1554;	//0xC4F418E0
	UINT32                                                 reserved1555;	//0xC4F418E4
	UINT32                                                 reserved1556;	//0xC4F418E8
	UINT32                                                 reserved1557;	//0xC4F418EC
	UINT32                                                 reserved1558;	//0xC4F418F0
	UINT32                                                 reserved1559;	//0xC4F418F4
	UINT32                                                 reserved1560;	//0xC4F418F8
	UINT32                                                 reserved1561;	//0xC4F418FC
	UINT32                                                 reserved1562;	//0xC4F41900
	UINT32                                                 reserved1563;	//0xC4F41904
	UINT32                                                 reserved1564;	//0xC4F41908
	UINT32                                                 reserved1565;	//0xC4F4190C
	UINT32                                                 reserved1566;	//0xC4F41910
	UINT32                                                 reserved1567;	//0xC4F41914
	UINT32                                                 reserved1568;	//0xC4F41918
	UINT32                                                 reserved1569;	//0xC4F4191C
	UINT32                                                 reserved1570;	//0xC4F41920
	UINT32                                                 reserved1571;	//0xC4F41924
	UINT32                                                 reserved1572;	//0xC4F41928
	UINT32                                                 reserved1573;	//0xC4F4192C
	UINT32                                                 reserved1574;	//0xC4F41930
	UINT32                                                 reserved1575;	//0xC4F41934
	UINT32                                                 reserved1576;	//0xC4F41938
	UINT32                                                 reserved1577;	//0xC4F4193C
	UINT32                                                 reserved1578;	//0xC4F41940
	UINT32                                                 reserved1579;	//0xC4F41944
	UINT32                                                 reserved1580;	//0xC4F41948
	UINT32                                                 reserved1581;	//0xC4F4194C
	UINT32                                                 reserved1582;	//0xC4F41950
	UINT32                                                 reserved1583;	//0xC4F41954
	UINT32                                                 reserved1584;	//0xC4F41958
	UINT32                                                 reserved1585;	//0xC4F4195C
	UINT32                                                 reserved1586;	//0xC4F41960
	UINT32                                                 reserved1587;	//0xC4F41964
	UINT32                                                 reserved1588;	//0xC4F41968
	UINT32                                                 reserved1589;	//0xC4F4196C
	UINT32                                                 reserved1590;	//0xC4F41970
	UINT32                                                 reserved1591;	//0xC4F41974
	UINT32                                                 reserved1592;	//0xC4F41978
	UINT32                                                 reserved1593;	//0xC4F4197C
	UINT32                                                 reserved1594;	//0xC4F41980
	UINT32                                                 reserved1595;	//0xC4F41984
	UINT32                                                 reserved1596;	//0xC4F41988
	UINT32                                                 reserved1597;	//0xC4F4198C
	UINT32                                                 reserved1598;	//0xC4F41990
	UINT32                                                 reserved1599;	//0xC4F41994
	UINT32                                                 reserved1600;	//0xC4F41998
	UINT32                                                 reserved1601;	//0xC4F4199C
	UINT32                                                 reserved1602;	//0xC4F419A0
	UINT32                                                 reserved1603;	//0xC4F419A4
	UINT32                                                 reserved1604;	//0xC4F419A8
	UINT32                                                 reserved1605;	//0xC4F419AC
	UINT32                                                 reserved1606;	//0xC4F419B0
	UINT32                                                 reserved1607;	//0xC4F419B4
	UINT32                                                 reserved1608;	//0xC4F419B8
	UINT32                                                 reserved1609;	//0xC4F419BC
	UINT32                                                 reserved1610;	//0xC4F419C0
	UINT32                                                 reserved1611;	//0xC4F419C4
	UINT32                                                 reserved1612;	//0xC4F419C8
	UINT32                                                 reserved1613;	//0xC4F419CC
	UINT32                                                 reserved1614;	//0xC4F419D0
	UINT32                                                 reserved1615;	//0xC4F419D4
	UINT32                                                 reserved1616;	//0xC4F419D8
	UINT32                                                 reserved1617;	//0xC4F419DC
	UINT32                                                 reserved1618;	//0xC4F419E0
	UINT32                                                 reserved1619;	//0xC4F419E4
	UINT32                                                 reserved1620;	//0xC4F419E8
	UINT32                                                 reserved1621;	//0xC4F419EC
	UINT32                                                 reserved1622;	//0xC4F419F0
	UINT32                                                 reserved1623;	//0xC4F419F4
	UINT32                                                 reserved1624;	//0xC4F419F8
	UINT32                                                 reserved1625;	//0xC4F419FC
	UINT32                                                 reserved1626;	//0xC4F41A00
	UINT32                                                 reserved1627;	//0xC4F41A04
	UINT32                                                 reserved1628;	//0xC4F41A08
	UINT32                                                 reserved1629;	//0xC4F41A0C
	UINT32                                                 reserved1630;	//0xC4F41A10
	UINT32                                                 reserved1631;	//0xC4F41A14
	UINT32                                                 reserved1632;	//0xC4F41A18
	UINT32                                                 reserved1633;	//0xC4F41A1C
	UINT32                                                 reserved1634;	//0xC4F41A20
	UINT32                                                 reserved1635;	//0xC4F41A24
	UINT32                                                 reserved1636;	//0xC4F41A28
	UINT32                                                 reserved1637;	//0xC4F41A2C
	UINT32                                                 reserved1638;	//0xC4F41A30
	UINT32                                                 reserved1639;	//0xC4F41A34
	UINT32                                                 reserved1640;	//0xC4F41A38
	UINT32                                                 reserved1641;	//0xC4F41A3C
	UINT32                                                 reserved1642;	//0xC4F41A40
	UINT32                                                 reserved1643;	//0xC4F41A44
	UINT32                                                 reserved1644;	//0xC4F41A48
	UINT32                                                 reserved1645;	//0xC4F41A4C
	UINT32                                                 reserved1646;	//0xC4F41A50
	UINT32                                                 reserved1647;	//0xC4F41A54
	UINT32                                                 reserved1648;	//0xC4F41A58
	UINT32                                                 reserved1649;	//0xC4F41A5C
	UINT32                                                 reserved1650;	//0xC4F41A60
	UINT32                                                 reserved1651;	//0xC4F41A64
	UINT32                                                 reserved1652;	//0xC4F41A68
	UINT32                                                 reserved1653;	//0xC4F41A6C
	UINT32                                                 reserved1654;	//0xC4F41A70
	UINT32                                                 reserved1655;	//0xC4F41A74
	UINT32                                                 reserved1656;	//0xC4F41A78
	UINT32                                                 reserved1657;	//0xC4F41A7C
	UINT32                                                 reserved1658;	//0xC4F41A80
	UINT32                                                 reserved1659;	//0xC4F41A84
	UINT32                                                 reserved1660;	//0xC4F41A88
	UINT32                                                 reserved1661;	//0xC4F41A8C
	UINT32                                                 reserved1662;	//0xC4F41A90
	UINT32                                                 reserved1663;	//0xC4F41A94
	UINT32                                                 reserved1664;	//0xC4F41A98
	UINT32                                                 reserved1665;	//0xC4F41A9C
	UINT32                                                 reserved1666;	//0xC4F41AA0
	UINT32                                                 reserved1667;	//0xC4F41AA4
	UINT32                                                 reserved1668;	//0xC4F41AA8
	UINT32                                                 reserved1669;	//0xC4F41AAC
	UINT32                                                 reserved1670;	//0xC4F41AB0
	UINT32                                                 reserved1671;	//0xC4F41AB4
	UINT32                                                 reserved1672;	//0xC4F41AB8
	UINT32                                                 reserved1673;	//0xC4F41ABC
	UINT32                                                 reserved1674;	//0xC4F41AC0
	UINT32                                                 reserved1675;	//0xC4F41AC4
	UINT32                                                 reserved1676;	//0xC4F41AC8
	UINT32                                                 reserved1677;	//0xC4F41ACC
	UINT32                                                 reserved1678;	//0xC4F41AD0
	UINT32                                                 reserved1679;	//0xC4F41AD4
	UINT32                                                 reserved1680;	//0xC4F41AD8
	UINT32                                                 reserved1681;	//0xC4F41ADC
	UINT32                                                 reserved1682;	//0xC4F41AE0
	UINT32                                                 reserved1683;	//0xC4F41AE4
	UINT32                                                 reserved1684;	//0xC4F41AE8
	UINT32                                                 reserved1685;	//0xC4F41AEC
	UINT32                                                 reserved1686;	//0xC4F41AF0
	UINT32                                                 reserved1687;	//0xC4F41AF4
	UINT32                                                 reserved1688;	//0xC4F41AF8
	UINT32                                                 reserved1689;	//0xC4F41AFC
	UINT32                                                 reserved1690;	//0xC4F41B00
	UINT32                                                 reserved1691;	//0xC4F41B04
	UINT32                                                 reserved1692;	//0xC4F41B08
	UINT32                                                 reserved1693;	//0xC4F41B0C
	UINT32                                                 reserved1694;	//0xC4F41B10
	UINT32                                                 reserved1695;	//0xC4F41B14
	UINT32                                                 reserved1696;	//0xC4F41B18
	UINT32                                                 reserved1697;	//0xC4F41B1C
	UINT32                                                 reserved1698;	//0xC4F41B20
	UINT32                                                 reserved1699;	//0xC4F41B24
	UINT32                                                 reserved1700;	//0xC4F41B28
	UINT32                                                 reserved1701;	//0xC4F41B2C
	UINT32                                                 reserved1702;	//0xC4F41B30
	UINT32                                                 reserved1703;	//0xC4F41B34
	UINT32                                                 reserved1704;	//0xC4F41B38
	UINT32                                                 reserved1705;	//0xC4F41B3C
	UINT32                                                 reserved1706;	//0xC4F41B40
	UINT32                                                 reserved1707;	//0xC4F41B44
	UINT32                                                 reserved1708;	//0xC4F41B48
	UINT32                                                 reserved1709;	//0xC4F41B4C
	UINT32                                                 reserved1710;	//0xC4F41B50
	UINT32                                                 reserved1711;	//0xC4F41B54
	UINT32                                                 reserved1712;	//0xC4F41B58
	UINT32                                                 reserved1713;	//0xC4F41B5C
	UINT32                                                 reserved1714;	//0xC4F41B60
	UINT32                                                 reserved1715;	//0xC4F41B64
	UINT32                                                 reserved1716;	//0xC4F41B68
	UINT32                                                 reserved1717;	//0xC4F41B6C
	UINT32                                                 reserved1718;	//0xC4F41B70
	UINT32                                                 reserved1719;	//0xC4F41B74
	UINT32                                                 reserved1720;	//0xC4F41B78
	UINT32                                                 reserved1721;	//0xC4F41B7C
	UINT32                                                 reserved1722;	//0xC4F41B80
	UINT32                                                 reserved1723;	//0xC4F41B84
	UINT32                                                 reserved1724;	//0xC4F41B88
	UINT32                                                 reserved1725;	//0xC4F41B8C
	UINT32                                                 reserved1726;	//0xC4F41B90
	UINT32                                                 reserved1727;	//0xC4F41B94
	UINT32                                                 reserved1728;	//0xC4F41B98
	UINT32                                                 reserved1729;	//0xC4F41B9C
	UINT32                                                 reserved1730;	//0xC4F41BA0
	UINT32                                                 reserved1731;	//0xC4F41BA4
	UINT32                                                 reserved1732;	//0xC4F41BA8
	UINT32                                                 reserved1733;	//0xC4F41BAC
	UINT32                                                 reserved1734;	//0xC4F41BB0
	UINT32                                                 reserved1735;	//0xC4F41BB4
	UINT32                                                 reserved1736;	//0xC4F41BB8
	UINT32                                                 reserved1737;	//0xC4F41BBC
	UINT32                                                 reserved1738;	//0xC4F41BC0
	UINT32                                                 reserved1739;	//0xC4F41BC4
	UINT32                                                 reserved1740;	//0xC4F41BC8
	UINT32                                                 reserved1741;	//0xC4F41BCC
	UINT32                                                 reserved1742;	//0xC4F41BD0
	UINT32                                                 reserved1743;	//0xC4F41BD4
	UINT32                                                 reserved1744;	//0xC4F41BD8
	UINT32                                                 reserved1745;	//0xC4F41BDC
	UINT32                                                 reserved1746;	//0xC4F41BE0
	UINT32                                                 reserved1747;	//0xC4F41BE4
	UINT32                                                 reserved1748;	//0xC4F41BE8
	UINT32                                                 reserved1749;	//0xC4F41BEC
	UINT32                                                 reserved1750;	//0xC4F41BF0
	UINT32                                                 reserved1751;	//0xC4F41BF4
	UINT32                                                 reserved1752;	//0xC4F41BF8
	UINT32                                                 reserved1753;	//0xC4F41BFC
	UINT32                                                 reserved1754;	//0xC4F41C00
	UINT32                                                 reserved1755;	//0xC4F41C04
	UINT32                                                 reserved1756;	//0xC4F41C08
	UINT32                                                 reserved1757;	//0xC4F41C0C
	UINT32                                                 reserved1758;	//0xC4F41C10
	UINT32                                                 reserved1759;	//0xC4F41C14
	UINT32                                                 reserved1760;	//0xC4F41C18
	UINT32                                                 reserved1761;	//0xC4F41C1C
	UINT32                                                 reserved1762;	//0xC4F41C20
	UINT32                                                 reserved1763;	//0xC4F41C24
	UINT32                                                 reserved1764;	//0xC4F41C28
	UINT32                                                 reserved1765;	//0xC4F41C2C
	UINT32                                                 reserved1766;	//0xC4F41C30
	UINT32                                                 reserved1767;	//0xC4F41C34
	UINT32                                                 reserved1768;	//0xC4F41C38
	UINT32                                                 reserved1769;	//0xC4F41C3C
	UINT32                                                 reserved1770;	//0xC4F41C40
	UINT32                                                 reserved1771;	//0xC4F41C44
	UINT32                                                 reserved1772;	//0xC4F41C48
	UINT32                                                 reserved1773;	//0xC4F41C4C
	UINT32                                                 reserved1774;	//0xC4F41C50
	UINT32                                                 reserved1775;	//0xC4F41C54
	UINT32                                                 reserved1776;	//0xC4F41C58
	UINT32                                                 reserved1777;	//0xC4F41C5C
	UINT32                                                 reserved1778;	//0xC4F41C60
	UINT32                                                 reserved1779;	//0xC4F41C64
	UINT32                                                 reserved1780;	//0xC4F41C68
	UINT32                                                 reserved1781;	//0xC4F41C6C
	UINT32                                                 reserved1782;	//0xC4F41C70
	UINT32                                                 reserved1783;	//0xC4F41C74
	UINT32                                                 reserved1784;	//0xC4F41C78
	UINT32                                                 reserved1785;	//0xC4F41C7C
	UINT32                                                 reserved1786;	//0xC4F41C80
	UINT32                                                 reserved1787;	//0xC4F41C84
	UINT32                                                 reserved1788;	//0xC4F41C88
	UINT32                                                 reserved1789;	//0xC4F41C8C
	UINT32                                                 reserved1790;	//0xC4F41C90
	UINT32                                                 reserved1791;	//0xC4F41C94
	UINT32                                                 reserved1792;	//0xC4F41C98
	UINT32                                                 reserved1793;	//0xC4F41C9C
	UINT32                                                 reserved1794;	//0xC4F41CA0
	UINT32                                                 reserved1795;	//0xC4F41CA4
	UINT32                                                 reserved1796;	//0xC4F41CA8
	UINT32                                                 reserved1797;	//0xC4F41CAC
	UINT32                                                 reserved1798;	//0xC4F41CB0
	UINT32                                                 reserved1799;	//0xC4F41CB4
	UINT32                                                 reserved1800;	//0xC4F41CB8
	UINT32                                                 reserved1801;	//0xC4F41CBC
	UINT32                                                 reserved1802;	//0xC4F41CC0
	UINT32                                                 reserved1803;	//0xC4F41CC4
	UINT32                                                 reserved1804;	//0xC4F41CC8
	UINT32                                                 reserved1805;	//0xC4F41CCC
	UINT32                                                 reserved1806;	//0xC4F41CD0
	UINT32                                                 reserved1807;	//0xC4F41CD4
	UINT32                                                 reserved1808;	//0xC4F41CD8
	UINT32                                                 reserved1809;	//0xC4F41CDC
	UINT32                                                 reserved1810;	//0xC4F41CE0
	UINT32                                                 reserved1811;	//0xC4F41CE4
	UINT32                                                 reserved1812;	//0xC4F41CE8
	UINT32                                                 reserved1813;	//0xC4F41CEC
	UINT32                                                 reserved1814;	//0xC4F41CF0
	UINT32                                                 reserved1815;	//0xC4F41CF4
	UINT32                                                 reserved1816;	//0xC4F41CF8
	UINT32                                                 reserved1817;	//0xC4F41CFC
	UINT32                                                 reserved1818;	//0xC4F41D00
	UINT32                                                 reserved1819;	//0xC4F41D04
	UINT32                                                 reserved1820;	//0xC4F41D08
	UINT32                                                 reserved1821;	//0xC4F41D0C
	UINT32                                                 reserved1822;	//0xC4F41D10
	UINT32                                                 reserved1823;	//0xC4F41D14
	UINT32                                                 reserved1824;	//0xC4F41D18
	UINT32                                                 reserved1825;	//0xC4F41D1C
	UINT32                                                 reserved1826;	//0xC4F41D20
	UINT32                                                 reserved1827;	//0xC4F41D24
	UINT32                                                 reserved1828;	//0xC4F41D28
	UINT32                                                 reserved1829;	//0xC4F41D2C
	UINT32                                                 reserved1830;	//0xC4F41D30
	UINT32                                                 reserved1831;	//0xC4F41D34
	UINT32                                                 reserved1832;	//0xC4F41D38
	UINT32                                                 reserved1833;	//0xC4F41D3C
	UINT32                                                 reserved1834;	//0xC4F41D40
	UINT32                                                 reserved1835;	//0xC4F41D44
	UINT32                                                 reserved1836;	//0xC4F41D48
	UINT32                                                 reserved1837;	//0xC4F41D4C
	UINT32                                                 reserved1838;	//0xC4F41D50
	UINT32                                                 reserved1839;	//0xC4F41D54
	UINT32                                                 reserved1840;	//0xC4F41D58
	UINT32                                                 reserved1841;	//0xC4F41D5C
	UINT32                                                 reserved1842;	//0xC4F41D60
	UINT32                                                 reserved1843;	//0xC4F41D64
	UINT32                                                 reserved1844;	//0xC4F41D68
	UINT32                                                 reserved1845;	//0xC4F41D6C
	UINT32                                                 reserved1846;	//0xC4F41D70
	UINT32                                                 reserved1847;	//0xC4F41D74
	UINT32                                                 reserved1848;	//0xC4F41D78
	UINT32                                                 reserved1849;	//0xC4F41D7C
	UINT32                                                 reserved1850;	//0xC4F41D80
	UINT32                                                 reserved1851;	//0xC4F41D84
	UINT32                                                 reserved1852;	//0xC4F41D88
	UINT32                                                 reserved1853;	//0xC4F41D8C
	UINT32                                                 reserved1854;	//0xC4F41D90
	UINT32                                                 reserved1855;	//0xC4F41D94
	UINT32                                                 reserved1856;	//0xC4F41D98
	UINT32                                                 reserved1857;	//0xC4F41D9C
	UINT32                                                 reserved1858;	//0xC4F41DA0
	UINT32                                                 reserved1859;	//0xC4F41DA4
	UINT32                                                 reserved1860;	//0xC4F41DA8
	UINT32                                                 reserved1861;	//0xC4F41DAC
	UINT32                                                 reserved1862;	//0xC4F41DB0
	UINT32                                                 reserved1863;	//0xC4F41DB4
	UINT32                                                 reserved1864;	//0xC4F41DB8
	UINT32                                                 reserved1865;	//0xC4F41DBC
	UINT32                                                 reserved1866;	//0xC4F41DC0
	UINT32                                                 reserved1867;	//0xC4F41DC4
	UINT32                                                 reserved1868;	//0xC4F41DC8
	UINT32                                                 reserved1869;	//0xC4F41DCC
	UINT32                                                 reserved1870;	//0xC4F41DD0
	UINT32                                                 reserved1871;	//0xC4F41DD4
	UINT32                                                 reserved1872;	//0xC4F41DD8
	UINT32                                                 reserved1873;	//0xC4F41DDC
	UINT32                                                 reserved1874;	//0xC4F41DE0
	UINT32                                                 reserved1875;	//0xC4F41DE4
	UINT32                                                 reserved1876;	//0xC4F41DE8
	UINT32                                                 reserved1877;	//0xC4F41DEC
	UINT32                                                 reserved1878;	//0xC4F41DF0
	UINT32                                                 reserved1879;	//0xC4F41DF4
	UINT32                                                 reserved1880;	//0xC4F41DF8
	UINT32                                                 reserved1881;	//0xC4F41DFC
	UINT32                                                 reserved1882;	//0xC4F41E00
	UINT32                                                 reserved1883;	//0xC4F41E04
	UINT32                                                 reserved1884;	//0xC4F41E08
	UINT32                                                 reserved1885;	//0xC4F41E0C
	UINT32                                                 reserved1886;	//0xC4F41E10
	UINT32                                                 reserved1887;	//0xC4F41E14
	UINT32                                                 reserved1888;	//0xC4F41E18
	UINT32                                                 reserved1889;	//0xC4F41E1C
	UINT32                                                 reserved1890;	//0xC4F41E20
	UINT32                                                 reserved1891;	//0xC4F41E24
	UINT32                                                 reserved1892;	//0xC4F41E28
	UINT32                                                 reserved1893;	//0xC4F41E2C
	UINT32                                                 reserved1894;	//0xC4F41E30
	UINT32                                                 reserved1895;	//0xC4F41E34
	UINT32                                                 reserved1896;	//0xC4F41E38
	UINT32                                                 reserved1897;	//0xC4F41E3C
	UINT32                                                 reserved1898;	//0xC4F41E40
	UINT32                                                 reserved1899;	//0xC4F41E44
	UINT32                                                 reserved1900;	//0xC4F41E48
	UINT32                                                 reserved1901;	//0xC4F41E4C
	UINT32                                                 reserved1902;	//0xC4F41E50
	UINT32                                                 reserved1903;	//0xC4F41E54
	UINT32                                                 reserved1904;	//0xC4F41E58
	UINT32                                                 reserved1905;	//0xC4F41E5C
	UINT32                                                 reserved1906;	//0xC4F41E60
	UINT32                                                 reserved1907;	//0xC4F41E64
	UINT32                                                 reserved1908;	//0xC4F41E68
	UINT32                                                 reserved1909;	//0xC4F41E6C
	UINT32                                                 reserved1910;	//0xC4F41E70
	UINT32                                                 reserved1911;	//0xC4F41E74
	UINT32                                                 reserved1912;	//0xC4F41E78
	UINT32                                                 reserved1913;	//0xC4F41E7C
	UINT32                                                 reserved1914;	//0xC4F41E80
	UINT32                                                 reserved1915;	//0xC4F41E84
	UINT32                                                 reserved1916;	//0xC4F41E88
	UINT32                                                 reserved1917;	//0xC4F41E8C
	UINT32                                                 reserved1918;	//0xC4F41E90
	UINT32                                                 reserved1919;	//0xC4F41E94
	UINT32                                                 reserved1920;	//0xC4F41E98
	UINT32                                                 reserved1921;	//0xC4F41E9C
	UINT32                                                 reserved1922;	//0xC4F41EA0
	UINT32                                                 reserved1923;	//0xC4F41EA4
	UINT32                                                 reserved1924;	//0xC4F41EA8
	UINT32                                                 reserved1925;	//0xC4F41EAC
	UINT32                                                 reserved1926;	//0xC4F41EB0
	UINT32                                                 reserved1927;	//0xC4F41EB4
	UINT32                                                 reserved1928;	//0xC4F41EB8
	UINT32                                                 reserved1929;	//0xC4F41EBC
	UINT32                                                 reserved1930;	//0xC4F41EC0
	UINT32                                                 reserved1931;	//0xC4F41EC4
	UINT32                                                 reserved1932;	//0xC4F41EC8
	UINT32                                                 reserved1933;	//0xC4F41ECC
	UINT32                                                 reserved1934;	//0xC4F41ED0
	UINT32                                                 reserved1935;	//0xC4F41ED4
	UINT32                                                 reserved1936;	//0xC4F41ED8
	UINT32                                                 reserved1937;	//0xC4F41EDC
	UINT32                                                 reserved1938;	//0xC4F41EE0
	UINT32                                                 reserved1939;	//0xC4F41EE4
	UINT32                                                 reserved1940;	//0xC4F41EE8
	UINT32                                                 reserved1941;	//0xC4F41EEC
	UINT32                                                 reserved1942;	//0xC4F41EF0
	UINT32                                                 reserved1943;	//0xC4F41EF4
	UINT32                                                 reserved1944;	//0xC4F41EF8
	UINT32                                                 reserved1945;	//0xC4F41EFC
	UINT32                                                 reserved1946;	//0xC4F41F00
	UINT32                                                 reserved1947;	//0xC4F41F04
	UINT32                                                 reserved1948;	//0xC4F41F08
	UINT32                                                 reserved1949;	//0xC4F41F0C
	UINT32                                                 reserved1950;	//0xC4F41F10
	UINT32                                                 reserved1951;	//0xC4F41F14
	UINT32                                                 reserved1952;	//0xC4F41F18
	UINT32                                                 reserved1953;	//0xC4F41F1C
	UINT32                                                 reserved1954;	//0xC4F41F20
	UINT32                                                 reserved1955;	//0xC4F41F24
	UINT32                                                 reserved1956;	//0xC4F41F28
	UINT32                                                 reserved1957;	//0xC4F41F2C
	UINT32                                                 reserved1958;	//0xC4F41F30
	UINT32                                                 reserved1959;	//0xC4F41F34
	UINT32                                                 reserved1960;	//0xC4F41F38
	UINT32                                                 reserved1961;	//0xC4F41F3C
	UINT32                                                 reserved1962;	//0xC4F41F40
	UINT32                                                 reserved1963;	//0xC4F41F44
	UINT32                                                 reserved1964;	//0xC4F41F48
	UINT32                                                 reserved1965;	//0xC4F41F4C
	UINT32                                                 reserved1966;	//0xC4F41F50
	UINT32                                                 reserved1967;	//0xC4F41F54
	UINT32                                                 reserved1968;	//0xC4F41F58
	UINT32                                                 reserved1969;	//0xC4F41F5C
	UINT32                                                 reserved1970;	//0xC4F41F60
	UINT32                                                 reserved1971;	//0xC4F41F64
	UINT32                                                 reserved1972;	//0xC4F41F68
	UINT32                                                 reserved1973;	//0xC4F41F6C
	UINT32                                                 reserved1974;	//0xC4F41F70
	UINT32                                                 reserved1975;	//0xC4F41F74
	UINT32                                                 reserved1976;	//0xC4F41F78
	UINT32                                                 reserved1977;	//0xC4F41F7C
	UINT32                                                 reserved1978;	//0xC4F41F80
	UINT32                                                 reserved1979;	//0xC4F41F84
	UINT32                                                 reserved1980;	//0xC4F41F88
	UINT32                                                 reserved1981;	//0xC4F41F8C
	UINT32                                                 reserved1982;	//0xC4F41F90
	UINT32                                                 reserved1983;	//0xC4F41F94
	UINT32                                                 reserved1984;	//0xC4F41F98
	UINT32                                                 reserved1985;	//0xC4F41F9C
	UINT32                                                 reserved1986;	//0xC4F41FA0
	UINT32                                                 reserved1987;	//0xC4F41FA4
	UINT32                                                 reserved1988;	//0xC4F41FA8
	UINT32                                                 reserved1989;	//0xC4F41FAC
	UINT32                                                 reserved1990;	//0xC4F41FB0
	UINT32                                                 reserved1991;	//0xC4F41FB4
	UINT32                                                 reserved1992;	//0xC4F41FB8
	UINT32                                                 reserved1993;	//0xC4F41FBC
	UINT32                                                 reserved1994;	//0xC4F41FC0
	UINT32                                                 reserved1995;	//0xC4F41FC4
	UINT32                                                 reserved1996;	//0xC4F41FC8
	UINT32                                                 reserved1997;	//0xC4F41FCC
	UINT32                                                 reserved1998;	//0xC4F41FD0
	UINT32                                                 reserved1999;	//0xC4F41FD4
	UINT32                                                 reserved2000;	//0xC4F41FD8
	UINT32                                                 reserved2001;	//0xC4F41FDC
	UINT32                                                 reserved2002;	//0xC4F41FE0
	UINT32                                                 reserved2003;	//0xC4F41FE4
	UINT32                                                 reserved2004;	//0xC4F41FE8
	UINT32                                                 reserved2005;	//0xC4F41FEC
	UINT32                                                 reserved2006;	//0xC4F41FF0
	UINT32                                                 reserved2007;	//0xC4F41FF4
	UINT32                                                 reserved2008;	//0xC4F41FF8
	UINT32                                                 reserved2009;	//0xC4F41FFC
	REG_DDRC_M0_PQ_T                                                 pq;	//0xC4F42000
	REG_DDRC_M0_BQ_T                                                 bq;	//0xC4F42004
	REG_DDRC_M0_BQ_RW_THR_T                                   bq_rw_thr;	//0xC4F42008
	REG_DDRC_M0_BQ_HYB_STV_T                                 bq_hyb_stv;	//0xC4F4200C
	UINT32                                                 reserved2010;	//0xC4F42010
	UINT32                                                 reserved2011;	//0xC4F42014
	UINT32                                                 reserved2012;	//0xC4F42018
	UINT32                                                 reserved2013;	//0xC4F4201C
	UINT32                                                 reserved2014;	//0xC4F42020
	UINT32                                                 reserved2015;	//0xC4F42024
	UINT32                                                 reserved2016;	//0xC4F42028
	UINT32                                                 reserved2017;	//0xC4F4202C
	UINT32                                                 reserved2018;	//0xC4F42030
	UINT32                                                 reserved2019;	//0xC4F42034
	UINT32                                                 reserved2020;	//0xC4F42038
	UINT32                                                 reserved2021;	//0xC4F4203C
	UINT32                                                 reserved2022;	//0xC4F42040
	UINT32                                                 reserved2023;	//0xC4F42044
	UINT32                                                 reserved2024;	//0xC4F42048
	UINT32                                                 reserved2025;	//0xC4F4204C
	UINT32                                                 reserved2026;	//0xC4F42050
	UINT32                                                 reserved2027;	//0xC4F42054
	UINT32                                                 reserved2028;	//0xC4F42058
	UINT32                                                 reserved2029;	//0xC4F4205C
	UINT32                                                 reserved2030;	//0xC4F42060
	UINT32                                                 reserved2031;	//0xC4F42064
	UINT32                                                 reserved2032;	//0xC4F42068
	UINT32                                                 reserved2033;	//0xC4F4206C
	UINT32                                                 reserved2034;	//0xC4F42070
	UINT32                                                 reserved2035;	//0xC4F42074
	UINT32                                                 reserved2036;	//0xC4F42078
	UINT32                                                 reserved2037;	//0xC4F4207C
	UINT32                                                 reserved2038;	//0xC4F42080
	UINT32                                                 reserved2039;	//0xC4F42084
	UINT32                                                 reserved2040;	//0xC4F42088
	UINT32                                                 reserved2041;	//0xC4F4208C
	UINT32                                                 reserved2042;	//0xC4F42090
	UINT32                                                 reserved2043;	//0xC4F42094
	UINT32                                                 reserved2044;	//0xC4F42098
	UINT32                                                 reserved2045;	//0xC4F4209C
	UINT32                                                 reserved2046;	//0xC4F420A0
	UINT32                                                 reserved2047;	//0xC4F420A4
	UINT32                                                 reserved2048;	//0xC4F420A8
	UINT32                                                 reserved2049;	//0xC4F420AC
	UINT32                                                 reserved2050;	//0xC4F420B0
	UINT32                                                 reserved2051;	//0xC4F420B4
	UINT32                                                 reserved2052;	//0xC4F420B8
	UINT32                                                 reserved2053;	//0xC4F420BC
	UINT32                                                 reserved2054;	//0xC4F420C0
	UINT32                                                 reserved2055;	//0xC4F420C4
	UINT32                                                 reserved2056;	//0xC4F420C8
	UINT32                                                 reserved2057;	//0xC4F420CC
	UINT32                                                 reserved2058;	//0xC4F420D0
	UINT32                                                 reserved2059;	//0xC4F420D4
	UINT32                                                 reserved2060;	//0xC4F420D8
	UINT32                                                 reserved2061;	//0xC4F420DC
	UINT32                                                 reserved2062;	//0xC4F420E0
	UINT32                                                 reserved2063;	//0xC4F420E4
	UINT32                                                 reserved2064;	//0xC4F420E8
	UINT32                                                 reserved2065;	//0xC4F420EC
	UINT32                                                 reserved2066;	//0xC4F420F0
	UINT32                                                 reserved2067;	//0xC4F420F4
	UINT32                                                 reserved2068;	//0xC4F420F8
	UINT32                                                 reserved2069;	//0xC4F420FC
	UINT32                                                 reserved2070;	//0xC4F42100
	UINT32                                                 reserved2071;	//0xC4F42104
	UINT32                                                 reserved2072;	//0xC4F42108
	UINT32                                                 reserved2073;	//0xC4F4210C
	UINT32                                                 reserved2074;	//0xC4F42110
	UINT32                                                 reserved2075;	//0xC4F42114
	UINT32                                                 reserved2076;	//0xC4F42118
	UINT32                                                 reserved2077;	//0xC4F4211C
	UINT32                                                 reserved2078;	//0xC4F42120
	UINT32                                                 reserved2079;	//0xC4F42124
	UINT32                                                 reserved2080;	//0xC4F42128
	UINT32                                                 reserved2081;	//0xC4F4212C
	UINT32                                                 reserved2082;	//0xC4F42130
	UINT32                                                 reserved2083;	//0xC4F42134
	UINT32                                                 reserved2084;	//0xC4F42138
	UINT32                                                 reserved2085;	//0xC4F4213C
	UINT32                                                 reserved2086;	//0xC4F42140
	UINT32                                                 reserved2087;	//0xC4F42144
	UINT32                                                 reserved2088;	//0xC4F42148
	UINT32                                                 reserved2089;	//0xC4F4214C
	UINT32                                                 reserved2090;	//0xC4F42150
	UINT32                                                 reserved2091;	//0xC4F42154
	UINT32                                                 reserved2092;	//0xC4F42158
	UINT32                                                 reserved2093;	//0xC4F4215C
	UINT32                                                 reserved2094;	//0xC4F42160
	UINT32                                                 reserved2095;	//0xC4F42164
	UINT32                                                 reserved2096;	//0xC4F42168
	UINT32                                                 reserved2097;	//0xC4F4216C
	UINT32                                                 reserved2098;	//0xC4F42170
	UINT32                                                 reserved2099;	//0xC4F42174
	UINT32                                                 reserved2100;	//0xC4F42178
	UINT32                                                 reserved2101;	//0xC4F4217C
	UINT32                                                 reserved2102;	//0xC4F42180
	UINT32                                                 reserved2103;	//0xC4F42184
	UINT32                                                 reserved2104;	//0xC4F42188
	UINT32                                                 reserved2105;	//0xC4F4218C
	UINT32                                                 reserved2106;	//0xC4F42190
	UINT32                                                 reserved2107;	//0xC4F42194
	UINT32                                                 reserved2108;	//0xC4F42198
	UINT32                                                 reserved2109;	//0xC4F4219C
	UINT32                                                 reserved2110;	//0xC4F421A0
	UINT32                                                 reserved2111;	//0xC4F421A4
	UINT32                                                 reserved2112;	//0xC4F421A8
	UINT32                                                 reserved2113;	//0xC4F421AC
	UINT32                                                 reserved2114;	//0xC4F421B0
	UINT32                                                 reserved2115;	//0xC4F421B4
	UINT32                                                 reserved2116;	//0xC4F421B8
	UINT32                                                 reserved2117;	//0xC4F421BC
	UINT32                                                 reserved2118;	//0xC4F421C0
	UINT32                                                 reserved2119;	//0xC4F421C4
	UINT32                                                 reserved2120;	//0xC4F421C8
	UINT32                                                 reserved2121;	//0xC4F421CC
	UINT32                                                 reserved2122;	//0xC4F421D0
	UINT32                                                 reserved2123;	//0xC4F421D4
	UINT32                                                 reserved2124;	//0xC4F421D8
	UINT32                                                 reserved2125;	//0xC4F421DC
	UINT32                                                 reserved2126;	//0xC4F421E0
	UINT32                                                 reserved2127;	//0xC4F421E4
	UINT32                                                 reserved2128;	//0xC4F421E8
	UINT32                                                 reserved2129;	//0xC4F421EC
	UINT32                                                 reserved2130;	//0xC4F421F0
	UINT32                                                 reserved2131;	//0xC4F421F4
	UINT32                                                 reserved2132;	//0xC4F421F8
	UINT32                                                 reserved2133;	//0xC4F421FC
	UINT32                                                 reserved2134;	//0xC4F42200
	UINT32                                                 reserved2135;	//0xC4F42204
	UINT32                                                 reserved2136;	//0xC4F42208
	UINT32                                                 reserved2137;	//0xC4F4220C
	UINT32                                                 reserved2138;	//0xC4F42210
	UINT32                                                 reserved2139;	//0xC4F42214
	UINT32                                                 reserved2140;	//0xC4F42218
	UINT32                                                 reserved2141;	//0xC4F4221C
	UINT32                                                 reserved2142;	//0xC4F42220
	UINT32                                                 reserved2143;	//0xC4F42224
	UINT32                                                 reserved2144;	//0xC4F42228
	UINT32                                                 reserved2145;	//0xC4F4222C
	UINT32                                                 reserved2146;	//0xC4F42230
	UINT32                                                 reserved2147;	//0xC4F42234
	UINT32                                                 reserved2148;	//0xC4F42238
	UINT32                                                 reserved2149;	//0xC4F4223C
	UINT32                                                 reserved2150;	//0xC4F42240
	UINT32                                                 reserved2151;	//0xC4F42244
	UINT32                                                 reserved2152;	//0xC4F42248
	UINT32                                                 reserved2153;	//0xC4F4224C
	UINT32                                                 reserved2154;	//0xC4F42250
	UINT32                                                 reserved2155;	//0xC4F42254
	UINT32                                                 reserved2156;	//0xC4F42258
	UINT32                                                 reserved2157;	//0xC4F4225C
	UINT32                                                 reserved2158;	//0xC4F42260
	UINT32                                                 reserved2159;	//0xC4F42264
	UINT32                                                 reserved2160;	//0xC4F42268
	UINT32                                                 reserved2161;	//0xC4F4226C
	UINT32                                                 reserved2162;	//0xC4F42270
	UINT32                                                 reserved2163;	//0xC4F42274
	UINT32                                                 reserved2164;	//0xC4F42278
	UINT32                                                 reserved2165;	//0xC4F4227C
	UINT32                                                 reserved2166;	//0xC4F42280
	UINT32                                                 reserved2167;	//0xC4F42284
	UINT32                                                 reserved2168;	//0xC4F42288
	UINT32                                                 reserved2169;	//0xC4F4228C
	UINT32                                                 reserved2170;	//0xC4F42290
	UINT32                                                 reserved2171;	//0xC4F42294
	UINT32                                                 reserved2172;	//0xC4F42298
	UINT32                                                 reserved2173;	//0xC4F4229C
	UINT32                                                 reserved2174;	//0xC4F422A0
	UINT32                                                 reserved2175;	//0xC4F422A4
	UINT32                                                 reserved2176;	//0xC4F422A8
	UINT32                                                 reserved2177;	//0xC4F422AC
	UINT32                                                 reserved2178;	//0xC4F422B0
	UINT32                                                 reserved2179;	//0xC4F422B4
	UINT32                                                 reserved2180;	//0xC4F422B8
	UINT32                                                 reserved2181;	//0xC4F422BC
	UINT32                                                 reserved2182;	//0xC4F422C0
	UINT32                                                 reserved2183;	//0xC4F422C4
	UINT32                                                 reserved2184;	//0xC4F422C8
	UINT32                                                 reserved2185;	//0xC4F422CC
	UINT32                                                 reserved2186;	//0xC4F422D0
	UINT32                                                 reserved2187;	//0xC4F422D4
	UINT32                                                 reserved2188;	//0xC4F422D8
	UINT32                                                 reserved2189;	//0xC4F422DC
	UINT32                                                 reserved2190;	//0xC4F422E0
	UINT32                                                 reserved2191;	//0xC4F422E4
	UINT32                                                 reserved2192;	//0xC4F422E8
	UINT32                                                 reserved2193;	//0xC4F422EC
	UINT32                                                 reserved2194;	//0xC4F422F0
	UINT32                                                 reserved2195;	//0xC4F422F4
	UINT32                                                 reserved2196;	//0xC4F422F8
	UINT32                                                 reserved2197;	//0xC4F422FC
	UINT32                                                 reserved2198;	//0xC4F42300
	UINT32                                                 reserved2199;	//0xC4F42304
	UINT32                                                 reserved2200;	//0xC4F42308
	UINT32                                                 reserved2201;	//0xC4F4230C
	UINT32                                                 reserved2202;	//0xC4F42310
	UINT32                                                 reserved2203;	//0xC4F42314
	UINT32                                                 reserved2204;	//0xC4F42318
	UINT32                                                 reserved2205;	//0xC4F4231C
	UINT32                                                 reserved2206;	//0xC4F42320
	UINT32                                                 reserved2207;	//0xC4F42324
	UINT32                                                 reserved2208;	//0xC4F42328
	UINT32                                                 reserved2209;	//0xC4F4232C
	UINT32                                                 reserved2210;	//0xC4F42330
	UINT32                                                 reserved2211;	//0xC4F42334
	UINT32                                                 reserved2212;	//0xC4F42338
	UINT32                                                 reserved2213;	//0xC4F4233C
	UINT32                                                 reserved2214;	//0xC4F42340
	UINT32                                                 reserved2215;	//0xC4F42344
	UINT32                                                 reserved2216;	//0xC4F42348
	UINT32                                                 reserved2217;	//0xC4F4234C
	UINT32                                                 reserved2218;	//0xC4F42350
	UINT32                                                 reserved2219;	//0xC4F42354
	UINT32                                                 reserved2220;	//0xC4F42358
	UINT32                                                 reserved2221;	//0xC4F4235C
	UINT32                                                 reserved2222;	//0xC4F42360
	UINT32                                                 reserved2223;	//0xC4F42364
	UINT32                                                 reserved2224;	//0xC4F42368
	UINT32                                                 reserved2225;	//0xC4F4236C
	UINT32                                                 reserved2226;	//0xC4F42370
	UINT32                                                 reserved2227;	//0xC4F42374
	UINT32                                                 reserved2228;	//0xC4F42378
	UINT32                                                 reserved2229;	//0xC4F4237C
	UINT32                                                 reserved2230;	//0xC4F42380
	UINT32                                                 reserved2231;	//0xC4F42384
	UINT32                                                 reserved2232;	//0xC4F42388
	UINT32                                                 reserved2233;	//0xC4F4238C
	UINT32                                                 reserved2234;	//0xC4F42390
	UINT32                                                 reserved2235;	//0xC4F42394
	UINT32                                                 reserved2236;	//0xC4F42398
	UINT32                                                 reserved2237;	//0xC4F4239C
	UINT32                                                 reserved2238;	//0xC4F423A0
	UINT32                                                 reserved2239;	//0xC4F423A4
	UINT32                                                 reserved2240;	//0xC4F423A8
	UINT32                                                 reserved2241;	//0xC4F423AC
	UINT32                                                 reserved2242;	//0xC4F423B0
	UINT32                                                 reserved2243;	//0xC4F423B4
	UINT32                                                 reserved2244;	//0xC4F423B8
	UINT32                                                 reserved2245;	//0xC4F423BC
	UINT32                                                 reserved2246;	//0xC4F423C0
	UINT32                                                 reserved2247;	//0xC4F423C4
	UINT32                                                 reserved2248;	//0xC4F423C8
	UINT32                                                 reserved2249;	//0xC4F423CC
	UINT32                                                 reserved2250;	//0xC4F423D0
	UINT32                                                 reserved2251;	//0xC4F423D4
	UINT32                                                 reserved2252;	//0xC4F423D8
	UINT32                                                 reserved2253;	//0xC4F423DC
	UINT32                                                 reserved2254;	//0xC4F423E0
	UINT32                                                 reserved2255;	//0xC4F423E4
	UINT32                                                 reserved2256;	//0xC4F423E8
	UINT32                                                 reserved2257;	//0xC4F423EC
	UINT32                                                 reserved2258;	//0xC4F423F0
	UINT32                                                 reserved2259;	//0xC4F423F4
	UINT32                                                 reserved2260;	//0xC4F423F8
	UINT32                                                 reserved2261;	//0xC4F423FC
	UINT32                                                 reserved2262;	//0xC4F42400
	UINT32                                                 reserved2263;	//0xC4F42404
	UINT32                                                 reserved2264;	//0xC4F42408
	UINT32                                                 reserved2265;	//0xC4F4240C
	UINT32                                                 reserved2266;	//0xC4F42410
	UINT32                                                 reserved2267;	//0xC4F42414
	UINT32                                                 reserved2268;	//0xC4F42418
	UINT32                                                 reserved2269;	//0xC4F4241C
	UINT32                                                 reserved2270;	//0xC4F42420
	UINT32                                                 reserved2271;	//0xC4F42424
	UINT32                                                 reserved2272;	//0xC4F42428
	UINT32                                                 reserved2273;	//0xC4F4242C
	UINT32                                                 reserved2274;	//0xC4F42430
	UINT32                                                 reserved2275;	//0xC4F42434
	UINT32                                                 reserved2276;	//0xC4F42438
	UINT32                                                 reserved2277;	//0xC4F4243C
	UINT32                                                 reserved2278;	//0xC4F42440
	UINT32                                                 reserved2279;	//0xC4F42444
	UINT32                                                 reserved2280;	//0xC4F42448
	UINT32                                                 reserved2281;	//0xC4F4244C
	UINT32                                                 reserved2282;	//0xC4F42450
	UINT32                                                 reserved2283;	//0xC4F42454
	UINT32                                                 reserved2284;	//0xC4F42458
	UINT32                                                 reserved2285;	//0xC4F4245C
	UINT32                                                 reserved2286;	//0xC4F42460
	UINT32                                                 reserved2287;	//0xC4F42464
	UINT32                                                 reserved2288;	//0xC4F42468
	UINT32                                                 reserved2289;	//0xC4F4246C
	UINT32                                                 reserved2290;	//0xC4F42470
	UINT32                                                 reserved2291;	//0xC4F42474
	UINT32                                                 reserved2292;	//0xC4F42478
	UINT32                                                 reserved2293;	//0xC4F4247C
	UINT32                                                 reserved2294;	//0xC4F42480
	UINT32                                                 reserved2295;	//0xC4F42484
	UINT32                                                 reserved2296;	//0xC4F42488
	UINT32                                                 reserved2297;	//0xC4F4248C
	UINT32                                                 reserved2298;	//0xC4F42490
	UINT32                                                 reserved2299;	//0xC4F42494
	UINT32                                                 reserved2300;	//0xC4F42498
	UINT32                                                 reserved2301;	//0xC4F4249C
	UINT32                                                 reserved2302;	//0xC4F424A0
	UINT32                                                 reserved2303;	//0xC4F424A4
	UINT32                                                 reserved2304;	//0xC4F424A8
	UINT32                                                 reserved2305;	//0xC4F424AC
	UINT32                                                 reserved2306;	//0xC4F424B0
	UINT32                                                 reserved2307;	//0xC4F424B4
	UINT32                                                 reserved2308;	//0xC4F424B8
	UINT32                                                 reserved2309;	//0xC4F424BC
	UINT32                                                 reserved2310;	//0xC4F424C0
	UINT32                                                 reserved2311;	//0xC4F424C4
	UINT32                                                 reserved2312;	//0xC4F424C8
	UINT32                                                 reserved2313;	//0xC4F424CC
	UINT32                                                 reserved2314;	//0xC4F424D0
	UINT32                                                 reserved2315;	//0xC4F424D4
	UINT32                                                 reserved2316;	//0xC4F424D8
	UINT32                                                 reserved2317;	//0xC4F424DC
	UINT32                                                 reserved2318;	//0xC4F424E0
	UINT32                                                 reserved2319;	//0xC4F424E4
	UINT32                                                 reserved2320;	//0xC4F424E8
	UINT32                                                 reserved2321;	//0xC4F424EC
	UINT32                                                 reserved2322;	//0xC4F424F0
	UINT32                                                 reserved2323;	//0xC4F424F4
	UINT32                                                 reserved2324;	//0xC4F424F8
	UINT32                                                 reserved2325;	//0xC4F424FC
	UINT32                                                 reserved2326;	//0xC4F42500
	UINT32                                                 reserved2327;	//0xC4F42504
	UINT32                                                 reserved2328;	//0xC4F42508
	UINT32                                                 reserved2329;	//0xC4F4250C
	UINT32                                                 reserved2330;	//0xC4F42510
	UINT32                                                 reserved2331;	//0xC4F42514
	UINT32                                                 reserved2332;	//0xC4F42518
	UINT32                                                 reserved2333;	//0xC4F4251C
	UINT32                                                 reserved2334;	//0xC4F42520
	UINT32                                                 reserved2335;	//0xC4F42524
	UINT32                                                 reserved2336;	//0xC4F42528
	UINT32                                                 reserved2337;	//0xC4F4252C
	UINT32                                                 reserved2338;	//0xC4F42530
	UINT32                                                 reserved2339;	//0xC4F42534
	UINT32                                                 reserved2340;	//0xC4F42538
	UINT32                                                 reserved2341;	//0xC4F4253C
	UINT32                                                 reserved2342;	//0xC4F42540
	UINT32                                                 reserved2343;	//0xC4F42544
	UINT32                                                 reserved2344;	//0xC4F42548
	UINT32                                                 reserved2345;	//0xC4F4254C
	UINT32                                                 reserved2346;	//0xC4F42550
	UINT32                                                 reserved2347;	//0xC4F42554
	UINT32                                                 reserved2348;	//0xC4F42558
	UINT32                                                 reserved2349;	//0xC4F4255C
	UINT32                                                 reserved2350;	//0xC4F42560
	UINT32                                                 reserved2351;	//0xC4F42564
	UINT32                                                 reserved2352;	//0xC4F42568
	UINT32                                                 reserved2353;	//0xC4F4256C
	UINT32                                                 reserved2354;	//0xC4F42570
	UINT32                                                 reserved2355;	//0xC4F42574
	UINT32                                                 reserved2356;	//0xC4F42578
	UINT32                                                 reserved2357;	//0xC4F4257C
	UINT32                                                 reserved2358;	//0xC4F42580
	UINT32                                                 reserved2359;	//0xC4F42584
	UINT32                                                 reserved2360;	//0xC4F42588
	UINT32                                                 reserved2361;	//0xC4F4258C
	UINT32                                                 reserved2362;	//0xC4F42590
	UINT32                                                 reserved2363;	//0xC4F42594
	UINT32                                                 reserved2364;	//0xC4F42598
	UINT32                                                 reserved2365;	//0xC4F4259C
	UINT32                                                 reserved2366;	//0xC4F425A0
	UINT32                                                 reserved2367;	//0xC4F425A4
	UINT32                                                 reserved2368;	//0xC4F425A8
	UINT32                                                 reserved2369;	//0xC4F425AC
	UINT32                                                 reserved2370;	//0xC4F425B0
	UINT32                                                 reserved2371;	//0xC4F425B4
	UINT32                                                 reserved2372;	//0xC4F425B8
	UINT32                                                 reserved2373;	//0xC4F425BC
	UINT32                                                 reserved2374;	//0xC4F425C0
	UINT32                                                 reserved2375;	//0xC4F425C4
	UINT32                                                 reserved2376;	//0xC4F425C8
	UINT32                                                 reserved2377;	//0xC4F425CC
	UINT32                                                 reserved2378;	//0xC4F425D0
	UINT32                                                 reserved2379;	//0xC4F425D4
	UINT32                                                 reserved2380;	//0xC4F425D8
	UINT32                                                 reserved2381;	//0xC4F425DC
	UINT32                                                 reserved2382;	//0xC4F425E0
	UINT32                                                 reserved2383;	//0xC4F425E4
	UINT32                                                 reserved2384;	//0xC4F425E8
	UINT32                                                 reserved2385;	//0xC4F425EC
	UINT32                                                 reserved2386;	//0xC4F425F0
	UINT32                                                 reserved2387;	//0xC4F425F4
	UINT32                                                 reserved2388;	//0xC4F425F8
	UINT32                                                 reserved2389;	//0xC4F425FC
	UINT32                                                 reserved2390;	//0xC4F42600
	UINT32                                                 reserved2391;	//0xC4F42604
	UINT32                                                 reserved2392;	//0xC4F42608
	UINT32                                                 reserved2393;	//0xC4F4260C
	UINT32                                                 reserved2394;	//0xC4F42610
	UINT32                                                 reserved2395;	//0xC4F42614
	UINT32                                                 reserved2396;	//0xC4F42618
	UINT32                                                 reserved2397;	//0xC4F4261C
	UINT32                                                 reserved2398;	//0xC4F42620
	UINT32                                                 reserved2399;	//0xC4F42624
	UINT32                                                 reserved2400;	//0xC4F42628
	UINT32                                                 reserved2401;	//0xC4F4262C
	UINT32                                                 reserved2402;	//0xC4F42630
	UINT32                                                 reserved2403;	//0xC4F42634
	UINT32                                                 reserved2404;	//0xC4F42638
	UINT32                                                 reserved2405;	//0xC4F4263C
	UINT32                                                 reserved2406;	//0xC4F42640
	UINT32                                                 reserved2407;	//0xC4F42644
	UINT32                                                 reserved2408;	//0xC4F42648
	UINT32                                                 reserved2409;	//0xC4F4264C
	UINT32                                                 reserved2410;	//0xC4F42650
	UINT32                                                 reserved2411;	//0xC4F42654
	UINT32                                                 reserved2412;	//0xC4F42658
	UINT32                                                 reserved2413;	//0xC4F4265C
	UINT32                                                 reserved2414;	//0xC4F42660
	UINT32                                                 reserved2415;	//0xC4F42664
	UINT32                                                 reserved2416;	//0xC4F42668
	UINT32                                                 reserved2417;	//0xC4F4266C
	UINT32                                                 reserved2418;	//0xC4F42670
	UINT32                                                 reserved2419;	//0xC4F42674
	UINT32                                                 reserved2420;	//0xC4F42678
	UINT32                                                 reserved2421;	//0xC4F4267C
	UINT32                                                 reserved2422;	//0xC4F42680
	UINT32                                                 reserved2423;	//0xC4F42684
	UINT32                                                 reserved2424;	//0xC4F42688
	UINT32                                                 reserved2425;	//0xC4F4268C
	UINT32                                                 reserved2426;	//0xC4F42690
	UINT32                                                 reserved2427;	//0xC4F42694
	UINT32                                                 reserved2428;	//0xC4F42698
	UINT32                                                 reserved2429;	//0xC4F4269C
	UINT32                                                 reserved2430;	//0xC4F426A0
	UINT32                                                 reserved2431;	//0xC4F426A4
	UINT32                                                 reserved2432;	//0xC4F426A8
	UINT32                                                 reserved2433;	//0xC4F426AC
	UINT32                                                 reserved2434;	//0xC4F426B0
	UINT32                                                 reserved2435;	//0xC4F426B4
	UINT32                                                 reserved2436;	//0xC4F426B8
	UINT32                                                 reserved2437;	//0xC4F426BC
	UINT32                                                 reserved2438;	//0xC4F426C0
	UINT32                                                 reserved2439;	//0xC4F426C4
	UINT32                                                 reserved2440;	//0xC4F426C8
	UINT32                                                 reserved2441;	//0xC4F426CC
	UINT32                                                 reserved2442;	//0xC4F426D0
	UINT32                                                 reserved2443;	//0xC4F426D4
	UINT32                                                 reserved2444;	//0xC4F426D8
	UINT32                                                 reserved2445;	//0xC4F426DC
	UINT32                                                 reserved2446;	//0xC4F426E0
	UINT32                                                 reserved2447;	//0xC4F426E4
	UINT32                                                 reserved2448;	//0xC4F426E8
	UINT32                                                 reserved2449;	//0xC4F426EC
	UINT32                                                 reserved2450;	//0xC4F426F0
	UINT32                                                 reserved2451;	//0xC4F426F4
	UINT32                                                 reserved2452;	//0xC4F426F8
	UINT32                                                 reserved2453;	//0xC4F426FC
	UINT32                                                 reserved2454;	//0xC4F42700
	UINT32                                                 reserved2455;	//0xC4F42704
	UINT32                                                 reserved2456;	//0xC4F42708
	UINT32                                                 reserved2457;	//0xC4F4270C
	UINT32                                                 reserved2458;	//0xC4F42710
	UINT32                                                 reserved2459;	//0xC4F42714
	UINT32                                                 reserved2460;	//0xC4F42718
	UINT32                                                 reserved2461;	//0xC4F4271C
	UINT32                                                 reserved2462;	//0xC4F42720
	UINT32                                                 reserved2463;	//0xC4F42724
	UINT32                                                 reserved2464;	//0xC4F42728
	UINT32                                                 reserved2465;	//0xC4F4272C
	UINT32                                                 reserved2466;	//0xC4F42730
	UINT32                                                 reserved2467;	//0xC4F42734
	UINT32                                                 reserved2468;	//0xC4F42738
	UINT32                                                 reserved2469;	//0xC4F4273C
	UINT32                                                 reserved2470;	//0xC4F42740
	UINT32                                                 reserved2471;	//0xC4F42744
	UINT32                                                 reserved2472;	//0xC4F42748
	UINT32                                                 reserved2473;	//0xC4F4274C
	UINT32                                                 reserved2474;	//0xC4F42750
	UINT32                                                 reserved2475;	//0xC4F42754
	UINT32                                                 reserved2476;	//0xC4F42758
	UINT32                                                 reserved2477;	//0xC4F4275C
	UINT32                                                 reserved2478;	//0xC4F42760
	UINT32                                                 reserved2479;	//0xC4F42764
	UINT32                                                 reserved2480;	//0xC4F42768
	UINT32                                                 reserved2481;	//0xC4F4276C
	UINT32                                                 reserved2482;	//0xC4F42770
	UINT32                                                 reserved2483;	//0xC4F42774
	UINT32                                                 reserved2484;	//0xC4F42778
	UINT32                                                 reserved2485;	//0xC4F4277C
	UINT32                                                 reserved2486;	//0xC4F42780
	UINT32                                                 reserved2487;	//0xC4F42784
	UINT32                                                 reserved2488;	//0xC4F42788
	UINT32                                                 reserved2489;	//0xC4F4278C
	UINT32                                                 reserved2490;	//0xC4F42790
	UINT32                                                 reserved2491;	//0xC4F42794
	UINT32                                                 reserved2492;	//0xC4F42798
	UINT32                                                 reserved2493;	//0xC4F4279C
	UINT32                                                 reserved2494;	//0xC4F427A0
	UINT32                                                 reserved2495;	//0xC4F427A4
	UINT32                                                 reserved2496;	//0xC4F427A8
	UINT32                                                 reserved2497;	//0xC4F427AC
	UINT32                                                 reserved2498;	//0xC4F427B0
	UINT32                                                 reserved2499;	//0xC4F427B4
	UINT32                                                 reserved2500;	//0xC4F427B8
	UINT32                                                 reserved2501;	//0xC4F427BC
	UINT32                                                 reserved2502;	//0xC4F427C0
	UINT32                                                 reserved2503;	//0xC4F427C4
	UINT32                                                 reserved2504;	//0xC4F427C8
	UINT32                                                 reserved2505;	//0xC4F427CC
	UINT32                                                 reserved2506;	//0xC4F427D0
	UINT32                                                 reserved2507;	//0xC4F427D4
	UINT32                                                 reserved2508;	//0xC4F427D8
	UINT32                                                 reserved2509;	//0xC4F427DC
	UINT32                                                 reserved2510;	//0xC4F427E0
	UINT32                                                 reserved2511;	//0xC4F427E4
	UINT32                                                 reserved2512;	//0xC4F427E8
	UINT32                                                 reserved2513;	//0xC4F427EC
	UINT32                                                 reserved2514;	//0xC4F427F0
	UINT32                                                 reserved2515;	//0xC4F427F4
	UINT32                                                 reserved2516;	//0xC4F427F8
	UINT32                                                 reserved2517;	//0xC4F427FC
	UINT32                                                 reserved2518;	//0xC4F42800
	UINT32                                                 reserved2519;	//0xC4F42804
	UINT32                                                 reserved2520;	//0xC4F42808
	UINT32                                                 reserved2521;	//0xC4F4280C
	UINT32                                                 reserved2522;	//0xC4F42810
	UINT32                                                 reserved2523;	//0xC4F42814
	UINT32                                                 reserved2524;	//0xC4F42818
	UINT32                                                 reserved2525;	//0xC4F4281C
	UINT32                                                 reserved2526;	//0xC4F42820
	UINT32                                                 reserved2527;	//0xC4F42824
	UINT32                                                 reserved2528;	//0xC4F42828
	UINT32                                                 reserved2529;	//0xC4F4282C
	UINT32                                                 reserved2530;	//0xC4F42830
	UINT32                                                 reserved2531;	//0xC4F42834
	UINT32                                                 reserved2532;	//0xC4F42838
	UINT32                                                 reserved2533;	//0xC4F4283C
	UINT32                                                 reserved2534;	//0xC4F42840
	UINT32                                                 reserved2535;	//0xC4F42844
	UINT32                                                 reserved2536;	//0xC4F42848
	UINT32                                                 reserved2537;	//0xC4F4284C
	UINT32                                                 reserved2538;	//0xC4F42850
	UINT32                                                 reserved2539;	//0xC4F42854
	UINT32                                                 reserved2540;	//0xC4F42858
	UINT32                                                 reserved2541;	//0xC4F4285C
	UINT32                                                 reserved2542;	//0xC4F42860
	UINT32                                                 reserved2543;	//0xC4F42864
	UINT32                                                 reserved2544;	//0xC4F42868
	UINT32                                                 reserved2545;	//0xC4F4286C
	UINT32                                                 reserved2546;	//0xC4F42870
	UINT32                                                 reserved2547;	//0xC4F42874
	UINT32                                                 reserved2548;	//0xC4F42878
	UINT32                                                 reserved2549;	//0xC4F4287C
	UINT32                                                 reserved2550;	//0xC4F42880
	UINT32                                                 reserved2551;	//0xC4F42884
	UINT32                                                 reserved2552;	//0xC4F42888
	UINT32                                                 reserved2553;	//0xC4F4288C
	UINT32                                                 reserved2554;	//0xC4F42890
	UINT32                                                 reserved2555;	//0xC4F42894
	UINT32                                                 reserved2556;	//0xC4F42898
	UINT32                                                 reserved2557;	//0xC4F4289C
	UINT32                                                 reserved2558;	//0xC4F428A0
	UINT32                                                 reserved2559;	//0xC4F428A4
	UINT32                                                 reserved2560;	//0xC4F428A8
	UINT32                                                 reserved2561;	//0xC4F428AC
	UINT32                                                 reserved2562;	//0xC4F428B0
	UINT32                                                 reserved2563;	//0xC4F428B4
	UINT32                                                 reserved2564;	//0xC4F428B8
	UINT32                                                 reserved2565;	//0xC4F428BC
	UINT32                                                 reserved2566;	//0xC4F428C0
	UINT32                                                 reserved2567;	//0xC4F428C4
	UINT32                                                 reserved2568;	//0xC4F428C8
	UINT32                                                 reserved2569;	//0xC4F428CC
	UINT32                                                 reserved2570;	//0xC4F428D0
	UINT32                                                 reserved2571;	//0xC4F428D4
	UINT32                                                 reserved2572;	//0xC4F428D8
	UINT32                                                 reserved2573;	//0xC4F428DC
	UINT32                                                 reserved2574;	//0xC4F428E0
	UINT32                                                 reserved2575;	//0xC4F428E4
	UINT32                                                 reserved2576;	//0xC4F428E8
	UINT32                                                 reserved2577;	//0xC4F428EC
	UINT32                                                 reserved2578;	//0xC4F428F0
	UINT32                                                 reserved2579;	//0xC4F428F4
	UINT32                                                 reserved2580;	//0xC4F428F8
	UINT32                                                 reserved2581;	//0xC4F428FC
	UINT32                                                 reserved2582;	//0xC4F42900
	UINT32                                                 reserved2583;	//0xC4F42904
	UINT32                                                 reserved2584;	//0xC4F42908
	UINT32                                                 reserved2585;	//0xC4F4290C
	UINT32                                                 reserved2586;	//0xC4F42910
	UINT32                                                 reserved2587;	//0xC4F42914
	UINT32                                                 reserved2588;	//0xC4F42918
	UINT32                                                 reserved2589;	//0xC4F4291C
	UINT32                                                 reserved2590;	//0xC4F42920
	UINT32                                                 reserved2591;	//0xC4F42924
	UINT32                                                 reserved2592;	//0xC4F42928
	UINT32                                                 reserved2593;	//0xC4F4292C
	UINT32                                                 reserved2594;	//0xC4F42930
	UINT32                                                 reserved2595;	//0xC4F42934
	UINT32                                                 reserved2596;	//0xC4F42938
	UINT32                                                 reserved2597;	//0xC4F4293C
	UINT32                                                 reserved2598;	//0xC4F42940
	UINT32                                                 reserved2599;	//0xC4F42944
	UINT32                                                 reserved2600;	//0xC4F42948
	UINT32                                                 reserved2601;	//0xC4F4294C
	UINT32                                                 reserved2602;	//0xC4F42950
	UINT32                                                 reserved2603;	//0xC4F42954
	UINT32                                                 reserved2604;	//0xC4F42958
	UINT32                                                 reserved2605;	//0xC4F4295C
	UINT32                                                 reserved2606;	//0xC4F42960
	UINT32                                                 reserved2607;	//0xC4F42964
	UINT32                                                 reserved2608;	//0xC4F42968
	UINT32                                                 reserved2609;	//0xC4F4296C
	UINT32                                                 reserved2610;	//0xC4F42970
	UINT32                                                 reserved2611;	//0xC4F42974
	UINT32                                                 reserved2612;	//0xC4F42978
	UINT32                                                 reserved2613;	//0xC4F4297C
	UINT32                                                 reserved2614;	//0xC4F42980
	UINT32                                                 reserved2615;	//0xC4F42984
	UINT32                                                 reserved2616;	//0xC4F42988
	UINT32                                                 reserved2617;	//0xC4F4298C
	UINT32                                                 reserved2618;	//0xC4F42990
	UINT32                                                 reserved2619;	//0xC4F42994
	UINT32                                                 reserved2620;	//0xC4F42998
	UINT32                                                 reserved2621;	//0xC4F4299C
	UINT32                                                 reserved2622;	//0xC4F429A0
	UINT32                                                 reserved2623;	//0xC4F429A4
	UINT32                                                 reserved2624;	//0xC4F429A8
	UINT32                                                 reserved2625;	//0xC4F429AC
	UINT32                                                 reserved2626;	//0xC4F429B0
	UINT32                                                 reserved2627;	//0xC4F429B4
	UINT32                                                 reserved2628;	//0xC4F429B8
	UINT32                                                 reserved2629;	//0xC4F429BC
	UINT32                                                 reserved2630;	//0xC4F429C0
	UINT32                                                 reserved2631;	//0xC4F429C4
	UINT32                                                 reserved2632;	//0xC4F429C8
	UINT32                                                 reserved2633;	//0xC4F429CC
	UINT32                                                 reserved2634;	//0xC4F429D0
	UINT32                                                 reserved2635;	//0xC4F429D4
	UINT32                                                 reserved2636;	//0xC4F429D8
	UINT32                                                 reserved2637;	//0xC4F429DC
	UINT32                                                 reserved2638;	//0xC4F429E0
	UINT32                                                 reserved2639;	//0xC4F429E4
	UINT32                                                 reserved2640;	//0xC4F429E8
	UINT32                                                 reserved2641;	//0xC4F429EC
	UINT32                                                 reserved2642;	//0xC4F429F0
	UINT32                                                 reserved2643;	//0xC4F429F4
	UINT32                                                 reserved2644;	//0xC4F429F8
	UINT32                                                 reserved2645;	//0xC4F429FC
	UINT32                                                 reserved2646;	//0xC4F42A00
	UINT32                                                 reserved2647;	//0xC4F42A04
	UINT32                                                 reserved2648;	//0xC4F42A08
	UINT32                                                 reserved2649;	//0xC4F42A0C
	UINT32                                                 reserved2650;	//0xC4F42A10
	UINT32                                                 reserved2651;	//0xC4F42A14
	UINT32                                                 reserved2652;	//0xC4F42A18
	UINT32                                                 reserved2653;	//0xC4F42A1C
	UINT32                                                 reserved2654;	//0xC4F42A20
	UINT32                                                 reserved2655;	//0xC4F42A24
	UINT32                                                 reserved2656;	//0xC4F42A28
	UINT32                                                 reserved2657;	//0xC4F42A2C
	UINT32                                                 reserved2658;	//0xC4F42A30
	UINT32                                                 reserved2659;	//0xC4F42A34
	UINT32                                                 reserved2660;	//0xC4F42A38
	UINT32                                                 reserved2661;	//0xC4F42A3C
	UINT32                                                 reserved2662;	//0xC4F42A40
	UINT32                                                 reserved2663;	//0xC4F42A44
	UINT32                                                 reserved2664;	//0xC4F42A48
	UINT32                                                 reserved2665;	//0xC4F42A4C
	UINT32                                                 reserved2666;	//0xC4F42A50
	UINT32                                                 reserved2667;	//0xC4F42A54
	UINT32                                                 reserved2668;	//0xC4F42A58
	UINT32                                                 reserved2669;	//0xC4F42A5C
	UINT32                                                 reserved2670;	//0xC4F42A60
	UINT32                                                 reserved2671;	//0xC4F42A64
	UINT32                                                 reserved2672;	//0xC4F42A68
	UINT32                                                 reserved2673;	//0xC4F42A6C
	UINT32                                                 reserved2674;	//0xC4F42A70
	UINT32                                                 reserved2675;	//0xC4F42A74
	UINT32                                                 reserved2676;	//0xC4F42A78
	UINT32                                                 reserved2677;	//0xC4F42A7C
	UINT32                                                 reserved2678;	//0xC4F42A80
	UINT32                                                 reserved2679;	//0xC4F42A84
	UINT32                                                 reserved2680;	//0xC4F42A88
	UINT32                                                 reserved2681;	//0xC4F42A8C
	UINT32                                                 reserved2682;	//0xC4F42A90
	UINT32                                                 reserved2683;	//0xC4F42A94
	UINT32                                                 reserved2684;	//0xC4F42A98
	UINT32                                                 reserved2685;	//0xC4F42A9C
	UINT32                                                 reserved2686;	//0xC4F42AA0
	UINT32                                                 reserved2687;	//0xC4F42AA4
	UINT32                                                 reserved2688;	//0xC4F42AA8
	UINT32                                                 reserved2689;	//0xC4F42AAC
	UINT32                                                 reserved2690;	//0xC4F42AB0
	UINT32                                                 reserved2691;	//0xC4F42AB4
	UINT32                                                 reserved2692;	//0xC4F42AB8
	UINT32                                                 reserved2693;	//0xC4F42ABC
	UINT32                                                 reserved2694;	//0xC4F42AC0
	UINT32                                                 reserved2695;	//0xC4F42AC4
	UINT32                                                 reserved2696;	//0xC4F42AC8
	UINT32                                                 reserved2697;	//0xC4F42ACC
	UINT32                                                 reserved2698;	//0xC4F42AD0
	UINT32                                                 reserved2699;	//0xC4F42AD4
	UINT32                                                 reserved2700;	//0xC4F42AD8
	UINT32                                                 reserved2701;	//0xC4F42ADC
	UINT32                                                 reserved2702;	//0xC4F42AE0
	UINT32                                                 reserved2703;	//0xC4F42AE4
	UINT32                                                 reserved2704;	//0xC4F42AE8
	UINT32                                                 reserved2705;	//0xC4F42AEC
	UINT32                                                 reserved2706;	//0xC4F42AF0
	UINT32                                                 reserved2707;	//0xC4F42AF4
	UINT32                                                 reserved2708;	//0xC4F42AF8
	UINT32                                                 reserved2709;	//0xC4F42AFC
	UINT32                                                 reserved2710;	//0xC4F42B00
	UINT32                                                 reserved2711;	//0xC4F42B04
	UINT32                                                 reserved2712;	//0xC4F42B08
	UINT32                                                 reserved2713;	//0xC4F42B0C
	UINT32                                                 reserved2714;	//0xC4F42B10
	UINT32                                                 reserved2715;	//0xC4F42B14
	UINT32                                                 reserved2716;	//0xC4F42B18
	UINT32                                                 reserved2717;	//0xC4F42B1C
	UINT32                                                 reserved2718;	//0xC4F42B20
	UINT32                                                 reserved2719;	//0xC4F42B24
	UINT32                                                 reserved2720;	//0xC4F42B28
	UINT32                                                 reserved2721;	//0xC4F42B2C
	UINT32                                                 reserved2722;	//0xC4F42B30
	UINT32                                                 reserved2723;	//0xC4F42B34
	UINT32                                                 reserved2724;	//0xC4F42B38
	UINT32                                                 reserved2725;	//0xC4F42B3C
	UINT32                                                 reserved2726;	//0xC4F42B40
	UINT32                                                 reserved2727;	//0xC4F42B44
	UINT32                                                 reserved2728;	//0xC4F42B48
	UINT32                                                 reserved2729;	//0xC4F42B4C
	UINT32                                                 reserved2730;	//0xC4F42B50
	UINT32                                                 reserved2731;	//0xC4F42B54
	UINT32                                                 reserved2732;	//0xC4F42B58
	UINT32                                                 reserved2733;	//0xC4F42B5C
	UINT32                                                 reserved2734;	//0xC4F42B60
	UINT32                                                 reserved2735;	//0xC4F42B64
	UINT32                                                 reserved2736;	//0xC4F42B68
	UINT32                                                 reserved2737;	//0xC4F42B6C
	UINT32                                                 reserved2738;	//0xC4F42B70
	UINT32                                                 reserved2739;	//0xC4F42B74
	UINT32                                                 reserved2740;	//0xC4F42B78
	UINT32                                                 reserved2741;	//0xC4F42B7C
	UINT32                                                 reserved2742;	//0xC4F42B80
	UINT32                                                 reserved2743;	//0xC4F42B84
	UINT32                                                 reserved2744;	//0xC4F42B88
	UINT32                                                 reserved2745;	//0xC4F42B8C
	UINT32                                                 reserved2746;	//0xC4F42B90
	UINT32                                                 reserved2747;	//0xC4F42B94
	UINT32                                                 reserved2748;	//0xC4F42B98
	UINT32                                                 reserved2749;	//0xC4F42B9C
	UINT32                                                 reserved2750;	//0xC4F42BA0
	UINT32                                                 reserved2751;	//0xC4F42BA4
	UINT32                                                 reserved2752;	//0xC4F42BA8
	UINT32                                                 reserved2753;	//0xC4F42BAC
	UINT32                                                 reserved2754;	//0xC4F42BB0
	UINT32                                                 reserved2755;	//0xC4F42BB4
	UINT32                                                 reserved2756;	//0xC4F42BB8
	UINT32                                                 reserved2757;	//0xC4F42BBC
	UINT32                                                 reserved2758;	//0xC4F42BC0
	UINT32                                                 reserved2759;	//0xC4F42BC4
	UINT32                                                 reserved2760;	//0xC4F42BC8
	UINT32                                                 reserved2761;	//0xC4F42BCC
	UINT32                                                 reserved2762;	//0xC4F42BD0
	UINT32                                                 reserved2763;	//0xC4F42BD4
	UINT32                                                 reserved2764;	//0xC4F42BD8
	UINT32                                                 reserved2765;	//0xC4F42BDC
	UINT32                                                 reserved2766;	//0xC4F42BE0
	UINT32                                                 reserved2767;	//0xC4F42BE4
	UINT32                                                 reserved2768;	//0xC4F42BE8
	UINT32                                                 reserved2769;	//0xC4F42BEC
	UINT32                                                 reserved2770;	//0xC4F42BF0
	UINT32                                                 reserved2771;	//0xC4F42BF4
	UINT32                                                 reserved2772;	//0xC4F42BF8
	UINT32                                                 reserved2773;	//0xC4F42BFC
	UINT32                                                 reserved2774;	//0xC4F42C00
	UINT32                                                 reserved2775;	//0xC4F42C04
	UINT32                                                 reserved2776;	//0xC4F42C08
	UINT32                                                 reserved2777;	//0xC4F42C0C
	UINT32                                                 reserved2778;	//0xC4F42C10
	UINT32                                                 reserved2779;	//0xC4F42C14
	UINT32                                                 reserved2780;	//0xC4F42C18
	UINT32                                                 reserved2781;	//0xC4F42C1C
	UINT32                                                 reserved2782;	//0xC4F42C20
	UINT32                                                 reserved2783;	//0xC4F42C24
	UINT32                                                 reserved2784;	//0xC4F42C28
	UINT32                                                 reserved2785;	//0xC4F42C2C
	UINT32                                                 reserved2786;	//0xC4F42C30
	UINT32                                                 reserved2787;	//0xC4F42C34
	UINT32                                                 reserved2788;	//0xC4F42C38
	UINT32                                                 reserved2789;	//0xC4F42C3C
	UINT32                                                 reserved2790;	//0xC4F42C40
	UINT32                                                 reserved2791;	//0xC4F42C44
	UINT32                                                 reserved2792;	//0xC4F42C48
	UINT32                                                 reserved2793;	//0xC4F42C4C
	UINT32                                                 reserved2794;	//0xC4F42C50
	UINT32                                                 reserved2795;	//0xC4F42C54
	UINT32                                                 reserved2796;	//0xC4F42C58
	UINT32                                                 reserved2797;	//0xC4F42C5C
	UINT32                                                 reserved2798;	//0xC4F42C60
	UINT32                                                 reserved2799;	//0xC4F42C64
	UINT32                                                 reserved2800;	//0xC4F42C68
	UINT32                                                 reserved2801;	//0xC4F42C6C
	UINT32                                                 reserved2802;	//0xC4F42C70
	UINT32                                                 reserved2803;	//0xC4F42C74
	UINT32                                                 reserved2804;	//0xC4F42C78
	UINT32                                                 reserved2805;	//0xC4F42C7C
	UINT32                                                 reserved2806;	//0xC4F42C80
	UINT32                                                 reserved2807;	//0xC4F42C84
	UINT32                                                 reserved2808;	//0xC4F42C88
	UINT32                                                 reserved2809;	//0xC4F42C8C
	UINT32                                                 reserved2810;	//0xC4F42C90
	UINT32                                                 reserved2811;	//0xC4F42C94
	UINT32                                                 reserved2812;	//0xC4F42C98
	UINT32                                                 reserved2813;	//0xC4F42C9C
	UINT32                                                 reserved2814;	//0xC4F42CA0
	UINT32                                                 reserved2815;	//0xC4F42CA4
	UINT32                                                 reserved2816;	//0xC4F42CA8
	UINT32                                                 reserved2817;	//0xC4F42CAC
	UINT32                                                 reserved2818;	//0xC4F42CB0
	UINT32                                                 reserved2819;	//0xC4F42CB4
	UINT32                                                 reserved2820;	//0xC4F42CB8
	UINT32                                                 reserved2821;	//0xC4F42CBC
	UINT32                                                 reserved2822;	//0xC4F42CC0
	UINT32                                                 reserved2823;	//0xC4F42CC4
	UINT32                                                 reserved2824;	//0xC4F42CC8
	UINT32                                                 reserved2825;	//0xC4F42CCC
	UINT32                                                 reserved2826;	//0xC4F42CD0
	UINT32                                                 reserved2827;	//0xC4F42CD4
	UINT32                                                 reserved2828;	//0xC4F42CD8
	UINT32                                                 reserved2829;	//0xC4F42CDC
	UINT32                                                 reserved2830;	//0xC4F42CE0
	UINT32                                                 reserved2831;	//0xC4F42CE4
	UINT32                                                 reserved2832;	//0xC4F42CE8
	UINT32                                                 reserved2833;	//0xC4F42CEC
	UINT32                                                 reserved2834;	//0xC4F42CF0
	UINT32                                                 reserved2835;	//0xC4F42CF4
	UINT32                                                 reserved2836;	//0xC4F42CF8
	UINT32                                                 reserved2837;	//0xC4F42CFC
	UINT32                                                 reserved2838;	//0xC4F42D00
	UINT32                                                 reserved2839;	//0xC4F42D04
	UINT32                                                 reserved2840;	//0xC4F42D08
	UINT32                                                 reserved2841;	//0xC4F42D0C
	UINT32                                                 reserved2842;	//0xC4F42D10
	UINT32                                                 reserved2843;	//0xC4F42D14
	UINT32                                                 reserved2844;	//0xC4F42D18
	UINT32                                                 reserved2845;	//0xC4F42D1C
	UINT32                                                 reserved2846;	//0xC4F42D20
	UINT32                                                 reserved2847;	//0xC4F42D24
	UINT32                                                 reserved2848;	//0xC4F42D28
	UINT32                                                 reserved2849;	//0xC4F42D2C
	UINT32                                                 reserved2850;	//0xC4F42D30
	UINT32                                                 reserved2851;	//0xC4F42D34
	UINT32                                                 reserved2852;	//0xC4F42D38
	UINT32                                                 reserved2853;	//0xC4F42D3C
	UINT32                                                 reserved2854;	//0xC4F42D40
	UINT32                                                 reserved2855;	//0xC4F42D44
	UINT32                                                 reserved2856;	//0xC4F42D48
	UINT32                                                 reserved2857;	//0xC4F42D4C
	UINT32                                                 reserved2858;	//0xC4F42D50
	UINT32                                                 reserved2859;	//0xC4F42D54
	UINT32                                                 reserved2860;	//0xC4F42D58
	UINT32                                                 reserved2861;	//0xC4F42D5C
	UINT32                                                 reserved2862;	//0xC4F42D60
	UINT32                                                 reserved2863;	//0xC4F42D64
	UINT32                                                 reserved2864;	//0xC4F42D68
	UINT32                                                 reserved2865;	//0xC4F42D6C
	UINT32                                                 reserved2866;	//0xC4F42D70
	UINT32                                                 reserved2867;	//0xC4F42D74
	UINT32                                                 reserved2868;	//0xC4F42D78
	UINT32                                                 reserved2869;	//0xC4F42D7C
	UINT32                                                 reserved2870;	//0xC4F42D80
	UINT32                                                 reserved2871;	//0xC4F42D84
	UINT32                                                 reserved2872;	//0xC4F42D88
	UINT32                                                 reserved2873;	//0xC4F42D8C
	UINT32                                                 reserved2874;	//0xC4F42D90
	UINT32                                                 reserved2875;	//0xC4F42D94
	UINT32                                                 reserved2876;	//0xC4F42D98
	UINT32                                                 reserved2877;	//0xC4F42D9C
	UINT32                                                 reserved2878;	//0xC4F42DA0
	UINT32                                                 reserved2879;	//0xC4F42DA4
	UINT32                                                 reserved2880;	//0xC4F42DA8
	UINT32                                                 reserved2881;	//0xC4F42DAC
	UINT32                                                 reserved2882;	//0xC4F42DB0
	UINT32                                                 reserved2883;	//0xC4F42DB4
	UINT32                                                 reserved2884;	//0xC4F42DB8
	UINT32                                                 reserved2885;	//0xC4F42DBC
	UINT32                                                 reserved2886;	//0xC4F42DC0
	UINT32                                                 reserved2887;	//0xC4F42DC4
	UINT32                                                 reserved2888;	//0xC4F42DC8
	UINT32                                                 reserved2889;	//0xC4F42DCC
	UINT32                                                 reserved2890;	//0xC4F42DD0
	UINT32                                                 reserved2891;	//0xC4F42DD4
	UINT32                                                 reserved2892;	//0xC4F42DD8
	UINT32                                                 reserved2893;	//0xC4F42DDC
	UINT32                                                 reserved2894;	//0xC4F42DE0
	UINT32                                                 reserved2895;	//0xC4F42DE4
	UINT32                                                 reserved2896;	//0xC4F42DE8
	UINT32                                                 reserved2897;	//0xC4F42DEC
	UINT32                                                 reserved2898;	//0xC4F42DF0
	UINT32                                                 reserved2899;	//0xC4F42DF4
	UINT32                                                 reserved2900;	//0xC4F42DF8
	UINT32                                                 reserved2901;	//0xC4F42DFC
	UINT32                                                 reserved2902;	//0xC4F42E00
	UINT32                                                 reserved2903;	//0xC4F42E04
	UINT32                                                 reserved2904;	//0xC4F42E08
	UINT32                                                 reserved2905;	//0xC4F42E0C
	UINT32                                                 reserved2906;	//0xC4F42E10
	UINT32                                                 reserved2907;	//0xC4F42E14
	UINT32                                                 reserved2908;	//0xC4F42E18
	UINT32                                                 reserved2909;	//0xC4F42E1C
	UINT32                                                 reserved2910;	//0xC4F42E20
	UINT32                                                 reserved2911;	//0xC4F42E24
	UINT32                                                 reserved2912;	//0xC4F42E28
	UINT32                                                 reserved2913;	//0xC4F42E2C
	UINT32                                                 reserved2914;	//0xC4F42E30
	UINT32                                                 reserved2915;	//0xC4F42E34
	UINT32                                                 reserved2916;	//0xC4F42E38
	UINT32                                                 reserved2917;	//0xC4F42E3C
	UINT32                                                 reserved2918;	//0xC4F42E40
	UINT32                                                 reserved2919;	//0xC4F42E44
	UINT32                                                 reserved2920;	//0xC4F42E48
	UINT32                                                 reserved2921;	//0xC4F42E4C
	UINT32                                                 reserved2922;	//0xC4F42E50
	UINT32                                                 reserved2923;	//0xC4F42E54
	UINT32                                                 reserved2924;	//0xC4F42E58
	UINT32                                                 reserved2925;	//0xC4F42E5C
	UINT32                                                 reserved2926;	//0xC4F42E60
	UINT32                                                 reserved2927;	//0xC4F42E64
	UINT32                                                 reserved2928;	//0xC4F42E68
	UINT32                                                 reserved2929;	//0xC4F42E6C
	UINT32                                                 reserved2930;	//0xC4F42E70
	UINT32                                                 reserved2931;	//0xC4F42E74
	UINT32                                                 reserved2932;	//0xC4F42E78
	UINT32                                                 reserved2933;	//0xC4F42E7C
	UINT32                                                 reserved2934;	//0xC4F42E80
	UINT32                                                 reserved2935;	//0xC4F42E84
	UINT32                                                 reserved2936;	//0xC4F42E88
	UINT32                                                 reserved2937;	//0xC4F42E8C
	UINT32                                                 reserved2938;	//0xC4F42E90
	UINT32                                                 reserved2939;	//0xC4F42E94
	UINT32                                                 reserved2940;	//0xC4F42E98
	UINT32                                                 reserved2941;	//0xC4F42E9C
	UINT32                                                 reserved2942;	//0xC4F42EA0
	UINT32                                                 reserved2943;	//0xC4F42EA4
	UINT32                                                 reserved2944;	//0xC4F42EA8
	UINT32                                                 reserved2945;	//0xC4F42EAC
	UINT32                                                 reserved2946;	//0xC4F42EB0
	UINT32                                                 reserved2947;	//0xC4F42EB4
	UINT32                                                 reserved2948;	//0xC4F42EB8
	UINT32                                                 reserved2949;	//0xC4F42EBC
	UINT32                                                 reserved2950;	//0xC4F42EC0
	UINT32                                                 reserved2951;	//0xC4F42EC4
	UINT32                                                 reserved2952;	//0xC4F42EC8
	UINT32                                                 reserved2953;	//0xC4F42ECC
	UINT32                                                 reserved2954;	//0xC4F42ED0
	UINT32                                                 reserved2955;	//0xC4F42ED4
	UINT32                                                 reserved2956;	//0xC4F42ED8
	UINT32                                                 reserved2957;	//0xC4F42EDC
	UINT32                                                 reserved2958;	//0xC4F42EE0
	UINT32                                                 reserved2959;	//0xC4F42EE4
	UINT32                                                 reserved2960;	//0xC4F42EE8
	UINT32                                                 reserved2961;	//0xC4F42EEC
	UINT32                                                 reserved2962;	//0xC4F42EF0
	UINT32                                                 reserved2963;	//0xC4F42EF4
	UINT32                                                 reserved2964;	//0xC4F42EF8
	UINT32                                                 reserved2965;	//0xC4F42EFC
	UINT32                                                 reserved2966;	//0xC4F42F00
	UINT32                                                 reserved2967;	//0xC4F42F04
	UINT32                                                 reserved2968;	//0xC4F42F08
	UINT32                                                 reserved2969;	//0xC4F42F0C
	UINT32                                                 reserved2970;	//0xC4F42F10
	UINT32                                                 reserved2971;	//0xC4F42F14
	UINT32                                                 reserved2972;	//0xC4F42F18
	UINT32                                                 reserved2973;	//0xC4F42F1C
	UINT32                                                 reserved2974;	//0xC4F42F20
	UINT32                                                 reserved2975;	//0xC4F42F24
	UINT32                                                 reserved2976;	//0xC4F42F28
	UINT32                                                 reserved2977;	//0xC4F42F2C
	UINT32                                                 reserved2978;	//0xC4F42F30
	UINT32                                                 reserved2979;	//0xC4F42F34
	UINT32                                                 reserved2980;	//0xC4F42F38
	UINT32                                                 reserved2981;	//0xC4F42F3C
	UINT32                                                 reserved2982;	//0xC4F42F40
	UINT32                                                 reserved2983;	//0xC4F42F44
	UINT32                                                 reserved2984;	//0xC4F42F48
	UINT32                                                 reserved2985;	//0xC4F42F4C
	UINT32                                                 reserved2986;	//0xC4F42F50
	UINT32                                                 reserved2987;	//0xC4F42F54
	UINT32                                                 reserved2988;	//0xC4F42F58
	UINT32                                                 reserved2989;	//0xC4F42F5C
	UINT32                                                 reserved2990;	//0xC4F42F60
	UINT32                                                 reserved2991;	//0xC4F42F64
	UINT32                                                 reserved2992;	//0xC4F42F68
	UINT32                                                 reserved2993;	//0xC4F42F6C
	UINT32                                                 reserved2994;	//0xC4F42F70
	UINT32                                                 reserved2995;	//0xC4F42F74
	UINT32                                                 reserved2996;	//0xC4F42F78
	UINT32                                                 reserved2997;	//0xC4F42F7C
	UINT32                                                 reserved2998;	//0xC4F42F80
	UINT32                                                 reserved2999;	//0xC4F42F84
	UINT32                                                 reserved3000;	//0xC4F42F88
	UINT32                                                 reserved3001;	//0xC4F42F8C
	UINT32                                                 reserved3002;	//0xC4F42F90
	UINT32                                                 reserved3003;	//0xC4F42F94
	UINT32                                                 reserved3004;	//0xC4F42F98
	UINT32                                                 reserved3005;	//0xC4F42F9C
	UINT32                                                 reserved3006;	//0xC4F42FA0
	UINT32                                                 reserved3007;	//0xC4F42FA4
	UINT32                                                 reserved3008;	//0xC4F42FA8
	UINT32                                                 reserved3009;	//0xC4F42FAC
	UINT32                                                 reserved3010;	//0xC4F42FB0
	UINT32                                                 reserved3011;	//0xC4F42FB4
	UINT32                                                 reserved3012;	//0xC4F42FB8
	UINT32                                                 reserved3013;	//0xC4F42FBC
	UINT32                                                 reserved3014;	//0xC4F42FC0
	UINT32                                                 reserved3015;	//0xC4F42FC4
	UINT32                                                 reserved3016;	//0xC4F42FC8
	UINT32                                                 reserved3017;	//0xC4F42FCC
	UINT32                                                 reserved3018;	//0xC4F42FD0
	UINT32                                                 reserved3019;	//0xC4F42FD4
	UINT32                                                 reserved3020;	//0xC4F42FD8
	UINT32                                                 reserved3021;	//0xC4F42FDC
	UINT32                                                 reserved3022;	//0xC4F42FE0
	UINT32                                                 reserved3023;	//0xC4F42FE4
	UINT32                                                 reserved3024;	//0xC4F42FE8
	UINT32                                                 reserved3025;	//0xC4F42FEC
	UINT32                                                 reserved3026;	//0xC4F42FF0
	UINT32                                                 reserved3027;	//0xC4F42FF4
	UINT32                                                 reserved3028;	//0xC4F42FF8
	UINT32                                                 reserved3029;	//0xC4F42FFC
	REG_DDRC_M0_LPD4_MAIN_FSM_INIT_0_T             lpd4_main_fsm_init_0;	//0xC4F43000
	REG_DDRC_M0_LPD4_MAIN_FSM_INIT_1_T             lpd4_main_fsm_init_1;	//0xC4F43004
	REG_DDRC_M0_LPD4_MAIN_FSM_INIT_2_T             lpd4_main_fsm_init_2;	//0xC4F43008
	REG_DDRC_M0_LPD4_MAIN_FSM_CTRL_T                 lpd4_main_fsm_ctrl;	//0xC4F4300C
	REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_0_T     lpd4_main_fsm_dir_ctrl_0;	//0xC4F43010
	REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_1_T     lpd4_main_fsm_dir_ctrl_1;	//0xC4F43014
	REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_2_T     lpd4_main_fsm_dir_ctrl_2;	//0xC4F43018
	REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_3_T     lpd4_main_fsm_dir_ctrl_3;	//0xC4F4301C
	REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_4_T     lpd4_main_fsm_dir_ctrl_4;	//0xC4F43020
	REG_DDRC_M0_LPD4_MAIN_FSM_DFS_MRW_T           lpd4_main_fsm_dfs_mrw;	//0xC4F43024
	REG_DDRC_M0_LPD4_MAIN_FSM_CTRLUPD_T           lpd4_main_fsm_ctrlupd;	//0xC4F43028
	REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_0_T     lpd4_main_fsm_mpc_fifo_0;	//0xC4F4302C
	REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_1_T     lpd4_main_fsm_mpc_fifo_1;	//0xC4F43030
	REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_2_T     lpd4_main_fsm_mpc_fifo_2;	//0xC4F43034
	REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_3_T     lpd4_main_fsm_mpc_fifo_3;	//0xC4F43038
	REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_4_T     lpd4_main_fsm_mpc_fifo_4;	//0xC4F4303C
	UINT32                                                 reserved3030;	//0xC4F43040
	UINT32                                                 reserved3031;	//0xC4F43044
	UINT32                                                 reserved3032;	//0xC4F43048
	UINT32                                                 reserved3033;	//0xC4F4304C
	REG_DDRC_M0_LPD4_MR_CTRL_0_T                         lpd4_mr_ctrl_0;	//0xC4F43050
	REG_DDRC_M0_LPD4_MR_CTRL_1_T                         lpd4_mr_ctrl_1;	//0xC4F43054
	REG_DDRC_M0_LPD4_MR_CTRL_2_T                         lpd4_mr_ctrl_2;	//0xC4F43058
	UINT32                                                 reserved3034;	//0xC4F4305C
	REG_DDRC_M0_LPD4_REF_REQ_CTRL_T                   lpd4_ref_req_ctrl;	//0xC4F43060
	UINT32                                                 reserved3035;	//0xC4F43064
	UINT32                                                 reserved3036;	//0xC4F43068
	UINT32                                                 reserved3037;	//0xC4F4306C
	REG_DDRC_M0_LPD4_REF_CTRL_T                           lpd4_ref_ctrl;	//0xC4F43070
	UINT32                                                 reserved3038;	//0xC4F43074
	UINT32                                                 reserved3039;	//0xC4F43078
	UINT32                                                 reserved3040;	//0xC4F4307C
	REG_DDRC_M0_LPD4_BANK_FSM_T                           lpd4_bank_fsm;	//0xC4F43080
	UINT32                                                 reserved3041;	//0xC4F43084
	UINT32                                                 reserved3042;	//0xC4F43088
	UINT32                                                 reserved3043;	//0xC4F4308C
	UINT32                                                 reserved3044;	//0xC4F43090
	UINT32                                                 reserved3045;	//0xC4F43094
	UINT32                                                 reserved3046;	//0xC4F43098
	UINT32                                                 reserved3047;	//0xC4F4309C
	REG_DDRC_M0_LPD4_BANK_STATUS_T                     lpd4_bank_status;	//0xC4F430A0
	UINT32                                                 reserved3048;	//0xC4F430A4
	UINT32                                                 reserved3049;	//0xC4F430A8
	UINT32                                                 reserved3050;	//0xC4F430AC
	UINT32                                                 reserved3051;	//0xC4F430B0
	UINT32                                                 reserved3052;	//0xC4F430B4
	UINT32                                                 reserved3053;	//0xC4F430B8
	UINT32                                                 reserved3054;	//0xC4F430BC
	REG_DDRC_M0_LPD4_PHY_IF_T                               lpd4_phy_if;	//0xC4F430C0
	UINT32                                                 reserved3055;	//0xC4F430C4
	UINT32                                                 reserved3056;	//0xC4F430C8
	UINT32                                                 reserved3057;	//0xC4F430CC
	UINT32                                                 reserved3058;	//0xC4F430D0
	UINT32                                                 reserved3059;	//0xC4F430D4
	UINT32                                                 reserved3060;	//0xC4F430D8
	UINT32                                                 reserved3061;	//0xC4F430DC
	UINT32                                                 reserved3062;	//0xC4F430E0
	UINT32                                                 reserved3063;	//0xC4F430E4
	UINT32                                                 reserved3064;	//0xC4F430E8
	UINT32                                                 reserved3065;	//0xC4F430EC
	UINT32                                                 reserved3066;	//0xC4F430F0
	UINT32                                                 reserved3067;	//0xC4F430F4
	UINT32                                                 reserved3068;	//0xC4F430F8
	UINT32                                                 reserved3069;	//0xC4F430FC
	REG_DDRC_M0_LPD4_DFS0_MR_0_CH0_T                 lpd4_dfs0_mr_0_ch0;	//0xC4F43100
	REG_DDRC_M0_LPD4_DFS0_MR_1_CH0_T                 lpd4_dfs0_mr_1_ch0;	//0xC4F43104
	REG_DDRC_M0_LPD4_DFS0_MR_2_CH0_T                 lpd4_dfs0_mr_2_ch0;	//0xC4F43108
	REG_DDRC_M0_LPD4_DFS0_MR_3_CH0_T                 lpd4_dfs0_mr_3_ch0;	//0xC4F4310C
	REG_DDRC_M0_LPD4_DFS0_MR_4_CH0_T                 lpd4_dfs0_mr_4_ch0;	//0xC4F43110
	REG_DDRC_M0_LPD4_DFS0_MR_5_CH0_T                 lpd4_dfs0_mr_5_ch0;	//0xC4F43114
	REG_DDRC_M0_LPD4_DFS0_MR_6_CH0_T                 lpd4_dfs0_mr_6_ch0;	//0xC4F43118
	UINT32                                                 reserved3070;	//0xC4F4311C
	REG_DDRC_M0_LPD4_DFS0_MR_0_CH1_T                 lpd4_dfs0_mr_0_ch1;	//0xC4F43120
	REG_DDRC_M0_LPD4_DFS0_MR_1_CH1_T                 lpd4_dfs0_mr_1_ch1;	//0xC4F43124
	REG_DDRC_M0_LPD4_DFS0_MR_2_CH1_T                 lpd4_dfs0_mr_2_ch1;	//0xC4F43128
	REG_DDRC_M0_LPD4_DFS0_MR_3_CH1_T                 lpd4_dfs0_mr_3_ch1;	//0xC4F4312C
	REG_DDRC_M0_LPD4_DFS0_MR_4_CH1_T                 lpd4_dfs0_mr_4_ch1;	//0xC4F43130
	REG_DDRC_M0_LPD4_DFS0_MR_5_CH1_T                 lpd4_dfs0_mr_5_ch1;	//0xC4F43134
	REG_DDRC_M0_LPD4_DFS0_MR_6_CH1_T                 lpd4_dfs0_mr_6_ch1;	//0xC4F43138
	UINT32                                                 reserved3071;	//0xC4F4313C
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_0_T             lpd4_dfs0_main_fsm_0;	//0xC4F43140
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_1_T             lpd4_dfs0_main_fsm_1;	//0xC4F43144
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_2_T             lpd4_dfs0_main_fsm_2;	//0xC4F43148
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_3_T             lpd4_dfs0_main_fsm_3;	//0xC4F4314C
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_4_T             lpd4_dfs0_main_fsm_4;	//0xC4F43150
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_5_T             lpd4_dfs0_main_fsm_5;	//0xC4F43154
	UINT32                                                 reserved3072;	//0xC4F43158
	UINT32                                                 reserved3073;	//0xC4F4315C
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_0_T     lpd4_dfs0_ref_req_ctrl_0;	//0xC4F43160
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_1_T     lpd4_dfs0_ref_req_ctrl_1;	//0xC4F43164
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_2_T     lpd4_dfs0_ref_req_ctrl_2;	//0xC4F43168
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_3_T     lpd4_dfs0_ref_req_ctrl_3;	//0xC4F4316C
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_4_T     lpd4_dfs0_ref_req_ctrl_4;	//0xC4F43170
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_5_T     lpd4_dfs0_ref_req_ctrl_5;	//0xC4F43174
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_6_T     lpd4_dfs0_ref_req_ctrl_6;	//0xC4F43178
	UINT32                                                 reserved3074;	//0xC4F4317C
	UINT32                                                 reserved3075;	//0xC4F43180
	UINT32                                                 reserved3076;	//0xC4F43184
	UINT32                                                 reserved3077;	//0xC4F43188
	UINT32                                                 reserved3078;	//0xC4F4318C
	REG_DDRC_M0_LPD4_DFS0_REF_CTRL_T                 lpd4_dfs0_ref_ctrl;	//0xC4F43190
	UINT32                                                 reserved3079;	//0xC4F43194
	UINT32                                                 reserved3080;	//0xC4F43198
	UINT32                                                 reserved3081;	//0xC4F4319C
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_0_T       lpd4_dfs0_bank_status_0;	//0xC4F431A0
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_1_T       lpd4_dfs0_bank_status_1;	//0xC4F431A4
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_2_T       lpd4_dfs0_bank_status_2;	//0xC4F431A8
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_3_T       lpd4_dfs0_bank_status_3;	//0xC4F431AC
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_4_T       lpd4_dfs0_bank_status_4;	//0xC4F431B0
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_5_T       lpd4_dfs0_bank_status_5;	//0xC4F431B4
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_6_T       lpd4_dfs0_bank_status_6;	//0xC4F431B8
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_7_T       lpd4_dfs0_bank_status_7;	//0xC4F431BC
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_8_T       lpd4_dfs0_bank_status_8;	//0xC4F431C0
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_9_T       lpd4_dfs0_bank_status_9;	//0xC4F431C4
	UINT32                                                 reserved3082;	//0xC4F431C8
	UINT32                                                 reserved3083;	//0xC4F431CC
	UINT32                                                 reserved3084;	//0xC4F431D0
	UINT32                                                 reserved3085;	//0xC4F431D4
	UINT32                                                 reserved3086;	//0xC4F431D8
	UINT32                                                 reserved3087;	//0xC4F431DC
	REG_DDRC_M0_LPD4_DFS0_PHY_IF_T                     lpd4_dfs0_phy_if;	//0xC4F431E0
	UINT32                                                 reserved3088;	//0xC4F431E4
	UINT32                                                 reserved3089;	//0xC4F431E8
	UINT32                                                 reserved3090;	//0xC4F431EC
	UINT32                                                 reserved3091;	//0xC4F431F0
	UINT32                                                 reserved3092;	//0xC4F431F4
	UINT32                                                 reserved3093;	//0xC4F431F8
	UINT32                                                 reserved3094;	//0xC4F431FC
	REG_DDRC_M0_LPD4_DFS1_MR_0_CH0_T                 lpd4_dfs1_mr_0_ch0;	//0xC4F43200
	REG_DDRC_M0_LPD4_DFS1_MR_1_CH0_T                 lpd4_dfs1_mr_1_ch0;	//0xC4F43204
	REG_DDRC_M0_LPD4_DFS1_MR_2_CH0_T                 lpd4_dfs1_mr_2_ch0;	//0xC4F43208
	REG_DDRC_M0_LPD4_DFS1_MR_3_CH0_T                 lpd4_dfs1_mr_3_ch0;	//0xC4F4320C
	REG_DDRC_M0_LPD4_DFS1_MR_4_CH0_T                 lpd4_dfs1_mr_4_ch0;	//0xC4F43210
	REG_DDRC_M0_LPD4_DFS1_MR_5_CH0_T                 lpd4_dfs1_mr_5_ch0;	//0xC4F43214
	REG_DDRC_M0_LPD4_DFS1_MR_6_CH0_T                 lpd4_dfs1_mr_6_ch0;	//0xC4F43218
	UINT32                                                 reserved3095;	//0xC4F4321C
	REG_DDRC_M0_LPD4_DFS1_MR_0_CH1_T                 lpd4_dfs1_mr_0_ch1;	//0xC4F43220
	REG_DDRC_M0_LPD4_DFS1_MR_1_CH1_T                 lpd4_dfs1_mr_1_ch1;	//0xC4F43224
	REG_DDRC_M0_LPD4_DFS1_MR_2_CH1_T                 lpd4_dfs1_mr_2_ch1;	//0xC4F43228
	REG_DDRC_M0_LPD4_DFS1_MR_3_CH1_T                 lpd4_dfs1_mr_3_ch1;	//0xC4F4322C
	REG_DDRC_M0_LPD4_DFS1_MR_4_CH1_T                 lpd4_dfs1_mr_4_ch1;	//0xC4F43230
	REG_DDRC_M0_LPD4_DFS1_MR_5_CH1_T                 lpd4_dfs1_mr_5_ch1;	//0xC4F43234
	REG_DDRC_M0_LPD4_DFS1_MR_6_CH1_T                 lpd4_dfs1_mr_6_ch1;	//0xC4F43238
	UINT32                                                 reserved3096;	//0xC4F4323C
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_0_T             lpd4_dfs1_main_fsm_0;	//0xC4F43240
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_1_T             lpd4_dfs1_main_fsm_1;	//0xC4F43244
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_2_T             lpd4_dfs1_main_fsm_2;	//0xC4F43248
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_3_T             lpd4_dfs1_main_fsm_3;	//0xC4F4324C
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_4_T             lpd4_dfs1_main_fsm_4;	//0xC4F43250
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_5_T             lpd4_dfs1_main_fsm_5;	//0xC4F43254
	UINT32                                                 reserved3097;	//0xC4F43258
	UINT32                                                 reserved3098;	//0xC4F4325C
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_0_T     lpd4_dfs1_ref_req_ctrl_0;	//0xC4F43260
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_1_T     lpd4_dfs1_ref_req_ctrl_1;	//0xC4F43264
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_2_T     lpd4_dfs1_ref_req_ctrl_2;	//0xC4F43268
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_3_T     lpd4_dfs1_ref_req_ctrl_3;	//0xC4F4326C
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_4_T     lpd4_dfs1_ref_req_ctrl_4;	//0xC4F43270
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_5_T     lpd4_dfs1_ref_req_ctrl_5;	//0xC4F43274
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_6_T     lpd4_dfs1_ref_req_ctrl_6;	//0xC4F43278
	UINT32                                                 reserved3099;	//0xC4F4327C
	UINT32                                                 reserved3100;	//0xC4F43280
	UINT32                                                 reserved3101;	//0xC4F43284
	UINT32                                                 reserved3102;	//0xC4F43288
	UINT32                                                 reserved3103;	//0xC4F4328C
	REG_DDRC_M0_LPD4_DFS1_REF_CTRL_T                 lpd4_dfs1_ref_ctrl;	//0xC4F43290
	UINT32                                                 reserved3104;	//0xC4F43294
	UINT32                                                 reserved3105;	//0xC4F43298
	UINT32                                                 reserved3106;	//0xC4F4329C
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_0_T       lpd4_dfs1_bank_status_0;	//0xC4F432A0
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_1_T       lpd4_dfs1_bank_status_1;	//0xC4F432A4
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_2_T       lpd4_dfs1_bank_status_2;	//0xC4F432A8
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_3_T       lpd4_dfs1_bank_status_3;	//0xC4F432AC
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_4_T       lpd4_dfs1_bank_status_4;	//0xC4F432B0
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_5_T       lpd4_dfs1_bank_status_5;	//0xC4F432B4
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_6_T       lpd4_dfs1_bank_status_6;	//0xC4F432B8
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_7_T       lpd4_dfs1_bank_status_7;	//0xC4F432BC
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_8_T       lpd4_dfs1_bank_status_8;	//0xC4F432C0
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_9_T       lpd4_dfs1_bank_status_9;	//0xC4F432C4
	UINT32                                                 reserved3107;	//0xC4F432C8
	UINT32                                                 reserved3108;	//0xC4F432CC
	UINT32                                                 reserved3109;	//0xC4F432D0
	UINT32                                                 reserved3110;	//0xC4F432D4
	UINT32                                                 reserved3111;	//0xC4F432D8
	UINT32                                                 reserved3112;	//0xC4F432DC
	REG_DDRC_M0_LPD4_DFS1_PHY_IF_T                     lpd4_dfs1_phy_if;	//0xC4F432E0
	UINT32                                                 reserved3113;	//0xC4F432E4
	UINT32                                                 reserved3114;	//0xC4F432E8
	UINT32                                                 reserved3115;	//0xC4F432EC
	UINT32                                                 reserved3116;	//0xC4F432F0
	UINT32                                                 reserved3117;	//0xC4F432F4
	UINT32                                                 reserved3118;	//0xC4F432F8
	UINT32                                                 reserved3119;	//0xC4F432FC
	REG_DDRC_M0_LPD4_DFS2_MR_0_CH0_T                 lpd4_dfs2_mr_0_ch0;	//0xC4F43300
	REG_DDRC_M0_LPD4_DFS2_MR_1_CH0_T                 lpd4_dfs2_mr_1_ch0;	//0xC4F43304
	REG_DDRC_M0_LPD4_DFS2_MR_2_CH0_T                 lpd4_dfs2_mr_2_ch0;	//0xC4F43308
	REG_DDRC_M0_LPD4_DFS2_MR_3_CH0_T                 lpd4_dfs2_mr_3_ch0;	//0xC4F4330C
	REG_DDRC_M0_LPD4_DFS2_MR_4_CH0_T                 lpd4_dfs2_mr_4_ch0;	//0xC4F43310
	REG_DDRC_M0_LPD4_DFS2_MR_5_CH0_T                 lpd4_dfs2_mr_5_ch0;	//0xC4F43314
	REG_DDRC_M0_LPD4_DFS2_MR_6_CH0_T                 lpd4_dfs2_mr_6_ch0;	//0xC4F43318
	UINT32                                                 reserved3120;	//0xC4F4331C
	REG_DDRC_M0_LPD4_DFS2_MR_0_CH1_T                 lpd4_dfs2_mr_0_ch1;	//0xC4F43320
	REG_DDRC_M0_LPD4_DFS2_MR_1_CH1_T                 lpd4_dfs2_mr_1_ch1;	//0xC4F43324
	REG_DDRC_M0_LPD4_DFS2_MR_2_CH1_T                 lpd4_dfs2_mr_2_ch1;	//0xC4F43328
	REG_DDRC_M0_LPD4_DFS2_MR_3_CH1_T                 lpd4_dfs2_mr_3_ch1;	//0xC4F4332C
	REG_DDRC_M0_LPD4_DFS2_MR_4_CH1_T                 lpd4_dfs2_mr_4_ch1;	//0xC4F43330
	REG_DDRC_M0_LPD4_DFS2_MR_5_CH1_T                 lpd4_dfs2_mr_5_ch1;	//0xC4F43334
	REG_DDRC_M0_LPD4_DFS2_MR_6_CH1_T                 lpd4_dfs2_mr_6_ch1;	//0xC4F43338
	UINT32                                                 reserved3121;	//0xC4F4333C
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_0_T             lpd4_dfs2_main_fsm_0;	//0xC4F43340
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_1_T             lpd4_dfs2_main_fsm_1;	//0xC4F43344
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_2_T             lpd4_dfs2_main_fsm_2;	//0xC4F43348
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_3_T             lpd4_dfs2_main_fsm_3;	//0xC4F4334C
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_4_T             lpd4_dfs2_main_fsm_4;	//0xC4F43350
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_5_T             lpd4_dfs2_main_fsm_5;	//0xC4F43354
	UINT32                                                 reserved3122;	//0xC4F43358
	UINT32                                                 reserved3123;	//0xC4F4335C
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_0_T     lpd4_dfs2_ref_req_ctrl_0;	//0xC4F43360
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_1_T     lpd4_dfs2_ref_req_ctrl_1;	//0xC4F43364
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_2_T     lpd4_dfs2_ref_req_ctrl_2;	//0xC4F43368
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_3_T     lpd4_dfs2_ref_req_ctrl_3;	//0xC4F4336C
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_4_T     lpd4_dfs2_ref_req_ctrl_4;	//0xC4F43370
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_5_T     lpd4_dfs2_ref_req_ctrl_5;	//0xC4F43374
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_6_T     lpd4_dfs2_ref_req_ctrl_6;	//0xC4F43378
	UINT32                                                 reserved3124;	//0xC4F4337C
	UINT32                                                 reserved3125;	//0xC4F43380
	UINT32                                                 reserved3126;	//0xC4F43384
	UINT32                                                 reserved3127;	//0xC4F43388
	UINT32                                                 reserved3128;	//0xC4F4338C
	REG_DDRC_M0_LPD4_DFS2_REF_CTRL_T                 lpd4_dfs2_ref_ctrl;	//0xC4F43390
	UINT32                                                 reserved3129;	//0xC4F43394
	UINT32                                                 reserved3130;	//0xC4F43398
	UINT32                                                 reserved3131;	//0xC4F4339C
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_0_T       lpd4_dfs2_bank_status_0;	//0xC4F433A0
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_1_T       lpd4_dfs2_bank_status_1;	//0xC4F433A4
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_2_T       lpd4_dfs2_bank_status_2;	//0xC4F433A8
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_3_T       lpd4_dfs2_bank_status_3;	//0xC4F433AC
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_4_T       lpd4_dfs2_bank_status_4;	//0xC4F433B0
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_5_T       lpd4_dfs2_bank_status_5;	//0xC4F433B4
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_6_T       lpd4_dfs2_bank_status_6;	//0xC4F433B8
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_7_T       lpd4_dfs2_bank_status_7;	//0xC4F433BC
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_8_T       lpd4_dfs2_bank_status_8;	//0xC4F433C0
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_9_T       lpd4_dfs2_bank_status_9;	//0xC4F433C4
	UINT32                                                 reserved3132;	//0xC4F433C8
	UINT32                                                 reserved3133;	//0xC4F433CC
	UINT32                                                 reserved3134;	//0xC4F433D0
	UINT32                                                 reserved3135;	//0xC4F433D4
	UINT32                                                 reserved3136;	//0xC4F433D8
	UINT32                                                 reserved3137;	//0xC4F433DC
	REG_DDRC_M0_LPD4_DFS2_PHY_IF_T                     lpd4_dfs2_phy_if;	//0xC4F433E0
	UINT32                                                 reserved3138;	//0xC4F433E4
	UINT32                                                 reserved3139;	//0xC4F433E8
	UINT32                                                 reserved3140;	//0xC4F433EC
	UINT32                                                 reserved3141;	//0xC4F433F0
	UINT32                                                 reserved3142;	//0xC4F433F4
	UINT32                                                 reserved3143;	//0xC4F433F8
	UINT32                                                 reserved3144;	//0xC4F433FC
	UINT32                                                 reserved3145;	//0xC4F43400
	UINT32                                                 reserved3146;	//0xC4F43404
	UINT32                                                 reserved3147;	//0xC4F43408
	UINT32                                                 reserved3148;	//0xC4F4340C
	UINT32                                                 reserved3149;	//0xC4F43410
	UINT32                                                 reserved3150;	//0xC4F43414
	UINT32                                                 reserved3151;	//0xC4F43418
	UINT32                                                 reserved3152;	//0xC4F4341C
	UINT32                                                 reserved3153;	//0xC4F43420
	UINT32                                                 reserved3154;	//0xC4F43424
	UINT32                                                 reserved3155;	//0xC4F43428
	UINT32                                                 reserved3156;	//0xC4F4342C
	UINT32                                                 reserved3157;	//0xC4F43430
	UINT32                                                 reserved3158;	//0xC4F43434
	UINT32                                                 reserved3159;	//0xC4F43438
	UINT32                                                 reserved3160;	//0xC4F4343C
	UINT32                                                 reserved3161;	//0xC4F43440
	UINT32                                                 reserved3162;	//0xC4F43444
	UINT32                                                 reserved3163;	//0xC4F43448
	UINT32                                                 reserved3164;	//0xC4F4344C
	UINT32                                                 reserved3165;	//0xC4F43450
	UINT32                                                 reserved3166;	//0xC4F43454
	UINT32                                                 reserved3167;	//0xC4F43458
	UINT32                                                 reserved3168;	//0xC4F4345C
	UINT32                                                 reserved3169;	//0xC4F43460
	UINT32                                                 reserved3170;	//0xC4F43464
	UINT32                                                 reserved3171;	//0xC4F43468
	UINT32                                                 reserved3172;	//0xC4F4346C
	UINT32                                                 reserved3173;	//0xC4F43470
	UINT32                                                 reserved3174;	//0xC4F43474
	UINT32                                                 reserved3175;	//0xC4F43478
	UINT32                                                 reserved3176;	//0xC4F4347C
	UINT32                                                 reserved3177;	//0xC4F43480
	UINT32                                                 reserved3178;	//0xC4F43484
	UINT32                                                 reserved3179;	//0xC4F43488
	UINT32                                                 reserved3180;	//0xC4F4348C
	UINT32                                                 reserved3181;	//0xC4F43490
	UINT32                                                 reserved3182;	//0xC4F43494
	UINT32                                                 reserved3183;	//0xC4F43498
	UINT32                                                 reserved3184;	//0xC4F4349C
	UINT32                                                 reserved3185;	//0xC4F434A0
	UINT32                                                 reserved3186;	//0xC4F434A4
	UINT32                                                 reserved3187;	//0xC4F434A8
	UINT32                                                 reserved3188;	//0xC4F434AC
	UINT32                                                 reserved3189;	//0xC4F434B0
	UINT32                                                 reserved3190;	//0xC4F434B4
	UINT32                                                 reserved3191;	//0xC4F434B8
	UINT32                                                 reserved3192;	//0xC4F434BC
	UINT32                                                 reserved3193;	//0xC4F434C0
	UINT32                                                 reserved3194;	//0xC4F434C4
	UINT32                                                 reserved3195;	//0xC4F434C8
	UINT32                                                 reserved3196;	//0xC4F434CC
	UINT32                                                 reserved3197;	//0xC4F434D0
	UINT32                                                 reserved3198;	//0xC4F434D4
	UINT32                                                 reserved3199;	//0xC4F434D8
	UINT32                                                 reserved3200;	//0xC4F434DC
	UINT32                                                 reserved3201;	//0xC4F434E0
	UINT32                                                 reserved3202;	//0xC4F434E4
	UINT32                                                 reserved3203;	//0xC4F434E8
	UINT32                                                 reserved3204;	//0xC4F434EC
	UINT32                                                 reserved3205;	//0xC4F434F0
	UINT32                                                 reserved3206;	//0xC4F434F4
	UINT32                                                 reserved3207;	//0xC4F434F8
	UINT32                                                 reserved3208;	//0xC4F434FC
	UINT32                                                 reserved3209;	//0xC4F43500
	UINT32                                                 reserved3210;	//0xC4F43504
	UINT32                                                 reserved3211;	//0xC4F43508
	UINT32                                                 reserved3212;	//0xC4F4350C
	UINT32                                                 reserved3213;	//0xC4F43510
	UINT32                                                 reserved3214;	//0xC4F43514
	UINT32                                                 reserved3215;	//0xC4F43518
	UINT32                                                 reserved3216;	//0xC4F4351C
	UINT32                                                 reserved3217;	//0xC4F43520
	UINT32                                                 reserved3218;	//0xC4F43524
	UINT32                                                 reserved3219;	//0xC4F43528
	UINT32                                                 reserved3220;	//0xC4F4352C
	UINT32                                                 reserved3221;	//0xC4F43530
	UINT32                                                 reserved3222;	//0xC4F43534
	UINT32                                                 reserved3223;	//0xC4F43538
	UINT32                                                 reserved3224;	//0xC4F4353C
	UINT32                                                 reserved3225;	//0xC4F43540
	UINT32                                                 reserved3226;	//0xC4F43544
	UINT32                                                 reserved3227;	//0xC4F43548
	UINT32                                                 reserved3228;	//0xC4F4354C
	UINT32                                                 reserved3229;	//0xC4F43550
	UINT32                                                 reserved3230;	//0xC4F43554
	UINT32                                                 reserved3231;	//0xC4F43558
	UINT32                                                 reserved3232;	//0xC4F4355C
	UINT32                                                 reserved3233;	//0xC4F43560
	UINT32                                                 reserved3234;	//0xC4F43564
	UINT32                                                 reserved3235;	//0xC4F43568
	UINT32                                                 reserved3236;	//0xC4F4356C
	UINT32                                                 reserved3237;	//0xC4F43570
	UINT32                                                 reserved3238;	//0xC4F43574
	UINT32                                                 reserved3239;	//0xC4F43578
	UINT32                                                 reserved3240;	//0xC4F4357C
	UINT32                                                 reserved3241;	//0xC4F43580
	UINT32                                                 reserved3242;	//0xC4F43584
	UINT32                                                 reserved3243;	//0xC4F43588
	UINT32                                                 reserved3244;	//0xC4F4358C
	UINT32                                                 reserved3245;	//0xC4F43590
	UINT32                                                 reserved3246;	//0xC4F43594
	UINT32                                                 reserved3247;	//0xC4F43598
	UINT32                                                 reserved3248;	//0xC4F4359C
	UINT32                                                 reserved3249;	//0xC4F435A0
	UINT32                                                 reserved3250;	//0xC4F435A4
	UINT32                                                 reserved3251;	//0xC4F435A8
	UINT32                                                 reserved3252;	//0xC4F435AC
	UINT32                                                 reserved3253;	//0xC4F435B0
	UINT32                                                 reserved3254;	//0xC4F435B4
	UINT32                                                 reserved3255;	//0xC4F435B8
	UINT32                                                 reserved3256;	//0xC4F435BC
	UINT32                                                 reserved3257;	//0xC4F435C0
	UINT32                                                 reserved3258;	//0xC4F435C4
	UINT32                                                 reserved3259;	//0xC4F435C8
	UINT32                                                 reserved3260;	//0xC4F435CC
	UINT32                                                 reserved3261;	//0xC4F435D0
	UINT32                                                 reserved3262;	//0xC4F435D4
	UINT32                                                 reserved3263;	//0xC4F435D8
	UINT32                                                 reserved3264;	//0xC4F435DC
	UINT32                                                 reserved3265;	//0xC4F435E0
	UINT32                                                 reserved3266;	//0xC4F435E4
	UINT32                                                 reserved3267;	//0xC4F435E8
	UINT32                                                 reserved3268;	//0xC4F435EC
	UINT32                                                 reserved3269;	//0xC4F435F0
	UINT32                                                 reserved3270;	//0xC4F435F4
	UINT32                                                 reserved3271;	//0xC4F435F8
	UINT32                                                 reserved3272;	//0xC4F435FC
	UINT32                                                 reserved3273;	//0xC4F43600
	UINT32                                                 reserved3274;	//0xC4F43604
	UINT32                                                 reserved3275;	//0xC4F43608
	UINT32                                                 reserved3276;	//0xC4F4360C
	UINT32                                                 reserved3277;	//0xC4F43610
	UINT32                                                 reserved3278;	//0xC4F43614
	UINT32                                                 reserved3279;	//0xC4F43618
	UINT32                                                 reserved3280;	//0xC4F4361C
	UINT32                                                 reserved3281;	//0xC4F43620
	UINT32                                                 reserved3282;	//0xC4F43624
	UINT32                                                 reserved3283;	//0xC4F43628
	UINT32                                                 reserved3284;	//0xC4F4362C
	UINT32                                                 reserved3285;	//0xC4F43630
	UINT32                                                 reserved3286;	//0xC4F43634
	UINT32                                                 reserved3287;	//0xC4F43638
	UINT32                                                 reserved3288;	//0xC4F4363C
	UINT32                                                 reserved3289;	//0xC4F43640
	UINT32                                                 reserved3290;	//0xC4F43644
	UINT32                                                 reserved3291;	//0xC4F43648
	UINT32                                                 reserved3292;	//0xC4F4364C
	UINT32                                                 reserved3293;	//0xC4F43650
	UINT32                                                 reserved3294;	//0xC4F43654
	UINT32                                                 reserved3295;	//0xC4F43658
	UINT32                                                 reserved3296;	//0xC4F4365C
	UINT32                                                 reserved3297;	//0xC4F43660
	UINT32                                                 reserved3298;	//0xC4F43664
	UINT32                                                 reserved3299;	//0xC4F43668
	UINT32                                                 reserved3300;	//0xC4F4366C
	UINT32                                                 reserved3301;	//0xC4F43670
	UINT32                                                 reserved3302;	//0xC4F43674
	UINT32                                                 reserved3303;	//0xC4F43678
	UINT32                                                 reserved3304;	//0xC4F4367C
	UINT32                                                 reserved3305;	//0xC4F43680
	UINT32                                                 reserved3306;	//0xC4F43684
	UINT32                                                 reserved3307;	//0xC4F43688
	UINT32                                                 reserved3308;	//0xC4F4368C
	UINT32                                                 reserved3309;	//0xC4F43690
	UINT32                                                 reserved3310;	//0xC4F43694
	UINT32                                                 reserved3311;	//0xC4F43698
	UINT32                                                 reserved3312;	//0xC4F4369C
	UINT32                                                 reserved3313;	//0xC4F436A0
	UINT32                                                 reserved3314;	//0xC4F436A4
	UINT32                                                 reserved3315;	//0xC4F436A8
	UINT32                                                 reserved3316;	//0xC4F436AC
	UINT32                                                 reserved3317;	//0xC4F436B0
	UINT32                                                 reserved3318;	//0xC4F436B4
	UINT32                                                 reserved3319;	//0xC4F436B8
	UINT32                                                 reserved3320;	//0xC4F436BC
	UINT32                                                 reserved3321;	//0xC4F436C0
	UINT32                                                 reserved3322;	//0xC4F436C4
	UINT32                                                 reserved3323;	//0xC4F436C8
	UINT32                                                 reserved3324;	//0xC4F436CC
	UINT32                                                 reserved3325;	//0xC4F436D0
	UINT32                                                 reserved3326;	//0xC4F436D4
	UINT32                                                 reserved3327;	//0xC4F436D8
	UINT32                                                 reserved3328;	//0xC4F436DC
	UINT32                                                 reserved3329;	//0xC4F436E0
	UINT32                                                 reserved3330;	//0xC4F436E4
	UINT32                                                 reserved3331;	//0xC4F436E8
	UINT32                                                 reserved3332;	//0xC4F436EC
	UINT32                                                 reserved3333;	//0xC4F436F0
	UINT32                                                 reserved3334;	//0xC4F436F4
	UINT32                                                 reserved3335;	//0xC4F436F8
	UINT32                                                 reserved3336;	//0xC4F436FC
	UINT32                                                 reserved3337;	//0xC4F43700
	UINT32                                                 reserved3338;	//0xC4F43704
	UINT32                                                 reserved3339;	//0xC4F43708
	UINT32                                                 reserved3340;	//0xC4F4370C
	UINT32                                                 reserved3341;	//0xC4F43710
	UINT32                                                 reserved3342;	//0xC4F43714
	UINT32                                                 reserved3343;	//0xC4F43718
	UINT32                                                 reserved3344;	//0xC4F4371C
	UINT32                                                 reserved3345;	//0xC4F43720
	UINT32                                                 reserved3346;	//0xC4F43724
	UINT32                                                 reserved3347;	//0xC4F43728
	UINT32                                                 reserved3348;	//0xC4F4372C
	UINT32                                                 reserved3349;	//0xC4F43730
	UINT32                                                 reserved3350;	//0xC4F43734
	UINT32                                                 reserved3351;	//0xC4F43738
	UINT32                                                 reserved3352;	//0xC4F4373C
	UINT32                                                 reserved3353;	//0xC4F43740
	UINT32                                                 reserved3354;	//0xC4F43744
	UINT32                                                 reserved3355;	//0xC4F43748
	UINT32                                                 reserved3356;	//0xC4F4374C
	UINT32                                                 reserved3357;	//0xC4F43750
	UINT32                                                 reserved3358;	//0xC4F43754
	UINT32                                                 reserved3359;	//0xC4F43758
	UINT32                                                 reserved3360;	//0xC4F4375C
	UINT32                                                 reserved3361;	//0xC4F43760
	UINT32                                                 reserved3362;	//0xC4F43764
	UINT32                                                 reserved3363;	//0xC4F43768
	UINT32                                                 reserved3364;	//0xC4F4376C
	UINT32                                                 reserved3365;	//0xC4F43770
	UINT32                                                 reserved3366;	//0xC4F43774
	UINT32                                                 reserved3367;	//0xC4F43778
	UINT32                                                 reserved3368;	//0xC4F4377C
	UINT32                                                 reserved3369;	//0xC4F43780
	UINT32                                                 reserved3370;	//0xC4F43784
	UINT32                                                 reserved3371;	//0xC4F43788
	UINT32                                                 reserved3372;	//0xC4F4378C
	UINT32                                                 reserved3373;	//0xC4F43790
	UINT32                                                 reserved3374;	//0xC4F43794
	UINT32                                                 reserved3375;	//0xC4F43798
	UINT32                                                 reserved3376;	//0xC4F4379C
	UINT32                                                 reserved3377;	//0xC4F437A0
	UINT32                                                 reserved3378;	//0xC4F437A4
	UINT32                                                 reserved3379;	//0xC4F437A8
	UINT32                                                 reserved3380;	//0xC4F437AC
	UINT32                                                 reserved3381;	//0xC4F437B0
	UINT32                                                 reserved3382;	//0xC4F437B4
	UINT32                                                 reserved3383;	//0xC4F437B8
	UINT32                                                 reserved3384;	//0xC4F437BC
	UINT32                                                 reserved3385;	//0xC4F437C0
	UINT32                                                 reserved3386;	//0xC4F437C4
	UINT32                                                 reserved3387;	//0xC4F437C8
	UINT32                                                 reserved3388;	//0xC4F437CC
	UINT32                                                 reserved3389;	//0xC4F437D0
	UINT32                                                 reserved3390;	//0xC4F437D4
	UINT32                                                 reserved3391;	//0xC4F437D8
	UINT32                                                 reserved3392;	//0xC4F437DC
	UINT32                                                 reserved3393;	//0xC4F437E0
	UINT32                                                 reserved3394;	//0xC4F437E4
	UINT32                                                 reserved3395;	//0xC4F437E8
	UINT32                                                 reserved3396;	//0xC4F437EC
	UINT32                                                 reserved3397;	//0xC4F437F0
	UINT32                                                 reserved3398;	//0xC4F437F4
	UINT32                                                 reserved3399;	//0xC4F437F8
	UINT32                                                 reserved3400;	//0xC4F437FC
	UINT32                                                 reserved3401;	//0xC4F43800
	UINT32                                                 reserved3402;	//0xC4F43804
	UINT32                                                 reserved3403;	//0xC4F43808
	UINT32                                                 reserved3404;	//0xC4F4380C
	UINT32                                                 reserved3405;	//0xC4F43810
	UINT32                                                 reserved3406;	//0xC4F43814
	UINT32                                                 reserved3407;	//0xC4F43818
	UINT32                                                 reserved3408;	//0xC4F4381C
	UINT32                                                 reserved3409;	//0xC4F43820
	UINT32                                                 reserved3410;	//0xC4F43824
	UINT32                                                 reserved3411;	//0xC4F43828
	UINT32                                                 reserved3412;	//0xC4F4382C
	UINT32                                                 reserved3413;	//0xC4F43830
	UINT32                                                 reserved3414;	//0xC4F43834
	UINT32                                                 reserved3415;	//0xC4F43838
	UINT32                                                 reserved3416;	//0xC4F4383C
	UINT32                                                 reserved3417;	//0xC4F43840
	UINT32                                                 reserved3418;	//0xC4F43844
	UINT32                                                 reserved3419;	//0xC4F43848
	UINT32                                                 reserved3420;	//0xC4F4384C
	UINT32                                                 reserved3421;	//0xC4F43850
	UINT32                                                 reserved3422;	//0xC4F43854
	UINT32                                                 reserved3423;	//0xC4F43858
	UINT32                                                 reserved3424;	//0xC4F4385C
	UINT32                                                 reserved3425;	//0xC4F43860
	UINT32                                                 reserved3426;	//0xC4F43864
	UINT32                                                 reserved3427;	//0xC4F43868
	UINT32                                                 reserved3428;	//0xC4F4386C
	UINT32                                                 reserved3429;	//0xC4F43870
	UINT32                                                 reserved3430;	//0xC4F43874
	UINT32                                                 reserved3431;	//0xC4F43878
	UINT32                                                 reserved3432;	//0xC4F4387C
	UINT32                                                 reserved3433;	//0xC4F43880
	UINT32                                                 reserved3434;	//0xC4F43884
	UINT32                                                 reserved3435;	//0xC4F43888
	UINT32                                                 reserved3436;	//0xC4F4388C
	UINT32                                                 reserved3437;	//0xC4F43890
	UINT32                                                 reserved3438;	//0xC4F43894
	UINT32                                                 reserved3439;	//0xC4F43898
	UINT32                                                 reserved3440;	//0xC4F4389C
	UINT32                                                 reserved3441;	//0xC4F438A0
	UINT32                                                 reserved3442;	//0xC4F438A4
	UINT32                                                 reserved3443;	//0xC4F438A8
	UINT32                                                 reserved3444;	//0xC4F438AC
	UINT32                                                 reserved3445;	//0xC4F438B0
	UINT32                                                 reserved3446;	//0xC4F438B4
	UINT32                                                 reserved3447;	//0xC4F438B8
	UINT32                                                 reserved3448;	//0xC4F438BC
	UINT32                                                 reserved3449;	//0xC4F438C0
	UINT32                                                 reserved3450;	//0xC4F438C4
	UINT32                                                 reserved3451;	//0xC4F438C8
	UINT32                                                 reserved3452;	//0xC4F438CC
	UINT32                                                 reserved3453;	//0xC4F438D0
	UINT32                                                 reserved3454;	//0xC4F438D4
	UINT32                                                 reserved3455;	//0xC4F438D8
	UINT32                                                 reserved3456;	//0xC4F438DC
	UINT32                                                 reserved3457;	//0xC4F438E0
	UINT32                                                 reserved3458;	//0xC4F438E4
	UINT32                                                 reserved3459;	//0xC4F438E8
	UINT32                                                 reserved3460;	//0xC4F438EC
	UINT32                                                 reserved3461;	//0xC4F438F0
	UINT32                                                 reserved3462;	//0xC4F438F4
	UINT32                                                 reserved3463;	//0xC4F438F8
	UINT32                                                 reserved3464;	//0xC4F438FC
	UINT32                                                 reserved3465;	//0xC4F43900
	UINT32                                                 reserved3466;	//0xC4F43904
	UINT32                                                 reserved3467;	//0xC4F43908
	UINT32                                                 reserved3468;	//0xC4F4390C
	UINT32                                                 reserved3469;	//0xC4F43910
	UINT32                                                 reserved3470;	//0xC4F43914
	UINT32                                                 reserved3471;	//0xC4F43918
	UINT32                                                 reserved3472;	//0xC4F4391C
	UINT32                                                 reserved3473;	//0xC4F43920
	UINT32                                                 reserved3474;	//0xC4F43924
	UINT32                                                 reserved3475;	//0xC4F43928
	UINT32                                                 reserved3476;	//0xC4F4392C
	UINT32                                                 reserved3477;	//0xC4F43930
	UINT32                                                 reserved3478;	//0xC4F43934
	UINT32                                                 reserved3479;	//0xC4F43938
	UINT32                                                 reserved3480;	//0xC4F4393C
	UINT32                                                 reserved3481;	//0xC4F43940
	UINT32                                                 reserved3482;	//0xC4F43944
	UINT32                                                 reserved3483;	//0xC4F43948
	UINT32                                                 reserved3484;	//0xC4F4394C
	UINT32                                                 reserved3485;	//0xC4F43950
	UINT32                                                 reserved3486;	//0xC4F43954
	UINT32                                                 reserved3487;	//0xC4F43958
	UINT32                                                 reserved3488;	//0xC4F4395C
	UINT32                                                 reserved3489;	//0xC4F43960
	UINT32                                                 reserved3490;	//0xC4F43964
	UINT32                                                 reserved3491;	//0xC4F43968
	UINT32                                                 reserved3492;	//0xC4F4396C
	UINT32                                                 reserved3493;	//0xC4F43970
	UINT32                                                 reserved3494;	//0xC4F43974
	UINT32                                                 reserved3495;	//0xC4F43978
	UINT32                                                 reserved3496;	//0xC4F4397C
	UINT32                                                 reserved3497;	//0xC4F43980
	UINT32                                                 reserved3498;	//0xC4F43984
	UINT32                                                 reserved3499;	//0xC4F43988
	UINT32                                                 reserved3500;	//0xC4F4398C
	UINT32                                                 reserved3501;	//0xC4F43990
	UINT32                                                 reserved3502;	//0xC4F43994
	UINT32                                                 reserved3503;	//0xC4F43998
	UINT32                                                 reserved3504;	//0xC4F4399C
	UINT32                                                 reserved3505;	//0xC4F439A0
	UINT32                                                 reserved3506;	//0xC4F439A4
	UINT32                                                 reserved3507;	//0xC4F439A8
	UINT32                                                 reserved3508;	//0xC4F439AC
	UINT32                                                 reserved3509;	//0xC4F439B0
	UINT32                                                 reserved3510;	//0xC4F439B4
	UINT32                                                 reserved3511;	//0xC4F439B8
	UINT32                                                 reserved3512;	//0xC4F439BC
	UINT32                                                 reserved3513;	//0xC4F439C0
	UINT32                                                 reserved3514;	//0xC4F439C4
	UINT32                                                 reserved3515;	//0xC4F439C8
	UINT32                                                 reserved3516;	//0xC4F439CC
	UINT32                                                 reserved3517;	//0xC4F439D0
	UINT32                                                 reserved3518;	//0xC4F439D4
	UINT32                                                 reserved3519;	//0xC4F439D8
	UINT32                                                 reserved3520;	//0xC4F439DC
	UINT32                                                 reserved3521;	//0xC4F439E0
	UINT32                                                 reserved3522;	//0xC4F439E4
	UINT32                                                 reserved3523;	//0xC4F439E8
	UINT32                                                 reserved3524;	//0xC4F439EC
	UINT32                                                 reserved3525;	//0xC4F439F0
	UINT32                                                 reserved3526;	//0xC4F439F4
	UINT32                                                 reserved3527;	//0xC4F439F8
	UINT32                                                 reserved3528;	//0xC4F439FC
	UINT32                                                 reserved3529;	//0xC4F43A00
	UINT32                                                 reserved3530;	//0xC4F43A04
	UINT32                                                 reserved3531;	//0xC4F43A08
	UINT32                                                 reserved3532;	//0xC4F43A0C
	UINT32                                                 reserved3533;	//0xC4F43A10
	UINT32                                                 reserved3534;	//0xC4F43A14
	UINT32                                                 reserved3535;	//0xC4F43A18
	UINT32                                                 reserved3536;	//0xC4F43A1C
	UINT32                                                 reserved3537;	//0xC4F43A20
	UINT32                                                 reserved3538;	//0xC4F43A24
	UINT32                                                 reserved3539;	//0xC4F43A28
	UINT32                                                 reserved3540;	//0xC4F43A2C
	UINT32                                                 reserved3541;	//0xC4F43A30
	UINT32                                                 reserved3542;	//0xC4F43A34
	UINT32                                                 reserved3543;	//0xC4F43A38
	UINT32                                                 reserved3544;	//0xC4F43A3C
	UINT32                                                 reserved3545;	//0xC4F43A40
	UINT32                                                 reserved3546;	//0xC4F43A44
	UINT32                                                 reserved3547;	//0xC4F43A48
	UINT32                                                 reserved3548;	//0xC4F43A4C
	UINT32                                                 reserved3549;	//0xC4F43A50
	UINT32                                                 reserved3550;	//0xC4F43A54
	UINT32                                                 reserved3551;	//0xC4F43A58
	UINT32                                                 reserved3552;	//0xC4F43A5C
	UINT32                                                 reserved3553;	//0xC4F43A60
	UINT32                                                 reserved3554;	//0xC4F43A64
	UINT32                                                 reserved3555;	//0xC4F43A68
	UINT32                                                 reserved3556;	//0xC4F43A6C
	UINT32                                                 reserved3557;	//0xC4F43A70
	UINT32                                                 reserved3558;	//0xC4F43A74
	UINT32                                                 reserved3559;	//0xC4F43A78
	UINT32                                                 reserved3560;	//0xC4F43A7C
	UINT32                                                 reserved3561;	//0xC4F43A80
	UINT32                                                 reserved3562;	//0xC4F43A84
	UINT32                                                 reserved3563;	//0xC4F43A88
	UINT32                                                 reserved3564;	//0xC4F43A8C
	UINT32                                                 reserved3565;	//0xC4F43A90
	UINT32                                                 reserved3566;	//0xC4F43A94
	UINT32                                                 reserved3567;	//0xC4F43A98
	UINT32                                                 reserved3568;	//0xC4F43A9C
	UINT32                                                 reserved3569;	//0xC4F43AA0
	UINT32                                                 reserved3570;	//0xC4F43AA4
	UINT32                                                 reserved3571;	//0xC4F43AA8
	UINT32                                                 reserved3572;	//0xC4F43AAC
	UINT32                                                 reserved3573;	//0xC4F43AB0
	UINT32                                                 reserved3574;	//0xC4F43AB4
	UINT32                                                 reserved3575;	//0xC4F43AB8
	UINT32                                                 reserved3576;	//0xC4F43ABC
	UINT32                                                 reserved3577;	//0xC4F43AC0
	UINT32                                                 reserved3578;	//0xC4F43AC4
	UINT32                                                 reserved3579;	//0xC4F43AC8
	UINT32                                                 reserved3580;	//0xC4F43ACC
	UINT32                                                 reserved3581;	//0xC4F43AD0
	UINT32                                                 reserved3582;	//0xC4F43AD4
	UINT32                                                 reserved3583;	//0xC4F43AD8
	UINT32                                                 reserved3584;	//0xC4F43ADC
	UINT32                                                 reserved3585;	//0xC4F43AE0
	UINT32                                                 reserved3586;	//0xC4F43AE4
	UINT32                                                 reserved3587;	//0xC4F43AE8
	UINT32                                                 reserved3588;	//0xC4F43AEC
	UINT32                                                 reserved3589;	//0xC4F43AF0
	UINT32                                                 reserved3590;	//0xC4F43AF4
	UINT32                                                 reserved3591;	//0xC4F43AF8
	UINT32                                                 reserved3592;	//0xC4F43AFC
	UINT32                                                 reserved3593;	//0xC4F43B00
	UINT32                                                 reserved3594;	//0xC4F43B04
	UINT32                                                 reserved3595;	//0xC4F43B08
	UINT32                                                 reserved3596;	//0xC4F43B0C
	UINT32                                                 reserved3597;	//0xC4F43B10
	UINT32                                                 reserved3598;	//0xC4F43B14
	UINT32                                                 reserved3599;	//0xC4F43B18
	UINT32                                                 reserved3600;	//0xC4F43B1C
	UINT32                                                 reserved3601;	//0xC4F43B20
	UINT32                                                 reserved3602;	//0xC4F43B24
	UINT32                                                 reserved3603;	//0xC4F43B28
	UINT32                                                 reserved3604;	//0xC4F43B2C
	UINT32                                                 reserved3605;	//0xC4F43B30
	UINT32                                                 reserved3606;	//0xC4F43B34
	UINT32                                                 reserved3607;	//0xC4F43B38
	UINT32                                                 reserved3608;	//0xC4F43B3C
	UINT32                                                 reserved3609;	//0xC4F43B40
	UINT32                                                 reserved3610;	//0xC4F43B44
	UINT32                                                 reserved3611;	//0xC4F43B48
	UINT32                                                 reserved3612;	//0xC4F43B4C
	UINT32                                                 reserved3613;	//0xC4F43B50
	UINT32                                                 reserved3614;	//0xC4F43B54
	UINT32                                                 reserved3615;	//0xC4F43B58
	UINT32                                                 reserved3616;	//0xC4F43B5C
	UINT32                                                 reserved3617;	//0xC4F43B60
	UINT32                                                 reserved3618;	//0xC4F43B64
	UINT32                                                 reserved3619;	//0xC4F43B68
	UINT32                                                 reserved3620;	//0xC4F43B6C
	UINT32                                                 reserved3621;	//0xC4F43B70
	UINT32                                                 reserved3622;	//0xC4F43B74
	UINT32                                                 reserved3623;	//0xC4F43B78
	UINT32                                                 reserved3624;	//0xC4F43B7C
	UINT32                                                 reserved3625;	//0xC4F43B80
	UINT32                                                 reserved3626;	//0xC4F43B84
	UINT32                                                 reserved3627;	//0xC4F43B88
	UINT32                                                 reserved3628;	//0xC4F43B8C
	UINT32                                                 reserved3629;	//0xC4F43B90
	UINT32                                                 reserved3630;	//0xC4F43B94
	UINT32                                                 reserved3631;	//0xC4F43B98
	UINT32                                                 reserved3632;	//0xC4F43B9C
	UINT32                                                 reserved3633;	//0xC4F43BA0
	UINT32                                                 reserved3634;	//0xC4F43BA4
	UINT32                                                 reserved3635;	//0xC4F43BA8
	UINT32                                                 reserved3636;	//0xC4F43BAC
	UINT32                                                 reserved3637;	//0xC4F43BB0
	UINT32                                                 reserved3638;	//0xC4F43BB4
	UINT32                                                 reserved3639;	//0xC4F43BB8
	UINT32                                                 reserved3640;	//0xC4F43BBC
	UINT32                                                 reserved3641;	//0xC4F43BC0
	UINT32                                                 reserved3642;	//0xC4F43BC4
	UINT32                                                 reserved3643;	//0xC4F43BC8
	UINT32                                                 reserved3644;	//0xC4F43BCC
	UINT32                                                 reserved3645;	//0xC4F43BD0
	UINT32                                                 reserved3646;	//0xC4F43BD4
	UINT32                                                 reserved3647;	//0xC4F43BD8
	UINT32                                                 reserved3648;	//0xC4F43BDC
	UINT32                                                 reserved3649;	//0xC4F43BE0
	UINT32                                                 reserved3650;	//0xC4F43BE4
	UINT32                                                 reserved3651;	//0xC4F43BE8
	UINT32                                                 reserved3652;	//0xC4F43BEC
	UINT32                                                 reserved3653;	//0xC4F43BF0
	UINT32                                                 reserved3654;	//0xC4F43BF4
	UINT32                                                 reserved3655;	//0xC4F43BF8
	UINT32                                                 reserved3656;	//0xC4F43BFC
	UINT32                                                 reserved3657;	//0xC4F43C00
	UINT32                                                 reserved3658;	//0xC4F43C04
	UINT32                                                 reserved3659;	//0xC4F43C08
	UINT32                                                 reserved3660;	//0xC4F43C0C
	UINT32                                                 reserved3661;	//0xC4F43C10
	UINT32                                                 reserved3662;	//0xC4F43C14
	UINT32                                                 reserved3663;	//0xC4F43C18
	UINT32                                                 reserved3664;	//0xC4F43C1C
	UINT32                                                 reserved3665;	//0xC4F43C20
	UINT32                                                 reserved3666;	//0xC4F43C24
	UINT32                                                 reserved3667;	//0xC4F43C28
	UINT32                                                 reserved3668;	//0xC4F43C2C
	UINT32                                                 reserved3669;	//0xC4F43C30
	UINT32                                                 reserved3670;	//0xC4F43C34
	UINT32                                                 reserved3671;	//0xC4F43C38
	UINT32                                                 reserved3672;	//0xC4F43C3C
	UINT32                                                 reserved3673;	//0xC4F43C40
	UINT32                                                 reserved3674;	//0xC4F43C44
	UINT32                                                 reserved3675;	//0xC4F43C48
	UINT32                                                 reserved3676;	//0xC4F43C4C
	UINT32                                                 reserved3677;	//0xC4F43C50
	UINT32                                                 reserved3678;	//0xC4F43C54
	UINT32                                                 reserved3679;	//0xC4F43C58
	UINT32                                                 reserved3680;	//0xC4F43C5C
	UINT32                                                 reserved3681;	//0xC4F43C60
	UINT32                                                 reserved3682;	//0xC4F43C64
	UINT32                                                 reserved3683;	//0xC4F43C68
	UINT32                                                 reserved3684;	//0xC4F43C6C
	UINT32                                                 reserved3685;	//0xC4F43C70
	UINT32                                                 reserved3686;	//0xC4F43C74
	UINT32                                                 reserved3687;	//0xC4F43C78
	UINT32                                                 reserved3688;	//0xC4F43C7C
	UINT32                                                 reserved3689;	//0xC4F43C80
	UINT32                                                 reserved3690;	//0xC4F43C84
	UINT32                                                 reserved3691;	//0xC4F43C88
	UINT32                                                 reserved3692;	//0xC4F43C8C
	UINT32                                                 reserved3693;	//0xC4F43C90
	UINT32                                                 reserved3694;	//0xC4F43C94
	UINT32                                                 reserved3695;	//0xC4F43C98
	UINT32                                                 reserved3696;	//0xC4F43C9C
	UINT32                                                 reserved3697;	//0xC4F43CA0
	UINT32                                                 reserved3698;	//0xC4F43CA4
	UINT32                                                 reserved3699;	//0xC4F43CA8
	UINT32                                                 reserved3700;	//0xC4F43CAC
	UINT32                                                 reserved3701;	//0xC4F43CB0
	UINT32                                                 reserved3702;	//0xC4F43CB4
	UINT32                                                 reserved3703;	//0xC4F43CB8
	UINT32                                                 reserved3704;	//0xC4F43CBC
	UINT32                                                 reserved3705;	//0xC4F43CC0
	UINT32                                                 reserved3706;	//0xC4F43CC4
	UINT32                                                 reserved3707;	//0xC4F43CC8
	UINT32                                                 reserved3708;	//0xC4F43CCC
	UINT32                                                 reserved3709;	//0xC4F43CD0
	UINT32                                                 reserved3710;	//0xC4F43CD4
	UINT32                                                 reserved3711;	//0xC4F43CD8
	UINT32                                                 reserved3712;	//0xC4F43CDC
	UINT32                                                 reserved3713;	//0xC4F43CE0
	UINT32                                                 reserved3714;	//0xC4F43CE4
	UINT32                                                 reserved3715;	//0xC4F43CE8
	UINT32                                                 reserved3716;	//0xC4F43CEC
	UINT32                                                 reserved3717;	//0xC4F43CF0
	UINT32                                                 reserved3718;	//0xC4F43CF4
	UINT32                                                 reserved3719;	//0xC4F43CF8
	UINT32                                                 reserved3720;	//0xC4F43CFC
	UINT32                                                 reserved3721;	//0xC4F43D00
	UINT32                                                 reserved3722;	//0xC4F43D04
	UINT32                                                 reserved3723;	//0xC4F43D08
	UINT32                                                 reserved3724;	//0xC4F43D0C
	UINT32                                                 reserved3725;	//0xC4F43D10
	UINT32                                                 reserved3726;	//0xC4F43D14
	UINT32                                                 reserved3727;	//0xC4F43D18
	UINT32                                                 reserved3728;	//0xC4F43D1C
	UINT32                                                 reserved3729;	//0xC4F43D20
	UINT32                                                 reserved3730;	//0xC4F43D24
	UINT32                                                 reserved3731;	//0xC4F43D28
	UINT32                                                 reserved3732;	//0xC4F43D2C
	UINT32                                                 reserved3733;	//0xC4F43D30
	UINT32                                                 reserved3734;	//0xC4F43D34
	UINT32                                                 reserved3735;	//0xC4F43D38
	UINT32                                                 reserved3736;	//0xC4F43D3C
	UINT32                                                 reserved3737;	//0xC4F43D40
	UINT32                                                 reserved3738;	//0xC4F43D44
	UINT32                                                 reserved3739;	//0xC4F43D48
	UINT32                                                 reserved3740;	//0xC4F43D4C
	UINT32                                                 reserved3741;	//0xC4F43D50
	UINT32                                                 reserved3742;	//0xC4F43D54
	UINT32                                                 reserved3743;	//0xC4F43D58
	UINT32                                                 reserved3744;	//0xC4F43D5C
	UINT32                                                 reserved3745;	//0xC4F43D60
	UINT32                                                 reserved3746;	//0xC4F43D64
	UINT32                                                 reserved3747;	//0xC4F43D68
	UINT32                                                 reserved3748;	//0xC4F43D6C
	UINT32                                                 reserved3749;	//0xC4F43D70
	UINT32                                                 reserved3750;	//0xC4F43D74
	UINT32                                                 reserved3751;	//0xC4F43D78
	UINT32                                                 reserved3752;	//0xC4F43D7C
	UINT32                                                 reserved3753;	//0xC4F43D80
	UINT32                                                 reserved3754;	//0xC4F43D84
	UINT32                                                 reserved3755;	//0xC4F43D88
	UINT32                                                 reserved3756;	//0xC4F43D8C
	UINT32                                                 reserved3757;	//0xC4F43D90
	UINT32                                                 reserved3758;	//0xC4F43D94
	UINT32                                                 reserved3759;	//0xC4F43D98
	UINT32                                                 reserved3760;	//0xC4F43D9C
	UINT32                                                 reserved3761;	//0xC4F43DA0
	UINT32                                                 reserved3762;	//0xC4F43DA4
	UINT32                                                 reserved3763;	//0xC4F43DA8
	UINT32                                                 reserved3764;	//0xC4F43DAC
	UINT32                                                 reserved3765;	//0xC4F43DB0
	UINT32                                                 reserved3766;	//0xC4F43DB4
	UINT32                                                 reserved3767;	//0xC4F43DB8
	UINT32                                                 reserved3768;	//0xC4F43DBC
	UINT32                                                 reserved3769;	//0xC4F43DC0
	UINT32                                                 reserved3770;	//0xC4F43DC4
	UINT32                                                 reserved3771;	//0xC4F43DC8
	UINT32                                                 reserved3772;	//0xC4F43DCC
	UINT32                                                 reserved3773;	//0xC4F43DD0
	UINT32                                                 reserved3774;	//0xC4F43DD4
	UINT32                                                 reserved3775;	//0xC4F43DD8
	UINT32                                                 reserved3776;	//0xC4F43DDC
	UINT32                                                 reserved3777;	//0xC4F43DE0
	UINT32                                                 reserved3778;	//0xC4F43DE4
	UINT32                                                 reserved3779;	//0xC4F43DE8
	UINT32                                                 reserved3780;	//0xC4F43DEC
	UINT32                                                 reserved3781;	//0xC4F43DF0
	UINT32                                                 reserved3782;	//0xC4F43DF4
	UINT32                                                 reserved3783;	//0xC4F43DF8
	UINT32                                                 reserved3784;	//0xC4F43DFC
	UINT32                                                 reserved3785;	//0xC4F43E00
	UINT32                                                 reserved3786;	//0xC4F43E04
	UINT32                                                 reserved3787;	//0xC4F43E08
	UINT32                                                 reserved3788;	//0xC4F43E0C
	UINT32                                                 reserved3789;	//0xC4F43E10
	UINT32                                                 reserved3790;	//0xC4F43E14
	UINT32                                                 reserved3791;	//0xC4F43E18
	UINT32                                                 reserved3792;	//0xC4F43E1C
	UINT32                                                 reserved3793;	//0xC4F43E20
	UINT32                                                 reserved3794;	//0xC4F43E24
	UINT32                                                 reserved3795;	//0xC4F43E28
	UINT32                                                 reserved3796;	//0xC4F43E2C
	UINT32                                                 reserved3797;	//0xC4F43E30
	UINT32                                                 reserved3798;	//0xC4F43E34
	UINT32                                                 reserved3799;	//0xC4F43E38
	UINT32                                                 reserved3800;	//0xC4F43E3C
	UINT32                                                 reserved3801;	//0xC4F43E40
	UINT32                                                 reserved3802;	//0xC4F43E44
	UINT32                                                 reserved3803;	//0xC4F43E48
	UINT32                                                 reserved3804;	//0xC4F43E4C
	UINT32                                                 reserved3805;	//0xC4F43E50
	UINT32                                                 reserved3806;	//0xC4F43E54
	UINT32                                                 reserved3807;	//0xC4F43E58
	UINT32                                                 reserved3808;	//0xC4F43E5C
	UINT32                                                 reserved3809;	//0xC4F43E60
	UINT32                                                 reserved3810;	//0xC4F43E64
	UINT32                                                 reserved3811;	//0xC4F43E68
	UINT32                                                 reserved3812;	//0xC4F43E6C
	UINT32                                                 reserved3813;	//0xC4F43E70
	UINT32                                                 reserved3814;	//0xC4F43E74
	UINT32                                                 reserved3815;	//0xC4F43E78
	UINT32                                                 reserved3816;	//0xC4F43E7C
	UINT32                                                 reserved3817;	//0xC4F43E80
	UINT32                                                 reserved3818;	//0xC4F43E84
	UINT32                                                 reserved3819;	//0xC4F43E88
	UINT32                                                 reserved3820;	//0xC4F43E8C
	UINT32                                                 reserved3821;	//0xC4F43E90
	UINT32                                                 reserved3822;	//0xC4F43E94
	UINT32                                                 reserved3823;	//0xC4F43E98
	UINT32                                                 reserved3824;	//0xC4F43E9C
	UINT32                                                 reserved3825;	//0xC4F43EA0
	UINT32                                                 reserved3826;	//0xC4F43EA4
	UINT32                                                 reserved3827;	//0xC4F43EA8
	UINT32                                                 reserved3828;	//0xC4F43EAC
	UINT32                                                 reserved3829;	//0xC4F43EB0
	UINT32                                                 reserved3830;	//0xC4F43EB4
	UINT32                                                 reserved3831;	//0xC4F43EB8
	UINT32                                                 reserved3832;	//0xC4F43EBC
	UINT32                                                 reserved3833;	//0xC4F43EC0
	UINT32                                                 reserved3834;	//0xC4F43EC4
	UINT32                                                 reserved3835;	//0xC4F43EC8
	UINT32                                                 reserved3836;	//0xC4F43ECC
	UINT32                                                 reserved3837;	//0xC4F43ED0
	UINT32                                                 reserved3838;	//0xC4F43ED4
	UINT32                                                 reserved3839;	//0xC4F43ED8
	UINT32                                                 reserved3840;	//0xC4F43EDC
	UINT32                                                 reserved3841;	//0xC4F43EE0
	UINT32                                                 reserved3842;	//0xC4F43EE4
	UINT32                                                 reserved3843;	//0xC4F43EE8
	UINT32                                                 reserved3844;	//0xC4F43EEC
	UINT32                                                 reserved3845;	//0xC4F43EF0
	UINT32                                                 reserved3846;	//0xC4F43EF4
	UINT32                                                 reserved3847;	//0xC4F43EF8
	UINT32                                                 reserved3848;	//0xC4F43EFC
	UINT32                                                 reserved3849;	//0xC4F43F00
	UINT32                                                 reserved3850;	//0xC4F43F04
	UINT32                                                 reserved3851;	//0xC4F43F08
	UINT32                                                 reserved3852;	//0xC4F43F0C
	UINT32                                                 reserved3853;	//0xC4F43F10
	UINT32                                                 reserved3854;	//0xC4F43F14
	UINT32                                                 reserved3855;	//0xC4F43F18
	UINT32                                                 reserved3856;	//0xC4F43F1C
	UINT32                                                 reserved3857;	//0xC4F43F20
	UINT32                                                 reserved3858;	//0xC4F43F24
	UINT32                                                 reserved3859;	//0xC4F43F28
	UINT32                                                 reserved3860;	//0xC4F43F2C
	UINT32                                                 reserved3861;	//0xC4F43F30
	UINT32                                                 reserved3862;	//0xC4F43F34
	UINT32                                                 reserved3863;	//0xC4F43F38
	UINT32                                                 reserved3864;	//0xC4F43F3C
	UINT32                                                 reserved3865;	//0xC4F43F40
	UINT32                                                 reserved3866;	//0xC4F43F44
	UINT32                                                 reserved3867;	//0xC4F43F48
	UINT32                                                 reserved3868;	//0xC4F43F4C
	UINT32                                                 reserved3869;	//0xC4F43F50
	UINT32                                                 reserved3870;	//0xC4F43F54
	UINT32                                                 reserved3871;	//0xC4F43F58
	UINT32                                                 reserved3872;	//0xC4F43F5C
	UINT32                                                 reserved3873;	//0xC4F43F60
	UINT32                                                 reserved3874;	//0xC4F43F64
	UINT32                                                 reserved3875;	//0xC4F43F68
	UINT32                                                 reserved3876;	//0xC4F43F6C
	UINT32                                                 reserved3877;	//0xC4F43F70
	UINT32                                                 reserved3878;	//0xC4F43F74
	UINT32                                                 reserved3879;	//0xC4F43F78
	UINT32                                                 reserved3880;	//0xC4F43F7C
	UINT32                                                 reserved3881;	//0xC4F43F80
	UINT32                                                 reserved3882;	//0xC4F43F84
	UINT32                                                 reserved3883;	//0xC4F43F88
	UINT32                                                 reserved3884;	//0xC4F43F8C
	UINT32                                                 reserved3885;	//0xC4F43F90
	UINT32                                                 reserved3886;	//0xC4F43F94
	UINT32                                                 reserved3887;	//0xC4F43F98
	UINT32                                                 reserved3888;	//0xC4F43F9C
	UINT32                                                 reserved3889;	//0xC4F43FA0
	UINT32                                                 reserved3890;	//0xC4F43FA4
	UINT32                                                 reserved3891;	//0xC4F43FA8
	UINT32                                                 reserved3892;	//0xC4F43FAC
	UINT32                                                 reserved3893;	//0xC4F43FB0
	UINT32                                                 reserved3894;	//0xC4F43FB4
	UINT32                                                 reserved3895;	//0xC4F43FB8
	UINT32                                                 reserved3896;	//0xC4F43FBC
	UINT32                                                 reserved3897;	//0xC4F43FC0
	UINT32                                                 reserved3898;	//0xC4F43FC4
	UINT32                                                 reserved3899;	//0xC4F43FC8
	UINT32                                                 reserved3900;	//0xC4F43FCC
	UINT32                                                 reserved3901;	//0xC4F43FD0
	UINT32                                                 reserved3902;	//0xC4F43FD4
	UINT32                                                 reserved3903;	//0xC4F43FD8
	UINT32                                                 reserved3904;	//0xC4F43FDC
	UINT32                                                 reserved3905;	//0xC4F43FE0
	UINT32                                                 reserved3906;	//0xC4F43FE4
	UINT32                                                 reserved3907;	//0xC4F43FE8
	UINT32                                                 reserved3908;	//0xC4F43FEC
	UINT32                                                 reserved3909;	//0xC4F43FF0
	UINT32                                                 reserved3910;	//0xC4F43FF4
	UINT32                                                 reserved3911;	//0xC4F43FF8
	UINT32                                                 reserved3912;	//0xC4F43FFC
	UINT32                                                 reserved3913;	//0xC4F44000
	UINT32                                                 reserved3914;	//0xC4F44004
	UINT32                                                 reserved3915;	//0xC4F44008
	UINT32                                                 reserved3916;	//0xC4F4400C
	UINT32                                                 reserved3917;	//0xC4F44010
	UINT32                                                 reserved3918;	//0xC4F44014
	UINT32                                                 reserved3919;	//0xC4F44018
	UINT32                                                 reserved3920;	//0xC4F4401C
	UINT32                                                 reserved3921;	//0xC4F44020
	UINT32                                                 reserved3922;	//0xC4F44024
	UINT32                                                 reserved3923;	//0xC4F44028
	UINT32                                                 reserved3924;	//0xC4F4402C
	UINT32                                                 reserved3925;	//0xC4F44030
	UINT32                                                 reserved3926;	//0xC4F44034
	UINT32                                                 reserved3927;	//0xC4F44038
	UINT32                                                 reserved3928;	//0xC4F4403C
	UINT32                                                 reserved3929;	//0xC4F44040
	UINT32                                                 reserved3930;	//0xC4F44044
	UINT32                                                 reserved3931;	//0xC4F44048
	UINT32                                                 reserved3932;	//0xC4F4404C
	UINT32                                                 reserved3933;	//0xC4F44050
	UINT32                                                 reserved3934;	//0xC4F44054
	UINT32                                                 reserved3935;	//0xC4F44058
	UINT32                                                 reserved3936;	//0xC4F4405C
	UINT32                                                 reserved3937;	//0xC4F44060
	UINT32                                                 reserved3938;	//0xC4F44064
	UINT32                                                 reserved3939;	//0xC4F44068
	UINT32                                                 reserved3940;	//0xC4F4406C
	UINT32                                                 reserved3941;	//0xC4F44070
	UINT32                                                 reserved3942;	//0xC4F44074
	UINT32                                                 reserved3943;	//0xC4F44078
	UINT32                                                 reserved3944;	//0xC4F4407C
	UINT32                                                 reserved3945;	//0xC4F44080
	UINT32                                                 reserved3946;	//0xC4F44084
	UINT32                                                 reserved3947;	//0xC4F44088
	UINT32                                                 reserved3948;	//0xC4F4408C
	UINT32                                                 reserved3949;	//0xC4F44090
	UINT32                                                 reserved3950;	//0xC4F44094
	UINT32                                                 reserved3951;	//0xC4F44098
	UINT32                                                 reserved3952;	//0xC4F4409C
	UINT32                                                 reserved3953;	//0xC4F440A0
	UINT32                                                 reserved3954;	//0xC4F440A4
	UINT32                                                 reserved3955;	//0xC4F440A8
	UINT32                                                 reserved3956;	//0xC4F440AC
	UINT32                                                 reserved3957;	//0xC4F440B0
	UINT32                                                 reserved3958;	//0xC4F440B4
	UINT32                                                 reserved3959;	//0xC4F440B8
	UINT32                                                 reserved3960;	//0xC4F440BC
	UINT32                                                 reserved3961;	//0xC4F440C0
	UINT32                                                 reserved3962;	//0xC4F440C4
	UINT32                                                 reserved3963;	//0xC4F440C8
	UINT32                                                 reserved3964;	//0xC4F440CC
	UINT32                                                 reserved3965;	//0xC4F440D0
	UINT32                                                 reserved3966;	//0xC4F440D4
	UINT32                                                 reserved3967;	//0xC4F440D8
	UINT32                                                 reserved3968;	//0xC4F440DC
	UINT32                                                 reserved3969;	//0xC4F440E0
	UINT32                                                 reserved3970;	//0xC4F440E4
	UINT32                                                 reserved3971;	//0xC4F440E8
	UINT32                                                 reserved3972;	//0xC4F440EC
	UINT32                                                 reserved3973;	//0xC4F440F0
	UINT32                                                 reserved3974;	//0xC4F440F4
	UINT32                                                 reserved3975;	//0xC4F440F8
	UINT32                                                 reserved3976;	//0xC4F440FC
	UINT32                                                 reserved3977;	//0xC4F44100
	UINT32                                                 reserved3978;	//0xC4F44104
	UINT32                                                 reserved3979;	//0xC4F44108
	UINT32                                                 reserved3980;	//0xC4F4410C
	UINT32                                                 reserved3981;	//0xC4F44110
	UINT32                                                 reserved3982;	//0xC4F44114
	UINT32                                                 reserved3983;	//0xC4F44118
	UINT32                                                 reserved3984;	//0xC4F4411C
	UINT32                                                 reserved3985;	//0xC4F44120
	UINT32                                                 reserved3986;	//0xC4F44124
	UINT32                                                 reserved3987;	//0xC4F44128
	UINT32                                                 reserved3988;	//0xC4F4412C
	UINT32                                                 reserved3989;	//0xC4F44130
	UINT32                                                 reserved3990;	//0xC4F44134
	UINT32                                                 reserved3991;	//0xC4F44138
	UINT32                                                 reserved3992;	//0xC4F4413C
	UINT32                                                 reserved3993;	//0xC4F44140
	UINT32                                                 reserved3994;	//0xC4F44144
	UINT32                                                 reserved3995;	//0xC4F44148
	UINT32                                                 reserved3996;	//0xC4F4414C
	UINT32                                                 reserved3997;	//0xC4F44150
	UINT32                                                 reserved3998;	//0xC4F44154
	UINT32                                                 reserved3999;	//0xC4F44158
	UINT32                                                 reserved4000;	//0xC4F4415C
	UINT32                                                 reserved4001;	//0xC4F44160
	UINT32                                                 reserved4002;	//0xC4F44164
	UINT32                                                 reserved4003;	//0xC4F44168
	UINT32                                                 reserved4004;	//0xC4F4416C
	UINT32                                                 reserved4005;	//0xC4F44170
	UINT32                                                 reserved4006;	//0xC4F44174
	UINT32                                                 reserved4007;	//0xC4F44178
	UINT32                                                 reserved4008;	//0xC4F4417C
	UINT32                                                 reserved4009;	//0xC4F44180
	UINT32                                                 reserved4010;	//0xC4F44184
	UINT32                                                 reserved4011;	//0xC4F44188
	UINT32                                                 reserved4012;	//0xC4F4418C
	UINT32                                                 reserved4013;	//0xC4F44190
	UINT32                                                 reserved4014;	//0xC4F44194
	UINT32                                                 reserved4015;	//0xC4F44198
	UINT32                                                 reserved4016;	//0xC4F4419C
	UINT32                                                 reserved4017;	//0xC4F441A0
	UINT32                                                 reserved4018;	//0xC4F441A4
	UINT32                                                 reserved4019;	//0xC4F441A8
	UINT32                                                 reserved4020;	//0xC4F441AC
	UINT32                                                 reserved4021;	//0xC4F441B0
	UINT32                                                 reserved4022;	//0xC4F441B4
	UINT32                                                 reserved4023;	//0xC4F441B8
	UINT32                                                 reserved4024;	//0xC4F441BC
	UINT32                                                 reserved4025;	//0xC4F441C0
	UINT32                                                 reserved4026;	//0xC4F441C4
	UINT32                                                 reserved4027;	//0xC4F441C8
	UINT32                                                 reserved4028;	//0xC4F441CC
	UINT32                                                 reserved4029;	//0xC4F441D0
	UINT32                                                 reserved4030;	//0xC4F441D4
	UINT32                                                 reserved4031;	//0xC4F441D8
	UINT32                                                 reserved4032;	//0xC4F441DC
	UINT32                                                 reserved4033;	//0xC4F441E0
	UINT32                                                 reserved4034;	//0xC4F441E4
	UINT32                                                 reserved4035;	//0xC4F441E8
	UINT32                                                 reserved4036;	//0xC4F441EC
	UINT32                                                 reserved4037;	//0xC4F441F0
	UINT32                                                 reserved4038;	//0xC4F441F4
	UINT32                                                 reserved4039;	//0xC4F441F8
	UINT32                                                 reserved4040;	//0xC4F441FC
	UINT32                                                 reserved4041;	//0xC4F44200
	UINT32                                                 reserved4042;	//0xC4F44204
	UINT32                                                 reserved4043;	//0xC4F44208
	UINT32                                                 reserved4044;	//0xC4F4420C
	UINT32                                                 reserved4045;	//0xC4F44210
	UINT32                                                 reserved4046;	//0xC4F44214
	UINT32                                                 reserved4047;	//0xC4F44218
	UINT32                                                 reserved4048;	//0xC4F4421C
	UINT32                                                 reserved4049;	//0xC4F44220
	UINT32                                                 reserved4050;	//0xC4F44224
	UINT32                                                 reserved4051;	//0xC4F44228
	UINT32                                                 reserved4052;	//0xC4F4422C
	UINT32                                                 reserved4053;	//0xC4F44230
	UINT32                                                 reserved4054;	//0xC4F44234
	UINT32                                                 reserved4055;	//0xC4F44238
	UINT32                                                 reserved4056;	//0xC4F4423C
	UINT32                                                 reserved4057;	//0xC4F44240
	UINT32                                                 reserved4058;	//0xC4F44244
	UINT32                                                 reserved4059;	//0xC4F44248
	UINT32                                                 reserved4060;	//0xC4F4424C
	UINT32                                                 reserved4061;	//0xC4F44250
	UINT32                                                 reserved4062;	//0xC4F44254
	UINT32                                                 reserved4063;	//0xC4F44258
	UINT32                                                 reserved4064;	//0xC4F4425C
	UINT32                                                 reserved4065;	//0xC4F44260
	UINT32                                                 reserved4066;	//0xC4F44264
	UINT32                                                 reserved4067;	//0xC4F44268
	UINT32                                                 reserved4068;	//0xC4F4426C
	UINT32                                                 reserved4069;	//0xC4F44270
	UINT32                                                 reserved4070;	//0xC4F44274
	UINT32                                                 reserved4071;	//0xC4F44278
	UINT32                                                 reserved4072;	//0xC4F4427C
	UINT32                                                 reserved4073;	//0xC4F44280
	UINT32                                                 reserved4074;	//0xC4F44284
	UINT32                                                 reserved4075;	//0xC4F44288
	UINT32                                                 reserved4076;	//0xC4F4428C
	UINT32                                                 reserved4077;	//0xC4F44290
	UINT32                                                 reserved4078;	//0xC4F44294
	UINT32                                                 reserved4079;	//0xC4F44298
	UINT32                                                 reserved4080;	//0xC4F4429C
	UINT32                                                 reserved4081;	//0xC4F442A0
	UINT32                                                 reserved4082;	//0xC4F442A4
	UINT32                                                 reserved4083;	//0xC4F442A8
	UINT32                                                 reserved4084;	//0xC4F442AC
	UINT32                                                 reserved4085;	//0xC4F442B0
	UINT32                                                 reserved4086;	//0xC4F442B4
	UINT32                                                 reserved4087;	//0xC4F442B8
	UINT32                                                 reserved4088;	//0xC4F442BC
	UINT32                                                 reserved4089;	//0xC4F442C0
	UINT32                                                 reserved4090;	//0xC4F442C4
	UINT32                                                 reserved4091;	//0xC4F442C8
	UINT32                                                 reserved4092;	//0xC4F442CC
	UINT32                                                 reserved4093;	//0xC4F442D0
	UINT32                                                 reserved4094;	//0xC4F442D4
	UINT32                                                 reserved4095;	//0xC4F442D8
	UINT32                                                 reserved4096;	//0xC4F442DC
	UINT32                                                 reserved4097;	//0xC4F442E0
	UINT32                                                 reserved4098;	//0xC4F442E4
	UINT32                                                 reserved4099;	//0xC4F442E8
	UINT32                                                 reserved4100;	//0xC4F442EC
	UINT32                                                 reserved4101;	//0xC4F442F0
	UINT32                                                 reserved4102;	//0xC4F442F4
	UINT32                                                 reserved4103;	//0xC4F442F8
	UINT32                                                 reserved4104;	//0xC4F442FC
	UINT32                                                 reserved4105;	//0xC4F44300
	UINT32                                                 reserved4106;	//0xC4F44304
	UINT32                                                 reserved4107;	//0xC4F44308
	UINT32                                                 reserved4108;	//0xC4F4430C
	UINT32                                                 reserved4109;	//0xC4F44310
	UINT32                                                 reserved4110;	//0xC4F44314
	UINT32                                                 reserved4111;	//0xC4F44318
	UINT32                                                 reserved4112;	//0xC4F4431C
	UINT32                                                 reserved4113;	//0xC4F44320
	UINT32                                                 reserved4114;	//0xC4F44324
	UINT32                                                 reserved4115;	//0xC4F44328
	UINT32                                                 reserved4116;	//0xC4F4432C
	UINT32                                                 reserved4117;	//0xC4F44330
	UINT32                                                 reserved4118;	//0xC4F44334
	UINT32                                                 reserved4119;	//0xC4F44338
	UINT32                                                 reserved4120;	//0xC4F4433C
	UINT32                                                 reserved4121;	//0xC4F44340
	UINT32                                                 reserved4122;	//0xC4F44344
	UINT32                                                 reserved4123;	//0xC4F44348
	UINT32                                                 reserved4124;	//0xC4F4434C
	UINT32                                                 reserved4125;	//0xC4F44350
	UINT32                                                 reserved4126;	//0xC4F44354
	UINT32                                                 reserved4127;	//0xC4F44358
	UINT32                                                 reserved4128;	//0xC4F4435C
	UINT32                                                 reserved4129;	//0xC4F44360
	UINT32                                                 reserved4130;	//0xC4F44364
	UINT32                                                 reserved4131;	//0xC4F44368
	UINT32                                                 reserved4132;	//0xC4F4436C
	UINT32                                                 reserved4133;	//0xC4F44370
	UINT32                                                 reserved4134;	//0xC4F44374
	UINT32                                                 reserved4135;	//0xC4F44378
	UINT32                                                 reserved4136;	//0xC4F4437C
	UINT32                                                 reserved4137;	//0xC4F44380
	UINT32                                                 reserved4138;	//0xC4F44384
	UINT32                                                 reserved4139;	//0xC4F44388
	UINT32                                                 reserved4140;	//0xC4F4438C
	UINT32                                                 reserved4141;	//0xC4F44390
	UINT32                                                 reserved4142;	//0xC4F44394
	UINT32                                                 reserved4143;	//0xC4F44398
	UINT32                                                 reserved4144;	//0xC4F4439C
	UINT32                                                 reserved4145;	//0xC4F443A0
	UINT32                                                 reserved4146;	//0xC4F443A4
	UINT32                                                 reserved4147;	//0xC4F443A8
	UINT32                                                 reserved4148;	//0xC4F443AC
	UINT32                                                 reserved4149;	//0xC4F443B0
	UINT32                                                 reserved4150;	//0xC4F443B4
	UINT32                                                 reserved4151;	//0xC4F443B8
	UINT32                                                 reserved4152;	//0xC4F443BC
	UINT32                                                 reserved4153;	//0xC4F443C0
	UINT32                                                 reserved4154;	//0xC4F443C4
	UINT32                                                 reserved4155;	//0xC4F443C8
	UINT32                                                 reserved4156;	//0xC4F443CC
	UINT32                                                 reserved4157;	//0xC4F443D0
	UINT32                                                 reserved4158;	//0xC4F443D4
	UINT32                                                 reserved4159;	//0xC4F443D8
	UINT32                                                 reserved4160;	//0xC4F443DC
	UINT32                                                 reserved4161;	//0xC4F443E0
	UINT32                                                 reserved4162;	//0xC4F443E4
	UINT32                                                 reserved4163;	//0xC4F443E8
	UINT32                                                 reserved4164;	//0xC4F443EC
	UINT32                                                 reserved4165;	//0xC4F443F0
	UINT32                                                 reserved4166;	//0xC4F443F4
	UINT32                                                 reserved4167;	//0xC4F443F8
	UINT32                                                 reserved4168;	//0xC4F443FC
	UINT32                                                 reserved4169;	//0xC4F44400
	UINT32                                                 reserved4170;	//0xC4F44404
	UINT32                                                 reserved4171;	//0xC4F44408
	UINT32                                                 reserved4172;	//0xC4F4440C
	UINT32                                                 reserved4173;	//0xC4F44410
	UINT32                                                 reserved4174;	//0xC4F44414
	UINT32                                                 reserved4175;	//0xC4F44418
	UINT32                                                 reserved4176;	//0xC4F4441C
	UINT32                                                 reserved4177;	//0xC4F44420
	UINT32                                                 reserved4178;	//0xC4F44424
	UINT32                                                 reserved4179;	//0xC4F44428
	UINT32                                                 reserved4180;	//0xC4F4442C
	UINT32                                                 reserved4181;	//0xC4F44430
	UINT32                                                 reserved4182;	//0xC4F44434
	UINT32                                                 reserved4183;	//0xC4F44438
	UINT32                                                 reserved4184;	//0xC4F4443C
	UINT32                                                 reserved4185;	//0xC4F44440
	UINT32                                                 reserved4186;	//0xC4F44444
	UINT32                                                 reserved4187;	//0xC4F44448
	UINT32                                                 reserved4188;	//0xC4F4444C
	UINT32                                                 reserved4189;	//0xC4F44450
	UINT32                                                 reserved4190;	//0xC4F44454
	UINT32                                                 reserved4191;	//0xC4F44458
	UINT32                                                 reserved4192;	//0xC4F4445C
	UINT32                                                 reserved4193;	//0xC4F44460
	UINT32                                                 reserved4194;	//0xC4F44464
	UINT32                                                 reserved4195;	//0xC4F44468
	UINT32                                                 reserved4196;	//0xC4F4446C
	UINT32                                                 reserved4197;	//0xC4F44470
	UINT32                                                 reserved4198;	//0xC4F44474
	UINT32                                                 reserved4199;	//0xC4F44478
	UINT32                                                 reserved4200;	//0xC4F4447C
	UINT32                                                 reserved4201;	//0xC4F44480
	UINT32                                                 reserved4202;	//0xC4F44484
	UINT32                                                 reserved4203;	//0xC4F44488
	UINT32                                                 reserved4204;	//0xC4F4448C
	UINT32                                                 reserved4205;	//0xC4F44490
	UINT32                                                 reserved4206;	//0xC4F44494
	UINT32                                                 reserved4207;	//0xC4F44498
	UINT32                                                 reserved4208;	//0xC4F4449C
	UINT32                                                 reserved4209;	//0xC4F444A0
	UINT32                                                 reserved4210;	//0xC4F444A4
	UINT32                                                 reserved4211;	//0xC4F444A8
	UINT32                                                 reserved4212;	//0xC4F444AC
	UINT32                                                 reserved4213;	//0xC4F444B0
	UINT32                                                 reserved4214;	//0xC4F444B4
	UINT32                                                 reserved4215;	//0xC4F444B8
	UINT32                                                 reserved4216;	//0xC4F444BC
	UINT32                                                 reserved4217;	//0xC4F444C0
	UINT32                                                 reserved4218;	//0xC4F444C4
	UINT32                                                 reserved4219;	//0xC4F444C8
	UINT32                                                 reserved4220;	//0xC4F444CC
	UINT32                                                 reserved4221;	//0xC4F444D0
	UINT32                                                 reserved4222;	//0xC4F444D4
	UINT32                                                 reserved4223;	//0xC4F444D8
	UINT32                                                 reserved4224;	//0xC4F444DC
	UINT32                                                 reserved4225;	//0xC4F444E0
	UINT32                                                 reserved4226;	//0xC4F444E4
	UINT32                                                 reserved4227;	//0xC4F444E8
	UINT32                                                 reserved4228;	//0xC4F444EC
	UINT32                                                 reserved4229;	//0xC4F444F0
	UINT32                                                 reserved4230;	//0xC4F444F4
	UINT32                                                 reserved4231;	//0xC4F444F8
	UINT32                                                 reserved4232;	//0xC4F444FC
	UINT32                                                 reserved4233;	//0xC4F44500
	UINT32                                                 reserved4234;	//0xC4F44504
	UINT32                                                 reserved4235;	//0xC4F44508
	UINT32                                                 reserved4236;	//0xC4F4450C
	UINT32                                                 reserved4237;	//0xC4F44510
	UINT32                                                 reserved4238;	//0xC4F44514
	UINT32                                                 reserved4239;	//0xC4F44518
	UINT32                                                 reserved4240;	//0xC4F4451C
	UINT32                                                 reserved4241;	//0xC4F44520
	UINT32                                                 reserved4242;	//0xC4F44524
	UINT32                                                 reserved4243;	//0xC4F44528
	UINT32                                                 reserved4244;	//0xC4F4452C
	UINT32                                                 reserved4245;	//0xC4F44530
	UINT32                                                 reserved4246;	//0xC4F44534
	UINT32                                                 reserved4247;	//0xC4F44538
	UINT32                                                 reserved4248;	//0xC4F4453C
	UINT32                                                 reserved4249;	//0xC4F44540
	UINT32                                                 reserved4250;	//0xC4F44544
	UINT32                                                 reserved4251;	//0xC4F44548
	UINT32                                                 reserved4252;	//0xC4F4454C
	UINT32                                                 reserved4253;	//0xC4F44550
	UINT32                                                 reserved4254;	//0xC4F44554
	UINT32                                                 reserved4255;	//0xC4F44558
	UINT32                                                 reserved4256;	//0xC4F4455C
	UINT32                                                 reserved4257;	//0xC4F44560
	UINT32                                                 reserved4258;	//0xC4F44564
	UINT32                                                 reserved4259;	//0xC4F44568
	UINT32                                                 reserved4260;	//0xC4F4456C
	UINT32                                                 reserved4261;	//0xC4F44570
	UINT32                                                 reserved4262;	//0xC4F44574
	UINT32                                                 reserved4263;	//0xC4F44578
	UINT32                                                 reserved4264;	//0xC4F4457C
	UINT32                                                 reserved4265;	//0xC4F44580
	UINT32                                                 reserved4266;	//0xC4F44584
	UINT32                                                 reserved4267;	//0xC4F44588
	UINT32                                                 reserved4268;	//0xC4F4458C
	UINT32                                                 reserved4269;	//0xC4F44590
	UINT32                                                 reserved4270;	//0xC4F44594
	UINT32                                                 reserved4271;	//0xC4F44598
	UINT32                                                 reserved4272;	//0xC4F4459C
	UINT32                                                 reserved4273;	//0xC4F445A0
	UINT32                                                 reserved4274;	//0xC4F445A4
	UINT32                                                 reserved4275;	//0xC4F445A8
	UINT32                                                 reserved4276;	//0xC4F445AC
	UINT32                                                 reserved4277;	//0xC4F445B0
	UINT32                                                 reserved4278;	//0xC4F445B4
	UINT32                                                 reserved4279;	//0xC4F445B8
	UINT32                                                 reserved4280;	//0xC4F445BC
	UINT32                                                 reserved4281;	//0xC4F445C0
	UINT32                                                 reserved4282;	//0xC4F445C4
	UINT32                                                 reserved4283;	//0xC4F445C8
	UINT32                                                 reserved4284;	//0xC4F445CC
	UINT32                                                 reserved4285;	//0xC4F445D0
	UINT32                                                 reserved4286;	//0xC4F445D4
	UINT32                                                 reserved4287;	//0xC4F445D8
	UINT32                                                 reserved4288;	//0xC4F445DC
	UINT32                                                 reserved4289;	//0xC4F445E0
	UINT32                                                 reserved4290;	//0xC4F445E4
	UINT32                                                 reserved4291;	//0xC4F445E8
	UINT32                                                 reserved4292;	//0xC4F445EC
	UINT32                                                 reserved4293;	//0xC4F445F0
	UINT32                                                 reserved4294;	//0xC4F445F4
	UINT32                                                 reserved4295;	//0xC4F445F8
	UINT32                                                 reserved4296;	//0xC4F445FC
	UINT32                                                 reserved4297;	//0xC4F44600
	UINT32                                                 reserved4298;	//0xC4F44604
	UINT32                                                 reserved4299;	//0xC4F44608
	UINT32                                                 reserved4300;	//0xC4F4460C
	UINT32                                                 reserved4301;	//0xC4F44610
	UINT32                                                 reserved4302;	//0xC4F44614
	UINT32                                                 reserved4303;	//0xC4F44618
	UINT32                                                 reserved4304;	//0xC4F4461C
	UINT32                                                 reserved4305;	//0xC4F44620
	UINT32                                                 reserved4306;	//0xC4F44624
	UINT32                                                 reserved4307;	//0xC4F44628
	UINT32                                                 reserved4308;	//0xC4F4462C
	UINT32                                                 reserved4309;	//0xC4F44630
	UINT32                                                 reserved4310;	//0xC4F44634
	UINT32                                                 reserved4311;	//0xC4F44638
	UINT32                                                 reserved4312;	//0xC4F4463C
	UINT32                                                 reserved4313;	//0xC4F44640
	UINT32                                                 reserved4314;	//0xC4F44644
	UINT32                                                 reserved4315;	//0xC4F44648
	UINT32                                                 reserved4316;	//0xC4F4464C
	UINT32                                                 reserved4317;	//0xC4F44650
	UINT32                                                 reserved4318;	//0xC4F44654
	UINT32                                                 reserved4319;	//0xC4F44658
	UINT32                                                 reserved4320;	//0xC4F4465C
	UINT32                                                 reserved4321;	//0xC4F44660
	UINT32                                                 reserved4322;	//0xC4F44664
	UINT32                                                 reserved4323;	//0xC4F44668
	UINT32                                                 reserved4324;	//0xC4F4466C
	UINT32                                                 reserved4325;	//0xC4F44670
	UINT32                                                 reserved4326;	//0xC4F44674
	UINT32                                                 reserved4327;	//0xC4F44678
	UINT32                                                 reserved4328;	//0xC4F4467C
	UINT32                                                 reserved4329;	//0xC4F44680
	UINT32                                                 reserved4330;	//0xC4F44684
	UINT32                                                 reserved4331;	//0xC4F44688
	UINT32                                                 reserved4332;	//0xC4F4468C
	UINT32                                                 reserved4333;	//0xC4F44690
	UINT32                                                 reserved4334;	//0xC4F44694
	UINT32                                                 reserved4335;	//0xC4F44698
	UINT32                                                 reserved4336;	//0xC4F4469C
	UINT32                                                 reserved4337;	//0xC4F446A0
	UINT32                                                 reserved4338;	//0xC4F446A4
	UINT32                                                 reserved4339;	//0xC4F446A8
	UINT32                                                 reserved4340;	//0xC4F446AC
	UINT32                                                 reserved4341;	//0xC4F446B0
	UINT32                                                 reserved4342;	//0xC4F446B4
	UINT32                                                 reserved4343;	//0xC4F446B8
	UINT32                                                 reserved4344;	//0xC4F446BC
	UINT32                                                 reserved4345;	//0xC4F446C0
	UINT32                                                 reserved4346;	//0xC4F446C4
	UINT32                                                 reserved4347;	//0xC4F446C8
	UINT32                                                 reserved4348;	//0xC4F446CC
	UINT32                                                 reserved4349;	//0xC4F446D0
	UINT32                                                 reserved4350;	//0xC4F446D4
	UINT32                                                 reserved4351;	//0xC4F446D8
	UINT32                                                 reserved4352;	//0xC4F446DC
	UINT32                                                 reserved4353;	//0xC4F446E0
	UINT32                                                 reserved4354;	//0xC4F446E4
	UINT32                                                 reserved4355;	//0xC4F446E8
	UINT32                                                 reserved4356;	//0xC4F446EC
	UINT32                                                 reserved4357;	//0xC4F446F0
	UINT32                                                 reserved4358;	//0xC4F446F4
	UINT32                                                 reserved4359;	//0xC4F446F8
	UINT32                                                 reserved4360;	//0xC4F446FC
	UINT32                                                 reserved4361;	//0xC4F44700
	UINT32                                                 reserved4362;	//0xC4F44704
	UINT32                                                 reserved4363;	//0xC4F44708
	UINT32                                                 reserved4364;	//0xC4F4470C
	UINT32                                                 reserved4365;	//0xC4F44710
	UINT32                                                 reserved4366;	//0xC4F44714
	UINT32                                                 reserved4367;	//0xC4F44718
	UINT32                                                 reserved4368;	//0xC4F4471C
	UINT32                                                 reserved4369;	//0xC4F44720
	UINT32                                                 reserved4370;	//0xC4F44724
	UINT32                                                 reserved4371;	//0xC4F44728
	UINT32                                                 reserved4372;	//0xC4F4472C
	UINT32                                                 reserved4373;	//0xC4F44730
	UINT32                                                 reserved4374;	//0xC4F44734
	UINT32                                                 reserved4375;	//0xC4F44738
	UINT32                                                 reserved4376;	//0xC4F4473C
	UINT32                                                 reserved4377;	//0xC4F44740
	UINT32                                                 reserved4378;	//0xC4F44744
	UINT32                                                 reserved4379;	//0xC4F44748
	UINT32                                                 reserved4380;	//0xC4F4474C
	UINT32                                                 reserved4381;	//0xC4F44750
	UINT32                                                 reserved4382;	//0xC4F44754
	UINT32                                                 reserved4383;	//0xC4F44758
	UINT32                                                 reserved4384;	//0xC4F4475C
	UINT32                                                 reserved4385;	//0xC4F44760
	UINT32                                                 reserved4386;	//0xC4F44764
	UINT32                                                 reserved4387;	//0xC4F44768
	UINT32                                                 reserved4388;	//0xC4F4476C
	UINT32                                                 reserved4389;	//0xC4F44770
	UINT32                                                 reserved4390;	//0xC4F44774
	UINT32                                                 reserved4391;	//0xC4F44778
	UINT32                                                 reserved4392;	//0xC4F4477C
	UINT32                                                 reserved4393;	//0xC4F44780
	UINT32                                                 reserved4394;	//0xC4F44784
	UINT32                                                 reserved4395;	//0xC4F44788
	UINT32                                                 reserved4396;	//0xC4F4478C
	UINT32                                                 reserved4397;	//0xC4F44790
	UINT32                                                 reserved4398;	//0xC4F44794
	UINT32                                                 reserved4399;	//0xC4F44798
	UINT32                                                 reserved4400;	//0xC4F4479C
	UINT32                                                 reserved4401;	//0xC4F447A0
	UINT32                                                 reserved4402;	//0xC4F447A4
	UINT32                                                 reserved4403;	//0xC4F447A8
	UINT32                                                 reserved4404;	//0xC4F447AC
	UINT32                                                 reserved4405;	//0xC4F447B0
	UINT32                                                 reserved4406;	//0xC4F447B4
	UINT32                                                 reserved4407;	//0xC4F447B8
	UINT32                                                 reserved4408;	//0xC4F447BC
	UINT32                                                 reserved4409;	//0xC4F447C0
	UINT32                                                 reserved4410;	//0xC4F447C4
	UINT32                                                 reserved4411;	//0xC4F447C8
	UINT32                                                 reserved4412;	//0xC4F447CC
	UINT32                                                 reserved4413;	//0xC4F447D0
	UINT32                                                 reserved4414;	//0xC4F447D4
	UINT32                                                 reserved4415;	//0xC4F447D8
	UINT32                                                 reserved4416;	//0xC4F447DC
	UINT32                                                 reserved4417;	//0xC4F447E0
	UINT32                                                 reserved4418;	//0xC4F447E4
	UINT32                                                 reserved4419;	//0xC4F447E8
	UINT32                                                 reserved4420;	//0xC4F447EC
	UINT32                                                 reserved4421;	//0xC4F447F0
	UINT32                                                 reserved4422;	//0xC4F447F4
	UINT32                                                 reserved4423;	//0xC4F447F8
	UINT32                                                 reserved4424;	//0xC4F447FC
	UINT32                                                 reserved4425;	//0xC4F44800
	UINT32                                                 reserved4426;	//0xC4F44804
	UINT32                                                 reserved4427;	//0xC4F44808
	UINT32                                                 reserved4428;	//0xC4F4480C
	UINT32                                                 reserved4429;	//0xC4F44810
	UINT32                                                 reserved4430;	//0xC4F44814
	UINT32                                                 reserved4431;	//0xC4F44818
	UINT32                                                 reserved4432;	//0xC4F4481C
	UINT32                                                 reserved4433;	//0xC4F44820
	UINT32                                                 reserved4434;	//0xC4F44824
	UINT32                                                 reserved4435;	//0xC4F44828
	UINT32                                                 reserved4436;	//0xC4F4482C
	UINT32                                                 reserved4437;	//0xC4F44830
	UINT32                                                 reserved4438;	//0xC4F44834
	UINT32                                                 reserved4439;	//0xC4F44838
	UINT32                                                 reserved4440;	//0xC4F4483C
	UINT32                                                 reserved4441;	//0xC4F44840
	UINT32                                                 reserved4442;	//0xC4F44844
	UINT32                                                 reserved4443;	//0xC4F44848
	UINT32                                                 reserved4444;	//0xC4F4484C
	UINT32                                                 reserved4445;	//0xC4F44850
	UINT32                                                 reserved4446;	//0xC4F44854
	UINT32                                                 reserved4447;	//0xC4F44858
	UINT32                                                 reserved4448;	//0xC4F4485C
	UINT32                                                 reserved4449;	//0xC4F44860
	UINT32                                                 reserved4450;	//0xC4F44864
	UINT32                                                 reserved4451;	//0xC4F44868
	UINT32                                                 reserved4452;	//0xC4F4486C
	UINT32                                                 reserved4453;	//0xC4F44870
	UINT32                                                 reserved4454;	//0xC4F44874
	UINT32                                                 reserved4455;	//0xC4F44878
	UINT32                                                 reserved4456;	//0xC4F4487C
	UINT32                                                 reserved4457;	//0xC4F44880
	UINT32                                                 reserved4458;	//0xC4F44884
	UINT32                                                 reserved4459;	//0xC4F44888
	UINT32                                                 reserved4460;	//0xC4F4488C
	UINT32                                                 reserved4461;	//0xC4F44890
	UINT32                                                 reserved4462;	//0xC4F44894
	UINT32                                                 reserved4463;	//0xC4F44898
	UINT32                                                 reserved4464;	//0xC4F4489C
	UINT32                                                 reserved4465;	//0xC4F448A0
	UINT32                                                 reserved4466;	//0xC4F448A4
	UINT32                                                 reserved4467;	//0xC4F448A8
	UINT32                                                 reserved4468;	//0xC4F448AC
	UINT32                                                 reserved4469;	//0xC4F448B0
	UINT32                                                 reserved4470;	//0xC4F448B4
	UINT32                                                 reserved4471;	//0xC4F448B8
	UINT32                                                 reserved4472;	//0xC4F448BC
	UINT32                                                 reserved4473;	//0xC4F448C0
	UINT32                                                 reserved4474;	//0xC4F448C4
	UINT32                                                 reserved4475;	//0xC4F448C8
	UINT32                                                 reserved4476;	//0xC4F448CC
	UINT32                                                 reserved4477;	//0xC4F448D0
	UINT32                                                 reserved4478;	//0xC4F448D4
	UINT32                                                 reserved4479;	//0xC4F448D8
	UINT32                                                 reserved4480;	//0xC4F448DC
	UINT32                                                 reserved4481;	//0xC4F448E0
	UINT32                                                 reserved4482;	//0xC4F448E4
	UINT32                                                 reserved4483;	//0xC4F448E8
	UINT32                                                 reserved4484;	//0xC4F448EC
	UINT32                                                 reserved4485;	//0xC4F448F0
	UINT32                                                 reserved4486;	//0xC4F448F4
	UINT32                                                 reserved4487;	//0xC4F448F8
	UINT32                                                 reserved4488;	//0xC4F448FC
	UINT32                                                 reserved4489;	//0xC4F44900
	UINT32                                                 reserved4490;	//0xC4F44904
	UINT32                                                 reserved4491;	//0xC4F44908
	UINT32                                                 reserved4492;	//0xC4F4490C
	UINT32                                                 reserved4493;	//0xC4F44910
	UINT32                                                 reserved4494;	//0xC4F44914
	UINT32                                                 reserved4495;	//0xC4F44918
	UINT32                                                 reserved4496;	//0xC4F4491C
	UINT32                                                 reserved4497;	//0xC4F44920
	UINT32                                                 reserved4498;	//0xC4F44924
	UINT32                                                 reserved4499;	//0xC4F44928
	UINT32                                                 reserved4500;	//0xC4F4492C
	UINT32                                                 reserved4501;	//0xC4F44930
	UINT32                                                 reserved4502;	//0xC4F44934
	UINT32                                                 reserved4503;	//0xC4F44938
	UINT32                                                 reserved4504;	//0xC4F4493C
	UINT32                                                 reserved4505;	//0xC4F44940
	UINT32                                                 reserved4506;	//0xC4F44944
	UINT32                                                 reserved4507;	//0xC4F44948
	UINT32                                                 reserved4508;	//0xC4F4494C
	UINT32                                                 reserved4509;	//0xC4F44950
	UINT32                                                 reserved4510;	//0xC4F44954
	UINT32                                                 reserved4511;	//0xC4F44958
	UINT32                                                 reserved4512;	//0xC4F4495C
	UINT32                                                 reserved4513;	//0xC4F44960
	UINT32                                                 reserved4514;	//0xC4F44964
	UINT32                                                 reserved4515;	//0xC4F44968
	UINT32                                                 reserved4516;	//0xC4F4496C
	UINT32                                                 reserved4517;	//0xC4F44970
	UINT32                                                 reserved4518;	//0xC4F44974
	UINT32                                                 reserved4519;	//0xC4F44978
	UINT32                                                 reserved4520;	//0xC4F4497C
	UINT32                                                 reserved4521;	//0xC4F44980
	UINT32                                                 reserved4522;	//0xC4F44984
	UINT32                                                 reserved4523;	//0xC4F44988
	UINT32                                                 reserved4524;	//0xC4F4498C
	UINT32                                                 reserved4525;	//0xC4F44990
	UINT32                                                 reserved4526;	//0xC4F44994
	UINT32                                                 reserved4527;	//0xC4F44998
	UINT32                                                 reserved4528;	//0xC4F4499C
	UINT32                                                 reserved4529;	//0xC4F449A0
	UINT32                                                 reserved4530;	//0xC4F449A4
	UINT32                                                 reserved4531;	//0xC4F449A8
	UINT32                                                 reserved4532;	//0xC4F449AC
	UINT32                                                 reserved4533;	//0xC4F449B0
	UINT32                                                 reserved4534;	//0xC4F449B4
	UINT32                                                 reserved4535;	//0xC4F449B8
	UINT32                                                 reserved4536;	//0xC4F449BC
	UINT32                                                 reserved4537;	//0xC4F449C0
	UINT32                                                 reserved4538;	//0xC4F449C4
	UINT32                                                 reserved4539;	//0xC4F449C8
	UINT32                                                 reserved4540;	//0xC4F449CC
	UINT32                                                 reserved4541;	//0xC4F449D0
	UINT32                                                 reserved4542;	//0xC4F449D4
	UINT32                                                 reserved4543;	//0xC4F449D8
	UINT32                                                 reserved4544;	//0xC4F449DC
	UINT32                                                 reserved4545;	//0xC4F449E0
	UINT32                                                 reserved4546;	//0xC4F449E4
	UINT32                                                 reserved4547;	//0xC4F449E8
	UINT32                                                 reserved4548;	//0xC4F449EC
	UINT32                                                 reserved4549;	//0xC4F449F0
	UINT32                                                 reserved4550;	//0xC4F449F4
	UINT32                                                 reserved4551;	//0xC4F449F8
	UINT32                                                 reserved4552;	//0xC4F449FC
	UINT32                                                 reserved4553;	//0xC4F44A00
	UINT32                                                 reserved4554;	//0xC4F44A04
	UINT32                                                 reserved4555;	//0xC4F44A08
	UINT32                                                 reserved4556;	//0xC4F44A0C
	UINT32                                                 reserved4557;	//0xC4F44A10
	UINT32                                                 reserved4558;	//0xC4F44A14
	UINT32                                                 reserved4559;	//0xC4F44A18
	UINT32                                                 reserved4560;	//0xC4F44A1C
	UINT32                                                 reserved4561;	//0xC4F44A20
	UINT32                                                 reserved4562;	//0xC4F44A24
	UINT32                                                 reserved4563;	//0xC4F44A28
	UINT32                                                 reserved4564;	//0xC4F44A2C
	UINT32                                                 reserved4565;	//0xC4F44A30
	UINT32                                                 reserved4566;	//0xC4F44A34
	UINT32                                                 reserved4567;	//0xC4F44A38
	UINT32                                                 reserved4568;	//0xC4F44A3C
	UINT32                                                 reserved4569;	//0xC4F44A40
	UINT32                                                 reserved4570;	//0xC4F44A44
	UINT32                                                 reserved4571;	//0xC4F44A48
	UINT32                                                 reserved4572;	//0xC4F44A4C
	UINT32                                                 reserved4573;	//0xC4F44A50
	UINT32                                                 reserved4574;	//0xC4F44A54
	UINT32                                                 reserved4575;	//0xC4F44A58
	UINT32                                                 reserved4576;	//0xC4F44A5C
	UINT32                                                 reserved4577;	//0xC4F44A60
	UINT32                                                 reserved4578;	//0xC4F44A64
	UINT32                                                 reserved4579;	//0xC4F44A68
	UINT32                                                 reserved4580;	//0xC4F44A6C
	UINT32                                                 reserved4581;	//0xC4F44A70
	UINT32                                                 reserved4582;	//0xC4F44A74
	UINT32                                                 reserved4583;	//0xC4F44A78
	UINT32                                                 reserved4584;	//0xC4F44A7C
	UINT32                                                 reserved4585;	//0xC4F44A80
	UINT32                                                 reserved4586;	//0xC4F44A84
	UINT32                                                 reserved4587;	//0xC4F44A88
	UINT32                                                 reserved4588;	//0xC4F44A8C
	UINT32                                                 reserved4589;	//0xC4F44A90
	UINT32                                                 reserved4590;	//0xC4F44A94
	UINT32                                                 reserved4591;	//0xC4F44A98
	UINT32                                                 reserved4592;	//0xC4F44A9C
	UINT32                                                 reserved4593;	//0xC4F44AA0
	UINT32                                                 reserved4594;	//0xC4F44AA4
	UINT32                                                 reserved4595;	//0xC4F44AA8
	UINT32                                                 reserved4596;	//0xC4F44AAC
	UINT32                                                 reserved4597;	//0xC4F44AB0
	UINT32                                                 reserved4598;	//0xC4F44AB4
	UINT32                                                 reserved4599;	//0xC4F44AB8
	UINT32                                                 reserved4600;	//0xC4F44ABC
	UINT32                                                 reserved4601;	//0xC4F44AC0
	UINT32                                                 reserved4602;	//0xC4F44AC4
	UINT32                                                 reserved4603;	//0xC4F44AC8
	UINT32                                                 reserved4604;	//0xC4F44ACC
	UINT32                                                 reserved4605;	//0xC4F44AD0
	UINT32                                                 reserved4606;	//0xC4F44AD4
	UINT32                                                 reserved4607;	//0xC4F44AD8
	UINT32                                                 reserved4608;	//0xC4F44ADC
	UINT32                                                 reserved4609;	//0xC4F44AE0
	UINT32                                                 reserved4610;	//0xC4F44AE4
	UINT32                                                 reserved4611;	//0xC4F44AE8
	UINT32                                                 reserved4612;	//0xC4F44AEC
	UINT32                                                 reserved4613;	//0xC4F44AF0
	UINT32                                                 reserved4614;	//0xC4F44AF4
	UINT32                                                 reserved4615;	//0xC4F44AF8
	UINT32                                                 reserved4616;	//0xC4F44AFC
	UINT32                                                 reserved4617;	//0xC4F44B00
	UINT32                                                 reserved4618;	//0xC4F44B04
	UINT32                                                 reserved4619;	//0xC4F44B08
	UINT32                                                 reserved4620;	//0xC4F44B0C
	UINT32                                                 reserved4621;	//0xC4F44B10
	UINT32                                                 reserved4622;	//0xC4F44B14
	UINT32                                                 reserved4623;	//0xC4F44B18
	UINT32                                                 reserved4624;	//0xC4F44B1C
	UINT32                                                 reserved4625;	//0xC4F44B20
	UINT32                                                 reserved4626;	//0xC4F44B24
	UINT32                                                 reserved4627;	//0xC4F44B28
	UINT32                                                 reserved4628;	//0xC4F44B2C
	UINT32                                                 reserved4629;	//0xC4F44B30
	UINT32                                                 reserved4630;	//0xC4F44B34
	UINT32                                                 reserved4631;	//0xC4F44B38
	UINT32                                                 reserved4632;	//0xC4F44B3C
	UINT32                                                 reserved4633;	//0xC4F44B40
	UINT32                                                 reserved4634;	//0xC4F44B44
	UINT32                                                 reserved4635;	//0xC4F44B48
	UINT32                                                 reserved4636;	//0xC4F44B4C
	UINT32                                                 reserved4637;	//0xC4F44B50
	UINT32                                                 reserved4638;	//0xC4F44B54
	UINT32                                                 reserved4639;	//0xC4F44B58
	UINT32                                                 reserved4640;	//0xC4F44B5C
	UINT32                                                 reserved4641;	//0xC4F44B60
	UINT32                                                 reserved4642;	//0xC4F44B64
	UINT32                                                 reserved4643;	//0xC4F44B68
	UINT32                                                 reserved4644;	//0xC4F44B6C
	UINT32                                                 reserved4645;	//0xC4F44B70
	UINT32                                                 reserved4646;	//0xC4F44B74
	UINT32                                                 reserved4647;	//0xC4F44B78
	UINT32                                                 reserved4648;	//0xC4F44B7C
	UINT32                                                 reserved4649;	//0xC4F44B80
	UINT32                                                 reserved4650;	//0xC4F44B84
	UINT32                                                 reserved4651;	//0xC4F44B88
	UINT32                                                 reserved4652;	//0xC4F44B8C
	UINT32                                                 reserved4653;	//0xC4F44B90
	UINT32                                                 reserved4654;	//0xC4F44B94
	UINT32                                                 reserved4655;	//0xC4F44B98
	UINT32                                                 reserved4656;	//0xC4F44B9C
	UINT32                                                 reserved4657;	//0xC4F44BA0
	UINT32                                                 reserved4658;	//0xC4F44BA4
	UINT32                                                 reserved4659;	//0xC4F44BA8
	UINT32                                                 reserved4660;	//0xC4F44BAC
	UINT32                                                 reserved4661;	//0xC4F44BB0
	UINT32                                                 reserved4662;	//0xC4F44BB4
	UINT32                                                 reserved4663;	//0xC4F44BB8
	UINT32                                                 reserved4664;	//0xC4F44BBC
	UINT32                                                 reserved4665;	//0xC4F44BC0
	UINT32                                                 reserved4666;	//0xC4F44BC4
	UINT32                                                 reserved4667;	//0xC4F44BC8
	UINT32                                                 reserved4668;	//0xC4F44BCC
	UINT32                                                 reserved4669;	//0xC4F44BD0
	UINT32                                                 reserved4670;	//0xC4F44BD4
	UINT32                                                 reserved4671;	//0xC4F44BD8
	UINT32                                                 reserved4672;	//0xC4F44BDC
	UINT32                                                 reserved4673;	//0xC4F44BE0
	UINT32                                                 reserved4674;	//0xC4F44BE4
	UINT32                                                 reserved4675;	//0xC4F44BE8
	UINT32                                                 reserved4676;	//0xC4F44BEC
	UINT32                                                 reserved4677;	//0xC4F44BF0
	UINT32                                                 reserved4678;	//0xC4F44BF4
	UINT32                                                 reserved4679;	//0xC4F44BF8
	UINT32                                                 reserved4680;	//0xC4F44BFC
	UINT32                                                 reserved4681;	//0xC4F44C00
	UINT32                                                 reserved4682;	//0xC4F44C04
	UINT32                                                 reserved4683;	//0xC4F44C08
	UINT32                                                 reserved4684;	//0xC4F44C0C
	UINT32                                                 reserved4685;	//0xC4F44C10
	UINT32                                                 reserved4686;	//0xC4F44C14
	UINT32                                                 reserved4687;	//0xC4F44C18
	UINT32                                                 reserved4688;	//0xC4F44C1C
	UINT32                                                 reserved4689;	//0xC4F44C20
	UINT32                                                 reserved4690;	//0xC4F44C24
	UINT32                                                 reserved4691;	//0xC4F44C28
	UINT32                                                 reserved4692;	//0xC4F44C2C
	UINT32                                                 reserved4693;	//0xC4F44C30
	UINT32                                                 reserved4694;	//0xC4F44C34
	UINT32                                                 reserved4695;	//0xC4F44C38
	UINT32                                                 reserved4696;	//0xC4F44C3C
	UINT32                                                 reserved4697;	//0xC4F44C40
	UINT32                                                 reserved4698;	//0xC4F44C44
	UINT32                                                 reserved4699;	//0xC4F44C48
	UINT32                                                 reserved4700;	//0xC4F44C4C
	UINT32                                                 reserved4701;	//0xC4F44C50
	UINT32                                                 reserved4702;	//0xC4F44C54
	UINT32                                                 reserved4703;	//0xC4F44C58
	UINT32                                                 reserved4704;	//0xC4F44C5C
	UINT32                                                 reserved4705;	//0xC4F44C60
	UINT32                                                 reserved4706;	//0xC4F44C64
	UINT32                                                 reserved4707;	//0xC4F44C68
	UINT32                                                 reserved4708;	//0xC4F44C6C
	UINT32                                                 reserved4709;	//0xC4F44C70
	UINT32                                                 reserved4710;	//0xC4F44C74
	UINT32                                                 reserved4711;	//0xC4F44C78
	UINT32                                                 reserved4712;	//0xC4F44C7C
	UINT32                                                 reserved4713;	//0xC4F44C80
	UINT32                                                 reserved4714;	//0xC4F44C84
	UINT32                                                 reserved4715;	//0xC4F44C88
	UINT32                                                 reserved4716;	//0xC4F44C8C
	UINT32                                                 reserved4717;	//0xC4F44C90
	UINT32                                                 reserved4718;	//0xC4F44C94
	UINT32                                                 reserved4719;	//0xC4F44C98
	UINT32                                                 reserved4720;	//0xC4F44C9C
	UINT32                                                 reserved4721;	//0xC4F44CA0
	UINT32                                                 reserved4722;	//0xC4F44CA4
	UINT32                                                 reserved4723;	//0xC4F44CA8
	UINT32                                                 reserved4724;	//0xC4F44CAC
	UINT32                                                 reserved4725;	//0xC4F44CB0
	UINT32                                                 reserved4726;	//0xC4F44CB4
	UINT32                                                 reserved4727;	//0xC4F44CB8
	UINT32                                                 reserved4728;	//0xC4F44CBC
	UINT32                                                 reserved4729;	//0xC4F44CC0
	UINT32                                                 reserved4730;	//0xC4F44CC4
	UINT32                                                 reserved4731;	//0xC4F44CC8
	UINT32                                                 reserved4732;	//0xC4F44CCC
	UINT32                                                 reserved4733;	//0xC4F44CD0
	UINT32                                                 reserved4734;	//0xC4F44CD4
	UINT32                                                 reserved4735;	//0xC4F44CD8
	UINT32                                                 reserved4736;	//0xC4F44CDC
	UINT32                                                 reserved4737;	//0xC4F44CE0
	UINT32                                                 reserved4738;	//0xC4F44CE4
	UINT32                                                 reserved4739;	//0xC4F44CE8
	UINT32                                                 reserved4740;	//0xC4F44CEC
	UINT32                                                 reserved4741;	//0xC4F44CF0
	UINT32                                                 reserved4742;	//0xC4F44CF4
	UINT32                                                 reserved4743;	//0xC4F44CF8
	UINT32                                                 reserved4744;	//0xC4F44CFC
	UINT32                                                 reserved4745;	//0xC4F44D00
	UINT32                                                 reserved4746;	//0xC4F44D04
	UINT32                                                 reserved4747;	//0xC4F44D08
	UINT32                                                 reserved4748;	//0xC4F44D0C
	UINT32                                                 reserved4749;	//0xC4F44D10
	UINT32                                                 reserved4750;	//0xC4F44D14
	UINT32                                                 reserved4751;	//0xC4F44D18
	UINT32                                                 reserved4752;	//0xC4F44D1C
	UINT32                                                 reserved4753;	//0xC4F44D20
	UINT32                                                 reserved4754;	//0xC4F44D24
	UINT32                                                 reserved4755;	//0xC4F44D28
	UINT32                                                 reserved4756;	//0xC4F44D2C
	UINT32                                                 reserved4757;	//0xC4F44D30
	UINT32                                                 reserved4758;	//0xC4F44D34
	UINT32                                                 reserved4759;	//0xC4F44D38
	UINT32                                                 reserved4760;	//0xC4F44D3C
	UINT32                                                 reserved4761;	//0xC4F44D40
	UINT32                                                 reserved4762;	//0xC4F44D44
	UINT32                                                 reserved4763;	//0xC4F44D48
	UINT32                                                 reserved4764;	//0xC4F44D4C
	UINT32                                                 reserved4765;	//0xC4F44D50
	UINT32                                                 reserved4766;	//0xC4F44D54
	UINT32                                                 reserved4767;	//0xC4F44D58
	UINT32                                                 reserved4768;	//0xC4F44D5C
	UINT32                                                 reserved4769;	//0xC4F44D60
	UINT32                                                 reserved4770;	//0xC4F44D64
	UINT32                                                 reserved4771;	//0xC4F44D68
	UINT32                                                 reserved4772;	//0xC4F44D6C
	UINT32                                                 reserved4773;	//0xC4F44D70
	UINT32                                                 reserved4774;	//0xC4F44D74
	UINT32                                                 reserved4775;	//0xC4F44D78
	UINT32                                                 reserved4776;	//0xC4F44D7C
	UINT32                                                 reserved4777;	//0xC4F44D80
	UINT32                                                 reserved4778;	//0xC4F44D84
	UINT32                                                 reserved4779;	//0xC4F44D88
	UINT32                                                 reserved4780;	//0xC4F44D8C
	UINT32                                                 reserved4781;	//0xC4F44D90
	UINT32                                                 reserved4782;	//0xC4F44D94
	UINT32                                                 reserved4783;	//0xC4F44D98
	UINT32                                                 reserved4784;	//0xC4F44D9C
	UINT32                                                 reserved4785;	//0xC4F44DA0
	UINT32                                                 reserved4786;	//0xC4F44DA4
	UINT32                                                 reserved4787;	//0xC4F44DA8
	UINT32                                                 reserved4788;	//0xC4F44DAC
	UINT32                                                 reserved4789;	//0xC4F44DB0
	UINT32                                                 reserved4790;	//0xC4F44DB4
	UINT32                                                 reserved4791;	//0xC4F44DB8
	UINT32                                                 reserved4792;	//0xC4F44DBC
	UINT32                                                 reserved4793;	//0xC4F44DC0
	UINT32                                                 reserved4794;	//0xC4F44DC4
	UINT32                                                 reserved4795;	//0xC4F44DC8
	UINT32                                                 reserved4796;	//0xC4F44DCC
	UINT32                                                 reserved4797;	//0xC4F44DD0
	UINT32                                                 reserved4798;	//0xC4F44DD4
	UINT32                                                 reserved4799;	//0xC4F44DD8
	UINT32                                                 reserved4800;	//0xC4F44DDC
	UINT32                                                 reserved4801;	//0xC4F44DE0
	UINT32                                                 reserved4802;	//0xC4F44DE4
	UINT32                                                 reserved4803;	//0xC4F44DE8
	UINT32                                                 reserved4804;	//0xC4F44DEC
	UINT32                                                 reserved4805;	//0xC4F44DF0
	UINT32                                                 reserved4806;	//0xC4F44DF4
	UINT32                                                 reserved4807;	//0xC4F44DF8
	UINT32                                                 reserved4808;	//0xC4F44DFC
	UINT32                                                 reserved4809;	//0xC4F44E00
	UINT32                                                 reserved4810;	//0xC4F44E04
	UINT32                                                 reserved4811;	//0xC4F44E08
	UINT32                                                 reserved4812;	//0xC4F44E0C
	UINT32                                                 reserved4813;	//0xC4F44E10
	UINT32                                                 reserved4814;	//0xC4F44E14
	UINT32                                                 reserved4815;	//0xC4F44E18
	UINT32                                                 reserved4816;	//0xC4F44E1C
	UINT32                                                 reserved4817;	//0xC4F44E20
	UINT32                                                 reserved4818;	//0xC4F44E24
	UINT32                                                 reserved4819;	//0xC4F44E28
	UINT32                                                 reserved4820;	//0xC4F44E2C
	UINT32                                                 reserved4821;	//0xC4F44E30
	UINT32                                                 reserved4822;	//0xC4F44E34
	UINT32                                                 reserved4823;	//0xC4F44E38
	UINT32                                                 reserved4824;	//0xC4F44E3C
	UINT32                                                 reserved4825;	//0xC4F44E40
	UINT32                                                 reserved4826;	//0xC4F44E44
	UINT32                                                 reserved4827;	//0xC4F44E48
	UINT32                                                 reserved4828;	//0xC4F44E4C
	UINT32                                                 reserved4829;	//0xC4F44E50
	UINT32                                                 reserved4830;	//0xC4F44E54
	UINT32                                                 reserved4831;	//0xC4F44E58
	UINT32                                                 reserved4832;	//0xC4F44E5C
	UINT32                                                 reserved4833;	//0xC4F44E60
	UINT32                                                 reserved4834;	//0xC4F44E64
	UINT32                                                 reserved4835;	//0xC4F44E68
	UINT32                                                 reserved4836;	//0xC4F44E6C
	UINT32                                                 reserved4837;	//0xC4F44E70
	UINT32                                                 reserved4838;	//0xC4F44E74
	UINT32                                                 reserved4839;	//0xC4F44E78
	UINT32                                                 reserved4840;	//0xC4F44E7C
	UINT32                                                 reserved4841;	//0xC4F44E80
	UINT32                                                 reserved4842;	//0xC4F44E84
	UINT32                                                 reserved4843;	//0xC4F44E88
	UINT32                                                 reserved4844;	//0xC4F44E8C
	UINT32                                                 reserved4845;	//0xC4F44E90
	UINT32                                                 reserved4846;	//0xC4F44E94
	UINT32                                                 reserved4847;	//0xC4F44E98
	UINT32                                                 reserved4848;	//0xC4F44E9C
	UINT32                                                 reserved4849;	//0xC4F44EA0
	UINT32                                                 reserved4850;	//0xC4F44EA4
	UINT32                                                 reserved4851;	//0xC4F44EA8
	UINT32                                                 reserved4852;	//0xC4F44EAC
	UINT32                                                 reserved4853;	//0xC4F44EB0
	UINT32                                                 reserved4854;	//0xC4F44EB4
	UINT32                                                 reserved4855;	//0xC4F44EB8
	UINT32                                                 reserved4856;	//0xC4F44EBC
	UINT32                                                 reserved4857;	//0xC4F44EC0
	UINT32                                                 reserved4858;	//0xC4F44EC4
	UINT32                                                 reserved4859;	//0xC4F44EC8
	UINT32                                                 reserved4860;	//0xC4F44ECC
	UINT32                                                 reserved4861;	//0xC4F44ED0
	UINT32                                                 reserved4862;	//0xC4F44ED4
	UINT32                                                 reserved4863;	//0xC4F44ED8
	UINT32                                                 reserved4864;	//0xC4F44EDC
	UINT32                                                 reserved4865;	//0xC4F44EE0
	UINT32                                                 reserved4866;	//0xC4F44EE4
	UINT32                                                 reserved4867;	//0xC4F44EE8
	UINT32                                                 reserved4868;	//0xC4F44EEC
	UINT32                                                 reserved4869;	//0xC4F44EF0
	UINT32                                                 reserved4870;	//0xC4F44EF4
	UINT32                                                 reserved4871;	//0xC4F44EF8
	UINT32                                                 reserved4872;	//0xC4F44EFC
	UINT32                                                 reserved4873;	//0xC4F44F00
	UINT32                                                 reserved4874;	//0xC4F44F04
	UINT32                                                 reserved4875;	//0xC4F44F08
	UINT32                                                 reserved4876;	//0xC4F44F0C
	UINT32                                                 reserved4877;	//0xC4F44F10
	UINT32                                                 reserved4878;	//0xC4F44F14
	UINT32                                                 reserved4879;	//0xC4F44F18
	UINT32                                                 reserved4880;	//0xC4F44F1C
	UINT32                                                 reserved4881;	//0xC4F44F20
	UINT32                                                 reserved4882;	//0xC4F44F24
	UINT32                                                 reserved4883;	//0xC4F44F28
	UINT32                                                 reserved4884;	//0xC4F44F2C
	UINT32                                                 reserved4885;	//0xC4F44F30
	UINT32                                                 reserved4886;	//0xC4F44F34
	UINT32                                                 reserved4887;	//0xC4F44F38
	UINT32                                                 reserved4888;	//0xC4F44F3C
	UINT32                                                 reserved4889;	//0xC4F44F40
	UINT32                                                 reserved4890;	//0xC4F44F44
	UINT32                                                 reserved4891;	//0xC4F44F48
	UINT32                                                 reserved4892;	//0xC4F44F4C
	UINT32                                                 reserved4893;	//0xC4F44F50
	UINT32                                                 reserved4894;	//0xC4F44F54
	UINT32                                                 reserved4895;	//0xC4F44F58
	UINT32                                                 reserved4896;	//0xC4F44F5C
	UINT32                                                 reserved4897;	//0xC4F44F60
	UINT32                                                 reserved4898;	//0xC4F44F64
	UINT32                                                 reserved4899;	//0xC4F44F68
	UINT32                                                 reserved4900;	//0xC4F44F6C
	UINT32                                                 reserved4901;	//0xC4F44F70
	UINT32                                                 reserved4902;	//0xC4F44F74
	UINT32                                                 reserved4903;	//0xC4F44F78
	UINT32                                                 reserved4904;	//0xC4F44F7C
	UINT32                                                 reserved4905;	//0xC4F44F80
	UINT32                                                 reserved4906;	//0xC4F44F84
	UINT32                                                 reserved4907;	//0xC4F44F88
	UINT32                                                 reserved4908;	//0xC4F44F8C
	UINT32                                                 reserved4909;	//0xC4F44F90
	UINT32                                                 reserved4910;	//0xC4F44F94
	UINT32                                                 reserved4911;	//0xC4F44F98
	UINT32                                                 reserved4912;	//0xC4F44F9C
	UINT32                                                 reserved4913;	//0xC4F44FA0
	UINT32                                                 reserved4914;	//0xC4F44FA4
	UINT32                                                 reserved4915;	//0xC4F44FA8
	UINT32                                                 reserved4916;	//0xC4F44FAC
	UINT32                                                 reserved4917;	//0xC4F44FB0
	UINT32                                                 reserved4918;	//0xC4F44FB4
	UINT32                                                 reserved4919;	//0xC4F44FB8
	UINT32                                                 reserved4920;	//0xC4F44FBC
	UINT32                                                 reserved4921;	//0xC4F44FC0
	UINT32                                                 reserved4922;	//0xC4F44FC4
	UINT32                                                 reserved4923;	//0xC4F44FC8
	UINT32                                                 reserved4924;	//0xC4F44FCC
	UINT32                                                 reserved4925;	//0xC4F44FD0
	UINT32                                                 reserved4926;	//0xC4F44FD4
	UINT32                                                 reserved4927;	//0xC4F44FD8
	UINT32                                                 reserved4928;	//0xC4F44FDC
	UINT32                                                 reserved4929;	//0xC4F44FE0
	UINT32                                                 reserved4930;	//0xC4F44FE4
	UINT32                                                 reserved4931;	//0xC4F44FE8
	UINT32                                                 reserved4932;	//0xC4F44FEC
	UINT32                                                 reserved4933;	//0xC4F44FF0
	UINT32                                                 reserved4934;	//0xC4F44FF4
	UINT32                                                 reserved4935;	//0xC4F44FF8
	UINT32                                                 reserved4936;	//0xC4F44FFC
	REG_DDRC_M0_DEBUG_COMMON_T                             debug_common;	//0xC4F45000
	REG_DDRC_M0_DEBUG_PERIOD_T                             debug_period;	//0xC4F45004
	UINT32                                                 reserved4937;	//0xC4F45008
	UINT32                                                 reserved4938;	//0xC4F4500C
	REG_DDRC_M0_IRQ_MASK_T                                     irq_mask;	//0xC4F45010
	REG_DDRC_M0_IRQ_STATUS_T                                 irq_status;	//0xC4F45014
	UINT32                                                 reserved4939;	//0xC4F45018
	UINT32                                                 reserved4940;	//0xC4F4501C
	UINT32                                                 reserved4941;	//0xC4F45020
	UINT32                                                 reserved4942;	//0xC4F45024
	UINT32                                                 reserved4943;	//0xC4F45028
	UINT32                                                 reserved4944;	//0xC4F4502C
	UINT32                                                 reserved4945;	//0xC4F45030
	UINT32                                                 reserved4946;	//0xC4F45034
	UINT32                                                 reserved4947;	//0xC4F45038
	UINT32                                                 reserved4948;	//0xC4F4503C
	UINT32                                                 reserved4949;	//0xC4F45040
	UINT32                                                 reserved4950;	//0xC4F45044
	UINT32                                                 reserved4951;	//0xC4F45048
	UINT32                                                 reserved4952;	//0xC4F4504C
	UINT32                                                 reserved4953;	//0xC4F45050
	UINT32                                                 reserved4954;	//0xC4F45054
	UINT32                                                 reserved4955;	//0xC4F45058
	UINT32                                                 reserved4956;	//0xC4F4505C
	UINT32                                                 reserved4957;	//0xC4F45060
	UINT32                                                 reserved4958;	//0xC4F45064
	UINT32                                                 reserved4959;	//0xC4F45068
	UINT32                                                 reserved4960;	//0xC4F4506C
	UINT32                                                 reserved4961;	//0xC4F45070
	UINT32                                                 reserved4962;	//0xC4F45074
	UINT32                                                 reserved4963;	//0xC4F45078
	UINT32                                                 reserved4964;	//0xC4F4507C
	UINT32                                                 reserved4965;	//0xC4F45080
	UINT32                                                 reserved4966;	//0xC4F45084
	UINT32                                                 reserved4967;	//0xC4F45088
	UINT32                                                 reserved4968;	//0xC4F4508C
	UINT32                                                 reserved4969;	//0xC4F45090
	UINT32                                                 reserved4970;	//0xC4F45094
	UINT32                                                 reserved4971;	//0xC4F45098
	UINT32                                                 reserved4972;	//0xC4F4509C
	UINT32                                                 reserved4973;	//0xC4F450A0
	UINT32                                                 reserved4974;	//0xC4F450A4
	UINT32                                                 reserved4975;	//0xC4F450A8
	UINT32                                                 reserved4976;	//0xC4F450AC
	UINT32                                                 reserved4977;	//0xC4F450B0
	UINT32                                                 reserved4978;	//0xC4F450B4
	UINT32                                                 reserved4979;	//0xC4F450B8
	UINT32                                                 reserved4980;	//0xC4F450BC
	UINT32                                                 reserved4981;	//0xC4F450C0
	UINT32                                                 reserved4982;	//0xC4F450C4
	UINT32                                                 reserved4983;	//0xC4F450C8
	UINT32                                                 reserved4984;	//0xC4F450CC
	UINT32                                                 reserved4985;	//0xC4F450D0
	UINT32                                                 reserved4986;	//0xC4F450D4
	UINT32                                                 reserved4987;	//0xC4F450D8
	UINT32                                                 reserved4988;	//0xC4F450DC
	UINT32                                                 reserved4989;	//0xC4F450E0
	UINT32                                                 reserved4990;	//0xC4F450E4
	UINT32                                                 reserved4991;	//0xC4F450E8
	UINT32                                                 reserved4992;	//0xC4F450EC
	UINT32                                                 reserved4993;	//0xC4F450F0
	UINT32                                                 reserved4994;	//0xC4F450F4
	UINT32                                                 reserved4995;	//0xC4F450F8
	UINT32                                                 reserved4996;	//0xC4F450FC
	REG_DDRC_M0_DEBUG_BUS_IF_T                             debug_bus_if;	//0xC4F45100
	UINT32                                                 reserved4997;	//0xC4F45104
	UINT32                                                 reserved4998;	//0xC4F45108
	UINT32                                                 reserved4999;	//0xC4F4510C
	UINT32                                                 reserved5000;	//0xC4F45110
	UINT32                                                 reserved5001;	//0xC4F45114
	UINT32                                                 reserved5002;	//0xC4F45118
	UINT32                                                 reserved5003;	//0xC4F4511C
	UINT32                                                 reserved5004;	//0xC4F45120
	UINT32                                                 reserved5005;	//0xC4F45124
	UINT32                                                 reserved5006;	//0xC4F45128
	UINT32                                                 reserved5007;	//0xC4F4512C
	UINT32                                                 reserved5008;	//0xC4F45130
	UINT32                                                 reserved5009;	//0xC4F45134
	UINT32                                                 reserved5010;	//0xC4F45138
	UINT32                                                 reserved5011;	//0xC4F4513C
	UINT32                                                 reserved5012;	//0xC4F45140
	UINT32                                                 reserved5013;	//0xC4F45144
	UINT32                                                 reserved5014;	//0xC4F45148
	UINT32                                                 reserved5015;	//0xC4F4514C
	UINT32                                                 reserved5016;	//0xC4F45150
	UINT32                                                 reserved5017;	//0xC4F45154
	UINT32                                                 reserved5018;	//0xC4F45158
	UINT32                                                 reserved5019;	//0xC4F4515C
	UINT32                                                 reserved5020;	//0xC4F45160
	UINT32                                                 reserved5021;	//0xC4F45164
	UINT32                                                 reserved5022;	//0xC4F45168
	UINT32                                                 reserved5023;	//0xC4F4516C
	UINT32                                                 reserved5024;	//0xC4F45170
	UINT32                                                 reserved5025;	//0xC4F45174
	UINT32                                                 reserved5026;	//0xC4F45178
	UINT32                                                 reserved5027;	//0xC4F4517C
	UINT32                                                 reserved5028;	//0xC4F45180
	UINT32                                                 reserved5029;	//0xC4F45184
	UINT32                                                 reserved5030;	//0xC4F45188
	UINT32                                                 reserved5031;	//0xC4F4518C
	UINT32                                                 reserved5032;	//0xC4F45190
	UINT32                                                 reserved5033;	//0xC4F45194
	UINT32                                                 reserved5034;	//0xC4F45198
	UINT32                                                 reserved5035;	//0xC4F4519C
	UINT32                                                 reserved5036;	//0xC4F451A0
	UINT32                                                 reserved5037;	//0xC4F451A4
	UINT32                                                 reserved5038;	//0xC4F451A8
	UINT32                                                 reserved5039;	//0xC4F451AC
	UINT32                                                 reserved5040;	//0xC4F451B0
	UINT32                                                 reserved5041;	//0xC4F451B4
	UINT32                                                 reserved5042;	//0xC4F451B8
	UINT32                                                 reserved5043;	//0xC4F451BC
	UINT32                                                 reserved5044;	//0xC4F451C0
	UINT32                                                 reserved5045;	//0xC4F451C4
	UINT32                                                 reserved5046;	//0xC4F451C8
	UINT32                                                 reserved5047;	//0xC4F451CC
	UINT32                                                 reserved5048;	//0xC4F451D0
	UINT32                                                 reserved5049;	//0xC4F451D4
	UINT32                                                 reserved5050;	//0xC4F451D8
	UINT32                                                 reserved5051;	//0xC4F451DC
	UINT32                                                 reserved5052;	//0xC4F451E0
	UINT32                                                 reserved5053;	//0xC4F451E4
	UINT32                                                 reserved5054;	//0xC4F451E8
	UINT32                                                 reserved5055;	//0xC4F451EC
	UINT32                                                 reserved5056;	//0xC4F451F0
	UINT32                                                 reserved5057;	//0xC4F451F4
	UINT32                                                 reserved5058;	//0xC4F451F8
	UINT32                                                 reserved5059;	//0xC4F451FC
	REG_DDRC_M0_DEBUG_PORT_IF_0_T                       debug_port_if_0;	//0xC4F45200
	REG_DDRC_M0_DEBUG_PORT_IF_1_T                       debug_port_if_1;	//0xC4F45204
	REG_DDRC_M0_DEBUG_PORT_IF_2_T                       debug_port_if_2;	//0xC4F45208
	REG_DDRC_M0_DEBUG_PORT_IF_3_T                       debug_port_if_3;	//0xC4F4520C
	REG_DDRC_M0_DEBUG_PORT_IF_4_T                       debug_port_if_4;	//0xC4F45210
	REG_DDRC_M0_DEBUG_PORT_IF_5_T                       debug_port_if_5;	//0xC4F45214
	REG_DDRC_M0_DEBUG_PORT_IF_6_T                       debug_port_if_6;	//0xC4F45218
	REG_DDRC_M0_DEBUG_PORT_IF_7_T                       debug_port_if_7;	//0xC4F4521C
	UINT32                                                 reserved5060;	//0xC4F45220
	UINT32                                                 reserved5061;	//0xC4F45224
	UINT32                                                 reserved5062;	//0xC4F45228
	UINT32                                                 reserved5063;	//0xC4F4522C
	UINT32                                                 reserved5064;	//0xC4F45230
	UINT32                                                 reserved5065;	//0xC4F45234
	UINT32                                                 reserved5066;	//0xC4F45238
	UINT32                                                 reserved5067;	//0xC4F4523C
	UINT32                                                 reserved5068;	//0xC4F45240
	UINT32                                                 reserved5069;	//0xC4F45244
	UINT32                                                 reserved5070;	//0xC4F45248
	UINT32                                                 reserved5071;	//0xC4F4524C
	UINT32                                                 reserved5072;	//0xC4F45250
	UINT32                                                 reserved5073;	//0xC4F45254
	UINT32                                                 reserved5074;	//0xC4F45258
	UINT32                                                 reserved5075;	//0xC4F4525C
	UINT32                                                 reserved5076;	//0xC4F45260
	UINT32                                                 reserved5077;	//0xC4F45264
	UINT32                                                 reserved5078;	//0xC4F45268
	UINT32                                                 reserved5079;	//0xC4F4526C
	UINT32                                                 reserved5080;	//0xC4F45270
	UINT32                                                 reserved5081;	//0xC4F45274
	UINT32                                                 reserved5082;	//0xC4F45278
	UINT32                                                 reserved5083;	//0xC4F4527C
	UINT32                                                 reserved5084;	//0xC4F45280
	UINT32                                                 reserved5085;	//0xC4F45284
	UINT32                                                 reserved5086;	//0xC4F45288
	UINT32                                                 reserved5087;	//0xC4F4528C
	UINT32                                                 reserved5088;	//0xC4F45290
	UINT32                                                 reserved5089;	//0xC4F45294
	UINT32                                                 reserved5090;	//0xC4F45298
	UINT32                                                 reserved5091;	//0xC4F4529C
	UINT32                                                 reserved5092;	//0xC4F452A0
	UINT32                                                 reserved5093;	//0xC4F452A4
	UINT32                                                 reserved5094;	//0xC4F452A8
	UINT32                                                 reserved5095;	//0xC4F452AC
	UINT32                                                 reserved5096;	//0xC4F452B0
	UINT32                                                 reserved5097;	//0xC4F452B4
	UINT32                                                 reserved5098;	//0xC4F452B8
	UINT32                                                 reserved5099;	//0xC4F452BC
	UINT32                                                 reserved5100;	//0xC4F452C0
	UINT32                                                 reserved5101;	//0xC4F452C4
	UINT32                                                 reserved5102;	//0xC4F452C8
	UINT32                                                 reserved5103;	//0xC4F452CC
	UINT32                                                 reserved5104;	//0xC4F452D0
	UINT32                                                 reserved5105;	//0xC4F452D4
	UINT32                                                 reserved5106;	//0xC4F452D8
	UINT32                                                 reserved5107;	//0xC4F452DC
	UINT32                                                 reserved5108;	//0xC4F452E0
	UINT32                                                 reserved5109;	//0xC4F452E4
	UINT32                                                 reserved5110;	//0xC4F452E8
	UINT32                                                 reserved5111;	//0xC4F452EC
	UINT32                                                 reserved5112;	//0xC4F452F0
	UINT32                                                 reserved5113;	//0xC4F452F4
	UINT32                                                 reserved5114;	//0xC4F452F8
	UINT32                                                 reserved5115;	//0xC4F452FC
	REG_DDRC_M0_DEBUG_UQ_1_T                                 debug_uq_1;	//0xC4F45300
	REG_DDRC_M0_DEBUG_UQ_2_T                                 debug_uq_2;	//0xC4F45304
	UINT32                                                 reserved5116;	//0xC4F45308
	UINT32                                                 reserved5117;	//0xC4F4530C
	UINT32                                                 reserved5118;	//0xC4F45310
	UINT32                                                 reserved5119;	//0xC4F45314
	UINT32                                                 reserved5120;	//0xC4F45318
	UINT32                                                 reserved5121;	//0xC4F4531C
	UINT32                                                 reserved5122;	//0xC4F45320
	UINT32                                                 reserved5123;	//0xC4F45324
	UINT32                                                 reserved5124;	//0xC4F45328
	UINT32                                                 reserved5125;	//0xC4F4532C
	UINT32                                                 reserved5126;	//0xC4F45330
	UINT32                                                 reserved5127;	//0xC4F45334
	UINT32                                                 reserved5128;	//0xC4F45338
	UINT32                                                 reserved5129;	//0xC4F4533C
	UINT32                                                 reserved5130;	//0xC4F45340
	UINT32                                                 reserved5131;	//0xC4F45344
	UINT32                                                 reserved5132;	//0xC4F45348
	UINT32                                                 reserved5133;	//0xC4F4534C
	UINT32                                                 reserved5134;	//0xC4F45350
	UINT32                                                 reserved5135;	//0xC4F45354
	UINT32                                                 reserved5136;	//0xC4F45358
	UINT32                                                 reserved5137;	//0xC4F4535C
	UINT32                                                 reserved5138;	//0xC4F45360
	UINT32                                                 reserved5139;	//0xC4F45364
	UINT32                                                 reserved5140;	//0xC4F45368
	UINT32                                                 reserved5141;	//0xC4F4536C
	UINT32                                                 reserved5142;	//0xC4F45370
	UINT32                                                 reserved5143;	//0xC4F45374
	UINT32                                                 reserved5144;	//0xC4F45378
	UINT32                                                 reserved5145;	//0xC4F4537C
	UINT32                                                 reserved5146;	//0xC4F45380
	UINT32                                                 reserved5147;	//0xC4F45384
	UINT32                                                 reserved5148;	//0xC4F45388
	UINT32                                                 reserved5149;	//0xC4F4538C
	UINT32                                                 reserved5150;	//0xC4F45390
	UINT32                                                 reserved5151;	//0xC4F45394
	UINT32                                                 reserved5152;	//0xC4F45398
	UINT32                                                 reserved5153;	//0xC4F4539C
	UINT32                                                 reserved5154;	//0xC4F453A0
	UINT32                                                 reserved5155;	//0xC4F453A4
	UINT32                                                 reserved5156;	//0xC4F453A8
	UINT32                                                 reserved5157;	//0xC4F453AC
	UINT32                                                 reserved5158;	//0xC4F453B0
	UINT32                                                 reserved5159;	//0xC4F453B4
	UINT32                                                 reserved5160;	//0xC4F453B8
	UINT32                                                 reserved5161;	//0xC4F453BC
	UINT32                                                 reserved5162;	//0xC4F453C0
	UINT32                                                 reserved5163;	//0xC4F453C4
	UINT32                                                 reserved5164;	//0xC4F453C8
	UINT32                                                 reserved5165;	//0xC4F453CC
	UINT32                                                 reserved5166;	//0xC4F453D0
	UINT32                                                 reserved5167;	//0xC4F453D4
	UINT32                                                 reserved5168;	//0xC4F453D8
	UINT32                                                 reserved5169;	//0xC4F453DC
	UINT32                                                 reserved5170;	//0xC4F453E0
	UINT32                                                 reserved5171;	//0xC4F453E4
	UINT32                                                 reserved5172;	//0xC4F453E8
	UINT32                                                 reserved5173;	//0xC4F453EC
	UINT32                                                 reserved5174;	//0xC4F453F0
	UINT32                                                 reserved5175;	//0xC4F453F4
	UINT32                                                 reserved5176;	//0xC4F453F8
	UINT32                                                 reserved5177;	//0xC4F453FC
	REG_DDRC_M0_DEBUG_SCH0_T                                 debug_sch0;	//0xC4F45400
	REG_DDRC_M0_DEBUG_SCH1_T                                 debug_sch1;	//0xC4F45404
	UINT32                                                 reserved5178;	//0xC4F45408
	UINT32                                                 reserved5179;	//0xC4F4540C
	UINT32                                                 reserved5180;	//0xC4F45410
	UINT32                                                 reserved5181;	//0xC4F45414
	UINT32                                                 reserved5182;	//0xC4F45418
	UINT32                                                 reserved5183;	//0xC4F4541C
	UINT32                                                 reserved5184;	//0xC4F45420
	UINT32                                                 reserved5185;	//0xC4F45424
	UINT32                                                 reserved5186;	//0xC4F45428
	UINT32                                                 reserved5187;	//0xC4F4542C
	UINT32                                                 reserved5188;	//0xC4F45430
	UINT32                                                 reserved5189;	//0xC4F45434
	UINT32                                                 reserved5190;	//0xC4F45438
	UINT32                                                 reserved5191;	//0xC4F4543C
	UINT32                                                 reserved5192;	//0xC4F45440
	UINT32                                                 reserved5193;	//0xC4F45444
	UINT32                                                 reserved5194;	//0xC4F45448
	UINT32                                                 reserved5195;	//0xC4F4544C
	UINT32                                                 reserved5196;	//0xC4F45450
	UINT32                                                 reserved5197;	//0xC4F45454
	UINT32                                                 reserved5198;	//0xC4F45458
	UINT32                                                 reserved5199;	//0xC4F4545C
	UINT32                                                 reserved5200;	//0xC4F45460
	UINT32                                                 reserved5201;	//0xC4F45464
	UINT32                                                 reserved5202;	//0xC4F45468
	UINT32                                                 reserved5203;	//0xC4F4546C
	UINT32                                                 reserved5204;	//0xC4F45470
	UINT32                                                 reserved5205;	//0xC4F45474
	UINT32                                                 reserved5206;	//0xC4F45478
	UINT32                                                 reserved5207;	//0xC4F4547C
	UINT32                                                 reserved5208;	//0xC4F45480
	UINT32                                                 reserved5209;	//0xC4F45484
	UINT32                                                 reserved5210;	//0xC4F45488
	UINT32                                                 reserved5211;	//0xC4F4548C
	UINT32                                                 reserved5212;	//0xC4F45490
	UINT32                                                 reserved5213;	//0xC4F45494
	UINT32                                                 reserved5214;	//0xC4F45498
	UINT32                                                 reserved5215;	//0xC4F4549C
	UINT32                                                 reserved5216;	//0xC4F454A0
	UINT32                                                 reserved5217;	//0xC4F454A4
	UINT32                                                 reserved5218;	//0xC4F454A8
	UINT32                                                 reserved5219;	//0xC4F454AC
	UINT32                                                 reserved5220;	//0xC4F454B0
	UINT32                                                 reserved5221;	//0xC4F454B4
	UINT32                                                 reserved5222;	//0xC4F454B8
	UINT32                                                 reserved5223;	//0xC4F454BC
	UINT32                                                 reserved5224;	//0xC4F454C0
	UINT32                                                 reserved5225;	//0xC4F454C4
	UINT32                                                 reserved5226;	//0xC4F454C8
	UINT32                                                 reserved5227;	//0xC4F454CC
	UINT32                                                 reserved5228;	//0xC4F454D0
	UINT32                                                 reserved5229;	//0xC4F454D4
	UINT32                                                 reserved5230;	//0xC4F454D8
	UINT32                                                 reserved5231;	//0xC4F454DC
	UINT32                                                 reserved5232;	//0xC4F454E0
	UINT32                                                 reserved5233;	//0xC4F454E4
	UINT32                                                 reserved5234;	//0xC4F454E8
	UINT32                                                 reserved5235;	//0xC4F454EC
	UINT32                                                 reserved5236;	//0xC4F454F0
	UINT32                                                 reserved5237;	//0xC4F454F4
	UINT32                                                 reserved5238;	//0xC4F454F8
	UINT32                                                 reserved5239;	//0xC4F454FC
	REG_DDRC_M0_DEBUG_ALP_T                                   debug_alp;	//0xC4F45500
	REG_DDRC_M0_DEBUG_ALP_ENTRY_NUM_T               debug_alp_entry_num;	//0xC4F45504
	REG_DDRC_M0_DEBUG_ALP_TIME_T                         debug_alp_time;	//0xC4F45508
	REG_DDRC_M0_DEBUG_ALP_WAIT_CNT_T                 debug_alp_wait_cnt;	//0xC4F4550C
	UINT32                                                 reserved5240;	//0xC4F45510
	UINT32                                                 reserved5241;	//0xC4F45514
	UINT32                                                 reserved5242;	//0xC4F45518
	UINT32                                                 reserved5243;	//0xC4F4551C
	UINT32                                                 reserved5244;	//0xC4F45520
	UINT32                                                 reserved5245;	//0xC4F45524
	UINT32                                                 reserved5246;	//0xC4F45528
	UINT32                                                 reserved5247;	//0xC4F4552C
	UINT32                                                 reserved5248;	//0xC4F45530
	UINT32                                                 reserved5249;	//0xC4F45534
	UINT32                                                 reserved5250;	//0xC4F45538
	UINT32                                                 reserved5251;	//0xC4F4553C
	UINT32                                                 reserved5252;	//0xC4F45540
	UINT32                                                 reserved5253;	//0xC4F45544
	UINT32                                                 reserved5254;	//0xC4F45548
	UINT32                                                 reserved5255;	//0xC4F4554C
	UINT32                                                 reserved5256;	//0xC4F45550
	UINT32                                                 reserved5257;	//0xC4F45554
	UINT32                                                 reserved5258;	//0xC4F45558
	UINT32                                                 reserved5259;	//0xC4F4555C
	UINT32                                                 reserved5260;	//0xC4F45560
	UINT32                                                 reserved5261;	//0xC4F45564
	UINT32                                                 reserved5262;	//0xC4F45568
	UINT32                                                 reserved5263;	//0xC4F4556C
	UINT32                                                 reserved5264;	//0xC4F45570
	UINT32                                                 reserved5265;	//0xC4F45574
	UINT32                                                 reserved5266;	//0xC4F45578
	UINT32                                                 reserved5267;	//0xC4F4557C
	UINT32                                                 reserved5268;	//0xC4F45580
	UINT32                                                 reserved5269;	//0xC4F45584
	UINT32                                                 reserved5270;	//0xC4F45588
	UINT32                                                 reserved5271;	//0xC4F4558C
	UINT32                                                 reserved5272;	//0xC4F45590
	UINT32                                                 reserved5273;	//0xC4F45594
	UINT32                                                 reserved5274;	//0xC4F45598
	UINT32                                                 reserved5275;	//0xC4F4559C
	UINT32                                                 reserved5276;	//0xC4F455A0
	UINT32                                                 reserved5277;	//0xC4F455A4
	UINT32                                                 reserved5278;	//0xC4F455A8
	UINT32                                                 reserved5279;	//0xC4F455AC
	UINT32                                                 reserved5280;	//0xC4F455B0
	UINT32                                                 reserved5281;	//0xC4F455B4
	UINT32                                                 reserved5282;	//0xC4F455B8
	UINT32                                                 reserved5283;	//0xC4F455BC
	UINT32                                                 reserved5284;	//0xC4F455C0
	UINT32                                                 reserved5285;	//0xC4F455C4
	UINT32                                                 reserved5286;	//0xC4F455C8
	UINT32                                                 reserved5287;	//0xC4F455CC
	UINT32                                                 reserved5288;	//0xC4F455D0
	UINT32                                                 reserved5289;	//0xC4F455D4
	UINT32                                                 reserved5290;	//0xC4F455D8
	UINT32                                                 reserved5291;	//0xC4F455DC
	UINT32                                                 reserved5292;	//0xC4F455E0
	UINT32                                                 reserved5293;	//0xC4F455E4
	UINT32                                                 reserved5294;	//0xC4F455E8
	UINT32                                                 reserved5295;	//0xC4F455EC
	UINT32                                                 reserved5296;	//0xC4F455F0
	UINT32                                                 reserved5297;	//0xC4F455F4
	UINT32                                                 reserved5298;	//0xC4F455F8
	UINT32                                                 reserved5299;	//0xC4F455FC
	REG_DDRC_M0_DEBUG_DFS_T                                   debug_dfs;	//0xC4F45600
	UINT32                                                 reserved5300;	//0xC4F45604
	UINT32                                                 reserved5301;	//0xC4F45608
	UINT32                                                 reserved5302;	//0xC4F4560C
	UINT32                                                 reserved5303;	//0xC4F45610
	UINT32                                                 reserved5304;	//0xC4F45614
	UINT32                                                 reserved5305;	//0xC4F45618
	UINT32                                                 reserved5306;	//0xC4F4561C
	UINT32                                                 reserved5307;	//0xC4F45620
	UINT32                                                 reserved5308;	//0xC4F45624
	UINT32                                                 reserved5309;	//0xC4F45628
	UINT32                                                 reserved5310;	//0xC4F4562C
	UINT32                                                 reserved5311;	//0xC4F45630
	UINT32                                                 reserved5312;	//0xC4F45634
	UINT32                                                 reserved5313;	//0xC4F45638
	UINT32                                                 reserved5314;	//0xC4F4563C
	UINT32                                                 reserved5315;	//0xC4F45640
	UINT32                                                 reserved5316;	//0xC4F45644
	UINT32                                                 reserved5317;	//0xC4F45648
	UINT32                                                 reserved5318;	//0xC4F4564C
	UINT32                                                 reserved5319;	//0xC4F45650
	UINT32                                                 reserved5320;	//0xC4F45654
	UINT32                                                 reserved5321;	//0xC4F45658
	UINT32                                                 reserved5322;	//0xC4F4565C
	UINT32                                                 reserved5323;	//0xC4F45660
	UINT32                                                 reserved5324;	//0xC4F45664
	UINT32                                                 reserved5325;	//0xC4F45668
	UINT32                                                 reserved5326;	//0xC4F4566C
	UINT32                                                 reserved5327;	//0xC4F45670
	UINT32                                                 reserved5328;	//0xC4F45674
	UINT32                                                 reserved5329;	//0xC4F45678
	UINT32                                                 reserved5330;	//0xC4F4567C
	UINT32                                                 reserved5331;	//0xC4F45680
	UINT32                                                 reserved5332;	//0xC4F45684
	UINT32                                                 reserved5333;	//0xC4F45688
	UINT32                                                 reserved5334;	//0xC4F4568C
	UINT32                                                 reserved5335;	//0xC4F45690
	UINT32                                                 reserved5336;	//0xC4F45694
	UINT32                                                 reserved5337;	//0xC4F45698
	UINT32                                                 reserved5338;	//0xC4F4569C
	UINT32                                                 reserved5339;	//0xC4F456A0
	UINT32                                                 reserved5340;	//0xC4F456A4
	UINT32                                                 reserved5341;	//0xC4F456A8
	UINT32                                                 reserved5342;	//0xC4F456AC
	UINT32                                                 reserved5343;	//0xC4F456B0
	UINT32                                                 reserved5344;	//0xC4F456B4
	UINT32                                                 reserved5345;	//0xC4F456B8
	UINT32                                                 reserved5346;	//0xC4F456BC
	UINT32                                                 reserved5347;	//0xC4F456C0
	UINT32                                                 reserved5348;	//0xC4F456C4
	UINT32                                                 reserved5349;	//0xC4F456C8
	UINT32                                                 reserved5350;	//0xC4F456CC
	UINT32                                                 reserved5351;	//0xC4F456D0
	UINT32                                                 reserved5352;	//0xC4F456D4
	UINT32                                                 reserved5353;	//0xC4F456D8
	UINT32                                                 reserved5354;	//0xC4F456DC
	UINT32                                                 reserved5355;	//0xC4F456E0
	UINT32                                                 reserved5356;	//0xC4F456E4
	UINT32                                                 reserved5357;	//0xC4F456E8
	UINT32                                                 reserved5358;	//0xC4F456EC
	UINT32                                                 reserved5359;	//0xC4F456F0
	UINT32                                                 reserved5360;	//0xC4F456F4
	UINT32                                                 reserved5361;	//0xC4F456F8
	UINT32                                                 reserved5362;	//0xC4F456FC
	REG_DDRC_M0_DEBUG_IDLE_CNT_T                         debug_idle_cnt;	//0xC4F45700
	REG_DDRC_M0_DEBUG_RD_CNT_T                             debug_rd_cnt;	//0xC4F45704
	REG_DDRC_M0_DEBUG_RDL_CNT_T                           debug_rdl_cnt;	//0xC4F45708
	UINT32                                                 reserved5363;	//0xC4F4570C
	REG_DDRC_M0_DEBUG_RWR_CNT_T                           debug_rwr_cnt;	//0xC4F45710
	REG_DDRC_M0_DEBUG_MWR_CNT_T                           debug_mwr_cnt;	//0xC4F45714
	REG_DDRC_M0_DEBUG_WRL_CNT_T                           debug_wrl_cnt;	//0xC4F45718
	UINT32                                                 reserved5364;	//0xC4F4571C
	REG_DDRC_M0_DEBUG_PRG_CNT_T                           debug_prg_cnt;	//0xC4F45720
	REG_DDRC_M0_DEBUG_REF_CNT_T                           debug_ref_cnt;	//0xC4F45724
	REG_DDRC_M0_DEBUG_ACT_CNT_T                           debug_act_cnt;	//0xC4F45728
	REG_DDRC_M0_DEBUG_RW_SWC_CNT_T                     debug_rw_swc_cnt;	//0xC4F4572C
	REG_DDRC_M0_DEBUG_R_URG_SWC_CNT_T               debug_r_urg_swc_cnt;	//0xC4F45730
	REG_DDRC_M0_DEBUG_R_REQ_ROW_HIT_CNT_T       debug_r_req_row_hit_cnt;	//0xC4F45734
	REG_DDRC_M0_DEBUG_R_REQ_HIT_CNT_T               debug_r_req_hit_cnt;	//0xC4F45738
	REG_DDRC_M0_DEBUG_R_URG_ROW_HIT_CNT_T       debug_r_urg_row_hit_cnt;	//0xC4F4573C
	REG_DDRC_M0_DEBUG_R_URG_HIT_CNT_T               debug_r_urg_hit_cnt;	//0xC4F45740
	REG_DDRC_M0_DEBUG_R_ROW_HIT_CNT_T               debug_r_row_hit_cnt;	//0xC4F45744
	REG_DDRC_M0_DEBUG_R_LUCKY_HIT_CNT_T           debug_r_lucky_hit_cnt;	//0xC4F45748
	UINT32                                                 reserved5365;	//0xC4F4574C
	REG_DDRC_M0_DEBUG_W_URG_SWC_CNT_T               debug_w_urg_swc_cnt;	//0xC4F45750
	REG_DDRC_M0_DEBUG_W_REQ_ROW_HIT_CNT_T       debug_w_req_row_hit_cnt;	//0xC4F45754
	REG_DDRC_M0_DEBUG_W_REQ_HIT_CNT_T               debug_w_req_hit_cnt;	//0xC4F45758
	REG_DDRC_M0_DEBUG_W_URG_ROW_HIT_CNT_T       debug_w_urg_row_hit_cnt;	//0xC4F4575C
	REG_DDRC_M0_DEBUG_W_URG_HIT_CNT_T               debug_w_urg_hit_cnt;	//0xC4F45760
	REG_DDRC_M0_DEBUG_W_ROW_HIT_CNT_T               debug_w_row_hit_cnt;	//0xC4F45764
	REG_DDRC_M0_DEBUG_W_LUCKY_HIT_CNT_T           debug_w_lucky_hit_cnt;	//0xC4F45768
	UINT32                                                 reserved5366;	//0xC4F4576C
	REG_DDRC_M0_DEBUG_MAX_LAT_QOS_T                   debug_max_lat_qos;	//0xC4F45770
	UINT32                                                 reserved5367;	//0xC4F45774
	UINT32                                                 reserved5368;	//0xC4F45778
	UINT32                                                 reserved5369;	//0xC4F4577C
	UINT32                                                 reserved5370;	//0xC4F45780
	UINT32                                                 reserved5371;	//0xC4F45784
	UINT32                                                 reserved5372;	//0xC4F45788
	UINT32                                                 reserved5373;	//0xC4F4578C
	UINT32                                                 reserved5374;	//0xC4F45790
	UINT32                                                 reserved5375;	//0xC4F45794
	UINT32                                                 reserved5376;	//0xC4F45798
	UINT32                                                 reserved5377;	//0xC4F4579C
	UINT32                                                 reserved5378;	//0xC4F457A0
	UINT32                                                 reserved5379;	//0xC4F457A4
	UINT32                                                 reserved5380;	//0xC4F457A8
	UINT32                                                 reserved5381;	//0xC4F457AC
	UINT32                                                 reserved5382;	//0xC4F457B0
	UINT32                                                 reserved5383;	//0xC4F457B4
	UINT32                                                 reserved5384;	//0xC4F457B8
	UINT32                                                 reserved5385;	//0xC4F457BC
	UINT32                                                 reserved5386;	//0xC4F457C0
	UINT32                                                 reserved5387;	//0xC4F457C4
	UINT32                                                 reserved5388;	//0xC4F457C8
	UINT32                                                 reserved5389;	//0xC4F457CC
	UINT32                                                 reserved5390;	//0xC4F457D0
	UINT32                                                 reserved5391;	//0xC4F457D4
	UINT32                                                 reserved5392;	//0xC4F457D8
	UINT32                                                 reserved5393;	//0xC4F457DC
	UINT32                                                 reserved5394;	//0xC4F457E0
	UINT32                                                 reserved5395;	//0xC4F457E4
	UINT32                                                 reserved5396;	//0xC4F457E8
	UINT32                                                 reserved5397;	//0xC4F457EC
	UINT32                                                 reserved5398;	//0xC4F457F0
	UINT32                                                 reserved5399;	//0xC4F457F4
	UINT32                                                 reserved5400;	//0xC4F457F8
	UINT32                                                 reserved5401;	//0xC4F457FC
	REG_DDRC_M0_DEBUG_R_HYB_SWC_CNT_T               debug_r_hyb_swc_cnt;	//0xC4F45800
	REG_DDRC_M0_DEBUG_W_HYB_SWC_CNT_T               debug_w_hyb_swc_cnt;	//0xC4F45804
	UINT32                                                 reserved5402;	//0xC4F45808
	UINT32                                                 reserved5403;	//0xC4F4580C
	UINT32                                                 reserved5404;	//0xC4F45810
	UINT32                                                 reserved5405;	//0xC4F45814
	UINT32                                                 reserved5406;	//0xC4F45818
	UINT32                                                 reserved5407;	//0xC4F4581C
	UINT32                                                 reserved5408;	//0xC4F45820
	UINT32                                                 reserved5409;	//0xC4F45824
	UINT32                                                 reserved5410;	//0xC4F45828
	UINT32                                                 reserved5411;	//0xC4F4582C
	UINT32                                                 reserved5412;	//0xC4F45830
	UINT32                                                 reserved5413;	//0xC4F45834
	UINT32                                                 reserved5414;	//0xC4F45838
	UINT32                                                 reserved5415;	//0xC4F4583C
	UINT32                                                 reserved5416;	//0xC4F45840
	UINT32                                                 reserved5417;	//0xC4F45844
	UINT32                                                 reserved5418;	//0xC4F45848
	UINT32                                                 reserved5419;	//0xC4F4584C
	UINT32                                                 reserved5420;	//0xC4F45850
	UINT32                                                 reserved5421;	//0xC4F45854
	UINT32                                                 reserved5422;	//0xC4F45858
	UINT32                                                 reserved5423;	//0xC4F4585C
	UINT32                                                 reserved5424;	//0xC4F45860
	UINT32                                                 reserved5425;	//0xC4F45864
	UINT32                                                 reserved5426;	//0xC4F45868
	UINT32                                                 reserved5427;	//0xC4F4586C
	UINT32                                                 reserved5428;	//0xC4F45870
	UINT32                                                 reserved5429;	//0xC4F45874
	UINT32                                                 reserved5430;	//0xC4F45878
	UINT32                                                 reserved5431;	//0xC4F4587C
	UINT32                                                 reserved5432;	//0xC4F45880
	UINT32                                                 reserved5433;	//0xC4F45884
	UINT32                                                 reserved5434;	//0xC4F45888
	UINT32                                                 reserved5435;	//0xC4F4588C
	UINT32                                                 reserved5436;	//0xC4F45890
	UINT32                                                 reserved5437;	//0xC4F45894
	UINT32                                                 reserved5438;	//0xC4F45898
	UINT32                                                 reserved5439;	//0xC4F4589C
	UINT32                                                 reserved5440;	//0xC4F458A0
	UINT32                                                 reserved5441;	//0xC4F458A4
	UINT32                                                 reserved5442;	//0xC4F458A8
	UINT32                                                 reserved5443;	//0xC4F458AC
	UINT32                                                 reserved5444;	//0xC4F458B0
	UINT32                                                 reserved5445;	//0xC4F458B4
	UINT32                                                 reserved5446;	//0xC4F458B8
	UINT32                                                 reserved5447;	//0xC4F458BC
	UINT32                                                 reserved5448;	//0xC4F458C0
	UINT32                                                 reserved5449;	//0xC4F458C4
	UINT32                                                 reserved5450;	//0xC4F458C8
	UINT32                                                 reserved5451;	//0xC4F458CC
	UINT32                                                 reserved5452;	//0xC4F458D0
	UINT32                                                 reserved5453;	//0xC4F458D4
	UINT32                                                 reserved5454;	//0xC4F458D8
	UINT32                                                 reserved5455;	//0xC4F458DC
	UINT32                                                 reserved5456;	//0xC4F458E0
	UINT32                                                 reserved5457;	//0xC4F458E4
	UINT32                                                 reserved5458;	//0xC4F458E8
	UINT32                                                 reserved5459;	//0xC4F458EC
	UINT32                                                 reserved5460;	//0xC4F458F0
	UINT32                                                 reserved5461;	//0xC4F458F4
	UINT32                                                 reserved5462;	//0xC4F458F8
	UINT32                                                 reserved5463;	//0xC4F458FC
	REG_DDRC_M0_DEBUG_R_FIFO_0_PRT_CNT_T         debug_r_fifo_0_prt_cnt;	//0xC4F45900
	REG_DDRC_M0_DEBUG_R_FIFO_1_PRT_CNT_T         debug_r_fifo_1_prt_cnt;	//0xC4F45904
	REG_DDRC_M0_DEBUG_R_FIFO_2_PRT_CNT_T         debug_r_fifo_2_prt_cnt;	//0xC4F45908
	REG_DDRC_M0_DEBUG_R_FIFO_3_PRT_CNT_T         debug_r_fifo_3_prt_cnt;	//0xC4F4590C
	REG_DDRC_M0_DEBUG_W_FIFO_0_PRT_CNT_T         debug_w_fifo_0_prt_cnt;	//0xC4F45910
	REG_DDRC_M0_DEBUG_W_FIFO_1_PRT_CNT_T         debug_w_fifo_1_prt_cnt;	//0xC4F45914
	REG_DDRC_M0_DEBUG_W_FIFO_2_PRT_CNT_T         debug_w_fifo_2_prt_cnt;	//0xC4F45918
	REG_DDRC_M0_DEBUG_W_FIFO_3_PRT_CNT_T         debug_w_fifo_3_prt_cnt;	//0xC4F4591C
	UINT32                                                 reserved5464;	//0xC4F45920
	UINT32                                                 reserved5465;	//0xC4F45924
	UINT32                                                 reserved5466;	//0xC4F45928
	UINT32                                                 reserved5467;	//0xC4F4592C
	UINT32                                                 reserved5468;	//0xC4F45930
	UINT32                                                 reserved5469;	//0xC4F45934
	UINT32                                                 reserved5470;	//0xC4F45938
	UINT32                                                 reserved5471;	//0xC4F4593C
	UINT32                                                 reserved5472;	//0xC4F45940
	UINT32                                                 reserved5473;	//0xC4F45944
	UINT32                                                 reserved5474;	//0xC4F45948
	UINT32                                                 reserved5475;	//0xC4F4594C
	UINT32                                                 reserved5476;	//0xC4F45950
	UINT32                                                 reserved5477;	//0xC4F45954
	UINT32                                                 reserved5478;	//0xC4F45958
	UINT32                                                 reserved5479;	//0xC4F4595C
	UINT32                                                 reserved5480;	//0xC4F45960
	UINT32                                                 reserved5481;	//0xC4F45964
	UINT32                                                 reserved5482;	//0xC4F45968
	UINT32                                                 reserved5483;	//0xC4F4596C
	UINT32                                                 reserved5484;	//0xC4F45970
	UINT32                                                 reserved5485;	//0xC4F45974
	UINT32                                                 reserved5486;	//0xC4F45978
	UINT32                                                 reserved5487;	//0xC4F4597C
	UINT32                                                 reserved5488;	//0xC4F45980
	UINT32                                                 reserved5489;	//0xC4F45984
	UINT32                                                 reserved5490;	//0xC4F45988
	UINT32                                                 reserved5491;	//0xC4F4598C
	UINT32                                                 reserved5492;	//0xC4F45990
	UINT32                                                 reserved5493;	//0xC4F45994
	UINT32                                                 reserved5494;	//0xC4F45998
	UINT32                                                 reserved5495;	//0xC4F4599C
	UINT32                                                 reserved5496;	//0xC4F459A0
	UINT32                                                 reserved5497;	//0xC4F459A4
	UINT32                                                 reserved5498;	//0xC4F459A8
	UINT32                                                 reserved5499;	//0xC4F459AC
	UINT32                                                 reserved5500;	//0xC4F459B0
	UINT32                                                 reserved5501;	//0xC4F459B4
	UINT32                                                 reserved5502;	//0xC4F459B8
	UINT32                                                 reserved5503;	//0xC4F459BC
	UINT32                                                 reserved5504;	//0xC4F459C0
	UINT32                                                 reserved5505;	//0xC4F459C4
	UINT32                                                 reserved5506;	//0xC4F459C8
	UINT32                                                 reserved5507;	//0xC4F459CC
	UINT32                                                 reserved5508;	//0xC4F459D0
	UINT32                                                 reserved5509;	//0xC4F459D4
	UINT32                                                 reserved5510;	//0xC4F459D8
	UINT32                                                 reserved5511;	//0xC4F459DC
	UINT32                                                 reserved5512;	//0xC4F459E0
	UINT32                                                 reserved5513;	//0xC4F459E4
	UINT32                                                 reserved5514;	//0xC4F459E8
	UINT32                                                 reserved5515;	//0xC4F459EC
	UINT32                                                 reserved5516;	//0xC4F459F0
	UINT32                                                 reserved5517;	//0xC4F459F4
	UINT32                                                 reserved5518;	//0xC4F459F8
	UINT32                                                 reserved5519;	//0xC4F459FC
	UINT32                                                 reserved5520;	//0xC4F45A00
	UINT32                                                 reserved5521;	//0xC4F45A04
	UINT32                                                 reserved5522;	//0xC4F45A08
	UINT32                                                 reserved5523;	//0xC4F45A0C
	UINT32                                                 reserved5524;	//0xC4F45A10
	UINT32                                                 reserved5525;	//0xC4F45A14
	UINT32                                                 reserved5526;	//0xC4F45A18
	UINT32                                                 reserved5527;	//0xC4F45A1C
	UINT32                                                 reserved5528;	//0xC4F45A20
	UINT32                                                 reserved5529;	//0xC4F45A24
	UINT32                                                 reserved5530;	//0xC4F45A28
	UINT32                                                 reserved5531;	//0xC4F45A2C
	UINT32                                                 reserved5532;	//0xC4F45A30
	UINT32                                                 reserved5533;	//0xC4F45A34
	UINT32                                                 reserved5534;	//0xC4F45A38
	UINT32                                                 reserved5535;	//0xC4F45A3C
	UINT32                                                 reserved5536;	//0xC4F45A40
	UINT32                                                 reserved5537;	//0xC4F45A44
	UINT32                                                 reserved5538;	//0xC4F45A48
	UINT32                                                 reserved5539;	//0xC4F45A4C
	UINT32                                                 reserved5540;	//0xC4F45A50
	UINT32                                                 reserved5541;	//0xC4F45A54
	UINT32                                                 reserved5542;	//0xC4F45A58
	UINT32                                                 reserved5543;	//0xC4F45A5C
	UINT32                                                 reserved5544;	//0xC4F45A60
	UINT32                                                 reserved5545;	//0xC4F45A64
	UINT32                                                 reserved5546;	//0xC4F45A68
	UINT32                                                 reserved5547;	//0xC4F45A6C
	UINT32                                                 reserved5548;	//0xC4F45A70
	UINT32                                                 reserved5549;	//0xC4F45A74
	UINT32                                                 reserved5550;	//0xC4F45A78
	UINT32                                                 reserved5551;	//0xC4F45A7C
	UINT32                                                 reserved5552;	//0xC4F45A80
	UINT32                                                 reserved5553;	//0xC4F45A84
	UINT32                                                 reserved5554;	//0xC4F45A88
	UINT32                                                 reserved5555;	//0xC4F45A8C
	UINT32                                                 reserved5556;	//0xC4F45A90
	UINT32                                                 reserved5557;	//0xC4F45A94
	UINT32                                                 reserved5558;	//0xC4F45A98
	UINT32                                                 reserved5559;	//0xC4F45A9C
	UINT32                                                 reserved5560;	//0xC4F45AA0
	UINT32                                                 reserved5561;	//0xC4F45AA4
	UINT32                                                 reserved5562;	//0xC4F45AA8
	UINT32                                                 reserved5563;	//0xC4F45AAC
	UINT32                                                 reserved5564;	//0xC4F45AB0
	UINT32                                                 reserved5565;	//0xC4F45AB4
	UINT32                                                 reserved5566;	//0xC4F45AB8
	UINT32                                                 reserved5567;	//0xC4F45ABC
	UINT32                                                 reserved5568;	//0xC4F45AC0
	UINT32                                                 reserved5569;	//0xC4F45AC4
	UINT32                                                 reserved5570;	//0xC4F45AC8
	UINT32                                                 reserved5571;	//0xC4F45ACC
	UINT32                                                 reserved5572;	//0xC4F45AD0
	UINT32                                                 reserved5573;	//0xC4F45AD4
	UINT32                                                 reserved5574;	//0xC4F45AD8
	UINT32                                                 reserved5575;	//0xC4F45ADC
	UINT32                                                 reserved5576;	//0xC4F45AE0
	UINT32                                                 reserved5577;	//0xC4F45AE4
	UINT32                                                 reserved5578;	//0xC4F45AE8
	UINT32                                                 reserved5579;	//0xC4F45AEC
	UINT32                                                 reserved5580;	//0xC4F45AF0
	UINT32                                                 reserved5581;	//0xC4F45AF4
	UINT32                                                 reserved5582;	//0xC4F45AF8
	UINT32                                                 reserved5583;	//0xC4F45AFC
	UINT32                                                 reserved5584;	//0xC4F45B00
	UINT32                                                 reserved5585;	//0xC4F45B04
	UINT32                                                 reserved5586;	//0xC4F45B08
	UINT32                                                 reserved5587;	//0xC4F45B0C
	UINT32                                                 reserved5588;	//0xC4F45B10
	UINT32                                                 reserved5589;	//0xC4F45B14
	UINT32                                                 reserved5590;	//0xC4F45B18
	UINT32                                                 reserved5591;	//0xC4F45B1C
	UINT32                                                 reserved5592;	//0xC4F45B20
	UINT32                                                 reserved5593;	//0xC4F45B24
	UINT32                                                 reserved5594;	//0xC4F45B28
	UINT32                                                 reserved5595;	//0xC4F45B2C
	UINT32                                                 reserved5596;	//0xC4F45B30
	UINT32                                                 reserved5597;	//0xC4F45B34
	UINT32                                                 reserved5598;	//0xC4F45B38
	UINT32                                                 reserved5599;	//0xC4F45B3C
	UINT32                                                 reserved5600;	//0xC4F45B40
	UINT32                                                 reserved5601;	//0xC4F45B44
	UINT32                                                 reserved5602;	//0xC4F45B48
	UINT32                                                 reserved5603;	//0xC4F45B4C
	UINT32                                                 reserved5604;	//0xC4F45B50
	UINT32                                                 reserved5605;	//0xC4F45B54
	UINT32                                                 reserved5606;	//0xC4F45B58
	UINT32                                                 reserved5607;	//0xC4F45B5C
	UINT32                                                 reserved5608;	//0xC4F45B60
	UINT32                                                 reserved5609;	//0xC4F45B64
	UINT32                                                 reserved5610;	//0xC4F45B68
	UINT32                                                 reserved5611;	//0xC4F45B6C
	UINT32                                                 reserved5612;	//0xC4F45B70
	UINT32                                                 reserved5613;	//0xC4F45B74
	UINT32                                                 reserved5614;	//0xC4F45B78
	UINT32                                                 reserved5615;	//0xC4F45B7C
	UINT32                                                 reserved5616;	//0xC4F45B80
	UINT32                                                 reserved5617;	//0xC4F45B84
	UINT32                                                 reserved5618;	//0xC4F45B88
	UINT32                                                 reserved5619;	//0xC4F45B8C
	UINT32                                                 reserved5620;	//0xC4F45B90
	UINT32                                                 reserved5621;	//0xC4F45B94
	UINT32                                                 reserved5622;	//0xC4F45B98
	UINT32                                                 reserved5623;	//0xC4F45B9C
	UINT32                                                 reserved5624;	//0xC4F45BA0
	UINT32                                                 reserved5625;	//0xC4F45BA4
	UINT32                                                 reserved5626;	//0xC4F45BA8
	UINT32                                                 reserved5627;	//0xC4F45BAC
	UINT32                                                 reserved5628;	//0xC4F45BB0
	UINT32                                                 reserved5629;	//0xC4F45BB4
	UINT32                                                 reserved5630;	//0xC4F45BB8
	UINT32                                                 reserved5631;	//0xC4F45BBC
	UINT32                                                 reserved5632;	//0xC4F45BC0
	UINT32                                                 reserved5633;	//0xC4F45BC4
	UINT32                                                 reserved5634;	//0xC4F45BC8
	UINT32                                                 reserved5635;	//0xC4F45BCC
	UINT32                                                 reserved5636;	//0xC4F45BD0
	UINT32                                                 reserved5637;	//0xC4F45BD4
	UINT32                                                 reserved5638;	//0xC4F45BD8
	UINT32                                                 reserved5639;	//0xC4F45BDC
	UINT32                                                 reserved5640;	//0xC4F45BE0
	UINT32                                                 reserved5641;	//0xC4F45BE4
	UINT32                                                 reserved5642;	//0xC4F45BE8
	UINT32                                                 reserved5643;	//0xC4F45BEC
	UINT32                                                 reserved5644;	//0xC4F45BF0
	UINT32                                                 reserved5645;	//0xC4F45BF4
	UINT32                                                 reserved5646;	//0xC4F45BF8
	UINT32                                                 reserved5647;	//0xC4F45BFC
	UINT32                                                 reserved5648;	//0xC4F45C00
	UINT32                                                 reserved5649;	//0xC4F45C04
	UINT32                                                 reserved5650;	//0xC4F45C08
	UINT32                                                 reserved5651;	//0xC4F45C0C
	UINT32                                                 reserved5652;	//0xC4F45C10
	UINT32                                                 reserved5653;	//0xC4F45C14
	UINT32                                                 reserved5654;	//0xC4F45C18
	UINT32                                                 reserved5655;	//0xC4F45C1C
	UINT32                                                 reserved5656;	//0xC4F45C20
	UINT32                                                 reserved5657;	//0xC4F45C24
	UINT32                                                 reserved5658;	//0xC4F45C28
	UINT32                                                 reserved5659;	//0xC4F45C2C
	UINT32                                                 reserved5660;	//0xC4F45C30
	UINT32                                                 reserved5661;	//0xC4F45C34
	UINT32                                                 reserved5662;	//0xC4F45C38
	UINT32                                                 reserved5663;	//0xC4F45C3C
	UINT32                                                 reserved5664;	//0xC4F45C40
	UINT32                                                 reserved5665;	//0xC4F45C44
	UINT32                                                 reserved5666;	//0xC4F45C48
	UINT32                                                 reserved5667;	//0xC4F45C4C
	UINT32                                                 reserved5668;	//0xC4F45C50
	UINT32                                                 reserved5669;	//0xC4F45C54
	UINT32                                                 reserved5670;	//0xC4F45C58
	UINT32                                                 reserved5671;	//0xC4F45C5C
	UINT32                                                 reserved5672;	//0xC4F45C60
	UINT32                                                 reserved5673;	//0xC4F45C64
	UINT32                                                 reserved5674;	//0xC4F45C68
	UINT32                                                 reserved5675;	//0xC4F45C6C
	UINT32                                                 reserved5676;	//0xC4F45C70
	UINT32                                                 reserved5677;	//0xC4F45C74
	UINT32                                                 reserved5678;	//0xC4F45C78
	UINT32                                                 reserved5679;	//0xC4F45C7C
	UINT32                                                 reserved5680;	//0xC4F45C80
	UINT32                                                 reserved5681;	//0xC4F45C84
	UINT32                                                 reserved5682;	//0xC4F45C88
	UINT32                                                 reserved5683;	//0xC4F45C8C
	UINT32                                                 reserved5684;	//0xC4F45C90
	UINT32                                                 reserved5685;	//0xC4F45C94
	UINT32                                                 reserved5686;	//0xC4F45C98
	UINT32                                                 reserved5687;	//0xC4F45C9C
	UINT32                                                 reserved5688;	//0xC4F45CA0
	UINT32                                                 reserved5689;	//0xC4F45CA4
	UINT32                                                 reserved5690;	//0xC4F45CA8
	UINT32                                                 reserved5691;	//0xC4F45CAC
	UINT32                                                 reserved5692;	//0xC4F45CB0
	UINT32                                                 reserved5693;	//0xC4F45CB4
	UINT32                                                 reserved5694;	//0xC4F45CB8
	UINT32                                                 reserved5695;	//0xC4F45CBC
	UINT32                                                 reserved5696;	//0xC4F45CC0
	UINT32                                                 reserved5697;	//0xC4F45CC4
	UINT32                                                 reserved5698;	//0xC4F45CC8
	UINT32                                                 reserved5699;	//0xC4F45CCC
	UINT32                                                 reserved5700;	//0xC4F45CD0
	UINT32                                                 reserved5701;	//0xC4F45CD4
	UINT32                                                 reserved5702;	//0xC4F45CD8
	UINT32                                                 reserved5703;	//0xC4F45CDC
	UINT32                                                 reserved5704;	//0xC4F45CE0
	UINT32                                                 reserved5705;	//0xC4F45CE4
	UINT32                                                 reserved5706;	//0xC4F45CE8
	UINT32                                                 reserved5707;	//0xC4F45CEC
	UINT32                                                 reserved5708;	//0xC4F45CF0
	UINT32                                                 reserved5709;	//0xC4F45CF4
	UINT32                                                 reserved5710;	//0xC4F45CF8
	UINT32                                                 reserved5711;	//0xC4F45CFC
	UINT32                                                 reserved5712;	//0xC4F45D00
	UINT32                                                 reserved5713;	//0xC4F45D04
	UINT32                                                 reserved5714;	//0xC4F45D08
	UINT32                                                 reserved5715;	//0xC4F45D0C
	UINT32                                                 reserved5716;	//0xC4F45D10
	UINT32                                                 reserved5717;	//0xC4F45D14
	UINT32                                                 reserved5718;	//0xC4F45D18
	UINT32                                                 reserved5719;	//0xC4F45D1C
	UINT32                                                 reserved5720;	//0xC4F45D20
	UINT32                                                 reserved5721;	//0xC4F45D24
	UINT32                                                 reserved5722;	//0xC4F45D28
	UINT32                                                 reserved5723;	//0xC4F45D2C
	UINT32                                                 reserved5724;	//0xC4F45D30
	UINT32                                                 reserved5725;	//0xC4F45D34
	UINT32                                                 reserved5726;	//0xC4F45D38
	UINT32                                                 reserved5727;	//0xC4F45D3C
	UINT32                                                 reserved5728;	//0xC4F45D40
	UINT32                                                 reserved5729;	//0xC4F45D44
	UINT32                                                 reserved5730;	//0xC4F45D48
	UINT32                                                 reserved5731;	//0xC4F45D4C
	UINT32                                                 reserved5732;	//0xC4F45D50
	UINT32                                                 reserved5733;	//0xC4F45D54
	UINT32                                                 reserved5734;	//0xC4F45D58
	UINT32                                                 reserved5735;	//0xC4F45D5C
	UINT32                                                 reserved5736;	//0xC4F45D60
	UINT32                                                 reserved5737;	//0xC4F45D64
	UINT32                                                 reserved5738;	//0xC4F45D68
	UINT32                                                 reserved5739;	//0xC4F45D6C
	UINT32                                                 reserved5740;	//0xC4F45D70
	UINT32                                                 reserved5741;	//0xC4F45D74
	UINT32                                                 reserved5742;	//0xC4F45D78
	UINT32                                                 reserved5743;	//0xC4F45D7C
	UINT32                                                 reserved5744;	//0xC4F45D80
	UINT32                                                 reserved5745;	//0xC4F45D84
	UINT32                                                 reserved5746;	//0xC4F45D88
	UINT32                                                 reserved5747;	//0xC4F45D8C
	UINT32                                                 reserved5748;	//0xC4F45D90
	UINT32                                                 reserved5749;	//0xC4F45D94
	UINT32                                                 reserved5750;	//0xC4F45D98
	UINT32                                                 reserved5751;	//0xC4F45D9C
	UINT32                                                 reserved5752;	//0xC4F45DA0
	UINT32                                                 reserved5753;	//0xC4F45DA4
	UINT32                                                 reserved5754;	//0xC4F45DA8
	UINT32                                                 reserved5755;	//0xC4F45DAC
	UINT32                                                 reserved5756;	//0xC4F45DB0
	UINT32                                                 reserved5757;	//0xC4F45DB4
	UINT32                                                 reserved5758;	//0xC4F45DB8
	UINT32                                                 reserved5759;	//0xC4F45DBC
	UINT32                                                 reserved5760;	//0xC4F45DC0
	UINT32                                                 reserved5761;	//0xC4F45DC4
	UINT32                                                 reserved5762;	//0xC4F45DC8
	UINT32                                                 reserved5763;	//0xC4F45DCC
	UINT32                                                 reserved5764;	//0xC4F45DD0
	UINT32                                                 reserved5765;	//0xC4F45DD4
	UINT32                                                 reserved5766;	//0xC4F45DD8
	UINT32                                                 reserved5767;	//0xC4F45DDC
	UINT32                                                 reserved5768;	//0xC4F45DE0
	UINT32                                                 reserved5769;	//0xC4F45DE4
	UINT32                                                 reserved5770;	//0xC4F45DE8
	UINT32                                                 reserved5771;	//0xC4F45DEC
	UINT32                                                 reserved5772;	//0xC4F45DF0
	UINT32                                                 reserved5773;	//0xC4F45DF4
	UINT32                                                 reserved5774;	//0xC4F45DF8
	UINT32                                                 reserved5775;	//0xC4F45DFC
	UINT32                                                 reserved5776;	//0xC4F45E00
	UINT32                                                 reserved5777;	//0xC4F45E04
	UINT32                                                 reserved5778;	//0xC4F45E08
	UINT32                                                 reserved5779;	//0xC4F45E0C
	UINT32                                                 reserved5780;	//0xC4F45E10
	UINT32                                                 reserved5781;	//0xC4F45E14
	UINT32                                                 reserved5782;	//0xC4F45E18
	UINT32                                                 reserved5783;	//0xC4F45E1C
	UINT32                                                 reserved5784;	//0xC4F45E20
	UINT32                                                 reserved5785;	//0xC4F45E24
	UINT32                                                 reserved5786;	//0xC4F45E28
	UINT32                                                 reserved5787;	//0xC4F45E2C
	UINT32                                                 reserved5788;	//0xC4F45E30
	UINT32                                                 reserved5789;	//0xC4F45E34
	UINT32                                                 reserved5790;	//0xC4F45E38
	UINT32                                                 reserved5791;	//0xC4F45E3C
	UINT32                                                 reserved5792;	//0xC4F45E40
	UINT32                                                 reserved5793;	//0xC4F45E44
	UINT32                                                 reserved5794;	//0xC4F45E48
	UINT32                                                 reserved5795;	//0xC4F45E4C
	UINT32                                                 reserved5796;	//0xC4F45E50
	UINT32                                                 reserved5797;	//0xC4F45E54
	UINT32                                                 reserved5798;	//0xC4F45E58
	UINT32                                                 reserved5799;	//0xC4F45E5C
	UINT32                                                 reserved5800;	//0xC4F45E60
	UINT32                                                 reserved5801;	//0xC4F45E64
	UINT32                                                 reserved5802;	//0xC4F45E68
	UINT32                                                 reserved5803;	//0xC4F45E6C
	UINT32                                                 reserved5804;	//0xC4F45E70
	UINT32                                                 reserved5805;	//0xC4F45E74
	UINT32                                                 reserved5806;	//0xC4F45E78
	UINT32                                                 reserved5807;	//0xC4F45E7C
	UINT32                                                 reserved5808;	//0xC4F45E80
	UINT32                                                 reserved5809;	//0xC4F45E84
	UINT32                                                 reserved5810;	//0xC4F45E88
	UINT32                                                 reserved5811;	//0xC4F45E8C
	UINT32                                                 reserved5812;	//0xC4F45E90
	UINT32                                                 reserved5813;	//0xC4F45E94
	UINT32                                                 reserved5814;	//0xC4F45E98
	UINT32                                                 reserved5815;	//0xC4F45E9C
	UINT32                                                 reserved5816;	//0xC4F45EA0
	UINT32                                                 reserved5817;	//0xC4F45EA4
	UINT32                                                 reserved5818;	//0xC4F45EA8
	UINT32                                                 reserved5819;	//0xC4F45EAC
	UINT32                                                 reserved5820;	//0xC4F45EB0
	UINT32                                                 reserved5821;	//0xC4F45EB4
	UINT32                                                 reserved5822;	//0xC4F45EB8
	UINT32                                                 reserved5823;	//0xC4F45EBC
	UINT32                                                 reserved5824;	//0xC4F45EC0
	UINT32                                                 reserved5825;	//0xC4F45EC4
	UINT32                                                 reserved5826;	//0xC4F45EC8
	UINT32                                                 reserved5827;	//0xC4F45ECC
	UINT32                                                 reserved5828;	//0xC4F45ED0
	UINT32                                                 reserved5829;	//0xC4F45ED4
	UINT32                                                 reserved5830;	//0xC4F45ED8
	UINT32                                                 reserved5831;	//0xC4F45EDC
	UINT32                                                 reserved5832;	//0xC4F45EE0
	UINT32                                                 reserved5833;	//0xC4F45EE4
	UINT32                                                 reserved5834;	//0xC4F45EE8
	UINT32                                                 reserved5835;	//0xC4F45EEC
	UINT32                                                 reserved5836;	//0xC4F45EF0
	UINT32                                                 reserved5837;	//0xC4F45EF4
	UINT32                                                 reserved5838;	//0xC4F45EF8
	UINT32                                                 reserved5839;	//0xC4F45EFC
	UINT32                                                 reserved5840;	//0xC4F45F00
	UINT32                                                 reserved5841;	//0xC4F45F04
	UINT32                                                 reserved5842;	//0xC4F45F08
	UINT32                                                 reserved5843;	//0xC4F45F0C
	UINT32                                                 reserved5844;	//0xC4F45F10
	UINT32                                                 reserved5845;	//0xC4F45F14
	UINT32                                                 reserved5846;	//0xC4F45F18
	UINT32                                                 reserved5847;	//0xC4F45F1C
	UINT32                                                 reserved5848;	//0xC4F45F20
	UINT32                                                 reserved5849;	//0xC4F45F24
	UINT32                                                 reserved5850;	//0xC4F45F28
	UINT32                                                 reserved5851;	//0xC4F45F2C
	UINT32                                                 reserved5852;	//0xC4F45F30
	UINT32                                                 reserved5853;	//0xC4F45F34
	UINT32                                                 reserved5854;	//0xC4F45F38
	UINT32                                                 reserved5855;	//0xC4F45F3C
	UINT32                                                 reserved5856;	//0xC4F45F40
	UINT32                                                 reserved5857;	//0xC4F45F44
	UINT32                                                 reserved5858;	//0xC4F45F48
	UINT32                                                 reserved5859;	//0xC4F45F4C
	UINT32                                                 reserved5860;	//0xC4F45F50
	UINT32                                                 reserved5861;	//0xC4F45F54
	UINT32                                                 reserved5862;	//0xC4F45F58
	UINT32                                                 reserved5863;	//0xC4F45F5C
	UINT32                                                 reserved5864;	//0xC4F45F60
	UINT32                                                 reserved5865;	//0xC4F45F64
	UINT32                                                 reserved5866;	//0xC4F45F68
	UINT32                                                 reserved5867;	//0xC4F45F6C
	UINT32                                                 reserved5868;	//0xC4F45F70
	UINT32                                                 reserved5869;	//0xC4F45F74
	UINT32                                                 reserved5870;	//0xC4F45F78
	UINT32                                                 reserved5871;	//0xC4F45F7C
	UINT32                                                 reserved5872;	//0xC4F45F80
	UINT32                                                 reserved5873;	//0xC4F45F84
	UINT32                                                 reserved5874;	//0xC4F45F88
	UINT32                                                 reserved5875;	//0xC4F45F8C
	UINT32                                                 reserved5876;	//0xC4F45F90
	UINT32                                                 reserved5877;	//0xC4F45F94
	UINT32                                                 reserved5878;	//0xC4F45F98
	UINT32                                                 reserved5879;	//0xC4F45F9C
	UINT32                                                 reserved5880;	//0xC4F45FA0
	UINT32                                                 reserved5881;	//0xC4F45FA4
	UINT32                                                 reserved5882;	//0xC4F45FA8
	UINT32                                                 reserved5883;	//0xC4F45FAC
	UINT32                                                 reserved5884;	//0xC4F45FB0
	UINT32                                                 reserved5885;	//0xC4F45FB4
	UINT32                                                 reserved5886;	//0xC4F45FB8
	UINT32                                                 reserved5887;	//0xC4F45FBC
	UINT32                                                 reserved5888;	//0xC4F45FC0
	UINT32                                                 reserved5889;	//0xC4F45FC4
	UINT32                                                 reserved5890;	//0xC4F45FC8
	UINT32                                                 reserved5891;	//0xC4F45FCC
	UINT32                                                 reserved5892;	//0xC4F45FD0
	UINT32                                                 reserved5893;	//0xC4F45FD4
	UINT32                                                 reserved5894;	//0xC4F45FD8
	UINT32                                                 reserved5895;	//0xC4F45FDC
	UINT32                                                 reserved5896;	//0xC4F45FE0
	UINT32                                                 reserved5897;	//0xC4F45FE4
	UINT32                                                 reserved5898;	//0xC4F45FE8
	UINT32                                                 reserved5899;	//0xC4F45FEC
	UINT32                                                 reserved5900;	//0xC4F45FF0
	UINT32                                                 reserved5901;	//0xC4F45FF4
	UINT32                                                 reserved5902;	//0xC4F45FF8
	UINT32                                                 reserved5903;	//0xC4F45FFC
	REG_DDRC_M0_DEBUG_LPD4_0_T                             debug_lpd4_0;	//0xC4F46000
	REG_DDRC_M0_DEBUG_LPD4_1_T                             debug_lpd4_1;	//0xC4F46004
	REG_DDRC_M0_DEBUG_LPD4_2_T                             debug_lpd4_2;	//0xC4F46008
	REG_DDRC_M0_DEBUG_LPD4_3_T                             debug_lpd4_3;	//0xC4F4600C
	REG_DDRC_M0_DEBUG_LPD4_4_T                             debug_lpd4_4;	//0xC4F46010
	REG_DDRC_M0_DEBUG_LPD4_5_T                             debug_lpd4_5;	//0xC4F46014
	REG_DDRC_M0_DEBUG_LPD4_6_T                             debug_lpd4_6;	//0xC4F46018
	REG_DDRC_M0_DEBUG_LPD4_7_T                             debug_lpd4_7;	//0xC4F4601C
	REG_DDRC_M0_DEBUG_LPD4_8_T                             debug_lpd4_8;	//0xC4F46020
	REG_DDRC_M0_DEBUG_LPD4_9_T                             debug_lpd4_9;	//0xC4F46024
	REG_DDRC_M0_DEBUG_LPD4_10_T                           debug_lpd4_10;	//0xC4F46028
	REG_DDRC_M0_DEBUG_LPD4_11_T                           debug_lpd4_11;	//0xC4F4602C
	REG_DDRC_M0_DEBUG_LPD4_12_T                           debug_lpd4_12;	//0xC4F46030
	REG_DDRC_M0_DEBUG_LPD4_13_T                           debug_lpd4_13;	//0xC4F46034
	REG_DDRC_M0_DEBUG_LPD4_14_T                           debug_lpd4_14;	//0xC4F46038
	REG_DDRC_M0_DEBUG_LPD4_15_T                           debug_lpd4_15;	//0xC4F4603C
	REG_DDRC_M0_DEBUG_LPD4_16_T                           debug_lpd4_16;	//0xC4F46040
	UINT32                                                 reserved5904;	//0xC4F46044
	UINT32                                                 reserved5905;	//0xC4F46048
	UINT32                                                 reserved5906;	//0xC4F4604C
	UINT32                                                 reserved5907;	//0xC4F46050
	UINT32                                                 reserved5908;	//0xC4F46054
	UINT32                                                 reserved5909;	//0xC4F46058
	UINT32                                                 reserved5910;	//0xC4F4605C
	UINT32                                                 reserved5911;	//0xC4F46060
	UINT32                                                 reserved5912;	//0xC4F46064
	UINT32                                                 reserved5913;	//0xC4F46068
	UINT32                                                 reserved5914;	//0xC4F4606C
	UINT32                                                 reserved5915;	//0xC4F46070
	UINT32                                                 reserved5916;	//0xC4F46074
	UINT32                                                 reserved5917;	//0xC4F46078
	UINT32                                                 reserved5918;	//0xC4F4607C
	UINT32                                                 reserved5919;	//0xC4F46080
	UINT32                                                 reserved5920;	//0xC4F46084
	UINT32                                                 reserved5921;	//0xC4F46088
	UINT32                                                 reserved5922;	//0xC4F4608C
	UINT32                                                 reserved5923;	//0xC4F46090
	UINT32                                                 reserved5924;	//0xC4F46094
	UINT32                                                 reserved5925;	//0xC4F46098
	UINT32                                                 reserved5926;	//0xC4F4609C
	UINT32                                                 reserved5927;	//0xC4F460A0
	UINT32                                                 reserved5928;	//0xC4F460A4
	UINT32                                                 reserved5929;	//0xC4F460A8
	UINT32                                                 reserved5930;	//0xC4F460AC
	UINT32                                                 reserved5931;	//0xC4F460B0
	UINT32                                                 reserved5932;	//0xC4F460B4
	UINT32                                                 reserved5933;	//0xC4F460B8
	UINT32                                                 reserved5934;	//0xC4F460BC
	UINT32                                                 reserved5935;	//0xC4F460C0
	UINT32                                                 reserved5936;	//0xC4F460C4
	UINT32                                                 reserved5937;	//0xC4F460C8
	UINT32                                                 reserved5938;	//0xC4F460CC
	UINT32                                                 reserved5939;	//0xC4F460D0
	UINT32                                                 reserved5940;	//0xC4F460D4
	UINT32                                                 reserved5941;	//0xC4F460D8
	UINT32                                                 reserved5942;	//0xC4F460DC
	UINT32                                                 reserved5943;	//0xC4F460E0
	UINT32                                                 reserved5944;	//0xC4F460E4
	UINT32                                                 reserved5945;	//0xC4F460E8
	UINT32                                                 reserved5946;	//0xC4F460EC
	UINT32                                                 reserved5947;	//0xC4F460F0
	UINT32                                                 reserved5948;	//0xC4F460F4
	UINT32                                                 reserved5949;	//0xC4F460F8
	UINT32                                                 reserved5950;	//0xC4F460FC
	REG_DDRC_M0_DEBUG_LPD4_MR_0_T                       debug_lpd4_mr_0;	//0xC4F46100
	REG_DDRC_M0_DEBUG_LPD4_MR_1_T                       debug_lpd4_mr_1;	//0xC4F46104
	REG_DDRC_M0_DEBUG_LPD4_MR_2_T                       debug_lpd4_mr_2;	//0xC4F46108
	REG_DDRC_M0_DEBUG_LPD4_MR_3_T                       debug_lpd4_mr_3;	//0xC4F4610C
	REG_DDRC_M0_DEBUG_LPD4_MR_4_T                       debug_lpd4_mr_4;	//0xC4F46110
	REG_DDRC_M0_DEBUG_LPD4_MR_5_T                       debug_lpd4_mr_5;	//0xC4F46114
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_0_T           debug_lpd4_mpc_fifo_0;	//0xC4F46118
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_1_T           debug_lpd4_mpc_fifo_1;	//0xC4F4611C
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_2_T           debug_lpd4_mpc_fifo_2;	//0xC4F46120
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_3_T           debug_lpd4_mpc_fifo_3;	//0xC4F46124
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_4_T           debug_lpd4_mpc_fifo_4;	//0xC4F46128
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_5_T           debug_lpd4_mpc_fifo_5;	//0xC4F4612C
	UINT32                                                 reserved5951;	//0xC4F46130
	UINT32                                                 reserved5952;	//0xC4F46134
	UINT32                                                 reserved5953;	//0xC4F46138
	UINT32                                                 reserved5954;	//0xC4F4613C
	UINT32                                                 reserved5955;	//0xC4F46140
	UINT32                                                 reserved5956;	//0xC4F46144
	UINT32                                                 reserved5957;	//0xC4F46148
	UINT32                                                 reserved5958;	//0xC4F4614C
	UINT32                                                 reserved5959;	//0xC4F46150
	UINT32                                                 reserved5960;	//0xC4F46154
	UINT32                                                 reserved5961;	//0xC4F46158
	UINT32                                                 reserved5962;	//0xC4F4615C
	UINT32                                                 reserved5963;	//0xC4F46160
	UINT32                                                 reserved5964;	//0xC4F46164
	UINT32                                                 reserved5965;	//0xC4F46168
	UINT32                                                 reserved5966;	//0xC4F4616C
	UINT32                                                 reserved5967;	//0xC4F46170
	UINT32                                                 reserved5968;	//0xC4F46174
	UINT32                                                 reserved5969;	//0xC4F46178
	UINT32                                                 reserved5970;	//0xC4F4617C
	UINT32                                                 reserved5971;	//0xC4F46180
	UINT32                                                 reserved5972;	//0xC4F46184
	UINT32                                                 reserved5973;	//0xC4F46188
	UINT32                                                 reserved5974;	//0xC4F4618C
	UINT32                                                 reserved5975;	//0xC4F46190
	UINT32                                                 reserved5976;	//0xC4F46194
	UINT32                                                 reserved5977;	//0xC4F46198
	UINT32                                                 reserved5978;	//0xC4F4619C
	UINT32                                                 reserved5979;	//0xC4F461A0
	UINT32                                                 reserved5980;	//0xC4F461A4
	UINT32                                                 reserved5981;	//0xC4F461A8
	UINT32                                                 reserved5982;	//0xC4F461AC
	UINT32                                                 reserved5983;	//0xC4F461B0
	UINT32                                                 reserved5984;	//0xC4F461B4
	UINT32                                                 reserved5985;	//0xC4F461B8
	UINT32                                                 reserved5986;	//0xC4F461BC
	UINT32                                                 reserved5987;	//0xC4F461C0
	UINT32                                                 reserved5988;	//0xC4F461C4
	UINT32                                                 reserved5989;	//0xC4F461C8
	UINT32                                                 reserved5990;	//0xC4F461CC
	UINT32                                                 reserved5991;	//0xC4F461D0
	UINT32                                                 reserved5992;	//0xC4F461D4
	UINT32                                                 reserved5993;	//0xC4F461D8
	UINT32                                                 reserved5994;	//0xC4F461DC
	UINT32                                                 reserved5995;	//0xC4F461E0
	UINT32                                                 reserved5996;	//0xC4F461E4
	UINT32                                                 reserved5997;	//0xC4F461E8
	UINT32                                                 reserved5998;	//0xC4F461EC
	UINT32                                                 reserved5999;	//0xC4F461F0
	UINT32                                                 reserved6000;	//0xC4F461F4
	UINT32                                                 reserved6001;	//0xC4F461F8
	UINT32                                                 reserved6002;	//0xC4F461FC
	REG_DDRC_M0_DEBUG_CTRL_CMD_MRW1_T               debug_ctrl_cmd_mrw1;	//0xC4F46200
	REG_DDRC_M0_DEBUG_CTRL_CMD_MRW0_T               debug_ctrl_cmd_mrw0;	//0xC4F46204
	REG_DDRC_M0_DEBUG_CTRL_CMD_LP_EXIT_T         debug_ctrl_cmd_lp_exit;	//0xC4F46208
	REG_DDRC_M0_DEBUG_CTRL_CMD_LP_ENTRY_T       debug_ctrl_cmd_lp_entry;	//0xC4F4620C
	REG_DDRC_M0_DEBUG_CTRL_CMD_SR_PD_EXIT_T   debug_ctrl_cmd_sr_pd_exit;	//0xC4F46210
	REG_DDRC_M0_DEBUG_CTRL_CMD_SR_PD_ENTRY_T debug_ctrl_cmd_sr_pd_entry;	//0xC4F46214
	REG_DDRC_M0_DEBUG_CTRL_CMD_SR_EXIT_T         debug_ctrl_cmd_sr_exit;	//0xC4F46218
	REG_DDRC_M0_DEBUG_CTRL_CMD_SR_ENTRY_T       debug_ctrl_cmd_sr_entry;	//0xC4F4621C
	REG_DDRC_M0_DEBUG_CTRL_CMD_PD_EXIT_T         debug_ctrl_cmd_pd_exit;	//0xC4F46220
	REG_DDRC_M0_DEBUG_CTRL_CMD_PD_ENTRY_T       debug_ctrl_cmd_pd_entry;	//0xC4F46224
	REG_DDRC_M0_DEBUG_CTRL_CMD_ZQLAT_T             debug_ctrl_cmd_zqlat;	//0xC4F46228
	REG_DDRC_M0_DEBUG_CTRL_CMD_ZQCAL_T             debug_ctrl_cmd_zqcal;	//0xC4F4622C
	REG_DDRC_M0_DEBUG_CTRL_CMD_CKE1_T               debug_ctrl_cmd_cke1;	//0xC4F46230
	REG_DDRC_M0_DEBUG_CTRL_CMD_CKE0_T               debug_ctrl_cmd_cke0;	//0xC4F46234
	REG_DDRC_M0_DEBUG_CTRL_CMD_RSTN1_T             debug_ctrl_cmd_rstn1;	//0xC4F46238
	REG_DDRC_M0_DEBUG_CTRL_CMD_RSTN0_T             debug_ctrl_cmd_rstn0;	//0xC4F4623C
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD0_T                 debug_ctrl_cmd_rd0;	//0xC4F46240
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD1_T                 debug_ctrl_cmd_rd1;	//0xC4F46244
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD2_T                 debug_ctrl_cmd_rd2;	//0xC4F46248
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD3_T                 debug_ctrl_cmd_rd3;	//0xC4F4624C
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD4_T                 debug_ctrl_cmd_rd4;	//0xC4F46250
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD5_T                 debug_ctrl_cmd_rd5;	//0xC4F46254
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD6_T                 debug_ctrl_cmd_rd6;	//0xC4F46258
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD7_T                 debug_ctrl_cmd_rd7;	//0xC4F4625C
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR0_T               debug_ctrl_cmd_mwr0;	//0xC4F46260
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR1_T               debug_ctrl_cmd_mwr1;	//0xC4F46264
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR2_T               debug_ctrl_cmd_mwr2;	//0xC4F46268
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR3_T               debug_ctrl_cmd_mwr3;	//0xC4F4626C
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR4_T               debug_ctrl_cmd_mwr4;	//0xC4F46270
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR5_T               debug_ctrl_cmd_mwr5;	//0xC4F46274
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR6_T               debug_ctrl_cmd_mwr6;	//0xC4F46278
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR7_T               debug_ctrl_cmd_mwr7;	//0xC4F4627C
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR0_T                 debug_ctrl_cmd_wr0;	//0xC4F46280
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR1_T                 debug_ctrl_cmd_wr1;	//0xC4F46284
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR2_T                 debug_ctrl_cmd_wr2;	//0xC4F46288
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR3_T                 debug_ctrl_cmd_wr3;	//0xC4F4628C
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR4_T                 debug_ctrl_cmd_wr4;	//0xC4F46290
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR5_T                 debug_ctrl_cmd_wr5;	//0xC4F46294
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR6_T                 debug_ctrl_cmd_wr6;	//0xC4F46298
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR7_T                 debug_ctrl_cmd_wr7;	//0xC4F4629C
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT0_T               debug_ctrl_cmd_act0;	//0xC4F462A0
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT1_T               debug_ctrl_cmd_act1;	//0xC4F462A4
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT2_T               debug_ctrl_cmd_act2;	//0xC4F462A8
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT3_T               debug_ctrl_cmd_act3;	//0xC4F462AC
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT4_T               debug_ctrl_cmd_act4;	//0xC4F462B0
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT5_T               debug_ctrl_cmd_act5;	//0xC4F462B4
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT6_T               debug_ctrl_cmd_act6;	//0xC4F462B8
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT7_T               debug_ctrl_cmd_act7;	//0xC4F462BC
	UINT32                                                 reserved6003;	//0xC4F462C0
	UINT32                                                 reserved6004;	//0xC4F462C4
	UINT32                                                 reserved6005;	//0xC4F462C8
	UINT32                                                 reserved6006;	//0xC4F462CC
	UINT32                                                 reserved6007;	//0xC4F462D0
	UINT32                                                 reserved6008;	//0xC4F462D4
	UINT32                                                 reserved6009;	//0xC4F462D8
	UINT32                                                 reserved6010;	//0xC4F462DC
	UINT32                                                 reserved6011;	//0xC4F462E0
	UINT32                                                 reserved6012;	//0xC4F462E4
	UINT32                                                 reserved6013;	//0xC4F462E8
	UINT32                                                 reserved6014;	//0xC4F462EC
	UINT32                                                 reserved6015;	//0xC4F462F0
	UINT32                                                 reserved6016;	//0xC4F462F4
	UINT32                                                 reserved6017;	//0xC4F462F8
	UINT32                                                 reserved6018;	//0xC4F462FC
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB0_T         debug_ctrl_cmd_ref_pb0;	//0xC4F46300
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB1_T         debug_ctrl_cmd_ref_pb1;	//0xC4F46304
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB2_T         debug_ctrl_cmd_ref_pb2;	//0xC4F46308
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB3_T         debug_ctrl_cmd_ref_pb3;	//0xC4F4630C
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB4_T         debug_ctrl_cmd_ref_pb4;	//0xC4F46310
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB5_T         debug_ctrl_cmd_ref_pb5;	//0xC4F46314
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB6_T         debug_ctrl_cmd_ref_pb6;	//0xC4F46318
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB7_T         debug_ctrl_cmd_ref_pb7;	//0xC4F4631C
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB0_T         debug_ctrl_cmd_prg_pb0;	//0xC4F46320
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB1_T         debug_ctrl_cmd_prg_pb1;	//0xC4F46324
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB2_T         debug_ctrl_cmd_prg_pb2;	//0xC4F46328
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB3_T         debug_ctrl_cmd_prg_pb3;	//0xC4F4632C
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB4_T         debug_ctrl_cmd_prg_pb4;	//0xC4F46330
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB5_T         debug_ctrl_cmd_prg_pb5;	//0xC4F46334
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB6_T         debug_ctrl_cmd_prg_pb6;	//0xC4F46338
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB7_T         debug_ctrl_cmd_prg_pb7;	//0xC4F4633C
	REG_DDRC_M0_DEBUG_CTRL_CMD_CG_REF_AB_T     debug_ctrl_cmd_cg_ref_ab;	//0xC4F46340
	REG_DDRC_M0_DEBUG_CTRL_CMD_MF_REF_AB_T     debug_ctrl_cmd_mf_ref_ab;	//0xC4F46344
	UINT32                                                 reserved6019;	//0xC4F46348
	UINT32                                                 reserved6020;	//0xC4F4634C
	REG_DDRC_M0_DEBUG_CTRL_CMD_CG_PRG_AB_T     debug_ctrl_cmd_cg_prg_ab;	//0xC4F46350
	REG_DDRC_M0_DEBUG_CTRL_CMD_MF_PRG_AB_T     debug_ctrl_cmd_mf_prg_ab;	//0xC4F46354
	UINT32                                                 reserved6021;	//0xC4F46358
	UINT32                                                 reserved6022;	//0xC4F4635C
	REG_DDRC_M0_DEBUG_CTRL_CMD_CG_BL_T             debug_ctrl_cmd_cg_bl;	//0xC4F46360
	REG_DDRC_M0_DEBUG_CTRL_CMD_CG_AP_T             debug_ctrl_cmd_cg_ap;	//0xC4F46364
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_CYCLE_T     debug_ctrl_cmd_ref_cycle;	//0xC4F46368
	UINT32                                                 reserved6023;	//0xC4F4636C
	UINT32                                                 reserved6024;	//0xC4F46370
	UINT32                                                 reserved6025;	//0xC4F46374
	UINT32                                                 reserved6026;	//0xC4F46378
	UINT32                                                 reserved6027;	//0xC4F4637C
	UINT32                                                 reserved6028;	//0xC4F46380
	UINT32                                                 reserved6029;	//0xC4F46384
	UINT32                                                 reserved6030;	//0xC4F46388
	UINT32                                                 reserved6031;	//0xC4F4638C
	UINT32                                                 reserved6032;	//0xC4F46390
	UINT32                                                 reserved6033;	//0xC4F46394
	UINT32                                                 reserved6034;	//0xC4F46398
	UINT32                                                 reserved6035;	//0xC4F4639C
	UINT32                                                 reserved6036;	//0xC4F463A0
	UINT32                                                 reserved6037;	//0xC4F463A4
	UINT32                                                 reserved6038;	//0xC4F463A8
	UINT32                                                 reserved6039;	//0xC4F463AC
	UINT32                                                 reserved6040;	//0xC4F463B0
	UINT32                                                 reserved6041;	//0xC4F463B4
	UINT32                                                 reserved6042;	//0xC4F463B8
	UINT32                                                 reserved6043;	//0xC4F463BC
	UINT32                                                 reserved6044;	//0xC4F463C0
	UINT32                                                 reserved6045;	//0xC4F463C4
	UINT32                                                 reserved6046;	//0xC4F463C8
	UINT32                                                 reserved6047;	//0xC4F463CC
	UINT32                                                 reserved6048;	//0xC4F463D0
	UINT32                                                 reserved6049;	//0xC4F463D4
	UINT32                                                 reserved6050;	//0xC4F463D8
	UINT32                                                 reserved6051;	//0xC4F463DC
	UINT32                                                 reserved6052;	//0xC4F463E0
	UINT32                                                 reserved6053;	//0xC4F463E4
	UINT32                                                 reserved6054;	//0xC4F463E8
	UINT32                                                 reserved6055;	//0xC4F463EC
	UINT32                                                 reserved6056;	//0xC4F463F0
	UINT32                                                 reserved6057;	//0xC4F463F4
	UINT32                                                 reserved6058;	//0xC4F463F8
	UINT32                                                 reserved6059;	//0xC4F463FC
	UINT32                                                 reserved6060;	//0xC4F46400
	UINT32                                                 reserved6061;	//0xC4F46404
	UINT32                                                 reserved6062;	//0xC4F46408
	UINT32                                                 reserved6063;	//0xC4F4640C
	UINT32                                                 reserved6064;	//0xC4F46410
	UINT32                                                 reserved6065;	//0xC4F46414
	UINT32                                                 reserved6066;	//0xC4F46418
	UINT32                                                 reserved6067;	//0xC4F4641C
	UINT32                                                 reserved6068;	//0xC4F46420
	UINT32                                                 reserved6069;	//0xC4F46424
	UINT32                                                 reserved6070;	//0xC4F46428
	UINT32                                                 reserved6071;	//0xC4F4642C
	UINT32                                                 reserved6072;	//0xC4F46430
	UINT32                                                 reserved6073;	//0xC4F46434
	UINT32                                                 reserved6074;	//0xC4F46438
	UINT32                                                 reserved6075;	//0xC4F4643C
	UINT32                                                 reserved6076;	//0xC4F46440
	UINT32                                                 reserved6077;	//0xC4F46444
	UINT32                                                 reserved6078;	//0xC4F46448
	UINT32                                                 reserved6079;	//0xC4F4644C
	UINT32                                                 reserved6080;	//0xC4F46450
	UINT32                                                 reserved6081;	//0xC4F46454
	UINT32                                                 reserved6082;	//0xC4F46458
	UINT32                                                 reserved6083;	//0xC4F4645C
	UINT32                                                 reserved6084;	//0xC4F46460
	UINT32                                                 reserved6085;	//0xC4F46464
	UINT32                                                 reserved6086;	//0xC4F46468
	UINT32                                                 reserved6087;	//0xC4F4646C
	UINT32                                                 reserved6088;	//0xC4F46470
	UINT32                                                 reserved6089;	//0xC4F46474
	UINT32                                                 reserved6090;	//0xC4F46478
	UINT32                                                 reserved6091;	//0xC4F4647C
	UINT32                                                 reserved6092;	//0xC4F46480
	UINT32                                                 reserved6093;	//0xC4F46484
	UINT32                                                 reserved6094;	//0xC4F46488
	UINT32                                                 reserved6095;	//0xC4F4648C
	UINT32                                                 reserved6096;	//0xC4F46490
	UINT32                                                 reserved6097;	//0xC4F46494
	UINT32                                                 reserved6098;	//0xC4F46498
	UINT32                                                 reserved6099;	//0xC4F4649C
	UINT32                                                 reserved6100;	//0xC4F464A0
	UINT32                                                 reserved6101;	//0xC4F464A4
	UINT32                                                 reserved6102;	//0xC4F464A8
	UINT32                                                 reserved6103;	//0xC4F464AC
	UINT32                                                 reserved6104;	//0xC4F464B0
	UINT32                                                 reserved6105;	//0xC4F464B4
	UINT32                                                 reserved6106;	//0xC4F464B8
	UINT32                                                 reserved6107;	//0xC4F464BC
	UINT32                                                 reserved6108;	//0xC4F464C0
	UINT32                                                 reserved6109;	//0xC4F464C4
	UINT32                                                 reserved6110;	//0xC4F464C8
	UINT32                                                 reserved6111;	//0xC4F464CC
	UINT32                                                 reserved6112;	//0xC4F464D0
	UINT32                                                 reserved6113;	//0xC4F464D4
	UINT32                                                 reserved6114;	//0xC4F464D8
	UINT32                                                 reserved6115;	//0xC4F464DC
	UINT32                                                 reserved6116;	//0xC4F464E0
	UINT32                                                 reserved6117;	//0xC4F464E4
	UINT32                                                 reserved6118;	//0xC4F464E8
	UINT32                                                 reserved6119;	//0xC4F464EC
	UINT32                                                 reserved6120;	//0xC4F464F0
	UINT32                                                 reserved6121;	//0xC4F464F4
	UINT32                                                 reserved6122;	//0xC4F464F8
	UINT32                                                 reserved6123;	//0xC4F464FC
	UINT32                                                 reserved6124;	//0xC4F46500
	UINT32                                                 reserved6125;	//0xC4F46504
	UINT32                                                 reserved6126;	//0xC4F46508
	UINT32                                                 reserved6127;	//0xC4F4650C
	UINT32                                                 reserved6128;	//0xC4F46510
	UINT32                                                 reserved6129;	//0xC4F46514
	UINT32                                                 reserved6130;	//0xC4F46518
	UINT32                                                 reserved6131;	//0xC4F4651C
	UINT32                                                 reserved6132;	//0xC4F46520
	UINT32                                                 reserved6133;	//0xC4F46524
	UINT32                                                 reserved6134;	//0xC4F46528
	UINT32                                                 reserved6135;	//0xC4F4652C
	UINT32                                                 reserved6136;	//0xC4F46530
	UINT32                                                 reserved6137;	//0xC4F46534
	UINT32                                                 reserved6138;	//0xC4F46538
	UINT32                                                 reserved6139;	//0xC4F4653C
	UINT32                                                 reserved6140;	//0xC4F46540
	UINT32                                                 reserved6141;	//0xC4F46544
	UINT32                                                 reserved6142;	//0xC4F46548
	UINT32                                                 reserved6143;	//0xC4F4654C
	UINT32                                                 reserved6144;	//0xC4F46550
	UINT32                                                 reserved6145;	//0xC4F46554
	UINT32                                                 reserved6146;	//0xC4F46558
	UINT32                                                 reserved6147;	//0xC4F4655C
	UINT32                                                 reserved6148;	//0xC4F46560
	UINT32                                                 reserved6149;	//0xC4F46564
	UINT32                                                 reserved6150;	//0xC4F46568
	UINT32                                                 reserved6151;	//0xC4F4656C
	UINT32                                                 reserved6152;	//0xC4F46570
	UINT32                                                 reserved6153;	//0xC4F46574
	UINT32                                                 reserved6154;	//0xC4F46578
	UINT32                                                 reserved6155;	//0xC4F4657C
	UINT32                                                 reserved6156;	//0xC4F46580
	UINT32                                                 reserved6157;	//0xC4F46584
	UINT32                                                 reserved6158;	//0xC4F46588
	UINT32                                                 reserved6159;	//0xC4F4658C
	UINT32                                                 reserved6160;	//0xC4F46590
	UINT32                                                 reserved6161;	//0xC4F46594
	UINT32                                                 reserved6162;	//0xC4F46598
	UINT32                                                 reserved6163;	//0xC4F4659C
	UINT32                                                 reserved6164;	//0xC4F465A0
	UINT32                                                 reserved6165;	//0xC4F465A4
	UINT32                                                 reserved6166;	//0xC4F465A8
	UINT32                                                 reserved6167;	//0xC4F465AC
	UINT32                                                 reserved6168;	//0xC4F465B0
	UINT32                                                 reserved6169;	//0xC4F465B4
	UINT32                                                 reserved6170;	//0xC4F465B8
	UINT32                                                 reserved6171;	//0xC4F465BC
	UINT32                                                 reserved6172;	//0xC4F465C0
	UINT32                                                 reserved6173;	//0xC4F465C4
	UINT32                                                 reserved6174;	//0xC4F465C8
	UINT32                                                 reserved6175;	//0xC4F465CC
	UINT32                                                 reserved6176;	//0xC4F465D0
	UINT32                                                 reserved6177;	//0xC4F465D4
	UINT32                                                 reserved6178;	//0xC4F465D8
	UINT32                                                 reserved6179;	//0xC4F465DC
	UINT32                                                 reserved6180;	//0xC4F465E0
	UINT32                                                 reserved6181;	//0xC4F465E4
	UINT32                                                 reserved6182;	//0xC4F465E8
	UINT32                                                 reserved6183;	//0xC4F465EC
	UINT32                                                 reserved6184;	//0xC4F465F0
	UINT32                                                 reserved6185;	//0xC4F465F4
	UINT32                                                 reserved6186;	//0xC4F465F8
	UINT32                                                 reserved6187;	//0xC4F465FC
	UINT32                                                 reserved6188;	//0xC4F46600
	UINT32                                                 reserved6189;	//0xC4F46604
	UINT32                                                 reserved6190;	//0xC4F46608
	UINT32                                                 reserved6191;	//0xC4F4660C
	UINT32                                                 reserved6192;	//0xC4F46610
	UINT32                                                 reserved6193;	//0xC4F46614
	UINT32                                                 reserved6194;	//0xC4F46618
	UINT32                                                 reserved6195;	//0xC4F4661C
	UINT32                                                 reserved6196;	//0xC4F46620
	UINT32                                                 reserved6197;	//0xC4F46624
	UINT32                                                 reserved6198;	//0xC4F46628
	UINT32                                                 reserved6199;	//0xC4F4662C
	UINT32                                                 reserved6200;	//0xC4F46630
	UINT32                                                 reserved6201;	//0xC4F46634
	UINT32                                                 reserved6202;	//0xC4F46638
	UINT32                                                 reserved6203;	//0xC4F4663C
	UINT32                                                 reserved6204;	//0xC4F46640
	UINT32                                                 reserved6205;	//0xC4F46644
	UINT32                                                 reserved6206;	//0xC4F46648
	UINT32                                                 reserved6207;	//0xC4F4664C
	UINT32                                                 reserved6208;	//0xC4F46650
	UINT32                                                 reserved6209;	//0xC4F46654
	UINT32                                                 reserved6210;	//0xC4F46658
	UINT32                                                 reserved6211;	//0xC4F4665C
	UINT32                                                 reserved6212;	//0xC4F46660
	UINT32                                                 reserved6213;	//0xC4F46664
	UINT32                                                 reserved6214;	//0xC4F46668
	UINT32                                                 reserved6215;	//0xC4F4666C
	UINT32                                                 reserved6216;	//0xC4F46670
	UINT32                                                 reserved6217;	//0xC4F46674
	UINT32                                                 reserved6218;	//0xC4F46678
	UINT32                                                 reserved6219;	//0xC4F4667C
	UINT32                                                 reserved6220;	//0xC4F46680
	UINT32                                                 reserved6221;	//0xC4F46684
	UINT32                                                 reserved6222;	//0xC4F46688
	UINT32                                                 reserved6223;	//0xC4F4668C
	UINT32                                                 reserved6224;	//0xC4F46690
	UINT32                                                 reserved6225;	//0xC4F46694
	UINT32                                                 reserved6226;	//0xC4F46698
	UINT32                                                 reserved6227;	//0xC4F4669C
	UINT32                                                 reserved6228;	//0xC4F466A0
	UINT32                                                 reserved6229;	//0xC4F466A4
	UINT32                                                 reserved6230;	//0xC4F466A8
	UINT32                                                 reserved6231;	//0xC4F466AC
	UINT32                                                 reserved6232;	//0xC4F466B0
	UINT32                                                 reserved6233;	//0xC4F466B4
	UINT32                                                 reserved6234;	//0xC4F466B8
	UINT32                                                 reserved6235;	//0xC4F466BC
	UINT32                                                 reserved6236;	//0xC4F466C0
	UINT32                                                 reserved6237;	//0xC4F466C4
	UINT32                                                 reserved6238;	//0xC4F466C8
	UINT32                                                 reserved6239;	//0xC4F466CC
	UINT32                                                 reserved6240;	//0xC4F466D0
	UINT32                                                 reserved6241;	//0xC4F466D4
	UINT32                                                 reserved6242;	//0xC4F466D8
	UINT32                                                 reserved6243;	//0xC4F466DC
	UINT32                                                 reserved6244;	//0xC4F466E0
	UINT32                                                 reserved6245;	//0xC4F466E4
	UINT32                                                 reserved6246;	//0xC4F466E8
	UINT32                                                 reserved6247;	//0xC4F466EC
	UINT32                                                 reserved6248;	//0xC4F466F0
	UINT32                                                 reserved6249;	//0xC4F466F4
	UINT32                                                 reserved6250;	//0xC4F466F8
	UINT32                                                 reserved6251;	//0xC4F466FC
	REG_DDRC_M0_DEBUG_DFI_T                                   debug_dfi;	//0xC4F46700
	UINT32                                                 reserved6252;	//0xC4F46704
	UINT32                                                 reserved6253;	//0xC4F46708
	UINT32                                                 reserved6254;	//0xC4F4670C
	UINT32                                                 reserved6255;	//0xC4F46710
	UINT32                                                 reserved6256;	//0xC4F46714
	UINT32                                                 reserved6257;	//0xC4F46718
	UINT32                                                 reserved6258;	//0xC4F4671C
	UINT32                                                 reserved6259;	//0xC4F46720
	UINT32                                                 reserved6260;	//0xC4F46724
	UINT32                                                 reserved6261;	//0xC4F46728
	UINT32                                                 reserved6262;	//0xC4F4672C
	UINT32                                                 reserved6263;	//0xC4F46730
	UINT32                                                 reserved6264;	//0xC4F46734
	UINT32                                                 reserved6265;	//0xC4F46738
	UINT32                                                 reserved6266;	//0xC4F4673C
	UINT32                                                 reserved6267;	//0xC4F46740
	UINT32                                                 reserved6268;	//0xC4F46744
	UINT32                                                 reserved6269;	//0xC4F46748
	UINT32                                                 reserved6270;	//0xC4F4674C
	UINT32                                                 reserved6271;	//0xC4F46750
	UINT32                                                 reserved6272;	//0xC4F46754
	UINT32                                                 reserved6273;	//0xC4F46758
	UINT32                                                 reserved6274;	//0xC4F4675C
	UINT32                                                 reserved6275;	//0xC4F46760
	UINT32                                                 reserved6276;	//0xC4F46764
	UINT32                                                 reserved6277;	//0xC4F46768
	UINT32                                                 reserved6278;	//0xC4F4676C
	UINT32                                                 reserved6279;	//0xC4F46770
	UINT32                                                 reserved6280;	//0xC4F46774
	UINT32                                                 reserved6281;	//0xC4F46778
	UINT32                                                 reserved6282;	//0xC4F4677C
	UINT32                                                 reserved6283;	//0xC4F46780
	UINT32                                                 reserved6284;	//0xC4F46784
	UINT32                                                 reserved6285;	//0xC4F46788
	UINT32                                                 reserved6286;	//0xC4F4678C
	UINT32                                                 reserved6287;	//0xC4F46790
	UINT32                                                 reserved6288;	//0xC4F46794
	UINT32                                                 reserved6289;	//0xC4F46798
	UINT32                                                 reserved6290;	//0xC4F4679C
	UINT32                                                 reserved6291;	//0xC4F467A0
	UINT32                                                 reserved6292;	//0xC4F467A4
	UINT32                                                 reserved6293;	//0xC4F467A8
	UINT32                                                 reserved6294;	//0xC4F467AC
	UINT32                                                 reserved6295;	//0xC4F467B0
	UINT32                                                 reserved6296;	//0xC4F467B4
	UINT32                                                 reserved6297;	//0xC4F467B8
	UINT32                                                 reserved6298;	//0xC4F467BC
	UINT32                                                 reserved6299;	//0xC4F467C0
	UINT32                                                 reserved6300;	//0xC4F467C4
	UINT32                                                 reserved6301;	//0xC4F467C8
	UINT32                                                 reserved6302;	//0xC4F467CC
	UINT32                                                 reserved6303;	//0xC4F467D0
	UINT32                                                 reserved6304;	//0xC4F467D4
	UINT32                                                 reserved6305;	//0xC4F467D8
	UINT32                                                 reserved6306;	//0xC4F467DC
	UINT32                                                 reserved6307;	//0xC4F467E0
	UINT32                                                 reserved6308;	//0xC4F467E4
	UINT32                                                 reserved6309;	//0xC4F467E8
	UINT32                                                 reserved6310;	//0xC4F467EC
	UINT32                                                 reserved6311;	//0xC4F467F0
	UINT32                                                 reserved6312;	//0xC4F467F4
	UINT32                                                 reserved6313;	//0xC4F467F8
	UINT32                                                 reserved6314;	//0xC4F467FC
	REG_DDRC_M0_DRAM_BIST_CTRL_0_T                     dram_bist_ctrl_0;	//0xC4F46800
	REG_DDRC_M0_DRAM_BIST_CTRL_1_T                     dram_bist_ctrl_1;	//0xC4F46804
	REG_DDRC_M0_DRAM_BIST_CTRL_2_T                     dram_bist_ctrl_2;	//0xC4F46808
	REG_DDRC_M0_DRAM_BIST_DATA_0_T                     dram_bist_data_0;	//0xC4F4680C
	REG_DDRC_M0_DRAM_BIST_DATA_1_T                     dram_bist_data_1;	//0xC4F46810
	REG_DDRC_M0_DRAM_BIST_DATA_2_T                     dram_bist_data_2;	//0xC4F46814
	REG_DDRC_M0_DRAM_BIST_ADDR_0_T                     dram_bist_addr_0;	//0xC4F46818
	REG_DDRC_M0_DRAM_BIST_ADDR_1_T                     dram_bist_addr_1;	//0xC4F4681C
	REG_DDRC_M0_DRAM_BIST_ADDR_2_T                     dram_bist_addr_2;	//0xC4F46820
	REG_DDRC_M0_DRAM_BIST_OPCMD_0_T                   dram_bist_opcmd_0;	//0xC4F46824
	REG_DDRC_M0_DRAM_BIST_OPCMD_1_T                   dram_bist_opcmd_1;	//0xC4F46828
	REG_DDRC_M0_DRAM_BIST_OPCMD_2_T                   dram_bist_opcmd_2;	//0xC4F4682C
	REG_DDRC_M0_DRAM_BIST_OPCMD_3_T                   dram_bist_opcmd_3;	//0xC4F46830
	REG_DDRC_M0_DRAM_BIST_ERR_ADDR_INFO_T       dram_bist_err_addr_info;	//0xC4F46834
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_00_T dram_bist_err_data_info_00;	//0xC4F46838
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_01_T dram_bist_err_data_info_01;	//0xC4F4683C
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_02_T dram_bist_err_data_info_02;	//0xC4F46840
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_03_T dram_bist_err_data_info_03;	//0xC4F46844
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_04_T dram_bist_err_data_info_04;	//0xC4F46848
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_05_T dram_bist_err_data_info_05;	//0xC4F4684C
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_06_T dram_bist_err_data_info_06;	//0xC4F46850
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_07_T dram_bist_err_data_info_07;	//0xC4F46854
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_08_T dram_bist_err_data_info_08;	//0xC4F46858
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_09_T dram_bist_err_data_info_09;	//0xC4F4685C
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_10_T dram_bist_err_data_info_10;	//0xC4F46860
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_11_T dram_bist_err_data_info_11;	//0xC4F46864
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_12_T dram_bist_err_data_info_12;	//0xC4F46868
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_13_T dram_bist_err_data_info_13;	//0xC4F4686C
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_14_T dram_bist_err_data_info_14;	//0xC4F46870
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_15_T dram_bist_err_data_info_15;	//0xC4F46874
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_00_T dram_bist_exp_data_info_00;	//0xC4F46878
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_01_T dram_bist_exp_data_info_01;	//0xC4F4687C
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_02_T dram_bist_exp_data_info_02;	//0xC4F46880
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_03_T dram_bist_exp_data_info_03;	//0xC4F46884
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_04_T dram_bist_exp_data_info_04;	//0xC4F46888
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_05_T dram_bist_exp_data_info_05;	//0xC4F4688C
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_06_T dram_bist_exp_data_info_06;	//0xC4F46890
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_07_T dram_bist_exp_data_info_07;	//0xC4F46894
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_08_T dram_bist_exp_data_info_08;	//0xC4F46898
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_09_T dram_bist_exp_data_info_09;	//0xC4F4689C
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_10_T dram_bist_exp_data_info_10;	//0xC4F468A0
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_11_T dram_bist_exp_data_info_11;	//0xC4F468A4
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_12_T dram_bist_exp_data_info_12;	//0xC4F468A8
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_13_T dram_bist_exp_data_info_13;	//0xC4F468AC
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_14_T dram_bist_exp_data_info_14;	//0xC4F468B0
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_15_T dram_bist_exp_data_info_15;	//0xC4F468B4
	UINT32                                                 reserved6315;	//0xC4F468B8
	UINT32                                                 reserved6316;	//0xC4F468BC
	UINT32                                                 reserved6317;	//0xC4F468C0
	UINT32                                                 reserved6318;	//0xC4F468C4
	UINT32                                                 reserved6319;	//0xC4F468C8
	UINT32                                                 reserved6320;	//0xC4F468CC
	UINT32                                                 reserved6321;	//0xC4F468D0
	UINT32                                                 reserved6322;	//0xC4F468D4
	UINT32                                                 reserved6323;	//0xC4F468D8
	UINT32                                                 reserved6324;	//0xC4F468DC
	UINT32                                                 reserved6325;	//0xC4F468E0
	UINT32                                                 reserved6326;	//0xC4F468E4
	UINT32                                                 reserved6327;	//0xC4F468E8
	UINT32                                                 reserved6328;	//0xC4F468EC
	UINT32                                                 reserved6329;	//0xC4F468F0
	UINT32                                                 reserved6330;	//0xC4F468F4
	UINT32                                                 reserved6331;	//0xC4F468F8
	UINT32                                                 reserved6332;	//0xC4F468FC
	UINT32                                                 reserved6333;	//0xC4F46900
	UINT32                                                 reserved6334;	//0xC4F46904
	UINT32                                                 reserved6335;	//0xC4F46908
	UINT32                                                 reserved6336;	//0xC4F4690C
	UINT32                                                 reserved6337;	//0xC4F46910
	UINT32                                                 reserved6338;	//0xC4F46914
	UINT32                                                 reserved6339;	//0xC4F46918
	UINT32                                                 reserved6340;	//0xC4F4691C
	UINT32                                                 reserved6341;	//0xC4F46920
	UINT32                                                 reserved6342;	//0xC4F46924
	UINT32                                                 reserved6343;	//0xC4F46928
	UINT32                                                 reserved6344;	//0xC4F4692C
	UINT32                                                 reserved6345;	//0xC4F46930
	UINT32                                                 reserved6346;	//0xC4F46934
	UINT32                                                 reserved6347;	//0xC4F46938
	UINT32                                                 reserved6348;	//0xC4F4693C
	UINT32                                                 reserved6349;	//0xC4F46940
	UINT32                                                 reserved6350;	//0xC4F46944
	UINT32                                                 reserved6351;	//0xC4F46948
	UINT32                                                 reserved6352;	//0xC4F4694C
	UINT32                                                 reserved6353;	//0xC4F46950
	UINT32                                                 reserved6354;	//0xC4F46954
	UINT32                                                 reserved6355;	//0xC4F46958
	UINT32                                                 reserved6356;	//0xC4F4695C
	UINT32                                                 reserved6357;	//0xC4F46960
	UINT32                                                 reserved6358;	//0xC4F46964
	UINT32                                                 reserved6359;	//0xC4F46968
	UINT32                                                 reserved6360;	//0xC4F4696C
	UINT32                                                 reserved6361;	//0xC4F46970
	UINT32                                                 reserved6362;	//0xC4F46974
	UINT32                                                 reserved6363;	//0xC4F46978
	UINT32                                                 reserved6364;	//0xC4F4697C
	UINT32                                                 reserved6365;	//0xC4F46980
	UINT32                                                 reserved6366;	//0xC4F46984
	UINT32                                                 reserved6367;	//0xC4F46988
	UINT32                                                 reserved6368;	//0xC4F4698C
	UINT32                                                 reserved6369;	//0xC4F46990
	UINT32                                                 reserved6370;	//0xC4F46994
	UINT32                                                 reserved6371;	//0xC4F46998
	UINT32                                                 reserved6372;	//0xC4F4699C
	UINT32                                                 reserved6373;	//0xC4F469A0
	UINT32                                                 reserved6374;	//0xC4F469A4
	UINT32                                                 reserved6375;	//0xC4F469A8
	UINT32                                                 reserved6376;	//0xC4F469AC
	UINT32                                                 reserved6377;	//0xC4F469B0
	UINT32                                                 reserved6378;	//0xC4F469B4
	UINT32                                                 reserved6379;	//0xC4F469B8
	UINT32                                                 reserved6380;	//0xC4F469BC
	UINT32                                                 reserved6381;	//0xC4F469C0
	UINT32                                                 reserved6382;	//0xC4F469C4
	UINT32                                                 reserved6383;	//0xC4F469C8
	UINT32                                                 reserved6384;	//0xC4F469CC
	UINT32                                                 reserved6385;	//0xC4F469D0
	UINT32                                                 reserved6386;	//0xC4F469D4
	UINT32                                                 reserved6387;	//0xC4F469D8
	UINT32                                                 reserved6388;	//0xC4F469DC
	UINT32                                                 reserved6389;	//0xC4F469E0
	UINT32                                                 reserved6390;	//0xC4F469E4
	UINT32                                                 reserved6391;	//0xC4F469E8
	UINT32                                                 reserved6392;	//0xC4F469EC
	UINT32                                                 reserved6393;	//0xC4F469F0
	UINT32                                                 reserved6394;	//0xC4F469F4
	UINT32                                                 reserved6395;	//0xC4F469F8
	UINT32                                                 reserved6396;	//0xC4F469FC
	UINT32                                                 reserved6397;	//0xC4F46A00
	UINT32                                                 reserved6398;	//0xC4F46A04
	UINT32                                                 reserved6399;	//0xC4F46A08
	UINT32                                                 reserved6400;	//0xC4F46A0C
	UINT32                                                 reserved6401;	//0xC4F46A10
	UINT32                                                 reserved6402;	//0xC4F46A14
	UINT32                                                 reserved6403;	//0xC4F46A18
	UINT32                                                 reserved6404;	//0xC4F46A1C
	UINT32                                                 reserved6405;	//0xC4F46A20
	UINT32                                                 reserved6406;	//0xC4F46A24
	UINT32                                                 reserved6407;	//0xC4F46A28
	UINT32                                                 reserved6408;	//0xC4F46A2C
	UINT32                                                 reserved6409;	//0xC4F46A30
	UINT32                                                 reserved6410;	//0xC4F46A34
	UINT32                                                 reserved6411;	//0xC4F46A38
	UINT32                                                 reserved6412;	//0xC4F46A3C
	UINT32                                                 reserved6413;	//0xC4F46A40
	UINT32                                                 reserved6414;	//0xC4F46A44
	UINT32                                                 reserved6415;	//0xC4F46A48
	UINT32                                                 reserved6416;	//0xC4F46A4C
	UINT32                                                 reserved6417;	//0xC4F46A50
	UINT32                                                 reserved6418;	//0xC4F46A54
	UINT32                                                 reserved6419;	//0xC4F46A58
	UINT32                                                 reserved6420;	//0xC4F46A5C
	UINT32                                                 reserved6421;	//0xC4F46A60
	UINT32                                                 reserved6422;	//0xC4F46A64
	UINT32                                                 reserved6423;	//0xC4F46A68
	UINT32                                                 reserved6424;	//0xC4F46A6C
	UINT32                                                 reserved6425;	//0xC4F46A70
	UINT32                                                 reserved6426;	//0xC4F46A74
	UINT32                                                 reserved6427;	//0xC4F46A78
	UINT32                                                 reserved6428;	//0xC4F46A7C
	UINT32                                                 reserved6429;	//0xC4F46A80
	UINT32                                                 reserved6430;	//0xC4F46A84
	UINT32                                                 reserved6431;	//0xC4F46A88
	UINT32                                                 reserved6432;	//0xC4F46A8C
	UINT32                                                 reserved6433;	//0xC4F46A90
	UINT32                                                 reserved6434;	//0xC4F46A94
	UINT32                                                 reserved6435;	//0xC4F46A98
	UINT32                                                 reserved6436;	//0xC4F46A9C
	UINT32                                                 reserved6437;	//0xC4F46AA0
	UINT32                                                 reserved6438;	//0xC4F46AA4
	UINT32                                                 reserved6439;	//0xC4F46AA8
	UINT32                                                 reserved6440;	//0xC4F46AAC
	UINT32                                                 reserved6441;	//0xC4F46AB0
	UINT32                                                 reserved6442;	//0xC4F46AB4
	UINT32                                                 reserved6443;	//0xC4F46AB8
	UINT32                                                 reserved6444;	//0xC4F46ABC
	UINT32                                                 reserved6445;	//0xC4F46AC0
	UINT32                                                 reserved6446;	//0xC4F46AC4
	UINT32                                                 reserved6447;	//0xC4F46AC8
	UINT32                                                 reserved6448;	//0xC4F46ACC
	UINT32                                                 reserved6449;	//0xC4F46AD0
	UINT32                                                 reserved6450;	//0xC4F46AD4
	UINT32                                                 reserved6451;	//0xC4F46AD8
	UINT32                                                 reserved6452;	//0xC4F46ADC
	UINT32                                                 reserved6453;	//0xC4F46AE0
	UINT32                                                 reserved6454;	//0xC4F46AE4
	UINT32                                                 reserved6455;	//0xC4F46AE8
	UINT32                                                 reserved6456;	//0xC4F46AEC
	UINT32                                                 reserved6457;	//0xC4F46AF0
	UINT32                                                 reserved6458;	//0xC4F46AF4
	UINT32                                                 reserved6459;	//0xC4F46AF8
	UINT32                                                 reserved6460;	//0xC4F46AFC
	UINT32                                                 reserved6461;	//0xC4F46B00
	UINT32                                                 reserved6462;	//0xC4F46B04
	UINT32                                                 reserved6463;	//0xC4F46B08
	UINT32                                                 reserved6464;	//0xC4F46B0C
	UINT32                                                 reserved6465;	//0xC4F46B10
	UINT32                                                 reserved6466;	//0xC4F46B14
	UINT32                                                 reserved6467;	//0xC4F46B18
	UINT32                                                 reserved6468;	//0xC4F46B1C
	UINT32                                                 reserved6469;	//0xC4F46B20
	UINT32                                                 reserved6470;	//0xC4F46B24
	UINT32                                                 reserved6471;	//0xC4F46B28
	UINT32                                                 reserved6472;	//0xC4F46B2C
	UINT32                                                 reserved6473;	//0xC4F46B30
	UINT32                                                 reserved6474;	//0xC4F46B34
	UINT32                                                 reserved6475;	//0xC4F46B38
	UINT32                                                 reserved6476;	//0xC4F46B3C
	UINT32                                                 reserved6477;	//0xC4F46B40
	UINT32                                                 reserved6478;	//0xC4F46B44
	UINT32                                                 reserved6479;	//0xC4F46B48
	UINT32                                                 reserved6480;	//0xC4F46B4C
	UINT32                                                 reserved6481;	//0xC4F46B50
	UINT32                                                 reserved6482;	//0xC4F46B54
	UINT32                                                 reserved6483;	//0xC4F46B58
	UINT32                                                 reserved6484;	//0xC4F46B5C
	UINT32                                                 reserved6485;	//0xC4F46B60
	UINT32                                                 reserved6486;	//0xC4F46B64
	UINT32                                                 reserved6487;	//0xC4F46B68
	UINT32                                                 reserved6488;	//0xC4F46B6C
	UINT32                                                 reserved6489;	//0xC4F46B70
	UINT32                                                 reserved6490;	//0xC4F46B74
	UINT32                                                 reserved6491;	//0xC4F46B78
	UINT32                                                 reserved6492;	//0xC4F46B7C
	UINT32                                                 reserved6493;	//0xC4F46B80
	UINT32                                                 reserved6494;	//0xC4F46B84
	UINT32                                                 reserved6495;	//0xC4F46B88
	UINT32                                                 reserved6496;	//0xC4F46B8C
	UINT32                                                 reserved6497;	//0xC4F46B90
	UINT32                                                 reserved6498;	//0xC4F46B94
	UINT32                                                 reserved6499;	//0xC4F46B98
	UINT32                                                 reserved6500;	//0xC4F46B9C
	UINT32                                                 reserved6501;	//0xC4F46BA0
	UINT32                                                 reserved6502;	//0xC4F46BA4
	UINT32                                                 reserved6503;	//0xC4F46BA8
	UINT32                                                 reserved6504;	//0xC4F46BAC
	UINT32                                                 reserved6505;	//0xC4F46BB0
	UINT32                                                 reserved6506;	//0xC4F46BB4
	UINT32                                                 reserved6507;	//0xC4F46BB8
	UINT32                                                 reserved6508;	//0xC4F46BBC
	UINT32                                                 reserved6509;	//0xC4F46BC0
	UINT32                                                 reserved6510;	//0xC4F46BC4
	UINT32                                                 reserved6511;	//0xC4F46BC8
	UINT32                                                 reserved6512;	//0xC4F46BCC
	UINT32                                                 reserved6513;	//0xC4F46BD0
	UINT32                                                 reserved6514;	//0xC4F46BD4
	UINT32                                                 reserved6515;	//0xC4F46BD8
	UINT32                                                 reserved6516;	//0xC4F46BDC
	UINT32                                                 reserved6517;	//0xC4F46BE0
	UINT32                                                 reserved6518;	//0xC4F46BE4
	UINT32                                                 reserved6519;	//0xC4F46BE8
	UINT32                                                 reserved6520;	//0xC4F46BEC
	UINT32                                                 reserved6521;	//0xC4F46BF0
	UINT32                                                 reserved6522;	//0xC4F46BF4
	UINT32                                                 reserved6523;	//0xC4F46BF8
	UINT32                                                 reserved6524;	//0xC4F46BFC
	UINT32                                                 reserved6525;	//0xC4F46C00
	UINT32                                                 reserved6526;	//0xC4F46C04
	UINT32                                                 reserved6527;	//0xC4F46C08
	UINT32                                                 reserved6528;	//0xC4F46C0C
	UINT32                                                 reserved6529;	//0xC4F46C10
	UINT32                                                 reserved6530;	//0xC4F46C14
	UINT32                                                 reserved6531;	//0xC4F46C18
	UINT32                                                 reserved6532;	//0xC4F46C1C
	UINT32                                                 reserved6533;	//0xC4F46C20
	UINT32                                                 reserved6534;	//0xC4F46C24
	UINT32                                                 reserved6535;	//0xC4F46C28
	UINT32                                                 reserved6536;	//0xC4F46C2C
	UINT32                                                 reserved6537;	//0xC4F46C30
	UINT32                                                 reserved6538;	//0xC4F46C34
	UINT32                                                 reserved6539;	//0xC4F46C38
	UINT32                                                 reserved6540;	//0xC4F46C3C
	UINT32                                                 reserved6541;	//0xC4F46C40
	UINT32                                                 reserved6542;	//0xC4F46C44
	UINT32                                                 reserved6543;	//0xC4F46C48
	UINT32                                                 reserved6544;	//0xC4F46C4C
	UINT32                                                 reserved6545;	//0xC4F46C50
	UINT32                                                 reserved6546;	//0xC4F46C54
	UINT32                                                 reserved6547;	//0xC4F46C58
	UINT32                                                 reserved6548;	//0xC4F46C5C
	UINT32                                                 reserved6549;	//0xC4F46C60
	UINT32                                                 reserved6550;	//0xC4F46C64
	UINT32                                                 reserved6551;	//0xC4F46C68
	UINT32                                                 reserved6552;	//0xC4F46C6C
	UINT32                                                 reserved6553;	//0xC4F46C70
	UINT32                                                 reserved6554;	//0xC4F46C74
	UINT32                                                 reserved6555;	//0xC4F46C78
	UINT32                                                 reserved6556;	//0xC4F46C7C
	UINT32                                                 reserved6557;	//0xC4F46C80
	UINT32                                                 reserved6558;	//0xC4F46C84
	UINT32                                                 reserved6559;	//0xC4F46C88
	UINT32                                                 reserved6560;	//0xC4F46C8C
	UINT32                                                 reserved6561;	//0xC4F46C90
	UINT32                                                 reserved6562;	//0xC4F46C94
	UINT32                                                 reserved6563;	//0xC4F46C98
	UINT32                                                 reserved6564;	//0xC4F46C9C
	UINT32                                                 reserved6565;	//0xC4F46CA0
	UINT32                                                 reserved6566;	//0xC4F46CA4
	UINT32                                                 reserved6567;	//0xC4F46CA8
	UINT32                                                 reserved6568;	//0xC4F46CAC
	UINT32                                                 reserved6569;	//0xC4F46CB0
	UINT32                                                 reserved6570;	//0xC4F46CB4
	UINT32                                                 reserved6571;	//0xC4F46CB8
	UINT32                                                 reserved6572;	//0xC4F46CBC
	UINT32                                                 reserved6573;	//0xC4F46CC0
	UINT32                                                 reserved6574;	//0xC4F46CC4
	UINT32                                                 reserved6575;	//0xC4F46CC8
	UINT32                                                 reserved6576;	//0xC4F46CCC
	UINT32                                                 reserved6577;	//0xC4F46CD0
	UINT32                                                 reserved6578;	//0xC4F46CD4
	UINT32                                                 reserved6579;	//0xC4F46CD8
	UINT32                                                 reserved6580;	//0xC4F46CDC
	UINT32                                                 reserved6581;	//0xC4F46CE0
	UINT32                                                 reserved6582;	//0xC4F46CE4
	UINT32                                                 reserved6583;	//0xC4F46CE8
	UINT32                                                 reserved6584;	//0xC4F46CEC
	UINT32                                                 reserved6585;	//0xC4F46CF0
	UINT32                                                 reserved6586;	//0xC4F46CF4
	UINT32                                                 reserved6587;	//0xC4F46CF8
	UINT32                                                 reserved6588;	//0xC4F46CFC
	UINT32                                                 reserved6589;	//0xC4F46D00
	UINT32                                                 reserved6590;	//0xC4F46D04
	UINT32                                                 reserved6591;	//0xC4F46D08
	UINT32                                                 reserved6592;	//0xC4F46D0C
	UINT32                                                 reserved6593;	//0xC4F46D10
	UINT32                                                 reserved6594;	//0xC4F46D14
	UINT32                                                 reserved6595;	//0xC4F46D18
	UINT32                                                 reserved6596;	//0xC4F46D1C
	UINT32                                                 reserved6597;	//0xC4F46D20
	UINT32                                                 reserved6598;	//0xC4F46D24
	UINT32                                                 reserved6599;	//0xC4F46D28
	UINT32                                                 reserved6600;	//0xC4F46D2C
	UINT32                                                 reserved6601;	//0xC4F46D30
	UINT32                                                 reserved6602;	//0xC4F46D34
	UINT32                                                 reserved6603;	//0xC4F46D38
	UINT32                                                 reserved6604;	//0xC4F46D3C
	UINT32                                                 reserved6605;	//0xC4F46D40
	UINT32                                                 reserved6606;	//0xC4F46D44
	UINT32                                                 reserved6607;	//0xC4F46D48
	UINT32                                                 reserved6608;	//0xC4F46D4C
	UINT32                                                 reserved6609;	//0xC4F46D50
	UINT32                                                 reserved6610;	//0xC4F46D54
	UINT32                                                 reserved6611;	//0xC4F46D58
	UINT32                                                 reserved6612;	//0xC4F46D5C
	UINT32                                                 reserved6613;	//0xC4F46D60
	UINT32                                                 reserved6614;	//0xC4F46D64
	UINT32                                                 reserved6615;	//0xC4F46D68
	UINT32                                                 reserved6616;	//0xC4F46D6C
	UINT32                                                 reserved6617;	//0xC4F46D70
	UINT32                                                 reserved6618;	//0xC4F46D74
	UINT32                                                 reserved6619;	//0xC4F46D78
	UINT32                                                 reserved6620;	//0xC4F46D7C
	UINT32                                                 reserved6621;	//0xC4F46D80
	UINT32                                                 reserved6622;	//0xC4F46D84
	UINT32                                                 reserved6623;	//0xC4F46D88
	UINT32                                                 reserved6624;	//0xC4F46D8C
	UINT32                                                 reserved6625;	//0xC4F46D90
	UINT32                                                 reserved6626;	//0xC4F46D94
	UINT32                                                 reserved6627;	//0xC4F46D98
	UINT32                                                 reserved6628;	//0xC4F46D9C
	UINT32                                                 reserved6629;	//0xC4F46DA0
	UINT32                                                 reserved6630;	//0xC4F46DA4
	UINT32                                                 reserved6631;	//0xC4F46DA8
	UINT32                                                 reserved6632;	//0xC4F46DAC
	UINT32                                                 reserved6633;	//0xC4F46DB0
	UINT32                                                 reserved6634;	//0xC4F46DB4
	UINT32                                                 reserved6635;	//0xC4F46DB8
	UINT32                                                 reserved6636;	//0xC4F46DBC
	UINT32                                                 reserved6637;	//0xC4F46DC0
	UINT32                                                 reserved6638;	//0xC4F46DC4
	UINT32                                                 reserved6639;	//0xC4F46DC8
	UINT32                                                 reserved6640;	//0xC4F46DCC
	UINT32                                                 reserved6641;	//0xC4F46DD0
	UINT32                                                 reserved6642;	//0xC4F46DD4
	UINT32                                                 reserved6643;	//0xC4F46DD8
	UINT32                                                 reserved6644;	//0xC4F46DDC
	UINT32                                                 reserved6645;	//0xC4F46DE0
	UINT32                                                 reserved6646;	//0xC4F46DE4
	UINT32                                                 reserved6647;	//0xC4F46DE8
	UINT32                                                 reserved6648;	//0xC4F46DEC
	UINT32                                                 reserved6649;	//0xC4F46DF0
	UINT32                                                 reserved6650;	//0xC4F46DF4
	UINT32                                                 reserved6651;	//0xC4F46DF8
	UINT32                                                 reserved6652;	//0xC4F46DFC
	UINT32                                                 reserved6653;	//0xC4F46E00
	UINT32                                                 reserved6654;	//0xC4F46E04
	UINT32                                                 reserved6655;	//0xC4F46E08
	UINT32                                                 reserved6656;	//0xC4F46E0C
	UINT32                                                 reserved6657;	//0xC4F46E10
	UINT32                                                 reserved6658;	//0xC4F46E14
	UINT32                                                 reserved6659;	//0xC4F46E18
	UINT32                                                 reserved6660;	//0xC4F46E1C
	UINT32                                                 reserved6661;	//0xC4F46E20
	UINT32                                                 reserved6662;	//0xC4F46E24
	UINT32                                                 reserved6663;	//0xC4F46E28
	UINT32                                                 reserved6664;	//0xC4F46E2C
	UINT32                                                 reserved6665;	//0xC4F46E30
	UINT32                                                 reserved6666;	//0xC4F46E34
	UINT32                                                 reserved6667;	//0xC4F46E38
	UINT32                                                 reserved6668;	//0xC4F46E3C
	UINT32                                                 reserved6669;	//0xC4F46E40
	UINT32                                                 reserved6670;	//0xC4F46E44
	UINT32                                                 reserved6671;	//0xC4F46E48
	UINT32                                                 reserved6672;	//0xC4F46E4C
	UINT32                                                 reserved6673;	//0xC4F46E50
	UINT32                                                 reserved6674;	//0xC4F46E54
	UINT32                                                 reserved6675;	//0xC4F46E58
	UINT32                                                 reserved6676;	//0xC4F46E5C
	UINT32                                                 reserved6677;	//0xC4F46E60
	UINT32                                                 reserved6678;	//0xC4F46E64
	UINT32                                                 reserved6679;	//0xC4F46E68
	UINT32                                                 reserved6680;	//0xC4F46E6C
	UINT32                                                 reserved6681;	//0xC4F46E70
	UINT32                                                 reserved6682;	//0xC4F46E74
	UINT32                                                 reserved6683;	//0xC4F46E78
	UINT32                                                 reserved6684;	//0xC4F46E7C
	UINT32                                                 reserved6685;	//0xC4F46E80
	UINT32                                                 reserved6686;	//0xC4F46E84
	UINT32                                                 reserved6687;	//0xC4F46E88
	UINT32                                                 reserved6688;	//0xC4F46E8C
	UINT32                                                 reserved6689;	//0xC4F46E90
	UINT32                                                 reserved6690;	//0xC4F46E94
	UINT32                                                 reserved6691;	//0xC4F46E98
	UINT32                                                 reserved6692;	//0xC4F46E9C
	UINT32                                                 reserved6693;	//0xC4F46EA0
	UINT32                                                 reserved6694;	//0xC4F46EA4
	UINT32                                                 reserved6695;	//0xC4F46EA8
	UINT32                                                 reserved6696;	//0xC4F46EAC
	UINT32                                                 reserved6697;	//0xC4F46EB0
	UINT32                                                 reserved6698;	//0xC4F46EB4
	UINT32                                                 reserved6699;	//0xC4F46EB8
	UINT32                                                 reserved6700;	//0xC4F46EBC
	UINT32                                                 reserved6701;	//0xC4F46EC0
	UINT32                                                 reserved6702;	//0xC4F46EC4
	UINT32                                                 reserved6703;	//0xC4F46EC8
	UINT32                                                 reserved6704;	//0xC4F46ECC
	UINT32                                                 reserved6705;	//0xC4F46ED0
	UINT32                                                 reserved6706;	//0xC4F46ED4
	UINT32                                                 reserved6707;	//0xC4F46ED8
	UINT32                                                 reserved6708;	//0xC4F46EDC
	UINT32                                                 reserved6709;	//0xC4F46EE0
	UINT32                                                 reserved6710;	//0xC4F46EE4
	UINT32                                                 reserved6711;	//0xC4F46EE8
	UINT32                                                 reserved6712;	//0xC4F46EEC
	UINT32                                                 reserved6713;	//0xC4F46EF0
	UINT32                                                 reserved6714;	//0xC4F46EF4
	UINT32                                                 reserved6715;	//0xC4F46EF8
	UINT32                                                 reserved6716;	//0xC4F46EFC
	UINT32                                                 reserved6717;	//0xC4F46F00
	UINT32                                                 reserved6718;	//0xC4F46F04
	UINT32                                                 reserved6719;	//0xC4F46F08
	UINT32                                                 reserved6720;	//0xC4F46F0C
	UINT32                                                 reserved6721;	//0xC4F46F10
	UINT32                                                 reserved6722;	//0xC4F46F14
	UINT32                                                 reserved6723;	//0xC4F46F18
	UINT32                                                 reserved6724;	//0xC4F46F1C
	UINT32                                                 reserved6725;	//0xC4F46F20
	UINT32                                                 reserved6726;	//0xC4F46F24
	UINT32                                                 reserved6727;	//0xC4F46F28
	UINT32                                                 reserved6728;	//0xC4F46F2C
	UINT32                                                 reserved6729;	//0xC4F46F30
	UINT32                                                 reserved6730;	//0xC4F46F34
	UINT32                                                 reserved6731;	//0xC4F46F38
	UINT32                                                 reserved6732;	//0xC4F46F3C
	UINT32                                                 reserved6733;	//0xC4F46F40
	UINT32                                                 reserved6734;	//0xC4F46F44
	UINT32                                                 reserved6735;	//0xC4F46F48
	UINT32                                                 reserved6736;	//0xC4F46F4C
	UINT32                                                 reserved6737;	//0xC4F46F50
	UINT32                                                 reserved6738;	//0xC4F46F54
	UINT32                                                 reserved6739;	//0xC4F46F58
	UINT32                                                 reserved6740;	//0xC4F46F5C
	UINT32                                                 reserved6741;	//0xC4F46F60
	UINT32                                                 reserved6742;	//0xC4F46F64
	UINT32                                                 reserved6743;	//0xC4F46F68
	UINT32                                                 reserved6744;	//0xC4F46F6C
	UINT32                                                 reserved6745;	//0xC4F46F70
	UINT32                                                 reserved6746;	//0xC4F46F74
	UINT32                                                 reserved6747;	//0xC4F46F78
	UINT32                                                 reserved6748;	//0xC4F46F7C
	UINT32                                                 reserved6749;	//0xC4F46F80
	UINT32                                                 reserved6750;	//0xC4F46F84
	UINT32                                                 reserved6751;	//0xC4F46F88
	UINT32                                                 reserved6752;	//0xC4F46F8C
	UINT32                                                 reserved6753;	//0xC4F46F90
	UINT32                                                 reserved6754;	//0xC4F46F94
	UINT32                                                 reserved6755;	//0xC4F46F98
	UINT32                                                 reserved6756;	//0xC4F46F9C
	UINT32                                                 reserved6757;	//0xC4F46FA0
	UINT32                                                 reserved6758;	//0xC4F46FA4
	UINT32                                                 reserved6759;	//0xC4F46FA8
	UINT32                                                 reserved6760;	//0xC4F46FAC
	UINT32                                                 reserved6761;	//0xC4F46FB0
	UINT32                                                 reserved6762;	//0xC4F46FB4
	UINT32                                                 reserved6763;	//0xC4F46FB8
	UINT32                                                 reserved6764;	//0xC4F46FBC
	UINT32                                                 reserved6765;	//0xC4F46FC0
	UINT32                                                 reserved6766;	//0xC4F46FC4
	UINT32                                                 reserved6767;	//0xC4F46FC8
	UINT32                                                 reserved6768;	//0xC4F46FCC
	UINT32                                                 reserved6769;	//0xC4F46FD0
	UINT32                                                 reserved6770;	//0xC4F46FD4
	UINT32                                                 reserved6771;	//0xC4F46FD8
	UINT32                                                 reserved6772;	//0xC4F46FDC
	REG_DDRC_M0_REY_SPARE_T                                   rey_spare;	//0xC4F46FE0
}REG_DDRC_M0_T;

extern volatile REG_DDRC_M0_T*                     gpREG_DDRC_M0;
  
#endif
