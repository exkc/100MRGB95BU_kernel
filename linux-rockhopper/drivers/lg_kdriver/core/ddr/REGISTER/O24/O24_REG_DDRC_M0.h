#ifndef _REG_DDRC_M0_h
#define _REG_DDRC_M0_h
//Header File for DDRC_M0 in \O24\O24_DRAM_M0_Register_Manual.xls

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
	struct {						//0xC4D00000 RW
	UINT32 reg_dram_ch                      :1;	//0 //Dram channel width (0: x16, 1: x32)
	UINT32 resvd0                           :3;  
	UINT32 reg_byte_mode                    :1;	//4 //Byte mode enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M0_DRAM_CONF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00004 RW
	UINT32 reg_op_mode                      :1;	//0 //operation mode selection (0: normal, 1: debug)
	UINT32 reg_bist_en                      :1;	//1 //bist mode enable
	UINT32 resvd                            :30; 
	};
}REG_DDRC_M0_MODE_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00008 RW
	UINT32 reg_base_period                  :10;	//9:0	//base period for counter (counter resolution) - ex: 1us
	UINT32 resvd                            :22; 
	};
}REG_DDRC_M0_BASE_PERIOD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00100 RW
	UINT32 reg_alp_en                       :2;	//1:0	//low power mode enable 	 ([0]: power down, [1]: self refresh)
	UINT32 resvd0                           :2;  
	UINT32 reg_pd_thr                       :4;	//7:4	//power down threshold - waiting for 4*(x+1) cycles
	UINT32 reg_sr_thr                       :4;	//11:8	//self refresh threshold - waiting for tREFI*(x+1) cycles
	UINT32 resvd1                           :20; 
	};
}REG_DDRC_M0_ALP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00104 RW
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
	struct {						//0xC4D00108 RO
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
	struct {						//0xC4D00200 RW
	UINT32 reg_pm_en                        :1;	//0 //performance monitor enable
	UINT32 resvd0                           :3;  
	UINT32 reg_emg_period                   :10;	//13:4	//emergency dfs monitoring period (ex: 100us) - (reg_base_period+1 (ex:1us)) * (reg_emg_period+1) : (final default value 0x63 --> 100ms)
	UINT32 resvd1                           :18; 
	};
}REG_DDRC_M0_PERFMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00204 RO
	UINT32 reg_emg_max                      :12;	//11:0	//max value among dfs_emg_totals during debug monitoring period : emg_total >> cut_width	(max of served bytes during emg period in debug monitoring period can be calculated by reg_emg_max * 16 << cut_width)	- cut_width : reg_emg_period[9]? 10 : 	                  reg_emg_period[8]?  9 :	                   reg_emg_period[7]?  8 :   	                   reg_emg_period[6]?  7 :	                   reg_emg_period[5]?  6 :	                   reg_emg_period[4]?  5 :   	                   reg_emg_period[3]?  4 :	                   reg_emg_period[2]?  3 :	                   reg_emg_period[1]?  2 :   	                      reg_emg_period[0]?  1 : 0
	UINT32 resvd                            :20; 
	};
}REG_DDRC_M0_PERFMON_EMG_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00210 RO
	UINT32 reg_pm_w0                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_W0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00214 RO
	UINT32 reg_pm_w1                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_W1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00218 RO
	UINT32 reg_pm_w2                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_W2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0021C RO
	UINT32 reg_pm_w3                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_W3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00220 RO
	UINT32 reg_pm_r0                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_R0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00224 RO
	UINT32 reg_pm_r1                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_R1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00228 RO
	UINT32 reg_pm_r2                        :32;	//31:0	//mornitoring result for write port 0  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_R2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0022C RO
	UINT32 reg_pm_r3                        :32;	//31:0	//mornitoring result for write port 2  (x * 16 >> cut_width)
	};
}REG_DDRC_M0_PERFMON_R3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00230 
	UINT32 reg_max_lat_en                   :1;	//0 //max latency monitor enable
	UINT32 resvd0                           :7;  
	UINT32 reg_max_lat                      :8;	//15:8	//max latency for read request in unified Q (it is reset at every period)
	UINT32 resvd1                           :16; 
	};
}REG_DDRC_M0_LATMON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00300 RW
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
	struct {						//0xC4D00304 RO
	UINT32 reg_dfs_done                     :1;	//0 //dfs done
	UINT32 resvd0                           :3;  
	UINT32 reg_dfs_type                     :2;	//5:4	//dfs type: DFS0, DFS1, DFS2 (emergency DFS exit)
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M0_DFS_RESULT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00400 RW
	UINT32 reg_dram_density                 :3;	//2:0	//dram density configuration per channel 	(enum {2Gb, 3Gb, 4Gb, 6Gb, 8Gb, 12Gb, 16Gb})
	UINT32 reg_addr_scrb_en                 :1;	//3 //address map: bank scramble enable
	UINT32 reg_addr_sel_bq                  :4;	//7:4	//address map: bank position	(enum {BG4, BG5, BG6, BG7, BP4, BP5, BP6, BP7, BP8, BP9, BP11, BP12})
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_ADDR_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00404 RW
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
	struct {						//0xC4D00408 
	UINT32 reg_rc4_enb                      :1;	//0 //data encryption enable
	UINT32 resvd0                           :7;  
	UINT32 reg_rc4_key_in_4                 :8;	//15:8	//key seed for data encryption (39:32 bits)
	UINT32 reg_rc4_state                    :2;	//17:16	//rc4 key generation status
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M0_DATA_ENC0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0040C RW
	UINT32 reg_rc4_key_in_3_0               :32;	//31:0	//key seed for data encryption (31:0 bits)
	};
}REG_DDRC_M0_DATA_ENC1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D00500 RW
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
	struct {						//0xC4D00504 RW
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
	struct {						//0xC4D01000 RW
	UINT32 reg_awready_en                   :4;	//3:0	//enable awready for each port
	UINT32 reg_pre_wready_en                :1;	//4 //enable pre-wready
	UINT32 resvd0                           :3;  
	UINT32 reg_arready_en                   :4;	//11:8	//enable arready for each port
	UINT32 resvd1                           :20; 
	};
}REG_DDRC_M0_FIFO_RDY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D01004 RO
	UINT32 reg_aw_all_empty                 :4;	//3:0	//monitor whether all aw valid entries is empty for each port
	UINT32 reg_ar_all_empty                 :4;	//7:4	//monitor whether all aw valid entries is empty for each port
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_FIFO_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D01008 RW
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
	struct {						//0xC4D01010 RW
	UINT32 reg_w_c_lim_en                   :4;	//3:0	//enable cmd cnt limiter
	UINT32 reg_w_d_lim_en                   :4;	//7:4	//enable data len limiter
	UINT32 reg_r_c_lim_en                   :4;	//11:8	//enable cmd cnt limiter
	UINT32 reg_r_d_lim_en                   :4;	//15:12	//enable data len limiter
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LIMITER_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D01014 RW
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
	struct {						//0xC4D01018 RW
	UINT32 reg_w_d_lim_thr0                 :8;	//7:0	//threshold value for data len limiter for port 0
	UINT32 reg_w_d_lim_thr1                 :8;	//15:8	//threshold value for data len limiter for port 1
	UINT32 reg_w_d_lim_thr2                 :8;	//23:16	//threshold value for data len limiter for port 2
	UINT32 reg_w_d_lim_thr3                 :8;	//31:24	//threshold value for data len limiter for port 3
	};
}REG_DDRC_M0_LIMITER_W_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D01024 RW
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
	struct {						//0xC4D01028 RW
	UINT32 reg_r_d_lim_thr0                 :8;	//7:0	//threshold value for data len limiter for port 0
	UINT32 reg_r_d_lim_thr1                 :8;	//15:8	//threshold value for data len limiter for port 1
	UINT32 reg_r_d_lim_thr2                 :8;	//23:16	//threshold value for data len limiter for port 2
	UINT32 reg_r_d_lim_thr3                 :8;	//31:24	//threshold value for data len limiter for port 3
	};
}REG_DDRC_M0_LIMITER_R_THR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D01100 RW
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
	struct {						//0xC4D01104 RW
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
	struct {						//0xC4D01108 RW
	UINT32 reg_wfo_prt_sol_max_en           :1;	//0 //write fifo prt sol max enable
	UINT32 resvd0                           :3;  
	UINT32 reg_wfo_prt_sol_max_thr          :4;	//7:4	//write fifo prt sol max threshold
	UINT32 reg_wfo_prt_ep_period            :10;	//17:8	//a period of epoch counter for wfifo prt
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M0_FIFO_MUX_WR_PRT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0110C RW
	UINT32 reg_rfo_prt_sol_max_en           :1;	//0 //read fifo prt sol max enable
	UINT32 resvd0                           :3;  
	UINT32 reg_rfo_prt_sol_max_thr          :4;	//7:4	//read fifo prt sol max threshold
	UINT32 reg_rfo_prt_ep_period            :10;	//17:8	//a period of epoch counter for rfifo prt
	UINT32 resvd1                           :14; 
	};
}REG_DDRC_M0_FIFO_MUX_RD_PRT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D01110 RW
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
	struct {						//0xC4D02000 RW
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
	struct {						//0xC4D02004 RW
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
	struct {						//0xC4D02008 RW
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
	struct {						//0xC4D0200C RW
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
	struct {						//0xC4D03000 RW
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
	struct {						//0xC4D03004 RW
	UINT32 lpd4_reg_init_mrw_ma_fsp0        :32;	//31:0	//Each of bit indicates the MR address for MRW operation for FSP0 during initialization.	[0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_INIT_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03008 RW
	UINT32 lpd4_reg_init_mrw_ma_fsp1        :32;	//31:0	//Each of bit indicates the MR address for MRW operation for FSP1 during initialization.	[0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_INIT_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0300C RW
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
	struct {						//0xC4D03010 
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
	struct {						//0xC4D03014 RW
	UINT32 lpd4_reg_dir_mrw_ma              :32;	//31:0	//Each of bit indicates the MR address for MRW operation for direct control interface	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03018 RW
	UINT32 lpd4_reg_dir_mrr_ma              :32;	//31:0	//Each of bit indicates the MR address for MRR operation for direct control interface	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0301C RW
	UINT32 lpd4_reg_dir_sr_mrw_ma           :32;	//31:0	//Each of bit indicates the MR address for MRW operation for direct control interface during self-refresh	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03020 RW
	UINT32 lpd4_reg_dir_sr_mrr_ma           :32;	//31:0	//Each of bit indicates the MR address for MRR operation for direct control interface during self-refresh	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03024 RW
	UINT32 lpd4_reg_dfs_mrw_ma              :32;	//31:0	//Each of bit indicates the MR address for MRW operation for DFS	- [0]: MR0, [1]: MR1, ・, [26]: MR31, [27]: MR32, [28]: MR39, [29] : MR40, [30] : MR13_2nd, [31]: MR13_3rd
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_DFS_MRW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03028 
	UINT32 lpd4_reg_dfi_ctrlupd_req         :1;	//0 //DFI control update request (This will be cleared when lpd4_mf_reg_dfi_ctrlupd_ack is asserted high)
	UINT32 lpd4_mf_reg_dfi_ctrlupd_ack      :1;	//1 //Completion of DFI control update request
	UINT32 resvd                            :30; 
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_CTRLUPD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0302C RW
	UINT32 lpd4_reg_mpc_fifo_en             :1;	//0 //Periodic MPC WR/RD FIFO command enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_mpc_fifo_cmd_cnt        :3;	//6:4	//Number of MPC FIFO commands issued at one time
	UINT32 resvd1                           :25; 
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03030 RW
	UINT32 lpd4_reg_mpc_fifo_period         :32;	//31:0	//Period of MPC WR/RD FIFO command
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03034 RW
	UINT32 lpd4_reg_mpc_fifo_data0          :32;	//31:0	//Data pattern of MPC WR FIFO Command
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03038 RW
	UINT32 lpd4_reg_mpc_fifo_data1          :32;	//31:0	//Data pattern of MPC WR FIFO Command
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0303C RW
	UINT32 lpd4_reg_mpc_fifo_dmi0           :4;	//3:0	//DMI data pattern of MPC WR FIFO Command
	UINT32 lpd4_reg_mpc_fifo_dmi1           :4;	//7:4	//DMI data pattern of MPC WR FIFO Command
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03050 RW
	UINT32 lpd4_reg_mrr_mr4_tuf_sel         :2;	//1:0	//Temperature Update Flag (TUF) in MR4 selection between two-channel (x32)	- 2'b00 : CH0 or CH1	- 2'b01 : CH0 and CH1	- 2'b10 : CH0	- 2'b11 : CH1
	UINT32 resvd0                           :2;  
	UINT32 lpd4_reg_mrr_mr4_rate_sel        :2;	//5:4	//Refresh rate in MR4 selection between two-channel (x32)	- 2'b00 : Bigger value between CH0 and CH1	- 2'b01 : Smaller value between CH0 and CH1	- 2'b10 : CH0	- 2'b11 : CH1
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M0_LPD4_MR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03054 RW
	UINT32 lpd4_reg_mrr_mr4_tuf_byte_sel    :2;	//1:0	//Temperature Update Flag (TUF) in MR4 selection between two-byte (x16) in byte-mode	- 2'b00 : Byte0 or Byte1	- 2'b01 : Byte0 and Byte1	- 2'b10 : Byte0	- 2'b11 : Byte1
	UINT32 resvd0                           :2;  
	UINT32 lpd4_reg_mrr_mr4_rate_byte_sel   :2;	//5:4	//Refresh rate in MR4 selection between two-byte (x16) in byte-mode	- 2'b00 : Bigger value between Byte0 and Byte1	- 2'b01 : Smaller value between Byte0 and Byte1	- 2'b10 : Byte0	- 2'b11 : Byte1
	UINT32 resvd1                           :26; 
	};
}REG_DDRC_M0_LPD4_MR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03058 RW
	UINT32 lpd4_reg_mrr_byte_sel            :1;	//0 //MR selection between two-byte (x16) in byte-mode	- 1'b0 : Byte0	- 1'b1 : Byte1
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_LPD4_MR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03060 RW
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
	struct {						//0xC4D03070 RW
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
	struct {						//0xC4D03080 RW
	UINT32 lpd4_reg_bank_lock_wait          :8;	//7:0	//Configurable locking time for BANK FSM operation
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_BANK_FSM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D030A0 RW
	UINT32 lpd4_reg_tBL                     :8;	//7:0	//Additional offset of AC timing parameters when applying BL32
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_BANK_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D030C0 RW
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
	struct {						//0xC4D03100 RW
	UINT32 lpd4_reg_mr1_ch0_dfs0            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs0            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs0            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs0            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS0_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03104 RW
	UINT32 lpd4_reg_mr9_ch0_dfs0            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs0           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs0           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03108 RW
	UINT32 lpd4_reg_mr12_ch0_dfs0           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs0           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS0_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0310C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs0       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs0       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs0       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03110 RW
	UINT32 lpd4_reg_mr15_ch0_dfs0           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs0           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs0           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs0           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS0_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03114 RW
	UINT32 lpd4_reg_mr21_ch0_dfs0           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs0           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs0           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs0           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS0_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03118 RW
	UINT32 lpd4_reg_mr31_ch0_dfs0           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs0           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs0           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs0           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS0_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03120 RW
	UINT32 lpd4_reg_mr1_ch1_dfs0            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs0            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs0            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs0            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS0_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03124 RW
	UINT32 lpd4_reg_mr9_ch1_dfs0            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs0           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs0           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03128 RW
	UINT32 lpd4_reg_mr12_ch1_dfs0           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs0           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS0_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0312C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs0       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs0       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs0       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03130 RW
	UINT32 lpd4_reg_mr15_ch1_dfs0           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs0           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs0           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs0           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS0_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03134 RW
	UINT32 lpd4_reg_mr21_ch1_dfs0           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs0           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs0           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs0           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS0_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03138 RW
	UINT32 lpd4_reg_mr31_ch1_dfs0           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs0           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs0           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs0           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS0_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03140 RW
	UINT32 lpd4_reg_period_zq_req_dfs0      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03144 RW
	UINT32 lpd4_reg_tINIT1_dfs0             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs0             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03148 RW
	UINT32 lpd4_reg_tINIT5_dfs0             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs0             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs0             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0314C RW
	UINT32 lpd4_reg_tXP_dfs0                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs0             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs0            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs0            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03150 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs0           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03154 RW
	UINT32 lpd4_reg_tXSR_dfs0               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs0         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03160 RW
	UINT32 lpd4_reg_tREFI_dfs0              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs0           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03164 RW
	UINT32 lpd4_reg_tMRR4I_dfs0             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03168 RW
	UINT32 lpd4_reg_tRRD_dfs0               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs0           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs0           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs0               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0316C RW
	UINT32 lpd4_reg_tRAS_dfs0               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs0              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs0              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs0               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03170 RW
	UINT32 lpd4_reg_tRAP_dfs0               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs0        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs0    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs0    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03174 RW
	UINT32 lpd4_reg_tRCD_derate_dfs0        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs0        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs0       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs0       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03178 RW
	UINT32 lpd4_reg_tWAP_derate_dfs0        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs0        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03190 RW
	UINT32 lpd4_reg_ref_ab_en_dfs0          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs0          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M0_LPD4_DFS0_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031A0 RW
	UINT32 lpd4_reg_odt_on_dfs0             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031A4 RW
	UINT32 lpd4_reg_tCCD_dfs0               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs0             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs0               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs0               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031A8 RW
	UINT32 lpd4_reg_tW2PD_dfs0              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs0             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs0           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs0         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs0        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs0               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs0              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs0             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs0           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs0               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031B4 RW
	UINT32 lpd4_reg_tRFCab_dfs0             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs0             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031B8 RW
	UINT32 lpd4_reg_tMRW_dfs0               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs0           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs0       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs0      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031BC RW
	UINT32 lpd4_reg_tFC_dfs0                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs0           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs0               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs0              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs0            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs0             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs0             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs0           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D031E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs0             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs0            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs0             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS0_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03200 RW
	UINT32 lpd4_reg_mr1_ch0_dfs1            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs1            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs1            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs1            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS1_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03204 RW
	UINT32 lpd4_reg_mr9_ch0_dfs1            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs1           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs1           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03208 RW
	UINT32 lpd4_reg_mr12_ch0_dfs1           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs1           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS1_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0320C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs1       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs1       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs1       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03210 RW
	UINT32 lpd4_reg_mr15_ch0_dfs1           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs1           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs1           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs1           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS1_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03214 RW
	UINT32 lpd4_reg_mr21_ch0_dfs1           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs1           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs1           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs1           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS1_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03218 RW
	UINT32 lpd4_reg_mr31_ch0_dfs1           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs1           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs1           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs1           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS1_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03220 RW
	UINT32 lpd4_reg_mr1_ch1_dfs1            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs1            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs1            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs1            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS1_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03224 RW
	UINT32 lpd4_reg_mr9_ch1_dfs1            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs1           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs1           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03228 RW
	UINT32 lpd4_reg_mr12_ch1_dfs1           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs1           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS1_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0322C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs1       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs1       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs1       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03230 RW
	UINT32 lpd4_reg_mr15_ch1_dfs1           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs1           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs1           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs1           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS1_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03234 RW
	UINT32 lpd4_reg_mr21_ch1_dfs1           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs1           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs1           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs1           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS1_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03238 RW
	UINT32 lpd4_reg_mr31_ch1_dfs1           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs1           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs1           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs1           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS1_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03240 RW
	UINT32 lpd4_reg_period_zq_req_dfs1      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03244 RW
	UINT32 lpd4_reg_tINIT1_dfs1             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs1             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03248 RW
	UINT32 lpd4_reg_tINIT5_dfs1             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs1             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs1             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0324C RW
	UINT32 lpd4_reg_tXP_dfs1                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs1             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs1            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs1            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03250 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs1           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03254 RW
	UINT32 lpd4_reg_tXSR_dfs1               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs1         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03260 RW
	UINT32 lpd4_reg_tREFI_dfs1              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs1           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03264 RW
	UINT32 lpd4_reg_tMRR4I_dfs1             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03268 RW
	UINT32 lpd4_reg_tRRD_dfs1               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs1           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs1           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs1               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0326C RW
	UINT32 lpd4_reg_tRAS_dfs1               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs1              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs1              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs1               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03270 RW
	UINT32 lpd4_reg_tRAP_dfs1               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs1        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs1    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs1    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03274 RW
	UINT32 lpd4_reg_tRCD_derate_dfs1        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs1        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs1       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs1       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03278 RW
	UINT32 lpd4_reg_tWAP_derate_dfs1        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs1        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03290 RW
	UINT32 lpd4_reg_ref_ab_en_dfs1          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs1          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M0_LPD4_DFS1_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032A0 RW
	UINT32 lpd4_reg_odt_on_dfs1             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032A4 RW
	UINT32 lpd4_reg_tCCD_dfs1               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs1             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs1               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs1               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032A8 RW
	UINT32 lpd4_reg_tW2PD_dfs1              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs1             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs1           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs1         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs1        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs1               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs1              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs1             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs1           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs1               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032B4 RW
	UINT32 lpd4_reg_tRFCab_dfs1             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs1             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032B8 RW
	UINT32 lpd4_reg_tMRW_dfs1               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs1           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs1       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs1      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032BC RW
	UINT32 lpd4_reg_tFC_dfs1                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs1           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs1               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs1              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs1            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs1             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs1             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs1           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D032E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs1             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs1            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs1             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS1_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03300 RW
	UINT32 lpd4_reg_mr1_ch0_dfs2            :8;	//7:0	//[DFS] MR1 write data for CH0
	UINT32 lpd4_reg_mr2_ch0_dfs2            :8;	//15:8	//[DFS] MR2 write data for CH0
	UINT32 lpd4_reg_mr3_ch0_dfs2            :8;	//23:16	//[DFS] MR3 write data for CH0
	UINT32 lpd4_reg_mr4_ch0_dfs2            :8;	//31:24	//[DFS] MR4 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS2_MR_0_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03304 RW
	UINT32 lpd4_reg_mr9_ch0_dfs2            :8;	//7:0	//[DFS] MR9 write data for CH0
	UINT32 lpd4_reg_mr10_ch0_dfs2           :8;	//15:8	//[DFS] MR10 write data for CH0
	UINT32 lpd4_reg_mr11_ch0_dfs2           :8;	//23:16	//[DFS] MR11 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_MR_1_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03308 RW
	UINT32 lpd4_reg_mr12_ch0_dfs2           :8;	//7:0	//[DFS] MR12 write data for CH0
	UINT32 lpd4_reg_mr14_ch0_dfs2           :8;	//15:8	//[DFS] MR14 write data for CH0
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS2_MR_2_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0330C RW
	UINT32 lpd4_reg_mr13_1st_ch0_dfs2       :8;	//7:0	//[DFS] 1ST MR13 write data for CH0
	UINT32 lpd4_reg_mr13_2nd_ch0_dfs2       :8;	//15:8	//[DFS] 2ND MR13 write data for CH0
	UINT32 lpd4_reg_mr13_3rd_ch0_dfs2       :8;	//23:16	//[DFS] 3RD MR13 write data for CH0
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_MR_3_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03310 RW
	UINT32 lpd4_reg_mr15_ch0_dfs2           :8;	//7:0	//[DFS] MR15 write data for CH0
	UINT32 lpd4_reg_mr16_ch0_dfs2           :8;	//15:8	//[DFS] MR16 write data for CH0
	UINT32 lpd4_reg_mr17_ch0_dfs2           :8;	//23:16	//[DFS] MR17 write data for CH0
	UINT32 lpd4_reg_mr20_ch0_dfs2           :8;	//31:24	//[DFS] MR20 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS2_MR_4_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03314 RW
	UINT32 lpd4_reg_mr21_ch0_dfs2           :8;	//7:0	//[DFS] MR21 write data for CH0
	UINT32 lpd4_reg_mr22_ch0_dfs2           :8;	//15:8	//[DFS] MR22 write data for CH0
	UINT32 lpd4_reg_mr23_ch0_dfs2           :8;	//23:16	//[DFS] MR23 write data for CH0
	UINT32 lpd4_reg_mr24_ch0_dfs2           :8;	//31:24	//[DFS] MR24 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS2_MR_5_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03318 RW
	UINT32 lpd4_reg_mr31_ch0_dfs2           :8;	//7:0	//[DFS] MR31 write data for CH0
	UINT32 lpd4_reg_mr32_ch0_dfs2           :8;	//15:8	//[DFS] MR32 write data for CH0
	UINT32 lpd4_reg_mr39_ch0_dfs2           :8;	//23:16	//[DFS] MR39 write data for CH0
	UINT32 lpd4_reg_mr40_ch0_dfs2           :8;	//31:24	//[DFS] MR40 write data for CH0
	};
}REG_DDRC_M0_LPD4_DFS2_MR_6_CH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03320 RW
	UINT32 lpd4_reg_mr1_ch1_dfs2            :8;	//7:0	//[DFS] MR1 write data for CH1
	UINT32 lpd4_reg_mr2_ch1_dfs2            :8;	//15:8	//[DFS] MR2 write data for CH1
	UINT32 lpd4_reg_mr3_ch1_dfs2            :8;	//23:16	//[DFS] MR3 write data for CH1
	UINT32 lpd4_reg_mr4_ch1_dfs2            :8;	//31:24	//[DFS] MR4 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS2_MR_0_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03324 RW
	UINT32 lpd4_reg_mr9_ch1_dfs2            :8;	//7:0	//[DFS] MR9 write data for CH1
	UINT32 lpd4_reg_mr10_ch1_dfs2           :8;	//15:8	//[DFS] MR10 write data for CH1
	UINT32 lpd4_reg_mr11_ch1_dfs2           :8;	//23:16	//[DFS] MR11 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_MR_1_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03328 RW
	UINT32 lpd4_reg_mr12_ch1_dfs2           :8;	//7:0	//[DFS] MR12 write data for CH1
	UINT32 lpd4_reg_mr14_ch1_dfs2           :8;	//15:8	//[DFS] MR14 write data for CH1
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS2_MR_2_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0332C RW
	UINT32 lpd4_reg_mr13_1st_ch1_dfs2       :8;	//7:0	//[DFS] 1ST MR13 write data for CH1
	UINT32 lpd4_reg_mr13_2nd_ch1_dfs2       :8;	//15:8	//[DFS] 2ND MR13 write data for CH1
	UINT32 lpd4_reg_mr13_3rd_ch1_dfs2       :8;	//23:16	//[DFS] 3RD MR13 write data for CH1
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_MR_3_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03330 RW
	UINT32 lpd4_reg_mr15_ch1_dfs2           :8;	//7:0	//[DFS] MR15 write data for CH1
	UINT32 lpd4_reg_mr16_ch1_dfs2           :8;	//15:8	//[DFS] MR16 write data for CH1
	UINT32 lpd4_reg_mr17_ch1_dfs2           :8;	//23:16	//[DFS] MR17 write data for CH1
	UINT32 lpd4_reg_mr20_ch1_dfs2           :8;	//31:24	//[DFS] MR20 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS2_MR_4_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03334 RW
	UINT32 lpd4_reg_mr21_ch1_dfs2           :8;	//7:0	//[DFS] MR21 write data for CH1
	UINT32 lpd4_reg_mr22_ch1_dfs2           :8;	//15:8	//[DFS] MR22 write data for CH1
	UINT32 lpd4_reg_mr23_ch1_dfs2           :8;	//23:16	//[DFS] MR23 write data for CH1
	UINT32 lpd4_reg_mr24_ch1_dfs2           :8;	//31:24	//[DFS] MR24 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS2_MR_5_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03338 RW
	UINT32 lpd4_reg_mr31_ch1_dfs2           :8;	//7:0	//[DFS] MR31 write data for CH1
	UINT32 lpd4_reg_mr32_ch1_dfs2           :8;	//15:8	//[DFS] MR32 write data for CH1
	UINT32 lpd4_reg_mr39_ch1_dfs2           :8;	//23:16	//[DFS] MR39 write data for CH1
	UINT32 lpd4_reg_mr40_ch1_dfs2           :8;	//31:24	//[DFS] MR40 write data for CH1
	};
}REG_DDRC_M0_LPD4_DFS2_MR_6_CH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03340 RW
	UINT32 lpd4_reg_period_zq_req_dfs2      :32;	//31:0	//[DFS] Periodic ZQ calibration interval
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03344 RW
	UINT32 lpd4_reg_tINIT1_dfs2             :16;	//15:0	//[DFS] Minimum RESET_n LOW time after completion of voltage ramp
	UINT32 lpd4_reg_tINIT3_dfs2             :16;	//31:16	//[DFS] Minimum CKE LOW time after RESET_n HIGH
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03348 RW
	UINT32 lpd4_reg_tINIT5_dfs2             :8;	//7:0	//[DFS] Minimum idle time before first MRW/MRR command
	UINT32 lpd4_reg_tZQCAL_dfs2             :16;	//23:8	//[DFS] ZQ calibration time
	UINT32 lpd4_reg_tZQLAT_dfs2             :8;	//31:24	//[DFS] ZQ calibration latch time
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0334C RW
	UINT32 lpd4_reg_tXP_dfs2                :8;	//7:0	//[DFS] Exit power-down to next valid command delay
	UINT32 lpd4_reg_tESCKE_dfs2             :8;	//15:8	//[DFS] Delay from SRE command to CKE input LOW
	UINT32 lpd4_reg_tCKELCK_dfs2            :8;	//23:16	//[DFS] Valid clock requirement after CKE input LOW
	UINT32 lpd4_reg_tCKCKEH_dfs2            :8;	//31:24	//[DFS] Valid clock requirement before CKE input HIGH
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03350 RW
	UINT32 lpd4_reg_tCKEHCMD_dfs2           :8;	//7:0	//[DFS] Exit self-refresh power-down to next valid command delay
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03354 RW
	UINT32 lpd4_reg_tXSR_dfs2               :12;	//11:0	//[DFS] Exit self-refresh to valid commands
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tXSR_ABORT_dfs2         :12;	//27:16	//[DFS] Exit self-refresh to valid commands when enabling self-refresh abort feature
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03360 RW
	UINT32 lpd4_reg_tREFI_dfs2              :16;	//15:0	//[DFS] Average refresh interval
	UINT32 lpd4_reg_tpbR2pbR_dfs2           :12;	//27:16	//[DFS] Per-bank refresh to per-bank refresh for different bank
	UINT32 resvd                            :4;  
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03364 RW
	UINT32 lpd4_reg_tMRR4I_dfs2             :32;	//31:0	//[DFS] Periodic MRR interval for reading refresh rate
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03368 RW
	UINT32 lpd4_reg_tRRD_dfs2               :8;	//7:0	//[DFS] Active bank A to active bank B
	UINT32 lpd4_reg_tRRD_A2R_dfs2           :8;	//15:8	//[DFS] Active bank A to per-bank refresh bank B
	UINT32 lpd4_reg_tRRD_R2A_dfs2           :8;	//23:16	//[DFS] Per-bank refresh bank A to active bank B
	UINT32 lpd4_reg_tRCD_dfs2               :8;	//31:24	//[DFS] RAS-to-CAS delay
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0336C RW
	UINT32 lpd4_reg_tRAS_dfs2               :8;	//7:0	//[DFS] Row active time
	UINT32 lpd4_reg_tRPab_dfs2              :8;	//15:8	//[DFS] Row all-bank precharge time
	UINT32 lpd4_reg_tRPpb_dfs2              :8;	//23:16	//[DFS] Row per-bank precharge time
	UINT32 lpd4_reg_tWAP_dfs2               :8;	//31:24	//[DFS] Write auto-precharge time
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03370 RW
	UINT32 lpd4_reg_tRAP_dfs2               :8;	//7:0	//[DFS] Read auto-precharge time
	UINT32 lpd4_reg_tRRD_derate_dfs2        :8;	//15:8	//[DFS] Active bank A to active bank B (derated)
	UINT32 lpd4_reg_tRRD_A2R_derate_dfs2    :8;	//23:16	//[DFS] Active bank A to per-bank refresh bank B (derated)
	UINT32 lpd4_reg_tRRD_R2A_derate_dfs2    :8;	//31:24	//[DFS] Per-bank refresh bank A to active bank B (derated)
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03374 RW
	UINT32 lpd4_reg_tRCD_derate_dfs2        :8;	//7:0	//[DFS] RAS-to-CAS delay (derated)
	UINT32 lpd4_reg_tRAS_derate_dfs2        :8;	//15:8	//[DFS] Row active time (derated)
	UINT32 lpd4_reg_tRPab_derate_dfs2       :8;	//23:16	//[DFS] Row all-bank precharge time (derated)
	UINT32 lpd4_reg_tRPpb_derate_dfs2       :8;	//31:24	//[DFS] Row per-bank precharge time (derated)
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03378 RW
	UINT32 lpd4_reg_tWAP_derate_dfs2        :8;	//7:0	//[DFS] Write auto-precharge time (derated)
	UINT32 lpd4_reg_tRAP_derate_dfs2        :8;	//15:8	//[DFS] Read auto-precharge time (derated)
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D03390 RW
	UINT32 lpd4_reg_ref_ab_en_dfs2          :1;	//0 //[DFS] All-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd0                           :3;  
	UINT32 lpd4_reg_ref_pb_en_dfs2          :1;	//4 //[DFS] Per-bank refresh scheme enable	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd1                           :27; 
	};
}REG_DDRC_M0_LPD4_DFS2_REF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033A0 RW
	UINT32 lpd4_reg_odt_on_dfs2             :1;	//0 //[DFS] AC timing control enable for read operation according to ODT	- 1'b0 : Disable	- 1'b1 : Enable
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033A4 RW
	UINT32 lpd4_reg_tCCD_dfs2               :8;	//7:0	//[DFS] CAS-to-CAS delay
	UINT32 lpd4_reg_tCCDMW_dfs2             :8;	//15:8	//[DFS] CAS-to-CAS delay (for masked write)
	UINT32 lpd4_reg_tW2R_dfs2               :8;	//23:16	//[DFS] Write to read time
	UINT32 lpd4_reg_tW2P_dfs2               :8;	//31:24	//[DFS] Write to precharge time
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033A8 RW
	UINT32 lpd4_reg_tW2PD_dfs2              :8;	//7:0	//[DFS] Write to power-down time
	UINT32 lpd4_reg_tW2MRW_dfs2             :8;	//15:8	//[DFS] Write to MRW time
	UINT32 lpd4_reg_tWAP2MRW_dfs2           :8;	//23:16	//[DFS] Write auto-precharge to MRW time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033AC RW
	UINT32 lpd4_reg_tR2W_ODTON_dfs2         :8;	//7:0	//[DFS] Read to write time (when ODT on)
	UINT32 lpd4_reg_tR2W_ODTOFF_dfs2        :8;	//15:8	//[DFS] Read to write time (when ODT off)
	UINT32 lpd4_reg_tR2P_dfs2               :8;	//23:16	//[DFS] Read to precharge time
	UINT32 lpd4_reg_tR2PD_dfs2              :8;	//31:24	//[DFS] Read to power-down time
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033B0 RW
	UINT32 lpd4_reg_tR2MRW_dfs2             :8;	//7:0	//[DFS] Read to MRW time
	UINT32 lpd4_reg_tRAP2MRW_dfs2           :8;	//15:8	//[DFS] Read auto-precharge to MODE REGISTER WRITE time
	UINT32 lpd4_reg_tPPD_dfs2               :8;	//23:16	//[DFS] Precharge to precharge time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033B4 RW
	UINT32 lpd4_reg_tRFCab_dfs2             :12;	//11:0	//[DFS] Refresh cycle Time (all-bank)
	UINT32 resvd0                           :4;  
	UINT32 lpd4_reg_tRFCpb_dfs2             :12;	//27:16	//[DFS] Refresh cycle Time (per-bank)
	UINT32 resvd1                           :4;  
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033B8 RW
	UINT32 lpd4_reg_tMRW_dfs2               :8;	//7:0	//[DFS] MRW command period & Mode register set command delay (tMRD)
	UINT32 lpd4_reg_tMRWCKEL_dfs2           :8;	//15:8	//[DFS] Valid clock and CS requirement after CKE input LOW after MRW command
	UINT32 lpd4_reg_tVRCG_ENABLE_dfs2       :8;	//23:16	//[DFS] VRCG mode enable time
	UINT32 lpd4_reg_tVRCG_DISABLE_dfs2      :8;	//31:24	//[DFS] VRCG mode disable time
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033BC RW
	UINT32 lpd4_reg_tFC_dfs2                :32;	//31:0	//[DFS] Frequency-Set-Point switching time
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033C0 RW
	UINT32 lpd4_reg_tZQRESET_dfs2           :8;	//7:0	//[DFS] ZQ calibration reset Time
	UINT32 lpd4_reg_tMRR_dfs2               :8;	//15:8	//[DFS] MRR command period
	UINT32 lpd4_reg_tMRRI_dfs2              :8;	//23:16	//[DFS] Additional time after tXP has expired until MRR command may be issued
	UINT32 lpd4_reg_tCMDCKE_dfs2            :8;	//31:24	//[DFS] Delay from valid command to CKE input LOW
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033C4 RW
	UINT32 lpd4_reg_tWRWTR_dfs2             :8;	//7:0	//[DFS] WR/MWR to MPC WR FIFO time
	UINT32 lpd4_reg_tRTRRD_dfs2             :8;	//15:8	//[DFS] RD/MRR to MPC WR FIFO time
	UINT32 lpd4_reg_tWTR2RTR_dfs2           :8;	//23:16	//[DFS] MPC WR FIFO to MPC RD FIFO time
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D033E0 RW
	UINT32 lpd4_reg_tWRLAT_dfs2             :8;	//7:0	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of write command on DFI to assertion of dfi_wrdata_en_p0/p1 signal)
	UINT32 lpd4_reg_tWRDATA_dfs2            :8;	//15:8	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of dfi_wrdata_en_p0/p1 to assertion of dfi_wrdata_p0/p1 signal)
	UINT32 lpd4_reg_tRDLAT_dfs2             :8;	//23:16	//[DFS] Specifies the number of DFI PHY clock cycles 	(From assertion of read command on DFI to assertion of dfi_rddata_en_p0/p1 signal)
	UINT32 resvd                            :8;  
	};
}REG_DDRC_M0_LPD4_DFS2_PHY_IF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05000 RO
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
	struct {						//0xC4D05004 RW
	UINT32 reg_debug_mon_period             :20;	//19:0	//debug monitoring period (ex: 100ms) - (reg_base_period+1) * (reg_debug_mon_period+1)
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_PERIOD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05010 RW
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
	struct {						//0xC4D05014 RO
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
	struct {						//0xC4D05100 RO
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
	struct {						//0xC4D05200 RO
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
	struct {						//0xC4D05204 RW
	UINT32 reg_port_cmd_mon_en              :1;	//0 //AXI  Request capture en in wfo/rfo
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_DEBUG_PORT_IF_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05208 RO
	UINT32 reg_ar_err_id                    :18;	//17:0	//AXI AR Request ERR or Last Request's id
	UINT32 resvd                            :14; 
	};
}REG_DDRC_M0_DEBUG_PORT_IF_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0520C RO
	UINT32 reg_ar_err_addr                  :32;	//31:0	//AXI AR Request ERR or Last Request's addr
	};
}REG_DDRC_M0_DEBUG_PORT_IF_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05210 RO
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
	struct {						//0xC4D05214 RO
	UINT32 reg_aw_err_id                    :18;	//17:0	//AXI AW Request ERR or Last Request's id
	UINT32 resvd                            :14; 
	};
}REG_DDRC_M0_DEBUG_PORT_IF_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05218 RO
	UINT32 reg_aw_err_addr                  :32;	//31:0	//AXI AW Request ERR or Last Request's addr
	};
}REG_DDRC_M0_DEBUG_PORT_IF_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0521C RO
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
	struct {						//0xC4D05300 RO
	UINT32 reg_debug_wuq_valid              :1;	//0 //wuq to sch valid signal probe
	UINT32 reg_debug_wuq_ready              :1;	//1 //wuq to sch ready signal probe
	UINT32 reg_debug_ruq_valid              :1;	//2 //ruq to sch valid signal probe
	UINT32 reg_debug_ruq_ready              :1;	//3 //ruq to sch ready signal probe
	UINT32 resvd                            :28; 
	};
}REG_DDRC_M0_DEBUG_UQ_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05304 RO
	UINT32 reg_debug_wuq_c_cnt              :6;	//5:0	//wuq data queue pending cnt
	UINT32 resvd0                           :10; 
	UINT32 reg_debug_wuq_d_cnt              :9;	//24:16	//wuq command queue pending cnt
	UINT32 resvd1                           :7;  
	};
}REG_DDRC_M0_DEBUG_UQ_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05400 RO
	UINT32 reg_debug_prg_rdy                :8;	//7:0	//precharge ready signal probe per each bank
	UINT32 reg_debug_act_rdy                :8;	//15:8	//activate ready signal probe per each bank
	UINT32 reg_debug_wr_rdy                 :8;	//23:16	//write ready signal probe per each bank
	UINT32 reg_debug_mwr_rdy                :8;	//31:24	//masked write ready signal probe per each bank
	};
}REG_DDRC_M0_DEBUG_SCH0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05404 RO
	UINT32 reg_debug_rd_rdy                 :8;	//7:0	//read ready signal probe per each bank
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_DEBUG_SCH1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05500 RO
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
	struct {						//0xC4D05504 RO
	UINT32 reg_debug_pd_cnt                 :16;	//15:0	//the number of power down entry during monitor period
	UINT32 reg_debug_sr_cnt                 :16;	//31:16	//the number of self refresh entry during monitor period
	};
}REG_DDRC_M0_DEBUG_ALP_ENTRY_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05508 RO
	UINT32 reg_debug_pd_time                :16;	//15:0	//total time of power down stay during monitor period
	UINT32 reg_debug_sr_time                :16;	//31:16	//total time of self refresh stay during monitor period: it is increased every reg_base_period (ex: 1us)
	};
}REG_DDRC_M0_DEBUG_ALP_TIME_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0550C RO
	UINT32 reg_debug_pd_std_cnt             :8;	//7:0	//max value of power down entry waiting counter during monitor period
	UINT32 reg_debug_sr_std_cnt             :8;	//15:8	//max value of self refresh entry waiting counter during monitor period: it is increased every reg_base_period (ex: 1us)
	UINT32 reg_debug_pd_ex_std_cnt          :8;	//23:16	//max value of power down exit waiting counter during monitor period
	UINT32 reg_debug_sr_ex_std_cnt          :8;	//31:24	//max value of self refresh exit waiting counter during monitor period: it is increased every reg_base_period (ex: 1us)
	};
}REG_DDRC_M0_DEBUG_ALP_WAIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05600 RO
	UINT32 reg_debug_dfs_state              :3;	//2:0	//dfs status
	UINT32 resvd                            :29; 
	};
}REG_DDRC_M0_DEBUG_DFS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05700 RO
	UINT32 reg_debug_nidle                  :32;	//31:0	//number of idle cycle
	};
}REG_DDRC_M0_DEBUG_IDLE_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05704 RO
	UINT32 reg_debug_nrd                    :32;	//31:0	//number of short read commands
	};
}REG_DDRC_M0_DEBUG_RD_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05708 RO
	UINT32 reg_debug_nrdl                   :32;	//31:0	//number of long read commands
	};
}REG_DDRC_M0_DEBUG_RDL_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05710 RO
	UINT32 reg_debug_nwr                    :32;	//31:0	//number of short write commands
	};
}REG_DDRC_M0_DEBUG_RWR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05714 RO
	UINT32 reg_debug_nmwr                   :32;	//31:0	//number of short masked write commands
	};
}REG_DDRC_M0_DEBUG_MWR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05718 RO
	UINT32 reg_debug_nwrl                   :32;	//31:0	//number of long write commands
	};
}REG_DDRC_M0_DEBUG_WRL_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05720 RO
	UINT32 reg_debug_nap                    :20;	//19:0	//number of AP commands
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_PRG_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05724 RO
	UINT32 reg_debug_nref                   :20;	//19:0	//number of all bank refresh commands
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_REF_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05728 RO
	UINT32 reg_debug_nact                   :32;	//31:0	//number of act commands
	};
}REG_DDRC_M0_DEBUG_ACT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0572C RO
	UINT32 reg_debug_nrw_swc                :32;	//31:0	//number of read/write command swich
	};
}REG_DDRC_M0_DEBUG_RW_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05730 RO
	UINT32 reg_debug_nr_urg_swc             :32;	//31:0	//number of urgent read command swich
	};
}REG_DDRC_M0_DEBUG_R_URG_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05734 RO
	UINT32 reg_debug_nr_req_row_hit         :32;	//31:0	//number of req_row hit in read port
	};
}REG_DDRC_M0_DEBUG_R_REQ_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05738 RO
	UINT32 reg_debug_nr_req_hit             :32;	//31:0	//number of req hit in read port
	};
}REG_DDRC_M0_DEBUG_R_REQ_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0573C RO
	UINT32 reg_debug_nr_urg_row_hit         :32;	//31:0	//number of urgent row hit in read port
	};
}REG_DDRC_M0_DEBUG_R_URG_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05740 RO
	UINT32 reg_debug_nr_urg_hit             :32;	//31:0	//number of urgent hit in read port
	};
}REG_DDRC_M0_DEBUG_R_URG_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05744 RO
	UINT32 reg_debug_nr_row_hit             :32;	//31:0	//number of row hit in read port
	};
}REG_DDRC_M0_DEBUG_R_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05748 RO
	UINT32 reg_debug_nr_lucky_hit           :32;	//31:0	//number of lucky in read port
	};
}REG_DDRC_M0_DEBUG_R_LUCKY_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05750 RO
	UINT32 reg_debug_nw_urg_swc             :32;	//31:0	//number of urgent write command swich
	};
}REG_DDRC_M0_DEBUG_W_URG_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05754 RO
	UINT32 reg_debug_nw_req_row_hit         :32;	//31:0	//number of req_row hit in write port
	};
}REG_DDRC_M0_DEBUG_W_REQ_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05758 RO
	UINT32 reg_debug_nw_req_hit             :32;	//31:0	//number of req hit in write port
	};
}REG_DDRC_M0_DEBUG_W_REQ_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0575C RO
	UINT32 reg_debug_nw_urg_row_hit         :32;	//31:0	//number of urgent row hit in write port
	};
}REG_DDRC_M0_DEBUG_W_URG_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05760 RO
	UINT32 reg_debug_nw_urg_hit             :32;	//31:0	//number of urgent hit in write port
	};
}REG_DDRC_M0_DEBUG_W_URG_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05764 RO
	UINT32 reg_debug_nw_row_hit             :32;	//31:0	//number of row hit in write port
	};
}REG_DDRC_M0_DEBUG_W_ROW_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05768 RO
	UINT32 reg_debug_nw_lucky_hit           :32;	//31:0	//number of lucky in write port
	};
}REG_DDRC_M0_DEBUG_W_LUCKY_HIT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05770 RO
	UINT32 reg_debug_max_lat_3              :8;	//7:0	//max latency for qos 1~3
	UINT32 reg_debug_max_lat_5              :8;	//15:8	//max latency for qos 4~5
	UINT32 reg_debug_max_lat_7              :8;	//23:16	//max latency for qos 6~7
	UINT32 reg_debug_max_lat_8              :8;	//31:24	//max latency for qos 8~
	};
}REG_DDRC_M0_DEBUG_MAX_LAT_QOS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05800 RO
	UINT32 reg_debug_nr_hyb_swc             :32;	//31:0	//number of hybrid read command swich
	};
}REG_DDRC_M0_DEBUG_R_HYB_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05804 RO
	UINT32 reg_debug_nw_hyb_swc             :32;	//31:0	//number of hybrid write command swich
	};
}REG_DDRC_M0_DEBUG_W_HYB_SWC_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05900 RO
	UINT32 reg_debug_nr_fifo_0_prt          :32;	//31:0	//number of read fifo 0 prt
	};
}REG_DDRC_M0_DEBUG_R_FIFO_0_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05904 RO
	UINT32 reg_debug_nr_fifo_1_prt          :32;	//31:0	//number of read fifo 1 prt
	};
}REG_DDRC_M0_DEBUG_R_FIFO_1_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05908 RO
	UINT32 reg_debug_nr_fifo_2_prt          :32;	//31:0	//number of read fifo 2 prt
	};
}REG_DDRC_M0_DEBUG_R_FIFO_2_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0590C RO
	UINT32 reg_debug_nr_fifo_3_prt          :32;	//31:0	//number of read fifo 3 prt
	};
}REG_DDRC_M0_DEBUG_R_FIFO_3_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05910 RO
	UINT32 reg_debug_nw_fifo_0_prt          :32;	//31:0	//number of write fifo 0 prt
	};
}REG_DDRC_M0_DEBUG_W_FIFO_0_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05914 RO
	UINT32 reg_debug_nw_fifo_1_prt          :32;	//31:0	//number of write fifo 1 prt
	};
}REG_DDRC_M0_DEBUG_W_FIFO_1_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D05918 RO
	UINT32 reg_debug_nw_fifo_2_prt          :32;	//31:0	//number of write fifo 2 prt
	};
}REG_DDRC_M0_DEBUG_W_FIFO_2_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0591C RO
	UINT32 reg_debug_nw_fifo_3_prt          :32;	//31:0	//number of write fifo 3 prt
	};
}REG_DDRC_M0_DEBUG_W_FIFO_3_PRT_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06000 RO
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
	struct {						//0xC4D06004 RO
	UINT32 lpd4_mf_reg_fsm_status_0         :32;	//31:0	//Main FSM information (1ST)
	};
}REG_DDRC_M0_DEBUG_LPD4_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06008 RO
	UINT32 lpd4_mf_reg_fsm_status_1         :32;	//31:0	//Main FSM information (2ND)
	};
}REG_DDRC_M0_DEBUG_LPD4_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0600C RO
	UINT32 lpd4_mf_reg_fsm_status_2         :1;	//0 //Main FSM information (3RD)
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_DEBUG_LPD4_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06010 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_0    :32;	//31:0	//Direct control done information (1ST)
	};
}REG_DDRC_M0_DEBUG_LPD4_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06014 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_1    :32;	//31:0	//Direct control done information (2ND)
	};
}REG_DDRC_M0_DEBUG_LPD4_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06018 RO
	UINT32 lpd4_mf_reg_dir_ctrl_status_2    :1;	//0 //Direct control done information (3RD)
	UINT32 resvd                            :31; 
	};
}REG_DDRC_M0_DEBUG_LPD4_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0601C RO
	UINT32 lpd4_rr_reg_ref_req_ctrl_status  :32;	//31:0	//[31:16] : Derated tREFI	[15:12] : Derated threshold value of urgent refresh	[11:4] : Derated tRRD	[1] : Forced all-bank refresh mode	[0] : Distributed all-bank refresh mode
	};
}REG_DDRC_M0_DEBUG_LPD4_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06020 RO
	UINT32 lpd4_rc_reg_fsm_status           :11;	//10:0	//Refresh controller FSM information
	UINT32 resvd                            :5;  
	UINT32 lpd4_rc_reg_ref_pb_sel_flag      :8;	//23:16	//Bank selection information for per-bank refresh
	UINT32 lpd4_rc_reg_ref_pb_done_flag     :8;	//31:24	//Bank completion information for per-bank refresh
	};
}REG_DDRC_M0_DEBUG_LPD4_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06024 RO
	UINT32 lpd4_bf_reg_fsm_status_b0        :14;	//13:0	//Bank FSM information (bank0)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b1        :14;	//29:16	//Bank FSM information (bank1)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M0_DEBUG_LPD4_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06028 RO
	UINT32 lpd4_bf_reg_fsm_status_b2        :14;	//13:0	//Bank FSM information (bank2)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b3        :14;	//29:16	//Bank FSM information (bank3)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M0_DEBUG_LPD4_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0602C RO
	UINT32 lpd4_bf_reg_fsm_status_b4        :14;	//13:0	//Bank FSM information (bank4)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b5        :14;	//29:16	//Bank FSM information (bank5)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M0_DEBUG_LPD4_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06030 RO
	UINT32 lpd4_bf_reg_fsm_status_b6        :14;	//13:0	//Bank FSM information (bank6)
	UINT32 resvd0                           :2;  
	UINT32 lpd4_bf_reg_fsm_status_b7        :14;	//29:16	//Bank FSM information (bank7)
	UINT32 resvd1                           :2;  
	};
}REG_DDRC_M0_DEBUG_LPD4_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06034 RO
	UINT32 lpd4_bs_reg_bank_open            :8;	//7:0	//Bank open information
	UINT32 resvd                            :24; 
	};
}REG_DDRC_M0_DEBUG_LPD4_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06038 RO
	UINT32 lpd4_bs_reg_rdy_status_0         :32;	//31:0	//Bank ready information	[31:24] : Read	[23:16] : Masked write	[15:8] : Write	[7:0] : Activate
	};
}REG_DDRC_M0_DEBUG_LPD4_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0603C RO
	UINT32 lpd4_bs_reg_rdy_status_1         :32;	//31:0	//Bank ready information	[28] : MRR	[27] : MRW	[26] : Power-down	[25] : All-bank refresh	[23:16] : Per-bank refresh	[15:8] : Auto-precharge	[7:0] : Per-bank precharge
	};
}REG_DDRC_M0_DEBUG_LPD4_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06040 RO
	UINT32 lpd4_pi_reg_fifo_status          :32;	//31:0	//Pointer information	[22:20] : Read pipeline pointer	[18:16] : Write pipeline pointer	[15:12] : RFIFO output pointer	[11:8] : RFIFO input pointer	[7:4] : WFIFO output pointer	[3:0] : WFIFO input pointer
	};
}REG_DDRC_M0_DEBUG_LPD4_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06100 RO
	UINT32 lpd4_mr_reg_mr0_ch0              :8;	//7:0	//MR0 read information for CH0
	UINT32 lpd4_mr_reg_mr4_ch0              :8;	//15:8	//MR4 read information for CH0
	UINT32 lpd4_mr_reg_mr5_ch0              :8;	//23:16	//MR5 read information for CH0
	UINT32 lpd4_mr_reg_mr6_ch0              :8;	//31:24	//MR6 read information for CH0
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06104 RO
	UINT32 lpd4_mr_reg_mr7_ch0              :8;	//7:0	//MR7 read information for CH0
	UINT32 lpd4_mr_reg_mr8_ch0              :8;	//15:8	//MR8 read information for CH0
	UINT32 lpd4_mr_reg_mr12_ch0             :8;	//23:16	//MR12 read information for CH0
	UINT32 lpd4_mr_reg_mr14_ch0             :8;	//31:24	//MR14 read information for CH0
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06108 RO
	UINT32 lpd4_mr_reg_mr18_ch0             :8;	//7:0	//MR18 read information for CH0
	UINT32 lpd4_mr_reg_mr19_ch0             :8;	//15:8	//MR19 read information for CH0
	UINT32 lpd4_mr_reg_mr24_ch0             :8;	//23:16	//MR24 read information for CH0
	UINT32 lpd4_mr_reg_mr25_ch0             :8;	//31:24	//MR25 read information for CH0
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0610C RO
	UINT32 lpd4_mr_reg_mr0_ch1              :8;	//7:0	//MR0 read information for CH1
	UINT32 lpd4_mr_reg_mr4_ch1              :8;	//15:8	//MR4 read information for CH1
	UINT32 lpd4_mr_reg_mr5_ch1              :8;	//23:16	//MR5 read information for CH1
	UINT32 lpd4_mr_reg_mr6_ch1              :8;	//31:24	//MR6 read information for CH1
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06110 RO
	UINT32 lpd4_mr_reg_mr7_ch1              :8;	//7:0	//MR7 read information for CH1
	UINT32 lpd4_mr_reg_mr8_ch1              :8;	//15:8	//MR8 read information for CH1
	UINT32 lpd4_mr_reg_mr12_ch1             :8;	//23:16	//MR12 read information for CH1
	UINT32 lpd4_mr_reg_mr14_ch1             :8;	//31:24	//MR14 read information for CH1
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06114 RO
	UINT32 lpd4_mr_reg_mr18_ch1             :8;	//7:0	//MR18 read information for CH1
	UINT32 lpd4_mr_reg_mr19_ch1             :8;	//15:8	//MR19 read information for CH1
	UINT32 lpd4_mr_reg_mr24_ch1             :8;	//23:16	//MR24 read information for CH1
	UINT32 lpd4_mr_reg_mr25_ch1             :8;	//31:24	//MR25 read information for CH1
	};
}REG_DDRC_M0_DEBUG_LPD4_MR_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06118 RO
	UINT32 lpd4_reg_mpc_fifo_fail_cnt       :32;	//31:0	//Periodic MPC FIFO fail count
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0611C RO
	UINT32 lpd4_reg_mpc_fifo_fail_data0     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06120 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data1     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06124 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data2     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06128 RO
	UINT32 lpd4_reg_mpc_fifo_fail_data3     :32;	//31:0	//Periodic MPC FIFO fail data
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0612C RO
	UINT32 lpd4_reg_mpc_fifo_fail_dmi0      :4;	//3:0	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi1      :4;	//7:4	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi2      :4;	//11:8	//Periodic MPC FIFO fail dmi data
	UINT32 lpd4_reg_mpc_fifo_fail_dmi3      :4;	//15:12	//Periodic MPC FIFO fail dmi data
	UINT32 resvd                            :16; 
	};
}REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06200 RO
	UINT32 reg_mf_mrw1_cnt                  :20;	//19:0	//number of channel 1 mrw command issued by main function
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MRW1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06204 RO
	UINT32 reg_mf_mrw0_cnt                  :20;	//19:0	//number of channel 0 mrw command issued by main function
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MRW0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06208 RO
	UINT32 reg_mf_lp_exit_cnt               :20;	//19:0	//number of lp exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_LP_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0620C RO
	UINT32 reg_mf_lp_entry_cnt              :20;	//19:0	//number of lp entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_LP_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06210 RO
	UINT32 reg_mf_sr_pd_exit_cnt            :20;	//19:0	//number of self-rerfresh power down exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_SR_PD_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06214 RO
	UINT32 reg_mf_sr_pd_entry_cnt           :20;	//19:0	//number of self-refresh power down entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_SR_PD_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06218 RO
	UINT32 reg_mf_sr_exit_cnt               :20;	//19:0	//number of self-refresh exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_SR_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0621C RO
	UINT32 reg_mf_sr_entry_cnt              :20;	//19:0	//number of self_refresh entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_SR_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06220 RO
	UINT32 reg_mf_pd_exit_cnt               :20;	//19:0	//number of power down exit command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PD_EXIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06224 RO
	UINT32 reg_mf_pd_entry_cnt              :20;	//19:0	//number of power down entry command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PD_ENTRY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06228 RO
	UINT32 reg_mf_zqlat_cnt                 :20;	//19:0	//number of zqcal latch command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ZQLAT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0622C RO
	UINT32 reg_mf_zqcal_cnt                 :20;	//19:0	//number of zqcal command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ZQCAL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06230 RO
	UINT32 reg_mf_cke_1_cnt                 :20;	//19:0	//number of cke rising command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CKE1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06234 RO
	UINT32 reg_mf_cke_0_cnt                 :20;	//19:0	//number of cke falling command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CKE0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06238 RO
	UINT32 reg_mf_rstn_1_cnt                :20;	//19:0	//number of reset rising command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RSTN1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0623C RO
	UINT32 reg_mf_rstn_0_cnt                :20;	//19:0	//number of reset falling command issued by main funciton
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RSTN0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06240 RO
	UINT32 reg_cg_rd0_cnt                   :32;	//31:0	//number of bank 0 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06244 RO
	UINT32 reg_cg_rd1_cnt                   :32;	//31:0	//number of bank 1 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06248 RO
	UINT32 reg_cg_rd2_cnt                   :32;	//31:0	//number of bank 2 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0624C RO
	UINT32 reg_cg_rd3_cnt                   :32;	//31:0	//number of bank 3 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06250 RO
	UINT32 reg_cg_rd4_cnt                   :32;	//31:0	//number of bank 4 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06254 RO
	UINT32 reg_cg_rd5_cnt                   :32;	//31:0	//number of bank 5 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06258 RO
	UINT32 reg_cg_rd6_cnt                   :32;	//31:0	//number of bank 6 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0625C RO
	UINT32 reg_cg_rd7_cnt                   :32;	//31:0	//number of bank 7 read command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_RD7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06260 RO
	UINT32 reg_cg_mwr0_cnt                  :32;	//31:0	//number of bank 0 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06264 RO
	UINT32 reg_cg_mwr1_cnt                  :32;	//31:0	//number of bank 1 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06268 RO
	UINT32 reg_cg_mwr2_cnt                  :32;	//31:0	//number of bank 2 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0626C RO
	UINT32 reg_cg_mwr3_cnt                  :32;	//31:0	//number of bank 3 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06270 RO
	UINT32 reg_cg_mwr4_cnt                  :32;	//31:0	//number of bank 4 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06274 RO
	UINT32 reg_cg_mwr5_cnt                  :32;	//31:0	//number of bank 5 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06278 RO
	UINT32 reg_cg_mwr6_cnt                  :32;	//31:0	//number of bank 6 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0627C RO
	UINT32 reg_cg_mwr7_cnt                  :32;	//31:0	//number of bank 7 masked write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MWR7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06280 RO
	UINT32 reg_cg_wr0_cnt                   :32;	//31:0	//number of bank 0 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06284 RO
	UINT32 reg_cg_wr1_cnt                   :32;	//31:0	//number of bank 1 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06288 RO
	UINT32 reg_cg_wr2_cnt                   :32;	//31:0	//number of bank 2 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0628C RO
	UINT32 reg_cg_wr3_cnt                   :32;	//31:0	//number of bank 3 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06290 RO
	UINT32 reg_cg_wr4_cnt                   :32;	//31:0	//number of bank 4 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06294 RO
	UINT32 reg_cg_wr5_cnt                   :32;	//31:0	//number of bank 5 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06298 RO
	UINT32 reg_cg_wr6_cnt                   :32;	//31:0	//number of bank 6 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0629C RO
	UINT32 reg_cg_wr7_cnt                   :32;	//31:0	//number of bank 7 write command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_WR7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D062A0 RO
	UINT32 reg_cg_act0_cnt                  :32;	//31:0	//number of bank 0 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D062A4 RO
	UINT32 reg_cg_act1_cnt                  :32;	//31:0	//number of bank 1 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D062A8 RO
	UINT32 reg_cg_act2_cnt                  :32;	//31:0	//number of bank 2 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D062AC RO
	UINT32 reg_cg_act3_cnt                  :32;	//31:0	//number of bank 3 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D062B0 RO
	UINT32 reg_cg_act4_cnt                  :32;	//31:0	//number of bank 4 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D062B4 RO
	UINT32 reg_cg_act5_cnt                  :32;	//31:0	//number of bank 5 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D062B8 RO
	UINT32 reg_cg_act6_cnt                  :32;	//31:0	//number of bank 6 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D062BC RO
	UINT32 reg_cg_act7_cnt                  :32;	//31:0	//number of bank 7 activate command issued by command generator
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_ACT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06300 RO
	UINT32 reg_ref_pb0_cnt                  :22;	//21:0	//number of bank 0 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06304 RO
	UINT32 reg_ref_pb1_cnt                  :22;	//21:0	//number of bank 1 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06308 RO
	UINT32 reg_ref_pb2_cnt                  :22;	//21:0	//number of bank 2 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0630C RO
	UINT32 reg_ref_pb3_cnt                  :22;	//21:0	//number of bank 3 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06310 RO
	UINT32 reg_ref_pb4_cnt                  :22;	//21:0	//number of bank 4 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06314 RO
	UINT32 reg_ref_pb5_cnt                  :22;	//21:0	//number of bank 5 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06318 RO
	UINT32 reg_ref_pb6_cnt                  :22;	//21:0	//number of bank 6 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0631C RO
	UINT32 reg_ref_pb7_cnt                  :22;	//21:0	//number of bank 7 per-bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06320 RO
	UINT32 reg_prg_pb0_cnt                  :22;	//21:0	//number of bank 0 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06324 RO
	UINT32 reg_prg_pb1_cnt                  :22;	//21:0	//number of bank 1 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06328 RO
	UINT32 reg_prg_pb2_cnt                  :22;	//21:0	//number of bank 2 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0632C RO
	UINT32 reg_prg_pb3_cnt                  :22;	//21:0	//number of bank 3 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06330 RO
	UINT32 reg_prg_pb4_cnt                  :22;	//21:0	//number of bank 4 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06334 RO
	UINT32 reg_prg_pb5_cnt                  :22;	//21:0	//number of bank 5 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06338 RO
	UINT32 reg_prg_pb6_cnt                  :22;	//21:0	//number of bank 6 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0633C RO
	UINT32 reg_prg_pb7_cnt                  :22;	//21:0	//number of bank 7 per-bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06340 RO
	UINT32 reg_cg_ref_ab_cnt                :22;	//21:0	//number of all bank refresh command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CG_REF_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06344 RO
	UINT32 reg_mf_ref_ab_cnt                :22;	//21:0	//number of all bank refresh command issued by main function
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MF_REF_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06350 RO
	UINT32 reg_cg_prg_ab_cnt                :22;	//21:0	//number of all bank pre-charge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CG_PRG_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06354 RO
	UINT32 reg_mf_prg_ab_cnt                :22;	//21:0	//number of all bank pre-charge command issued by main function
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_MF_PRG_AB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06360 RO
	UINT32 reg_cg_bl_cnt                    :22;	//21:0	//number of long burst command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CG_BL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06364 RO
	UINT32 reg_cg_ap_cnt                    :22;	//21:0	//number of auto precharge command issued by command generator
	UINT32 resvd                            :10; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_CG_AP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06368 RO
	UINT32 reg_ref_cycling_done_cnt         :20;	//19:0	//number of refresh cycling done command
	UINT32 resvd                            :12; 
	};
}REG_DDRC_M0_DEBUG_CTRL_CMD_REF_CYCLE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06700 RO
	UINT32 pi_reg_dfi_status                :32;	//31:0	//DFI information	[30] : dfi_lp_ack	[29:26] : dfi_lp_wakeup	[25] : dfi_lp_req	[24] : dfi_dram_clk_disable	[23:21] : pll_freq_type[2:0]	[20] : pll_lock_done	[19:18] : pll_freq_type[4:3]	[17] : dfi_ctrlupd_ack	[16] : dfi_ctrlupd_req	[14] : dfi_phyupd_ack	[13] : dfi_phyupd_type	[12] : dfi_phyupd_req	[10] : dfi_phymstr_ack	[9] : dfi_phymstr_type	[8] : dfi_phymstr_req	[6] : dfi_init_complete	[5:1] : dfi_frequency	[0] : dfi_init_start
	};
}REG_DDRC_M0_DEBUG_DFI_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06800 
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
	struct {						//0xC4D06804 
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
	struct {						//0xC4D06808 
	UINT32 reg_bist_cmdq_vld                :16;	//15:0	//bist cmdq valid state monitor
	UINT32 reg_bist_cmdq_req                :16;	//31:16	//bist cmdq request state monitor
	};
}REG_DDRC_M0_DRAM_BIST_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0680C 
	UINT32 reg_user_pat                     :32;	//31:0	//set bist user data pattern
	};
}REG_DDRC_M0_DRAM_BIST_DATA_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06810 
	UINT32 reg_mask_pat_0                   :16;	//15:0	//data mask for 1st 16byte data
	UINT32 reg_mask_pat_1                   :16;	//31:16	//data mask for 2nd 16byte data
	};
}REG_DDRC_M0_DRAM_BIST_DATA_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06814 
	UINT32 reg_mask_pat_2                   :16;	//15:0	//data mask for 3rd 16byte data
	UINT32 reg_mask_pat_3                   :16;	//31:16	//data mask for 4th 16byte data
	};
}REG_DDRC_M0_DRAM_BIST_DATA_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06818 
	UINT32 reg_bist_addr_cnt_max            :32;	//31:0	//Set how many times to repeat when reg_bist_addr_map is not "SPL".
	};
}REG_DDRC_M0_DRAM_BIST_ADDR_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0681C 
	UINT32 reg_s_addr                       :32;	//31:0	//set bist start address, SPL mode (use full bit), not SPL mode ([31:15] row, [14:12] ba, [11:5] col)
	};
}REG_DDRC_M0_DRAM_BIST_ADDR_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06820 
	UINT32 reg_e_addr                       :32;	//31:0	//set bist start address, SPL mode (use full bit), not SPL mode ([31:15] row, [14:12] ba, [11:5] col), default 2Gbyte setting
	};
}REG_DDRC_M0_DRAM_BIST_ADDR_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06824 
	UINT32 reg_bist_opcmd_00                :8;	//7:0	//
	UINT32 reg_bist_opcmd_01                :8;	//15:8	//
	UINT32 reg_bist_opcmd_02                :8;	//23:16	//
	UINT32 reg_bist_opcmd_03                :8;	//31:24	//set bist operation cmd  , default MARCH C-,
	};
}REG_DDRC_M0_DRAM_BIST_OPCMD_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06828 
	UINT32 reg_bist_opcmd_04                :8;	//7:0	//
	UINT32 reg_bist_opcmd_05                :8;	//15:8	//
	UINT32 reg_bist_opcmd_06                :8;	//23:16	//
	UINT32 reg_bist_opcmd_07                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M0_DRAM_BIST_OPCMD_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0682C 
	UINT32 reg_bist_opcmd_08                :8;	//7:0	//
	UINT32 reg_bist_opcmd_09                :8;	//15:8	//
	UINT32 reg_bist_opcmd_10                :8;	//23:16	//
	UINT32 reg_bist_opcmd_11                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M0_DRAM_BIST_OPCMD_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06830 
	UINT32 reg_bist_opcmd_12                :8;	//7:0	//
	UINT32 reg_bist_opcmd_13                :8;	//15:8	//
	UINT32 reg_bist_opcmd_14                :8;	//23:16	//
	UINT32 reg_bist_opcmd_15                :8;	//31:24	//set bist operation cmd  , default MARCH C-
	};
}REG_DDRC_M0_DRAM_BIST_OPCMD_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06834 RO
	UINT32 reg_err_addr                     :32;	//31:0	//address where error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_ADDR_INFO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06838 RO
	UINT32 reg_err_data_00                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0683C RO
	UINT32 reg_err_data_01                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06840 RO
	UINT32 reg_err_data_02                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06844 RO
	UINT32 reg_err_data_03                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06848 RO
	UINT32 reg_err_data_04                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0684C RO
	UINT32 reg_err_data_05                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06850 RO
	UINT32 reg_err_data_06                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06854 RO
	UINT32 reg_err_data_07                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06858 RO
	UINT32 reg_err_data_08                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0685C RO
	UINT32 reg_err_data_09                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06860 RO
	UINT32 reg_err_data_10                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06864 RO
	UINT32 reg_err_data_11                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06868 RO
	UINT32 reg_err_data_12                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0686C RO
	UINT32 reg_err_data_13                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06870 RO
	UINT32 reg_err_data_14                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06874 RO
	UINT32 reg_err_data_15                  :32;	//31:0	//err read data when error occurred
	};
}REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06878 RO
	UINT32 reg_exp_data_00                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0687C RO
	UINT32 reg_exp_data_01                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06880 RO
	UINT32 reg_exp_data_02                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06884 RO
	UINT32 reg_exp_data_03                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06888 RO
	UINT32 reg_exp_data_04                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0688C RO
	UINT32 reg_exp_data_05                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06890 RO
	UINT32 reg_exp_data_06                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06894 RO
	UINT32 reg_exp_data_07                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06898 RO
	UINT32 reg_exp_data_08                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D0689C RO
	UINT32 reg_exp_data_09                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D068A0 RO
	UINT32 reg_exp_data_10                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D068A4 RO
	UINT32 reg_exp_data_11                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D068A8 RO
	UINT32 reg_exp_data_12                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D068AC RO
	UINT32 reg_exp_data_13                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D068B0 RO
	UINT32 reg_exp_data_14                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D068B4 RO
	UINT32 reg_exp_data_15                  :32;	//31:0	//expected read data
	};
}REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC4D06FE0 RW
	UINT32 reg_rey_spare                    :32;	//31:0	//spare register for ECO (should not be removed)
	};
}REG_DDRC_M0_REY_SPARE_T;

typedef struct {
	REG_DDRC_M0_DRAM_CONF_T                                   dram_conf;	//0xC4D00000
	REG_DDRC_M0_MODE_SEL_T                                     mode_sel;	//0xC4D00004
	REG_DDRC_M0_BASE_PERIOD_T                               base_period;	//0xC4D00008
	UINT32                                                    reserved0;	//0xC4D0000C
	UINT32                                                    reserved1;	//0xC4D00010
	UINT32                                                    reserved2;	//0xC4D00014
	UINT32                                                    reserved3;	//0xC4D00018
	UINT32                                                    reserved4;	//0xC4D0001C
	UINT32                                                    reserved5;	//0xC4D00020
	UINT32                                                    reserved6;	//0xC4D00024
	UINT32                                                    reserved7;	//0xC4D00028
	UINT32                                                    reserved8;	//0xC4D0002C
	UINT32                                                    reserved9;	//0xC4D00030
	UINT32                                                   reserved10;	//0xC4D00034
	UINT32                                                   reserved11;	//0xC4D00038
	UINT32                                                   reserved12;	//0xC4D0003C
	UINT32                                                   reserved13;	//0xC4D00040
	UINT32                                                   reserved14;	//0xC4D00044
	UINT32                                                   reserved15;	//0xC4D00048
	UINT32                                                   reserved16;	//0xC4D0004C
	UINT32                                                   reserved17;	//0xC4D00050
	UINT32                                                   reserved18;	//0xC4D00054
	UINT32                                                   reserved19;	//0xC4D00058
	UINT32                                                   reserved20;	//0xC4D0005C
	UINT32                                                   reserved21;	//0xC4D00060
	UINT32                                                   reserved22;	//0xC4D00064
	UINT32                                                   reserved23;	//0xC4D00068
	UINT32                                                   reserved24;	//0xC4D0006C
	UINT32                                                   reserved25;	//0xC4D00070
	UINT32                                                   reserved26;	//0xC4D00074
	UINT32                                                   reserved27;	//0xC4D00078
	UINT32                                                   reserved28;	//0xC4D0007C
	UINT32                                                   reserved29;	//0xC4D00080
	UINT32                                                   reserved30;	//0xC4D00084
	UINT32                                                   reserved31;	//0xC4D00088
	UINT32                                                   reserved32;	//0xC4D0008C
	UINT32                                                   reserved33;	//0xC4D00090
	UINT32                                                   reserved34;	//0xC4D00094
	UINT32                                                   reserved35;	//0xC4D00098
	UINT32                                                   reserved36;	//0xC4D0009C
	UINT32                                                   reserved37;	//0xC4D000A0
	UINT32                                                   reserved38;	//0xC4D000A4
	UINT32                                                   reserved39;	//0xC4D000A8
	UINT32                                                   reserved40;	//0xC4D000AC
	UINT32                                                   reserved41;	//0xC4D000B0
	UINT32                                                   reserved42;	//0xC4D000B4
	UINT32                                                   reserved43;	//0xC4D000B8
	UINT32                                                   reserved44;	//0xC4D000BC
	UINT32                                                   reserved45;	//0xC4D000C0
	UINT32                                                   reserved46;	//0xC4D000C4
	UINT32                                                   reserved47;	//0xC4D000C8
	UINT32                                                   reserved48;	//0xC4D000CC
	UINT32                                                   reserved49;	//0xC4D000D0
	UINT32                                                   reserved50;	//0xC4D000D4
	UINT32                                                   reserved51;	//0xC4D000D8
	UINT32                                                   reserved52;	//0xC4D000DC
	UINT32                                                   reserved53;	//0xC4D000E0
	UINT32                                                   reserved54;	//0xC4D000E4
	UINT32                                                   reserved55;	//0xC4D000E8
	UINT32                                                   reserved56;	//0xC4D000EC
	UINT32                                                   reserved57;	//0xC4D000F0
	UINT32                                                   reserved58;	//0xC4D000F4
	UINT32                                                   reserved59;	//0xC4D000F8
	UINT32                                                   reserved60;	//0xC4D000FC
	REG_DDRC_M0_ALP_T                                               alp;	//0xC4D00100
	REG_DDRC_M0_CGL_T                                               cgl;	//0xC4D00104
	REG_DDRC_M0_CGL_MON_T                                       cgl_mon;	//0xC4D00108
	UINT32                                                   reserved61;	//0xC4D0010C
	UINT32                                                   reserved62;	//0xC4D00110
	UINT32                                                   reserved63;	//0xC4D00114
	UINT32                                                   reserved64;	//0xC4D00118
	UINT32                                                   reserved65;	//0xC4D0011C
	UINT32                                                   reserved66;	//0xC4D00120
	UINT32                                                   reserved67;	//0xC4D00124
	UINT32                                                   reserved68;	//0xC4D00128
	UINT32                                                   reserved69;	//0xC4D0012C
	UINT32                                                   reserved70;	//0xC4D00130
	UINT32                                                   reserved71;	//0xC4D00134
	UINT32                                                   reserved72;	//0xC4D00138
	UINT32                                                   reserved73;	//0xC4D0013C
	UINT32                                                   reserved74;	//0xC4D00140
	UINT32                                                   reserved75;	//0xC4D00144
	UINT32                                                   reserved76;	//0xC4D00148
	UINT32                                                   reserved77;	//0xC4D0014C
	UINT32                                                   reserved78;	//0xC4D00150
	UINT32                                                   reserved79;	//0xC4D00154
	UINT32                                                   reserved80;	//0xC4D00158
	UINT32                                                   reserved81;	//0xC4D0015C
	UINT32                                                   reserved82;	//0xC4D00160
	UINT32                                                   reserved83;	//0xC4D00164
	UINT32                                                   reserved84;	//0xC4D00168
	UINT32                                                   reserved85;	//0xC4D0016C
	UINT32                                                   reserved86;	//0xC4D00170
	UINT32                                                   reserved87;	//0xC4D00174
	UINT32                                                   reserved88;	//0xC4D00178
	UINT32                                                   reserved89;	//0xC4D0017C
	UINT32                                                   reserved90;	//0xC4D00180
	UINT32                                                   reserved91;	//0xC4D00184
	UINT32                                                   reserved92;	//0xC4D00188
	UINT32                                                   reserved93;	//0xC4D0018C
	UINT32                                                   reserved94;	//0xC4D00190
	UINT32                                                   reserved95;	//0xC4D00194
	UINT32                                                   reserved96;	//0xC4D00198
	UINT32                                                   reserved97;	//0xC4D0019C
	UINT32                                                   reserved98;	//0xC4D001A0
	UINT32                                                   reserved99;	//0xC4D001A4
	UINT32                                                  reserved100;	//0xC4D001A8
	UINT32                                                  reserved101;	//0xC4D001AC
	UINT32                                                  reserved102;	//0xC4D001B0
	UINT32                                                  reserved103;	//0xC4D001B4
	UINT32                                                  reserved104;	//0xC4D001B8
	UINT32                                                  reserved105;	//0xC4D001BC
	UINT32                                                  reserved106;	//0xC4D001C0
	UINT32                                                  reserved107;	//0xC4D001C4
	UINT32                                                  reserved108;	//0xC4D001C8
	UINT32                                                  reserved109;	//0xC4D001CC
	UINT32                                                  reserved110;	//0xC4D001D0
	UINT32                                                  reserved111;	//0xC4D001D4
	UINT32                                                  reserved112;	//0xC4D001D8
	UINT32                                                  reserved113;	//0xC4D001DC
	UINT32                                                  reserved114;	//0xC4D001E0
	UINT32                                                  reserved115;	//0xC4D001E4
	UINT32                                                  reserved116;	//0xC4D001E8
	UINT32                                                  reserved117;	//0xC4D001EC
	UINT32                                                  reserved118;	//0xC4D001F0
	UINT32                                                  reserved119;	//0xC4D001F4
	UINT32                                                  reserved120;	//0xC4D001F8
	UINT32                                                  reserved121;	//0xC4D001FC
	REG_DDRC_M0_PERFMON_T                                       perfmon;	//0xC4D00200
	REG_DDRC_M0_PERFMON_EMG_MAX_T                       perfmon_emg_max;	//0xC4D00204
	UINT32                                                  reserved122;	//0xC4D00208
	UINT32                                                  reserved123;	//0xC4D0020C
	REG_DDRC_M0_PERFMON_W0_T                                 perfmon_w0;	//0xC4D00210
	REG_DDRC_M0_PERFMON_W1_T                                 perfmon_w1;	//0xC4D00214
	REG_DDRC_M0_PERFMON_W2_T                                 perfmon_w2;	//0xC4D00218
	REG_DDRC_M0_PERFMON_W3_T                                 perfmon_w3;	//0xC4D0021C
	REG_DDRC_M0_PERFMON_R0_T                                 perfmon_r0;	//0xC4D00220
	REG_DDRC_M0_PERFMON_R1_T                                 perfmon_r1;	//0xC4D00224
	REG_DDRC_M0_PERFMON_R2_T                                 perfmon_r2;	//0xC4D00228
	REG_DDRC_M0_PERFMON_R3_T                                 perfmon_r3;	//0xC4D0022C
	REG_DDRC_M0_LATMON_T                                         latmon;	//0xC4D00230
	UINT32                                                  reserved124;	//0xC4D00234
	UINT32                                                  reserved125;	//0xC4D00238
	UINT32                                                  reserved126;	//0xC4D0023C
	UINT32                                                  reserved127;	//0xC4D00240
	UINT32                                                  reserved128;	//0xC4D00244
	UINT32                                                  reserved129;	//0xC4D00248
	UINT32                                                  reserved130;	//0xC4D0024C
	UINT32                                                  reserved131;	//0xC4D00250
	UINT32                                                  reserved132;	//0xC4D00254
	UINT32                                                  reserved133;	//0xC4D00258
	UINT32                                                  reserved134;	//0xC4D0025C
	UINT32                                                  reserved135;	//0xC4D00260
	UINT32                                                  reserved136;	//0xC4D00264
	UINT32                                                  reserved137;	//0xC4D00268
	UINT32                                                  reserved138;	//0xC4D0026C
	UINT32                                                  reserved139;	//0xC4D00270
	UINT32                                                  reserved140;	//0xC4D00274
	UINT32                                                  reserved141;	//0xC4D00278
	UINT32                                                  reserved142;	//0xC4D0027C
	UINT32                                                  reserved143;	//0xC4D00280
	UINT32                                                  reserved144;	//0xC4D00284
	UINT32                                                  reserved145;	//0xC4D00288
	UINT32                                                  reserved146;	//0xC4D0028C
	UINT32                                                  reserved147;	//0xC4D00290
	UINT32                                                  reserved148;	//0xC4D00294
	UINT32                                                  reserved149;	//0xC4D00298
	UINT32                                                  reserved150;	//0xC4D0029C
	UINT32                                                  reserved151;	//0xC4D002A0
	UINT32                                                  reserved152;	//0xC4D002A4
	UINT32                                                  reserved153;	//0xC4D002A8
	UINT32                                                  reserved154;	//0xC4D002AC
	UINT32                                                  reserved155;	//0xC4D002B0
	UINT32                                                  reserved156;	//0xC4D002B4
	UINT32                                                  reserved157;	//0xC4D002B8
	UINT32                                                  reserved158;	//0xC4D002BC
	UINT32                                                  reserved159;	//0xC4D002C0
	UINT32                                                  reserved160;	//0xC4D002C4
	UINT32                                                  reserved161;	//0xC4D002C8
	UINT32                                                  reserved162;	//0xC4D002CC
	UINT32                                                  reserved163;	//0xC4D002D0
	UINT32                                                  reserved164;	//0xC4D002D4
	UINT32                                                  reserved165;	//0xC4D002D8
	UINT32                                                  reserved166;	//0xC4D002DC
	UINT32                                                  reserved167;	//0xC4D002E0
	UINT32                                                  reserved168;	//0xC4D002E4
	UINT32                                                  reserved169;	//0xC4D002E8
	UINT32                                                  reserved170;	//0xC4D002EC
	UINT32                                                  reserved171;	//0xC4D002F0
	UINT32                                                  reserved172;	//0xC4D002F4
	UINT32                                                  reserved173;	//0xC4D002F8
	UINT32                                                  reserved174;	//0xC4D002FC
	REG_DDRC_M0_DFS_T                                               dfs;	//0xC4D00300
	REG_DDRC_M0_DFS_RESULT_T                                 dfs_result;	//0xC4D00304
	UINT32                                                  reserved175;	//0xC4D00308
	UINT32                                                  reserved176;	//0xC4D0030C
	UINT32                                                  reserved177;	//0xC4D00310
	UINT32                                                  reserved178;	//0xC4D00314
	UINT32                                                  reserved179;	//0xC4D00318
	UINT32                                                  reserved180;	//0xC4D0031C
	UINT32                                                  reserved181;	//0xC4D00320
	UINT32                                                  reserved182;	//0xC4D00324
	UINT32                                                  reserved183;	//0xC4D00328
	UINT32                                                  reserved184;	//0xC4D0032C
	UINT32                                                  reserved185;	//0xC4D00330
	UINT32                                                  reserved186;	//0xC4D00334
	UINT32                                                  reserved187;	//0xC4D00338
	UINT32                                                  reserved188;	//0xC4D0033C
	UINT32                                                  reserved189;	//0xC4D00340
	UINT32                                                  reserved190;	//0xC4D00344
	UINT32                                                  reserved191;	//0xC4D00348
	UINT32                                                  reserved192;	//0xC4D0034C
	UINT32                                                  reserved193;	//0xC4D00350
	UINT32                                                  reserved194;	//0xC4D00354
	UINT32                                                  reserved195;	//0xC4D00358
	UINT32                                                  reserved196;	//0xC4D0035C
	UINT32                                                  reserved197;	//0xC4D00360
	UINT32                                                  reserved198;	//0xC4D00364
	UINT32                                                  reserved199;	//0xC4D00368
	UINT32                                                  reserved200;	//0xC4D0036C
	UINT32                                                  reserved201;	//0xC4D00370
	UINT32                                                  reserved202;	//0xC4D00374
	UINT32                                                  reserved203;	//0xC4D00378
	UINT32                                                  reserved204;	//0xC4D0037C
	UINT32                                                  reserved205;	//0xC4D00380
	UINT32                                                  reserved206;	//0xC4D00384
	UINT32                                                  reserved207;	//0xC4D00388
	UINT32                                                  reserved208;	//0xC4D0038C
	UINT32                                                  reserved209;	//0xC4D00390
	UINT32                                                  reserved210;	//0xC4D00394
	UINT32                                                  reserved211;	//0xC4D00398
	UINT32                                                  reserved212;	//0xC4D0039C
	UINT32                                                  reserved213;	//0xC4D003A0
	UINT32                                                  reserved214;	//0xC4D003A4
	UINT32                                                  reserved215;	//0xC4D003A8
	UINT32                                                  reserved216;	//0xC4D003AC
	UINT32                                                  reserved217;	//0xC4D003B0
	UINT32                                                  reserved218;	//0xC4D003B4
	UINT32                                                  reserved219;	//0xC4D003B8
	UINT32                                                  reserved220;	//0xC4D003BC
	UINT32                                                  reserved221;	//0xC4D003C0
	UINT32                                                  reserved222;	//0xC4D003C4
	UINT32                                                  reserved223;	//0xC4D003C8
	UINT32                                                  reserved224;	//0xC4D003CC
	UINT32                                                  reserved225;	//0xC4D003D0
	UINT32                                                  reserved226;	//0xC4D003D4
	UINT32                                                  reserved227;	//0xC4D003D8
	UINT32                                                  reserved228;	//0xC4D003DC
	UINT32                                                  reserved229;	//0xC4D003E0
	UINT32                                                  reserved230;	//0xC4D003E4
	UINT32                                                  reserved231;	//0xC4D003E8
	UINT32                                                  reserved232;	//0xC4D003EC
	UINT32                                                  reserved233;	//0xC4D003F0
	UINT32                                                  reserved234;	//0xC4D003F4
	UINT32                                                  reserved235;	//0xC4D003F8
	UINT32                                                  reserved236;	//0xC4D003FC
	REG_DDRC_M0_ADDR_MAP_T                                     addr_map;	//0xC4D00400
	REG_DDRC_M0_COMMON_T                                         common;	//0xC4D00404
	REG_DDRC_M0_DATA_ENC0_T                                   data_enc0;	//0xC4D00408
	REG_DDRC_M0_DATA_ENC1_T                                   data_enc1;	//0xC4D0040C
	UINT32                                                  reserved237;	//0xC4D00410
	UINT32                                                  reserved238;	//0xC4D00414
	UINT32                                                  reserved239;	//0xC4D00418
	UINT32                                                  reserved240;	//0xC4D0041C
	UINT32                                                  reserved241;	//0xC4D00420
	UINT32                                                  reserved242;	//0xC4D00424
	UINT32                                                  reserved243;	//0xC4D00428
	UINT32                                                  reserved244;	//0xC4D0042C
	UINT32                                                  reserved245;	//0xC4D00430
	UINT32                                                  reserved246;	//0xC4D00434
	UINT32                                                  reserved247;	//0xC4D00438
	UINT32                                                  reserved248;	//0xC4D0043C
	UINT32                                                  reserved249;	//0xC4D00440
	UINT32                                                  reserved250;	//0xC4D00444
	UINT32                                                  reserved251;	//0xC4D00448
	UINT32                                                  reserved252;	//0xC4D0044C
	UINT32                                                  reserved253;	//0xC4D00450
	UINT32                                                  reserved254;	//0xC4D00454
	UINT32                                                  reserved255;	//0xC4D00458
	UINT32                                                  reserved256;	//0xC4D0045C
	UINT32                                                  reserved257;	//0xC4D00460
	UINT32                                                  reserved258;	//0xC4D00464
	UINT32                                                  reserved259;	//0xC4D00468
	UINT32                                                  reserved260;	//0xC4D0046C
	UINT32                                                  reserved261;	//0xC4D00470
	UINT32                                                  reserved262;	//0xC4D00474
	UINT32                                                  reserved263;	//0xC4D00478
	UINT32                                                  reserved264;	//0xC4D0047C
	UINT32                                                  reserved265;	//0xC4D00480
	UINT32                                                  reserved266;	//0xC4D00484
	UINT32                                                  reserved267;	//0xC4D00488
	UINT32                                                  reserved268;	//0xC4D0048C
	UINT32                                                  reserved269;	//0xC4D00490
	UINT32                                                  reserved270;	//0xC4D00494
	UINT32                                                  reserved271;	//0xC4D00498
	UINT32                                                  reserved272;	//0xC4D0049C
	UINT32                                                  reserved273;	//0xC4D004A0
	UINT32                                                  reserved274;	//0xC4D004A4
	UINT32                                                  reserved275;	//0xC4D004A8
	UINT32                                                  reserved276;	//0xC4D004AC
	UINT32                                                  reserved277;	//0xC4D004B0
	UINT32                                                  reserved278;	//0xC4D004B4
	UINT32                                                  reserved279;	//0xC4D004B8
	UINT32                                                  reserved280;	//0xC4D004BC
	UINT32                                                  reserved281;	//0xC4D004C0
	UINT32                                                  reserved282;	//0xC4D004C4
	UINT32                                                  reserved283;	//0xC4D004C8
	UINT32                                                  reserved284;	//0xC4D004CC
	UINT32                                                  reserved285;	//0xC4D004D0
	UINT32                                                  reserved286;	//0xC4D004D4
	UINT32                                                  reserved287;	//0xC4D004D8
	UINT32                                                  reserved288;	//0xC4D004DC
	UINT32                                                  reserved289;	//0xC4D004E0
	UINT32                                                  reserved290;	//0xC4D004E4
	UINT32                                                  reserved291;	//0xC4D004E8
	UINT32                                                  reserved292;	//0xC4D004EC
	UINT32                                                  reserved293;	//0xC4D004F0
	UINT32                                                  reserved294;	//0xC4D004F4
	UINT32                                                  reserved295;	//0xC4D004F8
	UINT32                                                  reserved296;	//0xC4D004FC
	REG_DDRC_M0_RD_URG_T                                         rd_urg;	//0xC4D00500
	REG_DDRC_M0_WR_URG_T                                         wr_urg;	//0xC4D00504
	UINT32                                                  reserved297;	//0xC4D00508
	UINT32                                                  reserved298;	//0xC4D0050C
	UINT32                                                  reserved299;	//0xC4D00510
	UINT32                                                  reserved300;	//0xC4D00514
	UINT32                                                  reserved301;	//0xC4D00518
	UINT32                                                  reserved302;	//0xC4D0051C
	UINT32                                                  reserved303;	//0xC4D00520
	UINT32                                                  reserved304;	//0xC4D00524
	UINT32                                                  reserved305;	//0xC4D00528
	UINT32                                                  reserved306;	//0xC4D0052C
	UINT32                                                  reserved307;	//0xC4D00530
	UINT32                                                  reserved308;	//0xC4D00534
	UINT32                                                  reserved309;	//0xC4D00538
	UINT32                                                  reserved310;	//0xC4D0053C
	UINT32                                                  reserved311;	//0xC4D00540
	UINT32                                                  reserved312;	//0xC4D00544
	UINT32                                                  reserved313;	//0xC4D00548
	UINT32                                                  reserved314;	//0xC4D0054C
	UINT32                                                  reserved315;	//0xC4D00550
	UINT32                                                  reserved316;	//0xC4D00554
	UINT32                                                  reserved317;	//0xC4D00558
	UINT32                                                  reserved318;	//0xC4D0055C
	UINT32                                                  reserved319;	//0xC4D00560
	UINT32                                                  reserved320;	//0xC4D00564
	UINT32                                                  reserved321;	//0xC4D00568
	UINT32                                                  reserved322;	//0xC4D0056C
	UINT32                                                  reserved323;	//0xC4D00570
	UINT32                                                  reserved324;	//0xC4D00574
	UINT32                                                  reserved325;	//0xC4D00578
	UINT32                                                  reserved326;	//0xC4D0057C
	UINT32                                                  reserved327;	//0xC4D00580
	UINT32                                                  reserved328;	//0xC4D00584
	UINT32                                                  reserved329;	//0xC4D00588
	UINT32                                                  reserved330;	//0xC4D0058C
	UINT32                                                  reserved331;	//0xC4D00590
	UINT32                                                  reserved332;	//0xC4D00594
	UINT32                                                  reserved333;	//0xC4D00598
	UINT32                                                  reserved334;	//0xC4D0059C
	UINT32                                                  reserved335;	//0xC4D005A0
	UINT32                                                  reserved336;	//0xC4D005A4
	UINT32                                                  reserved337;	//0xC4D005A8
	UINT32                                                  reserved338;	//0xC4D005AC
	UINT32                                                  reserved339;	//0xC4D005B0
	UINT32                                                  reserved340;	//0xC4D005B4
	UINT32                                                  reserved341;	//0xC4D005B8
	UINT32                                                  reserved342;	//0xC4D005BC
	UINT32                                                  reserved343;	//0xC4D005C0
	UINT32                                                  reserved344;	//0xC4D005C4
	UINT32                                                  reserved345;	//0xC4D005C8
	UINT32                                                  reserved346;	//0xC4D005CC
	UINT32                                                  reserved347;	//0xC4D005D0
	UINT32                                                  reserved348;	//0xC4D005D4
	UINT32                                                  reserved349;	//0xC4D005D8
	UINT32                                                  reserved350;	//0xC4D005DC
	UINT32                                                  reserved351;	//0xC4D005E0
	UINT32                                                  reserved352;	//0xC4D005E4
	UINT32                                                  reserved353;	//0xC4D005E8
	UINT32                                                  reserved354;	//0xC4D005EC
	UINT32                                                  reserved355;	//0xC4D005F0
	UINT32                                                  reserved356;	//0xC4D005F4
	UINT32                                                  reserved357;	//0xC4D005F8
	UINT32                                                  reserved358;	//0xC4D005FC
	UINT32                                                  reserved359;	//0xC4D00600
	UINT32                                                  reserved360;	//0xC4D00604
	UINT32                                                  reserved361;	//0xC4D00608
	UINT32                                                  reserved362;	//0xC4D0060C
	UINT32                                                  reserved363;	//0xC4D00610
	UINT32                                                  reserved364;	//0xC4D00614
	UINT32                                                  reserved365;	//0xC4D00618
	UINT32                                                  reserved366;	//0xC4D0061C
	UINT32                                                  reserved367;	//0xC4D00620
	UINT32                                                  reserved368;	//0xC4D00624
	UINT32                                                  reserved369;	//0xC4D00628
	UINT32                                                  reserved370;	//0xC4D0062C
	UINT32                                                  reserved371;	//0xC4D00630
	UINT32                                                  reserved372;	//0xC4D00634
	UINT32                                                  reserved373;	//0xC4D00638
	UINT32                                                  reserved374;	//0xC4D0063C
	UINT32                                                  reserved375;	//0xC4D00640
	UINT32                                                  reserved376;	//0xC4D00644
	UINT32                                                  reserved377;	//0xC4D00648
	UINT32                                                  reserved378;	//0xC4D0064C
	UINT32                                                  reserved379;	//0xC4D00650
	UINT32                                                  reserved380;	//0xC4D00654
	UINT32                                                  reserved381;	//0xC4D00658
	UINT32                                                  reserved382;	//0xC4D0065C
	UINT32                                                  reserved383;	//0xC4D00660
	UINT32                                                  reserved384;	//0xC4D00664
	UINT32                                                  reserved385;	//0xC4D00668
	UINT32                                                  reserved386;	//0xC4D0066C
	UINT32                                                  reserved387;	//0xC4D00670
	UINT32                                                  reserved388;	//0xC4D00674
	UINT32                                                  reserved389;	//0xC4D00678
	UINT32                                                  reserved390;	//0xC4D0067C
	UINT32                                                  reserved391;	//0xC4D00680
	UINT32                                                  reserved392;	//0xC4D00684
	UINT32                                                  reserved393;	//0xC4D00688
	UINT32                                                  reserved394;	//0xC4D0068C
	UINT32                                                  reserved395;	//0xC4D00690
	UINT32                                                  reserved396;	//0xC4D00694
	UINT32                                                  reserved397;	//0xC4D00698
	UINT32                                                  reserved398;	//0xC4D0069C
	UINT32                                                  reserved399;	//0xC4D006A0
	UINT32                                                  reserved400;	//0xC4D006A4
	UINT32                                                  reserved401;	//0xC4D006A8
	UINT32                                                  reserved402;	//0xC4D006AC
	UINT32                                                  reserved403;	//0xC4D006B0
	UINT32                                                  reserved404;	//0xC4D006B4
	UINT32                                                  reserved405;	//0xC4D006B8
	UINT32                                                  reserved406;	//0xC4D006BC
	UINT32                                                  reserved407;	//0xC4D006C0
	UINT32                                                  reserved408;	//0xC4D006C4
	UINT32                                                  reserved409;	//0xC4D006C8
	UINT32                                                  reserved410;	//0xC4D006CC
	UINT32                                                  reserved411;	//0xC4D006D0
	UINT32                                                  reserved412;	//0xC4D006D4
	UINT32                                                  reserved413;	//0xC4D006D8
	UINT32                                                  reserved414;	//0xC4D006DC
	UINT32                                                  reserved415;	//0xC4D006E0
	UINT32                                                  reserved416;	//0xC4D006E4
	UINT32                                                  reserved417;	//0xC4D006E8
	UINT32                                                  reserved418;	//0xC4D006EC
	UINT32                                                  reserved419;	//0xC4D006F0
	UINT32                                                  reserved420;	//0xC4D006F4
	UINT32                                                  reserved421;	//0xC4D006F8
	UINT32                                                  reserved422;	//0xC4D006FC
	UINT32                                                  reserved423;	//0xC4D00700
	UINT32                                                  reserved424;	//0xC4D00704
	UINT32                                                  reserved425;	//0xC4D00708
	UINT32                                                  reserved426;	//0xC4D0070C
	UINT32                                                  reserved427;	//0xC4D00710
	UINT32                                                  reserved428;	//0xC4D00714
	UINT32                                                  reserved429;	//0xC4D00718
	UINT32                                                  reserved430;	//0xC4D0071C
	UINT32                                                  reserved431;	//0xC4D00720
	UINT32                                                  reserved432;	//0xC4D00724
	UINT32                                                  reserved433;	//0xC4D00728
	UINT32                                                  reserved434;	//0xC4D0072C
	UINT32                                                  reserved435;	//0xC4D00730
	UINT32                                                  reserved436;	//0xC4D00734
	UINT32                                                  reserved437;	//0xC4D00738
	UINT32                                                  reserved438;	//0xC4D0073C
	UINT32                                                  reserved439;	//0xC4D00740
	UINT32                                                  reserved440;	//0xC4D00744
	UINT32                                                  reserved441;	//0xC4D00748
	UINT32                                                  reserved442;	//0xC4D0074C
	UINT32                                                  reserved443;	//0xC4D00750
	UINT32                                                  reserved444;	//0xC4D00754
	UINT32                                                  reserved445;	//0xC4D00758
	UINT32                                                  reserved446;	//0xC4D0075C
	UINT32                                                  reserved447;	//0xC4D00760
	UINT32                                                  reserved448;	//0xC4D00764
	UINT32                                                  reserved449;	//0xC4D00768
	UINT32                                                  reserved450;	//0xC4D0076C
	UINT32                                                  reserved451;	//0xC4D00770
	UINT32                                                  reserved452;	//0xC4D00774
	UINT32                                                  reserved453;	//0xC4D00778
	UINT32                                                  reserved454;	//0xC4D0077C
	UINT32                                                  reserved455;	//0xC4D00780
	UINT32                                                  reserved456;	//0xC4D00784
	UINT32                                                  reserved457;	//0xC4D00788
	UINT32                                                  reserved458;	//0xC4D0078C
	UINT32                                                  reserved459;	//0xC4D00790
	UINT32                                                  reserved460;	//0xC4D00794
	UINT32                                                  reserved461;	//0xC4D00798
	UINT32                                                  reserved462;	//0xC4D0079C
	UINT32                                                  reserved463;	//0xC4D007A0
	UINT32                                                  reserved464;	//0xC4D007A4
	UINT32                                                  reserved465;	//0xC4D007A8
	UINT32                                                  reserved466;	//0xC4D007AC
	UINT32                                                  reserved467;	//0xC4D007B0
	UINT32                                                  reserved468;	//0xC4D007B4
	UINT32                                                  reserved469;	//0xC4D007B8
	UINT32                                                  reserved470;	//0xC4D007BC
	UINT32                                                  reserved471;	//0xC4D007C0
	UINT32                                                  reserved472;	//0xC4D007C4
	UINT32                                                  reserved473;	//0xC4D007C8
	UINT32                                                  reserved474;	//0xC4D007CC
	UINT32                                                  reserved475;	//0xC4D007D0
	UINT32                                                  reserved476;	//0xC4D007D4
	UINT32                                                  reserved477;	//0xC4D007D8
	UINT32                                                  reserved478;	//0xC4D007DC
	UINT32                                                  reserved479;	//0xC4D007E0
	UINT32                                                  reserved480;	//0xC4D007E4
	UINT32                                                  reserved481;	//0xC4D007E8
	UINT32                                                  reserved482;	//0xC4D007EC
	UINT32                                                  reserved483;	//0xC4D007F0
	UINT32                                                  reserved484;	//0xC4D007F4
	UINT32                                                  reserved485;	//0xC4D007F8
	UINT32                                                  reserved486;	//0xC4D007FC
	UINT32                                                  reserved487;	//0xC4D00800
	UINT32                                                  reserved488;	//0xC4D00804
	UINT32                                                  reserved489;	//0xC4D00808
	UINT32                                                  reserved490;	//0xC4D0080C
	UINT32                                                  reserved491;	//0xC4D00810
	UINT32                                                  reserved492;	//0xC4D00814
	UINT32                                                  reserved493;	//0xC4D00818
	UINT32                                                  reserved494;	//0xC4D0081C
	UINT32                                                  reserved495;	//0xC4D00820
	UINT32                                                  reserved496;	//0xC4D00824
	UINT32                                                  reserved497;	//0xC4D00828
	UINT32                                                  reserved498;	//0xC4D0082C
	UINT32                                                  reserved499;	//0xC4D00830
	UINT32                                                  reserved500;	//0xC4D00834
	UINT32                                                  reserved501;	//0xC4D00838
	UINT32                                                  reserved502;	//0xC4D0083C
	UINT32                                                  reserved503;	//0xC4D00840
	UINT32                                                  reserved504;	//0xC4D00844
	UINT32                                                  reserved505;	//0xC4D00848
	UINT32                                                  reserved506;	//0xC4D0084C
	UINT32                                                  reserved507;	//0xC4D00850
	UINT32                                                  reserved508;	//0xC4D00854
	UINT32                                                  reserved509;	//0xC4D00858
	UINT32                                                  reserved510;	//0xC4D0085C
	UINT32                                                  reserved511;	//0xC4D00860
	UINT32                                                  reserved512;	//0xC4D00864
	UINT32                                                  reserved513;	//0xC4D00868
	UINT32                                                  reserved514;	//0xC4D0086C
	UINT32                                                  reserved515;	//0xC4D00870
	UINT32                                                  reserved516;	//0xC4D00874
	UINT32                                                  reserved517;	//0xC4D00878
	UINT32                                                  reserved518;	//0xC4D0087C
	UINT32                                                  reserved519;	//0xC4D00880
	UINT32                                                  reserved520;	//0xC4D00884
	UINT32                                                  reserved521;	//0xC4D00888
	UINT32                                                  reserved522;	//0xC4D0088C
	UINT32                                                  reserved523;	//0xC4D00890
	UINT32                                                  reserved524;	//0xC4D00894
	UINT32                                                  reserved525;	//0xC4D00898
	UINT32                                                  reserved526;	//0xC4D0089C
	UINT32                                                  reserved527;	//0xC4D008A0
	UINT32                                                  reserved528;	//0xC4D008A4
	UINT32                                                  reserved529;	//0xC4D008A8
	UINT32                                                  reserved530;	//0xC4D008AC
	UINT32                                                  reserved531;	//0xC4D008B0
	UINT32                                                  reserved532;	//0xC4D008B4
	UINT32                                                  reserved533;	//0xC4D008B8
	UINT32                                                  reserved534;	//0xC4D008BC
	UINT32                                                  reserved535;	//0xC4D008C0
	UINT32                                                  reserved536;	//0xC4D008C4
	UINT32                                                  reserved537;	//0xC4D008C8
	UINT32                                                  reserved538;	//0xC4D008CC
	UINT32                                                  reserved539;	//0xC4D008D0
	UINT32                                                  reserved540;	//0xC4D008D4
	UINT32                                                  reserved541;	//0xC4D008D8
	UINT32                                                  reserved542;	//0xC4D008DC
	UINT32                                                  reserved543;	//0xC4D008E0
	UINT32                                                  reserved544;	//0xC4D008E4
	UINT32                                                  reserved545;	//0xC4D008E8
	UINT32                                                  reserved546;	//0xC4D008EC
	UINT32                                                  reserved547;	//0xC4D008F0
	UINT32                                                  reserved548;	//0xC4D008F4
	UINT32                                                  reserved549;	//0xC4D008F8
	UINT32                                                  reserved550;	//0xC4D008FC
	UINT32                                                  reserved551;	//0xC4D00900
	UINT32                                                  reserved552;	//0xC4D00904
	UINT32                                                  reserved553;	//0xC4D00908
	UINT32                                                  reserved554;	//0xC4D0090C
	UINT32                                                  reserved555;	//0xC4D00910
	UINT32                                                  reserved556;	//0xC4D00914
	UINT32                                                  reserved557;	//0xC4D00918
	UINT32                                                  reserved558;	//0xC4D0091C
	UINT32                                                  reserved559;	//0xC4D00920
	UINT32                                                  reserved560;	//0xC4D00924
	UINT32                                                  reserved561;	//0xC4D00928
	UINT32                                                  reserved562;	//0xC4D0092C
	UINT32                                                  reserved563;	//0xC4D00930
	UINT32                                                  reserved564;	//0xC4D00934
	UINT32                                                  reserved565;	//0xC4D00938
	UINT32                                                  reserved566;	//0xC4D0093C
	UINT32                                                  reserved567;	//0xC4D00940
	UINT32                                                  reserved568;	//0xC4D00944
	UINT32                                                  reserved569;	//0xC4D00948
	UINT32                                                  reserved570;	//0xC4D0094C
	UINT32                                                  reserved571;	//0xC4D00950
	UINT32                                                  reserved572;	//0xC4D00954
	UINT32                                                  reserved573;	//0xC4D00958
	UINT32                                                  reserved574;	//0xC4D0095C
	UINT32                                                  reserved575;	//0xC4D00960
	UINT32                                                  reserved576;	//0xC4D00964
	UINT32                                                  reserved577;	//0xC4D00968
	UINT32                                                  reserved578;	//0xC4D0096C
	UINT32                                                  reserved579;	//0xC4D00970
	UINT32                                                  reserved580;	//0xC4D00974
	UINT32                                                  reserved581;	//0xC4D00978
	UINT32                                                  reserved582;	//0xC4D0097C
	UINT32                                                  reserved583;	//0xC4D00980
	UINT32                                                  reserved584;	//0xC4D00984
	UINT32                                                  reserved585;	//0xC4D00988
	UINT32                                                  reserved586;	//0xC4D0098C
	UINT32                                                  reserved587;	//0xC4D00990
	UINT32                                                  reserved588;	//0xC4D00994
	UINT32                                                  reserved589;	//0xC4D00998
	UINT32                                                  reserved590;	//0xC4D0099C
	UINT32                                                  reserved591;	//0xC4D009A0
	UINT32                                                  reserved592;	//0xC4D009A4
	UINT32                                                  reserved593;	//0xC4D009A8
	UINT32                                                  reserved594;	//0xC4D009AC
	UINT32                                                  reserved595;	//0xC4D009B0
	UINT32                                                  reserved596;	//0xC4D009B4
	UINT32                                                  reserved597;	//0xC4D009B8
	UINT32                                                  reserved598;	//0xC4D009BC
	UINT32                                                  reserved599;	//0xC4D009C0
	UINT32                                                  reserved600;	//0xC4D009C4
	UINT32                                                  reserved601;	//0xC4D009C8
	UINT32                                                  reserved602;	//0xC4D009CC
	UINT32                                                  reserved603;	//0xC4D009D0
	UINT32                                                  reserved604;	//0xC4D009D4
	UINT32                                                  reserved605;	//0xC4D009D8
	UINT32                                                  reserved606;	//0xC4D009DC
	UINT32                                                  reserved607;	//0xC4D009E0
	UINT32                                                  reserved608;	//0xC4D009E4
	UINT32                                                  reserved609;	//0xC4D009E8
	UINT32                                                  reserved610;	//0xC4D009EC
	UINT32                                                  reserved611;	//0xC4D009F0
	UINT32                                                  reserved612;	//0xC4D009F4
	UINT32                                                  reserved613;	//0xC4D009F8
	UINT32                                                  reserved614;	//0xC4D009FC
	UINT32                                                  reserved615;	//0xC4D00A00
	UINT32                                                  reserved616;	//0xC4D00A04
	UINT32                                                  reserved617;	//0xC4D00A08
	UINT32                                                  reserved618;	//0xC4D00A0C
	UINT32                                                  reserved619;	//0xC4D00A10
	UINT32                                                  reserved620;	//0xC4D00A14
	UINT32                                                  reserved621;	//0xC4D00A18
	UINT32                                                  reserved622;	//0xC4D00A1C
	UINT32                                                  reserved623;	//0xC4D00A20
	UINT32                                                  reserved624;	//0xC4D00A24
	UINT32                                                  reserved625;	//0xC4D00A28
	UINT32                                                  reserved626;	//0xC4D00A2C
	UINT32                                                  reserved627;	//0xC4D00A30
	UINT32                                                  reserved628;	//0xC4D00A34
	UINT32                                                  reserved629;	//0xC4D00A38
	UINT32                                                  reserved630;	//0xC4D00A3C
	UINT32                                                  reserved631;	//0xC4D00A40
	UINT32                                                  reserved632;	//0xC4D00A44
	UINT32                                                  reserved633;	//0xC4D00A48
	UINT32                                                  reserved634;	//0xC4D00A4C
	UINT32                                                  reserved635;	//0xC4D00A50
	UINT32                                                  reserved636;	//0xC4D00A54
	UINT32                                                  reserved637;	//0xC4D00A58
	UINT32                                                  reserved638;	//0xC4D00A5C
	UINT32                                                  reserved639;	//0xC4D00A60
	UINT32                                                  reserved640;	//0xC4D00A64
	UINT32                                                  reserved641;	//0xC4D00A68
	UINT32                                                  reserved642;	//0xC4D00A6C
	UINT32                                                  reserved643;	//0xC4D00A70
	UINT32                                                  reserved644;	//0xC4D00A74
	UINT32                                                  reserved645;	//0xC4D00A78
	UINT32                                                  reserved646;	//0xC4D00A7C
	UINT32                                                  reserved647;	//0xC4D00A80
	UINT32                                                  reserved648;	//0xC4D00A84
	UINT32                                                  reserved649;	//0xC4D00A88
	UINT32                                                  reserved650;	//0xC4D00A8C
	UINT32                                                  reserved651;	//0xC4D00A90
	UINT32                                                  reserved652;	//0xC4D00A94
	UINT32                                                  reserved653;	//0xC4D00A98
	UINT32                                                  reserved654;	//0xC4D00A9C
	UINT32                                                  reserved655;	//0xC4D00AA0
	UINT32                                                  reserved656;	//0xC4D00AA4
	UINT32                                                  reserved657;	//0xC4D00AA8
	UINT32                                                  reserved658;	//0xC4D00AAC
	UINT32                                                  reserved659;	//0xC4D00AB0
	UINT32                                                  reserved660;	//0xC4D00AB4
	UINT32                                                  reserved661;	//0xC4D00AB8
	UINT32                                                  reserved662;	//0xC4D00ABC
	UINT32                                                  reserved663;	//0xC4D00AC0
	UINT32                                                  reserved664;	//0xC4D00AC4
	UINT32                                                  reserved665;	//0xC4D00AC8
	UINT32                                                  reserved666;	//0xC4D00ACC
	UINT32                                                  reserved667;	//0xC4D00AD0
	UINT32                                                  reserved668;	//0xC4D00AD4
	UINT32                                                  reserved669;	//0xC4D00AD8
	UINT32                                                  reserved670;	//0xC4D00ADC
	UINT32                                                  reserved671;	//0xC4D00AE0
	UINT32                                                  reserved672;	//0xC4D00AE4
	UINT32                                                  reserved673;	//0xC4D00AE8
	UINT32                                                  reserved674;	//0xC4D00AEC
	UINT32                                                  reserved675;	//0xC4D00AF0
	UINT32                                                  reserved676;	//0xC4D00AF4
	UINT32                                                  reserved677;	//0xC4D00AF8
	UINT32                                                  reserved678;	//0xC4D00AFC
	UINT32                                                  reserved679;	//0xC4D00B00
	UINT32                                                  reserved680;	//0xC4D00B04
	UINT32                                                  reserved681;	//0xC4D00B08
	UINT32                                                  reserved682;	//0xC4D00B0C
	UINT32                                                  reserved683;	//0xC4D00B10
	UINT32                                                  reserved684;	//0xC4D00B14
	UINT32                                                  reserved685;	//0xC4D00B18
	UINT32                                                  reserved686;	//0xC4D00B1C
	UINT32                                                  reserved687;	//0xC4D00B20
	UINT32                                                  reserved688;	//0xC4D00B24
	UINT32                                                  reserved689;	//0xC4D00B28
	UINT32                                                  reserved690;	//0xC4D00B2C
	UINT32                                                  reserved691;	//0xC4D00B30
	UINT32                                                  reserved692;	//0xC4D00B34
	UINT32                                                  reserved693;	//0xC4D00B38
	UINT32                                                  reserved694;	//0xC4D00B3C
	UINT32                                                  reserved695;	//0xC4D00B40
	UINT32                                                  reserved696;	//0xC4D00B44
	UINT32                                                  reserved697;	//0xC4D00B48
	UINT32                                                  reserved698;	//0xC4D00B4C
	UINT32                                                  reserved699;	//0xC4D00B50
	UINT32                                                  reserved700;	//0xC4D00B54
	UINT32                                                  reserved701;	//0xC4D00B58
	UINT32                                                  reserved702;	//0xC4D00B5C
	UINT32                                                  reserved703;	//0xC4D00B60
	UINT32                                                  reserved704;	//0xC4D00B64
	UINT32                                                  reserved705;	//0xC4D00B68
	UINT32                                                  reserved706;	//0xC4D00B6C
	UINT32                                                  reserved707;	//0xC4D00B70
	UINT32                                                  reserved708;	//0xC4D00B74
	UINT32                                                  reserved709;	//0xC4D00B78
	UINT32                                                  reserved710;	//0xC4D00B7C
	UINT32                                                  reserved711;	//0xC4D00B80
	UINT32                                                  reserved712;	//0xC4D00B84
	UINT32                                                  reserved713;	//0xC4D00B88
	UINT32                                                  reserved714;	//0xC4D00B8C
	UINT32                                                  reserved715;	//0xC4D00B90
	UINT32                                                  reserved716;	//0xC4D00B94
	UINT32                                                  reserved717;	//0xC4D00B98
	UINT32                                                  reserved718;	//0xC4D00B9C
	UINT32                                                  reserved719;	//0xC4D00BA0
	UINT32                                                  reserved720;	//0xC4D00BA4
	UINT32                                                  reserved721;	//0xC4D00BA8
	UINT32                                                  reserved722;	//0xC4D00BAC
	UINT32                                                  reserved723;	//0xC4D00BB0
	UINT32                                                  reserved724;	//0xC4D00BB4
	UINT32                                                  reserved725;	//0xC4D00BB8
	UINT32                                                  reserved726;	//0xC4D00BBC
	UINT32                                                  reserved727;	//0xC4D00BC0
	UINT32                                                  reserved728;	//0xC4D00BC4
	UINT32                                                  reserved729;	//0xC4D00BC8
	UINT32                                                  reserved730;	//0xC4D00BCC
	UINT32                                                  reserved731;	//0xC4D00BD0
	UINT32                                                  reserved732;	//0xC4D00BD4
	UINT32                                                  reserved733;	//0xC4D00BD8
	UINT32                                                  reserved734;	//0xC4D00BDC
	UINT32                                                  reserved735;	//0xC4D00BE0
	UINT32                                                  reserved736;	//0xC4D00BE4
	UINT32                                                  reserved737;	//0xC4D00BE8
	UINT32                                                  reserved738;	//0xC4D00BEC
	UINT32                                                  reserved739;	//0xC4D00BF0
	UINT32                                                  reserved740;	//0xC4D00BF4
	UINT32                                                  reserved741;	//0xC4D00BF8
	UINT32                                                  reserved742;	//0xC4D00BFC
	UINT32                                                  reserved743;	//0xC4D00C00
	UINT32                                                  reserved744;	//0xC4D00C04
	UINT32                                                  reserved745;	//0xC4D00C08
	UINT32                                                  reserved746;	//0xC4D00C0C
	UINT32                                                  reserved747;	//0xC4D00C10
	UINT32                                                  reserved748;	//0xC4D00C14
	UINT32                                                  reserved749;	//0xC4D00C18
	UINT32                                                  reserved750;	//0xC4D00C1C
	UINT32                                                  reserved751;	//0xC4D00C20
	UINT32                                                  reserved752;	//0xC4D00C24
	UINT32                                                  reserved753;	//0xC4D00C28
	UINT32                                                  reserved754;	//0xC4D00C2C
	UINT32                                                  reserved755;	//0xC4D00C30
	UINT32                                                  reserved756;	//0xC4D00C34
	UINT32                                                  reserved757;	//0xC4D00C38
	UINT32                                                  reserved758;	//0xC4D00C3C
	UINT32                                                  reserved759;	//0xC4D00C40
	UINT32                                                  reserved760;	//0xC4D00C44
	UINT32                                                  reserved761;	//0xC4D00C48
	UINT32                                                  reserved762;	//0xC4D00C4C
	UINT32                                                  reserved763;	//0xC4D00C50
	UINT32                                                  reserved764;	//0xC4D00C54
	UINT32                                                  reserved765;	//0xC4D00C58
	UINT32                                                  reserved766;	//0xC4D00C5C
	UINT32                                                  reserved767;	//0xC4D00C60
	UINT32                                                  reserved768;	//0xC4D00C64
	UINT32                                                  reserved769;	//0xC4D00C68
	UINT32                                                  reserved770;	//0xC4D00C6C
	UINT32                                                  reserved771;	//0xC4D00C70
	UINT32                                                  reserved772;	//0xC4D00C74
	UINT32                                                  reserved773;	//0xC4D00C78
	UINT32                                                  reserved774;	//0xC4D00C7C
	UINT32                                                  reserved775;	//0xC4D00C80
	UINT32                                                  reserved776;	//0xC4D00C84
	UINT32                                                  reserved777;	//0xC4D00C88
	UINT32                                                  reserved778;	//0xC4D00C8C
	UINT32                                                  reserved779;	//0xC4D00C90
	UINT32                                                  reserved780;	//0xC4D00C94
	UINT32                                                  reserved781;	//0xC4D00C98
	UINT32                                                  reserved782;	//0xC4D00C9C
	UINT32                                                  reserved783;	//0xC4D00CA0
	UINT32                                                  reserved784;	//0xC4D00CA4
	UINT32                                                  reserved785;	//0xC4D00CA8
	UINT32                                                  reserved786;	//0xC4D00CAC
	UINT32                                                  reserved787;	//0xC4D00CB0
	UINT32                                                  reserved788;	//0xC4D00CB4
	UINT32                                                  reserved789;	//0xC4D00CB8
	UINT32                                                  reserved790;	//0xC4D00CBC
	UINT32                                                  reserved791;	//0xC4D00CC0
	UINT32                                                  reserved792;	//0xC4D00CC4
	UINT32                                                  reserved793;	//0xC4D00CC8
	UINT32                                                  reserved794;	//0xC4D00CCC
	UINT32                                                  reserved795;	//0xC4D00CD0
	UINT32                                                  reserved796;	//0xC4D00CD4
	UINT32                                                  reserved797;	//0xC4D00CD8
	UINT32                                                  reserved798;	//0xC4D00CDC
	UINT32                                                  reserved799;	//0xC4D00CE0
	UINT32                                                  reserved800;	//0xC4D00CE4
	UINT32                                                  reserved801;	//0xC4D00CE8
	UINT32                                                  reserved802;	//0xC4D00CEC
	UINT32                                                  reserved803;	//0xC4D00CF0
	UINT32                                                  reserved804;	//0xC4D00CF4
	UINT32                                                  reserved805;	//0xC4D00CF8
	UINT32                                                  reserved806;	//0xC4D00CFC
	UINT32                                                  reserved807;	//0xC4D00D00
	UINT32                                                  reserved808;	//0xC4D00D04
	UINT32                                                  reserved809;	//0xC4D00D08
	UINT32                                                  reserved810;	//0xC4D00D0C
	UINT32                                                  reserved811;	//0xC4D00D10
	UINT32                                                  reserved812;	//0xC4D00D14
	UINT32                                                  reserved813;	//0xC4D00D18
	UINT32                                                  reserved814;	//0xC4D00D1C
	UINT32                                                  reserved815;	//0xC4D00D20
	UINT32                                                  reserved816;	//0xC4D00D24
	UINT32                                                  reserved817;	//0xC4D00D28
	UINT32                                                  reserved818;	//0xC4D00D2C
	UINT32                                                  reserved819;	//0xC4D00D30
	UINT32                                                  reserved820;	//0xC4D00D34
	UINT32                                                  reserved821;	//0xC4D00D38
	UINT32                                                  reserved822;	//0xC4D00D3C
	UINT32                                                  reserved823;	//0xC4D00D40
	UINT32                                                  reserved824;	//0xC4D00D44
	UINT32                                                  reserved825;	//0xC4D00D48
	UINT32                                                  reserved826;	//0xC4D00D4C
	UINT32                                                  reserved827;	//0xC4D00D50
	UINT32                                                  reserved828;	//0xC4D00D54
	UINT32                                                  reserved829;	//0xC4D00D58
	UINT32                                                  reserved830;	//0xC4D00D5C
	UINT32                                                  reserved831;	//0xC4D00D60
	UINT32                                                  reserved832;	//0xC4D00D64
	UINT32                                                  reserved833;	//0xC4D00D68
	UINT32                                                  reserved834;	//0xC4D00D6C
	UINT32                                                  reserved835;	//0xC4D00D70
	UINT32                                                  reserved836;	//0xC4D00D74
	UINT32                                                  reserved837;	//0xC4D00D78
	UINT32                                                  reserved838;	//0xC4D00D7C
	UINT32                                                  reserved839;	//0xC4D00D80
	UINT32                                                  reserved840;	//0xC4D00D84
	UINT32                                                  reserved841;	//0xC4D00D88
	UINT32                                                  reserved842;	//0xC4D00D8C
	UINT32                                                  reserved843;	//0xC4D00D90
	UINT32                                                  reserved844;	//0xC4D00D94
	UINT32                                                  reserved845;	//0xC4D00D98
	UINT32                                                  reserved846;	//0xC4D00D9C
	UINT32                                                  reserved847;	//0xC4D00DA0
	UINT32                                                  reserved848;	//0xC4D00DA4
	UINT32                                                  reserved849;	//0xC4D00DA8
	UINT32                                                  reserved850;	//0xC4D00DAC
	UINT32                                                  reserved851;	//0xC4D00DB0
	UINT32                                                  reserved852;	//0xC4D00DB4
	UINT32                                                  reserved853;	//0xC4D00DB8
	UINT32                                                  reserved854;	//0xC4D00DBC
	UINT32                                                  reserved855;	//0xC4D00DC0
	UINT32                                                  reserved856;	//0xC4D00DC4
	UINT32                                                  reserved857;	//0xC4D00DC8
	UINT32                                                  reserved858;	//0xC4D00DCC
	UINT32                                                  reserved859;	//0xC4D00DD0
	UINT32                                                  reserved860;	//0xC4D00DD4
	UINT32                                                  reserved861;	//0xC4D00DD8
	UINT32                                                  reserved862;	//0xC4D00DDC
	UINT32                                                  reserved863;	//0xC4D00DE0
	UINT32                                                  reserved864;	//0xC4D00DE4
	UINT32                                                  reserved865;	//0xC4D00DE8
	UINT32                                                  reserved866;	//0xC4D00DEC
	UINT32                                                  reserved867;	//0xC4D00DF0
	UINT32                                                  reserved868;	//0xC4D00DF4
	UINT32                                                  reserved869;	//0xC4D00DF8
	UINT32                                                  reserved870;	//0xC4D00DFC
	UINT32                                                  reserved871;	//0xC4D00E00
	UINT32                                                  reserved872;	//0xC4D00E04
	UINT32                                                  reserved873;	//0xC4D00E08
	UINT32                                                  reserved874;	//0xC4D00E0C
	UINT32                                                  reserved875;	//0xC4D00E10
	UINT32                                                  reserved876;	//0xC4D00E14
	UINT32                                                  reserved877;	//0xC4D00E18
	UINT32                                                  reserved878;	//0xC4D00E1C
	UINT32                                                  reserved879;	//0xC4D00E20
	UINT32                                                  reserved880;	//0xC4D00E24
	UINT32                                                  reserved881;	//0xC4D00E28
	UINT32                                                  reserved882;	//0xC4D00E2C
	UINT32                                                  reserved883;	//0xC4D00E30
	UINT32                                                  reserved884;	//0xC4D00E34
	UINT32                                                  reserved885;	//0xC4D00E38
	UINT32                                                  reserved886;	//0xC4D00E3C
	UINT32                                                  reserved887;	//0xC4D00E40
	UINT32                                                  reserved888;	//0xC4D00E44
	UINT32                                                  reserved889;	//0xC4D00E48
	UINT32                                                  reserved890;	//0xC4D00E4C
	UINT32                                                  reserved891;	//0xC4D00E50
	UINT32                                                  reserved892;	//0xC4D00E54
	UINT32                                                  reserved893;	//0xC4D00E58
	UINT32                                                  reserved894;	//0xC4D00E5C
	UINT32                                                  reserved895;	//0xC4D00E60
	UINT32                                                  reserved896;	//0xC4D00E64
	UINT32                                                  reserved897;	//0xC4D00E68
	UINT32                                                  reserved898;	//0xC4D00E6C
	UINT32                                                  reserved899;	//0xC4D00E70
	UINT32                                                  reserved900;	//0xC4D00E74
	UINT32                                                  reserved901;	//0xC4D00E78
	UINT32                                                  reserved902;	//0xC4D00E7C
	UINT32                                                  reserved903;	//0xC4D00E80
	UINT32                                                  reserved904;	//0xC4D00E84
	UINT32                                                  reserved905;	//0xC4D00E88
	UINT32                                                  reserved906;	//0xC4D00E8C
	UINT32                                                  reserved907;	//0xC4D00E90
	UINT32                                                  reserved908;	//0xC4D00E94
	UINT32                                                  reserved909;	//0xC4D00E98
	UINT32                                                  reserved910;	//0xC4D00E9C
	UINT32                                                  reserved911;	//0xC4D00EA0
	UINT32                                                  reserved912;	//0xC4D00EA4
	UINT32                                                  reserved913;	//0xC4D00EA8
	UINT32                                                  reserved914;	//0xC4D00EAC
	UINT32                                                  reserved915;	//0xC4D00EB0
	UINT32                                                  reserved916;	//0xC4D00EB4
	UINT32                                                  reserved917;	//0xC4D00EB8
	UINT32                                                  reserved918;	//0xC4D00EBC
	UINT32                                                  reserved919;	//0xC4D00EC0
	UINT32                                                  reserved920;	//0xC4D00EC4
	UINT32                                                  reserved921;	//0xC4D00EC8
	UINT32                                                  reserved922;	//0xC4D00ECC
	UINT32                                                  reserved923;	//0xC4D00ED0
	UINT32                                                  reserved924;	//0xC4D00ED4
	UINT32                                                  reserved925;	//0xC4D00ED8
	UINT32                                                  reserved926;	//0xC4D00EDC
	UINT32                                                  reserved927;	//0xC4D00EE0
	UINT32                                                  reserved928;	//0xC4D00EE4
	UINT32                                                  reserved929;	//0xC4D00EE8
	UINT32                                                  reserved930;	//0xC4D00EEC
	UINT32                                                  reserved931;	//0xC4D00EF0
	UINT32                                                  reserved932;	//0xC4D00EF4
	UINT32                                                  reserved933;	//0xC4D00EF8
	UINT32                                                  reserved934;	//0xC4D00EFC
	UINT32                                                  reserved935;	//0xC4D00F00
	UINT32                                                  reserved936;	//0xC4D00F04
	UINT32                                                  reserved937;	//0xC4D00F08
	UINT32                                                  reserved938;	//0xC4D00F0C
	UINT32                                                  reserved939;	//0xC4D00F10
	UINT32                                                  reserved940;	//0xC4D00F14
	UINT32                                                  reserved941;	//0xC4D00F18
	UINT32                                                  reserved942;	//0xC4D00F1C
	UINT32                                                  reserved943;	//0xC4D00F20
	UINT32                                                  reserved944;	//0xC4D00F24
	UINT32                                                  reserved945;	//0xC4D00F28
	UINT32                                                  reserved946;	//0xC4D00F2C
	UINT32                                                  reserved947;	//0xC4D00F30
	UINT32                                                  reserved948;	//0xC4D00F34
	UINT32                                                  reserved949;	//0xC4D00F38
	UINT32                                                  reserved950;	//0xC4D00F3C
	UINT32                                                  reserved951;	//0xC4D00F40
	UINT32                                                  reserved952;	//0xC4D00F44
	UINT32                                                  reserved953;	//0xC4D00F48
	UINT32                                                  reserved954;	//0xC4D00F4C
	UINT32                                                  reserved955;	//0xC4D00F50
	UINT32                                                  reserved956;	//0xC4D00F54
	UINT32                                                  reserved957;	//0xC4D00F58
	UINT32                                                  reserved958;	//0xC4D00F5C
	UINT32                                                  reserved959;	//0xC4D00F60
	UINT32                                                  reserved960;	//0xC4D00F64
	UINT32                                                  reserved961;	//0xC4D00F68
	UINT32                                                  reserved962;	//0xC4D00F6C
	UINT32                                                  reserved963;	//0xC4D00F70
	UINT32                                                  reserved964;	//0xC4D00F74
	UINT32                                                  reserved965;	//0xC4D00F78
	UINT32                                                  reserved966;	//0xC4D00F7C
	UINT32                                                  reserved967;	//0xC4D00F80
	UINT32                                                  reserved968;	//0xC4D00F84
	UINT32                                                  reserved969;	//0xC4D00F88
	UINT32                                                  reserved970;	//0xC4D00F8C
	UINT32                                                  reserved971;	//0xC4D00F90
	UINT32                                                  reserved972;	//0xC4D00F94
	UINT32                                                  reserved973;	//0xC4D00F98
	UINT32                                                  reserved974;	//0xC4D00F9C
	UINT32                                                  reserved975;	//0xC4D00FA0
	UINT32                                                  reserved976;	//0xC4D00FA4
	UINT32                                                  reserved977;	//0xC4D00FA8
	UINT32                                                  reserved978;	//0xC4D00FAC
	UINT32                                                  reserved979;	//0xC4D00FB0
	UINT32                                                  reserved980;	//0xC4D00FB4
	UINT32                                                  reserved981;	//0xC4D00FB8
	UINT32                                                  reserved982;	//0xC4D00FBC
	UINT32                                                  reserved983;	//0xC4D00FC0
	UINT32                                                  reserved984;	//0xC4D00FC4
	UINT32                                                  reserved985;	//0xC4D00FC8
	UINT32                                                  reserved986;	//0xC4D00FCC
	UINT32                                                  reserved987;	//0xC4D00FD0
	UINT32                                                  reserved988;	//0xC4D00FD4
	UINT32                                                  reserved989;	//0xC4D00FD8
	UINT32                                                  reserved990;	//0xC4D00FDC
	UINT32                                                  reserved991;	//0xC4D00FE0
	UINT32                                                  reserved992;	//0xC4D00FE4
	UINT32                                                  reserved993;	//0xC4D00FE8
	UINT32                                                  reserved994;	//0xC4D00FEC
	UINT32                                                  reserved995;	//0xC4D00FF0
	UINT32                                                  reserved996;	//0xC4D00FF4
	UINT32                                                  reserved997;	//0xC4D00FF8
	UINT32                                                  reserved998;	//0xC4D00FFC
	REG_DDRC_M0_FIFO_RDY_T                                     fifo_rdy;	//0xC4D01000
	REG_DDRC_M0_FIFO_STATUS_T                               fifo_status;	//0xC4D01004
	REG_DDRC_M0_FIFO_CONF_T                                   fifo_conf;	//0xC4D01008
	UINT32                                                  reserved999;	//0xC4D0100C
	REG_DDRC_M0_LIMITER_EN_T                                 limiter_en;	//0xC4D01010
	REG_DDRC_M0_LIMITER_AW_THR_T                         limiter_aw_thr;	//0xC4D01014
	REG_DDRC_M0_LIMITER_W_THR_T                           limiter_w_thr;	//0xC4D01018
	UINT32                                                 reserved1000;	//0xC4D0101C
	UINT32                                                 reserved1001;	//0xC4D01020
	REG_DDRC_M0_LIMITER_AR_THR_T                         limiter_ar_thr;	//0xC4D01024
	REG_DDRC_M0_LIMITER_R_THR_T                           limiter_r_thr;	//0xC4D01028
	UINT32                                                 reserved1002;	//0xC4D0102C
	UINT32                                                 reserved1003;	//0xC4D01030
	UINT32                                                 reserved1004;	//0xC4D01034
	UINT32                                                 reserved1005;	//0xC4D01038
	UINT32                                                 reserved1006;	//0xC4D0103C
	UINT32                                                 reserved1007;	//0xC4D01040
	UINT32                                                 reserved1008;	//0xC4D01044
	UINT32                                                 reserved1009;	//0xC4D01048
	UINT32                                                 reserved1010;	//0xC4D0104C
	UINT32                                                 reserved1011;	//0xC4D01050
	UINT32                                                 reserved1012;	//0xC4D01054
	UINT32                                                 reserved1013;	//0xC4D01058
	UINT32                                                 reserved1014;	//0xC4D0105C
	UINT32                                                 reserved1015;	//0xC4D01060
	UINT32                                                 reserved1016;	//0xC4D01064
	UINT32                                                 reserved1017;	//0xC4D01068
	UINT32                                                 reserved1018;	//0xC4D0106C
	UINT32                                                 reserved1019;	//0xC4D01070
	UINT32                                                 reserved1020;	//0xC4D01074
	UINT32                                                 reserved1021;	//0xC4D01078
	UINT32                                                 reserved1022;	//0xC4D0107C
	UINT32                                                 reserved1023;	//0xC4D01080
	UINT32                                                 reserved1024;	//0xC4D01084
	UINT32                                                 reserved1025;	//0xC4D01088
	UINT32                                                 reserved1026;	//0xC4D0108C
	UINT32                                                 reserved1027;	//0xC4D01090
	UINT32                                                 reserved1028;	//0xC4D01094
	UINT32                                                 reserved1029;	//0xC4D01098
	UINT32                                                 reserved1030;	//0xC4D0109C
	UINT32                                                 reserved1031;	//0xC4D010A0
	UINT32                                                 reserved1032;	//0xC4D010A4
	UINT32                                                 reserved1033;	//0xC4D010A8
	UINT32                                                 reserved1034;	//0xC4D010AC
	UINT32                                                 reserved1035;	//0xC4D010B0
	UINT32                                                 reserved1036;	//0xC4D010B4
	UINT32                                                 reserved1037;	//0xC4D010B8
	UINT32                                                 reserved1038;	//0xC4D010BC
	UINT32                                                 reserved1039;	//0xC4D010C0
	UINT32                                                 reserved1040;	//0xC4D010C4
	UINT32                                                 reserved1041;	//0xC4D010C8
	UINT32                                                 reserved1042;	//0xC4D010CC
	UINT32                                                 reserved1043;	//0xC4D010D0
	UINT32                                                 reserved1044;	//0xC4D010D4
	UINT32                                                 reserved1045;	//0xC4D010D8
	UINT32                                                 reserved1046;	//0xC4D010DC
	UINT32                                                 reserved1047;	//0xC4D010E0
	UINT32                                                 reserved1048;	//0xC4D010E4
	UINT32                                                 reserved1049;	//0xC4D010E8
	UINT32                                                 reserved1050;	//0xC4D010EC
	UINT32                                                 reserved1051;	//0xC4D010F0
	UINT32                                                 reserved1052;	//0xC4D010F4
	UINT32                                                 reserved1053;	//0xC4D010F8
	UINT32                                                 reserved1054;	//0xC4D010FC
	REG_DDRC_M0_FIFO_MUX_T                                     fifo_mux;	//0xC4D01100
	REG_DDRC_M0_FIFO_MUX_MAX_T                             fifo_mux_max;	//0xC4D01104
	REG_DDRC_M0_FIFO_MUX_WR_PRT_T                       fifo_mux_wr_prt;	//0xC4D01108
	REG_DDRC_M0_FIFO_MUX_RD_PRT_T                       fifo_mux_rd_prt;	//0xC4D0110C
	REG_DDRC_M0_FIFO_MUX_PRT_MAX_T                     fifo_mux_prt_max;	//0xC4D01110
	UINT32                                                 reserved1055;	//0xC4D01114
	UINT32                                                 reserved1056;	//0xC4D01118
	UINT32                                                 reserved1057;	//0xC4D0111C
	UINT32                                                 reserved1058;	//0xC4D01120
	UINT32                                                 reserved1059;	//0xC4D01124
	UINT32                                                 reserved1060;	//0xC4D01128
	UINT32                                                 reserved1061;	//0xC4D0112C
	UINT32                                                 reserved1062;	//0xC4D01130
	UINT32                                                 reserved1063;	//0xC4D01134
	UINT32                                                 reserved1064;	//0xC4D01138
	UINT32                                                 reserved1065;	//0xC4D0113C
	UINT32                                                 reserved1066;	//0xC4D01140
	UINT32                                                 reserved1067;	//0xC4D01144
	UINT32                                                 reserved1068;	//0xC4D01148
	UINT32                                                 reserved1069;	//0xC4D0114C
	UINT32                                                 reserved1070;	//0xC4D01150
	UINT32                                                 reserved1071;	//0xC4D01154
	UINT32                                                 reserved1072;	//0xC4D01158
	UINT32                                                 reserved1073;	//0xC4D0115C
	UINT32                                                 reserved1074;	//0xC4D01160
	UINT32                                                 reserved1075;	//0xC4D01164
	UINT32                                                 reserved1076;	//0xC4D01168
	UINT32                                                 reserved1077;	//0xC4D0116C
	UINT32                                                 reserved1078;	//0xC4D01170
	UINT32                                                 reserved1079;	//0xC4D01174
	UINT32                                                 reserved1080;	//0xC4D01178
	UINT32                                                 reserved1081;	//0xC4D0117C
	UINT32                                                 reserved1082;	//0xC4D01180
	UINT32                                                 reserved1083;	//0xC4D01184
	UINT32                                                 reserved1084;	//0xC4D01188
	UINT32                                                 reserved1085;	//0xC4D0118C
	UINT32                                                 reserved1086;	//0xC4D01190
	UINT32                                                 reserved1087;	//0xC4D01194
	UINT32                                                 reserved1088;	//0xC4D01198
	UINT32                                                 reserved1089;	//0xC4D0119C
	UINT32                                                 reserved1090;	//0xC4D011A0
	UINT32                                                 reserved1091;	//0xC4D011A4
	UINT32                                                 reserved1092;	//0xC4D011A8
	UINT32                                                 reserved1093;	//0xC4D011AC
	UINT32                                                 reserved1094;	//0xC4D011B0
	UINT32                                                 reserved1095;	//0xC4D011B4
	UINT32                                                 reserved1096;	//0xC4D011B8
	UINT32                                                 reserved1097;	//0xC4D011BC
	UINT32                                                 reserved1098;	//0xC4D011C0
	UINT32                                                 reserved1099;	//0xC4D011C4
	UINT32                                                 reserved1100;	//0xC4D011C8
	UINT32                                                 reserved1101;	//0xC4D011CC
	UINT32                                                 reserved1102;	//0xC4D011D0
	UINT32                                                 reserved1103;	//0xC4D011D4
	UINT32                                                 reserved1104;	//0xC4D011D8
	UINT32                                                 reserved1105;	//0xC4D011DC
	UINT32                                                 reserved1106;	//0xC4D011E0
	UINT32                                                 reserved1107;	//0xC4D011E4
	UINT32                                                 reserved1108;	//0xC4D011E8
	UINT32                                                 reserved1109;	//0xC4D011EC
	UINT32                                                 reserved1110;	//0xC4D011F0
	UINT32                                                 reserved1111;	//0xC4D011F4
	UINT32                                                 reserved1112;	//0xC4D011F8
	UINT32                                                 reserved1113;	//0xC4D011FC
	UINT32                                                 reserved1114;	//0xC4D01200
	UINT32                                                 reserved1115;	//0xC4D01204
	UINT32                                                 reserved1116;	//0xC4D01208
	UINT32                                                 reserved1117;	//0xC4D0120C
	UINT32                                                 reserved1118;	//0xC4D01210
	UINT32                                                 reserved1119;	//0xC4D01214
	UINT32                                                 reserved1120;	//0xC4D01218
	UINT32                                                 reserved1121;	//0xC4D0121C
	UINT32                                                 reserved1122;	//0xC4D01220
	UINT32                                                 reserved1123;	//0xC4D01224
	UINT32                                                 reserved1124;	//0xC4D01228
	UINT32                                                 reserved1125;	//0xC4D0122C
	UINT32                                                 reserved1126;	//0xC4D01230
	UINT32                                                 reserved1127;	//0xC4D01234
	UINT32                                                 reserved1128;	//0xC4D01238
	UINT32                                                 reserved1129;	//0xC4D0123C
	UINT32                                                 reserved1130;	//0xC4D01240
	UINT32                                                 reserved1131;	//0xC4D01244
	UINT32                                                 reserved1132;	//0xC4D01248
	UINT32                                                 reserved1133;	//0xC4D0124C
	UINT32                                                 reserved1134;	//0xC4D01250
	UINT32                                                 reserved1135;	//0xC4D01254
	UINT32                                                 reserved1136;	//0xC4D01258
	UINT32                                                 reserved1137;	//0xC4D0125C
	UINT32                                                 reserved1138;	//0xC4D01260
	UINT32                                                 reserved1139;	//0xC4D01264
	UINT32                                                 reserved1140;	//0xC4D01268
	UINT32                                                 reserved1141;	//0xC4D0126C
	UINT32                                                 reserved1142;	//0xC4D01270
	UINT32                                                 reserved1143;	//0xC4D01274
	UINT32                                                 reserved1144;	//0xC4D01278
	UINT32                                                 reserved1145;	//0xC4D0127C
	UINT32                                                 reserved1146;	//0xC4D01280
	UINT32                                                 reserved1147;	//0xC4D01284
	UINT32                                                 reserved1148;	//0xC4D01288
	UINT32                                                 reserved1149;	//0xC4D0128C
	UINT32                                                 reserved1150;	//0xC4D01290
	UINT32                                                 reserved1151;	//0xC4D01294
	UINT32                                                 reserved1152;	//0xC4D01298
	UINT32                                                 reserved1153;	//0xC4D0129C
	UINT32                                                 reserved1154;	//0xC4D012A0
	UINT32                                                 reserved1155;	//0xC4D012A4
	UINT32                                                 reserved1156;	//0xC4D012A8
	UINT32                                                 reserved1157;	//0xC4D012AC
	UINT32                                                 reserved1158;	//0xC4D012B0
	UINT32                                                 reserved1159;	//0xC4D012B4
	UINT32                                                 reserved1160;	//0xC4D012B8
	UINT32                                                 reserved1161;	//0xC4D012BC
	UINT32                                                 reserved1162;	//0xC4D012C0
	UINT32                                                 reserved1163;	//0xC4D012C4
	UINT32                                                 reserved1164;	//0xC4D012C8
	UINT32                                                 reserved1165;	//0xC4D012CC
	UINT32                                                 reserved1166;	//0xC4D012D0
	UINT32                                                 reserved1167;	//0xC4D012D4
	UINT32                                                 reserved1168;	//0xC4D012D8
	UINT32                                                 reserved1169;	//0xC4D012DC
	UINT32                                                 reserved1170;	//0xC4D012E0
	UINT32                                                 reserved1171;	//0xC4D012E4
	UINT32                                                 reserved1172;	//0xC4D012E8
	UINT32                                                 reserved1173;	//0xC4D012EC
	UINT32                                                 reserved1174;	//0xC4D012F0
	UINT32                                                 reserved1175;	//0xC4D012F4
	UINT32                                                 reserved1176;	//0xC4D012F8
	UINT32                                                 reserved1177;	//0xC4D012FC
	UINT32                                                 reserved1178;	//0xC4D01300
	UINT32                                                 reserved1179;	//0xC4D01304
	UINT32                                                 reserved1180;	//0xC4D01308
	UINT32                                                 reserved1181;	//0xC4D0130C
	UINT32                                                 reserved1182;	//0xC4D01310
	UINT32                                                 reserved1183;	//0xC4D01314
	UINT32                                                 reserved1184;	//0xC4D01318
	UINT32                                                 reserved1185;	//0xC4D0131C
	UINT32                                                 reserved1186;	//0xC4D01320
	UINT32                                                 reserved1187;	//0xC4D01324
	UINT32                                                 reserved1188;	//0xC4D01328
	UINT32                                                 reserved1189;	//0xC4D0132C
	UINT32                                                 reserved1190;	//0xC4D01330
	UINT32                                                 reserved1191;	//0xC4D01334
	UINT32                                                 reserved1192;	//0xC4D01338
	UINT32                                                 reserved1193;	//0xC4D0133C
	UINT32                                                 reserved1194;	//0xC4D01340
	UINT32                                                 reserved1195;	//0xC4D01344
	UINT32                                                 reserved1196;	//0xC4D01348
	UINT32                                                 reserved1197;	//0xC4D0134C
	UINT32                                                 reserved1198;	//0xC4D01350
	UINT32                                                 reserved1199;	//0xC4D01354
	UINT32                                                 reserved1200;	//0xC4D01358
	UINT32                                                 reserved1201;	//0xC4D0135C
	UINT32                                                 reserved1202;	//0xC4D01360
	UINT32                                                 reserved1203;	//0xC4D01364
	UINT32                                                 reserved1204;	//0xC4D01368
	UINT32                                                 reserved1205;	//0xC4D0136C
	UINT32                                                 reserved1206;	//0xC4D01370
	UINT32                                                 reserved1207;	//0xC4D01374
	UINT32                                                 reserved1208;	//0xC4D01378
	UINT32                                                 reserved1209;	//0xC4D0137C
	UINT32                                                 reserved1210;	//0xC4D01380
	UINT32                                                 reserved1211;	//0xC4D01384
	UINT32                                                 reserved1212;	//0xC4D01388
	UINT32                                                 reserved1213;	//0xC4D0138C
	UINT32                                                 reserved1214;	//0xC4D01390
	UINT32                                                 reserved1215;	//0xC4D01394
	UINT32                                                 reserved1216;	//0xC4D01398
	UINT32                                                 reserved1217;	//0xC4D0139C
	UINT32                                                 reserved1218;	//0xC4D013A0
	UINT32                                                 reserved1219;	//0xC4D013A4
	UINT32                                                 reserved1220;	//0xC4D013A8
	UINT32                                                 reserved1221;	//0xC4D013AC
	UINT32                                                 reserved1222;	//0xC4D013B0
	UINT32                                                 reserved1223;	//0xC4D013B4
	UINT32                                                 reserved1224;	//0xC4D013B8
	UINT32                                                 reserved1225;	//0xC4D013BC
	UINT32                                                 reserved1226;	//0xC4D013C0
	UINT32                                                 reserved1227;	//0xC4D013C4
	UINT32                                                 reserved1228;	//0xC4D013C8
	UINT32                                                 reserved1229;	//0xC4D013CC
	UINT32                                                 reserved1230;	//0xC4D013D0
	UINT32                                                 reserved1231;	//0xC4D013D4
	UINT32                                                 reserved1232;	//0xC4D013D8
	UINT32                                                 reserved1233;	//0xC4D013DC
	UINT32                                                 reserved1234;	//0xC4D013E0
	UINT32                                                 reserved1235;	//0xC4D013E4
	UINT32                                                 reserved1236;	//0xC4D013E8
	UINT32                                                 reserved1237;	//0xC4D013EC
	UINT32                                                 reserved1238;	//0xC4D013F0
	UINT32                                                 reserved1239;	//0xC4D013F4
	UINT32                                                 reserved1240;	//0xC4D013F8
	UINT32                                                 reserved1241;	//0xC4D013FC
	UINT32                                                 reserved1242;	//0xC4D01400
	UINT32                                                 reserved1243;	//0xC4D01404
	UINT32                                                 reserved1244;	//0xC4D01408
	UINT32                                                 reserved1245;	//0xC4D0140C
	UINT32                                                 reserved1246;	//0xC4D01410
	UINT32                                                 reserved1247;	//0xC4D01414
	UINT32                                                 reserved1248;	//0xC4D01418
	UINT32                                                 reserved1249;	//0xC4D0141C
	UINT32                                                 reserved1250;	//0xC4D01420
	UINT32                                                 reserved1251;	//0xC4D01424
	UINT32                                                 reserved1252;	//0xC4D01428
	UINT32                                                 reserved1253;	//0xC4D0142C
	UINT32                                                 reserved1254;	//0xC4D01430
	UINT32                                                 reserved1255;	//0xC4D01434
	UINT32                                                 reserved1256;	//0xC4D01438
	UINT32                                                 reserved1257;	//0xC4D0143C
	UINT32                                                 reserved1258;	//0xC4D01440
	UINT32                                                 reserved1259;	//0xC4D01444
	UINT32                                                 reserved1260;	//0xC4D01448
	UINT32                                                 reserved1261;	//0xC4D0144C
	UINT32                                                 reserved1262;	//0xC4D01450
	UINT32                                                 reserved1263;	//0xC4D01454
	UINT32                                                 reserved1264;	//0xC4D01458
	UINT32                                                 reserved1265;	//0xC4D0145C
	UINT32                                                 reserved1266;	//0xC4D01460
	UINT32                                                 reserved1267;	//0xC4D01464
	UINT32                                                 reserved1268;	//0xC4D01468
	UINT32                                                 reserved1269;	//0xC4D0146C
	UINT32                                                 reserved1270;	//0xC4D01470
	UINT32                                                 reserved1271;	//0xC4D01474
	UINT32                                                 reserved1272;	//0xC4D01478
	UINT32                                                 reserved1273;	//0xC4D0147C
	UINT32                                                 reserved1274;	//0xC4D01480
	UINT32                                                 reserved1275;	//0xC4D01484
	UINT32                                                 reserved1276;	//0xC4D01488
	UINT32                                                 reserved1277;	//0xC4D0148C
	UINT32                                                 reserved1278;	//0xC4D01490
	UINT32                                                 reserved1279;	//0xC4D01494
	UINT32                                                 reserved1280;	//0xC4D01498
	UINT32                                                 reserved1281;	//0xC4D0149C
	UINT32                                                 reserved1282;	//0xC4D014A0
	UINT32                                                 reserved1283;	//0xC4D014A4
	UINT32                                                 reserved1284;	//0xC4D014A8
	UINT32                                                 reserved1285;	//0xC4D014AC
	UINT32                                                 reserved1286;	//0xC4D014B0
	UINT32                                                 reserved1287;	//0xC4D014B4
	UINT32                                                 reserved1288;	//0xC4D014B8
	UINT32                                                 reserved1289;	//0xC4D014BC
	UINT32                                                 reserved1290;	//0xC4D014C0
	UINT32                                                 reserved1291;	//0xC4D014C4
	UINT32                                                 reserved1292;	//0xC4D014C8
	UINT32                                                 reserved1293;	//0xC4D014CC
	UINT32                                                 reserved1294;	//0xC4D014D0
	UINT32                                                 reserved1295;	//0xC4D014D4
	UINT32                                                 reserved1296;	//0xC4D014D8
	UINT32                                                 reserved1297;	//0xC4D014DC
	UINT32                                                 reserved1298;	//0xC4D014E0
	UINT32                                                 reserved1299;	//0xC4D014E4
	UINT32                                                 reserved1300;	//0xC4D014E8
	UINT32                                                 reserved1301;	//0xC4D014EC
	UINT32                                                 reserved1302;	//0xC4D014F0
	UINT32                                                 reserved1303;	//0xC4D014F4
	UINT32                                                 reserved1304;	//0xC4D014F8
	UINT32                                                 reserved1305;	//0xC4D014FC
	UINT32                                                 reserved1306;	//0xC4D01500
	UINT32                                                 reserved1307;	//0xC4D01504
	UINT32                                                 reserved1308;	//0xC4D01508
	UINT32                                                 reserved1309;	//0xC4D0150C
	UINT32                                                 reserved1310;	//0xC4D01510
	UINT32                                                 reserved1311;	//0xC4D01514
	UINT32                                                 reserved1312;	//0xC4D01518
	UINT32                                                 reserved1313;	//0xC4D0151C
	UINT32                                                 reserved1314;	//0xC4D01520
	UINT32                                                 reserved1315;	//0xC4D01524
	UINT32                                                 reserved1316;	//0xC4D01528
	UINT32                                                 reserved1317;	//0xC4D0152C
	UINT32                                                 reserved1318;	//0xC4D01530
	UINT32                                                 reserved1319;	//0xC4D01534
	UINT32                                                 reserved1320;	//0xC4D01538
	UINT32                                                 reserved1321;	//0xC4D0153C
	UINT32                                                 reserved1322;	//0xC4D01540
	UINT32                                                 reserved1323;	//0xC4D01544
	UINT32                                                 reserved1324;	//0xC4D01548
	UINT32                                                 reserved1325;	//0xC4D0154C
	UINT32                                                 reserved1326;	//0xC4D01550
	UINT32                                                 reserved1327;	//0xC4D01554
	UINT32                                                 reserved1328;	//0xC4D01558
	UINT32                                                 reserved1329;	//0xC4D0155C
	UINT32                                                 reserved1330;	//0xC4D01560
	UINT32                                                 reserved1331;	//0xC4D01564
	UINT32                                                 reserved1332;	//0xC4D01568
	UINT32                                                 reserved1333;	//0xC4D0156C
	UINT32                                                 reserved1334;	//0xC4D01570
	UINT32                                                 reserved1335;	//0xC4D01574
	UINT32                                                 reserved1336;	//0xC4D01578
	UINT32                                                 reserved1337;	//0xC4D0157C
	UINT32                                                 reserved1338;	//0xC4D01580
	UINT32                                                 reserved1339;	//0xC4D01584
	UINT32                                                 reserved1340;	//0xC4D01588
	UINT32                                                 reserved1341;	//0xC4D0158C
	UINT32                                                 reserved1342;	//0xC4D01590
	UINT32                                                 reserved1343;	//0xC4D01594
	UINT32                                                 reserved1344;	//0xC4D01598
	UINT32                                                 reserved1345;	//0xC4D0159C
	UINT32                                                 reserved1346;	//0xC4D015A0
	UINT32                                                 reserved1347;	//0xC4D015A4
	UINT32                                                 reserved1348;	//0xC4D015A8
	UINT32                                                 reserved1349;	//0xC4D015AC
	UINT32                                                 reserved1350;	//0xC4D015B0
	UINT32                                                 reserved1351;	//0xC4D015B4
	UINT32                                                 reserved1352;	//0xC4D015B8
	UINT32                                                 reserved1353;	//0xC4D015BC
	UINT32                                                 reserved1354;	//0xC4D015C0
	UINT32                                                 reserved1355;	//0xC4D015C4
	UINT32                                                 reserved1356;	//0xC4D015C8
	UINT32                                                 reserved1357;	//0xC4D015CC
	UINT32                                                 reserved1358;	//0xC4D015D0
	UINT32                                                 reserved1359;	//0xC4D015D4
	UINT32                                                 reserved1360;	//0xC4D015D8
	UINT32                                                 reserved1361;	//0xC4D015DC
	UINT32                                                 reserved1362;	//0xC4D015E0
	UINT32                                                 reserved1363;	//0xC4D015E4
	UINT32                                                 reserved1364;	//0xC4D015E8
	UINT32                                                 reserved1365;	//0xC4D015EC
	UINT32                                                 reserved1366;	//0xC4D015F0
	UINT32                                                 reserved1367;	//0xC4D015F4
	UINT32                                                 reserved1368;	//0xC4D015F8
	UINT32                                                 reserved1369;	//0xC4D015FC
	UINT32                                                 reserved1370;	//0xC4D01600
	UINT32                                                 reserved1371;	//0xC4D01604
	UINT32                                                 reserved1372;	//0xC4D01608
	UINT32                                                 reserved1373;	//0xC4D0160C
	UINT32                                                 reserved1374;	//0xC4D01610
	UINT32                                                 reserved1375;	//0xC4D01614
	UINT32                                                 reserved1376;	//0xC4D01618
	UINT32                                                 reserved1377;	//0xC4D0161C
	UINT32                                                 reserved1378;	//0xC4D01620
	UINT32                                                 reserved1379;	//0xC4D01624
	UINT32                                                 reserved1380;	//0xC4D01628
	UINT32                                                 reserved1381;	//0xC4D0162C
	UINT32                                                 reserved1382;	//0xC4D01630
	UINT32                                                 reserved1383;	//0xC4D01634
	UINT32                                                 reserved1384;	//0xC4D01638
	UINT32                                                 reserved1385;	//0xC4D0163C
	UINT32                                                 reserved1386;	//0xC4D01640
	UINT32                                                 reserved1387;	//0xC4D01644
	UINT32                                                 reserved1388;	//0xC4D01648
	UINT32                                                 reserved1389;	//0xC4D0164C
	UINT32                                                 reserved1390;	//0xC4D01650
	UINT32                                                 reserved1391;	//0xC4D01654
	UINT32                                                 reserved1392;	//0xC4D01658
	UINT32                                                 reserved1393;	//0xC4D0165C
	UINT32                                                 reserved1394;	//0xC4D01660
	UINT32                                                 reserved1395;	//0xC4D01664
	UINT32                                                 reserved1396;	//0xC4D01668
	UINT32                                                 reserved1397;	//0xC4D0166C
	UINT32                                                 reserved1398;	//0xC4D01670
	UINT32                                                 reserved1399;	//0xC4D01674
	UINT32                                                 reserved1400;	//0xC4D01678
	UINT32                                                 reserved1401;	//0xC4D0167C
	UINT32                                                 reserved1402;	//0xC4D01680
	UINT32                                                 reserved1403;	//0xC4D01684
	UINT32                                                 reserved1404;	//0xC4D01688
	UINT32                                                 reserved1405;	//0xC4D0168C
	UINT32                                                 reserved1406;	//0xC4D01690
	UINT32                                                 reserved1407;	//0xC4D01694
	UINT32                                                 reserved1408;	//0xC4D01698
	UINT32                                                 reserved1409;	//0xC4D0169C
	UINT32                                                 reserved1410;	//0xC4D016A0
	UINT32                                                 reserved1411;	//0xC4D016A4
	UINT32                                                 reserved1412;	//0xC4D016A8
	UINT32                                                 reserved1413;	//0xC4D016AC
	UINT32                                                 reserved1414;	//0xC4D016B0
	UINT32                                                 reserved1415;	//0xC4D016B4
	UINT32                                                 reserved1416;	//0xC4D016B8
	UINT32                                                 reserved1417;	//0xC4D016BC
	UINT32                                                 reserved1418;	//0xC4D016C0
	UINT32                                                 reserved1419;	//0xC4D016C4
	UINT32                                                 reserved1420;	//0xC4D016C8
	UINT32                                                 reserved1421;	//0xC4D016CC
	UINT32                                                 reserved1422;	//0xC4D016D0
	UINT32                                                 reserved1423;	//0xC4D016D4
	UINT32                                                 reserved1424;	//0xC4D016D8
	UINT32                                                 reserved1425;	//0xC4D016DC
	UINT32                                                 reserved1426;	//0xC4D016E0
	UINT32                                                 reserved1427;	//0xC4D016E4
	UINT32                                                 reserved1428;	//0xC4D016E8
	UINT32                                                 reserved1429;	//0xC4D016EC
	UINT32                                                 reserved1430;	//0xC4D016F0
	UINT32                                                 reserved1431;	//0xC4D016F4
	UINT32                                                 reserved1432;	//0xC4D016F8
	UINT32                                                 reserved1433;	//0xC4D016FC
	UINT32                                                 reserved1434;	//0xC4D01700
	UINT32                                                 reserved1435;	//0xC4D01704
	UINT32                                                 reserved1436;	//0xC4D01708
	UINT32                                                 reserved1437;	//0xC4D0170C
	UINT32                                                 reserved1438;	//0xC4D01710
	UINT32                                                 reserved1439;	//0xC4D01714
	UINT32                                                 reserved1440;	//0xC4D01718
	UINT32                                                 reserved1441;	//0xC4D0171C
	UINT32                                                 reserved1442;	//0xC4D01720
	UINT32                                                 reserved1443;	//0xC4D01724
	UINT32                                                 reserved1444;	//0xC4D01728
	UINT32                                                 reserved1445;	//0xC4D0172C
	UINT32                                                 reserved1446;	//0xC4D01730
	UINT32                                                 reserved1447;	//0xC4D01734
	UINT32                                                 reserved1448;	//0xC4D01738
	UINT32                                                 reserved1449;	//0xC4D0173C
	UINT32                                                 reserved1450;	//0xC4D01740
	UINT32                                                 reserved1451;	//0xC4D01744
	UINT32                                                 reserved1452;	//0xC4D01748
	UINT32                                                 reserved1453;	//0xC4D0174C
	UINT32                                                 reserved1454;	//0xC4D01750
	UINT32                                                 reserved1455;	//0xC4D01754
	UINT32                                                 reserved1456;	//0xC4D01758
	UINT32                                                 reserved1457;	//0xC4D0175C
	UINT32                                                 reserved1458;	//0xC4D01760
	UINT32                                                 reserved1459;	//0xC4D01764
	UINT32                                                 reserved1460;	//0xC4D01768
	UINT32                                                 reserved1461;	//0xC4D0176C
	UINT32                                                 reserved1462;	//0xC4D01770
	UINT32                                                 reserved1463;	//0xC4D01774
	UINT32                                                 reserved1464;	//0xC4D01778
	UINT32                                                 reserved1465;	//0xC4D0177C
	UINT32                                                 reserved1466;	//0xC4D01780
	UINT32                                                 reserved1467;	//0xC4D01784
	UINT32                                                 reserved1468;	//0xC4D01788
	UINT32                                                 reserved1469;	//0xC4D0178C
	UINT32                                                 reserved1470;	//0xC4D01790
	UINT32                                                 reserved1471;	//0xC4D01794
	UINT32                                                 reserved1472;	//0xC4D01798
	UINT32                                                 reserved1473;	//0xC4D0179C
	UINT32                                                 reserved1474;	//0xC4D017A0
	UINT32                                                 reserved1475;	//0xC4D017A4
	UINT32                                                 reserved1476;	//0xC4D017A8
	UINT32                                                 reserved1477;	//0xC4D017AC
	UINT32                                                 reserved1478;	//0xC4D017B0
	UINT32                                                 reserved1479;	//0xC4D017B4
	UINT32                                                 reserved1480;	//0xC4D017B8
	UINT32                                                 reserved1481;	//0xC4D017BC
	UINT32                                                 reserved1482;	//0xC4D017C0
	UINT32                                                 reserved1483;	//0xC4D017C4
	UINT32                                                 reserved1484;	//0xC4D017C8
	UINT32                                                 reserved1485;	//0xC4D017CC
	UINT32                                                 reserved1486;	//0xC4D017D0
	UINT32                                                 reserved1487;	//0xC4D017D4
	UINT32                                                 reserved1488;	//0xC4D017D8
	UINT32                                                 reserved1489;	//0xC4D017DC
	UINT32                                                 reserved1490;	//0xC4D017E0
	UINT32                                                 reserved1491;	//0xC4D017E4
	UINT32                                                 reserved1492;	//0xC4D017E8
	UINT32                                                 reserved1493;	//0xC4D017EC
	UINT32                                                 reserved1494;	//0xC4D017F0
	UINT32                                                 reserved1495;	//0xC4D017F4
	UINT32                                                 reserved1496;	//0xC4D017F8
	UINT32                                                 reserved1497;	//0xC4D017FC
	UINT32                                                 reserved1498;	//0xC4D01800
	UINT32                                                 reserved1499;	//0xC4D01804
	UINT32                                                 reserved1500;	//0xC4D01808
	UINT32                                                 reserved1501;	//0xC4D0180C
	UINT32                                                 reserved1502;	//0xC4D01810
	UINT32                                                 reserved1503;	//0xC4D01814
	UINT32                                                 reserved1504;	//0xC4D01818
	UINT32                                                 reserved1505;	//0xC4D0181C
	UINT32                                                 reserved1506;	//0xC4D01820
	UINT32                                                 reserved1507;	//0xC4D01824
	UINT32                                                 reserved1508;	//0xC4D01828
	UINT32                                                 reserved1509;	//0xC4D0182C
	UINT32                                                 reserved1510;	//0xC4D01830
	UINT32                                                 reserved1511;	//0xC4D01834
	UINT32                                                 reserved1512;	//0xC4D01838
	UINT32                                                 reserved1513;	//0xC4D0183C
	UINT32                                                 reserved1514;	//0xC4D01840
	UINT32                                                 reserved1515;	//0xC4D01844
	UINT32                                                 reserved1516;	//0xC4D01848
	UINT32                                                 reserved1517;	//0xC4D0184C
	UINT32                                                 reserved1518;	//0xC4D01850
	UINT32                                                 reserved1519;	//0xC4D01854
	UINT32                                                 reserved1520;	//0xC4D01858
	UINT32                                                 reserved1521;	//0xC4D0185C
	UINT32                                                 reserved1522;	//0xC4D01860
	UINT32                                                 reserved1523;	//0xC4D01864
	UINT32                                                 reserved1524;	//0xC4D01868
	UINT32                                                 reserved1525;	//0xC4D0186C
	UINT32                                                 reserved1526;	//0xC4D01870
	UINT32                                                 reserved1527;	//0xC4D01874
	UINT32                                                 reserved1528;	//0xC4D01878
	UINT32                                                 reserved1529;	//0xC4D0187C
	UINT32                                                 reserved1530;	//0xC4D01880
	UINT32                                                 reserved1531;	//0xC4D01884
	UINT32                                                 reserved1532;	//0xC4D01888
	UINT32                                                 reserved1533;	//0xC4D0188C
	UINT32                                                 reserved1534;	//0xC4D01890
	UINT32                                                 reserved1535;	//0xC4D01894
	UINT32                                                 reserved1536;	//0xC4D01898
	UINT32                                                 reserved1537;	//0xC4D0189C
	UINT32                                                 reserved1538;	//0xC4D018A0
	UINT32                                                 reserved1539;	//0xC4D018A4
	UINT32                                                 reserved1540;	//0xC4D018A8
	UINT32                                                 reserved1541;	//0xC4D018AC
	UINT32                                                 reserved1542;	//0xC4D018B0
	UINT32                                                 reserved1543;	//0xC4D018B4
	UINT32                                                 reserved1544;	//0xC4D018B8
	UINT32                                                 reserved1545;	//0xC4D018BC
	UINT32                                                 reserved1546;	//0xC4D018C0
	UINT32                                                 reserved1547;	//0xC4D018C4
	UINT32                                                 reserved1548;	//0xC4D018C8
	UINT32                                                 reserved1549;	//0xC4D018CC
	UINT32                                                 reserved1550;	//0xC4D018D0
	UINT32                                                 reserved1551;	//0xC4D018D4
	UINT32                                                 reserved1552;	//0xC4D018D8
	UINT32                                                 reserved1553;	//0xC4D018DC
	UINT32                                                 reserved1554;	//0xC4D018E0
	UINT32                                                 reserved1555;	//0xC4D018E4
	UINT32                                                 reserved1556;	//0xC4D018E8
	UINT32                                                 reserved1557;	//0xC4D018EC
	UINT32                                                 reserved1558;	//0xC4D018F0
	UINT32                                                 reserved1559;	//0xC4D018F4
	UINT32                                                 reserved1560;	//0xC4D018F8
	UINT32                                                 reserved1561;	//0xC4D018FC
	UINT32                                                 reserved1562;	//0xC4D01900
	UINT32                                                 reserved1563;	//0xC4D01904
	UINT32                                                 reserved1564;	//0xC4D01908
	UINT32                                                 reserved1565;	//0xC4D0190C
	UINT32                                                 reserved1566;	//0xC4D01910
	UINT32                                                 reserved1567;	//0xC4D01914
	UINT32                                                 reserved1568;	//0xC4D01918
	UINT32                                                 reserved1569;	//0xC4D0191C
	UINT32                                                 reserved1570;	//0xC4D01920
	UINT32                                                 reserved1571;	//0xC4D01924
	UINT32                                                 reserved1572;	//0xC4D01928
	UINT32                                                 reserved1573;	//0xC4D0192C
	UINT32                                                 reserved1574;	//0xC4D01930
	UINT32                                                 reserved1575;	//0xC4D01934
	UINT32                                                 reserved1576;	//0xC4D01938
	UINT32                                                 reserved1577;	//0xC4D0193C
	UINT32                                                 reserved1578;	//0xC4D01940
	UINT32                                                 reserved1579;	//0xC4D01944
	UINT32                                                 reserved1580;	//0xC4D01948
	UINT32                                                 reserved1581;	//0xC4D0194C
	UINT32                                                 reserved1582;	//0xC4D01950
	UINT32                                                 reserved1583;	//0xC4D01954
	UINT32                                                 reserved1584;	//0xC4D01958
	UINT32                                                 reserved1585;	//0xC4D0195C
	UINT32                                                 reserved1586;	//0xC4D01960
	UINT32                                                 reserved1587;	//0xC4D01964
	UINT32                                                 reserved1588;	//0xC4D01968
	UINT32                                                 reserved1589;	//0xC4D0196C
	UINT32                                                 reserved1590;	//0xC4D01970
	UINT32                                                 reserved1591;	//0xC4D01974
	UINT32                                                 reserved1592;	//0xC4D01978
	UINT32                                                 reserved1593;	//0xC4D0197C
	UINT32                                                 reserved1594;	//0xC4D01980
	UINT32                                                 reserved1595;	//0xC4D01984
	UINT32                                                 reserved1596;	//0xC4D01988
	UINT32                                                 reserved1597;	//0xC4D0198C
	UINT32                                                 reserved1598;	//0xC4D01990
	UINT32                                                 reserved1599;	//0xC4D01994
	UINT32                                                 reserved1600;	//0xC4D01998
	UINT32                                                 reserved1601;	//0xC4D0199C
	UINT32                                                 reserved1602;	//0xC4D019A0
	UINT32                                                 reserved1603;	//0xC4D019A4
	UINT32                                                 reserved1604;	//0xC4D019A8
	UINT32                                                 reserved1605;	//0xC4D019AC
	UINT32                                                 reserved1606;	//0xC4D019B0
	UINT32                                                 reserved1607;	//0xC4D019B4
	UINT32                                                 reserved1608;	//0xC4D019B8
	UINT32                                                 reserved1609;	//0xC4D019BC
	UINT32                                                 reserved1610;	//0xC4D019C0
	UINT32                                                 reserved1611;	//0xC4D019C4
	UINT32                                                 reserved1612;	//0xC4D019C8
	UINT32                                                 reserved1613;	//0xC4D019CC
	UINT32                                                 reserved1614;	//0xC4D019D0
	UINT32                                                 reserved1615;	//0xC4D019D4
	UINT32                                                 reserved1616;	//0xC4D019D8
	UINT32                                                 reserved1617;	//0xC4D019DC
	UINT32                                                 reserved1618;	//0xC4D019E0
	UINT32                                                 reserved1619;	//0xC4D019E4
	UINT32                                                 reserved1620;	//0xC4D019E8
	UINT32                                                 reserved1621;	//0xC4D019EC
	UINT32                                                 reserved1622;	//0xC4D019F0
	UINT32                                                 reserved1623;	//0xC4D019F4
	UINT32                                                 reserved1624;	//0xC4D019F8
	UINT32                                                 reserved1625;	//0xC4D019FC
	UINT32                                                 reserved1626;	//0xC4D01A00
	UINT32                                                 reserved1627;	//0xC4D01A04
	UINT32                                                 reserved1628;	//0xC4D01A08
	UINT32                                                 reserved1629;	//0xC4D01A0C
	UINT32                                                 reserved1630;	//0xC4D01A10
	UINT32                                                 reserved1631;	//0xC4D01A14
	UINT32                                                 reserved1632;	//0xC4D01A18
	UINT32                                                 reserved1633;	//0xC4D01A1C
	UINT32                                                 reserved1634;	//0xC4D01A20
	UINT32                                                 reserved1635;	//0xC4D01A24
	UINT32                                                 reserved1636;	//0xC4D01A28
	UINT32                                                 reserved1637;	//0xC4D01A2C
	UINT32                                                 reserved1638;	//0xC4D01A30
	UINT32                                                 reserved1639;	//0xC4D01A34
	UINT32                                                 reserved1640;	//0xC4D01A38
	UINT32                                                 reserved1641;	//0xC4D01A3C
	UINT32                                                 reserved1642;	//0xC4D01A40
	UINT32                                                 reserved1643;	//0xC4D01A44
	UINT32                                                 reserved1644;	//0xC4D01A48
	UINT32                                                 reserved1645;	//0xC4D01A4C
	UINT32                                                 reserved1646;	//0xC4D01A50
	UINT32                                                 reserved1647;	//0xC4D01A54
	UINT32                                                 reserved1648;	//0xC4D01A58
	UINT32                                                 reserved1649;	//0xC4D01A5C
	UINT32                                                 reserved1650;	//0xC4D01A60
	UINT32                                                 reserved1651;	//0xC4D01A64
	UINT32                                                 reserved1652;	//0xC4D01A68
	UINT32                                                 reserved1653;	//0xC4D01A6C
	UINT32                                                 reserved1654;	//0xC4D01A70
	UINT32                                                 reserved1655;	//0xC4D01A74
	UINT32                                                 reserved1656;	//0xC4D01A78
	UINT32                                                 reserved1657;	//0xC4D01A7C
	UINT32                                                 reserved1658;	//0xC4D01A80
	UINT32                                                 reserved1659;	//0xC4D01A84
	UINT32                                                 reserved1660;	//0xC4D01A88
	UINT32                                                 reserved1661;	//0xC4D01A8C
	UINT32                                                 reserved1662;	//0xC4D01A90
	UINT32                                                 reserved1663;	//0xC4D01A94
	UINT32                                                 reserved1664;	//0xC4D01A98
	UINT32                                                 reserved1665;	//0xC4D01A9C
	UINT32                                                 reserved1666;	//0xC4D01AA0
	UINT32                                                 reserved1667;	//0xC4D01AA4
	UINT32                                                 reserved1668;	//0xC4D01AA8
	UINT32                                                 reserved1669;	//0xC4D01AAC
	UINT32                                                 reserved1670;	//0xC4D01AB0
	UINT32                                                 reserved1671;	//0xC4D01AB4
	UINT32                                                 reserved1672;	//0xC4D01AB8
	UINT32                                                 reserved1673;	//0xC4D01ABC
	UINT32                                                 reserved1674;	//0xC4D01AC0
	UINT32                                                 reserved1675;	//0xC4D01AC4
	UINT32                                                 reserved1676;	//0xC4D01AC8
	UINT32                                                 reserved1677;	//0xC4D01ACC
	UINT32                                                 reserved1678;	//0xC4D01AD0
	UINT32                                                 reserved1679;	//0xC4D01AD4
	UINT32                                                 reserved1680;	//0xC4D01AD8
	UINT32                                                 reserved1681;	//0xC4D01ADC
	UINT32                                                 reserved1682;	//0xC4D01AE0
	UINT32                                                 reserved1683;	//0xC4D01AE4
	UINT32                                                 reserved1684;	//0xC4D01AE8
	UINT32                                                 reserved1685;	//0xC4D01AEC
	UINT32                                                 reserved1686;	//0xC4D01AF0
	UINT32                                                 reserved1687;	//0xC4D01AF4
	UINT32                                                 reserved1688;	//0xC4D01AF8
	UINT32                                                 reserved1689;	//0xC4D01AFC
	UINT32                                                 reserved1690;	//0xC4D01B00
	UINT32                                                 reserved1691;	//0xC4D01B04
	UINT32                                                 reserved1692;	//0xC4D01B08
	UINT32                                                 reserved1693;	//0xC4D01B0C
	UINT32                                                 reserved1694;	//0xC4D01B10
	UINT32                                                 reserved1695;	//0xC4D01B14
	UINT32                                                 reserved1696;	//0xC4D01B18
	UINT32                                                 reserved1697;	//0xC4D01B1C
	UINT32                                                 reserved1698;	//0xC4D01B20
	UINT32                                                 reserved1699;	//0xC4D01B24
	UINT32                                                 reserved1700;	//0xC4D01B28
	UINT32                                                 reserved1701;	//0xC4D01B2C
	UINT32                                                 reserved1702;	//0xC4D01B30
	UINT32                                                 reserved1703;	//0xC4D01B34
	UINT32                                                 reserved1704;	//0xC4D01B38
	UINT32                                                 reserved1705;	//0xC4D01B3C
	UINT32                                                 reserved1706;	//0xC4D01B40
	UINT32                                                 reserved1707;	//0xC4D01B44
	UINT32                                                 reserved1708;	//0xC4D01B48
	UINT32                                                 reserved1709;	//0xC4D01B4C
	UINT32                                                 reserved1710;	//0xC4D01B50
	UINT32                                                 reserved1711;	//0xC4D01B54
	UINT32                                                 reserved1712;	//0xC4D01B58
	UINT32                                                 reserved1713;	//0xC4D01B5C
	UINT32                                                 reserved1714;	//0xC4D01B60
	UINT32                                                 reserved1715;	//0xC4D01B64
	UINT32                                                 reserved1716;	//0xC4D01B68
	UINT32                                                 reserved1717;	//0xC4D01B6C
	UINT32                                                 reserved1718;	//0xC4D01B70
	UINT32                                                 reserved1719;	//0xC4D01B74
	UINT32                                                 reserved1720;	//0xC4D01B78
	UINT32                                                 reserved1721;	//0xC4D01B7C
	UINT32                                                 reserved1722;	//0xC4D01B80
	UINT32                                                 reserved1723;	//0xC4D01B84
	UINT32                                                 reserved1724;	//0xC4D01B88
	UINT32                                                 reserved1725;	//0xC4D01B8C
	UINT32                                                 reserved1726;	//0xC4D01B90
	UINT32                                                 reserved1727;	//0xC4D01B94
	UINT32                                                 reserved1728;	//0xC4D01B98
	UINT32                                                 reserved1729;	//0xC4D01B9C
	UINT32                                                 reserved1730;	//0xC4D01BA0
	UINT32                                                 reserved1731;	//0xC4D01BA4
	UINT32                                                 reserved1732;	//0xC4D01BA8
	UINT32                                                 reserved1733;	//0xC4D01BAC
	UINT32                                                 reserved1734;	//0xC4D01BB0
	UINT32                                                 reserved1735;	//0xC4D01BB4
	UINT32                                                 reserved1736;	//0xC4D01BB8
	UINT32                                                 reserved1737;	//0xC4D01BBC
	UINT32                                                 reserved1738;	//0xC4D01BC0
	UINT32                                                 reserved1739;	//0xC4D01BC4
	UINT32                                                 reserved1740;	//0xC4D01BC8
	UINT32                                                 reserved1741;	//0xC4D01BCC
	UINT32                                                 reserved1742;	//0xC4D01BD0
	UINT32                                                 reserved1743;	//0xC4D01BD4
	UINT32                                                 reserved1744;	//0xC4D01BD8
	UINT32                                                 reserved1745;	//0xC4D01BDC
	UINT32                                                 reserved1746;	//0xC4D01BE0
	UINT32                                                 reserved1747;	//0xC4D01BE4
	UINT32                                                 reserved1748;	//0xC4D01BE8
	UINT32                                                 reserved1749;	//0xC4D01BEC
	UINT32                                                 reserved1750;	//0xC4D01BF0
	UINT32                                                 reserved1751;	//0xC4D01BF4
	UINT32                                                 reserved1752;	//0xC4D01BF8
	UINT32                                                 reserved1753;	//0xC4D01BFC
	UINT32                                                 reserved1754;	//0xC4D01C00
	UINT32                                                 reserved1755;	//0xC4D01C04
	UINT32                                                 reserved1756;	//0xC4D01C08
	UINT32                                                 reserved1757;	//0xC4D01C0C
	UINT32                                                 reserved1758;	//0xC4D01C10
	UINT32                                                 reserved1759;	//0xC4D01C14
	UINT32                                                 reserved1760;	//0xC4D01C18
	UINT32                                                 reserved1761;	//0xC4D01C1C
	UINT32                                                 reserved1762;	//0xC4D01C20
	UINT32                                                 reserved1763;	//0xC4D01C24
	UINT32                                                 reserved1764;	//0xC4D01C28
	UINT32                                                 reserved1765;	//0xC4D01C2C
	UINT32                                                 reserved1766;	//0xC4D01C30
	UINT32                                                 reserved1767;	//0xC4D01C34
	UINT32                                                 reserved1768;	//0xC4D01C38
	UINT32                                                 reserved1769;	//0xC4D01C3C
	UINT32                                                 reserved1770;	//0xC4D01C40
	UINT32                                                 reserved1771;	//0xC4D01C44
	UINT32                                                 reserved1772;	//0xC4D01C48
	UINT32                                                 reserved1773;	//0xC4D01C4C
	UINT32                                                 reserved1774;	//0xC4D01C50
	UINT32                                                 reserved1775;	//0xC4D01C54
	UINT32                                                 reserved1776;	//0xC4D01C58
	UINT32                                                 reserved1777;	//0xC4D01C5C
	UINT32                                                 reserved1778;	//0xC4D01C60
	UINT32                                                 reserved1779;	//0xC4D01C64
	UINT32                                                 reserved1780;	//0xC4D01C68
	UINT32                                                 reserved1781;	//0xC4D01C6C
	UINT32                                                 reserved1782;	//0xC4D01C70
	UINT32                                                 reserved1783;	//0xC4D01C74
	UINT32                                                 reserved1784;	//0xC4D01C78
	UINT32                                                 reserved1785;	//0xC4D01C7C
	UINT32                                                 reserved1786;	//0xC4D01C80
	UINT32                                                 reserved1787;	//0xC4D01C84
	UINT32                                                 reserved1788;	//0xC4D01C88
	UINT32                                                 reserved1789;	//0xC4D01C8C
	UINT32                                                 reserved1790;	//0xC4D01C90
	UINT32                                                 reserved1791;	//0xC4D01C94
	UINT32                                                 reserved1792;	//0xC4D01C98
	UINT32                                                 reserved1793;	//0xC4D01C9C
	UINT32                                                 reserved1794;	//0xC4D01CA0
	UINT32                                                 reserved1795;	//0xC4D01CA4
	UINT32                                                 reserved1796;	//0xC4D01CA8
	UINT32                                                 reserved1797;	//0xC4D01CAC
	UINT32                                                 reserved1798;	//0xC4D01CB0
	UINT32                                                 reserved1799;	//0xC4D01CB4
	UINT32                                                 reserved1800;	//0xC4D01CB8
	UINT32                                                 reserved1801;	//0xC4D01CBC
	UINT32                                                 reserved1802;	//0xC4D01CC0
	UINT32                                                 reserved1803;	//0xC4D01CC4
	UINT32                                                 reserved1804;	//0xC4D01CC8
	UINT32                                                 reserved1805;	//0xC4D01CCC
	UINT32                                                 reserved1806;	//0xC4D01CD0
	UINT32                                                 reserved1807;	//0xC4D01CD4
	UINT32                                                 reserved1808;	//0xC4D01CD8
	UINT32                                                 reserved1809;	//0xC4D01CDC
	UINT32                                                 reserved1810;	//0xC4D01CE0
	UINT32                                                 reserved1811;	//0xC4D01CE4
	UINT32                                                 reserved1812;	//0xC4D01CE8
	UINT32                                                 reserved1813;	//0xC4D01CEC
	UINT32                                                 reserved1814;	//0xC4D01CF0
	UINT32                                                 reserved1815;	//0xC4D01CF4
	UINT32                                                 reserved1816;	//0xC4D01CF8
	UINT32                                                 reserved1817;	//0xC4D01CFC
	UINT32                                                 reserved1818;	//0xC4D01D00
	UINT32                                                 reserved1819;	//0xC4D01D04
	UINT32                                                 reserved1820;	//0xC4D01D08
	UINT32                                                 reserved1821;	//0xC4D01D0C
	UINT32                                                 reserved1822;	//0xC4D01D10
	UINT32                                                 reserved1823;	//0xC4D01D14
	UINT32                                                 reserved1824;	//0xC4D01D18
	UINT32                                                 reserved1825;	//0xC4D01D1C
	UINT32                                                 reserved1826;	//0xC4D01D20
	UINT32                                                 reserved1827;	//0xC4D01D24
	UINT32                                                 reserved1828;	//0xC4D01D28
	UINT32                                                 reserved1829;	//0xC4D01D2C
	UINT32                                                 reserved1830;	//0xC4D01D30
	UINT32                                                 reserved1831;	//0xC4D01D34
	UINT32                                                 reserved1832;	//0xC4D01D38
	UINT32                                                 reserved1833;	//0xC4D01D3C
	UINT32                                                 reserved1834;	//0xC4D01D40
	UINT32                                                 reserved1835;	//0xC4D01D44
	UINT32                                                 reserved1836;	//0xC4D01D48
	UINT32                                                 reserved1837;	//0xC4D01D4C
	UINT32                                                 reserved1838;	//0xC4D01D50
	UINT32                                                 reserved1839;	//0xC4D01D54
	UINT32                                                 reserved1840;	//0xC4D01D58
	UINT32                                                 reserved1841;	//0xC4D01D5C
	UINT32                                                 reserved1842;	//0xC4D01D60
	UINT32                                                 reserved1843;	//0xC4D01D64
	UINT32                                                 reserved1844;	//0xC4D01D68
	UINT32                                                 reserved1845;	//0xC4D01D6C
	UINT32                                                 reserved1846;	//0xC4D01D70
	UINT32                                                 reserved1847;	//0xC4D01D74
	UINT32                                                 reserved1848;	//0xC4D01D78
	UINT32                                                 reserved1849;	//0xC4D01D7C
	UINT32                                                 reserved1850;	//0xC4D01D80
	UINT32                                                 reserved1851;	//0xC4D01D84
	UINT32                                                 reserved1852;	//0xC4D01D88
	UINT32                                                 reserved1853;	//0xC4D01D8C
	UINT32                                                 reserved1854;	//0xC4D01D90
	UINT32                                                 reserved1855;	//0xC4D01D94
	UINT32                                                 reserved1856;	//0xC4D01D98
	UINT32                                                 reserved1857;	//0xC4D01D9C
	UINT32                                                 reserved1858;	//0xC4D01DA0
	UINT32                                                 reserved1859;	//0xC4D01DA4
	UINT32                                                 reserved1860;	//0xC4D01DA8
	UINT32                                                 reserved1861;	//0xC4D01DAC
	UINT32                                                 reserved1862;	//0xC4D01DB0
	UINT32                                                 reserved1863;	//0xC4D01DB4
	UINT32                                                 reserved1864;	//0xC4D01DB8
	UINT32                                                 reserved1865;	//0xC4D01DBC
	UINT32                                                 reserved1866;	//0xC4D01DC0
	UINT32                                                 reserved1867;	//0xC4D01DC4
	UINT32                                                 reserved1868;	//0xC4D01DC8
	UINT32                                                 reserved1869;	//0xC4D01DCC
	UINT32                                                 reserved1870;	//0xC4D01DD0
	UINT32                                                 reserved1871;	//0xC4D01DD4
	UINT32                                                 reserved1872;	//0xC4D01DD8
	UINT32                                                 reserved1873;	//0xC4D01DDC
	UINT32                                                 reserved1874;	//0xC4D01DE0
	UINT32                                                 reserved1875;	//0xC4D01DE4
	UINT32                                                 reserved1876;	//0xC4D01DE8
	UINT32                                                 reserved1877;	//0xC4D01DEC
	UINT32                                                 reserved1878;	//0xC4D01DF0
	UINT32                                                 reserved1879;	//0xC4D01DF4
	UINT32                                                 reserved1880;	//0xC4D01DF8
	UINT32                                                 reserved1881;	//0xC4D01DFC
	UINT32                                                 reserved1882;	//0xC4D01E00
	UINT32                                                 reserved1883;	//0xC4D01E04
	UINT32                                                 reserved1884;	//0xC4D01E08
	UINT32                                                 reserved1885;	//0xC4D01E0C
	UINT32                                                 reserved1886;	//0xC4D01E10
	UINT32                                                 reserved1887;	//0xC4D01E14
	UINT32                                                 reserved1888;	//0xC4D01E18
	UINT32                                                 reserved1889;	//0xC4D01E1C
	UINT32                                                 reserved1890;	//0xC4D01E20
	UINT32                                                 reserved1891;	//0xC4D01E24
	UINT32                                                 reserved1892;	//0xC4D01E28
	UINT32                                                 reserved1893;	//0xC4D01E2C
	UINT32                                                 reserved1894;	//0xC4D01E30
	UINT32                                                 reserved1895;	//0xC4D01E34
	UINT32                                                 reserved1896;	//0xC4D01E38
	UINT32                                                 reserved1897;	//0xC4D01E3C
	UINT32                                                 reserved1898;	//0xC4D01E40
	UINT32                                                 reserved1899;	//0xC4D01E44
	UINT32                                                 reserved1900;	//0xC4D01E48
	UINT32                                                 reserved1901;	//0xC4D01E4C
	UINT32                                                 reserved1902;	//0xC4D01E50
	UINT32                                                 reserved1903;	//0xC4D01E54
	UINT32                                                 reserved1904;	//0xC4D01E58
	UINT32                                                 reserved1905;	//0xC4D01E5C
	UINT32                                                 reserved1906;	//0xC4D01E60
	UINT32                                                 reserved1907;	//0xC4D01E64
	UINT32                                                 reserved1908;	//0xC4D01E68
	UINT32                                                 reserved1909;	//0xC4D01E6C
	UINT32                                                 reserved1910;	//0xC4D01E70
	UINT32                                                 reserved1911;	//0xC4D01E74
	UINT32                                                 reserved1912;	//0xC4D01E78
	UINT32                                                 reserved1913;	//0xC4D01E7C
	UINT32                                                 reserved1914;	//0xC4D01E80
	UINT32                                                 reserved1915;	//0xC4D01E84
	UINT32                                                 reserved1916;	//0xC4D01E88
	UINT32                                                 reserved1917;	//0xC4D01E8C
	UINT32                                                 reserved1918;	//0xC4D01E90
	UINT32                                                 reserved1919;	//0xC4D01E94
	UINT32                                                 reserved1920;	//0xC4D01E98
	UINT32                                                 reserved1921;	//0xC4D01E9C
	UINT32                                                 reserved1922;	//0xC4D01EA0
	UINT32                                                 reserved1923;	//0xC4D01EA4
	UINT32                                                 reserved1924;	//0xC4D01EA8
	UINT32                                                 reserved1925;	//0xC4D01EAC
	UINT32                                                 reserved1926;	//0xC4D01EB0
	UINT32                                                 reserved1927;	//0xC4D01EB4
	UINT32                                                 reserved1928;	//0xC4D01EB8
	UINT32                                                 reserved1929;	//0xC4D01EBC
	UINT32                                                 reserved1930;	//0xC4D01EC0
	UINT32                                                 reserved1931;	//0xC4D01EC4
	UINT32                                                 reserved1932;	//0xC4D01EC8
	UINT32                                                 reserved1933;	//0xC4D01ECC
	UINT32                                                 reserved1934;	//0xC4D01ED0
	UINT32                                                 reserved1935;	//0xC4D01ED4
	UINT32                                                 reserved1936;	//0xC4D01ED8
	UINT32                                                 reserved1937;	//0xC4D01EDC
	UINT32                                                 reserved1938;	//0xC4D01EE0
	UINT32                                                 reserved1939;	//0xC4D01EE4
	UINT32                                                 reserved1940;	//0xC4D01EE8
	UINT32                                                 reserved1941;	//0xC4D01EEC
	UINT32                                                 reserved1942;	//0xC4D01EF0
	UINT32                                                 reserved1943;	//0xC4D01EF4
	UINT32                                                 reserved1944;	//0xC4D01EF8
	UINT32                                                 reserved1945;	//0xC4D01EFC
	UINT32                                                 reserved1946;	//0xC4D01F00
	UINT32                                                 reserved1947;	//0xC4D01F04
	UINT32                                                 reserved1948;	//0xC4D01F08
	UINT32                                                 reserved1949;	//0xC4D01F0C
	UINT32                                                 reserved1950;	//0xC4D01F10
	UINT32                                                 reserved1951;	//0xC4D01F14
	UINT32                                                 reserved1952;	//0xC4D01F18
	UINT32                                                 reserved1953;	//0xC4D01F1C
	UINT32                                                 reserved1954;	//0xC4D01F20
	UINT32                                                 reserved1955;	//0xC4D01F24
	UINT32                                                 reserved1956;	//0xC4D01F28
	UINT32                                                 reserved1957;	//0xC4D01F2C
	UINT32                                                 reserved1958;	//0xC4D01F30
	UINT32                                                 reserved1959;	//0xC4D01F34
	UINT32                                                 reserved1960;	//0xC4D01F38
	UINT32                                                 reserved1961;	//0xC4D01F3C
	UINT32                                                 reserved1962;	//0xC4D01F40
	UINT32                                                 reserved1963;	//0xC4D01F44
	UINT32                                                 reserved1964;	//0xC4D01F48
	UINT32                                                 reserved1965;	//0xC4D01F4C
	UINT32                                                 reserved1966;	//0xC4D01F50
	UINT32                                                 reserved1967;	//0xC4D01F54
	UINT32                                                 reserved1968;	//0xC4D01F58
	UINT32                                                 reserved1969;	//0xC4D01F5C
	UINT32                                                 reserved1970;	//0xC4D01F60
	UINT32                                                 reserved1971;	//0xC4D01F64
	UINT32                                                 reserved1972;	//0xC4D01F68
	UINT32                                                 reserved1973;	//0xC4D01F6C
	UINT32                                                 reserved1974;	//0xC4D01F70
	UINT32                                                 reserved1975;	//0xC4D01F74
	UINT32                                                 reserved1976;	//0xC4D01F78
	UINT32                                                 reserved1977;	//0xC4D01F7C
	UINT32                                                 reserved1978;	//0xC4D01F80
	UINT32                                                 reserved1979;	//0xC4D01F84
	UINT32                                                 reserved1980;	//0xC4D01F88
	UINT32                                                 reserved1981;	//0xC4D01F8C
	UINT32                                                 reserved1982;	//0xC4D01F90
	UINT32                                                 reserved1983;	//0xC4D01F94
	UINT32                                                 reserved1984;	//0xC4D01F98
	UINT32                                                 reserved1985;	//0xC4D01F9C
	UINT32                                                 reserved1986;	//0xC4D01FA0
	UINT32                                                 reserved1987;	//0xC4D01FA4
	UINT32                                                 reserved1988;	//0xC4D01FA8
	UINT32                                                 reserved1989;	//0xC4D01FAC
	UINT32                                                 reserved1990;	//0xC4D01FB0
	UINT32                                                 reserved1991;	//0xC4D01FB4
	UINT32                                                 reserved1992;	//0xC4D01FB8
	UINT32                                                 reserved1993;	//0xC4D01FBC
	UINT32                                                 reserved1994;	//0xC4D01FC0
	UINT32                                                 reserved1995;	//0xC4D01FC4
	UINT32                                                 reserved1996;	//0xC4D01FC8
	UINT32                                                 reserved1997;	//0xC4D01FCC
	UINT32                                                 reserved1998;	//0xC4D01FD0
	UINT32                                                 reserved1999;	//0xC4D01FD4
	UINT32                                                 reserved2000;	//0xC4D01FD8
	UINT32                                                 reserved2001;	//0xC4D01FDC
	UINT32                                                 reserved2002;	//0xC4D01FE0
	UINT32                                                 reserved2003;	//0xC4D01FE4
	UINT32                                                 reserved2004;	//0xC4D01FE8
	UINT32                                                 reserved2005;	//0xC4D01FEC
	UINT32                                                 reserved2006;	//0xC4D01FF0
	UINT32                                                 reserved2007;	//0xC4D01FF4
	UINT32                                                 reserved2008;	//0xC4D01FF8
	UINT32                                                 reserved2009;	//0xC4D01FFC
	REG_DDRC_M0_PQ_T                                                 pq;	//0xC4D02000
	REG_DDRC_M0_BQ_T                                                 bq;	//0xC4D02004
	REG_DDRC_M0_BQ_RW_THR_T                                   bq_rw_thr;	//0xC4D02008
	REG_DDRC_M0_BQ_HYB_STV_T                                 bq_hyb_stv;	//0xC4D0200C
	UINT32                                                 reserved2010;	//0xC4D02010
	UINT32                                                 reserved2011;	//0xC4D02014
	UINT32                                                 reserved2012;	//0xC4D02018
	UINT32                                                 reserved2013;	//0xC4D0201C
	UINT32                                                 reserved2014;	//0xC4D02020
	UINT32                                                 reserved2015;	//0xC4D02024
	UINT32                                                 reserved2016;	//0xC4D02028
	UINT32                                                 reserved2017;	//0xC4D0202C
	UINT32                                                 reserved2018;	//0xC4D02030
	UINT32                                                 reserved2019;	//0xC4D02034
	UINT32                                                 reserved2020;	//0xC4D02038
	UINT32                                                 reserved2021;	//0xC4D0203C
	UINT32                                                 reserved2022;	//0xC4D02040
	UINT32                                                 reserved2023;	//0xC4D02044
	UINT32                                                 reserved2024;	//0xC4D02048
	UINT32                                                 reserved2025;	//0xC4D0204C
	UINT32                                                 reserved2026;	//0xC4D02050
	UINT32                                                 reserved2027;	//0xC4D02054
	UINT32                                                 reserved2028;	//0xC4D02058
	UINT32                                                 reserved2029;	//0xC4D0205C
	UINT32                                                 reserved2030;	//0xC4D02060
	UINT32                                                 reserved2031;	//0xC4D02064
	UINT32                                                 reserved2032;	//0xC4D02068
	UINT32                                                 reserved2033;	//0xC4D0206C
	UINT32                                                 reserved2034;	//0xC4D02070
	UINT32                                                 reserved2035;	//0xC4D02074
	UINT32                                                 reserved2036;	//0xC4D02078
	UINT32                                                 reserved2037;	//0xC4D0207C
	UINT32                                                 reserved2038;	//0xC4D02080
	UINT32                                                 reserved2039;	//0xC4D02084
	UINT32                                                 reserved2040;	//0xC4D02088
	UINT32                                                 reserved2041;	//0xC4D0208C
	UINT32                                                 reserved2042;	//0xC4D02090
	UINT32                                                 reserved2043;	//0xC4D02094
	UINT32                                                 reserved2044;	//0xC4D02098
	UINT32                                                 reserved2045;	//0xC4D0209C
	UINT32                                                 reserved2046;	//0xC4D020A0
	UINT32                                                 reserved2047;	//0xC4D020A4
	UINT32                                                 reserved2048;	//0xC4D020A8
	UINT32                                                 reserved2049;	//0xC4D020AC
	UINT32                                                 reserved2050;	//0xC4D020B0
	UINT32                                                 reserved2051;	//0xC4D020B4
	UINT32                                                 reserved2052;	//0xC4D020B8
	UINT32                                                 reserved2053;	//0xC4D020BC
	UINT32                                                 reserved2054;	//0xC4D020C0
	UINT32                                                 reserved2055;	//0xC4D020C4
	UINT32                                                 reserved2056;	//0xC4D020C8
	UINT32                                                 reserved2057;	//0xC4D020CC
	UINT32                                                 reserved2058;	//0xC4D020D0
	UINT32                                                 reserved2059;	//0xC4D020D4
	UINT32                                                 reserved2060;	//0xC4D020D8
	UINT32                                                 reserved2061;	//0xC4D020DC
	UINT32                                                 reserved2062;	//0xC4D020E0
	UINT32                                                 reserved2063;	//0xC4D020E4
	UINT32                                                 reserved2064;	//0xC4D020E8
	UINT32                                                 reserved2065;	//0xC4D020EC
	UINT32                                                 reserved2066;	//0xC4D020F0
	UINT32                                                 reserved2067;	//0xC4D020F4
	UINT32                                                 reserved2068;	//0xC4D020F8
	UINT32                                                 reserved2069;	//0xC4D020FC
	UINT32                                                 reserved2070;	//0xC4D02100
	UINT32                                                 reserved2071;	//0xC4D02104
	UINT32                                                 reserved2072;	//0xC4D02108
	UINT32                                                 reserved2073;	//0xC4D0210C
	UINT32                                                 reserved2074;	//0xC4D02110
	UINT32                                                 reserved2075;	//0xC4D02114
	UINT32                                                 reserved2076;	//0xC4D02118
	UINT32                                                 reserved2077;	//0xC4D0211C
	UINT32                                                 reserved2078;	//0xC4D02120
	UINT32                                                 reserved2079;	//0xC4D02124
	UINT32                                                 reserved2080;	//0xC4D02128
	UINT32                                                 reserved2081;	//0xC4D0212C
	UINT32                                                 reserved2082;	//0xC4D02130
	UINT32                                                 reserved2083;	//0xC4D02134
	UINT32                                                 reserved2084;	//0xC4D02138
	UINT32                                                 reserved2085;	//0xC4D0213C
	UINT32                                                 reserved2086;	//0xC4D02140
	UINT32                                                 reserved2087;	//0xC4D02144
	UINT32                                                 reserved2088;	//0xC4D02148
	UINT32                                                 reserved2089;	//0xC4D0214C
	UINT32                                                 reserved2090;	//0xC4D02150
	UINT32                                                 reserved2091;	//0xC4D02154
	UINT32                                                 reserved2092;	//0xC4D02158
	UINT32                                                 reserved2093;	//0xC4D0215C
	UINT32                                                 reserved2094;	//0xC4D02160
	UINT32                                                 reserved2095;	//0xC4D02164
	UINT32                                                 reserved2096;	//0xC4D02168
	UINT32                                                 reserved2097;	//0xC4D0216C
	UINT32                                                 reserved2098;	//0xC4D02170
	UINT32                                                 reserved2099;	//0xC4D02174
	UINT32                                                 reserved2100;	//0xC4D02178
	UINT32                                                 reserved2101;	//0xC4D0217C
	UINT32                                                 reserved2102;	//0xC4D02180
	UINT32                                                 reserved2103;	//0xC4D02184
	UINT32                                                 reserved2104;	//0xC4D02188
	UINT32                                                 reserved2105;	//0xC4D0218C
	UINT32                                                 reserved2106;	//0xC4D02190
	UINT32                                                 reserved2107;	//0xC4D02194
	UINT32                                                 reserved2108;	//0xC4D02198
	UINT32                                                 reserved2109;	//0xC4D0219C
	UINT32                                                 reserved2110;	//0xC4D021A0
	UINT32                                                 reserved2111;	//0xC4D021A4
	UINT32                                                 reserved2112;	//0xC4D021A8
	UINT32                                                 reserved2113;	//0xC4D021AC
	UINT32                                                 reserved2114;	//0xC4D021B0
	UINT32                                                 reserved2115;	//0xC4D021B4
	UINT32                                                 reserved2116;	//0xC4D021B8
	UINT32                                                 reserved2117;	//0xC4D021BC
	UINT32                                                 reserved2118;	//0xC4D021C0
	UINT32                                                 reserved2119;	//0xC4D021C4
	UINT32                                                 reserved2120;	//0xC4D021C8
	UINT32                                                 reserved2121;	//0xC4D021CC
	UINT32                                                 reserved2122;	//0xC4D021D0
	UINT32                                                 reserved2123;	//0xC4D021D4
	UINT32                                                 reserved2124;	//0xC4D021D8
	UINT32                                                 reserved2125;	//0xC4D021DC
	UINT32                                                 reserved2126;	//0xC4D021E0
	UINT32                                                 reserved2127;	//0xC4D021E4
	UINT32                                                 reserved2128;	//0xC4D021E8
	UINT32                                                 reserved2129;	//0xC4D021EC
	UINT32                                                 reserved2130;	//0xC4D021F0
	UINT32                                                 reserved2131;	//0xC4D021F4
	UINT32                                                 reserved2132;	//0xC4D021F8
	UINT32                                                 reserved2133;	//0xC4D021FC
	UINT32                                                 reserved2134;	//0xC4D02200
	UINT32                                                 reserved2135;	//0xC4D02204
	UINT32                                                 reserved2136;	//0xC4D02208
	UINT32                                                 reserved2137;	//0xC4D0220C
	UINT32                                                 reserved2138;	//0xC4D02210
	UINT32                                                 reserved2139;	//0xC4D02214
	UINT32                                                 reserved2140;	//0xC4D02218
	UINT32                                                 reserved2141;	//0xC4D0221C
	UINT32                                                 reserved2142;	//0xC4D02220
	UINT32                                                 reserved2143;	//0xC4D02224
	UINT32                                                 reserved2144;	//0xC4D02228
	UINT32                                                 reserved2145;	//0xC4D0222C
	UINT32                                                 reserved2146;	//0xC4D02230
	UINT32                                                 reserved2147;	//0xC4D02234
	UINT32                                                 reserved2148;	//0xC4D02238
	UINT32                                                 reserved2149;	//0xC4D0223C
	UINT32                                                 reserved2150;	//0xC4D02240
	UINT32                                                 reserved2151;	//0xC4D02244
	UINT32                                                 reserved2152;	//0xC4D02248
	UINT32                                                 reserved2153;	//0xC4D0224C
	UINT32                                                 reserved2154;	//0xC4D02250
	UINT32                                                 reserved2155;	//0xC4D02254
	UINT32                                                 reserved2156;	//0xC4D02258
	UINT32                                                 reserved2157;	//0xC4D0225C
	UINT32                                                 reserved2158;	//0xC4D02260
	UINT32                                                 reserved2159;	//0xC4D02264
	UINT32                                                 reserved2160;	//0xC4D02268
	UINT32                                                 reserved2161;	//0xC4D0226C
	UINT32                                                 reserved2162;	//0xC4D02270
	UINT32                                                 reserved2163;	//0xC4D02274
	UINT32                                                 reserved2164;	//0xC4D02278
	UINT32                                                 reserved2165;	//0xC4D0227C
	UINT32                                                 reserved2166;	//0xC4D02280
	UINT32                                                 reserved2167;	//0xC4D02284
	UINT32                                                 reserved2168;	//0xC4D02288
	UINT32                                                 reserved2169;	//0xC4D0228C
	UINT32                                                 reserved2170;	//0xC4D02290
	UINT32                                                 reserved2171;	//0xC4D02294
	UINT32                                                 reserved2172;	//0xC4D02298
	UINT32                                                 reserved2173;	//0xC4D0229C
	UINT32                                                 reserved2174;	//0xC4D022A0
	UINT32                                                 reserved2175;	//0xC4D022A4
	UINT32                                                 reserved2176;	//0xC4D022A8
	UINT32                                                 reserved2177;	//0xC4D022AC
	UINT32                                                 reserved2178;	//0xC4D022B0
	UINT32                                                 reserved2179;	//0xC4D022B4
	UINT32                                                 reserved2180;	//0xC4D022B8
	UINT32                                                 reserved2181;	//0xC4D022BC
	UINT32                                                 reserved2182;	//0xC4D022C0
	UINT32                                                 reserved2183;	//0xC4D022C4
	UINT32                                                 reserved2184;	//0xC4D022C8
	UINT32                                                 reserved2185;	//0xC4D022CC
	UINT32                                                 reserved2186;	//0xC4D022D0
	UINT32                                                 reserved2187;	//0xC4D022D4
	UINT32                                                 reserved2188;	//0xC4D022D8
	UINT32                                                 reserved2189;	//0xC4D022DC
	UINT32                                                 reserved2190;	//0xC4D022E0
	UINT32                                                 reserved2191;	//0xC4D022E4
	UINT32                                                 reserved2192;	//0xC4D022E8
	UINT32                                                 reserved2193;	//0xC4D022EC
	UINT32                                                 reserved2194;	//0xC4D022F0
	UINT32                                                 reserved2195;	//0xC4D022F4
	UINT32                                                 reserved2196;	//0xC4D022F8
	UINT32                                                 reserved2197;	//0xC4D022FC
	UINT32                                                 reserved2198;	//0xC4D02300
	UINT32                                                 reserved2199;	//0xC4D02304
	UINT32                                                 reserved2200;	//0xC4D02308
	UINT32                                                 reserved2201;	//0xC4D0230C
	UINT32                                                 reserved2202;	//0xC4D02310
	UINT32                                                 reserved2203;	//0xC4D02314
	UINT32                                                 reserved2204;	//0xC4D02318
	UINT32                                                 reserved2205;	//0xC4D0231C
	UINT32                                                 reserved2206;	//0xC4D02320
	UINT32                                                 reserved2207;	//0xC4D02324
	UINT32                                                 reserved2208;	//0xC4D02328
	UINT32                                                 reserved2209;	//0xC4D0232C
	UINT32                                                 reserved2210;	//0xC4D02330
	UINT32                                                 reserved2211;	//0xC4D02334
	UINT32                                                 reserved2212;	//0xC4D02338
	UINT32                                                 reserved2213;	//0xC4D0233C
	UINT32                                                 reserved2214;	//0xC4D02340
	UINT32                                                 reserved2215;	//0xC4D02344
	UINT32                                                 reserved2216;	//0xC4D02348
	UINT32                                                 reserved2217;	//0xC4D0234C
	UINT32                                                 reserved2218;	//0xC4D02350
	UINT32                                                 reserved2219;	//0xC4D02354
	UINT32                                                 reserved2220;	//0xC4D02358
	UINT32                                                 reserved2221;	//0xC4D0235C
	UINT32                                                 reserved2222;	//0xC4D02360
	UINT32                                                 reserved2223;	//0xC4D02364
	UINT32                                                 reserved2224;	//0xC4D02368
	UINT32                                                 reserved2225;	//0xC4D0236C
	UINT32                                                 reserved2226;	//0xC4D02370
	UINT32                                                 reserved2227;	//0xC4D02374
	UINT32                                                 reserved2228;	//0xC4D02378
	UINT32                                                 reserved2229;	//0xC4D0237C
	UINT32                                                 reserved2230;	//0xC4D02380
	UINT32                                                 reserved2231;	//0xC4D02384
	UINT32                                                 reserved2232;	//0xC4D02388
	UINT32                                                 reserved2233;	//0xC4D0238C
	UINT32                                                 reserved2234;	//0xC4D02390
	UINT32                                                 reserved2235;	//0xC4D02394
	UINT32                                                 reserved2236;	//0xC4D02398
	UINT32                                                 reserved2237;	//0xC4D0239C
	UINT32                                                 reserved2238;	//0xC4D023A0
	UINT32                                                 reserved2239;	//0xC4D023A4
	UINT32                                                 reserved2240;	//0xC4D023A8
	UINT32                                                 reserved2241;	//0xC4D023AC
	UINT32                                                 reserved2242;	//0xC4D023B0
	UINT32                                                 reserved2243;	//0xC4D023B4
	UINT32                                                 reserved2244;	//0xC4D023B8
	UINT32                                                 reserved2245;	//0xC4D023BC
	UINT32                                                 reserved2246;	//0xC4D023C0
	UINT32                                                 reserved2247;	//0xC4D023C4
	UINT32                                                 reserved2248;	//0xC4D023C8
	UINT32                                                 reserved2249;	//0xC4D023CC
	UINT32                                                 reserved2250;	//0xC4D023D0
	UINT32                                                 reserved2251;	//0xC4D023D4
	UINT32                                                 reserved2252;	//0xC4D023D8
	UINT32                                                 reserved2253;	//0xC4D023DC
	UINT32                                                 reserved2254;	//0xC4D023E0
	UINT32                                                 reserved2255;	//0xC4D023E4
	UINT32                                                 reserved2256;	//0xC4D023E8
	UINT32                                                 reserved2257;	//0xC4D023EC
	UINT32                                                 reserved2258;	//0xC4D023F0
	UINT32                                                 reserved2259;	//0xC4D023F4
	UINT32                                                 reserved2260;	//0xC4D023F8
	UINT32                                                 reserved2261;	//0xC4D023FC
	UINT32                                                 reserved2262;	//0xC4D02400
	UINT32                                                 reserved2263;	//0xC4D02404
	UINT32                                                 reserved2264;	//0xC4D02408
	UINT32                                                 reserved2265;	//0xC4D0240C
	UINT32                                                 reserved2266;	//0xC4D02410
	UINT32                                                 reserved2267;	//0xC4D02414
	UINT32                                                 reserved2268;	//0xC4D02418
	UINT32                                                 reserved2269;	//0xC4D0241C
	UINT32                                                 reserved2270;	//0xC4D02420
	UINT32                                                 reserved2271;	//0xC4D02424
	UINT32                                                 reserved2272;	//0xC4D02428
	UINT32                                                 reserved2273;	//0xC4D0242C
	UINT32                                                 reserved2274;	//0xC4D02430
	UINT32                                                 reserved2275;	//0xC4D02434
	UINT32                                                 reserved2276;	//0xC4D02438
	UINT32                                                 reserved2277;	//0xC4D0243C
	UINT32                                                 reserved2278;	//0xC4D02440
	UINT32                                                 reserved2279;	//0xC4D02444
	UINT32                                                 reserved2280;	//0xC4D02448
	UINT32                                                 reserved2281;	//0xC4D0244C
	UINT32                                                 reserved2282;	//0xC4D02450
	UINT32                                                 reserved2283;	//0xC4D02454
	UINT32                                                 reserved2284;	//0xC4D02458
	UINT32                                                 reserved2285;	//0xC4D0245C
	UINT32                                                 reserved2286;	//0xC4D02460
	UINT32                                                 reserved2287;	//0xC4D02464
	UINT32                                                 reserved2288;	//0xC4D02468
	UINT32                                                 reserved2289;	//0xC4D0246C
	UINT32                                                 reserved2290;	//0xC4D02470
	UINT32                                                 reserved2291;	//0xC4D02474
	UINT32                                                 reserved2292;	//0xC4D02478
	UINT32                                                 reserved2293;	//0xC4D0247C
	UINT32                                                 reserved2294;	//0xC4D02480
	UINT32                                                 reserved2295;	//0xC4D02484
	UINT32                                                 reserved2296;	//0xC4D02488
	UINT32                                                 reserved2297;	//0xC4D0248C
	UINT32                                                 reserved2298;	//0xC4D02490
	UINT32                                                 reserved2299;	//0xC4D02494
	UINT32                                                 reserved2300;	//0xC4D02498
	UINT32                                                 reserved2301;	//0xC4D0249C
	UINT32                                                 reserved2302;	//0xC4D024A0
	UINT32                                                 reserved2303;	//0xC4D024A4
	UINT32                                                 reserved2304;	//0xC4D024A8
	UINT32                                                 reserved2305;	//0xC4D024AC
	UINT32                                                 reserved2306;	//0xC4D024B0
	UINT32                                                 reserved2307;	//0xC4D024B4
	UINT32                                                 reserved2308;	//0xC4D024B8
	UINT32                                                 reserved2309;	//0xC4D024BC
	UINT32                                                 reserved2310;	//0xC4D024C0
	UINT32                                                 reserved2311;	//0xC4D024C4
	UINT32                                                 reserved2312;	//0xC4D024C8
	UINT32                                                 reserved2313;	//0xC4D024CC
	UINT32                                                 reserved2314;	//0xC4D024D0
	UINT32                                                 reserved2315;	//0xC4D024D4
	UINT32                                                 reserved2316;	//0xC4D024D8
	UINT32                                                 reserved2317;	//0xC4D024DC
	UINT32                                                 reserved2318;	//0xC4D024E0
	UINT32                                                 reserved2319;	//0xC4D024E4
	UINT32                                                 reserved2320;	//0xC4D024E8
	UINT32                                                 reserved2321;	//0xC4D024EC
	UINT32                                                 reserved2322;	//0xC4D024F0
	UINT32                                                 reserved2323;	//0xC4D024F4
	UINT32                                                 reserved2324;	//0xC4D024F8
	UINT32                                                 reserved2325;	//0xC4D024FC
	UINT32                                                 reserved2326;	//0xC4D02500
	UINT32                                                 reserved2327;	//0xC4D02504
	UINT32                                                 reserved2328;	//0xC4D02508
	UINT32                                                 reserved2329;	//0xC4D0250C
	UINT32                                                 reserved2330;	//0xC4D02510
	UINT32                                                 reserved2331;	//0xC4D02514
	UINT32                                                 reserved2332;	//0xC4D02518
	UINT32                                                 reserved2333;	//0xC4D0251C
	UINT32                                                 reserved2334;	//0xC4D02520
	UINT32                                                 reserved2335;	//0xC4D02524
	UINT32                                                 reserved2336;	//0xC4D02528
	UINT32                                                 reserved2337;	//0xC4D0252C
	UINT32                                                 reserved2338;	//0xC4D02530
	UINT32                                                 reserved2339;	//0xC4D02534
	UINT32                                                 reserved2340;	//0xC4D02538
	UINT32                                                 reserved2341;	//0xC4D0253C
	UINT32                                                 reserved2342;	//0xC4D02540
	UINT32                                                 reserved2343;	//0xC4D02544
	UINT32                                                 reserved2344;	//0xC4D02548
	UINT32                                                 reserved2345;	//0xC4D0254C
	UINT32                                                 reserved2346;	//0xC4D02550
	UINT32                                                 reserved2347;	//0xC4D02554
	UINT32                                                 reserved2348;	//0xC4D02558
	UINT32                                                 reserved2349;	//0xC4D0255C
	UINT32                                                 reserved2350;	//0xC4D02560
	UINT32                                                 reserved2351;	//0xC4D02564
	UINT32                                                 reserved2352;	//0xC4D02568
	UINT32                                                 reserved2353;	//0xC4D0256C
	UINT32                                                 reserved2354;	//0xC4D02570
	UINT32                                                 reserved2355;	//0xC4D02574
	UINT32                                                 reserved2356;	//0xC4D02578
	UINT32                                                 reserved2357;	//0xC4D0257C
	UINT32                                                 reserved2358;	//0xC4D02580
	UINT32                                                 reserved2359;	//0xC4D02584
	UINT32                                                 reserved2360;	//0xC4D02588
	UINT32                                                 reserved2361;	//0xC4D0258C
	UINT32                                                 reserved2362;	//0xC4D02590
	UINT32                                                 reserved2363;	//0xC4D02594
	UINT32                                                 reserved2364;	//0xC4D02598
	UINT32                                                 reserved2365;	//0xC4D0259C
	UINT32                                                 reserved2366;	//0xC4D025A0
	UINT32                                                 reserved2367;	//0xC4D025A4
	UINT32                                                 reserved2368;	//0xC4D025A8
	UINT32                                                 reserved2369;	//0xC4D025AC
	UINT32                                                 reserved2370;	//0xC4D025B0
	UINT32                                                 reserved2371;	//0xC4D025B4
	UINT32                                                 reserved2372;	//0xC4D025B8
	UINT32                                                 reserved2373;	//0xC4D025BC
	UINT32                                                 reserved2374;	//0xC4D025C0
	UINT32                                                 reserved2375;	//0xC4D025C4
	UINT32                                                 reserved2376;	//0xC4D025C8
	UINT32                                                 reserved2377;	//0xC4D025CC
	UINT32                                                 reserved2378;	//0xC4D025D0
	UINT32                                                 reserved2379;	//0xC4D025D4
	UINT32                                                 reserved2380;	//0xC4D025D8
	UINT32                                                 reserved2381;	//0xC4D025DC
	UINT32                                                 reserved2382;	//0xC4D025E0
	UINT32                                                 reserved2383;	//0xC4D025E4
	UINT32                                                 reserved2384;	//0xC4D025E8
	UINT32                                                 reserved2385;	//0xC4D025EC
	UINT32                                                 reserved2386;	//0xC4D025F0
	UINT32                                                 reserved2387;	//0xC4D025F4
	UINT32                                                 reserved2388;	//0xC4D025F8
	UINT32                                                 reserved2389;	//0xC4D025FC
	UINT32                                                 reserved2390;	//0xC4D02600
	UINT32                                                 reserved2391;	//0xC4D02604
	UINT32                                                 reserved2392;	//0xC4D02608
	UINT32                                                 reserved2393;	//0xC4D0260C
	UINT32                                                 reserved2394;	//0xC4D02610
	UINT32                                                 reserved2395;	//0xC4D02614
	UINT32                                                 reserved2396;	//0xC4D02618
	UINT32                                                 reserved2397;	//0xC4D0261C
	UINT32                                                 reserved2398;	//0xC4D02620
	UINT32                                                 reserved2399;	//0xC4D02624
	UINT32                                                 reserved2400;	//0xC4D02628
	UINT32                                                 reserved2401;	//0xC4D0262C
	UINT32                                                 reserved2402;	//0xC4D02630
	UINT32                                                 reserved2403;	//0xC4D02634
	UINT32                                                 reserved2404;	//0xC4D02638
	UINT32                                                 reserved2405;	//0xC4D0263C
	UINT32                                                 reserved2406;	//0xC4D02640
	UINT32                                                 reserved2407;	//0xC4D02644
	UINT32                                                 reserved2408;	//0xC4D02648
	UINT32                                                 reserved2409;	//0xC4D0264C
	UINT32                                                 reserved2410;	//0xC4D02650
	UINT32                                                 reserved2411;	//0xC4D02654
	UINT32                                                 reserved2412;	//0xC4D02658
	UINT32                                                 reserved2413;	//0xC4D0265C
	UINT32                                                 reserved2414;	//0xC4D02660
	UINT32                                                 reserved2415;	//0xC4D02664
	UINT32                                                 reserved2416;	//0xC4D02668
	UINT32                                                 reserved2417;	//0xC4D0266C
	UINT32                                                 reserved2418;	//0xC4D02670
	UINT32                                                 reserved2419;	//0xC4D02674
	UINT32                                                 reserved2420;	//0xC4D02678
	UINT32                                                 reserved2421;	//0xC4D0267C
	UINT32                                                 reserved2422;	//0xC4D02680
	UINT32                                                 reserved2423;	//0xC4D02684
	UINT32                                                 reserved2424;	//0xC4D02688
	UINT32                                                 reserved2425;	//0xC4D0268C
	UINT32                                                 reserved2426;	//0xC4D02690
	UINT32                                                 reserved2427;	//0xC4D02694
	UINT32                                                 reserved2428;	//0xC4D02698
	UINT32                                                 reserved2429;	//0xC4D0269C
	UINT32                                                 reserved2430;	//0xC4D026A0
	UINT32                                                 reserved2431;	//0xC4D026A4
	UINT32                                                 reserved2432;	//0xC4D026A8
	UINT32                                                 reserved2433;	//0xC4D026AC
	UINT32                                                 reserved2434;	//0xC4D026B0
	UINT32                                                 reserved2435;	//0xC4D026B4
	UINT32                                                 reserved2436;	//0xC4D026B8
	UINT32                                                 reserved2437;	//0xC4D026BC
	UINT32                                                 reserved2438;	//0xC4D026C0
	UINT32                                                 reserved2439;	//0xC4D026C4
	UINT32                                                 reserved2440;	//0xC4D026C8
	UINT32                                                 reserved2441;	//0xC4D026CC
	UINT32                                                 reserved2442;	//0xC4D026D0
	UINT32                                                 reserved2443;	//0xC4D026D4
	UINT32                                                 reserved2444;	//0xC4D026D8
	UINT32                                                 reserved2445;	//0xC4D026DC
	UINT32                                                 reserved2446;	//0xC4D026E0
	UINT32                                                 reserved2447;	//0xC4D026E4
	UINT32                                                 reserved2448;	//0xC4D026E8
	UINT32                                                 reserved2449;	//0xC4D026EC
	UINT32                                                 reserved2450;	//0xC4D026F0
	UINT32                                                 reserved2451;	//0xC4D026F4
	UINT32                                                 reserved2452;	//0xC4D026F8
	UINT32                                                 reserved2453;	//0xC4D026FC
	UINT32                                                 reserved2454;	//0xC4D02700
	UINT32                                                 reserved2455;	//0xC4D02704
	UINT32                                                 reserved2456;	//0xC4D02708
	UINT32                                                 reserved2457;	//0xC4D0270C
	UINT32                                                 reserved2458;	//0xC4D02710
	UINT32                                                 reserved2459;	//0xC4D02714
	UINT32                                                 reserved2460;	//0xC4D02718
	UINT32                                                 reserved2461;	//0xC4D0271C
	UINT32                                                 reserved2462;	//0xC4D02720
	UINT32                                                 reserved2463;	//0xC4D02724
	UINT32                                                 reserved2464;	//0xC4D02728
	UINT32                                                 reserved2465;	//0xC4D0272C
	UINT32                                                 reserved2466;	//0xC4D02730
	UINT32                                                 reserved2467;	//0xC4D02734
	UINT32                                                 reserved2468;	//0xC4D02738
	UINT32                                                 reserved2469;	//0xC4D0273C
	UINT32                                                 reserved2470;	//0xC4D02740
	UINT32                                                 reserved2471;	//0xC4D02744
	UINT32                                                 reserved2472;	//0xC4D02748
	UINT32                                                 reserved2473;	//0xC4D0274C
	UINT32                                                 reserved2474;	//0xC4D02750
	UINT32                                                 reserved2475;	//0xC4D02754
	UINT32                                                 reserved2476;	//0xC4D02758
	UINT32                                                 reserved2477;	//0xC4D0275C
	UINT32                                                 reserved2478;	//0xC4D02760
	UINT32                                                 reserved2479;	//0xC4D02764
	UINT32                                                 reserved2480;	//0xC4D02768
	UINT32                                                 reserved2481;	//0xC4D0276C
	UINT32                                                 reserved2482;	//0xC4D02770
	UINT32                                                 reserved2483;	//0xC4D02774
	UINT32                                                 reserved2484;	//0xC4D02778
	UINT32                                                 reserved2485;	//0xC4D0277C
	UINT32                                                 reserved2486;	//0xC4D02780
	UINT32                                                 reserved2487;	//0xC4D02784
	UINT32                                                 reserved2488;	//0xC4D02788
	UINT32                                                 reserved2489;	//0xC4D0278C
	UINT32                                                 reserved2490;	//0xC4D02790
	UINT32                                                 reserved2491;	//0xC4D02794
	UINT32                                                 reserved2492;	//0xC4D02798
	UINT32                                                 reserved2493;	//0xC4D0279C
	UINT32                                                 reserved2494;	//0xC4D027A0
	UINT32                                                 reserved2495;	//0xC4D027A4
	UINT32                                                 reserved2496;	//0xC4D027A8
	UINT32                                                 reserved2497;	//0xC4D027AC
	UINT32                                                 reserved2498;	//0xC4D027B0
	UINT32                                                 reserved2499;	//0xC4D027B4
	UINT32                                                 reserved2500;	//0xC4D027B8
	UINT32                                                 reserved2501;	//0xC4D027BC
	UINT32                                                 reserved2502;	//0xC4D027C0
	UINT32                                                 reserved2503;	//0xC4D027C4
	UINT32                                                 reserved2504;	//0xC4D027C8
	UINT32                                                 reserved2505;	//0xC4D027CC
	UINT32                                                 reserved2506;	//0xC4D027D0
	UINT32                                                 reserved2507;	//0xC4D027D4
	UINT32                                                 reserved2508;	//0xC4D027D8
	UINT32                                                 reserved2509;	//0xC4D027DC
	UINT32                                                 reserved2510;	//0xC4D027E0
	UINT32                                                 reserved2511;	//0xC4D027E4
	UINT32                                                 reserved2512;	//0xC4D027E8
	UINT32                                                 reserved2513;	//0xC4D027EC
	UINT32                                                 reserved2514;	//0xC4D027F0
	UINT32                                                 reserved2515;	//0xC4D027F4
	UINT32                                                 reserved2516;	//0xC4D027F8
	UINT32                                                 reserved2517;	//0xC4D027FC
	UINT32                                                 reserved2518;	//0xC4D02800
	UINT32                                                 reserved2519;	//0xC4D02804
	UINT32                                                 reserved2520;	//0xC4D02808
	UINT32                                                 reserved2521;	//0xC4D0280C
	UINT32                                                 reserved2522;	//0xC4D02810
	UINT32                                                 reserved2523;	//0xC4D02814
	UINT32                                                 reserved2524;	//0xC4D02818
	UINT32                                                 reserved2525;	//0xC4D0281C
	UINT32                                                 reserved2526;	//0xC4D02820
	UINT32                                                 reserved2527;	//0xC4D02824
	UINT32                                                 reserved2528;	//0xC4D02828
	UINT32                                                 reserved2529;	//0xC4D0282C
	UINT32                                                 reserved2530;	//0xC4D02830
	UINT32                                                 reserved2531;	//0xC4D02834
	UINT32                                                 reserved2532;	//0xC4D02838
	UINT32                                                 reserved2533;	//0xC4D0283C
	UINT32                                                 reserved2534;	//0xC4D02840
	UINT32                                                 reserved2535;	//0xC4D02844
	UINT32                                                 reserved2536;	//0xC4D02848
	UINT32                                                 reserved2537;	//0xC4D0284C
	UINT32                                                 reserved2538;	//0xC4D02850
	UINT32                                                 reserved2539;	//0xC4D02854
	UINT32                                                 reserved2540;	//0xC4D02858
	UINT32                                                 reserved2541;	//0xC4D0285C
	UINT32                                                 reserved2542;	//0xC4D02860
	UINT32                                                 reserved2543;	//0xC4D02864
	UINT32                                                 reserved2544;	//0xC4D02868
	UINT32                                                 reserved2545;	//0xC4D0286C
	UINT32                                                 reserved2546;	//0xC4D02870
	UINT32                                                 reserved2547;	//0xC4D02874
	UINT32                                                 reserved2548;	//0xC4D02878
	UINT32                                                 reserved2549;	//0xC4D0287C
	UINT32                                                 reserved2550;	//0xC4D02880
	UINT32                                                 reserved2551;	//0xC4D02884
	UINT32                                                 reserved2552;	//0xC4D02888
	UINT32                                                 reserved2553;	//0xC4D0288C
	UINT32                                                 reserved2554;	//0xC4D02890
	UINT32                                                 reserved2555;	//0xC4D02894
	UINT32                                                 reserved2556;	//0xC4D02898
	UINT32                                                 reserved2557;	//0xC4D0289C
	UINT32                                                 reserved2558;	//0xC4D028A0
	UINT32                                                 reserved2559;	//0xC4D028A4
	UINT32                                                 reserved2560;	//0xC4D028A8
	UINT32                                                 reserved2561;	//0xC4D028AC
	UINT32                                                 reserved2562;	//0xC4D028B0
	UINT32                                                 reserved2563;	//0xC4D028B4
	UINT32                                                 reserved2564;	//0xC4D028B8
	UINT32                                                 reserved2565;	//0xC4D028BC
	UINT32                                                 reserved2566;	//0xC4D028C0
	UINT32                                                 reserved2567;	//0xC4D028C4
	UINT32                                                 reserved2568;	//0xC4D028C8
	UINT32                                                 reserved2569;	//0xC4D028CC
	UINT32                                                 reserved2570;	//0xC4D028D0
	UINT32                                                 reserved2571;	//0xC4D028D4
	UINT32                                                 reserved2572;	//0xC4D028D8
	UINT32                                                 reserved2573;	//0xC4D028DC
	UINT32                                                 reserved2574;	//0xC4D028E0
	UINT32                                                 reserved2575;	//0xC4D028E4
	UINT32                                                 reserved2576;	//0xC4D028E8
	UINT32                                                 reserved2577;	//0xC4D028EC
	UINT32                                                 reserved2578;	//0xC4D028F0
	UINT32                                                 reserved2579;	//0xC4D028F4
	UINT32                                                 reserved2580;	//0xC4D028F8
	UINT32                                                 reserved2581;	//0xC4D028FC
	UINT32                                                 reserved2582;	//0xC4D02900
	UINT32                                                 reserved2583;	//0xC4D02904
	UINT32                                                 reserved2584;	//0xC4D02908
	UINT32                                                 reserved2585;	//0xC4D0290C
	UINT32                                                 reserved2586;	//0xC4D02910
	UINT32                                                 reserved2587;	//0xC4D02914
	UINT32                                                 reserved2588;	//0xC4D02918
	UINT32                                                 reserved2589;	//0xC4D0291C
	UINT32                                                 reserved2590;	//0xC4D02920
	UINT32                                                 reserved2591;	//0xC4D02924
	UINT32                                                 reserved2592;	//0xC4D02928
	UINT32                                                 reserved2593;	//0xC4D0292C
	UINT32                                                 reserved2594;	//0xC4D02930
	UINT32                                                 reserved2595;	//0xC4D02934
	UINT32                                                 reserved2596;	//0xC4D02938
	UINT32                                                 reserved2597;	//0xC4D0293C
	UINT32                                                 reserved2598;	//0xC4D02940
	UINT32                                                 reserved2599;	//0xC4D02944
	UINT32                                                 reserved2600;	//0xC4D02948
	UINT32                                                 reserved2601;	//0xC4D0294C
	UINT32                                                 reserved2602;	//0xC4D02950
	UINT32                                                 reserved2603;	//0xC4D02954
	UINT32                                                 reserved2604;	//0xC4D02958
	UINT32                                                 reserved2605;	//0xC4D0295C
	UINT32                                                 reserved2606;	//0xC4D02960
	UINT32                                                 reserved2607;	//0xC4D02964
	UINT32                                                 reserved2608;	//0xC4D02968
	UINT32                                                 reserved2609;	//0xC4D0296C
	UINT32                                                 reserved2610;	//0xC4D02970
	UINT32                                                 reserved2611;	//0xC4D02974
	UINT32                                                 reserved2612;	//0xC4D02978
	UINT32                                                 reserved2613;	//0xC4D0297C
	UINT32                                                 reserved2614;	//0xC4D02980
	UINT32                                                 reserved2615;	//0xC4D02984
	UINT32                                                 reserved2616;	//0xC4D02988
	UINT32                                                 reserved2617;	//0xC4D0298C
	UINT32                                                 reserved2618;	//0xC4D02990
	UINT32                                                 reserved2619;	//0xC4D02994
	UINT32                                                 reserved2620;	//0xC4D02998
	UINT32                                                 reserved2621;	//0xC4D0299C
	UINT32                                                 reserved2622;	//0xC4D029A0
	UINT32                                                 reserved2623;	//0xC4D029A4
	UINT32                                                 reserved2624;	//0xC4D029A8
	UINT32                                                 reserved2625;	//0xC4D029AC
	UINT32                                                 reserved2626;	//0xC4D029B0
	UINT32                                                 reserved2627;	//0xC4D029B4
	UINT32                                                 reserved2628;	//0xC4D029B8
	UINT32                                                 reserved2629;	//0xC4D029BC
	UINT32                                                 reserved2630;	//0xC4D029C0
	UINT32                                                 reserved2631;	//0xC4D029C4
	UINT32                                                 reserved2632;	//0xC4D029C8
	UINT32                                                 reserved2633;	//0xC4D029CC
	UINT32                                                 reserved2634;	//0xC4D029D0
	UINT32                                                 reserved2635;	//0xC4D029D4
	UINT32                                                 reserved2636;	//0xC4D029D8
	UINT32                                                 reserved2637;	//0xC4D029DC
	UINT32                                                 reserved2638;	//0xC4D029E0
	UINT32                                                 reserved2639;	//0xC4D029E4
	UINT32                                                 reserved2640;	//0xC4D029E8
	UINT32                                                 reserved2641;	//0xC4D029EC
	UINT32                                                 reserved2642;	//0xC4D029F0
	UINT32                                                 reserved2643;	//0xC4D029F4
	UINT32                                                 reserved2644;	//0xC4D029F8
	UINT32                                                 reserved2645;	//0xC4D029FC
	UINT32                                                 reserved2646;	//0xC4D02A00
	UINT32                                                 reserved2647;	//0xC4D02A04
	UINT32                                                 reserved2648;	//0xC4D02A08
	UINT32                                                 reserved2649;	//0xC4D02A0C
	UINT32                                                 reserved2650;	//0xC4D02A10
	UINT32                                                 reserved2651;	//0xC4D02A14
	UINT32                                                 reserved2652;	//0xC4D02A18
	UINT32                                                 reserved2653;	//0xC4D02A1C
	UINT32                                                 reserved2654;	//0xC4D02A20
	UINT32                                                 reserved2655;	//0xC4D02A24
	UINT32                                                 reserved2656;	//0xC4D02A28
	UINT32                                                 reserved2657;	//0xC4D02A2C
	UINT32                                                 reserved2658;	//0xC4D02A30
	UINT32                                                 reserved2659;	//0xC4D02A34
	UINT32                                                 reserved2660;	//0xC4D02A38
	UINT32                                                 reserved2661;	//0xC4D02A3C
	UINT32                                                 reserved2662;	//0xC4D02A40
	UINT32                                                 reserved2663;	//0xC4D02A44
	UINT32                                                 reserved2664;	//0xC4D02A48
	UINT32                                                 reserved2665;	//0xC4D02A4C
	UINT32                                                 reserved2666;	//0xC4D02A50
	UINT32                                                 reserved2667;	//0xC4D02A54
	UINT32                                                 reserved2668;	//0xC4D02A58
	UINT32                                                 reserved2669;	//0xC4D02A5C
	UINT32                                                 reserved2670;	//0xC4D02A60
	UINT32                                                 reserved2671;	//0xC4D02A64
	UINT32                                                 reserved2672;	//0xC4D02A68
	UINT32                                                 reserved2673;	//0xC4D02A6C
	UINT32                                                 reserved2674;	//0xC4D02A70
	UINT32                                                 reserved2675;	//0xC4D02A74
	UINT32                                                 reserved2676;	//0xC4D02A78
	UINT32                                                 reserved2677;	//0xC4D02A7C
	UINT32                                                 reserved2678;	//0xC4D02A80
	UINT32                                                 reserved2679;	//0xC4D02A84
	UINT32                                                 reserved2680;	//0xC4D02A88
	UINT32                                                 reserved2681;	//0xC4D02A8C
	UINT32                                                 reserved2682;	//0xC4D02A90
	UINT32                                                 reserved2683;	//0xC4D02A94
	UINT32                                                 reserved2684;	//0xC4D02A98
	UINT32                                                 reserved2685;	//0xC4D02A9C
	UINT32                                                 reserved2686;	//0xC4D02AA0
	UINT32                                                 reserved2687;	//0xC4D02AA4
	UINT32                                                 reserved2688;	//0xC4D02AA8
	UINT32                                                 reserved2689;	//0xC4D02AAC
	UINT32                                                 reserved2690;	//0xC4D02AB0
	UINT32                                                 reserved2691;	//0xC4D02AB4
	UINT32                                                 reserved2692;	//0xC4D02AB8
	UINT32                                                 reserved2693;	//0xC4D02ABC
	UINT32                                                 reserved2694;	//0xC4D02AC0
	UINT32                                                 reserved2695;	//0xC4D02AC4
	UINT32                                                 reserved2696;	//0xC4D02AC8
	UINT32                                                 reserved2697;	//0xC4D02ACC
	UINT32                                                 reserved2698;	//0xC4D02AD0
	UINT32                                                 reserved2699;	//0xC4D02AD4
	UINT32                                                 reserved2700;	//0xC4D02AD8
	UINT32                                                 reserved2701;	//0xC4D02ADC
	UINT32                                                 reserved2702;	//0xC4D02AE0
	UINT32                                                 reserved2703;	//0xC4D02AE4
	UINT32                                                 reserved2704;	//0xC4D02AE8
	UINT32                                                 reserved2705;	//0xC4D02AEC
	UINT32                                                 reserved2706;	//0xC4D02AF0
	UINT32                                                 reserved2707;	//0xC4D02AF4
	UINT32                                                 reserved2708;	//0xC4D02AF8
	UINT32                                                 reserved2709;	//0xC4D02AFC
	UINT32                                                 reserved2710;	//0xC4D02B00
	UINT32                                                 reserved2711;	//0xC4D02B04
	UINT32                                                 reserved2712;	//0xC4D02B08
	UINT32                                                 reserved2713;	//0xC4D02B0C
	UINT32                                                 reserved2714;	//0xC4D02B10
	UINT32                                                 reserved2715;	//0xC4D02B14
	UINT32                                                 reserved2716;	//0xC4D02B18
	UINT32                                                 reserved2717;	//0xC4D02B1C
	UINT32                                                 reserved2718;	//0xC4D02B20
	UINT32                                                 reserved2719;	//0xC4D02B24
	UINT32                                                 reserved2720;	//0xC4D02B28
	UINT32                                                 reserved2721;	//0xC4D02B2C
	UINT32                                                 reserved2722;	//0xC4D02B30
	UINT32                                                 reserved2723;	//0xC4D02B34
	UINT32                                                 reserved2724;	//0xC4D02B38
	UINT32                                                 reserved2725;	//0xC4D02B3C
	UINT32                                                 reserved2726;	//0xC4D02B40
	UINT32                                                 reserved2727;	//0xC4D02B44
	UINT32                                                 reserved2728;	//0xC4D02B48
	UINT32                                                 reserved2729;	//0xC4D02B4C
	UINT32                                                 reserved2730;	//0xC4D02B50
	UINT32                                                 reserved2731;	//0xC4D02B54
	UINT32                                                 reserved2732;	//0xC4D02B58
	UINT32                                                 reserved2733;	//0xC4D02B5C
	UINT32                                                 reserved2734;	//0xC4D02B60
	UINT32                                                 reserved2735;	//0xC4D02B64
	UINT32                                                 reserved2736;	//0xC4D02B68
	UINT32                                                 reserved2737;	//0xC4D02B6C
	UINT32                                                 reserved2738;	//0xC4D02B70
	UINT32                                                 reserved2739;	//0xC4D02B74
	UINT32                                                 reserved2740;	//0xC4D02B78
	UINT32                                                 reserved2741;	//0xC4D02B7C
	UINT32                                                 reserved2742;	//0xC4D02B80
	UINT32                                                 reserved2743;	//0xC4D02B84
	UINT32                                                 reserved2744;	//0xC4D02B88
	UINT32                                                 reserved2745;	//0xC4D02B8C
	UINT32                                                 reserved2746;	//0xC4D02B90
	UINT32                                                 reserved2747;	//0xC4D02B94
	UINT32                                                 reserved2748;	//0xC4D02B98
	UINT32                                                 reserved2749;	//0xC4D02B9C
	UINT32                                                 reserved2750;	//0xC4D02BA0
	UINT32                                                 reserved2751;	//0xC4D02BA4
	UINT32                                                 reserved2752;	//0xC4D02BA8
	UINT32                                                 reserved2753;	//0xC4D02BAC
	UINT32                                                 reserved2754;	//0xC4D02BB0
	UINT32                                                 reserved2755;	//0xC4D02BB4
	UINT32                                                 reserved2756;	//0xC4D02BB8
	UINT32                                                 reserved2757;	//0xC4D02BBC
	UINT32                                                 reserved2758;	//0xC4D02BC0
	UINT32                                                 reserved2759;	//0xC4D02BC4
	UINT32                                                 reserved2760;	//0xC4D02BC8
	UINT32                                                 reserved2761;	//0xC4D02BCC
	UINT32                                                 reserved2762;	//0xC4D02BD0
	UINT32                                                 reserved2763;	//0xC4D02BD4
	UINT32                                                 reserved2764;	//0xC4D02BD8
	UINT32                                                 reserved2765;	//0xC4D02BDC
	UINT32                                                 reserved2766;	//0xC4D02BE0
	UINT32                                                 reserved2767;	//0xC4D02BE4
	UINT32                                                 reserved2768;	//0xC4D02BE8
	UINT32                                                 reserved2769;	//0xC4D02BEC
	UINT32                                                 reserved2770;	//0xC4D02BF0
	UINT32                                                 reserved2771;	//0xC4D02BF4
	UINT32                                                 reserved2772;	//0xC4D02BF8
	UINT32                                                 reserved2773;	//0xC4D02BFC
	UINT32                                                 reserved2774;	//0xC4D02C00
	UINT32                                                 reserved2775;	//0xC4D02C04
	UINT32                                                 reserved2776;	//0xC4D02C08
	UINT32                                                 reserved2777;	//0xC4D02C0C
	UINT32                                                 reserved2778;	//0xC4D02C10
	UINT32                                                 reserved2779;	//0xC4D02C14
	UINT32                                                 reserved2780;	//0xC4D02C18
	UINT32                                                 reserved2781;	//0xC4D02C1C
	UINT32                                                 reserved2782;	//0xC4D02C20
	UINT32                                                 reserved2783;	//0xC4D02C24
	UINT32                                                 reserved2784;	//0xC4D02C28
	UINT32                                                 reserved2785;	//0xC4D02C2C
	UINT32                                                 reserved2786;	//0xC4D02C30
	UINT32                                                 reserved2787;	//0xC4D02C34
	UINT32                                                 reserved2788;	//0xC4D02C38
	UINT32                                                 reserved2789;	//0xC4D02C3C
	UINT32                                                 reserved2790;	//0xC4D02C40
	UINT32                                                 reserved2791;	//0xC4D02C44
	UINT32                                                 reserved2792;	//0xC4D02C48
	UINT32                                                 reserved2793;	//0xC4D02C4C
	UINT32                                                 reserved2794;	//0xC4D02C50
	UINT32                                                 reserved2795;	//0xC4D02C54
	UINT32                                                 reserved2796;	//0xC4D02C58
	UINT32                                                 reserved2797;	//0xC4D02C5C
	UINT32                                                 reserved2798;	//0xC4D02C60
	UINT32                                                 reserved2799;	//0xC4D02C64
	UINT32                                                 reserved2800;	//0xC4D02C68
	UINT32                                                 reserved2801;	//0xC4D02C6C
	UINT32                                                 reserved2802;	//0xC4D02C70
	UINT32                                                 reserved2803;	//0xC4D02C74
	UINT32                                                 reserved2804;	//0xC4D02C78
	UINT32                                                 reserved2805;	//0xC4D02C7C
	UINT32                                                 reserved2806;	//0xC4D02C80
	UINT32                                                 reserved2807;	//0xC4D02C84
	UINT32                                                 reserved2808;	//0xC4D02C88
	UINT32                                                 reserved2809;	//0xC4D02C8C
	UINT32                                                 reserved2810;	//0xC4D02C90
	UINT32                                                 reserved2811;	//0xC4D02C94
	UINT32                                                 reserved2812;	//0xC4D02C98
	UINT32                                                 reserved2813;	//0xC4D02C9C
	UINT32                                                 reserved2814;	//0xC4D02CA0
	UINT32                                                 reserved2815;	//0xC4D02CA4
	UINT32                                                 reserved2816;	//0xC4D02CA8
	UINT32                                                 reserved2817;	//0xC4D02CAC
	UINT32                                                 reserved2818;	//0xC4D02CB0
	UINT32                                                 reserved2819;	//0xC4D02CB4
	UINT32                                                 reserved2820;	//0xC4D02CB8
	UINT32                                                 reserved2821;	//0xC4D02CBC
	UINT32                                                 reserved2822;	//0xC4D02CC0
	UINT32                                                 reserved2823;	//0xC4D02CC4
	UINT32                                                 reserved2824;	//0xC4D02CC8
	UINT32                                                 reserved2825;	//0xC4D02CCC
	UINT32                                                 reserved2826;	//0xC4D02CD0
	UINT32                                                 reserved2827;	//0xC4D02CD4
	UINT32                                                 reserved2828;	//0xC4D02CD8
	UINT32                                                 reserved2829;	//0xC4D02CDC
	UINT32                                                 reserved2830;	//0xC4D02CE0
	UINT32                                                 reserved2831;	//0xC4D02CE4
	UINT32                                                 reserved2832;	//0xC4D02CE8
	UINT32                                                 reserved2833;	//0xC4D02CEC
	UINT32                                                 reserved2834;	//0xC4D02CF0
	UINT32                                                 reserved2835;	//0xC4D02CF4
	UINT32                                                 reserved2836;	//0xC4D02CF8
	UINT32                                                 reserved2837;	//0xC4D02CFC
	UINT32                                                 reserved2838;	//0xC4D02D00
	UINT32                                                 reserved2839;	//0xC4D02D04
	UINT32                                                 reserved2840;	//0xC4D02D08
	UINT32                                                 reserved2841;	//0xC4D02D0C
	UINT32                                                 reserved2842;	//0xC4D02D10
	UINT32                                                 reserved2843;	//0xC4D02D14
	UINT32                                                 reserved2844;	//0xC4D02D18
	UINT32                                                 reserved2845;	//0xC4D02D1C
	UINT32                                                 reserved2846;	//0xC4D02D20
	UINT32                                                 reserved2847;	//0xC4D02D24
	UINT32                                                 reserved2848;	//0xC4D02D28
	UINT32                                                 reserved2849;	//0xC4D02D2C
	UINT32                                                 reserved2850;	//0xC4D02D30
	UINT32                                                 reserved2851;	//0xC4D02D34
	UINT32                                                 reserved2852;	//0xC4D02D38
	UINT32                                                 reserved2853;	//0xC4D02D3C
	UINT32                                                 reserved2854;	//0xC4D02D40
	UINT32                                                 reserved2855;	//0xC4D02D44
	UINT32                                                 reserved2856;	//0xC4D02D48
	UINT32                                                 reserved2857;	//0xC4D02D4C
	UINT32                                                 reserved2858;	//0xC4D02D50
	UINT32                                                 reserved2859;	//0xC4D02D54
	UINT32                                                 reserved2860;	//0xC4D02D58
	UINT32                                                 reserved2861;	//0xC4D02D5C
	UINT32                                                 reserved2862;	//0xC4D02D60
	UINT32                                                 reserved2863;	//0xC4D02D64
	UINT32                                                 reserved2864;	//0xC4D02D68
	UINT32                                                 reserved2865;	//0xC4D02D6C
	UINT32                                                 reserved2866;	//0xC4D02D70
	UINT32                                                 reserved2867;	//0xC4D02D74
	UINT32                                                 reserved2868;	//0xC4D02D78
	UINT32                                                 reserved2869;	//0xC4D02D7C
	UINT32                                                 reserved2870;	//0xC4D02D80
	UINT32                                                 reserved2871;	//0xC4D02D84
	UINT32                                                 reserved2872;	//0xC4D02D88
	UINT32                                                 reserved2873;	//0xC4D02D8C
	UINT32                                                 reserved2874;	//0xC4D02D90
	UINT32                                                 reserved2875;	//0xC4D02D94
	UINT32                                                 reserved2876;	//0xC4D02D98
	UINT32                                                 reserved2877;	//0xC4D02D9C
	UINT32                                                 reserved2878;	//0xC4D02DA0
	UINT32                                                 reserved2879;	//0xC4D02DA4
	UINT32                                                 reserved2880;	//0xC4D02DA8
	UINT32                                                 reserved2881;	//0xC4D02DAC
	UINT32                                                 reserved2882;	//0xC4D02DB0
	UINT32                                                 reserved2883;	//0xC4D02DB4
	UINT32                                                 reserved2884;	//0xC4D02DB8
	UINT32                                                 reserved2885;	//0xC4D02DBC
	UINT32                                                 reserved2886;	//0xC4D02DC0
	UINT32                                                 reserved2887;	//0xC4D02DC4
	UINT32                                                 reserved2888;	//0xC4D02DC8
	UINT32                                                 reserved2889;	//0xC4D02DCC
	UINT32                                                 reserved2890;	//0xC4D02DD0
	UINT32                                                 reserved2891;	//0xC4D02DD4
	UINT32                                                 reserved2892;	//0xC4D02DD8
	UINT32                                                 reserved2893;	//0xC4D02DDC
	UINT32                                                 reserved2894;	//0xC4D02DE0
	UINT32                                                 reserved2895;	//0xC4D02DE4
	UINT32                                                 reserved2896;	//0xC4D02DE8
	UINT32                                                 reserved2897;	//0xC4D02DEC
	UINT32                                                 reserved2898;	//0xC4D02DF0
	UINT32                                                 reserved2899;	//0xC4D02DF4
	UINT32                                                 reserved2900;	//0xC4D02DF8
	UINT32                                                 reserved2901;	//0xC4D02DFC
	UINT32                                                 reserved2902;	//0xC4D02E00
	UINT32                                                 reserved2903;	//0xC4D02E04
	UINT32                                                 reserved2904;	//0xC4D02E08
	UINT32                                                 reserved2905;	//0xC4D02E0C
	UINT32                                                 reserved2906;	//0xC4D02E10
	UINT32                                                 reserved2907;	//0xC4D02E14
	UINT32                                                 reserved2908;	//0xC4D02E18
	UINT32                                                 reserved2909;	//0xC4D02E1C
	UINT32                                                 reserved2910;	//0xC4D02E20
	UINT32                                                 reserved2911;	//0xC4D02E24
	UINT32                                                 reserved2912;	//0xC4D02E28
	UINT32                                                 reserved2913;	//0xC4D02E2C
	UINT32                                                 reserved2914;	//0xC4D02E30
	UINT32                                                 reserved2915;	//0xC4D02E34
	UINT32                                                 reserved2916;	//0xC4D02E38
	UINT32                                                 reserved2917;	//0xC4D02E3C
	UINT32                                                 reserved2918;	//0xC4D02E40
	UINT32                                                 reserved2919;	//0xC4D02E44
	UINT32                                                 reserved2920;	//0xC4D02E48
	UINT32                                                 reserved2921;	//0xC4D02E4C
	UINT32                                                 reserved2922;	//0xC4D02E50
	UINT32                                                 reserved2923;	//0xC4D02E54
	UINT32                                                 reserved2924;	//0xC4D02E58
	UINT32                                                 reserved2925;	//0xC4D02E5C
	UINT32                                                 reserved2926;	//0xC4D02E60
	UINT32                                                 reserved2927;	//0xC4D02E64
	UINT32                                                 reserved2928;	//0xC4D02E68
	UINT32                                                 reserved2929;	//0xC4D02E6C
	UINT32                                                 reserved2930;	//0xC4D02E70
	UINT32                                                 reserved2931;	//0xC4D02E74
	UINT32                                                 reserved2932;	//0xC4D02E78
	UINT32                                                 reserved2933;	//0xC4D02E7C
	UINT32                                                 reserved2934;	//0xC4D02E80
	UINT32                                                 reserved2935;	//0xC4D02E84
	UINT32                                                 reserved2936;	//0xC4D02E88
	UINT32                                                 reserved2937;	//0xC4D02E8C
	UINT32                                                 reserved2938;	//0xC4D02E90
	UINT32                                                 reserved2939;	//0xC4D02E94
	UINT32                                                 reserved2940;	//0xC4D02E98
	UINT32                                                 reserved2941;	//0xC4D02E9C
	UINT32                                                 reserved2942;	//0xC4D02EA0
	UINT32                                                 reserved2943;	//0xC4D02EA4
	UINT32                                                 reserved2944;	//0xC4D02EA8
	UINT32                                                 reserved2945;	//0xC4D02EAC
	UINT32                                                 reserved2946;	//0xC4D02EB0
	UINT32                                                 reserved2947;	//0xC4D02EB4
	UINT32                                                 reserved2948;	//0xC4D02EB8
	UINT32                                                 reserved2949;	//0xC4D02EBC
	UINT32                                                 reserved2950;	//0xC4D02EC0
	UINT32                                                 reserved2951;	//0xC4D02EC4
	UINT32                                                 reserved2952;	//0xC4D02EC8
	UINT32                                                 reserved2953;	//0xC4D02ECC
	UINT32                                                 reserved2954;	//0xC4D02ED0
	UINT32                                                 reserved2955;	//0xC4D02ED4
	UINT32                                                 reserved2956;	//0xC4D02ED8
	UINT32                                                 reserved2957;	//0xC4D02EDC
	UINT32                                                 reserved2958;	//0xC4D02EE0
	UINT32                                                 reserved2959;	//0xC4D02EE4
	UINT32                                                 reserved2960;	//0xC4D02EE8
	UINT32                                                 reserved2961;	//0xC4D02EEC
	UINT32                                                 reserved2962;	//0xC4D02EF0
	UINT32                                                 reserved2963;	//0xC4D02EF4
	UINT32                                                 reserved2964;	//0xC4D02EF8
	UINT32                                                 reserved2965;	//0xC4D02EFC
	UINT32                                                 reserved2966;	//0xC4D02F00
	UINT32                                                 reserved2967;	//0xC4D02F04
	UINT32                                                 reserved2968;	//0xC4D02F08
	UINT32                                                 reserved2969;	//0xC4D02F0C
	UINT32                                                 reserved2970;	//0xC4D02F10
	UINT32                                                 reserved2971;	//0xC4D02F14
	UINT32                                                 reserved2972;	//0xC4D02F18
	UINT32                                                 reserved2973;	//0xC4D02F1C
	UINT32                                                 reserved2974;	//0xC4D02F20
	UINT32                                                 reserved2975;	//0xC4D02F24
	UINT32                                                 reserved2976;	//0xC4D02F28
	UINT32                                                 reserved2977;	//0xC4D02F2C
	UINT32                                                 reserved2978;	//0xC4D02F30
	UINT32                                                 reserved2979;	//0xC4D02F34
	UINT32                                                 reserved2980;	//0xC4D02F38
	UINT32                                                 reserved2981;	//0xC4D02F3C
	UINT32                                                 reserved2982;	//0xC4D02F40
	UINT32                                                 reserved2983;	//0xC4D02F44
	UINT32                                                 reserved2984;	//0xC4D02F48
	UINT32                                                 reserved2985;	//0xC4D02F4C
	UINT32                                                 reserved2986;	//0xC4D02F50
	UINT32                                                 reserved2987;	//0xC4D02F54
	UINT32                                                 reserved2988;	//0xC4D02F58
	UINT32                                                 reserved2989;	//0xC4D02F5C
	UINT32                                                 reserved2990;	//0xC4D02F60
	UINT32                                                 reserved2991;	//0xC4D02F64
	UINT32                                                 reserved2992;	//0xC4D02F68
	UINT32                                                 reserved2993;	//0xC4D02F6C
	UINT32                                                 reserved2994;	//0xC4D02F70
	UINT32                                                 reserved2995;	//0xC4D02F74
	UINT32                                                 reserved2996;	//0xC4D02F78
	UINT32                                                 reserved2997;	//0xC4D02F7C
	UINT32                                                 reserved2998;	//0xC4D02F80
	UINT32                                                 reserved2999;	//0xC4D02F84
	UINT32                                                 reserved3000;	//0xC4D02F88
	UINT32                                                 reserved3001;	//0xC4D02F8C
	UINT32                                                 reserved3002;	//0xC4D02F90
	UINT32                                                 reserved3003;	//0xC4D02F94
	UINT32                                                 reserved3004;	//0xC4D02F98
	UINT32                                                 reserved3005;	//0xC4D02F9C
	UINT32                                                 reserved3006;	//0xC4D02FA0
	UINT32                                                 reserved3007;	//0xC4D02FA4
	UINT32                                                 reserved3008;	//0xC4D02FA8
	UINT32                                                 reserved3009;	//0xC4D02FAC
	UINT32                                                 reserved3010;	//0xC4D02FB0
	UINT32                                                 reserved3011;	//0xC4D02FB4
	UINT32                                                 reserved3012;	//0xC4D02FB8
	UINT32                                                 reserved3013;	//0xC4D02FBC
	UINT32                                                 reserved3014;	//0xC4D02FC0
	UINT32                                                 reserved3015;	//0xC4D02FC4
	UINT32                                                 reserved3016;	//0xC4D02FC8
	UINT32                                                 reserved3017;	//0xC4D02FCC
	UINT32                                                 reserved3018;	//0xC4D02FD0
	UINT32                                                 reserved3019;	//0xC4D02FD4
	UINT32                                                 reserved3020;	//0xC4D02FD8
	UINT32                                                 reserved3021;	//0xC4D02FDC
	UINT32                                                 reserved3022;	//0xC4D02FE0
	UINT32                                                 reserved3023;	//0xC4D02FE4
	UINT32                                                 reserved3024;	//0xC4D02FE8
	UINT32                                                 reserved3025;	//0xC4D02FEC
	UINT32                                                 reserved3026;	//0xC4D02FF0
	UINT32                                                 reserved3027;	//0xC4D02FF4
	UINT32                                                 reserved3028;	//0xC4D02FF8
	UINT32                                                 reserved3029;	//0xC4D02FFC
	REG_DDRC_M0_LPD4_MAIN_FSM_INIT_0_T             lpd4_main_fsm_init_0;	//0xC4D03000
	REG_DDRC_M0_LPD4_MAIN_FSM_INIT_1_T             lpd4_main_fsm_init_1;	//0xC4D03004
	REG_DDRC_M0_LPD4_MAIN_FSM_INIT_2_T             lpd4_main_fsm_init_2;	//0xC4D03008
	REG_DDRC_M0_LPD4_MAIN_FSM_CTRL_T                 lpd4_main_fsm_ctrl;	//0xC4D0300C
	REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_0_T     lpd4_main_fsm_dir_ctrl_0;	//0xC4D03010
	REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_1_T     lpd4_main_fsm_dir_ctrl_1;	//0xC4D03014
	REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_2_T     lpd4_main_fsm_dir_ctrl_2;	//0xC4D03018
	REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_3_T     lpd4_main_fsm_dir_ctrl_3;	//0xC4D0301C
	REG_DDRC_M0_LPD4_MAIN_FSM_DIR_CTRL_4_T     lpd4_main_fsm_dir_ctrl_4;	//0xC4D03020
	REG_DDRC_M0_LPD4_MAIN_FSM_DFS_MRW_T           lpd4_main_fsm_dfs_mrw;	//0xC4D03024
	REG_DDRC_M0_LPD4_MAIN_FSM_CTRLUPD_T           lpd4_main_fsm_ctrlupd;	//0xC4D03028
	REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_0_T     lpd4_main_fsm_mpc_fifo_0;	//0xC4D0302C
	REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_1_T     lpd4_main_fsm_mpc_fifo_1;	//0xC4D03030
	REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_2_T     lpd4_main_fsm_mpc_fifo_2;	//0xC4D03034
	REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_3_T     lpd4_main_fsm_mpc_fifo_3;	//0xC4D03038
	REG_DDRC_M0_LPD4_MAIN_FSM_MPC_FIFO_4_T     lpd4_main_fsm_mpc_fifo_4;	//0xC4D0303C
	UINT32                                                 reserved3030;	//0xC4D03040
	UINT32                                                 reserved3031;	//0xC4D03044
	UINT32                                                 reserved3032;	//0xC4D03048
	UINT32                                                 reserved3033;	//0xC4D0304C
	REG_DDRC_M0_LPD4_MR_CTRL_0_T                         lpd4_mr_ctrl_0;	//0xC4D03050
	REG_DDRC_M0_LPD4_MR_CTRL_1_T                         lpd4_mr_ctrl_1;	//0xC4D03054
	REG_DDRC_M0_LPD4_MR_CTRL_2_T                         lpd4_mr_ctrl_2;	//0xC4D03058
	UINT32                                                 reserved3034;	//0xC4D0305C
	REG_DDRC_M0_LPD4_REF_REQ_CTRL_T                   lpd4_ref_req_ctrl;	//0xC4D03060
	UINT32                                                 reserved3035;	//0xC4D03064
	UINT32                                                 reserved3036;	//0xC4D03068
	UINT32                                                 reserved3037;	//0xC4D0306C
	REG_DDRC_M0_LPD4_REF_CTRL_T                           lpd4_ref_ctrl;	//0xC4D03070
	UINT32                                                 reserved3038;	//0xC4D03074
	UINT32                                                 reserved3039;	//0xC4D03078
	UINT32                                                 reserved3040;	//0xC4D0307C
	REG_DDRC_M0_LPD4_BANK_FSM_T                           lpd4_bank_fsm;	//0xC4D03080
	UINT32                                                 reserved3041;	//0xC4D03084
	UINT32                                                 reserved3042;	//0xC4D03088
	UINT32                                                 reserved3043;	//0xC4D0308C
	UINT32                                                 reserved3044;	//0xC4D03090
	UINT32                                                 reserved3045;	//0xC4D03094
	UINT32                                                 reserved3046;	//0xC4D03098
	UINT32                                                 reserved3047;	//0xC4D0309C
	REG_DDRC_M0_LPD4_BANK_STATUS_T                     lpd4_bank_status;	//0xC4D030A0
	UINT32                                                 reserved3048;	//0xC4D030A4
	UINT32                                                 reserved3049;	//0xC4D030A8
	UINT32                                                 reserved3050;	//0xC4D030AC
	UINT32                                                 reserved3051;	//0xC4D030B0
	UINT32                                                 reserved3052;	//0xC4D030B4
	UINT32                                                 reserved3053;	//0xC4D030B8
	UINT32                                                 reserved3054;	//0xC4D030BC
	REG_DDRC_M0_LPD4_PHY_IF_T                               lpd4_phy_if;	//0xC4D030C0
	UINT32                                                 reserved3055;	//0xC4D030C4
	UINT32                                                 reserved3056;	//0xC4D030C8
	UINT32                                                 reserved3057;	//0xC4D030CC
	UINT32                                                 reserved3058;	//0xC4D030D0
	UINT32                                                 reserved3059;	//0xC4D030D4
	UINT32                                                 reserved3060;	//0xC4D030D8
	UINT32                                                 reserved3061;	//0xC4D030DC
	UINT32                                                 reserved3062;	//0xC4D030E0
	UINT32                                                 reserved3063;	//0xC4D030E4
	UINT32                                                 reserved3064;	//0xC4D030E8
	UINT32                                                 reserved3065;	//0xC4D030EC
	UINT32                                                 reserved3066;	//0xC4D030F0
	UINT32                                                 reserved3067;	//0xC4D030F4
	UINT32                                                 reserved3068;	//0xC4D030F8
	UINT32                                                 reserved3069;	//0xC4D030FC
	REG_DDRC_M0_LPD4_DFS0_MR_0_CH0_T                 lpd4_dfs0_mr_0_ch0;	//0xC4D03100
	REG_DDRC_M0_LPD4_DFS0_MR_1_CH0_T                 lpd4_dfs0_mr_1_ch0;	//0xC4D03104
	REG_DDRC_M0_LPD4_DFS0_MR_2_CH0_T                 lpd4_dfs0_mr_2_ch0;	//0xC4D03108
	REG_DDRC_M0_LPD4_DFS0_MR_3_CH0_T                 lpd4_dfs0_mr_3_ch0;	//0xC4D0310C
	REG_DDRC_M0_LPD4_DFS0_MR_4_CH0_T                 lpd4_dfs0_mr_4_ch0;	//0xC4D03110
	REG_DDRC_M0_LPD4_DFS0_MR_5_CH0_T                 lpd4_dfs0_mr_5_ch0;	//0xC4D03114
	REG_DDRC_M0_LPD4_DFS0_MR_6_CH0_T                 lpd4_dfs0_mr_6_ch0;	//0xC4D03118
	UINT32                                                 reserved3070;	//0xC4D0311C
	REG_DDRC_M0_LPD4_DFS0_MR_0_CH1_T                 lpd4_dfs0_mr_0_ch1;	//0xC4D03120
	REG_DDRC_M0_LPD4_DFS0_MR_1_CH1_T                 lpd4_dfs0_mr_1_ch1;	//0xC4D03124
	REG_DDRC_M0_LPD4_DFS0_MR_2_CH1_T                 lpd4_dfs0_mr_2_ch1;	//0xC4D03128
	REG_DDRC_M0_LPD4_DFS0_MR_3_CH1_T                 lpd4_dfs0_mr_3_ch1;	//0xC4D0312C
	REG_DDRC_M0_LPD4_DFS0_MR_4_CH1_T                 lpd4_dfs0_mr_4_ch1;	//0xC4D03130
	REG_DDRC_M0_LPD4_DFS0_MR_5_CH1_T                 lpd4_dfs0_mr_5_ch1;	//0xC4D03134
	REG_DDRC_M0_LPD4_DFS0_MR_6_CH1_T                 lpd4_dfs0_mr_6_ch1;	//0xC4D03138
	UINT32                                                 reserved3071;	//0xC4D0313C
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_0_T             lpd4_dfs0_main_fsm_0;	//0xC4D03140
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_1_T             lpd4_dfs0_main_fsm_1;	//0xC4D03144
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_2_T             lpd4_dfs0_main_fsm_2;	//0xC4D03148
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_3_T             lpd4_dfs0_main_fsm_3;	//0xC4D0314C
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_4_T             lpd4_dfs0_main_fsm_4;	//0xC4D03150
	REG_DDRC_M0_LPD4_DFS0_MAIN_FSM_5_T             lpd4_dfs0_main_fsm_5;	//0xC4D03154
	UINT32                                                 reserved3072;	//0xC4D03158
	UINT32                                                 reserved3073;	//0xC4D0315C
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_0_T     lpd4_dfs0_ref_req_ctrl_0;	//0xC4D03160
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_1_T     lpd4_dfs0_ref_req_ctrl_1;	//0xC4D03164
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_2_T     lpd4_dfs0_ref_req_ctrl_2;	//0xC4D03168
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_3_T     lpd4_dfs0_ref_req_ctrl_3;	//0xC4D0316C
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_4_T     lpd4_dfs0_ref_req_ctrl_4;	//0xC4D03170
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_5_T     lpd4_dfs0_ref_req_ctrl_5;	//0xC4D03174
	REG_DDRC_M0_LPD4_DFS0_REF_REQ_CTRL_6_T     lpd4_dfs0_ref_req_ctrl_6;	//0xC4D03178
	UINT32                                                 reserved3074;	//0xC4D0317C
	UINT32                                                 reserved3075;	//0xC4D03180
	UINT32                                                 reserved3076;	//0xC4D03184
	UINT32                                                 reserved3077;	//0xC4D03188
	UINT32                                                 reserved3078;	//0xC4D0318C
	REG_DDRC_M0_LPD4_DFS0_REF_CTRL_T                 lpd4_dfs0_ref_ctrl;	//0xC4D03190
	UINT32                                                 reserved3079;	//0xC4D03194
	UINT32                                                 reserved3080;	//0xC4D03198
	UINT32                                                 reserved3081;	//0xC4D0319C
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_0_T       lpd4_dfs0_bank_status_0;	//0xC4D031A0
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_1_T       lpd4_dfs0_bank_status_1;	//0xC4D031A4
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_2_T       lpd4_dfs0_bank_status_2;	//0xC4D031A8
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_3_T       lpd4_dfs0_bank_status_3;	//0xC4D031AC
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_4_T       lpd4_dfs0_bank_status_4;	//0xC4D031B0
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_5_T       lpd4_dfs0_bank_status_5;	//0xC4D031B4
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_6_T       lpd4_dfs0_bank_status_6;	//0xC4D031B8
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_7_T       lpd4_dfs0_bank_status_7;	//0xC4D031BC
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_8_T       lpd4_dfs0_bank_status_8;	//0xC4D031C0
	REG_DDRC_M0_LPD4_DFS0_BANK_STATUS_9_T       lpd4_dfs0_bank_status_9;	//0xC4D031C4
	UINT32                                                 reserved3082;	//0xC4D031C8
	UINT32                                                 reserved3083;	//0xC4D031CC
	UINT32                                                 reserved3084;	//0xC4D031D0
	UINT32                                                 reserved3085;	//0xC4D031D4
	UINT32                                                 reserved3086;	//0xC4D031D8
	UINT32                                                 reserved3087;	//0xC4D031DC
	REG_DDRC_M0_LPD4_DFS0_PHY_IF_T                     lpd4_dfs0_phy_if;	//0xC4D031E0
	UINT32                                                 reserved3088;	//0xC4D031E4
	UINT32                                                 reserved3089;	//0xC4D031E8
	UINT32                                                 reserved3090;	//0xC4D031EC
	UINT32                                                 reserved3091;	//0xC4D031F0
	UINT32                                                 reserved3092;	//0xC4D031F4
	UINT32                                                 reserved3093;	//0xC4D031F8
	UINT32                                                 reserved3094;	//0xC4D031FC
	REG_DDRC_M0_LPD4_DFS1_MR_0_CH0_T                 lpd4_dfs1_mr_0_ch0;	//0xC4D03200
	REG_DDRC_M0_LPD4_DFS1_MR_1_CH0_T                 lpd4_dfs1_mr_1_ch0;	//0xC4D03204
	REG_DDRC_M0_LPD4_DFS1_MR_2_CH0_T                 lpd4_dfs1_mr_2_ch0;	//0xC4D03208
	REG_DDRC_M0_LPD4_DFS1_MR_3_CH0_T                 lpd4_dfs1_mr_3_ch0;	//0xC4D0320C
	REG_DDRC_M0_LPD4_DFS1_MR_4_CH0_T                 lpd4_dfs1_mr_4_ch0;	//0xC4D03210
	REG_DDRC_M0_LPD4_DFS1_MR_5_CH0_T                 lpd4_dfs1_mr_5_ch0;	//0xC4D03214
	REG_DDRC_M0_LPD4_DFS1_MR_6_CH0_T                 lpd4_dfs1_mr_6_ch0;	//0xC4D03218
	UINT32                                                 reserved3095;	//0xC4D0321C
	REG_DDRC_M0_LPD4_DFS1_MR_0_CH1_T                 lpd4_dfs1_mr_0_ch1;	//0xC4D03220
	REG_DDRC_M0_LPD4_DFS1_MR_1_CH1_T                 lpd4_dfs1_mr_1_ch1;	//0xC4D03224
	REG_DDRC_M0_LPD4_DFS1_MR_2_CH1_T                 lpd4_dfs1_mr_2_ch1;	//0xC4D03228
	REG_DDRC_M0_LPD4_DFS1_MR_3_CH1_T                 lpd4_dfs1_mr_3_ch1;	//0xC4D0322C
	REG_DDRC_M0_LPD4_DFS1_MR_4_CH1_T                 lpd4_dfs1_mr_4_ch1;	//0xC4D03230
	REG_DDRC_M0_LPD4_DFS1_MR_5_CH1_T                 lpd4_dfs1_mr_5_ch1;	//0xC4D03234
	REG_DDRC_M0_LPD4_DFS1_MR_6_CH1_T                 lpd4_dfs1_mr_6_ch1;	//0xC4D03238
	UINT32                                                 reserved3096;	//0xC4D0323C
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_0_T             lpd4_dfs1_main_fsm_0;	//0xC4D03240
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_1_T             lpd4_dfs1_main_fsm_1;	//0xC4D03244
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_2_T             lpd4_dfs1_main_fsm_2;	//0xC4D03248
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_3_T             lpd4_dfs1_main_fsm_3;	//0xC4D0324C
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_4_T             lpd4_dfs1_main_fsm_4;	//0xC4D03250
	REG_DDRC_M0_LPD4_DFS1_MAIN_FSM_5_T             lpd4_dfs1_main_fsm_5;	//0xC4D03254
	UINT32                                                 reserved3097;	//0xC4D03258
	UINT32                                                 reserved3098;	//0xC4D0325C
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_0_T     lpd4_dfs1_ref_req_ctrl_0;	//0xC4D03260
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_1_T     lpd4_dfs1_ref_req_ctrl_1;	//0xC4D03264
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_2_T     lpd4_dfs1_ref_req_ctrl_2;	//0xC4D03268
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_3_T     lpd4_dfs1_ref_req_ctrl_3;	//0xC4D0326C
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_4_T     lpd4_dfs1_ref_req_ctrl_4;	//0xC4D03270
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_5_T     lpd4_dfs1_ref_req_ctrl_5;	//0xC4D03274
	REG_DDRC_M0_LPD4_DFS1_REF_REQ_CTRL_6_T     lpd4_dfs1_ref_req_ctrl_6;	//0xC4D03278
	UINT32                                                 reserved3099;	//0xC4D0327C
	UINT32                                                 reserved3100;	//0xC4D03280
	UINT32                                                 reserved3101;	//0xC4D03284
	UINT32                                                 reserved3102;	//0xC4D03288
	UINT32                                                 reserved3103;	//0xC4D0328C
	REG_DDRC_M0_LPD4_DFS1_REF_CTRL_T                 lpd4_dfs1_ref_ctrl;	//0xC4D03290
	UINT32                                                 reserved3104;	//0xC4D03294
	UINT32                                                 reserved3105;	//0xC4D03298
	UINT32                                                 reserved3106;	//0xC4D0329C
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_0_T       lpd4_dfs1_bank_status_0;	//0xC4D032A0
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_1_T       lpd4_dfs1_bank_status_1;	//0xC4D032A4
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_2_T       lpd4_dfs1_bank_status_2;	//0xC4D032A8
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_3_T       lpd4_dfs1_bank_status_3;	//0xC4D032AC
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_4_T       lpd4_dfs1_bank_status_4;	//0xC4D032B0
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_5_T       lpd4_dfs1_bank_status_5;	//0xC4D032B4
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_6_T       lpd4_dfs1_bank_status_6;	//0xC4D032B8
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_7_T       lpd4_dfs1_bank_status_7;	//0xC4D032BC
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_8_T       lpd4_dfs1_bank_status_8;	//0xC4D032C0
	REG_DDRC_M0_LPD4_DFS1_BANK_STATUS_9_T       lpd4_dfs1_bank_status_9;	//0xC4D032C4
	UINT32                                                 reserved3107;	//0xC4D032C8
	UINT32                                                 reserved3108;	//0xC4D032CC
	UINT32                                                 reserved3109;	//0xC4D032D0
	UINT32                                                 reserved3110;	//0xC4D032D4
	UINT32                                                 reserved3111;	//0xC4D032D8
	UINT32                                                 reserved3112;	//0xC4D032DC
	REG_DDRC_M0_LPD4_DFS1_PHY_IF_T                     lpd4_dfs1_phy_if;	//0xC4D032E0
	UINT32                                                 reserved3113;	//0xC4D032E4
	UINT32                                                 reserved3114;	//0xC4D032E8
	UINT32                                                 reserved3115;	//0xC4D032EC
	UINT32                                                 reserved3116;	//0xC4D032F0
	UINT32                                                 reserved3117;	//0xC4D032F4
	UINT32                                                 reserved3118;	//0xC4D032F8
	UINT32                                                 reserved3119;	//0xC4D032FC
	REG_DDRC_M0_LPD4_DFS2_MR_0_CH0_T                 lpd4_dfs2_mr_0_ch0;	//0xC4D03300
	REG_DDRC_M0_LPD4_DFS2_MR_1_CH0_T                 lpd4_dfs2_mr_1_ch0;	//0xC4D03304
	REG_DDRC_M0_LPD4_DFS2_MR_2_CH0_T                 lpd4_dfs2_mr_2_ch0;	//0xC4D03308
	REG_DDRC_M0_LPD4_DFS2_MR_3_CH0_T                 lpd4_dfs2_mr_3_ch0;	//0xC4D0330C
	REG_DDRC_M0_LPD4_DFS2_MR_4_CH0_T                 lpd4_dfs2_mr_4_ch0;	//0xC4D03310
	REG_DDRC_M0_LPD4_DFS2_MR_5_CH0_T                 lpd4_dfs2_mr_5_ch0;	//0xC4D03314
	REG_DDRC_M0_LPD4_DFS2_MR_6_CH0_T                 lpd4_dfs2_mr_6_ch0;	//0xC4D03318
	UINT32                                                 reserved3120;	//0xC4D0331C
	REG_DDRC_M0_LPD4_DFS2_MR_0_CH1_T                 lpd4_dfs2_mr_0_ch1;	//0xC4D03320
	REG_DDRC_M0_LPD4_DFS2_MR_1_CH1_T                 lpd4_dfs2_mr_1_ch1;	//0xC4D03324
	REG_DDRC_M0_LPD4_DFS2_MR_2_CH1_T                 lpd4_dfs2_mr_2_ch1;	//0xC4D03328
	REG_DDRC_M0_LPD4_DFS2_MR_3_CH1_T                 lpd4_dfs2_mr_3_ch1;	//0xC4D0332C
	REG_DDRC_M0_LPD4_DFS2_MR_4_CH1_T                 lpd4_dfs2_mr_4_ch1;	//0xC4D03330
	REG_DDRC_M0_LPD4_DFS2_MR_5_CH1_T                 lpd4_dfs2_mr_5_ch1;	//0xC4D03334
	REG_DDRC_M0_LPD4_DFS2_MR_6_CH1_T                 lpd4_dfs2_mr_6_ch1;	//0xC4D03338
	UINT32                                                 reserved3121;	//0xC4D0333C
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_0_T             lpd4_dfs2_main_fsm_0;	//0xC4D03340
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_1_T             lpd4_dfs2_main_fsm_1;	//0xC4D03344
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_2_T             lpd4_dfs2_main_fsm_2;	//0xC4D03348
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_3_T             lpd4_dfs2_main_fsm_3;	//0xC4D0334C
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_4_T             lpd4_dfs2_main_fsm_4;	//0xC4D03350
	REG_DDRC_M0_LPD4_DFS2_MAIN_FSM_5_T             lpd4_dfs2_main_fsm_5;	//0xC4D03354
	UINT32                                                 reserved3122;	//0xC4D03358
	UINT32                                                 reserved3123;	//0xC4D0335C
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_0_T     lpd4_dfs2_ref_req_ctrl_0;	//0xC4D03360
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_1_T     lpd4_dfs2_ref_req_ctrl_1;	//0xC4D03364
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_2_T     lpd4_dfs2_ref_req_ctrl_2;	//0xC4D03368
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_3_T     lpd4_dfs2_ref_req_ctrl_3;	//0xC4D0336C
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_4_T     lpd4_dfs2_ref_req_ctrl_4;	//0xC4D03370
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_5_T     lpd4_dfs2_ref_req_ctrl_5;	//0xC4D03374
	REG_DDRC_M0_LPD4_DFS2_REF_REQ_CTRL_6_T     lpd4_dfs2_ref_req_ctrl_6;	//0xC4D03378
	UINT32                                                 reserved3124;	//0xC4D0337C
	UINT32                                                 reserved3125;	//0xC4D03380
	UINT32                                                 reserved3126;	//0xC4D03384
	UINT32                                                 reserved3127;	//0xC4D03388
	UINT32                                                 reserved3128;	//0xC4D0338C
	REG_DDRC_M0_LPD4_DFS2_REF_CTRL_T                 lpd4_dfs2_ref_ctrl;	//0xC4D03390
	UINT32                                                 reserved3129;	//0xC4D03394
	UINT32                                                 reserved3130;	//0xC4D03398
	UINT32                                                 reserved3131;	//0xC4D0339C
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_0_T       lpd4_dfs2_bank_status_0;	//0xC4D033A0
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_1_T       lpd4_dfs2_bank_status_1;	//0xC4D033A4
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_2_T       lpd4_dfs2_bank_status_2;	//0xC4D033A8
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_3_T       lpd4_dfs2_bank_status_3;	//0xC4D033AC
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_4_T       lpd4_dfs2_bank_status_4;	//0xC4D033B0
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_5_T       lpd4_dfs2_bank_status_5;	//0xC4D033B4
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_6_T       lpd4_dfs2_bank_status_6;	//0xC4D033B8
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_7_T       lpd4_dfs2_bank_status_7;	//0xC4D033BC
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_8_T       lpd4_dfs2_bank_status_8;	//0xC4D033C0
	REG_DDRC_M0_LPD4_DFS2_BANK_STATUS_9_T       lpd4_dfs2_bank_status_9;	//0xC4D033C4
	UINT32                                                 reserved3132;	//0xC4D033C8
	UINT32                                                 reserved3133;	//0xC4D033CC
	UINT32                                                 reserved3134;	//0xC4D033D0
	UINT32                                                 reserved3135;	//0xC4D033D4
	UINT32                                                 reserved3136;	//0xC4D033D8
	UINT32                                                 reserved3137;	//0xC4D033DC
	REG_DDRC_M0_LPD4_DFS2_PHY_IF_T                     lpd4_dfs2_phy_if;	//0xC4D033E0
	UINT32                                                 reserved3138;	//0xC4D033E4
	UINT32                                                 reserved3139;	//0xC4D033E8
	UINT32                                                 reserved3140;	//0xC4D033EC
	UINT32                                                 reserved3141;	//0xC4D033F0
	UINT32                                                 reserved3142;	//0xC4D033F4
	UINT32                                                 reserved3143;	//0xC4D033F8
	UINT32                                                 reserved3144;	//0xC4D033FC
	UINT32                                                 reserved3145;	//0xC4D03400
	UINT32                                                 reserved3146;	//0xC4D03404
	UINT32                                                 reserved3147;	//0xC4D03408
	UINT32                                                 reserved3148;	//0xC4D0340C
	UINT32                                                 reserved3149;	//0xC4D03410
	UINT32                                                 reserved3150;	//0xC4D03414
	UINT32                                                 reserved3151;	//0xC4D03418
	UINT32                                                 reserved3152;	//0xC4D0341C
	UINT32                                                 reserved3153;	//0xC4D03420
	UINT32                                                 reserved3154;	//0xC4D03424
	UINT32                                                 reserved3155;	//0xC4D03428
	UINT32                                                 reserved3156;	//0xC4D0342C
	UINT32                                                 reserved3157;	//0xC4D03430
	UINT32                                                 reserved3158;	//0xC4D03434
	UINT32                                                 reserved3159;	//0xC4D03438
	UINT32                                                 reserved3160;	//0xC4D0343C
	UINT32                                                 reserved3161;	//0xC4D03440
	UINT32                                                 reserved3162;	//0xC4D03444
	UINT32                                                 reserved3163;	//0xC4D03448
	UINT32                                                 reserved3164;	//0xC4D0344C
	UINT32                                                 reserved3165;	//0xC4D03450
	UINT32                                                 reserved3166;	//0xC4D03454
	UINT32                                                 reserved3167;	//0xC4D03458
	UINT32                                                 reserved3168;	//0xC4D0345C
	UINT32                                                 reserved3169;	//0xC4D03460
	UINT32                                                 reserved3170;	//0xC4D03464
	UINT32                                                 reserved3171;	//0xC4D03468
	UINT32                                                 reserved3172;	//0xC4D0346C
	UINT32                                                 reserved3173;	//0xC4D03470
	UINT32                                                 reserved3174;	//0xC4D03474
	UINT32                                                 reserved3175;	//0xC4D03478
	UINT32                                                 reserved3176;	//0xC4D0347C
	UINT32                                                 reserved3177;	//0xC4D03480
	UINT32                                                 reserved3178;	//0xC4D03484
	UINT32                                                 reserved3179;	//0xC4D03488
	UINT32                                                 reserved3180;	//0xC4D0348C
	UINT32                                                 reserved3181;	//0xC4D03490
	UINT32                                                 reserved3182;	//0xC4D03494
	UINT32                                                 reserved3183;	//0xC4D03498
	UINT32                                                 reserved3184;	//0xC4D0349C
	UINT32                                                 reserved3185;	//0xC4D034A0
	UINT32                                                 reserved3186;	//0xC4D034A4
	UINT32                                                 reserved3187;	//0xC4D034A8
	UINT32                                                 reserved3188;	//0xC4D034AC
	UINT32                                                 reserved3189;	//0xC4D034B0
	UINT32                                                 reserved3190;	//0xC4D034B4
	UINT32                                                 reserved3191;	//0xC4D034B8
	UINT32                                                 reserved3192;	//0xC4D034BC
	UINT32                                                 reserved3193;	//0xC4D034C0
	UINT32                                                 reserved3194;	//0xC4D034C4
	UINT32                                                 reserved3195;	//0xC4D034C8
	UINT32                                                 reserved3196;	//0xC4D034CC
	UINT32                                                 reserved3197;	//0xC4D034D0
	UINT32                                                 reserved3198;	//0xC4D034D4
	UINT32                                                 reserved3199;	//0xC4D034D8
	UINT32                                                 reserved3200;	//0xC4D034DC
	UINT32                                                 reserved3201;	//0xC4D034E0
	UINT32                                                 reserved3202;	//0xC4D034E4
	UINT32                                                 reserved3203;	//0xC4D034E8
	UINT32                                                 reserved3204;	//0xC4D034EC
	UINT32                                                 reserved3205;	//0xC4D034F0
	UINT32                                                 reserved3206;	//0xC4D034F4
	UINT32                                                 reserved3207;	//0xC4D034F8
	UINT32                                                 reserved3208;	//0xC4D034FC
	UINT32                                                 reserved3209;	//0xC4D03500
	UINT32                                                 reserved3210;	//0xC4D03504
	UINT32                                                 reserved3211;	//0xC4D03508
	UINT32                                                 reserved3212;	//0xC4D0350C
	UINT32                                                 reserved3213;	//0xC4D03510
	UINT32                                                 reserved3214;	//0xC4D03514
	UINT32                                                 reserved3215;	//0xC4D03518
	UINT32                                                 reserved3216;	//0xC4D0351C
	UINT32                                                 reserved3217;	//0xC4D03520
	UINT32                                                 reserved3218;	//0xC4D03524
	UINT32                                                 reserved3219;	//0xC4D03528
	UINT32                                                 reserved3220;	//0xC4D0352C
	UINT32                                                 reserved3221;	//0xC4D03530
	UINT32                                                 reserved3222;	//0xC4D03534
	UINT32                                                 reserved3223;	//0xC4D03538
	UINT32                                                 reserved3224;	//0xC4D0353C
	UINT32                                                 reserved3225;	//0xC4D03540
	UINT32                                                 reserved3226;	//0xC4D03544
	UINT32                                                 reserved3227;	//0xC4D03548
	UINT32                                                 reserved3228;	//0xC4D0354C
	UINT32                                                 reserved3229;	//0xC4D03550
	UINT32                                                 reserved3230;	//0xC4D03554
	UINT32                                                 reserved3231;	//0xC4D03558
	UINT32                                                 reserved3232;	//0xC4D0355C
	UINT32                                                 reserved3233;	//0xC4D03560
	UINT32                                                 reserved3234;	//0xC4D03564
	UINT32                                                 reserved3235;	//0xC4D03568
	UINT32                                                 reserved3236;	//0xC4D0356C
	UINT32                                                 reserved3237;	//0xC4D03570
	UINT32                                                 reserved3238;	//0xC4D03574
	UINT32                                                 reserved3239;	//0xC4D03578
	UINT32                                                 reserved3240;	//0xC4D0357C
	UINT32                                                 reserved3241;	//0xC4D03580
	UINT32                                                 reserved3242;	//0xC4D03584
	UINT32                                                 reserved3243;	//0xC4D03588
	UINT32                                                 reserved3244;	//0xC4D0358C
	UINT32                                                 reserved3245;	//0xC4D03590
	UINT32                                                 reserved3246;	//0xC4D03594
	UINT32                                                 reserved3247;	//0xC4D03598
	UINT32                                                 reserved3248;	//0xC4D0359C
	UINT32                                                 reserved3249;	//0xC4D035A0
	UINT32                                                 reserved3250;	//0xC4D035A4
	UINT32                                                 reserved3251;	//0xC4D035A8
	UINT32                                                 reserved3252;	//0xC4D035AC
	UINT32                                                 reserved3253;	//0xC4D035B0
	UINT32                                                 reserved3254;	//0xC4D035B4
	UINT32                                                 reserved3255;	//0xC4D035B8
	UINT32                                                 reserved3256;	//0xC4D035BC
	UINT32                                                 reserved3257;	//0xC4D035C0
	UINT32                                                 reserved3258;	//0xC4D035C4
	UINT32                                                 reserved3259;	//0xC4D035C8
	UINT32                                                 reserved3260;	//0xC4D035CC
	UINT32                                                 reserved3261;	//0xC4D035D0
	UINT32                                                 reserved3262;	//0xC4D035D4
	UINT32                                                 reserved3263;	//0xC4D035D8
	UINT32                                                 reserved3264;	//0xC4D035DC
	UINT32                                                 reserved3265;	//0xC4D035E0
	UINT32                                                 reserved3266;	//0xC4D035E4
	UINT32                                                 reserved3267;	//0xC4D035E8
	UINT32                                                 reserved3268;	//0xC4D035EC
	UINT32                                                 reserved3269;	//0xC4D035F0
	UINT32                                                 reserved3270;	//0xC4D035F4
	UINT32                                                 reserved3271;	//0xC4D035F8
	UINT32                                                 reserved3272;	//0xC4D035FC
	UINT32                                                 reserved3273;	//0xC4D03600
	UINT32                                                 reserved3274;	//0xC4D03604
	UINT32                                                 reserved3275;	//0xC4D03608
	UINT32                                                 reserved3276;	//0xC4D0360C
	UINT32                                                 reserved3277;	//0xC4D03610
	UINT32                                                 reserved3278;	//0xC4D03614
	UINT32                                                 reserved3279;	//0xC4D03618
	UINT32                                                 reserved3280;	//0xC4D0361C
	UINT32                                                 reserved3281;	//0xC4D03620
	UINT32                                                 reserved3282;	//0xC4D03624
	UINT32                                                 reserved3283;	//0xC4D03628
	UINT32                                                 reserved3284;	//0xC4D0362C
	UINT32                                                 reserved3285;	//0xC4D03630
	UINT32                                                 reserved3286;	//0xC4D03634
	UINT32                                                 reserved3287;	//0xC4D03638
	UINT32                                                 reserved3288;	//0xC4D0363C
	UINT32                                                 reserved3289;	//0xC4D03640
	UINT32                                                 reserved3290;	//0xC4D03644
	UINT32                                                 reserved3291;	//0xC4D03648
	UINT32                                                 reserved3292;	//0xC4D0364C
	UINT32                                                 reserved3293;	//0xC4D03650
	UINT32                                                 reserved3294;	//0xC4D03654
	UINT32                                                 reserved3295;	//0xC4D03658
	UINT32                                                 reserved3296;	//0xC4D0365C
	UINT32                                                 reserved3297;	//0xC4D03660
	UINT32                                                 reserved3298;	//0xC4D03664
	UINT32                                                 reserved3299;	//0xC4D03668
	UINT32                                                 reserved3300;	//0xC4D0366C
	UINT32                                                 reserved3301;	//0xC4D03670
	UINT32                                                 reserved3302;	//0xC4D03674
	UINT32                                                 reserved3303;	//0xC4D03678
	UINT32                                                 reserved3304;	//0xC4D0367C
	UINT32                                                 reserved3305;	//0xC4D03680
	UINT32                                                 reserved3306;	//0xC4D03684
	UINT32                                                 reserved3307;	//0xC4D03688
	UINT32                                                 reserved3308;	//0xC4D0368C
	UINT32                                                 reserved3309;	//0xC4D03690
	UINT32                                                 reserved3310;	//0xC4D03694
	UINT32                                                 reserved3311;	//0xC4D03698
	UINT32                                                 reserved3312;	//0xC4D0369C
	UINT32                                                 reserved3313;	//0xC4D036A0
	UINT32                                                 reserved3314;	//0xC4D036A4
	UINT32                                                 reserved3315;	//0xC4D036A8
	UINT32                                                 reserved3316;	//0xC4D036AC
	UINT32                                                 reserved3317;	//0xC4D036B0
	UINT32                                                 reserved3318;	//0xC4D036B4
	UINT32                                                 reserved3319;	//0xC4D036B8
	UINT32                                                 reserved3320;	//0xC4D036BC
	UINT32                                                 reserved3321;	//0xC4D036C0
	UINT32                                                 reserved3322;	//0xC4D036C4
	UINT32                                                 reserved3323;	//0xC4D036C8
	UINT32                                                 reserved3324;	//0xC4D036CC
	UINT32                                                 reserved3325;	//0xC4D036D0
	UINT32                                                 reserved3326;	//0xC4D036D4
	UINT32                                                 reserved3327;	//0xC4D036D8
	UINT32                                                 reserved3328;	//0xC4D036DC
	UINT32                                                 reserved3329;	//0xC4D036E0
	UINT32                                                 reserved3330;	//0xC4D036E4
	UINT32                                                 reserved3331;	//0xC4D036E8
	UINT32                                                 reserved3332;	//0xC4D036EC
	UINT32                                                 reserved3333;	//0xC4D036F0
	UINT32                                                 reserved3334;	//0xC4D036F4
	UINT32                                                 reserved3335;	//0xC4D036F8
	UINT32                                                 reserved3336;	//0xC4D036FC
	UINT32                                                 reserved3337;	//0xC4D03700
	UINT32                                                 reserved3338;	//0xC4D03704
	UINT32                                                 reserved3339;	//0xC4D03708
	UINT32                                                 reserved3340;	//0xC4D0370C
	UINT32                                                 reserved3341;	//0xC4D03710
	UINT32                                                 reserved3342;	//0xC4D03714
	UINT32                                                 reserved3343;	//0xC4D03718
	UINT32                                                 reserved3344;	//0xC4D0371C
	UINT32                                                 reserved3345;	//0xC4D03720
	UINT32                                                 reserved3346;	//0xC4D03724
	UINT32                                                 reserved3347;	//0xC4D03728
	UINT32                                                 reserved3348;	//0xC4D0372C
	UINT32                                                 reserved3349;	//0xC4D03730
	UINT32                                                 reserved3350;	//0xC4D03734
	UINT32                                                 reserved3351;	//0xC4D03738
	UINT32                                                 reserved3352;	//0xC4D0373C
	UINT32                                                 reserved3353;	//0xC4D03740
	UINT32                                                 reserved3354;	//0xC4D03744
	UINT32                                                 reserved3355;	//0xC4D03748
	UINT32                                                 reserved3356;	//0xC4D0374C
	UINT32                                                 reserved3357;	//0xC4D03750
	UINT32                                                 reserved3358;	//0xC4D03754
	UINT32                                                 reserved3359;	//0xC4D03758
	UINT32                                                 reserved3360;	//0xC4D0375C
	UINT32                                                 reserved3361;	//0xC4D03760
	UINT32                                                 reserved3362;	//0xC4D03764
	UINT32                                                 reserved3363;	//0xC4D03768
	UINT32                                                 reserved3364;	//0xC4D0376C
	UINT32                                                 reserved3365;	//0xC4D03770
	UINT32                                                 reserved3366;	//0xC4D03774
	UINT32                                                 reserved3367;	//0xC4D03778
	UINT32                                                 reserved3368;	//0xC4D0377C
	UINT32                                                 reserved3369;	//0xC4D03780
	UINT32                                                 reserved3370;	//0xC4D03784
	UINT32                                                 reserved3371;	//0xC4D03788
	UINT32                                                 reserved3372;	//0xC4D0378C
	UINT32                                                 reserved3373;	//0xC4D03790
	UINT32                                                 reserved3374;	//0xC4D03794
	UINT32                                                 reserved3375;	//0xC4D03798
	UINT32                                                 reserved3376;	//0xC4D0379C
	UINT32                                                 reserved3377;	//0xC4D037A0
	UINT32                                                 reserved3378;	//0xC4D037A4
	UINT32                                                 reserved3379;	//0xC4D037A8
	UINT32                                                 reserved3380;	//0xC4D037AC
	UINT32                                                 reserved3381;	//0xC4D037B0
	UINT32                                                 reserved3382;	//0xC4D037B4
	UINT32                                                 reserved3383;	//0xC4D037B8
	UINT32                                                 reserved3384;	//0xC4D037BC
	UINT32                                                 reserved3385;	//0xC4D037C0
	UINT32                                                 reserved3386;	//0xC4D037C4
	UINT32                                                 reserved3387;	//0xC4D037C8
	UINT32                                                 reserved3388;	//0xC4D037CC
	UINT32                                                 reserved3389;	//0xC4D037D0
	UINT32                                                 reserved3390;	//0xC4D037D4
	UINT32                                                 reserved3391;	//0xC4D037D8
	UINT32                                                 reserved3392;	//0xC4D037DC
	UINT32                                                 reserved3393;	//0xC4D037E0
	UINT32                                                 reserved3394;	//0xC4D037E4
	UINT32                                                 reserved3395;	//0xC4D037E8
	UINT32                                                 reserved3396;	//0xC4D037EC
	UINT32                                                 reserved3397;	//0xC4D037F0
	UINT32                                                 reserved3398;	//0xC4D037F4
	UINT32                                                 reserved3399;	//0xC4D037F8
	UINT32                                                 reserved3400;	//0xC4D037FC
	UINT32                                                 reserved3401;	//0xC4D03800
	UINT32                                                 reserved3402;	//0xC4D03804
	UINT32                                                 reserved3403;	//0xC4D03808
	UINT32                                                 reserved3404;	//0xC4D0380C
	UINT32                                                 reserved3405;	//0xC4D03810
	UINT32                                                 reserved3406;	//0xC4D03814
	UINT32                                                 reserved3407;	//0xC4D03818
	UINT32                                                 reserved3408;	//0xC4D0381C
	UINT32                                                 reserved3409;	//0xC4D03820
	UINT32                                                 reserved3410;	//0xC4D03824
	UINT32                                                 reserved3411;	//0xC4D03828
	UINT32                                                 reserved3412;	//0xC4D0382C
	UINT32                                                 reserved3413;	//0xC4D03830
	UINT32                                                 reserved3414;	//0xC4D03834
	UINT32                                                 reserved3415;	//0xC4D03838
	UINT32                                                 reserved3416;	//0xC4D0383C
	UINT32                                                 reserved3417;	//0xC4D03840
	UINT32                                                 reserved3418;	//0xC4D03844
	UINT32                                                 reserved3419;	//0xC4D03848
	UINT32                                                 reserved3420;	//0xC4D0384C
	UINT32                                                 reserved3421;	//0xC4D03850
	UINT32                                                 reserved3422;	//0xC4D03854
	UINT32                                                 reserved3423;	//0xC4D03858
	UINT32                                                 reserved3424;	//0xC4D0385C
	UINT32                                                 reserved3425;	//0xC4D03860
	UINT32                                                 reserved3426;	//0xC4D03864
	UINT32                                                 reserved3427;	//0xC4D03868
	UINT32                                                 reserved3428;	//0xC4D0386C
	UINT32                                                 reserved3429;	//0xC4D03870
	UINT32                                                 reserved3430;	//0xC4D03874
	UINT32                                                 reserved3431;	//0xC4D03878
	UINT32                                                 reserved3432;	//0xC4D0387C
	UINT32                                                 reserved3433;	//0xC4D03880
	UINT32                                                 reserved3434;	//0xC4D03884
	UINT32                                                 reserved3435;	//0xC4D03888
	UINT32                                                 reserved3436;	//0xC4D0388C
	UINT32                                                 reserved3437;	//0xC4D03890
	UINT32                                                 reserved3438;	//0xC4D03894
	UINT32                                                 reserved3439;	//0xC4D03898
	UINT32                                                 reserved3440;	//0xC4D0389C
	UINT32                                                 reserved3441;	//0xC4D038A0
	UINT32                                                 reserved3442;	//0xC4D038A4
	UINT32                                                 reserved3443;	//0xC4D038A8
	UINT32                                                 reserved3444;	//0xC4D038AC
	UINT32                                                 reserved3445;	//0xC4D038B0
	UINT32                                                 reserved3446;	//0xC4D038B4
	UINT32                                                 reserved3447;	//0xC4D038B8
	UINT32                                                 reserved3448;	//0xC4D038BC
	UINT32                                                 reserved3449;	//0xC4D038C0
	UINT32                                                 reserved3450;	//0xC4D038C4
	UINT32                                                 reserved3451;	//0xC4D038C8
	UINT32                                                 reserved3452;	//0xC4D038CC
	UINT32                                                 reserved3453;	//0xC4D038D0
	UINT32                                                 reserved3454;	//0xC4D038D4
	UINT32                                                 reserved3455;	//0xC4D038D8
	UINT32                                                 reserved3456;	//0xC4D038DC
	UINT32                                                 reserved3457;	//0xC4D038E0
	UINT32                                                 reserved3458;	//0xC4D038E4
	UINT32                                                 reserved3459;	//0xC4D038E8
	UINT32                                                 reserved3460;	//0xC4D038EC
	UINT32                                                 reserved3461;	//0xC4D038F0
	UINT32                                                 reserved3462;	//0xC4D038F4
	UINT32                                                 reserved3463;	//0xC4D038F8
	UINT32                                                 reserved3464;	//0xC4D038FC
	UINT32                                                 reserved3465;	//0xC4D03900
	UINT32                                                 reserved3466;	//0xC4D03904
	UINT32                                                 reserved3467;	//0xC4D03908
	UINT32                                                 reserved3468;	//0xC4D0390C
	UINT32                                                 reserved3469;	//0xC4D03910
	UINT32                                                 reserved3470;	//0xC4D03914
	UINT32                                                 reserved3471;	//0xC4D03918
	UINT32                                                 reserved3472;	//0xC4D0391C
	UINT32                                                 reserved3473;	//0xC4D03920
	UINT32                                                 reserved3474;	//0xC4D03924
	UINT32                                                 reserved3475;	//0xC4D03928
	UINT32                                                 reserved3476;	//0xC4D0392C
	UINT32                                                 reserved3477;	//0xC4D03930
	UINT32                                                 reserved3478;	//0xC4D03934
	UINT32                                                 reserved3479;	//0xC4D03938
	UINT32                                                 reserved3480;	//0xC4D0393C
	UINT32                                                 reserved3481;	//0xC4D03940
	UINT32                                                 reserved3482;	//0xC4D03944
	UINT32                                                 reserved3483;	//0xC4D03948
	UINT32                                                 reserved3484;	//0xC4D0394C
	UINT32                                                 reserved3485;	//0xC4D03950
	UINT32                                                 reserved3486;	//0xC4D03954
	UINT32                                                 reserved3487;	//0xC4D03958
	UINT32                                                 reserved3488;	//0xC4D0395C
	UINT32                                                 reserved3489;	//0xC4D03960
	UINT32                                                 reserved3490;	//0xC4D03964
	UINT32                                                 reserved3491;	//0xC4D03968
	UINT32                                                 reserved3492;	//0xC4D0396C
	UINT32                                                 reserved3493;	//0xC4D03970
	UINT32                                                 reserved3494;	//0xC4D03974
	UINT32                                                 reserved3495;	//0xC4D03978
	UINT32                                                 reserved3496;	//0xC4D0397C
	UINT32                                                 reserved3497;	//0xC4D03980
	UINT32                                                 reserved3498;	//0xC4D03984
	UINT32                                                 reserved3499;	//0xC4D03988
	UINT32                                                 reserved3500;	//0xC4D0398C
	UINT32                                                 reserved3501;	//0xC4D03990
	UINT32                                                 reserved3502;	//0xC4D03994
	UINT32                                                 reserved3503;	//0xC4D03998
	UINT32                                                 reserved3504;	//0xC4D0399C
	UINT32                                                 reserved3505;	//0xC4D039A0
	UINT32                                                 reserved3506;	//0xC4D039A4
	UINT32                                                 reserved3507;	//0xC4D039A8
	UINT32                                                 reserved3508;	//0xC4D039AC
	UINT32                                                 reserved3509;	//0xC4D039B0
	UINT32                                                 reserved3510;	//0xC4D039B4
	UINT32                                                 reserved3511;	//0xC4D039B8
	UINT32                                                 reserved3512;	//0xC4D039BC
	UINT32                                                 reserved3513;	//0xC4D039C0
	UINT32                                                 reserved3514;	//0xC4D039C4
	UINT32                                                 reserved3515;	//0xC4D039C8
	UINT32                                                 reserved3516;	//0xC4D039CC
	UINT32                                                 reserved3517;	//0xC4D039D0
	UINT32                                                 reserved3518;	//0xC4D039D4
	UINT32                                                 reserved3519;	//0xC4D039D8
	UINT32                                                 reserved3520;	//0xC4D039DC
	UINT32                                                 reserved3521;	//0xC4D039E0
	UINT32                                                 reserved3522;	//0xC4D039E4
	UINT32                                                 reserved3523;	//0xC4D039E8
	UINT32                                                 reserved3524;	//0xC4D039EC
	UINT32                                                 reserved3525;	//0xC4D039F0
	UINT32                                                 reserved3526;	//0xC4D039F4
	UINT32                                                 reserved3527;	//0xC4D039F8
	UINT32                                                 reserved3528;	//0xC4D039FC
	UINT32                                                 reserved3529;	//0xC4D03A00
	UINT32                                                 reserved3530;	//0xC4D03A04
	UINT32                                                 reserved3531;	//0xC4D03A08
	UINT32                                                 reserved3532;	//0xC4D03A0C
	UINT32                                                 reserved3533;	//0xC4D03A10
	UINT32                                                 reserved3534;	//0xC4D03A14
	UINT32                                                 reserved3535;	//0xC4D03A18
	UINT32                                                 reserved3536;	//0xC4D03A1C
	UINT32                                                 reserved3537;	//0xC4D03A20
	UINT32                                                 reserved3538;	//0xC4D03A24
	UINT32                                                 reserved3539;	//0xC4D03A28
	UINT32                                                 reserved3540;	//0xC4D03A2C
	UINT32                                                 reserved3541;	//0xC4D03A30
	UINT32                                                 reserved3542;	//0xC4D03A34
	UINT32                                                 reserved3543;	//0xC4D03A38
	UINT32                                                 reserved3544;	//0xC4D03A3C
	UINT32                                                 reserved3545;	//0xC4D03A40
	UINT32                                                 reserved3546;	//0xC4D03A44
	UINT32                                                 reserved3547;	//0xC4D03A48
	UINT32                                                 reserved3548;	//0xC4D03A4C
	UINT32                                                 reserved3549;	//0xC4D03A50
	UINT32                                                 reserved3550;	//0xC4D03A54
	UINT32                                                 reserved3551;	//0xC4D03A58
	UINT32                                                 reserved3552;	//0xC4D03A5C
	UINT32                                                 reserved3553;	//0xC4D03A60
	UINT32                                                 reserved3554;	//0xC4D03A64
	UINT32                                                 reserved3555;	//0xC4D03A68
	UINT32                                                 reserved3556;	//0xC4D03A6C
	UINT32                                                 reserved3557;	//0xC4D03A70
	UINT32                                                 reserved3558;	//0xC4D03A74
	UINT32                                                 reserved3559;	//0xC4D03A78
	UINT32                                                 reserved3560;	//0xC4D03A7C
	UINT32                                                 reserved3561;	//0xC4D03A80
	UINT32                                                 reserved3562;	//0xC4D03A84
	UINT32                                                 reserved3563;	//0xC4D03A88
	UINT32                                                 reserved3564;	//0xC4D03A8C
	UINT32                                                 reserved3565;	//0xC4D03A90
	UINT32                                                 reserved3566;	//0xC4D03A94
	UINT32                                                 reserved3567;	//0xC4D03A98
	UINT32                                                 reserved3568;	//0xC4D03A9C
	UINT32                                                 reserved3569;	//0xC4D03AA0
	UINT32                                                 reserved3570;	//0xC4D03AA4
	UINT32                                                 reserved3571;	//0xC4D03AA8
	UINT32                                                 reserved3572;	//0xC4D03AAC
	UINT32                                                 reserved3573;	//0xC4D03AB0
	UINT32                                                 reserved3574;	//0xC4D03AB4
	UINT32                                                 reserved3575;	//0xC4D03AB8
	UINT32                                                 reserved3576;	//0xC4D03ABC
	UINT32                                                 reserved3577;	//0xC4D03AC0
	UINT32                                                 reserved3578;	//0xC4D03AC4
	UINT32                                                 reserved3579;	//0xC4D03AC8
	UINT32                                                 reserved3580;	//0xC4D03ACC
	UINT32                                                 reserved3581;	//0xC4D03AD0
	UINT32                                                 reserved3582;	//0xC4D03AD4
	UINT32                                                 reserved3583;	//0xC4D03AD8
	UINT32                                                 reserved3584;	//0xC4D03ADC
	UINT32                                                 reserved3585;	//0xC4D03AE0
	UINT32                                                 reserved3586;	//0xC4D03AE4
	UINT32                                                 reserved3587;	//0xC4D03AE8
	UINT32                                                 reserved3588;	//0xC4D03AEC
	UINT32                                                 reserved3589;	//0xC4D03AF0
	UINT32                                                 reserved3590;	//0xC4D03AF4
	UINT32                                                 reserved3591;	//0xC4D03AF8
	UINT32                                                 reserved3592;	//0xC4D03AFC
	UINT32                                                 reserved3593;	//0xC4D03B00
	UINT32                                                 reserved3594;	//0xC4D03B04
	UINT32                                                 reserved3595;	//0xC4D03B08
	UINT32                                                 reserved3596;	//0xC4D03B0C
	UINT32                                                 reserved3597;	//0xC4D03B10
	UINT32                                                 reserved3598;	//0xC4D03B14
	UINT32                                                 reserved3599;	//0xC4D03B18
	UINT32                                                 reserved3600;	//0xC4D03B1C
	UINT32                                                 reserved3601;	//0xC4D03B20
	UINT32                                                 reserved3602;	//0xC4D03B24
	UINT32                                                 reserved3603;	//0xC4D03B28
	UINT32                                                 reserved3604;	//0xC4D03B2C
	UINT32                                                 reserved3605;	//0xC4D03B30
	UINT32                                                 reserved3606;	//0xC4D03B34
	UINT32                                                 reserved3607;	//0xC4D03B38
	UINT32                                                 reserved3608;	//0xC4D03B3C
	UINT32                                                 reserved3609;	//0xC4D03B40
	UINT32                                                 reserved3610;	//0xC4D03B44
	UINT32                                                 reserved3611;	//0xC4D03B48
	UINT32                                                 reserved3612;	//0xC4D03B4C
	UINT32                                                 reserved3613;	//0xC4D03B50
	UINT32                                                 reserved3614;	//0xC4D03B54
	UINT32                                                 reserved3615;	//0xC4D03B58
	UINT32                                                 reserved3616;	//0xC4D03B5C
	UINT32                                                 reserved3617;	//0xC4D03B60
	UINT32                                                 reserved3618;	//0xC4D03B64
	UINT32                                                 reserved3619;	//0xC4D03B68
	UINT32                                                 reserved3620;	//0xC4D03B6C
	UINT32                                                 reserved3621;	//0xC4D03B70
	UINT32                                                 reserved3622;	//0xC4D03B74
	UINT32                                                 reserved3623;	//0xC4D03B78
	UINT32                                                 reserved3624;	//0xC4D03B7C
	UINT32                                                 reserved3625;	//0xC4D03B80
	UINT32                                                 reserved3626;	//0xC4D03B84
	UINT32                                                 reserved3627;	//0xC4D03B88
	UINT32                                                 reserved3628;	//0xC4D03B8C
	UINT32                                                 reserved3629;	//0xC4D03B90
	UINT32                                                 reserved3630;	//0xC4D03B94
	UINT32                                                 reserved3631;	//0xC4D03B98
	UINT32                                                 reserved3632;	//0xC4D03B9C
	UINT32                                                 reserved3633;	//0xC4D03BA0
	UINT32                                                 reserved3634;	//0xC4D03BA4
	UINT32                                                 reserved3635;	//0xC4D03BA8
	UINT32                                                 reserved3636;	//0xC4D03BAC
	UINT32                                                 reserved3637;	//0xC4D03BB0
	UINT32                                                 reserved3638;	//0xC4D03BB4
	UINT32                                                 reserved3639;	//0xC4D03BB8
	UINT32                                                 reserved3640;	//0xC4D03BBC
	UINT32                                                 reserved3641;	//0xC4D03BC0
	UINT32                                                 reserved3642;	//0xC4D03BC4
	UINT32                                                 reserved3643;	//0xC4D03BC8
	UINT32                                                 reserved3644;	//0xC4D03BCC
	UINT32                                                 reserved3645;	//0xC4D03BD0
	UINT32                                                 reserved3646;	//0xC4D03BD4
	UINT32                                                 reserved3647;	//0xC4D03BD8
	UINT32                                                 reserved3648;	//0xC4D03BDC
	UINT32                                                 reserved3649;	//0xC4D03BE0
	UINT32                                                 reserved3650;	//0xC4D03BE4
	UINT32                                                 reserved3651;	//0xC4D03BE8
	UINT32                                                 reserved3652;	//0xC4D03BEC
	UINT32                                                 reserved3653;	//0xC4D03BF0
	UINT32                                                 reserved3654;	//0xC4D03BF4
	UINT32                                                 reserved3655;	//0xC4D03BF8
	UINT32                                                 reserved3656;	//0xC4D03BFC
	UINT32                                                 reserved3657;	//0xC4D03C00
	UINT32                                                 reserved3658;	//0xC4D03C04
	UINT32                                                 reserved3659;	//0xC4D03C08
	UINT32                                                 reserved3660;	//0xC4D03C0C
	UINT32                                                 reserved3661;	//0xC4D03C10
	UINT32                                                 reserved3662;	//0xC4D03C14
	UINT32                                                 reserved3663;	//0xC4D03C18
	UINT32                                                 reserved3664;	//0xC4D03C1C
	UINT32                                                 reserved3665;	//0xC4D03C20
	UINT32                                                 reserved3666;	//0xC4D03C24
	UINT32                                                 reserved3667;	//0xC4D03C28
	UINT32                                                 reserved3668;	//0xC4D03C2C
	UINT32                                                 reserved3669;	//0xC4D03C30
	UINT32                                                 reserved3670;	//0xC4D03C34
	UINT32                                                 reserved3671;	//0xC4D03C38
	UINT32                                                 reserved3672;	//0xC4D03C3C
	UINT32                                                 reserved3673;	//0xC4D03C40
	UINT32                                                 reserved3674;	//0xC4D03C44
	UINT32                                                 reserved3675;	//0xC4D03C48
	UINT32                                                 reserved3676;	//0xC4D03C4C
	UINT32                                                 reserved3677;	//0xC4D03C50
	UINT32                                                 reserved3678;	//0xC4D03C54
	UINT32                                                 reserved3679;	//0xC4D03C58
	UINT32                                                 reserved3680;	//0xC4D03C5C
	UINT32                                                 reserved3681;	//0xC4D03C60
	UINT32                                                 reserved3682;	//0xC4D03C64
	UINT32                                                 reserved3683;	//0xC4D03C68
	UINT32                                                 reserved3684;	//0xC4D03C6C
	UINT32                                                 reserved3685;	//0xC4D03C70
	UINT32                                                 reserved3686;	//0xC4D03C74
	UINT32                                                 reserved3687;	//0xC4D03C78
	UINT32                                                 reserved3688;	//0xC4D03C7C
	UINT32                                                 reserved3689;	//0xC4D03C80
	UINT32                                                 reserved3690;	//0xC4D03C84
	UINT32                                                 reserved3691;	//0xC4D03C88
	UINT32                                                 reserved3692;	//0xC4D03C8C
	UINT32                                                 reserved3693;	//0xC4D03C90
	UINT32                                                 reserved3694;	//0xC4D03C94
	UINT32                                                 reserved3695;	//0xC4D03C98
	UINT32                                                 reserved3696;	//0xC4D03C9C
	UINT32                                                 reserved3697;	//0xC4D03CA0
	UINT32                                                 reserved3698;	//0xC4D03CA4
	UINT32                                                 reserved3699;	//0xC4D03CA8
	UINT32                                                 reserved3700;	//0xC4D03CAC
	UINT32                                                 reserved3701;	//0xC4D03CB0
	UINT32                                                 reserved3702;	//0xC4D03CB4
	UINT32                                                 reserved3703;	//0xC4D03CB8
	UINT32                                                 reserved3704;	//0xC4D03CBC
	UINT32                                                 reserved3705;	//0xC4D03CC0
	UINT32                                                 reserved3706;	//0xC4D03CC4
	UINT32                                                 reserved3707;	//0xC4D03CC8
	UINT32                                                 reserved3708;	//0xC4D03CCC
	UINT32                                                 reserved3709;	//0xC4D03CD0
	UINT32                                                 reserved3710;	//0xC4D03CD4
	UINT32                                                 reserved3711;	//0xC4D03CD8
	UINT32                                                 reserved3712;	//0xC4D03CDC
	UINT32                                                 reserved3713;	//0xC4D03CE0
	UINT32                                                 reserved3714;	//0xC4D03CE4
	UINT32                                                 reserved3715;	//0xC4D03CE8
	UINT32                                                 reserved3716;	//0xC4D03CEC
	UINT32                                                 reserved3717;	//0xC4D03CF0
	UINT32                                                 reserved3718;	//0xC4D03CF4
	UINT32                                                 reserved3719;	//0xC4D03CF8
	UINT32                                                 reserved3720;	//0xC4D03CFC
	UINT32                                                 reserved3721;	//0xC4D03D00
	UINT32                                                 reserved3722;	//0xC4D03D04
	UINT32                                                 reserved3723;	//0xC4D03D08
	UINT32                                                 reserved3724;	//0xC4D03D0C
	UINT32                                                 reserved3725;	//0xC4D03D10
	UINT32                                                 reserved3726;	//0xC4D03D14
	UINT32                                                 reserved3727;	//0xC4D03D18
	UINT32                                                 reserved3728;	//0xC4D03D1C
	UINT32                                                 reserved3729;	//0xC4D03D20
	UINT32                                                 reserved3730;	//0xC4D03D24
	UINT32                                                 reserved3731;	//0xC4D03D28
	UINT32                                                 reserved3732;	//0xC4D03D2C
	UINT32                                                 reserved3733;	//0xC4D03D30
	UINT32                                                 reserved3734;	//0xC4D03D34
	UINT32                                                 reserved3735;	//0xC4D03D38
	UINT32                                                 reserved3736;	//0xC4D03D3C
	UINT32                                                 reserved3737;	//0xC4D03D40
	UINT32                                                 reserved3738;	//0xC4D03D44
	UINT32                                                 reserved3739;	//0xC4D03D48
	UINT32                                                 reserved3740;	//0xC4D03D4C
	UINT32                                                 reserved3741;	//0xC4D03D50
	UINT32                                                 reserved3742;	//0xC4D03D54
	UINT32                                                 reserved3743;	//0xC4D03D58
	UINT32                                                 reserved3744;	//0xC4D03D5C
	UINT32                                                 reserved3745;	//0xC4D03D60
	UINT32                                                 reserved3746;	//0xC4D03D64
	UINT32                                                 reserved3747;	//0xC4D03D68
	UINT32                                                 reserved3748;	//0xC4D03D6C
	UINT32                                                 reserved3749;	//0xC4D03D70
	UINT32                                                 reserved3750;	//0xC4D03D74
	UINT32                                                 reserved3751;	//0xC4D03D78
	UINT32                                                 reserved3752;	//0xC4D03D7C
	UINT32                                                 reserved3753;	//0xC4D03D80
	UINT32                                                 reserved3754;	//0xC4D03D84
	UINT32                                                 reserved3755;	//0xC4D03D88
	UINT32                                                 reserved3756;	//0xC4D03D8C
	UINT32                                                 reserved3757;	//0xC4D03D90
	UINT32                                                 reserved3758;	//0xC4D03D94
	UINT32                                                 reserved3759;	//0xC4D03D98
	UINT32                                                 reserved3760;	//0xC4D03D9C
	UINT32                                                 reserved3761;	//0xC4D03DA0
	UINT32                                                 reserved3762;	//0xC4D03DA4
	UINT32                                                 reserved3763;	//0xC4D03DA8
	UINT32                                                 reserved3764;	//0xC4D03DAC
	UINT32                                                 reserved3765;	//0xC4D03DB0
	UINT32                                                 reserved3766;	//0xC4D03DB4
	UINT32                                                 reserved3767;	//0xC4D03DB8
	UINT32                                                 reserved3768;	//0xC4D03DBC
	UINT32                                                 reserved3769;	//0xC4D03DC0
	UINT32                                                 reserved3770;	//0xC4D03DC4
	UINT32                                                 reserved3771;	//0xC4D03DC8
	UINT32                                                 reserved3772;	//0xC4D03DCC
	UINT32                                                 reserved3773;	//0xC4D03DD0
	UINT32                                                 reserved3774;	//0xC4D03DD4
	UINT32                                                 reserved3775;	//0xC4D03DD8
	UINT32                                                 reserved3776;	//0xC4D03DDC
	UINT32                                                 reserved3777;	//0xC4D03DE0
	UINT32                                                 reserved3778;	//0xC4D03DE4
	UINT32                                                 reserved3779;	//0xC4D03DE8
	UINT32                                                 reserved3780;	//0xC4D03DEC
	UINT32                                                 reserved3781;	//0xC4D03DF0
	UINT32                                                 reserved3782;	//0xC4D03DF4
	UINT32                                                 reserved3783;	//0xC4D03DF8
	UINT32                                                 reserved3784;	//0xC4D03DFC
	UINT32                                                 reserved3785;	//0xC4D03E00
	UINT32                                                 reserved3786;	//0xC4D03E04
	UINT32                                                 reserved3787;	//0xC4D03E08
	UINT32                                                 reserved3788;	//0xC4D03E0C
	UINT32                                                 reserved3789;	//0xC4D03E10
	UINT32                                                 reserved3790;	//0xC4D03E14
	UINT32                                                 reserved3791;	//0xC4D03E18
	UINT32                                                 reserved3792;	//0xC4D03E1C
	UINT32                                                 reserved3793;	//0xC4D03E20
	UINT32                                                 reserved3794;	//0xC4D03E24
	UINT32                                                 reserved3795;	//0xC4D03E28
	UINT32                                                 reserved3796;	//0xC4D03E2C
	UINT32                                                 reserved3797;	//0xC4D03E30
	UINT32                                                 reserved3798;	//0xC4D03E34
	UINT32                                                 reserved3799;	//0xC4D03E38
	UINT32                                                 reserved3800;	//0xC4D03E3C
	UINT32                                                 reserved3801;	//0xC4D03E40
	UINT32                                                 reserved3802;	//0xC4D03E44
	UINT32                                                 reserved3803;	//0xC4D03E48
	UINT32                                                 reserved3804;	//0xC4D03E4C
	UINT32                                                 reserved3805;	//0xC4D03E50
	UINT32                                                 reserved3806;	//0xC4D03E54
	UINT32                                                 reserved3807;	//0xC4D03E58
	UINT32                                                 reserved3808;	//0xC4D03E5C
	UINT32                                                 reserved3809;	//0xC4D03E60
	UINT32                                                 reserved3810;	//0xC4D03E64
	UINT32                                                 reserved3811;	//0xC4D03E68
	UINT32                                                 reserved3812;	//0xC4D03E6C
	UINT32                                                 reserved3813;	//0xC4D03E70
	UINT32                                                 reserved3814;	//0xC4D03E74
	UINT32                                                 reserved3815;	//0xC4D03E78
	UINT32                                                 reserved3816;	//0xC4D03E7C
	UINT32                                                 reserved3817;	//0xC4D03E80
	UINT32                                                 reserved3818;	//0xC4D03E84
	UINT32                                                 reserved3819;	//0xC4D03E88
	UINT32                                                 reserved3820;	//0xC4D03E8C
	UINT32                                                 reserved3821;	//0xC4D03E90
	UINT32                                                 reserved3822;	//0xC4D03E94
	UINT32                                                 reserved3823;	//0xC4D03E98
	UINT32                                                 reserved3824;	//0xC4D03E9C
	UINT32                                                 reserved3825;	//0xC4D03EA0
	UINT32                                                 reserved3826;	//0xC4D03EA4
	UINT32                                                 reserved3827;	//0xC4D03EA8
	UINT32                                                 reserved3828;	//0xC4D03EAC
	UINT32                                                 reserved3829;	//0xC4D03EB0
	UINT32                                                 reserved3830;	//0xC4D03EB4
	UINT32                                                 reserved3831;	//0xC4D03EB8
	UINT32                                                 reserved3832;	//0xC4D03EBC
	UINT32                                                 reserved3833;	//0xC4D03EC0
	UINT32                                                 reserved3834;	//0xC4D03EC4
	UINT32                                                 reserved3835;	//0xC4D03EC8
	UINT32                                                 reserved3836;	//0xC4D03ECC
	UINT32                                                 reserved3837;	//0xC4D03ED0
	UINT32                                                 reserved3838;	//0xC4D03ED4
	UINT32                                                 reserved3839;	//0xC4D03ED8
	UINT32                                                 reserved3840;	//0xC4D03EDC
	UINT32                                                 reserved3841;	//0xC4D03EE0
	UINT32                                                 reserved3842;	//0xC4D03EE4
	UINT32                                                 reserved3843;	//0xC4D03EE8
	UINT32                                                 reserved3844;	//0xC4D03EEC
	UINT32                                                 reserved3845;	//0xC4D03EF0
	UINT32                                                 reserved3846;	//0xC4D03EF4
	UINT32                                                 reserved3847;	//0xC4D03EF8
	UINT32                                                 reserved3848;	//0xC4D03EFC
	UINT32                                                 reserved3849;	//0xC4D03F00
	UINT32                                                 reserved3850;	//0xC4D03F04
	UINT32                                                 reserved3851;	//0xC4D03F08
	UINT32                                                 reserved3852;	//0xC4D03F0C
	UINT32                                                 reserved3853;	//0xC4D03F10
	UINT32                                                 reserved3854;	//0xC4D03F14
	UINT32                                                 reserved3855;	//0xC4D03F18
	UINT32                                                 reserved3856;	//0xC4D03F1C
	UINT32                                                 reserved3857;	//0xC4D03F20
	UINT32                                                 reserved3858;	//0xC4D03F24
	UINT32                                                 reserved3859;	//0xC4D03F28
	UINT32                                                 reserved3860;	//0xC4D03F2C
	UINT32                                                 reserved3861;	//0xC4D03F30
	UINT32                                                 reserved3862;	//0xC4D03F34
	UINT32                                                 reserved3863;	//0xC4D03F38
	UINT32                                                 reserved3864;	//0xC4D03F3C
	UINT32                                                 reserved3865;	//0xC4D03F40
	UINT32                                                 reserved3866;	//0xC4D03F44
	UINT32                                                 reserved3867;	//0xC4D03F48
	UINT32                                                 reserved3868;	//0xC4D03F4C
	UINT32                                                 reserved3869;	//0xC4D03F50
	UINT32                                                 reserved3870;	//0xC4D03F54
	UINT32                                                 reserved3871;	//0xC4D03F58
	UINT32                                                 reserved3872;	//0xC4D03F5C
	UINT32                                                 reserved3873;	//0xC4D03F60
	UINT32                                                 reserved3874;	//0xC4D03F64
	UINT32                                                 reserved3875;	//0xC4D03F68
	UINT32                                                 reserved3876;	//0xC4D03F6C
	UINT32                                                 reserved3877;	//0xC4D03F70
	UINT32                                                 reserved3878;	//0xC4D03F74
	UINT32                                                 reserved3879;	//0xC4D03F78
	UINT32                                                 reserved3880;	//0xC4D03F7C
	UINT32                                                 reserved3881;	//0xC4D03F80
	UINT32                                                 reserved3882;	//0xC4D03F84
	UINT32                                                 reserved3883;	//0xC4D03F88
	UINT32                                                 reserved3884;	//0xC4D03F8C
	UINT32                                                 reserved3885;	//0xC4D03F90
	UINT32                                                 reserved3886;	//0xC4D03F94
	UINT32                                                 reserved3887;	//0xC4D03F98
	UINT32                                                 reserved3888;	//0xC4D03F9C
	UINT32                                                 reserved3889;	//0xC4D03FA0
	UINT32                                                 reserved3890;	//0xC4D03FA4
	UINT32                                                 reserved3891;	//0xC4D03FA8
	UINT32                                                 reserved3892;	//0xC4D03FAC
	UINT32                                                 reserved3893;	//0xC4D03FB0
	UINT32                                                 reserved3894;	//0xC4D03FB4
	UINT32                                                 reserved3895;	//0xC4D03FB8
	UINT32                                                 reserved3896;	//0xC4D03FBC
	UINT32                                                 reserved3897;	//0xC4D03FC0
	UINT32                                                 reserved3898;	//0xC4D03FC4
	UINT32                                                 reserved3899;	//0xC4D03FC8
	UINT32                                                 reserved3900;	//0xC4D03FCC
	UINT32                                                 reserved3901;	//0xC4D03FD0
	UINT32                                                 reserved3902;	//0xC4D03FD4
	UINT32                                                 reserved3903;	//0xC4D03FD8
	UINT32                                                 reserved3904;	//0xC4D03FDC
	UINT32                                                 reserved3905;	//0xC4D03FE0
	UINT32                                                 reserved3906;	//0xC4D03FE4
	UINT32                                                 reserved3907;	//0xC4D03FE8
	UINT32                                                 reserved3908;	//0xC4D03FEC
	UINT32                                                 reserved3909;	//0xC4D03FF0
	UINT32                                                 reserved3910;	//0xC4D03FF4
	UINT32                                                 reserved3911;	//0xC4D03FF8
	UINT32                                                 reserved3912;	//0xC4D03FFC
	UINT32                                                 reserved3913;	//0xC4D04000
	UINT32                                                 reserved3914;	//0xC4D04004
	UINT32                                                 reserved3915;	//0xC4D04008
	UINT32                                                 reserved3916;	//0xC4D0400C
	UINT32                                                 reserved3917;	//0xC4D04010
	UINT32                                                 reserved3918;	//0xC4D04014
	UINT32                                                 reserved3919;	//0xC4D04018
	UINT32                                                 reserved3920;	//0xC4D0401C
	UINT32                                                 reserved3921;	//0xC4D04020
	UINT32                                                 reserved3922;	//0xC4D04024
	UINT32                                                 reserved3923;	//0xC4D04028
	UINT32                                                 reserved3924;	//0xC4D0402C
	UINT32                                                 reserved3925;	//0xC4D04030
	UINT32                                                 reserved3926;	//0xC4D04034
	UINT32                                                 reserved3927;	//0xC4D04038
	UINT32                                                 reserved3928;	//0xC4D0403C
	UINT32                                                 reserved3929;	//0xC4D04040
	UINT32                                                 reserved3930;	//0xC4D04044
	UINT32                                                 reserved3931;	//0xC4D04048
	UINT32                                                 reserved3932;	//0xC4D0404C
	UINT32                                                 reserved3933;	//0xC4D04050
	UINT32                                                 reserved3934;	//0xC4D04054
	UINT32                                                 reserved3935;	//0xC4D04058
	UINT32                                                 reserved3936;	//0xC4D0405C
	UINT32                                                 reserved3937;	//0xC4D04060
	UINT32                                                 reserved3938;	//0xC4D04064
	UINT32                                                 reserved3939;	//0xC4D04068
	UINT32                                                 reserved3940;	//0xC4D0406C
	UINT32                                                 reserved3941;	//0xC4D04070
	UINT32                                                 reserved3942;	//0xC4D04074
	UINT32                                                 reserved3943;	//0xC4D04078
	UINT32                                                 reserved3944;	//0xC4D0407C
	UINT32                                                 reserved3945;	//0xC4D04080
	UINT32                                                 reserved3946;	//0xC4D04084
	UINT32                                                 reserved3947;	//0xC4D04088
	UINT32                                                 reserved3948;	//0xC4D0408C
	UINT32                                                 reserved3949;	//0xC4D04090
	UINT32                                                 reserved3950;	//0xC4D04094
	UINT32                                                 reserved3951;	//0xC4D04098
	UINT32                                                 reserved3952;	//0xC4D0409C
	UINT32                                                 reserved3953;	//0xC4D040A0
	UINT32                                                 reserved3954;	//0xC4D040A4
	UINT32                                                 reserved3955;	//0xC4D040A8
	UINT32                                                 reserved3956;	//0xC4D040AC
	UINT32                                                 reserved3957;	//0xC4D040B0
	UINT32                                                 reserved3958;	//0xC4D040B4
	UINT32                                                 reserved3959;	//0xC4D040B8
	UINT32                                                 reserved3960;	//0xC4D040BC
	UINT32                                                 reserved3961;	//0xC4D040C0
	UINT32                                                 reserved3962;	//0xC4D040C4
	UINT32                                                 reserved3963;	//0xC4D040C8
	UINT32                                                 reserved3964;	//0xC4D040CC
	UINT32                                                 reserved3965;	//0xC4D040D0
	UINT32                                                 reserved3966;	//0xC4D040D4
	UINT32                                                 reserved3967;	//0xC4D040D8
	UINT32                                                 reserved3968;	//0xC4D040DC
	UINT32                                                 reserved3969;	//0xC4D040E0
	UINT32                                                 reserved3970;	//0xC4D040E4
	UINT32                                                 reserved3971;	//0xC4D040E8
	UINT32                                                 reserved3972;	//0xC4D040EC
	UINT32                                                 reserved3973;	//0xC4D040F0
	UINT32                                                 reserved3974;	//0xC4D040F4
	UINT32                                                 reserved3975;	//0xC4D040F8
	UINT32                                                 reserved3976;	//0xC4D040FC
	UINT32                                                 reserved3977;	//0xC4D04100
	UINT32                                                 reserved3978;	//0xC4D04104
	UINT32                                                 reserved3979;	//0xC4D04108
	UINT32                                                 reserved3980;	//0xC4D0410C
	UINT32                                                 reserved3981;	//0xC4D04110
	UINT32                                                 reserved3982;	//0xC4D04114
	UINT32                                                 reserved3983;	//0xC4D04118
	UINT32                                                 reserved3984;	//0xC4D0411C
	UINT32                                                 reserved3985;	//0xC4D04120
	UINT32                                                 reserved3986;	//0xC4D04124
	UINT32                                                 reserved3987;	//0xC4D04128
	UINT32                                                 reserved3988;	//0xC4D0412C
	UINT32                                                 reserved3989;	//0xC4D04130
	UINT32                                                 reserved3990;	//0xC4D04134
	UINT32                                                 reserved3991;	//0xC4D04138
	UINT32                                                 reserved3992;	//0xC4D0413C
	UINT32                                                 reserved3993;	//0xC4D04140
	UINT32                                                 reserved3994;	//0xC4D04144
	UINT32                                                 reserved3995;	//0xC4D04148
	UINT32                                                 reserved3996;	//0xC4D0414C
	UINT32                                                 reserved3997;	//0xC4D04150
	UINT32                                                 reserved3998;	//0xC4D04154
	UINT32                                                 reserved3999;	//0xC4D04158
	UINT32                                                 reserved4000;	//0xC4D0415C
	UINT32                                                 reserved4001;	//0xC4D04160
	UINT32                                                 reserved4002;	//0xC4D04164
	UINT32                                                 reserved4003;	//0xC4D04168
	UINT32                                                 reserved4004;	//0xC4D0416C
	UINT32                                                 reserved4005;	//0xC4D04170
	UINT32                                                 reserved4006;	//0xC4D04174
	UINT32                                                 reserved4007;	//0xC4D04178
	UINT32                                                 reserved4008;	//0xC4D0417C
	UINT32                                                 reserved4009;	//0xC4D04180
	UINT32                                                 reserved4010;	//0xC4D04184
	UINT32                                                 reserved4011;	//0xC4D04188
	UINT32                                                 reserved4012;	//0xC4D0418C
	UINT32                                                 reserved4013;	//0xC4D04190
	UINT32                                                 reserved4014;	//0xC4D04194
	UINT32                                                 reserved4015;	//0xC4D04198
	UINT32                                                 reserved4016;	//0xC4D0419C
	UINT32                                                 reserved4017;	//0xC4D041A0
	UINT32                                                 reserved4018;	//0xC4D041A4
	UINT32                                                 reserved4019;	//0xC4D041A8
	UINT32                                                 reserved4020;	//0xC4D041AC
	UINT32                                                 reserved4021;	//0xC4D041B0
	UINT32                                                 reserved4022;	//0xC4D041B4
	UINT32                                                 reserved4023;	//0xC4D041B8
	UINT32                                                 reserved4024;	//0xC4D041BC
	UINT32                                                 reserved4025;	//0xC4D041C0
	UINT32                                                 reserved4026;	//0xC4D041C4
	UINT32                                                 reserved4027;	//0xC4D041C8
	UINT32                                                 reserved4028;	//0xC4D041CC
	UINT32                                                 reserved4029;	//0xC4D041D0
	UINT32                                                 reserved4030;	//0xC4D041D4
	UINT32                                                 reserved4031;	//0xC4D041D8
	UINT32                                                 reserved4032;	//0xC4D041DC
	UINT32                                                 reserved4033;	//0xC4D041E0
	UINT32                                                 reserved4034;	//0xC4D041E4
	UINT32                                                 reserved4035;	//0xC4D041E8
	UINT32                                                 reserved4036;	//0xC4D041EC
	UINT32                                                 reserved4037;	//0xC4D041F0
	UINT32                                                 reserved4038;	//0xC4D041F4
	UINT32                                                 reserved4039;	//0xC4D041F8
	UINT32                                                 reserved4040;	//0xC4D041FC
	UINT32                                                 reserved4041;	//0xC4D04200
	UINT32                                                 reserved4042;	//0xC4D04204
	UINT32                                                 reserved4043;	//0xC4D04208
	UINT32                                                 reserved4044;	//0xC4D0420C
	UINT32                                                 reserved4045;	//0xC4D04210
	UINT32                                                 reserved4046;	//0xC4D04214
	UINT32                                                 reserved4047;	//0xC4D04218
	UINT32                                                 reserved4048;	//0xC4D0421C
	UINT32                                                 reserved4049;	//0xC4D04220
	UINT32                                                 reserved4050;	//0xC4D04224
	UINT32                                                 reserved4051;	//0xC4D04228
	UINT32                                                 reserved4052;	//0xC4D0422C
	UINT32                                                 reserved4053;	//0xC4D04230
	UINT32                                                 reserved4054;	//0xC4D04234
	UINT32                                                 reserved4055;	//0xC4D04238
	UINT32                                                 reserved4056;	//0xC4D0423C
	UINT32                                                 reserved4057;	//0xC4D04240
	UINT32                                                 reserved4058;	//0xC4D04244
	UINT32                                                 reserved4059;	//0xC4D04248
	UINT32                                                 reserved4060;	//0xC4D0424C
	UINT32                                                 reserved4061;	//0xC4D04250
	UINT32                                                 reserved4062;	//0xC4D04254
	UINT32                                                 reserved4063;	//0xC4D04258
	UINT32                                                 reserved4064;	//0xC4D0425C
	UINT32                                                 reserved4065;	//0xC4D04260
	UINT32                                                 reserved4066;	//0xC4D04264
	UINT32                                                 reserved4067;	//0xC4D04268
	UINT32                                                 reserved4068;	//0xC4D0426C
	UINT32                                                 reserved4069;	//0xC4D04270
	UINT32                                                 reserved4070;	//0xC4D04274
	UINT32                                                 reserved4071;	//0xC4D04278
	UINT32                                                 reserved4072;	//0xC4D0427C
	UINT32                                                 reserved4073;	//0xC4D04280
	UINT32                                                 reserved4074;	//0xC4D04284
	UINT32                                                 reserved4075;	//0xC4D04288
	UINT32                                                 reserved4076;	//0xC4D0428C
	UINT32                                                 reserved4077;	//0xC4D04290
	UINT32                                                 reserved4078;	//0xC4D04294
	UINT32                                                 reserved4079;	//0xC4D04298
	UINT32                                                 reserved4080;	//0xC4D0429C
	UINT32                                                 reserved4081;	//0xC4D042A0
	UINT32                                                 reserved4082;	//0xC4D042A4
	UINT32                                                 reserved4083;	//0xC4D042A8
	UINT32                                                 reserved4084;	//0xC4D042AC
	UINT32                                                 reserved4085;	//0xC4D042B0
	UINT32                                                 reserved4086;	//0xC4D042B4
	UINT32                                                 reserved4087;	//0xC4D042B8
	UINT32                                                 reserved4088;	//0xC4D042BC
	UINT32                                                 reserved4089;	//0xC4D042C0
	UINT32                                                 reserved4090;	//0xC4D042C4
	UINT32                                                 reserved4091;	//0xC4D042C8
	UINT32                                                 reserved4092;	//0xC4D042CC
	UINT32                                                 reserved4093;	//0xC4D042D0
	UINT32                                                 reserved4094;	//0xC4D042D4
	UINT32                                                 reserved4095;	//0xC4D042D8
	UINT32                                                 reserved4096;	//0xC4D042DC
	UINT32                                                 reserved4097;	//0xC4D042E0
	UINT32                                                 reserved4098;	//0xC4D042E4
	UINT32                                                 reserved4099;	//0xC4D042E8
	UINT32                                                 reserved4100;	//0xC4D042EC
	UINT32                                                 reserved4101;	//0xC4D042F0
	UINT32                                                 reserved4102;	//0xC4D042F4
	UINT32                                                 reserved4103;	//0xC4D042F8
	UINT32                                                 reserved4104;	//0xC4D042FC
	UINT32                                                 reserved4105;	//0xC4D04300
	UINT32                                                 reserved4106;	//0xC4D04304
	UINT32                                                 reserved4107;	//0xC4D04308
	UINT32                                                 reserved4108;	//0xC4D0430C
	UINT32                                                 reserved4109;	//0xC4D04310
	UINT32                                                 reserved4110;	//0xC4D04314
	UINT32                                                 reserved4111;	//0xC4D04318
	UINT32                                                 reserved4112;	//0xC4D0431C
	UINT32                                                 reserved4113;	//0xC4D04320
	UINT32                                                 reserved4114;	//0xC4D04324
	UINT32                                                 reserved4115;	//0xC4D04328
	UINT32                                                 reserved4116;	//0xC4D0432C
	UINT32                                                 reserved4117;	//0xC4D04330
	UINT32                                                 reserved4118;	//0xC4D04334
	UINT32                                                 reserved4119;	//0xC4D04338
	UINT32                                                 reserved4120;	//0xC4D0433C
	UINT32                                                 reserved4121;	//0xC4D04340
	UINT32                                                 reserved4122;	//0xC4D04344
	UINT32                                                 reserved4123;	//0xC4D04348
	UINT32                                                 reserved4124;	//0xC4D0434C
	UINT32                                                 reserved4125;	//0xC4D04350
	UINT32                                                 reserved4126;	//0xC4D04354
	UINT32                                                 reserved4127;	//0xC4D04358
	UINT32                                                 reserved4128;	//0xC4D0435C
	UINT32                                                 reserved4129;	//0xC4D04360
	UINT32                                                 reserved4130;	//0xC4D04364
	UINT32                                                 reserved4131;	//0xC4D04368
	UINT32                                                 reserved4132;	//0xC4D0436C
	UINT32                                                 reserved4133;	//0xC4D04370
	UINT32                                                 reserved4134;	//0xC4D04374
	UINT32                                                 reserved4135;	//0xC4D04378
	UINT32                                                 reserved4136;	//0xC4D0437C
	UINT32                                                 reserved4137;	//0xC4D04380
	UINT32                                                 reserved4138;	//0xC4D04384
	UINT32                                                 reserved4139;	//0xC4D04388
	UINT32                                                 reserved4140;	//0xC4D0438C
	UINT32                                                 reserved4141;	//0xC4D04390
	UINT32                                                 reserved4142;	//0xC4D04394
	UINT32                                                 reserved4143;	//0xC4D04398
	UINT32                                                 reserved4144;	//0xC4D0439C
	UINT32                                                 reserved4145;	//0xC4D043A0
	UINT32                                                 reserved4146;	//0xC4D043A4
	UINT32                                                 reserved4147;	//0xC4D043A8
	UINT32                                                 reserved4148;	//0xC4D043AC
	UINT32                                                 reserved4149;	//0xC4D043B0
	UINT32                                                 reserved4150;	//0xC4D043B4
	UINT32                                                 reserved4151;	//0xC4D043B8
	UINT32                                                 reserved4152;	//0xC4D043BC
	UINT32                                                 reserved4153;	//0xC4D043C0
	UINT32                                                 reserved4154;	//0xC4D043C4
	UINT32                                                 reserved4155;	//0xC4D043C8
	UINT32                                                 reserved4156;	//0xC4D043CC
	UINT32                                                 reserved4157;	//0xC4D043D0
	UINT32                                                 reserved4158;	//0xC4D043D4
	UINT32                                                 reserved4159;	//0xC4D043D8
	UINT32                                                 reserved4160;	//0xC4D043DC
	UINT32                                                 reserved4161;	//0xC4D043E0
	UINT32                                                 reserved4162;	//0xC4D043E4
	UINT32                                                 reserved4163;	//0xC4D043E8
	UINT32                                                 reserved4164;	//0xC4D043EC
	UINT32                                                 reserved4165;	//0xC4D043F0
	UINT32                                                 reserved4166;	//0xC4D043F4
	UINT32                                                 reserved4167;	//0xC4D043F8
	UINT32                                                 reserved4168;	//0xC4D043FC
	UINT32                                                 reserved4169;	//0xC4D04400
	UINT32                                                 reserved4170;	//0xC4D04404
	UINT32                                                 reserved4171;	//0xC4D04408
	UINT32                                                 reserved4172;	//0xC4D0440C
	UINT32                                                 reserved4173;	//0xC4D04410
	UINT32                                                 reserved4174;	//0xC4D04414
	UINT32                                                 reserved4175;	//0xC4D04418
	UINT32                                                 reserved4176;	//0xC4D0441C
	UINT32                                                 reserved4177;	//0xC4D04420
	UINT32                                                 reserved4178;	//0xC4D04424
	UINT32                                                 reserved4179;	//0xC4D04428
	UINT32                                                 reserved4180;	//0xC4D0442C
	UINT32                                                 reserved4181;	//0xC4D04430
	UINT32                                                 reserved4182;	//0xC4D04434
	UINT32                                                 reserved4183;	//0xC4D04438
	UINT32                                                 reserved4184;	//0xC4D0443C
	UINT32                                                 reserved4185;	//0xC4D04440
	UINT32                                                 reserved4186;	//0xC4D04444
	UINT32                                                 reserved4187;	//0xC4D04448
	UINT32                                                 reserved4188;	//0xC4D0444C
	UINT32                                                 reserved4189;	//0xC4D04450
	UINT32                                                 reserved4190;	//0xC4D04454
	UINT32                                                 reserved4191;	//0xC4D04458
	UINT32                                                 reserved4192;	//0xC4D0445C
	UINT32                                                 reserved4193;	//0xC4D04460
	UINT32                                                 reserved4194;	//0xC4D04464
	UINT32                                                 reserved4195;	//0xC4D04468
	UINT32                                                 reserved4196;	//0xC4D0446C
	UINT32                                                 reserved4197;	//0xC4D04470
	UINT32                                                 reserved4198;	//0xC4D04474
	UINT32                                                 reserved4199;	//0xC4D04478
	UINT32                                                 reserved4200;	//0xC4D0447C
	UINT32                                                 reserved4201;	//0xC4D04480
	UINT32                                                 reserved4202;	//0xC4D04484
	UINT32                                                 reserved4203;	//0xC4D04488
	UINT32                                                 reserved4204;	//0xC4D0448C
	UINT32                                                 reserved4205;	//0xC4D04490
	UINT32                                                 reserved4206;	//0xC4D04494
	UINT32                                                 reserved4207;	//0xC4D04498
	UINT32                                                 reserved4208;	//0xC4D0449C
	UINT32                                                 reserved4209;	//0xC4D044A0
	UINT32                                                 reserved4210;	//0xC4D044A4
	UINT32                                                 reserved4211;	//0xC4D044A8
	UINT32                                                 reserved4212;	//0xC4D044AC
	UINT32                                                 reserved4213;	//0xC4D044B0
	UINT32                                                 reserved4214;	//0xC4D044B4
	UINT32                                                 reserved4215;	//0xC4D044B8
	UINT32                                                 reserved4216;	//0xC4D044BC
	UINT32                                                 reserved4217;	//0xC4D044C0
	UINT32                                                 reserved4218;	//0xC4D044C4
	UINT32                                                 reserved4219;	//0xC4D044C8
	UINT32                                                 reserved4220;	//0xC4D044CC
	UINT32                                                 reserved4221;	//0xC4D044D0
	UINT32                                                 reserved4222;	//0xC4D044D4
	UINT32                                                 reserved4223;	//0xC4D044D8
	UINT32                                                 reserved4224;	//0xC4D044DC
	UINT32                                                 reserved4225;	//0xC4D044E0
	UINT32                                                 reserved4226;	//0xC4D044E4
	UINT32                                                 reserved4227;	//0xC4D044E8
	UINT32                                                 reserved4228;	//0xC4D044EC
	UINT32                                                 reserved4229;	//0xC4D044F0
	UINT32                                                 reserved4230;	//0xC4D044F4
	UINT32                                                 reserved4231;	//0xC4D044F8
	UINT32                                                 reserved4232;	//0xC4D044FC
	UINT32                                                 reserved4233;	//0xC4D04500
	UINT32                                                 reserved4234;	//0xC4D04504
	UINT32                                                 reserved4235;	//0xC4D04508
	UINT32                                                 reserved4236;	//0xC4D0450C
	UINT32                                                 reserved4237;	//0xC4D04510
	UINT32                                                 reserved4238;	//0xC4D04514
	UINT32                                                 reserved4239;	//0xC4D04518
	UINT32                                                 reserved4240;	//0xC4D0451C
	UINT32                                                 reserved4241;	//0xC4D04520
	UINT32                                                 reserved4242;	//0xC4D04524
	UINT32                                                 reserved4243;	//0xC4D04528
	UINT32                                                 reserved4244;	//0xC4D0452C
	UINT32                                                 reserved4245;	//0xC4D04530
	UINT32                                                 reserved4246;	//0xC4D04534
	UINT32                                                 reserved4247;	//0xC4D04538
	UINT32                                                 reserved4248;	//0xC4D0453C
	UINT32                                                 reserved4249;	//0xC4D04540
	UINT32                                                 reserved4250;	//0xC4D04544
	UINT32                                                 reserved4251;	//0xC4D04548
	UINT32                                                 reserved4252;	//0xC4D0454C
	UINT32                                                 reserved4253;	//0xC4D04550
	UINT32                                                 reserved4254;	//0xC4D04554
	UINT32                                                 reserved4255;	//0xC4D04558
	UINT32                                                 reserved4256;	//0xC4D0455C
	UINT32                                                 reserved4257;	//0xC4D04560
	UINT32                                                 reserved4258;	//0xC4D04564
	UINT32                                                 reserved4259;	//0xC4D04568
	UINT32                                                 reserved4260;	//0xC4D0456C
	UINT32                                                 reserved4261;	//0xC4D04570
	UINT32                                                 reserved4262;	//0xC4D04574
	UINT32                                                 reserved4263;	//0xC4D04578
	UINT32                                                 reserved4264;	//0xC4D0457C
	UINT32                                                 reserved4265;	//0xC4D04580
	UINT32                                                 reserved4266;	//0xC4D04584
	UINT32                                                 reserved4267;	//0xC4D04588
	UINT32                                                 reserved4268;	//0xC4D0458C
	UINT32                                                 reserved4269;	//0xC4D04590
	UINT32                                                 reserved4270;	//0xC4D04594
	UINT32                                                 reserved4271;	//0xC4D04598
	UINT32                                                 reserved4272;	//0xC4D0459C
	UINT32                                                 reserved4273;	//0xC4D045A0
	UINT32                                                 reserved4274;	//0xC4D045A4
	UINT32                                                 reserved4275;	//0xC4D045A8
	UINT32                                                 reserved4276;	//0xC4D045AC
	UINT32                                                 reserved4277;	//0xC4D045B0
	UINT32                                                 reserved4278;	//0xC4D045B4
	UINT32                                                 reserved4279;	//0xC4D045B8
	UINT32                                                 reserved4280;	//0xC4D045BC
	UINT32                                                 reserved4281;	//0xC4D045C0
	UINT32                                                 reserved4282;	//0xC4D045C4
	UINT32                                                 reserved4283;	//0xC4D045C8
	UINT32                                                 reserved4284;	//0xC4D045CC
	UINT32                                                 reserved4285;	//0xC4D045D0
	UINT32                                                 reserved4286;	//0xC4D045D4
	UINT32                                                 reserved4287;	//0xC4D045D8
	UINT32                                                 reserved4288;	//0xC4D045DC
	UINT32                                                 reserved4289;	//0xC4D045E0
	UINT32                                                 reserved4290;	//0xC4D045E4
	UINT32                                                 reserved4291;	//0xC4D045E8
	UINT32                                                 reserved4292;	//0xC4D045EC
	UINT32                                                 reserved4293;	//0xC4D045F0
	UINT32                                                 reserved4294;	//0xC4D045F4
	UINT32                                                 reserved4295;	//0xC4D045F8
	UINT32                                                 reserved4296;	//0xC4D045FC
	UINT32                                                 reserved4297;	//0xC4D04600
	UINT32                                                 reserved4298;	//0xC4D04604
	UINT32                                                 reserved4299;	//0xC4D04608
	UINT32                                                 reserved4300;	//0xC4D0460C
	UINT32                                                 reserved4301;	//0xC4D04610
	UINT32                                                 reserved4302;	//0xC4D04614
	UINT32                                                 reserved4303;	//0xC4D04618
	UINT32                                                 reserved4304;	//0xC4D0461C
	UINT32                                                 reserved4305;	//0xC4D04620
	UINT32                                                 reserved4306;	//0xC4D04624
	UINT32                                                 reserved4307;	//0xC4D04628
	UINT32                                                 reserved4308;	//0xC4D0462C
	UINT32                                                 reserved4309;	//0xC4D04630
	UINT32                                                 reserved4310;	//0xC4D04634
	UINT32                                                 reserved4311;	//0xC4D04638
	UINT32                                                 reserved4312;	//0xC4D0463C
	UINT32                                                 reserved4313;	//0xC4D04640
	UINT32                                                 reserved4314;	//0xC4D04644
	UINT32                                                 reserved4315;	//0xC4D04648
	UINT32                                                 reserved4316;	//0xC4D0464C
	UINT32                                                 reserved4317;	//0xC4D04650
	UINT32                                                 reserved4318;	//0xC4D04654
	UINT32                                                 reserved4319;	//0xC4D04658
	UINT32                                                 reserved4320;	//0xC4D0465C
	UINT32                                                 reserved4321;	//0xC4D04660
	UINT32                                                 reserved4322;	//0xC4D04664
	UINT32                                                 reserved4323;	//0xC4D04668
	UINT32                                                 reserved4324;	//0xC4D0466C
	UINT32                                                 reserved4325;	//0xC4D04670
	UINT32                                                 reserved4326;	//0xC4D04674
	UINT32                                                 reserved4327;	//0xC4D04678
	UINT32                                                 reserved4328;	//0xC4D0467C
	UINT32                                                 reserved4329;	//0xC4D04680
	UINT32                                                 reserved4330;	//0xC4D04684
	UINT32                                                 reserved4331;	//0xC4D04688
	UINT32                                                 reserved4332;	//0xC4D0468C
	UINT32                                                 reserved4333;	//0xC4D04690
	UINT32                                                 reserved4334;	//0xC4D04694
	UINT32                                                 reserved4335;	//0xC4D04698
	UINT32                                                 reserved4336;	//0xC4D0469C
	UINT32                                                 reserved4337;	//0xC4D046A0
	UINT32                                                 reserved4338;	//0xC4D046A4
	UINT32                                                 reserved4339;	//0xC4D046A8
	UINT32                                                 reserved4340;	//0xC4D046AC
	UINT32                                                 reserved4341;	//0xC4D046B0
	UINT32                                                 reserved4342;	//0xC4D046B4
	UINT32                                                 reserved4343;	//0xC4D046B8
	UINT32                                                 reserved4344;	//0xC4D046BC
	UINT32                                                 reserved4345;	//0xC4D046C0
	UINT32                                                 reserved4346;	//0xC4D046C4
	UINT32                                                 reserved4347;	//0xC4D046C8
	UINT32                                                 reserved4348;	//0xC4D046CC
	UINT32                                                 reserved4349;	//0xC4D046D0
	UINT32                                                 reserved4350;	//0xC4D046D4
	UINT32                                                 reserved4351;	//0xC4D046D8
	UINT32                                                 reserved4352;	//0xC4D046DC
	UINT32                                                 reserved4353;	//0xC4D046E0
	UINT32                                                 reserved4354;	//0xC4D046E4
	UINT32                                                 reserved4355;	//0xC4D046E8
	UINT32                                                 reserved4356;	//0xC4D046EC
	UINT32                                                 reserved4357;	//0xC4D046F0
	UINT32                                                 reserved4358;	//0xC4D046F4
	UINT32                                                 reserved4359;	//0xC4D046F8
	UINT32                                                 reserved4360;	//0xC4D046FC
	UINT32                                                 reserved4361;	//0xC4D04700
	UINT32                                                 reserved4362;	//0xC4D04704
	UINT32                                                 reserved4363;	//0xC4D04708
	UINT32                                                 reserved4364;	//0xC4D0470C
	UINT32                                                 reserved4365;	//0xC4D04710
	UINT32                                                 reserved4366;	//0xC4D04714
	UINT32                                                 reserved4367;	//0xC4D04718
	UINT32                                                 reserved4368;	//0xC4D0471C
	UINT32                                                 reserved4369;	//0xC4D04720
	UINT32                                                 reserved4370;	//0xC4D04724
	UINT32                                                 reserved4371;	//0xC4D04728
	UINT32                                                 reserved4372;	//0xC4D0472C
	UINT32                                                 reserved4373;	//0xC4D04730
	UINT32                                                 reserved4374;	//0xC4D04734
	UINT32                                                 reserved4375;	//0xC4D04738
	UINT32                                                 reserved4376;	//0xC4D0473C
	UINT32                                                 reserved4377;	//0xC4D04740
	UINT32                                                 reserved4378;	//0xC4D04744
	UINT32                                                 reserved4379;	//0xC4D04748
	UINT32                                                 reserved4380;	//0xC4D0474C
	UINT32                                                 reserved4381;	//0xC4D04750
	UINT32                                                 reserved4382;	//0xC4D04754
	UINT32                                                 reserved4383;	//0xC4D04758
	UINT32                                                 reserved4384;	//0xC4D0475C
	UINT32                                                 reserved4385;	//0xC4D04760
	UINT32                                                 reserved4386;	//0xC4D04764
	UINT32                                                 reserved4387;	//0xC4D04768
	UINT32                                                 reserved4388;	//0xC4D0476C
	UINT32                                                 reserved4389;	//0xC4D04770
	UINT32                                                 reserved4390;	//0xC4D04774
	UINT32                                                 reserved4391;	//0xC4D04778
	UINT32                                                 reserved4392;	//0xC4D0477C
	UINT32                                                 reserved4393;	//0xC4D04780
	UINT32                                                 reserved4394;	//0xC4D04784
	UINT32                                                 reserved4395;	//0xC4D04788
	UINT32                                                 reserved4396;	//0xC4D0478C
	UINT32                                                 reserved4397;	//0xC4D04790
	UINT32                                                 reserved4398;	//0xC4D04794
	UINT32                                                 reserved4399;	//0xC4D04798
	UINT32                                                 reserved4400;	//0xC4D0479C
	UINT32                                                 reserved4401;	//0xC4D047A0
	UINT32                                                 reserved4402;	//0xC4D047A4
	UINT32                                                 reserved4403;	//0xC4D047A8
	UINT32                                                 reserved4404;	//0xC4D047AC
	UINT32                                                 reserved4405;	//0xC4D047B0
	UINT32                                                 reserved4406;	//0xC4D047B4
	UINT32                                                 reserved4407;	//0xC4D047B8
	UINT32                                                 reserved4408;	//0xC4D047BC
	UINT32                                                 reserved4409;	//0xC4D047C0
	UINT32                                                 reserved4410;	//0xC4D047C4
	UINT32                                                 reserved4411;	//0xC4D047C8
	UINT32                                                 reserved4412;	//0xC4D047CC
	UINT32                                                 reserved4413;	//0xC4D047D0
	UINT32                                                 reserved4414;	//0xC4D047D4
	UINT32                                                 reserved4415;	//0xC4D047D8
	UINT32                                                 reserved4416;	//0xC4D047DC
	UINT32                                                 reserved4417;	//0xC4D047E0
	UINT32                                                 reserved4418;	//0xC4D047E4
	UINT32                                                 reserved4419;	//0xC4D047E8
	UINT32                                                 reserved4420;	//0xC4D047EC
	UINT32                                                 reserved4421;	//0xC4D047F0
	UINT32                                                 reserved4422;	//0xC4D047F4
	UINT32                                                 reserved4423;	//0xC4D047F8
	UINT32                                                 reserved4424;	//0xC4D047FC
	UINT32                                                 reserved4425;	//0xC4D04800
	UINT32                                                 reserved4426;	//0xC4D04804
	UINT32                                                 reserved4427;	//0xC4D04808
	UINT32                                                 reserved4428;	//0xC4D0480C
	UINT32                                                 reserved4429;	//0xC4D04810
	UINT32                                                 reserved4430;	//0xC4D04814
	UINT32                                                 reserved4431;	//0xC4D04818
	UINT32                                                 reserved4432;	//0xC4D0481C
	UINT32                                                 reserved4433;	//0xC4D04820
	UINT32                                                 reserved4434;	//0xC4D04824
	UINT32                                                 reserved4435;	//0xC4D04828
	UINT32                                                 reserved4436;	//0xC4D0482C
	UINT32                                                 reserved4437;	//0xC4D04830
	UINT32                                                 reserved4438;	//0xC4D04834
	UINT32                                                 reserved4439;	//0xC4D04838
	UINT32                                                 reserved4440;	//0xC4D0483C
	UINT32                                                 reserved4441;	//0xC4D04840
	UINT32                                                 reserved4442;	//0xC4D04844
	UINT32                                                 reserved4443;	//0xC4D04848
	UINT32                                                 reserved4444;	//0xC4D0484C
	UINT32                                                 reserved4445;	//0xC4D04850
	UINT32                                                 reserved4446;	//0xC4D04854
	UINT32                                                 reserved4447;	//0xC4D04858
	UINT32                                                 reserved4448;	//0xC4D0485C
	UINT32                                                 reserved4449;	//0xC4D04860
	UINT32                                                 reserved4450;	//0xC4D04864
	UINT32                                                 reserved4451;	//0xC4D04868
	UINT32                                                 reserved4452;	//0xC4D0486C
	UINT32                                                 reserved4453;	//0xC4D04870
	UINT32                                                 reserved4454;	//0xC4D04874
	UINT32                                                 reserved4455;	//0xC4D04878
	UINT32                                                 reserved4456;	//0xC4D0487C
	UINT32                                                 reserved4457;	//0xC4D04880
	UINT32                                                 reserved4458;	//0xC4D04884
	UINT32                                                 reserved4459;	//0xC4D04888
	UINT32                                                 reserved4460;	//0xC4D0488C
	UINT32                                                 reserved4461;	//0xC4D04890
	UINT32                                                 reserved4462;	//0xC4D04894
	UINT32                                                 reserved4463;	//0xC4D04898
	UINT32                                                 reserved4464;	//0xC4D0489C
	UINT32                                                 reserved4465;	//0xC4D048A0
	UINT32                                                 reserved4466;	//0xC4D048A4
	UINT32                                                 reserved4467;	//0xC4D048A8
	UINT32                                                 reserved4468;	//0xC4D048AC
	UINT32                                                 reserved4469;	//0xC4D048B0
	UINT32                                                 reserved4470;	//0xC4D048B4
	UINT32                                                 reserved4471;	//0xC4D048B8
	UINT32                                                 reserved4472;	//0xC4D048BC
	UINT32                                                 reserved4473;	//0xC4D048C0
	UINT32                                                 reserved4474;	//0xC4D048C4
	UINT32                                                 reserved4475;	//0xC4D048C8
	UINT32                                                 reserved4476;	//0xC4D048CC
	UINT32                                                 reserved4477;	//0xC4D048D0
	UINT32                                                 reserved4478;	//0xC4D048D4
	UINT32                                                 reserved4479;	//0xC4D048D8
	UINT32                                                 reserved4480;	//0xC4D048DC
	UINT32                                                 reserved4481;	//0xC4D048E0
	UINT32                                                 reserved4482;	//0xC4D048E4
	UINT32                                                 reserved4483;	//0xC4D048E8
	UINT32                                                 reserved4484;	//0xC4D048EC
	UINT32                                                 reserved4485;	//0xC4D048F0
	UINT32                                                 reserved4486;	//0xC4D048F4
	UINT32                                                 reserved4487;	//0xC4D048F8
	UINT32                                                 reserved4488;	//0xC4D048FC
	UINT32                                                 reserved4489;	//0xC4D04900
	UINT32                                                 reserved4490;	//0xC4D04904
	UINT32                                                 reserved4491;	//0xC4D04908
	UINT32                                                 reserved4492;	//0xC4D0490C
	UINT32                                                 reserved4493;	//0xC4D04910
	UINT32                                                 reserved4494;	//0xC4D04914
	UINT32                                                 reserved4495;	//0xC4D04918
	UINT32                                                 reserved4496;	//0xC4D0491C
	UINT32                                                 reserved4497;	//0xC4D04920
	UINT32                                                 reserved4498;	//0xC4D04924
	UINT32                                                 reserved4499;	//0xC4D04928
	UINT32                                                 reserved4500;	//0xC4D0492C
	UINT32                                                 reserved4501;	//0xC4D04930
	UINT32                                                 reserved4502;	//0xC4D04934
	UINT32                                                 reserved4503;	//0xC4D04938
	UINT32                                                 reserved4504;	//0xC4D0493C
	UINT32                                                 reserved4505;	//0xC4D04940
	UINT32                                                 reserved4506;	//0xC4D04944
	UINT32                                                 reserved4507;	//0xC4D04948
	UINT32                                                 reserved4508;	//0xC4D0494C
	UINT32                                                 reserved4509;	//0xC4D04950
	UINT32                                                 reserved4510;	//0xC4D04954
	UINT32                                                 reserved4511;	//0xC4D04958
	UINT32                                                 reserved4512;	//0xC4D0495C
	UINT32                                                 reserved4513;	//0xC4D04960
	UINT32                                                 reserved4514;	//0xC4D04964
	UINT32                                                 reserved4515;	//0xC4D04968
	UINT32                                                 reserved4516;	//0xC4D0496C
	UINT32                                                 reserved4517;	//0xC4D04970
	UINT32                                                 reserved4518;	//0xC4D04974
	UINT32                                                 reserved4519;	//0xC4D04978
	UINT32                                                 reserved4520;	//0xC4D0497C
	UINT32                                                 reserved4521;	//0xC4D04980
	UINT32                                                 reserved4522;	//0xC4D04984
	UINT32                                                 reserved4523;	//0xC4D04988
	UINT32                                                 reserved4524;	//0xC4D0498C
	UINT32                                                 reserved4525;	//0xC4D04990
	UINT32                                                 reserved4526;	//0xC4D04994
	UINT32                                                 reserved4527;	//0xC4D04998
	UINT32                                                 reserved4528;	//0xC4D0499C
	UINT32                                                 reserved4529;	//0xC4D049A0
	UINT32                                                 reserved4530;	//0xC4D049A4
	UINT32                                                 reserved4531;	//0xC4D049A8
	UINT32                                                 reserved4532;	//0xC4D049AC
	UINT32                                                 reserved4533;	//0xC4D049B0
	UINT32                                                 reserved4534;	//0xC4D049B4
	UINT32                                                 reserved4535;	//0xC4D049B8
	UINT32                                                 reserved4536;	//0xC4D049BC
	UINT32                                                 reserved4537;	//0xC4D049C0
	UINT32                                                 reserved4538;	//0xC4D049C4
	UINT32                                                 reserved4539;	//0xC4D049C8
	UINT32                                                 reserved4540;	//0xC4D049CC
	UINT32                                                 reserved4541;	//0xC4D049D0
	UINT32                                                 reserved4542;	//0xC4D049D4
	UINT32                                                 reserved4543;	//0xC4D049D8
	UINT32                                                 reserved4544;	//0xC4D049DC
	UINT32                                                 reserved4545;	//0xC4D049E0
	UINT32                                                 reserved4546;	//0xC4D049E4
	UINT32                                                 reserved4547;	//0xC4D049E8
	UINT32                                                 reserved4548;	//0xC4D049EC
	UINT32                                                 reserved4549;	//0xC4D049F0
	UINT32                                                 reserved4550;	//0xC4D049F4
	UINT32                                                 reserved4551;	//0xC4D049F8
	UINT32                                                 reserved4552;	//0xC4D049FC
	UINT32                                                 reserved4553;	//0xC4D04A00
	UINT32                                                 reserved4554;	//0xC4D04A04
	UINT32                                                 reserved4555;	//0xC4D04A08
	UINT32                                                 reserved4556;	//0xC4D04A0C
	UINT32                                                 reserved4557;	//0xC4D04A10
	UINT32                                                 reserved4558;	//0xC4D04A14
	UINT32                                                 reserved4559;	//0xC4D04A18
	UINT32                                                 reserved4560;	//0xC4D04A1C
	UINT32                                                 reserved4561;	//0xC4D04A20
	UINT32                                                 reserved4562;	//0xC4D04A24
	UINT32                                                 reserved4563;	//0xC4D04A28
	UINT32                                                 reserved4564;	//0xC4D04A2C
	UINT32                                                 reserved4565;	//0xC4D04A30
	UINT32                                                 reserved4566;	//0xC4D04A34
	UINT32                                                 reserved4567;	//0xC4D04A38
	UINT32                                                 reserved4568;	//0xC4D04A3C
	UINT32                                                 reserved4569;	//0xC4D04A40
	UINT32                                                 reserved4570;	//0xC4D04A44
	UINT32                                                 reserved4571;	//0xC4D04A48
	UINT32                                                 reserved4572;	//0xC4D04A4C
	UINT32                                                 reserved4573;	//0xC4D04A50
	UINT32                                                 reserved4574;	//0xC4D04A54
	UINT32                                                 reserved4575;	//0xC4D04A58
	UINT32                                                 reserved4576;	//0xC4D04A5C
	UINT32                                                 reserved4577;	//0xC4D04A60
	UINT32                                                 reserved4578;	//0xC4D04A64
	UINT32                                                 reserved4579;	//0xC4D04A68
	UINT32                                                 reserved4580;	//0xC4D04A6C
	UINT32                                                 reserved4581;	//0xC4D04A70
	UINT32                                                 reserved4582;	//0xC4D04A74
	UINT32                                                 reserved4583;	//0xC4D04A78
	UINT32                                                 reserved4584;	//0xC4D04A7C
	UINT32                                                 reserved4585;	//0xC4D04A80
	UINT32                                                 reserved4586;	//0xC4D04A84
	UINT32                                                 reserved4587;	//0xC4D04A88
	UINT32                                                 reserved4588;	//0xC4D04A8C
	UINT32                                                 reserved4589;	//0xC4D04A90
	UINT32                                                 reserved4590;	//0xC4D04A94
	UINT32                                                 reserved4591;	//0xC4D04A98
	UINT32                                                 reserved4592;	//0xC4D04A9C
	UINT32                                                 reserved4593;	//0xC4D04AA0
	UINT32                                                 reserved4594;	//0xC4D04AA4
	UINT32                                                 reserved4595;	//0xC4D04AA8
	UINT32                                                 reserved4596;	//0xC4D04AAC
	UINT32                                                 reserved4597;	//0xC4D04AB0
	UINT32                                                 reserved4598;	//0xC4D04AB4
	UINT32                                                 reserved4599;	//0xC4D04AB8
	UINT32                                                 reserved4600;	//0xC4D04ABC
	UINT32                                                 reserved4601;	//0xC4D04AC0
	UINT32                                                 reserved4602;	//0xC4D04AC4
	UINT32                                                 reserved4603;	//0xC4D04AC8
	UINT32                                                 reserved4604;	//0xC4D04ACC
	UINT32                                                 reserved4605;	//0xC4D04AD0
	UINT32                                                 reserved4606;	//0xC4D04AD4
	UINT32                                                 reserved4607;	//0xC4D04AD8
	UINT32                                                 reserved4608;	//0xC4D04ADC
	UINT32                                                 reserved4609;	//0xC4D04AE0
	UINT32                                                 reserved4610;	//0xC4D04AE4
	UINT32                                                 reserved4611;	//0xC4D04AE8
	UINT32                                                 reserved4612;	//0xC4D04AEC
	UINT32                                                 reserved4613;	//0xC4D04AF0
	UINT32                                                 reserved4614;	//0xC4D04AF4
	UINT32                                                 reserved4615;	//0xC4D04AF8
	UINT32                                                 reserved4616;	//0xC4D04AFC
	UINT32                                                 reserved4617;	//0xC4D04B00
	UINT32                                                 reserved4618;	//0xC4D04B04
	UINT32                                                 reserved4619;	//0xC4D04B08
	UINT32                                                 reserved4620;	//0xC4D04B0C
	UINT32                                                 reserved4621;	//0xC4D04B10
	UINT32                                                 reserved4622;	//0xC4D04B14
	UINT32                                                 reserved4623;	//0xC4D04B18
	UINT32                                                 reserved4624;	//0xC4D04B1C
	UINT32                                                 reserved4625;	//0xC4D04B20
	UINT32                                                 reserved4626;	//0xC4D04B24
	UINT32                                                 reserved4627;	//0xC4D04B28
	UINT32                                                 reserved4628;	//0xC4D04B2C
	UINT32                                                 reserved4629;	//0xC4D04B30
	UINT32                                                 reserved4630;	//0xC4D04B34
	UINT32                                                 reserved4631;	//0xC4D04B38
	UINT32                                                 reserved4632;	//0xC4D04B3C
	UINT32                                                 reserved4633;	//0xC4D04B40
	UINT32                                                 reserved4634;	//0xC4D04B44
	UINT32                                                 reserved4635;	//0xC4D04B48
	UINT32                                                 reserved4636;	//0xC4D04B4C
	UINT32                                                 reserved4637;	//0xC4D04B50
	UINT32                                                 reserved4638;	//0xC4D04B54
	UINT32                                                 reserved4639;	//0xC4D04B58
	UINT32                                                 reserved4640;	//0xC4D04B5C
	UINT32                                                 reserved4641;	//0xC4D04B60
	UINT32                                                 reserved4642;	//0xC4D04B64
	UINT32                                                 reserved4643;	//0xC4D04B68
	UINT32                                                 reserved4644;	//0xC4D04B6C
	UINT32                                                 reserved4645;	//0xC4D04B70
	UINT32                                                 reserved4646;	//0xC4D04B74
	UINT32                                                 reserved4647;	//0xC4D04B78
	UINT32                                                 reserved4648;	//0xC4D04B7C
	UINT32                                                 reserved4649;	//0xC4D04B80
	UINT32                                                 reserved4650;	//0xC4D04B84
	UINT32                                                 reserved4651;	//0xC4D04B88
	UINT32                                                 reserved4652;	//0xC4D04B8C
	UINT32                                                 reserved4653;	//0xC4D04B90
	UINT32                                                 reserved4654;	//0xC4D04B94
	UINT32                                                 reserved4655;	//0xC4D04B98
	UINT32                                                 reserved4656;	//0xC4D04B9C
	UINT32                                                 reserved4657;	//0xC4D04BA0
	UINT32                                                 reserved4658;	//0xC4D04BA4
	UINT32                                                 reserved4659;	//0xC4D04BA8
	UINT32                                                 reserved4660;	//0xC4D04BAC
	UINT32                                                 reserved4661;	//0xC4D04BB0
	UINT32                                                 reserved4662;	//0xC4D04BB4
	UINT32                                                 reserved4663;	//0xC4D04BB8
	UINT32                                                 reserved4664;	//0xC4D04BBC
	UINT32                                                 reserved4665;	//0xC4D04BC0
	UINT32                                                 reserved4666;	//0xC4D04BC4
	UINT32                                                 reserved4667;	//0xC4D04BC8
	UINT32                                                 reserved4668;	//0xC4D04BCC
	UINT32                                                 reserved4669;	//0xC4D04BD0
	UINT32                                                 reserved4670;	//0xC4D04BD4
	UINT32                                                 reserved4671;	//0xC4D04BD8
	UINT32                                                 reserved4672;	//0xC4D04BDC
	UINT32                                                 reserved4673;	//0xC4D04BE0
	UINT32                                                 reserved4674;	//0xC4D04BE4
	UINT32                                                 reserved4675;	//0xC4D04BE8
	UINT32                                                 reserved4676;	//0xC4D04BEC
	UINT32                                                 reserved4677;	//0xC4D04BF0
	UINT32                                                 reserved4678;	//0xC4D04BF4
	UINT32                                                 reserved4679;	//0xC4D04BF8
	UINT32                                                 reserved4680;	//0xC4D04BFC
	UINT32                                                 reserved4681;	//0xC4D04C00
	UINT32                                                 reserved4682;	//0xC4D04C04
	UINT32                                                 reserved4683;	//0xC4D04C08
	UINT32                                                 reserved4684;	//0xC4D04C0C
	UINT32                                                 reserved4685;	//0xC4D04C10
	UINT32                                                 reserved4686;	//0xC4D04C14
	UINT32                                                 reserved4687;	//0xC4D04C18
	UINT32                                                 reserved4688;	//0xC4D04C1C
	UINT32                                                 reserved4689;	//0xC4D04C20
	UINT32                                                 reserved4690;	//0xC4D04C24
	UINT32                                                 reserved4691;	//0xC4D04C28
	UINT32                                                 reserved4692;	//0xC4D04C2C
	UINT32                                                 reserved4693;	//0xC4D04C30
	UINT32                                                 reserved4694;	//0xC4D04C34
	UINT32                                                 reserved4695;	//0xC4D04C38
	UINT32                                                 reserved4696;	//0xC4D04C3C
	UINT32                                                 reserved4697;	//0xC4D04C40
	UINT32                                                 reserved4698;	//0xC4D04C44
	UINT32                                                 reserved4699;	//0xC4D04C48
	UINT32                                                 reserved4700;	//0xC4D04C4C
	UINT32                                                 reserved4701;	//0xC4D04C50
	UINT32                                                 reserved4702;	//0xC4D04C54
	UINT32                                                 reserved4703;	//0xC4D04C58
	UINT32                                                 reserved4704;	//0xC4D04C5C
	UINT32                                                 reserved4705;	//0xC4D04C60
	UINT32                                                 reserved4706;	//0xC4D04C64
	UINT32                                                 reserved4707;	//0xC4D04C68
	UINT32                                                 reserved4708;	//0xC4D04C6C
	UINT32                                                 reserved4709;	//0xC4D04C70
	UINT32                                                 reserved4710;	//0xC4D04C74
	UINT32                                                 reserved4711;	//0xC4D04C78
	UINT32                                                 reserved4712;	//0xC4D04C7C
	UINT32                                                 reserved4713;	//0xC4D04C80
	UINT32                                                 reserved4714;	//0xC4D04C84
	UINT32                                                 reserved4715;	//0xC4D04C88
	UINT32                                                 reserved4716;	//0xC4D04C8C
	UINT32                                                 reserved4717;	//0xC4D04C90
	UINT32                                                 reserved4718;	//0xC4D04C94
	UINT32                                                 reserved4719;	//0xC4D04C98
	UINT32                                                 reserved4720;	//0xC4D04C9C
	UINT32                                                 reserved4721;	//0xC4D04CA0
	UINT32                                                 reserved4722;	//0xC4D04CA4
	UINT32                                                 reserved4723;	//0xC4D04CA8
	UINT32                                                 reserved4724;	//0xC4D04CAC
	UINT32                                                 reserved4725;	//0xC4D04CB0
	UINT32                                                 reserved4726;	//0xC4D04CB4
	UINT32                                                 reserved4727;	//0xC4D04CB8
	UINT32                                                 reserved4728;	//0xC4D04CBC
	UINT32                                                 reserved4729;	//0xC4D04CC0
	UINT32                                                 reserved4730;	//0xC4D04CC4
	UINT32                                                 reserved4731;	//0xC4D04CC8
	UINT32                                                 reserved4732;	//0xC4D04CCC
	UINT32                                                 reserved4733;	//0xC4D04CD0
	UINT32                                                 reserved4734;	//0xC4D04CD4
	UINT32                                                 reserved4735;	//0xC4D04CD8
	UINT32                                                 reserved4736;	//0xC4D04CDC
	UINT32                                                 reserved4737;	//0xC4D04CE0
	UINT32                                                 reserved4738;	//0xC4D04CE4
	UINT32                                                 reserved4739;	//0xC4D04CE8
	UINT32                                                 reserved4740;	//0xC4D04CEC
	UINT32                                                 reserved4741;	//0xC4D04CF0
	UINT32                                                 reserved4742;	//0xC4D04CF4
	UINT32                                                 reserved4743;	//0xC4D04CF8
	UINT32                                                 reserved4744;	//0xC4D04CFC
	UINT32                                                 reserved4745;	//0xC4D04D00
	UINT32                                                 reserved4746;	//0xC4D04D04
	UINT32                                                 reserved4747;	//0xC4D04D08
	UINT32                                                 reserved4748;	//0xC4D04D0C
	UINT32                                                 reserved4749;	//0xC4D04D10
	UINT32                                                 reserved4750;	//0xC4D04D14
	UINT32                                                 reserved4751;	//0xC4D04D18
	UINT32                                                 reserved4752;	//0xC4D04D1C
	UINT32                                                 reserved4753;	//0xC4D04D20
	UINT32                                                 reserved4754;	//0xC4D04D24
	UINT32                                                 reserved4755;	//0xC4D04D28
	UINT32                                                 reserved4756;	//0xC4D04D2C
	UINT32                                                 reserved4757;	//0xC4D04D30
	UINT32                                                 reserved4758;	//0xC4D04D34
	UINT32                                                 reserved4759;	//0xC4D04D38
	UINT32                                                 reserved4760;	//0xC4D04D3C
	UINT32                                                 reserved4761;	//0xC4D04D40
	UINT32                                                 reserved4762;	//0xC4D04D44
	UINT32                                                 reserved4763;	//0xC4D04D48
	UINT32                                                 reserved4764;	//0xC4D04D4C
	UINT32                                                 reserved4765;	//0xC4D04D50
	UINT32                                                 reserved4766;	//0xC4D04D54
	UINT32                                                 reserved4767;	//0xC4D04D58
	UINT32                                                 reserved4768;	//0xC4D04D5C
	UINT32                                                 reserved4769;	//0xC4D04D60
	UINT32                                                 reserved4770;	//0xC4D04D64
	UINT32                                                 reserved4771;	//0xC4D04D68
	UINT32                                                 reserved4772;	//0xC4D04D6C
	UINT32                                                 reserved4773;	//0xC4D04D70
	UINT32                                                 reserved4774;	//0xC4D04D74
	UINT32                                                 reserved4775;	//0xC4D04D78
	UINT32                                                 reserved4776;	//0xC4D04D7C
	UINT32                                                 reserved4777;	//0xC4D04D80
	UINT32                                                 reserved4778;	//0xC4D04D84
	UINT32                                                 reserved4779;	//0xC4D04D88
	UINT32                                                 reserved4780;	//0xC4D04D8C
	UINT32                                                 reserved4781;	//0xC4D04D90
	UINT32                                                 reserved4782;	//0xC4D04D94
	UINT32                                                 reserved4783;	//0xC4D04D98
	UINT32                                                 reserved4784;	//0xC4D04D9C
	UINT32                                                 reserved4785;	//0xC4D04DA0
	UINT32                                                 reserved4786;	//0xC4D04DA4
	UINT32                                                 reserved4787;	//0xC4D04DA8
	UINT32                                                 reserved4788;	//0xC4D04DAC
	UINT32                                                 reserved4789;	//0xC4D04DB0
	UINT32                                                 reserved4790;	//0xC4D04DB4
	UINT32                                                 reserved4791;	//0xC4D04DB8
	UINT32                                                 reserved4792;	//0xC4D04DBC
	UINT32                                                 reserved4793;	//0xC4D04DC0
	UINT32                                                 reserved4794;	//0xC4D04DC4
	UINT32                                                 reserved4795;	//0xC4D04DC8
	UINT32                                                 reserved4796;	//0xC4D04DCC
	UINT32                                                 reserved4797;	//0xC4D04DD0
	UINT32                                                 reserved4798;	//0xC4D04DD4
	UINT32                                                 reserved4799;	//0xC4D04DD8
	UINT32                                                 reserved4800;	//0xC4D04DDC
	UINT32                                                 reserved4801;	//0xC4D04DE0
	UINT32                                                 reserved4802;	//0xC4D04DE4
	UINT32                                                 reserved4803;	//0xC4D04DE8
	UINT32                                                 reserved4804;	//0xC4D04DEC
	UINT32                                                 reserved4805;	//0xC4D04DF0
	UINT32                                                 reserved4806;	//0xC4D04DF4
	UINT32                                                 reserved4807;	//0xC4D04DF8
	UINT32                                                 reserved4808;	//0xC4D04DFC
	UINT32                                                 reserved4809;	//0xC4D04E00
	UINT32                                                 reserved4810;	//0xC4D04E04
	UINT32                                                 reserved4811;	//0xC4D04E08
	UINT32                                                 reserved4812;	//0xC4D04E0C
	UINT32                                                 reserved4813;	//0xC4D04E10
	UINT32                                                 reserved4814;	//0xC4D04E14
	UINT32                                                 reserved4815;	//0xC4D04E18
	UINT32                                                 reserved4816;	//0xC4D04E1C
	UINT32                                                 reserved4817;	//0xC4D04E20
	UINT32                                                 reserved4818;	//0xC4D04E24
	UINT32                                                 reserved4819;	//0xC4D04E28
	UINT32                                                 reserved4820;	//0xC4D04E2C
	UINT32                                                 reserved4821;	//0xC4D04E30
	UINT32                                                 reserved4822;	//0xC4D04E34
	UINT32                                                 reserved4823;	//0xC4D04E38
	UINT32                                                 reserved4824;	//0xC4D04E3C
	UINT32                                                 reserved4825;	//0xC4D04E40
	UINT32                                                 reserved4826;	//0xC4D04E44
	UINT32                                                 reserved4827;	//0xC4D04E48
	UINT32                                                 reserved4828;	//0xC4D04E4C
	UINT32                                                 reserved4829;	//0xC4D04E50
	UINT32                                                 reserved4830;	//0xC4D04E54
	UINT32                                                 reserved4831;	//0xC4D04E58
	UINT32                                                 reserved4832;	//0xC4D04E5C
	UINT32                                                 reserved4833;	//0xC4D04E60
	UINT32                                                 reserved4834;	//0xC4D04E64
	UINT32                                                 reserved4835;	//0xC4D04E68
	UINT32                                                 reserved4836;	//0xC4D04E6C
	UINT32                                                 reserved4837;	//0xC4D04E70
	UINT32                                                 reserved4838;	//0xC4D04E74
	UINT32                                                 reserved4839;	//0xC4D04E78
	UINT32                                                 reserved4840;	//0xC4D04E7C
	UINT32                                                 reserved4841;	//0xC4D04E80
	UINT32                                                 reserved4842;	//0xC4D04E84
	UINT32                                                 reserved4843;	//0xC4D04E88
	UINT32                                                 reserved4844;	//0xC4D04E8C
	UINT32                                                 reserved4845;	//0xC4D04E90
	UINT32                                                 reserved4846;	//0xC4D04E94
	UINT32                                                 reserved4847;	//0xC4D04E98
	UINT32                                                 reserved4848;	//0xC4D04E9C
	UINT32                                                 reserved4849;	//0xC4D04EA0
	UINT32                                                 reserved4850;	//0xC4D04EA4
	UINT32                                                 reserved4851;	//0xC4D04EA8
	UINT32                                                 reserved4852;	//0xC4D04EAC
	UINT32                                                 reserved4853;	//0xC4D04EB0
	UINT32                                                 reserved4854;	//0xC4D04EB4
	UINT32                                                 reserved4855;	//0xC4D04EB8
	UINT32                                                 reserved4856;	//0xC4D04EBC
	UINT32                                                 reserved4857;	//0xC4D04EC0
	UINT32                                                 reserved4858;	//0xC4D04EC4
	UINT32                                                 reserved4859;	//0xC4D04EC8
	UINT32                                                 reserved4860;	//0xC4D04ECC
	UINT32                                                 reserved4861;	//0xC4D04ED0
	UINT32                                                 reserved4862;	//0xC4D04ED4
	UINT32                                                 reserved4863;	//0xC4D04ED8
	UINT32                                                 reserved4864;	//0xC4D04EDC
	UINT32                                                 reserved4865;	//0xC4D04EE0
	UINT32                                                 reserved4866;	//0xC4D04EE4
	UINT32                                                 reserved4867;	//0xC4D04EE8
	UINT32                                                 reserved4868;	//0xC4D04EEC
	UINT32                                                 reserved4869;	//0xC4D04EF0
	UINT32                                                 reserved4870;	//0xC4D04EF4
	UINT32                                                 reserved4871;	//0xC4D04EF8
	UINT32                                                 reserved4872;	//0xC4D04EFC
	UINT32                                                 reserved4873;	//0xC4D04F00
	UINT32                                                 reserved4874;	//0xC4D04F04
	UINT32                                                 reserved4875;	//0xC4D04F08
	UINT32                                                 reserved4876;	//0xC4D04F0C
	UINT32                                                 reserved4877;	//0xC4D04F10
	UINT32                                                 reserved4878;	//0xC4D04F14
	UINT32                                                 reserved4879;	//0xC4D04F18
	UINT32                                                 reserved4880;	//0xC4D04F1C
	UINT32                                                 reserved4881;	//0xC4D04F20
	UINT32                                                 reserved4882;	//0xC4D04F24
	UINT32                                                 reserved4883;	//0xC4D04F28
	UINT32                                                 reserved4884;	//0xC4D04F2C
	UINT32                                                 reserved4885;	//0xC4D04F30
	UINT32                                                 reserved4886;	//0xC4D04F34
	UINT32                                                 reserved4887;	//0xC4D04F38
	UINT32                                                 reserved4888;	//0xC4D04F3C
	UINT32                                                 reserved4889;	//0xC4D04F40
	UINT32                                                 reserved4890;	//0xC4D04F44
	UINT32                                                 reserved4891;	//0xC4D04F48
	UINT32                                                 reserved4892;	//0xC4D04F4C
	UINT32                                                 reserved4893;	//0xC4D04F50
	UINT32                                                 reserved4894;	//0xC4D04F54
	UINT32                                                 reserved4895;	//0xC4D04F58
	UINT32                                                 reserved4896;	//0xC4D04F5C
	UINT32                                                 reserved4897;	//0xC4D04F60
	UINT32                                                 reserved4898;	//0xC4D04F64
	UINT32                                                 reserved4899;	//0xC4D04F68
	UINT32                                                 reserved4900;	//0xC4D04F6C
	UINT32                                                 reserved4901;	//0xC4D04F70
	UINT32                                                 reserved4902;	//0xC4D04F74
	UINT32                                                 reserved4903;	//0xC4D04F78
	UINT32                                                 reserved4904;	//0xC4D04F7C
	UINT32                                                 reserved4905;	//0xC4D04F80
	UINT32                                                 reserved4906;	//0xC4D04F84
	UINT32                                                 reserved4907;	//0xC4D04F88
	UINT32                                                 reserved4908;	//0xC4D04F8C
	UINT32                                                 reserved4909;	//0xC4D04F90
	UINT32                                                 reserved4910;	//0xC4D04F94
	UINT32                                                 reserved4911;	//0xC4D04F98
	UINT32                                                 reserved4912;	//0xC4D04F9C
	UINT32                                                 reserved4913;	//0xC4D04FA0
	UINT32                                                 reserved4914;	//0xC4D04FA4
	UINT32                                                 reserved4915;	//0xC4D04FA8
	UINT32                                                 reserved4916;	//0xC4D04FAC
	UINT32                                                 reserved4917;	//0xC4D04FB0
	UINT32                                                 reserved4918;	//0xC4D04FB4
	UINT32                                                 reserved4919;	//0xC4D04FB8
	UINT32                                                 reserved4920;	//0xC4D04FBC
	UINT32                                                 reserved4921;	//0xC4D04FC0
	UINT32                                                 reserved4922;	//0xC4D04FC4
	UINT32                                                 reserved4923;	//0xC4D04FC8
	UINT32                                                 reserved4924;	//0xC4D04FCC
	UINT32                                                 reserved4925;	//0xC4D04FD0
	UINT32                                                 reserved4926;	//0xC4D04FD4
	UINT32                                                 reserved4927;	//0xC4D04FD8
	UINT32                                                 reserved4928;	//0xC4D04FDC
	UINT32                                                 reserved4929;	//0xC4D04FE0
	UINT32                                                 reserved4930;	//0xC4D04FE4
	UINT32                                                 reserved4931;	//0xC4D04FE8
	UINT32                                                 reserved4932;	//0xC4D04FEC
	UINT32                                                 reserved4933;	//0xC4D04FF0
	UINT32                                                 reserved4934;	//0xC4D04FF4
	UINT32                                                 reserved4935;	//0xC4D04FF8
	UINT32                                                 reserved4936;	//0xC4D04FFC
	REG_DDRC_M0_DEBUG_COMMON_T                             debug_common;	//0xC4D05000
	REG_DDRC_M0_DEBUG_PERIOD_T                             debug_period;	//0xC4D05004
	UINT32                                                 reserved4937;	//0xC4D05008
	UINT32                                                 reserved4938;	//0xC4D0500C
	REG_DDRC_M0_IRQ_MASK_T                                     irq_mask;	//0xC4D05010
	REG_DDRC_M0_IRQ_STATUS_T                                 irq_status;	//0xC4D05014
	UINT32                                                 reserved4939;	//0xC4D05018
	UINT32                                                 reserved4940;	//0xC4D0501C
	UINT32                                                 reserved4941;	//0xC4D05020
	UINT32                                                 reserved4942;	//0xC4D05024
	UINT32                                                 reserved4943;	//0xC4D05028
	UINT32                                                 reserved4944;	//0xC4D0502C
	UINT32                                                 reserved4945;	//0xC4D05030
	UINT32                                                 reserved4946;	//0xC4D05034
	UINT32                                                 reserved4947;	//0xC4D05038
	UINT32                                                 reserved4948;	//0xC4D0503C
	UINT32                                                 reserved4949;	//0xC4D05040
	UINT32                                                 reserved4950;	//0xC4D05044
	UINT32                                                 reserved4951;	//0xC4D05048
	UINT32                                                 reserved4952;	//0xC4D0504C
	UINT32                                                 reserved4953;	//0xC4D05050
	UINT32                                                 reserved4954;	//0xC4D05054
	UINT32                                                 reserved4955;	//0xC4D05058
	UINT32                                                 reserved4956;	//0xC4D0505C
	UINT32                                                 reserved4957;	//0xC4D05060
	UINT32                                                 reserved4958;	//0xC4D05064
	UINT32                                                 reserved4959;	//0xC4D05068
	UINT32                                                 reserved4960;	//0xC4D0506C
	UINT32                                                 reserved4961;	//0xC4D05070
	UINT32                                                 reserved4962;	//0xC4D05074
	UINT32                                                 reserved4963;	//0xC4D05078
	UINT32                                                 reserved4964;	//0xC4D0507C
	UINT32                                                 reserved4965;	//0xC4D05080
	UINT32                                                 reserved4966;	//0xC4D05084
	UINT32                                                 reserved4967;	//0xC4D05088
	UINT32                                                 reserved4968;	//0xC4D0508C
	UINT32                                                 reserved4969;	//0xC4D05090
	UINT32                                                 reserved4970;	//0xC4D05094
	UINT32                                                 reserved4971;	//0xC4D05098
	UINT32                                                 reserved4972;	//0xC4D0509C
	UINT32                                                 reserved4973;	//0xC4D050A0
	UINT32                                                 reserved4974;	//0xC4D050A4
	UINT32                                                 reserved4975;	//0xC4D050A8
	UINT32                                                 reserved4976;	//0xC4D050AC
	UINT32                                                 reserved4977;	//0xC4D050B0
	UINT32                                                 reserved4978;	//0xC4D050B4
	UINT32                                                 reserved4979;	//0xC4D050B8
	UINT32                                                 reserved4980;	//0xC4D050BC
	UINT32                                                 reserved4981;	//0xC4D050C0
	UINT32                                                 reserved4982;	//0xC4D050C4
	UINT32                                                 reserved4983;	//0xC4D050C8
	UINT32                                                 reserved4984;	//0xC4D050CC
	UINT32                                                 reserved4985;	//0xC4D050D0
	UINT32                                                 reserved4986;	//0xC4D050D4
	UINT32                                                 reserved4987;	//0xC4D050D8
	UINT32                                                 reserved4988;	//0xC4D050DC
	UINT32                                                 reserved4989;	//0xC4D050E0
	UINT32                                                 reserved4990;	//0xC4D050E4
	UINT32                                                 reserved4991;	//0xC4D050E8
	UINT32                                                 reserved4992;	//0xC4D050EC
	UINT32                                                 reserved4993;	//0xC4D050F0
	UINT32                                                 reserved4994;	//0xC4D050F4
	UINT32                                                 reserved4995;	//0xC4D050F8
	UINT32                                                 reserved4996;	//0xC4D050FC
	REG_DDRC_M0_DEBUG_BUS_IF_T                             debug_bus_if;	//0xC4D05100
	UINT32                                                 reserved4997;	//0xC4D05104
	UINT32                                                 reserved4998;	//0xC4D05108
	UINT32                                                 reserved4999;	//0xC4D0510C
	UINT32                                                 reserved5000;	//0xC4D05110
	UINT32                                                 reserved5001;	//0xC4D05114
	UINT32                                                 reserved5002;	//0xC4D05118
	UINT32                                                 reserved5003;	//0xC4D0511C
	UINT32                                                 reserved5004;	//0xC4D05120
	UINT32                                                 reserved5005;	//0xC4D05124
	UINT32                                                 reserved5006;	//0xC4D05128
	UINT32                                                 reserved5007;	//0xC4D0512C
	UINT32                                                 reserved5008;	//0xC4D05130
	UINT32                                                 reserved5009;	//0xC4D05134
	UINT32                                                 reserved5010;	//0xC4D05138
	UINT32                                                 reserved5011;	//0xC4D0513C
	UINT32                                                 reserved5012;	//0xC4D05140
	UINT32                                                 reserved5013;	//0xC4D05144
	UINT32                                                 reserved5014;	//0xC4D05148
	UINT32                                                 reserved5015;	//0xC4D0514C
	UINT32                                                 reserved5016;	//0xC4D05150
	UINT32                                                 reserved5017;	//0xC4D05154
	UINT32                                                 reserved5018;	//0xC4D05158
	UINT32                                                 reserved5019;	//0xC4D0515C
	UINT32                                                 reserved5020;	//0xC4D05160
	UINT32                                                 reserved5021;	//0xC4D05164
	UINT32                                                 reserved5022;	//0xC4D05168
	UINT32                                                 reserved5023;	//0xC4D0516C
	UINT32                                                 reserved5024;	//0xC4D05170
	UINT32                                                 reserved5025;	//0xC4D05174
	UINT32                                                 reserved5026;	//0xC4D05178
	UINT32                                                 reserved5027;	//0xC4D0517C
	UINT32                                                 reserved5028;	//0xC4D05180
	UINT32                                                 reserved5029;	//0xC4D05184
	UINT32                                                 reserved5030;	//0xC4D05188
	UINT32                                                 reserved5031;	//0xC4D0518C
	UINT32                                                 reserved5032;	//0xC4D05190
	UINT32                                                 reserved5033;	//0xC4D05194
	UINT32                                                 reserved5034;	//0xC4D05198
	UINT32                                                 reserved5035;	//0xC4D0519C
	UINT32                                                 reserved5036;	//0xC4D051A0
	UINT32                                                 reserved5037;	//0xC4D051A4
	UINT32                                                 reserved5038;	//0xC4D051A8
	UINT32                                                 reserved5039;	//0xC4D051AC
	UINT32                                                 reserved5040;	//0xC4D051B0
	UINT32                                                 reserved5041;	//0xC4D051B4
	UINT32                                                 reserved5042;	//0xC4D051B8
	UINT32                                                 reserved5043;	//0xC4D051BC
	UINT32                                                 reserved5044;	//0xC4D051C0
	UINT32                                                 reserved5045;	//0xC4D051C4
	UINT32                                                 reserved5046;	//0xC4D051C8
	UINT32                                                 reserved5047;	//0xC4D051CC
	UINT32                                                 reserved5048;	//0xC4D051D0
	UINT32                                                 reserved5049;	//0xC4D051D4
	UINT32                                                 reserved5050;	//0xC4D051D8
	UINT32                                                 reserved5051;	//0xC4D051DC
	UINT32                                                 reserved5052;	//0xC4D051E0
	UINT32                                                 reserved5053;	//0xC4D051E4
	UINT32                                                 reserved5054;	//0xC4D051E8
	UINT32                                                 reserved5055;	//0xC4D051EC
	UINT32                                                 reserved5056;	//0xC4D051F0
	UINT32                                                 reserved5057;	//0xC4D051F4
	UINT32                                                 reserved5058;	//0xC4D051F8
	UINT32                                                 reserved5059;	//0xC4D051FC
	REG_DDRC_M0_DEBUG_PORT_IF_0_T                       debug_port_if_0;	//0xC4D05200
	REG_DDRC_M0_DEBUG_PORT_IF_1_T                       debug_port_if_1;	//0xC4D05204
	REG_DDRC_M0_DEBUG_PORT_IF_2_T                       debug_port_if_2;	//0xC4D05208
	REG_DDRC_M0_DEBUG_PORT_IF_3_T                       debug_port_if_3;	//0xC4D0520C
	REG_DDRC_M0_DEBUG_PORT_IF_4_T                       debug_port_if_4;	//0xC4D05210
	REG_DDRC_M0_DEBUG_PORT_IF_5_T                       debug_port_if_5;	//0xC4D05214
	REG_DDRC_M0_DEBUG_PORT_IF_6_T                       debug_port_if_6;	//0xC4D05218
	REG_DDRC_M0_DEBUG_PORT_IF_7_T                       debug_port_if_7;	//0xC4D0521C
	UINT32                                                 reserved5060;	//0xC4D05220
	UINT32                                                 reserved5061;	//0xC4D05224
	UINT32                                                 reserved5062;	//0xC4D05228
	UINT32                                                 reserved5063;	//0xC4D0522C
	UINT32                                                 reserved5064;	//0xC4D05230
	UINT32                                                 reserved5065;	//0xC4D05234
	UINT32                                                 reserved5066;	//0xC4D05238
	UINT32                                                 reserved5067;	//0xC4D0523C
	UINT32                                                 reserved5068;	//0xC4D05240
	UINT32                                                 reserved5069;	//0xC4D05244
	UINT32                                                 reserved5070;	//0xC4D05248
	UINT32                                                 reserved5071;	//0xC4D0524C
	UINT32                                                 reserved5072;	//0xC4D05250
	UINT32                                                 reserved5073;	//0xC4D05254
	UINT32                                                 reserved5074;	//0xC4D05258
	UINT32                                                 reserved5075;	//0xC4D0525C
	UINT32                                                 reserved5076;	//0xC4D05260
	UINT32                                                 reserved5077;	//0xC4D05264
	UINT32                                                 reserved5078;	//0xC4D05268
	UINT32                                                 reserved5079;	//0xC4D0526C
	UINT32                                                 reserved5080;	//0xC4D05270
	UINT32                                                 reserved5081;	//0xC4D05274
	UINT32                                                 reserved5082;	//0xC4D05278
	UINT32                                                 reserved5083;	//0xC4D0527C
	UINT32                                                 reserved5084;	//0xC4D05280
	UINT32                                                 reserved5085;	//0xC4D05284
	UINT32                                                 reserved5086;	//0xC4D05288
	UINT32                                                 reserved5087;	//0xC4D0528C
	UINT32                                                 reserved5088;	//0xC4D05290
	UINT32                                                 reserved5089;	//0xC4D05294
	UINT32                                                 reserved5090;	//0xC4D05298
	UINT32                                                 reserved5091;	//0xC4D0529C
	UINT32                                                 reserved5092;	//0xC4D052A0
	UINT32                                                 reserved5093;	//0xC4D052A4
	UINT32                                                 reserved5094;	//0xC4D052A8
	UINT32                                                 reserved5095;	//0xC4D052AC
	UINT32                                                 reserved5096;	//0xC4D052B0
	UINT32                                                 reserved5097;	//0xC4D052B4
	UINT32                                                 reserved5098;	//0xC4D052B8
	UINT32                                                 reserved5099;	//0xC4D052BC
	UINT32                                                 reserved5100;	//0xC4D052C0
	UINT32                                                 reserved5101;	//0xC4D052C4
	UINT32                                                 reserved5102;	//0xC4D052C8
	UINT32                                                 reserved5103;	//0xC4D052CC
	UINT32                                                 reserved5104;	//0xC4D052D0
	UINT32                                                 reserved5105;	//0xC4D052D4
	UINT32                                                 reserved5106;	//0xC4D052D8
	UINT32                                                 reserved5107;	//0xC4D052DC
	UINT32                                                 reserved5108;	//0xC4D052E0
	UINT32                                                 reserved5109;	//0xC4D052E4
	UINT32                                                 reserved5110;	//0xC4D052E8
	UINT32                                                 reserved5111;	//0xC4D052EC
	UINT32                                                 reserved5112;	//0xC4D052F0
	UINT32                                                 reserved5113;	//0xC4D052F4
	UINT32                                                 reserved5114;	//0xC4D052F8
	UINT32                                                 reserved5115;	//0xC4D052FC
	REG_DDRC_M0_DEBUG_UQ_1_T                                 debug_uq_1;	//0xC4D05300
	REG_DDRC_M0_DEBUG_UQ_2_T                                 debug_uq_2;	//0xC4D05304
	UINT32                                                 reserved5116;	//0xC4D05308
	UINT32                                                 reserved5117;	//0xC4D0530C
	UINT32                                                 reserved5118;	//0xC4D05310
	UINT32                                                 reserved5119;	//0xC4D05314
	UINT32                                                 reserved5120;	//0xC4D05318
	UINT32                                                 reserved5121;	//0xC4D0531C
	UINT32                                                 reserved5122;	//0xC4D05320
	UINT32                                                 reserved5123;	//0xC4D05324
	UINT32                                                 reserved5124;	//0xC4D05328
	UINT32                                                 reserved5125;	//0xC4D0532C
	UINT32                                                 reserved5126;	//0xC4D05330
	UINT32                                                 reserved5127;	//0xC4D05334
	UINT32                                                 reserved5128;	//0xC4D05338
	UINT32                                                 reserved5129;	//0xC4D0533C
	UINT32                                                 reserved5130;	//0xC4D05340
	UINT32                                                 reserved5131;	//0xC4D05344
	UINT32                                                 reserved5132;	//0xC4D05348
	UINT32                                                 reserved5133;	//0xC4D0534C
	UINT32                                                 reserved5134;	//0xC4D05350
	UINT32                                                 reserved5135;	//0xC4D05354
	UINT32                                                 reserved5136;	//0xC4D05358
	UINT32                                                 reserved5137;	//0xC4D0535C
	UINT32                                                 reserved5138;	//0xC4D05360
	UINT32                                                 reserved5139;	//0xC4D05364
	UINT32                                                 reserved5140;	//0xC4D05368
	UINT32                                                 reserved5141;	//0xC4D0536C
	UINT32                                                 reserved5142;	//0xC4D05370
	UINT32                                                 reserved5143;	//0xC4D05374
	UINT32                                                 reserved5144;	//0xC4D05378
	UINT32                                                 reserved5145;	//0xC4D0537C
	UINT32                                                 reserved5146;	//0xC4D05380
	UINT32                                                 reserved5147;	//0xC4D05384
	UINT32                                                 reserved5148;	//0xC4D05388
	UINT32                                                 reserved5149;	//0xC4D0538C
	UINT32                                                 reserved5150;	//0xC4D05390
	UINT32                                                 reserved5151;	//0xC4D05394
	UINT32                                                 reserved5152;	//0xC4D05398
	UINT32                                                 reserved5153;	//0xC4D0539C
	UINT32                                                 reserved5154;	//0xC4D053A0
	UINT32                                                 reserved5155;	//0xC4D053A4
	UINT32                                                 reserved5156;	//0xC4D053A8
	UINT32                                                 reserved5157;	//0xC4D053AC
	UINT32                                                 reserved5158;	//0xC4D053B0
	UINT32                                                 reserved5159;	//0xC4D053B4
	UINT32                                                 reserved5160;	//0xC4D053B8
	UINT32                                                 reserved5161;	//0xC4D053BC
	UINT32                                                 reserved5162;	//0xC4D053C0
	UINT32                                                 reserved5163;	//0xC4D053C4
	UINT32                                                 reserved5164;	//0xC4D053C8
	UINT32                                                 reserved5165;	//0xC4D053CC
	UINT32                                                 reserved5166;	//0xC4D053D0
	UINT32                                                 reserved5167;	//0xC4D053D4
	UINT32                                                 reserved5168;	//0xC4D053D8
	UINT32                                                 reserved5169;	//0xC4D053DC
	UINT32                                                 reserved5170;	//0xC4D053E0
	UINT32                                                 reserved5171;	//0xC4D053E4
	UINT32                                                 reserved5172;	//0xC4D053E8
	UINT32                                                 reserved5173;	//0xC4D053EC
	UINT32                                                 reserved5174;	//0xC4D053F0
	UINT32                                                 reserved5175;	//0xC4D053F4
	UINT32                                                 reserved5176;	//0xC4D053F8
	UINT32                                                 reserved5177;	//0xC4D053FC
	REG_DDRC_M0_DEBUG_SCH0_T                                 debug_sch0;	//0xC4D05400
	REG_DDRC_M0_DEBUG_SCH1_T                                 debug_sch1;	//0xC4D05404
	UINT32                                                 reserved5178;	//0xC4D05408
	UINT32                                                 reserved5179;	//0xC4D0540C
	UINT32                                                 reserved5180;	//0xC4D05410
	UINT32                                                 reserved5181;	//0xC4D05414
	UINT32                                                 reserved5182;	//0xC4D05418
	UINT32                                                 reserved5183;	//0xC4D0541C
	UINT32                                                 reserved5184;	//0xC4D05420
	UINT32                                                 reserved5185;	//0xC4D05424
	UINT32                                                 reserved5186;	//0xC4D05428
	UINT32                                                 reserved5187;	//0xC4D0542C
	UINT32                                                 reserved5188;	//0xC4D05430
	UINT32                                                 reserved5189;	//0xC4D05434
	UINT32                                                 reserved5190;	//0xC4D05438
	UINT32                                                 reserved5191;	//0xC4D0543C
	UINT32                                                 reserved5192;	//0xC4D05440
	UINT32                                                 reserved5193;	//0xC4D05444
	UINT32                                                 reserved5194;	//0xC4D05448
	UINT32                                                 reserved5195;	//0xC4D0544C
	UINT32                                                 reserved5196;	//0xC4D05450
	UINT32                                                 reserved5197;	//0xC4D05454
	UINT32                                                 reserved5198;	//0xC4D05458
	UINT32                                                 reserved5199;	//0xC4D0545C
	UINT32                                                 reserved5200;	//0xC4D05460
	UINT32                                                 reserved5201;	//0xC4D05464
	UINT32                                                 reserved5202;	//0xC4D05468
	UINT32                                                 reserved5203;	//0xC4D0546C
	UINT32                                                 reserved5204;	//0xC4D05470
	UINT32                                                 reserved5205;	//0xC4D05474
	UINT32                                                 reserved5206;	//0xC4D05478
	UINT32                                                 reserved5207;	//0xC4D0547C
	UINT32                                                 reserved5208;	//0xC4D05480
	UINT32                                                 reserved5209;	//0xC4D05484
	UINT32                                                 reserved5210;	//0xC4D05488
	UINT32                                                 reserved5211;	//0xC4D0548C
	UINT32                                                 reserved5212;	//0xC4D05490
	UINT32                                                 reserved5213;	//0xC4D05494
	UINT32                                                 reserved5214;	//0xC4D05498
	UINT32                                                 reserved5215;	//0xC4D0549C
	UINT32                                                 reserved5216;	//0xC4D054A0
	UINT32                                                 reserved5217;	//0xC4D054A4
	UINT32                                                 reserved5218;	//0xC4D054A8
	UINT32                                                 reserved5219;	//0xC4D054AC
	UINT32                                                 reserved5220;	//0xC4D054B0
	UINT32                                                 reserved5221;	//0xC4D054B4
	UINT32                                                 reserved5222;	//0xC4D054B8
	UINT32                                                 reserved5223;	//0xC4D054BC
	UINT32                                                 reserved5224;	//0xC4D054C0
	UINT32                                                 reserved5225;	//0xC4D054C4
	UINT32                                                 reserved5226;	//0xC4D054C8
	UINT32                                                 reserved5227;	//0xC4D054CC
	UINT32                                                 reserved5228;	//0xC4D054D0
	UINT32                                                 reserved5229;	//0xC4D054D4
	UINT32                                                 reserved5230;	//0xC4D054D8
	UINT32                                                 reserved5231;	//0xC4D054DC
	UINT32                                                 reserved5232;	//0xC4D054E0
	UINT32                                                 reserved5233;	//0xC4D054E4
	UINT32                                                 reserved5234;	//0xC4D054E8
	UINT32                                                 reserved5235;	//0xC4D054EC
	UINT32                                                 reserved5236;	//0xC4D054F0
	UINT32                                                 reserved5237;	//0xC4D054F4
	UINT32                                                 reserved5238;	//0xC4D054F8
	UINT32                                                 reserved5239;	//0xC4D054FC
	REG_DDRC_M0_DEBUG_ALP_T                                   debug_alp;	//0xC4D05500
	REG_DDRC_M0_DEBUG_ALP_ENTRY_NUM_T               debug_alp_entry_num;	//0xC4D05504
	REG_DDRC_M0_DEBUG_ALP_TIME_T                         debug_alp_time;	//0xC4D05508
	REG_DDRC_M0_DEBUG_ALP_WAIT_CNT_T                 debug_alp_wait_cnt;	//0xC4D0550C
	UINT32                                                 reserved5240;	//0xC4D05510
	UINT32                                                 reserved5241;	//0xC4D05514
	UINT32                                                 reserved5242;	//0xC4D05518
	UINT32                                                 reserved5243;	//0xC4D0551C
	UINT32                                                 reserved5244;	//0xC4D05520
	UINT32                                                 reserved5245;	//0xC4D05524
	UINT32                                                 reserved5246;	//0xC4D05528
	UINT32                                                 reserved5247;	//0xC4D0552C
	UINT32                                                 reserved5248;	//0xC4D05530
	UINT32                                                 reserved5249;	//0xC4D05534
	UINT32                                                 reserved5250;	//0xC4D05538
	UINT32                                                 reserved5251;	//0xC4D0553C
	UINT32                                                 reserved5252;	//0xC4D05540
	UINT32                                                 reserved5253;	//0xC4D05544
	UINT32                                                 reserved5254;	//0xC4D05548
	UINT32                                                 reserved5255;	//0xC4D0554C
	UINT32                                                 reserved5256;	//0xC4D05550
	UINT32                                                 reserved5257;	//0xC4D05554
	UINT32                                                 reserved5258;	//0xC4D05558
	UINT32                                                 reserved5259;	//0xC4D0555C
	UINT32                                                 reserved5260;	//0xC4D05560
	UINT32                                                 reserved5261;	//0xC4D05564
	UINT32                                                 reserved5262;	//0xC4D05568
	UINT32                                                 reserved5263;	//0xC4D0556C
	UINT32                                                 reserved5264;	//0xC4D05570
	UINT32                                                 reserved5265;	//0xC4D05574
	UINT32                                                 reserved5266;	//0xC4D05578
	UINT32                                                 reserved5267;	//0xC4D0557C
	UINT32                                                 reserved5268;	//0xC4D05580
	UINT32                                                 reserved5269;	//0xC4D05584
	UINT32                                                 reserved5270;	//0xC4D05588
	UINT32                                                 reserved5271;	//0xC4D0558C
	UINT32                                                 reserved5272;	//0xC4D05590
	UINT32                                                 reserved5273;	//0xC4D05594
	UINT32                                                 reserved5274;	//0xC4D05598
	UINT32                                                 reserved5275;	//0xC4D0559C
	UINT32                                                 reserved5276;	//0xC4D055A0
	UINT32                                                 reserved5277;	//0xC4D055A4
	UINT32                                                 reserved5278;	//0xC4D055A8
	UINT32                                                 reserved5279;	//0xC4D055AC
	UINT32                                                 reserved5280;	//0xC4D055B0
	UINT32                                                 reserved5281;	//0xC4D055B4
	UINT32                                                 reserved5282;	//0xC4D055B8
	UINT32                                                 reserved5283;	//0xC4D055BC
	UINT32                                                 reserved5284;	//0xC4D055C0
	UINT32                                                 reserved5285;	//0xC4D055C4
	UINT32                                                 reserved5286;	//0xC4D055C8
	UINT32                                                 reserved5287;	//0xC4D055CC
	UINT32                                                 reserved5288;	//0xC4D055D0
	UINT32                                                 reserved5289;	//0xC4D055D4
	UINT32                                                 reserved5290;	//0xC4D055D8
	UINT32                                                 reserved5291;	//0xC4D055DC
	UINT32                                                 reserved5292;	//0xC4D055E0
	UINT32                                                 reserved5293;	//0xC4D055E4
	UINT32                                                 reserved5294;	//0xC4D055E8
	UINT32                                                 reserved5295;	//0xC4D055EC
	UINT32                                                 reserved5296;	//0xC4D055F0
	UINT32                                                 reserved5297;	//0xC4D055F4
	UINT32                                                 reserved5298;	//0xC4D055F8
	UINT32                                                 reserved5299;	//0xC4D055FC
	REG_DDRC_M0_DEBUG_DFS_T                                   debug_dfs;	//0xC4D05600
	UINT32                                                 reserved5300;	//0xC4D05604
	UINT32                                                 reserved5301;	//0xC4D05608
	UINT32                                                 reserved5302;	//0xC4D0560C
	UINT32                                                 reserved5303;	//0xC4D05610
	UINT32                                                 reserved5304;	//0xC4D05614
	UINT32                                                 reserved5305;	//0xC4D05618
	UINT32                                                 reserved5306;	//0xC4D0561C
	UINT32                                                 reserved5307;	//0xC4D05620
	UINT32                                                 reserved5308;	//0xC4D05624
	UINT32                                                 reserved5309;	//0xC4D05628
	UINT32                                                 reserved5310;	//0xC4D0562C
	UINT32                                                 reserved5311;	//0xC4D05630
	UINT32                                                 reserved5312;	//0xC4D05634
	UINT32                                                 reserved5313;	//0xC4D05638
	UINT32                                                 reserved5314;	//0xC4D0563C
	UINT32                                                 reserved5315;	//0xC4D05640
	UINT32                                                 reserved5316;	//0xC4D05644
	UINT32                                                 reserved5317;	//0xC4D05648
	UINT32                                                 reserved5318;	//0xC4D0564C
	UINT32                                                 reserved5319;	//0xC4D05650
	UINT32                                                 reserved5320;	//0xC4D05654
	UINT32                                                 reserved5321;	//0xC4D05658
	UINT32                                                 reserved5322;	//0xC4D0565C
	UINT32                                                 reserved5323;	//0xC4D05660
	UINT32                                                 reserved5324;	//0xC4D05664
	UINT32                                                 reserved5325;	//0xC4D05668
	UINT32                                                 reserved5326;	//0xC4D0566C
	UINT32                                                 reserved5327;	//0xC4D05670
	UINT32                                                 reserved5328;	//0xC4D05674
	UINT32                                                 reserved5329;	//0xC4D05678
	UINT32                                                 reserved5330;	//0xC4D0567C
	UINT32                                                 reserved5331;	//0xC4D05680
	UINT32                                                 reserved5332;	//0xC4D05684
	UINT32                                                 reserved5333;	//0xC4D05688
	UINT32                                                 reserved5334;	//0xC4D0568C
	UINT32                                                 reserved5335;	//0xC4D05690
	UINT32                                                 reserved5336;	//0xC4D05694
	UINT32                                                 reserved5337;	//0xC4D05698
	UINT32                                                 reserved5338;	//0xC4D0569C
	UINT32                                                 reserved5339;	//0xC4D056A0
	UINT32                                                 reserved5340;	//0xC4D056A4
	UINT32                                                 reserved5341;	//0xC4D056A8
	UINT32                                                 reserved5342;	//0xC4D056AC
	UINT32                                                 reserved5343;	//0xC4D056B0
	UINT32                                                 reserved5344;	//0xC4D056B4
	UINT32                                                 reserved5345;	//0xC4D056B8
	UINT32                                                 reserved5346;	//0xC4D056BC
	UINT32                                                 reserved5347;	//0xC4D056C0
	UINT32                                                 reserved5348;	//0xC4D056C4
	UINT32                                                 reserved5349;	//0xC4D056C8
	UINT32                                                 reserved5350;	//0xC4D056CC
	UINT32                                                 reserved5351;	//0xC4D056D0
	UINT32                                                 reserved5352;	//0xC4D056D4
	UINT32                                                 reserved5353;	//0xC4D056D8
	UINT32                                                 reserved5354;	//0xC4D056DC
	UINT32                                                 reserved5355;	//0xC4D056E0
	UINT32                                                 reserved5356;	//0xC4D056E4
	UINT32                                                 reserved5357;	//0xC4D056E8
	UINT32                                                 reserved5358;	//0xC4D056EC
	UINT32                                                 reserved5359;	//0xC4D056F0
	UINT32                                                 reserved5360;	//0xC4D056F4
	UINT32                                                 reserved5361;	//0xC4D056F8
	UINT32                                                 reserved5362;	//0xC4D056FC
	REG_DDRC_M0_DEBUG_IDLE_CNT_T                         debug_idle_cnt;	//0xC4D05700
	REG_DDRC_M0_DEBUG_RD_CNT_T                             debug_rd_cnt;	//0xC4D05704
	REG_DDRC_M0_DEBUG_RDL_CNT_T                           debug_rdl_cnt;	//0xC4D05708
	UINT32                                                 reserved5363;	//0xC4D0570C
	REG_DDRC_M0_DEBUG_RWR_CNT_T                           debug_rwr_cnt;	//0xC4D05710
	REG_DDRC_M0_DEBUG_MWR_CNT_T                           debug_mwr_cnt;	//0xC4D05714
	REG_DDRC_M0_DEBUG_WRL_CNT_T                           debug_wrl_cnt;	//0xC4D05718
	UINT32                                                 reserved5364;	//0xC4D0571C
	REG_DDRC_M0_DEBUG_PRG_CNT_T                           debug_prg_cnt;	//0xC4D05720
	REG_DDRC_M0_DEBUG_REF_CNT_T                           debug_ref_cnt;	//0xC4D05724
	REG_DDRC_M0_DEBUG_ACT_CNT_T                           debug_act_cnt;	//0xC4D05728
	REG_DDRC_M0_DEBUG_RW_SWC_CNT_T                     debug_rw_swc_cnt;	//0xC4D0572C
	REG_DDRC_M0_DEBUG_R_URG_SWC_CNT_T               debug_r_urg_swc_cnt;	//0xC4D05730
	REG_DDRC_M0_DEBUG_R_REQ_ROW_HIT_CNT_T       debug_r_req_row_hit_cnt;	//0xC4D05734
	REG_DDRC_M0_DEBUG_R_REQ_HIT_CNT_T               debug_r_req_hit_cnt;	//0xC4D05738
	REG_DDRC_M0_DEBUG_R_URG_ROW_HIT_CNT_T       debug_r_urg_row_hit_cnt;	//0xC4D0573C
	REG_DDRC_M0_DEBUG_R_URG_HIT_CNT_T               debug_r_urg_hit_cnt;	//0xC4D05740
	REG_DDRC_M0_DEBUG_R_ROW_HIT_CNT_T               debug_r_row_hit_cnt;	//0xC4D05744
	REG_DDRC_M0_DEBUG_R_LUCKY_HIT_CNT_T           debug_r_lucky_hit_cnt;	//0xC4D05748
	UINT32                                                 reserved5365;	//0xC4D0574C
	REG_DDRC_M0_DEBUG_W_URG_SWC_CNT_T               debug_w_urg_swc_cnt;	//0xC4D05750
	REG_DDRC_M0_DEBUG_W_REQ_ROW_HIT_CNT_T       debug_w_req_row_hit_cnt;	//0xC4D05754
	REG_DDRC_M0_DEBUG_W_REQ_HIT_CNT_T               debug_w_req_hit_cnt;	//0xC4D05758
	REG_DDRC_M0_DEBUG_W_URG_ROW_HIT_CNT_T       debug_w_urg_row_hit_cnt;	//0xC4D0575C
	REG_DDRC_M0_DEBUG_W_URG_HIT_CNT_T               debug_w_urg_hit_cnt;	//0xC4D05760
	REG_DDRC_M0_DEBUG_W_ROW_HIT_CNT_T               debug_w_row_hit_cnt;	//0xC4D05764
	REG_DDRC_M0_DEBUG_W_LUCKY_HIT_CNT_T           debug_w_lucky_hit_cnt;	//0xC4D05768
	UINT32                                                 reserved5366;	//0xC4D0576C
	REG_DDRC_M0_DEBUG_MAX_LAT_QOS_T                   debug_max_lat_qos;	//0xC4D05770
	UINT32                                                 reserved5367;	//0xC4D05774
	UINT32                                                 reserved5368;	//0xC4D05778
	UINT32                                                 reserved5369;	//0xC4D0577C
	UINT32                                                 reserved5370;	//0xC4D05780
	UINT32                                                 reserved5371;	//0xC4D05784
	UINT32                                                 reserved5372;	//0xC4D05788
	UINT32                                                 reserved5373;	//0xC4D0578C
	UINT32                                                 reserved5374;	//0xC4D05790
	UINT32                                                 reserved5375;	//0xC4D05794
	UINT32                                                 reserved5376;	//0xC4D05798
	UINT32                                                 reserved5377;	//0xC4D0579C
	UINT32                                                 reserved5378;	//0xC4D057A0
	UINT32                                                 reserved5379;	//0xC4D057A4
	UINT32                                                 reserved5380;	//0xC4D057A8
	UINT32                                                 reserved5381;	//0xC4D057AC
	UINT32                                                 reserved5382;	//0xC4D057B0
	UINT32                                                 reserved5383;	//0xC4D057B4
	UINT32                                                 reserved5384;	//0xC4D057B8
	UINT32                                                 reserved5385;	//0xC4D057BC
	UINT32                                                 reserved5386;	//0xC4D057C0
	UINT32                                                 reserved5387;	//0xC4D057C4
	UINT32                                                 reserved5388;	//0xC4D057C8
	UINT32                                                 reserved5389;	//0xC4D057CC
	UINT32                                                 reserved5390;	//0xC4D057D0
	UINT32                                                 reserved5391;	//0xC4D057D4
	UINT32                                                 reserved5392;	//0xC4D057D8
	UINT32                                                 reserved5393;	//0xC4D057DC
	UINT32                                                 reserved5394;	//0xC4D057E0
	UINT32                                                 reserved5395;	//0xC4D057E4
	UINT32                                                 reserved5396;	//0xC4D057E8
	UINT32                                                 reserved5397;	//0xC4D057EC
	UINT32                                                 reserved5398;	//0xC4D057F0
	UINT32                                                 reserved5399;	//0xC4D057F4
	UINT32                                                 reserved5400;	//0xC4D057F8
	UINT32                                                 reserved5401;	//0xC4D057FC
	REG_DDRC_M0_DEBUG_R_HYB_SWC_CNT_T               debug_r_hyb_swc_cnt;	//0xC4D05800
	REG_DDRC_M0_DEBUG_W_HYB_SWC_CNT_T               debug_w_hyb_swc_cnt;	//0xC4D05804
	UINT32                                                 reserved5402;	//0xC4D05808
	UINT32                                                 reserved5403;	//0xC4D0580C
	UINT32                                                 reserved5404;	//0xC4D05810
	UINT32                                                 reserved5405;	//0xC4D05814
	UINT32                                                 reserved5406;	//0xC4D05818
	UINT32                                                 reserved5407;	//0xC4D0581C
	UINT32                                                 reserved5408;	//0xC4D05820
	UINT32                                                 reserved5409;	//0xC4D05824
	UINT32                                                 reserved5410;	//0xC4D05828
	UINT32                                                 reserved5411;	//0xC4D0582C
	UINT32                                                 reserved5412;	//0xC4D05830
	UINT32                                                 reserved5413;	//0xC4D05834
	UINT32                                                 reserved5414;	//0xC4D05838
	UINT32                                                 reserved5415;	//0xC4D0583C
	UINT32                                                 reserved5416;	//0xC4D05840
	UINT32                                                 reserved5417;	//0xC4D05844
	UINT32                                                 reserved5418;	//0xC4D05848
	UINT32                                                 reserved5419;	//0xC4D0584C
	UINT32                                                 reserved5420;	//0xC4D05850
	UINT32                                                 reserved5421;	//0xC4D05854
	UINT32                                                 reserved5422;	//0xC4D05858
	UINT32                                                 reserved5423;	//0xC4D0585C
	UINT32                                                 reserved5424;	//0xC4D05860
	UINT32                                                 reserved5425;	//0xC4D05864
	UINT32                                                 reserved5426;	//0xC4D05868
	UINT32                                                 reserved5427;	//0xC4D0586C
	UINT32                                                 reserved5428;	//0xC4D05870
	UINT32                                                 reserved5429;	//0xC4D05874
	UINT32                                                 reserved5430;	//0xC4D05878
	UINT32                                                 reserved5431;	//0xC4D0587C
	UINT32                                                 reserved5432;	//0xC4D05880
	UINT32                                                 reserved5433;	//0xC4D05884
	UINT32                                                 reserved5434;	//0xC4D05888
	UINT32                                                 reserved5435;	//0xC4D0588C
	UINT32                                                 reserved5436;	//0xC4D05890
	UINT32                                                 reserved5437;	//0xC4D05894
	UINT32                                                 reserved5438;	//0xC4D05898
	UINT32                                                 reserved5439;	//0xC4D0589C
	UINT32                                                 reserved5440;	//0xC4D058A0
	UINT32                                                 reserved5441;	//0xC4D058A4
	UINT32                                                 reserved5442;	//0xC4D058A8
	UINT32                                                 reserved5443;	//0xC4D058AC
	UINT32                                                 reserved5444;	//0xC4D058B0
	UINT32                                                 reserved5445;	//0xC4D058B4
	UINT32                                                 reserved5446;	//0xC4D058B8
	UINT32                                                 reserved5447;	//0xC4D058BC
	UINT32                                                 reserved5448;	//0xC4D058C0
	UINT32                                                 reserved5449;	//0xC4D058C4
	UINT32                                                 reserved5450;	//0xC4D058C8
	UINT32                                                 reserved5451;	//0xC4D058CC
	UINT32                                                 reserved5452;	//0xC4D058D0
	UINT32                                                 reserved5453;	//0xC4D058D4
	UINT32                                                 reserved5454;	//0xC4D058D8
	UINT32                                                 reserved5455;	//0xC4D058DC
	UINT32                                                 reserved5456;	//0xC4D058E0
	UINT32                                                 reserved5457;	//0xC4D058E4
	UINT32                                                 reserved5458;	//0xC4D058E8
	UINT32                                                 reserved5459;	//0xC4D058EC
	UINT32                                                 reserved5460;	//0xC4D058F0
	UINT32                                                 reserved5461;	//0xC4D058F4
	UINT32                                                 reserved5462;	//0xC4D058F8
	UINT32                                                 reserved5463;	//0xC4D058FC
	REG_DDRC_M0_DEBUG_R_FIFO_0_PRT_CNT_T         debug_r_fifo_0_prt_cnt;	//0xC4D05900
	REG_DDRC_M0_DEBUG_R_FIFO_1_PRT_CNT_T         debug_r_fifo_1_prt_cnt;	//0xC4D05904
	REG_DDRC_M0_DEBUG_R_FIFO_2_PRT_CNT_T         debug_r_fifo_2_prt_cnt;	//0xC4D05908
	REG_DDRC_M0_DEBUG_R_FIFO_3_PRT_CNT_T         debug_r_fifo_3_prt_cnt;	//0xC4D0590C
	REG_DDRC_M0_DEBUG_W_FIFO_0_PRT_CNT_T         debug_w_fifo_0_prt_cnt;	//0xC4D05910
	REG_DDRC_M0_DEBUG_W_FIFO_1_PRT_CNT_T         debug_w_fifo_1_prt_cnt;	//0xC4D05914
	REG_DDRC_M0_DEBUG_W_FIFO_2_PRT_CNT_T         debug_w_fifo_2_prt_cnt;	//0xC4D05918
	REG_DDRC_M0_DEBUG_W_FIFO_3_PRT_CNT_T         debug_w_fifo_3_prt_cnt;	//0xC4D0591C
	UINT32                                                 reserved5464;	//0xC4D05920
	UINT32                                                 reserved5465;	//0xC4D05924
	UINT32                                                 reserved5466;	//0xC4D05928
	UINT32                                                 reserved5467;	//0xC4D0592C
	UINT32                                                 reserved5468;	//0xC4D05930
	UINT32                                                 reserved5469;	//0xC4D05934
	UINT32                                                 reserved5470;	//0xC4D05938
	UINT32                                                 reserved5471;	//0xC4D0593C
	UINT32                                                 reserved5472;	//0xC4D05940
	UINT32                                                 reserved5473;	//0xC4D05944
	UINT32                                                 reserved5474;	//0xC4D05948
	UINT32                                                 reserved5475;	//0xC4D0594C
	UINT32                                                 reserved5476;	//0xC4D05950
	UINT32                                                 reserved5477;	//0xC4D05954
	UINT32                                                 reserved5478;	//0xC4D05958
	UINT32                                                 reserved5479;	//0xC4D0595C
	UINT32                                                 reserved5480;	//0xC4D05960
	UINT32                                                 reserved5481;	//0xC4D05964
	UINT32                                                 reserved5482;	//0xC4D05968
	UINT32                                                 reserved5483;	//0xC4D0596C
	UINT32                                                 reserved5484;	//0xC4D05970
	UINT32                                                 reserved5485;	//0xC4D05974
	UINT32                                                 reserved5486;	//0xC4D05978
	UINT32                                                 reserved5487;	//0xC4D0597C
	UINT32                                                 reserved5488;	//0xC4D05980
	UINT32                                                 reserved5489;	//0xC4D05984
	UINT32                                                 reserved5490;	//0xC4D05988
	UINT32                                                 reserved5491;	//0xC4D0598C
	UINT32                                                 reserved5492;	//0xC4D05990
	UINT32                                                 reserved5493;	//0xC4D05994
	UINT32                                                 reserved5494;	//0xC4D05998
	UINT32                                                 reserved5495;	//0xC4D0599C
	UINT32                                                 reserved5496;	//0xC4D059A0
	UINT32                                                 reserved5497;	//0xC4D059A4
	UINT32                                                 reserved5498;	//0xC4D059A8
	UINT32                                                 reserved5499;	//0xC4D059AC
	UINT32                                                 reserved5500;	//0xC4D059B0
	UINT32                                                 reserved5501;	//0xC4D059B4
	UINT32                                                 reserved5502;	//0xC4D059B8
	UINT32                                                 reserved5503;	//0xC4D059BC
	UINT32                                                 reserved5504;	//0xC4D059C0
	UINT32                                                 reserved5505;	//0xC4D059C4
	UINT32                                                 reserved5506;	//0xC4D059C8
	UINT32                                                 reserved5507;	//0xC4D059CC
	UINT32                                                 reserved5508;	//0xC4D059D0
	UINT32                                                 reserved5509;	//0xC4D059D4
	UINT32                                                 reserved5510;	//0xC4D059D8
	UINT32                                                 reserved5511;	//0xC4D059DC
	UINT32                                                 reserved5512;	//0xC4D059E0
	UINT32                                                 reserved5513;	//0xC4D059E4
	UINT32                                                 reserved5514;	//0xC4D059E8
	UINT32                                                 reserved5515;	//0xC4D059EC
	UINT32                                                 reserved5516;	//0xC4D059F0
	UINT32                                                 reserved5517;	//0xC4D059F4
	UINT32                                                 reserved5518;	//0xC4D059F8
	UINT32                                                 reserved5519;	//0xC4D059FC
	UINT32                                                 reserved5520;	//0xC4D05A00
	UINT32                                                 reserved5521;	//0xC4D05A04
	UINT32                                                 reserved5522;	//0xC4D05A08
	UINT32                                                 reserved5523;	//0xC4D05A0C
	UINT32                                                 reserved5524;	//0xC4D05A10
	UINT32                                                 reserved5525;	//0xC4D05A14
	UINT32                                                 reserved5526;	//0xC4D05A18
	UINT32                                                 reserved5527;	//0xC4D05A1C
	UINT32                                                 reserved5528;	//0xC4D05A20
	UINT32                                                 reserved5529;	//0xC4D05A24
	UINT32                                                 reserved5530;	//0xC4D05A28
	UINT32                                                 reserved5531;	//0xC4D05A2C
	UINT32                                                 reserved5532;	//0xC4D05A30
	UINT32                                                 reserved5533;	//0xC4D05A34
	UINT32                                                 reserved5534;	//0xC4D05A38
	UINT32                                                 reserved5535;	//0xC4D05A3C
	UINT32                                                 reserved5536;	//0xC4D05A40
	UINT32                                                 reserved5537;	//0xC4D05A44
	UINT32                                                 reserved5538;	//0xC4D05A48
	UINT32                                                 reserved5539;	//0xC4D05A4C
	UINT32                                                 reserved5540;	//0xC4D05A50
	UINT32                                                 reserved5541;	//0xC4D05A54
	UINT32                                                 reserved5542;	//0xC4D05A58
	UINT32                                                 reserved5543;	//0xC4D05A5C
	UINT32                                                 reserved5544;	//0xC4D05A60
	UINT32                                                 reserved5545;	//0xC4D05A64
	UINT32                                                 reserved5546;	//0xC4D05A68
	UINT32                                                 reserved5547;	//0xC4D05A6C
	UINT32                                                 reserved5548;	//0xC4D05A70
	UINT32                                                 reserved5549;	//0xC4D05A74
	UINT32                                                 reserved5550;	//0xC4D05A78
	UINT32                                                 reserved5551;	//0xC4D05A7C
	UINT32                                                 reserved5552;	//0xC4D05A80
	UINT32                                                 reserved5553;	//0xC4D05A84
	UINT32                                                 reserved5554;	//0xC4D05A88
	UINT32                                                 reserved5555;	//0xC4D05A8C
	UINT32                                                 reserved5556;	//0xC4D05A90
	UINT32                                                 reserved5557;	//0xC4D05A94
	UINT32                                                 reserved5558;	//0xC4D05A98
	UINT32                                                 reserved5559;	//0xC4D05A9C
	UINT32                                                 reserved5560;	//0xC4D05AA0
	UINT32                                                 reserved5561;	//0xC4D05AA4
	UINT32                                                 reserved5562;	//0xC4D05AA8
	UINT32                                                 reserved5563;	//0xC4D05AAC
	UINT32                                                 reserved5564;	//0xC4D05AB0
	UINT32                                                 reserved5565;	//0xC4D05AB4
	UINT32                                                 reserved5566;	//0xC4D05AB8
	UINT32                                                 reserved5567;	//0xC4D05ABC
	UINT32                                                 reserved5568;	//0xC4D05AC0
	UINT32                                                 reserved5569;	//0xC4D05AC4
	UINT32                                                 reserved5570;	//0xC4D05AC8
	UINT32                                                 reserved5571;	//0xC4D05ACC
	UINT32                                                 reserved5572;	//0xC4D05AD0
	UINT32                                                 reserved5573;	//0xC4D05AD4
	UINT32                                                 reserved5574;	//0xC4D05AD8
	UINT32                                                 reserved5575;	//0xC4D05ADC
	UINT32                                                 reserved5576;	//0xC4D05AE0
	UINT32                                                 reserved5577;	//0xC4D05AE4
	UINT32                                                 reserved5578;	//0xC4D05AE8
	UINT32                                                 reserved5579;	//0xC4D05AEC
	UINT32                                                 reserved5580;	//0xC4D05AF0
	UINT32                                                 reserved5581;	//0xC4D05AF4
	UINT32                                                 reserved5582;	//0xC4D05AF8
	UINT32                                                 reserved5583;	//0xC4D05AFC
	UINT32                                                 reserved5584;	//0xC4D05B00
	UINT32                                                 reserved5585;	//0xC4D05B04
	UINT32                                                 reserved5586;	//0xC4D05B08
	UINT32                                                 reserved5587;	//0xC4D05B0C
	UINT32                                                 reserved5588;	//0xC4D05B10
	UINT32                                                 reserved5589;	//0xC4D05B14
	UINT32                                                 reserved5590;	//0xC4D05B18
	UINT32                                                 reserved5591;	//0xC4D05B1C
	UINT32                                                 reserved5592;	//0xC4D05B20
	UINT32                                                 reserved5593;	//0xC4D05B24
	UINT32                                                 reserved5594;	//0xC4D05B28
	UINT32                                                 reserved5595;	//0xC4D05B2C
	UINT32                                                 reserved5596;	//0xC4D05B30
	UINT32                                                 reserved5597;	//0xC4D05B34
	UINT32                                                 reserved5598;	//0xC4D05B38
	UINT32                                                 reserved5599;	//0xC4D05B3C
	UINT32                                                 reserved5600;	//0xC4D05B40
	UINT32                                                 reserved5601;	//0xC4D05B44
	UINT32                                                 reserved5602;	//0xC4D05B48
	UINT32                                                 reserved5603;	//0xC4D05B4C
	UINT32                                                 reserved5604;	//0xC4D05B50
	UINT32                                                 reserved5605;	//0xC4D05B54
	UINT32                                                 reserved5606;	//0xC4D05B58
	UINT32                                                 reserved5607;	//0xC4D05B5C
	UINT32                                                 reserved5608;	//0xC4D05B60
	UINT32                                                 reserved5609;	//0xC4D05B64
	UINT32                                                 reserved5610;	//0xC4D05B68
	UINT32                                                 reserved5611;	//0xC4D05B6C
	UINT32                                                 reserved5612;	//0xC4D05B70
	UINT32                                                 reserved5613;	//0xC4D05B74
	UINT32                                                 reserved5614;	//0xC4D05B78
	UINT32                                                 reserved5615;	//0xC4D05B7C
	UINT32                                                 reserved5616;	//0xC4D05B80
	UINT32                                                 reserved5617;	//0xC4D05B84
	UINT32                                                 reserved5618;	//0xC4D05B88
	UINT32                                                 reserved5619;	//0xC4D05B8C
	UINT32                                                 reserved5620;	//0xC4D05B90
	UINT32                                                 reserved5621;	//0xC4D05B94
	UINT32                                                 reserved5622;	//0xC4D05B98
	UINT32                                                 reserved5623;	//0xC4D05B9C
	UINT32                                                 reserved5624;	//0xC4D05BA0
	UINT32                                                 reserved5625;	//0xC4D05BA4
	UINT32                                                 reserved5626;	//0xC4D05BA8
	UINT32                                                 reserved5627;	//0xC4D05BAC
	UINT32                                                 reserved5628;	//0xC4D05BB0
	UINT32                                                 reserved5629;	//0xC4D05BB4
	UINT32                                                 reserved5630;	//0xC4D05BB8
	UINT32                                                 reserved5631;	//0xC4D05BBC
	UINT32                                                 reserved5632;	//0xC4D05BC0
	UINT32                                                 reserved5633;	//0xC4D05BC4
	UINT32                                                 reserved5634;	//0xC4D05BC8
	UINT32                                                 reserved5635;	//0xC4D05BCC
	UINT32                                                 reserved5636;	//0xC4D05BD0
	UINT32                                                 reserved5637;	//0xC4D05BD4
	UINT32                                                 reserved5638;	//0xC4D05BD8
	UINT32                                                 reserved5639;	//0xC4D05BDC
	UINT32                                                 reserved5640;	//0xC4D05BE0
	UINT32                                                 reserved5641;	//0xC4D05BE4
	UINT32                                                 reserved5642;	//0xC4D05BE8
	UINT32                                                 reserved5643;	//0xC4D05BEC
	UINT32                                                 reserved5644;	//0xC4D05BF0
	UINT32                                                 reserved5645;	//0xC4D05BF4
	UINT32                                                 reserved5646;	//0xC4D05BF8
	UINT32                                                 reserved5647;	//0xC4D05BFC
	UINT32                                                 reserved5648;	//0xC4D05C00
	UINT32                                                 reserved5649;	//0xC4D05C04
	UINT32                                                 reserved5650;	//0xC4D05C08
	UINT32                                                 reserved5651;	//0xC4D05C0C
	UINT32                                                 reserved5652;	//0xC4D05C10
	UINT32                                                 reserved5653;	//0xC4D05C14
	UINT32                                                 reserved5654;	//0xC4D05C18
	UINT32                                                 reserved5655;	//0xC4D05C1C
	UINT32                                                 reserved5656;	//0xC4D05C20
	UINT32                                                 reserved5657;	//0xC4D05C24
	UINT32                                                 reserved5658;	//0xC4D05C28
	UINT32                                                 reserved5659;	//0xC4D05C2C
	UINT32                                                 reserved5660;	//0xC4D05C30
	UINT32                                                 reserved5661;	//0xC4D05C34
	UINT32                                                 reserved5662;	//0xC4D05C38
	UINT32                                                 reserved5663;	//0xC4D05C3C
	UINT32                                                 reserved5664;	//0xC4D05C40
	UINT32                                                 reserved5665;	//0xC4D05C44
	UINT32                                                 reserved5666;	//0xC4D05C48
	UINT32                                                 reserved5667;	//0xC4D05C4C
	UINT32                                                 reserved5668;	//0xC4D05C50
	UINT32                                                 reserved5669;	//0xC4D05C54
	UINT32                                                 reserved5670;	//0xC4D05C58
	UINT32                                                 reserved5671;	//0xC4D05C5C
	UINT32                                                 reserved5672;	//0xC4D05C60
	UINT32                                                 reserved5673;	//0xC4D05C64
	UINT32                                                 reserved5674;	//0xC4D05C68
	UINT32                                                 reserved5675;	//0xC4D05C6C
	UINT32                                                 reserved5676;	//0xC4D05C70
	UINT32                                                 reserved5677;	//0xC4D05C74
	UINT32                                                 reserved5678;	//0xC4D05C78
	UINT32                                                 reserved5679;	//0xC4D05C7C
	UINT32                                                 reserved5680;	//0xC4D05C80
	UINT32                                                 reserved5681;	//0xC4D05C84
	UINT32                                                 reserved5682;	//0xC4D05C88
	UINT32                                                 reserved5683;	//0xC4D05C8C
	UINT32                                                 reserved5684;	//0xC4D05C90
	UINT32                                                 reserved5685;	//0xC4D05C94
	UINT32                                                 reserved5686;	//0xC4D05C98
	UINT32                                                 reserved5687;	//0xC4D05C9C
	UINT32                                                 reserved5688;	//0xC4D05CA0
	UINT32                                                 reserved5689;	//0xC4D05CA4
	UINT32                                                 reserved5690;	//0xC4D05CA8
	UINT32                                                 reserved5691;	//0xC4D05CAC
	UINT32                                                 reserved5692;	//0xC4D05CB0
	UINT32                                                 reserved5693;	//0xC4D05CB4
	UINT32                                                 reserved5694;	//0xC4D05CB8
	UINT32                                                 reserved5695;	//0xC4D05CBC
	UINT32                                                 reserved5696;	//0xC4D05CC0
	UINT32                                                 reserved5697;	//0xC4D05CC4
	UINT32                                                 reserved5698;	//0xC4D05CC8
	UINT32                                                 reserved5699;	//0xC4D05CCC
	UINT32                                                 reserved5700;	//0xC4D05CD0
	UINT32                                                 reserved5701;	//0xC4D05CD4
	UINT32                                                 reserved5702;	//0xC4D05CD8
	UINT32                                                 reserved5703;	//0xC4D05CDC
	UINT32                                                 reserved5704;	//0xC4D05CE0
	UINT32                                                 reserved5705;	//0xC4D05CE4
	UINT32                                                 reserved5706;	//0xC4D05CE8
	UINT32                                                 reserved5707;	//0xC4D05CEC
	UINT32                                                 reserved5708;	//0xC4D05CF0
	UINT32                                                 reserved5709;	//0xC4D05CF4
	UINT32                                                 reserved5710;	//0xC4D05CF8
	UINT32                                                 reserved5711;	//0xC4D05CFC
	UINT32                                                 reserved5712;	//0xC4D05D00
	UINT32                                                 reserved5713;	//0xC4D05D04
	UINT32                                                 reserved5714;	//0xC4D05D08
	UINT32                                                 reserved5715;	//0xC4D05D0C
	UINT32                                                 reserved5716;	//0xC4D05D10
	UINT32                                                 reserved5717;	//0xC4D05D14
	UINT32                                                 reserved5718;	//0xC4D05D18
	UINT32                                                 reserved5719;	//0xC4D05D1C
	UINT32                                                 reserved5720;	//0xC4D05D20
	UINT32                                                 reserved5721;	//0xC4D05D24
	UINT32                                                 reserved5722;	//0xC4D05D28
	UINT32                                                 reserved5723;	//0xC4D05D2C
	UINT32                                                 reserved5724;	//0xC4D05D30
	UINT32                                                 reserved5725;	//0xC4D05D34
	UINT32                                                 reserved5726;	//0xC4D05D38
	UINT32                                                 reserved5727;	//0xC4D05D3C
	UINT32                                                 reserved5728;	//0xC4D05D40
	UINT32                                                 reserved5729;	//0xC4D05D44
	UINT32                                                 reserved5730;	//0xC4D05D48
	UINT32                                                 reserved5731;	//0xC4D05D4C
	UINT32                                                 reserved5732;	//0xC4D05D50
	UINT32                                                 reserved5733;	//0xC4D05D54
	UINT32                                                 reserved5734;	//0xC4D05D58
	UINT32                                                 reserved5735;	//0xC4D05D5C
	UINT32                                                 reserved5736;	//0xC4D05D60
	UINT32                                                 reserved5737;	//0xC4D05D64
	UINT32                                                 reserved5738;	//0xC4D05D68
	UINT32                                                 reserved5739;	//0xC4D05D6C
	UINT32                                                 reserved5740;	//0xC4D05D70
	UINT32                                                 reserved5741;	//0xC4D05D74
	UINT32                                                 reserved5742;	//0xC4D05D78
	UINT32                                                 reserved5743;	//0xC4D05D7C
	UINT32                                                 reserved5744;	//0xC4D05D80
	UINT32                                                 reserved5745;	//0xC4D05D84
	UINT32                                                 reserved5746;	//0xC4D05D88
	UINT32                                                 reserved5747;	//0xC4D05D8C
	UINT32                                                 reserved5748;	//0xC4D05D90
	UINT32                                                 reserved5749;	//0xC4D05D94
	UINT32                                                 reserved5750;	//0xC4D05D98
	UINT32                                                 reserved5751;	//0xC4D05D9C
	UINT32                                                 reserved5752;	//0xC4D05DA0
	UINT32                                                 reserved5753;	//0xC4D05DA4
	UINT32                                                 reserved5754;	//0xC4D05DA8
	UINT32                                                 reserved5755;	//0xC4D05DAC
	UINT32                                                 reserved5756;	//0xC4D05DB0
	UINT32                                                 reserved5757;	//0xC4D05DB4
	UINT32                                                 reserved5758;	//0xC4D05DB8
	UINT32                                                 reserved5759;	//0xC4D05DBC
	UINT32                                                 reserved5760;	//0xC4D05DC0
	UINT32                                                 reserved5761;	//0xC4D05DC4
	UINT32                                                 reserved5762;	//0xC4D05DC8
	UINT32                                                 reserved5763;	//0xC4D05DCC
	UINT32                                                 reserved5764;	//0xC4D05DD0
	UINT32                                                 reserved5765;	//0xC4D05DD4
	UINT32                                                 reserved5766;	//0xC4D05DD8
	UINT32                                                 reserved5767;	//0xC4D05DDC
	UINT32                                                 reserved5768;	//0xC4D05DE0
	UINT32                                                 reserved5769;	//0xC4D05DE4
	UINT32                                                 reserved5770;	//0xC4D05DE8
	UINT32                                                 reserved5771;	//0xC4D05DEC
	UINT32                                                 reserved5772;	//0xC4D05DF0
	UINT32                                                 reserved5773;	//0xC4D05DF4
	UINT32                                                 reserved5774;	//0xC4D05DF8
	UINT32                                                 reserved5775;	//0xC4D05DFC
	UINT32                                                 reserved5776;	//0xC4D05E00
	UINT32                                                 reserved5777;	//0xC4D05E04
	UINT32                                                 reserved5778;	//0xC4D05E08
	UINT32                                                 reserved5779;	//0xC4D05E0C
	UINT32                                                 reserved5780;	//0xC4D05E10
	UINT32                                                 reserved5781;	//0xC4D05E14
	UINT32                                                 reserved5782;	//0xC4D05E18
	UINT32                                                 reserved5783;	//0xC4D05E1C
	UINT32                                                 reserved5784;	//0xC4D05E20
	UINT32                                                 reserved5785;	//0xC4D05E24
	UINT32                                                 reserved5786;	//0xC4D05E28
	UINT32                                                 reserved5787;	//0xC4D05E2C
	UINT32                                                 reserved5788;	//0xC4D05E30
	UINT32                                                 reserved5789;	//0xC4D05E34
	UINT32                                                 reserved5790;	//0xC4D05E38
	UINT32                                                 reserved5791;	//0xC4D05E3C
	UINT32                                                 reserved5792;	//0xC4D05E40
	UINT32                                                 reserved5793;	//0xC4D05E44
	UINT32                                                 reserved5794;	//0xC4D05E48
	UINT32                                                 reserved5795;	//0xC4D05E4C
	UINT32                                                 reserved5796;	//0xC4D05E50
	UINT32                                                 reserved5797;	//0xC4D05E54
	UINT32                                                 reserved5798;	//0xC4D05E58
	UINT32                                                 reserved5799;	//0xC4D05E5C
	UINT32                                                 reserved5800;	//0xC4D05E60
	UINT32                                                 reserved5801;	//0xC4D05E64
	UINT32                                                 reserved5802;	//0xC4D05E68
	UINT32                                                 reserved5803;	//0xC4D05E6C
	UINT32                                                 reserved5804;	//0xC4D05E70
	UINT32                                                 reserved5805;	//0xC4D05E74
	UINT32                                                 reserved5806;	//0xC4D05E78
	UINT32                                                 reserved5807;	//0xC4D05E7C
	UINT32                                                 reserved5808;	//0xC4D05E80
	UINT32                                                 reserved5809;	//0xC4D05E84
	UINT32                                                 reserved5810;	//0xC4D05E88
	UINT32                                                 reserved5811;	//0xC4D05E8C
	UINT32                                                 reserved5812;	//0xC4D05E90
	UINT32                                                 reserved5813;	//0xC4D05E94
	UINT32                                                 reserved5814;	//0xC4D05E98
	UINT32                                                 reserved5815;	//0xC4D05E9C
	UINT32                                                 reserved5816;	//0xC4D05EA0
	UINT32                                                 reserved5817;	//0xC4D05EA4
	UINT32                                                 reserved5818;	//0xC4D05EA8
	UINT32                                                 reserved5819;	//0xC4D05EAC
	UINT32                                                 reserved5820;	//0xC4D05EB0
	UINT32                                                 reserved5821;	//0xC4D05EB4
	UINT32                                                 reserved5822;	//0xC4D05EB8
	UINT32                                                 reserved5823;	//0xC4D05EBC
	UINT32                                                 reserved5824;	//0xC4D05EC0
	UINT32                                                 reserved5825;	//0xC4D05EC4
	UINT32                                                 reserved5826;	//0xC4D05EC8
	UINT32                                                 reserved5827;	//0xC4D05ECC
	UINT32                                                 reserved5828;	//0xC4D05ED0
	UINT32                                                 reserved5829;	//0xC4D05ED4
	UINT32                                                 reserved5830;	//0xC4D05ED8
	UINT32                                                 reserved5831;	//0xC4D05EDC
	UINT32                                                 reserved5832;	//0xC4D05EE0
	UINT32                                                 reserved5833;	//0xC4D05EE4
	UINT32                                                 reserved5834;	//0xC4D05EE8
	UINT32                                                 reserved5835;	//0xC4D05EEC
	UINT32                                                 reserved5836;	//0xC4D05EF0
	UINT32                                                 reserved5837;	//0xC4D05EF4
	UINT32                                                 reserved5838;	//0xC4D05EF8
	UINT32                                                 reserved5839;	//0xC4D05EFC
	UINT32                                                 reserved5840;	//0xC4D05F00
	UINT32                                                 reserved5841;	//0xC4D05F04
	UINT32                                                 reserved5842;	//0xC4D05F08
	UINT32                                                 reserved5843;	//0xC4D05F0C
	UINT32                                                 reserved5844;	//0xC4D05F10
	UINT32                                                 reserved5845;	//0xC4D05F14
	UINT32                                                 reserved5846;	//0xC4D05F18
	UINT32                                                 reserved5847;	//0xC4D05F1C
	UINT32                                                 reserved5848;	//0xC4D05F20
	UINT32                                                 reserved5849;	//0xC4D05F24
	UINT32                                                 reserved5850;	//0xC4D05F28
	UINT32                                                 reserved5851;	//0xC4D05F2C
	UINT32                                                 reserved5852;	//0xC4D05F30
	UINT32                                                 reserved5853;	//0xC4D05F34
	UINT32                                                 reserved5854;	//0xC4D05F38
	UINT32                                                 reserved5855;	//0xC4D05F3C
	UINT32                                                 reserved5856;	//0xC4D05F40
	UINT32                                                 reserved5857;	//0xC4D05F44
	UINT32                                                 reserved5858;	//0xC4D05F48
	UINT32                                                 reserved5859;	//0xC4D05F4C
	UINT32                                                 reserved5860;	//0xC4D05F50
	UINT32                                                 reserved5861;	//0xC4D05F54
	UINT32                                                 reserved5862;	//0xC4D05F58
	UINT32                                                 reserved5863;	//0xC4D05F5C
	UINT32                                                 reserved5864;	//0xC4D05F60
	UINT32                                                 reserved5865;	//0xC4D05F64
	UINT32                                                 reserved5866;	//0xC4D05F68
	UINT32                                                 reserved5867;	//0xC4D05F6C
	UINT32                                                 reserved5868;	//0xC4D05F70
	UINT32                                                 reserved5869;	//0xC4D05F74
	UINT32                                                 reserved5870;	//0xC4D05F78
	UINT32                                                 reserved5871;	//0xC4D05F7C
	UINT32                                                 reserved5872;	//0xC4D05F80
	UINT32                                                 reserved5873;	//0xC4D05F84
	UINT32                                                 reserved5874;	//0xC4D05F88
	UINT32                                                 reserved5875;	//0xC4D05F8C
	UINT32                                                 reserved5876;	//0xC4D05F90
	UINT32                                                 reserved5877;	//0xC4D05F94
	UINT32                                                 reserved5878;	//0xC4D05F98
	UINT32                                                 reserved5879;	//0xC4D05F9C
	UINT32                                                 reserved5880;	//0xC4D05FA0
	UINT32                                                 reserved5881;	//0xC4D05FA4
	UINT32                                                 reserved5882;	//0xC4D05FA8
	UINT32                                                 reserved5883;	//0xC4D05FAC
	UINT32                                                 reserved5884;	//0xC4D05FB0
	UINT32                                                 reserved5885;	//0xC4D05FB4
	UINT32                                                 reserved5886;	//0xC4D05FB8
	UINT32                                                 reserved5887;	//0xC4D05FBC
	UINT32                                                 reserved5888;	//0xC4D05FC0
	UINT32                                                 reserved5889;	//0xC4D05FC4
	UINT32                                                 reserved5890;	//0xC4D05FC8
	UINT32                                                 reserved5891;	//0xC4D05FCC
	UINT32                                                 reserved5892;	//0xC4D05FD0
	UINT32                                                 reserved5893;	//0xC4D05FD4
	UINT32                                                 reserved5894;	//0xC4D05FD8
	UINT32                                                 reserved5895;	//0xC4D05FDC
	UINT32                                                 reserved5896;	//0xC4D05FE0
	UINT32                                                 reserved5897;	//0xC4D05FE4
	UINT32                                                 reserved5898;	//0xC4D05FE8
	UINT32                                                 reserved5899;	//0xC4D05FEC
	UINT32                                                 reserved5900;	//0xC4D05FF0
	UINT32                                                 reserved5901;	//0xC4D05FF4
	UINT32                                                 reserved5902;	//0xC4D05FF8
	UINT32                                                 reserved5903;	//0xC4D05FFC
	REG_DDRC_M0_DEBUG_LPD4_0_T                             debug_lpd4_0;	//0xC4D06000
	REG_DDRC_M0_DEBUG_LPD4_1_T                             debug_lpd4_1;	//0xC4D06004
	REG_DDRC_M0_DEBUG_LPD4_2_T                             debug_lpd4_2;	//0xC4D06008
	REG_DDRC_M0_DEBUG_LPD4_3_T                             debug_lpd4_3;	//0xC4D0600C
	REG_DDRC_M0_DEBUG_LPD4_4_T                             debug_lpd4_4;	//0xC4D06010
	REG_DDRC_M0_DEBUG_LPD4_5_T                             debug_lpd4_5;	//0xC4D06014
	REG_DDRC_M0_DEBUG_LPD4_6_T                             debug_lpd4_6;	//0xC4D06018
	REG_DDRC_M0_DEBUG_LPD4_7_T                             debug_lpd4_7;	//0xC4D0601C
	REG_DDRC_M0_DEBUG_LPD4_8_T                             debug_lpd4_8;	//0xC4D06020
	REG_DDRC_M0_DEBUG_LPD4_9_T                             debug_lpd4_9;	//0xC4D06024
	REG_DDRC_M0_DEBUG_LPD4_10_T                           debug_lpd4_10;	//0xC4D06028
	REG_DDRC_M0_DEBUG_LPD4_11_T                           debug_lpd4_11;	//0xC4D0602C
	REG_DDRC_M0_DEBUG_LPD4_12_T                           debug_lpd4_12;	//0xC4D06030
	REG_DDRC_M0_DEBUG_LPD4_13_T                           debug_lpd4_13;	//0xC4D06034
	REG_DDRC_M0_DEBUG_LPD4_14_T                           debug_lpd4_14;	//0xC4D06038
	REG_DDRC_M0_DEBUG_LPD4_15_T                           debug_lpd4_15;	//0xC4D0603C
	REG_DDRC_M0_DEBUG_LPD4_16_T                           debug_lpd4_16;	//0xC4D06040
	UINT32                                                 reserved5904;	//0xC4D06044
	UINT32                                                 reserved5905;	//0xC4D06048
	UINT32                                                 reserved5906;	//0xC4D0604C
	UINT32                                                 reserved5907;	//0xC4D06050
	UINT32                                                 reserved5908;	//0xC4D06054
	UINT32                                                 reserved5909;	//0xC4D06058
	UINT32                                                 reserved5910;	//0xC4D0605C
	UINT32                                                 reserved5911;	//0xC4D06060
	UINT32                                                 reserved5912;	//0xC4D06064
	UINT32                                                 reserved5913;	//0xC4D06068
	UINT32                                                 reserved5914;	//0xC4D0606C
	UINT32                                                 reserved5915;	//0xC4D06070
	UINT32                                                 reserved5916;	//0xC4D06074
	UINT32                                                 reserved5917;	//0xC4D06078
	UINT32                                                 reserved5918;	//0xC4D0607C
	UINT32                                                 reserved5919;	//0xC4D06080
	UINT32                                                 reserved5920;	//0xC4D06084
	UINT32                                                 reserved5921;	//0xC4D06088
	UINT32                                                 reserved5922;	//0xC4D0608C
	UINT32                                                 reserved5923;	//0xC4D06090
	UINT32                                                 reserved5924;	//0xC4D06094
	UINT32                                                 reserved5925;	//0xC4D06098
	UINT32                                                 reserved5926;	//0xC4D0609C
	UINT32                                                 reserved5927;	//0xC4D060A0
	UINT32                                                 reserved5928;	//0xC4D060A4
	UINT32                                                 reserved5929;	//0xC4D060A8
	UINT32                                                 reserved5930;	//0xC4D060AC
	UINT32                                                 reserved5931;	//0xC4D060B0
	UINT32                                                 reserved5932;	//0xC4D060B4
	UINT32                                                 reserved5933;	//0xC4D060B8
	UINT32                                                 reserved5934;	//0xC4D060BC
	UINT32                                                 reserved5935;	//0xC4D060C0
	UINT32                                                 reserved5936;	//0xC4D060C4
	UINT32                                                 reserved5937;	//0xC4D060C8
	UINT32                                                 reserved5938;	//0xC4D060CC
	UINT32                                                 reserved5939;	//0xC4D060D0
	UINT32                                                 reserved5940;	//0xC4D060D4
	UINT32                                                 reserved5941;	//0xC4D060D8
	UINT32                                                 reserved5942;	//0xC4D060DC
	UINT32                                                 reserved5943;	//0xC4D060E0
	UINT32                                                 reserved5944;	//0xC4D060E4
	UINT32                                                 reserved5945;	//0xC4D060E8
	UINT32                                                 reserved5946;	//0xC4D060EC
	UINT32                                                 reserved5947;	//0xC4D060F0
	UINT32                                                 reserved5948;	//0xC4D060F4
	UINT32                                                 reserved5949;	//0xC4D060F8
	UINT32                                                 reserved5950;	//0xC4D060FC
	REG_DDRC_M0_DEBUG_LPD4_MR_0_T                       debug_lpd4_mr_0;	//0xC4D06100
	REG_DDRC_M0_DEBUG_LPD4_MR_1_T                       debug_lpd4_mr_1;	//0xC4D06104
	REG_DDRC_M0_DEBUG_LPD4_MR_2_T                       debug_lpd4_mr_2;	//0xC4D06108
	REG_DDRC_M0_DEBUG_LPD4_MR_3_T                       debug_lpd4_mr_3;	//0xC4D0610C
	REG_DDRC_M0_DEBUG_LPD4_MR_4_T                       debug_lpd4_mr_4;	//0xC4D06110
	REG_DDRC_M0_DEBUG_LPD4_MR_5_T                       debug_lpd4_mr_5;	//0xC4D06114
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_0_T           debug_lpd4_mpc_fifo_0;	//0xC4D06118
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_1_T           debug_lpd4_mpc_fifo_1;	//0xC4D0611C
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_2_T           debug_lpd4_mpc_fifo_2;	//0xC4D06120
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_3_T           debug_lpd4_mpc_fifo_3;	//0xC4D06124
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_4_T           debug_lpd4_mpc_fifo_4;	//0xC4D06128
	REG_DDRC_M0_DEBUG_LPD4_MPC_FIFO_5_T           debug_lpd4_mpc_fifo_5;	//0xC4D0612C
	UINT32                                                 reserved5951;	//0xC4D06130
	UINT32                                                 reserved5952;	//0xC4D06134
	UINT32                                                 reserved5953;	//0xC4D06138
	UINT32                                                 reserved5954;	//0xC4D0613C
	UINT32                                                 reserved5955;	//0xC4D06140
	UINT32                                                 reserved5956;	//0xC4D06144
	UINT32                                                 reserved5957;	//0xC4D06148
	UINT32                                                 reserved5958;	//0xC4D0614C
	UINT32                                                 reserved5959;	//0xC4D06150
	UINT32                                                 reserved5960;	//0xC4D06154
	UINT32                                                 reserved5961;	//0xC4D06158
	UINT32                                                 reserved5962;	//0xC4D0615C
	UINT32                                                 reserved5963;	//0xC4D06160
	UINT32                                                 reserved5964;	//0xC4D06164
	UINT32                                                 reserved5965;	//0xC4D06168
	UINT32                                                 reserved5966;	//0xC4D0616C
	UINT32                                                 reserved5967;	//0xC4D06170
	UINT32                                                 reserved5968;	//0xC4D06174
	UINT32                                                 reserved5969;	//0xC4D06178
	UINT32                                                 reserved5970;	//0xC4D0617C
	UINT32                                                 reserved5971;	//0xC4D06180
	UINT32                                                 reserved5972;	//0xC4D06184
	UINT32                                                 reserved5973;	//0xC4D06188
	UINT32                                                 reserved5974;	//0xC4D0618C
	UINT32                                                 reserved5975;	//0xC4D06190
	UINT32                                                 reserved5976;	//0xC4D06194
	UINT32                                                 reserved5977;	//0xC4D06198
	UINT32                                                 reserved5978;	//0xC4D0619C
	UINT32                                                 reserved5979;	//0xC4D061A0
	UINT32                                                 reserved5980;	//0xC4D061A4
	UINT32                                                 reserved5981;	//0xC4D061A8
	UINT32                                                 reserved5982;	//0xC4D061AC
	UINT32                                                 reserved5983;	//0xC4D061B0
	UINT32                                                 reserved5984;	//0xC4D061B4
	UINT32                                                 reserved5985;	//0xC4D061B8
	UINT32                                                 reserved5986;	//0xC4D061BC
	UINT32                                                 reserved5987;	//0xC4D061C0
	UINT32                                                 reserved5988;	//0xC4D061C4
	UINT32                                                 reserved5989;	//0xC4D061C8
	UINT32                                                 reserved5990;	//0xC4D061CC
	UINT32                                                 reserved5991;	//0xC4D061D0
	UINT32                                                 reserved5992;	//0xC4D061D4
	UINT32                                                 reserved5993;	//0xC4D061D8
	UINT32                                                 reserved5994;	//0xC4D061DC
	UINT32                                                 reserved5995;	//0xC4D061E0
	UINT32                                                 reserved5996;	//0xC4D061E4
	UINT32                                                 reserved5997;	//0xC4D061E8
	UINT32                                                 reserved5998;	//0xC4D061EC
	UINT32                                                 reserved5999;	//0xC4D061F0
	UINT32                                                 reserved6000;	//0xC4D061F4
	UINT32                                                 reserved6001;	//0xC4D061F8
	UINT32                                                 reserved6002;	//0xC4D061FC
	REG_DDRC_M0_DEBUG_CTRL_CMD_MRW1_T               debug_ctrl_cmd_mrw1;	//0xC4D06200
	REG_DDRC_M0_DEBUG_CTRL_CMD_MRW0_T               debug_ctrl_cmd_mrw0;	//0xC4D06204
	REG_DDRC_M0_DEBUG_CTRL_CMD_LP_EXIT_T         debug_ctrl_cmd_lp_exit;	//0xC4D06208
	REG_DDRC_M0_DEBUG_CTRL_CMD_LP_ENTRY_T       debug_ctrl_cmd_lp_entry;	//0xC4D0620C
	REG_DDRC_M0_DEBUG_CTRL_CMD_SR_PD_EXIT_T   debug_ctrl_cmd_sr_pd_exit;	//0xC4D06210
	REG_DDRC_M0_DEBUG_CTRL_CMD_SR_PD_ENTRY_T debug_ctrl_cmd_sr_pd_entry;	//0xC4D06214
	REG_DDRC_M0_DEBUG_CTRL_CMD_SR_EXIT_T         debug_ctrl_cmd_sr_exit;	//0xC4D06218
	REG_DDRC_M0_DEBUG_CTRL_CMD_SR_ENTRY_T       debug_ctrl_cmd_sr_entry;	//0xC4D0621C
	REG_DDRC_M0_DEBUG_CTRL_CMD_PD_EXIT_T         debug_ctrl_cmd_pd_exit;	//0xC4D06220
	REG_DDRC_M0_DEBUG_CTRL_CMD_PD_ENTRY_T       debug_ctrl_cmd_pd_entry;	//0xC4D06224
	REG_DDRC_M0_DEBUG_CTRL_CMD_ZQLAT_T             debug_ctrl_cmd_zqlat;	//0xC4D06228
	REG_DDRC_M0_DEBUG_CTRL_CMD_ZQCAL_T             debug_ctrl_cmd_zqcal;	//0xC4D0622C
	REG_DDRC_M0_DEBUG_CTRL_CMD_CKE1_T               debug_ctrl_cmd_cke1;	//0xC4D06230
	REG_DDRC_M0_DEBUG_CTRL_CMD_CKE0_T               debug_ctrl_cmd_cke0;	//0xC4D06234
	REG_DDRC_M0_DEBUG_CTRL_CMD_RSTN1_T             debug_ctrl_cmd_rstn1;	//0xC4D06238
	REG_DDRC_M0_DEBUG_CTRL_CMD_RSTN0_T             debug_ctrl_cmd_rstn0;	//0xC4D0623C
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD0_T                 debug_ctrl_cmd_rd0;	//0xC4D06240
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD1_T                 debug_ctrl_cmd_rd1;	//0xC4D06244
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD2_T                 debug_ctrl_cmd_rd2;	//0xC4D06248
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD3_T                 debug_ctrl_cmd_rd3;	//0xC4D0624C
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD4_T                 debug_ctrl_cmd_rd4;	//0xC4D06250
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD5_T                 debug_ctrl_cmd_rd5;	//0xC4D06254
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD6_T                 debug_ctrl_cmd_rd6;	//0xC4D06258
	REG_DDRC_M0_DEBUG_CTRL_CMD_RD7_T                 debug_ctrl_cmd_rd7;	//0xC4D0625C
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR0_T               debug_ctrl_cmd_mwr0;	//0xC4D06260
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR1_T               debug_ctrl_cmd_mwr1;	//0xC4D06264
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR2_T               debug_ctrl_cmd_mwr2;	//0xC4D06268
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR3_T               debug_ctrl_cmd_mwr3;	//0xC4D0626C
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR4_T               debug_ctrl_cmd_mwr4;	//0xC4D06270
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR5_T               debug_ctrl_cmd_mwr5;	//0xC4D06274
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR6_T               debug_ctrl_cmd_mwr6;	//0xC4D06278
	REG_DDRC_M0_DEBUG_CTRL_CMD_MWR7_T               debug_ctrl_cmd_mwr7;	//0xC4D0627C
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR0_T                 debug_ctrl_cmd_wr0;	//0xC4D06280
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR1_T                 debug_ctrl_cmd_wr1;	//0xC4D06284
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR2_T                 debug_ctrl_cmd_wr2;	//0xC4D06288
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR3_T                 debug_ctrl_cmd_wr3;	//0xC4D0628C
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR4_T                 debug_ctrl_cmd_wr4;	//0xC4D06290
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR5_T                 debug_ctrl_cmd_wr5;	//0xC4D06294
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR6_T                 debug_ctrl_cmd_wr6;	//0xC4D06298
	REG_DDRC_M0_DEBUG_CTRL_CMD_WR7_T                 debug_ctrl_cmd_wr7;	//0xC4D0629C
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT0_T               debug_ctrl_cmd_act0;	//0xC4D062A0
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT1_T               debug_ctrl_cmd_act1;	//0xC4D062A4
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT2_T               debug_ctrl_cmd_act2;	//0xC4D062A8
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT3_T               debug_ctrl_cmd_act3;	//0xC4D062AC
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT4_T               debug_ctrl_cmd_act4;	//0xC4D062B0
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT5_T               debug_ctrl_cmd_act5;	//0xC4D062B4
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT6_T               debug_ctrl_cmd_act6;	//0xC4D062B8
	REG_DDRC_M0_DEBUG_CTRL_CMD_ACT7_T               debug_ctrl_cmd_act7;	//0xC4D062BC
	UINT32                                                 reserved6003;	//0xC4D062C0
	UINT32                                                 reserved6004;	//0xC4D062C4
	UINT32                                                 reserved6005;	//0xC4D062C8
	UINT32                                                 reserved6006;	//0xC4D062CC
	UINT32                                                 reserved6007;	//0xC4D062D0
	UINT32                                                 reserved6008;	//0xC4D062D4
	UINT32                                                 reserved6009;	//0xC4D062D8
	UINT32                                                 reserved6010;	//0xC4D062DC
	UINT32                                                 reserved6011;	//0xC4D062E0
	UINT32                                                 reserved6012;	//0xC4D062E4
	UINT32                                                 reserved6013;	//0xC4D062E8
	UINT32                                                 reserved6014;	//0xC4D062EC
	UINT32                                                 reserved6015;	//0xC4D062F0
	UINT32                                                 reserved6016;	//0xC4D062F4
	UINT32                                                 reserved6017;	//0xC4D062F8
	UINT32                                                 reserved6018;	//0xC4D062FC
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB0_T         debug_ctrl_cmd_ref_pb0;	//0xC4D06300
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB1_T         debug_ctrl_cmd_ref_pb1;	//0xC4D06304
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB2_T         debug_ctrl_cmd_ref_pb2;	//0xC4D06308
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB3_T         debug_ctrl_cmd_ref_pb3;	//0xC4D0630C
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB4_T         debug_ctrl_cmd_ref_pb4;	//0xC4D06310
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB5_T         debug_ctrl_cmd_ref_pb5;	//0xC4D06314
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB6_T         debug_ctrl_cmd_ref_pb6;	//0xC4D06318
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_PB7_T         debug_ctrl_cmd_ref_pb7;	//0xC4D0631C
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB0_T         debug_ctrl_cmd_prg_pb0;	//0xC4D06320
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB1_T         debug_ctrl_cmd_prg_pb1;	//0xC4D06324
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB2_T         debug_ctrl_cmd_prg_pb2;	//0xC4D06328
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB3_T         debug_ctrl_cmd_prg_pb3;	//0xC4D0632C
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB4_T         debug_ctrl_cmd_prg_pb4;	//0xC4D06330
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB5_T         debug_ctrl_cmd_prg_pb5;	//0xC4D06334
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB6_T         debug_ctrl_cmd_prg_pb6;	//0xC4D06338
	REG_DDRC_M0_DEBUG_CTRL_CMD_PRG_PB7_T         debug_ctrl_cmd_prg_pb7;	//0xC4D0633C
	REG_DDRC_M0_DEBUG_CTRL_CMD_CG_REF_AB_T     debug_ctrl_cmd_cg_ref_ab;	//0xC4D06340
	REG_DDRC_M0_DEBUG_CTRL_CMD_MF_REF_AB_T     debug_ctrl_cmd_mf_ref_ab;	//0xC4D06344
	UINT32                                                 reserved6019;	//0xC4D06348
	UINT32                                                 reserved6020;	//0xC4D0634C
	REG_DDRC_M0_DEBUG_CTRL_CMD_CG_PRG_AB_T     debug_ctrl_cmd_cg_prg_ab;	//0xC4D06350
	REG_DDRC_M0_DEBUG_CTRL_CMD_MF_PRG_AB_T     debug_ctrl_cmd_mf_prg_ab;	//0xC4D06354
	UINT32                                                 reserved6021;	//0xC4D06358
	UINT32                                                 reserved6022;	//0xC4D0635C
	REG_DDRC_M0_DEBUG_CTRL_CMD_CG_BL_T             debug_ctrl_cmd_cg_bl;	//0xC4D06360
	REG_DDRC_M0_DEBUG_CTRL_CMD_CG_AP_T             debug_ctrl_cmd_cg_ap;	//0xC4D06364
	REG_DDRC_M0_DEBUG_CTRL_CMD_REF_CYCLE_T     debug_ctrl_cmd_ref_cycle;	//0xC4D06368
	UINT32                                                 reserved6023;	//0xC4D0636C
	UINT32                                                 reserved6024;	//0xC4D06370
	UINT32                                                 reserved6025;	//0xC4D06374
	UINT32                                                 reserved6026;	//0xC4D06378
	UINT32                                                 reserved6027;	//0xC4D0637C
	UINT32                                                 reserved6028;	//0xC4D06380
	UINT32                                                 reserved6029;	//0xC4D06384
	UINT32                                                 reserved6030;	//0xC4D06388
	UINT32                                                 reserved6031;	//0xC4D0638C
	UINT32                                                 reserved6032;	//0xC4D06390
	UINT32                                                 reserved6033;	//0xC4D06394
	UINT32                                                 reserved6034;	//0xC4D06398
	UINT32                                                 reserved6035;	//0xC4D0639C
	UINT32                                                 reserved6036;	//0xC4D063A0
	UINT32                                                 reserved6037;	//0xC4D063A4
	UINT32                                                 reserved6038;	//0xC4D063A8
	UINT32                                                 reserved6039;	//0xC4D063AC
	UINT32                                                 reserved6040;	//0xC4D063B0
	UINT32                                                 reserved6041;	//0xC4D063B4
	UINT32                                                 reserved6042;	//0xC4D063B8
	UINT32                                                 reserved6043;	//0xC4D063BC
	UINT32                                                 reserved6044;	//0xC4D063C0
	UINT32                                                 reserved6045;	//0xC4D063C4
	UINT32                                                 reserved6046;	//0xC4D063C8
	UINT32                                                 reserved6047;	//0xC4D063CC
	UINT32                                                 reserved6048;	//0xC4D063D0
	UINT32                                                 reserved6049;	//0xC4D063D4
	UINT32                                                 reserved6050;	//0xC4D063D8
	UINT32                                                 reserved6051;	//0xC4D063DC
	UINT32                                                 reserved6052;	//0xC4D063E0
	UINT32                                                 reserved6053;	//0xC4D063E4
	UINT32                                                 reserved6054;	//0xC4D063E8
	UINT32                                                 reserved6055;	//0xC4D063EC
	UINT32                                                 reserved6056;	//0xC4D063F0
	UINT32                                                 reserved6057;	//0xC4D063F4
	UINT32                                                 reserved6058;	//0xC4D063F8
	UINT32                                                 reserved6059;	//0xC4D063FC
	UINT32                                                 reserved6060;	//0xC4D06400
	UINT32                                                 reserved6061;	//0xC4D06404
	UINT32                                                 reserved6062;	//0xC4D06408
	UINT32                                                 reserved6063;	//0xC4D0640C
	UINT32                                                 reserved6064;	//0xC4D06410
	UINT32                                                 reserved6065;	//0xC4D06414
	UINT32                                                 reserved6066;	//0xC4D06418
	UINT32                                                 reserved6067;	//0xC4D0641C
	UINT32                                                 reserved6068;	//0xC4D06420
	UINT32                                                 reserved6069;	//0xC4D06424
	UINT32                                                 reserved6070;	//0xC4D06428
	UINT32                                                 reserved6071;	//0xC4D0642C
	UINT32                                                 reserved6072;	//0xC4D06430
	UINT32                                                 reserved6073;	//0xC4D06434
	UINT32                                                 reserved6074;	//0xC4D06438
	UINT32                                                 reserved6075;	//0xC4D0643C
	UINT32                                                 reserved6076;	//0xC4D06440
	UINT32                                                 reserved6077;	//0xC4D06444
	UINT32                                                 reserved6078;	//0xC4D06448
	UINT32                                                 reserved6079;	//0xC4D0644C
	UINT32                                                 reserved6080;	//0xC4D06450
	UINT32                                                 reserved6081;	//0xC4D06454
	UINT32                                                 reserved6082;	//0xC4D06458
	UINT32                                                 reserved6083;	//0xC4D0645C
	UINT32                                                 reserved6084;	//0xC4D06460
	UINT32                                                 reserved6085;	//0xC4D06464
	UINT32                                                 reserved6086;	//0xC4D06468
	UINT32                                                 reserved6087;	//0xC4D0646C
	UINT32                                                 reserved6088;	//0xC4D06470
	UINT32                                                 reserved6089;	//0xC4D06474
	UINT32                                                 reserved6090;	//0xC4D06478
	UINT32                                                 reserved6091;	//0xC4D0647C
	UINT32                                                 reserved6092;	//0xC4D06480
	UINT32                                                 reserved6093;	//0xC4D06484
	UINT32                                                 reserved6094;	//0xC4D06488
	UINT32                                                 reserved6095;	//0xC4D0648C
	UINT32                                                 reserved6096;	//0xC4D06490
	UINT32                                                 reserved6097;	//0xC4D06494
	UINT32                                                 reserved6098;	//0xC4D06498
	UINT32                                                 reserved6099;	//0xC4D0649C
	UINT32                                                 reserved6100;	//0xC4D064A0
	UINT32                                                 reserved6101;	//0xC4D064A4
	UINT32                                                 reserved6102;	//0xC4D064A8
	UINT32                                                 reserved6103;	//0xC4D064AC
	UINT32                                                 reserved6104;	//0xC4D064B0
	UINT32                                                 reserved6105;	//0xC4D064B4
	UINT32                                                 reserved6106;	//0xC4D064B8
	UINT32                                                 reserved6107;	//0xC4D064BC
	UINT32                                                 reserved6108;	//0xC4D064C0
	UINT32                                                 reserved6109;	//0xC4D064C4
	UINT32                                                 reserved6110;	//0xC4D064C8
	UINT32                                                 reserved6111;	//0xC4D064CC
	UINT32                                                 reserved6112;	//0xC4D064D0
	UINT32                                                 reserved6113;	//0xC4D064D4
	UINT32                                                 reserved6114;	//0xC4D064D8
	UINT32                                                 reserved6115;	//0xC4D064DC
	UINT32                                                 reserved6116;	//0xC4D064E0
	UINT32                                                 reserved6117;	//0xC4D064E4
	UINT32                                                 reserved6118;	//0xC4D064E8
	UINT32                                                 reserved6119;	//0xC4D064EC
	UINT32                                                 reserved6120;	//0xC4D064F0
	UINT32                                                 reserved6121;	//0xC4D064F4
	UINT32                                                 reserved6122;	//0xC4D064F8
	UINT32                                                 reserved6123;	//0xC4D064FC
	UINT32                                                 reserved6124;	//0xC4D06500
	UINT32                                                 reserved6125;	//0xC4D06504
	UINT32                                                 reserved6126;	//0xC4D06508
	UINT32                                                 reserved6127;	//0xC4D0650C
	UINT32                                                 reserved6128;	//0xC4D06510
	UINT32                                                 reserved6129;	//0xC4D06514
	UINT32                                                 reserved6130;	//0xC4D06518
	UINT32                                                 reserved6131;	//0xC4D0651C
	UINT32                                                 reserved6132;	//0xC4D06520
	UINT32                                                 reserved6133;	//0xC4D06524
	UINT32                                                 reserved6134;	//0xC4D06528
	UINT32                                                 reserved6135;	//0xC4D0652C
	UINT32                                                 reserved6136;	//0xC4D06530
	UINT32                                                 reserved6137;	//0xC4D06534
	UINT32                                                 reserved6138;	//0xC4D06538
	UINT32                                                 reserved6139;	//0xC4D0653C
	UINT32                                                 reserved6140;	//0xC4D06540
	UINT32                                                 reserved6141;	//0xC4D06544
	UINT32                                                 reserved6142;	//0xC4D06548
	UINT32                                                 reserved6143;	//0xC4D0654C
	UINT32                                                 reserved6144;	//0xC4D06550
	UINT32                                                 reserved6145;	//0xC4D06554
	UINT32                                                 reserved6146;	//0xC4D06558
	UINT32                                                 reserved6147;	//0xC4D0655C
	UINT32                                                 reserved6148;	//0xC4D06560
	UINT32                                                 reserved6149;	//0xC4D06564
	UINT32                                                 reserved6150;	//0xC4D06568
	UINT32                                                 reserved6151;	//0xC4D0656C
	UINT32                                                 reserved6152;	//0xC4D06570
	UINT32                                                 reserved6153;	//0xC4D06574
	UINT32                                                 reserved6154;	//0xC4D06578
	UINT32                                                 reserved6155;	//0xC4D0657C
	UINT32                                                 reserved6156;	//0xC4D06580
	UINT32                                                 reserved6157;	//0xC4D06584
	UINT32                                                 reserved6158;	//0xC4D06588
	UINT32                                                 reserved6159;	//0xC4D0658C
	UINT32                                                 reserved6160;	//0xC4D06590
	UINT32                                                 reserved6161;	//0xC4D06594
	UINT32                                                 reserved6162;	//0xC4D06598
	UINT32                                                 reserved6163;	//0xC4D0659C
	UINT32                                                 reserved6164;	//0xC4D065A0
	UINT32                                                 reserved6165;	//0xC4D065A4
	UINT32                                                 reserved6166;	//0xC4D065A8
	UINT32                                                 reserved6167;	//0xC4D065AC
	UINT32                                                 reserved6168;	//0xC4D065B0
	UINT32                                                 reserved6169;	//0xC4D065B4
	UINT32                                                 reserved6170;	//0xC4D065B8
	UINT32                                                 reserved6171;	//0xC4D065BC
	UINT32                                                 reserved6172;	//0xC4D065C0
	UINT32                                                 reserved6173;	//0xC4D065C4
	UINT32                                                 reserved6174;	//0xC4D065C8
	UINT32                                                 reserved6175;	//0xC4D065CC
	UINT32                                                 reserved6176;	//0xC4D065D0
	UINT32                                                 reserved6177;	//0xC4D065D4
	UINT32                                                 reserved6178;	//0xC4D065D8
	UINT32                                                 reserved6179;	//0xC4D065DC
	UINT32                                                 reserved6180;	//0xC4D065E0
	UINT32                                                 reserved6181;	//0xC4D065E4
	UINT32                                                 reserved6182;	//0xC4D065E8
	UINT32                                                 reserved6183;	//0xC4D065EC
	UINT32                                                 reserved6184;	//0xC4D065F0
	UINT32                                                 reserved6185;	//0xC4D065F4
	UINT32                                                 reserved6186;	//0xC4D065F8
	UINT32                                                 reserved6187;	//0xC4D065FC
	UINT32                                                 reserved6188;	//0xC4D06600
	UINT32                                                 reserved6189;	//0xC4D06604
	UINT32                                                 reserved6190;	//0xC4D06608
	UINT32                                                 reserved6191;	//0xC4D0660C
	UINT32                                                 reserved6192;	//0xC4D06610
	UINT32                                                 reserved6193;	//0xC4D06614
	UINT32                                                 reserved6194;	//0xC4D06618
	UINT32                                                 reserved6195;	//0xC4D0661C
	UINT32                                                 reserved6196;	//0xC4D06620
	UINT32                                                 reserved6197;	//0xC4D06624
	UINT32                                                 reserved6198;	//0xC4D06628
	UINT32                                                 reserved6199;	//0xC4D0662C
	UINT32                                                 reserved6200;	//0xC4D06630
	UINT32                                                 reserved6201;	//0xC4D06634
	UINT32                                                 reserved6202;	//0xC4D06638
	UINT32                                                 reserved6203;	//0xC4D0663C
	UINT32                                                 reserved6204;	//0xC4D06640
	UINT32                                                 reserved6205;	//0xC4D06644
	UINT32                                                 reserved6206;	//0xC4D06648
	UINT32                                                 reserved6207;	//0xC4D0664C
	UINT32                                                 reserved6208;	//0xC4D06650
	UINT32                                                 reserved6209;	//0xC4D06654
	UINT32                                                 reserved6210;	//0xC4D06658
	UINT32                                                 reserved6211;	//0xC4D0665C
	UINT32                                                 reserved6212;	//0xC4D06660
	UINT32                                                 reserved6213;	//0xC4D06664
	UINT32                                                 reserved6214;	//0xC4D06668
	UINT32                                                 reserved6215;	//0xC4D0666C
	UINT32                                                 reserved6216;	//0xC4D06670
	UINT32                                                 reserved6217;	//0xC4D06674
	UINT32                                                 reserved6218;	//0xC4D06678
	UINT32                                                 reserved6219;	//0xC4D0667C
	UINT32                                                 reserved6220;	//0xC4D06680
	UINT32                                                 reserved6221;	//0xC4D06684
	UINT32                                                 reserved6222;	//0xC4D06688
	UINT32                                                 reserved6223;	//0xC4D0668C
	UINT32                                                 reserved6224;	//0xC4D06690
	UINT32                                                 reserved6225;	//0xC4D06694
	UINT32                                                 reserved6226;	//0xC4D06698
	UINT32                                                 reserved6227;	//0xC4D0669C
	UINT32                                                 reserved6228;	//0xC4D066A0
	UINT32                                                 reserved6229;	//0xC4D066A4
	UINT32                                                 reserved6230;	//0xC4D066A8
	UINT32                                                 reserved6231;	//0xC4D066AC
	UINT32                                                 reserved6232;	//0xC4D066B0
	UINT32                                                 reserved6233;	//0xC4D066B4
	UINT32                                                 reserved6234;	//0xC4D066B8
	UINT32                                                 reserved6235;	//0xC4D066BC
	UINT32                                                 reserved6236;	//0xC4D066C0
	UINT32                                                 reserved6237;	//0xC4D066C4
	UINT32                                                 reserved6238;	//0xC4D066C8
	UINT32                                                 reserved6239;	//0xC4D066CC
	UINT32                                                 reserved6240;	//0xC4D066D0
	UINT32                                                 reserved6241;	//0xC4D066D4
	UINT32                                                 reserved6242;	//0xC4D066D8
	UINT32                                                 reserved6243;	//0xC4D066DC
	UINT32                                                 reserved6244;	//0xC4D066E0
	UINT32                                                 reserved6245;	//0xC4D066E4
	UINT32                                                 reserved6246;	//0xC4D066E8
	UINT32                                                 reserved6247;	//0xC4D066EC
	UINT32                                                 reserved6248;	//0xC4D066F0
	UINT32                                                 reserved6249;	//0xC4D066F4
	UINT32                                                 reserved6250;	//0xC4D066F8
	UINT32                                                 reserved6251;	//0xC4D066FC
	REG_DDRC_M0_DEBUG_DFI_T                                   debug_dfi;	//0xC4D06700
	UINT32                                                 reserved6252;	//0xC4D06704
	UINT32                                                 reserved6253;	//0xC4D06708
	UINT32                                                 reserved6254;	//0xC4D0670C
	UINT32                                                 reserved6255;	//0xC4D06710
	UINT32                                                 reserved6256;	//0xC4D06714
	UINT32                                                 reserved6257;	//0xC4D06718
	UINT32                                                 reserved6258;	//0xC4D0671C
	UINT32                                                 reserved6259;	//0xC4D06720
	UINT32                                                 reserved6260;	//0xC4D06724
	UINT32                                                 reserved6261;	//0xC4D06728
	UINT32                                                 reserved6262;	//0xC4D0672C
	UINT32                                                 reserved6263;	//0xC4D06730
	UINT32                                                 reserved6264;	//0xC4D06734
	UINT32                                                 reserved6265;	//0xC4D06738
	UINT32                                                 reserved6266;	//0xC4D0673C
	UINT32                                                 reserved6267;	//0xC4D06740
	UINT32                                                 reserved6268;	//0xC4D06744
	UINT32                                                 reserved6269;	//0xC4D06748
	UINT32                                                 reserved6270;	//0xC4D0674C
	UINT32                                                 reserved6271;	//0xC4D06750
	UINT32                                                 reserved6272;	//0xC4D06754
	UINT32                                                 reserved6273;	//0xC4D06758
	UINT32                                                 reserved6274;	//0xC4D0675C
	UINT32                                                 reserved6275;	//0xC4D06760
	UINT32                                                 reserved6276;	//0xC4D06764
	UINT32                                                 reserved6277;	//0xC4D06768
	UINT32                                                 reserved6278;	//0xC4D0676C
	UINT32                                                 reserved6279;	//0xC4D06770
	UINT32                                                 reserved6280;	//0xC4D06774
	UINT32                                                 reserved6281;	//0xC4D06778
	UINT32                                                 reserved6282;	//0xC4D0677C
	UINT32                                                 reserved6283;	//0xC4D06780
	UINT32                                                 reserved6284;	//0xC4D06784
	UINT32                                                 reserved6285;	//0xC4D06788
	UINT32                                                 reserved6286;	//0xC4D0678C
	UINT32                                                 reserved6287;	//0xC4D06790
	UINT32                                                 reserved6288;	//0xC4D06794
	UINT32                                                 reserved6289;	//0xC4D06798
	UINT32                                                 reserved6290;	//0xC4D0679C
	UINT32                                                 reserved6291;	//0xC4D067A0
	UINT32                                                 reserved6292;	//0xC4D067A4
	UINT32                                                 reserved6293;	//0xC4D067A8
	UINT32                                                 reserved6294;	//0xC4D067AC
	UINT32                                                 reserved6295;	//0xC4D067B0
	UINT32                                                 reserved6296;	//0xC4D067B4
	UINT32                                                 reserved6297;	//0xC4D067B8
	UINT32                                                 reserved6298;	//0xC4D067BC
	UINT32                                                 reserved6299;	//0xC4D067C0
	UINT32                                                 reserved6300;	//0xC4D067C4
	UINT32                                                 reserved6301;	//0xC4D067C8
	UINT32                                                 reserved6302;	//0xC4D067CC
	UINT32                                                 reserved6303;	//0xC4D067D0
	UINT32                                                 reserved6304;	//0xC4D067D4
	UINT32                                                 reserved6305;	//0xC4D067D8
	UINT32                                                 reserved6306;	//0xC4D067DC
	UINT32                                                 reserved6307;	//0xC4D067E0
	UINT32                                                 reserved6308;	//0xC4D067E4
	UINT32                                                 reserved6309;	//0xC4D067E8
	UINT32                                                 reserved6310;	//0xC4D067EC
	UINT32                                                 reserved6311;	//0xC4D067F0
	UINT32                                                 reserved6312;	//0xC4D067F4
	UINT32                                                 reserved6313;	//0xC4D067F8
	UINT32                                                 reserved6314;	//0xC4D067FC
	REG_DDRC_M0_DRAM_BIST_CTRL_0_T                     dram_bist_ctrl_0;	//0xC4D06800
	REG_DDRC_M0_DRAM_BIST_CTRL_1_T                     dram_bist_ctrl_1;	//0xC4D06804
	REG_DDRC_M0_DRAM_BIST_CTRL_2_T                     dram_bist_ctrl_2;	//0xC4D06808
	REG_DDRC_M0_DRAM_BIST_DATA_0_T                     dram_bist_data_0;	//0xC4D0680C
	REG_DDRC_M0_DRAM_BIST_DATA_1_T                     dram_bist_data_1;	//0xC4D06810
	REG_DDRC_M0_DRAM_BIST_DATA_2_T                     dram_bist_data_2;	//0xC4D06814
	REG_DDRC_M0_DRAM_BIST_ADDR_0_T                     dram_bist_addr_0;	//0xC4D06818
	REG_DDRC_M0_DRAM_BIST_ADDR_1_T                     dram_bist_addr_1;	//0xC4D0681C
	REG_DDRC_M0_DRAM_BIST_ADDR_2_T                     dram_bist_addr_2;	//0xC4D06820
	REG_DDRC_M0_DRAM_BIST_OPCMD_0_T                   dram_bist_opcmd_0;	//0xC4D06824
	REG_DDRC_M0_DRAM_BIST_OPCMD_1_T                   dram_bist_opcmd_1;	//0xC4D06828
	REG_DDRC_M0_DRAM_BIST_OPCMD_2_T                   dram_bist_opcmd_2;	//0xC4D0682C
	REG_DDRC_M0_DRAM_BIST_OPCMD_3_T                   dram_bist_opcmd_3;	//0xC4D06830
	REG_DDRC_M0_DRAM_BIST_ERR_ADDR_INFO_T       dram_bist_err_addr_info;	//0xC4D06834
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_00_T dram_bist_err_data_info_00;	//0xC4D06838
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_01_T dram_bist_err_data_info_01;	//0xC4D0683C
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_02_T dram_bist_err_data_info_02;	//0xC4D06840
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_03_T dram_bist_err_data_info_03;	//0xC4D06844
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_04_T dram_bist_err_data_info_04;	//0xC4D06848
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_05_T dram_bist_err_data_info_05;	//0xC4D0684C
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_06_T dram_bist_err_data_info_06;	//0xC4D06850
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_07_T dram_bist_err_data_info_07;	//0xC4D06854
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_08_T dram_bist_err_data_info_08;	//0xC4D06858
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_09_T dram_bist_err_data_info_09;	//0xC4D0685C
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_10_T dram_bist_err_data_info_10;	//0xC4D06860
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_11_T dram_bist_err_data_info_11;	//0xC4D06864
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_12_T dram_bist_err_data_info_12;	//0xC4D06868
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_13_T dram_bist_err_data_info_13;	//0xC4D0686C
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_14_T dram_bist_err_data_info_14;	//0xC4D06870
	REG_DDRC_M0_DRAM_BIST_ERR_DATA_INFO_15_T dram_bist_err_data_info_15;	//0xC4D06874
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_00_T dram_bist_exp_data_info_00;	//0xC4D06878
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_01_T dram_bist_exp_data_info_01;	//0xC4D0687C
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_02_T dram_bist_exp_data_info_02;	//0xC4D06880
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_03_T dram_bist_exp_data_info_03;	//0xC4D06884
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_04_T dram_bist_exp_data_info_04;	//0xC4D06888
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_05_T dram_bist_exp_data_info_05;	//0xC4D0688C
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_06_T dram_bist_exp_data_info_06;	//0xC4D06890
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_07_T dram_bist_exp_data_info_07;	//0xC4D06894
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_08_T dram_bist_exp_data_info_08;	//0xC4D06898
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_09_T dram_bist_exp_data_info_09;	//0xC4D0689C
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_10_T dram_bist_exp_data_info_10;	//0xC4D068A0
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_11_T dram_bist_exp_data_info_11;	//0xC4D068A4
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_12_T dram_bist_exp_data_info_12;	//0xC4D068A8
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_13_T dram_bist_exp_data_info_13;	//0xC4D068AC
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_14_T dram_bist_exp_data_info_14;	//0xC4D068B0
	REG_DDRC_M0_DRAM_BIST_EXP_DATA_INFO_15_T dram_bist_exp_data_info_15;	//0xC4D068B4
	UINT32                                                 reserved6315;	//0xC4D068B8
	UINT32                                                 reserved6316;	//0xC4D068BC
	UINT32                                                 reserved6317;	//0xC4D068C0
	UINT32                                                 reserved6318;	//0xC4D068C4
	UINT32                                                 reserved6319;	//0xC4D068C8
	UINT32                                                 reserved6320;	//0xC4D068CC
	UINT32                                                 reserved6321;	//0xC4D068D0
	UINT32                                                 reserved6322;	//0xC4D068D4
	UINT32                                                 reserved6323;	//0xC4D068D8
	UINT32                                                 reserved6324;	//0xC4D068DC
	UINT32                                                 reserved6325;	//0xC4D068E0
	UINT32                                                 reserved6326;	//0xC4D068E4
	UINT32                                                 reserved6327;	//0xC4D068E8
	UINT32                                                 reserved6328;	//0xC4D068EC
	UINT32                                                 reserved6329;	//0xC4D068F0
	UINT32                                                 reserved6330;	//0xC4D068F4
	UINT32                                                 reserved6331;	//0xC4D068F8
	UINT32                                                 reserved6332;	//0xC4D068FC
	UINT32                                                 reserved6333;	//0xC4D06900
	UINT32                                                 reserved6334;	//0xC4D06904
	UINT32                                                 reserved6335;	//0xC4D06908
	UINT32                                                 reserved6336;	//0xC4D0690C
	UINT32                                                 reserved6337;	//0xC4D06910
	UINT32                                                 reserved6338;	//0xC4D06914
	UINT32                                                 reserved6339;	//0xC4D06918
	UINT32                                                 reserved6340;	//0xC4D0691C
	UINT32                                                 reserved6341;	//0xC4D06920
	UINT32                                                 reserved6342;	//0xC4D06924
	UINT32                                                 reserved6343;	//0xC4D06928
	UINT32                                                 reserved6344;	//0xC4D0692C
	UINT32                                                 reserved6345;	//0xC4D06930
	UINT32                                                 reserved6346;	//0xC4D06934
	UINT32                                                 reserved6347;	//0xC4D06938
	UINT32                                                 reserved6348;	//0xC4D0693C
	UINT32                                                 reserved6349;	//0xC4D06940
	UINT32                                                 reserved6350;	//0xC4D06944
	UINT32                                                 reserved6351;	//0xC4D06948
	UINT32                                                 reserved6352;	//0xC4D0694C
	UINT32                                                 reserved6353;	//0xC4D06950
	UINT32                                                 reserved6354;	//0xC4D06954
	UINT32                                                 reserved6355;	//0xC4D06958
	UINT32                                                 reserved6356;	//0xC4D0695C
	UINT32                                                 reserved6357;	//0xC4D06960
	UINT32                                                 reserved6358;	//0xC4D06964
	UINT32                                                 reserved6359;	//0xC4D06968
	UINT32                                                 reserved6360;	//0xC4D0696C
	UINT32                                                 reserved6361;	//0xC4D06970
	UINT32                                                 reserved6362;	//0xC4D06974
	UINT32                                                 reserved6363;	//0xC4D06978
	UINT32                                                 reserved6364;	//0xC4D0697C
	UINT32                                                 reserved6365;	//0xC4D06980
	UINT32                                                 reserved6366;	//0xC4D06984
	UINT32                                                 reserved6367;	//0xC4D06988
	UINT32                                                 reserved6368;	//0xC4D0698C
	UINT32                                                 reserved6369;	//0xC4D06990
	UINT32                                                 reserved6370;	//0xC4D06994
	UINT32                                                 reserved6371;	//0xC4D06998
	UINT32                                                 reserved6372;	//0xC4D0699C
	UINT32                                                 reserved6373;	//0xC4D069A0
	UINT32                                                 reserved6374;	//0xC4D069A4
	UINT32                                                 reserved6375;	//0xC4D069A8
	UINT32                                                 reserved6376;	//0xC4D069AC
	UINT32                                                 reserved6377;	//0xC4D069B0
	UINT32                                                 reserved6378;	//0xC4D069B4
	UINT32                                                 reserved6379;	//0xC4D069B8
	UINT32                                                 reserved6380;	//0xC4D069BC
	UINT32                                                 reserved6381;	//0xC4D069C0
	UINT32                                                 reserved6382;	//0xC4D069C4
	UINT32                                                 reserved6383;	//0xC4D069C8
	UINT32                                                 reserved6384;	//0xC4D069CC
	UINT32                                                 reserved6385;	//0xC4D069D0
	UINT32                                                 reserved6386;	//0xC4D069D4
	UINT32                                                 reserved6387;	//0xC4D069D8
	UINT32                                                 reserved6388;	//0xC4D069DC
	UINT32                                                 reserved6389;	//0xC4D069E0
	UINT32                                                 reserved6390;	//0xC4D069E4
	UINT32                                                 reserved6391;	//0xC4D069E8
	UINT32                                                 reserved6392;	//0xC4D069EC
	UINT32                                                 reserved6393;	//0xC4D069F0
	UINT32                                                 reserved6394;	//0xC4D069F4
	UINT32                                                 reserved6395;	//0xC4D069F8
	UINT32                                                 reserved6396;	//0xC4D069FC
	UINT32                                                 reserved6397;	//0xC4D06A00
	UINT32                                                 reserved6398;	//0xC4D06A04
	UINT32                                                 reserved6399;	//0xC4D06A08
	UINT32                                                 reserved6400;	//0xC4D06A0C
	UINT32                                                 reserved6401;	//0xC4D06A10
	UINT32                                                 reserved6402;	//0xC4D06A14
	UINT32                                                 reserved6403;	//0xC4D06A18
	UINT32                                                 reserved6404;	//0xC4D06A1C
	UINT32                                                 reserved6405;	//0xC4D06A20
	UINT32                                                 reserved6406;	//0xC4D06A24
	UINT32                                                 reserved6407;	//0xC4D06A28
	UINT32                                                 reserved6408;	//0xC4D06A2C
	UINT32                                                 reserved6409;	//0xC4D06A30
	UINT32                                                 reserved6410;	//0xC4D06A34
	UINT32                                                 reserved6411;	//0xC4D06A38
	UINT32                                                 reserved6412;	//0xC4D06A3C
	UINT32                                                 reserved6413;	//0xC4D06A40
	UINT32                                                 reserved6414;	//0xC4D06A44
	UINT32                                                 reserved6415;	//0xC4D06A48
	UINT32                                                 reserved6416;	//0xC4D06A4C
	UINT32                                                 reserved6417;	//0xC4D06A50
	UINT32                                                 reserved6418;	//0xC4D06A54
	UINT32                                                 reserved6419;	//0xC4D06A58
	UINT32                                                 reserved6420;	//0xC4D06A5C
	UINT32                                                 reserved6421;	//0xC4D06A60
	UINT32                                                 reserved6422;	//0xC4D06A64
	UINT32                                                 reserved6423;	//0xC4D06A68
	UINT32                                                 reserved6424;	//0xC4D06A6C
	UINT32                                                 reserved6425;	//0xC4D06A70
	UINT32                                                 reserved6426;	//0xC4D06A74
	UINT32                                                 reserved6427;	//0xC4D06A78
	UINT32                                                 reserved6428;	//0xC4D06A7C
	UINT32                                                 reserved6429;	//0xC4D06A80
	UINT32                                                 reserved6430;	//0xC4D06A84
	UINT32                                                 reserved6431;	//0xC4D06A88
	UINT32                                                 reserved6432;	//0xC4D06A8C
	UINT32                                                 reserved6433;	//0xC4D06A90
	UINT32                                                 reserved6434;	//0xC4D06A94
	UINT32                                                 reserved6435;	//0xC4D06A98
	UINT32                                                 reserved6436;	//0xC4D06A9C
	UINT32                                                 reserved6437;	//0xC4D06AA0
	UINT32                                                 reserved6438;	//0xC4D06AA4
	UINT32                                                 reserved6439;	//0xC4D06AA8
	UINT32                                                 reserved6440;	//0xC4D06AAC
	UINT32                                                 reserved6441;	//0xC4D06AB0
	UINT32                                                 reserved6442;	//0xC4D06AB4
	UINT32                                                 reserved6443;	//0xC4D06AB8
	UINT32                                                 reserved6444;	//0xC4D06ABC
	UINT32                                                 reserved6445;	//0xC4D06AC0
	UINT32                                                 reserved6446;	//0xC4D06AC4
	UINT32                                                 reserved6447;	//0xC4D06AC8
	UINT32                                                 reserved6448;	//0xC4D06ACC
	UINT32                                                 reserved6449;	//0xC4D06AD0
	UINT32                                                 reserved6450;	//0xC4D06AD4
	UINT32                                                 reserved6451;	//0xC4D06AD8
	UINT32                                                 reserved6452;	//0xC4D06ADC
	UINT32                                                 reserved6453;	//0xC4D06AE0
	UINT32                                                 reserved6454;	//0xC4D06AE4
	UINT32                                                 reserved6455;	//0xC4D06AE8
	UINT32                                                 reserved6456;	//0xC4D06AEC
	UINT32                                                 reserved6457;	//0xC4D06AF0
	UINT32                                                 reserved6458;	//0xC4D06AF4
	UINT32                                                 reserved6459;	//0xC4D06AF8
	UINT32                                                 reserved6460;	//0xC4D06AFC
	UINT32                                                 reserved6461;	//0xC4D06B00
	UINT32                                                 reserved6462;	//0xC4D06B04
	UINT32                                                 reserved6463;	//0xC4D06B08
	UINT32                                                 reserved6464;	//0xC4D06B0C
	UINT32                                                 reserved6465;	//0xC4D06B10
	UINT32                                                 reserved6466;	//0xC4D06B14
	UINT32                                                 reserved6467;	//0xC4D06B18
	UINT32                                                 reserved6468;	//0xC4D06B1C
	UINT32                                                 reserved6469;	//0xC4D06B20
	UINT32                                                 reserved6470;	//0xC4D06B24
	UINT32                                                 reserved6471;	//0xC4D06B28
	UINT32                                                 reserved6472;	//0xC4D06B2C
	UINT32                                                 reserved6473;	//0xC4D06B30
	UINT32                                                 reserved6474;	//0xC4D06B34
	UINT32                                                 reserved6475;	//0xC4D06B38
	UINT32                                                 reserved6476;	//0xC4D06B3C
	UINT32                                                 reserved6477;	//0xC4D06B40
	UINT32                                                 reserved6478;	//0xC4D06B44
	UINT32                                                 reserved6479;	//0xC4D06B48
	UINT32                                                 reserved6480;	//0xC4D06B4C
	UINT32                                                 reserved6481;	//0xC4D06B50
	UINT32                                                 reserved6482;	//0xC4D06B54
	UINT32                                                 reserved6483;	//0xC4D06B58
	UINT32                                                 reserved6484;	//0xC4D06B5C
	UINT32                                                 reserved6485;	//0xC4D06B60
	UINT32                                                 reserved6486;	//0xC4D06B64
	UINT32                                                 reserved6487;	//0xC4D06B68
	UINT32                                                 reserved6488;	//0xC4D06B6C
	UINT32                                                 reserved6489;	//0xC4D06B70
	UINT32                                                 reserved6490;	//0xC4D06B74
	UINT32                                                 reserved6491;	//0xC4D06B78
	UINT32                                                 reserved6492;	//0xC4D06B7C
	UINT32                                                 reserved6493;	//0xC4D06B80
	UINT32                                                 reserved6494;	//0xC4D06B84
	UINT32                                                 reserved6495;	//0xC4D06B88
	UINT32                                                 reserved6496;	//0xC4D06B8C
	UINT32                                                 reserved6497;	//0xC4D06B90
	UINT32                                                 reserved6498;	//0xC4D06B94
	UINT32                                                 reserved6499;	//0xC4D06B98
	UINT32                                                 reserved6500;	//0xC4D06B9C
	UINT32                                                 reserved6501;	//0xC4D06BA0
	UINT32                                                 reserved6502;	//0xC4D06BA4
	UINT32                                                 reserved6503;	//0xC4D06BA8
	UINT32                                                 reserved6504;	//0xC4D06BAC
	UINT32                                                 reserved6505;	//0xC4D06BB0
	UINT32                                                 reserved6506;	//0xC4D06BB4
	UINT32                                                 reserved6507;	//0xC4D06BB8
	UINT32                                                 reserved6508;	//0xC4D06BBC
	UINT32                                                 reserved6509;	//0xC4D06BC0
	UINT32                                                 reserved6510;	//0xC4D06BC4
	UINT32                                                 reserved6511;	//0xC4D06BC8
	UINT32                                                 reserved6512;	//0xC4D06BCC
	UINT32                                                 reserved6513;	//0xC4D06BD0
	UINT32                                                 reserved6514;	//0xC4D06BD4
	UINT32                                                 reserved6515;	//0xC4D06BD8
	UINT32                                                 reserved6516;	//0xC4D06BDC
	UINT32                                                 reserved6517;	//0xC4D06BE0
	UINT32                                                 reserved6518;	//0xC4D06BE4
	UINT32                                                 reserved6519;	//0xC4D06BE8
	UINT32                                                 reserved6520;	//0xC4D06BEC
	UINT32                                                 reserved6521;	//0xC4D06BF0
	UINT32                                                 reserved6522;	//0xC4D06BF4
	UINT32                                                 reserved6523;	//0xC4D06BF8
	UINT32                                                 reserved6524;	//0xC4D06BFC
	UINT32                                                 reserved6525;	//0xC4D06C00
	UINT32                                                 reserved6526;	//0xC4D06C04
	UINT32                                                 reserved6527;	//0xC4D06C08
	UINT32                                                 reserved6528;	//0xC4D06C0C
	UINT32                                                 reserved6529;	//0xC4D06C10
	UINT32                                                 reserved6530;	//0xC4D06C14
	UINT32                                                 reserved6531;	//0xC4D06C18
	UINT32                                                 reserved6532;	//0xC4D06C1C
	UINT32                                                 reserved6533;	//0xC4D06C20
	UINT32                                                 reserved6534;	//0xC4D06C24
	UINT32                                                 reserved6535;	//0xC4D06C28
	UINT32                                                 reserved6536;	//0xC4D06C2C
	UINT32                                                 reserved6537;	//0xC4D06C30
	UINT32                                                 reserved6538;	//0xC4D06C34
	UINT32                                                 reserved6539;	//0xC4D06C38
	UINT32                                                 reserved6540;	//0xC4D06C3C
	UINT32                                                 reserved6541;	//0xC4D06C40
	UINT32                                                 reserved6542;	//0xC4D06C44
	UINT32                                                 reserved6543;	//0xC4D06C48
	UINT32                                                 reserved6544;	//0xC4D06C4C
	UINT32                                                 reserved6545;	//0xC4D06C50
	UINT32                                                 reserved6546;	//0xC4D06C54
	UINT32                                                 reserved6547;	//0xC4D06C58
	UINT32                                                 reserved6548;	//0xC4D06C5C
	UINT32                                                 reserved6549;	//0xC4D06C60
	UINT32                                                 reserved6550;	//0xC4D06C64
	UINT32                                                 reserved6551;	//0xC4D06C68
	UINT32                                                 reserved6552;	//0xC4D06C6C
	UINT32                                                 reserved6553;	//0xC4D06C70
	UINT32                                                 reserved6554;	//0xC4D06C74
	UINT32                                                 reserved6555;	//0xC4D06C78
	UINT32                                                 reserved6556;	//0xC4D06C7C
	UINT32                                                 reserved6557;	//0xC4D06C80
	UINT32                                                 reserved6558;	//0xC4D06C84
	UINT32                                                 reserved6559;	//0xC4D06C88
	UINT32                                                 reserved6560;	//0xC4D06C8C
	UINT32                                                 reserved6561;	//0xC4D06C90
	UINT32                                                 reserved6562;	//0xC4D06C94
	UINT32                                                 reserved6563;	//0xC4D06C98
	UINT32                                                 reserved6564;	//0xC4D06C9C
	UINT32                                                 reserved6565;	//0xC4D06CA0
	UINT32                                                 reserved6566;	//0xC4D06CA4
	UINT32                                                 reserved6567;	//0xC4D06CA8
	UINT32                                                 reserved6568;	//0xC4D06CAC
	UINT32                                                 reserved6569;	//0xC4D06CB0
	UINT32                                                 reserved6570;	//0xC4D06CB4
	UINT32                                                 reserved6571;	//0xC4D06CB8
	UINT32                                                 reserved6572;	//0xC4D06CBC
	UINT32                                                 reserved6573;	//0xC4D06CC0
	UINT32                                                 reserved6574;	//0xC4D06CC4
	UINT32                                                 reserved6575;	//0xC4D06CC8
	UINT32                                                 reserved6576;	//0xC4D06CCC
	UINT32                                                 reserved6577;	//0xC4D06CD0
	UINT32                                                 reserved6578;	//0xC4D06CD4
	UINT32                                                 reserved6579;	//0xC4D06CD8
	UINT32                                                 reserved6580;	//0xC4D06CDC
	UINT32                                                 reserved6581;	//0xC4D06CE0
	UINT32                                                 reserved6582;	//0xC4D06CE4
	UINT32                                                 reserved6583;	//0xC4D06CE8
	UINT32                                                 reserved6584;	//0xC4D06CEC
	UINT32                                                 reserved6585;	//0xC4D06CF0
	UINT32                                                 reserved6586;	//0xC4D06CF4
	UINT32                                                 reserved6587;	//0xC4D06CF8
	UINT32                                                 reserved6588;	//0xC4D06CFC
	UINT32                                                 reserved6589;	//0xC4D06D00
	UINT32                                                 reserved6590;	//0xC4D06D04
	UINT32                                                 reserved6591;	//0xC4D06D08
	UINT32                                                 reserved6592;	//0xC4D06D0C
	UINT32                                                 reserved6593;	//0xC4D06D10
	UINT32                                                 reserved6594;	//0xC4D06D14
	UINT32                                                 reserved6595;	//0xC4D06D18
	UINT32                                                 reserved6596;	//0xC4D06D1C
	UINT32                                                 reserved6597;	//0xC4D06D20
	UINT32                                                 reserved6598;	//0xC4D06D24
	UINT32                                                 reserved6599;	//0xC4D06D28
	UINT32                                                 reserved6600;	//0xC4D06D2C
	UINT32                                                 reserved6601;	//0xC4D06D30
	UINT32                                                 reserved6602;	//0xC4D06D34
	UINT32                                                 reserved6603;	//0xC4D06D38
	UINT32                                                 reserved6604;	//0xC4D06D3C
	UINT32                                                 reserved6605;	//0xC4D06D40
	UINT32                                                 reserved6606;	//0xC4D06D44
	UINT32                                                 reserved6607;	//0xC4D06D48
	UINT32                                                 reserved6608;	//0xC4D06D4C
	UINT32                                                 reserved6609;	//0xC4D06D50
	UINT32                                                 reserved6610;	//0xC4D06D54
	UINT32                                                 reserved6611;	//0xC4D06D58
	UINT32                                                 reserved6612;	//0xC4D06D5C
	UINT32                                                 reserved6613;	//0xC4D06D60
	UINT32                                                 reserved6614;	//0xC4D06D64
	UINT32                                                 reserved6615;	//0xC4D06D68
	UINT32                                                 reserved6616;	//0xC4D06D6C
	UINT32                                                 reserved6617;	//0xC4D06D70
	UINT32                                                 reserved6618;	//0xC4D06D74
	UINT32                                                 reserved6619;	//0xC4D06D78
	UINT32                                                 reserved6620;	//0xC4D06D7C
	UINT32                                                 reserved6621;	//0xC4D06D80
	UINT32                                                 reserved6622;	//0xC4D06D84
	UINT32                                                 reserved6623;	//0xC4D06D88
	UINT32                                                 reserved6624;	//0xC4D06D8C
	UINT32                                                 reserved6625;	//0xC4D06D90
	UINT32                                                 reserved6626;	//0xC4D06D94
	UINT32                                                 reserved6627;	//0xC4D06D98
	UINT32                                                 reserved6628;	//0xC4D06D9C
	UINT32                                                 reserved6629;	//0xC4D06DA0
	UINT32                                                 reserved6630;	//0xC4D06DA4
	UINT32                                                 reserved6631;	//0xC4D06DA8
	UINT32                                                 reserved6632;	//0xC4D06DAC
	UINT32                                                 reserved6633;	//0xC4D06DB0
	UINT32                                                 reserved6634;	//0xC4D06DB4
	UINT32                                                 reserved6635;	//0xC4D06DB8
	UINT32                                                 reserved6636;	//0xC4D06DBC
	UINT32                                                 reserved6637;	//0xC4D06DC0
	UINT32                                                 reserved6638;	//0xC4D06DC4
	UINT32                                                 reserved6639;	//0xC4D06DC8
	UINT32                                                 reserved6640;	//0xC4D06DCC
	UINT32                                                 reserved6641;	//0xC4D06DD0
	UINT32                                                 reserved6642;	//0xC4D06DD4
	UINT32                                                 reserved6643;	//0xC4D06DD8
	UINT32                                                 reserved6644;	//0xC4D06DDC
	UINT32                                                 reserved6645;	//0xC4D06DE0
	UINT32                                                 reserved6646;	//0xC4D06DE4
	UINT32                                                 reserved6647;	//0xC4D06DE8
	UINT32                                                 reserved6648;	//0xC4D06DEC
	UINT32                                                 reserved6649;	//0xC4D06DF0
	UINT32                                                 reserved6650;	//0xC4D06DF4
	UINT32                                                 reserved6651;	//0xC4D06DF8
	UINT32                                                 reserved6652;	//0xC4D06DFC
	UINT32                                                 reserved6653;	//0xC4D06E00
	UINT32                                                 reserved6654;	//0xC4D06E04
	UINT32                                                 reserved6655;	//0xC4D06E08
	UINT32                                                 reserved6656;	//0xC4D06E0C
	UINT32                                                 reserved6657;	//0xC4D06E10
	UINT32                                                 reserved6658;	//0xC4D06E14
	UINT32                                                 reserved6659;	//0xC4D06E18
	UINT32                                                 reserved6660;	//0xC4D06E1C
	UINT32                                                 reserved6661;	//0xC4D06E20
	UINT32                                                 reserved6662;	//0xC4D06E24
	UINT32                                                 reserved6663;	//0xC4D06E28
	UINT32                                                 reserved6664;	//0xC4D06E2C
	UINT32                                                 reserved6665;	//0xC4D06E30
	UINT32                                                 reserved6666;	//0xC4D06E34
	UINT32                                                 reserved6667;	//0xC4D06E38
	UINT32                                                 reserved6668;	//0xC4D06E3C
	UINT32                                                 reserved6669;	//0xC4D06E40
	UINT32                                                 reserved6670;	//0xC4D06E44
	UINT32                                                 reserved6671;	//0xC4D06E48
	UINT32                                                 reserved6672;	//0xC4D06E4C
	UINT32                                                 reserved6673;	//0xC4D06E50
	UINT32                                                 reserved6674;	//0xC4D06E54
	UINT32                                                 reserved6675;	//0xC4D06E58
	UINT32                                                 reserved6676;	//0xC4D06E5C
	UINT32                                                 reserved6677;	//0xC4D06E60
	UINT32                                                 reserved6678;	//0xC4D06E64
	UINT32                                                 reserved6679;	//0xC4D06E68
	UINT32                                                 reserved6680;	//0xC4D06E6C
	UINT32                                                 reserved6681;	//0xC4D06E70
	UINT32                                                 reserved6682;	//0xC4D06E74
	UINT32                                                 reserved6683;	//0xC4D06E78
	UINT32                                                 reserved6684;	//0xC4D06E7C
	UINT32                                                 reserved6685;	//0xC4D06E80
	UINT32                                                 reserved6686;	//0xC4D06E84
	UINT32                                                 reserved6687;	//0xC4D06E88
	UINT32                                                 reserved6688;	//0xC4D06E8C
	UINT32                                                 reserved6689;	//0xC4D06E90
	UINT32                                                 reserved6690;	//0xC4D06E94
	UINT32                                                 reserved6691;	//0xC4D06E98
	UINT32                                                 reserved6692;	//0xC4D06E9C
	UINT32                                                 reserved6693;	//0xC4D06EA0
	UINT32                                                 reserved6694;	//0xC4D06EA4
	UINT32                                                 reserved6695;	//0xC4D06EA8
	UINT32                                                 reserved6696;	//0xC4D06EAC
	UINT32                                                 reserved6697;	//0xC4D06EB0
	UINT32                                                 reserved6698;	//0xC4D06EB4
	UINT32                                                 reserved6699;	//0xC4D06EB8
	UINT32                                                 reserved6700;	//0xC4D06EBC
	UINT32                                                 reserved6701;	//0xC4D06EC0
	UINT32                                                 reserved6702;	//0xC4D06EC4
	UINT32                                                 reserved6703;	//0xC4D06EC8
	UINT32                                                 reserved6704;	//0xC4D06ECC
	UINT32                                                 reserved6705;	//0xC4D06ED0
	UINT32                                                 reserved6706;	//0xC4D06ED4
	UINT32                                                 reserved6707;	//0xC4D06ED8
	UINT32                                                 reserved6708;	//0xC4D06EDC
	UINT32                                                 reserved6709;	//0xC4D06EE0
	UINT32                                                 reserved6710;	//0xC4D06EE4
	UINT32                                                 reserved6711;	//0xC4D06EE8
	UINT32                                                 reserved6712;	//0xC4D06EEC
	UINT32                                                 reserved6713;	//0xC4D06EF0
	UINT32                                                 reserved6714;	//0xC4D06EF4
	UINT32                                                 reserved6715;	//0xC4D06EF8
	UINT32                                                 reserved6716;	//0xC4D06EFC
	UINT32                                                 reserved6717;	//0xC4D06F00
	UINT32                                                 reserved6718;	//0xC4D06F04
	UINT32                                                 reserved6719;	//0xC4D06F08
	UINT32                                                 reserved6720;	//0xC4D06F0C
	UINT32                                                 reserved6721;	//0xC4D06F10
	UINT32                                                 reserved6722;	//0xC4D06F14
	UINT32                                                 reserved6723;	//0xC4D06F18
	UINT32                                                 reserved6724;	//0xC4D06F1C
	UINT32                                                 reserved6725;	//0xC4D06F20
	UINT32                                                 reserved6726;	//0xC4D06F24
	UINT32                                                 reserved6727;	//0xC4D06F28
	UINT32                                                 reserved6728;	//0xC4D06F2C
	UINT32                                                 reserved6729;	//0xC4D06F30
	UINT32                                                 reserved6730;	//0xC4D06F34
	UINT32                                                 reserved6731;	//0xC4D06F38
	UINT32                                                 reserved6732;	//0xC4D06F3C
	UINT32                                                 reserved6733;	//0xC4D06F40
	UINT32                                                 reserved6734;	//0xC4D06F44
	UINT32                                                 reserved6735;	//0xC4D06F48
	UINT32                                                 reserved6736;	//0xC4D06F4C
	UINT32                                                 reserved6737;	//0xC4D06F50
	UINT32                                                 reserved6738;	//0xC4D06F54
	UINT32                                                 reserved6739;	//0xC4D06F58
	UINT32                                                 reserved6740;	//0xC4D06F5C
	UINT32                                                 reserved6741;	//0xC4D06F60
	UINT32                                                 reserved6742;	//0xC4D06F64
	UINT32                                                 reserved6743;	//0xC4D06F68
	UINT32                                                 reserved6744;	//0xC4D06F6C
	UINT32                                                 reserved6745;	//0xC4D06F70
	UINT32                                                 reserved6746;	//0xC4D06F74
	UINT32                                                 reserved6747;	//0xC4D06F78
	UINT32                                                 reserved6748;	//0xC4D06F7C
	UINT32                                                 reserved6749;	//0xC4D06F80
	UINT32                                                 reserved6750;	//0xC4D06F84
	UINT32                                                 reserved6751;	//0xC4D06F88
	UINT32                                                 reserved6752;	//0xC4D06F8C
	UINT32                                                 reserved6753;	//0xC4D06F90
	UINT32                                                 reserved6754;	//0xC4D06F94
	UINT32                                                 reserved6755;	//0xC4D06F98
	UINT32                                                 reserved6756;	//0xC4D06F9C
	UINT32                                                 reserved6757;	//0xC4D06FA0
	UINT32                                                 reserved6758;	//0xC4D06FA4
	UINT32                                                 reserved6759;	//0xC4D06FA8
	UINT32                                                 reserved6760;	//0xC4D06FAC
	UINT32                                                 reserved6761;	//0xC4D06FB0
	UINT32                                                 reserved6762;	//0xC4D06FB4
	UINT32                                                 reserved6763;	//0xC4D06FB8
	UINT32                                                 reserved6764;	//0xC4D06FBC
	UINT32                                                 reserved6765;	//0xC4D06FC0
	UINT32                                                 reserved6766;	//0xC4D06FC4
	UINT32                                                 reserved6767;	//0xC4D06FC8
	UINT32                                                 reserved6768;	//0xC4D06FCC
	UINT32                                                 reserved6769;	//0xC4D06FD0
	UINT32                                                 reserved6770;	//0xC4D06FD4
	UINT32                                                 reserved6771;	//0xC4D06FD8
	UINT32                                                 reserved6772;	//0xC4D06FDC
	REG_DDRC_M0_REY_SPARE_T                                   rey_spare;	//0xC4D06FE0
}REG_DDRC_M0_T;

extern volatile REG_DDRC_M0_T*                     gpREG_DDRC_M0;
  
#endif
